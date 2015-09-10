//
//  Header.h
//  glpro
//
//  Created by wcchan on 15/7/20.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __PARTICLE_CONFIG_H__
#define __PARTICLE_CONFIG_H__

#include "glm/vec3.hpp"

struct Particle
{
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 color;
    float alpha;
    float scale;
    float life;
    float duration;
};

#endif
