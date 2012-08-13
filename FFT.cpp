const double PI = 4*atan(1);
typedef complex<double> base;

vector<base> omega;
int FFT_N;
void init_fft(int n)
{
     FFT_N  = n;
     omega.resize(n);
     double angle = 2 * PI / n;
     
     for(int i = 0; i < n; i++)
          omega[i] = base( cos(i * angle), sin(i * angle));
}

void fft (vector<base> & a)
{
     int n = (int) a.size();
     if (n == 1)  return;
     int half = n >> 1;
     
     vector<base> even (half),  odd (half);
     for (int i=0, j=0; i<n; i+=2, ++j)
     {
          even[j] = a[i];
          odd[j] = a[i+1];
     }
     fft (even), fft (odd);
     
     for (int i=0, fact = FFT_N/n; i < half; ++i)
     {
          base twiddle =  odd[i] * omega[i * fact] ;
          a[i] =  even[i] + twiddle;
          a[i+half] = even[i] - twiddle;
     }
}
void multiply (const vector<long long> & a, const vector<long long> & b, vector<long long> & res)
{
     vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
     int n = 1;
     while (n < 2*max (a.size(), b.size()))  n <<= 1;
     fa.resize (n),  fb.resize (n);
     
     init_fft(n);
     fft (fa),  fft (fb);
     for (size_t i=0; i<n; ++i)
          fa[i] = conj( fa[i] * fb[i]);
     fft (fa);

     res.resize (n);
     for (size_t i=0; i<n; ++i)
          res[i] = (long long) (fa[i].real() / n + 0.5);
}
