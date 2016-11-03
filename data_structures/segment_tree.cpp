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
#include <unordered_set>
#include <unordered_map>
#include <cmath>

#define REP(i, x) for(int i = 0; i < x; i++)
#define REPS(i, s, x) for(int i = s; i < x; i++)
#define newl '\n'
#define dbg cerr
#define ll long long
#define dd pair <double, double>
#define ii pair<int, int>
#define iii pair <ii, int>
#define iiii pair<ii, ii>
#define vi vector <int>
#define vii vector <ii>
#define vs vector <string>
#define US unordered_set
#define UM unordered_map
#define PB push_back
#define INF 1000000008
#define EPS .0000001
#define all(x) x.begin(), x.end()

using namespace std;

template <typename T>
class segment_tree
{
    private:
        vector <T> st;
        int sz; //num of elements in lowest row, not number of nodes in tree
        T init;

        static int operation(T a, T b)
        {
            return a + b;
        }

    public:


        segment_tree<T>()
        {
            this -> sz = 0;
            vector <T> st;
        }

        void build(vector <T> &elem, T init)
        {
            this -> sz = elem.size();
            this -> init = init;

            st.resize(2 * sz);
            for (int i = sz; i < 2 * sz; i++)
            {
                this -> st[i] = elem[i - sz];            }

            for (int i = sz - 1; i > 0; i--)
            {
                this -> st[i] = operation(this -> st[2 * i], this -> st[(2 * i) | 1]);
            }
        }

        void build() //if for some reason you want to build entirely after changing something
        {
            for (int i = sz - 1; i > 0; i--)
            {
                st[i] = operation(st[2 * i], st[(2 * i) | 1]);
            }
        }

        void modify(int p, int value) //set position p to value
        {
            st[p + sz] = value;

            for (p = p + sz; p > 1; p /= 2)
            {
                st[p/2] = operation(st[p], st[p^1]); //p^1 is always the the other element in the 'block'
            }

        }

        T query(int l, int r) //query on range [l, r] inclusive, interval has to be 1-indexed
        {
            T res = init;
            for (l = l + sz, r = r + sz; l <= r; l /= 2, r /= 2)
            {
                if (l&1) //if l is odd, include it in sum and move right
                {
                    res = operation(st[l], res);
                    l++;
                }
                if (!(r&1)) // if r is even, include in sum and move left
                {
                    res = operation(res, st[r]);
                    r--;
                }
            }
            return res;
        }

        T getVal(int index)
        {
            return st[index];
        }


};

void tester()
{
    int n, m;
    segment_tree <int> stImpl = segment_tree<int>();

    cin>>n;
    vector <int> nums(n);
    REP(i, n)
    {
        cin>>nums[i];
    }
    stImpl.build(nums, 0);

    cin >> m;
    int l, r;
    REP(i, m)
    {
        cin>>l>>r;
        cout<<stImpl.query(l, r)<<newl;
    }
    cout<<"hi"<<newl;
    cin>>l>>r;
    stImpl.modify(l, r);

    cin>>m;
    REP(i, m)
    {
        cin>>l>>r;
        cout<<stImpl.query(l, r)<<newl;
    }
}

