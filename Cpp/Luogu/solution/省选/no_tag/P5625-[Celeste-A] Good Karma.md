# [Celeste-A] Good Karma

## 题目背景

> "我们永远不会忘记在这里的时光"

> "再也没有其他地方能让我感到平静。谢谢。"

> "很遗憾，Oshiro 先生，山庄要关门了。"

> "我会赶上他们，直到这里的一切都井然有序……"

> "在离开这个山庄之后，我应该去哪儿呢？"

## 题目描述

天空度假山庄是位于 Celeste 山半山腰上的一座山庄，这里已经被废弃许久。

当 Madeline 来到这座山庄之时，这里只剩下了一个幽灵，Oshiro 先生，独自管理这座山庄。

因为山庄有着神奇的魔力，里面凝聚着许多 Oshiro 先生不好的想法。

一个想法可能包含 $k$ 种不好的念头，诸如山庄倒闭，无人问津，无人体谅等等，每种念头对于 Oshiro 先生的重要度是不一样的，具体来讲，第 $i$ 种不好的念头对 Oshiro 先生的重要程度为 $2^{i-1}$。

有时，Oshiro 先生会抓起一堆糟糕的想法进行回忆，Oshiro 会一个一个挨着观看这些想法，并获得其中不好的念头。特别地，当 Oshiro 先生**两次看到同一种不好的念头**时，他就会认为这种念头没什么，下一瞬间就会**忘记自己曾经看到过这种念头**。

一次回忆对 Oshiro 先生的重要程度为 Oshiro 在看完这些想法之后**记住的念头**的重要程度和。

自然，在天空度假山庄里，Oshiro 先生对 Madeline 大吐苦水。

多年以后，当 Madeline 回忆她的登山之旅的时候，已经不记得 Oshiro 每个想法对于他的重要程度了，她只记得 Oshiro 先生的某几次回忆的重要程度以及天空度假山庄之中不好的想法的数量与每种想法中可能的不好的念头的数量。

你能帮助她找出有多少种合法的想法序列满足 Oshiro 先生的每次回忆吗？

特别地，一个想法也可能是一团浆糊，即里面什么都没有。

## 说明/提示

对于 $10\%$ 的数据, $ n,k\leq 5,q \leq 15$

对于 $30\%$ 的数据, $ n,q\leq 1000 $

对于额外 $10\%$ 的数据, $ k=1 $

对于额外 $15\%$ 的数据，不存在1操作

对于 $75\%$ 的数据, $n\leq 30000,q\leq 80000,k \leq 20$

对于 $100\%$ 的数据, $ n\leq 2 * 10^5,q\leq 10^6,k\leq 30,0 \leq val < 2^k$

## 样例 #1

### 输入

```
4 3 2
0 3 4 1
0 2 3 3
2
```

### 输出

```
16```

## 样例 #2

### 输入

```
8 9 6
0 1 1 1
0 2 2 9
0 3 3 2
0 4 4 6
0 5 5 0
0 6 6 8
0 7 7 1
0 8 8 7
2
```

### 输出

```
1```

## 样例 #3

### 输入

```
10 15 14
2
0 6 6 439
0 3 8 1865
2
0 7 10 11371
2
1 1
2
2
1 3
2
0 5 8 7784
2
0 4 7 8497
2
```

### 输出

```
155712307
76042715
719747106
76042715
76042715
74890016
76042715
719747106```

# 题解

## 作者：ArrTue (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P5625)

#### 前置知识：

Link-Cut Tree。

#### 题意简述：

- 有 $n$ 个未知数 $a_{1\dots n}$，每个数在 $[0,2^k)$ 范围内，$q$ 次操作，分为三种：
	1. 给出一条信息：$a_{l\dots r}$ 异或和为 $val$。
	2. 撤回第 $cnt$ 次操作 1。
	3. 询问有多少种 $a$ 序列满足当前未被撤回的操作 1。

- $n\le2\times10^5$，$q\le10^6$，$k\le30$。

#### 分析：

记 $s_i$ 为 $a_{1\dots i}$ 的异或和，则操作 1 的信息即为 $s_{l-1}\operatorname{xor}s_r=val$。这意味着确定了 $s_{l-1}$ 和 $s_r$ 的其中一个，另一个就会被确定。将操作 1 抽象为在 $s_{l-1}$ 与 $s_r$ 之间连一条权值为 $val$ 的边，则对于一个连通块，当其中一个 $s$ 确定后，其他也均可确定。

从左到右依次考虑 $a_i$ 的可能取值。考虑 $s_i$ 的值，如果 $s_{0\dots i-1}$ 中至少有一个与 $s_i$ 在同一个连通块内，那么 $s_i$ 就会被确定，$a_i$ 能且仅能取 $s_i\operatorname{xor}s_{i-1}$。否则由于 $s_i$ 能取任意值，$a_i$ 也能取任意值，有 $2^k$ 种方案。

故对于一个连通块，只有其中标号最小的有可能取最任意值（若标号最小的是 $s_0$，则只有一种取值，即 $0$；否则标号最小的有 $2^k$ 种方案），其他数都可以由这个标号最小的确定。故方案数是 $2^{k(m-1)}$，$m$ 代表连通块数量。

特殊地，当两条操作 1 矛盾时，没有情况满足条件，应输出 $0$。

这样问题就转化成：加边，删边，询问连通块数以及边权是否矛盾。

先不考虑边权，只考虑连通块数量。此时操作 1 不会产生矛盾。

如果保证图是森林，则显然可以使用 LCT 维护。考虑怎么把一般的连通图转化为树的情况。

注意到如果要删除的边在某一个环上，则该边的两个端点在删除前后均连通，即删除该边对连通性无影响，不如提前删掉该边。即每次加入一条边，对于形成的环，我们直接删掉该环中最早将被删的边。这样，每次加边都不会形成环，转化成了之前的情况。

现在考虑边权。新边的两个端点之间无边时，两点之间无限制关系，不会产生矛盾；有边时，若两点之间边权异或和不同于新边的边权，则产生矛盾，且矛盾会一直持续到该新边被删除或环上最早将被删的边被删除。

复杂度均摊 $\mathcal O(q\log n)$。

---

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(int i=l, _=r; i<=_; ++i)
#pragma GCC diagnostic ignored "-Wparentheses"
using namespace std;
typedef long long ll;
inline ll read() {
	ll res=0; bool k=1; char ch;
	while(!isdigit(ch=getchar())) k=ch^45;
	do res=res*10+(ch&15); while(isdigit(ch=getchar()));
	return k? res: -res;
}
inline void swap_(int &x, int &y) {int t_=x; x=y, y=t_;}
inline void to_max(int &x, int y) {if(x<y) x=y;}
inline int min_(int x, int y) {return x<y? x: y;}
const int mN=2e5+9, mQ=1e6+9, mS=mN+mQ, modn=998244353;
int n, q, k, cnt, ans, p[mN];   //p 为 2^ki 的预处理
int opt[mQ], cut[mQ], tim[mS], a[mQ][2];
//操作类型、删掉的边标号、边被删的时间、边的两端点

namespace LCT {
	#define lc tr[p].son[0]
	#define rc tr[p].son[1]
	#define f tr[p].fa
	struct Node {
		int fa, son[2], mn; //mn 为最早被删边的标号
		ll val, sum;    //边权，边权和
		bool rev;
	} tr[mS];
	inline bool which(int p) {return tr[f].son[1]==p;}
	inline bool is_rt(int p) {return !f || tr[f].son[0]^p && tr[f].son[1]^p;}
	inline void push_up(int p) {
		tr[p].mn=tr[tr[p].son[tim[tr[rc].mn]<tim[tr[lc].mn]]].mn;
		if(tim[p]<tim[tr[p].mn]) tr[p].mn=p;
		tr[p].sum=tr[p].val^tr[lc].sum^tr[rc].sum;
	}
	inline void push_down(int p) {
		if(!tr[p].rev) return;
		swap_(tr[lc].son[0], tr[lc].son[1]), tr[lc].rev^=1;
		swap_(tr[rc].son[0], tr[rc].son[1]), tr[rc].rev^=1;
		tr[p].rev=0;
	}
	inline void rotate(int p) {
		int x=f, fx=tr[x].fa;
		bool wp=which(p), wx=which(x), isrtx=is_rt(x);
		if(tr[p].son[wp^1]) tr[tr[p].son[wp^1]].fa=x;
		tr[x].son[wp]=tr[p].son[wp^1];
		tr[x].fa=p, tr[p].son[wp^1]=x, f=fx;
		if(!isrtx) tr[fx].son[wx]=p;
		push_up(x), push_up(p);
	}
	int sta[mS], top;
	void splay(int p) {
		for(int x=sta[top=1]=p; !is_rt(x); ) sta[++top]=x=tr[x].fa;
		while(top) push_down(sta[top--]);
		for(; !is_rt(p); rotate(p)) if(!is_rt(f)) rotate(which(f)^which(p)? p: f);
	}
	inline void access(int p) {for(int x=0; p; x=p, p=f) splay(p), rc=x, push_up(p);}
	inline void make_rt(int p) {access(p), splay(p), swap_(lc, rc), tr[p].rev^=1;}
	inline int find_rt(int p) {
		for(access(p), splay(p); lc; ) push_down(p=lc);
		return splay(p), p;
	}
	#undef lc
	#undef rc
	#undef f
}
using namespace LCT;
inline void e_cut(int p) {
	make_rt(p);
	access(a[p-n-1][0]), splay(p), tr[a[p-n-1][0]].fa=0, tr[p].son[1]=0;
	access(a[p-n-1][1]), splay(p), tr[a[p-n-1][1]].fa=0;
}

int main() {
	n=read(), q=read(), k=read();
	p[0]=1, p[1]=(1ll<<k)%modn;
	rep(i, 2, ans=n+1) p[i]=(ll) p[i-1]*p[1]%modn;
	rep(i, 0, n+q+1) tim[i]=q+1, tr[i].mn=i;    //初始化
	rep(i, 1, q) {
		if((opt[i]=read())==0) ++cnt, a[cnt][0]=read(), a[cnt][1]=read()+1, tr[n+1+cnt].sum=tr[n+1+cnt].val=read();
        //因为不想让 a[i][0]=0，故两者均 +1：l-1 -> l； r -> r+1
		else if(opt[i]==1) tim[cut[i]=n+1+read()]=i;
	}
	cnt=0;
	int mx=0;
	rep(i, 1, q) if(opt[i]==0) {
		++cnt;
		int u=a[cnt][0], v=a[cnt][1], t=tim[n+1+cnt];
        make_rt(u);
        int rt_v=find_rt(v);
		if(rt_v^u) {    //u,v 不在同一连通块中
			--ans;
			swap_(tr[rt_v].son[0], tr[rt_v].son[1]), tr[rt_v].rev^=1;   //相当于 make_rt(v)
			tr[rt_v].fa=tr[u].fa=n+1+cnt;   //相当于 link(u, n+1+cnt), link(v, n+1+cnt)
		} else {
			int id=tr[u].mn;
			if(tr[u].sum^tr[n+1+cnt].val) to_max(mx, min_(tim[id], t));
            //如果不相同，则到 min(tim[id], t) 之前均会矛盾
			if(tim[id]<t) { //最先被删除的边是 id
				e_cut(id), cut[tim[id]]=0;  //标记被删过
				make_rt(cnt+n+1);  
				make_rt(u), splay(u), tr[u].fa=cnt+n+1; //link(u, cnt+n+1)
				make_rt(v), splay(v), tr[v].fa=cnt+n+1; //link(v, cnt+n+1
			} else cut[t]=0;    //最先被删的边是 t，直接不加了
		}
	} else if(opt[i]==1) {
		if(cut[i]) ++ans, e_cut(cut[i]);
	} else printf("%d\n", i<=mx? 0: p[ans-1]);
	return 0;
}
```

---

## 作者：dAniel_lele (赞：0)

题目写的什么玩意，通过简单的转化可以得到每条限制等价于 $a_{l-1}\oplus a_r=val$，要求 $a_0=0,0\leq a_i<2^k$，求方案数。

显然可以用带权并查集处理有用限制组数。

不难发现每个限制存在的时间是一段区间，考虑线段树分治，离线下来跑可撤销带权并查集即可。总复杂度 $O(n\log^2n)$。

具体细节见代码。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
const int mod=998244353;
int qp(int a,int b){
	if(b<0) b=mod-b-1;
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
int opt[1000005],lv[1000005],rv[1000005],vv[1000005],lst[1000005];
vector<pair<pair<int,int>,int>> vc[4000005];
int f[200005],tof[200005],siz[200005],n,q,k;
vector<pair<int,pair<int,pair<int,int>>>> rem[4000005];
int find(int i){
	return f[i]==i?f[i]:find(f[i]);
}
int qlen(int i){
	return f[i]==i?0:qlen(f[i])^tof[i];
}
void add(int i,int l,int r,int ql,int qr,pair<pair<int,int>,int> cg){
	if(ql<=l&&r<=qr){
		vc[i].push_back(cg);
		return ;
	}
	if(ql<=mid) add(i*2,l,mid,ql,qr,cg);
	if(qr>mid) add(i*2+1,mid+1,r,ql,qr,cg);
}
void del(int i){
	for(auto v:rem[i]){
		f[v.first]=v.second.first;
		siz[v.first]=v.second.second.first;
		tof[v.first]=v.second.second.second;
	}
}
void solve(int i,int l,int r,int num){
	for(auto v:vc[i]){
		if(num==-1) break;
		int x=v.first.first,y=v.first.second,w=v.second;
		int X=find(x),Y=find(y);
		w^=qlen(x)^qlen(y);
		if(X==Y){
			if(w!=0){
				num=-1;
				break;
			}
			continue;
		}
		if(siz[X]>siz[Y]){
			swap(X,Y);
		}
		rem[i].push_back(make_pair(X,make_pair(f[X],make_pair(siz[X],tof[X]))));
		rem[i].push_back(make_pair(Y,make_pair(f[Y],make_pair(siz[Y],tof[Y]))));
		f[X]=Y,siz[Y]+=siz[X],tof[X]=w;
		num++;
	}
	reverse(rem[i].begin(),rem[i].end());
	if(l==r){
		if(opt[l]==2){
			if(num==-1) cout<<0;
			else cout<<qp(qp(2,k),n-num);
			cout<<"\n";
		}
		del(i);
		return ;
	}
	solve(i*2,l,mid,num),solve(i*2+1,mid+1,r,num);
	del(i);
	rem[i].clear();
	rem[i].shrink_to_fit();
}
int rpos[1000005],rcnt;
signed main(){
	cin>>n>>q>>k;
	for(int i=1;i<=q;i++){
		cin>>opt[i];
		if(opt[i]==0){
			cin>>lv[i]>>rv[i]>>vv[i];
			lst[i]=i;
			rpos[++rcnt]=i;
		}
		else if(opt[i]==1){
			int pos; cin>>pos;
			pos=rpos[pos];
			add(1,1,q,lst[pos],i,make_pair(make_pair(lv[pos]-1,rv[pos]),vv[pos]));
			lst[pos]=i+1;
		}
	} 
	for(int i=1;i<=q;i++){
		if(opt[i]==0&&lst[i]==i){
			add(1,1,q,i,q,make_pair(make_pair(lv[i]-1,rv[i]),vv[i]));
		}
	}
	for(int i=0;i<=n;i++) f[i]=i,siz[i]=1;
	solve(1,1,q,0);
	return 0;
}
```

---

## 作者：5ab_juruo (赞：0)

卡常半天原来是调试信息没删（

出题人又不说人话题面（

---

给定一个长为 $n$ 的整数序列 $a$，值域 $[0,2^k)$。有三种操作：

- `0 l r v`：加上 $\operatorname{xor}_{i=l}^r a_i=v$ 的限制条件；
- `1 x`：撤回第 $x$ 条限制；
- `2`：在当前限制下，有多少种序列满足条件。

不考虑操作 2 时，一看到限制就无脑转成前缀和，则要求变成两个数异或和，想到建图连边。每次统计连通块个数 $cnt$，同时钦定长度为 $0$ 的前缀和为 $0$，则答案就是 $2^{k\times (cnt-1)}$。

但是，给出的条件不保证有解，如何判断？考虑带权并查集维护连通块生成树，每次加边，如果两个端点在一个连通块，则两点在并查集上到根节点距离的异或和就是两点间路径的异或和。如果相等，则不必再加边，否则就无解。

加上操作 2 后就是一个经典的线段树分治，将并查集按秩合并支持撤销即可，复杂度 $\mathcal{O}(q\log q\log n)$。

注意加边的时候并查集上的边权要异或上两点到根的异或值。还可以加个优化：如果当前无解则所有子节点的询问一定无解，直接全部输出。

卡到了第三，和 LCT 的做法居然差不多，加个 zkw 可能就能榜一了（？

```cpp
#include <cstdio>
#include <cctype>
#include <vector>
using namespace std;

typedef long long ll;
const int max_q = 1000000, max_qs = 1048576, max_n = 1000001, mod = 998244353;

struct stnode
{
	int x, y;
};
stnode stk[max_q];
int opt[max_q], qc[max_qs*2+1], l[max_q], r[max_q], v[max_q], qid[max_q], stp = 0;
int dsu[max_n], val[max_n], rnk[max_n], k, kc;
ll pws[max_n];
vector<int> p[max_qs*2+1];

inline int ls(int x) { return x << 1; }
inline int rs(int x) { return (x << 1) | 1; }
inline void my_swap(int& a, int& b) { int k = a; a = b, b = k; }

void build(int l, int r, int id)
{
	if (l == r)
	{
		qc[id] = (opt[l] == 2);
		return;
	}
	
	int mid = (l + r) >> 1;
	build(l, mid, ls(id)), build(mid + 1, r, rs(id));
	qc[id] = qc[ls(id)] + qc[rs(id)];
}

void modify(int L, int R, int l, int r, int id, int val)
{
	if (L <= l && r <= R)
	{
		p[id].push_back(val);
		return;
	}
	
	int mid = (l + r) >> 1;
	if (L <= mid && l <= R)
		modify(L, R, l, mid, ls(id), val);
	if (L <= r && mid < R)
		modify(L, R, mid + 1, r, rs(id), val);
}

inline void unite(int x, int y, int tv)
{
	if (rnk[x] < rnk[y])
		my_swap(x, y);
	stk[stp++] = { x, y };
	rnk[x] += rnk[y], val[y] = tv;
	dsu[y] = x;
}

void solve(int L, int R, int id)
{
	int pl, pr, tl, tr, pls = stp, hans = 1;
	for (int x : p[id])
	{
		pl = l[x], tl = 0; while (pl != dsu[pl]) tl ^= val[pl], pl = dsu[pl];
		pr = r[x], tr = 0; while (pr != dsu[pr]) tr ^= val[pr], pr = dsu[pr];
		if (pl != pr)
			unite(pl, pr, v[x] ^ tl ^ tr), kc--;
		else if ((tl ^ tr) != v[x])
		{
			for (int i = 0; i < qc[id]; i++)
				puts("0");
			hans = 0; break;
		}
	}
	if (hans)
	{
		if (L == R)
		{
			if (opt[L] == 2)
				printf("%lld\n", pws[kc-1]);
		}
		else
		{
			int mid = (L + R) >> 1;
			solve(L, mid, ls(id)), solve(mid + 1, R, rs(id));
		}
	}
	
	while (stp > pls)
	{
		stp--;
		rnk[stk[stp].x] -= rnk[stk[stp].y];
		dsu[stk[stp].y] = stk[stp].y;
		kc++;
	}
}

inline int read()
{
	int c = getchar(), t = 1, n = 0;
	while (isspace(c)) { c = getchar(); }
	if (c == '-') { t = -1, c = getchar(); }
	while (isdigit(c)) { n = n * 10 + c - '0', c = getchar(); }
	return n * t;
}

signed main()
{
	int n = read(), m = read(), qc = 0;
	
	k = (1 << read()) % mod, kc = n + 1;
	for (int i = 0, px; i < m; i++)
	{
		opt[i] = read();
		
		if (opt[i] == 0)
		{
			l[qc] = read() - 1, r[qc] = read(), v[qc] = read();
			qid[qc++] = i;
		}
		else if (opt[i] == 1)
		{
			px = read() - 1;
			modify(qid[px], i, 0, m - 1, 1, px);
			opt[qid[px]] = -1;
		}
	}
	build(0, m - 1, 1);
	for (int i = 0; i < qc; i++)
		if (opt[qid[i]] == 0)
			modify(qid[i], m - 1, 0, m - 1, 1, i);
	
	for (int i = 0; i <= n; i++)
		dsu[i] = i, rnk[i] = 1;
	pws[0] = 1;
	for (int i = 0; i < n; i++)
		pws[i+1] = pws[i] * k % mod;
	
	solve(0, m - 1, 1);
	
	return 0;
}
```

---

