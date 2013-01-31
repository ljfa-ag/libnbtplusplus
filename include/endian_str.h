/*
  endian_str.h - Stream input and output of binary numbers with different
  byte orders.

  Copyright (C) 2013 ljfa-ag

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef ENDIAN_STR_H_INCLUDED
#define ENDIAN_STR_H_INCLUDED

#include <cstdint>
#include <iosfwd>

#if !defined(BOOST_LITTLE_ENDIAN) && !defined(BOOST_BIG_ENDIAN)
    #include <boost/detail/endian.hpp>
#endif

/**
 * \brief Reading and writing numbers from and to streams
 * in binary format with different byte orders.
 */
namespace endian
{

///Read number from stream in native byte order.
void read_native(std::istream& str, uint8_t& x);
void read_native(std::istream& str, uint16_t& x);
void read_native(std::istream& str, uint32_t& x);
void read_native(std::istream& str, uint64_t& x);
void read_native(std::istream& str, int8_t& x);
void read_native(std::istream& str, int16_t& x);
void read_native(std::istream& str, int32_t& x);
void read_native(std::istream& str, int64_t& x);
void read_native(std::istream& str, float& x);
void read_native(std::istream& str, double& x);

///Write number to stream in native byte order.
void write_native(std::ostream& str, uint8_t x);
void write_native(std::ostream& str, uint16_t x);
void write_native(std::ostream& str, uint32_t x);
void write_native(std::ostream& str, uint64_t x);
void write_native(std::ostream& str, int8_t x);
void write_native(std::ostream& str, int16_t x);
void write_native(std::ostream& str, int32_t x);
void write_native(std::ostream& str, int64_t x);
void write_native(std::ostream& str, float x);
void write_native(std::ostream& str, double x);

///Read number from stream in anti-native byte order.
void read_reorder(std::istream& str, uint8_t& x);
void read_reorder(std::istream& str, uint16_t& x);
void read_reorder(std::istream& str, uint32_t& x);
void read_reorder(std::istream& str, uint64_t& x);
void read_reorder(std::istream& str, int8_t& x);
void read_reorder(std::istream& str, int16_t& x);
void read_reorder(std::istream& str, int32_t& x);
void read_reorder(std::istream& str, int64_t& x);
void read_reorder(std::istream& str, float& x);
void read_reorder(std::istream& str, double& x);

///Write number to stream in anti-native byte order.
void write_reorder(std::ostream& str, uint8_t x);
void write_reorder(std::ostream& str, uint16_t x);
void write_reorder(std::ostream& str, uint32_t x);
void write_reorder(std::ostream& str, uint64_t x);
void write_reorder(std::ostream& str, int8_t x);
void write_reorder(std::ostream& str, int16_t x);
void write_reorder(std::ostream& str, int32_t x);
void write_reorder(std::ostream& str, int64_t x);
void write_reorder(std::ostream& str, float x);
void write_reorder(std::ostream& str, double x);

///Read number from stream in big endian.
template<class T> void read_big(std::istream& str, T& x);
///Read number from stream in little endian.
template<class T> void read_little(std::istream& str, T& x);
///Write number to stream in big endian.
template<class T> void write_big(std::ostream& str, T x);
///Write number to stream in little endian.
template<class T> void write_little(std::ostream& str, T x);

#if defined(BOOST_LITTLE_ENDIAN)

template<class T> inline void read_big(std::istream& str, T& x) { read_reorder(str, x); }
template<class T> inline void read_little(std::istream& str, T& x) { read_native(str, x); }

template<class T> inline void write_big(std::ostream& str, T x) { write_reorder(str, x); }
template<class T> inline void write_little(std::ostream& str, T x) { write_native(str, x); }

#elif defined(BOOST_BIG_ENDIAN)

template<class T> inline void read_big(std::istream& str, T& x) { read_native(str, x); }
template<class T> inline void read_little(std::istream& str, T& x) { read_reorder(str, x); }

template<class T> inline void write_big(std::ostream& str, T x) { write_native(str, x); }
template<class T> inline void write_little(std::ostream& str, T x) { write_reorder(str, x); }

#endif

}

#endif // ENDIAN_STR_H_INCLUDED
