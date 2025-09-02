# 题目信息

# [WFOI - 01] 硬币（coin）

## 题目描述

你面前有一排 $n$ **堆**硬币排成一线，**同一堆硬币**的面值相同，记第 $i$ 堆硬币的面值为 $a_i$。而**每堆硬币**的数量都相同，记为 $x$。

现在你知道每第 $i$ 堆硬币的面值 $a_i$，你需要确定一个**正整数** $x$，使得**每堆硬币的总金额的**方差最接近于一个**正整数** $k$。

两数 **“最接近”** 的定义：两数之差的绝对值最小。

方差定义：方差 $s ^ 2 = \cfrac{(a_1 - \bar x)^2 + (a_2 - \bar x) ^ 2 + \cdots + (a_n - \bar x) ^ 2}{n}$，其中 $\bar x$ 代表 $x$ 的平均值。

## 说明/提示


**【样例 $\#1$ 解释】**

  当 $x=3$ 时，第 $i$ 个堆的硬币金额为 $3\times a_i$，这些硬币堆的金额分别为 $21,6,12,18,9,21,30$，可以计算得这些硬币金额的方差约为 $58.78$，可以证明当 $x=3$ 时方差最接近 $47$。

**【样例 $\#2$ 解释】**

  可以发现，无论 $x$ 的取值，方差都会为 $0$，所以输出 `No answer!`。







**【数据规模】**

**本题采用 Subtask 捆绑测试。**

Subtask 编号 | $n,\forall a_i\le$ | $k\le$ | $\footnotesize\texttt{测试点数目}$ |
:-: | :-: | :-: | :-:
**Subtask #0 $(20\texttt{pts})$** | $10^3$ | $10^9$| $6$ |
**Subtask #1 $(25\texttt{pts})$** | $10^5$ | $10^{12}$| $6$ |
**Subtask #2 $(25\texttt{pts})$** | $10^5$ | $10^{18}$| $6$ |
**Subtask #3 $(30\texttt{pts})$** | $7\times10^6$ | $3\times 10^{18}$| $6$ |

对于 $100\%$ 的数据，$1\le n,\forall a_i\le7\times10^6$，$1\le k\le3\times10^{18}$。记原来 $a$ 数组的方差为 $p$，则数据满足 $p=0$ 或 $p\in[0.25,\ 2^{63}-1]$ 。





**【提示】**

  本题读入量较大，请使用合适的读入方式。此处推荐[快速读入模板](https://www.luogu.com.cn/paste/bcfvgxr7)，对于 $\texttt{C/C++}$ 语言，你也可以使用 `scanf` 语句完成读入。
  
  为避免卡精度，建议 `C/C++` 选手使用 $\texttt{double}$ 类型，并不建议使用 `eps`。

## 样例 #1

### 输入

```
7 47
7 2 4 6 3 7 10```

### 输出

```
3```

## 样例 #2

### 输入

```
4 4
4 4 4 4```

### 输出

```
No answer!```

# AI分析结果



# 硬币（coin）题解分析

## 唯一算法分类
**无算法分类**

---

## 题解思路与解决难点

### 核心思路
1. **方差倍率关系**：当每个硬币数量变为 `x` 倍时，方差变为原方差 `s²` 的 `x²` 倍。
2. **数学推导**：最优 `x` 满足 `x² * s² ≈ k`，即 `x ≈ sqrt(k/s²)`。
3. **候选值选取**：取 `x_floor = floor(sqrt(k/s²))` 和 `x_ceil = x_floor + 1`，比较两者对应的方差与 `k` 的接近程度。

### 解决难点
1. **精度处理**：浮点数运算可能存在精度损失，需确保 `x_floor` 和 `x_ceil` 的正确性。
2. **边界条件**：
   - 原方差为 0 时直接输出 `No answer!`。
   - `x_floor` 为 0 时只能取 `x=1`（因 `x` 必须为正整数）。
3. **候选值比较**：当两候选值方差与 `k` 的距离相等时，取较小的 `x`。

---

## 题解评分（≥4星）

### 1. Elgo87 题解（5星）
- **关键亮点**：
  - 直接推导公式，代码简洁高效。
  - 明确处理 `x=0` 的特殊情况。
  - 使用 `double` 避免精度问题，无需复杂优化。
- **代码片段**：
  ```cpp
  ll x = floor(sqrt(k/sum)), y = ceil(sqrt(k/sum));
  if (!x) printf("%lld\n", y);
  else if (fabs(x*x*sum -k) <= fabs(y*y*sum -k)) printf("%lld\n",x);
  else printf("%lld\n", y);
  ```

### 2. lnwhl 题解（4星）
- **关键亮点**：
  - 通过排序特判全相同元素，但时间复杂度较高（适合小数据）。
  - 通过遍历 `x` 的邻域（`ans-6` 到 `ans+6`）确保最优解。
- **代码片段**：
  ```cpp
  for (double i = max(1.0, ans-6.0); i <= ans+6.0; i += 1.0)
    if (abs(s*i*i -k) < minn) { /* 更新 ans */ }
  ```

### 3. Eason_AC 题解（4星）
- **关键亮点**：
  - 使用 `__int128` 处理大数运算。
  - 通过遍历邻域解决浮点误差问题。
- **代码片段**：
  ```cpp
  for (double i = max(1.0, ans-6.0); i <= ans+6.0; i += 1.0) { /* 比较 */ }
  ```

---

## 最优思路提炼
1. **公式推导**：利用方差与 `x²` 的正比关系直接计算候选值。
2. **边界处理**：
   - 原方差为 0 时直接无解。
   - `x_floor` 为 0 时强制取 `x=1`。
3. **候选值比较**：
   - 优先取 `x_floor` 和 `x_ceil` 中更接近 `k` 的值。
   - 距离相等时取较小值。

---

## 同类型题与算法套路
- **数学推导类**：如 [CF1114A](https://codeforces.com/problemset/problem/1114/A)，通过数学性质简化问题。
- **边界处理类**：如 [洛谷 P1024](https://www.luogu.com.cn/problem/P1024)，需处理浮点数的上下取整。

---

## 推荐相似题目
1. [P1024 一元三次方程求解](https://www.luogu.com.cn/problem/P1024)
2. [CF474B Worms](https://codeforces.com/problemset/problem/474/B)
3. [P1314 聪明的质监员](https://www.luogu.com.cn/problem/P1314)

---

## 个人心得摘录
- **精度陷阱**：避免直接用 `sqrt` 后取整，需验证邻域值（如 `x±1`）。
- **特殊测试点**：当 `k` 极小时，注意 `x=0` 的非法情况。

---

## 可视化设计（复古像素风格）
### 动画设计
- **Canvas 网格**：展示 `x` 从 `1` 到 `x_ceil` 的区间，高亮 `x_floor` 和 `x_ceil`。
- **颜色标记**：
  - **红色**：当前候选 `x`。
  - **绿色**：方差与 `k` 的距离。
- **音效**：
  - **更新候选**：8-bit 点击声。
  - **找到最优**：胜利音效。

### 交互设计
- **滑块调整 `k`**：动态更新方差曲线和候选 `x`。
- **自动演示**：按步长展示 `x` 的候选过程，类似“贪吃蛇 AI”逐步逼近。

---

## 核心代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    double sum = 0;
    for (auto &x : a) {
        cin >> x;
        sum += x;
    }
    double avg = sum / n;
    double s = 0;
    for (auto x : a) s += (x - avg) * (x - avg);
    s /= n;
    
    if (s == 0) {
        cout << "No answer!";
        return 0;
    }
    
    double x0 = sqrt(k / s);
    ll x_floor = floor(x0), x_ceil = ceil(x0);
    if (x_floor == 0) {
        cout << 1;
        return 0;
    }
    
    ll best_x = x_floor;
    double diff_floor = abs(s * x_floor * x_floor - k);
    double diff_ceil = abs(s * x_ceil * x_ceil - k);
    
    if (diff_ceil < diff_floor || (diff_ceil == diff_floor && x_ceil < x_floor))
        best_x = x_ceil;
    cout << best_x;
}
```

---
处理用时：183.33秒