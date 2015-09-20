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
#ifndef OZLIBSTREAM_H_INCLUDED
#define OZLIBSTREAM_H_INCLUDED

#include <ostream>
#include <vector>
#include <zlib.h>

namespace zlib
{

/**
 * @brief Stream buffer used by zlib::ozlibstream
 * @sa ozlibstream
 */
class deflate_streambuf : public std::streambuf
{
public:
    /**
     * @param output the ostream to wrap
     * @param bufsize the size of the internal buffers
     * @param level the compression level, ranges from 0 to 9
     *
     * Refer to the zlib documentation of deflateInit2 for details about the arguments.
     *
     * @throw zlib_error if zlib encounters a problem during initialization
     */
    explicit deflate_streambuf(std::ostream& output, size_t bufsize = 32768, int level = Z_DEFAULT_COMPRESSION, int window_bits = 15, int mem_level = 8, int strategy = Z_DEFAULT_STRATEGY);
    ~deflate_streambuf() noexcept;

    std::ostream& get_ostr() const { return os; }

private:
    std::ostream& os;
    std::vector<char> in;
    std::vector<char> out;
    z_stream zstr;

    void deflate_chunk(int flush = Z_NO_FLUSH);

    int_type overflow(int_type ch) override;
    int sync() override;
};

/**
 * @brief An ostream adapter that compresses data using zlib
 *
 * This ostream wraps another ostream. Data written to an ozlibstream will be
 * deflated (compressed) with zlib and written to the wrapped ostream.
 *
 * @sa deflate_streambuf
 */
class ozlibstream : public std::ostream
{
public:
    /**
     * @param output the ostream to wrap
     * @param level the compression level, ranges from 0 to 9
     * @param gzip if true, the output will be in gzip format rather than zlib
     * @param bufsize the size of the internal buffers
     */
    explicit ozlibstream(std::ostream& output, int level = Z_DEFAULT_COMPRESSION, bool gzip = false, size_t bufsize = 32768):
        std::ostream(&buf), buf(output, bufsize, level, 15 + (gzip ? 16 : 0))
    {}

    ///@return the wrapped ostream
    std::ostream& get_ostr() const { return buf.get_ostr(); }

private:
    deflate_streambuf buf;
};

}

#endif // OZLIBSTREAM_H_INCLUDED
