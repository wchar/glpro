//
//  Program.h
//  glpro
//
//  Created by wcchan on 15/7/20.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __GLCORE_PROGRAM_H__
#define __GLCORE_PROGRAM_H__

#include "config.h"
#include <string>
#include "Shader.h"
#include "Attribute.h"
#include "Uniform.h"

namespace glcore
{
    class Program
    {
    public:
        Program();
        Program(Program&& rhs);
        void operator=(Program&& rhs);
        ~Program();
        
        bool link(const VertexShader& shader0, const FragmentShader& shader1);
        bool link(const FragmentShader& shader0, const VertexShader& shader1);
        std::string getInfoLog() const;
        void use();
        
        GLuint slot() const;
        GLuint detachSlot();
        
        Attribute getAttribute(const char* name) const;
        Uniform getUniform(const char* name) const;
    private:
        GLuint _program;
    };
}

#endif 

