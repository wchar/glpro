//
//  ParticleSystem.h
//  glpro
//
//  Created by wcchan on 15/7/20.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __MODULE_PARTICLESYSTEM_H__
#define __MODULE_PARTICLESYSTEM_H__

#include "config.h"
#include <vector>
#include "Emittor.h"
#include "ParticleSystemArchetype.h"

namespace camera
{
    class Base;
}

namespace module
{
    class ParticleSystem
    {
    public:
        ParticleSystem(const ParticleSystemArchetype& archetype);
        ~ParticleSystem();
        
        void update(float t);
        void render(camera::Base* camera);
        
        const std::vector<std::shared_ptr<Emittor>>& getEmittors() const 
        {
            return _emittors;
        }
    private:
        std::vector<std::shared_ptr<Emittor>> _emittors;
    };
}

#endif
