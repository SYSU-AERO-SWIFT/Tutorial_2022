#include "Recovery.h"

int main() {
	Recovery ret;
	string readpath;
	string savepath;
	cin>>readpath>>savepath;
	ret.process(readpath);
	ret.saveAndShowResult(savepath);
	return 0;
}
