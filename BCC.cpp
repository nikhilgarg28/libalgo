/**
* Team Proof
* BiConnected Components
*
* Fill edgeList, deg, from, to, cost
*/

#include<algorithm>
#include<cstring>
using namespace std;
const int maxNode = 25;
const int maxEdge = 25;
int adjList [maxNode][maxNode];			// adjList[i][j] is number of jth edge coming out of i
int deg[maxNode];
int from[maxEdge], to[maxEdge], cost[maxEdge];

int dfsNum[maxNode], minDfsNum[maxNode], parent[maxNode];	// parent is useful only in undirected graphs
int currentComp[maxEdge], component[maxEdge], compSize[maxEdge];
bool inComp[maxEdge];
int dfsNext, currentSize, totalBCC;

void dfs ( int v)
{
	dfsNum[v] = minDfsNum[v] = dfsNext++;
	
	
	for(int i = 0;i < deg[v]; i++)
	{
		int e = adjList[v][i];
		int w = ( to[e] == v ? from[e] : to[e] );
		if(w == parent[v]) continue;
		
		if ( dfsNum[w] < 0 )	// W was a fresh vertex hence a proper ancestor of v
		{
			currentComp[currentSize++] = e;
			inComp[e] = true;
			parent[w] = v;			// We don't need notion of parent for directed graphs
			
			dfs(w);
			
			if( minDfsNum[w] >= dfsNum[v] )	// New biconnected compnent found. Pop all edges until ( v, w)
			{
				while(true)
				{
					int edge = currentComp[--currentSize];
					inComp[edge] = false;
					component[edge]  = totalBCC;
					compSize[totalBCC]++;
					if( edge == e) 	break;
				}
				totalBCC++;
			}
			else
				minDfsNum[v] = min ( minDfsNum[v], minDfsNum[w] );
		}
		
		else	if ( dfsNum[w] < dfsNum[v])	// Back edge found 
		{
			currentComp[currentSize++] = e;
			inComp[e] = true;
			minDfsNum[v] = min ( minDfsNum[v], dfsNum[w] );
		}
	}
}

void bcc()
{
	
	memset( dfsNum, -1, sizeof dfsNum);
	memset( inComp, false, sizeof inComp);
	memset( compSize, 0, sizeof compSize);
	
	totalBCC = dfsNext = currentSize = 0;
	dfs(0);
	
}