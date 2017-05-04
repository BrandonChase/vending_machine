CXX= g++ -std=c++11
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
