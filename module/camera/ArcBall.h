//
//  ArcBall.h
//  glpro
//
//  Created by wcchan on 15/7/22.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __CAMERA_ARCBALL_H__
#define __CAMERA_ARCBALL_H__

#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/gtc/quaternion.hpp"

namespace camera
{
    class ArcBall
    {
    public:
        ArcBall();
        void setWindow(int width, int height, float radius = 1.5)
        {
            _width = width;
            _height = height;
            _radius = radius;
        }

        void began(int x, int y);
        void moved(int x, int y);
        void ended(int x, int y);

        glm::mat4x4 getRotationMatrix()
        {
            return glm::mat4x4(_rot);
        }

        const glm::quat& getRotation() const
        {
            return _rot;
        }

    private:
        glm::quat _rot;
        glm::vec3 _downPt;
        glm::vec3 _currentPt;

        glm::vec3 screenToVector(int x, int y);

        float _radius;
        int _width;
        int _height;
        bool _drag;
    };
}

#endif
