#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H

#include<vector>

using namespace std;

class HuffmanSymbol{
public:
    char symbol;
    int codeLength;
    HuffmanSymbol(char symbol, int codeLenght);
};

class NodeList{
public:
    NodeList();
    std::vector<HuffmanSymbol> nodes;
    unsigned int frequency;
};

class HuffmanCoding
{
private:
    vector<char> symbols;
    vector<int> frequencies;

    void generateInitialList(vector<NodeList> &e);
public:

    HuffmanCoding(vector<char> symbols, vector<int> frequencies);


    void generateCodes();
};

#endif // HUFFMANCODING_H
