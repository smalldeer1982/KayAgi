# [ABC259D] Circumferences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc259/tasks/abc259_d

$ xy $ -平面上の $ N $ 個の円が与えられます。 $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、$ i $ 番目の円は点 $ (x_i,\ y_i) $ を中心とする半径 $ r_i $ の円です。

$ N $ 個の円のうち少なくとも $ 1 $ つ以上の円の円周上にある点のみを通って、点 $ (s_x,\ s_y) $ から点 $ (t_x,\ t_y) $ に行くことができるかどうかを判定してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3000 $
- $ -10^9\ \leq\ x_i,\ y_i\ \leq\ 10^9 $
- $ 1\ \leq\ r_i\ \leq\ 10^9 $
- $ (s_x,\ s_y) $ は $ N $ 個の円のうち少なくとも $ 1 $ つ以上の円の円周上にある
- $ (t_x,\ t_y) $ は $ N $ 個の円のうち少なくとも $ 1 $ つ以上の円の円周上にある
- 入力はすべて整数

### Sample Explanation 1

!\[\](https://img.atcoder.jp/abc259/7b850385b9d67dc150435ffc7818bd94.png) 例えば、下記の経路で点 $ (0,\ -2) $ から点 $ (3,\ 3) $ へ行くことができます。 - 点 $ (0,\ -2) $ から $ 1 $ つ目の円の円周上を反時計回りに通って点 $ (1,\ -\sqrt{3}) $ へ行く。 - 点 $ (1,\ -\sqrt{3}) $ から $ 2 $ つ目の円の円周上を時計回りに通って点 $ (2,\ 2) $ へ行く。 - 点 $ (2,\ 2) $ から $ 3 $ つ目の円の円周上を反時計回りに通って点 $ (3,\ 3) $ へ行く。 よって、`Yes` を出力します。

### Sample Explanation 2

!\[\](https://img.atcoder.jp/abc259/924efa40ff28e5d7125841da2710d012.png) 少なくとも $ 1 $ つ以上の円の円周上にある点のみを通って点 $ (0,\ 1) $ から点 $ (0,\ 3) $ に行くことはできないので `No` を出力します。

## 样例 #1

### 输入

```
4
0 -2 3 3
0 0 2
2 0 2
2 3 1
-3 3 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3
0 1 0 3
0 0 1
0 0 2
0 0 3```

### 输出

```
No```

# 题解

## 作者：Composite_Function (赞：4)

# 0-前言

有生之年，RMJ 活了

感谢为此付出的所有人

# 1-思路

题面也是我翻的，就不赘述了。

观察题目，发现对于两个圆，位置关系并没有那么重要，相对重要的，则是能不能通过一个圆连续地走到另一个圆上。

然后就问题转化成了无向图，即每个圆为节点，可否连续地走到为路径。所求就是 $(s_x, s_y)$ 所在的圆与 $(t_x, t_y)$ 所在的圆在图上是否联通。

注意是在圆的边缘上走，而不是圆内。

最后附上两个样例的图：

![](https://img.atcoder.jp/abc259/7b850385b9d67dc150435ffc7818bd94.png)
![](https://img.atcoder.jp/abc259/924efa40ff28e5d7125841da2710d012.png)

# 2-代码

```cpp
# include <bits/stdc++.h>
using namespace std;
# define int long long
const int N = 3e3 + 10;
int n, sx, sy, tx, ty;
int x[N], y[N], r[N];
bool check[N][N], s[N], t[N], vis[N];
void dfs(int pos) // 这里我选择的是用深搜查找，注意不用回溯
{
	if (t[pos] == true) {
		cout << "Yes" << endl;
		exit(0);
	} // 如果成立立即退出
	for (int i = 1; i <= n; ++i)
		if (check[pos][i] == true && vis[i] == false) 
			vis[i] = true, dfs(i);
	return;
}
signed main()
{
	cin >> n >> sx >> sy >> tx >> ty;
	for (int i = 1; i <= n; ++i) {
		cin >> x[i] >> y[i] >> r[i];
		int sdx = x[i] - sx, sdy = y[i] - sy;
		s[i] = (sdx * sdx + sdy * sdy == r[i] * r[i]); // 找过 s 的圆
		int tdx = x[i] - tx, tdy = y[i] - ty;
		t[i] = (tdx * tdx + tdy * tdy == r[i] * r[i]); // 找过 t 的圆
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			int dx = x[i] - x[j], dy = y[i] - y[j], dr = r[i] + r[j];
			int cal = max(r[i], r[j]) - min(r[i], r[j]);
			int dis = dx * dx + dy * dy;
			check[i][j] = (dis <= dr * dr && cal * cal <= dis); // 判断第 i, j 个圆是否联通
		}
	/*
	for (int i = 1; i <= n; ++i){
		for (int j = 1; j <= n; ++j)
			cout << check[i][j] << " ";
		cout << endl;
	}
	for (int i = 1; i <= n; ++i)
		cout << s[i] << " ";
	cout << endl;
	for (int i = 1; i <= n; ++i)
		cout << t[i] << " ";
	cout << endl;
	*/
	for (int i = 1; i <= n; ++i)
		if (s[i] == true && vis[i] == false) dfs(i);
	cout << "No" << endl;
	return 0;
}
```

---

## 作者：mi_Y13c (赞：1)

### 算法

#### (建图、图的连通性判定) $O(n^2)$

问从点 $(s_x,s_y)$ 能否到达点 $(t_x,t_y)$，等价于问这两点对应的圆是否连通

这里圆可以抽象成一个点，存在相交或相切关系的圆（内切或外切）可以进行连边，于是就变成了图上两点的连通性问题了

对于无向图的连通性问题可以用并查集来解决

判定点 $(x,y)$ 是否在圆上，只需验证这个点与圆点之间的距离是否等于半径 $r$

假设圆 $1$ 的圆心为 $O_1$ ，半径为 $r_1$ ，圆 $2$ 的圆心为 $O_2$ ，半径为 $r_2$ ，记 $d=dist(O_1,O_2)$ ，假设 $r_1<r_2$
                                        
则存在以下关系：

* 相交：$d<r_1+r_2$

* 相离：$d>r_1+r_2$

* 外切：$d=r_1+r_2$

* 内含：$d<r_2−r_1$

* 内切：$d=r_2−r_1$

注意精度问题

### 代码
```
#include <bits/stdc++.h>

#if __has_include(<atcoder/all>)

#include <atcoder/all>

using namespace atcoder;

#endif

#define rep(i, n) for (int i = 0; i < (n); ++i)

using std::cin;

using std::cout;

using std::swap;

using std::vector;

using ll = long long;

struct V {

    ll x, y;

    V(ll x=0, ll y=0): x(x), y(y) {}

};

int main() {

    int n;

    cin >> n;

    V s, t;

    cin >> s.x >> s.y;

    cin >> t.x >> t.y;

    vector<V> o(n);

    vector<int> r(n);

    rep(i, n) {

        cin >> o[i].x >> o[i].y >> r[i];

    }

    auto pow2 = [](ll x) { return x*x; };

    auto dist = [&](V a, V b) {

        return pow2(a.x-b.x) + pow2(a.y-b.y);

    };

    int si = 0, ti = 0;

    rep(i, n) {

        if (dist(s, o[i]) == pow2(r[i])) si = i; 

        if (dist(t, o[i]) == pow2(r[i])) ti = i; 

    }

    dsu uf(n);

    rep(i, n)rep(j, i) {

        ll d = dist(o[i], o[j]);

        ll r1 = r[i], r2 = r[j];

        if (r1 > r2) swap(r1, r2);

        if (d > pow2(r1+r2)) continue;

        if (d < pow2(r2-r1)) continue;

        uf.merge(i, j);

    }

    if (uf.same(si, ti)) puts("Yes");

    else puts("No");

    return 0;

}
```

---

