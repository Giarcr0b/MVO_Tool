# Type hierarchy to aid in splitting up of SHA2 algorithms
# as SHA224/256 are similar, and SHA-384/512 are similar
@compat abstract type SHA_CTX end
@compat abstract type SHA2_CTX <: SHA_CTX end
@compat abstract type SHA3_CTX <: SHA_CTX end
import Base: copy

# We derive SHA1_CTX straight from SHA_CTX since it doesn't have a
# family of types like SHA2 or SHA3 do
type SHA1_CTX <: SHA_CTX
    state::Array{UInt32,1}
    bytecount::UInt64
    buffer::Array{UInt8,1}
    W::Array{UInt32,1}
end

# SHA2 224/256/384/512-bit Context Structures
type SHA2_224_CTX <: SHA2_CTX
    state::Array{UInt32,1}
    bytecount::UInt64
    buffer::Array{UInt8,1}
end

type SHA2_256_CTX <: SHA2_CTX
    state::Array{UInt32,1}
    bytecount::UInt64
    buffer::Array{UInt8,1}
end

type SHA2_384_CTX <: SHA2_CTX
    state::Array{UInt64,1}
    bytecount::UInt128
    buffer::Array{UInt8,1}
end

type SHA2_512_CTX <: SHA2_CTX
    state::Array{UInt64,1}
    bytecount::UInt128
    buffer::Array{UInt8,1}
end

# Typealias common nicknames for SHA2 family of functions
const SHA224_CTX = SHA2_224_CTX
const SHA256_CTX = SHA2_256_CTX
const SHA384_CTX = SHA2_384_CTX
const SHA512_CTX = SHA2_512_CTX


# SHA3 224/256/384/512-bit context structures
type SHA3_224_CTX <: SHA3_CTX
    state::Array{UInt64,1}
    bytecount::UInt128
    buffer::Array{UInt8,1}
end
type SHA3_256_CTX <: SHA3_CTX
    state::Array{UInt64,1}
    bytecount::UInt128
    buffer::Array{UInt8,1}
end
type SHA3_384_CTX <: SHA3_CTX
    state::Array{UInt64,1}
    bytecount::UInt128
    buffer::Array{UInt8,1}
end
type SHA3_512_CTX <: SHA3_CTX
    state::Array{UInt64,1}
    bytecount::UInt128
    buffer::Array{UInt8,1}
end

# Define constants via functions so as not to bloat context objects.  Yay dispatch!

# Digest lengths for SHA1, SHA2 and SHA3.  This is easy to figure out from the typename
digestlen(::Type{SHA1_CTX}) = 20
digestlen(::Type{SHA2_224_CTX}) = 28
digestlen(::Type{SHA3_224_CTX}) = 28
digestlen(::Type{SHA2_256_CTX}) = 32
digestlen(::Type{SHA3_256_CTX}) = 32
digestlen(::Type{SHA2_384_CTX}) = 48
digestlen(::Type{SHA3_384_CTX}) = 48
digestlen(::Type{SHA2_512_CTX}) = 64
digestlen(::Type{SHA3_512_CTX}) = 64

# SHA1 and SHA2 have differing element types for the internal state objects
state_type(::Type{SHA1_CTX}) = UInt32
state_type(::Type{SHA2_224_CTX}) = UInt32
state_type(::Type{SHA2_256_CTX}) = UInt32
state_type(::Type{SHA2_384_CTX}) = UInt64
state_type(::Type{SHA2_512_CTX}) = UInt64

# blocklen is the number of bytes of data processed by the transform!() function at once
blocklen(::Type{SHA1_CTX}) = UInt64(64)
blocklen(::Type{SHA2_224_CTX}) = UInt64(64)
blocklen(::Type{SHA2_256_CTX}) = UInt64(64)
blocklen(::Type{SHA2_384_CTX}) = UInt64(128)
blocklen(::Type{SHA2_512_CTX}) = UInt64(128)

blocklen(::Type{SHA3_224_CTX}) = UInt64(25*8 - 2*digestlen(SHA3_224_CTX))
blocklen(::Type{SHA3_256_CTX}) = UInt64(25*8 - 2*digestlen(SHA3_256_CTX))
blocklen(::Type{SHA3_384_CTX}) = UInt64(25*8 - 2*digestlen(SHA3_384_CTX))
blocklen(::Type{SHA3_512_CTX}) = UInt64(25*8 - 2*digestlen(SHA3_512_CTX))


# short_blocklen is the size of a block minus the width of bytecount
short_blocklen{T<:Union{SHA1_CTX,SHA2_CTX}}(::Type{T}) = blocklen(T) - 2*sizeof(state_type(T))

# Once the "blocklen" methods are defined, we can define our outer constructors for SHA types:
SHA2_224_CTX() = SHA2_224_CTX(copy(SHA2_224_initial_hash_value), 0, zeros(UInt8, blocklen(SHA2_224_CTX)))
SHA2_256_CTX() = SHA2_256_CTX(copy(SHA2_256_initial_hash_value), 0, zeros(UInt8, blocklen(SHA2_256_CTX)))
SHA2_384_CTX() = SHA2_384_CTX(copy(SHA2_384_initial_hash_value), 0, zeros(UInt8, blocklen(SHA2_384_CTX)))
SHA2_512_CTX() = SHA2_512_CTX(copy(SHA2_512_initial_hash_value), 0, zeros(UInt8, blocklen(SHA2_512_CTX)))

SHA3_224_CTX() = SHA3_224_CTX(zeros(UInt64, 25), 0, zeros(UInt8, blocklen(SHA3_224_CTX)))
SHA3_256_CTX() = SHA3_256_CTX(zeros(UInt64, 25), 0, zeros(UInt8, blocklen(SHA3_256_CTX)))
SHA3_384_CTX() = SHA3_384_CTX(zeros(UInt64, 25), 0, zeros(UInt8, blocklen(SHA3_384_CTX)))
SHA3_512_CTX() = SHA3_512_CTX(zeros(UInt64, 25), 0, zeros(UInt8, blocklen(SHA3_512_CTX)))

# Nickname'd outer constructor methods for SHA2
SHA224_CTX = SHA2_224_CTX
SHA256_CTX = SHA2_256_CTX
SHA384_CTX = SHA2_384_CTX
SHA512_CTX = SHA2_512_CTX

# SHA1 is special; he needs extra workspace
SHA1_CTX() = SHA1_CTX(copy(SHA1_initial_hash_value), 0, zeros(UInt8, blocklen(SHA1_CTX)), Vector{UInt32}(80))


# Copy functions
copy{T <: SHA1_CTX}(ctx::T) = T(copy(ctx.state), ctx.bytecount, copy(ctx.buffer), copy(ctx.W))
copy{T <: SHA2_CTX}(ctx::T) = T(copy(ctx.state), ctx.bytecount, copy(ctx.buffer))
copy{T <: SHA3_CTX}(ctx::T) = T(copy(ctx.state), ctx.bytecount, copy(ctx.buffer))


# Make printing these types a little friendlier
import Base.show
show(io::IO, ::SHA1_CTX) = write(io, "SHA1 hash state")
show(io::IO, ::SHA2_224_CTX) = write(io, "SHA2 224-bit hash state")
show(io::IO, ::SHA2_256_CTX) = write(io, "SHA2 256-bit hash state")
show(io::IO, ::SHA2_384_CTX) = write(io, "SHA2 384-bit hash state")
show(io::IO, ::SHA2_512_CTX) = write(io, "SHA2 512-bit hash state")
show(io::IO, ::SHA3_224_CTX) = write(io, "SHA3 224-bit hash state")
show(io::IO, ::SHA3_256_CTX) = write(io, "SHA3 256-bit hash state")
show(io::IO, ::SHA3_384_CTX) = write(io, "SHA3 384-bit hash state")
show(io::IO, ::SHA3_512_CTX) = write(io, "SHA3 512-bit hash state")