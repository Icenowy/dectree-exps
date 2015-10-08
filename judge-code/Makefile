all: m s-dt c-dt s-j c-j
.PHONY: all
m: m.cpp ../id3.cpp ../isutil.cpp
	g++ m.cpp ../id3.cpp ../isutil.cpp -std=gnu++11 -I.. -o m $(CXXFLAGS)
s-dt: s-dt.cpp ../id3.cpp ../isutil.cpp
	g++ s-dt.cpp ../id3.cpp ../isutil.cpp -std=gnu++11 -I.. -o s-dt $(CXXFLAGS)
s-j: s-j.cpp ../id3.cpp ../isutil.cpp
	g++ s-j.cpp ../id3.cpp ../isutil.cpp ../isdecide.cpp -std=gnu++11 -I.. -o s-j $(CXXFLAGS)
c-dt: c-dt.cpp ../id3.cpp ../isutil.cpp
	g++ c-dt.cpp ../id3.cpp ../isutil.cpp -std=gnu++11 -I.. -DSIMP -o c-dt $(CXXFLAGS)
c-j: c-j.cpp ../id3.cpp ../isutil.cpp
	g++ c-j.cpp ../id3.cpp ../isutil.cpp ../isdecide.cpp -std=gnu++11 -I.. -DSIMP -o c-j $(CXXFLAGS)
