#ifndef PORT_H
#define PORT_H


#include "field.h"

class Port: public Field
{
private :
    String pattern;


public:
    /**
        * @brief low port num and high port num
        */
        int low_value;
        int high_value;
     Port (String pattern);
     /**
         * @brief sets low_value & high_value
         */
    bool set_value(String val);
    /**
         * @brief Check if packet matches the rule given by pattern
         */
    bool match_value(String packet) const;
};
#endif
