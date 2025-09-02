#include<bits/stdc++.h>
using namespace std;
#define int long long
string x,y;
int sumx=1,sumy=1;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>x>>y;
	for(int i=0;i<x.size();i++){
		sumx*=(x[i]-'A'+1);
	}
	for(int i=0;i<y.size();i++){
		sumy*=(y[i]-'A'+1);
	}
	if(sumx%47==sumy%47){
		cout<<"GO";
	}
	else{
		cout<<"STAY";
	}
	return 0;
}
