//
//  VariantArray.h
//  glpro
//
//  Created by wcchan on 15/7/22.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __UTILS_VARIANTARRAY_H__
#define __UTILS_VARIANTARRAY_H__

#include <vector>
#include <assert.h>

namespace utils
{
    class VariantArray
    {
    public:
        VariantArray()
        {
            _stride = 0;
            _size = 0;
        }
        
        void setStride(int stride)
        {
            assert(stride > 0);
            _stride = stride;
        }
        
        int getStride() const
        {
            return _stride;
        }
        
        void resize(int size)
        {
            assert(_stride > 0);
            _size = size;
            _data.resize(_stride * _size);
        }
        
        int size() const
        {
            return _size;
        }
        
        template<typename T>
        T* at(int idx)
        {
            assert(idx * _stride <= _data.size());
            return reinterpret_cast<T*>(_data.data() + idx * _stride);
        }
        
        void replaceLast(int idx, int by);
    private:
        std::vector<char> _data;
        int _size;
        int _stride;
    };
}

#endif
