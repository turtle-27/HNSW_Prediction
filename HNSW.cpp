#include <vector>
#include <stack>
#include <set>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define k 5

double cosine_dist(vector<double> A, vector<double> B)
{
    if(A.size() != B.size())
    {
        cout << "Dimension mismatch!" << endl;
    }

    double dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
    for(unsigned int i = 0u; i < A.size(); i++) {
        dot += A[i] * B[i] ;
        denom_a += A[i] * A[i] ;
        denom_b += B[i] * B[i] ;
    }
    return 1.0 - dot / (sqrt(denom_a) * sqrt(denom_b));
}

void trim(priority_queue<pair<int, double>> top_k, int k)
{
    while(top_k.size() > k)
    {
        top_k.pop();
    }
    return;
}

priority_queue<pair<int, double>> SearchLayer(vector<double> q, priority_queue<pair<int, double>> candidates,vector<int> indptr,vector<int> index, vector<int> level_offset, int lc, set<int> visited,vector<vector<double>> vect, int k)
{
    priority_queue<pair<int, double>> top_k(candidates);
    while (candidates.size() > 0)
    {
        int ep = candidates.top();
        candidates.pop();
        int start = indptr[ep] + level_offset[lc];
        int end = indptr[ep] + level_offset[lc+1];
        for(int i = start; i < end; i++)
        {
            int px = index[i];
            if(visited.find(px) != visited.end() || px == -1)
            {
                continue;
            }
            visited.insert(px);
            int _dist = cosine_dist(q, vect[px]);
            if(_dist > top_k.top().first and top_k.size() == k)
            {
                continue;
            }
            top_k.push({ _dist, px});
            trim(top_k, k);
            candidates.push({ _dist, px});
        }
    }
    return top_k;
}


priority_queue<pair<int, double>> QueryHNSW(vector<int> q, int topk, int ep, vector<int> indptr, vector<int> index, vector<int> level_offset, int max_level, vector<vector<double>> vect, int k)
{
    priority_queue<pair<double, int>> top_k;
    top_k.push({cosine_dist(q, vect[ep]), ep});
    unordered_map<int, bool> visited;
    visited[ep] = true;
    for (int level = max_level; level >= 0; level--)
    {
        top_k = SearchLayer(q, top_k, indptr, index, level_offset, level, visited, vect, k);
    }
    return top_k;
}
