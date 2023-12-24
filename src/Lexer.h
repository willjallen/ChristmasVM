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
		Lexer(std::string file) : file(file) {}
		int parse();

	private:
		std::string file;

};
