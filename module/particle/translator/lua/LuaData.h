//
//  LuaData.h
//  glpro
//
//  Created by wcchan on 15/9/6.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __LUATRANSLATOR_LUADATA_H__
#define __LUATRANSLATOR_LUADATA_H__

#include <string>
#include <functional>
#include <lua.hpp>
#include <assert.h>

namespace module
{
    namespace translator
    {
        class LuaData
        {
        public:
            LuaData(lua_State* L);
            
            LuaData* getChildren(int idx);
            LuaData* getChildren(const char* key);
            
            void getField(const char* key, const std::function<void()>& func);
            void getField(int idx, const std::function<void()>& func);
            
            template <typename T>
            void number(T key, const std::function<void(double)>& func)
            {
                assert(func);
                getField(key, [&]()
                         {
                             func(lua_tonumber(_L, -1));
                         });
            }
            
            template <typename T>
            double number(T key)
            {
                double value = 0;
                getField(key, [&]()
                         {
                             value = lua_tonumber(_L, -1);
                         });
                return value;
            }
            
            template <typename T>
            void string(T key, const std::function<void(const char*)>& func)
            {
                assert(func);
                getField(key, [&]()
                         {
                             func(lua_tostring(_L, -1));
                         });
            }
            
            template <typename T>
            std::string string(T key)
            {
                std::string value = 0;
                getField(key, [&]()
                         {
                             value = lua_tostring(_L, -1);
                         });
                return value;
            }
            
            template <typename T>
            bool isNumber(T key)
            {
                bool is = false;
                getField(key, [&]()
                         {
                             is = lua_isnumber(_L, -1);
                         });
                return is;
            }
            
            template <typename T>
            bool isString(T key)
            {
                bool is = false;
                getField(key, [&]()
                         {
                             is = lua_isstring(_L, -1);
                         });
                return is;
            }

        private:
            lua_State* _L;
        };
    }
}

#endif
