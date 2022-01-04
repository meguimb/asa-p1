#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;
int *largest_seq_size(vector<int> arr1, int len);

int main() {
    int len=0, type, a;
    vector<int> sequence;

    // receving input array
    cin >> type; // type can be 1 or 2 for each problem

    while(cin>>a){
        sequence.push_back(a);
        len++;
    }

    // copying the array and ordering it
    int ordered_seq [len];
    for(int i=0; i<len; ++i)
        ordered_seq[i] = sequence[i];
    sort(ordered_seq, ordered_seq + len);

    // printing out the ordered sequence
    for(int i = 0; i < len; i++){
        cout << sequence[i] << ' ';
    }

    int *lis = largest_seq_size(sequence, len);
    for(int i = 0; i < len; i++){
        cout << lis[i] << ' ';
    }
    cout << '\n';
    free(lis);
    return 0;
}

// function that compares ordered array with another array (can be different size)
// and outputs biggest common sequence
int largest_common_seq(vector<int> arr1, vector<int> ordered_arr, int len){
    for (int i = 0; i < len; i++){
        if (i>=1 && ordered_arr[i]==ordered_arr[i+1]){continue; }
        else{
            // TODO
            return 0;
        }
    }
    return 1;
}

int *largest_seq_size(vector<int> arr1, int len){
    int *largest_seq_int = (int *) malloc(sizeof(int)*len);
    for (int i = 0; i < len; i++){
        printf(".");
        largest_seq_int[i] = 1;
    }
    for (int i = 0; i < len; i++){
        for (int j = 0; j < i; j++){
            if (arr1[i] > arr1[j]){
                largest_seq_int[i] = max(largest_seq_int[i], largest_seq_int[j] + 1);
            }
        }
    }
    return largest_seq_int;
}