//
//  wordkit_test.c
//  WordKit
//
//  Created by Nathan Burgers on 12/27/13.
//  Copyright (c) 2013 Nathan Burgers. All rights reserved.
//

#include "prefix.h"
#include "list.h"
#include "peg.h"
#include <stdio.h>
#include <string.h>

#define TNRM "\x1B[0m"
#define TRED "\x1B[31m"
#define TGRN "\x1B[32m"
#define TCYN "\x1B[36m"

#define TEST_SECTION(NAME) printf("\n--[ %s ]--\n", (NAME))
#define LOG(EXPR) printf("%s[%s %s line %d] %s => %s %s\n", TCYN, __FILE__, __test_name__, __LINE__, (#EXPR), (EXPR), TNRM)
#define FAIL(PRED) printf("%s[%s %s line %d] %s failed%s\n", TRED, __FILE__, __test_name__, __LINE__, (#PRED), TNRM)
#define PASS(PRED) printf("%s[%s %s line %d] %s passed%s\n", TGRN, __FILE__, __test_name__, __LINE__, (#PRED), TNRM)
#define ASSERT(PRED) (PRED) ? PASS(PRED) : FAIL(PRED)

#define TEST(NAME) __test_name__ = (#NAME); TEST_SECTION(#NAME);
#define BEGIN_TESTS void run_tests(void) { char* __test_name__ = "";
#define END_TESTS }
    
BEGIN_TESTS

TEST(StringIncludesCharacterTest) {
    ASSERT(StringIncludesCharacter("abc", 'a'));
    ASSERT(StringIncludesCharacter(string("abc"), 'c'));
    ASSERT(! StringIncludesCharacter("abc", 'd'));
    ASSERT(! StringIncludesCharacter(string("abc"), 'd'));
}

TEST(ConjunctiveParserTest) {
    Parser abc = ParserWithCharacterClass("abc");
    Parser then = ParserWithConjunction(abc, abc);
    ParseResult result = parse(then, "bcaz");
    ASSERT(ParseResultSuccess(result));
    ASSERT(((String)ListHead(ParseResultValue(result)))[0] == 'b');
    ASSERT(((String)ListHead(ListTail(ParseResultValue(result))))[0] == 'c');
    ASSERT(strcmp(ParseResultRemainder(result), "az") == 0);
    ASSERT(strcmp(ParseResultRemainder(result), "asdf") > 0);
}

TEST(DisjunctiveParserTest) {
    Parser abc = ParserWithCharacterClass("abc");
    Parser xyz = ParserWithCharacterClass("xyz");
    Parser disjunctiveParser = ParserWithDisjunction(abc, xyz);
    Parser parse2 = ParserWithConjunction(disjunctiveParser, disjunctiveParser);
    ParseResult result = parse(parse2, "zbdac");
    ASSERT(ParseResultSuccess(result));
    ASSERT(((String)ListHead(ParseResultValue(result)))[0] == 'z');
    ASSERT(((String)ListHead(ListTail(ParseResultValue(result))))[0] == 'b');
    ASSERT(strcmp(ParseResultRemainder(result), "dac") == 0);
}

END_TESTS

int main() {
    run_tests();
    return 0;
}