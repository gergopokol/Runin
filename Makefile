GOOGLE_TEST_INCLUDE = ${DEPS_DIR}/gtest/usr/include
GOOGLE_TEST_LIB = ${DEPS_DIR}/gtest/usr/src/gtest
GOOGLE_TEST_LIB2 =  ${DEPS_DIR}/gtest/usr/lib/x86_64-linux-gnu
GOOGLE_TEST_LIB3 = ${DEPS_DIR}/gtest/usr/lib/x86_64-linux-gnu/pkgconfig

G++ = g++
G++_FLAGS = -c -Wall -I $(GOOGLE_TEST_INCLUDE) 
LD_FLAGS = -l $(GOOGLE_TEST_LIB) -l $(GOOGLE_TEST_LIB2) -l $(GOOGLE_TEST_LIB3) -l pthread

OBJECTS = critical_field.o growth_rate.o test_phys.o
TARGET = TEST

all:$(TARGET)

$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LD_FLAGS)

%.o: %.cpp
	$(G++) $(G++_FLAGS) $<

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean