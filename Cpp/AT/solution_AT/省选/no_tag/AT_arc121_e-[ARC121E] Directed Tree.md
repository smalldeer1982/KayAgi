# [ARC121E] Directed Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc121/tasks/arc121_e

$ 1 $ から $ N $ の番号がついた $ N $ 頂点の有向木が与えられます。

頂点 $ 1 $ はこの木の根です。 $ 2\ \leq\ i\ \leq\ N $ を満たす整数 $ i $ について、頂点 $ p_i $ から $ i $ へ向かう有向辺が存在します。

$ a $ を $ (1,\ldots,N) $ を並び替えて得られる数列とします。また、$ a $ の $ i $ 番目の項を $ a_i $ とします。

$ a $ としてありうる数列は $ N! $ 通りあります。それらのうち、下記の条件を満たすものの個数を $ 998244353 $ で割ったあまりを求めてください。

- 条件：$ 1\ \leq\ i\ \leq\ N $ を満たす任意の整数 $ i $ について、頂点 $ a_i $ から **$ 1 $ 度以上**辺を辿って頂点 $ i $ へ到達することはできない。

## 说明/提示

### 制約

- 与えられる入力は全て整数
- $ 1\ \leq\ N\ \leq\ 2000 $
- $ 1\ \leq\ p_i\ <\ i $

### Sample Explanation 2

\- $ 998244353 $ で割ったあまりを出力するのを忘れずに。

## 样例 #1

### 输入

```
4
1 1 3```

### 输出

```
4```

## 样例 #2

### 输入

```
30
1 1 3 1 5 1 1 1 8 9 7 3 11 11 15 14 4 10 11 12 1 10 13 11 7 23 8 12 18```

### 输出

```
746746186```

# 题解

## 作者：EuphoricStar (赞：7)

显然 $a_i$ 可以是除了 $i$ 的所有祖先以外的任意点。考虑求 $a$ 的逆排列 $b$，$b_i$ 就不可能是 $i$ 子树内的点。

考虑一个容斥，$g_i$ 为钦定其中 $i$ 个结点不合法的方案数。那么 $ans = \sum\limits_{i=0}^n (-1)^i g_i (n-i)!$。

现在问题转化成了如何求 $g_i$。考虑树形 dp，$f_{u,i}$ 表示 $u$ 子树内有 $i$ 个点不合法 **且只考虑不合法的点** 的方案数。

- 不同子树，因为不合法的范围不交，所以可以直接类似树形背包合并，$f_{u,j+k} \gets f_{u,j} \times f_{v,k}$。
- 最后计算 $u$ 不合法的情况的 dp 值时，$f_{u,i} \gets f_{u,i-1} \times ((sz_u-1)-(i-1))$，意思是 $u$ 原本可以选子树内的 $sz_u-1$ 个点，有 $i-1$ 个点已经被选了。

那么 $g_i = f_{1,i}$。

时间复杂度 $O(n^2)$。

[code](https://atcoder.jp/contests/arc121/submissions/37089728)

---

## 作者：Graphcity (赞：4)

比较简单的二项式反演题。

观察到原题的条件相当于不存在 $a_i$ 是 $i$ 的祖先。考虑二项式反演，设 $f_i$ 为钦定有 $i$ 个点不满足条件的方案数。

再设 $f_{x,i}$ 为 $x$ 子树内钦定了 $i$ 个点不满足条件的方案数。对于结点 $x$ 和它的一个儿子 $y$，有转移 $f_{x,i+j}\gets f_{x,i}\times f_{y,j}$。

当然也可以存在子树内的结点连到它自己，有转移 $f_{x,i}\gets f_{x,i}+f_{x,i-1}\times (siz_x-i)$。

剩下的未被钦定的点随便匹配即可，$f_i=f_{1,i}\times (n-i)!$。

二项式反演，$ans=\sum_{i=0}^n(-1)^if_i$。

时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e3,Mod=998244353;

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

int n,fa[Maxn+5],siz[Maxn+5],fac[Maxn+5];
int f[Maxn+5][Maxn+5],g[Maxn+5];
vector<int> v[Maxn+5];

inline void dfs(int x)
{
    f[x][0]=1,siz[x]=1;
    for(auto y:v[x]) dfs(y);
    for(auto y:v[x])
    {
        For(i,0,siz[x]+siz[y]) g[i]=0;
        For(i,0,siz[x]) For(j,0,siz[y]) g[i+j]=(g[i+j]+1ll*f[x][i]*f[y][j]%Mod)%Mod;
        For(i,0,siz[x]+siz[y]) f[x][i]=g[i];
        siz[x]+=siz[y];
    }
    Rof(i,siz[x],1) f[x][i]=(f[x][i]+1ll*f[x][i-1]*(siz[x]-(i-1)-1)%Mod)%Mod;
}

int main()
{
    n=read(),fac[0]=1;
    For(i,1,n) fac[i]=1ll*fac[i-1]*i%Mod;
    For(i,2,n) v[fa[i]=read()].push_back(i);
    dfs(1);
    int ans=0;
    For(i,0,n) f[1][i]=1ll*f[1][i]*fac[n-i]%Mod;
    For(i,0,n) ans=(ans+(i&1?-1ll:1ll)*f[1][i])%Mod;
    printf("%d\n",(ans+Mod)%Mod);
    return 0;
}
```

---

## 作者：Claire0918 (赞：1)

题目中对 $a_i$ 的限制实际上是要求 $a_i$ 不是 $i$ 的祖先。

直接要求任何 $a_i$ 都满足条件是难以统计的，考虑容斥。设 $F(S)$ 表示钦定 $i \in S$ 满足 $a_i$ 是 $i$ 的祖先，$i \notin S$ 则不做限制。那么答案为
$$
\sum_{S \subseteq [1, n]} (-1)^{|S|} F(S)
$$

考虑如何计算 $F(S)$。利用题目中的树形结构，设 $f_{u, i}$ 表示在 $u$ 子树中有 $i$ 个点被钦定满足 $a_i$ 是 $i$ 的祖先的**钦定方案数**，即不计算未被钦定点的 $a_i$ 的方案数，那么答案为
$$
\sum_{S \subseteq [1, n]} (-1)^{|S|} F(S) = \sum_{i = 0}^{n} (-1)^if_{1, i}(n - i)!
$$
我们有初始化 $f_{u, 0} = 1$。我们先不考虑 $u$ 可以作为某一个 $a_i$，而只是将 $f_v$ 合并，每一次有树上背包的转移 $f_{u, j} + f_{v, k} \to f'_{u, j + k}$。

再考虑选择 $u$ 作为某一个 $a_i$。对于一个状态 $f_{u, j}$，此时 $a_i$ 待确定的点共有 $siz_u - j - 1$ 个，从而有 $f'_{u, j + 1} \gets f_{u, j + 1} + f_{u, j} \times (siz_u - j - 1)$。

如上转移得到 $f_1$ 并按式子求值即可，时间复杂度是树上背包的 $\mathcal{O}(n^2)$。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 2000 + 10, mod = 998244353;

struct{
    int v, nex;
} edge[maxn << 1];

int n, res = 0;
int fac[maxn], siz[maxn], f[maxn][maxn], g[maxn];
int head[maxn], top = 0;

template<typename Tp_x, typename Tp_y>
inline int mod_add(Tp_x x, Tp_y y){
    x += y;
    return x >= mod ? x -= mod : x;
}

inline void add(int u, int v){
    edge[++top].v = v;
    edge[top].nex = head[u];
    head[u] = top;
}

inline void dfs(int u, int fa){
    f[u][0] = 1;
    siz[u] = 1;
    for (int i = head[u]; i; i = edge[i].nex){
        const int v = edge[i].v;
        if (v != fa){
            dfs(v, u);
            for (int j = 0; j <= siz[u] + siz[v]; j++){
                g[j] = 0;
            }
            for (int j = 0; j <= siz[u]; j++){
                for (int k = 0; k <= siz[v]; k++){
                    g[j + k] = mod_add(g[j + k], (long long)f[u][j] * f[v][k] % mod);
                }
            }
            siz[u] += siz[v];
            for (int j = 0; j <= siz[u]; j++){
                f[u][j] = g[j];
            }
        }
    }
    for (int j = 0; j <= siz[u]; j++){
        g[j] = 0;
    }
    for (int j = 0; j < siz[u]; j++){
        g[j + 1] = (long long)f[u][j] * (siz[u] - j - 1) % mod;
    }
    for (int j = 0; j <= siz[u]; j++){
        f[u][j] = mod_add(f[u][j], g[j]);
    }
}

int main(){
    scanf("%d", &n);
    fac[0] = 1;
    for (int i = 1; i <= n; i++){
        fac[i] = (long long)fac[i - 1] * i % mod;
    }
    for (int u = 2; u <= n; u++){
        int v;
        scanf("%d", &v);
        add(u, v), add(v, u);
    }
    dfs(1, 0);
    for (int i = 0; i <= n; i++){
        const int val = (long long)f[1][i] * fac[n - i] % mod;
        if (i & 1){
            res = mod_add(res, mod - val);
        }else{
            res = mod_add(res, val);
        }
    }
    printf("%d", res);

return 0;
}
```

---

## 作者：天命之路 (赞：1)

### ARC121E

关键词：容斥，拆贡献，树上背包

简单题。

原题是计数排列 $p$ ，满足 $p_i$ 不是 $i$ 的祖先。

”不是祖先“很难处理，故尝试容斥，原问题变为"钦定有 $x$ 个位置 $i$ 满足 $p_i$ 是 $i$ 的祖先"。

我们建一张图，对于已经钦定的点 $i$，由 $i$ 向 $p_i$ 连边。

因为 $p_i$ 是 $i$ 的祖先，所以这张图中不会有环。

所以钦定出来的是若干条链和若干个孤立点。

接下来把孤立点也算作链。

设有 $a$ 条链。

我们要把整张图补成若干个置换环， 在补的过程中，一条链和一个点是等价的。

所以，对于有 $a$ 条链的方案，贡献为 $a!$。

所以就会有个 $dp$，设 $f[u][x][a]$ 表示在 $u$ 子树内，钦定了 $x$ 个位置的 $p_i$，目前钦定出了 $a$ 条链的方案数。

转移的时候把子树背包起来，然后讨论 $u$ 是单独成链还是接在下面某条链的首端即可。

答案为 $\sum_{x,a} a!(-1)^xf[1][x][a]$

但我们发现，可以让每次新加一条链的时候都将现有方案乘上一个 $-1$，而不是到最后再乘上 $(-1)^x$。

这也就是把容斥系数拆进 $dp$ 过程里面，这样就只需记录 $f[u][a]$ 了（这个阶乘拆不进去）。

然后使用树上背包即可做到 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 5,P = 998244353;
int f[N][N],n,sze[N],fac[N];
vector<int> G[N];
void Dp(int x,int fa)
{
	static int tmp[N];
	for(int i = 0;i <= n;i++) tmp[i] = 0;
	f[x][0] = 1;
	for(auto y : G[x])
	{
		if(y == fa) continue;
		Dp(y,x);
		for(int i = 0;i <= sze[x];i++)
			for(int j = 0;j <= sze[y];j++)
				(tmp[i + j] += 1ll * f[x][i] * f[y][j] % P) %= P;
		sze[x] += sze[y];
		for(int i = 0;i <= sze[x];i++)
			f[x][i] = tmp[i],tmp[i] = 0;
	}
	// 合并 u
	for(int i = sze[x];i >= 0;i--)
	{
		(f[x][i + 1] += f[x][i]) %= P;// 让 u 成为新链的开头
		f[x][i] = 1ll * f[x][i] * (P - i) % P;// 让 u 接上一条链，带上 -1 的容斥系数
	}
	++sze[x];
}
int main()
{
	scanf("%d",&n);
	for(int i = 2,x;i <= n;i++)
		scanf("%d",&x),G[x].push_back(i);
	Dp(1,0);
	fac[0] = 1;
	for(int i = 1;i <= n;i++) fac[i] = 1ll * fac[i - 1] * i % P;
	int ans = 0;
	for(int i = 1;i <= n;i++) (ans += 1ll * f[1][i] * fac[i] % P) %= P;
	cout << ans << endl;
	return 0;
}
```



---

## 作者：lfxxx (赞：0)

问题等价于给树上每个点选择一个非祖先点，不能有两个点选择同一个点。

直接做能求出答案，但是时间比较劣，考虑二项式反演一下。

钦定若干个点不满足条件等价于钦定若干组祖先后代点对，计算选出 $i$ 组这样的点对方案可以简单树形背包，时间复杂度 $O(n^2)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e3+114;
const int mod = 998244353;
int dp[maxn][maxn];
int sz[maxn];
int n;
vector<int> E[maxn];
void dfs(int u,int fa){
    dp[u][0]=1;
    sz[u]=0;
    for(int v:E[u]){
        dfs(v,u);
        for(int i=sz[u];i>=0;i--){
            for(int j=sz[v];j>=1;j--){
                dp[u][i+j]=(dp[u][i+j]+dp[u][i]*dp[v][j]%mod)%mod;
            }
        }
        sz[u]+=sz[v];
    }
    for(int i=sz[u]-1;i>=0;i--) dp[u][i+1]=(dp[u][i+1]+dp[u][i]*(sz[u]-i)%mod)%mod;
    sz[u]++;
}
int fac[maxn];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    for(int i=2;i<=n;i++){
        int fa;
        cin>>fa;
        E[fa].push_back(i);
    }
    dfs(1,0);
    int ans=fac[n];
    for(int i=1;i<=n;i++){
        ans=(ans+(i%2==1?(mod-1):1)*dp[1][i]%mod*fac[n-i]%mod)%mod;
    }
    cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：ax_by_c (赞：0)

就是求有多少排列 $a$ 满足 $a_i$ 不是 $i$ 的祖先。

不会做，考虑容斥。

设有至少 $j$ 对 $a_i$ 是 $i$ 的祖先的方案数为 $F(j)$，则答案为 $\sum_j (-1)^{j}F(j)$。

考虑求 $F(j)$，选 $j$ 对的方案数乘 $(n-j)!$ 即可。

考虑 DP，设 $f_{i,j}$ 为 $i$ 子树内选 $j$ 对的方案数，转移就是卷积然后 $f_{i,j}\leftarrow f_{i,j}+f_{i,j-1}(sz_u-(i-1)-1)$。

时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const ll mod=998244353;
const int N=2005;
int n,fa[N],sz[N];
vector<int>g[N];
ll fac[N],f[N][N],ff[N];
void dfs(int u){
	f[u][0]=1;
	sz[u]=1;
	for(auto v:g[u]){
		dfs(v);
		rep(i,0,sz[u]+sz[v])ff[i]=0;
		rep(x,0,sz[u])rep(y,0,sz[v])ff[x+y]=(ff[x+y]+f[u][x]*f[v][y]%mod)%mod;
		rep(i,0,sz[u]+sz[v])f[u][i]=ff[i];
		sz[u]+=sz[v];
	}
	per(i,sz[u],1)f[u][i]=(f[u][i]+f[u][i-1]*(sz[u]-(i-1)-1)%mod)%mod;
}
void slv(){
	scanf("%d",&n);
	rep(i,2,n)scanf("%d",&fa[i]),g[fa[i]].pb(i);
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	dfs(1);
	ll ans=0;
	for(int i=0;i<=n;i++){
		if(i%2==0)ans=(ans+f[1][i]*fac[n-i]%mod)%mod;
		else ans=(ans-f[1][i]*fac[n-i]%mod+mod)%mod;
	}
	printf("%lld\n",ans);
}
void main(){
	int T=1;
//	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：Qiubit (赞：0)

可以将题意转化为：

一共有 $n$ 个位置 $p_1,p_2,\cdots,p_n$，你填 $1\sim n$ 进去，使得  $i$ 不能为 $p_i$ 的后代。

由于要所有的 $i$ 和 $p_i$ 都满足条件，每个 $i$ 要么满足要么不满足，因此对于 $n$ 个条件一共有 $2^n$ 个子集。

直接计算不好计算且容易重复，我们可以使用容斥原理，并能很容易求出 $i$ 可以为 $p_i$ 后代的情况。

设 $f[i][j]$ 表示以 $i$ 为根节点的子树有 $j$ 个点（即 $j$ 个条件不满足）的方案数。

则根据容斥原理，最后答案为 $f[1][0] \times n!-f[1][1] \times (n-1)!+f[1][2] \times (n-2)!- \cdots -(-1)^n \times f[1][n]$。

即 $\sum_{j=0}^n (-1)^j \times f[1][j] \times (n-j)!$。

求 $f[i][j]$ 可以用 dfs 完成。简单描述如下：

假设 $u$ 为子树根节点，当前 $f[u][x]$ 为还没有搜某个儿子节点 $v$ 的情况（已经求出了 $v$ 前面兄弟节点）

则可以求出当前所有情况,我们用 $g[i]$ 表示，有 $g[x+y]=g[x+y]+f[u][x]\times f[v][y]$, （其中 $x,y$ 为枚举 $u$ 子树已经有的节点和 $v$ 子树的节点）。更新完 $g$ 后即可把 $siz[v]$ 累加到 $siz[u]$ 里，且用 $g[x]$ 去更新 $f[u][x]$。

搜索并回溯所有的儿子后，更新所有 u 子树的 dp 情况：

$f[u][x+1]=f[u][x+1]+f[u][x] \times (siz[u]-x-1) $。

总的时间复杂度为 $O(n^2)$。

---

## 作者：DerrickLo (赞：0)

考虑容斥，如果一个排列中有 $i$ 个点不合法，那么对答案的贡献就是 $(-1)^i$，那我们只需要对于每个 $i$ 求出至少有 $i$ 个点不合法的方案数即可。

我们发现，如果这 $i$ 个不合法的点已经确定，那么对于这些不合法的点，它们都必须选择子树内且不等于自身的点作为 $a_i$，而其他点在它们选的点固定之后还有 $(n-i)!$ 种选法。那么通过乘法原理不难发现这些点选择 $a_i$ 的方案数就是所有不合法点 $v$ 的子树大小减去子树内不合法点的个数乘起来的积。

那么直接 dp 就可以了。记 $f_{u,i}$ 表示以 $u$ 为根的子树内，选了 $i$ 个不合法点的方案数，转移可以类似背包地转移。

时间复杂度 $\mathcal O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define int long long
using namespace std;
int n,p[2005],f[2005][2005],g[2005],h[2005],sz[2005],ans,fac[2005];
vector<int>ve[2005];
void dfs(int u){
	sz[u]=1;
	for(int v:ve[u])dfs(v),sz[u]+=sz[v];
	for(int i=0;i<=sz[u];i++)g[i]=1;
	int now=0;
	for(int v:ve[u]){
		memcpy(h,g,sizeof g);
		memset(g,0,sizeof g);
		for(int i=0;i<=now;i++)for(int j=0;j<=sz[v];j++){
			g[i+j]+=h[i]*f[v][j]%mod;
			g[i+j]%=mod;
		}
		now+=sz[v];
	}
	for(int i=0;i<sz[u];i++){
		f[u][i]+=g[i],f[u][i]%=mod;
		f[u][i+1]+=g[i]*(sz[u]-1-i),f[u][i+1]%=mod; 
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=2;i<=n;i++)cin>>p[i],ve[p[i]].emplace_back(i);
	dfs(1);
	ans=fac[n];
	for(int i=1;i<=n;i++){
		if(i&1)ans-=fac[n-i]*f[1][i]%mod,ans+=mod,ans%=mod;
		else ans+=fac[n-i]*f[1][i]%mod,ans%=mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

挺不错的容斥典题，记录一下。

题目要求每个 $a_i$ 都不能经过至少一条边到 $i$。如果考虑对于一个 $i$，怎么样的 $a_i$ 合法，则会发现它可以是 $i$ 子树内的点，$i$ 的父亲的儿子的子树中，不包含 $i$ 的子树内的点……这很难处理。

于是考虑正难则反，容易发现对于一个 $i$，不合法的 $a_i$ 是它的祖先。这个性质非常好，于是容斥。

考虑树形 dp，$dp_{u,i}$ 表示 $u$ 子树内有 $i$ 个点的 $a_i$ 还**没有**被钦定为不合法，按照 $O(n^2)$ 树形背包的方法转移。先不管 $u$ 点，把儿子的背包合并。

然后加入 $u$ 点，此时首先可能有一个 $u$ 子树内的点 $v$，$a_v\to u$。乘上选点的方案数，于是 $dp_{u,i}=dp_{u,i}+dp_{u,i+1}\times (i+1)$。然后 $u$ 点一定还没有被钦定，$dp_{u,i}=dp_{u,i-1}$。

最后统计答案时，给每个没有钦定的 $u$ 随便定一个 $a_i$，方案数为阶乘，再乘上 dp 值和 $(-1)^{n-i}$ 即可。

code：

```cpp
int n,m,siz[N],dp[N][N],tmp[N],fac[N];
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
il void add(int u,int v){
	e[++tot]={v,head[u]},head[u]=tot;
}
il int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
void dfs(int u,int f){
	siz[u]=1;
	dp[u][0]=1;
	go(i,u){
		int v=e[i].to;
		if(v==f){
			continue;
		}
		dfs(v,u);
		rep(i,0,siz[u]+siz[v]){
			tmp[i]=0;
		}
		rep(i,0,siz[u]){
			rep(j,0,siz[v]){
				tmp[i+j]=Mod(tmp[i+j],1ll*dp[u][i]*dp[v][j]%mod);
			}
		}
		siz[u]+=siz[v];
		rep(i,0,siz[u]){
			dp[u][i]=tmp[i];
		}
	}
	rep(i,0,siz[u]-1){
		dp[u][i]=Mod(dp[u][i],1ll*dp[u][i+1]*(i+1)%mod);
	}
	drep(i,siz[u],1){
		dp[u][i]=dp[u][i-1];
	}
	dp[u][0]=0;
}
void Yorushika(){
	read(n);
	rep(i,2,n){
		int x;read(x);
		add(x,i);
	}
	dfs(1,0);
	fac[0]=1;
	rep(i,1,n){
		fac[i]=1ll*fac[i-1]*i%mod;
	}
	int ans=0;
	rep(i,0,n){
		if(i&1){
			ans=Mod(ans,mod-1ll*dp[1][n-i]*fac[n-i]%mod);
		}else{
			ans=Mod(ans,1ll*dp[1][n-i]*fac[n-i]%mod);
		}
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：TLEWA (赞：0)

发现很难直接计数合法情况，考虑容斥。

我们设 $f_i$ 为钦定 $i$ 个点为不合法点的方案数。答案即为 $\sum_{i=0}^n{} (-1)^i (n-i)! f_i$。如何计算 $f$ 数组？不难想到使用树形 dp。我们设 $dp_{i,j}$ 表示以 $i$ 为根的子树中，钦定出 $j$ 个不合法点的方案数。如何转移？

我们发现这个东西其实是一个形似树上背包的东西，对于子树我们直接使用与普通树上背包相同的方法合并上来，合并完成后我们计算钦定自身为不合法点的方案数，转移为：

$$$dp_{u,i+1} \gets  dp_{u,i} \times ((siz_u-1)-i)$$$

时间复杂度 $O(n^2)$，注意最后转移自身不合法的情况时要按照从后往前转移的顺序，否则新值会影响转移。

## AC 代码


```cpp
#include<bits/stdc++.h>
#define int long long 

using namespace std;

/*
考虑容斥。

我的容斥很差，好在这题的容斥部分比较简单？考虑钦定不合法的数量，然后我们发现树的美丽性质
树形 dp 一下即可。
*/

const int N=2005,mod=998244353;

int n;

vector<int> vec[N];

int md(int num) {return (num+mod)%mod;}

int siz[N],dp[N][N],arr[N]; // 以 i 为根，不合法数量为 j 的数量 
void dfs(int u) {
	for(auto v:vec[u]) dfs(v);
	
	dp[u][0]=1;
	for(auto v:vec[u]) {
		fill(arr,arr+1+siz[u]+siz[v],0);
		for(int i=0;i<=siz[u];++i)
			for(int j=0;j<=siz[v];++j)
				arr[i+j]=md(arr[i+j]+dp[u][i]*dp[v][j]);
		siz[u]+=siz[v];
		for(int i=0;i<=siz[u];++i) dp[u][i]=arr[i];
	}
	siz[u]++;
	for(int i=siz[u];i>=1;--i) dp[u][i]=md(dp[u][i]+dp[u][i-1]*((siz[u]-1)-(i-1)));
}

int pw[N];
signed main() {
	cin >> n;
	
	int fa;
	for(int i=2;i<=n;++i) {
		cin >> fa;
		vec[fa].push_back(i);
	}
	
	dfs(1);
	
	pw[0]=1;
	for(int i=1;i<=n;++i) pw[i]=md(pw[i-1]*i);
	
	int ans=0,op=1;
	for(int i=0;i<=n;++i) {
		ans=md(ans+op*md(dp[1][i]*pw[n-i]));
		op=-op;
	}
	cout << ans;
	
	return 0;
}

```

树上背包做少了，vp 的时候一直没认出来这是个啥，以为这是 $O(n^3)$，最后才恍然大悟。

---

## 作者：DengDuck (赞：0)

想到了容斥，想到了树形 DP，想到了正确的状态，但是没想到怎么转移，这叫什么，这叫菜！

首先矛盾就是 $a_i$ 为自己的祖先，下文我们说 $i$ 指向 $a_i$。

我们发现，因为原来是个排列，所以一个点只能指向一个点，一个点也只能被一个点指向。

显然考虑容斥，设 $F_i$ 表示至少有 $i$ 个点指向自己的祖先。

考虑树形 DP，设 $f_{i,j}$ 表示 $i$ 子树中至少有 $j$ 个点指向了自己的祖先的方案数。

那么，我们思考，确定某一点指向祖先的时候，是在祖先那里确定，还是在孩子那里确定。

显然，为了防止祖先被多个孩子指到，应该在祖先那里确定。

所以思路就很明显了，以树上背包的形式合并子树和父亲，然后考虑有儿子连向根节点，来更新答案即可。

我们发现没有考虑其他的点，对于其他的点，我们最后对于 $f_{1,i}$ 乘上 $(n-i)!$ 表示其他点随便匹配，再赋值到 $F_i$ 上即可。

然后套一套容斥式子就做完了。

等等，有个小问题，在乘上 $(n-i)!$ 后，一种方案可能会在一个 $F_i$ 中计算多次，咋办呢？

让我们来推翻前面的所有容斥思考。

我问了一下 wtc 犇犇，wtc 告诉我，“一种方案可以通过多种钦定方式被重复计算”，我理解了一下，其实对于容斥来说，只需要保证一种已知的方案，考虑在每个 $F_i$ 中算了几次，最后看乘上容斥系数后累加看是否满足合法答案贡献为 $1$，非法情况贡献为 $0$ 即可。

对于这题怎么证明呢？感谢 wtc 老师的细致讲解。

对于一种方案，我们设不合规的点集为 $S$。

算贡献时枚举子集 $T$，然后改为枚举子集大小：

$$
\sum_{T\subset S} (-1)^{|T|}=\sum_{i=0}^{|S|}(-1)^i C_{|S|}^i
$$

利用二项式反演，得：

$$
\sum_{i=0}^{|S|}(-1)^i C_{|S|}^i=(-1+1)^{|S|}=0^{|S|}
$$

显然当 $|S|\not =0$ 时 贡献为 $0$，当 $|S|=0$ 时代入原式得结果为 $1$。

所以原式等价于 $[|S|=0]$，然后没了。

学到了什么：

- 不要破坏题目的美好性质，我一开始想的是转成 DFS 序变成区间问题。
- 容斥动态规划不要想着想着忘了至少多少多少。
- 树上背包可以开临时数组存，类似一个卷积，好写，问题少。
- 容斥，还可以这么玩的，对它有了一个全新的理解。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
//const LL inf;
const LL N=2e3+5;
//const LL M;
const LL mod=998244353;
//const LF eps;
//const LL P;
LL n,x,sz[N],f[N][N],ans,fac[N],g[N];
vector<LL>v[N];
void dfs(LL x,LL fa)
{
	sz[x]=1,f[x][0]=1;
	for(LL i:v[x])
	{
		if(i==fa)continue;
		dfs(i,x);
		for(int j=0;j<=sz[x]+sz[i];j++)g[j]=0;
		for(int j=0;j<=sz[x];j++)for(int k=sz[i];k>=0;k--)g[j+k]=(g[j+k]+f[x][j]*f[i][k]%mod)%mod;
		sz[x]+=sz[i];
		for(int j=0;j<=sz[x];j++)f[x][j]=g[j];
	}
	for(int i=sz[x];i>=1;i--)f[x][i]=(f[x][i]+f[x][i-1]*(sz[x]-i))%mod;
}
int main()
{
	scanf("%lld",&n);
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=2;i<=n;i++)
	{
		scanf("%lld",&x);
		v[x].pb(i);
	}
	dfs(1,0);
	LL t=1;
	for(int i=0;i<=n;i++)
	{
		ans=(ans+t*f[1][i]*fac[n-i]%mod+mod)%mod;
		t*=-1;
	}
	printf("%lld\n",ans);
	return 0;
}
//RP++
```

---

## 作者：Unnamed114514 (赞：0)

因为逆排列和原排列是一一对应的，考虑把求逆排列的方案数，把祖先的问题转化为子树的问题。

为了解决 @[lvvd](https://www.luogu.com.cn/user/517291) 的需求，我们来看看为什么取逆排列后祖先会变成子树：

首先因为它已经不合法了，所以 $a_i$ 就是 $i$ 的祖先。（注意题意：有根树，所以只有祖先到儿子的边）然后我们取它的逆排列 $b$ 有 $b_{a_i}=i$，因为 $i$ 是 $a_i$ 的儿子，所以逆排列 $b$ 中不能有 $b_i$ 满足 $b_i$ 是 $i$ 的儿子。

正难则反，考虑容斥，定义 $f_{u,k}$ 为以 $u$ 为根的子树，至少有 $k$ 个节点不合法时这 $k$ 个节点的方案，其它的点随便取，就是 $(n-k)!$。

因为不同的子树不合法区间相互独立，直接用背包合并即可。

最后算上 $u$ 要取的贡献，是容易算的 $f_{u,i}\gets f_{u,i}+f_{u,i-1}\times((siz_u-1)-(i-1))$。

注意转移顺序。

---

## 作者：win114514 (赞：0)

简单容斥题。

### 思路

题面的条件相当于一个位置上填的点不能是自己的祖先。

发现直接做并不好做。

考虑容斥。

我们想要求出 $f_i$ 为至少有 $i$ 个不合法位置的方案数。

那么答案为：

$$
\sum_{i=0}^n f_i(-1)^i
$$

如何求解。

设 $f_{i,j}$ 为 $i$ 子树下有 $j$ 个不合法位置的方案数。

第一种转移是普通背包合并。

$$
f_{i,j}=\sum_{k=0}f_{s,k}\times f_{i,j-k}
$$

第二种转移则是此时子树的根填到子树下的一个位置，相当于多了一个不合法位置。

$$
f_{i,j}=f_{i,j}+f_{i,j-1}\times (siz_i-j)
$$

最后在令 $f_{1,i}=f_{1,i}\times (n-i)!$，表示其它的点可以随便摆放。

时间复杂度：$O(n)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

#define int long long

int n, ans;
int s[2020], p[2020];
int g[2020], v[2020];
int f[2020][2020];
vector<int> to[2020];

inline void dfs(int x) {
  s[x] = f[x][0] = 1;
  for (auto i : to[x])
    if (i != p[x]) {
      dfs(i);
      fill(g, g + s[x] + s[i] + 1, 0);
      for (int j = 0; j <= s[x]; j++)
        for (int k = 0; k <= s[i]; k++)
          (g[j + k] += f[x][j] * f[i][k]) %= mod;
      copy(g, g + s[x] + s[i] + 1, f[x]);
      s[x] += s[i];
    }
  for (int i = s[x]; i >= 1; i--)
    (f[x][i] += f[x][i - 1] * (s[x] - i)) %= mod;
}

signed main() {
  cin >> n;
  for (int i = 2; i <= n; i++) cin >> p[i];
  for (int i = 2; i <= n; i++) to[p[i]].push_back(i);
  dfs(1);
  v[0] = 1;
  for (int i = 1; i <= n; i++) v[i] = v[i - 1] * i % mod;
  for (int i = 0; i <= n; i++) {
    (ans += v[n - i] * f[1][i] * (i & 1 ? -1 : 1)) %= mod;
  }
  cout << (ans + mod) % mod << "\n";
}
```

---

