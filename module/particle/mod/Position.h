//
//  InitPos.h
//  glpro
//
//  Created by wcchan on 15/7/20.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __PARTICLEMOD_POSITION_H__
#define __PARTICLEMOD_POSITION_H__

#include "In.h"

namespace module
{
    namespace mod
    {
        class PosOverLife;
        class InitPos;
        
        namespace action
        {
            class PosOverLife : public Base<action::PosOverLife, mod::PosOverLife>
            {
            public:
                virtual void update(Particle* p, float delta) override;
                glm::vec3 start;
                glm::vec3 end;
            };
        }
    
        struct PosOverLife : public InHasAction<action::PosOverLife>
        {
            void init(Particle* p, char* data) const override;
            DistributionVector start;
            DistributionVector end;
        };
        
        struct InitPos : public InNoAction
        {
            void init(Particle* p, char*) const override;
            DistributionVector v;
        };
    }
}

#endif 

