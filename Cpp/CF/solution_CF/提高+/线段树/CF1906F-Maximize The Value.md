# Maximize The Value

## 题目描述

You are given a one-based array consisting of $ N $ integers: $ A_1, A_2, \cdots, A_N $ . Initially, the value of each element is set to $ 0 $ .

There are $ M $ operations (numbered from $ 1 $ to $ M $ ). Operation $ i $ is represented by $ \langle L_i, R_i, X_i \rangle $ . If operation $ i $ is executed, all elements $ A_j $ for $ L_i \leq j \leq R_i $ will be increased by $ X_i $ .

You have to answer $ Q $ independent queries. Each query is represented by $ \langle K, S, T \rangle $ which represents the following task. Choose a range $ [l, r] $ satisfying $ S \leq l \leq r \leq T $ , and execute operations $ l, l + 1, \dots, r $ . The answer to the query is the maximum value of $ A_K $ after the operations are executed among all possible choices of $ l $ and $ r $ .

## 说明/提示

Explanation for the sample input/output #1

For query $ 1 $ , one of the solutions is to execute operation $ 4 $ and $ 5 $ .

For query $ 2 $ , one of the solutions is to execute operation $ 4 $ , $ 5 $ , and $ 6 $ .

For query $ 3 $ , the only solution is to execute operation $ 3 $ .

For query $ 4 $ , the only solution is to execute operation $ 1 $ .

For query $ 6 $ , the only solution is to execute operation $ 2 $ .

## 样例 #1

### 输入

```
2 6
1 1 -50
1 2 -20
2 2 -30
1 1 60
1 2 40
2 2 10
5
1 1 6
2 1 6
1 1 3
2 1 3
1 1 2```

### 输出

```
100
50
0
0
-20```

## 样例 #2

### 输入

```
5 3
1 3 3
2 4 -2
3 5 3
6
1 1 3
2 1 3
3 1 3
3 2 3
2 2 3
2 2 2```

### 输出

```
3
3
4
3
0
-2```

# 题解

## 作者：ydzr00000 (赞：8)

## 题面
有一个长度为 $N$ 的整数序列 $A$，初始 $A$ 中所有元素均为 $0$。

给出 $M$ 个操作，每一个操作给出 $\langle L_i,R_i,X_i\rangle$，表示给下标在 $[L_i,R_i]$ 内的**序列元素**加上 $X_i$。

给出 $Q$ 个**相互独立的**询问，每一个询问给出 $\langle K,S,T\rangle$，你需要选择一个区间 $[l,r]$，满足 $S\leq l\leq r\leq T$，然后执行下标在 $[l,r]$ 内的所有**操作**，你需要最大化 $A_K$ 的值。

## 题解
考虑如下子问题：
- 有一个变量 $v$，初始 $v=0$，接下来有若干操作，每一个操作给 $v$ 加上 $x_i$，你需要选择一段连续的操作并执行，最大化 $v$ 的值。

这个问题的解法可以发现等价于求操作序列中 $x$ 的最大子段和。

再拓展一下：
- 有一个变量 $v$，初始 $v=0$，接下来有若干操作，每一个操作给 $v$ 加上 $x_i$，给定一个区间，你需要选择**这个区间中**一段连续的操作并执行，最大化 $v$ 的值。

根据前面的问题所得的答案，上述问题需要求的是区间最大子段和。

于是本题就可以变成：
- 对于每一个询问，拉出所有与 $K$ 有关的操作，再给定限制区间 $[S,T]$，你需要求出编号在 $[S,T]$ 内操作中的 $X_i$ 最大子段和。

很好，这个问题看起来也没有简单很多，但是我们已经发现这个问题跟区间最大子段和有关了，所以考虑线段树。

不妨离线所有询问，按顺序对每一个元素进行处理，假设考虑到了 $A_i$，我们接下来需要考虑所有与 $i$ 有关的操作与询问。很显然的解法就是暴力扫描所有操作，如果包含 $i$ 则将其加入线段树，扫描每一个询问，处理每一个询问中 $[S,T]$ 的最大子段和。

接下来，我们需要优化这个暴力扫描。我们可以发现每一个操作影响的是一批连续的元素，不妨差分掉每一个操作，对于 $(L,R,X)$，在 $L$ 处添加 $+X$ 的影响，在 $R+1$ 处添加 $-X$ 的影响，以抵消前面 $+X$ 的影响。

非常好，所有的操作的影响以及询问的处理最终落到了每一个元素上，最后，顺序扫描每一个元素，先处理掉所有操作的影响，再解答所有询问。

时间复杂度为 $\mathcal{O}((M+Q)\log_2 M)$。

### Talking is cheap, show you the code.
```c++
#include<bits/stdc++.h>
using namespace std;
class SegmentTree{
	private:
		struct node{
			long long sum,val;
			long long maxpre,maxsuf;
		}seg[2500001];
		friend node operator+(node x,node y)
		{
			node z;
			z.sum=x.sum+y.sum;
			z.maxpre=max(x.maxpre,x.sum+y.maxpre);
			z.maxsuf=max(y.maxsuf,y.sum+x.maxsuf);
			z.val=max(max(x.val,y.val),x.maxsuf+y.maxpre);
			return z;
		}
		inline void pushup(int id)
		{
			seg[id]=seg[id<<1]+seg[id<<1|1];
		}
	public:
		inline void build(int l,int r,int id)
		{
			if(l==r)
			{
				seg[id].sum=0;
				seg[id].maxpre=0;
				seg[id].maxsuf=0;
				seg[id].val=0;
				return;
			}
			int mid=(l+r)>>1;
			build(l,mid,id<<1);
			build(mid+1,r,id<<1|1);
			pushup(id);
		}
		inline void update(int l,int r,int id,int pos,int val)
		{
			if(l==r)
			{
				seg[id].sum+=val;
				seg[id].maxpre+=val;
				seg[id].maxsuf+=val;
				seg[id].val+=val;
				return;
			}
			int mid=(l+r)>>1;
			if(mid>=pos)
				update(l,mid,id<<1,pos,val);
			else
				update(mid+1,r,id<<1|1,pos,val);
			pushup(id);
		}
		inline node query(int l,int r,int id,int head,int tail)
		{
			if(l==head&&r==tail)
				return seg[id];
			int mid=(l+r)>>1;
			if(mid>=tail)
				return query(l,mid,id<<1,head,tail);
			if(mid<head)
				return query(mid+1,r,id<<1|1,head,tail);
			return query(l,mid,id<<1,head,mid)+query(mid+1,r,id<<1|1,mid+1,tail);
		}
};
SegmentTree S;
vector<pair<int,int> >op[200002];
struct query{
	int l,r,id;
};
vector<query>qy[200001];
long long ans[200001];
int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int l,r,x;
		scanf("%d %d %d",&l,&r,&x);
		op[l].push_back({x,i});
		op[r+1].push_back({-x,i});
	}
	int q;
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		int k,s,t;
		scanf("%d %d %d",&k,&s,&t);
		qy[k].push_back({s,t,i});
	}
	S.build(1,m,1);
	for(int i=1;i<=n;i++)
	{
		for(auto [val,id]: op[i])
			S.update(1,m,1,id,val);
		for(auto [l,r,id]: qy[i])
			ans[id]=S.query(1,m,1,l,r).val;
	}
	for(int i=1;i<=q;i++)
		printf("%lld\n",ans[i]);

	return 0;
}
```

---

## 作者：nullqtr_pwp (赞：2)

一眼了。

这种问题与序列本身没有太大关系，但是和时间，操作序列轴有很大关系的可以考虑离线询问，并且将序列，时间维互换（正常线段树可以理解为对时间扫描线，对序列维护）

考虑对序列进行从左到右扫描线，维护时间轴的信息。每个时间 $i$ 的操作差分成两次单点修改 $(i,l,x)$ 以及 $(i,r+1,-x)$。

考虑当前扫到了位置 $p$，那么线段树每个叶子节点加了 $x$ 就对应时间 $i$，相当于在第 $i$ 次操作，在 $p$ 位置加了 $x$。

考虑询问，问题是执行 $[l,r]\subset [S,T]$ 的操作，其实就是在时间轴的 $[S,T]$ 的子区间中选取一个和最大的子段。区间最大子段和问题容易用线段树维护（区间答案，区间最大前后缀和，区间和）

代码懒得写了。时间复杂度 $O((n+q)\log q)$。建议把[这题](https://loj.ac/p/3523)写了。

---

## 作者：fantastic_dream (赞：2)

### 解答
若考虑直接在序列上操作，已经有序列上的线段树，对于询问的优化比较困难，复杂度为 $O(QM \log N)$，无法通过。

换种思路，把序列想象成时间轴，只处理与当前元素 $A_i$ 有关的操作，也就是把操作用线段树维护，类似于扫描线的思想，对于一个操作，在扫到第 $L_i$ 个元素时把其 $X_i$ 加入线段树，在扫到第 $R_i+1$ 个元素时把其影响消除，也就是在线段树对应地减去 $X_i$。

而对于我们的询问，根据上面的想法不难看出线段树上从 $S$ 到 $T$ 的最大子段和即为我们所要求的答案，具体操作方法可以参考 [P4513](https://www.luogu.com.cn/problem/P4513)。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define fi first
#define se second
const int ma=1e5+5,inf=-1e13;
int n,m,q,ans[ma];
vector<pair<int,int> > qe[ma];
struct n1{
	int pos,l,r;
};
vector<n1> rq[ma];
struct node{
	int ls,rs,zd,sum;
}tr[ma<<2];
void pup(node &x,node a,node b){
	x.sum=a.sum+b.sum;
	x.ls=max(a.ls,a.sum+b.ls);
	x.rs=max(b.rs,b.sum+a.rs);
	x.zd=max(a.zd,max(b.zd,a.rs+b.ls));
}
void upd(int l,int r,int a,int x,int k){
	if(l==r){
		tr[x]={tr[x].ls+k,tr[x].rs+k,tr[x].zd+k,tr[x].sum+k};
		return;
	}
	int mid=(l+r)>>1;
	if(a<=mid)	upd(l,mid,a,x<<1,k);
	if(a>mid)	upd(mid+1,r,a,x<<1|1,k);
	pup(tr[x],tr[x<<1],tr[x<<1|1]);
}
node que(int l,int r,int a,int b,int x){
	if(l>=a&&r<=b)	return tr[x];
	node re={inf,inf,inf,0};
	int mid=(l+r)>>1;
	if(a<=mid&&b>mid)	pup(re,que(l,mid,a,b,x<<1),que(mid+1,r,a,b,x<<1|1));
	else if(a<=mid)	re=que(l,mid,a,b,x<<1);
	else	re=que(mid+1,r,a,b,x<<1|1);
	return re;
} 
main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int l,r,k;
		cin>>l>>r>>k;
		qe[l].push_back({i,k}),qe[r+1].push_back({i,-k});
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		int l,r,k;
		cin>>k>>l>>r;
		rq[k].push_back({i,l,r});
	}
	for(int i=1;i<=n;i++){
		for(auto j:qe[i])	upd(1,m,j.fi,1,j.se);
		for(auto j:rq[i])	ans[j.pos]=que(1,m,j.l,j.r,1).zd;
	}
	for(int i=1;i<=q;i++)	cout<<ans[i]<<'\n';
	return 0;
} 
```

---

## 作者：Loser_Syx (赞：1)

考虑离线后按 $k$ 来扫，那么 $[l,r]$ 的区间加就变成了 $l$ 的单点加和 $r+1$ 的单点减，对于每个 $k$ 直接计算其差分的值即可。

记差分完的数组为 $c$，那么就发现此时的选 $[s,t]$ 的区间变成了 $[s,t]$ 里 $c$ 的最大子段和，用线段树是好维护的。

注意可能 $[s,t]$ 里都是对 $k$ 操作且都是负数，这个要特判输出 $\max$。

[code](https://codeforces.com/contest/1906/submission/293108358)。

---

## 作者：Mirasycle (赞：0)

翻看别人 PKUWC 游记看到的题，简单题，放学回家路上想了几分钟就会了。

首先选择的是时间区间，但是我们要求的产生贡献的是包含序列上单点的位置区间。如果直接在时间区间内选择很难考虑到是否对于某个位置产生贡献。

所以很套路化地转化为对于位置进行扫描线，然后维护时间信息。对于一条在 $t$ 时刻进行的更新 $(l,r,val)$，我们在扫描到 $l$ 处加入，在扫描到 $r+1$ 处删除。因此扫描到某个点时，目前维护的就是所有包含这个点的区间。

考虑处理询问，我们用线段树维护时间轴，每次加入就是在对于节点将权值设为 $val$，删除就是将权值设为 $0$。然后查询时间区间内的子区间最大贡献，就是在时间轴上寻找区间最大子段和（注意上述扫描线已经保证了目前加入的区间修改都是肯定可以对这个点进行贡献的区间修改）即可。

于是我们用线段树维护区间最大子段和就行了。

时间复杂度 $O((n+q)\log n)$。

---

## 作者：rainygame (赞：0)

你说得对，但是双 log 卡过去了。

发现如果 $K \in [L_i,R_i]$，那么这个操作对询问的贡献为 $X_i$，否则为 $0$。

那么考虑对于每个 $K$，求出所有包含它的询问的贡献，然后直接求出 $[S,T]$ 的最大子段和即为答案。

显然可以线段树分治，时间复杂度 $O(n \log^2 n)$。

[submission](https://codeforces.com/problemset/submission/1906/295903867)

---

## 作者：tai_chi (赞：0)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18421485) 中阅读。

见这种题比较少，写篇题解加深印象。

如果直接上数据结构维护数组，似乎没有好的办法处理操作序列的一个子段。那不妨转变思路，对操作序列上数据结构维护。

假设顺序进行每个修改操作，我们用**时间**表示修改操作的编号，**位置**表示数组的下标，则常见的维护序列的数据结构实际是对位置维度维护，这里我们对时间维度维护。

我们把询问挂在其对应位置 $k$ 上，位置指针一遍从 $1$ 扫到 $n$，在扫描到位置 $i$ 的时候，为获取当前位置的询问答案，我们需要位置 $i$ 在不同时间发生的变化量。

这么说可能有些抽象，具体来说就是要支持一个序列 $T$，$T_j$ 记录第 $j$ 个修改操作的生效情况，生效为 $x$，失效为 $0$。$T$ 也可以看做时间轴。

可以把修改操作在位置维度上离线下来，用差分技巧拆成两次单点修改，实际意义对应：位置指针在左端点时修改操作生效，在右端点之后失效。

根据前面的思路，我们按位置编号递增处理询问，询问 $(k,s,t)$ 的答案就是位置指针在 $k$ 时，时间轴 $T$ 上 $[s,t]$ 区间内的最大子段和。

回头看需要，我们要维护一个序列，支持单点加，询问区间最大子段和，这是经典线段树问题，只需在线段树上维护最大前缀和、最大后缀和、区间答案、区间和即可。参考 P4513。

[code](https://codeforces.com/contest/1906/submission/281864678)

---

## 作者：Leaper_lyc (赞：0)

发现在线维护是不太好实现，考虑**离线**。

接下来我们来考虑单个询问中的 $k$。对于一个区间 $[L,R]$，满足 $S\le L\le R\le T$ 且 $k\in[L,R]$，则这个区间可以给 $A_k$ 加上 $x_i$。如果我们把所有合法的区间的贡献值列出来（或者说只要区间合法即可，不考虑区间具体范围），那么会得到**一个序列 $X$。要使 $A_k$ 最大，就是要从 $X$ 中选出连续的一段和最大的连续子序列，然后加到 $A_k$ 上。**

这就是经典的最大连续子段问题，用线段树维护一下一个区间的前缀最大值、后缀最大值、区间和以及区间答案等。

于是本题就可以变成：对于每一个询问 $(S,T,K)$，在所有与 $K$ 有关的且在 $[S,T]$ 范围内的操作中，其贡献 $x_p$ 组成的序列 $X$ 最大子段和。

假设我们正在考虑第 $i$ 位，显然每一个操作影响的是一批连续的元素，可以考虑差分：将操作 $(L,R,x)$ 等同于操作 $(L,i,x)$ 和 $(i,R+1,-x)$。

差分有什么好处呢？它把区间的操作转换到了与单点有关的操作，这样就做完了！

时间复杂度：$O((m+q)\log q)$。

细节：
- 由于从一个操作变成两个操作，要开二倍空间！
- 不开 `long long` 见祖宗！

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 1e6 + 10;
#define int long long
#define ls (cur << 1)
#define rs (cur << 1 | 1)
int n, m;
int ans[N];
struct que { int l, r, id; }; vector <que> q[N << 1];
vector < pair <int, int> > op[N << 1];
struct node {
    int sum, val, pre, suf;
    void init() { sum = val = pre = suf = 0; }
} tr[N << 2];
node operator+(const node &x, const node &y) {
    node z; z.init();
    z.sum = x.sum + y.sum;
    z.pre = max(x.pre, x.sum + y.pre);
    z.suf = max(y.suf, y.sum + x.suf);
    z.val = max(max(x.val, y.val), x.suf + y.pre);
    return z;
}
void pushup(int cur) { tr[cur] = tr[ls] + tr[rs]; }
void update(int cur, int l, int r, int p, int k) {
    if (l == r) {
        tr[cur].sum += k, tr[cur].pre += k, tr[cur].suf += k, tr[cur].val += k;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) update(ls, l, mid, p, k);
    else update(rs, mid + 1, r, p, k);
    pushup(cur);
}
node query(int cur, int l, int r, int L, int R) {
    if (L == l && r == R) return tr[cur];
    int mid = (l + r) >> 1;
    if (R <= mid) return query(ls, l, mid, L, R);
    if (L > mid) return query(rs, mid + 1, r, L, R);
    return query(ls, l, mid, L, mid) + query(rs, mid + 1, r, mid + 1, R);
}
signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        op[l].push_back(make_pair(x, i));
        op[r + 1].push_back(make_pair(-x, i));
    }
    int T; cin >> T;
    for (int i = 1, k, s, t; i <= T; i++) {
        cin >> k >> s >> t;
        q[k].push_back((que){ s, t, i });
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (int)op[i].size(); j++)
            update(1, 1, m, op[i][j].second, op[i][j].first);
        for (int j = 0; j < (int)q[i].size(); j++)
            ans[q[i][j].id] = query(1, 1, m, q[i][j].l, q[i][j].r).val;
    }
    for (int i = 1; i <= T; i++) cout << ans[i] << '\n';
}
```

---

## 作者：Filberte (赞：0)

比较经典的线段树离线套路。

先考虑所有询问的 $k$ 相等时，这个问题如何解决。可以维护一个长度为 $m$ 序列 $a$，其中如果 $k \in [l_i, r_i]$，那么令 $a_i = x_i$，否则令 $a_i = 0$。此时对于一个每询问，可以转化为求 $a$ 序列上一段区间的最大子段和，这可以简单地用线段树维护。

再来考虑 $k$ 不同时怎么办。一种简单的思路是对于不同的 $k$ 每次暴力 $O(m)$ 把 $a$ 序列搞出来，然后回答与之有关的询问，接着再看下一个 $k$。但这样的复杂度时 $O(mq)$ 的，需要优化。我们可以动态维护 $a$ 序列：先把所有询问按照 $k$ 的大小排序，当 $k$ 变成 $k + 1$ 时，与原来相比，那些 $r_p = k$ 的操作对于 $a$ 数组的影响将会消失，应令 $a_p = 0$；与之相对的，所有 $l_p = k + 1$ 的操作将会对 $a$ 数组产生新的影响，应令 $a_p = x_p$。处理完这些变化后，就把 $a$ 序列变成了 $k + 1$ 时的状态，此时回答询问就是十分简单的了。

总的来说，需要维护一棵支持单点修改，区间求最大子段和的线段树。其中每次操作最多需要在线段树上修改 $2$ 次，每次询问需要在线段树上查询 $1$ 次，总复杂度 $O((q + m)\log m)$，可以通过此题。

代码如下：

```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
const int N = 2e5 + 100;
struct Qs{
	int l, r, p, id;
	bool operator < (Qs ot) const{
		return p < ot.p;
	}
}qs[N];
int n, m, q;
vector<pair<int, int>> vc[N];
struct Node{
	ll pre, suf, sum, mxs;
	friend Node operator ^ (Node x, Node y){
		Node res;
		res.pre = max(x.pre, x.sum + y.pre);
		res.suf = max(y.suf, y.sum + x.suf);
		res.sum = x.sum + y.sum;
		res.mxs = max(max(x.mxs, y.mxs), x.suf + y.pre);
		return res;
	}
	void Add(int x){
		pre += x, suf += x;
		sum += x, mxs += x;
	}
}t[N << 2];
Node qry(int u, int l, int r, int L, int R){
	if(L <= l && r <= R) return t[u];
	int mid = (l + r) >> 1;
	if(R <= mid) return qry(u << 1, l, mid, L, R);
	if(L > mid) return qry(u << 1 | 1, mid + 1, r, L, R);
	return qry(u << 1, l, mid, L, R) ^ qry(u << 1 | 1, mid + 1, r, L, R);
}
void add(int u, int l, int r, int p, int k){
	if(l == r){
		t[u].Add(k);
		return ;
	}
	int mid = (l + r) >> 1;
	if(p <= mid) add(u << 1, l, mid, p, k);
	else add(u << 1 | 1, mid + 1, r, p, k);
	t[u] = t[u << 1] ^ t[u << 1 | 1];
}
ll ans[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for(int i = 1, l, r, x;i <= m;i++){
		cin >> l >> r >> x;
		vc[l].push_back(make_pair(i, x));
		vc[r + 1].push_back(make_pair(i, -x)); 
	}
	cin >> q;
	for(int i = 1;i <= q;i++){
		qs[i].id = i;
		cin >> qs[i].p >> qs[i].l >> qs[i].r;
	}
	sort(qs + 1, qs + 1 + q);
	int cur = 0;
	for(int i = 1;i <= q;i++){
		while(cur < qs[i].p){
			++cur;
			for(pair<int, int> x : vc[cur]) add(1, 1, m, x.first, x.second);
		}
		ans[qs[i].id] = qry(1, 1, m, qs[i].l, qs[i].r).mxs;
	}
	for(int i = 1;i <= q;i++) cout << ans[i] << "\n";
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

\*2000，水题。

容易想到其实就是对 $[S,T]$ 中的询问关于 $k$ 做个最大子段和的问题，最大子段和问题一般要放到线段树上。

借助[这道题](https://www.luogu.com.cn/problem/AT_abc214_e)的思路，下标 $i$ 从 $1$ 到 $n$ 枚举，我们可以对修改按照左端点排序，然后维护一个右端点的优先队列，这样队列对应的就是覆盖了一个下标的所有修改。插入时单点加，删除时单点减，然后查询最大子段和即可。

但是我们显然不能对每个点都建一棵线段树对吧，所以这时我们回到上面的操作，$i$ 枚举的过程相当于 $[1,n]$ 每次从 $i-1$ 递推到 $i$ 的过程，并且一共只有 $2m$ 次修改操作，空间 1G，直接建主席树即可。

时间 $O(n\log n)$，空间 $O(n\log n)$，还有就是因为是 $2m$ 的询问线段树的数组要开够。

[code](https://codeforces.com/contest/1906/submission/238837369)

---

