#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <fstream>
#include <limits>
#include <algorithm>
using namespace std;

void clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

struct User
{
    string username, password, mobile, address, email;
    bool isAdmin;
    int failedLoginAttempts;
    bool isLocked;
};

struct Product
{
    int id;
    string name;
    double price;
    int stock;
    string category;
    int sold = 0;
};

struct CartItem
{
    Product product;
    int quantity;
};

vector<User> users;
vector<Product> products;
vector<CartItem> cart;
map<string, double> coupons = {{"DISCOUNT10", 0.10}, {"SALE20", 0.20}};
User *currentUser = nullptr;
int productIdCounter = 1;
double totalSales = 0;

string adminPhone = "01300000000";
string adminPassword = "admin123";

void pause()
{
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void registerUser()
{
    clear();
    string uname, pass, mobile, address, email, confirmPass;
    cout << "Customer Registration\n";
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, uname);

    cout << "Enter mobile Number: ";
    cin >> mobile;
    while (mobile.length() != 11)
    {
        cout << "Mobile number must be exactly 11 digits. Re-enter: ";
        cin >> mobile;
    }

    cin.ignore();
    cout << "Enter address: ";
    getline(cin, address);

    // Email validation
    do
    {
        cout << "Enter email: ";
        getline(cin, email);
        if (email.find('@') == string::npos || email.find(".com") == string::npos)
        {
            cout << "Invalid email. Email must contain '@' and '.com'. Please try again.\n";
        }
    } while (email.find('@') == string::npos || email.find(".com") == string::npos);

    cout << "Enter password: ";
    cin >> pass;
    while (true)
    {
        cout << "Confirm password: ";
        cin >> confirmPass;
        if (pass == confirmPass)
        {
            break; // Passwords match, exit the loop
        }
        else
        {
            cout << "Passwords do not match. Please re-enter the password.\n";
        }
    }

    users.push_back({uname, pass, mobile, address, email, false, 0, false});
    cout << "Registration successful!\n";
}

bool loginUser()
{
    clear();
    string phnOrEmail, pass;

    cout << "********** Login **********\n";
    cout << "Enter phone number or email: ";
    cin >> phnOrEmail;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto &u : users)
    {
        if ((u.mobile == phnOrEmail || u.email == phnOrEmail))
        {
            if (u.isLocked)
            {
                cout << "Your account is locked due to multiple failed login attempts.\n";
                pause();
                return false;
            }

            for (int i = 1; i <= 3; ++i)
            {
                cout << "\nEnter password: ";
                cin >> pass;

                if (u.password == pass)
                {
                    currentUser = &u;
                    clear();
                    cout << "********** Welcome **********\n";
                    cout << "Login successful! Welcome, " << u.username << "!\n";
                    pause();
                    return true;
                }
                else
                {
                    cout << "\nIncorrect password! Try with valid password. \nAttempt " << i << " of 3.\n";
                }
            }

            u.failedLoginAttempts = 3;
            u.isLocked = true;
            cout << "\nYour account is locked due to Multiple attempts.\n";

            return false;
        }
    }

    cout << "Account not found.\n";

    return false;
}

bool adminLogin()
{
    clear();
    string phone, password;
    cout << "********** Admin Login **********\n";
    cout << "Enter phone number: ";
    cin >> phone;
    cout << "Enter password: ";
    cin >> password;

    return (phone == adminPhone && password == adminPassword);
}

void addProduct()
{
    clear();
    int n;
    cout << "How many products to add - ";
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        Product p;
        p.id = productIdCounter++;
        cout << "\nProduct " << i + 1 << ":\n";
        cout << "Name: ";
        cin >> p.name;
        cout << "Price: ";
        cin >> p.price;
        cout << "Stock: ";
        cin >> p.stock;
        cout << "Category: ";
        cin >> p.category;
        products.push_back(p);
        cout << "Product added!\n";
    }
}

void updateProduct()
{
    int id;
    clear();
    cout << "Enter Product ID to update: ";
    cin >> id;
    for (auto &p : products)
    {
        if (p.id == id)
        {
            cout << "New Price: ";
            cin >> p.price;
            cout << "New Stock: ";
            cin >> p.stock;
            cout << "Product updated!\n";
            return;
        }
    }
    cout << "Product not found.\n";
}

void deleteProduct()
{
    int id;
    clear();
    cout << "Enter Product ID to delete: ";
    cin >> id;
    for (auto it = products.begin(); it != products.end(); ++it)
    {
        if (it->id == id)
        {
            products.erase(it);
            cout << "Product deleted!\n";
            return;
        }
    }
    cout << "Product not found.\n";
}

void viewProducts()
{
    clear();
    cout << left << setw(5) << "ID" << setw(15) << "Name" << setw(10) << "Price" << setw(8) << "Stock" << "Category\n";
    for (auto &p : products)
    {
        cout << left << setw(5) << p.id << setw(15) << p.name << setw(10) << p.price << setw(8) << p.stock << p.category << endl;
    }
}

void addToCart()
{
    int id, qty;
    clear();
    viewProducts();
    cout << "Enter Product ID to add: ";
    cin >> id;
    for (auto &p : products)
    {
        if (p.id == id && p.stock > 0)
        {
            cout << "Enter quantity: ";
            cin >> qty;
            if (qty <= p.stock)
            {
                cart.push_back({p, qty});
                cout << "Added to cart!\n";
                return;
            }
            else
            {
                cout << "Insufficient stock.\n";
                return;
            }
        }
    }
    cout << "Product not found.\n";
}

void viewCart()
{
    clear();
    double total = 0;
    cout << "********** Your Cart **********\n";
    for (auto &item : cart)
    {
        double subtotal = item.product.price * item.quantity;
        cout << item.product.name << " x " << item.quantity << " = " << subtotal << endl;
        total += subtotal;
    }
    cout << "Total: " << total << endl;
}

void removeFromCart()
{
    clear();
    if (cart.empty())
    {
        cout << "\U0001F6D2 Your cart is empty!\n";
        return;
    }

    cout << "********** Your Cart **********\n";
    for (int i = 0; i < cart.size(); ++i)
    {
        cout << i + 1 << ". " << cart[i].product.name
             << " x " << cart[i].quantity
             << " = " << cart[i].product.price * cart[i].quantity << endl;
    }

    int index;
    cout << "\nEnter the item number to remove from cart: ";
    cin >> index;

    if (index < 1 || index > cart.size())
    {
        cout << "\u274C Invalid selection!\n";
    }
    else
    {
        cart.erase(cart.begin() + (index - 1));
        cout << "\u2705 Item removed from cart successfully.\n";
    }
}

void generateInvoice(double total, double discountPercent, const string &paymentMethod)
{
    ofstream file("invoice.txt");
    file << "************ Invoice ************\n";
    file << "Customer: " << currentUser->username << "\n";
    file << "Mobile: " << currentUser->mobile << "\n";
    file << "Address: " << currentUser->address << "\n";
    file << "Email: " << currentUser->email << "\n";
    file << "-------------------------------\n";
    for (auto &item : cart)
    {
        double subtotal = item.product.price * item.quantity;
        file << item.product.name << " x " << item.quantity << " = " << subtotal << "\n";
    }
    file << "-------------------------------\n";
    file << "Discount: " << (discountPercent * 100) << "%\n";
    file << "Payment Method: " << paymentMethod << "\n";
    file << "Total Payable: " << total << "\n";
    file << "********** Thank You ***********\n";
    file.close();
    cout << "Invoice generated: invoice.txt\n";
}

void placeOrder()
{
    clear();
    viewCart();
    string method, coupon;
    double discount = 0;
    cout << "Enter payment method (card/mobile): ";
    cin >> method;
    cout << "Have a coupon? Enter code or 'no': ";
    cin >> coupon;
    if (coupons.count(coupon))
    {
        discount = coupons[coupon];
        cout << "Coupon applied! " << (discount * 100) << "% off\n";
    }
    double total = 0;
    for (auto &item : cart)
    {
        total += item.product.price * item.quantity;
        for (auto &p : products)
        {
            if (p.id == item.product.id)
            {
                p.stock -= item.quantity;
                p.sold += item.quantity;
                break;
            }
        }
    }
    total -= total * discount;
    totalSales += total;
    generateInvoice(total, discount, method);
    cout << "Final total after discount: " << total << endl;
    cout << "Order placed successfully!\n";
    cart.clear();
}

void adminDashboard()
{
    clear();
    cout << "Admin Dashboard\n";
    cout << "Total Products: " << products.size() << endl;
    cout << "Total Sales: " << totalSales << endl;
    if (!products.empty())
    {
        auto mostSold = *max_element(products.begin(), products.end(), [](Product &a, Product &b)
                                     { return a.sold < b.sold; });
        cout << "Most Sold Product: " << mostSold.name << " (" << mostSold.sold << " sold)\n";
    }
}

void customerMenu()
{
    int ch;
    do
    {
        clear();
        cout << "******* Customer Menu *******\n";
        cout << "1. Browse Products\n2. Add to Cart\n3. View Cart\n4. Remove from Cart\n5. Place Order\n6. Logout\nChoice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            viewProducts();
            pause();
            break;
        case 2:
            addToCart();
            pause();
            break;
        case 3:
            viewCart();
            pause();
            break;
        case 4:
            removeFromCart();
            pause();
            break;
        case 5:
            placeOrder();
            pause();
            break;
        }
    } while (ch != 6);
}

void adminMenu()
{
    int ch;
    do
    {
        clear();
        cout << "******* Admin Menu *******\n";
        cout << "1. Add Product\n2. Update Product\n3. Delete Product\n4. View Products\n5. Dashboard\n6. Logout\nChoice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            addProduct();
            pause();
            break;
        case 2:
            updateProduct();
            pause();
            break;
        case 3:
            deleteProduct();
            pause();
            break;
        case 4:
            viewProducts();
            pause();
            break;
        case 5:
            adminDashboard();
            pause();
            break;
        }
    } while (ch != 6);
}

int main()
{
    users.push_back({"admin", "admin123", adminPhone, "Admin Address", "admin@example.com", true, 0, false});

    int choice;
    do
    {
        clear();
        system("color B");
        cout << "********** Welcome to E-Commerce System **********\n";
        cout << "1. Customer Register\n2. Customer Login\n3. Admin Login\n4. Exit\nChoice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            registerUser();
            pause();
            break;
        case 2:
            if (loginUser())
            {
                if (currentUser->isAdmin)
                    adminMenu();
                else
                    customerMenu();
            }
            else
            {
                pause();
            }
            break;
        case 3:
            if (adminLogin())
            {
                adminMenu();
            }
            else
            {
                cout << "Invalid admin login!\n";
                pause();
            }
            break;
        }
    } while (choice != 4);
    return 0;
}