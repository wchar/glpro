//
//  Velocity.h
//  glpro
//
//  Created by wcchan on 15/7/20.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __PARTICLEMOD_VELOCITY_H__
#define __PARTICLEMOD_VELOCITY_H__

#include "In.h"

namespace module
{
    namespace mod
    {
        class VelOverLife;
        class InitVel;
        
        namespace action
        {
            struct VelOverLife : public Base<VelOverLife, mod::VelOverLife>
            {
                void update(Particle* p, float delta) override;
                glm::vec3 start;
                glm::vec3 end;
            };
        }
        
        struct VelOverLife : public InHasAction<action::VelOverLife>
        {
            void init(Particle* p, char* data) const override;
            DistributionVector start;
            DistributionVector end;
        };
        
        struct InitVel : public InNoAction
        {
            void init(Particle* p, char*) const override;
            DistributionVector v;
        };
    }
}

#endif