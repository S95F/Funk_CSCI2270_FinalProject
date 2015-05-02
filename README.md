# Funk_CSCI2270_FinalProject
Final Project for the class 2270

Document Editing

Project Summary
  My project is a library that is an extention of Assignment 2 "Word Analysis". It will use a red/black tree to store the words. It is capable of both editing the document and also giving some frequency of words that were used in the document. It is able to take any txt document and edit it. It allows the user to call functions that will change words. It can exchange words, shift letters by thir acii values, makes the words appear backwards, and make words either all capitalied or all lowercase. It can also tell you how many distinct words there are, how frequently they appear, and can show you each distinct word there is. 

How to Run
  Take the fanalysis.h and fanalysis.cpp and include them to the main project which in code blocks all you have to do is go to project and add them to the project, note the header and cpp will have to be in the same file as the main. You can either include the main I have created to facilitate testing or create your own main, this library is inteneded for a more general use. There is also a text file that must be in the same file as the main/header/cpp to run correctly. You can also create your own text file to edit and analysis. It does not need to be of any specific format because it looks at each word individually by the seperation of spaces.
  To run you create an instance of the class "fanalysis" with the text file's name as its initializing parameter. It will then create a red/black tree from that txt file and allow you to call the other various functions by using the created instance of the class to call the other functions: "frequent_wrds(int )", "getTotal_num_words()", "removePunc()", "capitalize(bool)", "replaceWrd(string,string)", "shift_all_words(int)", "backwords_words()", "frequencyofword(string)" ,"listallwords()".
 frequent_words(int) takes one parameter, an integer, and it will give back an array of size of the integer with the int more frequent words.
 getTotal_num_words() will return an int of the total number of distinct words in the txt
 removePunc() will take all punctuation out of the txt
 capitalize(bool) takes one parameter a bool. false will make the txt all lowercase while true will make it all capitals
 replaceWrd(string,string) takes two strings. It will find the first string in the document and replace it with the second string.
 shift_all_words(int) takes one arrguemnt an integer. It will shift all letters in the txt by this integer and of course if you then put the negitive integer it will put the document back to its origonal text.
 backwords_words() will make all the words in the document backwwards. 
 frequencyofword(string) will find the node with the same string and return the frequency of the word, 0 means it didn't find the node.
 listallwords() will return a array of all the words
 
Dependencies
	It will depend of the librarys: fstream, queue, stdlib.h, sstream
System Requirements
	The system has to be able to compile c++ functions
Group Members
 None
Contributers
 Gramkuma
Open issues/Bugs
It will occasionally add more spaces when it is replacing and shifting. Doesn't correctly view words if there is a period after a word.
