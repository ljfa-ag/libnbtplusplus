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

#include "tag_list.h"
#include "endian_str.h"

#include <boost/format.hpp>

namespace nbt
{

tag_list::index_out_of_range::index_out_of_range(uint32_t index, uint32_t size):
std::out_of_range((boost::format("Index %1% is out of list range, the size is %2%.")
    % index % size
).str()) {}

tag_list::bad_insert::bad_insert(tag_type given, tag_type expected):
std::invalid_argument((boost::format("Attempted to insert tag of type \"%1%\" in tag_list of type \"%2%\"")
    % given % expected
).str()) {}

void tag_list::push_back(std::unique_ptr<tag>&& tp)
{
    tag_type tt = tp->get_type();
    if(tt != m_type)
        throw bad_insert(tt, m_type);
    m_data.push_back(std::move(tp));
}

void tag_list::print(std::ostream& os) const
{
    os << "list<" << m_type << ">(" << size() << ") {\n";
    for(const tag& t: *this)
        os << t << '\n';
    os << '}';
}

void tag_list::write_payload(std::ostream& os) const
{
    os.put(static_cast<char>(m_type));
    endian::write_big(os, size());
    for(const tag& t: *this)
        t.write_payload(os);
}

}
