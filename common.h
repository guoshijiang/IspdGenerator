﻿#ifndef COMMON_H
#define COMMON_H
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define color_black_red "黑红"
#define color_white_red "白红"

#define size_big    "大"
#define size_middle "中"
#define size_small  "小"


class common
{
public:
    common();
    ~common();
    QString handle_color(QString color_str);
    QString handle_size(QString size_str);
};

#endif // COMMON_H
