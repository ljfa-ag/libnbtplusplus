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
#include "microtest.h"
#include "libnbt.h"
#include <iostream>

using namespace nbt;

void test_get_type()
{
    ASSERT(tag_byte().get_type()   == tag_type::Byte);
    ASSERT(tag_short().get_type()  == tag_type::Short);
    ASSERT(tag_int().get_type()    == tag_type::Int);
    ASSERT(tag_long().get_type()   == tag_type::Long);
    ASSERT(tag_float().get_type()  == tag_type::Float);
    ASSERT(tag_double().get_type() == tag_type::Double);
}

int main()
{
    test_get_type();
}
