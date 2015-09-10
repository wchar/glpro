//
//  ParticleSystem.cpp
//  glpro
//
//  Created by wcchan on 15/7/20.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "ParticleSystem.h"

namespace module
{
    ParticleSystem::ParticleSystem(const ParticleSystemArchetype& archetype)
    {
        for (auto& a : archetype.getEmittorArchetypes())
        {
            _emittors.push_back(std::shared_ptr<Emittor>(new Emittor(a)));
        }
    }
    
    ParticleSystem::~ParticleSystem()
    {
    }
    
    void ParticleSystem::update(float t)
    {
        for (auto emittor : _emittors)
        {
            emittor->update(t);
        }
    }
    
    void ParticleSystem::render(camera::Base* camera)
    {
        for (auto emittor : _emittors)
        {
            emittor->render(camera);
        }
    }
}