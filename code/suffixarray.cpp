#include <cstdio>
#include <algorithm>
using namespace std;


const int MAXN = 1 << 21;
char  S[MAXN];
int N, gap;
int sa[MAXN], pos[MAXN], tmp[MAXN], lcp[MAXN];

bool sufCmp(int i, int j)
{
	if (pos[i] != pos[j])
		return pos[i] < pos[j];
	i += gap;
	j += gap;
	return (i < N && j < N) ? pos[i] < pos[j] : i > j;
}

void buildSA()
{
	N = strlen(S);
	for (int i = 0; i < N; ++i) sa[i] = i, pos[i] = S[i];
	for (gap = 1;; gap *= 2)
	{
		sort(sa, sa + N, sufCmp);
		for (int i = 0; i < N-1; ++i) tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]);
		for (int i = 0; i < N; ++i) pos[sa[i]] = tmp[i];
		if (tmp[N - 1] == N - 1) break;
	}
}

void buildLCP()
{
	for (int i = 0, k = 0; i < N; ++i) if (pos[i] != N - 1)
	{
		for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k];)
		++k;
		lcp[pos[i]] = k;
		if (k)--k;
	}
}
void getdistinctsubstring(){
	buildSA();
	buildLCP();
	long long sum=0;
	for(int i=0;i<N;i++) sum+=lcp[i];
	printf("%lld\n", ((long long)N*(N+1))/2-sum);
}
int main(){;}
