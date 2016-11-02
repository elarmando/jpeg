#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H

#include<vector>
#include <string>

using namespace std;

class HuffmanSymbol{
public:
    char symbol;
    int codeLength;
    int code;
     HuffmanSymbol();
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

    void findMinMax(std::vector<HuffmanSymbol> &symbols, std::vector<int> &minOut, std::vector<int> &maxOut);


public:

    HuffmanCoding(vector<char> symbols, vector<int> frequencies);

    vector<long> getTwoLowestFreq(vector<HuffmanSymbols> &e);
    long getLowestFreq(vector<HuffmanSymbols> &e, long indexToSkip = -1);
    void generateCodeLengths(vector<HuffmanSymbols> &e);
    void generateCodes(vector<HuffmanSymbol> &, bool order = true);
    void generateCodeLengthsFromCounts(vector<char> &counts, vector<HuffmanSymbol> &outLengths, bool resize = true);
    void generateInitialList(vector<HuffmanSymbols> &e);
    void generateCodes(HuffmanSymbol &simbols);
    void generateCodes();

    void readStream(std::vector<char> &countHuffman, std::vector<char> &values, std::vector<char> stream);
};

#endif // HUFFMANCODING_H
