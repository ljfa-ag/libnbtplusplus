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

#ifndef TAG_SCALAR_H_INCLUDED
#define TAG_SCALAR_H_INCLUDED

#include "endian_str.h"
#include "tag_base.h"

#include <type_traits>

namespace nbt
{

namespace detail //Forward declaration.
{ template<class S> struct get_scalar_type; }

/**
 * \brief Contains an integral or floating-point number.
 *
 * Common class for tag_byte, tag_short, tag_int, tag_long, tag_float and tag_double.
 */
template<class S> class tag_scalar : public tag
{
public:
    ///The type of the value.
    typedef S value_type;

    ///The type of the tag.
    static constexpr tag_type type = detail::get_scalar_type<S>::value;

    ///Scalar constructor
    explicit tag_scalar(S val = 0): value(val) {}

    tag_type get_type() const noexcept { return type; }

    void print(std::ostream& os) const;

    value_type value;

protected:
    void write_payload(std::ostream& os) const
    { endian::write_big(os, value); }
};

//Typedefs that should be used instead of the template tag_scalar.
typedef tag_scalar<int8_t> tag_byte;
typedef tag_scalar<int16_t> tag_short;
typedef tag_scalar<int32_t> tag_int;
typedef tag_scalar<int64_t> tag_long;
typedef tag_scalar<float> tag_float;
typedef tag_scalar<double> tag_double;

namespace detail
{

    template<> struct get_scalar_type<int8_t>  : std::integral_constant<tag::tag_type, tag::tag_type::_byte> {};
    template<> struct get_scalar_type<int16_t> : std::integral_constant<tag::tag_type, tag::tag_type::_short> {};
    template<> struct get_scalar_type<int32_t> : std::integral_constant<tag::tag_type, tag::tag_type::_int> {};
    template<> struct get_scalar_type<int64_t> : std::integral_constant<tag::tag_type, tag::tag_type::_long> {};
    template<> struct get_scalar_type<float>   : std::integral_constant<tag::tag_type, tag::tag_type::_float> {};
    template<> struct get_scalar_type<double>  : std::integral_constant<tag::tag_type, tag::tag_type::_double> {};

}

template<class S> inline void tag_scalar<S>::print(std::ostream& os) const
{ os << type << '(' << value << ')'; }

//Specialization for tag_byte, so a number is printed into the stream and not a character.
template<> inline void tag_scalar<int8_t>::print(std::ostream& os) const
{ os << "byte(" << static_cast<int>(value) << ')'; }

}

#endif // TAG_SCALAR_H_INCLUDED
