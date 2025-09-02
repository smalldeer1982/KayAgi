# 题目信息

# The Legend of Freya the Frog

## 题目描述

Freya the Frog is traveling on the 2D coordinate plane. She is currently at point $ (0,0) $ and wants to go to point $ (x,y) $ . In one move, she chooses an integer $ d $ such that $ 0 \leq d \leq k $ and jumps $ d $ spots forward in the direction she is facing.

Initially, she is facing the positive $ x $ direction. After every move, she will alternate between facing the positive $ x $ direction and the positive $ y $ direction (i.e., she will face the positive $ y $ direction on her second move, the positive $ x $ direction on her third move, and so on).

What is the minimum amount of moves she must perform to land on point $ (x,y) $ ?

## 说明/提示

In the first sample, one optimal set of moves is if Freya jumps in the following way: ( $ 0,0 $ ) $ \rightarrow $ ( $ 2,0 $ ) $ \rightarrow $ ( $ 2,2 $ ) $ \rightarrow $ ( $ 3,2 $ ) $ \rightarrow $ ( $ 3,5 $ ) $ \rightarrow $ ( $ 6,5 $ ) $ \rightarrow $ ( $ 6,8 $ ) $ \rightarrow $ ( $ 9,8 $ ) $ \rightarrow $ ( $ 9,11 $ ). This takes 8 jumps.

## 样例 #1

### 输入

```
3
9 11 3
0 10 8
1000000 100000 10```

### 输出

```
8
4
199999```

# AI分析结果

### 题目内容重写
# 青蛙Freya的传说

## 题目描述

青蛙Freya在二维坐标平面上旅行。她当前位于点 $ (0,0) $，想要到达点 $ (x,y) $。在一次移动中，她选择一个整数 $ d $，满足 $ 0 \leq d \leq k $，并朝她当前面对的方向跳跃 $ d $ 个点。

初始时，她面向正 $ x $ 方向。每次移动后，她会在正 $ x $ 方向和正 $ y $ 方向之间交替（即第二次移动时面向正 $ y $ 方向，第三次移动时面向正 $ x $ 方向，依此类推）。

她最少需要多少次移动才能到达点 $ (x,y) $？

## 说明/提示

在第一个样例中，Freya的一种最优移动方式是：$ (0,0) \rightarrow (2,0) \rightarrow (2,2) \rightarrow (3,2) \rightarrow (3,5) \rightarrow (6,5) \rightarrow (6,8) \rightarrow (9,8) \rightarrow (9,11) $。这需要8次跳跃。

## 样例 #1

### 输入

```
3
9 11 3
0 10 8
1000000 100000 10```

### 输出

```
8
4
199999```

### 题解分析与结论

#### 综合分析与结论
本题的核心在于计算青蛙Freya在交替跳跃方向的情况下，最少需要多少次跳跃才能到达目标点 $ (x, y) $。所有题解都采用了贪心策略，即每次跳跃尽可能跳最远的距离 $ k $，并且根据跳跃方向的交替性，计算横向和纵向的跳跃次数，最终取最大值或进行相应调整。

#### 最优关键思路
1. **贪心策略**：每次跳跃尽可能跳最远的距离 $ k $。
2. **跳跃次数计算**：横向跳跃次数为 $ \lceil \frac{x}{k} \rceil $，纵向跳跃次数为 $ \lceil \frac{y}{k} \rceil $。
3. **交替跳跃调整**：由于跳跃方向交替，若横向跳跃次数多于纵向，则总跳跃次数为 $ 2 \times \lceil \frac{x}{k} \rceil - 1 $；否则为 $ 2 \times \lceil \frac{y}{k} \rceil $。

#### 推荐题解
1. **作者：player_1_Z (5星)**
   - **关键亮点**：详细分析了跳跃次数的计算方式，并提供了错误代码的修正思路，最终得出正确代码。
   - **代码核心**：
     ```cpp
     int xs = x / k, ys = y / k;
     if (xs * k < x) xs++; if (ys * k < y) ys++;
     if (xs <= ys) cout << 2 * ys << endl;
     else if (xs > ys) cout << 2 * xs - 1 << endl;
     ```

2. **作者：Yxy7952 (4星)**
   - **关键亮点**：思路清晰，代码简洁，直接计算跳跃次数并进行调整。
   - **代码核心**：
     ```cpp
     int a = x / k, b = y / k;
     if (a * k < x) a++; if (b * k < y) b++;
     if (a < b) cout << 2 * b;
     else if (a > b) cout << 2 * a - 1;
     else cout << a + b;
     ```

3. **作者：tiantianyang (4星)**
   - **关键亮点**：代码简洁，逻辑清晰，直接计算跳跃次数并进行调整。
   - **代码核心**：
     ```cpp
     maxx = (k + x - 1) / k; maxy = (y + k - 1) / k;
     if (maxx > maxy) cout << maxx * 2 - 1 << endl;
     else cout << maxy * 2 << endl;
     ```

#### 可拓展之处
- **类似题目**：可以考虑在三维空间中的跳跃问题，或者跳跃方向不固定时的最小跳跃次数问题。
- **算法套路**：贪心策略在计算最小步数或最短路径问题时非常常见，可以结合其他算法如动态规划进行优化。

#### 推荐题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：42.10秒