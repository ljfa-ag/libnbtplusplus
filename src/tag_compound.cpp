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
#include "tag_compound.h"

namespace nbt
{

value& tag_compound::at(const std::string& key)
{
    return tags.at(key);
}

const value& tag_compound::at(const std::string& key) const
{
    return tags.at(key);
}

value& tag_compound::operator[](const std::string& key)
{
    return tags[key];
}

bool tag_compound::put(const std::string& key, std::unique_ptr<tag>&& t)
{
    auto it = tags.find(key);
    if(it != tags.end())
    {
        it->second = std::move(t);
        return false;
    }
    else
    {
        tags.emplace(key, value(std::move(t)));
        return true;
    }
}

bool tag_compound::erase(const std::string& key)
{
    return tags.erase(key) != 0;
}

bool tag_compound::has_key(const std::string& key) const
{
    return tags.find(key) != tags.end();
}

size_t tag_compound::size() const
{
    return tags.size();
}

void tag_compound::clear()
{
    tags.clear();
}

auto tag_compound::begin() -> iterator { return tags.begin(); }
auto tag_compound::end()   -> iterator { return tags.end(); }
auto tag_compound::begin() const  -> const_iterator { return tags.begin(); }
auto tag_compound::end() const    -> const_iterator { return tags.end(); }
auto tag_compound::cbegin() const -> const_iterator { return tags.cbegin(); }
auto tag_compound::cend() const   -> const_iterator { return tags.cend(); }

tag_type tag_compound::get_type() const noexcept
{
    return type;
}

std::unique_ptr<tag> tag_compound::move_clone() &&
{
    return std::unique_ptr<tag>(new tag_compound(std::move(*this)));
}

bool tag_compound::equals(const tag& rhs) const
{
    return tags == static_cast<const tag_compound&>(rhs).tags;
}

}
