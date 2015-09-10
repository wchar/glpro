//
//  Data.h
//  glpro
//
//  Created by PatGame on 15/7/29.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __UTILS_DATA_H__
#define __UTILS_DATA_H__

#include <vector>
#include <string>

namespace utils
{
    class Data
    {
    public:
        typedef uint8_t byte_t;
        static Data loadFromFile(const std::string& filePath);

        Data();
        Data(const Data& rhs);
        Data& operator=(const Data& rhs);

        Data(size_t size);
        ~Data();
        Data(Data&& rhs);

        void swap(Data& rhs);

        // 将数据写入文件
        bool writeToFile(const std::string& filePath) const;

        bool pushData(const void* data, size_t len);

        void resize(size_t size);
        void reserve(size_t size);
        void shrink_to_fit();
        void clear();

        const byte_t*  bytes() const {   return _bytes;              }
        size_t          size() const {   return _size;               }
        bool empty() const           {   return size() == 0;         }
        
        const byte_t& operator[] (size_t idx) const   {   return _bytes[idx];  }
        byte_t& operator[] (size_t idx)        {   return _bytes[idx];         }
        
        const byte_t* begin() const            {   return _bytes;              }
        const byte_t* end() const              {   return _bytes + _size;      }
        
    private:
        void expandCapacity(size_t capacity);

    private:
        byte_t* _bytes;
        size_t _size;
        size_t _capacity;
    };

    bool operator==(const Data& lhs, const Data& rhs);
    bool operator!=(const Data& lhs, const Data& rhs);
}

#endif
