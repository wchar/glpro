//
//  Program.cpp
//  glpro
//
//  Created by wcchan on 15/7/20.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "Program.h"
#include <stdio.h>
#include <vector>

namespace glcore
{
    static inline void deleteProgram(GLuint slot)
    {
        if (slot)
        {
            glDeleteProgram(slot);
        }
    }
    
    Program::Program()
    {
        _program = 0;
    }
    
    Program::Program(Program&& rhs)
    {
        _program = rhs._program;
        rhs._program = 0;
    }
    
    void Program::operator=(Program&& rhs)
    {
        deleteProgram(_program);
        _program = rhs._program;
        rhs._program = 0;
    }
    
    Program::~Program()
    {
        deleteProgram(_program);
    }
    
    GLuint Program::detachSlot()
    {
        auto slot = _program;
        _program = 0;
        return slot;
    }
    
    void Program::use()
    {
        glUseProgram(_program);
    }
    
    bool Program::link(const FragmentShader& shader0, const VertexShader& shader1)
    {
        return link(shader1, shader0);
    }
    
    GLuint Program::slot() const
    {
        return _program;
    }
    
    bool Program::link(const VertexShader& shader0, const FragmentShader& shader1)
    {
        deleteProgram(_program);
        _program = glCreateProgram();
        
        glAttachShader(_program, shader0.slot());
        glAttachShader(_program, shader1.slot());
        
        glLinkProgram(_program);
        
        GLint status = 0;
        glGetProgramiv(_program, GL_LINK_STATUS, &status);
        return (status == GL_TRUE);
    }
    
    std::string Program::getInfoLog() const
    {
        GLint infoLen = 0;
        glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1)
        {
            std::vector<char> buf(infoLen);
            glGetProgramInfoLog(_program, infoLen, NULL, &buf[0]);
            return std::string(&buf[0]);
        }
        return std::string("");
    }
    
    Attribute Program::getAttribute(const char* name) const
    {
        auto location = glGetAttribLocation(_program, name);
        return Attribute(location);
    }
    
    Uniform Program::getUniform(const char* name) const
    {
        auto location = glGetUniformLocation(_program, name);
        return Uniform(location);
    }
}
