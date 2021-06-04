#ifndef IP_H
#define IP_H


#include "field.h"
#define ip_SIZE 32

class ip: public Field
{
private :
    String pattern;

public:
    /**
        * @brief num of bits to consider in rule
        */
    int offset;
    /**
         * @brief bit array for ip address
         */
    int bit_arr[ip_SIZE];
     ip (String pattern);
     /**
          * @brief set offset
          */
    bool set_value(String val);
    /**
        * @brief Check if packet matches the rule given by pattern
        */
    bool match_value(String packet) const;
};
#endif
