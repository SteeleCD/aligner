// main
#include "assembly.h"
#include "centralDogma.h"
#include <vector>
#include <string>

using namespace std;

int main()
    {
    vector<string> reads;
    string dnaseq;
    Assembly assembly;
    // get reads from file
    reads = assembly.getData();
    // assemble reads
    dnaseq = assembly.assembleData(reads);
    centralDogma centDog;
    string rnaseq, protein, ORF;
    cout << "DNA Sequence: \n";
    centDog.PrintSequence(dnaseq);
    // convert to RNA
    rnaseq = centDog.DNAtoRNA(dnaseq);
    cout << "RNA Sequence: \n";
    centDog.PrintSequence(rnaseq);
    // convert to protein
    protein = centDog.RNAtoProtein(rnaseq);
    cout << "Protein Sequence: \n";
    centDog.PrintSequence(protein);
    // estimate ORFs
    ORF = centDog.FindORFS(protein);
    cout << "Potential ORF: \n";
    centDog.PrintSequence(ORF);
    return 0;
    }
