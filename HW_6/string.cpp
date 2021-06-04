#include <stddef.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "string.h"

#define SPACE 32
#define EMPTY_STRING ""
#define ZERO_STRING "0"
#define FAIL -1


//aux function for counting all sub strings created after parsing
namespace My_Func1{

 static int string_parsing_counting (const char *str, const char *delimiters);
 static int string_parsing_counting (const char *str, const char *delimiters){
        char *parse = new char [strlen(str)+1];
        strcpy(parse, str);
        char *tmp_iterator = parse;
        int counter = 0;
        tmp_iterator = strtok(tmp_iterator, delimiters);
        while (tmp_iterator){
            counter++;
            tmp_iterator = strtok(NULL, delimiters);

        }

        delete[] parse;

        return counter;
    }
}


String::String(){
    data = new char;
    strcpy(data, EMPTY_STRING);
    length = 0;
    }
String::String(const String &str){
    data = strcpy(new char [str.length+1], str.data);
    length = str.length;
    }
String::String(const char *str){

	 length = strlen(str);
	    data = new char[length+1];
	    strcpy(data, str);
    }

String::~String() { delete[] data;}

String& String::operator=(const String &rhs){
    if(this == &rhs){
        return *this;
    }
    delete data;
    data = strcpy(new char [rhs.length+1], rhs.data);
    length = strlen(rhs.data);
    return *this;
    }


String& String::operator=(const char *str){
    delete data;
    data = strcpy(new char [strlen(str)+1], str);
    length = strlen(str);
    return *this;
    }


bool String::equals(const char* rhs) const{
    if(strcmp(data , rhs)){
        return true;
    }
    return false;
}

bool String::equals(const String &rhs) const{return equals(rhs.data);}

void String::split(const char *delimiters, String **output,
		size_t *size) const{
    int counter = My_Func1::string_parsing_counting(data, delimiters);
    *size = counter;
    if (output == NULL){
        return;
    }
    *output = new String [counter];
    char *tmp_str = new char [strlen(data)+1];
    strcpy(tmp_str, data);
    char *tmp_ptr =  tmp_str;
    tmp_ptr = strtok(tmp_ptr , delimiters);
    while (tmp_ptr){
        String obj_tmp = String(tmp_ptr);
        **output = obj_tmp;
        (*output)++;

        tmp_ptr = strtok(NULL, delimiters);


    }
    delete[] tmp_str;


    *output = *output - counter;
}

int String::to_integer() const{
    int result = atoi(data);
    if(result == 0 && strcmp(data,ZERO_STRING)){
       return FAIL;
    }
    return result;
}

String String::trim()const{
    int length = strlen(data);
    int right_trim_index, left_trim_index;
    right_trim_index = 0, left_trim_index = length-1;

    while( ((int)*(data+right_trim_index)) == SPACE &&
    		right_trim_index < length ){
        right_trim_index++;
    }
    while( ((int)*(data+left_trim_index)) == SPACE && right_trim_index > 0 ){
        left_trim_index--;
    }
    int new_length = left_trim_index-right_trim_index+1;
    char *new_data = new char[new_length + 1];
    strncpy(new_data, data+right_trim_index, new_length);
    String new_string = String(new_data);
    delete[] new_data;
    return new_string;
}



