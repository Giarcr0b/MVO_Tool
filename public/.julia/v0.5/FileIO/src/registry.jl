### Simple cases

# data formats
add_format(format"JLD", "Julia data file (HDF5)", ".jld", [:JLD])

# test for RD?2 magic sequence at the beginning of R data input stream
function detect_rdata(io)
    seekstart(io)
    read(io, UInt8) == UInt8('R') &&
    read(io, UInt8) == UInt8('D') &&
    read(io, UInt8) in (UInt8('A'), UInt8('B'), UInt8('X')) &&
    read(io, UInt8) == UInt8('2') &&
    (c = read(io, UInt8); c == UInt8('\n') || (c == UInt8('\r') && read(io, UInt8) == UInt8('\n')))
end

add_format(format"RData", detect_rdata, [".rda", ".RData", ".rdata"], [:RData, LOAD])

# Image formats
add_format(format"PBMBinary", b"P4", ".pbm", [:ImageMagick])
add_format(format"PGMBinary", b"P5", ".pgm", [:Netpbm])
add_format(format"PPMBinary", b"P6", ".ppm", [:Netpbm])
add_format(format"PBMText",   b"P1", ".pbm", [:ImageMagick, LOAD])
add_format(format"PGMText",   b"P2", ".pgm", [:ImageMagick, LOAD])
add_format(format"PPMText",   b"P3", ".ppm", [:ImageMagick, LOAD])

add_format(format"NRRD", "NRRD", [".nrrd", ".nhdr"], [:NRRD])

add_format(format"AndorSIF", "Andor Technology Multi-Channel File", ".sif", [:AndorSIF, LOAD])


add_format(format"CRW", UInt8[0x49,0x49,0x1a,0x00,0x00,0x00,0x48,0x45], ".crw", [:ImageMagick])
add_format(format"CUR", UInt8[0x00,0x00,0x02,0x00],                     ".cur", [:ImageMagick])
add_format(format"DCX", UInt8[0xb1,0x68,0xde,0x3a],                     ".dcx", [:ImageMagick])
add_format(format"DOT", UInt8[0xd0,0xcf,0x11,0xe0,0xa1,0xb1,0x1a,0xe1], ".dot", [:ImageMagick])
add_format(format"EPS", UInt8[0x25,0x21,0x50,0x53,0x2d,0x41,0x64,0x6f], ".eps", [:ImageMagick])
add_format(format"HDR", UInt8[0x23,0x3f,0x52,0x41,0x44,0x49,0x41,0x4e], ".hdr", [:ImageMagick])
add_format(format"ICO", UInt8[0x00,0x00,0x01,0x00],                     ".ico", [:ImageMagick])
add_format(format"INFO", UInt8[0x7a,0x62,0x65,0x78],                    ".info",[:ImageMagick])
add_format(format"JP2", UInt8[0x00,0x00,0x00,0x0c,0x6a,0x50,0x20,0x20], ".jp2", [:ImageMagick])
add_format(format"PCX", UInt8[0x0a,0x05,0x01,0x01],                     ".pcx", [:ImageMagick])
add_format(format"PDB", UInt8[0x73,0x7a,0x65,0x7a],                     ".pdb", [:ImageMagick])
add_format(format"PDF", UInt8[0x25,0x50,0x44,0x46],                     ".pdf", [:ImageMagick])
add_format(format"PGM", UInt8[0x50,0x35,0x0a],                          ".pgm", [:ImageMagick])
add_format(format"PSD", UInt8[0x38,0x42,0x50,0x53],                     ".psd", [:ImageMagick])
add_format(format"RGB", UInt8[0x01,0xda,0x01,0x01,0x00,0x03],           ".rgb", [:ImageMagick])
add_format(format"WMF", UInt8[0xd7,0xcd,0xc6,0x9a],                     ".wmf", [:ImageMagick])
add_format(format"WPG", UInt8[0xff,0x57,0x50,0x43],                     ".wpg", [:ImageMagick])
add_format(format"Imagine", "IMAGINE",                                  ".imagine", [:ImagineFormat])

add_format(
    format"TGA",
    (),
    ".tga",
    [:QuartzImageIO, OSX],
    [:ImageMagick]
)
add_format(
    format"GIF",
    UInt8[0x47,0x49,0x46,0x38],
    ".gif",
    [:QuartzImageIO, OSX],
    [:ImageMagick]
)
add_format(
    format"PNG",
    UInt8[0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a],
    ".png",
    [:QuartzImageIO, OSX],
    [:ImageMagick]
)
add_format(
    format"TIFF",
    (UInt8[0x4d,0x4d,0x00,0x2a], UInt8[0x4d,0x4d,0x00,0x2b], UInt8[0x49,0x49,0x2a,0x00],UInt8[0x49,0x49,0x2b,0x00]),
    [".tiff", ".tif"],
    [:QuartzImageIO, OSX],
    [:ImageMagick]
)
add_format(
    format"JPEG",
    UInt8[0xff,0xd8,0xff],
    [".jpeg", ".jpg", ".JPG"],
    [:QuartzImageIO, OSX],
    [:ImageMagick]
) # 0xe1
add_format(
    format"BMP",
    UInt8[0x42,0x4d],
    ".bmp",
    [:QuartzImageIO, OSX],
    [:ImageMagick]
)

#=
add_format(format"NPY", UInt8[0x93, 'N', 'U', 'M', 'P', 'Y'], ".npy")
add_loader(format"NPZ", :NPZ)
add_saver(format"NPZ", :NPZ)

add_format(format"ZIP", [0x50,0x4b,0x03,0x04], ".zip")
add_loader(format"ZIP", :ZipeFile)
add_saver(format"ZIP", :ZipeFile)
=#

#Shader files
add_format(format"GLSLShader", (), [".frag", ".vert", ".geom", ".comp"], [:GLAbstraction])

# Mesh formats
add_format(format"OBJ", (), ".obj", [:MeshIO])
add_format(format"PLY_ASCII", "ply\nformat ascii 1.0", ".ply", [:MeshIO])
add_format(format"PLY_BINARY", "ply\nformat binary_little_endian 1.0", ".ply", [:MeshIO])
add_format(format"2DM", "MESH2D", ".2dm", [:MeshIO])
add_format(format"OFF", "OFF", ".off", [:MeshIO])

# GSLIB/SGeMS format (http://gslib.com)
add_format(format"GSLIB", (), [".gslib",".sgems"], [:GslibIO])

### Audio formats
function detectwav(io)
    seekstart(io)
    magic = read(io, UInt8, 4)
    magic == b"RIFF" || return false
    seek(io, 8)
    submagic = read(io, UInt8, 4)

    submagic == b"WAVE"
end
add_format(format"WAV", detectwav, ".wav", [:WAV])
add_format(format"FLAC","fLaC",".flac",[:FLAC])


### Complex cases

# AVI is a subtype of RIFF, as is WAV
function detectavi(io)
    seekstart(io)
    magic = read(io, UInt8, 4)
    magic == b"RIFF" || return false
    seek(io, 8)
    submagic = read(io, UInt8, 4)

    submagic == b"AVI "
end
add_format(format"AVI", detectavi, ".avi", [:ImageMagick])

# HDF5: the complication is that the magic bytes may start at
# 0, 512, 1024, 2048, or any multiple of 2 thereafter
h5magic = (0x89,0x48,0x44,0x46,0x0d,0x0a,0x1a,0x0a)
function detecthdf5(io)
    position(io) == 0 || return false
    seekend(io)
    len = position(io)
    seekstart(io)
    magic = Vector{UInt8}(length(h5magic))
    pos = position(io)
    while pos+length(h5magic) <= len
        read!(io, magic)
        if iter_eq(magic, h5magic)
            return true
        end
        pos = pos == 0 ? 512 : 2*pos
        if pos < len
            seek(io, pos)
        end
    end
    false
end
add_format(format"HDF5", detecthdf5, [".h5", ".hdf5"], [:HDF5])

function detect_stlascii(io)
    try
        position(io) != 0 && (seekstart(io); return false)
        seekend(io)
        len = position(io)
        seekstart(io)
        len < 80 && return false
        header = read(io, 80) # skip header
        seekstart(io)
        header[1:6] == b"solid " && !detect_stlbinary(io)
    finally
        seekstart(io)
    end
end

function detect_stlbinary(io)
    const size_header = 80+sizeof(UInt32)
    const size_triangleblock = (4*3*sizeof(Float32)) + sizeof(UInt16)

    position(io) != 0 && (seekstart(io); return false)
    seekend(io)
    len = position(io)
    seekstart(io)
    len < size_header && return false

    skip(io, 80) # skip header
    number_of_triangle_blocks = read(io, UInt32)
     #1 normal, 3 vertices in Float32 + attrib count, usually 0
    len != (number_of_triangle_blocks*size_triangleblock)+size_header && (seekstart(io); return false)
    skip(io, number_of_triangle_blocks*size_triangleblock-sizeof(UInt16))
    attrib_byte_count = read(io, UInt16) # read last attrib_byte
    attrib_byte_count != zero(UInt16) && (seekstart(io); return false) # should be zero as not used
    result = eof(io) # if end of file, we have a stl!
    seekstart(io)
    return result
end
add_format(format"STL_ASCII", detect_stlascii, [".stl", ".STL"], [:MeshIO])
add_format(format"STL_BINARY", detect_stlbinary, [".stl", ".STL"], [:MeshIO])

add_format(format"ABAQUS_INP", (), [".inp"], [:MeshIO])
