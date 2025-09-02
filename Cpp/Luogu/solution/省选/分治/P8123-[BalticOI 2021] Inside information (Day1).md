# [BalticOI 2021] Inside information (Day1)

## 题目描述

有 $N$ 个服务器，第 $i$ 个服务器存储着第 $i$ 块数据，现在有若干种操作：

- `S a b` 第 $a$ 个服务器与第 $b$ 个服务器共享数据，即这两个服务器同时拥有这两个服务器本身拥有的数据块的和，并自动去重（可以理解为数据块之并）。
- `Q a d` 查询第 $a$ 个服务器是否拥有第 $d$ 块数据。
- `C a` 查询存储数据块 $a$ 的服务器数量。

S 操作有 $N-1$ 次，如果把共享看做连边，那么最后将形成以 $N$ 个服务器为点的一棵树；Q 操作和 C 操作一共有 $K$ 次。

求对于每个 Q 操作和 C 操作返回的结果。

## 说明/提示

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$N \le 4000$。
- Subtask 2（5 pts）：第 $1$ 个服务器与第 $2,3,\cdots,N$ 个服务器共享数据。
- Subtask 3（10 pts）：如果 $|A-B|=1$，那么第 $A$ 个服务器和第 $B$ 个服务器共享数据。
- Subtask 4（20 pts）：如果 $A<B$ 且 $2A=B$ 或 $2A+1=B$，那么第 $A$ 个服务器和第 $B$ 个服务器共享数据。
- Subtask 5（25 pts）：每个服务器最多与 $5$ 个服务器共享数据。
- Subtask 6（35 pts）：无特殊限制。

对于 $100\%$  的数据，$1 \le N,K \le 1.2 \times 10^5$。

#### 说明

翻译自 [BalticOI 2021 Day1 B Inside information](https://boi.cses.fi/files/boi2021_day1.pdf)。

## 样例 #1

### 输入

```
6 9
S 1 2
S 1 3
S 3 4
Q 5 1
S 4 5
S 1 6
Q 5 1
Q 1 5
C 1
C 2
C 3
C 4
C 5
C 6```

### 输出

```
no
yes
no
6
6
5
3
2
2```

## 样例 #2

### 输入

```
4 4
S 1 2
S 1 3
S 3 4
Q 2 1
Q 2 2
Q 2 3
Q 2 4```

### 输出

```
yes
yes
no
no```

# 题解

## 作者：阿丑 (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/P8123)

#### 前置知识：

可持久化线段树合并**或**点分治。

#### 题意：

- 给出 $n$ 个集合，初始时第 $i$ 个集合 $S_i=\{i\}$。

- 给出 $n-1+k$ 次操作，每次操作为下列三种之一：
	1. 给出 $a,b$，使 $S_a,S_b\gets S_a\cup S_b$。
	2. 给出 $a,d$，问是否有 $d\in S_a$。
	3. 给出 $a$，问有多少集合满足 $a\in S_i$。

- 保证操作 1 恰好出现 $n-1$ 次，且所有操作 1 的 $(a,b)$ 构成一棵树。

- $n,k\le1.2\times10^5$。

#### 方法 1（线段树合并）：

观察操作 1 与 2，容易想到一个熟悉的问题：$n$ 个孤立的点，每次选两个点连边，维护连通块的点集。可以使用并查集 + 线段树合并维护。

本题中不能使用并查集，因为操作 1 并未将 $S_a$、$S_b$ 合并为同一个集合，两者仍然相互独立。但线段树合并仍然可以使用，并且注意到 $S_a$ 大小一定不大于 $a$ 所在的连通块大小，因此时间复杂度一定不大于上题（即 $\mathcal O(n\log^2 n)$）。由于将合并后的线段树复制成两份会导致复杂度错误，所以使用一棵线段树来维护 $S_a$、$S_b$ 两个集合，通过可持久化来保证修改 $S_a$ 时 $S_b$ 不会改变。

既然用线段树维护了点集，询问点是否在集合中显然可以 $\mathcal O(\log n)$ 查询。考虑操作 3。

求有多少集合 $S_i$ 满足 $a\in S_i$ 较为困难，但求有多少 $i$ 满足 $i\in S_a$ 较为容易：答案即为 $S_a$ 的大小，可以在线段树合并的同时维护。而两者可以互相转化：

考虑样例一（边权 $w(a,b)$ 为边 $(a,b)$ 加入的时间）：

![图挂了，自己脑补吧（](https://s4.ax1x.com/2022/02/09/HJiU8s.png)

由于 $w(1,3)<w(3,4)<w(4,5)$，所以最后 $1\in S_5$。如果将所有边权取反，即倒序加入所有边，则 $w(1,3)>w(3,4)>w(4,5)$，最后 $5\in S'_1$。可以发现当且仅当正序加入所有边后 $a\in S_b$ 时，将所有边权取反后重新倒序加入，最后有 $b\in S'_a$。

所以只需倒序加一次边就能将所有满足 $a\in S_i$ 的 $i$ 都存储到 $S'_a$ 中。但注意到这么做只有在倒序加完所有边后才能得到所有的 $i$，不能处理加完所有边之前的询问。所以在线段树中不再维护每个 $i$ 是否加入，而是对每个时刻 $t$，维护时刻 $t$ 有多少 $i$ 加入。加完边之后，时刻 $t$ 的询问 $\text C\ a$ 统计 $a$ 所对应线段树中的 $[1,t]$ 之和即可。

注意我们在倒序加边，所以在处理时刻 $i$ 加入的边 $(a,b)$ 时，新加入 $S'_a$ 的点 $x$ 不一定是在时刻 $i$ 加入集合的，而可能在这之后。事实上，考虑正序加入的过程，$a$ 被加入 $S_x$ 是在 $b$ 被加入到 $S_x$ 时发生的，而不是在 $a$ 被加入到 $S_b$，即时刻 $i$ 时发生。

对于新加入 $S'_a$ 的点 $x$，$a$ 加入 $S_x$ 的时刻与 $b$ 加入 $S_x$ 的时刻相同，而新加入 $b$ 的点也同理。所以加入 $(a,b)$ 后 $a,b$ 对应的线段树相同（不考虑 $a,b$ 本身的贡献），仍然只需要合并即可。

时间复杂度 $\mathcal O(m\log n+n\log^2n)$，空间复杂度 $\mathcal O(n\log^2n)$，实际空间很难跑满。

代码放在最后。

---

#### 方法 2（点分治）：

观察询问 1 和 3。在树上对一个点进行全局询问，可以想到点分治。

考虑样例一（边权 $w(a,b)$ 为边 $(a,b)$ 加入的时间）：

![图挂了，自己脑补吧（](https://s4.ax1x.com/2022/02/09/HJiU8s.png)

假设在时刻 $5$ 后插入一个询问 $\text C\ 3$，则 $S_1,S_3,S_4,S_5$ 都满足 $3\in S_i$。可以发现，$v$ 对询问 $\text C\ u$ 有贡献，当且仅当从 $u$ 到 $v$ 的路径 $\text{path}(u,v)$ 边权递增，且与 $v$ 相连的边（即最大的那条边）的边权不大于询问的时刻。

对于每个分治中心 $x$，我们要处理所有满足 $\text{path}(u,v)$ 经过 $x$ 的二元组 $(u,v)$ 之间的贡献。考虑要对怎样的点处理询问，统计贡献。

由于 $\text{path}(u,v)$ 递增，$\text{path}(u,v)$ 经过 $x$，所以 $\text{path}(u,x),\text{path}(x,v)$ 也递增。故只需要处理所有本层分治中 $\text{path}(x,v)$ 递增的节点 $v$ 对于 $\text{path}(u,x)$ 递增的节点 $u$ 的贡献即可。

注意到满足上述条件并一定不能满足 $\text{path}(u,v)$ 递增，如上图中 $\text{path}(6,1)$ 递增（因为只有一条边），$\text{path}(1,5)$ 递增，但 $\text{path}(6,5)$ 不递增。记 $e(v)$ 为 $v$ 到 $x$ 的路径上与 $x$ 相连的边，还需满足 $w(e(u))<w(e(v))$。可以调整搜索子树的顺序，先搜索 $w(e(u))$ 较大的子树，保证处理询问 $\text C\ u$ 时所有有贡献的节点 $v$ 都满足 $w(e(u))<w(e(v))$。

而要求最靠近 $v$ 的边的边权不大于询问时刻，只需将最靠近 $v$ 的边的边权作为 $v$ 的权值，处理询问时统计权值不大于时刻的 $v$，可以使用树状数组解决。

考虑询问 2。可以发现对于询问 $\text Q\ u\ v$，当且仅当 $\text{path}(v,u)$ 的边权递增，且最靠近 $u$ 的边的边权不大于询问时刻时满足条件。类似于上述转化，也可以在点分治的过程中实现。读者可以自行思考，或参考代码。

分析复杂度。共有 $\log$ 层，每层每个询问会被处理一次，每个点会被处理一次，加上树状数组的 $\log$，复杂度为 $\mathcal O((n+m)\log^2n)$，空间复杂度 $\mathcal O(n)$。

---

线段树合并代码：

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(int i=l, _=r; i<=_; ++i)
using namespace std;
typedef long long ll;
bool Mbe;
const int mN=1.2e5+9, mS=3.5e7;
int n, k, qn[mN*2][2];
bool ans[mN*2];

namespace SGT {	//线段树
#define lc(p) tr[p].son[0]
#define rc(p) tr[p].son[1]
	struct Node {int son[2], siz;} tr[mS];
	int on, rt[mN];
	void modify(int lp, int &p, int l, int r, int x) {	//在 x 处增加 1，记得可持久化
		tr[p=++on]=tr[lp], ++tr[p].siz;
		if(l==r) return;
		int mid=l+r>>1;
		x<=mid? modify(lc(lp), lc(p), l, mid, x): modify(rc(lp), rc(p), mid+1, r, x);
	}
	void merge(int &p, int q1, int q2) {	//合并
		if(!q1 || !q2) return p=q1|q2, void();
		tr[p=++on].siz=tr[q1].siz+tr[q2].siz;
		merge(lc(p), lc(q1), lc(q2)), merge(rc(p), rc(q1), rc(q2));
	}
	inline bool query1(int p, int l, int r, int x) {	//询问是否存在 x 点
		while(l^r) {
			int mid=l+r>>1;
			x<=mid? (p=lc(p), r=mid): (p=rc(p), l=mid+1);
			if(!p) return 0;
		}
		return 1;
	}
	inline int query2(int p, int l, int r, int x) {	//询问 [1,x] 有多少点
		int res=0;
		while(r>x) {
			int mid=l+r>>1;
			x<=mid? (r=mid, p=lc(p)): (res+=tr[lc(p)].siz, l=mid+1, p=rc(p));
			if(!p) return res;
		}
		return res+tr[p].siz;
	}
#undef lc
#undef rc
}
using namespace SGT;

bool Men;
int main() {
	cerr<<"memory: "<<(&Men-&Mbe>>20)<<"MB"<<endl, 0;
	scanf("%d%d", &n, &k);
	rep(i, 1, n) modify(0, rt[i], 1, n, i);	//初始化，每个集合都只包含自己

	rep(i, 1, n-1+k) {
		char opt;
		int x, y;
		scanf("\n%c%d", &opt, &x);
		if(opt^'C') scanf("%d", &y);

		if(opt=='S') merge(rt[x], rt[x], rt[y]), rt[y]=rt[x], qn[i][0]=x, qn[i][1]=y;  
		//合并后 x y 的集合相同，因此 rt[y]=rt[x]；可持久化，所以一个被合并时另一个不会改变
		else if(opt=='Q') ans[i]=query1(rt[x], 1, n, y);
		else qn[i][0]=x;
	}
	memset(tr, 0, sizeof tr), on=n;
	rep(i, 1, n) rt[i]=i;	//倒着做之前重新初始化，每个集合都为空

	for(int i=n-1+k; i>=1; --i) if(qn[i][1]) {	//即，if( 第 i 次操作为操作 1)
		int x=qn[i][0], y=qn[i][1];
		merge(rt[x], rt[x], rt[y]), modify(rt[x], rt[x], 1, n-1+k, i), rt[y]=rt[x];
		//点 x 在时刻 t 加入 Sy，点 y 在时刻 t 加入 Sx，两者都是在时刻 t 增加了一个节点，所以 x,y 对应的线段树是一样的
	}
	rep(i, 1, n-1+k)
		if(!qn[i][0]) puts(ans[i]? "yes": "no");	//操作 2
		else if(!qn[i][1]) printf("%d\n", query2(rt[qn[i][0]], 1, n-1+k, i)+1);	//操作 3
	return 0;
}
```

---

点分治代码：

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(int i=l, _=r; i<=_; ++i)
#define lfor(t, y, x) for(int t=head[x], y; y=e[t][1], t; t=e[t][0])
using namespace std;
typedef long long ll;
inline void to_max(int &x, int y) {if(x<y) x=y;}
bool Mbe;
const int mN=1.2e5+9;
int n, k, ans[mN], qn[mN];
//ans 表示答案，-1(no) / -2(yes) 表示 Q 操作的答案，其他表示 C 操作的答案
//qn 表示时间的映射，qn[i]=j 表示第 i 个询问是在第 j 条边后，第 j+1 条边前提出的

int oe=1, head[mN], e[mN*2][2];
//oe=1 是为了让编号为 t 的边恰好是第 t/2 条边
inline void adde(const int x, const int y) {e[++oe][0]=head[x], e[head[x]=oe][1]=y;}

vector<int> C[mN];
vector<pair<int, int> > Q[mN];

//timh/timt 是懒惰删除，当 tim_[i]!=T 时表示对应数组所含信息没有意义
int T, hav[mN], timh[mN];
//hav 若有意义，hav[i]=j 表示 path(x, i) 中距离 i 最近的边是第 j 条被加入的边
int tr[mN], timt[mN];	//树状数组
inline void add(int x, const int z) {for(; x<=n; x+=x&-x) timt[x]^T? timt[x]=T, tr[x]=z: tr[x]+=z;}
inline int ask(int x) {
	int res=0;
	for(; x; x^=x&-x) timt[x]^T? timt[x]=T, tr[x]=0: res+=tr[x];
	return res;
}

bool mark[mN];
int siz[mN], rt, tot, krt;
void dfs_rt(int x, int f) {	//找重心
	int k=(siz[x]=1, 0);
	lfor(t, y, x) if(y^f && !mark[y]) dfs_rt(y, x), to_max(k, siz[y]), siz[x]+=siz[y];
	if(to_max(k, tot-siz[x]), k<krt) rt=x, krt=k;
}
void dfs_add(int x, int lst) {	//处理 x 的贡献
	if(timh[x]^T) timh[x]=T;	//使数组有意义
	hav[x]=lst, add(lst, 1);
	lfor(t, y, x) if(t>>1>lst && !mark[y]) dfs_add(y, t>>1);	//t>>1>lst 保证递增
}
void dfs_que(int x, int lst) {	//处理 x 的询问
	for(auto it: Q[x]) {
		int t=it.first, y=it.second;
		if(timh[y]==T && hav[y]<=qn[t]) ans[t]=-2;	//如果 y 数组有意义且距离 y 最近的边边权不大于询问时刻
	}
	for(int t: C[x]) ans[t]+=ask(qn[t]);	//统计 [1, qn[t]] 的边的贡献
	lfor(t, y, x) if(t>>1<lst && !mark[y]) dfs_que(y, t>>1);	//t>>1<lst 保证递减
}
void dfs(int x) {
	krt=tot=siz[x], dfs_rt(x, 0), mark[x=rt]=1;
	timh[x]=++T;	//++T 为清空
	lfor(t, y, x) if(!mark[y]) add(hav[x]=t>>1, 1), dfs_que(y, t>>1), dfs_add(y, t>>1), add(t>>1, -1);
	//按照加边顺序的倒序访问每个子树，保证 w(e(u))<w(e(v))
	//hav[x]=t>>1, add(t>>1, 1) 为处理 x 对询问的贡献，add(t>>1, -1) 为撤销
	hav[x]=0;	//特判 Q x y 中 x=y 的情况
	for(auto it: Q[x]) {
		int t=it.first, y=it.second;
		if(timh[y]==T && hav[y]<=qn[t]) ans[t]=-2;
	}
	for(int t: C[x]) ans[t]+=ask(qn[t]);
	lfor(t, y, x) if(!mark[y]) dfs(y);
}

bool Men;
int main() {
	cerr<<"memory: "<<(&Men-&Mbe>>20)<<"MB"<<endl, 0;

	scanf("%d%d", &n, &k);
	rep(i, 1, n-1+k) {
		char opt;
		int x, y;
		scanf("\n%c%d", &opt, &x);
		if(opt^'C') scanf("%d", &y);

		if(opt=='S') adde(x, y), adde(y, x);
		else if(opt=='Q') Q[y].push_back(make_pair(i-oe/2, x)), qn[i-oe/2]=oe/2, ans[i-oe/2]=-1;
		//初始赋为没有找到
		else C[x].push_back(i-oe/2), qn[i-oe/2]=oe/2;
	}
	siz[1]=n, dfs(1);
	rep(i, 1, k) ans[i]<0? puts(~ans[i]? "yes": "no"): printf("%d\n", ans[i]+1);
	return 0;
}
```

---

## 作者：suzhikz (赞：4)

非常好的线段树合并题，这使我的 binzhou 旋转。

题目开始给了个很重要的信息，合并后形成一棵树，然后在加上共享数据这个神秘操作，自然想到合并线段树。

前两个操作非常板子，第三个操作非常不好处理。

我刚开始想的是合并时，把贡献在做一次合并，但是这样复杂度就退化了。

考虑把第三个询问独立出来，并且先建出图，给每个边赋上一个权值，权值的大小为合并的次数。

发现每个询问三能有贡献的点到询问的点的权值是单调递减的。

这玩意是不是还是非常像合并？没错，这玩意还能用线段树合并维护。我们倒着建图，保证新建的边的点的新增贡献等于询问中另一点的能到的所有点。这样子合并的值就很好算了。

然后对于每个点再来一颗线段树维护他能走到的边，能走当且仅当他走的路的权值单调递增。答案就是这玩意加一。

注意修改不能再原树上做，要新开节点，否则会影响和他共用一个根的点。


```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<iomanip>
#include<cstdio>
#include<string>
#include<deque>
#include<stack>
#include<queue>
#include<vector>
#include<stdio.h>
#include<map>
#include<set>
#include<string.h>
#include<random>
#include<time.h>
#include<stdlib.h>
#include<bitset>
#define il inline
#define reg register
#define popcount __builtin_popcount
using namespace std;
inline void read(int &n){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}n=x*f;}
inline void print(int n){if(n<0){putchar('-');n*=-1;}if(n>9) print(n/10);putchar(n % 10 + '0');}
const int N=1.6e6,M=3.5e7;
int n,m,tree[M],ls[M],rs[M],tot,rt[N];
int update(int x,int l,int r,int pos,int w){
	if(l==r){
		int tmp=++tot;tree[tmp]=tree[x]+w;return tmp;
	}
	int mid=(l+r)/2,tmp=++tot;
	if(pos<=mid){
		rs[tmp]=rs[x];
		if(ls[x]==0)ls[x]=++tot;
		ls[tmp]=update(ls[x],l,mid,pos,w);
	}else{
		ls[tmp]=ls[x];
		if(rs[x]==0)rs[x]=++tot;
		rs[tmp]=update(rs[x],mid+1,r,pos,w);
	}tree[tmp]=tree[ls[tmp]]+tree[rs[tmp]];return tmp;
}
int query(int x,int l,int r,int ql,int qr){
	if(ql<=l&&qr>=r)return tree[x];
	int mid=(l+r)/2,re=0;
	if(ls[x]&&ql<=mid)re+=query(ls[x],l,mid,ql,qr);
	if(rs[x]&&qr>mid)re+=query(rs[x],mid+1,r,ql,qr);
	return re;
}
int merge(int x1,int x2,int l,int r){
	if(x1==0||x2==0){
		return x1+x2;
	}
	if(l==r){
		int tmp=++tot;tree[tmp]=tree[x1]+tree[x2];return tmp;
	}
	int mid=(l+r)/2;
	int tmp=++tot;
	ls[tmp]=merge(ls[x1],ls[x2],l,mid);rs[tmp]=merge(rs[x1],rs[x2],mid+1,r);
	tree[tmp]=tree[ls[tmp]]+tree[rs[tmp]];return tmp;
}

char cc[N];int ll[N],rr[N];
int main(){
	read(n);read(m);
	rt[0]=++tot;
	for(int i=1;i<=n;i++){
		rt[i]=++tot;rt[i]=update(rt[i],1,n,i,1);
	}
	for(int i=1;i<=n;i++){
		rt[i+n]=++tot; 
	}
	for(int lll=1;lll<=n+m-1;lll++){
		cin>>cc[lll];
		if(cc[lll]=='S'){
			read(ll[lll]);read(rr[lll]);
		}else if(cc[lll]=='Q'){
			read(ll[lll]);read(rr[lll]);
		}else{
			read(ll[lll]);
		}
	}
	int cnt=n-1;
	for(int lll=n+m+1;lll>=1;lll--){
		if(cc[lll]=='S'){
			int l=ll[lll],r=rr[lll];
			l=rt[l+n];r=rt[r+n];
			rt[ll[lll]+n]=update(l,1,n-1,cnt,1);rt[rr[lll]+n]=merge(r,rt[ll[lll]+n],1,n-1);
			rt[ll[lll]+n]=rt[rr[lll]+n];cnt--;
		}
	}
	for(int lll=1;lll<=n+m-1;lll++){
		char c=cc[lll];
		if(c=='S'){
			int l=ll[lll],r=rr[lll];
			rt[l]=merge(rt[l],rt[r],1,n);rt[r]=rt[l];cnt++;
		}else if(c=='Q'){
			int l=ll[lll],r=rr[lll];
			if(query(rt[l],1,n,r,r)==1)puts("yes");else puts("no");
		}else{
			int l=ll[lll];
			printf("%d\n",query(rt[l+n],1,n-1,1,cnt)+1);
		}
	}
	return 0;
}
```

---

## 作者：a326820068122c (赞：2)

最近分块上瘾了，就自然想到分块。

这个做法的优势是不需要比较复杂的算法作为前置知识。

### 预处理

因为合并一段时间后会出现很多东西一样，所以就能想到把这些东西揉成块加速处理。

显然，块大小太小会导致块数过多起不到优化效果，块太大会因为形成块前合并过多起不到优化效果。

首先通过观察数据规模可以发现大概能让 $O((n+k)\sqrt n)$ 的算法通过。

然后就能想到先把树的结构离散下来然后记录块的大小，每当超过 $\sqrt n$ 的大小就“截断”一下（特殊的,根节点认为和 $0$ 号节点截断）

然后在操作时每当操作的是"被截断的边"或者“合并之后块的大小（包含其他块的数和散块数量之和）超过 $\sqrt n$ 且操作深度较小的点和其父节点连边为截断边"时需要揉成一个块，这里的块可以包含其他的块。

可以证明，这时的块数 $\le2\sqrt n$（"被截断的边"和“合并之后块的大小超过 $\sqrt n$ 且操作深度较小的点和其父节点连边为截断边"出现的次数均 $\le\sqrt n$），每个块内元素个数 $\le2\sqrt n$。

需要在做每个块时记录其中出现的数，查询时要用（为了节约空间建议使用 `bitset`）还需要记录每个散点和块出现的次数。

### 查询

**对于" Q 操作"** 查询可以寻找这个这个点所有块内和所以散数中是否有这个数。

**对于" C 操作"** 查询可以暴力查找每一个块中如果出现这个数则答案增加它的出现次数，最后再加上散数中出现的次数。

### 总结

时间复杂度 $O((n+k)\sqrt n)$，空间复杂度 $O(n\sqrt n+k)$。

由于大量使用 STL 且没有卡常，需要 O2 才能通过（听说 `vector` 在开 O2 后还跑得蛮快的）。

### 代码
```cpp
#include <bits/stdc++.h>
#define for1(i,n) for(i=1;i<=(n);i++)
#define for0(i,n) for(i=0;i<=(n);i++)
#define forlr(i,l,r) for(i=(l);i<=(r);i++)
using namespace std;
typedef const int cint;
cint N=120005,S=350,K=705;
int n,m,t,ck,fr[N],to[N],d[N],si[N],qx[N],qy[N],c[N],kc[N];
bitset<N> b,g,h[K];
vector<int> v[N],q[N],k[K],kk[K],p[N],pk[N];
void dfs(cint &x,cint &fx){
	si[x]=1;d[x]=d[fx]+1;
	for(int y:v[x]) if(y!=fx)
		dfs(y,x),si[x]+=si[y];
	if(si[x]>S) si[x]=0,b[x]=1;
}
void bk(cint &x){
	for(int z:k[x]) h[ck][z]=1;
	for(int z:kk[x]) bk(z);
}
void add(int x,int y){
	if(d[x]<d[y]) swap(x,y);
	int ss=si[x]+si[y];
	for(int z:p[x]) p[y].push_back(z);
	for(int z:pk[x]) pk[y].push_back(z);
	if(b[x]||(b[y]&&ss>S)){
		swap(k[++ck],p[y]);swap(kk[ck],pk[y]);
		bk(ck);si[x]=si[y]=1;
		pk[y].push_back(ck);
	}else si[x]=si[y]=ss;
	p[x]=p[y];pk[x]=pk[y];
	for(int z:p[y]) c[z]++;
	for(int z:pk[y]) kc[z]++;
}
bool fin(cint &x,cint &y){
	for(int z:pk[x]) if(h[z][y]) return 1;
	for(int z:p[x]) if(z==y) return 1;
	return 0;
}
int gc(cint &x){
	int i,ans=c[x];
	for1(i,ck) if(h[i][x]) ans+=kc[i];
	return ans;
}
int main(){
	int i,x,y;
	char s[5];
	scanf("%d%d",&n,&m);
	for1(i,n+m-1){
		scanf("%s%d",s,&x);
		if(s[0]=='C') q[t].push_back(i-t),qx[i-t]=x;
		else{
			scanf("%d",&y);
			if(s[0]=='S'){
				v[x].push_back(y);
				v[y].push_back(x);
				fr[++t]=y;to[t]=x;
			}else q[t].push_back(i-t),g[i-t]=1,qx[i-t]=x,qy[i-t]=y;
		}
	}
	dfs(1,0);
	for1(i,n) p[i].push_back(i),si[i]=c[i]=1;
	for0(i,t){
		if(i) add(fr[i],to[i]);
		for(int z:q[i]){
			if(g[z]){
				if(fin(qx[z],qy[z])) puts("yes");
				else puts("no");
			}else printf("%d\n",gc(qx[z]));
		}
	}
	return 0;
}
```

---

## 作者：IkunTeddy (赞：2)

# 前置知识
此做法需要用到**线段树合并**和**可持久化线段树**。

可以以做做模板题。

线段树合并：[P4556](https://www.luogu.com.cn/problem/P4556)。

可持久化线段树：[P3919](https://www.luogu.com.cn/problem/P3919)和[P3834](https://www.luogu.com.cn/problem/P3834)。

# 题目分析
这个题就是将相连的两个点求并集，再次赋给这两个点。

我们很轻松就能想到**线段树合并**。但是如果单纯用线段树合并，他能给你的空间卡成 $O(n^2\log{n})$。这都是血的教训啊。

但是算法肯定是没问题的，那么想该如何优化。

**可持久化线段树**就可以帮我们解决这个问题。可持久化正好可以帮助我们减少空间消耗，大概是 $O(n\log{n})$。十分充裕。

但是可持久化线段树合并在 merge 函数中有些改变。合并时需要更新版本。具体代码如下：

```cpp
int merge(int x,int y,int l,int r){
	if(!x||!y)return x|y;
	int v=newnode(); //需要重开点进行持久化更新版本
	if(l==r){
		tree[v].s=tree[x].s+tree[y].s;
		return v;
	}
	int mid=(l+r)>>1;
	tree[v].ls=merge(tree[x].ls,tree[y].ls,l,mid);
	tree[v].rs=merge(tree[x].rs,tree[y].rs,mid+1,r);
	pushup(v);
	return v;
}
```
那么现在操作 $1$ 和操作 $2$ 就很好进行维护了，就是纯模板。

那么现在思考操作 $3$，它也可以被看作是每个数据块拥有那些点来进行计算。但是我们直接正着来遍历一遍发现是有问题的，这个拥有点的集合就会无法传递。

正难则反，我们看一下倒着合并是否可以。惊奇的发现倒着合并竟然刚好可以得到正确的集合！但是查询顺序有先后，我们按照点值域来作为下标的话无法区分时间顺序进行回答询问。

所以我们考虑用时间作为下标进行维护。如果在 $t$ 时间发生合并那么当前数据块的集合至少增加 $1$。所以我们就在当前时间 $t$ 处加 $1$。在与要合并的数据块的集合取并集。就能把增加量传递过来。最后的答案就是 $1$ 至查询时间 $t$ 的前缀和。

这样分析完了思路就很清晰了。有不懂的可以自己画画图理解一下，毕竟文字确实没有图像直观。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
char opt[maxn];int x[maxn],y[maxn],ans[maxn];
int idx[maxn],tot;
struct node{
	int ls,rs;
	int s;
}tree[maxn*400];
int rt[maxn],cnt;
int newnode(){
	int v=++cnt;
	tree[v].ls=tree[v].rs=tree[v].s=0;
	return v;
}
void pushup(int v){
	tree[v].s=tree[tree[v].ls].s+tree[tree[v].rs].s;
}
void update(int pre,int &v,int l,int r,int x,int k){
	v=newnode();
	tree[v]=tree[pre];
	if(l==r){
		tree[v].s+=k;
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid)update(tree[pre].ls,tree[v].ls,l,mid,x,k);
	else update(tree[pre].rs,tree[v].rs,mid+1,r,x,k); 
	pushup(v);
}
int merge(int x,int y,int l,int r){
	if(!x||!y)return x|y;
	int v=newnode();
	if(l==r){
		tree[v].s=tree[x].s+tree[y].s;
		return v;
	}
	int mid=(l+r)>>1;
	tree[v].ls=merge(tree[x].ls,tree[y].ls,l,mid);
	tree[v].rs=merge(tree[x].rs,tree[y].rs,mid+1,r);
	pushup(v);
	return v;
}
int ask(int v,int l,int r,int x){
	if(l==r)return tree[v].s;
	int mid=(l+r)>>1;
	if(x<=mid)return ask(tree[v].ls,l,mid,x);
	else return ask(tree[v].rs,mid+1,r,x);
}
int ask_sum(int v,int l,int r,int x,int y){
	if(x>y)return 0;
	if(!v)return 0;
	if(l>y||r<x)return 0;
	if(l>=x&&r<=y)return tree[v].s;
	int mid=(l+r)>>1;
	return ask_sum(tree[v].ls,l,mid,x,y)+ask_sum(tree[v].rs,mid+1,r,x,y);
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)update(rt[0],rt[i],1,n,i,1);
	for(int i=1;i<=n+m-1;i++){
		scanf("\n%c%d",&opt[i],&x[i]);
		if(opt[i]=='S'){
			scanf("%d",&y[i]);
			rt[x[i]]=merge(rt[x[i]],rt[y[i]],1,n);
			rt[y[i]]=rt[x[i]];
		}else if(opt[i]=='Q'){
			scanf("%d",&y[i]);
			ans[i]=ask(rt[x[i]],1,n,y[i]);
		}else{
			idx[++tot]=i;
		}
	}
	for(int i=1;i<=cnt;i++){
		tree[i].ls=tree[i].rs=tree[i].s=0;//这个地方不初始化会有问题
	}
	cnt=0;
	for(int i=1;i<=n;i++)rt[i]=++cnt;
	for(int i=n+m-1;i>=1;i--){
		if(opt[i]=='S'){
			update(rt[x[i]],rt[x[i]],1,n+m-1,i,1);
			rt[x[i]]=merge(rt[x[i]],rt[y[i]],1,n+m-1);
			rt[y[i]]=rt[x[i]];
		}
	}
	for(int i=1;i<=n+m-1;i++){
		if(opt[i]=='Q'){
			if(ans[i])puts("yes");
			else puts("no");
		}else if(opt[i]=='C'){
			printf("%d\n",ask_sum(rt[x[i]],1,n+m-1,1,i)+1);
		}
	}

	return 0;
}


```

---

## 作者：_maze (赞：1)

很劣但是很好想的点分治做法。

如果你不会点分治，[打个广告](https://www.cnblogs.com/closureshop/p/17032173.html)。

------------
题目已经明示了合并操作会形成一棵树，不妨将加入边的时间设为边权，这样我们可以对余下操作有更深的认识。

观察树上路径，若点 $v$ 的数据存于点 $u$ 内，必须从点 $v$ 到点 $u$ 边权递增。举一个例子，对于下面点 $v$ 到点 $u$ 的路径：

![](https://cdn.luogu.com.cn/upload/image_hosting/xnlngr30.png)

点 $u$ 会先与点 $1$ 合并，之后尽管点 $1$ 与点 $v$ 合并，但是点 $v$ 的数据并不能传给点 $u$。

因此，我们可以改写题目中的余下两个操作，分别为：

1. 查询点 $d$ 到点 $a$ 的路径权值是否递增。

2. 查询点 $d$ 有几条权值递增的路径。

显然，这两个操作都可以用点分治解决。

具体的，我们求出每个点到当前根路径上的最大值（用于判断是否符合询问的时间限制），再求出每个点到根的路径是递增还是递减，由根往下的递减序列和另一条不同子树的递增序列可以合成一条更大的递增序列，因此我们统计递增序列的数量就可以求出 ```C``` 操作的答案了，加个判断也可以求出 ```Q``` 操作的答案。

如何判断是否符合询问的时间限制？对于 ```Q``` 操作，直接判就行。对于 ```C``` 操作，我们建立树状数组，可以实现 $O(\log n)$ 查询。

------------
真的吗？我们好像忽略了一个问题。例如，对于这棵以点 $3$ 为根的树：

![](https://cdn.luogu.com.cn/upload/image_hosting/zqili8ev.png)

尽管点 $1$ 到根是递增序列，点 $5$ 到根是递减序列，但是点 $1$ 到点 $5$ 的路径并不是递增路径。

因此我们要在开始递归前对根连向子树的边从大到小排序，这样才能保证递减路径连上之前的递增路径是货真价实的递增路径。

复杂度是点分治上排序，$O(n \log n \log n)$。

我的实现很丑，建议自己写。

```cpp
#include <bits/stdc++.h>
#define forp(i, a, b) for(int i = (a);i <= (b);i ++)
#define forc(i, a, b) for(int i = (a);i >= (b);i --)
#define ll long long
#define pii pair<ll, ll>
#define mp make_pair
using namespace std;
const ll maxn = 3e5 + 5;
const ll mod = 998244353;
bool chkmax(int &a, int b){ return (a < b) && (a = b); }
int n, K;
struct ques{ int id, u, time, type, point; };
struct edge{ int v, t; };
vector<edge> e[maxn];
vector<ques> que[maxn];
bool vis[maxn];
int mx[maxn], si[maxn], tot, rt;
int ans[maxn];
void find_rt(int u, int fa = -1)
{
    si[u] = 1, mx[u] = 0;
    for(auto p : e[u])
    {
        int v = p.v;
        if(v == fa || vis[v]) continue;
        find_rt(v, u);si[u] += si[v];
        if(mx[u] < si[v]) mx[u] = si[v];
    }
    mx[u] = max(mx[u], tot - si[u]);
    if(mx[u] < mx[rt]) rt = u;
}
int totp, mt[maxn], qu[maxn], col[maxn], C;
struct BIT{
    #define bs(u) (u & (-u))
    int tr[maxn];
    void add(int u, int k){ for(;u <= n + K;u += bs(u)) tr[u] += k; }
    int que(int u){ int ans = 0; for(;u;u -= bs(u)) ans += tr[u]; return ans; }
}T;
// 1:从上往下递增
// 2:从上往下递减
int pd = 0;
void findq(int u, int fa, int val, int mx, int lei)
{
    // cout << u << endl;
    if(val != -1){
        for(auto v : que[u]){
            if(v.type != 2 + pd) continue;
            if(v.type == 2){
                if(qu[v.point] == 0 || ans[v.id] != 0) continue;
                if((lei == 1 || lei == 3) && (qu[v.point] == 2 || qu[v.point] == 3) && mx <= v.time)
                {
                    ans[v.id] = -2;
                }
                else ans[v.id] = -1; 
            }
            else{
                if((lei == 2 || lei == 3) && mx <= v.time) ans[v.id] += (T.que(v.time) + 1);
            }
        }
    }
    for(auto v : e[u]){
        if(v.v == fa || vis[v.v]) continue;
        if(val == -1) findq(v.v, u, -1, max(mx, v.t), lei);
        else if(val < v.t){
            if(lei ==3 || lei == 1) findq(v.v, u, v.t, max(mx, v.t), 1);
        }else{
            if(lei == 3 || lei == 2) findq(v.v, u, v.t, max(mx, v.t), 2);
        }
    }
}
void addq(int u, int fa, int val, int mx, int lei, int k)
{
    if(k == 1) mt[u] = mx, qu[u] = lei, col[u] = C;
    if((lei == 3 || lei == 1) && pd == 1) T.add(mx, k);
    for(auto v : e[u]){
        if(v.v == fa || vis[v.v]) continue;
        else if(val < v.t){
            if(lei == 3 || lei == 1) addq(v.v, u, v.t, max(mx, v.t), 1, k);
        }else{
            if(lei == 3 || lei == 2) addq(v.v, u, v.t, max(mx, v.t), 2, k);
        }
    }
}
bool cmp(edge a, edge b){ return a.t > b.t; }
bool cmp1(edge a, edge b){ return a.t < b.t; }
void del(int u, int fa)
{
    mt[u] = qu[u] = col[u] = 0;
    for(auto v : e[u])
    {
        if(vis[v.v] || v.v == fa) continue;
        del(v.v, u);
    }
}
void calc(int u)
{
    totp = 0;
    sort(e[u].begin(), e[u].end(), cmp1);
    pd = 0;
    qu[u] = 3;
    for(auto p : e[u]){
        if(vis[p.v]) continue;
        C = p.t;
        findq(p.v, -1, p.t, p.t, 3);
        addq(p.v, -1, p.t, p.t, 3, 1);
    }
    del(u, -1);
    qu[u] = 3;
    sort(e[u].begin(), e[u].end(), cmp);
    pd = 1;
    for(auto p : e[u]){
        if(vis[p.v]) continue;
        C = p.t;
        findq(p.v, -1, p.t, p.t, 3);
        addq(p.v, -1, p.t, p.t, 3, 1);
    }
    for(auto v : que[u]){
        if(v.type == 2){
            if(qu[v.point] == 0 || ans[v.id] != 0) continue;
            if((qu[v.point] == 2 || qu[v.point] == 3) && mt[v.point] <= v.time) ans[v.id] = -2;
            else ans[v.id] = -1; 
        }
        else{
            ans[v.id] += (T.que(v.time) + 1);
        }
    }
    for(auto p : e[u])
    {
        if(vis[p.v]) continue;
        addq(p.v, -1, p.t, p.t, 3, -1);
    }
    del(u, -1);
}
void solve(int u){
    vis[u] = 1, calc(u);
    for(auto p : e[u]){
        int v = p.v;
        if(vis[v]) continue;    
        tot = si[v], rt = 0, find_rt(v);
        solve(rt);
    }
}
signed main(){
    // freopen("text.in", "r", stdin);
    // freopen("text.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> K;
    string s;int a, b, cnt = 0;
    forp(i, 1, n + K - 1){
        cin >> s >> a;
        if(s[0] == 'S'){
            cin >> b;
            e[a].push_back(edge{b, i});
            e[b].push_back(edge{a, i});
        }
        else if(s[0] == 'Q'){
            cin >> b;
            que[a].push_back(ques{++ cnt, a, i, 2, b});
        }
        else que[a].push_back(ques{++ cnt, a, i, 3, 0});
    }
    mx[0] = 2147483647;
    tot = n, find_rt(1);
    solve(rt);
    forp(i, 1, cnt)
    {
        if(ans[i] == -1 || ans[i] == 0) cout << "no" << endl;
        else if(ans[i] == -2) cout << "yes" << endl;
        else cout << ans[i] << endl;
    }
    return 0;
}
```


---

