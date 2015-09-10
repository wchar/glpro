//
//  ScopeExit.h
//  glpro
//
//  Created by PatGame on 15/7/29.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __MISC_SCOPEEXIT_H__
#define __MISC_SCOPEEXIT_H__

#include <functional>

namespace misc
{
    template <typename Fun>
    class Scope
    {
    public:
        Scope(Fun&& f) : _fun(std::forward<Fun>(f)), _active(true)
        {
        }
        
        ~Scope()
        {
            if (_active)
            {
                _fun();
            }
        }
        
        void dismiss()
        {
            _active = false;
        }
        
        Scope() = delete;
        Scope(const Scope&) = delete;
        Scope& operator=(const Scope&) = delete;
        
        Scope(Scope&& rhs) : _fun(std::move(rhs._fun)), _active(rhs._active)
        {
            rhs.dismiss();
        }
        
    private:
        Fun _fun;
        bool _active;
    };
    
    namespace detail
    {
        enum class OnExit
        {
        };
        
        template <typename Fun>
        inline Scope<Fun> operator+(OnExit, Fun&& fn)
        {
            return Scope<Fun>(std::forward<Fun>(fn));
        }
    }
}

#define SCOPE_EXIT \
auto __ANONYMOUS_VARIABLE(SCOPE_EXIT_STATE) = misc::detail::OnExit() + [&]()

#define __CONCATENATE_IMPL(s1, s2) s1##s2
#define __CONCATENATE(s1, s2) __CONCATENATE_IMPL(s1, s2)

#ifdef __COUNTER__
    #define __ANONYMOUS_VARIABLE(str) __CONCATENATE(str, __COUNTER__)
#else
    #define __ANONYMOUS_VARIABLE(str) __CONCATENATE(str, __LINE__)
#endif

#endif

