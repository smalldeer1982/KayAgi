#include <bits/stdc++.h>
using namespace std;

const int N=500005;
int head[N],to[N<<1],ne[N<<1],idx;
void add(int x,int y){
  to[++idx]=y,ne[idx]=head[x],head[x]=idx;
}
int n,a[N],f[N],s[N],p[N];

bool cmp(int x,int y){
  return f[x]-s[x]>f[y]-s[y];
}
void dfs(int x,int fa){
  f[x]=a[x];
  for(int i=head[x];i;i=ne[i])
    if(to[i]!=fa) dfs(to[i],x);
  
  int t=0;
  for(int i=head[x];i;i=ne[i])
    if(to[i]!=fa) p[++t]=to[i];
  sort(p+1,p+t+1,cmp);
  for(int i=1;i<=t;++i){
    f[x]=max(f[x],s[x]+1+f[p[i]]);
    s[x]+=s[p[i]]+2;
  }
}
int main(){
  scanf("%d",&n);
  for(int i=1;i<=n;++i)
    scanf("%d",&a[i]);
  for(int i=1,x,y;i<n;++i)
    scanf("%d%d",&x,&y),
    add(x,y),add(y,x);
  dfs(1,0);
  printf("%d\n",max(f[1],s[1]+a[1]));
}