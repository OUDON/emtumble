CXX      = g++-6
CXXFLAGS = -std=c++14 -O2 -Wall -Wextra -Wshadow -g 
LIBS     = 
LDLIBS   = 
TARGET   = bin/emtumble
OBJDIR   = ./obj
SOURCES  = $(wildcard *.cpp)
OBJECTS  = $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

$(TARGET) : $(OBJECTS) $(LIBS)
	$(CXX) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o: %.cpp
	@[ -d $(OBJDIR) ]
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJECTS) $(TARGET)
