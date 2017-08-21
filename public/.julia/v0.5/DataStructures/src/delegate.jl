# by JMW
macro delegate(source, targets)
    typename = esc(source.args[1])
    fieldname = source.args[2].args[1]
    funcnames = targets.args
    n = length(funcnames)
    fdefs = Vector{Any}(n)
    for i in 1:n
        funcname = esc(funcnames[i])
        fdefs[i] = quote
                     ($funcname)(a::($typename), args...) =
                       ($funcname)(a.$fieldname, args...)
                   end
    end
    return Expr(:block, fdefs...)
end

macro delegate_return_parent(source, targets)
    typename = esc(source.args[1])
    fieldname = source.args[2].args[1]
    funcnames = targets.args
    n = length(funcnames)
    fdefs = Vector{Any}(n)
    for i in 1:n
        funcname = esc(funcnames[i])
        fdefs[i] = quote
                     ($funcname)(a::($typename), args...) =
                       (($funcname)(a.$fieldname, args...); a)
                   end
    end
    return Expr(:block, fdefs...)
end
