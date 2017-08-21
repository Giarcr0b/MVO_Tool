# Dictionary which returns (and sets) a default value for a requested item not
# already in to the dictionary

# DefaultDictBase is the main class used to in Default*Dicts.
#
# Each related (immutable) Default*Dict class contains a single
# DefaultDictBase object as a member, and delegates almost all
# functions to this object.
#
# The main rationale for doing this instead of using type aliases is
# that this way, we can have actual class names and constructors for
# each of the DefaultDictBase "subclasses", in some sense getting
# around the Julia limitation of not allowing concrete classes to be
# subclassed.
#

@compat immutable DefaultDictBase{K,V,F,D} <: Associative{K,V}
    default::F
    d::D

    check_D(D,K,V) = (D <: Associative{K,V}) ||
        throw(ArgumentError("Default dict must be <: Associative{$K,$V}"))

    (::Type{DefaultDictBase{K,V,F,D}}){K,V,F,D}(x::F, kv::AbstractArray{Tuple{K,V}}) =
        (check_D(D,K,V); new{K,V,F,D}(x, D(kv)))
    (::Type{DefaultDictBase{K,V,F,D}}){K,V,F,D}(x::F, ps::Pair{K,V}...) =
        (check_D(D,K,V); new{K,V,F,D}(x, D(ps...)))

    (::Type{DefaultDictBase{K,V,F,D}}){K,V,F,D<:DefaultDictBase}(x::F, d::D) =
        (check_D(D,K,V); DefaultDictBase(x, d.d))
    (::Type{DefaultDictBase{K,V,F,D}}){K,V,F,D}(x::F, d::D = D()) =
        (check_D(D,K,V); new{K,V,F,D}(x, d))
end

# Constructors

DefaultDictBase() = throw(ArgumentError("no default specified"))
DefaultDictBase(k,v) = throw(ArgumentError("no default specified"))

# syntax entry points
DefaultDictBase{F}(default::F) = DefaultDictBase{Any,Any,F,Dict{Any,Any}}(default)
DefaultDictBase{K,V,F}(default::F, kv::AbstractArray{Tuple{K,V}}) = DefaultDictBase{K,V,F,Dict{K,V}}(default, kv)
DefaultDictBase{K,V,F}(default::F, ps::Pair{K,V}...) = DefaultDictBase{K,V,F,Dict{K,V}}(default, ps...)
DefaultDictBase{F,D<:Associative}(default::F, d::D) = (K=keytype(d); V=valtype(d); DefaultDictBase{K,V,F,D}(default, d))

# Constructor for DefaultDictBase{Int,Float64}(0.0)
@compat (::Type{DefaultDictBase{K,V}}){K,V,F}(default::F) = DefaultDictBase{K,V,F,Dict{K,V}}(default)

# Functions

# most functions are simply delegated to the wrapped dictionary
@delegate DefaultDictBase.d [ get, haskey, getkey, pop!,
                              start, done, next, isempty, length ]

# Some functions are delegated, but then need to return the main dictionary
# NOTE: push! is not included below, because the fallback version just
#       calls setindex!
@delegate_return_parent DefaultDictBase.d [ delete!, empty!, setindex!, sizehint! ]

similar{K,V,F}(d::DefaultDictBase{K,V,F}) = DefaultDictBase{K,V,F}(d.default)
in{T<:DefaultDictBase}(key, v::Base.KeyIterator{T}) = key in keys(v.dict.d)
next{T<:DefaultDictBase}(v::Base.KeyIterator{T}, i) = (v.dict.d.keys[i], Base.skip_deleted(v.dict.d,i+1))
next{T<:DefaultDictBase}(v::Base.ValueIterator{T}, i) = (v.dict.d.vals[i], Base.skip_deleted(v.dict.d,i+1))

getindex(d::DefaultDictBase, key) = get!(d.d, key, d.default)

function getindex{K,V,F<:Base.Callable}(d::DefaultDictBase{K,V,F}, key)
    return get!(d.d, key) do
        d.default()
    end
end



################

# Here begins the actual definition of the DefaultDict and
# DefaultOrderedDict classes.  As noted above, these are simply
# wrappers around a DefaultDictBase object, and delegate all functions
# to that object

for _Dict in [:Dict, :OrderedDict]
    DefaultDict = Symbol("Default"*string(_Dict))
    @eval begin
        @compat immutable $DefaultDict{K,V,F} <: Associative{K,V}
            d::DefaultDictBase{K,V,F,$_Dict{K,V}}

            (::Type{$DefaultDict{K,V,F}}){K,V,F}(x, ps::Pair{K,V}...) =
                new{K,V,F}(DefaultDictBase{K,V,F,$_Dict{K,V}}(x, ps...))
            (::Type{$DefaultDict{K,V,F}}){K,V,F}(x, kv::AbstractArray{Tuple{K,V}}) =
                new{K,V,F}(DefaultDictBase{K,V,F,$_Dict{K,V}}(x, kv))
            (::Type{$DefaultDict{K,V,F}}){K,V,F}(x, d::$DefaultDict) = $DefaultDict(x, d.d)
            (::Type{$DefaultDict{K,V,F}}){K,V,F}(x, d::$_Dict) =
                new{K,V,F}(DefaultDictBase{K,V,F,$_Dict{K,V}}(x, d))
            (::Type{$DefaultDict{K,V,F}}){K,V,F}(x) =
                new{K,V,F}(DefaultDictBase{K,V,F,$_Dict{K,V}}(x))
        end

        ## Constructors

        $DefaultDict() = throw(ArgumentError("$DefaultDict: no default specified"))
        $DefaultDict(k,v) = throw(ArgumentError("$DefaultDict: no default specified"))

        # syntax entry points
        $DefaultDict{F}(default::F) = $DefaultDict{Any,Any,F}(default)
        $DefaultDict{K,V,F}(default::F, kv::AbstractArray{Tuple{K,V}}) = $DefaultDict{K,V,F}(default, kv)
        $DefaultDict{K,V,F}(default::F, ps::Pair{K,V}...) = $DefaultDict{K,V,F}(default, ps...)

        $DefaultDict{F}(default::F, d::Associative) = ((K,V)= (Base.keytype(d), Base.valtype(d)); $DefaultDict{K,V,F}(default, $_Dict(d)))

        # Constructor syntax: DefaultDictBase{Int,Float64}(default)
        @compat (::Type{$DefaultDict{K,V}}){K,V}() = throw(ArgumentError("$DefaultDict: no default specified"))
        @compat (::Type{$DefaultDict{K,V}}){K,V,F}(default::F) = $DefaultDict{K,V,F}(default)

        ## Functions

        # Most functions are simply delegated to the wrapped DefaultDictBase object
        @delegate $DefaultDict.d [ getindex, get, get!, haskey,
                                   getkey, pop!, start, next,
                                   done, isempty, length ]

        # Some functions are delegated, but then need to return the main dictionary
        # NOTE: push! is not included below, because the fallback version just
        #       calls setindex!
        @delegate_return_parent $DefaultDict.d [ delete!, empty!, setindex!, sizehint! ]

        # NOTE: The second and third definition of push! below are only
        # necessary for disambiguating with the fourth, fifth, and sixth
        # definitions of push! below.
        # If these are removed, the second and third definitions can be
        # removed as well.
        push!(d::$DefaultDict, p::Pair) = (setindex!(d.d, p.second, p.first); d)
        push!(d::$DefaultDict, p::Pair, q::Pair) = push!(push!(d, p), q)
        push!(d::$DefaultDict, p::Pair, q::Pair, r::Pair...) = push!(push!(push!(d, p), q), r...)

        push!(d::$DefaultDict, p) = (setindex!(d.d, p[2], p[1]); d)
        push!(d::$DefaultDict, p, q) = push!(push!(d, p), q)
        push!(d::$DefaultDict, p, q, r...) = push!(push!(push!(d, p), q), r...)

        similar{K,V,F}(d::$DefaultDict{K,V,F}) = $DefaultDict{K,V,F}(d.d.default)
        in{T<:$DefaultDict}(key, v::Base.KeyIterator{T}) = key in keys(v.dict.d.d)
    end
end


## This should be uncommented to provide a DefaultSortedDict

# immutable DefaultSortedDict{K,V,F} <: Associative{K,V}
#     d::DefaultDictBase{K,V,F,SortedDict{K,V}}

#     DefaultSortedDict(x, kv::AbstractArray{(K,V)}) = new(DefaultDictBase{K,V,F,SortedDict{K,V}}(x, kv))
#     DefaultSortedDict(x, d::DefaultSortedDict) = DefaultSortedDict(x, d.d)
#     DefaultSortedDict(x, d::SortedDict) = new(DefaultDictBase{K,V,F,SortedDict{K,V}}(x, d))
#     DefaultSortedDict(x) = new(DefaultDictBase{K,V,F,SortedDict{K,V}}(x))
#     DefaultSortedDict(x, ks, vs) = new(DefaultDictBase{K,V,F,SortedDict{K,V}}(x,ks,vs))
# end

## Constructors

# DefaultSortedDict() = throw(ArgumentError("DefaultSortedDict: no default specified"))
# DefaultSortedDict(k,v) = throw(ArgumentError("DefaultSortedDict: no default specified"))

# # TODO: these mimic similar Dict constructors, but may not be needed
# DefaultSortedDict{K,V,F}(default::F, ks::AbstractArray{K}, vs::AbstractArray{V}) = DefaultSortedDict{K,V,F}(default,ks,vs)
# DefaultSortedDict{F}(default::F,ks,vs) = DefaultSortedDict{Any,Any,F}(default, ks, vs)

# # syntax entry points
# DefaultSortedDict{F}(default::F) = DefaultSortedDict{Any,Any,F}(default)
# DefaultSortedDict{K,V,F}(::Type{K}, ::Type{V}, default::F) = DefaultSortedDict{K,V,F}(default)
# DefaultSortedDict{K,V,F}(default::F, kv::AbstractArray{(K,V)}) = DefaultSortedDict{K,V,F}(default, kv)

# DefaultSortedDict{F}(default::F, d::Associative) = ((K,V)=eltype(d); DefaultSortedDict{K,V,F}(default, SortedDict(d)))

## Functions

## Most functions are simply delegated to the wrapped DefaultDictBase object

# @delegate DefaultSortedDict.d [ getindex, get, get!, haskey,
#                                 getkey, pop!, start, next,
#                                 done, isempty, length]
# @delegate_return_parent DefaultSortedDict.d [ delete!, empty!, setindex!, sizehint! ]

# similar{K,V,F}(d::DefaultSortedDict{K,V,F}) = DefaultSortedDict{K,V,F}(d.d.default)
# in{T<:DefaultSortedDict}(key, v::Base.KeyIterator{T}) = key in keys(v.dict.d.d)
