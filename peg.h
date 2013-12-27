//
//  peg.h
//  WordKit
//
//  Created by Nathan Burgers on 12/26/13.
//  Copyright (c) 2013 Nathan Burgers. All rights reserved.
//

#ifndef WordKit_peg_h
#define WordKit_peg_h

#include "prefix.h"

Boolean StringIncludesCharacter(String, Unichar);

enum ParseResultVariants {
    ParseResultUnconsumedError,
    ParseResultConsumedError,
    ParseResultUnconsumedSuccess,
    ParseResultConsumedSuccess,
};

typedef const struct _ParseError *const ParseError;
typedef const struct _ParseResult *const ParseResult;
typedef const struct _Parser *const Parser;

ParseResult ParseResultSuccessfullyConsuming(Dynamic result, String remainder);
ParseResult ParseResultSuccessfullyNonconsuming(Dynamic result, String remainder);
ParseResult ParseResultFailingConsuming(String remainder, ParseError error);

Boolean ParseResultSuccess(ParseResult);
Boolean ParseResultConsumed(ParseResult);
Dynamic ParseResultValue(ParseResult);
String ParseResultRemainder(ParseResult);

Parser ParserWithCharacterClass(String);
Parser ParserWithConjunction(Parser, Parser);
Parser ParserWithDisjunction(Parser, Parser);
Parser ParserWithMany(Parser);
Parser ParserWithPossiblyMany(Parser);
Parser ParserWithOptional(Parser);
Parser ParserOrParser(Parser, Parser);
Parser ParserAndParser(Parser, Parser);

ParseResult parse(Parser, String);

#endif
