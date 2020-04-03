GOOGLE_TEST_INCLUDE = ../mingw/msys/1.0/home/porda/googletest-master/googletest/include
GOOGLE_TEST_INCLUDE2 = ../mingw/include
GOOGLE_TEST_LIB = gtest


G++ = g++
G++_FLAGS = -c -Wall -I $(GOOGLE_TEST_INCLUDE) -I $(GOOGLE_TEST_INCLUDE2)
LD_FLAGS = -L c:/mingw/lib -l $(GOOGLE_TEST_LIB) -l pthread

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