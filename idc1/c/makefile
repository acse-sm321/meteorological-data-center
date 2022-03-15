PUBINCL = -I/cpp-weather-data-center/public

PUBCPP = /root/cpp-weather-data-center/public/_public.cpp

CFLAGS = -g

all:crtsurfdata1

crtsurfdata1:crtsurfdata1.cpp
	g++ $(CFLAGS) -o crtsurfdata1 crtsurfdata1.cpp  $(PUBINCL) $(PUBCPP) -lm -lc
	cp crtsurfdata1 ../bin/.

clean:
	rm crtsurfdata1