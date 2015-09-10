//
//  EmittorArchetype.h
//  glpro
//
//  Created by PatGame on 15/7/28.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __MODULE_EMITTORARCHETYPE_H__
#define __MODULE_EMITTORARCHETYPE_H__

#include <vector>
#include <string>
#include "In.h"

namespace module
{
    class EmittorArchetype
    {
    public:
        EmittorArchetype();

        int getCount() const;
        void setCount(int);

        int getSpeed() const;
        void setSpeed(int);

        float getDuration() const;
        void setDuration(float);
        
        const mod::In* getMod(unsigned int idx) const;
        const std::vector<std::shared_ptr<mod::In>>& getMods() const;
        void addMod(std::shared_ptr<mod::In>&& mod);

        int getModActionSize() const;

    private:
        int _count;
        int _speed;
        float _duration;

        std::vector<std::shared_ptr<mod::In>> _mods;
    };

    inline int EmittorArchetype::getCount() const
    {
        return _count;
    }

    inline void EmittorArchetype::setCount(int v)
    {
        _count = v;
    }

    inline int EmittorArchetype::getSpeed() const
    {
        return _speed;
    }

    inline void EmittorArchetype::setSpeed(int v)
    {
        _speed = v;
    }

    inline float EmittorArchetype::getDuration() const
    {
        return _duration;
    }
    
    inline void EmittorArchetype::setDuration(float v)
    {
        _duration = v;
    }
    
    inline const mod::In* EmittorArchetype::getMod(unsigned int idx) const
    {
        assert(idx < _mods.size());
        return _mods[idx].get();
    }

    inline const std::vector<std::shared_ptr<mod::In>>& EmittorArchetype::getMods() const
    {
        return _mods;
    }

    inline void EmittorArchetype::addMod(std::shared_ptr<mod::In>&& mod)
    {
        _mods.push_back(mod);
    }
}

#endif
