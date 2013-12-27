//
//  list.c
//  WordKit
//
//  Created by Nathan Burgers on 12/27/13.
//  Copyright (c) 2013 Nathan Burgers. All rights reserved.
//

#include "list.h"
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

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

#pragma mark - Linked Lists

struct _List {
    Dynamic head;
    List tail;
};

inline List ListNil()
{
    return NULL;
}

inline List ListWithHead(Dynamic head)
{
    return ListWithHeadAndTail(head, NULL);
}

List ListWithHeadAndTail(Dynamic head, List tail)
{
    assert(head != NULL);
    const struct _List List = {
        .head = head,
        .tail = tail,
    };
    return heapCopy(&List, sizeof(struct _List));
}

static List _ListWithElements(Dynamic element, va_list elements)
{
    if (element == NULL) {
        return ListNil();
    } else {
        Dynamic nextElement = va_arg(elements, Dynamic);
        return ListWithHeadAndTail(element, _ListWithElements(nextElement, elements));
    }
}

List ListWithElements(Dynamic element, ...)
{
    va_list arguments;
    va_start(arguments, element);
    List list = _ListWithElements(element, arguments);
    va_end(arguments);
    return list;
}

inline Dynamic ListHead(List list)
{
    assert(list != NULL);
    return list->head;
}

inline List ListTail(List list)
{
    assert(list != NULL);
    return list->tail;
}

List ListElementAtIndex(List list, UInteger index)
{
    assert(list != NULL); // will crash if index > length(list);
    if (index == 0) {
        return ListHead(list);
    } else {
        return ListElementAtIndex(list, index-1);
    }
}

// FIXME: put into tail form, this will cause a stack explosion on
// reasonably sized strings.
List ListWithString(String string)
{
    if (string == NULL) {
        return ListNil();
    } else {
        return ListWithHeadAndTail(string, ListWithString(string+1));
    }
}



