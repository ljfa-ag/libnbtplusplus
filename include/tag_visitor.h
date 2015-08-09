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
#ifndef TAG_VISITOR_H_INCLUDED
#define TAG_VISITOR_H_INCLUDED

#include "tagfwd.h"

namespace nbt
{

/**
 * @brief Base class for visitors of tags
 *
 * Implementing the Visitor pattern
 */
class tag_visitor
{
public:
    virtual ~tag_visitor() noexcept = 0; //Abstract class

    virtual void visit(tag_byte& tag) {}
    virtual void visit(tag_short& tag) {}
    virtual void visit(tag_int& tag) {}
    virtual void visit(tag_long& tag) {}
    virtual void visit(tag_float& tag) {}
    virtual void visit(tag_double& tag) {}
    virtual void visit(tag_byte_array& tag) {}
    virtual void visit(tag_string& tag) {}
    virtual void visit(tag_list& tag) {}
    virtual void visit(tag_compound& tag) {}
    virtual void visit(tag_int_array& tag) {}
};

inline tag_visitor::~tag_visitor() noexcept {}

}

#endif // TAG_VISITOR_H_INCLUDED
