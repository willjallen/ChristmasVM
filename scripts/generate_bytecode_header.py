import json
import os

def indent(level):
	return "\t" * level

DEFINITION_MACROS = """
#ifndef BYTECODE_H
#define BYTECODE_H
\n"""

HEADER_FILES = """
#include <stdint.h>
#include <string>
#include <unordered_map>
\n"""

ENDIF_MACRO = """
#endif
"""

BYTECODE_ENUM_TYPE = """
enum class BYTECODE : uint8_t {
\n"""

def generate_bytecode_enum(bytecode_dict):
	first_bytecode_template = "{comment}\n{indent}{name} = 0x00,\n\n"
	bytecode_template = "{comment}\n{indent}{name},\n\n"
	formatted_bytecodes = []

	for i, bytecode in enumerate(bytecode_dict["bytecode"]):
		comments = "\n".join([f"{indent(1)}// {comment}" for comment in bytecode.get("comments", [])])
		template = first_bytecode_template if i == 0 else bytecode_template
		formatted_bytecodes.append(template.format(indent=indent(1), comment=comments, name=bytecode["name"]))

	bytecode_enum_str = BYTECODE_ENUM_TYPE + "".join(formatted_bytecodes) + indent(0) + "};\n"
	return bytecode_enum_str
		
OBJECT_FROM_NAME_TYPE = """
	const std::unordered_map<std::string, BYTECODE_OBJECT> OBJECT_FROM_NAME_MAP = {
"""
def generate_object_from_name_map(bytecode_dict):
	object_from_name_map_str = OBJECT_FROM_NAME_TYPE

	for bytecode in bytecode_dict["bytecode"]:
		args_formatted = ", ".join([f"ARGUMENT_TYPE::{arg}" for arg in bytecode["args"]])

		bytecode_line = f"{indent(2)}{{\"{bytecode['name']}\", {{BYTECODE::{bytecode['name']}, \"{bytecode['name']}\", {{{args_formatted}}}}}}},\n"

		object_from_name_map_str += bytecode_line

	object_from_name_map_str += f"{indent(1)}}};\n"

	return object_from_name_map_str

NAME_FROM_VALUE_TYPE = """
	const std::unordered_map<BYTECODE, std::string> NAME_FROM_VALUE_MAP = {
"""
def generate_name_from_value_map(bytecode_dict):
	name_from_value_map_str = NAME_FROM_VALUE_TYPE
	for bytecode in bytecode_dict["bytecode"]:
     
		bytecode_line = f"{indent(2)}{{BYTECODE::{bytecode['name']}, \"{bytecode['name']}\"}},\n"

		name_from_value_map_str += bytecode_line

	name_from_value_map_str += f"{indent(1)}}};\n"

	return name_from_value_map_str
 
  
BYTECODE_INFO_NAMESPACE = """
namespace BYTECODE_INFO {
"""

ARGUMENT_TYPE_ENUM = """
	enum class ARGUMENT_TYPE : uint8_t
	{
		REGISTER,
		LITERAL,
		ADDRESS,
	};

\n"""

BYTECODE_OBJECT_STRUCT = """
	struct BYTECODE_OBJECT
	{
		BYTECODE_OBJECT(BYTECODE bytecode,
						std::string name,
						std::vector<ARGUMENT_TYPE> args) : bytecode(bytecode),
														   name(name),
														   args(args)
		{
		}
		BYTECODE bytecode;
		std::string name;
		std::vector<ARGUMENT_TYPE> args;
	};
\n"""
def generate_bytecode_info_namespace(bytecode_dict):
	bytecode_info_namespace = ""
	
	bytecode_info_namespace += BYTECODE_INFO_NAMESPACE
	bytecode_info_namespace	+= ARGUMENT_TYPE_ENUM
	bytecode_info_namespace += BYTECODE_OBJECT_STRUCT
 
	bytecode_info_namespace += generate_object_from_name_map(bytecode_dict)
	bytecode_info_namespace += generate_name_from_value_map(bytecode_dict)
 
	bytecode_info_namespace += "};"
 
	return bytecode_info_namespace
 
 


def generate_header(bytecode_dict):
	header_str = ""
	header_str += DEFINITION_MACROS
	header_str += HEADER_FILES
	
	header_str += generate_bytecode_enum(bytecode_dict)
	header_str += generate_bytecode_info_namespace(bytecode_dict)
 
	header_str += ENDIF_MACRO
	
	return header_str


if __name__ == "__main__":
	try:
		# Construct file paths in a platform-independent way
		base_dir = os.path.dirname(__file__)
		json_path = os.path.join(base_dir, '..', 'src', 'bytecode.json')
		header_path = os.path.join(base_dir, '..', 'src', 'ByteCode.h')

		# Reading the JSON file
		with open(json_path, 'r') as f:
			bytecode_dict = json.load(f)
		
  		# Generate header string
		header_str = generate_header(bytecode_dict)

		# Write the header string to a file
		with open(header_path, 'w') as f:
			f.write(header_str)

	except FileNotFoundError as e:
		print(f"Error: {e}")
	except json.JSONDecodeError as e:
		print(f"Invalid JSON: {e}")
	except IOError as e:
		print(f"I/O Error: {e}")
	except Exception as e:
		print(f"An unexpected error occurred: {e}")