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

class trie{
    struct counts
    {
        int pc = 0; //prefix count - num of words that begin with current node
        bool we = false; //word end - whether current node is the end of a word
    };

    private:
        map <pair <char, int>, int> t; //maps (x, y) to z, where x is the value of and y is the parent of node z
        map <int, counts> tc; //maps x to y where y contains the counts of node x
        int nn = 0; //number of nodes that exist in the trie

    public:
        map <pair <char, int>, int> getTrie()
        {
            return t;
        }

        map <int, counts> getTotalCounts()
        {
            return tc;
        }

        /* input: string to be inserted
        *  Runs in O(|S| * log(N)) time; |S| = length of the string being inserted; N = number of nodes in the trie
        *  output: true or false depending on whether s is in trie or not respectively
        */
        void addWord(string s) //
        {
            int v = 0;
            tc[0].pc += 1;
            for (char ch: s)
            {
                if (t.count({ch, v}) == 0) //if there is not an edge that goes from node v to a node with ch, create one
                {
                    t[{ch, v}] = ++nn;
                }
                v = t[{ch, v}];
                tc[v].pc += 1;
            }
            tc[v].we = true;
        }

        /* input: string that needs to be found in trie
        *  Runs in O(|S| * log(N)) time; |S| = length of string that's being found; N = number of nodes in trie
        *  output: true or false depending on whether s is in trie or not respectively
        */
        bool findWord(string s) //finds word in O(|S| * log(N)) time
        {
            int v = 0;
            for(char ch: s)
            {
                if (t.count({ch, v}) == 0)
                {
                    return false;
                }
                v = t[{ch, v}];
            }
            return tc[v].we;
        }
};

/* input: insert n words into trie, then make m queries
*  output: whether any of the queries are found or not
*/
void tester()
{
    int n, m;
    string tempWord;
    trie timpl = trie();

    cin>>n;
    cin.get();

    REP(i, n)
    {
        getline(cin, tempWord);
        timpl.addWord(tempWord);
    }

    cin>>m;
    cin.get();

    REP(i, m)
    {
        getline(cin, tempWord);
        cout<<(timpl.findWord(tempWord) ? "found" : "not found")<<newl;
    }
}
