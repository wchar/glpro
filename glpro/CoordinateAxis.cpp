//
//  CoordinateAxis.cpp
//  glpro
//
//  Created by wcchan on 15/7/24.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "CoordinateAxis.h"

namespace
{
    struct Vertex
    {
        float pos[3];
        float color[4];
    };
    
    static const Vertex vertices[] = {
        { {  0.f, 0.f, 0 }, { 1.f, .3f, .3f, 1 } },
        { {  1.f, 0.f, 0 }, { 1.f, .3f, .3f, 1 } },
        { {  .9f, .1f, 0 }, { 1.f, .3f, .3f, 1 } },
        { {  1.f, 0.f, 0 }, { 1.f, .3f, .3f, 1 } },
        { {  .9f, 0.f,.1 }, { 1.f, .3f, .3f, 1 } },
        { {  1.f, 0.f, 0 }, { 1.f, .3f, .3f, 1 } },
        
        { {  0.f, 0.f, 0 }, { .3f, 1.f, .3f, 1 } },
        { {  0.f, 1.f, 0 }, { .3f, 1.f, .3f, 1 } },
        { {  .1f, .9f, 0 }, { .3f, 1.f, .3f, 1 } },
        { {  0.f, 1.f, 0 }, { .3f, 1.f, .3f, 1 } },
        { {  0.f, .9f,.1 }, { .3f, 1.f, .3f, 1 } },
        { {  0.f, 1.f, 0 }, { .3f, 1.f, .3f, 1 } },
        
        { {  0.f, 0.f, 0 }, { .3f, .3f, 1.f, 1 } },
        { {  0.f, 0.f, 1 }, { .3f, .3f, 1.f, 1 } },
        { {  0.f, .1f,.9 }, { .3f, .3f, 1.f, 1 } },
        { {  0.f, 0.f, 1 }, { .3f, .3f, 1.f, 1 } },
        { {  .1f, 0.f,.9 }, { .3f, .3f, 1.f, 1 } },
        { {  0.f, 0.f, 1 }, { .3f, .3f, 1.f, 1 } },
    };
}

void CoordinateAxis::draw()
{
    _position.enableArray();
    _color.enableArray();
    
    _position.setVec3(vertices[0].pos, sizeof(Vertex));
    _color.setVec4(vertices[0].color, sizeof(Vertex));
    
    GLsizei vertexCount = sizeof(vertices) / sizeof(Vertex);
    glDrawArrays(GL_LINES, 0, vertexCount);
    
    _position.disableArray();
    _color.disableArray();
}