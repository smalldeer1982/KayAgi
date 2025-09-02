# Vittorio Plays with LEGO Bricks

## 题目描述

Vittorio is playing with his new LEGO Duplo bricks. All the bricks have the shape of a square cuboid with a $ 2 \times 2 $ square base and a height of $ 1 $ . They can be arranged in the 3D space to build structures, provided that the following rules are met:

1. No two bricks can intersect, but they can touch on their faces.
2. The corners of every brick must have integer coordinates (so bricks are axis-aligned) and the $ z $ coordinates of all corners must be non-negative.
3. The square bases of every brick must be parallel to the ground (i.e. the plane $ z=0 $ ).
4. The lower base of any brick that is not touching the ground must touch the upper base of some other brick in a region of positive area (when this happens, the two bricks stay attached to each other thanks to small studs).

For example, this is a valid structure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1776B/50a6ec76636f7a5cd263915e1fb86a1ec589d956.png)Vittorio wants to build a structure that includes purple bricks in the following $ n $ positions: $ (x_1, 0, h) $ , $ (x_2, 0, h) $ , $ \dots $ , $ (x_n, 0, h) $ — these are the coordinates of the centers of their lower bases; note that all of these bricks have $ y $ coordinate equal to $ 0 $ and $ z $ coordinate equal to $ h $ . Vittorio will use additional bricks of other colors to support the purple bricks. He is willing to place bricks only in positions where the center of the lower base has $ y $ coordinate equal to $ 0 $ . What is the minimum number of additional bricks needed?

It can be shown that a valid construction always exists.

## 说明/提示

In the first sample, all the purple bricks lie on the ground, so no additional bricks are needed.

In the second sample, Vittorio will have to place supporting bricks under the purple bricks, and he can use a single brick to support both the third and the fourth purple bricks. For example, he can place additional bricks at positions $ (3, 0, 0) $ , $ (7, 0, 0) $ and $ (12, 0, 0) $ . It can be shown that it is impossible to build a valid construction using less than $ 3 $ additional bricks.

In the fourth sample, a possible structure that minimizes the number of additional bricks is shown in the problem description.

## 样例 #1

### 输入

```
4 0
2 7 11 13```

### 输出

```
0```

## 样例 #2

### 输入

```
4 1
2 7 11 13```

### 输出

```
3```

## 样例 #3

### 输入

```
4 100
2 7 11 13```

### 输出

```
107```

## 样例 #4

### 输入

```
4 3
2 5 8 11```

### 输出

```
8```

# 题解

## 作者：Leasier (赞：3)

若 $n = 1$，答案就是 $h$。

若 $n = 2$，我们可以考虑从中点开始先向上，再从中间往两边构建一个等腰直角三角形状物。具体地，此时花费为 $h + \min(\lfloor \frac{x_2 - x_1 - 1}{2} \rfloor, h)$，相比分成两个 $n = 1$ 的花费减少了 $\max(h - \lfloor \frac{x_2 - x_1 - 1}{2} \rfloor, 0)$。

当 $n$ 更大时，我们可以考虑参照 $n = 2$ 的做法合并两个相邻区间内的积木。画图可知，我们对大区间最左侧和最右侧的积木做 $n = 2$ 时的操作以减少花费，原来其他积木的块数不受影响。

于是考虑区间 dp。设 $dp_{i, j}$ 表示合并区间 $[i, j]$ 内的积木的最小花费。

初值：$dp_{i, i} = h$。

转移：$dp_{i, j} = \displaystyle\min_{k = i}^{j - 1} (dp_{i, k} + dp_{k + 1, j}) - \max(h - \lfloor \frac{x_j - x_i - 1}{2} \rfloor, 0)$。

答案：$dp_{1, n}$。

暴力实现即可。时间复杂度为 $O(n^3)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

int x[307];
ll dp[307][307];

inline ll min(ll a, ll b){
	return a < b ? a : b;
}

inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	int n, h;
	scanf("%d %d", &n, &h);
	for (int i = 1; i <= n; i++){
		scanf("%d", &x[i]);
	}
	for (int i = n; i >= 1; i--){
		dp[i][i] = h;
		for (int j = i + 1; j <= n; j++){
			dp[i][j] = 0x7fffffffffffffffll;
			for (int k = i; k < j; k++){
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
			}
			dp[i][j] -= max(h - (x[j] - x[i] - 1) / 2, 0);
		}
	}
	printf("%lld", dp[1][n]);
	return 0;
}
```

---

