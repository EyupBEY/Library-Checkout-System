#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

void LoadCatalog(string isbn[], string names[], double prices[], double availableInStore[], double vowelCountInTitle[], const int & MAX_Books);
int Menu();
void AddBookToTheCart(const string isbn[], const string names[], const double prices[], double availableInStore[], double quantities[], const int & MAX_Books);
void EditBooksQuantityInTheCart(const string isbn[], const double prices[], double availableInStore[], double quantities[], const int & MAX_Books);
void DeleteBooksFromTheCart(const string isbn[], const double prices[], double availableInStore[], double quantities[], const int & MAX_Books);
void DisplayCart(const string isbn[], const string names[], const double prices[], const double quantities[], const int & MAX_Books);
void Exit(double prices[], double quantities[], const int & MAX_Books, const double & SERVICE_FEE);

int main() {
    cout.setf(ios::fixed);
    cout << setprecision(2);
    string EorC;
    const int MAX_Books = 50;
    const double SERVICE_FEE = 4.99;
    string isbn[MAX_Books];
    string names[MAX_Books];
    double prices[MAX_Books];
    double availableInStore[MAX_Books];
    double vowelCountInTitle[MAX_Books];
    double quantities[MAX_Books];
    
    for (int i = 0; i < MAX_Books;i++) {
        isbn[i] = "";
        names[i] = "";
        prices[i] = 0.00;
        vowelCountInTitle[i] = 0.00;
        availableInStore[i] = 0.00;
        quantities[i] = 0.00;
    }

    cout << "Welcome to the Library Checkout System!" << endl;
    
    LoadCatalog(isbn, names, prices, availableInStore, vowelCountInTitle, MAX_Books);
    
    while (true) {
        int choice = Menu();
        if (choice == 1)
            AddBookToTheCart(isbn, names, prices, availableInStore, quantities, MAX_Books);
        else if (choice == 2)
            EditBooksQuantityInTheCart(isbn, prices, availableInStore, quantities, MAX_Books);
        else if (choice == 3)
            DeleteBooksFromTheCart(isbn, prices, availableInStore, quantities, MAX_Books);
        else if (choice == 4) {
            DisplayCart(isbn, names, prices, quantities, MAX_Books);
            cout << "Do you want to exit (checkout) or continue? Enter E to exit, or any other key to continue:" << endl;
            cin >> EorC;
            if (EorC == "E") {
                Exit(prices, quantities, MAX_Books, SERVICE_FEE);
                break;
            } else
                cout << "Continuing..." << endl;
        } else if (choice == 5) {
            Exit(prices, quantities, MAX_Books, SERVICE_FEE);
            break;
        } else
            cout << "Invalid input." << endl;
    }
    
    return 0;
}

void LoadCatalog(string isbn[], string names[], double prices[], double availableInStore[], double vowelCountInTitle[], const int & MAX_Books) {
    // precondition: Format of each line of the input stream file: ISBN,Title,Price,Quantity,...
    // post: Saves the input stream file data to arrays. 
    int i = 0;
    string filename, line;
    ifstream input;
    cout << "Enter the name of the file containing books data:" << endl;
    do {
        cin >> filename;
        input.open(filename.c_str());
        if (input.fail()) cout << "Error: Unable to open file " << filename << endl << "Please re-enter a valid filename." << endl;
    } while (input.fail());
    while(getline(input, line)) {
        int start, end;
        start = 0;
        end = line.find(",");
        isbn[i] = line.substr(start, end-start);
        start = end + 1;
        end = line.find(",", start);
        names[i] = line.substr(start, end-start);
        start = end + 1;
        end = line.find(",", start);
        prices[i] = stod(line.substr(start, end-start));
        start = end + 1;
        end = line.find(",", start);
        if (end == -1) availableInStore[i] = stod(line.substr(start));
        else availableInStore[i] = stod(line.substr(start, end-start));
        for (long unsigned int j = 0; j < names[i].length(); j++)
            if (names[i][j] == 'a' || names[i][j] == 'e' || names[i][j] == 'i' || names[i][j] == 'o' || names[i][j] == 'u' || names[i][j] == 'A' || names[i][j] == 'E' || names[i][j] == 'I' || names[i][j] == 'O' || names[i][j] == 'U')
                vowelCountInTitle[i]++;
        i++;
    }
    cout << endl << "=== Catalog Loaded ===" << endl;
    for (int j = 0; j < i; j++)
        cout << "ISBN: " << isbn[j] << " | " << "Title: " << names[j] << " | " << "Price: $" << prices[j] << " | " << "Available Quantity: " << availableInStore[j] << " | " << "Vowels in Title: " << vowelCountInTitle[j] << endl;
    cout << "======================" << endl;
}

int Menu() {
    // post: Returns the intended task's int value.
    int choice;
    string dummyS;
    cout << endl <<
    "Menu" << endl <<
    "1. Add Book to the Cart" << endl <<
    "2. Edit Book's Quantity in the Cart" << endl <<
    "3. Delete Books from the Cart" << endl <<
    "4. Display Cart" << endl <<
    "5. Exit" << endl;
    cout << "Enter your choice:" << endl;
    if (!(cin >> choice)) {
        cin.clear();
        cin >> dummyS;
        return -1;
    }
    return choice;
}

void AddBookToTheCart(const string isbn[], const string names[], const double prices[], double availableInStore[], double quantities[], const int & MAX_Books) {
    int i;
    string isbn_in;
    double quantity_in;
    bool found = false;
    cout << "Enter ISBN no:" << endl;
    cin >> isbn_in;
    for (i = 0; i < MAX_Books;i++)
        if (isbn_in == isbn[i]) {
            found = true;
            break;
        }
    if (!found)
        cout << "The Book with this ISBN no is not found in the Catalog." << endl;
    else {
        cout << "Enter quantity to add:" << endl;
        cin >> quantity_in;
        if (availableInStore[i] >= quantity_in) {
            availableInStore[i] -= quantity_in;
            quantities[i] += quantity_in;
            cout << "Added " << quantity_in << " copies of \"" << names[i] << "\"." << endl;
        } else cout << "Only " << availableInStore[i] << " available." << endl;
    }
}

void EditBooksQuantityInTheCart(const string isbn[], const double prices[], double availableInStore[], double quantities[], const int & MAX_Books) {
    string isbn_in;
    bool found = false;
    int i, newQuantity;
    for (i = 0; i < MAX_Books;i++)
        if (quantities[i]) {
            found = true;
            break;
        }
    if (found) {
        cout << "Enter ISBN no:" << endl;
        cin >> isbn_in;
        for (int j = 0; j < MAX_Books;j++)
            if (isbn[j] == isbn_in) {
                int total = availableInStore[j] + quantities[j];
                cout << "Current quantity in Cart: " << quantities[j] << endl;
                cout << "Remaining in store (not in your cart yet): " << availableInStore[j] << endl;
                cout << "Enter new quantity (>= 0):" << endl;
                cin >> newQuantity;
                if (newQuantity <= total) {
                    availableInStore[j] = total - newQuantity;
                    quantities[j] = newQuantity;
                    cout << "Quantity updated." << endl;
                } else cout << "Only " << availableInStore[j] + quantities[j] << " available in total (store + cart)." << endl;
            }
    } else cout << "Cart is empty. Nothing to edit." << endl;
}

void DeleteBooksFromTheCart(const string isbn[], const double prices[], double availableInStore[], double quantities[], const int & MAX_Books) {
    string isbn_in;
    bool empty = true;
    for (int i = 0; i < MAX_Books;i++)
        if (quantities[i] > 0)
            empty = false;
    if (empty)
        cout << "Cart is empty. Nothing to delete." << endl;
    else {
        cout << "Enter ISBN no:" << endl;
        cin >> isbn_in;
        for (int i = 0; i < MAX_Books;i++)
            if (isbn[i] == isbn_in) {
                if (quantities[i] <= 0) {
                    cout << "There is no such a book with this ISBN in your cart." << endl;
                    break;
                }
                availableInStore[i] += quantities[i];
                quantities[i] = 0;
                cout << "Item removed from cart." << endl;
                break;
            }
    }
}

void DisplayCart(const string isbn[], const string names[], const double prices[], const double quantities[], const int & MAX_Books) {
    int order = 1;
    bool empty = true;
    for (int i = 0; i < MAX_Books; i++)
        if (quantities[i] > 0)
            empty = false;
    if (empty)
        cout << "Cart is empty." << endl;
    else {
        cout << "Cart (Items Added):" << endl;
        for (int i = 0; i < MAX_Books; i++)
            if (quantities[i] > 0)
                cout << order++ << ". ISBN: " << isbn[i] << " | " << names[i] << "  " << quantities[i] << " x $" << prices[i] << " = $" << quantities[i] * prices[i] << endl;
    }
}

void Exit(double prices[], double quantities[], const int & MAX_Books, const double & SERVICE_FEE) {
    // post: Outputs the Subtotal, Service Fee, and Total Price.
    double subtotal = 0.00;
    for (int i = 0; i < MAX_Books; i++)
        if (quantities[i] > 0.00)
            subtotal += prices[i] * quantities[i];
    cout << "Subtotal: $" << subtotal << endl;
    cout << "Service fee: $" << SERVICE_FEE * bool(subtotal) << endl;
    cout << "Total price: $" << (subtotal + SERVICE_FEE) * bool(subtotal) << endl;
    cout << "Goodbye!" << endl;
}
