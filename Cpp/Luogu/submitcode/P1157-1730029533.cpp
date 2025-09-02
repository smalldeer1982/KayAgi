#include<bits/stdc++.h>
using namespace std;
int n,r,b[25],c=0;
long long y=1;
vector<vector<int>>ans;
int main(){
	cin>>n>>r;
	for(int i=1;i<(1<<n);i++){
		int x=i;
		int cnt=0,t=1;
		while(x>0){
			if(x%2){
				b[t]=1;
				cnt+=1; 
			}
			else{
				b[t]=0;
			}
			t+=1;
			x/=2;
		}
		if(cnt==r){
			vector<int>a;
			c+=1;
			for(int j=1;j<=n;j++){
				if(b[j]==1){
					a.push_back(j);
					c+=1;
				}	
			}
			ans.push_back(a);
		}
	}
	sort(ans.begin(),ans.end());
	for(auto &item1:ans){
		for(auto &item2:item1){
			cout<<setw(3)<<item2;
		}
		cout<<endl;
	}
	return 0;
}