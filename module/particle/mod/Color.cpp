//
//  Color.cpp
//  glpro
//
//  Created by wcchan on 15/9/8.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "Color.h"

namespace module
{
    namespace mod
    {
        namespace action
        {
            void ColorOverLife::update(Particle* p, float delta)
            {
                glm::vec3 scale = (end - start) * delta;
                p->color *= (last + scale) / last;
                last += scale;
            }
        }
        
        void ColorOverLife::init(Particle* p, char* data) const
        {
            auto action = createAction(this, data);
            action->start = start.gen();
            action->end = end.gen();
            action->last = action->start;
            p->color *= action->last;
        }
        
        void InitColor::init(Particle* p, char*) const
        {
            p->color *= v.gen();
        }
    }
    
    
    namespace mod
    {
        namespace action
        {
            void AlphaOverLife::update(Particle* p, float delta)
            {
                float scale = (end - start) * delta;
                p->alpha *= (last + scale) / last;
                last += scale;
            }
        }
        
        void AlphaOverLife::init(Particle* p, char* data) const
        {
            auto action = createAction(this, data);
            action->start = start.gen();
            action->end = end.gen();
            action->last = action->start;
            p->alpha *= action->last;
        }
        
        void InitAlpha::init(Particle* p, char*) const
        {
            p->alpha *= v.gen();
        }
    }
}