#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <ctype.h>

const int MAX = 400000;
std::string dic[MAX];
int end = 0;

//AVL TREE IMPLEMENTATION
#pragma region
struct Word_Type{
public:
    static int vwords;
    static int uwords;
    static int udwords;
    Word_Type(){};
    Word_Type(std::string w, bool u, bool d) : word(w), isUnique(u), inDic(d){};
    std::string word;
    Word_Type* left;
    Word_Type* right;
    int height;
    bool isUnique;
    bool inDic;
};

int Word_Type::vwords = 0;
int Word_Type::uwords = 0;
int Word_Type::udwords = 0;

void clean(std::string &nword){
    std::string cword ="";
    for (int i = 0; i < nword.size(); i++){
        if (isalpha(nword[i])) cword += tolower(nword[i]);
    }
    nword = cword;
}

int Max(int a, int b){
    return (a > b) ? a : b;
}

int Height(Word_Type* node){
    if(node == nullptr) return -1;
    return node->height;
}

//create wordtype
Word_Type* NewNode(std::string word, bool isUnique, bool inDictionary){
    Word_Type* newWord_Type = new Word_Type();
    newWord_Type->word = word;
    newWord_Type->left = nullptr;
    newWord_Type->right = nullptr;
    newWord_Type->height = 0;
    newWord_Type->isUnique = isUnique;
    newWord_Type->inDic = inDictionary;
    return newWord_Type;
}

Word_Type* RightRotate(Word_Type* nodeY){
    Word_Type* nodeX = nodeY->left;
    Word_Type* subT2 = nodeX->right;

    //perform retation
    nodeX->right = nodeY;
    nodeY->left = subT2;

    //update heights
    nodeY->height = Max(Height(nodeY->left), Height(nodeY->right)) + 1;
    nodeX->height = Max(Height(nodeX->left), Height(nodeX->right)) + 1;

    //return new root
    return nodeX;
}

Word_Type* LeftRotate(Word_Type* nodeX){
    Word_Type* nodeY = nodeX->right;
    Word_Type* subT2 = nodeY->left;

    // Perform rotation  
    nodeY->left = nodeX;  
    nodeX->right = subT2;  
  
    // Update heights
    nodeX->height = Max(Height(nodeX->left), Height(nodeX->right)) + 1;
    nodeY->height = Max(Height(nodeY->left), Height(nodeY->right)) + 1;

    // Return new root  
    return nodeY;  
}  

int GetBalance(Word_Type* node){
    if(node == nullptr) return 0;
    return Height(node->left) - Height(node->right);
}

Word_Type* Insert(Word_Type* root, std::string word, bool isUnique, bool inDictionary){
    if(root == nullptr) {//empty tree
        root = NewNode(word, isUnique, inDictionary);
    }
    else if (word <= root->word) {
        root->left = Insert(root->left, word, isUnique, inDictionary);
    }
    else if (word > root->word) {
        root->right = Insert(root->right, word, isUnique, inDictionary);
    } else {//all words are unique, but still duplicates are not allowed.
        return root;
    }

    //update Height of this ancestor node
    root->height = Max(Height(root->left), Height(root->right)) + 1; //plus one since its the parent

    //get balance factor
    int balance = GetBalance(root);

    //if root is unbalanced the determine out of the 4 cases

    //left left (push nodes to the left)
    if (balance > 1 && word < root->left->word){
        return RightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && word > root->right->word)
        return LeftRotate(root);

    // Left Right Case
    if (balance > 1 && word > root->left->word){
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && word < root->right->word){
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    /* return the (unchanged) node pointer */
    return root;
}


bool Search(Word_Type* root, std::string word){
    //comparisons++;
    if(root == nullptr){
        return false;
    } else if (root->word == word){
        //this will only execute when the first duplicate of a word is searched
        //std::cout << "Search success: " << root->word << " || uwords count: " << Word_Type::uwords << " || udwords count: " << Word_Type::udwords << std::endl;
        return true;
    } else if (word <= root->word){
        return Search(root->left, word);
    } else return Search(root->right, word);
}

void InOrder(Word_Type* root){
    //left, data, right

    //left
    if(root->left != nullptr) InOrder(root->left);

    //data
    std::cout << root->word << " ";

    //right
    if(root->right != nullptr) InOrder(root->right);

    //exit
    if(root->left == nullptr && root->right == nullptr) return;
}

void InOrderUnique(Word_Type* root){
    //left, data, right

    //left
    if(root->left != nullptr) InOrderUnique(root->left);

    //data
    if (root->isUnique == true) {
        //std::cout << root->word << " ";
    }

    //right
    if(root->right != nullptr) InOrderUnique(root->right);

    //exit
    if(root->left == nullptr && root->right == nullptr) return;
}

void Unique2Array(Word_Type* root, std::string* uwords_arr, int &end_uwords_arr) {
    //left, data, right

    //left
    if(root->left != nullptr)
        Unique2Array(root->left, uwords_arr, end_uwords_arr);

    //data
    if (root->isUnique == true) {
        end_uwords_arr++;
        uwords_arr[end_uwords_arr] = root->word;
    }

    //right
    if(root->right != nullptr)
        Unique2Array(root->right, uwords_arr, end_uwords_arr);

    //exit
    if(root->left == nullptr && root->right == nullptr) return;
}


#pragma endregion

//STEP 4 FUNCTIONS
#pragma region
//partition functions used in quicksort
int partition(char *arr, int ast, int aen){
    int piv = arr[aen];
    int parIn = ast; //initialize start partition at the start of array
    for (int i = ast; i < aen; i++){
        if(arr[i] <= piv){ //move larger elements toward end of arr, move smaller elements toward start of arr
            std::swap(arr[i], arr[parIn]);
            parIn++;
        }
    }
    std::swap(arr[parIn], arr[aen]);
    return parIn;
}
//quick sort function
void qsort(char *arr, int ast, int aen){
    if (ast < aen){
        int parIn = partition(arr, ast, aen);
        qsort(arr, ast, parIn - 1);
        qsort(arr, parIn + 1, aen);
    }
}
//used in step 4 to sort the unique word needed for comparisons with an additionally sorted dictionary word
void sort(std::string* word, int s, int e){
    char arr[35];
    int arr_end = 0;
    for (char c : (*word)){
        arr[arr_end] = c;
        arr_end++;
    }
    qsort(arr, s, e);
    
    for (int i = 0; i < arr_end; i++){
        (*word)[i] = arr[i];
    }
}

#pragma endregion

//MAIN
int main(){
    //DICTIONARY INITIALIZATION
    #pragma region
        std::ifstream inword;
        inword.open("dictionary.txt");
        if(!inword.is_open()) return -1;

        std::string line;
        while(getline(inword, line) && end < MAX){
            end++;
            dic[end] = line;
        }
        inword.close();
        std::cout << "Number of words in dictionary: " << end << '\n';
    #pragma endregion

    //STEP 1 USE LINEAR SEARCH TO FIND FIRST 10 REVERSE WORDS IN DICTIONARY
    #pragma region
    /*std::cout << "Find first 5 valid reversed words\n";
    std::string rword;
    int matches = 0;
    int comparisons = 0;
    clock_t time_begin = clock();
    for (int i = 1; i <= end && matches < 5; i++){
        if (dic[i].size() > 1){
            rword = std::string(dic[i].rbegin(), dic[i].rend());
            //find word with linear search
            for (int j = 1; j <= end; j++){
                comparisons++;
                if ((dic[j] == rword)) {
                    std::cout << dic[i] << " : " << rword << std::endl;
                    matches++;
                    break;
                }
            }
        }
    }
    clock_t time_end = clock();
    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;
    std::cout << "comparisons: " << comparisons << std::endl;
    std::cout << "time (sec): " << elapsed_secs << std::endl;
    std::cout << std::endl;*/
    #pragma endregion

    //STEP 2 USE BINARY SEARCH TO FIND ALL REVERSE WORDS IN DICTIONARY
    #pragma region
    /*int lower, higher, mid;
    //int matches = 0;
    std::string rword = "";
    bool found;
    int comparisons = 0;
    //start timing
    clock_t time_begin = clock();
    for (int i = 1; i <= end; i++){
        if (dic[i].size() > 1){
            rword = std::string(dic[i].rbegin(), dic[i].rend());
            //search for word using binary search
            lower = 1;
            higher = end-1;
            found = false;
            while(!found && lower <= higher){
                mid = (lower + higher) / 2;
                comparisons++;
                if(dic[mid] == rword) {
                    found = true;
                    //matches++;
                } else {
                    comparisons++;
                    if (dic[mid] > rword) {
                        higher = mid -1;
                    } else {
                        lower = mid +1;
                    }
                }
            }
        }
    }
    //end timing
    clock_t time_end = clock();
    double elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;
    std::cout << "comparisons: " << comparisons << std::endl;
    std::cout << "time for binary to find ALL (sec): " << elapsed_secs << std::endl;
    std::cout << std::endl;*/
    #pragma endregion
    
    //STEP 2 FIND 10 AND LARGEST REVERSE WORD
    #pragma region
    /*
    std::cout << "Find first 10 valid reversed words and largest reversed word, with binary search.\n";
    matches = 0;
    int largest = 2;
    int lindex;
    std::string lrword;
    //start timing
    time_begin = clock();
    for (int i = 1; i <= end; i++){
        if (dic[i].size() > 1){
            rword = std::string(dic[i].rbegin(), dic[i].rend());
            //search for word using binary search
            lower = 1;
            higher = end;
            found = false;
            while(!found && lower <= higher){
                mid = (lower + higher) / 2;
                if (dic[mid] == rword){
                    found = true;
                    if(matches < 10){
                        matches++;
                        //std::cout << word << " : " << rword << std::endl;
                    }
                    if (dic[i].size() > largest){
                        largest = rword.size();
                        lindex = i;
                        lrword = rword;
                    }
                } else {
                    if (dic[mid] > rword){
                        higher = mid -1;
                    } else {
                        lower = mid +1;
                    }
                }
            }
        }
    }
    std::cout << "largest emordnilap found has a size of: "<< largest << " => " << dic[lindex] << " : " << lrword << std::endl;
    //end timing
    time_end = clock();
    elapsed_secs = double(time_end - time_begin) / CLOCKS_PER_SEC;
    std::cout << "time to find first 10 and largest (sec): " << elapsed_secs << std::endl;
    std::cout << std::endl;*/

    //STEP 2 Find All/Find 10 and largest, SPEED IMPROVMENTS:
    /*  Previous version of the algorithm, would take a word at index i from dictionary array and assign it to a variable 'word' to be used in the algorithm
        Removing that assignment and just refering to dic[i] throughout the algorithm improved speed.
        Before --> After
        5.38s  --> 5.05s

        Adding a condition to check if the word is already a palindrome before searching the dictionary cause time to complete to increase.
        Before --> After
        5.38s  --> 7.88s
    */
   #pragma endregion

    //STEP 3 SAMPLE TEXT SPELL CHECKER
    #pragma region

    //Read the input sample.txt file
    inword.open("sample.txt");
    if (!inword.is_open()){ return -1;}
    std::string nword;
    Word_Type* rootptr;
    rootptr = nullptr;

    //begin spell checking
    while (inword >> nword){
        //preprocess word
        clean(nword);
        //std::cout << nword << " ";
        //check if valid word
        if (nword.size() > 0){
            Word_Type::vwords++;
            //search for word in wordsarr
            bool inWordsTree = false;
            bool isUnique = false;
            bool inDictionary = false;

            //search for word in words tree
            inWordsTree = Search(rootptr, nword);
            
            //if not found, then nword isUnique and search in dictionary
            if (!inWordsTree) {
                isUnique = true;
                //search in dictionary to check spelling via binary search
                int lower = 1, higher = end, mid;
                bool found = false;
                while(!found && lower <= higher){
                    mid = (lower + higher) / 2;
                    if(dic[mid] == nword) {
                        found = true;
                        inDictionary = true;
                    } else {
                        if (dic[mid] > nword) {
                            higher = mid -1;
                        } else {
                            lower = mid +1;
                        }
                    }
                }
                if(isUnique) Word_Type::uwords++;
                if(isUnique && inDictionary) Word_Type::udwords++;
                //add to words tree, AVL tree will balance itself
                //std::cout <<"Insertion call: "<< nword << " || uwords count: " << Word_Type::uwords << " || udwords count: " << Word_Type::udwords << std::endl;
                rootptr = Insert(rootptr, nword, true, inDictionary);
            }  
        }
        //std::cout << std::endl;
        nword = "";
    }
    std::cout << "Number of valid words read: " << Word_Type::vwords << std::endl;
    std::cout << "Number of unique words read: " << Word_Type::uwords << std::endl;
    std::cout << "Number of unique dictionary words read: " << Word_Type::udwords << std::endl;
    
    //storing unique words in a suitable array.
    std::string uwords_arr[500];
    int end_uwords_arr = 0;
    Unique2Array(rootptr, uwords_arr, end_uwords_arr);
    
    //testing functions that print out the AVL tree data via inOrder traversal
    /*std::cout << "Displaying all the words found in the file: " << std::endl;
    InOrder(rootptr);
    std::cout << std::endl;
    
    std::cout << "Displaying all the unique words found in the file: " << std::endl;
    std::cout << std::endl;
    InOrderUnique(rootptr);
    //END OF COMMENT BLOCK*/

    //pre process the words read, by converting to lowercase with no punchtuations (as one word), 0 char words are rejected from the sample.txt

    //STRAT 3 (with structs): get word, preprocess, if valid increment vwords, search in WORDSARR if found && .isUnique == true then set to false and decrement unique words (if .inDictionary was also true then decrement udwords as well) then break otherwise just break, 
    
    //if not found search in dictionary if found in dictionary add to end of WORDSARR increment uwords and udwords and set .inDictionary to true and insertion sort it, if not found in dictionary add to WORDSARR increment uwords and set .inDictionary to false and insertion sort it.

    //print, num valid words, num unique words, num of unique that were in dictionary
    #pragma endregion

//Step 4 - Anagrams
/*
    //STRAT 1: for each word in unique_words array, create search and sort permutatioins, if valid print, increment amagram_words and increment anagrams_found, keep count of word which had most anagrams and how many and its index in uniquewords array, repeat for next permutation, repeat for next word, be sure to do more than a binary search
*/
    std::string anagrams[500];
    int end_anagrams = 0, max_anagrams = 0, total_anagrams = 0;
    int s4_matches = 0, max_anagram_index, anagram_words = 0, anagrams_found= 0;
    int largest_anagram_index, largest_anagram_size = 0;
    std::string largest_anagram_sample = "";
    for (int i = 1; i < end_uwords_arr; i++){
        //create sorted alternative (potential optimization check if word is more than 1 character long before doing all this)
        std::string sort_origin = uwords_arr[i];
        sort(&sort_origin, 0, sort_origin.size()-1);
        for (int j = 1; j < end; j++){
            //for each word in dictionary of the same size
            if (dic[j].size() == sort_origin.size()){
                std::string dword = dic[j];
                //create sorted dword (dictionary word)
                sort(&dword, 0, dword.size()-1);
                //compare with original sorted word
                if (dword == sort_origin && uwords_arr[i] != dic[j]){
                    //add to anagrams array if anagram
                    end_anagrams++;
                    anagrams[end_anagrams] = dic[j];
                    //increment number of anagrams found
                    anagrams_found++;
                }
            }
        }
        //print out all the anagrams found for current unique word which has more than 1
        if (end_anagrams > 0){
            //increment number of unique words which had anagrams
            anagram_words++;
            //check if current unique word has potential to be the largest word with anagram(s)
            if (uwords_arr[i].size() > largest_anagram_size) {
                largest_anagram_index = i;
                largest_anagram_size = uwords_arr[i].size();
                largest_anagram_sample = anagrams[1];
                
            }

            //print anagrams only for first 10 unique words
            if(s4_matches < 10){
                std::cout << uwords_arr[i] << ": ";
                for (int j = 1; j <= end_anagrams; j++){
                    std::cout << anagrams[j] << " ";
                }
                std::cout << std::endl;
                s4_matches++;
            }
        }
        //determine if this uword had the most anagrams
        if (end_anagrams > max_anagrams){
            max_anagram_index = i;
            max_anagrams = end_anagrams;
        }
        end_anagrams = 0;
    }
    std::cout << "Word that had the most anagrams: " << uwords_arr[max_anagram_index] << " => " << max_anagrams << " anagrams.\n";
    std::cout << "Largest valid word that has an anagram: " << uwords_arr[largest_anagram_index] /*<<" => " << largest_anagram_sample*/ << std::endl;
    std::cout << "Total amount of words with anagrams: " << anagram_words << std::endl;
    std::cout << "Total anagrams found: " << anagrams_found << std::endl;
 
}


/*******************************************************************//*
                                STEP 5
Step 1 linear search for first 10 emordnilap time   ==> 57.23sec ~ 1min
Step 2 linear search for all emordnilap estimation - 10th emordnilap 
is the 616th word which is 0.16644% of the total dictionary. 
0.16644 * 600.8165584 ~ 100%
~1min * 600.8165584 = 600.8165584mins ~ 10hrs
binary search too ~5.05s to find all reverse palindromes.
(5.05/600.8165584mins * 60s) * 100 = 0.014% of linear search's time
99.986% reduction in time taken. Based on linear estimation

Step 2 binary search for all emordnilap time taken  ==> 5.05
Step 2 speedup factor achieved                      ==> 99.986%
Run time of whole program                           ==> ???
Machine                                             ==> BANSHEE SERVER
DS and Algos used in: 
spell checker                                       ==> my own algorithm
find emordnilap                                     ==> my own algorithm
find anagrams                                       ==> match sorted strings algorithm
*//******************************************************************/
