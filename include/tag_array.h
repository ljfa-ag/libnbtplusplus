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
#ifndef TAG_ARRAY_H_INCLUDED
#define TAG_ARRAY_H_INCLUDED

#include "crtp_tag.h"

namespace nbt
{

/**
 * @brief Tag that contains an array of byte or int values
 *
 * Common class for tag_byte_array and tag_int_array.
 */
template<class T>
class tag_array final : public detail::crtp_tag<tag_array<T>>
{

};

//Typedefs that should be used instead of the template tag_array.
typedef tag_array<int8_t> tag_byte_array;
typedef tag_array<int32_t> tag_int_array;

}

#endif // TAG_ARRAY_H_INCLUDED
