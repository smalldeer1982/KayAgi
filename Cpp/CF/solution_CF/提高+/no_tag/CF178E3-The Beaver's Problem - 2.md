# The Beaver's Problem - 2

## 题目描述

Offering the ABBYY Cup participants a problem written by the Smart Beaver is becoming a tradition. He proposed the following problem.

You are given a monochrome image, that is, an image that is composed of two colors (black and white). The image is given in raster form, that is, as a matrix of pixels' colors, and the matrix's size coincides with the size of the image.

The white color on the given image corresponds to the background. Also, the image contains several black geometric shapes. It is known that the image can contain only two types of shapes: squares and circles. Your task is to count the number of circles and the number of squares which the given image contains.

The squares on the image can be rotated arbitrarily. In addition, the image can possibly contain some noise arranged as follows: each pixel of the original image can change its color to the opposite with the probability of $ 20 $ %.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178E3/575cc300a436bc791f059ed1604954db020e4792.png) An example of an image that has no noise and the sides of the squares are parallel to the coordinate axes (two circles and three squares).   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178E3/5a255ee1bca061f5ff62a305107ac74540469a88.png) An example of an image that has no noise and the squares are rotated arbitrarily (two circles and three squares).   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178E3/6588309d80aee82245c95133dff3b167b5dbc7e6.png) An example of an image that has noise and the squares are rotated arbitrarily (one circle and three squares).

## 说明/提示

You are given a sample of original data for each difficulty level. The samples are available at http://codeforces.ru/static/materials/contests/178/e-samples.zip .

# 题解

## 作者：Halberd_Cease (赞：0)

见鬼题，E2、E3 过了 E1 没过（

首先考虑把每一个图形分离出来，有噪点可以用众数滤波，如果一个点周围点多数是黑的，那这个点应该就是黑的，反之是白的。

写法有不同，我习惯这么写：

```cpp
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            int res = mapp[i][j];
            for (int k = 0; k < 8; k++)
            {
                res += mapp[i+dx[k]][j+dy[k]];
            }
            if (res >= 5)
            {
                mapp_real[i][j] = 1;
            }
            else
            {
                mapp_real[i][j] = 0;
            }
        }
```

然后分离图形，直接做洪水填充即可。

考虑对于一个点集组成的图形，如何判断是正方形或者圆形，我的思路是找到图像中点，然后枚举每一个点找到最长半径。

这个半径对应圆的面积是 $\pi r^2$，对应正方形的面积是 $2r^2$，比较真实面积即点数更接近谁即可。

因为识别中出现识别的圆少一些，也没有样例或者输入数据反馈，我手动给圆的面积上了 $0.8$ 的参数，然后就可以过 2 和 3 了。

至于 1 的话，直接考虑边平不平，然后就可以了。

[submission](https://codeforces.com/contest/178/submission/252891427)

好了，你已经掌握了基本的图像识别技巧，[试试看](https://www.luogu.com.cn/problem/AT_birthday0410_x)

---

## 作者：shiyihang (赞：0)

## Update

修了一部分代码上的锅，重新提交。

- - -

此题与 [CF178E1](https://www.luogu.com.cn/problem/cf178e1) [CF178E2](https://www.luogu.com.cn/problem/cf178e2) 的唯一区别在于数据范围。

## 题意

给出一张黑白图像，求出图中圆形和方形的数量。

- 图像大小 $n$ 给定；
- 图像背景为白色，在输入中用 `0` 表示；
- 图形均为黑色，在输入中用 `1` 表示；
- 图像中可能存在噪声，如果存在，则对于每个原图中的像素，都有 $20\%$ 的概率转变为相反的颜色；
- 正方形可能会被任意旋转。

保证 $1000 \le n \le 2000$。

## 思路

先考虑对图像进行降噪，我们可以采用对多个像素取均值的方式去除大部分噪点。

如果有同学学过卷积相关的知识，就可以发现这能写成一个卷积核的形式（以 $5\times 5$ 为例）：

$$
\begin{bmatrix}
\frac{1}{25} & \cdots & \frac{1}{25} \\
\vdots & \ddots & \vdots \\
\frac{1}{25} & \cdots & \frac{1}{25}
\end{bmatrix}
$$

然后考虑进行边缘检测，方便判断图像边界，这一部分也可以写成一个卷积的形式（使用 [Laplacian 算子的八邻域模板](https://blog.csdn.net/Vermont_/article/details/108451563#7%20Laplacian%20%E7%AE%97%E5%AD%90)）：

$$
\begin{bmatrix}
-1 & -1 & -1 \\
-1 &  8 & -1 \\
-1 & -1 & -1 \\
\end{bmatrix}
$$

这个卷积会突出图像中变化剧烈的部分，以便于我们寻找图形，这可以直接使用 bfs 实现。

接下来就是判断图形是圆还是方的问题了。

方形由于会发生旋转，不方便判断，所以我们直接判断一个图形是否是圆。

我们可以根据“圆上各点到圆心距离相等”这一性质，先枚举出图形上所有的点（在 bfs 时直接记录即可），然后求出这些点的平均点，再算得平均点到所有点的距离的方差，若方差小于一个阈值就认为这个图形是圆，否则就是方形。

但是还有一点问题，在前面降噪的地方有可能留下一部分很小的连通块，可以加一个面积判断将其去掉。

代码如下（有点乱，见谅）：

```cpp
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
constexpr int maxn = 2e3 + 5;
int n, m;
bitset<maxn> mp[maxn];
bitset<maxn> tmp[maxn];
struct matrix {
	double data[107][107];
	int size;
	matrix() = default;
	explicit matrix(const int &x) : size(x) {
		for (int i = 0; i <= size; i++) {
			std::fill_n(data[i], size + 1, 0);
		}
	}
	auto operator[](const int &t) -> double * { return data[t]; }
	auto operator[](const int &t) const -> const double * { return data[t]; }
};
double dv[maxn][maxn];
auto main() -> int {
	ios::sync_with_stdio(false);
#define fin cin
	fin >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			char x;
			fin >> x;
			mp[i][j] = x == '1';
		}
		mp[i][0] = mp[i][n + 1] = true;
	}
	mp[0].set();
	mp[n + 1].set();
	matrix cov(9);
	for (int i = 1; i <= cov.size; ++i) {
		for (int j = 1; j <= cov.size; ++j) {
			cov.data[i][j] = 1.0 / (cov.size * cov.size);
		}
	}
	m = n - cov.size - 1;
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= m; ++j) {
			double &res = dv[i][j] = 0;
			for (int x = 1; x <= cov.size; ++x) {
				for (int y = 1; y <= cov.size; ++y) {
					res += static_cast<int>(mp[i + x][j + y]) * cov[x][y];
					res += static_cast<int>(mp[i + x][j + y]) * cov[y][x];
				}
			}
		}
	}
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= m; ++j) {
			mp[i][j] = dv[i][j] > 0.95;
		}
	}
	cov = matrix(3);
	cov.data[1][1] = -1;
	cov.data[1][2] = -1;
	cov.data[1][3] = -1;
	cov.data[2][1] = -1;
	cov.data[2][2] = 8;
	cov.data[2][3] = -1;
	cov.data[3][1] = -1;
	cov.data[3][2] = -1;
	cov.data[3][3] = -1;
	m = m - cov.size - 1;
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= m; ++j) {
			double &res = dv[i][j] = 0;
			for (int x = 1; x <= cov.size; ++x) {
				for (int y = 1; y <= cov.size; ++y) {
					res += static_cast<int>(mp[i + x][j + y]) * cov[x][y];
					res += static_cast<int>(mp[i + x][j + y]) * cov[y][x];
				}
			}
			res = fabs(res);
		}
	}
	for (int i = 1; i <= m; ++i) {
		mp[i].reset();
		mp[i].set(0);
		mp[i].set(m + 1);
	}
	mp[0].set();
	mp[m + 1].set();
	int area = 0;
	auto bfs = [&](int x, int y) {
		pair<double, double> avg;
		vector<pair<double, double>> edge;
		queue<pair<int, int>> q;
		q.emplace(x, y);
		mp[x][y] = true;
		while (!q.empty()) {
			auto [nowx, nowy] = q.front();
			q.pop();
			++area;
			int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
			for (auto [dx, dy] : d) {
				int tx = nowx + dx;
				int ty = nowy + dy;
				if (mp[tx][ty]) {
					continue;
				}
				if (dv[tx][ty] > 5) {
					edge.emplace_back(tx, ty);
					avg = {avg.first + tx, avg.second + ty};
					continue;
				}
				mp[tx][ty] = true;
				q.emplace(tx, ty);
			}
		}
		avg.first /= edge.size();
		avg.second /= edge.size();
		double aver = 0;
		double e = 0;
		auto getDis = [](pair<double, double> a, pair<double, double> b) {
			return sqrt(pow(a.first - b.first, 2) +
						pow(a.second - b.second, 2));
		};
		vector<double> a;
		a.resize(edge.size());
		for (int i = 0; i < edge.size(); ++i) {
			auto [tx, ty] = edge[i];
			aver += (a[i] = getDis(avg, {tx, ty}));
		}
		aver /= edge.size();
		for (auto v : a) {
			e += pow(v - aver, 2);
		}
		e /= a.size();
		return e;
	};
	bfs(1, 1);
	int res1 = 0;
	int res2 = 0;
	double eps = 0.85;
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (!mp[i][j] && dv[i][j] < 1) {
				area = 0;
				auto diff = bfs(i, j);
				if (area < 10) {
					continue;
				}
				if (diff < eps) {
					++res1;
				}
				else {
					++res2;
				}
			}
		}
	}
	// cout << res << "\n";
	cout << res1 << " " << res2 << "\n";
	return 0;
}
```

---

