# 题目信息

# VIDEO - Video game combos

## 题目描述

 Bessie is playing a video game! In the game, the three letters 'A', 'B', and 'C' are the only valid buttons. Bessie may press the buttons in any order she likes. However, there are only N distinct combos possible (1 <= N <= 20). Combo i is represented as a string S\_i which has a length between 1 and 15 and contains only the letters 'A', 'B', and 'C'.

 Whenever Bessie presses a combination of letters that matches with a combo, she gets one point for the combo. Combos may overlap with each other or even finish at the same time! For example if N = 3 and the three possible combos are "ABA", "CB", and "ABACB", and Bessie presses "ABACB", she will end with 3 points. Bessie may score points for a single combo more than once.

 Bessie of course wants to earn points as quickly as possible. If she presses exactly K buttons (1 <= K <= 1,000), what is the maximum number of points she can earn?

## 样例 #1

### 输入

```
3 7
ABA
CB
ABACB```

### 输出

```
4```

# AI分析结果



# 综合分析与结论

**唯一算法分类**：AC自动机 + 动态规划

---

## 题解思路与核心难点

### 核心思路
所有题解均基于 **AC自动机** 和 **动态规划**：
1. **AC自动机预处理**：将所有模式串构建为 Trie 树，并计算每个节点的 `fail` 指针。通过 `fail` 指针路径累加每个节点的得分（即该节点及其 `fail` 链上的模式串总数）。
2. **动态规划**：定义状态 `dp[i][j]` 表示按了 `i` 次按钮后处于自动机节点 `j` 时的最大得分。状态转移时，枚举下一个按钮（A/B/C），更新对应的子节点得分。

### 解决难点
- **多模式串重叠匹配**：利用 AC自动机的 `fail` 指针，在预处理阶段计算每个节点的累计得分，解决重叠匹配问题。
- **高效状态转移**：动态规划状态转移复杂度为 `O(K * 节点数 * 3)`，通过预处理节点得分避免重复计算。

---

## 题解评分与推荐（≥4星）

### 推荐题解
| 作者          | 评分 | 亮点                                                                 |
|---------------|------|----------------------------------------------------------------------|
| ez_lcw        | ⭐⭐⭐⭐⭐ | 预处理 `num` 数组逻辑清晰，状态转移简洁，代码可读性高。              |
| Engulf        | ⭐⭐⭐⭐  | 使用 `vis` 数组记录得分，初始化与转移处理严谨，注释详细。            |
| Charlie_ljk   | ⭐⭐⭐⭐  | 代码精简，利用位运算优化状态存储，适合理解核心逻辑。                 |

---

## 最优思路与技巧提炼

### 关键步骤
1. **AC自动机构建**：
   - 插入模式串至 Trie 树。
   - 计算 `fail` 指针，并通过 `fail` 链累加节点得分（`num[u] += num[fail[u]]`）。
2. **动态规划**：
   - 初始化 `dp[0][0] = 0`，其他状态为负无穷。
   - 转移方程：`dp[i+1][ch] = max(dp[i+1][ch], dp[i][u] + num[ch])`。

### 代码片段（ez_lcw 实现）
```cpp
void getfail() {
    queue<int> q;
    for (int i=0; i<3; i++) 
        if (t[0].ch[i]) q.push(t[0].ch[i]);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i=0; i<3; i++) {
            int v = t[u].ch[i];
            if (v) {
                t[v].fail = t[t[u].fail].ch[i];
                t[v].num += t[t[v].fail].num; // 关键：累加得分
                q.push(v);
            } else t[u].ch[i] = t[t[u].fail].ch[i];
        }
    }
}
```

---

## 同类型题与推荐题目

### 相似题目
1. [P3041 USACO12JAN Video Game G](https://www.luogu.com.cn/problem/P3041)  
   **双倍经验**，题意与实现完全相同。
2. [P4052 JSOI2007 文本生成器](https://www.luogu.com.cn/problem/P4052)  
   统计包含至少一个模式串的文本数，需结合容斥原理。
3. [P2292 HNOI2004 L语言](https://www.luogu.com.cn/problem/P2292)  
   AC自动机 + 动态规划，求最长可匹配前缀。

---

## 可视化与算法演示

### 动画设计
1. **AC自动机构建**：
   - **节点展开**：逐步插入模式串，展示 Trie 树生长过程。
   - **fail指针计算**：用红色箭头标记 `fail` 指针，绿色高亮当前处理的节点。
2. **动态规划过程**：
   - **状态表更新**：网格显示 `dp[i][j]`，黄色高亮当前更新的状态。
   - **转移路径追踪**：用蓝色线条标记从 `dp[i][u]` 到 `dp[i+1][v]` 的转移。

### 复古游戏化
- **像素风格**：AC自动机节点用 8-bit 像素方块表示，`fail` 指针为闪烁箭头。
- **音效设计**：
  - **节点插入**：短促“滴”声。
  - **状态更新**：得分增加时播放金币音效。
- **自动演示模式**：按空格键逐步执行构建和 DP 过程，ESC 暂停。

---

## 个人心得摘录

> **Charlie_ljk** 的调试经历：  
> 初始代码未处理节点深度，导致短于模式串的状态被错误计数。通过增加深度校验解决。

---

## 总结
本题解通过 AC自动机预处理和动态规划，高效解决了多模式串重叠匹配的最大得分问题。可视化方案结合复古游戏元素，增强理解与趣味性。

---
处理用时：71.63秒