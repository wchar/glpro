//
//  main.cpp
//  glpro
//
//  Created by wcchan on 15/7/18.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "../module/glcore/system.h"
#include "../module/glcore/glcore.h"
#include "../module/particle/Emittor.h"
#include "../module/camera/Base.h"
#include "../module/camera/ModelViewer.h"
#include "../module/particle/ParticleSystem.h"

#include "CoordinateAxis.h"
#include "WatchProgram.h"

#include "Loader.h"
#include "fsys/Watcher.h"

using namespace glcore;

// statics
static WatchProgram s_watchProgram;
static Attribute s_position;
static Attribute s_color;
static Uniform s_MVP_Matrix;
static std::string s_appName;
static camera::ModelViewer s_camera;
static CoordinateAxis s_coordinateAxis;
static int s_width = 600;
static int s_height = 400;

static module::ParticleSystemArchetype s_psa;
static module::ParticleSystem s_ps(s_psa);

// callback
void onInit();
void onDisplay();
void onReshape(int w, int h);
void onMouseBegan(int x, int y)
{
    s_camera.began(x, y);
}
void onMouseMoved(int x, int y)
{
    s_camera.moved(x, y);
}
void onMouseEnded(int x, int y)
{
    s_camera.ended(x, y);
}

// main
int main(int argc, char* argv[])
{
    glcore::System system(argc, argv);
    system.onInit = onInit;
    system.onDisplay = onDisplay;
    system.onReshape = onReshape;
    system.onMouseBegan = onMouseBegan;
    system.onMouseMoved = onMouseMoved;
    system.onMouseEnded = onMouseEnded;
    system.runInWindow("ParticleSystem", 100, 600, s_width, s_height);

    return 0;
}

//
// function defines
//
void onInit()
{
    s_camera.initProj(s_width, s_height);

    auto vertName = System::getInstance()->getAppPath() + "/shader/particle.vert";
    auto fragName = System::getInstance()->getAppPath() + "/shader/particle.frag";
    s_watchProgram.create(vertName, fragName);

    s_position = s_watchProgram.getAttribute("a_position");
    s_color = s_watchProgram.getAttribute("a_color");
    s_MVP_Matrix = s_watchProgram.getUniform("u_matrixModelViewProj");

    s_coordinateAxis.init(s_position, s_color);
    
//    auto configPath = System::getInstance()->getAppPath() + "/config/config";
    auto configPath = "/Users/wcchan/快盘/glpro/glpro/config/config";
    auto refreshConfig = [=]()
    {
        s_psa = module::translator::parse(configPath);
        s_ps = module::ParticleSystem(s_psa);
        puts("=== config changed ===");
    };
    
    refreshConfig();
    fsys::watchFile(configPath, refreshConfig);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.01f);
}

void onReshape(int w, int h)
{
    s_camera.initProj(w, h);
    glViewport(0, 0, w, h);
}

void onDisplay()
{
    glClearColor(0.12, 0.18, 0.25, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    s_watchProgram.use();

    glDisable(GL_BLEND);
    auto mat = s_camera.getProj() * s_camera.getView() * s_camera.getModel();
    s_MVP_Matrix.setMatrix((float*)&mat);
    s_coordinateAxis.draw();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    auto modelView = s_camera.getView() * s_camera.getModel();
    glUseProgram(0);
    glLoadMatrixf((float*)&mat);
    s_ps.update(0.02);
    s_ps.render(&s_camera);
}
