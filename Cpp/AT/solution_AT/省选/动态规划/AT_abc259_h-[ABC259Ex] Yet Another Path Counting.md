# [ABC259Ex] Yet Another Path Counting

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc259/tasks/abc259_h

縦 $ N $ 行横 $ N $ 列のマス目があり、上から $ i $ 行目、左から $ j $ 列目のマスには整数のラベル $ a_{i,j} $ が付けられています。  
 いずれかのマスから始めて**右または下**に隣接するマスへの移動を $ 0 $ 回以上繰り返すことで得られる経路のうち、始点と終点のラベルが同じものの個数を $ 998244353 $ で割った余りを求めてください。  
 なお、$ 2 $ つの経路は通ったマス(始点・終点含む)の集合が異なる場合に区別します。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 400 $
- $ 1\ \leq\ a_{i,j}\ \leq\ N^2 $
- 入力はすべて整数

### Sample Explanation 1

条件を満たす経路は以下の $ 6 $ 個です。(上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,j) $ として、各経路で通るマスを順に示しています) - $ (1,1) $ - $ (1,1) $ → $ (1,2) $ → $ (2,2) $ - $ (1,1) $ → $ (2,1) $ → $ (2,2) $ - $ (1,2) $ - $ (2,1) $ - $ (2,2) $

## 样例 #1

### 输入

```
2
1 3
3 1```

### 输出

```
6```

# 题解

## 作者：AKPC (赞：8)

先引入小学问题：从左上角 $(1,1)$ 走到右下角 $(n,m)$，仅向右或向下走，有多少中路径？

法一：递推法。令 $dp_{i,j}$ 表示 $(1,1)$ 走到 $(i,j)$ 的方案数，因为不可能走到第 $0$ 行（列），所以形如 $dp_{0,j}(1\leq j\leq m)$ 和 $dp_{i,0}(1\leq i\leq n)$ 的值初值为 $0$。然后就有 $dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}(1\leq i\leq n,1\leq j\leq m)$，这是显然的，从 $(i,j-1)$ 到 $(i,j)$ 只能向右一步（仅一种方案），也就是 $(1,1)$ 到 $(i,j)$ 的方案乘以 $1$，$(i-1,j)$ 的同理。复杂度 $\Theta(nm)$。

法二：组合数学。从 $(1,1)$ 到 $(n,m)$ 需要向右 $m-1$ 步，向下 $n-1$ 步，原因显然。那么问题转化从 $n+m-2$ 步内选 $n-1$ 步向下的问题，对应组合数公式为 $C_{n+m-2}^{n-1}$。复杂度 $\Theta(n+m-2)$（暴力算组合数），也可以选择预处理阶乘以及其逆元。

回到本题，题意相当于求 $\sum\limits_{i=1}^n\sum\limits_{j=1}^m\sum\limits_{i'=1}^n\sum\limits_{j'=1}^mf(i,j,i',j')[a_{i,j}=a_{i',j'}]$，其中 $f(i,j,i',j')$ 表示 $(i,j)$ 到 $(i',j')$ 的方案总和。

对于这个问题我的第一个想法就是组合数（小学问题里面其复杂度更优），把 $f(i,j,i',j')$ 换成 $C_{i'+j'-i-j}^{i'-i}$，直接这么做，复杂度 $\Theta(n^4)$，但是有 $[a_{i,j}=a_{i',j'}]$ 的存在，所以可以把同种颜色对应的点存一起，直接同颜色内枚举可以消掉，复杂度 $\Theta(\sum c^2)$，$\sum c^2$ 表示每种颜色数量的平方和。

发现不能再优化了，考虑递推法，我们可以先考虑这样的问题：有一个 $01$ 矩阵，求开头结尾都是 $1$ 的路径的数量。

这个问题设 $dp_{i,j}$ 表示出发点的值是 $1$，结尾是 $dp_{i,j}$ 的路径数量，也就是每个在 $(i,j)$ 左上角的 $1$ 到这个点的路径个数和。显然有 $dp_{i,j}=[a_{i,j}=1]+dp_{i,j-1}+dp_{i-1,j}$，其中 $[a_{i,j}=1]$ 主要是为了给在 $(i,j)$ 右下角的计算贡献。你也可以理解为把矩阵拆成 $1$ 的数量个开头的小学问题的合并。

那么根据上面的做法，我们枚举颜色，对于每种颜色我们把这种颜色在矩阵上的值设为 $1$，其余都是 $0$，这个问题就得已解决，复杂度 $\Theta(Tn^2)$，$T$ 表示颜色数量。

此时我们已经有两个暴力。考虑分治，统计颜色 $i$ 对应出现次数 $c_i$，对于 $c_i\leq B$，可以考虑第一种做法，而其他情况可以考虑第二种。

分析复杂度。对于 $c_i\leq B$，因为 $x^2+(p-x)^2\leq p^2(x,p\in N^*,x\leq p)$，所以当每个 $c_i$ 尽量都是 $B$ 个的时候复杂度最高为 $\Theta(n^2B)$。对于其他情况，容易发现这样的颜色不超过 $\frac{n}{B}$ 个，所以复杂度最高是 $\Theta(\frac{n^4}{B})$。

那么这样合并的复杂度只有 $\Theta(n^2B+\frac{n^4}{B})$ 了，取 $B=n$，复杂度为 $\Theta(n^3)$。

[code](/paste/3pw740ge)。

关于 $x^2+(p-x)^2\leq p^2(x,p\in N^*,x\leq p)$ 的证明，把这个式子拆掉，变成 $2x(x-p)+p^2\leq p^2$，因为 $1\leq x\leq p$，所以 $2x(x-p)\leq0$，即证。

---

## 作者：llingy (赞：5)

UPD：更正时间复杂度计算错误。

[可能更好的阅读体验](https://www.llingy.ml/posts/3648470459/)


还是不够熟练。

## 题意简述

一个 $n\times n$ 的网格图，每个格子上有颜色，求满足起点和终点颜色均相同且只向下和向右走的路径条数。可以走 $0$ 步。$n\le 400$。

## 解法

* 设起点为 $(x,y)$ 终点为 $(z,w)$，则从 $(x,y)$ 到 $(z,w)$ 仅向下和向右走的路径条数为 $\dbinom{x-z+y-w}{x-z}$，可以理解为从起点到终点总共要走 $(x-z+y-w)$ 步，而其中有 $(x-z)$ 步是向下走的，这 $(x-z)$ 步可以在任意时刻走，所以相当于在 $(x-z+y-w)$ 步中选出 $(x-z)$ 步的方案数。
* 颜色之间是独立的，可以分开考虑。
* 对于每种颜色，枚举起点和终点，容易根据上式计算答案，时间复杂度 $O(n^4)$。
* 不过我们忽略了一种最朴素的解题思路。记 $f_{i,j}$ 为以 $(i,j)$ 结尾的合法路径条数，转移为 $f_{i,j}=f_{i,j}+f_{i,j-1}+f_{i-1,j}$。对于所有颜色为当前枚举的颜色的位置 $(i,j)$，初值为 $1$，否则为 $0$。对于每个颜色都要做一遍，时间复杂度 $O(n^4)$。
* 对于这种分颜色处理的问题，很经典的解决方式是对颜色出现次数进行根号分治。记阈值为 $B$，则最多有 $\dfrac {n^2}{B}$ 种颜色出现次数超过 $B$ 次，对这部分做 DP，而对出现次数小于 $B$ 次使用组合数计算。时间复杂度 $O(nB^2+\dfrac{n^4}{B})$，当 $B=n$ 时取到最优，为 $O(n^3)$。

## Code
```cpp
constexpr int N=405;using ll=long long;constexpr ll mod=998244353;
inline ll qpow(ll a,ll b)
{
    ll ret=1;a%=mod;
    while(b)
    {
        if(b&1) ret=ret*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ret;
}
int a[N][N];ll f[N][N];
struct dat{int x,y;};
vector<dat>id[N*N];
ll fac[N<<1],ifac[N<<1];
inline ll abs(ll x){return x<0?-x:x;}
inline ll binom(ll n,ll m){return (m<0||n<m)?0:fac[n]*ifac[n-m]%mod*ifac[m]%mod;}
inline ll calc(ll x,ll y,ll z,ll w){return binom(z-x+w-y,z-x);}
inline void init(const int n)
{
    fac[0]=ifac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    ifac[n]=qpow(fac[n],mod-2);
    for(int i=n-1;i>0;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
}
inline void work()
{
    ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
    int n;cin>>n;init(n*2);
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>a[i][j],id[a[i][j]].emplace_back((dat){i,j});
    ll ans=0;
    for(int i=1;i<=n*n;i++)
    {
        if(!id[i].size()) continue;
        int sz=int(id[i].size());
        if(sz<=n) for(int j=0;j<sz;j++) for(int k=0;k<sz;k++) ans=(ans+calc(id[i][j].x,id[i][j].y,id[i][k].x,id[i][k].y))%mod;
        else
        {
            memset(f,0,sizeof(f));
            for(const dat&j:id[i]) f[j.x][j.y]=1;
            for(int j=1;j<=n;j++) for(int k=1;k<=n;k++) f[j][k]=(f[j][k]+f[j-1][k]+f[j][k-1])%mod;
            for(int j=1;j<=n;j++) for(int k=1;k<=n;k++) if(a[j][k]==i) ans=(ans+f[j][k])%mod;
        }
    }
    cout<<ans<<endl;
}
```

---

## 作者：rui_er (赞：5)

首先，每种颜色互不干扰，因此考虑对每种颜色统计答案。

有两种解法：

- 枚举起始格子 $(x,y)$ 和结尾格子 $(z,w)$，由组合数易知共有 $\binom{z-x+w-y}{z-x}$ 种路径。时间复杂度为 $\mathcal O(k^2)$，其中 $k$ 为这种颜色格子数量。
- 动态规划统计这种颜色的格子到每个格子的路径数。时间复杂度为 $\mathcal O(n^2)$。

进行根号分治。当 $k\le n$ 时，第一种解法总复杂度不超过 $\mathcal O(n^3)$；当 $k > n$ 时，此类情况不超过 $n$ 次，第二种解法总复杂度不超过 $\mathcal O(n^3)$。

```cpp
// Problem: AT_abc259_h [ABC259Ex] Yet Another Path Counting
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc259_h
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const ll N = 405, mod = 998244353;

ll n, a[N][N], dp[N][N], fac[N*2], ifac[N*2], ans;
vector<tuple<ll, ll> > pos[N*N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
void initC(ll x) {
	fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	rep(i, 2, x) {
		fac[i] = fac[i-1] * i % mod;
		ifac[i] = (mod - mod / i) * ifac[mod%i] % mod;
	}
	rep(i, 2, x) ifac[i] = ifac[i-1] * ifac[i] % mod;
}
ll C(ll x, ll y) {
	if(x < 0 || y < 0 || x < y) return 0;
	return fac[x] * ifac[y] % mod * ifac[x-y] % mod;
}

int main() {
	initC(N*2-1);
	scanf("%lld", &n);
	rep(i, 1, n) {
		rep(j, 1, n) {
			scanf("%lld", &a[i][j]);
			pos[a[i][j]].emplace_back(i, j);
		}
	}
	rep(c, 1, n*n) {
		if(!pos[c].empty()) {
			if((ll)pos[c].size() <= n) {
				ll sz = pos[c].size();
				rep(i, 0, sz-1) {
					rep(j, 0, sz-1) {
						ll x = get<0>(pos[c][j]) + get<1>(pos[c][j]) - get<0>(pos[c][i]) - get<1>(pos[c][i]);
						ll y = get<0>(pos[c][j]) - get<0>(pos[c][i]);
						ans += C(x, y);
						ans %= mod;
					}
				}
			}
			else {
				rep(i, 1, n) {
					rep(j, 1, n) {
						dp[i][j] = (a[i][j] == c);
						dp[i][j] += dp[i-1][j]; dp[i][j] %= mod;
						dp[i][j] += dp[i][j-1]; dp[i][j] %= mod;
						if(a[i][j] == c) {
							ans += dp[i][j];
							ans %= mod;
						}
					}
				}
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：analysis (赞：2)

## sol

首先，容易想到，对于两个点 $P_1$，$P_2$，他们之间路径条数为：
$$
\begin{pmatrix}\Delta{x} + \Delta{y} \\ \Delta{x}\end{pmatrix}
$$
其中 $\Delta{x}$ 为两点横坐标差，$\Delta{y}$ 同理。

也即，对于给定两点，我们可以在 $O(1)$ 时间复杂度内解决问题。

要在点集 $S$ 中枚举两个点，时间复杂度为：$|S|^2$。

如果我们直接暴力的去做，时间复杂度为 $O(n^4)$，显然无法完成。

瓶颈在于枚举点集中的两个点，我们考虑优化此过程。

想要上述做法通过，则点集大小 $|s|$ 应当受到限制。

考虑根号分治，设对所有点集大小 $|s| \leq S$ 的点集应用此做法，时间复杂度为 $\sum_ic_i^2$（$c_i$ 表点集大小）。

$c_i \leq S$，所以上式写作 $\sum_{i=1}^{S}a_ii^2$，$a_i$ 为点集大小为 $i$ 的颜色数。
$$
\sum_{i=1}^{S}a_ii^2\\
= \sum_{i=1}^{S}a_ii\sum_{j=1}^{i}1\\
= \sum_{j=1}^{S}\sum_{i=j}^{S}a_ii\\
$$
显而易见，$\sum_{i=j}^{S}a_ii \leq \sum_{i=1}^{S}a_ii \leq n^2$（点集大小总和不可能超过 $n^2$）。

于是上述做法的时间复杂度可以视为 $O(n^2S)$。

对于点集大小大于 $S$ 的颜色个数不超过 $\frac{n^2}{S}$，我们可以直接应用 $O(n^2)$ 的在原矩阵上的朴素 DP，时间复杂度为 $O(\frac{n^4}{S})$。

加起来为 $O(n^2S + \frac{n^4}{S})$，发现当 $S = n$ 时，上述做法时间复杂度为 $O(n^3)$，可以通过。

```cpp
#include<bits/stdc++.h>
#define int long long
const int mod = 998244353;
#define pii pair<int,int>
#define xx first
#define yy second
using namespace std;
int n;
int fact[805],inv[805],ifact[805];
int col[160005];
vector<pii> pos[160005];
int r[160005];
int C(int n,int m)
{
    if(n < m)return 0;
    return fact[n] * ifact[m] % mod * ifact[n - m] % mod;
}
int ans;
int f[405][405];
int a[405][405];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    fact[0] = fact[1] = ifact[0] = ifact[1] = inv[1] = 1;
    for(int i=2;i<=2 * n;i++)
    {
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        fact[i] = fact[i-1] * i % mod;
        ifact[i] = ifact[i-1] * inv[i] % mod;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin >> a[i][j];
            col[a[i][j]]++;
            pos[a[i][j]].push_back(pii(i,j));
        }
    }
    for(int c=1;c<=n*n;c++)
    {
        if(col[c] <= n)
        {
            for(int i=0,sz=pos[c].size();i<sz;i++)
            {
                ans = (ans + 1) % mod;
                for(int j=i+1,sz=pos[c].size();j<sz;j++)
                {
                    if(pos[c][i].xx <= pos[c][j].xx && pos[c][i].yy <= pos[c][j].yy)
                    {
                        int dx = abs(pos[c][i].xx - pos[c][j].xx);
                        int dy = abs(pos[c][i].yy - pos[c][j].yy);
                        ans = (ans + C(dx + dy,dx)) % mod;
                    }
                }
            }
        }
        else
        {
            for(int i=1;i<=n;i++)
            {
                for(int j=1;j<=n;j++)
                {
                    f[i][j] = 0;
                    if(a[i][j] == c)f[i][j] = 1;
                    f[i][j] = (f[i][j] + f[i-1][j] + f[i][j-1]) % mod;
                    if(a[i][j] == c)ans = (ans + f[i][j]) % mod;
                }
            }
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Day_Tao (赞：2)

### 题目大意
题面已经很简洁了，所以就不在此所说啦。

### Sol

看到数据范围，就应该想到应该是 $O(n^3)$ 的做法。

首先我们可以想到，可以对每一个数字都开一个 $vector$ 存下来然后再进行处理。处理的思路也很明确，就是通过组合数求出每一条路径的数量。但如果真的是这么简单，那么这道题也不会评紫了。考虑这样做的时间复杂度，是 $O(n^2\times sum_i ^ 2)$，$sum_i$ 表示编号为 $i$ 的点的个数。对于整个 $a$ 数组是同一个数的情况，复杂度会变为 $O(n^4)$，肯定过不了。现实也是如此，加了快读我也有 $18$ 个点 T 了。

对于这种求路径的题，不难想到另外一种方法，也是最先能想到的方法，就是 DP。虽然 DP 的 $n^2$ 复杂度在处理两个点之间的总路径时远远不如组合数的方法，但是对于这样点较为稠密的情况，去求所有点的总路径就能体现出它的优势了。设 $f_{i,j}$ 表示到 $(i,j)$ 点的答案，那么转移方程就是：
$$f_{i,j}=f_{i,j}+f_{i-1,j}+f_{i,j-1}$$
其中 $f_{i,j}$ 初始值为 $[a_{i,j}=x]$，$x$ 表示当前枚举到的数字。

但是不难发现，这两种方法单独使用的最坏时间复杂度都是 $O(n^4)$ 的，但是又各有长处，这时我们就会想到类似于根号分治的思想。对于一个稠密的数字可以使用 $O(n^2)$ 的 DP，对于一个稀疏的数字则可以采用 $O(sum_i ^2)$ 的组合数来求。由于我们的期望复杂度应为 $O(n^3)$，所以我们就设阈值为 $n$，当然另外正面的证法其他题解也有很清楚的证明，我也就不废话啦。

### AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define mp(x, y) make_pair(x, y)
#define pqg priority_queue<int, vector<int>, greater<int>>
#define pql priority_queue<int, vector<int>, less<int>>
#define ls root << 1
#define rs root << 1 | 1
#define scnaf scanf
#define rt register int
#define int long long
const int MAX = 401;
const int INF = 0x7fffffff;
const int mod = 998244353;
int n, x[MAX][MAX], dp[MAX][MAX];
struct node
{
    int x, y;
};
vector<node> a[MAX * MAX];
int fac[MAX * 2], inv[MAX * 2];//由于 C(N,M) 的时候 N 的取值最大会取到 2n，所以这个空间要记得开两倍
inline int qpow(int a, int b)
{
    int sum = 1;
    while (b)
    {
        if (b & 1)
            sum *= a, sum %= mod;
        a *= a, a %= mod, b >>= 1;
    }
    return sum;
}
inline void init()
{
    int n = MAX * 2 - 1;
    fac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = fac[i - 1] * i % mod;
    inv[n] = qpow(fac[n], mod - 2);
    for (int i = n - 1; i >= 1; i--)
        inv[i] = inv[i + 1] * (i + 1) % mod;
    return;
}
inline int C(int n, int m)
{
    if (n < 0 || m < 0 || n < m)
        return 0;
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
} //这三部分是组合数的基础内容，不太了解的可以移步   B3717 组合数问题
signed main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    scanf("%lld", &n);
    init();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            scanf("%lld", &x[i][j]);
            a[x[i][j]].push_back({i, j});        //存数
        }
    int ans = 0;
    for (int i = 1; i <= n * n; i++)
    {
        if (a[i].empty())
            continue;
        int s = a[i].size();
        if (s <= n)                              //组合数部分
        {
            for (int j = 0; j < s; j++)
                for (int k = 0; k < s; k++)
                    ans += C(a[i][k].x + a[i][k].y - a[i][j].x - a[i][j].y, a[i][k].x - a[i][j].x) % mod, ans %= mod;
        }//由于我们无法直接知道每个点的具体位置，无法精确找出要算的所有点对，所以干脆所有的点对都跑一遍，而对于 (a,b)，(b,a) 两个点对，
        else//一定有一个的 a.x - b.x 小于等于 0 的，所以在组合数的计算中加入特判，这样就能算出对于数字 i 的总方案数了。
        {
            for (int j = 1; j <= n; j++)         //DP部分
                for (int k = 1; k <= n; k++)
                {
                    if (x[j][k] == i)
                        dp[j][k] = 1;
                    else
                        dp[j][k] = 0;
                    dp[j][k] = (dp[j][k] + dp[j - 1][k] + dp[j][k - 1]) % mod;
                    if (x[j][k] == i)
                        ans += dp[j][k], ans %= mod;
                }
        }
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}
```


---
### END

---

## 作者：Purslane (赞：1)

## Solution

根号分治。

第一种做法，也是最自然的，枚举两两颜色相同的数。假设点 $(a,b)$ 要走到点 $(c,d)$，方案数是 $C_{c+d-a-b}^{c-a}$。

第二种做法，对于每种颜色分开考虑。我们设 $dp_{a,b}$ 是从某个钦定颜色走到格子 ${a,b}$ 的方案数。显然有 $dp_{a,b}=dp_{a,b-1}+dp_{b,a-1}+[col_{a,b}=tag]$。

这两种做法都是 $O(n^4)$ 的。

但是你细品，如果同种颜色的数很少，那么第一种做法很快。

如果颜色种类很少，也就是同种颜色的数很多，那么第二种做法很快。

这种根据数据大小确定复杂度的，而且正好存在各有所长的两种做法，考虑使用根号分治。

假设一个阈值 $B$。那么 $\ge B$ 的数用第二种做法。最多有 $\frac{n^2}{B}$ 种这样的颜色，所以复杂度为 $O(\frac{n^4}{B})$。

$< B$ 的数用第一种方法。假设每种颜色的个数是 $x_i$，那么你要在 $\sum x_i$ 一定的时候最大化 $\sum x_i^2$ 来估算最差复杂度。

由于 $(a+b)^2 \ge a^2+b^2$，那么应当每个数都取到最大值。也就是 $x_i=B$。这样最多有 $\frac{n^2}{B} \times B^2=n^2B$ 的计算次数。

总复杂度是 $O(n^2B+\frac{n^4}{B})$。当 $B=n$ 时取最小值  $O(n^3)$。

代码非常简单。

---

## 作者：FiraCode (赞：1)

## 思路：
由于只要求起点和终点的颜色相同，那么可以枚举颜色。

对于每种颜色，分别考虑。

设当前颜色为 $c$。

考虑两种暴力：

*	1.对于当前颜色，设 $f_{i,j}$ 表示起点的颜色是 $c$，终点为 $(i,j)$ 时的路径数，初始化就是对于所有颜色为 $c$ 的位置 $f_{i,j}=1$，然后转移就是 $f_{i,j} += f_{i - 1,j} + f_{i,j-1}$；时间复杂度 $\mathcal{O(n^2)}$。
*	2.由于只要求起点和终点颜色相同那么可以枚举起点和终点然后组合数求个路径数即可，时间复杂度为 $\mathcal{O(n^4)}$。

然后我们发现当当前颜色不超过 $n$ 个时，暴力 $2$ 的时间总复杂度仅为 $\mathcal{O(n^3)}$，而超过 $n$ 个时，由于最多有 $n$ 个颜色的点数 $\ge n$（要不然总点数就超过 $n^2$ 了），那么用暴力 $1$ 总时间复杂度也为 $\mathcal{O(n^3)}$，所以两个结合起来就可以过啦。

总时间复杂度为 $\mathcal{O(n^3)}$。

## Code:
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define int ll

const int N = 1010, mod = 998244353;
int fac[N], inv[N];

int n;
int a[410][410];
int f[410][410];
vector<pair<int, int>> e[160010];

int C(int n, int m) {
	if (n < m) return 0;
	if (n < 0 || m < 0) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int qmi(int a, int k, int p) {
    int res = 1;
    while (k){
        if (k & 1) res = (ll)res * a % p;
        a = (ll)a * a % p;
        k >>= 1;
    }
    return res;
}

signed main() {
    fac[0] = inv[0] = 1;
    for (int i = 1; i < N; ++i) {
        fac[i] = (ll)fac[i - 1] * i % mod;
        inv[i] = (ll)inv[i - 1] * qmi(i, mod - 2, mod) % mod;
    }
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			scanf("%lld", &a[i][j]);
			e[a[i][j]].push_back({i, j});
		}
	}

	ll ans = 0;

	for (int i = 1; i <= n * n; ++i) {
		if (!e[i].size()) continue;
		if (e[i].size() <= n) {
			for (auto [X1, Y1] : e[i])
				for (auto [X2, Y2] : e[i]) {
					ans = (ans + C(X2 - X1 + Y2 - Y1, X2 - X1)) % mod;
				}
		} else {
			for (int j = 1; j <= n; ++j)
				for (int k = 1; k <= n; ++k) {
					f[j][k] = (a[j][k] == i);
					f[j][k] = (f[j][k] + f[j][k - 1]) % mod;
					f[j][k] = (f[j][k] + f[j - 1][k]) % mod;
					ans += f[j][k] * (a[j][k] == i);
					ans %= mod;
				}
		}
	}

	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Register_int (赞：0)

单独考虑每种颜色 $c$，数量为 $k$。我们可以将所有颜色为 $c$ 的格子按字典序排序，之后枚举起点终点计算结果。时间复杂度 $O(k^2)=O(n^4)$，优秀到爆炸。

另一方面，我们可以考虑 dp。设 $dp_{i,j}$ 表示从颜色为 $c$ 的格子到 $(i,j)$ 的路径总数，有转移式 $dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}+[a_{i,j}=c]$，时间复杂度 $O(n^2\times n^2)=O(n^4)$，依然优秀到爆炸。

考虑将两种算法结合起来，当 $k\le n$ 时使用第一种算法，否则使用第二种。这样，在极端情况下也只有 $n$ 种颜色达到 $O(n^2)$ 复杂度上限，总时间复杂度 $O(n\times n^2)=O(n^3)$，可以通过。

# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 4e2 + 10;
const int MAXM = 1.6e5 + 10;
const int mod = 998244353;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1) res = res * b % mod;
		b = b * b % mod, p >>= 1;
	}
	return res;
}

struct node {
	int x, y;
};

ll fac[MAXN << 1], ifac[MAXN << 1];

inline 
void init(int n) {
	*fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[n] = qpow(fac[n], mod - 2);
    for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod;
}

inline 
ll c(int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

inline 
ll ask(node p, node q) {
	if (p.x > q.x || p.y > q.y) return 0;
	return c(q.x - p.x + q.y - p.y, q.x - p.x);
}

vector<node> col[MAXM];

int n, a[MAXN][MAXN];

ll ans, dp[MAXN][MAXN];

int main() {
    scanf("%d", &n), init(n << 1);
    for (int i = 1; i <= n; i++) {
    	for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]), col[a[i][j]].push_back({ i, j });
	}
	for (int k = 1; k <= n * n; k++) {
		if (col[k].empty()) continue;
		if (col[k].size() <= n) {
			for (int i = 0; i < col[k].size(); i++) {
				for (int j = i; j < col[k].size(); j++) ans = (ans + ask(col[k][i], col[k][j])) % mod;
			}
		} else {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) dp[i][j] = (dp[i - 1][j] + dp[i][j - 1] + (a[i][j] == k)) % mod;
			}
			for (auto t : col[k]) ans = (ans + dp[t.x][t.y]) % mod;
		}
	}
	printf("%lld", ans);
}
```

---

## 作者：GIFBMP (赞：0)

注意到每种颜色之间是互相独立的，考虑对于每种颜色分别统计答案。

设这种颜色的方格共有 $k$ 个，显然可以枚举路径的两个端点 $(a,b)$，$(c,d)$，再乘上 $C_{b-a+d-c}^{b-a}$，统计到答案中，时间复杂度 $\Theta(k^2)$。

我们还可以设 $f_{i,j}$ 表示从这种颜色的格子走到 $(i,j)$ 的方案数，转移式显然，即 $f_{i,j}=f_{i-1,j}+f_{i,j-1}+[a_{i,j}=c]$。答案即为 $\sum\limits_{i=1}^n\sum\limits_{j=1}^n f_{i,j}[a_{i,j}=c]$。时间复杂度 $\Theta(n^2)$。

遇到这种有多种时间复杂度不同的暴力的情况，可以想到根号分治。设这个阈值为 $B$，则当这种颜色的方格数 $\le B$ 时，执行第一种算法，此时时间复杂度不超过 $O(n^2B)$，当方格数大于 $B$ 时，执行第二种算法，时间复杂度不超过 $O(\dfrac{n^4}{B})$。

$n^2B=\dfrac{n^4}{B}$，解得 $B=n$，此时时间复杂度最优，为 $\Theta(n^3)$。

Code:

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std ;
const int mod = 998244353 ;
int n , a[410][410] , c[810][810] , f[410][410] , ans ;
typedef pair <int , int> P ;
#define mp make_pair
#define fi first
#define se second
vector <P> v[410 * 410] ;
int main () {
	scanf ("%d" , &n) ;
	for (int i = 0 ; i <= 2 * n ; i++) c[i][0] = 1 ;
	for (int i = 1 ; i <= 2 * n ; i++)
		for (int j = 1 ; j <= i ; j++)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod ;
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 ; j <= n ; j++)
			scanf ("%d" , &a[i][j]) , v[a[i][j]].push_back (mp (i , j))  ;
	for (int i = 1 ; i <= n * n ; i++) {
		int len = v[i].size () ;
		if (!len) continue ;
		if (len < n) {
			for (int j = 0 ; j < len ; j++)
				for (int k = 0 ; k < len ; k++) {
					int x = v[i][j].fi , y = v[i][j].se , xx = v[i][k].fi , yy = v[i][k].se ;
					if (x <= xx && y <= yy) ans = (ans + c[xx - x + yy - y][xx - x]) % mod ;
				}
		}
		else {
			for (int j = 1 ; j <= n ; j++)
				for (int k = 1 ; k <= n ; k++) {
					f[j][k] = (f[j][k - 1] + f[j - 1][k] + (a[j][k] == i)) % mod ;
					if (a[j][k] == i) ans = (ans + f[j][k]) % mod ;
				}
		}
	}
	printf ("%d\n" , ans) ;
	return 0 ;
} 
```

---

## 作者：dd_d (赞：0)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/16823698.html)
## Sol  
考虑两种暴力。  

- 直接枚举同类点，组合数计算两点之间的路径数。单次操作时间复杂度 $O(B^2)$。其中 $B$ 表示这类点的个数。
- 暴力 dp，记 $dp_{i,j}$ 表示到 $(i,j)$ 的方案数，若走到同类点那么加上方案数，单次操作复杂度 $O(n^2)$。  

然后考虑根号分治，当 $B \leq n$ 时，做第一种操作，单次复杂度 $O(n^2)$，不会超过 $n$ 次，总复杂度 $O(n^3)$。当 $B>n$ 时，最多做 $n$ 次，单次复杂度 $O(n^2)$，总复杂度 $O(n^3)$。  
综上，总复杂度 $O(n^3)$。  
## Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define lowbit(x) (x&(-x))
#define int long long
using namespace std;
inline char gc()
{
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=1e3+10,mod=998244353;
int n,C[N][N],ans,f[N][N],Map[N][N];
vector<pair<int,int> > G[N*N];
void work1(vector<pair<int,int> > g)
{
	for (int i=0;i<(int)g.size();i++)
		for (int j=i;j<(int)g.size();j++)
		{
			int x=g[i].first-g[j].first,y=g[i].second-g[j].second;
			if (x<0) x=-x,y=-y;
			else if (!x&&y<0) y=-y;
			if (y<0) continue;	
			ans=(ans+C[x+y][x])%mod;
		}
}
void work2(vector<pair<int,int> > g)
{
	memset(Map,0,sizeof(Map));
	for (auto x:g)
		Map[x.first][x.second]=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			f[i][j]=(f[i-1][j]+f[i][j-1])%mod;
			if (Map[i][j]) (f[i][j]+=1)%=mod,ans=(ans+f[i][j])%mod;
		}
}
signed main()
{
	n=read();
	for (int i=0;i<=2*n;i++)
	{
		C[i][0]=1;
		for (int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			int x=read();
			G[x].emplace_back(i,j);
		}
	for (int i=1;i<=n*n;i++)
	{
		if (G[i].empty()) continue;
		if (G[i].size()<=n) work1(G[i]);
		else work2(G[i]);
	}
	writeln(ans);
}





```

---

## 作者：AlicX (赞：0)

## Solution 

首先考虑暴力：

1. 枚举同种颜色的格子，假设两点为 $(i,j),(x,y)$，那么从 $(i,j)$ 到 $(x,y)$ 的方案数即为 $C_{x-i+y-j}^{x-i}$。考虑当前颜色有 $B$ 个，枚举的时间复杂度为 $O(B^2)$。

2. 考虑枚举每一种颜色，算出这种颜色到其他格子方案数，有递推方程：$f_{i,j}=f_{i-1,j}+f_{i,j-1}$，当 $a_{i,j}$ 为当前颜色时，$f_{i,j}=1$。枚举时间复杂度为 $O(n^2)$。

再考虑根号分治，把两个暴力拼在一起，当 $B \leq n$ 时执行第一种暴力，时间复杂度最坏为 $O(nB^2)$；当 $B>n$ 时执行第二种暴力，时间复杂度最坏为 $O(\frac{n^4}{B})$，当 $B=n$ 时，总时间复杂度为 $O(n^3)$。 

注意在处理逆元的时候应处理到 $2n$，因为需要计算 $inv_{x-i+y-j}$，而 $x-i+y-j$ 最大为 $2n-2$。

```cpp
#include<bits/stdc++.h> 
#define ll long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=410; 
const ll Mod=998244353; 
int n; 
ll f[N][N]; 
int a[N][N]; 
vector<pii> v,mp[N*N]; 
ll inv[N<<1],fac[N<<1]; 
il ll qmi(ll x,int k){ 
	ll res=1; 
	while(k){
		if(k&1) res=res*x%Mod; 
		x=x*x%Mod; k>>=1; 
	} return res; 
} 
il ll calc(int i,int j,int x,int y){ 
	int P=x-i+y-j,R=x-i; 
	return fac[P]*inv[P-R]%Mod*inv[R]%Mod; 
} 
il void init(){ 
	fac[0]=inv[0]=1; 
	for(int i=1;i<=2*n;i++) fac[i]=fac[i-1]*i%Mod; 
	inv[2*n]=qmi(fac[2*n],Mod-2); 
	for(int i=2*n-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%Mod; 
} 
signed main(){ 
	scanf("%d",&n); 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&a[i][j]); 
			if(!mp[a[i][j]].size()) v.push_back({i,j}); 
			mp[a[i][j]].push_back({i,j}); 
		} 
	} init(); ll ans=0; 
	for(auto u:v){ 
		int col=a[u.x][u.y]; 
		if(mp[col].size()<=n){
			for(auto i:mp[col]) 
				for(auto j:mp[col]) 
					if(i.x<=j.x&&i.y<=j.y) ans=(ans+calc(i.x,i.y,j.x,j.y))%Mod; 
		} else{ 
			for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]=0; 
			int col=a[u.x][u.y]; for(auto i:mp[col]) f[i.x][i.y]=1; 
			for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]=(f[i][j]+f[i-1][j]+f[i][j-1])%Mod,ans=(ans+((a[i][j]==col)?f[i][j]:0))%Mod; 
		} 
	} printf("%lld\n",ans); return 0; 
} 
```


---

