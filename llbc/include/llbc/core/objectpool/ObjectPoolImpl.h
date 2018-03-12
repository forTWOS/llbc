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

#include "llbc/core/thread/SpinLock.h"

__LLBC_NS_BEGIN

template<typename T, bool ThreadSafe>
inline LLBC_ObjectPool<T, ThreadSafe>::LLBC_ObjectPool(sint32 reserveSize)
: _lock(NULL) 

, _reserveSize(reserveSize)
{
    if (UNLIKELY(ThreadSafe))
        _lock = new LLBC_SpinLock();

    _objPool.reserve(_reserveSize);
}

template<typename T, bool ThreadSafe>
inline LLBC_ObjectPool<T, ThreadSafe>::~LLBC_ObjectPool()
{
    typedef typename std::vector<T *>::iterator _Iterator;
    for (_Iterator iter = _objPool.begin();
         iter != _objPool.end();
         ++iter)
        LLBC_XDelete(*iter);

    _objPool.clear();
    LLBC_XDelete(_lock);
}

template<typename T, bool ThreadSafe>
inline T *LLBC_ObjectPool<T, ThreadSafe>::Pop()
{
    if (UNLIKELY(ThreadSafe))
        _lock->Lock();

    T *newobj = NULL;
    if (_objPool.empty())
        newobj = new T();
    else
        newobj = _PopFromCache();

    if (UNLIKELY(ThreadSafe))
        _lock->Unlock();

    return newobj;
}

template<typename T, bool ThreadSafe>
inline void LLBC_ObjectPool<T, ThreadSafe>::Push(T *&o)
{
    if (UNLIKELY(!o))
        return;

    if (UNLIKELY(ThreadSafe))
        _lock->Lock();

    if (UNLIKELY(_objPool.size() >= _reserveSize))
    {
        _reserveSize *= 2;
        _objPool.reserve(_reserveSize);
    }
    _objPool.push_back(o);
    o = NULL;

    if (UNLIKELY(ThreadSafe))
        _lock->Unlock();
}

template<typename T, bool ThreadSafe>
inline T *LLBC_ObjectPool<T, ThreadSafe>::_PopFromCache()
{
    T *obj = _objPool.back();
    _objPool.pop_back();
    _ReInitialize(obj);
    return obj;
}

template<typename T, bool ThreadSafe>
inline void LLBC_ObjectPool<T, ThreadSafe>::_ReInitialize(T *o)
{
    //call object's ReInitialize func
    o->ReInitialize();
}

__LLBC_NS_END

#endif // __LLBC_CORE_OBJECTPOOL_OBJECTPOOL_H__
