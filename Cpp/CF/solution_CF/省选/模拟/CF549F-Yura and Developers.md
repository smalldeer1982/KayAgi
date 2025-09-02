# Yura and Developers

## 题目描述

Yura has a team of $ k $ developers and a list of $ n $ tasks numbered from $ 1 $ to $ n $ . Yura is going to choose some tasks to be done this week. Due to strange Looksery habits the numbers of chosen tasks should be a segment of consecutive integers containing no less than 2 numbers, i. e. a sequence of form $ l,l+1,...,r $ for some $ 1<=l&lt;r<=n $ .

Every task $ i $ has an integer number $ a_{i} $ associated with it denoting how many man-hours are required to complete the $ i $ -th task. Developers are not self-confident at all, and they are actually afraid of difficult tasks. Knowing that, Yura decided to pick up a hardest task (the one that takes the biggest number of man-hours to be completed, among several hardest tasks with same difficulty level he chooses arbitrary one) and complete it on his own. So, if tasks with numbers $ [l,r] $ are chosen then the developers are left with $ r-l $ tasks to be done by themselves.

Every developer can spend any integer amount of hours over any task, but when they are done with the whole assignment there should be exactly $ a_{i} $ man-hours spent over the $ i $ -th task.

The last, but not the least problem with developers is that one gets angry if he works more than another developer. A set of tasks $ [l,r] $ is considered good if it is possible to find such a distribution of work that allows to complete all the tasks and to have every developer working for the same amount of time (amount of work performed by Yura doesn't matter for other workers as well as for him).

For example, let's suppose that Yura have chosen tasks with following difficulties: $ a=[1,2,3,4] $ , and he has three developers in his disposal. He takes the hardest fourth task to finish by himself, and the developers are left with tasks with difficulties $ [1,2,3] $ . If the first one spends an hour on the first task and an hour on the third one, the second developer spends two hours on the second task and the third developer spends two hours on the third task, then they are done, since every developer worked exactly for two hours and every task has been worked over for the required amount of time. As another example, if the first task required two hours instead of one to be completed then it would be impossible to assign the tasks in a way described above.

Besides work, Yura is fond of problem solving. He wonders how many pairs $ (l,r) $ ( $ 1<=l&lt;r<=n $ ) exists such that a segment $ [l,r] $ is good? Yura has already solved this problem, but he has no time to write the code. Please, help Yura and implement the solution for this problem.

## 说明/提示

In the first sample there are three good segments:

1. $ [1;3] $ — the hardest task requires $ 3 $ man-hours, so there are tasks left that require $ 1 $ and $ 2 $ man-hours. A solution is to make first developer work on the first task for an hour, while second and third developers work on the second task. Each developer works exactly one hour.
2. $ [1;4] $ — the hardest task requires $ 4 $ man-hours, so there are tasks left that require $ 1 $ , $ 2 $ and $ 3 $ man-hours. If the first developer spends an hour on the first task and an hour on the third one, the second developer spends two hours on the second task and the third developer spends two hours on the third task, then they are done, since every developer worked exactly for two hours.
3. $ [3;4] $ — the hardest task requires $ 4 $ man-hours, so there is only one task left that requires $ 3 $ man-hours. A solution is to make each developer work for an hour.

## 样例 #1

### 输入

```
4 3
1 2 3 4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 2
4 4 7 4
```

### 输出

```
6
```

# 题解

## 作者：ningago (赞：5)

单 $\log$ 简单分治题解。

考虑处理区间 $[l,r]$ 的答案，钦定左端点 $\leq mid$，右端点 $>mid$，其他情况分治。

首先规定相等的数之间的大小关系，规定标号小的大于编号大的。

对于每个 $i\leq mid$，计算**以 $i$ 为左端点，区间最大值在左侧**的所有右端点的答案，此时右端点的取值为一个区间。不难用双指针维护出区间。记作 $(mid,R_i]$。

利用前缀和，此时即求 $r\in (mid,R_i],pre_r-pre_i-mx\equiv 0\pmod K$ 的个数，即 $pre_r\equiv pre_i+mx\pmod K$。

由于模数很小，直接存即可。

右端点同理，计算**以 $i$ 为右端点，区间最大值在右侧**的所有左端点的答案即可。

复杂度 $O(n\log n)$，十分优美。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctype.h>
#include <cmath>
#include <vector>
#include <queue>
#include <numeric>

char ST;
#define int long long
//#define ll long long
//#define inf 0x3f3f3f3f
#define inf 0x3f3f3f3f3f3f3f3f
int read()
{
	int x = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(;  isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	return x * f;
}

int readstr(char *str)
{
	int len = 0;
	char c = getchar();
	for(; !isalpha(c) && !isdigit(c) && c != '.' && c != '*' && c != '#'; c = getchar());
	for(;  isalpha(c) ||  isdigit(c) || c == '.' || c == '*' || c == '#'; c = getchar()) str[++len] = c;
	return len;
}

#define debug(...) fprintf(stderr, __VA_ARGS__)
#define gline debug("now is #%d\n", __LINE__)
#define pii std::pair <int, int>
#define mkp std::make_pair
#define fi first
#define se second

void ckmax(int &x, int y) { x = x > y ? x : y; }
void ckmin(int &x, int y) { x = x < y ? x : y; }
//#define mod 998244353
#define mod 1000000007
void plus_(int &x, int y) { x = x + y >= mod ? x + y - mod : x + y; }
void mul_(int &x, int y) { x = 1ll * x * y % mod; }
int ksm(int a, int b)
{
	int res = 1;
	for(; b; b >>= 1, mul_(a, a)) if(b & 1) mul_(res, a);
	return res;
}

#define N 300010
int n, m, a[N];
int pre[N], ans;
int cnt[1000100];

void solve(int l, int r)
{
	if(l == r)
		return;
	int mid = (l + r) >> 1;
	solve(l, mid), solve(mid + 1, r);
	int idx = mid, mx = 0;
	for(int i = mid; i >= l; i--)
	{
		mx = std::max(mx, a[i]);
		while(idx != r && a[idx + 1] <= mx)
		{
			idx++;
			cnt[pre[idx] % m]++;
		}
		ans += cnt[(pre[i - 1] + mx) % m];
	}
	for(int i = mid + 1; i <= r; i++) cnt[pre[i] % m] = 0;
	idx = mid + 1, mx = 0;
	for(int i = mid + 1; i <= r; i++)
	{
		mx = std::max(mx, a[i]);
		while(idx != l && a[idx - 1] < mx)
		{
			idx--;
			cnt[pre[idx - 1] % m]++;
		}
		ans += cnt[((pre[i] - mx) % m + m) % m];
	}
	for(int i = l; i <= mid; i++) cnt[pre[i - 1] % m] = 0;
}

char ED;
signed main()
{
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read(), pre[i] = pre[i - 1] + a[i];
	solve(1, n);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：SilverLi (赞：4)

> [Yura and Developers の 传送门](https://www.luogu.com.cn/problem/CF549F)
>
> [点一点](https://www.cnblogs.com/Silver-Wolf/p/18690056/CF549F)

### 题外话

怎么没人直接强上笛卡尔树分治。

### 正文

看到**最大值**，想一想笛卡尔树分治。

令当前区间为 $\left [ l, r \right ]$，区间最大值及位置为 $mx, k$。

假设 $\left [ l, k \right ]$ 为短边（另一段为短边时也差不太多）。

满足条件的子段长成 $sum_i-sum_{j-1}-mx \equiv 0 \left ( \bmod \ k \right )$。

移一移项，得 $sum_i \equiv sum_{j-1}+mx \left ( \bmod \ k \right )$。

开个 `map` 把右边的 $sum_i$ 存下来，暴力算左边每个数的贡献就行。

### 啸细节

存每个长边 $sum_i$ 的 `map` 可以直接一层层传下去，不要重新统计。

`map` 换成 `__gnu_pbds::gp_hash_table`（详见[这里](https://www.luogu.com.cn/article/tk8rh0c9)）。

### 代码

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define int long long
using namespace std;
inline int read()
{
    int f = 0, ans = 0;
    char c = getchar();
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        ans = (ans << 3) + (ans << 1) + c - 48, c = getchar();
    return f ? -ans : ans;
}
void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
const int N = 3e5 + 5;
int n, _K, a[N];
int ans, s[N];
__gnu_pbds::gp_hash_table<int, int> mp;
template <typename T>
inline T Mod(T &&x) { return x >= _K ? x -= _K : x; }
namespace ST
{
    pair<int, int> f[19][N];
    inline void init()
    {
        for (int i = 1; i <= n; ++i)
            f[0][i] = {a[i], i};
        for (int j = 1; j <= __lg(n); ++j)
            for (int i = 1; i + (1 << j) - 1 <= n; ++i)
                f[j][i] = max(f[j - 1][i], f[j - 1][i + (1 << j - 1)]);
    }
    inline pair<int, int> get_max(int l, int r)
    {
        int lg = __lg(r - l + 1);
        return max(f[lg][l], f[lg][r - (1 << lg) + 1]);
    }
}
void solve(int l, int r, int d)
{
    if (l >= r)
    {
        ans += l == r;
        return;
    }
    auto [mx, k] = ST::get_max(l, r);
    mx %= _K;
    if (k - l <= r - k)
    {
        for (int i = l; i < k; ++i)
            --mp[s[i]];
        for (int i = l; i <= k; ++i)
            ans += mp[Mod(s[i - 1] + mx)];
        --mp[s[k]];
        solve(k + 1, r, d + 1);
        mp.clear();
        for (int i = l; i < k; ++i)
            ++mp[s[i]];
        solve(l, k - 1, d + 1);
    }
    else
    {
        for (int i = k + 1; i <= r; ++i)
            --mp[s[i]];
        ++mp[s[l - 1]], --mp[s[k]];
        for (int i = k; i <= r; ++i)
            ans += mp[Mod(s[i] - mx + _K)];
        --mp[s[l - 1]];
        solve(l, k - 1, d + 1);
        mp.clear();
        for (int i = k + 1; i <= r; ++i)
            ++mp[s[i]];
        solve(k + 1, r, d + 1);
    }
}
signed main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    n = read(), _K = read();
    for (int i = 1; i <= n; ++i)
    {
        Mod(s[i] = s[i - 1] + (a[i] = read()) % _K);
        ++mp[s[i]];
    }
    ST::init();
    solve(1, n, 0);
    write(ans - n);
    return 0;
}
```

---

## 作者：hzjnsy (赞：4)

**[CNBLOGS](https://www.cnblogs.com/MnZnOIerLzy/articles/17723990.html)**

这不今年完善程序 T2 吗？

**[CF](https://codeforces.com/problemset/problem/549/F "CF")** **[洛谷](https://www.luogu.com.cn/problem/CF549F "洛谷")**

> - 给定数组 $a_1\sim a_n$ 和常数 $k$，求有多少个区间 $[l,r]$，满足:
>
>     - $r-l+1\ge 2$。
>
>     - $\left(\sum\limits_{i=l}^r a_i-\max\limits_{i=l}^r a_i\right)\bmod k=0$。
>
> - $n\le 3\times 10^5$，$k\le 10^6$。

考虑分治。设当前分治区间左端点为 $l$，右端点为 $r$，中点为 $mid$，考虑如何计算跨过中点的贡献。

首先对于右半区间，维护 $pre_p=\max\limits_{u=mid+1}^p a_u$，$sum_p=\left(\sum\limits_{v=mid+1}^pa_v\right)\bmod k$，$dif_p=(sum_p-pre_p)\bmod k$，即以 $mid+1$ 为起点的前缀最大值、模 $k$ 意义下的前缀和以及它们的差对 $k$ 取模的值。

从右往左扫描跨过中点的区间的左端点 $i$，记 $suf=\max\limits_{v=i}^{mid}a_v$，$s=\left(\sum\limits_{u=i}^{mid} a_u\right)\bmod k$，我们要找到一个位置 $j$，使得：

$$\max\limits_{u=mid+1}^{j-1} a_u\le suf\, \land \,\forall \,w\in[j,r],\max\limits_{u=mid+1}^w a_u> suf$$

说白了就是右端点取在 $j$ 及其左边区间最大值位于 $mid$ 及其左边，右端点取在 $j$ 右边区间最大值位于 $mid$ 右边。不难发现**随着 $\boldsymbol i$ 递减，$\boldsymbol j$ 不降**。

分别计算以 $j$ 为界的两部分的贡献，对于 $j$ 及其左边，要找到这样的右端点 $x$，使得 $(s+sum_x-suf)\bmod k=0$，移项得 $sum_x=(k-s+suf)\bmod k$；对于 $j$ 右边，要找到这样的右端点 $y$，使得 $(s+dif_y)\bmod k=0$，移项得 $dif_y=(k-s)\bmod k$。

问题变成求 $(mid,j)$ 中有多少 $sum$ 值为 $(k-s+suf)\bmod k$，$[j,r]$ 中有多少 $dif$ 值为 $(k-s)\bmod k$，主席树维护即可，然后[被卡了](https://codeforces.com/problemset/submission/549/224617481)。

两只 $\log$ 跑不快啊 /fn！

然后你发现主席树的可持久化是没有意义的，因为 $j$ 不降，因此一个版本不会被再次使用。

考虑维护 $b_1,b_2$ 两个桶，分别表示扫到当前的 $j$ 时 $[j,r]$ 中 $dif$ 在每种值各出现了几次和 $(mid,j)$ 中 $sum$ 在每种值各出现了几次。$j$ 增加到 $j+1$ 时，相当于 $(mid,j)$ 比原来多包含了一个 $j$ 位置，将 $b_{2_{sum_{j}}}$ 增加 $1$；$[j,r]$ 比原来少包含了一个 $j$ 位置，将 $b_{1_{dif_{j}}}$ 减去 $1$。

这么一来，左端点 $i$ 的贡献为 $b_{2_{(k-s+suf)\bmod k}}+b_{1_{(k-s)\bmod k}}$，注意边界、负数取模以及清空（有人又没清空，我不说是谁）。

时间复杂度为 $\mathcal{O}(n\log n)$，空间复杂度为 $\mathcal{O}(n+k)$。

**[提交记录](https://codeforces.com/problemset/submission/549/224686074)**

```cpp
#include <bits/stdc++.h>
#define ll long long // 防见祖宗。
using namespace std; const int N = 3e5 + 5, V = 1e6; 
int n, k, a[N], pre[N], sum[N], b1[V], b2[V]; // 代码里 dif 数组就直接用 pre  和 sum 表示了。
template<class T> void read(T &x) {
    x = 0; T f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - 48; x *= f;
}
template<class T> void write(T x) {
    if (x > 9) write(x / 10); putchar(x % 10 + 48);
}
template<class T> void print(T x, char ed = '\n') {
    if (x < 0) putchar('-'), x = -x; write(x), putchar(ed);
}
ll solve(int l, int r) {
    if (l == r) return 0; int md = (l + r) >> 1; 
    ll ret = solve(l, md) + solve(md + 1, r); pre[md] = sum[md] = 0;
    for (int i = md + 1; i <= r; ++i) 
        pre[i] = max(pre[i - 1], a[i]), sum[i] = (sum[i - 1] + a[i]) % k;
    for (int i = r; i > md; --i) ++b1[(sum[i] - pre[i] % k + k) % k];
    for (int i = md, suf = 0, s = 0, j = md + 1, pos; i >= l; --i) {
        suf = max(suf, a[i]); s = (s + a[i]) % k; 
        for (; j <= r && pre[j] <= suf; ++j)
            --b1[(sum[j] - pre[j] % k + k) % k], ++b2[sum[j]];
        if (j > md + 1) ret += b2[(k - s + suf) % k];
        if (j <= r) ret += b1[(k - s) % k]; 
    }
    for (int i = r; i > md; --i) // 清空。
        b1[(sum[i] - pre[i] % k + k) % k] = b2[sum[i]] = 0;
    return ret;
}
signed main() {
    read(n), read(k); for (int i = 1; i <= n; ++i) read(a[i]);
    return print(solve(1, n)), 0;
}
```



---

## 作者：Jsxts_ (赞：4)

这道题的做法很套路，枚举最大值之后处理出它是最大值的区间，再枚举短的区间，之后问题就变成了区间中模 $k$ 余 $x$ 的数有多少，并且 $k$ 是固定的。这就相当于问区间中 $x$ 的出现次数，用 vector 加二分或扫描线或者其他做法都行。

这里主要证明一下枚举短区间为什么复杂度是对的。

我们对这个序列建出笛卡尔树，之后发现每个数的最大值区间就是它的子树，左儿子是左边，右儿子是右边区间。那么，枚举短区间的复杂度就是

$$\sum_{u}\min(size_{ls_u},size_{rs_u})$$

对笛卡尔树做重链剖分，有个结论是轻子树的总大小是 $O(n\log n)$ 的，所以枚举短区间的复杂度就是 $O(n\log n)$ 的。

如果用 vector 加二分复杂度是两个 $\log$ 的，扫描线就是一个。

代码（最优解）：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 1e9;
inline int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
int n,k,L[300010],R[300010];
ll ans;
int a[300010],pre[300010];
vector<int> vc[1000010];
int query(int x,int l,int r) {
	return lower_bound(vc[x].begin(),vc[x].end(),r) - lower_bound(vc[x].begin(),vc[x].end(),l);
}
int main() {
	n = read(), k = read();
	for (int i = 1;i <= n;i ++ ) a[i] = read();
	L[1] = 1, R[n] = n;
	for (int i = 2;i <= n;i ++ ) {
		if (a[i] >= a[i-1]) {
			int t = i;
			while (t > 1 && a[t-1] < a[i]) t = L[t-1];
			L[i] = t;
		}
		else L[i] = i;
	}
	for (int i = n - 1;i;i -- ) {
		if (a[i] >= a[i+1]) {
			int t = i;
			while (t < n && a[t+1] <= a[i]) t = R[t+1];
			R[i] = t;
		}
		else R[i] = i;
	}//奇怪的处理最值区间方法，用单调栈就好了
//	for (int i = 1;i <= n;i ++ ) cout << L[i] << ' ' << R[i] << endl; 
	for (int i = 1;i <= n;i ++ ) pre[i] = (a[i] + pre[i-1]) % k;
	for (int i = 0;i <= n;i ++ ) vc[pre[i]].push_back(i);
	ans = 0;
	for (int i = 1;i <= n;i ++ ) {
		if (i - L[i] > R[i] - i) {//短区间
			for (int j = i;j <= R[i];j ++ ) {
				int x = ((pre[j] - a[i]) % k + k) % k;
				ans += query(x,L[i]-1,i);
			}
		}
		else {
			for (int j = L[i];j <= i;j ++ ) {
				int x = (pre[j-1] + a[i]) % k;
				ans += query(x,i,R[i]+1);
			}
		}
	}
	cout << ans - n;//减n是因为区间长度至少是2，算多了
	return 0;
}
```


---

## 作者：Limit (赞：2)

# 题目大意

给出一个序列,问又多少子串的和($sum$)减去最大值($max$)除 $k$ 后的余数等于 $0$($(sum-max)\bmod k=0$).

# 分析

可以先用单调栈处理出每个位置为最大值的区间,那么可以计算出前缀和之后在这个最大值的两边各枚举一下这个子串的起点和终点,利用前缀和可以做到 $\mathcal{O}(1)$ 判断这个子串是否合法.当然,如果只枚举一边,另外一边可以用一些奇怪的数据结构等东西维护一下前缀和对 $k$ 取模后的结果也是可以的.但一个点到这个点为最大值的区间两边的距离最大是可以到 $n$ 级别的,直接枚举的复杂度就是 $\mathcal{O}(n^2)$ 了,显然不行.但如果是枚举较短的一边呢?发现居然是可以过的!!!

现在来非常不科学得证明一下(因为对于上面这个问题是可以转化为每个数都不同的,所以下面考虑的序列是一个排列):

显然可以写出如下 $\operatorname{dp}$($f_i$ 表示长度为 $i$ 的序列通过以上方法枚举的最多枚举次数)

```cpp
f[0]=0;
f[1]=1;
f[2]=1;
REP(i,3,n)
{
    //一个长度为 i 的排列有一个唯一的最大值,并且对于除这个最大值对应的区间以外,其他数的区间是不可能经过这个位置的,所以可以枚举这个最大值出现的位置,那么就变成了两个长度较短的排列,可以直接使用前面计算出来的 dp 值
	REP(j,0,i-1)
	{
		f[i]=max(f[i],f[j]+f[i-1-j]+min(j,i-1-j));
	}
}
```

在 $n=10000$ 时,通过以上代码计算出来的 $f_n=59613$,在 $n=100000$ 时,通过以上代码计算出来的 $f_n=765030$,在 $n=300000$ 时,通过以上代码计算出来的 $f_n=2528456$,据此,我们可以大胆猜测这个 $f_i$ 是 $n\log_2n$ 级别,且在 $n$ 较大时(此题数据范围)比 $n\log_2n$ 小很多.

当然,通过这个代码也不难看出 $f_i$ 的转移显然是从中间断开时最大(类似快速排序等分治算法)且每一层的距离的和是 $n$ 级别,妹子区间的长度都会初二,所以层数是 $log_2n$ 级别(因为中间为最大值的数不可以被计算到距离里,所以最终能计算结果与小于 $n\log_2n$).

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
namespace IO
//快读模板
using namespace IO;
using namespace std;
const int MAXN=3e5+20;
int n,k;
struct Number
{
	int num,l,r,sum;
}arr[MAXN];
int st[MAXN],top=0;
int root_[MAXN];
int *root=root_+10;
namespace SGT//因为闲得无聊就直接用可持久化线段树维护区间前缀和模 k 后的结果个数了(可以用 vector+二分来维护)
{
	struct SegmentTree
	{
		int sum,lson,rson;
	}sgt[MAXN<<6];
	int sgt_cnt=0;
	#define LSON sgt[now].lson
	#define RSON sgt[now].rson
	#define MIDDLE ((left+right)>>1)
	#define LEFT LSON,left,MIDDLE
	#define RIGHT RSON,MIDDLE+1,right
	#define NEW_LSON sgt[new_tree].lson
	#define NEW_RSON sgt[new_tree].rson
	void Updata(int place,int &new_tree,int now,int left=0,int right=k)
	{
		if(place<left||right<place)
		{
			new_tree=now;
			return;
		}
		new_tree=++sgt_cnt;
		if(left==right)
		{
			sgt[new_tree].sum=sgt[now].sum+1;
			return;
		}
		Updata(place,NEW_LSON,LEFT);
		Updata(place,NEW_RSON,RIGHT);
	}
	int Query(int place,int cut,int now,int left=0,int right=k)
	{
		if(place<left||right<place)
		{
			return 0;
		}
		if(left==right)
		{
			return sgt[now].sum-sgt[cut].sum;
		}
		return Query(place,sgt[cut].lson,LEFT)+Query(place,sgt[cut].rson,RIGHT);
	}
}
int main()
{
	Read(n,k);
	SGT::Updata(0,root[0],root[-1]);
	int sum=0;
	REP(i,1,n)//单调栈处理出每个数为最大值的区间
	{
		Read(arr[i].num);
		arr[i].sum=(arr[i-1].sum+arr[i].num)%k;
		SGT::Updata(arr[i].sum,root[i],root[i-1]);
		while(top&&arr[st[top]].num<arr[i].num)
		{
			top--;
		}
		arr[i].l=st[top]+1;
		st[++top]=i;
	}
	top=0;
	DOW(i,n,1)
	{
		while(top&&arr[st[top]].num<=arr[i].num)
		{
			top--;
		}
		arr[i].r=st[top]?st[top]-1:n;
		st[++top]=i;
	}
	long long answer=-n;
	REP(i,1,n)
	{
		if(i-arr[i].l<arr[i].r-i)//枚举较短的一边
		{
			REP(j,arr[i].l,i)
			{
				answer+=SGT::Query((arr[j-1].sum+arr[i].num)%k/*需要用到的前缀和的数值可以通过简单计算得出,这里不展开*/,root[i-1],root[arr[i].r]);
			}
		}
		else//下面同理
		{
			REP(j,i,arr[i].r)
			{
				answer+=SGT::Query((arr[j].sum-arr[i].num%k+k)%k,root[arr[i].l-2],root[i-1]);
			}
		}
	}
	Writeln(answer);
	return 0;
}
```

---

## 作者：AC_Lover (赞：1)

### 简要题面：

给定长度为 $n$ 的序列 $a$，以及 $k$，求满足

$$
\left(\sum_{i=l}^{r}a_i\right)-\left(\max_{i=l}^{r}a_i\right)\equiv 0 \pmod k
$$

的 $(l,r)$ 的个数。

### 正解：

看到和最大最小值有关的，求子段个数问题时，考虑使用最大/最小值分治（其实就是笛卡尔树上分治）。

原式中的区间最大值不好处理，考虑固定住。

定义 $\mathrm{solve}(l,r)$ 表示分治求解子区间 $[l,r]$ 中的答案，然后我们找到 $\max_{i=l}^{r}a_i$ 的位置，记为 $p$，这个可以用 $\mathrm{ST}$ 表简单解决，那么我们发现，所有横跨了 $p$ 的区间 $[L,R]$ 中  $\max_{i=L}^{R}a_i$ 的值就是 $a_p$，于是对于横跨了 $p$ 的区间，即满足 $l\le L \le p\le R \le r$ 的区间 $[L,R]$，相当于要满足

$$
\left(\sum_{i=L}^{R}a_i\right)-a_p\equiv 0 \pmod k
$$

将区间和用前缀和表示出来，记$sum$表示$a$的前缀和数组，于是

$$
sum_{R}-sum_{L-1}+a_p\equiv 0\pmod k \\
$$

我们考虑固定住一端，注意此时为了使得复杂度不会退化，我们选择长度短的一端作为固定的点，于是分讨一下。

① $p-l\le r-p$，此时选择左端点固定更优。

于是我们枚举这个子区间 $[L,R]$ 的左端点 $L$，相当于要找到满足条件的 $R$ 的个数

还是看一下原来的柿子，发现其中的 $sum_{L-1},a_p$ 都是定值，稍微推一下，发现

$$
sum_{R}-sum_{L-1}+a_p \equiv 0\pmod k \\
sum_{R}\equiv sum_{L-1}-a_p \pmod k
$$

那么相当于要找到右边满足 $sum_{R}\bmod k=(sum_{L-1}-a_p)\bmod k$ 的 $R$ 的个数。

② $r-p\le p-l$，此时选择右端点固定更优

同理，固定右端点 $R$，发现 $sum_R,a_p$ 是固定的，于是

$$
sum_{R}-sum_{L-1}+a_p \equiv 0\pmod k \\
sum_{L-1}\equiv sum_{R}+a_p \pmod k
$$

相当于要找到满足 $sum_{L-1}\bmod k=(sum_{R}+a_p)\bmod k$ 的 $L$ 的个数。

综上，我们发现核心问题就是要快速求出一个区间中有多少个 $sum$ 取模于 $k$ 等于一个数。

一个很简单并且常数小的做法就是开 $k$ 个 $\texttt{vector}$，第 $i$ 个存储 $sum$ 取模于 $k$ 等于 $i$ 的下标，由于从前往后扫着加入，所以下标是递增的，然后假设要求出 $[l,r]$ 中满足 $sum$ 取模与 $k$ 余数是 $R$ 的个数，根据经典结论，在有序序列中找数在 $[x,y]$ 中的数的个数，可以用二分，表示为

`upper_bound(...,y)-lower_bound(...,x)`

于是直接在存储余数为 $R$ 的 $\texttt{vector}$ 中二分即可。

然后我们就可以求出跨过 $p$ 的子区间的个数了，注意计算时会计算到子区间 $[p,p]$，而这个区间长度小于2，不应该计算，所以计算结果减1。

至此就解决了 $\mathrm{solve}(l,r)$，那么接下来分治求解 $\mathrm{solve}(l,p-1),\mathrm{solve}(p+1,r)$ 即可。

计算一下复杂度，对于计算跨过 $p$ 的区间，复杂度是  $O(\min(p-l+1,r-p+1)\times \log n)$，发现由于我们只取较小长度的一部分，$\min(p-l+1,r-p+1)\le \frac{n}{2}$，所以最终复杂度是 $O(n\log^2 n)$。

代码：

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

//#include <cassert>

using namespace std;

const int N=300010,T=20,K=1000010;
typedef long long ll;
int n,k;
int a[N];
ll sum[N];
int lg[N],f[N][T];
vector<int> R[K];
ll ans;

int op(int x,int y)
{
	if (a[x]>a[y]) return x;
	return y;
}

void Init_ST()
{
	lg[0]=-1;
	for (int i=1;i<=n;i++)
	{
		lg[i]=lg[i>>1]+1;
		f[i][0]=i;
	}
	for (int k=1;k<=lg[n];k++)
	{
		for (int i=1;i+(1<<k)-1<=n;i++)
		{
			f[i][k]=op(f[i][k-1],f[i+(1<<(k-1))][k-1]);
		}
	}
}

int query(int l,int r)
{
	int k=lg[r-l+1];
	return op(f[l][k],f[r-(1<<k)+1][k]);
}

int Mod(ll x) { return (x%k+k)%k; }

int get_cnt(int qr,int l,int r)
{
	return upper_bound(R[qr].begin(),R[qr].end(),r)-lower_bound(R[qr].begin(),R[qr].end(),l);
}

void solve(int l,int r)
{
	if (l>=r) return;
	if (r-l+1==2) 
	{
		int p=query(l,r);
		ll s=Mod(sum[r]-sum[l-1]-a[p]);
		if (s%k==0) ans++;
		return;
	}
	
	int p=query(l,r);
	solve(l,p-1),solve(p+1,r);
	
	if (p-l<r-p)
	{
		for (int i=l;i<=p;i++)
		{
			ll s=sum[p-1]-sum[i-1];
			int qr=Mod(sum[p]-s);
			//assert(Mod(qr-sum[p]+s)==0);
			ans+=get_cnt(qr,p,r);
		}
		ans--;
	}
	else
	{
		for (int i=p;i<=r;i++)
		{
			ll s=sum[i]-sum[p];
			int qr=Mod(sum[p-1]+s);
			//assert(Mod(sum[p-1]-qr+s)==0);
			ans+=get_cnt(qr,l-1,p-1);
		}
		ans--;
	}
}

int main()
{
	cin >> n >> k;
	for (int i=1;i<=n;i++) cin >> a[i];
	for (int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
	for (int i=0;i<=n;i++) R[sum[i]%k].push_back(i);
	
	Init_ST();
	
	ans=0;
	solve(1,n);
	cout << ans << "\n";
	
	return 0;
}
```

---

## 作者：TMLY114514 (赞：1)

## 题解：CF549F Yura and Developers

很套路的分治题。

看到所有区间的贡献和，考虑用分治做。有一种很典的处理跨越左右区间的最值的做法，枚举左端点，找到最值取在左区间时跨越区间的最右的右端点 $r$，此时合法区间数即为 $r-mid$。算最大值在右区间的子段同理。左区间严格取到最值，右区间不严格，就可以保证不会算重。

此时左区间的最值是以 $mid$ 结尾的后缀最值，可以在从 $mid$ 扫到 $l$ 的时候维护。此时让左区间取到最值的最大的 $r$ 是单调递增的，可以直接双指针维护。

回到本题，要求长度大于 $1$ 且满足 $\displaystyle \sum_{i=l}^{r}a_i-\max_{i=l}^{r}a_i\equiv 0\space(\bmod\space k)$ 的子区间个数。

考虑套用上面的办法，在扩展区间的时候把区间和存到桶里，取和区间最值相等的部分。发现这样在扩展左区间时，有很多右区间的和都会改变，难以维护。考虑把原式化为：

$$\displaystyle \sum_{i=mid+1}^{r}a_i\equiv \max_{i=l}^{r}a_i-\sum_{i=l}^{mid}a_i\space(\bmod\space k)$$

此时左右区间互不影响，很容易在扩展区间的时候维护存贡献的桶。
### 代码：
```cpp
#define int long long
int n,k,a[N],s[N],st[N],cnt[1000000];
inline int solve(int l,int r){
	if(l==r)return 0;
	int mid=l+r>>1,mx=0,j=mid,tag=0,top=0,res=0;
	for(int i=mid;i>=l;--i){
		tag=(tag+a[i])%k;
		mx=max(mx,a[i]);
		while(j<r&&a[j+1]<mx){//左端点l对应的最右端点，此时有j-mid个区间
			++j;
			++cnt[(s[j]+k-s[mid])%k];
			st[++top]=(s[j]+k-s[mid])%k;
		}
		res+=cnt[(mx+k-tag)%k];
	}
	while(top)--cnt[st[top--]];
	j=mid+1,tag=mx=0;
	for(int i=mid+1;i<=r;++i){
		tag=(tag+a[i])%k;
		mx=max(mx,a[i]);
		while(j>l&&a[j-1]<=mx){
			--j;
			++cnt[(s[mid]+k-s[j-1])%k];
			st[++top]=(s[mid]+k-s[j-1])%k;
		}
		res+=cnt[(mx+k-tag)%k];
	}
	while(top)--cnt[st[top--]];
	return solve(l,mid)+solve(mid+1,r)+res;
}
```

---

## 作者：CQ_Bab (赞：0)

# 前言
没脑子题。
# 思路
看到求有多少个子段还有最大值，直接分治。

假设当前分治区间为 $l\sim r$ 那么考虑枚举左端点 $x$ 那么我们可以推出能拓展到的最靠右的点 $rr$ 那么对于满足条件的区间需要满足 $(s_r-s_{l-1})\bmod k=\max(s_l\sim s_r)\bmod k$ 然后移项便可求出合法的右端点需要满足的条件，枚举左端点同理。

就转化为了求一段区间中数 $x$ 的出现次数，当然可以主席树（但是被卡死了），所以还是老老实实离线之后扫过去用桶统计即可，细节见代码。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define fs complex<double>
#define pi acos(-1)
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define ll long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
}
int T=1;
int n,k;
const int N=3e5+10;
int a[N],f[N][20];
int lg[N];
int rt[N],idx;
int s[N],mp[1001000];
int Ans(int l,int r) {
	int len=lg[r-l+1];
	return max(f[l][len],f[r-(1<<len)+1][len]);
}
ll ans=0;
vector<int>v[N];
void get(int l,int r) {
	if(l>=r) return;
	int mid=l+r>>1;
	get(l,mid);
	get(mid+1,r);
	rep(i,l-1,r) v[i].clear();
	rep(i,mid+1,r) {
		int s1=Ans(mid+1,i);
		int L=l,R=mid,res=0;
		while(L<=R) {
			int md=L+R>>1;
			if(Ans(md,i)==s1) R=md-1,res=md;
			else L=md+1;
		}
		if(!res) continue;
		int an=(s[i]-s1%k+k)%k;
		v[res-1].pb(an);
	}
	rep1(i,mid-1,l-1) {
		mp[s[i]]++;
		for(auto to:v[i]) ans+=mp[to];
	}
	rep(i,l-1,mid-1) mp[s[i]]--;
	rep(i,l,mid) {
		int s1=Ans(i,mid);
		int L=mid+1,R=r,res=0;
		while(L<=R) {
			int md=L+R>>1;
			if(Ans(mid+1,md)<s1) L=md+1,res=md;
			else R=md-1;
		}
		if(!res) continue;
		int an=(s[i-1]+s1)%k;
		v[res].pb(an);
	}
	rep(i,mid+1,r) {
		mp[s[i]]++;
		for(auto to:v[i]) ans+=mp[to];
	}
	rep(i,mid+1,r) mp[s[i]]--;
}
void solve() {
	in(n),in(k);
	rep(i,1,n) in(a[i]),s[i]=(s[i-1]+a[i])%k,f[i][0]=a[i];
	rep(i,2,n) lg[i]=lg[i/2]+1;
	rep(j,1,19) rep(i,1,n-(1<<j)+1) f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);
	get(1,n);
	printf("%lld\n",ans);
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：_determination_ (赞：0)

显然要对着最大值分治。

设现在在处理区间 $[L,R]$，最大值在 $m$ 处。

显然分治只能枚举较小一侧（假设是 $[L,mid)$，另一半同理）。那么我们要算出来每个左端点的贡献。

一个区间 $[l,r]$ 有贡献，当且仅当 $s_r-s_{l-1}-a_m \bmod k=0$，其中 $s_x=\sum_{i=1}^{x}a_i$。那拆式子之后我们就会得到一堆形如 $(l,r,x)$ 的询问，代表着区间 $[l,r]$ 内 $s_i\bmod k=x$ 的 $i$ 的个数。最终答案就是这 $O(n\log n)$ 个询问的答案总和。

至于处理这些询问，非常简单，直接离线一下树状数组处理即可。时间复杂度 $O(n\log^2n)$。

[Link](https://codeforces.com/contest/549/submission/304954727) 跑得飞快。

---

## 作者：kkxacj (赞：0)

#### 思路

对于每个值 $a_i$ 我们求出一个管理区间 $\left(l_i,r_i\right)$，表示它是 $\left(l_i,r_i\right)$ 里最大的数。

若 $l_i \le L \le i \le r \le r_i$，则我们可以抛弃 $a_i$，我们记 $sum_i$ 为前缀和，问题转化为快速求一段区间使得 $\left(sum_r-sum_{l-1}-a_i\right)\bmod k = 0$，这个式子可以移项得到下面两个式子：

1. $sum_r\bmod k = \left(sum_{l-1}+a_i\right)\bmod k$
2. $sum_{l-1}\bmod k = \left(sum_{r}-a_i\right)\bmod k$

我们考虑笛卡尔树分治，先用桶存一下 $sum_i$，得到每个值出现了几次，每次找到一个最大值，然后选出小的一边计算贡献，左右分别对应上面的一式二式，算完后递归两边即可，如果对实现有疑惑的可以看一下代码。

**code**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf1) + fread(buf1, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf1[1 << 23], *p1 = buf1, *p2 = buf1, ubuf[1 << 23], *u = ubuf;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 1e6+10;
int n,k,o,a[N],sum[N],ans,t[N],lg[N],st[N][20]; 
inline int Max(int l,int r)
{
	if(a[l] > a[r]) return l;
	return r;
}
void solve(int l,int r)
{
	if(l == r)
	{
		t[sum[l]]--,ans++;//我们先抛开len>=2的要求，最后减n即可，注意此时也需要删去贡献 
		return;
	}
	if(l>r) return;
	o = lg[r-l+1];
	int mid = Max(st[l][o],st[r-(1<<o)+1][o]);
	if(mid-l <= r-mid)
	{
		for(int i = l;i < mid;i++) t[sum[i]]--;
		for(int i = l;i <= mid;i++) ans += t[(sum[i-1]+a[mid])%k];
		t[sum[mid]]--; 
		solve(mid+1,r);//递归完右边，右边的贡献都被删完了，把左边的加入递归即可 
		for(int i = l;i < mid;i++) t[sum[i]]++;
		solve(l,mid-1);
	} 
	else
	{
		for(int i = r;i > mid;i--) t[sum[i]]--;
		t[sum[l-1]]++,t[sum[mid]]--;//由于要计算sum_{l-1}的，会有所改变 
		for(int i = r;i >= mid;i--) ans += t[(sum[i]-a[mid]%k+k)%k];
		t[sum[l-1]]--; //删去这里的贡献，不过sum[mid]的贡献本来就要删，就不用恢复了 
		solve(l,mid-1);
		for(int i = r;i > mid;i--) t[sum[i]]++;
		solve(mid+1,r);
	}
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(k);
	for(int i = 1;i <= n;i++) read(a[i]),sum[i] = sum[i-1]+a[i],sum[i]%=k,st[i][0] = i,t[sum[i]]++;
	for(int i = 2;i <= n;i++) lg[i] = lg[i/2]+1;
	for(int i = 1;i <= lg[n];i++)//st表找区间最大值下标 
		for(int j = 1;j+(1<<i)-1 <= n;j++)
			st[j][i] = Max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
	solve(1,n); 
	print(ans-n); flush();
	return 0;
}
/*
对于每个值a_i我们求出一个管理区间(l_i,r_i)，表示它是(l_i,r_i)里最大的数
若 l_i <= L <= i <= r <= r_i && r != l，则我们可以抛弃a_i，问题转化为快速求一段区间%k=0
sum_i为前缀和，sum_r%k = (sum_{l-1}+a_i)%k 则%k=0
右边就是(sum_r-a_i)%k = sum_{l-1}%k 
优先考虑用桶存sum_r%k的值，然后选小的一边删去贡献，然后直接计算，然后加入贡献，递归完事 
*/ 
```

---

## 作者：ast123 (赞：0)

### [CF549F Yura and Developers](https://www.luogu.com.cn/problem/CF549F)

直接枚举时间复杂度会很高，考虑分治。
取区间的中点 $[l,r]$，该区间的答案即为过中点 $mid$ 的满足条件的区间数加上区间 $[l,mid]$ 和 $[mid+1,r]$ 的答案。

考虑固定左端点，求过区间中点的答案数。可以考虑维护序列模k意义下的前缀和以及右端点区间 $[i,r](mid+1 \leq i \leq r)$ 的最大值 $pre_i$、统计区间 $[mid+1,i]$ 和减去最大值模k结果的 $b1_j$ 和统计区间 $[mid+1,i]$ 和模k结果的 $b2_j$，$b1_j$ 可以用一个for循环预处理，$b2_j$ 初始全部为 $0$，不断增大 $i$，这时 $b1_j$ 要减去原来的 $i$ 的贡献，$b2_j$ 要加上 $i$ 的贡献。可以发现，随着左端点逐渐靠近 $l$，左半部分的最大值是不降的，所以可以按照上面的做法，保证最大值在我们想要的那一边，接着按照最大值的位置分类讨论，假设此时左端点为 $l_1$，区间 $[l_1,mid]$ 的和模 $k$ 的值为 $sum$，最大值为 $mx$。
1. 区间最大值在 $mid$ 左边，此时贡献为 $b2[k-((sum+mx)\bmod k)]$。
2. 区间最大值在 $mid$ 右边，此时贡献为 $b1[k-(sum\bmod k)]$。

注意这里 $k$ 是 $10^6$ 级别的，直接从 $1$ 至 $k$ 初始化为 $0$ 会 TLE，所以我们最后只清空修改过的，$n$ 是 $5 \times 10^5$ 级别的，可以过。

核心代码：
```cpp
ll solve(int l, int r){
	if(l >= r) return 0;
	int mid = l+r>>1;
	int mx = a[mid+1];
	ll ans = 0;
	pre[mid] = 0;
	for(int i=mid+1; i<=r; ++i)
		pre[i] = max(pre[i-1], a[i]), ++b1[mod(s[i]-s[mid]-pre[i])];
	
	mx = a[mid];
	int j = mid+1;
	for(int i=mid; i>=l; --i, mx=max(mx, a[i])){
		while(j<=r && pre[j]<=mx){//保证b1中的一定是最大值，b2中的和正确 
			--b1[mod(s[j]-s[mid]-pre[j])];
			++b2[mod(s[j]-s[mid])]; ++j;
		}
		if(j > mid+1) ans += b2[mod(k-s[mid]+s[i-1]+mx)];
		if(j <= r) ans += b1[mod(k-s[mid]+s[i-1])];
	}
	for(int i=mid+1; i<=j; ++i)//卡常，直接0~k-1 1e6*log2(3e5)会TLE 
		b2[mod(s[i]-s[mid])] = 0;
	for(int i=j; i<=r; ++i)
		b1[mod(s[i]-s[mid]-pre[i])] = 0;
	return ans + solve(l, mid) + solve(mid+1, r);
}
```
完整代码：
```cpp
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
const int N = 3e5+5, K = 1e6+5;
int n, k, a[N], s[N], b1[K], b2[K], pre[N];
inline int mod(int x){//计算x mod k的值 
	return (x%k+k)%k; 
}
inline int read(){
	int res = 0;
	char ch=' ';
	while(ch<'0' || ch>'9') ch = getchar();
	while(ch>='0' && ch<='9'){
		res = (res<<3)+(res<<1)+ch-'0';
		ch = getchar();
	}
	return res;
}
ll solve(int l, int r){
	if(l >= r) return 0;
	int mid = l+r>>1;
	int mx = a[mid+1];
	ll ans = 0;
	pre[mid] = 0;
	for(int i=mid+1; i<=r; ++i)
		pre[i] = max(pre[i-1], a[i]), ++b1[mod(s[i]-s[mid]-pre[i])];
	
	mx = a[mid];
	int j = mid+1;
	for(int i=mid; i>=l; --i, mx=max(mx, a[i])){
		while(j<=r && pre[j]<=mx){//保证b1中的一定是最大值，b2中的和正确 
			--b1[mod(s[j]-s[mid]-pre[j])];
			++b2[mod(s[j]-s[mid])]; ++j;
		}
		if(j > mid+1) ans += b2[mod(k-s[mid]+s[i-1]+mx)];
		if(j <= r) ans += b1[mod(k-s[mid]+s[i-1])];
	}
	for(int i=mid+1; i<=j; ++i)//卡常，直接0~k-1 1e6*log2(3e5)会TLE 
		b2[mod(s[i]-s[mid])] = 0;
	for(int i=j; i<=r; ++i)
		b1[mod(s[i]-s[mid]-pre[i])] = 0;
	return ans + solve(l, mid) + solve(mid+1, r);
}
int main(){
	n = read(); k = read();
	for(int i=1; i<=n; ++i){
		a[i] = read();
		s[i] = mod(s[i-1]+a[i]);
	}
	
	printf("%lld\n", solve(1, n));
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

遇到最大值，考虑笛卡尔树。

不难发现对于一个位置 $a_i$ 为子树根时，每次相当于要统计 $x\in[l-1,i-1]$，$y\in[i,r]$，$pre_y-pre_x\equiv a_i(\bmod\ k)$ 的 $(x,y)$ 数量。

考虑启发式合并，按左边与右边大小将小的一边枚举统计，然后合并至右边即可。可以用数组或 map 存，本人偷懒不建树直接用 map 写的，复杂度 $O(n\log^2n)$，建树后用启发式合并是 $O(n\log n)$ 的。双 $\log$ 比较卡常，本人用了 pb_ds。

```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/trie_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
#pragma GCC optimize(2,3,"Ofast","inline")
using namespace std;
int n,k,a[300005],b[300005],fl[300005],fr[300005],f[300005],pre[300005];
long long ans;
vector<int> apr[300005];
gp_hash_table<int,int> mp[300005];
int findl(int i){ return fl[i]==i?fl[i]:fl[i]=findl(fl[i]); }
int findr(int i){ return fr[i]==i?fr[i]:fr[i]=findr(fr[i]); }
int find(int i){ return f[i]==i?f[i]:f[i]=find(f[i]); }
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i],pre[i]=(pre[i-1]+a[i])%k;
	sort(b+1,b+n+1); int m=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++) apr[a[i]=lower_bound(b+1,b+m+1,a[i])-b].push_back(i); 
	for(int i=1;i<=n;i++){
		for(auto v:apr[i]){
			fl[v]=fr[v]=f[v]=v;
			if(!fl[v-1]&&!fl[v+1]){
				mp[v][pre[v]]++;
				mp[v][pre[v-1]]++;
				continue;
			}
			if(!fl[v-1]){
				fl[v+1]=v;
				fr[v]=findr(v+1);
				f[v]=find(v+1);
				ans+=mp[find(v)][pre[v]]-1;
				mp[find(v)][pre[v-1]]++;
				continue;
			}
			if(!fl[v+1]){
				fr[v-1]=v;
				fl[v]=findl(v-1);
				f[v]=find(v-1);
				ans+=mp[find(v)][pre[v-1]]-1;
				mp[find(v)][pre[v]]++;
				continue;
			}
			int lm=findl(v-1),rm=findr(v+1),bl=find(v-1),br=find(v+1);
			int dl=v-findl(v-1),dr=findr(v+1)-v;
			if(dl<dr){
				for(int j=lm;j<=v;j++) ans+=mp[br][(pre[j-1]+b[a[v]])%k];
				for(int j=lm;j<=v;j++) mp[br][pre[j-1]]++;
				mp[bl].clear();
				f[find(v-1)]=find(v+1);
				f[v]=find(v+1);
			}
			else{
				for(int j=v;j<=rm;j++) ans+=mp[bl][(pre[j]+k-b[a[v]]%k)%k];
				for(int j=v;j<=rm;j++) mp[bl][pre[j]]++;
				mp[br].clear();
				f[find(v+1)]=find(v-1);
				f[v]=find(v-1);
			}
			ans--;
			fl[v]=findl(v-1);
			fl[v+1]=findl(v-1);
			fr[v]=findr(v+1);
			fr[v-1]=findr(v+1);
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Avocadooo (赞：0)

考虑分治。

对于区间 $ [L,R] $，其答案为 $ [L,mid],[mid+1,R] $ 区间内的答案加上跨越这两个区间的答案。

考虑如何求跨区间答案。显然跨越左右区间的一个子段可以看作是由 $ [L',mid],[mid+1,R'] $ 拼接而成。

分类看 $ \max $ 值在左区间还是右区间。

- 若在左区间，则左区间对子段权值的贡献为 $ sum(L',mid)-\max(L',mid) $，右区间贡献为 $ sum(mid+1,R') $。

- 若在右区间，则左区间对子段权值的贡献为 $ sum(L',mid) $，右区间对贡献为 $ sum(mid+1,R')-\max(mid+1,R') $。

左边可供拼接的有 $ mid-l+1 $ 个串，右区间可供拼接的有 $ r-mid $ 个串。将这些串放在一起按串内最大值从小到大排序（**相同则根据是左区间还是右区间排序**）。

顺序倒序扫两次，用模 $ k $ 的桶统计即可。

下面是一些细节。

为了不重不漏，我们规定桶中存的是**左区间的串的贡献**，即统计贡献时左区间的串一定比右区间的串先扫到。

- 顺序时，先扫到的（即左区间）最值较小，其贡献为该串的 $ sum $，后扫到的（即右区间）贡献为 $ sum-\max $。

- 倒序时，先扫到的（即左区间）最值较大，其贡献为 $ sum-\max $，后扫到的（即右区间）贡献为 $ sum $。

由于最值相同时我们根据是左区间还是右区间排了序，所以当左右两边的两个串的 $ \max $ 相同时，我们同样没有重复统计。

至此解决该题，时间复杂度 $ O(n \log^2n) $。

另外，考虑到左区间的串和右区间的串的 $ \max $ 具有单调性，可以归并排序将时间复杂度降低至 $ O(n \log n) $，但是作者不想写了。

剩下的细节见代码：

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=1000005;
#define int ll
#define inv(x) (k-(x)%k)%k
int n,k,a[N],bk[N];
struct P{int sum,mx,id;}t[N];
int solve(int x,int y)
{
	if(x==y) return 0;
	int mid=x+y>>1,Ans=solve(x,mid)+solve(mid+1,y),j=1;

	for(int i=mid;i>=x;j++,i--) t[j].mx=max(t[j-1].mx,a[i]),t[j].sum=t[j-1].sum+a[i],t[j].id=0;
	for(int i=mid+1;i<=y;j++,i++) t[j].mx=max((i!=mid+1)*t[j-1].mx,a[i]),t[j].sum=(i!=mid+1)*t[j-1].sum+a[i],t[j].id=1;

	--j;
	sort(t+1,t+j+1,[](P A,P B){return A.mx==B.mx?A.id<B.id:A.mx<B.mx;});

	for(int i=1;i<=j;i++) t[i].id?Ans+=bk[inv(t[i].sum-t[i].mx)]:++bk[t[i].sum%k];
	for(int i=1;i<=j;i++) bk[t[i].sum%k]-=(!t[i].id);

	for(int i=j;i>=1;i--) t[i].id?Ans+=bk[inv(t[i].sum)]:++bk[(t[i].sum-t[i].mx)%k];
	for(int i=j;i>=1;i--) bk[(t[i].sum-t[i].mx)%k]-=(!t[i].id);

	return Ans;
}
signed main()
{
	scanf("%lld %lld",&n,&k);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	printf("%lld\n",solve(1,n));
}
```

---

## 作者：UperFicial (赞：0)

同步发表于我的 [$\text{cnblog}$](https://www.cnblogs.com/UperFicial/p/16377512.html)。

楼下的两篇题解都看不懂，不会笛卡尔树，不会打标找规律。

但是 $\texttt{CDQ}$ 分治你值得拥有。


对于分治的两个区间 $[l,mid]$ 和 $(mid,r]$，对于分别位于两个区间的点 $j,i$，计算是否有贡献。

设 $s_i$ 表示前缀/后缀和，$b_i$ 表示前缀/后缀最大值。

则可以将题目条件写成另一种形式：$s_j+s_i -\max (b_i,b_j)\equiv 0\pmod k$。

对于取 max 操作，我们最常见的手法就是分情况讨论。

这里只讨论 $b_j>b_i$ 的情况，另一种情况留给读者分析。

那么原式化为 $s_j+s_i -b_j\equiv 0\pmod k$。

令 $c_i =s_j -b_j$，则原式变为 $s_i+c_j \equiv 0\pmod k$。

那么本题可以转化为，对于 $b_j>b_i$ 的所有下标 $j$，有多少个满足与 $c_j+s_i\equiv 0\pmod k$。

这就很简单了，我们对 $[l,mid]$ 和 $(mid,r]$ 分别按照 $b_i$ 排序，然后一个 Two-Pointers 两边扫过去就行了。

单点修改单点查询的问题我竟然一开始 nt 写了树状数组然后被卡常了。

这样复杂度是 $\Theta(n\log^2 n)$，瓶颈在于排序。

**能不能更快？**

答案是可以的。

我们排序的 $b$ 是一个前缀/后缀最大值，它是具有单调性的，所以只需要区间反转，这是 $\Theta(n\log n)$ 的！

但你会发现不管是 $\Theta(n\log n)$ 还是 $\Theta(n\log ^2 n)$ 都是最劣解。

![](https://cdn.luogu.com.cn/upload/image_hosting/8gcqvss7.png)

两次速度对比。

放一下代码（需要针对 $b$ 的大小关系做两次 $\texttt{CDQ}$，所以有点长）：

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<cctype>
#include<stack>
#include<map>
#include<climits>
#include<set>
#include<iostream>
#define rint() read<int>()
#define rll() read<ll>()
#define rep(i,a,b) for(register int i=a;i<=b;++i)
#define rev(i,a,b) for(register int i=a;i>=b;--i)
#define gra(i,u) for(register int i=head[u];i;i=edge[i].nxt)
#define print(a,l,r) rep(i,l,r) printf("%d ",a[i]);
#define printll(a,l,r) rep(i,l,r) printf("%lld ",a[i]);
#define Clear(a) memset(a,0,sizeof(a))
#define yes puts("YES")
#define no puts("NO")
#define yyds puts("YYDS")
using namespace std;
typedef long long ll;
inline int read()
{
	register int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
const int INF=1e9;
const ll LLINF=1e18;
template<typename T>
inline T Min(T x,T y){return x<y?x:y;}
template<typename T>
inline T Max(T x,T y){return x>y?x:y;}
template<typename T>
inline void Swap(T&x,T&y){int t=x;x=y;y=t;return;}
const int MAXN(3e5+10);
const int MAXM(1e6+10);
int n,k,a[MAXN],b[MAXN];
ll s[MAXN],c[MAXN]; 
struct node{int s,c;int b;};
node h[MAXN];
inline bool cmp2(node x,node y){return x.b<y.b;}
inline bool cmp4(node x,node y){return x.b>y.b;}
int bit[MAXM];
inline ll CDQ(int l,int r)
{
	if(l==r) return 0;
	int mid=(l+r)>>1;
	ll ans=CDQ(l,mid)+CDQ(mid+1,r);
	b[mid]=a[mid],s[mid]=a[mid],b[mid+1]=a[mid+1],s[mid+1]=a[mid+1];
	rev(i,mid-1,l) b[i]=Max(a[i],b[i+1]),s[i]=s[i+1]+(ll)a[i];
	rep(i,mid+2,r) b[i]=Max(a[i],b[i-1]),s[i]=s[i-1]+(ll)a[i];
	rep(i,l,r) c[i]=s[i]-(ll)b[i];
	rep(i,l,r)
	{
		c[i]%=k,s[i]=(-s[i]%k+(ll)k)%k;
		h[i].c=(int)c[i]+1,h[i].s=(int)s[i]+1,h[i].b=b[i];
	} 
	reverse(h+l,h+mid+1);
	int j(l);
	rep(i,mid+1,r)
	{
		while(j<=mid&&h[j].b<h[i].b) ++bit[h[j].s],++j;
		ans+=(ll)bit[h[i].c];
	}
	rep(i,l,j-1) --bit[h[i].s];
	return ans;
}
inline ll CDQ2(int l,int r)
{
	if(l==r) return 0;
	int mid=(l+r)>>1;
	ll ans=CDQ2(l,mid)+CDQ2(mid+1,r);
	b[mid]=a[mid],s[mid]=a[mid];
	b[mid+1]=a[mid+1],s[mid+1]=a[mid+1];
	rev(i,mid-1,l) b[i]=Max(a[i],b[i+1]),s[i]=s[i+1]+(ll)a[i];
	rep(i,mid+2,r) b[i]=Max(a[i],b[i-1]),s[i]=s[i-1]+(ll)a[i];
	rep(i,l,r)
	{
		c[i]=((b[i]-s[i])%k+(ll)k)%k,s[i]%=k;
		h[i].c=(int)c[i]+1,h[i].s=(int)s[i]+1,h[i].b=b[i];
	} 
	reverse(h+mid+1,h+r+1);
	int j(l);
	rep(i,mid+1,r)
	{
		while(j<=mid&&h[j].b>=h[i].b) ++bit[h[j].c],++j;
		ans+=bit[h[i].s];
	}
	rep(i,l,j-1) --bit[h[i].c];
	return ans;
}
int main()
{
	n=read(),k=read();
	rep(i,1,n) a[i]=read();
	printf("%lld\n",CDQ(1,n)+CDQ2(1,n));
	return 0;
}
```

---

