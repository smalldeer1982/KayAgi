# Wrap Around

## 题目描述

给定一个二进制字符串 $s$。

请你计算长度为 $n$ 的不同循环二进制字符串的数量，这些字符串中包含 $s$ 作为子串。

如果存在某个循环移位后的字符串 $t$，使得 $s$ 是该字符串的一个子串，则称循环字符串 $t$ 包含 $s$ 作为子串。

例如，循环字符串 "000111" 包含子串 "001"、"01110" 和 "10"，但不包含 "0110" 和 "10110"。

如果两个循环字符串本身不同，则认为它们是不同的循环字符串，即使它们仅通过循环移位不同，也视为不同的循环字符串。

## 说明/提示

在第一个样例中，有三个包含 "0" 的循环字符串——"00"、"01" 和 "10"。

在第二个样例中，只有两个这样的字符串——"1010" 和 "0101"。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
0
```

### 输出

```
3```

## 样例 #2

### 输入

```
4
1010
```

### 输出

```
2```

## 样例 #3

### 输入

```
20
10101010101010
```

### 输出

```
962```

# 题解

## 作者：RainFestival (赞：9)

本题于 $2018.9.6$ 出现在比赛中，$\rm Codefoces$ 评分 $\color{red}{2900}$。

如果这篇文章有什么错误，欢迎联系笔者。

本文介绍一种在 $\mathcal O(n^2)$ 时间内解决这个问题的方法。这个方法来自 @[realskc](https://www.luogu.com.cn/user/35672)。非常感谢 Ta。

我们记 $|s|=m,|t|=n$，根据题意，$0\le m\le n$。

我们首先考虑怎么样的串 $t$ 可以满足题目条件。

我们首先考虑 $t$ 的无限循环串 $T=tttttt\cdots$。

我们注意到 $s$ 的长度 $|s|=m\le n=|t|$，因此 $s$ 如果出现在 $T$ 中，**必然是** $t$ 的子串（如 $s=101$，$t=10101$）**或者** 跨过相邻的二个 $t$（如 $s=101,t=1110$）。

设 $f_i=0/1$ 为第 $i$ 个位置是否被匹配。

我们现在要计算有多少个字符串 $t$ 使得 $t$ 的 $f$ 数组至少有一位 $\neq0$。

有关于 **至少** 的问题不容易维护，考虑容斥。

我们记一个字符串 $s$ 是**满足**集合 $S$ 的，当且仅当对于每一个 $i\in S$ 满足 $f_i=1$（注意对于那些 $i\not\in S$ 的 $i$，我们不关心 $f_i=0$ 还是 $1$）。

我们考虑经典的容斥方法。我们考虑对于所有的 $S\in \{1,2,\cdots,n\}，S\neq \emptyset$，我们把 满足集合 $S$ 的字符串数量 记为 $g_S$。记 $p_n=\sum\limits_{|S|=n}g_S$。则我们要求的总方案数 $ans=\sum\limits_{i=1}^{n}(-1)^{i+1}p_i$。

我们发现，我们不用关心具体的 $S$ 是什么，只需要关心 $|S|$ 的大小。

我们考虑按照从左往右填写的顺序，使用动态规划解决这个问题。

我们先对 $t$ 做一个改造。设 $x$ 是最小的满足 $f_x=1$ 的位置。若 $x\neq 1$，则我们将 $t$ 循环左移 $x-1$ 位（比如，字符串 $0110$ 循环左移 $1$ 位变成 $1100$），变成新的字符串 $t'$。显然，对于 $t'$，$f_1=1$。 

现在我们考虑 $t'$ 和 $t$ 的关系。对于 $t'$，记 $y$ 为最大满足 $f_i=1$ 的位置。那么 $t'$ 对应 $n-y+1$ 个 $t$，分别是把 $t'$ 循环右移（定义类似循环左移）$1,2,3\dots n-y+1$ 位形成的 $t$。

我们记录 $dp_{i,x,t}$ 为我们现在考虑到填 $t$ 的第 $i$ 位，上一个 $\in S$ 的位置是 $x$，当前的 $|S|=t$。

因为 $x\in S$，所以 $f_x$ 一定为 $1$。这样 $t_{x\cdots x+m-1}$ 的内容是确定的。

我们分二种情况考虑。

+ 我们要通过填数使得 $f_i=1$。

这种情况下，我们的第 $t_{i\cdots i+m-1}$ 位也会被固定。但是这可能会和之前固定的那些位相矛盾。

当 $i<x+m$ 的时候，$i$ 可能会和从 $x$ 开始的一段被固定的串相矛盾。此时我们要求 $s$ 有 $m-(x-i)$ 长度的 $\rm border$。（可以画一个图验证一下）

当 $i+m-1>n$ 的时候，$i$ 可能会和从 $1$ 开始的一段被固定的串相矛盾。此时我们要求 $s$ 有 $m-(n+1-i)$ 长度的 $\rm border$。（同样的，也可以画一个图验证一下）

在不矛盾的情况下，$t_i$ 有一种填法，那么我们可以做如下转移：

$$dp_{i,i,t}\leftarrow dp_{i,i,t}+dp_{i-1,x,t-1}$$

+ 我们可以任意的填数，对 $f_i$ 没有要求。

这种情况下的填数相对更自由。

如果 $i\ge x+m$，那么 $i$ 这个位置有 $2$ 种填法，做如下转移：

$$dp_{i,x,t}\leftarrow dp_{i,x,t}+2\times dp_{i-1,x,t}$$

如果 $i<x+m$，那么 $i$ 这个位置 $x$ 开始的串被限制了，只能有 $1$ 种填法，做如下转移：

$$dp_{i,x,t}\leftarrow dp_{i,x,t}+dp_{i-1,x,t}$$

我们按照上面的步骤，就可以执行动态规划。这个时间复杂度和空间复杂度都是 $\mathcal{O(n^3)}$ 的。

我们继续考虑优化这个做法。

我们发现 $t$ 的具体值我们不关心，我们只关心 $t$ 的奇偶性（来决定容斥系数是 $1$ 还是 $-1$）。

所以我们把 $t$ 那一维压成 $0/1$，$0$ 表示是偶数，$1$ 表示是奇数。

这样时间复杂度和空间复杂度都是 $\mathcal{O(n^2)}$ 的。

当然我们计算 $dp_{i,*,0/1}$ 的值只和 $dp_{i-1,*,0/1}$ 有关，因此可以使用滚动数组将空间优化到 $\mathcal{O(n)}$。很可惜，笔者没有实现它。

注意我们之前需要 $s$ 所有 $\rm border$ 的长度。这里可以暴力求，因为时间复杂度的瓶颈不在这里，在于动态规划。代码中 $g_i$ 表示 $s$ 是否存在 $g_{m-i}$ 长度的 $\rm border$。

参考代码如下：

```cpp
#include<cstdio>
#include<cstring>
int n,m,g[45];
char st[45];
long long dp[45][45][2],ans=0;
int main()
{
	scanf("%d",&n);
	scanf("%s",st+1);
	m=std::strlen(st+1);
	for (int i=1;i<=m;i++)
	{
		int flag=1,x=1,y=i;
		while (y<=m){if (st[x]!=st[y]) flag=0;++x,++y;}
		g[i-1]=flag;
	}
	dp[1][1][1]=1;
	for (int i=2;i<=n;i++)
		for (int x=1;x<i;x++)
			for (int o=0;o<=1;o++)
			{
				if ((i-x>=m||g[i-x])&&(n+1-i>=m||g[n+1-i])) dp[i][i][1-o]=dp[i][i][1-o]+dp[i-1][x][o];
				dp[i][x][o]=dp[i][x][o]+(1+(x+m<=i))*dp[i-1][x][o];
			}
	for (int x=1;x<=n;x++) ans=ans+(dp[n][x][1]-dp[n][x][0])*(n+1-x);
	printf("%lld\n",ans);
	return 0;
}
```

代码长度 $\tt 658B$，由于数据范围太小，时间和空间消耗无意义。

-----------------------------------------------

下面是笔者本来的做法：

另一种方法就是使用 $\rm AC$ 自动机，在自动机上做 $dp$。

我们考虑算在无限循环串中没有出现 $t$ 的方案。显然 $2^n-$ 这个方案数就是最终答案。

如果 $s$ 出现在 $t$ 的无限循环串中，只有二种可能：

+ $s\in t$（$s$ 是 $t$ 的子串的情况）

+ $t$ 的长度为 $l$ 的前缀是 $s$ 的后缀，并且 $t$ 的长度为 $m-l$ 的后缀是 $l$ 的前缀（$s$ 跨过相邻的二个 $t$ 的情况）

我们考虑把 $s$ 的所有前缀和后缀加入 $\rm AC$ 自动机。

我们记 $dp_{n,a,b}$ 填到第 $n$ 位，当前 $t$ 在 $AC$ 自动机上位于节点 $a$，$t$ 的最长的是 $s$ 的某个后缀的前缀长度为 $b$。

动态规划的过程类似于一般的 $\rm AC$ 自动机上 $dp$，这里不再赘述，可以考虑阅读其他题解获取详细做法，~~但是不知道有没有和我一样做法的题解~~。要注意在 $dp$ 过程中，$a$ 始终不能是 $s$ 整串对应的 $\rm AC$ 自动机节点，因为如果这样，那么就满足了第一种情况。

最后统计答案的时候，我们考虑 $dp_{n,a,b}$ 是否可行。

首先我们考虑 $s$ 长度为 $b$ 的后缀在 $\rm AC$ 自动机上位于点 $p$。

对于 $a$ 在 $\rm Trie$ 树上的所有父亲节点（它一定是 $t$ 的前缀），如果它是一个 $s$ 长度为 $l$ 的后缀，记 $f_l=1$。

对于 $p$ 在 $\rm Fail$ 树上的所有父亲节点（它一定是 $t$ 的后），如果它是一个 $s$ 长度为 $l$ 的前缀，记 $g_l=1$。

如果 $\bigvee\limits_{i=1}^{n-1}f_l\wedge g_{m-l}$ 值为 $1$，那么满足第二种情况，此时不能将这个 $dp$ 加入最后的答案。否则可以。

这样做就可以了。因为 $\rm AC$ 自动机上最多有 $n^2$ 个节点，所以这个动态规划是 $\mathcal{O(n^4)}$ 的。

代码如下：

```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<bitset>
#include<vector>
#include<queue>
char st[45],g[45];
int n,m;
long long dp[45][2005][45],all=0;
struct acam
{
	std::vector<int> a[2005];
	int son[2005][2],fail[2005],dep[2005],g[2005],cnt,v0[2005],v1[2005];
	std::bitset<45> p0[2005],p1[2005];
	void insert(char *st,int n,int flag)
	{
		int now=1;
		for (int i=1;i<=n;i++)
		{
			int x=st[i]-48;
			if (!son[now][x]) dep[son[now][x]=++cnt]=dep[now]+1;
			now=son[now][x];
		}
		if (!flag) p0[now][n]=1,v0[now]=1;
		if (flag) p1[now][n]=1,v1[now]=1,g[n]=now/*,printf("1:%d\n",now)*/;
	}
	void add(int x,int y){a[x].push_back(y);a[y].push_back(x);}
	void bfs()
	{
		int s=1;
		std::queue<int> q;
		q.push(s);
		while (!q.empty())
		{
			int v=q.front();q.pop();
			for (int i=0;i<=1;i++)
			{
				if (!son[v][i]) son[v][i]=(v==1?1:son[fail[v]][i]);
				else fail[son[v][i]]=(v==1?1:son[fail[v]][i]),q.push(son[v][i]),p1[son[v][i]]=p1[son[v][i]]|p1[v];
			}
		}
		for (int i=2;i<=cnt;i++) add(fail[i],i);
	}
	void dfs(int v,int fa)
	{
		for (int i=0;i<(int)a[v].size();i++)
		{
			int u=a[v][i];
			if (u==fa) continue;
			p0[u]=p0[u]|p0[v];
			dfs(u,v);
		}
	}
	int check(int x,int y,int m)
	{
		for (int i=1;i<m;i++) if (p1[x][i]&p0[y][m-i]) return 0;
		return 1;
	}
	void pre(){cnt=1;}
};
acam t;
void insert(int l,int r,int k)
{
	int cnt=0;
	for (int s=l;s<=r;s++) g[++cnt]=st[s];
	t.insert(g,cnt,k);
}
int main()
{
	scanf("%d",&n);
	t.pre();t.g[0]=1;
	scanf("%s",st+1);
	m=std::strlen(st+1);
	for (int i=1;i<=m;i++) for (int j=1;j<=m;j++) if ((i==1||j==m)) insert(i,j,j==m);
	t.bfs();
	t.dfs(1,-1);
	dp[0][1][0]=1;
	for (int i=1;i<=n;i++)
		for (int x=1;x<=t.cnt;x++)
			for (int k=0;k<=n;k++)
				for (int s=0;s<=1;s++)
				{
					if (!dp[i-1][x][k]) continue;
					int nx,nk;
					nx=t.son[x][s];
					if (t.dep[nx]==m) continue;
					nk=k;
					if (t.dep[nx]==i&&t.v1[nx]) nk=i;
					dp[i][nx][nk]=dp[i][nx][nk]+dp[i-1][x][k];
				}
	for (int x=1;x<=t.cnt;x++) for (int k=0;k<=n;k++) if (t.check(t.g[k],x,m)) all=all+dp[n][x][k];
	printf("%lld\n",(1ll<<n)-all);
	return 0;
}
```
代码长度 $\tt 2.14kb$。由于 $\rm AC$ 自动机上的节点数难以达到 $O(n^2)$，所以实际表现效率非常快。

---

## 作者：Mine_King (赞：8)

## Problem

[CF1038F Wrap Around](https://www.luogu.com.cn/problem/CF1038F)

**题目大意：**

给定一个字符串，字符集为 $\{0, 1\}$。求有多少长度为 $n$ 的字符串 $t$，满足以 $t$ 为循环节的无限循环字符串包含 $s$。

## Solution

给出另一种 $O(n|s|)$ 的做法。

> 前置知识：对于文本串 $s$ 和模式串 $t$，若 $|t| \ge \frac{|s|}{2}$，且 $t$ 在 $s$ 中至少成功匹配了 $3$ 次，则每次匹配的位置形成一个等差数列，且公差为 $t$ 的最小周期。

*证明：*

考虑匹配成功的第 $1$ 次、第 $2$ 次和最后一次，分别记为 $t_1, t_2, t_x$。  
设 $t_1, t_2$ 的间隔为 $d$，$t_2, t_x$ 的间隔为 $a$。显然 $d, a$ 都是 $t$ 的周期。

![](https://s2.loli.net/2024/04/20/8fIpvteEPo3bBX9.png)

因为 $|t| \ge \frac{|s|}{2}$，所以 $t_1, t_x$ 的间隔不会超过 $|t|$。  
所以 $d + a \le |t|$，根据弱周期引理，$\gcd(d, a)$ 也是 $t$ 的周期。

设 $t$ 的最小周期为 $p$，显然有 $p \le \gcd(d, a) \le d$，因此 $p + \gcd(d, a) \le d + \gcd(d, a) \le d + a \le |t|$，根据弱周期引理显然还有周期 $\gcd(p, d, a) \le p$。因为 $p$ 最小，故 $p\mid\gcd(p, d, a)$，因此 $p\mid d$。

若 $p\ne d$，则在与 $t_1$ 间隔 $p$ 的位置也会有一个匹配，因此一定有 $p = d$。

显然上面的分析中只要满足 $t_x$ 是第 $\ge 3$ 次匹配即可，因此相邻两次匹配的间隔一定都是 $p$ 的倍数，并且除最后一次外每次匹配间隔 $p$ 的位置一定也会有一个匹配。故所有匹配的间隔相同，即匹配的位置形成等差数列。

$\square$

---

以下是做法：

考虑 $s$ 出现的位置，如果在 $t$ 中出现了，那可以设 $dp_{i, j}$ 表示考虑前 $i$ 个字符，$s$ 匹配到 $j$ 的方案数，然后用 KMP 自动机转移一下，在 $j = |s|$ 时统计答案即可。

然后考虑所有 $s$ 都经过头尾的方案，假设已经知道所有 $s$ 覆盖的长度，剩余部分的方案数即为这样一个问题：求有多少长度为 $len$ 的字符串 $t$，满足 $s + t + s$ 只在头尾能匹配到 $s$。

做法和上面的 DP 类似，将初值设为 $dp_{0, \pi_{|s|}} = 1$，然后对于每个 $i$，设答案为 $sum_i$，则有：

$$
sum_i = \sum\limits_{j \notin \mathcal{P}} dp_{i, j}
$$

然后考虑 $s$ 的方法，分类讨论：

- 如果只放了 $1$ 个，则起点可以选在 $s_2$ 到 $s_{|s|}$，答案为 $(|s| - 1) sum_{n - |s|}$。
- 如果放了 $\ge 3$ 个，根据上面的定理，相邻两个的位置差为最小周期，设为 $p$，则放了 $i$ 个的答案为 $(|s| - (i - 1)p - 1) sum_{n - (|s| - (i - 1)p)}$。注意需要满足所有的 $s$ 有交，即 $(i - 1)p < |s|$。
- 如果放了 $2$ 个，则枚举 Border 作为交，每次需要 check 中间能不能再匹配别的 $s$，设交的长度为 $i$，则答案为 $(i - 1) sum_{n - (2|s| - i)}$。

注意需要保证 $s$ 覆盖的长度 $\le n$。

但是这样仍是有问题的，考虑 $n = 5, s = \verb|101|$，发现当放了 $2$ 个时第一个串和第二个串头尾重叠了，这是我们没有统计到的。因此对于放了 $\ge 2$ 个的情况，需要判断一下第一次 $\ge n$ 时能否叠在一起，如果可以则也要计入答案。

## Code

码是模拟赛时写的，比较丑陋。

```cpp
// Think twice, code once.
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#define eputchar(c) putc(c, stderr)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define eputs(str) fputs(str, stderr), putc('\n', stderr)
using namespace std;

int n, m, nxt[4005], delta[4005][2];
string s;
long long ans, dp[4005][4005], pw[4005], sum[4005], f[4005][2];

int main() {
	// freopen("d.in", "r", stdin);
	// freopen("d.out", "w", stdout);
	scanf("%d", &n);
	cin >> s;
	m = s.length();
	s = " " + s;
	for (int i = 2, j = 0; i <= m; i++) {
		while (j && s[j + 1] != s[i]) j = nxt[j];
		if (s[j + 1] == s[i]) nxt[i] = ++j;
	}
	if (m == n) {
		printf("%d\n", m % (m - nxt[m]) == 0 ? m - nxt[m] : m);
		return 0;
	}
	pw[0] = 1;
	for (int i = 1; i <= n; i++) pw[i] = pw[i - 1] * 2;
	for (int i = 0; i < m; i++) {
		delta[i][s[i + 1] - '0'] = i + 1;
		delta[i][(s[i + 1] - '0') ^ 1] = delta[nxt[i]][(s[i + 1] - '0') ^ 1];
	}
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++)
			for (int k = 0; k < 2; k++)
				dp[i][delta[j][k]] = (dp[i][delta[j][k]] + dp[i - 1][j]);
		ans = (ans + (long long)dp[i][m] * pw[n - i]);
	}
	memset(dp, 0, sizeof(dp));
	dp[0][nxt[m]] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < m; j++)
			for (int k = 0; k < 2; k++)
				dp[i][delta[j][k]] = (dp[i][delta[j][k]] + dp[i - 1][j]);
	for (int i = 0; i <= n; i++) {
		for (int j = 0 ; j < m; j++) sum[i] = (sum[i] + dp[i][j]);
		for (int j = nxt[m]; j; j = nxt[j]) sum[i] = (sum[i] - dp[i][m - j]);
	}
	int period = m - nxt[m];
	if (m + period < n) {
		for (int i = 3; 1 + (i - 1) * period <= m; i++) {
			if (m + (i - 1) * period <= n) {
				ans = (ans + (long long)(m - (i - 1) * period - 1) * sum[n - m - (i - 1) * period]);
				if (m + (i - 1) * period == n) break;
				continue;
			}
			string t = s;
			for (int j = 1; j <= i; j++)
				for (int k = 1; k <= period; k++) t.push_back(s[k]);
			int flag = 1;
			for (int j = n + 1; j <= m + (i - 1) * period; j++) flag &= t[j] == t[j - n];
			ans += flag * (m - (i - 1) * period - 1);
			break;
		}
	}
	for (int i = nxt[m]; i; i = nxt[i]) {
		string t = s;
		for (int j = 1; j <= m - i; j++) t.push_back(s[j]);
		int flag = 0;
		for (int j = 1, k = 0; j <= m + m - i; j++) {
			while (k && s[k + 1] != t[j]) k = nxt[k];
			if (s[k + 1] == t[j])
				if (++k == m) {
					flag |= j != m && j != m + m - i;
					k = nxt[k];
				}
		}
		if (flag) continue;
		if (m + m - i <= n) {
			ans = (ans + (long long)(i - 1) * sum[n - m - m + i]);
			if (m + m - i == n) break;
			continue;
		}
		flag = 1;
		for (int j = n + 1; j <= m + m - i; j++) flag &= t[j] == t[j - n];
		ans += flag * (i - 1);
		break;
	}
	ans = (ans + (long long)(m - 1) * sum[n - m]);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：C20203030 (赞：3)

## 一、题目
[点此看题](https://www.luogu.com.cn/problem/CF1038F)
## 二、解法
题目中的循环节有点吓人，我们可以把它变成文本串倍长之后是否包含模式串。

正难则反，我们求出不包含的所有方案数，用所有方案减去即可。

先建出$\text{AC}$自动机，我们枚举文本串的后缀能够匹配到点$i$，设$f[len][j][k]$为当前处理到的长度为$len$，前缀匹配到的点为$j$，后缀加上前缀能够匹配到的点为$j$（这一部分体现了倍长），初始化时我们只把$f[0][0][i]$设置成$1$，最后用$2^n$减去$f[n][i][j]$（第二维必须在$i$结束，才符合我们开始的设置）

具体实现的话需要保证任何时候不经过点$cnt$（只有一个串，也只有一个结束点），时间复杂度$O(n^4)$，这道题的$dp$特别巧妙，口胡可能难以理解，贴个代码。

```cpp
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define int long long
const int M = 45;
int read()
{
    int x=0,flag=1;
    char c;
    while((c=getchar())<'0' || c>'9') if(c=='-') flag=-1;
    while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*flag;
}
int T,n;
char s[M];
struct Automaton
{
    int c[M][2],fail[M],cnt,f[M][M][M];
    void ins(char *s)
    {
        int len=strlen(s),now=0;
        for(int i=0; i<len; i++)
        {
            int v=s[i]-'0';
            if(!c[now][v]) c[now][v]=++cnt;
            now=c[now][v];
        }
    }
    void build()
    {
        queue<int> q;
        for(int i=0; i<2; i++) if(c[0][i]) q.push(c[0][i]);
        while(!q.empty())
        {
            int t=q.front();
            q.pop();
            for(int i=0; i<2; i++)
                if(c[t][i]) fail[c[t][i]]=c[fail[t]][i],q.push(c[t][i]);
                else c[t][i]=c[fail[t]][i];
        }
    }
    void dp()
    {
        int ans=1ll<<n;
        for(int i=0; i<cnt; i++)
        {
            memset(f,0,sizeof f);
            f[0][0][i]=1;
            for(int j=0; j<n; j++)
                for(int l=0; l<cnt; l++)
                    for(int k=0; k<cnt; k++)
                        for(int v=0; v<2; v++)
                        {
                            int a=c[l][v],b=c[k][v];
                            if(a==cnt || b==cnt) continue ;
                            f[j+1][a][b]+=f[j][l][k];
                        }
            for(int j=0; j<cnt; j++)
                ans-=f[n][i][j];
        }
        printf("%lld\n",ans);
    }
} AC;
signed main()
{
    n=read();
    scanf("%s",s);
    AC.ins(s);
    AC.build();
    AC.dp();
}


```



---

## 作者：strapplE (赞：1)

另一个有意思的做法。正难则反。考虑 kmp 自动机（里面的点是 $0\sim |S|-1$，因为要求不碰到 $|S|$）。

不难（很难）发现：一个无限循环不包含目标子串 $S$ 的字符串 $T$ 与 $S$ 的 kmp 自动机上的一个固定起始（终止）点的长度为 $n$ 的环一一对应。

考虑怎么理解这样一个结论。如果不是无限循环，只是单个字符串，那么相当于在 kmp 自动机上的一条长度为 $n$ 的路径。

如果有无限循环，那么可以发现，对于足够大的 $M$，有 $T^M$ 和 $T^{M+1}$ 等价。也就是说，走到这两个字符串的末尾时，得到的自动机上的点是相同的，我们说它就对应从 $T^M$ 走到 $T^{M+1}$ 的路径。

反面，如果存在这条路径 $R$，走充分大次也会走到一个相同的东西，此时 $R^M$ 和 $R^{M+1}$ 也等价，与起点无关，所以从 $r$ 走到 $r$ 等价于从 $0$ 走到 $r$，因此这个字符串对应的一定是这条路径。

有了这个结论，直接 $dp$，设 $f_{i,j,k}$ 表示走了 $i$ 步，从 $j$ 走到 $k$ 即可。答案是 $\sum\limits_{i} f_{n,i,i}$。

时间复杂度是 $O(n|S|^2\Sigma)$，其中本题里 $\Sigma=2$。

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[45];
int nxt[45],zy[45][2];
long long f[45][45][45];
int main(){
	int n;
	scanf("%d",&n);
	scanf("%s",s+1);
	int m=strlen(s+1);
	for(int i=2;i<=m;++i){
		int r=nxt[i-1];
		while(r&&s[r+1]!=s[i])r=nxt[r];
		if(s[r+1]==s[i])nxt[i]=r+1;
		else nxt[i]=0;
	}
	for(int i=0;i<m;++i)f[0][i][i]=1;
	for(int i=0;i<m;++i)for(int j=0;j<2;++j){
		int r=i;
		while(r&&s[r+1]-'0'!=j)r=nxt[r];
		if(s[r+1]-'0'==j)zy[i][j]=r+1;
		else zy[i][j]=0;
	}
	for(int i=0;i<n;++i)for(int j=0;j<m;++j)for(int k=0;k<m;++k){
		for(int s=0;s<2;++s)if(zy[k][s]<m){
			f[i+1][j][zy[k][s]]+=f[i][j][k];
		}
	}
	long long ans=0;
	for(int i=0;i<m;++i)ans+=f[n][i][i];
	printf("%lld\n",(1ll<<n)-ans);
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：0)

来点不用脑子也好写的做法，复杂度四次。

# Solution

首先重复无数次等于重复两次。考虑建出 $s$ 的 KMP 自动机，然后从左往右填 $t$。

但是 $t$ 会重复两次，不好做。考虑枚举走完第一个 $t$ 后到的点 $x$，然后设 $f_{i,p,q}$ 表示当前的 $t$ 前后两个对应的路径分别是 $1\to p$，$x\to q$ 的方案数。初值是 $f_{0,0,x}=1$，答案就是 $f_{n,x,\lvert s\rvert}$。

复杂度 $\mathcal{O}(n\lvert s\rvert^3)$。

# Code

```cpp
typedef long long LL;
typedef pair<LL, LL> pii;
const int N = 45;
LL n, m, rs, f[N][N][N], nxt[N][2]; string s;
void KMP(auto s, int n) {
  vector<int> fail(n + 1);
  for (int i = 2, j = 0; i <= n; i ++) {
    while (j > 0 && s[i] != s[j + 1]) j = fail[j];
    if (s[i] == s[j + 1]) j ++;
    fail[i] = j;
  }
  REP(i, 0, n) REP(p, 0, 1) {
    if (i == n) { nxt[i][p] = n; continue; }
    int j = i;
    while (j > 0 && s[j + 1] != p + '0') j = fail[j];
    nxt[i][p] = j + (s[j + 1] == p + '0');
  }
} // 建 KMP 自动机
int main() {
  cin >> m >> s, n = SZ(s), s = "#" + s;
  KMP(s, n);
  REP(t, 0, n) {
    REP(i, 0, m) REP(x, 0, n) REP(y, 0, n) f[i][x][y] = 0;
    f[0][0][t] = 1;
    REP(i, 0, m - 1) REP(x, 0, n) REP(y, 0, n) {
      f[i + 1][nxt[x][0]][nxt[y][0]] += f[i][x][y];
      f[i + 1][nxt[x][1]][nxt[y][1]] += f[i][x][y];
    } 
    rs += f[m][t][n];
  }
  cout << rs << '\n';
  return 0;
}
```

---

## 作者：vme50xiex2 (赞：0)

怎么没有用 ACAM 正着做的。

考虑 $t$ 中出现 $s$ 无非两种情况：
- $s$ 完整地在 $t$ 的中间出现。
- $t$ 的开头为 $s$ 的一段后缀，结尾为 $s$ 的一段前缀，满足后缀一直跳 fail 和 前缀一直跳 fail 中途能拼一个 $s$。

那么状态设计中至少要包反映出三个量：目前 $t$ 的最长前缀使得其是 $s$ 的后缀，目前 $t$ 的最长后缀使得其是 $s$ 的前缀，中途有无出现过 $s$。

考虑如何刻画这三个量：维护 KMP 的匹配指针即可求出后两个量，把所有前缀建 Trie，维护 Trie 上的指针即可求出第一个量。但其实你发现把 $s$ 的所有前缀和后缀建 ACAM 就可以同时维护这三个量。设 $f(i,now,max,0/1)$ 表示填了前 $i$ 个点，当前在 ACAM 上走到 $now$ 了，最长后缀是 $max$，途中有无出现整个 $s$ 的方案数。直接转移即可。时间复杂度 $\mathcal{O(n^4)}$。

注意更新最长前缀要保证 $now$ 的深度等于 $i$，否则会出现在 ACAM 上往回跳后更新 $max$ 的情况。

$\mathcal{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 45;
const int M = N * N / 2 + N;
struct ACAM {
	int son[2], fail, len;
	ll pre, suf;
} t[M];
int n, m, cnt, id[N];
char s[N];
ll f[N][M][N][2];
vector<int> G[M];
void Dfs(int u) {
	for(int v : G[u]) {
		t[v].pre |= t[u].pre;
		Dfs(v);
	}
}
void Build() {
	queue<int> q;
	for(int i = 0; i < 2; ++i) if(t[0].son[i])
		q.push(t[0].son[i]);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int i = 0; i < 2; ++i)
			if(int v = t[u].son[i]) {
				t[v].fail = t[t[u].fail].son[i], q.push(v);
				t[v].suf |= t[u].suf;
			}
			else t[u].son[i] = t[t[u].fail].son[i];
	}
	for(int i = 1; i <= cnt; ++i) G[t[i].fail].push_back(i);
	Dfs(0);
}
int main() {
	//freopen("data.in", "r", stdin);
	//freopen("code.out", "w", stdout);
	scanf("%d%s", &n, &s[1]);
	m = strlen(s + 1);
	for(int i = 1, now = 0; i <= m; ++i) {
		int k = s[i] - '0';
		if(!t[now].son[k]) t[now].son[k] = ++cnt;
		now = t[now].son[k], t[now].pre |= 1ll << i;
	}
	for(int i = 1; i <= m; ++i) {
		int now = 0;
		for(int j = i; j <= m; ++j) {
			int k = s[j] - '0';
			if(!t[now].son[k]) t[now].son[k] = ++cnt;
			now = t[now].son[k];
		}
		t[now].suf |= 1ll << i, t[now].len = m - i + 1, id[m - i + 1] = now;
	}
	Build();
	f[0][0][0][0] = 1;
	for(int i = 1; i <= n; ++i)
		for(int u = 0; u <= cnt; ++u)
			for(int j = 0; j <= m; ++j)
				for(int k = 0; k < 2; ++k) if(f[i - 1][u][j][k]) {
				for(int c = 0; c < 2; ++c) {
					int v = t[u].son[c], nk = k;
					if(t[v].pre >> m & 1) nk = 1;
					int nj = j;
					if(t[v].len == i) nj = max(nj, i);
					f[i][v][nj][nk] += f[i - 1][u][j][k];
				}
			}
	ll ans = 0;
	for(int u = 0; u <= cnt; ++u)
		for(int j = 0; j <= m; ++j)
			for(int k = 0; k < 2; ++k) {
				bool isOK = 0;
				for(int i = 1; i <= m; ++i)
					isOK |= (t[u].pre >> i & 1) && (t[id[j]].suf >> (i + 1) & 1);
				if(isOK || k) ans += f[n][u][j][k];
			}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Vidoliga (赞：0)

好题。

设 $n,m$ 分别为 $t,s$ 的长度。

直接考虑计数区间或后缀拼前缀方案数显然错。

错在哪？算重，容斥。

首先必须至少包含一个 $s$，考虑应定 $[n-m+2,n]\cup\{1\}$ 与 $s$ 串匹配。

问题在于对于原问题，我们需要算的是每个位置作为序列从左往右的第一个匹配 $s$ 串末尾的答案。

考虑算出 $1$ 为第一个匹配 $s$ 串末尾，$p$ 为最后一个匹配 $s$ 串末尾的答案。

注意此时将整个匹配序列向右平移后，答案不变，直到最后一个位置平移超出 $n$（相当于回到 $1$） 前，都会对答案产生贡献。

所以应定 $1$ 为开头后，对答案的贡献应当乘上 $(n-p)$。

怎么算 $1$ 为第一个匹配 $s$ 串末尾，$p$ 为最后一个匹配 $s$ 串末尾的答案。

$f_{i}$ 表示填了 $[1,i]$，$i$ 匹配 $s$ 串末尾方案数。

最后乘上去除应定 $1$ 对序列结尾的一些位置，剩下位置随便填的贡献。

复杂度 $O(n^2)$。

```cpp
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("Ofast","unroll-loops","inline")
#include<bits/stdc++.h>
#define ll long long
#define int ll
using namespace std;
const int N=100+20,M=1e6+20,mod=998244353;
int n,m,pw[N],f[N];char s[N];bool fl[N];
inline bool chk(int k){
	for(int i=1;i<=k;i++) if(s[i]!=s[m-k+i]) return 0;
	return 1;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>(s+1);m=strlen(s+1);
	for(int i=1;i<=m;i++) fl[i]=chk(m-i);
	pw[0]=1;for(int i=1;i<=n;i++) pw[i]=pw[i-1]*2;
	f[1]=1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++) if(i-j>m||fl[i-j]){
			if(i>=n-m+1+1&&!fl[m-(i-n+m-1)]) continue;
			int d=i-j-m;
			f[i]=f[i]-(d>0?pw[d]:1)*f[j];
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		int d=n-i-m+1;
		int res=(d>0?pw[d]:1)*f[i];
		ans=(ans+res*(n-i+1));
	}
	cout<<ans<<'\n';
	return 0;
}
```


---

