# 题目信息

# Vladik and flights

## 题目描述

Vladik is a competitive programmer. This year he is going to win the International Olympiad in Informatics. But it is not as easy as it sounds: the question Vladik face now is to find the cheapest way to get to the olympiad.

Vladik knows $ n $ airports. All the airports are located on a straight line. Each airport has unique id from $ 1 $ to $ n $ , Vladik's house is situated next to the airport with id $ a $ , and the place of the olympiad is situated next to the airport with id $ b $ . It is possible that Vladik's house and the place of the olympiad are located near the same airport.

To get to the olympiad, Vladik can fly between any pair of airports any number of times, but he has to start his route at the airport $ a $ and finish it at the airport $ b $ .

Each airport belongs to one of two companies. The cost of flight from the airport $ i $ to the airport $ j $ is zero if both airports belong to the same company, and $ |i-j| $ if they belong to different companies.

Print the minimum cost Vladik has to pay to get to the olympiad.

## 说明/提示

In the first example Vladik can fly to the airport $ 2 $ at first and pay $ |1-2|=1 $ (because the airports belong to different companies), and then fly from the airport $ 2 $ to the airport $ 4 $ for free (because the airports belong to the same company). So the cost of the whole flight is equal to $ 1 $ . It's impossible to get to the olympiad for free, so the answer is equal to $ 1 $ .

In the second example Vladik can fly directly from the airport $ 5 $ to the airport $ 2 $ , because they belong to the same company.

## 样例 #1

### 输入

```
4 1 4
1010
```

### 输出

```
1```

## 样例 #2

### 输入

```
5 5 2
10110
```

### 输出

```
0```

# AI分析结果



# Vladik and flights

## 题目描述

Vladik 是一名竞赛选手。他计划赢得国际信息学奥林匹克竞赛。现在他面临的问题是找到前往比赛地点的最便宜路线。

已知有 $n$ 个机场排成一条直线，每个机场有唯一的编号（1 到 $n$）。Vladik 的家在编号为 $a$ 的机场旁，比赛地点在编号为 $b$ 的机场旁。每个机场属于两家航空公司中的一家。从机场 $i$ 到 $j$ 的飞行费用为 $0$（若同属一个公司）或 $|i-j|$（若属于不同公司）。求从 $a$ 到 $b$ 的最小费用。

## 样例说明

- 样例 1：通过相邻不同公司的机场中转，总费用为 1。
- 样例 2：直接到达同公司机场，费用为 0。

---

**算法分类**：构造

---

### 综合结论
所有题解的核心思路均为**直接比较起点与终点机场的公司归属**：
- 若公司相同，费用为 0
- 若不同，费用必为 1

**关键证明**：当两机场公司不同时，必存在相邻的不同公司机场，通过构造路径（如 $a \to 同公司机场 \to 相邻异公司机场 \to b$），总费用为 1。

---

### 精选题解

#### 1. piggymichael（5星）
**亮点**：代码极简，直接判断字符  
**核心代码**：
```cpp
if(a[y-1]==a[z-1]) cout<<0; // 比较起点与终点的字符
else cout<<1;
```

#### 2. wxwoo（5星）
**亮点**：详细数学证明，输入处理规范  
**证明思路**：存在相邻异公司机场，构造三次飞行路径总费用为 1。

#### 3. 铃宕（4星）
**亮点**：分类讨论，快读优化  
**代码片段**：
```cpp
if(f[a]==f[b]) putchar('0'); 
else putchar('1');
```

---

### 关键技巧
1. **索引转换**：将题目中的 1-based 编号转换为 0-based 字符串索引。
2. **输入优化**：直接读取关键位置字符，避免存储整个数组（如 JS_TZ_ZHR 的解法）。
3. **思维突破**：将看似复杂的最短路问题转化为简单的字符比较。

---

### 拓展训练
类似问题需观察隐藏规律：
1. **CF734B**（贪心构造）
2. **P1031**（均分纸牌，贪心策略）
3. **P1008**（三连击，数字构造）

---

### 个人心得摘录
- "本题的思维难点在于跳出传统最短路框架，发现费用仅与起点终点相关"（wxwoo）
- "大胆尝试直接比较字符，发现数据水反而成就最优解"（piggymichael）
- "快读并非必要，但养成优化习惯很重要"（铃宕）

---
处理用时：83.41秒