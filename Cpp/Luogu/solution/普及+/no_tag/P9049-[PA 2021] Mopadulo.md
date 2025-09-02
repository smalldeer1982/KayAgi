# [PA 2021] Mopadulo

## 题目描述

给定一个长度为 $n$ 的序列 $a$，求有多少种方案可以将 $a$ 划分成若干个区间，使得每段区间所有数的和模 $10^9 + 7$ 的结果为偶数。

由于结果可能很大，你只需要求出结果对 $10^9 + 7$ 取模的值。

## 说明/提示

#### 样例 #1 解释
三种划分方式如下：

- $[1, 4]$
- $[1, 2], [3, 4]$
- $[1], [2, 3], [4]$
#### 数据范围
对于 $100\%$ 的数据，$1 \leq n \leq 3 \times 10^5$，$0 \leq a_i < 10^9 + 7$。

## 样例 #1

### 输入

```
4
1000000006 1 5 1000000004```

### 输出

```
3```

# 题解

## 作者：wqc2011 (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P9049)

### 考虑暴力：
- $dp_i$ 为从 $1$ 至 $i$ 所有满足条件的方案数
- $ dp_i = \begin{cases} \begin{aligned} \sum _{j=0} ^{i-1} dp_j  & (s_i-s_j)\equiv 0\pmod2\end{aligned}\end{cases}$
- $dp_0 = 1$

暴力代码如下：

```
dp[0] = 1;
for(int i = 1;i <= n;i++){
    for(int j = 0;j < i;j++){
        if((s[i] - s[j] + inf) % inf % 2 == 0){
            dp[i] += dp[j];
            dp[i] %= inf;
        }
    }
}
```
### 优化
但这样会 $O(n^2)$ 超时，所以我们需要记录下从 $1 \to i - 1$ 的所有可行的方案数，有以下结论：
$s_i - s_j = \begin{cases} (s_i - s_j)\mod10^9+7 & s_j \le s_i 且 s_i&s_j 奇偶性相同\\ (s_i - s_j + 10^9 + 7)\mod 10^9 + 7 & s_j > s_i 且 s_i&s_j 奇偶性不同\end{cases}$

我们只需对 $s$ 数组建两棵棵线段树，一棵存奇，一棵存偶，每次求完 $dp_i$ 后单点修改，再进行区间查询记录答案即可。
### 代码附上——

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 300010;
const int inf = 1e9 + 7;
//unsigned long long
//cout << fixed << setprecision(3)
//cout << setw(5) <<
//continue
int a[maxn], dp[maxn], s[maxn], s2[maxn];
struct S {
	int l, r, sum;
} f[maxn * 4], f1[maxn * 4];
//偶线段树     奇线段树
void up(int x) {
	f[x].sum = f[x * 2].sum + f[x * 2 + 1].sum;
}
void built(int u, int l, int r) {
	f[u].l = l, f[u].r = r;
	if(l == r) return ;
	int mid = (l + r) / 2;
	built(u * 2, l, mid);
	built(u * 2 + 1, mid + 1, r);
}
void add(int u, int x, int p) {
	if(f[u].l == f[u].r) f[u].sum += p;
	else {
		int mid = (f[u].l + f[u].r) / 2;
		if(x <= mid) add(u * 2, x, p);
		else add(u * 2 + 1, x, p);
		up(u);
	}
}
int q(int u, int l, int r) {
	if(f[u].l >= l && f[u].r <= r) return f[u].sum;
	int mid = (f[u].l + f[u].r) / 2, ans = 0;
	if(l <= mid) ans += q(u * 2, l, r);
	if(r > mid) ans += q(u * 2 + 1, l, r);
	up(u);
	return ans;
}
void up1(int x) {
	f1[x].sum = f1[x * 2].sum + f1[x * 2 + 1].sum;
}
void built1(int u, int l, int r) {
	f1[u].l = l, f1[u].r = r;
	if(l == r) return ;
	int mid = (l + r) / 2;
	built1(u * 2, l, mid);
	built1(u * 2 + 1, mid + 1, r);
}
void add1(int u, int x, int p) {
	if(f1[u].l == f1[u].r) f1[u].sum += p;
	else {
		int mid = (f1[u].l + f1[u].r) / 2;
		if(x <= mid) add1(u * 2, x, p);
		else add1(u * 2 + 1, x, p);
		up1(u);
	}
}
int q1(int u, int l, int r) {
	if(f1[u].l >= l && f1[u].r <= r) return f1[u].sum;
	int mid = (f1[u].l + f1[u].r) / 2, ans = 0;
	if(l <= mid) ans += q1(u * 2, l, r);
	if(r > mid) ans += q1(u * 2 + 1, l, r);
	up1(u);
	return ans;
}
signed main() {
	//freopen("a.in", "r", stdin);
	//freopen("a.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		s[i] = s[i - 1] + a[i];
		s[i] %= inf;
		s2[i] = s[i];
	}
	sort(s2 + 1, s2 + 1 + n);
	int len = unique(s2 + 1, s2 + 1 + n) - s2 - 1;
        //离散化
	built(1, 1, len + 1);
	built1(1, 1, len + 1);
        //建树
	for(int i = 1; i <= n; i++) {
		int p = lower_bound(s2 + 1, s2 + 1 + len, s[i]) - s2;
                //找第一个小于等于s[i]的数的位置
		int p1 = upper_bound(s2 + 1, s2 + 1 + len, s[i]) - s2;
                //找第一个大于s[i]的数的位置
		if(s[i] % 2 == 0) {
			dp[i] = 1;
			dp[i] += q(1, 1, p) + q1(1, p1, len);
		} else {
			dp[i] += q1(1, 1, p) + q(1, p1, len);
		}
		dp[i] %= inf;
		if(s[i] % 2 == 0) {
			add(1, p, dp[i]);
		} else {
			add1(1, p, dp[i]);
		}
	}
	cout << dp[n] % inf;
	return 0;
}
```
## 感谢阅读！

---

## 作者：Usada_Pekora (赞：5)

看到区间和首先考虑作一个前缀和 $s$，注意是 $\bmod {10^9+7}$ 意义下的。

于是就变成了 $(s_i-s_{j-1})\bmod{10^9+7}$ 是不是一个偶数。

不妨令 $f_i$ 以 $i$ 结尾的前缀的答案。

考虑怎么转移，若 $s_{j-1}\leq s_i$ 且这两个东西奇偶性相同，显然 $f_j$ 是可以转移到 $f_i$ 上的；不一样的当然也可以贡献，不过要 $s_{j-1}\gt s_i$，因为此时 $\bmod$ 后的值是 $s_i-s_{j-1}+10^9+7$，因为奇偶性不一样，所以前面两项减完是奇数，再加上一个奇数就是偶数了。

此时是 $O(n^2)$ 的，注意到 $f_i$ 的转移事实上只跟值域相关，于是考虑经典套路：将所有的 $f_i$ 映射到值域上然后用一个数据结构维护。

维护两个 `BIT`，分别对应奇偶数即可，注意离散化的处理，需要保留之前的奇偶性。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5, mod = 1e9 + 7;
int n, m, a[N], sum[N], lsh[N], f[N];
inline int mod_add(int x, int y) {
	x += y;
	return x >= mod ? x - mod : x;
}
struct BIT {
	int c[N];
	inline void modify(int x, int k) {
		while (x <= m) {
			c[x] = mod_add(c[x], k);
			x += (x & -x);
		}
	}
	inline int query(int x) {
		int res = 0;
		while (x) {
			res = mod_add(res, c[x]);
			x -= (x & -x);
		}
		return res;
	}
} odd, even;
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		sum[i] = mod_add(sum[i - 1], a[i]);
	for (int i = 1; i <= n; i++)
		lsh[++m] = sum[i];
	lsh[++m] = 0;
	sort(lsh + 1, lsh + m + 1);
	m = unique(lsh + 1, lsh + m + 1) - lsh - 1;
	even.modify(1, 1);
	for (int i = 1; i <= n; i++) {
		int pos = lower_bound(lsh + 1, lsh + m + 1, sum[i]) - lsh;
		if (sum[i] & 1) {
			f[i] = mod_add(odd.query(pos), mod_add(even.query(m), mod - even.query(pos - 1)));
			odd.modify(pos, f[i]);
		} else {
			f[i] = mod_add(mod_add(odd.query(m), mod - odd.query(pos - 1)), even.query(pos));
			even.modify(pos, f[i]);
		}
	}
	cout << f[n] << endl;
	return 0;
}
```

---

## 作者：Expector_Hutch (赞：2)

> 正文部分[跳转](#正文开始)

> 特别声明：本文经修改后全部内容均由本人（我是真人）写作，无任何 AIGC 生成内容

先上代码：

```cpp
/*
给定一个长度为 n 的序列 a，求有多少种方案可以将 a
划分成若干个区间，使得每段区间所有数的和模 1e9 + 7 的结果为偶数。
由于结果可能很大，你只需要求出结果对 1e9 + 7 取模的值。
*/

#include <bits/stdc++.h>

using namespace std;

// MInt 类用于处理模 1e9 + 7 的整数运算
class MInt {
  private:
    static constexpr int M = 1e9 + 7; // 定义模数
    int val;                          // 存储当前值

  public:
    // 构造函数，初始化 MInt 对象
    MInt(int x) : val(x % M) {}
    MInt() : val(0) {}

    // 类型转换运算符，将 MInt 转换为 int 类型
    operator int() const { return val; }

    // 重载加法运算符
    MInt operator+(const MInt &other) const {
        return MInt((val + other.val) % M);
    }

    // 重载减法运算符
    MInt operator-(const MInt &other) const {
        return MInt((val + M - other.val) % M);
    }

    // 重载加法赋值运算符
    MInt &operator+=(const MInt &other) {
        val = (val + other.val) % M;
        return *this;
    }

    // 重载减法赋值运算符
    MInt &operator-=(const MInt &other) {
        val = (val + M - other.val) % M;
        return *this;
    }

    // 重载输入运算符
    friend istream &operator>>(std::istream &is, MInt &mint) {
        return is >> mint.val;
    }

    // 重载输出运算符
    friend ostream &operator<<(ostream &os, const MInt &mint) {
        return os << (mint.val % M);
    }
};

// BIT 类用于实现树状数组数据结构
struct BIT {
    vector<MInt> data; // 存储树状数组的数据
    BIT(ssize_t size) {
        data.resize(size, 0);
    } // 构造函数，初始化树状数组的大小

    // 更新树状数组中的元素
    void update(const ssize_t idx, const MInt val) {
        for (int i = idx; i < (signed)data.size(); i += i & -i) data[i] += val;
    }

    // 查询树状数组中的前缀和
    auto query(const ssize_t idx) {
        MInt r = 0;
        for (int i = idx; i > 0; i -= i & -i) r += data[i];
        return r;
    }
};

// 输入函数，读取序列并计算前缀和
auto input() {
    cin.tie(nullptr)->sync_with_stdio(false);
    ssize_t n;
    cin >> n;
    vector<MInt> s(n + 1);
    for (int i = 1; i <= n; ++i) cin >> s[i], s[i] += s[i - 1];
    return s;
}

// 解决函数，计算满足条件的方案数
auto solve(const vector<MInt> &s) {
    const ssize_t n = s.size() - 1;

    // 离散化 s 到 s_sorted
    vector<MInt> s_sorted = s;
    s_sorted.push_back(0);
    sort(s_sorted.begin() + 1, s_sorted.end());
    s_sorted.erase(unique(s_sorted.begin() + 1, s_sorted.end()),
                   s_sorted.end());

    vector<MInt> f(n + 1); // 动态规划状态
    BIT _odd(s_sorted.size()), _even(s_sorted.size());
    BIT g[2]{_odd, _even};
    g[1].update(1, 1); // 初始化 dp 条件
    for (int i = 1; i <= n; ++i) {
        auto idx = lower_bound(s_sorted.begin() + 1, s_sorted.end(), s[i]) -
                   s_sorted.begin(); // 查找 s[i] 在 s_sorted 中的位置
        // 状态转移
        f[i] = g[!(s[i] & 1)].query(idx) +
               g[s[i] & 1].query(s_sorted.size() - 1) -
               g[s[i] & 1].query(idx - 1);
        g[!(s[i] & 1)].update(idx, f[i]);
    }

    return f[n];
}

// 主函数，调用 solve 函数并输出结果
int main() {
    cout << solve(input()) << endl;
    return 0;
}
```

---
  
# 正文开始
  
显然动态规划。
  
记 $f_i$ 表示 $a$ 的前 $i$ 项，$s_i\equiv_{\mod 10^9+7}\sum_{j=1}^{i}a_j$，不难得出如下状态转移方程：
  
$$
f_i=\sum_{j=1}^{i}\left[s_{j-1}\underset{\mod 2}\equiv s_i\wedge s_{j-1}\leq s_i\right]f_j+\sum_{j=1}^{i}\left[s_{j-1}\underset{\mod 2}{\not\equiv} s_i\wedge s_{j-1}\geq s_i\right]f_j
$$

> 解释（以下讨论均在 $\mod {10^9+7}$ 条件下进行）：
>
> - 当 $s_i$ 与 $s_{j-1}$ 奇偶性相同且 $s_{j-1}\leq s_i$ 时，$s_i-s_{j-1}$ 为偶数，可转移
> - 当 $s_i$ 与 $s_{j-1}$ 偶奇性不同且 $s_{j-1}\geq s_i$ 时，$s_i-s_{j-1}$ 为偶数，可转移

时间复杂度为 $\mathcal{O}(n^2)$，接下来考虑优化。对于 $f_i$ 的两部分求和，对其三维条件（$j<i$，$s_i$ 与 $s_{j-1}$ 的奇偶性，$s_i$ 与 $s_{j-1}$ 的大小）拆分，不难发现 $j<i$ 可以由由小到大遍历保证，$s_i$ 与 $s_{j-1}$ 的奇偶性可以通过拆分出奇答案和偶答案来处理，$s_i$ 与 $s_{j-1}$ 的大小可以通过离散化 $s$ 来处理，最后求和可以利用树状数组维护，从而将时间复杂度优化至 $\mathcal{O}(n\log n)$。

---

