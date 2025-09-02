# 题目信息

# Place for a Selfie

## 题目描述

The universe is a coordinate plane. There are $ n $ space highways, each of which is a straight line $ y=kx $ passing through the origin $ (0, 0) $ . Also, there are $ m $ asteroid belts on the plane, which we represent as open upwards parabolas, i. e. graphs of functions $ y=ax^2+bx+c $ , where $ a > 0 $ .

You want to photograph each parabola. To do this, for each parabola you need to choose a line that does not intersect this parabola and does not touch it. You can select the same line for different parabolas. Please find such a line for each parabola, or determine that there is no such line.

## 说明/提示

In the first test case, both parabolas do not intersect the only given line $ y=1\cdot x $ , so the answer is two numbers $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1805C/18de32de6fde4236646d351f878d2be05006f8bc.png)In the second test case, the line $ y=x $ and the parabola $ 2x^2+5x+1 $ intersect, and also the line $ y=4x $ and the parabola $ x^2+2x+1 $ touch, so these pairs do not satisfy the condition. So for the first parabola, the answer is $ 1 $ ( $ y=1x $ ), and for the second parabola — $ 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1805C/58b8a5a9448e772cebadc5139da584db388c8262.png)In the third test set, the line and the parabola intersect, so the answer is "NO".

## 样例 #1

### 输入

```
5
1 2
1
1 -1 2
1 -1 3
2 2
1
4
1 2 1
2 5 1
1 1
0
1 0 0
1 1
100000000
100000000 100000000 100000000
2 3
0
2
2 2 1
1 -2 1
1 -2 -1```

### 输出

```
YES
1
YES
1

YES
1
YES
4

NO

YES
100000000

YES
0
NO
NO```

# AI分析结果

### 题目内容重写

#### 题目描述

宇宙是一个坐标平面。有 $n$ 条太空高速公路，每条都是一条通过原点 $(0, 0)$ 的直线 $y=kx$。此外，平面上还有 $m$ 条小行星带，我们将其表示为开口向上的抛物线，即函数 $y=ax^2+bx+c$ 的图像，其中 $a > 0$。

你想拍摄每条抛物线。为此，对于每条抛物线，你需要选择一条直线，这条直线不与这条抛物线相交，也不与其相切。你可以为不同的抛物线选择相同的直线。请为每条抛物线找到这样的一条直线，或者确定不存在这样的直线。

#### 说明/提示

在第一个测试用例中，两条抛物线都不与给定的唯一一条直线 $y=1\cdot x$ 相交，因此答案是两个数字 $1$。

在第二个测试用例中，直线 $y=x$ 与抛物线 $2x^2+5x+1$ 相交，且直线 $y=4x$ 与抛物线 $x^2+2x+1$ 相切，因此这些对不满足条件。所以对于第一条抛物线，答案是 $1$（$y=1x$），对于第二条抛物线，答案是 $4$。

在第三个测试集中，直线和抛物线相交，因此答案是 "NO"。

#### 样例 #1

##### 输入

```
5
1 2
1
1 -1 2
1 -1 3
2 2
1
4
1 2 1
2 5 1
1 1
0
1 0 0
1 1
100000000
100000000 100000000 100000000
2 3
0
2
2 2 1
1 -2 1
1 -2 -1
```

##### 输出

```
YES
1
YES
1

YES
1
YES
4

NO

YES
100000000

YES
0
NO
NO
```

### 算法分类
数学、二分

### 题解分析与结论

本题的核心是通过数学推导和二分查找来确定是否存在一条直线不与给定的抛物线相交。所有题解都基于以下数学原理：直线 $y=kx$ 与抛物线 $y=ax^2+bx+c$ 不相交的条件是方程 $ax^2+(b-k)x+c=0$ 无实数解，即判别式 $\Delta=(b-k)^2-4ac<0$。

大多数题解通过排序和二分查找来找到最接近 $b$ 的 $k$ 值，然后验证是否满足 $\Delta<0$。这种方法的时间复杂度为 $O(m \log n)$，适合处理大规模数据。

### 精选题解

#### 题解1：作者：Mr_Gengar (赞：2)
**星级：4星**
**关键亮点：**
- 简洁明了地解释了数学原理。
- 使用二分查找优化了查找过程。
- 代码结构清晰，易于理解。

**核心代码：**
```cpp
int p = lower_bound(d.begin(), d.end(), b) - d.begin();
if (p < n && C(p)) {
    cout << "Yes\n" << d[p] << "\n";
} else if (p && C(p - 1)) {
    cout << "Yes\n" << d[p - 1] << "\n";
} else {
    cout << "No\n";
}
```

#### 题解2：作者：BLuemoon_ (赞：1)
**星级：4星**
**关键亮点：**
- 详细推导了判别式的条件。
- 通过二分查找找到最接近 $b$ 的 $k$ 值。
- 代码实现简洁高效。

**核心代码：**
```cpp
int x = lower_bound(k + 1, k + n + 1, b) - k;
if (x != n + 1 && (b - k[x]) * (b - k[x]) < 4 * a * c) {
    cout << "YES\n" << k[x] << '\n';
} else if (x != 1 && (b - k[x - 1]) * (b - k[x - 1]) < 4 * a * c) {
    cout << "YES\n" << k[x - 1] << '\n';
} else {
    cout << "NO\n";
}
```

#### 题解3：作者：aCssen (赞：0)
**星级：4星**
**关键亮点：**
- 详细推导了判别式的条件。
- 通过二分查找找到最接近 $b$ 的 $k$ 值。
- 代码实现简洁高效。

**核心代码：**
```cpp
int p2 = lower_bound(k + 1, k + n + 1, b) - k;
int p1 = p2 - 1;
if (!p1 && p2 > n) {
    printf("No\n");
    continue;
}
if (b - k[p1] > k[p2] - b && p2 <= n && p1) p1 = p2;
if (!p1) p1 = p2;
p1 = k[p1];
if (1ll * p1 * p1 - 2ll * p1 * b < 4ll * a * c - 1ll * b * b) printf("Yes\n%d\n", p1);
else printf("No\n");
```

### 最优关键思路或技巧
1. **数学推导**：通过判别式 $\Delta=(b-k)^2-4ac<0$ 来判断直线与抛物线是否相交。
2. **二分查找**：对 $k$ 值进行排序后，使用二分查找快速找到最接近 $b$ 的 $k$ 值，验证是否满足条件。

### 可拓展之处
类似的问题可以扩展到其他类型的函数，如指数函数、对数函数等，通过类似的数学推导和二分查找来解决。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
3. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)

---
处理用时：35.94秒