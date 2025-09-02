# Double Sort II

## 题目描述

You are given two permutations $ a $ and $ b $ , both of size $ n $ . A permutation of size $ n $ is an array of $ n $ elements, where each integer from $ 1 $ to $ n $ appears exactly once. The elements in each permutation are indexed from $ 1 $ to $ n $ .

You can perform the following operation any number of times:

- choose an integer $ i $ from $ 1 $ to $ n $ ;
- let $ x $ be the integer such that $ a_x = i $ . Swap $ a_i $ with $ a_x $ ;
- let $ y $ be the integer such that $ b_y = i $ . Swap $ b_i $ with $ b_y $ .

Your goal is to make both permutations sorted in ascending order (i. e. the conditions $ a_1 < a_2 < \dots < a_n $ and $ b_1 < b_2 < \dots < b_n $ must be satisfied) using minimum number of operations. Note that both permutations must be sorted after you perform the sequence of operations you have chosen.

## 样例 #1

### 输入

```
5
1 3 2 4 5
2 1 3 4 5```

### 输出

```
1
2```

## 样例 #2

### 输入

```
2
1 2
1 2```

### 输出

```
0```

## 样例 #3

### 输入

```
4
1 3 4 2
4 3 2 1```

### 输出

```
2
3 4```

# 题解

## 作者：Lgx_Q (赞：9)

题意：两个排列 $a,b$，每次选择一个 $i$，把两个排列中等于 $i$ 的数与 $a_i,b_i$ 交换，求把两个排列排好序的最小操作次数。

分析：

套路化，把两个排列看成两张图，第一张图中 $i$ 向 $a_i$ 连边，第二张图中 $i$ 向 $b_i$ 连边。

简化问题，如果只有一张图？

显然，答案为 ```n - 环的个数```。每次操作相当于把一个点搞自环，其所在的环的点的个数减一，最后剩下那个点不用操作。即：每个环都可以有一个不会被操作的点， $n$ 个点中一共有 ```环的个数``` 个点不会被操作。

两个环呢？我们使用类似的思想，选出一些不操作的点。但有个条件：每个环最多选 $1$ 个点。

假设有一个点 $i$，在第一张图中处于第 $ca_i$ 个环，第二张图中处于第 $cb_i$ 个环，如果选择 $i$，那么这两个环就不能选择其他的点。

这就有点像二分图匹配了，第一张图的每个环和第二张图的每个环匹配，一个环最多有 $1$ 条匹配边。

于是枚举每个点 $i$，把 $ca_i$ 和 $cb_i$ 连边，跑匈牙利，最大匹配就是选出最多的不操作的点。

用 $n$ 减去 ```最大匹配数``` 即可，输出的方案应是除了选择的点的剩下那些点。

对于枚举的每个点 $i$，最多建立一条边（因为还会有重边），最多建立 $n$ 条边，所以匈牙利的时间是平方级别的，总体时间复杂度为 $O(n^2)$

[**code**](https://codeforces.com/contest/1783/submission/188829624)

---

## 作者：DaiRuiChen007 (赞：4)

# CF1783F 题解



## 思路分析

先考虑只对 $a$ 排序的最小花费，显然连接 $i\to a_i$ 建图，对于图中的每一个大小为 $|\mathbf C|$ 的置换环，根据复原置换的结论，我们需要 $|\mathbf C|-1$ 次操作把这个环复原，设 $cyc$ 为图中环的数量，答案为 $n-cyc$，我们可以理解为每个在每个环中选出一个 $x$ 不操作。

接下来考虑同时对 $a$ 和 $b$ 排序，类似上面，对于 $a,b$ 中的每个环，分别选出一个 $x$ 不操作，我们称 $x$ 为这个环的“代表”。

注意到只有 $x$ 同时是 $a$ 中所属环和 $b$ 中所属环的“代表”，我们才可以不操作 $x$。

因此把 $a$ 中的每个环看成左部点，$v$ 中的每个环看成其右部点，每个位置 $i$ 看成一条连接 $i$ 在 $a$ 中所属环和在 $b$ 中所属环的一条边，得到一张二分图，二分图的每条匹配边对应选择相应的 $x$ 作为其在两边所在的环的“代表”然后跳过对 $x$ 的操作。

设其最大匹配大小为 $|\mathbf M|$，那么答案为 $n-|\mathbf M|$，求出匹配方案输出即可。

时间复杂度 $\Theta(n^2)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=3001;
vector <int> G[MAXN];
int a[MAXN],b[MAXN],ia[MAXN],ib[MAXN],tar[MAXN];
bool vis[MAXN];
inline bool dfs(int x) {
	for(int p:G[x]) {
		if(vis[p]) continue;
		vis[p]=true;
		if(tar[p]==-1||dfs(tar[p])) {
			tar[p]=x;
			return true;
		}
	}
	return false;
}
signed main() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	memset(vis,false,sizeof(vis));
	for(int tot=0,i=1;i<=n;++i) {
		if(ia[i]) continue;
		++tot;
		while(!vis[i]) {
			vis[i]=true,ia[i]=tot;
			i=a[i];
		}
	}
	for(int i=1;i<=n;++i) scanf("%d",&b[i]);
	memset(vis,false,sizeof(vis));
	for(int tot=0,i=1;i<=n;++i) {
		if(ib[i]) continue;
		++tot;
		while(!vis[i]) {
			vis[i]=true,ib[i]=tot;
			i=b[i];
		}
	}
	memset(tar,-1,sizeof(tar));
	for(int i=1;i<=n;++i) G[ia[i]].push_back(ib[i]);
	int tot=n;
	for(int i=1;i<=n;++i) {
		memset(vis,false,sizeof(vis));
		if(dfs(i)) --tot;
	}
	printf("%d\n",tot);
	for(int i=1;i<=n;++i) {
		if(tar[ib[i]]==ia[i]) tar[ib[i]]=-1;
		else printf("%d ",i);
	}
	puts("");
	return 0;
}
```

---

## 作者：zac2010 (赞：2)

以下是自己的题解以及自己的做题经过。其中读者的重点在于**第二、四部分**，第一、三部分可凭个人喜好已确定是否阅读。

### 思路历程

下面是自己没做出来的原因。

1. 贪心

   似乎感觉没法贪，且感觉反悔贪心也没有策略

2. 按一定顺序模拟

   因为考虑按一定顺序归位，比如说先把 $a,b$ 的第一位都通过操作变为 $1$ ，但是考虑可能后面的什么通过交换归位了再和前面的换就一举两得，所以可能由于当前。

3. 动态规划

	 $dp[i]$ 表示把前 $i$ 个数归位的最小答案，但有可能有 $2$ 中说的情况，所以没法转移。

### 题解思路

首先我们简化问题：假设只要一个数组。

我们把 $i$ 向 $a_i$ 连边，这样得到了一个由环组成的有向图。

那么思考，如果我们要每一步都会使得一个点从环中删除，以连向自己。那么最后环中剩下的点就不用操作了。所以一个数组的操作次数是 $n$ 减环的个数。

接下来考虑两个是数组。因为每一步操作都可以使两个数组中的 $i$ 位置变成指定数值。那么当两个环剩下的元素相同那么是可以省掉操作对的这 $1$ 次的。

所以我们把每个环看成一个点，拥有相同颜色的环连边。由于每个环中只有剩下的一个点是可能省掉 $1$ 步的，所以我们跑二分图的最大匹配。而匹配出来的就是可以省掉的次数。所以答案就是 $n$ 减最大匹配数。

至于输出方案，我们要知道：有了我们的模型转换之后不管什么顺序都没有问题。所以我们只需要枚举每个 $i$ （因为前面的连边方案是把拥有编号相同的两个点的环所代表的点连边），看看这条边是否被匹配就行了，如果匹配了，那么就证明这个点没有被选并且操作过，不输出；否则输出 $i$ 。

时间复杂度 $O(n^2)$ ，在于求解二分图的最大匹配的匈牙利算法。

### 分析原因

以下是自己分析的没做出来的原因。

1. 没想出建图方式

   缺乏这样套路性的思维。在一个**排列**中 $i$ 向 $a_i$ 或者 $a_i$ 向 $i$ 连边的这种建图方式非常常见。

2. 知道了建图方式之后没有想到性质

   像这道题的一个性质需要简化问题，从只有一个数组开始。然后根据题目的两个数组选的都是 $i$ 这点去确定建图方式，而最后的得出是二分图的结论就比较显而易见。

### 代码

```cpp
#include <bits/stdc++.h>
#define L(i, a, b) for(int i = a; i <= b; i++)
#define R(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 3010;
int n, cnt, tota, totb, p[N], vis[N];
int a[N], b[N], t[N], ca[N], cb[N], mp[N][N];
vector<int> g[N];
void Get(int u, int col, int e[], int c[]){//获取每个点所处环的标号
	c[u] = col;
	if(!c[e[u]]) Get(e[u], col, e, c);
}
bool Dfs(int u){//二分图的最大匹配
	for(int v: g[u]){
		if(!vis[v]){
			vis[v] = 1; 
			if(!p[v] || Dfs(p[v])){
				p[v] = u;
				return 1;
			}
		} 
	}
	return 0;
}
int main(){
	scanf("%d", &n);
	L(i, 1, n) scanf("%d", &a[i]); 
	L(i, 1, n) scanf("%d", &b[i]);
	L(i, 1, n){
		if(!ca[i]) Get(i, ++tota, a, ca);
		if(!cb[i]) Get(i, ++totb, b, cb);
	}
	L(i, 1, n)
		if(!mp[ca[i]][cb[i]])
			mp[ca[i]][cb[i]] = i, g[ca[i]].push_back(cb[i]);//拥有相同节点的环连边
	L(i, 1, tota){
		L(j, 1, totb) vis[j] = 0;
		cnt += Dfs(i);
	}
	printf("%d\n", n - cnt);
	L(i, 1, totb)
		if(p[i]) t[mp[p[i]][i]] = 1;
	L(i, 1, n)
		if(!t[i]) printf("%d ", i);
	return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：2)

由于场上花了一个小时写 E 的谔谔行为导致没有时间思考 F。实际上这是一道简单题。

两个排列太烦了，我们先只看一个排列 $a_i$ 吧。建出含有置换环的图：$i$ 向 $a_i$ 连边。一个长度为 $n$ 的排列有序的充要条件是其对应 $n$ 个自环。

一次操作中我们选择了一个数 $i$，令 $a_x=i$ 交换 $a_x$ 和 $a_i$。这个操作的本质是什么？把 $a_i$ 归位形成自环，在含有 $x$ 和 $i$ 的置换环中切掉 $i$，并把剩下的部分顺次连接起来。这个过程自己模拟一下样例就明白了，画图解释有点烦。

由此我们可以发现如果我们把 $i\in [1,n]$ 都操作一次，那么两个排列自然都能有序，所以操作上界不超过 $n$ 次。进一步的，每个置换环中最后剩余的一个点可以不用操作，因为它已经形成自环了。那我们不妨从反面来考虑：哪些操作是不必要的？

再回到置换环中，我们把每个排列中的置换环看成一个集合。以排列 $a_i$ 举例，假设有 $c$ 个置换环，则存在集合 $A_1,A_2,\cdots A_c$，每个集合对应在它这个环中的所有点，也就是 $\bigcup_{i=1}^{n}A_i=\{1,2,\cdots n\},\bigcap_{i=1}^{n}A_i=\emptyset$。$B_i$ 同理。

如果我们省略掉的操作点的集合 $S=\{p_1,p_2\cdots p_m\}$，那么需要保证这 $m$ 个点中的任意两点在任意一张图中都不能存在于同一个置换环中，也就是说每个 $A_i$ 和 $B_i$ 里最多取出一个元素（或者不取）。

根据经验这应当是一道网络流题。剩下的事情就简单了：建立源点 $S$ 和汇点 $T$，$S$ 向 $A_i$ 连边，$B_i$ 向 $T$ 连边，$A_i$ 向它所含的所有数字连边，所有数字向它所属的集合 $B_i$ 连边。以上所有边的容量均为 $1$。用你想用的网络流算法跑出 $S$ 和 $T$ 直接的最大流 $f$，答案即为 $n-f$。至于点 $x$ 是否在省略的集合中？直接看指向点 $x$ 的边 $(A_i,x)$ 是否满流即可。

边数点数均为 $\mathcal{O}(n)$，时间复杂度是 $\mathcal{O}(n\sqrt n)$。

代码：

```cpp
//114
#include <bits/stdc++.h>
const int M = 30114, inf = 114114;
int n, a[3005], b[3005], fa[3005], S, T, cnt = 0;
int tot = 1, ver[M], nxt[M], len[M], head[M];
int myf = 0, ok[3005], pre[M];
inline void adde(int x, int y){
	nxt[++tot] = head[x];
	head[x] = tot;
	ver[tot] = y;
	len[tot] = 1;
	nxt[++tot] = head[y];
	head[y] = tot;
	ver[tot] = x;
	len[tot] = 0;
	return ;
} 
std::vector <int> sa[3005], sb[3005];
int fd(int x){
	return x == fa[x] ? x : fa[x] = fd(fa[x]);
}
void merge(int x, int y){
	x = fd(x);
	y = fd(y);
	fa[y] = x;
	return ;
}
int d[M];
bool bfs(){
	std::queue <int> q;
	memset(d, 0, sizeof d);
	for(int i = 1; i <= 3 * n; ++i) pre[i] = head[i];
	pre[S] = head[S];
	pre[T] = head[T];
	d[S] = 1; q.push(S);
	while(q.size()){
		int u = q.front(); q.pop();
		for(int i = head[u]; i; i = nxt[i]){
			int x = ver[i];
			if(d[x] || !len[i]) continue;
			d[x] = d[u] + 1;
			q.push(x);
		}
	}
	return d[T];
}
int dinic(int x, int rest){
	if(x == T || !rest) return rest;
	int tmp = rest;
	for(int i = pre[x]; i; i = nxt[i], pre[x] = i){
		if(!tmp) break;
		int v = ver[i];
		if(d[v] != d[x] + 1 || !len[i]) continue;
		int k = dinic(v, std::min(tmp, len[i]));
		if(!k) d[v] = 0;
		tmp -= k;
		len[i] -= k;
		len[i ^ 1] += k;
	}
	return rest - tmp;
}
void solve(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for(int i = 1; i <= n; ++i) scanf("%d", &b[i]);
	for(int i = 1; i <= n; ++i) fa[i] = i;
	for(int i = 1; i <= n; ++i) merge(i, a[i]);
	for(int i = 1; i <= n; ++i) sa[fd(i)].push_back(i);
	for(int i = 1; i <= n; ++i) fa[i] = i;
	for(int i = 1; i <= n; ++i) merge(i, b[i]);
	for(int i = 1; i <= n; ++i) sb[fd(i)].push_back(i);
	S = 30001, T = 30002;
	for(int i = 1; i <= n; ++i) adde(S, i);
	for(int i = 1; i <= n; ++i) adde(2 * n + i, T);
	for(int i = 1; i <= n; ++i)
		for(auto j : sa[i]) 
			adde(i, n + j);
	for(int i = 1; i <= n; ++i)
		for(auto j : sb[i])
			adde(n + j, 2 * n + i);
	int ff = 0;
	while(bfs()) while(ff = dinic(S, inf)) myf += ff;
	printf("%d\n", n - myf);
	for(int i = 1; i <= n; ++i)
		for(int j = head[i]; j; j = nxt[j])
			if(len[j] == 0 && ver[j] != S)
				ok[ver[j] - n] = 1;
	for(int i = 1; i <= n; ++i) if(!ok[i]) printf("%d ", i);
	printf("\n");
	return ;
}
int main(){
	int T = 1;
	while(T--) solve();
	return 0;
}
```


---

## 作者：shinkuu (赞：1)

好像是一种不一样的建模方法。

首先我们会做只有 $a$ 的情况：每个 $i\to a_i$ 连边，答案即为 $n-cntc$，其中 $cntc$ 为环的个数。

考虑加上 $b$ 后怎么做。考虑补集转化，每个环内可以选一个数，不去操作它，只操作其他的，它也可以自动归位。此时问题就变成：给你一个长度为 $n$ 的 $01$ 序列和 $m$ 个性质，形如集合 $S$ 中每个位置，其中最多只能有一个 $1$。

正常做是困难的，但是发现这些的集合相当于分成了两组（$a$ 产生的集合和 $b$ 产生的），每组中的集合交集为空，并集为全部位置。则可以如下网络流建模：

设 $a$ 产生的集合为 $S_i$，$b$ 产生的为 $T_j$，源点为 $s$，汇点为 $t$。

- $\forall i$，连 $s\to S_i$。
- $\forall x\in S_i$，连 $S_i\to x$。
- $\forall j$，连 $T_j\to t$。
- $\forall y\in T_j$，连 $y\to T_j$。

（上面的表达可能不够严谨，看懂就行）

流量均为 $1$。答案即为 $n-maxflow$。这是一个单位容量的图，所以 dinic 的复杂度大致是 $O(n\sqrt n)$ 的，可以通过。

输出方案直接在残量网络上找起点为 $i$ 的边（容易发现只有一条）检查流量是否为 $0$ 即可。

code：

```cpp
int n,m,dis[N],cur[N],a[N],b[N];
bool vis[N];
static int S,T;
int tot=1,head[N];
struct node{int to,nxt,fl;}e[N<<2];
vector<int> g;
il void add(int u,int v,int f){
	e[++tot]={v,head[u],f},head[u]=tot;
	e[++tot]={u,head[v],0},head[v]=tot;
}
bool bfs(){
	mems(dis,0),memcpy(cur,head,sizeof head);
	queue<int> q;
	dis[S]=1,q.push(S);
	while(q.size()){
		int u=q.front();q.pop();
		go(i,u){
			int v=e[i].to;
			if(dis[v]||!e[i].fl)continue;
			dis[v]=dis[u]+1;
			q.push(v);
		}
	}
	return dis[T];
}
int dfs(int u,int f){
	if(u==T)return f;
	int s=0;
	for(int &i=cur[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(dis[v]!=dis[u]+1||!e[i].fl)continue;
		int l=dfs(v,min(e[i].fl,f-s));
		s+=l;
		e[i].fl-=l,e[i^1].fl+=l;
		if(s==f)break;
	}
	return s;
}
int dinic(){
	int ret=0;
	while(bfs())ret+=dfs(S,inf);
	return ret;
}
void Yorushika(){
	scanf("%d",&n),m=n;
	rep(i,1,n)scanf("%d",&a[i]);
	rep(i,1,n)scanf("%d",&b[i]);
	S=3*n+1,T=S+1;
	rep(i,1,n){
		if(vis[i])continue;
		int u=a[i];g.clear();
		while(u!=i)g.eb(u),vis[u]=1,u=a[u];
		g.eb(u),vis[u]=1,m++;
		add(S,m,1);
		for(int j:g)add(m,j,1);
	}
	mems(vis,false);
	rep(i,1,n){
		if(vis[i])continue;
		int u=b[i];g.clear();
		while(u!=i)g.eb(u),vis[u]=1,u=b[u];
		g.eb(u),vis[u]=1,m++;
		add(m,T,1);
		for(int j:g)add(j,m,1);
	}
	printf("%d\n",n-dinic());
	for(int i=2;i<=tot;i+=2){
		int u=e[i].to;
		if(u<=n&&e[i].fl)printf("%d ",u);
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：__Louis__ (赞：0)

## 题解：CF1783F Double Sort II

### 题目大意

有两个排列 $A,B$，问至少要进行多少次操作，可以把 $A,B$ 排好序。

操作的方式是：选择一个数，把两个序列中 $i$ 和 第 $i$ 个数交换。

同时，输出一种选数字的方案。

### 思路

很明显，对于一个排列，操作会使其形成一些环。设某一个环的大小为 $siz$，那么我们只需要选 $siz-1$ 个点就可以了。

然后，考虑如何使两个序列一起做更优。

首先，用并查集找出全部的环，然后求单独做需要的次数 $sum$。

对于每一个环生成一个节点，加入源汇点到每一个环的边，权值为 $siz-1$ 表示只需要选 $siz-1$ 种。

然后，把每一个环连到对应的节点上，权值为 $1$。

就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/4d5sl4dm.png)

这个是针对样例


```cpp
4
1 3 4 2
4 3 2 1
```

所建的图。

这个流网络中的最大流 $flow$ 表示可以产生两个序列一起做的最多的个数。第一行的答案就是 $sum-flow$。

最终根据网络流给出的最大流输出答案。

### code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f
const int maxn=1e6+10;
const int maxv=1e4+10;
int head[maxn],w[maxn],to[maxn],nxt[maxn],cnt=1;
int n,m,s,t;
void add_edge(int u,int v,int da){
	to[++cnt]=v;
	w[cnt]=da;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
int fa[maxv],siz1[maxv],siz[maxv],fa1[maxv];
void init(){
	for(int i=1;i<=n;i++){
		fa[i]=i;
		siz[i]=0;
	}
}
int find_fa(int x){
	if(fa[x]==x) return x;
	else return fa[x]=find_fa(fa[x]);
}
int find_fa1(int x){
	if(fa1[x]==x) return x;
	else return fa1[x]=find_fa1(fa1[x]);
}
int cur[maxn],dis[maxn];
bool bfs(int begin,int end){
	queue<int> q;
	memset(dis,-1,sizeof(dis));
	dis[begin]=0,cur[begin]=head[begin];
	q.push(begin);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=nxt[i]){
			int v=to[i];
			if(dis[v]==-1&&w[i]>0){
				dis[v]=dis[u]+1;
				cur[v]=head[v];
				q.push(v);
				if(v==end) return true;
			} 
		}
	}
	return false;
}
int find(int u,int lim,int end){
	if(u==end) return lim;
	int sum=0;
	for(int i=cur[u];i&&sum<lim;i=nxt[i]){
		cur[u]=i;
		int v=to[i];
		if(dis[v]==dis[u]+1&&w[i]>0){
			int flow=find(v,min(w[i],lim-sum),end);
			if(!flow) dis[v]=-1;
			w[i]-=flow,w[i^1]+=flow;
			sum+=flow;
		}
	}
	return sum;
}
int dinic(int begin,int end){
	int ans=0,sum;
	while(bfs(begin,end))
		while(sum=find(begin,inf,end))
			ans+=sum;
	return ans;
}
unordered_map<int,int> ma;

signed main(){
	int sum=0,m1;
	s=9501,t=9500;
	scanf("%lld",&n);
	init();
	int a;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a);
		int p=find_fa(a);
		fa[i]=p;
	}
	for(int i=1;i<=n;i++){
		int p=find_fa(i);
		siz[p]++;
	}
	for(int i=1;i<=n;i++){
		int p=find_fa(i);
		if(!ma.count(p)){
			ma[p]=++m;
			add_edge(s,m+n,siz[p]-1);
			add_edge(m+n,s,0);
			sum+=(siz[p]-1);
		}
		add_edge(ma[p]+n,i,1);
		add_edge(i,ma[p]+n,0);
	}
	for(int i=1;i<=n;i++){
		fa1[i]=fa[i];
		siz1[i]=siz[i];
	}
	ma.clear(),init();
	m1=m;
	
	for(int i=1;i<=n;i++){
		scanf("%lld",&a);
		int p=find_fa(a);
		fa[i]=p;
	}
	for(int i=1;i<=n;i++){
		int p=find_fa(i);
		siz[p]++;
	}
	for(int i=1;i<=n;i++){
		int p=find_fa(i);
		if(!ma.count(p)){
			ma[p]=++m;
			add_edge(m+n,t,siz[p]-1);
			add_edge(t,m+n,0);
			sum+=(siz[p]-1);
		}
		add_edge(i,ma[p]+n,1);
		add_edge(ma[p]+n,i,0);
	}
	int k=dinic(s,t);
	printf("%lld\n",sum-k);
	unordered_set<int> s_;
	for(int i=1;i<=m1;i++){
		for(int j=head[i+n];j;j=nxt[j]){
			int v=to[j];
			if(v>0&&v<=n&&w[j]==0){
				printf("%lld ",v);
				int p=find_fa(v),q=find_fa1(v);
				siz[p]--,siz1[q]--;
				s_.insert(v);
			} 
		}
	}
	for(int i=1;i<=n;i++){
		int p=find_fa(i),q=find_fa1(i);
		if(((siz[p]>1)||(siz1[q]>1))&&(!s_.count(i))) printf("%lld ",i),siz[p]--,siz1[q]--;
	}
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

to Luogu [CF1783F](https://www.luogu.com.cn/problem/CF1783F)

to Codeforces [CF1783F](https://codeforces.com/problemset/problem/1783/F)

考虑题目中交换的含义。

对于 $a$，找到一个 $a_x=i$，并且交换 $a_x,a_i$，发现就是以最快的速度进行交换方式为 `交换任意两个数` 的排序。

考虑其实际含义，在序列中，连接 $(x,a_x)$，交换 $a_x,a_i$，发现就是两条边 $(x,a_x=i),(i=a_x,a_i)$ 合并成一条边 $(x,a_i)$ 和一个自环 $(i,a_x=i)$。

目标就是把所有的边都变成自环。

发现上面的操作会让这个环变的总数减少 $1$。当边的总数为 $1$ 的时候，就是自环，所以，对于一个环，操作步数就是 $sz-1$，$sz$ 是环的大小（环中边和点是一样多的）。

那么，两张图应该怎么做呢？

考虑上面的环操作 $-1$ 是怎么来的。我们显然希望 $-1$ 的数量尽可能多，这样可以在原来所有环大小之和的基础上减去更多的。

在序列上理解，是到后来 $a_x=i$ 的时候，恰好 $a_i=x$，两者交换只用 $1$ 次。

在图上理解，是最后 $sz=2$，减 $1$ 之后 $sz=1$，就是自环，就是说，连起来的边，是 $(x,x)$，代表着 $a_x=x$。

那么，我们想让两个序列最后剩下的这个 $x$ 的个数尽可能多，并且重合。

而且每个环只能选择一个 $x$。

考虑条件：

- $a,b$ 两个序列选出来的 $x$ 应该是一样的（废话）。

- $a,b$ 两个序列选出来的 $x$ 所在的环不能相同。

发现可以以环为点，将 $a_i,b_i$ 所在的环进行连边，目标就是选出最多的边。

二分图最大匹配显然，操作次数易得。

接下来考虑操作。

我们钦定的 $x$ 是不能被选择的，其他的都可以选。

发现对于本来是自环的节点，如果匹配上了，就不会动，否则会选择，原因是要为另一个序列操作。

我们二分图已经处理出匹配的 $mat$ 数组，只要 $mat_i$ 想 $i$ 连边就说明选到了。

因此后面的代码就比较简单了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3005;
int n, a[N], b[N], fir[N << 1], nxt[N * N], son[N * N], tot, to[N][2], cnt, cnt1, mat[N << 1], ans;
bool vis[N], Mat[N][N], aans[N];
bitset<N * 2>f;
inline void add(int x, int y){
	nxt[++tot] = fir[x];
	fir[x] = tot;
	son[tot] = y;
}
inline void init(){
	for(int i = 1; i <= n; i++) fir[i] = 0, vis[i] = 0;
	for(int i = 1; i <= tot; i++) nxt[i] = 0;
	tot = 0;
}
inline void dfs(int x, int o){
	to[x][o] = cnt;
	if(vis[x]) return ;
	vis[x] = 1;
	for(int i = fir[x]; i ; i = nxt[i]){
		dfs(son[i], o);
	}
}
inline bool dfs1(int x){
	if(f[x]) return 0;
	f[x] = 1;
	for(int i = fir[x]; i ; i = nxt[i]){
		if(!mat[son[i]] || dfs1(mat[son[i]])){
			mat[son[i]] = x;
			return 1;
		}
	}
	return 0;
}
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		add(a[i], i);
	}
	for(int i = 1; i <= n; i++){
		if(!vis[i]){
			cnt++;
			dfs(i, 0);			
		}
	}
	cnt1 = cnt;
	init();
	for(int i = 1; i <= n; i++){
		scanf("%d", &b[i]);
		add(b[i], i);
	}
	for(int i = 1; i <= n; i++){
		if(!vis[i]){
			cnt++;
			dfs(i, 1);
		}
	}
	init();
	for(int i = 1; i <= n; i++){
		if(Mat[to[i][0]][to[i][1]]) continue ;
		add(to[i][0], to[i][1]);
	}
	for(int i = 1; i <= cnt; i++){
		f = 0;
		if(dfs1(i)) ans++;
	}
	for(int i = cnt1 + 1; i <= cnt; i++){
		if(!mat[i]) continue ;
		for(int j = 1; j <= n && mat[i]; j++){
			if(to[j][0] == mat[i] && to[j][1] == i){
				mat[i] = 0;
				vis[j] = 1;
			}
		}
	}
	printf("%d\n", n - ans);
	for(int i = 1; i <= n; i++) if(!vis[i]) printf("%d ", i);
	return 0;
}
```

---

## 作者：masonpop (赞：0)

看似是神题，其实是简单题。

首先看到这个交换位置 $i$ 和 $a_i$ 的规则就眼前一亮，这不是经典套路嘛？

果断建图，对于两个序列分别建出两张图，其中连有向边 $i\to a_i$，表示数 $i$ 必须要去数 $a_i$ 那里。此时显然就形成了若干个环。先考虑一张图，根据经典套路，其答案是 $n-\text{环的个数}$。其意义是从每个环中选出一个点不操作，因为其它的点操作后这个点就自动归位了。

那么现在是两个图同时操作。仍然考虑最多选出多少个点不操作。但是有条件：每个环最多选出一个点不操作。也就是说，对于每个点 $i$，设其在两图中分别属于环 $A_i,B_i$，那么选了点 $i$ 就不能在 $A_i,B_i$ 中选其它点了。

这明显是一个二分图匹配的结构。对于每个 $i$，将 $A_i$ 向 $B_i$ 连边。然后求出最大匹配，这些就是不用动的点。把其它点的编号输出即可。由于数据范围小，故直接使用 $O(n^2)$ 的匈牙利算法即可。

注意考虑重边问题，我们只匹配了一条，其它的得输出。我的做法是开个 map 记录一下边的出现次数。[代码](https://codeforces.com/contest/1783/submission/209711232)。

---

## 作者：Link_Cut_Y (赞：0)

最近总做到排列和置换的题。感觉是套路题，尽量写得亲民一点。

--------------------

首先考虑将其中一个排列变成自然顺序的最小操作。显然，最小操作次数取决于原排列所建有向图中置换环的个数 $r$。具体地，将排列 $\mathrm{P}$ 中每个数向排序后的序列 $\mathrm{P'}$ 中这个数所在的位置连边得到图 $\mathrm{G(P)}$。显然，对于每个大小为 $|\mathbb{C}|$ 的置换环，需要 $|\mathbb{C}| - 1$ 次交换才能使环内有序。总操作次数就是 $\sum \left ( |\mathbb{C_i}| - 1 \right ) = n - r$。$r$ 的意义如上所述。其中置换环可以用搜索 $O(n)$ 求出或者并查集 $O\left(n \alpha(n) \right)$ 求出。

现在考虑双排序。每个位置 $i$ 和权值为 $i$ 的点，假设为 $a_x$ 和 $b_y$ 交换，相当于对 $a_x$ 和 $b_y$ 两点所在的置换环都交换了一次。现在要求 $a, b$ 两个排列中的每个置换环 $\mathbb{C}$ 都被交换 $|\mathbb{C}| - 1$ 次。因此，每个置换环中有一个点不需要动。让不动的点尽可能多是我们的目标。

将每个位置 $i$ 所在 $a$ 中置换环 $\mathrm{A_x}$ 和在 $b$ 中所在置换环 $\mathrm{B_y}$ 之间连边。这样形成了一个二分图。考虑边的意义：边两端的点可以不用交换。显然，一个环最多有一个点不交换，因此题目转化为二分图最大匹配。设最大匹配为 $k$，$n - k$ 即为答案。

求二分图匹配可以跑网络流，复杂度 $O(n\sqrt{n})$。实际复杂度还要小得多，因为环的总个数小于等于 $2n$。方案输出就是看是否满流，满流的话代表不用交换，没满流就要交换。

代码很烂，可能跑不过匈牙利算法。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;

const int N = 30010, M = N << 2, INF = 2e9;
int n, m, S, T;
int h[N], e[M], ne[M], f[M], idx = 1;
int d[N], cur[N], a[N], b[N];
int pa[N], pb[N], cnta, cntb, ida[N], idb[N];
bool sta[N], stb[N], st[3010][3010];

void add(int a, int b, int c) {
	e[ ++ idx] = b, ne[idx] = h[a], h[a] = idx, f[idx] = c;
}
bool bfs() { // 分层
	memset(d, -1, sizeof d);
	queue<int> q; cur[S] = h[S];
	q.push(S); d[S] = 1;
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int i = h[u]; i; i = ne[i]) {
			int v = e[i];
			if (d[v] == -1 and f[i]) {
				d[v] = d[u] + 1;
				cur[v] = h[v];
				if (v == T) return true;
				q.push(v);
			}
		}
	}
	return false;
}
int dfs(int u, int flow) { // 找增广路
	int now = 0;
	if (u == T) return flow;
	for (int i = cur[u]; i; i = ne[i]) {
		int v = e[i]; cur[u] = i;
		if (d[v] == d[u] + 1 and f[i])
			if (now = dfs(v, min(flow, f[i])))
				return (f[i] -= now, f[i ^ 1] += now, now);
	}
	return 0;
}
int dinic() { // 求最大匹配
	int flow, ans = 0;
	while (bfs()) while (flow = dfs(S, INF)) ans += flow;
	return ans;
}
void dfsa(int u) { // 找 a 排列中的环
	if (sta[u]) return;
	sta[u] = true; ida[u] = cnta, dfsa(pa[u]);
}
void dfsb(int u) { // 找 b 排列中的环
	if (stb[u]) return;
	stb[u] = true; idb[u] = cntb; dfsb(pb[u]);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ )
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i ++ )
		scanf("%d", &b[i]);
	for (int i = 1; i <= n; i ++ )
		pa[i] = a[i], pb[i] = b[i];
	for (int i = 1; i <= n; i ++ )
		if (!sta[i]) cnta ++ , dfsa(i);
	for (int i = 1; i <= n; i ++ )
		if (!stb[i]) cntb ++ , dfsb(i);
	
	
	S = 0, T = cnta + cntb + 1;
	for (int i = 1; i <= n; i ++ ) { // 环之间建边
		add(ida[i], idb[i] + cnta, 1);
		add(idb[i] + cnta, ida[i], 0);
	}
	
	for (int i = 1; i <= cnta; i ++ )
		add(S, i, 1), add(i, S, 0);
	for (int i = 1; i <= cntb; i ++ )
		add(i + cnta, T, 1), add(T, i + cnta, 0);
	
	int ans = dinic(); printf("%d\n", n - ans);
	
	for (int i = 1; i <= cnta; i ++ )
		for (int j = h[i]; j; j = ne[j])
			if (f[j] == 0 and e[j] != S) 
				st[i][e[j] - cnta] = true;
	
	for (int i = 1; i <= n; i ++ )
		if (st[ida[i]][idb[i]]) st[ida[i]][idb[i]] = false;
		else printf("%d ", i);
	return 0;
}
```

另外关于排列排序的最小交换次数的证明可以参考这篇文章[排列排序最小交换次数](https://www.cnblogs.com/CDOI-24374/p/16410082.html)。这里不再赘述了。

---

## 作者：ducati (赞：0)

## Description

[传送门](https://www.luogu.com.cn/problem/CF1783F)

## Solution

小清新图论题。

操作有些抽象，考虑建立图论模型。$\forall i \in [1,n]$，连一条从 $i$ 到 $a_i$ 的边，则图由若干环组成。$a$ 有序当且仅当图中只有自环。手玩不难发现，对 $x$ 进行操作等价于将 $a_x$ 修改为 $x$，并将 $x$ 的前驱的 $a$ 修改为 $x$ 的后继，从而 $x$ 断成自环，环长减 $1$。

不难发现，对于点数为 $c$ 的环，其中至多只能有一个位置未被操作过。于是问题转化为：将 $[1,n]$ 中的若干位置钦定为关键点，使得两个序列的每个环中**关键点数量均不超过 $1$**，并在此基础上最大化关键点数量。

继续进行转化。考虑建一张二分图，左侧对应 $a$ 中的每个环，右侧对应 $b$ 中的每个环。若位置 $i$ 属于 $a$ 中编号为 $x$ 的环及 $b$ 中编号为 $y$ 的环，则将左侧点 $x$ 与右侧点 $y$ 连一条边。那么，我们需要选定若干条边，使得每个点至多是一条被选定边的端点。显然是二分图最大匹配模型，跑 Dinic 即可。

至于如何构造方案，操作所有非关键点即可。总复杂度 $O(n \sqrt n)$，本题被解决。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;

int read(){
	int s=0,w=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')w=-w;ch=getchar();}
	while (ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+(ch^'0');ch=getchar();}
	return s*w;
}
int n,p,q,S,T,cnt=1,res,a[N],b[N],A[N],B[N],head[N],dep[N],saver[N]; bitset<N> ban;
struct edge{int nxt,to,f,id;}e[N];
void add_edge(int u,int v,int f,int id){e[++cnt]=edge{head[u],v,f,id},head[u]=cnt;}
void Add(int u,int v,int f,int id){add_edge(u,v,f,id),add_edge(v,u,0,id);}
void init(int *a,int *A,int &p){
	for (int i=1;i<=n;i++)  a[i]=read();
	for (int u=1;u<=n;u++){
		p+=(!A[u]);
		for (int x=u;!A[x];A[x]=p,x=a[x]);
	}
}
bool bfs(){
	queue<int> q;
	for (int i=S;i<=T;i++)  dep[i]=0,saver[i]=head[i];
	q.push(S),dep[S]=1;	
	while (!q.empty()){
		int u=q.front();q.pop();
		for (int i=head[u];i;i=e[i].nxt){
			int y=e[i].to;
			if (e[i].f&&!dep[y])  dep[y]=dep[u]+1,q.push(y);
		}
	}
	return dep[T];
}
int dfs(int u,int Flow){
	if (u==T)  return Flow;
	
	int Out=0;
	for (int i=saver[u];i;i=e[i].nxt){
		if (Flow<=0)  break;
		saver[u]=i;

		int y=e[i].to;
		if (dep[y]==dep[u]+1&&e[i].f){
			int tmp=dfs(y,min(Flow,e[i].f));
			e[i].f-=tmp,e[i^1].f+=tmp,Flow-=tmp,Out+=tmp;
		}
	}
	if (!Out)  dep[u]=-114514;
	return Out;
}
int main(){
	n=res=read(),init(a,A,p),init(b,B,q),T=p+q+1;
	for (int i=1;i<=p;i++)  Add(S,i,1,0);
	for (int i=1;i<=q;i++)  Add(i+p,T,1,0);
	for (int i=1;i<=n;i++)  Add(A[i],B[i]+p,1,i);
	while (bfs())  dfs(S,INT_MAX);
	for (int u=1;u<=p;u++){
		for (int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if (!e[i].f&&v>p&&v<T)  ban[e[i].id]=1,res--;
		}
	}
	printf("%d\n",res);
	for (int i=1;i<=n;i++){
		if (!ban[i])  printf("%d ",i);
	}
	return 0;
}
```


---

