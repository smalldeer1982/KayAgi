# [ABC391G] Many LCS

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc391/tasks/abc391_g

给定长度为 $N$ 的小写英文字符串 $S$ 和整数 $M$。请对每个 $k=0,1,\ldots,N$ 解决以下问题：

- 在全部 $26^M$ 种长度为 $M$ 的小写英文字符串中，计算与 $S$ 的最长公共子序列（LCS）长度恰好为 $k$ 的字符串数量，结果对 $998244353$ 取模。

## 说明/提示

### 约束条件

- $1 \leq N \leq 10$
- $1 \leq M \leq 100$
- $N$ 和 $M$ 为整数
- $S$ 是长度为 $N$ 的小写英文字符串

### 样例解释 1

各 $k$ 值对应的答案如下：  
- $k=0$：在长度为 $2$ 的字符串中，与 `ab` 的 LCS 长度为 $0$ 的字符串共有 $576$ 个（例如 `cd`, `re`, `zz`）。  
- $k=1$：在长度为 $2$ 的字符串中，与 `ab` 的 LCS 长度为 $1$ 的字符串共有 $99$ 个（例如 `ac`, `wa`, `ba`）。  
- $k=2$：在长度为 $2$ 的字符串中，与 `ab` 的 LCS 长度为 $2$ 的字符串仅有 `ab` 这 $1$ 个。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2 2
ab```

### 输出

```
576 99 1```

## 样例 #2

### 输入

```
3 4
aaa```

### 输出

```
390625 62500 3750 101```

## 样例 #3

### 输入

```
7 50
atcoder```

### 输出

```
309810541 226923474 392073062 146769908 221445233 435648037 862664208 238437587```

# 题解

## 作者：nr0728 (赞：7)

三倍经验：[AT_abc391_g](/problem/AT_abc391_g)、[P4590](/problem/P4590)、[P10614](/problem/P10614)。

**注意：默认字符串 $\bm S$ 的下标从 $\bm 0$ 开始，二进制第 $\bm i$ 位默认从低到高。**

注意到 $N\leq 10$，考虑状压。

对于一个状态，其二进制第 $i$ 位为 $1$ 表示 $S$ 的第 $i$ 位（第 $i+1$ 个字符）被选中。这样，一个状态二进制 $1$ 的个数就表示当前 LCS 的长度。

### 预处理状态转移数组 $\bm f$

设 $f_{s,c}$ 表示：当前状态为 $s$，再加一个字母 $c$，新的 LCS 的匹配状态。枚举每个状态，具体来说：

- 枚举每一个字母 $ch$，记录一个数组 $t$，$t_i$ 初始值为：当前状态前 $i$ 个字符中，有多少个匹配了。
  - 从 $N-1$ 开始倒序找 $S$ 中这个位置 $ch$ 是否出现。（倒序是因为防止重复更新，因为只能匹配一次）
  - 如果出现，并且 $t_i=t_{i+1}$ 成立（这说明 $S_i$ 尚未匹配，即 $t$ 在此处没有增加），那么说明我们可以用这个字符 $ch$ 去匹配 $S_i$，从而使得 $t_{i+1}$ 更新为 $t_i+1$（表示多匹配了一个字符）。
- 然后保证 $t$ 是单调不减的，即对于 $i$ 从 $1$ 到 $N$ 依次执行 $t_i\leftarrow \max\{t_i,t_{i-1}\}$。

最后根据 $t$ 处理出 $f_{s.c}$ 即可，如果 $t_i+1=t_{i+1}$ 则说明 $S_i$ 被匹配了，将 $f_{s,c}$ 的第 $i$ 位设为 $1$。

### DP 统计方案

设 $g_{i,s}$ 表示：长度为 $i$ 的所有字符串，与 $S$ 匹配的状态为 $s$ 的方案数。初始值 $g_{0,0}=1$（空字符串）。

接下来对于每个长度 $i\in[0,M)$，具体来说：

- 对于所有状态：
  - 尝试在第 $i$ 次得到的匹配状态 $s$ 上（此时字符串长度为 $i$），添加一个字符 $c$，得到新的状态 $f_{s,c}$。此时字符串长度增加 $1$。
  - 然后增加新的状态的方案数：
     $$g_{i+1,f_{s,c}}\leftarrow g_{i+1,f_{s,c}}+g_{s,i}\pmod{998244353}$$

这里也可以滚动数组优化，不过本题没必要。

### 计算答案

枚举所有状态 $s$，$g_{M,s}$ 二进制中 $1$ 的个数（即 $\operatorname{popcount}$）即为长度为 $M$ 的所有字符串中，与 $S$ 的匹配状态为 $s$ 的字符串，与 $S$ 的 LCS 长度。所以：
$$\text{ans}_{\operatorname{popcount}(s)}\leftarrow\text{ans}_{\operatorname{popcount}(s)}+g_{M,s}\pmod{998244353}$$

### 时间复杂度

- 预处理状态转移数组 $f$：$\mathcal O(2^N\times\lvert\Sigma\rvert\times N)$；
- DP 统计方案：$\mathcal O(2^N\times\lvert\Sigma\rvert\times M)$；
- 计算答案：$\mathcal O(2^N)$。

总时间复杂度：$\mathcal O(2^N\times\lvert\Sigma\rvert\times (N+M))$，可以通过。

### 代码

[Submission #62289239 - AtCoder Beginner Contest 391](https://atcoder.jp/contests/abc391/submissions/62289239)。

---

## 作者：littlebug (赞：5)

~~你会发现这篇题解和我在 P10614 的[题解](https://www.luogu.com.cn/article/ypkfm95l)几乎一模一样~~。

## Solution

原题是 P4590 和 P10614。

dp 套 dp 典题。考虑算 LCS 中的那个 dp：

> 设 $g_{i,j}$ 为 $s_{1 \sim i}$ 与 $t_{1 \sim j}$ 的 LCS，有转移：
> $$g_{i,j} = \min (g_{i-1,j} , g_{i,j-1} , g_{i-1,j-1} + [s_i = t_j])$$

可以发现，每个 $g_{i,j}$ 与 $g_{i,j+1}$ 要不相等，要不后者比前者多 $1$，于是对于 $g_i$ 进行差分后可以得到一个只包含 $0,1$ 的数组，同时原数组和差分数组构成双射关系，于是直接转换是可以的。这个 dp 还有一个性质就是，如果要求 $g_i$，只需要知道 $g_{i-1}$、$t$ 与 $s_i$ 即可。

然后考虑设计状压 dp。设 $f_{i,s}$ 为长度为 $i$，与模式串 $b$ 进行 LCS 的 dp 所构成的 $g_{n}$ 的差分数组为 $s$，的方案数。那么转移就是显然的了，先从小到大枚举 $i$，然后枚举 $s$，然后考虑下一个位置填哪个字母即可，再现场把 $g_{i+1}$ dp 出来，设得到的差分数组为 $t$，那么则有转移：

$$
f_{i+1,t} \gets f_{i+1,t} + f_{i,s}
$$

于是这样做就可以了。

统计答案的时候，一个 $s$ 所对应的 LCS 长度显然就是 ${\rm popc}(s)$。

需要注意两个优化剪枝，一是可以把 $f_{i,s}$ 为 $0$ 的状态直接剪掉，因为这部分起不到任何作用；二是可以把每个 $s,c$（$s$ 为差分数组，$c$ 为在末尾加的字符）在 LCS 的 dp 后对应的 $s'$ 预处理出来或者记忆化（我这里采用的是记忆化），避免重复做同样的事。

## Code

```cpp
string base;
int n,m,f[2][1<<11],g[2][12],ans[12],nxt[1<<11][26];

il void dp(int flag,int s,char c,int v)
{
    if(nxt[s][c-'a']!=-1) return add(f[flag][nxt[s][c-'a']],v);
    
    rep(i,0,n-1) g[0][i+1]=(s>>i&1)+g[0][i];
    rep(i,1,n) g[1][i]=max({g[1][i-1],g[0][i],g[0][i-1]+(c==base[i])});

    int t=0;
    rep(i,0,n-1) t|=g[1][i+1]-g[1][i]<<i;
    add(f[flag][t],v);
    nxt[s][c-'a']=t;
}

signed main()
{
    memset(nxt,-1,sizeof(nxt));
    
    read(n,m),read(base),base="$"+base;

    f[0][0]=1;
    
    bool flag=0;
    rep(i,0,m-1)
    {
        rep(s,0,(1<<n)-1) f[!flag][s]=0;
        rep(s,0,(1<<n)-1) rep(j,'a','z') dp(!flag,s,j,f[flag][s]);
        flag=!flag;
    }

    rep(s,0,(1<<n)-1) add(ans[popc(s)],f[m&1][s]);
    rep(i,0,n) write(ans[i],' ');

    return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：___PatrickChen___ (赞：3)

提示：三倍经验为 P4590 和 P10614。核心算法为 dp 套 dp。

求 LCS 的值为 $k$ 的方案数，考虑设 $f_{i,j}$ 表示长度为 $i$ 时 LCS 为 $j$ 的方案数。

但是这样好像不能进行 dp，那么我们尝试更改状态设计，$f_{i,s}$ 表示长度为 $i$ 且 LCS 状态为 $s$ 的方案数。

然而我们仍然不知道这个状态 $s$ 如何设计使得它容易进行转移，并且容易进行统计答案。那么我们观察一下 LCS 是怎么 dp 的：

> $g_{i,j} = max\{g_{i-1,j},g_{i,j-1},g_{i-1,j-1}+[A_i=B_j]\}$

注意到 LCS 的 dp 数组有一个性质，就是 $g_{i,j-1}$ 与 $g_{i,j}$ 的差一定为 $1$ 或 $0$。  
我们还发现，如果我们要求 $g_i$ 那么我们就只需要知道 $g_{i-1}$、$A_i$ 和 $B$ 就可以求出了。

综合以上两点，我们可以对 $g$ 进行差分得到一个 01 串，然后对这个 01 串进行状压。  
我们发现，状压之后的这个东西似乎很好转移，非常适合作为上文提及状态 $s$。我们考虑枚举这个状态 $s$ 以及未知字符串下一个字符 $A_i$，然后进行一次 dp，我们就可以得到新状态 $s'$。  
最后在统计答案的时候，我们发现因为 $s$ 是 LCS 的 dp 数组的差分，所以状态为 $s$ 的 dp 数组的 LCS 值为 $popcount(s)$。于是 $ans_{poopcount(i)} =\sum f_{n,s}$ 即可。

综上，我们得到了一个神秘做法。不过如果每一次转移都进行一次 LCS 的 dp 的话，有一些[神金题目](https://www.luogu.com.cn/problem/P10614)会把这种做法[卡掉](https://www.luogu.com.cn/record/204465035)。

~~好吧我并不知道这道题有没有卡这种做法。如果你想的话可以试一下。~~

所以我们可以考虑建出一个 DFA，那么只需要在预处理 DFA 的时候进行 LCS 的 dp 即可。

最后给一下代码：

```cpp
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

using ll = long long;

const ll N = 35005, M = 105, P = 998244353;

int n, m, f[2][N], tmp1[M], tmp2[M];
ll ans[M], _next[N][26];
string s;

// 编码，对 dp 数组进行状压得到状态 s
ll encode(int a[]) {
	ll res = 0;
	for (int i = 0; i < m; ++i) res |= (a[i + 1] - a[i]) << i;
	return res;
}

// 解码，对状态 s 进行还原得到 dp 数组
void decode(int a[], ll res) {
	for (int i = 0; i < m; ++i) a[i + 1] = res >> i & 1;
	for (int i = 1; i <= m; ++i) a[i] += a[i - 1];
}

// LCS dp 预处理 DFA
ll calc(ll _hash, char ch) {
	decode(tmp1, _hash);
	for (int i = 1; i <= m; ++i) tmp2[i] = max({tmp2[i - 1], tmp1[i], tmp1[i - 1] + (ch == s[i])});
	_hash = encode(tmp2);
	return _hash;
}

void init() {}

void solve() {
	cin >> m >> n >> s;
	m = s.size();
	s = " " + s;
	memset(ans, 0, sizeof ans);
	memset(f, 0, sizeof f);
	memset(_next, 0, sizeof _next);
	f[0][0] = 1;
	for (int i = 0; i < 1 << m; ++i) { // 枚举上一个状态
		for (int j = 'a'; j <= 'z'; ++j) // 枚举未知字符串的下一个字符 A_i
			_next[i][j - 97] = calc(i, j); // LCS dp 得到下一个状态 s' 并存入 DFA
	}
	for (int i = 1, now, last; i <= n; ++i) {
		now = i & 1, last = !now; // 滚动数组避免 MLE
		for (int j = 0; j < 1 << m; ++j) f[now][j] = 0; // 滚动数组初始化
		for (int j = 0; j < 1 << m; ++j) {
			for (int k = 'a'; k <= 'z'; ++k) (f[now][_next[j][k - 97]] += f[last][j]) %= P; // 枚举下一个字符 A_i，利用 DFA 进行转移
		}
	}
	for (int i = 0; i < 1 << m; ++i) (ans[__builtin_popcount(i)] += f[n & 1][i]) %= P; // 统计答案
	for (int i = 0; i <= m; ++i) cout << ans[i] << " \n"[i == m]; // 输出
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int _ = 1;
	// cin >> _;
	init();
	while (_--) solve();
	return 0;
}
```

---

## 作者：DYYqwq (赞：3)

这辈子做的第一个 dp of dp。

题意是给你 $S$ 这个串，长为 $n$，问你有对于每一个 $k \in [0,n]$ 多少和 $S$ 的 LCS 为 $k$，长度为 $m$ 的串 $T$。

考虑小朋友写的 LCS 怎么写。不妨设 $f_{i,j}$ 表示 $T$ 取到前 $i$ 位，$S$ 取到第 $j$ 位的最长公共子序列长度。

考虑设 $g_{i,s}$ 表示 $T$ 取到前 $i$ 位，$s=\{f_{i,j}\}$（一个集合，包含且仅包含对于当前 $i$ 所有的 $f_{i,j}$ 的值，将其全部打入 $g$ 的状态，这种做法称之为 dp of dp）的方案数。

但是显然向数组的一维中打入一个集合比较困难，考虑如何优化。

不难发现 $f$ 的增长十分缓慢，当 $j \rightarrow j+1$ 时，$f$ 可能 $+1$ 或者 $+0$。于是考虑只将这里的 $+1,+0$ 压入状态（即差分）。

显然直接二进制状态压缩即可。而该序列代表的最终的 LCS 长度即为 `__builtin_popcount(s)`。

注意这里的每一个二进制状态都表示一行 $f$ 数组，而非其他乱七八糟的东西。

上代码好解释一点。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 998244353;
int n , m , g[110][1 << 11] , f[110] , nf[110] , ans[110] , pow2[15] , mp[1 << 11][30];
string S , T;
inline void add(int &x , int y) {x = (x + y > mod ? x + y - mod : x + y);}
int F(int s , char c)
{
	for(int i = 1 ; i <= n ; i ++) f[i] = f[i - 1] + ((s >> (i - 1)) & 1);
	int ans = 0;
	for(int i = 1 ; i <= n ; i ++) nf[i] = max({f[i - 1] + (c == S[i]) , nf[i - 1] , f[i]}) , ans += (nf[i] - nf[i - 1]) * pow2[i - 1];
	return ans;
}
signed main()
{
	pow2[0] = 1;
	for(int i = 1 ; i <= 10 ; i ++) pow2[i] = pow2[i - 1] * 2;
	scanf("%lld%lld" , &n , &m); cin >> S; S = '_' + S;
	g[0][0] = 1;
	for(int s = 0 ; s < (1 << n) ; s ++) for(char c = 'a' ; c <= 'z' ; c ++) mp[s][c - 'a'] = F(s , c);
//	for(int i = 0 ; i < m ; i ++) for(int s = 0 ; s < (1 << n) ; s ++) for(char c = 'a' ; c <= 'z' ; c ++) add(g[i + 1][F(s , c)] , g[i][s]);
	for(int i = 0 ; i < m ; i ++) for(int s = 0 ; s < (1 << n) ; s ++) if(g[i][s]) for(char c = 'a' ; c <= 'z' ; c ++) add(g[i + 1][mp[s][c - 'a']] , g[i][s]);
	for(int s = 0 ; s < (1 << n) ; s ++) add(ans[__builtin_popcount(s)] , g[m][s]);
	for(int i = 0 ; i <= n ; i ++) printf("%lld " , ans[i]);
	return 0;
}
// g[i][s] --> T 填到第 i 位，状态数为 s 的方案数
// f[i] S:i T:_ -1
// nf[i] S:i T:_
```

函数 $F(s,c)$ 中的 $s$ 表示上一行（$T$ 填到 $i-1$ 位时）整个 $f_{i-1,j}$ 的状态。其中的 $c$ 表示 $T_i$ 填入的字符。

在这个函数中，首先通过 $s$ 计算了上一行的 $f$ 值（这里使用一维数组）。接着计算当前行的 $nf$ 值。然后将其再次压入二进制并返回。

可以先看注释掉的那行，转移就是将 $g_{i+1,F(s,c)}$ 加上 $g_{i,s}$，原因是显著的。

然后可以在这上面加一些巨大的优化。

- 提前预处理出所有的 $F(s,c)$，因为这只和状态与 $26$ 个字符有关。这样在转移的时候就避免了重复计算过多次 $F(s,c)$ 的值。
- 判断 $g_{i,s}$ 是否有值。这个原因显然。其实容易发现有很多 $g_{i,s}$ 都是 $0$ 方案的，找一个小点的样例输出输出就能看出来了。

如此的时间复杂度为 $O(2^nm \times26)$。当然有一些 $<1$ 的常数。

当然，如果不加入这些优化，在此题中仍然可以通过。

但是[无法](https://www.luogu.com.cn/record/203697896)在其[双倍经验](https://www.luogu.com.cn/problem/P10614)中[通过](https://www.luogu.com.cn/record/203723876)。

但是[三倍经验](https://www.luogu.com.cn/problem/P4590)也能过。

---

## 作者：GUO120822 (赞：2)

$dp_{i,j}$ 表示前 $i$ 个，上一行状态为 $j$ 的方案数。

由于每一位最多相差 1，则可以差分，状压 0/1，状态只有 $2^n$ 个。

那么对于 $dp_{i,j}$，$dp_{i+1,j}$ 该如何转移呢？

枚举 a 到 z，对于这个字母 $c$，枚举 $n$ 个位置，对于 $f_{i,j}$：

若 $c=a_j$，则 $f_{i,j}=f_{i-1,j-1}$；

否则，$f_{i,j}=\max(f_{i-1,j},f_{i,j-1})$；

转移完毕之后差分一下，记录一下即可。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=11,M=105,mod=998244353;
int n,m,i,j,k,dp[M][1<<N],ans[N],f[N],t[N],cf[N],x;
char a[N],c;
int cnt(int x)
{
	int res=0;
	while (x)
	{
		res+=x&1;
		x>>=1;
	}
	return res;
}
int main() 
{
	scanf("%d%d%s",&n,&m,a);
	dp[1][0]=1;
	for (i=1;i<=m;i++)
	{
		for (j=0;j<(1<<n);j++)
		{
			for (k=0;k<n;k++) f[k]=((j>>k)&1);
			for (k=1;k<n;k++) f[k]+=f[k-1];
			for (c='a';c<='z';c++)
			{
				for (k=0;k<n;k++)
				{
					if (c==a[k]) t[k]=(!k?0:f[k-1])+1;
					else t[k]=max(f[k],(!k?0:t[k-1]));
				}
				cf[0]=t[0];
				for (k=1;k<n;k++) cf[k]=t[k]-t[k-1];
				x=0;
				for (k=0;k<n;k++) x+=(1<<k)*cf[k];
				dp[i+1][x]=(dp[i+1][x]+dp[i][j])%mod;
			}
		}
	}
	for (i=0;i<(1<<n);i++) ans[cnt(i)]=(ans[cnt(i)]+dp[m+1][i])%mod;
	for (i=0;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：ty_mxzhn (赞：2)

这个题应该是 dp of dp 板子题吧。

先回顾经典的 LCS 问题。设计 $f_{i,j}$ 表示 $S$ 截取了前 $i$ 位，$T$ 截取了前 $j$ 位时的 LCS 长度。

+ 从 $f_{i,j}$ 直接推到 $f_{i+1,j}$ 和 $f_{i,j+1}$。
+ 如果 $i+1$ 可以与 $j+1$ 匹配，则 $f_{i+1,j+1}=\max(f_{i+1,j+1},f_{i,j}+1)$。

考虑 dp of dp。设 $F_{i,S}$ 表示对于一个目前推到的 $i$，$S=f_i$ 时的方案数。

考虑显然 $f_{i,j} \in \{ f_{i,j-1},f_{i,j-1}+1\}$ 所以 $f$ 可以被压成一个二进制数。

转移时枚举这一位取什么和上一位的状压掩码。时间复杂度 $O(nm|\Sigma|2^n)$ 足以通过。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,p[17],q[17];
char s[17];
int dp[107][1<<10],ans[17];
const int mod=998244353;
void Add(int &x,int y){
	x+=y;
	if(x>=mod) x-=mod;
}
int DP(int s0,char c){
	for(int i=1;i<=n;i++) p[i]=p[i-1]+((s0>>(i-1))&1);
	for(int i=1;i<=n;i++){
		q[i]=max(p[i],q[i-1]);
		q[i]=max(q[i],p[i-1]+(c==s[i]));
	}
	int s1=0;
	for(int i=1;i<=n;i++){
		if(q[i]-q[i-1]>0) s1|=(1<<(i-1));
	}
	return s1;
}
signed main(){
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	dp[0][0]=1;
	for(int i=0;i<m;i++){
		for(char c='a';c<='z';c++){
			for(int j=0;j<(1<<n);j++){
				Add(dp[i+1][DP(j,c)],dp[i][j]);
			}
		}
	}
	for(int j=0;j<(1<<n);j++){
		//printf("%d %d\n",j,dp[m][j]);
		int w=0;
		for(int i=1;i<=n;i++) w+=((j>>(i-1))&1);
		Add(ans[w],dp[m][j]);
	}
	for(int i=0;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}
```

附三倍经验。

1. https://www.luogu.com.cn/problem/P10614

2. https://www.luogu.com.cn/problem/AT_abc391_g

3. https://www.luogu.com.cn/problem/P4590

---

## 作者：lml0928 (赞：2)

通过题目中 $n \leq 10$ 的条件，不难想到状压的方法。
而题目让我们计算有多少种方法能达到特定的 LCS，当然，我们要先回顾 LCS 的做法。

我们使用 DP 来求两个字符串 $s, t$ 的 LCS。定义一个二维数组 $dp_{i,j}$ 表示 $s$ 的前 $i$ 个字符和 $t$ 的前 $j$ 个字符的 LCS 长度。转移方程是：
$$
dp_{i,j}=\max(\{dp_{i,j-1},dp_{i-1,j},(dp_{i-1,j-1}+1)[s_i=t_j]\})
$$

>注：接下来第一维称为行，第二维称为列。

显然，对于 $dp$ 数组的每一列，按照行号排列后，对应的值是单调不降的。而且，由于

$$
dp_{i,j} \leq dp_{i-1,j-1}+1 \leq dp_{i-1,j}+1
$$

可知，每一列的差分数组只包含 $0$ 和 $1$。于是，我们可以对每一列进行状压来进行 DP。
#### 状态定义
定义 $dp_{i,arr}$ 表示长为 $i$ 的，且 LCS 的 DP 数组中第 $i$ 列差分数组的状压为 $arr$ 的合法字符串的个数。
#### 初始值
显然，有 $dp_{0,0}=1$,其他为 $0$。
#### 转移
我们采用刷表法。

先枚举 $i$ 表示上一列，再枚举 $j$ 表示差分数组的状压。接着，我们枚举所有小写字母，设当前枚举到了 $c$。我们按照如下的方法转移。

1. 将 $j$ 还原成 DP 数组，存在数组 $tmp$ 中。（简单前缀和加位运算）
2. 从后往前枚举 $k$，如果 $s_k=c$，则令 $tmp_k=max(\{tmp_k,tmp_{k-1}+1\})$。（这一步有点像 01 背包的滚动数组，要用上一列的结果）
3. 从前往后枚举 $k$，令 $tmp_k=max(\{tmp_k,tmp_{k-1}\})$。（这一步有点像完全背包的滚动数组，要用自己列的结果）
4. 把这个数组还原回状压的值，并转移。
#### 答案
发现一个状态的 LCS 就是它的 $\operatorname{popcount}$，因为这代表了差分数组中 $1$ 的个数，就是差分数组的总和。我们直接把它统计到对应的位置上即可。
#### 小优化
刷到某个 $i,j$ 时，如果 $dp_{i,j}=0$，则我们可以直接跳过转移。

---

## 作者：Chenyichen0420 (赞：2)

## 思路分析

一眼 DP，想一下有没有好写一点的方法。我们令 $dp_{i,p}$ 表示 $m$ 个空位已经填了前 $i$ 个，匹配上了集合 $p$。$p$ 从低到高二进制压位。

这时候，因为每一个新的字符匹配后面的字符一定比覆盖 $p$ 更优，因此我们只要预处理出 $p$ 加上字符 $c$ 之后的新集合即可。

怎么预处理呢？首先，我们处理出这个状态下前 $i$ 个匹配到了几个。然后看每一个位置能不能匹配上字符 $c$，能就在前一个位置原状态的基础上抬高一个，每个位置取 $\max$ 即可。

然后枚举每一个位置，如果和前面的不一样就说明被更新了，将新状态对应的位置为一即可。

然后你会发现不对劲，你这么算，遇到 `bab` 这样的老六字符串。你算一下 $p=4,c=2$ 的值，诶！他等于 $1$！

这年头，连 $dp$ 都会回滚了，准备高斯消元……吗？

再仔细一看，你有一个 $b$ 的时候，你会先去匹配后面那个 $b$ 吗？不会啊！妥妥的不合法状态啊！

就这样，这个预处理还顺便的噶掉了不合法状态！

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define mp for (int p = 0; p != 1ll << n; p++)
#define mc for (int c = 1; c <= 26; c++)
constexpr int md = 998244353;
inline void mad(int& l, const int r) { (l += r) >= md && (l -= md); }
int t, n, m, f[105][1ll << 10 | 2], ans[105]; char s[12];
int nxt[1ll << 10 | 2][30], g1[105], g2[105];
signed main() {
	ios::sync_with_stdio(0);
	cin >> n >> m >> (s + 1); f[0][0] = 1;
	mp{
		for (int i = 1; i <= n; i++)
			g1[i] = g1[i - 1] + ((p >> (i - 1)) & 1);
		mc {
			for (int i = 1; i <= n; i++) {
				g2[i] = max(g2[i - 1], g1[i]);
				if (c == s[i] - 'a' + 1)
					g2[i] = max(g2[i], g1[i - 1] + 1);
			}
			for (int i = 1; i <= n; i++)
				nxt[p][c] |= ((g2[i] - g2[i - 1]) << (i - 1));
		}
	}
	for (int i = 0; i != m; i++)
		mp mc mad(f[i + 1][nxt[p][c]], f[i][p]);
	mp mad(ans[bitset<20>(p).count()], f[m][p]);
	for (int i = 0; i <= n; i++) cout << ans[i] << " ";
}
```

---

## 作者：Milthm (赞：1)

我们想一下我们平时是怎么做 LCS 的，设 $dp_{i,j}$ 表示 $s$ 的前 $i$ 个字符与 $t$ 的前 $j$ 个字符的 LCS，则有：

- 若 $s_i=t_j$，$dp_{i,j}=dp_{i-1,j-1}+1$。

- 否则，$dp_{i,j}=\max(dp_{i-1,j},dp_{i,j-1})$。

现在要求满足条件的 $t$ 的个数了，我们可以设 $dp_{i,s_2}$ 表示满足 $t$ 的前 $i$ 个字符与 $s$ 的 LCS 是 $s_2$ 的 $t$ 的个数，然后转移的时候枚举下一位是什么就可以。

那么问题来了，这个东西的状态看起来很多，我们应该如何优化？

事实上，我们可以先把 $s_2$ 换成我们开头那个 dp 数组中的一行，因为我们知道这一行就知道了下一行的状态。接下来，因为每增加一位 LCS 最多增加 $1$，所以我们最开头说的那个 dp 数组的相邻两行的差分只可能是 $0$ 或 $1$（所以再用差分数组代替 dp 数组）。然后我们需要做的就是：

- 先预处理出来每个差分数组后面添加每个字符会变成的差分数组。

- 转移时枚举后面是哪一位，更新 dp 状态。

这两部分都可以采用状压处理，总时间复杂度为 $O(2^nm(n+\alpha))$，其中 $\alpha$ 为字母表大小 $26$。


```cpp
#include<bits/stdc++.h>
#define N 105 
using namespace std;
const int mod=998244353;
string s;
int T,n,m,a[N],dp[N][1<<15],g[N],f[N],nxt[1<<15][N],ans[N];
void qm(int &x){
	if(x>=mod)x-=mod;
}
int add(int S,int nxt){
	for(int i=1;i<=n;++i)g[i]=g[i-1]+((S>>(i-1))&1);
	for(int i=1;i<=n;++i){
		if(a[i]==nxt)f[i]=g[i-1]+1;
		else f[i]=max(g[i],f[i-1]);
	}
	int ans=0;
	for(int i=1;i<=n;++i)ans+=(f[i]-f[i-1])<<(i-1);
	return ans;
}
signed main(){
	cin>>n>>m>>s;s=" "+s;
	for(int i=1;i<=n;++i)a[i]=s[i]-'a'+1;
	for(int i=0;i<(1<<n);++i){
		for(int j=1;j<=26;++j)nxt[i][j]=add(i,j);
	}
	dp[0][0]=1;
	for(int i=0;i<m;++i){
		for(int j=0;j<(1<<n);++j){
			if(!dp[i][j])continue;
			for(int k=1;k<=26;++k){
				qm(dp[i+1][nxt[j][k]]+=dp[i][j]);
			}
		}
	}
	for(int i=0;i<(1<<n);++i)qm(ans[__builtin_popcount(i)]+=dp[m][i]);
	for(int i=0;i<=n;++i)cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：D0000 (赞：1)

DP 套 DP 板子题。

记 $f_{i,A}$ 表示构造序列前 $i$ 位与 $S$ 的最长公共子序列 DP 数组为 $A$ 的方案数。其中 $A$ 是一个长 $n$ 的数组，$A_j$ 为 $A$ 的前 $j$ 位与构造序列前 $i$ 位的最长公共子序列长度。这样对于一个数组状态 $A$ 和一个字符 $c$ 可以唯一确定在构造序列末尾添加 $c$ 后数组 $A$ 会变成的 $A'$。

这样做唯一的瓶颈在于 $A$ 是长度为 $n$ 的数组，但是注意 $A_1,A_i+1-A_i\le1$，因此将 $A$ 改为差分序列状压就可以了。

预处理数组 $A$ 添加每个字符会变成的 $A'$，时间复杂度做到 $(n+m)2^n|\sum^*|$，其中 $|\sum^*|$ 是字符集大小，此处为 $26$。

### 代码

```cpp
#include<cstdio>
#include<algorithm>
int n,m;
char s[19];
int ch[500005][26],a[500005],l[500005],mod=998244353,ans[16];
int main(){
    scanf("%d%d%s",&n,&m,s+1);
    for(n=1;s[n];n++)ans[n]=0;n--,ans[0]=0;
    for(int i=0;i<1<<n;i++)for(int j=0;j<26;j++){
        int res=0,rtt[19];rtt[0]=0;
        for(int k=1;k<=n;k++)rtt[k]=rtt[k-1]+bool((1<<(k-1))&i);//printf("%d\n",rtt[2]);
        for(int k=n;k;k--)if(s[k]-'a'==j)rtt[k]=rtt[k-1]+1;
        for(int k=1;k<=n;k++)rtt[k]=std::max(rtt[k],rtt[k-1]);
        for(int k=1;k<=n;k++)res^=(1<<(k-1))*(rtt[k]-rtt[k-1]);
        ch[i][j]=res;
        //printf("%d %d %d %d %d\n",rtt[1],rtt[2],i,j,res); 
    }
    for(int i=1;i<1<<n;i++)a[i]=0;a[0]=1;
    for(int i=1;i<=m;i++){
        for(int j=0;j<1<<n;j++)l[j]=a[j],a[j]=0;//,printf("%d %d\n",j,l[j]);
        for(int j=0;j<1<<n;j++)for(int k=0;k<26;k++)a[ch[j][k]]=(a[ch[j][k]]+l[j])%mod;
    }
    for(int i=0;i<1<<n;i++){//printf("%d %d\n",i,a[i]);
        int res=0;
        for(int j=0;j<n;j++)if((1<<j)&i)res++;
        
        ans[res]=(ans[res]+a[i])%mod;
    }
    for(int i=0;i<=n;i++)printf("%d ",ans[i]);
}
```

---

## 作者：dayz_break404 (赞：1)

dp 套 dp 板子题。

考虑固定构成的字符串为 $T$ 后，其与 $S$ 的经典转移方程：

$$dp_{i,j}=\begin{cases} dp_{i-1,j-1}+1,s_i=t_j\\ \max(dp_{i,j-1},dp_{i-1,j}),s_i\neq t_j\end{cases}$$

考虑将其作为外层 dp 数组的一层状态，那么转移就相当于就是枚举当前加入哪一个字符，根据当前的字符来更新内层 dp 数组的状态。

将数组作为状态的一维显然不现实，将内层 dp 看作一个二维表格，每次在 $T$ 后面添加字符相当于就是在这个表格内加一行或者一列。不妨钦定为列，那么当前列的值只会由上一列得到，并且发现对于一列而言，差分后的序列只会有 $0$ 或者 $1$，于是就可以愉快状压了。

内层就是一个 DFA 转移的过程，预处理转移函数 $nxt_{s,i}$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
#define ll long long
const int mod=998244353;
const int maxn=1030;
ll t,n,m,nxt[maxn][27],dp[101][maxn],a[maxn],g[maxn],h[maxn],ans[maxn];
char s[20];
int main(){
	n=read(),m=read();
	cin>>(s+1);
	for(int i=1;i<=n;i++) a[i]=s[i]-'a';
	for(int s=0;s<(1<<n);s++){
		for(int i=1;i<=n;i++) g[i]=g[i-1]+((s>>(i-1))&1);
		for(int i=0;i<=25;i++){
			for(int j=1;j<=n;j++){
				if(i==a[j]) h[j]=g[j-1]+1;
				else h[j]=max(g[j],h[j-1]);
			}
			int now=0;
			for(int j=1;j<=n;j++) now+=((h[j]-h[j-1])<<(j-1));
			nxt[s][i]=now;
		}
	}
	dp[0][0]=1;
	for(int i=0;i<m;i++){
		for(int s=0;s<(1<<n);s++){
			for(int j=0;j<=25;j++) dp[i+1][nxt[s][j]]=(dp[i+1][nxt[s][j]]+dp[i][s])%mod;
		}
	}
	for(int i=0;i<(1<<n);i++) (ans[__builtin_popcount(i)]+=dp[m][i])%mod;
	for(int i=0;i<=n;i++) printf("%lld ",ans[i]%mod);
	return 0;
}
```

---

## 作者：Felix72 (赞：1)

求一个可以使用 DP 解决的问题的答案出现次数，考虑使用 DP 套 DP 解决。

设自动机（也可以理解成一个 DP 数组） $g_i$ 表示 LCS 的末尾元素取 $s_i$ 时，某个字符串和 $s$ 的最长公共子序列。设在这“某个字符串”后面加一个字符 $c$，$g$ 也会发生相应的变化（即一个 DP 转移过程），即 $g_i = \max(g_i, \max_{j = 1}^{i - 1}g_j + 1) \ (s_i == c)$。设 $f_{g, p}$ 表示已经添加 $p$ 个字符，自动机状态为 $g$ 的方案数。用 map 辅助转移。

但是这样 $g$ 的状态数是 $n!$ 的，不能保证上界，运行起来较慢。

因此我们修改定义，令 $h_i = \max_{j = 1}^{i} g_j$，可知 $h$ 递增，因此 $h$ 的状态数是长度、值域均在 $n$ 以内的递增（还要满足单次增量不超过 $1$）序列数量。这个状态数量级大大减小了，是 $2^n$ 级别，可以轻松通过。

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & (-x))
using namespace std;

const int N = 15, M = 110, mod = 998244353;
int n, m, res[N]; string s; bool vis[1024]; vector < char > occ;
struct State
{
	array < int, 11 > p;
	bool operator < (const State &w) const
	{
		for(int i = 1; i < n; ++i) if(p[i] != w.p[i]) return p[i] < w.p[i];
		return p[n] < w.p[n];
	}
	bool operator > (const State &w) const
	{
		for(int i = 1; i < n; ++i) if(p[i] != w.p[i]) return p[i] > w.p[i];
		return p[n] > w.p[n];
	}
};
int pr[N];
inline State trans(State f, char c)
{
	for(int i = 1; i <= n; ++i)
		pr[i] = max(pr[i - 1], f.p[i]);
	for(int i = n; i >= 1; --i)
		if(s[i] == c)
			f.p[i] = max(f.p[i], pr[i - 1] + 1);
	for(int i = 2; i <= n; ++i) f.p[i] = max(f.p[i], f.p[i - 1]);
	return f;
}
map < State, int > mp[M];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	cin >> s; s = ' ' + s;
	for(int i = 1; i <= n; ++i)
		if(!vis[s[i]])
			{vis[s[i]] = true; occ.push_back(s[i]);}
	State emp; emp.p.fill(0);
	mp[0][emp] = 1;
	for(int i = 0; i < m; ++i)
	{
		for(pair < State, int > pii : mp[i])
		{
			State now = pii.first; int val = pii.second;
			for(char c : occ)
			{
				State to = trans(now, c);
				mp[i + 1][to] = (mp[i + 1][to] + val) % mod;
			}
			mp[i + 1][now] = (mp[i + 1][now] + 1ll * val * (26 - occ.size()) % mod) % mod;
		}
	}
	for(pair < State, int > pii : mp[m])
	{
		State now = pii.first; int val = pii.second;
		int maxn = 0;
		for(int i = 1; i <= n; ++i) maxn = max(maxn, now.p[i]);
		res[maxn] = (res[maxn] + val) % mod;
	}
	for(int i = 0; i <= n; ++i) cout << res[i] << " "; cout << '\n';
	return 0;
}
/*

*/
```

---

## 作者：SunburstFan (赞：1)

## [\[ABC391G\] Many LCS](https://www.luogu.com.cn/problem/AT_abc391_g)

### 题目大意
有一个长度为 $N$ 的小写英文字符串 $S$。需要统计对于所有可能的长度为 $M$ 的小写英文字符串 $T$，它们与 $S$ 的最长公共子序列长度为 $0,1,2,\dots,N$ 各自为多少。

### 解题思路

dp of dp，之前并没有做过这类的题目。

回忆计算 $\operatorname{LCS}$ 的过程，注意到状态转移数组 `f` 的差分数组只由 `0` 和 `1` 组成。

对原串 $S$ 的状态进行位压缩，以二进制表示子序列选取情况。

对每个状态 $S$ 和待加入的字母 $x$，使用一个转移函数求出新状态。DP 里再根据已经转移到的子序列与生成的字母数位置，累加结果。

时间复杂度 $O(26 \times (n + m) \times 2^n)$。

这里给出核心代码：

```cpp
for(int i=1;i<=n;i++){
        a[i]=s[i-1]-'a';
    }
    for(int S=0;S<(1<<n);S++){
        for(int i=0;i<26;i++){
            nxt[S][i]=calc(S,i);
        }
    }

    f[0][0]=1;
    for(int i=0;i<m;i++){
        for(int S=0;S<(1<<n);S++){
            for(int j=0;j<26;j++){
                f[nxt[S][j]][i+1]=(f[nxt[S][j]][i+1]+f[S][i])%mod;
            }
        }
    }

```

`calc` 部分略。

---

## 作者：rubbishZZZ (赞：0)

##  ABC391G Many LCS



#### 题意：

- 给定长度为 $n$ 的由小写字母组成的字符串 $S$ 与整数 $m$，对于 $k=0,1,\cdots,n$，求解以下问题：

  有 $26^m$ 个长度为 $m$，由小写字母构成的字符串。在这些字符串中，有多少个字符串与 $S$ 的最长公共子串恰好为 $k$。



#### 解法：

- 考虑一个给定的长度为 $m$ 的字符串 $T$，如何求解 $\operatorname{LCS}(S,T)$。

  我们可以设 $f_{i,j}$ 表示考虑了 $T$ 的前 $i$ 位与 $S$ 的前 $j$ 位的最长公共子序列。

  转移时 $f_{i,j}=\max(f_{i-1,j},f_{i,j-1},f_{i-1,j-1}+[T_i=S_j])$。

  但是对于多个 $T$ 同时处理，$f$ 的第二维是一个不可分割的整体。又观察到 $n$ 的范围较小，考虑用一种方法将第二维压成一个值。

  对于某个 $i$，$\{f_{i,0},f_{i,1},\cdots,f_{i,n}\}$ 的方案数看起来就不会很多，我们发掘性质一下其中的性质。

  由于 $f_{i,j}$ 对 $f_{i,j-1}$ 取了 $\max$，而 $f_{i,j-1}\geq f_{i-1,j-1}$，故 $0\leq f_{i,j}-f_{i,j-1}\leq 1$。

  自然地想到将 $f_{i,*}$ 做差分，差分后只剩 $01$，那么就可以压成一个二进制数。

  我们对于多个 $T$ 在外层做 DP。设 $g_{i,j}$ 表示考虑了 $T$ 的前 $i$ 位，$\{f_{i,*}\}$ 差分后的二进制数为 $j$ 的方案数。

  转移时枚举 $T$ 的第 $i+1$ 位放什么，接着使用 $j$ 还原出 $f_{i,*}$ 并计算出 $f_{i+1,*}$，再将 $f_{i+1,*}$ 压成二进制数 $k$ 转移到 $g_{i+1,k}$。这样的复杂度为 $O(nm2^n\Sigma)$。

  事实上我们发现通过枚举字符 $c$，并将 $j$ 转化成 $k$ 的步骤是重复的，可以预处理 $h_{c,j}$ 表示枚举的字符为 $c$，当前状态为 $j$ 所转移到的状态。

  预处理部分的复杂度为 $O(n2^n\Sigma)$，但是这样 $g$ 转移的复杂度就变成了 $O(\Sigma)$，此时从复杂度 $O((n+m)2^n\Sigma)$。



#### 代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <ctime>
#include <random>
#include <cassert>
#include <numeric>
#include <cmath>
#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#define pii pair<int, int>
#define fi first
#define se second
#define MP make_pair
#define ep emplace
#define eb emplace_back
//#define int long long
#define rep(i, j, k) for (int i = (j); i <= (k); i++)
#define per(i, j, k) for (int i = (j); i >= (k); i--)
typedef double db;
typedef long double ldb;
typedef long long ll;
//typedef __int128 lll;
typedef unsigned long long ull;
typedef unsigned int ui;
using namespace std;
using namespace __gnu_pbds;
bool Mbe;

//char buf[1<<20],*p1,*p2;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)
int read() {
	int s = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') f ^= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') s = s * 10 + c - '0', c = getchar();
	return f ? s : -s;
}

const int mod=998244353;
char s[20];
int n,m,tr[1<<11][26],f[20],g[20],dp[2][1<<11],ans[20];
int turn(char c){return c-'a';}

bool Med;
signed main() {
//	printf("%.3lfMb\n",(&Mbe-&Med)/1024./1024.);
	n=read(),m=read();
	scanf("%s",s+1);
	rep(S,0,(1<<n)-1){
		rep(i,1,n)g[i]=g[i-1]+(S>>(i-1)&1);
		rep(c,0,25){
			int SS=0;
			rep(i,1,n)f[i]=max({g[i],f[i-1],g[i-1]+(turn(s[i])==c)});
			rep(i,1,n)SS|=(f[i]-f[i-1])<<(i-1);
			tr[S][c]=SS;
		}
	}
	dp[0][0]=1;
	int o=0;
	rep(i,1,m){
		memset(dp[o^1],0,sizeof dp[o^1]);
		rep(S,0,(1<<n)-1)if(dp[o][S]){
			rep(c,0,25)(dp[o^1][tr[S][c]]+=dp[o][S])%=mod;
		}
		o^=1;
	}
	rep(S,0,(1<<n)-1){
		rep(i,1,n)f[i]=f[i-1]+(S>>(i-1)&1);
		(ans[f[n]]+=dp[o][S])%=mod;
	}
	rep(i,0,n)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：RiceFruit (赞：0)

看到这么小的数据范围，一眼 DP 套 DP，考虑如何求最长公共子序列，设 $f_{i,j}$ 表示 $s$ 的前 $i$ 个和 $t$ 的前 $j$ 个构成的最长公共子序列，那么可以从 $f_{i-1,j-1},f_{i-1,j},f_{i,j-1}$ 转移过来，考虑用 $f_i$ 表示一个长度为 $n+1$ 的数组，那么可以发现 $f_i-f_{i-1}\in [0,1],i>0$，从而得到 $f_i$ 只有 $2^n$ 个状态，于是把 $f_i$ 压到动态规划的状态里，直接转移即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 11, M = 101, mod = 998244353;
int n, m;
char a[N];
void solve(int a[], int st) {
    a[0] = 0;
    for (int i = 1; i <= n; ++i) a[i] = a[i - 1] + (st >> (i - 1) & 1);
    return;
}
int calc(int a[]) {
    int st = 0;
    for (int i = n; i >= 1; --i) st = st * 2 + a[i] - a[i - 1];
    return st;
}
inline void add(int &x, int y) {
    x += y;
    if (x >= mod) x -= mod;
    return;
}
int f[1 << N], g[1 << N], dp[N], pdp[N], res[N];
int main() {
    scanf("%d%d%s", &n, &m, a + 1);
    f[0] = 1;
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < (1 << n); ++j) g[j] = f[j], f[j] = 0;
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            for (int j = 0; j < (1 << n); ++j) {
                solve(dp, j), pdp[0] = 0;
                for (int k = 1; k <= n; ++k) {
                    pdp[k] = max(pdp[k - 1], dp[k]);
                    if (ch == a[k]) pdp[k] = max(pdp[k], dp[k - 1] + 1);
                }
                add(f[calc(pdp)], g[j]);
            }
        }
    }
    for (int i = 0; i <= (1 << n); ++i) add(res[__builtin_popcount(i)], f[i]);
    for (int i = 0; i <= n; ++i) printf("%d ", res[i]);
    return 0;
}
```

---

## 作者：Thomas0702 (赞：0)

这是 dp of dp 吗？

考虑我们是怎么求两个字符串 $S,T$ 的 LCS 的，设 $f_{i,j}$ 表示考虑 $S[1,\dots,i],T[1,\dots,j]$，它们的 LCS 是多少。有转移：
$$f_{i,j}\gets f_{i-1,j}$$
$$f_{i,j}\gets f_{i,j-1}$$
$$f_{i,j}\gets f_{i-1,j-1}\times[S_i=T_j]$$
$\gets$ 是取 $\max$ 操作。

考虑对 $f$ dp。设 $g_{i,a}$ 表示考虑所有长度为 $i$ 的字符串，$f_i=a$ 的字符串数量，其中 $a$ 是一个数组。即：有 $g_{i,a}$ 个长度为 $i$ 的字符串，$\forall1\leq j\leq N$，与 $S[1,\dots,j]$ 的 LCS 长度是 $a_j$。
![a的图示](https://cdn.luogu.com.cn/upload/image_hosting/nggt07s0.png)
考虑用 map 维护 $g$，把所有可能的 $a$ 的形态以及对应的方案数全都丢进去。每次转移，枚举字符串的下一个字符是什么，遍历上一个 map 里的所有 $a$，转移得到新的 $a$，丢到下一个 map 里。

最后，根据 $a_N$ 是多少统计答案即可。

考虑 $a$ 的差分数组，每个位置只可能是 $0$ 或 $1$，因为 $LCS(S+c,T)\leq LCS(S,T)+1$，所以 $a$ 的总数为 $O(2^N)$。所以时间复杂度为 $O(2^NNM|\Sigma|)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define fir first
#define sec second
using namespace std;
void rd(){}
template<typename T,typename... U> void rd(T &x,U&... arg){
	x=0;int f=1,c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=x*10+c-48,c=getchar();
	x*=f;rd(arg...);
}
typedef array<int,12> info;
const int P=998244353;
map<info,ll> f[2];
int N,M;
char s[15];
ll ans[15];
int main(){
	scanf("%d%d%s",&N,&M,s+1);
	info ept;
	for(int i=0;i<12;i++) ept[i]=0;
	f[0][ept]=1;
	int t=0;
	for(int i=1;i<=M;i++){
		f[t^=1].clear();
		for(auto it:f[t^1])
			for(char c='a';c<='z';c++){
				info b=it.fir;
				for(int j=1;j<=N;j++){
					b[j]=max(b[j],b[j-1]);
					if(c==s[j]) b[j]=max(b[j],it.fir[j-1]+1);
				}
				(f[t][b]+=it.sec)%=P;
			}
	}
	for(auto i:f[t]) (ans[i.fir[N]]+=i.sec)%=P;
	for(int i=0;i<=N;i++) printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：Lovely_Sun (赞：0)

###### 转发
---

[G - Many LCS](/contests/abc391/tasks/abc391_g) 题解 by [en\_translator](/users/en_translator)
--------------------------------------------------------------------------------------------

* * *

让我们简要回顾一下如何求出 $T$ 和 $S$ 的最长公共后序列（LCS）的长度。

> 准备一个大小为 $(|T|+1)\times (|S|+1)$ 的数组 $dp$ （DP 表示动态编程），其中 $dp[i][j]$ 表示 $T[:i]$ 和 $S[:j]$ 的最长公共序列的长度。有三种过渡：
>
> 1. $dp[i][j] \leftarrow dp[i-1][j]$
> 2. $dp[i][j] \leftarrow dp[i][j-1]$
3. $dp[i][j] \leftarrow dp[i-1][j-1]+1$ if $T[i]=S[j]$ > 3.

仔细观察这些转换，我们会发现 DP 数组具有以下特性：

- $dp[i][0]=0$
- $0\leq dp[i][j+1]-dp[i][j]\leq 1$

也就是说， $dp[i]$ 是一个弱单调递增序列，相邻元素最多相差一个。因此， $2^{|S|}$ 只有 $dp[i]$ 种可能的模式。

我们利用这一事实来解决原问题。假设 $DP[i][dp\_array]$ 是长度为 $i$ 的字符串 $T$ 的个数，当找到 $T$ 和 $S$ 的 LCS 时， $dp\_array$ 是 DP 数组 $dp[i]$ 。随着 $i$ 的增加， $dp\_array$ 上的更新可以根据上述 LCS DP 的转换找到。 $DP[i]$ 有 $O(2^N)$ 个状态，计算 $dp\_array$ 的转换需要花费 $O(\sigma N)$ ，因此总体复杂度为 $O(NM\sigma 2^N)$ （其中 $\sigma$ 是字母表的大小）。通过预先计算转换，复杂度可降至 $O(NM2^N)$ 。

```
from collections import defaultdict

mod = 998244353

N, M = map(int, input().split())
A = [ord(i) - ord("a") for i in input()]
K = 26
dp = defaultdict(int)
dp[tuple([0] * (N + 1))] = 1
for _ in range(M):
    ndp = defaultdict(int)
    for arr, c in dp.items():
        for i in range(K):
            narr = [0] * (N + 1)
            for j in range(N):
                narr[j + 1] = max(narr[j], arr[j + 1])
                if A[j] == i:
                    narr[j + 1] = max(narr[j + 1], arr[j] + 1)
            ndp[tuple(narr)] = (ndp[tuple(narr)] + c) % mod
    dp = ndp
ans = [0] * (N + 1)
for arr, c in dp.items():
    ans[arr[N]] += c
print(*[i % mod for i in ans])
```

---

## 作者：liruixiong0101 (赞：0)

看到 $n,m$ 都很小，考虑最暴力的 dp。

回顾一下 LCP 怎么求，设 $f_{i,j}$ 为匹配到 $T$ 的第 $i$ 位和 $S$ 的第 $j$ 位的最长公共子序列，转移式为：
$$
\begin{gathered}
{f_{0,0}=f_{1,0}=f_{0,1}=0}\\
{f_{i,j}\gets f_{i-1,j}}\\
f_{i,j}\gets f_{i,j-1}\\
\text{if}\ T[i] = S[j]\ \text{then}\ f_{i,j}\gets f_{i-1,j-1}+1
\end{gathered}
$$

那么答案就是 $f_{m,n}$。

我们可以在记方案数的 dp 状态里加上 $f$，我们设 $g_{i,f}$ 表示匹配到 $T$ 的第 $i$ 位时，数组 $f_i$ 为 $f$ 的方案数。这个状态的转移是简单的，我们枚举 $T$ 的第 $i$ 位选什么，然后从 $f_{i-1}$ 更新到 $f_i$ 就可以转移了。

但是现在的问题就是我们无法在 dp 数组的状态里加入 $f$ 这一维度，因为它实在是太大了。

我们仔细观察 $f$ 的转移，我们可以发现它的一些性质。对于固定的 $i$ 都有：
- $f_{i,0}=0$。
- $f_{i,j}\le f_{i,j+1}\le f_{i,j}+1$。

第二个性质让我们发现 $f_i$ 相邻两项的差不超过 $1$，这非常棒，这说明了 $f$ 的差分数组只可能有 $2^n$ 个，那么 $f$ 也只可能有 $2^n$ 个，所以我们可以在 $g_{i,f}$ 中将 $f$ 改存为 $f$ 的差分数组，并将其压缩成一个二进制数，这样的复杂度就是对的了。时间复杂度：$\mathcal{O}(nm2^n|\sum|)$（当然我们也可以通过预处理做到 $\mathcal{O}(m2^n|\sum|)$），空间复杂度：$\mathcal{O}(m2^n)$。

这种 dp 我们把它称为 dp 套 dp。

---

## 作者：ivyjiao (赞：0)

三倍经验：[P4590 [TJOI2018] 游园会](https://www.luogu.com.cn/problem/P4590)、[P10614 BZOJ3864 Hero meet devil](https://www.luogu.com.cn/problem/P10614)、[AT_abc391_g [ABC391G] Many LCS](https://www.luogu.com.cn/problem/AT_abc391_g)。

---

DP of DP 题目。

这道题的内层 DP 是 LCS，回忆 LCS 的 DP 方程：

设此时 $S$ 为第 $i$ 位，$T$ 为第 $j$ 位，则有：

$dp_{i,j}= \begin{cases}
  dp_{i-1,j-1}+1 & S_i=T_j \\
  \max(dp_{i-1,j},dp_{i,j-1}) & S_i\neq T_j
\end{cases}$

我们考虑状压 dp，预处理出每个 LCS 状态 $A$ 后面接每个字母与 $S$ 的 LCS 的状态是什么，容易发现这个操作与原串无关，等价于在 LCS 数组下面加一个 $x$，我们只需要匹配新加进来的这一位就能得出答案。记为 $nxt_{A,x}$，$x$ 为后面接的东西。

状压过程就是长为 $n$ 的字符串，对于每一位，$0$ 是不在 $S$ 与 $T$ 的 LCS 中，$1$ 是在，详见代码。

设 $f_{i,A}$ 为考虑 $T$ 的前 $i$ 位，与 $S$ 的 LCS 为 $A$ 的方案数。

对于每个 $x$，每次转移从 $f_{i,A}$ 转移到 $f_{i+1,nxt_{A,x}}$。

初值就是 $f_{0,0}=1$。

时间复杂度 $O(mk\times 2^n)$，此题 $k=26$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int p=1e9+7;
int t,n,m,dp[1001][1<<15],g[16],h[16],nxt[1<<15][5],a[16],ans[16];
char s[16];
int get(int S,int c){
    int ans=0;
    for(int i=1;i<=n;i++) g[i]=g[i-1]+((S>>(i-1))&1);
    for(int i=1;i<=n;i++){
        if(a[i]==c) h[i]=g[i-1]+1;
        else h[i]=max(h[i-1],g[i]);
    }
    for(int i=1;i<=n;i++) ans+=(1<<(i-1))*(h[i]-h[i-1]);
    return ans;
}
int main(){
    cin>>t;
    while(t--){
        memset(ans,0,sizeof ans);
        memset(dp,0,sizeof dp);
        scanf("%s",s+1);
        cin>>m;
        n=strlen(s+1);
        for(int i=1;i<=n;i++){
            if(s[i]=='A') a[i]=1;
            if(s[i]=='T') a[i]=2;
            if(s[i]=='G') a[i]=3;
            if(s[i]=='C') a[i]=4;
        }
        for(int S=0;S<(1<<n);S++){
            nxt[S][1]=get(S,1);
            nxt[S][2]=get(S,2);
            nxt[S][3]=get(S,3);
            nxt[S][4]=get(S,4);
        }
        dp[0][0]=1;
        for(int i=0;i<m;i++){
	        for(int S=0;S<(1<<n);S++){
                (dp[i+1][nxt[S][1]]+=dp[i][S])%=p;
                (dp[i+1][nxt[S][2]]+=dp[i][S])%=p;
                (dp[i+1][nxt[S][3]]+=dp[i][S])%=p;
                (dp[i+1][nxt[S][4]]+=dp[i][S])%=p;
            }
        }
        for(int S=0;S<(1<<n);S++) (ans[__builtin_popcount(S)]+=dp[m][S])%=p;
        for(int i=0;i<=n;i++) cout<<ans[i]<<endl;
    }
}
```

---

## 作者：_Kenma_ (赞：0)

## 前言

推销博客：[here.](https://www.cnblogs.com/Kenma/p/18696757)

## 正文

游园会.jpg

但是我做这个题的时候已经忘了游园会怎么做了。

不难发现是 DP of DP，外层是对 $T$ 形态的 DP，内层是对 $S$ 和 $T$ 的 LCS 的 DP。

考虑 LCS 的 DP，设 $f_{i,j}$ 表示 $T$ 匹配到 $i$ 位置，$S$ 匹配到 $j$ 位置的 LCS。

在外层 DP 时，记录内层 DP 的状态，也就是记录 $f_i$ 就行了。

设 $g_{i,s}$ 表示考虑到 $T$ 的前 $i$ 位，$S$ 和 $T$ 的 LCS DP 数组为 $s$ 的方案数。

枚举当前位置填什么字符，在内层求出 $s$ 的变化，直接转移即可。

因为 $0\le f_{i,j}-f_{i,j-1} \le 1$，所以 $s$ 的上界为 $2^n$。

在实现上，为了方便，可以在状态中记录 $f_i$ 的差分数组。

总体复杂度为 $O(m\sigma 2^m)$，$\sigma$ 是字符集大小。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
char a[15];
int g[15],h[15],n,m,ans;
int get(int ch,int s){
	int t=0;
	for(int i=1;i<=n;i++){
		g[i]=g[i-1]+(bool)(s&(1<<(i-1)));
    }
	for(int i=1;i<=n;i++){
		if(a[i]-'a'==ch) h[i]=g[i-1]+1;
		else h[i]=max(h[i-1],g[i]);
	}
	for(int i=1;i<=n;i++){
		t|=(1<<(i-1))*(h[i]-h[i-1]);
	}
	return t;
}
int f[101][1025];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	f[0][0]=1;
	for(int i=1;i<=m;i++){
		for(int s=0;s<(1<<n);s++){
			for(int j=0;j<26;j++){
				int t=get(j,s);
				f[i][t]=(f[i][t]+f[i-1][s])%mod;
			}
	    }
	}
	for(int i=0;i<=n;i++){
		ans=0;
		for(int s=0;s<(1<<n);s++){
			if(__builtin_popcount(s)==i) ans=(ans+f[m][s])%mod;
		}
		cout<<ans<<' ';
	}
	return 0;
}
```

---

