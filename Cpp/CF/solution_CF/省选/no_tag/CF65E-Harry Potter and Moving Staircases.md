# Harry Potter and Moving Staircases

## 题目描述

### 题意翻译


哈利波特在从管理员费尔奇那里逃走时，丢失了他的隐形衣。寻找一件隐形的物件可不是一件容易的事情。幸运的是哈利有乐意帮助他的朋友们。赫敏·格兰杰读了“隐形衣和关于它们的一切”，以及“最短路径百科全书”，“网络流”，“最长上升子序列”和其他的魔法物品。她已经为在复杂的动态系统（霍格沃茨是其中一个）中的隐形衣开发了一套搜索算法。

霍格沃茨由 n 层组成，这 n 层分别从 1 到 n 标号。一些楼层被楼梯连着。这些楼梯会改变自己一端的位置。通常情况像这样：如果之前连接着 a 层和 b 层，那么它移动后就可能连接 a 层和 c 层或 b层和 c 层，其中 c 层不为 a 层或 b 层。任何情况下楼梯都不能和本身相连。同时可以有多个楼梯连接相同楼层。

现在楼梯的活动十分少。然而，罗恩和赫敏很乐意去在它们上面释放法术来帮助哈利找到隐形衣。为了减少怀疑，三个人计划一个个移动楼梯。在两次移动楼梯中间，哈利可以在楼层上走动，从楼梯上到达另一层来寻找自己的隐形衣。此时可以认为楼梯不会自主移动。

请帮助三人来制定一个搜索的计划。如果有多个不同的方法可以解决问题（不一定是最优情况下），都可以被接受。

## 样例 #1

### 输入

```
6 4
1 2
1 3
2 3
4 5
```

### 输出

```
YES
2
3 1 2 3
2 3 5
3 5 4 5
4 5 6
3 6 5 3
```

## 样例 #2

### 输入

```
4 1
1 2
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5 5
1 2
1 3
3 4
3 5
4 5
```

### 输出

```
YES
0
6 1 2 1 3 4 5
```

# 题解

## 作者：wind_whisper (赞：3)

## $\text{Description}$
有一个 $n$ 个点 $m$ 条边的无向图，哈利初始在结点 $1$，哈利可以沿着边任意移动，过程中任意时刻可以选择一条边，改变它的**一个端点**，但是每条边只能被修改一次.    
请构造一种方案使哈利走遍所有楼层，或者报告无解.  
$n\le 10^5,m\le 2\times10^5$
## $\text{Solution}$
阴间大特判题.   
容易找到一种比较正确的整体方案：dfs，过程中——
1. 若出边连向走过的结点，则直接把边改向一个未走过的结点，递归 dfs.
2. 若出边连向未走过的结点，则先递归 dfs，回溯时在把边改向一个未走过的结点，递归 dfs.

不难发现这样一定是最优的.  
然后就是 ~~通过观察 WA 的数据~~ 处理亿点点细节问题：  
1. 改边连向的点应该优先连向**有度数的点**.
2. 有可能会出现 $1$ 没有度数但存在解的情况，这时候需要尝试把一条边直接改为连向 $1$，同时这个边不应该是一条边连接两个点的简单图形.（否则改完还是会死掉）
3. 改为连向 $1$ 的边应该优先选择成环的边，这样会更优.


具体实现留给读者自行思考.（或者参考我实现丑的一批的代码）
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define double long double 
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=4e5+100;
const double eps=1e-12;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m;
struct node{
  int to,nxt;
}p[N<<1];
int fi[N],cnt;
inline void addline(int x,int y){
  p[++cnt]=(node){y,fi[x]};fi[x]=cnt;
  return;
}
int jd[N],du[N];
set<int>s1,s2;
int dfn[N<<2],tim,tot;
struct edge{
  int x,y,id;
}e[N];
int siz[N];
int ans[N],num;
int flag,O,ID;
void print(){
  int pl(1);
  if(!O) flag=0;
  printf("YES\n%d\n",tot+flag);
  for(int i=1;i<=tim+1;i++){
    if(dfn[i]) ans[++num]=dfn[i];
    else{
      printf("%d ",num);
      for(int j=1;j<=num;j++) printf("%d ",ans[j]);
      putchar('\n');   
      num=0;
      if(pl<=tot){
	printf("%d %d %d\n",e[pl].id,e[pl].x,e[pl].y);   
	++pl;
      }
    }
    if(i==1&&flag){
      printf("1 1\n%d %d 1\n",ID,O);num=0;
    }
  }
  return;
}
int fa[N];
vector<int> v[N];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
bool vis[N];
void dfs(int x){
  dfn[++tim]=x;vis[x]=1;
  for(int i=fi[x];~i;i=p[i].nxt){
    if(jd[i]==1) continue;
    int f=jd[i];
    jd[i]=jd[i^1]=1;
    int to=p[i].to;
    //printf("x=%d to=%d\n",x,to);
    dfs(to);
    dfn[++tim]=x;
    if((!s1.empty()||!s2.empty())&&!f){
      int o;
      if(!s1.empty()) o=(*s1.begin()),s1.erase(o);
      else o=(*s2.begin()),s2.erase(o);
      //printf("x=%d o=%d\n",x,o);
      dfn[++tim]=0;e[++tot]=(edge){x,o,i/2+1};
      dfs(o);
      dfn[++tim]=x;
    }
  }
  return;
}
int E;
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  memset(fi,-1,sizeof(fi));cnt=-1;  
  n=read();m=read();
  for(int i=1;i<=n;i++) fa[i]=i;
  for(int i=1;i<=m;i++){
    e[i].x=read();e[i].y=read();
    ++du[e[i].x];++du[e[i].y];
    if(find(e[i].x)==find(e[i].y)){
      E=i;
    }
    else fa[find(e[i].x)]=find(e[i].y);
  }
  if(du[1]==0){
    flag=1;
    if(E){
      e[E].y=1;O=e[E].x;ID=E;
    }
    else{
      for(int i=1;i<=m;i++){
	if(du[e[i].x]<=1) swap(e[i].x,e[i].y);
	if(du[e[i].x]>1){
	  e[i].id=1;O=e[i].x;ID=i;
	  e[i].y=1;break;
	}
      }
    }
  }
  memset(du,0,sizeof(du));
  for(int i=1;i<=n;i++) fa[i]=i;
  for(int i=1;i<=m;i++){
    int x=e[i].x,y=e[i].y;
    addline(x,y);addline(y,x);
    fa[find(x)]=find(y);
    ++du[x];++du[y];
    if(e[i].id) jd[cnt]=jd[cnt^1]=2;
  }
  //for(int i=1;i<=n;i++) debug("i=%d fa=%d\n",i,fa[i]);
  for(int i=2;i<=n;i++){
    if(i==find(i)&&find(1)!=i){
      if(du[i]) s1.insert(i);
      else s2.insert(i);
    }
  }
  dfs(1);
  if(!s1.empty()||!s2.empty()) printf("NO\n");
  else print();
  return 0;
}
/*

*/

```


---

