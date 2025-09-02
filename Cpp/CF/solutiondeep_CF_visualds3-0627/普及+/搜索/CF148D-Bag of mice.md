# 题目信息

# Bag of mice

## 题目描述

The dragon and the princess are arguing about what to do on the New Year's Eve. The dragon suggests flying to the mountains to watch fairies dancing in the moonlight, while the princess thinks they should just go to bed early. They are desperate to come to an amicable agreement, so they decide to leave this up to chance.

They take turns drawing a mouse from a bag which initially contains $ w $ white and $ b $ black mice. The person who is the first to draw a white mouse wins. After each mouse drawn by the dragon the rest of mice in the bag panic, and one of them jumps out of the bag itself (the princess draws her mice carefully and doesn't scare other mice). Princess draws first. What is the probability of the princess winning?

If there are no more mice in the bag and nobody has drawn a white mouse, the dragon wins. Mice which jump out of the bag themselves are not considered to be drawn (do not define the winner). Once a mouse has left the bag, it never returns to it. Every mouse is drawn from the bag with the same probability as every other one, and every mouse jumps out of the bag with the same probability as every other one.

## 说明/提示

Let's go through the first sample. The probability of the princess drawing a white mouse on her first turn and winning right away is 1/4. The probability of the dragon drawing a black mouse and not winning on his first turn is 3/4 \* 2/3 = 1/2. After this there are two mice left in the bag — one black and one white; one of them jumps out, and the other is drawn by the princess on her second turn. If the princess' mouse is white, she wins (probability is 1/2 \* 1/2 = 1/4), otherwise nobody gets the white mouse, so according to the rule the dragon wins.

## 样例 #1

### 输入

```
1 3
```

### 输出

```
0.500000000
```

## 样例 #2

### 输入

```
5 5
```

### 输出

```
0.658730159
```

# AI分析结果



## 算法分类选择
**其他搜索**（动态规划的概率DP问题，部分题解采用记忆化搜索实现）

---

## 题解思路与核心难点分析

### 题解思路
所有题解均基于动态规划，状态定义为 `dp[i][j]` 表示剩余 `i` 白鼠和 `j` 黑鼠时公主获胜的概率：
1. **初始状态**：`dp[i][0]=1`（全白必胜），`dp[0][j]=0`（全黑必败）。
2. **转移方程**：
   - 公主直接抓白鼠：概率为 `i/(i+j)`。
   - 公主抓黑鼠，龙抓黑鼠后逃跑一只：
     - 逃跑白鼠：概率为 `j/(i+j) * (j-1)/(i+j-1) * i/(i+j-2)`，转移到 `dp[i-1][j-2]`。
     - 逃跑黑鼠：概率为 `j/(i+j) * (j-1)/(i+j-1) * (j-2)/(i+j-2)`，转移到 `dp[i][j-3]`。

### 解决难点
1. **条件分治**：需严格处理龙抓黑鼠后的逃跑逻辑，分白鼠逃跑和黑鼠逃跑两种情况。
2. **边界处理**：当剩余鼠数不足时（如 `j=0` 或 `j=1`），需单独处理。
3. **浮点精度**：多次概率连乘需注意浮点精度误差。

---

## 高星题解推荐（≥4星）
1. **yingyudou（5星）**
   - **亮点**：提供递推和记忆化搜索两种实现，代码结构清晰，注释详细。
   - **代码片段**：
     ```cpp
     // 记忆化搜索实现
     double dfs(int i, int j) {
         if (f[i][j]) return f[i][j];
         if (!i) return 0;
         if (!j) return 1.0;
         f[i][j] = 1.0 * i / (i + j);
         if (j >= 2) f[i][j] += ... // 分情况累加概率
         return f[i][j];
     }
     ```

2. **Pathetique（4星）**
   - **亮点**：纯记忆化搜索实现，仅计算有效状态，避免无效遍历。
   - **心得**：强调“只搜索有用状态”，减少计算量。

3. **mzgwty（4星）**
   - **亮点**：代码简洁，直接按递推公式实现，适合快速理解核心逻辑。

---

## 最优思路提炼
1. **状态设计**：二维状态 `(i,j)` 表示剩余白鼠和黑鼠数量。
2. **记忆化搜索优化**：通过递归缓存中间结果，避免重复计算。
3. **概率分治**：将复杂事件拆分为独立概率事件，累加所有可能路径。

---

## 同类型题与算法套路
- **类似题目**：博弈论中的概率DP（如抓石子、抽卡策略）。
- **通用解法**：状态表示当前局面，分步计算转移概率，最终累加获胜路径。

---

## 推荐相似题目
1. **P2473 [SCOI2008] 奖励关**（概率DP + 状态压缩）
2. **P1850 [NOIP2016 提高组] 换教室**（期望DP + 路径规划）
3. **P4548 [CTSC2006] 歌唱王国**（概率生成函数 + 递推）

---

## 可视化与算法演示
### 动态规划状态转移可视化
- **动画设计**：
  - **网格图**：横纵轴表示白鼠和黑鼠数量，每个格子显示 `dp[i][j]` 的值。
  - **颜色渐变**：用颜色深浅表示概率高低（深色高概率，浅色低概率）。
  - **转移箭头**：高亮当前状态 `(i,j)` 的转移来源（如 `(i-1,j-2)` 和 `(i,j-3)`）。

### 复古像素风格实现
- **Canvas绘制**：8位风格网格，节点用像素块表示，访问时播放“滴”音效。
- **自动演示**：按递推顺序遍历状态，单步显示概率计算过程。
- **交互控制**：支持暂停/继续，调节动画速度。

---

## 核心代码实现（记忆化搜索）
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
double dp[N][N];

double dfs(int w, int b) {
    if (w <= 0) return 0;
    if (b <= 0) return 1;
    if (dp[w][b] > 0) return dp[w][b];
    
    double win = 1.0 * w / (w + b); // 直接抓白鼠
    if (b >= 2) {
        double p_bb = 1.0 * b / (w + b) * (b - 1) / (w + b - 1);
        if (b >= 3) { // 逃跑黑鼠
            win += p_bb * (b - 2.0) / (w + b - 2) * dfs(w, b - 3);
        }
        if (w >= 1) { // 逃跑白鼠
            win += p_bb * w / (w + b - 2) * dfs(w - 1, b - 2);
        }
    }
    return dp[w][b] = win;
}

int main() {
    int w, b; cin >> w >> b;
    printf("%.9lf\n", dfs(w, b));
    return 0;
}
```

---
处理用时：174.04秒