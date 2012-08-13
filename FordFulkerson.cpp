// Fast Ford fullkerson with scaling!

const int maxNode=10000;
VI cap[maxNode];
VI adjList[maxNode];
VI revmap[maxNode];
int deg[maxNode];
bool done[maxNode];

int scale;
void initFlow()
{
	for(int i=0;i<maxNode;i++)
	{
		adjList[i].clear();
		cap[i].clear();
		revmap[i].clear();
		deg[i]=0;
	}
}

void addEdge(int u,int v,int cap1,int cap2)
{
	revmap[u].pb(deg[v]);
	revmap[v].pb(deg[u]);
	adjList[u].pb(v);
	adjList[v].pb(u);
	cap[u].pb(cap1);
	cap[v].pb(cap2);
	deg[u]++;
	deg[v]++;
}

int visit(int cur,int dest,int flow)
{
	done[cur]=true;
	if(cur==dest) return flow;
	
	for(int k=0;k<deg[cur];k++)
	{
		int v = adjList[cur][k];
		if(!done[v] && cap[cur][k]>=scale)
		{
			int z=visit(v,dest,min(flow,cap[cur][k]));
            if(z>0)
			{
				cap[cur][k] -= z;
				cap[v][revmap[cur][k]] += z;
				return z;
			}
		}
	}
	return 0;
}	

int flow (int src, int dest)
{
	int total = 0;
    scale = 1 << 25;
	while(scale > 0)
	{
		fill(done,false);
		int z = visit(src,dest,(int)1e9);
		if(z==0) 
            scale /= 2;
        else 
            total += z;
	}
	return total;
}
