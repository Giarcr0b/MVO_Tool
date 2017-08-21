"""
The threading macro is like a more flexible version of the `|>` operator.

    @> x f = f(x)
    @> x g f == f(g(x))
    @> x a b c d e == e(d(c(b(a(x)))))

Unlike |>, functions can have arguments - the value
preceding a function will be treated as its first argument

    @> x g(y, z) f == f(g(x, y, z))

    @> x g f(y, z) == f(g(x), y, z)

See also `@>>`, `@as`.
"""
macro >(exs...)
  thread(x) = isexpr(x, :block) ? thread(rmlines(x).args...) : x

  thread(x, ex) =
    isexpr(ex, :call, :macrocall) ? Expr(ex.head, ex.args[1], x, ex.args[2:end]...) :
    isexpr(ex, :block)            ? thread(x, rmlines(ex).args...) :
    Expr(:call, ex, x)

  thread(x, exs...) = reduce(thread, x, exs)

  esc(thread(exs...))
end

"""
Same as `@>`, but threads the last argument.

  @>> x g(y, z) f == f(g(y, z, x))

  @>> x g f(y, z) == f(y, z, g(x))
"""
macro >>(exs...)
  thread(x) = isexpr(x, :block) ? thread(rmlines(x).args...) : x

  thread(x, ex) =
    isexpr(ex, :call, :macrocall) ? Expr(ex.head, ex.args..., x) :
    isexpr(ex, :block)            ? thread(x, rmlines(ex).args...) :
    Expr(:call, ex, x)

  thread(x, exs...) = reduce(thread, x, exs)

  esc(thread(exs...))
end
