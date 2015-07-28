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
#ifndef ENDIAN_STR_H_INCLUDED
#define ENDIAN_STR_H_INCLUDED

#include <cstdint>
#include <iosfwd>

/**
 * @brief Reading and writing numbers from and to streams
 * in binary format with different byte orders.
 */
namespace endian
{

///Reads number from stream in little endian
void read_little(std::istream& str, uint8_t& x);
void read_little(std::istream& str, uint16_t& x);
void read_little(std::istream& str, uint32_t& x);
void read_little(std::istream& str, uint64_t& x);
void read_little(std::istream& str, int8_t& x);
void read_little(std::istream& str, int16_t& x);
void read_little(std::istream& str, int32_t& x);
void read_little(std::istream& str, int64_t& x);
void read_little(std::istream& str, float& x);
void read_little(std::istream& str, double& x);

///Writes number to stream in little endian
void write_little(std::ostream& str, uint8_t x);
void write_little(std::ostream& str, uint16_t x);
void write_little(std::ostream& str, uint32_t x);
void write_little(std::ostream& str, uint64_t x);
void write_little(std::ostream& str, int8_t x);
void write_little(std::ostream& str, int16_t x);
void write_little(std::ostream& str, int32_t x);
void write_little(std::ostream& str, int64_t x);
void write_little(std::ostream& str, float x);
void write_little(std::ostream& str, double x);

///Reads number from stream in big endian
void read_big(std::istream& str, uint8_t& x);
void read_big(std::istream& str, uint16_t& x);
void read_big(std::istream& str, uint32_t& x);
void read_big(std::istream& str, uint64_t& x);
void read_big(std::istream& str, int8_t& x);
void read_big(std::istream& str, int16_t& x);
void read_big(std::istream& str, int32_t& x);
void read_big(std::istream& str, int64_t& x);
void read_big(std::istream& str, float& x);
void read_big(std::istream& str, double& x);

///Writes number to stream in big endian
void write_big(std::ostream& str, uint8_t x);
void write_big(std::ostream& str, uint16_t x);
void write_big(std::ostream& str, uint32_t x);
void write_big(std::ostream& str, uint64_t x);
void write_big(std::ostream& str, int8_t x);
void write_big(std::ostream& str, int16_t x);
void write_big(std::ostream& str, int32_t x);
void write_big(std::ostream& str, int64_t x);
void write_big(std::ostream& str, float x);
void write_big(std::ostream& str, double x);

}

#endif // ENDIAN_STR_H_INCLUDED
