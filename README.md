**Note: This repository is no longer actively being maintained. The library still works for reading and writing current NBT files, but you might want to refer to one of the more active forks instead, for example [PrismLauncher/libnbtplusplus](https://github.com/PrismLauncher/libnbtplusplus).**

# libnbt++

libnbt++ is a C++ library for reading, writing and manipulating Minecraft's file format Named Binary Tag (NBT).

It also optionally includes simple iostream wrappers for zlib, to allow reading and writing GZip compressed NBT files.

## Building

The library uses CMake for building. Example:

```sh
cd libnbtplusplus
mkdir build
cd build
# configure the build. See below for CMake options.
cmake .. -DCMAKE_INSTALL_PREFIX=install
# build the library
cmake --build .
# optionally run the unit tests
cmake --build . --target test
# install the library and headers
cmake --install . 
```
The following CMake options are available:
- NBT_BUILD_SHARED: Build shared instead of static library. Default OFF
- NBT_NBT_USE_ZLIB: Adds support for the zlib streams. Requires zlib. Default ON
- NBT_BUILD_TESTS: Builds the unit tests. Requires CxxTest. Default ON
