#ifndef RESULT_CODE_H
#define RESULT_CODE_H

#include <string>


struct RESULT {
	RESULT(int value, std::string name) : value(value), name(name) {}
	int value;
	std::string name;
};


namespace RESULT_CODE{
	const RESULT UNSPECIFIED_FAILURE = RESULT(0, "UNSPECIFIED_FAILURE");
	const RESULT SUCCESS = RESULT(1, "SUCCESS");
	const RESULT OUT_OF_MEMORY_ERROR = RESULT(2, "OUT_OF_MEMORY_ERROR");
	const RESULT CLI_ERROR = RESULT(3, "CLI_ERROR");
}

#endif
