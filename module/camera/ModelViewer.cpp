//
//  ModelViewer.cpp
//  glpro
//
//  Created by PatGame on 15/7/22.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "ModelViewer.h"

namespace camera
{
    ModelViewer::ModelViewer()
    {
        initView({0, 0, 6}, {0, 0, 0});
    }
    
    void ModelViewer::began(int x, int y)
    {
        _modelArcBall.began(x, y);
    }
    
    void ModelViewer::moved(int x, int y)
    {
        _modelArcBall.moved(x, y);
        update();  
    }
    
    void ModelViewer::ended(int x, int y)
    {
        _modelArcBall.ended(x, y);
        _modelLastRot = glm::mat4x4();
    }
    
    void ModelViewer::update()
    {
        auto rot = _modelArcBall.getRotation();
        rot *= rot;
        auto modelRot = glm::mat4x4(rot);
        _modelRot = modelRot * glm::inverse(_modelLastRot) * _modelRot;
        _modelLastRot = modelRot;
    }
    
    void ModelViewer::onWindowChanged(int width, int height)
    {
        Base::onWindowChanged(width, height);
        _modelArcBall.setWindow(width, height);
    }
}