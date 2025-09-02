# [JOISC 2021] 最悪の記者 4 (Worst Reporter 4) (Day4)

## 题目背景

B 太郎不可爱。

## 题目描述

B 太郎是一名主要写关于 OI 的报道的记者。再过几天，就要举行 IOI 了，B 太郎决定写一篇关于 IOI 的文章。

比赛将有 $n$ 名选手参加，每位选手的编号从 $1$ 到 $n$。每位选手都有一个 Rating，这是衡量其实力的标准。Rating 用 $1$ 至 $10^9$ 之间的整数表示。

B 太郎采访了每位选手，并获得了以下信息：

- 选手 $i\ (1\le i\le N)$ 的 Rating 大于等于选手 $a_i\ (1\le a_i \le n)$ 的 Rating（$a_i$ 可以等于 $i$）。

在所有的采访结束后，B 太郎从管理 Rating 系统的公司收到了一张表格，上面有每个选手的 Rating。 表上写着以下信息：

- 选手 $i\ (1 \le i \le n)$ 的 Rating 是 $h_i$。

当 B 太郎试图根据这些信息写一篇文章时，他发现每个选手的 Rating 表可能存在错误。

由于临近截止时间，没有时间去弄正确的 Rating 表。因此，B 太郎决定重写表中选手的 Rating，使其与采访中获得的信息不相矛盾。

B 太郎在表中改写选手 $i\ (1\le i \le n)$ 的 Rating 需要 $c_i$ 日元。

也就是说，B 太郎可以通过支付 $c_i$ 日元，将列表中选手 $i$ 的 Rating 更改为 $1$ 到 $10^9$ 之间的任意整数。为了在截止日期前完成任务，B 太郎想要最小化更改列表中 Rating 的总成本。

编写一个程序，给定选手的数量、采访获得的信息、Rating 列表、和更改每个选手 Rating 所用的花费。请你计算不与采访信息矛盾的情况下，最少需要花费多少日元。

## 说明/提示

#### 样例 #1 解释

如下表所示。

| 选手 | 原 Rating | 更改为 | 花费日元 |
| :-: | :-: | :-: | :-: |
| $1$ | $6$ | $1$ | $5$ |
| $3$ | $8$ | $4$ | $4$ |
| $5$ | $2$ | $10^9$ | $5$ |

花费了 $5+4+5=14$ 日元。

本样例满足 Subtask $1, 2, 3$。


#### 样例 #2 解释

信息一致，输出 $\tt 0$。

#### 样例 #3 解释

本样例满足 Subtask $1, 2, 3$。

#### 数据规模与约定

**本题采用 Subtask 计分法。**

| Subtask | 分值占比百分率 | 特殊限制 |
| :-: | :-: | :-: |
| $1$ | $14\%$ | $n \le 5 \times 10^3$，$a_1 = 1$，$a_i \le i - 1$，且 $2 \le i \le n$ |
| $2$ | $65\%$ | $a_1 = 1$，$a_i \le i - 1$，且 $2 \le i \le n$ |
| $3$ | $21\%$ | / |

**注：斜线表示无特殊限制。**

对于 $100\%$ 的数据：

- $2 \le n \le 2 \times 10^5$；
- $1 \le a_i \le n\ (1\le i\le n)$；
- $1\le h_i,\ c_i \le 10^9\ (1\le i\le n)$；


#### 说明

本题译自 [第２０回日本情報オリンピック 2020/2021春季トレーニング合宿 -](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/index.html) [競技 4 -](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day4/2021-sp-d4-notice.pdf) [T3 日文题面](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day4/worst_reporter4.pdf)。

## 样例 #1

### 输入

```
6
1 6 5
1 3 6
1 8 4
3 4 9
2 2 5
2 5 6
```

### 输出

```
14```

## 样例 #2

### 输入

```
5
1 1 1
2 2 1
4 3 1
3 3 1
4 3 1
```

### 输出

```
0```

## 样例 #3

### 输入

```
20
1 7 381792936
1 89 964898447
1 27 797240712
3 4 299745243
2 18 113181438
2 20 952129455
4 34 124298446
4 89 33466733
7 40 109601410
5 81 902931267
2 4 669879699
8 23 785166502
8 1 601717183
8 26 747624379
1 17 504589209
9 24 909134233
16 56 236448090
8 94 605526613
5 90 481898834
9 34 183442771
```

### 输出

```
2711043927
```

## 样例 #4

### 输入

```
20
15 62 418848971
13 5 277275513
14 60 80376452
12 14 256845164
12 42 481331310
6 86 290168639
3 98 947342135
3 19 896070909
16 39 48034188
8 29 925729089
18 97 420006994
13 51 454182928
19 61 822405612
13 37 148425187
15 77 474094143
14 27 272926693
18 43 566552069
9 93 790433300
10 73 61654171
14 28 334498030
```

### 输出

```
4012295156
```

# 题解

## 作者：yyyyxh (赞：9)

考虑 $i$ 向 $a_i$ 连边，构成一个内向基环树，注意到环上的人的 Rating 都应相等，而树上祖先的 Rating 都比后代小。

假设只有一棵树的情况。注意到这样一个事实：

当确定好不更改哪一些人的 Rating 时，如果这些人的 Rating 满足了他们之间已经有了的限制关系，剩下的人通过更改 Rating 一定能够满足题意。

问题转化成了保留一定数量的点满足限制关系，且这些点的权值和最大，想到树形 DP。

设 $f_u$ 表示第 $u$ 个人必须选，其子树中的选择的点权值和的最大值。

$$f_u=c_u+\max_{S\in subtree(u)/\{u\}}\sum_{v \in S} f_v$$

其中 $S$ 是两两没有祖先关系且 Rating 都大于 $h_u$ 的一些点的集合。

发现这些点的选取跟 $h_u$ 有关，把 $h_u$ 离散化后记这些转移式右边那坨为 $g_{u,i}$，表示仅考虑那些 $h_v\geq i$ 的点的答案。

这样子就 $f_u=c_u+g_{u,h_u}$ 了。

转移 $g$ 数组就把各个儿子对应位置的值相加，再与父亲的 DP 值 $[1,h_u]$ 前缀取 max 即可，线段树合并维护。

现在线段树要支持区间取 max 和合并，也就是说要取 max 还要加，想了很久。

后来问了同机房数据结构神仙才知道要维护两个懒标记，像线段树2一样先 max 后 +，本质上是广义矩阵乘法，写一个 struct 复合懒标记即可。

至于环上的话枚举将值修改成环上的哪一个值或者是全局最小值，取最大值统计答案。

代码：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int _=200003;
int n,cnt;
int a[_],h[_],c[_],t[_];
int read(){
	char c=getchar();int x=0;
	while (c<48||c>57) c=getchar();
	do x=(x<<1)+(x<<3)+(c^48),c=getchar();
	while (c>=48&&c<=57);
	return x;
}
typedef long long ll;
struct tags{ll a,c;tags(ll A=0,ll C=0):a(A),c(C){}};
tags operator*(const tags x,const tags y){
	return tags(max(x.a,y.a-x.c),x.c+y.c); //这里需要稍微推下式子
}
int hd[_],ver[_],nxt[_],tot;
void add(int u,int v){nxt[++tot]=hd[u];hd[u]=tot;ver[tot]=v;}
tags sg[_<<6];
int lc[_<<6],rc[_<<6];
void pushdown(int p){
	if (sg[p].a||sg[p].c){
		if (!lc[p]) lc[p]=++cnt;
		sg[lc[p]]=sg[lc[p]]*sg[p];
		if (!rc[p]) rc[p]=++cnt;
		sg[rc[p]]=sg[rc[p]]*sg[p];
		sg[p]=tags();
	}
}
ll query(int x,int &p,int l=1,int r=n){
	if (!p) p=++cnt;
	if (l==r) return sg[p].a+sg[p].c;
	pushdown(p);
	int mid=(l+r)>>1;
	if (x<=mid) return query(x,lc[p],l,mid);
	else return query(x,rc[p],mid+1,r);
}
void modify(int x,ll v,int &p,int l=1,int r=n){
	if (!p) p=++cnt;
	if (x>=r) {sg[p]=sg[p]*tags(v,0);return;}
	pushdown(p);
	int mid=(l+r)>>1;
	modify(x,v,lc[p],l,mid);
	if (x>mid) modify(x,v,rc[p],mid+1,r);
}
int merge(int u,int v){
	if (!u||!v) return u^v;
	if (!lc[u]&&!rc[u]) u^=v^=u^=v;
	if (!lc[v]&&!rc[v]) sg[u]=sg[u]*tags(0,sg[v].a+sg[v].c);
    //每一次都pushdown强行新建节点复杂度会爆炸，所以没有儿子节点时改为添加加法懒标记
	else pushdown(u),pushdown(v);
	lc[u]=merge(lc[u],lc[v]);
	rc[u]=merge(rc[u],rc[v]);
	return u;
}
int rt[_];ll buc[_];
bool vis[_],cir[_],tmp[_];
void dfs(int u){
	for (int i=hd[u]; i; i=nxt[i]){
		int v=ver[i];
		if (cir[v]) continue;
		dfs(v);
		rt[u]=merge(rt[u],rt[v]);
	}
	ll v=query(h[u],rt[u])+c[u];
	if (!cir[u]) modify(h[u],v,rt[u]);
}
int main(){
	ll sum=0; n=read();
	for (int i=1; i<=n; ++i){
		a[i]=read(); t[i]=h[i]=read();
		sum+=c[i]=read(); add(a[i],i);
	}
	sort(t+1,t+n+1);
	int rk=unique(t+1,t+n+1)-t-1;
	for (int i=1; i<=n; ++i) h[i]=lower_bound(t+1,t+rk+1,h[i])-t;
	for (int i=1; i<=n; ++i)
		if (!vis[i]){
			int cur=i;
			while (!vis[cur]) tmp[cur]=vis[cur]=1,cur=a[cur];
			if (tmp[cur]) while (!cir[cur]) cir[cur]=1,cur=a[cur];
			cur=i;while (tmp[cur]) tmp[cur]=0,cur=a[cur];
		}
	for (int i=1; i<=n; ++i) if (cir[i]) dfs(i);
	for (int i=1; i<=n; ++i)
		if (cir[i]){
			int cur=i;
			while (cir[cur]){
				cir[cur]=0;
				if (cur^i) rt[i]=merge(rt[i],rt[cur]);
				buc[h[cur]]+=c[cur];
				cur=a[cur];
			}
			ll res=query(1,rt[i]);
			while (!tmp[cur]){
				tmp[cur]=1;
				res=max(res,query(h[cur],rt[i])+buc[h[cur]]);
				cur=a[cur];
			}
			sum-=res;
			while (tmp[cur]){
				tmp[cur]=0;
				buc[h[cur]]=0;
				cur=a[cur];
			}
		}
	printf("%lld\n",sum);
	return 0;
}
```

时间复杂度 $\mathcal{O}(n\log_2n)$

---

## 作者：ZillionX (赞：8)

## Description
有 $n$ 个人，第 $i$ 个人的分数为 $h_i$，修改 $h_i$ 需要 $c_i$ 元，要求 $h_i \ge h_{a_i}$，求最小修改费用。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210718134829554.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210718134842633.png)


## Solution
首先考虑根据题目给出的不等关系建图，我们发现 Subtask 1 和 Subtask 2 就是一棵内向树，进一步推导出无特殊限制时的图为基环内向树森林。

考虑针对 Subtask 1 设计一个 ${\rm O}(n^2)$ 的算法，容易发现应选择树形 DP。由于我们只需要判断修改后的 $h_i$ 与原 $h_i$ 的不等关系，所以可以将 $h_i$ 离散化，方便存储空间。

我们设 $f_{i,j}$ 为修改 $h_i$ 为 $j$ 后，满足 $i$ 子树中的不等关系所需的最小花费，设 $m$ 为离散化后的 $h_i$ 上界。可以推导出状态转移方程

$$f_{i,j}=c_i \times [j\not=h_i]+\sum_{k \in {\rm son}_i} \min_{j \le l \le m} \big\{f_{k,l}\big\}$$

这个算法虽然超时，但是是正确的，这启发我们进一步优化 DP 转移。优化到 ${\rm O}(n)$ 比较不现实，考虑优化到 ${\rm O}(n \log n)$。

我们发现 $f_{i,j}$ 中第二维有值的 $c_i \times [j\not=h_i]$ 占数组的大部分，如果用数据结构来维护的话会增加许多赘余的操作。但是 $c_{1} \sim c_n$ 的和是不变的，因此我们可以将状态转移方程变成这样：

$$f_{i,j}=\sum_{k \in {\rm son}_i} \min_{j \le l \le m} \big\{f_{k,l}\big\}-c_i \times [j=h_i]$$

然后再用 $c_{1} \sim c_n$ 的和加上 $\min f_{1,i}$，这样只需要进行单点减值，却有相同的效果，大大缩短了时间。

状态转移中只有简单的单点加值和区间查询最小值操作，不妨使用线段树维护 $f_{i,j}$ 中的第二维，给每个点开一棵线段树显然不可行，因此想到采用线段树合并。

找区间最小值时的区间是 $[j,m]$，然后再将每个子树中的最小值加起来。合并树 $u$ 和树 $v$ 时，我们可以记录 $u_{\min}$ 和 $v_{\min}$ 为两棵树各自的最小值。设当前结点为 $p$ 和 $q$，然后讨论 $p+v_{\min}$ 是否小于 $q+u_{\min}$。

$j$ 虽然不确定，但是右端点 $m$ 是固定的。因此我们在合并时不可以用平常的方式合并，而是先合并右子树，再合并左子树。（想一想，为什么）然后简单维护 $c_i \times [j=h_i]$ 的单点修改和合并时遇到一边空树的区间加标记就好了。

现在我们已经得到了针对 Subtask 1 和 Subtask 2 的 ${\rm O}(n \log n)$ 树形 DP 算法。我们发现它同样适用于内向树森林，只需要对每一棵树分别跑一遍 DP 就好了。

对于基环树，我们可以先做一次拓扑排序或者 Tarjan 算法找强连通分量。找出环后将其看作一个点，将与环相连的所有子树的线段树进行合并。容易发现环上每个点的最终值一定相等，而且是环上的某个值或者最小值 $1$。于是我们枚举环的最终值，同时在线段树上查询 $[h_i,m]$ 的最小值更新答案。至此本题得到完整解法。

### Warning
线段树合并的空间复杂度为 ${\rm O}(n \log n)$ 而非 ${\rm O}(n)$，还带点附加常数，因此请开 $\log_2 (2 \times 10^5) \times 3 \approx 54$ 倍空间。

## Code

```cpp
typedef long long LL;
const int N=2e5+5;

int n,NumE,rb,tot,a[N],Fir[N],d[N],in[N],dfn[N];
LL Ret,h[N],c[N];

inline LL Read() {
	LL x=0;
	char ch=getchar();

	while (ch<'0' || ch>'9') ch=getchar();
	
	while (ch>='0' && ch<='9') {
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
  
	return x;
}

struct Edge {int v,nxt;}E[N];

void AddE(int u,int v) {
	E[++NumE]={v,Fir[u]};
	Fir[u]=NumE;
}

namespace Seg {
	int cnt,rt[N],nt[N],ls[N*54],rs[N*54];
	LL d1,d2,v[N*54],t[N*54];
	
	void Chg(int x,LL u) {if (x) v[x]+=u,t[x]+=u;}
	
	void Up(int x) {v[x]=min(v[ls[x]],v[rs[x]]);}
	
	void Dw(int x) {
		if (!t[x]) return;
		Chg(ls[x],t[x]),Chg(rs[x],t[x]),t[x]=0;
	}
	
	int Upd(int x,int l,int r,int p,LL k) {
		if (!x) x=++cnt;
		
		if (l==r) {
			v[x]=k;
			return x;
		}
		
		Dw(x);
		
		int mid=(l+r)>>1;
		if (p<=mid) ls[x]=Upd(ls[x],l,mid,p,k);
		else rs[x]=Upd(rs[x],mid+1,r,p,k);
		
		Up(x);
		
		return x;
	}
	
	LL Qry(int x,int l,int r,int L,int R) {
		if (!x) return 0;
		if (L<=l && r<=R) return v[x];
		
		Dw(x);
		
		int mid=(l+r)>>1;
		LL Res=0;
		
		if (L<=mid) Res=min(Res,Qry(ls[x],l,mid,L,R));
		if (R>mid) Res=min(Res,Qry(rs[x],mid+1,r,L,R));
		
		return Res;
	}
	
	int Mrg_Dfs(int p,int q,int l,int r) {
		if (!p && !q) return 0;
		
		if (!p) {
			d2=min(d2,v[q]),Chg(q,d1);
			return q;
		}
		if (!q) {
			d1=min(d1,v[p]),Chg(p,d2);
			return p;
		}
		
		if (l==r) {
			d1=min(d1,v[p]),d2=min(d2,v[q]);
			
			if (v[p]+d2<=v[q]+d1) {
				v[p]+=d2;
				return p;
			}
			else {
				v[q]+=d1;
				return q;
			}
		}
		
		Dw(p),Dw(q);
		
		int mid=(l+r)>>1;
		
		rs[p]=Mrg_Dfs(rs[p],rs[q],mid+1,r);
		ls[p]=Mrg_Dfs(ls[p],ls[q],l,mid);
		
		Up(p);
		
		return p;
	}
	
	int Mrg(int x,int y) {
		d1=d2=0;
		return Mrg_Dfs(x,y,1,rb);
	}
}

using namespace Seg;

struct Cir {
	LL h,c;
	bool operator<(const Cir& rhs) const {return h<rhs.h;}
};
vector<Cir> cr[N];

void Dfs(int x) {
	for (int i=Fir[x];i;i=E[i].nxt) {
		Dfs(E[i].v);
		rt[x]=Mrg(rt[x],rt[E[i].v]);
	}

	rt[x]=Upd(rt[x],1,rb,h[x],Qry(rt[x],1,rb,h[x],rb)-c[x]);
}

void PushT(int x) {
	dfn[x]=tot;
	cr[tot].push_back({h[x],c[x]});
	if (!dfn[a[x]]) PushT(a[x]);
}

void TopS(int n) {
	queue<int> q;
	q=queue<int>();
	
	For(i,1,n) if (!in[i]) q.push(i);
	
	while (!q.empty()) {
		int u=q.front();
		q.pop();
		if (!--in[a[u]]) q.push(a[u]);
	}
	
	For(i,1,n) if (!dfn[i] && in[i])
		tot++,PushT(i);
}

void Calc(int n) {
	For(i,1,n) if (!in[i] && in[a[i]])
		Dfs(i),nt[dfn[a[i]]]=Mrg(nt[dfn[a[i]]],rt[i]);
	
	For(i,1,tot) {
		sort(cr[i].begin(),cr[i].end());
		
		LL Cnt=v[nt[i]],sh=cr[i][0].h,sc=cr[i][0].c;
		
		For(j,1,cr[i].size()-1)
			if (sh==cr[i][j].h) sc+=cr[i][j].c;
			else {
				Cnt=min(Cnt,Qry(nt[i],1,rb,sh,rb)-sc);
				sh=cr[i][j].h,sc=cr[i][j].c;
			}
		
		Cnt=min(Cnt,Qry(nt[i],1,rb,sh,rb)-sc);
		Ret+=Cnt;
	}
}

int main() {
	n=Read();
	
	For(i,1,n) {
		a[i]=Read(),h[i]=Read(),c[i]=Read();
		AddE(a[i],i),in[a[i]]++,d[i]=h[i],Ret+=c[i];
	}
	
	sort(d+1,d+n+1);
	rb=unique(d+1,d+n+1)-d-1;
	
	For(i,1,n) h[i]=lower_bound(d+1,d+rb+1,h[i])-d;
	
	TopS(n),Calc(n);
	
	printf("%lld",Ret);
	
	return 0;
}
```

---

## 作者：Henry__Chen (赞：6)

## 大意
给定 $n$ 点内向基环树，长度为 $n$ 的序列 $H, C$，在有向边 $u\to v$ 中要求 $H_u\le H_v$。你可以花费 $C_u$ 的代价使得 $H_u$ 任取，求使所有边合法的最小代价。

$n\le 2\times 10^5$
## Sol
给出一种不用线段树的做法。

考虑树上的情况怎么做。

首先原条件可以转化为钦定一些点的点权为 $H_u$，价值为 $C_u$，其他点任选的最大价值。

考虑动态规划，设 $f(u, i)$ 表示在 $u$ 的子树内所有点点权 $\ge i$ 的最大价值，则有转移
$$
f(u, i)=
\begin{cases}
\displaystyle\sum_{v\in son_u}f(v,i)&i > H_u\\
\displaystyle\max\left\{\sum_{v\in son_u}f(v,i), C_u+\sum_{v\in son_u}f(v,H_u)\right\}&i \le H_u\\
\end{cases}
$$
暴力转移是 $O(n^2)$ 的，考虑优化。

不难发现，$f(u,i)$ 是单调不升的，考虑维护 $f(u,i)$ 的差分。

我们利用 `std::map` 维护 $f(u,i)$ 的每一个拐点（即斜率不为 $0$），每次从儿子节点转移时先不考虑 $H_u$ 的限制启发式合并，最后加上 $H_u$ 的限制时同时更新找到一段区间 $[i,H_u]$ 的斜率为 $0$（这段区间被 $f(u,H_u)$ 更新），可以运用 `std::map::lower_bound` 和 `std::map::erase` 完成。

再考虑环上的情况，环上的 $H$ 必然相等，可以递增的枚举环上的点权 $H_u$，再用双指针去除掉树上小于 $H_u$ 的贡献，更新答案即可。

时间复杂度 $\mathcal O(n\log^2 n)$（`std::map` + 启发式合并）。

**Code**
```cpp
int n;
std::cin >> n;
std::vector<int> a(n), b(n), fa(n);
std::vector<std::vector<int>> e(n);
for (int i = 0; i < n; ++i) {
    std::cin >> fa[i] >> a[i] >> b[i];
    --fa[i];
    e[fa[i]].emplace_back(i);
}
std::vector<bool> vis(n), cir(n);
using i64 = long long;
using Info = std::map<int, i64>;
i64 ans = std::accumulate(b.begin(), b.end(), 0ll);
std::vector<Info> f(n);
for (int i = 0; i < n; ++i) {
    if (vis[i]) continue;
    std::vector<int> c;
    {
        int u = i;
        for (; !vis[u]; u = fa[u])
            vis[u] = true;
        for (; !cir[u]; u = fa[u])
            cir[u] = true, c.push_back(u);
    }
    auto Merge = [&](Info &a, Info &b) {
        if (a.size() < b.size()) a.swap(b);
        for (auto &[v, w] : b) a[v] += w;
    };
    std::function<void(int)> DFS = [&](int u) {
        vis[u] = true;
        for (auto &v : e[u]) {
            DFS(v);
            Merge(f[u], f[v]);
        }
        f[u][a[u]] += b[u];
        for (;;) {
            auto it = f[u].lower_bound(a[u]);
            if (it == f[u].begin()) break;
            --it;
            i64 _ = std::min(1ll * b[u], it -> second);
            b[u] -= _;
            it -> second -= _;
            if (it -> second == 0) f[u].erase(it);
            if (b[u] == 0) break;
        }
    };
    Info rt, cur;
    for (auto &u : c) {
        cur[a[u]] += b[u];
        for (auto &v : e[u])
            if (!cir[v]) {
                DFS(v);
                Merge(rt, f[v]);
            }
    }
    i64 ret = 0, mx = 0;
    for (auto &[v, w] : rt) ret += w;
    mx = ret;
    auto it = rt.begin();
    for (auto &[v, w] : cur) {
        for (; it != rt.end() && it -> first < v; ++it) ret -= it -> second;
        mx = std::max(mx, w + ret);
    }
    ans -= mx;
}
std::cout << ans << '\n';
```

---

## 作者：_LiWenX_ (赞：5)

感觉其他题解都有点复杂了，给一个直接无脑优化 dp 的做法。

我们把 $i\to a_i$ 建图，那么每一个点的出边点的权值都要比它小，这必然形成了一颗内向基环树。

首先肯定先考虑树咋做。

不难想到设 $f_{i,j}$ 表示节点 $i$ 的权值为 $j$ 时的答案。

那么转移就是 $f_{x,i}=[h_x\not=i]c_x+\sum\limits_{u} \min\limits_{j\ge i} f_{u,j}$。这看起来就很想用线段树做。

我们把转移看成两步，每一步单独处理。

首先 $f_{x,i}=\sum\limits_{u} \min\limits_{j\ge i} f_{u,j}$，如果得到了 $g_{u}$ 为 $f_u$ 的后缀最小值数组，那么直接线段树合并就好了，而且在这样操作后，$f_x$ 本身就是它的后缀最小值数组，所以你会发现，转移完的 $f_u$ 只差一点就和 $g_u$ 一样了，差的地方在于 $f_{u,h_u}$ 比其它地方少加上了一个 $c_u$，而前面和后面都是单调的，于是我们可以把前面这一段全部与 $f_{u,h_u}$ 取最小值，这样就可以使得 $f_u$ 变成 $g_u$，注意到我们对线段树的操作只是想求出全局最小值，所以这个修改是可以通过打标记和下传实现的，或者，你也可以线段树上二分，把不合法的那一段区间覆盖成 $f_{u,h_u}$，但是取最小值标记好写一些所以我实现了第一种做法。

看看第二步，$f_{x,i}=f_{x,i}^\prime+[i\not=h_x]c_x$，直接分段再区间加就好了，这是很简单的。

所以你只用实现一个区间加，区间取最小值，维护区间最小值，线段树合并的线段树就完成了树的部分。

考虑一个基环树的情况。

发现基环树上的点权全部相同，设环上点集为 $S$，把环上的边断开，然后跑树形 dp 后，发现如果换上点权为 $x$ 时，答案就是 $\sum\limits_{u\in S}f_{u,x}$。发现这又是一个线段树合并的形式，那就把环上的这些线段树也合并一下就好了，最后的答案就是合并完的线段树中的全局最小值。

注意这是基环森林。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int tree[200005*60],tag[200005*60],minn[200005*60];
signed ls[200005*60],rs[200005*60],cnt;
int build(int now){
	now=++cnt;
	tree[now]=ls[now]=rs[now]=0;
	tag[now]=0;
	minn[now]=1e18;
	return now;
}
void pushminn(int now,int k){
	tree[now]=min(tree[now],k);
	minn[now]=min(minn[now],k);
}
void pushadd(int now,int k){
	tree[now]+=k;
	tag[now]+=k;
	minn[now]+=k;
}
void pushdown(int now){
	if(!ls[now]){
		ls[now]=build(ls[now]);
	}
	if(!rs[now]){
		rs[now]=build(rs[now]);
	}
	if(tag[now]){
		pushadd(ls[now],tag[now]);
		pushadd(rs[now],tag[now]);
		tag[now]=0;
	}
	pushminn(ls[now],minn[now]);
	pushminn(rs[now],minn[now]);
	minn[now]=1e18;
}
void pushup(int now){
	tree[now]=min(tree[ls[now]],tree[rs[now]]);
}
#define mid ((l+r)>>1)
int addmin(int now,int l,int r,int x,int y,int k){
	if(!now){
		now=build(now);
	}
	if(l>=x&&r<=y){
		pushminn(now,k);
		return now;
	}
	pushdown(now);
	if(mid>=x) ls[now]=addmin(ls[now],l,mid,x,y,k);
	if(mid<y) rs[now]=addmin(rs[now],mid+1,r,x,y,k);
	pushup(now);
	return now;
}
int add(int now,int l,int r,int x,int y,int k){
	if(!now){
		now=build(now);
	}
	if(x>y) return now;
	if(l>=x&&r<=y){
		pushadd(now,k);
		return now;
	}
	pushdown(now);
	if(mid>=x) ls[now]=add(ls[now],l,mid,x,y,k);
	if(mid<y) rs[now]=add(rs[now],mid+1,r,x,y,k);
	pushup(now);
	return now;
}
int merge(int a,int b,int l,int r){
	if(!a||!b) return a^b;
	if(!ls[a]&&!rs[a]){
		pushadd(b,tree[a]);
		return b;
	}
	else if(!ls[b]&&!rs[b]){
		pushadd(a,tree[b]);
		return a;
	}
	pushdown(a),pushdown(b);
	ls[a]=merge(ls[a],ls[b],l,mid);
	rs[a]=merge(rs[a],rs[b],mid+1,r);
	pushup(a);
	return a;
}
int ask(int now,int l,int r,int x){
	if(l==r){
		return tree[now];
	}
	pushdown(now);
	if(mid>=x) return ask(ls[now],l,mid,x);
	return ask(rs[now],mid+1,r,x);
}
#undef mid
int a[200005],h[200005],c[200005],b[200005],tot;
int n;
struct edge{
	int from,to;
}e[200005<<1];int head[200005],siz;
void addedge(int x,int y){
	e[++siz].to=y;
	e[siz].from=head[x],head[x]=siz;
}
int root[200005];
int du[200005],ci[200005],vis[200005];
vector<int> vec;
void get(int now){
	vis[now]=1;
	vec.push_back(now);
	for(int i=head[now];i;i=e[i].from){
		int u=e[i].to;
		if(vis[u]) continue;
		get(u);
	}
}
void dfs(int now,int fa){
	for(int i=head[now];i;i=e[i].from){
		int u=e[i].to;
		if(u==fa) continue;
		if(ci[u]) continue;
		dfs(u,now);
		int val=ask(root[u],1,tot,h[u]);
		root[u]=addmin(root[u],1,tot,1,h[u],val);
		root[now]=merge(root[now],root[u],1,tot);
	} 
	root[now]=add(root[now],1,tot,1,h[now]-1,c[now]);
	root[now]=add(root[now],1,tot,h[now]+1,tot,c[now]);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>h[i]>>c[i];
		addedge(a[i],i);
		addedge(i,a[i]);
		b[i]=h[i];
		du[a[i]]++;
		du[i]++;ci[i]=1;
	}
	sort(b+1,b+1+n);
	tot=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++){
		h[i]=lower_bound(b+1,b+1+tot,h[i])-b;
	}
	queue<int> q;
	for(int i=1;i<=n;i++){
		if(du[i]==1){
			q.push(i);
			ci[i]=0;
		}
	}
	while(!q.empty()){
		int now=q.front();q.pop();
		for(int i=head[now];i;i=e[i].from){
			int u=e[i].to;
			du[u]--;
			if(du[u]==1){
				q.push(u);
				ci[u]=0;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(vis[i]) continue;
		vec.clear();
		get(i);
		vector<int> V;
		for(int u:vec){
			if(!ci[u]) continue;
			dfs(u,u);
			V.push_back(u);
		}
		for(int j=1;j<(int)V.size();j++){
			root[V[0]]=merge(root[V[0]],root[V[j]],1,tot);
		}
		ans+=tree[root[V[0]]];
	}
	cout<<ans;
}
/*
3
1 2 13
1 1 6
1 1 6
*/
```

---

## 作者：DeepSeaSpray (赞：2)

# P7563 [JOISC 2021 Day4] 最悪の記者 4 (Worst Reporter 4)

[[JOISC 2021 Day4] 最悪の記者 4 (Worst Reporter 4)](https://www.luogu.com.cn/problem/P7563)

略去题面。

首先需要对 $h$ 离散化，下文 $h$ 默认为离散化后的结果，记 $m$ 表示离散化后的数字在 $[1,m]$ 之间。

接下来，我们按照部分分思考。

## Subtask 1

如果按照 $i$ 到 $a_i$ 建图，可以发现建的是一颗内向树（儿子节点连向父亲）。即儿子的 $h$ 大于父亲的。

既然建出了树，考虑树形 DP。

设 $f(u,i)$ 表示 $u$ 取 $i$ 时，使其子树全部符合条件所需要的代价。

记 $v$ 为 $u$ 的儿子，有转移：

$$
f(u,i) = ( \sum_v ( \min_{i \leq j \leq m} f(v,j) ) ) + [ h_u \not= i ] c_i
$$

时间复杂度 $O(nm)$。

## Subtask 2

与 Subtask 1 性状相同，数据范围加大，考虑进行优化。

观察状态转移方程，发现类似一个区间最值与区间修改问题，考虑将每一个 $f(u)$ 的第二维用线段树记录。

那么转移的过程不难想到需要用线段树合并完成。我们还需要继续简化。

如果将答案提前加上 $\sum_{i=1}^n c_i$ 那么转移方程可以变成：

$$
f(u,i) = ( \sum_v ( \min_{i \leq j \leq m} f(v,j) ) ) - [ h_u = i ] c_i
$$

然后就变成了区间最值与单点修改问题，单点修改好处理，关键是区间最值与合并过程。

首先，对于每一个 $v$ 一个个往 $u$ 上合并即可，现在我们专注于两个线段树之间的合并。

即对于两个线段树 $u$,$v$ 如何求出所有的：

$$
\min_{i \leq j \leq m} f(u,j) + \min_{i \leq j \leq m} f(v,j)
$$

设：

$$
g(i) = \min \{ f(u,i) + \min_{i \leq j \leq m} f(v,j) , f(v,i) + \min_{i \leq j \leq m} f(u,j) \}
$$

那么：

$$
f(u,i) = \min_{i \leq j \leq m} g(i)
$$

现在只需要维护 $g$ 通过区间查询得到 $f$。

尽管 $i$ 是变的，但是上界 $m$ 没有变。我们其实就是需要维护后缀，所以我们要优先走右子树。

当只有一个子树合并的时候，我们先维护该子树的后缀，再将另一个子树的后缀加上去，注意这里涉及区间修改，需要懒标记。

当走到了叶子节点，同样的，先维护后缀，然后看是 $u$ 的值加上 $v$ 的后缀，还是反过来。

附上代码片段，方便理解。

```cpp
void Merge(int &u,int v){
    if(!u&&!v) return;
    else if(!u) mnv=min(mnv,a[v].v),Update(v,mnu),u=v;
    else if(!v) mnu=min(mnu,a[u].v),Update(u,mnv),u=u;
    else if(a[u].l==a[u].r) {
        mnu=min(mnu,a[u].v),mnv=min(mnv,a[v].v);
        if(a[u].v+mnv<a[v].v+mnu)
            a[u].v+=mnv,u=u;
        else a[v].v+=mnu,u=v;
    }
    else{
        Pushdown(u),Pushdown(v);
        Merge(a[u].rs,a[v].rs);
        Merge(a[u].ls,a[v].ls);
        Pushup(u);
    }
}
```

对于 $- [ h_u = i ] c_i$ 的处理，由于我们维护的是 $g$，所以需要先查询出 $f$ 然后覆盖。

其他的操作比较常规，具体见文末代码。

## Subtask 3

现在由树变成了基环森林。首先环内的点的 $h$ 相同，可以缩点，DP 之后，环上的点要不取其中某一个值，要不取所有 $f$ 中的最小值。

找环使用拓扑排序，由于其有向性，可以写出非常简洁的代码，参考文末代码注释。

最后答案全部相加即可，记得加上 $\sum_{i=1}^n c_i$（上文提及过这一步转换）。

## 值得注意的

- 记得开 long long
- $f(u,i)$ 为负数
- Merge 记得初始化后缀

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
#define ll long long
const int maxn=2*1e5+5;
int n;
int h[maxn],rh[maxn],rk;
unordered_map<int,int> mp;//离散化
int c[maxn];
ll ans;
namespace T{//线段树
	struct Tree{int l,r,ls,rs;ll v,t;};
	Tree a[maxn*60];
	int at;
	int rt[maxn],nrt[maxn];//节点的根，缩点的根
	ll mnu,mnv;//后缀
	inline void Update(int u,ll v){
		if(u) a[u].v+=v,a[u].t+=v;
	}
	inline void Pushup(int u){
		a[u].v=min(a[a[u].ls].v,a[a[u].rs].v);
	}
	inline void Pushdown(int u){//记得有懒标记
		if(a[u].t){
			Update(a[u].ls,a[u].t);
			Update(a[u].rs,a[u].t);
			a[u].t=0;
		}
	}
	void Insert(int &u,int l,int r,int p,ll v){//单点修改，这里选择直接覆盖
		if(!u) u=++at;
		a[u].l=l,a[u].r=r;
		if(a[u].l==a[u].r) a[u].v=v;
		else{
			int mid=(a[u].r-a[u].l)/2+a[u].l;
			Pushdown(u);
			if(p<=mid) Insert(a[u].ls,l,mid,p,v);
			else Insert(a[u].rs,mid+1,r,p,v);
			Pushup(u);
		}
	}
	void Merge(int &u,int v){//合并，正文中有详解
		if(!u&&!v) return;
		else if(!u) mnv=min(mnv,a[v].v),Update(v,mnu),u=v;
		else if(!v) mnu=min(mnu,a[u].v),Update(u,mnv),u=u;
		else if(a[u].l==a[u].r) {
			mnu=min(mnu,a[u].v),mnv=min(mnv,a[v].v);
			if(a[u].v+mnv<a[v].v+mnu)
				a[u].v+=mnv,u=u;
			else a[v].v+=mnu,u=v;
		}
		else{
			Pushdown(u),Pushdown(v);
			Merge(a[u].rs,a[v].rs);
			Merge(a[u].ls,a[v].ls);
			Pushup(u);
		}
	}
	ll Query(int u,int l,int r){//查询
		if(!u) return 0;
		else if(l<=a[u].l&&a[u].r<=r) return a[u].v;
		else{
			int mid=(a[u].r-a[u].l)/2+a[u].l;
			ll mn=0;
			Pushdown(u);
			if(l<=mid) mn=min(mn,Query(a[u].ls,l,r));
			if(mid<r) mn=min(mn,Query(a[u].rs,l,r));
			return mn;
		}
	}
	void RMerge(int &u,int v){//记得初始化前缀，注意 f 值为负数
		mnu=mnv=0;
		Merge(u,v);
	}
}
using namespace T;
namespace G{
	struct Edge{int u,v,nxt;};
	Edge e[maxn];//指向儿子
	int hd[maxn],et;
	int idg[maxn];//入度
	int to[maxn+5];//指向父亲
	queue<int> qi;
	int rng[maxn],tot;//环编号
	vector<pii> vp[maxn];//环内节点 h，c 信息，后面需要排序
	inline void Init(){
		memset(e,-1,sizeof(e));
		memset(hd,-1,sizeof(hd));
	}
	inline void Adde(int u,int v){
		e[et].u=u,e[et].v=v;
		e[et].nxt=hd[u],hd[u]=et++;
	}
	void Ring(int u){//找环（有向）
		rng[u]=tot;
		vp[tot].push_back(pii(h[u],c[u]));
		if(!rng[to[u]]) Ring(to[u]);
	}
	inline void Bfs(){//拓扑排序，找环
		int u;
		for(int i=1;i<=n;i++)
			if(!idg[i]) qi.push(i);
		while(!qi.empty()){
			u=qi.front(),qi.pop();
			if(!(--idg[to[u]])) qi.push(to[u]);
		}
		for(int i=1;i<=n;i++)
			if(!rng[i]&&idg[i]) tot++,Ring(i);
	}
	void Dfs(int u){//树上 DP
		int v;
		for(int i=hd[u];~i;i=e[i].nxt){
			v=e[i].v;
			Dfs(v);
			RMerge(rt[u],rt[v]);//合并，转移
		}
		Insert(rt[u],1,rk,h[u],Query(rt[u],h[u],rk)-c[u]);//单点修改
//		Modify(rt[u],1,rk,h[u],-c[u]);
	}
	inline void Calc(){
		ll res,sh,sc;
		for(int i=1;i<=n;i++)
			if(!idg[i]&&idg[to[i]])
				Dfs(i),RMerge(nrt[rng[to[i]]],rt[i]);//树上 DP ，合并到环上
		for(int i=1;i<=tot;i++){//统计环贡献的答案
			sort(vp[i].begin(),vp[i].end());//排序，使相同的 h 排在一起
			res=a[nrt[i]].v;//取全局最小
			sh=vp[i][0].fi,sc=vp[i][0].se;
			for(int j=1;j<(int)vp[i].size();j++){//选择 h 值
				if(sh==vp[i][j].fi) sc+=vp[i][j].se;
				else{
					res=min(res,Query(nrt[i],sh,rk)-sc);
					sh=vp[i][j].fi,sc=vp[i][j].se;
				}
			}
			res=min(res,Query(nrt[i],sh,rk)-sc);
			ans+=res;
		}
	}
}
using namespace G;
signed main(){
	Init();
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&to[i],&h[i],&c[i]);
		Adde(to[i],i),idg[to[i]]++;
		rh[i]=h[i],ans+=c[i];
	}
	sort(rh+1,rh+n+1);//离散化
	for(int i=1;i<=n;i++)
		if(!mp[rh[i]]) mp[rh[i]]=++rk;
	for(int i=1;i<=n;i++) h[i]=mp[h[i]];
	Bfs(),Calc();
	printf("%lld",ans);
	return 0;
}
```

## 鸣谢

[ZillionX的题解](https://www.luogu.com.cn/blog/ZillionX/solution-p7563)

给了我很大的帮助。

---

## 作者：7KByte (赞：2)

### 子任务 $1$ 

树，$n\le 5\times 10^3$ 。

考虑 $n^2$ 动态规划。

定义 $f[i][j]$ 表示已 $i$ 为根，根的值为 $j$ 的最小代价。

显然 $j$ 只能取出现过的数，一共 $n$ 种。

$$f[i][j]=c_i\times[j=h_i]+\sum \limits_{u\in son}\min\limits_{k\ge j}\{f[u][k]\}$$ 

直接转移即可，时间复杂度 $\mathcal{O}(n^2)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 5005
using namespace std;
int n,a[N],u[N],c[N],o[N],T,b[N],h[N],tot;long long f[N][N];
struct edge{int to,nxt;}e[N<<1];
void add(int x,int y){e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;}
void dfs(int x){
	int cur=lower_bound(b+1,b+T+1,u[x])-b;
	rep(i,1,T)f[x][i]=c[x];f[x][cur]=0;
	for(int i=h[x];i;i=e[i].nxt){
		dfs(e[i].to);long long mn=0x7fffffffffffffffLL;
		pre(j,T,1)mn=min(mn,f[e[i].to][j]),f[x][j]+=mn;
	}
}
int main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d%d%d",&a[i],&u[i],&c[i]),o[i]=u[i];
	sort(o+1,o+n+1);rep(i,1,n)if(o[i]!=o[i-1])b[++T]=o[i];
	rep(i,2,n)add(a[i],i);dfs(1);long long ans=0x7fffffffffffffffLL;
	rep(i,1,T)ans=min(ans,f[1][i]);printf("%lld\n",ans);
	return 0;
} 
```
### 子任务 $2$ 

树， $n\le 2\times 10^5$ 。

对于以 $i$ 为根的子树，$f[i][j]$ 中 $j$ 的取值一定是其子树中的值。

考虑线段树合并优化 $\rm DP$ 。

合并时先合并右子树，再合并左子树，记录 $u$ 表示当前第一颗树中的最小值，$v$ 表示第二颗树中的最小值。

对于线段树上每个节点，维护区间最小值，和区间加的标记。注意及时下传标记。

时间复杂度 $\mathcal{O}(n\log n)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define int long long
#define N 200005
using namespace std;
int n,h[N],tot,u[N],c[N],o[N],t,b[N],w[N];
struct edge{int to,nxt;}e[N];
void add(int x,int y){e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;}
struct node{
	int l,r,mn,tag;
}a[N<<6];
#define ls a[x].l
#define rs a[x].r
#define S a[x].mn
#define T a[x].tag
int idx,rt[N],pm,qm;
void pushup(int x,int val){if(x)S+=val,T+=val;}
void down(int x){if(T)pushup(ls,T),pushup(rs,T),T=0;}
int ins(int x,int l,int r,int pos,int val){
	if(!x){x=++idx,T=S=0;}
	if(l==r){S=val;return x;}
	down(x);int mid=(l+r)>>1;
	if(mid>=pos)ls=ins(ls,l,mid,pos,val);
	else rs=ins(rs,mid+1,r,pos,val);
	S=min(a[ls].mn,a[rs].mn);return x;
}
int merge(int x,int y,int l,int r){
	if(!x&&!y)return 0;
	if(!x){qm=min(qm,a[y].mn);pushup(y,pm);return y;}
	if(!y){pm=min(pm,a[x].mn);pushup(x,qm);return x;}
	if(l==r){
		pm=min(pm,a[x].mn);qm=min(qm,a[y].mn);
		if(a[x].mn+qm<=a[y].mn+pm){pushup(x,qm);return x;}
		pushup(y,pm);return y;
	}
	down(x);down(y);int mid=(l+r)>>1;
	rs=merge(a[x].r,a[y].r,mid+1,r);
	ls=merge(a[x].l,a[y].l,l,mid);
	S=min(a[ls].mn,a[rs].mn);return x;
}
int ask(int x,int l,int r,int L,int R){
	if(!x)return 0;
	if(L>=l&&R<=r)return S;
	down(x);
	int mid=(L+R)>>1,cur=0;
	if(mid>=l)cur=min(cur,ask(ls,l,r,L,mid));
	if(mid<r)cur=min(cur,ask(rs,l,r,mid+1,R));
	return cur;
}
void dfs(int x){
	rt[x]=ins(0,1,t+1,t+1,0);
	for(int i=h[x];i;i=e[i].nxt){
		dfs(e[i].to);pm=qm=0;
		rt[x]=merge(rt[x],rt[e[i].to],1,t+1);
		w[x]+=w[e[i].to];
	}
	int cur=lower_bound(b+1,b+t+1,u[x])-b;
	int now=ask(rt[x],cur,t+1,1,t+1);
	rt[x]=ins(rt[x],1,t+1,cur,now-c[x]);w[x]+=c[x];
}
signed main(){
	scanf("%lld",&n);
	rep(i,1,n){
		int x;scanf("%lld%lld%lld",&x,&u[i],&c[i]);
		o[i]=u[i];if(i>1)add(x,i);
	}
	sort(o+1,o+n+1);rep(i,1,n)if(o[i]!=o[i-1])b[++t]=o[i];
	dfs(1);
	printf("%lld\n",a[rt[1]].mn+w[1]);
	puts("No Copy");return 0;
}
```

### 子任务 $3$

基环内向树森林，$n\le 2\times 10^5$ 。

先一遍拓扑将环删掉，对于剩下的树跑子任务 $2$ 。

将环看成一个点，将它的子树合并到一颗线段树中。

最后枚举整个环的最终值，同时在线段树中区间查询最小值，更新答案。

环的最终值一定是环上某个点的值，或者是最小值 $1$ 。

时间复杂度 $\mathcal{O} (n\log n)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define int long long
#define N 200005
using namespace std;
int n,h[N],tot,u[N],c[N],o[N],t,b[N],w;
struct edge{int to,nxt;}e[N];
void add(int x,int y){e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;}
struct node{
	int l,r,mn,tag;
}a[N<<6];
#define ls a[x].l
#define rs a[x].r
#define S a[x].mn
#define T a[x].tag
int idx,rt[N],pm,qm,wt[N];
void pushup(int x,int val){if(x)S+=val,T+=val;}
void down(int x){if(T)pushup(ls,T),pushup(rs,T),T=0;}
int ins(int x,int l,int r,int pos,int val){
	if(!x){x=++idx,T=S=0;}
	if(l==r){S=val;return x;}
	down(x);int mid=(l+r)>>1;
	if(mid>=pos)ls=ins(ls,l,mid,pos,val);
	else rs=ins(rs,mid+1,r,pos,val);
	S=min(a[ls].mn,a[rs].mn);return x;
}
int change(int x,int l,int r,int pos,int val){
	if(!x){x=++idx,T=S=0;}
	if(l==r){S+=val;return x;}
	down(x);int mid=(l+r)>>1;
	if(mid>=pos)ls=ins(ls,l,mid,pos,val);
	else rs=ins(rs,mid+1,r,pos,val);
	S=min(a[ls].mn,a[rs].mn);return x;
}
int merge(int x,int y,int l,int r){
	if(!x&&!y)return 0;
	if(!x){qm=min(qm,a[y].mn);pushup(y,pm);return y;}
	if(!y){pm=min(pm,a[x].mn);pushup(x,qm);return x;}
	if(l==r){
		pm=min(pm,a[x].mn);qm=min(qm,a[y].mn);
		if(a[x].mn+qm<=a[y].mn+pm){pushup(x,qm);return x;}
		pushup(y,pm);return y;
	}
	down(x);down(y);int mid=(l+r)>>1;
	rs=merge(a[x].r,a[y].r,mid+1,r);
	ls=merge(a[x].l,a[y].l,l,mid);
	S=min(a[ls].mn,a[rs].mn);return x;
}
int ask(int x,int l,int r,int L,int R){
	if(!x)return 0;
	if(L>=l&&R<=r)return S;
	down(x);
	int mid=(L+R)>>1,cur=0;
	if(mid>=l)cur=min(cur,ask(ls,l,r,L,mid));
	if(mid<r)cur=min(cur,ask(rs,l,r,mid+1,R));
	return cur;
}
void dfs(int x){
	rt[x]=ins(0,1,t,t,0);
	for(int i=h[x];i;i=e[i].nxt){
		dfs(e[i].to);pm=qm=0;
		rt[x]=merge(rt[x],rt[e[i].to],1,t);
	}
	int cur=lower_bound(b+1,b+t+1,u[x])-b;
	int now=ask(rt[x],cur,t,1,t);
	rt[x]=ins(rt[x],1,t,cur,now-c[x]);
}
queue<int>q;int in[N],cnt,dfn[N],f[N];vector<pair<int,int> >cir[N];
void mark(int x){
	dfn[x]=cnt;
	cir[cnt].push_back(make_pair(lower_bound(b+1,b+t+1,u[x])-b,-c[x]));
	if(!dfn[f[x]])mark(f[x]);
}
void topo(){
	rep(i,1,n)if(!in[i])q.push(i);
	while(!q.empty()){
		int x=q.front();q.pop();
		in[f[x]]--;
		if(!in[f[x]])q.push(f[x]);
	}
	rep(i,1,n)if(!dfn[i]&&in[i])++cnt,mark(i);
}
void calc(){
	rep(i,1,n)if(!in[i]&&in[f[i]])dfs(i),qm=pm=0,wt[dfn[f[i]]]=merge(wt[dfn[f[i]]],rt[i],1,t);
	rep(i,1,cnt){
		sort(cir[i].begin(),cir[i].end());int mn=a[wt[i]].mn;
		int sum=cir[i][0].second,pre=cir[i][0].first;
		for(int j=1;j<(int)cir[i].size();j++){
			if(cir[i][j].first==pre)sum+=cir[i][j].second;
			else {
				mn=min(mn,ask(wt[i],pre,t,1,t)+sum);
				sum=cir[i][j].second,pre=cir[i][j].first;
			}
		}
		w+=min(mn,ask(wt[i],pre,t,1,t)+sum);
	}
}
signed main(){
	scanf("%lld",&n);
	rep(i,1,n){
		scanf("%lld%lld%lld",&f[i],&u[i],&c[i]);
		o[i]=u[i];w+=c[i];add(f[i],i);in[f[i]]++;
	}
	sort(o+1,o+n+1);rep(i,1,n)if(o[i]!=o[i-1])b[++t]=o[i];
	puts("No Copy");topo();calc();
	printf("%lld\n",w);
	return 0;
}
```

---

## 作者：GK0328 (赞：2)

### 线段树合并

从早上研究到晚上，终于干掉了这道题![](//啧.tk/fendou)。

对于题目中**rating**关系建图。

首先，每个点的出度为$1$，因此整张图是由多个基环内向树组成的，我们需要对于每个基环内向树计算答案，相加即可。

容易发现，在一棵基环内向树上，环上点的权值必然相等。

我们先考虑树的情况，需要满足子节点的权值$\ge$父节点的权值，可以发现最优方案中，父节点的权值一定是保持自己的权值不变，或者取子节点中的最小权值。然后再考虑叶子节点，显然它的权值要么保持不变，要么取$INF=10^9$。

因此在一棵大小为$n$的基环内向树中，节点权值取值范围最多只有$n+1$个数。我们可以进行$dp$，维护一个子树的根节点权值等于任意在其子树内节点权值（或$INF$）时的最小代价。考虑到从子节点推到父节点，比如两棵根节点权值分别为$s,t(s<t)$的子树，最终我们会将他们俩组成的答案合并到$s$中，这个可以在线段树合并的过程中实现。最终，对于一棵树，我们可以取出根节点的权值等于任意在其子树内的节点权值（或$INF$）情况下的最小代价。

因此，对于一棵基环内向树，我们先处理每棵子树，然后直接枚举每个权值来计算答案。对于枚举的权值$V$来说，每棵子树根节点的权值必须$\ge V$，我们可以默认根节点权值必须更改，然后对于那些根节点权值不更改的进行特判。

我们优化这一过程，从大到小枚举权值，然后对于每棵子树，不断拓展它的取值范围，这可以用优先队列进行动态维护。同样，对根节点权值不更改的情况进行特判。

然后我们就解决了这道题。

时间复杂度：$O(n \log n)$。

$Code:$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#define N 200005
#define M 10000005
#define ll long long
#define pr pair<int,ll>
#define mp make_pair
#define IT vector<int> :: iterator
#define pIT vector< pr > :: iterator
#define mIT map<int,bool> :: iterator
using namespace std;
const ll INF=1919191919191919;
int n,cc,a[N],h[N],c[N],d[N],rd[N],rt[N];
vector<int>e[N],val[N];
vector< pr >co[N];
queue<int>q;
map<int,bool>ht;
int z0,z[N];
bool vis[N];
int cnt,n1,n2;
ll ans,sz[N],g[N];
#define ls(p) tr[p].ch[0]
#define rs(p) tr[p].ch[1]
#define mn(p) tr[p].Mn
#define tag(p) tr[p].Tag
struct node
{
    int ch[2];
    ll Mn,Tag;
}tr[M];
void push_tag(int p,ll z)
{
    if (!p)
        return;
    mn(p)+=z,tag(p)+=z;
    mn(p)=min(mn(p),INF),tag(p)=min(tag(p),INF);
}
void push_down(int p)
{
    if (tag(p))
    {
        push_tag(ls(p),tag(p));
        push_tag(rs(p),tag(p));
        tag(p)=0;
    }
}
void update(int p)
{
    mn(p)=min(mn(ls(p)),mn(rs(p)));
}
void modify(int &p,int l,int r,int x,int y)
{
    if (!p)
        p=++cnt;
    if (l==r)
    {
        mn(p)+=y;
        return;
    }
    push_down(p);
    int mid(l+r >> 1);
    if (x<=mid)
        modify(ls(p),l,mid,x,y); else
        modify(rs(p),mid+1,r,x,y);
    update(p);
}
void modify2(int &p,int l,int r,int x,ll y)
{
    if (!p)
        p=++cnt;
    if (l==r)
    {
        mn(p)=y;
        return;
    }
    push_down(p);
    int mid(l+r >> 1);
    if (x<=mid)
        modify2(ls(p),l,mid,x,y); else
        modify2(rs(p),mid+1,r,x,y);
    update(p);
}
int combine(int x,int y,int l,int r,ll xm,ll ym)
{
    if (!x && y)
        push_tag(y,xm);
    if (x && !y)
        push_tag(x,ym);
    if (!x || !y)
        return x|y;
    if (l==r)
    {
        mn(x)=min(mn(x)+min(ym,mn(y)),mn(y)+min(xm,mn(x)));
        return x;
    }
    push_down(x),push_down(y);
    int mid(l+r >> 1);
    ls(x)=combine(ls(x),ls(y),l,mid,min(xm,mn(rs(x))),min(ym,mn(rs(y))));
    rs(x)=combine(rs(x),rs(y),mid+1,r,xm,ym);
    update(x);
    return x;
}
ll calc(int p,int l,int r,int x,int y)
{
    if (!p)
        return INF;
    if (l==x && r==y)
        return mn(p);
    push_down(p);
    int mid(l+r >> 1);
    if (y<=mid)
        return calc(ls(p),l,mid,x,y); else
    if (x>mid)
        return calc(rs(p),mid+1,r,x,y); else
        return min(calc(ls(p),l,mid,x,mid),calc(rs(p),mid+1,r,mid+1,y));
}
void dfs(int p,int l,int r,int u)
{
    if (!p)
        return;
    if (l==r)
    {
        co[u].push_back(mp(l,mn(p)));
        return;
    }
    push_down(p);
    int mid(l+r >> 1);
    dfs(ls(p),l,mid,u),dfs(rs(p),mid+1,r,u);
}
void dfs(int u)
{
    ht[h[u]]=true;
    vis[u]=true;
    sz[u]=c[u];
    int ct(0);
    for (IT it=e[u].begin();it!=e[u].end();++it)
    {
        int v(*it);
        if (v==n1 || v==n2)
            continue;
        ++ct;
    }
    if (!ct)
    {
        modify(rt[u],1,cc,h[u],0);
        modify(rt[u],1,cc,cc,c[u]);
    } else
    {
        for (IT it=e[u].begin();it!=e[u].end();++it)
        {
            int v(*it);
            if (v==n1 || v==n2)
                continue;
            dfs(v);
            sz[u]+=sz[v];
            if (!rt[u])
                rt[u]=rt[v]; else
                rt[u]=combine(rt[u],rt[v],1,cc,INF,INF);
        }
        ll zt(calc(rt[u],1,cc,h[u],cc));
        push_tag(rt[u],c[u]);
        modify2(rt[u],1,cc,h[u],zt);
    }
}
struct node2
{
    pIT it;
    int id;
    node2 () {}
    node2 (pIT It,int Id):it(It),id(Id) {}
    bool operator < (const node2 &A) const
    {
        return it->first<A.it->first;
    }
};
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
        scanf("%d%d%d",&a[i],&h[i],&c[i]),e[a[i]].push_back(i),++rd[a[i]],d[i]=h[i];
    sort(d+1,d+n+1);
    cc=unique(d+1,d+n+1)-d-1;
    for (int i=1;i<=n;++i)
        h[i]=lower_bound(d+1,d+cc+1,h[i])-d;
    ++cc;
    for (int i=1;i<=n;++i)
        if (!rd[i])
            q.push(i);
    while (!q.empty())
    {
        int u(q.front());
        vis[u]=true;
        q.pop();
        --rd[a[u]];
        if (!rd[a[u]])
            q.push(a[u]);
    }
    mn(0)=INF;
    for (int i=1;i<=n;++i)
        if (!vis[i])
        {
            z0=0;
            z[++z0]=i;
            for (int j=a[i];j!=i;j=a[j])
                z[++z0]=j;
            ll oc(0);
            priority_queue<node2>Q;
            for (int j=1;j<=z0;++j)
            {
                n1=(j==1)?z[z0]:z[j-1];
                n2=(j==z0)?z[1]:z[j+1];
                dfs(z[j]);
                modify(rt[z[j]],1,cc,h[z[j]],c[z[j]]);
                dfs(rt[z[j]],1,cc,j);
                val[h[z[j]]].push_back(j);
                g[j]=sz[z[j]];
                oc+=g[j];
                pIT it=co[j].end();
                --it;
                Q.push(node2(it,j));
            }
            ht[cc]=true;
            ll tas(INF);
            mIT mt=ht.end();
            --mt;
            for (;;--mt)
            {
                int x(mt->first);
                while (!Q.empty() && (Q.top().it->first)>=x)
                {
                    int u(Q.top().id);
                    pIT it(Q.top().it);
                    Q.pop();
                    oc-=g[u];
                    g[u]=min(g[u],it->second);
                    oc+=g[u];
                    if (it!=co[u].begin())
                        --it,Q.push(node2(it,u));
                }
                tas=min(tas,oc);
                ll kt(oc);
                for (IT it=val[x].begin();it!=val[x].end();++it)
                {
                    int u(*it);
                    ll vt(calc(rt[z[u]],1,cc,x,x));
                    kt+=min(0LL,vt-c[z[u]]-g[u]);
                }
                val[x].clear();
                tas=min(tas,kt);
                if (mt==ht.begin())
                    break;
            }
            ans+=tas;
            for (int j=1;j<=z0;++j)
                co[j].clear();
            ht.clear();
        }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：binbin_200811 (赞：2)

# [P7563 JOISC 2021 Day4 最悪の記者 4 (Worst Reporter 4)](https://www.luogu.com.cn/problem/P7563)

线段树合并好题，通过线段树合并特别的方式优化了树形 dp。

### 思路

根据图中的不等关系连边建图，不难发现最后的图将会是基环树森林和普通的树的森林，我们先考虑对于一棵树要怎么办。

将 $h_i$ 离散化，$m$ 为离散化上界，使用树形 dp。

设 $f_{i,j}$ 为将 $i$ 改成 $j$ 使 $i$ 的子树内满足不等关系的最小花费。
$$
f_{i,j}=c_i\times[j\neq h_i]+\sum_{k\in i.sons} \min_{j\leq t \leq m} f_{k,t}
$$
这个 dp 是超时的，但是是正确的，我们考虑优化 dp 转移。

我们发现每个都加上 $c_i$ 对我们操作有点麻烦，我们在最后求出答案是统一加上 $\sum c_i$，将方程改为
$$
f_{i,j}=\sum_{k\in i.sons}\min_{j\leq t\leq m} f_{k,t} -c_i*[j=h_i]
$$
为什么这样操作呢？

这样使得转移只有区间最小值查询和**单点**减法操作，考虑线段树维护 $f$ 值。

线段树的区间维护一个节点的状态的第二维，点取值维护对应区间的最小值，区间 $[l,r]$ 维护的是 $\min_{l\leq i\leq r} f_{u,i}$。

每个点开一棵肯定不现实，考虑线段树合并，每一次合并就相当于父亲和儿子做一次转移。

找区间最小值的区间是 $[j,m]$，合并树 $u$ 和树 $v$ 时，计 $u_{min}$ 和 $v_{min}$ 为各自的最小值（在区间 $[j,m]$ 内），对于节点 $p$ 和 $q$ 分类讨论 $p.val+v_{min}$ 和 $q.val+u_{min}$ 哪个最小（线段树 $u$ 的叶子区间 $[i,i]$ 维护的是 $\sum_{k\in u 已合并的儿子} \min_{i\leq l\leq m} f[k][l]$ 最后才会加上 $-c$ 的贡献；$u.min$ 的目的是区间 $[l,r]$ 不存在 $u$ 的节点时快速对区间 $u$ 赋值 $q.val+u_{min}$），将较小值设置即可。

由于最小值右端点固定，启发性的先合并右子树，便于维护最小值。

对于每个点的初始更新，在 $[h_i,h_i]$ 出加上 $-c_i$ 即可。

扩展到基环树，发现基环树的环上的点肯定是同一取值，且要么是 $1$ 要么是环上取值。

那么先求出基环树的环上节点的 $f$ 状态，最后枚举环上的点的取值即可。

#### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define lch(p) tree[p].lch
#define rch(p) tree[p].rch

const int maxn=2e5+5;

int rb;

struct linetree
{
    int tot;
    ll d1,d2;
    struct treenode{int lch,rch;ll lazy,mi;}tree[maxn*57];
    void push_down(int p)//下传懒标记
    {
        if(!tree[p].lazy) return ;
        ll &lazy=tree[p].lazy;
        if(lch(p)) tree[lch(p)].lazy+=lazy,tree[lch(p)].mi+=lazy;
        if(rch(p)) tree[rch(p)].lazy+=lazy,tree[rch(p)].mi+=lazy;
        lazy=0;
    }
    void updata(int p)
    {
        tree[p].mi=min(tree[lch(p)].mi,tree[rch(p)].mi);
    }
    void insert(int &p,int l,int r,int x,ll y)
    {
        if(l>x||r<x) return ;
        if(!p) p=++tot;
        if(l==r){tree[p].mi=y;return ;}
        push_down(p);
        int mid=(l+r)>>1;
        insert(lch(p),l,mid,x,y);
        insert(rch(p),mid+1,r,x,y);
        updata(p);
    }
    ll qry(int p,int l,int r,int lx,int rx)//查询区间最小值
    {
        if(!p) return 0;
        if(lx<=l&&r<=rx) return tree[p].mi;
        if(lx>r||rx<l) return 0;
        push_down(p);
        int mid=(l+r)>>1;
        return min(qry(lch(p),l,mid,lx,rx),qry(rch(p),mid+1,r,lx,rx));
    }
    void merge(int &p1,int p2,int l,int r)//合并
    {
        if(!p1&&!p2) return ;
        if(!p1)
        {
            d2=min(d2,tree[p2].mi);
            tree[p2].mi+=d1;
            tree[p2].lazy+=d1;
            p1=p2;
            return ;
        }
        else if(!p2)
        {
            d1=min(d1,tree[p1].mi);
            tree[p1].mi+=d2;
            tree[p1].lazy+=d2;
            return ;
        }
        if(l==r)
        {
            d1=min(d1,tree[p1].mi),d2=min(d2,tree[p2].mi);
            if(tree[p1].mi+d2<=tree[p2].mi+d1){tree[p1].mi=tree[p1].mi+d2;}
            else{tree[p1].mi=tree[p2].mi+d1;}
            return ;
        }
        push_down(p1);
        push_down(p2);
        int mid=(l+r)>>1;
        merge(rch(p1),rch(p2),mid+1,r);//启发式
        merge(lch(p1),lch(p2),l,mid);
        updata(p1);
    }
    void premrg(int &x,int y)
    {
        d1=d2=0;
        merge(x,y,1,rb);
    }
}T;
struct Edge
{
    int tot;
    int head[maxn];
    struct edgenode{int to,nxt;}edge[maxn*2];
    void add(int u,int v)
    {
        tot++;
        edge[tot].to=v;
        edge[tot].nxt=head[u];
        head[u]=tot;
    }
}E;

int n,tot;
int a[maxn],h[maxn],c[maxn],ind[maxn],d[maxn],dfn[maxn];
int rt[maxn],nt[maxn];

struct node{ll h,c;};
bool cmp(node a,node b){return a.h<b.h;}
vector<node>cr[maxn];

ll ans;

void pushcir(int u)//同一个环赋予同一编号
{
    dfn[u]=tot;
    cr[tot].push_back({h[u],c[u]});
    if(!dfn[a[u]]) pushcir(a[u]);
}
void gtp()//找环
{
    queue<int>que;
    while(!que.empty()) que.pop();
    for(int i=1;i<=n;i++) if(!ind[i]) que.push(i);
    while(!que.empty())
    {
        int u=que.front();que.pop();
        if(!--ind[a[u]]) que.push(a[u]);
    }
    for(int i=1;i<=n;i++)//可能有多个环，tot 是环数
        if(!dfn[i]&&ind[i]) tot++,pushcir(i);
}
void dfs(int u)//求 u 的状态
{
    for(int i=E.head[u];i;i=E.edge[i].nxt)
    {
        int v=E.edge[i].to;
        dfs(v);
        T.premrg(rt[u],rt[v]);//合并儿子和自己
    }
    T.insert(rt[u],1,rb,h[u],T.qry(rt[u],1,rb,h[u],rb)-c[u]);
    //insert 更改区间 [h[u],h[u]] 的值
}
void calc()
{
    for(int i=1;i<=n;i++) if(!ind[i]&&ind[a[i]])//求环的状态
        dfs(i),T.premrg(nt[dfn[a[i]]],rt[i]);
    for(int i=1;i<=tot;i++)
    {
        sort(cr[i].begin(),cr[i].end(),cmp);
        ll cnt=T.tree[nt[i]].mi,sh=cr[i][0].h,sc=0;
        for(node v:cr[i])
        {
            if(v.h==sh) sc+=v.c;
            else
            {
                cnt=min(cnt,T.qry(nt[i],1,rb,sh,rb)-sc);
                sh=v.h,sc=v.c;
            }
        }
        cnt=min(cnt,T.qry(nt[i],1,rb,sh,rb)-sc);
        ans+=cnt;
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&a[i],&h[i],&c[i]);
        E.add(a[i],i);
        ind[a[i]]++;
        d[i]=h[i];
        ans+=c[i];
    }
    sort(d+1,d+n+1);
    rb=unique(d+1,d+n+1)-d-1;
    for(int i=1;i<=n;i++) h[i]=lower_bound(d+1,d+rb+1,h[i])-d;//离散化
    gtp();
    calc();
    printf("%lld",ans);
}
```

---

## 作者：_Ch1F4N_ (赞：1)

从下午一直写到了晚上。

首先不难发现假若连边 $a_i \to i$ 那么原图构成了基环树森林，考虑每个连通块要么是树要么是基环树。

假若是树，考虑设计状态 $dp_{u,i}$ 表示点 $u$ 取 $i$ 且它的子树内的关系被满足的最小花费，有 $dp_{u,i} = \sum_{v} \min(dp_{v,j})(j \geq i) + [i \not= h_u] \times c_u$。

最后的一项可以最后提出来做区间加区间维护，前面的合并与转移过程中维护一个最小的后缀最小值，但是鉴于这题只有单点修改和全局加的特性，我们提供一个全新的思路。

考虑假若没有最后一项，那么我们的 $dp_{u}$ 一定是一个单调的数组，就只用维护区间最小值即可，但是加入最后一项后，区间 $[1,h_u]$ 内的单调性会被打破，考虑这时直接用后缀最小值数组替换原数组，等价于 $[1,h_u]$ 内的 $dp_{u,j}$ 与 $dp_{u,h_u}$ 取最小值，考虑在线段树上维护矩阵或者变换 $x \to \min(x+a,b)$ 即可。

最后考虑基环树，不妨将环上所有点合并产生新的树去做转移，发现只有根处转移式的最后一项变成了多项，考虑维护合并前取到环上不同的点的不同贡献即可。

最后我们就在时空 $O(n \log n)$ 的复杂度内解决了这个问题。

顺带一提，合并带标记的线段树时要是某个点同时没有左右儿子就需要把它的标记合并到另一个点上。

还有，这题卡空间，注意实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
const long long inf = 1e15+114;
const int maxv = 1e9+114;
struct Node{
    int ls,rs;
    long long Min,getMin,tag;
    Node(){
        Min=getMin=inf;
        ls=rs=tag=0;
    }
}tr[maxn*70];
int tot;
void pushup(int cur){
    tr[cur].Min=min(tr[tr[cur].ls].Min,tr[tr[cur].rs].Min);
}
void pushdown(int cur){
    if(tr[cur].ls==0) tr[cur].ls=++tot;
    if(tr[cur].rs==0) tr[cur].rs=++tot;
    tr[tr[cur].ls].Min+=tr[cur].tag;
    tr[tr[cur].ls].tag+=tr[cur].tag;
    tr[tr[cur].ls].getMin+=tr[cur].tag;
    tr[tr[cur].ls].getMin=min(tr[tr[cur].ls].getMin,tr[cur].getMin);
    tr[tr[cur].ls].Min=min(tr[tr[cur].ls].Min,tr[cur].getMin);
    tr[tr[cur].rs].Min+=tr[cur].tag;
    tr[tr[cur].rs].tag+=tr[cur].tag;
    tr[tr[cur].rs].getMin+=tr[cur].tag;
    tr[tr[cur].rs].getMin=min(tr[tr[cur].rs].getMin,tr[cur].getMin);
    tr[tr[cur].rs].Min=min(tr[tr[cur].rs].Min,tr[cur].getMin);
    tr[cur].tag=0;
    tr[cur].getMin=inf;
    return ;
}
int merge(int u,int v,int lt,int rt){
    if(lt==rt){
        tr[u].Min=tr[u].Min+tr[v].Min;
        return u;
    }
    if(tr[u].ls==0&&tr[u].rs==0){
        tr[v].Min+=tr[u].Min;
        tr[v].tag+=tr[u].Min;
        tr[v].getMin+=tr[u].Min;
        tr[v].getMin=min(tr[v].getMin,inf);
        return v;
    }
    if(tr[v].ls==0&&tr[v].rs==0){
        tr[u].Min+=tr[v].Min;
        tr[u].tag+=tr[v].Min;
        tr[u].getMin+=tr[v].Min;
        tr[u].getMin=min(tr[u].getMin,inf);
        return u;
    }
    pushdown(u);
    pushdown(v);
    int mid=(lt+rt)>>1;
    tr[u].ls=merge(tr[u].ls,tr[v].ls,lt,mid);
    tr[u].rs=merge(tr[u].rs,tr[v].rs,mid+1,rt);
    pushup(u);
    return u;
}
void getMin(int cur,int lt,int rt,int l,int r,long long c){
    if(rt<l||r<lt) return ;
    if(l<=lt&&rt<=r){
        tr[cur].Min=min(tr[cur].Min,c);
        tr[cur].getMin=min(tr[cur].getMin,c);
        return ;
    }
    int mid=(lt+rt)>>1;
    pushdown(cur);
    getMin(tr[cur].ls,lt,mid,l,r,c);
    getMin(tr[cur].rs,mid+1,rt,l,r,c);
    pushup(cur);
}
void add(int cur,int lt,int rt,int l,int r,long long c){
    if(rt<l||r<lt) return ;
    if(l<=lt&&rt<=r){
        tr[cur].Min+=c;
        tr[cur].tag+=c;
        tr[cur].getMin+=c;
        return ;
    }
    pushdown(cur);
    int mid=(lt+rt)>>1;
    add(tr[cur].ls,lt,mid,l,r,c);
    add(tr[cur].rs,mid+1,rt,l,r,c);
    pushup(cur);
}
long long ask(int cur,int lt,int rt,int l,int r){
    if(rt<l||r<lt) return inf;
    if(l<=lt&&rt<=r) return tr[cur].Min;
    pushdown(cur);
    int mid=(lt+rt)>>1;
    return min(ask(tr[cur].ls,lt,mid,l,r),ask(tr[cur].rs,mid+1,rt,l,r));
}
vector<int> E[maxn];
long long C[maxn];
int root[maxn];
int H[maxn],n;
vector<int> edge[maxn],Fedge[maxn];
vector< pair<int,long long> > other[maxn];
long long sum[maxn];
void DP(int u,int fa){
    root[u]=++tot;
    getMin(root[u],1,maxv,1,maxv,0);
    for(int v:E[u]){
        DP(v,u);
        long long val=ask(root[v],1,maxv,H[v],H[v]);
        getMin(root[v],1,maxv,1,H[v],val);
        root[u]=merge(root[u],root[v],1,maxv);
    }
    add(root[u],1,maxv,1,maxv,C[u]+sum[u]);
    add(root[u],1,maxv,H[u],H[u],-C[u]);
    for(pair<int,int> v:other[u]) add(root[u],1,maxv,v.first,v.first,-v.second);
}
vector<int> rt;
int In[maxn],Out[maxn];
int vis[maxn];
int fa[maxn];
int found(int u){
    return fa[u]=(fa[u]==u?u:found(fa[u]));
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        int fa;
        cin>>fa>>H[i]>>C[i];
        if(i==fa) continue;
        edge[fa].push_back(i);
        Fedge[i].push_back(fa);
        In[i]++;
        Out[fa]++;
    }
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(Out[i]==0){
            q.push(i);
        }
    }
    while(q.size()>0){
        int u=q.front();
        q.pop();
        vis[u]=1;
        for(int v:Fedge[u]){
            Out[v]--;
            if(Out[v]==0) q.push(v);
        }
    }
    for(int i=1;i<=n;i++){
        if(vis[i]==0||In[i]==0) rt.push_back(i);
    }

    for(int x:rt) fa[x]=x;
    for(int u:rt){
        for(int v:edge[u]){
            if(vis[u]==0&&vis[v]==0){
                if(found(u)!=found(v)){
                    fa[found(v)]=found(u);
                }
            }
        }
    }
    for(int x:rt){
        if(found(x)!=x){
            other[found(x)].push_back(make_pair(H[x],C[x]));
            sum[found(x)]+=C[x];
        }
    }
    for(int u=1;u<=n;u++){
        for(int v:edge[u]){
            if(vis[u]==0&&vis[v]==1) E[found(u)].push_back(v);
            else if(vis[u]==1||vis[v]==1) E[u].push_back(v);
        }
    }
    for(int x:rt) if(found(x)==x) DP(x,0);
    long long ans=0;
    for(int x:rt){
        if(found(x)==x) ans+=tr[root[x]].Min;
    }
    cout<<ans<<'\n';
    return 0;
}
```


---

## 作者：_zuoqingyuan (赞：0)

写了一天，终于 AC 了。

# 思路分析

对于每一个 $i$，连一条 $i\to a_i$ 的边，得到一个基环森林，对于每一个节点 $u$ 及其子树中一点 $v$ 来说，必须满足 $h_u>h_v$，修改 $h_u$ 的代价为 $c_u$。为了方便处理，我们连 $a_i\to i$ 的边，则点的父亲的 $h$ 应该小于儿子的 $h$。 

注意任何一对祖先和子孙都具有这样的关系，只需要通过儿子 $h$ 就可以计算父亲的情况，可以考虑动态规划。对于基环树，可以在此基础上分类讨论一下。

## $O(n^2)$

先考虑一下树。

假设 $dp'_{u,i}$ 表示 $u$ 为根子树中最小的 $h_v$ 为 $i$ 的情况下，使整颗子树合法所需要付出的最小代价。

我们先不考虑点 $u$，而是只考虑其每一个儿子 $v$。则有：

$$dp'_{u,i}\gets \min\{dp'_{u,i}+\min_{j\ge i} dp'_{v,j},\min_{j\ge i}dp'_{u,j}+dp'_{v,i}\}$$

在上述过程完成后，再考虑加入点 $u$ 的贡献，实际上，若 $u$ 为根子树中最小的 $h_v$ 为 $i$，则等价于 $h_u=i$。

$$dp'_{u,i}\gets [h_u\ne i]c_u+\min_{j\ge i}dp'_{u,j}$$

$h_u\ne i$ 不好处理，我们改变定义，向将 $u$ 子树中每个点的点权都修改，再假设 $dp_{u,i}$ 表示 $u$ 为根子树中最小的 $h_v$ 为 $i$，且使整颗子树合法的情况下，能避免付出的最大代价。同理可得：

$$dp_{u,i}\gets \max\{dp_{u,i}+\max_{j\ge i} dp_{v,j},\max_{j\ge i}dp_{u,j}+dp_{v,i}\}$$

$$dp_{u,i}\gets [h_u=i]c_u+\max_{j\ge i}dp_{u,j}$$

同时记录每个子树内 $c$ 的和 $S_u$，则有 $dp'_{u,i}=S_u-dp_{u,i}$。

直接做树上 dp，利用两个额外的变量辅助转移，即可做到 [$O(n^2)$](https://uoj.ac/submission/748518)。

考虑一下基环树，对于环上的 $m$ 个点 $a_{1\sim m}$，满足 $h_{a_1}\le h_{a_2}\le \dots \le h_{a_m}\le h_{a_1}$，注意到 $h_{a_1}\le h_{a_1}$ 实际上就是 $h_{a_1}=h_{a_1}$，可以推出环上 $n$ 个点 $h$ 值均相等。

我们先将环上每个点挂在环外的树的部分处理出来，让后将 $m$ 个点的 $dp$ 数组合并到同一个点的 $dp$ 上，然后枚举这个环上所有点最后的取值，即可计算出答案。

代码还是上面的那个链接。

## $O(n\log n)$

还是先考虑树。

注意到 dp 数组是二维的，每一维大小都是 $n$，空间上无法承受，仔细观察 dp 数组，不难发现每个点内只有少量的状态是有效的，其他的状态都可以用这些状态代替。

这种问题的一个经典做法是用动态开点线段树代替 dp 数组，用线段树合并来进行 dp 的转移，不懂的可以看一下 [Magic Tree](https://www.luogu.com.cn/problem/P6847) 这道题。

本题仍然可以套用同样的方法处理树的情况，但注意合并的顺序是先合并右儿子再合并左儿子。

考虑一下基环树。

注意到环上每个点的 $h$ 值都一样，我们可以把一整个环看做一个新点，并直接将环上点儿子的线段树直接合并到新点上，此时这颗线段树上 $dp_{u,i}$ 即为整颗基环树，在不考虑环上点贡献，最小的 $h_v=i$ 且整颗基环树合法
的情况下，可以避免的最大花费。

如何考虑加入环上点的贡献，假设要将所有环上的点都修改为 $k$，则考虑两部分贡献：

1. 环上的贡献：假设 $H_i$ 表示所有 $h_u=i$ 的环上的点的代价和（可以预处理），如果整个环都变为 $k$，则环上不用操作，可以避免代价的点只有原本 $h_u=k$ 的点，即 $H_k$。

2. 其他的贡献：环上的点明确全部为 $k$，则其他的必须大于等于 $k$，即为 $\max_{j\ge k}dp_{u,j}$，直接查询线段树区间和即可。

显然不能暴力枚举 $k$，有用的 $k$ 值要么是环上某些点原本的 $h_u$，要么是 $1$。

对于每一个基环树独立处理一遍即可。[record](https://uoj.ac/submission/748537)。

如有错误，请指出。

---

## 作者：activeO (赞：0)

早上随到的题，调了一个下午还多，早上的题还没改，快调吐了。

## 题意

给你一个内向基环树森林，给定点的权值 $ a_i $ 和修改他的权值成任意数的代价 $ c_i $，你可以进行若干次修改，问最小代价使得每个点的权值都大于等于他指向的点。

## 思路

首先显然每棵基环树互不影响，我们计算每棵基环树的最小代价相加。

然后基环树的经典套路，把他看成每个环的节点上吊了一棵树，先处理树然后再处理环。

树上有个显然的 $ dp $，定义 $ f_{u,i} $ 表示 $ u $ 的权值修改为 $ i $，使他的子树满足条件的最小代价，有：

$$ f_{u,i} \leftarrow \sum_{v \in son(u)} \min_{j=i}^{m} f_{v,j} + [a_u \neq i]c_u $$

然后提前加上所有的 $ c_u $，进行一步转化：

$$ f_{u,i} \leftarrow \sum_{v \in son(u)} \min_{j=i}^{m} f_{v,j} - [a_u = i] c_u $$

然后离散化后，就可以用线段树优化了，观察到前面都是后缀查询，所以前面一部分就线段树合并维护，先处理后缀维护后缀的最小值即可，后面其实就是线段树的单点修改。

然后接着考虑环，环上的点显然权值要求都相等，所以我们可以枚举他等于环上哪些点的权值（或都不是），计算取最小即可。

## 细节

- 下传标记和线段树合并的时候一定要注意不能给 $ 0 $ 点修改了，不然之后 $ pushup $ 的时候会错。
- 每次计算一棵新的基环树时要清空。
- $ \text{define int long long} $ 会炸空间。
- 合并前清空后缀标记。
- 环有可能是自环也有可能是二元环，判环时要注意。

## 代码

```cpp
// Problem: P7563 [JOISC 2021 Day4] 最悪の記者 4 (Worst Reporter 4)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7563
// Memory Limit: 500 MB
// Time Limit: 4000 ms

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn=2e5+5;
struct edge{
	int to,nxt;
}e[maxn<<1];
int head[maxn],len,tot=0;
ll minu,minv;
struct Tree{
	ll tr[maxn*60],tag[maxn*60];
	int lc[maxn*60],rc[maxn*60];
	void pushup(int now){
		tr[now]=min(tr[lc[now]],tr[rc[now]]);
	}
	void pushdown(int now){
		if(!tag[now]) return;
		// if(!lc[now]) lc[now]=++tot;
		// if(!rc[now]) rc[now]=++tot;
		if(lc[now]){
			tag[lc[now]]+=tag[now];
			tr[lc[now]]+=tag[now];
		}
		if(rc[now]){
			tr[rc[now]]+=tag[now];
			tag[rc[now]]+=tag[now];
		}
		tag[now]=0;
	}
	int update(int now,int l,int r,int x,ll v){
		if(!now) now=++tot;
		if(l==r){
			tr[now]=v;
			return now;
		}
		pushdown(now);
		int mid=(l+r)>>1;
		if(x<=mid) lc[now]=update(lc[now],l,mid,x,v);
		else rc[now]=update(rc[now],mid+1,r,x,v);
		pushup(now);
		return now;
	}
	ll query(int now,int l,int r,int ql,int qr){
		if(!now) return 0;
		if(ql<=l&&qr>=r) return tr[now];
		int mid=(l+r)>>1;
		ll res=0;
		pushdown(now);
		if(ql<=mid) res=min(res,query(lc[now],l,mid,ql,qr));
		if(qr>mid) res=min(res,query(rc[now],mid+1,r,ql,qr));
		return res;
	}
	int merge(int u,int v,int l,int r){
		if(!u){
			minv=min(minv,tr[v]);
			if(v){
				tr[v]+=minu;
				tag[v]+=minu;
			}
			return v;
		}
		// printf("pp%d %lld %lld %lld %lld\n",u,v,r,minu,minv);
		if(!v){
			minu=min(minu,tr[u]);
			tr[u]+=minv;
			tag[u]+=minv;
			return u;
		}
		if(l==r){
			minu=min(minu,tr[u]);
			minv=min(minv,tr[v]);
			tr[u]=min(tr[u]+minv,tr[v]+minu);
			return u;
		}
		pushdown(u);
		pushdown(v);
		int mid=(l+r)>>1;
		rc[u]=merge(rc[u],rc[v],mid+1,r);
		lc[u]=merge(lc[u],lc[v],l,mid);
		pushup(u);
		return u;
	}
	// int merge2(int u,int v,int l,int r){
		// // printf("pq%d %d %d %d\n",u,v,l,r);
		// if(!u){
			// minv=min(minv,tr[v]);
			// tr[v]=minv;
			// return v;
		// }
		// if(!v) return u;
		// if(l==r){
			// minv=min(minv,tr[v]);
			// tr[u]+=minv;
			// return u;
		// }
		// pushdown(u);
		// pushdown(v);
		// int mid=(l+r)>>1;
		// rc[u]=merge2(rc[u],rc[v],mid+1,r);
		// lc[u]=merge2(lc[u],lc[v],l,mid);
		// pushup(u);
		// return u;
	// }
}tt;
int rt[maxn],n;
ll a[maxn],c[maxn],lsh[maxn],res=0;
int st[maxn],top=0,ph[maxn],cnt=0;
bool inst[maxn],flag=0,bk[maxn];
int llen=0,ss;
bool vis[maxn];

inline void init(){
	memset(head,-1,sizeof(head));
	len=1;
}
void add(int u,int v){
	e[++len].to=v;
	e[len].nxt=head[u];
	head[u]=len;
}

void dfs1(int u,int ff){
	st[++top]=u;
	inst[u]=1;
	for(int i=head[u];i!=-1;i=e[i].nxt){
		int v=e[i].to;
		if((i^1)==ff) continue;
		// printf("ll%d %lld\n",u,v);
		if(inst[v]){
			while(top&&st[top]!=v){
				bk[st[top]]=1;
				ph[++cnt]=st[top];
				top--;
			}
			top--;
			ph[++cnt]=v;
			bk[v]=1;
			flag=1;
			return;
		}
		dfs1(v,i);
		if(flag) return;
	}
	top--;
	inst[u]=0;
}

void dfs2(int u,int ff){
	vis[u]=1;
	for(int i=head[u];i!=-1;i=e[i].nxt){
		int v=e[i].to;
		if((i^1)==ff||bk[v]) continue;
		dfs2(v,i);
		minu=minv=0;
		rt[u]=tt.merge(rt[u],rt[v],1,llen);
		// printf("kk%lld %lld\n",u,v);
		// for(int i=1;i<=llen;i++){
			// printf("%lld %lld\n",i,tt.query(rt[u],1,llen,i,i));
		// }
	}
	if(u!=ss) rt[u]=tt.update(rt[u],1,llen,a[u],tt.query(rt[u],1,llen,a[u],llen)-c[u]);
	// printf("kk%lld\n",u);
	// for(int j=1;j<=llen;j++) printf("%lld ",tt.query(rt[u],1,llen,j,j));
	// puts("");
}

bool cmp(int x,int y){
	return a[x]<a[y];
}

signed main(){
	
	init();
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int v;
		scanf("%d %lld %lld",&v,&a[i],&c[i]);
		add(i,v);
		// printf("%lld %lld\n",i,v);
		add(v,i);
		lsh[++llen]=a[i];
		res+=c[i];
	}
	
	// printf("kk%lld\n",res);
	
	sort(lsh+1,lsh+llen+1);
	llen=unique(lsh+1,lsh+llen+1)-lsh-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(lsh+1,lsh+llen+1,a[i])-lsh;
	
	// printf("kk%d\n",llen);
	// for(int i=1;i<=n;i++) printf("%lld %lld\n",i,a[i]);
	
	// printf("%lld\n",cnt);
	// for(int i=1;i<=cnt;i++) printf("kk%d\n",ph[i]);
	
	for(int i=1;i<=n;i++){
		if(vis[i]) continue;
		top=0;
		cnt=0;
		flag=0;
		dfs1(i,0);
		// printf("pp%lld\n",cnt);
		rt[0]=0;
		for(int j=1;j<=cnt;j++){
			ss=ph[j];
			dfs2(ph[j],0);
			// printf("kk%lld %lld %lld\n",ph[j],rt[ph[j]],tt.query(rt[ph[j]],1,llen,1,llen));
			minu=minv=0;
			rt[0]=tt.merge(rt[0],rt[ph[j]],1,llen);
		}
		// puts("here");
		// for(int j=1;j<=llen;j++) printf("%lld ",tt.query(rt[0],1,llen,j,j));
		sort(ph+1,ph+cnt+1,cmp);
		// for(int j=1;j<=cnt;j++) printf("%lld %lld\n",ph[j],a[ph[j]]);
		// puts("");
		ll ret=tt.query(rt[0],1,llen,1,llen),tmp=c[ph[1]];
		// printf("%lld\n",ret);
		for(int j=2;j<=cnt;j++){
			if(a[ph[j]]==a[ph[j-1]]) tmp+=c[ph[j]];
			else{
				ret=min(ret,tt.query(rt[0],1,llen,a[ph[j-1]],llen)-tmp);
				tmp=c[ph[j]];
			}
		}
		ret=min(ret,tt.query(rt[0],1,llen,a[ph[cnt]],llen)-tmp);
		// printf("here%lld : %lld %lld\n",rt[0],tt.query(rt[0],1,llen,1,llen),ret);
		res+=ret;
	}
	
	printf("%lld\n",res);
	
	return 0;
}
```



---

