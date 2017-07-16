#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(FFS.Replace)

#include <arcanecore/base/clock/ClockOperations.hpp>

#include <FFS/Replace.h>


namespace
{

ARC_TEST_UNIT(proto)
{
    std::string s = "h_e_l_l_o____w_o_r_l_d";

    ffs_replace_single_naive(&s[0], '_', '*', s.length());

    std::cout << s << std::endl;

    ffs_replace_single(&s[0], '*', '^', s.length());

    std::cout << s << std::endl;
}

} // namespace anonymous
