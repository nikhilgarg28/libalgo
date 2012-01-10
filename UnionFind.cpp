struct UnionFind
{
    VI dad, mass;
    int N;
    UnionFind(int _N)
    {
        N = _N;
        dad.resize(N);
        mass.resize(N);
        forall(i, 0, N)
            dad[i] = -1, mass[i] = 1;
    }

    int find(int a)
    {
        if(dad[a] < 0) return a;
        return dad[a] = find(dad[a]);
    }

    void merge(int a, int b)
    {
        int c1 = find(a), c2 = find(b);
        if(c1 != c2)
        {
            N--;
            if(mass[c1] < mass[c2]) swap(c1, c2);
            mass[c1] += mass[c2];
            dad[c2] = c1;
        }
    }
    int size()
    {
        return N;
    }
};

int main()
{
    UnionFind uf(20);
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 20; j++)
            if( i + j == 30) uf.merge(i,j);
    
    int heads = uf.size();
    for(int i = 0; i < N; i++)
        cout << uf.find(i) << endl;
}