//==================================
// define class functions

//================================
// include guard
#ifndef __CENTRALDOGMA_h_INCLUDED__  // if myclass.h has not been included
#define __CENTRALDOGMA_H_INCLUDED__  // #define this so the compiler knows it has been included

//================================
// forward declared dependencies

//=================================
// included dependencies
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>


class centralDogma
    {
    public:
        std::string GetSequence ();
        void PrintSequence (std::string string);
        std::string DNAtoRNA (std::string DNAseq);
        std::string GetCodon (std::string RNAseq, int position);
        char NucleotideToAminoAcid (std::string RNAsequence, int pos);
        std::string RNAtoProtein (std::string RNASEQ);
        std::string FindORFS (std::string protein);
        int StopTotal (std::string seq);
    };

#endif  // __MYCLASS_H_INCLUDED__

    
