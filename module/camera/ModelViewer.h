//
//  ModelViewer.h
//  glpro
//
//  Created by PatGame on 15/7/22.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __CAMERA__MODELVIEWER_H__
#define __CAMERA__MODELVIEWER_H__

#include "Base.h"
#include "ArcBall.h"

namespace camera
{
    class ModelViewer : public Base
    {
    public:
        ModelViewer();
        
        void began(int x, int y);
        void moved(int x, int y);
        void ended(int x, int y);
        void update();

        glm::mat4x4 getModel() const override
        {
            return _modelRot;
        }
    protected:
        virtual void onWindowChanged(int width, int height) override;
        
    private:
        ArcBall _modelArcBall;
        
        glm::mat4x4 _modelLastRot;
        glm::mat4x4 _modelRot;
    };
}

#endif

