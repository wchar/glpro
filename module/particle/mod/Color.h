//
//  Color.h
//  glpro
//
//  Created by wcchan on 15/9/8.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __PARTICLEMOD_COLOR_H__
#define __PARTICLEMOD_COLOR_H__

#include "In.h"

namespace module
{
    namespace mod
    {
        class ColorOverLife;
        class InitColor;
        
        namespace action
        {
            class ColorOverLife : public Base<action::ColorOverLife, mod::ColorOverLife>
            {
            public:
                virtual void update(Particle* p, float delta) override;
                glm::vec3 start;
                glm::vec3 end;
                glm::vec3 last;
            };
        }
        
        struct ColorOverLife : public InHasAction<action::ColorOverLife>
        {
            void init(Particle* p, char* data) const override;
            DistributionVector start;
            DistributionVector end;
        };
        
        struct InitColor : public InNoAction
        {
            void init(Particle* p, char*) const override;
            DistributionVector v;
        };
    }
    
    namespace mod
    {
        class AlphaOverLife;
        class InitAlpha;
        
        namespace action
        {
            class AlphaOverLife : public Base<action::AlphaOverLife, mod::AlphaOverLife>
            {
            public:
                virtual void update(Particle* p, float delta) override;
                float start;
                float end;
                float last;
            };
        }
        
        struct AlphaOverLife : public InHasAction<action::AlphaOverLife>
        {
            void init(Particle* p, char* data) const override;
            Distribution start;
            Distribution end;
        };
        
        struct InitAlpha : public InNoAction
        {
            void init(Particle* p, char*) const override;
            Distribution v;
        };
    }
}

#endif
