#include<bits/stdc++.h>
using namespace std;
map<long long,int>mp;
int n;
int main(){
	cin>>n;
	mp.clear();
	long long x;
	for(int j=1;j<=n;j++){
		cin>>x;
		mp[x]+=1;
	}
	map<long long,int>::iterator it;
	for(it=mp.begin();it!=mp.end();it++){
		cout<<it->first<<" "<<it->second<<endl;
	}
	return 0;
}