//
//  Emittor.cpp
//  glpro
//
//  Created by PatGame on 15/7/21.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include <map>
#include "../camera/Base.h"
#include "Emittor.h"
#include "Position.h"

namespace module
{
    Emittor::Emittor(const EmittorArchetype& archetype)
        : _archetype(archetype)
        , _num(0)
        , _emitCounter(0)
    {
        auto count = _archetype.getCount();
        _particles.resize(count);
        _indices.resize(count);
        _depths.resize(count);

        auto size = _archetype.getModActionSize();
        if (size)
        {
            _actions.setStride(_archetype.getModActionSize());
            _actions.resize(count);
        }
    }
    
    void Emittor::newParticle(int i)
    {
        auto& particle = _particles[i];
        memset(&particle, 0, sizeof(Particle));
        particle.scale = 1.0f;
        particle.alpha = 1.0f;
        particle.duration = _archetype.getDuration();
        particle.color = { 1.f, 1.f, 1.f };
        
        char* buf = _actions.at<char>(i);
        int offset = 0;
        for (auto& m : _archetype.getMods())
        {
            m->init(&particle, buf + offset);
            offset += m->size();
        }
    }
    
    void Emittor::advanceParticle(int i, float delta)
    {
        auto& particle = _particles[i];
        char* buf = _actions.at<char>(i);
        int offset = 0;

        delta /= _archetype.getDuration();
        while (offset < _actions.getStride())
        {
            auto action = reinterpret_cast<mod::action::In*>(buf + offset);
            action->update(&particle, delta);
            offset += action->size();
        }
        
        particle.position += particle.velocity * delta;
    }
    
    void Emittor::update(float delta)
    {
        // emit
        float rate = 1.0f / _archetype.getSpeed();
        if (_num < _archetype.getCount())
        {
            _emitCounter += delta;
        }
        
        while (_num < _archetype.getCount() && _emitCounter > rate)
        {
            newParticle(_num++);
            _emitCounter -= rate;
        }
        
        // advance
        int i = 0;
        while (i < _num)
        {
            auto& particle = _particles[i];
            particle.life += delta / particle.duration;
            
            // delete
            if (particle.life > 1)
            {
                --_num;
                if (i != _num)
                {
                    _particles[i] = _particles[_num];
                    _actions.replaceLast(i, _num);
                }
                continue;
            }
            
            advanceParticle(i, delta);
            i++;
        }
    }

    void Emittor::render(camera::Base* camera)
    {
        auto modelView = camera->getView() * camera->getModel();
        float* m = (float*)& modelView;
        float v[4][3] = {
            {-m[0]-m[1], -m[4]-m[5], -m[8]-m[9]},
            { m[0]-m[1],  m[4]-m[5],  m[8]-m[9]},
            { m[0]+m[1],  m[4]+m[5],  m[8]+m[9]},
            {-m[0]+m[1], -m[4]+m[5], -m[8]+m[9]}
        };
        
        auto rot = glm::inverse(camera->getModel());
        auto eye = rot * glm::vec4(camera->getEye(), 1);
        depthSort(glm::vec3(eye));
        
        // draw indices
        for (int i = 0; i < _num; i++)
        {
            auto& p = _particles[_indices[i]];
            
            glPushMatrix();
            
            glTranslatef(p.position.x, p.position.y, p.position.z);
            float scale = 0.2 * p.scale;
            glScalef(scale, scale, scale);
            glColor4f(p.color.x, p.color.y, p.color.z, p.alpha);
            
            glBegin(GL_QUADS);
            glVertex3fv(v[0]);
            glVertex3fv(v[1]);
            glVertex3fv(v[2]);
            glVertex3fv(v[3]);
            glEnd();
            
            glPopMatrix();
        }
    }
    
    static void quickDepthSort(unsigned int* indices, float* depths, int lo, int hi)
    {
        int i=lo, j=hi;
        float h;
        int index;
        float x=depths[(lo+hi)/2];
        
        //  partition
        do
        {
            while (depths[i] > x) i++;
            while (depths[j] < x) j--;
            if (i<=j)
            {
                h=depths[i]; depths[i]=depths[j]; depths[j]=h;
                index = indices[i]; indices[i] = indices[j]; indices[j] = index;
                i++; j--;
            }
        } while (i<=j);
        
        //  recursion
        if (lo<j) quickDepthSort(indices, depths, lo, j);
        if (i<hi) quickDepthSort(indices, depths, i, hi);
    }
    
    void Emittor::depthSort(const glm::vec3& eye)
    {
        for (int i = 0; i < _num; i++)
        {
            _indices[i] = i;
            auto v = eye - _particles[i].position;
            _depths[i] = v.x * v.x + v.y * v.y + v.z * v.z;
        }
        
        quickDepthSort(_indices.data(), _depths.data(), 0, _num - 1);
    }
}
