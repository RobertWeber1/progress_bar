#include "catch.hpp"
#include <progress_bar/options.h>


using namespace progress_bar;


namespace
{

using options =
		Options<
			Start<'['>,
			End<']'>,
			Fill<'='>,
			Lead<'>'>,
			ShowRemainingTime,
			ShowElapsedTime>;


} //namespace


TEST_CASE("get or default")
{
	REQUIRE(options::contains<StartChar>());
	REQUIRE_FALSE(options::contains<RemainderChar>());
	REQUIRE(options::get_value<StartChar>() == '[');
	REQUIRE(options::get_value_or<LeadChar, Lead<'+'>>() == '>');
	REQUIRE(options::get_value_or<RemainderChar, Remainder<'+'>>() == '+');

}
