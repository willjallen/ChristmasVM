#include <regex>

#include <fstream>
#include "Lexer.h"

std::vector<Token> Lexer::tokenize(){
	std::fstream fileStream(filePath.native(), std::fstream::in);

	/* fileStream.open(); */
		
	while(!fileStream.eof()){

	}
	return std::vector<Token>();
}

