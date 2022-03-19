PUBINCL = -I/root/meteorological-data-center/public

PUBCPP = /root/meteorological-data-center/public/_public.cpp

CFLAGS = -g

all:crtsurfdata1 crtsurfdata2

crtsurfdata1:crtsurfdata1.cpp
	g++ $(CFLAGS) -o crtsurfdata1 crtsurfdata1.cpp  $(PUBINCL) $(PUBCPP) -lm -lc
	cp crtsurfdata1 ../bin/.

crtsurfdata2:crtsurfdata2.cpp
	g++ $(CFLAGS) -o crtsurfdata2 crtsurfdata2.cpp  $(PUBINCL) $(PUBCPP) -lm -lc
	cp crtsurfdata2 ../bin/.

clean:
	rm crtsurfdata1
	rm crtsurfdata2
