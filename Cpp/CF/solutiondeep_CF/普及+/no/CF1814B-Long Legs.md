# 题目信息

# Long Legs

## 题目描述

A robot is placed in a cell $ (0, 0) $ of an infinite grid. This robot has adjustable length legs. Initially, its legs have length $ 1 $ .

Let the robot currently be in the cell $ (x, y) $ and have legs of length $ m $ . In one move, it can perform one of the following three actions:

- jump into the cell $ (x + m, y) $ ;
- jump into the cell $ (x, y + m) $ ;
- increase the length of the legs by $ 1 $ , i. e. set it to $ m + 1 $ .

What's the smallest number of moves robot has to make to reach a cell $ (a, b) $ ?

## 说明/提示

In the first testcase, the robot can first jump to $ (0, 1) $ , then to $ (1, 1) $ . If it ever increases the length of its legs, it will only be able to jump past $ (1, 1) $ .

In the second testcase, the robot can jump to $ (1, 0) $ , then increase the length of its length to $ 2 $ and jump three times to reach $ (1, 6) $ .

In the third testcase, the robot can increase the length of its legs three times to make it $ 4 $ . Then jump to $ (0, 4) $ . Then jump twice to reach $ (8, 4) $ .

## 样例 #1

### 输入

```
3
1 1
1 6
8 4```

### 输出

```
2
5
6```

# AI分析结果

### 中文题目重写

#### 题目描述

一个机器人被放置在无限网格的单元格 $(0, 0)$ 处。这个机器人有可调节长度的腿，初始时腿的长度为 $1$。

假设机器人当前位于单元格 $(x, y)$，且腿的长度为 $m$。在一步操作中，它可以执行以下三种操作之一：

- 跳到单元格 $(x + m, y)$；
- 跳到单元格 $(x, y + m)$；
- 将腿的长度增加 $1$，即将其设置为 $m + 1$。

问：机器人到达单元格 $(a, b)$ 所需的最少操作次数是多少？

#### 说明/提示

在第一个测试用例中，机器人可以先跳到 $(0, 1)$，然后再跳到 $(1, 1)$。如果它曾经增加腿的长度，那么它将只能跳过 $(1, 1)$。

在第二个测试用例中，机器人可以先跳到 $(1, 0)$，然后将腿的长度增加到 $2$，再跳三次到达 $(1, 6)$。

在第三个测试用例中，机器人可以将腿的长度增加三次，使其变为 $4$，然后跳到 $(0, 4)$，再跳两次到达 $(8, 4)$。

#### 样例 #1

##### 输入

```
3
1 1
1 6
8 4
```

##### 输出

```
2
5
6
```

### 算法分类
数学、枚举

### 题解分析与结论

本题的核心在于找到一个合适的腿长 $m$，使得在增加腿长的操作和移动操作之间取得平衡，从而最小化总操作次数。大多数题解都采用了枚举的方法，通过枚举可能的 $m$ 值，计算对应的操作次数，并取最小值。

#### 最优关键思路
1. **枚举腿长 $m$**：通过枚举 $m$ 的可能值，计算对应的操作次数。由于 $m$ 的最优值通常在 $\sqrt{a+b}$ 附近，因此枚举范围可以缩小到 $\sqrt{a+b} \pm 100$，从而减少计算量。
2. **操作次数计算**：对于每个 $m$，计算增加腿长的操作次数 $m-1$，以及移动操作次数 $\lceil \frac{a}{m} \rceil + \lceil \frac{b}{m} \rceil$，总和即为总操作次数。
3. **均值不等式优化**：通过均值不等式，可以证明当 $m = \sqrt{a+b}$ 时，操作次数接近最小值，从而进一步优化枚举范围。

### 高星题解推荐

#### 题解1：frelow_poem (5星)
**关键亮点**：
- 详细推导了最优腿长 $m$ 的取值，并通过均值不等式证明了枚举范围的合理性。
- 提供了代码优化思路，通过调整枚举范围，进一步减少计算量。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
inline int Solve(int x) {
    return (a / x) + (a % x != 0) + (b / x) + (b % x != 0) + (x - 1);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &a, &b);
        int ans = inf;
        int base = (int)sqrt(a+b);
        for (int i = _max(1, base - delta); i <= base + delta; i++) {
            _setmin(ans, Solve(i));
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

#### 题解2：Xy_top (4星)
**关键亮点**：
- 通过简单的公式推导，得出了操作次数的计算方法。
- 提供了枚举范围的上界，并通过实际数据验证了其合理性。
- 代码实现简洁，易于理解。

**核心代码**：
```cpp
for (int i = 1; i <= 500000; i++) {
    ans = min (ans, int (ceil (n * 1.0 / i) ) + int (ceil (m * 1.0 / i) ) + i - 1);
}
```

#### 题解3：VitrelosTia (4星)
**关键亮点**：
- 通过均值不等式推导了最优腿长 $m$ 的取值，并提供了枚举范围的合理性证明。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
for (int m = max(1, qwq - 114); m <= qwq + 114; m++) {
    int now = m - 1 + ceil(1.0 * a / m) + ceil(1.0 * b / m);
    ans = min(ans, now);
}
```

### 拓展思路与推荐题目
1. **类似题目**：
   - [P1008 三连击](https://www.luogu.com.cn/problem/P1008)：考察枚举与数学思维。
   - [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)：考察数学与递归思维。
   - [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)：考察贪心与动态规划。

2. **个人心得**：
   - 通过均值不等式优化枚举范围，可以显著减少计算量，提高代码效率。
   - 在实际编程中，合理调整枚举范围，避免不必要的计算，是优化代码的重要手段。

---
处理用时：42.88秒