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
#include "io/stream_reader.h"
#include "nbt_tags.h"
#include <fstream>
#include <sstream>

using namespace nbt;

void test_stream_reader_big()
{
    const char input[] {
        1, //tag_type::Byte
        0, //tag_type::End
        11, //tag_type::Int_Array

        0x0a, 0x0b, 0x0c, 0x0d, //0x0a0b0c0d in Big Endian

        0x00, 0x06, //String length in Big Endian
        'f', 'o', 'o', 'b', 'a', 'r',

        0 //tag_type::End (invalid with allow_end = false)
    };
    std::istringstream is(std::string(input, sizeof input));
    nbt::io::stream_reader reader(is);

    ASSERT(&reader.get_istr() == &is);
    ASSERT(reader.get_endian() == endian::big);

    ASSERT(reader.read_type() == tag_type::Byte);
    ASSERT(reader.read_type(true) == tag_type::End);
    ASSERT(reader.read_type(false) == tag_type::Int_Array);

    int32_t i;
    reader.read_num(i);
    ASSERT(i == 0x0a0b0c0d);

    ASSERT(reader.read_string() == "foobar");

    EXPECT_EXCEPTION(reader.read_type(false), io::stream_reader::input_error);
    ASSERT(!is);
    is.clear();

    //Test for invalid tag type 12
    is.str("\x0c");
    EXPECT_EXCEPTION(reader.read_type(), io::stream_reader::input_error);
    ASSERT(!is);
    is.clear();

    //Test for unexpcted EOF on numbers (input too short for int32_t)
    is.str("\x03\x04");
    reader.read_num(i);
    ASSERT(!is);
}

void test_stream_reader_little()
{
    const char input[] {
        0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, //0x0d0c0b0a09080706 in Little Endian

        0x06, 0x00, //String length in Little Endian
        'f', 'o', 'o', 'b', 'a', 'r',

        0x10, 0x00, //String length (intentionally too large)
        'a', 'b', 'c', 'd' //unexpected EOF
    };
    std::istringstream is(std::string(input, sizeof input));
    nbt::io::stream_reader reader(is, endian::little);

    ASSERT(reader.get_endian() == endian::little);

    int64_t i;
    reader.read_num(i);
    ASSERT(i == 0x0d0c0b0a09080706);

    ASSERT(reader.read_string() == "foobar");

    EXPECT_EXCEPTION(reader.read_string(), io::stream_reader::input_error);
    ASSERT(!is);
}

void test_read_bigtest()
{
    //Uses an extended variant of Notch's original bigtest file
    std::ifstream file("bigtest_uncompr", std::ios::binary);
    ASSERT(file);
    nbt::io::stream_reader reader(file);

    ASSERT(reader.read_type() == tag_type::Compound);
    ASSERT(reader.read_string() == "Level");
    auto tagptr = reader.read_payload(tag_type::Compound);

    ASSERT(tagptr->get_type() == tag_type::Compound);
    const tag_compound& comp = tagptr->as<tag_compound>();

    ASSERT(comp.size() == 13);

    ASSERT(comp.at("byteTest") == tag_byte(127));
    ASSERT(comp.at("shortTest") == tag_short(32767));
    ASSERT(comp.at("intTest") == tag_int(2147483647));
    ASSERT(comp.at("longTest") == tag_long(9223372036854775807));
    ASSERT(comp.at("floatTest") == tag_float(std::stof("0xff1832p-25"))); //0.4982315
    ASSERT(comp.at("doubleTest") == tag_double(std::stod("0x1f8f6bbbff6a5ep-54"))); //0.493128713218231

    //From bigtest.nbt: "the first 1000 values of (n*n*255+n*7)%100, starting with n=0 (0, 62, 34, 16, 8, ...)"
    tag_byte_array byteArrayTest;
    for(int n = 0; n < 1000; ++n)
        byteArrayTest.push_back((n*n*255 + n*7) % 100);
    ASSERT(comp.at("byteArrayTest (the first 1000 values of (n*n*255+n*7)%100, starting with n=0 (0, 62, 34, 16, 8, ...))") == byteArrayTest);

    ASSERT(comp.at("stringTest") == tag_string("HELLO WORLD THIS IS A TEST STRING \u00C5\u00C4\u00D6!"));

    ASSERT(comp.at("listTest (compound)") == tag_list::of<tag_compound>({
        {{"created-on", tag_long(1264099775885)}, {"name", "Compound tag #0"}},
        {{"created-on", tag_long(1264099775885)}, {"name", "Compound tag #1"}}
    }));
    ASSERT(comp.at("listTest (long)") == tag_list::of<tag_long>({11, 12, 13, 14, 15}));
    ASSERT(comp.at("listTest (end)") == tag_list());

    ASSERT((comp.at("nested compound test") == tag_compound{
        {"egg", tag_compound{{"value", 0.5f},  {"name", "Eggbert"}}},
        {"ham", tag_compound{{"value", 0.75f}, {"name", "Hampus"}}}
    }));

    ASSERT(comp.at("intArrayTest") == tag_int_array(
        {0x00010203, 0x04050607, 0x08090a0b, 0x0c0d0e0f}));
}

int main()
{
    test_stream_reader_big();
    test_stream_reader_little();
    test_read_bigtest();
}
