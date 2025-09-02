#include<bits/stdc++.h>
using namespace std;
int n,sum=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		if(i%2==1){
			sum+=3;
		}
		else{
			sum-=2;
		}
	}
	cout<<sum;
	return 0;
}
