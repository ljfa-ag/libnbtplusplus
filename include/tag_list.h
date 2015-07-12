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
#ifndef TAG_LIST_H_INCLUDED
#define TAG_LIST_H_INCLUDED

#include "crtp_tag.h"
#include <vector>

namespace nbt
{

///Tag that contains multiple unnamed tags of the same type
class tag_list : public detail::crtp_tag<tag_list>
{
public:
    //Iterator types
    typedef std::vector<value>::iterator iterator;
    typedef std::vector<value>::const_iterator const_iterator;

    ///The type of the tag
    static constexpr tag_type type = tag_type::List;

    /**
     * @brief Constructs an empty list
     *
     * The content type is determined when the first tag is added.
     */
    tag_list();

    ///Constructs an empty list with the given content type
    tag_list(tag_type type);

    /**
     * @brief Accesses a tag by index with bounds checking
     *
     * Returns a value to the tag at the specified index, or throws an
     * exception if it is out of range.
     * @throw std::out_of_range if given key does not exist
     */
    value& at(size_t i);
    const value& at(size_t i) const;

    /**
     * @brief Accesses a tag by index
     *
     * Returns a value to the tag at the specified index. No bounds checking
     * is performed.
     */
    value& operator[](size_t i);
    const value& operator[](size_t i) const;

    /**
     * @brief Appends the tag to the end of the list
     * @throw std::bad_cast if the type of the tag does not match the list's
     * content type
     */
    void push_back(value&& val);

    /**
     * @brief Constructs and appends a tag to the end of the list
     * @throw std::bad_cast if the type of the tag does not match the list's
     * content type
     */
    template<class T, class... Args>
    void emplace_back(Args&&... args);

    ///Removes the last element of the list
    void pop_back();

    ///Returns the content type of the list, or tag_type::Null if undetermined
    tag_type el_type() const;

    ///Returns the number of tags in the list
    size_t size() const;

    ///Erases all tags from the list
    void clear();

    //Iterators
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    friend bool operator==(const tag_list& lhs, const tag_list& rhs);
    friend bool operator!=(const tag_list& lhs, const tag_list& rhs);

private:
    std::vector<value> tags;
    tag_type el_type;
};

}

#endif // TAG_LIST_H_INCLUDED
