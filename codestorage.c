//code storage
#include <stdio.h>
#include <math.h>
#include <string.h>
//gcd in approx O log n
long long gcd(long long a,long long b){
	if(a==0) return b;
	return gcd(b%a,a);
}
//lcm in approx O log n
long long lcm(long long a,long long b){
	return (a*b)/gcd(a,b);
}
//primefactorize with primecount in O n
//very fast for small prime divisors
void primefactorize(int b,int* primes,int* primecount){
	int j=0;
	int lim=b/2;
	for(int i=2;i<=lim;i++){
		if(b<i) break;
		if(b%i==0){
			primes[j]=i;
			primecount[j]=0;
			while(b%i==0){
				b=b/i;
				primecount[j]++;
			}
			j++;
		}
	}
	if(b==1) return;
	if(primes[0]==0) {primes[0]=b;primecount[0]=1;}
	/*for(int i=0;i<1000;i++){
		if(primes[i]==0) break;
		printf("%d,%d\n",primes[i],primecount[i] );
	}*/
}
//find larger int with same number of ones in binary rep O 1 (?)
long long nextintwithsamebinones(long long x) { 
    long long smallest, ripple, ones; 
    // x = xxx0 1111 0000 
    smallest = x & -x; // 0000 0001 0000 
    ripple = x + smallest; // xxx1 0000 0000 
    ones = x ^ ripple; // 0001 1111 0000 
    ones = (ones >> 2)/smallest; // 0000 0000 0111 
    return ripple | ones; // xxx1 0000 0111 
} 
//find smaller int with same number of ones in binary rep O 1 (?)
long long previntwithsamebinones(long long x){
	return ~nextintwithsamebinones(~x);
}
//check if power of 2 O 1 (?)
bool ispowoftwo(long long x)
{
	return (!(x & (x - 1)))	;
} 
//like gcd returns -1 if no soln
long long mul_inv(long long a, long long b)
{
    int t, nt, r, nr, q, tmp;
 	if (b < 0) b = -b;
    if (a < 0) a = b - (-a % b);
    t = 0;  nt = 1;  r = b;  nr = a % b;
    while (nr != 0) {
		q = r/nr;
		tmp = nt;  nt = t - q*nt;  t = tmp;
		tmp = nr;  nr = r - q*nr;  r = tmp;
	}
    if (r > 1) return -1;  /* No inverse */
    if (t < 0) t += b;
    return t;
}
//runs in O log(exponent).easy to convert to regular exponentiation
long long modexp(long long base, long long exponent, long long modulus)
{
    long long result = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}
//O 1
double distance(double x1,double y1,double x2,double y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
bool isprime(int n){
	for(int i=2;i<=sqrt(n);i++){
		if(n%i==0) return false;
	}
	return true;
}
double trianglearea(int x1,int x2,int y1,int y2,int z1,int z2){
	return fabs((x1*(y2-z2)+y1*(z2-x2)+z1*(x2-y2))/2);
}
int sieve[1000000];
void primegen(int n){
	for(int i=0;i<n;i++) sieve[i]=1;
	sieve[0]=sieve[1]=0;
	for(int i=2;i<n;i++){
		if(sieve[i]) 
			for(int j=2*i;j*j<n;j+=i)
				sieve[j]=0;
	}
}
int main(){;}
