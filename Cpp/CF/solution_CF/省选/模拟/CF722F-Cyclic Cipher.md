# Cyclic Cipher

## 题目描述

You are given $ n $ sequences. Each sequence consists of positive integers, not exceeding $ m $ . All integers in one sequence are distinct, but the same integer may appear in multiple sequences. The length of the $ i $ -th sequence is $ k_{i} $ .

Each second integers in each of the sequences are shifted by one to the left, i.e. integers at positions $ i&gt;1 $ go to positions $ i-1 $ , while the first integers becomes the last.

Each second we take the first integer of each sequence and write it down to a new array. Then, for each value $ x $ from $ 1 $ to $ m $ we compute the longest segment of the array consisting of element $ x $ only.

The above operation is performed for $ 10^{100} $ seconds. For each integer from $ 1 $ to $ m $ find out the longest segment found at this time.

## 样例 #1

### 输入

```
3 4
3 3 4 1
4 1 3 4 2
3 3 1 4
```

### 输出

```
2
1
3
2
```

## 样例 #2

### 输入

```
5 5
2 3 1
4 5 1 3 2
4 2 1 3 5
1 3
2 5 3
```

### 输出

```
3
1
4
0
1
```

## 样例 #3

### 输入

```
4 6
3 4 5 3
2 6 3
2 3 6
3 3 6 5
```

### 输出

```
0
0
2
1
1
2
```

# 题解

## 作者：Kinandra (赞：7)

1. 考虑对每个 $i$ 分别求解. 一个固定的 $i$ 在某个数列中只出现一次, 他出现的时间可以表示成 $kx+b$ 的形式.
2. 考虑用尺取法求答案, 易知 $k1\times x1-k2\times x2=b2-b1$有解$\Leftrightarrow(b1-b2)\equiv 0\pmod {gcd(k1, k2)} $。记录尺取时当前区间每一个 $k$ 对应的 $b$ (当 $k1=k2$时，$b1$ 显然必须等于 $b2$)，加入新的一组 $(k,b)$ 时只需要用 $\mathcal O(maxk)$ 的复杂度来更新区间就好了.

```cpp
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
struct P {
    int i, k, b;
} st[200005];
vector<P> v[200005];

int read();

int gcd(int a, int b) {
    while (b ^= a ^= b ^= a %= b)
        ;
    return a;
}

bool check(int k1, int b1, int k2, int b2) {
    if (k1 == k2) return b1 == b2;
    return (b2 - b1) % gcd(k1, k2) == 0;
}

int main() {
    int n = read(), m = read();
    for (int i = 1; i <= n; ++i) {
        int k = read();
        for (int j = 1; j <= k; ++j) {
            int x = read();
            v[x].push_back((P){i, k, j - 1});
        }
    }
    for (int x = 1; x <= m; ++x) {
        int sz = v[x].size();
        int l = 0, res = 0;
        for (int i = 1; i <= 40; ++i) st[i].k = 0;
        for (int i = 0; i < sz; ++i) {
            if (i && v[x][i].i != v[x][i - 1].i + 1)
                while (l < i) st[v[x][l++].k].k--;
            for (int j = 1; j <= 40; ++j) {
                if (!st[j].k) continue;
                if (!check(j, st[j].b, v[x][i].k, v[x][i].b)) {
                    while (l <= st[j].i) st[v[x][l++].k].k--;
                }
            }
            st[v[x][i].k].k++, st[v[x][i].k].b = v[x][i].b, st[v[x][i].k].i = i;
            res = max(res, i - l + 1);
        }
        printf("%d\n", res);
    }
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}

```


---

## 作者：沉石鱼惊旋 (赞：1)

# 题目翻译

给定 $n$ 个序列，第 $i$ 个序列长度 $k_i$。保证元素都不超过 $m$。每一秒进行一次循环向左移位，问 $10^{100}$ 秒内，对于所有 $1\leq x\leq m$，回答开头最长连续 $x$ 的长度。

$1\leq n,m\leq 10^5$，$1\leq k_i\leq 40$，$1\leq \sum k_i \leq 2\times 10^5$。

# 题目思路

一个序列，开头是 $x$，等价于一个 $t\equiv b\pmod k$ 形式的方程。两个组合在一起就是 $$\begin{cases}t\equiv b_1\pmod {k_1}\\t\equiv b_2\pmod {k_2}\end{cases}$$。

其实等价于 $k_1x_1+b_1=k_2x_2+b_2$ 的方程，$x_1,x_2$ 是否有解。

移项得到 $k_1x_1-k_2x_2=b_2-b_1$，根据裴蜀定理，$ax+by=c$ 形式的方程有解，当且仅当 $\gcd(a,b)\mid c$。那么我们就可以做两个序列的合法性判断了。

考虑双指针对于每个 $l$ 求出最远的 $r$。这里不难发现对于一个固定的 $l$，$r$ 合法则 $r-1$ 一定合法，一个合法连续段的子段是一定合法的。

双指针每次拓展 $r+1$ 的时候，对于 $[l,r]$ 的限制暴力 check。但是这样会导致我们对一些相同的限制重复 check 导致复杂度其实是错误的。我们对相同 $k$ 的去重 $b$ 即可。合法的 $k$ 一共只有 $40$ 个。那么每次 check 至多对于 $40$ 个限制进行 check。

复杂度 $\mathcal O(\sum k_i\times k)$。依据实现可能会多带个 $\log$ 用来去重。

# 完整代码

[CF submission 290168515](https://codeforces.com/contest/722/submission/290168515)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
template <class T>
void write(T x)
{
    static int stk[30];
    if (x < 0)
        putchar('-'), x = -x;
    int top = 0;
    do
    {
        stk[top++] = x % 10, x /= 10;
    } while (x);
    while (top)
        putchar(stk[--top] + '0');
}
template <class T>
void write(T x, char lastChar) { write(x), putchar(lastChar); }
int gcd(int a, int b)
{
    if (!a | !b)
        return a + b;
    int az = __builtin_ctz(a);
    int bz = __builtin_ctz(b);
    int z = min(az, bz);
    a >>= az, b >>= bz;
    while (a ^ b)
    {
        int diff = b - a;
        az = __builtin_ctz(diff);
        b = min(a, b), a = abs(diff) >> az;
    }
    return a << z;
}
template <typename T>
void chkmx(T &x, T y) { x = max(x, y); }
int n, m;
vector<array<int, 3>> vec[100020];
map<int, int> mp;
map<int, array<int, 2>> kb;
set<array<int, 2>> s;
void add(int k, int b)
{
    if (!kb.count(k))
        kb[k] = {b, 1}, s.insert({k, b});
    else
        kb[k][1]++;
}
void del(int k, int b)
{
    kb[k][1]--;
    if (!kb[k][1])
        kb.erase(k), s.erase({k, b});
}
bool check(int x, int l, int r)
{
    if (l <= r - 1 && vec[x][r][0] != vec[x][r - 1][0] + 1)
        return 0;
    auto [t2, k2, b2] = vec[x][r];
    if (kb.count(k2) && kb[k2][0] != b2)
        return 0;
    for (auto [k1, b1] : s)
    {
        if ((b1 - b2) % gcd(k1, k2))
            return 0;
    }
    return 1;
}
int main()
{
    read(n, m);
    for (int i = 1; i <= n; i++)
    {
        int k;
        read(k);
        for (int j = 1; j <= k; j++)
        {
            int x;
            read(x);
            vec[x].push_back({i, k, j});
        }
    }
    for (int x = 1; x <= m; x++)
    {
        if (vec[x].empty())
        {
            write(0, '\n');
            continue;
        }
        mp.clear();
        kb.clear();
        int id = 0;
        for (auto [t, k, b] : vec[x])
        {
            if (mp.count(k))
                continue;
            mp[k] = ++id;
        }
        int ans = 1;
        int l = 0, r = -1;
        s.clear();
        while (l < vec[x].size())
        {
            while (r + 1 < vec[x].size() && check(x, l, r + 1))
                r++, chkmx(ans, r - l + 1), add(vec[x][r][1], vec[x][r][2]);
            del(vec[x][l][1], vec[x][l][2]), l++;
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：MatrixGroup (赞：0)

## 分析

设 $K=\max k$。对于每个数 $x$，取出它所在的序列，找出每个编号连续的序列段，则只需要对每个序列段求出最长的可行子段即可。考虑只需要判断合法性，不需要使用 exCRT，只需要对于每个 $p^\alpha \le K$，判断它的相关条件是否合法就行。这个是容易撤销的，因为只需要记录对于每个 $p^\alpha$，是否确定了余数，如果有，是多少，出现了多少次即可。精细实现的话，因为满足 $p^\alpha|k$ 的 $p^\alpha$ 不超过 $\log_2 k$ 个，时间复杂度 $O(n+m+\sum (k\log k))$。

## 代码

```cpp
#include <bits/stdc++.h>
#define rep(i,n) for(int i=0,del##i##verme=int(n);i<del##i##verme;++i)
#define rep1(i,n) for(int i=1,parano##i##a=int(n);i<=parano##i##a;++i)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
const int p[19]={2,3,4,5,7,8,9,11,13,16,17,19,23,25,27,29,31,32,37};
vector<int> d[45];
int n,m,k,x;
int mod[200005];
int res[200005];
int lst,c;
vector<pair<int,pair<int,int> > > occ[200005];
int ans;
vector<pair<int,int> > qt[200005];
int lit[22],cnt[22];
bool chk(int r)
{
	for(pair<int,int> P:qt[r]) if(lit[P.fi]!=P.se&&cnt[P.fi]) return false;
	return true;
}
void delt(int r)
{
	for(pair<int,int> P:qt[r]) --cnt[P.fi];
}
void inct(int r)
{
	for(pair<int,int> P:qt[r])
	{
		lit[P.fi]=P.se;
		++cnt[P.fi]; 
	}
}
void solve()
{
	rep1(i,c)
	{
		qt[i].clear();
		for(int y:d[mod[i]]) qt[i].pb(mp(y,res[i]%p[y]));
	}
	int l=1;
	rep1(i,c)
	{
		while(!chk(i))
		{
			delt(l++);
		}
		inct(i);
		ans=max(ans,i-l+1);
	}
	while(l<=c)delt(l++); 
}
int main()
{
	ios_base::sync_with_stdio(false);cin.tie(0);
	cin>>n>>m;
	rep1(i,n)
	{
		cin>>k;
		rep(j,k)
		{
			cin>>x;occ[x].pb(mp(i,mp(k,j)));
		}
	}
	rep(j,19) for(int i=p[j];i<=40;i+=p[j]) d[i].pb(j);
	rep1(i,m)
	{
		ans=0;
		if(!occ[i].empty())
		{
			lst=-1;c=0;
			for(pair<int,pair<int,int> > P:occ[i])
			{
				if(lst!=P.fi-1)
				{
					solve();c=0;
				}
				mod[++c]=P.se.fi;res[c]=P.se.se;
				lst=P.fi;
			}
			solve();
		}
		cout<<ans<<"\n"; 
	}
	return 0;
}
```

---

## 作者：orz_z (赞：0)



对于每个权值找出他出现的极长区间，总数是 $\mathcal O(40n)$ 的。

然后我们判断一个区间是否有解，每个限制形如一个同余式，发现模数 $\leq 40$，那么两两判断裴蜀定理即可。

考虑双指针，找到最长合法区间，对每个模数记录出现位置及余数，这很好做。

---

## 作者：SunsetSamsara (赞：0)

## CF722F

### 题意

给定 $n$ 个数列，第 $i$ 个数列包含 $k_i$ 个不超过 $m$ 的互不相同的正整数（从 $1$ 开始标号）。

每一秒将每个数列中的数左移一个位置（即将每个数的下标 $-1$，下标 $1$ 的数下标变为 $k_i$），并记录由每个数列的第一个数组成的序列。

足够长时间后，对于所有的 $1\le x\le m$，求 $x$ 在记录下来的序列中出现的最长的连续的一段长度。

### 标签

思维，数论，双指针

### 做法

对于每一个 $x$，设其在长度为 $k$ 的序列中的第 $p$ 个位置，则它在时刻 $t$ 出现在第一个位置的条件是 $t \equiv p \pmod k$。联立起来，就把这个问题转化为了最长连续有解的同余方程组。

发现 $k \le 40$，所以最多有 $40$ 个模数。对于每一个模数都记录模数为这个值的同余方程。显然，如果一个模数对应了两个不同的余数，那么这个同余方程组无解。又由裴蜀定理知，$x \equiv p_1 \pmod{k_1}$ 且 $x \equiv p_2\pmod{k_2}$ 且 $k_1 \neq k_2$ 有解的充要条件是 $\gcd(k_1, k_2) | p_1 - p_2$。于是这样就求出了同余方程组有解的充要条件。

考虑对于所有的 $x \le m$ 都单独求出结果。

记录每个值出现的位置，记序列 $a$，$b$ 分别表示第几个序列与第几个数。

考虑双指针。

对于每个 $r$，记录以在原序列中 $a_r$ 为右端点的最长有解同余方程组的左端点 $L$。显然，$L$ 在序列 $a$ 中，记 $L = a_l$。

当 $r$ 增加时，先要判断 $a_r$ 是否是 $a_{r - 1} + 1$。

接下来不断增加 $l$ 直到满足一个模数只能对应一个余数的条件。

最后，发现只有 $40$ 个方程，于是直接对于每一个方程判断是否能与 $a_r$ 对应的方程组相容，不能则将 $l$ 右移直到相容为止。

最终的复杂度是 $O(nk^2)$。

### 代码

```cpp
#pragma GCC optimize("Ofast")
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <set>
typedef long long lld;
using namespace std;
const int N = 100010;
const int M = 50;
inline lld qpow(lld a, lld b, lld p) {
	a %= p;
	lld ret = 1;
	for (; b; b >>= 1, a = a * a % p)
		if (b & 1) ret = ret * a % p;
	return ret;
}
int n, s;
vector<pair<int, int> > pos[N];
int m[N];
int cnt[M];
int a[M];
int _gcd[M][M];
int main() {
//	freopen("sample3.in", "r", stdin);
//	freopen("sample3.ans", "w", stdout);
	scanf("%d%d", &n, &s);
	for (int i = 1; i <= n; ++ i) {
		scanf("%d", m + i);
		for (int x, j = 1; j <= m[i]; ++ j) {
			scanf("%d", &x);
			pos[x].push_back(make_pair(i, j));
		}
	}
	for (int v = 1; v <= s; ++ v) {
//		printf("v = %d\n", v);
		memset(cnt, 0, sizeof(cnt));
		memset(a, 0, sizeof(a));
		register int ans = 0;
		for (register int l = 0, r = 0; r < pos[v].size(); ++ r) {
			int mr = m[pos[v][r].first], ar = pos[v][r].second;
			if (r && pos[v][r].first != pos[v][r - 1].first + 1)
				for (; l < r; -- cnt[m[pos[v][l].first]], ++ l);
//			printf("%d %d\n", l, r);
			if (cnt[mr] && a[mr] != ar)
				for (; l < r && cnt[mr]; -- cnt[m[pos[v][l].first]], ++ l);
//			printf("%d %d\n", l, r);
			if ((++ cnt[mr]) == 1) {
				a[mr] = ar;
				for (int k = 1; k <= 40; ++ k)
					if (cnt[k] && abs(ar - a[k]) % __gcd(mr, k))
						for (; l < r && cnt[k]; -- cnt[m[pos[v][l].first]], ++ l);
			}
//			printf("%d %d\n", l, r);
			ans = max(ans, r - l + 1);
		}
		printf("%d\n", ans);
	}
}

```

---

## 作者：Albert_van (赞：0)

首先将每个数下标 $-1$。那么记 $x$ 在第 $i$ 个数列中下标为 $p_{x,i}$，$x$ 的答案即为最长段 $[l,r]$，满足关于 $t$ 的同余方程组

$$\begin{cases}X_l:t\equiv p_{x,l}\pmod {k_l}\\\cdots\\X_r:t\equiv p_{x,r}\pmod {k_r}\end{cases}$$

有解。这个东西显然是单调的，对于确定的 $l$，若 $[l,r_0]$ 合法，那么 $[l,r]:r<r_0$ 也合法。根据 exCRT，同余方程这个东西是可合并的，考虑倍增。

具体地，用 $(p,k)$ 刻画形如 $t\equiv p\pmod k$ 的同余方程。预处理 $f_{i,k}$ 表示将 $X_i$ 到 $X_{i+2^k-1}$ 这 $2^k$ 个同余方程合并后的结果，若无解则记 $k=-1$。对于每个 $l$，从大到小枚举 $k$，尝试将当前的方程和 $f_{l+1,k}$ 合并，若有解则令 $l\gets l+2^k$，最终的 $l$ 即为最大的合法右端点。

同余方程合并和判断无解的操作见 [exCRT](https://www.luogu.com.cn/problem/P4777)。$\operatorname{lcm}(1,2,\cdots,40)<10^{18}$ 给了我们模拟上述操作的可能。查询时，对于所问数字在原序列出现的每个连续段，分别实现上面的过程即可。

时间复杂度 $\Theta(nm\log n),m=\max\{k_i\}$，理论优于 std。但是在某 OJ 上会被卡常。

[RECORD](https://codeforces.com/contest/722/submission/229961190)

---

