#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
#include <string>

using namespace std;
int *algo_1(vector<int> sequence, int len);
int algo_2(vector<int> seq1, int len1, vector<int> seq2, int len2);

int main() {
    int len = 0, type, num, n;
    char a;
    string line;
    vector<int> sequence;

    // receving input
    getline(cin, line);
    type = line[0] - '0'; // type can be 1 or 2 for each problem
    
    getline(cin, line);

    n = line.length();
    for(int i = 0; i < n; i++) {
        a = line[i];

        if(a == ' ')
            continue;
        else {
            num = a - '0';
            sequence.push_back(num);
            len++;
        }
    }

    if(type == 1) {
        // int *rtn_val = num_increasing_subs_size_k(sequence, len);
        int *rtn_val = algo_1(sequence, len);
        // printf de t e c, separados por um espaço, onde t é o tamanho da maior
        // subsequencia e c o numero de subsequencias com tamanho t (maximo)
        cout << rtn_val[0] << " " << rtn_val[1] << endl;
        free(rtn_val);
    }

    else if(type == 2) {
        int len2 = 0;
        vector<int> sequence2;

        while(cin >> num) {
            sequence2.push_back(num);
            len2++;
        }

        int rtn = algo_2(sequence, len, sequence2, len2);
        cout << rtn << endl;
    }
    return 0;
}

int *algo_1(vector<int> sequence, int len){
    int n_max_size = 0;
    int *rtn_vals = (int *) malloc(sizeof(int)*2); 
    // length of Longest Increasing Sequence starting at sequence[i]
    vector<int> lengthOfLIS(len, 1);
    // number of Longest Increasing Sequences of length lengthOfLIS[i] starting at sequence[i]
    vector<int> countOfLIS(len, 0);
    countOfLIS[len-1] = 1;
    for (int i = len - 1; i >= 0; i--){
        for (int j = i+1; j < len; j++){
            if (sequence[i] < sequence[j]){
                // se adicionámos 1 ao len, ir buscar as counts do len menor e somá-las
                if (lengthOfLIS[j] + 1 > lengthOfLIS[i]){
                    lengthOfLIS[i] = lengthOfLIS[j] + 1;
                    countOfLIS[i] = countOfLIS[j];
                }
                else if (lengthOfLIS[j] + 1 == lengthOfLIS[i]){
                    countOfLIS[i] += countOfLIS[j];
                }
            }
        }
        countOfLIS[i] = max(countOfLIS[i], 1);
    }
    // get first return value - size of longest subsequence which is maximum of lis
    rtn_vals[0] = *max_element(lengthOfLIS.begin(), lengthOfLIS.end());

    // get second return value - number of LIS with max size (rtn_vals[0])
    for (int i = 0; i < len; i++){
        if (lengthOfLIS[i] == rtn_vals[0]){
            n_max_size += countOfLIS[i];
        }
    }
    rtn_vals[1] = n_max_size;

    return rtn_vals;
}

int algo_2(vector<int> seq1, int len1, vector<int> seq2, int len2)
{
    // table[j] is going to store length of LCIS
    // ending with seq2[j]. We initialize it as 0,
    vector<int> table(len2, 0);

    // Traverse all elements of seq1[]
    for (int i = 0; i < len1; i++)
    {
        // Initialize current length of LCIS
        int current = 0;

        // For each element of seq1[], traverse all
        // elements of seq2[].
        for (int j = 0; j < len2; j++)
        {
            // If both the vectors have the same elements.
            // Note that we don't break the loop here.
            if (seq1[i] == seq2[j])
                if (current + 1 > table[j])
                    table[j] = current + 1;

            /* Now seek for previous smaller common
               element for current element of seq1 */
            if (seq1[i] > seq2[j])
                if (table[j] > current)
                    current = table[j];
        }
    }

    // The maximum value in table[] is out result
    int result = 0;
    for (int i = 0; i < len2; i++)
        if (table[i] > result)
           result = table[i];

    return result;
}