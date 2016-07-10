#include "huffmancoding.h"

HuffmanSymbol::HuffmanSymbol(char _symbol, int _codeLength):
symbol(_symbol),
codeLength(_codeLength)
{

}

NodeList::NodeList():
frequency(0)
{

}

void HuffmanCoding::generateInitialList(vector<NodeList> &lista)
{

    for(size_t i = 0; i < symbols.size(); i++){
        NodeList list;
        HuffmanSymbol symbol(symbols[i], 0);

        list.nodes.push_back(symbol);
        list.frequency = frequencies[i];

        lista.push_back(list);

    }

}

HuffmanCoding::HuffmanCoding(vector<char> _symbols, vector<int> _frequencies):
symbols(_symbols),
frequencies(_frequencies)
{

}

void HuffmanCoding::generateCodes(){

}

