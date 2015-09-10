//
//  ParticleSystemArchetype.h
//  glpro
//
//  Created by PatGame on 15/7/28.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __MODULE_PARTICLESYSTEMARCHETYPE_H__
#define __MODULE_PARTICLESYSTEMARCHETYPE_H__

#include <string>
#include <vector>
#include "EmittorArchetype.h"

namespace module
{
    class ParticleSystemArchetype
    {
    public:
        ParticleSystemArchetype();
        
        const std::vector<EmittorArchetype>& getEmittorArchetypes() const
        {
            return _emittorArchetypes;
        }
        
        void pushEmittor(EmittorArchetype&& ea)
        {
            _emittorArchetypes.push_back(ea);
        }
        
    private:
        std::vector<EmittorArchetype> _emittorArchetypes;
    };
}

#endif

