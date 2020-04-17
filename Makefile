GOOGLE_TEST_INCLUDE = deps/gtest/usr/include
GOOGLE_TEST_LIB = gtest

G++ = g++
G++_FLAGS = -c -Wall -std=c++11 -I $(GOOGLE_TEST_INCLUDE) 
LD_FLAGS = -L ${TRAVIS_BUILD_DIR}/deps -l $(GOOGLE_TEST_LIB)  -l pthread

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