//
//  Attribute.h
//  glpro
//
//  Created by wcchan on 15/7/20.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __GLCORE_ATTRIBUTE_H__
#define __GLCORE_ATTRIBUTE_H__

#include "config.h"
#include "stdio.h"

namespace glcore
{
    class Attribute
    {
    public:
        explicit Attribute(GLuint slot = 0) : _slot(slot)
        {
        }
        
        GLuint slot() const
        {
            return _slot;
        }
        
        void enableArray()
        {
            glEnableVertexAttribArray(_slot);
        }
        
        void disableArray()
        {
            glDisableVertexAttribArray(_slot);
        }
        
        void setVec1(const GLvoid* ptr, GLsizei stride)
        {
            glVertexAttribPointer(_slot, 1, GL_FLOAT, GL_FALSE, stride, ptr);
        }
        
        void setVec2(const GLvoid* ptr, GLsizei stride)
        {
            glVertexAttribPointer(_slot, 2, GL_FLOAT, GL_FALSE, stride, ptr);
        }
        
        void setVec3(const GLvoid* ptr, GLsizei stride)
        {
            glVertexAttribPointer(_slot, 3, GL_FLOAT, GL_FALSE, stride, ptr);
        }
        
        void setVec4(const GLvoid* ptr, GLsizei stride)
        {
            glVertexAttribPointer(_slot, 4, GL_FLOAT, GL_FALSE, stride, ptr);
        }
    private:
        GLuint _slot;
    };
}

#endif
