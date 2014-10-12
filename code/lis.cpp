#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
int solve(vector<int> input, vector<int>& solution)
{
    vector<int> magic;
    vector< vector<int> > history; // OPTIONAL
    for (vector<int>::iterator iter=input.begin();iter!=input.end();++iter) {
    	int x=*iter;
        vector<int>::iterator it = lower_bound(magic.begin(), magic.end(), x);
        if (it == magic.end()) {
            magic.push_back(x);
            history.push_back(vector<int>(1, x)); // OPTIONAL
        }
        else {
            *it = x;
            history[it-magic.begin()].push_back(x); // OPTIONAL
        }
    }
    
    // OPTIONAL
    {
        int result = magic.size();
        solution.resize(result);
        solution.back() = magic.back();
        for (int i=result-2; i>=0; i--) {
            vector<int>::reverse_iterator it = lower_bound(history[i].rbegin(), history[i].rend(), solution[i+1]);
            it --;
            solution[i] = *it;
        }
    }
    
    return magic.size();
}

int main(int argc, char const *argv[])
{
	int array[]={0,8,7,3,4,6};
	vector<int> vect(array,array+sizeof(array)/sizeof(int));
	vector<int> answer;
	printf("%d\n",solve(vect,answer));
	for (vector<int>::iterator i = answer.begin(); i != answer.end(); ++i)
	{
		printf("%d ", *i);
	}
	printf("\n");

	return 0;
}
