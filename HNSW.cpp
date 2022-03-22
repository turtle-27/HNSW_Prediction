#include <vector>
#include <stack>
#include <set>
#include <iostream>
using namespace std;

#define max_stack_size 5

double cosine_dist(vector<double> a, vector<double> b)
{
    int size = a.size();
    double out;
    if(size != b.size())
    {
        cout << "Dimension mismatch!" << endl;
    }
    // calculate cosine_dist
}

int findMax(stack<int> s)
{
    int m = s.top(); //initialization

    int a;

    while (!s.empty())
    {
        a = s.top();

        if (m < a)
            m = a; //Storing the maximum element in m

        s.pop(); //removing the topmost element to bring next element at the top
    }

    return m;
}

stack<<pair<int, double>> SearchLayer(vector<double> q, stack<<pair<int, double>> candidates,vector<int> indptr,vector<int> index, vector<int> level_offset,int lc, set<int> visited,vector<vector<double>> vect)
{
    stack<<pair<int, double>> top_k(candidates);
    while (candidates.size() > 0)
    {
        int ep = candidates.top();
        candidates.pop();
        int start = indptr[ep] + level_offset[lc];
        int end = indptr[ep] + level_offset[lc+1];
        for(int i = start; i< end; i++)
        {
            int px = index[i];
            if(visited.find(px) != visited.end() || px == -1)
            {
                continue;
            }
            visited.insert(px);
            int _dist = cosine_dist(q, vect[px]);
            if(_dist > findMax(top_k) and top_k.size() == max_stack_size)
            {
                continue;
            }
            top_k.push()
        }
    }
    
}