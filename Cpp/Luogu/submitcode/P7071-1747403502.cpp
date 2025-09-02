#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin>>n;
	if(n%2==1){
		cout<<-1;
		return 0;
	}
	else{
		while(n){
			for(int i=1;i<=n;i++){
				if(pow(2,i)>n){
					int x=pow(2,i-1);
					cout<<x<<" ";
					n-=pow(2,i-1);
					break;
				}
			}
		}
	}
	return 0;
}
