//
//  regex.h
//  glpro
//
//  Created by PatGame on 15/7/27.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __STRING_REGEX_H__
#define __STRING_REGEX_H__

#include <string>
#include <vector>
#include <functional>

namespace strlibs
{
    // search once
    std::string regexSearch(const std::string& str, const std::string& regex);

    // search all
    void regexSearch(const std::string& str,
                     const std::string& regex,
                     std::function<void(const std::string&)> callback);

    void regexSearch(const std::string& str,
                     const std::string& regex,
                     std::function<void(const std::string&, int idx)> callback);

    bool regexMatch(const std::string& str, const std::string& regex);
}

#endif
