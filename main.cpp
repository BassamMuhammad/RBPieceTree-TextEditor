#include <iostream>
#include <cstddef>
#include <vector>
#include "rb_piece_tree.hpp"
using namespace std;
//when column is 2 we will delete text at 1 and enter text at 2
int main() {
    RBPieceTree *node = new RBPieceTree();
    int command = 0;
    int col_index;
    string line;
    while (true) {
        cout << "<<<<<<<<<<<TEXT EDITOR COMMANDS>>>>>>>>>>>>" << endl;
        cout << "1. Insert Text into File " << endl;
        cout << "2. Delete a Letter at Specified Index " << endl;
        cout << "3. Insert a Letter at Specified Index" << endl;
        cout << "4. Show the written Text" << endl;
        cout << "5. Exit the Editor." << endl;
        cin >> command;
        if (command == 1) {
            cout << "Start Typing your text.." << endl;
            getline(cin, line);
            getline(cin, line);
            node->insertText(line);
        } else if (command == 2) {
            cout << "Enter the column where text to be deleted: ";
            cin >> col_index;
            node->deleteLetter(col_index + 1);
        } else if (command == 3) {
            cout << "Enter the column where text to be inserted: ";
            cin >> col_index;

            cout << "Enter the word to be inserted: ";
            getline(cin, line);
            getline(cin, line);
            node->updateText(line, col_index);
        } else if (command == 4) {
            cout << "Text in the File is: \n";
            string text = node->getText();
            cout << text<<endl;
        } else if (command == 5) {
            delete node;
            return 0;
        } else {
            cout << "Choose Correct Command!" << endl;
        }
    }
}
