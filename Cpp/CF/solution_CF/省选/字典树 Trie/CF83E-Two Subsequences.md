# Two Subsequences

## 题目描述

# CF83E 两个子序列
在一堂IT课上，Valera 学习了数据压缩。我们现在将向你介绍老师所讲解的一种新的数据压缩方法。

定义压缩函数 $f()$：

- $f($空序列$)=$ 空字符串
- 对于任意一个字符串 $s$，$f(s)=s$。
- 对于任意两个字符串 $s_{1}$，$s_{2}$，$f(s1,s2)$ 为包含前缀 $s_{1}$ 且包含后缀 $s_{2}$ 的字符串中长度最小的一个。
- 对于任意 $n$ 个字符串，$f({s_{1},s_{2},\ldots,s_{n}})=f(f({s_{1},s_{2},\ldots,s_{n-1}}),s_{n})$

例如：
1. $ f(001,011)=0011 $ 
2. $ f(111,011)=111011 $ 
2. $f(000,000,111)=f(f(000,000),111)=f(000,111)=000111 $ .

现在 Valera 面临一个难题：他需要将给定的需要压缩的序列 ${a_{1},a_{2},\ldots,a_{n}}$ 分成两个新的序列 ${b_{1},b_{2},\ldots,b_{k}}$ 和 ${c_{1},c_{2},\ldots,c_{m}}$ $(k+m=n)$ ，使得$S=|f({b_{1},b_{2},\ldots,b_{k}})|+|f({c_{1},c_{2},\ldots,c_{m}})|$ 的值最小。这里 $|p|$ 表示字符串 $p$ 的长度。

**注意**：
1. 不允许在子序列中更改元素的相对顺序。
2. 可以使得 $mk=0$ 即可以使得序列 $b$ $c$ 中的一个为空。
3. 对于原序列 $a$ 中的任意一项 $a_{i}$，不得既不存在于 $b$ 中，亦不存在于 $c$ 中。也不得同时存在于 $b$ 和 $c$ 中。
4.  $b$  $c$ 中的元素在 $a$ 中不必连续，即 $b$ 和 $c$ 的元素可以在 $a$ 中交替出现(参见样例2、3)。

## 样例 #1

### 输入

```
3
01
10
01
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
000
111
110
001
```

### 输出

```
8
```

## 样例 #3

### 输入

```
5
10101
01010
11111
01000
10010
```

### 输出

```
17
```

# 题解

## 作者：Daniel_yuan (赞：6)

#### 题意简述：

定义一个函数 $f$：

1. $f(\varnothing)=\text{empty string}$

2. 对于任意一个字符串 $s$，$f(s)=s$ 。

3. 对于任意两个字符串 $s_1,s_2$，$f(s_1,s_2)$ 为最短的，且长度为 $|s_1|$ 的前缀为 $s_1$，长度为 $|s_2|$ 的后缀为 $s_2$ 的字符串。例如 $f(001,011)=0011$， $f(111,011)=111011$

4. 对于任意多个字符串 $s_1,s_2...s_n$，$f(s_1,s_2...s_n)=f(f(s_1,s_2...s_{n-1}),s_n)$。

现在按照顺序给出 $n$ 个长度相等的 $01$ 串 $a_1,a_2...a_n$，你要把他们分成两个序列 $B,C$，且要保证每个 $a_i$ 出现且仅出现在一个序列中。求 $|f(B)|+|f(C)|$ 最小值。**特殊的，你需要保证在同一个序列内的字符串的相对位置不能改变，某个序列可以为空**。（如对于初始 $01$ 串 $a_1,a_2,a_3$，你可以把他们分成 $a_1,a_3$ 与 $a_2$，但是不能分成 $a_3,a_1$ 与 $a_2$）。$n\leq 2\times 10^5$，$01$ 串长度不超过 $20$。

#### 题解：

首先考虑怎么求 $f(s_1,s_2)$，可以枚举 $s_2$ 的每个前缀，然后看这个前缀是不是 $s_1$ 的某个后缀，如果是，那么这个前缀和后缀就可以缩到一起。如 $011$ 和 $110$，$110$ 的前缀 $11$ 是 $011$ 的一个后缀，所以 $f(011,110)$ 就是把这两个部分缩在一起即 $0110$。复杂度是 $\text{len}^2$ 的。

对于求最小值考虑 DP。

有一个比较显然的 DP，设 $f[i][j][k]$ 表示考虑到第 $i$ 个字符串，第一个序列的结尾是字符串 $a_j$，第二个序列的结尾是字符串 $a_k$ 的最小值。因为 $a_{i-1}$ 必定放进了序列中且一定在某个序列的最后一个，所以状态可以优化成 $f[i][j]$ 表示考虑到第 $i$ 个字符串，一个序列的结尾是 $a_{i-1}$，另一个序列的结尾是 $a_j$ 的最小值。

这样复杂度是 $O(n^2\times \text{len}^2)$ 的，不能通过本题。而且如果 DP 状态中带一个序列中的位置的话，似乎不能继续优化下去。

故考虑另一种 DP 状态。设 $f[i][S]$ 表示考虑到第 $i$ 个字符串，一个序列的结尾是字符串 $a_{i-1}$，另一个序列的结尾是字符串 $S$。单看状态数似乎复杂度变高了，但是这样设状态的好处是，把 $01$ 串放到了状态中，那么对于这个 $S$，就可以用 ```01-Trie``` 去维护。

每次转移的时候，如果把当前字符串 $a_i$ 接到 $a_{i-1}$ 上，那么 $S$ 的状态不会改变，相当于整棵树加上了 $|f(a_{i-1},a_i)|$，所以可以在外面记上一个标记，表示树里面的值需要加上标记才是真实答案。如果把当前字符串 $a_i$ 接到另一个字符串上，那么就枚举 $a_i$ 的一个前缀 $T$，并且在 ```01-Tire``` 上查询所有后缀为 $T$ 的字符串的 DP 值的最小值，然后把得到的这个最小值更新 $f[i][a_{i-1}]$。

这样子复杂度是 $O(n\times \text{len}^2)$ 的，足以通过本题。

代码如下

```cpp
#include <bits/stdc++.h>
#define RI register int
typedef long long LL;

#define FILEIO(name) freopen(name".in", "r", stdin), freopen(name".out", "w", stdout);

using namespace std;

char s[200005][22];
int Mn[1 << 22];
int len;

inline void Reverse(char *s, int l) {
  for (RI i = 1, j = l; i < j; ++i, --j)
    swap(s[i], s[j]);
}

int GetMin(char *s, int l) {
  int now = 1;
  for (RI i = 1; i <= l; ++i)
    if (s[i] == '0') now <<= 1;
    else now <<= 1, now |= 1;
  return Mn[now];
}
int Query(char *s) {
  int re = 0x3f3f3f3f;
  for (RI i = 0; i <= len; ++i) {
    Reverse(s, i);
    re = min(re, GetMin(s, i) + len - i);
    Reverse(s, i);
  }
  return re;
}
int Solve(char *s, char *t) {
  int re = 0;
  for (RI i = len; i; --i) {
    int flag = 1;
    for (RI j = len; flag && j > len - i; --j)
      if (s[j] != t[i - (len - j)])
        flag = 0;
    if (flag) { re = i; break; }
  }
  return len - re;
}
void Insert(char *s, int val) {
  int now = 1;
  for (RI i = 1; i <= len; ++i) {
    Mn[now] = min(Mn[now], val);
    if (s[i] == '0') now <<= 1;
    else now <<= 1, now |= 1;
  }
  Mn[now] = min(Mn[now], val);
}

int main() {
  
#ifdef LOCAL
  FILEIO("a");
#endif

  int n; cin >> n;
  for (RI i = 1; i <= n; ++i)
    cin >> (s[i] + 1);
  len = strlen(s[1] + 1);
  int tag = len;
  memset(Mn, 0x3f, sizeof(Mn));
  Mn[1] = 0;
  for (RI i = 2; i <= n; ++i) {
    int re = Query(s[i]);
    re += tag;
    tag += Solve(s[i - 1], s[i]);
    Reverse(s[i - 1], len);
    Insert(s[i - 1], re - tag);
  }
  int ans = Mn[1];
  printf("%d\n", ans + tag);

  return 0;
}

// created by Daniel yuan
/*
     ________
    /        \
   / /      \ \
  / /        \ \
  \            /
   \  ______  /
    \________/
*/

```

---

## 作者：xs_siqi (赞：1)

考场上只写出来 $O(2^mn)$ 的做法。

然后由于考后的题解太过于抽象，所以这个题解可以说是我们考后题解的扩充吧。

先介绍一下 $n^2$ 的做法：

$f_{i,j}$ 表示前 $i$ 个，第一个字符串以第 $i$ 个字符串结尾，另外一个字符串以 $j$ 结尾的最小值（$j$ 的状态在 $2^m$ 次中枚举）。

然后我们现在把串分成两个。我们分别叫它们第一个串和第二个串。

枚举到当前这个 $i$ 号串，你可以把它加到第一个串或第二个。这两个串中必然有一个串是以 $i-1$ 结尾的。如果我们把这个串加入以 $i-1$ 结尾的串中，那么就会有转移式 $f_{i+1,j}=f_{i,j}+\operatorname{cost}(a_i,a_{i+1})$。

其中， $\operatorname{cost}$ 函数表示的是两个数，第一个数的后缀**不等于**第二个数的前缀的最长长度（也就是一个数的后缀等于另一个数的前缀的最长段，再用一个串的长度减掉它）。

然后加入另一个串中我们是无法确定它的结尾是谁，所以我们肯定刚从 $2^m$ 枚举。然后类似地，会得到一个转移式 $f_{i+1,a_i}=f_{i,j}+\operatorname{cost}(j,a_{i+1})$。

然后我们枚举 $i,j$ 就得到了一个 $O(2^mn)$ 的做法。

如何优化上面的过程？对于第一个式子，我们发现 $i$ 是固定的，那么我们大可不必枚举那么多东西，只需要在最后加上 $\sum_{i=2}^{n} \operatorname{cost}(a_i,a_{i-1})$ 即可。这样我们甚至把这个第一条式子优化到了 $O(nm)$（枚举哪个串是一个 $n$，对每一个 $i$ 做一个 $\operatorname{cost}$ 函数是一个 $m$）。

然后我们看后面的式子，对于 $\operatorname{cost}$ 函数我们其实是很难去优化的，$n$ 个串我们又是一定要去枚举的，所以我们考虑能不能对 $j$ 的枚举节省时间。

我们发现我们大可不必枚举完这么 $2^m$ 次。因为对于一个串，它要是想去合并，必然只能合并到给出串的后缀里去。也就是说，我们只要枚举前 $i-2$ 个串的后缀即可。那么我们就要改改式子的定义了。

记 $dp_{t,i,j}$ 表示枚举到第几个串，前 $i$ 位固定，固定的串为 $j$。$t$ 可以压维。那么我们只剩下 $dp_{i,j}$ 了。

为什么只要前 $i$ 位固定呢？因为我只合并前 $i$ 位。有人会说可能存在一种情况，那就是剩余的 $m-i$ 位也存在后缀等于前缀的情况，也就是合并不完的情况。贪心一下合并完必然最优（因为合不合并完都不影响后续合并，说明这是可贪心的）。但是考虑一件事情：没合并完一定不是最优情况。换句话说，最终一定会枚举到合并完的状态，那直接会把这个覆盖掉。

然后我们算出它与 $a_{t+1}$ 的公共部分，取一个最小值，然后去更新对于合并后的新 $dp$ 序列即可。这样的复杂度就是 $O(nm)$ 的了。为什么呢？

决定状态的是哪几位是固定的（合并只跟这个有关），因为你现在已知你要合并几位，然后现在这个串你也是已知的，也就是说，我们从枚举这个串，转向了根据 $a_t$ 这个串的前缀去枚举对应的后缀。求前缀找对应的后缀我们都是可以 $O(1)$ 搞定的。我们把它从 $2^m$ 优化到了 $m$。这一步真的很妙。

参考实现如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxm=25;
const int maxn=1e6+5;
int n,m,a[maxn],f[maxm][1048577],delta,ans=1e9;
char s[maxm];
void mn(int &x,int y){if(y<x)x=y;}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		m=strlen(s+1);
		for(int j=1;j<=m;j++)
			a[i]+=(s[j]=='1')*(1<<(m-j));}
	memset(f,63,sizeof f),f[0][0]=m;
	for(int i=2;i<=n;i++){
		int k=0,cnt=1e9;
		while(k<m&&(a[i]>>k)!=(a[i-1]&((1<<(m-k))-1)))k++,delta++;
		for(int j=0;j<=m;j++)mn(cnt,f[m-j][a[i]>>j]+j-k);
		for(int j=0;j<=m;j++)mn(f[m-j][a[i-1]&((1<<(m-j))-1)],cnt);}
	for(int i=0;i<=m;i++)
		for(int j=0;j<(1<<i);j++)
			mn(ans,f[i][j]);
	printf("%d\n",ans+delta);
	return 0;}
```




---

## 作者：Para (赞：1)

所有字符串长度相同是一个重要的性质。

考虑一个暴力 $\text{dp}$。设 $f_{i,S_1,S_2}$ 表示考虑到第 $i$ 个串，拆分出来的两个集合分别为 $S_1,S_2$，此时长度和的最小值。因为字符串长度相同，所以当我们新接入一个串 $S'$ 时，新的状态中的 $S_1$ 或 $S_2$ 会被替换为 $S'$。

这样我们可以观察到 $S_1,S_2$ 中必定有一维是上一次加入的字符串，这样就可以压缩一维状态。设 $f_{i,S}$ 表示考虑到第 $i$ 个串，拆分出来的集合一个为 $S$ 另一个为上一次保留的字符串。转移分两种。

- 新字符串并入 $S$ 中，$f_{i+1,a_{i-1}} \leftarrow f_{i,S}$。
- 新字符串并入第 $i - 1$ 个字符串，$f_{i+1,S} \leftarrow f_{i,S}$。

维护时可以打全局加标记，统计贡献一个后缀的最小值。实现可以看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair
#define inf 1e9
#define pii pair <int, int>
const int mod = 1e9 + 7;
inline int read () {
	int x = 0, f = 1;
	char ch = getchar ();
	while (ch < '0' || ch > '9') f = ((ch == '-') ? -1 : f), ch = getchar ();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar ();
	return x * f;
}
inline void write (int x) {
	if (x < 0) x = -x, putchar ('-');
	if (x >= 10) write (x / 10);
	putchar (x % 10 + '0');
}
inline int quickmod (int x, int y) {
	int Ans = 1;
	while (y) {
		if (y & 1) Ans = (1ll * Ans * x) % mod;
		x = (1ll * x * x) % mod;
		y >>= 1;
	}
	return Ans;
}
int n, m, Ad;
char ch[25];
int a[200005], pre[200005];
int mn[21][(1<<20)+5];
int f[(1<<20)+5];
inline int chk(int x, int y, int l) {
	return (y & ((1 << l) - 1)) == (x >> (m - l));
}
inline int get_match(int x, int y) {
	for(int i = m; i >= 1; i--) if(chk(x, y, i)) return m - i;
	return m;
}
signed main () {
//	freopen (".in", "r", stdin);
//	freopen (".out", "w", stdout);
	n = read();
	for(int i = 1; i <= n; i++) {
		scanf("%s", ch);
		m = (int)strlen(ch);
		for(int j = 0; j < m; j++) if(ch[j] == '1') a[i] |= (1 << j);
	}
	if(n == 1) return printf("%lld\n", m) & 0;
	if(n == 2) return printf("%lld\n", m + get_match(a[1], a[2])) & 0;
	memset(f, 0x3f, sizeof f), memset(mn, 0x3f, sizeof mn);
	pre[1] = m;
	for(int i = 2; i <= n; i++) pre[i] = pre[i-1] + get_match(a[i-1], a[i]);
	for(int i = 2; i <= n; i++) {
		int ad = get_match(a[i-1], a[i]);
		for(int j = 0; j <= m; j++) f[a[i-1]] = min(f[a[i-1]], mn[j][a[i]&((1<<j)-1)] + (m - j) - ad);
		Ad += ad;
		f[a[i-1]] = min(f[a[i-1]], m + pre[i-1] - Ad);
		for(int j = 0; j <= m; j++) mn[j][a[i-1]>>(m-j)] = min(mn[j][a[i-1]>>(m-j)], f[a[i-1]]);
	}
	int Ans = pre[n];
	for(int i = 0; i < (1 << m); i++) Ans = min(Ans, f[i] + Ad);
	write(Ans), putchar('\n');
	return 0;
}
/*
*/
```

---

## 作者：pldzy (赞：0)

想加写 40min，但是调了一个半钟。纪念一下。

## Solution

CSP2024S T3 原题搬到 01 trie 上做。很典的问题模型，关键性质是所有字符串长度相等。

按照给定的字符串顺序转移。由于长度相等所以需要记录的转移信息只有另一个序列末尾的 01 串的状态。因为最后一个串 $i$ 所在的序列末尾一定是 $i$。

转移是显然的。$f_{i,s}$ 表示到第 $i$ 个串，另一个的末尾 01 串是 $s$，拼接总长度最小值。$f_{i,s}=f_{i-1,s} + m-w(a_i,a_{i-1})$。其中 $m$ 是字符串长度，$w(a_i,a_{i-1})$ 表示它们拼接时可以省略的最长长度。另一种转移是 $f_{i,a_{i-1}}=f_{i-1,s} + m-w(a_i,s)$。上述转移取 $\min$ 即可。

发现第一种就是全局加。第二种发现可以放到 01 trie 上做。具体地，对于 $f_{i-1,s}$ 的值，我们可以把它放到 01 trie 上所有表示 $s$ 后缀的节点。这样做第二种转移的时候，只需要拿 $a_i$ 在 01 trie 上跑，对应的 $w(a_i,s)$ 的值就是当前已经走了的长度。

调了 1.5h 的细节：每次新求出 $f_{i,a_{i-1}}$ 的时候，就把这个值放到 01 trie 上的、所有表示 $a_{i-1}$ 后缀的节点上。但是要记得 trie 的根节点的值也要对它取 $\min$，因为转移的 $w(a_i,s)$ 可以为 $0$，即两个串的匹配长度为 $0$。

## Code

````cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define per(i, a, b) for(int i = a; i >= b; --i)

const int maxn = 2e5 + 5;

int n, m; 
char str[maxn][25];
int tot = 1, t[maxn * 100][2], f[maxn * 100], tg;

inline void Insert(int i, int j, int val){
	int p = 1;
	val -= tg;
	for(; j <= m; ++j){
		int c = str[i][j] - '0';
		if(!t[p][c]) t[p][c] = ++tot;
		p = t[p][c];
	}
	f[p] = min(f[p], val);
}

inline int qry(int i, int j){
	int p = 1, res = f[p];
	for(; j <= m; ++j){
		int c = str[i][j] - '0';
		if(!t[p][c]) break;
		p = t[p][c];
		res = min(res, f[p] - j);
	}
	return res + tg + m;
}

int main(){
	scanf("%d", &n);
	rep(i, 1, n) scanf("%s", str[i] + 1);
	m = strlen(str[1] + 1);
	
	memset(f, 0x3f3f3f3f, sizeof f);
	f[1] = m;
	rep(i, 2, n){
		int len = qry(i, 1), mx = 0;
		rep(j, 1, m){
			int k = 0;
			while(j + k <= m and str[i - 1][j + k] == str[i][k + 1]) ++k;
			if(k < m - j + 1) continue;
			mx = m - j + 1; break;
		}
		tg += m - mx;
		rep(j, 1, m) Insert(i - 1, j, len); f[1] = min(f[1], len - tg);
	}
	int ans = n * m;
	rep(i, 1, tot) ans = min(ans, f[i] + tg);
	printf("%d\n", ans);
	return 0;
}
````

---

## 作者：Moyou (赞：0)

# \[CF83E] Two Subsequences 题解

## 思路

定义 $\text{overlap}(a, b)$ 为字符串 $a$ 的后缀与 $b$ 的前缀的最大相等的长度，有 $|f(a, b)| = |a| + |b| - \text{overlap}(a, b)$，下文称匹配为相邻两串的 $\text{overlap}$。

观察到每次操作之后，一定有一个序列是以 $a_i$ 为结尾的。

所以根据这个性质设计状态：$f_{i ,j}$ 表示考虑到 $a_i$，另一个序列以 $a_j$ 结尾的最少长度。

但是这个状态设计并不好，因为没法进一步优化，发现 $|a_i|\le 20$，所以尝试把另一个序列的结尾状压进状态表示，另外为了方便，可以做一步转化（不做也可以）：最后序列的最短长度就等于总长度减去最多能匹配的长度。

所以可以列出这个状态表示：$f_{i, s}$ 表示考虑到 $a_i$，另一个序列结尾为 $s$ 的最大匹配数量。

推出状态转移方程为：（为了方便书写，这里省略和状态原值取 $\max$ 的步骤）

$$
\begin{aligned}
f_{i, s}\gets f_{i - 1, s} + \text{overlap}(a_{i - 1}, a_i)\\
f_{i, a_{i - 1}}\gets f_{i - 1, s} + \text{overlap}(s, a_i)
\end{aligned}
$$

- 第一个转移代表把 $a_{i - 1}$ 和 $a_{i}$ 放到同一个序列里面；

- 第二个转移代表 $a_{i - 1}$ 和 $a_i$ 不在同一个序列里面，这种情况下要枚举另一个序列结尾本来是什么来转移。

这样是 $O(2^{|a|}n)$ 的，会超时，考虑优化：

首先发现第一个转移是对所有的 $f_{i, s}$ 都加上一个值之后取 $\max$，因为是对所有状态的操作，所以每次加上的这个值可以使用一个标记 $tag$ 维护。

那么瓶颈就到了第二个转移上面，发现第二个转移的特点是只有一个状态发生了改变，并且每次加上的值都介于 $0\sim |a|$ 之间，非常小，考虑枚举加上的值，也就是上一个串 $s$ 的后缀和 $a_i$ 前缀匹配数。

这样就可以把第二个转移写成：

$$
f_{i, a_{i - 1}} \gets \max_{k = 0}^{|a|}(\max_{s_{|a| - k + 1\sim |a|} = a_{i_{1\sim k}}} (f_{i - 1, s}) + k)
$$

进一步发现第二个 $\max$ 可以预处理出来，具体而言，定义 $g^i_{k, x}$ 表示 $\max_{s_{|a| - k + 1\sim |a|} = x} (f_{i - 1, s})$。

把 $g$ 代入原式：

$$
f_{i, a_{i - 1}} \gets \max_{k = 0}^{|a|}(g^i_{k, a_{i_{1\sim k}}} + k)
$$

这样如果得到了 $g$ 数组，我们就可以实现对 $f$ 的 $O(|a|)$ 转移。

如何得到 $g$ 呢，我们发现对于 $g^i$ 而言它的大部分转移都和 $g^{i - 1}$ 相似，只会相差 $\Delta tag$，而唯一一个会改变的是第二维为 $a_{i - 1}$ 的状态，这个每次更新完 $f$ 之后对 $g$ 进行更新即可。

之后进行滚动数组优化即可通过此题。

## 实现

注意一些细节，所有的 $f$ 状态是默认会加上 $tag$ 的，所以转移的时候要减掉 $\Delta tag$ 来转移。

时间复杂度：$O(n|a|\sim n|a|^2)$，这个波浪号取决于你怎么实现 $\text{overlap}$，时间允许当然暴力好写，追求极致可以写 Exkmp。

```cpp
// Problem: Two Subsequences
// Author: Moyou
// Copyright (c) 2023 Moyou All rights reserved.
// Date: 2023-12-06 22:07:10

#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 2e5 + 10;

string a[N];
int n, m, f[(1 << 20) + 5], g[22][(1 << 20) + 5], tag;
int overlap(string a, string b) {
    for(int i = m; ~i; i --) {
        bool flg = 1;
        for(int j = 0; j < i && flg; j ++)
            if(a[m - i + j] != b[j]) flg = 0;
        if(flg) return i;
    }
    return 0;
}
int change(string x) {
    int t = 0;
    for(int i = 0; i < m; i ++)
        t = t * 2 + (x[i] - '0');
    return t;
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i ++) cin >> a[i];
    m = a[1].size();
    memset(f, -0x3f, sizeof f), memset(g, -0x3f, sizeof g);
    for(int i = 2, delta = 0; i <= n; i ++) {
        delta = overlap(a[i - 1], a[i]);
        int now = change(a[i - 1]);
        tag += delta;
        f[now] = max(-delta, f[now]); // 这个转移来自于那些本来第二个序列里面没有放东西的
        for(int j = 0, t = 0; j <= m; j ++) {
            f[now] = max(f[now], g[j][t] + j - delta);
            if(j < m) t = t * 2 + (a[i][j] - '0');
        }
        for(int j = 0, t = 0; j <= m; j ++) {
            g[j][t] = max(g[j][t], f[now]);
            if(j < m) t += (1 << j) * (a[i - 1][m - j - 1] - '0');
        }
    }
    int ans = tag;
    for(int i = 0; i < (1 << m); i ++)
        ans = max(ans, f[i] + tag);
    cout << n * m - ans << '\n';
    return 0;
}

```


---

