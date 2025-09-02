# 题目信息

# Sum and Product

## 题目描述

You have an array $ a $ of length $ n $ .

Your task is to answer $ q $ queries: given $ x,y $ , find the number of pairs $ i $ and $ j $ ( $ 1 \le i < j \le n $ ) that both $ a_i + a_j = x $ and $ a_i \cdot a_j = y $ .

That is, for the array $ [1,3,2] $ and asking for $ x=3,y=2 $ the answer is $ 1 $ :

- $ i=1 $ and $ j=2 $ fail because $ 1 + 3 = 4 $ and not $ 3, $ also $ 1 \cdot 3=3 $ and not $ 2 $ ;
- $ i=1 $ and $ j=3 $ satisfies both conditions;
- $ i=2 $ and $ j=3 $ fail because $ 3 + 2 = 5 $ and not $ 3, $ also $ 3 \cdot 2=6 $ and not $ 2 $ ;

## 说明/提示

For the first test case, let's analyze each pair of numbers separately:

- pair $ (a_1,a_2) $ : $ a_1 + a_2 = 4 $ , $ a_1 \cdot a_2 = 3 $
- pair $ (a_1,a_3) $ : $ a_1 + a_3 = 3 $ , $ a_1 \cdot a_3 = 2 $
- pair $ (a_2,a_3) $ : $ a_2 + a_3 = 5 $ , $ a_2 \cdot a_3 = 6 $

 From this, we can see that for the first query, the pair $ (a_1,a_3) $ is suitable, for the second query, it is $ (a_2,a_3) $ , and there are no suitable pairs for the third and fourth queries.In the second test case, all combinations of pairs are suitable.

## 样例 #1

### 输入

```
3
3
1 3 2
4
3 2
5 6
3 1
5 5
4
1 1 1 1
1
2 1
6
1 4 -2 3 3 3
3
2 -8
-1 -2
7 12```

### 输出

```
1 1 0 0 
6 
1 1 3```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

你有一个长度为 $n$ 的数组 $a$。

你的任务是回答 $q$ 次查询：给定 $x$ 和 $y$，找到满足 $1 \le i < j \le n$ 且 $a_i + a_j = x$ 且 $a_i \cdot a_j = y$ 的数对 $(i, j)$ 的数量。

例如，对于数组 $[1, 3, 2]$，查询 $x=3$ 和 $y=2$ 时，答案为 $1$：

- $i=1$ 和 $j=2$ 不满足条件，因为 $1 + 3 = 4$ 且 $1 \cdot 3 = 3$；
- $i=1$ 和 $j=3$ 满足条件；
- $i=2$ 和 $j=3$ 不满足条件，因为 $3 + 2 = 5$ 且 $3 \cdot 2 = 6$。

#### 说明/提示

对于第一个测试用例，我们分析每一对数字：

- 对 $(a_1, a_2)$：$a_1 + a_2 = 4$，$a_1 \cdot a_2 = 3$；
- 对 $(a_1, a_3)$：$a_1 + a_3 = 3$，$a_1 \cdot a_3 = 2$；
- 对 $(a_2, a_3)$：$a_2 + a_3 = 5$，$a_2 \cdot a_3 = 6$。

从中可以看出，对于第一个查询，对 $(a_1, a_3)$ 是符合条件的；对于第二个查询，对 $(a_2, a_3)$ 是符合条件的；而对于第三和第四个查询，没有符合条件的数对。在第二个测试用例中，所有数对都符合条件。

#### 样例 #1

##### 输入

```
3
3
1 3 2
4
3 2
5 6
3 1
5 5
4
1 1 1 1
1
2 1
6
1 4 -2 3 3 3
3
2 -8
-1 -2
7 12
```

##### 输出

```
1 1 0 0 
6 
1 1 3
```

### 算法分类

数学

### 题解分析与结论

所有题解的核心思路都是通过数学推导将问题转化为解一元二次方程，然后通过统计数组中满足条件的元素个数来计算符合条件的数对数量。具体步骤如下：

1. **方程转化**：将 $a_i + a_j = x$ 和 $a_i \cdot a_j = y$ 转化为关于 $a_i$ 的一元二次方程 $a_i^2 - x \cdot a_i + y = 0$。
2. **求解方程**：利用求根公式 $a_i = \frac{x \pm \sqrt{x^2 - 4y}}{2}$ 求出可能的 $a_i$ 和 $a_j$。
3. **判断条件**：判断求得的根是否为整数，并且是否在数组中存在。
4. **统计结果**：根据根的情况统计符合条件的数对数量。

### 评分较高的题解

#### 1. 作者：luqyou (5星)

**关键亮点**：
- 思路清晰，代码简洁。
- 使用了 `map` 来统计数组中每个元素的出现次数，方便快速查询。
- 处理了 $x^2 - 4y = 0$ 的特殊情况，避免了重复计算。

**核心代码**：
```cpp
int num = x * x - 4 * y;
if (num < 0) {
    cout << 0 << " ";
    continue;
}
int sq = sqrt(num);
if (sq * sq != num) {
    cout << 0 << " ";
    continue;
}
if (num == 0) {
    cout << mp[(x - sq) / 2] * (mp[(x - sq) / 2] - 1) / 2 << " ";
    continue;
}
int n1 = x - sq, n2 = x + sq;
cout << mp[n1 / 2] * mp[n2 / 2] << " ";
```

#### 2. 作者：hanjinghao (4星)

**关键亮点**：
- 代码结构清晰，使用了模板函数进行输入输出优化。
- 详细处理了 $x^2 - 4y = 0$ 的情况，并进行了边界检查。

**核心代码**：
```cpp
int delta = x * x - 4ll * y;
if (delta < 0) {
    writesp(0);
    continue;
}
if (!delta) {
    if (mp.find(x >> 1) == mp.end()) {
        writesp(0);
        continue;
    }
    int tmp = mp[x >> 1];
    writesp(tmp * (tmp - 1) / 2);
    continue;
}
int t = sqrtl(delta);
while (t * t > delta) --t;
while ((t + 1) * (t + 1) <= delta) ++t;
if (t * t != delta) {
    writesp(0);
    continue;
}
int X1 = (x + t) / 2;
int X2 = x - X1;
writesp(mp[X1] * mp[X2]);
```

#### 3. 作者：ProzacPainkiller (4星)

**关键亮点**：
- 代码简洁，逻辑清晰。
- 使用了 `long double` 来处理平方根计算，避免了精度问题。

**核心代码**：
```cpp
ll delta = x * x - 4 * y, sqrdelta;
long double sd = sqrtl(delta);
sqrdelta = sd;
if ((sqrdelta + 1ll) * (sqrdelta + 1ll) == delta) ++sqrdelta;
if (delta < 0ll || sqrdelta * sqrdelta != delta) {
    cout << "0 ";
    continue;
}
if (!delta) cout << mp[x / 2ll] * (mp[x / 2ll] - 1) / 2 << ' ';
else {
    ll t1 = (x - sqrdelta) / 2ll, t2 = (x + sqrdelta) / 2ll;
    cout << mp[t1] * mp[t2] << ' ';
}
```

### 最优关键思路与技巧

1. **数学转化**：将问题转化为一元二次方程，利用求根公式求解。
2. **统计优化**：使用 `map` 统计数组中每个元素的出现次数，方便快速查询。
3. **边界处理**：特别注意 $x^2 - 4y = 0$ 的情况，避免重复计算。

### 可拓展之处

类似的问题可以通过数学转化和统计优化来解决，例如：
- 寻找满足特定条件的数对或子数组。
- 利用 `map` 或 `unordered_map` 进行快速查询和统计。

### 推荐题目

1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
2. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

### 个人心得总结

- **调试经历**：在处理 $x^2 - 4y = 0$ 的情况时，容易忽略重复计算的问题，需要特别注意。
- **顿悟感想**：通过数学转化，可以将复杂的问题简化为简单的方程求解，大大降低了问题的复杂度。

---
处理用时：59.29秒