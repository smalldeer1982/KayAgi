#include<bits/stdc++.h>
using namespace std;
int n,sum=0;
bool a[100000005];
//bool prime1(int x){
//	for(int i=2;i<=sqrt(x);i++){
//		if(x%i==0){
//			return false;
//		}
//	}
//	return true;
//}
void prime2(){
	for(int i=2;i<=sqrt(n);i++){
		if(a[i]){
			for(int j=i*i;j<=n;j+=i){
				a[j]=0;
			}
		}
	}
}
int main(){
	cin>>n;
	memset(a,1,sizeof(a));
//	for(int i=2;i<=n;i++){
//		if(prime1(i)){
//			sum+=1;
//		}		
//	}
	prime2();
	for(int i=2;i<=n;i++){
		if(a[i]==1){
			sum+=1;
		}
	}
	cout<<sum;
	return 0;
}