# 木

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tdpc/tasks/tdpc_tree

入力は以下の形式で標準入力から与えられる。

> $ N $ $ a_1\ b_1 $ $ ... $ $ a_{N-1}\ b_{N-1} $

 答えを一行に出力せよ。 ```

4
1 2
2 3
3 4
```

```

4
```

```

8
1 2
4 6
6 7
3 2
2 4
4 5
8 6
```

```

752
```

## 说明/提示

### Constraints

 頂点 1 から頂点 $ N $ までが紙が描かれている。すぬけ君は、頂点 $ a_i $ と頂点 $ b_i $ の間に辺を描き、木にすることにした。木を書いている途中で常に辺が連結になっているようにしたいとき、辺を描く順番は何通り考えられるか、mod 1,000,000,007 で求めよ。

- - - - - -

- $ 2\ <\ =\ N\ <\ =\ 1000 $
- $ 1\ <\ =\ a_i,\ b_i\ <\ =\ N $
- The input will represent a tree.

# 题解

## 作者：Cry_For_theMoon (赞：3)

[传送门](https://atcoder.jp/contests/tdpc/tasks/tdpc_tree)

好水啊（）

这个思路完全来自于 CF1540B Tree Arrays 赛场时的错误 DP 想法（）

考虑枚举第一条染色边 $<u,v>$，则树形如：
$$
subtree(u) \leftrightarrow u \leftrightarrow v \leftrightarrow subtree(v)
$$
~~莫名想到割边 qwq~~

那么考虑如果算出 $subtree(u)$ 和 $subtree(v)$ 内所有边的染色方案，则由于 $<u,v>$ 边第一个加入，组合答案即可。这里的组合和等会 dp 里的组合答案一样所以先不讲。

考虑设 $f(u)$ 为 $subtree(u)$ 染色的答案，$sz(u)$ 为 $subtree(u)$ 内的边数。注意这里 $u,v$ 和上面没有关系。

则 $f(u)$ 就是 $f(v) (v \in son(u))$ 的答案组合在一起。考虑各个 $v$ 之间相互独立，如果加入当前 $v$ 后共加入了 $sum$ 条边，则我们有  $\dbinom{sum}{sz[v]+1}$ 种（注意还有加上 $v$ 到父亲 $u$ 的连边）方案选择这颗 $subtree(v)$ 内的边还有边 $v\leftrightarrow u$ 的位置。所以初始令 $sum=0,f(u)=1$，每次加入一个儿子 $v$，就
$$
sum \leftarrow sum+sz[v]+1
$$
然后
$$
f(u) \leftarrow  f(u) \,\cdot \dbinom{sum}{sz[v]+1}\,\cdot f(v)
$$
最后组合枚举边两端点 $u,v$ 的答案同理，不再赘述。

```C++
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=1010,mod=1e9+7;
int n,u[MAXN],v[MAXN];
vector<int>E[MAXN];
ll C[MAXN][MAXN],f[MAXN],sz[MAXN];
ll vis[MAXN],ans,ret;
void dfs(int u){
	sz[u]=0;vis[u]=f[u]=1;
	for(vit it=E[u].begin();it!=E[u].end();it++){int v=*it;
		if(vis[v])continue;
		dfs(v);
		sz[u]=(sz[u]+sz[v]+1);
	}
}
void dp(int u){
	vis[u]=1;
	ll sum=0; //总边数 
	for(vit it=E[u].begin();it!=E[u].end();it++){int v=*it;
		if(vis[v])continue;
		dp(v);
		sum=(sum+sz[v]+1); 
		f[u]=f[u]*C[sum][sz[v]+1]%mod*f[v]%mod;  
	}
}
int main(){
	cin>>n;
	rep(i,1,n-1){
		cin>>u[i]>>v[i];
		E[u[i]].pb(v[i]);E[v[i]].pb(u[i]);
	}
	C[0][0]=1;
	rep(i,1,n){
		C[i][0]=1;
		rep(j,1,i){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;	
		}
	}
	rep(i,1,n-1){
		int x=u[i],y=v[i]; //第一条染(x,y)边
		memset(vis,0,sizeof vis);
		vis[x]=vis[y]=1;
		dfs(x);dfs(y);
		memset(vis,0,sizeof vis);
		vis[x]=vis[y]=1;
		dp(x);dp(y);
		//组合x,y答案
		ret=f[x]*C[n-2][sz[x]]%mod*f[y]%mod;
		ans=(ans+ret)%mod;
	}
	cout<<ans<<endl;
	return 0;
}
```





---

## 作者：kouylan (赞：1)

我们可以枚举第一次加的是那条边，记为 $(xx,yy)$，这样就把原树拆成两个以 $xx$ 和 $yy$ 为根的不相交的子树，在这两个子树中，父节点的边必须在子节点的边之前加入。

我们设 $f(x)$ 为以 $x$ 为根的子树内的边全部连好的方案数。考虑合并两个子树。

![](https://cdn.luogu.com.cn/upload/image_hosting/w38ihsyt.png)

我们现在已经求出了 $f(y_1),f(y_2)$，要求 $f(x)$。我们发现，只要两个红色圈内的边按顺序就行，两个红色圈之间并没有顺序的要求。左边有 $siz_{y_1}$ 条边，右边有 $siz_{y_2}$ 条边，这些边可以互相插入，所以我们现在要求这样的问题：

**·** 左右两边各取一种方式，把两边合并起来的方案数。

这个问题又可以转化成如下问题：

**·** 给你 $n$ 个球和 $m$ 个筐，要把这 $n$ 个球放进这些筐中，使得每个球进的筐不前于上一个球进的筐，求方案数，记为 $g(n,m)$。

为什么这两个问题是等价的呢？我们把左边红圈内的边想象成球，右边红圈内的边想象成在这些筐之间，而我们按照从左到右按 “筐——空格——筐...” 这样的顺序加边就可以满足条件，所以原问题的答案就是 $g(siz_{y_1},siz_{y_2}+1)$。

现在我们考虑求 $g(n,m)$。因为并不需要把每个筐都放进球，所以不好直接计算。我们可以再设 $g2(n,m)$ 表示 $n$ 个球 $m$ 个筐，按照 $g(n,m)$ 的要求放入球，但最后一个筐必须放球的方案数。这样 $g2(n,m)=g2(n-1,m)+g2(n,m-1)$，就容易计算了。

求出 $g2$ 后，$g(n,m)=\sum\limits_{j=1}^m g2(i,j)$。带回原问题，$f(x)=f(y_1)\times f(y_2)\times g(siz_{y_1},siz_{y_2}+1)$，就可以求解出答案。

这样，预处理 $g2$ 和 $g$ 的复杂度是 $O(n^2)$ 的，枚举最先加的边，再计算 $f$，也是 $O(n^2)$ 的，总时间复杂度为 $O(n^2)$。

下面是 AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int M = 1e9+7ll;

int n,ans,g[1005][1005],g2[1005][1005];
int ee,h[1005],nex[1005<<1],to[1005<<1];
int siz[1005],f[1005];
int fa[1005],xx,yy;

void addedge(int x,int y)
{
	nex[++ee] = h[x], to[ee] = y, h[x] = ee;
}

void getfa(int x,int pre)
{
	fa[x] = pre;
	for(int i=h[x];i;i=nex[i])
		if(to[i]!=pre)
			getfa(to[i],x);
}

void dfs(int x,int pre)
{
	siz[x] = f[x] = 1;
	int cnt=0;
	for(int i=h[x];i;i=nex[i])
		if(to[i]!=pre && to[i]!=xx && to[i]!=yy)
		{
			cnt++;
			dfs(to[i],x);
			if(cnt==1)
				f[x] = f[to[i]];
			else
				f[x] = f[x]*f[to[i]]%M*g[siz[x]-1][siz[to[i]]+1]%M;
			siz[x] += siz[to[i]];
		}
}

signed main()
{
	cin>>n;
	for(int i=1,x,y;i<n&&cin>>x>>y;i++)
		addedge(x,y), addedge(y,x);
	for(int i=1;i<=n;i++)
		g2[1][i] = g2[i][1] = 1;
	for(int i=2;i<=n;i++)
		for(int j=2;j<=n;j++)
			g2[i][j] = (g2[i-1][j]+g2[i][j-1])%M;
	for(int i=1;i<=n;i++)
		g[0][i] = 1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			g[i][j] = (g[i][j-1]+g2[i][j])%M;
//	for(int i=1;i<=n;puts(""),i++)for(int j=1;j<=n;j++)cout<<g[i][j]<<' ';
	getfa(1,0);
	for(int k=2;k<=n;k++)
	{
		xx = k, yy = fa[k];
		dfs(xx,0), dfs(yy,0);
		ans = (ans+f[xx]*f[yy]%M*g[siz[xx]-1][siz[yy]]%M)%M;
//		cout<<xx<<' '<<yy<<endl;for(int i=1;i<=n;i++)cout<<f[i]<<' ';cout<<endl;
	}
	cout<<ans<<endl;
	
	return 0;
   
}
```

祝大家 AC 愉快！

---

## 作者：インデックス (赞：1)

### 题意：画中描绘了从顶点1到顶点N的纸。他在顶点bi和顶点bi之间画了一个边，变成了树。在写树的途中，想一直保持边上的时候，要想什么样的顺序，求mod1000000007后的值

```
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <set>
#include <algorithm>
#include <string>
#include <math.h>
#include <limits.h>
#include <stack>
#include <complex>
 
using namespace std;
 
typedef long long ll;
typedef pair<ll, ll> P;
 
const ll mod = 1000000007;
ll fact[200200];
ll invfact[200200];
 
inline ll take_mod(ll a){
    return (a % mod + mod) % mod;
}
 
inline ll add(ll a, ll b){
    return take_mod(a+b);
}
 
inline ll sub(ll a, ll b){
    return take_mod(a-b);
}
 
 
inline ll mul(ll a, ll b){
    return take_mod(a * b);
}
 
inline ll pow(ll x, ll n){
    ll res = 1LL;
    while(n > 0){
        if(n & 1) res = mul(res, x);
        x = mul(x, x);
        n >>= 1;
    }
    return res;
}
 
ll mod_inv(ll x){
    return pow(x, mod-2);
}
 

void make_fact(ll n){
    fact[0] = 1;
    ll res = 1;
    for(int i = 1; i <= n; i++){
        fact[i] = res;
        res = mul(res, i+1);
    }
}
 

void make_invfact(ll n){
    invfact[0] = 1;
    invfact[n] = mod_inv(fact[n]);
    for(int i = n-1; i >= 1; i--){
        invfact[i] = mul(invfact[i + 1], i + 1);
    }
}
 
ll perm(ll n, ll k){
    return mul(fact[n], invfact[n-k]);
}
 
ll comb(ll n, ll k){
    return mul(mul(fact[n], invfact[n-k]), invfact[k]);
}
 
int N;
vector<int> v[1010];
 
P solve(int s, int bef){
    vector<P> res_list;
    for(int i = 0; i < v[s].size(); i++){
        if(v[s][i] == bef){
            continue;
        }
        P x = solve(v[s][i], s);
        res_list.push_back(x);
    }
 
    ll res = 1, y_sum = 0;
    for(int i = 0; i < res_list.size(); i++){
        y_sum = add(y_sum, res_list[i].second);
    }
    if(y_sum == 0){
        P ret = P(1LL, 1LL);
        return ret;
    }
    else{
        res = fact[y_sum];
        for(int i = 0; i < res_list.size(); i++){
            res = mul(res, invfact[res_list[i].second]);
            res = mul(res, res_list[i].first);
        }
        P ret = P(res, add(y_sum, 1LL));
        return ret;
    }
}
 
 
int main(){
    cin >> N;
    for(int i = 0; i < N-1; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        v[a].push_back(b);
        v[b].push_back(a);
    }
 
    make_fact(10000);
    make_invfact(10000);
 
    ll res = 0;
    for(int i = 0; i < N; i++){
        res = add(res, solve(i, -1).first);
        /*if(i == 0){
            cout << res << endl;
        }
        cout << solve(i, -1).second << endl;*/
 
    }
 
    cout << mul(res, invfact[2]) << endl;
 
    return 0;
 
}
```


---

## 作者：Priestess_SLG (赞：0)

首先套路的，枚举第一条加入的边 $u\to v$，并将其缩为一个点。此时问题变为给定一个有根树，每一次只能从上往下加边，问有多少种不同的加边方法。

然后肯定就是在树上 dfs 遍历每一个结点，然后合并该结点的所有子树信息。设 $f_u$ 表示 $u$ 为根的子树中有多少种不同的加边方法。考虑从简单的情况开始入手：

+ 当前结点 $u$ 没有儿子结点。显然只有一种加边方法。
+ 当前结点 $u$ 恰有一个儿子结点 $v$。显然只能先加 $u\to v$ 这一条边，$f_u=f_v$。
+ 当前结点 $u$ 恰有两个儿子结点 $v_1,v_2$。考虑合并两个儿子结点的信息。首先把 $u$ 和 $v_1$ 为根子树的信息合并，方案数显然为 $f_{v_1}$。然后再将其和 $v_2$ 为根子树合并时：我们设 $g_i$ 表示当前以 $i$ 为根的子树中边的数目，则当前的子问题就和下面的问题相同：
  + 给定两个序列，长度分别为 $g_{v_1}$ 和 $g_{v_2}$。现在需要将两个序列合并为一个长度为 $g_{v_1}+g_{v_2}$ 的序列，且满足在新的序列中原来两个序列中元素的大小关系相对不变。问有多少种不同的新序列。
  + 可以肯定这个转化掉的问题的答案和序列内的值无关。也就是说只需要维护 $f$ 和 $g$ 两个数组的信息。
  + 考虑将第二个序列内的元素按照顺序插入到第一个序列中。则考虑组合计数。最终得到的新序列中有 $g_{v_1}+g_{v_2}$ 的元素，其中有 $g_{v_2}$ 个元素来源于第二个序列，这 $g_{v_2}$ 个元素的顺序已经固定。因此问题的答案为 $\binom{g_{v_1}+g_{v_2}}{g_{v_2}}$。
+ 回到这里讨论的问题。除了上述的 $\binom{g_{v_1}+g_{v_2}}{g_{v_2}}$ 种不同的合并方法外，还有 $v_1$、$v_2$ 为根的子树内对答案的贡献。因此总的合并方案数为：$\binom{g_{v_1}+g_{v_2}}{g_{v_2}}\times f_{v_1}\times f_{v_2}$。
+ 当前结点 $u$ 恰有 $k$ 个儿子结点 $v_1,v_2,\ldots,v_k$。则只需要将这 $k$ 个儿子结点按照顺序依次两两合并即可。

可以通过线性求逆元预处理出组合数，时间复杂度为 $O(n^2)$，可以通过。

```cpp
int n;
vector<int> z[N];
pair<int, int> edge[N];
int f[N], g[N];
int fac[N], inv[N], ifac[N];
int binom(int x, int y) {
    return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
void dfs(int u, int fa) {
    g[u] = f[u] = 1;
    for (auto &v : z[u])
        if (v != fa) {
            dfs(v, u);
            g[u] += g[v];
            f[u] = f[u] * f[v] % mod * binom(g[u] - 1, g[v]) % mod;
        }
}
void run() {
    int n = read();
    for (int i = 0; i < 2; ++i)
        fac[i] = inv[i] = ifac[i] = 1;
    for (int i = 2; i < N; ++i) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = mod - inv[mod % i] * (mod / i) % mod;
        ifac[i] = ifac[i - 1] * inv[i] % mod;
    }
    for (int i = 1; i < n; ++i) {
        int x = read(), y = read();
        edge[i] = {x, y};
    }
    int s = 0;
    for (int i = 1; i < n; ++i) {
        auto [X, Y] = edge[i];
        for (int i = 1; i <= n; ++i) z[i].clear();
        for (int j = 1; j < n; ++j) {
            auto [x, y] = edge[j];
            if (i != j)
                z[x].eb(y), z[y].eb(x);
        }
        fill(f + 1, f + n + 1, 0ll);
        fill(g + 1, g + n + 1, 0ll);
        dfs(X, Y);
        int fx = f[X], gx = g[X];
        fill(f + 1, f + n + 1, 0ll);
        fill(g + 1, g + n + 1, 0ll);
        dfs(Y, X);
        int fy = f[Y], gy = g[Y];
        s = (s + fx * fy % mod * binom(n - 2, gx - 1) % mod) % mod;
    }
    cout << s << '\n';
}
```

---

## 作者：cosf (赞：0)

分享一个麻烦一点的 $O(n\log n)$ 办法。

加边等价于加点。我们可以理解为一个一个点加进去，这样答案除以 $2$ 即可。

因此，我们可以计算每一个点作为第一个被加入的点的方案数。加入该点之后，对于它的每一个子树，我们可以给剩下的 $n-1$ 次加点中选出对应个位置，分配给该子树，该子树再在这些位置里安排自己的顺序。于是这是个递归的过程，可以 dp。

令 $s_u$ 表示子树大小，显然，$s_u = 1 + \sum_{c \in e_u} s_c$，其中 $e_u$ 表示 $u$ 的子节点。然后令 $v_u$ 表示 $u$ 的子树内第一个加入 $u$ 的总方案数是多少，那么有

$$
v_u = (s_u - 1)! \times \prod_{c \in e_u}\frac{v_c}{s_c!}
$$

其中，$\frac{(s_u - 1)!}{\prod_{c \in e_u}s_c!}$ 表示分配给子树的方案。

接下来，我们令 $g_u$ 表示 $u$ 的子树外，先加 $u$ 的父节点 $f$ 的加完点的方案数，有

$$
g_u = (n - s_u - 1)! \times \frac{g_f}{(n - s_f)!} \times \prod_{c \in e_f, c \not= u}\frac{v_c}{s_c!} = g_f \times \frac{v_f \times s_u! \times (n - s_u - 1)!}{v_u \times (s_f - 1)! \times (n - s_f)!}
$$

特别地，如果 $u$ 是根，则 $g_u = 1$。

有了这些，我们就可以算先加点 $u$ 的总方案数 $a_u$：

$$
a_u = (n-1)! \times \frac{g_u}{(n - s_u)!} \times \prod_{c \in e_u}\frac{v_c}{s_c!} = \frac{v_u \times g_u \times (n-1)!}{(n-s_u)! \times (s_u - 1)!}
$$

答案即 $\frac{1}{2} \times \sum_u a_u$。

分两次 dfs，第一次是普通的树形 dp，算 $s_u$ 和 $v_u$，第二次换根，算 $g_v$ 和 $a_v$，时间复杂度 $O(n\log n)$，瓶颈在于算 $v_u$ 的逆元，所以其实可以 $O(n)$。

画个图理解一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/jfl9rib8.png)

```cpp
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 1005
#define MOD 1000000007

using ll = long long;

ll pow(ll b, ll p, ll m);

vector<int> e[MAXN];

int n;

ll fac[MAXN], inf[MAXN];

ll s[MAXN], v[MAXN], inv[MAXN], g[MAXN], a[MAXN];

void dfs1(int u, int f)
{
    s[u] = 1;
    v[u] = 1;
    for (int c : e[u])
    {
        if (c == f)
        {
            continue;
        }
        dfs1(c, u);
        s[u] += s[c];
        v[u] = v[u] * v[c] % MOD * inf[s[c]] % MOD;
    }
    v[u] = v[u] * fac[s[u] - 1] % MOD;
    inv[u] = pow(v[u], MOD - 2, MOD);
}

void dfs2(int u, int f)
{
    if (u == f)
    {
        g[u] = 1;
    }
    else
    {
        g[u] = v[f] * fac[n - s[u] - 1] % MOD * g[f] % MOD * fac[s[u]] % MOD * inf[s[f] - 1] % MOD * inv[u] % MOD * inf[n - s[f]] % MOD;
    }
    a[u] = v[u] * g[u] % MOD * inf[n - s[u]] % MOD * fac[n - 1] % MOD * inf[s[u] - 1] % MOD;
    for (int c : e[u])
    {
        if (c == f)
        {
            continue;
        }
        dfs2(c, u);
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    fac[0] = inf[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        fac[i] = fac[i - 1] * i % MOD;
        inf[i] = pow(fac[i], MOD - 2, MOD);
    }
    dfs1(1, 1);
    dfs2(1, 1);
    ll res = 0;
    for (int i = 1; i <= n; i++)
    {
        res = (res + a[i]) % MOD;
    }
    cout << res * inf[2] % MOD << endl;
    return 0;
}

```

---

## 作者：xuantianhao (赞：0)

# [木](https://www.luogu.com.cn/problem/AT_tdpc_tree)

弱智 DP 题，直接设 $f_i$ 表示 $i$ 子树内染色的方案数，然后每次合并一个点与它的儿子即可（具体而言，因为儿子间独立，所以方案数就是二项式系数）。

需要注意的是因为第一条边可以在任意位置，所以要以每个点为根各 DP 一次。但是这样每条边会被算两次，所以乘以 2 的逆元即可。

时间复杂度 $O(n^2)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int inv2=5e8+4;
const int N=1e3+100;
int n,res;
int f[N],sz[N],fac[N],inv[N];
vector<int>v[N];
void dfs(int x,int fa){
    f[x]=1;
	sz[x]=0;
    for(auto y:v[x]){
        if(y==fa) continue;
        dfs(y,x);
        f[x]=1ll*f[x]*f[y]%mod*inv[sz[x]]%mod*inv[sz[y]]%mod*fac[sz[x]+sz[y]]%mod;
        sz[x]+=sz[y];
    }
    sz[x]++;
}
int ksm(int x,int y=mod-2){
	int z=1;
	for(;y;y>>=1,x=1ll*x*x%mod) if(y&1) z=1ll*z*x%mod;
	return z;
}
signed main(){
    scanf("%lld",&n);
    fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
	for(int i=n;i;i--) inv[i-1]=1ll*inv[i]*i%mod;
    for(int i=1,x,y;i<n;i++){
		scanf("%lld%lld",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
    for(int i=1;i<=n;i++){
		dfs(i,0);
		(res+=f[i])%=mod;
	}
    printf("%lld\n",1ll*res*inv2%mod);
    return 0;
}
```


---

## 作者：shinkuu (赞：0)

典中典，但是好像题解区没有我这个思路的（虽然差不多就是了）？

考虑固定了根，每个子树内部顺序已经固定，这样会有多少种方案。设当前点为 $u$，子树 $i$ 大小为 $siz_i$。则所有方案数为 $(siz_i-1)!$。但是每个以 $v$ 为根的子树都会使答案序列中长为 $siz_v$ 的一个子序列的先后顺序固定。则最后方案数为 $\frac{(siz_u-1)!}{\prod\limits_{v\in son_u} siz_v!}$。总答案则为 $\prod\limits_u\frac{(siz_u-1)!}{\prod\limits_{v\in son_u} siz_v!}$。

这是对于一个根的情况。枚举每一个点为根计算一次，预处理阶乘及逆元后可以 $O(n^2)$ 解决。要注意，因为题目为加边，所以先选 $1,2$ 和先选 $2,1$ 是一样的，即答案最后要 $\times \frac{1}{2}$。

code：

```cpp
int n,m,f[N],inv[N],siz[N];
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
inline void add(int u,int v){
	e[++tot]={v,head[u]};
	head[u]=tot;
}
inline int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
inline int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)
			ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return ret;
}
int calc(int u,int fa){
	int ret=1;
	siz[u]=1;
	go(i,u){
		int v=e[i].to;
		if(v==fa)
			continue;
		ret=1ll*ret*calc(v,u)%mod;
		siz[u]+=siz[v];
		ret=1ll*ret*inv[siz[v]]%mod;
	}
	return 1ll*ret*f[siz[u]-1]%mod;
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	f[0]=1;
	rep(i,1,n){
		f[i]=1ll*f[i-1]*i%mod;
	}
	inv[n]=qpow(f[n],mod-2);
	drep(i,n-1,0){
		inv[i]=1ll*inv[i+1]*(i+1)%mod;
	}
	int ans=0;
	rep(i,1,n){
		ans=Mod(ans,calc(i,0));
	}
	printf("%lld\n",1ll*ans*qpow(2,mod-2)%mod);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：ylxmf2005 (赞：0)

### Description

给定一棵大小为 $n$ 的树，用另外 $n$ 个点加边构造出这棵树，要求构造时所被边连到的点联通，求有多少连边顺序。

$1 \leq n \leq 1000$。

### Solution

![](https://i.loli.net/2020/02/01/dOch6MFrGLkZyEo.png)

连边大致有从上向下和从下向上两个顺序。由于是无根树，可以枚举一个点作为根节点，让所有的边只能从根节点开始往下连，即为从根节点开始生长到叶子节点。

设 $f_x$ 为 $x$ 子树的方案数，$sz_x$ 为子树 $x$ 有多少条边。

初始令 $f_x = 1$。假设处理到了 $x$ 的儿子 $y$，根据乘法原理，$f_x = f_x \times f_y$。但是儿子子树的加边顺序合并到父亲子树时，并不是独立的，只要保证每个儿子加边的相对顺序相对不变，就可以混合搭配。 举个栗子，点 $x$ 有 $k$ 个儿子$y_1 \sim y_k$，现在处理到里 $x$ 的第 $i$ 个儿子 $y_i$，其中 $y_1 \sim y_{i-1}$ 的加边顺序之一为 ${1,2}$，而 $y_i$ 子树的加边顺序之一为 $3,4$。那么有以下混合方式


$1 \quad 2 \quad \color{red}{3 \quad 4}$

$\color{red}{3 \quad 4} \color{black}{\quad 1 \quad 2}$

$1 \color{red}{\quad 3} \color{black}{\quad 2} \color{red}{\quad 4}$

$\color{red}{3} \color{black}{\quad 1} \color{red}{\quad 4} \color{black}{\quad 2}$

$\color{red}{3} \color{black}{\quad 1 \quad 2} \quad \color{red}{4}$

$1 \quad \color{red}{3 \quad 4} \color{black}{\quad 2}$



在处理到 $y$ 时，$f_x$ 已经是若干个儿子子树的所有加边顺序了。所以再乘上一个数，该数为将 $y$ 与之前若干个儿子子树的加边顺序合并，保证 $y$ 子树加边相对位置不变的方案数。

若处理到儿子 $y$ 时，$x$ 子树的边数为 $sz_x$，这里的 $sz_x$ 不是处理完 $x$ 所有儿子后的边数，而是处理到儿子 $y$ 时的边数。问题可以转换成在 $sz_y$ 个不同盒子里面放 $sz_x - sz_y$ 个相同球，可以不放，求方案数。根据插板法，方案数为 $C_{sz_y}^{sz_x}$，这个东东预处理一下即可。

最后 $ans$ 要除以二，因为每一条边会在它两个端点作为父亲时第一个加入。因为 $ans$ 是将所有点为根的答案加起来，所以除以二要用逆元。

时空复杂度为 $O(n^2)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N  = 2000 + 5, p = 1e9 + 7;
inline int read() {
    int X = 0,w = 0; char ch = 0;
    while(!isdigit(ch)) {w |= ch == '-';ch = getchar();}
    while(isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48),ch = getchar();
    return w ? -X : X;
}
struct edge{
	int to, nxt;
}e[N];
int head[N], tot; 
void addedge(int x, int y) {
	e[++tot].to = y, e[tot].nxt = head[x], head[x] = tot;
}
int c[N][N], f[N], sz[N], n, ans;
void dfs(int x, int fa) {
	f[x] = 1, sz[x] = 0;
	for (int i = head[x]; i; i = e[i].nxt) {
		int y = e[i].to;
		if (y != fa) {
			dfs(y, x); sz[x] += sz[y];
			f[x] = f[x] * f[y] % p * c[sz[x]][sz[y]] % p;
		}
	}
	sz[x]++;
}
int ksm(int a, int k) {
    int res = 1;
    while (k) {
        if (k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res % p;
}
signed main() {
	n = read();
	for (int i = 1; i < n; i++) {
		int x = read(), y = read();
		addedge(x, y), addedge(y, x);
	}
	for (int i = 0; i <= n; i++) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; j++) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % p;
	}
	for (int i = 1; i <= n; i++) {
		dfs(i, -1); ans = (ans + f[i]) % p;
	}
	printf("%lld\n", ans * ksm(2, p - 2) % p);
	return 0;	
}

```

---

