//
//  prefix.c
//  WordKit
//
//  Created by Nathan Burgers on 12/27/13.
//  Copyright (c) 2013 Nathan Burgers. All rights reserved.
//

#include "prefix.h"

#pragma mark - Strings

String string(String stackString)
{
    return heapCopy(stackString, strlen(stackString));
}

#pragma mark - Memory Management

Integer integerHash(Integer x)
{
    Integer a = ((x >> 16) ^ x) * 0x45d9f3b;
    Integer b = ((a >> 16) ^ a) * 0x45d9f3b;
    Integer c = (b >> 16) ^ b;
    return c;
}

void *heapCopy(const void *stackAllocatedObject, size_t length)
{
    void *buffer = malloc(length);
    memcpy(buffer, stackAllocatedObject, length);
    return buffer;
}