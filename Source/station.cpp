#include <station/station.h>

namespace Station {
    Station::Station(QWidget* parent)
        : QWidget(parent) {
        setFixedSize(1024, 600);

        palBack.setColor(QPalette::Background, QColor(0, 189, 222));
        setAutoFillBackground(true);
        setPalette(palBack);
    }
}
