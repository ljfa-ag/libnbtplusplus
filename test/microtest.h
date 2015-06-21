#ifndef MICROTEST_H
#define MICROTEST_H

#include <iostream>

#define FAIL_TEST { std::cerr << "Assertion failed at " __FILE__ ":" << __LINE__ << std::endl; \
    exit(EXIT_FAILURE); }
#define ASSERT(expr) { if(!(expr)) FAIL_TEST }
#define EXPECT_EXCEPTION(expr, type) { \
    try { (expr); std::cerr << "Expected " #type " to be thrown" << std::endl; FAIL_TEST } \
    catch(type&) {} \
    catch(...) { std::cerr << "Expected " #type " to be thrown" << std::endl; FAIL_TEST } }

#endif
