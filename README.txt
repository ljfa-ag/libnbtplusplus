libnbt++ is a free C++ library for Minecraft's file format NBT - Named Binary Tag.
It can read and write compressed and uncompressed NBT files.
It uses streams for input and output.

The nbttest program is a simple program which takes a compressed
or uncompressed NBT file as input and prints out the contents in
text form, then optionally writes it back into an output NBT file.

Dependencies:
libnbt++ requires the following Boost headers:
- Config
- Format
- Iterator
Additionally, if you want to have GZip support:
- Iostreams (must be compiled with Zlib support)

Building:
You need CMake for building.
Set NBT_IOSTREAMS_HAS_ZLIB if your Boost.Iostreams library was built with Zlib support.
Otherwise, the functions nbt::io::read_gzip and nbt::io::write_gzip will not be available
and nbttest will not be built.
