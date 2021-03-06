#include <cstring>
#include <iostream>
#include <string>

#include <alignment/bwt/BWT.hpp>
#include <alignment/suffixarray/SuffixArray.hpp>
#include <alignment/suffixarray/SuffixArrayTypes.hpp>

int main(int argc, char* argv[])
{

    std::string bwtFileName, saFileName;
    if (argc < 3) {
        std::cout << "usage: bwt2sa bwtfile safile " << std::endl;
        std::exit(EXIT_FAILURE);
    }
    bwtFileName = argv[1];
    saFileName = argv[2];

    Bwt<PackedDNASequence, FASTASequence> bwt;
    DNASuffixArray suffixArray;

    bwt.Read(bwtFileName);
    suffixArray.AllocateSuffixArray(bwt.bwtSequence.length - 1);
    SAIndex index;
    for (index = 1; index < bwt.bwtSequence.length + 1; index++) {
        suffixArray.index[index - 1] = bwt.Locate(index);
    }
    suffixArray.Write(saFileName);
}
