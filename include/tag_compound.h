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
#ifndef TAG_COMPOUND_H_INCLUDED
#define TAG_COMPOUND_H_INCLUDED

#include "tag.h"
#include "value.h"
#include <map>
#include <string>

namespace nbt
{

///Tag that contains multiple unordered named tags of arbitrary types
class tag_compound : public tag
{
public:
    //Iterator types
    typedef std::map<std::string, value>::iterator iterator;
    typedef std::map<std::string, value>::const_iterator const_iterator;

    ///The type of the tag
    static constexpr tag_type type = tag_type::Compound;

    ///Constructs an empty compound
    tag_compound() {}

    //TODO: Make a separate class similar to and convertible to value for initializing tag values
    //tag_compound(std::initializer_list<std::pair<std::string, value&&>> init);

    /**
     * @brief Accesses a tag by key with bounds checking
     *
     * Returns a value to the tag with the specified key, or throws an
     * exception if it does not exist.
     * @throw std::out_of_range if given key does not exist
     */
    value& at(const std::string& key);
    const value& at(const std::string& key) const;

    /**
     * @brief Accesses a tag by key
     *
     * If the key exists, returns a value to the corresponding tag.
     * Else, a new uninitalized entry is created under this key.
     */
    value& operator[](const std::string& key);

    /**
     * @brief Erases a tag from the compound
     * @return true if a tag was erased
     */
    bool erase(const std::string& key);

    ///Returns true if the given key exists in the compound
    bool has_key(const std::string& key) const;

    ///Returns the number of tags in the compound
    size_t size() const;

    ///Erases all tags from the compound
    void clear();

    //Iterators
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    tag_type get_type() const noexcept override;

private:
    std::map<std::string, value> tags;

    bool equals(const tag& rhs) const override;
};

}

#endif // TAG_COMPOUND_H_INCLUDED
