//
//  Distribute.cpp
//  glpro
//
//  Created by wcchan on 15/7/18.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "Distribution.h"
#include <stdlib.h>

namespace module
{
    //
    // === Distribution ===
    //
    static float s_random(float min, float max)
    {
        float p = 0.0001f * (rand() % 10000);
        return p * min + (1 - p) * max;
    }

    void Distribution::set(float constant)
    {
        _value.constant = constant;
        _type = CONSTANT;
    }

    void Distribution::set(float min, float max)
    {
        if (min > max)
        {
            float m = min;
            min = max;
            max = m;
        }

        _value.uniform.min = min;
        _value.uniform.max = max;
        _type = UNIFORM;
    }

    float Distribution::gen() const
    {
        if (_type == UNIFORM)
        {
            return s_random(_value.uniform.min, _value.uniform.max);
        }
        return _value.constant;
    }

    //
    // === DistributionVector ===
    //
    void DistributionVector::set(const glm::vec3& constant)
    {
        _x.set(constant.x);
        _y.set(constant.y);
        _z.set(constant.z);
    }

    void DistributionVector::set(const glm::vec3& min, const glm::vec3& max)
    {
        _x.set(min.x, max.x);
        _y.set(min.y, max.y);
        _z.set(min.z, max.z);
    }

    glm::vec3 DistributionVector::gen() const
    {
        return { _x.gen(), _y.gen(), _z.gen() };
    }
}