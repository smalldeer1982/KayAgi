# [GCJ 2018 #3] Raise the Roof

## 题目描述

人类学家们对某个古希腊几何学家社团有了令人惊讶的发现：他们对聚会的热爱丝毫不亚于对数学的热爱！事实上，随着年复一年的聚会规模不断扩大，他们不得不不断抬高舞厅的屋顶，以保持噪音在可接受的水平。

我们知道，他们舞厅的屋顶始终由恰好三根柱子的顶端支撑；这些柱子是从地板上垂直升起的无限细线段。每当社团想要抬高屋顶时，他们会先拆除现有的屋顶。然后，在一个还没有柱子的地方建造一根新柱子。最后，用新柱子和之前建造的柱子中最近的两根柱子的顶端作为支点，搭建新的屋顶。出于神秘的原因，任意三根柱子的底座都不会共线，任意四根柱子的顶端也不会共面。

每一块屋顶都是一个凸多边形，属于由三根支撑柱顶端确定的平面。对于每一根在支撑柱之前建造的柱子，屋顶不会与该柱子有任何交点，并且屋顶足够大，可以覆盖该柱子顶端的上方空间。屋顶不会接触地板。不同的屋顶形状不一定完全相同。

在一次考古发掘中，你找到了社团曾经建造过的所有 $N$ 根柱子，但没有发现任何屋顶。你想要确定一种可能的柱子建造顺序，使其符合上述规则。一个可能的顺序是对 $N$ 根柱子的一个排列，使得对于该排列的每一个长度不少于 4 的前缀，存在一块屋顶（凸多边形），它包含该前缀最后三根柱子的顶端，并且对于前缀中的其它每一根柱子，若其顶端为 $(x, y, h)$，则屋顶上存在一个点 $(x, y, z)$ 满足 $z > h$。

## 说明/提示

**样例解释**

下图展示了样例第 1 组数据的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/cefuy1j7.png)

**数据范围**

- $1 \leq T \leq 100$。
- $-10^6 \leq X_i \leq 10^6$，对所有 $i$。
- $-10^6 \leq Y_i \leq 10^6$，对所有 $i$。
- $1 \leq H_i \leq 10^6$，对所有 $i$。
- 任意不同的 $i, j, k$，$(X_i, Y_i)$、$(X_j, Y_j)$ 和 $(X_k, Y_k)$ 不共线。
- 任意不同的 $i, j, k, l$，$(X_i, Y_i, H_i)$、$(X_j, Y_j, H_j)$、$(X_k, Y_k, H_k)$ 和 $(X_l, Y_l, H_l)$ 不共面。

**测试点 1（7 分，公开）**

- $4 \leq N \leq 10$。

**测试点 2（19 分，隐藏）**

- $4 \leq N \leq 1000$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
5
-1 0 3
1 2 4
1 -2 4
3 1 3
3 -1 2
4
1 1 1
2 2 3
2 3 4
10 11 120
4
1 1 1
2 2 3
2 3 4
10 11 12```

### 输出

```
Case #1: 5 4 3 1 2
Case #2: 3 2 1 4
Case #3: 1 2 4 3```

# 题解

## 作者：ttmttntff (赞：0)

题意：在空间中给定 $n$ 个点，构造一个点的排列，使得对于每个长度不少于 $4$ 的前缀，该前缀最后三个点构成的平面在该前缀中其余所有点之上。

考虑从后往前构造这个排列。一开始的三个点构成的平面高于其余所有点，随后每次将构造的排列向前推进一位，即给定平面上的两点，寻找第三点使得这三点构成的平面高于其余所有点，并将这点删除。

现在讨论如何给定两点确定第三点。在这个构造中，一个重要的条件性质是，对于给定的两点，一定存在过两点的某个平面，高于其余所有点。因此，一个猜想是：遍历所有未被删除的点，如果当前平面低于该点，就用以该点作为第三点的平面替换当前平面。

可以从两个方面来说明猜想：1. 在用正确的第三点进行判定时，若当前的第三点不正确，则一定会被替换。2. 在用不正确的第三点进行判定时，若当前的第三点正确，则一定不会被替换。2 是明显的，1 的说明从略。因为不存在四点共面的情况，所以“正确的点”最多不超过两个。

也可以直观地理解该过程，即平面绕着给定的两点组成的“轴”旋转，“搭”在正确的第三点上。

另一种理解是，寻找一个垂直于给定的两点组成的“轴”的方向导数的绝对值最小的平面。

总之，最后是初始条件的构造。只需满足“对于给定的两点，一定存在过两点的某个平面，高于其余所有点”即可，所以可以构造两个极高的虚拟点作为初始条件。

时间复杂度 $O(n^2)$ 。

```cpp
//洛谷P13151
#include <iostream>
#include <vector>
using namespace std;

//单点
struct Point {
	int id;
	long double x, y, z;
	bool existed = true;

	Point() :id(0), x(0), y(0), z(0) {}

	Point(int _id, long double _x, long double _y, long double _z)
	{
		id = _id;
		x = _x, y = _y, z = _z;
	}

	//获得编号
	int get_id() const
	{
		return id;
	}

	//获得坐标
	void get_xyz(long double& _x, long double& _y, long double& _z) const
	{
		_x = x, _y = y, _z = z;
	}

	//检测点是否存在
	bool exist() const
	{
		return existed;
	}

	//删除点
	void erase()
	{
		existed = false;
	}
};

//平面(z=Ax+By+C)
struct Plane {
	long double A, B, C;

	Plane() :A(0), B(0), C(0) {}

	//三点式构造
	Plane(Point p1, Point p2, Point p3)
	{
		long double x1, y1, z1;
		p1.get_xyz(x1, y1, z1);
		long double x2, y2, z2;
		p2.get_xyz(x2, y2, z2);
		long double x3, y3, z3;
		p3.get_xyz(x3, y3, z3);

		//_Ax+_By+_Cz+_D=0 -> z=Ax+By+C
		long double _A = (y2 - y1) * (z3 - z1) - (z2 - z1) * (y3 - y1);
		long double _B = (z2 - z1) * (x3 - x1) - (x2 - x1) * (z3 - z1);
		long double _C = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
		long double _D = -_A * x1 - _B * y1 - _C * z1;
		A = -_A / _C;
		B = -_B / _C;
		C = -_D / _C;
	}

	//检测平面是否在单点上侧
	bool is_above(Point p) const
	{
		long double x, y, z;
		p.get_xyz(x, y, z);
		return A * x + B * y + C > z;
	}
};

//点集
struct Points {
	vector <Point> s;

	//加入单点
	void add(Point p)
	{
		s.push_back(p);
	}

	//删除单点
	void erase(Point p)
	{
		s[p.get_id() - 1].erase();
	}

	//通过两点计算第三点
	Point another(Point p1, Point p2)
	{
		Point p3;
		Plane plane;
		for (auto it = s.begin(); it < s.end(); it++)
		{
			Point p = *it;
			if (!p.exist() || plane.is_above(p))
				continue;
			p3 = p;
			plane = Plane(p1, p2, p3);
		}
		return p3;
	}
};

//构造答案序列
void solve(Points& points, vector <int>& seq)
{
	int n = (int)seq.size();
	Point p1, p2, p3;
	p1 = Point(0, 0, 0, 1e7);
	p2 = Point(0, 0, 1, 1e7);
	for (int i = n - 1; i >= 0; i--) {
		p3 = points.another(p1, p2);
		points.erase(p3);
		seq[i] = p3.get_id();
		p1 = p2;
		p2 = p3;
	}
}

int main()
{
	int T;
	cin >> T;
	for (int case_id = 1; case_id <= T; case_id++) {
		int n;
		cin >> n;
		Points points;
		for (int id = 1; id <= n; id++) {
			long double x, y, z;
			cin >> x >> y >> z;
			points.add(Point(id, x, y, z));
		}
		vector <int> seq(n);
		solve(points, seq);
		cout << "Case #" << case_id << ": ";
		for (int i = 0; i < n; i++)
			cout << seq[i] << " ";
		cout << endl;
	}
	return 0;
}
```

---

