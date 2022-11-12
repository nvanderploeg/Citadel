
#ifndef __TYPES_H__
#define __TYPES_H__

namespace citadel
{
	// BASIC TYPES
	// base types are borrowed from the Irrlicht Engine (irrTypes.h)
	// Copyright (C) 2002-2012 Nikolaus Gebhardt
#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	typedef __int8 s8;
	typedef unsigned __int8 u8;
	typedef __int16 s16;
	typedef unsigned __int16 u16;
	typedef __int32 s32;
	typedef unsigned __int32 u32;
#else
	typedef signed char s8;			//           -128 ..           127
	typedef unsigned char u8;		//              0 ..           256 (0xff)
	typedef signed short s16;		//        -32,768 ..        32,767
	typedef unsigned short u16;		//              0 ..        65,535 (0xffff)
	typedef signed int s32;			// -2,147,483,648 .. 2,147,483,647
	typedef unsigned int u32;		//			    0 .. 4,294,967,295 (0xffffffff)
#endif

	typedef unsigned char byte;

#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	typedef __int64 s64;
	typedef unsigned __int64 u64;
#elif __GNUC__
#	if __WORDSIZE == 64
	typedef long int s64;
	typedef unsigned long int u64;
#	else
	__extension__ typedef long long s64;
	__extension__ typedef unsigned long long u64;
#	endif
#else
	typedef long long s64;			// -9,223,372,036,854,775,808 ..  9,223,372,036,854,775,807
	typedef unsigned long long u64; //					        0 .. 18,446,744,073,709,551,615 (0xffffffffffffffff)
#endif

	typedef float f32;
	typedef double f64;

//    template<typename ... Args>
//    std::string string_format( const std::string& format, Args ... args )
//    {
//        std::size_t size = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
//        std::unique_ptr<char[]> buf( new char[ size ] );
//        std::snprintf( buf.get(), size, format.c_str(), args ... );
//        return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
//    }

} // namespace citadel

#endif // __TYPES_H__
