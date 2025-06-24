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

Note: By default, the header files are directly installed inside the "include" subdirectory of the install prefix. You might want to choose a different
path by using the CMAKE_INSTALL_INCLUDEDIR option. In this case, you will need to add this path as include path when using the library.

## Usage example

```c++
#include <iostream>
#include <fstream>
#include "nbt_tags.h"
#include "io/stream_reader.h"
#include "io/stream_writer.h"
#include "io/izlibstream.h"
#include "io/ozlibstream.h"

// open a compressed NBT file as a binary stream and wrap it inside a zlib stream
std::ifstream file_str{"level.dat", std::ios::binary};
zlib::izlibstream zlib_str{file_str};

// read the named tag from the file
auto [name, tag_ptr] = nbt::io::read_tag(zlib_str);
// name: std::string
// tag_ptr: std::unique_ptr<nbt::tag>
// the tag_ptr can be wrapped inside a value object to be able to access it conveniently
nbt::value tag{std::move(tag_ptr)};

// for example, to acccess the item ID of the first item in the player's inventory, you can chain the "at" method and
// explicitly convert the resulting nbt::value to a string:
auto item_id = std::string(tag.at("Data").at("Player").at("Inventory").at(0).at("id"));
std::cout << item_id << std::endl; //might print minecraft:lever

// the NBT data can also be manipulated:
tag["foo"] = "a string";
tag["bar"] = nbt::tag_compound{{"a", "compound"}, {"b", 42}};

std::cout << tag << std::endl; //prints the tag in a JSON-like format
// Note: the library has no support for SNBT

// to write the NBT data into a compressed file, wrap an output stream inside a zlib stream
std::ofstream ofile_str{"out.nbt", std::ios::binary};
zlib::ozlibstream ozlib_str{ofile_str, -1, true}; //-1 for default compression level, true for GZip rather than zlib compression
// write the named tag
nbt::io::write_tag(name, tag, ozlib_str);
```

The header files are documented using Doxygen comments, refer to them for more information on usage.
