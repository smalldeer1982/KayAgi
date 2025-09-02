# 题目信息

# [ABC350E] Toward 0

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc350/tasks/abc350_e

整数 $ N $ が与えられます。あなたは次の $ 2 $ 種類の操作を行うことができます。

- $ X $ 円払う。$ N $ を $ \displaystyle\left\lfloor\frac{N}{A}\right\rfloor $ に置き換える。
- $ Y $ 円払う。$ 1 $ 以上 $ 6 $ 以下の整数が等確率で出るサイコロを振る。その出目を $ b $ としたとき、$ N $ を $ \displaystyle\left\lfloor\frac{N}{b}\right\rfloor $ に置き換える。
 
ここで $ \lfloor\ s\ \rfloor $ は $ s $ 以下の最大の整数を表します。例えば $ \lfloor\ 3\ \rfloor=3 $、$ \lfloor\ 2.5\ \rfloor=2 $ です。

適切に操作を選択したとき、$ N $ を $ 0 $ にするまでに払う必要がある金額の期待値の最小値を求めてください。  
 なお、サイコロの出目は操作ごとに独立であり、操作の選択はそれまでの操作の結果を確認してから行うことができます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{18} $
- $ 2\ \leq\ A\ \leq\ 6 $
- $ 1\ \leq\ X,Y\ \leq\ 10^9 $
- 入力は全て整数である
 
### Sample Explanation 1

行える操作は 次の $ 2 $ 種類です。 - $ 10 $ 円払う。$ N $ を $ \displaystyle\left\lfloor\frac{N}{2}\right\rfloor $ に置き換える。 - $ 20 $ 円払う。$ 1 $ 以上 $ 6 $ 以下の整数が等確率で出るサイコロを振る。その出目を $ b $ としたとき、$ N $ を $ \displaystyle\left\lfloor\frac{N}{b}\right\rfloor $ に置き換える。 前者の操作を $ 2 $ 回行うのが最適です。

### Sample Explanation 2

行える操作は 次の $ 2 $ 種類です。 - $ 20 $ 円払う。$ N $ を $ \displaystyle\left\lfloor\frac{N}{2}\right\rfloor $ に置き換える。 - $ 20 $ 円払う。$ 1 $ 以上 $ 6 $ 以下の整数が等確率で出るサイコロを振る。その出目を $ b $ としたとき、$ N $ を $ \displaystyle\left\lfloor\frac{N}{b}\right\rfloor $ に置き換える。 最適な操作は以下のようになります。 - まず後者の操作でサイコロを振ります。 - $ 4 $ 以上が出た場合 $ N=0 $ となります。 - $ 2 $ または $ 3 $ が出た場合 $ N=1 $ となります。続けて前者の操作を行うことで $ N=0 $ となります。 - $ 1 $ が出た場合最初からやり直します。

## 样例 #1

### 输入

```
3 2 10 20```

### 输出

```
20.000000000000000```

## 样例 #2

### 输入

```
3 2 20 20```

### 输出

```
32.000000000000000```

## 样例 #3

### 输入

```
314159265358979323 4 223606797 173205080```

### 输出

```
6418410657.7408381```

# AI分析结果



# 题目翻译

## 题目描述

给定一个整数 $N$。你可以进行以下两种操作：

- 支付 $X$ 日元。将 $N$ 替换为 $\displaystyle\left\lfloor\frac{N}{A}\right\rfloor$。
- 支付 $Y$ 日元。掷一个等概率出现 $1$ 到 $6$ 的骰子，设结果为 $b$，将 $N$ 替换为 $\displaystyle\left\lfloor\frac{N}{b}\right\rfloor$。

其中 $\lfloor s \rfloor$ 表示不大于 $s$ 的最大整数，例如 $\lfloor 3 \rfloor = 3$，$\lfloor 2.5 \rfloor = 2$。

在最优选择操作的情况下，求将 $N$ 变为 $0$ 所需支付金额的期望最小值。骰子的结果在不同操作间相互独立，且操作选择可以基于之前的所有结果。

---

## 输入格式

输入包含四个整数：$N$, $A$, $X$, $Y$。

## 输出格式

输出最小期望值，保留至少七位小数。

---

## 样例

### 样例 #1
输入：
```
3 2 10 20
```
输出：
```
20.000000000000000
```

### 样例 #2
输入：
```
3 2 20 20
```
输出：
```
32.000000000000000
```

---

## 提示

### 数据范围
- $1 \leq N \leq 10^{18}$
- $2 \leq A \leq 6$
- $1 \leq X,Y \leq 10^9$

---

# 算法分类
**线性DP**

---

# 综合分析与结论

## 核心思路
1. **动态规划与记忆化搜索**  
   采用递归式动态规划，通过记忆化搜索处理大范围状态。定义 $dp[n]$ 为将 $n$ 变为 $0$ 的最小期望费用：
   - **操作一**：直接支付 $X$ 并转移到 $\lfloor n/A \rfloor$。
   - **操作二**：支付 $Y$ 后根据骰子结果 $b$ 转移到 $\lfloor n/b \rfloor$。由于 $b=1$ 会导致自环，通过移项消除后效性：
     \[
     dp2[n] = \frac{1}{5} \left( \sum_{b=2}^6 dp[\lfloor n/b \rfloor] \right) + \frac{6Y}{5}
     \]
   - 最终取两种操作的最小值：$dp[n] = \min(dp1[n], dp2[n])$。

2. **状态数优化**  
   虽然 $N$ 极大，但每次递归会将 $n$ 除以至少 $2$，实际有效状态数为 $O(\log N)$，利用 `map` 存储已计算状态。

## 解决难点
- **后效性处理**：通过代数变形消除操作二中 $b=1$ 的自环依赖。
- **记忆化效率**：利用哈希表（如 `std::map`）仅存储实际访问的状态，避免存储所有可能的 $n$。

## 可视化设计要点
- **像素动画**：用 8-bit 风格网格展示当前状态 $n$ 及其子状态 $\lfloor n/b \rfloor$。
- **音效提示**：状态计算时播放不同音效（如计算成功、选择操作类型）。
- **递归树展示**：动态绘制递归调用的树状结构，高亮当前处理节点和已缓存节点。
- **自动演示模式**：模拟 AI 自动选择最优操作，逐步展开状态空间。

---

# 题解清单（≥4星）

## 题解1（作者：fcy20180201，⭐⭐⭐⭐⭐）
**亮点**：
- 简洁的转移方程变形和记忆化实现。
- 代码清晰，直接处理骰子后效性。

**代码核心**：
```cpp
double dfs(ll i) {
    if (!i) return 0;
    if (dp.count(i)) return dp[i];
    return dp[i] = min(dfs(i/A) + x, 
        (dfs(i/2) + dfs(i/3) + dfs(i/4) + dfs(i/5) + dfs(i/6)) /5 + y*1.2);
}
```

---

# 最优思路提炼
1. **后效性消除**：将骰子操作的 $b=1$ 情况通过代数变形转化为无后效形式。
2. **记忆化剪枝**：仅计算实际访问的状态，避免无效计算。
3. **对数复杂度**：利用除法操作快速缩小问题规模，保证时间复杂度为 $O(\log N)$。

---

# 类似题目推荐
1. **AT188F**：大数处理与记忆化搜索的动态规划。
2. **洛谷P1464**：记忆化搜索的经典应用。
3. **CF55D**：数位DP与状态压缩的结合。

---

# 代码实现（核心片段）
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n, A;
double X, Y;
map<ll, double> dp;

double dfs(ll n) {
    if (n == 0) return 0.0;
    if (dp.count(n)) return dp[n];
    
    double op1 = dfs(n / A) + X;
    double sum = dfs(n/2) + dfs(n/3) + dfs(n/4) + dfs(n/5) + dfs(n/6);
    double op2 = (sum / 5.0) + Y * 1.2;
    
    return dp[n] = min(op1, op2);
}

int main() {
    cin >> n >> A >> X >> Y;
    cout << fixed << setprecision(15) << dfs(n);
    return 0;
}
```

---

# 可视化方案（Canvas伪代码）
```javascript
// 初始化 Canvas
const canvas = document.getElementById('dp-canvas');
const ctx = canvas.getContext('2d');

// 绘制状态节点
function drawNode(n, x, y, isCached) {
    ctx.fillStyle = isCached ? '#00FF00' : '#FF0000';
    ctx.fillRect(x, y, 30, 30);
    ctx.fillStyle = '#000';
    ctx.fillText(n.toString(), x + 5, y + 20);
}

// 递归动画
async function animateDFS(n, parentX, parentY) {
    if (n === 0) return;
    const cached = dpMap.has(n);
    drawNode(n, currentX, currentY, cached);
    if (!cached) {
        playSound('compute');
        await delay(500);
        // 绘制子节点
        animateDFS(n/A, currentX, currentY);
        animateDFS(n/2, currentX, currentY);
        // ...其他子节点
    }
}
```

---
处理用时：93.09秒