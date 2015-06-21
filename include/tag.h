#ifndef TAG_H_INCLUDED
#define TAG_H_INCLUDED

#include <cstdint>

namespace nbt
{

///Tag type values used in the binary format
enum class tag_type : int8_t
{
    End = 0,
    Byte = 1,
    Short = 2,
    Int = 3,
    Long = 4,
    Float = 5,
    Double = 6,
    Byte_Array = 7,
    String = 8,
    List = 9,
    Compound = 10,
    Int_Array = 11
};

///Base class for all NBT tag classes
class tag
{
public:
    //Virtual destructor
    virtual ~tag() noexcept {}

    ///Returns the type of the tag
    virtual tag_type get_type() const noexcept = 0;
};

}

#endif // TAG_H_INCLUDED
