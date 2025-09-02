#include<bits/stdc++.h>
using namespace std;
int n,a,b,sum=0;
int main(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++){
		if(i%a==0&&i%b!=0||i%a!=0&&i%b==0){
			sum+=1;
		}
	}
	cout<<sum;
	return 0;
}
