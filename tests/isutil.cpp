#include <isutil.h>
#include <cassert>
#include <iostream>

int main()
{
	isdectree::Divide dv;
	dv.decisionType = isdectree::Number;
	dv.paramater = 0;
	dv.threshold = 1.0;
	
	isdectree::Datum dt;
	dt.numbers.push_back(0.5);
	assert(!util_datajudge(dv,dt));

	dt.numbers.clear();
	dt.numbers.push_back(2.0);
	assert(util_datajudge(dv,dt));

	dt.numbers.clear();
	dv.decisionType = isdectree::Enum;
	dv.judgment.insert(1);
	dt.enums.push_back(0);
	assert(!util_datajudge(dv,dt));

	dt.enums.clear();
	dt.enums.push_back(1);
	assert(util_datajudge(dv,dt));

	dt.numbers.clear();
	dt.enums.clear();

	dt.enums.push_back(1);
	std::vector<isdectree::Datum> dtv;
	dtv.push_back(dt);
	dt.enums.clear();
	dt.enums.push_back(0);
	dtv.push_back(dt);

	std::pair<std::vector<isdectree::Datum>, std::vector<isdectree::Datum> > dtvpr = util_datadivide(dv,dtv);
	assert(dtvpr.first.size() == 1);
	assert(dtvpr.second.size() == 1);

	std::cout << util_divide_stringize(dv) << std::endl;

	return 0;
}
