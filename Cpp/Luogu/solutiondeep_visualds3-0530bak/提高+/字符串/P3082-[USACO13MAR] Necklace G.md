# 题目信息

# [USACO13MAR] Necklace G

## 题目描述

Bessie the cow has arranged a string of N rocks, each containing a single letter of the alphabet, that she wants to build into a fashionable necklace.

Being protective of her belongings, Bessie does not want to share her necklace with the other cow currently living on her side of the barn.  The other cow has a name that is a string of M characters, and Bessie wants to be sure that this length-M string does not occur as a contiguous substring anywhere within the string representing her necklace (otherwise, the other cow might mistakenly think the necklace is for her).  Bessie decides to remove some of the rocks in her necklace so that the other cow's name does not appear as a substring.  Please help Bessie determine the minimum number of rocks she must remove.

贝西收集了N颗石头，每颗石头上都有一个字母，贝西想把这些石头做成项链。

贝西的身边有另一只奶牛，这只奶牛的名字是一个长度为M的字符串，贝西不希望这只牛的名字出现在她的项链上(项链的子串)，她想知道，最少删掉几颗石头就可以避免这种情况发生。


## 说明/提示

```cpp
For at least 20% of test cases, N <= 20. 
For at least 60% of test cases, N <= 1000, M <= 100. 
For all test cases, N <= 10000, M <= 1000. 
For all test cases, M <= N. 
```
The modified necklace should be "abbaa".

---

$\text{upd 2022.7.29}$：新增加一组 Hack 数据。

## 样例 #1

### 输入

```
ababaa 
aba 
```

### 输出

```
1 
```

# AI分析结果



**唯一算法分类**  
动态规划（DP）结合 KMP 算法

---

### **题解思路、算法要点与解决难点**  
#### **核心思路**  
所有题解均采用动态规划，通过预处理模式串的匹配状态（KMP 的 `next` 数组或 AC 自动机）跟踪当前匹配位置，确保不形成完整子串。关键点如下：  
1. **状态定义**：`f[i][j]` 表示处理到 `S` 的第 `i` 个字符时，当前匹配到 `T` 的前 `j` 位，此时保留的最大字符数或需删除的最小字符数。  
2. **状态转移**：  
   - **保留字符**：通过预处理的状态转移表（`g[j][c]`）跳转到新的匹配位置。  
   - **删除字符**：直接从上一状态继承，删除数 +1。  
3. **预处理优化**：利用 KMP 的 `next` 数组快速计算状态转移路径，避免暴力匹配。  

#### **解决难点**  
- **高效状态转移**：通过 KMP 预处理 `g[j][c]`，将转移复杂度从 O(M^2) 降为 O(M)。  
- **避免完整匹配**：在转移过程中，若新状态 `j = m`（完整匹配），直接跳过该状态。  

---

### **题解评分 (≥4星)**  
1. **zhaoyp 的题解（5星）**  
   - 思路清晰，代码简洁。  
   - 使用 KMP 预处理 `g[j][c]`，DP 转移逻辑直观。  
   - 核心代码段：  
     ```cpp  
     void prefix() { /* 预处理 g[j][c] */ }  
     void DP() { /* 转移方程：f[i+1][g[j][c]] = max(f[i][j] + 1) */ }  
     ```  

2. **船酱魔王 的题解（4星）**  
   - 结合 KMP 的 `next` 数组，状态转移表 `g[j][c]` 的推导详细。  
   - 使用最小删除数作为 DP 状态，更符合直觉。  
   - 核心代码段：  
     ```cpp  
     int findnxt(int ps, char ch) { /* 计算跳转位置 */ }  
     for (int i=0; i<n; i++) {  
         for (int j=0; j<m; j++) {  
             dp[i+1][k] = min(dp[i][j], ...);  
         }  
     }  
     ```  

3. **lyhqwq 的题解（4星）**  
   - 预处理 `to[j][c]` 与 KMP 的 `next` 数组完全对应，代码可读性强。  
   - 通过 `f[i][j]` 记录删除数，直接取最小值作为答案。  

---

### **最优思路或技巧提炼**  
1. **KMP 预处理加速转移**  
   - 预处理 `g[j][c]` 表示当前匹配到 `T` 的第 `j` 位时，下一个字符为 `c` 的跳转位置。  
   - 利用 `next` 数组快速计算 `g[j][c]`，避免每次暴力匹配。  

2. **逆向思维转换问题**  
   - 将“最少删除”转换为“最多保留”，简化状态转移逻辑。  

3. **滚动数组优化空间**  
   - DP 数组仅保留当前层和上一层，空间复杂度从 O(NM) 降为 O(M)。  

---

### **同类型题或类似算法套路**  
- **子串/子序列匹配问题**：如 [LeetCode 115. 不同的子序列](https://leetcode.cn/problems/distinct-subsequences/)。  
- **动态规划结合预处理**：如 [CF 625B. War of the Corporations](https://codeforces.com/problemset/problem/625/B)。  

---

### **推荐相似题目**  
1. **P3975 [TJOI2015]弦论**（后缀自动机 + DP）  
2. **P3435 [POI2006] OKR-Periods of Words**（KMP 的 `next` 数组应用）  
3. **P3193 [HNOI2008]GT考试**（KMP + 矩阵快速幂优化 DP）  

---

### **可视化与算法演示**  
#### **动画方案设计**  
1. **像素风格界面**  
   - **背景**：8-bit 风格网格，`S` 和 `T` 字符串以像素方块显示。  
   - **颜色标记**：  
     - 红色方块：当前处理的字符 `S[i]`。  
     - 绿色方块：`T` 的当前匹配位置 `j`。  
     - 蓝色箭头：状态转移路径（`g[j][c]`）。  

2. **动态演示步骤**  
   - **Step 1**：展示 KMP 的 `next` 数组构建过程，高亮匹配失败时的跳转。  
   - **Step 2**：逐字符处理 `S`，显示 `f[i][j]` 的更新过程。  
   - **Step 3**：当 `j` 达到 `m` 时，触发警告音效并跳过该状态。  

3. **交互功能**  
   - **速度控制**：滑动条调节动画速度（0.5x~3x）。  
   - **单步执行**：按空格键逐帧观察状态转移。  
   - **音效**：  
     - `f[i][j]` 更新时播放“滴”声。  
     - 完整匹配时播放“警报”声。  

#### **核心代码片段（JS 伪代码）**  
```javascript  
// 预处理 g[j][c]  
function preprocess(T) {  
    let next = computeKMPNext(T);  
    for (let j=0; j<T.length; j++) {  
        for (let c of 'abcdefghijklmnopqrstuvwxyz') {  
            let k = j;  
            while (k > 0 && T[k] != c) k = next[k-1];  
            g[j][c] = (T[k] == c) ? k+1 : 0;  
        }  
    }  
}  

// DP 动画演示  
function animateDP(S, T) {  
    let dp = initializeDP();  
    for (let i=0; i<S.length; i++) {  
        highlightCurrentChar(S[i]);  
        for (let j=0; j<T.length; j++) {  
            let c = S[i];  
            let nextJ = g[j][c];  
            if (nextJ != T.length) {  
                updateDP(i+1, nextJ, dp[i][j] + 1);  
                drawArrow(j, nextJ);  
            }  
            updateDP(i+1, j, dp[i][j]);  
        }  
        playSound('step');  
    }  
}  
```  

---

### **个人心得摘录**  
- **Parsley_**：KMP 的 `next` 数组不仅是匹配工具，还能预处理状态转移表，极大简化 DP 设计。  
- **SolIII**：主动转移比被动转移更直观，通过刷表法避免冗余计算。  

---

### **结论**  
本题核心为 **KMP 预处理 + 动态规划**，通过预处理跳转路径优化状态转移，时间复杂度为 O(NM)，空间可优化至 O(M)。可视化设计应聚焦于 KMP 的 `next` 构建与 DP 状态更新，通过像素动画和音效增强理解。

---
处理用时：84.56秒