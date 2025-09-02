# Doremy's Drying Plan (Hard Version)

## 题目描述

The only differences between the two versions of this problem are the constraint on $ k $ , the time limit and the memory limit. You can make hacks only if all versions of the problem are solved.

Doremy lives in a rainy country consisting of $ n $ cities numbered from $ 1 $ to $ n $ .

The weather broadcast predicted the distribution of rain in the next $ m $ days. In the $ i $ -th day, it will rain in the cities in the interval $ [l_i, r_i] $ . A city is called dry if it will never rain in that city in the next $ m $ days.

It turns out that Doremy has a special power. She can choose $ k $ days, and during these days it will not rain. Doremy wants to calculate the maximum number of dry cities after using the special power.

## 说明/提示

In the first test case, if Doremy prevents

- rain $ 1,2 $ , then city $ 2 $ will be dry;
- rain $ 2,3 $ , then no city will be dry;
- rain $ 1,3 $ , then no city will be dry;

So there is at most $ 1 $ dry city.

In the second test case, if Doremy prevents

- rain $ 1,2 $ , then city $ 1,2 $ will be dry;
- rain $ 2,3 $ , then city $ 4,5 $ will be dry;
- rain $ 1,3 $ , then city $ 1,5 $ will be dry.

So there are at most $ 2 $ dry cities.

In the third test case, it is optimal to prevent rain $ 1,2,4,5 $ .

In the forth test case, there is always a day of rain that wets all the cities and cannot be prevented.

## 样例 #1

### 输入

```
6
2 3 2
1 2
1 2
1 1
5 3 2
1 3
2 4
3 5
10 6 4
1 5
6 10
2 2
3 7
5 8
1 4
100 6 5
1 100
1 100
1 100
1 100
1 100
1 100
1000 2 2
1 1
1 1
20 5 3
9 20
3 3
10 11
11 13
6 18```

### 输出

```
1
2
6
0
1000
17```

# 题解

## 作者：樱雪喵 (赞：22)

## Description

给定 $m$ 条线段 $[l_i,r_i]$，其中 $l_i,r_i\in [1,n]$。至多删除 $K$ 条线段，使 $[1,n]$ 中未被任何线段覆盖的点数最多。输出这个数。

$n,m\le 2\times 10^5,\, K\le \min(10,m)$。

## Solution

推翻 C1 的做法，考虑 DP。

设 $f_{i,j}$ 表示考虑了点 $i$ 不被覆盖，已经删除了 $j$ 条线段，前 $i$ 个点最多不被覆盖的点数。

那么我们枚举上一个没被覆盖的点为 $k$，考虑所有覆盖的点 $i$ 的线段 $[l,r]$：

- 如果 $l\le k$，由于要保证 $k$ 没被覆盖，这条线段在 $k$ 那里就被删了，不应该计入“令点 $i$ 不被覆盖”的代价。
- $l>k$，说明这条线段是因为点 $i$ 而删掉的，应当计入代价。

设第二类线段数为 $t$。那么有转移：

$$
f_{i,j}=1+\max\limits_{k=0}^{i-1} f_{k,j-t}
$$

直接实现是 $O(n^2K)$ 的，考虑找性质优化。发现第二维只有 $K$ 种取值，且 $j-t$ 的取值随 $k$ 的增加单调不降。那么我们可以根据 $j-t$ 的取值将 $k$ 划分成 $K$ 段。

对于每个 $j$ 使用数据结构维护区间最大值即可。但是有同层转移，需要支持修改操作，而线段树等数据结构都是 $O(nK^2 \log n)$ 的，无法接受。

修改操作实际上只会依次在末尾加数，而不会改变已经添加过的值。  
这可以使用 ST 表维护：把 ST 表倒过来，令 $st_{i,j}$ 表示 $[j-2^i+1,j]$ 的最大值。这样即可方便地在末尾以 $\log n$ 的复杂度更新 ST 表。

时间复杂度 $O(nK^2)$。

```cpp
const int N=2e5+5,M=15,inf=1e9;
int T,n,m,k;
vector<int> t1[N],t2[N];
multiset<int> s;
vector<int> a[N];
int f[M][N];
struct ST
{
    int st[20][N];
    void ins(int x,int i)
    {
        st[0][i]=f[x][i];
        for(int j=1;i-(1<<j-1)>=0;j++) st[j][i]=max(st[j-1][i],st[j-1][i-(1<<j-1)]);
    }
    il int ask(int l,int r)
    {
        if(l>r) return -inf;
        int len=__lg(r-l+1);
        return max(st[len][r],st[len][l+(1<<len)-1]);
    }
}st[M];
int main()
{
    T=read();
    while(T--)
    {
        n=read(),m=read(),k=read();
        for(int i=1;i<=n;i++) t1[i].clear(),t2[i].clear(),a[i].clear();
        s.clear();
        for(int i=1;i<=m;i++)
        {
            int l=read(),r=read();
            t1[l].push_back(l),t2[r+1].push_back(l);
        }
        for(int i=1;i<=n;i++)
        {
            for(auto x:t1[i]) s.insert(x);
            for(auto x:t2[i]) s.erase(s.find(x));
            if(s.size()>k) a[i].push_back(-1);
            else {for(auto x:s) a[i].push_back(x); a[i].push_back(i);}
        }
        for(int i=1;i<=n;i++) f[0][i]=f[0][i-1]+(a[i].size()==1&&a[i][0]!=-1);
        st[0].ins(0,0);
        for(int i=1;i<=n;i++) 
        {
            if(!a[i].empty()&&a[i][0]==-1) f[0][i]=0;
            st[0].ins(0,i);
        }
        for(int j=1;j<=k;j++)
        {
            for(int i=1;i<=n;i++)
            {
                int lst=0,now=a[i].size()-1; f[j][i]=0;
                if(a[i].size()==1&&a[i][0]==-1) {st[j].ins(j,i);continue;}
                for(auto x:a[i])
                {
                    if(j-now<0) break;
                    f[j][i]=max(f[j][i],1+st[j-now].ask(lst,x-1));
                    now--,lst=x;
                }
                st[j].ins(j,i);
            }
        }
        printf("%d\n",st[k].ask(0,n));
    }
    return 0;
}
```

---

## 作者：hyman00 (赞：18)

## CF1889C 题解

### 题意

有 $m$ 个线段，值域 $[1,n]$，可以删除至多 $k$ 个，最大化没有被任意一个剩余线段覆盖的位置的个数。

$ 1\le n\le 2\cdot 10^5 $ , $ 2 \le m \le 2\cdot 10^5 $ , $ 2 \le k \le \min(10, m) $

### 做法

考虑 dp，把所有线段按照左端点从小到大排序，令 $dp_{i,x,y}$ 表示对于前 $i$ 个线段，其中有 $x$ 个删除了，没有删除的右端点最大是 $y$ 时，没有删除的线段最少覆盖了多少个位置。

注意 $x$ 是 $[0,k]$ 中的数，$y$ 虽然范围较大，但是只有前 $i$ 个线段中最大的 $k+1$ 个右端点是有用的（显然这些不可能全删完），状态数 $O(nk^2)$，需要用 `unordered_map` 记录。

转移可以枚举当前线段是否删除，是 $O(1)$ 的。

### 实现细节

dp 数组只开一个 `unordered_map`，可以把三维压一起，这样不用担心开 $2\times 10^6$ 个会炸，状态可以用 $i\times 2^{22}+x\times 2^{18}+y$ 记录。

转移完一个状态后就可以把它从哈希表里删除，这样同一时刻的哈希表里的元素个数仅有 $O(k^2)$，常数不会太大。

注意不要 $n,m$ 写反。

总复杂度时间 $O(mk^2)$，空间 $O(m+k^2)$。

### 代码

```c++
unordered_map<int,int>dp;
int n,m,k;
pii p[200005];
//i*(k+1)*(n+1)+j*(n+1)+k 
const int C=100000000;
inline void go(int x,int y,int z,int t){
	int w=(x<<22)|(y<<18)|z;
	Mi(dp[w],t-C);
}
void run(){
	cin>>n>>m>>k;
	rep(i,m){
		cin>>p[i].F>>p[i].S;
	}
	if(k>=m){
		cout<<n<<"\n";
		re;
	}
	sort(p,p+m);
	dp.clear();
	set<int>st;
	st.insert(0);
	int ans=n+1;
	go(0,0,0,0);
	rep(i,m){
		for(int l:st)rep(j,min(k,i)+1)if(dp.count((i<<22)|(j<<18)|l)){
			int t=dp[(i<<22)|(j<<18)|l]+C;
			dp.erase((i<<22)|(j<<18)|l);
//			cout<<i<<" "<<j<<" "<<l<<": "<<t<<"\n";
			go(i+1,j,max(l,p[i].S),t+max(p[i].S,l)-max(p[i].F-1,l));
			if(j<k)go(i+1,j+1,l,t);
		}
		st.insert(p[i].S);
		while(sz(st)>k+1)st.erase(st.begin());
	}
	for(int l:st)rep(j,k+1){
//		cout<<m<<" "<<j<<" "<<l<<": "<<dp[(m<<22)|(j<<18)|l]+C<<"\n";
		Mi(ans,dp[(m<<22)|(j<<18)|l]+C);
	}
	cout<<n-ans<<"\n";
}
```

---

## 作者：stntn (赞：7)

考虑 DP，设 $f_{i,j}$ 表示钦定位置 $i$ 不被覆盖，操作 $j$ 次的最大收益。

$$
f_{i,j}=\max_{p<i} \{ f_{p,j-cost(p,i)}+1 \}
$$

$cost(i,j)$ 指已经删除所有覆盖 $i$ 的区间后还需要删除多少区间才能把覆盖 $j$ 的区间删空。暴力转移是 $O(n^2k)$ 的，考虑优化转移。

发现对于固定的 $j$ 随着 $i$ 的减小，$cost(i,j)$ 是单调不增的。并且注意到 $k$ 的值域是极小的。

于是我们维护对于当前 $i$ 而言 $cost(p,i)$ 相同的一些区间，每次往前枚举若干区间进行转移，这样一次枚举只会涉及前 $k$ 个区间，然后用数据结构维护每个区间内的最大值即可转移。

代码使用 `set` 维护区间，线段树维护区间最大值，第 $i$ 棵线段树维护已经操作 $i$ 次的 $f$。

```cpp
#include<bits/stdc++.h>
#define N 200010
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define INF 0x3f3f3f3f
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=a*10+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
int T,n,m,k,ans,cntl[N],f[N][11];
vector<int> pl[N];
struct NODE
{
	int x;mutable int v;
	NODE(int x=0,int v=0):x(x),v(v){}
	inline bool operator < (const NODE &b) const {return x<b.x;}
};
set<NODE> s;
struct SGT
{
	#define lc rt<<1
	#define rc rt<<1|1
	#define mid ((l+r)>>1)
	int mx[N<<2];
	inline void pushup(int rt){mx[rt]=max(mx[lc],mx[rc]);}
	inline void build(int rt,int l,int r)
	{
		mx[rt]=-INF;if(l==r) return;
		build(lc,l,mid);build(rc,mid+1,r);
	}
	inline void update(int rt,int l,int r,int p,int v)
	{
		if(l==r) return mx[rt]=v,void();
		p<=mid?update(lc,l,mid,p,v):update(rc,mid+1,r,p,v);
		pushup(rt);
	}
	inline int query(int rt,int l,int r,int L,int R)
	{
		if(L>R) return -INF;
		if(L<=l&&r<=R) return mx[rt];int res=-INF;
		if(L<=mid) res=max(res,query(lc,l,mid,L,R));
		if(mid<R) res=max(res,query(rc,mid+1,r,L,R));
		return res;
	}
	#undef lc
	#undef rc
	#undef mid
}t[11];
signed main()
{
	read(T);
	while(T--)
	{
		read(n,m,k);s.clear();ans=0;
		rep(i,0,k) t[i].build(1,0,n);
		rep(i,0,n)
		{
			cntl[i]=0;pl[i].clear();
			rep(j,0,k) f[i][j]=-INF;
		}
		rep(i,1,m)
		{
			int l,r;read(l,r);
			cntl[l]++;pl[r].push_back(l);
		}
		f[0][0]=0;t[0].update(1,0,n,0,0);
		rep(i,1,n)
		{
			rep(j,0,cntl[i]-1)
			{
				auto p=s.lower_bound(NODE(i,-INF));
				if(p!=s.end()&&p->x==i) p->v++;
				else s.insert(NODE(i,1));
			}
			if(!s.size())
			{
				rep(j,0,k) f[i][j]=max(f[i][j],t[j].query(1,0,n,0,i-1)+1);
			}
			else
			{
				auto p=prev(s.end());int pos=p->x,cur=p->v;
				if(pos^i) rep(j,0,k) f[i][j]=max(f[i][j],t[j].query(1,0,n,pos,i-1)+1);
				for(;cur<=k;p--,cur+=p->v)
				{
					if(p==s.begin())
					{
						rep(j,cur,k) f[i][j]=max(f[i][j],t[j-cur].query(1,0,n,0,p->x-1)+1);
						break;
					}
					else rep(j,cur,k) f[i][j]=max(f[i][j],t[j-cur].query(1,0,n,prev(p)->x,p->x-1)+1);
				}
			}
			rep(j,0,k) t[j].update(1,0,n,i,f[i][j]);
			for(int j:pl[i])
			{
				auto p=s.lower_bound(NODE(j,-INF));
				if(p==s.end()||p->x!=j) continue;
				if(p->v>1) p->v--;
				else s.erase(NODE(j,1));
			}
		}
		rep(i,1,n) rep(j,0,k) ans=max(ans,f[i][j]);
    	printf("%d\n",ans);
	}
    return 0;
}
```

---

## 作者：AzusidNya (赞：5)

### Description

有 $n$ 个点和 $m$ 条线段，你可以选择 $k$ 条线段删除，最大化未被线段覆盖的点的数量，输出最大值，$n, m \le 2 \times 10^5, k \le \min(m, 10)$

### Solution

一道比较好玩的 dp 题。建议评级紫。[可能更好的观看体验。](https://www.cnblogs.com/AzusidNya/p/17803979.html)

单独考虑每个点。设现在在考虑点 $i$，如果我们需要让 $i$ 不被覆盖，那么我们要清空覆盖在它上面的所有线段。

如果我们按顺序考虑每个点是否不被覆盖，即在考虑 $i$ 之前也删除了一些线段，那么这时我们发现有些覆盖在 $i$ 上面的线段之前已经删过了，而其决定因素在上一个没被覆盖的点的位置，原因如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/lropzlfa.png)

考虑 $t$ 和 $i$ 两个点和三条线段。对于 $i$ 和 $t$，与这两个点有关的线段只有三类，如图中的紫色、红色、绿色线段所示。假设现在在希望让 $i$ 点不被覆盖。首先紫色线段与 $i$ 完全无关，不会产生贡献。设 $t$ 是上一个没被覆盖的点，那么在考虑 $t$ 的时候就会把红色线段删掉，而在考虑 $i$ 的时候就不用删去红色线段。在这种情况下 $i$ 只需要删去绿色线段就行了。假设已经确定了前 $i$ 个点中不被覆盖的点，那么每次考虑上一个没被覆盖的点，不断往前推且删除绿色线段，则可以生成所有需要删除的线段。

上面的分析中已经分析出了子问题结构，考虑 dp。设 $f_{i, j}$ 表示考虑前 $i$ 个点且最后一个未被覆盖的点为 $i$，当前删去了 $j$ 条线段，最多有多少个点不被覆盖，$del(i, t)$ 表示满足 $t < l \le i \le r$ 的线段数量，也就是图中绿色线段的数量，那么可以得到状态转移方程：

$$ f_{i, j} = \max ^ {i - 1} _ {t = 0} {f_{t, j - del(i, t)} + 1}$$

这个方程直接转移是 $O(n ^ 2 k)$ 的，所以需要优化。

首先如果覆盖在 $i$ 上面的线段超过了 $k$ 条，那么 $i$ 一定会被覆盖。接下来只考虑 $i$ 上面的线段小于 $k$ 条的情况，此时有 $del(i, x) \le k$。

容易发现当 $t$ 减小的时候，$del(i, t)$ 会随之增大，且不会超过 $k$。

假设有 $tt$ 条线段覆盖在 $i$ 上面，将覆盖在 $i$ 上的线段按左端点从小到大排序，得到一个左端点序列 $\left\{L_1, L_2, \dots L_{tt}\right\}$。

这个序列将 $[1, i - 1]$ 划分成了很多个区间 $[0, L_1 - 1], [L_1, L_2 - 1], \dots, [L_{tt}, i - 1]$，对于在同一个区间中的 $t,del(i, t)$ 都是相等的。因此可以用数据结构去维护这 $tt + 1$ 个区间的最小值优化转移。

动态 st 表可以做到 $O(\log n)$ 插入一个数，$O(1)$ 查询区间 RMQ。具体而言，将 st 表倒过来，设 $st_{i, p}$ 表示以 $i$ 结尾的 $2^p$ 个数的最小值，就能够动态的在序列尾端插入，而且常数较小。用 st 表对于每个 $p$ 维护 $f_{x, p}$ 的最小值即可快速转移。

最后问题只剩下如何对于每个 $i$ 快速得到左端点序列 $L$。

利用差分思想。对每个位置维护两个集合 $add, del$，分别表示这个位置相对于上一个位置增加的线段编号和减小的线段编号。先依次考虑每条线段。考虑线段 $i$，其影响区间是 $l_i$ 到 $r_i$，那么在 $add_{l_i}$ 集合中插入 $i$，并在 $del_{r_i + 1}$ 集合中插入 $i$。

维护完 $add$ 和 $del$ 集合后，从 $1$ 号点到 $n$ 号点扫一遍。维护当前线段集合 $cover$，初始为空。考虑 $i$ 号点时，将 $add_i$ 内的元素插入到集合 $cover$ 中，然后再将 $del_i$ 内的元素从 $cover$ 中删除，这样此时的 $cover$ 集合就存储了覆盖 $i$ 号点的所有线段。如果集合大小不大于 $k$，那么集合中线段的左端点就构成了 $i$ 这个点的左端点序列 $L$。

维护完 $L$ 后按上面的思路 dp 即可。

### Code
```cpp
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <cstring>
using namespace std;
const int inf = 0x3f3f3f3f;
namespace SparseTable {
//	bool bst;
	int st[11][18][200005];
//	bool bed;
	int lg[200005];
	int Init() {
		lg[0] = -1;
		for (int i = 1; i <= 200000; i ++)
			lg[i] = lg[i >> 1] + 1;
		return 0;
	}
	struct Table {
		int tot = 0, z;
		int clear() {
			tot = 0, z = 0;
			return 0;
		}
		int insert(int x) {
			tot ++;
			st[z][0][tot] = x;
			int u = tot;
			for (int i = 1; u - (1 << i) >= 0; i ++)
				st[z][i][u] = (max(st[z][i - 1][u], st[z][i - 1][u - (1 << (i - 1))]));
			return 0;
		}
		int query(int l, int r) {
			l ++, r ++;
			if (l > r) return -inf;
			int len = lg[r - l + 1];
			return max(st[z][len][r], st[z][len][l + (1 << len) - 1]);
		}
	};
}
namespace solve1 {
	struct Node {
		int a;
		Node(int x) {
			a = x;
		}
	};
	bool operator<(Node a, Node b) {
		return a.a > b.a;
	}
	int n, m, k;
	using namespace SparseTable;
	Table st[11];
	pair<int, int> a[200005];
	#define l(u) a[u].first
	#define r(u) a[u].second
	set<int> add[200005], del[200005];
	set<Node> cover;
	vector<int> cov[200005];
	bool vis[200005];
	int f[200005][11];
	int clear() {
		for (int i = 0; i <= 10; i ++)
			st[i].clear(), st[i].z = i;
		for (int i = 1; i <= n + 1; i ++)
			cov[i].clear(), vis[i] = 0;
		return 0;
	}
	int main() {
		clear();
		cin >> n >> m >> k;
		for (int i = 1; i <= m; i ++)
			cin >> l(i) >> r(i);
		sort(a + 1, a + m + 1);
		for (int i = 1; i <= m; i ++)
			add[l(i)].insert(i), del[r(i) + 1].insert(i);
		for (int i = 1; i <= n + 1; i ++) {
			cov[i].push_back(i);
			for (int j : del[i]) cover.erase(Node(j));
			for (int j : add[i]) cover.insert(Node(j));
			add[i].clear(), del[i].clear();
			if (int(cover.size()) > k) vis[i] = 1;
			int cnt = 0;
			if (!vis[i] && (cover.size()))
				for (Node j : cover) {
					if (cnt == k) break;
					cov[i].push_back(l(j.a)), cnt ++;
				}
		}
		for (int i = 0; i <= k; i ++)
			st[i].insert(0);
		int ret = 0;
		for (int i = 1; i <= n; i ++) {
			if (vis[i]) {
				for (int j = 0; j <= k; j ++)
					st[j].insert(-inf), f[i][j] = -inf;
				continue;
			}
			int tt = cov[i].size();
			for (int j = 0; j < tt - 1; j ++)
				f[i][j] = -inf;
			for (int j = tt - 1; j <= k; j ++) {
				f[i][j] = 0;
				for (int p = 0; p < tt; p ++) {
					if (p > j) break;
					if (p != tt - 1)
						f[i][j] = max(f[i][j], st[j - p].query(cov[i][p + 1], cov[i][p] - 1) + 1);
					else
						f[i][j] = max(f[i][j], st[j - p].query(0, cov[i][p] - 1) + 1);
				}
			}
			for (int j = 0; j <= k; j ++)
				st[j].insert(f[i][j]), ret = max(ret, f[i][j])/*, cout << i << " " << j << " " << f[i][j] << "\n"*/;
		}
		cout << ret << "\n";
		return 0;
	}
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
	cin >> T;
	SparseTable::Init();
	while (T --)
		solve1::main();
	return 0;
}
```

---

## 作者：_ZSR_ (赞：2)

### [CF1889C2 Doremy's Drying Plan (Hard Version)](https://www.luogu.com.cn/problem/CF1889C2)

考虑动态规划。令 $dp_{i,j}$ 表示考虑前 $i$ 座城市，删掉了 $j$ 条线段，第 $i$ 座城市不被覆盖的最大城市数。不难想到枚举上一个不被覆盖的城市进行转移，假设为 $k$。那么我们要计算满足 $k<l \leq i \leq r$ 的线段的个数，记为 $cnt$，转移就是 $dp_{i,j}=\min_{1 \leq k < i} dp_{k,j-cnt}+1$。

直接转移的话是 $O(n^3)$ 的，考虑优化。首先思考怎么求满足上面性质的线段的个数。一条线段 $[l,r]$，只有在它覆盖的区间才会产生贡献，那么运用差分的思想，我们在 $l$ 加上它的贡献，在 $r+1$ 减去它的贡献，具体就是用 $set$ 维护一下。但是复杂度还是很高，因为我们要枚举 $1$ 到 $i-1$。其实，我们可以把 $1$ 到 $i-1$ 的所有城市按照 $cnt$ 最多分成 $11$ 段，那么我们就只要知道每一段的最大值便可以快速转移。除了查询区间最大值，我们还要进行单点修改，显然线段树可以解决。在线段树的每一个节点中，我们对于 $j \in [0,k]$，维护 $\min_{l \leq i \leq r} dp_{i,j}$。由于 $k$ 的范围很小，所以空间是可以接受的。

code
```
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N=2e5+10,M=15;
int n,m,k,T; 
int f[N][M];
multiset<int> S;
vector<pii> inter[N];
struct Tree{
	int l,r;
	int maxx[M];
}tr[N<<2];
inline Tree pushup(Tree lson,Tree rson)
{
	Tree res;
	res.l=lson.l,res.r=rson.r;
	for (int i=0;i<=k;++i) res.maxx[i]=max(lson.maxx[i],rson.maxx[i]);
	return res;
}
inline void pushup(int p)
{
	tr[p]=pushup(tr[p<<1],tr[p<<1|1]);
}
void build(int p,int inl,int inr)
{
	tr[p].l=inl,tr[p].r=inr;
	for (int i=0;i<=k;++i) tr[p].maxx[i]=-0x3f3f3f3f;
	if (inl==inr) return;
	int mid=inl+inr>>1;
	build(p<<1,inl,mid);
	build(p<<1|1,mid+1,inr);
}
void change(int p,int x,int maxx[M])
{
	if (tr[p].l==tr[p].r)
	{
		for (int i=0;i<=k;++i) tr[p].maxx[i]=maxx[i];
		return;
	}
	int mid=tr[p].l+tr[p].r>>1;
	if (x<=mid) change(p<<1,x,maxx);
	else change(p<<1|1,x,maxx);
	pushup(p);
}
Tree query(int p,int x,int y)
{
	if (x<=tr[p].l&&tr[p].r<=y) return tr[p];
	int mid=tr[p].l+tr[p].r>>1;
	if (y<=mid) return query(p<<1,x,y);
	if (x>mid) return query(p<<1|1,x,y);
	return pushup(query(p<<1,x,y),query(p<<1|1,x,y));
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>T;
	while (T--)
	{
		cin>>n>>m>>k;
		for (int i=1;i<=n;++i) 
		{
			for (int j=0;j<=k;++j) f[i][j]=-0x3f3f3f3f;
			inter[i].clear();
		}
		for (int i=1;i<=m;++i)
		{
			int l,r;
			cin>>l>>r;
			inter[l].emplace_back(l,1),inter[r+1].emplace_back(l,-1);
		}
		S.clear();
		int ans=0;
		build(1,0,n);
		change(1,0,f[0]);
		for (int i=1;i<=n;++i)
		{
			for (auto p:inter[i])
			{
				int l=p.first,d=p.second;
				if (d==-1) S.erase(S.find(l));
				else S.insert(l);
			}
			if (S.size()>k) continue;
			int r=i-1,cnt=0;
			for (auto it=S.rbegin();it!=S.rend();++it)
			{
				int l=*it;
				if (l<=r)
				{
					Tree t=query(1,l,r);
					for (int j=cnt;j<=k;++j) f[i][j]=max(f[i][j],t.maxx[j-cnt]+1);
				}
				r=l-1;
				++cnt;
			}
			Tree t=query(1,0,r);
			for (int j=cnt;j<=k;++j) f[i][j]=max(f[i][j],t.maxx[j-cnt]+1);		
			for (int j=1;j<=k;++j) ans=max(ans,f[i][j]);
			change(1,i,f[i]);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：lzytag (赞：2)

提供一个无 DS 的超级好写做法。

首先有一个比较常见的转化，将区间按左端点从小到大排序，令 $f_{i,j,R}$ 代表选完了前 $i$ 个区间，删了 $j$ 个区间，剩下的区间中最右端点为 $R$（小于 $L$ 则视为 $L-1$）的情况下，小于等于 $L$ 的城中最大的干城数量，然后考虑转移。

我们从小到大枚举 $L$，当我们 $L$ 要加上 $1$ 时，枚举所有左端点为 $L+1$ 的区间，枚举到 $[l,r]$ 时，我们的转移方式为。

$$ f_{L,i,r} \leftarrow \max_{x=1}^{r} f_{L,i,x}$$
$$ f_{L,i,R} \leftarrow f_{L,i-1,R} (R < r)$$
$$ f_{L,i,R} \leftarrow f_{L,i,R} (R > r) $$

最后，让 $L$ 加上 $1$。

$$ f_{L+1,i,R} \leftarrow f_{L,i,R} (R > L+1)$$
$$ f_{L+1,i,L+1} \leftarrow \max(f_{L,i,L} + 1,f_{L,i,L+1})$$

我们发现有很多转移的 $j,R$ 压根没发生改变，可以压掉第一维。剩下的可能可以用 DS 维护，但我没想明白 DS 咋做。所以我们暴力转移，一个区间复杂度贡献就是 $O(len\times k)$，其中 $len$ 为区间长度。

怎么让 $\sum len$ 处于一个可以接受的范围内呢？我们发现，如果一个点有大于 $k$ 个区间覆盖，那么他一定不会产生贡献，所以可以把这些点全部删掉，剩下的点点数为 $O(n)$，每个点上都覆盖了最多 $k$ 个区间，所以所有区间长度加起来就成了 $O(n\times k)$ 了，所以复杂度就是 $O(n\times k^2)$ 了。


---

## 作者：yllcm (赞：1)

不会 RMQ 怎么办？

设计 DP 状态：$f_{u,i}$ 表示最后一个未被区间覆盖的点为 $u$，删除了 $i$ 个线段，最多有多少个未被区间覆盖的点。

转移很简单：$f_{u,i}+1\to f_{v,i+w(u,v)}$。其中 $w(u,v)$ 表示包含 $u$ 但不包含 $v$ 的线段数量。

注意到只有覆盖次数不超过 $k$ 的点才有可能在最终答案中不被任意区间覆盖，所以可以把覆盖 $v$ 的所有区间提出来，假设一共有 $c_v$ 个。将所有区间按照左端点从小到大排序，假设第 $i$ 个区间为 $[l_i,r_i]$。那么计算 $w(u,v)$ 的方式如下：找到最大的 $i$ 使得 $l_i\leq u$，那么贡献为 $c_v-i$。

注意到 $w(u,v)$ 只与最大的 $i$ 有关，所以可以考虑分步转移：把点转移到线段上，然后再由线段转移到点。设 $g_{i,j}$ 表示所有满足 当前覆盖 $v$ 的区间中，$i$ 为最大的满足 $l_i\leq u$ 的区间 的点 $u$ 的 $f_{u,j}$ 的最大值，那么转移是：

* 加入一个点 $u$，此时找到覆盖它的左端点最大的区间，转移。
* 删除一个区间，假设当前被删除的区间的左端点是 $l_i$，那么找到覆盖点 $l_i$ 的左端点最大的区间，转移。

使用 set+扫描线 维护覆盖当前点的所有线段，时间复杂度 $\mathcal{O}(n\log n+nk^2)$。为了方便实现，我们默认存在一个 $[0,n+1]$ 的区间，并在计算个数的时候忽略它。[code](https://codeforces.com/contest/1889/submission/231126298)


---

## 作者：Diaоsi (赞：1)

[Doremy's Drying Plan (Hard Version)](https://www.luogu.com.cn/problem/CF1889C2)

扫描线 + $\mathtt{st}$ 表优化 $\mathtt{dp}$ 

为方便表述，原题中的 $n$ 和 $k$ 在此题解中用 $N$ 和 $K$ 代替。

首先还是反向考虑，对于一个点，当且仅当覆盖它的区间个数小于等于 $K$ 时，它才有可能对答案产生贡献。

于是我们可以得到这样一个 $\mathtt{dp}$ 方程，记 $f_{i,j}$ 表示前 $i$ 个点中最后一个空点为 $i$，左端点在 $[1,i]$ 中的区间被删了 $j$ 个时的最大空点个数。

有如下转移：

$$f_{i,j}\leftarrow1+\max_{k=1}^{i-1}f_{k,j-t}$$

最终答案是在**所有**状态中取最大值。

方程中的 $t$ 表示删掉至少 $t$ 个覆盖 $i$ 的区间后，位置 $i$ 和 $k$ 才有可能分别成为空点。

发现这个方程不是特别好转移，注意到不同的 $t$ 至多有 $K+1$ 个，而且还有如下性质：

>考虑将覆盖 $i$ 的若干区间的左端点 $p_u$ 进行升序排序，这些左端点将 $[1,i-1]$ 划分成了若干个形如 $[p_u,p_{u+1}-1]$ 的区间，而每一个区间内的 $t$ 均相同且随着 $u$ 增大而减小。

于是我们得到如下算法：对于每一个覆盖它的区间个数小于等于 $K$ 的点 $i$，我们都可以维护一个覆盖它的区间的左端点的可重集，然后在至多 $K+1$ 个区间上求最值进行转移。

实现细节方面：

维护可重集可以使用 ```std::multiset``` 这类稳定 $\mathcal{O}(\log N)$ 插入的数据结构，并用扫描线控制插入和删除。为了方便实现我采用了暴力插入的有序 ```std::vector```，在本题中表现优秀。

求区间最值可以开 $K+1$ 个 $\mathtt{st}$ 表，因为在 $\mathtt{st}$ 表的端点插入新值是 $\mathcal{O}(\log N)$ 的，这样就可以实现 $\mathcal{O}(\log N)$ 插入 $\mathcal{O}(1)$ 查询。

注意处理一些细节情况（如 $p_u$ 重合等），就可以通过此题。

时间复杂度 $\mathcal{O}\left(NK(K+\log N)\right)$ 

```Code:```

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=200050,M=2000050,INF=0x3f3f3f3f;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int T,n,m,ans,K,lg[N],st[22][N][22];
struct Set{
	vector<int> h;
	void ins(int x){
		h.insert(upper_bound(h.begin(),h.end(),x),x);
	}
	void ers(int x){
		h.erase(lower_bound(h.begin(),h.end(),x));
	}
}add[N],del[N],s;
void insert(int i,int d){
	for(int j=1;i-(1<<(j-1))>0;j++)
		st[d][i][j]=max(st[d][i][j-1],st[d][i-(1<<(j-1))][j-1]);
}
int query(int l,int r,int d){
	if(l>r)return 0;
	int ln=lg[r-l+1];
	return max(st[d][r][ln],st[d][l+(1<<ln)-1][ln]);
}
int main(){
	scanf("%d",&T);
	for(int i=2;i<N;i++)lg[i]=lg[i>>1]+1;
	while(T--){
		scanf("%d%d%d",&n,&m,&K);
		for(int i=1;i<=m;i++){
			int l,r;
			scanf("%d%d",&l,&r);
			add[l].ins(l),del[r+1].ins(l);
		}
		for(int z:add[1].h)s.ins(z);
		if((int)s.h.size()<=K)st[s.h.size()][1][0]=1;
		for(int i=2;i<=n;i++){
			for(int z:add[i].h)s.ins(z);
			for(int z:del[i].h)s.ers(z);
			s.ins(i);
			int t=s.h.size()-1;
			if(!t)
				for(int k=0;k<=K;k++)
					st[k][i][0]=max(st[k][i][0],query(1,i-1,k)+1);
			else if(t<=K){
				for(int j=0,l,r,c=0;j<(int)s.h.size();j++,t--){// t -> need to delete t intervals
					l=!j?1:s.h[j-1];
					for(;s.h[c]==l&&c<(int)s.h.size()-1;c++);//find next
					r=s.h[c]-1;
					if(l>r)continue;
					for(int k=0;k+t<=K;k++){
						int val=query(l,r,k);
						if(val||!j)st[k+t][i][0]=max(st[k+t][i][0],val+1);
					}
				}
			}
			for(int j=0;j<=K;j++)insert(i,j);
			s.ers(i);
		}
		for(int k=0;k<=K;k++)
			ans=max(ans,query(1,n,k));
		printf("%d\n",ans);
		for(int i=1;i<=n;i++)
			for(int k=0;k<=K;k++)st[k][i][0]=0,insert(i,k);
		for(int i=1;i<=n+1;i++)add[i].h.clear(),del[i].h.clear();//clear
		s.h.clear();ans=0;
	}
	return 0;
}
```


---

