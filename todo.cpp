#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <experimental/filesystem>
#include <unistd.h>
#include <ncurses.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

using namespace std;
namespace fs = std::experimental::filesystem;

string path = "Your Desired Todo Item Dir Here!";

void editItem() {
    for (const auto & entry : fs::directory_iterator(path))
            cout << entry.path() << "\n\n";
    string editItem;
    cout << "Desired item to edit: ";
    cin >> editItem;
    editItem = "$EDITOR " + path + editItem;
    system(editItem.c_str());
    return;
}

void delItem() {    
    string itemDeletion;
    if (bool emptyDir = fs::is_empty(path) == 1) {
        cout << "No more items to delete!\n"; 
        sleep(1);
    } else {
        cout << "Deletable items:\n";
        for (const auto & entry : fs::directory_iterator(path))
            cout << entry.path() << "\n\n";
        cout << "Name of item for deletion: ";
        cin.ignore();
        getline(cin, itemDeletion);
        string delPath = path + itemDeletion;
        if (bool exist = fs::exists(delPath) == 0) {
            cout << RED << itemDeletion <<" could not be deleted (might not exist)\n\n" << RESET;
            sleep(1);
        } else {
            system(("rm "+delPath+"").c_str());
            cout << GREEN << "Deleted: " << delPath << RESET << "\n";
            sleep(2);
        }
    }
}

void emptyCheck() {
    if (bool emptyDir = fs::is_empty(path) == 1) {
        cout << RED << "Directory is empty!\n" << RESET; 
        sleep(1);
    } else {
        delItem();
    }
}

void makeItem() {
    string itemName;
    cout << "Todo Name: ";
    cin.ignore();
    getline(cin, itemName);
    string itemPath = path + itemName;
    if (bool exist = fs::exists(itemPath) == 1) {
        cout << RED << itemPath << " already exists!\n" << RESET;
        sleep(1);
    } else {
        ofstream item;
        item.open(itemPath.c_str(), ios::app);
        string itemTitle;
        string itemContent;
        cout << "Title: ";
        getline(cin, itemTitle);
        itemTitle += ":";
        item << itemTitle << endl;
        cout << "Contents: ";
        getline(cin, itemContent);
        item << itemContent << endl;
        item.close();
        cout << GREEN << "Created: " << itemPath << RESET << endl;
        sleep(2);
    }
}

void menu() {
    cout << CYAN << "Current Todo Items:\n";
    cout << YELLOW << "\n";
    bool emptyDir = fs::is_empty(path);
    if (emptyDir == 0) {
        system(("find "+path+" -type f -print0 | xargs -0 tail -n +1").c_str());
            
    } else if (emptyDir == 1) { 
        cout << RED << "Nothing Todo!\n" << RESET;
    }
    cout << GREEN << "\nm" << RESET << ": Make a new todo item \n"
    << RED << "d" << RESET << ": Delete a todo item \n"
    << BLUE << "e" RESET << ": Edit a todo item\n" << RESET;
    int select;
    select = true;
    while (select == 1) {
        switch (getchar()) {
            case 'm': case 'M':
                select = false;
                makeItem();
                break;
            case 'd': case 'D':
                select = false;
                emptyCheck();
                break;
            case 'e': case 'E':
                select = false;
                editItem();
                break;
            default:
                cout << RED << "Enter [m] [d] [e]\n" << RESET;
                break;
        }
    }
}

int main() {
        /*string execPath;
        execPath = "/home/narmis/programs/c++/todo/";
        fstream todoPath{execPath +"TODO_PATH.txt"}; // /home/narmis/programs/c++/todo/items/
        if (!todoPath) {
            cout << "Please enter (full) todo item storage path: ";
            string desiredPath;
            cin >> desiredPath;
            todoPath.open("TODO_PATH.txt", ios::app);
            todoPath << desiredPath;
            todoPath.close();
            path = desiredPath;
            menu();
        } else {
            menu();bl
        }*/
    while (true) {
        system("clear");
        menu();
    }
    return 0;
}
