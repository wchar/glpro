//
//  VariantArray.cpp
//  glpro
//
//  Created by wcchan on 15/7/22.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "VariantArray.h"

namespace utils
{
    void VariantArray::replaceLast(int idx, int by)
    {
        auto current = &_data[idx * _stride];
        auto last = &_data[by * _stride];
        memcpy(current, last, _stride);
    }
}