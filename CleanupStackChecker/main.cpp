#include "CheckCleanupStackAction.h"
#include "CheckCleanupStackConsumer.h"
#include "helper/ErrorMgr.h"
#include "clang/Tooling/Tooling.h"

#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;
using namespace Fang;

int main(int argc, char *argv[])
{
	if (argc > 1) {
        string filePath = argv[1];
		ifstream fs(filePath);
		if (!fs.is_open()) {
			cerr << "failed to load file: " << filePath << endl;
			return 1;
		}

		stringstream buffer;
		buffer << fs.rdbuf();
        fs.close();
		string file_contents = buffer.str();
       
		clang::tooling::runToolOnCode(std::unique_ptr<CheckCleanupStackAction>(new CheckCleanupStackAction()), file_contents);
        
        ErrorMgr &errMgr = ErrorMgr::getInstance();
        errMgr.Output();
    } else {
        cerr << "Usage : CleanupStackChecker <filename>" << endl;
    }

	return 0;
}

