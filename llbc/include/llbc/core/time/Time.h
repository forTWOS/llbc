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

#ifndef __LLBC_CORE_TIME_TIME_H__
#define __LLBC_CORE_TIME_TIME_H__

#include "llbc/common/Common.h"

__LLBC_NS_BEGIN

class LLBC_Time;
class LLBC_TimeSpan;

__LLBC_NS_END

/**
 * Time class stream output operators previous declare.
 */
LLBC_EXTERN LLBC_EXPORT std::ostream & operator <<(std::ostream &stream, const LLBC_NS LLBC_Time &span);

__LLBC_NS_BEGIN

/**
 * \brief LLBC library Time class encapsulation.
 */
class LLBC_EXPORT LLBC_Time
{
public:
    /**
     * Some constants variables define.
     */
    static const int NumOfSecondsPerDay; // Number of seconds per-day.
    static const int NumOfMilliSecondsPerDay; // Number of milli-seconds per-day.
    static const sint64 NumOfMicroSecondsPerDay; // Number of micro-seconds per-day.

    static const int NumOfSecondsPerHour; // Number of seconds per-hour.
    static const int NumOfMilliSecondsPerHour; // Number of milli-seconds per-hour.
    static const sint64 NumOfMicroSecondsPerHour; // Number of micro-seconds per-hour.

    static const int NumOfSecondsPerMinute; // Number of seconds per-minute.
    static const int NumOfMilliSecondsPerMinute; // Number of milli-seconds per-minute.
    static const sint64 NumOfMicroSecondsPerMinute; // Number of micro-seconds per-minute.

    static const int NumOfMilliSecondsPerSecond; // Number of milli-seconds per-second.
    static const sint64 NumOfMicroSecondsPerSecond; // Number of micro-seconds per-second.

    static const sint64 NumOfMicroSecondsPerMilliSecond; // Number of micro-seconds per-millisecond.

public:
    /**
     * Constructors.
     */
    LLBC_Time();
    LLBC_Time(const LLBC_Time &time);
    explicit LLBC_Time(const timeval &tv);
    explicit LLBC_Time(const timespec &ts);
    explicit LLBC_Time(double clanderTime);

    /**
     * Destructor.
     */
    ~LLBC_Time();

public:
    /**
     * Get current time.
     */
    static LLBC_Time Now();

    /**
     * Get current timestamp.
     */
    static uint32 NowTimeStamp();

    /**
     * Get local time parts(year, month, day, hour, minute, second, dayofweek).
     * Notes: GetMonth() start by 1, GetDayOfWeek() start by 0(sunday), GetDayOfYear() start by 1.
     * @return int - the specified time parts.
     */
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    int GetDayOfWeek() const;
    int GetDayOfYear() const;
    int GetHour() const;
    int GetMinute() const;
    int GetSecond() const;
    int GetMilliSecond() const;
    int GetMicroSecond() const;

    /**
     * Get date part time.
     * @return LLBC_Time - the date part time.
     */
    LLBC_Time GetDate() const;
    /**
     * Get current time of day.
     * @return LLBC_TimeSpan - the current time of day.
     */
    LLBC_TimeSpan GetTimeOfDay() const;

    /**
     * Get time tick, in micro seconds.
     * @return uint64 - the time tick, in micro seconds.
     */
    uint64 GetTimeTick() const;
    /**
     * Get timestamp, in seconds.
     * @return uint32 - the timestamp, in seconds.
     */
    uint32 GetTimeStamp() const;

public:
    /**
     * Get GMT time struct.
     * @param[out] time struct - time struct object reference.
     * @return const struct tm & - time struct object.
     */
    const struct tm &GetGmtTime() const;
    void GetGmtTime(struct tm &timeStruct) const;

    /**
     * Get local time struct.
     * @param[out] timeStruct - time struct reference.
     * @return const struct tm & - time struct object.
     */
    const struct tm &GetLocalTime() const;
    void GetLocalTime(struct tm &timeStruct) const;

public:
    /**
     * Format local time, see strftime() api.
     */
    LLBC_String Format(const char *format = NULL) const;
    static LLBC_String Format(double time, const char *format);

    /**
     * Format gmt time, see strftime() api.
     */
    LLBC_String FormatAsGmt(const char *format = NULL) const;
    static LLBC_String FormatAsGmt(double time, const char *format);

public:
    /**
     * Create time object from some ways.
     * @param[in] time         - calendar time, in seconds/milli-seconds/micro-seconds.
     * @param[in] time         - calendar time, in milli seconds.
     * @param[in] time         - calendar time, in micro seconds.
     * @param[in] timeVal      - calendar time in milliseconds representation by timeval struct.
     * @param[in] timeRepr     - time string representation, for example: "2015-12-25 00:00:00.000000".
     * @param[in] <time parts> - the all time parts(year, month, day, ...). 
     * @return LLBC_Time - Time object.
     */
    static LLBC_Time FromSeconds(double time);
    static LLBC_Time FromMilliSeconds(sint64 time);
    static LLBC_Time FromMicroSeconds(sint64 time);
    static LLBC_Time FromTimeVal(const struct timeval &timeVal);
    static LLBC_Time FromTimeRepr(LLBC_String timeRepr);
    static LLBC_Time FromTimeStruct(const struct tm &timeStruct, int milliSecond = 0, int microSecond = 0);
    static LLBC_Time FromTimeParts(int year, int month, int day, int hour, int minute, int second, int milliSecond = 0, int microSecond = 0);

public:
    /**
     * Add specified time parts values.
     * Notes: These operations are thread-safe, all add parts added to new LLBC_Time object.
     * @param[in] <time parts> - the all time parts(year, month, day, ...).
     * @return LLBC_Time - the new time object.
     */
    LLBC_Time AddYears(int years) const;
    LLBC_Time AddMonths(int months) const;
    LLBC_Time AddDays(int days) const;
    LLBC_Time AddHours(int hours) const;
    LLBC_Time AddMinutes(int minutes) const;
    LLBC_Time AddSeconds(int seconds) const;
    LLBC_Time AddMilliSeconds(int milliSeconds) const;
    LLBC_Time AddMicroSeconds(int microSeconds) const;

public:
    /**
     * Makesure given year is leap year or not.
     * @param[in] year - the given year.
      *@return bool - return true it means given year is leap year, otherwise not.
     */
    static bool IsLeapYear(int year);

    /**
     * Get specific month max days.
     * @param[in] year  - the year.
     * @param[in] month - the month.
     * @return int - the specific month max days, if failed, return 0.
     */
    static int GetMonthMaxDays(int year, int month);

public:
    /**
     * Get interval to specify hour,minute,second every day.
     * @param[in] fromTime     - the interval from time.
     * @param[in] secondsInDay - seconds seconds in day.
     * @param[in] hour         - hour.
     * @param[in] minute       - minute.
     * @param[in] second       - second.
     * @param[in] milliSecond  - milli-second.
     * @param[in] microSecond  - micro-second.
     * @return LLBC_TimeSpan - timespan value.
     */
    static LLBC_TimeSpan GetIntervalTo(double secondsInDay);
    static LLBC_TimeSpan GetIntervalTo(int hour, int minute, int second, int milliSecond = 0, int microSecond = 0);
    static LLBC_TimeSpan GetIntervalTo(const LLBC_Time &fromTime, double secondsInDay);
    static LLBC_TimeSpan GetIntervalTo(const LLBC_Time &fromTime, int hour, int minute, int second, int milliSecond = 0, int microSecond = 0);

public:
    /**
     * Time span operations.
     */
    LLBC_TimeSpan operator -(const LLBC_Time &time) const;
    LLBC_TimeSpan operator +(const LLBC_Time &time) const;

    LLBC_Time operator +(const LLBC_TimeSpan &span) const;
    LLBC_Time operator -(const LLBC_TimeSpan &span) const;

    bool operator ==(const LLBC_Time &time) const;
    bool operator !=(const LLBC_Time &time) const;
    bool operator <(const LLBC_Time &time) const;
    bool operator >(const LLBC_Time &time) const;
    bool operator <=(const LLBC_Time &time) const;
    bool operator >=(const LLBC_Time &time) const;

    LLBC_Time &operator =(const LLBC_Time &time);

public:
    /**
     * Stream output operator support.
     */
    friend std::ostream & ::operator <<(std::ostream &o, const LLBC_Time &t);

public:
    /**
     * Serialize / DeSerialize support.
     */
    void Serialize(LLBC_Stream &stream) const;
    bool DeSerialize(LLBC_Stream &stream);

    void SerializeEx(LLBC_Stream &stream) const;
    bool DeSerializeEx(LLBC_Stream &stream);

private:
    void UpdateTimeStructs();

private:
    double _time;
    struct tm _gmtTimeStruct;
    struct tm _localTimeStruct;
};

__LLBC_NS_END

#endif // !__LLBC_CORE_TIME_TIME_H__
