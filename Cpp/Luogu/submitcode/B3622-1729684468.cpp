#include<bits/stdc++.h>
using namespace std;
int n,t,ans,a[1050];
int main(){
	cin>>n;
	for(int i=0;i<(1<<n);i++){
		int x=i;
		t=1;
		while(x>0){
			if(x%2){
				a[t]=1;
			}
			else{
				a[t]=0;
			}
			t+=1;
			x/=2;
		}
		for(int i=n;i>=1;i--){
			if(a[i]==1){
				cout<<"Y";
			}
			else{
				cout<<"N";
			}
		}
		cout<<endl;
	}
	return 0;
}