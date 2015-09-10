//
//  System.cpp
//  glpro
//
//  Created by wcchan on 15/7/18.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "System.h"
#include <assert.h>
#include <unistd.h>
#include <vector>
#include <unistd.h>

namespace glcore
{
    std::string s_realPath(const std::string& path)
    {
        std::vector<char> buf;
        buf.resize(path.size());
        realpath(path.c_str(), buf.data());
        return buf.data();
    }
    
    static System* s_globalSys = 0;
    static void s_display()
    {
        assert(s_globalSys);
        s_globalSys->onDisplay();
        glutSwapBuffers();
        sleep(0.02);
        glutPostRedisplay();
    }
    
    static void s_reshape(int w, int h)
    {
        s_globalSys->onReshape(w, h);
    }
    
    static void s_motion(int x, int y)
    {
        s_globalSys->onMouseMoved(x, y);
    }
    
    void s_mouse(int button,int state,int x,int y)
    {
        if (state==GLUT_DOWN)
        {
            s_globalSys->onMouseBegan(x, y);
        }
        
        if (state==GLUT_UP)
        {
            s_globalSys->onMouseEnded(x, y);
        }
    }
    
    //////////////////////////////////////////
    System::System(int argc, char** argv)
    {
        if (s_globalSys == 0)
        {
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        }
        s_globalSys = this;
        
        onMouseBegan =
        onMouseMoved =
        onMouseEnded = ^(int, int){};
        onInit =
        onDisplay = ^(){};
        onReshape = ^(int w, int h){
            glViewport(0, 0, w, h);
        };

        _appPath = s_realPath(std::string(argv[0]) + "/../");
    }
    
    System* System::getInstance()
    {
        return s_globalSys;
    }
    
    System::~System()
    {
        if (s_globalSys == this)
        {
            s_globalSys = 0;
        }
    }
    
    void System::postRedisplay()
    {
        glutPostRedisplay();
    }
    
    void System::redisplay()
    {
        s_display();
    }
    
    void System::runInWindow(const char* title)
    {
        runInWindow(title, 100, 100, 200, 200);
    }
    
    void System::runInWindow(const char* title, int x, int y, int width, int height)
    {
        glutInitWindowPosition(x, y);
        glutInitWindowSize(width, height);
        glutCreateWindow(title);
        
        if (onInit)
        {
            onInit();
        }
        
        glutDisplayFunc(s_display);
        glutReshapeFunc(s_reshape);
        glutMouseFunc(s_mouse);
        glutMotionFunc(s_motion);
        glutMainLoop();
    }
}
