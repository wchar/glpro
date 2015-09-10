//
//  Scale.cpp
//  glpro
//
//  Created by wcchan on 15/9/8.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "Scale.h"

namespace module
{
    namespace mod
    {
        namespace action
        {
            void ScaleOverLife::update(Particle* p, float delta)
            {
                float scale = (end - start) * delta;
                p->scale *= (last + scale) / last;
                last += scale;
            }
        }
        
        void ScaleOverLife::init(Particle* p, char* data) const
        {
            auto action = createAction(this, data);
            action->start = start.gen();
            action->end = end.gen();
            action->last = action->start;
            p->scale *= action->last;
        }
        
        void InitScale::init(Particle* p, char*) const
        {
            p->scale *= v.gen();
        }
    }
}