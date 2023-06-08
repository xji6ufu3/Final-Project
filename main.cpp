//#include "mainwindow.h"

#include <QPushButton>
#include <QToolButton>
#include <QIcon>
#include <QDir>
#include <QStringList>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QHBoxLayout>

void menu(int var){
//    QIcon icon("C:/Users/vicky/Desktop/final.png/a");
//    QString buttonText = "番茄炒蛋";
//    QPushButton button_1(icon, buttonText); //選項方塊

//    //    QToolButton button_1;


//    //    button_1.setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//    //    button_1.setIcon(icon);
//    button_1.setIconSize(QSize(64, 64));    //圖標的像素
//    //button_1.move(100, 100);    //按鈕位置
//    button_1.resize(100, 100);  //按鈕大小
//    button_1.show();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget widget;
    widget.setWindowTitle("Menu");

    QVBoxLayout mainLayout(&widget);
    QHBoxLayout layout_1;

    QIcon icon_1("C:/Users/vicky/Desktop/final.png/a");
    QString buttonText_1 = "a.番茄炒蛋";
    QPushButton button_1(icon_1, buttonText_1); //選項方塊
    button_1.setParent(&widget);
    button_1.setIconSize(QSize(64, 64));    //圖標的像素
    button_1.resize(120, 80);  //按鈕大小
    layout_1.addWidget(&button_1);

    QIcon icon_2("C:/Users/vicky/Desktop/final.png/b");
    QString buttonText_2 = "b.牛肉麵";
    QPushButton button_2(icon_2, buttonText_2); //選項方塊
    button_2.setParent(&widget);
    button_2.setIconSize(QSize(64, 64));    //圖標的像素
    button_2.resize(120, 80);  //按鈕大小
    layout_1.addWidget(&button_2);

    QIcon icon_3("C:/Users/vicky/Desktop/final.png/c");
    QString buttonText_3 = "c.青椒炒蛋";
    QPushButton button_3(icon_3, buttonText_3); //選項方塊
    button_3.setParent(&widget);
    button_3.setIconSize(QSize(64, 64));    //圖標的像素
    button_3.resize(120, 80);  //按鈕大小
    layout_1.addWidget(&button_3);

    QIcon icon_4("C:/Users/vicky/Desktop/final.png/d");
    QString buttonText_4 = "d.牛肉炒蛋";
    QPushButton button_4(icon_4, buttonText_4); //選項方塊
    button_4.setParent(&widget);
    button_4.setIconSize(QSize(64, 64));    //圖標的像素
    button_4.resize(120, 80);  //按鈕大小
    layout_1.addWidget(&button_4);

    QIcon icon_5("C:/Users/vicky/Desktop/final.png/e");
    QString buttonText_5 = "e.青椒牛柳";
    QPushButton button_5(icon_5, buttonText_5); //選項方塊
    button_5.setParent(&widget);
    button_5.setIconSize(QSize(64, 64));    //圖標的像素
    button_5.resize(120, 80);  //按鈕大小
    layout_1.addWidget(&button_5);

    mainLayout.addLayout(&layout_1);
    QHBoxLayout layout_2;

    QIcon icon_6("C:/Users/vicky/Desktop/final.png/f");
    QString buttonText_6 = "f.和牛漢堡";
    QPushButton button_6(icon_6, buttonText_6); //選項方塊
    button_6.setParent(&widget);
    button_6.setIconSize(QSize(64, 64));    //圖標的像素
    button_6.resize(120, 80);  //按鈕大小
    layout_2.addWidget(&button_6);

    QIcon icon_7("C:/Users/vicky/Desktop/final.png/g");
    QString buttonText_7 = "g.蝦仁炒飯";
    QPushButton button_7(icon_7, buttonText_7); //選項方塊
    button_7.setParent(&widget);
    button_7.setIconSize(QSize(64, 64));    //圖標的像素
    button_7.resize(120, 80);  //按鈕大小
    layout_2.addWidget(&button_7);

    QIcon icon_8("C:/Users/vicky/Desktop/final.png/h");
    QString buttonText_8 = "h.紫菜蛋花湯";
    QPushButton button_8(icon_8, buttonText_8); //選項方塊
    button_8.setParent(&widget);
    button_8.setIconSize(QSize(64, 64));    //圖標的像素
    button_8.resize(120, 80);  //按鈕大小
    layout_2.addWidget(&button_8);

    QIcon icon_9("C:/Users/vicky/Desktop/final.png/i");
    QString buttonText_9 = "i.柳橙汁";
    QPushButton button_9(icon_9, buttonText_9); //選項方塊
    button_9.setParent(&widget);
    button_9.setIconSize(QSize(64, 64));    //圖標的像素
    button_9.resize(120, 80);  //按鈕大小
    layout_2.addWidget(&button_9);

    QIcon icon_10("C:/Users/vicky/Desktop/final.png/j");
    QString buttonText_10 = "j.壽司捲";
    QPushButton button_10(icon_10, buttonText_10); //選項方塊
    button_10.setParent(&widget);
    button_10.setIconSize(QSize(64, 64));    //圖標的像素
    button_10.resize(120, 80);  //按鈕大小
    layout_2.addWidget(&button_10);

    mainLayout.addLayout(&layout_2);
    QHBoxLayout layout_3;

    QIcon icon_11("C:/Users/vicky/Desktop/final.png/k");
    QString buttonText_11 = "k.巧克力冰淇淋";
    QPushButton button_11(icon_11, buttonText_11); //選項方塊
    button_11.setParent(&widget);
    button_11.setIconSize(QSize(64, 64));    //圖標的像素
    button_11.resize(120, 80);  //按鈕大小
    layout_3.addWidget(&button_11);

    QIcon icon_12("C:/Users/vicky/Desktop/final.png/l");
    QString buttonText_12 = "l.香蕉巧克力鮮奶油鬆餅";
    QPushButton button_12(icon_12, buttonText_12); //選項方塊
    button_12.setParent(&widget);
    button_12.setIconSize(QSize(64, 64));    //圖標的像素
    button_12.resize(120, 80);  //按鈕大小
    layout_3.addWidget(&button_12);

    QIcon icon_15("C:/Users/vicky/Desktop/final.png/m");
    QString buttonText_15 = "m.牛排";
    QPushButton button_15(icon_15, buttonText_15); //選項方塊
    button_15.setParent(&widget);
    button_15.setIconSize(QSize(64, 64));    //圖標的像素
    button_15.resize(120, 80);  //按鈕大小
    layout_3.addWidget(&button_15);

    mainLayout.addLayout(&layout_3);
    QHBoxLayout layout_4;

    QIcon icon_16("C:/Users/vicky/Desktop/final.png/n");
    QString buttonText_16 = "n.薯條";
    QPushButton button_16(icon_16, buttonText_16); //選項方塊
    button_16.setParent(&widget);
    button_16.setIconSize(QSize(64, 64));    //圖標的像素
    button_16.resize(120, 80);  //按鈕大小
    layout_4.addWidget(&button_16);

    QIcon icon_14("C:/Users/vicky/Desktop/final.png/o");
    QString buttonText_14 = "o.蘿蔔糕";
    QPushButton button_14(icon_14, buttonText_14); //選項方塊
    button_14.setParent(&widget);
    button_14.setIconSize(QSize(64, 64));    //圖標的像素
    button_14.resize(120, 80);  //按鈕大小
    layout_3.addWidget(&button_14);

    QIcon icon_13("C:/Users/vicky/Desktop/final.png/p");
    QString buttonText_13 = "p.玉米濃湯";
    QPushButton button_13(icon_13, buttonText_13); //選項方塊
    button_13.setParent(&widget);
    button_13.setIconSize(QSize(64, 64));    //圖標的像素
    button_13.resize(120, 80);  //按鈕大小
    layout_3.addWidget(&button_13);

    QIcon icon_17("C:/Users/vicky/Desktop/final.png/q");
    QString buttonText_17 = "q.香草冰淇淋";
    QPushButton button_17(icon_17, buttonText_17); //選項方塊
    button_17.setParent(&widget);
    button_17.setIconSize(QSize(64, 64));    //圖標的像素
    button_17.resize(120, 80);  //按鈕大小
    layout_4.addWidget(&button_17);

    QIcon icon_18("C:/Users/vicky/Desktop/final.png/r");
    QString buttonText_18 = "r.蘋果派";
    QPushButton button_18(icon_18, buttonText_18); //選項方塊
    button_18.setParent(&widget);
    button_18.setIconSize(QSize(64, 64));    //圖標的像素
    button_18.resize(120, 80);  //按鈕大小
    layout_4.addWidget(&button_18);

    QIcon icon_19("C:/Users/vicky/Desktop/final.png/s");
    QString buttonText_19 = "s.滷肉飯";
    QPushButton button_19(icon_19, buttonText_19); //選項方塊
    button_19.setParent(&widget);
    button_19.setIconSize(QSize(64, 64));    //圖標的像素
    button_19.resize(120, 80);  //按鈕大小
    layout_4.addWidget(&button_19);

    QIcon icon_20("C:/Users/vicky/Desktop/final.png/t");
    QString buttonText_20 = "t.地瓜球";
    QPushButton button_20(icon_20, buttonText_20); //選項方塊
    button_20.setParent(&widget);
    button_20.setIconSize(QSize(64, 64));    //圖標的像素
    button_20.resize(120, 80);  //按鈕大小
    layout_4.addWidget(&button_20);

    mainLayout.addLayout(&layout_4);

    widget.setLayout(&mainLayout);
    widget.show();

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "qt_test_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    return a.exec();
}
