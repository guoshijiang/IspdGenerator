#include "common.h"

common::common()
{

}

common::~common()
{

}

QString common::handle_color(QString color_str)
{
    QString color;
    if(color_str == color_black_red)
    {
       color = "01";
    }
    else if(color_str == color_white_red)
    {
        color = "02";
    }
    else
    {
        //qDebug() << "error";
    }
    return color;
}

QString common::handle_size(QString size_str)
{
    QString str;
    if(size_str == size_big)
    {
        str = "20";
    }
    else if(size_str == size_middle)
    {
         str = "10";
    }
    else if(size_str == size_small)
    {
         str = "05";
    }
    else
    {
        //qDebug() << "error";
    }
    return str;
}
