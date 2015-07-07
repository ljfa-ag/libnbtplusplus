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
#include <string>

namespace nbt
{

/**
 * @brief Contains an NBT value of fixed type
 *
 * A convenience wrapper around @c std::unique_ptr<tag>, contains a tag of
 * fixed type.
 */
class value
{
public:
    value() {}
    explicit value(std::unique_ptr<tag>&& t);
    explicit value(tag&& t);

    //Movable but not (implicitly) copyable
    value(const value&) = delete;
    value(value&&) = default;
    value& operator=(const value&) = delete;
    value& operator=(value&&) = default;

    /**
     * @brief Assigns the given value to the tag if the type matches
     * @throw std::bad_cast if the type of @c t is not the same as the type
     * of this value
     */
    value& operator=(tag&& t);
    void set(tag&& t);

    //Conversion to tag
    /**
     * @brief Returns the contained tag
     *
     * If the value is uninitialized, the behavior is undefined.
     */
    operator tag&();
    operator const tag&() const;
    tag& get();
    const tag& get() const;

    //Assignment of primitives and string
    /**
     * @brief Assigns the given value to the tag if the type is compatible
     * @throw std::bad_cast if the value is not convertible to the tag type
     * via a widening conversion
     */
    value& operator=(int8_t val);
    value& operator=(int16_t val);
    value& operator=(int32_t val);
    value& operator=(int64_t val);
    value& operator=(float val);
    value& operator=(double val);

    /**
     * @brief Assigns the given string to the tag if it is a tag_string
     * @throw std::bad_cast if the contained tag is not a tag_string
     */
    value& operator=(const std::string& str);
    value& operator=(std::string&& str);

    //Conversions to primitives and string
    /**
     * @brief Returns the contained value if the type is compatible
     * @throw std::bad_cast if the tag type is not convertible to the desired
     * type via a widening conversion
     */
    operator int8_t() const;
    operator int16_t() const;
    operator int32_t() const;
    operator int64_t() const;
    operator float() const;
    operator double() const;

    /**
     * @brief Returns the contained string if the type is tag_string
     *
     * If the value is uninitialized, the behavior is undefined.
     * @throw std::bad_cast if the tag type is not tag_string
     */
    operator const std::string&() const;

    ///Returns true if the value is not uninitialized
    explicit operator bool() const;

    /**
     * @brief In case of a tag_compound, accesses a tag by key with bounds checking
     *
     * If the value is uninitialized, the behavior is undefined.
     * @throw std::bad_cast if the tag type is not tag_compound
     * @throw std::out_of_range if given key does not exist
     * @sa tag_compound::at
     */
    value& at(const std::string& key);
    const value& at(const std::string& key) const;

    /**
     * @brief In case of a tag_compound, accesses a tag by key
     *
     * If the value is uninitialized, the behavior is undefined.
     * @sa tag_compound::operator[]
     */
    value& operator[](const std::string& key);
    value& operator[](const char* key); //need this overload because of conflict with built-in operator[]

    /**
     * @brief Creates a copy of the value
     */
    value copy() const;

    std::unique_ptr<tag>& get_ptr();
    const std::unique_ptr<tag>& get_ptr() const;
    void set_ptr(std::unique_ptr<tag>&& t);

    ///@sa tag::get_type
    tag_type get_type() const;

    friend bool operator==(const value& lhs, const value& rhs);
    friend bool operator!=(const value& lhs, const value& rhs);

private:
    std::unique_ptr<tag> tag_;
};

}

#endif // TAG_REF_PROXY_H_INCLUDED
