#include<bits/stdc++.h>
using namespace std;
int m,n,x,a[1000005];
void prime(int t){
	for(int i=ceil((double)sqrt(t));i*i<=1000001;i++)
	{
		if(a[i*i]==0)
		{
			for(int j=1;i*i*j<=1000001;j++)
			{
				a[i*i*j]=1;
			}
		}
	}
}
int main(){
	cin>>m>>n;
	prime(m);
	for(int i=1;i<=n;i++){
		cin>>x;
		if(a[x]==1){
			cout<<"lucky"<<endl;
		}
		else{
			for(int j=x+1;;j++){
				if(a[j]==1){
					cout<<j<<endl;
					break;
				}
			}
		}
	}
	return 0;
}