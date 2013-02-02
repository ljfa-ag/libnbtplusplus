libnbt++ is a free C++ library for Minecraft's file format NBT - Named Binary Tag.
It can read and write compressed and uncompressed NBT files.
It uses streams for input and output.

Dependencies:
libnbt++ requires the following Boost headers:
- Config
- Format
- Iterator

Additionally, if you want to have GZip support (nbt::io::read_gzip and nbt::io::write_gzip):
- Iostreams (must be compiled with Zlib support)

Building:
You need CMake for building.
Set NBT_WITH_GZIP if you want to activate GZip support.
Set NBT_BUILD_NBTTEST if you want to build the nbttest program (requires NBT_WITH_GZIP).

The nbttest program is a simple program which takes a compressed
or uncompressed NBT file as input and prints out the contents in
text form, then optionally writes it back into an output NBT file.
