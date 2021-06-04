#include "ip.h"
#define EMPTY_VAL 0
#define NO_OFFSET -1
#define DELIMITERS "./ "
#define NOT_FOUND -1



//turning integer to bit array display
namespace My_Func{
    void int_to_bit_arr (int *arr, int integer);
    void int_to_bit_arr (int *arr, int integer, int start){
        for(int i=start; integer > 0; i++){
            arr[i]= integer % 2;
            integer = integer / 2;
        }
    }
}


ip::ip(String pattern) : Field(pattern) {
    this->pattern = String(pattern);
    for (int i = 0; i < ip_SIZE ; i++){
        bit_arr[i] = EMPTY_VAL;
    }
    offset= NO_OFFSET;
}


bool ip::set_value(String val){
	//parsing by DELIMITERS
	String *values_string_arr;
	size_t *size = new size_t;
	String ip_str_val = String(val);
	ip_str_val.split(DELIMITERS, &values_string_arr, size);
	for (size_t i = 0; i < *size-1; i++) {
       int tmp_int = (values_string_arr+i)->to_integer();
       My_Func::int_to_bit_arr(bit_arr, tmp_int, ((*size-2-i)*8));
	}
    offset = (values_string_arr+*size-1)->to_integer();

    delete[] values_string_arr;
    delete size;
	return true;
}
bool ip::match_value(String packet) const{
	//parsing by DELIMITERS2
	String *values_string_arr;
	size_t *size = new size_t;
	String packet_to_parse = String(packet);
	int find_index = NOT_FOUND;
	packet_to_parse.split(" ,=", &values_string_arr, size);
	for (size_t i = 0; i < *size; i++) {
        String tmp_str =  ((values_string_arr+i)->trim());
	    if (tmp_str.equals(pattern) == 0){
			find_index = i;
		}
	}
	if (find_index == NOT_FOUND){
		delete[] values_string_arr;
		delete size;
        return false;
	}
	//creating bit array all zeros
	String *tmp_arr;
	int bit_arr_tmp[ip_SIZE];
	for(int i = 0; i<ip_SIZE; i++){
        bit_arr_tmp[i]=0;
	}
	//splitting by '.'an converting each num to bit array display
    size_t *size2 = new size_t;
	(values_string_arr + find_index + 1)->split(".", &tmp_arr, size2);
	for (size_t i = 0; i < *size2; i++) {
       int tmp_int = (tmp_arr+i)->to_integer();
       My_Func::int_to_bit_arr(bit_arr_tmp, tmp_int, ((*size2-i-1)*8));
	}
	delete size2;
	delete[] tmp_arr;
	delete[] values_string_arr;
	delete size;
	//comparing bit arrays
	for (int i = ip_SIZE-1; i >= ip_SIZE-offset; i--){

        if (bit_arr_tmp[i] != bit_arr[i]){

            return false;
        }
    }
    return true;
}




