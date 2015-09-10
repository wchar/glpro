//
//  FileIO.cpp
//  glpro
//
//  Created by PatGame on 15/7/24.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "FileIO.h"
#include <stdio.h>


namespace fsys
{
    std::string readFromPath(const std::string& path)
    {
        FILE* file = fopen(path.c_str(), "r");
        std::string result;
        
        if (file == nullptr)
        {
            return result;
        }
        
        const size_t read_len = 1024;
        char buf[read_len];
        for (;;)
        {
            size_t n = fread(buf, 1, read_len, file);
            result.insert(result.size(), buf, n);
            if (n < read_len)
            {
                break;
            }
        }
        fclose(file);
        return result;
    }
}