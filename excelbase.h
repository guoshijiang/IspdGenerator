#ifndef EXCELREADER_H
#define EXCELREADER_H
#include <QObject>
#include <QAxObject>
#include <QString>
#include <QStringList>
#include <QVariant>

class ExcelBasePrivate;

class ExcelBase : public QObject
{
public:
    ExcelBase(QObject* par=NULL);
    ~ExcelBase();
private:
    Q_DISABLE_COPY(ExcelBase)
    Q_DECLARE_PRIVATE(ExcelBase)
    ExcelBasePrivate* const d_ptr;
signals:

public:
    enum Alignment
    {
        xlTop    = -4160,
        xlLeft   = -4131,
        xlRight  = -4152,
        xlCenter = -4108,
        xlBottom = -4107
    };
    bool create(const QString& filename = QString());
    bool open(const QString& filename = QString());
    void saveAs(const QString& filename);
    void save();
    void saveExecl();
    void close();
    void kick();
    void setVisible(bool value);
    void setCaption(const QString& value); //设置Excel文档的标题
    bool addBook();    //新建一本Excel文档
    int sheetCount();  //返回当前Excel的Sheet数量
    QStringList sheetNames(); //返回当前打开的Excel全部Sheet名
    bool currentSheet();    //获得当前Sheet
    bool setCurrentSheet(int index); //设置并指定当前Sheet
    QString currentSheetName();   //当前打开的Excel的Sheet名
    QVariant read(int row, int col);  //读取单元格Sheet的内容
    inline QVariant cell(int row, int col) {return read(row, col);}  //读取单元格Sheet的内容
    void write(int row, int col, const QVariant& value);   //写入单元格Sheet的内容
    void cellFormat(int row, int col, const QString& format); 
    void cellAlign(int row, int col, Alignment hAlign, Alignment vAlign);
    bool usedRange(int& rowStart, int& colStart, int &rowEnd, int &colEnd); //获取有效区域信息
    QVariant readAll();  //读整个sheet
    void readAll(QList<QList<QVariant>> &cells); //读取整个sheet的数据，并放置到cells中
    bool writeCurrentSheet(const QList<QList<QVariant>> &cells);  //写入一个表格内容
    static void convertToColName(int data, QString &res);    //把列数转换为excel的字母列号
    static QString to26AlphabetString(int data);   //数字转换为26字母
    static void castListListVariant2Variant(const QList<QList<QVariant>> &cells,QVariant& res); //QList<QList<QVariant>>转换为QVariant
    static void castVariant2ListListVariant(const QVariant& var,QList<QList<QVariant>> &res); //把QVariant转为QList<QList<QVariant>>
};

#endif
