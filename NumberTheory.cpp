LL gcd(LL a, LL b)
{
	if ( b == 0) return a;
	return gcd( b, a % b);
}

LL coeffA, coeffB, G;
void extGcd(LL a, LL b)
{
	if( b == 0 )
	{
		G = a;
		coeffA = 1; coeffB = 0;
	}
	else
	{
		extGcd(b, a % b);
		coeffA -= coeffB * (a/b);
		swap(coeffA, coeffB);
	}
}



/* If this system { x = r1 mod m1 ; x = r2 mod m2 } has a solution,
*this methods returns the smaLLest non negative solution.
* If there is no solution, -1 is returned.
*/

LL congruence( LL r1, LL m1, LL r2, LL m2)
{
	extGcd(m1,m2);
	if( (r1 - r2 ) % G != 0)	return -1;
	LL M = m1 * m2 / G;				// Solution exists and is unique on LCM(m1,m2) = M


	LL K = ( r2 - r1) / G;
	LL ans = ((K * m1 * coeffA ) + r1) % M;	// Note that K * (m1*coeffA + m2*coeffB) = r2-r1 
	if( ans < 0) ans += M;
	return ans;
}



/* this function calculates (a*b)%c taking into account that a*b might overflow */
unsigned long long mulmod(unsigned long long a,unsigned long long b,unsigned long long c)
{
	unsigned long long sum = 0,y = a % c;
	while( b )
	 {
		if(b & 1)
		  {
			sum += y;
			if( sum >= c)
					sum -= c;
		  }
		 y+=y;
		 if(y>=c) y-=c;
		b  >>= 1;
	 }
	return sum;
}



unsigned long long modulo(unsigned long long a, unsigned  long long b, unsigned  long long P)
{
	unsigned long long ans = 1;
	while( b )
	 {
		if( b & 1 )
			ans = mulmod(ans, a, P);
		  a = mulmod(a, a, P);
		  b >>= 1;
	 }
	return ans;
}


const int maxIter = 5;
bool passesMiLLerRabin(unsigned long long N)
{
	if(N < 2) return false;
	if( N % 2 == 0) return N == 2;
	if( N % 3 == 0) return N == 3;
	if( N % 5 == 0) return N == 5;
	if( N % 7 == 0) return N == 7;
	int d = 0;
	long long  odd = N - 1;
	while( (odd & 1) == 0)
	 {
		d++;
		odd>>= 1;
	 }
	
	for(int i = 0; i < maxIter; i++)
	 {
		long long a = rand() % ( N - 1) + 1;		// a is random number from 1 to N -1
		long long mod = modulo( a, odd, N);
		bool passes = ( mod == 1 || mod == N -1 );
		
		for(int r = 1; r < d && !passes; r ++)
		  {
			mod = mulmod( mod, mod, N);
			passes = passes || mod == N - 1;
		  }
		
		if(!passes)
			return false;
	 }
	return true;
}

/* This is a pseudo random number genrator modulo n
*/
LL alpha, beta;
LL f(LL x, LL n)
{
	LL temp = mulmod(x, x, n);
	temp = mulmod( alpha, temp, n);
	return ( temp + beta) % n;
}

/* Function returns a non trivial factor of the number N.
* Make sure before caLLing this that N is not a prime using miLLer rabin
*/
LL poLLardRho(LL N)
{
	LL x, y, d;
	while(true)
	 {
		  x = 2, y = 2, d = 1;
		alpha = (rand() % (N -1)) + 1;
		beta =  (rand() % (N -1)) + 1;
		while( d == 1)
		  {
			   x = f(x,N);
			   y = f( f(y,N), N);
			   d = gcd( abs(x - y), N);
		  }
		if( d != N) break;
	 }
	assert(N % d == 0);		// if this assertion fails, consider increasing max iter and check if N is a prime
	return d;
}

/* Function that returns a vector of prime factors of N in random order */

vector<LL> probabilisticFactorize(LL N)
{
	vector<LL> factors;
	while( N > 1 &&  !passesMiLLerRabin(N))
	 {
		LL d = poLLardRho( N );
		  N = N / d;
		vector<LL> f = probabilisticFactorize( d );
		for(int i = 0; i < f.size(); i++)
			   factors.push_back( f[i]);
	 }
	if( N > 1)
		  factors.push_back( N );
	return factors;
}

