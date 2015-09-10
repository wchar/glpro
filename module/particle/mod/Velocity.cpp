//
//  Velocity.cpp
//  glpro
//
//  Created by wcchan on 15/7/20.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "Velocity.h"

namespace module
{
    namespace mod
    {
        namespace action
        {
            void VelOverLife::update(Particle* p, float delta)
            {
                p->velocity += (end - start) * delta;
            }
        }
        
        void VelOverLife::init(Particle* p, char* data) const
        {
            auto action = createAction(this, data);
            action->start = start.gen();
            action->end = end.gen();
            p->velocity += action->start;
        }
        
        void InitVel::init(Particle* p, char*) const
        {
            p->velocity += v.gen();
        }
    }
}
