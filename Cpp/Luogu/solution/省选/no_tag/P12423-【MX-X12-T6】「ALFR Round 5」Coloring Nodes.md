# 【MX-X12-T6】「ALFR Round 5」Coloring Nodes

## 题目背景

原题链接：<https://oier.team/problems/X12F>。

## 题目描述

给定一棵 $n$ 个点的树，初始时所有结点为白色。

你可以花费 $w_u$ 的代价将结点 $u$ 染黑。

有 $q$ 次询问，每次询问形如 `u l r`。对于每次询问，你需要花费尽可能小的代价，将一些结点染黑，使得点 $u$ 到**叶结点** $v$ 的简单路径上存在黑色结点，**当且仅当** $l \le v \le r$，并输出最小代价。

## 说明/提示

**【样例解释 #1】**  

该样例满足特殊性质 A。  

对于第一次询问，染黑 $2$ 号点，最小代价为 $3$；  

对于第二次询问，染黑 $3$ 号点，最小代价为 $1$；

对于第三次询问，染黑 $1$ 号点，最小代价为 $4$；

对于第四次询问，染黑 $3$ 号点，最小代价为 $1$。

**【样例解释 #2】**  

该样例满足特殊性质 B。

对于第一次询问，染黑 $3$ 号点，最小代价为 $1$； 

对于第二次询问，染黑 $2,4,6,7$ 号点，最小代价为 $-19$；  

对于第三次询问，可证明没有可行的染色方案。

**【数据范围】**

**本题使用捆绑测试。**

对于 $100\%$ 的数据，$1 \le n, q \le 2 \times 10^5$，$|w_u| \le 10^9$，$1 \le u, v \le n$，$1 \le l \le r \le n$。

|子任务编号|$n \le$|$q \le$|特殊性质|分值|子任务依赖|
|:-:|:-:|:-:|:-:|:-:|:-:|
|$1$|$20$|$20$|无|$5$|-|
|$2$|$20$|$2 \times 10^5$|无|$5$|$1$|
|$3$|$8000$|$8000$|A|$5$|-|
|$4$|$8000$|$8000$|无|$5$|$3$|
|$5$|$8000$|$2 \times 10^5$|A|$10$|$3$|
|$6$|$8000$|$2 \times 10^5$|无|$10$|$2, 4, 5$|
|$7$|$2 \times 10^5$|$2 \times 10^5$|AB|$10$|-|
|$8$|$2 \times 10^5$|$2 \times 10^5$|A|$15$|$5, 7$|
|$9$|$2 \times 10^5$|$2 \times 10^5$|B|$15$|$7$|
|$10$|$2 \times 10^5$|$2 \times 10^5$|无|$20$|$6, 8, 9$|

特殊性质 A：$w_u \ge 0$。  

特殊性质 B：对于所有询问，$u=1$。

## 样例 #1

### 输入

```
3 4
4 3 1
1 3
3 2
2 1 2
1 2 3
1 1 3
3 1 2
```

### 输出

```
3
1
4
1
```

## 样例 #2

### 输入

```
7 3
1 -9 1 -9 8 -1 0
1 2
2 3
2 4
4 5
5 6
6 7
1 3 3
1 2 7
1 1 2```

### 输出

```
1
-19
Impossible```

## 样例 #3

### 输入

```
5 5
6 1 4 -6 8
2 4
1 5
3 4
5 4
5 2 3
1 2 3
5 3 3
3 1 5
2 5 5
```

### 输出

```
-6
-6
4
-2
0```

# 题解

## 作者：EasonLiang (赞：3)

声明：本题的某些部分分算法**略微卡常**，但保证出题人对所有部分分算法的代码实现，在对应子任务中的运行时间均在时间限制的一半以内。

感谢 [fjy666](https://www.luogu.com.cn/user/366338) 佬的验题！  
感谢 [Leo_SZ](https://www.luogu.com.cn/user/258520)、[sunrise1024](https://www.luogu.com.cn/user/368884) 帮忙检验了一些部分分。  
感谢 [NanXl07](https://www.luogu.com.cn/user/379328) 实现了暴力程序，并帮我对拍。

**算法一**

我会暴力！

对于每次询问，枚举 $2^n$ 种染色方案并判断是否满足要求。  
时间复杂度 $O(2^nq\operatorname{poly}(n))$，期望得分 0~5pts。

**算法二**

我会预处理！

对于 $2^n$ 种染色方案中的每一种，记录下 $u$ 到 $v$ 的路径上是否有黑色结点，可以预处理出所有答案，询问时直接回答即可。  
时间复杂度 $O(2^n\operatorname{poly}(n)+q)$，期望得分 0~10pts。

> 接下来的期望得分取决于你是否会写 $w_u < 0$ 的树形 DP。

**算法三**

我会 DP！

对于每次询问，以 $u$ 为根进行树形 DP。  
时间复杂度 $O(nq)$，期望得分 15~20pts。

**算法四**

我会数点！

将询问离线，对于每个询问到的 $u$，以 $u$ 为根进行树形 DP，并做二维数点。  
时间复杂度 $O(kn \log n + q \log n)$，其中 $k$ 为询问到的不同 $u$ 的数量，结合算法三数据点分治后期望得分 25~45pts。

**算法五**

我会离散化！

注意到算法四的瓶颈在于，对于固定的 $u$，对答案造成贡献的区间数量是 $O(n)$ 的。  
考虑对于同一个 $u$ 的询问（假设有 $q_u$ 个），将询问的区间 $[l, r]$ 离散化。  
可以证明$ ^{\dagger} $离散化后，对答案造成贡献的不同区间 $[l, r]$ 的数量只有 $O(q_u)$ 个。  
因此，我们可以在 $O(n + q_u \log n)$ 的时间内回答所有根为 $u$ 的询问。  
总时间复杂度 $O(kn + q \log n)$，其中 $k$ 为询问到的不同 $u$ 的数量，期望得分 35~65pts。

**算法六**

我会换根！

考虑换根 DP，不难发现换根后改变的贡献区间数量是 $O(1)$ 的，将贡献离线下来三维数点即可。  
总时间复杂度 $O((n+q) \log^2 (n+q))$，期望得分 50~100pts。

---

$ ^{\dagger} $证明：$q_u$ 个区间离散化后构成 $O(q_u)$ 个极小区间，将每一个极小区间内的叶结点合并看作一个结点，则这些结点构成的虚树上的所有结点所代表区间，即为所有对答案造成贡献的区间，共 $O(q_u)$ 个。

---

## 作者：BreakPlus (赞：1)

先考虑 $u$ 固定的时候怎么做。

首先肯定要搞一个树形 DP。令 $f_x$ 表示以 $x$ 为根的子树，所有叶子结点到 $x$ 的路径上均有黑点的最小代价。令 $g_x$ 表示以 $x$ 为根的子树内所有负权之和。

显然有：若 $x$ 为叶子，$f_x$ = $w_x$；否则 $f_x = \min(w_x + \sum \limits_{y \in son(x)}g_y, \sum \limits_{y \in son(x)}f_y)$。

当给出区间 $[l,r]$ 的时候，定义 $x$ 是**重要的**，当且仅当以 $x$ 为根的子树内，所有叶子结点的编号都在 $[l,r]$ 中。定义 $x$ 是**关键的**，当且仅当其父亲是**不重要的**（或者它根本没有父亲，为 $u$ 本身），而其本身是**重要的**。

答案应当是所有**关键的**点的 $f$ 之和。这里有一个技巧，维护**关键的**点比较麻烦，但是维护**重要的**点比较容易（判断区间包含关系即可）。令 $f'_x = f_x - \sum \limits_{y \in son(x)}f_y$，答案就是所有**重要的**点的 $f'$ 之和。

那么当 $u$ 固定的时候，考察每一个点 $x$ 在 $[l,r]$ 满足什么条件的情况下会变成**重要的**点，以及计算 $f'_x$。其实就是一个简单的二维数点的问题。

----

当 $u$ 不固定的时候，我们继续考察每一个点 $x$ 作为重要的点的贡献。但是 $u$ 的位置会影响其贡献的内容。

不难发现其实只和 $u$ 在 $x$ 的哪个子树中有关，也就是有 $d(x)$ 种情况。而 $u$ 在哪个子树可以用 dfn 序刻画，相当于给之前的二维偏序加了一个维度，变成三维偏序了。具体实现细节不再赘述，跑个换根 DP 就好了。

+ 注意特判 $d(u)=1$ 且 $l \le u \le r$ 的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const ll mod = 998244353;
inline ll read(){
	ll x=0, f=1; char ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
int n,q,dfn[200005],efn[200005],fa[200005],d[200005],tim; ll all,dp[200005],odp[200005],w[200005],os[200005],oos[200005];
pair<int,int> in[200005],out[200005];
pair<int,int> merge(pair<int,int> A, pair<int,int> B){ return mkp(min(A.fi,B.fi), max(A.se,B.se)); }
vector<int>E[200005];

struct Node{
	ll tp,a,b,c,w;
}seq[2000005], lft[2000005], rht[2000005]; int tl, lt, rt;
void upd(int vl,int vr,int ql,int qr,ll w,int x){
	seq[++tl] = (Node){0,vl,ql,qr,w};
	seq[++tl] = (Node){0,vr+1,ql,qr,-w};
}
void dfs1(int x,int f){
	fa[x] = f; in[x] = mkp(n+1,0); dfn[x] = (++tim);
	if(d[x]==1) in[x] = mkp(x,x);
	sort(E[x].begin(), E[x].end());
	if(f) E[x].erase(lower_bound(E[x].begin(), E[x].end(), f));

	ll sum = 0; os[x] = 0;
	for(auto y: E[x]){
		dfs1(y, x);
		sum += dp[y]; in[x] = merge(in[x], in[y]);
		os[x] += os[y];
	}
	dp[x] = min(w[x] + os[x], sum); if(d[x] == 1) dp[x] = w[x];
	os[x] += min(0ll, w[x]);
	efn[x] = tim;

	if(1 < dfn[x]) upd(1, dfn[x]-1, in[x].fi, in[x].se, dp[x]-sum, x);
	if(efn[x] < n) upd(efn[x]+1, n, in[x].fi, in[x].se, dp[x]-sum, x);
}


void dfs2(int x){
	multiset<int>S;
	ll sum = 0, OS = 0;
	if(fa[x]){
		S.insert(out[x].fi), S.insert(out[x].se), sum += odp[x], OS += oos[x];
	}
	if(d[x]==1){
		S.insert(x);
	}
	for(auto y: E[x]){
		S.insert(in[y].fi), S.insert(in[y].se), sum += dp[y], OS += os[y];
	}
	for(auto y: E[x]){
		S.erase(S.find(in[y].fi)),S.erase(S.find(in[y].se));
		assert(S.size());
		out[y]=mkp(*S.begin(), *prev(S.end()));
		oos[y]=all-os[y];

		sum -= dp[y]; OS -= os[y];

		odp[y]=min(w[x]+OS,sum); if(d[x]==1) odp[y]=w[x];
		upd(dfn[y], efn[y], out[y].fi, out[y].se, odp[y]-sum, x);
		
		sum += dp[y], OS += os[y];
		S.insert(in[y].fi),S.insert(in[y].se);
	}
	upd(dfn[x], dfn[x], in[1].fi, in[1].se, min(w[x]+OS,sum)-sum, x);

	for(auto y: E[x]) dfs2(y);
}

ll ans[200005]; bool mk[200005];

ll c[200005];
void modify(int x,ll w){
	while(x<=n){
		c[x]+=w;
		x+=(x&-x);
	}
}
ll query(int x){
	ll res=0;
	while(x){
		res+=c[x];
		x-=(x&-x);
	}
	return res;
}
void cdq(int l,int r){
	if(l>=r) return;

	int mid=(l+r)>>1;
	cdq(l,mid); cdq(mid+1,r);
	lt=0, rt=0;
	for(int i=l;i<=mid;i++) if(seq[i].tp==0) lft[++lt]=seq[i];
	for(int i=mid+1;i<=r;i++) if(seq[i].tp==1) rht[++rt]=seq[i];
	sort(lft+1, lft+lt+1, [](Node A, Node B){ return A.b > B.b; });
	sort(rht+1, rht+rt+1, [](Node A, Node B){ return A.b > B.b; });

	int fk=0;
	for(int i=1;i<=rt;i++){
		while(fk<lt && lft[fk+1].b>=rht[i].b){
			fk++;
			modify(lft[fk].c,lft[fk].w);
		}
		ans[rht[i].w]+=query(rht[i].c);
	}
	for(int i=1;i<=fk;i++) modify(lft[i].c,-lft[i].w);
}
void procedure(){
	n=read(),q=read(); all=0;
	for(int i=1;i<=n;i++) w[i]=read(), all+=min(0ll,w[i]);
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v); E[v].pb(u); d[u]++, d[v]++;
	}
	dfs1(1,0);
	dfs2(1);

	int L = n+1, R = 0;
	for(int i=1;i<=n;i++) if(d[i]==1) L=min(L,i),R=max(R,i);

	for(int i=1;i<=q;i++){
		int u=read(),l=read(),r=read();

		if(n == 1){
			ans[i] = w[u];
			continue;
		}
		if(d[u] == 1 && l <= u && u <= r){
			if(l <= L && R <= r) ans[i] = all-min(0ll,w[u])+w[u];
			else mk[i] = 1;
			continue;
		}

		seq[++tl] = (Node){1,dfn[u],l,r,i};
	}
	sort(seq+1, seq+tl+1, [](Node A, Node B){
		if(A.a != B.a) return A.a < B.a;
		else return A.tp < B.tp;
	});

	cdq(1, tl);

	for(int i=1;i<=q;i++){
		if(mk[i]) puts("Impossible");
		else printf("%lld\n", ans[i]);
	}
}
```

---

