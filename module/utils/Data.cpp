//
//  Data.cpp
//  glpro
//
//  Created by PatGame on 15/7/29.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "Data.h"
#include <assert.h>
#include "misc/ScopeExit.h"

namespace utils
{
    void Data::expandCapacity(size_t capacity)
    {
        assert(capacity > _capacity);
        _capacity = capacity;
        _bytes = (byte_t*)realloc(_bytes, _capacity);
        assert(_bytes);
    }
    
    static size_t s_computeNewCapacity(size_t oldCapacity, size_t needSize)
    {
        assert(oldCapacity < needSize);
        if (oldCapacity == 0)
        {
            return needSize;
        }
        
        size_t newCapacity = oldCapacity * 2;
        while (newCapacity < needSize)
        {
            newCapacity *= 2;
        }
        return newCapacity;
    }
    
    bool Data::pushData(const void* data, size_t len)
    {
        if (data == nullptr || len == 0)
        {
            return false;
        }
        
        auto totalSize = _size + len;
        if (_capacity < totalSize)
        {
            auto capacity = s_computeNewCapacity(_capacity, totalSize);
            expandCapacity(capacity);
        }
        memcpy(_bytes + _size, data, len);
        _size = totalSize;
        return true;
    }
    
    Data Data::loadFromFile(const std::string& filePath)
    {
        Data data;
        FILE* file = fopen(filePath.c_str(), "rb");
        if (file == NULL)
        {
            return data;
        }
        
        SCOPE_EXIT
        {
            fclose(file);
        };
        
        size_t read_len = 1024;
        size_t pos = 0;
        data.resize(read_len);
        
        for (;;)
        {
            assert(pos + read_len == data.size());
            size_t n = fread(&data[pos], 1, read_len, file);
            pos += n;
            
            if (n < read_len)
            {
                break;
            }
            
            read_len *= 2;
            data.resize(data.size() + read_len);
        }
        data.resize(pos);
        return std::move(data);
    }
    
    bool Data::writeToFile(const std::string& filePath) const
    {
        FILE* file = fopen(filePath.c_str(), "wb");
        if (file == NULL)
        {
            return false;
        }
        
        SCOPE_EXIT
        {
            fclose(file);
        };
        
        fwrite(_bytes, _size, 1, file);
        return true;
    }
    
    void Data::swap(Data& rhs)
    {
        std::swap(_bytes, rhs._bytes);
        std::swap(_size, rhs._size);
        std::swap(_capacity, rhs._capacity);
    }
    
    void Data::shrink_to_fit()
    {
        if (_size == _capacity)
        {
            return;
        }
        
        if (_bytes)
        {
            if (_size == 0)
            {
                free(_bytes);
                _bytes = nullptr;
                _size = 0;
                _capacity = 0;
            }
            else
            {
                _bytes = (byte_t*)realloc(_bytes, _size);
                _capacity = _size;
            }
        }
    }
    
    void Data::resize(size_t size)
    {
        if (_capacity < size)
        {
            expandCapacity(size);
        }
        _size = size;
    }
    
    void Data::reserve(size_t size)
    {
        if (_capacity < size)
        {
            expandCapacity(size);
        }
    }
    
    void Data::clear()
    {
        _size = 0;
    }
    
    Data::Data()
    {
        _bytes = nullptr;
        _size = 0;
        _capacity = 0;
    }
    
    Data::Data(const Data& rhs)
    {
        if (rhs.empty())
        {
            _bytes = nullptr;
            _size = 0;
            _capacity = 0;
        }
        else
        {
            _bytes = (byte_t*)realloc(nullptr, rhs._size);
            _size = rhs._size;
            _capacity = rhs._size;
            memcpy(_bytes, rhs._bytes, _size);
        }
    }
    
    Data& Data::operator=(const Data& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        
        if (rhs.empty())
        {
            if (_bytes)
            {
                free(_bytes);
            }
            _bytes = nullptr;
            _capacity = 0;
            _size = 0;
            return *this;
        }
        
        if (_capacity > rhs._size)
        {
            _size = rhs._size;
            memcpy(_bytes, rhs._bytes, _size);
        }
        else
        {
            _bytes = (byte_t*)realloc(_bytes, rhs._size);
            _size = rhs._size;
            _capacity = rhs._size;
            memcpy(_bytes, rhs._bytes, _size);
        }
        return *this;
    }
    
    Data::Data(size_t size)
    {
        _bytes = (byte_t*)realloc(nullptr, size);
        _size = size;
        _capacity = size;
    }
    
    Data::~Data()
    {
        if (_bytes)
        {
            free(_bytes);
        }
    }
    
    Data::Data(Data&& rhs)
    {
        _bytes = rhs._bytes;
        _size = rhs._size;
        _capacity = rhs._capacity;
        rhs._bytes = nullptr;
        rhs._size = 0;
        rhs._capacity = 0;
    }
    
    bool operator==(const Data& lhs, const Data& rhs)
    {
        if (lhs.empty() && rhs.empty())
        {
            return true;
        }
        
        if (lhs.size() != rhs.size())
        {
            return false;
        }
        return memcmp(lhs.begin(), rhs.begin(), lhs.size()) == 0;
    }
    
    bool operator!=(const Data& lhs, const Data& rhs)
    {
        return !(lhs == rhs);
    }
}