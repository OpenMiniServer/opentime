#include <assert.h>
#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#include "opentime.h"

int main()
{
    OpenTime openTime;
    std::cout << "Current Unixtime:" << openTime.unixtime() << std::endl;
    std::cout << "Current Date:" << openTime.toString() << std::endl;

    int64_t thatTime = 1676704738;
    openTime = thatTime;
    assert(openTime.unixtime() == thatTime);
    assert(openTime.toString() == "2023-02-18 15:18:58");
    openTime = "2023-02-18 15:18:58";
    assert(openTime.unixtime() == thatTime);
    assert(openTime.wday() == 6);

    openTime += 3600 * 24 * 2;
    assert(openTime.toString() == "2023-02-20 15:18:58");

    thatTime = openTime.unixtime();
    assert(openTime.toGMT() == "Mon, 20 Feb 2023 15:18:58 GMT");
    openTime.fromGMT("Mon, 20 Feb 2023 15:18:58 GMT");
    assert(openTime.unixtime() == thatTime);


    int64_t inttime = 20230218133755;
    openTime.fromIntTime(inttime);
    std::string strTime = openTime.toString();
    assert(strTime == "2023-02-18 13:37:55");

    //2023-02-18 00:00:00
    openTime = "2023-02-18 15:18:58";
    int64_t alignTime = openTime.alignDayTime();
    strTime = OpenTime::ToString(alignTime);
    assert(strTime == "2023-02-18 00:00:00");
    
    thatTime = 1642490337;
    alignTime = OpenTime::AlignDayTime(thatTime);
    strTime = OpenTime::ToString(alignTime);
    assert(strTime == "2022-01-18 00:00:00");

    std::map<int64_t, std::vector<std::string>> testDatas = {
        {1676698675, {"2023-02-18 13:37:55", "", "2023-02-18 13:37:55"}},
        {669274675,  {"1991-03-18 13:37:55", "%Y_%M_%D", "1991_03_18"}},
        {1292614675, {"2010-12-18 03:37:55", "%Y_%M_%D_%h_%m_%s", "2010_12_18_03_37_55"}},
        {77693875,   {"1972-06-18 13:37:55", "date:%h:%m:%s %Y/%M/%D%d", "date:13:37:55 1972/06/18%d"}},
    };
    for (auto& iter : testDatas)
    {
        int64_t timeStamp = iter.first;
        openTime = timeStamp;
        auto& datas = iter.second;
        assert(openTime.toString() == datas[0]);

        std::string ret = openTime.toString(datas[1]);
        assert(ret == datas[2]);

        openTime.fromString(ret, datas[1]);
        assert(openTime.unixtime() == timeStamp);
    }

    // sleep 1 second
    OpenTime::Sleep(1000);
    int64_t timeStamp = OpenTime::Unixtime();
    std::cout << "Current timeStamp:" << OpenTime(timeStamp).toString() << std::endl;

    int64_t milliTimeStamp = OpenTime::MilliUnixtime();
    std::cout << "Current milliTimeStamp:" << OpenTime(milliTimeStamp / 1000).toString(milliTimeStamp % 1000) << std::endl;
    return 0;
}