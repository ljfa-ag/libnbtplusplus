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
#include "tag_primitive.h"
#include <limits>

namespace nbt
{

static_assert(std::numeric_limits<float>::is_iec559 && std::numeric_limits<double>::is_iec559,
    "The floating point values for NBT must conform to IEC 559/IEEE 754");

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
void tag_primitive<T>::set(T val)
{
    value = val;
}

template<class T>
tag_primitive<T>::operator T&()
{
    return value;
}

template<class T>
tag_primitive<T>::operator T() const
{
    return value;
}

template<class T>
T tag_primitive<T>::get() const
{
    return value;
}

template<class T>
bool operator==(const tag_primitive<T>& lhs, const tag_primitive<T>& rhs)
{
    return lhs.get() == rhs.get();
}

template<class T>
bool operator!=(const tag_primitive<T>& lhs, const tag_primitive<T>& rhs)
{
    return !(lhs == rhs);
}

//Enforce template instantiations
template class tag_primitive<int8_t>;
template class tag_primitive<int16_t>;
template class tag_primitive<int32_t>;
template class tag_primitive<int64_t>;
template class tag_primitive<float>;
template class tag_primitive<double>;
//Need to also instantiate operator!=, whereas operator== already gets instantiated in crtp_tag
template bool operator!=<int8_t> (const tag_primitive<int8_t>& , const tag_primitive<int8_t>&);
template bool operator!=<int16_t>(const tag_primitive<int16_t>&, const tag_primitive<int16_t>&);
template bool operator!=<int32_t>(const tag_primitive<int32_t>&, const tag_primitive<int32_t>&);
template bool operator!=<int64_t>(const tag_primitive<int64_t>&, const tag_primitive<int64_t>&);
template bool operator!=<float>  (const tag_primitive<float>&  , const tag_primitive<float>&);
template bool operator!=<double> (const tag_primitive<double>& , const tag_primitive<double>&);

}
