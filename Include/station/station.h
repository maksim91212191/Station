#ifndef STATION_H
#define STATION_H

#include <QWidget>
#include <QPalette>

namespace Station {
    class Station : public QWidget {
    public:
        Station(QWidget* parent = nullptr);
    private:
        QPalette palBack;
    };
}

#endif
