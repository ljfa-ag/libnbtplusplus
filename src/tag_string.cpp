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
#include "tag_string.h"

namespace nbt
{

tag_string::tag_string(const std::string& str):
    value(str)
{}

tag_string::tag_string(std::string&& str):
    value(std::move(str))
{}

tag_string::tag_string(const char* str):
    value(std::string(str))
{}

tag_string::operator std::string&()
{
    return value;
}

tag_string::operator const std::string&() const
{
    return value;

}
const std::string& tag_string::get() const
{
    return value;
}

tag_string& tag_string::operator=(const std::string& str)
{
    value = str;
    return *this;
}

tag_string& tag_string::operator=(std::string&& str)
{
    value = std::move(str);
    return *this;
}

tag_string& tag_string::operator=(const char* str)
{
    value = std::string(str);
    return *this;
}

void tag_string::set(const std::string& str)
{
    value = str;
}

void tag_string::set(std::string&& str)
{
    value = std::move(str);
}

bool operator==(const tag_string& lhs, const tag_string& rhs)
{
    return lhs.get() == rhs.get();
}

bool operator!=(const tag_string& lhs, const tag_string& rhs)
{
    return !(lhs == rhs);
}

}
