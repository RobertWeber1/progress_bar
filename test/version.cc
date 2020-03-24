#include "catch.hpp"
#include <progress_bar/version.h>
#include <string>

using namespace progress_bar;

TEST_CASE("check generation of verion header")
{
	REQUIRE(Version::project_name == std::string("progress_bar"));
}