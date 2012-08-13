/* 
   Proof : Min Cost Flow
   
   Interface is :
   Call init function and then just use addEdge to fill in all edges
   After that just call minCost function. Taddda!
   
   Orders :
   Time -> O(F*E*V)
   Space -> O(V*V)
 */
public class MinCostFlow
{
	int T;
	int [][]cost, cap;
	int []deg;
	int [][]adjList;
	int INF = (int)1e9;
	
	void initFlow(int _T)
	{
		T= _T;
		cost = new int[T][T]; 
		cap = new int[T][T];
		deg = new int[T];
		adjList = new int[T][T];
	}
		
	void addEdge(int a, int b, int cap1, int cap2, int cost1, int cost2)
	{
		adjList[a][deg[a]++] = b;
		adjList[b][deg[b]++] = a;		
		cap[a][b] = cap1; cap[b][a] = cap2;
		cost[a][b] = cost1; cost[b][a] = cost2;
	}
	
	// Returns cost of sending need flow, -INF if its impossible
	int minCostFlow(int src, int dest, int need)
	{
		int C=0;		
		int [] dist = new int[T];
		int []parent = new int[T];
		boolean [] done = new boolean[T];
		
		while( need > 0)
		{
			Arrays.fill(done,false);
			Arrays.fill(parent, -1);
			Arrays.fill(dist, INF);
			dist[src] = 0;
			
			while(true)
			{
				boolean changed = false;
				for(int i = 0; i < T; i++)
				{
					if(done[i] || dist[i]>=INF) continue;
					done[i]=true;
					for(int j = 0; j < deg[i]; j++)
					{
						int v = adjList[i][j];
						if( dist[v] > dist[i] + cost[i][v] && cap[i][v] > 0)
						{
							dist[v] = dist[i] + cost[i][v];
							parent[v] = i;	done[v]=false;
							changed = true;
						}
					}
				}
				if (!changed) break;
			}
			
			if( dist[dest]  ==  INF) break;
			
			C += dist[dest];
			need--;
			for(int cur = dest; cur != src; cur = parent[cur])
			{
				int v = parent[cur];
				cap[v][cur] --;
				cap[cur][v] ++;
			}
		}
			
		if( need > 0) return -INF;
		return C;
	}
}
