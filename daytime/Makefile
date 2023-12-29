CXX = g++
CXXFLAGS = -std=c++11

udp_daytime_client: daytime.cpp
	$(CXX) $(CXXFLAGS) -o udp_daytime_client daytime.cpp

.PHONY: clean
clean:
	rm -f udp_daytime_client
