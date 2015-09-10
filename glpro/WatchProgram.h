//
//  WatchProgram.h
//  glpro
//
//  Created by PatGame on 15/7/21.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __WATCHPROGRAM_H__
#define __WATCHPROGRAM_H__

#include "glcore.h"
#include <string>

class WatchProgram : public glcore::Program
{
public:
    void create(const std::string& vertName, const std::string& fragName);
    
private:
    void refresh();

    std::string _vertName;
    std::string _fragName;
};

#endif 

