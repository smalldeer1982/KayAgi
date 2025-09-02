# [ABC226F] Score of Permutations

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc226/tasks/abc226_f

$ (1,2,\ \dots,\ N) $ を並び替えた長さ $ N $ の順列 $ P\ =\ (p_1,\ p_2,\ \dots,\ p_N) $ に対して、 $ P $ のスコア $ S(P) $ を次のように定めます。

- $ N $ 人の人とすぬけ君がいて、$ N $ 人の人には $ 1,2,\dots,N $ の番号がついています。はじめ、人 $ i $ $ (1\ \leq\ i\ \leq\ N) $ はボール $ i $ を持っています。  
   すぬけ君が叫ぶたびに、$ i\ \neq\ p_i $ であるようなすべての人 $ i $ は人 $ p_i $ に持っているボールを同時に渡します。  
   すぬけ君は、$ 1 $ 回以上叫んだ後にすべての人 $ i $ がボール $ i $ を持っている状態になると叫ぶのをやめます。  
   すぬけ君が叫ぶのをやめるまでに叫んだ回数が順列のスコアとなります。ここでスコアは有限の値を取ることが保証されます。

$ P $ としてあり得るものは $ N! $ 通りありますが、それらのスコアを $ K $ 乗した値の総和を $ 998244353 $ で割ったあまりを計算してください。

- 厳密に言い換えると、$ (1,2,\ \dots,\ N) $ を並び替えた長さ $ N $ の順列全体の集合を $ S_N $ として
  
  $ \displaystyle\ \left(\sum_{P\ \in\ S_N}\ S(P)^K\ \right)\ \bmod\ {998244353} $
  
  を計算してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 50 $
- $ 1\ \leq\ K\ \leq\ 10^4 $
- 入力はすべて整数である。

### Sample Explanation 1

$ N\ =\ 2 $ のとき $ P $ としてあり得る順列は $ (1,2),(2,1) $ の $ 2 $ つです。 順列 $ (1,2) $ のスコアは次のように決まります。 - はじめ人 $ 1 $ はボール $ 1 $ を、人 $ 2 $ はボール $ 2 $ を持っています。 すぬけ君が $ 1 $ 回目に叫んだ後に、人 $ 1 $ はボール $ 1 $ を、人 $ 2 $ はボール $ 2 $ を持っています。 このとき、すべての人が自身の番号と同じ番号が書かれたボールを持っているので、すぬけ君は叫ぶのをやめます。 よってスコアは $ 1 $ となります。 順列 $ (2,1) $ のスコアは次のように決まります。 - はじめ人 $ 1 $ はボール $ 1 $ を、人 $ 2 $ はボール $ 2 $ を持っています。 すぬけ君が $ 1 $ 回目に叫んだ後に、人 $ 1 $ はボール $ 2 $ を、人 $ 2 $ はボール $ 1 $ を持っています。 すぬけ君が $ 2 $ 回目に叫んだ後に、人 $ 1 $ はボール $ 1 $ を、人 $ 2 $ はボール $ 2 $ を持っています。 このとき、すべての人が自身の番号と同じ番号が書かれたボールを持っているので、すぬけ君は叫ぶのをやめます。 よってスコアは $ 2 $ となります。 よって $ 1^2\ +\ 2^2\ =\ 5 $ がこの問題の答えになります。

### Sample Explanation 2

すべての順列とスコアの組を列挙すると以下のようになります。 - 順列 : $ (1,2,3) $, スコア : $ 1 $ - 順列 : $ (1,3,2) $, スコア : $ 2 $ - 順列 : $ (2,1,3) $, スコア : $ 2 $ - 順列 : $ (2,3,1) $, スコア : $ 3 $ - 順列 : $ (3,1,2) $, スコア : $ 3 $ - 順列 : $ (3,2,1) $, スコア : $ 2 $ よって $ 1^3\ +\ 2^3\ +\ 2^3\ +\ 3^3\ +\ 3^3\ +\ 2^3\ =\ 79 $ を出力します。

## 样例 #1

### 输入

```
2 2```

### 输出

```
5```

## 样例 #2

### 输入

```
3 3```

### 输出

```
79```

## 样例 #3

### 输入

```
50 10000```

### 输出

```
77436607```

# 题解

## 作者：ran_qwq (赞：15)

这么水的题，怎么没人发题解（

考虑对于一个排列怎样计算 $S(p)$。把排列按 $i\rightarrow p_i$ 的方式拆成若干个环，每个环在变换上是独立的。设一个环长为 $L$，则当这个环的变换次数是 $L$ 的倍数时会恢复原样。所以 $S(p)$ 就是所有环长的 LCM。

$N\le50$，考虑一些稍暴力的非多项式复杂度做法。我们直接枚举环长序列 $\{l_k\}$，钦定它单调不降。只需要求它的 LCM $val$ 以及这种大小序列的数量 $cnt$。这一部分的答案就是 $val\cdot cnt^K$。

$val$ 是好求的，不需要高精度。把每个 $l_i$ 分解质因数，对于一个质数 $p$，它在 LCM 中的次数就是所有 $l_i$ 的 $p$ 的次数的最大值。

$cnt$ 也可以用由局部到整体的思想去求。对于一个长度为 $L$ 的环，从一个位置开始选，每次都选之前没选过的且不同于当前位置的位置。第 $i$ 次有 $L-i$ 种选法，所以一共有 $(L-1)!$ 种选法。

而对于多个环 $l_1,l_2,\dots,l_k$，可以看作第一次从 $n$ 个点中选 $l_1$ 个，第二次从 $n-l_1$ 个点中选 $l_2$ 个。但是两个长度相同的环，它们选的元素互换，会被看作两种方案。所以对于 $c$ 个长度为 $L$ 的环，还得除以 $c!$。

综上，一个 $\{l_k\}$ 的个数为 $\dfrac{\prod(l_i-1)!\cdot\prod\binom{n-\sum\limits_{j=1}^{i-1}l_j}{l_i}}{\prod c_i!}$。

至于时间复杂度，比较玄学，经计算 $n=50$ 方案数是 $8\times10^7$。跑最后一个样例要 1.3 秒，可以接受。

```cpp
int n,m,ans,CNT,a[N],b[N],fac[N],C[N][N];
void dfs(int s,int k) {
	if(s==n) {
		mst(b,0); int val=1,cnt=1;
		for(int i=1;i<k;i++) {
			cmul(cnt,fac[a[i]-1]); int x=a[i];
			for(int j=2;j*j<=x;j++) {int cur=0; while(x%j==0) cur++,x/=j; cmax(b[j],cur);}
			if(x!=1) cmax(b[x],1);
		}
		for(int i=1;i<=n;i++) cmul(val,qpow(i,b[i]));
		for(int i=1,lft=n;i<k;i++) cmul(cnt,C[lft][a[i]]),lft-=a[i];
		mst(b,0); for(int i=1;i<k;i++) b[a[i]]++; for(int i=1;i<=n;i++) cmul(cnt,qpow(fac[b[i]],MOD-2));
		return cadd(ans,vmul(cnt,qpow(val,m)));
	}
	for(int i=a[k-1];i<=n-s;i++) a[k]=i,dfs(s+i,k+1);
}
void QwQ() {
	n=rd(),m=rd(),fac[0]=1; for(int i=1;i<=n;i++) fac[i]=vmul(fac[i-1],i);
	for(int i=0;i<=n;i++) {C[i][0]=1; for(int j=1;j<=i;j++) C[i][j]=vadd(C[i-1][j-1],C[i-1][j]);}
	a[0]=1,dfs(0,1),wr(ans,"\n");
}
```

---

## 作者：mskqwq (赞：4)

一个排列的权值就是所有环长的 $\operatorname{lcm}$，注意到 $n=50$ 的整数拆分方案不多，那么不同的 $\operatorname{lcm}$ 的数量更少，考虑将 $\operatorname{lcm}$ 加入 dp 状态中。

$f_{i,j}$ 表示所有环长之和为 $i$，$\operatorname{lcm}=j$ 的方案数。枚举新的环的长度 $k$，转移系数为 $\binom {n-i}{k}(k-1)!$，也就是在剩下的数中选 $k$ 个再乘上圆排列的方案。

但是这样子会算重，原因在于先取 $1$ 再取 $2$ 和先取 $2$ 再取 $1$ 是一样的。解决方法是每次钦定选出的 $k$ 个数中必须包含剩下的数的编号的最小值，所以正确的系数为 $\binom {n-i-1}{k-1}(k-1)!$。

该做法可以在 1s 内跑出 $n=110$ 的结果。

```cpp
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#define fi first
#define se second
#define ep emplace
#define MISAKA main
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define rg(x) x.begin(),x.end()
#define pc(x) __builtin_popcount(x)
#define mems(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _rep(i,a,b) for(int i=(a);i>=(b);--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline int read(){
    char c=getchar();int f=1,x=0;
    for(;c<48||c>57;c=getchar())if(c=='-') f=-1;
    for(;47<c&&c<58;c=getchar()) x=(x<<3)+(x<<1)+(c^48);
    return x*f;
}
const int N=150,mod=998244353;
int n,K,ans,c[N][N],fac[N];
unordered_map<ll,int> f[N];
ll lcm(ll a,ll b){return a/__gcd(a,b)*b;}
void add(int &x,int y){((x+=y)>=mod)&&(x-=mod);}
ll qp(ll a,ll b){ll r=1;for(;b;b>>=1,a=a*a%mod)if(b&1)r=r*a%mod;return r;}
void misaka(){
    n=read(),K=read();
    rep(i,0,n){c[i][0]=1;rep(j,1,i)c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;}
    f[0][1]=fac[0]=1;
    rep(i,1,n) fac[i]=1ll*fac[i-1]*i%mod;
    rep(i,0,n-1)for(auto [a,b]:f[i])
        rep(j,1,n-i) add(f[i+j][lcm(a,j)],1ll*b*c[n-i-1][j-1]%mod*fac[j-1]%mod);
    for(auto [a,b]:f[n]) add(ans,qp(a%mod,K)*b%mod);
    printf("%d",ans);
}
bool __ed;
signed MISAKA(){
    #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs  ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB\n",abs(&__st-&__ed)/1024./1024);});
    #endif
    
    int T=1;
    while(T--) misaka();
    return 0;
}

```

---

## 作者：mathcode (赞：0)

首先对于一个确定的排列，该排列对应的 $S(p)$ 值为对每个 $i \rightarrow p_{i}$ 连边，最后一定会形成若干个环，所有环长的 $lcm$ 即对应该排列的 $S(p)$ 值（这应该是非常好理解的）。

然后该问题可以抽象为：对于给定 $n$ ，将 $n$ 进行整数划分，划分得到的所有整数 $lcm$ 的 $k$ 次幂的和。

但是还存在一个问题，就是一种整数划分可能会对应多种不同的原排列。现在考虑 $n$ 的一种整数划分结果 $l_{1}, l_{2}, \dots ,l_{k}$ ，每种数的个数对应为 $c_{1}, c_{2}, \dots ,c_{k}$ ，则本质不同的环的个数为 $\prod \limits_{i=1}^k \frac{\left( \binom{n - sum_{i-1}}{l_{i}} (l_{i} - 1)!\right) ^{c_{i}}}{c_{i}!}$ ， 其中 $sum_{i}$ 表示 $\sum_{i = 1}^{i} l_{i}$ 。

为什么得到这个式子，手模一下样例。首先考虑 $4$ 的一种划分结果 $ \{1,3\} $ ，首先确定 $1$ 的位置与本质不同环个数，即 $\binom{4}{1} \times 0!$ ，然后确定 $3$ 的位置与本质不同环个数，注意此时只剩余三个位置，即 $\binom{3}{3} \times 2!$ 。但是注意 $\{2,2\}$ 而言，由于他们之间并不需要区分，所以需要除以 $2!$ 避免数重。由此大胆 guess 上述式子。（手动狗头.png）

![环长为3本质不同环数手模](https://s2.loli.net/2024/10/14/tmUWnecM5qX6TEu.jpg)

考虑时间复杂度， $50$ 只有 $204266$ 种整数划分结果，所以完全可以通过，并且代码也出奇的好写。实际也只运行了 27ms 。

![image.png](https://s2.loli.net/2024/10/14/gZbLdTrGPosEhN9.png)


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 60; // 需要的最大组合数n，m的范围
const int mod = 998244353;
int fac[N], ifac[N];
int ksm(int x, int y)
{
    int ans = 1ll;
    for (; y; y >>= 1, x = x * x % mod)
        if (y & 1) ans = ans * x % mod;
    return ans;
}
int C(int n, int m)
{
    // m是小的数字,n是大的
    if (n < m || m < 0) return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

void init()
{
    fac[0] = 1ll; // 阶乘预处理
    for (int i = 1; i <= N - 5; i++)
        fac[i] = fac[i - 1] * i % mod;
    ifac[N - 5] = ksm(fac[N - 5], mod - 2);
    for (int i = N - 5; i; i--)
        ifac[i - 1] = ifac[i] * i % mod;
}
int lcm(int a, int b) { return a * b / gcd(a, b); }
int n, k, ans;
void dfs(int n, int x, int cnt, int sum, int lc)
{
    if (!n)
    {
        sum = (sum * ifac[cnt]) % mod; 
        ans = (ans + sum * ksm(lc, k) % mod) % mod;
        return;
    }
    for (int i = 1; i <= min(x, n); i++)
    {
        if (i != x)
            dfs(n - i, i, 1, sum * C(n, i) % mod * fac[i - 1] % mod * ifac[cnt] % mod, lcm(lc, i));
        else dfs(n - x, x, cnt + 1, sum * C(n, x) % mod * fac[x - 1] % mod, lcm(lc, x));
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    init();
    cin >> n >> k;
    dfs(n, n, 0, 1, 1);
    cout << ans << '\n';
}
```

---

