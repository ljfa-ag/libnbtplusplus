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
#ifndef TAG_STRING_H_INCLUDED
#define TAG_STRING_H_INCLUDED

#include "tag.h"
#include <string>

namespace nbt
{

///Tag that contains a UTF-8 string
class tag_string final : public tag
{
public:
    ///The type of the tag
    static constexpr tag_type type = tag_type::String;

    tag_string(const std::string& str);
    tag_string(std::string&& str = "");

    operator std::string&();
    operator const std::string&() const;
    const std::string& get() const;

    tag_string& operator=(const std::string& str);
    tag_string& operator=(std::string&& str);
    void set(const std::string& str);
    void set(std::string&& str);

    tag_type get_type() const noexcept override;

    std::unique_ptr<tag> move_clone() && override;

private:
    std::string value;

    bool equals(const tag& rhs) const override;
};

bool operator==(const tag_string& lhs, const tag_string& rhs);
bool operator!=(const tag_string& lhs, const tag_string& rhs);

}

#endif // TAG_STRING_H_INCLUDED
