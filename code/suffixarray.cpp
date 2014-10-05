#include <stdio.h>
#include <string.h>
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
int search(char *pat)
{
    int m = strlen(pat);
    int l = 0, r = N-1;
    while (l <= r)
    {
        int mid = l + (r - l)/2;
        int res = strncmp(pat, S+sa[mid], m);
        if (res == 0)
        {
            return mid;
        }
        if (res < 0) r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}
void longestrepeatedsubstring(){
	int i=(max_element(lcp,lcp+N-1)-lcp);
	printf("position is %d/%d , length is %d \n",sa[i],sa[i+1],lcp[i]);
	char substr[MAXN];
	strncpy(substr,S+sa[i],lcp[i]);
	substr[lcp[i]]='\0';
	printf("%s\n", substr);
}
long long getdistinctsubstring(){
	//buildSA();
	//buildLCP();
	long long sum=0;
	for(int i=0;i<N-1;i++) sum+=lcp[i];
	return ((long long)N*(N+1))/2-sum;
}
void longestcommonsubstring(char* a,char* b){
	int n1=strlen(a);
	strcpy(S,strcat(a,b));
	buildSA();
	buildLCP();
	int max=-1,index=-1;
	for(int i=0;i<N-1;i++){
		if((sa[i]<n1)&&(sa[i+1]<n1)) continue;
		if((sa[i]>=n1)&&(sa[i+1]>=n1)) continue;
		if(lcp[i]>max){
			max=lcp[i];
			index=sa[i];
		}
	}
	char substr[MAXN];
	strncpy(substr,S+index,max);
	substr[max]='\0';
	printf("%s\n", substr);
}
int main()
{
	strcpy(S,"abcbc");
	buildSA();
	buildLCP();
	/*for(int i=0;i<N;i++){
		printf("%d %d %d %d\n", i,pos[i],sa[i],lcp[i]);
	}*/
	printf("%lld\n",getdistinctsubstring());
	char pat[]="bad";
	printf("%d\n", search(pat));
	strcpy(pat,"bd");
	printf("%d\n", search(pat));
	longestrepeatedsubstring();
	char s1[]="acabcababcbc",s2[]="babcabcdbacbacd";
	longestcommonsubstring(s1,s2);
}
