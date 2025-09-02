#include<bits/stdc++.h>
using namespace std;
int c,m,e,sum=0;
int main(){
	cin>>c>>m>>e;
	if(c<60){
		sum+=1;
	}
	if(m<60){
		sum+=1;
	}
	if(e<60){
		sum+=1;
	}
	if(sum==1){
		cout<<1;
	}
	else{
		cout<<0;
	}
	return 0;
}