/**
 *  @file    segment_parser_interface.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef KITSUNEMIMI_HANAMI_SEGMENT_PARSER_PARSER_INTERFACE_H
#define KITSUNEMIMI_HANAMI_SEGMENT_PARSER_PARSER_INTERFACE_H

#include <iostream>
#include <mutex>

#include <libKitsunemimiCommon/logger.h>

namespace Kitsunemimi
{
namespace Hanami
{
struct SegmentMeta;
class location;

class SegmentParserInterface
{

public:
    static SegmentParserInterface* getInstance();
    ~SegmentParserInterface();

    // connection the the scanner and parser
    void scan_begin(const std::string &inputString);
    void scan_end();
    bool parse(SegmentMeta* result,
               const std::string &inputString,
               ErrorContainer &error);
    const std::string removeQuotes(const std::string &input);

    // Error handling.
    void error(const Kitsunemimi::Hanami::location &location,
               const std::string& message);

    bool dryRun = false;

private:
    SegmentParserInterface(const bool traceParsing = false);

    static SegmentParserInterface* m_instance;

    SegmentMeta* m_output = nullptr;
    std::string m_errorMessage = "";
    std::string m_inputString = "";
    std::mutex m_lock;

    bool m_traceParsing = false;
};

}  // namespace Hanami
}  // namespace Kitsunemimi

#endif // KITSUNEMIMI_HANAMI_SEGMENT_PARSER_PARSER_INTERFACE_H
