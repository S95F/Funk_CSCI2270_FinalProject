#ifndef FANALYSIS_H
#define FANALYSIS_H
#include <string>
#include <queue>
using namespace std;
struct words{
    int frequency; //how often the word is seen
    string word;
    words *l;
    words *r;
    words *p;
    bool isRed;
    void setNode(string w, words *left, words *right, words *parent){
        frequency = 1;
        word = w;
        l = right;
        r = left;
        p = parent;
        isRed = true;
    }
};

class fanalysis{
private:
    words *root; //root of red/black
    words *nill;
    string fileName;
    int n_of_total_words;
    void insertWord(string word);
    void deleteAll(words*);
    void rbAddFixup(words*);
    void leftRotate(words*);
    void rightRotate(words*);
    void rbTransplant(words *u, words *v);
    void print(words*);
    words *findNode(string word);
    void carr(words*, words *, int);
public:
    virtual ~fanalysis();

    fanalysis(string f_name); // initializes file analysis
    words* frequent_words(int ); // finds the int most frequent words
    int getTotal_num_words(); // returns total number of words
    void removePunc(); // removes punctuation
    void capitalize(bool); // either makes everything capitalize, true, or uncapitalize everything, false
    void replaceWrd(string,string); // replaces one string by the other
    void shift_all_words(int); //shifts all the chars by the int
    void backwords_words(); // makes all the words backwards
    int frequencyofword(string); // returns frequency of word
    words * listallwords();



};

#endif // FANALYSIS_H
