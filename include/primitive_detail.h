#ifndef PRIMITIVE_DETAIL_H_INCLUDED
#define PRIMITIVE_DETAIL_H_INCLUDED

namespace nbt
{

namespace detail
{
    ///Meta-struct that holds the tag_type value for a specific primitive type
    template<class T> struct get_primitive_type;

    template<> struct get_primitive_type<int8_t>  : public std::integral_constant<tag_type, tag_type::Byte> {};
    template<> struct get_primitive_type<int16_t> : public std::integral_constant<tag_type, tag_type::Short> {};
    template<> struct get_primitive_type<int32_t> : public std::integral_constant<tag_type, tag_type::Int> {};
    template<> struct get_primitive_type<int64_t> : public std::integral_constant<tag_type, tag_type::Long> {};
    template<> struct get_primitive_type<float>   : public std::integral_constant<tag_type, tag_type::Float> {};
    template<> struct get_primitive_type<double>  : public std::integral_constant<tag_type, tag_type::Double> {};
}

}

#endif // PRIMITIVE_DETAIL_H_INCLUDED
