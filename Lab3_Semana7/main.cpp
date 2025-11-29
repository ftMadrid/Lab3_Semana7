#include <QCoreApplication>

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <map>

using std::cout;
using std::endl;
using std::cin;
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
    cout << "\n=========== INVENTORY ==========\n" << endl;
    cout << "CODE\tCANT\tPRODUCT\n" << endl;

    for (map<int, Product>::const_iterator it = inventory.begin(); it != inventory.end(); ++it) {
        cout << it->first << "\t"
             << it->second.quantity << "\t"
             << it->second.name << endl;
    }
    cout << "=================================" << endl;
}

void searchProductByCode(const map<int, Product>& inventory, int code) {

    map<int, Product>::const_iterator it = inventory.find(code);

    if (it != inventory.end()) {
        cout << "\n[PRODUCT FOUND]: " << endl;
        cout << "\n| Code: " << it->first << endl;;
        cout << "| Name: " << it->second.name << endl;
        cout << "| Quantity: " << it->second.quantity << endl;
    } else {
        cout << "\n| Product with that code [" << code << "] doesnt exists!" << endl;
    }
}

void searchProductByName(const map<int, Product>& inventory, string name){

    string searchLower = to_lower(name);
    bool find = false;

    cout << "\n ====== SEARCH RESULT ======" << endl;

    for (map<int, Product>::const_iterator it = inventory.begin(); it != inventory.end(); ++it) {
        string nameLower = to_lower(it->second.name);

        if (nameLower.find(searchLower) != string::npos) {
            cout << "\n[PRODUCT FOUND]: " << endl;
            cout << "\n| Code: " << it->first << endl;;
            cout << "| Name: " << it->second.name << endl;
            cout << "| Quantity: " << it->second.quantity << endl;
            find = true;
        }
    }

    if (!find) {
        cout << "\n| There is no product with that name!" << endl;
    }
}

void updateQuantity(map<int, Product>& inventory, int code, int delta) {
    map<int, Product>::iterator it = inventory.find(code);

    if (it != inventory.end()) {
        int newCant = it->second.quantity + delta;

        if (newCant < 0) {
            cout << "\n| The output exceeds the current stock! It will be adjusted to 0." << endl;
            it->second.quantity = 0;
        } else {
            it->second.quantity = newCant;
            cout << "\n| Stock Updated!" <<endl;
            cout << "| New Total: " << newCant << endl;
        }
    } else {
        cout << "\n| We cannot updated because the code [" << code << "] doesnt exists!" << endl;
    }
}

void addProduct(map<int, Product>& inventory, int code, string name, int quantity) {
    if (quantity < 0) {
        cout << "\n| The quantity cant be negative! It will be setted to 0." << endl;
        quantity = 0;
    }

    map<int, Product>::iterator it = inventory.find(code);

    if (it != inventory.end()) {
        cout << "\n| There is already a product with this code!" << endl;
        return;
    } else {
        Product newProduct;
        newProduct.name = name;
        newProduct.quantity = quantity;

        inventory[code] = newProduct;

        cout << "\n| The product " << name << " with code [" << code << "] has been created!" <<endl;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    map<int, Product> inventory;

    inventory[100] = {"Carton de Huevos", 30};
    inventory[200] = {"Leche Descremada", 20};
    inventory[300] = {"Harina El Gallo", 45};
    inventory[400] = {"Maseca", 40};
    inventory[500] = {"Salsina", 25};

    int option = 0, code = 0, quantity = 0;
    string name;

    do{
        cout << "\n ===== CHOLOMA STORE =====\n" << endl;
        cout << "1. Add a product" <<endl;
        cout << "2. Show inventory" <<endl;
        cout << "3. Search product by code" <<endl;
        cout << "4. Search product by name" <<endl;
        cout << "5. Update product quantity" <<endl;
        cout << "6. Exit" <<endl;

        cout << "\n| Select an option: ";
        cin >> option;

        switch(option){
        case 1:
            cout << "\n ===== ADD A PRODUCT ====\n" <<endl;
            cout << "| Enter the code: ";
            cin >> code;
            cin.ignore();
            cout << "| Enter the name: ";
            std::getline(cin, name);
            cout << "| Enter the quantity: ";
            cin >> quantity;
            addProduct(inventory, code, name, quantity);
            break;
        case 2:
            showInventory(inventory);
            break;
        case 3:
            cout << "\n ===== SEARCH PRODUCT [BY CODE] ====\n" <<endl;
            cout << "| Enter the code: ";
            cin >> code;
            searchProductByCode(inventory, code);
            break;
        case 4:
            cin.ignore();
            cout << "\n ===== SEARCH PRODUCT [BY NAME] ====\n" <<endl;
            cout << "| Enter the name: ";
            std::getline(cin, name);
            searchProductByName(inventory, name);
            break;
        case 5:
            cout << "\n ===== UPDATE PRODUCT QUANTITY ====\n" <<endl;
            cout << "| Enter the code: ";
            cin >> code;
            cout << "| Enter the new quantity: ";
            cin >> quantity;
            updateQuantity(inventory, code, quantity);
            break;
        case 6:
            cout << "\n| Have a nice day!" << endl;
            break;
        default:
            cout << "\n| This option doesnt exists!" <<endl;
            break;
        }

    }while(option != 6);

    cout << "| Viva Choloma!" << endl;

    return a.exec();
}
