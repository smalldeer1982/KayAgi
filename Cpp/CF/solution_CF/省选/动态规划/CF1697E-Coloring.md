# Coloring

## 题目描述

You are given $ n $ points on the plane, the coordinates of the $ i $ -th point are $ (x_i, y_i) $ . No two points have the same coordinates.

The distance between points $ i $ and $ j $ is defined as $ d(i,j) = |x_i - x_j| + |y_i - y_j| $ .

For each point, you have to choose a color, represented by an integer from $ 1 $ to $ n $ . For every ordered triple of different points $ (a,b,c) $ , the following constraints should be met:

- if $ a $ , $ b $ and $ c $ have the same color, then $ d(a,b) = d(a,c) = d(b,c) $ ;
- if $ a $ and $ b $ have the same color, and the color of $ c $ is different from the color of $ a $ , then $ d(a,b) < d(a,c) $ and $ d(a,b) < d(b,c) $ .

Calculate the number of different ways to choose the colors that meet these constraints.

## 说明/提示

In the first test, the following ways to choose the colors are suitable:

- $ [1, 1, 1] $ ;
- $ [2, 2, 2] $ ;
- $ [3, 3, 3] $ ;
- $ [1, 2, 3] $ ;
- $ [1, 3, 2] $ ;
- $ [2, 1, 3] $ ;
- $ [2, 3, 1] $ ;
- $ [3, 1, 2] $ ;
- $ [3, 2, 1] $ .

## 样例 #1

### 输入

```
3
1 0
3 0
2 1```

### 输出

```
9```

## 样例 #2

### 输入

```
5
1 2
2 4
3 4
4 4
1 3```

### 输出

```
240```

## 样例 #3

### 输入

```
4
1 0
3 0
2 1
2 0```

### 输出

```
24```

# 题解

## 作者：绝顶我为峰 (赞：8)

从条件入手，考虑如果两个点可以染成同色会是什么情况。

根据第二条限制，不难发现点对 $(x,y)$ 可以染成同色时 $x,y$ 互为对方距离最近的点。

但最近的点可能有多个，第一条限制告诉我们这时应该把这些点放在一起，但这样的连通块不一定是合法的，加入一个点时需要满足已经加入的点全部是新加入点的最近点才能染成同一种颜色。

显然可以染成同色的点被分成了若干互不相交的连通块，那么我们可以预处理出来每个点的最近点集合，然后从每个点开始 dfs，记点 $i$ 的距离最近点的距离是 $minn_i$，那么我们 dfs 时只访问 $minn_j=minn_i$ 的相邻点，把这样的点加入连通块中，并且判断这个连通块是否合法即可。如果合法，我们用并查集把他们连起来，表示这些点要么两两不同色，要么全部同色。

接下来考虑怎样计算答案，记 $dp_i$ 表示用 $i$ 种颜色讲整个图染色的合法方案数，那么这就是一个简单 01 背包，每个连通块看做一个物品，可以产生连通块大小或 $1$ 的贡献，这样做完背包之后答案就是 $\sum\limits_{i=1}^nn^{\underline i}dp_i$，其中 $n^{\underline i}=\prod\limits_{j=1}^in-j+1$。

时间复杂度 $O(n^2)$。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
const int mod=998244353;
int n,minn[101],bin[101],s[101],dp[101],f[101],fac[101],inv[101],ans;
pair<int,int> a[101];
vector<int> v[101],tmp;
bool vis[101],flag;
inline int pw(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1)
            res=1ll*res*a%mod;
        b>>=1;
        a=1ll*a*a%mod;
    }
    return res;
}
inline int anc(int k)
{
    if(!bin[k])
        return k;
    return bin[k]=anc(bin[k]);
}
inline void link(int x,int y)
{
    x=anc(x);
    y=anc(y);
    if(x^y)
    {
        bin[y]=x;
        s[x]+=s[y];
    }
}
inline int dis(int x,int y)
{
    return abs(a[x].first-a[y].first)+abs(a[x].second-a[y].second);
}
inline void dfs(int k,int val)
{
    tmp.emplace_back(k);
    vis[k]=1;
    for(int i:v[k])
    {
        if(minn[i]<val)
            flag=0;
        if(vis[i])
            continue;
        for(auto j:tmp)
            if(find(v[i].begin(),v[i].end(),j)==v[i].end())
            {
                flag=0;
                break;
            }
        if(minn[i]==val)
            dfs(i,val);
    }
}
inline int c(int x,int y)
{
    return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int main()
{
    cin>>n;
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;++i)
    {
        cin>>a[i].first>>a[i].second;
        s[i]=1;
        fac[i]=1ll*fac[i-1]*i%mod;
    }
    inv[n]=pw(fac[n],mod-2);
    for(int i=n-1;i>=1;--i)
        inv[i]=1ll*inv[i+1]*(i+1)%mod;
    for(int i=1;i<=n;++i)
    {
        minn[i]=1e9;
        for(int j=1;j<=n;++j)
            if(i!=j)
            {
                int val=dis(i,j);
                if(val<minn[i])
                {
                    minn[i]=val;
                    v[i].clear();
                    v[i].emplace_back(j);
                }
                else if(val==minn[i])
                    v[i].emplace_back(j);
            }
    }
    for(int i=1;i<=n;++i)
        if(!vis[i])
        {
            tmp.clear();
            flag=1;
            dfs(i,minn[i]);
            if(flag)
                for(auto j:tmp)
                    link(i,j);
        }
    dp[0]=1;
    for(int i=1;i<=n;++i)
        if(anc(i)==i)
        {
            for(int j=0;j<=n;++j)
            {
                f[j]=dp[j];
                dp[j]=0;
            }
            for(int j=n;j>=s[i];--j)
                dp[j]=(dp[j]+f[j-s[i]])%mod;
            if(s[i]^1)
                for(int j=n;j>=1;--j)
                    dp[j]=(dp[j]+f[j-1])%mod;
        }
    for(int i=1;i<=n;++i)
        ans=(ans+1ll*c(n,i)*fac[i]%mod*dp[i]%mod)%mod;
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：lingfunny (赞：7)

首先读懂题意：两个点可以同色当且仅当他们互为最近点。此外，一堆可同色点要么都同色，要么都都不相同，读者自证不难。

可以发现，如果两点的距离定义为曼哈顿距离，那么最多可以让四个点两两互为最近点。四个点形如 $(d,0),(-d,0),(0,d),(0,-d)$。

不难理解，因为钦定两个点后，分别以两点为圆心，距离为半径作出曼哈顿圆，最多只有两个交点。

不过这不重要，有一种更高效的找可同色集做法。首先不难想到把每个点向其最近点连接一条有向边，那么当一堆点可同色时，当且仅当它们构成了完全图。反证，读者自证不难。

这时候不难想到正解：对于每个点，找出它能到的所有点，判断这些点两两之间是否都有边。时间复杂度 $O(n^3)$。

找到一堆同色点集后，设 $a_i$ 为第 $i$ 个同色点集的大小。

不妨设 $f_{i,k}$ 表示前 $i$ 个同色点集合，用了 $k$ 种颜色的方案数，不难写出 dp 方程：
$$
f_{i,k}=[a_i>1](n-k+1)f_{i-1,k-1}+\binom{n-k+a_i}{a_i}a_i!f_{i-1,k-a_i}
$$
记总共有 $m$ 个同色点集，答案为 $\sum\limits_{i=1}^nf_{m,i}$。

相信大家都有根据 dp 方程写出代码的能力， 这里就不贴代码了。

upd：还是贴贴，虽然比较丑。

```cpp
// Problem: E. Coloring
// From: Codeforces - Educational Codeforces Round 130 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1697/problem/E
// Time: 2022-06-12 22:35
// Author: lingfunny

#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mod = 998244353, mxn = 205;

int n, md[mxn], d[mxn][mxn], jc[mxn], ijc[mxn], vis[mxn], cur, a[mxn], cnt, f[mxn];
vector <int> G[mxn], res;
struct node { int x, y; } nd[mxn];
int mul() { return 1; }
template <typename... A>
int mul(int x, A... a) { return (LL)x*mul(a...)%mod; }
inline int qpow(int x, int k) {
	int res = 1; x %= mod;
	for(; k; k >>= 1, x = mul(x, x)) if(k&1) res = mul(res, x);
	return res;
}
bool dfs(int u) {
	vis[u] = cur; res.push_back(u);
	int f = 1;
	for(int v: G[u])
	if(!vis[v]) f &= dfs(v);
	else if(vis[v] != vis[u]) f = 0;
	return f;
}

signed main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d%d", &nd[i].x, &nd[i].y);
	jc[0] = 1; for(int i = 1; i < mxn; ++i) jc[i] = mul(jc[i-1], i);
	ijc[mxn-1] = qpow(jc[mxn-1], mod-2); for(int i = mxn-2; ~i; --i) ijc[i] = mul(ijc[i+1], i+1);
	for(int i = 1; md[i] = 1e9, i <= n; ++i) for(int j = 1; j <= n; ++j) if(i != j) {
		d[i][j] = d[j][i] = abs(nd[i].x - nd[j].x) + abs(nd[i].y - nd[j].y);
		md[i] = min(md[i], d[i][j]);
	}
	for(int i = 1; i <= n; ++i) for(int j = 1; j <= n; ++j) if(i != j && md[i] == d[i][j]) G[i].push_back(j);
	for(int i = 1; i <= n; ++i) if(!vis[i]) {
		++cur; vector <int> ().swap(res); int F = dfs(i);
		for(int x: res) for(int y: res) if(F && x != y && (d[x][y] != md[x] || d[x][y] != md[y])) F = 0;
		if(!F) {
			for(int x: res) vis[x] = 0;
			vis[i] = 1; a[++cnt] = 1;
		} else a[++cnt] = res.size();
	}
	for(int i = 1; i <= cnt; ++i) scanf("%d", a+i);
	f[0] = 1; int ans = 0;
	for(int i = 1; i <= cnt; ++i, f[0] = 0) for(int k = n; k >= 1; --k)
	f[k] = (mul(a[i]>1, n-k+1, f[k-1]) + (k >= a[i] ? mul(jc[n-k+a[i]], ijc[n-k], f[k-a[i]]) : 0))%mod;
	for(int i = 1; i <= n; ++i) (ans += f[i]) %= mod;
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Miraik (赞：7)

这有 \*2400 ？

乍一看似乎不太好做，但是由于点的坐标互不相同，且要求点集中两两曼哈顿距离都相等，我们可以发现点集大小定然很小。

我们稍加思（da）考（biao），发现点集大小必然不超过 $4$。但其实这是很显然的，因为假设我们在平面上有两个点 $a$ 和 $b$，分别以相同的曼哈顿距离 $l$ 作正方形，最多只有两个交点，因此点集大小最多为 $2+2=4$。

再考虑题目中的另一个条件：点集内的点的距离严格小于点集内的点与点集外的点的任意距离。

从这里我们可以得出：所有合法点集之间不可能有交。

这也是显然的，因为如果有交，那么对于一个交点，它在两个点集中必然分别与非交点的距离相等，不符合严格小于的条件。

发现这个后，我们可以尝试去统计一下所有大小为 $2,3,4$ 的点集个数，然后就能计算答案了。

这也很好维护，我们只需要提前求出每个点与其它点的最小距离 $d_i$，最小距离点的数组 $g_i$。由于点集大小最多为 $4$，所以这个数组第二维只需要开到 $5$ 即可，当数组大小达到 $4$ 时无论如何它都不会对答案有贡献。

然后我们就可以用暴力的方式求出所有合法的点集了：

```cpp
for(int i=1;i<=n;i++){
		if(mncnt[i]==4 || c[i]) continue; //最小距离点超过3个，或者已经统计过这个点，跳过
		bool ok=1;
		for(int j=1;j<=mncnt[i];j++){
			if(mn[g[i][j]]^mn[i] || mncnt[g[i][j]]^mncnt[i]) ok=0;
            // 最小距离不同，或者最小距离点个数不同，显然不会是在一个点集里
			for(int k=1;k<=mncnt[g[i][j]];k++)
			    if(g[g[i][j]][k]^i && w[i][g[g[i][j]][k]]^mn[i]) ok=0;
                // g[i][j] 所连接的最小距离点并不是 i 所连接的最小距离点，也不可行
		}
		if(ok){
			t[mncnt[i]+1]++; //算上 i，点集大小为 cnt+1 的个数增加
			c[i]=1;
			for(int j=1;j<=mncnt[i];j++) c[g[i][j]]=1; //打上统计标记
		}
	}
```

怎么统计答案呢？由于 $n$ 很小，我们可以直接暴力枚举选取几个大小为 $2,3,4$ 的点集，设为 $i,j,k$，那么就剩下 $l=n-2\times i-3\times j -4 \times k$ 个大小为 $1$ 的点集，其对答案的贡献显然为：

${cnt_2 \choose i} \times {cnt_3 \choose j} \times {cnt_4 \choose k} \times {n \choose i+j+k+l} \times (i+j+k+l)!$

其中 ${n \choose i+j+k+l} \times (i+j+k+l)!$ 是因为我要在 $n$ 种颜色中选出 $i+j+k+l$ 种染色，然后对于每种选择方案都有 $(i+j+k+l)!$ 种排列方式。

至此我们解决了这个问题，时间复杂度 $O(n^3)$（实际上由于 $cnt_2\times2+cnt_3\times3+cnt_4\times4 \le n$，其效率是远高于 $O(n^3)$的，在 $n\le 2000$ 下都能轻松跑过）

[完整代码](https://codeforces.com/contest/1697/submission/170844072)

---

## 作者：ExplodingKonjac (赞：3)

**[【原题链接】](https://www.luogu.com.cn/problem/CF1697E)**

## 题目分析

考虑那些可以染上同种颜色的大小大于 $2$ 的点集。如果我们钦定两个点 $i,j$ 染同一种颜色，那么我们就可以相应地推出这些东西：

1. 不能存在点 $k$ 使得 $\operatorname{dist}(i,k)<\operatorname{dist}(i,j)$ 或 $\operatorname{dist}(j,k)<\operatorname{dist}(i,j)$。

2. 对于所有 $k$ 使得 $\operatorname{dist}(i,k)=\operatorname{dist}(i,j)$ 或 $\operatorname{dist}(j,k)=\operatorname{dist}(i,j)$，$k$ 也要染上相同的颜色。

这样我们就可以找到一个**可能**可以染上同一种颜色的点集。再经过判断之后就可以知道所有可以染上同一种颜色的点集。我们称这种点集为合法点集。

发现一件事情：合法点集不可能有交。证明如下：

* 不妨假设一个点在两个合法点集内，这两个点集对应的那个相同的曼哈顿距离分别是 $d_1,d_2$；

* 如果 $d_1=d_2$，那么显然这两个点集不会同时存在，它们的颜色应该相同，矛盾；

* 如果 $d_1\neq d_2$，那么与上文中的推论 $1$ 相矛盾。

所以我们可以 $O(n^2)$ 枚举所有点对 $(i,j)$，扩展出整个点集或者判断不合法，然后再 $O(n^2)$ 最终判断这个点集是否合法。因为 $(i,j)$ 一定是互相曼哈顿距离最小的点对，所以最终判断只会进行 $O(n)$ 次。于是就可以 $O(n^3)$ 找到所有的合法点集。

如何计数呢？一个合法点集可以染相同的颜色，也可以都染不同的颜色。假设我们钦定其中一些合法点集必须相同，这些点集的大小分别为 $a_1,a_2,\dots,a_k$，那么答案可以表示为：

$$
ans=\sum_{a_1,a_2,\dots,a_k}k!{n\choose k}\cdot\left(n-\sum a_i\right)!{n-k\choose n-\sum a_i}
$$

求和的东西分别是：枚举钦定的点集的颜色和顺序，剩余的单点的颜色和顺序。

这个东西看上去不是很好处理，但是仔细思考后，发现后面的那一坨玩意只跟选出点集的大小有关。然后再手玩几个数据便会惊奇地发现：合法点集的大小不超过 $4$。最大的情况如下图，可以发现不可能加入新的点：

![](https://cdn.luogu.com.cn/upload/image_hosting/1ovmivau.png)

然后就可以 $O(n^3)$ 枚举大小为 $2,3,4$ 的合法点集选了多少个。假设大小为 $2,3,4$ 分别共有 $m_2,m_3,m_4$ 个，你选了 $i,j,k$ 个，对答案的贡献就是下式（$P_n^m$ 表示 $m!{n\choose m}$），直接计算即可。

$$
{m_2\choose i}{m_3\choose j}{m_4\choose k}\cdot P_n^{i+j+k}\cdot P_{n-i-j-k}^{n-2i-3j-4k}
$$

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

/* 省略快读快写，即下面的 qin、qout */

template<int MOD>
class Modint
{
 private:
	int val;
	template<typename T> static T inverse(T a,T b)
		{ T x=0,y=1,t;for(;a;t=b/a,swap(a,b-=t*a),swap(y,x-=t*y));return x; }
	template<typename T> static T fix(T x)
		{ return (x%=MOD)<0?x+MOD:x; }
 public:
	Modint(): val(0){}
	template<typename T> Modint(const T &x): val(fix(x)){}
	inline int operator ()() { return val; }
	inline Modint &operator +=(const Modint &rhs)
		{ return (val+=rhs.val)>=MOD?val-=MOD:0,*this; }
	inline Modint &operator -=(const Modint &rhs)
		{ return (val-=rhs.val)<0?val+=MOD:0,*this; }
	inline Modint &operator *=(const Modint &rhs)
		{ return val=fix(1ll*val*rhs.val),*this; }
	inline Modint &operator /=(const Modint &rhs)
		{ return val=fix(1ll*val*inverse(rhs.val,MOD)),*this; }
	inline Modint inv()const
		{ return Modint(inverse(val,MOD)); }
	friend inline Modint operator +(const Modint &lhs,const Modint &rhs)
		{ return Modint(lhs)+=rhs; }
	friend inline Modint operator -(const Modint &lhs,const Modint &rhs)
		{ return Modint(lhs)-=rhs; }
	friend inline Modint operator *(const Modint &lhs,const Modint &rhs)
		{ return Modint(lhs)*=rhs; }
	friend inline Modint operator /(const Modint &lhs,const Modint &rhs)
		{ return Modint(lhs)/=rhs; }
	template<typename T> friend inline Modint qpow(Modint x,T y)
		{ Modint res(1);for(;y;x*=x,y>>=1)if(y&1)res*=x;return res; }
};
constexpr int MOD=998244353;
typedef Modint<MOD> Mint;

int n,cnt[10];
struct Point{ int x,y; }p[105];
bool vis[105],chk[105];
inline int dist(const Point &A,const Point &B)
	{ return abs(A.x-B.x)+abs(A.y-B.y); }
vector<int> findSameColor(int x)
{
	for(int i=1;i<=n;i++)
	{
		if(vis[i] || i==x) continue;
		int d=dist(p[x],p[i]);
		bool fl=false;
		for(int j=1;j<=n;j++)
			if(j!=x && j!=i && (dist(p[j],p[x])<d || dist(p[j],p[i])<d))
				{ fl=true;break; }
		if(fl) continue;
		vector<int> res{i,x};
		for(int j=1;j<=n;j++) chk[j]=false;
		chk[i]=chk[x]=true;
		for(int j=1;j<=n;j++)
			if(j!=x && j!=i && (dist(p[j],p[x])==d || dist(p[j],p[i])==d))
				res.push_back(j),chk[j]=true;
		for(auto &j: res) for(auto &k: res)
			if(j!=k && dist(p[j],p[k])!=d)
				{ fl=true;goto out_of_loop; }
		for(int j=1;j<=n;j++) for(auto &k: res)
			if(!chk[j] && dist(p[j],p[k])<=d)
				{ fl=true;goto out_of_loop; }
		out_of_loop:;
		if(fl) continue;
		return res;
	}
	return vector<int>();
}
Mint fac[105],inv[105];
inline Mint C(int r,int c)
	{ return r<c?0:fac[r]*inv[c]*inv[r-c]; }
inline Mint P(int r,int c)
	{ return r<c?0:fac[r]*inv[r-c]; }
int main()
{
	qin>>n;
	for(int i=1;i<=n;i++) qin>>p[i].x>>p[i].y;
	for(int i=1;i<=n;i++)
	{
		if(vis[i]) continue;
		vector<int> vec=findSameColor(i);
		if(vec.empty()) continue;
		for(auto &j: vec) vis[j]=true;
		cnt[vec.size()]++;
	}
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i;
	inv[n]=fac[n].inv();
	for(int i=n;i>=1;i--) inv[i-1]=inv[i]*i;
	Mint ans;
	for(int i=0;i<=cnt[2];i++)
		for(int j=0;j<=cnt[3];j++)
			for(int k=0;k<=cnt[4];k++)
				ans+=C(cnt[2],i)*C(cnt[3],j)*C(cnt[4],k)*P(n,i+j+k)*P(n-i-j-k,n-2*i-3*j-4*k);
	qout<<ans();
	return 0;
}
```


---

## 作者：ax_by_c (赞：1)

首先容易发现每个点要么单独染一种颜色要么和距离它最近的所有点染同一种颜色。

我们让每个点向所有距离它最近的点连边，此时每个点要么和所有出边相连的点选择同种颜色，要么作为孤点。

于是对于每个点，我们找出其所有出边相连的点以及它本身。若该点集的导出子图不是完全图，则该点只能是孤点，否则该点集中的点可以同色也可以全部孤点。

容易发现我们最终关心的只有颜色种数，所以我们可以通过 dp 求出每个颜色种数出现的方案数。最后算排列数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const ll mod=998244353;
const int N=105;
const int inf=1e9;
int n;
pii a[N];
vector<int>g[N];
int dis(pii x,pii y){
	return abs(x.first-y.first)+abs(x.second-y.second);
}
bitset<N>mk,vis;
vector<int>sz;
void check(int u){
	vector<int>pos;
	pos.push_back(u);
	for(auto v:g[u]){
		pos.push_back(v);
	}
	vis=0;
	for(auto v:pos){
		vis[v]=1;
	}
	mk[u]=1;
	for(auto v:pos){
		if(g[v].size()!=pos.size()-1){
			sz.push_back(1);
			return ;
		}
		for(auto it:g[v]){
			if(!vis[it]){
				sz.push_back(1);
				return ;
			}
		}
	}
	for(auto v:pos){
		mk[v]=1;
	}
	sz.push_back(pos.size());
}
ll f[N];
ll fac[N],inv[N];
ll ksm(ll a,ll b,ll p){
	a=a%p;
	ll r=1;
	while(b){
		if(b&1){
			r=r*a%p;
		}
		a=a*a%p;
		b>>=1;
	}
	return r%p;
}
void Init(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	inv[n]=ksm(fac[n],mod-2,mod);
	for(int i=n;i>=1;i--){
		inv[i-1]=inv[i]*i%mod;
	}
}
ll C(int n,int m){
	if(n<m)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	for(int i=1;i<=n;i++){
		int mn=inf;
		for(int j=1;j<=n;j++){
			if(j!=i){
				mn=min(mn,dis(a[j],a[i]));
			}
		}
		for(int j=1;j<=n;j++){
			if(j!=i){
				if(dis(a[j],a[i])==mn){
					g[i].push_back(j);
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!mk[i]){
			check(i);
		}
	}
	f[0]=1;
	for(auto x:sz){
		for(int i=n;i>=0;i--){
			f[i]=0;
			if(i>=1){
				f[i]=f[i-1];
			}
			if(i>=x&&x!=1){
				f[i]=(f[i]+f[i-x])%mod;
			}
		}
	}
	Init(n);
	ll ans=0;
	for(int i=1;i<=n;i++){
		ans=(ans+f[i]*C(n,i)%mod*fac[i]%mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

你说的对，但是为什么要分析几何性质？

~~但是我的第一反应也是分析几何性质，转切比雪夫距离之后发现了一些事情，但是好像不重要。~~

考虑每个点 $u$，离他最近的点构成的集合为 $S$，其他点构成的集合为 $T$，则 $S \cup T = \{1,2,\dots,n\} / \{u\}$，$S \cap T = \varnothing$。

显然，最后和 $u$ 同色的集合，要么是 $S$，要么是空集。能是 $S$ 的充分必要条件就是 $S$ 中其他每个元素最近点的集合都是 $S \cup \{u\}$ 在扣掉这个元素。

于是可以把所有点分成若干个集合，每个集合要么颜色全部相等，要么互不相同。使用 $\rm DP$ 计算最终颜色数为 $c$ 的不同情况总数即可。

这时候结合一下几何性质，复杂度为 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100+10,MOD=998244353;
int n,mul=1,x[MAXN],y[MAXN],cov[MAXN],f[MAXN],g[MAXN];
set<int> cl[MAXN]; vector<int> lth;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; ffor(i,1,n) cin>>x[i]>>y[i];
	ffor(i,1,n) {
		vector<pair<int,int>> vc;
		ffor(j,1,n) if(i!=j) vc.push_back({abs(x[i]-x[j])+abs(y[i]-y[j]),j});
		sort(vc.begin(),vc.end());
		int mn=vc[0].first;
		for(auto pr:vc) if(pr.first==mn) cl[i].insert(pr.second);
		cl[i].insert(i);
	}
	ffor(i,1,n) if(!cov[i]) {
		int flg=0;
		for(auto id:cl[i]) if(cl[i]!=cl[id]) flg=1;
		if(flg==1) lth.push_back(1);
		else {
			lth.push_back(cl[i].size());	
			for(auto id:cl[i]) cov[id]=1;
		}
	}
	f[0]=1;
	for(auto l:lth) {
		memset(g,0,sizeof(g));
		if(l!=1) ffor(j,l,n) g[j]=(g[j]+f[j-l])%MOD;
		ffor(j,1,n) g[j]=(g[j]+f[j-1])%MOD;	
		ffor(j,0,n) f[j]=g[j];
	}
	roff(i,n,1) mul=mul*i%MOD,ans=(ans+f[n-i+1]*mul)%MOD;
	cout<<ans;
	return 0;
}
```

---

## 作者：cwfxlh (赞：1)

# [CF1697E](https://www.luogu.com.cn/problem/CF1697E)

感觉洛谷和 CF 对这道题的评分都太高了。   

题目大意是说，让你给一个平面内的点集染色，满足相同颜色的点之间距离相等，并满足如果一种颜色的点不止一个，那么该种颜色中任意一个点的最近点与其均有相同颜色。要你给出方案数。  

首先可以想到一种平凡的方案，给所有的点染上不同的颜色。这一定是符合要求的。考虑在这个方案上做改动。  

如果扩充上述方案中某种颜色的点集 $S$，令上述方案中被染上这种颜色的点为 $P$，那么 $P$ 的所有最近点均要被染成相同的颜色，并且扩充出来的点集中，每个点的最近点集加上自己必须等于整个点集 $S$。   

在这个过程中我们可以发现，一个点是否进行扩充，可以确定一种同色点集（扩充不合法除外），并且有一个很明显的事实，不同同色点集互不相交。那么我们可以提前算出每一种同色点集 $S$，留下的点就是只能自己染一个颜色的点。同色点集的染色方案有两种，第一种就是自己染一个颜色，第二种就是把自身分解掉，每一个点染一个不同的颜色。由此可以 DP 出染 $i$ 种颜色的方案数，最后答案就是 $\sum dp_i\times A_n^i$。   

上代码：  

```cpp
#include<bits/stdc++.h>
#define MOD 998244353
#define int long long
using namespace std;
int n;
struct point{
	int X;
	int Y;
}P[1003];
vector<int> E[1003];//每个点的最近点集 
int mn[1003];//最小距离 
int dis(int A,int B){
	return abs(P[A].X-P[B].X)+abs(P[A].Y-P[B].Y);
}
int blk[1003],totb;//记录每一个同色点集的大小 
int stk[1003],tot,ans;
int f;
int mp[1003];
int dp[1003][1003],jc[1003],vis[1003];
int fstp(int X,int Y){
	int ret=1,bse=X;
	while(Y){
		if(Y&1)ret*=bse;
		bse*=bse;
		ret%=MOD;
		bse%=MOD;
		Y>>=1;
	}
	return ret;
}
signed main(){
	scanf("%lld",&n);
	jc[0]=1;
	for(int i=1;i<=1000;i++){
		jc[i]=jc[i-1]*i;
		jc[i]%=MOD;
	}
	for(int i=1;i<=n;i++)scanf("%lld%lld",&P[i].X,&P[i].Y);
	for(int i=1;i<=n;i++){
		mn[i]=-10;
		for(int j=1;j<=n;j++){
			if(j==i)continue;
			if(mn[i]<0||mn[i]>dis(i,j)){
				mn[i]=dis(i,j);
				E[i].clear();
			}
			if(mn[i]==dis(i,j)){
				E[i].push_back(j);
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		tot=0;
		tot++;
		stk[tot]=i;
		mp[i]=1;
		for(int j=0;j<E[i].size();j++){
			tot++;
			stk[tot]=E[i][j];
			mp[E[i][j]]=1;
		}
		f=1;
		for(int j=1;j<=tot;j++){
			if(E[stk[j]].size()!=tot-1)f=0;
			for(int u=0;u<E[stk[j]].size();u++){
				if(mp[E[stk[j]][u]]==0){
					f=0;
				}
			}
		}
		if(f){
			totb++;
			blk[totb]=tot;
			for(int i=1;i<=tot;i++)vis[stk[i]]=1;
		}
		for(int j=1;j<=tot;j++)mp[stk[j]]=0;
	}
	for(int i=1;i<=n;i++){
		if(vis[i]==0){
			totb++;
			blk[totb]=1;
		}
	}
	sort(blk+1,blk+totb+1);
	dp[1][1]=1;
	dp[1][blk[1]]=1;
	for(int i=2;i<=totb;i++){
		for(int j=1;j<=n;j++){
			dp[i][j]+=dp[i-1][j-1];
			if(blk[i]!=1&&j-blk[i]>=0)dp[i][j]+=dp[i-1][j-blk[i]];
			dp[i][j]%=MOD;
		}
	}
	for(int i=0;i<=n;i++){
		ans+=(dp[totb][i]*((jc[n]*fstp(jc[n-i],MOD-2))%MOD))%MOD;
		ans%=MOD;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：2022dyx (赞：0)

要先分析一下性质。由于同色点间的连接要求是最近点，因此先把每个点和其最近点连边，那么有相同颜色就要求一个连通块是一个完整的团且团中边权相等。因为不同连通块之间是独立的，因此可以直接预处理掉每个点能处于哪个颜色块中。在这样的约束条件下，一个颜色块要么全都染相同颜色要么全都染不同颜色，最终答案的系数只与用过的颜色个数有关，因此我们设 $dp_{i,j}$ 为考虑到第 $i$ 个颜色块，用了 $j$ 个颜色的方案数，转移就是 $dp_{i,j}=dp_{i-1,j-1}+[a_i\neq1]dp_{i-1,j-a_i}$，其中 $a_i$ 为第 $i$ 个颜色块的点数，统计答案时，有：
$$ans=\sum_{i=1}^n\binom{n}{i}i!\times dp_{m,i}$$
依预处理的实现精细与否，时间复杂度为 $O(n^2) $ 到 $O(n^3)$。

代码如下：
```
#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define file(x) freopen(#x ".in", "r", stdin); freopen(#x ".out", "w", stdout);
using namespace std;
constexpr int N = 1e2 + 5;
constexpr int mod = 998244353;
int n, mn[N], val[N], idx, dp[N][N], ans, fac[N], inv[N];
bool E[N][N];
bool vis[N];
vector <int> e[N];
struct Point { int x, y; } a[N];
int dis(int x, int y) { return abs(a[x].x - a[y].x) + abs(a[x].y - a[y].y); }
int pw(int x, int y) { return !y ? 1 : (y & 1 ? x : 1) * pw(x * x % mod, y >> 1) % mod;}
signed main() {
    cin.tie(0) -> sync_with_stdio(false); 
    cin >> n;
    fac[0] = inv[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod, inv[i] = pw(fac[i], mod - 2);
    for (int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
        if (i == j) continue;
        if (e[i].empty() || dis(i, j) < mn[i]) e[i].clear(), mn[i] = dis(i, j);
        if (dis(i, j) == mn[i]) e[i].pb(j);
    }
    for (int i = 1; i <= n; ++i) for (int j : e[i]) E[i][j] = true;
    for (int i = 1; i <= n; ++i) if (!vis[i]) {
        bool flg = true;
        for (int j : e[i]) if (e[j].size() != e[i].size() || vis[j] || !E[j][i]) flg = false;
        for (int j : e[i]) for (int k : e[i]) if (j != k && !E[j][k]) flg = false;
        if (!flg) { vis[i] = true; val[++idx] = 1; continue; }
        for (int j : e[i]) vis[j] = true;
        val[++idx] = e[i].size() + 1;
    }
    dp[0][0] = 1;
    for (int i = 1; i <= idx; ++i) for (int j = 1; j <= n; ++j) {
        dp[i][j] = dp[i - 1][j - 1];
        if (j >= val[i] && val[i] != 1) dp[i][j] = (dp[i][j] + dp[i - 1][j - val[i]]) % mod;
    }
    for (int i = 1; i <= n; ++i) ans = (ans + dp[idx][i] * fac[n] % mod * inv[n - i]) % mod;
    cout << ans << '\n';
}
```

---

