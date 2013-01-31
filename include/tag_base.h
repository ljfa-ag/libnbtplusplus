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

#ifndef TAG_BASE_H_INCLUDED
#define TAG_BASE_H_INCLUDED

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace nbt
{

//Forward declarations:
class tag;
namespace io { void write(std::ostream&, const std::string&, const tag&); }

///Base class for all tag classes.
class tag
{
public:
    ///Tag type values used in the binary NBT format.
    enum class tag_type : int8_t
    {
        _end = 0,
        _byte = 1,
        _short = 2,
        _int = 3,
        _long = 4,
        _float = 5,
        _double = 6,
        _byte_array = 7,
        _string = 8,
        _list = 9,
        _compound = 10,
        _int_array = 11
    };

    ///Exception thrown when the cast with #as fails.
    struct bad_as : public std::runtime_error
    { explicit bad_as(tag_type from, tag_type to); };

    /**
     * \brief Exception thrown when reading a tag from stream fails.
     * \sa read
     */
    struct input_error : public std::runtime_error
    { explicit input_error(std::string str): std::runtime_error(std::move(str)) {} };

    //Virtual destructor
    virtual ~tag() noexcept {}

    /**
     * \brief Attempts to cast the tag reference to the given type.
     * \throw bad_as if the tag is not of type T.
     * \sa static_as
     */
    template<class T> T& as();
    template<class T> const T& as() const;

    /**
     * \brief `static_cast`s the tag reference to the given type.
     * \sa as
     */
    template<class T> T& static_as();
    template<class T> const T& static_as() const;

    ///Returns the type of the tag.
    virtual tag_type get_type() const noexcept = 0;

    ///Prints a human-readable representation of the tag into the stream.
    virtual void print(std::ostream& os) const = 0;

protected:
    ///Writes the binary content of the tag into the stream.
    virtual void write_payload(std::ostream& os) const = 0;

    //The container classes need access to the protected read and write functions.
    friend class tag_list;
    friend class tag_compound;

    //The write function needs access to wite_payload.
    friend void io::write(std::ostream&, const std::string&, const tag&);
};

template<class T> inline T& tag::as()
{
    if(get_type() != T::type)
        throw bad_as(get_type(), T::type);
    return static_cast<T&>(*this);
}

template<class T> inline const T& tag::as() const
{
    if(get_type() != T::type)
        throw bad_as(get_type(), T::type);
    return static_cast<const T&>(*this);
}

template<class T> inline T& tag::static_as()
{ return static_cast<T&>(*this); }

template<class T> inline const T& tag::static_as() const
{ return static_cast<const T&>(*this); }

///\relates tag
inline std::ostream& operator<<(std::ostream& os, const tag& t)
{ t.print(os); return os; }

///\relates tag
std::ostream& operator<<(std::ostream& os, tag::tag_type tt);

}

#endif // TAG_BASE_H_INCLUDED
