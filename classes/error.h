//
// Created by aca on 30.1.21..
//

#ifndef RG_3D_SAH_ERROR_H
#define RG_3D_SAH_ERROR_H

#include <iostream>
#include <cstdlib>

#define CHECK_ERROR(condition, message) {\
    do\
    {\
        if(!(condition))\
        {\
            std::cerr << "Error: " << message << std::endl;\
            exit(EXIT_FAILURE);\
        }\
    } while(0);\
}

#endif //RG_3D_SAH_ERROR_H
