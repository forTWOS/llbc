// The MIT License (MIT)

// Copyright (c) 2013 lailongwei<lailongwei@126.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of 
// this software and associated documentation files (the "Software"), to deal in 
// the Software without restriction, including without limitation the rights to 
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of 
// the Software, and to permit persons to whom the Software is furnished to do so, 
// subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all 
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS 
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifdef __LLBC_COMM_PACKET_H__

__LLBC_NS_BEGIN

#define __LLBC_COMM_PACKET_EXTDATA_GET_FUNC(Type, Num)\
template <>											 \
inline Type LLBC_Packet::GetExtData##Num() const     \
{													 \
	return static_cast<Type>(_extData##Num);		 \
}													 \

#define __LLBC_COMM_PACKET_EXTDATA_GET_BOOL_FUNC(Num)\
template <>											 \
inline bool LLBC_Packet::GetExtData##Num() const     \
{													 \
	return _extData##Num != 0;						 \
}													 \

#define __LLBC_COMM_PACKET_EXTDATA_GET_FLOAT_FUNC(Num)\
template <>											 \
inline float LLBC_Packet::GetExtData##Num() const    \
{													 \
	return static_cast<float>(*reinterpret_cast<const double *>(&_extData##Num));\
}													 \

#define __LLBC_COMM_PACKET_EXTDATA_GET_DOUBLE_FUNC(Num)\
template <>											 \
inline double LLBC_Packet::GetExtData##Num() const    \
{													 \
	return static_cast<double>(*reinterpret_cast<const double *>(&_extData##Num));	 \
}													 \


#define __LLBC_COMM_PACKET_EXTDATA_SET_FUNC(Type, Num)			\
template <>														\
inline void LLBC_Packet::SetExtData##Num(const Type &extData)	\
{																\
	_extData##Num = extData;				                    \
}																\

#define __LLBC_COMM_PACKET_EXTDATA_SET_BOOL_FUNC(Num)			\
template <>														\
inline void LLBC_Packet::SetExtData##Num(const bool &extData)	\
{																\
	_extData##Num = extData?1:0;			                    \
}																\

#define __LLBC_COMM_PACKET_EXTDATA_SET_FLOAT_FUNC(Num)			\
template <>														\
inline void LLBC_Packet::SetExtData##Num(const float &extData)	\
{																\
	*reinterpret_cast<double *>(&_extData##Num) = extData;		\
}																\

#define __LLBC_COMM_PACKET_EXTDATA_SET_DOUBLE_FUNC(Num)			\
template <>														\
inline void LLBC_Packet::SetExtData##Num(const double &extData)	\
{																\
	*reinterpret_cast<double *>(&_extData##Num) = extData;		\
}																\

#define __LLBC_COMM_PACKET_EXTDATA_TEMPLATE_FUNC(Num)	\
template<typename T>									\
inline T LLBC_Packet::GetExtData##Num() const			\
{														\
	return static_cast<T>(_extData##Num);				\
}														\
														\
template<typename T>									\
inline void LLBC_Packet::SetExtData##Num(const T &extData)\
{														\
	_extData##Num = static_cast<sint64>(extData);		\
}														\

//get func
__LLBC_COMM_PACKET_EXTDATA_GET_BOOL_FUNC(1);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(sint8, 1);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(sint16, 1);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(sint32, 1);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(sint64, 1);
__LLBC_COMM_PACKET_EXTDATA_GET_FLOAT_FUNC(1);
__LLBC_COMM_PACKET_EXTDATA_GET_DOUBLE_FUNC(1);

__LLBC_COMM_PACKET_EXTDATA_GET_BOOL_FUNC(2);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(sint8, 2);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(sint16, 2);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(sint32, 2);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(sint64, 2);
__LLBC_COMM_PACKET_EXTDATA_GET_FLOAT_FUNC(2);
__LLBC_COMM_PACKET_EXTDATA_GET_DOUBLE_FUNC(2);

__LLBC_COMM_PACKET_EXTDATA_GET_BOOL_FUNC(3);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(sint8, 3);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(sint16, 3);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(sint32, 3);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(sint64, 3);
__LLBC_COMM_PACKET_EXTDATA_GET_FLOAT_FUNC(3);
__LLBC_COMM_PACKET_EXTDATA_GET_DOUBLE_FUNC(3);

__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(uint8, 1);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(uint16, 1);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(uint32, 1);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(uint64, 1);

__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(uint8, 2);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(uint16, 2);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(uint32, 2);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(uint64, 2);

__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(uint8, 3);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(uint16, 3);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(uint32, 3);
__LLBC_COMM_PACKET_EXTDATA_GET_FUNC(uint64, 3);

//set func
__LLBC_COMM_PACKET_EXTDATA_SET_BOOL_FUNC(1);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(sint8, 1);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(sint16, 1);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(sint32, 1);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(sint64, 1);
__LLBC_COMM_PACKET_EXTDATA_SET_FLOAT_FUNC(1);
__LLBC_COMM_PACKET_EXTDATA_SET_DOUBLE_FUNC(1);

__LLBC_COMM_PACKET_EXTDATA_SET_BOOL_FUNC(2);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(sint8, 2);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(sint16, 2);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(sint32, 2);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(sint64, 2);
__LLBC_COMM_PACKET_EXTDATA_SET_FLOAT_FUNC(2);
__LLBC_COMM_PACKET_EXTDATA_SET_DOUBLE_FUNC(2);

__LLBC_COMM_PACKET_EXTDATA_SET_BOOL_FUNC(3);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(sint8, 3);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(sint16, 3);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(sint32, 3);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(sint64, 3);
__LLBC_COMM_PACKET_EXTDATA_SET_FLOAT_FUNC(3);
__LLBC_COMM_PACKET_EXTDATA_SET_DOUBLE_FUNC(3);

__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(uint8, 1);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(uint16, 1);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(uint32, 1);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(uint64, 1);

__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(uint8, 2);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(uint16, 2);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(uint32, 2);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(uint64, 2);

__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(uint8, 3);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(uint16, 3);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(uint32, 3);
__LLBC_COMM_PACKET_EXTDATA_SET_FUNC(uint64, 3);

__LLBC_COMM_PACKET_EXTDATA_TEMPLATE_FUNC(1);
__LLBC_COMM_PACKET_EXTDATA_TEMPLATE_FUNC(2);
__LLBC_COMM_PACKET_EXTDATA_TEMPLATE_FUNC(3);

__LLBC_NS_END

#endif // __LLBC_COMM_PACKET_H__
