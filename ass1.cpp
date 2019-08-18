#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <ctype.h>

const int MAX = 400000;
std::string dic[MAX];
int end = 0;

struct Word_Type{
public:
    Word_Type(){};
    Word_Type(std::string w, bool u, bool d) : word(w), isUnique(u), inDic(d){};
    static int vwords;
    static int uwords;
    static int udwords;
    std::string word;
    bool isUnique;
    bool inDic;
};

int Word_Type::vwords = 0;
int Word_Type::uwords = 0;
int Word_Type::udwords = 0;

void clean(std::string &nword){
    std::string cword ="";
    for (int i = 0; i < nword.size(); i++){
        if (isalpha(nword[i])){
            cword += tolower(nword[i]);
        }
    }
    nword = cword;
    return;
}

void insertion_sort(Word_Type *arr, int size){
    for(int i = 1; i < size; i++){
        Word_Type curr = arr[i];
        int hole_index = i;
        //while not at the start of sorted portion, check if curr is < hole_index
        while (hole_index > 1 && arr[hole_index - 1].word > curr.word){
            //swap 
            arr[hole_index] = arr[hole_index -1];
            hole_index = hole_index - 1;
        }
        arr[hole_index] = curr;
    }
}

void print(Word_Type *arr, int size){
    for(int i = 1; i < size; i++){
        std::cout << arr[i].word << " ";
    }
    std::cout << std::endl;
}

void print_unique(Word_Type *arr, int size){
    for(int i = 1; i < size; i++){
        if(arr[i].isUnique){
            std::cout << arr[i].word << " ";
        }
    }
    std::cout << std::endl;
}

int main(){
//Step 1 emordnilap pt.1
    //read dictionary.txt into an array of 400,000 words (each word is max 35 chars)
    std::ifstream inData;
    inData.open("dictionary.txt");
    if(!inData.is_open()) return -1;
    
    std::string line;
    while(getline(inData, line) && end < MAX){
        end++;
        dic[end] = line;
    }
    inData.close(); /*
    std::cout << "Number of words added is: " << end << '\n';
    std::cout << "Find first 10 valid reversed words\n";

//use linear search to find the first 10 reverse words in the dictionary array
    std::string word, rword;
    int matches = 0;
    clock_t time_begin = clock();
    for (int i = 1; i <= end && matches < 5; i++){
        //get word and rword
        word = dic[i];
        if (word.size() > 1){
            rword = std::string(word.rbegin(), word.rend());
            //find word with linear search
            for (int j = 1; j <= end; j++){
                if ((dic[j] == rword)) {
                    std::cout << word << " : " << rword << std::endl;
                    matches++;
                    break;
                }
            }
        }
    }
    clock_t time_end = clock();
    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;
    std::cout << "time (sec): " << elapsed_secs << std::endl;

    //Step 2 - emordnilap pt.2
    //perform a binary search to find all emordnilap
    int lower, higher, mid;
    bool found;

    time_begin = clock();
    for (int i = 1; i <= end; i++){
        //get word and rword
        word = dic[i];
        if(word.size() > 1){
            rword = std::string(word.rbegin(), word.rend());

            //search for word using binary search
            lower = 1;
            higher = end-1;
            found = false;
            while(!found && lower <= higher){
                mid = (lower + higher) / 2;
                if(dic[mid] == rword) {
                    found = true;
                    //std::cout << word << " : " << rword << std::endl;
                } else {
                    if (dic[mid] > rword) {
                        higher = mid -1;
                    } else {
                        lower = mid +1;
                    }
                }
            }
        }
    }
    std::cout << std::endl;
    time_end = clock();
    elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;
    std::cout << "time for binary to do ALL (sec): " << elapsed_secs << std::endl;

    //perform a binary search insted of linear search, print 10
    std::cout << "Find first 10 valid reversed words, with binary search.\n";
    matches = 0;
    
    for (int i = 1; i <= end && matches < 5; i++){
        //get word and rword
        word = dic[i];
        if(word.size() > 1){
            rword = std::string(word.rbegin(), word.rend());

            //search for word using binary search
            lower = 1;
            higher = end;
            found = false;
            while(!found && lower <= higher){
                mid = (lower + higher) / 2;
                if(dic[mid] == rword) {
                    found = true;
                    matches++;
                    std::cout << word << " : " << rword << std::endl;
                } else {
                    if (dic[mid] > rword) {
                        higher = mid -1;
                    } else {
                        lower = mid +1;
                    }
                }
            }
        }
    }

//print the largest emordnilap
    int largest = 2;
    int lindex;
    std::string lrword;
    for (int i = 1; i <= end; i++){
        //get word
        word = dic[i];

        //determine if the word is the largest encountered
        if(word.size() > largest){
            rword = std::string(word.rbegin(), word.rend());

            //search for word using binary search
            lower = 1;
            higher = end;
            found = false;
            while(!found && lower <= higher){
                mid = (lower + higher) / 2;
                if(dic[mid] == rword) {
                    //if found then make it largest
                    found = true;
                    largest = rword.size();
                    lindex = i;
                    lrword = rword;
                } else {
                    if (dic[mid] > rword) {
                        higher = mid -1;
                    } else {
                        lower = mid +1;
                    }
                }
            }
        }
    }
    std::cout << "largest emordnilap found has a size of: "<< largest << " => " << dic[lindex] << " : " << lrword << std::endl;//*/

//Step 3 - Spell checker
    //Read the input sample.txt file
    /**/inData.open("sample.txt");
    if (!inData.is_open()){ return -1;}
    std::string nword;
    Word_Type wordsarr[500];
    int end_wordsarr = 0; //is one based array
    while (inData >> nword){
        //preprocess word
        clean(nword);

        if (nword.size() > 0){
            Word_Type::vwords++;
            //Search for word in wordsarr
            int l=1,m = 1,h=end_wordsarr;
            bool f = false, inDic = false, isUnique = false;
            while(!f && l <= h && end_wordsarr > 0){
                m = (l + h) /2;
                if(wordsarr[m].word == nword){
                    //if target was consider unique
                    f = true;
                    wordsarr[m].isUnique = false;
                } else {
                    if (wordsarr[m].word > nword){
                        h = m - 1;
                    } else {
                        l = m + 1;
                    }
                }
            }
            //if not found in wordsarr search in dictionary, if it was found then dont do this, since nword is already in wordsarr program can just move onto next word
            if (!f){
                isUnique = true;
                l=1, h=end;
                while (!inDic && l <= h){
                    m = (l+h)/2;
                    if(dic[m] == nword){
                        //if found set inDic to true, isUnique to true and added to wordsarr and sort
                        inDic = true;
                    } else {
                        if (dic[m] > nword){
                            h = m - 1;
                        } else {
                            l = m + 1;
                        }
                    }
                }
                if(!f){
                    Word_Type nword_type(nword, isUnique, inDic);
                    if (isUnique) Word_Type::uwords++;
                    if (isUnique && inDic) Word_Type::udwords++;
                    end_wordsarr++;
                    wordsarr[end_wordsarr] = nword_type;
                    //std::cout << wordsarr[end_wordsarr].word << " isUnique: " << wordsarr[end_wordsarr].isUnique << " inDic: " << wordsarr[end_wordsarr].inDic << std::endl;
                    insertion_sort(wordsarr, end_wordsarr);
                }
            }
        }
        nword = "";
    }
    std::cout << "number of valid words read: " << Word_Type::vwords << std::endl;
    std::cout << "number of unique words read: " << Word_Type::uwords << std::endl;
    std::cout << "number of unique dictionary words read: " << Word_Type::udwords << std::endl;
    print(wordsarr, end_wordsarr);
    std::cout << "\nUnique words" << std::endl;
    print_unique(wordsarr, end_wordsarr);
    //*/
    //pre process the words read, by converting to lowercase with no punchtuations (as one word), 0 char words are rejected from the sample.txt

    //STRAT 3 (with structs): get word, preprocess, if valid increment vwords, search in WORDSARR if found && .isUnique == true then set to false and decrement unique words (if .inDictionary was also true then decrement udwords as well) then break otherwise just break, 
    
    //if not found search in dictionary if found in dictionary add to end of WORDSARR increment uwords and udwords and set .inDictionary to true and insertion sort it, if not found in dictionary add to WORDSARR increment uwords and set .inDictionary to false and insertion sort it.

    //print, num valid words, num unique words, num of unique that were in dictionary

//Step 4 - Anagrams
    //STRAT 1: for each word in unique_words array, create search and sort permutatioins, if valid print, increment amagram_words and increment anagrams_found, keep count of word which had most anagrams and how many and its index in uniquewords array, repeat for next permutation, repeat for next word, be sure to do more than a binary search

}


/*******************************************************************//*
                                STEP 5
Step 1 linear search for first 5 emordnilap time    ==>
Step 2 linear search for all emordnilap time taken  ==>
Step 2 binary search for all emordnilap time taken  ==>
Step 2 speedup factor achieved                      ==>

Run time of whole program                           ==>
Machine                                             ==> Windows, 16gb ram, 1.6ghz cpu

DS and Algos used in: 
spell checker                                       ==>
find emordnilap                                     ==>
find anagrams                                       ==>
*//******************************************************************/
