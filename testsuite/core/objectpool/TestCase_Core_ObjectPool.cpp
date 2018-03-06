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

#include "core/objectpool/TestCase_Core_ObjectPool.h"



TestCase_Core_ObjectPool::TestCase_Core_ObjectPool()
{
}

TestCase_Core_ObjectPool::~TestCase_Core_ObjectPool()
{
}

int TestCase_Core_ObjectPool::Run(int argc, char *argv[])
{
    std::cout <<"core/objectpool test:" <<std::endl;

	LLBC_ObjectPool<LLBC_MessageBlock> *objpool = new LLBC_ObjectPool<LLBC_MessageBlock>(3);
	LLBC_MessageBlock *obj1 = objpool->Pop();
	LLBC_MessageBlock *obj2 = objpool->Pop();
	LLBC_MessageBlock *obj3 = objpool->Pop();
	LLBC_PrintLine("obj1: %p", obj1);
	LLBC_PrintLine("obj2: %p", obj2);
	LLBC_PrintLine("obj3: %p", obj3);
	objpool->Push(obj1);
	LLBC_MessageBlock *obj4 = objpool->Pop();
	LLBC_PrintLine("obj4: %p", obj4);
	LLBC_MessageBlock *obj5 = objpool->Pop();
	LLBC_PrintLine("obj5: %p", obj5);
	objpool->Push(obj1);
	objpool->Push(obj2);
	objpool->Push(obj3);
	objpool->Push(obj4);
	objpool->Push(obj5);
	
	ASSERT(obj4 == obj1);
   
	LLBC_XDelete(objpool);
    LLBC_PrintLine("Press any key to continue ...");
    getchar();

    return 0;
}

