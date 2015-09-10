//
//  Emittor.h
//  glpro
//
//  Created by PatGame on 15/7/21.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __MODULE_EMITTOR_H__
#define __MODULE_EMITTOR_H__

#include "config.h"
#include <vector>
#include <assert.h>
#include <memory>

#include "mod/In.h"
#include "VariantArray.h"
#include "glcore.h"
#include "EmittorArchetype.h"

namespace camera
{
    class Base;
}

namespace module
{
    class Emittor
    {
    public:
        Emittor(const EmittorArchetype& archetype);
        void newParticle(int i);
        void advanceParticle(int i, float delta);
        void update(float delta);
        void render(float* modelView);
        void render(camera::Base* camera);
    private:
        char* getActionBuffer(int i);
        void depthSort(const glm::vec3& eye);

    private:
        utils::VariantArray _actions;
        std::vector<Particle> _particles;
        std::vector<unsigned int> _indices;
        std::vector<float> _depths;
        const EmittorArchetype& _archetype;

        float _emitCounter;
        int _num;
    };
}

#endif
