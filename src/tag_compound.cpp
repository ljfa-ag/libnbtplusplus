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

tag_compound::tag_compound(std::initializer_list<std::pair<std::string, value_initializer>> init)
{
    for(const auto& pair: init)
        tags.emplace(std::move(pair.first), std::move(pair.second));
}

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

std::pair<tag_compound::iterator, bool> tag_compound::put(const std::string& key, value&& val)
{
    auto it = tags.find(key);
    if(it != tags.end())
    {
        it->second = std::move(val);
        return {it, false};
    }
    else
    {
        return tags.emplace(key, std::move(val));
    }
}

std::pair<tag_compound::iterator, bool> tag_compound::insert(const std::string& key, value&& val)
{
    return tags.emplace(key, std::move(val));
}

bool tag_compound::erase(const std::string& key)
{
    return tags.erase(key) != 0;
}

bool tag_compound::has_key(const std::string& key) const
{
    return tags.find(key) != tags.end();
}

bool tag_compound::has_key(const std::string& key, tag_type type) const
{
    auto it = tags.find(key);
    return it != tags.end() && it->second.get_type() == type;
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

bool operator==(const tag_compound& lhs, const tag_compound& rhs)
{
    return lhs.tags == rhs.tags;
}

bool operator!=(const tag_compound& lhs, const tag_compound& rhs)
{
    return !(lhs == rhs);
}

}
