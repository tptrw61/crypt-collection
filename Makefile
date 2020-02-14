
CXXFLAGS := -Wall 

#INC_TEXT = -Iinc/text
#INC_DATA = -Iinc/data
#INC_UTIL = -Iinc/util

TEXT = bin/text_shift.o
DATA = 
UTIL = bin/util_galois.o
DRIV = bin/driv_text_shift.o

.PHONY: all clean

bin/crypt: bin/crypt.o $(UTIL) $(TEXT) $(DATA) $(DRIV)
	$(CXX) $(CXXFLAGS) -o $@ $^

bin/crypt.o: src/crypt.cpp inc/crypt.h inc/text_cipher.h inc/data_cipher.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/util_%.o: src/util/%.cpp inc/util/%.h bin
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/text_%.o: src/text/%.cpp inc/text/%.h bin
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/data_%.o: src/data/%.cpp inc/data/%.h bin
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/driv_text_%.o: src/driver/text/%.cpp inc/text/%.h bin
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/driv_data_%.o: src/driver/data/%.cpp inc/data/%.h bin
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin:
	mkdir bin

clean:
	$(RM) bin/*.o
