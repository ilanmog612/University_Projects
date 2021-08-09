#include <iostream>
#include "string.h"
#include "port.h"
#include "ip.h"
#include "input.h"
#include "field.h"
#define DELIMITERS " ,""="
#define RULE_TYPE 0 
#define RULE_LIMITS 1
#define ERROR -1




int main(int argc, char **argv) {

	if( check_args( argc, argv) == 0 )
	{
	String *values_string_arr;
		size_t *size = new size_t;
		String parsed_rule = String(argv[1]);
		parsed_rule.split(DELIMITERS, &values_string_arr, size);
		Field *field;

		if( !(values_string_arr[RULE_TYPE].equals(String("dst-port"))) ||
				!(values_string_arr[RULE_TYPE].equals(String("src-port"))) ){
							field = new Port(values_string_arr[RULE_TYPE]);
						}
		if(!(values_string_arr[RULE_TYPE].equals(String("dst-ip"))) ||
				!(values_string_arr[RULE_TYPE].equals(String("src-ip"))) ){
			field = new ip(values_string_arr[RULE_TYPE]);
		}

		field->set_value(values_string_arr[RULE_LIMITS]);

		delete[] values_string_arr;
		delete size;
		parse_input(*field);
		delete field;


    return 0;
	}
	else{

		return ERROR;
	}



}
