# 题目信息

# Gotta Go Fast

## 题目描述

You're trying to set the record on your favorite video game. The game consists of $ N $ levels, which must be completed sequentially in order to beat the game. You usually complete each level as fast as possible, but sometimes finish a level slower. Specifically, you will complete the $ i $ -th level in either $ F_{i} $ seconds or $ S_{i} $ seconds, where $ F_{i}&lt;S_{i} $ , and there's a $ P_{i} $ percent chance of completing it in $ F_{i} $ seconds. After completing a level, you may decide to either continue the game and play the next level, or reset the game and start again from the first level. Both the decision and the action are instant.

Your goal is to complete all the levels sequentially in at most $ R $ total seconds. You want to minimize the expected amount of time playing before achieving that goal. If you continue and reset optimally, how much total time can you expect to spend playing?

## 说明/提示

In the first example, you never need to reset. There's an $ 81% $ chance of completing the level in $ 2 $ seconds and a $ 19% $ chance of needing $ 8 $ seconds, both of which are within the goal time. The expected time is $ 0.81·2+0.19·8=3.14 $ .

In the second example, you should reset after the first level if you complete it slowly. On average it will take $ 0.25 $ slow attempts before your first fast attempt. Then it doesn't matter whether you complete the second level fast or slow. The expected time is $ 0.25·30+20+0.85·3+0.15·9=31.4 $ .

## 样例 #1

### 输入

```
1 8
2 8 81
```

### 输出

```
3.14
```

## 样例 #2

### 输入

```
2 30
20 30 80
3 9 85
```

### 输出

```
31.4
```

## 样例 #3

### 输入

```
4 319
63 79 89
79 97 91
75 87 88
75 90 83
```

### 输出

```
314.159265358
```

# AI分析结果



---

## **算法分类**
**二分**

---

## **题解思路与算法要点**

### **核心思路**
- **问题转化**：将原问题转化为二分答案问题。假设当前期望时间为 `mid`，通过动态规划（DP）验证是否可行。
- **状态设计**：定义 `f[i][j]` 表示在第 `i` 关已用 `j` 秒时，通关的最小期望时间。
- **转移方程**：  
  对于每个状态 `f[i][j]`，计算两种选择：
  - **继续游戏**：按当前关卡的快/慢时间累加期望。
  - **重置游戏**：直接花费 `mid` 的期望时间。
  取两者的最小值：  
  ```
  f[i][j] = min(
      mid,
      p_{i+1} * (f[i+1][j+a_{i+1}] + a_{i+1}) + 
      (1-p_{i+1}) * (f[i+1][j+b_{i+1}] + b_{i+1})
  )
  ```
- **二分条件**：若 `f[0][0] < mid`，说明 `mid` 偏大，缩小右边界；否则缩小左边界。

### **解决难点**
1. **状态转移的环问题**：直接 DP 无法处理 `f[0][0]` 与其他状态的相互依赖。通过二分法将 `f[0][0]` 视为常数 `mid`，打破循环依赖。
2. **时间限制处理**：当累计时间超过 `R` 时，强制重置（即 `f[i][j] = mid`）。
3. **二分单调性**：假设的 `mid` 越大，实际期望可能越小，具有单调性，确保二分正确性。

---

## **题解评分（≥4星）**

### 1. **ღꦿ࿐ 题解（4星）**
- **亮点**：代码简洁，明确二分与DP结合，关键注释清晰。
- **改进点**：循环终止条件 `cnt>200` 不够严谨，建议改用固定二分次数（如100次）。

### 2. **skylee 题解（5星）**
- **亮点**：代码规范，状态转移逻辑清晰，边界处理完善。
- **关键代码**：
  ```cpp
  for(int j=0;j<=m;j++) {
      f[i][j] = std::min(
          (f[i+1][j+a[i]]+a[i])*p[i]/100 + 
          (f[i+1][j+b[i]]+b[i])*(1-p[i])/100, 
          k
      );
  }
  ```

### 3. **Purslane 题解（4星）**
- **亮点**：深入分析二分法的单调性来源，强调 `f_{i,j}` 的单调性。
- **心得摘录**：  
  > “通过将 `dp[0][0]` 设为常数 `c`，避免高斯消元的复杂度，结合二分法巧妙解决环问题。”

---

## **最优思路提炼**
1. **二分答案框架**：  
   - 初始区间 `[0, 1e9]`，固定二分次数（如100次）避免精度问题。
   - **判断条件**：若 `check(mid)` 返回 `f[0][0] < mid`，则 `mid` 偏大。
2. **DP状态压缩**：  
   - 从后向前递推（`i` 从 `n-1` 到 `0`），避免无效状态。
   - 预处理超时情况（`j > R` 时直接赋 `mid`）。
3. **边界处理**：  
   - 时间溢出时强制重置，确保最优策略。

---

## **同类型题与算法套路**
- **通用二分答案套路**：  
  当问题满足单调性，且直接求解困难时，假设答案并验证（如求最小最大值、最大最小值）。
- **类似题目**：
  1. **CF865C**（原题）
  2. **POJ 2976**（二分答案+分数规划）
  3. **洛谷 P1182**（数列分段，二分最小最大值）

---

## **推荐题目**
1. **P1182**：数列分段（二分答案）
2. **P4344**：SHOI2015 零件组装（二分+动态规划）
3. **CF1117C**（二分答案+贪心验证）

---

## **可视化与算法演示**

### **二分过程动画设计**
1. **区间可视化**：  
   - 用 Canvas 绘制区间 `[left, right]`，标记 `mid` 和当前区间范围。
   - **颜色标记**：`left`（蓝色）、`right`（红色）、`mid`（黄色）。
2. **动态更新**：  
   - 每次二分后，根据 `check(mid)` 结果更新区间：
     - 若 `check(mid)` 为真，`right = mid`，播放“成功音效”。
     - 否则 `left = mid`，播放“失败音效”。
3. **音效设计**：  
   - 8位风格音效：更新 `mid` 时触发“哔”声，找到答案时播放“胜利旋律”。
4. **自动演示模式**：  
   - 初始时自动运行，逐步展示区间收缩过程，支持暂停/继续。

---

## **核心代码片段**

```cpp
bool check(double mid) {
    memset(f, 0, sizeof(f));
    for (int i = n-1; i >= 0; i--) {
        for (int j = R+1; j <= 5000; j++) f[i+1][j] = mid;
        for (int j = 0; j <= R; j++) {
            double t1 = (f[i+1][j+a[i]] + a[i]) * p[i]/100;
            double t2 = (f[i+1][j+b[i]] + b[i]) * (100-p[i])/100;
            f[i][j] = std::min(mid, t1 + t2);
        }
    }
    return f[0][0] < mid;
}

double l = 0, r = 1e9;
for (int iter = 0; iter < 100; iter++) {
    double mid = (l + r) / 2;
    if (check(mid)) r = mid;
    else l = mid;
}
printf("%.9f\n", r);
```

---

## **总结**
本题通过二分答案将复杂的状态转移环问题转化为单调性问题，结合动态规划验证，巧妙避免了高斯消元的高复杂度。关键点在于利用二分的单调性和DP的最优子结构，将初始状态的期望值作为二分目标，逐步逼近正确答案。

---
处理用时：87.23秒