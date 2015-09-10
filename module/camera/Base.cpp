//
//  Camera.cpp
//  glpro
//
//  Created by PatGame on 15/7/22.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "Base.h"
#include "glm/gtc/matrix_transform.hpp"

namespace camera
{
    void Base::initView(const glm::vec3 &eye, const glm::vec3 center, const glm::vec3& up)
    {
        _eye = eye;
        _center = center;
        _view = glm::lookAt(_eye, _center, up);
    }
    
    void Base::initProj(int width, int height)
    {
        float aspect = (float)width / height;
        _proj = glm::perspective(45.f, aspect, 0.1f, 100.f);
        
        onWindowChanged(width, height);
    }
    
    void Base::onWindowChanged(int width, int height)
    {
        _width = width;
        _height = height;
    }
}