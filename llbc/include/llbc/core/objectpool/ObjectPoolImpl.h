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

#ifdef __LLBC_CORE_OBJECTPOOL_OBJECTPOOL_H__

__LLBC_NS_BEGIN

template<typename T, typename LockType>
inline LLBC_ObjectPool<T, LockType>::LLBC_ObjectPool(sint32 reserveSize /*= LLBC_CFG_OBJECTPOOL_RESERVE_SIZE*/)
: _reserveSize(reserveSize)
{
	_objPool.reserve(_reserveSize);
}

template<typename T, typename LockType>
inline LLBC_ObjectPool<T, LockType>::~LLBC_ObjectPool()
{
	for (_Iterator iter = _objPool.begin();
		iter != _objPool.end();
		++iter)
	{
		LLBC_XDelete(*iter);
	}
	_objPool.clear();
}

template<typename T, typename LockType>
inline T *LLBC_ObjectPool<T, LockType>::Pop()
{
	LLBC_LockGuard guard(_lock);
	T *newobj = NULL;
	if (_objPool.empty())
		newobj = new T();
	else
		newobj = _PopFromCache();

	return newobj;
}

template<typename T, typename LockType>
inline void LLBC_ObjectPool<T, LockType>::Push(T *&o)
{
	if (UNLIKELY(!o))
		return;

	LLBC_LockGuard guard(_lock);
	if (UNLIKELY(_objPool.size() >= _reserveSize))
	{
		_reserveSize *= 2;
		_objPool.reserve(_reserveSize);
	}
	_objPool.push_back(o);
	o = NULL;
}

template<typename T, typename LockType>
inline T *LLBC_ObjectPool<T, LockType>::_PopFromCache()
{
	T *obj = _objPool.back();
	_objPool.pop_back();
	_ReInitialize(obj);
	return obj;
}

template<typename T, typename LockType>
inline void LLBC_ObjectPool<T, LockType>::_ReInitialize(T *o)
{
	//call object's ReInitialize func
	//o->ReInitialize();			//TODO
}

__LLBC_NS_END

#endif // __LLBC_CORE_OBJECTPOOL_OBJECTPOOL_H__
