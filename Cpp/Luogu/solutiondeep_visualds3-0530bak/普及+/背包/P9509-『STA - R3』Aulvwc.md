# 题目信息

# 『STA - R3』Aulvwc

## 题目背景

统计学是一门古老而迷人的学科。

传说早在若干年前，一位名为惠普的神灵来到地球，发现了人类——另一种有智慧的物种……

**已加入 Hack 数据，位于 Subtask 5，不计分。**

## 题目描述

定义一个序列 $\{a_n\}$ 是分部平均的，当且仅当存在一个 $\{1,2,\cdots,n\}$ 的划分 $S_1,S_2,\cdots,S_k$（其中 $k>1$），满足对于每个整数 $1\le i\le k$，序列 $\{a\}$ 中以 $S_i$ 为下标的元素之平均数都是相等的**整数**。

现在，给定序列 $\{a_n\}$，问它是否是分部平均的。

如果你对于一些定义不很清楚，可以查阅最后的「提示」部分。



## 说明/提示

### 提示
一个集合 $S$ 的划分定义为一组集合 $U_1,U_2,\cdots,U_k$，满足：
- 对于所有 $i\neq j$，有 $U_i\cap U_j=\varnothing$。
- $U_1\cup U_2\cup\cdots\cup U_k=S$。

一个序列 $\{x_n\}$ 的平均数定义为：
$$\bar x=\dfrac{x_1+x_2+\cdots+x_n}{n}=\dfrac 1n\sum_{i=1}^nx_i$$
### 样例解释
第一组数据的一种划分方案：$\{1\},\{2\},\{3\},\{4\},\{5\}$。

第二组数据的一种划分方案：$\{1,5\},\{2,4\},\{3\}$。

注意：划分方案所提供的集合是下标集合。

### 数据范围

**本题采用捆绑测试及子任务依赖。**
$$
\newcommand{\arraystretch}{1.5}
\begin{array}{c|c|c|c|c}\hline\hline
\textbf{Subtask} & \bm{n}\le & \textbf{分值} & \textbf{特殊性质}&\textbf{依赖子任务}\\\hline
\textsf{1} & 10 & 5 & \\\hline
\textsf{2} & 10^3 & 20 & \sum a_i=0 \\\hline
\textsf{3} & 100 & 25 & & \sf1\\\hline
\textsf{4} & 10^3 & 50 & & \sf1\texttt{,}\ 3\\\hline
\end{array}
$$

对于全部数据，$1\le q\le 10$，$2\le n\le 10^3$，$|a_i|\le 5\times10^3$。

## 样例 #1

### 输入

```
4
5
1 1 1 1 1
5
1 2 3 4 5
5
1 1 1 1 6
5
-1 0 1 0 1```

### 输出

```
Yes
Yes
No
No```

# AI分析结果



# 『STA - R3』Aulvwc 题解分析

## 唯一算法分类
动态规划优化（bitset优化）

---

## 题解思路与核心难点
**核心思路**：  
1. 判断全局平均数是否为整数  
2. 将所有元素减去平均数，转化为求非全选非空真子集和为0的问题  
3. 使用动态规划或bitset优化子集和判定  

**关键步骤**：  
- **数学转化**：通过减去平均值消除长度影响，转化为子集和问题  
- **同余优化**：利用模数压缩状态空间，解决超大值域问题  
- **bitset优化**：将正负元素分别处理，通过位运算快速计算可能和  

**解决难点**：  
- 值域高达±5e6，传统DP无法处理  
- 需要排除全选和空集的特殊情况  

---

## 题解评分（≥4★）

### ty_mxzhn（5★）
**亮点**：  
- 多模数同余优化，保证正确性  
- 状态压缩剪枝技巧  
- 代码结构清晰，剪枝策略合理  

### Lyz09（5★）
**亮点**：  
- 正负分离bitset优化  
- 零元素特判加速  
- 代码简洁高效，复杂度最优  

### zqiaor（4★）
**亮点**：  
- 双bitset交集判定  
- 偏移量处理负数  
- 代码简洁，但未处理极大值域极端情况  

---

## 最优思路与技巧提炼

**关键技巧**：  
1. **数学转化**：  
   ```cpp
   for(int i=1;i<=n;i++) a[i] -= avg;  
   ```
   将原问题转化为求子集和为0  

2. **bitset分治**：  
   ```cpp
   bitset<2500001> pos, neg;  
   pos |= pos << a[i];  // 处理正数
   neg |= neg << (-a[i]); // 处理负数
   if ((pos & neg).count() > 2) return true; 
   ```

3. **同余优化**：  
   ```cpp
   for(int k=1;k<=6;k++) // 多个质数模数
       dp[k][j] = (dp[k][j] + dp[k][j-a[i]%p[k]]) % p[k];
   ```

---

## 类似题目推荐
1. **P2347 砝码称重**（bitset基础应用）  
2. **P4942 小凯的疑惑**（模数优化思想）  
3. **CF755F PolandBall and Gifts**（子集和变形问题）

---

## 可视化设计（bitset优化）

**动画方案**：  
1. **初始化网格**：  
   创建两个并排的像素条带（正数区/负数区），每个像素代表一个可能的和值  
   ```javascript
   const canvas = document.getElementById("bitset-canvas");
   ctx.fillStyle = "#8B00FF"; // 紫色像素块
   ```

2. **更新过程**：  
   ```javascript
   function updateBitset(val) {
     if(val > 0) {
       posBitset |= posBitset << val; // 位运算模拟
       drawPixelColumn(posBitset, 0); 
     } else {
       negBitset |= negBitset << (-val);
       drawPixelColumn(negBitset, 200); 
     }
   }
   ```

3. **高亮策略**：  
   - 当前处理元素：红色闪烁边框  
   - 新增激活位：黄色高亮  
   - 最终交集位：绿色持续点亮  

**音效设计**：  
- `bitSetSound()`：每次位操作时播放8位电子音效  
- `successSound()`：检测到交集时播放FC游戏通关音效

---

## 核心代码实现（Lyz09优化版）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e6+5;

bitset<N> pos, neg;

void solve() {
    pos.reset(); neg.reset();
    pos[0] = neg[0] = 1;
    
    int sum = 0, n;
    cin >> n;
    vector<int> a(n);
    for(auto& x : a) {
        cin >> x;
        sum += x;
    }
    if(sum % n != 0) {
        cout << "No\n";
        return;
    }
    int avg = sum / n;
    bool hasZero = false;
    for(auto& x : a) {
        x -= avg;
        if(x == 0) hasZero = true;
    }
    if(hasZero) {
        cout << "Yes\n";
        return;
    }
    for(auto x : a) {
        if(x > 0) pos |= pos << x;
        else if(x < 0) neg |= neg << (-x);
    }
    cout << ((pos & neg).count() > 2 ? "Yes\n" : "No\n");
}
```

---

## 个人心得摘录
> "随机打乱后前缀和判重的思路来自哈希碰撞原理，实践中需要平衡随机次数与正确率" —— Huangjy88  
> "bitset的移位操作本质是并行状态转移，比传统DP快64倍" —— Lyz09

---
处理用时：67.46秒