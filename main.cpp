// main

#include "align.h"

#include <vector>

#include <string>



using namespace std;



int main()

    {

    vector<string> reads;

    Align align;

    reads = align.getData();

    align.alignData(reads);

    return 0;

    }
