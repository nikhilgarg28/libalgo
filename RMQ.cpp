const int LOGN = 20;
const int N = 1000005;
int rmq[18][N];
int K[N];

void calcRMQ(const VI & arr)
{
	int n=arr.size();
	for(int i = 0; i < n; i++)
		rmq[0][i] = arr[i];
	
	for(int stp = 1, len = 2; stp < 18; stp++, len<<=1)
		for(int i = 0; i < n; i++)
		{
			int f = i + (len>>1);
			if(f < n)	rmq[stp][i] = min(rmq[stp-1][i], rmq[stp-1][f]);
			else 		rmq[stp][i] = rmq[stp-1][i];
		}
	}
}

int getRMQ(int a,int b) // a inclusive, b exclusive
{
	if(a==b) return +INF;
	int k = K[b-a];
	return min(rmq[k][a], rmq[k][b-(1<<k)]);
}
	

void preprocess()
{
	K[0]=-1;
	for(int i=1;i<=N;i++)
	{
		K[i]=K[i-1];
		if((i&(i-1))==0) K[i]++;
	}
}