# 题目信息

# Tetrahedron

## 题目描述

You are given a tetrahedron. Let's mark its vertices with letters $ A $ , $ B $ , $ C $ and $ D $ correspondingly.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166E/40dcfda00eddce9e7e8701e13b2759e732ca40f3.png)An ant is standing in the vertex $ D $ of the tetrahedron. The ant is quite active and he wouldn't stay idle. At each moment of time he makes a step from one vertex to another one along some edge of the tetrahedron. The ant just can't stand on one place.

You do not have to do much to solve the problem: your task is to count the number of ways in which the ant can go from the initial vertex $ D $ to itself in exactly $ n $ steps. In other words, you are asked to find out the number of different cyclic paths with the length of $ n $ from vertex $ D $ to itself. As the number can be quite large, you should print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

The required paths in the first sample are:

- $ D-A-D $
- $ D-B-D $
- $ D-C-D $

## 样例 #1

### 输入

```
2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
```

### 输出

```
21
```

# AI分析结果



## 唯一算法分类
**动态规划**

---

## 题解思路、算法要点与解决难点

### 核心思路对比
所有题解均围绕状态转移展开，主要分为两类动态规划思路：
1. **双状态滚动优化**（ModestCoder_、Zhou_Wingay 等）：  
   定义两个状态 `f`（当前在顶点 D）和 `g`（当前不在 D），通过递推式 `f_i=3g_{i-1}` 和 `g_i=f_{i-1}+2g_{i-1}`，利用滚动数组将空间复杂度优化为 O(1)，时间复杂度 O(n)。

2. **数学推导通项公式**（Flokirie、EDqwq 等）：  
   将状态转移转换为线性递推式 `g[i]=2g[i-1]+3g[i-2]`，通过特征方程求解通项公式 `g[i]=(3^i - (-1)^i)/4`，结合快速幂与逆元实现 O(log n) 时间复杂度。

### 解决难点
1. **状态压缩**：通过合并对称状态（所有非 D 顶点等价），将 4 顶点模型简化为双状态模型。
2. **数学抽象**：将递推式转化为特征方程求通项，突破 O(n) 的时间限制。
3. **大数处理**：通过滚动数组和取模运算避免溢出。

---

## 题解评分（≥4⭐）

### 1. ModestCoder_（⭐⭐⭐⭐⭐）
- **亮点**：双状态滚动优化代码简洁高效，时间复杂度与空间复杂度均最优，适合 1e7 量级数据。
- **代码片段**：
  ```cpp
  LL f = 0, g = 1;
  for (int i = 2; i <= n; ++i){
      LL tmp = f;
      f = 3 * g % qy;
      g = (tmp + 2 * g) % qy;
  }
  ```

### 2. Flokirie（⭐⭐⭐⭐）
- **亮点**：数学推导通项公式实现 O(log n) 时间，适合超大 n（如 1e18）。
- **代码片段**：
  ```cpp
  int ans = (750000006ll * (ksm(3, n-1, mod) - ksm(-1, n-1, mod))) % mod;
  ```

### 3. EDqwq（⭐⭐⭐⭐）
- **亮点**：逆向思维公式 `f[i] = 3^{i-1} - f[i-1]` 简洁直观，代码实现易读。
- **代码片段**：
  ```cpp
  for(int i=2;i<=n;++i){
      t = t * 3 % mod;
      dp[i] = (t - dp[i-1]) % mod;
  }
  ```

---

## 最优思路提炼
**双状态滚动优化**是本题的最优实践方案：
1. **状态定义**：`f` 表示在顶点 D 的方案数，`g` 表示不在 D 的方案数。
2. **转移方程**：
   - `f_i = 3 * g_{i-1}`（从三个非 D 顶点各走一步到 D）
   - `g_i = f_{i-1} + 2 * g_{i-1}`（从 D 走一步到非 D，或从非 D 走一步到其他两个非 D）
3. **空间优化**：仅需两个变量滚动更新。

---

## 同类型题与算法套路
1. **对称状态合并**：如斐波那契数列、爬楼梯问题中的状态压缩。
2. **矩阵快速幂优化**：适用于线性递推式（如斐波那契数列、路径计数问题）。
3. **逆向思维公式**：如卡特兰数、错排问题中的递推关系。

---

## 相似题目推荐
1. **P1255 数楼梯**（递推 + 滚动数组）
2. **P1939 矩阵加速（数列）**（矩阵快速幂优化递推）
3. **P1216 数字三角形**（对称状态合并）

---

## 可视化与算法演示设计
### 动态规划状态转移动画
1. **像素风格显示**：
   - 用绿色方块表示 `f`（在 D），红色方块表示 `g`（不在 D）。
   - 每一步循环时，左侧旧状态（`f_old`, `g_old`）向右滑动，生成新状态（`f_new`, `g_new`）。
   ```javascript
   // 伪代码示例
   function drawStep(i, f, g) {
       ctx.fillStyle = '#00FF00'; // 绿色表示 f
       fillRect(i*10, 0, 10, f*10);
       ctx.fillStyle = '#FF0000'; // 红色表示 g
       fillRect(i*10, 20, 10, g*10);
   }
   ```
2. **音效设计**：
   - 每次状态更新时播放 8-bit "blip" 音效。
   - 完成计算时播放胜利音效。

---

## 核心代码实现（ModestCoder_ 方案）
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const LL MOD = 1e9 + 7;

int main() {
    int n;
    scanf("%d", &n);
    LL f = 0, g = 1;
    for (int i = 2; i <= n; ++i) {
        LL tmp = f;
        f = (3 * g) % MOD;
        g = (tmp + 2 * g) % MOD;
    }
    printf("%lld\n", n == 1 ? 0 : f);
    return 0;
}
```

---
处理用时：90.13秒