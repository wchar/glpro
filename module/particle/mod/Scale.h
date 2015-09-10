//
//  Scale.h
//  glpro
//
//  Created by wcchan on 15/9/8.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __PARTICLEMOD_SCALE_H__
#define __PARTICLEMOD_SCALE_H__

#include "In.h"

namespace module
{
    namespace mod
    {
        class ScaleOverLife;
        class InitScale;
        
        namespace action
        {
            class ScaleOverLife : public Base<action::ScaleOverLife, mod::ScaleOverLife>
            {
            public:
                virtual void update(Particle* p, float delta) override;
                float start;
                float end;
                float last;
            };
        }
        
        struct ScaleOverLife : public InHasAction<action::ScaleOverLife>
        {
            void init(Particle* p, char* data) const override;
            Distribution start;
            Distribution end;
        };
        
        struct InitScale : public InNoAction
        {
            void init(Particle* p, char*) const override;
            Distribution v;
        };
    }
}

#endif
