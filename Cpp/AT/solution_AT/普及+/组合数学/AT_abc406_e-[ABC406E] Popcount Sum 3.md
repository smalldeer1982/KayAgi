# [ABC406E] Popcount Sum 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc406/tasks/abc406_e

正の整数 $ N,K $ が与えられます。  
 $ N $ 以下の正の整数 $ x $ であって、次の条件をみたすものの **総和** を $ 998244353 $ で割った余りを求めてください。

- $ x $ の popcount の値はちょうど $ K $ である。
 
$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

  popcount とは 正整数 $ y $ に対して、$ y $ の popcount の値 $ \mathrm{popcount}(y) $ は、$ y $ を二進数表記したとき $ 1 $ となっている桁の個数を表します。 例えば、$ \mathrm{popcount}(5)=2 $, $ \mathrm{popcount}(16)=1 $, $ \mathrm{popcount}(25)=3 $ です。

## 说明/提示

### 制約

- $ 1\leq\ T\leq\ 100 $
- $ 1\leq\ N\ <\ 2^{60} $
- $ 1\leq\ K\ \leq\ 60 $
- $ T,N,K $ は整数
 
### Sample Explanation 1

$ 1 $ 番目のテストケースについて、$ 20 $ 以下の正の整数のうち、popcount の値が $ 2 $ であるものは $ 3,5,6,9,10,12,17,18,20 $ の $ 9 $ つであり、その総和は $ 100 $ となります。 $ 100 $ を $ 998244353 $ で割った余りは $ 100 $ であるため、$ 1 $ 行目には $ 100 $ を出力します。 $ 998244353 $ で割った余りを出力する必要があることに注意してください。

## 样例 #1

### 输入

```
2
20 2
1234567890 17```

### 输出

```
100
382730918```

# 题解

## 作者：_zhangcx (赞：4)

# 题解：AT_abc406_e [ABC406E] Popcount Sum 3

题意：求 $\le N$ 中满足其恰好有 $K$ 二进制位为 1 的所有数之和。

首先考虑一个特殊情况，若没有 $\le N$ 的限制的答案是多少呢？我们记 $F(i, j)$ 在 $i$ 个二进制位中选 $j$ 个位填 1 的数的和，不难发现：

$$
F(i, j) = (2 ^ i - 1) \times \dbinom{i - 1}{j - 1}
$$

现实意义很简单，对于每个位 $k$，其如果选定为 1，则方案数为在 $i - 1$ 位中选定 $j - 1$ 位为 1 的方案数，其他情况不会产生贡献。因而单个位贡献为 $2 ^ k \times \dbinom{i - 1}{j - 1}$。因而提公因式后等比数列求和可得：

$$
F(i, j) = \sum _ {k = 0} ^ {i - 1} {2 ^ k \times \dbinom{i - 1}{j - 1}} = (2 ^ i - 1) \times \dbinom{i - 1}{j - 1}
$$

现在回到题目。加上了 $\le N$ 的限制，其实本可以像数位 DP 那样做，但是似乎这种思路会好想一些？

我们记$cnt(n, k)$、$sum(n, k)$ 分别为 $\le n$ 中满足 $k$ 个二进制位为 1 的方案数、数之和。答案即为 $sum(N, K)$。

考虑如何用已知的 $F(n, k)$ 求出 $sum(n, k)$。

首先，如果 $n$ 的最高位 $i$ 选了 1，后面的答案可以拆成第 $i$ 位的贡献和第 1 位到第 $i - 1$ 位的贡献，即 $sum(n - 2 ^ i, k - 1) + 2^i \times cnt(n - 2 ^ i, k - 1)$，否则若不选 1，后面 $i$ 位随便选，答案为 $F(i, k)$。

求 $cnt(n, k)$ 的方法同理可得 $cnt(n, k) = cnt(n - 2 ^ i, k - 1) + \dbinom{i}{k}$。

实现方法有递归和递推，我觉得递归会好实现一些，$cnt$ 和 $sum$ 可以存一块。此外，由于不明原因，**此代码过程量不开 `__int128` 无法 AC**，欢迎 dalao 们指处错误。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long int
const int mod = 998244353;
int qpow(int x, int y, const int mod) {
    int res = 1;
    for (; y; y >>= 1) {
        if (y & 1) res = res * x % mod;
        x = x * x % mod;
    } return res;
}
int fac[65], invfac[65];
void init() {
    fac[0] = 1; for (int i = 1; i <= 63; i++) fac[i] = fac[i - 1] * i % mod;
    for (int i = 0; i <= 63; i++) invfac[i] = qpow(fac[i], mod - 2, mod);
}
int comb(int n, int m) { return m > n ? 0 : (__int128)fac[n] * invfac[m] % mod * invfac[n - m] % mod; }
int chose(int i, int j) { return (__int128)((1ULL << i) - 1) * comb(i - 1, j - 1) % mod; }
struct node { int sum, cnt; };
node solve(int n, int k, int t) { // t 记录的是当前位数
    if (k > t + 1) return {0, 0};
    else if (n == 0) return {0, !k};
    if (n >> t) {
        node x = solve(n ^ (1ULL << t), k - 1, t - 1);
        return {(int)((chose(t, k) + x.sum) % mod + (__int128)x.cnt * (1ULL << t) % mod) % mod,
                (x.cnt + comb(t, k)) % mod};
    } else return solve(n, k, t - 1); // 还不是最高位
}
main() {
    ios::sync_with_stdio(false), cin.tie(0);
    init();
    int t, n, k;
    for (cin >> t; t; t--) {
        cin >> n >> k;
        int w = 63; while (!(n >> w & 1)) w--; // 求最高位
        cout << solve(n, k, w).sum % mod << '\n';
    }
    return 0;
}
```

---

## 作者：Collapsarr (赞：4)

### AT\_abc406\_e 题解

#### 翻译

你需要求出 $1$ 到 $n$ 中满足二进制下 $1$ 的个数为 $k$ 的数之和，对 $998244353$ 求和。

#### 思路

赛后看了眼官方题解，觉得 dp 还是不好做，不如爆搜。

考虑从高位到地位搜索答案，在搜索的过程中，我们需要维护三个东西，分别是：当前搜索的位置、搜索到现在二进制下共有多少个 $1$、搜索到现在的二进制是否和 $n$ 完全相等。

搜索的时候判断：如果搜索到现在的二进制和 $n$ 完全相等，那么当前这一位一定不能高于 $n$ 二进制对应的位。

在记录贡献的时候可以将搜索每一位的贡献拆开，维护每一个二进制位的贡献，最后再合并起来便好。

最后再套上记忆化就可以愉快切掉了。

#### code
赛时代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

int read()
{
	int x = 0,f = 1;
	char ch = getchar();
	while(ch<'0'||'9'<ch)
	{
		if(ch=='-')
		{
			f = -1;
		}
		ch = getchar();
	}
	while('0'<=ch&&ch<='9')
	{
		x = (x<<3) + (x<<1) + ch - '0';
		ch = getchar();
	}
	return x * f;
}

const int inf = 1e18,mod = 998244353;

pair<int,int> last[64][64][2];
int f[64],p[64],tot,n,k;

pair<int,int> dfs(int it,int cnt,bool t)
{
    if(it==tot+1)
    {
        if(cnt==k)
        {
            return {1,0};
        }
        else
        {
            return {0,0};
        }
    }
    //剪枝，判断剩余的位数和应选1的位数
    if(tot-it+1<k-cnt)
    {
    	return {0,0};
	}
    //记忆化
    if(last[it][cnt][t].first!=-inf)
    {
        return last[it][cnt][t];
    }
    //判断是否和n在高位上全相等
    int r = t?f[it]:1,cntt = 0,summ = 0;
    for(int i = 0,cnttt;i<=r;i++)
	{
		cnttt = cnt + i;
        if(cnttt>k)
		{
            continue;
        }
        auto nxt = dfs(it+1,cnttt,t&&(i==f[it]));
        //维护贡献
        //其中的first维护的是有多少种情况，second维护的是之后的贡献
        summ = (summ + ((i * p[it]) % mod * nxt.first) % mod + nxt.second) % mod;
        cntt = (cntt + nxt.first) % mod;
    }
    //记忆化
    last[it][cnt][t] = {cntt,summ};
    return last[it][cnt][t];
}

signed main()
{
    int T = read();
    while(T--)
    {
        n = read(),k = read(),tot = 0;
		for(int i = 0;i<64;i++)
	    {
	        for(int j = 0;j<64;j++)
	        {
	        	last[i][j][0] = last[i][j][1] = {-inf,-inf};
	        }
	    }
        //拆分n的二进制位
		while(n)
		{
			f[++tot] = n & 1;
			n>>=1;
		}
        //翻转
		reverse(f+1,f+1+tot);
        //预处理每一位二进制下的贡献
		p[tot] = 1;
        for(int i = tot-1;i;i--)
        {
        	p[i] = (p[i+1]<<1) % mod;
        }
        cout<<dfs(1,0,1).second<<endl;
    }
    return 0;
}
/*
2
20 2
1234567890 17
*/
/*
100
382730918
*/
```

---

## 作者：Lacuna (赞：3)

### 前言：

主播也是场切了好吧。

### 思路：

考虑数位 DP，我们要设两个状态，一是已经选择的 $1$ 的个数，二是 $n$ 对每一位大小的限制。先将 $n$ 转为二进制，然后从后往前考虑每一位，对于可选的数，有两种情况：

- 前面的位和 $n$ 相同，那么我们就不能超过 $n$ 的对应位。

- 否则当位不受 $n$ 的限制，随便取。

设 $nw$ 分别对应前面这两种情况，然后考虑两种情况：

- 选 $0$：若前面的位受 $n$ 限制，且 $n$ 当前位是 $0$，则后面要受限制。否则后面不受限制，将状态改为 $0$。

- 选 $1$：先判断一的个数是不是小于 $k$，以及 $n$ 对这位是否有只能选 $0$ 的限制。然后更新状态，和前面一样。

随后累加答案即可。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define gc getchar
#define ll long long
template<typename T>inline void rd(T&x){x=0;char ch=gc();while(ch<'0'||ch>'9')ch=gc();while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=gc();}}
template<typename T,typename...A>inline void rd(T&x,A&...a){rd(x);rd(a...);}
const ll mod=998244353,mk=60;
ll p2[61];
string change(ll n){string s;while(n){s+=(n&1)+'0';n>>=1;}return s;}//转二进制 
void init(){p2[0]=1;for(int i=1;i<=60;i++)p2[i]=p2[i-1]*2%mod;}//预处理2^i 
ll solve(ll n,ll k){//数位DP 
    if(!k)return 0;
    string b=change(n);
    ll l=b.size(),pc[2][mk+1]={},ps[2][mk+1]={};//pc:个数，ps:和 
    pc[1][0]=1;//第一位表示：0：不受限制，1：受限制。第二位表示cnt 
    for(int i=l-1;i>=0;i--){//从高到低枚举位 
        ll cnt[2][mk+1]={},sum[2][mk+1]={};//目前状态 
        for(int x=0;x<2;x++){//枚举前面的状态 
            for(int y=0;y<=k;y++){
                if(!pc[x][y])continue;
                ll mb=x?(b[i]-'0'):1;
                //选一 
                ll nw=x&&(!mb);//更新状态 
                ll c0=y;
                if(c0<=k){
                    cnt[nw][c0]=(cnt[nw][c0]+pc[x][y])%mod;//累加 
                    sum[nw][c0]=(sum[nw][c0]+ps[x][y])%mod;
                }
                //选零 
                if(y+1>k||1>mb)continue;
                nw=x&&(mb==1);
                ll c1=y+1;
                ll as=(ps[x][y]+pc[x][y]*p2[i])%mod;//对答案的贡献：2^i*个数 
                cnt[nw][c1]=(cnt[nw][c1]+pc[x][y])%mod;//累加 
                sum[nw][c1]=(sum[nw][c1]+as)%mod;
            }
        }
        for(int i=0;i<2;i++)for(int j=0;j<=k;j++)pc[i][j]=cnt[i][j],ps[i][j]=sum[i][j];//更新 
    }
    ll a=0;
    for(int i=0;i<2;i++)a=(a+ps[i][k])%mod;
    return a;
}
signed main(){
    init();
    int T;rd(T);
    while(T--){
        ll n,k;rd(n,k);
        printf("%lld\n",solve(n,k));
    }
    return 0;
}
```

---

## 作者：xuan_never (赞：2)

## 题目大意
给定正整数 $n$，求 $[1,n]$ 中所有满足在二进制下恰好有 $k$ 个 $1$ 的数的和，对 $998244353$ 取模。

## 做法
显然的数位 DP，设计 $f_{k,x,s}$ 与 $an_{k,x,s}$ 分别表示在求有 $k$ 个 $1$ ，到由低到高第 $x$ 二进制位且已取得 $s$ 个 $1$ 时的数量与数值和。

搜索数量的方式比较板，在此不赘述。而 $an$ 的转移应利用 $f$，为  
$$an_{k,x,s}=an_{k,x-1,s}+f_{k,x-1,s+1}\times 2^{x-1}$$

使用记搜实现，搜索时要额外记录是否受到范围限制。

## 代码
记得取模。

以下非赛时代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int, int> pii;
#define fi first
#define se second
const int maxl = 70, maxb = 5, mod = 998244353;
int T, n, k, num[maxl];
int f[maxl][maxl][maxl], an[maxl][maxl][maxl];
pii dfs(int x, int s, bool lim) {
	if (s > k) return {0, 0};
	if (!x) return {s == k, 0};
	if (!lim && ~f[k][x][s]) return {f[k][x][s], an[k][x][s]};
	int cnt = 0, su = 0, ma = (lim ? num[x] : 1);
	for (int i = 0; i <= ma; ++i) {
		pii t = dfs(x - 1, s + i, lim && i == ma);
		(cnt += t.fi) %= mod,
		(su += t.se + t.fi * ((i << x - 1) % mod) % mod) %= mod;
	}
	if (!lim) f[k][x][s] = cnt, an[k][x][s] = su;
	return {cnt, su};
}
int solve(int x) {
	int len = 0;
	while (x) {
		num[++len] = x & 1;
		x >>= 1;
	}
	return dfs(len, 0, 1).se;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	memset(f, -1, sizeof f);
	cin >> T;
	while (T--) {
		cin >> n >> k;
		cout << solve(n) << '\n';
	}
	return 0;
}
```

---

## 作者：ALLIN2624 (赞：2)

## Meaning

求 $[1,n]$ 范围中满足二进制下 1 的个数为 $k$ 的整数之和。

## Solution

数位 dp，建议[出门右转](https://www.luogu.com.cn/problem/P8764)。

记 $f(x,y)$ 为从大到小第 $x$ 位有 $y$ 个 1 的数的个数，$g(x,y)$ 为从大到小第 $x(\geq0)$ 位有 $y$ 个 1 的数的和。

前者是典的，着重讨论后者。

根据计数和贡献的思想，当我们在第 $x$ 位放数字 $z(0/1)$ 时，$g(x,y)$ 就必然要加上 $f(x,y)\times z\times2^x$，同时还可以加上 $g(x-1,y)$ 和 $g(x-1,y+1)$ 的贡献。

注意取模。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define il inline
#define all(v) (v).begin(), (v).end()
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define up(v, l, r) for (i32 v = (l); v <= (r); v++)
#define dn(v, l, r) for (i32 v = (r); v >= (l); v--)
#define run(v, f) for_each(all(v), f)

namespace {
	using i32 = int32_t;
	using i64 = int64_t;
	using u32 = uint32_t;
	using u64 = uint64_t;
	template <typename Tp> using art = vector<Tp>;
	
	struct IO_t {
		istream &inner;
		ostream &outter;
		IO_t(istream &_inner = cin, ostream &_outter = cout): inner(_inner), outter(_outter)
		{ ios::sync_with_stdio(0); inner.tie(0), outter.tie(0); }
		void sp() { outter << " "; }
		void ln() { outter << "\n"; }
		template <typename Tp> void in(Tp &x) { inner >> x; }
		template <typename Tp> void sp(Tp x) { outter << x << " "; }
		template <typename Tp> void ln(Tp x) { outter << x << "\n"; }
		template <typename Tp> void in(art<Tp> &a) { for (auto &u : a) inner >> u; }
		template <typename Tp> void sp(art<Tp> &a) { for (auto &u : a) outter << u << " "; }
		template <typename Tp> void ln(art<Tp> &a) { for (auto &u : a) outter << u << "\n"; }
		template <typename Tp, typename... Args> void in(Tp &x, Args& ...args) { in(x), in(args...); }
		template <typename Tp, typename... Args> void sp(Tp x, Args... args) { sp(x), sp(args...); }
		template <typename Tp, typename... Args> void ln(Tp x, Args... args) { ln(x), ln(args...); }
	} IO, dbg(cin, cerr);
	
	const i32 mod = 998244353;
	
	art<art<i64>> f, g;
	art<i32> a;
	i64 n;
	i32 k;
	
	il pair<i64, i64> dfs(i32 pos, i32 tot, bool limit) {
		if (pos == -1) return {tot == k, 0};
		if (!limit && ~f[pos][tot]) return {f[pos][tot], g[pos][tot]};
		i32 p = limit ? a[pos] : 1;
		i64 cnt = 0, sum = 0;
		up(i, 0, p) {
			auto u = dfs(pos - 1, tot + i, limit && i == p);
			cnt = (cnt + u.first) % mod;
			sum = (sum + u.first * (((i64)i << pos) % mod) % mod + u.second) % mod;
		}
		if (!limit) f[pos][tot] = cnt, g[pos][tot] = sum;
		return {cnt, sum};
	}
	
	il i64 calc(i64 x) {
		a.clear();
		while (x) {
			a.push_back(x % 2);
			x /= 2;
		}
		return dfs(a.size() - 1, 0, true).second;
	}
	
	void solve() {
		IO.in(n, k);
		art<art<i64>> v(70, art<i64>(70, -1));
		f = v, g = v;
		IO.ln(calc(n));
	}
}

signed main() {
	signed T = 1;
	cin >> T;
	while (T--) solve();
	return 0;
}
```

夹带了一点私货，望见谅。

## Ponder

这样做的正确性是显然的，但是可不可以在 `dfs` 中放一个参数表示当前搜到的数，合法返回这个参数，否则返回 0？

回忆数位 dp 的原理：**计数思想**！如果这么做只是统计到了第一个合法的数，错失范围内的其它解。

这部分写给一个不追求算法原理的 OIer。

---

## 作者：LionBlaze (赞：2)

简单题。

# 引入

考虑这样一道小学奥数题目：

> 有多少个 $(1,2,3,4,5,6)$ 的排列的字典序比 $(2,4,3,1,6,5)$ 小？

解法是：

> 首先考虑第一位是 $1$，这样显然是更小的。一共有 $A_5^5=120$ 个。
> 
> 然后考虑前两位是 $(2,k)$ 的情况，其中 $1 \le k \le 3$。一共有 $2 \times A_4^4=48$ 种（因为 $k \neq 2$）。
>
> 然后考虑前三位是 $(2,4,k)$ 的情况，其中 $1 \le k \le 2$。一共有 $A_3^3=6$ 种。
>
> 然后考虑前四位是 $(2,4,3,k)$ 的情况，其中 $1 \le k \le 0$，数学老师爆炸了。
>
> 然后考虑前五位是 $(2,4,3,1,k)$ 的情况，其中 $1 \le k \le 5$，一共有 $1$ 种。
>
> 最后考虑 $(2,4,3,1,6,k)$ 的情况，其中 $k=5$，不符合。
>
> 求和得到 $120+48+6+\text{爆炸的数学老师}_{(=0)}+1+0=175$ 个。

这里的原理是，我们逐个考虑每一位，然后再这一位上分为两种情况：收紧限制和放宽限制。

收紧限制就是指这里选原本排列 $(2,4,3,1,6,5)$ 中的位，无法保证后面任意排列都可以。放宽就是指选择比原本排列小的，这样可以保证，可以直接计数。

> update：发现这是[康托展开](https://www.luogu.com.cn/problem/P5367)。但是我真的是在做小学奥数题的时候第一次遇见了这种题，并且独立想出了做法。~~虽然当时算错了。~~

对应的思想也可以拓展到这题。

# 此题解法

我们同样逐位考虑。位权从大到小。

如果考虑到第 $i$ 位（位权为 $2^i$），我们默认位权更大的位都选了（即有 $1$ 选 $1$，没 $1$ 选 $0$），则如果第 $i$ 位为 $0$ 则必然不能选，对答案无影响。如果为 $1$ 则还是不选，后面可以任意选，但是需要保证 $\mathrm{popcount}=K$。

如何保证后者？

因为我们前面的位都已经选了，所以对 popcount 已经有了一定贡献。设剩下还需要 $K'$，显然剩下还有 $i$ 位。

一种显而易见的做法是，先 DP 求出所有“$i$ 位二进制数中 popcount 为 $j$ 的数字的和”$S_{i,j}$，然后答案就是 $S_{i,K'}$。

*这个结论是错的*。因为我们没有加上前面的位的和。正确做法是再预处理出对应的方案数 $C_{i,j}$，贡献为 $S_{i,j}+C_{i,j} \times \text{前面的位}$。

这样就正确了。*吗？*

我们注意到我们只考虑了“第一个不选的位为 $i$”的情况，如果所有位都选上则没有考虑。怎么做那也是非常显然的，如果 $\mathrm{popcount}(N)=K$ 则将最终答案加上 $N$。

记得取模。做完了。

什么你问 $S$ 和 $C$ 怎么求？首先注意到一个没啥用的性质 $C_{i,j}=C_i^j$。

当然我们根据 $C$ 的意义或者组合数的递推式就可以得到 $C$ 的递推式 $C_{i,j}=C_{i-1,j-1}+C_{i-1,j}$（分类讨论第 $i$ 位选不选）。$S$ 类似。

代码。

```cpp
#include <cstdio>
#include <bit>

using namespace std;

// c 表示 count，[i][j] 表示 i 位，1 为 j
unsigned long long c[64][64], p[64][64];

unsigned long long calc(unsigned long long k, unsigned long long r)
{
	unsigned long long sum = 0;
	for (int i = 59; i >= 0; i--)
	{
		if ((1ull << i) > k) continue;
		if ((k & (1ull << i)) == 0) continue;
		if (popcount(k >> (i + 1)) > r) break;
		sum += p[i][r - popcount(k >> (i + 1))] + ((k >> (i + 1) << (i + 1)) % 998244353) * c[i][r - popcount(k >> (i + 1))];
		sum %= 998244353;
	}
	return (sum + k * int(popcount(k) == r)) % 998244353;
}

int main()
{
	c[0][0] = 1;
	for (int i = 1; i < 60; i++)
	{
		c[i][0] = 1;
		p[i][0] = 0;
		for (int j = 1; j <= i; j++)
		{
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % 998244353;
			p[i][j] = (p[i - 1][j] + c[i - 1][j - 1] * ((1ull << (i - 1)) % 998244353) % 998244353 + p[i - 1][j - 1]) % 998244353;
		}
	}
	int t;
	scanf("%d", &t);
	while (t--)
	{
		unsigned long long n, k;
		scanf("%llu%llu", &n, &k);
		printf("%llu\n", calc(n, k));
	}
	return 0;
}
```

[sub](https://atcoder.jp/contests/ABC406/submissions/65938615)。

---

## 作者：zhangbo1000 (赞：1)

拆贡献。

首先 $N$ 的二进制下恰好有 $K$ 个 $1$ 的情况直接算进答案里面，下面考虑 $x<N$。

显然 $x$ 的构成一定是若干（可能 $0$）个高位与 $N$ 相等，某一位上 $N$ 为 $1$ 而 $x$ 为 $0$。

枚举这一位，设该位为第 $i$ 位，高位的数字为 $p$，其中包含 $j$ 个 $1$，那么显然 $x$ 的低 $i-1$ 位需要随便填 $k-j$ 个 $1$，方案数为 $C_{i-1}^{k-j}$，然后这里面第 $h$ 位上的 $1$ 贡献了 $C_{i-2}^{k-j-1}$ 个 $2^{h-1}$（因为相当于钦定这一位为 $1$ 然后剩下的随便填），然后我们又知道 $\sum_{u=1}^{i-1}2^{u-1}=2^{i-1}-1$，所以这部分可以 $O(1)$ 算出。

$p$ 和 $j$ 可以在枚举 $i$ 的过程中 $O(1)$ 更新，组合数可以 $O(\log^2n)$ 预处理，因此总复杂度为 $O(\log^2n+T\log n)$，足够通过本题，记得取模。

[代码和评测记录。](https://atcoder.jp/contests/abc406/submissions/65920398)

~~赛时就是这一坨东西卡了我半小时。~~

代码是短小精悍跑得快的，至于思路……你以为我会告诉你我不会数位 dp 吗？

---

## 作者：Nasaepa (赞：1)

同机房大家都写 `dfs` 就我不这么写。

---

纯计数。

我们先考虑 $n$ 的 popcount 和 $k$ 相等的情况。从高到低遍历 $n$ 的每一位 $1$，假设当前是第 $i$ 位（最低为第 $0$ 位）。令我们枚举的数字的最高位到低 $i+1$ 位都和 $n$ 是一样的，并考虑第 $i$ 位填 $0$ 的情况，可以确定这样一定小于 $n$ 并且不会重复。设 $n$ 的第 $0$ 位到第 $i$ 位一共有 $num$ 个 $1$，显然总共能产生 $\binom{i}{num}$ 个不同的数字，在这些数字中考虑每个位的贡献。第 $0$ 位到第 $i-1$ 位的任意一位在这些数字中一共会在 $\binom{i-1}{num-1}$ 个数字中为 $1$。所以第 $0$ 位到第 $i-1$ 位对答案产生的总贡献为 $(2^{i}-1)\times \binom{i-1}{num-1}$。至于高位的部分，将 $n$ 的最高位到第 $i+1$ 位取出，为 $q$，则这部分的贡献为 $\binom{i}{num}\times q$。注意到这种方法只能统计小于 $n$ 的数字，所以最后输出的答案要加 $n$。

那么如果 $n$ 的 popcount 不是 $k$ 呢？如果 $n$ 的 popcount 大于 $k$，那么就从低到高把 $n$ 的 $1$ 位置变成 $0$ 直到 $n$ 的 popcount 等于 $k$，然后直接按照上面的方法处理。如果 $n$ 的 popcount 小于 $k$，也是从低到高遍历每一位，只不过是把 $0$ 变成 $1$，并且答案不需要额外加 $n$。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define N 1000010
#define INF 0x3f3f3f3f
#define lowbit(x) (x&-x)
#define pii pair<int,int>
const ll mod = 998244353;
inline ll qpow(ll base,ll e){ll res=1;while(e){if(e&1)res=res*base%mod;base=base*base%mod;e>>=1;}return res;}
int t,k,cnt,num;ll n,ans,q;
ll f[N],g[N],p[N];
inline ll c(const int &x,const int &y){if(y > x)return 0;return f[x]*g[x-y]%mod*g[y]%mod;}

// 主函数
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> t;f[0] = p[0] = 1;
    for(int i = 1;i < N;++i)f[i]=f[i-1]*i%mod,p[i]=p[i-1]*2%mod;g[N-1] = qpow(f[N-1],mod-2);
    for(int i = N-2;i >= 0;--i)g[i]=g[i+1]*(i+1)%mod;
    while(t--){cin >> n >> k;ans = q = 0;num = 0;
        for(int i = 62;i >= 0;--i)if((n&(1ll<<i)))++num;
        if(num >= k){for(ll pos = 1;num != k;pos <<= 1)if(n & pos){--num,n&=(~pos);}ans = n;}// 把位置卸掉
        else for(ll pos = 1;num != k;pos <<= 1)if(!(n & pos)){++num,n|=pos;}// 补上
        for(int i = 62;i >= 0;--i){ll pos = (1ll<<i);if(!(n&pos))continue;
            ans = ans + c(i,num)*q%mod + (p[i]-1)*c(i-1,num-1)%mod;ans %= mod;--num;q += pos,q %= mod;
        }cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：1)

建议蓝，考虑数位 dp。

我们考虑另一个问题，$1 \sim n$ 之内有多少个 $x$ 满足 $\text{popcount}(x)=k$。

定义 $dp_{i,s}$ 表示当前是二进制下的第 $i$ 位，还可以填 $s$ 个 $1$ 的方案数，数位 dp 板子套上去直接做就行。

现在要求 $\sum x$，考虑当前状态下对答案的贡献，用 $sum$ 统计以下当前状态是 $1$ 的贡献即可。

```cpp
pii dfs (int pos,int s,int head,int lim){ // 返回二元组 (个数，总和)
	if (pos > cnt) return mp(!s,0);
	if (!head && !lim && dp[pos][s][head][lim] != -1)
		return mp(dp[pos][s][head][lim],sum[pos][s][head][lim]);
	int ret1 = 0,ret2 = 0; // ret1 表示当前为是 1 的个数
	int x = (lim ? a[cnt - pos + 1] : 1);
	for (int i = 0 ; i <= x ; i++){
		if (i == 1 && s > 0){
			pii g = dfs(pos + 1,s - 1,0,lim);
			ret1 += g.fi; sum[pos][s][head][lim] = (sum[pos][s][head][lim] + g.se) % mod;
		}
		if (!i){
			pii g = dfs(pos + 1,s,head,(lim && (i == x)));
			ret2 += g.fi; sum[pos][s][head][lim] = (sum[pos][s][head][lim] + g.se) % mod;
		}
	}
	sum[pos][s][head][lim] = (sum[pos][s][head][lim] + (ret1 % mod) * pw[cnt - pos]) % mod;
	dp[pos][s][head][lim] = (ret1 + ret2) % mod;
	return mp(dp[pos][s][head][lim],sum[pos][s][head][lim]);
}
```

---

## 作者：Chase12345 (赞：1)

考虑逐位处理。

请注意这里按照数位 DP 的方式，从高位往低位说明。

例如某一位前面是有压位的，也就是这一位不能填比原数大的数。

* 情况一：这一位原数为 $1$，那么这一位如果填 $1$，下一位同样处理。如果填 $0$，之后也就不压位了。
* 情况二：这一位原数为 $0$，那么这一位也就只能填 $0$，下一位依旧压位。

如果是没有压位的，也就是比较好处理的，那么直接组合计数。假设接下来还有 $n$ 位，要填 $k$ 个 $1$。

* 情况一：这一位填 $1$，那么接下来的填法总共有 $\binom{n}{k-1}$ 种。接下来仍然不压位。
* 情况二：这一位填 $0$，那么接下来填法就有 $\binom{n}{k}$ 种。接下来也就不压位了。

最后直接位值原理合并答案即可。位值原理具体而言可以参考二进制转十进制的原理。通过计算每一位能放 $1$ 的数的个数和放 $0$ 的数的个数，之后统计，位值也就用上了。

---

## 作者：lyx128 (赞：1)

本题目我们考虑使用数位动态规划实现。

由于我做过一道[洛谷的题目](https://www.luogu.com.cn/problem/P8764)，和这题几乎一样，所以很快想到了。

本题还要求计算所有数字的和，所以我们考虑分别记录符合要求的次数和符合要求的和。我们分别考虑一下两种情况：

1. 当前位数的二进制值为 $1$。那么，到此产生的贡献为**原来的产生的贡献**和**加上原来符合要求的数乘以这一位的贡献**之和。
2. 当前位数的二进制值为 $0$。那么，到此产生的贡献为**原来的产生的贡献**。

最后，我们写出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=60;
const int mod=998244353;
int T;
ll n;
int K;

vector<bool> num;
pair<ll,ll> dp[N+5][N+5];

pair<ll,ll> dfs(ll x,ll k,ll closer){
	if(!x)
		return {k==K,0};
	if(!closer&&dp[x][k].first!=-1)
		return dp[x][k];
	ll maxn=closer?num[x]:1;
	ll res_sum=0;
	ll res_count=0;
	for(int i=0;i<=maxn;i++){
		pair<ll,ll> val=dfs(x-1,k+i,closer&&(i==maxn));
		res_count=(res_count+val.first)%mod;
		if(i)
			res_sum=(res_sum+val.second+(1ll<<(x-1))%mod*val.first%mod)%mod;
		else
			res_sum=(res_sum+val.second)%mod;
	}
	if(!closer)
		dp[x][k]={res_count,res_sum};
	return {res_count,res_sum};
}

ll solve(ll x){
	ll t=x;
	num.clear();
	num.push_back(-1);
	while(t){
		num.push_back(t&1);
		t>>=1;
	}
	memset(dp,0xff,sizeof(dp));
	return dfs(num.size()-1,0,1).second;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>K;
		cout<<solve(n)<<"\n";
	}
	return 0;
}
```

---

## 作者：ANDER_ (赞：1)

对于这类题目，一般来说需要拆位处理。也就是把问题转换为计算每个合法数字在二进制位上 $\tt1$ 的贡献之和。

我们记 $m$ 为 $N$ 的最高二进制位，$cnt_i$ 表示的是第 $i$ 位为 $\tt1$ 且合法的数字个数。那么有：

$$\text{ans} = \displaystyle\sum_{i = 0}^m{2^i cnt_i}$$

对于 $cnt$ 数组的计算，可以使用数位 DP 的思路解决。设 $dp_{i,j,k \isin\{0,1\}}$ 表示当前倒序处理到了第 $i$ 位，已经用了 $j$ 个 $\tt1$，且是不是“严格限制于 $N$”，如果 $k$ 为 $1$，意味着后面怎么填，最大由 $N$ 的二进制位决定。

当 $i = -1$，且 $cnt = K$，计数加一。

用 $bts_i$ 表示 $N$ 在二进制下的第 $i$ 位，考虑如下转移：

- 若当前位置 $i$ 是目标位 $t$：

  $$cnt_t = cnt_t + dp_{i - 1,j + 1,t \land[1 \le bts_i]}$$

- 否则，遍历当前位可能的取值 $b \isin[0,\text{MAX}]$：

  $$dp_{i, j, k} = dp_{i,j,k} + \displaystyle\sum_{b = 0}^{\text{MAX}}dp_{i - 1,j + b,k \land [b = \text{MAX}]}$$

其中 $\text{MAX} = \begin{cases}
bts_i &\text{if } k\\
1 &\text{otherwise}
\end{cases}$。


时间复杂度为 $\mathcal{O}(T\log_2^3N)$，这足够快了。[代码](https://atcoder.jp/contests/abc406/submissions/65911706)。

---

## 作者：zhangzheng2026 (赞：1)

枚举从哪一位开始不同，设该位从高往低数第 $i$ 位，第 $i$ 位之前的数位表示的数为 $j$ 且有 $l$ 个数位不为零，总位数为 $num$，则对答案的贡献为：  
$$j\times \binom{num-i}{k-l}+(2^{num-i}-1)\times \binom{num-i-1}{k-l-1}$$  
解释一下：即 $i$ 位之前表示的数乘上总方案再加上每个 $i$ 位之后为一的贡献乘上该位为一时的方案数，显然方案数相等，放到一起算，所有位的和就为 $2^{num-i}-1$。  
代码：  

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int t,n,k,a[65],num,f[65],g[65],ans,al,nm,mi[65];
int c(int x,int y){return (x<0||y<0||x<y)?0:g[x]*f[y]%mod*f[x-y]%mod;}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	f[0]=f[1]=g[0]=g[1]=mi[0]=1;
	for(int i=2;i<65;i++) f[i]=(mod-mod/i)*f[mod%i]%mod,g[i]=g[i-1]*i%mod;
	for(int i=2;i<65;i++) f[i]=f[i-1]*f[i]%mod;
	for(int i=1;i<65;i++) mi[i]=mi[i-1]*2%mod;
	cin>>t;
	while(t--)
	{
		cin>>n>>k,nm=num=al=ans=0,memset(a,0,sizeof(a));
		while(n) a[++num]=(n&1),n/=2;reverse(a+1,a+num+1);
		for(int i=1;i<=num;i++)
		{
			if(!a[i]) continue;
			ans=(ans+c(num-i,k-nm)*al+c(num-i-1,k-nm-1)*(mi[num-i]-1))%mod;
			nm++,(al+=mi[num-i])%=mod;
		}
		if(nm==k) (ans+=al)%=mod;
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：haokee (赞：1)

这道题目需要我们求出 $1\sim n$ 中所有二进制 1 位数量为 $k$ 的数的和。对于这种需要进行数位统计、对数位有一定限制、数据规模很大的题目使用数位 dp 再合适不过了。

首先我们需要先将 $n$ 转换为二进制形式，方便我们进行状态枚举。设计状态 $dp_{x,cnt,tight}$，存储两个值，表示对于 $x$ 位及以后，若前面的数位中有 $cnt$ 个二进制 1，是否受 $n$ 的数位限制（前面的数位和 $n$ 一样），有多少种数满足要求和这些数的和。

采用记忆化搜索实现。对于已经存在的状态，直接返回之前的值。随后按照限制对下一位进行枚举，递归求出下一位的答案，累加下一位的满足要求的数量和这些数的和。最后返回当前状态。

具体实现看代码。

```cpp
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;
using LL = long long;

const LL kMaxN = 65, kMod = 998244353;

LL t, n, k;
pair<LL, LL> dp[kMaxN][kMaxN][2];
string s;

pair<LL, LL> dfs(LL x, LL cnt, bool tight) {
  // 对于边界状态的判断
  if (x == s.size()) {
    return {cnt == k ? 1 : 0, 0};
  }
  // 如果状态已经存在，则调用记忆
  if (dp[x][cnt][tight] != make_pair(-1LL, -1LL)) {
    return dp[x][cnt][tight];
  }
  // 当前位的最大数；满足条件的数数量；满足条件的数的和
  LL limit = tight ? s[x] - '0' : 1, tot = 0, ans = 0;
  // 枚举下一位
  for (LL i = 0; i <= limit; i++) {
    // 下一位是否也受 n 的约束
    bool now_tight = tight && (i == limit);
    // 可行性剪枝
    LL new_cnt = cnt + (i == 1);
    if (new_cnt > k) {
      continue;
    }
    // 递归下一位
    auto t = dfs(x + 1, new_cnt, now_tight);
    tot = (tot + t.first) % kMod;  // 累加数量
    ans = (ans + t.second) % kMod;  // 累加和
    // 如果当前位为 1，则加上当前为的贡献
    if (i == 1) {
      LL p = s.size() - x - 1, add = (1LL << p) % kMod;
      add = add * t.first % kMod;
      ans = (ans + add) % kMod;
    }
  }
  // 返回答案
  return dp[x][cnt][tight] = {tot, ans};
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> t; t; t--) {
    cin >> n >> k;
    s.clear();
    // 转换 n 为二进制数
    if (!n) {
      s = "0";
    } else {
      for (; n; n /= 2) {
        s.push_back((n & 1) + '0');
      }
      reverse(s.begin(), s.end());
    }
    memset(dp, -1, sizeof(dp));
    cout << dfs(0, 0, true).second << '\n';
  }
  return 0;
}
```

数位 dp 不仅好想还好写，比用组合数拆分算贡献简单多了，因为满足条件数的数量是通过拆分成子问题来计算的，而非用公式计算。

---

## 作者：littlebug (赞：1)

数位 dp，场切不了的。

## Solution

显然是数位 dp，先把 $n$ 拆成二进制位。

设 $f_{i,j}$ 为后 $i+1$ 位（就是第 $0$ 位到第 $i$ 位）中有 $j$ 个 $1$ 的所有方案的数字和**与方案数**。

那么转移是容易的，考虑当前位选 $0$ 还是 $1$ 即可，注意 dp 的过程中不仅要统计数字和，还要统计方案数，因为当第 $i$ 位选 $1$ 时，仅知道 $f_{i-1,j-1}$ 的数字和似乎不够的，还需要知道有多少个，这决定了我们在第 $i$ 位需要放多少个 $1$。

不过要注意一些剪枝。

首先当 $j=0$ 时，显然只有一种方案，就是 $0$（注意取全 $0$ 虽然不怎么符合题意，但对答案没有影响，因为它不会产生任何贡献）。

其次，当 $j > i+1$ 时，一定无解，这很重要，剪枝效果看起来非常非常非常非常非常非常大。

![](https://s21.ax1x.com/2025/05/18/pEvDnTs.png)

怎么感觉评测姬在嘲讽我 /fn

## Code

```cpp
int n,k;
pii f[70][70];
bitset <70> a;

il pii dp(int i,int j,bool lim)
{
	if(!j) return {0,1};
    if(j>i+1) return {0,0};
    if(!i)
    {
        if(j>1) return {0,0};
        else return lim ? (a[i]==1 ? mp(1,1) : mp(0,0)) : mp(1,1);
    }
    if(!lim && f[i][j].st>0) return f[i][j];
    
    pii ans={0,0},res;

    // choose 0
    res=dp(i-1,j,lim && !a[i]);
    add(ans.st,res.st),add(ans.nd,res.nd);
    
    // choose 1
    if(!lim || (lim && a[i]))
    {
        res=dp(i-1,j-1,lim);
        add(ans.st,mod_(res.st+res.nd*mod_(1ll<<i))),add(ans.nd,res.nd);
    }

    if(!lim) f[i][j]=ans;
    return ans;
}

il void solve()
{
    read(n,k);
    a=n;
    write(dp(64-__builtin_clzll(n),k,1).st,'\n');
}
```

---

华风夏韵，洛水天依！

---

## 作者：zsq9 (赞：0)

[AC 记录](https://atcoder.jp/contests/abc406/submissions/66017785)

## 题目大意

求 $1 \sim n$ 中所有二进制数 1 的个数为 $k$ 的数的和，对 $998244353$ 取模。

## 思路

这里看到数据范围 $1 \leq N < 2^{60}$ 和题目让我们求所有二进制数为 1 的数，我们就可以想到数位 dp，[学数位 dp 点这里](https://oi-wiki.org/dp/number/)。
我们考虑一种特殊情况，$n$ 为 $2^{m}$ 次方，这样 $n-1$ 的二进制就为 $0111111 \cdots$ 这样就很好做了，答案就是 $C_{n-1}^{k-1} \times (2^{m}-1)$。我们怎么把特殊情况推广到题目呢？我们可以从高位开始，首先我们令到这个一的位数是 $z$，遇到一个一，然后我们看一下 1 的个数有没有 $k$，没有就分成 $z-1$ 和 $z$ 来算，$z-1$ 部分就用上面的特殊情况做，$z$ 就是 $C_{n-1}^{l-1} \times (2^{l}-1)$，把这两贡献加起来就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,n,k,C[65][65];
const ll mod=998244353;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	for(int i=0;i<65;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
		}
	}
	while(t--){
		cin>>n>>k;
		ll cnt=0,ans=0;
		n++;
		for(int i=61;i>=0;i--){
			if((n>>i)&1){
				if(k>=1)ans=(ans+((1ll<<i)%mod-1)*(C[i-1][k-1]%mod))%mod;
				if(k>=0)ans=(ans+cnt*C[i][k]%mod)%mod;
				k--,cnt=(cnt+(1ll<<i))%mod;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：canwen (赞：0)

**场切数位 dp 是不可能的，赛后补题过是爽的。**

## Solution
**写递推式是不可能的，我喜欢 `dfs` ！**

建议先做 [P8764](https://www.luogu.com.cn/problem/P8764)，本题为此题升级版。

我们从最高位一路搜索下来，维护当前位数的位置，当前是否已经比 $N$ 小（若已经小了，该位放 `0` 或者 `1` 都是可行的，否则就得另外判断），二进制下放了多少个 `1` 了。

用 `pair` 类型记录当前的方案数和符合条件的数求和，记 $fst$ 表示数字和（即最后的答案），$snd$ 表示方案数。记当前的数字和 $fst1$，方案数 $snd1$，下一位搜索得到的数字和 $fst0$，方案数 $snd0$，那么乘法原理和加法原理，可以得到若当前位放置一个 `1` 有 $2^x$ 的贡献，那么 $fst1 = fst1 +  snd0 \cdot 2^x + fst0$，若当前位置放的是 `0` 则 $fst1 = fst1 + fst0$。方案数累计即可，即 $snd1 = snd1 + snd0$。
## Code

```cpp
const int mod = 998244353;

int n,k,f[70][2][70][2],a[70],cnt;
int qsm(int a,int b){
	int res = 1;
	while(b){
		if(b&1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

pint dfs(int x,int zt,int sum){
	// 0 : 价值, 1 : 计数 
	if(f[x][zt][sum][0] != -1) return mk(f[x][zt][sum][0],f[x][zt][sum][1]);
	if(x == 0){
		return sum == k ? mk(0,1) : mk(0,0);
	}
	int cnt = 0, w = 0;
	_rep(i,0,1){
		if(zt && i > a[x]) continue;
		if(sum == k && i) continue;
		pint nxt = dfs(x-1,zt && i == a[x], sum + i);
		(w += (i*qsm(2,x-1)%mod*nxt.snd%mod)) %= mod;
		(w += nxt.fst) %= mod;
		(cnt += nxt.snd) %= mod;
	}
	f[x][zt][sum][0] = w, f[x][zt][sum][1] = cnt;
	return {w,cnt};
}

void solve(){
	n = in(), k = in();
	cnt = 0;
	memset(f,-1,sizeof(f));
	while(n){
		a[++cnt] = n % 2, n /= 2;
	}
	out(dfs(cnt,1,0).fst), pc;
}
```
[Accept submission & complete code](https://atcoder.jp/contests/abc406/submissions/66044476)。

---

## 作者：He_XY (赞：0)

## [E. Popcount Sum 3](https://atcoder.jp/contests/abc406/tasks/abc406_e)

### 题意

多测，共 $T$ 组数据。

给你整数 $N$ 和 $K$，找到所有满足以下条件的数 $x$ 的和：

- $\text{popcount}(x)=K$ 且 $ x\le N$，其中 $\text{popcount(x)}$ 表示 $x$ 在二进制形式中 $1$ 的数量。

### 思路

提供一个不是 $\text{DP}$ 的做法。为了方便表示，设 $998244353=M$。

对于 $N$ 二进制形式中每个是 $1$ 的位数 $d$（从后往前数，最右边的是第 $1$ 位），把它之前（不包括自己）的所有是 $1$ 的位都默认设成 $1$，设之前有 $cnt$ 位是 $1$（可以**预处理** 出前面是 $1$ 的数位表示的数的总和，即 $sum=\sum_{i=[x在二进制形式下的位数]}^{d+1} 2^{d-1}$），在之后（不包括自己）的共 $d-1$ 位中任意放入 $K-cnt$ 个 $1$，很明显，方案数为 $\text{C}_{d-1}^{K-cnt}$。我们把这些方案全部列出来：


*下图展示了 $k-cnt=3$，$d-1=5$ 的情况* ：

![](https://cdn.luogu.com.cn/upload/image_hosting/eslnxsyx.png)

它是 $\text{C}_{d-1}^{K-cnt}$ 个长度为 $K-cnt$ 的序列，每个数在 $1 \sim d-1$ 之间，可以证明，$1 \sim d-1$ 之间的每一个数（每一位）出现的次数都一样，即每个数字（每一位）出现了 $t=\displaystyle \frac{\text{C}_{d-1}^{K-cnt} \times (K-cnt)}{d-1}$ 次：
第 $i$ 位表示的数为 $2^i$，则本次答案增加 $\Delta=\sum_{i=1}^{d-2}2^i\times t+\text{C}_{d-1}^{K-cnt}\times sum =\displaystyle \frac{\text{C}_{d-1}^{K-cnt} \times (K-cnt)}{d-1}\times (2^{d-1}-1)+\text{C}_{d-1}^{K-cnt}\times sum$。

如果 $cnt=K$ 就把答案加上 $sum$ 并跳出循环。

注意点：

- 因为先取模再除法可能会出错，所以我们把除法换成乘法逆元，即 $\frac{1}{d-1} \bmod M=(d-1)^{M-2}\bmod M$（可以用费马小定理证明）。

- 同理，$\text{C}_n^k$ 也需要预处理，预处理出 $fact_i=i! \bmod M$，$rev_i=\frac{1}{i!}\bmod M$， $\text{C}_n^k=fact_n\times rev_k\times rev_{n-k}$。

- 记得开 $\text{long long}$，计算幂要用快速幂，不然超时。

### C++ 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define mpr make_pair
#define pb push_back
#define sz(v) (int)v.size()
using namespace std;
const int MOD=998244353;
int n,k;
int fact[64],rev[64];
int pw(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return res;
}
int C(int n,int k){
	if(n<k) return 0;
	return fact[n]*rev[k]%MOD*rev[n-k]%MOD;
}
void solve(){
	cin>>n>>k;
	vector<bool> v;
	while(n!=0){
		v.pb(n&1);
		n>>=1;
	}
	reverse(v.begin(),v.end());
	int ans=0,cnt=0,sum=0;
	for(int i=0;i<sz(v);i++){
		if(v[i]==0) continue;
		int dig=sz(v)-i;
		ans=(ans+(pw(2,dig-1)-1)*(C(dig-1,k-cnt)*(k-cnt)%MOD*pw(dig-1,MOD-2)%MOD)%MOD)%MOD;
		ans=(ans+C(dig-1,k-cnt)*sum)%MOD;
		cnt++;
		sum+=pw(2,dig-1);
		if(cnt==k){
			ans=(ans+sum)%MOD;
			break;
		}
	}
	cout<<ans<<endl;
}
signed main(){
	fact[1]=fact[0]=rev[0]=1;
	for(int i=2;i<=61;i++){
		fact[i]=fact[i-1]*i%MOD;
	}
	rev[61]=pw(fact[61],MOD-2);
	for(int i=60;i>=1;i--){
		rev[i]=rev[i+1]*(i+1)%MOD;
	}
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

