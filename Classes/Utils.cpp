//
//  Utils.cpp
//  mygame
//
//  Created by 刘 潇逸 on 14-1-23.
//
//

#include "Utils.h"
#include <cocos2d.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <cmath>

namespace utils {
    bool floatEuqalCompare(float lhs, float rhs)
    {
        return fabs(lhs-rhs) <= __FLT_EPSILON__;//std::numeric_limits<float>::epsilon();
    }
    
    bool floatGreaterEuqalCompare(float lhs, float rhs)
    {
        return lhs > rhs || floatEuqalCompare(lhs, rhs);
    }
    
    bool floatLessEuqalCompare(float lhs, float rhs)
    {
        return lhs < rhs || floatEuqalCompare(lhs, rhs);
    }
}