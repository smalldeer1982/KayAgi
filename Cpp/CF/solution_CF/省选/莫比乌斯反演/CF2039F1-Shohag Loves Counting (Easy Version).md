# Shohag Loves Counting (Easy Version)

## 题目描述

此题为简单版本。简单版本和困难版本的区别在于 $t,m,\sum m$ 的数据范围。

对于一个包含 $n$ 个元素的数组 $a$，定义 $f(k)$ 表示数组 $a$ 所有长度为 $k$ 的子串的最大值的最大公因数。

例如，对于数组 $[2,1,4,6,2]$，$f(3)=\gcd(\max(2,1,4),\max(1,4,6),\max(4,6,2))=\gcd(4,6,6)=2$。

定义一个数组 $a$ 是好的，当且仅当 $\forall 1\leq i<j\leq n，f(i)\neq f(j)$。现在，给定一个数 $m$，请你算出任意非空的仅包含 $1$ 到 $m$ 内的所有整数的好的数组有多少个。由于这样的数组可能很多，答案请对 $998244353$ 取模。

例如，当 $m=2$ 时，所有满足上述要求的数组有 $[1],[1,2],[2],[2,1]$。

## 说明/提示

$1\leq t\leq 10^4,1\leq m,\sum m\leq 10^5.$

## 样例 #1

### 输入

```
3
2
5
9```

### 输出

```
4
29
165```

# 题解

## 作者：迟暮天复明 (赞：3)

大家好，我居然做出来了这道题！

显然数列是单谷的，并且从大到小排序后所有前缀的 gcd 两两不同。如果你没有发现这个结论，那么说明你需要再转化一下题目描述的内容。

设当前放的数是 $i$，当前 gcd 是 $g$。设 $F_{i,g}$ 是这个状态的方案数。那么有 
$$F_{i,g}=2\times \sum_{j>i}\sum_{h>g} F_{j,h}[\gcd(i,h)=g]+[i=g]$$

解释一下这个式子：$f_{i,g}$ 的状态可以由任意一个前置状态在中间放进去一个 $i$ 而形成，而放进去一个数显然有两种方法。最后再加上单独一个 $i$ 形成的数列。

接下来可以发现 $f$ 数组是可以后缀和优化的，因为对于每一个 $j>i$ 其实地位是一样的。于是记 $\sum_{j>i}F_{j,h}=G_h$。

这样原式里面要算的东西就只剩下
$$
\begin{aligned}
& \sum_{h>g} G_h[\gcd(i,h)=g] \\
= & \sum_{h>1} G_{gh}[\gcd(i/g,h)=1]\\
= & \sum_{dg \mid i}\mu(d)\sum_{dh\neq 1}G_{dgh}
\end{aligned}
$$

第二个等号是简单的莫比乌斯反演，虽然这个东西我学了将近一个下午。

不过现在这个题目还无法解决，因为枚举 $h$ 的复杂度是错的。所以还要计算一个东西：$\sum_h G_{dgh}$，也就是 $\sum_h G_{hC}$。这个可以在 $i\to i-1$ 的时候，和 $G$ 数组一起处理。

由于对于 $i$ 来说有效的 dp 值只有 $g\mid i$ 的所有 $g$，所以前面所有的枚举都只在 $i$ 的因数里进行，于是时间复杂度是 $O(\sigma(i)^2)$。同时也容易证明 $i\to i-1$ 时计算 $G$ 数组和 $\sum G_{iC}$ 的值的复杂度也是 $O(\sigma(i)^2)$ 的。于是解决整个问题的复杂度就是 $O(\sum_{i=1}^M\sigma(i)^2)$。

[代码](https://www.luogu.com.cn/paste/5cx1myv4)出奇的短。

---

## 作者：tr1pTreap (赞：2)

超级困难题。官方题解做法。

题意：对于长度为 $n$ 的一个数列 $A$ ，定义 $f(k)$ 为所有长度为 $k$ 的子区间的 $\max$ 的 $\gcd$ 。定义一个序列 $A$ 是好的，当且仅当对于 $k \in [1, n]$ ，$f(k)$ 两两互异。给定数列 $A$ 的值域 $m$ （即 $A_i \in [1, m] \space \forall i \in [1, n]$），求任意长度的好的序列的个数 $\mod 998244353$ 。

首先一个有所有任意长度的序列的集合非常难数数。考虑找一个性质去限制这个集合中序列的长度。\
考察一下 $f(k)$ 会被怎么计算。对于序列中的一个 $A_i$ ，设序列中前面第一个大于它的位置是 $\text{bef}_i$ ， 后面第一个大于它的位置是 $\text{aft}_i$ 。 则对于任何区间 $[l, r]$ 满足 $l \in [\text{bef}_i + 1, i], r \in [i, \text{aft}_i - 1]$ 它的最大值一定是 $A_i$ 。\
如果贡献多于一个 $A_i$ 给 $\gcd$ 答案不会因此改变。考虑什么时候不贡献 $A_i$ ，可以知道是当 $len_i = (\text{aft}_i - 1) - (\text{bef}_i + 1) + 1 < k$ 的时候 $A_i$ 作为最大值不被包含在任何一个合法长度等于 $k$ 的区间里面。\
结合所有 $f(k)$ 两两互异的限制，可以知道从 $f(k)$ 转移到 $f(k + 1)$ 的时候，一定有至少一个原来有贡献的区间从中剔除，不然不能满足限制。也就是说，一定至少有一个 $len_i = 1$ ，至少有一个 $len_i = 2$ ，一直到 $len_i = n$ 。所以就是有**恰好一个** $len_i = 1$ ，$len_i = 2$ ... $len_i = n$ 。同时两两互异的限制还提示每次贡献的数必须不同，所以 $A_i$ 两两互异。在 $\gcd$ 两两互异的情况下，值域 $[1, m]$ 中存在大概 $\log$ 个 $\gcd$ ，所以序列 $A$ 的长度大概是 $\log m$ 。

现在问题转换成了，求长度为 $\log m$ 中的 $f(k)$ 不同的 $A$ 。考虑 $[1,m]$ 中选出 $n$ 个数，如何排列使得有 $S = \{ len_i \} = \{1, 2, ..., n\}$ 。一个数（最大值）的情况显然，两个数则第二个数可以插入在第一个数前面或者后面。归纳可得一个数可以插入在前一个数的左边或者右边，一共两种插法。所以对于一种数的选法一共有 $2^{n - 1}$ 种插法可以满足条件。为方便我们可以只去算数列单调递增的情况然后乘上 $2^{n - 1}$ 。

则现在问题又转化成了，计算后缀 $\gcd$ 不同的单调递增的 $A$ 。我们可以通过 dp 来计算。定义 $f_{i, g}$ 表示序列的值从 $i$ 开始，序列的 $\gcd$ 是 $g$ 。有下列转移：
$$f_{i, g} = \sum_{j > i} f_{j, h} + 1$$
其中 $h$ 是满足 $g < h \le m$ 且 $\gcd(i, h) = g$ 的整数。

朴素地用后缀和优化然后枚举转移是 $O(m^2 \log m)$ 的，其中 $O(m \log m)$ 是状态数，$O(m)$ 是枚举可行 $h$ 的复杂度。

注意到 $g | i$ 且 $g | h$ ，有 $g | \gcd(i, h)$ 的答案可以 $O(1)$ 转移，则我们可以通过容斥计算出 $g = \gcd(i, h)$ 的所有 $h$ 的答案之和。

设 $i = rem \times g$ ，$rem$ 可以被拆成某些 $p,q$ 的和，此时 $g = \gcd(i, h)$ 的答案可以用 $S_{g | \gcd(i, h)} - S_{g | p \times \gcd(i, h)} - S_{g | q \times \gcd(i, h)} + S_{g | p \times q \times \gcd(i, h)}$ 的容斥方式计算。更多的因数同理。快速计算容斥系数可以使用莫比乌斯函数。

代码参考了 [grass8cow](https://www.luogu.com.cn/user/223624) 大佬的赛时实现，拜谢神仙。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int mad(int &a,int b){a+=b;if(a>=mod)a-=mod;return a;}
vector<int>d[100100],dd[100100];
int pr[100100],top,mu[100100];bool np[100100];
void sieve(){
    mu[1]=1;
    for(int i=2;i<100100;i++){
        if(!np[i])pr[++top]=i,mu[i]=-1;
        for(int j=1;j<=top&&i*pr[j]<100100;j++){
            np[i*pr[j]]=true;
            if(i%pr[j]==0)break;
            mu[i*pr[j]]=-mu[i];
        }
    }
}
// d 是因子 dd 是 mu!=0 的非平方因子
int tag[100100],f[100100],fs[100100];
// tag[g] 是前面算出来 g|h 所有 h 的 dp 值
// f 是当前 dp 值
// fs 是后缀和后的 dp 值
void solve(){
    int m;cin>>m;
    for(int i=1;i<=m;i++)tag[i]=fs[i]=f[i]=0;
    int ans=0;
    for(int i=m;i>=1;i--){ // i
        for(int g:d[i]){ // g
            fs[g]=0;
            for(int hh:dd[i/g]){
                int h=hh*g;
                if(mu[hh]>0)mad(fs[g],tag[h]);
                else mad(fs[g],mod-tag[h]);
            }
            mad(fs[g],mod-f[g]);
            mad(fs[g],fs[g]);
            mad(ans,fs[g]);
            mad(f[g],fs[g]);
            for(int gg:d[g])mad(tag[gg],fs[g]);
        }
        mad(f[i],1);
        // cerr<<"F:"<<f[i]<<'\n';
        for(int k:d[i])mad(tag[k],1);
        ans++;
        // cerr<<ans<<'\n';
    }
    printf("%d\n",ans);
}
int main(){
    sieve();
    for(int i=1;i<=100005;i++)
        for(int j=i;j<=100005;j+=i){
            d[j].push_back(i);
            if(mu[i])dd[j].push_back(i);
        }
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
/*
1 2    2 1
1 2 3     2 1 3    3 2 1    3 1 2
mobius 是用来加速转移的
dp[i][h] 表示从 i 开始 gcd 为 h 的序列个数
dp[i'<i][gcd(i',h)] <- dp[i][h]
这里不能朴素转移 
*/
```

---

## 作者：UKE_Automation (赞：1)

### F CF2039F1 Shohag Loves Counting (Easy Version)

[$\text{Link }$](https://codeforces.com/problemset/problem/2039/F1)

首先需要关注到一个重要性质：最大值一定在数组两端。原因在于我们要求所有 $f$ 值互不相同，而为了满足 $f(n-1)\ne f(n)$ 我们就必须要让最大值放在两边。进一步的可以得出结论：我们的数组一定是一个单谷，且数字两两不同。

然后考虑 dp，我们每次往里面加入一个最小值，这样的话新的 $f(2)\sim f(n)$ 就是原来的 $f(1)\sim f(n-1)$，我们只要让新的 $f(1)\ne f(2)$ 即可，新的 $f(1)$ 就是所有数字的 $\gcd$。所以设 $dp(i,d)$ 表示当前最小值为 $i$，所有数字的 $\gcd=d$ 的方案数。转移非常简单：
$$
2\times dp(i,d)\to dp(j,\gcd(d,j))
$$
直接做复杂度是 $O(m^2\sqrt m)$ 的，考虑优化。优化前我们先把刷表改为填表：
$$
dp(i,d)=\sum_{j={i+1}}^m\sum_{d\mid d'} dp(j,d')[\gcd(d',i)=d]
$$
先做一次后缀和优化，记 $S(i,d)=\sum\limits_{j=i+1}^m dp(j,d)$，则有：
$$
dp(i,d)=\sum_{d\mid d'}S(i,d')[\gcd(d',i)=d]
$$
然后看到后面的 $\gcd$，不难想到莫反，于是有：
$$
\begin{aligned}
dp(i,d)&=\sum_{d\mid d'}S(i,d')[\gcd(d',i)=d]\\
&=\sum_{d'=1}^{\lfloor\frac md\rfloor}S(i,d'd)[\gcd(d',\frac i d)=1]\\
&=\sum_{d'=1}^{\lfloor\frac md\rfloor}S(i,d'd)\sum_{p\mid \gcd(d',\frac i d)} \mu(p)\\
&=\sum_{p\mid \frac i d} \mu(p)\sum_{d'=1}^{\lfloor\frac m{dp}\rfloor}S(i,d'dp)\\
\end{aligned}
$$
这样的话再记 $S'(i,d)=\sum S(i,dj)$，我们的方程就可以变为：
$$
dp(i,d)=\sum_{p\mid \frac{i}{d}} \mu(p) S'(i,dp)
$$
这样的话我们求解的复杂度就是 $\sum\limits_{i=1}^m \sum\limits_{j\mid i} d(j)$，足够通过了。最后还需要注意上面我们其实还没有保证 $f(1)\ne f(2)$，这个是容易的，只需要在最后把 $S(i, d)$ 减掉即可。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

const int Maxn = 2e5 + 5;
const int Inf = 2e9;
const int Mod = 998244353;
il int Add(int x, int y) {return x + y >= Mod ? x + y - Mod: x + y;} il void pls(int &x, int y) {x = Add(x, y);}
il int Del(int x, int y) {return x - y < 0 ? x - y + Mod : x - y;} il void sub(int &x, int y) {x = Del(x, y);}
il int qpow(int a, int b) {int res = 1; for(; b; a = 1ll * a * a % Mod, b >>= 1) if(b & 1) res = 1ll * res * a % Mod; return res;}
il int Inv(int a) {return qpow(a, Mod - 2);}
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool typ = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	typ ? putchar('\n') : putchar(' ');
}
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int T, m;
int s[Maxn], sum[Maxn], f[Maxn];

vector <int> P[Maxn]; 
void divd(int x) {
	for(int i = 1; i <= x / i; i++) {
		if(x % i == 0) {
			P[x].push_back(i);
			if(i * i != x) P[x].push_back(x / i);
		}
	}
}
int mu[Maxn], prim[Maxn], tot, vis[Maxn];
void init(int N) {
	mu[1] = 1;
	for(int i = 2; i <= N; i++) {
		if(!vis[i]) prim[++tot] = i, mu[i] = -1;
		for(int j = 1; prim[j] * i <= N; j++) {
			vis[i * prim[j]] = 1;
			if(i % prim[j] == 0) {
				mu[i * prim[j]] = 0; break;
			}
			mu[i * prim[j]] = -mu[i];
		}
	}
}

void solve() {
	read(m);
	for(int i = 1; i <= m; i++) s[i] = sum[i] = 0;
	int ans = 0;
	for(int i = m; i >= 1; i--) {
		for(auto d : P[i]) {
			f[d] = (d == i);
			for(auto p : P[i / d]) {
				if(mu[p] == 1) pls(f[d], 2ll * s[d * p] % Mod);
				else if(mu[p] == -1) sub(f[d], 2ll * s[d * p] % Mod);
			}
			sub(f[d], 2ll * sum[d] % Mod);
			pls(ans, f[d]);
		}
		for(auto d : P[i]) {
			pls(sum[d], f[d]);
			for(auto _d : P[d]) {
				pls(s[_d], f[d]);
			}
		}
	}
	write(ans);
}

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	read(T);
	for(int i = 1; i <= 100000; i++) divd(i);
	init(1e5);
	while(T--) solve();
    Usd();
	return 0;
}

```

---

## 作者：SunsetGlow95 (赞：1)

我不会的题，那就是好题。

## 题意简述

假设有一个数组 $a$，$f(k)$ 表示 $a$ 所有长度为 $k$ 的子区间的最大值的 $\gcd$，$a$ 是好的当且仅当在定义域内 $f(k)$ 两两不同。求有多少个值域为 $[1,m]$ 的整数的任意长度的 $a$ 是好的。对 F1 Easy Version，$\sum m\le 10^5$。

## 观察

$f(k)$ 两两不同，首先要定长区间最大值集合两两不同。从 $k=2$ 考虑，就是要求 $\nexists i\ \text{s.t.}\ a_i\ge a_{i-1},a_i\ge a_{i+1}$。然后发现对后续的过程还要求 $a_i$ 两两不同。

手动模拟后总结一下：好的序列必须是一个严格单谷序列，并且从小到大排序后，所有后缀 $\gcd$ 两两不同。

## Easy Version

既然是后缀，$\sum m$ 也很小，考虑从大到小插入数。令 $f_i$ 维护当前后缀 $\gcd$ 为 $i$ 的序列个数，然后每次长度加一的时候因为最小值有两个位置可以插入（当前最小值的左右），所以 $\times$ 贡献过去。每次插入一个数 $i$，考虑 $f_j$ 向 $f_{\gcd(i,j)}$ 贡献。直接做是 $O(m^2\log m)$。

看到 $\gcd$ 一个想法是莫反。推一推式子，假设当前考虑对 $f_j$ 的增量，且暂且不考虑贡献时 $\gcd(i,j)<j$ 的限制：

$$\begin{aligned}&\sum_k f_k[\gcd(k,i)=j] \\
=& \sum_k f_{jk}[\gcd(k,\frac{i}{j})=1] \\
=& \sum_k f_{jk}\sum_{d|\gcd(k,\frac{i}{j})} \mu(d) \\
=& \sum_{dj|i} \mu(d)\sum_k f_{djk} \\ \end{aligned}$$

实时维护一下 $g_i=\sum_j f_{ij}$，遍历每个 $i$ 的因子 $j$，套一层遍历每个 $\frac{i}{j}$ 的因子 $d$，把 $\mu (d)g_{dj}$ 加入贡献中。最后把限制减掉 $f_j$ 对自身的贡献，这部分的贡献 $\times 2$。然后新建一个点的贡献就是给 $f_i$ 做一次 $+1$。细节上，这些都是同时做的，所以把所有的贡献暂存然后再一起加回去。

单次时间 $O(\sum_{1\le i\le n}\sum_{d|i}\sigma(d))$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MXN = 100005;
const int DVS = 998244353;
int T, N, cnt[MXN], sum[MXN], ans, delta[MXN], mu[MXN];
vector<int> fac[MXN];

inline void add(int i, int v) {
  cnt[i] = (cnt[i] + v) % DVS;
  for (int j : fac[i]) sum[j] = (sum[j] + v) % DVS;
}

int main() {
  mu[1] = 1;
  for (int i(1); i != MXN; ++i) {
    fac[i].push_back(i);
    for (int j(i + i); j < MXN; j += i) fac[j].push_back(i), mu[j] -= mu[i];
    mu[i] = (DVS + mu[i]) % DVS;
  }
  cin >> T;
  while (T--) {
    cin >> N;
    for (int i(1); i <= N; ++i) cnt[i] = 0, sum[i] = 0;
    for (int i(N); i; --i) {
      for (int j : fac[i]) {
        delta[j] = (DVS - cnt[j]) % DVS;
        for (int k : fac[i / j])
          delta[j] = (delta[j] + mu[k] * 1LL * sum[j * k]) % DVS;
        delta[j] = delta[j] * 2 % DVS;
      }
      delta[i] = (delta[i] + 1) % DVS;
      for (int j : fac[i]) add(j, delta[j]), delta[j] = 0;
    }
    ans = 0;
    for (int i(1); i <= N; ++i) ans = (ans + cnt[i]) % DVS;
    cout << ans << endl;
  }
  return 0;
}
```

---

