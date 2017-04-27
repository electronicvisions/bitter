// Copyright 2013, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the LGPLv3 or newer.

#pragma once

namespace bit {
namespace detail {

// set value to N for TYPE<N> or 1 for bool
template<typename T>
struct lengthOfBoolOrBitset;

template<size_t N, template <size_t> class T>
struct lengthOfBoolOrBitset<T<N>>
{
	enum : size_t { value = N };
};

template<>
struct lengthOfBoolOrBitset<bool>
{
	enum : size_t { value = 1 };
};

// calculate sum of all bools and Ns in a pack of TYPE<N>
template<typename ... Ts>
struct sum;

template<typename T, typename ... Ts>
struct sum<T, Ts...>
{
	enum : size_t { value = lengthOfBoolOrBitset<T>::value + sum<Ts...>::value };
};

template<>
struct sum<>
{
	enum : size_t { value = 0 };
};


template<size_t N, size_t M>
struct min
{
	enum : size_t { value = N<M ? N : M };
};

} // namespace detail
} // namespace bit
