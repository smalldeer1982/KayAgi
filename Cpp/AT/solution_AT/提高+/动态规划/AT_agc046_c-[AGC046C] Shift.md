# [AGC046C] Shift

## 题目描述

给定一个只由 `0` 和 `1` 组成的序列 $S$ 。求对 $S$ 进行以下的操作 $[0,k]$ 次后可以得到的字符串种类个数模 $998244353$ 后的值。

- 选取一对整数 $i,j \space (1 \le i < j \le |S|)$ ，使得 $S_i$ 为 `0` 且 $S_j$ 为 `1`。将 $S_j$ 删去，并将这个数插在 $S_i$ 之前。

## 说明/提示

- $ 1 \le |S| \le 300$
- $ 0 \le k \le 10^9$
- $S$ 只包含 `0` 和 `1`

### 样例解释 1

可能形成 `0101`, `0110`, `1001`, `1010` 四种字符串。

## 样例 #1

### 输入

```
0101 1```

### 输出

```
4```

## 样例 #2

### 输入

```
01100110 2```

### 输出

```
14```

## 样例 #3

### 输入

```
1101010010101101110111100011011111011000111101110101010010101010101 20```

### 输出

```
113434815```

# 题解

## 作者：jun头吉吉 (赞：7)

## 题意
有一个 $01$ 串 $S$，每次选择 $i<j$ 满足 $S[i]=0,S[j]=1$，把 $j$ 移到 $i$ 之前，可以操作不超过 $K$ 次，求有最终能够得到多少不同的串。

$1\le|S|\le300,0\le K\le10^9$
## 题解
考虑在最后面加上一个 $0$ 显然不影响答案。记一共有 $m$ 个 $0$，第 $a_i$ 表示第 $i-1$ 个 $0$ 到第 $i$ 个 $0$ 中间 $1$ 的数量，一步操作就相当于选择 $i<j$，$a_i$ 加上 $1$，$a_j$ 减去 $1$，只能操作 $K$ 次求最终有多少种 $\{a_i\}_{i=1}^m$。

不考虑操作次数，一个 $\{b_i\}_{i=1}^m$ 能被构造出来的充要条件：

- $\sum_{i=1}^ma_i=\sum_{i=1}^mb_i$
- $\forall i\in[1,m],\sum_{j=1}^ib_j\ge\sum_{j=1}^ia_i$

两个条件都是必要的。然后毛估估也是充分的。最小操作次数是 $\sum_{i=1}^m\max(b_i-a_i,0)$。

这个可以直接 dp，就设 $f_{i,j,k}$ 表示 $\sum_{x=1}^i b_{x}=j,\sum_{x=1}^i\max(b_x-a_x,0)=k$ 的方案数。

转移的时候要枚举 $b_i$，复杂度是四次方，但是直接过了。

优化到三次方不难。但是我是懒狗。
## 代码
```cpp
const int N=3e2+10;
char s[N];int n,k,m,a[N],sum[N];
mint dp[2][N][N],ans;
signed main(){
	scanf("%s",s+1);read(k);
	n=strlen(s+1);s[++n]='0';
	for(int i=1,j=0;i<=n;i++)if(s[i]=='0')
		a[++m]=i-j-1,j=i;
	for(int i=1;i<=m;i++)sum[i]=sum[i-1]+a[i];
	int cur=0,lst=1;dp[cur][0][0]=1;
	for(int i=1;i<=m;i++){
		swap(cur,lst);memset(dp[cur],0,sizeof dp[cur]);
		for(int j=sum[i-1];j<=sum[m];j++)
			for(int k=0;k<=sum[m];k++)if(dp[lst][j][k].x)
				for(int w=max(sum[i]-j,0);j+w<=sum[m];w++)
					dp[cur][j+w][k+max(0,w-a[i])]+=dp[lst][j][k];
	}
	for(int i=0;i<=k&&i<=sum[m];i++)ans+=dp[cur][sum[m]][i];
	writeln(ans.x);
}
```

---

## 作者：liangbowen (赞：3)

[blog](https://www.cnblogs.com/liangbowen/p/18343931)。好菜啊，不会这题，来写个题解 /kel。

---

很难直接做，先找一点性质：操作只改变相对顺序，而总数不变。

这启示我们记录每个 $0$ 前面的极长 $1$ 连续段长度。记第 $i(1\le i\le C)$ 个 $0$ 对应长度为 $a_i$，就存在下面的等价表述：

> 每次操作可以选定 $i,j(1\le i<j\le C)$，将 $a_i$ 加 $1$，$a_j$ 减 $1$，且始终有 $\forall a_i\ge0$。

注意到，如果选定 $(p,i)(i,q)$，实际只是 $a_p$ 少了 $1$，$a_q$ 多了 $1$，可以用一步 $(p,q)$ 代替。于是此时存在操作次数更少的相同方案。

也就是说，**每一位要么始终加，要么始终减**。

不难用 dp 刻画：$dp_{i,p,q}$ 表示前 $i$ 个数用了 $p$ 次 $+1$ 与 $q$ 次 $-1$（$p\ge q$），方案数。不难有如下 $O(n^2 k^2)$ 的转移：

$$\begin{cases}dp_{i,p,q}\gets dp_{i-1,p,q}\\dp_{i,p,q}\gets dp_{i-1,p-t,q} & (1\le t\le x)\\dp_{i,p,q}\gets dp_{i-1,p,q-t} & (1\le t\le \min(q,a_i))\end{cases}$$

$k$ 很大。但是注意到每个 $1$ 至多被移动一次。因为移动很多次的话，实际可以一步到位，于是必然存在操作次数更少的相同方案。

所以可以令 $k\gets\min(k,|S|)$，复杂度就降为了 $O(n^4)$。不难前缀和优化至 $O(n^3)$。

---

小细节：可以在 $S$ 末尾添加一个 `0`，来处理末尾 $1$ 连续段。

[code](https://atcoder.jp/contests/agc046/submissions/56383594)，时间复杂度 $O(n^4)$，加上指令集后可以轻松通过。~~三次方做法懒得改了，反正其他题解有写。~~

---

## 作者：happybob (赞：3)

$k$ 很大，猜测复杂度与 $k$ 无关。

需要一些注意力就可以注意到一对 $(0,1)$ 被操作后，这个 $1$ 不可能再被前面的 $0$ 操作，因为这样的话我们可以一次操作得到同样的结果。

每个 $1$ 只会至多被操作一次，故至多 $n$ 次操作就可以得出所有可能结果。所以 $k>n$ 时视为 $k=n$ 处理。

考虑转化一下题意，在字符串末尾补充一个 $0$ 显然不会对答案造成影响。

转化问题。设字符串有 $m$ 个 $0$，第 $i$ 个 $0$ 的前面连续极长 $1$ 的长度为 $c_i$。发现我们每次操作即指定一个 $1\leq i < j \leq m$，$c_i \leftarrow c_i+1$，$c_j \leftarrow c_j - 1$。问至多 $k$ 次操作后不同的 $c$ 序列个数。

上面的那个观察可以更强一点，对于每个 $i$，要么选择从来不在 $i$ 操作，要么 $i$ 只做加法或减法。否则我们可以使操作次数更少且达到同样目的。

考虑 DP，$f_{i,x,y}$ 表示前 $i$ 个数，用了 $x$ 次 $+1$ 和 $y$ 次 $-1$。这里要保证 $\max\{x,y\} \leq k$ 且 $x \geq y$。原因是操作次数不能超过 $k$ 且不能 $-1$ 比 $1$ 多，因为我们每次操作要求 $i<j$。

转移时枚举第 $i$ 个数选 $+1$ 还是 $-1$ 以及选的次数。$-1$ 可以暴力枚举，因为 $\sum c_i \leq n$，而 $+1$ 次数可以在 DP 时做前缀和。时间复杂度 $O(n^3)$，空间 $O(n^3)$，滚动一下可以做到 $O(n^2)$ 但不重要。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
using namespace std;

using ll = long long;

const int N = 305;
const ll MOD = 998244353ll;

long long qpow(long long a, long long b)
{
	long long res = 1ll, base = a;
	while (b)
	{
		if (b & 1ll) res = res * base % MOD;
		base = base * base % MOD;
		b >>= 1ll;
	}
	return res;
}

ll f[N][N][N];
int n, k;
string s;
int m, c[N];
ll ss[N][N];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> s >> k;
	k = min(k, (int)s.size());
	s += "0";
	n = s.size();
	s = " " + s;
	for (int i = 1; i <= n; i++)
	{
		if (s[i] == '0')
		{
			m++;
			int cnt = 0;
			for (int j = i - 1; j >= 1; j--)
			{
				if (s[j] == '1')
				{
					cnt++;
				}
				else break;
			}
			c[m] = cnt;
		}
	}
	f[0][0][0] = 1;
	for (int i = 0; i <= n; i++) ss[i][0] = 1;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			for (int k = 0; k <= n; k++)
			{
				if (max(j, k) > ::k || j < k) break;
				f[i][j][k] = f[i - 1][j][k];
				for (int x = 1; x <= min(k, c[i]); x++)
				{
					f[i][j][k] = (f[i][j][k] + f[i - 1][j][k - x]) % MOD;
				}
				if (j) f[i][j][k] = (f[i][j][k] + ss[j - 1][k]) % MOD;
				//for (int x = 1; x <= j; x++) f[i][j][k] = (f[i][j][k] + f[i - 1][j - x][k]) % MOD;
			}
		}
		for (int k = 0; k <= n; k++)
		{
			for (int j = 0; j <= n; j++)
			{
				ss[j][k] = ((j == 0 ? 0 : ss[j - 1][k]) + f[i][j][k]) % MOD;
			}
		}
	}
	ll ans = 0ll;
	for (int i = 0; i <= k; i++)
	{
		ans = (ans + f[m][i][i]) % MOD;
	}
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：Conan15 (赞：1)

2025.02.24 修复加粗渲染问题。

把一个 $1$ 扔到某一个 $0$ 之前，这个东西感觉相当难刻画。\
但注意到每个 $1$ 一定可以“**属于**”一个 $0$，即它往后的第一个 $0$。当把一个 $1$ 移动的时候，相当于一个 $0$ **失去**一个 $1$，另一个 $0$ **得到**一个 $1$。\
那么就可以设 $c_i$ 表示 $i$ 这个位置之前**连续** $1$ 的个数，特别地，如果 $i$ 位置是 $1$ 则 $c_i = 0$。\
一次操作相当于选择 $i \lt j$，令 $c_i \leftarrow c_i + 1, c_j \leftarrow c_j - 1$。则计算字符串个数转化为计算 $c$ 序列个数。

这一步转化过后，考虑 DP 解决问题。\
观察到如果对 $(i,j)$、$(j,k)$ 分别操作一次，相当于对 $(i,k)$ 操作一次。所以**每个位置只能加或者只能减**，不会出现同时加减的情况。\
设 $dp_{i,j,k}$ 表示前 $i$ 个点，总共操作了 $j$ 次 $+1$，操作了 $k$ 次 $-1$，产生 $c$ 序列的数量。\
考虑枚举 $e$ 表示这一位操作 $e$ 次 $+1$ 或 $-1$。\
容易写出转移方程：

$$dp_{i,j,k} = dp_{i-1,j,k} + \sum\limits_{e=1}^{j} dp_{i-1,j-e,k} + \sum\limits_{e=1}^{\min(k, c_i)} dp_{i-1,j,k-e}$$

题目中给出的 $k \leq 10^9$ 显然是诈骗。\
但是更诈骗的是，虽然操作总数理论上是 $O(n^2)$ 级别，但是转化成上述的模型之后，$+1,-1$ 的数量最多只有 $O(n)$ 级别。\
因此 $j,k$ 两维都是 $O(n)$ 级别，时间复杂度 $O(n^4)$。\
观察到有区间和形式，容易想到前缀和优化到 $O(n^3)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 315, mod = 998244353;
int n, m, p;
int c[N], num;
char s[N];

template <class type,const type mod> struct Modint{ ... };
typedef Modint<long long, mod> Mint;    //记得自定义 mod

Mint dp[N][N][N];
int main() {
    scanf("%s %d", s + 1, &p), n = strlen(s + 1), s[n + 1] = '0';
    for (int i = 1; i <= n + 1; i++) {
        if (s[i] == '1') { num++; continue; }
        int j = i - 1;
        while (s[j] == '1' && j >= 1) j--;
        c[i] = (i - 1) - j;
    }
    // for (int i = 1; i <= n; i++) cout << c[i] << ' '; puts("");
    for (int i = 1; i <= n + 1; i++)
        if (s[i] == '0') c[++m] = c[i];
    // for (int i = 1; i <= m; i++) cout << c[i] << ' '; puts("");
    
    dp[0][0][0] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= min(num, p); j++)    //进行 j 次 +1 操作
            for (int k = 0; k <= j; k++) {      //减的显然不能比加的多
                dp[i][j][k] += dp[i - 1][j][k];
                for (int e = 1; e <= j; e++) dp[i][j][k] += dp[i - 1][j - e][k];
                for (int e = 1; e <= min(k, c[i]); e++) dp[i][j][k] += dp[i - 1][j][k - e];
            }
    }
    Mint ans = 0;
    for (int i = 0; i <= min(num, p); i++) ans += dp[m][i][i];
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Union_Find (赞：1)

~~为什么我连蓝题都做不出来了？~~

如果从原题目考虑比较难想，所以我们思考可不可以转化问题。~~就是这个点卡了我半天。~~

后来我考虑到，每次移动 $1$，一定是在一段连续的极长的 $1$ 之后。当然，这里如果是连续的两个 $0$ 中间我们也认为中间有一段长度为 $0$ 的极长连续 $1$ 段。而最后我们只要确定每一段极长连续的 $1$ 的长度就可以确定 $01$ 串。

所以我们可以把问题转化成有一个长度为 $n$ 的序列 $a_i$，每次操作可以选择 $1 \le i < j \le n$，将 $a_i$ 加 $1$，将 $a_j$ 减 $1$。其中的 $a_i$ 对应原 $01$ 串中每一段极长连续的 $1$ 的长度。

这样子我们就好 dp 了。设 $f_{i,x,y}$ 表示前 $i$ 个数，已经进行了 $x$ 次加 $1$ 操作和 $y$ 次减 $1$ 操作。其中 $x,y$ 满足 $y \le x$。初始化是 $f_{0,0,0} = 1$。答案是 $\sum_{j=0}^k f_{n,j,j}$。

考虑转移。

$$f_{i,x,y} = f_{i-1,x,y} + \sum_{j=1}^{x} f_{i-1,x - j,y} + \sum_{j=1}^{\min(y,a_i)}f_{i-1,x,y-j}$$

其中的第一项指的是不考虑在这一位操作，后面两项分别指在 $i$ 这一位加 $j$ 和减 $j$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 305
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}const ll P = 998244353;
char s[N];
ll n = 1, m, k, a[N], f[N][N][N], ans;
il void add(ll &x, ll y){x = (x + y >= P ? x + y - P : x + y);}
int main(){
	scanf ("%s", s + 1);
	m = strlen(s + 1);
	k = min(rd(), m);
	s[++m] = '0';
	for (int i = 1; i <= m; i++){
		if (s[i] == '1') a[n]++;
		else n++;
	}n--;
	f[0][0][0] = 1;
	for (int i = 1; i <= n; i++) for (int p1 = 0; p1 <= k; p1++) for (int p2 = 0; p2 <= p1; p2++){
		f[i][p1][p2] = f[i - 1][p1][p2];
		for (int t = 1; t <= p1; t++) add(f[i][p1][p2], f[i - 1][p1 - t][p2]);
		for (int t = 1; t <= min((ll)p2, a[i]); t++) add(f[i][p1][p2], f[i - 1][p1][p2 - t]);
	}for (int i = 0; i <= k; i++) ans = (ans + f[n][i][i]) % P;
	printf ("%lld\n", ans);
	return 0;
}
```

---

## 作者：lalaouye (赞：1)

这是一种 dp 状态不那么抽象的组合数做法。~~但是很复杂，仅供参考。~~

经过思考后发现，我们可以将字符串串按零的位置割开并分成若干个子串，设 $a_i$ 表示第 $i$ 个子串中 $1$ 的个数（子串长度），这样就能转化为每一次操作将后面的一个数减 $1$，前面的一个数加 $1$，求操作数小于等于 $k$ 能产生的本质不同的数组个数，我们发现这个可以用 dp 解决。

具体应该怎么做的？容易想到一个不管重复的 dp，也就是记 $f_{i,j}$ 表示考虑到第 $i$ 个数，操作 $j$ 次可以得到的不同操作序列，显然这个肯定是错的。该怎么判重？通过观察发现，每一个 $a_i$ 要么只加要么只减，否则所需步数还多，最终还有可能重复。我们统计的数即为数组的加减情况（废话），但是这还远远不够，因为我们发现对于当前状态下的两种情况 ``6 2``，``5 3``，现在考虑加一个 $1$，当我们加到第一个数时，可以得到 ``7 2`` 和 ``6 3``，当我们加到第二个数时，可以得到 ``6 3``，``5 4``，很遗憾，又有重复情况出现，考虑继续增添限制。观察这个过程，我们如果在一个方案中，先加完需要增加的第一个，再加需要增加的第二个，然后第一个就不再去管了，于是这个做法就不会被操作顺序等影响了，这样就可以进行一个 dp，记 $f_{i,j,k}$ 表示考虑到第 $i$ 位，前面有 $j$ 个位置可以加，共花了 $k$ 次操作的方案数，这个 dp 有两个转移：

$$f_{i,j,k}\longleftarrow f_{i-1,j-1,k}$$

$$f_{i,j-l,k}=\sum_{l=0}^{j-1}\sum_{o=1}^{\min(k,a_i)} f_{i-1,j,k-o}\times\binom{o+l-1}{l}$$

我们将只能被加的位叫做接收位，只能减的位叫做输出位。

第一个转移表示让当前这一位作为接收位。

第二个转移就有点复杂了，首先这个是这一位作为输出位的转移，$l$ 表示这一位加完了前面的多少接收位（意思就是说，有 $l$ 位是只有我能加的，其它的输出位只能加这 $l$ 位以后的了），显然 $l$ 是可以为 $0$ 的，因为这就表示这个输出位全部就加到当前的接收位，并且下一个输出位也可以加到这里。

$o$ 则表示一共输出了 $o$，后面的组合数则表示给前面的 $l+1$ 的接收位的分配方案数，用插板法计算，至于上面为啥要减个 $1$，是因为如果不保证最后一位一定会被分配就又会有重复的情况，所以先钦定一个输出量给最后一个接收位。

因为 $o$ 最多就会枚举 $n$ 次，所以这个 dp 的时间复杂度为 $\mathcal{O}(n^4)$，但是估计出题人没想到会有这么愚蠢的方法出现，于是没有故意卡，最慢的点也只有四百多毫秒，而且它跑不满，~~所以直接过了~~。

代码：

```
#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for (int i = l; i <= r; ++ i)
#define rrp(i, l, r) for (int i = r; i >= l; -- i)
#define pii pair <int, int>
#define eb emplace_back
#define inf 1000000000
#define linf 1000000000000000000
using namespace std;
typedef long long ll;
constexpr int N = 305, P = 998244353;
inline int rd ()
{
    int x = 0, f = 1;
    char ch = getchar ();
    while (! isdigit (ch))
    {
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (isdigit (ch))
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar ();
    }
    return x * f;
}
void add (int &x, int y)
{
	(x += y) >= P && (x -= P);
}
char s[N];
int m;
int f[2][N][N];
int a[N];
int C[N << 1][N << 1];
signed main ()
{
    // freopen ("1.in", "r", stdin);
    // freopen ("1.out", "w", stdout);
	C[0][0] = 1;
	rep (i, 1, 600) rep (j, 0, i) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
    scanf ("%s", s + 1); m = rd ();
	int n = strlen (s + 1); s[++ n] = '0';
	m = min (m, n); int cnt = 0, tot = 0, sum = 0;
	rep (i, 1, n) if (s[i] == '0') a[++ tot] = cnt, cnt = 0; else ++ cnt, ++ sum;
	int p = 0; f[0][0][0] = 1;
	rep (i, 1, tot)
	{
		int v = ! p; rep (j, 0, i) rep (k, 0, m)
			{ if (j) f[v][j][k] = f[p][j - 1][k];
				rep (l, 0, j - 1)
					rep (o, 1, min (k, a[i]))
						add (f[v][j - l][k], f[p][j][k - o] * C[o + l - 1][l] % P);
			} memset (f[p], 0, sizeof f[p]);
	}
	int ret = 0; rep (i, 0, tot) rep (j, 0, m)
	add (ret, f[p][i][j]); printf ("%lld\n", ret);
}
```



---

## 作者：serene_analysis (赞：1)

可见操作不会改变序列中 $0/1$ 的个数，只会改变顺序。考虑对于每个序列找到一个双射进行计数。由于操作是往 $0$ 前加 $1$，这启示我们把 $0/1$ 分开处理。一个或许相当经典的想法是取出所有只含 $1$ 的极长连续段（两个相邻的 $0$ 之间视为有一个长度为 $0$ 的段），把所有段的长度构成的序列拿出来。可以发现这个序列和原序列一一对应，因为你可以根据这个序列直接还原出原序列，同时不同的长度序列一定会还原出不同的原序列，于是就找到了双射。

这样一来，原本的操作在长度序列中可以如此描述：你可以执行不超过 $k$ 次操作，每次操作选定两个数并让靠前者 $+1$ 靠后者 $-1$，要求序列中的数非负。一个明显的性质是一个数不会又加又减（否则可以合并两次操作），因此一个数要么加要么减要么不动。设 $tot_{i,j,l}$ 表示从后往前处理完了原序列中的第 $i$ 个数，已经有了 $j$ 个 $-1$，已经分配完了 $l$ 个 $+1$ 的方案数。（这里有个问题，$k$ 太大怎么办？发现实际上有效操作的个数不超过长度序列所有数的总和，因为你要分配 $-1$ 的位置不能分配 $1$，这导致你选择的 $-1$ 的个数的总和不超过长度序列对应位置的值之和，后者又小于原串长度，于是将 $k$ 在开始时对原序列长度取最小值即可。）

转移时枚举当前数加多少或减多少，即 $tot_{i,j,l}=(\sum_{p=0}^l tot_{i+1,j,p})+(\sum_{p=\max(l,j-val_i)}^j tot_{i+1,p,l})-tot_{i+1,j,l}$，最后要减 $tot_{i+1,j,l}$ 是因为加 $0$ 和减 $0$ 都算到了它。这样直接写就是 $\mathcal{O}(n^4)$ 的。发现两个求和符号里面都只有一个下标在变，于是维护两个前缀和相减即可做到 $\mathcal{O}(n^3)$。空间复杂度 $\mathcal{O}(n^3)$，可以滚动数组优化到 $\mathcal{O}(n^2)$。

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
const int maxn=3e2+5;
const int maxk=3e2+5;
const int mod=998244353;
char str[maxn];
int n,k;
int wz[maxn],wcnt,val[maxn];
int tot[maxn][maxn][maxn],fsum[maxn][maxn][maxn],ssum[maxn][maxn][maxn];
signed main(){
	scanf("%s%d",str+1,&k),n=strlen(str+1),k=std::min(k,n);
	for(int i=1;i<=n;i++)if(str[i]=='0')wz[++wcnt]=i;
	wz[++wcnt]=n+1,n=0;
	for(int i=1;i<=wcnt;i++)val[++n]=wz[i]-wz[i-1]-1;
	if(!n){
		printf("1");
		return 0;
	}
	for(int i=0;i<=val[n];i++){
		tot[n][i][0]=1;
		for(int j=0;j<=k;j++)fsum[n][i][j]=1;
		ssum[n][i][0]=i+1;
	}
	for(int i=val[n]+1;i<=k;i++)ssum[n][i][0]=val[n]+1;
	for(int i=n-1;i;i--){
		for(int j=0;j<=k;j++)for(int l=0;l<=j;l++){
			int np=std::max(l,j-val[i])-1;
			tot[i][j][l]=fsum[i+1][j][l];
//			printf("tot[%d][%d][%d]=%d\n",i,j,l,tot[i][j][l]);
			(tot[i][j][l]+=(ssum[i+1][j][l]+mod-(np>=0?ssum[i+1][np][l]:0))%mod)%=mod;
//			printf("np=%d,tot[%d][%d][%d]=%d\n",np,i,j,l,tot[i][j][l]);
			(tot[i][j][l]+=mod-tot[i+1][j][l])%=mod;
//			printf("tot[%d][%d][%d]=%d\n",i,j,l,tot[i][j][l]);
		}
		for(int j=0;j<=k;j++){
			fsum[i][j][0]=tot[i][j][0];
			for(int l=1;l<=j;l++)fsum[i][j][l]=(fsum[i][j][l-1]+tot[i][j][l])%mod;
		}
		for(int l=0;l<=k;l++){
			ssum[i][l][l]=tot[i][l][l];
			for(int j=l+1;j<=k;j++)ssum[i][j][l]=(ssum[i][j-1][l]+tot[i][j][l])%mod;
		}
	}
	int ans=0;
	for(int j=0;j<=k;j++)(ans+=tot[1][j][j])%=mod;
	printf("%d",ans);
	return 0;
}
//namespace burningContract
```

感谢你的阅读。

---

## 作者：2008verser (赞：0)

设 $a$ 数组是原串被 $0$ 割开的各个长度。举个例子

$$
110110\to a=\{2,2,0\}
$$

注意一次操作对 $a$ 的影响，即选定 $i\lt j$，令 $a_i$ 减一并 $a_j$ 加一。

对 $a$ 的结果序列 $b$ 的计数，考虑最少操作步数。从后往前贪心，$b\lt a$ 意味 $a$ 向前扔，$b\geq a$ 代表从后面扔过来接住。

不难发现 $b$ 的充要条件：

- 任意后缀和不超过 $a$ 的。$\forall1\leq p\leq n,\sum_{i\geq p}b_i\leq \sum_{i\geq p}a_i$。（合法性）
- $\sum_{i=1}^n[a_i\gt b_i](a_i-b_i)\leq k$。（$k$ 步内）

暴力 dp 是 $O(n^4)$ 的，观察转移形式可以前缀和做到 $O(n^3)$。

[AC 链接](https://atcoder.jp/contests/agc046/submissions/61062662)

---

