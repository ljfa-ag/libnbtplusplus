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

#include "tag_string.h"
#include "endian_str.h"
#include "nbt_io.h"

#include <boost/format.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

namespace nbt
{

tag::bad_as::bad_as(tag_type from, tag_type to):
std::runtime_error((boost::format("Attempted to cast a tag of type \"%1%\" to \"%2%\" using as()") % from % to).str()) {}

std::ostream& operator<<(std::ostream& os, tag::tag_type tt)
{
    switch(tt)
    {
    case tag::tag_type::_end:        return os << "end";
    case tag::tag_type::_byte:       return os << "byte";
    case tag::tag_type::_short:      return os << "short";
    case tag::tag_type::_int:        return os << "int";
    case tag::tag_type::_long:       return os << "long";
    case tag::tag_type::_float:      return os << "float";
    case tag::tag_type::_double:     return os << "double";
    case tag::tag_type::_byte_array: return os << "byte_array";
    case tag::tag_type::_string:     return os << "string";
    case tag::tag_type::_list:       return os << "list";
    case tag::tag_type::_compound:   return os << "compound";
    case tag::tag_type::_int_array:  return os << "int_array";

    default: return os << "invalid [" << static_cast<int>(tt) << ']';
    }
}

//Anonymous namespace for the internal writing functions.
namespace
{
    void write_type(std::ostream& os, tag::tag_type tt)
    { os.put(static_cast<char>(tt)); }

    void write_str(std::ostream& os, const std::string& str)
    {
        uint16_t len = str.length();
        endian::write_big(os, len);
        os.write(str.c_str(), len);
    }
}

void tag_string::write_payload(std::ostream& os) const
{ write_str(os, str); }

void io::write(std::ostream& os, const std::string& key, const tag& t)
{
    write_type(os, t.get_type());
    write_str(os, key);
    t.write_payload(os);
}

namespace bio = boost::iostreams;

std::unique_ptr<tag> io::read_gzip(std::istream& is, std::string& key)
{
    bio::filtering_istream igzs;
    igzs.push(bio::gzip_decompressor());
    igzs.push(is);

    return read(igzs, key);
}

void io::write_gzip(std::ostream& os, const std::string& key, const tag& t, int compression_level)
{
    bio::filtering_ostream ogzs;
    ogzs.push(bio::gzip_compressor(bio::gzip_params(compression_level)));
    ogzs.push(os);

    write(ogzs, key, t);
}

}
