
CXXFLAGS := -Wall 

INC_TEXT = -Iinc/text
INC_DATA = -Iinc/data
INC_UTIL = -Iinc/util

TEXT = bin/text_shift.o
DATA = 
UTIL = bin/util_galois.o

.PHONY: all clean

all: $(UTIL) $(TEXT) $(DATA)

bin/util_%.o: src/util/%.cpp inc/util/%.h bin
	$(CXX) $(CXXFLAGS) $(INC_UTIL) -c -o $@ $<

bin/text_%.o: src/text/%.cpp inc/text/%.h bin
	$(CXX) $(CXXFLAGS) $(INC_TEXT) -c -o $@ $<

bin/data_%.o: src/data/%.cpp inc/data/%.h bin
	$(CXX) $(CXXFLAGS) $(INC_DATA) -c -o $@ $<

bin:
	mkdir bin

clean:
	$(RM) bin/*.o
