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
#include "io/stream_writer.h"
#include <iostream>
#include <sstream>

using namespace nbt;

void test_stream_writer_big()
{
    std::ostringstream os;
    nbt::io::stream_writer writer(os);

    ASSERT(&writer.get_ostr() == &os);
    ASSERT(writer.get_endian() == endian::big);

    writer.write_type(tag_type::End);
    writer.write_type(tag_type::Long);
    writer.write_type(tag_type::Int_Array);

    writer.write_num(int64_t(0x0102030405060708));

    writer.write_string("foobar");

    ASSERT(os);
    std::string expected{
        0, //tag_type::End
        4, //tag_type::Long
        11, //tag_type::Int_Array

        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, //0x0102030405060708 in Big Endian

        0x00, 0x06, //string length in Big Endian
        'f', 'o', 'o', 'b', 'a', 'r'
    };
    std::string s = os.str();
    ASSERT(os.str() == expected);
    std::clog << "test_stream_writer_big passed" << std::endl;
}

void test_stream_writer_little()
{
    std::ostringstream os;
    nbt::io::stream_writer writer(os, endian::little);

    ASSERT(writer.get_endian() == endian::little);

    writer.write_num(int32_t(0x0a0b0c0d));

    writer.write_string("foobar");

    ASSERT(os);
    std::string expected{
        0x0d, 0x0c, 0x0b, 0x0a, //0x0a0b0c0d in Little Endian

        0x06, 0x00, //string length in Little Endian
        'f', 'o', 'o', 'b', 'a', 'r'
    };
    std::string s = os.str();
    ASSERT(os.str() == expected);
    std::clog << "test_stream_writer_little passed" << std::endl;
}

int main()
{
    test_stream_writer_big();
    test_stream_writer_little();
}
