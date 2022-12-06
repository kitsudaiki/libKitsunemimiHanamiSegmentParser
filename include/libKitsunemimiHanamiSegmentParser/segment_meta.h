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
#include <any>

#include <libKitsunemimiCommon/logger.h>
#include <libKitsunemimiHanamiCommon/structs.h>

namespace Kitsunemimi
{
namespace Hanami
{

enum SegmentType
{
    UNDEFINED_SEGMENT_TYPE = 0,
    DYNAMIC_SEGMENT_TYPE = 1,
};

enum BrickType
{
    CENTRAL_BRICK_TYPE = 0,
    INPUT_BRICK_TYPE = 1,
    OUTPUT_BRICK_TYPE = 2,
};

struct BrickMeta
{
    Position position;
    std::string name = "";
    BrickType type = CENTRAL_BRICK_TYPE;
    uint64_t numberOfNeurons = 0;
};

struct SegmentMeta
{
    uint32_t version = 0;
    SegmentType segmentType = UNDEFINED_SEGMENT_TYPE;
    uint32_t maxSynapseSections = 0;
    uint32_t synapseSegmentation = 0;
    float signNeg = 0.0;
    std::vector<BrickMeta> bricks;
};


bool
parseSegment(SegmentMeta* result,
             const std::string &input,
             ErrorContainer &error);

}  // namespace Hanami
}  // namespace Kitsunemimi

#endif // KITSUNEMIMI_HANAMI_SEGMENT_PARSER_ITEM_H
