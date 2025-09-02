# Expected diameter of a tree

## 题目描述

Pasha is a good student and one of MoJaK's best friends. He always have a problem to think about. Today they had a talk about the following problem.

We have a forest (acyclic undirected graph) with $ n $ vertices and $ m $ edges. There are $ q $ queries we should answer. In each query two vertices $ v $ and $ u $ are given. Let $ V $ be the set of vertices in the connected component of the graph that contains $ v $ , and $ U $ be the set of vertices in the connected component of the graph that contains $ u $ . Let's add an edge between some vertex ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/8ef01bdc02f37e886781700f62479c92154da008.png) and some vertex in ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/0479fe8afb5e9211cdac4c2d711ca0b8e2ad6e82.png) and compute the value $ d $ of the resulting component. If the resulting component is a tree, the value $ d $ is the diameter of the component, and it is equal to -1 otherwise. What is the expected value of $ d $ , if we choose vertices $ a $ and $ b $ from the sets uniformly at random?

Can you help Pasha to solve this problem?

The diameter of the component is the maximum distance among some pair of vertices in the component. The distance between two vertices is the minimum number of edges on some path between the two vertices.

Note that queries don't add edges to the initial forest.

## 说明/提示

In the first example the vertices $ 1 $ and $ 3 $ are in the same component, so the answer for the first query is -1. For the second query there are two options to add the edge: one option is to add the edge $ 1-2 $ , the other one is $ 2-3 $ . In both ways the resulting diameter is $ 2 $ , so the answer is $ 2 $ .

In the second example the answer for the first query is obviously -1. The answer for the second query is the average of three cases: for added edges $ 1-2 $ or $ 1-3 $ the diameter is $ 3 $ , and for added edge $ 1-4 $ the diameter is $ 2 $ . Thus, the answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/80f05d9f9a5abbad800eeb11e2f309500aaccabe.png).

## 样例 #1

### 输入

```
3 1 2
1 3
3 1
2 3
```

### 输出

```
-1
2.0000000000
```

## 样例 #2

### 输入

```
5 2 3
2 4
4 3
4 2
4 1
2 5
```

### 输出

```
-1
2.6666666667
2.6666666667
```

# 题解

## 作者：Graphcity (赞：14)

首先发现这道题的期望是假的，我们需要算两棵树 $x,y$ 中所有连边方式的直径长度和除以 $siz_x\times siz_y$。

我们都知道，距离树上一个点最远的点中，一定有一个是直径的端点。所以找出每棵树的直径端点，然后就可以 dfs 求出所有点的最远距离 $mx_i$。

如果我们在两棵树 $x,y$ 中选择了两个点 $a,b$ 进行连边，那么直径的长度显然是 $\max(d_x,d_y,mx_a+mx_b+1)$。左边 $\max(d_x,d_y)$ 这部分很好处理，难算的是右边 $mx_a+mx_b+1$ 产生的贡献。

一种比较自然的思路是对于 $x$ 树的每个点 $s$，找到 $y$ 树中所有满足 $mx_s\ge \max(d_x,d_y)-mx_t$ 的 $s$ 的个数与距离和。注意到 $mx_s\le siz_y$，而 $\sum_ysiz_y=n$，所以可以直接前缀和 $O(n)$ 预处理并 $O(1)$ 回答每个询问。

这样我们回答一次询问的时间复杂度就变为了 $\min(siz_x,siz_y)$，因为我们可以枚举结点个数少的那一棵树。如果我们用 map 记忆化所有的询问，总时间复杂度是 $O(n\sqrt n)$ 的（这里默认 $n,q$ 同阶）。为什么呢？

考虑将所有树按照大小分为 $\le \sqrt n$ 和 $>\sqrt n$ 两个部分。

- 对于小树和任意树的询问，由于小树的大小 $\le \sqrt n$，所以总时间复杂度 $O(n\sqrt n)$。
- 对于两棵大树之间的询问，注意到大树的个数不超过 $\sqrt n$ 个，所以每一棵大树对总复杂度的贡献次数不超过 $\sqrt n$，总时间复杂度 $O(n\sqrt n)$。

综上，这种方法的时间复杂度为 $O(n\sqrt n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,q,fa[Maxn+5],siz[Maxn+5];
int mx[Maxn+5],dis[Maxn+5],ans[Maxn+5];
vector<int> v[Maxn+5],w[Maxn+5],cnt[Maxn+5];
vector<ll> sum[Maxn+5];
map<pair<int,int>,double> mp;
inline int Find(int x) {return fa[x]==x?x:fa[x]=Find(fa[x]);}

inline void dfs(int x,int f,int d)
{
    mx[x]=max(mx[x],d),dis[x]=d;
    for(auto y:v[x]) if(y!=f) dfs(y,x,d+1);
}
inline double Solve(int x,int y)
{
    int dx=max(ans[x],ans[y]); ll s1=1ll*siz[x]*siz[y],s2=0;
    for(auto i:w[x]) if(dx-mx[i]<=siz[y])
    {
        if(!(dx-mx[i]))
        {
            s1-=cnt[y][siz[y]],s2+=sum[y][siz[y]];
            s2+=1ll*mx[i]*cnt[y][siz[y]];
        }
        else
        {
            ll a=cnt[y][siz[y]]-cnt[y][dx-mx[i]-1];
            ll b=sum[y][siz[y]]-sum[y][dx-mx[i]-1];
            s1-=a,s2+=b+a*mx[i];
        }
    }
    ll res=s1*dx+s2; return 1.0*res/(1ll*siz[x]*siz[y]);
}

int main()
{
    n=read(),m=read(),q=read();
    For(i,1,n) fa[i]=i,siz[i]=1;
    For(i,1,m)
    {
        int a=read(),b=read();
        v[a].push_back(b),v[b].push_back(a);
        a=Find(a),b=Find(b);
        if(a!=b) fa[a]=b,siz[b]+=siz[a];
    }
    For(i,1,n) w[Find(i)].push_back(i);
    For(i,1,n) if(fa[i]==i)
    {
        int rt=0; dfs(i,0,0);
        for(auto j:w[i]) if(dis[j]>dis[rt]) rt=j;
        dfs(rt,0,0);
        for(auto j:w[i]) if(dis[j]>dis[rt]) rt=j;
        dfs(rt,0,0);
        sum[i].resize(siz[i]+3),cnt[i].resize(siz[i]+3);
        for(auto j:w[i]) cnt[i][mx[j]]++,sum[i][mx[j]]+=mx[j]+1,ans[i]=max(ans[i],mx[j]);
        For(j,1,siz[i]) cnt[i][j]+=cnt[i][j-1],sum[i][j]+=sum[i][j-1];
    }
    while(q--)
    {
        int a=read(),b=read(); a=Find(a),b=Find(b);
        if(a==b) {printf("-1\n"); continue;}
        if(siz[a]>siz[b]) swap(a,b);
        if(mp[make_pair(a,b)]) printf("%.8lf\n",mp[make_pair(a,b)]);
        else printf("%.8lf\n",mp[make_pair(a,b)]=Solve(a,b));
    }
    return 0;
}
```

---

## 作者：violin_wyl (赞：5)

### Expected diameter of a tree

#### 解析：

###### 题目大意：

给一片森林，$q$ 个询问，每个询问两个点，问将这两个点所在的树连接起来组成的新树，它的期望直径长度的值是多少。

--------------------------

###### 思路：

大套路，但细节巨多，调了一天zbl

考虑直径的期望怎么算，很明显为$\frac{\text{直径的总长度}}{\text{新树的个数}}$，其中能组成的数的个数很明显就是 $siz_u\times siz_v$ ，考虑怎么算上面的部分。

我们考虑换根dp，先预处理出来每个点到当前树中最远的点的距离，记为 $dp_i$（其实直接考虑树中每个点到直径两个端点的距离的最大值即可），我们设当前需要连接的两个点为 $u,v$ ，那组成的新树的直径为 $\max (len_1,len_2,dp_u+dp_v+1)$，我们考虑把 $dp$ 处理出来对于每棵树从小到大排序，然后问题就转化为求下面这个式子：
$$
ans=\sum_{i\in A,j\in B}dp_i+dp_j+1(dp_i+dp_j+1\geq mx)+\max(len_1,len_2)\times \sum_{i\in A,j\in B}[dp_i+dp_j+1<mx]
$$
表示对于 $u$ 和 $v$ 连接起来会影响影响直径的 $dp_u+dp_v+1$ 的和和不会影响直径的点对 $(u,v)$ 的个数乘 $\max(len_1,len_2)$。

我在这里卡了一段时间，最开始想到根号分治以为复杂度假了没敢写，后来听巨佬分析了一下觉得很对，所以考虑对树的大小进行根号分治，对于每次查询的两棵树，如果有一者的点数小于 $\sqrt n$ ，那我们直接暴力枚举这棵树上的每个点，在第二棵树中二分找使得与当前枚举到的第一棵树中的点相加小于 $\max(len_1,len_2)$ 的点的个数和大于当前 $\max(len_1,len_2)$ 的距离和，这里可以前缀和预处理一下，那么只要二分找到了当前点就可以 $\mathcal O(1)$ 求距离了。

对于两棵树都大于 $\sqrt n$ 的部分，我们考虑预处理，考虑枚举第一棵树，再枚举当前树中的每个点，然后再往后找每棵大小大于 $\sqrt n$ 的树，并在里面二分。考虑分析一下复杂度，最坏情况下应该有 $\sqrt n$ 棵大小在 $\sqrt n$ 的树，那枚举需要预处理的每对树的组合是 $\mathcal O((\sqrt n)^2)=\mathcal O(n)$ 的，我们还需要在每棵树中枚举每个点，因为每棵树只会遍历一次，所以这部分是均摊 $\mathcal O(n)$ 的，每棵树一共有 $\sqrt n$ 个节点，对于每个点我都需要在后面的树中二分找，这部分是 $\sqrt n\log n$，所以总时间复杂度是 $O(n\sqrt n \log n)$的。

具体细节请看代码。

时间复杂度 $\mathcal O(n\sqrt n\log n+q\sqrt n\log n)$，常数好就可以通过本题。

----------------------------------------------------

#### code：

```c++
#include <bits/stdc++.h>
#define int long long // 注意开 long long
#define pb push_back
#define pob pop_back
#define pf push_front
#define pof pop_front
#define lob lower_bound
#define fi first
#define se second
#define mk make_pair
using namespace std;
const int N = 1e5 + 10;
const int SN = 400 + 10;
const int INF = INT_MAX;
typedef pair <int, int> pii;
inline int read ( )
{
    int x = 0, f = 1;
    char ch = getchar ( );
    while (ch < '0' || ch > '9') {if (ch == '-') f = - 1; ch = getchar ( );}
    while (ch >= '0' && ch <='9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar ( );}
    return x * f;
}
int n, m, q;
struct edge {
    int ver, nxt;
} e[N << 1];
int head[N], tot;
void add_edge (int u, int v) { e[++tot] = (edge) {v, head[u]}; head[u] = tot; }
int cnt;
bool vis[N];
int belong[N], Dim, dim[N];
int siz[N], len[N], len2[N], son[N];
int block[N], bcnt, from[N];
int f[SN][SN];
vector <int> vec[N], sum[N];
void dfs (int u, int f, int b)
{
    vis[u] = 1;
    siz[b]++; len[u] = 0;
    belong[u] = b;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].ver;
        if (v == f) continue;
        dfs (v, u, b);
        Dim = max (Dim, len[u] + len[v] + 1);
        if (len[v] + 1 >= len[u]) { len2[u] = len[u]; len[u] = len[v] + 1; son[u] = v; }
        else len2[u] = max (len2[u], len[v] + 1);
    }
}
void dfs2 (int u, int f, int l)
{
    vis[u] = 1;
    if (son[u]) dfs2 (son[u], u, max (len2[u], l) + 1);
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].ver;
        if (v != f && v != son[u])
            dfs2 (v, u, max (len[u], l) + 1);
    }
    len[u] = max (len[u], l);
    vec[belong[u]].pb (len[u]);
}
void solve (int x)
{
    for (int i = 0; i < vec[block[x]].size (); i++) // 对于当前树枚举每个点
    {
        for (int j = x + 1; j <= bcnt; j++) // 往后找需要处理的树
        {
            int y = block[j];
            int mx = max (dim[block[x]], dim[y]), s = vec[y].size ();
            int l = 0, r = s - 1, res = s;
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                if (vec[block[x]][i] + vec[y][mid] + 1 < mx) l = mid + 1, res = mid;
                else r = mid - 1;
            }
            if (vec[block[x]][i] + vec[y][0] + 1 >= mx)
                f[x][j] += vec[block[x]][i] * s + sum[y][s - 1] + s;
            else if (vec[block[x]][i] + vec[y][s - 1] + 1 < mx)
                f[x][j] += mx * s;
            else
                f[x][j] += mx * (res + 1) + vec[block[x]][i] * (s - res - 1) + (sum[y][s - 1] - sum[y][res]) + (s - res - 1);
        }
    }
}
int getans (int x, int y)
{
    int mx = max (dim[x], dim[y]), ans = 0, s = vec[y].size ();
    for (int i = 0; i < vec[x].size (); i++)
    {
        int l = 0, r = s - 1, res = s;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (vec[x][i] + vec[y][mid] + 1 < mx) l = mid + 1, res = mid;
            else r = mid - 1;
        }
        if (vec[x][i] + vec[y][0] + 1 >= mx)
            ans += vec[x][i] * s + sum[y][s - 1] + s;
        else if (vec[x][i] + vec[y][s - 1] + 1 < mx) ans += mx * s;
        else
            ans += mx * (res + 1) + vec[x][i] * (s - res - 1) + (sum[y][s - 1] - sum[y][res]) + (s - res - 1);
    }
    return ans;
}
signed main()
{
    n = read ( ), m = read ( ), q = read ( );
    for (int i = 1, u, v; i <= m; i++)
    {
        u = read ( ), v = read ( );
        add_edge (u, v);
        add_edge (v, u);
    }
    for (int i = 1; i <= n; i++)
        if (!vis[i])
        {
            Dim = 0;
            dfs (i, 0, ++cnt);
            dim[cnt] = Dim;
        }
    memset (vis, 0, sizeof (vis));
    for (int i = 1; i <= n; i++) if (!vis[i]) dfs2 (i, 0, 0); // 换根
    for (int i = 1; i <= cnt; i++) sort (vec[i].begin (), vec[i].end ());
    for (int i = 1; i <= cnt; i++)
        for (int j = 0; j < vec[i].size (); j++)
            sum[i].pb ((j > 0 ? sum[i][sum[i].size () - 1] : 0) + vec[i][j]); // 前缀和，方便二分
    int Block = sqrt (n);
    for (int i = 1; i <= cnt; i++)
        if (siz[i] > Block) block[++bcnt] = i, from[i] = bcnt;
    for (int i = 1; i <= bcnt; i++) solve (i); // 根号分治 >= sqrt(n) 的点
    while (q--)
    {
        int x = read ( ), y = read ( );
        if (from[belong[x]] > from[belong[y]]) swap (x, y);
        if (belong[x] == belong[y]) printf ("-1\n");
        else if (f[from[belong[x]]][from[belong[y]]])
            printf ("%.6lf\n", double (f[from[belong[x]]][from[belong[y]]]) / double(siz[belong[x]] * siz[belong[y]]));
        else
        {
            if (siz[belong[x]] > siz[belong[y]]) swap (x, y);
            printf ("%.6lf\n", double(getans (belong[x], belong[y])) / double(siz[belong[x]] * siz[belong[y]]));
        }
    }
    return 0;
}
```

### 

---

## 作者：i207M (赞：3)

题意：

给定一个森林，求每次选择两棵树，求随机选择两个点把它们连起来，新树的直径的期望；

这个题的时间复杂度证明比较有意思；

方法是：预处理每棵树的直径，和每个点到树上的最远距离，并求出前缀和；

对于每个询问（记忆化）：

我们每次枚举sz较小的树上的点i
，显然和这个点连接之后，期望的直径为$\max(dis_i+1+dis_v,\max(diam))$所以一定是对于dis小的一部分点取diam，另一部分取disv；

分类讨论做好就行；

注意初始直径为两棵树的diam的max；

```
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<stack>
#include<bitset>
#include<deque>
using namespace std;
#define ll long long
// #define inf 0x3f3f3f3f
#define ri register int
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pi pair<int,int>
#define mem0(x) memset((x),0,sizeof (x))
#define mem1(x) memset((x),0x3f,sizeof (x))
il char gc() {
	static const int BS = 1 << 22;
	static unsigned char buf[BS], *st, *ed;
	if (st == ed) ed = buf + fread(st = buf, 1, BS, stdin);
	return st == ed ? EOF : *st++;
}
#define gc getchar
template<class T>void in(T &x) {
	x = 0;
	bool f = 0;
	char c = gc();
	while (c < '0' || c > '9') {
		if (c == '-') f = 1;
		c = gc();
	}
	while ('0' <= c && c <= '9') {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = gc();
	}
	if (f) x = -x;
}
#undef gc
#define pb push_back
#define N 100010
#define M N<<1
#define int ll
int v[M], nx[M];
int cnt, head[N];
il void add(int uu, int vv) {
	v[++cnt] = vv, nx[cnt] = head[uu];
	head[uu] = cnt;
}
int n, m, cntq;
int bel[N], cur;
vector<int>sum[N];
void dfs(int x, int k) {
	bel[x] = k;
	for (ri i = head[x]; i; i = nx[i])
		if (!bel[v[i]]) dfs(v[i], k);
}
pi q[N];
int hd, tl;
int vis[N], cnv;
int diam[N];
pi getd(int k, int st) {
	++cnv;
	int mxd = 0, mxk = st;
	hd = 1, tl = 0;
	vis[st] = cnv;
	q[++tl] = mp(st, 0);
	while (hd <= tl) {
		pi x = q[hd++];
		if (x.se > mxd) mxd = x.se, mxk = x.fi;
		for (ri i = head[x.fi]; i; i = nx[i]) {
			if (vis[v[i]] == cnv) continue;
			vis[v[i]] = cnv;
			q[++tl] = mp(v[i], x.se + 1);
		}
	}
	++cnv;
	hd = 1, tl = 0;
	vis[mxk] = cnv;
	q[++tl] = mp(mxk, 0);
	int lst = mxk;
	mxd = 0;
	while (hd <= tl) {
		pi x = q[hd++];
		if (x.se > mxd) mxd = x.se, mxk = x.fi;
		for (ri i = head[x.fi]; i; i = nx[i]) {
			if (vis[v[i]] == cnv) continue;
			vis[v[i]] = cnv;
			q[++tl] = mp(v[i], x.se + 1);
		}
	}
	diam[k] = mxd;
	return mp(lst, mxk);
}
int dis[N];
vector<int>hv[N];
vector<int>sumlen[N];
void getlen(int k, pi st) {
	++cnv;
	hd = 1, tl = 0;
	vis[st.fi] = cnv;
	q[++tl] = mp(st.fi, 0);
	while (hd <= tl) {
		pi t = q[hd++];
		hv[k].pb(t.fi);
		dis[t.fi] = max(t.se, dis[t.fi]);
		for (ri i = head[t.fi]; i; i = nx[i]) {
			if (vis[v[i]] == cnv) continue;
			vis[v[i]] = cnv;
			q[++tl] = mp(v[i], t.se + 1);
		}
	}
	++cnv;
	hd = 1, tl = 0;
	vis[st.se] = cnv;
	q[++tl] = mp(st.se, 0);
	int mx = 0;
	while (hd <= tl) {
		pi t = q[hd++];
		dis[t.fi] = max(t.se, dis[t.fi]);
		mx = max(dis[t.fi], mx);
		for (ri i = head[t.fi]; i; i = nx[i]) {
			if (vis[v[i]] == cnv) continue;
			vis[v[i]] = cnv;
			q[++tl] = mp(v[i], t.se + 1);
		}
	}
	sum[k].resize(mx + 1);
	sumlen[k].resize(mx + 1);
	for (ri i = 0; i < (int)hv[k].size(); ++i) {
		++sum[k][dis[hv[k][i]]];
	}
	for (ri i = 1; i <= mx; ++i) {
		sumlen[k][i] = sum[k][i] * i + sumlen[k][i - 1];
		sum[k][i] += sum[k][i - 1];
	}
}
map<pi, double>rem;
double sol(int x, int y) {
	if (rem.count(mp(x, y))) return rem[mp(x, y)];
	int res = 0;
	int mxd = max(diam[x], diam[y]);
	for (ri i = 0; i < (int)hv[x].size(); ++i) {
		if ((int)sum[y].size() + dis[hv[x][i]] <= mxd) {
			res += mxd * (int)hv[y].size();
		}
		else {
			if (mxd - dis[hv[x][i]] - 1 < 0) {
				res += (dis[hv[x][i]] + 1) * ((int)hv[y].size()) + sumlen[y][sum[y].size() - 1];
			}
			else {
				res += mxd * sum[y][mxd - dis[hv[x][i]] - 1];
				res += (dis[hv[x][i]] + 1) * ((int)hv[y].size() - sum[y][mxd - dis[hv[x][i]] - 1]) + (sumlen[y][sum[y].size() - 1] - sumlen[y][mxd - dis[hv[x][i]] - 1]);
			}
		}
	}
	double tmp = (double)res / (hv[x].size() * hv[y].size());
	rem[mp(x, y)] = tmp;
	return tmp;
}
signed main() {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
#endif
	in(n), in(m), in(cntq);
	int a, b;
	for (ri i = 1; i <= m; ++i) {
		in(a), in(b);
		add(a, b), add(b, a);
	}
	for (ri i = 1; i <= n; ++i)
		if (!bel[i]) {
			dfs(i, ++cur);
			getlen(cur, getd(cur, i));
		}
	while (cntq--) {
		in(a), in(b);
		if (bel[a] == bel[b]) {
			puts("-1");
			continue;
		}
		if (hv[bel[a]].size() > hv[bel[b]].size() || (hv[bel[a]].size() == hv[bel[b]].size() && bel[a] > bel[b])) swap(a, b);
		printf("%.10f\n", sol(bel[a], bel[b]));
	}
	return 0;
}
```

---

## 作者：SudoXue (赞：1)

[更好的阅读体验](https://www.cnblogs.com/xueruhao/p/18990015)

集训习题。特别地，让我们膜拜一下教练 [zmwang](https://www.luogu.com.cn/user/33653)。

题目要求在给定森林上回答多次随机连边后直径期望的询问。若把询问点分别所在的两棵树记为 $V$ 与 $U$，随机等概率选取 $a\in V$、$b\in U$ 后加上一条边 $a-b$。若两点本来同属一棵树，则不会形成树结构，答案固定 $-1$。否则加边后得到一棵新树，其直径满足
$D_{\text{new}}=\max\bigl(D_V,D_U,1+e_a+e_b\bigr)$，
这里 $D_V,D_U$ 是两棵原树的直径，$e_x$ 表示顶点 $x$ 的偏心距（到两端点的距离最大值）。

对单棵树先做两遍广搜，任选一点做第一次 BFS 得到最远端点 $p$，以 $p$ 再来一次 BFS 得到另一端点 $q$ 和直径 $D$，接着把第三次 BFS 换成简单地在第二遍得到的最短路树上回溯就能算出所有顶点到 $p,q$ 的距离。于是偏心距 $e_x=\max(\text{dist}(x,p),\text{dist}(x,q))$ 可以 $O(n)$ 求完。把这些 $e_x$ 排序后连同前缀和保存在全局数组，顺带记录节点数 $s$ 与直径 $D$。

一次询问若涉及两棵不同的树，只需计算

$$
\mathbb{E}[D_{\text{new}}]=
\frac{\displaystyle\sum_{a\in V}\sum_{b\in U}\max\bigl(D_V,D_U,1+e_a+e_b\bigr)}
{|V|\cdot|U|}
$$

设 $D_{\max}=\max(D_V,D_U)$。为了快速累加，把较小的那棵树记为 $A$，较大的记为 $B$。遍历 $A$ 中每个 $e_a$ 时，在 $B$ 的有序偏心距数组里二分出最后一个满足 $e_b\le D_{\max}-1-e_a$ 的位置，其之前的 $\ell$ 个点与 $e_a$ 搭配时 $\max$ 恰好取 $D_{\max}$，贡献 $\ell\cdot D_{\max}$。后面的部分利用前缀和一次性求出 $\sum(1+e_a+e_b)$。这轮复杂度 $O(|A|\log|B|)$。

因为不同树对总共不会超过 $\sqrt n$ 级别，所有未缓存的树对最多触发同阶复杂度的真正计算，随后将结果以键 $\text{key}=id_1\cdot N+id_2$ 存进哈希表，再遇到同一对树即可 $O(1)$ 取值，整体复杂度摊成 $O(n\sqrt n+q\log n)$。

[link](https://codeforces.com/contest/804/submission/329307767)

---

## 作者：piggy123 (赞：0)

补充一种解法，首先前面用换根预处理出最远点对不变。

询问的时候开个 map ，记录一下第 $i$ 个连通块与第 $j$ 个连通块是否被计算过，如果有则直接输出，否则选择小的一方暴力。

这种写法实际上是隐式的根号分治，所以复杂度不变。考虑证明：对于任何一个大于 $\sqrt{n}$ 的连通块，他作为 $\min$ 出现只会有 $\sqrt{n}$ 次，对于小于 $\sqrt{n}$ 的，出现多少次都没关系，于是这个复杂度就是 $\Theta(n\sqrt{n})$ 的。

代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;

ll dp[200005],secdp[200005],mxid[200005],dp2[200005],a[200005],vis[200005],zz[200005],tot=0;
vector<ll> vct[200005];
vector<ll> far[200005];
vector<ll> sm[200005];
map<pair<ll,ll>,double> mem;

void dfs(ll root,ll fa){
	vis[root]=tot;
	for (ll i:vct[root]){
		if (i!=fa){
			dfs(i,root);
			if (dp[i]+1>=dp[root])secdp[root]=dp[root],dp[root]=dp[i]+1,mxid[root]=i;
			else if (dp[i]+1>=secdp[root])secdp[root]=dp[i]+1;
		}
	}
}

void dfs2(ll root,ll fa){
	a[root]=max(dp[root],dp2[root]);
	far[tot].push_back(a[root]);
	zz[tot]=max(zz[tot],dp[root]+dp2[root]);
	for (ll i:vct[root]){
		if (i!=fa){
			dp2[i]=max(dp2[root]+1,(mxid[root]==i?secdp[root]+1:dp[root]+1));
			dfs2(i,root);
		}
	}
}

int main(){
	ll n,m,q;
	cin>> n;
	cin >> m>> q;
	for (ll i=1;i<=m;i++){
		ll u,v;
		cin>> u >>v;
		vct[u].push_back(v);
		vct[v].push_back(u);
	}
	ll zj=0;
	for (ll i=1;i<=n;i++){
		if (!vis[i]){
			tot++;
			dfs(i,0);
			dfs2(i,0);
			sort(far[tot].begin(),far[tot].end());
			sm[tot].push_back(far[tot][0]);
			for (ll i=1;i<far[tot].size();i++){
				sm[tot].push_back(sm[tot][i-1]+far[tot][i]);
			}
		}
	} 
	cout<<fixed<<setprecision(10);
	for (ll i=1;i<=q;i++){
		ll u,v;
		cin >> u >> v;
		if (vis[u]==vis[v]){
			cout<<"-1\n";
		}else if (mem[{vis[u],vis[v]}]){
			cout<< mem[{vis[u],vis[v]}] << endl;
		}else {
			ll ans=0;
			ll zj=max(zz[vis[u]],zz[vis[v]]);
			if (far[vis[u]].size()<far[vis[v]].size()){
				for (ll i:far[vis[u]]){
					ll cnt=upper_bound(far[vis[v]].begin(),far[vis[v]].end(),zj-i-1)-far[vis[v]].begin()-1;
					if (cnt<0){
						ans+=sm[vis[v]][far[vis[v]].size()-1]+(i+1)*far[vis[v]].size();
					}else{
						ans+=sm[vis[v]][far[vis[v]].size()-1]-sm[vis[v]][cnt]+(i+1)*(far[vis[v]].size()-cnt-1)+zj*(cnt+1);
					}
				}
			}else{
				for (ll i:far[vis[v]]){
					ll cnt=upper_bound(far[vis[u]].begin(),far[vis[u]].end(),zj-i-1)-far[vis[u]].begin()-1;
					if (cnt<0){
						ans+=sm[vis[u]][far[vis[u]].size()-1]+(i+1)*far[vis[u]].size();
					}else{
						ans+=sm[vis[u]][far[vis[u]].size()-1]-sm[vis[u]][cnt]+(i+1)*(far[vis[u]].size()-cnt-1)+zj*(cnt+1);
					}
				}
			}
			mem[{vis[u],vis[v]}]=mem[{vis[v],vis[u]}]=ans*1.0/(far[vis[u]].size()*far[vis[v]].size());
			cout<< ans*1.0/(far[vis[u]].size()*far[vis[v]].size()) << endl;
		}
	}
	return 0;
}
```


---

## 作者：OtoriEmu (赞：0)

标题是因为写这道题的时候在听。

首先根据树的性质，一个点到树中最远的距离可以通过直径得出。具体的，如果直径为 $(u,v)$ 这条链，那么点 $c$ 到树中的最远距离即为 $\max(\operatorname{dis}(u,c),\operatorname{dis}(v,c))$。这个性质的实际运用是两次 DFS 找到树的直径，当然在这题中有更直接的运用。

那么对于每一棵树都线性求出它们中的所有点到树中最远的距离，记为 $p_1,p_2,\cdots ,p_n$。现在连接两棵树，假设连接到了 $u,v$，那么直径即为 $\max(d_1,d_2,p_u+p_v+1)$（其中 $d_1$ 表示第一棵树原来的直径，$d_2$ 同理）。

这个取 $\max$ 不太合理。先考虑一次查询，将子树里的点按 $p$ 值从小到大排序，这样就可以用双指针解决问题，贡献拆算比较简单，不再赘述。

但是总共有 $q$ 次询问。加上两个简单的优化就可以做到 $O(n \sqrt n \log n + q \sqrt n \log n)$：

1. 记忆化，即对相同的两棵子树，算出答案并记录（使用 `map`）；   
2. 双指针的时候指针暴力移动树大小小的那个，另外一个指针应该使用二分查找。

具体的复杂度分析可以这样考虑：树大小不小于 $O(\sqrt n)$ 的总共只有 $O(\sqrt n)$ 个，这样就只有 $O(n)$ 对本质不同的询问，暴力做并记忆化就是 $O(n \sqrt n)$ 或者 $O(n \sqrt n \log n)$；对于两个小于 $O(\sqrt n)$ 的树，暴力做就是 $O(q \sqrt n)$ 或者 $O(q \sqrt n \log n)$ 的；小块对大块可能产生很多组不同的询问，注意到小块大小只有 $O(\sqrt n)$，那么另外一个树可以二分处理来平衡复杂度。

可是 emu 在写这个题的时候忘记二分平衡复杂度了！可是还是过了，可见这个常数之小 ×

那么，只有一份复杂度错误的参考实现。改成二分并不困难，那就不改了。[评测链接](https://codeforces.com/contest/804/submission/176147268)，可见实际上代码并不长。

---

