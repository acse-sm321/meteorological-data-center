PUBINCL = -I/root/meteorological-data-center/public

PUBCPP = /root/meteorological-data-center/public/_public.cpp

CFLAGS = -g

all:crtsurfdata

crtsurfdata:crtsurfdata.cpp
	g++ $(CFLAGS) -o crtsurfdata crtsurfdata.cpp  $(PUBINCL) $(PUBCPP) -lm -lc
	cp crtsurfdata ../bin/.

clean:
	rm crtsurfdata
