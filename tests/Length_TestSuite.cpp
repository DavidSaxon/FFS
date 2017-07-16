#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(Length)

#include <arcanecore/base/clock/ClockOperations.hpp>

#include <FFS/FFS.h>


namespace
{

//------------------------------------------------------------------------------
//                                    FIXTURE
//------------------------------------------------------------------------------

class LengthFixture : public arc::test::Fixture
{
public:

    //-----------------------------PUBLIC FUNCTIONS-----------------------------

    const char* generate_string(std::size_t length)
    {
        char* ret = new char[length + 1];

        srand(time(0));
        for(std::size_t i = 0; i < length; ++i)
        {
            ret[i] = (rand() % 127) + 1;
        }
        ret[length] = '\0';

        return ret;
    }

};

ARC_TEST_UNIT_FIXTURE(unit, LengthFixture)
{
    std::string s = "0123456789";
    ARC_CHECK_EQUAL(ffs_length_naive(s.c_str()), 10);
    ARC_CHECK_EQUAL(ffs_length(s.c_str()), 10);
}

ARC_TEST_UNIT_FIXTURE(performance, LengthFixture)
{
    static const std::size_t iterations = 10000;

    std::vector<const char*> strs;
    strs.reserve(iterations);
    for(std::size_t i = 0; i < iterations; ++i)
    {
        strs.push_back(fixture->generate_string(1024 + (rand() % 1024)));
    }

    // generate the strings
    const char* s2048 = fixture->generate_string(2048);

    ARC_CHECK_EQUAL(ffs_length(s2048), 2048);

    ARC_TEST_MESSAGE("Timing FFS length with 2048 characters");
    {
        std::vector<FFS_size_t> results(iterations, 0);

        arc::uint64 time_start =
            arc::clock::get_current_time(arc::clock::METRIC_NANOSECONDS);
        for(std::size_t i = 0; i < iterations; ++i)
        {
            results[0] = ffs_length(strs[i]);
        }
        arc::uint64 time_end =
            arc::clock::get_current_time(arc::clock::METRIC_NANOSECONDS);
        arc::uint64 duration = time_end - time_start;
        std::cout << "FFS time:   " << duration << std::endl;
    }

    ARC_TEST_MESSAGE("Timing naive length with 2048 characters");
    {
        std::vector<FFS_size_t> results(iterations, 0);

        arc::uint64 time_start =
            arc::clock::get_current_time(arc::clock::METRIC_NANOSECONDS);
        for(std::size_t i = 0; i < iterations; ++i)
        {
            results[0] = ffs_length_naive(strs[i]);
        }
        arc::uint64 time_end =
            arc::clock::get_current_time(arc::clock::METRIC_NANOSECONDS);
        arc::uint64 duration = time_end - time_start;
        std::cout << "naive time: " << duration << std::endl;
    }

    ARC_TEST_MESSAGE("Timing strlen with 2048 characters");
    {
        std::vector<std::size_t> results(iterations, 0);

        arc::uint64 time_start =
            arc::clock::get_current_time(arc::clock::METRIC_NANOSECONDS);
        for(std::size_t i = 0; i < iterations; ++i)
        {
            results[0] = strlen(strs[i]);
        }
        arc::uint64 time_end =
            arc::clock::get_current_time(arc::clock::METRIC_NANOSECONDS);
        arc::uint64 duration = time_end - time_start;
        std::cout << "std time:   " << duration << std::endl;
    }

    // clean up the strings
    delete[] s2048;
}

} // namespace anonymous
