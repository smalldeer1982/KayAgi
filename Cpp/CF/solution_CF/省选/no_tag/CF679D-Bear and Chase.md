# Bear and Chase

## 题目描述

Bearland has $ n $ cities, numbered $ 1 $ through $ n $ . There are $ m $ bidirectional roads. The $ i $ -th road connects two distinct cities $ a_{i} $ and $ b_{i} $ . No two roads connect the same pair of cities. It's possible to get from any city to any other city (using one or more roads).

The distance between cities $ a $ and $ b $ is defined as the minimum number of roads used to travel between $ a $ and $ b $ .

Limak is a grizzly bear. He is a criminal and your task is to catch him, or at least to try to catch him. You have only two days (today and tomorrow) and after that Limak is going to hide forever.

Your main weapon is BCD (Bear Criminal Detector). Where you are in some city, you can use BCD and it tells you the distance between you and a city where Limak currently is. Unfortunately, BCD can be used only once a day.

You don't know much about Limak's current location. You assume that he is in one of $ n $ cities, chosen uniformly at random (each city with probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679D/4e096649e26b2f57c3c1c5f2e21fdc5f3c577972.png)). You decided for the following plan:

1. Choose one city and use BCD there. 
  - After using BCD you can try to catch Limak (but maybe it isn't a good idea). In this case you choose one city and check it. You win if Limak is there. Otherwise, Limak becomes more careful and you will never catch him (you loose).
2. Wait $ 24 $ hours to use BCD again. You know that Limak will change his location during that time. In detail, he will choose uniformly at random one of roads from his initial city, and he will use the chosen road, going to some other city.
3. Tomorrow, you will again choose one city and use BCD there.
4. Finally, you will try to catch Limak. You will choose one city and check it. You will win if Limak is there, and loose otherwise.

Each time when you choose one of cities, you can choose any of $ n $ cities. Let's say it isn't a problem for you to quickly get somewhere.

What is the probability of finding Limak, if you behave optimally?

## 说明/提示

In the first sample test, there are three cities and there is a road between every pair of cities. Let's analyze one of optimal scenarios.

1. Use BCD in city $ 1 $ . 
  - With probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679D/11122857c8fbc4142ef5e22b839ee7f4cb432c56.png) Limak is in this city and BCD tells you that the distance is $ 0 $ . You should try to catch him now and you win for sure.
  - With probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679D/c171d3ec3c02b9089b571e24a262c7ab1c15c85e.png) the distance is $ 1 $ because Limak is in city $ 2 $ or city $ 3 $ . In this case you should wait for the second day.
2. You wait and Limak moves to some other city. 
  - There is probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679D/d4383517ebf44313369997271f7ef256a2d71555.png) that Limak was in city $ 2 $ and then went to city $ 3 $ .
  - ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679D/d4383517ebf44313369997271f7ef256a2d71555.png) that he went from $ 2 $ to $ 1 $ .
  - ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679D/d4383517ebf44313369997271f7ef256a2d71555.png) that he went from $ 3 $ to $ 2 $ .
  - ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679D/d4383517ebf44313369997271f7ef256a2d71555.png) that he went from $ 3 $ to $ 1 $ .
3. Use BCD again in city $ 1 $ (though it's allowed to use it in some other city). 
  - If the distance is $ 0 $ then you're sure Limak is in this city (you win).
  - If the distance is $ 1 $ then Limak is in city $ 2 $ or city $ 3 $ . Then you should guess that he is in city $ 2 $ (guessing city $ 3 $ would be fine too).

You loose only if Limak was in city $ 2 $ first and then he moved to city $ 3 $ . The probability of loosing is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679D/df23948d6bfff12ae417cb5328b837ccd2dc1824.png). The answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679D/0b7c81b1d3f961403f91c76191a20e8c20f3a753.png).

## 样例 #1

### 输入

```
3 3
1 2
1 3
2 3
```

### 输出

```
0.833333333333
```

## 样例 #2

### 输入

```
5 4
1 2
3 1
5 1
1 4
```

### 输出

```
1.000000000000
```

## 样例 #3

### 输入

```
4 4
1 2
1 3
2 3
1 4
```

### 输出

```
0.916666666667
```

## 样例 #4

### 输入

```
5 5
1 2
2 3
3 4
4 5
1 5
```

### 输出

```
0.900000000000
```

# 题解

## 作者：duyi (赞：1)

洛谷的 markdown 格式有点问题，请务必点进[我的博客](https://www.cnblogs.com/dysyn1314/p/14347422.html)查看本文。


# CF679D Bear and Chase

[题目链接](https://codeforces.com/contest/679/problem/D)

## 本题题解

记图的边集为 $E$。

先用 floyd 算法预处理出任意两点之间的距离。时间复杂度 $\mathcal{O}(n^3)$。

记两次查询的节点分别为 $a$, $b$，两次查询得到的结果分别为 $d_1, d_2$。

- 枚举 $a$。计算出第一步选 $a$ 时的答案。因为我们要求**最优策略**下的答案，所以对所有 $a$ 的情况取最大值即可。
  - 枚举 $d_1$。考虑所有距离 $a$ 为 $d_1$ 的节点，记为点集 $U = \{u | \mathrm{dis}(u, a) = d_1\}$。则得到回答 "$d_1$" 的概率是 $\frac{|U|}{n}$。求出 $d_1$ 的答案后，乘以这个概率，累加起来，就是当前 $a$ 的答案了。
    - 预处理出第二天罪犯来到 $v$ 的概率 $p(v)$。具体来说，$p(v) = \sum_{u\in U} \frac{1}{|U|}\cdot \frac{1}{\mathrm{deg(u)}} \cdot[(u, v)\in E]$。把所有 $p(v)\neq 0$ 的点（即与 $U$ 中至少一个点有连边的点）存起来，记为集合 $V = \{v | p(v)\neq 0\}$。
    - 现在已经得到了回答 $d_1$。考虑我们接下来的最优策略，是两种情况的较大者：要么在 $U$ 中随便猜一个点，并结束游戏，获胜的概率是 $\frac{1}{|U|}$。要么继续询问。
    - 如果继续询问。枚举接下来要询问的点 $b$。那这种情况下，获胜的概率就是所有 $b$ 的答案的最大值。对每个 $b$：
      - 枚举得到的回答 $d_2$。考虑距离 $b$ 为 $d_2$ 的点，记为集合 $W = \{w | \mathrm{dis}(w, b) = d_2\}$。在知道了 $d_2$ 后，我们有唯一的最优策略，且获胜的概率是 $\frac{\max_{v \in (V \cap W)}\{p(v)\}}{\sum_{v\in(V \cap W)} p(v)}$。同时，$d_2$ 发生的概率是 $\sum_{v\in(V \cap W)} p(v)$。所以 $b$ 的答案是：$\sum_{d_2} \frac{\max_{v \in (V \cap W)}\{p(v)\}}{\sum_{v\in(V \cap W)} p(v)}\times (\sum_{v\in(V \cap W)} p(v)) = \max_{v \in (V \cap W)}\{p(v)\}$。所以我们只需要在枚举 $d_2$ 之前，先枚举一遍 $v$，就能预处理出每个 $d_2$ 的答案。然后再扫描所有 $d_2$，把这些答案加起来。

上述的做法看起来是四重循环。但对于同一个 $a$，在所有 $d_1$ 下 $U$ 集合的大小之和为 $n$。$V$ 集合里的点与 $a$ 的距离要么是 $d_1 + 1$，要么是 $d_1 - 1$，所以 $V$ 集合的大小之和也是 $\mathcal{O}(n)$ 的。发现我们真正枚举的只有 $a, b, V$，时间复杂度是 $\mathcal{O}(n^3)$ 的。

具体可以见代码。

## 参考代码

```cpp
// problem: CF679D
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

const int MAXN = 400;
const int INF = 1e9;

int n, m;
vector<int> G[MAXN + 5];
int dis[MAXN + 5][MAXN + 5];

double p[MAXN + 5];
bool vis[MAXN + 5];
vector<int> calc_probability_for_each_city(const vector<int>& vec_u) {
	for (int i = 1; i <= n; ++i) {
		p[i] = 0;
		vis[i] = 0;
	}
	vector<int> vec_v;
	for (int i = 0; i < SZ(vec_u); ++i) {
		int u = vec_u[i];
		for (int j = 0; j < SZ(G[u]); ++j) {
			int v = G[u][j];
			p[v] += 1.0 / SZ(vec_u) / SZ(G[u]);
			if (!vis[v]) {
				vis[v] = 1;
				vec_v.push_back(v);
			}
		}
	}
	return vec_v;
}

double pmax[MAXN + 5];
double consider_tomorrow(const vector<int>& vec_v) {
	double res = 0;
	for (int i = 0; i < n; ++i) {
		pmax[i] = 0;
	}
	for (int b = 1; b <= n; ++b) { // 第二次询问的节点
		// 选好 b 后, 会问到一个距离 d2
		// 我们根据 d2 去选择最终的猜测: c. 即: 每个 d2 对应了一种选 c 的策略
		// 具体来说就是选择该 d2 里概率 p 最大的点作为 c
		// 所以此处先对每种距离 d2, 预处理出它对应的节点的 p 的最大值
		
		for (int i = 0; i < SZ(vec_v); ++i) {
			int v = vec_v[i];
			ckmax(pmax[dis[v][b]], p[v]);
		}
		
		double res_b = 0;
		for (int i = 0; i < SZ(vec_v); ++i) {
			int v = vec_v[i];
			int d2 = dis[v][b];
			
			res_b += pmax[d2];
			pmax[d2] = 0;
		}
		ckmax(res, res_b);
	}
	return res;
}
double ask_immediately(const vector<int>& vec_u) {
	return 1.0 / SZ(vec_u);
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			dis[i][j] = (i == j ? 0 : INF);
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
		dis[u][v] = dis[v][u] = 1;
	}
	for (int k = 1; k <= n; ++k) { // 中间点
		for (int i = 1; i <= n; ++i) { // 起点
			for (int j = 1; j <= n; ++j) { // 终点
				ckmin(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
	double ans = 0;
	for (int a = 1; a <= n; ++a) { // 第一次询问的节点
		double ans_a = 0;
		for (int d1 = 0; d1 < n; ++d1) { // 第一次得到的答案
			vector<int> vec_u;
			double p_d1 = 0;
			for (int u = 1; u <= n; ++u) if (dis[a][u] == d1) {
				vec_u.push_back(u);
				p_d1 += 1;
			}
			if (!SZ(vec_u))
				continue;
			
			p_d1 /= (double)n;
			
			double ans_a_d1 = 0;
			vector<int> vec_v = calc_probability_for_each_city(vec_u);
			ans_a_d1 = max(consider_tomorrow(vec_v), ask_immediately(vec_u));
			ans_a += p_d1 * ans_a_d1; // 有 p 的概率, 进入 d1 这种情况
			                          // 在 d1 的情况下, 选取最优策略能得到 ans_a_d1 这一答案
		}
		ckmax(ans, ans_a); // 选取最优策略
	}
	cout << setiosflags(ios :: fixed) << setprecision(10) << ans << endl;
	return 0;
}
```







---

