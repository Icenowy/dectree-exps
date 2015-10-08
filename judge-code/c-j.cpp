#include <isdectree.h>
#include <id3.h>
#include <isutil.h>
#include <isdecide.h>

#include <vector>
#include <sstream>
#include <string>

using namespace std;
using namespace isdectree;

#define BASENAME "final.csv"
#define DATA_COL 4 //exclude the result
#define DATA_LINE 16000
#define JUDGE_BASENAME "takeout.csv"
#define JUDGE_LINE 1500

int main()
{
	ostringstream oss;	
	FILE **fps = new FILE*[DATA_COL+1];
	for (int i = 0;i<DATA_COL+1;i++) {
		oss.str("");
		oss << BASENAME << "-nohead-" << i+2 << "-enumized";
		fps[i] = fopen(oss.str().c_str(),"r");
	}
	DatasetMetadata meta;
	for (int i = 0;i<DATA_COL;i++)
		meta.maxenum.push_back(0); // init maxenum
	meta.maxresult = 0;
	meta.number_count = 0;
	meta.enum_count = DATA_COL;
	vector<Datum> data;
	for (int l = 0;l<DATA_LINE;l++) {
		Datum dt;
		for(int i = 0;i<DATA_COL;i++) {
			EnumType enumval;
			fscanf(fps[i],"%u",&enumval);
			dt.enums.push_back(enumval);
			if(meta.maxenum[i] < enumval)
				meta.maxenum[i] = enumval;
		}
		EnumType resval;
		fscanf(fps[DATA_COL],"%u",&resval);
		dt.result = resval;
		if(meta.maxresult < resval)
			meta.maxresult = resval;
		data.push_back(dt);
	}
	for (int i = 0;i<DATA_COL+1;i++) {
		fclose(fps[i]);
	}
	Node *node = algorithm_id3(meta,data);
	data.clear();
	for (int i = 0;i<DATA_COL;i++) {
		oss.str("");
		oss << JUDGE_BASENAME << "-nohead-" << i+2 << "-enumized";
		fps[i] = fopen(oss.str().c_str(),"r");
	}
	for (int l = 0;l<JUDGE_LINE;l++) {
		Datum dt;
		for(int i = 0;i<DATA_COL;i++) {
			EnumType enumval;
			fscanf(fps[i],"%u",&enumval);
			dt.enums.push_back(enumval);
			if(meta.maxenum[i] < enumval)
				meta.maxenum[i] = enumval;
		}
		data.push_back(dt);
	}
	for(Datum dt : data) {
		if(decide(dt,node)-1)
			printf("False\n");
		else
			printf("True\n"); //FIXME: HARD CODE
	}
	return 0;
}
