#include <iostream>
#include "fanalysis.h"

using namespace std;

int main()
{
    //Initialize
    fanalysis edit  = fanalysis("Hemingway_edit.txt");
     int input;
     while(input != 10)
    {
        cout << "Main Menu" << endl;
        cout << "===========================================" << endl;
		cout << "1. Print All Words" << endl;
		cout << "2. List of Frequent Words" << endl;
        cout << "3. Total Number of Words" << endl;
        cout << "4. Remove Punctuation" << endl;
        cout << "5. Capitalize All  Words" << endl;
        cout << "6. Swap Words" << endl;
		cout << "7. Shift ASCII Value of Words" << endl;
		cout << "8. Reverse All Words" << endl;
		cout << "9. Word Frequency" << endl;
		cout << "10. Quit Program" << endl;

		cin >> input;
        //clear out cin
        cin.clear();
        cin.ignore(10000,'\n');

        switch (input)
        {
            //Print All Words
            case 1:
                edit.listallwords();
                break;

            //Frequent Words
            case 2:
                int numWords;
                cout << " Enter the number of the most frequent words you want:" << endl;
                cin >> numWords;
                edit.frequent_words(numWords);
                break;

            //Total number of words
            case 3:
                edit.getTotal_num_words();
                break;

            //Remove Punctuation
            case 4:
                edit.removePunc();
                break;

            //Capitalize all Words
            case 5:
                {
                    bool cap = false;
                    edit.capitalize(cap);
                    break;
                }

            //Swap Words
            case 6:
                {
                    string word1;
                    string word2;
                    cout << "Enter a word you want to replace:" << endl;
                    cin >> word1;
                    cout << "Enter the replacement word:" << endl;
                    cin >> word2;
                    edit.replaceWrd( word1,  word2);
                    break;
                }

            //Ascii Shift Words
            case 7:
                {
                    int shift;
                    cout << "Enter in how many ascii characters you would like to shift over: " << endl;
                    cin >> shift;
                    edit.shift_all_words(shift);
                     break;
                }

            //Reverse All Words
            case 8:
                edit.backwords_words();
                break;

            //Word Frequency
            case 9:
                {
                    string freqWord;
                    int freqNumber;
                    cout << "Enter a word you would like the frequency of: " << endl;
                    cin >> freqWord;
                    freqNumber = edit.frequencyofword(freqWord);
                    cout << freqWord << ": " << freqNumber << endl;
                      break;
                }

            //Quit Program
            case 10:
                cout << "Goodbye!" << endl;
                break;

            default:
                cout << "Invalid Input" << endl;
                cin.clear();
                cin.ignore(10000,'\n');
                break;
        }
    }
}
