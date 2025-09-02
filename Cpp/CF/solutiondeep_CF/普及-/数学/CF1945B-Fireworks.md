# 题目信息

# Fireworks

## 题目描述

One of the days of the hike coincided with a holiday, so in the evening at the camp, it was decided to arrange a festive fireworks display. For this purpose, the organizers of the hike bought two installations for launching fireworks and a huge number of shells for launching.

Both installations are turned on simultaneously. The first installation launches fireworks every $ a $ minutes (i.e., after $ a, 2 \cdot a, 3 \cdot a, \dots $ minutes after launch). The second installation launches fireworks every $ b $ minutes (i.e., after $ b, 2 \cdot b, 3 \cdot b, \dots $ minutes after launch).

Each firework is visible in the sky for $ m + 1 $ minutes after launch, i.e., if a firework was launched after $ x $ minutes after the installations were turned on, it will be visible every minute from $ x $ to $ x + m $ , inclusive. If one firework was launched $ m $ minutes after another, both fireworks will be visible for one minute.

What is the maximum number of fireworks that could be seen in the sky at the same time?

## 说明/提示

In the first set of input data, the fireworks are visible in the sky for $ 5 $ minutes. Since the first installation launches fireworks every $ 6 $ minutes, and the second one every $ 7 $ minutes, two fireworks launched from the same installation will not be visible in the sky at the same time. At the same time, after $ 7 $ minutes from the start of the holiday, one firework from the first and one from the second camp will be visible. Thus, it is possible to see no more than $ 2 $ fireworks simultaneously.

In the third set of input data, $ 17 $ fireworks will be visible after $ 112 $ minutes:

- $ 9 $ fireworks launched from the first installation at times \[ $ 56, 63, 70, 77, 84, 91, 98, 105, 112 $ \];
- $ 8 $ fireworks launched from the second installation at times \[ $ 56, 64, 72, 80, 88, 96, 104, 112 $ \].

## 样例 #1

### 输入

```
6
6 7 4
3 4 10
7 8 56
5 6 78123459896
1 1 1
1 1 1000000000000000000```

### 输出

```
2
7
17
28645268630
4
2000000000000000002```

# AI分析结果

### 题目内容重写（中文）

# 烟花

## 题目描述

在徒步旅行中的某一天恰逢节日，因此晚上在营地决定举行一场烟花表演。为此，徒步旅行的组织者购买了两台烟花发射装置和大量的烟花弹。

两台装置同时启动。第一台装置每隔 $a$ 分钟发射一次烟花（即在启动后的 $a, 2 \cdot a, 3 \cdot a, \dots$ 分钟发射）。第二台装置每隔 $b$ 分钟发射一次烟花（即在启动后的 $b, 2 \cdot b, 3 \cdot b, \dots$ 分钟发射）。

每个烟花在发射后会在天空中持续可见 $m + 1$ 分钟，即如果烟花在启动后 $x$ 分钟发射，那么它将在 $x$ 到 $x + m$ 分钟的每一分钟内可见。如果一个烟花在另一个烟花发射后 $m$ 分钟发射，那么两个烟花将在一分钟内同时可见。

问：在天空中最多可以同时看到多少个烟花？

## 说明/提示

在第一组输入数据中，烟花在天空中可见的时间为 $5$ 分钟。由于第一台装置每隔 $6$ 分钟发射一次烟花，第二台装置每隔 $7$ 分钟发射一次烟花，因此同一台装置发射的两个烟花不会同时在天空中可见。然而，在启动后的 $7$ 分钟，第一台和第二台装置发射的烟花将同时可见。因此，最多可以同时看到 $2$ 个烟花。

在第三组输入数据中，启动后的 $112$ 分钟将有 $17$ 个烟花同时可见：

- 第一台装置在 $56, 63, 70, 77, 84, 91, 98, 105, 112$ 分钟发射的 $9$ 个烟花；
- 第二台装置在 $56, 64, 72, 80, 88, 96, 104, 112$ 分钟发射的 $8$ 个烟花。

## 样例 #1

### 输入

```
6
6 7 4
3 4 10
7 8 56
5 6 78123459896
1 1 1
1 1 1000000000000000000
```

### 输出

```
2
7
17
28645268630
4
2000000000000000002
```

---

### 题解分析与结论

本题的核心在于计算在任意长度为 $m+1$ 的时间区间内，两个烟花发射装置发射的烟花数量的最大值。所有题解都基于以下关键思路：

1. **问题转化**：将问题转化为在长度为 $m+1$ 的区间内，计算 $a$ 和 $b$ 的倍数的个数。
2. **公式推导**：答案公式为 $\lfloor \frac{m}{a} \rfloor + \lfloor \frac{m}{b} \rfloor + 2$，其中 $+2$ 是因为初始时刻两台装置同时发射的烟花。
3. **时间复杂度**：所有题解的时间复杂度均为 $O(1)$，适合处理大范围数据。

### 精选题解

#### 题解1：作者：spfa_ (赞：6)
- **星级**：★★★★★
- **关键亮点**：思路清晰，直接给出公式，代码简洁。
- **核心代码**：
  ```cpp
  cout << m / a + m / b + 2 << endl;
  ```

#### 题解2：作者：tanzicheng (赞：2)
- **星级**：★★★★
- **关键亮点**：通过图示帮助理解，代码实现简单明了。
- **核心代码**：
  ```cpp
  cout << m / a + m / b + 2 << endl;
  ```

#### 题解3：作者：littlebug (赞：2)
- **星级**：★★★★
- **关键亮点**：详细解释了公式推导过程，代码可读性好。
- **核心代码**：
  ```cpp
  cout << m / a + m / b + 2 << '\n';
  ```

### 最优关键思路与技巧

1. **问题转化**：将问题转化为在长度为 $m+1$ 的区间内计算 $a$ 和 $b$ 的倍数的个数。
2. **公式推导**：通过数学推导得出 $\lfloor \frac{m}{a} \rfloor + \lfloor \frac{m}{b} \rfloor + 2$ 的公式。
3. **代码实现**：使用整数除法直接计算，确保时间复杂度为 $O(1)$。

### 拓展思路

类似的问题可以通过将问题转化为区间内的计数问题来解决，常见于时间序列或周期性事件的分析中。

### 推荐题目

1. [P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226)
2. [P1082 【模板】同余方程](https://www.luogu.com.cn/problem/P1082)
3. [P1029 【模板】最大公约数和最小公倍数](https://www.luogu.com.cn/problem/P1029)

### 个人心得摘录

- **spfa_**：直接通过数学推导得出公式，避免了复杂的计算和模拟。
- **tanzicheng**：通过图示帮助理解问题，使得公式推导更加直观。
- **littlebug**：详细解释了公式的推导过程，帮助读者更好地理解问题的本质。

---
处理用时：49.30秒