#include "field.h"

Field::Field(String pattern){
	this->pattern = String(pattern);}
Field::~Field(){};
bool Field::match(String packet) {
    return match_value(packet);
}
