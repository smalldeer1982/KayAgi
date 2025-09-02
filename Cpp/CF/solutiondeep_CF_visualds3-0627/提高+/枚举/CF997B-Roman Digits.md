# 题目信息

# Roman Digits

## 题目描述

Let's introduce a number system which is based on a roman digits. There are digits I, V, X, L which correspond to the numbers $ 1 $ , $ 5 $ , $ 10 $ and $ 50 $ respectively. The use of other roman digits is not allowed.

Numbers in this system are written as a sequence of one or more digits. We define the value of the sequence simply as the sum of digits in it.

For example, the number XXXV evaluates to $ 35 $ and the number IXI — to $ 12 $ .

Pay attention to the difference to the traditional roman system — in our system any sequence of digits is valid, moreover the order of digits doesn't matter, for example IX means $ 11 $ , not $ 9 $ .

One can notice that this system is ambiguous, and some numbers can be written in many different ways. Your goal is to determine how many distinct integers can be represented by exactly $ n $ roman digits I, V, X, L.

## 说明/提示

In the first sample there are exactly $ 4 $ integers which can be represented — I, V, X and L.

In the second sample it is possible to represent integers $ 2 $ (II), $ 6 $ (VI), $ 10 $ (VV), $ 11 $ (XI), $ 15 $ (XV), $ 20 $ (XX), $ 51 $ (IL), $ 55 $ (VL), $ 60 $ (XL) and $ 100 $ (LL).

## 样例 #1

### 输入

```
1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2
```

### 输出

```
10
```

## 样例 #3

### 输入

```
10
```

### 输出

```
244
```

# AI分析结果



### 算法分类
**数学/规律发现**

---

### 综合分析与结论
**题目核心**：在罗马数字系统（值集 {1,5,10,50}）中，用恰好 n 个数字求可表示的不同整数数量。  
**关键难点**：直接暴力枚举 n 个数字的组合复杂度为 O(n³)，无法处理大 n；需通过数学推导或观察规律找到通解。

#### 核心思路对比
1. **数学推导法**（litble 题解）  
   - 将原问题转换为等价数集 {0,4,9,49} 的组合问题，通过限制 4 和 9 的个数避免重复。  
   - 枚举 i（4 的个数 ≤8）和 j（9 的个数 ≤4），剩余位置由 0 和 49 填充，总方案数为 `n-i-j+1`。  
   - **优势**：严格数学证明，适用于任意 n；**劣势**：推导过程复杂，代码需双重循环。

2. **打表找规律法**（多数题解）  
   - 暴力计算小 n 的值，发现当 n≥12 时答案呈公差 49 的等差数列。  
   - **优势**：代码极简，时间复杂度 O(1)；**劣势**：依赖正确识别规律起点，需提前打表验证。

---

### 题解评分（≥4星）
1. **litble 题解**（4.5星）  
   - **亮点**：严谨数学推导，揭示问题本质；代码高效（O(1) 双重循环）。  
   - **不足**：推导过程需较高数学背景，初学者可能难以理解。

2. **__Hacheylight__ 题解**（4星）  
   - **亮点**：简洁分治策略（n≤20 暴力，n>20 公式），代码易实现。  
   - **不足**：未详细解释为何公差为 49，规律起点需读者自行验证。

3. **Amm_awa 题解**（4星）  
   - **亮点**：完整打表过程与规律验证，提供 AC 代码与错误分析。  
   - **不足**：代码中阈值设定（n≤25）与部分题解不一致，需注意数据验证。

---

### 最优思路提炼
**数学推导法关键步骤**：  
1. **问题转换**：将原数集 {1,5,10,50} 转换为 {0,4,9,49}，确保两两互质。  
2. **限制条件**：  
   - 4 的个数 ≤8（避免 9 个 4 被 4 个 9+5 个 0 替代）。  
   - 若使用 4，则 9 的个数 ≤4；否则 9 的个数 ≤8。  
3. **枚举计数**：双重循环枚举 i（4 的个数）和 j（9 的个数），剩余位置由 0 和 49 自由组合，贡献 `n-i-j+1` 种方案。

**核心代码片段**（litble 题解）：
```cpp
for(RI i=0;i<=8&&i<=n;++i)
    for(RI j=0;j<=(i==0?8:4)&&j+i<=n;++j)
        ans+=n-i-j+1;
```

---

### 同类型题与算法套路
- **规律发现**：适用于答案随输入参数呈现明显数学规律的问题。  
- **组合数学**：涉及有限数集的线性组合计数，需排除重复情况。  
- **类似题目**：  
  1. [CF 630K Indivisibility](https://codeforces.com/problemset/problem/630/K)（容斥原理）  
  2. [洛谷 P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)（枚举+预处理）  
  3. [LeetCode 441. Arranging Coins](https://leetcode.com/problems/arranging-coins/)（数学公式推导）

---

### 可视化与算法演示
**动画设计**：  
1. **像素风格界面**：  
   - 使用 16 色调色板，数字组合以不同颜色方块表示（如 I=红、V=蓝、X=绿、L=黄）。  
   - 每个步骤显示当前选择的数字数量及总和，背景播放 8-bit 风格音效。  

2. **关键步骤高亮**：  
   - **枚举 i 和 j**：动态显示 i（4 的个数）和 j（9 的个数）的变化，剩余位置自动填充 0/49。  
   - **答案更新**：每当 i 或 j 变化时，显示 `n-i-j+1` 的累加过程，伴随“滴答”音效。  

3. **自动演示模式**：  
   - 按空格键切换手动/自动模式，自动模式下算法逐步执行，速度可调。  
   - 当 n≥12 时，切换为等差数列模式，显示公式 `ans = 292 + (n-11)*49` 并动态计算。

**代码片段（JS 伪代码）**：
```javascript
function drawAnimation(n) {
    let ans = 0;
    for (let i = 0; i <= Math.min(8, n); i++) {
        for (let j = 0; j <= (i === 0 ? 8 : 4); j++) {
            if (i + j > n) continue;
            // 高亮当前 i 和 j
            highlightCells(i, j);
            ans += (n - i - j + 1);
            // 播放音效并更新显示
            playSound('blip');
            updateCounter(ans);
            delay(100);
        }
    }
}
```

---

### 个人心得摘录
- **调试教训**（5G信号塔报装）：未使用 `long long` 导致溢出，强调数据范围检查的重要性。  
- **规律验证**（Guizy）：通过暴力打表发现 n≥12 时公差为 49，提醒注意规律起点的正确性。  
- **数学直觉**（Daeyr_Xu）：通过数集变换将问题简化，展示如何将复杂问题转化为可枚举形式。  

---

### 最终结论
**推荐解法**：  
- **小 n**（n≤20）：直接暴力枚举所有组合，利用哈希表去重。  
- **大 n**（n>20）：应用公式 `ans = 292 + (n-11)*49`，时间复杂度 O(1)。  

**代码选择**（平衡效率与可读性）：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
    LL n; cin >> n;
    if(n <= 11) cout << vector<LL>{0,4,10,20,35,56,83,116,155,198,244,292}[n];
    else cout << 292 + (n - 11) * 49;
    return 0;
}
```

---
处理用时：93.43秒