# 题目信息

# Monsters (easy version)

## 题目描述

This is the easy version of the problem. In this version, you only need to find the answer once. In this version, hacks are not allowed.

In a computer game, you are fighting against $ n $ monsters. Monster number $ i $ has $ a_i $ health points, all $ a_i $ are integers. A monster is alive while it has at least $ 1 $ health point.

You can cast spells of two types:

1. Deal $ 1 $ damage to any single alive monster of your choice.
2. Deal $ 1 $ damage to all alive monsters. If at least one monster dies (ends up with $ 0 $ health points) as a result of this action, then repeat it (and keep repeating while at least one monster dies every time).

Dealing $ 1 $ damage to a monster reduces its health by $ 1 $ .

Spells of type 1 can be cast any number of times, while a spell of type 2 can be cast at most once during the game.

What is the smallest number of times you need to cast spells of type 1 to kill all monsters?

## 说明/提示

In the first test case, the initial health points of the monsters are $ [3, 1, 2] $ . It is enough to cast a spell of type 2:

- Monsters' health points change to $ [2, 0, 1] $ . Since monster number $ 2 $ dies, the spell is repeated.
- Monsters' health points change to $ [1, 0, 0] $ . Since monster number $ 3 $ dies, the spell is repeated.
- Monsters' health points change to $ [0, 0, 0] $ . Since monster number $ 1 $ dies, the spell is repeated.
- Monsters' health points change to $ [0, 0, 0] $ .

Since it is possible to use no spells of type 1 at all, the answer is $ 0 $ .

In the second test case, the initial health points of the monsters are $ [4, 1, 5, 4, 1, 1] $ . Here is one of the optimal action sequences:

- Using a spell of type 1, deal $ 1 $ damage to monster number $ 1 $ . Monsters' health points change to $ [3, 1, 5, 4, 1, 1] $ .
- Using a spell of type 1, deal $ 1 $ damage to monster number $ 4 $ . Monsters' health points change to $ [3, 1, 5, 3, 1, 1] $ .
- Using a spell of type 1, deal $ 1 $ damage to monster number $ 4 $ again. Monsters' health points change to $ [3, 1, 5, 2, 1, 1] $ .
- Use a spell of type 2:
  - Monsters' health points change to $ [2, 0, 4, 1, 0, 0] $ . Since monsters number $ 2 $ , $ 5 $ , and $ 6 $ die, the spell is repeated.
  - Monsters' health points change to $ [1, 0, 3, 0, 0, 0] $ . Since monster number $ 4 $ dies, the spell is repeated.
  - Monsters' health points change to $ [0, 0, 2, 0, 0, 0] $ . Since monster number $ 1 $ dies, the spell is repeated.
  - Monsters' health points change to $ [0, 0, 1, 0, 0, 0] $ .
- Using a spell of type 1, deal $ 1 $ damage to monster number $ 3 $ . Monsters' health points change to $ [0, 0, 0, 0, 0, 0] $ .

Spells of type 1 are cast $ 4 $ times in total. It can be shown that this is the smallest possible number.

## 样例 #1

### 输入

```
2
3
3 1 2
6
4 1 5 4 1 1```

### 输出

```
0
4```

# AI分析结果



## 唯一算法分类
贪心

## 综合分析与结论
**核心思路**：将怪物血量排序后，通过贪心策略调整每个怪物的血量，使其形成严格递增序列（相邻差不超过1），从而最大化群体攻击（技能2）的触发次数。

**算法流程**：
1. **排序数组**：将怪物按血量从小到大排序。
2. **逐元素调整**：维护一个变量 `cnt`（初始为1），遍历排序后的数组。若当前元素 `a[i] >= cnt`，则将其调整为 `cnt`，并递增 `cnt`；否则跳过。
3. **计算总次数**：调整后的数组总和与原数组总和的差即为所需技能1的最小次数。

**难点解析**：
- **调整策略推导**：需确保每次群体攻击至少消灭一个怪物，触发连续攻击。调整后的序列必须满足严格递增或相邻差不超过1。
- **贪心选择证明**：每次调整都让当前怪物的血量尽可能小，同时保证后续怪物能继续触发群体攻击。

**可视化设计**：
- **动画演示**：用柱状图表示排序后的怪物血量，逐步调整每个柱子到目标高度（`cnt`），动态显示调整过程及总次数累计。
- **高亮操作**：调整的柱子用红色闪烁，当前 `cnt` 值用绿色标记。
- **复古风格**：8-bit像素风，每次调整播放“扣血”音效，群体攻击触发时播放连续攻击音效。

## 题解清单（≥4星）
1. **Alex_Wei（4.5星）**  
   **亮点**：理论推导严谨，代码简洁，时间复杂度分析清晰。  
   **核心代码**：
   ```cpp
   int cnt = 1;
   for (int i=1; i<=n; i++) {
       if (a[i] >= cnt) {
           ans += a[i] - cnt;
           cnt++;
       }
   }
   ```

2. **听取MLE声一片（4星）**  
   **亮点**：逻辑清晰，变量命名直观，代码可读性强。  
   **核心代码**：
   ```cpp
   int ans=0, cnt=1;
   for (int i=1; i<=n; i++) {
       if (a[i] < cnt) continue;
       ans += a[i] - cnt;
       cnt++;
   }
   ```

3. **c20231020（4星）**  
   **亮点**：完整的问题分析框架，包含错误思路排除和正确调整策略推导。  
   **核心代码**：
   ```cpp
   for (int i=1; i<=n; ++i) {
       if (a[i] > a[i-1]) act++;
       if (a[i] > act) {
           use += a[i] - act;
           a[i] = act;
       }
   }
   ```

## 最优思路提炼
**关键步骤**：
1. **排序**：确保调整后的序列满足贪心条件。
2. **严格递增调整**：维护 `cnt` 变量，将每个元素调整到 `cnt` 并递增。
3. **总和差值计算**：原总和减去调整后的总和即为答案。

**技巧**：
- 排序预处理简化后续调整。
- 维护变量代替数组修改，节省空间。

## 同类题型推荐
1. **CF977F Consecutive Subsequence**：类似严格递增序列调整。
2. **洛谷P1094 纪念品分组**：贪心策略调整元素配对。
3. **LeetCode 455. Assign Cookies**：排序后贪心匹配。

## 核心代码实现
```cpp
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int& x : a) cin >> x;
        sort(a.begin(), a.end());
        long long ans = 0, cnt = 1;
        for (int x : a) {
            if (x >= cnt) {
                ans += x - cnt;
                cnt++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

## 可视化算法演示（复古风格）
1. **Canvas绘制**：怪物血量用不同高度像素柱表示，排序后按序调整。
2. **音效设计**：
   - `attack.wav`：每次调整播放。
   - `combo.wav`：群体攻击连续触发时播放。
3. **自动演示**：按步长自动调整柱子，显示当前 `cnt` 值和总次数。

---

**总结**：通过排序与贪心调整，确保群体攻击最大化触发，是本题的最优解法。同类问题中，排序预处理与维护状态变量是常见技巧。

---
处理用时：210.44秒