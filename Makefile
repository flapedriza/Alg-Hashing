all: algorisme1.cpp algorisme2.cpp algorisme3.cpp
	g++ -std=c++11 -o algorisme1.x algorisme1.cpp
	g++ -std=c++11 -o algorisme2.x algorisme2.cpp
	g++ -std=c++11 -o algorisme3.x algorisme3.cpp
	
debug: algorisme1.cpp algorisme2.cpp algorisme3.cpp
	g++ -D_GLIBCXX_DEBUG -std=c++11 -o algorisme1.x algorisme1.cpp
	g++ -D_GLIBCXX_DEBUG -std=c++11 -o algorisme2.x algorisme2.cpp
	g++ -D_GLIBCXX_DEBUG -std=c++11 -o algorisme3.x algorisme3.cpp

algorisme1: algorisme1.cpp
	g++ -std=c++11 -o algorisme1.x algorisme1.cpp

algorisme2: algorisme2.cpp
	g++ -std=c++11 -o algorisme2.x algorisme2.cpp

algorisme3: algorisme3.cpp
	g++ -std=c++11 -o algorisme3.x algorisme3.cpp

clean:
	rm -f *.x