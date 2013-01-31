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

#ifndef NBT_IO_H_INCLUDED
#define NBT_IO_H_INCLUDED

#include "tag_base.h"

#include <memory>

namespace nbt
{

///Stream input and output of binary NBT data
namespace io
{

/**
 * \brief Reads a named tag in uncompressed NBT format from stream.
 * \param is The stream to read from.
 * \param[out] key A string object to read the name into.
 * \return A \c unique_ptr to the tag object.
 * \throw input_error if an error occurs while reading, i.e. end of file or a syntax error
 * \sa read_gzip()
 */
std::unique_ptr<tag> read(std::istream& is, std::string& key);

/**
 * \brief Writes a named tag in uncompressed NBT format into stream.
 * \param os The stream to write the data to.
 * \param key The key of the root tag.
 * \param t The tag to write. Should be a tag_compound.
 * \sa write_gzip()
 */
void write(std::ostream& os, const std::string& key, const tag& t);

/**
 * \brief Reads a named tag in GZip-compressed NBT format from stream.
 * \param is The stream to read from.
 * \param[out] key A string object to read the name into.
 * \return A \c unique_ptr to the tag object.
 * \throw input_error if an error occurs while reading, i.e. end of file or a syntax error
 * \sa read()
 */
std::unique_ptr<tag> read_gzip(std::istream& is, std::string& key);

/**
 * \brief Writes a named tag in GZip-compressed NBT format into stream.
 * \param os The stream to write the compressed data to.
 * \param key The key of the root tag.
 * \param t The tag to write. Should be a tag_compound.
 * \param compression_level The GZip compression level. Must be a number between 0 and 9:
 * 0 gives no compression, 1 wekaest and 9 strongest compression.
 * \sa write()
 */
void write_gzip(std::ostream& os, const std::string& key, const tag& t, int compression_level = -1);

}
}

#endif // NBT_IO_H_INCLUDED
