#include <vector>

vector <int> sieve(int n)
{
  int visited[n];
  vector <int> sol;
  memset(visited, 0, sizeof(visited));
  for (int i = 2; i * i < n; i ++)
  {
    if (visited[n] == 0)
    {
      sol.push_back(i);
    }
    for (int j = i * i; j < n; j+=i)
    {
      visited[j] = 1;
      
    }
  }
  
  return sol;

}
