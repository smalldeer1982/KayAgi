#include<bits/stdc++.h>
using namespace std;
int x,y,p,q;
int main(){
	cin>>x>>y>>p>>q;
	for(int i=min(x,y);i>=1;i--){
		if(p-i>=0&&q-i>=0&&p+i<=x&&q+i<=y){
			cout<<i;
			break;
		}
	}
	return 0;
}