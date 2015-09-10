//
//  WatchProgram.cpp
//  glpro
//
//  Created by PatGame on 15/7/21.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "WatchProgram.h"
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include "fsys/Watcher.h"
#include "fsys/FileIO.h"

using namespace glcore;

static void s_link_program(Program* program, const std::string& vert, const std::string& frag)
{
    VertexShader vertexShader;
    if (!vertexShader.compile(vert.c_str()))
    {
        puts(vertexShader.getInfoLog().c_str());
        return;
    }
    
    FragmentShader fragShader;
    if (!fragShader.compile(frag.c_str()))
    {
        puts(fragShader.getInfoLog().c_str());
        return;
    }
    
    if (!program->link(vertexShader, fragShader))
    {
        puts(program->getInfoLog().c_str());
        return;
    }
    
    puts("=== shader linked ===");
}

void WatchProgram::create(const std::string& vertName, const std::string& fragName)
{
    _vertName = vertName;
    _fragName = fragName;
    
    refresh();
    
    auto callback = [=]()
    {
        refresh();
    };
    fsys::watchFile(_vertName, callback);
    fsys::watchFile(_fragName, callback);
}

void WatchProgram::refresh()
{
    auto vert = fsys::readFromPath(_vertName);
    auto frag = fsys::readFromPath(_fragName);
    s_link_program(this, vert, frag);
}