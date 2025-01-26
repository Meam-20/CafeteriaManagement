#include<bits/stdc++.h>
using namespace std;
class Cafeteria
{
private:
    struct MenuItem
    {
        int id;
        string name;
        double price;
    };

    MenuItem menu[10] =
    {
        {1,"Burger",80},
        {2,"Pizza",200},
        {3,"Coffee",100},
        {4,"Sandwich",90},
        {5,"Soda",25},
        {6,"Fried Rice",180},
        {7,"Pasta",150},
        {8,"Noodles",100},
        {9,"Soup",80},
       {10,"Momo",70}


    };

    string orderFile = "CAFE.data";
    const string adminPassword = "cafe@123";
public:
    void displayMenu()
    {
        cout << "\n------ Cafeteria Menu ------" << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << menu[i].id << ". " << menu[i].name << "-TK" << menu[i].price<<endl;
        }
        cout << "----------------------------\n" << endl;
    }

    string getCurrentDateTime()
    {
        time_t now = time(0);
        tm *localTime = localtime(&now);
        int day = localTime->tm_mday;
        int month = localTime->tm_mon + 1;
        int year = localTime->tm_year + 1900;
        int hour = localTime->tm_hour;
        int min = localTime->tm_min;
        int sec = localTime->tm_sec;

        return to_string(day) + "/" + to_string(month) + "/" + to_string(year) + " " +
               to_string(hour) + ":" + to_string(min) + ":" + to_string(sec);
    }

    void takeOrder()
    {
        int choice, quantity;
        double total = 0;
        char more;
        ofstream orderOut;
        orderOut.open("CAFE.data",ios::app);

        if(!orderOut)
        {
            cout<<"Error: Unable to open file for writing!" << endl;
            return;
        }

        cout << "\n------ Customer Order ------" << endl;

        do
        {

            while (true)
            {
                cout <<"Enter the item ID you want to order:";
                cin >>choice;


                if (cin.fail()||choice<1||choice>10)
                {
                    cout<<"Invalid input! Please enter a valid item number from the menu.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                {
                    break;
                }
            }
            while (true)
            {
                cout << "Enter quantity for " << menu[choice - 1].name << ": ";
                cin >> quantity;

                if (cin.fail() || quantity <= 0)
                {
                    cout << "Invalid quantity!Please enter a positive number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                {
                    break;
                }
            }

            double itemTotal = menu[choice - 1].price * quantity;
            total += itemTotal;


            orderOut << menu[choice - 1].name << " x" << quantity << " = TK" << itemTotal << endl;

            cout << "Item added to your order. Current total: TK" << total << endl;

            cout << "Do you want to order another item? (y/n): ";
            cin >> more;

        }
        while (more=='y' || more=='Y');


        orderOut<<"Total: TK" << total<<endl;
        orderOut<<"----------------------------"<<endl;

        cout<<"Your total bill is: TK" << total << endl;
        cout<<"Thank you for ordering. Enjoy your meal!"<<endl;

        orderOut.close();
    }

    void viewAllOrders()
    {
        string password;
        cout << "\nEnter Admin Password: ";
        cin >> password;

        if(password!=adminPassword)
        {
            cout << "Access Denied! Incorrect password.\n";
            return;
        }

        ifstream orderIn(orderFile);
        if(!orderIn)
        {
            cout<<"Error: Unable to open file or no orders yet!"<<endl;
            return;
        }

        string line;
        cout<<"\n------ All Orders ------"<<endl;

        while (getline(orderIn, line))
        {
            cout << line << endl;
        }

        orderIn.close();
    }
};

int main()
{
    Cafeteria cafe;
    int choice;

    while (true)
    {
        cout<<"\n------Cafeteria Management------"<<endl;
        cout<<"1. View Menu"<<endl;
        cout<<"2. Place order"<<endl;
        cout<<"3. Admin : View All Orders"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Enter your choice:";
        cin>>choice;


        switch(choice)
        {
        case 1:
            cafe.displayMenu();
            break;
        case 2:
            cafe.takeOrder();
            break;
        case 3:
            cafe.viewAllOrders();
            break;
        case 4:
            cout<<"Thank you for using the Cafeteria Oder Management System!"<<endl;
            return 0;
        default:
            cout<<"Invalid choice.Please try again."<<endl;
        }
    }

    return 0;
}





