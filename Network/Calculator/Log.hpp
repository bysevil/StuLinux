#include <iostream>
#include <ctime>
#include <mutex>
#include <string>
#include <cstdlib>

namespace bysevil
{

    enum LogLevel
    {
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    class Log
    {
    public:
        void operator()(LogLevel lv, std::string &&text)
        {
            // 获取时间，转换为字符串
            time_t ptime;
            time(&ptime);
            struct tm *ptm = localtime(&ptime);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%04Y-%02m-%02d %02H:%02M:%02S", ptm);
            std::string timestr(buffer);

            // 日志等级转换为字符串
            std::string lvstr;
            std::string strerrmsg;
            std::string strerrno;
            if (lv == DEBUG)
            {
                lvstr = "DEBUG";
            }
            else if (lv == INFO)
            {
                lvstr = "INFO";
            }
            else if (lv == WARN)
            {
                lvstr = "WARN";
            }
            else if (lv == ERROR)
            {
                lvstr = "ERROR";
            }
            else if (lv == FATAL)
            {
                lvstr = "FATAL";
            }

            // 拼接为输出字符串，输出
            std::string str = "[" + lvstr + "][" + timestr + "]#" + text;
            std::cout << str << std::endl;
        };
    };

    Log lg;

}