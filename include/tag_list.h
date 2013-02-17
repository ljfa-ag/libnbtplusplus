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

#ifndef TAG_LIST_H_INCLUDED
#define TAG_LIST_H_INCLUDED

#include "tag_base.h"

#include <memory>
#include <vector>
#include <boost/iterator/indirect_iterator.hpp>

namespace nbt
{

///Contains multiple unnamed tags from the same type.
class tag_list : public tag
{
private:
    typedef std::vector<std::unique_ptr<tag>> _vec_t;

public:
    ///Exception thrown when the access by index fails.
    struct index_out_of_range : public std::out_of_range
    { index_out_of_range(uint32_t index, uint32_t size); };

    ///Exception thrown when a tag of the wrong type is attempted to insert.
    struct bad_insert : public std::invalid_argument
    { bad_insert(tag_type given, tag_type list); };

    //Iterator typedefs
    typedef boost::indirect_iterator<_vec_t::iterator, tag> iterator;
    typedef boost::indirect_iterator<_vec_t::const_iterator, tag> const_iterator;

    ///The type of the tag.
    static constexpr tag_type type = tag_type::_list;

    ///Constructs a tag_list with \c tt as the type of the elements.
    explicit tag_list(tag_type tt) noexcept: m_type(tt) {}

    //tag_list is not copyable,
    tag_list(const tag_list&) = delete;
    tag_list& operator=(const tag_list&) = delete;

    //but movable. The move constructor and assignment operator
    //have to be defaulted explicitly.
    tag_list(tag_list&&) = default;
    tag_list& operator=(tag_list&&) = default;

    ///Returns the type of the list elements.
    tag_type element_type() const noexcept { return m_type; }

    ///Element access by index without bounds checking.
    tag& operator[](uint32_t i) { return *m_data[i]; }
    const tag& operator[](uint32_t i) const { return *m_data[i]; }
    /**
     * \brief Element access by index with bounds checking.
     * \throw index_out_of_range if the index is out of range.
     */
    tag& at(uint32_t i);
    const tag& at(uint32_t i) const;

    /**
     * \brief Inserts a tag at the back of the list.
     * \throw bad_insert if the type of the tag does not equal the element type of the list.
     */
    void push_back(std::unique_ptr<tag>&& tp);
    /**
     * \brief Allocates and constructs a new tag and inserts it at the back of the list.
     *
     * Allocates space and constructs a new tag of type \c T using the given constructor arguments.
     * and inserts it at the back of the list.
     * \throw bad_insert if the type of the tag does not equal the element type of the list.
     */
    template<class T, class... Args> void emplace_back(Args&&... args);

    ///Erases the last element from the list.
    void pop_back() { m_data.pop_back(); }

    ///Returns the number of elements in the list.
    uint32_t size() const noexcept { return m_data.size(); }

    ///Erases all elements from the list.
    void clear() noexcept { m_data.clear(); }
    ///Erases all elements from the list and resets the element type.
    void reset(tag_type new_type) noexcept { clear(); m_type = new_type; }

    ///Attempts to reserve enough space for n list elements.
    void reserve(uint32_t n) { m_data.reserve(n); }

    //List iterators
    iterator begin() noexcept { return m_data.begin(); }
    iterator end() noexcept { return m_data.end(); }
    const_iterator begin() const noexcept { return m_data.cbegin(); }
    const_iterator end() const noexcept { return m_data.cend(); }
    const_iterator cbegin() const noexcept { return m_data.cbegin(); }
    const_iterator cend() const noexcept { return m_data.cend(); }

    //Implementation of the tag interface
    tag_type get_type() const noexcept { return type; }
    void print(std::ostream& os) const;

    ///Returns a constant reference to the internally used \c std::vector object.
    const _vec_t& data() const noexcept { return m_data; }

protected:
    void write_payload(std::ostream& os) const;

private:
    tag_type m_type;
    _vec_t m_data;
};

inline tag& tag_list::at(uint32_t i)
{
    if(i >= size())
        throw index_out_of_range(i, size());
    return *m_data[i];
}

inline const tag& tag_list::at(uint32_t i) const
{
    if(i >= size())
        throw index_out_of_range(i, size());
    return *m_data[i];
}

template<class T, class... Args> inline void tag_list::emplace_back(Args&&... args)
{
    tag_type tt = T::type;
    if(tt != m_type)
        throw bad_insert(tt, m_type);
    m_data.push_back(std::unique_ptr<T>(new T(std::forward<Args>(args)...)));
}

}

#endif // TAG_LIST_H_INCLUDED
