/*
* Author : Nikhil Garg
* Date   : 2010-12-27
* Hopcrof Karp algorithm.
* Finds maximum matching in a graph in time O(E sqrt V). In practice has much better performance.
* 
*/

#include<cstring>
using namespace std;

const int maxn = 1005;
int N,M;
int matchL[maxn], matchR[maxn];
int distL[maxn], distR[maxn];
int Q[maxn], qf, qb;


inline bool bfs()
{
	memset( distL, -1, sizeof distL);
	memset( distR, -1, sizeof distR);
	qf = qb = 0;
	
	for(int i = 0; i < N; i++)
		if( matchL[i] == -1)
			distL[i] = 0, Q[qb++] = i;
		
	bool found = false;
	while( qf < qb)
	{
		int u = Q[qf++];
		for(int i = 0; i < deg[u]; i++)
		{
			int v = adjList[u][i];
			if( distR[v] >= 0)	continue;		// Seen vertex
				distR[v] = 1 + distL[u];
			if( matchR[v] == -1)			    // Unmatched vertex, aug path exists. Don't push vertices anymore on queue
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
	for(int i= 0; i < deg[u]; i++)
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

int hck()
{
	memset( matchL, -1, sizeof matchL);
	memset( matchR, -1, sizeof matchR);
	int match = 0;
	while(bfs())
	{
		for(int i = 0; i < N; i++)
			if( matchL[i] == -1 && dfs(i) ) match++;
	}
	return match;
}


int main()
{
	// Fill up the adjList & deg for all X vertices
	// Set up value of maxn accordingly
}