#include<bits/stdc++.h>
using namespace std;
int a[40005],n,ans,cnt=1,x;
bool flag=0;
int main(){
	cin>>n;
	while(ans<n*n){
		cin>>x;
		for(int i=1;i<=x;i++){
			cout<<flag;
			cnt+=1;
			if(cnt>n){
				cnt=1;
				cout<<endl;
			}
		}
		if(flag==1){
			flag=0;
		}
		else{
			flag=1;
		}
		ans+=x;
	}
	return 0;
}