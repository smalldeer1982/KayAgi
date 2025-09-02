#include<bits/stdc++.h>
using namespace std;
long long a[100005],n,add=0,sub=0,x;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(i==1){
			continue;
		}
		x=a[i-1]-a[i];
		if(x>0){
			add+=x;
		}
		else{
			sub-=x; 
		}
	}
	cout<<max(add,sub)<<endl;
	cout<<abs(add-sub)+1;
	return 0;
}