# BZOJ3864 Hero meet devil

## 题目描述

给定一个字符集为 `ACGT` 的字符串 $S$。定义 $\text{LCS}(S,T)$ 为两个字符串 $S,T$ 的最长公共子序列。

对于每个 $0\leq i \leq |S|$，求有多少个长度为 $m$，字符集 `ACGT` 的字符串 $T$，满足 $|\text{LCS}(S,T)|=i$，答案对 $10^9+7$ 取模。

## 说明/提示

对于 $100\%$ 的数据，保证 $1\leq T\leq 5$，$1\leq |S| \leq 15$，$1\leq m\leq 1000$。

## 样例 #1

### 输入

```
1
GTC
10```

### 输出

```
1
22783
528340
497452```

# 题解

## 作者：_fairytale_ (赞：8)

upd 2024.9.5：感谢 [@Auferstanden](https://www.luogu.com.cn/user/894526) 指出的代码错误，发现是 `ans[0]` 忘清空了，已修改。

欸这题啥时候登陆洛谷了，抢下第一篇题解！

经典 DP 套 DP 题目。

这道题的内层 DP 是 LCS，我们不妨想 LCS 的转移方程：

设 $g_{i,j}$ 为串 $s$ 的前 $i$ 位和串 $t$ 前 $j$ 位的 LCS，则

$$
g_{i,j}=
\begin{cases}
g_{i-1,j-1}+1&s_i=t_j\\
\max(g_{i-1,j},g_{i,j-1})&s_i\ne t_j
\end{cases}
$$

因此一个朴素的想法就是，设 $f_{i,S}$ 表示考虑串 $t$ 的前 $i$ 位，与串 $S$ 的 LCS 数组为 $S$ 的方案数。转移的时候考虑下一位放啥，然后先把 $S$ 转移到 $S'$，再从 $f_{i,S}$ 转移到 $f_{i+1,S'}$ 即可。

其实到这里已经可以了，这个 DP 看着状态数很恐怖，实际上状态数很少。

考虑在 $i$ 固定的时候，$g_i$ 这一行的差分数组。根据转移方程可知，差分数组只有 $0/1$ 两种数，又因为差分数组和 $g_i$ 这一行是双射，所以第二维大小最多为 $2^{|S|}$。

而且既然发现差分数组只有 $0/1$，那直接状压记第二维即可。

```cpp
#include<bits/stdc++.h>
bool Mst;
#define in(S,i) (((S)>>((i)-1))&1)
#define rep(x,qwq,qaq) for(int (x)=(qwq);(x)<=(qaq);++(x))
using namespace std;
#define mod 1000000007
int T;
int n,m;
string s;
#define maxm 1010
int f[maxm][(1<<15)];
int g[20],h[20];
void add(int &x,int y) {
	x+=y;
	if(x>=mod)x-=mod;
}
int a[20];
int append(int S,int nxt) {
	rep(i,1,n)g[i]=g[i-1]+in(S,i);
	rep(i,1,n) {
		if(a[i]==nxt)h[i]=g[i-1]+1;
		else h[i]=max({h[i-1],g[i]});
	}
	int reS=0;
	rep(i,1,n)reS+=(1<<(i-1))*(h[i]-h[i-1]);
	return reS;
}
int ans[20];
int nxt[(1<<15)][5];
void solve() {
	cin>>s>>m;
	n=s.length();
	s=" "+s;
	rep(i,1,n) {
		switch(s[i]) {
			case 'A':
				a[i]=1;
				break;
			case 'C':
				a[i]=2;
				break;
			case 'G':
				a[i]=3;
				break;
			case 'T':
				a[i]=4;
				break;
		}
	}
	rep(S,0,(1<<n)-1)rep(i,1,4)nxt[S][i]=append(S,i);
	f[0][0]=1;
	rep(i,0,m-1) {
		rep(S,0,(1<<n)-1) {
			if(f[i][S]==0)continue;
			add(f[i+1][nxt[S][1]],f[i][S]);
			add(f[i+1][nxt[S][2]],f[i][S]);
			add(f[i+1][nxt[S][3]],f[i][S]);
			add(f[i+1][nxt[S][4]],f[i][S]);
			f[i][S]=0;
		}
	}
	rep(i,0,n)ans[i]=0;
	rep(S,0,(1<<n)-1) {
		add(ans[__builtin_popcount(S)],f[m][S]);
		f[m][S]=0;
	}
	rep(i,0,n)cout<<ans[i]<<'\n';
}
bool Med;
signed main() {
	cerr<<(&Mst-&Med)/1024.0/1024.0<<" MB\n";
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：panxz2009 (赞：7)

[双倍经验](https://www.luogu.com.cn/problem/P4590)

首先考虑一个正常的 LCS 应该怎么求：

设 $f_{i,j}$ 表示 $S$ 串的前 $i$ 位与 $T$ 串的前 $j$ 位的最长公共子序列长度。
$$
f_{i,j} = 
\begin{cases}
\max(f_{i, j - 1}, f_{i - 1, j}) & S_i \ne T_j\\
f_{i,j} + 1 & S_i = T_j\\
\end{cases}
$$
从中可以发现一条重要性质：从 $f_{i, j - 1}$ 转移到 $f_{i, j}$，dp 值的差分数组只可能是 $0$ 或 $1$，且增量是 $1$ 时，就意味着当前位被选入 LCS 中。同时注意到 $1 \le |S| \le 15$，自然想到可以**状压**。

好，有点思路了！那我们先把 LCS 放一边，想想怎么计数。

一个想法是设 $f_{i, j}$ 表示考虑 $T$ 的前 $i$ 位，$S$ 的状态是 $j$。但是这样显然是会算重的。联想到上面的状压，可以考虑把第二维替换成 LCS 差分数组的状态。转移就是考虑 $T$ 的当前这一位上应该放什么字母。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool f1;
const int maxn = 16, maxm = 1010, mod = 1e9 + 7;
char s[maxn];
const char tzx[5] = {'A', 'C', 'G', 'T'};
int n, m;
int f[maxm][1 << maxn], num[1 << maxn][5], ans[maxn];
int g[maxn], dp[maxn];
void fix(int &x, const int &y) {
	x += y;
	if(x >= mod) x -= mod;
}
int calc(int x) {
	int sum = 0;
	while(x) {
		if(x % 2 == 1) sum++;
		x /= 2;
	}
	return sum;
}
void solve() {
	scanf("%s", s + 1);
	scanf("%d", &m);
	n = strlen(s + 1);
	for(int i = 0; i < (1 << n); i++) {
		g[0] = 0;
		for(int j = 1; j <= n; j++) {
			g[j] = g[j - 1];
			if(i & (1 << (j - 1))) g[j]++;
		}
		for(int k = 0; k < 4; k++) {
			int tmp = 0;
			dp[0] = 0; 
			for(int j = 1; j <= n; j++) {
				if(s[j] == tzx[k]) dp[j] = g[j - 1] + 1;
				else dp[j] = max(dp[j - 1], g[j]);
				int d = dp[j] - dp[j - 1];
				tmp += (d << (j - 1));
			}
			num[i][k] = tmp;
		}
	}
	for(int i = 1; i <= m; i++) {
		for(int j = 0; j < (1 << n); j++) {
			f[i][j] = 0;
		}
	}
	f[0][0] = 1;
	for(int i = 1; i <= m; i++) {
		for(int j = 0; j < (1 << n); j++) {
			for(int k = 0; k < 4; k++) {
				fix(f[i][num[j][k]], f[i - 1][j]);
			}
		}
	}
	for(int i = 0; i <= n; i++) {
		ans[i] = 0;
	}
	for(int i = 0; i < (1 << n); i++) {
		fix(ans[calc(i)], f[m][i]);
	}
	for(int i = 0; i <= n; i++) {
		printf("%d\n", ans[i]);
	}
}
bool f2;
int main() {
//	printf("%.2lfMB\n", (&f1 - &f2) / 1024.0 / 1024.0);
	int T;
	scanf("%d", &T);
	while(T--) solve();
	return 0;
}
```
## 鸣谢
@[tongzhenxuan](https://www.luogu.com.cn/user/184615)

---

## 作者：littlebug (赞：6)

## Solution

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

需要注意两个优化剪枝，一是可以把 $f_{i,s}$ 为 $0$ 的状态直接剪掉，因为这部分起不到任何作用；二是可以把每个 $s,c$（$s$ 为差分数组，$c$ 为在末尾加的字符）在 LCS 的 dp 后对应的 $s'$ 预处理出来或者记忆化（我采用的是记忆化），避免重复做同样的事。

## Code

```cpp
string base;
int n,m,f[2][1<<16],g[2][17],ans[17],nxt[1<<16][4],to[200];

il void dp(int flag,int s,char c,int v)
{
    if(nxt[s][to[c]]!=-1) return add(f[flag][nxt[s][to[c]]],v);
    
    rep(i,0,n-1) g[0][i+1]=(s>>i&1)+g[0][i];
    rep(i,1,n) g[1][i]=max({g[1][i-1],g[0][i],g[0][i-1]+(c==base[i])});

    int t=0;
    rep(i,0,n-1) t|=g[1][i+1]-g[1][i]<<i;
    add(f[flag][t],v);
    nxt[s][to[c]]=t;
}

il void solve(int __Ti)
{
	to['A']=0,to['C']=1,to['G']=2,to['T']=3;
	
    read(base),read(m),n=base.size(),base="$"+base;

    memset(f,0,sizeof(f)),memset(ans,0,sizeof(ans)),memset(nxt,-1,sizeof(nxt));
    f[0][0]=1;
    
    bool flag=0;
    rep(i,0,m-1)
    {
        rep(s,0,(1<<n)-1) f[!flag][s]=0;
        rep(s,0,(1<<n)-1)
        {
            dp(!flag,s,'A',f[flag][s]);
            dp(!flag,s,'C',f[flag][s]);
            dp(!flag,s,'G',f[flag][s]);
            dp(!flag,s,'T',f[flag][s]);
        }
        flag=!flag;
    }

    rep(s,0,(1<<n)-1) add(ans[popc(s)],f[m&1][s]);
    rep(i,0,n) write(ans[i],'\n');
}
```

---

华风夏韵，洛水天依！

---

## 作者：___PatrickChen___ (赞：4)

提示：三倍经验为 P4590 和 P10614。核心算法为 dp 套 dp。  
另外，这篇题解跟前面投的[那篇](https://www.luogu.com.cn/article/f1xbg734)一模一样。

求 LCS 的值为 $k$ 的方案数，考虑设 $f_{i,j}$ 表示长度为 $i$ 时 LCS 为 $j$ 的方案数。

但是这样好像不能进行 dp，那么我们尝试更改状态设计，$f_{i,s}$ 表示长度为 $i$ 且 LCS 状态为 $s$ 的方案数。

然而我们仍然不知道这个状态 $s$ 如何设计使得它容易进行转移，并且容易进行统计答案。那么我们观察一下 LCS 是怎么 dp 的：

> $g_{i,j} = max\{g_{i-1,j},g_{i,j-1},g_{i-1,j-1}+[A_i=B_j]\}$

注意到 LCS 的 dp 数组有一个性质，就是 $g_{i,j-1}$ 与 $g_{i,j}$ 的差一定为 $1$ 或 $0$。  
我们还发现，如果我们要求 $g_i$ 那么我们就只需要知道 $g_{i-1}$、$A_i$ 和 $B$ 就可以求出了。

综合以上两点，我们可以对 $g$ 进行差分得到一个 01 串，然后对这个 01 串进行状压。  
我们发现，状压之后的这个东西似乎很好转移，非常适合作为上文提及状态 $s$。我们考虑枚举这个状态 $s$ 以及未知字符串下一个字符 $A_i$，然后进行一次 dp，我们就可以得到新状态 $s'$。  
最后在统计答案的时候，我们发现因为 $s$ 是 LCS 的 dp 数组的差分，所以状态为 $s$ 的 dp 数组的 LCS 值为 $popcount(s)$。于是 $ans_{poopcount(i)} =\sum f_{n,s}$ 即可。

综上，我们得到了一个神秘做法。不过如果每一次转移都进行一次 LCS 的 dp 的话，这道题会把这种做法[卡掉](https://www.luogu.com.cn/record/204465035)。

所以我们可以考虑建出一个 DFA，那么只需要在预处理 DFA 的时候进行 LCS 的 dp 即可。

最后给一下代码：

```cpp
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

using ll = long long;

const ll N = 35005, M = 105, P = 1e9 + 7;

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
	cin >> s >> n;
	m = s.size();
	s = " " + s;
	memset(ans, 0, sizeof ans);
	memset(f, 0, sizeof f);
	memset(_next, 0, sizeof _next);
	f[0][0] = 1;
	for (int i = 0; i < 1 << m; ++i) { // 枚举上一个状态
		// 枚举未知字符串的下一个字符 A_i，然后使用LCS dp 得到下一个状态 s' 并存入 DFA
		_next[i]['A' - 65] = calc(i, 'A');
		_next[i]['C' - 65] = calc(i, 'C');
		_next[i]['G' - 65] = calc(i, 'G');
		_next[i]['T' - 65] = calc(i, 'T');
	}
	for (int i = 1, now, last; i <= n; ++i) {
		now = i & 1, last = !now; // 滚动数组避免 MLE
		for (int j = 0; j < 1 << m; ++j) f[now][j] = 0; // 滚动数组初始化
		for (int j = 0; j < 1 << m; ++j) {
			// 枚举下一个字符 A_i，利用 DFA 进行转移
			(f[now][_next[j]['A' - 65]] += f[last][j]) %= P;
			(f[now][_next[j]['C' - 65]] += f[last][j]) %= P;
			(f[now][_next[j]['G' - 65]] += f[last][j]) %= P;
			(f[now][_next[j]['T' - 65]] += f[last][j]) %= P;
		}
	}
	for (int i = 0; i < 1 << m; ++i) (ans[__builtin_popcount(i)] += f[n & 1][i]) %= P; // 统计答案
	for (int i = 0; i <= m; ++i) cout << ans[i] << endl; // 输出
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int _ = 1;
	cin >> _;
	init();
	while (_--) solve();
	return 0;
}
```

---

## 作者：断清秋 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P10614)

设 $n=|s|$。

写在脸上的 dp of dp，显然内层 dp 是一个 LCS。

LCS 就直接设 $dp_{i,j}$ 表示考虑到串 $s$ 的第 $i$ 个字符，串 $t$ 的第 $j$ 个字符，然后 $dp_{i,j}=\max(dp_{i-1,j},dp_{i,j-1},dp_{i-1,j-1}+[s_i=t_j])$。

考虑怎么把内层 dp 状态压入外层 dp 中。

考虑对于本题，串 $s$ 不变但串 $t$ 会变化。因此外层 dp 需要有一维 $j$ 表示现在考虑到串 $t$ 的第 $j$ 位。

然后自然考虑用 $S$ 记录此时 $dp[1 \dots n][j]$ 的值。

显然 $S$ 不可能存储 $n$ 个 int 类型，观察数据范围 $n \leq 15$，自然想到有 $O(2^n)$ 级别的做法，然后可以发现 $dp_{i+1,j}-dp_{i,j} \in \{0,1\}$。

考虑利用归纳法证明这个结论。$j=1$ 是显然的。

然后如果 $dp_{i+1,j}=dp_{i,j}$ 那么自然成立。

如果 $dp_{i+1,j}=dp_{i+1,j-1}$，又根据归纳法有 $dp_{i+1,j-1}-dp_{i,j-1} \in \{0,1\}$，所以 $dp_{i+1,j}-dp_{i,j} \in \{0,1\}$。

如果 $dp_{i+1,j}=dp_{i,j-1}+1$，又 $dp_{i,j}-dp_{i,j-1} \in \{0,1\}$，所以 $dp_{i+1,j}-dp_{i,j}=1-(dp_{i,j}-dp_{i,j-1}) \in \{0,1\}$。

这样就证明了这个结论。

那么如果固定 $j$ 这一维，$dp[1...n][j]$ 的差分数组就是一个 $01$ 序列。于是就可以用一个二进制数 $S$ 压缩这个差分数组。

定义 $f_{i,S}$ 表示考虑到串 $t$ 的第 $i$ 位时，内层 dp 状态为 $S$ 的方案数。

需要 $O(n2^n)$ 预处理一个 $g_{S,ch}$ 表示在差分数组状态为 $S$ 时，再加一个字符 $ch$ 会变成的状态，这样就可以做到 $O(1)$ 转移。

枚举 $i,S$ 直接转移即可，时间复杂度 $O((n+m)2^n)$。

好像还要乘个字符集大小，不过无所谓。

---

## 作者：sqrtqwq (赞：2)

小 S 最近刚学 dp 套 dp，于是她找来了这道道来练手。

小 S 先考虑怎么做内层的 dp，也就是求 LIS。先定义 $g_{i,j}$ 为 $S$ 前 $i$ 个字符和 $T$ 的前 $j$ 个字符的 LIS 的长度。那么就有转移式：

$$g_{i,j} = \begin{cases} g_{i - 1,j - 1} \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \  s_i = t_j\\ \max{g_{i - 1,j},g_{i,j - 1}} \ \ \ \ \text{other}\end{cases}$$

这是平凡的。

然后小 S 考虑设计外层 dp。由于之和上一行的状态有关，也就是只需要记录 $g_{\cdot,j}$ 的所有情况，但是很明显直接纪录会有 $|S|^{|S|}$ 种可能，很明显不能过。

但是小 S 发现，需要维护的数组每一次的变化要么是 $+1$ 要么是不变。发现了这一个性质之后，小 S 考虑做一次差分，直接用状压记录状态即可，此时需要记录的状态为 $\mathrm O(2^{|S|})$ 了。那么这个题就可以做了。小 S 很高兴。

---

## 作者：DYYqwq (赞：1)

这辈子做的第三个 dp of dp。

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
using namespace std;
const int mod = 1e9 + 7;
int n , m , g[1010][1 << 16] , f[20] , nf[20] , ans[20] , pow2[20] , mp[1 << 16][5];
string S , T;
inline void add(int &x , int y) {x = (x + y > mod ? x + y - mod : x + y);}
inline int getnum(char c)
{
	if(c == 'A') return 1;
	if(c == 'C') return 2;
	if(c == 'G') return 3;
	if(c == 'T') return 4;
	assert(false) , __builtin_unreachable();
}
int F(int s , char c)
{
	for(int i = 1 ; i <= n ; i ++) f[i] = f[i - 1] + ((s >> (i - 1)) & 1);
	int ans = 0;
	for(int i = 1 ; i <= n ; i ++) nf[i] = max({f[i - 1] + (c == S[i]) , nf[i - 1] , f[i]}) , ans += (nf[i] - nf[i - 1]) * pow2[i - 1];
	return ans;
}
void solve()
{
	cin >> S; S = '_' + S; scanf("%d" , &m); n = S.size() - 1;
	g[0][0] = 1;
	for(int s = 0 ; s < (1 << n) ; s ++) for(char c : {'A' , 'C' , 'G' , 'T'}) mp[s][getnum(c)] = F(s , c);
    // for(int i = 0 ; i < m ; i ++) for(int s = 0 ; s < (1 << n) ; s ++) if(g[i][s]) for(char c : {'A' , 'C' , 'G' , 'T'}) add(g[i + 1][F(s , c)] , g[i][s]);
	for(int i = 0 ; i < m ; i ++) for(int s = 0 ; s < (1 << n) ; s ++) if(g[i][s]) for(char c : {'A' , 'C' , 'G' , 'T'}) add(g[i + 1][mp[s][getnum(c)]] , g[i][s]);
	for(int s = 0 ; s < (1 << n) ; s ++) add(ans[__builtin_popcount(s)] , g[m][s]);
	for(int i = 0 ; i <= n ; i ++) printf("%d\n" , ans[i]);
	memset(g , 0 , sizeof(g)) , memset(f , 0 , sizeof(f)) , memset(nf , 0 , sizeof(nf)) , memset(ans , 0 , sizeof(ans)) , memset(mp , 0 , sizeof(mp));
}
// g[i][s] --> T 填到第 i 位，状态数为 s 的方案数
// f[i] S:i T:_ -1
// nf[i] S:i T:_
signed main()
{
	pow2[0] = 1;
	for(int i = 1 ; i <= 15 ; i ++) pow2[i] = pow2[i - 1] * 2;
	int t; scanf("%d" , &t);
	while(t --) solve();
	return 0;
}
```

函数 $F(s,c)$ 中的 $s$ 表示上一行（$T$ 填到 $i-1$ 位时）整个 $f_{i-1,j}$ 的状态。其中的 $c$ 表示 $T_i$ 填入的字符。

在这个函数中，首先通过 $s$ 计算了上一行的 $f$ 值（这里使用一维数组）。接着计算当前行的 $nf$ 值。然后将其再次压入二进制并返回。

可以先看注释掉的那行，转移就是将 $g_{i+1,F(s,c)}$ 加上 $g_{i,s}$，原因是显著的。

直接这么写是会 T 掉的。

然后需要在这上面加一些巨大的优化。

- 提前预处理出所有的 $F(s,c)$，因为这只和状态与 $4$ 个字符 `A,C,G,T` 有关。这样在转移的时候就避免了重复计算过多次 $F(s,c)$ 的值。
- 判断 $g_{i,s}$ 是否有值。这个原因显然。其实容易发现有很多 $g_{i,s}$ 都是 $0$ 方案的，找一个小点的样例输出输出就能看出来了。

如此的时间复杂度为 $O(T\times2^nm \times4)$。当然有一些 $<1$ 的常数。

于是可以通过此题。

---

## 作者：__O_v_O__ (赞：0)

我们首先会想到一个 DP：设 $f_{i,j}$ 表示对于长度为 $i$ 的 $T$，和 $S$ 的最长公共子序列为 $j$ 的方案数。但是这样无法转移，我们发现主要的问题是：我们不知道这个最长公共子序列对应的是哪些字符。

考虑朴素求最长公共子序列的过程：设 $g_{i,j}$ 表示考虑 $T$ 的前 $i$ 位和 $S$ 的前 $j$ 位，最长公共子序列的长度。我们发现，对于一个 $i$，只需要记录 $g_i$ 这个一维数组每一位的值，就能准确维护当前 $S$ 与 $T$ 前 $i$ 位最长公共子序列的状态。因为 $S$ 长度只有 $15$，我们发现这个思想是可行的。

于是重新设状态 $f_{i,x}$ 表示对于长度为 $i$ 的 $T$，与 $S$ 的 DP 数组（就是 $g_i$）状态为 $x$ 的方案数。这个 DP 看起来状态数很多，然而我们可以发现 $g_{i,j}-g_{i,j-1}\le 1$，于是维护 $g_i$ 的差分数组，状态数是 $2^{|S|}$ 的。

现在思考怎么转移。容易发现，如果我们知道了 $g_i$ 这个数组，也知道了 $T_{i+1}$，就能通过朴素 LCS 转移求出 $g_{i+1}$。于是朴素的 LCS 就成为了帮助 $f$ 转移的内层 DP。

于是我们枚举 $T_{i+1}$，计算出 $x$ 转移后的状态 $x'$，$f_{i+1,x'}$ 加上 $f_{i,x}$ 即可。最后答案是好求的（$f$ 都把所有 DP 数组的情况转移出来了怎么不好求）。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pc __builtin_popcount
const int mo=1e9+7;
int T,a[101],nx[70001][5],h[101];
int g[101],f[1001][70001],m,n,an[101];
void pl(int &x,int y){x=(x+y)%mo;}
int ca(int no,int x){
	int re=0;
	for(int i=0;i<n;i++)
		g[i+1]=g[i]+(no>>i&1);
	for(int i=1;i<=n;i++){
		if(a[i]==x)h[i]=g[i-1]+1;
		else h[i]=max(h[i-1],g[i]);
	}
	for(int i=1;i<=n;i++)
		re|=((1<<(i-1))*(h[i]-h[i-1]));
	return re;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		string S;cin>>S>>m,n=S.size();
		memset(an,0,sizeof an),f[0][0]=1;
		for(int i=0;i<n;i++){
			if(S[i]=='A')a[i+1]=0;
			if(S[i]=='C')a[i+1]=1;
			if(S[i]=='G')a[i+1]=2;
			if(S[i]=='T')a[i+1]=3;
		}
		for(int i=0;i<(1<<n);i++)
			for(int j=0;j<4;j++)nx[i][j]=ca(i,j);
		for(int i=0;i<m;i++)
			for(int j=0;j<(1<<n);j++)
				for(int k=0;k<4;k++)
					pl(f[i+1][nx[j][k]],f[i][j]);
		for(int i=0;i<(1<<n);i++)
			pl(an[pc(i)],f[m][i]);
		for(int i=0;i<=n;i++)cout<<an[i]<<'\n';
		for(int i=0;i<=m;i++)
			for(int j=0;j<(1<<n);j++)f[i][j]=0;
	}
	return 0;
}
```

---

## 作者：lhc0707 (赞：0)

dp of dp 模板题。内层 dp 是经典 LCS 问题，设 $g_{i,j}$ 表示考虑到 $S$ 的前 $i$ 位和 $T$ 的前 $j$ 位的 LCS，有转移

$$g_{i,j}=\begin{cases}
g_{i-1,j-1}+1 & s_i=t_j \\
\max(g_{i-1,j},g_{i,j-1}) & \text{otherwise}
\end{cases}
$$

对于外层 dp，记 $f_{i,R}$ 表示 dp 到 $T$ 的第 $i$ 位，与串 $S$ 的内层 dp 数组是 $R$ 的方案数，考虑维护 $R$。发现差分最多为 1，于是 $R$ 这一维可以做到 $2^{|S|}$ 的。对于这一层的 dp，记 $nxt_{S,c}$ 表示 $g$ 的状态为 $S$ 时 $T$ 后面加上一个字符 $c$ 后的 $g'$，有 $f_{i+1,nxt_{S,c}}\leftarrow f_{i,S}$。

code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 16, M = 1005, mod = 1e9 + 7;
inline void add(int &x, int y) { x = (x + y) % mod; }
int n, m, f[M][1 << N], g[N], a[N], nxt[1 << N][4], h[N], ans[N];
char s[N];
inline int append(int S, int op)
{
 for (int i = 1; i <= n; i++) g[i] = g[i - 1] + ((S >> (i - 1)) & 1);
 for (int i = 1; i <= n; i++)
 {
  if (a[i] == op) h[i] = g[i - 1] + 1;
  else h[i] = max(h[i - 1], g[i]);
 }
 int ans = 0;
 for (int i = 1; i <= n; i++) ans += (1 << i - 1) * (h[i] - h[i - 1]);
 return ans;
}
inline void solve()
{
 cin >> s >> m, n = strlen(s);
 for (int i = 1; i <= n; i++)
 {
  if (s[i - 1] == 'A') a[i] = 0;
  else if (s[i - 1] == 'C') a[i] = 1;
  else if (s[i - 1] == 'G') a[i] = 2;
  else a[i] = 3;
 }
 for (int i = 0; i < (1 << n); i++)
  for (int j = 0; j < 4; j++) nxt[i][j] = append(i, j);
 f[0][0] = 1;
 for (int i = 0; i < m; i++)
  for (int S = 0; S < (1 << n); S++)
   for (int j = 0; j < 4; j++) add(f[i + 1][nxt[S][j]], f[i][S]);
 for (int i = 0; i <= n; i++) ans[i] = 0;
 for (int S = 0; S < (1 << n); S++) add(ans[__builtin_popcount(S)], f[m][S]);
 for (int i = 0; i <= n; i++) cout << ans[i] << '\n';
 for (int i = 0; i <= m; i++)
  for (int S = 0; S < (1 << n); S++) f[i][S] = 0;
}
int main()
{
 cin.tie(0)->sync_with_stdio(false);
 cout.tie(0);
 int T;
 cin >> T;
 while (T--) solve();
 return 0;
}
```

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

时间复杂度 $O(Tmk\times 2^n)$，此题 $k=4$。

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

## 作者：11400F (赞：0)

[不知道怎么样的阅读体验](https://www.11490dx.net/2025/02/05/R702-practice-log/#p10614-hero-meet-devil-in-lv.13)

---

这道题我们首先考虑如何求两个串的最长 LCS。

显然，可用 DP 求得，设 $dp_{i, j}$ 为考虑串 $T_{1\sim i}$ 和串 $S_{1\sim j}$ 时，两个串的 LCS。容易得出转化式子：
$$
dp_{i,j} = \left\{
\begin{aligned}
&dp_{i-1, j-1} + 1 &(t_i = s_j) \\
& \max(dp_{i-1, j}, dp_{i, j-1}) &(t_i \neq s_j)
\end{aligned}
\right.
$$
但是现在只是知道了当 $T$ 和 $S$ 已知的情况。而现在 $T$ 不知道。

那么我们可以再套一层 DP。设 $f_{i, D}$ 为考虑串 $T_{1 \sim i}$，使现在 $dp$ 数组的 $j$ 维度数组（即现在的 LCS 数组）为 $D$ 的方案数。

根据前面推的那个式子，可以求出之前 LCS 数组状态为 $D$，现在字符串 $T$ 新插入一个字符 $j$ 时 LCS 数组会变成什么新数组。我们令其为 $D^{\prime}$。求 $D^{\prime}$ 的过程就是一个内层 DP。

那么就可以枚举 $j$ 的 $4$ 种情况，求出 $4$ 种情况下的的 $D^{\prime}$，然后使 $f_{i+1,D^{\prime}} \gets f_{i+1, D^{\prime}} + f_{i,D}$。这个过程就是外层 DP。而这道题涉及的算法自然就是 **DP 套 DP** 了。

但是正常情况下的数组 $D$ 的状态会比较难枚举，因为这些数的范围都最多到 $15$。但是再看那个转化式子，$dp_{i, j}$ 和 $dp_{i, j-1}$ 的差最多也就是 $1$。所以我们可以将其转化为差分数组，这样状态数就大大减小到了 $2^{|S|}$，时间复杂度可以接受。

最后的就是求每一个状态 $stat$ 的 `popcount`，这个值其实就是这个状态对应的 LCS 的长度。然后统计答案即可。

Double Exp：[ABC391G Many LCS IN Lv.12](https://www.luogu.com.cn/problem/AT_abc391_g)

---

## 作者：liruixiong0101 (赞：0)

令 $n=|S|$。

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

## 作者：ty_mxzhn (赞：0)

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
int dp[1007][1<<15],ans[17];
int pre[1<<15][4];
const int mod=1e9+7;
void Add(int &x,int y){
	x+=y;
	if(x>=mod) x-=mod;
}
int DP(int s0,char c){
    if(pre[s0][c-'a']!=-1) return pre[s0][c-'a'];
	for(int i=1;i<=n;i++) p[i]=p[i-1]+((s0>>(i-1))&1);
	for(int i=1;i<=n;i++){
		q[i]=max(p[i],q[i-1]);
		q[i]=max(q[i],p[i-1]+(c==s[i]));
	}
	int s1=0;
	for(int i=1;i<=n;i++){
		if(q[i]-q[i-1]>0) s1|=(1<<(i-1));
	}
	pre[s0][c-'a']=s1;
	return s1;
}
 void Subt(){
	scanf("%s%d",s+1,&m);
	n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='A') s[i]='a';
		if(s[i]=='C') s[i]='b';
		if(s[i]=='G') s[i]='c';
		if(s[i]=='T') s[i]='d';
	}
	dp[0][0]=1;
	for(int j=0;j<(1<<n);j++) for(int k=0;k<4;k++) pre[j][k]=-1;
	for(int i=0;i<m;i++){
		for(int j=0;j<(1<<n);j++) dp[i+1][j]=0;
		for(char c='a';c<='d';c++){
			for(int j=0;j<(1<<n);j++){
				Add(dp[i+1][DP(j,c)],dp[i][j]);
			}
		}
	}
	for(int i=0;i<=n;i++) ans[i]=0;
	for(int j=0;j<(1<<n);j++){
		//printf("%d %d\n",j,dp[m][j]);
		int w=0;
		for(int i=1;i<=n;i++) w+=((j>>(i-1))&1);
		Add(ans[w],dp[m][j]);
	}
	for(int i=0;i<=n;i++) printf("%d\n",ans[i]);
	return;
}
signed main(){
	int T=1;
	scanf("%d",&T);
	while(T--) Subt();
}
```

附三倍经验。

1. https://www.luogu.com.cn/problem/P10614

2. https://www.luogu.com.cn/problem/AT_abc391_g

3. https://www.luogu.com.cn/problem/P4590

---

