# [EC Final 2022] Magic

## 题目描述

**警告：不寻常的内存限制！**

给定一个序列 $a_0, \ldots, a_{2n}$。最初，所有数字都是零。

有 $n$ 个操作。第 $i$ 个操作由两个整数 $l_i, r_i$ 表示（$1 \le l_i < r_i \le 2n, 1 \le i \le n$），它将 $i$ 赋值给 $a_{l_i}, \ldots, a_{r_i-1}$。保证所有 $2n$ 个整数 $l_1, l_2, \ldots, l_n, r_1, r_2, \ldots, r_n$ 都是不同的。

你需要以任意顺序执行每个操作恰好一次。

你想要最大化满足 $a_i 
\neq a_{i+1}$ 的 $i$ 的数量（$0 \leq i < 2n$）在所有 $n$ 个操作之后。输出最大数量。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
2 3
6 7
1 9
5 10
4 8
```

### 输出

```
9
```

# 题解

## 作者：Leasier (赞：5)

妙妙题 /jw

------------

一个简单的想法是考虑 $a_i \neq a_{i + 1}$ 的条件：

- 找出 $l_p / r_p = i + 1$ 的 $p$。
- 条件等价于 $\forall q \neq p, l_q \leq i, r_q > i + 1$，$q$ 在 $p$ 前执行。

然后这道题就被转化成了一个类似“图定向”的问题，然而这种东西一般都是不可做的 /ng

不妨转而考虑两个区间的相对顺序对可以取到 $a_i \neq a_{i + 1}$ 的 $i$ 的影响。

下面讨论两个区间 $[l_1, r_1], [l_2, r_2], l_1 < l_2$：

- $[l_1, r_1] \cap [l_2, r_2] = \emptyset$：无影响。
- $[l_2, r_2] \subseteq [l_1, r_1]$：我们一定会把 $[l_2, r_2]$ 放在后面。
- $\operatorname{otherwise}$：此时 $l_2 < r_1$，若我们把 $[l_1, r_1]$ 放在前面则 $r_1$ 取不到，否则 $l_2$ 取不到。

于是我们可以建立若干“$l_2, r_1$ 只能二选一”的互斥关系，建图后答案即为最大独立集的大小。

由于本题中 $l_i, r_i$ 两两不同，则该图为**二分图**。

bitset 优化 BFS 匈牙利即可。时间复杂度为 $O(\frac{n^3}{w})$。

代码：
```cpp
#include <iostream>
#include <queue>
#include <bitset>

using namespace std;

int head, tail;
int l[5007], r[5007], color[10007], q[10007], link[10007], prex[10007], prey[10007];
bitset<10007> bs1, bs2, bs3[10007];

inline bool bfs(int start, int n){
	int pos = 0;
	head = 1;
	tail = 0;
	q[++tail] = start;
	bs1.set();
	while (head <= tail && pos == 0){
		int cur = q[head++];
		bs2 = bs1;
		bs2 &= bs3[cur];
		for (register int i = bs2._Find_first(); i <= n; i = bs2._Find_next(i)){
			if (link[i] == 0){
				link[i] = cur;
				pos = cur;
				break;
			}
			bs1[i] = false;
			prex[link[i]] = cur;
			prey[link[i]] = i;
			q[++tail] = link[i];
		}
	}
	if (pos == 0) return false;
	for (register int i = pos; i != start; i = prex[i]){
		link[prey[i]] = prex[i];
	}
	return true;
}

int main(){
	int n, m, ans;
	cin >> n;
	m = ans = n * 2;
	for (register int i = 1; i <= n; i++){
		cin >> l[i] >> r[i];
		color[l[i]] = 0;
		color[r[i]] = 1;
	}
	for (register int i = 1; i <= n; i++){
		for (register int j = 1; j <= n; j++){
			if (l[i] < l[j] && l[j] < r[i] && r[i] < r[j]) bs3[l[j]][r[i]] = true;
		}
	}
	for (register int i = 1; i <= m; i++){
		if (color[i] == 0 && bfs(i, m)) ans--;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：李至擎 (赞：4)

“这不是简单题吗，为什么是黑啊？”——marblue

记位置 $i$ 会对答案产生贡献当且仅当 $a_{i-1}\neq a_i$，问题可以转化成在 $2n$ 个点中选最多的贡献给答案，现在考虑限制。对于两个区间 $[l_1,r_1),[l_2,r_2)$，我们分情况讨论一下：

- $[l_1,r_1)\in[l_2,r_2)$。显然我们先执行 $[l_2,r_2)$ 再执行 $[l_1,r_1)$ 不劣。

- $[l_1,r_1)\cap[l_2,r_2)=\varnothing$。显然互不影响。

- $[l_1,r_1)\cap[l_2,r_2)\neq\varnothing$。令 $l_1<l_2,r_1<r_2$，如果 $[l_1,r_1)$ 在后面则 $r_1$ 会产生贡献，否则 $l_2$ 会产生贡献。所以 $r_1$ 与 $l_2$ 不能同时选择，这就是一个建图后的独立集。

发现题目保证 $l_i,r_i$ 互不相等，故这是一个二分图，跑 bitset 优化 dinic/匈牙利即可，复杂度 $\mathcal{O}(\dfrac{n^3}{w})/\mathcal{O}(\dfrac{n^2\sqrt{n}}{w})$。似乎还可以用可持久化线段树优化建图的 dinic，好像是 $\mathcal{O}(n^2\log n)$，但我不太会（

是 luogu 上的倒数第二劣解，不知道为什么 dinic 这么慢啊，可能复杂度假了？

证明一下为什么找到独立集后一定有对应解。无解当且仅当对于区间执行顺序的先后限制构成环。考虑找到这个环上随便一个区间 $[l_1,r_1)$，假设它取的是右端点 $r_1$ 产生贡献，找到它下一个区间 $[l_2,r_2)$，$l_1<l_2,r_1<r_2$，此时只能是 $r_2$ 产生贡献。于是递归下去，因为 $r_i$ 互不相同，所以环上的区间的 $r$ 单调递增，故不会形成环。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,S,T,dep[10005];bitset<10005>g[10005];
int bfs(){
	for(int i=1;i<=T;i++)dep[i]=0;
	dep[S]=1;queue<int>q;q.push(S);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v=g[u]._Find_first();v<=T;v=max(v+1,(int)g[u]._Find_next(v))){
			if(g[u][v]==0)continue;
			if(!dep[v])dep[v]=dep[u]+1,q.push(v);
		}
	}
	return dep[T];
}
int dinic(int u,int flow){
	if(u==T)return flow;
	int rest=0;
	for(int v=g[u]._Find_first();v<=T&&flow;v=max(v+1,(int)g[u]._Find_next(v))){
		if(g[u][v]==0)break;
		if(dep[v]!=dep[u]+1)continue;
		int k=dinic(v,min(flow,1));if(!k)dep[v]=0;
		rest+=k,flow-=k;if(k)g[u][v]=0,g[v][u]=1;
	}
	return rest;
}
int l[5005],r[5005],pos[10005];
signed main(){
	n=read(),S=2*n+1,T=2*n+2;
	for(int i=1;i<=n;i++){
		l[i]=read(),r[i]=read();
		pos[l[i]]=0,pos[r[i]]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(l[i]<l[j]&&l[j]<r[i]&&r[i]<r[j]){
				g[l[j]][r[i]]=1;
			}
		}
	}
	for(int i=1;i<=2*n;i++)if(pos[i]==0)g[S][i]=1;
	for(int i=1;i<=2*n;i++)if(pos[i]==1)g[i][T]=1;
	int ans=2*n;
	while(bfs())ans-=dinic(S,inf);
	printf("%d\n",ans);	
	return 0;
}
```

---

## 作者：lalaouye (赞：2)

首先注意到能产生贡献的只有 $l_i,r_i$，虽然这是废话，因为每个点都有一个唯一对应的 $l_i$ 或 $r_i$，但我认为刚刚的性质还是挺有用的，因为这启发我们考虑每个点的贡献，然而对于一个点可选可不选，并考虑每个的贡献，点之间有些限制，这非常网络流。

于是我们去分析这些性质，发现有包含或不交关系的点之间并不存在限制，否则才有限制。那么什么会有限制呢？其实只有当 $l_i<l_j,r_i<r_j,r_i>l_j$ 时，$l_j$ 和 $r_i$ 之间才有限制，我们连接这些边，由于我们只会在 $l$ 与 $r$ 之间连边，所以长出来的图是个二分图，然后问题变成了求最大独立集问题，于是这道题就做完啦！


代码：


```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; ++ i)
#define rrp(i, l, r) for (int i = r; i >= l; -- i)
#define pii pair <int, int>
#define eb emplace_back
#define inf 1000000000
#define id(x, y) n * (x - 1) + y
#define ls p << 1
#define rs ls | 1
using namespace std;
constexpr int N = 1e4 + 5, M = (1ll << 31) - 1, P = 1e9 + 7;
constexpr double PI = acos (-1.0);
inline int rd () {
  int x = 0, f = 1;
  char ch = getchar ();
  while (! isdigit (ch)) {
    if (ch == '-') f = -1;
    ch = getchar ();
  }
  while (isdigit (ch)) {
    x = (x << 1) + (x << 3) + ch - 48;
    ch = getchar ();
  }
  return x * f;
}
int qpow (int x, int y) {
  int ret = 1;
  for (; y; y >>= 1, x = x * x % P) if (y & 1) ret = ret * x % P;
  return ret;
}
void add (int &x, int y) {
  x += y;
  if (x >= P) x -= P;
}
int n;
int l[N], r[N];
bitset <N> e[N];
int dep[N];
queue <int> q;
bool bfs () {
  rep (i, 0, n * 2 + 1) dep[i] = 0;
  dep[0] = 1;
  q.push (0);
  while (! q.empty ()) {
    int u = q.front ();
    q.pop ();
    for (int v = e[u]._Find_first (); v <= n * 2 + 1; v = e[u]._Find_next (v)) {
      if (dep[v]) continue;
      dep[v] = dep[u] + 1; q.push (v);
    }
  } return dep[n * 2 + 1];
}
int dfs (int u, int f) {
  if (u == n * 2 + 1) return f;
  int out = 0;
  for (int v = e[u]._Find_first (); v <= n * 2 + 1 && f; v = e[u]._Find_next (v)) {
    if (dep[v] != dep[u] + 1) continue;
    int tmp = dfs (v, min (1, f));
    if (tmp) e[u][v] = 0, e[v][u] = 1;
    out += tmp, f -= tmp;
  }
  if (! out) dep[u] = 0;
  return out;
}
bool pos[N];
int main () {
  // freopen ("1.in", "r", stdin);
  // freopen ("1.out", "w", stdout);
  n = rd ();
  rep (i, 1, n) {
    l[i] = rd (), r[i] = rd ();
    pos[r[i]] = 1;
  }
  rep (i, 1, n * 2) {
    if (! pos[i]) e[0][i] = 1;
    if (pos[i]) e[i][n * 2 + 1] = 1;
  }
  rep (i, 1, n) {
    rep (j, 1, n) {
      if (l[i] >= l[j]) continue;
      if (r[i] > l[j] && r[i] < r[j]) e[l[j]][r[i]] = 1;
    }
  }
  int ret = 0;
  while (bfs ()) ret += dfs (0, inf);
  printf ("%d\n", n * 2 - ret);
}
```

---

## 作者：六楼溜刘 (赞：2)

## 题意

~~这道题翻译是我提交的，自己去看翻译。~~

- 你有一个序列 $a_0,a_1,a_2\dots a_{2n}$，初始全为 $0$。
- 给定 $n$ 个区间赋值操作，第 $i$ 个操作 $(l_i,r_i)(1\le l_i,r_i\le 2n)$ 表示把区间 $[l_i,r_i)$ 全部赋值为 $i$，**保证所有 $l_i,r_i$ 互不相同**。
- 你可以指定一个执行操作的顺序，最大化 $\sum_{i=0}^{2n-1}[a_i\ne a_{i+1}]$，输出这个最大值。
- $1\le n\le 5\times 10^3$，**注意空间限制**。

## 题解

首先可以分三种情况转化为二分图最大独立集问题，具体转化可以参考 [lzq 大佬的这篇题解](https://www.luogu.com.cn/blog/lzqtcl/solution-p9726)，这里主要讲他提到但是没有具体说明的**可持久化线段树优化建图**。

~~他题解里说有这种方法于是我去网上找题解结果没找到，然后我就自己琢磨着写了一个。~~

首先考虑问题的转化，对于一对 $(l_x,r_x)(l_y,r_y)$（假设 $l_x<l_y$），$r_x,l_y$ 之间何时会连边。考虑把 $l$ 作为横坐标，$r$ 作为纵坐标，建出坐标系。原本的限制是 $l_x<l_y<r_x<r_y$，即当 $x$ 的纵坐标 $r_x\in (l_y,r_y)$，横坐标 $l_x<l_y$ 时，$r_x$ 和 $l_y$ 之间会连一条边。

![](https://cdn.luogu.com.cn/upload/image_hosting/ldxxf3tf.png)

大概是这样的一些向左无限延长的矩形，然后一个矩形 $(l_y,r_y)$ 的 $l_y$ 需要和它包含的所有点对应的 $r_x$ 连一条边。

为什么要这样转化呢？因为通过线段树优化建图的经验，我们发现向一段连续的区间连边是可维护的，而如果转化为类似“一个点要向包含它的所有矩形连边”就不好维护了。

那么考虑一个类似于扫描线的算法，即维护一条从左到右的扫描线，每次向区间连边，然后把点 $(l_i,r_i)$ 挂在区间上的 $r_i$ 位置。但是线段树优化建图要求**所有点已经被挂在序列上**，即必须离线下来，考虑用其它数据结构转化成在线加点。

这时候~~看了标题~~聪明的同学就能想到用可持久化线段树。

具体来说，每次加入一个点 $(l_i,r_i)$ 的时候，在 $i-1$ 版本的基础上新建一个版本，除去新增 $r_i$ 对应的一条树链以外，其余配置完全继承 $i-1$。这样就能实现加点了。

注意新增的这条树链要记得和从前一个版本中继承的儿子连边。

总结一下，遇到序列上点会增加/减少，但是要向区间连边时可以考虑主席树优化建图。（删点怎么维护应该很简单吧？）

然后考虑边权问题，即考虑新加的这些边容量应该取多少。我之前纠结了半天数据结构优化建图怎么赋容量才能等价于向区间所有点连一条容量为 $1$ 的边。但其实不用这么麻烦，因为是二分图匹配问题，所以中间的边容量是可以取正无穷的！然后就做完了，在新建出来的图上跑一遍 dinic 即可，空间复杂度 $O(n\log n)$，时间复杂度大概是 $O(n^3\log n)$，但这毕竟是 dinic 的复杂度，一般情况下不会被卡的。

## code

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define forup(i,s,e) for(int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(int i=(s);i>=(e);i--)
using namespace std;
#define gc getchar()
inline int read(){
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=5005;
int n,cntn;
struct Node{
	int l,r;
}s[N];
struct flow{//dinic 板子
	struct edge{
		int v,rst,nxt;
	}e[N*80];//注意边数开大一点
	int head[N*20],cur[N*20],cnte=1,dpt[N*20],s,t;
	void adde(int u,int v,int w){
		e[++cnte]=edge{v,w,head[u]};head[u]=cnte;
		e[++cnte]=edge{u,0,head[v]};head[v]=cnte;
	}
	bool bfs(){
		forup(i,1,cntn){
			cur[i]=head[i];
			dpt[i]=-1;
		}
		queue<int> q;
		q.push(s);dpt[s]=0;
		while(q.size()){
			int u=q.front();q.pop();
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].v;
				if(dpt[v]!=-1||!e[i].rst) continue;
				dpt[v]=dpt[u]+1;
				q.push(v);
			}
		}
		return dpt[t]!=-1;
	}
	int dfs(int x,int flow){
		if(x==t||!flow) return flow;
		int res=0;
		for(int i=cur[x];i;i=e[i].nxt){
			cur[x]=i;int v=e[i].v;
			if(dpt[v]!=dpt[x]+1||!e[i].rst) continue;
			int gt=dfs(v,min((int)e[i].rst,flow-res));
			if(gt){
				res+=gt;
				e[i].rst-=gt;
				e[i^1].rst+=gt;
				if(res==flow) break;
			}
		}
		return res;
	}
	int dinic(){
		int ans=0;
		while(bfs()){
			ans+=dfs(s,n);//这里正无穷取的 n，因为流量不会超过 n。
		}
		return ans;
	}
}mf;
struct SegTree{
	#define mid ((l+r)>>1)
	#define lson l,mid,ls[id]
	#define rson mid+1,r,rs[id]
	int num[N*15],cntt,ls[N*15],rs[N*15];
	void Update(int P,int X,int l,int r,int id,int o){//新加入一个点
		if(l==r){
			num[id]=X;
			return;
		}
		num[id]=++cntn;
		if(P<=mid){
			ls[id]=++cntt;rs[id]=rs[o];
			Update(P,X,lson,ls[o]);
			mf.adde(num[id],num[ls[id]],n);
			if(rs[id]) mf.adde(num[id],num[rs[id]],n);
		}else{
			rs[id]=++cntt;ls[id]=ls[o];
			Update(P,X,rson,rs[o]);
			mf.adde(num[id],num[rs[id]],n);
			if(ls[id]) mf.adde(num[id],num[ls[id]],n);
		}
	}
	void Link(int L,int R,int X,int l,int r,int id){//向区间连边
		if(L<=l&&r<=R){
			mf.adde(X,num[id],n);
			return;
		}
		if(L<=mid&&ls[id]) Link(L,R,X,lson);
		if(mid< R&&rs[id]) Link(L,R,X,rson);
	}
}mt;
signed main(){
	n=read();
	forup(i,1,n){
		s[i].l=read();s[i].r=read();
	}
	sort(s+1,s+n+1,[&](Node a,Node b){
		return a.l<b.l;
	});
	mf.s=n*2+1;mf.t=n*2+2;
	mt.cntt=n;cntn=n*2+2;
	forup(i,1,n){
		mf.adde(mf.s,i,1);mf.adde(i+n,mf.t,1);
		mt.Link(s[i].l,s[i].r,i,1,n*2,i-1);
		mt.Update(s[i].r,i+n,1,n*2,i,i-1);
     		//这里点的序号是随便取的，左部点是 [1,n]，右部点是 [n+1,2n]
	}
	printf("%d\n",n*2-mf.dinic());//注意最大独立集是最小点覆盖的补集
}
```

---

## 作者：Petit_Souris (赞：2)

自己做了 2h 过了，很有成就感。

一开始在想区间 dp，但是好像不是很可做，不太懂。

一上来就来一个各个 $l,r$ 互不相同的条件就十分可疑。

先观察不同相交情况的区间对答案的贡献：假设现在考虑 $[l,r)$ 和 $[u,v)$，且 $l<u$。

- 如果 $[l,r)$ 和 $[u,v)$ 不相交，那么 $l,r,u,v$ 的贡献互不影响，都能取到；
- 如果 $[l,r)$ 和 $[u,v)$ 是包含关系，那么先做 $[l,r)$ 再做 $[u,v)$ 也一定都能取到；
- 如果 $[l,r)$ 和 $[u,v)$ 部分相交，那么 $l,v$ 的贡献一定可以取到，$r,u$ 中能恰好取一个。

第三个条件明显是一个独立集的限制，而 $l,r$ 互不相同，连出来是一个二分图，跑二分图最大独立集 = 点数 - 二分图最大匹配 即可。

但是空间只有 16MB，考虑 bitset 优化 dinic 的过程，每次用 `_Find_next(v)` 找下一条出边，复杂度 $\mathcal O(\frac{n^3}{\omega})$，空间复杂度 $\mathcal O(\frac{n^2}{\omega})$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void write(ll x){
	if(x<0)x=-x,putchar('-');
	if(x>9)write(x/10);
	putchar('0'+x%10);
}
const ll N=10005,INF=1e9;
ll n,l[N],r[N],S,T,tag[N],d[N];
bitset<N>to[N];
bool bfs(){
	queue<ll>q;
	q.push(S);
	rep(i,1,T)d[i]=0;
	d[S]=1;
	while(!q.empty()){
		ll u=q.front();q.pop();
		ll v=to[u]._Find_first();
		while(v<=T){
			if(!to[u][v])break;
			if(!d[v]){
				d[v]=d[u]+1;
				q.push(v);
				if(v==T)return 1;
			}
			ll nxt=to[u]._Find_next(v);
			v=max(v+1,nxt);
		}
	}
	return 0;
}
ll dinic(ll u,ll flow){
	ll rst=flow;
	if(u==T)return flow;
	ll v=to[u]._Find_first();
	while(v<=T){
		if(!to[u][v])break;
		if(d[v]==d[u]+1){
			ll k=dinic(v,min(rst,1ll));
			if(!k)d[v]=0;
			else {
				rst--;
				to[u][v]=0,to[v][u]=1;
			}
			if(!rst)return flow;
		}
		ll nxt=to[u]._Find_next(v);
		v=max(v+1,nxt);
	}
	return flow-rst;
}
ll runflow(){
	ll res=0;
	while(bfs())res+=dinic(S,INF);
	return res;
}
bool Med;
int main(){
	cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
	n=read();
	rep(i,1,n)l[i]=read(),r[i]=read(),tag[r[i]]=1;
	S=n*2+1,T=n*2+2;
	rep(i,1,n){
		rep(j,1,n){
			if(l[i]<l[j]&&l[j]<r[i]&&r[i]<r[j])to[l[j]][r[i]]=1;
		}
	}
	rep(i,1,2*n){
		if(!tag[i])to[S][i]=1;
		else to[i][T]=1;
	}
	write(2*n-runflow());
	return 0;
}
```

---

## 作者：Acoipp (赞：1)

网络流。

## 分析

首先题目中说明了**保证所有 $l_i,r_i$ 互不相同**，我们尝试从这个角度入手。

遇到区间排序的问题很显然地任取两个区间出来分类讨论一下，设这两个区间分别为 $[l_1,r_1),[l_2,r_2)$，那么所有情况如下所示（令 $l_1<l_2$）：

- 若 $r_1 < l_2$，那么这两个区间无交集，先后顺序不影响。

- 若 $r_1 > r_2$，那么前一个区间包含后一个区间，显然把前一个区间放在操作序列前会比较优秀。

- 否则这两个区间有交且不包含，如果 $[l_1,r_1)$ 放前面，那么 $l_2$ 这个下标上的元素就会与它之前的不一样；否则 $r_1$ 这个下标上的元素就会与它之前的不一样，经典二选一问题。

于是对有交且不包含的区间像上述执行操作即可，建立二分图，然后用匈牙利算法或者网络流跑最大独立集即可。

二分图最大独立集等于总点数减去最大匹配。

## 代码

代码使用 ISAP 实现，加上 bitset 优化空间即可通过。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 10005
using namespace std;
ll n,i,j,l[N],r[N],pos[N],dis[N],sum[N],s,t,inf,ans;
bitset<N> maps[N];
ll dfs(ll x,ll step){
	if(x==t) return step;
	ll used = 0;
	for(ll i=maps[x]._Find_first();i<=t;i=max(i+1,(ll)maps[x]._Find_next(i))){
		if(maps[x][i]==0) break;
		if(dis[i]+1==dis[x]){
			ll temp = dfs(i,min(1ll,step-used));
			used += temp;
			if(temp) maps[x][i]=0,maps[i][x]=1;
			if(used==step||dis[s]>=inf) return used;
		}
	}
	if(--sum[dis[x]]==0) dis[s] = inf;
	sum[++dis[x]]++;
	return used;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(i=1;i<=n;i++) cin>>l[i]>>r[i],pos[r[i]]=1;
	for(i=1;i<=n;i++) for(j=1;j<=n;j++) if(l[i]<l[j]&&l[j]<r[i]&&r[i]<r[j]) maps[l[j]][r[i]]=1;
	s=0,t=2*n+1,inf=t-s+1,sum[0]=inf;
	for(i=1;i<=2*n;i++){
		if(!pos[i]) maps[s][i]=1;
		else maps[i][t]=1;
	}
	while(dis[s]<inf) ans+=dfs(s,1e18);
	cout<<2*n-ans<<endl;
	return 0;
}
```

---

