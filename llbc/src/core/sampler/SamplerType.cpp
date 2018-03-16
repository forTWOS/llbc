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

#include "llbc/core/sampler/SamplerType.h"

namespace
{
    typedef LLBC_NS LLBC_SamplerBaseInfo Base;
}

__LLBC_NS_BEGIN

bool LLBC_SamplerType::IsValid(int type)
{
    return (type >= LLBC_SamplerType::Begin && 
        type < LLBC_SamplerType::End) ? true : false;
}

LLBC_SamplerBaseInfo::LLBC_SamplerBaseInfo(int type)
: type(type)
, tm(LLBC_Time::Now())
{
}

LLBC_SamplerBaseInfo::~LLBC_SamplerBaseInfo()
{
}

LLBC_SamplerInfo_SessionCreateDestroy::LLBC_SamplerInfo_SessionCreateDestroy(bool create)
: Base(LLBC_SamplerInfoType::SessionSamplerInfo)
, isCreate(create)
{
}

LLBC_SamplerInfo_SessionCreateDestroy::~LLBC_SamplerInfo_SessionCreateDestroy()
{
}

LLBC_String LLBC_SamplerInfo_SessionCreateDestroy::ToString() const
{
    LLBC_String retStr;
    retStr.append_format("%s, ", tm.Format().c_str())
          .append_format("samplerType:%d, ", type)
          .append_format("serviceId:%d, ", svcId)
          .append_format("serviceName:%s, ", svcName.c_str())
          .append_format("%s, ", isCreate ? "sessionCreate" : "sessionDestroy")
          .append_format("isListen:%s, ", isListen ? "true" : "false")
          .append_format("sessionId:%d, ", sessionId)
          .append_format("acceptSessionId:%d, ", acceptSessionId)
          .append_format("localAddr:%s, ", localAddr.c_str())
          .append_format("localAddr:%s, ", peerAddr.c_str())
          .append_format("handle:%d", sockHandle);

    return retStr;
}

LLBC_SamplerInfo_PacketSendRecv::LLBC_SamplerInfo_PacketSendRecv(bool send)
: Base(LLBC_SamplerInfoType::PacketSamplerInfo)
, isSend(send)
{
}

LLBC_SamplerInfo_PacketSendRecv::~LLBC_SamplerInfo_PacketSendRecv()
{
}

LLBC_String LLBC_SamplerInfo_PacketSendRecv::ToString() const
{
    LLBC_String retStr;
    retStr.append_format("%s, ", tm.Format().c_str())
          .append_format("samplerType:%d, ", type)
          .append_format("%s, ", isSend ? "sendPacket" : "recvPacket")
          .append_format("recverSvcId:%d, ", recverSvcId)
          .append_format("senderSvcId:%d, ", senderSvcId)
          .append_format("sessionId:%d, ", sessionId)
          .append_format("opcode:%d,  ", opcode)
          .append_format("packeLen:%u", len);

    return retStr;
}

__LLBC_NS_END

#include "llbc/common/AfterIncl.h"
