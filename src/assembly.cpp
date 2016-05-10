// define functions within MyClass class
#include "assembly.h"

// include dependencies
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> Assembly::getData()
    {
    // Declare variables
    string fileName, tmpstring;
    vector<string> data;
    vector<string>::iterator itStr; 
    // Ask for filename
    cout << "Please enter filename:" << endl;
    // get file name from user
    cin >> fileName;
    // ifstream object to get information from a file
    ifstream myfile;
    // convert filename to c_str, then open
    myfile.open(fileName.c_str());
    // get data from file
    while(!myfile.eof())
        {
        // get current line into temporary string
        myfile >> tmpstring;
        // add tmpstring to vector of strings
        data.push_back(tmpstring);
        }
    // close file
    myfile.close();
    // remove last entry of data, because push_back always duplicates last entry
    data.pop_back();
    // display data
    for (itStr=data.begin(); itStr!=data.end(); itStr++)
        {
        cout << *itStr << endl;
        }
    return(data);
    }


string Assembly::assembleData(vector<string> data)
    {
    // Declare variables
    vector<string>::iterator itStr,itStr2;
    vector<int> matchLengths;
    vector<int> itInt;
    int flag=0;
    string outString,mergeString, checkString;
    int readLength, maxMatch=0;
    // Set iterator to first element of data
    itStr = data.begin();
    // Make outString the first string contained in data
    outString = *itStr;
    // Get read length
    readLength = outString.length();
    // Remove first string from data
    data.erase(itStr);
    // Repeat the following until no matches can be found
    do {
        // Exit the loop if there are no more reads to assemble
        if(data.empty()==true) goto out;
        // For each data string, find the longest match with outString
        // Loop over all elements in vector
        for(itStr=data.begin(); itStr!=data.end(); itStr++)
            {
            // Loop over the length of a read
            for(int i=readLength; i>0; i--)
                {
                checkString = *itStr;
                // Last i characters of outString and first i elements of data[x] are the same
                if(outString.substr(outString.length()-i,i)==checkString.substr(0,i))
                    {
                    matchLengths.push_back(i);
                    // if the match length is bigger than the current best match
                    if(i>=maxMatch) 
                        {
                        // Update best match
                        maxMatch = i; 
                        // Get best match string
                        itStr2 = itStr;
                        // Update flag to indicate a right hand side match
                        flag = 1;
                        }
                    break;
                    }
                }
            // Loop again, to check other side of the read
            for(int i=1; i<readLength+1; i++)
                {
                checkString = *itStr;
                // First i characters of outString and last i elements of data[x] are the same
                if(outString.substr(0,i)==checkString.substr(checkString.length()-i,i))
                    {
                    matchLengths.push_back(i);
                    // if the match length is bigger than the current best match
                    if(i>=maxMatch) 
                        {
                        // Update best match
                        maxMatch = i; 
                        // Get best match string
                        itStr2 = itStr;
                        // Update flag to indicate a right hand side match
                        flag = 2;
                        }
                    break;
                    }
                }
            }
         // Get the maximum match length
         maxMatch = *max_element(matchLengths.begin(),matchLengths.end());
         // String to merge with outString
         mergeString = *itStr2;
         cout << "Merge string: " << mergeString << " Current out string: " << outString << endl;
         // Add chars of mergeString to outString
         if(flag==1)
            {
            outString = outString.append(mergeString.substr(maxMatch,readLength-maxMatch));
            }
         else if(flag==2)
            {
            outString = outString.insert(0,mergeString.substr(0,readLength-maxMatch));
            }
         // Remove matched read from list of reads
         data.erase(itStr2);
       } while (maxMatch>0);

    out:

    return(outString);
    }


