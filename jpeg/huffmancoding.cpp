#include "huffmancoding.h"
#include <string>
#include <sstream>
#include <iostream>
#include <limits>

HuffmanSymbol::HuffmanSymbol(char _symbol, int _codeLength):
symbol(_symbol),
codeLength(_codeLength)
{

}

string HuffmanSymbol::toStr(){
    stringstream stream;
    stream <<"(" <<symbol <<", " <<codeLength <<")";
    return stream.str();
}

HuffmanSymbols::HuffmanSymbols():
frequency(0)
{

}

string HuffmanSymbols::toStr(){
    vector<HuffmanSymbol>::iterator ite = nodes.begin();
    stringstream stream;

    while( ite != nodes.end()){
        HuffmanSymbol &node = *ite;
        stream << node.toStr()<<"  ";


        ite++;
    }

    stream<<"freq " << frequency;

    return stream.str();

}

void HuffmanCoding::generateInitialList(vector<HuffmanSymbols> &lista)
{

    for(size_t i = 0; i < symbols.size(); i++){
        HuffmanSymbols list;
        HuffmanSymbol symbol(symbols[i], 0);

        list.nodes.push_back(symbol);
        list.frequency = frequencies[i];

        lista.push_back(list);

    }

}

void HuffmanCoding::generateCodes(HuffmanSymbol &simbols)
{

}

HuffmanCoding::HuffmanCoding(vector<char> _symbols, vector<int> _frequencies):
symbols(_symbols),
frequencies(_frequencies)
{

}

vector<long> HuffmanCoding::getTwoLowestFreq(vector<HuffmanSymbols> &lista)
{
    long first = this->getLowestFreq(lista);
    long second = this->getLowestFreq(lista, first);

    vector<long> lowest;
    lowest.push_back(first);
    lowest.push_back(second);


    return lowest;
}

long HuffmanCoding::getLowestFreq(vector<HuffmanSymbols> &lista, long indexToSkip)
{
    unsigned int minVal = std::numeric_limits<unsigned long>::max();
    unsigned int currentVal;
    long lowestIndex = -1;
    long l = lista.size();

    for(long i = 0; i < l; i++){
        currentVal = lista[i].frequency;

        if(currentVal <= minVal && indexToSkip != i){
            lowestIndex = i;
            minVal = currentVal;
        }

    }

    return lowestIndex;

}

void HuffmanCoding::generateCodeLengths(vector<HuffmanSymbols> &e)
{
    while(e.size() > 1){
        vector<long> indexes = this->getTwoLowestFreq(e);

        HuffmanSymbols &simbols1 = e[indexes[0]];
        HuffmanSymbols &simbols2 = e[indexes[1]];

        //new list frequency is the sum of the previous ones
        simbols1.frequency += simbols2.frequency;


        //add each simbol of the second list to the first one
        auto ite = simbols2.nodes.begin();
        auto end = simbols2.nodes.end();

        while(ite != end){
            simbols1.nodes.push_back(*ite);
            ite++;
        }

        //increment all code lengths
        ite = simbols1.nodes.begin();
        end = simbols1.nodes.end();

        while(ite != end){
            HuffmanSymbol &symbol = *ite;
            symbol.codeLength++;
            ite++;
        }

        //removes second of the list
        e.erase(e.begin() + indexes[1]);

    }

}



void HuffmanCoding::generateCodes(){

    vector<HuffmanSymbols> lista;

    this->generateInitialList(lista);




}

