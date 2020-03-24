#pragma once
#include <type_traits>
#include <tuple>

namespace progress_bar
{

struct ShowPercentage {};
struct ShowElapsedTime {};
struct ShowRemainingTime {};

template<class ... Opts>
struct Options
{
	template<class Arg>
	static constexpr bool contains()
	{
		return (false ... | std::is_same<Arg, Opts>::value);
	}
};

template<class Tag, class Type, Type Value>
struct Literal
{
	using type = Type;

	static Type value()
	{
		return Value;
	}
};

template<char C>
using Start = Literal<struct StartTag, char, C>;

template<char C>
using End = Literal<struct EndTag, char, C>;

template<char C>
using Fill = Literal<struct FillTag, char, C>;

template<char C>
using Lead = Literal<struct LeadTag, char, C>;

template<char C>
using Remainder = Literal<struct RemainderTag, char, C>;



template<class Arg, class ... Opts>
struct contains
{
	enum { value = (false ... | std::is_same<Arg, Opts>::value) };
};


template<class, class, class>
struct get_or;

// template<typename T, class Default>
// struct get_or<T, Default, std::tuple<>>
// {
// 	using type = Default;
// };

// template<class T, class Default, class... Ts>
// struct get_or<T, Default, std::tuple<T, Ts...>>
// {
// 	using type = T;
// };

// template<class T, class Default, class U, class... Ts>
// struct get_or<T, Default, std::tuple<U, Ts...>>
// : get_or<T, Default, std::tuple<Ts...>>
// {};


// template<class Tag, class Type, Type C, Type Default>
// struct get_or<Literal<Tag, Type, C>, Default, std::tuple<>>
// {
// 	using type = Literal<Tag, Type, Default>;
// };

// template<class Tag, class Type, Type C, Type Default, class... Ts>
// struct get_or<Literal<Tag, Type, C>, Default, std::tuple<Literal<Tag, Type, C>, Ts...>>
// {
// 	using type = Literal<Tag, Type, C>;
// };

// template<class Tag, class Type, Type C, Type Default, class U, class... Ts>
// struct get_or<Literal<Tag, Type, C>, Default, std::tuple<U, Ts...>>
// : get_or<Literal<Tag, Type, C>, Default, std::tuple<Ts...>>
// {};


// template<class Arg, class Default, class ... Options>
// constexpr decltype(auto) get_or() noexcept
// {
// 	if(contains<Arg, Options...>::value)
// 	{
// 		// get<Arg, Options>::value{};
// 	}

//     return default_value;
// }




//------------------------------------------------------------------------------

// template<class Tag, class Type, Type Value>
// constexpr Type getter(Literal<Tag, Type, Value> const& lit)
// {
//     return lit.value();
// }

// template<template<char C>class T, class ... Args>
// constexpr typename T<>::Type getter(std::tuple<Args...> const& t) noexcept
// {
//     return getter<T>(t);
// }


// template<class ... Args>
// struct ProgressBar
// {
// 	static char start()
// 	{
// 		return getter<Start>(std::tuple<Args...>{});
// 	}
// };


// namespace detail
// {

// template<
// 	int Id,
// 	class Name,
// 	ITEMTYPE ItemType,
// 	class DataType,
// 	template<class, class> class OnValidate,
// 	template<class, class> class OnNotify>
// constexpr DataType& get(Var<Id, Name, ItemType, DataType, OnValidate, OnNotify>& t)
// {
//     return t.value;
// }

// } //namespace detail





// template<char S, char E, char F, char L, char R>
// struct ProgressBarImpl<
// 	Start<S>,
// 	End<E>,
// 	Fill<F>,
// 	Lead<L>,
// 	Remainder<R>>
// {};


//------------------------------------------------------------------------------


// template<class ... Ordered, class ... Unordered>
// struct MatchArgs
// {

// }



// template<template<class ... Ts> class T, class ... Args>
// struct MatchArgs_l1
// {
// 	using type = bool;
// };

// template<class ... Ts, class ... Args>
// struct MatchArgs<ProgressBarImpl<Ts...>, Args...>
// {
// 	// using t = std::tuple<Ts...>;
// 	using type = int;
// };


// template<class ... Args>
// using ProgressBar = typename MatchArgs_l1<ProgressBarImpl, Args...>::type;






} //namespace progress_bar
