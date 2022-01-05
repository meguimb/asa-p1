#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;
int *largest_seq_size(vector<int> arr1, int len);
int *num_increasing_subs_size_k(vector<int> sequence, int len);
int *algo_2(vector<int> sequence, int len);

int main() {
    int len=0, type, a;
    vector<int> sequence, ordered_seq;

    // receving input array
    cin >> type; // type can be 1 or 2 for each problem

    while(cin>>a){
        sequence.push_back(a);
        len++;
    }

    // int *rtn_val = num_increasing_subs_size_k(sequence, len);
    int *rtn_val = algo_2(sequence, len);
    // printf de t e c, separados por um espaço, onde t é o tamanho da maior
    // subsequencia e c o numero de subsequencias com tamanho t (maximo)
    printf("%d %d\n", rtn_val[0], rtn_val[1]);
    free(rtn_val);
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

int *num_increasing_subs_size_k(vector<int> sequence, int len){
    // first value: size of longest subsequence
    // second value: number of subsequences with that size
    int *rtn_vals = (int *) malloc(sizeof(int)*2); 
    int count_subs = 0;
    vector<int> lis(len, 1); // initialize all longest increasing subsequences to 1 (each number is its own sequence)
    vector<int> count(len, 1); // number of 

    if (len <= 1) { 
        return NULL; 
    }

    for (int i = 1; i < len; i++){
        for (int j = 0; j < i; j++){
            if (sequence[j] < sequence[i]){
                if (lis[j] >= lis[i]){
                    lis[i] = lis[j] + 1;
                    count[i] = count[j];
                } 
                else if (lis[i] == lis[j] + 1){
                    count[i] += count[j]; 
                }
            }
        }
    }
    
    // get first return value - size of longest subsequence which is maximum of lis
    rtn_vals[0] = *max_element(lis.begin(), lis.end());

    // get second return value - number of subsequences with max size (first return value)
    for (int i = 0; i < len; i++){
        if (lis[i] == rtn_vals[0]){
            count_subs += count[i];
        }
    }
    rtn_vals[1] = count_subs;

    // return 
    return rtn_vals;
}

int *algo_2(vector<int> sequence, int len){
    int *rtn_vals = (int *) malloc(sizeof(int)*2); 
    // length of Longest Increasing Sequence starting at sequence[i]
    vector<int> lengthOfLIS(len, 1);
    // number of Longest Increasing Sequences of length lengthOfLIS[i] starting at sequence[i]
    vector<int> countOfLIS(len, 1);

    for (int i = len - 1; i >= 0; i--){
        for (int j = i+1; j < len; j++){
            if (sequence[i] < sequence[j]){
                lengthOfLIS[i] = max(1 + lengthOfLIS[j], lengthOfLIS[i]);
                countOfLIS[i] = min(countOfLIS[i+1]+1, countOfLIS[j]+1);
                //countOfLIS[i] = max(countOfLIS[i], min(countOfLIS[i]+1, countOfLIS[j]));
            }
        }
    }

    // get first return value - size of longest subsequence which is maximum of lis
    rtn_vals[0] = *max_element(lengthOfLIS.begin(), lengthOfLIS.end());
    rtn_vals[1] = *max_element(countOfLIS.begin(), countOfLIS.end());

    // return 
    return rtn_vals;
}