//
//  list.h
//  WordKit
//
//  Created by Nathan Burgers on 12/27/13.
//  Copyright (c) 2013 Nathan Burgers. All rights reserved.
//

#ifndef WordKit_list_h
#define WordKit_list_h

#include "prefix.h"

Integer integerHash(Integer);

String string(String);

typedef const struct _List *const List;

#define L(...) ListWithElements(__VA_ARGS__, NULL)
List ListNil();
List ListWithHead(Dynamic head);
List ListWithHeadAndTail(Dynamic head, List tail);
List ListWithElements(Dynamic element, ...);
List ListWithString(String);
List ListElementAtIndex(List, UInteger);
List ListFindString(List, String);

Dynamic ListHead(List);
List ListTail(List);

#endif
