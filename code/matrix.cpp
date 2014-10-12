#include <cstdio>
#include <vector>

using namespace std;
typedef vector < vector < long long > >  matrix;
matrix I;
int MOD=1000000007;
void initI(int n){
	I.resize(n);
    for(int i=0; i<n; i++)
    {
        I[i].resize(n);
        I[i][i]=1;
    }
}
matrix multiply(matrix A, matrix B)
{
    int K=(int)A.size();
    matrix C(K, vector<long long>(K));
    for(int i=0;i<K;i++) for(int j=0;j<K;j++) for(int k=0;k<K;k++)
    {
        C[i][j] = C[i][j] + (A[i][k] * B[k][j]) % MOD;
        if(C[i][j]>=MOD)
            C[i][j]-=MOD;
    }
    return C;
}
matrix matrix_pow(matrix T, long long N)
{
    if(N==0)return I;
    if(N==1)return T;
    matrix ret=matrix_pow(T,N/2);
    matrix ret1=multiply(ret,ret);
    if(N%2==0)return ret1;
    else return multiply(ret1,T);
}

void print_matrix(matrix m){
	for(int i=0;i<m.size();i++){
		for(int j=0;j<m[0].size();j++){
			printf("%lld ", m[i][j]);
		}
		printf("\n");
	}
}
int main(){
	long long arra[][3]={{1,1,0},{0,1,0},{0,0,1}},arrb[][3]={{1,0,0},{0,1,0},{0,0,1}};
	matrix a(3),b(3),c;
	a.assign(3,vector<long long>());
	b.assign(3,vector<long long>());
	for(int i=0;i<3;i++){
		a[i]=vector<long long>(arra[i],arra[i]+3);
		b[i]=vector<long long>(arrb[i],arrb[i]+3);
	}
	c=multiply(a,b);
	print_matrix(c);
	c=matrix_pow(a,10);
	print_matrix(c);
}
