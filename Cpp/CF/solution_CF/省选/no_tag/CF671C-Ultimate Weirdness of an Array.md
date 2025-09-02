# Ultimate Weirdness of an Array

## 题目描述

Yasin has an array $ a $ containing $ n $ integers. Yasin is a 5 year old, so he loves ultimate weird things.

Yasin denotes weirdness of an array as maximum $ gcd(a_{i},a_{j}) $ value among all $ 1<=i<j<=n $ . For $ n<=1 $ weirdness is equal to $ 0 $ , $ gcd(x,y) $ is the greatest common divisor of integers $ x $ and $ y $ .

He also defines the ultimate weirdness of an array. Ultimate weirdness is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF671C/a3868a08df9a3849d15ef8af5c85461c405fe050.png) where $ f(i,j) $ is weirdness of the new array $ a $ obtained by removing all elements between $ i $ and $ j $ inclusive, so new array is $ [a_{1}...\ a_{i-1},a_{j+1}...\ a_{n}] $ .

Since 5 year old boys can't code, Yasin asks for your help to find the value of ultimate weirdness of the given array $ a $ !

## 说明/提示

Consider the first sample.

- $ f(1,1) $ is equal to $ 3 $ .
- $ f(2,2) $ is equal to $ 1 $ .
- $ f(3,3) $ is equal to $ 2 $ .
- $ f(1,2) $ , $ f(1,3) $ and $ f(2,3) $ are equal to $ 0 $ .

 Thus the answer is $ 3+0+0+1+0+2=6 $ .

## 样例 #1

### 输入

```
3
2 6 3
```

### 输出

```
6
```

# 题解

## 作者：eee_hoho (赞：4)

首先我们用$nxt_l$表示当$f(l,r)\le i$时，$l$对应的右端点$r$最往左能取到哪里，初始时$nxt_l=l$，如果不存在合法右端点就记$nxt_l=n+1$。

然后考虑从大到小枚举$i$，当从$f(l,r)\le i$变为$f(l,r)\le i-1$时，我们需要删除$gcd=i$的贡献，找出$i$的倍数在原序列中的下标记为$x_1,x_2......x_m$，而我们新得到的区间$[l,nxt_l']$肯定是要满足包含$m-1$个$x_i$的，不然答案就至少是$i$了，所以我们进行如下修改操作：

- $l\in(x_2,n]$，$nxt_l=n+1$

- $l\in(x_1,x_2]$，$nxt_l=max(nxt_l,x_m)$

- $l\in[1,x_1]$，$nxt_l=max(nxt_l,x_{m-1})$

2,3操作看似需要吉司机线段树来维护，但是我们冷静下来分析一波，$nxt$数组一定是单调不降，所以一定是进行区间的一段前缀覆盖，直接线段树上二分修改复杂度就是$O(nlogn)$。

其实开始时$O(n\sqrt n)$处理每个数倍数的位置就已经足够了，但是也可以优化，因为我们最多只需要2个开头的和2个结尾的，那么直接合并$i$的倍数的集合就好了，复杂度是$O(nlogn)$，我比较懒就直接写的第一种QAQ

``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define zrt k << 1
#define yrt k << 1 | 1
const int N = 2e5;
using namespace std;
int n,a[N + 5],Mx;
long long ans,las;
vector <int> d[N + 5];
struct Seg
{
    long long sm[N * 5 + 5],tag[N * 4 + 5];
    int mi[N * 4 + 5],mx[N * 4 + 5];
    void pushup(int k)
    {
        sm[k] = sm[zrt] + sm[yrt];
        mi[k] = min(mi[zrt],mi[yrt]);
        mx[k] = max(mx[zrt],mx[yrt]);
    }
    void build(int k,int l,int r)
    {
        if (l == r)
        {
            mx[k] = mi[k] = sm[k] = l;
            return;
        }
        int mid = l + r >> 1;
        build(zrt,l,mid);
        build(yrt,mid + 1,r);
        pushup(k);
    }
    void cha(int k,int l,int r,int z)
    {
        sm[k] = 1ll * (r - l + 1) * z;
        mi[k] = mx[k] = z;
        tag[k] = z;
    }
    void pushdown(int k,int l,int r,int mid)
    {
        if (tag[k])
        {
            cha(zrt,l,mid,tag[k]);
            cha(yrt,mid + 1,r,tag[k]);
            tag[k] = 0;
        }
    }
    void modify(int k,int l,int r,int x,int y,int z)
    {
        if (x > y)
            return;
        if (r < x || l > y || mi[k] >= z)
            return;
        if (l >= x && r <= y && mx[k] <= z)
        {
            cha(k,l,r,z);
            return;
        }
        if (l == r)
        {
            sm[k] = mi[k] = mx[k] = z;
            return;
        }
        int mid = l + r >> 1;
        pushdown(k,l,r,mid);
        modify(zrt,l,mid,x,y,z);
        modify(yrt,mid + 1,r,x,y,z);
        pushup(k);
    }
}tree;
int main()
{
    scanf("%d",&n);
    for (int i = 1;i <= n;i++)
        scanf("%d",&a[i]),Mx = max(Mx,a[i]);
    for (int i = 1;i <= n;i++)
        for (int j = 1;j * j <= a[i];j++)
            if (a[i] % j == 0)
            {
                d[j].push_back(i);
                if (j * j != a[i])
                    d[a[i] / j].push_back(i);
            }
    tree.build(1,1,n);
    las = 1ll * n * (n + 1) - tree.sm[1];
    int x1,x2,x3,x4;
    for (int i = Mx;i >= 1;i--)
    {
        if (d[i].size() < 2)
            continue;
        x1 = *d[i].begin();
        x2 = *(d[i].begin() + 1);
        x3 = *(d[i].end() - 2);
        x4 = *(d[i].end() - 1);
        tree.modify(1,1,n,x2 + 1,n,n + 1);
        tree.modify(1,1,n,x1 + 1,x2,x4);
        tree.modify(1,1,n,1,x1,x3);
        ans += (las - (1ll * n * (n + 1) - tree.sm[1])) * i;
        las = 1ll * n * (n + 1) - tree.sm[1];
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：duyi (赞：2)

# CF671C Ultimate Weirdness of an Array

## 本题题解

先预处理出，每个数值在序列里第一次和最后一次出现的位置。再枚举每个数值的倍数（时间复杂度是调和级数），求出**每个值的倍数**在序列里第一次和最后一次出现的位置。

考虑求 $f(i,j)$。设 $\gcd$ 取到最大值的两个位置为 $x,y$ ($x,y\in\{[1, i - 1] \cup[j + 1,n]\}$)，不失一般性地设 $x < y$。可以分三种情况：

- $x,y$ 全都在 $[1, i - 1]$ 内部。
- $x,y$ 全部在 $[j + 1, n]$ 内部。
- $x$ 在 $[1, i - 1]$，$y$ 在 $[j + 1, n]$。

前两种情况是类似的。以第一种为例。从小到大枚举 $i$。显然答案是单调不降的。$i$ 的答案相比于 $i - 1$ 的答案，其实就是多出了 $x < i - 1, y = i - 1$ 的情况。考虑这种情况的 $\gcd$ 是多少。可以暴力枚举 $a_{i- 1}$ 的所有约数，看这个约数第一次出现的位置（前面已经预处理出来）是否小于 $i - 1$，然后用这个约数更新答案。

因为每个数至多只有 $\mathcal{O}(\sqrt{n})$ 个约数，所以暴力实现的时间复杂度是 $\mathcal{O}(n\sqrt{n})$。但是发现，如果当前 $a_{i - 1}$ 这个值在前面已经出现过，那 $a_{i - 1}$ 这个数直接可以更新答案，这一定比它的任何约数都优，因此此时就不必枚举约数了。于是，对每个数值，我们只枚举一次约数，时间复杂度就是 $1\dots 2\times 10^5$ 里所有数的约数个数和，是 $\mathcal{O}(n\log n)$ 的。

对于第三种情况。考虑从小到大枚举 $i$，在线段树上维护所有 $j$ 的答案。仍然考虑从 $i - 1$ 变到 $i$ 对答案的影响。发现只多出了 $x = i - 1, y \in[j + 1, n]$ 的情况。枚举 $a_{i - 1}$ 的所有约数，设它最后一次出现的位置为 $p$，则 $j\in[i, p - 1]$ 的答案可以被更新（也就是对这个约数取 $\max$）。另外，$j = i - 1$ 这个位置的答案需要被清空。综上，我们需要一个数据结构，支持：

- 让一段区间对一个数取 $\max$。
- 更改一个单点的数值（设为 $0$）。
- 求全局和。

可以用吉老师线段树维护，单次操作时间复杂度是 $\mathcal{O}(\log n)$ 的。因为要枚举约数，总时间复杂度 $\mathcal{O}(n\sqrt{n}\log n)$。和前面类似，我们发现，同一个 $a_{i - 1}$ 的值，如果在之前出现过，则现在并不会有新的价值。于是每个数值只枚举一次约数（并做线段树操作），时间复杂度 $\mathcal{O}(n\log^2 n)$。

总时间复杂度 $\mathcal{O}(n\log^2 n)$。

## 参考代码

```cpp
// problem:
#include <bits/stdc++.h>
using namespace std;

#define mk make_pair
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

/* --------------- fast io --------------- */ // begin
namespace Fread {
const int SIZE = 1 << 21;
char buf[SIZE], *S, *T;
inline char getchar() {
	if (S == T) {
		T = (S = buf) + fread(buf, 1, SIZE, stdin);
		if (S == T) return '\n';
	}
	return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SIZE = 1 << 21;
char buf[SIZE], *S = buf, *T = buf + SIZE;
inline void flush() {
	fwrite(buf, 1, S - buf, stdout);
	S = buf;
}
inline void putchar(char c) {
	*S++ = c;
	if (S == T) flush();
}
struct NTR {
	~ NTR() { flush(); }
} ztr;
} // namespace Fwrite
#ifdef ONLINE_JUDGE
	#define getchar Fread :: getchar
	#define putchar Fwrite :: putchar
#endif
namespace Fastio {
struct Reader {
	template<typename T>
	Reader& operator >> (T& x) {
		char c = getchar();
		T f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		x = 0;
		while (c >= '0' && c <= '9') {
			x = x * 10 + (c - '0');
			c = getchar();
		}
		x *= f;
		return *this;
	}
	Reader& operator >> (char& c) {
		c = getchar();
		while (c == '\n' || c == ' ') c = getchar();
		return *this;
	}
	Reader& operator >> (char* str) {
		int len = 0;
		char c = getchar();
		while (c == '\n' || c == ' ') c = getchar();
		while (c != '\n' && c != ' ') {
			str[len++] = c;
			c = getchar();
		}
		str[len] = '\0';
		return *this;
	}
	Reader(){}
} cin;
const char endl = '\n';
struct Writer {
	template<typename T>
	Writer& operator << (T x) {
		if (x == 0) { putchar('0'); return *this; }
		if (x < 0) { putchar('-'); x = -x; }
		static int sta[45];
		int top = 0;
		while (x) { sta[++top] = x % 10; x /= 10; }
		while (top) { putchar(sta[top] + '0'); --top; }
		return *this;
	}
	Writer& operator << (char c) {
		putchar(c);
		return *this;
	}
	Writer& operator << (char* str) {
		int cur = 0;
		while (str[cur]) putchar(str[cur++]);
		return *this;
	}
	Writer& operator << (const char* str) {
		int cur = 0;
		while (str[cur]) putchar(str[cur++]);
		return *this;
	}
	Writer(){}
} cout;
} // namespace Fastio
#define cin Fastio :: cin
#define cout Fastio :: cout
#define endl Fastio :: endl
/* --------------- fast io --------------- */ // end

const int MAXN = 2e5;
const int INF = 1e9;

int n, a[MAXN + 5];
int fstpos[MAXN + 5], lstpos[MAXN + 5];
vector<int> d[MAXN + 5];
bool vis[MAXN + 5];

int f[MAXN + 5];
struct SegmentTree {
	
	ll sum[MAXN * 4 + 5];
	ll mn[MAXN * 4 + 5], semn[MAXN * 4 + 5];
	int mncnt[MAXN * 4 + 5];
	
	void push_up(int p) {
		int ls = (p << 1), rs = (p << 1 | 1);
		sum[p] = sum[ls] + sum[rs];
		if (mn[ls] < mn[rs]) {
			mn[p] = mn[ls];
			mncnt[p] = mncnt[ls];
			semn[p] = min(semn[ls], mn[rs]);
		} else if (mn[ls] > mn[rs]) {
			mn[p] = mn[rs];
			mncnt[p] = mncnt[rs];
			semn[p] = min(semn[rs], mn[ls]);
		} else {
			mn[p] = mn[ls];
			mncnt[p] = mncnt[ls] + mncnt[rs];
			semn[p] = min(semn[ls], semn[rs]);
		}
	}
	void push_down(int p) {
		int ls = (p << 1), rs = (p << 1 | 1);
		if (mn[p] > mn[ls]) {
			assert(mn[p] < semn[ls]);
			sum[ls] += (ll)mncnt[ls] * (mn[p] - mn[ls]);
			mn[ls] = mn[p];
		}
		if (mn[p] > mn[rs]) {
			assert(mn[p] < semn[rs]);
			sum[rs] += (ll)mncnt[rs] * (mn[p] - mn[rs]);
			mn[rs] = mn[p];
		}
	}
	
	template<typename Tp>
	void build(int p, int l, int r, const Tp* arr) {
		if (l == r) {
			sum[p] = arr[l];
			mn[p] = arr[l];
			semn[p] = INF;
			mncnt[p] = 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(p << 1, l, mid, arr);
		build(p << 1 | 1, mid + 1, r, arr);
		
		push_up(p);
	}
	
	void range_ckmax(int p, int l, int r, int ql, int qr, ll v) {
		if (v <= mn[p]) {
			return;
		}
		
		if (ql <= l && qr >= r) {
			if (v < semn[p]) {
				sum[p] += (ll)mncnt[p] * (v - mn[p]);
				mn[p] = v;
				return;
			}
		}
		
		int mid = (l + r) >> 1;
		push_down(p);
		if (ql <= mid) {
			range_ckmax(p << 1, l, mid, ql, qr, v);
		}
		if (qr > mid) {
			range_ckmax(p << 1 | 1, mid + 1, r, ql, qr, v);
		}
		
		push_up(p);
	}
	
	void point_clear(int p, int l, int r, int pos) {
		if (l == r) {
			sum[p] = 0;
			mn[p] = 0;
			semn[p] = INF;
			mncnt[p] = 1;
			return;
		}
		int mid = (l + r) >> 1;
		push_down(p);
		if (pos <= mid) {
			point_clear(p << 1, l, mid, pos);
		} else {
			point_clear(p << 1 | 1, mid + 1, r, pos);
		}
		
		push_up(p);
	}
	
	SegmentTree() {}
};

SegmentTree T;

int main() {
	cin >> n;
	for (int i = 1; i <= MAXN; ++i) {
		fstpos[i] = n + 1;
		lstpos[i] = 0;
	}
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		lstpos[a[i]] = i;
	}
	for (int i = n; i >= 1; --i) {
		fstpos[a[i]] = i;
	}
	
	for (int i = 1; i <= MAXN; ++i) {
		for (int j = i; j <= MAXN; j += i) {
			ckmax(lstpos[i], lstpos[j]);
			ckmin(fstpos[i], fstpos[j]);
			d[j].push_back(i);
		}
	} // lstpos[i]: i 的倍数的最大出现位置
	
	
	for (int i = n - 1; i >= 1; --i) {
		f[i] = f[i + 1];
		if (!vis[a[i + 1]]) {
			vis[a[i + 1]] = 1;
			for (int j = 0; j < SZ(d[a[i + 1]]); ++j) {
				int x = d[a[i + 1]][j];
				if (lstpos[x] > i + 1) {
					ckmax(f[i], x);
				}
			}
		} else {
			ckmax(f[i], a[i + 1]);
		}
	}
	
	for (int i = 1; i <= MAXN; ++i) vis[i] = 0;
	
	T.build(1, 1, n, f);
	ll ans = T.sum[1];
	f[1] = 0;
	for (int i = 2; i <= n; ++i) {
		T.point_clear(1, 1, n, i - 1);
		
		f[i] = f[i - 1];
		if (!vis[a[i - 1]]) {
			vis[a[i - 1]] = 1;
			for (int j = 0; j < SZ(d[a[i - 1]]); ++j) {
				int x = d[a[i - 1]][j];
				if (lstpos[x] >= i + 1) {
					T.range_ckmax(1, 1, n, i, lstpos[x] - 1, x);
				}
				if (fstpos[x] < i - 1) {
					ckmax(f[i], x);
				}
			}
		} else {
			ckmax(f[i], a[i - 1]);
		}
		T.range_ckmax(1, 1, n, i, n, f[i]);
		
		ans += T.sum[1];
	}
	cout << ans << endl;
	return 0;
}
```





---

## 作者：Alex_Eon (赞：1)

#### [$\color{blueviolet}\text{CF 杂题集（点我）}$](https://www.cnblogs.com/Eon-Sky/p/17763683.html)
#### [$\color{red}\text{博客内食用效果更佳（点我）}$](https://www.luogu.com.cn/blog/Ksy/solution-cf671cc)

## 主体思路：枚举+线段树上二分

## 复杂度：$O(n \log n)$

## 完整思路

优美的题，感觉很仙。

一般这种题可以先考虑枚举左端点，然后看所有右端点的整体贡献，但这道题要求 $\gcd$ 很不友好，无法这么处理。稍微转换一下思路，枚举答案，求每种答案的方案数，根据差分思想可以考虑求答案 $\le i$ 的总方案数（下文称为 $val_i$），这样对于每个 $i$ 求完之后可以差分得到某个值的答案，这样最终答案的计算是简单的。

设 $i$ 为当前枚举的答案上界，我们尝试求出 $f(l, r) \le i$ 的合法 $(l, r)$ 数量。首先观察到当 $i$ 为极大值的时候，所有区间都是符合条件的，因此我们考虑从大到小枚举 $i$ 每次修改贡献的变化量。

固定现在枚举到的 $i$，设 $nex_j$ 为对于第 $j$ 个数，在保证 $f(j, r) \le i$ 的条件下的最小的 $r$，若不存在这样的 $r$ 则 $nex_j = n + 1$。于是有：

$$val_i = \sum \limits_{1 \le j \le n} n - nex_j + 1 = n(n + 1) - \sum \limits_{1 \le j \le n} nex_j$$

所以只需要考虑维护 $nex_j$ 的和即可，现在考虑当 $i$ 变为 $i - 1$ 我们修改什么。显然地，对于所有答案等于 $i$ 的区间我们需要舍去，而只有是 $i$ 的倍数的数才能造成贡献。在某个所选区间外（即没有删除的数中），$i$ 的倍数至多出现一次时，此区间才可以合法，换句话说，我们需要将所有区间外存在多个 $i$ 的倍数的区间扩展，考虑分类讨论进行扩展。

设 $p_1, p_2, \dots, p_{k - 1}, p_k$ 表示 $i$ 的倍数的出现位置（$p_t < p_{t + 1} \quad (1 \le t < n)$），分以下几种进行讨论：

- $1 \le j \le p_1$：此时区间左侧没有 $i$ 的倍数，所以我们可以让区间右侧出现至多一个 $i$ 的倍数，有 $nex_j \leftarrow \max\{nex_j, p_{k - 1}\}$。
- $p_1 < j \le p_2$：此时区间左侧有一个 $i$ 的倍数，所以我们必须让区间包括右侧所有 $i$ 的倍数，有 $nex_j \leftarrow \max\{nex_j, p_k\}$。

- $p_2 < j$：此时我们不论如何修改 $nex_j$ 都没有合法的值，因为区间左侧永远有至少两个 $i$ 的倍数，所以 $nex_j \leftarrow n + 1$。

我们知道维护逻辑后考虑维护方式，这个东西是一个区间对某个数取 $\max$，全局询问和的东西。

单纯的维护是较为困难的，我们需要注意到 $nex_j$ 在 $i$ 固定时的取值是单调不降的，也就是说区间 $[l, r]$ 对某数 $v$ 取 $\max$ 等价于将某段区间 $[l, x]$ 全都赋值为 $v$（也可能完全不赋值），这个东西是可以用线段树上二分解决的。所以考虑将 $nex_j$ 扔到线段树上维护，线段树上二分时需要注意边界以及返回条件。

目前为止还没有提到 $p$ 的求法，我们发现只有 $p_1, p_2, p_{k - 1}, p_k$ 是有用的，所以对于每个数字只需要求出其倍数的前两次出现和后两次出现即可。维护方式是简单的，首先预处理每个数的约数，复杂度是 $n\ln n$ 的，然后对于每个输入的 $a_i$ 都枚举其因数，用 $i$ 去更新维护的 $p$，详见代码。这里因为 $a_i$ 互不相同所以复杂度是调和级数的，如果 $a_i$ 都拉满并且相同，那预处理复杂度上界应该就是 $n\sqrt V$ 了。

最后注意所有 $nex_j$ 初值都有 $nex_j = j$。

## 代码实现需要注意的地方：

- 求和需要开 **long long**。
- 线段树上二分注意边界，尤其是左端点大于右端点的情况。


## 参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int UIT;
typedef double DB;
typedef pair<int, int> PII;

#define fi first
#define se second
//--------------------//
const int N = 2e5 + 5;

int n, a[N], l[N][2], r[N][2];
// l[i][0/1] 是 i 第一次、第二次出现位置
// r[i][0/1] 是 i 倒数第一次、倒数第二次出现位置

LL val[N];

vector<int> d[N]; // 约数
//--------------------//
#define ls(x) ((x) << 1)
#define rs(x) ((x) << 1 | 1)

const int TN = 8e5 + 5;

struct Seg_Tree {
    struct Seg_Tree_Node {
        int mnv, mxv, lazy;
        LL sum;
    } t[TN];

    void tag(int rt, int L, int R, int val) {
        t[rt].mnv = t[rt].mxv = t[rt].lazy = val;
        t[rt].sum = 1LL * (R - L + 1) * t[rt].mnv;
    }

    void push_up(int rt) {
        t[rt].sum = t[ls(rt)].sum + t[rs(rt)].sum;
        t[rt].mnv = min(t[ls(rt)].mnv, t[rs(rt)].mnv);
        t[rt].mxv = max(t[ls(rt)].mxv, t[rs(rt)].mxv);
    }

    void push_down(int rt, int L, int R) {
        if (!t[rt].lazy)
            return;
        int mid = L + R >> 1;
        tag(ls(rt), L, mid, t[rt].lazy), tag(rs(rt), mid + 1, R, t[rt].lazy);
        t[rt].lazy = 0;
    }

    void change(int rt, int L, int R, int l, int r, int val) {
        if (l > r || t[rt].mnv >= val) // 边界特判
            return;
        if (L >= l && R <= r && t[rt].mxv <= val) // 合法则区间覆盖
            return tag(rt, L, R, val);
        push_down(rt, L, R);
        int mid = L + R >> 1;
        if (l <= mid)
            change(ls(rt), L, mid, l, r, val);
        if (r > mid)
            change(rs(rt), mid + 1, R, l, r, val);
        push_up(rt);
    }
} T;

void init() { // 预处理约数
    for (int i = 1; i <= N - 5; i++)
        for (int j = i; j <= N - 5; j += i)
            d[j].push_back(i);
}
//--------------------//
int main() {
    init();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        for (auto j : d[a[i]]) { // 枚举约数处理倍数出现位置
            if (!l[j][0])
                l[j][0] = i;
            else if (!l[j][1])
                l[j][1] = i;
            r[j][1] = r[j][0], r[j][0] = i;
        }
    }
    for (int i = 1; i <= n; i++) // nex 初值
        T.change(1, 1, n, i, i, i);
    for (int i = N - 4; i; i--) {
        if (l[i][0] != r[i][0]) { // 如果此数字出现不止一次时才会造成影响
            T.change(1, 1, n, 1, l[i][0], r[i][1]);
            T.change(1, 1, n, l[i][0] + 1, l[i][1], r[i][0]);
            T.change(1, 1, n, l[i][1] + 1, n, n + 1);
        }
        val[i] = 1LL * n * (n + 1) - T.t[1].sum; // 统计贡献
    }
    LL ans = 0;
    for (int i = 1; i <= N - 5; i++)
        ans += (val[i + 1] - val[i]) * i; // 统计答案
    printf("%lld", ans);
    return 0;
}
```



---

## 作者：tzc_wk (赞：1)

[Codeforces 题目传送门](https://codeforces.com/contest/671/problem/C) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF671C)

安利个人 blog：https://www.cnblogs.com/ET2006/

~~*2800 的 DS，不过还是被我自己想出来了~~

~~u1s1 这个 D1C 比某些 D1D 不知道难到什么地方去了~~

首先碰到这类问题我们肯定考虑枚举什么东西，然后在枚举过程中用个什么东西维护答案，求出其对答案的贡献。此题一个很直观的想法是枚举左端点，但很遗憾此题涉及 gcd，不太好直接维护。故我们换个想法，枚举答案。

我们先预处理出每个数的所有因子——这个显然可以在 $n\ln n$ 的时间内求出。然后从大到小动态地枚举一个指针 $i$。容易注意到的一件事情是如果 $f(l,r)\geq i$，那么 $f(l,r-1)\geq i$。故考虑设 $t_l$ 为以 $l$ 为左端点的区间中，最小的满足 $f(l,r)<i$ 的 $r$。那么显然满足 $f(l,r)\geq i$ 的区间 $[l,r]$ 的个数为 $\sum\limits_{i=1}^n(t_i-i)=\sum\limits_{i=1}^nt_i-\dfrac{n(n-1)}{2}$，而答案又显然可以用差分的思想转化为对于所有 $i$，满足 $f(l,r)\geq i$ 的区间 $[l,r]$ 的个数之和。

考虑当指针 $i$ 从 $i+1$ 变为 $i$ 的时候会对 $t_l$ 造成什么影响。显然只有满足 $a_j$ 为 $i$ 的倍数的位置 $j$ 才有可能对 $t_l$ 造成影响，故考虑将满足 $a_j$ 是 $i$ 的倍数的位置 $j$ 按照下标从小到大排好，假设为 $p_1,p_2,\dots,p_k$，那么有：

- 若 $k=1$，一个数显然不会对 $t_l$ 产生任何影响，故不考虑 $k=1$ 的情况。
- 若 $k>2$，那么：
  - 对于 $l\in [1,x_1]$，$\forall r\in[l,x_{m-1}-1]$，区间 $[l,r]$ 之外都有两个 $i$ 的倍数（$a_{x_{m-1}},a_{x_m}$），故 $t_l\leftarrow\max(t_l,x_{m-1})$
  - 对于 $l\in [x_1+1,x_2]$，$\forall r\in[l,x_{m}-1]$，区间 $[l,r]$ 之外都有两个 $i$ 的倍数（$a_1,a_{x_m}$），故 $t_l\leftarrow\max(t_l,x_{m})$
  - 对于 $l\in [x_2+1,n]$，$\forall r\in[l,n]$，区间 $[l,r]$ 之外都有两个 $i$ 的倍数（$a_1,a_2$），故 $t_l\leftarrow\max(t_l,n+1)$

于是现在我们要实现支持区间取 $\max$，全局求和的数据结构，这个显然是数据结构不太好直接维护的，第一篇题解说要这东西要用到什么吉司机线段树（~~反正我不会就对了~~）。不过我们静下心来好好想想，真的要这么麻烦吗？这个 $t$ 数组就没有什么性质吗？不难发现，如果 $f(l,r)\geq i$，那么 $f(l+1,r)\geq i$。故我们有 $t_l\leq t_{l+1}$。也就是说对于一次将 $t_l,t_{l+1},t_{l+2},\dots,t_r$ 与 $x$ 取 $\max$ 的操作，我们显然可以找到一个断点 $k$ 使得 $t_l,t_{l+1},\dots,t_k$ 均小于 $x$，$t_{k+1},t_{k+2},\dots,t_r$ 均 $\ge x$，故我们只需对 $[l,k]$ 进行**区间赋值**操作，这显然是普通线段树可以维护的。这个 $k$ 可以通过**线段树二分**求出，二分出第一个 $\geq x$ 的位置 $p$ 并与 $r+1$ 取 $\min$，然后将区间 $[l,p-1]$ 赋上 $x$ 即可。

时间复杂度 $nd(a_i)+n\log n$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=2e5;
const int MAX_ITEM=3e6;
int n,a[MAXN+5];vector<int> pos[MAXN+5];
struct chain_list{
	int hd[MAXN+5],v[MAX_ITEM+5],nxt[MAX_ITEM+5],item_n=0;
	void ins(int p,int q){v[++item_n]=q;nxt[item_n]=hd[p];hd[p]=item_n;}
} fac;
void prework(int n){
	for(int i=1;i<=n;i++) for(int j=i;j<=n;j+=i) fac.ins(j,i);
}
struct node{int l,r,tag,mx;ll sum;} s[MAXN*4+5];
void pushup(int k){
	s[k].sum=s[k<<1].sum+s[k<<1|1].sum;
	s[k].mx=max(s[k<<1].mx,s[k<<1|1].mx);
}
void pushdown(int k){
	if(s[k].tag!=0){
		s[k<<1].mx=s[k].tag;s[k<<1].tag=s[k].tag;
		s[k<<1].sum=1ll*(s[k<<1].r-s[k<<1].l+1)*s[k].tag;
		s[k<<1|1].mx=s[k].tag;s[k<<1|1].tag=s[k].tag;
		s[k<<1|1].sum=1ll*(s[k<<1|1].r-s[k<<1|1].l+1)*s[k].tag;
		s[k].tag=0;
	}
}
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;if(l==r){s[k].sum=l;s[k].mx=l;return;}
	int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	pushup(k);
}
void modify(int k,int l,int r,int x){
	if(l<=s[k].l&&s[k].r<=r){
		s[k].tag=x;s[k].mx=x;
		s[k].sum=1ll*(s[k].r-s[k].l+1)*x;return;
	} pushdown(k);int mid=s[k].l+s[k].r>>1;
	if(r<=mid) modify(k<<1,l,r,x);
	else if(l>mid) modify(k<<1|1,l,r,x);
	else modify(k<<1,l,mid,x),modify(k<<1|1,mid+1,r,x);
	pushup(k);
}
int get_first_le(int k,int x){//find the first element >= x
	if(s[k].l==s[k].r) return s[k].l;
	pushdown(k);
	if(s[k<<1|1].mx<x) return s[k].r+1;
	else if(s[k<<1].mx<x) return get_first_le(k<<1|1,x);
	else return get_first_le(k<<1,x);
}
void deal_max(int l,int r,int x){
	if(l>r) return;
	int pos=get_first_le(1,x)-1;
//	printf("%d %d %d %d\n",l,r,x,pos);
	if(pos>r) pos=r;if(pos<l) return;
	modify(1,l,pos,x);
}
int main(){
	scanf("%d",&n);prework(MAXN);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) for(int e=fac.hd[a[i]];e;e=fac.nxt[e])
		pos[fac.v[e]].pb(i);
	build(1,1,n);ll ans=0;
	for(int i=MAXN;i;i--){
		if(pos[i].size()>=2){
			int fst=pos[i][0],fst_se=pos[i][1];
			int lst=pos[i][pos[i].size()-1],lst_se=pos[i][pos[i].size()-2];
			deal_max(1,fst,lst_se);
			deal_max(fst+1,fst_se,lst);
			deal_max(fst_se+1,n,n+1);
		} ans+=s[1].sum-1ll*n*(n+1)/2;
//		printf("%d %lld\n",i,s[1].sum);
	} printf("%lld\n",ans);
	return 0;
}
```



---

