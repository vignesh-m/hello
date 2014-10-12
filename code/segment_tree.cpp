#include <cstdio>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
using namespace std;

const int MAXN=1000;
const int MAXIND=2*MAXN+1;
int arr[MAXN];
int tree[MAXIND];
int lazy[MAXIND];
const int IDENTITY=1000000000;
int target_function(int a,int b){
	return min(a,b);
}

void build_tree(int node, int a, int b) {
  	if(a > b) return; // Out of range
  	
  	if(a == b) { // Leaf node
    		tree[node] = arr[a]; // Init value
		return;
	}
	
	build_tree(node*2, a, (a+b)/2); // Init left child
	build_tree(node*2+1, 1+(a+b)/2, b); // Init right child
	
	tree[node] = target_function(tree[node*2], tree[node*2+1]); // Init root value
}
void update_tree(int node, int a, int b, int i, int j, int value) {
  
  	if(lazy[node] != 0) { // This node needs to be updated
   		tree[node] += lazy[node]; // Update it
 
		if(a != b) {
			lazy[node*2] += lazy[node]; // Mark child as lazy
    			lazy[node*2+1] += lazy[node]; // Mark child as lazy
		}
 
   		lazy[node] = 0; // Reset it
  	}
  
	if(a > b || a > j || b < i) // Current segment is not within range [i, j]
		return;
    
  	if(a >= i && b <= j) { // Segment is fully within range
    		tree[node] += value;
 
		if(a != b) { // Not leaf node
			lazy[node*2] += value;
			lazy[node*2+1] += value;
		}
 
    		return;
	}
 
	update_tree(node*2, a, (a+b)/2, i, j, value); // Updating left child
	update_tree(1+node*2, 1+(a+b)/2, b, i, j, value); // Updating right child
 
	tree[node] = target_function(tree[node*2], tree[node*2+1]); // Updating root with max value
}
void update_point(int pos,int newval,int n){
	update_tree(1,0,n-1,pos,pos,newval-arr[pos]);
}
int query_tree(int node, int a, int b, int i, int j) {
	
	if(a > b || a > j || b < i) return IDENTITY; // Out of range
 
	if(lazy[node] != 0) { // This node needs to be updated
		tree[node] += lazy[node]; // Update it
 
		if(a != b) {
			lazy[node*2] += lazy[node]; // Mark child as lazy
			lazy[node*2+1] += lazy[node]; // Mark child as lazy
		}
 
		lazy[node] = 0; 
	}
 
	if(a >= i && b <= j) 
		return tree[node];
 
	int q1 = query_tree(node*2, a, (a+b)/2, i, j); 
	int q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j); 
 
	int res = target_function(q1, q2); //function use
	
	return res;
}
int main(int argc, char const *argv[])
{
	//array[]={3,5,7,4,8,0,4};
	int a,b,n;
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",&(arr[i]));
	for(int i=0;i<2*n+1;i++) tree[i]=-1;
	build_tree(1,0,n-1);
	scanf("%d %d",&a,&b);
	printf("%d\n", query_tree(1,0,n-1,a,b));
	scanf("%d %d",&a,&b);
	update_point(a,b,n);
	scanf("%d %d",&a,&b);
	printf("%d\n", query_tree(1,0,n-1,a,b));
	return 0;
}
