#  Copyright 2016, Iain Dunning, Joey Huchette, Miles Lubin, and contributors
#  This Source Code Form is subject to the terms of the Mozilla Public
#  License, v. 2.0. If a copy of the MPL was not distributed with this
#  file, You can obtain one at http://mozilla.org/MPL/2.0/.

using Base.Meta
# multivarate "dictionary" used for collections of variables/constraints

abstract JuMPContainer{T,N}

include("JuMPArray.jl")

type IndexPair
    idxvar
    idxset
end

type JuMPDict{T,N} <: JuMPContainer{T,N}
    tupledict::Dict{NTuple{N,Any},T}
    meta::Dict{Symbol,Any}

    JuMPDict() = new(Dict{NTuple{N,Any},T}(), Dict{Symbol,Any}())
end

function JuMPDict{T,N}(d::Dict{NTuple{N,Any},T})
    tmp = JuMPDict{T,N}()
    tmp.tupledict = d
    tmp
end

function JuMPDict{T,N}(d::Dict{NTuple{N,Any},T}, meta::Dict{Symbol,Any})
    tmp = JuMPDict{T,N}()
    tmp.tupledict = d
    tmp.meta = meta
    tmp
end

type JuMPContainerData
    name
    indexsets
    indexexprs::Vector{IndexPair}
    condition
end

#JuMPDict{T,N}(name::AbstractString) =
#    JuMPDict{T,N}(Dict{NTuple{N},T}(), name)

Base.getindex(d::JuMPDict, t...) = d.tupledict[t]
Base.setindex!(d::JuMPDict, value, t...) = (d.tupledict[t] = value)

Base.map(f::Function, d::JuMPArray) =
    JuMPArray(map(f, d.innerArray), d.indexsets, d.lookup, d.meta)

function Base.map{T,N}(f::Function, d::JuMPDict{T,N})
    ret = Base.return_types(f, Tuple{T})
    R = (length(ret) == 1 ? ret[1] : Any)
    x = JuMPDict{R,N}()
    for (k,v) in d.tupledict
        x.tupledict[k] = f(v)
    end
    return x
end

Base.isempty(d::JuMPContainer) = isempty(_innercontainer(d))

coloncheck(args::Number...) = nothing

function coloncheck(args...)
    if any(t -> t == Colon(), args)
        error("Colons not allowed as keys in JuMP containers.")
    end
end

# generate and instantiate a type which is indexed by the given index sets
# the following types of index sets are allowed:
# 0:K -- range with compile-time starting index
# S -- general iterable set
function gendict(instancename,T,idxsets...)
    N = length(idxsets)
    truearray = true
    for idxset in idxsets
        s = isexpr(idxset,:escape) ? idxset.args[1] : idxset
        if !(isexpr(s,:(:)) && length(s.args) == 2 && s.args[1] == 1)
            truearray = false
            break
        end
    end
    sizes = Expr(:tuple, [:(length($rng)) for rng in idxsets]...)
    if truearray
        :($instancename = Array($T, $sizes))
    else
        indexsets = Expr(:tuple, idxsets...)
        :($instancename = JuMPArray(Array($T, $sizes), $indexsets))
    end
end

pushmeta!(x::JuMPContainer, sym::Symbol, val) = (x.meta[sym] = val)
getmeta(x::JuMPContainer, sym::Symbol) = x.meta[sym]

# duck typing approach -- if eltype(innerArray) doesn't support accessor, will fail
for accessor in (:getdual, :getlowerbound, :getupperbound)
    @eval $accessor(x::Union{JuMPContainer,Array}) = map($accessor,x)
end

_similar(x::Array) = Array(Float64,size(x))
_similar{T}(x::Dict{T}) = Dict{T,Float64}()

_innercontainer(x::JuMPArray) = x.innerArray
_innercontainer(x::JuMPDict)  = x.tupledict

function _getValueInner(x)
    vars = _innercontainer(x)
    vals = _similar(vars)
    data = printdata(x)
    warnedyet = false
    for I in eachindex(vars)
        tmp = _getValue(vars[I])
        if isnan(tmp) && !warnedyet
            warn("Variable value not defined for entry of $(data.name). Check that the model was properly solved.")
            warnedyet = true
        end
        vals[I] = tmp
    end
    vals
end

JuMPContainer_from(x::JuMPDict,inner) = JuMPDict(inner)
JuMPContainer_from(x::JuMPArray,inner) = JuMPArray(inner, x.indexsets)

function getvalue(x::JuMPContainer)
    getvalue_warn(x)
    ret = JuMPContainer_from(x,_getValueInner(x))
    # I guess copy!(::Dict, ::Dict) isn't defined, so...
    for (key,val) in x.meta
        ret.meta[key] = val
    end
    m = getmeta(x, :model)
    # cache indexing info for new container for printing purposes
    m.varData[ret] = printdata(x)
    ret
end

# delegate zero-argument functions
for f in (:(Base.ndims), :(Base.length), :(Base.abs))
    @eval $f(x::JuMPArray) = $f(x.innerArray)
end

Base.length(x::JuMPDict) = length(x.tupledict)

Base.ndims{T,N}(x::JuMPDict{T,N}) = N
Base.abs(x::JuMPDict) = map(abs, x)
# avoid dangerous behavior with "end" (#730)
Base.endof(x::JuMPArray) = error("endof() (and \"end\" syntax) not implemented for JuMPArray objects.")
Base.size(x::JuMPArray) = error("size (and \"end\" syntax) not implemented for JuMPArray objects. Use JuMP.size if you want to access the dimensions.")
Base.size(x::JuMPArray,k) = error("size (and \"end\" syntax) not implemented for JuMPArray objects. Use JuMP.size if you want to access the dimensions.")
size(x::JuMPArray) = size(x.innerArray)
size(x::JuMPArray,k) = size(x.innerArray,k)
# for uses of size() within JuMP
size(x) = Base.size(x)
size(x,k) = Base.size(x,k)
# delegate one-argument functions
Compat.issymmetric(x::JuMPArray) = Compat.issymmetric(x.innerArray)

Base.eltype{T}(x::JuMPContainer{T}) = T

Base.full(x::JuMPContainer) = x

# keys/vals iterations for JuMPContainers
Base.keys(d::JuMPDict)    = keys(d.tupledict)
Base.values(d::JuMPDict)  = values(d.tupledict)

Base.keys(d::JuMPArray)   = KeyIterator(d)
Base.values(d::JuMPArray) = ValueIterator(d.innerArray)

# Wrapper type so that you can't access the values directly
type ValueIterator{T,N}
    x::Array{T,N}
end
Base.start(it::ValueIterator)   =  start(it.x)
Base.next(it::ValueIterator, k) =   next(it.x, k)
Base.done(it::ValueIterator, k) =   done(it.x, k)
Base.length(it::ValueIterator)  = length(it.x)

type KeyIterator{JA<:JuMPArray}
    x::JA
end
Base.start(it::KeyIterator)   =  start(it.x.innerArray)
@generated __next{T,N,NT}(x::JuMPArray{T,N,NT}, k) =
    quote
        subidx = ind2sub(size(x),k)
        $(Expr(:tuple, [:(x.indexsets[$i][subidx[$i]]) for i in 1:N]...)), next(x.innerArray,k)[2]
    end
Base.next(it::KeyIterator, k) = __next(it.x,k)
Base.done(it::KeyIterator, k) =   done(it.x.innerArray, k)
Base.length(it::KeyIterator)  = length(it.x.innerArray)
