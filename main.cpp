#include "range.h"
#include "range/v3/view/reverse.hpp"
#include <QMap>
#include <QString>
#include <QtDebug>

using namespace ranges;


int main() {
    QMap<QString, QString> map = {
        { "1" , "a" },
        { "2" , "b" },
        { "3" , "c" },
        { "4" , "d" },
        { "5" , "e" },
    };

    for(auto && v : map | to_std_pairs ) {
        qDebug() << v;
    }

    for(auto && v : map | to_qt_pairs ) {
        qDebug() << v;
    }


    return 0;
}
