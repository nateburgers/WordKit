//
//  prefix.c
//  WordKit
//
//  Created by Nathan Burgers on 12/27/13.
//  Copyright (c) 2013 Nathan Burgers. All rights reserved.
//

#include "prefix.h"

void *heapCopy(const void *stackAllocatedObject, size_t length)
{
    void *buffer = malloc(length);
    memcpy(buffer, stackAllocatedObject, length);
    return buffer;
}