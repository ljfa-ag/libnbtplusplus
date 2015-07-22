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
#include "tag_list.h"
#include "libnbt.h"

namespace nbt
{

tag_list::tag_list():
    tag_list(tag_type::Null)
{}

tag_list::tag_list(tag_type type):
    el_type_(type)
{}

tag_list::tag_list(std::initializer_list<int8_t>         il) { init<tag_byte>(il); }
tag_list::tag_list(std::initializer_list<int16_t>        il) { init<tag_short>(il); }
tag_list::tag_list(std::initializer_list<int32_t>        il) { init<tag_int>(il); }
tag_list::tag_list(std::initializer_list<int64_t>        il) { init<tag_long>(il); }
tag_list::tag_list(std::initializer_list<float>          il) { init<tag_float>(il); }
tag_list::tag_list(std::initializer_list<double>         il) { init<tag_double>(il); }
tag_list::tag_list(std::initializer_list<std::string>    il) { init<tag_string>(il); }
tag_list::tag_list(std::initializer_list<tag_byte_array> il) { init<tag_byte_array>(il); }
tag_list::tag_list(std::initializer_list<tag_list>       il) { init<tag_list>(il); }
tag_list::tag_list(std::initializer_list<tag_compound>   il) { init<tag_compound>(il); }
tag_list::tag_list(std::initializer_list<tag_int_array>  il) { init<tag_int_array>(il); }

tag_list::tag_list(std::initializer_list<value> init)
{
    if(init.size() == 0)
        el_type_ = tag_type::Null;
    else
    {
        el_type_ = init.begin()->get_type();
        for(const value& val: init)
        {
            if(!val || val.get_type() != el_type_)
                throw std::bad_cast();
        }
        tags.assign(init.begin(), init.end());
    }
}

value& tag_list::at(size_t i)
{
    return tags.at(i);
}

const value& tag_list::at(size_t i) const
{
    return tags.at(i);
}

value& tag_list::operator[](size_t i)
{
    return tags[i];
}

const value& tag_list::operator[](size_t i) const
{
    return tags[i];
}

void tag_list::set(size_t i, value&& val)
{
    if(val.get_type() != el_type_)
        throw std::bad_cast();
    tags.at(i) = std::move(val);
}

void tag_list::push_back(value_initializer&& val)
{
    if(!val) //don't allow null values
        throw std::bad_cast();
    if(el_type_ == tag_type::Null) //set content type if undetermined
        el_type_ = val.get_type();
    else if(el_type_ != val.get_type())
        throw std::bad_cast();
    tags.push_back(std::move(val));
}

void tag_list::pop_back()
{
    tags.pop_back();
}

tag_type tag_list::el_type() const
{
    return el_type_;
}

size_t tag_list::size() const
{
    return tags.size();
}

void tag_list::clear()
{
    tags.clear();
}

auto tag_list::begin() -> iterator { return tags.begin(); }
auto tag_list::end()   -> iterator { return tags.end(); }
auto tag_list::begin() const  -> const_iterator { return tags.begin(); }
auto tag_list::end() const    -> const_iterator { return tags.end(); }
auto tag_list::cbegin() const -> const_iterator { return tags.cbegin(); }
auto tag_list::cend() const   -> const_iterator { return tags.cend(); }

bool operator==(const tag_list& lhs, const tag_list& rhs)
{
    if(lhs.size() == 0 && rhs.size() == 0)
        return true;
    return lhs.el_type_ == rhs.el_type_ && lhs.tags == rhs.tags;
}

bool operator!=(const tag_list& lhs, const tag_list& rhs)
{
    return !(lhs == rhs);
}

}
