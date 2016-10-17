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
class longest_subsequence
{
    struct comparator
    {
        string type;
        comparator(string type)
        {
            this -> type = type;
        }
        bool operator()(pair <T, int> left, pair <T, int> right)
        {
            if (type == "strictly_dec")
            {
                return left.first > right.first;
            }
            else if (type == "non_dec")
            {
                return left.first <= right.first;
            }
            else if (type == "non_inc")
            {
                return left.first >= right.first;
            }
            else //default case is strictly increasing
            {
                return left.first < right.first;
            }

        }
    };

    private:
        vector <T> sequence;
        string comparator_type = "";

    public:
        longest_subsequence(string comparator_type)
        {
            this -> comparator_type = comparator_type;
        }

        void setType(string comparator_type)
        {
            this -> comparator_type = comparator_type;
        }

        void setSequence(vector <T> sequence)
        {
            this -> sequence = sequence;
        }

        vector <T> getSequence()
        {
            return this -> sequence;
        }


        vector <T> compute_subsequence()
        {
            int sz = sequence.size();
            if (sz == 0)
            {
                return {};
            }

            vector <pair<T, int>> value_index;
            vi prev(sz, -1);

            int maxLen = 0;
            value_index.PB({sequence[0], 0});

            longest_subsequence::comparator compareObj(comparator_type);

            for (int i = 1; i < sz; i++)
            {
                int len = lower_bound(all(value_index), make_pair(sequence[i], i), compareObj) - value_index.begin();
                if (len >= value_index.size())
                {
                    value_index.PB({sequence[i], i});
                }
                else
                {
                    value_index[len] = {sequence[i], i};
                }
                prev[i] = value_index[len - 1].second;
                maxLen = max(maxLen, len);
            }

            int currInd = value_index[maxLen].second;
            vector <T> subsequence(++maxLen);

            REP(i, maxLen)
            {
                subsequence[maxLen - i - 1] = sequence[currInd];
                currInd = prev[currInd];
            }

            return subsequence;
        }

        int compute_length()
        {
            int sz = sequence.size();
            if (sz == 0)
            {
                return 0;
            }

            vector <pair<T, int>> value_index;

            int maxLen = 0;
            value_index.PB({sequence[0], 0});

            longest_subsequence::comparator compareObj(comparator_type);

            for (int i = 1; i < sz; i++)
            {
                int len = lower_bound(all(value_index), make_pair(sequence[i], i), compareObj) - value_index.begin();
                if (len >= value_index.size())
                {
                    value_index.PB({sequence[i], i});
                }
                else
                {
                    value_index[len] = {sequence[i], i};
                }
                maxLen = max(maxLen, len);
            }
            return ++maxLen;
        }

        void tester()
        {
            int n;
            cin>>n;
            vector <T> num_list(n);
            REP(i, n)
            {
                cin>>num_list[i];
            }

            setSequence(num_list);

            for (T elem: compute_subsequence())
            {
                cout<<elem<<" ";
            }
            cout<<newl;
            setType("non_dec");
            cout<<compute_length()<<newl;
        }
};
