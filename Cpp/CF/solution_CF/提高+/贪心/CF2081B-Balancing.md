# Balancing

## 题目描述

Ecrade 有一个整数数组 $a_1, a_2, \ldots, a_n$。保证对于每个 $1 \le i < n$，$a_i \neq a_{i+1}$。

Ecrade 可以通过若干次操作将数组变为严格递增的数组。

每次操作中，他可以选择两个整数 $l$ 和 $r$（$1 \le l \le r \le n$），并将 $a_l, a_{l+1}, \ldots, a_r$ 替换为任意 $r-l+1$ 个整数 $a'_l, a'_{l+1}, \ldots, a'_r$。替换后的数组需要满足以下约束：
- 对于每个 $l \le i < r$，$a'_i$ 和 $a'_{i+1}$ 之间的比较关系必须与原数组中 $a_i$ 和 $a_{i+1}$ 的比较关系相同。即，若原数组中 $a_i < a_{i+1}$，则替换后必须有 $a'_i < a'_{i+1}$；若原数组中 $a_i > a_{i+1}$，则替换后必须有 $a'_i > a'_{i+1}$；若原数组中 $a_i = a_{i+1}$，则替换后必须有 $a'_i = a'_{i+1}$。

Ecrade 想知道使数组严格递增所需的最少操作次数。由于问题有一定难度，请你帮助他！

## 说明/提示

第一个测试用例中，一种获得最少操作次数的方式为：
1. 第一次操作选择 $l = 2, r = 2$，将 $a'_2 = 4$，此时数组变为 $[3, 4, 1]$；
2. 第二次操作选择 $l = 1, r = 2$，将 $a'_1 = -1, a'_2 = 0$，此时数组变为 $[-1, 0, 1]$。

第二个测试用例中，一种获得最少操作次数的方式为：
1. 第一次操作选择 $l = 2, r = 3$，将 $a'_2 = 4, a'_3 = 5$，此时数组变为 $[3, 4, 5]$。

第三个测试用例中，一种获得最少操作次数的方式为：
1. 第一次操作选择 $l = 2, r = 3$，将 $a'_2 = -1, a'_3 = 1$，此时数组变为 $[-2, -1, 1, 2]$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3
3 2 1
3
3 1 2
4
-2 -5 5 2
7
1 9 1 9 8 1 0```

### 输出

```
2
1
1
3```

# 题解

## 作者：Butterfly_qwq (赞：3)

我们设 $\Delta(x)$ 为在 $x$ 状态下，相邻逆序对的值。

也就是说，$\Delta(x)=\sum\limits_{i=1}^n[a_i>a_{i+1}]$。

然后你考虑每次操作显然最多只能消去左端点和右端点的两个相邻逆序对，也就是说，经过一次操作后，$\Delta(x)$ 至多减少 $2$，于是答案下界是 $\lceil\frac{\Delta(x)}{2}\rceil$。

这时候你瞎枚举几个答案发现答案最多比这个下界多 $1$，我们尝试来证一下。

单增区间段是 $\Delta(x)+1$，设其为 $s$。

首先一个很显然的事情就是每次操作的单位是一整个单增区间段，这个易证。

如果单增区间段有偶数个，那么你考虑每次这么操作：

1. 把第一个区间段和第二个区间段一起，尽可能变小；
2. 这时候二、三区间段会变成一个区间段，于是你把二、三、四放一起，尽可能变小，记得要顺便把第二个区间段搞大一点；
3. 然后把四、五、六放一起搞，然后是六、七、八放一起……就可以取到下界。

如果有奇数个，你考虑这么操作：

1. 如果中间空间不够放，把第一个区间尽可能的减小，在这种情况下，答案会比下界多 $1$；
2. 然后你和偶数段一样操作，先把二、三放到下界，然后搞三、四、五，然后搞五、六、七，然后七、八、九，于是这样可以刚好卡到下界（如果上一步多用了一步则会比下界多 $1$）。

然后你就会了。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,s,l,r,a[200005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;s=l=0;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<n;i++)if(a[i]>a[i+1])
		{
			s++;r=i+1;
			if(!l)l=i;
		}
		if(s%2||(s&&a[r]-a[l]<r-l))cout<<s/2+1<<'\n';
		else cout<<s/2<<'\n';
	}
}
```

---

## 作者：bsdsdb (赞：1)

题意：$\{a_i\}_{i=1}^n$，不存在 $a_i=a_{i+1}$。一次操作可以选择 $l,r$，自主决定一个整数序列 $\{{a'}_i\}_{i=l}^r$，满足 $\forall i\in[l,r):\gdef\sgn{\operatorname{sgn}}\sgn({a'}_{i+1}-{a'}_i)=\sgn(a_{i+1})-\sgn(a_i)$，然后用 ${a'}_{[l,r]}$ 替换 $a_{[l,r]}$ 问最少多少次操作可以把 $a$ 变成严格单调递增。

称「下降数 $d$」为 $[a_i>a_{i+1}]$ 的数量。感觉结论不是很好想啊，思路也不好表述，就多造几个样例就出来了。

引理 1：$d=0$ 时答案为 $0$。

> 显然。

引理 2：一次操作最多将 $d$ 减少 $2$。

> 操作 $(l,r)$ 只有可能删掉 $l-1,r$ 两个下降点。

推论 1：答案的下界为 $\left\lceil\frac d2\right\rceil$。

引理 3：当 $d\ge 3$ 时，一次操作可以将 $d$ 减少 $2$。

> 如图：
>
> ![](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/ezpeoirw)

引理 4：如果每次操作都让 $d$ 减少 $2$，那么最左边的へ的拐点处高度动不了。右边同理。

> 如果想让他动，因为他是最左边的，再左边没有下降点了，$d$ 也就减不了 $2$ 了。

引理 5：当 $d=1$ 时答案上界为 $1$。

> 如图：
>
> ![](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/gl36p4x2)

推论 2：$d=1$ 时答案为 $1$。

推论 3：$2\nmid d$ 时答案为 $\left\lceil\frac d2\right\rceil$。

引理 6：当 $d=2$，有 $l\neq r-1,a_{l}\ge a_{l+1},a_{r-1}\ge a_r$ 时，答案上界为 $1$。

> 如图：
>
> ![](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/c3bzzg3n)

推论 4：此时答案为 $1$。

推论 5：$2\mid d,a_{l}\ge a_{l+1},a_{r-1}\ge a_r$，$l$ 是最左边下降点，$r$ 是最右边下降点往右一个（就是图中加粗的右边的黑点）时，答案为 $\frac d2$。

引理 7：当 $d=2$ 但不符合引理 6 中所述其他条件时，答案为 $2$。

> ![](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/rpjlczyt)
>
> 里面全是上升，最理想情况压到全 $+1$。此时左右两点平均斜率至少为 $1$，矛盾，因此一次操作压不进去。
>
> 两次操作很简单，左边点一按，右边点一抬就 ok 了。

引理 8：符合引理 7 所述情况但 $2\mid d,d>2$ 时答案下界为 $\frac d2+1$。

> 等价于 $\frac d2$ 是不行的。如果一直按引理 2 的方法调整，那么根据引理 4，最后肯定面临一个引理 7 的情况。

推论 6：此情况下答案为 $\frac d2+1$。

结合引理 1，推论 3，推论 5，推论 6 可得出答案。

```cpp
#include <bits/stdc++.h>
using namespace std; 
namespace heead {
	// types
	using i32 = int32_t;
	using i64 = int64_t;
	using i128 = __int128;
	using f32 = float;
	using f64 = double;
	using f128 = __float128;
	using ll = long long;
	using ldb = long double;
	#define umap unordered_map
	#define uset unordered_set
	#define prque priority_queue
	#define pi32 pair<i32, i32>
	#define pi64 pair<i64, i64>
	#define pll pair<ll, ll>
	// functions
	#define emp emplace
	#define empb emplace_back
	#define empf emplace_front
	#define mkp make_pair
	mt19937_64 rd(chrono::high_resolution_clock().now().time_since_epoch().count());
	// constants
	#define csep constexpr
	csep i64 inf = 0x3f3f3f3f3f3f3f3fll;
	csep f64 eps = 1e-7;
	csep f64 PI = 3.14159265358979323846264338327950288419716939937510582097;
	// non-std type io
	istream& operator>>(istream& in, i128& x) {
		string input;
		in >> input;
		x = 0;
		for (char c : input) {
			if (c == '-') {
				continue;
			}
			x = (x << 3) + (x << 1) + (c & 15);
		}
		if (input[0] == '-') {
			x *= -1;
		}
		return in;
	}
	ostream& operator<<(ostream& out, i128 x) {
		stack<char> output;
		if (x < 0) {
			out << '-';
			x *= -1;
		}
		if (!x) {
			out << '0';
			return out;
		}
		while (x) {
			output.emp((x % 10) | 48);
			x /= 10;
		}
		while (!output.empty()) {
			out << output.top();
			output.pop();
		}
		return out;
	}
	istream& operator>>(istream& in, f128& x) {
		string input;
		in >> input;
		f128 mul = 1;
		i64 id = (input.find('.') == string::npos ? input.length() : input.find('.')) - (input[0] == '-') - 1;
		for (ll i = 1; i <= id; ++i) {
			mul *= 10;
		}
		x = 0;
		for (char c : input) {
			if (c == '.' || c == '-') {
				continue;
			}
			x += mul * (c & 15);
			mul /= 10;
		}
		if (input[0] == '-') {
			x *= -1;
		}
		return in;
	}
	csep i64 F128ACC = 12;
	ostream& operator<<(ostream& out, f128 x) {
		// negative case
		if (x < 0) {
			out << '-';
			x *= -1;
		}
		// integer part
		out << i128(x);
		x -= i128(x);
		// fractional part
		for (ll i = 1; i <= F128ACC; ++i) {
			x *= 10;
		}
		if (!x) {
			return out;
		}
		out << '.';
		// prefix 0
		i128 y = x;
		i128 _y = y;
		for (ll i = 1; i <= F128ACC; ++i) {
			if (!_y) {
				out << '0';
			}
			_y /= 10;
		}
		// suffix 0
		while (y && y % 10 == 0) {
			y /= 10;
		}
		// out
		out << i128(y);
		return out;
	}
}
using namespace heead;

ll n, a[1000005];
vector<pll> inv;

void init() {
	fill_n(a, n + 4, inf);
	inv.clear();
}
int mian() {
	cin >> n;
	a[n + 1] = inf;
	for (ll i = 1; i <= n; ++i) cin >> a[i];
	ll l = 1, ans = 0;
	for (ll i = 2; i <= n; ++i) {
		if (a[i - 1] > a[i]) {
			inv.empb(mkp(i - 1, i));
		}
	}
	if (inv.size() <= 1) {
		cout << inv.size() << endl;
		return 0;
	}
	if (inv.size() % 2) {
		cout << inv.size() / 2 + 1 << endl;
	} else {
		if (inv.back().second - inv[0].first <= a[inv.back().second] - a[inv[0].first]) {
			cout << inv.size() / 2 << endl;
		} else {
			cout << inv.size() / 2 + 1 << endl;
		}
	}
	return 0;
}

#define FASTIO
int main() {
	#ifdef FASTIO
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	#endif
	i32 T;
	cin >> T;
	while (T--) init(), mian(), init();
	return 0;
}
```

---

