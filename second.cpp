#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class shopping {
private:
    int pcode;
    float price;
    float dis;
    string pname;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void recepit();
    void recommendProducts(string product);
    void feedback();
    void aiAssistant(); // AI Chat Assistant
};

// Product recommendations based on simple associations
map<string, vector<string>> recommendations = {
    {"Milk", {"Bread", "Eggs", "Butter"}},
    {"Shampoo", {"Conditioner", "Body Wash", "Soap"}},
    {"Rice", {"Beans", "Lentils", "Spices"}},
    {"Bread", {"Jam", "Butter", "Cheese"}},
    {"Coffee", {"Milk", "Sugar", "Cookies"}}
};

void shopping::menu() {
m:
    int choice;
    string email;
    string password;

    cout << "\t\t\t\t__________________________________\n";
    cout << "\t\t\t\t                                  \n";
    cout << "\t\t\t\t      SuperMarket Main Menu       \n";
    cout << "\t\t\t\t                                  \n";
    cout << "\t\t\t\t__________________________________\n";
    cout << "\t\t\t\t                                  \n";

    cout << "\t\t\t\t|  1) Administrator   |\n";
    cout << "\t\t\t\t|                     |\n";
    cout << "\t\t\t\t|  2) Buyer           |\n";
    cout << "\t\t\t\t|                     |\n";
    cout << "\t\t\t\t|  3) AI Assistant    |\n";
    cout << "\t\t\t\t|                     |\n";
    cout << "\t\t\t\t|  4) Exit            |\n";
    cout << "\t\t\t\t|                     |\n";
    cout << "\n\t\t\t Please Select: ";
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "\t\t\t Please Login\n";
        cout << "\t\t\t Enter E-Mail: ";
        cin >> email;
        cout << "\t\t\t Enter Password: ";
        cin >> password;
        if (email == "admin@gmail.com" && password == "admin123") {
            administrator();
        } else {
            cout << "Invalid User E-Mail or Password\n";
        }
        break;
    case 2:
        buyer();
        break;
    case 3:
        aiAssistant();
        break;
    case 4:
        exit(0);
    default:
        cout << "Please Select from the given options\n";
    }
    goto m;
}

void shopping::administrator() {
m:
    int choice;
    cout << "\n\n\n\t\t\t|  Administrator Menu";
    cout << "\n\t\t\t|_____1) Add the product________|";
    cout << "\n\t\t\t|                               |";
    cout << "\n\t\t\t|_____2) Modify the product_____|";
    cout << "\n\t\t\t|                               |";
    cout << "\n\t\t\t|_____3) Delete the product_____|";
    cout << "\n\t\t\t|                               |";
    cout << "\n\t\t\t|_____4) Back to main menu______|";

    cout << "\n\n\t Please enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        add();
        break;
    case 2:
        edit();
        break;
    case 3:
        rem();
        break;
    case 4:
        menu();
        break;
    default:
        cout << "Invalid Choice\n";
        break;
    }
    goto m;
}

void shopping::buyer() {
m:
    int choice;
    cout << "\t\t\t   Buyer\n";
    cout << "\n\t\t\t 1) Buy Product\n";
    cout << "\n\t\t\t 2) Go back\n";
    cout << "\t\t\t Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        recepit();
        break;
    case 2:
        menu();
        break;
    default:
        cout << "Invalid Choice\n";
        break;
    }
    goto m;
}

void shopping::add() {
    fstream data;
    int c;
    float p, d;
    string n;

    cout << "\n\n\t\t\t Add New Product";
    cout << "\n\n\t Product Code: ";
    cin >> pcode;
    cout << "\n\n\t Name of the Product: ";
    cin >> pname;
    cout << "\n\n\t Price of Product: ";
    cin >> price;
    cout << "\n\n\t Discount on Product: ";
    cin >> dis;

    data.open("database.txt", ios::app | ios::out);
    data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
    data.close();

    cout << "\n\n\t\t Record Inserted!";
}

void shopping::list() {
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n|______________________________________\n";
    cout << "ProNo\t\tName\t\tPrice\n";
    cout << "|______________________________________\n";
    data >> pcode >> pname >> price >> dis;

    while (!data.eof()) {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void shopping::aiAssistant() {
    cout << "\n\n\t\tHello! I'm your AI Shopping Assistant. How can I help you today?\n";
    cout << "\t- You can ask about products, recommendations, or provide feedback.\n";
    cout << "\t- Type 'recommend' followed by a product name for suggestions.\n";
    cout << "\t- Type 'feedback' to provide feedback.\n";
    cout << "\t- Type 'exit' to go back to the main menu.\n\n";

    string input;
    cin.ignore();
    while (true) {
        cout << "You: ";
        getline(cin, input);

        if (input == "exit") {
            break;
        } else if (input.find("recommend") != string::npos) {
            string product = input.substr(10);
            recommendProducts(product);
        } else if (input == "feedback") {
            feedback();
        } else {
            cout << "AI Assistant: I'm here to help! Try asking for 'recommend <product>' or 'feedback'.\n";
        }
    }
}

void shopping::recommendProducts(string product) {
    transform(product.begin(), product.end(), product.begin(), ::tolower);
    bool found = false;
    for (const auto& pair : recommendations) {
        string key = pair.first;
        transform(key.begin(), key.end(), key.begin(), ::tolower);
        if (key == product) {
            cout << "\nBased on your interest in " << pair.first << ", you might also like:\n";
            for (const string& item : pair.second) {
                cout << "- " << item << "\n";
            }
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Sorry, I have no recommendations for that product.\n";
    }
}

void shopping::feedback() {
    string feedback;
    cout << "\nPlease provide your feedback: ";
    getline(cin, feedback);

    if (feedback.find("good") != string::npos || feedback.find("excellent") != string::npos) {
        cout << "Thank you for your positive feedback!\n";
    } else if (feedback.find("bad") != string::npos || feedback.find("poor") != string::npos) {
        cout << "We're sorry to hear that. We'll work on improving our services.\n";
    } else {
        cout << "Thank you for your feedback!\n";
    }
}

void shopping::rem() {
    fstream data, data1;
    int pkey;
    int tokens = 0;

    cout << "\n\n\t Delete Product";
    cout << "\n\n\t Enter Product Code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\nFile doesn't exist!";
        return;
    }

    data1.open("database1.txt", ios::app | ios::out);
    data >> pcode >> pname >> price >> dis;

    while (!data.eof()) {
        if (pcode == pkey) {
            cout << "\n\n\t Product Deleted Successfully!";
            tokens++;
        } else {
            data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
        }
        data >> pcode >> pname >> price >> dis;
    }

    data.close();
    data1.close();

    remove("database.txt");
    rename("database1.txt", "database.txt");

    if (tokens == 0) {
        cout << "\n\n Record Not Found!";
    }
}

void shopping::edit() {
    fstream data, data1;
    int pkey;
    int tokens = 0;
    int c;
    float p, d;
    string n;

    cout << "\n\t\t\t Modify the Record ";
    cout << "\n\t\t\t Enter Product Code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\nFile doesn't exist!";
        return;
    }

    data1.open("database1.txt", ios::app | ios::out);
    data >> pcode >> pname >> price >> dis;

    while (!data.eof()) {
        if (pkey == pcode) {
            cout << "\n\t\t New Product Code: ";
            cin >> c;
            cout << "\n\t\t New Name of the Product: ";
            cin >> n;
            cout << "\n\t\t New Price: ";
            cin >> p;
            cout << "\n\t\t New Discount: ";
            cin >> d;

            data1 << " " << c << " " << n << " " << p << " " << d << "\n";
            cout << "\n\n\t\t Record Updated!";
            tokens++;
        } else {
            data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
        }
        data >> pcode >> pname >> price >> dis;
    }

    data.close();
    data1.close();

    remove("database.txt");
    rename("database1.txt", "database.txt");

    if (tokens == 0) {
        cout << "\n\n Record Not Found!";
    }
}

void shopping::recepit() {
    fstream data;
    int arrc[100], arrq[100];
    int c = 0;
    float amount = 0, disc = 0, total = 0;
    char choice;

    cout << "\n\n\n\t\t\t RECEIPT ";
    list();
    cout << "\n__________________________________\n";
    cout << "     Please Place Your Order         \n";
    cout << "__________________________________\n";

    do {
        cout << "\nEnter the Product Code: ";
        cin >> arrc[c];
        cout << "Enter the Product Quantity: ";
        cin >> arrq[c];
        c++;
        cout << "Do you want to buy another product? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "\n\n\t\t\t_______________RECEIPT_______________\n";
    cout << "Product No\tProduct Name\tQuantity\tPrice\tAmount\tDiscounted Amount\n";

    for (int i = 0; i < c; i++) {
        data.open("database.txt", ios::in);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof()) {
            if (pcode == arrc[i]) {
                amount = price * arrq[i];
                disc = amount - (amount * dis / 100);
                total += disc;
                cout << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t" << amount << "\t" << disc << "\n";
                recommendProducts(pname);
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
    }
    cout << "\nTotal Amount: " << total << "\n";
    feedback();
}


int main() {
    shopping s;
    s.menu();
    return 0;
}
