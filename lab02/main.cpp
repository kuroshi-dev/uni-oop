#include "MusicBand.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "=== Система управління музичним гуртом ===" << endl;

    Manager manager1("Олексій Петренко", "+380501234567");
    Manager manager2("Світлана Іванова", "+380672345678");

    cout << "\nСтворено менеджерів:" << endl;
    manager1.displayInfo();
    manager2.displayInfo();

    Musician musician1("Іван Коваль", "Гітара Gibson", 2015);
    Musician musician2("Марія Шевченко", "Барабани Yamaha", 2018);
    Musician musician3("Петро Мельник", "Бас-гітара Fender", 2020);
    Musician musician4("Ольга Сидоренко", "Клавішні Korg", 2019);

    musician1.setManager(&manager1);
    musician2.setManager(&manager1);
    musician3.setManager(&manager2);
    musician4.setManager(&manager2);

    cout << "\n=== Створення гурту ===" << endl;
    MusicBand band("Зоряний шлях", "Рок", "Андрій Бондаренко", 15);

    cout << "\n=== Додавання музикантів ===" << endl;
    band.addMusician(&musician1);
    band.addMusician(&musician2);
    band.addMusician(&musician3);
    band.addMusician(&musician4);

    band.displayInfo();

    cout << "\n=== Видалення музиканта ===" << endl;
    band.removeMusician("Петро Мельник");

    band.displayInfo();

    cout << "\n=== Музикант Петро після видалення з гурту ===" << endl;
    musician3.displayInfo();

    cout << "\n=== Кінець програми ===" << endl;

    return 0;
}
