# 题目信息

# Reconstruction

## 题目描述

There is a hidden array $ a_1, a_2, \ldots, a_n $ of length $ n $ whose elements are integers between $ -m $ and $ m $ , inclusive.

You are given an array $ b_1, b_2, \ldots, b_n $ of length $ n $ and a string $ s $ of length $ n $ consisting of the characters $ \texttt{P} $ , $ \texttt{S} $ , and $ \texttt{?} $ .

For each $ i $ from $ 1 $ to $ n $ inclusive, we must have:

- If $ s_i = \texttt{P} $ , $ b_i $ is the sum of $ a_1 $ through $ a_i $ .
- If $ s_i = \texttt{S} $ , $ b_i $ is the sum of $ a_i $ through $ a_n $ .

Output the number of ways to replace all $ \texttt{?} $ in $ s $ with either $ \texttt{P} $ or $ \texttt{S} $ such that there exists an array $ a_1, a_2, \ldots, a_n $ with elements not exceeding $ m $ by absolute value satisfying the constraints given by the array $ b_1, b_2, \ldots, b_n $ and the string $ s $ .

Since the answer may be large, output it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, we can see that the following array satisfies all constraints, thus the answer is $ 1 $ :

1. $ \texttt{P} $ — $ {[\color{red}{\textbf{1}},3,4,2]} $ : sum of $ 1 $ .
2. $ \texttt{S} $ — $ {[1,\color{red}{\textbf{3},4,2}]} $ : sum of $ 9 $ .
3. $ \texttt{P} $ — $ {[\color{red}{1,3,\textbf{4}},2]} $ : sum of $ 8 $ .
4. $ \texttt{P} $ — $ {[\color{red}{1,3,4,\textbf{2}}]} $ : sum of $ 10 $ .

In the second test case, it can be shown that no array $ a $ with all $ |a_i| \leq m = 10^9 $ satisfies all constraints.

## 样例 #1

### 输入

```
6
4 10
PSPP
1 9 8 10
4 1000000000
????
1 1 1 4000000000
8 1000000000
?P?SSP?P
-857095623 -1424391899 -851974476 673437144 471253851 -543483033 364945701 -178537332
4 7
PPSS
4 2 1 3
9 20
?????????
1 2 3 4 5 6 7 8 9
3 1000000000
P??
-145463248 -974068460 -1287458396```

### 输出

```
1
0
2
1
14
1```

# AI分析结果



# 题解翻译  
## 题目描述  

存在一个长度为 $n$ 的隐藏数组 $a_1, a_2, \ldots, a_n$，其元素均为 $[-m, m]$ 范围内的整数。  

给定一个长度为 $n$ 的数组 $b_1, b_2, \ldots, b_n$ 和一个由字符 $\texttt{P}$、$\texttt{S}$、$\texttt{?}$ 组成的字符串 $s$。  

对于每个 $i$ 从 $1$ 到 $n$，必须满足：  
- 若 $s_i = \texttt{P}$，则 $b_i$ 是 $a_1$ 到 $a_i$ 的和。  
- 若 $s_i = \texttt{S}$，则 $b_i$ 是 $a_i$ 到 $a_n$ 的和。  

输出将 $s$ 中所有 $\texttt{?}$ 替换为 $\texttt{P}$ 或 $\texttt{S}$ 的方式数，使得存在满足条件的数组 $a$。答案对 $998244353$ 取模。  

---

# 唯一算法分类  
**线性DP**  

---

# 综合分析与结论  

## 核心思路  
1. **总和推导**：通过字符串 $s$ 中必然存在的 $\texttt{PS}$ 组合（或在边界处虚拟的 $\texttt{PS}$）推导数组总和 $sum = b_i + b_{i+1}$，枚举所有可能的 $sum$ 值。  
2. **状态设计**：定义 $f[i][0/1]$ 表示前 $i$ 位中，第 $i$ 位填 $\texttt{P/S}$ 的合法方案数。  
3. **转移方程**：根据相邻字符组合类型（$\texttt{PP}$、$\texttt{PS}$、$\texttt{SP}$、$\texttt{SS}$）对应的约束条件转移状态。  

## 关键难点  
- **总和枚举**：确定 $sum$ 的可能取值范围（$b$ 的相邻项和或首尾项）。  
- **约束条件处理**：对每种字符组合类型，推导对应的 $a_i$ 取值约束（如 $\texttt{PP} \Rightarrow a_i = b_i - b_{i-1}$）。  

## 可视化设计  
1. **DP矩阵动画**：以网格形式展示 $f[i][0/1]$，高亮当前更新的单元格，颜色标记转移来源（如黄色箭头表示从 $f[i-1][0]$ 转移）。  
2. **条件检查提示**：在检查约束条件时，若条件不满足，单元格显示红色警示，并播放短促音效。  
3. **复古像素风格**：使用 8-bit 风格绘制 DP 矩阵，每个单元格显示当前方案数，背景音乐采用经典 FC 音效。  

---

# 题解清单（评分≥4星）  

1. **作者：_fairytale_（★★★★★）**  
   - **亮点**：通过虚拟边界处理简化推导，利用 map 去重优化枚举，代码结构清晰。  
   - **心得**：发现必须存在 $\texttt{PS}$ 组合推导 $sum$ 是解题突破口。  

2. **作者：Fesdrer（★★★★）**  
   - **亮点**：将后缀和转换为前缀和之差，统一约束条件处理。  
   - **代码优化**：使用哈希表存储可能的 $sum$ 值。  

3. **作者：happybob（★★★★）**  
   - **亮点**：显式列出所有可能的 $sum$ 候选，通过 Lambda 表达式简化约束检查。  

---

# 核心代码实现（以 _fairytale_ 题解为例）  

```cpp
int f[maxn][2]; // DP状态数组

void solve(){
    // 初始化边界条件
    f[0][0] = 1;
    for(int i=1; i<=n+1; i++){
        f[i][0] = f[i][1] = 0;
        // 处理 PP 和 SP 转移
        if(ch[i] != 'S'){
            if(abs(b[i]-b[i-1]) <= m) 
                add(f[i][0], f[i-1][0]); // PP
            ll mx = b[i] + b[i-1] - sum;
            if(abs(mx) <= 2*m) 
                add(f[i][0], f[i-1][1]); // SP
        }
        // 处理 PS 和 SS 转移
        if(ch[i] != 'P'){
            if(b[i-1] + b[i] == sum) 
                add(f[i][1], f[i-1][0]); // PS
            if(abs(b[i]-b[i-1]) <= m) 
                add(f[i][1], f[i-1][1]); // SS
        }
    }
    ans = (ans + f[n+1][1]) % mod;
}
```

---

# 同类型题目推荐  
1. **P1357 后缀表达式计数**（线性DP与后缀表达式约束）  
2. **P1040 加分二叉树**（区间DP与树形结构）  
3. **P1273 有线电视网**（树形DP与背包结合）  

---

# 可视化与交互设计  
1. **Canvas网格**：绘制 $n \times 2$ 的网格，每格显示 $f[i][0/1]$ 的当前值。  
2. **音效设计**：  
   - 转移成功：8-bit "ping" 音效（频率 800Hz，时长 50ms）  
   - 约束失败：低频 "buzz" 音效（频率 200Hz，时长 100ms）  
3. **自动演示模式**：AI 自动遍历所有可能的 $sum$ 值，按最优路径优先策略展示 DP 过程。  

---

**通过线性DP与枚举总和的结合，此题展现了动态规划在复杂约束下的灵活应用，核心在于将全局约束转化为局部状态转移条件。**

---
处理用时：74.23秒