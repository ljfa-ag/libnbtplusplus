libnbt++ is a free C++ library for Minecraft's file format NBT - Named Binary Tag.
It can read and write compressed and uncompressed NBT files.
It uses streams for input and output.

libnbt++ depends on Boost. The following Boost libraries are needed:
- Config
- Format
- Iostreams (must be compiled with Zlib support)
- Iterator

The test program is a simple program which takes a compressed
or uncompressed NBT file as input and prints out the contents,
then optionally writes it back into an output NBT file.

To build, open the makefile with a text editor and adjust the defines.