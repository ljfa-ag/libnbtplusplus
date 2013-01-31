/*
    libnbt++ - A library for the Minecraft Named Binary Tag format.
    Copyright (C) 2013 ljfa-ag

    This file is part of libnbt++.

    libnbt++ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libnbt++ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libnbt++.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "tag.h"
#include "nbt_io.h"

#include <fstream>
#include <iostream>
#include <cstring>

int main(int argc, const char* const* argv)
{
    if(argc < 2)
    {
        std::cerr << "Usage: nbttest input [output]" << std::endl;
        return 1;
    }

    const char* filename = argv[1];
    std::ifstream file(filename, std::ios::binary);

    if(!file)
    {
        std::cerr << "Error opening file \"" << filename << "\"." << std::endl;
        return 2;
    }

    int magic_num = file.peek();
    bool uncompressed;

    if(magic_num == 0x1F) //First byte of a gzip file
        uncompressed = false;
    else if(magic_num == 0x0A) //First byte of an uncompressed NBT file
        uncompressed = true;
    else
    {
        std::cerr << "Invalid file format of \"" << filename << "\"." << std::endl;
        return 2;
    }

    std::string key;
    std::unique_ptr<nbt::tag> tp;
    try
    {
        if(uncompressed)
            tp = nbt::io::read(file, key);
        else
            tp = nbt::io::read_gzip(file, key);
    }
    catch(std::exception& ex)
    {
        std::cerr << "Error reading file \"" << filename << "\": " << ex.what() << std::endl;
        return 3;
    }

    file.close();

    std::cout << "Contents of ";
    if(uncompressed)
        std::cout << "uncompressed ";
    std::cout << "NBT file \"" << filename << "\":\n\n\"" << key << "\" -> " << *tp << std::endl;

    if(argc < 3)
        return 0;

    const char* output = argv[2];

    std::ofstream outf(output, std::ios::binary);

    nbt::io::write_gzip(outf, key, *tp);
    std::cout << "\nOutput written to \"" << output << "\"." << std::endl;
    return 0;
}
