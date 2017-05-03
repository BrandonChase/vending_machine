CXX= g++
CXXFLAGS= -Wall -g
LDFLAGS= 
INCLUDE= 

SRCDIR= .
BINDIR= .
TARGET= $(BINDIR)/vm

SOURCE= $(wildcard $(SRCDIR)/*.cpp)

all:
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(SOURCE) $(LDFLAGS) -o $(TARGET)

clean:
	rm $(TARGET)
