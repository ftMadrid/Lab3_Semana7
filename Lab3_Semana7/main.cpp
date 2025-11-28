#include <QCoreApplication>

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::map;

struct Product{

    string name;
    int quantity;

};

unsigned char to_lower_char(unsigned char c) {
    return std::tolower(c);
}

string to_lower(const string& s) {
    string out = s;
    transform(out.begin(), out.end(), out.begin(), to_lower_char);
    return out;
}

void showInventory(const map<int, Product>& inventory) {
    cout << "\n==== INVENTORY ====" << endl;
    cout << "CODE\tCANT\tPRODUCT" << endl;
    cout << "===========================" << endl;

    for (map<int, Product>::const_iterator it = inventory.begin(); it != inventory.end(); ++it) {
        cout << it->first << "\t"
             << it->second.quantity << "\t"
             << it->second.name << endl;
    }
    cout << "===========================" << endl;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "Viva Choloma!" << endl;

    return a.exec();
}
