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
#include "nbt_tags.h"
#include <algorithm>

using namespace nbt;

void test_tag()
{
    ASSERT(*tag::create(tag_type::Byte) == tag_byte());
    ASSERT(tag::create(tag_type::Null) == nullptr);
    ASSERT(tag::create(tag_type::End) == nullptr);

    tag_string tstr("foo");
    auto cl = tstr.clone();
    ASSERT(tstr.get() == "foo");
    ASSERT(tstr == *cl);

    cl = std::move(tstr).clone();
    ASSERT(*cl == tag_string("foo"));
    ASSERT(*cl != tag_string("bar"));

    cl = std::move(*cl).move_clone();
    ASSERT(*cl == tag_string("foo"));

    tstr.assign(tag_string("bar"));
    EXPECT_EXCEPTION(tstr.assign(tag_int(6)), std::bad_cast);
    ASSERT(tstr.get() == "bar");
    std::clog << "test_tag passed" << std::endl;
}

void test_get_type()
{
    ASSERT(tag_byte().get_type()       == tag_type::Byte);
    ASSERT(tag_short().get_type()      == tag_type::Short);
    ASSERT(tag_int().get_type()        == tag_type::Int);
    ASSERT(tag_long().get_type()       == tag_type::Long);
    ASSERT(tag_float().get_type()      == tag_type::Float);
    ASSERT(tag_double().get_type()     == tag_type::Double);
    ASSERT(tag_byte_array().get_type() == tag_type::Byte_Array);
    ASSERT(tag_string().get_type()     == tag_type::String);
    ASSERT(tag_list().get_type()       == tag_type::List);
    ASSERT(tag_compound().get_type()   == tag_type::Compound);
    ASSERT(tag_int_array().get_type()  == tag_type::Int_Array);
    std::clog << "test_get_type passed" << std::endl;
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

    ASSERT(tag == tag_int(7));
    ASSERT(tag_float(2.5) != tag_float(-2.5));
    ASSERT(tag_float(2.5) != tag_double(2.5));

    ASSERT(tag_double() == 0.0);

    ASSERT(tag_byte(INT8_MAX).get() == INT8_MAX);
    ASSERT(tag_byte(INT8_MIN).get() == INT8_MIN);
    ASSERT(tag_short(INT16_MAX).get() == INT16_MAX);
    ASSERT(tag_short(INT16_MIN).get() == INT16_MIN);
    ASSERT(tag_int(INT32_MAX).get() == INT32_MAX);
    ASSERT(tag_int(INT32_MIN).get() == INT32_MIN);
    ASSERT(tag_long(INT64_MAX).get() == INT64_MAX);
    ASSERT(tag_long(INT64_MIN).get() == INT64_MIN);
    std::clog << "test_tag_primitive passed" << std::endl;
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
    std::clog << "test_tag_string passed" << std::endl;
}

void test_tag_compound()
{
    tag_compound comp{
        {"foo", int16_t(12)},
        {"bar", "baz"},
        {"baz", -2.0},
        {"list", tag_list{16, 17}}
    };

    ASSERT(comp["foo"].get_type() == tag_type::Short);
    ASSERT(static_cast<int32_t>(comp["foo"]) == 12);
    ASSERT(static_cast<int16_t>(comp.at("foo")) == int16_t(12));
    ASSERT(comp["foo"] == tag_short(12));
    EXPECT_EXCEPTION(static_cast<int8_t>(comp["foo"]), std::bad_cast);
    EXPECT_EXCEPTION(static_cast<std::string>(comp["foo"]), std::bad_cast);

    EXPECT_EXCEPTION(comp["foo"] = 32, std::bad_cast);
    comp["foo"] = int8_t(32);
    ASSERT(static_cast<int16_t>(comp["foo"]) == 32);

    ASSERT(comp["bar"].get_type() == tag_type::String);
    ASSERT(static_cast<std::string>(comp["bar"]) == "baz");
    EXPECT_EXCEPTION(static_cast<int>(comp["bar"]), std::bad_cast);

    EXPECT_EXCEPTION(comp["bar"] = -128, std::bad_cast);
    comp["bar"] = "barbaz";
    ASSERT(static_cast<std::string>(comp["bar"]) == "barbaz");

    ASSERT(comp["baz"].get_type() == tag_type::Double);
    ASSERT(static_cast<double>(comp["baz"]) == -2.0);
    EXPECT_EXCEPTION(static_cast<float>(comp["baz"]), std::bad_cast);

    comp["quux"] = tag_compound{{"Hello", "World"}, {"zero", 0}};
    ASSERT(comp.at("quux").get_type() == tag_type::Compound);
    ASSERT(std::string(comp["quux"].at("Hello")) == "World");
    ASSERT(std::string(comp["quux"]["Hello"]) == "World");
    ASSERT(comp["list"][1] == tag_int(17));

    EXPECT_EXCEPTION(comp.at("nothing"), std::out_of_range);

    tag_compound comp2{
        {"foo", int16_t(32)},
        {"bar", "barbaz"},
        {"baz", -2.0},
        {"quux", tag_compound{{"Hello", "World"}, {"zero", 0}}},
        {"list", tag_list{16, 17}}
    };
    ASSERT(comp == comp2);
    ASSERT(comp != dynamic_cast<const tag_compound&>(comp2["quux"].get()));
    ASSERT(comp != comp2["quux"]);
    ASSERT(dynamic_cast<const tag_compound&>(comp["quux"].get()) == comp2["quux"]);

    ASSERT(comp2.size() == 5);
    const char* keys[] = {"bar", "baz", "foo", "list", "quux"}; //alphabetic order
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
    ASSERT(comp.has_key("quux", tag_type::Compound));
    ASSERT(!comp.has_key("quux", tag_type::List));
    ASSERT(!comp.has_key("quux", tag_type::Null));

    ASSERT(comp.erase("quux") == true);
    ASSERT(!comp.has_key("quux"));
    ASSERT(!comp.has_key("quux", tag_type::Compound));
    ASSERT(!comp.has_key("quux", tag_type::Null));

    comp.clear();
    ASSERT(comp == tag_compound{});

    ASSERT(comp.put("abc", tag_double(6.0)).second == true);
    ASSERT(comp.put("abc", tag_long(-28)).second == false);
    ASSERT(comp.insert("ghi", tag_string("world")).second == true);
    ASSERT(comp.insert("abc", tag_string("hello")).second == false);
    ASSERT(comp.emplace<tag_string>("def", "ghi").second == true);
    ASSERT(comp.emplace<tag_byte>("def", 4).second == false);
    ASSERT((comp == tag_compound{
        {"abc", tag_long(-28)},
        {"def", tag_byte(4)},
        {"ghi", tag_string("world")}
    }));

    std::clog << "test_tag_compound passed" << std::endl;
}

void test_value()
{
    value val1;
    value val2(make_unique<tag_int>(42));
    value val3(tag_int(42));

    ASSERT(!val1 && val2 && val3);
    ASSERT(val1 == val1);
    ASSERT(val1 != val2);
    ASSERT(val2 == val3);
    ASSERT(val3 == val3);

    value valstr(tag_string("foo"));
    ASSERT(static_cast<std::string>(valstr) == "foo");
    valstr = "bar";
    EXPECT_EXCEPTION(valstr = 5, std::bad_cast);
    ASSERT(static_cast<std::string>(valstr) == "bar");
    ASSERT(valstr.as<tag_string>() == "bar");
    ASSERT(&valstr.as<tag>() == &valstr.get());
    EXPECT_EXCEPTION(valstr.as<tag_float>(), std::bad_cast);

    val1 = int64_t(42);
    ASSERT(val2 != val1);

    EXPECT_EXCEPTION(val2 = int64_t(12), std::bad_cast);
    ASSERT(static_cast<int64_t>(val2) == 42);
    tag_int* ptr = dynamic_cast<tag_int*>(val2.get_ptr().get());
    ASSERT(*ptr == 42);
    val2 = 52;
    ASSERT(static_cast<int32_t>(val2) == 52);
    ASSERT(*ptr == 52);

    EXPECT_EXCEPTION(val1["foo"], std::bad_cast);
    EXPECT_EXCEPTION(val1.at("foo"), std::bad_cast);

    val3 = 52;
    ASSERT(val2 == val3);
    ASSERT(val2.get_ptr() != val3.get_ptr());

    val3 = std::move(val2);
    ASSERT(val3 == tag_int(52));
    ASSERT(!val2);

    tag_int& tag = dynamic_cast<tag_int&>(val3.get());
    ASSERT(tag == tag_int(52));
    tag = 21;
    ASSERT(static_cast<int32_t>(val3) == 21);
    val1.set_ptr(std::move(val3.get_ptr()));
    ASSERT(val1.as<tag_int>() == 21);

    ASSERT(val1.get_type() == tag_type::Int);
    ASSERT(val2.get_type() == tag_type::Null);
    ASSERT(val3.get_type() == tag_type::Null);

    val2 = val1;
    val1 = val3;
    ASSERT(!val1 && val2 && !val3);
    ASSERT(val1.get_ptr() == nullptr);
    ASSERT(val2.get() == tag_int(21));
    ASSERT(value(val1) == val1);
    ASSERT(value(val2) == val2);
    val1 = val1;
    val2 = val2;
    ASSERT(!val1);
    ASSERT(val2 == tag_int(21));

    val3 = tag_short(2);
    EXPECT_EXCEPTION(val3 = tag_string("foo"), std::bad_cast);
    ASSERT(val3.get() == tag_short(2));

    val2.set_ptr(make_unique<tag_string>("foo"));
    ASSERT(val2 == tag_string("foo"));
    std::clog << "test_value passed" << std::endl;
}

void test_tag_list()
{
    tag_list list;
    ASSERT(list.el_type() == tag_type::Null);
    EXPECT_EXCEPTION(list.push_back(value(nullptr)), std::bad_cast);

    list.emplace_back<tag_string>("foo");
    ASSERT(list.el_type() == tag_type::String);
    list.push_back(tag_string("bar"));
    EXPECT_EXCEPTION(list.push_back(tag_int(42)), std::bad_cast);
    EXPECT_EXCEPTION(list.emplace_back<tag_compound>(), std::bad_cast);

    ASSERT((list == tag_list{"foo", "bar"}));
    ASSERT(list[0] == tag_string("foo"));
    ASSERT(static_cast<std::string>(list.at(1)) == "bar");

    ASSERT(list.size() == 2);
    EXPECT_EXCEPTION(list.at(2), std::out_of_range);
    EXPECT_EXCEPTION(list.at(-1), std::out_of_range);

    list.set(1, value(tag_string("baz")));
    EXPECT_EXCEPTION(list.set(1, value(nullptr)), std::bad_cast);
    EXPECT_EXCEPTION(list.set(1, value(tag_int(-42))), std::bad_cast);
    ASSERT(static_cast<std::string>(list[1]) == "baz");

    ASSERT(list.size() == 2);
    tag_string values[] = {"foo", "baz"};
    ASSERT(list.end() - list.begin() == int(list.size()));
    ASSERT(std::equal(list.begin(), list.end(), values));

    list.pop_back();
    ASSERT(list == tag_list{"foo"});
    ASSERT(list == tag_list::of<tag_string>({"foo"}));
    ASSERT(tag_list::of<tag_string>({"foo"}) == tag_list{"foo"});
    ASSERT((list != tag_list{2, 3, 5, 7}));

    list.clear();
    ASSERT(list.size() == 0 && list.el_type() == tag_type::String);
    EXPECT_EXCEPTION(list.push_back(tag_short(25)), std::bad_cast);
    EXPECT_EXCEPTION(list.push_back(value(nullptr)), std::bad_cast);

    list.reset();
    ASSERT(list.el_type() == tag_type::Null);
    list.emplace_back<tag_int>(17);
    ASSERT(list.el_type() == tag_type::Int);

    list.reset(tag_type::Float);
    ASSERT(list.el_type() == tag_type::Float);
    list.emplace_back<tag_float>(17.0f);
    ASSERT(list == tag_list({17.0f}));

    ASSERT(tag_list() != tag_list(tag_type::Int));
    ASSERT(tag_list() == tag_list());
    ASSERT(tag_list(tag_type::Short) != tag_list(tag_type::Int));
    ASSERT(tag_list(tag_type::Short) == tag_list(tag_type::Short));

    tag_list short_list = tag_list::of<tag_short>({25, 36});
    ASSERT(short_list.el_type() == tag_type::Short);
    ASSERT((short_list == tag_list{int16_t(25), int16_t(36)}));
    ASSERT((short_list != tag_list{25, 36}));
    ASSERT((short_list == tag_list{value(tag_short(25)), value(tag_short(36))}));

    EXPECT_EXCEPTION((tag_list{value(tag_byte(4)), value(tag_int(5))}), std::bad_cast);
    EXPECT_EXCEPTION((tag_list{value(nullptr), value(tag_int(6))}), std::bad_cast);
    EXPECT_EXCEPTION((tag_list{value(tag_int(7)), value(tag_int(8)), value(nullptr)}), std::bad_cast);
    ASSERT((tag_list(std::initializer_list<value>{})).el_type() == tag_type::Null);
    ASSERT((tag_list{2, 3, 5, 7}).el_type() == tag_type::Int);
    std::clog << "test_tag_list passed" << std::endl;
}

void test_tag_byte_array()
{
    std::vector<int8_t> vec{1, 2, 127, -128};
    tag_byte_array arr{1, 2, 127, -128};
    ASSERT(arr.size() == 4);
    ASSERT(arr.at(0) == 1 && arr[1] == 2 && arr[2] == 127 && arr.at(3) == -128);
    EXPECT_EXCEPTION(arr.at(-1), std::out_of_range);
    EXPECT_EXCEPTION(arr.at(4), std::out_of_range);

    ASSERT(arr.get() == vec);
    ASSERT(arr == tag_byte_array(std::vector<int8_t>(vec)));

    arr.push_back(42);
    vec.push_back(42);

    ASSERT(arr.size() == 5);
    ASSERT(arr.end() - arr.begin() == int(arr.size()));
    ASSERT(std::equal(arr.begin(), arr.end(), vec.begin()));

    arr.pop_back();
    arr.pop_back();
    ASSERT(arr.size() == 3);
    ASSERT((arr == tag_byte_array{1, 2, 127}));
    ASSERT((arr != tag_int_array{1, 2, 127}));
    ASSERT((arr != tag_byte_array{1, 2, -1}));

    arr.clear();
    ASSERT(arr == tag_byte_array());
    std::clog << "test_tag_byte_array passed" << std::endl;
}

void test_tag_int_array()
{
    std::vector<int32_t> vec{100, 200, INT32_MAX, INT32_MIN};
    tag_int_array arr{100, 200, INT32_MAX, INT32_MIN};
    ASSERT(arr.size() == 4);
    ASSERT(arr.at(0) == 100 && arr[1] == 200 && arr[2] == INT32_MAX && arr.at(3) == INT32_MIN);
    EXPECT_EXCEPTION(arr.at(-1), std::out_of_range);
    EXPECT_EXCEPTION(arr.at(4), std::out_of_range);

    ASSERT(arr.get() == vec);
    ASSERT(arr == tag_int_array(std::vector<int32_t>(vec)));

    arr.push_back(42);
    vec.push_back(42);

    ASSERT(arr.size() == 5);
    ASSERT(arr.end() - arr.begin() == int(arr.size()));
    ASSERT(std::equal(arr.begin(), arr.end(), vec.begin()));

    arr.pop_back();
    arr.pop_back();
    ASSERT(arr.size() == 3);
    ASSERT((arr == tag_int_array{100, 200, INT32_MAX}));
    ASSERT((arr != tag_int_array{100, -56, -1}));

    arr.clear();
    ASSERT(arr == tag_int_array());
    std::clog << "test_tag_int_array passed" << std::endl;
}

int main()
{
    test_tag();
    test_get_type();
    test_tag_primitive();
    test_tag_string();
    test_tag_compound();
    test_value();
    test_tag_list();
    test_tag_byte_array();
    test_tag_int_array();
}
