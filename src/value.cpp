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
    tag_->assign(std::move(t));
    return *this;
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
