# Three Activities

## 题目描述

Winter holidays are coming up. They are going to last for $ n $ days.

During the holidays, Monocarp wants to try all of these activities exactly once with his friends:

- go skiing;
- watch a movie in a cinema;
- play board games.

Monocarp knows that, on the $ i $ -th day, exactly $ a_i $ friends will join him for skiing, $ b_i $ friends will join him for a movie and $ c_i $ friends will join him for board games.

Monocarp also knows that he can't try more than one activity in a single day.

Thus, he asks you to help him choose three distinct days $ x, y, z $ in such a way that the total number of friends to join him for the activities ( $ a_x + b_y + c_z $ ) is maximized.

## 说明/提示

In the first testcase, Monocarp can choose day $ 2 $ for skiing, day $ 1 $ for a movie and day $ 3 $ for board games. This way, $ a_2 = 10 $ friends will join him for skiing, $ b_1 = 10 $ friends will join him for a movie and $ c_3 = 10 $ friends will join him for board games. The total number of friends is $ 30 $ .

In the second testcase, Monocarp can choose day $ 1 $ for skiing, day $ 4 $ for a movie and day $ 2 $ for board games. $ 30 + 20 + 25 = 75 $ friends in total. Note that Monocarp can't choose day $ 1 $ for all activities, because he can't try more than one activity in a single day.

In the third testcase, Monocarp can choose day $ 2 $ for skiing, day $ 3 $ for a movie and day $ 7 $ for board games. $ 19 + 19 + 17 = 55 $ friends in total.

In the fourth testcase, Monocarp can choose day $ 1 $ for skiing, day $ 4 $ for a movie and day $ 9 $ for board games. $ 17 + 19 + 20 = 56 $ friends in total.

## 样例 #1

### 输入

```
4
3
1 10 1
10 1 1
1 1 10
4
30 20 10 1
30 5 15 20
30 25 10 10
10
5 19 12 3 18 18 6 17 10 13
15 17 19 11 16 3 11 17 17 17
1 17 18 10 15 8 17 3 13 12
10
17 5 4 18 12 4 11 2 16 16
8 4 14 19 3 12 6 7 5 16
3 4 8 11 10 8 10 2 20 3```

### 输出

```
30
75
55
56```

# 题解

## 作者：hjqhs (赞：6)

显然先排个序。由于编号重合的问题，并不一定选择最大值。但至少也能选到次次大值，即最多编号退两个，三层循环枚举 $n$ 到 $n-2$ 即可。时间复杂度 $O(n \log n)$。如果扩展到 $k$ 个就是 $O(kn \log n + k^3)$。
```cpp
// Problem: D. Three Activities
// Contest: Codeforces - Codeforces Round 916 (Div. 3)
// URL: https://codeforces.com/problemset/problem/1914/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Created Time: 2023-12-22 17:15:26
// Author: hjqhs
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define per(i, a, b) for(int i = (a); i >= (b); -- i)
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

const int N = 100005;
const int INF = 0x3f3f3f3f;

int T;
int n, ans = -INF;
pii a[N], b[N], c[N];

void init() {
	ans = -INF;
}

void solve() {
	cin >> n;
	rep(i, 1, n) cin >> a[i].first, a[i].second = i;
	rep(i, 1, n) cin >> b[i].first, b[i].second = i;
	rep(i, 1, n) cin >> c[i].first, c[i].second = i;
	
	sort(a + 1, a + 1 + n), sort(b + 1, b + 1 + n), sort(c + 1, c + 1 + n);
	
	per(i, n, max(n - 2, 0) ) per(j, n, max(n - 2, 0) ) per(k, n, max(n - 2, 0) ) {
		if(a[i].second != b[j].second && a[i].second != c[k].second && b[j].second != c[k].second) 
			ans = max(ans, a[i].first + b[j].first + c[k].first);
	}
	
	cout << ans << '\n';
	
	return;
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	
	cin >> T;
	while(T --) init(), solve();
	
	return 0;
}
```

---

## 作者：infinite2021 (赞：0)

### 题解

直接做是立方级别的，显然超时。

我们会发现 $a,b,c$ 数组里的很多数都是没用的，又发现当 $a,b$ 已经选数了，那 $c$ 最坏会选到数组中的第三大数。

由此可见，每一个数组中我们只需要知道前三大的数及其位置即可，然后再去遍历，只有 $3^3$ 种情况。

核心代码如下

```cpp
for(int i=1;i<=n;i++)cin>>a[i].v,a[i].pos=i;
for(int i=1;i<=n;i++)cin>>b[i].v,b[i].pos=i;
for(int i=1;i<=n;i++)cin>>c[i].v,c[i].pos=i;
sort(a+1,a+n+1,cmp);
sort(b+1,b+n+1,cmp);
sort(c+1,c+n+1,cmp);
int res=0;
for(int i=1;i<=3;i++)
	for(int j=1;j<=3;j++)
		for(int k=1;k<=3;k++)
			if(a[i].pos!=b[j].pos&&b[j].pos!=c[k].pos&&a[i].pos!=c[k].pos)
				res=max(res,a[i].v+b[j].v+c[k].v);
```

---

## 作者：InversionShadow (赞：0)

给定三个数组 $a,b,c$，找三个互不相同的整数 $i,j,k$，使得 $a_i+b_j+c_k$ 的值最大。

---------------------

显然对 $a,b,c$ **从大到小**排序，暴力枚举最大的那几个所对应的 $i,j,k$ 互不相等即可。

小优化：可以在极少的次数中满足 $i,j,k$ 互不相等，如 $100$ 次。

代码实现的时候是从小到大排序，所以后面三重循环的时候要倒序枚举。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 100;

int n, t, k;

pair<int, int> a[N], b[N], c[N];

bool check(int x, int y, int z) {
	return !(x == y || y == z || x == z);
}

void solve() {
	cin >> n;
	int k = 0;
	for (int i = 1, x; i <= 3 * n; i++) {
		cin >> x;
		if (i <= n) {
			a[++k] = {x, k};
//			cout << '\n' << "i = " << i << "\n";
		} else if (i > n && i <= 2 * n) {
			if (i == n + 1) {
				k = 0;
			}
//			cout << "b" << "i = " << i << "\n";
			b[++k] = {x, k};
		} else {
			if (i == 2 * n + 1) {
				k = 0;
			}
			c[++k] = {x, k};
		}
	}
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	sort(c + 1, c + n + 1);
	int maxx = 0;
	for (int i = n; i >= max(0, n - 10); i--) {
		for (int j = n; j >= max(0, n - 10); j--) {
			for (int k = n; k >= max(0, n - 10); k--) {
				if (check(a[i].second, b[j].second, c[k].second)) {
					maxx = max(maxx, a[i].first + b[j].first + c[k].first);
				}
			}
		}
	} 
	cout << maxx << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
```

---

