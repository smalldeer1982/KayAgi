# 题目信息

# Deleting Divisors

## 题目描述

Alice and Bob are playing a game.

They start with a positive integer $ n $ and take alternating turns doing operations on it. Each turn a player can subtract from $ n $ one of its divisors that isn't $ 1 $ or $ n $ . The player who cannot make a move on his/her turn loses. Alice always moves first.

Note that they subtract a divisor of the current number in each turn.

You are asked to find out who will win the game if both players play optimally.

## 说明/提示

In the first test case, the game ends immediately because Alice cannot make a move.

In the second test case, Alice can subtract $ 2 $ making $ n = 2 $ , then Bob cannot make a move so Alice wins.

In the third test case, Alice can subtract $ 3 $ so that $ n = 9 $ . Bob's only move is to subtract $ 3 $ and make $ n = 6 $ . Now, Alice can subtract $ 3 $ again and $ n = 3 $ . Then Bob cannot make a move, so Alice wins.

## 样例 #1

### 输入

```
4
1
4
12
69```

### 输出

```
Bob
Alice
Alice
Bob```

# AI分析结果



### 题目重写

# 删除除数

## 题目描述

Alice 和 Bob 正在玩一个游戏。

他们从一个正整数 $n$ 开始，轮流进行操作。每次操作时，玩家需要从当前数字中减去一个既不是 $1$ 也不是它本身的除数。无法进行合法操作的玩家输掉游戏，Alice 总是先手。

注意：每次操作中减去的除数必须是当前数字的除数。

你需要判断当双方都采用最优策略时谁会获胜。

## 说明/提示

样例 1 中，Alice 无法操作直接输掉。

样例 2 中，Alice 减去 2 得到 2，此时 Bob 无法操作。

样例 3 中，Alice 通过三次减 3 的操作获胜。

---

### 题解综合分析

#### 核心结论：
1. **奇数必败**：当 $n$ 是奇数时，所有除数都是奇数，操作后必得偶数，将必胜态转移给对手
2. **非2幂偶数必胜**：当 $n$ 是偶数且存在奇数除数时，可以一步转为奇数必败态
3. **2的幂次特例**：当 $n=2^k$ 时，胜负由指数奇偶性决定，奇数次幂必败，偶数次幂必胜

#### 算法验证：
- 判断是否为 2 的幂次：通过不断除以 2 直到无法整除，若最后商为 1 则是幂次
- 特判 $n=1$ 和质数情况

---

### 精选题解（评分≥4⭐）

#### 1. Little09（5⭐）
**关键亮点**：
- 将问题分为三类情况，逻辑链条严密
- 数学证明清晰，提出核心定理：
  - 奇数只能转为偶数（必败→必胜态转移）
  - 非2幂偶数必能转为奇数（必胜）
  - 2的幂次形成独立博弈链

**代码核心**：
```cpp
while (p < x) p *= 4; // 快速定位到最近的4的幂
if (p == x || x%2 == 1) cout << "Bob\n"; // 2的奇次幂或奇数
else cout << "Alice\n";
```

#### 2. pomelo_nene（4⭐）
**关键亮点**：
- 通过质因数分解分析除数奇偶性
- 代码清晰处理所有边界条件
- 提出「除以2博弈链」模型

**代码核心**：
```cpp
int tmp = n, cnt = 0;
while (tmp % 2 == 0) {
    tmp /= 2;
    cnt++; // 统计2的幂次
}
if (tmp == 1 && cnt%2 == 0) puts("Alice");
else if (tmp != 1) puts("Alice");
else puts("Bob");
```

#### 3. Exiler（4⭐）
**关键亮点**：
- 使用位运算快速判断2的幂次
- 引入对数计算优化判断过程
- 代码简洁高效，适合大数范围

**代码核心**：
```cpp
int clc = log2(n*1.0); // 计算对数
if (1<<clc == n && clc&1) puts("Bob"); // 位运算验证
```

---

### 最优思路总结

**核心判断流程**：
1. 若 $n$ 为奇数 → Bob 胜
2. 若 $n$ 存在奇数除数：
   - 可一步转为奇数必败态 → Alice 胜
3. 若 $n$ 是纯2的幂次：
   - 指数为奇数 → Bob 胜（操作链长度为奇数次）
   - 指数为偶数 → Alice 胜

**实现技巧**：
- 位运算判断：`n & (n-1) == 0` 可快速判断2的幂次
- 对数运算：`log2(n)` 配合取整验证幂次
- 快速幂检测：通过不断乘以4逼近目标值（Little09解法）

---

### 拓展与心得

**类似题型套路**：
1. 奇偶性转换博弈（CF1537D）
2. 幂次结构博弈（洛谷 P2949）
3. 除数操作博弈（AtCoder ARC137B）

**推荐练习**：
1. 洛谷 P1290 - 欧几里得的游戏（除数博弈变体）
2. 洛谷 P1247 - 取火柴游戏（Nim博弈基础）
3. 洛谷 P2197 - Nim游戏（经典博弈模板）

**作者心得摘录**：
> "打表找规律是解决博弈论题目的有效手段，尤其是在比赛时间有限的情况下" —— Aestas16  
> "发现2的奇次幂特例后，意识到博弈链长度决定胜负" —— YuanZihan1225  
> "将问题分解为三种情况后，代码结构突然变得清晰" —— Little09

---
处理用时：63.99秒