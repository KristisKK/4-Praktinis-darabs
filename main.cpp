#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

// Struktura meniu elementams
struct menuItemType {
    string menuItem;
    double menuPrice;
};

// Funkcija ikelia duomenis i masyva menuList
void getData(vector<menuItemType>& menuList) {
    menuList.push_back({"Kiausiniene", 1.45});
    menuList.push_back({"Kiaulienos sonine su keptu kiausiniu", 2.45});
    menuList.push_back({"Keksiukas su vysnia", 0.99});
    menuList.push_back({"Prancuziskas skrebutis", 1.99});
    menuList.push_back({"Vaisiu salotos", 2.49});
    menuList.push_back({"Pusryciu dribsniai", 0.69});
    menuList.push_back({"Kava", 0.50});
    menuList.push_back({"Arbata", 0.75});
}

// Funkcija rodo meniu ir leidzia pasirinkti patiekalus
void showMenu(const vector<menuItemType>& menuList) {
    cout << "Sveiki atvyke i restorana \"6 Kepykla\"" << endl;
    cout << "Pasirinkite norimus patiekalus ir nurodykite kieki:" << endl;

    for (int i = 0; i < menuList.size(); ++i) {
        cout << i + 1 << ". " << menuList[i].menuItem << " - "
             << fixed << setprecision(2) << menuList[i].menuPrice << "Eur" << endl;
    }
}

// Funkcija apskaiciuoja ir atspausdina saskaita
void printCheck(const vector<menuItemType>& menuList, const vector<int>& order) {
    double total = 0.0;
    ofstream receipt("saskaita.txt");

    cout << "\nJusu uzsakymas:\n";
    receipt << "Jusu uzsakymas:\n";

    for (int i = 0; i < order.size(); ++i) {
        int itemIndex = order[i] - 1;
        double price = menuList[itemIndex].menuPrice;
        cout << i + 1 << " " << menuList[itemIndex].menuItem << " "
             << fixed << setprecision(2) << price << "Eur" << endl;
        receipt << i + 1 << " " << menuList[itemIndex].menuItem << " "
                << fixed << setprecision(2) << price << "Eur" << endl;
        total += price;
    }

    double taxes = total * 0.21;
    double finalTotal = total + taxes;

    cout << "Mokesciai: " << fixed << setprecision(2) << taxes << "Eur" << endl;
    cout << "Galutine suma: " << fixed << setprecision(2) << finalTotal << "Eur" << endl;

    receipt << "Mokesciai: " << fixed << setprecision(2) << taxes << "Eur" << endl;
    receipt << "Galutine suma: " << fixed << setprecision(2) << finalTotal << "Eur" << endl;

    receipt.close();
}

int main() {
    vector<menuItemType> menuList;
    vector<int> order;

    getData(menuList);

    showMenu(menuList);

    int choice, quantity;
    cout << "\nIveskite pasirinkto patiekalo numeri ir kieki (0 - baigti uzsakyma):\n";

    while (true) {
        cout << "Pasirinkite patiekala (0 baigti): ";
        cin >> choice;

        if (choice == 0) {
            break;
        }

        if (choice < 1 || choice > menuList.size()) {
            cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
            continue;
        }

        cout << "Iveskite kieki: ";
        cin >> quantity;

        for (int i = 0; i < quantity; ++i) {
            order.push_back(choice);
        }
    }

    printCheck(menuList, order);

    return 0;
}
