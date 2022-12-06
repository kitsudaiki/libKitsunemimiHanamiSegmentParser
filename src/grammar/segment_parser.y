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
#include <map>
#include <vector>
#include <libKitsunemimiHanamiCommon/structs.h>
#include <libKitsunemimiHanamiSegmentParser/segment_meta.h>

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
    COMMA  ","
    ASSIGN  ":"
    LINEBREAK "linebreak"
    VERSION_1 "version1"
    SEGMENT_TYPE "segment_type"
    SETTINGS "settings"
    BRICKS "bricks"
;

%token <std::string> IDENTIFIER "identifier"
%token <std::string> STRING "string"
%token <std::string> STRING_PLN "string_pln"
%token <long> NUMBER "number"
%token <double> FLOAT "float"

%type  <Kitsunemimi::Hanami::Position> position
%type  <Kitsunemimi::Hanami::BrickMeta> brick_settings

%%
%start startpoint;

// version: 1
// segment_type: dynamic_segment
// settings:
//     max_synapse_sections: 100000
//     synapse_segmentation: 10
//     sign_neg: 0.5
//
// bricks:
//     1,1,1
//         input: test_input
//         number_of_neurons: 20
//
//     2,1,1
//         number_of_neurons": 10
//
//     3,1,1
//         output: test_output
//         number_of_neurons: 5

startpoint:
    "version1" linebreaks segment_type "settings" "linebreak" settings "bricks" "linebreak" bricks
    {

    }

segment_type:
    "segment_type" ":" "identifier" "linebreak"
    {
        if($3 == "dynamic_segment") {
            driver.output->segmentType = DYNAMIC_SEGMENT_TYPE;
        } else {
            driver.error(yyla.location, "unkown segment-type '" + $3 + "'");
            return 1;
        }
    }

settings:
    settings "identifier" ":" "float" "linebreak"
    {
        std::any val = $4;
        driver.output->settings.emplace($2, val);
    }
|
    settings "identifier" ":" "number" "linebreak"
    {
        std::any val = $4;
        driver.output->settings.emplace($2, val);
    }
|
    "identifier" ":" "float" "linebreak"
    {
        std::any val = $3;
        driver.output->settings.emplace($1, val);
    }
|
    "identifier" ":" "number" "linebreak"
    {
        std::any val = $3;
        driver.output->settings.emplace($1, val);
    }

bricks:
    bricks position "linebreak" brick_settings
    {
        $4.position = $2;
        driver.output->bricks.push_back($4);
    }
|
    position "linebreak" brick_settings
    {
        $3.position = $1;
        driver.output->bricks.push_back($3);
    }

brick_settings:
    brick_settings "identifier" ":" "identifier" "linebreak"
    {
        if($2 == "input")
        {
            $1.type = INPUT_BRICK_TYPE;
            $1.name = $4;
        }
        else if($2 == "output")
        {
            $1.type = OUTPUT_BRICK_TYPE;
            $1.name = $4;
        }
        else
        {
            driver.error(yyla.location, "unkown brick-field '" + $2 + "'");
            return 1;
        }

        $$ = $1;
    }
|
    brick_settings "identifier" ":" "number" "linebreak"
    {
        if($2 == "number_of_neurons")
        {
            $1.numberOfNeurons = $4;
        }
        else
        {
            driver.error(yyla.location, "unkown brick-field '" + $2 + "'");
            return 1;
        }

        $$ = $1;
    }
|
    "identifier" ":" "identifier" "linebreak"
    {
        Kitsunemimi::Hanami::BrickMeta brickMeta;

        if($1 == "input")
        {
            brickMeta.type = INPUT_BRICK_TYPE;
            brickMeta.name = $3;
        }
        else if($1 == "output")
        {
            brickMeta.type = OUTPUT_BRICK_TYPE;
            brickMeta.name = $3;
        }
        else
        {
            driver.error(yyla.location, "unkown brick-field '" + $1 + "'");
            return 1;
        }

        $$ = brickMeta;
    }
|
    "identifier" ":" "number" "linebreak"
    {
        Kitsunemimi::Hanami::BrickMeta brickMeta;

        if($1 == "number_of_neurons")
        {
            brickMeta.numberOfNeurons = $3;
        }
        else
        {
            driver.error(yyla.location, "unkown brick-field '" + $1 + "'");
            return 1;
        }

        $$ = brickMeta;
    }

position:
    "number" "," "number" "," "number"
    {
        Kitsunemimi::Hanami::Position pos;
        pos.x = $1;
        pos.y = $3;
        pos.z = $5;
        $$ = pos;
    }

linebreaks:
    linebreaks "linebreak"
    {}
|
    "linebreak"
    {}
%%

void Kitsunemimi::Hanami::SegmentParser::error(const Kitsunemimi::Hanami::location& location,
                                               const std::string& message)
{
    driver.error(location, message);
}
