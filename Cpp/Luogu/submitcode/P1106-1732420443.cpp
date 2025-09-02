#include<bits/stdc++.h>
using namespace std;
char s[260];
int k;
int main(){
	scanf("%s %d",s,&k);
	int len=strlen(s);
	while(k--){
		for(int i=0;i<len;i++){
			if(s[i]>s[i+1]){
				for(int j=i;j<len;j++){
					s[j]=s[j+1];
				}
				break;
			}
		}
		len-=1;
	}
	int m=0;
	while(s[m]=='0'){
		m+=1;
	}
	for(;s[m]!='\0';m+=1){
		cout<<s[m];
	}
	if(len==1){
		cout<<0;
	}
	return 0;
}