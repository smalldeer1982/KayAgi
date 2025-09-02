# 题目信息

# Primal Sport

## 题目描述

Alice and Bob begin their day with a quick game. They first choose a starting number $ X_{0}>=3 $ and try to reach one million by the process described below.

Alice goes first and then they take alternating turns. In the $ i $ -th turn, the player whose turn it is selects a prime number smaller than the current number, and announces the smallest multiple of this prime number that is not smaller than the current number.

Formally, he or she selects a prime $ p&lt;X_{i-1} $ and then finds the minimum $ X_{i}>=X_{i-1} $ such that $ p $ divides $ X_{i} $ . Note that if the selected prime $ p $ already divides $ X_{i-1} $ , then the number does not change.

Eve has witnessed the state of the game after two turns. Given $ X_{2} $ , help her determine what is the smallest possible starting number $ X_{0} $ . Note that the players don't necessarily play optimally. You should consider all possible game evolutions.

## 说明/提示

In the first test, the smallest possible starting number is $ X_{0}=6 $ . One possible course of the game is as follows:

- Alice picks prime 5 and announces $ X_{1}=10 $
- Bob picks prime 7 and announces $ X_{2}=14 $ .

In the second case, let $ X_{0}=15 $ .

- Alice picks prime 2 and announces $ X_{1}=16 $
- Bob picks prime 5 and announces $ X_{2}=20 $ .

## 样例 #1

### 输入

```
14
```

### 输出

```
6
```

## 样例 #2

### 输入

```
20
```

### 输出

```
15
```

## 样例 #3

### 输入

```
8192
```

### 输出

```
8191
```

# AI分析结果



### 综合分析与结论

#### 核心思路与贪心策略
题目要求逆向推导最小初始值 $X_0$。所有题解均采用以下贪心策略：
1. **最大质因数决定范围**：利用 $X_2$ 的最大质因数 $p_2$，确定 $X_1$ 的可能范围为 $[X_2 - p_2 +1, X_2]$。
2. **预处理优化**：通过筛法预处理每个数的最大质因数，使得范围计算和后续查询高效。
3. **逆向枚举**：枚举 $X_1$ 的可能值，并计算对应的 $X_0 = X_1 - p_1 +1$（$p_1$ 为 $X_1$ 的最大质因数），取全局最小值。

#### 解决难点
- **高效计算最大质因数**：通过线性筛或埃氏筛的变形，在预处理时记录每个数的最大质因数。
- **范围推导的正确性**：利用数学证明 $X_{i}$ 的取值范围，确保逆向推导的完备性。

#### 可视化设计
- **筛法过程动态展示**：以颜色区分质数/合数，实时显示每个数的最大质因数更新。
- **逆向推导动画**：从 $X_2$ 出发，分解 $p_2$ 并高亮 $X_1$ 的候选区间，逐步计算最小 $X_0$。
- **像素风格交互**：采用 8-bit 像素风格，通过点击查看每个数的质因数分解路径，音效提示关键步骤。

---

### 题解清单（评分≥4星）

1. **Blunt_Feeling（★★★★☆）**  
   - **亮点**：代码最短，利用埃氏筛预处理最大质因数，思路简洁高效。
   - **关键代码**：通过遍历质数并标记倍数，直接记录最大质因数。

2. **ModestCoder_（★★★★☆）**  
   - **亮点**：线性筛法实现，时间复杂度更低，适合大规模数据。
   - **关键代码**：在线性筛过程中动态维护最大质因数数组。

3. **cbyybccbyybc（★★★★☆）**  
   - **亮点**：代码清晰，结合筛法与逆向枚举，强调贪心策略的正确性。
   - **关键代码**：预处理后直接遍历区间求最小值。

---

### 最优思路提炼

#### 核心步骤
1. **预处理最大质因数**：使用筛法为每个数保存其最大质因数。
2. **逆向推导范围**：对 $X_2$ 分解得到 $p_2$，确定 $X_1 \in [X_2 - p_2 +1, X_2]$。
3. **枚举求最小值**：对每个 $X_1$ 计算 $X_0 = X_1 - p_1 +1$，取所有 $X_0$ 的最小值。

#### 代码实现
```cpp
// 预处理最大质因数（埃氏筛变体）
int a[MAX] = {0};
for (int i = 2; i <= x2; ++i) {
    if (!a[i]) { // i是质数
        for (int j = i * 2; j <= x2; j += i) {
            a[j] = i; // 更新j的最大质因数为i
        }
    }
}

// 逆向枚举求最小值
int ans = x2;
for (int x1 = x2 - a[x2] + 1; x1 <= x2; ++x1) {
    ans = min(ans, x1 - a[x1] + 1);
}
```

---

### 类似题目推荐
1. **P1075 质因数分解**：求一个数的最大质因数。
2. P1217 回文质数：结合质数与范围筛选。
3. P3383 线性筛素数：练习筛法实现。

---

### 可视化与算法演示

#### 动画设计
1. **筛法过程**：网格中每个数动态显示其最大质因数，质数高亮为黄色，合数根据最大质因数显示不同颜色。
2. **逆向推导**：从 $X_2$ 开始，红色框标记 $p_2$，绿色框展开 $X_1$ 的候选区间，逐个计算并比较 $X_0$。
3. **交互操作**：点击任意数查看质因数分解路径，滑动调节动画速度。

#### 复古游戏化元素
- **像素风格**：数字以 16x16 像素块显示，背景音乐为 8-bit 循环。
- **音效反馈**：正确选择时播放上升音阶，错误选择播放低沉音效。
- **积分系统**：每找到一个更小的 $X_0$ 获得积分，连击加成。

---

### 个人心得摘录
- **调试教训**：注意筛法预处理时覆盖顺序，确保最大质因数正确更新。
- **优化顿悟**：线性筛法在处理大规模数据时时间复杂度更优。

---
处理用时：200.62秒