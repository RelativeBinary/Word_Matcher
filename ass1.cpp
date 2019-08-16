#include <string>
#include <iostream>
#include <fstream>
#include <ctime> 

void findEmordnilapLinear(std::string *arr, int end){
    int matches = 0;
    for (int i = 1; i <= end && matches < 10; i++){
        
    }
    std::cout << std::endl;
}

int main(){
    //Step 1 palindromes pt.1
    //start recording the start time
    std::clock_t start;
    double duration;
    start = std::clock();

    //read distionary.txt into an array of 400,000 words (each word is max 35 chars)
    const int max = 400000;
    int end = 0;
    std::string *dictionary = new std::string[max];
    std::ifstream inData;
    inData.open("dictionary.txt");
    if(!inData.is_open()) return -1;
    std::cout << "File opened\n";

    std::string line;
    int count = 0;
    while(getline(inData, line)){
        end++;
        dictionary[end] = line;
        count++;
    }

    std::cout << "\nNumber of words added: " << count << std::endl;

    //use linear search to find the first 10 palindromes in the dictionary array
    findPalindromeLinear(dictionary, end);

    //print the palindromes

    //then the program is to stop after 5 palindromes? (poor documentation)

    //Step 2 - Palindromes pt.2
    // (make some estimate on how long itll take to find all palindromes)

    //perform a binary search and estimate the time to find all the palindromes in the dictionary

    //print the first 10 palindromes, and the longest palindrome found (if there are multiple longest just print the first one encountered)

    //Step 3 - Spell checker
    //Read the input sample.txt file
    //pre process the words read, by converting to lowercase with no punchtuations (as one word), 0 char words are rejected from the sample.txt

    //Search each word

    //determine if its valid, if so add it to valid words, if not add it to invalid
    //determine if its been search already, if so dont search and remove unique word trait

    //print, num valid words, num unique words, num of unique that were in dictionary

    //Step 4 - Anagrams

    //end time recording and display time taken
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<<"Time taken in seconds: "<< duration <<'\n';
}


/*******************************************************************//*
                                STEP 5
Step 1 linear search for first 5 emordnilap time    ==>
Step 2 linear search for all emordnilap time taken ==>
Step 2 binary search for all emordnilap time taken ==>
Step 2 speedup factor achieved                      ==>

Run time of whole program                           ==>
Machine                                             ==> Windows, 16gb ram, 1.6ghz cpu

DS and Algos used in: 
spell checker                                       ==>
find emordnilap                                    ==>
find anagrams                                       ==>
*//******************************************************************/