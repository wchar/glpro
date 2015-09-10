//
//  In.h
//  glpro
//
//  Created by wcchan on 15/7/20.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __PARTICLEMOD_IN_H__
#define __PARTICLEMOD_IN_H__

#include <memory>
#include <new>
#include <string>
#include <functional>
#include "Distribution.h"
#include "../config.h"

namespace module
{
    namespace mod
    {
        namespace action
        {
            class In
            {
            public:
                virtual void update(Particle*, float delta) = 0;
                virtual int size() const = 0;
            };

            template <typename T, typename ModuleT>
            class Base : public action::In
            {
            public:
                int size() const override
                {
                    return sizeof(T);
                }

                void setModule(const ModuleT* t)
                {
                    t = _ref;
                }

                ModuleT* getModule()
                {
                    return _ref;
                }

            private:
                ModuleT* _ref;
            };
        }

        struct In
        {
            virtual void init(Particle*, char* data) const = 0;
            virtual int size() const = 0;
        };

        struct InNoAction : public In
        {
            virtual int size() const override
            {
                return 0;
            }
        };

        template <typename T>
        struct InHasAction : public In
        {
            int size() const override
            {
                return sizeof(T);
            }

            template <typename This>
            static T* createAction(This thisMod, char* data)
            {
                auto action = new (data) T();
                action->setModule(thisMod);
                return action;
            }
        };

    }
}

#endif
