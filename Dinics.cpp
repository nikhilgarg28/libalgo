/*
	Author - Nikhil Garg
	Dinic's Max Flow algorithm : based on ACRush's implementation
*/

#include<algorithm>
#include<csting>
using namespace std;
const int maxnode=1000+5;
const int maxedge=50000+5;
const int oo=1000000000;
int node,src,dest,nedge;			// node is number of vertices. nedge is number of edges

// to[e] stores the desitnation of edge e
// next[e] stores the next edge from same source ( simulating adjList using next )
int to[maxedge],next[maxedge],flow[maxedge],cap[maxedge];

// head[v] stores the first edge out of this node
// work[v] is first edge of this node in working phase. Note as we may "delete" edges, this has to be changed in same phase
int head[maxnode], dist[maxnode], Q[maxnode], work[maxnode];

void init(int _node,int _src,int _dest)
{
	node=_node;
	src=_src;
	dest=_dest;
	for (int i=0;i<node;i++)		head[i]=-1;
	nedge=0;
}

void addedge(int u,int v,int c1,int c2)					// add to graphs edge from  u to v with cap c1 & from v to u with cap c2
{
	to[nedge]=v,cap[nedge]=c1,flow[nedge]=0,next[nedge]=head[u],head[u]=(nedge++);
	to[nedge]=u,cap[nedge]=c2,flow[nedge]=0,next[nedge]=head[v],head[v]=(nedge++);
}

// Check if using "valid" edges you can go from source to destintion. Also meanwhile make layers of graph
bool dinic_bfs()
{
	for(int i =0; i < node; i++)
		dist[i] = -1;
	
	dist[src]=0;	int sizeQ=0;	Q[sizeQ++]=src;
	for (int front=0;front<sizeQ; front++)
	{
		for (int u=Q[front], e=head[u]; e>=0; e=next[e])
		{
			int v = to[e];
			if (flow[e]<cap[e] && dist[v]<0 )			// We want dist[v] < 0 as we want only edges which are crossing layers
			{
				dist[v]=dist[u]+1;
				Q[sizeQ++]=v;
			}
		}
	}
	return dist[dest] >= 0;
}

int dinic_dfs(int u,int bot)		// Find augment pathing from u to destination, where path capacity is alredy found to be nomore then bot
{
	if (u==dest) return bot;
	for (int i=work[u];i>=0; i=next[i], work[u] = i)		// we are changing work[u] as in this phase, previous edge has been deleted
	{
		int v=to[i],tmp;
		if (flow[i]<cap[i] && dist[v]==dist[u]+1 && (tmp = dinic_dfs(v,min(bot,cap[i]-flow[i])) )>0)
		{
			flow[i] +=tmp;
			flow[i^1]-=tmp;						// i^1 is the reverse edge always !
			return tmp;
		}
	}
	return 0;
}

int dinic_flow()
{
	int result=0;
	while (dinic_bfs())
	{
		for (int i=0;i<node;i++) work[i]=head[i];
		while (true)
		{
			int delta=dinic_dfs(src,oo);
			if (delta==0) break;					// This phase is over
			result+=delta;
		}
	}
	return result;
}
