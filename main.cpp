
#include <iostream>
#include <vector>
#include <string>
#include "bank_customer.h"
#include "buyer.h"

enum PrimaryPrompt{LOGIN, REGISTER, EXIT};
enum RegisterPrompt{CREATE_BUYER, CREATE_SELLER, BACK};
using namespace std;

struct Account {
    std::string username;
    std::string password;
    std::string name;
    std::string address;
    std::string phone;
    std::string email;
};

std::vector<Account> accounts;

int main() {
    PrimaryPrompt prompt = LOGIN;
    RegisterPrompt regPrompt = CREATE_BUYER;

    while (prompt != EXIT) {
        cout << "Select an option: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);
        switch (prompt) {
            /* if Login is selected, based on authority then provide options:
                assume user is logged in as Buyer for now
                1. Chek Account Status (will display if user is Buyer or Seller or both and linked banking account status)
                Will display Buyer, Seller and Banking Account details
                2. Upgrade Account to Seller
                Will prompt user to enter Seller details and create a Seller account linked to Buyer account
                Will reject if a user dont have a banking account linked
                3. Create Banking Account (if not already linked), will be replaced with banking functions
                Must provides: initial deposit amount, Address, Phone number, Email
                Banking functions will provides: Balance checking, Transaction History, Deposit, Withdraw
                4. Browse Store Functionality
                Will display all stores initially
                Need to select a store to browse each store inventory
                Will display all items in the store inventory
                After selecting an item, will display item details and option to add to cart
                After adding to cart, will notify user item is added to cart
                5. Order Functionality
                Will display all items in cart
                Will provide option to remove item from cart
                Will provide option to checkout
                After checkout invoide will be generated (will go to payment functionality)
                6. Payment Functionality
                Will display all listed invoices
                Pick an invoice to pay
                Will display invoice details and total amount
                Will provide option to pay invoice
                Payment is done through confirmation dialogue
                In confirmation dialogue, will display account balance as precursor
                User will need to manually enter invoice id to pay
                After paying balance will be redacted from buyer and added to the responding seller account
                After payment, order status will be changed to paid
                7. Logout (return to main menu)
                Display confirmation dialogue
                If confirmed, return to main menu
                If not, return to Buyer menu
                8. Delete Account (remove both Buyer and Seller account and relevant banking account)
                Display confirmation dialogue
                If confirmed, delete account and return to main menu
                If not, return to Buyer menu

                assume user is logged in as Seller for now
                9. Check Inventory
                10. Add Item to Inventory
                11. Remove Item from Inventory
                12. View Orders (will display all orders placed to this seller
                Only orders with paid status will be listed
                Order details will listing items, quantity, total amount, buyer details, order status (paid, cancelled, completed)
                extra functions
                9. Exit to main Menu
                10. Exit Program
                **/
            case LOGIN: {
                cout << "Login selected." << endl;
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                bool found = false;
                Account loggedInAccount;
                for (const auto& acc : accounts) {
                    if (acc.username == username && acc.password == password) {
                        found = true;
                        loggedInAccount = acc;
                        break;
                    }
                }
                if (found) {
                    cout << "Login successful!" << endl;
                    bool loggedIn = true;
                    bool isSeller = false;
                    string sellerName = "";
                    int sellerId = 0;
                    while (loggedIn) {
                        cout << "\nBuyer Menu:" << endl;
                        cout << "1. Check Account Status" << endl;
                        cout << "2. Upgrade Account to Seller" << endl;
                        cout << "3. Logout" << endl;
                        int buyerChoice;
                        cin >> buyerChoice;
                        switch (buyerChoice) {
                            case 1:
                                cout << "\n--- Account Status ---" << endl;
                                cout << "Account Type: ";
                                if (isSeller) {
                                    cout << "Buyer & Seller" << endl;
                                } else {
                                    cout << "Buyer only" << endl;
                                }
                                cout << "\nBuyer Details:" << endl;
                                cout << "Name: " << loggedInAccount.name << endl;
                                cout << "Username: " << loggedInAccount.username << endl;
                                cout << "Address: " << loggedInAccount.address << endl;
                                cout << "Phone: " << loggedInAccount.phone << endl;
                                cout << "Email: " << loggedInAccount.email << endl;
                                cout << "\nBanking Account Details:" << endl;
                                cout << "(Demo) Balance: $1000" << endl;
                                if (isSeller) {
                                    cout << "\nSeller Details:" << endl;
                                    cout << "Store Name: " << sellerName << endl;
                                    cout << "Seller ID: " << sellerId << endl;
                                }
                                cout << "----------------------\n" << endl;
                                break;
                            case 2:
                                if (!isSeller) {
                                    cout << "Enter Seller ID: ";
                                    cin >> sellerId;
                                    cout << "Enter Store Name: ";
                                    cin.ignore();
                                    getline(cin, sellerName);
                                    isSeller = true;
                                    cout << "Seller account created and linked!" << endl;
                                } else {
                                    cout << "Already a Seller." << endl;
                                }
                                break;
                            case 3:
                                cout << "Logging out..." << endl;
                                loggedIn = false;
                                break;
                            default:
                                cout << "Invalid option." << endl;
                                break;
                        }
                    }
                } else {
                    cout << "Login failed. Invalid username or password." << endl;
                }
                break;
            }
            case REGISTER: {
                regPrompt = CREATE_BUYER;
                while (regPrompt != BACK){
                    cout << "Register selected. " << endl;
                    cout << "Select an option: " << endl;
                    cout << "1. Create Buyer Account" << endl;
                    cout << "2. Create Seller Account" << endl;
                    cout << "3. Back" << endl;
                    int regChoice;
                    cin >> regChoice;
                    regPrompt = static_cast<RegisterPrompt>(regChoice - 1);
                    switch (regPrompt) {
                        case CREATE_BUYER: {
                            cout << "Create Buyer Account selected." << endl;
                            Account newAcc;
                            cout << "Enter username: ";
                            cin >> newAcc.username;
                            cout << "Enter password: ";
                            cin >> newAcc.password;
                            cin.ignore();
                            cout << "Enter Name: ";
                            getline(cin, newAcc.name);
                            cout << "Enter Home Address: ";
                            getline(cin, newAcc.address);
                            cout << "Enter Phone Number: ";
                            getline(cin, newAcc.phone);
                            cout << "Enter Email: ";
                            getline(cin, newAcc.email);
                            accounts.push_back(newAcc);
                            cout << "\nBuyer Account Created and Saved!" << endl;
                            break;
                        }
                        case CREATE_SELLER: {
                            cout << "Create Seller Account selected. (Feature not implemented)" << endl;
                            break;
                        }
                        case BACK: {
                            cout << "Back selected." << endl;
                            break;
                        }
                        default: {
                            cout << "Invalid option." << endl;
                            break;
                        }
                    }
                }
                break;
            }
            case EXIT: {
                cout << "Exiting." << endl;
                break;
            }
            default: {
                cout << "Invalid option." << endl;
                break;
            }
        }
        cout << endl;
    }

    //BankCustomer customer1(1, "Alice", 1000.0);
    //Buyer buyer1(1, customer1.getName(), customer1);
    return 1;
}
