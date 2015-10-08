#include <isdectree.h>
#include <id3.h>
#include <isutil.h>

#include <vector>
#include <sstream>
#include <string>

using namespace std;
using namespace isdectree;

#define BASENAME "funny.csv"
#define DATA_COL 4 //exclude the result
#define DATA_LINE 100

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
	Node *node = algorithm_id3(meta,data);
	FILE *fpout = fopen((string(BASENAME) + "-out.dot").c_str(),"w");
	fprintf(fpout,"digraph{\n");
	util_dotize(node,fpout);
	fprintf(fpout,"}\n");
	//system((string("dot -Tsvg -o ") + BASENAME + "-out.svg " + BASENAME + "-out.dot").c_str());
	return 0;
}
