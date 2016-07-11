#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H

#include<vector>
#include <string>

using namespace std;

class HuffmanSymbol{
public:
    char symbol;
    int codeLength;
    HuffmanSymbol(char symbol, int codeLenght);
    string toStr();

};

class HuffmanSymbols{
public:
    HuffmanSymbols();
    std::vector<HuffmanSymbol> nodes;
    unsigned int frequency;

    string toStr();
};

class HuffmanCoding
{
private:
    vector<char> symbols;
    vector<int> frequencies;


public:

    HuffmanCoding(vector<char> symbols, vector<int> frequencies);

    vector<long> getTwoLowestFreq(vector<HuffmanSymbols> &e);
    long getLowestFreq(vector<HuffmanSymbols> &e, long indexToSkip = -1);
    void generateCodeLengths(vector<HuffmanSymbols> &e);
    void generateInitialList(vector<HuffmanSymbols> &e);
    void generateCodes(HuffmanSymbol &simbols);
    void generateCodes();
};

#endif // HUFFMANCODING_H
