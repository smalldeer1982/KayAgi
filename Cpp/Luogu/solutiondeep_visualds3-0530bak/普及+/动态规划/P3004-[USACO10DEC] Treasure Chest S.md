# 题目信息

# [USACO10DEC] Treasure Chest S

## 题目描述

Bessie and Bonnie have found a treasure chest full of marvelous gold coins! Being cows, though, they can't just walk into a store and buy stuff, so instead they decide to have some fun with the coins.

The N (1 <= N <= 5,000) coins, each with some value C\_i (1 <= C\_i <= 5,000) are placed in a straight line. Bessie and Bonnie take turns, and for each cow's turn, she takes exactly one coin off of either the left end or the right end of the line. The game ends when there are no coins left.

Bessie and Bonnie are each trying to get as much wealth as possible for themselves. Bessie goes first. Help her figure out the maximum value she can win, assuming that both cows play optimally.

Consider a game in which four coins are lined up with these values:

30  25  10  35

Consider this game sequence:

Bessie    Bonnie       New Coin

Player   Side   CoinValue   Total     Total         Line

Bessie   Right     35        35         0       30  25  10

Bonnie   Left      30        35        30         25  10

Bessie   Left      25        60        30           10

Bonnie   Right     10        60        40           --

This is the best game Bessie can play.

小 A 和小 B 在玩游戏。

初始时，有 $n$ 个硬币被摆成了一行，从左至右数第 $i$ 个硬币的价值为 $c_i$。

小 A 和小 B 每人一回合，在一个人的回合中，他可以选择**当前**硬币序列最左侧或者最右侧的硬币，并将他从序列中取出，将其价值累加到自己获得的累计价值中，然后进行另一个人的回合。当硬币全部被取走时，游戏结束。

请求出在双方都尽可能的使自己累计价值最大的情况下，若由小 A 进行第一回合，那么他能获得的累计价值最大是多少。

## 说明/提示

#### 输入输出样例 $1$ 解释

初始时，硬币序列为 $\{30,~25,~10,~35\}$。

第一回合，小 A 取走最右侧的硬币，序列变为 $\{30,~25,~10\}$，小 A 的累加价值为 $35$。

第二回合，小 B 取走最左侧的硬币，序列变为 $\{25,~10\}$，小 B 的累加价值为 $30$。

第三回合，小 A 取走最左侧的硬币，序列变为 $\{10\}$，小 A 的累加价值为 $35 + 25 = 60$。

第四回合，小 B 取走最左侧的硬币，序列变为空，小 B 的累加价值为 $30 + 10 = 40$，游戏结束。

小 A 获得的最大累计价值为 $60$。

#### 数据范围与约定

对于全部的测试点，$1 \leq n \leq 5 \times 10^3$，$1 \leq c_i \leq 5 \times 10^3$。

**提示：请注意，本题的空间限制为 $64$ Mib。**

## 样例 #1

### 输入

```
4 
30 
25 
10 
35 
```

### 输出

```
60 
```

# AI分析结果



## 算法分类
**线性DP**

---

## 题解分析与结论

### 核心思路
所有题解的核心均为**区间动态规划**，状态定义为 `f[l][r]` 表示在区间 `[l, r]` 中先手能获得的最大价值。状态转移方程：
```math
f[l][r] = sum(l,r) - min(f[l+1][r], f[l][r-1])
```
其中 `sum(l,r)` 为区间和，`min` 对应对手的最优策略选择。

### 解决难点
1. **空间优化**：直接开二维数组 `f[5000][5000]` 会导致 MLE。  
   - **滚动数组**：利用区间 DP 的更新顺序特性，用一维数组 `f[i]` 表示以 `i` 为起点，当前长度区间的最优解（如逝星DS、＂黎筱っ的题解）。  
   - **动态内存**：仅存储 `i ≤ j` 的 `f[i][j]`，通过指针数组动态分配内存（如ghj1222的题解）。  
2. **正确性证明**：贪心解法（如Kinandra、tuliwei的题解）需严格证明其正确性，但未给出充分依据，存在风险。

### 关键优化对比
| 题解作者      | 空间优化方法          | 时间复杂度 | 代码复杂度 |
|-----------|-----------------|-------|-------|
| 逝星DS      | 一维滚动数组          | O(n²) | 低     |
| ghj1222   | 动态指针数组          | O(n²) | 中     |
| Kinandra  | 贪心（未严格证明）       | O(n)  | 高     |

---

## 题解评分（≥4星）
1. **逝星DS（5星）**  
   - 亮点：一维滚动数组简洁高效，代码清晰易读。  
   - 代码片段：  
     ```cpp
     for(int len=2; len<=N; len++)
         for(int i=1; i+len-1<=N; i++)
             f[i] = sum[i+len-1] - sum[i-1] - min(f[i], f[i+1]);
     ```

2. **＂黎筱っ（4星）**  
   - 亮点：详细解释滚动数组原理，适合动态规划初学者。  
   - 代码片段：  
     ```cpp
     for(int l=2; l<=n; ++l)
         for(int i=1; i+l-1<=n; ++i)
             f[i] = a[i+l-1] - a[i-1] - min(f[i+1], f[i]);
     ```

3. **览遍千秋（4星）**  
   - 亮点：代码简洁，前缀和与滚动数组结合紧密。  
   - 代码片段：  
     ```cpp
     for(int len=2; len<=n; len++)
         for(int l=1; l+len<=n+1; l++)
             opt[l] = sum[r] - sum[l-1] - min(opt[l], opt[l+1]);
     ```

---

## 最优思路提炼
1. **状态设计**：区间 `[l, r]` 的最优解 `f[l][r]`，通过对手的最优选择反向推导。  
2. **滚动数组优化**：逆序更新一维数组，利用区间长度递增的特性覆盖旧状态。  
3. **前缀和加速**：用 `sum[r] - sum[l-1]` 替代二维区间和数组，减少空间占用。

---

## 同类题目推荐
1. **P2734 [USACO3.3] 游戏 A Game**：几乎相同的区间 DP 模型。  
2. **P1880 [NOI1995] 石子合并**：环形区间 DP，需处理环形展开。  
3. **P1430 序列取数**：类似的双端选择问题，需优化时间复杂度。

---

## 可视化与算法演示

### 动态规划矩阵更新动画
1. **初始状态**：  
   - 对角线 `f[i][i] = c[i]`（黄色高亮）。  
   - 示例：`n=4` 时初始矩阵为：  
     ```
     30  0   0   35
     0   25  0   0
     0   0   10  0
     35  0   0   35
     ```

2. **步进更新**：  
   - 长度 `len=2` 时，计算 `f[1][2] = sum(1,2) - min(f[2][2], f[1][1]) = 55 - 25 = 30`，更新为绿色。  
   - 逐步填充上三角区域，颜色渐变表示不同区间长度。

3. **滚动数组效果**：  
   - 用一维数组模拟二维更新，高亮当前更新的 `f[i]`（红色闪烁）。  
   - 示例：`len=3` 时，`f[1]` 更新为 `sum(1,3) - min(f[2], f[1])`。

### 复古像素风格设计
- **Canvas 绘制**：  
  - 8位像素网格，每个格子表示 `f[i][j]`，底色为深蓝，文字为黄色。  
  - 更新时播放 `8-bit` 音效（类似《超级玛丽》金币声）。  

- **自动演示模式**：  
  - 点击“Auto”按钮，算法自动以 500ms/步的速度填充矩阵。  
  - 支持暂停/继续，拖动速度条调节动画速度（100ms~2000ms）。  

- **音效触发**：  
  - 状态转移：短促“哔”声（Web Audio API 合成）。  
  - 完成计算：播放《塞尔达传说》解谜成功音效。  

---

## 核心代码实现
```cpp
#include <iostream>
using namespace std;

int N, c[5010], sum[5010], f[5010];

int main() {
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> c[i];
        sum[i] = sum[i-1] + c[i];
        f[i] = c[i]; // 初始化长度为1的区间
    }
    for (int len = 2; len <= N; ++len)
        for (int i = 1; i + len - 1 <= N; ++i)
            f[i] = sum[i+len-1] - sum[i-1] - min(f[i], f[i+1]);
    cout << f[1];
    return 0;
}
```

---

## 个人心得摘录
- **ghj1222**：  
  > “做题要早一点做否则改了内存就gg了”——空间优化需提前规划，避免重构代码。  
- **逝星DS**：  
  > “观察状态转移方程发现可以滚动优化”——逆向思维发现维度可压缩。  
- **Kinandra**：  
  > “贪心解法欢迎证伪”——非DP解法需谨慎验证边界条件。

---
处理用时：89.64秒