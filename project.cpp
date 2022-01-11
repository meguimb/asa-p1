#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>

using namespace std;
int *num_of_largest_increasing_seqs(vector<int> sequence, int len);
int size_of_largest_common_inc_subseq(vector<int> seq1, int len1, vector<int> seq2, int len2);

int main() {
    int len = 0, type, num = 0, n;
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

        if(a == ' ') {
            sequence.push_back(num);
            len++;
            num = 0;
        }
        else
            num = num * 10 + (a - '0');
        if(i + 1 == n) {
            sequence.push_back(num);
            len++;
        }
    }

    if(type == 1) {
        // int *rtn_val = num_increasing_subs_size_k(sequence, len);
        int *rtn_val = num_of_largest_increasing_seqs(sequence, len);
        // printf de t e c, separados por um espaço, onde t é o tamanho da maior
        // subsequencia e c o numero de subsequencias com tamanho t (maximo)
        cout << rtn_val[0] << " " << rtn_val[1] << endl;
        free(rtn_val);
    }

    else if(type == 2) {
        int len2 = 0;
        vector<int> sequence2;

        unordered_set<int> set_seq(sequence.begin(), sequence.end());
        while(cin >> num) {
            if (set_seq.find(num) != set_seq.end()) {
                sequence2.push_back(num);
                len2++;
            }
        }

        int rtn = size_of_largest_common_inc_subseq(sequence, len, sequence2, len2);
        cout << rtn << endl;
    }
    return 0;
}

int *num_of_largest_increasing_seqs(vector<int> sequence, int len){
    int n_max_size = 0;
    int *rtn_vals = new int(2); 
    // length of Longest Increasing Sequence starting at sequence[i]
    vector<int> contador_seq_i(len, 1);
    // number of Longest Increasing Sequences of length contador_seq_i[i] starting at sequence[i]
    vector<int> tamanho_i(len, 0);
    tamanho_i[len-1] = 1;
    for (int i = len - 1; i >= 0; i--){
        for (int j = i+1; j < len; j++){
            if (sequence[i] < sequence[j]){
                // se adicionámos 1 ao len, ir buscar as counts do len menor e somá-las
                if (contador_seq_i[j] + 1 > contador_seq_i[i]){
                    contador_seq_i[i] = contador_seq_i[j] + 1;
                    tamanho_i[i] = tamanho_i[j];
                }
                else if (contador_seq_i[j] + 1 == contador_seq_i[i]){
                    tamanho_i[i] += tamanho_i[j];
                }
            }
        }
        tamanho_i[i] = max(tamanho_i[i], 1);
    }
    // get first return value - size of longest subsequence which is maximum of lis
    rtn_vals[0] = *max_element(contador_seq_i.begin(), contador_seq_i.end());

    // get second return value - number of LIS with max size (rtn_vals[0])
    for (int i = 0; i < len; i++){
        if (contador_seq_i[i] == rtn_vals[0]){
            n_max_size += tamanho_i[i];
        }
    }
    rtn_vals[1] = n_max_size;

    return rtn_vals;
}

int size_of_largest_common_inc_subseq(vector<int> seq1, int len1, vector<int> seq2, int len2)
{
    vector<int> len_subseq(len2, 0);

    for (int i = 0; i < len1; i++)
    {
        int current = 0;

        for (int j = 0; j < len2; j++)
        {
            if ((seq1[i] == seq2[j]) && (current + 1 > len_subseq[j]))
                len_subseq[j] = current + 1;

            if ((seq1[i] > seq2[j]) && (len_subseq[j] > current))
                current = len_subseq[j];
        }
    }

    int result = 0;
    for (int i = 0; i < len2; i++)
        if (len_subseq[i] > result)
           result = len_subseq[i];

    return result;
}
