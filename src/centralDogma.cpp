#include "centralDogma.h"

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

// Extract the sequence to be used from a file
string centralDogma::GetSequence () {
  ifstream sequencefile("sequence.txt");
  string sequence;
  if (sequencefile.is_open())
    {
      getline (sequencefile, sequence);
      return sequence;
    }
  else cout << "Could not open sequence file";
}


// Print a string to the screen
void centralDogma::PrintSequence (string string) {
  cout << string << endl;
}

// Convert the DNA sequence into its mRNA sequence
string centralDogma::DNAtoRNA (string DNAseq) {
  char RNASeq[DNAseq.length()];
  char * p1 = RNASeq;
  for (int i=0; i<DNAseq.length(); i++)
    {
      if (DNAseq[i]=='A') *p1='U', p1++;
      else if (DNAseq[i]=='T') *p1='A', p1++;
      else if (DNAseq[i]=='C') *p1='G', p1++;
      else if (DNAseq[i]=='G') *p1='C', p1++;
      else cout << "Sequence is not a DNA sequence";
        }
  RNASeq[DNAseq.length()] = '\0';
  string RNAseq(RNASeq);
  return RNAseq;
}

// Split the RNA sequence into seperate codons
string centralDogma::GetCodon (string RNAseq, int position) {
  string codon;
      codon = RNAseq.substr(position, 3);
      return codon;
}

// Convert a nucleotide triplet into an amino acid using reference file
char centralDogma::NucleotideToAminoAcid (string RNAsequence, int pos) {
  string RNA, RNAsubstring;
  char AA;
  RNAsubstring = GetCodon(RNAsequence, pos);
  ifstream RefFile("data/RNAtoProtein.txt");
  if (RefFile.is_open())
    {
      while (RefFile >> RNA >> AA)
	{
	  if (RNA==RNAsubstring) return AA;
	}
    } 
  else cout << "Could not open reference file"; 
}

// Change the whole RNA sequence into a protein sequence
string centralDogma::RNAtoProtein (string RNASEQ) {
  int aalength = (RNASEQ.length() / 3);
  char protein [aalength];
  for (int rnapos=0, aapos=0; rnapos<RNASEQ.length(), aapos<aalength; rnapos+=3, aapos++)
    {
      protein[aapos] = NucleotideToAminoAcid(RNASEQ, rnapos);
    }
  protein[aalength]='\0';
  string Protein(protein);
  return Protein;
}

// Find possible open reading frames
string centralDogma::FindORFS (string protein) {
  vector<int> Mpos; 
  vector<int> STOPpos;
  size_t foundM, foundSTOP;
  string ORF1, ORF2;
  int mpos;
  foundM = protein.find('M');
  foundSTOP = protein.find('*');

  if (foundM!=string::npos) 
	{
	Mpos.push_back(foundM);
	} else {
	return "none";
	}
  if (foundSTOP!=string::npos) 
	{
	STOPpos.push_back(foundSTOP);
	} else {
	return "none";
	}
  foundM = protein.find('M', foundM+1);
  foundSTOP = protein.find('*', foundSTOP+1); 
  if (foundM!=string::npos) Mpos.push_back(foundM);
  if (foundSTOP!=string::npos) STOPpos.push_back(foundSTOP);
  ORF1=protein.substr(*min_element(Mpos.begin(), Mpos.end()), (*min_element(STOPpos.begin(), STOPpos.end())-*min_element(Mpos.begin(), Mpos.end())));
  ORF2=protein.substr(*max_element(Mpos.begin(), Mpos.end()), (*max_element(STOPpos.begin(), STOPpos.end())-*max_element(Mpos.begin(), Mpos.end())));
  return ORF2;
}

// predict frame
int centralDogma::predictFrame (string RNAseq)
	{
	string protein;
	int nStops, minStops, frame;
	for(int i=0; i<3; i++)
		{
		protein = RNAtoProtein(RNAseq.substr(i));
		nStops = StopTotal(protein);
		if(i==0)
			{
			frame=i;
			minStops = nStops;
			} else {
			if(nStops<minStops)
				{
				frame = i;
				minStops = nStops;
				}
			}
		}
	cout << "Estmimated frame: " << frame << " with " << minStops << " stops\n";
	return frame;
	}

int centralDogma::StopTotal (string seq)
{
  int NumStops = 0;
  for (int i=0; i<seq.length(); i++)
    {
      if (seq[i]=='*') NumStops++;
    }
  return NumStops;
}
