//
//  peg.c
//  WordKit
//
//  Created by Nathan Burgers on 12/26/13.
//  Copyright (c) 2013 Nathan Burgers. All rights reserved.
//

#include "peg.h"
#include "list.h"
#include <stdio.h>
#include <assert.h>

#pragma mark - Private Headers

Boolean StringIncludesCharacter(String, Unichar);
ParseResult _parseCharacterClass(Parser, String);
ParseResult _parseConjunction(Parser, String);

#pragma mark - Data Structures

struct _ParseError {
    String message;
};

struct _ParseResult {
    const enum ParseResultVariants type;
    const union {
        struct { String remainder; ParseError error; } unconsumedError;
        struct { String remainder; ParseError error; } consumedError;
        struct { Dynamic result; String remainder; } unconsumedSuccess;
        struct { Dynamic result; String remainder; } consumedSuccess;
    } variant;
};

typedef ParseResult (*const ParsingFunction)(Parser self, String);

struct _Parser {
    ParsingFunction method;
    const union {
        struct { String characterClass; } characterClassParser;
        struct { Parser parser; } monadicParser;
        struct { Parser parser0; Parser parser1; } dyadicParser;
    } variant;
};

#pragma mark - Constructors

ParseResult ParseResultSuccessfullyConsuming(Dynamic result, String remainder)
{
    const struct _ParseResult parseResult = {
        .type = ParseResultConsumedSuccess,
        .variant.consumedSuccess = {
            .result = result,
            .remainder = remainder
        }
    };
    return heapCopy(&parseResult, sizeof(struct _ParseResult));
}

ParseResult ParseResultFailingConsuming(String remainder, ParseError error)
{
    const struct _ParseResult parseResult = {
        .type = ParseResultConsumedError,
        .variant.consumedError = {
            .remainder = remainder,
            .error = error
        }
    };
    return heapCopy(&parseResult, sizeof(struct _ParseResult));
}

Boolean ParseResultSuccess(ParseResult result)
{
    return result->type == ParseResultConsumedSuccess || result->type == ParseResultUnconsumedSuccess;
}

Dynamic ParseResultValue(ParseResult result)
{
    switch (result->type) {
        case ParseResultConsumedSuccess:
            return result->variant.consumedSuccess.result;
        case ParseResultUnconsumedSuccess:
            return result->variant.unconsumedSuccess.result;
        default:
            assert(False);
            break;
    }
}

String ParseResultRemainder(ParseResult result)
{
    switch (result->type) {
        case ParseResultConsumedError:
            return result->variant.consumedError.remainder;
        case ParseResultConsumedSuccess:
            return result->variant.consumedSuccess.remainder;
        case ParseResultUnconsumedSuccess:
            return result->variant.unconsumedSuccess.remainder;
        case ParseResultUnconsumedError:
            return result->variant.unconsumedError.remainder;
    }
}

#pragma mark - Parser Constructors

Parser ParserWithCharacterClass(String string)
{
    const struct _Parser parser = {
        .method = _parseCharacterClass,
        .variant.characterClassParser = {
            .characterClass = string
        }
    };
    return heapCopy(&parser, sizeof(struct _Parser));
}

Parser ParserWithConjunction(Parser parser0, Parser parser1)
{
    const struct _Parser parser = {
        .method = _parseConjunction,
        .variant.dyadicParser = {
            .parser0 = parser0,
            .parser1 = parser1
        }
    };
    return heapCopy(&parser, sizeof(struct _Parser));
}

#pragma mark - Private

Boolean StringIncludesCharacter(String string, Unichar character)
{
    if (string[0] == '\0') {
        return False;
    }
    else if (string[0] == character) {
        return True;
    }
    else {
        return StringIncludesCharacter(string+1, character);
    }
}

#pragma mark - Parsing

ParseResult parse(Parser parser, String string)
{
    return parser->method(parser, string);
}

#pragma mark - Parsing Methods

ParseResult _parseCharacterClass(Parser parser, String string)
{
    String characterClass = parser->variant.characterClassParser.characterClass;
    Boolean success = StringIncludesCharacter(characterClass, string[0]);
    if (success) {
        return ParseResultSuccessfullyConsuming(&string[0], string+1);
    } else {
        return ParseResultFailingConsuming(string+0, NULL);
    }
}

ParseResult _parseConjunction(Parser self, String string)
{
    Parser parser0 = self->variant.dyadicParser.parser0;
    Parser parser1 = self->variant.dyadicParser.parser1;
    ParseResult result0 = parse(parser0, string);
    if (ParseResultSuccess(result0)) {
        ParseResult result1 = parse(parser1, ParseResultRemainder(result0));
        // TODO properly form this result
        return ParseResultSuccessfullyConsuming(L(ParseResultValue(result0),
                                                  ParseResultValue(result1)),
                                                ParseResultRemainder(result1));
    } else {
        return result0;
    }
}












