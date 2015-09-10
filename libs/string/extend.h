//
//  extend.h
//  glpro
//
//  Created by PatGame on 15/7/27.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __STRLIBS_EXTEND_H__
#define __STRLIBS_EXTEND_H__

#include <string>
#include <vector>

namespace strlibs
{
    // 分割
    std::pair<std::string, std::string> split(const std::string& str, const std::string& spliter);

    // 前后去空
    std::string trim(const std::string& str);
    
    //
    std::string between(const std::string& str, char left = '{', char right = '}');
    
}

#endif
