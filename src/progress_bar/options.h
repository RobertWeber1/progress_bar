#pragma once
#include <type_traits>


namespace progress_bar
{



template<class Tag, class Type, Type Value>
struct OptionLiteral
{
	using type = Type;

	static constexpr Type value()
	{
		return Value;
	}
};


template<class Lhs, class Rhs>
struct IsOption
{
	enum { value = false };
};

template<class Type>
struct IsOption<Type, Type>
{
	enum { value = true };
};

template<class Tag, class Type, Type Value>
struct IsOption<Tag, OptionLiteral<Tag, Type, Value>>
{
	enum { value = true };
};



template<class ... Opts>
struct Options
{
private:
	struct OptHelper : Opts ... {};

public:
	template<class Arg>
	static constexpr bool contains()
	{
		return (false ... | IsOption<Arg, Opts>::value);
	}

	template<class Tag, class Default>
	static constexpr auto get_value_or()
	{
		if constexpr(not contains<Tag>())
		{
			return Default::value();
		}
		else
		{
			return get_value_<Tag>(OptHelper{});
		}
	}

	template<class Tag>
	static constexpr auto get_value()
	{
		return get_value_<Tag>(OptHelper{});
	}

private:
	template<class Tag, class Type, Type Value>
	static constexpr Type get_value_(OptionLiteral<Tag, Type, Value> const&)
	{
		return Value;
	}
};


struct ShowPercentageEnabled {};
struct ShowElapsedTimeEnabled {};
struct ShowRemainingTimeEnabled {};
struct StartChar {};
struct EndChar {};
struct FillChar {};
struct LeadChar {};
struct RemainderChar {};

using ShowPercentage = OptionLiteral<ShowPercentageEnabled, bool, true>;

using ShowElapsedTime = OptionLiteral<ShowElapsedTimeEnabled, bool, true>;

using ShowRemainingTime = OptionLiteral<ShowRemainingTimeEnabled, bool, true>;

template<char C>
using Start = OptionLiteral<StartChar, char, C>;

template<char C>
using End = OptionLiteral<EndChar, char, C>;

template<char C>
using Fill = OptionLiteral<FillChar, char, C>;

template<char C>
using Lead = OptionLiteral<LeadChar, char, C>;

template<char C>
using Remainder = OptionLiteral<RemainderChar, char, C>;


} //namespace progress_bar
