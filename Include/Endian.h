#ifndef ENDIAN_H
#define ENDIAN_H

template<typename T>
constexpr T convert_between_host_and_little_endian(T value)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	return value;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	if constexpr (sizeof(T) == 8)
		return __builtin_bswap64(value);
	if constexpr (sizeof(T) == 4)
		return __builtin_bswap32(value);
	if constexpr (sizeof(T) == 2)
		return __builtin_bswap16(value);
	if constexpr (sizeof(T) == 1)
		return value;
#endif
}

template<typename T>
constexpr T convert_between_host_and_big_endian(T value)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	if constexpr (sizeof(T) == 8)
		return __builtin_bswap64(value);
	if constexpr (sizeof(T) == 4)
		return __builtin_bswap32(value);
	if constexpr (sizeof(T) == 2)
		return __builtin_bswap16(value);
	if constexpr (sizeof(T) == 1)
		return value;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return value;
#endif
}

template<typename T>
class BigEndian
{
private:
	T m_value{};
public:
	constexpr BigEndian() = default;

	constexpr BigEndian(T value)
		: m_value(convert_between_host_and_big_endian(value))
	{
	}
	constexpr operator T() const
	{
		return convert_between_host_and_little_endian(m_value);
	}
};

template<typename T>
class LittleEndian
{
private:
	T m_value{};
public:
	constexpr LittleEndian() = default;

	constexpr LittleEndian(T value)
		: m_value(convert_between_host_and_little_endian(value))
	{
	}
	constexpr operator T() const
	{
		return convert_between_host_and_little_endian(m_value);
	}
};

#endif //ENDIAN_H
