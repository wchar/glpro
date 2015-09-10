//
//  LuaData.cpp
//  glpro
//
//  Created by wcchan on 15/9/6.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "LuaData.h"

namespace module
{
    namespace translator
    {
        LuaData::LuaData(lua_State* L)
        {
            _L = L;
        }
        
        void LuaData::getField(const char* key, const std::function<void()>& func)
        {
            assert(func);
            lua_getfield(_L, -1, key);
            if (!lua_isnil(_L, -1))
            {
                func();
            }
            lua_pop(_L, 1);
        }
        
        void LuaData::getField(int idx, const std::function<void()>& func)
        {
            assert(func);
            lua_rawgeti(_L, -1, idx);
            if (!lua_isnil(_L, -1))
            {
                func();
            }
            lua_pop(_L, 1);
        }
    }
}