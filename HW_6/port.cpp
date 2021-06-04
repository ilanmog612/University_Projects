#include "port.h"
#include <iostream>

#define NO_PORT -1
#define DELIMITERS ",= "
#define NOT_FOUND -1






Port::Port(String pattern) : Field(pattern) {
    this->pattern = String(pattern);
    low_value = NO_PORT;
    high_value = NO_PORT;
}


bool Port::set_value(String val){
	String *values_string_arr;
	size_t *size = new size_t;
	String borders = String(val);
	borders.split("- ", &values_string_arr, size);
	low_value = (values_string_arr)->to_integer();
	high_value = (values_string_arr+1)->to_integer();
	delete[] values_string_arr;
	delete size;
	return true;
}

bool Port::match_value(String packet) const{
	String *values_string_arr;
	size_t *size = new size_t;
	String packet_to_parse = String(packet);
	int find_index = NOT_FOUND;
	int val = 0;
	packet_to_parse.split(" ,=", &values_string_arr, size);
	for (size_t i = 0; i < *size; i++) {
        String tmp_str =  (values_string_arr+i)->trim();
	    if (tmp_str.equals(pattern) == 0){
			find_index = i;
		}
	}

	if (find_index == NOT_FOUND){
		 delete[] values_string_arr;
		  delete size;
        return false;
	}


    val = (values_string_arr + find_index + 1)->to_integer();
    delete[] values_string_arr;
    delete size;
	return (val >= low_value && val <= high_value);
}








