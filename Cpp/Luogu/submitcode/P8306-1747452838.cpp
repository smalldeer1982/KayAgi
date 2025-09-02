#include<bits/stdc++.h> 
using namespace std;

const int maxn=3e6+10;
int n;
char s[maxn];
int ch[maxn][75],cnt[maxn],idx;
void init(){
	for (int i=0;i<=idx;i++){
		memset(ch[i],0,sizeof(ch[i]));
		cnt[i]=0;
	}
	idx=0;
}
void insert(char *s){
  int p=0;
  for(int i=0; s[i]; i ++){
    int j=s[i]-'0';//字母映射
    if(!ch[p][j])ch[p][j]=++idx;
    p=ch[p][j];
    cnt[p]++;
  }
}
int query(char *s){
  int p=0;
  for(int i=0; s[i]; i ++){
    int j=s[i]-'0';
    if(!ch[p][j]) return 0;
    p=ch[p][j];
  }
  return cnt[p];
}
int main(){
  int T;
  scanf("%d",&T);
  while(T--){
  	init();
  	int n,m;
  	scanf("%d%d",&n,&m);
  	while (n--){
  		scanf("%s",s);
  		insert(s);
	}
    while (m--){
    	scanf("%s",s);
    	printf("%d\n",query(s));	
	}
  }
  return 0;
}