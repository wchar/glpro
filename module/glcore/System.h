//
//  System.h
//  glpro
//
//  Created by wcchan on 15/7/18.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __GLCORE_SYETEM_H__
#define __GLCORE_SYETEM_H__

#include <glut/glut.h>
#include <functional>
#include <string>

namespace glcore
{
    class System
    {
    public:
        static System* getInstance();
        
        System(int argc, char** argv);
        ~System();
        
        void postRedisplay();
        void redisplay();
        
        void runInWindow(const char* title);
        void runInWindow(const char* title, int x, int y, int width, int height);
        
        std::function<void(void)> onDisplay;
        std::function<void(void)> onInit;
        std::function<void(int x, int y)> onMouseBegan;
        std::function<void(int x, int y)> onMouseMoved;
        std::function<void(int x, int y)> onMouseEnded;
        std::function<void(int width, int height)> onReshape;
        
        const std::string& getAppPath()
        {
            return _appPath;
        }
        
    private:
        std::string _appPath;
    };
}

#endif

