struct LCA
{
    #include <vector>

    vector<int> L, D;
    vector<vector<int> > P;
    int N;
    LCA(vector<int> & dad, vector<int> & level)
    {
        N = dad.size();
        D = dad,         L = level;
        int LOG = 1,     base = 1;

        while(base < N)
            LOG++, base <<= 1;

        P.resize(N, vector<int>(LOG, -1));

        for (int i = 0; i < N; i++)
            P[i][0] = D[i];

        for (int j = 1; 1 << j < N; j++)
            for (int i = 0; i < N; i++)
                if (P[i][j - 1] != -1)
                    P[i][j] = P[P[i][j - 1]][j - 1];
    }

    int query(int p, int q)
    {
        int tmp, log, i;
        if (L[p] < L[q])
            tmp = p, p = q, q = tmp;

        for (log = 1; 1 << log <= L[p]; log++);
        log--;

        for (i = log; i >= 0; i--)
            if (L[p] - (1 << i) >= L[q])
                p = P[p][i];

        if (p == q)
            return p;

        for (i = log; i >= 0; i--)
            if (P[p][i] != -1 && P[p][i] != P[q][i])
                p = P[p][i], q = P[q][i];

            return D[p];
    }
};
