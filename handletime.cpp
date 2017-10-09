#include "handletime.h"

HandleTime::HandleTime()
{

}

HandleTime::~HandleTime()
{

}

//年转换函数
QString HandleTime::Handle_year(int y)
{
    QString year_num_str;
    int year_num = 0;
    year_num = y - 2016;
    if(year_num < 10)
    {
        year_num_str = "0" + QString::number(year_num);
    }
    else
    {
        year_num_str = QString::number(year_num);
    }
    return year_num_str;
}

//计算某日为该年的第多少周
QString HandleTime::week_of_year(int y, int m, int d)
{
  struct tm tm;
  char time_buf[10];
  QString time_buf_str;
  memset(&tm, 0, sizeof(struct tm));
  tm.tm_mday = d;
  tm.tm_mon = m;
  tm.tm_year = y - 1900;
  mktime(&tm);
  strftime(time_buf, sizeof(time_buf), "%W", &tm);
  time_buf_str = QString(time_buf);
  return time_buf_str;
}

//计算该天是星期几函数.
QString HandleTime::day_of_week(int y, int m, int d)
{
    int w_day = 0;
    QString w_day_str;
    if (m == 1 || m == 2)
    {
        m += 12;
        y--;
    }
    int weekday = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    switch (weekday)
    {
        case 0: w_day = 1; break;
        case 1: w_day = 2; break;
        case 2: w_day = 3; break;
        case 3: w_day = 4; break;
        case 4: w_day = 5; break;
        case 5: w_day = 6; break;
        case 6: w_day = 7; break;
    }
    w_day_str = QString::number(w_day);
    return w_day_str;
}

