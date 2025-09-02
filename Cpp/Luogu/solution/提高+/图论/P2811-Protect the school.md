# Protect the school

## 题目背景

话说上回保安因为奶牛事件而搞得地位岌岌可危，所以他们决定好好看守这个学校，他们有一个计划。但是由于学校太大了，他们计划不好，所以找到上次帮他的你，请你解决他的苦难。然后他又可以开始了手机游戏之旅。


## 题目描述

学校有 $n$ 个检查点，由于保安懒得动脑筋，他们决定在这 $n$ 个检查点之间建立 $m$ 条通道，由于学校的懒政以及军事化管理，这些路是单向的，逆向通过会被处分。保安们人手不够（游戏任务太多），他们决定只挑选一些点来站岗，由于保安身怀绝技，可以瞬间通过任何他站岗点可以走到的路（瞬移到到任何连通的点）。每一个检查点有一个值表示这个点的困难程度。为了保护学校，请你帮他们出个主意，保证一旦有一个检查点发生事件，都能有保安瞬间抵达。但是为了舒服和管理便利，请你告诉他们在使用最少的保安数量的情况下最小的困难总和。


## 说明/提示

$1 \le n \le 10 ^ 4,1 \le m \le 5 \times 10 ^ 4$，保证答案在 `int` 范围内。

## 样例 #1

### 输入

```
5
31619 26195 18669 1198 178
4
2 4
3 5
1 2
4 1```

### 输出

```
20045 1```

# 题解

## 作者：logfk (赞：9)

## 前置知识
tarjan

[缩点](https://www.luogu.com.cn/problem/P3387)

## 题意

有 $n$个点，$m$条边，每个点有一个点权，求选择某些点后，使得每个点**始终**能够到达，且选择的点权和最小，并求出点权和最小的方案数。

## 分析

为什么要缩点？

题目中要求最少的保安，而一个保安就可以控制一个环，所以可以用缩点求出最少的保安数。

如何理解**始终**？

就是说，你在处理一个紧急事件后，仍旧能够处理其他所有的紧急事件，讨论区中有一个比较有趣的问题，是对样例的错误分析，我们把样例搞出来。

![](https://cdn.luogu.com.cn/upload/image_hosting/fw17qk0e.png)

疑问是：选择 $3$、$4$后图就是能够到达的，但是出现了一个问题：$3$处理了 $5$之后，这个保安便不能再回到 $3$了，所以说没有满足始终这个约束条件。


------------

所以我们得出，缩点后，每个点的值（或者环中的最小值）的总和便是我们要求的最小点权和，至于方案数，每个环中可能有多个最小值，使用乘法原理解决即可。

## 代码部分

```cpp
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
vector <int>a[10010];
int sta[10010],top=0,flag[10010],num,tot,col[10010],ss[10010];
int ans,va[10010],dfn[10010],low[10010],ans1=1,mm[10010],nn[10010],sc[10010];
void tarjan(int x)//标准tarjan缩点
{
    sta[++top]=x;
    flag[x]=1;
    dfn[x]=low[x]=++num;
    for(int i=0;i<a[x].size();i++)
    {
        int y=a[x][i];
        if(!dfn[y])
        {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }
        else
        {
            if(flag[y])
            {
                low[x]=min(low[x],dfn[y]);
            }
        }
    }
    if(dfn[x]==low[x])
    {
        tot++;
        while(sta[top+1]!=x)
        {
            col[sta[top]]=tot;
            ss[tot]+=va[sta[top]];
            flag[sta[top--]]=0;
        }
    }
}
int read()
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
int main()
{
	memset(mm,0x3f,sizeof(mm));
    int n,m,u,v;
    n=read();
    for(int i=1;i<=n;i++)
    {
        va[i]=read();
    }
    m=read();
    for(int i=1;i<=m;i++)
    {
    	u=read(),v=read();
        a[u].push_back(v);
    }
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i]) tarjan(i);
    }
    for(int i=1;i<=n;i++)//把点或者环的最小值处理出来，并且统计最小值的数量
    {
    	if(!sc[col[i]])
    	{
    		sc[col[i]]=col[i];
    	}
    	if(va[i]<mm[col[i]])
    	{
    		mm[col[i]]=va[i];
    		nn[col[i]]=1;
    	}
    	else
    	{
    		if(va[i]==mm[col[i]])
    		{
    			nn[col[i]]++;
    		}
    	}
    }
    for(int i=1;i<=n;i++)//一加一乘，解决战斗
    {
    	if(sc[i])
    	{
    		ans+=mm[sc[i]];
    		ans1*=nn[sc[i]];
    	}
    }
	cout<<ans<<" "<<ans1<<endl;
}
```

蒟蒻实力不足，有问题欢迎指出

---

## 作者：_xxxxx_ (赞：1)

### 题意

给出一张图，不保证联通。对于在一个强连通分量里的点中，要选择一个点将它染色，染色一次的花费为这个点的点权。问最小花费及有多少种方案可以达到这个最小花费。

### 分析

易想到用 tarjan 缩点来解决。

每个强连通分量中都必须要选一个点，可以看出，最小花费为每个强连通分量中最小值的和。

维护每个强连通分量中的最小值出现次数，通过乘法原理可得知，方案数量就是所有出现次数的乘积。

### 代码

```cpp
#include <iostream>
#include <stack>
#include <cmath>
#include <vector>
#include <map>
#include <string.h>
#include <queue>
#include <stdio.h>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
int n;
int a[N];
int head[N], ne[N], to[N], w[N], id;
void add(int x, int y)
{
	to[++id] = y;
	ne[id] = head[x];
	head[x] = id;
}
int m;
int dfn[N], dn;
int sta[N], top, k;
int low[N], mn[N], num[N];
//mn：连通块中的最小值
//num：连通块中的最小值的出现次数 
bool vis[N];
void tarjan(int u)
{
	low[u] = dfn[u] = ++dn;
	vis[u] = 1;
	sta[++top] = u;
	for(int i = head[u]; i; i = ne[i])
	{
		int v = to[i];
		if(!dfn[v])
		{
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if(vis[v]) low[u] = min(low[u], dfn[v]);
	}
	//tarjan板 
	if(dfn[u] == low[u])
	{
		k++;
		while(sta[top + 1] != u)
		{
			int now = sta[top--];
			vis[u] = 0;
			if(mn[k] == a[now]) num[k]++;//最小值相同 
			else if(mn[k] > a[now]) num[k] = 1, mn[k] = a[now];//新的最小值 
		}
	}
}
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i], mn[i] = 1e9;
	cin >> m;
	for(int i = 1; i <= m; i++)
	{
		int x, y;
		cin >> x >> y;
		add(x, y);
	}
	for(int i = 1; i <= n; i++)
	{
		if(!dfn[i]) tarjan(i);
	}
	int ans = 0, cnt = 1;//注意 
	for(int i = 1; i <= k; i++)
	{
		ans += mn[i];//花费加 
		cnt *= num[i];//方案乘 
	}
	cout << ans << " " << cnt << endl;
	return 0;
}
```

---

## 作者：EastPorridge (赞：1)

### 题目大意：
给你一个有 $n$ 点 $m$ 条边的有向有环图，每个点都有点权 $w$ ，让你求出最少取多少个点时能使任意点能被到达且能到达这个点的点能返回它的原点，求此时所取的最小点权和方案数。

### 思路：
看到一张有向有环的图，我们可以使用 tarjan 算法进行缩点，将原图转化为一张 DAG 。那么，我们此时的问题便转化为：求每个强连通分量上的最小点，统计综合，并计算此时的方案数。

我们可以在 $tarjan$ 时更新最小的困难值 $w[i]$ ，并更新最小的困难值的数量 $size[i]$ 。

那么此时答案的最小困难值为 $\sum_{i=1}^{scc_{sum}}min[i]$ ，方案数为 $\prod_{i=1}^{scc_{sum}}size[i]$ 。

特别注意的数据范围： $1 \le n \le 10000 , 1 \le m \le 50000$ 。

题目描述 $m$ 的范围并不能让你通过所有的数据。

时间复杂度： $O(n+m)$ 。

#### Code.
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+10,M=1e6+10;
int n,m,h[N],ne[M],e[M],idx,minn[N],dfn[N],low[N],scc_cnt,stk[N],nowstep,tt,w[N],sz[N];
bool in_stk[N];
void add(int u,int v) {ne[++idx]=h[u],e[idx]=v,h[u]=idx;}
void tarjan(int u)
{
	dfn[u]=low[u]=++nowstep;in_stk[u]=1,stk[++tt]=u;
	for(int i=h[u];~i;i=ne[i])
	{
		int j=e[i];
		if(!dfn[j])
		{
			tarjan(j);
			low[u]=min(low[u],low[j]);
		}
		else if(in_stk[j]) low[u]=min(low[u],dfn[j]);
	}
	if(low[u]==dfn[u])
	{
		int y;scc_cnt++;
		do
		{
			y=stk[tt--]; in_stk[y]=0;
			if(minn[scc_cnt] == w[y]) sz[scc_cnt]++;
			else
			{
				sz[scc_cnt]=1;
				minn[scc_cnt]=min(minn[scc_cnt],w[y]);
			}
		}while(y!=u);
	}
}
int main()
{
	memset(h,-1,sizeof h);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) minn[i]=INT_MAX; //minn初始赋极大值
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v); //建边
		add(u,v);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	int minh=0,sum=1;
	for(int i=1;i<=scc_cnt;i++) //统计答案
		minh+=minn[i],sum*=sz[i];
	printf("%d %d",minh,sum);
	return 0;
}
```
------------
更好的阅读体验：[这里](https://www.cnblogs.com/EastPorridge/p/16391773.html)

---

## 作者：ymx2009 (赞：0)

# 题目大意  
给定一个图，每个点有一个权值，在每个联通分量中选一个点使得权值之和最小，求最小权值和权值最小的方案数。  
# Solution  
Tarjan 求出每个联通分量，在每个联通分量中找权值最小值的个数，把每个联通分量中权值最小值的个数相乘即是答案。  
# 代码  

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e4+10;
int n,m,dfn[N],low[N],a[N],tot,cnt,p[N],res[N],t[N];
vector<int> e[N],ans[N];
stack<int> stk;
bool instk[N];
void tarjan(int x)//tarjan板子
{
	stk.push(x);
	instk[x]=true,dfn[x]=++tot,low[x]=tot;
	for(auto u:e[x])
	{
		if(!dfn[u])
		{
			tarjan(u);
			low[x]=min(low[u],low[x]);
		}
		else if(instk[u]) low[x]=min(low[x],dfn[u]);
	}
	if(low[x]==dfn[x])
	{
		res[++cnt]=0x7f7f7f7f;
		for(;1;)
		{
			int y=stk.top();
			stk.pop();
			res[cnt]=min(res[cnt],a[y]);
			ans[cnt].push_back(y);
			instk[y]=false,p[y]=cnt;
			if(x==y) return;
		}
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>m;
	for(;m--;)
	{
		int x,y;
		cin>>x>>y;
		e[x].push_back(y);
	}
	int ans1=0,ans2=1;
	for(int i=1;i<=n;i++)
	{
		if(!dfn[i]) tarjan(i);
	}
	for(int i=1;i<=cnt;i++) 
	{
		int s=0;
		ans1+=res[i];//求权值和最小值
		for(auto x:ans[i])if(a[x]==res[i])
			s++;
		ans2*=s;//求方案数
	}
	cout<<ans1<<' '<<ans2;
	return 0;
}
```

---

## 作者：Motonic_queues (赞：0)

# 题目大意  
给定一个带权有向图，从中选取一些点，是的从它们出发可以到达所有节点，给出最小的权值和。  

# 思路分析  
Tarjan 求 SCC 模板题，从每个强连通分量里找最小点，有多个就把个数乘进第二问里。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e4+5;
int n,m,ans1,ans2=1;
int w[N];
vector<int> e[N]; //邻接表存图

int dfn[N],low[N],cnt,scccnt;
bool vis[N];
stack<int> scc;
vector<int> inscc[N];
void TARJAN(int p){ // Tarjan 板子
	dfn[p]=low[p]=++cnt;
	vis[p]=1;
	scc.push(p);
	for(int i:e[p]){
		if(!dfn[i]){
			TARJAN(i);
			low[p]=min(low[p],low[i]);
		}else if(vis[i]){
			low[p]=min(low[p],dfn[i]);
		}
	}
	if(dfn[p]==low[p]){
		int tt=scc.top();
		scccnt++;
		do{
			tt=scc.top();
			inscc[scccnt].push_back(tt);
			scc.pop();
		}while(tt!=p);
	}
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>w[i];
	cin>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i])TARJAN(i);
	}
	for(int i=1;i<=scccnt;i++){
		int mn=1e9,mncnt=0;
		for(int p:inscc[i]){
			if(w[p]<mn)mn=w[p],mncnt=1;
			else if(w[p]==mn)mncnt++;
		}
		ans1+=mn,ans2*=mncnt; //更新答案
	}
	cout<<ans1<<' '<<ans2;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 一、前置芝士

------------
 [强连通分量](https://oi-wiki.org/graph/scc/)


### 二、分析

要求用最少的保安，则通过瞬移可以互相到达的点组成的图中，显然只需要一个保安（图必须是最大强联通子图，不然保安数就不是最小的）。

因为要使选择的检查点**困难值和**最小，所以每个图应选其最小值点，总方案数自然就是所有**最小困难值点个数之积** 。


------------
### 三、简明题意

给定一个有 $n$ 个点 $m$ 条边的有向图，求出所有极大强连通子图。若有 $k$ 个极大强联通子图,设 $v[i]$ 表示第 $i$ 个图的点权最小值,$cnt[i]$ 为最小值个数，则请输出

$$ans1=\sum_{i=1}^{k}v[i]$$

$$ans2=\prod_{i=1}^{k}cnt[i]$$

### 四、算法选择

说到强连通图，绝大多数 OIer 都会使用算法 Tarjan!

在此我想提醒大家，强连通图，除了 Tarjan，还有另一个简单易懂的算法 **Kosaraju** 。

它的特点就是简单，实现比 Tarjan 简单得多，调试也方便。


------------

### 五、算法介绍

Kosaraju 算法，简单来说就是将一个图正反跑两遍，来找到极大强连通图（以下简称图）。

感性地理解下，点 $A$，$B$ 属于同一个图，就是说指从存在路径 由 $A$ 到 $B$ 和由 $B$ 到 $A$。

Kosaraju 就是正向从 $A$ 出发跑到 $B$，再顺着反向边摸到 $B$。

------------

#### 算法流程

1. 对原图 $G$ 进行深度优先搜索，找出每个节点的完成时间(时间戳)。

2. 选择完成时间较大的节点开始，对逆图 $GT$ 搜索，能够到达的点构成一个强连通分量。

3. 如果所有节点未被遍历，重复2，否则算法结束。

------------
### 六、具体实现

```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void rd(T&x){
	T f=1;x=0;char ch=getchar();
	while(!isdigit(ch))f=(ch=='-')?-1:1,ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	x*=f;
}
const int M=30010;
struct Edge{int to,nxt;}e[M<<1],e2[M<<1];//e为正向图，e1为反向图 
int tot,hd[M],hd2[M];
inline void addedge(int x,int y){
	e[++tot]={y,hd[x]};
	hd[x]=tot;			
	e2[tot]={x,hd2[y]};
	hd2[y]=tot;
}//正向图和反向图 
int a[M],n,m,d[M],kt,vis[M];
void dfs1(int x){
	vis[x]=1;
	for(int i=hd[x];i;i=e[i].nxt){
		int go=e[i].to;
		if(!vis[go])dfs1(go);
	}
	d[++kt]=x; //在完成时记录完成时间 
}// 跑第一遍 
int sum=INT_MAX,color[M],ct,mi[M],cnt[M];
void dfs2(int x){
	color[x]=ct;//标明点的归属 
	vis[x]=1;
	sum=min(sum,a[x]);
	for(int i=hd2[x];i;i=e2[i].nxt){
		int go=e2[i].to;
		if(!vis[go])dfs2(go);
	}
}// 跑第二遍 
int main(){
	rd(n);
	for(int i=1;i<=n;i++)rd(a[i]);
	rd(m);
	for(int i=1;i<=m;i++){
		int x,y;rd(x),rd(y);
		addedge(x,y);
	}
	for(int i=1;i<=n;i++)if(!vis[i])dfs1(i);
	memset(vis,0,sizeof vis);
	int ans1=0,ans2=1;
	for(int i=n;i>=1;i--){
		if(!vis[d[i]]){
			ct++;
			sum=INT_MAX;//sum 用于查最小值 
			dfs2(d[i]);
			mi[ct]=sum; //记录块的最小值 
			ans1+=sum;
		}
	}
	cout<<ans1<<' ';
	for(int i=1;i<=n;i++)
		if(a[i]==mi[color[i]])cnt[color[i]]++; //统计最小值个数 
	for(int i=1;i<=ct;i++)ans2=ans2*cnt[i];
	cout<<ans2<<endl;
	return 0;
}
```


---

## 作者：WaterSun (赞：0)

# 思路

根据题面我们可知，对于每一个强连通分量只需要一个保安来管辖。

那么，我们可以对这个图进行缩点，然后，用一个数组 $val_i$ 来存储缩点后的，编号为 $i$ 这个连通分量中的原本点权的最小值。

我们最终的最小代价就是 $\sum_{i = 1}^{num}val_i$，其中 $num$ 为缩点后节点的数量。

然后，我们记录一下在每一个节点的点权在这个强连通分量中出现的次数 $cnt_{id_i}$（$id_i$ 表示节点 $i$ 缩完点后所处的联通分量的编号）。

然后，根据分步乘法计数原理，得方案数为 $\prod_{i = 1}^{num}cnt_i$。

注：$m$ 的数据范围有误，应为 $1 \leq m \leq 5 \times 10^4$

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 1e4 + 10,M = 5e4 + 10,inf = 1e9 + 10;
int n,m,idx,tim,num,ans_1,ans_2 = 1;
int h[N],ne[M],e[M],arr[N],cnt[N];
int dfn[N],low[N],id[N],val[N];
bool vis[N];
stack<int> s;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline void add(int a,int b){
	ne[idx] = h[a];
	e[idx] = b;
	h[a] = idx++;
}

inline void tarjan(int u){
	dfn[u] = low[u] = ++tim;
	vis[u] = true;
	s.push(u);
	for (re int i = h[u];~i;i = ne[i]){
		int j = e[i];
		if (!dfn[j]){
			tarjan(j);
			low[u] = min(low[u],low[j]);
		}
		else if (vis[j]) low[u] = min(low[u],dfn[j]);
	}
	if (dfn[u] == low[u]){
		int x;
		num++;
		do{
			x = s.top();
			s.pop();
			vis[x] = false;
			id[x] = num;
			val[num] = min(val[num],arr[x]);
		}while (x != u);
	}
}

signed main(){
	memset(h,-1,sizeof(h));
	n = read();
	for (re int i = 1;i <= n;i++){
		arr[i] = read();
		val[i] = inf;
	}
	m = read();
	for (re int i = 1;i <= m;i++){
		int a,b;
		a = read();
		b = read();
		add(a,b);
	}
	for (re int i = 1;i <= n;i++){
		if (!dfn[i]) tarjan(i);//缩点 
	}
	for (re int i = 1;i <= num;i++) ans_1 += val[i];//分别得出两个结果 
	for (re int i = 1;i <= n;i++){
		if (arr[i] == val[id[i]]) cnt[id[i]]++;
	}
	for (re int i = 1;i <= num;i++) ans_2 *= cnt[i];
	printf("%lld %lld",ans_1,ans_2);
	return 0;
}
```

---

## 作者：Kalium (赞：0)

# P2811 Protect the school 题解

## 前言：

**M 的范围是 50000，不是 30000！！！**

## 题意：

给 n 个点，每个点有个点权，若每个点能够管该点所在的环，那么所选的这些点的点权最小为多少，在点权最小的情况下方案有多少。

## 思路：

明显的，由于有环，我们需要进行缩点。

缩点直接 tarjan 搞上去啊，不会的自行调到[模板](https://www.luogu.com.cn/problem/P3387)。

既然要保证所选的点点权最小，那么我们直接在统计强连通分量的时候顺带着统计下这个强连通分量里的最小点权即可。

那么要做到方案数的话，很明显，我们只需要算出每个强连通分量有几个最小点权，然后根据乘法原理，将其一个个相乘即为所求。

其实这个有点像[这题](https://www.luogu.com.cn/problem/P2194)。

## 代码：

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>

#define ll long long
#define inf 0x3f3f3f3f

const int N = 1e4 + 7;
const int M = 5e4 + 7;

using namespace std;

int n, m;

int a[N];

struct Edge {
	int to, next;
} edge[M]; 

int head[N], cnt;

int dfn[N], low[N];

int ti;

int stk[N], instk;

bool flag[N];

int num;

int k1[N], k2[N];

int ans1, ans2 = 1;

inline int read() {
	int n = 0, f = 1;
	char c = getchar();
	
	while (c < '0' || c > '9') {
		if (c == '-') f = -f;
		
		c = getchar();
	}
	
	while (c >= '0' && c <= '9') {
		n = (n << 3) + (n << 1) + (c ^ '0');
		c = getchar();
	}
	
	return n * f;
}

inline void addedge(int u, int v) {
	edge[++ cnt] = (Edge) {v, head[u]};
	head[u] = cnt;
}

inline int mina(int a, int b) {
	if (a < b)
		return a;
	return b;
}

void tarjan(int u) {
	dfn[u] = low[u] = ++ ti;
	stk[++ instk] = u;
	flag[u] = 1;
	
	for (int i = head[u]; ~i; i = edge[i].next) {
		int v = edge[i].to;
		
		if (! dfn[v]) {
			tarjan(v);
			low[u] = mina(low[v], low[u]);
		} else if (flag[v])
			low[u] = mina(dfn[v], low[u]);
	}
	
	if (dfn[u] == low[u]) {
		int cur;
		
		num ++;
		
		do {
			cur = stk[instk --];
			flag[cur] = 0;
			
			if (k1[num] == a[cur]) k2[num] ++;
			else {
				k2[num] = 1;
				
				if (k1[num] > a[cur])
					k1[num] = a[cur];
			}
		} while (cur != u);
	}
}

int main() {
	n = read();
	
	for (int i = 1; i <= n; i ++) {
		a[i] = read(); 
		
		k1[i] = inf, head[i] = -1;
	}
	
	m = read();
	
	for (int i = 1; i <= m; i ++) {
		int u, v;
		
		u = read(), v = read();
		
		addedge(u, v);
	}
	
	for (int i = 1; i <= n; i ++)
		if (! dfn[i]) tarjan(i);
	
	/*for (int i = 1; i <= n; i ++)
		cout << belong[i] << " ";*/
	
	for (int i = 1; i <= num; i ++) {
		ans1 += k1[i];
		ans2 *= k2[i];
	}
	
	printf("%d %d\n", ans1, ans2);
	
	return 0;
} 
```

$Atlantis.$

---

