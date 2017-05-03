// Copyright 2013, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the LGPLv3 or newer.

#pragma once

#include <bitset>
#include <string>

#include <bitter/define.h>
#include <bitter/detail/detail.h>

#define BITTER_IF_INTEGRAL(T, RET) \
	typename std::enable_if<(std::is_integral<T>::value), RET>::type

namespace bit {

using std::size_t;
using std::bitset;

// type converter
template<typename T = size_t, size_t N>
T convert(bitset<N> const& t)
{
	static_assert(N <= sizeof(T)*BITTER_BITS_PER_BYTE, "unsupported conversion");
	return T(t.to_ullong());
}

template<typename T, size_t N = sizeof(T)*BITTER_BITS_PER_BYTE>
BITTER_IF_INTEGRAL(T, bitset<N>)
convert(T t) noexcept
{
	return bitset<N>(t);
}


template<size_t Len, size_t N>
typename std::enable_if<
	(N<=BITTER_BITS_PER_BYTE*sizeof(unsigned long long)),
	std::bitset<Len>>::type
resize(bitset<N> const& t)
{
	return std::bitset<Len>(t.to_ullong());
}

// copy lowest bits
template<size_t Len, size_t N>
typename std::enable_if<
	(N>BITTER_BITS_PER_BYTE*sizeof(uintmax_t)),
	std::bitset<Len>>::type
resize(bitset<N> const& t)
{
	bitset<Len> r;
	size_t c = detail::min<Len, N>::value;
	while (c--)
		r[c] = t[c];
	return r;
}

// copy bool value into the lowest bit (same as for bitset<1>)
template<size_t Len>
std::bitset<Len>
resize(bool const& t)
{
	bitset<Len> r;
	r[0] = t;
	return r;
}


// string converter
template<size_t N>
std::string str(bitset<N> const& t)
{
	return t.to_string();
}

template<size_t Len, size_t N>
std::string str(bitset<N> const& t)
{
	return bitset<Len>(t.to_ullong()).to_string();
}

template<typename T>
BITTER_IF_INTEGRAL(T, std::string)
str(T t)
{
	return convert(t).to_string();
}

template<size_t Len, typename T>
BITTER_IF_INTEGRAL(T, std::string)
str(T t)
{
	return convert<T, Len>(t).to_string();
}


// concatenation of bitsets
template<size_t N>
bitset<N> concat(bitset<N> const& t)
{
	return t;
}

inline bitset<1> concat(bool const& b)
{
	return bitset<1>(b);
}

template<typename T, typename ... Ts>
bitset<detail::sum<T, Ts...>::value>
concat(T const& t, Ts const&... ts)
{
	return (resize<detail::sum<T, Ts...>::value>(t) << detail::sum<Ts...>::value
		| resize<detail::sum<T, Ts...>::value>(concat(ts...)));
}

} // namespace bit

#undef BITTER_IF_INTEGRAL
