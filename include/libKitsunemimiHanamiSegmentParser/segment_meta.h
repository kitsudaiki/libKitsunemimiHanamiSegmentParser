/**
 *  @file    segment_meta.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef KITSUNEMIMI_HANAMI_SEGMENT_PARSER_ITEM_H
#define KITSUNEMIMI_HANAMI_SEGMENT_PARSER_ITEM_H

#include <string>
#include <vector>
#include <map>

#include <libKitsunemimiCommon/logger.h>

namespace Kitsunemimi
{
namespace Hanami
{

struct SegmentMeta;

bool
parseSegment(SegmentMeta* result,
             const std::string &input,
             ErrorContainer &error);

}  // namespace Hanami
}  // namespace Kitsunemimi

#endif // KITSUNEMIMI_HANAMI_SEGMENT_PARSER_ITEM_H
