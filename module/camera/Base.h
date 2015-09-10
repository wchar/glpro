//
//  Camera.h
//  glpro
//
//  Created by PatGame on 15/7/22.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __CAMERA_BASE_H__
#define __CAMERA_BASE_H__

#include "glm/matrix.hpp"

namespace camera
{
    class Base
    {
    public:
        const glm::vec3& getEye()
        {
            return _eye;
        }
        const glm::vec3& getCenter()
        {
            return _center;
        }
        const int getWidth() const
        {
            return _width;
        }
        const int getHeight() const
        {
            return _height;
        }
        const glm::mat4x4& getView() const
        {
            return _view;
        }
        const glm::mat4x4& getProj() const
        {
            return _proj;
        }
        glm::mat4x4 getViewProj() const
        {
            return _view * _proj;
        }
        virtual glm::mat4x4 getModel() const
        {
            return glm::mat4x4();
        }
        void initView(const glm::vec3& eye, const glm::vec3 center, const glm::vec3& up = glm::vec3(0, 100, 0));
        void initProj(int width, int height);

    protected:
        virtual void onWindowChanged(int width, int height);

    private:
        glm::mat4x4 _view;
        glm::mat4x4 _proj;

        glm::vec3 _eye;
        glm::vec3 _center;

        int _width;
        int _height;
    };
}

#endif
