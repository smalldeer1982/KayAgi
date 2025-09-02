#include<bits/stdc++.h>
using namespace std;
int n,m,x,ans=0;
vector<int>a;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>x;
		if(find(a.begin(),a.end(),x)==a.end()){
			ans+=1;
			a.push_back(x);
		}
		if(a.size()>n){
			a.erase(a.begin());
		}
	}
	cout<<ans;
	return 0;
}