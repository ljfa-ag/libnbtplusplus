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
#include "value.h"
#include "libnbt.h"
#include <typeinfo>

namespace nbt
{

value::value(std::unique_ptr<tag>&& t):
    tag_(std::move(t))
{}

value& value::operator=(tag&& t)
{
    set(std::move(t));
    return *this;
}

void value::set(tag&& t)
{
    tag_->assign(std::move(t));
}

value::operator tag&()
{
    return get();
}

value::operator const tag&() const
{
    return get();
}

tag& value::get()
{
    return *tag_;
}

const tag& value::get() const
{
    return *tag_;
}

//Primitive assignment
//FIXME: Make this less copypaste!
value& value::operator=(int8_t val)
{
    switch(tag_->get_type())
    {
    case tag_type::Byte:
        static_cast<tag_byte&>(*tag_).set(val);
        break;
    case tag_type::Short:
        static_cast<tag_short&>(*tag_).set(val);
        break;
    case tag_type::Int:
        static_cast<tag_int&>(*tag_).set(val);
        break;
    case tag_type::Long:
        static_cast<tag_long&>(*tag_).set(val);
        break;
    case tag_type::Float:
        static_cast<tag_float&>(*tag_).set(val);
        break;
    case tag_type::Double:
        static_cast<tag_double&>(*tag_).set(val);
        break;

    default:
        throw std::bad_cast();
    }
    return *this;
}

value& value::operator=(int16_t val)
{
    switch(tag_->get_type())
    {
    case tag_type::Short:
        static_cast<tag_short&>(*tag_).set(val);
        break;
    case tag_type::Int:
        static_cast<tag_int&>(*tag_).set(val);
        break;
    case tag_type::Long:
        static_cast<tag_long&>(*tag_).set(val);
        break;
    case tag_type::Float:
        static_cast<tag_float&>(*tag_).set(val);
        break;
    case tag_type::Double:
        static_cast<tag_double&>(*tag_).set(val);
        break;

    default:
        throw std::bad_cast();
    }
    return *this;
}

value& value::operator=(int32_t val)
{
    switch(tag_->get_type())
    {
    case tag_type::Int:
        static_cast<tag_int&>(*tag_).set(val);
        break;
    case tag_type::Long:
        static_cast<tag_long&>(*tag_).set(val);
        break;
    case tag_type::Float:
        static_cast<tag_float&>(*tag_).set(val);
        break;
    case tag_type::Double:
        static_cast<tag_double&>(*tag_).set(val);
        break;

    default:
        throw std::bad_cast();
    }
    return *this;
}

value& value::operator=(int64_t val)
{
    switch(tag_->get_type())
    {
    case tag_type::Long:
        static_cast<tag_long&>(*tag_).set(val);
        break;
    case tag_type::Float:
        static_cast<tag_float&>(*tag_).set(val);
        break;
    case tag_type::Double:
        static_cast<tag_double&>(*tag_).set(val);
        break;

    default:
        throw std::bad_cast();
    }
    return *this;
}

value& value::operator=(float val)
{
    switch(tag_->get_type())
    {
    case tag_type::Float:
        static_cast<tag_float&>(*tag_).set(val);
        break;
    case tag_type::Double:
        static_cast<tag_double&>(*tag_).set(val);
        break;

    default:
        throw std::bad_cast();
    }
    return *this;
}

value& value::operator=(double val)
{
    switch(tag_->get_type())
    {
    case tag_type::Double:
        static_cast<tag_double&>(*tag_).set(val);
        break;

    default:
        throw std::bad_cast();
    }
    return *this;
}

//Primitive conversion
value::operator int8_t() const
{
    switch(tag_->get_type())
    {
    case tag_type::Byte:
        return static_cast<tag_byte&>(*tag_).get();

    default:
        throw std::bad_cast();
    }
}

value::operator int16_t() const
{
    switch(tag_->get_type())
    {
    case tag_type::Byte:
        return static_cast<tag_byte&>(*tag_).get();
    case tag_type::Short:
        return static_cast<tag_short&>(*tag_).get();

    default:
        throw std::bad_cast();
    }
}

value::operator int32_t() const
{
    switch(tag_->get_type())
    {
    case tag_type::Byte:
        return static_cast<tag_byte&>(*tag_).get();
    case tag_type::Short:
        return static_cast<tag_short&>(*tag_).get();
    case tag_type::Int:
        return static_cast<tag_int&>(*tag_).get();

    default:
        throw std::bad_cast();
    }
}

value::operator int64_t() const
{
    switch(tag_->get_type())
    {
    case tag_type::Byte:
        return static_cast<tag_byte&>(*tag_).get();
    case tag_type::Short:
        return static_cast<tag_short&>(*tag_).get();
    case tag_type::Int:
        return static_cast<tag_int&>(*tag_).get();
    case tag_type::Long:
        return static_cast<tag_long&>(*tag_).get();

    default:
        throw std::bad_cast();
    }
}

value::operator float() const
{
    switch(tag_->get_type())
    {
    case tag_type::Byte:
        return static_cast<tag_byte&>(*tag_).get();
    case tag_type::Short:
        return static_cast<tag_short&>(*tag_).get();
    case tag_type::Int:
        return static_cast<tag_int&>(*tag_).get();
    case tag_type::Long:
        return static_cast<tag_long&>(*tag_).get();
    case tag_type::Float:
        return static_cast<tag_float&>(*tag_).get();

    default:
        throw std::bad_cast();
    }
}

value::operator double() const
{
    switch(tag_->get_type())
    {
    case tag_type::Byte:
        return static_cast<tag_byte&>(*tag_).get();
    case tag_type::Short:
        return static_cast<tag_short&>(*tag_).get();
    case tag_type::Int:
        return static_cast<tag_int&>(*tag_).get();
    case tag_type::Long:
        return static_cast<tag_long&>(*tag_).get();
    case tag_type::Float:
        return static_cast<tag_float&>(*tag_).get();
    case tag_type::Double:
        return static_cast<tag_double&>(*tag_).get();

    default:
        throw std::bad_cast();
    }
}

value& value::operator=(const std::string& str)
{
    return *this = std::move(std::string(str));
}

value& value::operator=(std::string&& str)
{
    dynamic_cast<tag_string&>(*tag_).set(std::move(str));
    return *this;
}

value::operator const std::string&() const
{
    return dynamic_cast<tag_string&>(*tag_).get();
}

value::operator bool() const
{
    return tag_ != nullptr;
}

std::unique_ptr<tag>& value::get_ptr()
{
    return tag_;
}

const std::unique_ptr<tag>& value::get_ptr() const
{
    return tag_;
}

void value::set_ptr(std::unique_ptr<tag>&& t)
{
    tag_ = std::move(t);
}

tag_type value::get_type() const
{
    return tag_->get_type();
}

bool operator==(const value& lhs, const value& rhs)
{
    return *lhs.tag_ == *rhs.tag_;
}

bool operator!=(const value& lhs, const value& rhs)
{
    return !(lhs == rhs);
}

}
