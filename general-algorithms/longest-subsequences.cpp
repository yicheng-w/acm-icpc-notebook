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

template <typename T>
vector<T> longest_increasing_subsequence(vector <T> &n) //returns LIS in O(NlogN) time, and O(N) memory where N is the size of the input vector
{
    int sz = n.size();
    if (sz == 0)
    {
        return {};
    }
    vector <pair<T, int>> lis; //binary sorted list containing {value, index} pairs
    vector <int> prev(sz, -1); //list containing previous index for each element in n


    int maxLen = 0; //len is 0-indexed
    lis.PB({n[0], 0});

    for (int i = 1; i < sz; i++)
    {
        int len = lower_bound(all(lis), make_pair(n[i], i), [](pair<T, int> left, pair <T, int> right) -> bool {return left.first < right.first;}) - lis.begin(); // < strictly inc, > strictly dec, <= non-dec, >= non-inc

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
    vector <T> sol(++maxLen); //we want 1-indexed (actual) maxLen now

    REP(i, maxLen)
    {
        sol[maxLen - i - 1] = n[currInd];
        currInd = prev[currInd];
    }

    return sol;
}

void tester()
{
    int n;
    int t;
    cin>>n;
    vector <int> num_list(n);
    REP(i, n)
    {
        cin>>t;
        num_list[i] = t;
    }

    auto test = longest_increasing_subsequence(num_list);
    for (auto elem: test)
    {
        cout<<elem<<" ";
    }
    cout<<newl;

}


int main()
{
    //freopen("/Users/Mac/Desktop/input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);

    tester();


    return 0;
}
