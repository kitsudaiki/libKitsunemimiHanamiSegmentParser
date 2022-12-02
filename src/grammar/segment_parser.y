/**
 *  @file    segment_parser.y
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

%skeleton "lalr1.cc"

%defines
%require "3.0.4"

%define parser_class_name {SegmentParser}

%define api.prefix {segment}
%define api.namespace {Kitsunemimi::Hanami}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include <string>
#include <iostream>
#include <libKitsunemimiCommon/items/data_items.h>

using Kitsunemimi::DataItem;
using Kitsunemimi::DataArray;
using Kitsunemimi::DataValue;
using Kitsunemimi::DataMap;


namespace Kitsunemimi
{
namespace Hanami
{

class SegmentParserInterface;

}  // namespace Hanami
}  // namespace Kitsunemimi
}

// The parsing context.
%param { Kitsunemimi::Hanami::SegmentParserInterface& driver }

%locations

%code
{
#include <segment_parsing/segment_parser_interface.h>
# undef YY_DECL
# define YY_DECL \
    Kitsunemimi::Hanami::SegmentParser::symbol_type segmentlex (Kitsunemimi::Hanami::SegmentParserInterface& driver)
YY_DECL;
}

// Token
%define api.token.prefix {Segment_}
%token
    END  0  "end of file"
    EXPRESTART  "{"
    EXPREEND  "}"
    BRACKOPEN  "["
    BRACKCLOSE  "]"
    COMMA  ","
    ASSIGN  ":"
    BOOL_TRUE  "true"
    BOOL_FALSE "false"
    NULLVAL "null"
;


%token <std::string> IDENTIFIER "identifier"
%token <std::string> STRING "string"
%token <std::string> STRING_PLN "string_pln"
%token <long> NUMBER "number"
%token <double> FLOAT "float"
ent

%%
%start startpoint;


startpoint:
    "identifier"
    {

    }

%%

void Kitsunemimi::Hanami::SegmentParser::error(const Kitsunemimi::Hanami::location& location,
                                               const std::string& message)
{
    driver.error(location, message);
}
