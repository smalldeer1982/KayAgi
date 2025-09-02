#include<bits/stdc++.h>
using namespace std;
int n,s[15],b[15],c[15],miny=100000000;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i]>>b[i];
	}
	for(int i=1;i<(1<<n);i++){
		int x=i,y=1,z=0,t=1;
		while(x>0){
			if(x%2){
				c[t]=1; 
			}
			else{
				c[t]=0;
			}
			t+=1;
			x/=2;
		}
		for(int j=1;j<=n;j++){
			if(c[j]==1){
				y*=s[j];
				z+=b[j];
			}
		}
		miny=min(miny,abs(y-z));
	}
	cout<<miny;
	return 0;
}