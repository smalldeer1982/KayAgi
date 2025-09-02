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



## 唯一算法分类
数学转化 + 动态规划（同余优化与 bitset 优化）

---

## 综合分析与结论

### 核心思路
1. **数学转化**：将原问题转化为寻找和为 0 的子集。若原序列平均数为整数，将所有元素减去该平均数后，问题等价于寻找非空真子集和为 0。
2. **动态规划优化**：
   - **同余优化**：通过模运算减少状态空间，避免处理大数（如 ty_mxzhn 解法）。
   - **bitset 优化**：利用位运算压缩背包状态，高效处理正负分离的求和问题（如 Lyz09、zqiaor 解法）。
3. **随机化策略**：随机打乱序列后检查前缀和重复性，属于概率算法（如 Huangjy88 解法）。

### 解决难点
- **大值域处理**：直接背包可能因值域过大超时，通过同余或 bitset 优化解决。
- **非空真子集判断**：需排除空集和全集，通过强制选特定元素或检查子集大小实现。

### 可视化设计
- **动画方案**：以像素风格展示序列元素转化为 0 后的值，红色表示正数，蓝色表示负数，白色为 0。
- **bitset 状态更新**：用网格表示 bitset 每一位，绿色高亮当前更新的位，伴随音效提示。
- **步进控制**：允许单步执行，观察每个元素如何影响 bitset 状态，速度可调。
- **复古音效**：使用 8-bit 音效，元素处理时播放短音，找到解时播放胜利音效。

---

## 题解清单（≥4星）

### 1. Lyz09 的 bitset 解法（5星）
- **亮点**：正负数分离处理，bitset 位运算高效压缩状态，代码简洁。
- **关键代码**：
  ```cpp
  bitset<N> b, s;
  b.set(0); s.set(0);
  for (int i=1; i<=n; i++) {
      if (a[i] > 0) b |= b << a[i];
      else s |= s << (-a[i]);
  }
  if ((b & s).count() > 2) return Yes;
  ```

### 2. zqiaor 的 bitset 解法（4.5星）
- **亮点**：代码更精简，直接处理正负贡献，判断交集大小。
- **核心逻辑**：
  ```cpp
  bitset<2500001> b1, b2;
  b1[0] = b2[0] = 1;
  for (int x : a) {
      if (x > 0) b1 |= b1 << x;
      else b2 |= b2 << (-x);
  }
  return (b1 & b2).count() > 2;
  ```

### 3. jijidawang 的随机化解法（4星）
- **亮点**：多次随机打乱序列，利用前缀和和 set 快速判断。
- **关键代码**：
  ```cpp
  random_shuffle(a, a+n);
  set<int> s;
  int sum = 0;
  for (int x : a) {
      sum += x;
      if (s.count(sum)) return Yes;
      s.insert(sum);
  }
  ```

---

## 最优思路提炼
1. **数学转化**：所有元素减去平均数，问题简化为寻找和为 0 的非空真子集。
2. **bitset 位压缩**：将正负贡献分离，通过位运算快速更新可能和。
3. **同余优化**：使用多个模数减少状态空间，避免大数运算。

---

## 同类型题推荐
1. **P2347 砝码称重**：利用 bitset 处理背包问题。
2. **P1284 三角形牧场**：数学转化后寻找可行子集。
3. **P2218 覆盖问题**：随机化算法与贪心结合。

---

## 个人心得摘录
- **Lyz09**：强调正负分离处理，避免值域爆炸。
- **Huangjy88**：多次随机打乱提升成功率，但需注意不能遍历到全集。

---

## 可视化与算法演示

### 核心算法流程（bitset 版）
1. **初始化**：展示原始序列，高亮当前平均数计算。
2. **元素转化**：每个元素减去平均数，颜色区分正负。
3. **bitset 更新**：
   - 正数左移更新，负数右移更新（视觉化位操作）。
   - 高亮新激活的位，播放“滴”声。
4. **交集检测**：显示正负 bitset 的交集，找到非零交集时播放胜利音效。

### 复古像素风格设计
- **颜色方案**：8-bit 调色板，红/蓝区分正负，绿色表示激活位。
- **Canvas 绘制**：网格化显示 bitset 状态，每帧更新伴随像素动画。
- **音效设计**：使用 Web Audio API 播放 8-bit 音效，关键操作触发不同音调。

```javascript
// 示例代码片段（Canvas 绘制 bitset）
function drawBitset(bitset, x, y) {
  for (let i = 0; i < bitset.length; i++) {
    ctx.fillStyle = bitset[i] ? '#00FF00' : '#444444';
    ctx.fillRect(x + i * 10, y, 8, 8);
  }
}
```

---

## 代码实现（Lyz09 解法核心）
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 2500010
bitset<N> b, s;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, sum = 0; cin >> n;
        vector<int> a(n);
        for (int &x : a) cin >> x, sum += x;
        if (sum % n) { cout << "No\n"; continue; }
        int avg = sum / n;
        bool has_zero = false;
        b.reset(); s.reset();
        b[0] = s[0] = 1;
        for (int x : a) {
            x -= avg;
            if (x == 0) has_zero = true;
            if (x > 0) b |= b << x;
            else if (x < 0) s |= s << (-x);
        }
        if (has_zero || (b & s).count() > 2) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
```

---
处理用时：96.59秒