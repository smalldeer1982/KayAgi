# [GCJ 2019 Finals] Juggle Struggle: Part 1

## 题目描述

本题的前两段（不包括本段）与“Juggle Struggle: Part 2”完全相同。除此之外，这两道题可以独立解决；你无需阅读或解决其中一道题即可理解或解决另一道题。

作为 Graceful Chainsaw Jugglers 团队的经理，你决定让表演更加精彩。你不再让每位杂技演员单独抛接自己的电锯，而是让他们两两组队，每对互相抛接电锯。在这种新表演中，将有 $2 \times \mathbf{N}$ 名杂技演员同时登台，被分为 $\mathbf{N}$ 对，每位杂技演员恰好属于一对。

你认为，如果不同对的杂技演员所抛接的电锯有相互碰撞的风险，表演会更加惊险。设舞台为一个二维平面，连接一对杂技演员位置的直线段称为该对的抛接路径。当两条抛接路径相交时，称这两对杂技演员的电锯存在碰撞风险。我们称杂技演员的空间位置及其配对方式为一种“安排”。如果每两对杂技演员的电锯都存在碰撞风险，则称该安排为“壮观的安排”。

经过长时间的思考和设计，你想出了一个壮观的安排，并把杂技演员在舞台上的位置和配对方式记录在纸上。不幸的是，一次失误的电锯抛掷把纸张切成了两半，你丢失了记载配对方式的那一半。由于舞台布景已经根据杂技演员的位置设计好，这些位置无法更改。距离备受期待的首演只剩下几个小时，你需要重新找到一个壮观的安排！给定每位杂技演员在二维舞台上的位置，请找出一种配对方式，使得该安排是壮观的。

## 说明/提示

**样例解释**

在样例第 1 个测试用例中，杂技演员的位置构成一个正方形。唯一的有效方案是将第 1 位与第 3 位配对，第 2 位与第 4 位配对。

**数据范围**

- $-10^9 \leq \mathbf{X}_\mathbf{i} \leq 10^9$，对所有 $i$ 成立。
- $-10^9 \leq \mathbf{Y}_\mathbf{i} \leq 10^9$，对所有 $i$ 成立。
- 任意三位杂技演员的位置不共线。（这也意味着没有两位杂技演员处于同一位置。）
- 至少存在一种配对方式，使得最终安排是壮观的。

**测试点 1（5 分，公开）**

- 时间限制：20 秒。
- $1 \leq \mathbf{T} \leq 100$。
- $2 \leq \mathbf{N} \leq 100$。

**测试点 2（30 分，隐藏）**

- 时间限制：60 秒。
- $1 \leq \mathbf{T} \leq 10$。
- $2 \leq \mathbf{N} \leq 10^5$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2
-1 -1
-1 1
1 1
1 -1
3
1 2
2 1
2 3
3 1
3 3
4 2
3
7 1
1 1
7 2
5 5
3 5
1 2```

### 输出

```
Case #1: 3 4 1 2
Case #2: 6 5 4 3 2 1
Case #3: 5 4 6 2 1 3```

# 题解

## 作者：ttmttntff (赞：0)

用一条直线将平面划分为两个区域，则这两个区域内部不可能同时都有连线。因为：若两个区域内部同时都有连线，则这些连线一定不相交。

若这两个区域内所含的点数相同，则这两个区域内部都不可能有连线。因为：若任意一个区域内部有连线，则另一个区域也一定内部有连线，而这与第一段的结论矛盾。

用两条直线将平面划分成四个区域，若每条直线所划分出来的两个区域的点数相同，则连线一定只存在于两个对角区域之间。因为：相邻区域在其中某条直线的同侧，不可能有连线。

所以我们的初步思路是：每次用两条直线划分平面，因为连线只存在于对角区域之间，问题的规模就得以缩小。现在的问题是：怎么使得每次问题的规模稳定缩小一半？

猜想：已固定一条直线时，四个区域所包含的点数都关于另一条直线与该直线的夹角单调。也就是说，两条直线夹角越大，夹成区域的点数越多。

因此可以使用二分法寻找另一条直线的夹角，使得四个区域的点数都接近 $n/4$ 。

注意对角区域的点数必须相等。由于题目保证解一定存在，所以一定可以找到这样的夹角。

时间复杂度 $O(n\operatorname{log}^2n)$ ，注意常数优化。

```cpp
//洛谷P13126
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const long double PI = (long double)3.141592653589793;
const long double HALF_PI = PI / 2;

//点
struct Point {
	long double x, y;
	int id;
	Point(long double _x, long double _y, int _id)
	{
		x = _x, y = _y;
		id = _id;
	}
	//获得坐标
	void get_xy(long double& _x, long double& _y) const
	{
		_x = x, _y = y;
	}
	//获得id
	void get_id(int& _id) const
	{
		_id = id;
	}
	//计算Ax+By
	long double f(long double A, long double B) const
	{
		return A * x + B * y;
	}
};

//直线(Ax+By+C=0)
struct Line {
	long double A, B, C;
	//普通构造方式
	Line(long double _A, long double _B, long double _C)
	{
		A = _A, B = _B, C = _C;
	}
	//构造倾斜角为theta的直线
	Line(long double theta)
	{
		*this = Line(sin(theta), -cos(theta), 0);
	}
	//计算点在直线上还是下
	int is_pabove(Point p) const
	{
		long double x, y;
		p.get_xy(x, y);
		if (B > 0)
			return A * x + B * y + C > 0;
		return A * x + B * y + C < 0;
	}
};

//点集
struct Points {
	vector <Point> p;
	//插入点
	void insert(Point other)
	{
		p.push_back(other);
	}
	//返回容量
	int size() const
	{
		return (int)p.size();
	}
	//返回点id
	int pid(int i)
	{
		int id;
		p[i].get_id(id);
		return id;
	}
	//融合点集
	void merge(Points& other)
	{
		p.insert(p.end(), other.p.begin(), other.p.end());
	}
	//在点集s计算Ax+By意义下的第k小
	long double get_kmin(const vector<Point>& s, int k, long double A, long double B)
	{
		int n = (int)s.size();
		long double m = s[rand() % n].f(A, B);
		int cnt1 = 0, cnt2 = 0;
		for (int i = 0; i < n; i++)
			cnt1 += (s[i].f(A, B) < m),
			cnt2 += (s[i].f(A, B) <= m);
		if (cnt1 < k && cnt2 >= k)
			return m;
		vector <Point> s_;
		for (int i = 0; i < n; i++) {
			if (cnt2<k && s[i].f(A, B)>m)
				s_.push_back(s[i]);
			if (cnt1 >= k && s[i].f(A, B) < m)
				s_.push_back(s[i]);
		}
		if (cnt2 < k)
			k -= cnt2;
		return get_kmin(s_, k, A, B);
	}
	//计算点集在Ax+By意义下的中位数
	long double median_AB(long double A, long double B)
	{
		int n = (int)p.size();
		long double median_AB = (get_kmin(p, n / 2, A, B) + get_kmin(p, n / 2 + 1, A, B)) / 2;
		return median_AB;
	}
	//用两条直线将点集里的点分成四部分
	//p2与p3,p1与p4对角
	void split(Line l1, Line l2, Points& p1, Points& p2, Points& p3, Points& p4)
	{
		for (int i = 0; i < (int)p.size(); i++) {
			switch ((l1.is_pabove(p[i]) << 1) + l2.is_pabove(p[i])) {
			case 0:
				p1.insert(p[i]);
				break;
			case 1:
				p2.insert(p[i]);
				break;
			case 2:
				p3.insert(p[i]);
				break;
			case 3:
				p4.insert(p[i]);
				break;
			}
		}
	}
};

//确保解存在
static void solve(Points p, vector<int>& match)
{
	int n = p.size();
	if (n == 0)
		return;
	if (n == 2) {
		int u = p.pid(0), v = p.pid(1);
		match[u] = v, match[v] = u;
		return;
	}
	long double theta = static_cast<long double>(rand()) / RAND_MAX * PI - HALF_PI;//[-PI/2,PI/2)
	Line l1 = Line(theta);
	l1.C = -p.median_AB(l1.A, l1.B);

	long double l = 0, r = PI;
	long double m = (l + r) / 2;
	while (r - l > 1e-13) {
		Line l2 = Line(theta + m);
		l2.C = -p.median_AB(l2.A, l2.B);
		Points p1, p2, p3, p4;
		p.split(l1, l2, p1, p2, p3, p4);
		if (theta + m > HALF_PI) {
			swap(p1, p2);
			swap(p3, p4);
		}
		int p2_size = p2.size(), p3_size = p3.size();
		if (p2_size < n / 4 || (p2_size == n / 4 && p3_size < n / 4))
			l = m;
		else if (p2_size > n / 4 || (p2_size == n / 4 && p3_size > n / 4))
			r = m;
		else if (p2_size == n / 4 && p3_size == n / 4)
			break;
		m = (l + r) / 2;
	}

	long double delta = m;
	Line l2 = Line(theta + delta);
	l2.C = -p.median_AB(l2.A, l2.B);
	Points p1, p2, p3, p4;
	p.split(l1, l2, p1, p2, p3, p4);
	p1.merge(p4), p2.merge(p3);
	solve(p1, match), solve(p2, match);
}

int main()
{
	int T, case_id = 1;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		Points p;
		for (int i = 0; i < n * 2; i++) {
			long double x, y;
			cin >> x >> y;
			p.insert(Point(x, y, i));
		}
		vector<int> match(n * 2);
		solve(p, match);
		cout << "Case #" << case_id++ << ": ";
		for (int i = 0; i < n * 2; i++)
			cout << match[i] + 1 << " ";
		cout << endl;
	}
	return 0;
}
```

---

