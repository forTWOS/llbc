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

#ifndef __LLBC_COMM_SAMPLER_FACADE_H__
#define __LLBC_COMM_SAMPLER_FACADE_H__

#include "llbc/common/Common.h"
#include "llbc/core/Core.h"
#include "llbc/objbase/ObjBase.h"

#if LLBC_CFG_COMM_ENABLE_SAMPLER_SUPPORT

#include "llbc/comm/IFacade.h"

__LLBC_NS_BEGIN

class LLBC_EXPORT LLBC_SamplerFacade : public LLBC_IFacade
{
    typedef std::map<sint32, LLBC_String> _SessionId2SessionInfo;
    typedef std::map<sint32, size_t> _Opcode2Flow;

public:
    LLBC_SamplerFacade();
    virtual ~LLBC_SamplerFacade();

public:
    //Sample session create and Destroy info 
    virtual void OnSessionCreateSampling(LLBC_SamplerBaseInfo *samplerInfo);
    virtual void OnSessionDestroySampling(LLBC_SamplerBaseInfo *samplerInfo);

    //Sample packet send and recv info
    virtual void OnPacketRecvSampling(LLBC_SamplerBaseInfo *samplerInfo);
    virtual void OnPacketSendSampling(LLBC_SamplerBaseInfo *samplerInfo);

    //sample network flow
    virtual void OnNetWorkFlowSampling(bool isSend, size_t len);

private:
    _SessionId2SessionInfo *_sessionId2Info;

    _Opcode2Flow *_recvOpcodeFlow;
    _Opcode2Flow *_sendOpcodeFlow;

    size_t _recvFlow;
    size_t _sendFlow;
};

__LLBC_NS_END

#endif // !__LLBC_COMM_SAMPLER_FACADE_H__
#endif // LLBC_CFG_COMM_ENABLE_SAMPLER_SUPPORT