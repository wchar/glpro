//
//  Watcher.h
//  glpro
//
//  Created by PatGame on 15/7/21.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __FSYS_WATCHER_H__
#define __FSYS_WATCHER_H__

#include <functional>
#include <string>

namespace fsys
{
    void watchFile(const std::string& path, std::function<void()> callback);
}

#endif

