#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

int main() {
    int len, temp;

    // receving input array
    cin >> len;
    int sequence[len];
    for (int i = 0; i < len; i++){
        cin >> temp;
        sequence[i] = temp;
    }
    // copying the array and ordering it
    int ordered_seq [len];
    for(int i=0; i<len; ++i)
        ordered_seq[i] = sequence[i];
    sort(ordered_seq, ordered_seq + len);

    // printing out the ordered sequence
    for(auto e : ordered_seq)
        cout << e << ' ';
    cout << '\n';

    
    return 0;
}

// function that gets array as input and its output is an array in increasing order only

// function that compares ordered array with another array (can be different size)
// and outputs biggest common sequence