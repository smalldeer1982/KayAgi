# Program

## 题目描述

You are given a program that consists of $ n $ instructions. Initially a single variable $ x $ is assigned to $ 0 $ . Afterwards, the instructions are of two types:

- increase $ x $ by $ 1 $ ;
- decrease $ x $ by $ 1 $ .

You are given $ m $ queries of the following format:

- query $ l $ $ r $ — how many distinct values is $ x $ assigned to if all the instructions between the $ l $ -th one and the $ r $ -th one inclusive are ignored and the rest are executed without changing the order?

## 说明/提示

The instructions that remain for each query of the first testcase are:

1. empty program — $ x $ was only equal to $ 0 $ ;
2. "-" — $ x $ had values $ 0 $ and $ -1 $ ;
3. "---+" — $ x $ had values $ 0 $ , $ -1 $ , $ -2 $ , $ -3 $ , $ -2 $ — there are $ 4 $ distinct values among them;
4. "+--+--+" — the distinct values are $ 1 $ , $ 0 $ , $ -1 $ , $ -2 $ .

## 样例 #1

### 输入

```
2
8 4
-+--+--+
1 8
2 8
2 5
1 1
4 10
+-++
1 1
1 2
2 2
1 3
2 3
3 3
1 4
2 4
3 4
4 4```

### 输出

```
1
2
4
4
3
3
4
2
3
2
1
2
2
2```

# 题解

## 作者：wanggk (赞：6)

upd.2022.8.13 修改了一处错别字。

### 前言

决定写一篇容易看懂的，不用 ~~又臭又长的~~ 线段树的题解。

### 题意

一个数初始为 $0$，给定一个操作序列。加号和减号分别表示该操作使该数增加或减少 $1$，$k$ 次询问：若删去操作序列的区间 $[l,r]$，整个操作过程中会出现多少个不同的数。

### 分析

- **对于区间**：减去一个区间，相当于只计算区间左边的一个前缀，和区间右边的一个后缀。

- **对于最值与个数**：每次加上或减去 $1$，意味着只要求出某一段最大值 $mx$ 和最小值 $mn$，所有在 $[mn,mx]$ 中的数都出现过。记这段区间答案即为 $mx-mn+1$。

- **对于去重**：区间左边的前缀，和区间右边的前缀，可能出现相同的数字。这个时候要去重，把两个区间各自的最大值和最小值求出来，然后再求 两个区间的并区间 。

- **对于初值 0**：考虑操作前数的初值为 $0$，这个 $0$ 也算出现过的数。那么对于我们所求的答案，如果答案中不包含 $0$，那么要再把 $0$ 的那个也算上。

- **对于端点**：如果询问的区间与原操作序列端点重合，即端点也被删去了，这种情况我是选择了特判（不确定不特判可不可以）。

### 代码

```cpp
int a[maxn];//加减序列 
int sum[maxn];//前缀和数组 
int mx1[maxn],mn1[maxn];//sum[1]-sum[i]的最大/小值 
int mx2[maxn],mn2[maxn];//sum[i]到sum[n]的最大/小值 
```
```cpp
sum[0]=0,mx1[0]=-inf,mx2[n+1]=-inf,mn1[0]=inf,mn2[n+1]=inf;//多组数据初始化 
for(int i=1;i<=n;i++) a[i]=(s[i-1]=='+')?1:-1,sum[i]=sum[i-1]+a[i];
for(int i=1;i<=n;i++) mx1[i]=max(mx1[i-1],sum[i]),mn1[i]=min(mn1[i-1],sum[i]);
for(int i=n;i>=1;i--) mx2[i]=max(mx2[i+1],sum[i]),mn2[i]=min(mn2[i+1],sum[i]); 
```
计算前缀和，前缀最大值，前缀最小值，后缀最大值，后缀最小值。

```cpp
int chk(int x,int y){ if(x<=0&&y>=0) return 0; return 1; }//专门判断初始未操作的0，如果在答案区间未出现，则加一 
int solve(int x,int y,int x2,int y2)//求两段区间去重之后的"并"，return"并"的大小 
{
	if(x>x2) swap(x,x2),swap(y,y2);
	if(x2>y) return (y-x+1)+(y2-x2+1)+(chk(x,y)&chk(x2,y2));//不相交，直接输出长度的和
	return max(y,y2)-min(x,x2)+1+chk(min(x,x2),max(y,y2));
}
```
chk 函数用来特判初值 $0$， solve 函数用来计算两个区间的并区间。

#### 完整代码

```cpp
#include<bits/stdc++.h>
#define inf 1000000000
#define maxn 200005
using namespace std;

string s;
int T,n,m;
int a[maxn];//加减序列 
int sum[maxn];//前缀和数组 
int mx1[maxn],mn1[maxn];//sum[1]-sum[i]的最大/小值 
int mx2[maxn],mn2[maxn];//sum[i]到sum[n]的最大/小值 

int chk(int x,int y){ if(x<=0&&y>=0) return 0; return 1; }//专门判断初始未操作的0，如果在答案区间未出现，则加一 
int solve(int x,int y,int x2,int y2)//求两段区间去重之后的"并"，return"并"的大小 
{
	if(x>x2) swap(x,x2),swap(y,y2);
	if(x2>y) return (y-x+1)+(y2-x2+1)+(chk(x,y)&chk(x2,y2));//不相交，直接输出长度的和
	return max(y,y2)-min(x,x2)+1+chk(min(x,x2),max(y,y2));
}

signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m>>s;
		sum[0]=0,mx1[0]=-inf,mx2[n+1]=-inf,mn1[0]=inf,mn2[n+1]=inf;//多组数据初始化 
		for(int i=1;i<=n;i++) a[i]=(s[i-1]=='+')?1:-1,sum[i]=sum[i-1]+a[i];
		for(int i=1;i<=n;i++) mx1[i]=max(mx1[i-1],sum[i]),mn1[i]=min(mn1[i-1],sum[i]);
		for(int i=n;i>=1;i--) mx2[i]=max(mx2[i+1],sum[i]),mn2[i]=min(mn2[i+1],sum[i]); 
		while(m--)
		{
			int l,r;
			cin>>l>>r;
			//这组if语句用来判l和r在两端时的特殊情况 
			if(l==1&&r==n) cout<<1<<endl;
			else if(l==1) cout<<(mx2[r+1]-mn2[r+1]+1)+chk(mn2[r+1]-(sum[r]-sum[l-1]),mx2[r+1]-(sum[r]-sum[l-1]))<<endl;
			else if(r==n) cout<<(mx1[l-1]-mn1[l-1]+1)+chk(mn1[l-1],mx1[l-1])<<endl; 
			else
			{
				int x=mn1[l-1],y=mx1[l-1];
				int x2=mn2[r+1]-(sum[r]-sum[l-1]),y2=mx2[r+1]-(sum[r]-sum[l-1]);//把[l,r]这段操作带来的前缀和影响消除，所以减去这段操作区间和 
				cout<<solve(x,y,x2,y2)<<endl; 
			}
		}
	}
	return 0;
}
```


---

## 作者：Theophania (赞：3)

在一段操作中 $x$ 的所有值必然是连续的，所以只需求出最大值和最小值就知道了值域大小。无视一段操作后整个区间被分为至多两部分，只需求出每个值域的大小再减去公共部分即可。

可以用ST表求区间最值，时间复杂度 $O(n\log n + m)$。

```c++
#include <bits/stdc++.h>
using namespace std;
string str;
int ST1[200001][22], ST2[200001][22];
int querymax(int left, int right)
{
    int k = log2(right - left + 1);
    return max(ST1[left][k], ST1[right - (1 << k) + 1][k]);
}

int querymin(int left, int right)
{
    int k = log2(right - left + 1);
    return min(ST2[left][k], ST2[right - (1 << k) + 1][k]);
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        int n, q, ans;
        cin >> n >> q;
        cin >> str;
        for (int i = 1; i <= n; ++i)
        {
            if (str[i - 1] == '+')
                ST1[i][0] = ST1[i - 1][0] + 1, ST2[i][0] = ST2[i - 1][0] + 1;
            else
                ST1[i][0] = ST1[i - 1][0] - 1, ST2[i][0] = ST2[i - 1][0] - 1;
        }
        for (int j = 1; j <= 22; ++j)
            for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            {
                ST1[i][j] = max(ST1[i][j - 1], ST1[i + (1 << (j - 1))][j - 1]);
                ST2[i][j] = min(ST2[i][j - 1], ST2[i + (1 << (j - 1))][j - 1]);
            }
        for (int cas = 1, l, r; cas <= q; ++cas)
        {
            cin >> l >> r;
            int lmax = 0, lmin = 0, rmax = 0, rmin = 0, tmp = ST1[r][0] - ST1[l - 1][0];
            if (l > 1)
            {
                lmax = max(0, querymax(1, l - 1));
                lmin = min(0, querymin(1, l - 1));
            }
            if (r < n)
            {
                rmax = querymax(r + 1, n) - tmp;
                rmin = querymin(r + 1, n) - tmp;
            }
            if (lmax < rmin || rmax < lmin)
                ans = lmax - lmin + rmax - rmin + 2;
            else if (lmax <= rmax)
            {
                ans = lmax - lmin + rmax - rmin + 2;
                ans -= lmax - max(rmin, lmin) + 1;
            }
            else
            {
                ans = lmax - lmin + rmax - rmin + 2;
                ans -= rmax - max(rmin, lmin) + 1;
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
```

由于查询的区间有一个端点是固定的，也可以扫两遍前缀和直接统计最值，时间复杂度 $O(n+m)$。

```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 9;
const int inf = 0x3f3f3f3f;

string str;
int T, n, q;
int sum[maxn],  maxxl[maxn], maxxr[maxn], minnl[maxn], minnr[maxn];
signed main()
{
    cin >> T;
    while (T--)
    {
        cin >> n >> q;
        cin >> str;
        for (int i = 1; i <= n; ++i)
        {
            sum[i] = sum[i - 1] + (str[i - 1] == '-' ? -1 : 1);
            maxxl[i] = max(maxxl[i - 1], sum[i]);
            minnl[i] = min(minnl[i - 1], sum[i]);
        }
        maxxr[n + 1] = -inf;
        minnr[n + 1] = inf;
        for (int i = n; i >= 1; --i)
        {
            maxxr[i] = max(maxxr[i + 1], sum[i]);
            minnr[i] = min(minnr[i + 1], sum[i]);
        }
        for (int cas = 1, l, r; cas <= q; ++cas)
        {
            cin >> l >> r;
            int t = sum[r] - sum[l - 1];
            int ans = max(maxxl[l - 1], maxxr[r + 1] - t) - min(minnl[l - 1], minnr[r + 1] - t) + 1;
            cout << ans << '\n';
        }
    }
    return 0;
}
```

---

## 作者：zhouzihang1 (赞：1)

# CF1473D Program 题解

## 题意

给出长度为 $n$ 的操作序列，$\texttt{+}$ 表示上一个数 $+1$，$\texttt{-}$ 表示上一个数 $-1$。

第 $0$ 个数的值为 $0$。

每次询问给出 $l,r$，问删去区间 $l,r$ 后整个操作序列计算完后出现过多少个不同的值。

## 思路

我们可以先计算出操作序列操作后的每一个值，记为 $a$。

有一个结论：

对于 $a$ 的区间 $l,r$，他出现过的值的个数是 $(\max \limits _{i=l} ^{r} a_i) - (\min \limits _{i=l} ^ {r} a_i)$，这一步显然可以 ST 表或线段树维护。

如果有删除操作，只需删去这一区间的前缀和即可。

需要注意的是有的最小值会大于 $0$ 或最大值小于 $0$，特判让其等于 $0$ 即可。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
int n, q, mx[N][20], mn[N][20], lg_[N];
string s;
void initlog(int m) {
	lg_[1] = 0;
	lg_[2] = 1;
	for(int i = 3; i <= m; i++)
		lg_[i] = lg_[i - 1] + ((1 << lg_[i - 1] << 1) == i);
}//预处理 log2，常数优化 
int query(bool op, int l, int r)
//1 max,0 min
{
	if(l > r) return 0;
	int lg = lg_[r - l + 1];
	if(op == 1) return max(mx[l][lg], mx[r - (1 << lg) + 1][lg]);
	return min(mn[l][lg], mn[r - (1 << lg) + 1][lg]);
}
void solve() {
	scanf("%d%d", &n, &q);
	cin >> s;
	s = ' ' + s;
	for(int i = 1; i <= n; i++) {
		mx[i][0] = mx[i - 1][0] + (s[i] == '+' ? 1 : -1);//max
		mn[i][0] = mn[i - 1][0] + (s[i] == '+' ? 1 : -1);//min
	}//处理前缀和 
	for(int j = 1; (1 << j) <= n; j++)
		for(int i = 1; i + (1 << j) - 1 <= n; i++) {
			mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
			mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
		}//ST 表 
	while(q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		int mx1 = query(1, 1, l - 1);//[1,l-1] max
		int mx2 = query(1, r + 1, n);//[r+1,n] max
		int mn1 = query(0, 1, l - 1);//[1,l-1] min
		int mn2 = query(0, r + 1, n);//[r+1,n] min
		//一些情况无法处理可以直接特判 
		if(l == 1 && r == n) {
			puts("1");
			continue;
		}
		if(l == 1) {
			mx2 -= mx[r][0];
			mn2 -= mx[r][0];
			if(mx2 < 0) mx2 = 0;
			if(mn2 > 0) mn2 = 0;
			printf("%d\n", mx2 - mn2 + 1);
			continue;
		}
		if(r == n) {
			if(mx1 < 0) mx1 = 0;
			if(mn1 > 0) mn1 = 0;
			printf("%d\n", mx1 - mn1 + 1);
			continue;
		}
		mx2 -= mx[r][0] - mx[l - 1][0];
		mn2 -= mx[r][0] - mx[l - 1][0];
		//减去 [l,r] 的前缀和 
		if(min(mn1, mn2) > 0) printf("%d\n", max(mx1, mx2) + 1);//max(mx1,mx2)-0+1
		else if(max(mx1, mx2) < 0) printf("%d\n", 1 - min(mn1, mn2));//0-min(mn1,mn2)+1
		else printf("%d\n", max(mx1, mx2) - min(mn1, mn2) + 1);
	}
}
int main() {
	initlog(N - 1);
	int T;
	scanf("%d", &T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：StayAlone (赞：1)

### 前言
我是 zz，所以我用线段树（甚至不是树状数组）维护前缀后缀最值和前缀后缀和。因此这个题是可以 $O(n)$ 单次的。这里讲讲思路。

### 题意

一个数 $x = 0$，给定一个操作序列，包含加减两种符号。

- `+` 表示 $x = x + 1$
- `-` 表示 $x = x - 1$


$k$ 次询问，求删除操作序列中的 $[l, r]$ 后，会出现的不同的数的数量。**询问相互独立**。

### 思路

因为只有加一减一的操作，所以可以发现答案就是当前操作序列的最大值与最小值的差加一。形式化地，令 $s_i$ 表示此次询问的操作序列中，操作完第 $i$ 次操作后的值，令 $p = \max\limits_{i = 1}^{n - (r - l + 1)}\{s_i\}, q = \min\limits_{i = 1}^{n - (r - l + 1)}\{s_i\}$，则这次询问的答案为 $p - q + 1$。原因是出现的数必定都是相邻的，所以 $[p, q]$ 中的所有数都会出现。

而上面的 $s$ 我们也可以从另一个方面理解：把操作序列中的 `-` 变成 $-1$，`+` 变成 $1$ 形成的序列称作 $a$，那么 $s$ 就是序列 $a$ 的前缀和。那么求出 $p$ 和 $q$ 就很简单了。下面以 $p$ 为例， $q$ 以此类推。

删掉 $[l, r]$ 的操作序列，对 $i\in[1,l - 1]$ 中的数没有影响；而对 $i \in [r + 1, n]$ 中的数，实际上是全部减去了一个 $\sum\limits_{i = l}^r a_i$。而这显然可以用前缀和 $s_r - s_{l - 1}$ 求出。故 $p = \max\{\max\limits_{i = 1}^{l - 1}s_i, \max\limits_{i= r + 1}^{n}\{s_i\} - (s_r - s_{l - 1})\}$。

其实说到这里代码就很好写了，只需要预处理前缀和 $s$ 以及它的前缀后缀最值即可。然后当时我因未知原因，用线段树维护了这个东西，所以下面放的代码不必参考。

[AC Record](https://www.luogu.com.cn/record/82960249)

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (int i = l; i <= int(r); ++i)
#define rep2(i, l, r) for (int i = l; i >= int(r); --i)
#define ......
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int MAXN = 2e5 + 10, inf = ~0U >> 2, INF = ~0U >> 1;
const int LOGN = log2(MAXN) + 1;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
namespace stupid_lrc {
	template <typename T> il bool read(T &x)
	il int read()

	template <typename T> il bool read(pair <T, T> &x)

	template <typename T, typename ...L>
	il bool read(T &x, L &...y)

	template <typename T> il void write(T x)

	template <typename T> il void write(T x, char ch)

	template <typename T> il void write(pair <T, T> x)

	template <typename T> il T my_max(const T &x, const T &y)

	template <typename T> il T my_min(const T &x, const T &y)

	template <typename T> il T lowbit(const T &x)
}
using namespace stupid_lrc;
// 奇妙缺省源……
int n, k, a[MAXN]; char s[MAXN];

struct setr {
	#define STZ MAXN << 2
	int sum[STZ], maa[STZ], mii[STZ];

	il void pushup(int x) {
		sum[x] = sum[ls(x)] + sum[rs(x)];
		maa[x] = my_max(maa[ls(x)], maa[rs(x)]);
		mii[x] = my_min(mii[ls(x)], mii[rs(x)]);
	}

	il void build(int x, int l, int r) {
		if (l == r) return sum[x] = maa[x] = mii[x] = a[l], void();
		int mid = l + r >> 1;
		build(ls(x), l, mid); build(rs(x), mid + 1, r);
		pushup(x);
	}

	il int query_max(int x, int l, int r, int ql, int qr) {
		if (l > qr || r < ql) return -inf;
		if (l >= ql && r <= qr) return maa[x];
		int mid = l + r >> 1;
		return my_max(query_max(ls(x), l, mid, ql, qr), query_max(rs(x), mid + 1, r, ql, qr));
	}

	il int query_min(int x, int l, int r, int ql, int qr) {
		if (l > qr || r < ql) return INF;
		if (l >= ql && r <= qr) return mii[x];
		int mid = l + r >> 1;
		return my_min(query_min(ls(x), l, mid, ql, qr), query_min(rs(x), mid + 1, r, ql, qr));
	}

	il int query_sum(int x, int l, int r, int k) {
		if (l > k || r < k) return 0;
		if (l == r) return sum[x];
		int mid = l + r >> 1;
		return query_sum(ls(x), l, mid, k) + query_sum(rs(x), mid + 1, r, k);
	}
} t;

int main() {
	for (int T = read(); T--; ) {
		read(n, k); scanf("%s", s + 1); int ans = 0;
		rep1(i, 1, n) a[i] = a[i - 1] + (s[i] ^ '-' ? 1 : -1);
		a[n + 1] = a[n]; ++n;
		t.build(1, 0, n);
		int maa = -1, mii = INF, l, r;
		while (k--) {
			read(l, r);
			maa = my_max(t.query_max(1, 0, n, 0, l - 1), t.query_max(1, 0, n, r + 1, n) - (t.query_sum(1, 0, n, r) - t.query_sum(1, 0, n, l - 1)));
			mii = my_min(t.query_min(1, 0, n, 0, l - 1), t.query_min(1, 0, n, r + 1, n) - (t.query_sum(1, 0, n, r) - t.query_sum(1, 0, n, l - 1)));
			write(maa - mii + 1, '\n');
		}
	}
	rout;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

因为此题目中对于数的更新只能为 $1$，所以，如果我们找到了 $[1,l - 1]$ 与 $[r + 1,n]$ 中能获得的两个极值即可。

我们为 $S$ 赋予权值，用一个数组 $a$ 储存：

1. 如果 $S_i$ 为 `+`，则其权值为 $1$。

2. 否则其权值为 $-1$。

那么，在第 $i$ 次操作后，能产生的数是 $\sum_{j = 1}^ia_j$。

考虑用前缀和维护这个数，记作 $s$。

因为它是一个静态的问题，所以用 ST 表维护一下前缀和的极值。

对于前一部分（即 $[1,l - 1]$），只需要求出 $\max_{i \in [1,l - 1]}\{s_i\}$ 与 $\min_{i \in [1,l - 1]}\{s_i\}$；对于后一部分，只需要求出 $\max_{i \in [r + 1,n]}\{s_i\} - s_r + s_{l - 1}$ 与 $\min_{i \in [r + 1,n]}\{s_i\} - s_r + s_{l - 1}$ 即可。（因为 $[l,r]$ 区间被忽略了）

此外，需要注意的是，如果 $0$ 未包含在两个极值之间，需要将答案额外加上 $1$。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2e5 + 10,M = 25,inf = 0x3f3f3f3f;
int T,n,q;
int arr[N],lg[N + 10];
string s;

struct ST{
	#define pot(x) (1 << x)
	
	int dp1[N][M],dp2[N][M];//dp1 维护最小值，dp2 维护最大值 
	
	inline void init(){
		for (re int j = 1;j <= lg[n];j++){
			for (re int i = 1;i <= n - pot(j) + 1;i++){
				dp1[i][j] = min(dp1[i][j - 1],dp1[i + pot(j - 1)][j - 1]);
				dp2[i][j] = max(dp2[i][j - 1],dp2[i + pot(j - 1)][j - 1]);
			}
		}
	}
	
	inline int query_Min(int l,int r){
		int x = lg[r - l + 1];
		return min(dp1[l][x],dp1[r - pot(x) + 1][x]);
	}
	
	inline int query_Max(int l,int r){
		int x = lg[r - l + 1];
		return max(dp2[l][x],dp2[r - pot(x) + 1][x]);
	}
	
	#undef pot
}st;

inline void Log(){
	lg[1] = 0;
	for (re int i = 2;i <= N;i++) lg[i] = lg[i / 2] + 1;
}

inline int sum(int l,int r){
	return arr[r] - arr[l - 1];
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	Log();
	while (T--){
		cin >> n >> q >> s;
		s = ' ' + s;
		for (re int i = 1;i <= n;i++){//转化权值 
			if (s[i] == '+') arr[i] = arr[i - 1] + 1;
			else arr[i] = arr[i - 1] - 1;
		}
		for (re int i = 1;i <= n;i++) st.dp1[i][0] = st.dp2[i][0] = arr[i];
		st.init();
		while (q--){
			int l,r;
			cin >> l >> r;
			int l1 = 1,r1 = l - 1;
			int l2 = r + 1,r2 = n;
			int Min = inf,Max = -inf;
			if (l1 <= r1){//避免出现 l = 1 的情况 
				Min = min(Min,st.query_Min(l1,r1));
				Max = max(Max,st.query_Max(l1,r1));
			}
			if (l2 <= r2){//避免出现 r = n 的情况 
				Min = min(Min,st.query_Min(l2,r2) - sum(l,r));
				Max = max(Max,st.query_Max(l2,r2) - sum(l,r));
			}
			if (Min == inf) Min = 0;//特判 l = 1 且 r = n 的情况 
			if (Max == -inf) Max = 0;
			if (Min <= 0 && 0 <= Max) cout << (Max - Min + 1) << "\n";
			else cout << (Max - Min + 2) << "\n";
		}
	}
	return 0;
}
```

---

## 作者：cppcppcpp3 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1473D)。

## Solution
先做一遍前缀和 $sum_i$，线段树维护其最值。

因为每个格子都只能 $+1$ 或 $-1$，所以只要求出值域端点，就可以知道出现过多少个不同的数（注意就算没有包含 $0$ 也要算上）。

因为每次仅忽略一个区间 $[l,r]$，所以最多会将操作分成左右两段。

分类讨论：

- $l = 1$，$r = n$。忽略整个序列，答案为 $1$。

- $l > 1$，$r = n$，只剩左边一段，查询 $[1,l-1]$ 的最值即可得出值域大小。

- $l = 1$，$r < n$，剩下右边一段，查询 $[r+1,n]$ 最值设为 $p$ 和 $q$，则实际值域为 $[p-sum_i,q-sum_i]$。

- $l > 1$，$r < n$，共左右两段。查询左右两段最值。由于忽略中间，前缀和从 $l-1$ 直接接向 $r+1$，所以右边的值域相应加上 $sum_{l-1}-sum_r$。统计时要去掉交集。

## Code
```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int N=2e5+5;
const int inf=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}

int n,m,a[N],s[N<<2][2];

#define ls (t<<1)
#define rs (t<<1|1)
#define md ((l+r)>>1)

il void pushup(int t){
	s[t][0]=max(s[ls][0],s[rs][0]),s[t][1]=min(s[ls][1],s[rs][1]);
} 

void build(int l,int r,int t){
	if(l==r){
		s[t][0]=s[t][1]=a[l];
		return;
	}
	build(l,md,ls),build(md+1,r,rs);
	pushup(t);
}

int querymax(int l,int r,int t,int x,int y){
	if(l>y || r<x) return -inf;
	if(l>=x&&r<=y) return s[t][0];
	return max(querymax(l,md,ls,x,y),querymax(md+1,r,rs,x,y));
}

int querymin(int l,int r,int t,int x,int y){
	if(l>y || r<x) return inf;
	if(l>=x&&r<=y) return s[t][1];
	return min(querymin(l,md,ls,x,y),querymin(md+1,r,rs,x,y));
}

il int U(int x,int y,int u,int v){
	if(x>u) swap(x,u),swap(y,v);
	if(y>=u-1) return min(y,v)-u+1;
	return 0;
}

il void solve(){
	n=wrd(),m=wrd();
	for(int i=1;i<=n;++i){
		char c; cin >> c;
		a[i]=a[i-1]+(c=='-' ? -1 : 1); //前缀和 
	} 
	build(1,n,1);
	
	while(m--){
		int l=wrd(),r=wrd();
		//分类讨论 
		if(l==1 && r==n){puts("1"); continue;}
		if(l==1){
			int t=-a[r];
			int y=t+querymax(1,n,1,r+1,n),x=t+querymin(1,n,1,r+1,n);
			int ans=y-x+1;
			if(y<0 || x>0) ans++;
			printf("%lld\n",ans); 
		}else if(r==n){
			int y=querymax(1,n,1,1,l-1),x=querymin(1,n,1,1,l-1);
			int ans=y-x+1;
			if(y<0 || x>0) ans++;
			printf("%lld\n",ans);
		}else{
			int p=a[l-1],q=a[r],t=p-q;
			int y=querymax(1,n,1,1,l-1),x=querymin(1,n,1,1,l-1);
			int v=t+querymax(1,n,1,r+1,n),u=t+querymin(1,n,1,r+1,n);
			int len=(y-x+1)+(v-u+1)-U(x,y,u,v);
			if((y<0 || x>0) && (v<0 || u>0)) ++len;
			printf("%lld\n",len);
		}
	}
}

main(){
	int T=wrd();
	while(T--) solve();
	return 0;
}
```

---

## 作者：Yizhixiaoyun (赞：0)

[博客园食用](https://www.cnblogs.com/yizhixiaoyun/p/17315972.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1473D)

## 题目分析

线段树、前缀和、$\text{ST}$ 表题解都有了，我补一发猫树题解吧。

由于每次操作只能将大小改变成跟原来差 $1$，所以只需要知道这段操作中的最大值和最小值，最后所求的答案的范围就被卡住了。对于每一次操作，我们把操作序列拦腰斩断，那么分别求两边的范围，最后减去重复的部分即可。

求最小值最大值部分可以用猫树维护，注意猫树空间要额外再开大一些。

## 贴上代码

```cpp
#include<bits/stdc++.h>
// #define int long long
#define debug puts("Shiina_Mashiro_kawaii")
#define ok puts("Yes")
#define no puts("No")
#define inf 1e9
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
const int maxn=4e5+5;
int n,m;
int lmin,lmax,rmin,rmax,ans;
int a[maxn],b[maxn];
int lg[maxn<<2];
string s;
struct cat_tree1{
    int cat[25][maxn];
    void init_tree(int o,int l,int r){
        int mid=(l+r)>>1;
        for(register int i=mid-1;i>=l;--i) cat[o][i]=max(cat[o][i+1],a[i]);
        for(register int i=mid+2;i<r+1;++i) cat[o][i]=max(cat[o][i-1],a[i]);
    }
    void build_tree(int o){
        int n=1;while(n<o) n<<=1;
        for(register int i=o;i<n;++i) a[i]=0;
        for(register int j=1,cnt=0;j<=n;j<<=1,++cnt){
            for(register int i=0;i<n;++i) cat[cnt][i]=a[i];
            for(register int i=0;i<n;i+=j) init_tree(cnt,i,i+j-1); 
        }
    }
    int query(int l,int r){
        int o=lg[l^r];
        if(l==r) return cat[o][l];
        else return max(cat[o][l],cat[o][r]);
    }
}ct1;
struct cat_tree2{
    int cat[25][maxn];
    void init_tree(int o,int l,int r){
        int mid=(l+r)>>1;
        for(register int i=mid-1;i>=l;--i) cat[o][i]=min(cat[o][i+1],b[i]);
        for(register int i=mid+2;i<r+1;++i) cat[o][i]=min(cat[o][i-1],b[i]);
    }
    void build_tree(int o){
        int n=1;while(n<o) n<<=1;
        for(register int i=o;i<n;++i) b[i]=0;
        for(register int j=1,cnt=0;j<=n;j<<=1,++cnt){
            for(register int i=0;i<n;++i) cat[cnt][i]=b[i];
            for(register int i=0;i<n;i+=j) init_tree(cnt,i,i+j-1); 
        }
    }
    int query(int l,int r){
        int o=lg[l^r];
        if(l==r) return cat[o][l];
        else return min(cat[o][l],cat[o][r]);
    }
}ct2;
inline void init(){
    n=read();m=read();cin>>s;s=" "+s;
    for(register int i=1;i<=n;++i){
    	if(s[i]=='+'){
    		a[i]=a[i-1]+1;b[i]=b[i-1]+1;
    	}
    	else{
    		a[i]=a[i-1]-1;b[i]=b[i-1]-1;
    	}
    }
    int len=2;while(len<n) len<<=1;
    len<<=1;
    for(register int i=1;i<=len;++i) lg[i]=lg[i>>1]+1;
    ct1.build_tree(n+1);ct2.build_tree(n+1);
}
inline void solve(){
	init();
	while(m--){
		int l=read(),r=read();lmin=lmax=rmin=rmax=0;
		if(l==1&&r==n){
			puts("1");continue;
		}
		if(l>1){
			lmax=max(ct1.query(1,l-1),0);
			lmin=min(ct2.query(1,l-1),0);
		}
		if(r<n){
			rmax=ct1.query(r+1,n)-(a[r]-a[l-1]);
			rmin=ct2.query(r+1,n)-(a[r]-a[l-1]);
		}
		if(lmax<rmin||rmax<lmin) ans=lmax-lmin+rmax-rmin+2;
        else if(lmax<=rmax) ans=(lmax-lmin)+(rmax-rmin)-lmax+max(lmin,rmin)+1;
        else ans=(lmax-lmin)+(rmax-rmin)-rmax+max(lmin,rmin)+1;
        printf("%d\n",ans);
	}
}
int main(){
    int T=read();
    while(T--) solve();
}
```

---

