#include <QApplication>
#include "InventoryWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    InventoryWindow window;
    window.show();

    return app.exec();
}
