//
//  ArcBall.cpp
//  glpro
//
//  Created by wcchan on 15/7/22.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "ArcBall.h"
#include "glm/gtx/vector_angle.hpp"

namespace camera
{
    ArcBall::ArcBall()
    {
    }

    void ArcBall::began(int x, int y)
    {
        if (x >= 0 && x < _width && y >= 0 && y < _height)
        {
            _drag = true;
            _downPt = screenToVector(x, y);
        }
    }

    void ArcBall::moved(int x, int y)
    {
        if (_drag)
        {
            _currentPt = screenToVector(x, y);
            _rot = glm::rotation(_downPt, _currentPt);
        }
    }

    void ArcBall::ended(int x, int y)
    {
        _drag = false;
    }

    glm::vec3 ArcBall::screenToVector(int x, int y)
    {
        float halfw = (float)_width / 2;
        float halfh = (float)_height / 2;
        float fx = -(halfw - x) / (halfw * _radius);
        float fy = (halfh - y) / (halfh * _radius);

        float fz = 0.0f;

        float mag = fx * fx + fy * fy;
        if (mag > 1.0f)
        {
            float scale = 1.0f / sqrtf(mag);
            fx *= scale;
            fy *= scale;
        }
        else
        {
            fz = sqrtf(1.0f - mag);
        }

        return { fx, fy, fz };
    }
}