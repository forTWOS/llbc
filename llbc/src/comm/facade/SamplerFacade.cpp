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


#include "llbc/common/Export.h"
#include "llbc/common/BeforeIncl.h"

#include "llbc/comm/facade/SamplerFacade.h"

#if LLBC_CFG_COMM_ENABLE_SAMPLER_SUPPORT

namespace
{
    typedef LLBC_NS LLBC_SamplerInfo_SessionCreateDestroy SessionCreateSamplerInfo;
    typedef LLBC_NS LLBC_SamplerInfo_SessionCreateDestroy SessionDestroySamplerInfo;
    typedef LLBC_NS LLBC_SamplerInfo_PacketSendRecv PacketRecvSamplerInfo;
    typedef LLBC_NS LLBC_SamplerInfo_PacketSendRecv PacketSendSamplerInfo;
}

__LLBC_NS_BEGIN

LLBC_SamplerFacade::LLBC_SamplerFacade()
: _sessionId2Info(LLBC_New(_SessionId2SessionInfo))
, _recvOpcodeFlow(LLBC_New(_Opcode2Flow))
, _sendOpcodeFlow(LLBC_New(_Opcode2Flow))
, _recvFlow(0)
, _sendFlow(0)
{
}

LLBC_SamplerFacade::~LLBC_SamplerFacade()
{
    _sessionId2Info->clear();
    _recvOpcodeFlow->clear();
    _sendOpcodeFlow->clear();
    LLBC_XDelete(_sessionId2Info);
    LLBC_XDelete(_recvOpcodeFlow);
    LLBC_XDelete(_sendOpcodeFlow);
}

void LLBC_SamplerFacade::OnSessionCreateSampling(LLBC_SamplerBaseInfo *samplerInfo)
{
    typedef _SessionId2SessionInfo::iterator _Iter;
    SessionCreateSamplerInfo *info = static_cast<SessionCreateSamplerInfo *>(samplerInfo);
    _Iter iter = _sessionId2Info->find(info->sessionId);
    if (iter != _sessionId2Info->end())
        LLBC_PrintLine("OnSessionCreateSampling error: repeat sessionInfo %s", iter->second.c_str());

    _sessionId2Info->insert(std::make_pair(info->sessionId, info->ToString()));
}

void LLBC_SamplerFacade::OnSessionDestroySampling(LLBC_SamplerBaseInfo *samplerInfo)
{
    typedef _SessionId2SessionInfo::iterator _Iter;
    SessionDestroySamplerInfo *info = static_cast<SessionDestroySamplerInfo *>(samplerInfo);
    _Iter iter = _sessionId2Info->find(info->sessionId);
    if (iter == _sessionId2Info->end())
    {
        LLBC_PrintLine("OnSessionDestroySampling fail: session %d not find, sessionInfo is %s", info->sessionId, info->ToString().c_str());
        return;
    }

    LLBC_PrintLine("OnSessionDestroySampling success: destroy sessionInfo is %s", info->ToString().c_str());
    _sessionId2Info->erase(iter);
}

void LLBC_SamplerFacade::OnPacketRecvSampling(LLBC_SamplerBaseInfo *samplerInfo)
{
    PacketRecvSamplerInfo *info = static_cast<PacketRecvSamplerInfo *>(samplerInfo);
    (*_recvOpcodeFlow)[info->opcode] += info->len;
    LLBC_PrintLine("OnPacketRecvSampling: opcode %d flow %u", info->opcode, (*_recvOpcodeFlow)[info->opcode]);
}

void LLBC_SamplerFacade::OnPacketSendSampling(LLBC_SamplerBaseInfo *samplerInfo)
{
    PacketSendSamplerInfo *info = static_cast<PacketSendSamplerInfo *>(samplerInfo);
    (*_sendOpcodeFlow)[info->opcode] += info->len;
    LLBC_PrintLine("OnPacketSendSampling: opcode %d flow %u", info->opcode, (*_sendOpcodeFlow)[info->opcode]);
}

void LLBC_SamplerFacade::OnNetWorkFlowSampling(bool isSend, size_t len)
{
    if (isSend)
        _sendFlow += len;
    else
        _recvFlow += len;

    LLBC_PrintLine("OnNetWorkFlowSampling: _sendFlow %u _recvFlow %u", _sendFlow, _recvFlow);
}

__LLBC_NS_END

#endif // LLBC_CFG_COMM_ENABLE_SAMPLER_SUPPORT
#include "llbc/common/AfterIncl.h"
