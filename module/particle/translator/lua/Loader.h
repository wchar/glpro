//
//  Loader.h
//  glpro
//
//  Created by PatGame on 15/7/29.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __LUATRANSLATOR_LOADER_H__
#define __LUATRANSLATOR_LOADER_H__

#include <string>
#include "ParticleSystemArchetype.h"

namespace module
{
    namespace translator
    {
        ParticleSystemArchetype parse(const std::string& path);
    }
}

#endif
