//
//  prefix.h
//  WordKit
//
//  Created by Nathan Burgers on 12/26/13.
//  Copyright (c) 2013 Nathan Burgers. All rights reserved.
//

#ifndef WordKit_prefix_h
#define WordKit_prefix_h

#include <stdlib.h>
#include <string.h>

typedef const void *const Dynamic;
typedef const char *const String;
typedef const char Unichar;
typedef const unsigned int UInteger;
typedef const int Integer;
typedef const enum {
    False = 0,
    True = 1,
} Boolean;

String string(String);

Integer integerHash(Integer);
void *heapCopy(const void *stackAllocatedObject, size_t length);

#endif
