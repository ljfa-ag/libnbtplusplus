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

#ifndef TAG_COMPOUND_H_INCLUDED
#define TAG_COMPOUND_H_INCLUDED

#include "tag_base.h"

#include <map>
#include <memory>
#include <boost/iterator/transform_iterator.hpp>

namespace nbt
{

///Contains multiple named tags of arbitrary types.
class tag_compound : public tag
{
private:
    typedef std::map<std::string, std::unique_ptr<tag>> _map_t;

    //Functors for the boost transform_iterator.
    struct _it_trans
    {
        std::pair<const std::string&, tag&> operator()(const _map_t::value_type& it) const noexcept
        { return {it.first, *it.second}; }
    };

    struct _const_it_trans
    {
        std::pair<const std::string&, const tag&> operator()(const _map_t::value_type& it) const noexcept
        { return {it.first, *it.second}; }
    };

public:
    ///Exception thrown when the access by key fails.
    struct key_not_found : public std::out_of_range
    {
        explicit key_not_found(const std::string& key):
        std::out_of_range("Key \"" + key + "\" not found in compound.") {}
    };

    /* Iterator typedefs
    Boost will never let me down <3 */
    typedef boost::transform_iterator<_it_trans, _map_t::iterator, std::pair<const std::string&, tag&>> iterator;
    typedef boost::transform_iterator<_const_it_trans, _map_t::const_iterator, std::pair<const std::string&, const tag&>> const_iterator;

    ///The type of the tag.
    static constexpr tag_type type = tag_type::_compound;

    ///Constructs an empty compound.
    tag_compound() {}

    //tag_compound is not copyable.
    tag_compound(const tag_compound&) = delete;
    tag_compound& operator=(const tag_compound&) = delete;

    //The move constructor and assignment operator must explicitly be defaulted,
    //otherwise the compiler attempts to use the deleted copy constructor and assignment.
    tag_compound(tag_compound&&) = default;
    tag_compound& operator=(tag_compound&&) = default;

    /**
     * \brief Accesses a tag by key.
     * \throw key_not_found if the key does not exist.
     */
    tag& at(const std::string& key);
    const tag& at(const std::string& key) const;

    /**
     * \brief Accesses a nested compound tag by a sequence of keys.
     *
     * Example:
     * \code x.at({"foo", "bar"}) \endcode
     * is equivalent to
     * \code x.at("foo").as<tag_compound>().at("bar") \endcode
     * \throw key_not_found if a key in the sequence does not exist.
     * \throw bad_as if a key in the sequence does not refer to a tag_compound.
     */
    tag& at(std::initializer_list<std::string> keys);
    const tag& at(std::initializer_list<std::string> keys) const;

    ///\sa at
    tag& operator[](const std::string& key) { return at(key); }
    const tag& operator[](const std::string& key) const { return at(key); }
    tag& operator[](std::initializer_list<std::string> keys) { return at(keys); }
    const tag& operator[](std::initializer_list<std::string> keys) const { return at(keys); }

    /**
     * \brief Inserts a tag into the container.
     *
     * The tag pointed to by \c tp is moved into the container.
     * If the given key already exists, no insertion is performed.
     * \return true if the tag was inserted.
     */
    bool insert(std::string key, std::unique_ptr<tag>&& tp);
    /**
     * \brief Allocates and constructs a new tag and inserts it into the container.
     *
     * Allocates space and constructs a new tag of type \c T using the given constructor arguments.
     * and inserts it into the container.
     * If the given key already exists, no construction and no insertion is performed.
     * \return true if the tag was inserted.
     */
    template<class T, class... Args> bool emplace(std::string key, Args&&... args);

    /**
     * \brief Erases an element from the container.
     * \return true if an element was erased.
     */
    bool erase(const std::string& key) { return m_data.erase(key); }

    ///Returns the number of elements in the container.
    uint32_t size() const noexcept { return m_data.size(); }

    ///Erases all elements from the container.
    void clear() { m_data.clear(); }

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend() const noexcept { return end(); }

    //Implementation of the tag interface.
    tag_type get_type() const noexcept { return type; }
    void print(std::ostream& os) const;

    ///Returns a constant reference to the internally used \c std::map object.
    const _map_t& data() const noexcept { return m_data; }

protected:
    void write_payload(std::ostream& os) const;

private:
    _map_t m_data;
};

inline auto tag_compound::begin() noexcept       -> iterator       { return {m_data.begin(),  _it_trans()}; }
inline auto tag_compound::end() noexcept         -> iterator       { return {m_data.end(),    _it_trans()}; }
inline auto tag_compound::begin() const noexcept -> const_iterator { return {m_data.cbegin(), _const_it_trans()}; }
inline auto tag_compound::end() const noexcept   -> const_iterator { return {m_data.cend(),   _const_it_trans()}; }

inline bool tag_compound::insert(std::string key, std::unique_ptr<tag>&& tp)
{ return m_data.insert(std::make_pair(std::move(key), std::move(tp))).second; }

template<class T, class... Args> inline bool tag_compound::emplace(std::string key, Args&&... args)
{
    if(m_data.find(key) != m_data.end())
        return false;
    insert(std::move(key), std::unique_ptr<T>(new T(std::forward<Args>(args)...)));
    return true;
}

}

#endif // TAG_COMPOUND_H_INCLUDED
