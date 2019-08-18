#include <iostream>
#include <string>
#include <chrono> 


int main(){
    std::string word = "DIOOOO";

    auto stBegin = std::chrono::high_resolution_clock::now();
    //reverse string method 1
    std::string rWord2;
    int_fast8_t len = word.size();
    for (int_fast8_t i = len; i >= 0; i--){
        rWord2 += word[i];
    }
    //std::cout << rWord2 << '\n';
    std::cout << '\n';
    /////////////////////
    auto stEnd = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( stEnd - stBegin ).count();
    std::cout <<"time: "<< duration << '\n';

    stBegin = std::chrono::high_resolution_clock::now();
    //reverse string method 2
    std::string rWord1;
    int ilen = word.size();
    for (int i = ilen; i >= 0; i--){
        rWord1 += word[i];
    }
    //std::cout << rWord1 << std::endl;
    std::cout << '\n';
    ////////////////////////
    stEnd = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( stEnd - stBegin).count();
    std::cout <<"time: "<< duration << '\n';
    
    //conclusions and testing
    //tested with method 1 and 2 both taking turns being first in the execution order
    //about 60 runs of the program were done

    //int came out faster than int_fast8_t 23 times agaisnt fast_int8_t winning 12 times
}