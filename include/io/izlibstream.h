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
#ifndef IZLIBSTREAM_H_INCLUDED
#define IZLIBSTREAM_H_INCLUDED

#include <istream>
#include <vector>
#include <zlib.h>

namespace zlib
{

/**
 * @brief Stream buffer used by zlib::izlibstream
 * @see izlibstream
 */
class inflate_streambuf : public std::streambuf
{
public:
    explicit inflate_streambuf(std::istream& input, size_t bufsize = 32768, int window_bits = 32);
    ~inflate_streambuf() noexcept;

    //No copying or moving
    inflate_streambuf(const inflate_streambuf&) = delete;
    inflate_streambuf& operator=(const inflate_streambuf&) = delete;

    std::istream& get_istr() const { return is; }

private:
    std::istream& is;
    std::vector<char> in;
    std::vector<char> out;
    z_stream zstr;
};

/**
 * @brief An istream adapter that decompresses data using zlib
 *
 * This istream wraps another istream. The izlibstream will read compressed
 * data from the wrapped istream and inflate (decompress) it with zlib.
 */
class izlibstream : public std::istream
{
public:
    /**
     * @param input the istream to wrap
     * @param bufsize the size of the internal buffer
     */
    explicit izlibstream(std::istream& input, size_t bufsize = 32768):
        buf(input, bufsize)
    {
        init(&buf);
    }
    ///@return the wrapped istream
    std::istream& get_istr() const { return buf.get_istr(); }

private:
    inflate_streambuf buf;
};

}

#endif // IZLIBSTREAM_H_INCLUDED
