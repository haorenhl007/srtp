#include <QApplication>
#include <QLabel>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QImage myImage;
    if (myImage.load("/home/yangzai/test.jpg"))
        cout << "ok" << endl;
    else
        cout << "no" << endl;

    QLabel myLabel;
    myLabel.setPixmap(QPixmap::fromImage(myImage));

    myLabel.show();

    return a.exec();
}
