# [USACO23JAN] Mana Collection P

## 题目描述

## 题目背景

**注意：这个问题的时间限制是5秒，是默认的2.5倍。这个问题的内存限制是512MB，是默认值的两倍。**


贝西需要为一个非常重要的法术收集法力。贝西有 $N$  $(1\le N\le 18)$ 个法力池，其中第 $i$ 个法力池每秒可积累 $m_i$ 法力 $(1\le m_i\le 10^8)$ 。这些池子由 $M$ $(0\le M\le N \cdot (N-1))$  条有向边 $(a_i,b_i,t_i)$ 连接，这意味着她可以在 $t_i$ 秒内从 $a_i$ 移动到 $b_i$ $(1\le a_i, b_i\le N$, $a_i\neq b_i$, $1\le t_i\le 10^9)$ 。每当贝西出现在一个池子里，她就可以收集储存在那个地方的所有法力，把它清空。在 $0$ 的时候，所有的法力池都是空的，贝西可以选择任何一个池子来开始收集。

回答 $Q$ $(1\le Q\le 2\cdot 10^5)$ 个查询，每个查询由两个整数 $s$ 和 $e$ 指定 $(1\le s\le 10^9$，$1\le e\le N)$ 。对于每个查询，如果贝西在第 $s$ 秒结束时必须在法力池 $e$ 处，请确定她在 $s$ 秒内能收集的最大法力值。

## 说明/提示

对于第一个样例：

第一次询问。贝西在 $5$ 秒后从水池 $1$ 中取出 $5$ 个法力值。

第二次查询。 $5$ 秒后，贝西从水池 $2$ 中获取 $50$ 点法力。

第三次查询。 $100$ 秒后，贝西从水池 $1$ 中获取 $100$ 法力值。

第四次查询。 $90$ 秒后贝西从水池 $1$ 中获得 $90$ 法力， $100$ 秒后从水池 $2$ 中获得 $1000$ 法力。

测试点 $3-4$: $N\le 10, Q\le 100$ 。

测试点 $5-9$: $N\le 10$ 。

测试点 $10-14$: $Q\le 100$ 。

测试点 $15-17$: $N = 16$ 。

测试点 $18-20$: $N = 17$ 。

测试点 $21-24$：没有其他约束条件 。

## 样例 #1

### 输入

```
2 1
1 10
1 2 10
4
5 1
5 2
100 1
100 2```

### 输出

```
5
50
100
1090```

## 样例 #2

### 输入

```
4 8
50000000 100000000 20000000 70000000
1 2 20
2 1 50
2 3 90
1 3 40
3 1 10
4 1 25
1 4 5
4 3 70
3
8 3
1000000000 1
500000 4```

### 输出

```
160000000
239999988050000000
119992550000000```

# 题解

## 作者：Ecrade_ (赞：12)

题意：

- 有 $n$ 个点，第 $i$ 个点每秒可产出 $f_i$ 点法力，初始时每个点的法力为 $0$。
- 有 $m$ 条单向路径，第 $i$ 条路径表示从 $a_i$ 直接走到 $b_i$ 需花费 $t_i$ 秒。
- 每走到一个点时可立即收集该点上的所有法力，收集完成后该点的法力清零。
- $q$ 次询问，每次给出一个时刻 $s$ 和一个点 $e$，求：
	- 在 $0$ 时刻，从任意一个点开始收集法力，在保证 $s$ 时刻恰好处在点 $e$ 的前提下，到 $s$ 时刻为止收集到的法力的最大值。
- $1\le n\le 18$，$0\le m\le n(n-1)$，$1\le q\le 2\cdot 10^5$，$1\le a_i,b_i,e\le n$，$a_i\neq b_i$，$1\le f_i\le 10^8$，$1\le t_i,s\le 10^9$。

---

记 $\text{dis}(x,y)$ 表示从 $x$ 走到 $y$ 所需的最短时间，先用 Floyd 算法将所有点对 $(x,y)$ 的 $\text{dis}(x,y)$ 求出。

容易发现，对于一条路径，收集到的法力仅与路径上所有点的最晚遍历时刻有关，也就是说，我们仅需知道这些点的最晚遍历时刻即可推算出收集到的法力大小。具体地，假设路径经过了 $c_1,c_2,\dots,c_k\ (c_k=e)$ 这些互不相同的点，且 $c_i$ 的最晚遍历时刻为 $d_i\ (0\le d_1<d_2<\dots<d_k=s)$，那么最终收集到的法力大小为 $\sum\limits_{i=1}^kf_{c_i}\cdot d_i$。

假如确定了 $c_1,c_2,\dots,c_k$，那么显然 $d_i$ 越大，收集到的法力就越多，又由于从 $c_i$ 走到 $c_{i+1}$ 至少需要 $\text{dis}(c_i,c_{i+1})$ 秒，故我们取 $d_i=s-\sum\limits_{j=i}^{k-1}\text{dis}(c_j,c_{j+1})$ 是最优的。改写一下法力大小的式子，$\sum\limits_{i=1}^kf_{c_i}\cdot d_i=\sum\limits_{i=1}^kf_{c_i}\cdot \left(s-\sum\limits_{j=i}^{k-1}\text{dis}(c_j,c_{j+1})\right)=s\cdot \sum\limits_{i=1}^kf_{c_i}-\sum\limits_{i=1}^{k-1}\text{dis}(c_i,c_{i+1})\sum\limits_{j=1}^if_{c_j}$。

将式中的 $\sum\limits_{i=1}^kf_{c_i}$ 看作斜率，$-\sum\limits_{i=1}^{k-1}\text{dis}(c_i,c_{i+1})\sum\limits_{j=1}^if_{c_j}$ 看作截距，那么它代表的就是一条直线。进一步地，对于一个确定的点集 $c_1,c_2,\dots,c_k$，由于斜率为定值，故我们仅需保留截距最大的那条直线即可，这可以通过状压来预处理。对于每个询问，我们仅需考虑满足 $c_k=e$ 的点集对应的直线，并求出当前横坐标 $s$ 对应的最大纵坐标即可，这可以通过单调栈维护凸包来预处理，询问时二分查找 $s$ 对应的是哪条直线即可。

但是别忘了，我们还需要保证 $d_1\ge 0$，即 $\sum\limits_{i=1}^{k-1}\text{dis}(c_i,c_{i+1})\le s$。而一旦加上了这个限制，问题就变得异常棘手了——我们需要额外记录 $d_i$ 的大小，复杂度直接上天。

仔细思考下，我们真的需要刻意满足这条限制吗？当然不用！因为当 $d_1,d_2,\dots,d_i$ 为负数时，仅保留 $c_{i+1},c_{i+2},\dots,c_k$ 显然更优，也就是说，最大值一定不会在 $d_1<0$ 的直线上。

至此，我们便用 $O(n^3+2^nn^2+qn)$ 的时间复杂度解决了本题。将所有询问离线处理，可以做到 $O(n^3+2^nn^2+q)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,q,x,y,z,a[19],dis[19][19],sum[1 << 18],f[1 << 18][19];
struct st{ll x,y;};
vector <st> seg[19];
vector <ll> stk[19];
vector <double> pnt[19];
bool cmp(const st &a,const st &b){return a.x < b.x || a.x == b.x && a.y > b.y;}
inline ll read(){
	ll s = 0,w = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0'){ if (ch == '-') w = -1; ch = getchar();}
	while (ch <= '9' && ch >= '0') s = (s << 1) + (s << 3) + (ch ^ 48),ch = getchar();
	return s * w;
}
void init(){
	for (ll i = 1;i < (1 << n);i += 1) for (ll j = 1;j <= n;j += 1) f[i][j] = 1e18;
	for (ll i = 1;i <= n;i += 1) for (ll j = 1;j <= n;j += 1) if (i ^ j) dis[i][j] = 1e18;
}
double get(ll o,ll x,ll y){
	if (seg[o][x].x == seg[o][y].x) return seg[o][x].y > seg[o][y].y ? -1e18 : 1e18;
	return 1.0 * (seg[o][y].y - seg[o][x].y) / (seg[o][x].x - seg[o][y].x);
}
void work(ll o){
	sort(seg[o].begin(),seg[o].end(),cmp);
	stk[o].emplace_back(0),pnt[o].emplace_back(-1e18);
	for (ll i = 0;i < seg[o].size();i += 1){
		st now = seg[o][i];
		while (stk[o].size() > 1 && get(o,i,stk[o].back()) < pnt[o].back()){
			stk[o].pop_back(),pnt[o].pop_back();
		}
		pnt[o].emplace_back(get(o,i,stk[o].back())),stk[o].emplace_back(i);
	}
}
int main(){
	n = read(),m = read(),init();
	for (ll i = 1;i <= n;i += 1) a[i] = read();
	for (ll i = 1;i <= m;i += 1) x = read(),y = read(),z = read(),dis[x][y] = z;
	for (ll i = 1;i <= n;i += 1) for (ll j = 1;j <= n;j += 1){
		for (ll k = 1;k <= n;k += 1) dis[j][k] = min(dis[j][k],dis[j][i] + dis[i][k]);
	}
	for (ll i = 1;i < (1 << n);i += 1){
		for (ll j = 1;j <= n;j += 1) if (i & (1 << j - 1)){
			sum[i] += a[j];
			ll qwq = i ^ (1 << j - 1);
			if (!qwq){f[i][j] = 0; break;}
			for (ll k = 1;k <= n;k += 1) if (qwq & (1 << k - 1)){
				if (dis[k][j] == 1e18) continue;
				f[i][j] = min(f[i][j],f[qwq][k] + sum[qwq] * dis[k][j]);
			}
		}
	}
	for (ll i = 1;i <= n;i += 1){
		for (ll j = 1;j < (1 << n);j += 1) if (j & (1 << i - 1)){
			seg[i].emplace_back((st){sum[j],-f[j][i]});
		}
		work(i);
	}
	q = read();
	while (q --){
		x = read(),y = read();
		ll pos = upper_bound(pnt[y].begin(),pnt[y].end(),x) - pnt[y].begin() - 1;
		printf("%lld\n",x * seg[y][stk[y][pos]].x + seg[y][stk[y][pos]].y);
	}
	return 0;
}
```

---

## 作者：_ZSR_ (赞：4)

### [P9020 [USACO23JAN] Mana Collection P](https://www.luogu.com.cn/problem/P9020)

正着不好求，我们考虑反着求。我们求一路上最少损失多少法力，然后用总的减去损失的就是获得的了。写成式子就是 $s \times \sum m_i-f$，其中 $f$ 表示损失的法力的最小值。

观察到，$n$ 的范围很小，因此考虑状压。令 $dp_{i}$ 表示经过的点的集合为 $i$ 的最小法力损失。因为题目规定了终点，所以一维是不够的。令 $dp_{i,j}$ 表示经过的点的集合为 $i$，最后一个到达的点是 $j$ 的最小法力损失。

接下来考虑转移。可以发现，从一个点到另一个点的过程中，之前已经经过的所有点都会以每秒 $m_i$ 的速度损失法力，因此可以写出转移方程：$dp[sta][i]=\min(dp[sta][i],dp[newsta][j]+dis[j][i] \times sum[newsta])$。其中 $sum_{i}$ 表示点集 $i$ 中的所有点的 $m$ 之和。

回到最开始的那个式子，可以发现，这就是一个关于 $s$ 的一次函数，因此直接用李超树就可以了。

code
```
#include <bits/stdc++.h>
using namespace std;
const int N=20,M=5e6+10;
typedef long long ll;
int n,m,tot,q;
int a[N],rt[N];
ll dis[N][N];
ll sum[1<<N];
ll dp[1<<N][N];
struct Function{
    ll k,b;
    ll operator() (const ll &x) const
    {
        return k*x+b;
    }
};
struct Tree{
    int l,r;
    Function f;
}tr[M];
void modify(int &p,int l,int r,Function h)
{
    if (!p)
    {
        p=++tot;
        tr[p].f=h;
        return;
    }
    if (l==r)
    {
        if (h(l)>tr[p].f(l)) tr[p].f=h;
        return;
    }
    int mid=l+r>>1;
    if (h(mid)>tr[p].f(mid)) swap(h,tr[p].f);
    if (h(l)>=tr[p].f(l)) modify(tr[p].l,l,mid,h);
    if (h(r)>=tr[p].f(r)) modify(tr[p].r,mid+1,r,h);
}
ll query(int p,int l,int r,int x)
{
    if (!p) return 0;
    int mid=l+r>>1;
    ll res=tr[p].f(x);
    if (x<=mid) res=max(res,query(tr[p].l,l,mid,x));
    else res=max(res,query(tr[p].r,mid+1,r,x));
    return res;
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i) scanf("%d",&a[i]);
    for (int i=1;i<=n;++i)
    {
        for (int j=1;j<=n;++j)
        {
            if (i^j) dis[i][j]=1e18;
        }
    }
    for (int i=1;i<=m;++i)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        dis[u][v]=w;
    }
    for (int k=1;k<=n;++k)
    {
        for (int i=1;i<=n;++i)
        {
            for (int j=1;j<=n;++j)
            {
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
    }
    for (int sta=0;sta<(1<<n);++sta)
    {
        for (int i=1;i<=n;++i)
        {
            dp[sta][i]=1e18;
        }
    }
    for (int sta=1;sta<(1<<n);++sta)
    {
        for (int i=1;i<=n;++i)
        {
            if (!(sta&(1<<i-1))) continue;
            sum[sta]+=a[i];
            int newsta=sta^(1<<i-1);
            if (!newsta)
            {
                dp[sta][i]=0;
                break;
            }
            for (int j=1;j<=n;++j)
            {
                if (!(newsta&(1<<j-1))) continue;
                if (dis[j][i]==1e18) continue;
                dp[sta][i]=min(dp[sta][i],dp[newsta][j]+dis[j][i]*sum[newsta]);
            }
        }
    }
    for (int sta=1;sta<(1<<n);++sta)
    {
        for (int i=1;i<=n;++i)
        {
            if (!(sta&(1<<i-1))) continue;
            if (dp[sta][i]<1e18) modify(rt[i],1,1e9,{sum[sta],-dp[sta][i]});
        }
    }
    scanf("%d",&q);
    while (q--)
    {
        int s,e;
        scanf("%d%d",&s,&e);
        printf("%lld\n",query(rt[e],1,1e9,s));
    }
    return 0;
}
```


---

## 作者：Masterwei (赞：3)

不错的题。

首先发现在一条路径中，一个点的贡献只用算最后出现的时间即可。

但是由于询问是确定终点，正着不好做，所以我们考虑将整个图反过来，也就是建反边。

那么对于一条路径，一个点 $u$ 的贡献就是 $(s-t_u)f_u$，其中 $t_u$ 表示 $u$ 在这条路径上最早出现的时间，拆开式子，对于每个点分别算 $s\times f_u$ 和 $t_uf_u$。

发现 $n$ 很小，考虑状压，对于一种状态 $S$，我们设 $sum_S$ 表示 $S$ 状态下 $f$ 的和，$F_{S,u}$ 表示在 $S$ 状态下，以 $u$ 为起点（反图中），$t_xf_x$ 的和的最小值，其中 $x$ 是以 $u$ 开头路径中的一点（包含 $u$）。$sum$ 数组和 $F$ 数组均可简单预处理。


那么对于一个 $S$，最优的答案就是 $s\times sum_S-F_{S,e}$。

这样我们直接算答案时间复杂是 $O(q2^n)$ 的，但是可以发现求答案的形式就是个一次函数，所以直接李超树即可。

时间复杂度 $O(2^nn(n+\log V)+q\log V)$。其中 $V$ 是时间的最大值。


注意此题李超树会炸 long long，记得乘的时候开一下 __int128。

```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=(1<<18)+5,inf=1e18,V=1e9;
int n,m,q;
int a[Maxn],sum[Maxn];
int e[20][20];
int f[Maxn][20];
struct point{
	int k,b;
	inline int get(int x){return k*x+b;}
};
struct tree{
	struct Tree{
		int ls,rs;point data;
	}t[Maxn*20];
	int root,cnt;
	void change(int&x,int l,int r,point g){
		if(!x)x=++cnt,t[x]={0,0,{0,-inf}};int mid=l+r>>1;
		if(t[x].data.get(mid)<g.get(mid))swap(t[x].data,g);
		if(l==r)return;
		if(t[x].data.get(l)<g.get(l))change(t[x].ls,l,mid,g);
		if(t[x].data.get(r)<g.get(r))change(t[x].rs,mid+1,r,g);
	}
	int query(int x,int l,int r,int d){
		if(l==r)return t[x].data.get(d);
		int mid=l+r>>1;
		if(mid>=d)return max(t[x].data.get(d),query(t[x].ls,l,mid,d));
		return max(t[x].data.get(d),query(t[x].rs,mid+1,r,d));
	}
}T[20];
signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)T[i].t[0]={0,0,{0,-inf}};
	memset(f,0x7f,sizeof f);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)e[i][j]=inf;
	for(int i=1;i<=n;i++)a[1<<i-1]=read(),f[1<<i-1][i]=0,T[i].change(T[i].root,1,V,{a[1<<i-1],0});
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		e[u][v]=w;
	}
	for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)e[i][j]=min(e[i][j],e[i][k]+e[k][j]);
	for(int s=1;s<(1<<n);s++)sum[s]=sum[s^(s&-s)]+a[(s&-s)];
	for(int s=1;s<(1<<n);s++){
		if(__builtin_popcount(s)==1)continue;
		for(int i=1;i<=n;i++){
			if((s>>i-1)&1){
				for(int j=1;j<=n;j++)
					if(i!=j&&((s>>j-1)&1))f[s][i]=min(f[s^(1<<i-1)][j]+e[j][i]*sum[s^(1<<i-1)],f[s][i]);
				T[i].change(T[i].root,1,V,{sum[s],-f[s][i]});
			}
		}
	}
	q=read();
	while(q--){
		int ti=read(),u=read();
		printf("%lld\n",(long long)T[u].query(T[u].root,1,V,ti));
	}
	return 0;
}


```

---

## 作者：绝顶我为峰 (赞：2)

这里是赛后两分钟调出来这题的小丑。

首先一个显然但重要的事实是任何时刻我都可以待在某个点不动，这意味着我们可以先等很长时间，然后再走到要求的点。

另一个性质是如果一个点经过了多次，那么我们可以只在最后一次经过的时候记录这个点，因为取多次和取一次获得的贡献是相等的。

这个时候我们考虑一条路径事实上对应了一个损失 $f$，即你到达终点时路径经过的所有点积攒的贡献和。假设时间是 $t$，那么这条路径的贡献就是 $(\sum\limits_pm_p)t-f$，也就是先算能产生多少再减掉损失。

这明显是关于 $t$ 的一次函数，可以直接用李超树查询，关键在于怎样求出 $f$。

考虑 dp，先枚举起点，记 $dp_{s,i}$ 表示经过了 $s$ 中的点，现在在 $i$ 的最小损失，转移可以直接贡献推迟计算，得到转移方程 $dp_{s,i}+sum_s\times dis_{i,j}\rightarrow dp_{s+\{j\}},j$，其中 $sum_s=\sum\limits_{i\in s}m_i$，$dis_{i,j}$ 是两点的最短路，分别可以在 $O(n2^n)$ 和 $O(n^3)$ 的时间复杂度内预处理得到。

这样我们对于每个点集 $s$ 都求出了最小损失，再对每个终点和点集找出从哪个起点出发损失最小，把对应的一次函数插入这个终点对应的李超树即可，查询直接在终点的李超树里查询。

这里可能有一个问题是路径长度大于 $t$ 的一次函数也在李超树中，不过这并不会影响最终答案。证明就考虑超时的那一部分贡献一定是负的，不如直接扔掉这一段。

时间复杂度 $O(n^32^n+qn)$。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,root[21],tot,ls[3500001],rs[3500001];
long long dis[21][21],val[1<<18],dp[1<<18][18],maxn[18][1<<18];
struct element
{
    long long a,b;
    long long operator ()(const long long &x) const
    {
        return a*x+b;
    }
}f[3500001];
inline void init()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}
inline long long read()
{
    long long x;
    cin>>x;
    return x;
}
inline void update(int l,int r,int &k,element p)
{
    if(!k)
    {
        k=++tot;
        f[k]=p;
        return;
    }
    if(l==r)
    {
        if(p(l)>f[k](l))
            f[k]=p;
        return;
    }
    int mid=(l+r)>>1;
    if(p(mid)>f[k](mid))
        swap(f[k],p);
    if(p(l)>=f[k](l))
        update(l,mid,ls[k],p);
    if(p(r)>=f[k](r))
        update(mid+1,r,rs[k],p);
}
inline long long query(int node,int l,int r,int &k)
{
    if(!k)
        return 0;
    int mid=(l+r)>>1;
    long long res=f[k](node);
    if(node<=mid)
        res=max(res,query(node,l,mid,ls[k]));
    else
        res=max(res,query(node,mid+1,r,rs[k]));
    return res;
}
signed main()
{
    init();
    n=read(),m=read();
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            dis[i][j]=1e18;
    for(int i=0;i<n;++i)
    {
        val[1<<i]=read();
        for(int s=0;s<1<<n;++s)
            maxn[i][s]=-1e18;
    }
    for(int i=0;i<n;++i)
        for(int s=0;s<1<<n;++s)
            if(s>>i&1)
                val[s]+=val[s^(1<<i)];
    for(int i=1;i<=m;++i)
    {
        int x=read()-1,y=read()-1;
        dis[x][y]=min(dis[x][y],read());
    }
    for(int k=0;k<n;++k)
        for(int i=0;i<n;++i)
            if(i!=k)
                for(int j=0;j<n;++j)
                    if(i!=j&&j!=k)
                        dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    for(int i=0;i<n;++i)
    {
        for(int s=0;s<1<<n;++s)
            for(int j=0;j<n;++j)
                dp[s][j]=1e18;
        dp[1<<i][i]=0;
        for(int s=1;s<1<<n;++s)
            if(s>>i&1)
                for(int j=0;j<n;++j)
                    if((s>>j&1)&&dp[s][j]<1e18)
                        for(int k=0;k<n;++k)
                            if((s>>k&1^1)&&dis[j][k]<1e18)
                                dp[s|(1<<k)][k]=min(dp[s|(1<<k)][k],dp[s][j]+dis[j][k]*val[s]);
        for(int s=1;s<1<<n;++s)
            if(s>>i&1)
                for(int j=0;j<n;++j)
                    if((s>>j&1)&&dp[s][j]<1e18)
                        maxn[j][s]=max(maxn[j][s],-dp[s][j]);
    }
    for(int i=0;i<n;++i)
        for(int s=0;s<1<<n;++s)
            if(maxn[i][s]>-1e18)
                update(1,1e9,root[i],{val[s],maxn[i][s]});
    m=read();
    while(m--)
    {
        int t=read();
        cout<<query(t,1,1e9,root[read()-1])<<'\n';
    }
    cout.flush();
    return 0;
}
```

---

## 作者：PersistentLife (赞：1)

### [【USACO23JAN_Pt T2】Mana Collection](http://usaco.org/index.php?page=viewproblem2&cpid=1285)

[cnblogs](https://www.cnblogs.com/znstz2018/p/17087422.html)

一个很显然的性质：若一个点被经过多次，则只在最后一次取走一定不劣。设在这个性质下，依次取走 $u_1,u_2, \cdots ,u_k$ 上的物品，则对于所有 $i \in [1,k-1]$，$u_i$ 走到 $u_{i+1}$ 一定经过的是最短路。在原图中跑 Floyd 求出全源最短路，并建立新图：两点之间的边权是原图中两点间的最短路。对于每个询问要找到一条简单路径最大化：$\sum m_{u_i}(T-dist(u_i,e))=T\sum m_{u_i}-\sum m_{u_i}dist(u_i,e)$。

令 $dp(S,u)$ 表示：已经访问过 $S$ 中的点，目前在点 $u$，$\sum m_{u_i}dist(u_i,e)$ 的最小值是多少。转移枚举下一个访问到的点 $v$，将 $dp(S,u)+\sum_{x \in S+\{v\}} m_xdist(u,v)$ 转移到 $dp(S+\{v\},v)$ 即可。

考虑统计答案，对于一个 $s,e$ 的查询，有 $ans=\max_{T} \sum_{x \in T} m_xs-dp(T,e)$，发现这可以看做一条斜率为 $\sum_{x \in T} m_x$，截距为 $dp(T,e)$ 的直线，将询问离线用李超树或者凸壳维护即可，复杂度 $O(2^n poly(n))$。

一个疑问：统计答案的时候如果 $dp(T,e)$ 没有时间走完怎么办。你会发现如果走不完，则第一个访问到的点是”负贡献“，不断删去第一个点，一定可以找到一个能走完的且更优的 $dp(T',e)$。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define fi first
#define se second
#define pii pair<long long,long long>
#define mp make_pair
#define pb push_back
const int mod=998244353;
const int inf=0x3f3f3f3f;
const int INF=1e18;
int n,m;
int g[18][18];
int dp[1<<18][18],f[1<<18][18];
int sumw[1<<18];
int w[18];
vector <pii > res[18];
struct Line
{
	int k,b;
}p[1000005];
int t[12000005];
int ls[12000005],rs[12000005];
int idx,tid;
void init()
{
	idx=0,tid=1;
	ls[1]=0,rs[1]=0,t[1]=0;
	p[0].k=1,p[0].b=-9LL*INF;
}
void add_line(int k,int b)
{
	p[++idx].k=k;
	p[idx].b=b;
}
int get_y(int id,int x)
{
	return p[id].k*x+p[id].b;
}
void update(int &id,int l,int r,int lid)
{
//	cout<<id<<" "<<l<<" "<<r<<" "<<lid<<endl;
	if(!id) id=++tid,t[id]=0,ls[id]=rs[id]=0;
	int mid=(l+r)>>1;
	if(get_y(lid,mid)>get_y(t[id],mid)) swap(lid,t[id]);
	if(get_y(lid,l)>get_y(t[id],l)) update(ls[id],l,mid,lid);
	if(get_y(lid,r)>get_y(t[id],r)) update(rs[id],mid+1,r,lid);	
}
void insert(int &id,int l,int r,int x,int y,int lid)
{
	if(!id) id=++tid,t[id]=0,ls[id]=rs[id]=0;
	if(x<=l&&r<=y)
	{
		update(id,l,r,lid);
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) insert(ls[id],l,mid,x,y,lid);
	if(y>mid) insert(rs[id],mid+1,r,x,y,lid);
}
int query(int id,int l,int r,int x)
{
	if(!id) return -1;
	int mid=(l+r)>>1;
	int res=get_y(t[id],x);
//	cout<<id<<" "<<l<<" "<<r<<" "<<t[id]<<" "<<x<<" "<<res<<endl;
	if(l==r) return res;
	if(x<=mid) res=max(res,query(ls[id],l,mid,x));
	else res=max(res,query(rs[id],mid+1,r,x));
	return res;
}
vector <pii > que[18];
int ans[200005];
void solve()
{
	scanf("%lld%lld",&n,&m);
	for(int i=0;i<n;i++) scanf("%lld",&w[i]);
	memset(g,0x3f,sizeof(g));
	while(m--)
	{
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		u--,v--;
		g[u][v]=w;
	}
	for(int i=0;i<n;i++) g[i][i]=0;
	for(int k=0;k<n;k++) for(int i=0;i<n;i++) for(int j=0;j<n;j++) g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
	memset(dp,0x3f,sizeof(dp)),memset(f,0x3f,sizeof(f));
	for(int mask=0;mask<(1<<n);mask++) for(int i=0;i<n;i++) if(mask&(1<<i)) sumw[mask]+=w[i];
	for(int i=0;i<n;i++) dp[1<<i][i]=0,f[1<<i][i]=0;
	for(int mask=0;mask<(1<<n);mask++) for(int i=0;i<n;i++) if(f[mask][i]<INF)
	{
		for(int j=0;j<n;j++) if(g[i][j]<INF) if(!(mask&(1<<j)))
		{
			dp[mask|(1<<j)][j]=min(dp[mask|(1<<j)][j],dp[mask][i]+sumw[mask]*g[i][j]);
			f[mask|(1<<j)][j]=min(f[mask|(1<<j)][j],f[mask][i]+g[i][j]);
		}
	}
	for(int mask=0;mask<(1<<n);mask++) for(int i=0;i<n;i++) if(f[mask][i]<INF) res[i].pb(mp(sumw[mask],-dp[mask][i]));
	for(int i=0;i<n;i++) sort(res[i].begin(),res[i].end()),reverse(res[i].begin(),res[i].end()); 
	int q;
	scanf("%lld",&q);
	for(int i=1;i<=q;i++)
	{
		int t,u;
		scanf("%lld%lld",&t,&u);
		u--;
		que[u].pb(mp(t,i));
	}
	int rt=1;
	for(int i=0;i<n;i++)
	{
		init();
		for(int j=0;j<res[i].size();j++) 
		{
			add_line(res[i][j].fi,res[i][j].se);
			insert(rt,1,1000000005,1,1000000005,idx);
		}
		for(int j=0;j<que[i].size();j++) ans[que[i][j].se]=query(rt,1,1000000005,que[i][j].fi);
	}
	for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
}
signed main()
{
	int _=1;
//	cin>>_;
	while(_--) solve();
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

根据最优结构调整，可以改写为：从 $e$ 点出发，到每个点去收集能量。每个点初始有能量 $s \times m_i$，每秒会损失 $m_i$ 个能量。

因此你访问的点集一定时，初始能量和为定值，我们需要损失的能量尽量少。

显然损失的能量可以用状压 DP 实现，这个好像比较简单，先预处理两两最短路，再暴力转移即可。

这样每个集合 $S$ 都有最优的损失能量 $f_S$。相当于我们需要计算 $sw_S -f_S$ 的最大值（其中 $w_S$ 表示集合 $S$ 的 $m_i$ 之和）。

注意到如果 $f_S$ 用的时间超过了 $s$，那么必定有一个点带来了负的代价，错解不优直接忽略。

而这个一次函数的形式用动态开点李超线段树直接维护即可。

众所周知，我的素质比较低下，直接使用 `__int128` 而避开了对值域的估计。反正也就常数大一点。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=20,MAXM=(1<<18)+10;
int n,m,q,c[MAXN];
__int128 dis[MAXN][MAXN],dp[MAXN][MAXM],sum[MAXM];
namespace DS {
	#define mid (l+r>>1)
	struct SEG {__int128 k,b;__int128 f(__int128 x) {return k*x+b;}}t[MAXM];
	int rt,tot,ls[MAXM],rs[MAXM];
	void update(int &u,int l,int r,SEG sg) {
		if(!u) return u=++tot,t[u]=sg,void();
		if(l==r) return ;
		if(t[u].f(mid)<sg.f(mid)) swap(t[u],sg);
		if(t[u].k>=sg.k) update(ls[u],l,mid,sg);
		else update(rs[u],mid+1,r,sg);
		return ;
	}
	__int128 query(int u,int l,int r,int pos) {
		if(!u) return 0;
		__int128 ans=t[u].f(pos);
		if(l!=r) ans=max(ans,(pos<=mid)?query(ls[u],l,mid,pos):query(rs[u],mid+1,r,pos));
		return ans;
	}
	void init(void) {return memset(ls,0,sizeof(ls)),memset(rs,0,sizeof(rs)),tot=0,rt=0,void();}
};
int ans[MAXM];
vector<pair<int,int>> qr[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m; memset(dis,0x3f,sizeof(dis));
	ffor(i,1,n) cin>>c[i];
	ffor(i,1,m) {int u,v,w;cin>>u>>v>>w,dis[u][v]=min(dis[u][v],(__int128)w);}
	ffor(k,1,n) ffor(i,1,n) ffor(j,1,n) dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	ffor(i,1,(1<<n)-1) ffor(j,1,n) if(i&(1<<j-1)) sum[i]+=c[j];
	memset(dp,0x3f,sizeof(dp));
	ffor(i,1,n) dp[i][(1<<i-1)]=0;
	ffor(s,1,(1<<n)-1) ffor(t,1,n) if(s&(1<<t-1)) ffor(l,1,n) if(dis[l][t]<=LONG_LONG_MAX) if((s&(1<<l-1))&&l!=t) dp[t][s]=min(dp[t][s],dp[l][s-(1<<t-1)]+dis[l][t]*sum[s-(1<<t-1)]);
	cin>>q;
	ffor(i,1,q) {
		int s,e;
		cin>>s>>e;
		qr[e].push_back({s,i});	
	}
	ffor(i,1,n) {
		DS::init();
		ffor(s,1,(1<<n)-1) if(s&(1<<i-1)) DS::update(DS::rt,1,1000000000,{sum[s],-dp[i][s]});
		for(auto pr:qr[i]) ans[pr.second]=DS::query(1,1,1000000000,pr.first);	
	}
	ffor(i,1,q) cout<<ans[i]<<'\n';
	return 0;
}
```

---

