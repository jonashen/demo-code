#include "msort.h"
#include <vector>
#include <iostream>


int main()
{
    vector<string> a;
    a.push_back("a");
    a.push_back("c");
    a.push_back("b");
    a.push_back("z");
    a.push_back("t");
    a.push_back("c");
    
    cout<<"sorting using merge sort"<<endl;
    
    AscendSort<string> nah;
    mergeSort(a, nah);
    
    cout<<"sorted form"<<endl;
    for(int i=0; i < a.size() ;i++)
    {
        cout<<"a["<<i<<"]="<<a[i]<<endl;
    }
    return 0;
}
