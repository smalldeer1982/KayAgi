#include<bits/stdc++.h>
using namespace std;
int A,B,C,b,c,x[15],s=0;
bool flag=1;
int main(){
	cin>>A>>B>>C;
	if(A==0||B==0||C==0){
		cout<<"No!!!";
		return 0;
	}
	for(int a=123;a<=987;a++){
		flag=1;
		b=a*B/A;
		c=a*C/A;
		x[a%10]+=1;
		x[a/10%10]+=1;
		x[a/100]+=1;
		x[b%10]+=1;
		x[b/10%10]+=1;
		x[b/100]+=1;
		x[c%10]+=1;
		x[c/10%10]+=1;
		x[c/100]+=1;
		for(int i=1;i<=9;i++){
			if(x[i]!=1){
				flag=0;
			}
			x[i]=0;
		}
		if(flag==1){
			s=1;
			cout<<a<<" "<<b<<" "<<c<<endl;
		}
	}
	if(s==0){
		cout<<"No!!!";
	}
	return 0;
}