#include<bits/stdc++.h>
using namespace std;
int n,a[10005],x,sum=0;
bool flag=1;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		sum=0;
		x=a[i];
		for(int j=2;j<=sqrt(a[i]);j++){
			if(x%j==0){
				sum+=1;
				while(x%j==0){
					x/=j;
				}
			}
		}
		if(x>1){
			sum+=1;
		}
		if(sum==2){
			printf("%d\n",1);
		}
		else{
			printf("%d\n",0);
		}
	}
	return 0;
}