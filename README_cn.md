# OpenTime做最称心的C++开发时间库
跨平台多线程设计！
程序开发频繁涉及时间处理，有一个好用的时间库可以大幅提高工作效率。
OpenTime是最简单易用的C++处理时间工具。

**OpenLinyou项目设计跨平台服务器框架，在VS或者XCode上写代码，无需任何改动就可以编译运行在Linux上，甚至是安卓和iOS.**
OpenLinyou：https://github.com/openlinyou

## 跨平台支持
Windows、linux、Mac、iOS、Android等跨平台设计

## 编译和执行
请安装cmake工具，用cmake可以构建出VS或者XCode工程，就可以在vs或者xcode上编译运行。
源代码：https://github.com/openlinyou/opentime
```
git clone https://github.com/openlinyou/opentime
cd ./opentime
mkdir build
cd build
cmake ..
#如果是win32，在该目录出现opentime.sln，点击它就可以启动vs写代码调试
make
./test
```

## 全部源文件
+ src/opentime.h
+ src/opentime.cpp


## 1.时间戳转换成字符串
```C++
#include <assert.h>
#include <iostream>
#include "opentime.h"
int main()
{
    OpenTime openTime(OpenTime::Unixtime());
    std::cout << "Current Unixtime:" << openTime.unixtime() << std::endl;
    std::cout << "Current Date:" << openTime.toString() << std::endl;

    openTime = 1676704738;
    assert(openTime.unixtime() == 1676704738);
    assert(openTime.wday() == 6);
    assert(openTime.toString() == "2023-02-18 15:18:58");
    assert(openTime.toGMT() == "Mon, 18 Feb 2023 15:18:58 GMT");

    //2023-02-18 13:37:55
    openTime = 1676698675;
    assert(openTime.toString("") == "2023-02-18 13:37:55");
    assert(openTime.toString("_") == "2023_02_18_13_37_55");

    //1991-03-18 13:37:55
    openTime = 669274675;
    assert(openTime.toString("%Y_%M_%D") == "1991_03_18");

    //2010-12-18 03:37:55
    openTime = 1292614675;
    assert(openTime.toString("%Y_%M_%D_%h_%m_%s") == "2010_12_18_03_37_55");

    //1972-06-18 13:37:55
    openTime = 77693875;
    assert(openTime.toString("date:%h:%m:%s %Y/%M/%D%d") == "date:13:37:55 1972/06/18%d");
    return 0;
}
```

## 2.字符串转换成时间戳
```C++
#include <assert.h>
#include <iostream>
#include "opentime.h"
int main()
{
    OpenTime openTime;

    openTime = "2023-02-18 15:18:58";
    int64_t thatTime = 1676704738;
    assert(openTime.unixtime() == thatTime);

    openTime += 3600 * 24 * 2;
    assert(openTime.toString() == "2023-02-20 15:18:58");

    openTime.fromGMT("Sat, 18 Feb 2023 15:18:58 GMT");
    assert(openTime.unixtime() == thatTime);

    //2023-02-18 13:37:55
    std::string strTime = "2023-02-18 13:37:55";
    openTime = strTime;
    assert(openTime.unixtime() == 1676698675);

    //1991-03-18 00:00:00
    strTime = "1991_03_18";
    openTime.fromString(strTime, "%Y_%M_%D");
    assert(openTime.unixtime() == 669225600);

    //2010-12-18 03:37:55
    strTime = "2010_12_18_03_37_55";
    openTime.fromString(strTime, "%Y_%M_%D_%h_%m_%s");
    assert(openTime.unixtime() == 1292614675);

    //1972-06-18 13:37:55
    strTime = "date:13:37:55 1972/06/18%d";
    openTime.fromString(strTime, "date:%h:%m:%s %Y/%M/%D%d");
    assert(openTime.unixtime() == 77693875);

    int64_t milliTimeStamp = OpenTime::MilliUnixtime();
    std::cout << "Current milliTimeStamp:" << OpenTime(milliTimeStamp / 1000).toString(milliTimeStamp % 1000) << std::endl;
    return 0;
}
```

## 3.GMT时间与时间戳转换
```C++
#include <assert.h>
#include <iostream>
#include "opentime.h"
int main()
{
    OpenTime openTime;

    openTime = "2023-02-18 15:18:58";
    openTime += 3600 * 24 * 2;
    assert(openTime.toString() == "2023-02-20 15:18:58");

    int64_t thatTime = openTime.unixtime();
    assert(openTime.toGMT() == "Mon, 20 Feb 2023 15:18:58 GMT");
    openTime.fromGMT("Mon, 20 Feb 2023 15:18:58 GMT");
    assert(openTime.unixtime() == thatTime);

    // sleep 1 second
    OpenTime::Sleep(1000);
    return 0;
}
```

## 4.整数时间与时间戳转换
```C++
#include <assert.h>
#include <iostream>
#include "opentime.h"
int main()
{
    OpenTime openTime;
    
    int64_t inttime = 20230218133755;
    openTime.fromIntTime(inttime);
    assert(openTime.toString() == "2023-02-18 13:37:55");
    assert(openTime.toIntTime() == 20230218133755);
    return 0;
}
```

## 5.时间戳按日对齐
```C++
#include <assert.h>
#include "opentime.h"

int main()
{
    OpenTime openTime;
    //2023-02-18 00:00:00
    openTime = "2023-02-18 15:18:58";
    int64_t alignTime = openTime.alignDay();
    assert(OpenTime::ToString(alignTime) == "2023-02-18 00:00:00");
    
    alignTime = OpenTime::AlignDay(1642490337);
    assert(OpenTime::ToString(alignTime) == "2022-01-18 00:00:00");
    return 0;
}
```
