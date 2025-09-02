# [COTS 2023] 题 Zadatak

## 题目背景

译自 [Izborne Pripreme 2023 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2023/) D2T3。$\texttt{1s,0.5G}$。

祝 NaCly_Fish 生日快乐！（2024.7.28）

## 题目描述

Jura 有 $N$ 个正方形，标号为 $1\sim N$，第 $i$ 个正方形边长为 $a_i$，且 $2\mid a_i$。起初，这些正方形都是黑色的。

Jura 决定花费他生命中的 $(N-1)$ 秒来玩这些正方形。在第 $i$ 秒时，Jura 将第 $x_i$ 和第 $y_i$ 个正方形合并成第 $(N+i)$ 个正方形（合并后，第 $x_i$ 和第 $y_i$ 个正方形不再存在）。

合并正方形时，将两个正方形的中心对齐，边缘平行对齐地摆在平面中。新的正方形的大小为合并的两个正方形中较大那个的大小；它的颜色是原来两个正方形颜色的「异或和」（黑+黑=白，白+白=白，黑+白=黑，白+黑=黑）。合并正方形的**代价**为，两个正方形合并前（但是已经按照刚才的要求摆好），正方形的交中，满足在两个正方形中均为黑色的区域的面积。

你需要输出每次合并操作的代价。

下图为正方形合并的示例：

![](https://cdn.luogu.com.cn/upload/image_hosting/8uquyi9a.png)

## 说明/提示

### 样例解释

样例 $1$ 的最后一个操作如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/rvjzj56s.png)

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le N\le 10^5$；
- $2\le a_i\le 10^6$。
- $2\mid a_i$。
- $1\le x_i,y_i\le N+i-1$
- 操作前正方形存在，且 $x_i\neq y_i$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $14$  | $N\le 5\, 000$  |
| $2$  | $25$  | $x_1=1,y_1=2$；$\forall 2\le i\le N-1$，$x_i=i+1,y_i=N+i-1$  |
| $3$  | $17$  | $\exists k\in \mathbb{N}$，使得 $2^k=N$；$x_i=2i-1,y_i=2i$ |
| $4$  | $21$  | $n\le 30\, 000$ |
| $5$  | $23$  | 无额外约束 |

## 样例 #1

### 输入

```
6 
8 6 2 4 2 6
1 2
3 4
5 7
6 8
9 10```

### 输出

```
36
4
0
12
4```

## 样例 #2

### 输入

```
7 
4 2 6 6 2 4 2
1 2
3 8
4 9
5 10
6 11
7 12```

### 输出

```
4
12
24
0
16
0 ```

## 样例 #3

### 输入

```
8
4 10 2 10 6 8 4 12
1 2
3 4
5 6
7 8
9 10
11 12
13 14```

### 输出

```
16
4
36
16
84
28
0```

# 题解

## 作者：xiezheyuan (赞：6)

## 思路

不是，真的没人写树上启发式合并吗？

考虑建一个类似“重构树”的东西，对于每一次合并，我们将合并得到的点，向被合并的两点各连一条边。这样子我们可以得到一棵树（准确来说，是二叉树）。

然后考虑题面中这个“合并”的性质，容易发现交换合并顺序不会影响图案以及总代价和。于是可以考虑一些比较一般的做法，比如树上启发式合并。

考虑到树上启发式合并的性质，使得我们只会将一个图案和纯黑矩形合并，所以假如我们维护矩形从中心到外围每一圈为黑色或白色，则可以看成是前缀取反，我们需要维护黑色面积，稍加转换可以看成前缀求和，这个都是可以用线段树维护的。

还需要考虑到我们无法一次性精确求得一次合并的贡献，只能求出若干次合并的和，不过由于交换不会改变总代价和，所以可以用父节点的和减去子节点的和来求出父节点的答案。

清空的话，只需要再取反一次即可。

复杂度稍劣，为 $O(n\log n\log a_i)$。不过可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;

const int N = 2e5 + 5, V = 1e6 + 5;
int n, a[N];
vector<int> g[N];

struct node{
    long long val, sum;
    bool tag;
} t[V << 2];

void pushdown(int i){
    if(t[i].tag){
        t[ls].tag ^= 1;
        t[rs].tag ^= 1;
        t[ls].val = t[ls].sum - t[ls].val;
        t[rs].val = t[rs].sum - t[rs].val;
        t[i].tag = 0;
    }
}

void pushup(int i){
    t[i].val = t[ls].val + t[rs].val;
    t[i].sum = t[ls].sum + t[rs].sum;
}

void build(int i, int l, int r){
    if(l == r){
        t[i].sum = 1ll * l * l - 1ll * (l - 1) * (l - 1);
        return;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(i);
}

void update(int ql, int qr, int i, int l, int r){
    if(ql <= l && r <= qr){
        t[i].tag ^= 1;
        t[i].val = t[i].sum - t[i].val;
        return;
    }
    pushdown(i);
    if(ql <= mid) update(ql, qr, ls, l, mid);
    if(mid < qr) update(ql, qr, rs, mid + 1, r);
    pushup(i);
}

long long query(int ql, int qr, int i, int l, int r){
    if(ql <= l && r <= qr) return t[i].val;
    pushdown(i);
    long long ans = 0;
    if(ql <= mid) ans += query(ql, qr, ls, l, mid);
    if(mid < qr) ans += query(ql, qr, rs, mid + 1, r);
    return ans;
}

int siz[N], son[N], dfn[N], rev[N];
long long ans[N];

void dfs(int u){
    siz[u] = 1;
    dfn[u] = ++dfn[0]; rev[dfn[u]] = u;
    for(int v : g[u]){
        dfs(v);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] =v;
    }
}

long long solve(int u, bool keep = false){
    // cerr << "IN " << u << '\n';
    long long ytxy = 0, yzy = 0;
    for(int v : g[u]){
        if(v != son[u]) yzy += solve(v);
    }
    if(son[u]) ytxy = solve(son[u], true);
    yzy += ytxy;
    // cerr << "ADD " << u << '\n';
    for(int v : g[u]){
        if(v == son[u]) continue;
        for(int i=0;i<siz[v];i++){
            int j = rev[dfn[v] + i];
            if(siz[j] != 1) continue;
            ytxy += query(1, a[j], 1, 1, (int)(1e6));
            update(1, a[j], 1, 1, (int)(1e6));
        }
    }
    if(siz[u] == 1){
        ytxy += query(1, a[u], 1, 1, (int)(1e6));
        update(1, a[u], 1, 1, (int)(1e6));
    }
    ans[u] = ytxy - yzy;
    if(!keep){
        for(int v : g[u]){
            for(int i=0;i<siz[v];i++){
                int j = rev[dfn[v] + i];
                if(siz[j] != 1) continue;
                update(1, a[j], 1, 1, (int)(1e6));
            }
        }
        if(siz[u] == 1){
            update(1, a[u], 1, 1, (int)(1e6));
        }
    }
    // cerr << "OUT " << u << '\n';
    return ytxy;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    build(1, 1, (int)(1e6));
    for(int i=1,x,y;i<n;i++){
        cin >> x >> y;
        g[n + i].push_back(x);
        g[n + i].push_back(y);
    }
    dfs((n << 1) - 1);
    solve((n << 1) - 1);
    for(int i=n+1;i<(n << 1);i++) cout << ans[i] << '\n';
    return 0;
}

// Written by xiezheyuan

```

---

## 作者：pig1121 (赞：5)

考虑线段树合并。

先试图用线段树表示状态。注意到合并是中心对齐且 $2\mid a_i$，故只需要维护正方形的一角（输出时将答案乘以 $4$）。某一个位置的颜色只与它到中心的水平（或竖直）距离有关，故考虑用线段树维护距中心为某个值的点的颜色。

设节点 $i$ 维护的范围为 $[l_i,r_i]$，则区域面积 $len_i=r_i^2-(l_i-1)^2$，另维护 $sum_i$ 表示在 $[l_i,r_i]$ 中**黑色**区域的总面积，$tag_i$ 表示区间 $[l_i,r_i]$ 是否要整体取反（合并和初始化要用的）。

一开始对 $rt_i$ 打 $[1,\frac{a_i}2]$ 的区间反转（置为黑色）。

进行合并时，叶子节点的值为 $sum_u\oplus sum_v$ （$\oplus$ 表示异或），代价等于 $[sum_u>0 \land sum_v>0]\times len_i$（只有两者都为黑才会产生 $len$ 的代价），非叶子节点递归合并。

然后你就愉快地 TLE 了……

为神马？

因为你的初始点数可能是满的，每次合并可以退化到 $O(n)$。

但是我们发现，如果这个区间内的所有数都是同一个值，那我们可以直接合并然后取反，就像这样：

```cpp
if(tr[u].sum==tr[u].len){
    int res=tr[v].sum;
    pusht(v,1);
    return{v,res};
}
```
这样相当于每棵树初始只有 $O(\log n)$ 个点，合并 $n$ 次复杂度正确。

哦对了，不要忘记 `pushdown`，而且由于新建了 $n-1$ 棵树，`rt` 数组要开 $2n$。

没了，代码：

```cpp
#include<iostream>
#include<cassert>
#include<algorithm>
#include<vector>
#define int long long
#define endl '\n'
#ifdef ONLINE_JUDGE
#define getc getc_unlocked
#endif
#define str stdin
using namespace std;

inline void read(int&x){
	x=0;
	int f=1;
	char ch=getc(str);
	while(ch<'0'||'9'<ch){
		if(ch=='-')f=-1;
		ch=getc(str);
	}
	while('0'<=ch&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getc(str);
	}
	x*=f;
}

namespace segtree{
	struct node{
		int ls,rs,sum,len,tag;
	};
	node tr[13000005];
	int tot;
	inline void update(int p){
		tr[p].sum=tr[tr[p].ls].sum+tr[tr[p].rs].sum;
	}
	inline void pusht(int p,int k){
		tr[p].sum=tr[p].len-tr[p].sum;
		tr[p].tag^=k;
	}
	inline void pushdown(int p){
		int ls=tr[p].ls,rs=tr[p].rs;
		if(tr[p].tag){
			pusht(ls,tr[p].tag);
			pusht(rs,tr[p].tag);
			tr[p].tag=0;
		}
	}
	int nnd(int l,int r){
		int p=++tot;
		tr[p].len=r*r-(l-1)*(l-1);
		return p;
	}
	void modify(int&p,int x,int y,int l,int r,int k){
		if(!p)p=nnd(l,r);
		if(x<=l&&r<=y){
			pusht(p,k);
			return;
		}
		int mid=(l+r)>>1;
		if(!tr[p].ls)tr[p].ls=nnd(l,mid);
		if(!tr[p].rs)tr[p].rs=nnd(mid+1,r);
		pushdown(p);
		if(x<=mid)modify(tr[p].ls,x,y,l,mid,k);
		if(mid<y)modify(tr[p].rs,x,y,mid+1,r,k);
		update(p);
	}
	pair<int,int>merge(int u,int v,int l,int r){
	//	cerr<<u<<' '<<v<<' '<<l<<' '<<r<<endl;
		if(!u||!v)return{u|v,0};
		if(!tr[u].sum)return{v,0};
		if(!tr[v].sum)return{u,0};
		if(tr[u].sum==tr[u].len){
			int res=tr[v].sum;
	//		cerr<<tr[u].sum<<' '<<tr[u].len<<' '<<res<<endl<<flush;
			pusht(v,1);
	//		cerr<<tr[v].sum<<endl<<flush;
			return{v,res};
		}
		if(tr[v].sum==tr[v].len){
			int res=tr[u].sum;
	//		cerr<<tr[v].sum<<' '<<tr[v].len<<' '<<res<<endl<<flush;
			pusht(u,1);
	//		cerr<<tr[u].sum<<endl<<flush;
			return{u,res};
		}
		if(l==r){
			int res=(tr[u].sum&&tr[v].sum)*tr[u].len;
	//		cerr<<tr[u].sum<<' '<<tr[v].sum<<' '<<tr[u].len<<' '<<res<<endl;
			tr[u].sum^=tr[v].sum;
			return {u,res};
		}
		int mid=(l+r)>>1;
//		if(!tr[u].ls)tr[u].ls=nnd(l,mid);
//		if(!tr[v].ls)tr[v].ls=nnd(l,mid);
//		if(!tr[u].rs)tr[u].rs=nnd(mid+1,r);
//		if(!tr[v].rs)tr[v].rs=nnd(mid+1,r);
		pushdown(u);pushdown(v);
		int res=0;
		pair<int,int>tmp=merge(tr[u].ls,tr[v].ls,l,mid);
		tr[u].ls=tmp.first,res+=tmp.second;
		tmp=merge(tr[u].rs,tr[v].rs,mid+1,r);
		tr[u].rs=tmp.first,res+=tmp.second;
		update(u);
		return {u,res};
	}
}
int rt[200005],a[100005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
//	freopen("P10834_4.in","r",stdin);
//	freopen("P10834_4.out","w",stdout);
	int n;
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);
		a[i]/=2;
		segtree::modify(rt[i],1,a[i],1,5e5,1);
	}
	for(int i=1;i<n;i++){
		int x,y;
		read(x);read(y);
		pair<int,int>tmp=segtree::merge(rt[x],rt[y],1,5e5);
		rt[i+n]=tmp.first;
//		cerr<<"MERGE "<<i<<" COMPLETED\n"<<flush;
		cout<<tmp.second*4<<endl;
//		cerr<<i<<endl<<flush;
//		cout<<flush;
	}
	return 0;
}
```

---

## 作者：zhangshiyan (赞：4)

# P10834 [COTS 2023] 题 Zadatak
[R190281008 记录详情](https://www.luogu.com.cn/record/190281008)

## Solution
**算法：线段树合并**

我们可以将一个正方形拆成若干个小正方形，我们发现：
1. 每一次合并满足结合律和交换律。

1. 整个操作过程中的代价与操作顺序无关。显然白色块对答案无影响，不用考虑，我们只要考虑黑色块，而黑色块相互等价，以任意顺序操合并，答案总是不变的。

根据以上性质，我们便可以考虑使用线段树合并。
不会的详见[线段树合并 - OI Wiki](https://oi-wiki.org/ds/seg/#线段树合并 )。

有 $n$ 个正方形，有 $n−1$ 次合并，提示我们建立一颗树。

每一次合并，我们将合并得到的正方形 $n+i$，向被合并的两点 $u$ 和 $v$ 各连一条边。这样子我们可以得到一棵二叉树。

合并后，第 $x_i$ 和第 $y_i$ 个正方形不再存在，又因为进行了 $n-1$ 次的合并，不难发现这颗二叉树有且仅有一个根，每一个非叶子节点有且仅有两个儿子节点。

又注意到 $2\mid a_i$，所以 $a_i$ 的边长为偶数，提示我们可以将正方形分成左上，右上，右下，左下四个部分，我们只需要考虑其中的一个部分，最终结果乘 $4$ 即可。

我们用第 $i$ 个叶子节点表示矩形左上角 $(0,0)$ 到 $(i,i)$ 的面积，我们用 $area_i$ 维护，使用区间合并，将右侧区间全部合并到左侧区间，发现左侧区间可能消去一块面积，也可能补上一块面积，而情况取决于左右两侧区间覆盖了奇数次，还是偶数次，我们用 $cnt_i$ 维护这个信息即可。

### 优化
当你做完后，开心地提交后，发现错了，为什么呢？由于合并后，第 $x_i$ 和第 $y_i$ 个正方形不再存在，所以会占用很多额外的空间，怎么优化呢？

1. 由于数据范围比较小，$1\le N\le 10^5$，$2\le a_i\le 10^6$，我们便可以大胆地开大数组。

2. 或者是将删去的节点保存到 $havedelete_i$ 数组中，重复使用。

我采取的是第一种方式优化，具体实现见代码。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 1e18

ll read()
{
	ll x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-')
		{
			f = -1;
		}
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 1) + (x << 3) + c - '0';
		c = getchar();
	}
	return x * f;
}

const ll N = 2e6, M = 1e6;

vector<ll> g[2 * N + 5];//存图
ll tot;//动态开点
ll a[2 * N + 5];//每个正方形的边长
ll in[2 * N + 5];//每个节点的入度，为了求出根节点，因为根节点没有入度
ll rt[2 * N + 5], ls[2 * N + 5], rs[2 * N + 5];//rt分别表示节点编号，ls左儿子编号，rs右儿子编号，
ll cnt[2 * N + 5], area[2 * N + 5];//cnt分别表示被覆盖了多少次，面积是多少。
ll ans[2 * N + 5];//ans分别表示答案。

void pushup(ll u)
{
	cnt[u] = cnt[ls[u]] ^ cnt[rs[u]];
	if(cnt[rs[u]] == 1)
	{
		area[u] = area[rs[u]] - area[ls[u]];
	}
	else
	{
		area[u] = area[rs[u]] + area[ls[u]];
	}
}

ll add(ll id, ll len, ll l, ll r)
{
	if(!id)
	{
		id = ++tot;//动态开点
	}
	if(l == r)
	{
		cnt[id] ^= 1;//求被覆盖了多少次
		area[id] = cnt[id] * l * l;//求新的面积
		return id;
	}
	ll mid = (l + r) >> 1;
	if(len <= mid)
	{
		ls[id] = add(ls[id], len, l, mid);//递归左节点
	}
	if(len >= mid + 1)
	{
		rs[id] = add(rs[id], len, mid + 1, r);//递归右节点
	}
	pushup(id);
	return id;
}

ll merge(ll a, ll b, ll l, ll r)//合并的模板，不会详见https://oi-wiki.org/ds/seg/#线段树合并
{
	if(!a)
	{
		return b;
	}
	if(!b)
	{
		return a;
	}
	if(l == r)
	{
		cnt[a] ^= cnt[b];//判断左右区间合并后被覆盖了多少次
		area[a] = cnt[a] * l * l;//求新的面积
		return a;
	}
	ll mid = (l + r) >> 1;
	ls[a] = merge(ls[a], ls[b], l, mid);
	rs[a] = merge(rs[a], rs[b], mid + 1, r);
	pushup(a);
	return a;
}

void solve(ll u)
{
	if(g[u].empty())//如果是叶子节点
	{
		rt[u] = add(rt[u], a[u], 1, M);//初始化
		return ;
	}
	ll lson = g[u][0], rson = g[u][1];//因为每一个非叶子节点有且仅有两个儿子节点
	solve(lson);
	solve(rson);//先递归，从叶子节点往上求答案
	ll area_lson = area[rt[lson]];//求左侧区间的面积
	ll area_rson = area[rt[rson]];//求右侧区间的面积
	rt[u] = merge(rt[lson], rt[rson], 1, M);// 将左右区间合并到父亲节点
	ll area_rt = area[rt[u]];//求左右侧区间合并后的面积
	ans[u] = (area_lson + area_rson - area_rt) / 2;//使用容斥原理求答案
}

int main()
{
	ll n = read();
	for(ll i = 1; i <= n; i++)
	{
		a[i] = read();
		a[i] /= 2;
	}
	for(ll i = 1; i < n; i++)
	{
		ll u = read(), v = read();
		g[n + i].push_back(u);
		g[n + i].push_back(v);
		in[u]++, in[v]++;
	}
	//求出根节点
	ll root = -1;
	for(ll i = 1; i < n * 2; i++)
	{
		if(in[i] == 0)
		{
			root = i;
			break;
		}
	}
	solve(root);// 从根节点往下求答案
	for(ll i = n + 1; i < n * 2; i++)
	{
		printf("%lld\n", ans[i] * 4);//最终结果要乘4
	}
	return 0;
}

```

---

## 作者：_Ch1F4N_ (赞：2)

评价：比较中规中矩的线段树合并题，可以用动态 dp 相关技巧做到更优，不过没有必要。

考虑维护正方形的半条斜对角线上的黑白情况，不难发现的是这条线上黑白一定在形如 $\sqrt 2$ 乘整数 $k$ 的点上交替，且区间 $[\sqrt 2 \times (k-1),\sqrt 2 \times k]$ 的贡献为 $4 \times k^2 - 4 \times (k-1)^2$，考虑将这样的区间看成线段树上一个点，并将贡献作为其权值，那么考虑在线段树合并的过程中计算贡献，更新权值即可，注意这里线段树上带区间翻转标记用来维护图形的异或，合并过程中遇到某个左右儿子均没有标记的点需要直接将这个点的标记打在需要合并的节点上。

时空复杂度 $O(n \log n)$，使用 top tree 与动态 dp 可以将空间优化到线性，且时间复杂度仍然为 $O(n \log n)$，这个做法以后再讲。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxv = 1e6+114;
const int top = 1e6;
const int maxn = 1e5+114;
int pre[maxv];
int tr[maxn*70],tag[maxn*70];//0 无标记 1 标记翻转
int ls[maxn*70],rs[maxn*70];
int rt[maxn<<1];
int tot,n;
void pushdown(int cur,int lt,int rt){
    if(ls[cur]==0) ls[cur]=++tot;
    if(rs[cur]==0) rs[cur]=++tot;
    if(tag[cur]==1){
        int mid=(lt+rt)>>1;
        tr[ls[cur]]=pre[mid]-pre[lt-1]-tr[ls[cur]];
        tag[ls[cur]]^=1;
        tr[rs[cur]]=pre[rt]-pre[mid]-tr[rs[cur]];
        tag[rs[cur]]^=1;
        tag[cur]=0;
    }
}
void pushup(int cur){
    tr[cur]=tr[ls[cur]]+tr[rs[cur]];
}
int ans;
int merge(int a,int b,int lt,int rt){
    if(lt==rt){
        ans+=min(tr[a],tr[b]);
        if(tag[b]!=0){
            tr[a]=pre[rt]-pre[lt-1]-tr[a];
            tag[a]^=1;
            tag[b]=0;
        }
        return a;
    }
    if(ls[a]==0&&rs[a]==0){
        if(tr[a]!=0) ans+=tr[b];
        if(tag[a]!=0){
            tr[b]=pre[rt]-pre[lt-1]-tr[b];
            tag[b]^=1;
            tag[a]=0;
        }
        return b;
    }
    if(ls[b]==0&&rs[b]==0){
        if(tr[b]!=0) ans+=tr[a];
        if(tag[b]!=0){
            tr[a]=pre[rt]-pre[lt-1]-tr[a];
            tag[a]^=1;
            tag[b]=0;
        }
        return a;
    }
    int mid=(lt+rt)>>1;
    pushdown(a,lt,rt),pushdown(b,lt,rt);
    ls[a]=merge(ls[a],ls[b],lt,mid);
    rs[a]=merge(rs[a],rs[b],mid+1,rt);
    pushup(a);
    return a;
}
void cover(int cur,int lt,int rt,int l,int r){
    if(l<=lt&&rt<=r){
        tr[cur]=pre[rt]-pre[lt-1]-tr[cur];
        tag[cur]^=1;
        return ;
    }
    pushdown(cur,lt,rt);
    int mid=(lt+rt)>>1;
    if(l<=mid) cover(ls[cur],lt,mid,l,r);
    if(r>mid) cover(rs[cur],mid+1,rt,l,r);
    pushup(cur);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    for(int i=1;i<maxv;i++) pre[i]=i*i;
    cin>>n;
    for(int i=1;i<=n;i++) rt[i]=++tot;
    for(int i=1;i<=n;i++){
        int a;
        cin>>a;
        a/=2;
        cover(rt[i],1,top,1,a);
    }
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        ans=0;
        rt[i+n]=merge(rt[x],rt[y],1,top);
        cout<<ans*4<<'\n';
    }
    return 0;
}

```

---

## 作者：Engulf (赞：1)

注意到无论怎么合并，正方形都是中心对称、轴对称的，不妨只维护左上角的正方形区域，合并的代价 $\times 4$ 就是答案。

进而发现到中心水平或竖直距离相等的点颜色总是一样的，也就是这个样子：![](https://cdn.luogu.com.cn/upload/image_hosting/eh96kuzv.png)

可以看作是许多 L 顺时针旋转 $90$ 度的位似图形的叠加。

用一个序列 $a_i$ 表示到中心水平（或竖直）距离为 $i$ 的黑色面积，容易发现 $a_i$ 只有两种取值：
- 如果这个区域是白色，$a_i=0$
- 如果这个区域是黑色，$a_i = i^2-(i-1)^2$

现在考虑怎么维护正方形的叠加，不妨用线段树维护序列 $a$，一开始对于每个正方形 $i$，在第 $i$ 棵线段树上将区间 $[1, \dfrac{a_i}{2}]$ 异或 $1$（白置为黑），然后线段树合并，在叶子节点计算贡献，若均为黑就加上面积。

这在时间和空间上都无法承受，因为动态开点线段树做区间操作时为了下放懒标记，会不断新增节点，直接就把线段树补满为 $O(n)$ 个节点了，合并 $n$ 次复杂度 $O(n ^ 2)$。

解决方案是对于那些没有儿子的节点，直接把这个修改打到合并的对应节点上，效果是一样的。

![](https://cdn.luogu.com.cn/upload/image_hosting/7j0cjxrn.png)

如图，由于 $x$ 没有子节点，整个 $x$ 子树的操作都是一样的，与其一个一个补出一样的节点合并过去，还不如直接在 $y$ 那里打上 $x$ 的标记。

这样，最多补一层节点，时空复杂度就都是 $O(n\log n)$ 了。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 1e5 + 5, M = 5e5 + 5;

int n;

int root[2 * N];
int ls[M * 20], rs[M * 20], idx;
int rev[M * 20];
ll area[M * 20];

void pushdown(int p, int l, int r) {
    if (!rev[p]) return;

    if (!ls[p]) ls[p] = ++idx;
    if (!rs[p]) rs[p] = ++idx;

    int mid = l + r >> 1;
    rev[ls[p]] ^= 1, area[ls[p]] = 1ll * mid * mid - 1ll * (l - 1) * (l - 1) - area[ls[p]];
    rev[rs[p]] ^= 1, area[rs[p]] = 1ll * r * r - 1ll * mid * mid - area[rs[p]];

    rev[p] ^= 1;
}

void reverse(int &p, int l, int r, int L, int R) {
    if (!p) p = ++idx;
    if (L <= l && r <= R) {
        area[p] = 1ll * r * r - 1ll * (l - 1) * (l - 1) - area[p];
        rev[p] ^= 1;
        return;
    }
    pushdown(p, l, r);
    int mid = l + r >> 1;
    if (L <= mid) reverse(ls[p], l, mid, L, R);
    if (mid < R) reverse(rs[p], mid + 1, r, L, R);
    area[p] = area[ls[p]] + area[rs[p]];
}

int merge(int x, int y, int l, int r, ll &ans) {
    if (!x || !y) return x + y;
    if (l == r) {
        ans += min(area[x], area[y]);
        area[x] ^= area[y];
        return x;
    }

    if (!ls[x] && !rs[x]) {
        ans += min(area[x], area[y]);
        if (rev[x]) {
            area[y] = 1ll * r * r - 1ll * (l - 1) * (l - 1) - area[y];
            rev[y] ^= 1;
        }
        return y;
    }
    if (!ls[y] && !rs[y]) {
        ans += min(area[x], area[y]);
        if (rev[y]) {
            area[x] = 1ll * r * r - 1ll * (l - 1) * (l - 1) - area[x];
            rev[x] ^= 1;
        }
        return x;
    }

    pushdown(x, l, r), pushdown(y, l, r);
    int mid = l + r >> 1;
    ls[x] = merge(ls[x], ls[y], l, mid, ans);
    rs[x] = merge(rs[x], rs[y], mid + 1, r, ans);
    area[x] = area[ls[x]] + area[rs[x]];
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    for (int i = 1, a; i <= n; i++) {
        cin >> a;
        reverse(root[i], 1, 5e5, 1, a / 2);
    }

    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        ll ans = 0;
        root[i + n] = merge(root[x], root[y], 1, 5e5, ans);
        cout << ans * 4 << "\n";
    }

    return 0;
}
```

---

## 作者：Felix72 (赞：1)

这是一道线段树合并的好题，如果用启发式合并也可以用略低的思维难度通过，但考虑到训练价值问题还是用了线段树合并。

对于线段树的题目，其核心就是信息的结合律以及可快速合并性。我们维护以下信息，以达到上面两个要求：

- 对于一个覆盖范围为 $[l, r]$ 的树点，我们仅考虑这个范围之内的边界线（边界线指图形中黑白交替的部分）
- $data$ 表示最中心的位置是什么颜色；
- $sum$ 表示这个图形**不考虑 $[1, l)$ 范围边界线时**的黑色面积大小；

这些信息可以简单地在合并时维护，但怎样计算答案是一个问题。

不妨考虑在计算大范围时先不管正方形在 $[1, l)$ 范围的边界线，如果多算了就挖去，少算了就加上。这样就可以仅用当前节点的信息求答案了。

我们在合并过程中维护这些东西：

- $nx$ 和 $ny$ 表示节点编号
- 当前考虑的范围
- $ex$ 和 $ey$ 表示若考虑 $[r + 1, \infty)$ 的边界线，当前范围内的图形是否需要反色；
- $opt$ 表示是加上面积还是去掉多算的面积。

这样，我们便在 $O(N \log{M})$ 的时间完成了这道题。

```cpp
/*Good Game, Well Play.*/
#include <bits/stdc++.h>
using namespace std;

const int N = 100010, M = 1000010;
typedef pair < long long, bool > PII;
int n, m, a[N];

int rt[N * 2], idx;
inline long long pw(long long x) {return x * x;}
struct SGT
{
	int ls, rs; bool data;
	long long sum;
	#define ls(x) tree[x].ls
	#define rs(x) tree[x].rs
	#define data(x) tree[x].data
	#define sum(x) tree[x].sum
} tree[M * 20];
inline void pushup(int now, int l, int r)
{
	data(now) = data(ls(now)) ^ data(rs(now));
	if(data(rs(now))) sum(now) = sum(rs(now)) - sum(ls(now));
	else sum(now) = sum(rs(now)) + sum(ls(now));
}
inline void insert(int &now, int l, int r, int pos)
{
	now = ++idx;
	if(l == r) {data(now) = true; sum(now) = pw(pos * 2); return ;}
	int mid = (l + r) >> 1;
	if(pos <= mid) insert(ls(now), l, mid, pos);
	if(mid < pos) insert(rs(now), mid + 1, r, pos);
	pushup(now, l, r);
}
inline PII combine(int &nx, int ny, int l, int r, bool ex, bool ey, bool opt)
{
//	cerr << "Combine " << nx << " " << ny << " " << l << " " << r << " " << ex << " " << ey << " " << data(nx) << " " << data(ny) << " " << opt << '\n';
	long long res = 0; bool flag = false;
	if(!nx && !ny) {return {0, opt};}
	else if(!nx || !ny)
	{
		if(!nx) swap(nx, ny), swap(ex, ey);
		if(!opt)
		{
			if(ey) res += (ex ? (pw(r * 2) - sum(nx)) : sum(nx));
			if(ey && (ex ^ data(nx))) flag = true;
			else flag = false;
		}
		else
		{
			if(!ey) res -= pw(r * 2);
			else if(!ex) res -= (pw(r * 2) - sum(nx));
			else res -= sum(nx);
			if(!ey || !(ex ^ data(nx))) flag = false;
			else flag = true;
		}
		return {res, flag};
	}
	if(l == r)
	{
		if(!opt)
		{
			if((ex ^ data(nx)) && (ey ^ data(ny))) res += pw(r * 2), flag = true;
			else flag = false;
		}
		else
		{
			if(!(ex ^ data(nx)) || !(ey ^ data(ny))) res -= pw(r * 2), flag = false;
			else flag = true;
		}
		
		data(nx) ^= data(ny); sum(nx) = data(nx) * pw(r * 2);
		return {res, flag};
	}
	int mid = (l + r) >> 1;
	bool lx = (ex ^ data(rs(nx))), ly = (ey ^ data(rs(ny)));
	PII rn = combine(rs(nx), rs(ny), mid + 1, r, ex, ey, opt);
	res += rn.first;
	PII ln = combine(ls(nx), ls(ny), l, mid, lx, ly, rn.second);
	res += ln.first;
	pushup(nx, l, r); return {res, ln.second};
}
inline void output(int now, int l, int r)
{
	if(!now) return ;
	cerr << "output " << now << " " << l << " " << r << " " << data(now) << " " << sum(now) << '\n';
	if(l == r) return ; int mid = (l + r) >> 1;
	output(ls(now), l, mid); output(rs(now), mid + 1, r);
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> a[i], m = max(m, a[i] / 2);
	for(int i = 1; i <= n; ++i) insert(rt[i], 1, m, a[i] / 2);
	for(int i = 1; i < n; ++i)
	{
		int x, y; cin >> x >> y;
		cout << combine(rt[x], rt[y], 1, m, 0, 0, 0).first << '\n';
		rt[n + i] = rt[x];
//		output(rt[n + i], 1, m);
	}
	return 0;
}
/*
2
8 6
1 2
*/
```

---

## 作者：ZhongYuLin (赞：1)

题目中有 $n$ 个正方形，有 $n-1$ 个操作，提示我们按操作建立一颗树。具体地，如果矩形 $A$ 和矩形 $B$ 合成了矩形 $C$，$C$ 向 $A,B$ 连边。显然这是一棵二叉树。

类比于整数的异或和，将一个正方形拆成若干个单位小正方形，我们发现：

1. 这个操作符合结合律和交换律。

2. 整个操作过程中的代价与操作顺序无关。显然白色块对答案无影响，将其去除，然后就只剩下黑色块，而黑色块相互等价，显然以任意顺序操作，答案总是不变的。

于是可以使用线段树合并。

容易想到，将正方形分为四块，只研究一块。一种维护答案的方式是每个叶子节点表示当前坐标的答案，但这样就要区间赋值，复杂度不保证。考虑更改维护方式。第 $i$ 个叶子节点表示矩形 $(0,0),(i,i)$ 的面积。这样，我们的复杂度就有了保证。

考虑区间合并。发现左侧区间可能消去一块面积，可能补上一块面积，而情况取决于左侧区间位于的坐标区间，是黑色还是白色，是被右侧区间覆盖了奇数次，还是被右侧区间覆盖了偶数次，维护这个信息即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+3,V=5e5;
vector<int>e[N];
int a[N],d[N],sz[N];
int ls[N<<2],rs[N<<2],cnt[N<<2],st[N],rt[N];
ll s[N<<2],ans[N];
int n,tot,top;
void add(int u,int v){
    e[u].push_back(v);
    ++d[v];
}
int newNode(){return top?st[top--]:++tot;}
void dlt(int p){st[++top]=p;ls[p]=rs[p]=s[p]=cnt[p]=0;}
void push_up(int p){
    cnt[p]=cnt[ls[p]]+cnt[rs[p]];
    if(cnt[rs[p]]&1)s[p]=s[rs[p]]-s[ls[p]];
    else s[p]=s[rs[p]]+s[ls[p]];
}
void upd(int x,int l,int r,int &p){
    if(!p)p=newNode();
    if(l==r){
        cnt[p]^=1;
        s[p]=1ll*cnt[p]*l*l;
        return;
    }
    int mid=l+r>>1;
    if(x<=mid)upd(x,l,mid,ls[p]);
    else upd(x,mid+1,r,rs[p]);
    push_up(p);
}
int merge(int x,int y,int l,int r){
    if(!x||!y)return x|y;
    if(l==r){
        cnt[x]^=cnt[y];
        s[x]=1ll*cnt[x]*l*l; 
        dlt(y);
        return x;
    }
    int mid=l+r>>1;
    ls[x]=merge(ls[x],ls[y],l,mid);
    rs[x]=merge(rs[x],rs[y],mid+1,r);
    push_up(x);dlt(y);
    return x;
}
void dfs(int x){
    sz[x]=1;
    for(auto y:e[x]){
        dfs(y);
        sz[x]+=sz[y];
    }
}
void solve(int x){
    if(e[x].empty()){
        upd(a[x],1,V,rt[x]);
        return;
    }
    if(e[x].size()!=2)exit(-1);
    int y1=e[x][0],y2=e[x][1];
    if(sz[y1]<sz[y2])swap(y1,y2);
    solve(y1);solve(y2);
    ll k1=s[rt[y1]],k2=s[rt[y2]];
    rt[x]=merge(rt[y1],rt[y2],1,V);
    ll k3=s[rt[x]];
    ans[x]=(k1+k2-k3)>>1;
}
int main(){
    int u,v,w,x,y,z;
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i],a[i]>>=1;
    for(int i=1;i<n;++i){
        cin>>x>>y;
        add(i+n,x);add(i+n,y);
    }
    for(int i=n+1;i<n<<1;++i)
        if(!d[i])dfs(i),solve(i);
    for(int i=n+1;i<n<<1;++i)
        printf("%lld\n",ans[i]*4);
    return 0;
}
```

---

## 作者：zifanwang (赞：0)

考虑线段树合并。令 $a_i\leftarrow\frac{a_i}2$，最后再将答案 $\times 4$，对于每个正方形用动态开点线段树维护一个序列，第 $i$ 个值为 $0/1$ 表示颜色为白/黑。

对于线段树上的每个节点记录区间异或和以及 $0/1$ 的面积。

合并时对两棵线段树记录当前区间右边所有值的异或和，直接合并即可。

时间复杂度 $\mathcal O(n\log V)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 100003
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rept(i,a,b) for(int i=(a);i<(b);++i)
#define drep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
struct node{
	int x,ls,rs;
	ll s[2];
}t[mxn*40];
int n,tot,a[mxn],rt[mxn<<1];
ll ans;
inline ll get(ll x,ll y){
	return y*y-(x-1)*(x-1);
}
void push_up(int p,int l,int r,int mid){
	t[p].x=t[t[p].ls].x^t[t[p].rs].x;
	t[p].s[0]=(t[p].rs?t[t[p].rs].s[0]:get(mid+1,r))+(t[p].ls?t[t[p].ls].s[t[t[p].rs].x]:t[t[p].rs].x==0?get(l,mid):0);
	t[p].s[1]=t[t[p].rs].s[1]+(t[p].ls?t[t[p].ls].s[!t[t[p].rs].x]:t[t[p].rs].x?get(l,mid):0);
}
void upd(int &p,int x,int l,int r){
	if(!p)p=++tot;
	if(l==r){
		t[p].x=1,t[p].s[1]=x*2-1;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)upd(t[p].ls,x,l,mid);
	else upd(t[p].rs,x,mid+1,r);
	push_up(p,l,r,mid);
}
int mrg(int x,int y,int a,int b,int l,int r){
	if(!x&&!y){
		if(a&&b)ans+=get(l,r);
		return 0;
	}
	if(!x){
		if(a)ans+=t[y].s[b^1];
		return y;
	}
	if(!y){
		if(b)ans+=t[x].s[a^1];
		return x;
	}
	if(l==r){
		if((t[x].x^a)&&(t[y].x^b))ans+=l*2-1;
		t[x].x^=t[y].x;
		t[x].s[t[x].x]=l*2-1,t[x].s[t[x].x^1]=0;
		return x;
	}
	int mid=(l+r)>>1;
	t[x].ls=mrg(t[x].ls,t[y].ls,a^t[t[x].rs].x,b^t[t[y].rs].x,l,mid);
	t[x].rs=mrg(t[x].rs,t[y].rs,a,b,mid+1,r);
	push_up(x,l,r,mid);
	return x;
}
signed main(){
	scanf("%d",&n);
	rep(i,1,n){
		scanf("%d",&a[i]),a[i]>>=1;
		upd(rt[i],a[i],1,1e6);
	}
	int x,y;
	rept(tt,1,n){
		scanf("%d%d",&x,&y);
		ans=0;
		rt[n+tt]=mrg(rt[x],rt[y],0,0,1,1e6);
		cout<<ans*4<<'\n';
	}
	return 0;
}
```

---

## 作者：SamHJD (赞：0)

只考虑正方形的右上角四分之一，每一个图案用线段树维护，一段黑色 $(l,r)$ 的面积即为 $r^2-(l-1)^2$。

合并即线段树合并，但需注意如果其中一棵线段树的当前节点没有子节点，则无需 pushdown，在另一棵线段树的对应节点处理标记并返回该节点即可，答案在最深一层节点处计算。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define rep(i,k,n) for(int i=k;i<=n;++i)
#define per(i,n,k) for(int i=n;i>=k;--i)
using namespace std;
template<typename T>
inline void read(T &x){
    x=0;int f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c-'0');
    x*=f;
}
template<typename T,typename ...Args>
inline void read(T &x,Args &...rest){read(x);read(rest...);}
const int N=1e6+10;
int n,rt[N],a[N];
namespace SGT{
    int tot;
    struct node{int ls,rs,tag;ll sum;}t[N*20];
    void lazy(int &p,int l,int r){
        if(!p) p=++tot;
        t[p].tag^=1;
        t[p].sum=1ll*r*r-1ll*(l-1)*(l-1)-t[p].sum;
    }
    void pushdown(int p,int l,int r){
        if(!t[p].tag) return;
        int mid=(l+r)>>1;
        lazy(t[p].ls,l,mid);lazy(t[p].rs,mid+1,r);
        t[p].tag=0;
    }
    void upd(int &p,int l,int r,int nl,int nr){
        if(!p) p=++tot;
        if(nl<=l&&r<=nr) return lazy(p,l,r);
        int mid=(l+r)>>1;
        pushdown(p,l,r);
        if(nl<=mid) upd(t[p].ls,l,mid,nl,nr);
        if(nr>mid) upd(t[p].rs,mid+1,r,nl,nr);
        t[p].sum=t[t[p].ls].sum+t[t[p].rs].sum;
    }
    int merge(int px,int py,int l,int r,ll &ans){
        if(!px||!py) return px+py;
        if(l==r){
            ans+=min(t[px].sum,t[py].sum);
            t[px].sum^=t[py].sum;
            return px;
        }
        int mid=(l+r)>>1;
        if(!t[px].ls&&!t[px].ls){
            ans+=min(t[px].sum,t[py].sum);
            if(t[px].tag) lazy(py,l,r);
            return py;
        }
        if(!t[py].ls&&!t[py].ls){
            ans+=min(t[px].sum,t[py].sum);
            if(t[py].tag) lazy(px,l,r);
            return px;
        }
        pushdown(px,l,r);pushdown(py,l,r);
        t[px].ls=merge(t[px].ls,t[py].ls,l,mid,ans);
        t[px].rs=merge(t[px].rs,t[py].rs,mid+1,r,ans);
        t[px].sum=t[t[px].ls].sum+t[t[px].rs].sum;
        return px;
    }
}
int main(){
    read(n);
    rep(i,1,n){
        read(a[i]);
        SGT::upd(rt[i],1,5e5,1,a[i]/2);
    }
    rep(i,1,n-1){
        int x,y;read(x,y);ll ans=0;
        rt[n+i]=SGT::merge(rt[x],rt[y],1,5e5,ans);
        printf("%lld\n",ans*4ll);
    }
    return 0;
}
```

---

