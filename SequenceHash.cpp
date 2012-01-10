/*
 * Author : Nikhil Garg
 * Date   : 2011-12-29
 * A SequenceHash data structure.
 * Initial construction takes O(N) time. 
 * After that it can query hashcode of any contiguous subsequence in O(1)
 *
 */

struct SequenceHash
{
    vector<long long> prefixHash, powers;
    
    SequenceHash(const vector<int>& seq)
    {
        int L = seq.size();
        prefixHash.resize(L+1); powers.resize(L+1);
        prefixHash[0] = 0LL;    powers[0] = 1LL;
        
        for(int i = 1; i <= L;i++)
        {
            prefixHash[i] = prefixHash[i-1] * 31LL + seq[i-1];
            powers[i] = powers[i-1] * 31LL;
        }        
    }
    
    long long hash(int a, int b)           // Returns hash code for seq[a..b], both endpoints inclusive
    {
        return prefixHash[b+1] - prefixHash[a] * powers[b-a+1];
    }
};


int main()
{
    int A[] = { 1, 2, 3, 1, 2, 3};
    SequenceHash sh(VI(A));             // Just instantiate the SequenceHash 
    assert( sh.hash(0,2) == sh.hash(3,5));
}
