#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qvariantlistlistmodel.h"
#include "excelbase.h"
#include "handletime.h"
#include "qalgorithm.h"
#include "common.h"

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QList>
#include <QScopedPointer>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void main_window_init();
    void start();

private slots:
    void on_pushButton_write_clicked();
    void on_action_open_triggered();
    void on_action_create_triggered();
    void on_pushButton_reset_clicked();
    void on_pushButton_execl_head_clicked();
    void on_textEdit_textChanged();
    void on_pushButton_select_clicked();
    //void on_pushButton_newfile_clicked();

    void on_pushButton_close_clicked();

    void on_dateEdit_editingFinished();

    void on_dateEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_dateEdit_dateChanged(const QDate &date);

public slots:
    void recvMsg(QString msg);
    void on_pushButton_clicked();

signals:
    void sendMsg(QString msg);
private:
    Ui::MainWindow *ui;
private:
    QList< QList<QVariant> > m_datas;

    QString m_product_type;
    QString m_product_size;
    QString m_product_color;
    QString m_baterry_type;
    QString m_water_proof;
    QString m_execl_dir;
    QString m_execlfile_name;
    QString m_log_str;
    QString m_execl_tail;
    QString m_err_info;
    QString m_ui_time;
    QString m_year_str;
    QString m_week_str;
    QString m_day_str;

    qint32  m_execl_sheet;
    unsigned int m_start_id;
    unsigned int m_ispd_num;

    qint32 m_year;
    qint32 m_week;
    qint32 m_day;

    QStringList m_protype_array;
    QStringList m_prosize_array;
    QStringList m_procolor_array;
    QStringList m_battype_array;
    QStringList m_watproof_array;
    QStringList m_execltail_array;
    QStringList m_uitime_array;

    QScopedPointer<ExcelBase> m_xls;
    QScopedPointer<HandleTime> m_time;
    QScopedPointer<QAlgorithm> m_gorithm;
    QScopedPointer<common> m_com;

    float upload_rate;
    float upload_process;
};

#endif // MAINWINDOW_H
