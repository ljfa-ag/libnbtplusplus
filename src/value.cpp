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

namespace nbt
{

value::value(std::unique_ptr<tag>&& t):
    tag_(std::move(t))
{}

value& value::operator=(std::unique_ptr<tag>&& t)
{
    tag_ = std::move(t);
    return *this;
}

value& value::operator=(tag&& t)
{
    return *this = std::move(t).move_clone();
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
