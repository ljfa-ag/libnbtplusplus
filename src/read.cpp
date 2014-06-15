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

#include "tag.h"
#include "nbt_io.h"
#include "endian_str.h"

#include <vector>
#include <boost/format.hpp>

namespace nbt
{

//Anonymous namespace for the internal reading functions.
namespace
{
    //Checks for a valid tag type. Optionally accepts the END tag as valid.
    bool is_valid_type(tag::tag_type tt, bool end_ok = false)
    {
        short range_begin = end_ok ? 0 : 1;
        int itt = static_cast<int>(tt);
        return range_begin <= itt && itt <= 11;
    }

    //Reads and checks type. Since Minecraft may create an Array of END tags,
    //optionally accept it.
    tag::tag_type read_type(std::istream& is, bool end_ok = false)
    {
        tag::tag_type tt = static_cast<tag::tag_type>(is.get());
        if(!is)
            throw tag::input_error("Error reading tag type");
        if(!is_valid_type(tt, end_ok))
        {
            is.setstate(std::ios::failbit);
            throw tag::input_error((boost::format("Invalid tag type: %1%") % static_cast<int>(tt)).str());
        }
        return tt;
    }

    //Reads and checks type for use in reading of tag_compound.
    //Returns false if "tag" read is tag_end, true otherwise.
    bool read_type_for_compound(std::istream& is, tag::tag_type& tt)
    {
        tt = static_cast<tag::tag_type>(is.get());
        if(!is)
            throw tag::input_error("Error reading tag type");
        if(tt == tag::tag_type::_end)
            return false;
        else if(!is_valid_type(tt))
        {
            is.setstate(std::ios::failbit);
            throw tag::input_error((boost::format("Invalid tag type: %1%") % static_cast<int>(tt)).str());
        }
        else
            return true;
    }

    std::string read_str(std::istream& is)
    {
        uint16_t len; //Strings in NBT are always preceded by a 16-bit integer as size
        endian::read_big(is, len);

        if(!is)
            return "";

        std::vector<char> buf(len);
        is.read(buf.data(), len);

        if(!is)
            return "";

        return {buf.begin(), buf.end()};
    }

    //Dispatching function
    //Forward declaration
    std::unique_ptr<tag> read_payload(tag::tag_type tt, std::istream& is);

    //Helper function for shorter unique_ptr creation syntax
    template<class T, class... Args> std::unique_ptr<T> make_uq(Args&&... args)
    { return std::unique_ptr<T>(new T(std::forward<Args>(args)...)); }

    //Functions for dedicated payload reading:

    template<class T> std::unique_ptr<T> read_scalar(std::istream& is)
    {
        typename T::value_type val;
        endian::read_big(is, val);
        return make_uq<T>(val);
    }

    std::unique_ptr<tag_byte_array> read_byte_array(std::istream& is)
    {
        uint32_t len;
        endian::read_big(is, len);

        if(!is)
            return nullptr;

        auto tp = make_uq<tag_byte_array>(len);
        is.read(reinterpret_cast<char*>(tp->data.data()), len);

        return tp;
    }

    std::unique_ptr<tag_list> read_list(std::istream& is)
    {
        tag::tag_type tt = read_type(is, true);

        auto tp = make_uq<tag_list>(tt);

        uint32_t len;
        endian::read_big(is, len);
        if(!is)
            return nullptr;
        tp->reserve(len);

        while(len--)
            tp->push_back(read_payload(tt, is));

        return tp;
    }

    std::unique_ptr<tag_compound> read_compound(std::istream& is)
    {
        auto tp = make_uq<tag_compound>();

        tag::tag_type tt;
        while(read_type_for_compound(is, tt))
        {
            std::string key = read_str(is);
            if(!is)
                throw tag::input_error((boost::format("Error reading name of tag_%1%") % tt).str());
            tp->insert(key, read_payload(tt, is));
        }

        return tp;
    }

    std::unique_ptr<tag_int_array> read_int_array(std::istream& is)
    {
        uint32_t len;
        endian::read_big(is, len);

        if(!is)
            return nullptr;

        auto tp = make_uq<tag_int_array>(len);
        for(int32_t& val: tp->data)
            endian::read_big(is, val);

        return tp;
    }

    //Definition of dispatching function
    std::unique_ptr<tag> read_payload(tag::tag_type tt, std::istream& is)
    {
        std::unique_ptr<tag> ret;
        switch(tt)
        {
        case tag::tag_type::_byte:       ret = read_scalar<tag_byte>(is); break;
        case tag::tag_type::_short:      ret = read_scalar<tag_short>(is); break;
        case tag::tag_type::_int:        ret = read_scalar<tag_int>(is); break;
        case tag::tag_type::_long:       ret = read_scalar<tag_long>(is); break;
        case tag::tag_type::_float:      ret = read_scalar<tag_float>(is); break;
        case tag::tag_type::_double:     ret = read_scalar<tag_double>(is); break;
        case tag::tag_type::_byte_array: ret = read_byte_array(is); break;
        case tag::tag_type::_string:     ret = make_uq<tag_string>(read_str(is)); break; //Just read_str.
        case tag::tag_type::_list:       ret = read_list(is); break;
        case tag::tag_type::_compound:   ret = read_compound(is); break;
        case tag::tag_type::_int_array:  ret = read_int_array(is); break;

        default: is.setstate(std::ios::failbit); break;
        }

        if(!is)
            throw tag::input_error((boost::format("Error reading contents from tag_%1%") % tt).str());
        return ret;
    }
}

std::unique_ptr<tag> io::read(std::istream& is, std::string& key)
{
    tag::tag_type tt = read_type(is);
    key = read_str(is);
    if(!is)
        throw tag::input_error((boost::format("Error reading name of tag_%1%") % tt).str());
    return read_payload(tt, is);
}

}
