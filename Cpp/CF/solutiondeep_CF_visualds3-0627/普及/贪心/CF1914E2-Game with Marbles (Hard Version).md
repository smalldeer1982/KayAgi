# 题目信息

# Game with Marbles (Hard Version)

## 题目描述

The easy and hard versions of this problem differ only in the constraints on the number of test cases and $ n $ . In the hard version, the number of test cases does not exceed $ 10^4 $ , and the sum of values of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ . Furthermore, there are no additional constraints on $ n $ in a single test case.

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
**题目核心思路**：  
Alice和Bob的弹珠游戏本质是轮流选择双方共有的颜色，每次选择后对方清空该颜色。最终得分是Alice剩余弹珠数减去Bob的。关键在于确定双方的最优选择顺序。  

**贪心策略**：  
- **核心观察**：每次选择颜色时，对总得分的贡献为 `(a_i - 1)`（Alice选）或 `-(b_i - 1)`（Bob选）。  
- **排序依据**：按 `a_i + b_i` 降序排序。总和越大，说明该颜色对两人总剩余的影响越大，优先处理可最大化Alice的收益或最小化Bob的损失。  
- **实现方式**：轮流选择排序后的颜色，奇数次由Alice加分，偶数次由Bob减分。  

**正确性证明**：  
初始所有颜色可用，每次选当前最优（最大 `a_i + b_i`），处理后对方颜色清空，后续颜色处理不受影响。排序确保每一步选择全局最优，最终总得分最优。  

**可视化设计**：  
- **动画演示**：颜色块按 `a_i + b_i` 排序，高亮当前处理项，显示得分变化。  
- **复古风格**：像素化颜色块，音效提示选择动作，自动播放或步进控制。  
- **交互面板**：支持暂停、步进、速度调节，对比不同排序策略的效果。  

---

### 题解评分（≥4星）  
1. **abensyl（5星）**  
   - **亮点**：代码简洁，优先队列排序，直接累加得分。  
   - **代码可读性**：逻辑清晰，无冗余操作。  
   - **算法优化**：时间复杂度 `O(n log n)`，完美适配数据规模。  

2. **Erica_N_Contina（4星）**  
   - **亮点**：结构体排序，明确得分贡献计算。  
   - **代码结构**：易扩展，注释详细。  
   - **实现细节**：处理奇偶轮次逻辑清晰。  

3. **KID2695（4星）**  
   - **亮点**：代码极简，运算符重载排序。  
   - **实践性**：适合快速实现，核心逻辑一目了然。  

---

### 最优思路与技巧提炼  
1. **贪心选择依据**：`a_i + b_i` 排序确保每一步最优。  
2. **奇偶轮次处理**：Alice和Bob交替选择，直接加减对应贡献。  
3. **时间复杂度优化**：排序后线性遍历，避免复杂判断。  

**关键代码片段**：  
```cpp
sort(color.begin(), color.end(), [](auto& x, auto& y) {
    return x.a + x.b > y.a + y.b;
});
for (int i = 0; i < n; i++) {
    if (i % 2 == 0) score += color[i].a - 1;
    else score -= color[i].b - 1;
}
```

---

### 同类型题目推荐  
1. **P1080 国王游戏**：贪心排序确定最优队列。  
2. **P1230 智力大冲浪**：时间窗口下的任务选择。  
3. **P1094 纪念品分组**：双指针贪心配对。  

---

### 个人心得摘录  
- **abensyl**：总和排序直接解决优先级，无需复杂动态判断。  
- **KID2695**：代码精简是竞赛中的优势，避免过度设计。  
- **调试经验**：初始错误尝试按单一弹珠数排序，后通过样例发现必须考虑双方总和。  

---

### 可视化与算法演示  
**动画方案**：  
1. **初始化**：颜色块按 `a_i + b_i` 降序排列，显示当前得分。  
2. **每一步选择**：高亮当前颜色，播放音效，更新得分。  
3. **效果反馈**：处理后的颜色变灰，对方数量清零。  

**复古游戏化设计**：  
- **8位像素风格**：颜色块用像素方格表示，背景音乐循环。  
- **音效提示**：选择时“哔”声，得分变化时不同音调。  
- **自动演示**：AI按贪心策略自动执行，支持暂停/继续。  

---

### 参考代码（abensyl）  
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    priority_queue<pair<ll, int>> pq;
    for (int i = 0; i < n; i++) {
        pq.push({a[i] + b[i], i});
    }
    ll score = 0;
    for (int turn = 0; !pq.empty(); turn++) {
        auto [sum, idx] = pq.top();
        pq.pop();
        if (turn % 2 == 0) score += a[idx] - 1;
        else score -= b[idx] - 1;
    }
    cout << score << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
```

---
处理用时：227.86秒