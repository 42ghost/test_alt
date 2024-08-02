CXX=g++
CXXFLAGS=-std=c++17 -Wall -c -fPIC
LDFLAGS=-shared -Wl,-soname,libmylib.so
CURL_FLAGS=-lcurl

LIB_NAME=libmylib.so

JSONHandler_o=JSONHandler.o
CURLRequest_o=CURLRequest.o
Comparator_o=Comparator.o
main_o=main.o

all: $(LIB_NAME) main

$(JSONHandler_o): JSONHandler.cpp JSONHandler.h
	$(CXX) $(CXXFLAGS) $< -o $@

$(CURLRequest_o): CURLRequest.cpp CURLRequest.h
	$(CXX) $(CXXFLAGS) $< -o $@

$(Comparator_o): Comparator.cpp Comparator.h 
	$(CXX) $(CXXFLAGS) $< -o $@

$(LIB_NAME): $(JSONHandler_o) $(CURLRequest_o) $(Comparator_o)
	$(CXX) $(LDFLAGS) $^ $(CURL_FLAGS) -o $@

main: $(LIB_NAME) $(main_o)
	$(CXX) $(main_o) -L. -lmylib $(CURL_FLAGS) -o main

clean:
	rm -f *.o $(LIB_NAME)

install: $(LIB_NAME)
	cp $(LIB_NAME) /usr/lib/

uninstall:
	rm /usr/lib/$(LIB_NAME)

