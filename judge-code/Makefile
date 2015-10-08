all: m s-dt c-dt
.PHONY: all
m: m.cpp ../id3.cpp ../isutil.cpp
	g++ m.cpp ../id3.cpp ../isutil.cpp -std=gnu++11 -I.. -o m
s-dt: s-dt.cpp ../id3.cpp ../isutil.cpp
	g++ s-dt.cpp ../id3.cpp ../isutil.cpp -std=gnu++11 -I.. -o s-dt
c-dt: c-dt.cpp ../id3.cpp ../isutil.cpp
	g++ c-dt.cpp ../id3.cpp ../isutil.cpp -std=gnu++11 -I.. -o c-dt
