
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <bitset>
#include <sstream>

#include<jfifreader.h>





//void testGenerateCodes(){
//    char symbols[] = {'A', 'C' , 'L', 'M', 'N', 'P', '_', '.'};
//    int frequencies[] = {10, 1, 2, 2,4,   2,  6,     1};

//    vector<char> vsymbols(symbols, std::end(symbols) );
//    vector<int> vfrequencies(frequencies, std::end(frequencies));

//    HuffmanCoding codec(vsymbols, vfrequencies);

//    vector<HuffmanSymbols> simbols;
//    codec.generateInitialList(simbols);

//    codec.generateCodeLengths(simbols);

//    HuffmanSymbols &fila = simbols.front();

//    vector<HuffmanSymbol> &sbls = fila.nodes;

//    codec.generateCodes(sbls);

//    stringstream stream;

//    for(auto ite = sbls.begin(); ite != sbls.end(); ite++){
//        HuffmanSymbol &symbol = *ite;
//        std::bitset<32> binary(symbol.code);

//        stream<<"simbolo " << symbol.symbol << " codelength " << symbol.codeLength <<"binario " <<binary<<'\n';
//    }

//    std::cout<<stream.str();


//}

//void testGenerateCodeLengths(){
//    char symbols[] = {'A', 'C' , 'L', 'M', 'N', 'P', '_', '.'};
//    int frequencies[] = {10, 1, 2, 2,4,   2,  6,     1};

//    vector<char> vsymbols(symbols, std::end(symbols) );
//    vector<int> vfrequencies(frequencies, std::end(frequencies));

//    HuffmanCoding codec(vsymbols, vfrequencies);

//    vector<HuffmanSymbols> simbols;

//    codec.generateInitialList(simbols);

//    codec.generateCodeLengths(simbols);

//    HuffmanSymbols &fila = simbols.front();

//    std::string str = fila.toStr();
//    std::cout<<str<<'\n';
//}

//void testInitialList(){
//    char symbols[] = {'a', 'b' , 'c'};
//    int frequencies[] = {1, 0, 1};

//    vector<char> vsymbols(symbols, std::end(symbols) );
//    vector<int> vfrequencies(frequencies, std::end(frequencies));

//    HuffmanCoding algo(vsymbols, vfrequencies);

//    vector<HuffmanSymbols> list;

//    algo.generateInitialList(list);

//    auto ite = list.begin();

//    while(ite != list.end()){
//        HuffmanSymbols &node = *ite;

//        std::cout<<node.toStr()<<'\n';

//        ite++;
//    }


//}

//void testGetLowest(){
//    char symbols[] = {'A', 'C' , 'L', 'M', 'N', 'P', '_', '.'};
//    int frequencies[] = {10, 1, 2, 2,4,   2,  6,     1};

//    vector<char> vsymbols(symbols, std::end(symbols) );
//    vector<int> vfrequencies(frequencies, std::end(frequencies));

//    HuffmanCoding codec(vsymbols, vfrequencies);

//    vector<HuffmanSymbols> simbols;

//    codec.generateInitialList(simbols);
//    vector<long> lowest = codec.getTwoLowestFreq(simbols);

//    std::for_each(lowest.begin(), lowest.end(), [](long &num){
//       std::cout<<num<<'/n';
//    });
//}

void testReadHeader(){
    std::string pathImage("test.jpg");

    try{

        JfifReader reader(pathImage);

        reader.read();


    }catch(std::exception &e){
        std::cout<<e.what();
    }


}



int main()
{

   //testInitialList();

    //testGetLowest();

    //testGenerateCodeLengths();

   // testGenerateCodes();

    testReadHeader();
    return 0;
}

