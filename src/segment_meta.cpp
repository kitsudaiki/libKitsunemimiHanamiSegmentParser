/**
 *  @file    segment_meta.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include <libKitsunemimiHanamiSegmentParser/segment_meta.h>
#include <segment_parsing/segment_parser_interface.h>

namespace Kitsunemimi
{
namespace Hanami
{

/**
 * @brief convert a segment-formated string into a segment-object-tree
 *
 * @param input segment-formated string, which should be parsed
 * @param error reference for error-message output
 *
 * @return true, if successful, else false
 */
inline bool
parseSegment(SegmentMeta* result,
             const std::string &input,
             ErrorContainer &error)
{
    SegmentParserInterface* parser = SegmentParserInterface::getInstance();

    if(input.size() == 0)
    {
        // TODO: error-message
        return false;
    }

    return parser->parse(result, input, error);
}

}  // namespace Hanami
}  // namespace Kitsunemimi
