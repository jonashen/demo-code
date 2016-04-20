#include <vector>
#include <iostream>

using namespace std;

template <class T>
void merge(vector<T>& arr, int l, int m, int r, string order)
{
    int i, j, k; // index integers
    int lnum = m - l + 1; // # of values on left side
    int rnum = r - m; // # of values on right side
    
    vector<T> L, R; // temp vectors
    
    for (i = 0; i < lnum; i++) // copy data into temp vector L
        L.push_back( arr[l + i] );
    
    for (j = 0; j < rnum; j++) // copy data into temp vector R
        R.push_back( arr[m + j + 1] );
    
    i = 0, j = 0, k = l; // k = l finds index of original vector
    
    while (i < lnum && j < rnum) // compares first two values of each vector
    {
        if (order == "ascend")
        {
            if (L[i] <= R[j]) // use value from temp vector L
            {
                arr[k] = L[i];
                i++;
            }
            
            else
            {
                arr[k] = R[j]; // use value from temp vector R
                j++;
            }
            
            k++; // increment index of original vector
        }
        
        else
        {
            if (L[i] > R[j]) // use value from temp vector L
            {
                arr[k] = L[i];
                i++;
            }
            
            else
            {
                arr[k] = R[j]; // use value from temp vector R
                j++;
            }
            
            k++; // increment index of original vector
        }
    }
    
    while (i < lnum) // ensures rest of L vector's elements are copied over
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < rnum) // ensures rest of R vector's elements are copied over
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template <class T, class Comparator>
void mergeSort (vector<T>& myvector, Comparator comp)
{
    comp(myvector);
}

template <class T>
void mSort(vector<T>& arr, int l, int r, string order)
{
    if (l < r)
    {
        int m = (l+r)/2;
        
        // Sort first and second halves
        mSort(arr, l, m, order);
        mSort(arr, m + 1, r, order);
        merge(arr, l, m, r, order);
    }
}


template <class T>
struct AscendSort {
    void operator() (vector<T>& myvector)
    {
        mSort(myvector, 0, myvector.size() - 1, "ascend" );
    }
};

template <class T>
struct DescendSort {
    void operator() (vector<T>& myvector)
    {
        mSort(myvector, 0, myvector.size() - 1, "descend" );
    }
};

/*
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
*/