# [USACO24OPEN] Splitting Haybales P

## 题目描述

Farmer John 想要将干草堆公平地分配给他最喜欢的两头奶牛 Bessie 和 Elsie。他有 $N$（$1\le N\le 2\cdot 10^5$）个降序排序的干草堆，其中第 $i$ 个干草堆有 $a_i$ 单位干草（$2\cdot 10^5\ge a_1\ge a_2\ge \cdots \ge a_N\ge 1$）。

Farmer John 正在考虑将一个连续区间的干草堆 $a_l,\ldots,a_r$ 分配给 Bessie 和 Elsie。他决定按从 $l$ 到 $r$ 的顺序处理干草堆，当处理第 $i$ 个干草堆时他会将其交给当前干草较少的奶牛（如果并列，他会将其交给 Bessie）。

给定 $Q$（$1\le Q\le 2\cdot 10^5$）个询问，每个询问包含三个整数 $l,r,x$（$1\le l\le r\le N$，$|x|\le 10^9$）。对于每个询问，输出如果 Bessie 初始时比 Elsie 多 $x$ 单位干草，在处理干草堆 $l$ 到 $r$ 后 Bessie 将比 Elsie 多多少单位的干草。注意如果 Elsie 最终获得的干草多于 Bessie 则该值为负。

## 说明/提示

### 样例解释 1

对于第 1 个询问，Elsie 初始时比 Bessie 多 2 单位干草。然后，在处理干草堆 1 后，Bessie 将收到 3 单位干草，从而 Bessie 将比 Elsie 多 1 单位干草。

对于第 3 个询问，Elsie 和 Bessie 初始时有相同的干草数量。在处理干草堆 1 后，Bessie 将收到 3 单位干草，从而 Bessie 将比 Elsie 多 3 
单位干草。

对于第 9 个询问，Bessie 初始时比 Elsie 多 1 单位干草，然后在处理第 1 个干草堆后，比 Elsie 少 2 单位干草，处理第 2 个干草堆后，比 Elsie 少 1 单位干草。

### 样例解释 2

对于第 5 个询问，有 5 个干草堆需要处理。Bessie 收到 4 单位干草，然后 Elsie 收到 4 单位干草，然后 Bessie 收到 3 单位干草，然后 Elsie 收到 1 单位干草，然后 Elsie 收到 1 单位干草。

### 测试点性质

- 测试点 $3$：$Q\le 100$。
- 测试点 $4-6$：至多存在 $100$ 个不同的 $a_i$。
- 测试点 $7-22$：没有额外限制。

## 样例 #1

### 输入

```
2
3 1
15
1 1 -2
1 1 -1
1 1 0
1 1 1
1 1 2
1 2 -2
1 2 -1
1 2 0
1 2 1
1 2 2
2 2 -2
2 2 -1
2 2 0
2 2 1
2 2 2```

### 输出

```
1
2
3
-2
-1
0
1
2
-1
0
-1
0
1
0
1```

## 样例 #2

### 输入

```
5
4 4 3 1 1
7
1 1 20
1 2 20
1 5 20
1 1 0
1 5 0
1 4 0
3 5 2```

### 输出

```
16
12
7
4
1
2
1```

# 题解

## 作者：Larunatrecy (赞：17)

~~讲个笑话，这题过了才发现保证了 $a_1\geq a_2\geq \cdots a_n$ 的性质~~。

记 $x$ 为两人干草数量的差，每次相当于：

- 若 $x\leq 0$，$x=x+a_i$。
- 若 $x>0$，$x=x-a_i$。

我们可以先做一步预处理，因为 $x$ 在第一次转变正负前是操作固定的，我们可以先二分出第一个转变正负的位置，那么此时必然有 $|x|\leq 2\times 10^5$，并且之后一直满足。

然后的做法和 P8264 基本相同，我们考虑分块，散块暴力操作，整块维护出每个初始值变成了啥。

我们初始令 $[l,r]=[1,2\times 10^5]$，表示当前还存在的值，那么当遇到一个 $a_i$ 时，我们发现整体平移等价于平移原点，因此我们维护再维护当前的原点 $p$。

平移过后，我们考察一下，若两个点关于原点对称，那么他们最终变成的值也只有正负号的区别，因此我们不妨把他们合并成一个，可以把点的个数少的一边向另一边对应的点连边，并把小的一部分删掉，最后只需要遍历一下这个森林就能知道每个点的答案了。

原点的答案需要特殊处理一下，复杂度约为 $O(qB+\frac{n}{B}(V+q))$，一点不卡常。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
template <typename T>inline void read(T &x)
{
    x=0;char c=getchar();bool f=0;
    for(;c<'0'||c>'9';c=getchar())f|=(c=='-');
    for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
    x=(f?-x:x);
}
int sign(LL x){return x>0;}
int n,m;
const int N = 2e5+7;
int a[N];
LL s[N];
inline LL f(LL x,LL v){return x>0?x-v:x+v;}
int ql[N],qr[N],qx[N];
int bel[N],B;
int fa[N],ans[N],spe[N];
int calc(int x,int l,int r)
{
    for(int i=l;i<=r;i++)x=f(x,a[i]);
    return x;
}
int vis[N],tag=0,tag2=0;
void get(int x)
{
    if(vis[x]==tag||spe[x]==tag2)return;
    vis[x]=tag;
    get(fa[x]);
    if(spe[fa[x]]==tag2)
    {
        ans[x]=ans[fa[x]];
        spe[x]=tag2;
    }
    else
    {
        ans[x]=-ans[fa[x]];
    }
}
int main()
{
    read(n);
    for(int i=1;i<=n;i++)
    {
        read(a[i]);
        s[i]=s[i-1]+a[i];
    }
    read(m);
    for(int i=1;i<=m;i++)
    {
        int L,R;
        LL x;
        read(L);read(R);read(x);
        int l=L,r=R,pos=l-1;
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(sign(x)==sign(f(x,s[mid]-s[L-1])))
            {
                pos=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        x=f(x,s[pos]-s[L-1]);
        ql[i]=pos+1;qr[i]=R;qx[i]=x;
    }
    B=sqrt(n);
    for(int al=1;al<=n;al+=B)
    {
        ++tag;
        ++tag2;
        int ar=min(n,al+B-1);
        int l=1,r=2e5,p=0;
        ans[0]=calc(0,al,ar);vis[0]=tag;spe[0]=tag2;
        for(int i=l;i<=r;i++)fa[i]=i;
        for(int i=al;i<=ar;i++)
        {
            int x=a[i];
            if(p<l)p+=x;
            else if(p>r)p-=x;
            if(p<l||p>r)continue;
            ans[p]=calc(0,i+1,ar);
            vis[p]=tag;spe[p]=tag2;
            if(p-l<r-p)
            {
                for(int i=l;i<p;i++)fa[i]=2*p-i;
                l=p+1;
            }
            else
            {
                for(int i=r;i>p;i--)fa[i]=2*p-i;
                r=p-1;
            }
        }
        for(int i=l;i<=r;i++)ans[i]=i-p,vis[i]=tag;
        for(int i=1;i<=m;i++)
        {
            if(qr[i]<al||ql[i]>ar)continue;
            if(ql[i]<=al&&ar<=qr[i])
            {
                if(qx[i]==0)qx[i]=ans[0];
                else
                {
                    int v=abs(qx[i]);
                    get(v);
                    if(spe[v]==tag2)qx[i]=ans[v];
                    else
                    {
                        if(qx[i]<0)qx[i]=-ans[v];
                        else qx[i]=ans[v];
                    }
                }
                continue;
            }
            for(int j=max(al,ql[i]);j<=min(ar,qr[i]);j++)qx[i]=f(qx[i],a[j]);
        }
    }
    for(int i=1;i<=m;i++)printf("%d\n",qx[i]);
    return 0;
}
```

---

## 作者：EnofTaiPeople (赞：16)

如果你通关铂金组了，那么你就没有**贝提拔**的机会了。

这道题可能用条件做比不用更难，反正我没有想到怎么使用这个条件。

本题相当于正数减去 $a_i$，非正数加上 $a_i$，求经过区间 $[l,r]$ 的操作后的值。

考虑整体使用平衡树维护，在 $l$ 处加入，$r$ 处查询，每次操作时分裂、修改、合并即可。

这里平衡树合并的复杂度似乎可以通过 $\log|a_i-a_{i+1}|$ 的势能分析出是 $O(n\log n\log V)$ 的，可能不难证明。

注意使用 Treap 维护时对于相等的值需要设置第二关键字进行比较，否则等值过多会退化。

时间为**均摊期望** $O(n\log n\log V)$，空间 $O(n)$：
```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=(1<<20)+100;
mt19937_64 rg(41719);
using ll=long long;
#define ls t[x][0]
#define rs t[x][1]
int n,m,a[N],b[N],rp[N];
vector<int>ad[N>>2],dl[N>>2];
int t[N][2],f[N],cnt,rt,ans[N];
ll v[N],tg[N],K;
void atg(int x,ll d){v[x]+=d,tg[x]+=d;}
void pd(int x){
    if(tg[x]){
        if(ls)atg(ls,tg[x]);
        if(rs)atg(rs,tg[x]);tg[x]=0;
    }
}
void pp(int x){f[ls]=f[rs]=x;}
void spt(int x,ll k,int &L,int &R){
    if(!x){L=R=0;return;}pd(x);
    if(v[x]<k)L=x,spt(rs,k,rs,R);
    else R=x,spt(ls,k,L,ls);pp(x);
}
int mg(int x,int y){
    if(!x||!y)return x|y;
    if(rp[x]<rp[y])swap(x,y);
    int L,R;spt(y,v[x],L,R),pd(x);
    ls=mg(ls,L),rs=mg(rs,R),pp(x);
    return x;
}
void ppd(int x){if(f[x])ppd(f[x]);pd(x);}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int i,j,k,l,r,x,y,z;
    for(x=1,cin>>n;x<=n;++x)cin>>a[x];
    for(i=1,cin>>m;i<=m;++i){
        cin>>l>>r>>b[i];rp[i]=i;
        ad[l].push_back(i);
        dl[r].push_back(i);
    }
    K=m+2,shuffle(rp+1,rp+m+1,rg);
    for(i=1;i<=n;++i){
        for(int p:ad[i]){
            v[p]=K*b[p]+p;
            rt=mg(rt,p);
        }
        spt(rt,K,l,r);
        atg(l,K*a[i]),atg(r,-K*a[i]);
        rt=mg(l,r),f[rt]=0;
        for(int p:dl[i])
            ppd(p),ans[p]=(v[p]-p)/K;
    }
    for(x=1;x<=m;++x)printf("%d\n",ans[x]);
    return 0;
}
```

---

## 作者：ty_mxzhn (赞：7)

# 插入标记回收算法

本算法在 lxl 讲课时提出。~~然后立马就被放到了数据结构专场的签到题。~~

解决的问题是：

$q$ 次询问 $x$ 依次经过 $r-l+1$ 种操作的结果。

第 $i$ 种操作是 $x\leftarrow F_i(x)$ 这样。可以离线。

算法流程如下：

1. 插入数据。在 $l$ 时间开始前把 $x$ 加入集合 $S$ 中。
2. 标记。在 $i$ 时间执行 $S\leftarrow F_i(S)$。
3. 回收数据。在 $r+1$ 时间开始前把 $l$ 丢进去的数据从 $S$ 中回收。

难得 lxl 讲这么简单的算法。

## 例题 $1$

PKUSC 的题（澡堂）：$F_i(x)=x+[x\in[l_i,r_i]]$。

显然 $S$ 中节点保持单调顺序。直接用线段树二分定位线段树区间加即可。时间复杂度 $O(n\log n)$。

# 平衡树合并技巧

平衡树合并是在没有一些奇怪操作的 FHQ-Treap 上的合并两颗**不需要满足任何条件**的 FHQ-Treap 的方法。

## 一个暴力

假设我们要从 $y$ 合并到 $x$，启发式后直接一个一个合并。

然而这样复杂度是错的，因为我们可以不断分裂合并。

## 一个暴力？

直接按照 $x$ 的键值分裂 $y$。然后把 $y$ 的两边放到 $x$ 的两边递归合并。

需要注意的是要求 $P_x>P_y$ 也就是按照优先级决定谁合并谁。其实理论上按照大小合并会更优但是其实差不多。

## 复杂度证明

假设 $n,q$ 同阶。上述“暴力”的时间复杂度为 $O(n\log n\log V)$。

证明考虑设计势能函数 $\epsilon(x)$ 表示 $x$ 内部相邻两点的值域差对数的和。

设值域连续段有 $c$ 个，这里的连续段指的是合并 $A,B$ 两颗平衡时后新树的值总是成 $A..B..A..B..A..B..A..B..$ 这样。则 $c=8$。

合并时有值域连续段内总有 $O(c)$ 个节点的势能减少 $1$。而上述“暴力”的复杂度最高只有 $O(c\log n)$。

显然分裂不增加势能。

## 友情提示

![](https://cdn.luogu.com.cn/upload/image_hosting/pwhyistc.png)

## 例题 $2$

例题：[Ynoi TEST_100](https://www.luogu.com.cn/problem/P8264)。

用刚才两个算法。则相当于对 $a_i$ 的大小关系分讨后使用平衡树合并在一起。

并不是这样的，因为强制在线限制了第一个算法。

考虑分块。因为值域很小所以我们可以每一段内暴力平衡树合并跑出 $1\sim V$ 的答案。

查询时散块暴力，跳整块直接用刚才平衡树合并时跑出来的结果即可。

$n,q,V$ 同阶。时间复杂度 $O(n\sqrt{n}+n\log^2n)$。

## 例题 $3$

例题：[Splitting Haybals P](https://www.luogu.com.cn/problem/P10284)。

用刚才提到的两个算法。插入标记回收以后，按照 $0$ 分裂以后分别打加法标记并合并。

$n,q$ 同阶。时间复杂度 $O(n\log n\log V)$。

---

## 作者：Genius_Star (赞：3)

[**双倍经验。**](https://www.luogu.com.cn/problem/AT_arc149_d)

~~怎么 USACO 都开始出原题了。。。~~

### 思路：

插入标记回收算法板子。

考虑扫描线，在 $l$ 处将 $x$ 插入进去，每扫过一个对全局进行一次变换，最后再 $r$ 处将 $x$ 取出。

考虑一次全局变换是什么：

- 若 $x > 0$，那么 $x \gets x - a_i$。

- 否则若 $x \le 0$，那么 $x \gets x + a_i$。

考虑使用平衡树维护上述过程，首先按照 $\le 0$ 分裂为 $x, y$，将 $x$ 打上 $+a_i$ 的懒标记，$y$ 打上 $-a_i$ 的懒标记。

但是此时两平衡树值域有交，使用平衡树有交合并算法即可做到 $O(N \log^2 N)$。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, m, l, r, x, rt, cnt;
int id[N], a[N], ans[N];
vector<int> V[N];
vector<pair<int, int>> Q[N];
namespace DSU{
	int fa[N];
	inline void init(int n){
		for(int i = 1; i <= n; ++i)
		  fa[i] = i;
	}
	inline int Find(int x){
		if(x != fa[x])
		  return fa[x] = Find(fa[x]);
		return fa[x];
	}
	inline void merge(int x, int y){
		x = Find(x), y = Find(y);
		if(x == y)
		  return ;
		fa[x] = y;
	}
};
mt19937 R(time(0));
struct Node{
	int fa;
	int lson, rson;
	ll data, add;
	bool tag;
	ll key;
}X[N];
inline int newnode(ll v){
	++cnt;
	X[cnt].lson = X[cnt].rson = X[cnt].add = X[cnt].tag = 0;
	X[cnt].key = R();
	X[cnt].data = v;
	return cnt;
}
inline void pushup(int k){
	X[X[k].lson].fa = X[X[k].rson].fa = k;
}
inline void add(int k, ll v){
	if(!k)
	  return ;
	X[k].data += v;
	X[k].add += v;
}
inline void rev(int k){
	if(!k)
	  return ;
	X[k].data = -X[k].data;
	X[k].add = -X[k].add;
	X[k].tag ^= 1;
}
inline void push_down(int k){
	if(X[k].tag){
		swap(X[k].lson, X[k].rson);
		rev(X[k].lson);
		rev(X[k].rson);
		X[k].tag = 0;
	}
	if(X[k].add){
		add(X[k].lson, X[k].add);
		add(X[k].rson, X[k].add);
		X[k].add = 0;
	}
}
inline void split(int k, ll v, int &x, int &y){
	if(!k){
		x = y = 0;
		return ;
	}
	push_down(k);
	if(X[k].data <= v){
		x = k;
		split(X[x].rson, v, X[x].rson, y);
		pushup(x);
	}
	else{
		y = k;
		split(X[y].lson, v, x, X[y].lson);
		pushup(y);
	}
}
inline int merge(int x, int y){
	if(!x || !y)
	  return x + y;
	if(X[x].key < X[y].key){
		push_down(x);
		X[x].rson = merge(X[x].rson, y);
		pushup(x);
		return x;
	}
	else{
		push_down(y);
		X[y].lson = merge(x, X[y].lson);
		pushup(y);
		return y;
	}
}
inline void dfsfa(int k, int v){
	if(!k)
	  return ;
	DSU::merge(k, v);
	dfsfa(X[k].lson, v);
	dfsfa(X[k].rson, v);
}
inline int Merge(int x, int y){
	if(!x || !y)
	  return x + y;
	if(X[x].key >= X[y].key)
	  swap(x, y);
	push_down(x);
	int l, r, p;
	split(y, X[x].data, l, r);
	split(l, X[x].data - 1, l, p);
	dfsfa(p, x);
	X[x].lson = Merge(X[x].lson, l);
	X[x].rson = Merge(X[x].rson, r);
	pushup(x);
	return x;
}
inline void insert(ll v){
	int x, y;
	split(rt, v, x, y);
	rt = merge(merge(x, newnode(v)), y);
}
inline ll getval(int k){
	if(X[k].fa)
	  getval(X[k].fa);
	push_down(k);
	return X[k].data;
}
bool End;
int main(){
//	open("A.in", "A.out");
	n = read();
	for(int i = 1; i <= n; ++i)
	  a[i] = read();
	m = read();
	DSU::init(m);
	for(int i = 1; i <= m; ++i){
		l = read(), r = read(), x = read();
		Q[l].push_back({x, i});
		V[r].push_back(i);
	}
	for(int i = 1; i <= n; ++i){
		for(auto t : Q[i]){
			insert(t.fi);
			id[t.se] = cnt;
		}
		int x, y;
		split(rt, 0, x, y);
		add(x, a[i]), add(y, -a[i]);
		rt = Merge(x, y);
		for(auto v : V[i])
		  ans[v] = getval(DSU::Find(id[v]));
	}
	for(int i = 1; i <= m; ++i){
		write(ans[i]);
		putchar('\n');
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：daiyulong20120222 (赞：3)

设 $A$ 是 $a_1$ 的上界，$T=N+Q+A$。预期的时间复杂度为 $O(T\log T)$。下面描述了实现这种复杂性的几种方法。

## Subtask 1 

> $Q\le100$

设 $x$ 为任意时刻 Bessie 的草包数减去 Elsie 的草包数。当给出第 $i$ 捆时，当 $x≤0$ 时 $x$ 增加 $a_i$，当 $x>0$ 时 $x$ 减少 $a_i$。在每个查询 $O(N)$ 次中模拟这种情况，得到一个 $O (NQ)$的解决方案。

## Subtask 2

> $a_i\le100$

我们可以在 $O(a_i)$ 时间内处理每个查询，而不是 $O(N)$ 时间。更具体地说，对于相等的 $a_i$ 范围，我们可以在 $O(1)$ 时间内处理它对 $x$ 的影响；首先，$x$ 的绝对值会持续减少，直到它的绝对值低于 $a_i$，然后它的符号会交替。

## 完整解决方案

> 二分和倍增

让我们更仔细地看看 $x$ 在查询期间是如何变化的。

让我们考虑当 $x>0$ 时会发生什么。对于最初的几捆干草，$x$ 可能非常大，你会不断减小它，直到 $x≤0$。设 $i$ 为使 $x≤0$ 的草堆的指标。

在给出第 $i+1$ 个和的草堆之后，$x$ 在正数和非正数之间交替一段时间是有意义的。设 $j$ 为草堆的索引，之后 $x$ 打破了这个模式。

假设 $j-i$ 是偶数。然后注意下面的事件：

- 在第 $i$ 个草堆之后，$x$ 在 $(-a_i,0]$ 范围内（因为在此之前 $x>0$）。
- 在第 $i+1$ 个草堆之后，$x$ 在 $(0,a_{i+1}]$ 范围内。
- 在第 $i+2$ 个草堆之后，$x$ 在 $(-a_{i+2},0]$ 范围内。
- 在第 $i+3$ 个草堆之后，$x$ 在 $(0,a_{i+3}]$ 范围内。
- $\cdots\cdots$
- 在第 $j-1$ 个草堆之后，$x$ 在 $(0,a_{j-1}]$ 范围内。

最后，在第 $j$ 个干草包之后，$x$ 在 $(0,a_{j-1}-a_{j}]$ 的范围内。当 $j-i$ 是奇数；我们可以看到，在这种情况下，$x$ 在 $(-(a_{j-1}-a_{j},0]$ 的范围内。

对称地，当 $x$ 初始 $≤0$ 时，上述也成立。

综上所述，在以上述方式给出草堆后，我们要么给出从 $l$ 到 $r$ 的所有草堆，要么在给出第 $k$ 个草堆 $(k≥l+2)$ 之前停止，新 $x$ 满足 $|x|≤ a_{k-2}-a_{k-1}$。

从现在开始，我们将上述操作称为从 $(l,x)$ **跳转**。我们可以用二分法找到 $i$。利用 $a$ 不递增的事实，我们也可以用两个二分奇数 $j-i$ 和偶数 $j-i$。这样，计算跳转需要 $O(\log N)$ 的时间。

现在我们来解题。我们首先计算，对于所有 $i$ 从 $3$ 到 $N$ 且 $|x|≤a_{i-2}-a_{i-1}$，如果你从 $(i,x)$ 开始，你会跳到这里。我们可以在这些跳台上建一个二元升降台。

然后，为了回答查询，我们执行以下操作。从 $(1,x)$ 跳到 $(i,y)$ 一次。使用倍增从 $(i,y)$ 开始重复跳跃，直到下一次跳跃超过 $r$。我们称你到达的状态为 $(j,z)$。从 $(j,z)$ 跳起，当你发出第 $r$ 个草包时停止。

为什么上面的速度快？让我们首先计算需要从多少个状态开始计算跳跃。这个等于

$$ 
\begin{aligned}
  \sum_{i=3}^{n}(2\times(a_{i-2}-a_{i-1})+1) &= \Bigg(2\sum^N_{i=3}(a_{i-2}-a_{i-1})\Bigg)+O(N) \\
                 &= 2\times (a_1-a_{N-1})+O(N)\\
                 &= O(N+A)
\end{aligned}
$$

因此，计算跳跃需要 $O((N+A)\log N)$ 时间，构建倍增需要 $O((N+A)\log N)$ 时间（或者使用[本博客](https://codeforces.com/blog/entry/74847)需要 $O(N+A)$ 时间）。回答每个查询包括执行一次二分、使用倍增和执行另一次二分，每次查询总共花费 $O(\log N)$ 时间。因此，整个解的运行时间为 $O((N+A+Q)\log N)$，得到满分。

### [code](https://www.luogu.com.cn/paste/twn5vral)

---

## 作者：Graphcity (赞：3)

我们按照这种方式考虑问题。对于一个询问，我们在时刻 $l$ 放一个棋子在位置 $x$，然后让它不断进行操作，在时刻 $r$ 后将其取出。使用并查集来合并重合的棋子。取出时棋子的位置即为答案。

首先我们可以通过二分的方式快速找到 $x$ 在什么时候落在了 $(-a_i,a_i]$ 这段区间。考虑用平衡树快速模拟这段区间内棋子的变化情况。对于这段区间中的每一个位置，在平衡树上用一个结点维护这个位置上棋子对应的并查集。

假设当前平衡树模拟的区间为 $[L,R]$。模拟的过程分为两步。第一步，把正数和其它数字拆开，变成 $(L,0]$ 和 $(0,R]$。进行变换后，两个区间分别被平移到了 $(L+a_{i+1},a_{i+1}]$ 和 $(-a_{i+1},R-a_{i+1}]$。不难发现两个区间有重合。我们暴力将重合的位置对应的并查集合并。注意到一次重合必然会删掉一个结点，所以总的合并次数是 $O(n)$ 的。

第二步，就是把这两个区间去重后拼起来。这些都是平衡树的基本操作。总时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e6;

int n,m,rt,a[Maxn+5],fa[Maxn+5],chk[Maxn+5];
int ans[Maxn+5],R[Maxn+5]; ll sum[Maxn+5];
struct Node{int l,r,val,siz,fa;} t[Maxn+5];
mt19937 rnd(time(0));
#define ls(x) t[x].l
#define rs(x) t[x].r

vector<pair<int,int>> v[Maxn+5];
inline int Find(int x) {return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void push_up(int p)
{
    if(ls(p)) t[ls(p)].fa=p; if(rs(p)) t[rs(p)].fa=p;
    t[p].siz=t[ls(p)].siz+t[rs(p)].siz+1; t[p].fa=0;
}
inline void Split(int p,int k,int &a,int &b)
{
    if(!p) {a=b=0; return;} int w=t[ls(p)].siz+1;
    if(w<=k) a=p,Split(rs(p),k-w,rs(p),b);
    else b=p,Split(ls(p),k,a,ls(p));
    push_up(p);
}
inline int Merge(int x,int y)
{
    if(!x || !y) return x+y;
    if(t[x].val<=t[y].val) {rs(x)=Merge(rs(x),y),push_up(x); return x;}
    else {ls(y)=Merge(x,ls(y)),push_up(y); return y;}
}
inline void Shrink(int &l,int r,int &k)
{
    if(k<=-a[l])
    {
        int p=upper_bound(sum+l,sum+r+1,sum[l-1]-k)-sum;
        if(p>r) k+=(sum[r]-sum[l-1]),l=r+1;
        else k+=(sum[p-1]-sum[l-1]),l=p;
    }
    if(k>a[l])
    {
        int p=lower_bound(sum+l,sum+r+1,sum[l-1]+k)-sum;
        if(p>r) k-=(sum[r]-sum[l-1]),l=r+1;
        else k-=(sum[p-1]-sum[l-1]),l=p;
    }
}
inline void DSU(int x,int y) {x=Find(x),y=Find(y); if(x==y) return; fa[y]=x;}
inline int Get(int p,int x)
{
    while(1)
    {
        if(t[ls(p)].siz>=x) p=ls(p);
        else if(x==t[ls(p)].siz+1) return p;
        else x-=(t[ls(p)].siz+1),p=rs(p);
    }
}
inline int Rank(int x)
{
    int p=t[ls(x)].siz;
    for(int f=t[x].fa;f;x=f,f=t[f].fa)
        if(x==rs(f)) p+=t[ls(f)].siz+1;
    return p+1;
}
inline int Cut(int &k,int l,int r)
{
    int a,b,c; Split(k,r,a,c),Split(a,l-1,a,b);
    k=Merge(a,c); return b;
}

int main()
{
    cin>>n; For(i,1,n) cin>>a[i],sum[i]=sum[i-1]+a[i];
    For(i,1,a[1]*2) {t[i].siz=1,t[i].val=rnd(),rt=Merge(rt,i);}
    cin>>m; For(i,1,a[1]*2+m) fa[i]=i;
    For(i,1,m)
    {
        int l,r,k; cin>>l>>r>>k; R[i]=r,Shrink(l,r,k);
        if(l>r) ans[i]=k,chk[i]=1;
        else
        {
            k=(k<=0?k+a[l]:k-a[l]);
            v[l].emplace_back(k,a[1]*2+i),v[r].emplace_back(0,-i);
        }
    }
    int L=-a[1],R=a[1];
    For(i,1,n)
    {
        for(auto [k,id]:v[i]) if(id>=0) {int p=Get(rt,k-L); DSU(p,id);}
        for(auto [k,id]:v[i]) if(id<0)
        {
            id=-id; if(chk[id]) continue; chk[id]=1;
            ans[id]=Rank(Find(a[1]*2+id))+L;
        }
        if(i==n) break;
        int p=Cut(rt,1,-L),q=rt;
        int l1=L+a[i+1],r1=a[i+1];
        int l2=-a[i+1],r2=R-a[i+1];
        int lx=max(l1,l2),rx=min(r1,r2);
        if(lx<rx)
        {
            int len=min(r1,r2)-max(l1,l2);
            int x=Cut(p,lx-l1+1,rx-l1),y=Cut(q,lx-l2+1,rx-l2);
            For(i,1,len) {int p1=Get(x,i),p2=Get(y,i); DSU(p1,p2);}
            if(l1<=l2) p=Merge(p,x); else p=Merge(x,p);
        }
        if(l1<=l2) rt=Merge(p,q); else rt=Merge(q,p);
        L=min(l1,l2),R=max(r1,r2);
    }
    For(i,1,m) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：oyzr (赞：1)

### 做法一：分块 + Treap（在线）

#### 1. 思路

注意到 $a_i \le 2 \times 10^5$，这个值域是比较小的，可以进行分块预处理（设块长为 $B$）

那么对于询问，我们先二分跳到第一个 $x \in [-2 \times 10^5,2 \times 10^5]$ 的情况，再走一下非整块和整块部分，复杂度为 $O(B + \frac{B}{n})$

下面的问题是我们如何在一个较小的复杂度内预处理每个块

对于一个操作，我们发现，它会使 $(L,0] \to (L+a_i,a_i]$，$(0,R) \to (-a_i,R-a_i)$，区间会一点点缩小，而且因为 $a_i$ 单调递减，区间一定是连续的，那我们考虑如何维护它

可以使用 treap，这样可以记录每个点的 $id$ 和 $val$ 信息

![两种情况的分类](https://cdn.luogu.com.cn/upload/image_hosting/rfax1vpx.png)

我们每次按 $val$ 在 0 点把区间拆分成两部分，然后给 $rt1$ 打上 $+a_i$ 的 tag，给 $rt2$ 打上 $-a_i$ 的 tag

对于重合区间，我们可以把 $rt3$ 的每个结点遍历一遍，记录一下 $val$ 对应的 $id$，然后把 $rt4$ 的每个结点的 $id$ 使用并查集合并到和它 $val$ 相同的 $rt3$ 的节点上，重合区间合并一次后就被删掉了，这部分对于每块来说总复杂度 $O(Vk)$（$k$ 是并查集的复杂度，不知道咋证，应该比较小）

更具体地，对于重合区间的范围，我们有两种情况：（我一开始把区间边界当成 inf 处理了，没考虑分类，挂了好久）

1. $-a_i + 1 \le L + a_i$
    - 重合区间：$[L + a_i, R - a_i]$​
    - 总区间：$[-a_i+1,a_i]$
2. $-a_i + 1 > L + a_i$​
    - 重合区间：$[-a_i+1,a_i]$
    - 总区间：$[L+a_i,R-a_i]$

处理完重复区间后，我们再一次合并子树即可

那么我们就完成了对于每块的处理，复杂度大概是 $O(\frac{n}{b}(V+\sqrt n\log V + V))$​（注意 treap 的建树用一个递归可以做到 $O(V)$）

总结：这个做法的复杂度比较炸裂，我卡着 2.00s 过的，图一乐就好，空间复杂度也到了 $O(\frac{n}{b} V)$​

#### 2. 代码

```c++
#include <bits/stdc++.h>
using namespace std;
const int Maxn = 2e5 + 5, Maxcnt = 50;
const int MaxV = 2e5;
class disjoint_set{
private:
    const static int Size = 2 * Maxn;
    int fa[Size];
public:
    /**
     * @brief 初始化并查集
     */
    void init(){
        for (int i = 0; i < Size; i++)
            fa[i] = i;
    }
    /**
     * @brief 获取 x 节点所在连通块的代表员，并进行路径压缩
     * @param x 要获取代表员的节点
     * @return int x 节点所在连通块的代表员
     */
    int getfa(int x){
        if (fa[x] == x) return x;
        return fa[x] = getfa(fa[x]);
    }
    /**
     * @brief 将第二个连通块合并到第一个连通块
     * @param x 第一个连通块的任一成员
     * @param y 第二个连通块的任一成员
     */
    void merge(int x, int y){
        int fx = getfa(x);
        int fy = getfa(y);
        fa[fy] = fx;
    }
};
disjoint_set DSU;
int mp[2 * Maxn];
class treap{
private:
    #define lson (t[id].ch[0])
    #define rson (t[id].ch[1])
    const static int Size = 2 * Maxn;
    struct Node{
        int val, rnd;
        int size;
        int ch[2];
        int id, lazy;
        Node(){
            size = 0;
            rnd = rand();
            id = val = 0;
            ch[0] = ch[1] = 0;
            lazy = 0;
        }
        Node(int a, int b = 0){
            size = 1;
            rnd = rand();
            id = val = a;
            ch[0] = ch[1] = 0;
            lazy = b;
        }
        bool haveLazy(){
            return lazy != 0;
        }
        void resetLazy(){
            lazy = 0;
        }
        void operator *= (const Node T){
            val += T.lazy;
            lazy += T.lazy;
        }
    };
    int newNode(int val){
        ++tot;
        t[tot] = Node(val);
        return tot;
    }
    void pushdown(int id){
        if (t[id].haveLazy()){
            if (lson)
                t[lson] *= t[id];
            if (rson)
                t[rson] *= t[id];
            t[id].resetLazy();
        }
    }
    void update(int id){
        t[id].size = 1 + t[lson].size + t[rson].size;
    }
public:
    Node t[Size];
    int tot = 0;
    void split(int id, int val, int &x, int &y){
        if (!id)
            return (void)(x = y = 0);
        pushdown(id);
        if (t[id].val <= val){
            x = id;
            split(rson, val, rson, y);
        }
        else{
            y = id;
            split(lson, val, x, lson);
        }
        update(id);
    }
    int merge(int x, int y){
        if (!x || !y)
            return x + y;
        if (t[x].rnd < t[y].rnd){
            pushdown(x);
            t[x].ch[1] = merge(t[x].ch[1], y);
            update(x);
            return x;
        }
        else{
            pushdown(y);
            t[y].ch[0] = merge(x, t[y].ch[0]);
            update(y);
            return y;
        }
    }
    void clear(){
        // for (int i = 1; i <= tot; i++)
        //     t[i] = Node();
        tot = 0;
    }
    void build(int &id, int l, int r){
        if (l > r)
            return;
        int mid = (l + r) >> 1;
        id = newNode(mid);
        build(lson, l, mid - 1);
        build(rson, mid + 1, r);
        update(id);
    }
    void add(int id){
        if (!id)
            return;
        mp[t[id].val + MaxV] = t[id].id;
        add(lson);
        add(rson);
    }
    void upd(int id){
        if (!id)
            return;
        DSU.merge(mp[t[id].val + MaxV] + MaxV, t[id].id + MaxV);
        upd(lson);
        upd(rson);
    }
    void pushdownTree(int id){
        if (!id)
            return;
        pushdown(id);
        pushdownTree(lson);
        pushdownTree(rson);
    }
    void addLazy(int rt, int lazy){
        if (rt == 0)
            return;
        t[rt] *= Node(0, lazy);
    }
    /**
     * @brief 切下来 l <= val <= r 的结点，保证 l或r 是rt的一端
     * @param rt 
     * @param l 
     * @param r 
     * @return int 切下来的结点对应的treap的根
     */
    int cut(int &rt, int l, int r){
        int x = 0, y = 0;
        split(rt, r, rt, x);
        split(rt, l - 1, rt, y);
        rt = merge(rt, x);
        return y;
    }
    // int kth(int rt, int k){
    //     while(rt){
    //         pushdown(rt);
    //         int lsize = t[t[rt].ch[0]].size;
    //         if (k <= lsize)
    //             rt = t[rt].ch[0];
    //         else if (k > lsize + 1)
    //             rt = t[rt].ch[1], k = k - lsize - 1;
    //         else
    //             return t[rt].val;
    //     }
    //     return -2147483648;
    // }
};
treap Treap;
#define block(x) ((x - 1) / blockSize + 1)
#define blockLeft(x) ((x - 1) * blockSize + 1)
#define blockRight(x) min(x * blockSize, n)
int a[Maxn];
long long sum[Maxn];
int val[Maxcnt][2 * Maxn];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // freopen("C:\\Users\\oyang\\Downloads\\prob2_platinum_open24\\8.in", "r", stdin);
    // freopen("C:\\Users\\oyang\\Downloads\\prob2_platinum_open24\\8.txt", "w", stdout);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + a[i];
    int blockSize = pow(n, 0.71), blockCnt = (n + blockSize - 1) / blockSize;
    for (int b = 1; b <= blockCnt; b++){
        DSU.init();
        int rt = 1;
        Treap.build(rt, -MaxV, MaxV);
        int L = -MaxV, R = MaxV;
        for (int i = blockLeft(b); i <= blockRight(b); i++){
            int rt1 = 0, rt2 = 0, rt3 = 0, rt4 = 0;
            Treap.split(rt, 0, rt1, rt2);
            Treap.addLazy(rt1, a[i]);
            Treap.addLazy(rt2, -a[i]);
            int l = max(L + a[i], -a[i] + 1), r = min(R - a[i], a[i]);
            // cout << "-------------" << endl;
            // cout << i << ' ' << Treap.kth(rt1, 1) << ' ' << Treap.kth(rt1, Treap.t[rt1].size)<< endl;
            // cout << i << ' ' << Treap.kth(rt2, 1) << ' ' << Treap.kth(rt2, Treap.t[rt2].size) << endl;
            // cout << l << ' ' << r << endl;
            rt3 = Treap.cut(rt1, l, r);
            rt4 = Treap.cut(rt2, l, r);
            // if (Treap.t[rt3].size != Treap.t[rt4].size){
            //     cout << endl;
            //     cout << endl;
            //     cout << "!!!!!!!!!!!!!!!!!!!!!!" << endl;
            //     cout << a[i] << endl;
            //     cout << l << ' ' << r << endl;
            //     cout << Treap.kth(rt3, 1) << ' ' << Treap.kth(rt4, 1) << endl;
            //     cout << Treap.t[rt3].size << ' ' << Treap.t[rt4].size << endl;
            // }
            // assert(Treap.t[rt3].size == Treap.t[rt4].size);
            Treap.pushdownTree(rt3);
            Treap.add(rt3);
            Treap.pushdownTree(rt4);
            Treap.upd(rt4);
            if (L + a[i] < -a[i] + 1)
                rt = Treap.merge(Treap.merge(rt1, rt3), rt2);
            else
                rt = Treap.merge(Treap.merge(rt2, rt3), rt1);
            L = min(L + a[i], -a[i] + 1), R = max(R - a[i], a[i]);
            // cout << L << ' ' << R << endl;
        }
        Treap.pushdownTree(rt);
        for (int i = 1; i <= Treap.tot; i++)
            val[b][Treap.t[i].id + MaxV] = Treap.t[i].val;
        for (int i = -MaxV; i <= MaxV; i++)
            val[b][i + MaxV] = val[b][DSU.getfa(i + MaxV)];
        // if (DSU.getfa(i + MaxV) != i + MaxV){
        //     cout << "?" << endl;
        //     cout << b << endl;
        //     cout << val[b][i + MaxV] << endl;
        //     cout << DSU.getfa(i + MaxV) << ' ' << i + MaxV << endl;
        // }
        // assert(DSU.getfa(i + MaxV) == i + MaxV);
        Treap.clear();
    }
    int q;
    cin >> q;
    while (q--){
        int l, r;
        long long x;
        cin >> l >> r >> x;
        int L = l - 1, R = r, ans = r;
        if (x >= 0){
            while (L <= R){
                int mid = (L + R) >> 1;
                if (x - (sum[mid] - sum[l - 1]) <= MaxV)
                    R = mid - 1, ans = mid;
                else
                    L = mid + 1;
            }
            x = x - (sum[ans] - sum[l - 1]);
        }else{
            while (L <= R){
                int mid = (L + R) >> 1;
                if (x + (sum[mid] - sum[l - 1]) >= -MaxV)
                    R = mid - 1, ans = mid;
                else
                    L = mid + 1;
            }
            x = x + (sum[ans] - sum[l - 1]);
        }
        l = ans + 1;
        if (l > r){   
            cout << x << endl;
            continue;
        }
        if (block(l) == block(r)){
            for (int i = l; i <= r; i++){
                if (x <= 0)
                    x += a[i];
                else
                    x -= a[i];
            }
        }else{
            for (int i = l; i <= blockRight(block(l)); i++){
                if (x <= 0)
                    x += a[i];
                else
                    x -= a[i];
            }
            for (int i = block(l) + 1; i <= block(r) - 1; i++){
                x = val[i][x + MaxV];
            }
            for (int i = blockLeft(block(r)); i <= r; i++){
                if (x <= 0)
                    x += a[i];
                else
                    x -= a[i];
            }
        }
        cout << x << endl;
    }
    return 0;
}
```



### 做法二：Treap（离线）

#### 1. 思路

我们还是开一个 treap 维护，维护情况几乎和上面的相同，但是我们发现每个块维护一个 treap 太麻烦了，我们把整个询问离线下来跑一次 treap 就够了，treap 的维护方法和上面一样

对于每个新到的点，由于当前区间是连续的，treap 里第 $val - L + 1$ 个点的值就是 $val$，我们把 $id$ 合并到这个点的 $id$ 上即可

对于每个查询，我们的区间是连续的，treap 里 $id$ 对应结点的 $rank + L - 1$，就是我们的 $ans$

- 这里需要顺序建 treap，以获得 $id$ 和 treap 结点编号的对应关系
- 给定一个结点求 $rank$ 我们可以一直向它的 $fa$ 跳，如果它是 $fa$ 的右子，那么 $fa$ 的左子和 $fa$ 都比它小，累加即可

总复杂度  $O((n + q) \log V)$

注意二分应该跳到最小的 $mid$ 满足 $x + a_l + a_{l+1} + \cdots + a_{mid} \in [-a_{mid}+1, a_{mid}]$

#### 2. 代码

```c++
#include <bits/stdc++.h>
using namespace std;
const int Maxn = 2e5 + 5;
const int MaxV = 2e5;
class disjoint_set{
private:
    const static int Size = 3 * Maxn;
    int fa[Size];
public:
    /**
     * @brief 初始化并查集
     */
    void init(){
        for (int i = 0; i < Size; i++)
            fa[i] = i;
    }
    /**
     * @brief 获取 x 节点所在连通块的代表员，并进行路径压缩
     * @param x 要获取代表员的节点
     * @return int x 节点所在连通块的代表员
     */
    int getfa(int x){
        if (fa[x] == x) return x;
        return fa[x] = getfa(fa[x]);
    }
    /**
     * @brief 将第二个连通块合并到第一个连通块
     * @param x 第一个连通块的任一成员
     * @param y 第二个连通块的任一成员
     */
    void merge(int x, int y){
        int fx = getfa(x);
        int fy = getfa(y);
        fa[fy] = fx;
    }
};
disjoint_set DSU;
int mp[2 * Maxn];
class treap{
private:
    #define lson (t[id].ch[0])
    #define rson (t[id].ch[1])
    const static int Size = 2 * Maxn;
    int f[Size];
    struct Node{
        int val, rnd;
        int size;
        int ch[2];
        int id, lazy;
        Node(){
            size = 0;
            rnd = rand();
            id = val = 0;
            ch[0] = ch[1] = 0;
            lazy = 0;
        }
        Node(int a, int b = 0){
            size = 1;
            rnd = rand();
            id = val = a;
            ch[0] = ch[1] = 0;
            lazy = b;
        }
        bool haveLazy(){
            return lazy != 0;
        }
        void resetLazy(){
            lazy = 0;
        }
        void operator *= (const Node T){
            val += T.lazy;
            lazy += T.lazy;
        }
    };
    void pushdown(int id){
        if (t[id].haveLazy()){
            if (lson)
                t[lson] *= t[id];
            if (rson)
                t[rson] *= t[id];
            t[id].resetLazy();
        }
    }
    void update(int id){
        t[id].size = 1 + t[lson].size + t[rson].size;
        if (lson)
            f[lson] = id;
        if (rson)
            f[rson] = id;
        f[id] = 0;
    }
public:
    Node t[Size];
    int newNode(int val){
        ++tot;
        t[tot] = Node(val);
        return tot;
    }
    int tot = 0;
    void split(int id, int val, int &x, int &y){
        if (!id)
            return (void)(x = y = 0);
        pushdown(id);
        if (t[id].val <= val){
            x = id;
            split(rson, val, rson, y);
        }
        else{
            y = id;
            split(lson, val, x, lson);
        }
        update(id);
    }
    int merge(int x, int y){
        if (!x || !y)
            return x + y;
        if (t[x].rnd < t[y].rnd){
            pushdown(x);
            t[x].ch[1] = merge(t[x].ch[1], y);
            update(x);
            return x;
        }
        else{
            pushdown(y);
            t[y].ch[0] = merge(x, t[y].ch[0]);
            update(y);
            return y;
        }
    }
    void add(int id){
        if (!id)
            return;
        mp[t[id].val + MaxV] = t[id].id;
        add(lson);
        add(rson);
    }
    void upd(int id){
        if (!id)
            return;
        DSU.merge(mp[t[id].val + MaxV] + MaxV, t[id].id + MaxV);
        upd(lson);
        upd(rson);
    }
    void pushdownTree(int id){
        if (!id)
            return;
        pushdown(id);
        pushdownTree(lson);
        pushdownTree(rson);
    }
    void addLazy(int rt, int lazy){
        if (rt == 0)
            return;
        t[rt] *= Node(0, lazy);
    }
    /**
     * @brief 切下来 l <= val <= r 的结点，保证 l或r 是rt的一端
     * @param rt 
     * @param l 
     * @param r 
     * @return int 切下来的结点对应的treap的根
     */
    int cut(int &rt, int l, int r){
        int x = 0, y = 0;
        split(rt, r, rt, x);
        split(rt, l - 1, rt, y);
        rt = merge(rt, x);
        return y;
    }
    Node kth(int rt, int k){
        while(rt){
            pushdown(rt);
            int lsize = t[t[rt].ch[0]].size;
            if (k <= lsize)
                rt = t[rt].ch[0];
            else if (k > lsize + 1)
                rt = t[rt].ch[1], k = k - lsize - 1;
            else
                return t[rt];
        }
        return Node(-2147483648);
    }
    int rank(int id){
        int res = t[lson].size + 1; //id的左子树和id自己
        for (int fa = f[id]; fa; id = fa, fa = f[id])
            if (id == t[fa].ch[1])
                res += t[t[fa].ch[0]].size + 1; //fa的左子树和fa自己
        return res;
    }
};
treap Treap;
int a[Maxn];
long long sum[Maxn];
int ans[Maxn];
struct Node{
    int id;
    int val;
};
vector <Node> change[Maxn], query[Maxn];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + a[i];
    int q;
    cin >> q;
    for (int i = 1; i <= q; i++){
        int l, r;
        long long x;
        cin >> l >> r >> x;
        int L = l - 1, R = r, res = r;
        if (x >= 0){
            while (L <= R){
                int mid = (L + R) >> 1;
                if (x - (sum[mid] - sum[l - 1]) <= a[res])
                    R = mid - 1, res = mid;
                else
                    L = mid + 1;
            }
            x = x - (sum[res] - sum[l - 1]);
        }else{
            while (L <= R){
                int mid = (L + R) >> 1;
                if (x + (sum[mid] - sum[l - 1]) > -a[res])
                    R = mid - 1, res = mid;
                else
                    L = mid + 1;
            }
            x = x + (sum[res] - sum[l - 1]);
        }
        l = res + 1;
        // cout << i << ' ' << l << ' ' << r << ' ' << x << ' ' << a[res] << endl;
        if (l > r){
            ans[i] = x;
        }else{
            change[l].push_back({i, (int)x});
            query[r].push_back({i, (int)x});
        }
    }
    DSU.init();
    int rt = 0;
    for (int i = -MaxV; i <= MaxV; i++)
        rt = Treap.merge(rt, Treap.newNode(i));
    int L = -MaxV, R = MaxV;
    //重要性质：区间一定是连续的, 结点id=结点初始值, 结点编号=结点初始值+MaxV+1=id+MaxV+1
    for (int i = 1; i <= n; i++){
        for (auto [id, val]: change[i]){
            // cout << "C: " << i << ' ' << id << ' ' << val - L + 1 << endl;
            DSU.merge(Treap.kth(rt, val - L + 1).id + MaxV, id + 2 * MaxV);
        }
        int rt1 = 0, rt2 = 0, rt3 = 0, rt4 = 0;
        Treap.split(rt, 0, rt1, rt2);
        Treap.addLazy(rt1, a[i]);
        Treap.addLazy(rt2, -a[i]);
        int l = max(L + a[i], -a[i] + 1), r = min(R - a[i], a[i]);
        rt3 = Treap.cut(rt1, l, r);
        rt4 = Treap.cut(rt2, l, r);
        Treap.pushdownTree(rt3);
        Treap.add(rt3);
        Treap.pushdownTree(rt4);
        Treap.upd(rt4);
        if (L + a[i] < -a[i] + 1)
            rt = Treap.merge(Treap.merge(rt1, rt3), rt2);
        else
            rt = Treap.merge(Treap.merge(rt2, rt3), rt1);
        L = min(L + a[i], -a[i] + 1), R = max(R - a[i], a[i]);
        for (auto [id, val]: query[i]){
            // cout << "Q: " << id << ' ' << ' '  << id + 2 * MaxV << ' ' << DSU.getfa(id + 2 * MaxV) + 1 << endl;
            ans[id] = Treap.rank(DSU.getfa(id + 2 * MaxV) + 1) + L - 1;
        }
    }
    for (int i = 1; i <= q; i++)
        cout << ans[i] << endl;
    return 0;
}
```

---

