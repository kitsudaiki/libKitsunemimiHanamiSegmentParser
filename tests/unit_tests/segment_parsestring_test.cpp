#include "segment_parsestring_test.h"

#include <libKitsunemimiHanamiSegmentParser/segment_meta.h>

namespace Kitsunemimi
{
namespace Hanami
{

Segment_ParseString_Test::Segment_ParseString_Test()
    : Kitsunemimi::CompareTestHelper("Segment_ParseString_Test")
{
    parseString_test();
}

/**
 * parseString_test
 */
void
Segment_ParseString_Test::parseString_test()
{
    std::string input("version: 1\n"
                      "segment_type: dynamic_segment\n"
                      "settings:\n"
                      "    max_synapse_sections: 100000\n"
                      "    synapse_segmentation: 10\n"
                      "    sign_neg: 0.5\n"
                      "        \n"
                      "bricks:\n"
                      "    1,1,1\n"
                      "        input: test_input\n"
                      "        number_of_neurons: 20\n"
                      "         \n "
                      "    2,1,1\n"
                      "        number_of_neurons: 10\n"
                      "          \n"
                      "    3,1,1\n"
                      "        output: test_output\n"
                      "        number_of_neurons: 5\n");

    SegmentMeta result;
    ErrorContainer error;
    bool ret = parseSegment(&result, input, error);
    TEST_EQUAL(ret, true);
    if(ret == false) {
        LOG_ERROR(error);
    }

    TEST_EQUAL(result.version, 1);
    TEST_EQUAL(result.segmentType, DYNAMIC_SEGMENT_TYPE);

    TEST_EQUAL(result.maxSynapseSections, 100000);
    TEST_EQUAL(result.synapseSegmentation, 10);
    TEST_EQUAL(result.signNeg, 0.5);

    TEST_EQUAL(result.bricks.size(), 3);

    TEST_EQUAL(result.bricks.at(0).position.x, 1);
    TEST_EQUAL(result.bricks.at(0).position.y, 1);
    TEST_EQUAL(result.bricks.at(0).position.z, 1);
    TEST_EQUAL(result.bricks.at(0).numberOfNeurons, 20);
    TEST_EQUAL(result.bricks.at(0).name, "test_input");
    TEST_EQUAL(result.bricks.at(0).type, INPUT_BRICK_TYPE);

    TEST_EQUAL(result.bricks.at(1).position.x, 2);
    TEST_EQUAL(result.bricks.at(1).position.y, 1);
    TEST_EQUAL(result.bricks.at(1).position.z, 1);
    TEST_EQUAL(result.bricks.at(1).numberOfNeurons, 10);
    TEST_EQUAL(result.bricks.at(1).name, "");
    TEST_EQUAL(result.bricks.at(1).type, CENTRAL_BRICK_TYPE);

    TEST_EQUAL(result.bricks.at(2).position.x, 3);
    TEST_EQUAL(result.bricks.at(2).position.y, 1);
    TEST_EQUAL(result.bricks.at(2).position.z, 1);
    TEST_EQUAL(result.bricks.at(2).numberOfNeurons, 5);
    TEST_EQUAL(result.bricks.at(2).name, "test_output");
    TEST_EQUAL(result.bricks.at(2).type, OUTPUT_BRICK_TYPE);
}

}
}
