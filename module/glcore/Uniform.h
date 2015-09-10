//
//  Uniform.h
//  glpro
//
//  Created by wcchan on 15/7/20.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __GLCORE_UNIFORM_H__
#define __GLCORE_UNIFORM_H__

#include "config.h"

namespace glcore
{
    class Uniform
    {
    public:
        explicit Uniform(GLuint slot = 0) : _slot(slot)
        {
        }
        
        GLuint slot() const
        {
            return _slot;
        }
        
        void setMatrix(const GLfloat matrix[16])
        {
            glUniformMatrix4fv(_slot, 1, 0, matrix);
        }
        
        void setColor(const GLfloat color[4])
        {
            glUniform4fv(_slot, 1, color);
        }
        
        void set(GLint v)
        {
            glUniform1i(_slot, v);
        }
        
    private:
        GLuint _slot;
    };
}

#endif

