#include<bits/stdc++.h>
using namespace std;
int p,q,a,b,ans=0;
int main(){
	cin>>p>>q>>a>>b;
	for(int i=1;i<=q;i++){
		if(i<=p){
			ans+=a;
		}
		else{
			ans+=b;
		}
	}
	cout<<ans;
	return 0;
}
