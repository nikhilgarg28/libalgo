/**
* Team Proof
* Hungarian
* 
* Reverse edges are not to be given any cost
* All left vertices are forcibly matched
* Right side vertices MAY be unmatched
*/
#include <cstring>
#include <algorithm>
using namespace std;
#define INF (int)1e9

const int maxNode =505;
int cost[maxNode][maxNode],X[maxNode],Y[maxNode];

void hungarian(int nx, int ny)
{
	int Lx[maxNode], Ly[maxNode], Q[maxNode], prev[maxNode];

	memset(X, -1, sizeof X); memset(Y, -1, sizeof Y);
	memset(Lx, 0, sizeof Lx); memset(Ly, 0, sizeof Ly);
	
	for(int i = 0; i < nx; i++)
		for(int j = 0; j < ny; j++)
			Lx[i] = max( Lx[i], cost[i][j]);
		
	for(int i = 0;i < nx; )
	{
		memset( prev, -1, sizeof prev);
		int head = 0, tail = 0;
		for(Q[tail++] = i; head < tail && X[i] < 0; head ++)
		{
			int u = Q[head];
			for(int v = 0; v < ny && X[i] < 0; v++)
			{
				if( prev[v] >= 0 || Lx[u] + Ly[v] > cost[u][v] ) continue;
				if( Y[v] >=  0)
					prev[v] = u,  Q[tail++] = Y[v];
				else
				{
					prev[v] = u;
					for(int at = v; at >=0; )
					{
						u = Y[at] = prev[at];
						//swap X[u] , at
						int a = X[u];
						X[u] = at;
						at = a;
					}
				}
			}
			
		}

		if( X[i] >=0) i ++;
		else
		{
			int alpha = INF;
			for(int head = 0; head < tail; head++)
			{
				int u = Q[head];
				for(int v = 0; v < ny; v++)
					if( prev[v] == -1)
						alpha = min ( alpha, Lx[u] + Ly[v] - cost[u][v] );
			}

			for(int head = 0; head < tail; head ++)
				Lx[Q[head]] -= alpha;
			
			for(int v = 0; v < ny; v++)
				if( prev[v] >= 0 )
					Ly[v] += alpha;
		}
	}
	
}