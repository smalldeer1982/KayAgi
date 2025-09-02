# 题目信息

# Thief in a Shop

## 题目描述

A thief made his way to a shop.

As usual he has his lucky knapsack with him. The knapsack can contain $ k $ objects. There are $ n $ kinds of products in the shop and an infinite number of products of each kind. The cost of one product of kind $ i $ is $ a_{i} $ .

The thief is greedy, so he will take exactly $ k $ products (it's possible for some kinds to take several products of that kind).

Find all the possible total costs of products the thief can nick into his knapsack.

## 样例 #1

### 输入

```
3 2
1 2 3
```

### 输出

```
2 3 4 5 6
```

## 样例 #2

### 输入

```
5 5
1 1 1 1 1
```

### 输出

```
5
```

## 样例 #3

### 输入

```
3 3
3 5 11
```

### 输出

```
9 11 13 15 17 19 21 25 27 33
```

# AI分析结果



# 算法分类
**动态规划（完全背包）**

---

## 题解思路与解决难点

### 核心算法流程
1. **预处理物品价值**：将所有物品价值减去最小值，使其中一个物品价值为0，便于补足k个物品的数量。
2. **动态规划状态定义**：`dp[i]`表示凑出价值`i`所需的最小物品数。
3. **状态转移**：用完全背包思想更新`dp`数组，`dp[i] = min(dp[i], dp[i - (a[j] - min_val)] + 1)`。
4. **筛选结果**：若`dp[i] ≤ k`，则总价值为`i + k * min_val`。

### 解决难点
- **恰好k个物品的限制**：通过减去最小值引入0价值物品，允许补足不足的数量。
- **高效计算所有可能价值**：动态规划的时间复杂度为`O(n * k * max_a)`，通过预处理优化避免了暴力组合的指数级复杂度。

---

## 题解评分（≥4星）

### 1. QuZhan 题解（5星）
- **亮点**：代码简洁，预处理逻辑清晰，直接体现核心思路。
- **代码片段**：
```cpp
sort(a+1,a+n+1);
for (int i=1;i<=n;i++) b[i]=a[i]-a[1]; //预处理
for (int i=1;i<=n;i++)
    for (int j=b[i];j<N*N;j++)
        dp[j] = min(dp[j], dp[j-b[i]] + 1); //背包更新
```

### 2. zhoufangyuanPT 题解（4星）
- **亮点**：详细分析两种解法（DP与生成函数），对比优劣。
- **关键说明**：
  > "将物品价值减去最小值后，所有不足k个的方案可以通过加0补足。"

### 3. pldzy 题解（4星）
- **亮点**：代码注释明确，变量命名直观（如`limi = k * a[n]`）。
- **个人心得**：
  > "原本想直接暴力01背包，结果发现样例都过不了，这才意识到必须用预处理技巧。"

---

## 最优思路提炼

### 关键技巧
- **价值归一化**：所有物品减最小值，引入0价值物品简化问题。
- **完全背包优化**：用`dp[i]`记录最小物品数，将原问题转化为可行性判断。

### 同类型题套路
- **扩展问题**：若要求恰好选`k`个物品且总价值最大/最小，可用类似预处理技巧。
- **类似题目**：完全背包的变形问题，如[CF981D](https://codeforces.com/problemset/problem/981/D)。

---

## 推荐题目
1. **P1616 疯狂的采药**（完全背包模板）
2. **P1776 宝物筛选**（多重背包优化）
3. **CF981D Bookshelves**（位运算+动态规划）

---

## 可视化设计

### 动画方案
1. **DP状态更新**：
   - **高亮当前物品**（红色框），逐步更新`dp`数组。
   - 显示`dp[i]`值变化过程，绿色表示有效更新。
2. **复古像素风格**：
   - **Canvas绘制**：物品显示为像素方块，背包状态用网格表示。
   - **音效**：每次更新`dp`时播放“嘀”声，找到可行解时播放“成功”音效。

### 交互功能
- **步进控制**：支持暂停/继续/单步执行。
- **参数调节**：允许修改`n`、`k`和物品价值，实时观察算法变化。

---

## 代码实现（核心逻辑）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5, M=1e6+5;
int dp[M], a[N], n, k;

int main() {
    cin >> n >> k;
    int min_val = INT_MAX;
    for (int i=1; i<=n; i++) {
        cin >> a[i];
        min_val = min(min_val, a[i]);
    }
    // 预处理：所有物品价值减最小值
    for (int i=1; i<=n; i++) a[i] -= min_val;
    
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    // 完全背包更新dp数组
    for (int i=1; i<=n; i++) {
        for (int j=a[i]; j<=k*1000; j++) {
            dp[j] = min(dp[j], dp[j - a[i]] + 1);
        }
    }
    // 输出所有满足条件的结果
    for (int i=0; i<=k*1000; i++) {
        if (dp[i] <= k) cout << i + k*min_val << " ";
    }
    return 0;
}
```

---
处理用时：74.94秒