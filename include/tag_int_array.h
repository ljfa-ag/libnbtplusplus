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

#ifndef TAG_INT_ARRAY_H_INCLUDED
#define TAG_INT_ARRAY_H_INCLUDED

#include "tag_base.h"

#include <vector>

namespace nbt
{

///Contains an array of signed 32-bit integers.
class tag_int_array : public tag
{
public:
    ///The type of the tag.
    static constexpr tag_type type = tag_type::_int_array;

    tag_int_array() {} ///< Default constructor
    explicit tag_int_array(const std::vector<int32_t>& v): data(v) {} ///< Vector-copy constructor
    explicit tag_int_array(std::vector<int32_t>&& v): data(std::move(v)) {} ///< Vector-move constructor
    tag_int_array(uint32_t len, int32_t val = 0): data(len, val) {} ///< Fill constructor
    template<class InputIt> tag_int_array(InputIt first, InputIt last): data(first, last) {} ///< Range constructor
    tag_int_array(std::initializer_list<int32_t> il): data(il) {} ///< Initializer-list constructor

    tag_type get_type() const noexcept { return type; }

    void print(std::ostream& os) const
    { os << "int_array(" << data.size() << ')'; }

    ///Returns the number of bytes contained.
    uint32_t size() const noexcept { return data.size(); }

    ///The data array.
    std::vector<int32_t> data;

protected:
    void write_payload(std::ostream& os) const;
};

}

#endif // TAG_INT_ARRAY_H_INCLUDED
