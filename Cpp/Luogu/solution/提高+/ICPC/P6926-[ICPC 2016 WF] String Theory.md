# [ICPC 2016 WF] String Theory

## 题目描述

嵌套引号不仅在写作具有复杂叙述结构的文学作品时很有用，在编程语言中也是如此。虽然在不同的嵌套层次使用不同的引号似乎是必要的，但还有一种替代方法。我们可以使用 $k$-引号来表示各种嵌套层次，其定义如下。

一个 $1$-引号是一个以引号字符开始，以另一个引号字符结束且中间不包含引号字符的字符串。这只是通常的（未嵌套的）引号。例如，'this is a string' 是一个 $1$-引号。

对于 $k > 1$，一个 $k$-引号是一个以 $k$ 个引号字符开始，以另一个 $k$ 个引号字符结束且中间包含一个嵌套字符串的字符串。嵌套字符串是一个非空的 $(k-1)$-引号序列，可以在前、后或中间被任意数量的非引号字符分隔。例如，''All 'work' and no 'play''' 是一个 $2$-引号。

给定一个字符串的描述，你必须确定其最大可能的嵌套层次。

## 说明/提示

时间限制：2000 毫秒，内存限制：1048576 kB。

国际大学生程序设计竞赛（ACM-ICPC）世界总决赛 2016。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
2 1 1 1 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1
22
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1
1
```

### 输出

```
no quotation
```

# 题解

## 作者：0000pnc (赞：4)

神仙题。

首先如果所有的 $a_{i}$ 之和为奇数那么一定无解。

然后这里有个关键观察：对于 $n\ge 2$，一个 n-quotation 序列（即由若干个 n-quotation 拼接而成的序列）一定是一个完整的 n-quotation。

证明考虑归纳。首先对于 $n=2$ 是比较容易的，把首尾的两个引号分别去掉后剩下的一定是一个 1-quotation 序列（因为所有数之和是偶数，一定能够找到合适的匹配）。

如果 $n=k-1$ 时成立，那么 $n=k$ 时每个 n-quotation 都会恰好包括一个 (n-1)-quotation。此时这个序列大概长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/8mobhd4m.png)

把首尾的 $\{k,k-1,k-2,\cdots,2\}$ 单独拎出来，那中间的显然是一个 1-quotation 序列（图中未写出“序列”），这样就符合 n-quotation 的定义了。

于是可以枚举答案 $x$，然后对于每个答案都可以利用这个性质 $\mathcal{O}(x)$ 判断是否合法（即：依次从头和尾删去 $x,x-1,x-2,\cdots,2$ 个引号，每次判断删除操作是否合法即可）。注意到答案的上界是 $\min(a_1,a_n)$，因此时间复杂度为 $\mathcal{O}(V^{2})$（或者 $\mathcal{O}(nV)$？）。

最后可能需要特判答案为 $1$ 的情况，这个也很好处理。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, a[105], sm, tmp[105];

bool chk(int x) {
	for (int i = 1; i <= n; i++) tmp[i] = a[i];
	int l = 1, r = n, i;
	for (i = x; i > 1 && l <= r; i--) {
		if (tmp[l] < i) break;
		tmp[l] -= i; if (!tmp[l]) ++l;
		if (tmp[r] < i) break;
		tmp[r] -= i; if (!tmp[r]) --r;
	}
	return (l <= r && i == 1);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), sm += a[i];
	if (sm & 1) return printf("no quotation\n"), 0;
	for (int i = min(a[1], a[n]); i >= 2; i--) {
		if (chk(i)) return printf("%d\n", i), 0;
	}
	return printf(sm == 2 ? "1\n" : "no quotation\n"), 0;
}
```

---

## 作者：Starlight237 (赞：1)

> 定义 $1$ 级引用是一个以引号字符 ' 开头和结尾，中间不包含引号字符的字符串。定义 $k$ 级引用为两端各有连续 $k(k>1)$ 个引号，中间有若干个 $k-1$ 级引用的字符串，其中第一个 $k-1$ 级引用前，最后一个 $k-1$ 级引用后，相邻两个 $k-1$ 级引用之间都可以添加任意个非引用字符。

> 现给定一个字符串中极长连续引号段的个数 $n(n\le100)$，和这 $n$ 个极长连续引号段的长度 $a_1,...,a_n$，求最大的 $k$，使得这个字符串是一个 $k$ 级引用。
若这样的 $k$ 不存在，输出 `no quotation`。

**Lemma** 一个字符串为 $k$ 级引用，当且仅当它开头的连续引号段长度不少于 $1+2+...+k$，结尾的连续引号段长度也不少于 $1+2+...+k$，并且引号总数为不少于 $2(1+2+...+k)$ 的偶数。  
证明：必要性显然，充分性只需要把中间的引号两两配对成一级引用即可。

显而易见 $k=O(\sqrt{\sum a_i})$，因此可以暴力枚举 $k$，判断字符串是否符合上面这个条件。具体地，可以先将所有 $a_i$ 拼起来成为一个长度为 $len=\sum a_i$ 的字符串 $S$，令 $b_i$ 表示**从 $i$ 处起**极长连续引号段的长度（注意，虽然我们将所有引号段拼成了一块，但是仍然认为相邻两个 $a_i$ 段之间是不连续的），$pre_{i,j}$ 表示从 $j$ 处起的极长连续引号段长度是否不少于 $1+...+i$，$suf_{i,j}$ 表示从 $[1,j]$ 中包含 $j$ 的极长连续引号段长度是否不少于 $1+...+i$，最终只需要判断 $pre_{k,1}$ 和 $suf_{k,len}$ 是否同时成立。

注意需要特判 $len=2$ 的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace io {
#define BUFS 100000
	char in[BUFS], *p = in, *pp = in;
#define gc (p == pp && (pp = (p = in) + fread(in, 1, BUFS, stdin), p == pp) ? EOF : *p++)
	inline int read() {
		int x = 0; char ch, f = 0;
		while (!isdigit(ch = gc)) f |= ch == '-';
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc;
		return f ? -x : x; 
	}
}
#define rd io :: read
const int N = 110, M = 10010;
int n, len, a[N], f[N], b[M], ans = 0x3f3f3f3f;
bool pre[N][M], suf[N][M];
int main() {
	for (int i = 1; i < N; ++i) f[i] = f[i - 1] + i;
	n = rd();
	for (int i = 1; i <= n; ++i)
		a[i] = rd(), len += a[i], b[len] = 1, (i == 1 || i == n) && (ans = min(ans, a[i]), false);
	if (len & 1) return !printf("no quotation");
	for (int i = len; i; --i) if (!b[i]) b[i] = b[i + 1] + 1;
	ans = min(ans, ___); // 此处只需要填写一个 sqrt(n) 级别的足够大但不会 TLE 的数字即可
	memset(pre[1], true, sizeof pre[1]);
	memset(suf[1], true, sizeof suf[1]);
	for (int i = 2; i <= ans; ++i)
		for (int j = 1; j <= len - f[i] + 1; ++j)
			pre[i][j] = b[j] >= i && pre[i - 1][j + i];
	for (int i = 2; i <= ans; ++i)
		for (int j = f[i]; j <= len; ++j)
			suf[i][j] = b[j - i + 1] >= i && suf[i - 1][j - i];
	for (; ans > 1; --ans)
		if (pre[ans][1] && suf[ans][len]) return !printf("%d", ans);
	puts(len == 2 ? "1" : "no quotation");
	return 0;
}
```

---

