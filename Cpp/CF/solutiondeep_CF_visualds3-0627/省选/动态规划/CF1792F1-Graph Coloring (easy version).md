# 题目信息

# Graph Coloring (easy version)

## 题目描述

The only difference between the easy and the hard version is the constraint on $ n $ .

You are given an undirected complete graph on $ n $ vertices. A complete graph is a graph where each pair of vertices is connected by an edge. You have to paint the edges of the graph into two colors, red and blue (each edge will have one color).

A set of vertices $ S $ is red-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through red edges and vertices from $ S $ . Similarly, a set of vertices $ S $ is blue-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through blue edges and vertices from $ S $ .

You have to paint the graph in such a way that:

- there is at least one red edge;
- there is at least one blue edge;
- for each set of vertices $ S $ such that $ |S| \ge 2 $ , $ S $ is either red-connected or blue-connected, but not both.

Calculate the number of ways to paint the graph, and print it modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3```

### 输出

```
6```

## 样例 #2

### 输入

```
4```

### 输出

```
50```

## 样例 #3

### 输入

```
100```

### 输出

```
878752271```

## 样例 #4

### 输入

```
1337```

### 输出

```
520628749```

# AI分析结果



0. **题目翻译**

# 图的着色（简单版）

## 题目描述

简单版与困难版的唯一区别在于对 $n$ 的约束不同。

给定一个 $n$ 个顶点的无向完全图。完全图是指每对顶点之间都有一条边相连。你需要将图中的每条边染成红色或蓝色（每条边必须染色）。

顶点集合 $S$ 被称为红连通的，当且仅当对于任意 $v_1 \in S$ 和 $v_2 \in S$，存在一条仅通过红色边和 $S$ 中顶点的路径连接 $v_1$ 和 $v_2$。类似地，顶点集合 $S$ 被称为蓝连通的，当且仅当存在一条仅通过蓝色边的路径连接所有顶点对。

你需要满足以下条件：
- 至少有一条红边；
- 至少有一条蓝边；
- 对于每个顶点集合 $S$（$|S| \ge 2$），$S$ 必须是红连通或蓝连通，但不能同时满足两者。

计算符合条件的染色方式数目，结果对 $998244353$ 取模。

## 样例 #1

### 输入
```
3
```

### 输出
```
6
```

## 样例 #2

### 输入
```
4
```

### 输出
```
50
```

## 样例 #3

### 输入
```
100
```

### 输出
```
878752271
```

## 样例 #4

### 输入
```
1337
```

### 输出
```
520628749
```

---

1. **唯一算法分类**  
线性DP

---

2. **综合分析与结论**  
**核心思路**：利用红蓝图的互补性质，通过动态规划枚举包含顶点1的连通块大小，计算合法方案数。最终答案需排除全红和全蓝的情况。

**关键难点**：
- 确保所有子集S满足单连通性条件
- 通过补图性质将问题转化为连通性约束
- 动态规划状态转移的系数处理

**状态转移设计**：
定义 $dp[i]$ 表示i个顶点满足约束的方案数。转移时枚举包含顶点1的连通块大小$j$：
$$ dp[i] = \sum_{j=1}^{i-1} \binom{i-1}{j-1} \times dp[j] \times dp[i-j] \times (2 - [i-j=1]) $$
其中：
- $\binom{i-1}{j-1}$ 选择连通块成员的组合数
- $dp[j]$ 表示包含顶点1的连通块方案
- $dp[i-j] \times 2$ 处理剩余部分的可选性（$i-j=1$ 时系数为1）

**可视化设计**：
- **动画矩阵**：绘制二维DP表，行表示顶点数i，列表示分割点j。高亮当前计算的格子$dp[i]$与依赖的$dp[j]$和$dp[i-j]$格子
- **像素风格**：用8位色块表示状态值，绿色表示已计算状态，红色表示当前计算状态，黄色表示依赖项
- **音效提示**：状态转移时播放"哔"声，完成计算时播放上升音调
- **自动演示**：按i从小到大自动播放计算过程，支持暂停/步进观察组合数选择细节

---

3. **题解清单 (≥4星)**  
- **Purslane（★★★★☆）**  
  关键亮点：  
  - 清晰引理证明补图性质  
  - 状态转移方程推导完整  
  - 代码包含组合数预处理优化  

- **寄风（★★★★☆）**  
  关键亮点：  
  - 双数组优化减少Cache Miss  
  - 特例处理通过数组预处理实现  
  - 代码简洁高效  

- **zzzYheng（★★★☆☆）**  
  亮点：  
  - 详细分析子集约束条件  
  - 提出多项式优化思路  

---

4. **代码实现与核心逻辑**  
**关键代码（寄风优化版）**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n, dp1[1000005], dp2[1000005], C[1000005];

inline void add(int &x, int y) {
    x += y - mod;
    x += (x >> 31) & mod;
}

int main() {
    cin >> n; 
    dp1[1] = dp2[1] = C[0] = 1;
    for(int i = 2; i <= n; i++) {
        for(int j = i-1; j; j--) 
            add(C[j], C[j-1]);        
        for(int j = 1, k = i-1; j < i; j++, k--) 
            add(dp1[i], (1LL * C[j-1] * dp1[j] % mod * dp2[k] % mod));
        dp2[i] = (dp1[i] << 1) % mod;
    }
    cout << (dp2[n] - 2 + mod) % mod;
    return 0;
}
```

**实现要点**：
- `dp1`存储原始方案数，`dp2`存储两倍方案数（特例预处理）
- 组合数`C`使用递推式计算，避免预计算阶乘
- 内层循环通过`j`和`k=i-j`同步减少循环次数
- 最终结果减去全红和全蓝的两种非法情况

---

5. **同类型题推荐**  
- CF1792F2（本题困难版）
- P6775 [NOI2020] 制作菜品（连通性DP）
- CF1515E（连通块组合计数）

---

6. **可视化代码片段（Canvas动画）**  
```javascript
// 伪代码示例
class DPDemo {
    constructor(n) {
        this.dpGrid = new PixelGrid(n, n); // 像素网格
        this.currentStep = 1;
    }

    drawFrame() {
        for (let j = 1; j < this.currentStep; j++) {
            const k = this.currentStep - j;
            // 高亮依赖格子
            this.dpGrid.highlight(j, 0xFFFF00); 
            this.dpGrid.highlight(k, 0xFFA500);
            // 计算当前格子
            this.dpGrid.update(this.currentStep, computeDP(j, k));
            playSound('blip'); // 触发音效
        }
        this.currentStep++;
    }
}
```

---
处理用时：71.77秒