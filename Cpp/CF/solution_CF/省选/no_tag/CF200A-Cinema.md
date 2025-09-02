# Cinema

## 题目描述

The capital of Berland has the only movie theater in the country. Besides, it consists of only one room. The room is divided into $ n $ rows, each row consists of $ m $ seats.

There are $ k $ people lined up to the box office, each person wants to buy exactly one ticket for his own entertainment. Before the box office started selling tickets, each person found the seat that seemed best for him and remembered it as a pair of coordinates $ (x_{i},y_{i}) $ , where $ x_{i} $ is the row number, and $ y_{i} $ is the seat number in this row.

It is possible that some people have chosen the same place, then when some people see their favorite seat taken in the plan of empty seats in the theater, they choose and buy a ticket to another place. Each of them has the following logic: let's assume that he originally wanted to buy a ticket to seat $ (x_{1},y_{1}) $ , then when he comes to the box office, he chooses such empty seat $ (x_{2},y_{2}) $ , which satisfies the following conditions:

- the value of $ |x_{1}-x_{2}|+|y_{1}-y_{2}| $ is minimum
- if the choice is not unique, then among the seats that satisfy the first condition, this person selects the one for which the value of $ x_{2} $ is minimum
- if the choice is still not unique, among the seats that satisfy the first and second conditions, this person selects the one for which the value of $ y_{2} $ is minimum

Your task is to find the coordinates of a seat for each person.

## 样例 #1

### 输入

```
3 4 6
1 1
1 1
1 1
1 2
1 3
1 3
```

### 输出

```
1 1
1 2
2 1
1 3
1 4
2 3
```

## 样例 #2

### 输入

```
4 3 12
2 2
2 2
2 2
2 2
2 2
2 2
2 2
2 2
2 2
2 2
2 2
2 2
```

### 输出

```
2 2
1 2
2 1
2 3
3 2
1 1
1 3
3 1
3 3
4 2
4 1
4 3
```

# 题解

## 作者：ChengJY_ (赞：5)

根据题意，若要填的位置已经被占了，那么就按照半径递增的曼哈顿距离圆填入。

我们发现，一个点周围最密集的情况下也只可能有 $k$ 个点，也就是说这个正方形的边长不会超过 $\sqrt k$ 。

所以我们需要找的只有对角线为 $\sqrt{2k}$ 的正方形，用并查集分别维护每一行的联通块的左右边界就可以在 $O(\sqrt{k})$ 的时间复杂度内实现单次查询。 

但是当 $m$ 很小的时候，左右边界被填满了，那么就会导致这时候不是一个正方形，需要遍历的行数增多。

但是这时候我们发现中间的一部分已经填满，不需要再填，那么我们也用并查集维护一下，这样可以保证查询的区间一定是一个正方形。

总时间复杂度 $O(k\sqrt{k})$ 。

[aclink](https://codeforces.com/contest/200/submission/168743887)



---

## 作者：__Hacheylight__ (赞：4)

题意：

有一个矩阵，输入几个(x,y),

如果(x,y)没有被占领，则输出(x,y),标记被占领

否则找一个与(x,y)曼哈顿距离最小的点且没有被占领的点输出，并标记被占领

分析：

很容易想出暴力，就是菱形着搜（就是在搜索包含该点（圈）的更大的圈上的点是否又满足的）

但是这样会被都是一个位置的~~毒瘤数据~~卡到O(NM)

思考。。。

怎么优化暴力？

在上面所讲的那个毒瘤数据中，我们的暴力是每次都要走过一遍菱形，这样一次一次搜错误的点非常浪费时间

于是我们把它记录一下

我们当然知道同一个菱形上的点到该点得曼哈顿距离相等。

d[x][y]表示这个点周围已经走了多少次

这里我们要考虑一个情况，就是包围情况，如果一个点的位置在另一个点选择的时候就已经访问了，那么我们就要通过另一个点更新该点

于是更新就可以了

```cpp
#include <set>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef pair <ll, ll> pll ;

const int N = 2010 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;

inline int read(){
    int X = 0, w = 0 ;
	char ch = 0 ;
    while (!isdigit(ch)) { w |= ch == '-' ; ch = getchar() ; }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar() ;
    return w ? - X : X ;
}

void write(int x){
     if (x < 0) putchar('-'), x = - x ;
     if (x > 9) write(x / 10) ;
     putchar(x % 10 + '0') ;
}

void print(int x) {
	cout << x << endl ;
	exit(0) ;
}

void PRINT(string x) {
	cout << x << endl ;
	exit(0) ;
}

void douout(double x){
	 printf("%lf\n", x + 0.0000000001) ;
}

int d[N][N], vis[N][N] ;
int n, m, ex, ey, k, x, y ;

bool check(int x, int y) {
	int l = max(x - d[x][y], 1), r = min(x + d[x][y], n) ;
	for (int i = l; i <= r; i++) {
		int t = d[x][y] - abs(i - x) ;
		if (y - t > 0 && !vis[i][y - t]) {
			ex = i ;
			ey = y - t ;
			return false ;
		}
		if (y + t <= m && !vis[i][y + t]) {
			ex = i ;
			ey = y + t ;
			return false ;
		}
	}
	return true ;
}

signed main(){
	scanf("%d%d%d", &n, &m, &k) ;
	while (k--) {
		scanf("%d%d", &x, &y) ;
		if (!vis[x][y]) {
			printf("%d %d\n", x, y) ;
			vis[x][y] = 1 ;
			continue ;
		}
		for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++) {
			if (x + i >= n || y + j >= m || x - i <= 0 || y - j <= 0) continue ;
			d[x][y] = max(d[x][y], d[x + i][y + j] - abs(i) - abs(j)) ;
		}
		while (check(x, y)) d[x][y]++ ;
		vis[ex][ey]++ ;
		printf("%d %d\n", ex, ey) ;
	}

}

/*
写代码时请注意：
	1.是否要开Long Long？数组边界处理好了么？
	2.实数精度有没有处理？
	3.特殊情况处理好了么？
	4.做一些总比不做好。
思考提醒：
	1.最大值和最小值问题可不可以用二分答案？
	2.有没有贪心策略？否则能不能dp？
*/

```

---

