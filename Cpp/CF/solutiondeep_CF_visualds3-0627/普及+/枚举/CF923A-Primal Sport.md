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



# Primal Sport 题解分析

## 算法分类
**数论（质因数分解与预处理）**

---

## 题解思路与核心难点

### 核心逻辑
1. **逆向推导**：已知 X₂，反推可能的 X₁ 和 X₀ 范围。
2. **最大质因数**：Xᵢ 的范围由 Xᵢ₊₁ 的最大质因数 p 决定，即 Xᵢ ∈ [Xᵢ₊₁ - p +1, Xᵢ₊₁]。
3. **预处理优化**：通过筛法预处理每个数的最大质因数，避免重复分解质因数。

### 解决难点
- **确定 X₁ 范围**：需从 X₂ 的最大质因数 p₂ 推导出 X₁ ∈ [X₂ - p₂ +1, X₂]。
- **最小化 X₀**：对每个可能的 X₁，取其最大质因数 p₁，X₀ 最小为 X₁ - p₁ +1。
- **高效预处理**：线性筛法预处理每个数的最大质因数，时间复杂度 O(n)。

---

## 题解评分（≥4星）

### 1. Blunt_Feeling（4星）
- **亮点**：代码最简洁，利用筛法预处理最大质因数，直接枚举 X₁ 区间。
- **代码**：预处理与枚举逻辑清晰，适合快速理解核心思路。

### 2. ModestCoder_（4星）
- **亮点**：使用线性筛预处理，同时标记质数和最大质因数，代码高效。
- **实现**：结合欧拉筛特性，在处理合数时继承最大质因数。

### 3. Patrickpwq（4星）
- **亮点**：代码清晰，预处理与枚举逻辑分离，适合教学演示。
- **可视化适配**：预处理步骤可分解为独立函数，便于动画演示。

---

## 最优思路与技巧
1. **最大质因数预处理**  
   - **筛法优化**：在线性筛中维护每个数的最大质因数。
   - **关键代码**：
     ```cpp
     for(int i=2;i<=n;i++){
         if(!flag[i]) prime[++tot] = a[i] = i;
         for(int j=1; prime[j]<=n/i; j++){
             flag[i*prime[j]] = 1;
             a[i*prime[j]] = a[i]; // 继承最大质因数
             if(i%prime[j]==0) break;
         }
     }
     ```
2. **区间枚举与最小值计算**  
   - **推导公式**：X₀ = X₁ - p₁ +1，其中 p₁ 是 X₁ 的最大质因数。
   - **实现逻辑**：对每个 X₁ ∈ [X₂ - p₂ +1, X₂]，计算对应的 X₀ 并取最小值。

---

## 类似题目推荐
1. **P1075 质因数分解**  
   - 题意：给定一个合数的质因数分解结果，求较大的质因数。
2. **P3383 线性筛素数**  
   - 题意：使用线性筛法预处理质数。
3. **P2429 制杖题**  
   - 题意：涉及质因数性质与区间枚举，需预处理优化。

---

## 可视化与算法演示

### 核心动画流程
1. **预处理阶段**  
   - **网格绘制**：在 Canvas 中绘制 2~X₂ 的数列。
   - **筛法过程**：高亮当前质数，标记其倍数的最大质因数。
   - **音效**：质数标记时播放“滴”声，倍数更新时播放“咔”声。

2. **X₂ 分解阶段**  
   - **质因数分解**：动态显示 X₂ 分解为 p₂ 的过程。
   - **区间标记**：用红色框标出 X₁ 的区间 [X₂ - p₂ +1, X₂]。

3. **枚举 X₁ 阶段**  
   - **遍历高亮**：逐个高亮 X₁ 候选值，显示其最大质因数 p₁。
   - **计算 X₀**：实时显示 X₀ = X₁ - p₁ +1，更新最小值。

### 复古像素风格
- **调色板**：8-bit 风格，质数用绿色，合数用灰色，当前操作数用闪烁黄色。
- **音效**：使用 ChipTunes 合成音效，背景音乐为 8-bit 循环旋律。

---

## 题解代码（核心逻辑）

### Blunt_Feeling 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int x2,x0,a[1000050];
int main() {
    cin>>x2;
    // 预处理最大质因数
    for(int i=2; i<=x2; i++) {
        if(!a[i]) 
            for(int j=i*2; j<=x2; j+=i) 
                a[j] = i; // j的最大质因数为i
    }
    x0 = x2;
    int p2 = (a[x2]==0) ? x2 : a[x2]; // 处理x2为质数的情况
    for(int i=x2 - p2 +1; i<=x2; i++) {
        int p1 = (a[i]==0) ? i : a[i]; // i为质数时最大质因数是自身
        x0 = min(x0, i - p1 +1);
    }
    cout<<x0<<endl;
    return 0;
}
```

### 核心逻辑解释
1. **预处理**：标记每个合数的最大质因数。
2. **计算 p₂**：若 X₂ 是质数，p₂=X₂；否则取预处理值。
3. **枚举 X₁**：在区间内计算每个 X₁ 对应的 X₀，维护最小值。

---

通过上述分析，结合预处理和逆向推导，此问题得以高效解决。可视化设计可帮助理解筛法和区间枚举的动态过程。

---
处理用时：92.67秒