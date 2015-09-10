//
//  InitPos.cpp
//  glpro
//
//  Created by wcchan on 15/7/20.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "Position.h"

namespace module
{
    namespace mod
    {
        namespace action
        {
            void PosOverLife::update(Particle* p, float delta)
            {
                p->position += (end - start) * delta;
            }
        }

        void PosOverLife::init(Particle* p, char* data) const
        {
            auto action = createAction(this, data);
            action->start = start.gen();
            action->end = end.gen();
            p->position += action->start;
        }
        
        void InitPos::init(Particle* p, char*) const
        {
            p->position += v.gen();
        }
    }
}
