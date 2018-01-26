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

    virtual void setup()
    {
        srand(time(0));
    }

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

//------------------------------------------------------------------------------
//                                   UNIT TESTS
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(unit, LengthFixture)
{
    static const std::size_t iterations = 100;

    //------------------------------SHORT STRINGS-------------------------------

    // generate short strings
    std::vector<const char*> short_strs;
    short_strs.reserve(iterations);
    for(std::size_t i = 0; i < iterations; ++i)
    {
        short_strs.push_back(fixture->generate_string(1 + (rand() % 15)));
    }

    ARC_TEST_MESSAGE("Testing short strings with FFS naive");
    for(const char* s : short_strs)
    {
        ARC_CHECK_EQUAL(ffs_length__naive(s), strlen(s));
    }

    ARC_TEST_MESSAGE("Testing short strings with FFS word");
    for(const char* s : short_strs)
    {
        ARC_CHECK_EQUAL(ffs_length__word(s), strlen(s));
    }

    // TODO: ffs simd

    // clean up the strings
    for(const char* s : short_strs)
    {
        delete[] s;
    }

    //-------------------------------LONG STRINGS-------------------------------

    // generate long strings
    std::vector<const char*> long_strs;
    long_strs.reserve(iterations);
    for(std::size_t i = 0; i < iterations; ++i)
    {
        long_strs.push_back(fixture->generate_string(1024 + (rand() % 16384)));
    }

    ARC_TEST_MESSAGE("Testing long strings with FFS naive");
    for(const char* s : long_strs)
    {
        ARC_CHECK_EQUAL(ffs_length__naive(s), strlen(s));
    }

    ARC_TEST_MESSAGE("Testing long strings with FFS word");
    for(const char* s : long_strs)
    {
        ARC_CHECK_EQUAL(ffs_length__word(s), strlen(s));
    }

    // TODO: ffs simd

    // clean up the strings
    for(const char* s : long_strs)
    {
        delete[] s;
    }
}

//------------------------------------------------------------------------------
//                               PERFORMANCE TESTS
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE(performance, LengthFixture)
{
    static const std::size_t iterations = 20;
    static const std::size_t sub_iterations = 10000;


    arc::uint64 naive_time = 0;
    arc::uint64 std_time   = 0;
    arc::uint64 word_time  = 0;
    arc::uint64 simd_time  = 0;

    for(std::size_t i = 0; i < iterations; ++i)
    {
        // generate the strings
        std::vector<const char*> strs;
        strs.reserve(sub_iterations);
        for(std::size_t j = 0; j < sub_iterations; ++j)
        {
            strs.push_back(fixture->generate_string(1024 + (rand() % 16384)));
        }

        //--------------------------------NAIVE---------------------------------
        {
            std::vector<FFS_size_t> results(sub_iterations, 0);

            arc::uint64 time_start =
                arc::clock::get_current_time(arc::clock::METRIC_NANOSECONDS);
            for(std::size_t i = 0; i < sub_iterations; ++i)
            {
                results[0] = ffs_length__naive(strs[i]);
            }
            arc::uint64 time_end =
                arc::clock::get_current_time(arc::clock::METRIC_NANOSECONDS);
            arc::uint64 duration = time_end - time_start;
            naive_time += duration;
        }

        //--------------------------------GLIBC---------------------------------
        {
            std::vector<std::size_t> results(sub_iterations, 0);

            arc::uint64 time_start =
                arc::clock::get_current_time(arc::clock::METRIC_NANOSECONDS);
            for(std::size_t i = 0; i < sub_iterations; ++i)
            {
                results[0] = strlen(strs[i]);
            }
            arc::uint64 time_end =
                arc::clock::get_current_time(arc::clock::METRIC_NANOSECONDS);
            arc::uint64 duration = time_end - time_start;
            std_time += duration;
        }

        //-----------------------------SINGLE WORDS-----------------------------
        {
            std::vector<FFS_size_t> results(sub_iterations, 0);

            arc::uint64 time_start =
                arc::clock::get_current_time(arc::clock::METRIC_NANOSECONDS);
            for(std::size_t i = 0; i < sub_iterations; ++i)
            {
                results[0] = ffs_length__word(strs[i]);
            }
            arc::uint64 time_end =
                arc::clock::get_current_time(arc::clock::METRIC_NANOSECONDS);
            arc::uint64 duration = time_end - time_start;
            word_time += duration;
        }

        //------------------------------SIMD WORDS------------------------------
        {
            std::vector<FFS_size_t> results(sub_iterations, 0);

            arc::uint64 time_start =
                arc::clock::get_current_time(arc::clock::METRIC_NANOSECONDS);
            for(std::size_t i = 0; i < sub_iterations; ++i)
            {
                // results[0] = ffs_length__simd(strs[i]);
                ffs_length__simd(strs[i]);
            }
            arc::uint64 time_end =
                arc::clock::get_current_time(arc::clock::METRIC_NANOSECONDS);
            arc::uint64 duration = time_end - time_start;
            simd_time += duration;
        }

        // clean up the strings
        for(const char* s : strs)
        {
            delete[] s;
        }
    }

    std::cout << "naive time:    " << naive_time << std::endl;
    std::cout << "std time:      " << std_time << std::endl;
    std::cout << "FFS word time: " << word_time << std::endl;
    std::cout << "FFS simd time: " << simd_time << std::endl;


}

} // namespace anonymous
