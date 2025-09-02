#include<bits/stdc++.h>
using namespace std;
int x,y,X,Y;
float ans;
int main(){
	cin>>x>>y>>X>>Y;
	ans=sqrt((x-X)*(x-X)+(y-Y)*(y-Y));
	printf("%.3f",ans);
	return 0;
}