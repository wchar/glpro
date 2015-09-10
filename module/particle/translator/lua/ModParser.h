//
//  ModParser.h
//  glpro
//
//  Created by PatGame on 15/7/30.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __LUATRANSLATOR_MODPARSER_H__
#define __LUATRANSLATOR_MODPARSER_H__

class lua_State;

namespace module
{
    namespace mod
    {
        class In;
    }
    
    namespace translator
    {
        mod::In* genMod(lua_State* L);
    }
}

#endif

