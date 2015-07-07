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
#ifndef TAG_H_INCLUDED
#define TAG_H_INCLUDED

#include <cstdint>
#include <memory>

namespace nbt
{

///Tag type values used in the binary format
enum class tag_type : int8_t
{
    End = 0,
    Byte = 1,
    Short = 2,
    Int = 3,
    Long = 4,
    Float = 5,
    Double = 6,
    Byte_Array = 7,
    String = 8,
    List = 9,
    Compound = 10,
    Int_Array = 11,
    Null = -1
};

///Base class for all NBT tag classes
class tag
{
public:
    //Virtual destructor
    virtual ~tag() noexcept {}

    ///Returns the type of the tag
    virtual tag_type get_type() const noexcept = 0;

    virtual std::unique_ptr<tag> clone() const& = 0;
    virtual std::unique_ptr<tag> move_clone() && = 0;

    friend bool operator==(const tag& lhs, const tag& rhs);
    friend bool operator!=(const tag& lhs, const tag& rhs);

private:
    /**
     * @brief Checks for equality to a tag of the same type
     * @param rhs an instance of the same class as @c *this
     */
    virtual bool equals(const tag& rhs) const = 0;

    /**
     * @brief Move-assigns the given tag if the class is the same
     * @throw std::bad_cast if @c rhs is not the same type as @c *this
     */
    virtual tag& assign(tag&& rhs) = 0;

    friend class value;
};

}

#endif // TAG_H_INCLUDED
