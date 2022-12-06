#ifndef SEGMENT_PARSESTRING_TEST_H
#define SEGMENT_PARSESTRING_TEST_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

namespace Kitsunemimi
{
namespace Hanami
{

class Segment_ParseString_Test
        : public Kitsunemimi::CompareTestHelper
{
public:
    Segment_ParseString_Test();

private:
    void parseString_test();
};

}  // namespace Hanami
}  // namespace Kitsunemimi

#endif // SEGMENT_PARSESTRING_TEST_H
