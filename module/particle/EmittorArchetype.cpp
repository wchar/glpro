//
//  EmittorArchetype.cpp
//  glpro
//
//  Created by PatGame on 15/7/28.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "EmittorArchetype.h"
#include <map>
#include "string/extend.h"

namespace module
{
    EmittorArchetype::EmittorArchetype()
    {
        _count = 20;
        _speed = 20;
    }
    
    int EmittorArchetype::getModActionSize() const
    {
        int size = 0;
        for (auto& m : _mods)
        {
            size += m->size();
        }
        
        return size;
    }
}