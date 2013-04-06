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

#ifndef TAG_STRING_H_INCLUDED
#define TAG_STRING_H_INCLUDED

#include "tag_base.h"

namespace nbt
{

///Contains a UTF-8 string.
class tag_string : public tag
{
public:
    ///The type of the tag.
    static constexpr tag_type type = tag_type::_string;

    ///Default constructor
    tag_string() {}
    ///String-copy constructor
    explicit tag_string(const std::string& s): str(s) {}
    ///String-move constructor
    explicit tag_string(std::string&& s): str(std::move(s)) {}

    tag_type get_type() const noexcept { return type; }

    void print(std::ostream& os) const
    { os << "string(\"" << str << "\")"; }

    ///The contained string.
    std::string str;

protected:
    void write_payload(std::ostream& os) const;
};

}

#endif // TAG_STRING_H_INCLUDED
