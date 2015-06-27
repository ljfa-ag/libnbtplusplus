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
#ifndef TAG_REF_PROXY_H_INCLUDED
#define TAG_REF_PROXY_H_INCLUDED

#include "tag.h"
#include <memory>
#include <string>

namespace nbt
{

//Forward declarations
class tag_compound;
class tag_list;

/**
 * @brief Represents a reference to a tag of fixed type
 *
 * This can contain a tag of arbitrary type, but once the tag's type
 * is set it is immutable.
 * It can be casted to or assigned values, but if the types do not match it
 * will throw an exception.
 * It can also refer to an uninitialized value (e.g. when using tag_compound::operator[]
 * with a non-existant key).
 */
class nbt_value
{
public:
    //Movable but not (implicitly) copyable
    nbt_value& operator=(nbt_value&&) = default;
    nbt_value& operator=(const nbt_value&) = delete;

    //nbt_value& operator=(std::unique_ptr<tag>&& ptr);

    //Assignment
    /**
     * @brief Assigns the given value to the tag if the type matches
     * @throw std::bad_cast if the value is not convertible to the tag type
     * via a widening conversion
     */
    nbt_value& operator=(int8_t val);
    nbt_value& operator=(int16_t val);
    nbt_value& operator=(int32_t val);
    nbt_value& operator=(int64_t val);
    nbt_value& operator=(float val);
    nbt_value& operator=(double val);
    nbt_value& operator=(const std::string& str);
    nbt_value& operator=(tag_compound&& comp);
    nbt_value& operator=(tag_list&& list);

    //Conversion to tag
    operator tag&();
    operator const tag&() const;

    //Conversions to primitives and string
    /**
     * @brief Casts the value if the type matches
     * @throw std::bad_cast if the tag type is not convertible to the desired
     * type via a widening conversion
     */
    explicit operator int8_t() const;
    explicit operator int16_t() const;
    explicit operator int32_t() const;
    explicit operator int64_t() const;
    explicit operator float() const;
    explicit operator double() const;
    explicit operator const std::string&() const;

    /**
     * @brief In case of a tag_compound, accesses a tag by key
     * @throw std::bad_cast if the tag type is not tag_compound
     * @sa tag_compound::operator[]
     */
    nbt_value& operator[](const std::string& key);
    const nbt_value& operator[](const std::string& key) const;

    ///@sa tag::get_type
    tag_type get_type() const;

    friend bool operator==(const nbt_value& lhs, const nbt_value& rhs);
    friend bool operator!=(const nbt_value& lhs, const nbt_value& rhs);

private:
    std::unique_ptr<tag> value;
};

}

#endif // TAG_REF_PROXY_H_INCLUDED
