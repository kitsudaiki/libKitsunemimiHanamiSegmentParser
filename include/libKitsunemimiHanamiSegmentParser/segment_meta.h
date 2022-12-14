/**
 * @file       segment_meta.h
 *
 * @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 * @copyright  Apache License Version 2.0
 *
 *      Copyright 2022 Tobias Anker
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
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
    float synapseSegmentation = 0;
    float signNeg = 0.0;
    std::vector<BrickMeta> bricks;

    BrickMeta*
    getBrick(const std::string &name)
    {
        BrickMeta* tempBrick = nullptr;
        for(uint64_t i = 0; i < bricks.size(); i++)
        {
            tempBrick = &bricks[i];
            if(tempBrick->name == name) {
                return tempBrick;
            }
        }
        return tempBrick;
    }
};


bool
parseSegment(SegmentMeta* result,
             const std::string &input,
             ErrorContainer &error);

}  // namespace Hanami
}  // namespace Kitsunemimi

#endif // KITSUNEMIMI_HANAMI_SEGMENT_PARSER_ITEM_H
