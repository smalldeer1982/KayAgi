# Max and Bike

## 题目描述

For months Maxim has been coming to work on his favorite bicycle. And quite recently he decided that he is ready to take part in a cyclists' competitions.

He knows that this year $ n $ competitions will take place. During the $ i $ -th competition the participant must as quickly as possible complete a ride along a straight line from point $ s_{i} $ to point $ f_{i} $ ( $ s_{i}&lt;f_{i} $ ).

Measuring time is a complex process related to usage of a special sensor and a time counter. Think of the front wheel of a bicycle as a circle of radius $ r $ . Let's neglect the thickness of a tire, the size of the sensor, and all physical effects. The sensor is placed on the rim of the wheel, that is, on some fixed point on a circle of radius $ r $ . After that the counter moves just like the chosen point of the circle, i.e. moves forward and rotates around the center of the circle.

At the beginning each participant can choose any point $ b_{i} $ , such that his bike is fully behind the starting line, that is, $ b_{i}&lt;s_{i}-r $ . After that, he starts the movement, instantly accelerates to his maximum speed and at time $ ts_{i} $ , when the coordinate of the sensor is equal to the coordinate of the start, the time counter starts. The cyclist makes a complete ride, moving with his maximum speed and at the moment the sensor's coordinate is equal to the coordinate of the finish (moment of time $ tf_{i} $ ), the time counter deactivates and records the final time. Thus, the counter records that the participant made a complete ride in time $ tf_{i}-ts_{i} $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF594B/0da531a238dd82ea419c8ad0bc10a8e3fa696887.png)Maxim is good at math and he suspects that the total result doesn't only depend on his maximum speed $ v $ , but also on his choice of the initial point $ b_{i} $ . Now Maxim is asking you to calculate for each of $ n $ competitions the minimum possible time that can be measured by the time counter. The radius of the wheel of his bike is equal to $ r $ .

## 样例 #1

### 输入

```
2 1 2
1 10
5 9
```

### 输出

```
3.849644710502
1.106060157705
```

# 题解

## 作者：KaguyaH (赞：2)

### 题意简述

给定一个半径为 $r$ 的圆，你有一根不定长的绳子；

你需要把绳子绕在圆上，使绳子的长度加上绳子两端点间的直线距离等于 $f - s$；

求绳子的最短长度 $l$，你需要输出 $\frac l v$。

$n$ 组数据。

### 题目分析

为什么可以如上理解题目呢？

我们考虑，把真正走过的路径长度绕在车轮上，那么，路径长度就是绳长 $l$，不必走的距离就是绳子两端点之间的距离。

那么，如何求出 $l$ 呢？

易得，绳子首位两端点间的距离应为 $2r\sin\frac l{2r}$。所以，

$$l + 2r\sin\frac l{2r} = f - s.$$

设 $x = \frac l{2r}$，$s' = \frac{f - s}{2r}$，则有

$$2r(x + \sin x) = f - s,$$

$$x + \sin x = s'.$$

设 $f(x) = x + \sin x$，则

$$f'(x) = \cos(x) + 1 \geqslant 0.$$

故 $f$ 具有单调性，二分即可。

### Code

```cpp
# define _CRT_SECURE_NO_WARNINGS
# include <cmath>
# include <cstdio>

namespace Main {
	namespace Sourse {
		typedef long unsigned int lu;
		typedef long double Lf;
		static const Lf Pi(acosl(-1));
		static const Lf eps(1e-9l);
	}
	using namespace Sourse;
	static lu n, r, v;
	static inline const Lf f(const Lf s) {
		Lf l(0), r(s);
		while (r - l > eps) ((l + r) / 2 + 2 * fabsl(sinl((l + r) / 2 / 2)) < s ? l : r) = (l + r) / 2;
		return (l + r) / 2;
	}
	static inline const void main() {
		scanf("%lu%lu%lu", &n, &r, &v);
		for (register lu i(0); i < n; ++i) {
			static lu s, t; scanf("%lu%lu", &s, &t);
			printf("%.12Lf\n", f((t - s) * 1.0l / r) * r / v);
		}
	}
}

signed int main() { Main::main(); return 0; }
```

---

