# 「GFOI Round 2」Turtle and Nediam

## 题目描述

对一个元素互不相同的长度 $\ge 3$ 的正整数序列 $a$，定义 $a$ 的“肿胃数（nediam）”$f(a)$ 为：

- 当 $|a| = 3$ 时，$f(a)$ 为 $a$ 的中位数；
- 当 $|a| > 3$ 时，取 $a$ 的任意一个长度为 $3$ 的子段 $[a_i, a_{i + 1}, a_{i + 2}]$，记这个子段的中位数为 $x$，$a$ 删掉 $x$ 后的序列为 $b$，$f(a)$ 为所有 $b$ 中 $f(b)$ 的最大值。

乌龟给你一个 $1 \sim n$ 的排列 $p_1, p_2, \ldots, p_n$ 和 $m$ 次询问，每次询问给定 $l, r$，你需要求出 $[p_l, p_{l + 1}, \ldots, p_r]$ 的“肿胃数（nediam）”，即 $f([p_l, p_{l + 1}, \ldots, p_r])$。

## 说明/提示

#### 【样例解释 #1】

生成的四组询问分别为 $(1, 4), (1, 3), (1, 3), (2, 4)$，答案分别为 $2, 3, 3, 3$，所以你需要输出 $(1 \times 2) \oplus (2 \times 3) \oplus (3 \times 3) \oplus (4 \times 3) = 2 \oplus 6 \oplus 9 \oplus 12 = 1$。

对于第一组询问，选择子段 $[1, 3, 4]$ 或 $[3, 4, 2]$ 都会使得 $3$ 被删除。删除 $3$ 后的序列为 $[1, 4, 2]$，中位数为 $2$。

#### 【数据范围】

**本题使用捆绑测试。**

| 子任务编号 | $n \le$ | $m \le$ | 特殊性质 | 分值 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $18$ | $100$ | 无 | $9$ |
| $2$ | $10^6$ | $5 \times 10^6$ | A | $5$ |
| $3$ | $10^3$ | $10^4$ | 无 | $19$ |
| $4$ | $10^5$ | $10^5$ | 无 | $17$ |
| $5$ | $10^6$ | $10^6$ | B | $15$ |
| $6$ | $10^6$ | $10^6$ | 无 | $13$ |
| $7$ | $10^6$ | $5 \times 10^6$ | 无 | $22$ |

- 特殊性质 A：$p_i = i$；
- 特殊性质 B：$p$ 从所有 $1 \sim n$ 的排列中等概率随机生成。

对于所有数据，满足：

- $3 \le n \le 10^6$；
- $1 \le m \le 5 \times 10^6$；
- $0 \le seed, A, B, C < 2^{32}$；
- $p$ 是一个 $1 \sim n$ 的排列。

## 样例 #1

### 输入

```
4 4 114 514 1919 810
1 3 4 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
10 100 123456 789123 456789 123456789
3 9 5 7 6 4 10 8 2 1
```

### 输出

```
142
```

# 题解

## 作者：Aventurine_stone (赞：5)

## 1. 题目分析
首先简化一下肿胃数的定义，每次任意选连续的三个数，删除其中的中位数，在 $n - 3$ 次操作后，剩下的三个数的中位数的最大值即是肿胃数。  
其实我们只需要看有哪些区间中的最大值一定可以作为最终的答案，从中取所有的最大值即可。  
### 判断哪些区间中最大值可以作为最终答案
首先对于总区间，其最大值和最小值都不能作为最终答案，这是显然的。  
接下来我们通过手推发现以下区间中的最大值是可以作为最终答案的（我们用 $mx$ 表示总区间最大值，用 $dmn$ 表示在总区间最大值的左边和右边的区间中更大的最小值，用 $xmn$ 表示在总区间最大值左边和右边的区间中更小的最小值）：  
![](https://cdn.luogu.com.cn/upload/image_hosting/5t7mo2mr.png)  
**证明：**  
对于两个红色区间中的最大值，因为 $dmn$ 或 $xmn$ 都小于它们，所以如果只在红色区间操作的话，红色区间中除了最大值外的数一定可以作为中位数被全部删完，故红色区间中的最大值可以被保留。  
而对于绿色和蓝色区间，因为它们中的最大值又小于 $mx$，最小值又大于 $dmn$ 或 $xmn$，所以一定可以全部作为中位数被删去。  
接下来就只剩左红色区间最大值、$dmn$、$mx$、$xmn$、右红色区间最大值。现在若我们想要保留左红色区间最大值，那么我们可以先选择右边三个数操作将右红色区间最大值删去，再选择两个最小值和总区间的最大值，将 $dmn$ 删去，最后得到最终答案为左红色区间最大值。保留右红色区间最大值的操作是保留左红色区间最大值的镜像操作。  
故两个红色区间的最大值都可以被保留。  
**证毕。**  
简单推一下，我们发现可以先将左右红色区间最大值先删去，所以 $dmn$ 也可以被保留，$dmn$ 也可能是肿胃数，大家不要遗漏了。  
那么就只有这两个区间的最大值可以被保留吗？答案是否定的。  
设在 $mx$ 右边第一个小于 $dmn$ 的数为 $x$，那么区间 $x$ 到 $xmn - 1$ 中的最大值是可以被保留的。  
**证明：**  
因为 $x$ 到 $xmn - 1$ 的右边有蓝色和右红色区间的共同最小值 $xmn$，所以我们可以在不删去 $x$ 的情况下将此区间中的最大值保留下来。至于在 $x$ 左边的蓝色区间则直接用 $dmn$ 和 $mx$ 全部删掉即可。  
我这里用 $qmx$ 表示 $x$ 到 $xmn - 1$ 的最大值（假设最大值不是 $x$，其实后面你仔细想想如果最大值是 $x$ 也没影响），用 $hmx$ 表示右红色区间最大值，左红色区间最大值很显然可以被删掉就不表示了。  
最后情况的处理如下（这里保证 $qmx > hmx$）：  
![](https://cdn.luogu.com.cn/upload/image_hosting/92ohn3sb.png)  
如果 $hmx > qmx$ 呢，那么请问，如果 $hmx > qmx$，你为什么要选 $qmx$ 而不选更大的 $hmx$ 呢，对吧。  
**证毕。**  
对于其他区间中的数，因为有 $dmn$ 和 $xmn$，所以无论怎样都不会成为最终答案的，会直接被当成中位数删掉。  
至于 $dmn$ 和 $xmn$ 的位置交换之后也一样。  
如果没有 $dmn$ 的话，我们可以直接取 $x$ 为 $mx - 1$ 或 $mx + 1$（根据 $xmn$ 在 $mx$ 的左边还是右边而定）。
## 2. 题目做法
对于这道题，我们需要求出 $dmn$、$mx$、$x$、$xmn$ 的位置。  
- 暴力，$O(n^2)$。  
每次询问 $O(n)$ 暴力扫，不过多阐述。
- 线段树加二分，$O(m \log^2{n})$。  
预处理 $O(n)$，每次询问可以 $O(\log{n})$ 求出 $dmn$、$mx$、$xmn$。
对于 $x$，可以在 $mx$ 和 $xmn$ 之间二分，二分中每次都要调用线段树查区间最小值，故每次查询要消耗 $O(\log^2{n})$。
- st 表加二分，$O(n \log{n} + m \log{n})$。  
预处理 $O(n \log{n})$，每次询问 $O(1)$ 求出 $dmn$、$mx$、$xmn$。  
对于 $x$，二分方法和线段树做法一样，只不过每次查区间最小值是 $O(1)$ 的，所以每次查询只消耗 $O(\log{n})$。
- st 表加单调栈，$O(n \log{n} + m)$。  
我这人写的代码常数比较大，上面的做法我的代码都过不了，所以只能用这种做法过。  
时间复杂度瓶颈在于求 $x$，但我们发现在 $dmn$ 到 $x$ 之间没有 $< dmn$ 的数，也就是 $x$ 是在 $dmn$ 的左边或右边的第一个 $< dmn$ 的数，这样很容易想到用单调栈线性 $O(n)$ 预处理，这样每次查 $x$ 也变成 $O(1)$ 了。
## 3. 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
//#define getchar getchar_unlocked
//#define putchar putchar_unlocked
using namespace std;
int n,m; 
unsigned seed,A,B,C;
inline unsigned rnd() {
	seed=A*seed*seed+B*seed+C;
	seed=seed^(seed<<27);
	seed=seed^(seed>>19);
	return seed;
}
int l,r;
inline void gen() {
	do {
		l = rnd() % n + 1;
		r = rnd() % n + 1;
	} while (abs(l - r) < 2);
	if(l>r)
		l^=r^=l^=r;
}
const int N=1000010,M=20;
inline unsigned read()
{
	unsigned x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
inline int max(int x,int y)
{
	return x>y?x:y;
}
int a[N];
int w[N],mx[M][N],mn[M][N];
void init()
{
	for(int i=1;i<=n;i++)
		mx[0][i]=mn[0][i]=i;
	for(int i=1;i<=w[n];i++)
	{
		int t1=n-(1<<i)+1,t2=1<<i-1;
		for(int j=1;j<=t1;j++)
		{
			mx[i][j]=a[mx[i-1][j]]>a[mx[i-1][j+t2]]?mx[i-1][j]:mx[i-1][j+t2];
			mn[i][j]=a[mn[i-1][j]]<a[mn[i-1][j+t2]]?mn[i-1][j]:mn[i-1][j+t2];
		}
	}
}
inline int qmx(int l,int r)
{
	if(l>r)
		return 0;
	int t1=w[r-l+1],t2=(1<<t1)-1;
	return a[mx[t1][l]]>a[mx[t1][r-t2]]?mx[t1][l]:mx[t1][r-t2];
}
inline int qmn(int l,int r)
{
	if(l>r)
		return 0;
	int t1=w[r-l+1],t2=(1<<t1)-1;
	return a[mn[t1][l]]<a[mn[t1][r-t2]]?mn[t1][l]:mn[t1][r-t2];
}
stack<int>s;
int l1[N],r1[N];
ll ans;
int main()
{
	n=read(),m=read(),seed=read(),A=read(),B=read(),C=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=2;i<=n;i++)
		w[i]=w[i>>1]+1;
	init();
	a[0]=INT_MAX;
	for(int i=1;i<=n;i++)
	{
		while(!s.empty()&&a[s.top()]>a[i])
			r1[s.top()]=i,s.pop();
		s.push(i);
	}
	while(!s.empty())//记得清空！ 
		s.pop();
	for(int i=n;i;i--)
	{
		while(!s.empty()&&a[s.top()]>a[i])
			l1[s.top()]=i,s.pop();
		s.push(i);
	}
	for(ll i=1;i<=m;i++)
	{
		gen();
		int zmx=qmx(l,r),lmn=qmn(l,zmx-1),rmn=qmn(zmx+1,r);
		if(a[lmn]<a[rmn])
			rmn?lmn=l1[rmn]:lmn=zmx-1;
		else if(a[lmn]>a[rmn])
			lmn?rmn=r1[lmn]:rmn=zmx+1;
		ans^=i*max(lmn?a[qmx(l,lmn)]:0,rmn?a[qmx(rmn,r)]:0);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：EuphoricStar (赞：3)

求出区间最大值位置 $x$。显然 $p_x$ 不能成为答案且 $p_x$ 不会被删除。考虑 $l \le i < x$ 的数中，答案 $\ge p_i$ 需要满足的条件。可以发现充要条件是 $[i, x]$ 中的最小值 $\le [l, i]$ 中的最小值或 $[x, r]$ 中的最小值。因为若两侧最小值都小于中间最小值那么这两个数无法在删 $p_x$ 前被删，否则一定能借助中间最小值把两侧全部删光。

求出 $[l, x]$ 中最小值的位置 $y$ 和 $[x, r]$ 中最小值的位置 $z$。那么若 $[i, x]$ 中最小值 $\le [l, i - 1]$ 中最小值需要满足 $i \le y$，若 $[i, x]$ 中最小值 $\le [x, r]$ 中最小值，设 $L_j$ 为 $p_j$ 前面第一个比 $p_j$ 小的数，那么需要满足 $i \le L_z$。求出 $i$ 的范围后求区间最大值即可。

$x < i \le r$ 的情况类似。

时间复杂度 $O(n \log n + m)$ 或 $O(n + m)$。


```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define uint unsigned
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<int, int> pii;

const int maxn = 1000100;
const int logn = 22;

int n, m, a[maxn], b[maxn], f[logn][maxn], g[logn][maxn], L[maxn], R[maxn], stk[maxn], top;
uint seed, A, B, C;

inline uint rnd() {
	seed = A * seed * seed + B * seed + C;
	seed = seed ^ (seed << 27);
	seed = seed ^ (seed >> 19);
	return seed;
}

inline pii gen() {
	int l, r;
	do {
		l = rnd() % n + 1;
		r = rnd() % n + 1;
	} while (abs(l - r) < 2);
	if (l > r) {
		swap(l, r);
	}
	return make_pair(l, r);
}

inline int qmax(int l, int r) {
	if (l > r) {
		return 0;
	}
	int k = __lg(r - l + 1);
	return max(f[k][l], f[k][r - (1 << k) + 1]);
}

inline int qmin(int l, int r) {
	int k = __lg(r - l + 1);
	return min(g[k][l], g[k][r - (1 << k) + 1]);
}

void solve() {
	scanf("%d%d%u%u%u%u", &n, &m, &seed, &A, &B, &C);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		b[a[i]] = i;
		f[0][i] = g[0][i] = a[i];
	}
	for (int j = 1; (1 << j) <= n; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
			f[j][i] = max(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
			g[j][i] = min(g[j - 1][i], g[j - 1][i + (1 << (j - 1))]);
		}
	}
	for (int i = 1; i <= n; ++i) {
		while (top && a[stk[top]] > a[i]) {
			--top;
		}
		L[i] = (top ? stk[top] : 0);
		stk[++top] = i;
	}
	top = 0;
	for (int i = n; i; --i) {
		while (top && a[stk[top]] > a[i]) {
			--top;
		}
		R[i] = (top ? stk[top] : n + 1);
		stk[++top] = i;
	}
	ll ans = 0;
	for (int i = 1; i <= m; ++i) {
		pii p = gen();
		int l = p.fst, r = p.scd;
		int x = b[qmax(l, r)];
		int y = b[qmin(l, x)], z = b[qmin(x, r)];
		ans ^= (1LL * i * max(qmax(l, max(min(y, x - 1), L[z])), qmax(min(max(z, x + 1), R[y]), r)));
	}
	printf("%lld\n", ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```

---

