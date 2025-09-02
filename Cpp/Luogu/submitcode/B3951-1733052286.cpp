#include<bits/stdc++.h>
using namespace std;
int n,m,a[2005],b[2005],p,sum=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>p;
		sum=0;
		p+=1;
		b[i]=a[p];
		for(int j=1;j<=i;j++){
			if(b[j]>b[i]){
				swap(b[j],b[i]);
				sum+=1;
			}
		}
		cout<<sum<<endl;
	}
	return 0;
}