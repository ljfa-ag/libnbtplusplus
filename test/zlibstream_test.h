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
#include <cxxtest/TestSuite.h>
#include "io/izlibstream.h"
#include "io/ozlibstream.h"
#include <fstream>
#include <sstream>

using namespace zlib;

class zlibstream_test : public CxxTest::TestSuite
{
public:
    void test_izlibstream()
    {
        std::ifstream gzip_in("bigtest.nbt", std::ios::binary);
        std::ifstream expected_in("bigtest_uncompr", std::ios::binary);
        std::stringbuf expected;
        expected_in >> &expected; //Dump uncompressed file contents into streambuf
        TS_ASSERT(gzip_in && expected_in);
        TS_ASSERT_DIFFERS(expected.str().size(), 0u);
        expected_in.close();

        izlibstream igzs(gzip_in, 256); //Small buffer so not all fits at once (the compressed file is 561 bytes)
        TS_ASSERT(igzs.good());
        TS_ASSERT(!igzs.eof());

        std::stringbuf data;
        igzs >> &data;
        TS_ASSERT(igzs);
        TS_ASSERT(igzs.eof());
        TS_ASSERT_EQUALS(data.str(), expected.str());
    }
};
