#include<bits/stdc++.h>
using namespace std;
long long n,m;
long long sum=0;
int main(){
	cin>>n>>m;
	while(n!=0&&m!=0){
		long long minn=min(n,m);
		long long maxx=max(n,m);
		sum+=maxx/minn*4*minn;
		maxx%=minn;
		n=minn;
		m=maxx;
	}
	cout<<sum;
	return 0;
}
