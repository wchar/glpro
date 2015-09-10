//
//  CoordinateAxis.h
//  glpro
//
//  Created by wcchan on 15/7/24.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __COORDINATEAXIS_H__
#define __COORDINATEAXIS_H__

#include "Attribute.h"

class CoordinateAxis
{
public:
    void init(glcore::Attribute& position, glcore::Attribute& color)
    {
        _position = position;
        _color = color;
    }
    
    void draw();
private:
    glcore::Attribute _position;
    glcore::Attribute _color;
};

#endif

