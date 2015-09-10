//
//  Loader.cpp
//  glpro
//
//  Created by PatGame on 15/7/29.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//
#include "Loader.h"

#include <functional>
#include <memory>
#include <lua.hpp>
#include "fsys/FileIO.h"
#include "In.h"
#include "ModParser.h"
#include "LuaData.h"

static lua_State* L = nullptr;

static void s_loadFile(const char* path)
{
    if (0 != luaL_loadfile(L, path))
    {
        puts(lua_tostring(L, -1));
    }
    else if (0 != lua_pcall(L, 0, 0, 0))
    {
        puts(lua_tostring(L, -1));
    }
}

static void s_loadString(const char* str)
{
    if (0 != luaL_loadstring(L, str))
    {
        puts(lua_tostring(L, -1));
    }
    else if (0 != lua_pcall(L, 0, 0, 0))
    {
        puts(lua_tostring(L, -1));
    }
}

namespace module
{
    namespace translator
    {
        static void s_parseMod(lua_State* L, EmittorArchetype* ea)
        {
            int it = lua_gettop(L);
            lua_pushnil(L);
            while (lua_next(L, it))
            {
                if (lua_istable(L, -1))
                {
                    auto mod = genMod(L);
                    if (mod)
                    {
                        auto shared = std::shared_ptr<mod::In>(mod);
                        ea->addMod(std::forward<decltype(shared)>(shared));
                    }
                }
                lua_gettable(L, -1);
                lua_pop(L, 1);
            }
        }
        
        void parseEmittor(lua_State* L, EmittorArchetype* ea)
        {
            LuaData data(L);
            
            data.number("count",
                           [&](double v)
                           {
                               ea->setCount(v);
                           });
            
            data.number("speed",
                           [&](double v)
                           {
                               ea->setSpeed(v);
                           });
            
            data.number("duration",
                        [&](double v)
                        {
                            ea->setDuration(v);
                        });

            lua_getfield(L, -1, "mod");
            if (lua_istable(L, -1))
            {
                s_parseMod(L, ea);
            }
            lua_pop(L, 1);
        }

        ParticleSystemArchetype parse(const std::string& path)
        {
            s_loadString("clean()");
            s_loadFile(path.c_str());

//            s_loadString("d_print(__emittors)");
            
            ParticleSystemArchetype result;

            lua_getglobal(L, "__emittors");
            int it = lua_gettop(L);
            lua_pushnil(L);

            while (lua_next(L, it))
            {
                EmittorArchetype emittor;
                parseEmittor(L, &emittor);
                result.pushEmittor(std::forward<EmittorArchetype>(emittor));
                lua_pop(L, 1);
            }

            return result;
        }
    }
}

#include "EnterCase.h"
ENTER_CASE
{
    L = luaL_newstate();
    luaL_openlibs(L);

    const char* raw_c_str = R"(
    
    local meta_table = {}
        meta_table.__index = function(t, k)
        if rawget(t, k) == nil then
            return function(...)
                return { k, ... }
            end
        end
    
        return rawget(t, k)
    end
    
    setmetatable(_G, meta_table)
    
    function d_print(t)
        local has_printed = {}
        local function inner_print(t, head)
            for k, v in pairs(t) do
                print(head .. "" .. tostring(k) .. ": " .. tostring(v))
                if type(v) == "table" and not has_printed[v] then
                    inner_print(v, head .. "   ")
                end
                has_printed[v] = true
            end
        end
        inner_print(t, "")
    end
    
    __emittors = {}
    function emittor(t)
        table.insert(__emittors, t)
    end
    
    function clean()
        __emittors = {}
    end
    
    )";

    s_loadString(raw_c_str);
}