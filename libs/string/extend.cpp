//
//  extend.cpp
//  glpro
//
//  Created by PatGame on 15/7/27.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "extend.h"

namespace strlibs
{
    std::pair<std::string, std::string> split(const std::string& str, const std::string& spliter)
    {
        size_t pos = str.find_first_of(spliter);
        std::pair<std::string, std::string> result;

        if (pos == -1)
        {
            result.first = str.substr();
        }
        else
        {
            result.first = str.substr(0, pos);
            result.second = str.substr(pos + 1, str.length() - pos - 1);
        }

        return result;
    }

    std::string trim(const std::string& str)
    {
        std::string result;
        size_t pos1 = str.find_first_not_of(' ');
        size_t pos2 = str.find_last_not_of(' ');
        if (pos1 != -1)
        {
            result = str.substr(pos1, pos2 - pos1 + 1);
        }
        return result;
    }
    
    std::string between(const std::string& str, char left, char right)
    {
        std::string result;
        size_t pos1 = str.find_first_of(left);
        size_t stack = 0;
        size_t len = str.length();
        for (size_t pos2 = pos1 + 1; pos2 < len; pos2++)
        {
            if (str[pos2] == left)
            {
                stack++;
            }
            else if (str[pos2] == right)
            {
                if (stack == 0)
                {
                    result = str.substr(pos1, pos2 - pos1 + 1);
                    break;
                }
                stack--;
            }
        }
        return result;
    }
}

//* test
#include <iostream>
#include "misc/EnterCase.h"
ENTER_CASE
{
    
}
//*/