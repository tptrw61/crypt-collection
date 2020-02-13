
CXXFLAGS := -Wall 

INC_TEXT = -Iinc/text
INC_DATA = -Iinc/data
INC_TOOLS = -Iinc/tools

TEXT = bin/text_shift.o
DATA = 
TOOLS = bin/tools_galois.o

.PHONY: all clean

all: $(TOOLS) $(TEXT) $(DATA)

bin/tools_%.o: src/tools/%.cpp inc/tools/%.h bin
	$(CXX) $(CXXFLAGS) $(INC_TOOLS) -c -o $@ $<

bin/text_%.o: src/text/%.cpp inc/text/%.h bin
	$(CXX) $(CXXFLAGS) $(INC_TEXT) -c -o $@ $<

bin/data_%.o: src/data/%.cpp inc/data/%.h bin
	$(CXX) $(CXXFLAGS) $(INC_DATA) -c -o $@ $<

bin:
	mkdir bin

clean:
	$(RM) bin/*.o
