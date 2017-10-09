#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qvariantlistlistmodel.h"
#include <QSettings>
#include <QDebug>
#include <QStringList>
#include <QAxObject>
#include <QScopedPointer>
#include <QFileDialog>
#include <QDateTime>
#include <QTextCursor>
#include <QMessageBox>
#include <QDir>

#define MESSAGE_RED "<font size = 200 color = red ><strong>"
#define MESSAGE_GREEN "<font size = 200 color = blue ><strong>"
#define MESSAGE_END "</strong></font>"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QDir dir;
    QString program_path = dir.currentPath();
    QString path = program_path + "/config.ini";
    qDebug() << "path = " << path;
    QSettings settings(path, QSettings::IniFormat);
    this->m_product_type = settings.value("product_type").toString();
    this->m_product_size = settings.value("product_size").toString();
    this->m_product_color = settings.value("product_color").toString();
    this->m_baterry_type = settings.value("baterry_type").toString();
    this->m_water_proof = settings.value("water_proof").toString();
    this->m_execl_dir = settings.value("execl_dir").toString();
    this->m_execl_tail = settings.value("execl_tail").toString();
    if(this->m_product_type != NULL)
    {
        this->m_protype_array = this->m_product_type.split("|");
    }
    if(this->m_product_size != NULL)
    {
        this->m_prosize_array = this->m_product_size.split("|");
    }
    if(this->m_product_color != NULL)
    {
        this->m_procolor_array = this->m_product_color.split("|");
    }
    if(this->m_baterry_type != NULL)
    {
        this->m_battype_array = this->m_baterry_type.split("|");
    }
    if(this->m_water_proof != NULL)
    {
        this->m_watproof_array = this->m_water_proof.split("|");
    }
    if(this->m_execl_tail != NULL)
    {
        this->m_execltail_array = this->m_execl_tail.split("|");
    }
    ui->setupUi(this);
    this->ui->uploadProgressBar->setMinimum(0);
    this->ui->uploadProgressBar->setMaximum(100);
    this->ui->uploadProgressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::main_window_init()
{
    for(qint32 i = 0; i < this->m_protype_array.size(); i++)
    {
        ui->comboBox_type->addItem(this->m_protype_array[i]);
    }
    for(qint32 i = 0; i < this->m_prosize_array.size(); i++)
    {
        ui->comboBox_size->addItem(this->m_prosize_array[i]);
    }
    for(qint32 i = 0; i < this->m_procolor_array.size(); i++)
    {
        ui->comboBox_color->addItem(this->m_procolor_array[i]);
    }
    for(qint32 i = 0; i < this->m_battype_array.size(); i++)
    {
        ui->comboBox_bat->addItem(this->m_battype_array[i]);
    }
    for(qint32 i = 0; i < this->m_watproof_array.size(); i++)
    {
        ui->comboBox_water->addItem(this->m_watproof_array[i]);
    }
    /*
    for(qint32 i = 0; i < this->m_execltail_array.size(); i++)
    {
        ui->comboBox_execl_tail->addItem(this->m_execltail_array[i]);
    }
    ui->comboBox_year->addItem("01");
    ui->comboBox_week->addItem("01");
    ui->comboBox_day->addItem("1");
   */
    this->ui->dateEdit->setDateTime(QDateTime::currentDateTime());
    this->ui->pushButton_select->setDisabled(true);
    this->ui->pushButton_reset->setDisabled(true);
    this->ui->pushButton_write->setDisabled(true);
    this->ui->pushButton_close->setDisabled(true);
    this->ui->pushButton_execl_head->setDisabled(true);
}

void MainWindow::start()
{
    //this->setAutoFillBackground(true);
    //this->setMouseTracking(false);
    //this->setFixedSize(1130, 1020);
    //this->setWindowFlags(windowFlags()|Qt::WindowMinimizeButtonHint|Qt::WindowStaysOnTopHint);
    this->showMaximized();

    main_window_init();
    connect(this, SIGNAL(sendMsg(QString)), this, SLOT(recvMsg(QString)));
}

void MainWindow::on_action_open_triggered()
{
    QString xls_file_name = QFileDialog::getOpenFileName(this,QString(),QString(),"excel(*.xls *.xlsx)");
    if(xls_file_name.isEmpty())
    {
       return ;
    }
    if(m_xls.isNull())
    {
       m_xls.reset(new ExcelBase);
    }
    this->m_execlfile_name = xls_file_name;
    m_xls->open(this->m_execlfile_name);
    QString sentence_log = QString::fromLocal8Bit("打开文件成功:");
    this->m_log_str = sentence_log + this->m_execlfile_name;
    ui->textEdit_optlog->append(m_log_str);
    ui->pushButton_select->setEnabled(true);
}

void MainWindow::on_action_create_triggered()
{
    QString fpath = QCoreApplication::applicationDirPath() + "/path";
    QFileDialog dialog(this);
    dialog.setWindowTitle(QString::fromLocal8Bit("新建文件"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDirectory(fpath);
    dialog.setNameFilter("execl file(*.xls *.xlsx)");
    if(QDialog::Accepted == dialog.exec())
    {
        QString sentence_log = QString::fromLocal8Bit("创建文档成功:");
        QString new_file_name = dialog.selectedFiles()[0];
        if(m_xls.isNull())
        {
            m_xls.reset(new ExcelBase);
        }
        m_xls->create(new_file_name);
         m_xls->save();
        this->m_log_str = sentence_log + new_file_name;
        ui->textEdit_optlog->append(this->m_log_str);
    }
#if 0
    QString xls_file = QFileDialog::getExistingDirectory(this);
    static qint32 execl_back = 0;
    QString sentence_log = tr("通过对话框的形式创建文档成功:");
    if(xls_file.isEmpty())
    {
        return ;
    }
    QString tail = QString::number(++execl_back);
    xls_file += "/" + tr("文档") + tail + ".xls";
    if(m_xls.isNull())
    {
        m_xls.reset(new ExcelBase);
    }
    m_xls->create(xls_file);
    m_xls->save();
    this->m_log_str = sentence_log + xls_file;
    ui->textEdit_optlog->append(this->m_log_str);
#endif
}

void MainWindow::on_pushButton_write_clicked()
{
    static qint32 A_I = 1;
    QString       ispd_year;
    QString       ispd_month;
    QString       ispd_day;
    char          psztemp[64] = {0};
    QString       encrypt_str;
    if(this->ui->lineEdit_startid->text() == NULL || this->ui->lineEdit_need_num->text() == NULL)
    {
        this->m_err_info = QString::fromLocal8Bit("起始ID或者录入的需求个数为空,请您必须输入!");
        QString err_info = MESSAGE_RED + m_err_info + MESSAGE_END;
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), err_info);
        qCritical() << m_err_info;
        this->ui->textEdit_optlog->append(m_err_info);
        return ;
    }

    this->m_ui_time =  ui->dateEdit->text();
    if(this->m_ui_time != NULL)
    {
      this->m_uitime_array  = this->m_ui_time.split("/");
    }
    for(qint32 i = 0; i < this->m_uitime_array.size(); i++)
    {
        this->m_year_str  = this->m_uitime_array[0];
        this->m_week_str = this->m_uitime_array[1];
        this->m_day_str   = this->m_uitime_array[2];
    }
    this->m_year = this->m_year_str.toInt();
    this->m_week = this->m_week_str.toInt();
    this->m_day = this->m_day_str.toInt();

    this->upload_process = 0;
    this->ui->uploadProgressBar->setValue(this->upload_process);

    this->m_start_id = ui->lineEdit_startid->text().toInt();
    this->m_ispd_num = ui->lineEdit_need_num->text().toInt();

    ispd_year = m_time->Handle_year(this->m_year);
    ispd_month = m_time->week_of_year(this->m_year, this->m_week, this->m_day);
    ispd_day = m_time->day_of_week(this->m_year, this->m_week, this->m_day);

    this->upload_rate = 100.0 / float(this->m_ispd_num);
    m_xls->setCurrentSheet(this->m_execl_sheet);
    QString ispd_color = ui->comboBox_color->currentText().trimmed();
    QString ispd_size = ui->comboBox_size->currentText().trimmed();
    for(int i = this->m_start_id; i < (this->m_start_id + this->m_ispd_num); i++)
    {

        QString sentence_log = QString::fromLocal8Bit("数据写入Eexecl文件成功:");
        QDateTime time = QDateTime::currentDateTime();
        QString time_str = time.toString("yyyy-MM-dd hh:mm:ss");
        QString ispd_str = QString::number(i);

        snprintf(psztemp, 64, "%u", i);
        assert(0 != strlen(psztemp));
        unsigned int base = pow(10, strlen(psztemp)) *  100;
        encrypt_str = this->m_gorithm->encrypt_ispd_id(i + base);

        QString ser_number = this->m_year_str + this->m_week_str + this->m_day_str + ui->comboBox_type->currentText() +
                this->m_com->handle_color(ispd_color) + this->m_com->handle_size(ispd_size) + encrypt_str;

        m_xls->write(++A_I, 1, ispd_str);
        m_xls->write(A_I, 2, encrypt_str);
        m_xls->write(A_I, 3, ui->comboBox_type->currentText());
        m_xls->write(A_I, 4, ui->comboBox_color->currentText());
        m_xls->write(A_I, 5, ui->comboBox_bat->currentText());
        m_xls->write(A_I, 6, ui->comboBox_water->currentText());
        m_xls->write(A_I, 7, ui->lineEdit_v->text());
        m_xls->write(A_I, 8, ui->lineEdit_i->text());
        m_xls->write(A_I, 9, ui->lineEdit_cap->text());
        m_xls->write(A_I, 10, ser_number);
        m_xls->write(A_I, 11, time_str);
        this->upload_process += this->upload_rate;
        this->ui->uploadProgressBar->setValue(int(this->upload_process));
        QString log = sentence_log + ispd_str + ispd_str + ui->comboBox_type->currentText()
                + ui->comboBox_color->currentText() + ui->comboBox_bat->currentText() +
                ui->comboBox_water->currentText() + ui->lineEdit_v->text() + ui->lineEdit_i->text()
                + ui->lineEdit_cap->text() + QString::number(i) + time_str;
        emit sendMsg(log);
    }
    this->ui->uploadProgressBar->setValue(100);
    m_xls->save();
    ui->label_status_result->setText(QString::fromLocal8Bit("写入Execl文件成功"));
    ui->pushButton_write->setDisabled(true);
    ui->pushButton_close->setEnabled(true);
    ui->pushButton_reset->setDisabled(false);
}

void MainWindow::recvMsg(QString msg)
{
    this->m_log_str = msg;
    ui->textEdit_optlog->append(this->m_log_str);
}

void MainWindow::on_pushButton_reset_clicked()
{
    ui->lineEdit_startid->clear();
    ui->lineEdit_need_num->clear();
    this->ui->uploadProgressBar->setValue(0);
    ui->lineEdit_i->clear();
    ui->lineEdit_v->clear();
    ui->lineEdit_cap->clear();
    ui->pushButton_reset->setEnabled(false);
    ui->textEdit_optlog->clear();
    ui->label_status_result->setText(QString::fromLocal8Bit("重置成功"));
    ui->pushButton_write->setEnabled(true);
}



void MainWindow::on_textEdit_textChanged()
{
    QTextCursor cursor = ui->textEdit_optlog->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_optlog->setTextCursor(cursor);
}

void MainWindow::on_pushButton_select_clicked()
{
    this->m_execl_sheet = ui->lineEdit_sheets->text().toInt();
    QString sentence_log = QString::fromLocal8Bit("选择工作sheet成功:");
    this->m_log_str = sentence_log + QString::number(this->m_execl_sheet);
    ui->textEdit_optlog->append(m_log_str);
    this->ui->pushButton_execl_head->setEnabled(true);
}

void MainWindow::on_pushButton_clicked()
{
   this->m_log_str = QString::fromLocal8Bit("关闭Execl成功");
   m_xls->close();
   ui->textEdit_optlog->append(this->m_log_str);
}

#if 0
void MainWindow::on_pushButton_newfile_clicked()
{
    QString execl_file_name = ui->lineEdit_newfile->text();
    QString execl_tail_str = ui->comboBox_execl_tail->currentText();
    QString new_file_name  = this->m_execl_dir + execl_file_name + execl_tail_str;
    QString sentence_log = tr("通过按钮组件新建Execl文档成功:");
    if(m_xls.isNull())
    {
        m_xls.reset(new ExcelBase);
    }
    m_xls->create(new_file_name);
    m_xls->save();
    this->m_log_str = sentence_log + new_file_name;
    ui->textEdit_optlog->append(this->m_log_str);
}
#endif


void MainWindow::on_pushButton_close_clicked()
{
    QString sentence_log = QString::fromLocal8Bit("关闭Execl成功:");
    if(!m_xls.isNull())
    {
        m_xls->close();
        this->m_log_str = sentence_log + this->m_execlfile_name;
        ui->textEdit_optlog->append(this->m_log_str);
    }
    this->ui->pushButton_reset->setDisabled(true);
    this->ui->pushButton_select->setDisabled(true);
    this->ui->pushButton_write->setDisabled(true);
}

void MainWindow::on_pushButton_execl_head_clicked()
{
    m_xls->setCurrentSheet(this->m_execl_sheet);
    m_xls->write(1, 1, QString::fromLocal8Bit("超级版原始ID"));
    m_xls->write(1, 2, QString::fromLocal8Bit("超级版加密ID"));
    m_xls->write(1, 3, QString::fromLocal8Bit("产品型号"));
    m_xls->write(1, 4, QString::fromLocal8Bit("产品颜色"));
    m_xls->write(1, 5, QString::fromLocal8Bit("电池类型"));
    m_xls->write(1, 6, QString::fromLocal8Bit("防水等级"));
    m_xls->write(1, 7, QString::fromLocal8Bit("输入电压"));
    m_xls->write(1, 8, QString::fromLocal8Bit("输入电流"));
    m_xls->write(1, 9, QString::fromLocal8Bit("电池容量"));
    m_xls->write(1, 10, QString::fromLocal8Bit("序列号"));
    m_xls->write(1, 11, QString::fromLocal8Bit("日期时间"));
    m_xls->save();
    QString sentence_log = QString::fromLocal8Bit("设置execl的头部成功:设置项包括->超级版原始ID->超级版加密ID->产品型号"
                              "->产品颜色->电池类型->防水等级->输入电压->输入电流->电池容量->"
                              "序列号->日期时间");
    this->m_log_str  = sentence_log;
    ui->textEdit_optlog->append(m_log_str);
    ui->label_status_result->setText(QString::fromLocal8Bit("设置execl头成功"));
    ui->pushButton_write->setEnabled(true);
}
