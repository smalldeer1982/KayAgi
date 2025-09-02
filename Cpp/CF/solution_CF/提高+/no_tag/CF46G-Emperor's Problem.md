# Emperor's Problem

## 题目描述

It happened at the times of the Great Berland Empire. Once the Emperor dreamt that the Messenger from the gods ordered to build a temple whose base would be a convex polygon with $ n $ angles. Next morning the Emperor gave the command to build a temple whose base was a regular polygon with $ n $ angles. The temple was built but soon the Empire was shaken with disasters and crop failures. After an earthquake destroyed the temple, the Emperor understood that he somehow caused the wrath of gods to fall on his people. He ordered to bring the wise man. When the wise man appeared, the Emperor retold the dream to him and asked "Oh the wisest among the wisest, tell me how could I have infuriated the Gods?". "My Lord," the wise man answered. "As far as I can judge, the gods are angry because you were too haste to fulfill their order and didn't listen to the end of the message".

Indeed, on the following night the Messenger appeared again. He reproached the Emperor for having chosen an imperfect shape for the temple. "But what shape can be more perfect than a regular polygon!?" cried the Emperor in his dream. To that the Messenger gave a complete and thorough reply.

- All the vertices of the polygon should be positioned in the lattice points.
- All the lengths of its sides should be different.
- From the possible range of such polygons a polygon which maximum side is minimal possible must be chosen.

You are an obedient architect who is going to make the temple's plan. Note that the polygon should be simple (having a border without self-intersections and overlapping) and convex, however, it is acceptable for three consecutive vertices to lie on the same line.

## 样例 #1

### 输入

```
3
```

### 输出

```
YES
0 0
1 0
0 2
```

## 样例 #2

### 输入

```
3
```

### 输出

```
YES
0 1
-1 0
-1 -1
```

# 题解

## 作者：rEdWhitE_uMbrElla (赞：4)

CodeForces的标签中说这题是计算几何题，，，而官方题解里说这是贪心题，，，然而我认为这就是一道暴力题。。

设有两个点$(x_1,y_1)$和$(x_2,y_2)$，则这条边的长$l=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$，那么$l^2=(x_1-x_2)^2+(y_1-y_2)^2$。我们定义{X,Y}为这条边的移动量，则$\{X,Y\}=\{x_1-x_2,y_1-y_2\}$。所以有$X^2+Y^2=l^2$。

假设有一个n边形，则有$\{\sum_{i=1}^{i=n}X_i,\sum_{i=1}^{i=n}Y_i\}=\{0,0\}$，所以$\sum_{i=1}^{i=n}(X_i)^2$和$\sum_{i=1}^{i=n}(Y_i)^2$皆为偶数，所以$\sum_{i=1}^{i=n}(l_i)^2$为偶数。

于是我们可以假设有一点为(0,0),第一条边为最长边。从4开始穷举$l^2$(因为1,2,3是不可能作为$l^2$)，我们知道从(0,0)为一个端点，选另一个整数格点作为另一个端点且线段长度为l的线段最多有8个，我们可以任意选一个线段作为第一条边，于是$X_1$和$Y_1$便就已知了。然后就转化为了一个更简单的问题：已知$X_1$和$Y_1$的值，求$\left\{\begin{matrix} \sum_{i=2}^{i=n}X_i=-X_1 \\  \sum_{i=2}^{i=n}Y_i=-Y_1 \\ l_{i(2\le i\le n)}\le l_1 \end{matrix}\right.$的一组解。这个可以配合奇偶性快速求出。

代码如下：

```
#include <bits/stdc++.h>
using namespace std;

struct point {
	int x , y , r;
	point() {}
	point(int a,int b):x(a) , y(b) , r(a*a + b*b){}
	bool operator == (point &cmp) const {
		return r == cmp.r;
	}
};
vector <point> vec;
vector <pair<int,int> > X , Y;

bool cmp1(const point &a,const point &b) {
	return a.r < b.r;
}
bool cmp2(const point &a,const point &b) {
	return atan2(a.y+0.0 , a.x+0.0) < atan2(b.y+0.0 , b.x+0.0) - 1e-8;
}
void init() {
	for (int i = 0 ; i < 200 ; i ++) {
		for (int j = i ; j < 200 ; j ++) {
			vec.push_back(point(i , j));
		}
	}
	sort(vec.begin() , vec.end() , cmp1);
	vec.erase(unique(vec.begin() , vec.end()) , vec.end());
}

int main() {
	ios_base::sync_with_stdio(false);
	init();
	int n;
	cin >> n;
	int del = 0;
	for (int i = 4 , cnt = 2 , bit = 1; ; i ++) {
		int p = bit;
		int q = (vec[i].x + vec[i].y) & 1;
		if (p && q) {
			if (++cnt == n) del = 3;
			++cnt;
		} else if (p && !q) {
			if (++cnt == n) del = 6;
		} else if (!p && !q) ++ cnt;
		bit = (p + q) & 1;
		if (cnt >= n) {
			int sum = 0;
			for (int j = 1 ; j <= i ; j ++) {
				if (j == del) continue;
				X.push_back(make_pair(vec[j].x , X.size()));
				Y.push_back(make_pair(vec[j].y , Y.size()));
				sum = (sum + vec[j].x) & 1;
			}
			if (sum & 1) swap(X[0].first , Y[0].first);
			break;
		}
	}
	sort(X.begin() , X.end());
	sort(Y.begin() , Y.end());
	int sumX = 0 , sumY = 0;
	for (int i = X.size() - 1 ; i >= 0 ; i --) {
		if (abs(sumX - X[i].first) < abs(sumX + X[i].first)) {
			sumX -= X[i].first;
			X[i].first = -X[i].first;
		} else sumX += X[i].first;
		if (abs(sumY - Y[i].first) < abs(sumY + Y[i].first)) {
			sumY -= Y[i].first;
			Y[i].first = -Y[i].first;
		} else sumY += Y[i].first;
	}
	while (sumX || sumY);
	for (int i = 0; i < X.size() ; i ++) {
		vec[ X[i].second ].x = X[i].first;
		vec[ Y[i].second ].y = Y[i].first;
	}
	vec.erase(vec.begin() + X.size() , vec.end());
	sort(vec.begin() , vec.end() , cmp2);
	cout<<"YES"<<endl;
	int sumx = 0 , sumy = 0;
	for (int i = 0 ; i < vec.size() ; i ++) {
		sumx += vec[i].x;
		sumy += vec[i].y;
		cout << sumx << ' ' << sumy << endl;
	}
	return 0;
}
```

---

