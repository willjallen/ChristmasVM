/**
 * 
	<program> ::= <statement> | <statement> <program>

	<statement> ::= <operation> | <operation> <argument> | <operation> <argument> <argument>

	<operation> ::= "AddressOf" | "Load" | "Store" | "Jump" | "JumpC" | "Add" | "Subtract" | "Multiply" | "Divide"

	<argument> ::= <register> | <type>

	<register> ::= "REG_A" | "REG_B" | "REG_PC"

	<type> ::= <place> | <pointer> | <bool> | <int> | <uint>

	<place> ::= "PLACE(" <number> ")"
	<pointer> ::= "POINTER(" <number> ")"
	<bool> ::= "TRUE" | "FALSE"
	<int> ::= <signed_number>
	<uint> ::= <number>

	<number> ::= <digit> | <digit> <number>
	<signed_number> ::= <number> | "-" <number>
	<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"

 */

class Parser {

};
