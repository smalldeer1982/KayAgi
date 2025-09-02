#include<bits/stdc++.h>
using namespace std;
int k;
bool flag=0;
int main(){
	cin>>k;
	for(int a=1;a<=2;a++){
		for(int b=0;b<=9;b++){
			for(int c=0;c<=9;c++){
				for(int d=0;d<=9;d++){
					for(int e=0;e<=9;e++){
						if((a*100+b*10+c)%k==0&&(b*100+c*10+d)%k==0&&(c*100+d*10+e)%k==0){
							flag=1;
							cout<<a<<b<<c<<d<<e<<endl;
						}
					}
				}
			}
		}
	}
	if(300%k==0){
		flag=1;
		cout<<30000<<endl;
	}
	if(flag==0){
		cout<<"No";
	}
	return 0;
}