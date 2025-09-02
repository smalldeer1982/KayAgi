# 题目信息

# Chess For Three

## 题目描述

Three friends gathered to play a few games of chess together.

In every game, two of them play against each other. The winner gets $ 2 $ points while the loser gets $ 0 $ , and in case of a draw, both players get $ 1 $ point each. Note that the same pair of players could have played any non-negative number of times (possibly zero). It is also possible that no games were played at all.

You've been told that their scores after all the games were played were $ p_1 $ , $ p_2 $ and $ p_3 $ . Additionally, it is guaranteed that $ p_1 \leq p_2 \leq p_3 $ holds.

Find the maximum number of draws that could have happened and print it. If there isn't any way to obtain $ p_1 $ , $ p_2 $ and $ p_3 $ as a result of a non-negative number of games between the three players, print $ -1 $ instead.

## 说明/提示

In the first example, no games were played at all, so no draws could occur either.

For the second example, exactly one game occurred between the second and the third player and it ended in draw, so the answer is $ 1 $ .

It's easy to see that there's no set of games achieving the scores in third example, so the answer for it is $ -1 $ .

## 样例 #1

### 输入

```
7
0 0 0
0 1 1
1 1 1
1 1 2
3 3 3
3 4 5
1 1 10```

### 输出

```
0
1
-1
2
-1
6
2```

# AI分析结果



---

## 算法分类  
**组合数学**  

---

## 综合分析与结论  
### 核心条件  
1. **总和必须为偶数**：每局比赛总贡献2分，总得分为 $s = p_1 + p_2 + p_3$，需满足 $s \mod 2 = 0$。  
2. **最大得分者的限制**：最大得分 $p_3$ 需满足 $p_3 \leq p_1 + p_2 + d$，其中 $d$ 为平局次数。  

### 关键推导  
- **总比赛次数**：$k = \frac{s}{2}$（因每场比赛贡献2分）。  
- **平局与胜负场次关系**：胜负场次 $w = k - d$。  
- **最大平局数的约束**：  
  - 平局次数 $d$ 需满足 $d \leq p_1 + p_2$（因每场平局最多增加 $p_1 + p_2$ 的总和）。  
  - 同时需满足 $d \geq p_3 - (p_1 + p_2)$（确保 $p_3$ 不超过其他两人得分与平局贡献的总和）。  

### 解决步骤  
1. **总和检查**：若 $s$ 为奇数，直接返回 `-1`。  
2. **合法性判断**：若 $p_3 > p_1 + p_2 + (k - (p_3 - (p_1 + p_2)))$，则无法构造解，返回 `-1`。  
3. **计算最大平局数**：$d = \min(p_1 + p_2, k - (p_3 - (p_1 + p_2)))$。  

---

## 题解评分  
**暂无评分 ≥4星的题解**  

---

## 最优思路提炼  
1. **总和奇偶性**：总和必须为偶数，否则直接排除。  
2. **平局贡献分析**：平局次数 $d$ 的上界由 $p_1 + p_2$ 决定，下界由 $p_3$ 与其他两人的得分差决定。  
3. **约束条件联立**：通过联立不等式确定 $d$ 的可行范围，并取最大值。  

---

## 类似算法套路  
**组合优化中的约束联立**：通过分析变量间的约束关系（如奇偶性、上下界）联立方程，找到可行解的最大/最小值。  

---

## 推荐题目  
1. **P1008 三连击**（组合数的构造与约束验证）  
2. **P1036 选数**（组合总和与质数判断）  
3. **P1157 组合的输出**（组合生成与剪枝）  

---

## 代码实现  
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int p[3];
        cin >> p[0] >> p[1] >> p[2];
        sort(p, p + 3);
        int p1 = p[0], p2 = p[1], p3 = p[2];
        int s = p1 + p2 + p3;
        
        if (s % 2 != 0) {
            cout << -1 << endl;
            continue;
        }
        
        int k = s / 2;
        int delta = p3 - (p1 + p2);
        int d = k - delta;
        
        if (delta > k || p1 + p2 < d || d < 0) {
            cout << -1 << endl;
        } else {
            cout << min(p1 + p2, d) << endl;
        }
    }
    return 0;
}
```

---

## 可视化设计要点  
### 复古像素风格  
- **颜色方案**：使用16色调色板，得分用绿色，平局用黄色，胜负用红色。  
- **动画流程**：  
  1. 显示总分并检查奇偶性（失败音效触发条件：奇数）。  
  2. 逐步展示 $p_3$ 与其他得分的比较（高亮当前条件）。  
  3. 动态计算 $d$ 的范围，用像素方块表示可行区间。  

### 音效与交互  
- **成功音效**：当条件满足时播放8-bit音效。  
- **失败音效**：总分奇数或约束不满足时播放低音。  
- **自动推导**：模拟条件检查与公式推导的步骤，以“关卡”形式逐步解锁。  

---

**核心思路总结**：通过组合约束与数学推导，确定平局次数的可行范围，结合条件验证得出最优解。

---
处理用时：537.64秒