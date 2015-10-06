all_checked:isutil_checked isdecide_checked
	touch all_checked
isutil_checked:isutil
	./isutil && touch isutil_checked
isutil:isutil.cpp ../isutil.cpp
	g++ isutil.cpp ../isutil.cpp -I.. -std=gnu++11 -o isutil
isdecide_checked:isdecide
	./isdecide && touch isdecide_checked
isdecide:isdecide.cpp ../isdecide.cpp ../isutil.cpp
	g++ isdecide.cpp ../isdecide.cpp ../isutil.cpp -I.. -std=gnu++11 -o isdecide
