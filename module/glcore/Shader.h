//
//  Shader.h
//  glpro
//
//  Created by wcchan on 15/7/20.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __GLCORE_SHADER_H__
#define __GLCORE_SHADER_H__

#include "config.h"
#include <string>

namespace glcore
{
    class Shader
    {
    public:
        bool compile(const GLchar* source);
        std::string getInfoLog() const;
        GLuint slot() const;
        
    protected:
        Shader(GLenum type);
        ~Shader();
        
    private:
        GLuint _shader;
    };

    class VertexShader : public Shader
    {
    public:
        VertexShader();
    };

    class FragmentShader : public Shader
    {
    public:
        FragmentShader();
    };
}

#endif

