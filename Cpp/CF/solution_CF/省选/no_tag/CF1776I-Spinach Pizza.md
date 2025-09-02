# Spinach Pizza

## 题目描述

Alberto 和 Beatrice 两兄妹必须一起吃菠菜披萨。但是他们都不喜欢吃菠菜，所以都想尽量少吃。

披萨的形状是一个由 $n$ 个位于平面的整数坐标的顶点 $(x_1, y_1), \, (x_2, y_2), \, \dots, \, (x_n, y_n)$ 组成的严格凸多边形。

兄妹俩决定以下面的方式吃掉披萨：从 Alberto 开始，兄妹轮流选择披萨剩余部分的一个顶点，吃掉由其两条相邻边决定的三角形（详情请查看样例解释）。在这样的前 $n - 3$ 轮，披萨上的顶点每轮会减少一个。在第 $(n - 2)$ 轮，披萨全部被吃掉，游戏结束。

假设 Alberto 和 Beatrice 以最优策略吃披萨，那么谁会吃掉**最多一半**披萨？你应该找出谁会赢，并帮他们适当地选择披萨片。请注意，如果 Alberto 和 Beatrice 都以最有策略吃披萨，那么他们最终吃掉的面积有可能正好是一半。

## 样例 #1

### 输入

```
4
0 0
6 1
5 3
1 4```

### 输出

```
-```

## 样例 #2

### 输入

```
6
0 0
2 0
3 2
2 4
0 4
-1 2```

### 输出

```
-```

## 样例 #3

### 输入

```
7
0 0
2 0
5 2
4 5
1 5
-1 4
-1 2```

### 输出

```
-```

# 题解

## 作者：5ab_juruo (赞：4)

结论：每次贪心选最小的三角形，这样选出来的三角形面积不降。

所以，当 $n$ 为奇数时，后手必胜，否则先手必胜。

证明：设最小的三角形是 $\text{ABC}$，其中 $\text B$ 是被删除的顶点，则只需说明包含边 $\text{AC}$ 的三角形都比 $\text{ABC}$ 小即可。

引理：以一条边为底的三角形中，面积最小的三角形的另一个顶点必然与这条边的一个顶点相邻。由多边形的凸性易证。

设 $\text{A,C}$ 除了与 $\text B$ 以外还分别和 $\text{D,E}$ 相邻，则任何包含 $\text{AC}$ 的新三角形都不会比 $\text{ADC,AEC}$ 大，而这两者又没 $\text{ADB,CEB}$ 大，因此也没有 $\text{ABC}$ 大。

三角形面积用叉积判一下就好了。

```cpp
typedef long long ll;
template<class T> const T INF = numeric_limits<T>::max() / 2;

struct point
{
	int x, y;
	point operator-(const point& rhs) const {
		return point{ x - rhs.x, y - rhs.y };
	}
};
vector<pair<int, point>> a;

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	
	cin >> n;
	for (int i = 0, x, y; i < n; i++)
	{
		cin >> x >> y;
		a.emplace_back(i, point{ x, y });
	}
	
	int lst = -1;
	if (n & 1)
	{
		cout << "Beatrice" << endl;
		cin >> lst, lst--;
	}
	else
		cout << "Alberto" << endl;
	
	auto erase = [&](int x) {
		for (auto p = a.begin(); p != a.end(); p++)
			if (p->first == x)
			{
				a.erase(p);
				break;
			}
	};
	auto cross = [&](point lhs, point rhs) {
		return 1ll * lhs.x * rhs.y - 1ll * rhs.x * lhs.y;
	};
	
	while (true)
	{
		erase(lst);
		
		int mxp = -1;
		ll mxs = INF<ll>;
		for (int i = 0; i < ssize(a); i++)
		{
			ll curv = cross(a[(i + 1) % ssize(a)].second - a[i].second,
			                a[(i - 1 + ssize(a)) % ssize(a)].second - a[i].second);
			if (curv < mxs)
				mxs = curv, mxp = a[i].first;
		}
		erase(mxp);
		cout << mxp + 1 << endl;
		
		if (ssize(a) <= 3)
			break;
		cin >> lst, lst--;
	}
	
	return 0;
}
```

---

