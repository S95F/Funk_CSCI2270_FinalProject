#include <iostream>
#include <stdlib.h>
#include "fanalysis.h"

using namespace std;

int main()
{
    bool quit = false;

    string input;
    cout << "Word Analysis" << endl;
    cout << "Please enter a text file name (inputing 'default' uses file that came with this):";
    getline(cin,input);
    if(input == "default"){
        input = "test.txt";
    }
    fanalysis edit(input);
    while(!quit and edit.get_open()){
        cout << "Menu:" << endl
        << "1. Frequent words" << endl
        << "2. Get total number of words" << endl
        << "3. Remove punctuation" << endl
        << "4. Capitlization" << endl
        << "5. Replace word" << endl
        << "6. Shift ASCII values" << endl
        << "7. Make all words backwards" << endl
        << "8. Get frequency of word" << endl
        << "9. List words" << endl
        << "10. quit" << endl;
        getline(cin,input);
        if(input == "1"){
            cout << "How big do you want the list:";
            getline(cin, input);
            words *frqnt_words = edit.frequent_words(atoi(input.c_str()));
            cout << atoi(input.c_str()) << endl;
            if(frqnt_words != NULL){
                for(int i = 0; i < atoi(input.c_str()); i++){
                    cout << frqnt_words[i].word << endl;
                }
            }
            input = "";
        }
        if(input == "2"){
            cout << edit.getTotal_num_words() << endl;
        }
        if(input == "3"){
            edit.removePunc();
            cout << "Punctuation removed" << endl;
        }
        if(input == "4"){
            cout << "Would you like to make it all caps or all lowercase (true for caps, false for lowercase):";
            getline(cin,input);
            if(input == "true"){
                edit.capitalize(true);
            }
            if(input == "false"){
                edit.capitalize(false);
            }
        }
        if(input == "5"){
            string replace;
            cout << "What word would you like to replace:";
            getline(cin,input);
            cout << "What word would you like to replace it with:";
            getline(cin,replace);
            edit.replaceWrd(input,replace);
        }
        if(input == "6"){
            cout << "How much would you like to shift the ASCII values:";
            getline(cin,input);
            edit.shift_all_words(atoi(input.c_str()));
            cout << "Values shifted" << endl;
        }
        if(input == "7"){
            edit.backwords_words();
            cout << "The words are now backwards" << endl;
        }
        if(input == "8"){
            cout << "Which word would you like to know the frequency of:";
            getline(cin,input);
            cout << "Frequency of " << input << " is " << edit.frequencyofword(input) << "." << endl;
        }
        if(input == "9"){
            words *allwords = edit.listallwords();
            int totWords = edit.getTotal_num_words();
            for(int i = 0; i < totWords; i++){
                cout << allwords[i].word << endl;
            }
        }
        if(input == "10"){
            quit = true;
        }
    }
    return 0;

}
