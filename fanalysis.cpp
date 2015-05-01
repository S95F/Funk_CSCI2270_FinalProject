#include "fanalysis.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
using namespace std;
fanalysis::~fanalysis(){
    if(root != nill){
        deleteAll(root);
    }
    delete nill;
}

void fanalysis::deleteAll(words *node){
    if(node->l != nill){
        deleteAll(node->l);
    }
    if(node->r != nill){
        deleteAll(node->r);
    }
    delete node;
}

bool fanalysis::get_open(){
    return open;
}

void fanalysis::rbAddFixup(words *x){
    /* restore the red-black property */
    while((x != root) && (x->p->isRed)){
       if(x->p == x->p->p->l) {
           /* If x's parent is a left, y is x's right 'uncle' */
           words *y = x->p->p->r;

           if(y->isRed){
              /* case 1 - change the colors */
              x->p->isRed = false;
              y->isRed = false;
              x->p->p->isRed = true;
              /* Move x up the tree */
              x = x->p->p;
          }
          else{
              /* y is a black node */
              if ( x == x->p->r) {
                  /* and x is to the right */
                  /* case 2 - move x up and rotate */
                  x = x->p;
                  leftRotate(x);
              }
              /* case 3 */
              x->p->isRed = false;
              x->p->p->isRed = true;
              rightRotate(x->p->p);
          }
      }
      else {
          /* repeat the "if" part with right and left exchanged */
        /* If x's parent is a left, y is x's left 'uncle' */
           words *y = x->p->p->l;
           if(y->isRed){
              /* case 1 - change the colors */
              x->p->isRed = false;
              y->isRed = false;
              x->p->p->isRed = true;
              /* Move x up the tree */
              x = x->p->p;
          }
          else{
              /* y is a black node */
              if(x == x->p->l){
                  /* and x is to the left */
                  /* case 2 - move x up and rotate */
                  x = x->p;
                  rightRotate(x);
              }
              /* case 3 */
              x->p->isRed = false;
              x->p->p->isRed = true;
              leftRotate(x->p->p);
          }
      }
  }
  /* Color the root black */
  root->isRed = false;
}

void fanalysis::rbTransplant(words *u, words *v){
    // if u is the root v will now be the root.
    if (u->p == nill)
        root = v;
    // if u is a left child, set parent's left child to be v.
    else if (u == u->p->l)
        u->p->l = v;
    // if u is a right child
    else
        u->p->r = v;

    // update the parent of v
    v->p = u->p;
}

void fanalysis::rightRotate(words *node){
    words *y = node->l;
    node->l = y->r;

    if(y->r != nill){
        y->r->p = node;
    }
    y->p = node->p;
    if(node->p == nill){
        root = y;
    }
    else{
        if(node==node->p->r){
            node->p->r = y;
        }
        else{
            node->p->l = y;
        }
    }

    y->r = node;
    node->p = y;
}

void fanalysis::leftRotate(words *node){

    words *y = node->r;
    node->r = y->l;

    if(y->l != nill){
        y->l->p = node;
    }

    y->p = node->p;

    if(node->p == nill){
        root = y;
    }

    else{
        if(node == node->p->l){
            node->p->l = y;
        }
        else{
            node->p->r = y;
        }
    }
    y->l = node;
    node->p = y;
}

void fanalysis::print(words *node){
    if(node->l != nill){
        print(node->l);
    }

    cout << node->word << endl;

    if(node->r != nill){
        print(node->r);
    }
}

void fanalysis::carr(words* arr, words *node, int counter){
    arr[counter] = *node;

    if(node->l != nill){
        carr(arr,node->l, counter+1);
        counter++;
    }
    counter++;
    if(node->r != nill){
        carr(arr, node->r, counter+1);
    }
}

words *fanalysis::findNode(string word){
    words *node = root;
    while(node != nill){
        if(word.compare(node->word.c_str()) < 0){
            node = node->l;
        }
        if(word.compare(node->word.c_str()) > 0){
            node = node->r;
        }
        if(word == node->word){
            break;
        }
    }
    return node;
}

void fanalysis::insertWord(string word){
    words *newNode = new words;
    newNode->setNode(word, nill, nill, nill);
    bool same = false;
    if(root == nill){
        root = newNode;
        n_of_total_words++;
    }
    else{
        words *traverse = root;
        while(traverse != nill){
            if(word.compare(traverse->word.c_str()) < 0){
                if(traverse->l == nill){break;}
                traverse = traverse->l;
            }
            else if(word.compare(traverse->word.c_str()) > 0){
                if(traverse->r == nill){break;}
                traverse = traverse->r;
            }
            if(word == traverse->word){
                break;
            }
        }
        if(word.compare(traverse->word.c_str()) < 0){
            traverse->l = newNode;
            n_of_total_words++;
            newNode->p = traverse;
        }
        if(word.compare(traverse->word.c_str()) > 0){
            traverse->r = newNode;
            n_of_total_words++;
            newNode->p = traverse;
        }

        if(word == traverse->word){
            delete newNode;
            same = true;
            traverse->frequency++;
        }
    }
    if(!same){
        rbAddFixup(newNode);
    }
}


/*
Function prototype:
fanalysis::fanalysis(string)

Function description:
This method creates a red/black tree from the words in the file and sorts them alphabetically. It keeps track of frequency of words as well.

Example:
fanalysis file("myFile.txt");

Precondition: If the file cannot be opened the other methods will not be able to function and will not build red/black tree.
*/

fanalysis::fanalysis(string f_name){
    words *nNill = new words;
    nNill->setNode("NILL", nNill, nNill, nNill);
    nill = nNill;
    root = nNill;
    nill->isRed = false;
    fileName = f_name;
    ifstream file;
    file.open(f_name.c_str());
    string word;
    n_of_total_words = 0;

    if(file.is_open()){
        open = true;
        while(!file.eof()){
            getline(file,word,' ');
            insertWord(word);
        }
    }
    else{
        cout << "File was not able to open." << endl;
        open = false;
    }
    file.close();
}

/*
Function prototype:
words *fanalysis::listallwords()

Function description:
This will return an array of all the words in pre-order traversal.

Example:
fanalysis file("myFile.txt");
words *arr = file.listallwords();

Precondition: If file was not able to be opened it wont return anything.
Postcondition: All memory deletion will be handled in the destructor.
*/

words *fanalysis::listallwords(){
    words *arr = new words[n_of_total_words];
    carr(arr,root,0);
    return arr;
}

/*
Function prototype:
words *fanalysis::frequent_words(int amt);

Function description:
This method find the top "amt" of words and returns them in an array of size "amt". Sorted by most frequent first.

Example:
fanalysis file("myFile.txt");
words *arr = file.frequent_words(7);

Precondition: If file was not able to be opened it wont return anything and if the file does not have enough words it will return empty slots.
Postcondition: All memory deletion will be handled in the destructor.
*/

words* fanalysis::frequent_words(int amt){
    words *list_o_words = new words[n_of_total_words];
    carr(list_o_words,root,0);
    queue<words> ranked;
    for(int i = 0; i < n_of_total_words; i++){
        ranked.push(list_o_words[i]);
    }
    words *rank_wrds = new words[amt];
    int mx = 0;
    for(int i = 0; i < amt; i++){
        rank_wrds[i].frequency = 0;
    }
    while(!ranked.empty()){
        words node = ranked.front();ranked.pop();
        for(int x = 0; x < amt; x++){
            if(node.frequency >= rank_wrds[x].frequency and (x+1) != amt){
                for(int y = amt-1; (y-1) >= x; y--){
                    rank_wrds[y].frequency = rank_wrds[y-1].frequency;
                    rank_wrds[y].word = rank_wrds[y-1].word;
                }
                rank_wrds[x].frequency = node.frequency;
                rank_wrds[x].word = node.word;
                break;
            }
        }
    }

    /*
    for(int x = 0; x < amt; x++){
        cout << rank_wrds[x].frequency << " - " << rank_wrds[x].word << endl;
    }*/

    delete []list_o_words;
    return rank_wrds;

}

/*
Function prototype:
int fanalysis::getTotal_num_words();

Function description:
Returns the total amount of distinct words in the text document that was read in upon initiating the class.

Example:
fanalysis file("myFile.txt");
int num = file.getTotal_num_words();

Precondition: If file was not able to be opened it wont return anything.
Postcondition: Nothing to worru about after calling function.
*/

int fanalysis::getTotal_num_words(){
    return n_of_total_words;
}

/*
Function prototype:
void fanalysis::removePunc();

Function description:
Takes each line of the file and takes out the punctuation and then outputs to the original file.

Example:
fanalysis file("myFile.txt");
file.removePunc();

Precondition: If file was not able to be opened if will create the file.
Postcondition: Nothing to worry about after calling function.
*/

void fanalysis::removePunc(){
    ifstream file(fileName.c_str());
    queue<string> fileLines;
    string line;
    while(!file.eof()){
        getline(file,line,'\n');
        if(line != ""){
            fileLines.push(line);
        }
        line = "";
    }
    file.close();
    ofstream f(fileName.c_str());
    while(!fileLines.empty()){
        line = fileLines.front();fileLines.pop();

        for(int i = 0; i < line.size(); i++){
            if((int)line[i] < (int)'A' and (int)line[i] != (int)' '){
                for(int j = i; j < line.size(); j++){
                    line[j] = line[j+1];
                }
            }
        }
        for(int i = 0; i < line.size(); i++){
            if((int)line[i] < (int)'A' and (int)line[i] != (int)' '){
                for(int j = i; j < line.size(); j++){
                    line[j] = line[j+1];
                }
            }
        }
        f << line;
    }
    f.close();
}

/*
Function prototype:
void fanalysis::capitalize(bool);

Function description:
Takes each line and capitalizes each letter or makes each letter lowercase. True for capitalize and false for lowercase.

Example:
fanalysis file("myFile.txt");
file.capitalize(true);

Precondition: If file was not able to be opened if will create the file.
Postcondition: Nothing to worry about after calling function.
*/

void fanalysis::capitalize(bool cap){
    ifstream file(fileName.c_str());
    queue<string> fileLines;
    string line;
    while(!file.eof()){
        getline(file,line,'\n');
        if(line != ""){
            fileLines.push(line);
        }
        line = "";
    }
    file.close();
    ofstream f(fileName.c_str());
    while(!fileLines.empty()){
        line = fileLines.front();fileLines.pop();
        for(int i = 0; i < line.length(); i++){
            if(cap and (int)line[i] >= 97 and (int)line[i] <= 122){
                line[i] -= 32;
            }
            if(!cap and (int)line[i] >= 65 and (int)line[i] <= 90){
                line[i] += 32;
            }
        }
        line+="\n";
        f<<line;
    }
    f.close();
}

/*
Function prototype:
void fanalysis::replaceWrd(string,string);

Function description:
Finds every instance of the first string with the second string.

Example:
fanalysis file("myFile.txt");
file.replaceWrd("Blue","Green);

Precondition: If file was not able to be opened if will create the file.
Postcondition: Nothing to worry about after calling function.
*/

void fanalysis::replaceWrd(string wd1, string wd2){
    ifstream file(fileName.c_str());
    queue<string> fileLines;
    string line;
    string word;
    string line_edit;
    while(!file.eof()){
        getline(file,line,'\n');
        if(line != ""){
            fileLines.push(line);
        }
        line = "";
    }
    file.close();
    ofstream f(fileName.c_str());
    while(!fileLines.empty()){
        stringstream line; line << fileLines.front();fileLines.pop();
        while(!line.eof()){
            getline(line,word,' ');
            if(word == wd1){
                line_edit += wd2 + " ";
            }
            else{
                line_edit += word + " ";
            }

        }
        line_edit += "\n";
        f<<line_edit;
        line_edit = "";
    }
    f.close();
}

/*
Function prototype:
void fanalysis::shift_all_words(int);

Function description:
Shifts the ASCII value of each character by the integer inputed in.

Example:
fanalysis file("myFile.txt");
file.shift_all_words(17);

Precondition: If file was not able to be opened if will create the file.
Postcondition: It will delete the existing file and replace it with the edited one.
*/

void fanalysis::shift_all_words(int shift){
    ifstream file(fileName.c_str());
    queue<string> fileLines;
    string line;
    while(!file.eof()){
        getline(file,line,'\n');
        if(line != ""){
            fileLines.push(line);
        }
        line = "";
    }
    file.close();
    ofstream f(fileName.c_str());
    while(!fileLines.empty()){
        line = fileLines.front();fileLines.pop();
        for(int i = 0; i < line.length(); i++){
            line[i]+=shift;
        }
        line += "\n";
        f<<line;
    }
    f.close();
}

/*
Function prototype:
void fanalysis::bacwords_words();

Function description:
Takes every word and makes it backwards and puts it back into the file in the correct order except the word itself is backwards.

Example:
fanalysis file("myFile.txt");
file.backwords_words();

Precondition: If file was not able to be opened if will create the file.
Postcondition: It will delete the existing file and replace it with the edited one.
*/

void fanalysis::backwords_words(){
    ifstream file(fileName.c_str());
    queue<string> fileLines;
    string line;
    string word;
    string temp;
    string line_edit;
    while(!file.eof()){
        getline(file,line,'\n');
        if(line != ""){
            fileLines.push(line);
        }
        line = "";
    }
    file.close();
    ofstream f(fileName.c_str());
    while(!fileLines.empty()){
        stringstream line; line << fileLines.front();fileLines.pop();
        while(!line.eof()){
            getline(line,word,' ');
            temp = word;
            for(int i = 0; i < word.length(); i++){
                temp[word.length()-1-i] = word[i];
            }
            line_edit += temp + " ";

        }
        line_edit += "\n";
        f<<line_edit;
        line_edit = "";
    }
    f.close();
}

/*
Function prototype:
int fanalysis::frequencyofword(string word);

Function description:
Finds the node in the tree and returns its frequency in the document.

Example:
fanalysis file("myFile.txt");
int i = file.frequencyofword("Pineapple");

Precondition: If file was not able to be opened it will return 0.
Postcondition:
*/

int fanalysis::frequencyofword(string word){
    words *node = findNode(word);
    if(node == nill){
        return 0;
    }
    else{
        return node->frequency;
    }
}
