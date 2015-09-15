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
#include "io/zlib_error.h"
#include <fstream>
#include <sstream>

using namespace zlib;

class zlibstream_test : public CxxTest::TestSuite
{
private:
    std::stringbuf bigtest;

public:
    zlibstream_test()
    {
        std::ifstream bigtest_f("bigtest_uncompr", std::ios::binary);
        bigtest_f >> &bigtest;
        if(!bigtest_f || bigtest.str().size() == 0)
            throw std::runtime_error("Could not read bigtest_uncompr file");
    }

    void test_inflate_gzip()
    {
        std::ifstream gzip_in("bigtest.nbt", std::ios::binary);
        TS_ASSERT(gzip_in);

        std::stringbuf data;
        //Small buffer so not all fits at once (the compressed file is 561 bytes)
        {
            izlibstream igzs(gzip_in, 256);
            igzs.exceptions(std::ios::failbit);
            TS_ASSERT(igzs.good());

            TS_ASSERT_THROWS_NOTHING(igzs >> &data);
            TS_ASSERT(igzs);
            TS_ASSERT(igzs.eof());
            TS_ASSERT_EQUALS(data.str(), bigtest.str());
        }

        //Clear and reuse buffers
        data.str("");
        gzip_in.clear();
        gzip_in.seekg(0);
        //Now try the same with larger buffer (but not large enough for all output, uncompressed size 1561 bytes)
        {
            izlibstream igzs(gzip_in, 1000);
            igzs.exceptions(std::ios::failbit);
            TS_ASSERT(igzs.good());

            TS_ASSERT_THROWS_NOTHING(igzs >> &data);
            TS_ASSERT(igzs);
            TS_ASSERT(igzs.eof());
            TS_ASSERT_EQUALS(data.str(), bigtest.str());
        }

        data.str("");
        gzip_in.clear();
        gzip_in.seekg(0);
        //Now with large buffer
        {
            izlibstream igzs(gzip_in, 4000);
            igzs.exceptions(std::ios::failbit);
            TS_ASSERT(igzs.good());

            TS_ASSERT_THROWS_NOTHING(igzs >> &data);
            TS_ASSERT(igzs);
            TS_ASSERT(igzs.eof());
            TS_ASSERT_EQUALS(data.str(), bigtest.str());
        }
    }

    void test_inflate_zlib()
    {
        std::ifstream zlib_in("bigtest.zlib", std::ios::binary);
        TS_ASSERT(zlib_in);

        std::stringbuf data;
        izlibstream izls(zlib_in, 256);
        izls.exceptions(std::ios::failbit);
        TS_ASSERT(izls.good());

        TS_ASSERT_THROWS_NOTHING(izls >> &data);
        TS_ASSERT(izls);
        TS_ASSERT(izls.eof());
        TS_ASSERT_EQUALS(data.str(), bigtest.str());
    }

    void test_inflate_corrupt()
    {
        std::ifstream gzip_in("bigtest_corrupt.nbt", std::ios::binary);
        TS_ASSERT(gzip_in);

        std::stringbuf data;
        {
            izlibstream igzs(gzip_in);
            igzs.exceptions(std::ios::failbit);
            TS_ASSERT_THROWS(igzs >> &data, zlib_error);
        }

        gzip_in.close();
        gzip_in.open("bigtest_eof.nbt", std::ios::binary);
        TS_ASSERT(gzip_in);

        data.str("");
        {
            izlibstream igzs(gzip_in);
            igzs.exceptions(std::ios::failbit);
            TS_ASSERT_THROWS(igzs >> &data, zlib_error);
        }
    }
};
