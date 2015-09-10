//
//  EnterFile.h
//  glpro
//
//  Created by wcchan on 15/7/26.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __MISC_ENTERFILE_H__
#define __MISC_ENTERFILE_H__

namespace misc
{
    template <typename T>
    class EnterCase
    {
    public:
        EnterCase()
        {
            run();
        }
        void run();
    };

#define __ENTER_CASE_CONCATENATE_IMPL(s1, s2) s1##s2
#define __ENTER_CASE_CONCATENATE(s1, s2) __ENTER_CASE_CONCATENATE_IMPL(s1, s2)

#define __ENTER_CASE(ClassName)                                                \
    namespace                                                                  \
    {                                                                          \
        struct ClassName;                                                      \
    }                                                                          \
    static misc::EnterCase<ClassName> __ENTER_CASE_CONCATENATE(s_, ClassName); \
    template <>                                                                \
    void misc::EnterCase<ClassName>::run()

#define ENTER_CASE __ENTER_CASE(__ENTER_CASE_CONCATENATE(ENTER_CASE_NAME, __LINE__))
}

#endif
