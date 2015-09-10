//
//  Watcher.cpp
//  glpro
//
//  Created by PatGame on 15/7/21.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#include "Watcher.h"
#include <dispatch/dispatch.h>
#include <stdlib.h>
#include <stdio.h>

static dispatch_source_t s_watchFile(const std::string& path,
                                     void (^callback)(const char* path, unsigned long flags))
{
    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    int file = open(path.c_str(), O_EVTONLY);
    unsigned int mask = DISPATCH_VNODE_DELETE
                      | DISPATCH_VNODE_WRITE
                      | DISPATCH_VNODE_EXTEND
                      | DISPATCH_VNODE_RENAME;
    auto source = dispatch_source_create(DISPATCH_SOURCE_TYPE_VNODE, file, mask, queue);
    
    const char* tmpPath = strdup(path.c_str());
    dispatch_source_set_event_handler(source, ^{
        unsigned long flags = dispatch_source_get_data(source);
        if (flags)
        {
            dispatch_async(dispatch_get_main_queue(), ^{
                callback(tmpPath, flags);
            });
        }
    });
    
    auto closeFile = ^(void) {
        free((void*)tmpPath);
        close(file);
    };
    
    dispatch_source_set_cancel_handler(source, closeFile);
    dispatch_resume(source);
    return source;
}

namespace fsys
{
    void watchFile(const std::string& file, std::function<void()> callback)
    {
        s_watchFile(file, ^(const char* tmpPath, unsigned long flags) {
            callback();
        });
    }
}
