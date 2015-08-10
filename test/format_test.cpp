/*
 * libnbt++ - A library for the Minecraft Named Binary Tag format.
 * Copyright (C) 2013, 2015  ljfa-ag
 *
 * This file is part of libnbt++.
 *
 * libnbt++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libnbt++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libnbt++.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "microtest.h"
//#include "text/json_formatter.h"
#include "io/stream_reader.h"
#include <fstream>
#include <iostream>
#include "nbt_tags.h"

using namespace nbt;

int main()
{
    std::ifstream file("bigtest_uncompr", std::ios::binary);
    ASSERT(file);
    std::string key;
    std::unique_ptr<tag_compound> comp;
    std::tie(key, comp) = io::stream_reader(file).read_compound();

    std::cout << "----- default operator<<:\n";
    std::cout << *comp;
    std::cout << "\n-----" << std::endl;
}
