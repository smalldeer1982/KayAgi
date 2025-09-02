#include<bits/stdc++.h>
using namespace std;
int w11,l11,w21,l21,a[5105][3],b[2605][3],x=0,y=0;
char n;
int main(){
	while(cin>>n){
		if(n=='E'){
			break;
		}
		if(n=='W'){
			w11+=1;
			w21+=1;
		}
		else{
			l11+=1;
			l21+=1;
		}
		if((l11>=11&&(l11-w11>=2))||(w11>=11&&(w11-l11>=2))){
			x+=1;
			a[x][1]=w11;
			a[x][2]=l11;
			w11=0;
			l11=0;
		}
		if((l21>=21&&(l21-w21>=2))||(w21>=21&&(w21-l21>=2))){
			y+=1;
			b[y][1]=w21;
			b[y][2]=l21;
			w21=0;
			l21=0;
		}
	}
	if(w11!=0||l11!=0){
		x+=1;
		a[x][1]=w11;
		a[x][2]=l11;
	}
	else{
		x+=1;
		a[x][1]=0;
		a[x][2]=0;
	}
	if(w21!=0||l21!=0){
		y+=1;
		b[y][1]=w21;
		b[y][2]=l21;
	}
	else{
		y+=1;
		b[y][1]=0;
		b[y][2]=0;
	}
	if(x==0&&y==0){
		cout<<"0:0"<<endl;
		cout<<endl;
		cout<<"0:0";
	}
	for(int i=1;i<=x;i++){
		cout<<a[i][1]<<":"<<a[i][2]<<endl;
	}
	cout<<endl;
	for(int i=1;i<=y;i++){
		cout<<b[i][1]<<":"<<b[i][2]<<endl;
	}
	return 0;
}