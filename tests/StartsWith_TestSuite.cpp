#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(StartsWith)

#include <arcanecore/base/clock/ClockOperations.hpp>

#include <FFS/FFS.h>


namespace
{

//------------------------------------------------------------------------------
//                                    FIXTURE
//------------------------------------------------------------------------------

class StartsWithFixture : public arc::test::Fixture
{
public:

    //-----------------------------PUBLIC FUNCTIONS-----------------------------

    virtual void setup()
    {
        srand(time(0));
    }

    // const char* generate_string_and_substr(std::size_t length)
    // {
    //     char* ret = new char[length + 1];

    //     srand(time(0));
    //     for(std::size_t i = 0; i < length; ++i)
    //     {
    //         ret[i] = (rand() % 127) + 1;
    //     }
    //     ret[length] = '\0';

    //     return ret;
    // }
};

//------------------------------------------------------------------------------
//                                   UNIT TESTS
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(unit, LengthFixture)
{
    static const std::size_t iterations = 100;

    //------------------------------SHORT STRINGS-------------------------------

    // generate short strings
    // TODO:
}

} // namespace anonymous
