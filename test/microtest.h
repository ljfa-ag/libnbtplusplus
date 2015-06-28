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
#ifndef MICROTEST_H
#define MICROTEST_H

#include <iostream>

#define FAIL_TEST { std::cerr << "Assertion failed at " __FILE__ ":" << __LINE__ << std::endl; \
    exit(EXIT_FAILURE); }
#define ASSERT(expr) { if(!(expr)) FAIL_TEST }
#define EXPECT_EXCEPTION(expr, type) { \
    try { (expr); std::cerr << "Expected " #type " to be thrown, got no exception instead" << std::endl; FAIL_TEST } \
    catch(type&) {} \
    catch(...) { std::cerr << "Expected " #type " to be thrown, got something else instead" << std::endl; FAIL_TEST } }

#endif
