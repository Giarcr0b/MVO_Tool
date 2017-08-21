# 32-bit fixed point; parameter `f` is the number of fraction bits
immutable Fixed{T <: Signed,f} <: FixedPoint{T,  f}
    i::T

    # constructor for manipulating the representation;
    # selected by passing an extra dummy argument
    (::Type{Fixed{T, f}}){T, f}(i::Integer, _) = new{T, f}(i % T)
    (::Type{Fixed{T, f}}){T, f}(x) = convert(Fixed{T,f}, x)
end

reinterpret{T<:Signed, f}(::Type{Fixed{T,f}}, x::T) = Fixed{T,f}(x, 0)

typechar{X<:Fixed}(::Type{X}) = 'Q'
signbits{X<:Fixed}(::Type{X}) = 1

for T in (Int8, Int16, Int32, Int64)
    for f in 0:sizeof(T)*8-1
        sym = Symbol(String(take!(showtype(_iotypealias, Fixed{T,f}))))
        @eval begin
            const $sym = Fixed{$T,$f}
            export $sym
        end
    end
end

# basic operators
-{T,f}(x::Fixed{T,f}) = Fixed{T,f}(-x.i,0)
abs{T,f}(x::Fixed{T,f}) = Fixed{T,f}(abs(x.i),0)

+{T,f}(x::Fixed{T,f}, y::Fixed{T,f}) = Fixed{T,f}(x.i+y.i,0)
-{T,f}(x::Fixed{T,f}, y::Fixed{T,f}) = Fixed{T,f}(x.i-y.i,0)

# with truncation:
#*{f}(x::Fixed32{f}, y::Fixed32{f}) = Fixed32{f}(Base.widemul(x.i,y.i)>>f,0)
# with rounding up:
*{T,f}(x::Fixed{T,f}, y::Fixed{T,f}) = Fixed{T,f}((Base.widemul(x.i,y.i) + (convert(widen(T), 1) << (f-1) ))>>f,0)

/{T,f}(x::Fixed{T,f}, y::Fixed{T,f}) = Fixed{T,f}(div(convert(widen(T), x.i) << f, y.i), 0)


# # conversions and promotions
convert{T,f}(::Type{Fixed{T,f}}, x::Integer) = Fixed{T,f}(round(T, convert(widen1(T),x)<<f),0)
convert{T,f}(::Type{Fixed{T,f}}, x::AbstractFloat) = Fixed{T,f}(round(T, trunc(widen1(T),x)<<f + rem(x,1)*(1<<f)),0)
convert{T,f}(::Type{Fixed{T,f}}, x::Rational) = Fixed{T,f}(x.num)/Fixed{T,f}(x.den)

rem{T,f}(x::Integer, ::Type{Fixed{T,f}}) = Fixed{T,f}(rem(x,T)<<f,0)
rem{T,f}(x::Real,    ::Type{Fixed{T,f}}) = Fixed{T,f}(rem(Integer(trunc(x)),T)<<f + rem(Integer(round(rem(x,1)*(1<<f))),T),0)

# convert{T,f}(::Type{AbstractFloat}, x::Fixed{T,f}) = convert(floattype(x), x)
float(x::Fixed) = convert(floattype(x), x)

convert{T,f}(::Type{BigFloat}, x::Fixed{T,f}) =
    convert(BigFloat,x.i>>f) + convert(BigFloat,x.i&(1<<f - 1))/convert(BigFloat,1<<f)
convert{TF<:AbstractFloat,T,f}(::Type{TF}, x::Fixed{T,f}) =
    convert(TF,x.i>>f) + convert(TF,x.i&(1<<f - 1))/convert(TF,1<<f)

convert{T,f}(::Type{Bool}, x::Fixed{T,f}) = x.i!=0
function convert{TI<:Integer, T,f}(::Type{TI}, x::Fixed{T,f})
    isinteger(x) || throw(InexactError())
    convert(TI, x.i>>f)
end

convert{TR<:Rational,T,f}(::Type{TR}, x::Fixed{T,f}) =
    convert(TR, x.i>>f + (x.i&(1<<f-1))//(1<<f))

promote_rule{T,f,TI<:Integer}(ft::Type{Fixed{T,f}}, ::Type{TI}) = Fixed{T,f}
promote_rule{T,f,TF<:AbstractFloat}(::Type{Fixed{T,f}}, ::Type{TF}) = TF
promote_rule{T,f,TR}(::Type{Fixed{T,f}}, ::Type{Rational{TR}}) = Rational{TR}

# TODO: Document and check that it still does the right thing.
decompose{T,f}(x::Fixed{T,f}) = x.i, -f, 1
