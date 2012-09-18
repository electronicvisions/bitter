#pragma once

// Copyright (c) 2012, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the GPLv2 or newer

#include <type_traits>

namespace bit {

using std::size_t;

// size
template<typename T, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
size_t size(T) noexcept
{
	return sizeof(T) * 8;
}


// flip
template<typename T, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
T flip(T t, size_t pos) noexcept
{
	return t ^ (1<<pos);
}

template<typename T, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
T flip(T t) noexcept
{
	return ~t;
}



// set
template<typename T, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
inline void _set(T& t, size_t pos) noexcept
{
	t |= (1<<pos);
}

template<typename T, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
T set(T t, size_t pos) noexcept
{
	_set(t, pos);
	return t;
}

template<typename T, typename ... Pos, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
T set(T t, size_t pos0, size_t pos1, Pos ... pos) noexcept
{
	_set(t, pos0);
	return set(t, pos1, pos...);
}

template<typename T, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
T set(T t, size_t pos, bool value) noexcept
{
	return (t & ~(1<<pos)) | (-value & (1<<pos));
}



// reset
template<typename T, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
inline void _reset(T& t, size_t pos) noexcept
{
	t &= flip(t, pos);
}

template<typename T, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
T reset(T t, size_t pos) noexcept
{
	_reset(t, pos);
	return t;
}

template<typename T, typename ... Pos, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
T reset(T t, size_t pos0, Pos ... pos) noexcept
{
	_reset(t, pos0);
	return reset(t, pos...);
}



// test
template<typename T, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
bool test(T t, size_t pos) noexcept
{
	return t & (1<<pos);
}


// mask
template<typename T, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
T mask(T t, T mask) noexcept
{
	return t & mask;
}


// crop
template<typename T, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
T crop(T t, size_t begin, size_t end) noexcept
{
	T m = (1<<(end+1)) - (1<<begin);
	return mask(t, m) >> begin;
}


// count
template<typename T, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
size_t count(T t) noexcept
{
	// Brian Kernighan's way
	size_t c {0};
	for (; t; c++)
		t &= t - 1;
	return c;
}


// all
template<typename T, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
bool all(T t) noexcept
{
	return !static_cast<T>(~t);
}


// any
template<typename T, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
bool any(T t) noexcept
{
	return t != 0x0;
}


// none
template<typename T, typename =
	typename std::enable_if<std::is_integral<T>::value>::type>
bool none(T t) noexcept
{
	return !t;
}

} // namespace bit
