#include <filesystem>
#include <fstream>

enum TokenType {
	PLACE,
	POINTER,
	BOOL,
	INT,
	UINT,
	ADDRESS_OF,
	LOAD,
	STORE,
	JUMP,
	JUMPC,
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE,
	SEMICOLON
};

struct Token {
	size_t lineNumber;
	size_t charNumber;
	TokenType tokenType;
};

class Lexer{
	public:
		Lexer(std::filesystem::path filePath) : filePath(filePath) {}
		std::vector<Token> tokenize();

	private:
		std::filesystem::path filePath;

};
