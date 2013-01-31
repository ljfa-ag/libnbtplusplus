CXX = g++
LD = g++
AR = ar

CXXFLAGS = -Wall -Wextra -std=c++11 -g
LDFLAGS = 

BOOST_INCLUDE = boost_include_path
BOOST_LIB = boost_library_path
BOOST_IOSTREAMS = -lboost_iostreams

NBT_LIB = libnbt++.a
TEST_PROG = nbttest

INSTALL_PREFIX = /usr/local

SRC = src
INCLUDE = include
OBJS = endian_str.o read.o tag.o tag_array.o tag_compound.o tag_list.o

all: $(NBT_LIB) test

$(NBT_LIB): $(OBJS)
	$(AR) -r -s libnbt++.a $?

%.o:
	$(CXX) $(CXXFLAGS) -I $(INCLUDE) -I $(BOOST_INCLUDE) -c -o $@ $<

test.o: test.cpp include/tag.h include/tag_scalar.h include/endian_str.h \
 include/tag_base.h include/tag_byte_array.h include/tag_string.h \
 include/tag_list.h include/tag_compound.h include/tag_int_array.h \
 include/nbt_io.h
	$(CXX) $(CXXFLAGS) -I $(INCLUDE) -I $(BOOST_INCLUDE) -c -o $@ $<

test: $(TEST_PROG)

$(TEST_PROG): test.o $(NBT_LIB)
	$(LD) $(LDFLAGS) -L $(BOOST_LIB) -o $(TEST_PROG) $^ $(BOOST_IOSTREAMS)

install: $(NBT_LIB)
	mkdir -p $(INSTALL_PREFIX)/include/NBT $(INSTALL_PREFIX)/lib
	cp $(INCLUDE)/* $(INSTALL_PREFIX)/include/NBT
	cp $(NBT_LIB) $(INSTALL_PREFIX)/lib

clean:
	rm -f *.o $(NBT_LIB) $(TEST_PROG)

.PHONY: all test install clean

endian_str.o: src/endian_str.cpp include/endian_str.h
read.o: src/read.cpp include/tag.h include/tag_scalar.h \
 include/endian_str.h include/tag_base.h include/tag_byte_array.h \
 include/tag_string.h include/tag_list.h include/tag_compound.h \
 include/tag_int_array.h include/nbt_io.h include/endian_str.h
tag.o: src/tag.cpp include/tag_string.h include/tag_base.h \
 include/endian_str.h include/nbt_io.h
tag_array.o: src/tag_array.cpp include/tag_byte_array.h \
 include/tag_base.h include/tag_int_array.h include/endian_str.h
tag_compound.o: src/tag_compound.cpp include/tag_compound.h \
 include/tag_base.h
tag_list.o: src/tag_list.cpp include/tag_list.h include/tag_base.h \
 include/endian_str.h