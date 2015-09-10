//
//  ModParser.cpp
//  ;
//
//  Created by PatGame on 15/7/30.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "ModParser.h"

#include <Map>
#include <functional>

#include <lua.hpp>
#include "In.h"
#include "LuaData.h"

#include "EnterCase.h"
#include "Position.h"
#include "Velocity.h"
#include "Scale.h"
#include "Color.h"

using namespace module;
static std::map<std::string, std::function<mod::In*(lua_State* L)>> s_genFuncs;

namespace module
{
    namespace translator
    {
        mod::In* genMod(lua_State* L)
        {
            mod::In* mod = nullptr;
            
            lua_rawgeti(L, -1, 1);
            auto name = lua_tostring(L, -1);
            lua_pop(L, 1);

            auto func = s_genFuncs[name];
            if (func)
            {
                lua_rawgeti(L, -1, 2);
                mod = func(L);
                lua_pop(L, 1);
            }
            return mod;
        }
    }
}

template <typename T>
static void parseDistribution(lua_State* L, T key,Distribution* d)
{
    assert(d);
    module::translator::LuaData data(L);

    if (data.isNumber(key))
    {
        d->set(data.number(key));
    }
    else
    data.getField(key, [&]()
                  {
                      d->set(data.number(2), data.number(3));
                  });
}

static glm::vec3 s_getVector(lua_State* L)
{
    module::translator::LuaData data(L);
    return { data.number(1), data.number(2), data.number(3) };
}

template <typename T>
static void parseDistributionVector(lua_State* L, T key,DistributionVector* d)
{
    assert(d);
    module::translator::LuaData data(L);
    data.getField(key, [&]()
                  {
                      if (data.isNumber(1))
                      {
                          // const
                          d->set(s_getVector(L));
                      }
                      else
                      {
                          // range
                          lua_rawgeti(L, -1, 2);
                          glm::vec3 min = s_getVector(L);
                          lua_pop(L, 1);
                          
                          lua_rawgeti(L, -1, 3);
                          glm::vec3 max = s_getVector(L);
                          lua_pop(L, 1);

                          d->set(min, max);
                      }
                  });
}

ENTER_CASE
{
    s_genFuncs["posOverLife"] = [](lua_State* L)
    {
        auto mod = new mod::PosOverLife();

        parseDistributionVector(L, "began", &mod->start);
        parseDistributionVector(L, "ended", &mod->end);
        
        return mod;
    };
    
    s_genFuncs["initPosition"] = [](lua_State* L)
    {
        auto mod = new mod::InitPos();
        parseDistributionVector(L, "pos", &mod->v);
        return mod;
    };
    
    s_genFuncs["velOverLife"] = [](lua_State* L)
    {
        auto mod = new mod::VelOverLife();
        
        parseDistributionVector(L, "began", &mod->start);
        parseDistributionVector(L, "ended", &mod->end);
        
        return mod;
    };
    
    s_genFuncs["initVelocity"] = [](lua_State* L)
    {
        auto mod = new mod::InitVel();
        
        parseDistributionVector(L, "vel", &mod->v);
        
        return mod;
    };
    
    s_genFuncs["initScale"] = [](lua_State* L)
    {
        auto mod = new mod::InitScale();
        
        parseDistribution(L, "scale", &mod->v);
        
        return mod;
    };
    
    s_genFuncs["scaleOverLife"] = [](lua_State* L)
    {
        auto mod = new mod::ScaleOverLife();
        
        parseDistribution(L, "began", &mod->start);
        parseDistribution(L, "ended", &mod->end);
        
        return mod;
    };
    
    s_genFuncs["colorOverLife"] = [](lua_State* L)
    {
        auto mod = new mod::ColorOverLife();
        
        parseDistributionVector(L, "began", &mod->start);
        parseDistributionVector(L, "ended", &mod->end);
        
        return mod;
    };
    
    s_genFuncs["initColor"] = [](lua_State* L)
    {
        auto mod = new mod::InitColor();
      
        parseDistributionVector(L, "color", &mod->v);
        
        return mod;
    };
    
    s_genFuncs["alphaOverLife"] = [](lua_State* L)
    {
        auto mod = new mod::AlphaOverLife();
        
        parseDistribution(L, "began", &mod->start);
        parseDistribution(L, "ended", &mod->end);
        
        return mod;
    };
    
    s_genFuncs["initAlpha"] = [](lua_State* L)
    {
        auto mod = new mod::InitAlpha();
        
        parseDistribution(L, "alpha", &mod->v);
        
        return mod;
    };
}

