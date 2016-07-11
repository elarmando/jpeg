#include <iostream>
#include "huffmancoding.h"
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

void testGenerateCodeLengths(){
    char symbols[] = {'A', 'C' , 'L', 'M', 'N', 'P', '_', '.'};
    int frequencies[] = {10, 1, 2, 2,4,   2,  6,     1};

    vector<char> vsymbols(symbols, std::end(symbols) );
    vector<int> vfrequencies(frequencies, std::end(frequencies));

    HuffmanCoding codec(vsymbols, vfrequencies);

    vector<HuffmanSymbols> simbols;

    codec.generateInitialList(simbols);

    codec.generateCodeLengths(simbols);

    HuffmanSymbols &fila = simbols.front();

    std::string str = fila.toStr();
    std::cout<<str<<'\n';
}

void testInitialList(){
    char symbols[] = {'a', 'b' , 'c'};
    int frequencies[] = {1, 0, 1};

    vector<char> vsymbols(symbols, std::end(symbols) );
    vector<int> vfrequencies(frequencies, std::end(frequencies));

    HuffmanCoding algo(vsymbols, vfrequencies);

    vector<HuffmanSymbols> list;

    algo.generateInitialList(list);

    auto ite = list.begin();

    while(ite != list.end()){
        HuffmanSymbols &node = *ite;

        std::cout<<node.toStr()<<'\n';

        ite++;
    }


}

void testGetLowest(){
    char symbols[] = {'A', 'C' , 'L', 'M', 'N', 'P', '_', '.'};
    int frequencies[] = {10, 1, 2, 2,4,   2,  6,     1};

    vector<char> vsymbols(symbols, std::end(symbols) );
    vector<int> vfrequencies(frequencies, std::end(frequencies));

    HuffmanCoding codec(vsymbols, vfrequencies);

    vector<HuffmanSymbols> simbols;

    codec.generateInitialList(simbols);
    vector<long> lowest = codec.getTwoLowestFreq(simbols);

    std::for_each(lowest.begin(), lowest.end(), [](long &num){
       std::cout<<num<<'/n';
    });
}

int main()
{
   //testInitialList();

    //testGetLowest();

    testGenerateCodeLengths();

    return 0;
}

