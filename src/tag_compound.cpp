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

#include "tag_compound.h"

namespace nbt
{

tag& tag_compound::at(const std::string& key)
{
    auto it = m_data.find(key);
    if(it == m_data.end())
        throw key_not_found(key);
    return *it->second;
}

const tag& tag_compound::at(const std::string& key) const
{
    auto it = m_data.find(key);
    if(it == m_data.end())
        throw key_not_found(key);
    return *it->second;
}

tag& tag_compound::at(std::initializer_list<std::string> keys)
{
    tag* p = this;
    for(const std::string& key: keys)
        p = &p->as<tag_compound>().at(key);
    return *p;
}

const tag& tag_compound::at(std::initializer_list<std::string> keys) const
{
    const tag* p = this;
    for(const std::string& key: keys)
        p = &p->as<tag_compound>().at(key);
    return *p;
}

void tag_compound::print(std::ostream& os) const
{
    os << "compound(" << m_data.size() << ") {\n";
    for(const auto& tp: m_data)
        os << '"' << tp.first << "\" -> " << *tp.second << '\n';
    os << '}';
}

void tag_compound::write_payload(std::ostream& os) const
{
    for(const auto& p: m_data)
        io::write(os, p.first, *p.second);
    os.put(static_cast<char>(tag_type::_end));
}

}
