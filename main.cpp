
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <bitset>
#include <sstream>

#include "jfifreader.h"

#include "huffmancoding.h"





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

void testCodeLenFromCounts(){

    std::vector<char> symbols;
    std::vector<int> freq;

    HuffmanCoding coding(symbols, freq);

    char counts[6] = {0, 1, 0, 2, 3, 2};
    std::vector<char> vcounts;

    vcounts.push_back(0);
    vcounts.push_back(1);
    vcounts.push_back(0);
    vcounts.push_back(2);
    vcounts.push_back(3);
    vcounts.push_back(2);
    std::vector<HuffmanSymbol> outsimbols;

    coding.generateCodeLengthsFromCounts(vcounts, outsimbols, true);

    for(size_t i = 0; i < outsimbols.size(); i++){
        std::cout<<i<<" : "<<outsimbols[i].codeLength<<'\n';
    }

}

void testReadBits(){
	char byte1 = 255;
	char byte2 = 1;

	vector<char> arr;

	arr.push_back(byte2);
	arr.push_back(byte1);

	vector<char> t1;
	vector<int> t2;
	HuffmanCoding a(t1, t2);
	unsigned long size = arr.size()*8;

	for(unsigned long i = 0; i < size; i++){
		int bit = a.readBit(i, arr);
		std::cout<<bit;
	}
}

void testReadHeader(){
    /*std::string pathImage("test.jpg");

    try{

        JfifReader reader(pathImage);

        reader.read();


    }catch(std::exception &e){
        std::cout<<e.what();
    }*/

	testReadBits();


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

