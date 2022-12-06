/**
 *  @file    main.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include <iostream>

#include <segment_parsestring_test.h>
#include <libKitsunemimiCommon/logger.h>

int main()
{
    Kitsunemimi::initConsoleLogger(true);
    Kitsunemimi::Hanami::Segment_ParseString_Test();
}
