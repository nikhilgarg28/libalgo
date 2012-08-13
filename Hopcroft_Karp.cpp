
#include <iostream>
#include <cstdio>

/*
* Author : Nikhil Garg
* Date   : 2010-12-27
* Hopcrof Karp algorithm.
* Finds maximum matching in a graph in time O(E sqrt V). In practice has much better performance.
* Just copy class HCK, include <vector> and <algorithm> and let namespace be
* std. Look at sample usage in main for details
* 
*/

#include<vector>
#include<algorithm>
using namespace std;

class HCK
{
    int N,M;
    vector<int> matchL, matchR, distL, distR, Q;
    vector<vector<int> > adjList;
    int qf, qb;

    inline bool bfs()
    {
        fill(distL.begin(), distL.end(), -1);
        fill(distR.begin(), distR.end(), -1);
        qf = qb = 0;
        
        for(int i = 0; i < N; i++)
            if( matchL[i] == -1)
                distL[i] = 0, Q[qb++] = i;
            
        bool found = false;
        while( qf < qb)
        {
            int u = Q[qf++];
            for(int i = 0; i < adjList[u].size(); i++)
            {
                int v = adjList[u][i];
                if( distR[v] >= 0)	continue;		// Seen vertex
                    distR[v] = 1 + distL[u];
                if( matchR[v] == -1)	// Unmatched vertex, aug path exists. Don't push vertices anymore on queue
                    found  = true;
                else
                {
                    Q[qb++] = matchR[v];
                    distL[matchR[v]] = 1 + distR[v];
                }
            }
        }
        return found;
    }


    inline bool dfs(int u)
    {
        for(int i= 0; i < adjList[u].size(); i++)
        {
            int v = adjList[u][i];
            if( distR[v] == distL[u] + 1)			// u -> v is a forward edge
            {
                distR[v]  = -1;				        // Mark this vertex as seen.
                if( matchR[v] == -1 || dfs(matchR[v]) )
                {
                    matchL[u] = v;	matchR[v] = u;
                    distL[u] = -1;				    // 	Mark this vertex as seen.
                    return true;
                }
            }
        }
        
        distL[u] = -1;							    // Mark this vertex as seen.
        return false;
    }
   
    public:
    void init(int lsize, int rsize)
    {
       //using namespace std;
        N = lsize, M = rsize;
        matchL.clear(); matchL.resize(N);
        matchR.clear(); matchR.resize(M);
        distL.clear();  distL.resize(N);
        distR.clear();  distR.resize(M);
        Q.resize(N); qf = qb = 0;

        adjList.resize(N);
        for(int i = 0; i < N; i++)
            adjList[i].clear();
    }

    inline void addEdge(int l, int r)
    {
        adjList[l].push_back(r);
    }
    
    int maxMatching()
    {
        fill(matchL.begin(), matchL.end(), -1);
        fill(matchR.begin(), matchR.end(), -1);
        int match = 0;
        while(bfs())
        {
            for(int i = 0; i < N; i++)
                if( matchL[i] == -1 && dfs(i) ) match++;
        }
        return match;
    }
};


int main()
{
     //Sample usage
    HCK hck;

    // initialize with left and right partition sizes
    hck.init(10, 20);     

    // Add some edges
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 20; j++)
            if( (i + j) & 1)
                hck.addEdge(i, j);

    int max_match = hck.maxMatching();
    cout << max_match << endl;
    return 0;
}
