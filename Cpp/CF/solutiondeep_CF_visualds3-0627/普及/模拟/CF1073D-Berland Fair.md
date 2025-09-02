# 题目信息

# Berland Fair

## 题目描述

XXI Berland Annual Fair is coming really soon! Traditionally fair consists of $ n $ booths, arranged in a circle. The booths are numbered $ 1 $ through $ n $ clockwise with $ n $ being adjacent to $ 1 $ . The $ i $ -th booths sells some candies for the price of $ a_i $ burles per item. Each booth has an unlimited supply of candies.

Polycarp has decided to spend at most $ T $ burles at the fair. However, he has some plan in mind for his path across the booths:

- at first, he visits booth number $ 1 $ ;
- if he has enough burles to buy exactly one candy from the current booth, then he buys it immediately;
- then he proceeds to the next booth in the clockwise order (regardless of if he bought a candy or not).

Polycarp's money is finite, thus the process will end once he can no longer buy candy at any booth.

Calculate the number of candies Polycarp will buy.

## 说明/提示

Let's consider the first example. Here are Polycarp's moves until he runs out of money:

1. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 33 $ ;
2. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 31 $ ;
3. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 26 $ ;
4. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 21 $ ;
5. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 19 $ ;
6. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 14 $ ;
7. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 9 $ ;
8. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 7 $ ;
9. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 2 $ ;
10. Booth $ 1 $ , buys no candy, not enough money;
11. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 0 $ .

No candy can be bought later. The total number of candies bought is $ 10 $ .

In the second example he has $ 1 $ burle left at the end of his path, no candy can be bought with this amount.

## 样例 #1

### 输入

```
3 38
5 2 5
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 21
2 4 100 2 6
```

### 输出

```
6
```

# AI分析结果



# Berland Fair 题解分析

## 唯一算法分类
**贪心算法 + 数学优化**

---

## 综合分析与结论
### 核心思路与难点
1. **核心思路**：  
   - 每次计算当前可购买的摊位总和 `sum`，尽可能多地转完整圈数 `m // sum`，快速累加答案。
   - 剩余钱数通过取模 `m %= sum` 减少规模，每次取模后钱数至少减半。
   - 删除无法购买的摊位（价格超过当前剩余钱），动态更新 `sum` 和摊位数量。

2. **解决难点**：  
   - **暴力模拟超时**：直接逐次购买会因 T 极大（1e18）导致超时。
   - **数学优化**：利用模运算将时间复杂度从 O(T) 优化至 O(n log T)。

### 算法流程与可视化设计
1. **可视化设计**：
   - **动态更新摊位**：用不同颜色标记可用/已删除的摊位（如绿色可用，红色删除）。
   - **钱数变化动画**：显示每轮完整圈数购买后钱数的减少与取模过程。
   - **复古像素风格**：摊位排列为环形像素网格，钱数变化以 8 位数字滚动显示，音效触发关键操作（如转圈、删除摊位）。
   - **步进控制**：允许单步执行观察每轮 `sum` 计算与摊位删除。

---

## 题解评分 (≥4星)
1. **Ynoi 题解 (4.5星)**  
   - **亮点**：代码简洁，核心逻辑清晰，利用模运算快速减少问题规模。
   - **优化点**：变量命名可读性稍差（如 `rs` 建议改为 `candies_per_round`）。

2. **信息向阳花木 题解 (4.5星)**  
   - **亮点**：注释详细，变量命名合理（`sum`, `cnt`），可读性强。
   - **优化点**：循环条件可合并减少冗余计算。

3. **傅思维666 题解 (4星)**  
   - **亮点**：引入标记数组动态删除摊位，避免重复无效检查。
   - **优化点**：初始代码存在 TLE 问题，需结合优化思路。

---

## 最优思路与代码实现
### 关键代码片段（Ynoi 题解核心逻辑）
```cpp
while (true) {
    LL sum = 0, cnt = 0;
    // 计算当前一圈的总花费 sum 和可购买次数 cnt
    for (int i = 1; i <= n; ++i) {
        if (sum + a[i] <= m) {
            sum += a[i];
            cnt++;
        }
    }
    if (sum == 0) break;
    ans += (m / sum) * cnt; // 累加完整圈数的答案
    m %= sum;               // 剩余钱数取模
}
```

### 完整代码（优化版）
```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    int n;
    LL m;
    cin >> n >> m;
    vector<LL> a(n);
    for (auto &x : a) cin >> x;

    LL ans = 0;
    while (true) {
        LL sum = 0, cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i] <= m - sum) {
                sum += a[i];
                cnt++;
            }
        }
        if (sum == 0) break;
        ans += (m / sum) * cnt;
        m %= sum;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 类似题目与拓展
1. **同类型题**  
   - **约瑟夫问题**：循环删除元素，动态调整剩余集合。
   - **CF 939E Maximize!**：贪心维护最小值优化计算。

2. **推荐题目**  
   - **洛谷 P1031 均分纸牌**：循环处理与动态调整。
   - **洛谷 P1080 国王游戏**：贪心策略与数学证明。
   - **CF 1526C2 Potions**：动态选择与总和优化。

---

## 个人心得摘录
- **调试教训**：初始代码未处理 `sum=0` 导致死循环，需增加终止条件。
- **优化顿悟**：取模操作可将钱数指数级减少，避免逐次减法。

---

## 可视化与复古游戏化设计
### 动画方案
1. **Canvas 布局**：  
   - 环形排列摊位，每个摊位显示价格与状态（绿色可用/红色不可用）。
   - 右侧面板显示当前钱数 `m` 和总糖果数 `ans`。

2. **关键动画**：  
   - **转圈购买**：高亮当前处理的摊位，显示 `sum` 累加过程。
   - **模运算触发**：钱数快速减少时播放“金币掉落”音效。
   - **摊位删除**：不可用摊位变为红色并下沉消失，伴随“错误”音效。

3. **复古风格**：  
   - **调色板**：16色，主色调为深蓝（背景）、亮绿（可用摊位）、暗红（删除摊位）。
   - **音效**：8位芯片音效，购买成功时短促“滴”声，模运算触发长音。

### 交互功能
- **步进控制**：暂停/继续按钮，拖动进度条调节动画速度。
- **AI 模式**：自动运行并高亮算法关键决策点（如 `sum` 计算、摊位删除）。

---

**通过上述分析与实现，可深入理解贪心与数学优化在循环问题中的应用，并借助可视化工具直观掌握算法流程。**

---
处理用时：85.16秒