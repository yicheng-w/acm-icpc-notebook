#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <stack>
#include <queue>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <cstdlib>

#define REP(i, x) for(int i = 0; i < x; i++)
#define REPS(i, s, x) for(int i = s; i < x; i++)
#define newl '\n'
#define dbg cerr
#define ll long long
#define ii pair<int, int>
#define iii pair <ii, int>
#define iiii pair<ii, ii>
#define vi vector <int>
#define vii vector <ii>
#define vs vector <string>
#define PB push_back
#define INF 1000000008
#define all(x) x.begin(), x.end()

using namespace std;

vi longest_increasing_subsequence(vi &n) //returns LIS in O(NlogN) time, and O(N) memory where N is the size of the input vector
{
    int sz = n.size();
    if (sz == 0)
    {
        return {};
    }
    vii lis; //binary sorted list containing {value, index} pairs
    vi prev(sz, -1); //list containing previous index for each element in n


    int maxLen = 0; //len is 0-indexed
    lis.PB({n[0], 0});

    for (int i = 1; i < sz; i++)
    {
        int len = lower_bound(all(lis), make_pair(n[i], i), [](ii left, ii right) -> bool {return left.first < right.first;}) - lis.begin(); // < strictly inc, > strictly dec, <= non-dec, >= non-inc
        //cout<<len<<newl;
        if (len >= lis.size())
        {
            lis.PB({n[i], i});
        }
        else
        {
            lis[len] = {n[i], i};
        }
        prev[i] = lis[len - 1].second;
        maxLen = max(maxLen, len);
    }

    int currInd = lis[maxLen].second;
    vi sol(++maxLen); //we want 1-indexed (actual) maxLen now

    REP(i, maxLen)
    {
        sol[maxLen - i - 1] = n[currInd];
        currInd = prev[currInd];
    }

    return sol;
}

int longest_increasing_subsequence_length(vi &n) //returns length of LIS in O(NlogN) time and O(N) memory
{
    vi lis;
    int maxLen = 0;
    for (int i: n)
    {
        int len = lower_bound(lis.begin(), lis.end(), i, [](int left, int right) -> bool {return left < right;}) - lis.begin(); // < strictly inc, > strictly dec, <= non-dec, >= non-inc
        if (len >= lis.size())
        {
            lis.PB(i);
        }
        else
        {
            lis[len] = i;
        }
        maxLen = max(maxLen, len);
        lis[len] = i;
    }
    return maxLen + 1; //len was 0-indexed
}
