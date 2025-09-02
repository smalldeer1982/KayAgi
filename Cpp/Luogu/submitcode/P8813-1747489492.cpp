#include<bits/stdc++.h>
using namespace std;
long long a,b,sum;
int main(){
	cin>>a>>b;
	sum=1;
	for(int i=1;i<=b;i++){
		sum*=a;
		if(sum>1e9){
			cout<<-1;
			return 0;
		}
	}
	cout<<sum;
	return 0;
}
