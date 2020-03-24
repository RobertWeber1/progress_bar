#include "catch.hpp"
#include <progress_bar/parameter.h>


using namespace progress_bar;


namespace pTest
{

template<class ... Options>
bool check()
{
	return
		contains<ShowPercentage, Options...>::value and
		contains<ShowElapsedTime, Options...>::value and
		not contains<ShowRemainingTime, Options...>::value;
}

} //namespace pTest

TEST_CASE("check argument list for type")
{

	REQUIRE(
		pTest::check<
			ShowPercentage,
			ShowElapsedTime,
			Start<'['>>);

	REQUIRE_FALSE(
		pTest::check<
			ShowRemainingTime,
			ShowElapsedTime,
			Start<'['>>());
}

TEST_CASE("get or default")
{
	using tup =
		std::tuple<
			Start<'['>,
			End<']'>,
			Fill<'='>,
			Lead<'>'>,
			// Remainder<' '>,
			Options<ShowRemainingTime, ShowElapsedTime>>;

	// static_assert(
	// 	std::is_same<
	// 		get_or<Remainder, '_', tup>::type,
	// 		Literal<strut RemainderTag, char, '_'>>::value, "");
}

TEST_CASE("make progess bar")
{
	// using bar =
	// 	ProgressBar<
	// 		Start<'['>,
	// 		End<']'>,
	// 		Fill<'='>,
	// 		Lead<'>'>,
	// 		Remainder<' '>,
	// 		Options<ShowRemainingTime, ShowElapsedTime>>;

	// REQUIRE(bar::start() == '[');
}