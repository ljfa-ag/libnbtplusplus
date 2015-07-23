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
#ifndef CRTP_TAG_H_INCLUDED
#define CRTP_TAG_H_INCLUDED

#include "tag.h"
#include "make_unique.h"

namespace nbt
{

namespace detail
{

    template<class Sub>
    class crtp_tag : public tag
    {
    public:
        //Pure virtual destructor to make the class abstract
        virtual ~crtp_tag() noexcept = 0;

        tag_type get_type() const noexcept override final;

        std::unique_ptr<tag> clone() const& override final;
        std::unique_ptr<tag> move_clone() && override final;

        tag& assign(tag&& rhs) override final;

    private:
        bool equals(const tag& rhs) const override final;
    };

    template<class Sub>
    crtp_tag<Sub>::~crtp_tag() noexcept {}

    template<class Sub>
    tag_type crtp_tag<Sub>::get_type() const noexcept
    {
        return Sub::type;
    }

    template<class Sub>
    std::unique_ptr<tag> crtp_tag<Sub>::clone() const&
    {
        return make_unique<Sub>(static_cast<const Sub&>(*this));
    }

    template<class Sub>
    std::unique_ptr<tag> crtp_tag<Sub>::move_clone() &&
    {
        return make_unique<Sub>(static_cast<Sub&&>(*this));
    }

    template<class Sub>
    tag& crtp_tag<Sub>::assign(tag&& rhs)
    {
        return static_cast<Sub&>(*this) = dynamic_cast<Sub&&>(rhs);
    }

    template<class Sub>
    bool crtp_tag<Sub>::equals(const tag& rhs) const
    {
        return static_cast<const Sub&>(*this) == static_cast<const Sub&>(rhs);
    }

}

}

#endif // CRTP_TAG_H_INCLUDED
