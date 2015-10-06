all_checked:isutil_checked
	touch all_checked
isutil_checked:isutil
	./isutil && touch isutil_checked
isutil:isutil.cpp ../isutil.cpp
	g++ isutil.cpp ../isutil.cpp -I.. -std=gnu++11 -o isutil
