//
//  Shader.cpp
//  glpro
//
//  Created by wcchan on 15/7/20.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "Shader.h"
#include <assert.h>
#include <stdio.h>
#include <vector>

namespace glcore
{
    Shader::Shader(GLenum type)
    {
        _shader = glCreateShader((GLenum)type);
    }
    
    Shader::~Shader()
    {
        if (_shader != 0)
        {
            glDeleteShader(_shader);
        }
    }
    
    bool Shader::compile(const GLchar* source)
    {
        assert(source);
        
        glShaderSource(_shader, 1, &source, NULL);
        glCompileShader(_shader);
        
        GLint status;
        glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);
        
        return (status == GL_TRUE);
    }
    
    GLuint Shader::slot() const
    {
        return _shader;
    }
    
    std::string Shader::getInfoLog() const
    {
        GLint infoLen = 0;
        glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &infoLen);
        
        if (infoLen > 1)
        {
            std::vector<char> buf(infoLen);
            glGetShaderInfoLog(_shader, infoLen, NULL, &buf[0]);
            return std::string(&buf[0]);
        }
        return std::string("");
    }
    
    VertexShader::VertexShader() : Shader(GL_VERTEX_SHADER)
    {
    }
    
    FragmentShader::FragmentShader() : Shader(GL_FRAGMENT_SHADER)
    {
    }
}
