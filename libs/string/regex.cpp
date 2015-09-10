//
//  regex.cpp
//  glpro
//
//  Created by PatGame on 15/7/27.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "regex.h"
#include <regex>

namespace strlibs
{
    std::string regexSearch(const std::string& str, const std::string& regex)
    {
        std::string result;
        std::smatch smatch;
        if (std::regex_search(str, smatch, std::regex(regex)))
        {
            result = smatch.str();
        }
        return result;
    }
    
    void regexSearch(const std::string& str,
                     const std::string& regex,
                     std::function<void(const std::string&, int idx)> callback)
    {
        const std::regex pattern(regex);
        const std::sregex_token_iterator end;
        std::sregex_token_iterator it(str.begin(), str.end(), pattern);
        for (int i = 0; it != end; ++it, ++i)
        {
            callback(it->str(), i);
        }
    }

    void regexSearch(const std::string& str, const std::string& regex, std::function<void(const std::string&)> callback)
    {
        regexSearch(str, regex, [=](const std::string& str, auto)
                    {
                        callback(str);
                    });
    }
    
    bool regexMatch(const std::string& str, const std::string& regex)
    {
        return std::regex_match(str, std::regex(regex));
    }
}
