# [USACO11JAN] The Continental Cowngress G

## 题目描述

由于对农场主约翰的领导不满，奶牛们已经从农场中分离出来，并成立了第一个大陆奶牛议会。基于「每头奶牛都能得到她想要的东西」这一原则，她们决定采用以下投票系统：

出席的 $M$ 头奶牛将对 $N$ 项立法议案进行投票。每头奶牛对两个（不同的）议案 $B_i$ 和 $C_i$ 分别投下「赞成」或「反对」票（在输入文件中用 `Y` 或 `N` 表示）。这些投票分别称为 $VB_i$ 和 $VC_i$。

最终，议案的通过与否必须满足每头奶牛至少有一个投票结果符合她的意愿。例如，如果 Bessie 对议案 $1$ 投了「赞成」票，对议案 $2$ 投了「反对」票，那么在任何有效的解决方案中，要么议案 $1$ 通过，要么议案 $2$ 被否决（或者两者都满足）。

给定每头奶牛的投票情况，你的任务是找出哪些议案将被通过，哪些议案将被否决，以符合上述规则。如果没有解决方案，请输出 `IMPOSSIBLE`。如果至少有一个解决方案，那么对于每个议案，显示：

`Y` 如果在每个解决方案中该议案都通过

`N` 如果在每个解决方案中该议案都被否决

`?` 如果存在一些解决方案中该议案通过，而在另一些解决方案中该议案没有通过

考虑以下投票集（每头奶牛投两票）：  

|编号|$1$|$2$|$3$|
|:-:|:-:|:-:|:-:
|奶牛 $1$|赞成|反对
|奶牛 $2$|反对|反对
|奶牛 $3$|赞成||赞成
|奶牛 $4$|赞成|赞成

由此，两个解决方案满足每头奶牛：

+ 议案 $1$ 通过（这满足了奶牛 $1$、$3$ 和 $4$）
+ 议案 $2$ 被否决（这满足了奶牛 $2$）
+ 议案 $3$ 可以通过或被否决（这就是有两个解决方案的原因）

事实上，这些是仅有的两个解决方案，因此答案是 `YN?`。

## 说明/提示

对于 $100\%$ 的数据，$1\le M\le4000$，$1\le N\le1000$，$1\le B_i,C_i\le N$，$VB_i,VC_i\in\{Y,N\}$。  
（本题由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
3 4 
1 Y 2 N 
1 N 2 N 
1 Y 3 Y 
1 Y 2 Y 
```

### 输出

```
YN? 
```

# 题解

## 作者：Acc_Robin (赞：15)

这道题其实没必要 tarjan ，既然已经允许 $O(n^2)$ 的复杂度，那就直接暴力给每个点判断一下是否合法即可。

1如果从一个点 $i$ 出发，经过了某个点 $j$ 的正反两个点
$j$ 和 $j+n$，那就说明 $i$ 这个情况是非法的。

我们对每个点 $i$ 和 $i+n$ 都dfs一遍，直接判断即可。

如果点 $i$ 和点 $i+n$ 都不合法，说明无解。

在代码中体现为
```
for(int i=1,x,y;i<=m;i++){
	x=check(i),y=check(i+m);
	if(!x&&!y)return (void)(puts("IMPOSSIBLE"));
	if(x&&y)ans[i]='?';
	if(x&&!y)ans[i]='N';
	if(!x&&y)ans[i]='Y';
}
```

整体代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
	const int N=2e3+10;
	basic_string<int>G[N];
	int n,m,d[N];
	char s[10],t[10],ans[N];
	void Dfs(int u){
		d[u]=1;
		for(auto v:G[u])if(!d[v])Dfs(v);
	}
	int check(int x){
		memset(d,0,sizeof d),Dfs(x);
		for(int i=1;i<=m;i++)if(d[i]&&d[i+m])return 0;
		return 1;
	}
	void work(){
		cin>>m>>n;
		for(int i=1,x,y,a,b;i<=n;i++)cin>>x>>s>>y>>t,a=s[0]=='Y',b=t[0]=='Y',G[x+m*(1-a)]+=y+b*m,G[y+m*(1-b)]+=x+a*m;
		for(int i=1,x,y;i<=m;i++){
			x=check(i),y=check(i+m);
			if(!x&&!y)return (void)(puts("IMPOSSIBLE"));
			if(x&&y)ans[i]='?';
			if(x&&!y)ans[i]='N';
			if(!x&&y)ans[i]='Y';
		}
		cout<<ans+1;
	}
}
int main(){
	return Acc::work(),0;
}
```

---

## 作者：Nuisdete (赞：6)

$2-SAT$ 裸题。

建图，设第 $i$ 号点表示支持第 $i$ 个法案，第 $i$ $+$ $n$ 号点表示反对第 $i$ 个法案。

对于每头奶牛的两个条件，因为题目要求必须满足其一，那就对奶牛的两个条件之一取反，并向另一个条件连边，表示如果不满足奶牛的其中一个要求，那必须满足另一个要求。

跑一遍 $Tarjan$ ，然后判断 $i$ 号点， $i$ $+$ $n$ 号点是否在同一个强连通分量里，如果是的话无论反对还是支持第 $i$ 个法案都会矛盾，无解。

之后如果有解的话（不满足上一行的情况），那么 $O(n ^ 2)$暴力判断如果支持了第 $i$ 号法案会不会矛盾，反对会不会矛盾，按情况输出。

**code ：** [https://www.cnblogs.com/qqq1112/p/14427359.html](https://www.cnblogs.com/qqq1112/p/14427359.html)

---

## 作者：niiick (赞：6)

2-SAT练习的好题，
建图方式是比较基础的**或**形式

$Y_i,N_j$——连边i到j，表示若i不通过则j必须不通过；j+n到i+n，表示若j通过则i必须通过 

$Y_i,Y_j$——连边i到j+n，表示若i不通过则j必须通过；j到i+n，表示若j不通过则i必须通过

$N_i,N_j$——连边i+n到j，表示若i通过则j必须不通过；j+n到i，表示若j通过则i必须不通过

$N_i,Y_j$——连边i+n到j+n，表示若i通过则j必须通过；j到i，表示若j不通过则i必须不通过

tarjan求SCC后**缩点**

枚举每个点(议案)的通过和不通过

然后分别从表示该状态的结点(col[i]和col[i+n])出发**深搜**并**标记访问到的点**

最后检测**是否有**$col[i]$**与**$col[i+n]$**都被访问到**即可

虽然实测不缩点直接深搜也可以过，
但理论上的时间复杂度是不对的，
可以被特殊数据hack

```
//niiick
#include<iostream>
#include<stack>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
using namespace std;
typedef long long lt;

int read()
{
    int f=1,x=0;
    char ss=getchar();
    while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
    while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
    return f*x;
}

const int maxn=4010;
int n,m;
struct node{int v,nxt;}E[2][maxn<<1];
int head[2][maxn],tot[2];
int low[maxn],dfn[maxn],cnt;
int col[maxn],ins[maxn],colnum;
int st[maxn],top;
int vis[maxn];
char s1[5],s2[5],ans[maxn];

void add(int u,int v,int d)
{
    E[d][++tot[d]].nxt=head[d][u];
    E[d][tot[d]].v=v;
    head[d][u]=tot[d];
}

void dfs(int u)
{
    vis[u]=1;
    for(int i=head[1][u];i;i=E[1][i].nxt)
    if(!vis[E[1][i].v]) dfs(E[1][i].v);
}

void tarjan(int u)
{
    low[u]=dfn[u]=++cnt;
    st[++top]=u; ins[u]=1;
    for(int i=head[0][u];i;i=E[0][i].nxt)
    {
        int v=E[0][i].v;
        if(!dfn[v]){tarjan(v);low[u]=min(low[u],low[v]);}
        else if(ins[v])low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u])
    {
        colnum++;
        do{
            ins[st[top]]=0;
            col[st[top]]=colnum;
        }while(st[top--]!=u);
    }
}

int check(int u)
{
    memset(vis,0,sizeof(vis));
    dfs(u);
    for(int i=1;i<=n;++i)
    if(vis[col[i]]&&vis[col[i+n]])return 0;
    return 1;
}

int main()
{
    n=read();m=read();
    for(int i=1;i<=m;++i)//N-0,Y-1
    {
        int u=read(); scanf("%s",&s1);
        int v=read(); scanf("%s",&s2);
        if(s1[0]=='Y')
        {
            if(s2[0]=='N')add(u,v,0),add(v+n,u+n,0);
            else if(s2[0]=='Y')add(u,v+n,0),add(v,u+n,0);
        }
        else if(s1[0]=='N')
        {
            if(s2[0]=='N')add(u+n,v,0),add(v+n,u,0);
            else if(s2[0]=='Y')add(u+n,v+n,0),add(v,u,0);
        }
    }
    
    for(int i=1;i<=n<<1;++i)
    if(!dfn[i])tarjan(i);
    
    for(int u=1;u<=n<<1;++u)
    for(int i=head[0][u];i;i=E[0][i].nxt)
    {
    	int v=E[0][i].v;
    	if(col[u]==col[v])continue;
    	add(col[u],col[v],1);
    }
    
    for(int i=1;i<=n;++i)
    {
        int p=check(col[i]),q=check(col[i+n]);
        if(!p&&!q){printf("IMPOSSIBLE");return 0;}
        else if(p&&q)ans[i]='?';
        else if(p&&!q)ans[i]='N';
        else if(!p&&q)ans[i]='Y';
    }
    for(int i=1;i<=n;++i)
    cout<<ans[i];
    return 0;
}

```

---

## 作者：StarsIntoSea (赞：2)

# Solution

2-SAT 板子题。

不同的是，这里需要判断一种情况是否能同时满足。

根据对 2-SAT 图上的性质，如果一个正点能够直接或间接到达另一个负点，那么这个点的答案肯定对于正点是约束的，反之同理。

![](https://cdn.luogu.com.cn/upload/image_hosting/5x6ewvcj.png)

如图的 $1$ 与 $-1$ 就是一组约束的点，这时候我们只能取 $-1$ 这个点为答案。

但是如果两个点互不约束，即双方都无法到达对方，这个时候显然无论取正点还是负点都是满足的。

因为 $n \le 1000,m\le4000$，因此我们可以 $O(n+m)$ 暴力 dfs 预处理每个点能否到达另一个对应的负点，在输出时判断即可。

时间复杂度 $O(n^2+nm)$，瓶颈在于预处理。

# Code


```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N=2005;
int n,m;
vector<int> e[N];
int tot,cnt;
int low[N],dfn[N],d[N],vis[N];
int stk[N],instk[N],scc[N],top;
void Tarjan(int x){
	dfn[x]=low[x]=++tot;
	stk[++top]=x;
	instk[x]=1;
	for(auto y:e[x]){
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(instk[y])
			low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]){
		++cnt;
		int y;
		do{
			y=stk[top];
			top--;
			instk[y]=0;
			scc[y]=cnt;
		}while(x!=y);
	}
}
void dfs(int x){ //预处理
	vis[x]=1;
	for(auto y:e[x]){
		if(!vis[y]) dfs(y);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	while(m--){ //2-SAT建图
		int a,b;
		char x,y;
		cin>>a>>x>>b>>y;
		if(x=='Y'&&y=='Y'){
			e[a+n].push_back(b);
			e[b+n].push_back(a);
		}
		if(x=='N'&&y=='N'){
			e[a].push_back(b+n);
			e[b].push_back(a+n);
		}
		if(x=='Y'&&y=='N'){
			e[a+n].push_back(b+n);
			e[b].push_back(a);
		}
		if(x=='N'&&y=='Y'){
			e[a].push_back(b);
			e[b+n].push_back(a+n);
		}
	}
	for(int i=1;i<=2*n;++i)
		if(!dfn[i]) Tarjan(i);
	for(int i=1;i<=2*n;++i){ //暴力dfs
		for(int i=1;i<=2*n;++i) vis[i]=0;
		dfs(i);
		int l=i;
		if(i>n) l-=n;
		if(vis[l] && vis[l+n]) d[l]=1; //约束的点打上标记
	}
	for(int i=1;i<=n;++i) if(scc[i]==scc[i+n])
		return !printf("IMPOSSIBLE\n");
	for(int i=1;i<=n;++i){
		if(!d[i]) printf("?");
		else if(scc[i]>scc[i+n]) printf("N");
		else printf("Y");
	}
	printf("\n");
}
```

---

## 作者：xiaoshumiao (赞：2)

看到题面不难想到 2-SAT，直接跑 Tarjan 即可，不会的同学请出门右转到 P4782。

如果 2-SAT 中的一个状态 $i$ 可以到达状态 $j$，则说明由 $i$ 可以推出 $j$。

我们对每一个满足 $1 \le i \le N$ 的 $i$ 都对 $i$ 和 $i+n$ 做一遍 DFS。对于一个状态 $j$，如果有 $k$ 满足状态 $k$ 和 $k+n$ 都能被访问到，那么说明 $j$ 是不可行的，否则就可行。这样就得到了最终的答案。

具体实现可见代码：
```cpp
#include<cstdio>
#include<stack>
#include<vector>
#include<iostream>
using namespace std;
const int N=1010;
stack<int>sta; bool in_stack[2*N],vis[2*N]; vector<int>g[2*N],g2[2*N]; char ans[N];
int n,m,idx,scc_cnt,dfn[2*N],low[2*N],scc_id[2*N];
void Tarjan(int u) {
  dfn[u]=low[u]=++idx,in_stack[u]=true,sta.push(u);
  for(auto v:g[u]) {
    if(!dfn[v]) Tarjan(v),low[u]=min(low[u],low[v]);
    else if(in_stack[v]) low[u]=min(low[u],dfn[v]);
  }
  if(dfn[u]==low[u]) {
    scc_cnt++; int v;
    do v=sta.top(),sta.pop(),in_stack[v]=false,scc_id[v]=scc_cnt; while(u!=v);
  }
}
void dfs(int u) {
  vis[u]=true;
  for(auto v:g2[u]) if(!vis[v]) dfs(v);
}
bool check(int u) {
  for(int i=1;i<=scc_cnt;i++) vis[i]=false;
  dfs(u);
  for(int i=1;i<=n;i++) if(vis[scc_id[i]]&&vis[scc_id[i+n]]) return false;
  return true;
}
int main() {
  scanf("%d %d",&n,&m);
  while(m--) {
  	char ca,cb; int a,va,b,vb; cin>>a>>ca>>b>>cb,va=(ca=='Y'?1:0),vb=(cb=='Y'?1:0);
	g[a+n*(va&1)].push_back(b+n*(vb^1)),g[b+n*(vb&1)].push_back(a+n*(va^1));
  }
  for(int i=1;i<=2*n;i++) if(!dfn[i]) Tarjan(i);
  for(int i=1;i<=2*n;i++) for(auto j:g[i]) if(scc_id[i]!=scc_id[j]) g2[scc_id[i]].push_back(scc_id[j]);
  for(int i=1;i<=n;i++) {
  	bool a=check(scc_id[i]),b=check(scc_id[i+n]);//a:i 号法案是否可以通过 b:i 号法案是否可以驳回
  	if(!a&&!b) return printf("IMPOSSIBLE"),0;
  	if(a&&b) ans[i]='?';
	if(a&&!b) ans[i]='Y';
	if(!a&&b) ans[i]='N';
  }
  for(int i=1;i<=n;i++) printf("%c",ans[i]);
  return 0;
}
```

---

## 作者：MY（一名蒟蒻） (赞：2)

[P3007 [USACO11JAN] The Continental Cowngress G](https://www.luogu.com.cn/problem/P3007)

本题是我在练习 2-SAT 的时候做的。

[我的 2-SAT 总结](https://www.luogu.com.cn/blog/nizhuan/post-2-sat-xue-xi-bi-ji)

---

这题的 2-SAT 模型非常典型，不同的是区别于求解，还需要判断是否必须通过或者不通过。

那承接刚才的想法 tarjan 后 dfs 即可。

但是这题的数据范围不大，直接用 $n^2$ dfs 即可。

---

联系 2-SAT 求解的原理， $i$ 和 $i^{\prime}$ 如果在同一个强连通分量内则无解。

**也就是选一个会导致另一个。**

而必须是某一种的取值的话，**在图上体现为选择 $i$ 或者 $i^{\prime}$ 会有环。**

如果都可以的话也就是两个取值都不影响解。

那么对于每一个法案，我们对两个取值分别进行 dfs ，记录一下指向关系。

建边类似 2-SAT ，使用位运算。

---

**Code**

```cpp
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int N=2e3+10,M=8e3+10;

int n,fir[N],tot;
bool vis[N];
struct edge {int to,nex;} e[M];

inline void add(int u,int v)
{
	e[++tot]=(edge) {v,fir[u]};
	fir[u]=tot; return ;
}
inline int turn(char c) {return c == 'Y'? 0:1;}

void dfs(int u)
{
	vis[u]=true;
	int v;
	for(int i=fir[u];i;i=e[i].nex)
		if(!vis[v=e[i].to]) dfs(v);
	return ;
}

inline int check(int u)//这个取值是否可行
{
	memset(vis,false,sizeof(vis));
	dfs(u);
	for(int i=1;i<=n;i++) if(vis[i] && vis[i+n]) return 0;
	return 1;
}

int main()
{
//	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	int m,u,v,x,y;
	char a,b,ans[N >> 1];
	scanf("%d%d",&n,&m);
	while(m--)
	{
		scanf("%d %c%d %c",&u,&a,&v,&b);
		x=turn(a); y=turn(b);
		add(u+(x^1)*n,v+y*n); add(v+(y^1)*n,u+x*n);
	}//位运算建图
	for(int i=1;i<=n;i++)
	{
		x=check(i); y=check(i+n);
		if(!x && !y) return printf("IMPOSSIBLE"),0;
		else if(x && !y) ans[++m]='Y';
		else if(!x && y) ans[++m]='N';
		else ans[++m]='?';
	}//这里有一个细节，我的 m 用完之后是 -1
	for(int i=0;i<=m;i++) printf("%c",ans[i]);
//	fclose(stdin); fclose(stdout);
	return 0;
}
```

$Thank\ you\ for\ your\ reading\ !$

---

## 作者：luxiaomao (赞：1)

## [P3007](https://www.luogu.com.cn/problem/P3007) 2-SAT 思维练习

最近刚好接触了一点 2-SAT，权将这篇题解作为学习的笔记吧，正好补充一下题解区关于怎么输出的小小不足。

## Solution

题意还是挺清晰的，用笔者习惯的模型化表述，给出 $n$ 个布尔值变量和 $m$ 个限制条件，每个条件会给两个布尔变量赋值，要求每个条件至少满足其中一个赋值。若无解输出 `IMPOSSIBLE`，否则输出每个布尔变量的可行值。

如果学过 **2-SAT** 的话（[没学过の传送门](https://oiwiki.com/graph/2-sat/)），相信大家不难看出模板题的影子。对于每个限制条件，我们进行建图，并跑一次 `Tarjan SCC` 缩点，这样就得到了~~最终的答案~~一张 `DAG`。

问题来了，题目跟模板题有点不一样，要求我们输出具体的解：

- $\tt{Y}$ 如果在每个解中，这个法案都**必须**通过。
- $\tt{N}$ 如果在每个解中，这个法案都**必须**驳回。
- $\tt{?}$ **如果有的解这个法案可以通过，有的解中这个法案会被驳回**。

传统的用拓扑序判断的输出只能输出任意一组解，这也是本题评到紫的原因。

我的做法是这样的：（pia 黑板！）

对于每个布尔变量 $i$，分别以节点 $i$ 和节点 $i+n$ 为起点进行 `dfs`（这两个节点分别代表 $i$ 取 `Yes` 和 $i$ 取 `No` 的两种决策），根据 `2-SAT` 的思想，如果能从一个决策节点 $A$ 搜到另一个决策节点 $B$，说明如果做出决策 $A$ 就必须做出决策 $B$。搜完之后，我们判断是否存在 $j$ 和 $j+n$ 同时被搜到，如果出现这样的情况，说明**做出这个决策会导致出现自相矛盾的情况**，即当前决策不可行（会导致一个布尔变量又要取 $0$ 又要取 $1$）。

搜索完后，根据决策 $i$ 和决策 $i+n$ 分别是否可行，我们进行分类讨论，并得出无解或布尔变量 $i$ 的正确答案，具体实现请看代码。

## Code Time

```cpp
#include<bits/stdc++.h>
#define N 2005
#define M 8005
using namespace std;

int n,m;
struct edge{int u,v,nex;}e[2][M];
int tot[2] = {1,1},head[2][N];

char ans[N];

void add(int u,int v,int x)
{
	e[x][++tot[x]].u = u,e[x][tot[x]].v = v;
	e[x][tot[x]].nex = head[x][u],head[x][u] = tot[x];
}

int t,dfn[N],low[N];
int s[N],top;
bool in[N];
int cnt,fa[N];

void tarjan(int u)
{
	dfn[u] = low[u] = ++t;
	s[++top] = u,in[u] = 1;
	for(int i = head[0][u];i;i = e[0][i].nex)
	{
		int v = e[0][i].v;
		if(!dfn[v])tarjan(v),low[u] = min(low[u],low[v]);
		else if(in[v])low[u] = min(low[u],dfn[v]);
	}
	if(dfn[u] == low[u])
	{
		cnt++;
		do
		{
			fa[s[top]] = cnt;
			in[s[top]] = 0;
		}while(s[top--] != u);
	}
}

bool vis[N];
void dfs(int u)
{
	vis[u] = 1;
	for(int i = head[1][u];i;i = e[1][i].nex)
	{
		int v = e[1][i].v;
		if(!vis[v])dfs(v);
	}
}

bool check(int u)
{
	for(int i = 1;i <= cnt;i++)vis[i] = 0;
	dfs(u);
	for(int i = 1;i <= n;i++)
		if(vis[fa[i]] && vis[fa[i+n]])return 0;
	return 1;
}

int main()
{
	scanf("%d%d",&n,&m);
	while(m--)
	{
		int u,v;char a,b;
		scanf("%d %c %d %c",&u,&a,&v,&b);
		add(u+n*(a=='Y'),v+n*(b=='N'),0);
		add(v+n*(b=='Y'),u+n*(a=='N'),0);
	}
	for(int i = 1;i <= 2*n;i++)
		if(!dfn[i])tarjan(i);
	for(int u = 1;u <= 2*n;u++)
		for(int i = head[0][u];i;i = e[0][i].nex)
		{
			int v = e[0][i].v;
			if(fa[u] != fa[v])add(fa[u],fa[v],1);
		}
	for(int i = 1;i <= n;i++)
	{
		bool a = check(fa[i]),b = check(fa[i+n]);
		if(!a && !b)return printf("IMPOSSIBLE"),0;
		if(a && b)ans[i] = '?';
		if(a && !b)ans[i] = 'Y';
		if(!a && b)ans[i] = 'N';
	}
	ans[n+1] = '\0';
	printf("%s",ans+1);
	return 0;
}
```

## PS

本题使用 $O(n^2)$ 的非 `Tarjan` 暴搜也可以通过，但使用 `Tarjan` 效率更高，看读者个人喜好啦。

---

## 作者：FiraCode (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P3007)

我们要判断一个变量恒为真/假/真假都可以。

### 方法一

我们可以强行设 $x_i$ 为假，若无解，那么 $x_i$ 一定为真或真假都行，或都不行。

要跑 $n$ 次，所以时间复杂度是 $O(nm)$。

### 方法二

若 $x_i$ 是指向 $\neg x_i$ 的话，我们就一定选 $x_i$ 为假。

若 $\neg x_i$ 是指向 $x_i$ 的话，我们就一定选 $\neg x_i$ 为假。

否则若 $\neg x_i$ 和 $x_i$ 没有可达关系，那么就是 `?`。

那么这样的话，我们就可以判断两个点是否有可达关系就可以了，而判断可达关系的话就可以用 `BFS` 或 `DFS`。

时间复杂度为 $O(n^2)$。

### CODE:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2010;
int n, m;
bool ins[N], vis[N];
vector<int> e[N];
int dfn[N], low[N], idx, bel[N];
stack<int> stk;
int cnt;
char ans[N];
void taryan(int u) {//联通分量
	dfn[u] = low[u] = ++idx;
	ins[u] = true;
	stk.push(u);
	for (auto v: e[u]) {
		if (!dfn[v]) taryan(v);
		if (ins[v]) low[u] = min(low[u], low[v]);
	}
	if (dfn[u] == low[u]) {
		++cnt;
		while (true) {
			int v = stk.top();
			bel[v] = cnt;
			ins[v] = false;
			stk.pop();
			if (u == v) break;
		}
	}
}
void dfs2(int u) {//dfs
	vis[u] = 1;
    for (auto v : e[u]) if (!vis[v])
        dfs2(v);
}
bool check(int s, int t) {
    memset(vis, false, sizeof(vis));
    dfs2(s);
    return vis[t];
}
int main() {
	scanf("%d%d", &n, &m);
    	for (int i = 1; i <= m; ++i) {
		int u, v;
		char ty1[2], ty2[2];
		scanf("%d%s%d%s", &u, ty1, &v, ty2);
		--u, --v;
		u = (u * 2) + (*ty1 == 'Y');
		v = (v * 2) + (*ty2 == 'Y');
		e[u ^ 1].push_back(v);
		e[v ^ 1].push_back(u);
	}
	for (int i = 0; i < 2 * n; ++i) if (!dfn[i])
		taryan(i);
	for (int i = 0; i < n; ++i) {
		if (bel[i << 1] == bel[i << 1 | 1]) {
			puts("IMPOSSIBLE");//无解
			return 0;
		}
	}
    for (int i = 0; i < n; ++i) {
        if (check(2 * i, 2 * i + 1)) ans[i] = 'Y';//当i*2是2*i+1,则第i个恒为真
        else if (check(2 * i + 1, 2 * i)) ans[i] = 'N';//另一种情况
        else ans[i] = '?';//因为不会是无解，所以就是?
    }
    puts(ans);
    return 0;
}
```

---

## 作者：zyctc (赞：1)

这是一道明显的 2-SAT 题。建边方式与模板题完全一致。主要不同的地方在于要判断是必须选择还是 ```Y\N``` 都可以。

设 $a_i$ 为某一奶牛是否希望 $i$ 通过，则对于奶牛的要求 $i, a_i, j, a_j$ 建边：

$(i+(!a_i)* n, j+a_j* n)$

$(j+(!a_j)* n, i+a_i* n)$

即如果法案 $i$ 不满足奶牛的要求，法案 $j$ 就必须满足奶牛的要求；如果法案 $j$ 不满足奶牛的要求，法案 $i$ 就必须满足奶牛的要求。

建完图后 Tarjan 求 scc 缩点。

先检查是否有 $i$ 与 $i+n$ 在同一 scc 中，若存在则直接输出```IMPOSSIBLE```。

若存在合法方案，则在缩点后的 dag 上从入度为 $0$ 的点开始搜索。

搜索时记录已经搜过的点和当前搜索路径上已经经过的点。当经过的点同时包括某个 $i$ 和 $i+n$ 时，显然后被遍历的必选，并且该点的后续也必选，因此再用一个 bool 变量记录是否有这样的 $i$ 即可。搜索时注意已经确定要选的点不需要再被遍历第二次。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e3+5;
inline int read(){
    int x=0,f=1,ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
    return x*f;
}
int n,m;
int hd_e[maxn],e_cnt,g_cnt,hd_g[maxn];
struct edge{int f,t,nxt;}e[maxn<<3],g[maxn];
void add_edge(int f,int t){
    e[++e_cnt]=(edge){f,t,hd_e[f]};
    hd_e[f]=e_cnt;
}
void add_g(int f,int t){
    g[++g_cnt]=(edge){f,t,hd_g[f]};
    hd_g[f]=g_cnt;
}
int dfn[maxn],low[maxn],tj_cnt;
int stk[maxn],stk_top;
bool vis[maxn];
int scc[maxn],scc_num;
void tarjan(int x){
    dfn[x]=low[x]=++tj_cnt;
    stk[++stk_top]=x;vis[x]=1;
    for(int i=hd_e[x];i;i=e[i].nxt){
        if(!dfn[e[i].t]){
            tarjan(e[i].t);
            low[x]=min(low[x],low[e[i].t]);
        }
        else if(vis[e[i].t])
            low[x]=min(low[x],low[e[i].t]);
    }
    if(low[x]==dfn[x]){
        scc[x]=++scc_num;vis[x]=0;
        while(stk[stk_top]!=x){
            scc[stk[stk_top]]=scc_num;
            vis[stk[stk_top]]=0;
            stk_top--;
        }stk_top--;
    }
}
char op[3]={'N','Y','?'};
bool mst[maxn],res[maxn];//必选的点，已经经过的点
void srch(int x,bool pl){
    vis[x]=res[x]=1;
    if(!pl)
    	for(int i=hd_g[x];i;i=g[i].nxt)
        	if(res[g[i].t]){pl=1;break;}
    mst[x]=pl;
    for(int i=hd_e[x];i;i=e[i].nxt)
        if(!mst[e[i].t])srch(e[i].t,pl);
    res[x]=0;
}
void shrink(){//缩点
    int cc=e_cnt;
    e_cnt=0;memset(hd_e,0,sizeof(hd_e));
    for(int i=1;i<=cc;i++){
        if(scc[e[i].f]==scc[e[i].t])continue;
        add_edge(scc[e[i].f],scc[e[i].t]);
    }
    for(int i=1;i<=n;i++){
        add_g(scc[i],scc[i+n]);
        add_g(scc[i+n],scc[i]);
    }
}
int main(){
    n=read();m=read();
    for(int i=1,c1,c2,c3,c4;i<=m;i++){
        c1=read(),c2=getchar(),c3=read(),c4=getchar();
        c2=(c2=='Y');c4=(c4=='Y');
        add_edge(c1+(!c2)*n,c3+c4*n);
        add_edge(c3+(!c4)*n,c1+c2*n);
    }
    for(int i=1;i<=2*n;i++)if(!dfn[i])tarjan(i);
    for(int i=1;i<=n;i++)if(scc[i]==scc[i+n]){printf("IMPOSSIBLE\n");return 0;}
    shrink();
    for(int i=scc_num;i>=1;i--)if(!vis[i])srch(i,0);
    for(int i=1;i<=n;i++){
        if(mst[scc[i+n]])printf("%c",op[1]);
        else if(mst[scc[i]])printf("%c",op[0]);
        else printf("%c",op[2]);
    }putchar('\n');
    return 0;
}
```

---

## 作者：OIerAlbedo (赞：1)

# 前言
如果你学过2-SAT，那你应当稍加思考会这道题。
# 题意
给你 $ m $ 个约束条件，要你决定 $ n $ 个方案是Y还是N还是不确定,使得 $ m $ 个约束条件都能满足。
# 前置思路
将第 $ i $ 个方案通过定为 $ i $ ,不通过定为 $ i+n $ ,那么对于奶牛的要求就可以连边了，具体情况如下。


1. $ i $ 不通过或 $ j $ 通过----若 $ i $ 通过，则 $ j $ 通过；若 $ j $ 为不通过则 $ i $ 不通过-----连 $ i $ 与 $ j $ 和 $ j+n $ 与 $ i+n $ 。

2. $ i $ 不通过或 $ j $ 不通过----若 $ i $ 通过，则 $ j $ 不通过；若   $ j $ 通过则 $ i $ 不通过-----连 $ i $ 与 $ j+n $ 和 $ j $ 与 $ i+n $ 。
  
3. $ i $ 通过或 $ j $ 通过----若 $ i $ 不通过，则 $ j $ 通过；若 $ j $ 不通过则 $ i $ 通过-----连 $ i+n $ 与 $ j $ 和 $ j+n $ 与 $ i $ 。

4. $ i $ 通过或 $ j $ 不通过----若 $ i $ 不通过，则 $ j $ 不通过；若   $ j $ 通过则 $ i $ 通过-----连 $ i+n $ 与 $ j+n $ 和 $ j $ 与 $ i $ 。

连好边之后，我们可以发现在一个强连通分量内的点状态是一样的，我们用Tarjan求出强联通分量，然后判断 $ i $ 与 $ i+n $ 是否在同一个强联通分量内，因为一个方案不可能既是通过又是不通过。

# 真正思路
刚才我们已经算出了方案的可行性，算方案的话就会比较麻烦，一般2-SAT问题都是判断 $ i $ 与 $ i+n $ 哪个先遍历到，就选哪一个状态，这在只有唯一解是固然可行，但是这道题目要我们算是否有多解，所以我们考虑每个点做两次Tarjan，第一次 $ i $ ,第二次 $ i+n $ ,判断两次算出的解是否一样。如果不一样则有多解。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int e[2000000],h[2000000],f[2000000],a[2000000],b[2000000],d[2000000],stak[2000000],dfn[2000000],low[2000000];
bool cut[2000000],u[2000000];
int root,j,T,n,m,cnt,tt,id,tot,i,xx,yy,x,y;
bool flag;
string s1,s2;
void add(int x,int y)
{
	cnt++;a[cnt]=y;b[cnt]=d[x];d[x]=cnt;
}
void tarjan(int x)
{
	tt++;dfn[x]=tt;low[x]=dfn[x];id++;stak[id]=x;u[x]=true;
	for (int i=d[x];i;i=b[i])
	     {
	     	if (dfn[a[i]]==0) 
	     	    {
	     	    	tarjan(a[i]);
	     	    	low[x]=min(low[x],low[a[i]]);
				 }
			else if (u[a[i]]) low[x]=min(low[x],dfn[a[i]]);
		 }
	if (low[x]==dfn[x])
	     {
	     	tot++;h[x]=1;
	     	while (1)
	            {
	            	f[stak[id]]=tot;
	            	u[stak[id]]=false;id--;
	            	if (stak[id+1]==x) break;
				}
		 }
	return;
}
int main()
{
	   	tt=0;id=0;tot=0;cnt=0;
	   	for (i=1;i<=2*n;i++) dfn[i]=0,low[i]=0,d[i]=0,u[i]=0,f[i]=0;
	cin>>n>>m;
	for (i=1;i<=m;i++)
	     {
	     	cin>>x>>s1>>y>>s2;
	     	if (s1[0]=='Y') xx=1;else xx=0;
	     	if (s2[0]=='Y') yy=1;else yy=0;
	     	if ((xx==0)&(yy==0)) {add(x+n,y);add(y+n,x);}
	     	if ((xx==1)&(yy==1)) {add(x,y+n);add(y,x+n);}
	     	if ((xx==1)&(yy==0)) {add(x,y);add(y+n,x+n);}
	     	if ((xx==0)&(yy==1)) {add(x+n,y+n);add(y,x);}
		 }
	for (i=1;i<=2*n;i++)
	    if (dfn[i]==0) 
		    {
			root=i;tarjan(i);
		    }
	flag=true;
	for (i=1;i<=n;i++)
	    if (f[i]==f[i+n])
	        flag=false;
//	for (i=1;i<=2*n;i++) e[i]=f[i];
	//tt=0;id=0;tot=0;
  // 	for (i=1;i<=2*n;i++) dfn[i]=0,low[i]=0,u[i]=0,f[i]=0;
//	for (i=n*2;i>=1;i--)
//	    if (dfn[i]==0) tarjan(i);
	if (flag==false) { puts("IMPOSSIBLE");return 0;}
	for (j=1;j<=n;j++)
	     {
	     	tt=0;id=0;tot=0;
	   	for (i=1;i<=2*n;i++) dfn[i]=0,low[i]=0,u[i]=0,f[i]=0;
	   	tarjan(j);
	   	if (dfn[j+n]==0) tarjan(j+n);
	   	xx=f[j];yy=f[j+n];
	   		tt=0;id=0;tot=0;
	   	for (i=1;i<=2*n;i++) dfn[i]=0,low[i]=0,u[i]=0,f[i]=0;
	   	tarjan(j+n);
	   	if (dfn[j]==0) tarjan(j);
	   	if ((xx<yy)&(f[j]>f[j+n])||(xx>yy)&(f[j]<f[j+n])) printf("?");
	   	else if (xx<yy) printf("N");
	   	else printf("Y");
		 }
	return 0;
}
```


---

## 作者：yzxoi (赞：1)

[My Blog](https://yzxoi.top/archives/1699)

## Description

给出 $n$ 个法案，$m$ 头牛的意见， 每头牛会表决两次。
每次表决格式为 `i Y` 表示“支持 $i$ 号法案”或 `i N` 表示“反对 $i$ 号法案”。
最终，每头牛至少要有一个表决被满足。不可能成立的话输出 `IMPOSSIBLE`，否则输出方案。

$1\leq N \leq 1,000,1\leq M \leq 4,000$

## Solution

显然是 2-SAT。

对于每头牛的表决，只要根据“若某个表决是错误的，那么另一个表决一定是对的“条件来建图即可。

然后判断一下是否合法（只要每个法案的两种状态均不在同一个连通块即可）

最后对于每个法案，暴力枚举该法案是否成立，然后跑一次 DFS 判断下是否有矛盾即可。

## Code

```c++
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define W while
#define I inline
#define RI register int
#define LL long long
#define Cn const
#define CI Cn int&
#define gc getchar
#define D isdigit(c=gc())
#define pc(c) putchar((c))
#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((x)>(y)?(x):(y))
using namespace std;
namespace Debug{
	Tp I void _debug(Cn char* f,Ty t){cerr<<f<<'='<<t<<endl;}
	Ts I void _debug(Cn char* f,Ty x,Ar... y){W(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	Tp ostream& operator<<(ostream& os,Cn vector<Ty>& V){os<<"[";for(Cn auto& vv:V) os<<vv<<",";os<<"]";return os;}
	#define gdb(...) _debug(#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
namespace FastIO{
	Tp I void read(Ty& x){char c;int f=1;x=0;W(!D) f=c^'-'?1:-1;W(x=(x<<3)+(x<<1)+(c&15),D);x*=f;}
	Ts I void read(Ty& x,Ar&... y){read(x),read(y...);}
	Tp I void write(Ty x){x<0&&(pc('-'),x=-x,0),x<10?(pc(x+'0'),0):(write(x/10),pc(x%10+'0'),0);}
	Tp I void writeln(Cn Ty& x){write(x),pc('\n');}
}using namespace FastIO;
Cn int N=1010,M=4010;
int n,m,fir[N<<1],nxt[M<<1],son[M<<1],tot,dfn[N<<1],low[N<<1],stk[N<<1],col[N<<1],top,cnt,cc,vis[N<<1];
I int opp(CI x){return x>n?x-n:x+n;}
I void Add(CI x,CI y){nxt[++tot]=fir[x],fir[x]=tot,son[tot]=y;}
#define to son[i]
I void Tarjan(CI x){
	dfn[x]=low[x]=++cnt,stk[++top]=x;
	RI i;for(i=fir[x];i;i=nxt[i]) if(!dfn[to]) Tarjan(to),low[x]=min(low[x],low[to]);else if(!col[to]) low[x]=min(low[x],dfn[to]);
	if(dfn[x]==low[x]){col[x]=++cc;W(stk[top]^x) col[stk[top--]]=cc;top--;}
}
I void dfs(CI x){
	if(vis[x]) return ;
	vis[x]=1;RI i;for(i=fir[x];i;i=nxt[i]) if(!vis[to]) dfs(to);
}
I int check(CI x){
	RI i;memset(vis,0,sizeof(vis));dfs(x);for(i=1;i<=n;i++) if(vis[i]&&vis[i+n]) return 0;return 1;//判断是否可行
}
int main(){
	RI i,x,y;char a,b;for(read(n,m),i=1;i<=m;i++) scanf("%d %c %d %c",&x,&a,&y,&b),x+=(a=='Y')*n,y+=(b=='Y')*n,Add(x,opp(y)),Add(y,opp(x));//反向建
	for(i=1;i<=(n<<1);i++) if(!dfn[i]) Tarjan(i);for(i=1;i<=n;i++) if(col[i]==col[i+n]) return puts("IMPOSSIBLE"),0;//无解判断
	for(i=1;i<=n;i++) x=check(i),y=check(i+n),(x&&y)?(pc('?'),0):x?(pc('Y'),0):(pc('N'),0);
	return 0;
}
```



---

## 作者：Igallta (赞：0)

有点板。

这题我的思路是先用 2 - SAT 判断有没有合法的方案，这个直接套板子就可以。

注意建图的时候要这样建：

```
		if (c == 'N') {
			i1 = 1;
		}
		if (d == 'N') {
			i2 = 1;
		}
		vec[a + n * !i1].push_back(b + n * i2);
		vec[b + n * !i2].push_back(a + n * i1);
```

例：$a$ 法案需要通过，$b$ 法案需要驳回。

那么这个建图方式的意思是：如果 $a$ 被驳回了，那么 $b$ 必须被驳回才能合法；如果 $b$ 被通过了，那么 $a$ 也必须被通过才能合法。

然后这题的输出有一点独特，它并不是只求一个方案，而是求所有方案里的这个法案能不能通过。

我的思路是分别判断这个法案通过和不通过行不行。

如果这个法案通过和不通过都行那就输出 `?`，如果这个法案可以通过而且不能不通过那就输出 `Y`，否则输出 `N`。

---

## 作者：MSavannah (赞：0)

**Solution**

每头牛有两个意见必须满足其一，求有没有合法解，一眼 2-SAT。

设 $i$ 表示支持第 $i$ 号法案，$i+n$ 表示反对第 $i$ 号法案。连边。

连边之后缩点，如果 $i$ 和 $i+n$ 在同一个强连通分量中，显然不合法。

那么有解时候怎么输出方案，直接枚举 $i$，DFS 直接判断，当我们钦定支持 $i$ 的时候会不会出现冲突即可。

时间复杂度 $O(n^2)$。

[code](https://www.luogu.com.cn/record/158596929)

---

## 作者：_anll_ (赞：0)

## 题目大意
给你 $n$ 个布尔类型， $m$ 个约束方程，其格式均为 $a \vee b$，问你该方程是否能被满足。如果不能，输出 `IMPOSSIBLE`，否则判断对于每个布尔类型是只能为真还是只能为假还是真假都可。

## 大体思路
前置芝士：[P4782 【模板】2-SAT](https://www.luogu.com.cn/problem/P4782)，也可以查看这篇蒟蒻写的[学习笔记](https://www.luogu.com.cn/blog/is-saliang-awa/post-2-sat)。

建图是比较裸的或形式和建反边，设 $i$ 号点为支持第 $i$ 个法案，$i+n$ 号点为反对。建图方式在这里就不再赘述了，不懂的话可以去上面的两个链接学习一下。

有思维空间的是输出部分，问你每个布尔类型可能的状态，而不是基础的求解。

对于 `IMPOSSIBLE` 很简单，tarjan 之后直接判断 $i$ 和 $i+n$ 是否都在同一强连通内即可。

对于有解的情况，缩点建新图后暴力查找。如果可以从 $i$ 所在的强连通跑到 $i+n$，就说明会从真状态推到假状态，所以这个方案只能不通过。同理，如果可以从 $i+n$ 所在的强连通跑到 $i$，就说明只能通过。若两点互不可达，就说明互不影响，通不通过都可。

## 代码展示
大体思路就是这样，如果有不清晰的地方，还请结合代码理解。

```cpp
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
struct Edge{
    int l,nxt;
}edges[16005],ed[16005];
int n,m,tt=1,ttt=1,head[2005],h[2005];
int tot,dfn[2005],low[2005];
int top,stk[2005],instk[2005];
int cnt,scc[2005],vu[2005];
void add_edge(int f,int l){
    tt+=1;
    edges[tt]={l,head[f]};
    head[f]=tt;
}
void add(int f,int l){
    ttt+=1;
    ed[ttt]={l,h[f]};
    h[f]=ttt;
}
void tarjian(int x){
    tot+=1,top+=1;
    dfn[x]=low[x]=tot;
    instk[x]=1,stk[top]=x;
    for(int i=head[x];i;i=edges[i].nxt){
        int l=edges[i].l;
        if(!low[l]){
            tarjian(l);
            low[x]=min(low[x],low[l]);
        }
        else if(instk[l]) low[x]=min(low[x],dfn[l]);
    }
    if(dfn[x]==low[x]){
        int y;cnt+=1;
        do{
            y=stk[top],top-=1,instk[y]=0;
            scc[y]=cnt;
        }while(y!=x);
    }
}
void dfs(int x){
    vu[x]=1;
    for(int i=h[x];i;i=ed[i].nxt){
        int l=ed[i].l;
        if(!vu[l]) dfs(l);
    }
}
int check(int x){
    memset(vu,0,sizeof(vu));
    dfs(scc[x]);
    if(x>n) return vu[scc[x-n]];
    return vu[scc[x+n]];
}
signed main(){
    int f,l;char a,b;
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>f>>a>>l>>b;
        if(a=='Y'){
            if(b=='Y') add_edge(f+n,l),add_edge(l+n,f);
            else add_edge(f+n,l+n),add_edge(l,f);
        }
        else{
            if(b=='Y') add_edge(f,l),add_edge(l+n,f+n);
            else add_edge(f,l+n),add_edge(l,f+n);
        }
    }
    for(int i=1;i<=2*n;i++) if(!dfn[i]) tarjian(i);
    for(int i=1;i<=n;i++){
        if(scc[i]==scc[i+n]){
            cout<<"IMPOSSIBLE";
            return 0;
        }
    }
    for(f=1;f<=2*n;f++){
        for(int i=head[f];i;i=edges[i].nxt){
            int l=edges[i].l;
            if(scc[f]==scc[l]) continue;
            add(scc[f],scc[l]);
        }
    }
    for(int i=1;i<=n;i++){
        if(check(i)) cout<<'N';
        else if(check(i+n)) cout<<'Y';
        else cout<<'?';
    }
    cout<<s;
    return 0;
}
```


---

## 作者：Coros_Trusds (赞：0)

$\rm 2-SAT$ 模板题。

# 题目大意

给出 $n$ 个法案， $m$ 头牛的意见， 每头牛会表决两次。  

每次表决格式为 `i Y` 表示“支持 $i$ 号法案”或 `i N` 表示“反对 $i$ 号法案”。  

最终，每头牛至少要有一个表决被满足。不可能成立的话输出 `IMPOSSIBLE`，否则输出方案。

$1\le n\le 1000,1\le m\le 4000$。

# 题目分析

首先建边方式跟模板题是没什么两样的，我们用 $x$ 来表示通过法案 $x$，$x'$ 表示驳回法案 $x$。

重点是如何求出每个方案是否能够被通过。

如果 $\forall x\in [1,n],x,x'$ 在同一连通块内，则无解。

结果是 `?` 亦即两个取值 $x,x'$ 都不会影响到一起，即 $x$ 能到达的所有点没有 $x'$，$x'$ 能到达的所有点没有 $x$。

如果是其他结果，在我们建出来的图中表现为选择 $x$ 或 $x'$ 会形成环，但不能同时兼备，兼备了就是无解了。

# 代码

```cpp
// Problem: P3007 [USACO11JAN] The Continental Cowngress G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3007
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Date:2022-05-28 23:01
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <cmath>
#include <stack>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	inline int read() {
		int ret = 0,f = 0;char ch = getchar();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getchar();
		}
		return f ? -ret : ret;
	}
	inline double double_read() {
		long long ret = 0,w = 1,aft = 0,dot = 0,num = 0;
		char ch = getchar();
		while (!isdigit(ch)) {
			if (ch == '-') w = -1;
			ch = getchar();
		}
		while (isdigit(ch) || ch == '.') {
			if (ch == '.') {
				dot = 1;
			} else if (dot == 0) {
				ret = (ret << 3) + (ret << 1) + ch - 48;
			} else {
				aft = (aft << 3) + (aft << 1) + ch - '0';
				num ++;
			}
			ch = getchar();
		}
		return (pow(0.1,num) * aft + ret) * w;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 4005;
struct Graph {
	int v,nxt;
} gra[N << 2];
int head[N << 1],dfn[N << 1],low[N << 1],col[N << 1];
bool in_stack[N << 1],vis[N << 1];
std::stack<int>st;
int n,m,idx,num,cnt;
inline void add(int u,int v) {
	gra[++ idx] = (Graph){v,head[u]},head[u] = idx;
}
inline void tarjan(int now) {
	dfn[now] = low[now] = ++ num,in_stack[now] = true;
	st.push(now);
	for (register int i = head[now];i;i = gra[i].nxt) {
		int v = gra[i].v;
		if (!dfn[v]) {
			tarjan(v);
			low[now] = std::min(low[now],low[v]);
		} else if (in_stack[v]) {
			low[now] = std::min(low[now],dfn[v]);
		}
	}
	if (dfn[now] == low[now]) {
		cnt ++;
		int u;
		do {
			u = st.top();st.pop();
			in_stack[u] = false,col[u] = cnt;
		} while (u != now);
	}
}
inline void dfs(int now) {
	vis[now] = true;
	for (register int i = head[now];i;i = gra[i].nxt) {
		int v = gra[i].v;
		if (!vis[v]) {
			dfs(v);
		}
	}
}
inline bool check(int now) {
	mst(vis,false);
	dfs(now);
	for (register int i = 1;i <= n; ++ i) {
		if (vis[i] == true && vis[i + n] == true) {
			return true;
		}
	}
	return false;
}
int main(void) {
	std::cin >> n >> m;
	for (register int i = 1;i <= m; ++ i) {
		int a,b;
		char Ta[5],Tb[5];
		std::cin >> a >> Ta >> b >> Tb;
		char ta = Ta[0],tb = Tb[0];
		if (ta == 'N' && tb == 'N') {
			add(a,b + n),add(b,a + n);
		} else if (ta == 'N' && tb == 'Y') {
			add(a,b),add(b + n,a + n);
		} else if (ta == 'Y' && tb == 'N') {
			add(a + n,b + n),add(b,a);
		} else if (ta == 'Y' && tb == 'Y') {
			add(a + n,b),add(b + n,a);
		}
	}
	for (register int i = 1;i <= 2 * n; ++ i) {
		if (!dfn[i]) {
			tarjan(i);
		}
	}
	for (register int i = 1;i <= n; ++ i) {
		if (col[i] == col[i + n]) {
			puts("IMPOSSIBLE");
			return 0;
		}
	}
	for (register int i = 1;i <= n; ++ i) {
		bool ta = check(i),tb = check(i + n);
		if (ta == true && tb == false) putchar('N');
		else if (ta == false && tb == true) putchar('Y');
		else if (ta == false && tb == false) putchar('?');
	}
	
	return 0;
}
```

---

## 作者：Iam1789 (赞：0)

2-SAT 板题。

对于第 $i$ 条法案开两个点 $i$ 和 $i+n$。对于每条限制 $A,B$，若 $A$ 没被满足则 $B$ 必须满足，反之同理，因此连两条边 $a_{i\oplus1},b_j$ 和 $b_{j\oplus1},a_i$。

之后就是常规的 tarjan 求 SCC 了，注意 tarjan 求出来的拓扑序是反的，输出答案的时候要注意。

之后就是判定第 $i$ 条法案是否表决或者通过都可以了。
### 方法一
由于这题数据范围很小，我们每次判定可以直接从 $i$ 和 $i+n$ 开始爆搜，如果都无法互相到达，说明该法案的选择无影响，时间复杂度是 $O(nm)$ 的。~~但是我实现的不好 TLE 了。~~
### 方法二
于是我们换一种方式，缩点进行拓扑排序，每个点用一个 vector 来记录它可以被哪些点到达，在拓扑的过程中维护，时间复杂度依然是 $O(nm)$ 的，但可以起到不错的常数优化。~~但是它又 MLE 了~~
### 方法三
于是我们十分愤怒，直接开了 $2n$ 个 bitset。依然是拓扑排序，但是每个点我们开一个 bitset，第 $i$ 位为 $1$ 说明 $i$ 可以到达这个点，依然是在拓扑的过程中维护，时间复杂度也还是 $O(nm)$ 的，但是 bitset 常数极小，跑的飞快，再加上 bitset 每一位仅占用 $1$ 个 bit 位，空间占用也很小。于是我们~~在 O2 的加持下~~拿到了本题的最优解。
## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
		f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		s=s*10+c-'0';
		c=getchar();
	}
	return s*f;
}
inline bool read_bool()
{
	char c=getchar();
	while(c!='Y'&&c!='N')
	c=getchar();
	if(c=='Y')
	return 0;
	return 1;
}
int n,m;
vector <int> a[4007],b[4007];
int dfn[4007],low[4007],col[4007],tot,jss;
bool vis[4007];
bitset <2007> jl[2007];
stack <int> s;
inline void get_col(int y)
{
	int x=-1;
	++jss;
	while(x!=y)
	{
		x=s.top();
		s.pop();
		vis[x]=0;
		col[x]=jss;
	}
}
void tarjan(int x)
{
	++tot;
	dfn[x]=low[x]=tot;
	s.push(x);
	vis[x]=1;
	int siz=a[x].size();
	for(int i=0;i<siz;++i)
	{
		int v=a[x][i];
		if(!dfn[v])
		{
			tarjan(v);
			low[x]=min(low[x],low[v]);
		}
		else if(vis[v])
		low[x]=min(low[x],dfn[v]);
	}
	if(low[x]==dfn[x])
	get_col(x);
}
char ans[2]={'N','Y'};
int ff[8007],tt[8007],rd[4007];
int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;++i)
	{
		int x=read(),xk=read_bool(),y=read(),yk=read_bool();
		ff[i*2-1]=x+(xk^1)*n,tt[i*2-1]=y+yk*n;
		a[x+(xk^1)*n].push_back(y+yk*n);
		ff[i*2]=y+(yk^1)*n,tt[i*2]=x+xk*n;
		a[y+(yk^1)*n].push_back(x+xk*n);
	}
	for(int i=1;i<=2*n;++i)
	{
		if(!dfn[i])
		tarjan(i);
	}
	for(int i=1;i<2*m;++i)
	{
		if(col[ff[i]]!=col[tt[i]])
		b[col[ff[i]]].push_back(col[tt[i]]),++rd[col[tt[i]]];
	}
	queue <int> q;
	for(int i=1;i<=jss;++i)
	{
		if(!rd[i])
		q.push(i);
		jl[i][i]=1;
	}
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=0;i<b[u].size();++i)
		{
			int v=b[u][i];
			--rd[v];
			jl[v]|=jl[u];
			if(!rd[v])
			q.push(v);
		}
	}
	for(int i=1;i<=n;++i)
	{
		if(col[i]==col[i+n])
		{
			puts("IMPOSSIBLE");
			return 0;
		}
	}
	for(int i=1;i<=n;++i)
	{
		if(!(jl[col[i]][col[i+n]]|jl[col[i+n]][col[i]]))
		putchar('?');
		else
		putchar(ans[col[i]<col[i+n]]);
	}
	return 0;
}
```
## 后记
关于方法一和方法二，方法一如果你实现得漂亮一些的话是可以过去的，毕竟时间复杂度是没有问题的。方法二你直接去暴力维护你时空可能会炸，你需要对 vector 进行去重。这样时间复杂度和空间复杂度都是 $O(nm)$，是正确的，完全可以过。


---

## 作者：Mosher (赞：0)

### 2-SAT的题，没看出来可以去模板学下

**正文：**

1. 建边：i为同意，i+n为反对

	由题：每头牛的对应两种提案，**二者必选其一，可多选**，利用反向关系建图即可：

	```cpp
	for(int i=1,x,y;i<=m;++i){
		scanf("%d%s%d%s",&x,s1,&y,s2);
		if(s1[0]=='Y'&&s2[0]=='Y'){
			add(x+n,y);//若x反对，y必须同意
			add(y+n,x);//若y同意，x必须同意
		}
		else if(s1[0]=='N'&&s2[0]=='Y'){
			add(y+n,x+n);//若y反对，x必须反对，以下同理
			add(x,y);
		}
		else if(s1[0]=='N'&&s2[0]=='N'){
			add(x,y+n);
			add(y,x+n);
		}
		else if(s1[0]=='Y'&&s2[0]=='N'){
			add(x+n,y+n);
			add(y,x);
		}
	}
	```

2. 算法，思路：tarjan+dfs，判环以及成立关系

3. 难点：‘？’怎么搞？
	
    其实只需知道i和i+n都可行，则为‘？’，其他亦然
    
**Code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4+5;
char ans[maxn],s1[3],s2[3];
int low[maxn],dfn[maxn],col[maxn],n,m,dfs_clock,tot,size,head[maxn];
struct node{
	int v,nxt;
}e[maxn];
bool vis[maxn];

void add(int u,int v){
	e[++size].v=v;
	e[size].nxt=head[u];
	head[u]=size;
}

stack<int>s;
void tarjan(int u){
	s.push(u);
	dfn[u]=low[u]=++dfs_clock;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!col[v]) low[u]=min(low[u],low[v]);
	}
	int k;
	if(low[u]==dfn[u]){
		++tot;
		do{
			k=s.top();s.pop();
			col[k]=tot;
		}while(k!=u);
	}
}

void dfs(int u){
	if(vis[u]) return;
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
		if(!vis[e[i].v]) dfs(e[i].v);
}

bool check(int u){
	memset(vis,0,sizeof(vis));
	dfs(u);
	for(int i=1;i<=n;++i)
		if(vis[i]&&vis[i+n]) return 0;
	return 1;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;++i){
		scanf("%d%s%d%s",&x,s1,&y,s2);
		if(s1[0]=='Y'&&s2[0]=='Y'){
			add(x+n,y);
			add(y+n,x);
		}
		else if(s1[0]=='N'&&s2[0]=='Y'){
			add(y+n,x+n);
			add(x,y);
		}
		else if(s1[0]=='N'&&s2[0]=='N'){
			add(x,y+n);
			add(y,x+n);
		}
		else if(s1[0]=='Y'&&s2[0]=='N'){
			add(x+n,y+n);
			add(y,x);
		}
	}
	for(int i=1;i<=n<<1;++i) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;++i)
		if(col[i]==col[i+n]) return puts("IMPOSSIBLE"),0;//i，i+n都要选，则无解
	for(int i=1;i<=n;++i){
		bool a=check(i),b=check(i+n);
		if(a&&b) ans[i]='?';
		else if(!a&&b) ans[i]='N';
		else if(a&&!b) ans[i]='Y';
	}
	for(int i=1;i<=n;++i) printf("%c",ans[i]);
}
```


---

## 作者：mengdai (赞：0)

我用这题来练2-SAT

因为我常用的某题库上面貌似没有2-SAT特别好的例题

我们可以把所有的会议看做是点，通过Y/N来拆开成为两个点i,i'

然后通过每一头奶牛来建边，如果考虑猜中那很难建边(至少我没想过)

那么我们考虑其中一个方案没有猜对，那么另外一个方案必须猜对了，那么就连边咯

然后考虑每一个方案的两种可能，dfs一下判断是什么情况

人生第一道2-SAT题

==================================代码分割线======================================

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,m,cnt;
int last[2003],ans[2003];
bool mark[2003];
char ch[3]={'?','N','Y'};
struct edge{
    int to,next;
}e[8003];
inline int get(){
    int x;
    cin>>x;
    char c=getchar();
    while(c!='Y'&&c!='N')  c=getchar();
    if(c=='Y'){
        x=x*2-1;
    }else{
        x=x*2;
    }
    return x;
}
inline void insert(int u,int v){
    e[++cnt].to=v; e[cnt].next=last[u]; last[u]=cnt;
}
void dfs(int x){
    mark[x]=1;
    for(int i=last[x];i;i=e[i].next){
        if(!mark[e[i].to]){
            dfs(e[i].to);
        }
    }
}
bool check(int x){
    memset(mark,0,sizeof(mark));
    dfs(x);
    for(int i=1;i<=n;i++){
        if(mark[2*i]&&mark[2*i-1]){
            return 0;
        }
    }
    return 1;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int a=get(),b,c=get(),d;
        if(a&1){
            b=a+1;
        }else{
            b=a-1;
        }
        if(c&1){
            d=c+1;
        }else{
            d=c-1;
        }
        insert(b,c);  insert(d,a);
    }
    for(int i=1;i<=n;i++){
        bool p=check(2*i-1);
        bool q=check(2*i);
        if(!p&&!q){
            cout<<"IMPOSSIBLE"<<endl;
            return 0;
        }else if(p&&q){
            ans[i]=0;
        }else if(!p){
            ans[i]=1;
        }else{
            ans[i]=2;
        }
    }
    for(int i=1;i<=n;i++){
        cout<<ch[ans[i]];
    }
    return 0;
}
```
/\*

in:
,

out:
YN?

\*/
==================================代码分割线======================================


---

