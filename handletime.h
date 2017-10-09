#ifndef HANDLETIME_H
#define HANDLETIME_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <QString>

#define ISLEAPYEAR(year) (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)

class HandleTime
{
public:
    HandleTime();
    ~HandleTime();
    QString Handle_year(int y);
    QString day_of_week(int y, int m, int d);
    QString week_of_year(int y, int m, int d);
private:
};

#endif // HANDLETIME_H
