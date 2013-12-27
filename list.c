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

#pragma mark - Linked Lists

enum ListType {
    ListTypeNil,
    ListTypeCons,
};

struct _List {
    const enum ListType type;
    const union {
        struct { } nil;
        struct { Dynamic head; List tail; } cons;
    } variant;
};

inline List ListNil()
{
    static const struct _List list = {
        .type = ListTypeNil,
    };
    return heapCopy(&list, sizeof(struct _List));
}

inline List ListWithHead(Dynamic head)
{
    return ListWithHeadAndTail(head, ListNil());
}

List ListWithHeadAndTail(Dynamic head, List tail)
{
    assert(head != NULL);
    assert(tail != NULL);
    const struct _List List = {
        .type = ListTypeCons,
        .variant.cons = {
            .head = head,
            .tail = tail,
        }
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
    assert(list->type == ListTypeCons);
    return list->variant.cons.head;
}

inline List ListTail(List list)
{
    assert(list != NULL);
    assert(list->type == ListTypeCons);
    return list->variant.cons.tail;
}

List ListElementAtIndex(List list, UInteger index)
{
    assert(list->type != ListTypeNil);
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



