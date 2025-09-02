# 题目信息

# Game with Marbles (Easy Version)

## 题目描述

The easy and hard versions of this problem differ only in the constraints on the number of test cases and $ n $ . In the easy version, the number of test cases does not exceed $ 10^3 $ , and $ n $ does not exceed $ 6 $ .

Recently, Alice and Bob were given marbles of $ n $ different colors by their parents. Alice has received $ a_1 $ marbles of color $ 1 $ , $ a_2 $ marbles of color $ 2 $ ,..., $ a_n $ marbles of color $ n $ . Bob has received $ b_1 $ marbles of color $ 1 $ , $ b_2 $ marbles of color $ 2 $ , ..., $ b_n $ marbles of color $ n $ . All $ a_i $ and $ b_i $ are between $ 1 $ and $ 10^9 $ .

After some discussion, Alice and Bob came up with the following game: players take turns, starting with Alice. On their turn, a player chooses a color $ i $ such that both players have at least one marble of that color. The player then discards one marble of color $ i $ , and their opponent discards all marbles of color $ i $ . The game ends when there is no color $ i $ such that both players have at least one marble of that color.

The score in the game is the difference between the number of remaining marbles that Alice has and the number of remaining marbles that Bob has at the end of the game. In other words, the score in the game is equal to $ (A-B) $ , where $ A $ is the number of marbles Alice has and $ B $ is the number of marbles Bob has at the end of the game. Alice wants to maximize the score, while Bob wants to minimize it.

Calculate the score at the end of the game if both players play optimally.

## 说明/提示

In the first example, one way to achieve a score of $ 1 $ is as follows:

1. Alice chooses color $ 1 $ , discards $ 1 $ marble. Bob also discards $ 1 $ marble;
2. Bob chooses color $ 3 $ , discards $ 1 $ marble. Alice also discards $ 1 $ marble;
3. Alice chooses color $ 2 $ , discards $ 1 $ marble, and Bob discards $ 2 $ marble.

As a result, Alice has $ a = [3, 1, 0] $ remaining, and Bob has $ b = [0, 0, 3] $ remaining. The score is $ 3 + 1 - 3 = 1 $ .

It can be shown that neither Alice nor Bob can achieve a better score if both play optimally.

In the second example, Alice can first choose color $ 1 $ , then Bob will choose color $ 4 $ , after which Alice will choose color $ 2 $ , and Bob will choose color $ 3 $ . It can be shown that this is the optimal game.

## 样例 #1

### 输入

```
5
3
4 2 1
1 2 4
4
1 20 1 20
100 15 10 20
5
1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1
3
5 6 5
2 1 7
6
3 2 4 2 5 5
9 4 7 9 2 5```

### 输出

```
1
-9
2999999997
8
-6```

# AI分析结果



### 综合分析与结论

**题目核心**：Alice和Bob轮流选择双方共有弹珠的颜色，每次操作会清空对方的该颜色弹珠。目标是最大化最终得分（Alice剩余弹珠数 - Bob剩余弹珠数），双方均采取最优策略。

**贪心策略核心**：
1. **贡献值排序**：每个颜色 $i$ 的总贡献值为 $a_i + b_i$，该值越大，说明双方在该颜色的争夺中总收益越高。
2. **交替选择**：按总贡献值从大到小排序，Alice（先手）和Bob（后手）轮流选择当前最大贡献值的颜色，奇数次由Alice选择，偶数次由Bob选择。
3. **得分计算**：Alice选择颜色 $i$ 的贡献为 $(a_i - 1)$，Bob选择的贡献为 $-(b_i - 1)$，最终累加所有贡献得到总分。

**正确性证明**：  
当双方选择总贡献值最大的颜色时，每一步的局部最优选择能保证全局最优。对于总贡献值相同的颜色，不同选择顺序的最终得分相同（数学可证），因此排序顺序不影响结果。

---

### 题解清单（≥4星）

1. **Elhaithan（★★★★☆）**  
   - **亮点**：代码简洁，直接按 $a_i + b_i$ 排序，奇偶轮次处理贡献，逻辑清晰。
   - **代码片段**：
     ```cpp
     sort(num+1, num+1+n);
     int res = 0;
     for(int i=1; i<=n; i++){
         if(i&1) res += num[i].a - 1;
         else res -= num[i].b - 1;
     }
     ```

2. **Erica_N_Contina（★★★★☆）**  
   - **亮点**：理论推导清晰，解释了贡献值的来源和贪心选择的正确性。
   - **代码片段**：
     ```cpp
     sort(t+1, t+n+1, cmp);
     for(int i=1; i<=n; i++){
         if(i&1) ans += t[i].a - 1;
         else ans -= t[i].b - 1;
     }
     ```

3. **wmrqwq（★★★★☆）**  
   - **亮点**：结合结构体排序和动态更新总和，代码可读性高。
   - **代码片段**：
     ```cpp
     sort(f + 1, f + n + 1, cmp);
     for(int i = 1; i <= n; i++){
         if(i % 2) res += a[i] - 1;
         else res -= b[i] - 1;
     }
     ```

---

### 最优思路或技巧提炼

1. **贪心选择依据**：总贡献值 $a_i + b_i$ 的降序排序是核心，确保每一步的局部最优。
2. **交替处理**：奇偶轮次区分Alice和Bob的选择，直接累加贡献值。
3. **数学性质**：总贡献值相同的颜色不影响最终得分，排序顺序无关紧要。

---

### 同类型题与算法套路

1. **博弈中的交替选择**：如取石子游戏、交替拿卡片最大分差问题。
2. **贪心排序应用**：区间调度（按结束时间排序）、最小生成树（Kruskal算法）等。
3. **对抗性策略**：极大极小算法（Minimax）的简化版，适用于有限步数博弈。

---

### 推荐题目

1. **洛谷 P1220**：区间贪心问题，需选择最优覆盖顺序。
2. **洛谷 P1090**：合并果子，贪心选择最小堆。
3. **Codeforces 455A**：动态规划与贪心结合，按数值频率选择。

---

### 可视化与算法演示

**核心贪心过程动画设计**：
1. **排序展示**：初始颜色列表按 $a_i + b_i$ 降序排列，用不同颜色区分Alice和Bob的操作。
2. **步进操作**：高亮当前选择的颜色，显示其 $a_i$ 和 $b_i$ 值，更新得分。
3. **弹珠变化**：每次操作后，对方对应颜色弹珠归零，己方减1，动态显示数值变化。

**复古游戏化效果**：
- **像素风格**：颜色块表示弹珠，8-bit音效提示选择（Alice操作高音，Bob低音）。
- **自动演示模式**：AI自动按贪心策略选择，可调节速度观察每一步。
- **积分系统**：正确选择得分，错误选择扣分，增强互动性。

---

### 代码实现（关键贪心逻辑）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

struct Node { int a, b; };
bool cmp(Node x, Node y) { return x.a + x.b > y.a + y.b; }

signed main() {
    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        vector<Node> colors(n);
        for(auto &c : colors) cin >> c.a;
        for(auto &c : colors) cin >> c.b;
        sort(colors.begin(), colors.end(), cmp);
        
        int score = 0;
        for(int i = 0; i < n; i++) {
            if(i % 2 == 0) score += colors[i].a - 1; // Alice
            else score -= colors[i].b - 1;            // Bob
        }
        cout << score << endl;
    }
    return 0;
}
```

**核心说明**：排序后遍历，奇偶轮次分别处理Alice和Bob的贡献，时间复杂度 $O(n \log n)$。

---
处理用时：174.67秒