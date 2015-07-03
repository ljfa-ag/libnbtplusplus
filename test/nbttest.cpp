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
#include <stdexcept>

using namespace nbt;

void test_get_type()
{
    ASSERT(tag_byte().get_type()       == tag_type::Byte);
    ASSERT(tag_short().get_type()      == tag_type::Short);
    ASSERT(tag_int().get_type()        == tag_type::Int);
    ASSERT(tag_long().get_type()       == tag_type::Long);
    ASSERT(tag_float().get_type()      == tag_type::Float);
    ASSERT(tag_double().get_type()     == tag_type::Double);
    //ASSERT(tag_byte_array().get_type() == tag_type::Byte_Array);
    ASSERT(tag_string().get_type()     == tag_type::String);
    //ASSERT(tag_list().get_type()       == tag_type::List);
    ASSERT(tag_compound().get_type()   == tag_type::Compound);
    //ASSERT(tag_int_array().get_type()  == tag_type::Int_Array);
}

void test_tag_primitive()
{
    tag_int tag(6);
    ASSERT(tag.get() == 6);
    int& ref = tag;
    ref = 12;
    ASSERT(tag == 12);
    ASSERT(tag != 6);
    tag.set(24);
    ASSERT(ref == 24);
    tag = 7;
    ASSERT(7 == static_cast<int>(tag));

    ASSERT(tag_double() == 0.0);
}

void test_tag_string()
{
    tag_string tag("foo");
    ASSERT(tag.get() == "foo");
    std::string& ref = tag;
    ref = "bar";
    ASSERT(tag.get() == "bar");
    ASSERT(tag.get() != "foo");
    tag.set("baz");
    ASSERT(ref == "baz");
    tag = "quux";
    ASSERT("quux" == static_cast<std::string>(tag));
    std::string str("foo");
    tag = str;
    ASSERT(tag.get() == str);

    ASSERT(tag_string(str).get() == "foo");
    ASSERT(tag_string().get() == "");
}

void test_tag_compound()
{
    tag_compound comp{
        {"foo", int16_t(12)},
        {"bar", "baz"},
        {"baz", -2.0}
    };

    ASSERT(comp["foo"].get_type() == tag_type::Short);
    ASSERT(int32_t(comp["foo"]) == 12);
    ASSERT(int16_t(comp.at("foo")) == int16_t(12));
    EXPECT_EXCEPTION(int8_t(comp["foo"]), std::bad_cast);
    EXPECT_EXCEPTION(std::string(comp["foo"]), std::bad_cast);

    EXPECT_EXCEPTION(comp["foo"] = 32, std::bad_cast);
    comp["foo"] = int8_t(32);
    ASSERT(int8_t(comp["foo"]) == 32);

    ASSERT(comp["bar"].get_type() == tag_type::String);
    ASSERT(std::string(comp["bar"]) == "baz");
    EXPECT_EXCEPTION(int(comp["bar"]), std::bad_cast);

    EXPECT_EXCEPTION(comp["bar"] = -128, std::bad_cast);
    comp["bar"] = "barbaz";
    ASSERT(std::string(comp["foo"]) == "barbaz");

    ASSERT(comp["baz"].get_type() == tag_type::Double);
    ASSERT(double(comp["baz"]) == -2.0);
    EXPECT_EXCEPTION(float(comp["baz"]), std::bad_cast);

    comp["quux"] = tag_compound{/*{"Hello", "World"}, {"zero", 0}*/};
    ASSERT(comp.at("quux").get_type() == tag_type::Compound);
    ASSERT(std::string(comp["quux"].at("Hello")) == "World");

    EXPECT_EXCEPTION(comp.at("nothing"), std::out_of_range);

    tag_compound comp2{
        {"foo", int16_t(32)},
        {"bar", "barbaz"},
        {"baz", -2.0},
        {"quux", tag_compound{{"Hello", "World"}, {"zero", 0}}}
    };
    ASSERT(comp == comp2);
    ASSERT(comp != (const tag_compound&)comp2["quux"]);
    ASSERT(comp != comp2["quux"]);

    ASSERT(comp2.size() == 4);
    const char* keys[] = {"bar", "baz", "foo", "quux"}; //alphabetic order
    unsigned i = 0;
    for(const std::pair<const std::string, value>& val: comp2)
    {
        ASSERT(i < comp2.size());
        ASSERT(val.first == keys[i]);
        ASSERT(val.second == comp2[keys[i]]);
        ++i;
    }

    ASSERT(comp.erase("nothing") == false);
    ASSERT(comp.has_key("quux"));
    ASSERT(comp.erase("quux") == true);
    ASSERT(!comp.has_key("quux"));

    comp.clear();
    ASSERT(comp == tag_compound{});

    ASSERT(comp.put("abc", std::unique_ptr<tag>(new tag_double(6.0))) == true);
    ASSERT(comp.put("abc", std::unique_ptr<tag>(new tag_long(-28))) == false);
    ASSERT(comp.emplace<tag_string>("def", "ghi") == true);
    ASSERT(comp.emplace<tag_byte>("def", 4) == false);
    ASSERT((comp == tag_compound{{"abc", tag_long(-28)}, {"def", tag_byte(4)}}));
}

int main()
{
    test_get_type();
    test_tag_primitive();
    test_tag_string();
    test_tag_compound();
}
