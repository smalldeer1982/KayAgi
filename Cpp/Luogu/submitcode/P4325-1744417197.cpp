#include<bits/stdc++.h>
using namespace std;
int a[15],sum=0;
int main(){
	for(int i=1;i<=10;i++){
		cin>>a[i];
		a[i]%=42;
	}
	for(int i=1;i<=10;i++){
		if(a[i]!=-1){
			for(int j=1;j<=10;j++){
				if(j!=i&&a[i]==a[j]){
					a[j]=-1;
				}
			}
		}	
	}
	for(int i=1;i<=10;i++){
		if(a[i]!=-1){
			sum+=1;
		}
	}
	cout<<sum;
	return 0;
} 