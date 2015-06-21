#include "microtest.h"
#include "libnbt.h"
#include <iostream>

using namespace nbt;

void test_get_type()
{
    ASSERT(tag_byte().get_type()   == tag_type::Byte);
    ASSERT(tag_short().get_type()  == tag_type::Short);
    ASSERT(tag_int().get_type()    == tag_type::Int);
    ASSERT(tag_long().get_type()   == tag_type::Long);
    ASSERT(tag_float().get_type()  == tag_type::Float);
    ASSERT(tag_double().get_type() == tag_type::Double);
}

int main()
{
    test_get_type();
}
