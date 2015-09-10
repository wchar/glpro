//
//  Distribute.h
//  glpro
//
//  Created by wcchan on 15/7/18.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __MODULE_DISTRIBUTE_H__
#define __MODULE_DISTRIBUTE_H__

#include <stdio.h>
#include <vector>
#include "glm/glm.hpp"

namespace module
{
    class Distribution
    {
    public:
        void set(float constant);
        void set(float min, float max);

        float gen() const;
        
    private:
        union
        {
            float constant;
            struct
            {
                float max;
                float min;
            }uniform;
            
            struct
            {
                float feq;
                float scale;
            };
        } _value;
        
        enum
        {
            CONSTANT,
            UNIFORM,
        } _type;
    };
    
    class DistributionVector
    {
    public:
        void set(const glm::vec3& constant);
        void set(const glm::vec3& min, const glm::vec3& max);
        
        glm::vec3 gen() const;
        
    private:
        Distribution _x;
        Distribution _y;
        Distribution _z;
    };

    class DistributionCurve
    {
    public:
        float gen() const;
    private:
        std::vector<std::pair<float, float>> _points;
    };

    class DistributionCurveVector
    {
    public:
        glm::vec3 gen() const;
    private:
        std::vector<std::pair<float, glm::vec3>> _points;
    };
}

#endif

