all_checked:isutil_checked isdecide_checked
	touch all_checked
isutil_checked:isutil_check
	./isutil_check && touch isutil_checked
isutil_check:isutil.cpp ../isutil.cpp
	g++ isutil.cpp ../isutil.cpp -I.. -std=gnu++11 -o isutil_check
isdecide_checked:isdecide_check
	./isdecide_check && touch isdecide_checked
isdecide_check:isdecide.cpp ../isdecide.cpp ../isutil.cpp
	g++ isdecide.cpp ../isdecide.cpp ../isutil.cpp -I.. -std=gnu++11 -o isdecide_check
.PHONY:clean
clean:
	rm -f *_checked *_check
