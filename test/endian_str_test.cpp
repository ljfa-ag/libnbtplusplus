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
#include "endian_str.h"
#include <cstdlib>
#include <sstream>

using namespace endian;

void test_uint()
{
    std::stringstream str(std::ios::in | std::ios::out | std::ios::binary);

    write_little(str, uint8_t (0x01));
    write_little(str, uint16_t(0x0102));
    write_little(str, uint32_t(0x01020304UL));
    write_little(str, uint64_t(0x0102030405060708ULL));

    write_big   (str, uint8_t (0x09));
    write_big   (str, uint16_t(0x090A));
    write_big   (str, uint32_t(0x090A0B0CUL));
    write_big   (str, uint64_t(0x090A0B0C0D0E0F10ULL));

    const char expected[] = {
        1,
        2, 1,
        4, 3, 2, 1,
        8, 7, 6, 5, 4, 3, 2, 1,

        9,
        9, 10,
        9, 10, 11, 12,
        9, 10, 11, 12, 13, 14, 15, 16,
        0}; //Null terminator
    ASSERT(str.str() == expected);

    uint8_t  u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;

    read_little(str, u8);
    ASSERT(u8 == 0x01);
    read_little(str, u16);
    ASSERT(u16 == 0x0102);
    read_little(str, u32);
    ASSERT(u32 == 0x01020304UL);
    read_little(str, u64);
    ASSERT(u64 == 0x0102030405060708ULL);

    read_big(str, u8);
    ASSERT(u8 == 0x09);
    read_big(str, u16);
    ASSERT(u16 == 0x090A);
    read_big(str, u32);
    ASSERT(u32 == 0x090A0B0CUL);
    read_big(str, u64);
    ASSERT(u64 == 0x090A0B0C0D0E0F10ULL);

    ASSERT(str); //Check if stream has failed
}

void test_sint()
{
    std::stringstream str(std::ios::in | std::ios::out | std::ios::binary);

    write_little(str, int8_t (-0x01));
    write_little(str, int16_t(-0x0102));
    write_little(str, int32_t(-0x01020304L));
    write_little(str, int64_t(-0x0102030405060708LL));

    write_big   (str, int8_t (-0x09));
    write_big   (str, int16_t(-0x090A));
    write_big   (str, int32_t(-0x090A0B0CL));
    write_big   (str, int64_t(-0x090A0B0C0D0E0F10LL));

    const char expected[] = { //meh, stupid narrowing conversions
        '\xFF',
        '\xFE', '\xFE',
        '\xFC', '\xFC', '\xFD', '\xFE',
        '\xF8', '\xF8', '\xF9', '\xFA', '\xFB', '\xFC', '\xFD', '\xFE',

        '\xF7',
        '\xF6', '\xF6',
        '\xF6', '\xF5', '\xF4', '\xF4',
        '\xF6', '\xF5', '\xF4', '\xF3', '\xF2', '\xF1', '\xF0', '\xF0',
        0}; //Null terminator
    ASSERT(str.str() == expected);

    int8_t  i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;

    read_little(str, i8);
    ASSERT(i8 == -0x01);
    read_little(str, i16);
    ASSERT(i16 == -0x0102);
    read_little(str, i32);
    ASSERT(i32 == -0x01020304L);
    read_little(str, i64);
    ASSERT(i64 == -0x0102030405060708LL);

    read_big(str, i8);
    ASSERT(i8 == -0x09);
    read_big(str, i16);
    ASSERT(i16 == -0x090A);
    read_big(str, i32);
    ASSERT(i32 == -0x090A0B0CL);
    read_big(str, i64);
    ASSERT(i64 == -0x090A0B0C0D0E0F10LL);

    ASSERT(str); //Check if stream has failed
}

void test_float()
{
    std::stringstream str(std::ios::in | std::ios::out | std::ios::binary);

    //C99 has hexadecimal floating point literals, C++ doesn't...
    const float fconst = strtof("-0xCDEF01p-63", nullptr); //-1.46325e-012
    const double dconst = strtod("-0x1DEF0102030405p-375", nullptr); //-1.09484e-097
    //We will be assuming IEEE 754 here

    write_little(str, fconst);
    write_little(str, dconst);
    write_big   (str, fconst);
    write_big   (str, dconst);

    const char expected[] = {
        '\x01', '\xEF', '\xCD', '\xAB',
        '\x05', '\x04', '\x03', '\x02', '\x01', '\xEF', '\xCD', '\xAB',

        '\xAB', '\xCD', '\xEF', '\x01',
        '\xAB', '\xCD', '\xEF', '\x01', '\x02', '\x03', '\x04', '\x05',
        0}; //Null terminator
    ASSERT(str.str() == expected);

    float f;
    double d;

    read_little(str, f);
    ASSERT(f == fconst);
    read_little(str, d);
    ASSERT(d == dconst);

    read_big(str, f);
    ASSERT(f == fconst);
    read_big(str, d);
    ASSERT(d == dconst);

    ASSERT(str); //Check if stream has failed
}

int main()
{
    test_uint();
    test_sint();
    test_float();
}
