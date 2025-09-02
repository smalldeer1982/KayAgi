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



**算法分类**：数论、筛法

---

### **题解思路与核心难点**

1. **问题转化与逆向推导**  
   给定X₂，需逆向推导可能的X₁范围，进而求X₀的最小值。关键结论：Xᵢ的范围为[Xᵢ₊₁ - P +1, Xᵢ₊₁]，其中P是Xᵢ₊₁的最大质因数。

2. **最大质因数的预处理**  
   使用线性筛法预处理每个数的最大质因数。在线筛过程中，每个合数被其最小质因数筛掉，同时记录其最大质因数。

3. **遍历X₁的可能范围**  
   X₂的最大质因数P₂决定了X₁的范围为[X₂ - P₂ +1, X₂]。遍历此范围内的每个X₁，计算对应的X₀ = X₁ - P₁ +1（P₁为X₁的最大质因数），取最小值。

---

### **最优思路与技巧提炼**

1. **线筛预处理最大质因数**  
   - 在线筛过程中，记录每个数的最大质因数。例如，合数`i*prime[j]`的最大质因数为`max(a[i], prime[j])`，但在线筛中`prime[j]`是i的最小质因数，因此只需继承`a[i]`的值。
   - **代码片段**：
     ```cpp
     for (int i = 2; i <= n; ++i) {
         if (!flag[i]) prime[++tot] = a[i] = i;
         for (int j = 1; j <= tot && i * prime[j] <= n; ++j) {
             flag[i * prime[j]] = 1;
             a[i * prime[j]] = a[i];
             if (i % prime[j] == 0) break;
         }
     }
     ```

2. **逆向推导与区间遍历**  
   - 根据X₂的最大质因数确定X₁的范围，遍历每个X₁并计算X₀的最小值。
   - **代码片段**：
     ```cpp
     int ans = n;
     for (int i = n - a[n] + 1; i <= n; ++i)
         if (flag[i]) ans = min(ans, i - a[i] + 1);
     ```

---

### **题解评分（≥4星）**

1. **ModestCoder_（4.5星）**  
   - **亮点**：简洁的线筛预处理，高效处理最大质因数，代码可读性高。  
   - **代码**：预处理与遍历逻辑清晰，时间复杂度O(n)。

2. **Blunt_Feeling（4星）**  
   - **亮点**：埃氏筛预处理最大质因数，代码最短。  
   - **缺点**：预处理效率略低于线筛，但逻辑直观。

3. **cbyybccbyybc（4星）**  
   - **亮点**：结合线筛与逆向推导，代码结构清晰。  
   - **关键注释**：明确说明X₁必须为合数的条件，避免无效计算。

---

### **可视化算法演示**

1. **核心步骤可视化**  
   - **筛法预处理**：在网格中动态显示每个数的最大质因数标记过程。例如，素数显示为红色，合数根据最大质因数显示不同颜色。
   - **区间遍历**：高亮X₁的范围[X₂-P₂+1, X₂]，并逐个显示X₁对应的X₀值，最终标记最小值。

2. **复古像素风格设计**  
   - **颜色方案**：使用16色调色板，素数用亮红色，合数根据最大质因数值渐变。
   - **音效提示**：筛法标记时播放“滴”声，找到X₀时播放胜利音效。
   - **交互控制**：允许单步执行筛法过程，调节动画速度观察标记细节。

---

### **同类型题目推荐**

1. **P1075 质因数分解**  
   - 求一个数的最大质因数，直接应用预处理技巧。

2. **P3383 线性筛素数**  
   - 练习线筛的变体应用，如预处理最小质因数。

3. **P1217 回文质数**  
   - 结合筛法与数学推导，优化回文数生成。

---

### **个人心得摘录**

- **预处理的重要性**：线筛预处理最大质因数将时间复杂度从O(n√n)优化到O(n)，大幅提升效率。  
- **逆向思维**：从X₂逆向推导X₁和X₀，避免正向模拟的复杂性。

---
处理用时：170.50秒