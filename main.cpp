#include "app.h"
#include <clocale>

int main() {
    setlocale(LC_ALL, "Russian");

    CaveApp application;
    application.run();

    return 0;
}