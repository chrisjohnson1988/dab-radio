CXXFLAGS=-std=c++11 -frtti -fexceptions
SOURCES=$(wildcard *.cpp)
FEC=$(wildcard fec/*.c)
MAINS=dab_scan dab_mp2 dab_aac
OBJECTS=$(SOURCES:.cpp=.o) $(FEC:.c=.o)
COMMON_OBJECTS=$(filter-out $(MAINS:=.o),$(OBJECTS))

.PHONY: all clean

all: clean $(MAINS)

$(MAINS): $(COMMON_OBJECTS)
	$(MAKE) $(@:=.o)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ $@.o -o $@ -lusb-1.0

clean:
	$(RM) *.o
	$(RM) $(MAINS)

