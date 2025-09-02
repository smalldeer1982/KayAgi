# [COCI 2018/2019 #5] Transport

## 题目描述

 一个国家有 $n$ 个城市，每个城市中都有一个加油站，燃料储量为 $a_i$。  
有 $n-1$ 条路径，将这些城市连接成一个树形结构。  

一个货车能从城市 $u$ 到达城市 $v$ ，货车的燃料量必须不小于 $u,v$ 之间的距离。  
每当货车抵达一个城市，就可以补充不超过加油站储量的燃料。  

假设货车的油箱是无限大的，请你算出有多少个有序数对 $(u,v)$ 满足：  
一个油箱燃料量初始为 $0$ 的货车，可以从城市 $u$ 出发，抵达城市 $v$。

请注意，货车只能走简单路径，也就是说不能走回头路。

## 说明/提示

### 样例1解释：  
唯一可行的是 $(1,2)$，即只有 $1\rightarrow 2$ 是可行的。  

### 数据范围：  
对于 $20\%$ 的数据：  
$1\le n \le 5000$   
对于 $40\%$ 的数据：   
树是一条链    
对于 $100\%$ 的数据：   
$1\le n \le 10^5$      
$1\le u,v \le n$     
$1\le w,a_i \le 10^9$   

## 样例 #1

### 输入

```
2
3 1
1 2 2```

### 输出

```
1```

## 样例 #2

### 输入

```
5
3 1 2 4 5
1 2 3
3 2 2
4 2 6
5 4 3```

### 输出

```
5```

# 题解

## 作者：sprads (赞：24)

这是一篇点分治 + 双指针的题解。

### 计算路径

设点分治中，**当前**找到的**根**为 $rt$，$w_i$ 表示从 $rt$ 到 $i$ 的**点权和**，$d_i$ 则表示从 $rt$ 到 $i$ 的**边权和**。

分两种情况考虑合法性：

- 从 $i$ 走到 $rt$：显然需要对于任意在 $i$ 到 $rt$ 路径上的节点 $j$，满足 $w_i-w_j \ge d_i - d_j$。稍加变换得：$w_i-d_i-(w_j-d_j)\ge 0$。此时只需要维护、记录**最大的** $w_j-d_j$ 即可判断从 $i$ 到 $rt$ 的合法性。

- 从 $rt$ 走到 $i$：这种情况，路径的起点**不一定**是 $rt$，可以从其他子树中的一个节点 $k\rightarrow rt \rightarrow i$。设 $k\rightarrow rt$ 后还剩下的油量为 $x$（直接从 $rt$ 出发那么 $x$ 为 $0$），则 $rt\rightarrow i$ 路径上任意一点 $j$，需要满足 $x+w_{fa_j} \ge d_j$。依旧是稍加变换：$x+(w_{fa_j}-d_j) \ge 0$，维护、记录路径上**最小的** $w_{fa_j}-d_j$ 即可。

### 统计答案

遍历所有子树，把所有路径都记录下来。

从 $i$ 到 $rt$ 记录 $w_i-d_i$，表示到 $rt$ 后的剩余油量。

从 $rt$ 到 $i$ 记录 $w_{fa_j}-d_j$ 的最小值。

分别将两种情况按记录的权值排序，用 $rt\rightarrow i$ 匹配 $k\rightarrow i$（反过来也可以）。

此时对于所有 $w_k-d_k + w_{fa_j}-d_j \ge 0$ 的 $k$ 都可以，双指针扫描统计即可。

注意要将 $k$ 和 $i$ 在同一子树内的情况提前减去。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100005;
int rd(){
	int x = 0;char ch = getchar();
	while(ch < '0' || ch > '9')ch = getchar();
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x;
}
ll s1[N],s2[N],q1[N],q2[N],w[N],d[N],ans;
int tot,head[N],ver[2*N],edge[2*N],Next[2*N];
int n,a[N],rt,sum,s[N],Mas[N],vis[N],t1,t2,h1,h2;
void add(int x,int y,int z){
	tot++;
	ver[tot] = y;
	edge[tot] = z;
	Next[tot] = head[x];
	head[x] = tot;
}
void Grt(int fa,int x){
	s[x] = 1,Mas[x] = 0;
	for(int i = head[x];i;i = Next[i]){
		int y = ver[i];
		if(y == fa || vis[y])continue;
		Grt(x,y);
		s[x] += s[y];
		Mas[x] = max(Mas[x],s[y]);
	}
	Mas[x] = max(Mas[x],sum - s[x]);
	if(!rt || Mas[x] < Mas[rt])rt = x;
}
void dfs(int fa,int x,ll Max,ll Min){//Max 最大 w[j] - d[j]；Min 最小 w[fa[j]]-d[j]
	if(w[x] - d[x] >= Max)//合法才记录
		s1[++t1] = w[x] - d[x];//i到rt
	s2[++t2] = Min;//rt到i，目前不能确定是否合法，都记录
	for(int i = head[x];i;i = Next[i]){
		int y = ver[i],z = edge[i];
		if(y == fa || vis[y])continue;
		d[y] = d[x] + z,w[y] = w[x] + a[y];
		dfs(x,y,max(Max,w[x] - d[x]),min(Min,w[x] - d[y]));//注意更新 Max 和 Min
	}
}
void calc(int x){
	int L;
	h1 = 0,h2 = 0;
	d[x] = 0,w[x] = a[x];
	for(int i = head[x];i;i = Next[i]){
		int y = ver[i],z = edge[i];
		if(vis[y])continue;
		t1 = 0,t2 = 0;
		d[y] = z,w[y] = w[x] + a[y];//初始化d[y]和w[y]
		dfs(x,y,w[x] - d[x],w[x] - d[y]);
		sort(s1 + 1,s1 + 1 + t1);//s1、s2记录当前子树内的路径
		sort(s2 + 1,s2 + 1 + t2);
		L = 1;
		for(int i = t2;i >= 1;i--){//注意倒序枚举
			while(L <= t1 && s1[L] + s2[i] - a[x] < 0)L++;
			ans -= t1 - L + 1;//减去同一子树内的答案
		}
		for(int i = 1;i <= t1;i++)
			q1[++h1] = s1[i];
		for(int i = 1;i <= t2;i++)
			q2[++h2] = s2[i];//q1和q2记录所有路径
	}
	sort(q1 + 1,q1 + 1 + h1);
	sort(q2 + 1,q2 + 1 + h2);
	L = 1;
	for(int i = h2;i >= 1;i--){
		if(q2[i] >= 0)//rt到i直接从rt出发
			ans++;
		while(L <= h1 && q1[L] + q2[i] - a[x] < 0)L++;//i到rt，rt到i都加了a[x]，减掉一次
		ans += h1 - L + 1;
	}
	ans += h1;//i出发到rt结束的情况
}
void solve(int x){
	vis[x] = 1,calc(x);
	for(int i = head[x];i;i = Next[i]){
		int y = ver[i],z = edge[i];
		if(vis[y])continue;
		rt = 0,sum = s[y];
		Grt(x,y),solve(rt);
	}
}
int main(){
	n = rd();
	for(int i = 1;i <= n;i++)
		a[i] = rd();
	for(int i = 1;i < n;i++){
		int x = rd(),y = rd(),z = rd();
		add(x,y,z);
		add(y,x,z);
	}
	rt = 0,sum = n;
	Grt(0,1),solve(rt);
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：wawa123 (赞：9)

# 点分治

~~又叫淀粉质。~~

常用于处理树上路径相关问题，可以在 $O(nlog_2(n))$ 左右的时间复杂度内高效处理问题。

# 基本思想

1. 找到当前子树的一个重心 $u$。

2. 将路径分为经过重心和不经过重心的两种。

3. 经过重心：将重心作为根，枚举儿子，用数据结构记录每个节点到重心的路径信息（可以直接记录，也可以分类成 $i$ 到 $u$ 和 $u$ 到 $i$ 的路径），儿子的路径之间合并信息处理问题。

4. 不经过重心：递归处理重心的儿子的子树。

没错，就这么简单，接下来说例题和几个坑点。

# P4149 [IOI2011] Race

显然的模版题，将路径长度和其对应的边数记录下来，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5,K=1e6+5;
struct node{ll v,w;};
ll genshin=1e13,n,k;vector<node>g[N];
bool vis[N];
ll len[K];//记录对应路径长度的最小边数，如果没有就是INF
vector<node>p;
ll sz[N],mx[N],S,rt;
void find_rt(ll u,ll f){
	sz[u]=1;mx[u]=0;
	for(int i=0;i<g[u].size();i++){
		if(vis[g[u][i].v]||f==g[u][i].v)continue;
		find_rt(g[u][i].v,u);sz[u]+=sz[g[u][i].v];
		mx[u]=max(mx[u],sz[g[u][i].v]);
	}
	mx[u]=max(mx[u],S-sz[u]);
	if(mx[u]<mx[rt]){rt=u;}
}
void find_dis(ll u,ll f,ll dis,ll dep){
	if(dis>k)return;
	p.push_back({dis,dep});
	for(int i=0;i<g[u].size();i++){
		ll v=g[u][i].v,w=g[u][i].w;
		if(vis[v]||f==v)continue;
		find_dis(v,u,dis+w,dep+1);
	}
}
queue<ll>q;
void cal(ll u){
	len[0]=0;
	while(!q.empty())q.pop();
	for(int i=0;i<g[u].size();i++){
		ll v=g[u][i].v,w=g[u][i].w;
		if(vis[v])continue;p.clear();
		find_dis(v,u,w,1);
		for(int j=0;j<p.size();j++){
			ll t1=p[j].v,t2=p[j].w;
			genshin=min(genshin,t2+len[k-t1]);//统计答案
		}
		for(int j=0;j<p.size();j++){
			ll t1=p[j].v,t2=p[j].w;
			q.push(t1);len[t1]=min(len[t1],t2);//加入
		}
	}
	while(!q.empty()){//注意memset不一定能保证时间复杂度
		len[q.front()]=1e9;q.pop();
	}
}
void divide(ll u){
	vis[u]=1;
	cal(u);
	for(int i=0;i<g[u].size();i++){
		ll v=g[u][i].v,w=g[u][i].w;
		if(vis[v])continue;
		S=sz[v];rt=0;mx[0]=1e9;
		find_rt(v,u);
		divide(rt);
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<n;i++){
		ll u,v,w;cin>>u>>v>>w;u++,v++;
		g[u].push_back({v,w});g[v].push_back({u,w});
	}
	rt=0;mx[0]=1e9;S=n;find_rt(1,0);
	memset(len,0x3f,sizeof(len));
	divide(rt);
	if(genshin>=n)cout<<-1;//如果答案一直没有更新，只能说明无解
	else cout<<genshin;
	return 0;
}
```
坑点：
1. 注意范围 $n$ 和 $k$ 分清楚。

2. 注意不要写成 $\operatorname{divide(v)}$。

3. 注意最开始 $\operatorname{main}$ 函数里面也要先算重心再分治。

4. 注意 $len_0$ 也是一个可行的方案。

# P5306 [COCI2018-2019#5] Transport

比较难，假设重心（根）为 $rt$，先将路径 $(a,b)$ 分为两段，一段是上行路径 $(a,rt)$，一段是下行路径 $(rt,b)$。

先以$rt$为根，求出油量和路程的树上前缀和 $fuel[u]$ 和 $d[u]$。

我们发现，对于一个上行路径 $(a,rt)$，如果他是合法的，那么对于 $(a,rt)$ 上的任意一点 $v$，他都必须满足 $fuel[a]-fuel[v]\geq d[a]-d[v]$，也就是 $fuel[a]-d[a]\geq fuel[v]-d[v]$。因此我们只需要在 $\operatorname{find\underline{~}dis}$ 的过程中记录一个 $maxn$ 表示路径上遇到的 $fuel[v]-d[v]$ 的最大值，用这个判断当前点 $a$ 有没有可能成为一个上行路径的起点，如果可能，将可能的点 $a$ 的 $fuel[a]-d[a]$ 计入数组，代码中为 $s1$。

接着，我们又发现，对于一个下行路径 $(rt,b)$，如果他是合法的，那么对于 $(rt,b)$ 上的任意一点 $v$，都必须满足 $x+fuel[fa[v]]\geq d[v]$，也就是 $x+fuel[fa[v]]-d[v]\geq 0$，其中 $x$ 是上行路径的剩余油量，这个不好判断，我们可以全都先记着，待会判断，对于每一个点 $b$，记录的数据就是 $(rt,b)$ 路径上任意点 $v$ 的 $fuel[fa[v]]-d[v]$ 的最小值，将此最小值记为 $s2$。

最后，我们考虑如何合并答案，我们发现，只要 $s1+s2-a[rt]\geq0$ 就符合要求（当然 $s1$ 和 $s2$ 必须来源于不同子树，而减去 $a[rt]$ 则是因为 $s1$ 和 $s2$ 都统计了一遍 $a[rt]$）

如何实现这个呢？

可以容斥，先提前让答案减去符合 $s1+s2-a[rt]\geq0$ 要求的（其中 $s1$ 和 $s2$  **来源于同一子树**）

然后用双指针统计符合 $s1+s2-a[rt]\geq0$ 要求的（这里的 $s1$ 和 $s2$ 既可以是同一子树，也可以不同，但是因为前面的容斥，剩下的只会是不同子树的）

代码如下（统计答案部分的代码借鉴了 $\text{sprads}$ 的题解）
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
ll n,a[N],fuel[N],d[N];
struct node{ll v,w;};
vector<node>g[N];bool vis[N];
ll sz[N],rt,S,mx[N];//求重心
ll s1[N],s2[N],cnt1,cnt2;//单个儿子
ll q1[N],q2[N],tot1,tot2;//所有儿子
ll genshin=0;//统计答案
void find_rt(ll u,ll f){
	sz[u]=1;mx[u]=0;
	for(int i=0;i<g[u].size();i++){
		ll v=g[u][i].v;
		if(v==f||vis[v])continue;
		find_rt(v,u);sz[u]+=sz[v];
		mx[u]=max(mx[u],sz[v]);
	}
	mx[u]=max(mx[u],S-sz[u]);
	if(mx[u]<mx[rt])rt=u;
}
void find_dis(ll u,ll f,ll maxn,ll minn){
	if(fuel[u]-d[u]>=maxn){s1[++cnt1]=fuel[u]-d[u];}maxn=max(maxn,fuel[u]-d[u]);
	s2[++cnt2]=minn;
	for(int i=0;i<g[u].size();i++){
		ll v=g[u][i].v,w=g[u][i].w;
		if(v==f||vis[v])continue;
		fuel[v]=fuel[u]+a[v],d[v]=d[u]+w;
		find_dis(v,u,maxn,min(minn,fuel[u]-d[v]));
	}
}

void cal(ll u){
	tot1=tot2=0;fuel[u]=a[u];d[u]=0;
	for(int i=0;i<g[u].size();i++){
		ll v=g[u][i].v,w=g[u][i].w;cnt1=cnt2=0;
		if(vis[v])continue;
		fuel[v]=fuel[u]+a[v];d[v]=d[u]+w;
		find_dis(v,u,fuel[u]-d[u],fuel[u]-d[v]);
		sort(s1+1,s1+cnt1+1);sort(s2+1,s2+cnt2+1);
		for(int j=cnt2,k=1;j>=1;j--){//双指针减去同一子树
			while(k<=cnt1&&s1[k]+s2[j]-fuel[u]<0)k++;
			genshin-=cnt1-k+1;
		}
		for(int i=1;i<=cnt1;i++)q1[++tot1]=s1[i];
		for(int i=1;i<=cnt2;i++)q2[++tot2]=s2[i];
	}
	sort(q1+1,q1+tot1+1);sort(q2+1,q2+tot2+1);
	for(int j=tot2,k=1;j>=1;j--){//双指针统计答案
		if(q2[j]>=0){genshin++;}//注意自己也能做贡献，相当于是(rt,b)
		while(k<=tot1&&q1[k]+q2[j]-fuel[u]<0)k++;
		genshin+=tot1-k+1;
	}
	genshin+=tot1;//(a,rt)的上行路径
}
void divide(ll u){
	vis[u]=1;cal(u);
	for(int i=0;i<g[u].size();i++){
		ll v=g[u][i].v,w=g[u][i].w;
		if(vis[v])continue;
		S=sz[v];rt=0;mx[0]=1e9;
		find_rt(v,u);divide(rt);
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){cin>>a[i];}
	for(int i=1;i<n;i++){
		ll u,v,w;cin>>u>>v>>w;
		g[u].push_back({v,w});g[v].push_back({u,w});
	}
	S=n;rt=0;mx[0]=1e9;
	find_rt(1,0);
	divide(rt);
	cout<<genshin;
	return 0;
}
```

坑点：注意 $s1$ 和 $s2$ 自己也可以独立做贡献（就是 $(a,rt)$ 和 $(rt,b)$ 本身也是合法路径）

~~另外，用genshin当变量名统计答案真的超酷的好嘛~~
# 题外话

点分治功能非常强大，~~甚至可以瞎搞~~

比如说我的另一篇未发布的题解（因为太奇怪了，没发）

[点分治过树形dp](https://www.luogu.com.cn/blog/379261/p3047-usaco12feb-nearby-cows-g-ti-xie)

（不过这是纯粹瞎搞，正常学算法的灵长类可以忽略）

---

## 作者：Guitar_Jasmine (赞：8)

## 闲聊

看到树上路径问题点分治肯定可以做

看了一下其他题解好像没有具体介绍如何不重不漏地计数以及一些细节（~~其实是我太菜了没看懂~~

蒟蒻我做点分题还没有用过容斥定理，一般都是在每颗子树里跑一遍的时候直接累加前面已经跑过的贡献QWQ

## 前置芝士
- 点分治
- 平衡树（其实可以不用，~~但因为我不太会容斥~~，而且这题边权比较大树状数组维护不了

## 大体思路
（后面会详细介绍如何累计答案
- ~~首先点分治~~
- 考虑对分治中心的每一颗子树跑两遍，（鉴于方便，先说第二遍的作用）第二遍算从每个点能否到分治中心，如果能到的话到了以后还剩多少油并插进Treap里，第一遍跑的时候直接合并分治中心到当前子树点的路径和 与 之前Treap里的计算一下就OK了(具体怎么维护我觉得楼上写的特别清楚就不赘述了)
- Upd 7.20： 算了还是讲一讲这个具体怎么往Treap里插吧（顺便修一下错别字）。首先第一遍DFS，这个点到分治中心的任意过程中都不能出现油量为负数的情况；第二遍DFS，分治中心到这个点的过程中出现的最小油量 加上 Treap里目前的最大油量应该大于等于0
- 至于两遍DFS的顺序问题应该很显然（就是因为这样所以不用容斥了
- 那么这样算下来，你会发现答案少了很多，因为我们枚举到终点的路径（也就是分治中心到某个节点的路径）时只有前面跑过的子树会对它产生贡献，但是目前没跑过的子树也会对它产生贡献
- 解决方法是每次分治的时候记一下分治中心即将访问的每棵子树，先正着跑一遍，再倒着跑一遍就可以把答案全累加了

## 如何累加答案（重点来啦）
- 上文说到一共要跑两遍，这就会引发一些奇奇怪怪的问题，比如分治中心与子树节点形成的点对会被加两次，下面就来说一说我的处理方法
- 计算点对（分治中心，子树节点）的贡献：注意到累加以根为起点产生的贡献其实就是把根(分治中心)拥有的汽油量插进Treap里，这样我们在正着跑的时候不管他，倒着跑之前$Insert（point[分治中心]）$就可以了
- 计算点对（子树节点，分支中心）的贡献：我的处理方法是用一个变量ans_1来临时记下贡献,累加给答案的时候除以2就好啦
- 至于其他起点和终点都不是分治中心的点对,我们的做法能很好的应对

#### 这题的细节其实还是非常多的,有不懂的地方可以私我QWQ

上代码
```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=100009;
typedef long long LL;
int n,point[N],head[N],cnt,siz[N],del[N],l[N],tmp,pool,root,w[N],tot;
LL ans,all[N],ans_1;
struct Edge
{
	int nxt,to,w;
}g[2*N];
struct Tree
{
	int pri,l,r,cnt,siz;
	LL val;
	#define p(x) a[x].pri
	#define v(x) a[x].val
	#define l(x) a[x].l
	#define r(x) a[x].r
	#define c(x) a[x].cnt
	#define s(x) a[x].siz
}a[N*10];

void Zig(int &k)
{
	int x=l(k);
	l(k)=r(x);
	r(x)=k;
	s(x)=s(k);
	s(k)=s(l(k))+s(r(k))+c(k);
	k=x;
}

void Zag(int &k)
{
	int x=r(k);
	r(k)=l(x);
	l(x)=k;
	s(x)=s(k);
	s(k)=s(l(k))+s(r(k))+c(k);
	k=x;
}

void Insert(int &k,LL x)
{
	if(!k)
	{
		k=++pool,v(k)=x,c(k)=s(k)=1,p(k)=rand();
		return;
	}
	s(k)++;
	if(x==v(k))
		c(k)++;
	else if(x<v(k))
	{
		Insert(l(k),x);
		if(p(l(k))<p(k))
			Zig(k);
	}
	else
	{
		Insert(r(k),x);
		if(p(r(k))<p(k))
			Zag(k);
	}
}

void Delete(int &k,LL x)
{
	if(v(k)==x)
	{
		if(c(k)>1)
			c(k)--,s(k)--;
		else if(!l(k)||!r(k))
			k=l(k)+r(k);
		else if(p(l(k))<p(r(k)))
			Zig(k),Delete(k,x);
		else
			Zag(k),Delete(k,x);
		return;
	}
	s(k)--;
	if(x<v(k))
		Delete(l(k),x);
	else
		Delete(r(k),x);
}

int Query(LL x)//计算当前Treap里>=x的数有多少个
{
	int k=root,ans=0;
	while(k)
	{
		if(x<v(k))
			ans+=c(k)+s(r(k)),k=l(k);
		else if(x>v(k))
			k=r(k);
		else
			return ans+c(k)+s(r(k));
	}
	return ans;
}

void add(int from,int to,int w)
{
	g[++cnt].nxt=head[from];
	g[cnt].to=to;
	g[cnt].w=w;
	head[from]=cnt;
}

void init()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&point[i]);
	int x,y,z;
	for (int i=1;i<n;i++)
	{
		scanf("%d %d %d",&x,&y,&z);
		add(x,y,z),add(y,x,z);
	}
}

void dfs(int x,int fa)//计算子树大小
{
	siz[x]=1;
	for (int i=head[x];i;i=g[i].nxt)
	{
		int v=g[i].to;
		if(v==fa||del[v])
			continue;
		dfs(v,x);
		siz[x]+=siz[v];
	}
}

int Get_Weight(int x)//找重心
{
	dfs(x,-1);
	int k=siz[x]/2,fa=-1;
	while(1)
	{
		int tmp=0;
		for (int i=head[x];i;i=g[i].nxt)
		{
			int v=g[i].to;
			if(del[v]||v==fa)
				continue;
			if(siz[v]>siz[tmp])
				tmp=v;
		}
		if(siz[tmp]<=k)
			return x;
		fa=x,x=tmp;
	}
}

void DFS(int x,int fa,LL Max,LL now)//第一遍DFS
{
	ans+=Query(Max);
	for (int i=head[x];i;i=g[i].nxt)
	{
		int v=g[i].to;
		if(v==fa||del[v])
			continue;
		DFS(v,x,max(Max,now-point[x]+g[i].w),now-point[x]+g[i].w);
	}
}

void DFS_1(int x,int fa,LL Max,LL now)//第二遍DFS
{
	if(now>=Max)
		Insert(root,now),all[++tot]=now,ans_1++;
	for (int i=head[x];i;i=g[i].nxt)
	{
		int v=g[i].to;
		if(v==fa||del[v])
			continue;
		DFS_1(v,x,max(now,Max),now+point[v]-g[i].w);
	}
}

void Get_Ans(int x)
{
	tmp=tot=ans_1=0;
	for (int i=head[x];i;i=g[i].nxt)
	{
		int v=g[i].to;
		if(del[v])
			continue;
		l[++tmp]=v,w[tmp]=g[i].w;
	}
    //正着跑一遍
	for (int i=1;i<=tmp;i++)
	{
		DFS(l[i],x,w[i],w[i]);
		DFS_1(l[i],x,point[x],point[x]+point[l[i]]-w[i]);
	}
	while(tot)
		Delete(root,all[tot--]);//清空防止对以后产生影响
    //倒着跑一遍
	Insert(root,point[x]);//分治中心的油量第二遍再加进来
	for (int i=tmp;i>=1;i--)
	{
		DFS(l[i],x,w[i],w[i]);
		DFS_1(l[i],x,point[x],point[x]+point[l[i]]-w[i]);
	}
	while(tot)
		Delete(root,all[tot--]);
	Delete(root,point[x]);
	ans+=ans_1/2;//点对（子树节点，分治中心）的贡献最后要除以二
}

void conquer(int x)
{
	int w=Get_Weight(x);
	Get_Ans(w);
	del[w]=1;
	for (int i=head[w];i;i=g[i].nxt)
	{
		int v=g[i].to;
		if(del[v])
			continue;
		conquer(v);
	}
}

void work()
{
	Insert(root,-(1LL<<60)),conquer(1);//加入负无穷大是为了怕Query出锅
	printf("%lld\n",ans);
}

int main()
{
	init();
	work();
	return 0;
}
```


---

## 作者：glorious_dream (赞：6)

## 题目大意：

在一棵树中，找出满足条件的点对 $i$，$j$ 数量，使从 $i$ 能走到 $j$，其中任意时刻，满足点权之和 $\geq$ 边权之和。

## 算法分析：

看题目的描述，很明显是一道点分治的题目。关键在于如何去维护答案。

这道题是我们的模拟赛题，考场上打了一个假到不能再假的点分治，一分没有。

先来模拟一下点分治的过程：首先找到 $root$，对于根为 $root$ 的这棵树进行操作，最后把 $root$ 删掉。

那么这道题，很自然的难点，就是如何对这棵树进行操作，我们一步一步看。

首先，$i$和 $j$ 要在 $root$ 的两棵不同的子树中，最后统计答案的时候，把 $i$ 和 $j$ 在一棵子树的情况给删掉就行。

关键操作：把 $i$ 到 $j$ 的路径，分为 $i$ 到 $root$ 和 $root$ 到 $j$。我们用两个数组 $w_i$，$d_i$ 分别记录这条路径的点权之和，和边权之和。

第一步，从 $i$ 到 $root$ ：对于满足条件的节点 $k$，需要 $w[i]-w[k] \geq d[i]-d[k]$，把这个式子移项，可以得到 $(w[i]-d[i])-(w[k]-d[k]) \geq 0$。所以我们记录最大的 $w[k]-d[k]$ 就可以判断 $i$ 到 $root$ 是否合法。 

第二步，从 $root$ 到 $j$：这种情况，该路径的起点不一定是 $root$，可以从另一个子树的 $u$ 为起点。设以 $u$ 为起点到 $root$，剩余的油量是 $x$，则路径上的任意一点 $k$，需要满足 $x+w[fa[k]] \geq d[k]$，$fa[k]$ 表示 $k$ 的父亲。变换一下，式子就变成 $x+(w[fa[k]]-d[k]) \geq 0$。这时我们维护路径上 $w[fa[k]]-d[k]$ 的最小值即可。

如何统计答案：

先遍历所有子树，从 $i$ 到 $root$ 记录 $w[i]-d[i]$ 表示从 $i$ 到 $root$ 的剩余油量。

从 $root$ 到 $j$ 记录 $w[fa[j]]-d[j]$ 的最小值。

将两种情况按升序排序，用双指针来维护答案的区间。

答案区间为 $w[k]-d[k]+w[f[a[j]]-d[j]$ 的 $k$ 都可以。

注意，像上面所说，要先把 $i$ 和 $k$ 在同一棵子树中的情况提前删掉。

## 总代码：

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#define re register
#define int long long
#define drep(a,b,c) for(re int a(b) ; a>=(c) ; --a)
#define rep(a,b,c) 	for(re int a(b) ; a<=(c) ; ++a)
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int M = 2e5+10;
int n;
int head[M],siz[M],maxp[M],vis[M],a[M];
int w[M],d[M],tmp1[M],tmp2[M],q1[M],q2[M];
int root,sum,ans,cnt,cnt1,cnt2; 
struct edge{
	int to,nxt,w;
}e[M];
inline void add(int u,int v,int w){ //村边 
	e[++cnt].to = v;
	e[cnt].w = w;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}
inline void getroot(int u,int fa){
	siz[u] = 1;maxp[u] = 0; //maxp记录该节点的最大的子树的size 
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to;
		if(vis[v] || v==fa) continue;
		getroot(v,u);
		siz[u] += siz[v];
		maxp[u] = max(maxp[u],siz[v]); //找最大 
	}
	maxp[u] = max(maxp[u],sum-siz[u]); //注意，该节点外部也可能有点，要考虑到 
	if(maxp[u] < maxp[root]) root = u; //更新重心 
}
inline void dfs(int u,int fa,int mx,int mi){
	if(w[u] - d[u] >= mx) tmp1[++cnt1] = w[u]-d[u]; //把符合要求的记录下来 
	tmp2[++cnt2] = mi; //因为不确定从root到j的路径是从哪一个点开始，所以也都要记录下来 
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to;
		if(v==fa || vis[v]) continue;
		d[v] = d[u]+e[i].w; //更新边权之和 
		w[v] = w[u]+a[v];	//更新点权之和 
		dfs(v,u,max(mx,w[u]-d[u]),min(mi,w[u]-d[v])); //往下接着更新 
	}
}
inline void solve(int u){
	int tot1=0,tot2=0;
	d[u] = 0,w[u] = a[u]; //初始化 
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to;
		if(vis[v]) continue;
		cnt1 = cnt2 = 0;
		d[v] = e[i].w,w[v] = w[u]+a[v]; //初始化两个数组 
		dfs(v,u,w[u]-d[u],w[u]-d[v]); //进行dfs，找tmp1和tmp2来更新答案 
		sort(tmp1+1,tmp1+cnt1+1); //升序 
		sort(tmp2+1,tmp2+cnt2+1); //tmp1和tmp2记录的是当前子树内的路径 
		int l = 1;
		for(re int i(cnt2) ; i>=1 ; --i){ //注意是反着枚举，相当于双指针维护 
			while(l<=cnt1 && tmp1[l]+tmp2[i]-a[u]<0) l++; //如果改路径不符合要求 
			ans -= cnt1-l+1; //把在同一棵子树内的贡献给删掉 
		}	
		for(re int i(1) ; i<=cnt1 ; ++i) q1[++tot1] = tmp1[i];
		for(re int i(1) ; i<=cnt2 ; ++i) q2[++tot2] = tmp2[i]; //q1和q2记录的是所有的路径 
	}
	sort(q1+1,q1+tot1+1); //同样升序排序 
	sort(q2+1,q2+tot2+1);
	int l = 1;
	for(re int i(tot2) ; i>=1 ; --i){ //双指针找答案 
		if(q2[i] >= 0) ans++; //相当于可以直接从root出发到j，那么直接+1即可 
		while(l<=tot1 && q1[l]+q2[i]-a[u]<0) l++; //从i到root和从root到j加了两次a[root]，减去就行 
		ans += tot1-l+1; //更新答案 
	}
	ans += tot1; //这是加上从i出发直接到root结束的情况 
}
inline void work(int u){
	vis[u] = 1; //相当于把这个点删了 
	solve(u); //从这个点开始 
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to;
		if(vis[v]) continue;
		maxp[root = 0] = sum = siz[v]; //重新找重心 
		getroot(v,0);
		getroot(root,0); //注意还是两次 
		work(root); //重复该过程 
	}
}
signed main(){
	n=read();
	rep(i,1,n) a[i] = read();
	rep(i,1,n-1){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	maxp[0] = sum = n; //注意要先赋值 
	getroot(1,0);
	getroot(root,0); //可以算是一个细节吧，因为如果只找一次根，
					 //那么记录的siz数组很有可能不是以root为根的size 
	work(root); //从root开始点分治 
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Great_Influence (赞：6)

点分治。

关于树上路径统计问题首先就会想到点分治或者边分治。边分太麻烦了，我们采用点分治。

我们考虑计算出当前点分树内的所有点能否到分治中心，以及到了中心后还剩下多少油，然后再算出从分治中心到所有点的路径前缀最小值，然后就可以排序后直接用双指针扫描即可。

记得容斥掉同一颗子树内的答案。

时间复杂度为 $O(n\log^2 n)$ 。

代码：
```cpp
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cassert>
#include<queue>
#include<iostream>
#include<climits>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define rep(i,a,b) for(register int i=(a);i<(b);++i)
#define pb push_back
#define mp make_pair
#define mx(a,b) (a>b?a:b)
#define mn(a,b) (a<b?a:b)
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef long long ll;
using namespace std;

namespace IO
{
	const uint32 Buffsize=1<<15,Output=1<<24;
	static char Ch[Buffsize],*S=Ch,*T=Ch;
	inline char getc()
	{
		return((S==T)&&(T=(S=Ch)+fread(Ch,1,Buffsize,stdin),S==T)?0:*S++);
	}
	static char Out[Output],*nowps=Out;
	
	inline void flush(){fwrite(Out,1,nowps-Out,stdout);nowps=Out;}

	template<typename T>inline void read(T&x)
	{
		x=0;static char ch;T f=1;
		for(ch=getc();!isdigit(ch);ch=getc())if(ch=='-')f=-1;
		for(;isdigit(ch);ch=getc())x=x*10+(ch^48);
		x*=f;
	}

	template<typename T>inline void write(T x,char ch='\n')
	{
		if(!x)*nowps++='0';
		if(x<0)*nowps++='-',x=-x;
		static uint32 sta[111],tp;
		for(tp=0;x;x/=10)sta[++tp]=x%10;
		for(;tp;*nowps++=sta[tp--]^48);
		*nowps++=ch;
		if(nowps-Out>=1<<23)flush();
	}
}
using namespace IO;

void file()
{
#ifndef ONLINE_JUDGE
	FILE*DSD=freopen("water.in","r",stdin);
	FILE*CSC=freopen("water.out","w",stdout);
#endif
}

const int MAXN=1e5+7,MAXM=5e5+7;

inline void Chkmin(int&u,int v){u>v?u=v:0;}

inline void Chkmax(int&u,int v){u<v?u=v:0;}

inline void Chkmax(ll&u,ll v){u<v?u=v:0;}

inline void Chkmin(ll&u,ll v){u>v?u=v:0;}

static int n,a[MAXN];

static struct edge{int v,w,nxt;}p[MAXN<<1];

static int head[MAXN],e;

inline void add(int u,int v,int w){p[++e]=(edge){v,w,head[u]},head[u]=e;}

inline void init()
{
	read(n);
	Rep(i,1,n)read(a[i]);
	static int u,v,w;
	Rep(i,1,n-1)read(u),read(v),read(w),add(u,v,w),add(v,u,w);
}

static int sz[MAXN],F[MAXN],rt,al,vis[MAXN];

void getrt(int u,int fr)
{
	sz[u]=1,F[u]=0;
	for(int i=head[u];i;i=p[i].nxt)
	{
		int v=p[i].v;
		if(v^fr&&!vis[v])getrt(v,u),sz[u]+=sz[v],Chkmax(F[u],sz[v]);
	}
	Chkmax(F[u],al-sz[u]);
	if(F[u]<F[rt])rt=u;
}

static ll ans;

static ll wa[MAXN],wb[MAXN];

static int tp1,tp2;

void getnd(int u,int fr,ll sm,ll mntl,ll mnhd,int st)
{
	if(mntl==0)wa[++tp1]=sm;
	wb[++tp2]=-mnhd;
	for(int i=head[u];i;i=p[i].nxt)
	{
		int v=p[i].v;
		if(v^fr&&!vis[v])
			getnd(v,u,sm-p[i].w+a[v],min(0ll,mntl-p[i].w+a[v])
			,min(mnhd,sm-a[st]-p[i].w),st);
	}
}

void getans(int u)
{
	vis[u]=1;
	tp2=0;
	wa[tp1=1]=a[u];
	for(int i=head[u];i;i=p[i].nxt)
	{
		int v=p[i].v;
		if(!vis[v])
		{
			if(sz[v]>sz[u])sz[v]=al-sz[u];
			int cr1=tp1+1,cr2=tp2+1;
			getnd(v,u,a[u]+a[v]-p[i].w,min(0,a[v]-p[i].w),min(0,-p[i].w),u);
			if(tp1>=cr1&&tp2>=cr2)
			{
				sort(wa+cr1,wa+tp1+1),sort(wb+cr2,wb+tp2+1);
				int r=cr2;
				Rep(l,cr1,tp1)
				{
					while(r<=tp2&&wa[l]>=wb[r])++r;
					ans-=r-cr2;
				}
			}
		}
	}
	sort(wa+1,wa+tp1+1),sort(wb+1,wb+tp2+1);
	int r=1;
	Rep(l,1,tp1)
	{
		while(r<=tp2&&wa[l]>=wb[r])++r;
		ans+=r-1;
	}
	ans+=tp1-1;
	for(int i=head[u];i;i=p[i].nxt)
	{
		int v=p[i].v;
		if(!vis[v])al=F[rt=0]=sz[v],getrt(v,u),getans(rt);
	}
}

inline void solve()
{
	al=F[0]=n,getrt(1,0),getans(rt);
	cout<<ans<<endl;
}

int main()
{
	file();
	init();
	solve();
	flush();
	return 0;
}
```

---

## 作者：_ctz (赞：4)

[安利blog](https://ctz45562.github.io/2019/09/21/%E6%B4%9B%E8%B0%B7-P5306-COCI2019-Transport/)

[传送门](https://www.luogu.org/problem/P5306)

下记$root$为分治中心，$dis_i$为$i$到$root$的距离，$sum_i$为$i$到$root$路径的点权和（不包括$root$的点权）。

对于每次分治，先把当前树内点作为起点判断是否能到根，并用平衡树存一下到达根后剩余油量。

使点$i$能到达根，就要满足$\forall j$位于路径$i\rightarrow root$，$sum_i-dis_i-sum_j+dis_j\ge 0$。

$dfs$时维护最小的$dis_j-sum_j$判断即可。

再$dfs$一遍树，以每个点作为终点，判断是否存在一条路径和自己拼起来合法。

同理，维护一个最大的$dis_j-sum_{fa_j}$即可，注意是$fa_j$的$sum$。平衡树里查一下大于等于该值减去$a_{root}$的数作为贡献。减去$a_{root}$是因为这两次统计时都没有算上$root$的点权。还要减去同一子树的点的贡献。

复杂度是$O(n\log^2 n)$的。

一开始想把剩余油量存数组里排个序`build`一棵平衡树。甚至可以把序列去重，不涉及插入删除直接搞一个$BST$出来。

`build`是$O(n)$的，于是总复杂度就成$O(n\log n)$了，然后发现排序还是带个$\log$.

然而我已经写出来了所以代码如此冗长丑陋$QAQ$：

``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

#define maxn 100005
#define inf 0x3f3f3f3f

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
#define ls(x) ls[x]
#define rs(x) rs[x]
struct edge{
	int pre,to,l;
}e[maxn<<1];
int a[maxn],h[maxn],siz[maxn],s[maxn],ls[maxn],rs[maxn],c[maxn],cn[maxn],cnt,num,mx,root,all,len,rt;
bool vis[maxn];
long long ans,base[maxn],b[maxn],dat[maxn];
void build(int l,int r,int &node){
	if(l>r){node=0;return;}
	node=++cnt;
	int mid=l+r>>1;
	build(l,mid-1,ls(node));
	build(mid+1,r,rs(node));
	dat[node]=b[mid],c[node]=cn[mid];
	s[node]=s[ls(node)]+s[rs(node)]+c[node];
}
void clear(int node){
	if(!node)return;
	clear(ls(node)),clear(rs(node));
	ls(node)=rs(node)=0;
}
void change(long long x,int d){
	int node=rt;
	while(node){
		s[node]+=d;
		if(dat[node]==x){c[node]+=d;return;}
		if(dat[node]<x)node=rs(node);
		else node=ls(node);
	}
}
int ask(long long d){
	int node=rt,ans=0;
	while(node){
		if(dat[node]>=d)ans+=s[rs(node)]+c[node],node=ls(node);
		else node=rs(node);
	}
	return ans;
}
inline void add(int from,int to,int l){
	e[++num]=(edge){h[from],to,l};
	h[from]=num;
}
void getroot(int node,int f=0){
	int x,ma=all-siz[node];
	for(register int i=h[node];i;i=e[i].pre){
		x=e[i].to;
		if(x==f||vis[x])continue;
		getroot(x,node),ma=max(ma,siz[x]);
	}
	if(ma<mx)mx=ma,root=node;
}
void Count(int node,long long sum,long long dis,long long mi,int f=0){
	sum+=a[node];
	mi=min(mi,dis-sum);
	for(register int i=h[node],x;i;i=e[i].pre){
		x=e[i].to;
		if(vis[x]||x==f)continue;
		Count(x,sum,dis+e[i].l,mi,node);
		if(a[x]>=e[i].l&&sum+a[x]-dis-e[i].l+mi>=0)base[++len]=a[x]+sum-dis-e[i].l;
	}
}
void work(int node,int opt,long long sum,long long dis,long long mi,int f=0){
	sum+=a[node];	
	mi=min(mi,dis-sum);
	for(register int i=h[node],x;i;i=e[i].pre){
		x=e[i].to;
		if(vis[x]||x==f)continue;
		work(x,opt,sum,dis+e[i].l,mi,node);
		if(a[x]>=e[i].l&&sum+a[x]-dis-e[i].l+mi>=0)change(a[x]+sum-dis-e[i].l,opt);
	}
}
void calc(int node,long long sum,long long dis,long long ma=0,int f=0){
	ma=max(ma,dis-sum),sum+=a[node],siz[node]=1;
	ans+=ask(ma-a[root]);
	for(register int i=h[node],x;i;i=e[i].pre){
		x=e[i].to;
		if(x==f||vis[x])continue;
		calc(x,sum,dis+e[i].l,ma,node);
		siz[node]+=siz[x];
	}
}
int uniq(){
	sort(base+1,base+1+len);
	int pos,k=0;
	for(register int i=1;i<=len;i=pos){
		pos=i+1;
		while(pos<=len&&base[pos]==base[i])++pos;
		b[++k]=base[i],cn[k]=pos-i;
	}
	return k;
}
void solve(int node){
	int x;
	vis[node]=1,base[len=1]=0,cnt=0;
	for(register int i=h[node];i;i=e[i].pre){
		x=e[i].to;
		if(vis[x])continue;
		Count(x,0,e[i].l,0);
		if(a[x]>=e[i].l)base[++len]=a[x]-e[i].l;
	}
	ans+=len-1,len=uniq();
	build(1,len,rt);
	for(register int i=h[node];i;i=e[i].pre){
		x=e[i].to;
		if(vis[x])continue;
		work(x,-1,0,e[i].l,0);
		if(a[x]>=e[i].l)change(a[x]-e[i].l,-1);
		calc(x,0,e[i].l,e[i].l);
		work(x,1,0,e[i].l,0);
		if(a[x]>=e[i].l)change(a[x]-e[i].l,1);
	}
	clear(rt);
	for(register int i=h[node];i;i=e[i].pre){
		x=e[i].to;
		if(vis[x])continue;
		mx=inf,all=siz[x],getroot(x),solve(root);
	}
}
void dfs(int node=1){
	siz[node]=1;
	for(register int i=h[node],x;i;i=e[i].pre){
		x=e[i].to;
		if(siz[x])continue;
		dfs(x),siz[node]+=siz[x];
	}
}
int main(){
	int n=read();
	for(register int i=1;i<=n;++i)a[i]=read();
	for(register int i=1,x,y,z;i<n;++i)x=read(),y=read(),z=read(),add(x,y,z),add(y,x,z);
	dfs(),all=n,mx=inf,getroot(1),solve(root);
	printf("%lld\n",ans);
}
```



---

## 作者：Durancer (赞：3)

借鉴自 @AxDea大佬 的思路，希望通过这篇题解可以更详细的证明并且阐述一下思路。

### 思路

一看与树上路径问题有关，首先就会想到**点分治**，这里只讲一下用容斥怎么做，~~平衡树的方法我是看不懂~~。

既然要用到点分治，那么一定会把路径分成两份来计数，但是这次这两个路径统计的东西应该是不一样的。

注：以下的 $rt$ 都是在计算的时候子树的根，不是树的重心（~~不过好像就是一个东西~~）。

我们考虑把路径分成 $L_{u\to\ rt},R_{rt\to\ v}$ 两部分，第一部分，我们记录一下，从 $u\to rt$ 最后剩下的油量，但是我们储存的时候我们需要看一下这个是否是合法的，因为我们是从 $rt$ 开始计数的，所以就要考虑逆序推，是否能走到 $rt$，只有合法的路径才记录下来。

1、判断 $L_{u\to rt}$ 的合法性。

设置一个 $\text{flag}$，从 $rt$ 开始，每次进入他的儿子的时候，就记录一下$-w+oil_v$，当然需要与 $0$ 去一个最小值，如果是合法的，那么从 $0$ 开始记录即可。

如果当前进入儿子的子树时 $\text{flag}=0$，那么就直接记录一下从 $u\to rt$ （并且已经在 $rt$ 加满油）时的油的剩余量即可，反之不记录。

2、记录 $R_{rt\to v}$ 中的值只需要记录从 $rt\to v$ 中，所剩油量 （可以是负数）最小的那一段即可，如果这一段最小值都可以补充上，那么从 $u$ 走过来的油一定是够的，判断条件为 $L_{u\to rt}\geq\ R_{rt\to v}$ ，那么这一条路径就是合法的。

这里证明一下为什么是最小值就可以：

想一想为什么会出现最小值，当然是在去 $v$ 的一条边上，在那里补充的油量支撑不了这一条边的耗费，然后从这个点再走到下一个点的时候，补充的油量又可以支撑这一条边的耗费，所以从 $rt\to\ poi$ 这个点的路径就会出现一个最小值，既然走到下一个点的时候油量会有剩余，那么并不会影响下面的走动，只需要考虑如何把这一块油量补齐即可，所以说，这个时候就要看 $u\to rt$ 所剩下的油量的多少了，如果够，那么走这条路径就一定会够，反之不会。

3、容斥答案

在记录 $L,R$ 的同时，跟随着这个数值的还是要记录一个东西，那就是起点，也就是从 $rt$ 开始走出来的第一个点 $st$ 这一个点
这一个点用于容斥。

在容斥的时候，先按照 $L,R$ 的权值分别升序排序，然后双指针记录即可。

最后别忘了容斥掉本来当前的 $L$ 起始点 $st$ 原本的贡献个数，防止重复。

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
#include<queue>
#include<vector>
#include<map>
#define int long long
using namespace std;
const int N=1e5+9;
const int INF=2e9+9;
struct node{
	int last;
	int to;
	int dis;
}e[N<<1];
int head[N],cnt;
int oil[N];//油
int n,sum; 
int siz[N],maxp[N],rt;
bool vis[N];
int ans,l,r;
int idl[N],idr[N];
int Line[N],Rine[N];
int L[N],R[N];
int Cen;//当前的重心
int st;//起点 
int f[N];//记录 
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar(); }
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar(); }
	return f*x;
}
void add(int from,int to,int dis)
{
	e[++cnt].last=head[from];
	e[cnt].to=to;
	e[cnt].dis=dis;
	head[from]=cnt; 
}
bool cmpl(int x,int y)
{
	return L[x]<L[y];
}
bool cmpr(int x,int y)
{
	return R[x]<R[y];
}
void getdis(int u,int fa,int dis,int weast,int flag)
//当前点，父亲，到这个点油的总剩余量，两个点的路径中花费的最大值，判断能否走到	 
{
	if(flag==0)
	{
		L[++l]=dis; 
		Line[l]=st;
	}
	R[++r]=-weast;
	Rine[r]=st;
	for(int i=head[u];i;i=e[i].last)
	{
		int v=e[i].to;
		int w=e[i].dis;
		if(v==fa or vis[v])
			continue;
		getdis(v,u,dis-w+oil[v],min(weast,dis-oil[Cen]-w),min(0ll,flag-w+oil[v]));
	} 
}
void calc(int u)
{
	int j=1;
	l=r=0;
	Cen=u;
	L[++l]=oil[u]; Line[l]=u; f[u]=0;
	R[++r]=0; Rine[r]=u;
	for(int i=head[u];i;i=e[i].last)
	{
		int v=e[i].to;
		int w=e[i].dis;
		if(vis[v]) continue;
		st=v;
		f[st]=0;
		getdis(v,u,oil[u]+oil[v]-w,-w,min(0ll,oil[v]-w));
	}
	for(int i=1;i<=l;i++)
		idl[i]=i;
	for(int i=1;i<=r;i++)
		idr[i]=i;
	sort(idl+1,idl+1+l,cmpl);
	sort(idr+1,idr+1+r,cmpr);
	for(int i=1;i<=l;i++)
	{
		while(j<=r and L[idl[i]]>=R[idr[j]])
		{
			f[Rine[idr[j]]]++;
			j++; 
		}
		ans+=(j-1)-f[Line[idl[i]]];//容斥，当前的j不算数 
	}
}
void root(int u,int fa)
{
	siz[u]=1;
	maxp[u]=0;
	for(int i=head[u];i;i=e[i].last)
	{
		int v=e[i].to;
		if(v==fa or vis[v]) continue;
		root(v,u);
		siz[u]+=siz[v];
		maxp[u]=max(maxp[u],siz[v]);
	}
	maxp[u]=max(maxp[u],sum-siz[u]);
	if(maxp[u]<maxp[rt])
		rt=u;
}
void solution(int u)
{
	vis[u]=1;
	calc(u);
	for(int i=head[u];i;i=e[i].last)
	{
		int v=e[i].to;
		if(vis[v]) continue;
		sum=siz[v];
		maxp[rt=0]=INF;
		root(v,0);
		solution(rt);
	}
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
		oil[i]=read();
	for(int i=1;i<n;i++)
	{
		int u=read();
		int v=read();
		int w=read();
		add(u,v,w);
		add(v,u,w);
	}
	maxp[rt=0]=sum=n;
	root(1,0);
	solution(rt);
	printf("%lld\n",ans);
	return 0;
}
```






---

## 作者：Graphcity (赞：2)

首先做一步转化：原题的限制相当于走过一条边燃料量就会减去边权，求出任意时刻燃料量均不小于零的方案数。

用数学语言去刻画它：设一条路径依次经过点 $u_1,u_2,\cdots,u_k$，那么就有

$$
\min_{i=1}^{k-1}\sum_{j=1}^ia_{u_j}-w(u_j,u_{j+1})\ge 0
$$

考虑点分治。设当前分治中心为 $k$，需要求出经过 $k$ 的合法路径数量。对于一条路径 $(u,v)$，我们把它拆分成两个部分：$(u,l)$ 的部分和 $(l,v)$ 的部分。

- 对于 $(u,l)$ 的部分：

设 $val_i$ 为 $a_i-w(i,fa_i)$，那么点 $u$ 能够到达分治中心 $l$ 当且仅当任意时刻 $val$ 之和大于等于零。这个东西可以利用动态规划来求：设 $f_i$ 为从 $i$ 到 $l$ 的路径上 $val$ 值之和的最小值，就有

$$
f_i=\min(f_{fa_i}+val_i,val_i)
$$

求出 $f_i$ 之后，我们还可以顺便求出从 $i$ 到 $l$ 时候的剩余燃料量，设它为 $dis_i$。

$$
dis_i=dis_{fa_i}+val_i
$$

- 对于 $(l,v)$ 的部分：

这个时候就要和上一部分综合考虑了。设 $g_i$ 为对于 $l$ 到 $i$ 的路径，从 $l$ 出发时至少需要的燃料量，则有

$$
g_i=\max(g_{fa_i},dis_i-a_i+a_l)
$$

将 $dis$ 离散化后，利用树状数组可以方便的求出有多少个点的 $dis$ 值大于等于 $g_i$。

总时间复杂度 $O(n\log^2n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

struct Node{int frm,to,nxt,w;} Edge[Maxn*2+5];
int tot,Head[Maxn+5];
inline void Addedge(int x,int y,int z)
{
    Edge[++tot]=(Node){x,y,Head[x],z};
    Head[x]=tot;
}
int n,s,val[Maxn+5],siz[Maxn+5],maxs[Maxn+5];
int rt,sum,vis[Maxn+5],t[Maxn+5];
ll num[Maxn+5],f[Maxn+5],g[Maxn+5],dis[Maxn+5],dep[Maxn+5],ans;
vector<ll> v;
#define lowbit(x) (x&-x)

inline void Add(int x,int y) {while(x<=s) t[x]+=y,x+=lowbit(x);}
inline int Count(int x) {int res=0; while(x){res+=t[x],x-=lowbit(x);} return res;}
inline void GetRt(int x,int f)
{
    siz[x]=1,maxs[x]=0;
    for(int i=Head[x];i;i=Edge[i].nxt)
    {
        int y=Edge[i].to;
        if(y==f || vis[y]) continue;
        GetRt(y,x),siz[x]+=siz[y];
        maxs[x]=max(maxs[x],siz[y]);
    }
    maxs[x]=max(maxs[x],sum-siz[x]);
    rt=(maxs[x]<maxs[rt]?x:rt);
}
inline void dfs1(int x,int fa)
{
    dis[x]=dis[fa]+num[x];
    f[x]=min(f[fa]+num[x],num[x]);
    if(f[x]>=0) v.push_back(dis[x]),ans++;
    for(int i=Head[x];i;i=Edge[i].nxt)
    {
        int y=Edge[i].to;
        if(y==fa || vis[y]) continue;
        num[y]=val[y]-Edge[i].w,dfs1(y,x);
    }
}
inline void dfs2(int x,int fa,int opt)
{
    if(f[x]>=0)
    {
        if(!opt)
        {
            dis[x]=lower_bound(v.begin(),v.end(),dis[x])-v.begin()+1;
            Add(dis[x],1);
        }
        else Add(dis[x],opt);
    }
    for(int i=Head[x];i;i=Edge[i].nxt)
    {
        int y=Edge[i].to;
        if(y==fa || vis[y]) continue;
        dfs2(y,x,opt);
    }
}
inline void dfs3(int x,int fa)
{
    if(g[x]<=0ll) ans++;
    int id=lower_bound(v.begin(),v.end(),g[x])-v.begin()+1;
    if(id<=s) ans+=(Count(s)-Count(id-1));
    for(int i=Head[x];i;i=Edge[i].nxt)
    {
        int y=Edge[i].to;
        if(y==fa || vis[y]) continue;
        dep[y]=dep[x]+val[x]-Edge[i].w;
        g[y]=max(g[x],-dep[y]);
        dfs3(y,x);
    }
}
inline void Discrete()
{
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    s=v.size();
}
inline void Solve(int x)
{
    f[x]=0,dis[x]=0,v.clear();
    for(int i=Head[x];i;i=Edge[i].nxt)
    {
        int y=Edge[i].to;
        if(vis[y]) continue;
        num[y]=val[y]-Edge[i].w,dfs1(y,x);
    }
    Discrete();
    for(int i=Head[x];i;i=Edge[i].nxt)
    {
        int y=Edge[i].to;
        if(vis[y]) continue;
        dfs2(y,x,0);
    }
    for(int i=Head[x];i;i=Edge[i].nxt)
    {
        int y=Edge[i].to;
        if(vis[y]) continue;
        g[y]=max(0ll,1ll*Edge[i].w-val[x]);
        dep[y]=val[x]-Edge[i].w;
        dfs2(y,x,-1),dfs3(y,x),dfs2(y,x,1);
    }
    for(int i=Head[x];i;i=Edge[i].nxt)
    {
        int y=Edge[i].to;
        if(vis[y]) continue;
        dfs2(y,x,-1);
    }
}
inline void dfs(int x)
{
    vis[x]=1; Solve(x);
    for(int i=Head[x];i;i=Edge[i].nxt)
    {
        int y=Edge[i].to;
        if(vis[y]) continue;
        rt=0,sum=siz[y],GetRt(y,0),GetRt(rt,0),dfs(rt);
    }
}

int main()
{
    n=read(),maxs[0]=n+5;
    For(i,1,n) val[i]=read();
    For(i,1,n-1)
    {
        int a=read(),b=read(),c=read();
        Addedge(a,b,c),Addedge(b,a,c);
    }
    rt=0,sum=n,GetRt(1,0),GetRt(rt,0),dfs(rt);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：StarRoam (赞：1)

**[P5306 [COCI 2018/2019 #5] Transport](https://www.luogu.com.cn/problem/P5306)**

模拟赛的一道点分治好题。

考虑当前计算从 $i$ 到 $j$ 的路径是否合法，所经过的根节点为 $k$。

令 $val_u$ 表示：从 $k$ 到 $u$ 能加的油的总数。

令 $dis_u$ 表示：从 $k$ 到 $u$ 的总距离。

要使此路径合法，从 $i$ 到 $k$ 的部分需要满足：

 $$\forall u ,  val_i - val_u \ge dis_i-dis_u $$

 即

$$val_i-dis_i \ge val_u-dis_u$$

而 $val_i-dis_i$ 为定值，所以此定值要大于此路径上最大的 $val_u-dis_u$。

记 $x$：$val_i-dis_i$，即走完从 $i$ 到 $k$ 的油的剩余量。

则是路径合法，从 $k$ 到 $j$ 需要满足：

$$\forall u ,  x+(val_{fa_u}-a_k) \ge dis_u。 $$

即 

$$x+(val_{fa_u}-a_k-dis_u) \ge 0$$

我们可以考虑用点分治求出所有合法的 $x$ 以及所有 $(val_{fa_u}-a_k-dis_u)$，然后用尺取法求答案。

**注意**加上从 $i$ 到 $k$ 与从 $k$ 到 $j$ 的合法路径。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+5;
int n,a[N];
struct EDGE{int to,w;};
vector<EDGE> e[N];
bool vis[N];
int ntot,rt,mxp[N],sz[N];
void get_root(int pos,int fa)
{
	sz[pos]=1,mxp[pos]=0;
	for(auto now:e[pos])
	{
		int v=now.to;
		if(v==fa||vis[v]) continue;
		get_root(v,pos);
		sz[pos]+=sz[v];
		mxp[pos]=max(mxp[pos],sz[v]);
	}
	mxp[pos]=max(mxp[pos],ntot-sz[pos]);
	if(mxp[pos]<mxp[rt]) rt=pos;
}
int ct1,ct2,ct3,ct4;
ll q1[N],q2[N],q3[N],q4[N],d[N],val[N];
ll ans;
void dfs(int pos,int fa,ll mx,ll mn)
{
	if(val[pos]-d[pos]>=mx) q1[++ct1]=val[pos]-d[pos];
	q2[++ct2]=mn;
	sz[pos]=1;
	for(auto now:e[pos])
	{
		int v=now.to,w=now.w;
		if(vis[v]||v==fa) continue;
		val[v]=val[pos]+a[v];
		d[v]=d[pos]+w;
		dfs(v,pos,max(mx,val[pos]-d[pos]),min(mn,val[pos]-d[v]));
		sz[pos]+=sz[v];
	}
}
void calc(int pos)
{
	val[pos]=a[pos];
	ct3=ct4=d[pos]=0;
	for(auto now:e[pos])
	{
		int v=now.to,w=now.w;
		if(vis[v]) continue;
		ct1=ct2=0;
		val[v]=val[pos]+a[v],d[v]=d[pos]+w;
		dfs(v,pos,val[pos]-d[pos],val[pos]-d[v]);
		sort(q1+1,q1+ct1+1);
		sort(q2+1,q2+ct2+1);
		int p=1;
		for(int i=ct1;i>=1;i--)
		{
			while(q1[i]+q2[p]-a[pos]<0&&p<=ct2) p++;
			ans-=(ct2-p+1);
		}
		for(int i=1;i<=ct1;i++) q3[++ct3]=q1[i];
		for(int i=1;i<=ct2;i++) q4[++ct4]=q2[i];
	}
	sort(q3+1,q3+ct3+1);
	sort(q4+1,q4+ct4+1);
	int now=1;
	ans+=ct3;
	for(int i=ct3;i>=1;i--)
	{
		while(q3[i]+q4[now]-a[pos]<0&&now<=ct4) now++;
		ans+=(ct4-now+1);
	}
	for(int i=1;i<=ct4;i++)
	{
		if(q4[i]>=0)
		{
			ans+=ct4-i+1;
			break;
		}
	}
}
void solve(int pos)
{
	vis[pos]=true;
	calc(pos); 
	for(auto now:e[pos])
	{
		int v=now.to,w=now.w;
		if(vis[v]) continue;
		ntot=sz[v],rt=0;
		get_root(v,pos);
		solve(rt);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<n;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		e[u].push_back(EDGE{v,w});
		e[v].push_back(EDGE{u,w});
	}
	ntot=n,mxp[0]=N;
	get_root(1,0);
	solve(rt);
	cout<<ans;
	return 0;
}
```

---

## 作者：ClearluvXL (赞：1)

# Transport

点分治

## 思路

令当前的根为点分治的根，那么我们可以分成两种情况。过跟和不过跟，那么我们还是此时只考虑过跟，把不过跟的情况放到处理子树里。

那么在任意时刻，都要满足油量 $\geq$ 路径长。

记录当前根节点到 $x$ 点时，在根节点至少需要 $val_{x}$ 的油量。

那么考虑现在哪些点能到根节点，以及到了根节点后剩余的油量。

搜索完当前子树，考虑和之前子树里的点进行配对。那么令 $t1_{x}$ 为当前这棵子树内某个点能到达根节点，且还有 $t1$ 这么多的油，令 $t2$ 为之前子树内如果到达 $x$ 至少需要在根节点有 $-t2$ 这么多的油量。那么排完序之后，考虑使用双指针。

现在考虑如何求 $t1,t2$。

一个点到根节点的后剩余的油量肯定为路径上的点权和 $-$ 边权和。现在考虑这个值合不合法的问题。什么意思呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/s7wu9070.png)

就像当前图一样，很明显点权和 $>$ 边权和，但是他连第一步都迈不出。

这一点怎么处理呢？考虑令 $ch_{x}$ 为 $x$ 的点权 $-$ $x$ 到其父亲的边权。那么，此时如果 $x$ 能到达根节点的话，一定会保证 $x$ 到任何一个点的 $ch$ 和 $\geq 0$。（不包括 ch)。 所以此时我们维护最小的到其父亲节点的路径上的最小的 $ch$ 和。如果此时 $ch_{x}$ 加上这个东西依旧时合法的话，那么 $x$ 就一定能到达根节点。同时，因为其实每个 $ch$ 和都会加上 $ch_{x}$，相当于幅度变，那么此时最小的依旧这个数加上 $ch_{x}$。

现在考虑根节点到该子树内的点的条件。很明显，如果跟节点能直接到这个点的话，那么其他子树到根节点后的剩余值最低可以为 $0$。下文直接说初始值。否则，初始值就应该有个条件。

令 $dic_{x}$ 为根节点到 $x$ 前的点权和 $-$ 边权和。也是同一个道理，不一定合法。我们必须要保证 $x$ 的祖先节点都能到达。所以维护 $x$ 的祖先节点中 $dic$ 的最小值即可。即为到 $x$ 时所必需的初始值。当然是负数时才表示需要初始值啦。

那么说完这些之后，~~我们就能开心点分治啦！！！~~一点都不开心。

## 代码

```c++
#include<bits/stdc++.h>
#define endl '\n'

using namespace std;

const int N=1e5+10;

typedef long long ll;
typedef pair<int,int> pii;

int n;

vector<pii> e[N];

void add(int u,int v,int w){
	e[u].push_back({v,w});
}//end

ll s[N],a[N];

bool vis[N];
int rt;
int sz[N],sum,maxson[N];

void calcsiz(int x,int fa){
	sz[x]=1; maxson[x]=0; 
	for(auto nxt:e[x]){
		int y=nxt.first,w=nxt.second;
		if(y==fa||vis[y]) continue;
		calcsiz(y,x);
		sz[x]+=sz[y];
		maxson[x]=max(maxson[x],sz[y]);
 	}
 	maxson[x]=max(maxson[x],sum-sz[x]);
 	if(maxson[x]<maxson[rt]) rt=x;
}//end

int i1f,i1n,i2f,i2n;//下标 
ll t1f[N],t1n[N],t2f[N],t2n[N];

ll ch[N],dic[N];

void dfs2(int x,int fa,ll dianh,ll bianh){ 
	for(auto nxt:e[x]){
		int y=nxt.first,w=nxt.second;
		if(y==fa||vis[y]) continue;
		ch[y]=min(ch[x]+a[y]-w,a[y]-w);//维护最小前缀区间和 
		if(ch[y]>=0) t1n[++i1n]=dianh+a[y]-bianh-w;
		dfs2(y,x,dianh+a[y],bianh+w);
	}
}//end

void dfs3(int x,int fa,ll mindic){ 
	for(auto nxt:e[x]){
		int y=nxt.first,w=nxt.second;
		if(y==fa||vis[y]) continue;
		dic[y]=dic[x]+a[x]-w;
		ll nowmindic=min(mindic,dic[y]);
		t2n[++i2n]=nowmindic;
		dfs3(y,x,nowmindic);
	}
}//end

ll ans=0;

void solve(int x,int fa){
	vis[x]=1;
	ch[x]=0;
	
	i1f=i2f=0;
	
	t1f[++i1f]=0;//根节点本身 
	t2f[++i2f]=0;
	
	for(auto nxt:e[x]){
		int y=nxt.first,w=nxt.second;
		if(y==fa||vis[y]) continue;
		ch[y]=ch[x]+a[y]-w;//前缀和 
		dic[y]=a[x]-w;
		i1n=i2n=0;
		
		if(ch[y]>=0) t1n[++i1n]=ch[y];
		dfs2(y,x,a[y],w); 
		
		t2n[++i2n]=dic[y];
		dfs3(y,x,dic[y]);
		
		sort(t1n+1,t1n+i1n+1);
		sort(t2n+1,t2n+i2n+1);
		
		int r=i1f+1;
		for(int i=1;i<=i2n;i++){
			while(r>1&&t1f[r-1]+t2n[i]>=0) r--;
			ans+=(i1f-r+1);
		}
		
		r=i1n+1;
		for(int i=1;i<=i2f;i++){
			while(r>1&&t1n[r-1]+t2f[i]>=0) r--;
			ans+=(i1n-r+1);
		}
		
		for(int i=1;i<=i1n;i++) t1f[++i1f]=t1n[i];
		for(int i=1;i<=i2n;i++) t2f[++i2f]=t2n[i];
		
		sort(t1f+1,t1f+i1f+1);
		sort(t2f+1,t2f+i2f+1);
	}
	
	for(auto nxt:e[x]){
		int y=nxt.first,w=nxt.second;
		if(y==fa||vis[y]) continue;
		sum=sz[y];
		rt=0;
		calcsiz(y,x);
		calcsiz(rt,x);
		solve(rt,x);
	}
}//end

int main(){
	freopen("transport.in","r",stdin);
	freopen("transport.out","w",stdout);
	
	ios::sync_with_stdio(0);
	
	cin>>n;
	
	for(int i=1;i<=n;i++) cin>>a[i];
	
	for(int i=1;i<n;i++){
		int u,v,w; cin>>u>>v>>w;
		add(u,v,w); add(v,u,w);
	}
	
	maxson[0]=(int)1e9;
	rt=0; sum=n;
	calcsiz(1,0);
	calcsiz(rt,0);
	solve(rt,0);
		
	cout<<ans<<endl;
	
	return 0;
}//end
```

---

## 作者：CQ_Bab (赞：1)

# 思路

首先考虑转化，我们将一条 $i\to j$ 的路径转化为 $i\to x$ 与 $x\to j$ 两条，那么我们对于两种情况分类讨论即可。

- 首先我们定义 $sum1_i,sum2_i$ 为从当前的必经点 $x$ 到 $i$ 的点权和以及边权和。

- 对于第一条路径，一个满足条件的 $i$ 是能满足 $sum1_i-sum2_i\geq 0$ 且对于从 $i\to x$ 的路径上的任意一点 $j$ 都要满足 $sum1_i-sum2_i\ge sum1_j-sum2_j$ 所以我们这里记录一个最大的 $sum1_j-sum2_j$ 即可。

- 对于第二条路径，我们因为要让一二两条路径进行匹配所以我们假设前一条路径剩的油为 $now$ 那么对于每一个点 $x$ 都需要满足 $sum1_{fa_x}-sum2_x+now\ge 0$ 就是对于到达 $x$ 时还剩的油要大于等于 $0$，然后移一下项可以得出 $now\leq sum1_{fa_x}-sum2_x$ 那么只需要记录路途上 $sum1_{fa_x}-sum2_x$ 的最小值即可。

- 然后对于这道题进行匹配的时候就是对于第一种情况存一个数组，第二种情况存一个数组，再对于当前的值与之前的进行匹配，又让之前的对于当前值进行匹配即可，所以根本不用容斥原理，这里匹配的时候只用在最大值中找有多少个大于等于最小值中的即可，直接双指针即可。

注意这里为了保证正确性要将在同一棵子树中的答案减去，就是容斥原理。

# 代码

```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define int long long
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define in(x) scanf("%lld",&x)
#define fire signed
#define il inline
il void print(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int T=1;
int n;
const int N=1e5+10;
int p[N];
int Max[N],siz[N];
vector<pair<int,int>>v[N];
int vis[N],rt,sum;
void dfs(int x,int fa) {
	Max[x]=false;
	siz[x]=1;
	for(auto xx:v[x]) {
		int to=xx.first;
		if(to==fa||vis[to]) continue;
		dfs(to,x);
		siz[x]+=siz[to];
		Max[x]=max(Max[x],siz[to]);
	}
	Max[x]=max(Max[x],sum-siz[x]);
	if(Max[x]<Max[rt]) rt=x;
}
int a[N],idx,tot,b[N];
int sum1[N],sum2[N];
int res;
void dfs1(int x,int fa,int mx,int mi) {//在a中大于等于b的为答案 
	if(sum1[x]-sum2[x]>=mx) {
		a[++tot]=sum1[x]-sum2[x];
	}
	b[++idx]=mi;
	if(mi>=0) res++;
	for(auto xx:v[x]) {
		int to=xx.first;
		if(to==fa||vis[to]) continue;
		sum1[to]=sum1[x]+p[to];
		sum2[to]=sum2[x]+xx.second;
		dfs1(to,x,max(mx,sum1[x]-sum2[x]),min(mi,sum1[x]-sum2[to]));
	}
}
int q1[N],q2[N],cnt1,cnt2;
void get(int x,int fa) {
	vis[x]=1;
	sum1[x]=p[x];
	sum2[x]=false;
	cnt1=cnt2=false;
	for(auto xx:v[x]) {
		int to=xx.first;
		if(to==fa||vis[to]) continue;
		sum1[to]=sum1[x]+p[to];
		sum2[to]=xx.second;
		dfs1(to,x,sum1[x],sum1[x]-sum2[to]);
		sort(a+1,a+1+tot);
		sort(b+1,b+1+idx);
		int l=1;
		rep1(i,idx,1) {
			while(l<=tot&&a[l]+b[i]-p[x]<0) {
				l++;
			}
			res-=tot-l+1;
		}
		res+=tot;
		rep(i,1,tot) q1[++cnt1]=a[i];
		rep(i,1,idx) q2[++cnt2]=b[i];
		idx=tot=false;
	}
	sort(q1+1,q1+1+cnt1);
	sort(q2+1,q2+1+cnt2);
	int l=1;
	rep1(i,cnt2,1) {
		while(l<=cnt1&&q1[l]+q2[i]-p[x]<0) {
			l++;
		}
		res+=cnt1-l+1;
	}
	for(auto xx:v[x]) {
		int to=xx.first;
		if(to==fa||vis[to]) continue;
		rt=false;
		sum=siz[to];
		dfs(to,x);
		get(rt,x);
	}
}
void solve() {
	in(n);
	rep(i,1,n) in(p[i]);
	rep(i,1,n-1) {
		int x,y,z;
		in(x),in(y),in(z);
		v[x].push_back({y,z});
		v[y].push_back({x,z});
	}
	Max[0]=LONG_LONG_MAX;
	rt=false;
	sum=n;
	dfs(1,0);
	get(rt,0);
	cout<<res<<endl;
	return;
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：OIer_ACMer (赞：1)

~~好难呀！~~


------------
注意：本人实力较弱，部分思路参考[大佬博客](https://blog.csdn.net/glorious_dream/article/details/126254904?ops_request_misc=&request_id=&biz_id=102&utm_term=P5306%20%5BCOCI2018-2019&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-126254904.142^v93^insert_down28v1&spm=1018.2226.3001.4187#5%5D%20Transp&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-126254904.142^v93^insert_down28v1)。

------------
## 警钟敲烂：
这道题今天上午做了 $2$ 小时，搞了半天 Splay 才发现是点分治，所以各位，一定要思维开拓！！！

------------
## 大致思路：
这道题是一道经典的**点分治**题目，因为这道题要求一个数对 $(u,v)$ 是大货车可以走的路线，而这个 $(u,v)$ 又没限制在哪，所以分治是个很好的思路。

我们先来根据点分治的性质模拟一下分治的过程：首先找到 $root$，也就是**分治开始节点**，接着对于根为 $root$ 的这棵树进行操作，最后把 $root$ 删掉。

接着，操作便是这道题很难的一步，首先，我们要确定 $i$ 和 $j$ 要在 $root$ 的两棵不同的子树中，最后统计答案的时候，把 $i$ 和 $j$ 在一棵子树的情况给删掉就行。至于怎么处理 $i$ 与 $j$ 之间的距离（注意，是题目中的），同时也要判断可行性，我们就可以这样做：

1. 把 $i$ 到 $j$ 的路径，分为 $i$ 到 $root$ 和 $root$ 到 $j$。我们建立两个数组 $w_i$，$d_i$ 分别记录这条路径的点权之和，和边权之和。

2. 从 $i$ 到 $root$：对于满足条件的节点 $k$，需要保证 $w_i - w_k\ge d_i - d_k$，因为我们**需要保证这么多油需要跑完整个路程**，而我们**需要在每个点加油**，也就是点权转化为了油量，根据小学知识，我们可以把这个式子移项，可以得到 $(w_i - w_k) - (d_i - d_k) \ge 0$。所以我们记录最大的 $w_k - d_k$，也就是就可以判断 $i$ 到 $root$ 是否合法。

3. 同理，从 $root$ 到 $j$：这种情况，该路径的起点**不一定**是 $root$，可以从另一个子树的 $u$ 为起点。设以 $u$ 为起点到 $root$，剩余的油量是 $x$，则路径上的任意一点 $k$，需要满足 $x - w[d[k]] \ge d[k]$（同理，也是为了满足第二条中的要求），为了简化公式，我们定义$fa[k]$ 表示 $k$ 的父亲。变换一下，式子就变成 $x + (w[fa[k]] - d[k]) \ge 0$。这时我们维护路径上 $w[fa[k]] - d[k]$ 的最小值就可以了。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int M = 2e5 + 10;
int n;
int head[M], siz[M], maxp[M], vis[M], a[M];
int w[M], d[M], tmp1[M], tmp2[M], q1[M], q2[M];
int root, sum, ans, cnt, cnt1, cnt2;
struct edge
{
    int to, nxt, w;
} edge[M];
void add(int u, int v, int w)
{
    edge[++cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}
void zson(int u, int fa)
{
    siz[u] = 1;
    maxp[u] = 0;
    for (int i = head[u]; i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (vis[v] || v == fa)
        {
            continue;
        }
        zson(v, u);
        siz[u] += siz[v];
        maxp[u] = max(maxp[u], siz[v]);
    }
    maxp[u] = max(maxp[u], sum - siz[u]);
    if (maxp[u] < maxp[root])
    {
        root = u;
    }
}
void dfs(int u, int fa, int mx, int mi)
{
    if (w[u] - d[u] >= mx)
    {
        tmp1[++cnt1] = w[u] - d[u];
    }
    tmp2[++cnt2] = mi;
    for (int i = head[u]; i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (v == fa || vis[v])
        {
            continue;
        }
        d[v] = d[u] + edge[i].w;
        w[v] = w[u] + a[v];
        dfs(v, u, max(mx, w[u] - d[u]), min(mi, w[u] - d[v]));
    }
}
void solve(int u)
{
    int res1 = 0, tot2 = 0;
    d[u] = 0, w[u] = a[u];
    for (int i = head[u]; i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (vis[v])
        {
            continue;
        }
        cnt1 = cnt2 = 0;
        d[v] = edge[i].w, w[v] = w[u] + a[v];
        dfs(v, u, w[u] - d[u], w[u] - d[v]);
        sort(tmp1 + 1, tmp1 + cnt1 + 1);
        sort(tmp2 + 1, tmp2 + cnt2 + 1);
        int l = 1;
        for (int i = cnt2; i >= 1; --i)
        {
            while (l <= cnt1 && tmp1[l] + tmp2[i] - a[u] < 0)
            {
                l++;
            }
            ans -= cnt1 - l + 1;
        }
        for (int i(1); i <= cnt1; ++i)
        {
            q1[++res1] = tmp1[i];
        }
        for (int i(1); i <= cnt2; ++i)
        {
            q2[++tot2] = tmp2[i];
        }
    }
    sort(q1 + 1, q1 + res1 + 1);
    sort(q2 + 1, q2 + tot2 + 1);
    int l = 1;
    for (int i(tot2); i >= 1; --i)
    {
        if (q2[i] >= 0)
        {
            ans++;
        }
        while (l <= res1 && q1[l] + q2[i] - a[u] < 0)
        {
            l++;
        }
        ans += res1 - l + 1;
    }
    ans += res1;
}
void work(int u)
{
    vis[u] = 1; 
    solve(u);   
    for (int i = head[u]; i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (vis[v])
        {
            continue;
        }
        maxp[root = 0] = sum = siz[v]; 
        zson(v, 0);
        zson(root, 0); 
        work(root);       
    }
}
signed main()
{
    n = read();
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
    }
    for (int i = 1; i < n; i++)
    {
        int u = read(), v = read(), w = read();
        add(u, v, w);
        add(v, u, w);
    }
    maxp[0] = sum = n;
    zson(1, 0);
    zson(root, 0);
    work(root);
    cout << ans << endl;
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/121596996)

---

## 作者：FutaRimeWoawaSete (赞：1)

**sol of P5306**

个人感觉比较 trick。没有太大的思维难度。

一个套路的想法是观察到求总的合法路径数，直接尝试点分治。

发现维护的东西可以被拆为自底向顶的路径和自顶向底的路径，发现路径本身就是一个 $y$ 值与前缀和相关的带折点函数，则对于自顶向底的路径直接从上往下跑维护前缀和上拐点的最小值。

考虑拼接的条件，需要一个**合法**的自底向顶函数，维护出来最后一个拐点的 $y$ 值后在每个子树上做二维数点就随便 $O(n \log ^ 2 n)$ 了。

如果你做过很多题，很容易就看出来对于自底向顶路径对应的前缀函数是需要从后往前构造的（路径是底到顶，但实际上遍历的时候是从根往子树走），需要的信息是函数的顶点，这是一个半群信息，每次往前加点时可以直接 $O(1)$ 合并。

实现时需注意路径的划分。我采用的是将根划分进自顶向底的路径这样的写法，则我们在求经过 $\text{rt}$ 的合法路径时：

- 需要单独求和自顶向底路径的合法个数（包含 $\text{rt}$）；

- 维护**合法**的自底向顶路径函数时只需要对路径求和以及维护顶点信息即可判断是否合法以及需要的数点；

- 维护自顶向底路径函数时维护顶点即可。

注意的是路径是无序的，所以在枚举子树时匹配有两类：前后分别是底向顶匹配顶向底，顶向底匹配底向顶。

对于求解二维数点在此题可以采取排序加双指针或数据结构的方式进行求解。

时间复杂度 $O(n \log ^ 2 n)$，使用的线段树实现。

```cpp
/*
考虑淀粉质，由于是有序路径所以考虑每次复合两个路径。
显然路径等价于折现函数上撒点，信息可以转化成半群的，维护路径最小的需要燃料数即可。
然后就直接统计就做完了
我们细节一点，想一下这个半群信息怎么合并：
自底向上，相当于产生的是 maxv，这个是可以平衡树启发式合并的？套个淀粉质就起飞了啊！想点快的。
好像我是神笔，直接对于整条链求和就行了。 
自底向下，这个就直接维护初始为 0 时向下传的信息就行了。 
*/
#include "bits/stdc++.h"
using namespace std;
#define int ll 
#define ll long long
inline int read() {
    char ch = getchar();
    int x = 0, f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void write(ll x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
const int Len = 1e5 + 5;
const ll Inf = 1e14;
int n,m,w[Len],rt,siz[Len],vis[Len],head[Len],cnt,S,mx[Len];
ll sm[Len],mns[Len][3],tr[Len];
struct node
{
	int next,to,w;
}edge[Len << 1];
inline void add(int from,int to,int w)
{
	edge[++ cnt].to = to;
	edge[cnt].w = w;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
void getrt(int x,int f)
{
	mx[x] = 0 , siz[x] = 1;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f || vis[to]) continue;
		getrt(to , x);
		siz[x] += siz[to];
		if(siz[to] > mx[x]) mx[x] = siz[to];
	}
	if(S - siz[x] > mx[x]) mx[x] = S - siz[x];
	if(mx[x] < mx[rt]) rt = x;
}
void resiz(int x,int f)
{
	siz[x] = 1;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f || vis[to]) continue;
		resiz(to , x);
		siz[x] += siz[to]; 
	}
}
ll q[Len][2];int len[2];ll as,ss;
struct info
{
	#define ls(x) ch[x][0]
	#define rs(x) ch[x][1]
	int rt,ct,ch[Len * 50][2],sum[Len * 50];
	inline void clr(){rt = 0;for(int i = 1 ; i <= ct ; i ++) ch[i][0] = ch[i][1] = sum[i] = 0;ct = 0;}
	inline void push_up(int p){sum[p] = 0;if(ls(p)) sum[p] += sum[ls(p)];if(rs(p)) sum[p] += sum[rs(p)];}
	void update(int &p,ll l,ll r,ll idx)
	{
		if(!p) p = ++ ct;
		if(l == r) 
		{
			sum[p] ++;
			return;
		}
		ll mid = (l + r) >> 1;
		if(idx <= mid) update(ls(p) , l , mid , idx);
		else update(rs(p) , mid + 1 , r , idx);
		push_up(p); 
	}
	ll query(int &p,ll l,ll r,ll nl,ll nr)
	{
		if(!p) return 0;
		if(nl <= l && nr >= r) return sum[p];
		ll mid = (l + r) >> 1;ll res = 0;
		if(nl <= mid) res += query(ls(p) , l , mid , nl , nr);
		if(nr > mid) res += query(rs(p) , mid + 1 , r , nl , nr);
		return res; 
	}
	inline void upd(ll idx){update(rt , -Inf , Inf , idx);return;}
	inline ll Q(ll nl,ll nr){return query(rt , -Inf , Inf , nl , nr);}
}T1,T2;
void getdis(int x,int f)
{
	as += T1.Q(-mns[x][1] , Inf);
	if(mns[x][0] >= 0 && sm[x] - w[rt] >= 0) as += T2.Q(-Inf , sm[x] - w[rt]); 
	as += (mns[x][1] >= 0);
	as += (mns[x][2] >= 0);
	//printf("!!!%d %lld %lld\n",x,mns[x][1],mns[x][2]);
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f || vis[to]) continue;
		sm[to] = sm[x] - edge[e].w + w[to];
		mns[to][0] = min(mns[x][0] + (w[to] - edge[e].w) , 1ll * (w[to] - edge[e].w));
		mns[to][1] = min(mns[x][1] , sm[x] + - edge[e].w);
		mns[to][2] = min(mns[x][2] + (w[to] - edge[e].w) , 1ll * (w[to] - edge[e].w));
		if(mns[to][0] >= 0) q[++ len[0]][0] = sm[to] - w[rt];
		q[++ len[1]][1] = mns[to][1];
		getdis(to , x);
	}
}
void calc(int x)
{
	T1.clr();T2.clr();ss = as;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		len[0] = len[1] = 0;
		int to = edge[e].to;if(vis[to]) continue;
		sm[to] = w[x] + w[to] - edge[e].w;
		mns[to][0] = (w[to] - edge[e].w);
		mns[to][1] = w[x] - edge[e].w;
		mns[to][2] = w[to] - edge[e].w;
		if(mns[to][0] >= 0) q[++ len[0]][0] = sm[to] - w[rt];
		q[++ len[1]][1] = mns[to][1];
		getdis(to , x);
		for(int j = 1 ; j <= len[0] ; j ++) if(q[j][0] >= 0) 
		{
			//printf("####%lld\n",q[j]);
			T1.upd(q[j][0]);
		}
		for(int j = 1 ; j <= len[1] ; j ++) T2.upd(-q[j][1]);
	}
	//printf("%d %lld\n",x,as - ss);
}
void solve(int x)
{
	vis[x] = 1;calc(x);
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(vis[to]) continue;
		resiz(to , x);
		S = siz[to] , mx[rt = 0] = n + 1;
		getrt(to , 0) , resiz(rt , 0) , solve(rt);
	}
}
signed main()
{
	n = read();
	for(int i = 1 ; i <= n ; i ++) w[i] = read();
	for(int i = 1 ; i < n ; i ++)
	{
		int x,y,w;x = read() , y = read() , w = read();
		add(x , y , w) , add(y , x , w); 
	}
	S = n , mx[rt = 0] = n + 1; 
	getrt(1 , 0);resiz(rt , 0);
	solve(rt);
	printf("%lld\n",as);
	return 0;
}
```

---

## 作者：AxDea (赞：1)

树上点对问题考虑点分治。

按照套路讨论经过一个点 $p$ 的路径的情况。

对于这道题的每一个点对 $(u,v)$ 的路径可以分为 $u\rightarrow p$ 和 $p\rightarrow v$ 两段。

对于前者，需要知道走完这条路径后剩余的油量，记作 $L_{u\rightarrow p}$ ，

对于后者，需要知道在允许油量小于 0 时，走这条路径时油量的最小值，记作 $R_{p\rightarrow v}$ 。

这样只要满足 $L_{u\rightarrow p}\geq R_{p\rightarrow v}$ 时，点对 $(u,v)$ 成立。

处理出 $L$ 和 $R$ 后，将两者暴力排序，之后用双指针扫一遍就行了，不要忘了用容斥或者染色法避免重复计数。

时间复杂度 $\mathcal{O}(n\log_2^2 n)$

Code(C++):

```cpp
#include<bits/stdc++.h>
#define forn(i,s,t) for(register int i=(s);i<=(t);++i)
using namespace std;
typedef long long LL;
const int N = 1e5+1e3;
template<typename T>inline T Max(T A, T B) {return A>B?A:B;}
template<typename T>inline T Min(T A, T B) {return A<B?A:B;}
struct List {int dir, nxt; LL lng; } E[N<<1];
int G[N], cnt;
inline void Add(int u, int v, LL w) {
	E[++cnt].dir = v, E[cnt].nxt = G[u], G[u] = cnt;
	E[cnt].lng = w;
}
int n; LL a[N], Ans;
bool vis[N];
int Mx[N], sz[N], rt, S;
void Getrt(int u, int fa) { // 找重心 
	sz[u] = 1, Mx[u] = 0;
	for(int i=G[u];i;i=E[i].nxt) {
		int v = E[i].dir;
		if(vis[v] || v == fa) continue ;
		Getrt(v, u);
		sz[u] += sz[v];
		Mx[u] = Max(Mx[u], sz[v]);
	}
	Mx[u] = Max(Mx[u], S - sz[u]);
	(Mx[u] < Mx[rt]) && (rt = u);
}
LL L[N], R[N];
int f[N], l, r, Cl[N], Cr[N], now, Nu, idl[N], idr[N];
inline bool cmpl(int A, int B) {return L[A] < L[B];}
inline bool cmpr(int A, int B) {return R[A] < R[B];}
void dfs(int u, int fa, LL dist, LL Dn, LL Up) {
	if(Up == 0) L[++l] = dist, Cl[l] = now;
	R[++r] = -Dn, Cr[r] = now;
	for(int i=G[u];i;i=E[i].nxt) {
		int v = E[i].dir; LL w = E[i].lng;
		if(vis[v] || v == fa) continue ;
		dfs(v, u, dist - w + a[v], Min(Dn, dist - a[Nu] - w), Min(0ll, Up - w + a[v]));
	}
}
void calc(int u) {
	l = r = 0, Nu = u;
	L[++l] = a[u], Cl[l] = u, f[u] = 0;
	R[++r] = 0, Cr[r] = u;
	for(int i=G[u];i;i=E[i].nxt) {
		int v = E[i].dir; LL w = E[i].lng;
		if(vis[v]) continue ;
		now = v; f[now] = 0;
		dfs(v, u, a[u] + a[v] - w, -w, Min(0ll, - w + a[v]));
	}
	forn(i,1,l) idl[i] = i; sort(idl+1, idl+l+1, cmpl);
	forn(i,1,r) idr[i] = i; sort(idr+1, idr+r+1, cmpr);
	int j = 1;
	forn(i,1,l) {	// 2 Pnt 
		while(j <= r && R[idr[j]] <= L[idl[i]]) f[Cr[idr[j++]]] ++ ;
		Ans += j - 1 - f[Cl[idl[i]]];
	}
}
void solve(int u) {
	vis[u] = 1;
	calc(u);
	for(int i=G[u];i;i=E[i].nxt) {
		int v = E[i].dir;
		if(vis[v]) continue ;
		S = sz[v] > sz[u] ? n - sz[u] : sz[v];
		rt = 0, Getrt(v, v);
		solve(rt);
	}
}
int main() {
	scanf("%d", &n);
	forn(i,1,n) scanf("%lld", a+i);
	forn(i,2,n) {
		int u, v; LL w;
		scanf("%d%d%lld", &u, &v, &w);
		Add(u, v, w), Add(v, u, w);
	}
	S = Mx[rt = 0] = n;
	Getrt(1, 1);
	solve(rt);
	printf("%lld\n", Ans);
	return 0;
} 
```

---

## 作者：bsdsdb (赞：0)

题意：有一棵带点权和边权的树。现在你想从节点 $u$ 走到节点 $v$，你每走到一个节点（包括 $u$）手里的钱都会多出对应的点权块，但是每条边都会收你边权块过路费。问有多少对点 $(u,v)$ 使得你在一开始没钱（拿 $u$ 的钱之前没钱，$u$ 的钱可以拿）的情况下走到 $v$。

解：路径问题，所以可以考虑设 $r$ 为根，只处理经过 $r$ 的，剩下的点分治。对于经过 $r$ 的 $(u,v)$，可以分为两部分：从 $u$ 开始走到 $r$；如果走到了，拿着剩下的钱从 $r$ 走到 $v$。由此我们可以设四个数组 $\mathrm{Uc},\mathrm{Ur},\mathrm{Dc},\mathrm{Dr}$，分别表示：从 $x$ 走到 $r$ 最少需要多少启动资金（可能为负，为正表示走不到）；从 $x$ 走到 $r$ 能剩下多少块钱（不拿 $r$ 的钱）；从 $r$ 走到 $x$ 所需启动资金和剩下的钱（拿 $r$ 不拿 $v$）。**本人踩过的坑：并不总是 $\mathrm{Uc}_x=-\mathrm{Ur}_x$**。设 $p$ 为 $x$ 的父亲，$w$ 为边 $(p,x)$ 的权值，$a_x$ 为 $x$ 的权值，那么这四个数组可以如下递推：

$$
\mathrm{Uc}_x=\max(w-a_x,\mathrm{Uc}_p+w-a_x)\\
\mathrm{Ur}_x=a_x-w+\mathrm{Ur}_p\\
\mathrm{Dc}_x=
\begin{aligned}\begin{cases}
w-a_p,\quad&p=r\\
\max(\mathrm{Dc}_p,w-a_p-\mathrm{Dr}_p),\quad&\text{otherwise}
\end{cases}\end{aligned}\\
\mathrm{Dr}_x=\mathrm{Dr}_p+a_p-w\\
\mathrm{Uc}_r=\mathrm{Ur}_r=\mathrm{Dc}_r=\mathrm{Dr}_r=0
$$

有了这四个数组之后，$u$ 能走到 $v$ 就当且仅当 $\mathrm{Uc}_u\le0\land\mathrm{Ur}_u\ge\mathrm{Dc}_v$。

法一：开一个线段树，每个子树两轮dfs，第一轮对每个 $u$ 将答案加上 $[\mathrm{Dc}_v,+\infty]$ 上的区间和；第二轮当 $\mathrm{Uc_u}\le0$ 的时候将线段树的 $\mathrm{Ur}_u$ 位置加上 $1$。**本人踩过的坑：这样子统计出来的 $(u,v)$ 对只有 $u$ 的所处子树比 $v$ 靠前的情况，想要统计所有答案应该倒着再扫一遍**。时间复杂度 $\Omicron(n\log n\log nV)=\Omicron(n\log n\log V)$。

法二：对两个可重集 $S,T$ 设函数 $f(S,T)\coloneqq\sum_{i\in S}\sum_{j\in T}[i\ge j]$，那么他是可以双指针 $\Omicron(|S|\log|S|+|T|\log|T|)$ 计算的（要排序）。但是我们不能直接将所有的 $\mathrm{Ur}_x(\mathrm{Uc}_x\le0)$ 和 $\mathrm{Dc}_x$ 拉在一起计算，因为这样可能会将来自同一子树的两个节点也算进答案中。所以我们还要将每个子树内部的 $\mathrm{Ur}$ 和 $\mathrm{Dc}$ 求一遍 $f$，把它从答案中减去。注意还要从答案中减掉由 $(r,r)$ 贡献的 $1$。在 $r$ 为根的树上单次统计的复杂度为 $\Omicron(n\log n)$，总复杂度也就是 $\Omicron(n\log^2n)$。

```cpp
#include <bits/stdc++.h>
//#define CODEFORCES
#ifdef CODEFORCES 
#pragma GCC optimize(1,2,3,"Ofast","inline","unroll-loops")
#endif
bool memtest1;
using namespace std; 
namespace heead {
	// types
	using i32 = int32_t;
	using i64 = int64_t;
	using i128 = __int128;
	using u32 = unsigned int;
	using u64 = unsigned long long;
	using f32 = float;
	using f64 = double;
	using f128 = __float128;
	using ll = i64;
	using ull = u64;
	using ldb = long double;
	#define umap unordered_map
	#define uset unordered_set
	#define prque priority_queue
	#define pi32 pair<i32, i32>
	#define pi64 pair<i64, i64>
	#define pll pair<ll, ll>
	// functions
	#define emp emplace
	#define empb emplace_back
	#define empf emplace_front
	#define mkp make_pair
//	mt19937_64 rd(chrono::high_resolution_clock().now().time_since_epoch().count());
	mt19937_64 rd(1);
	ldb randreal() {
		return ldb(rd()) / (1ll << 32) / (1ll << 32);
	}
	bool dice(ldb x) {
		return randreal() <= x;
	}
	// constants
	#define csep constexpr
	csep i64 inf = 0x3f3f3f3f3f3f3f3fll;
	csep f64 eps = 1e-8;
	csep f64 PI = 3.14159265358979323846264338327950288419716939937510582097;
	// non-std type io
	istream& operator>>(istream& in, i128& x) {
		string input;
		in >> input;
		x = 0;
		for (char c : input) {
			if (c == '-') {
				continue;
			}
			x = (x << 3) + (x << 1) + (c & 15);
		}
		if (input[0] == '-') {
			x *= -1;
		}
		return in;
	}
	ostream& operator<<(ostream& out, i128 x) {
		stack<char> output;
		if (x < 0) {
			out << '-';
			x *= -1;
		}
		if (!x) {
			out << '0';
			return out;
		}
		while (x) {
			output.emp((x % 10) | 48);
			x /= 10;
		}
		while (!output.empty()) {
			out << output.top();
			output.pop();
		}
		return out;
	}
	istream& operator>>(istream& in, f128& x) {
		string input;
		in >> input;
		f128 mul = 1;
		i64 id = (input.find('.') == string::npos ? input.length() : input.find('.')) - (input[0] == '-') - 1;
		for (ll i = 1; i <= id; ++i) {
			mul *= 10;
		}
		x = 0;
		for (char c : input) {
			if (c == '.' || c == '-') {
				continue;
			}
			x += mul * (c & 15);
			mul /= 10;
		}
		if (input[0] == '-') {
			x *= -1;
		}
		return in;
	}
	csep i64 F128ACC = 12;
	ostream& operator<<(ostream& out, f128 x) {
		// negative case
		if (x < 0) {
			out << '-';
			x *= -1;
		}
		// integer part
		out << i128(x);
		x -= i128(x);
		// fractional part
		for (ll i = 1; i <= F128ACC; ++i) {
			x *= 10;
		}
		if (!x) {
			return out;
		}
		out << '.';
		// prefix 0
		i128 y = x;
		i128 _y = y;
		for (ll i = 1; i <= F128ACC; ++i) {
			if (!_y) {
				out << '0';
			}
			_y /= 10;
		}
		// suffix 0
		while (y && y % 10 == 0) {
			y /= 10;
		}
		// out
		out << i128(y);
		return out;
	}
}
using namespace heead;

//#define DEBUG
#define DEBUG_USAGE

// 1. build centroid tree
// 2. for all centroid node x:
//   1. calculate U, D with x rooted
//   2. path (a,b) is legal iff -U_a\ge0 and rest_a\ge D_b

csep ll MAXN = 1e5 + 5, V = 1e14 + 5;
ll n, a[MAXN], ans;
vector<pll> e[MAXN];

// centroid tree part
vector<ll> ct[MAXN];
ll ctroot;
namespace centree {
	ll sz[MAXN], mxs[MAXN];
	bool vis[MAXN];
	#define cli if (i.first == pr || vis[i.first]) continue
	void clear(ll x, ll pr) {
		sz[x] = mxs[x] = 0, mxs[0] = inf;
		for (auto i : e[x]) {
			cli;
			clear(i.first, x);
		}
	}
	void setsz(ll x, ll pr) {
		sz[x] = 1;
		for (auto i : e[x]) {
			cli;
			setsz(i.first, x);
			sz[x] += sz[i.first];
		}
	}
	void fndcen(ll x, ll pr, ll crt, ll& ret) {
		mxs[x] = 0;
		for (auto i : e[x]) {
			cli;
			fndcen(i.first, x, crt, ret);
			mxs[x] = max(mxs[x], sz[i.first]);
		}
		mxs[x] = max(mxs[x], sz[crt] - sz[x]);
		if (mxs[x] < mxs[ret]) {
			ret = x;
		}
	}
	void bdct(ll x, ll pr) {
		ll cen = 0;
		clear(x, pr), setsz(x, pr), fndcen(x, pr, x, cen);
		if (pr) {
			ct[pr].empb(cen);
		} else {
			ctroot = cen;
		}
		vis[cen] = 1;
		for (auto i : e[cen]) {
			cli;
			bdct(i.first, cen);
		}
	}
	#undef cli
}

// dp part
namespace tdv {
	ll U[MAXN], D[MAXN], Ure[MAXN], Dre[MAXN];
	bool vis[MAXN];
	#define cli if (i.first == pr || vis[i.first]) continue
	void clear(ll x, ll pr) {
		U[x] = D[x] = Ure[x] = Dre[x] =  0;
		for (pll i : e[x]) {
			cli;
			clear(i.first, x);
		}
	}
	void dp(ll x, ll pr, ll v, ll sp, vector<ll> &retU, vector<ll> &retD) {
		U[x] = max(v - a[x], U[pr] + v - a[x]);
		Ure[x] = a[x] - v + Ure[pr];
		Dre[x] = Dre[pr] + a[pr] - v;
		if (pr == sp) {
			D[x] = v - a[pr];
		} else {
			D[x] = max(D[pr], v - a[pr] - Dre[pr]);
		}
		if (U[x] <= 0) {
			retU.empb(Ure[x]);
		}
		retD.empb(D[x]);
		for (pll i : e[x]) {
			cli;
			dp(i.first, x, i.second, sp, retU, retD);
		}
	}
	ll doublepointer(vector<ll> &u, vector<ll> &d) {
		// (a,b):u_a\ge d_b
		ll ret = 0;
		sort(u.begin(), u.end());
		sort(d.begin(), d.end());
		ll p1 = 0, p2 = -1;
		while (p1 < u.size()) {
			while (p2 + 1 < d.size() && d.at(p2 + 1) <= u.at(p1)) {
				++p2;
			}
			ret += p2 + 1;
			++p1;
		}
		return ret;
	}
	void calans(ll x, ll pr) {
		clear(x, 0);
		vector<ll> urev, dv;
		for (auto i : e[x]) {
			cli;
			vector<ll> cu, cd;
			dp(i.first, x, i.second, x, cu, cd);
			ans -= doublepointer(cu, cd);
			urev.insert(urev.end(), cu.begin(), cu.end());
			dv.insert(dv.end(), cd.begin(), cd.end());
		}
		urev.empb(0), dv.empb(0);
		ans += doublepointer(urev, dv) - 1;
		clear(x, 0); 
		vis[x] = 1;
		for (ll i : ct[x]) {
			calans(i, x);
		}
	}
}

void precalc();
void init();
int mian(); 

bool memtest2;
#define OFFSYNC
//#define MULTITEST
int main() {
	auto st = clock();
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
//	freopen("err.txt", "w", stderr);
	#ifdef OFFSYNC
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	#endif
	precalc();
	#ifdef MULTITEST
	i32 T;
	cin >> T;
	while (T--) {
		#ifdef DEBUG
		cerr << "-------------------------------\n";
		#endif
		init();
		mian();
	}
	#else
	mian();
	#endif
	auto ed = clock();
	#ifdef DEBUG_USAGE
	cerr << "memory usage: " << abs(&memtest2 - &memtest1) << " Bytes\n";
	cerr << "time usage: " << f64(ed - st) / CLOCKS_PER_SEC * 1000 << " ms\n";
	#endif
	return 0;
}

void precalc() {}
void init() {}
int mian() {
	cin >> n;
	for (ll i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	for (ll i = 1, u, v, w; i < n; ++i) {
		cin >> u >> v >> w;
		e[u].empb(v, w);
		e[v].empb(u, w);
	}
	centree::bdct(1, 0);
	tdv::calans(ctroot, 0);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：lhc0707 (赞：0)

## P5306 [COCI2018-2019#5] Tansport sol

路径 $(u,v)$ 可以拆解成 $(u,\operatorname{lca}(u,v))$，$(\operatorname{lca}(u,v),v)$ 两段路径，两段路径的答案合并可以得到 $(u,v)$ 的答案。对于这种路径合并问题，可以考虑点分治。

### 对于单条路径

这道题中我们分类别来讨论路径。设当前的根是 $rt$，点 $u$ 到 $rt$ 的点权和为 $w_u$，边权和是 $d_u$，父节点为 $fa_u$。

第一种情况是 $u \rightarrow rt$，考虑该路径合法的条件是对于任意路径上的点 $v$ 都有 $d_u-d_v \leq w_u-w_v$，换句话说就是 $u$ 到路径上任意一点时油量都大于等于 0。将上面的式子变形，得到 $w_v-d_v \leq w_u-d_u$，那我们只需要让路径上最大的 $w_v-d_v$ 小于 $w_u-d_u$ 即可满足条件。于是我们只需记 $w_u-d_u$ 的最大值就可以判断点 $u$ 能不能走到 $rt$。

第二种情况 $rt \rightarrow u$ 就有点儿复杂，因为这时货车的起点不一定是 $rt$，如果总路径是 $v \rightarrow rt \rightarrow u$，设 $v \rightarrow rt$ 路径结束后剩余油量为 $x$，则路径 $rt \rightarrow v$ 合法的条件是对于路径上任意一点 $k$，都有 $x+w_{fa_k}-d_k \geq 0$。这里我们可以记 $y=\min \{w_{fa_u}-d_u\}$，则该路径合法的充分必要条件就是 $x+y \geq 0$。

### 合并路径

开两个队列 $q1$ 和 $q2$，其中 $q1$ 记所有合法路径到 $rt$ 时的剩余油量，$q2$ 记所有下行路径的 $\min\{w_{fa_u}-d_u\}$，将两个队列中的元素升序排列，倒序枚举 $q2$,看 $q1$ 中多少值满足下行路径的合法条件。这个可以用双指针做到 $O(N)$ 复杂度。当然，如果我们用这种方法合并路径，会将同一子树内的条件也算上，这需要我们把他们排掉。具体可以看代码。

有一个细节就是我们在合并两条路径的时候，因为这两条路径都算上了 $a_{rt}$，所以我们要利用容斥原理减掉一个 $a_{rt}$。还有就是点分治本来复杂度就不算低，合并路径过程中复杂度当然是越低越保险，所以这里并不推荐用二分的方法平添一个 $\log$。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm> 
#define int long long
using namespace std;
const int N=200005;
int n,a[N],ans;
int head[N],tot;
struct edge{
	int v,w,nxt;
}e[N<<1];
void add(int u,int v,int w)
{
	e[++tot].v=v,e[tot].w=w;
	e[tot].nxt=head[u],head[u]=tot;
}
bool vis[N];
int siz[N],rt,tem,sum;
void find_rt(int u,int fath)
{
	int mx=0;
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(vis[v]||v==fath)continue;
		find_rt(v,u);
		siz[u]+=siz[v];
		mx=max(mx,siz[v]);
	}
	mx=max(mx,sum-siz[u]);
	if(mx<tem)tem=mx,rt=u;
}
int w[N],d[N];
int up[N],down[N],cnt1,cnt2;
void calc_dis(int u,int fath,int mx,int mn)
{
	if(w[u]-d[u]>=mx)up[++cnt1]=w[u]-d[u];
	down[++cnt2]=mn;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(vis[v]||v==fath)continue;
		d[v]=d[u]+e[i].w,w[v]=w[u]+a[v];
		calc_dis(v,u,max(mx,w[u]-d[u]),min(mn,w[u]-d[v]));
	}
} 
int q1[N],q2[N],p1,p2;
inline void calc(int u)
{
	p1=p2=0;
	d[u]=0,w[u]=a[u];
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(vis[v])continue;	
		cnt1=cnt2=0;
		w[v]=w[u]+a[v],d[v]=e[i].w;
		calc_dis(v,u,w[u]-d[u],w[u]-d[v]);
		sort(up+1,up+1+cnt1);
		sort(down+1,down+1+cnt2);
		int l=1;
		for(int i=cnt2;i>=1;i--)
		{
			while(l<=cnt1&&up[l]+down[i]-a[u]<0)l++;
			ans-=cnt1-l+1;
		} 
		for(int i=1;i<=cnt1;i++)q1[++p1]=up[i];
		for(int i=1;i<=cnt2;i++)q2[++p2]=down[i];
	} 
	sort(q1+1,q1+1+p1);
	sort(q2+1,q2+1+p2);
	int l=1;
	for(int i=p2;i>=1;i--)
	{
		if(q2[i]>=0)ans++;
		while(l<=p1&&q1[l]+q2[i]-a[u]<0)l++;
		ans+=p1-l+1;
	}
	ans+=p1;
}
void solve(int u)
{
	vis[u]=true;
	calc(u);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(vis[v])continue;
		sum=siz[v],tem=1000000000;
		find_rt(v,u);
		solve(rt);
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++)
	{
		int u,v,w;cin>>u>>v>>w;
		add(u,v,w);add(v,u,w);
	}
	sum=n,tem=1000000000;
	find_rt(1,0);
	solve(rt);
	cout<<ans<<"\n";
	return 0;
}
```

题解制作不易，望过审 QWQ。

---

## 作者：junee (赞：0)

# P5306 题解

## 前置知识

点分治

## 题目分析

我们考虑把将答案的计算分为两部分 $L_u \rightarrow root$ ，即从下到上和 $R_{root} \rightarrow v$ ，即从上到下。

首先考虑 $L_u \rightarrow rt$ ，由于我们是从根节点开始跑的，所以必须满足自下而上是符合条件的。从 $root$ 节点开始走他的子树，将距离 $dist$ 加上 $-w_i+a_j$ 的值，由于可能出现无法往上走的情况，我们就要与 0 做比较，如果合法就记录油的剩余量，否则不记录。

考虑 $R_{root} \rightarrow v$ ，由于是自上往下走，所以不需要考虑合法性，只需记录从上往下走的所剩余油量最小的那一段，如果满足最小的那一段，那么整条路经就一定是合法的。

最后在计算答案时，将两段路径按升序排列。当 $L_u \rightarrow root \ge R_{root} \rightarrow v$ 时，说明整条路径是合法的，然后减去 $L$ 路径以 $s$ 为起点的方案数。

## Code
```
#include<iostream>
#include<algorithm>
#include<cstring> 
using namespace std;
typedef long long LL;
const int N=1e5+10;
LL st[N];
LL h[N],e[N*2],ne[N*2],idx;
LL w[N*2],a[N*2];
LL n,m,s;
LL l[N],r[N],L[N],R[N],lt,rt;
LL rk[N],lk[N];
LL root;
LL q[N];
bool cmpl(int a,int b){
	return l[a]<l[b];
}
bool cmpr(int a,int b){
	return r[a]<r[b];
}
void add(int a,int b,LL c){
	e[idx]=b,ne[idx]=h[a],w[idx]=c,h[a]=idx++;
}
int get_sz(int u,int f){
	if(st[u])return 0;
	int sz=1;
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		if(j==f)continue;
		sz+=get_sz(j,u);
	}
	return sz;
}
int get_ws(int u,int f,int tot,int &ws){
	if(st[u])return 0;
	int sum=1,ms=0;
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		if(j==f)continue;
		int t=get_ws(j,u,tot,ws);
		sum+=t;
		ms=max(ms,t);
	}
	ms=max(ms,tot-sum);
	if(ms<=tot/2)ws=u;
	return sum;
}
void get_dist(int u,int f,LL dist,LL mx,LL flag){
	if(!flag){
		l[++lt]=dist;
		lk[lt]=s;
	}
	r[++rt]=-mx;
	rk[rt]=s;
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		if(j==f||st[j])continue;
		get_dist(j,u,dist-w[i]+a[j],min(mx,dist-a[root]-w[i]),min(0LL,flag-w[i]+a[j]));
	}
}
int calc(int u){
	if(st[u])return 0;
	get_ws(u,-1,get_sz(u,-1),u);
	int ans=0;
	st[root=u]=1;
	lt=rt=0;
	l[++lt]=a[u],lk[lt]=u;
	r[++rt]=0,rk[rt]=u;
	q[u]=0;
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		if(st[j])continue;
		s=j;
		q[s]=0;
		get_dist(j,u,a[u]+a[j]-w[i],-w[i],min(0LL,a[j]-w[i]));
	}
	for(int i=1;i<=lt;i++)L[i]=i;
	for(int i=1;i<=rt;i++)R[i]=i;
	sort(R+1,R+1+rt,cmpr);
	sort(L+1,L+1+lt,cmpl);
	int j=1;
	for(int i=1;i<=lt;i++){
		while(j<=rt&&l[L[i]]>=r[R[j]])q[rk[R[j]]]++,j++;
		ans+=(j-1)-q[lk[L[i]]];
	}
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		ans+=calc(j);
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	memset(h,-1,sizeof h);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++){
		int a,b;
		LL c;
		cin>>a>>b>>c;
		add(a,b,c);
		add(b,a,c);
	}
	cout<<calc(1);
    return 0;
}

```

---

## 作者：Judgelight (赞：0)

[传送门](https://www.luogu.com.cn/problem/P5306)

---

首先一眼看上去就非常点分治，考虑如何维护合法路径。

不妨设当前讨论的路径是 $v_1\rightarrow u\rightarrow v_2$，考虑拆分成 $v_1\rightarrow u$ 和 $u\rightarrow v_2$ 两个部分，那么可以算出第二部分的一个值 $lst$ 表示进入这条路径时至少拥有 $lst$ 的油才可以安全通过，显然这个 $lst$ 是可以维护的。那么假设我们走完路径的第一部分时剩下了 $x$ 升油，则满足 $lst\le x$ 的路径会对答案贡献 $1$。注意需要对第一部分的路径也统计一个 $lst$，只有当 $lst=0$ 时才进行答案的计算。

所以就变成了一个区间查询单点加的问题，由于值域比较大所以使用动态开点线段树进行统计，时间复杂度为 $O(n\log^2n)$。（其实可以直接双指针，但是为了方便就用了线段树）。

---

## 作者：rainygame (赞：0)

为啥没有边分治的题解呀？

这道题是点分治板子题，而点分治可以做的题边分治大多都可以做。

我们先回顾一下点分治是怎么做的？

1. 找到重心。

2. 统计经过重心的合法路径数量。

3. 将树按重心分为几颗子树，递归解决子问题。

而树分治中还有一种“边分治”，它和点分治差不多：

1. 找到一条边使得两端的子树大小之差尽量小。

2. 统计经过这条边的合法路径数量。

3. 将树分为两颗子树，递归地解决子问题。

边分治的优势：

- 点分治是多颗子树合并，有时候需要用到一些 DS 来维护，复杂度可能多若干个 $\log$。而且合并的逻辑可能会很麻烦。边分治是两颗子树合并，比起点分治相对简单。

- 点分治中关于“到达”重心、“通过”重心之类的分裂讨论可能比较繁杂，但是边分治就清晰很多。

但是边分治的复杂度是假的，具体到一个菊花图上，我们发现复杂度退化成了 $O(n^2)$。所以需要把图先进行“三度化”，具体地，对于每一个儿子数量大于 $2$ 的结点，我们将它的儿子分为两个大小差最多为 $1$ 的集合中，并建立两个虚点，类似线段树一样分别连接这两个集合内的所有点，最后再和原来的结点连接。最后整棵树就变成了一颗大小不会超过 $2n$ 的二叉树，这样复杂度就不会假了，但是常数会大一些。而且设置虚点和虚边的边权有时也是比较麻烦的（比如这道题）。这就是边分治唯一美中不足的地方了。

**本题解的代码没有进行“三度化”，希望大家不要 hack 我。**

关于边分治的一些前置知识讲完了，让我们看看这道题。

递归解决子问题是简单的。我们思考怎么解决通过重边的路径个数。设重边的两个端点分别为 $u, v$，边权为 $w$。设 $V(u \rightarrow v)$ 表示 $u$ 到 $v$ 路径的点权和，$E(u \rightarrow v)$ 表示 $u$ 到 $v$ 路径的边权和。

那么先考虑路径从 $u$ 到 $v$ 的情况。设合法路径的两个端点分别为 $s,t$，$s$ 在 $u$ 的子树内，$t$ 在 $v$ 的子树内。 

那么首先就是要保证 $s\rightarrow v$ 的路上没有一次油不够的情况。如果 $s$ 在 $u$ 的子树内有一个祖先 $x$，使得 $V(x\rightarrow v)-E(x \rightarrow v)>V(s\rightarrow v)-E(s \rightarrow v)$，那么就表示有油不够的情况出现，否则表示没有。因为这样就表示存在一个 $s \rightarrow x$ 路径上的结点使得 $s$ 到那个结点的油量为负。对 $u$ 的子树搜索结束之后，我们把所有可作为起点的结点 $s$ 的 $V(s\rightarrow v)-E(s \rightarrow v)$ 放进一个集合 $A$ 中。

再考虑 $v \rightarrow t$ 的路径，因为我们不知道 $s \rightarrow v$ 的剩余油量，所以默认所有的 $t$ 都是可行的，那么显然地，$v \rightarrow t$ 最大的困难就是路径上最大的边权和减去点权和，所以我们对于所有的 $t$，把 $v\rightarrow t$ 中最大的边权和减去点权和存在 $B$ 中即可。

然后就是对于每个 $A_i$ 找到有多少个 $j$ 满足 $A_i \ge B_j$，双指针维护即可，找到后直接加入答案。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 100001

int n, u, v, w, minn, sum, zb, ans;
int a[MAXN], siz[MAXN];
vector<int> vec1, vec2;
bitset<MAXN> vis;

struct Edge{int id, v, w;};
vector<Edge> e[MAXN];

struct edge{int u, v, w;}edges[MAXN];

void dfs1(int x, int fa){
    siz[x] = 1;
    for (auto i: e[x]){
        int v(i.v);
        if (v != fa && !vis.test(i.id)){
            dfs1(v, x);
            siz[x] += siz[v];
            int tmp(max(siz[v], sum-siz[v]));
            if (tmp < minn){
                minn = tmp;
                zb = i.id;
            }
        }
    }
}

void dfs2(int x, int fa, int w, int d, int maxn){
    if (w-d >= maxn){
        maxn = w-d;
        vec1.push_back(maxn);
    }

    for (auto i: e[x]){
        int v(i.v);
        if (v != fa && !vis.test(i.id)) dfs2(v, x, w+a[v], d+i.w, maxn);
    }
}

void dfs3(int x, int fa, int w, int d, int maxn){
    maxn = max(maxn, d-w);
    vec2.push_back(maxn);
    for (auto i: e[x]){
        int v(i.v);
        if (v != fa && !vis.test(i.id)) dfs3(v, x, w+a[x], d+i.w, maxn);
    }
}

void calc(int u, int v, int w){
    vec1.clear();
    dfs2(u, v, a[u], w, 0);
    sort(vec1.begin(), vec1.end());
    vec2.clear();
    dfs3(v, u, 0, 0, 0);
    sort(vec2.begin(), vec2.end());

    int l(0);
    for (int i(0); i<vec1.size(); ++i){
        while (l < vec2.size() && vec2[l] <= vec1[i]) ++l;
        ans += l;
    }
}

void solve(int x, int sz){
    if (sz == 1) return;
    sum = minn = sz;
    dfs1(x, 0);
    vis.set(zb);
    int u(edges[zb].u), v(edges[zb].v);
    calc(u, v, edges[zb].w);
    calc(v, u, edges[zb].w);
    if (siz[v] < siz[u]) swap(u, v);
    solve(v, sz-siz[u]);
    solve(u, siz[u]);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i(1); i<=n; ++i) cin >> a[i];
    for (int i(1); i<n; ++i){
        cin >> u >> v >> w;
        e[u].push_back({i, v, w});
        e[v].push_back({i, u, w});
        edges[i] = {u, v, w};
    }
    solve(1, n);

    cout << ans;

    return 0;
}

```

这道题还不太能体现出边分治的优势，因此再给一道[例题](https://vjudge.net/problem/%E9%BB%91%E6%9A%97%E7%88%86%E7%82%B8-2870)。

---

## 作者：chen_qian (赞：0)

一个大常数写法，但是就是纯DS，没有思维难度。

解法：题目上要求一直有油用，假设我们经过的点是 $p_1,p_2 \dots p_{k+1}$，走过的边是 $l_1,l_2 \dots ,l_k$。那么题目可以转化成对于任意的 $i \in [1,k]$，满足：

$$ \sum_{j=1}^i a_{p_i}- \sum_{j=1}^i w_{l_i}\ge 0$$

恒成立。也就是：

$$ \min_{i=1}^k{\sum_{j=1}^i a_{p_i}- \sum_{j=1}^i w_{l_i}}\ge 0$$

成立。

考虑点分治，对于当前的分治中心 $x$ ，记录 $\text{minn} _ i$ 表示 $x$ 走到 $i$ 的路径上出现过的最缺油的时候。那么对于 $\text{minn} _ i \ge 0$ 的点，那么答案就是之前的遍历到的点中能够走到 $x$ 的点，至于怎么求这些点，之后再说。否则，我们就只能与之前那些走到 $x$ 点之后剩余油量 $\text{left} \ge -minn_i$ 的点的数量，这相当于区间数点的数量，可以用值域线段树来计算。

然后在考虑这颗子树加入到线段树中，同样还是记录 记录 $\text{minn} _ i$ 表示 $i$ 走到 $x$ 的路径上出现过的最缺油的时候。要求 $\text{minn} _ i \ge 0$ ，其才能成为候选点，然后将其加入到值域线段树中。其实平衡树也是可以的，常数大概比线段树小。

然后倒着来一边，再计算一个端点为 $x$ 的点对数量。时间复杂度是 $O(n\log{n}\log{v})$。平衡树就是 $O(n\log^2{n})$ 。需要垃圾回收。

```
#include<bits/stdc++.h>
#define N 100005
#define INF 1e14
#define pb push_back 
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second  
#define int long long  
using namespace std;
int rt,cnt,sum[N<<5],ls[N<<5],rs[N<<5];
int rubbish[N<<3],rub;
int newnode(){
	if(rub) return rubbish[rub--];
	return ++cnt;
}
void destory(int &x){
	ls[x]=rs[x]=sum[x]=0;
	rubbish[++rub]=x;
	x=0;
}
void modify(int &p,int l,int r,int x,int v){
	if(!p) p=newnode();
	if(l==r){
		sum[p]+=v;
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid) modify(ls[p],l,mid,x,v);
	else modify(rs[p],mid+1,r,x,v);
	sum[p]=sum[ls[p]]+sum[rs[p]];
}
int query(int p,int l,int r,int ql,int qr){
	if(!p) return 0;
	if(ql<=l&&qr>=r) return sum[p];
	int mid=(l+r)>>1,res=0;
	if(ql<=mid) res+=query(ls[p],l,mid,ql,qr);
	if(qr>mid) res+=query(rs[p],mid+1,r,ql,qr); 
	return res;
}
void clear(int &p,int l,int r){
	if(!p) return ;
	if(l==r){
		destory(p);
		return ;
	}
	int mid=(l+r)>>1;
	clear(ls[p],l,mid);
	clear(rs[p],mid+1,r);
	destory(p);
}
int n,m;
int a[N];
vector<pii > e[N];
bool vis[N];
int ans=0,len=0;
int maxn[N],tot,size[N],root;
void getroot(int x,int f){
	size[x]=1;
	maxn[x]=1;
	for(int i=0;i<e[x].size();i++){
		int y=e[x][i].fi;
		if(y==f||vis[y]) continue;
		getroot(y,x);
		size[x]+=size[y];
		maxn[x]=max(maxn[x],size[y]); 
	}
	maxn[x]=max(maxn[x],tot-size[x]);
	if(maxn[x]<maxn[root]) root=x;
}
int sumw1[N],suma1[N],minn1[N],sumw2[N],suma2[N],minn2[N];
vector<int> v1[N],v2[N];
void dfs1(int x,int f,int id){
	v1[id].pb(x);
	for(int i=0;i<e[x].size();i++){
		int y=e[x][i].fi,z=e[x][i].se;
		if(y==f||vis[y]) continue;
		sumw1[y]=sumw1[x]+z;
		suma1[y]=suma1[x]+a[x];
		minn1[y]=min(minn1[x],suma1[y]-sumw1[y]);//求最小
		dfs1(y,x,id);
	}
}
void dfs2(int x,int f,int id){
	if(minn2[x]>=0) v2[id].pb(x); 
	for(int i=0;i<e[x].size();i++){
		int y=e[x][i].fi,z=e[x][i].se;
		if(y==f||vis[y]) continue;
		minn2[y]=min(minn2[x]+a[y]-z,a[y]-z);//求最小
		suma2[y]=suma2[x]+a[y];
		sumw2[y]=sumw2[x]+z;
		dfs2(y,x,id);
	}
}
void solve(int x){//这个方法常熟真的很大，所以不要每次计算都遍历子树，记录下来。
	if(!x) return ;
	for(int i=0;i<e[x].size();i++){
		int y=e[x][i].fi,z=e[x][i].se;
		if(vis[y]) continue;
		v1[i].clear();
		minn1[y]=a[x]-z;
		suma1[y]=a[x];
		sumw1[y]=z;
		dfs1(y,x,i);
		for(int j=0;j<v1[i].size();j++){
			int t=v1[i][j];
			if(minn1[t]>=0) ans+=sum[rt];
			else ans+=query(rt,0,INF,-minn1[t],INF);
		}
		minn2[y]=a[y]-z;
		suma2[y]=a[y];
		sumw2[y]=z;
		v2[i].clear();
		dfs2(y,x,i);
		for(int j=0;j<v2[i].size();j++){
			int t=v2[i][j];
			modify(rt,0,INF,suma2[t]-sumw2[t],1);
		}
	}
	clear(rt,0,INF);
	for(int i=e[x].size()-1;i>=0;i--){
		int y=e[x][i].fi,z=e[x][i].se;
		if(vis[y]) continue;
		for(int j=0;j<v1[i].size();j++){
			int t=v1[i][j];
			if(minn1[t]>=0) ans+=sum[rt];
			else ans+=query(rt,0,INF,-minn1[t],INF);
		}
		for(int j=0;j<v2[i].size();j++){
			int t=v2[i][j];
			modify(rt,0,INF,suma2[t]-sumw2[t],1);
		}
	}
	clear(rt,0,INF);
	for(int i=0;i<e[x].size();i++){
		int y=e[x][i].fi,z=e[x][i].se;
		if(vis[y]) continue;
		for(int j=0;j<v1[i].size();j++){
			int t=v1[i][j];
			if(minn1[t]>=0) ans++;
		}
		ans+=v2[i].size();
	}
} 
void divide(int x){
	vis[x]=1;
	solve(x);
	for(int i=0;i<e[x].size();i++){
		int y=e[x][i].fi;
		if(vis[y]) continue;
		maxn[0]=tot=size[y];
		root=0;
		getroot(y,x);
		divide(root);
	}
}
signed main(){
	//freopen("data.in","r",stdin);
	//freopen("my.out","w",stdout);
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<n;i++){
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		e[u].pb(mp(v,w));
		e[v].pb(mp(u,w));
	}
	maxn[0]=tot=n,root=0;
	getroot(1,0);
	divide(root);
	printf("%lld\n",ans);
	return 0;
}
/*
4
4 3 3 3 
4 3 4
2 1 3
4 1 4
*/
```


---

