# 题目信息

# 「Wdcfr-1」Alice Wins! (hard version)

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/zshuq5iq.png)

## 题目描述

**The difference between the versions is the limit of operations.**

Alice is a cute girl who has a lot of dolls.

There are $4\cdot n$ dolls playing *rock-paper-scissors*. They are divided into two teams: Team A and Team B. Each team contains $2\cdot n$ dolls.

A total of $2\cdot n$ rounds of the game will be played. In the $i$-th round, the $i$-th doll in Team A will play against the $i$-th doll in Team B. If the doll in Team A wins, Team A will get $1$ point. If it loses, Team A will lose $1$ point. If it ties, Team A will not get points.

Alice knows all the dolls' choices in this game. To be precise, she uses two arrays $a$ and $b$ to represent the choices of the dolls in the two teams. $a_i$ means the choice of the $i$-th doll in Team A, and $b_i$ means the choice of the $i$-th doll in Team B. In this question, we use $1$ for rock, $2$ for scissors, and $3$ for paper.

Now for **each team**, Alice wants to change the choices of **exact** $n$ dolls to make the score of Team A as high as possible.

Find the maximum score of Team A and its construction method. If there are multiple answers print any of them (you still have to maximize the score of Team A).

## 说明/提示

### Explanation

For the first test case, we can change $a_2$ to $1$ and $b_1$ to $2$. Then Team A can get $2$ points. It can be proved that this is the maximum score that Team A can get.

### Constraints

$1\le T,n \le 10^5;\ 1\le a_i,b_i \le 3$. The sum of $n$ of all test cases $\le 10^5$.

## 样例 #1

### 输入

```
1
1
1 2
1 2```

### 输出

```
2
1 1
2 2```

# AI分析结果



**算法分类**: 贪心

---

### 综合分析与结论
题目要求通过修改两队各 $n$ 个元素，使得 A 队得分最大。所有题解均基于以下核心思路：
1. **贪心构造全胜局面**：优先让每个回合 A 队胜利。
2. **操作次数分配**：通过交替修改 A/B 队，保证每队恰好修改 $n$ 次。
3. **剩余次数处理**：对已全胜的情况，通过同时修改 A/B 队或调整未修改的对局来消耗剩余次数。

最优策略的关键在于始终保持每轮 A 胜利，同时灵活分配修改次数。所有题解最终均能保证得分为 $2n$。

---

### 精选题解与评分
#### 1. [ahawzlc] ⭐⭐⭐⭐
**关键亮点**:
- 分阶段处理：先构造全胜局面，再通过两种方式消耗剩余次数。
- 代码结构清晰，通过标记数组 `v1[]` 和 `v2[]` 记录修改位置。
- 处理剩余次数时，通过循环调整确保修改后的值与原值不同。

**核心代码思想**:
```cpp
// 构造全胜局面
for (int i=1; i<=n; i++) 
    if (a[i]未胜利) 修改a[i]使其必胜，消耗A队次数；
for (int i=n+1; i<=2n; i++) 
    if (a[i]未胜利) 修改b[i]使其必胜，消耗B队次数；

// 处理剩余次数
for 每个位置 i {
    if 可同时消耗A、B次数：同时修改a[i]和b[i]；
    else if 仅需消耗A：调整a[i]且保证与原值不同；
    else if 仅需消耗B：调整b[i]且保证与原值不同；
}
```

#### 2. [tongyanmin] ⭐⭐⭐⭐
**关键亮点**:
- 使用 `vis[]` 标记已修改的对局，便于后续处理剩余次数。
- 通过暴力枚举修改方式处理特殊情况（剩1次操作）。
- 代码逻辑分层明确：构造全胜 → 消耗次数 → 处理剩余。

**核心代码片段**:
```cpp
// 处理剩余次数
for (int i=1; i<=2n; i++) {
    if (未修改且A/B次数未满) {
        同时修改a[i]和b[i]，消耗次数；
    }
}
// 处理剩1次B操作的特殊情况
if (B次数不足) {
    找到第一个已修改的位置，暴力枚举新值保证胜利；
}
```

---

### 关键思路与技巧
1. **全胜构造**：通过修改 A 或 B 的值，使得每轮 A 必胜。例如，若原对局为 (a,b)，则修改 a 为 `(b+2)%3`，或修改 b 为 `(a+1)%3`。
2. **剩余次数处理**：优先选择未修改的对局进行「无害调整」（如同时 +1），既不改变胜负，又能消耗次数。
3. **避免重复值**：在调整已修改的对局时，需确保新值与原值不同（如循环 `a[i]=(a[i]+1)%3`）。

---

### 拓展与举一反三
同类问题可参考以下洛谷题目：
1. [P1007 独木桥](https://www.luogu.com.cn/problem/P1007) - 贪心策略模拟。
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心与优先队列结合。
3. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080) - 贪心排序与高精度处理。

---

### 个人心得摘录
- **ahawzlc**：在处理剩余次数时，发现必须确保修改后的值与原值不同，否则可能导致无效操作。
- **zzy0618**：调试中发现，暴力枚举修改值时需同时满足胜利条件和新值不重复，否则可能陷入死循环。

---
处理用时：59.86秒