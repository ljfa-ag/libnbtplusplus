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
#ifndef TAG_PRIMITIVE_H_INCLUDED
#define TAG_PRIMITIVE_H_INCLUDED

#include "tag.h"
#include "primitive_detail.h"
#include <type_traits>

namespace nbt
{

/**
 * @brief Contains an integral or floating-point value.
 *
 * Common class for tag_byte, tag_short, tag_int, tag_long, tag_float and tag_double.
 */
template<class T>
class tag_primitive : public tag
{
public:
    ///The type of the value
    typedef T value_type;

    ///The type of the tag
    static constexpr tag_type type = detail::get_primitive_type<T>::value;

    tag_primitive(T value = 0);

    tag_primitive& operator=(T value);

    operator T() const;

    tag_type get_type() const noexcept override;

private:
    T value;
};

//Typedefs that should be used instead of the template tag_primitive.
typedef tag_primitive<int8_t> tag_byte;
typedef tag_primitive<int16_t> tag_short;
typedef tag_primitive<int32_t> tag_int;
typedef tag_primitive<int64_t> tag_long;
typedef tag_primitive<float> tag_float;
typedef tag_primitive<double> tag_double;

template<class T>
tag_primitive<T>::tag_primitive(T val):
    value(val)
{}

template<class T>
tag_primitive<T>& tag_primitive<T>::operator=(T val)
{
    value = val;
    return *this;
}

template<class T>
tag_primitive<T>::operator T() const
{
    return value;
}

template<class T>
tag_type tag_primitive<T>::get_type() const noexcept
{
    return type;
}

}

#endif // TAG_PRIMITIVE_H_INCLUDED
