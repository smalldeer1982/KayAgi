# 题目信息

# Alice and Bob

## 题目描述

It is so boring in the summer holiday, isn't it? So Alice and Bob have invented a new game to play. The rules are as follows. First, they get a set of $ n $ distinct integers. And then they take turns to make the following moves. During each move, either Alice or Bob (the player whose turn is the current) can choose two distinct integers $ x $ and $ y $ from the set, such that the set doesn't contain their absolute difference $ |x-y| $ . Then this player adds integer $ |x-y| $ to the set (so, the size of the set increases by one).

If the current player has no valid move, he (or she) loses the game. The question is who will finally win the game if both players play optimally. Remember that Alice always moves first.

## 说明/提示

Consider the first test sample. Alice moves first, and the only move she can do is to choose 2 and 3, then to add 1 to the set. Next Bob moves, there is no valid move anymore, so the winner is Alice.

## 样例 #1

### 输入

```
2
2 3
```

### 输出

```
Alice
```

## 样例 #2

### 输入

```
2
5 3
```

### 输出

```
Alice
```

## 样例 #3

### 输入

```
3
5 6 7
```

### 输出

```
Bob
```

# AI分析结果



# Alice and Bob

## 题目描述

暑假太无聊了，不是吗？于是 Alice 和 Bob 发明了一个新游戏。规则如下：首先，他们获得一个包含 $n$ 个不同整数的集合。然后他们轮流进行如下操作：当前回合的玩家（Alice 或 Bob）从集合中选择两个不同的整数 $x$ 和 $y$，要求集合中不包含它们的绝对差 $|x-y|$。然后将这个绝对差添加到集合中（集合大小增加一）。

如果当前玩家没有合法操作，则输掉游戏。问题是在双方都采取最优策略的情况下，谁会赢得比赛？注意 Alice 总是先手。

## 说明/提示

考虑第一个测试样例。Alice 先手，她唯一能做的操作是选择 2 和 3，然后将 1 添加到集合中。接下来 Bob 没有合法操作，因此 Alice 获胜。

## 样例 #1

### 输入

```
2
2 3
```

### 输出

```
Alice
```

## 样例 #2

### 输入

```
2
5 3
```

### 输出

```
Alice
```

## 样例 #3

### 输入

```
3
5 6 7
```

### 输出

```
Bob
```

---

**算法分类**：数学（博弈论与数论结合）

---

## 题解综合分析

所有题解均基于以下核心结论：
1. 最终集合形如公差为 $d$ 的等差数列 $[d,2d,...,m]$，其中 $d$ 是原集合的 GCD，$m$ 是原集合最大值
2. 总操作次数为 $\frac{m}{d} - n$，奇数次 Alice 胜，偶数次 Bob 胜

关键验证步骤：
- 通过辗转相除法证明最终集合必为等差数列
- 最大公约数的计算决定等差数列的公差
- 最大值的计算决定等差数列的末项

---

## 优质题解推荐

### 题解1：liuyi0905（⭐⭐⭐⭐⭐）
**核心亮点**：
- 直击本质的数学推导，仅需 7 行代码
- 使用 STL 的 `__gcd` 简化实现
```cpp
puts((m/d-n)%2?"Alice":"Bob");
```

### 题解2：b6e0_（⭐⭐⭐⭐⭐）
**核心亮点**：
- 包含完整的数学证明链条
- 手写 GCD 实现更易理解
```cpp
int gcd(int x,int y){
    if(!y) return x;
    return gcd(y,x%y);
}
```

### 题解3：离散小波变换°（⭐⭐⭐⭐）
**核心亮点**：
- 明确指出"与策略无关"的博弈本质
- 使用更规范的代码风格
```cpp
up(1, n, i){
    int a = qread(); 
    m = max(m, a);
    d = __gcd(a, d);
}
```

---

## 关键思路总结
1. **数学建模**：将操作过程转化为等差数列生成问题
2. **GCD 计算**：使用辗转相除法确定等差数列公差
3. **奇偶判定**：通过简单模运算决定胜负，复杂度 O(n)
4. **库函数利用**：`__gcd` 和 `max` 的内置函数优化代码

---

## 拓展与同类题目
**类似套路题**：
1. [P1290 欧几里德的游戏](https://www.luogu.com.cn/problem/P1290)（辗转相除博弈）
2. [P2734 游戏](https://www.luogu.com.cn/problem/P2734)（数学分析博弈）
3. [CF276D Little Girl and Maximum XOR](https://www.luogu.com.cn/problem/CF276D)（位运算与数学结合）

**调试心得**：
- dyc2022 提到手写 GCD 时注意不要使用 `gcd` 作为函数名（可能冲突）
- huangmingyi 提醒注意 __gcd 的双下划线写法

---
处理用时：49.40秒