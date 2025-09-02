# 题目信息

# Sasha and the Casino

## 题目描述

Sasha decided to give his girlfriend the best handbag, but unfortunately for Sasha, it is very expensive. Therefore, Sasha wants to earn it. After looking at earning tips on the internet, he decided to go to the casino.

Sasha knows that the casino operates under the following rules. If Sasha places a bet of $ y $ coins (where $ y $ is a positive integer), then in case of winning, he will receive $ y \cdot k $ coins (i.e., his number of coins will increase by $ y \cdot (k - 1) $ ). And in case of losing, he will lose the entire bet amount (i.e., his number of coins will decrease by $ y $ ).

Note that the bet amount must always be a positive ( $ > 0 $ ) integer and cannot exceed Sasha's current number of coins.

Sasha also knows that there is a promotion at the casino: he cannot lose more than $ x $ times in a row.

Initially, Sasha has $ a $ coins. He wonders whether he can place bets such that he is guaranteed to win any number of coins. In other words, is it true that for any integer $ n $ , Sasha can make bets so that for any outcome that does not contradict the rules described above, at some moment of time he will have at least $ n $ coins.

## 说明/提示

In the first test case, Sasha can proceed as follows:

- If Sasha places a bet for the first time or if he won the previous bet, then he places $ 1 $ coin.
- If Sasha lost the previous bet, then he places $ 2 $ coins.

Note that Sasha cannot lose more than once in a row.

It can be proven that with this strategy, Sasha can obtain as many coins as he wants.

In the second test case, Sasha can only place $ 1 $ coin for the first time. But in case of a loss, he will not be able to place any more bets, so he will not be able to guarantee having as many coins as he wants.

## 样例 #1

### 输入

```
9
2 1 7
2 1 1
2 3 15
3 3 6
4 4 5
5 4 7
4 88 1000000000
25 69 231
13 97 18806```

### 输出

```
YES
NO
YES
NO
NO
YES
NO
NO
NO```

# AI分析结果



### 中文题目重写

# 萨沙与赌场

## 题目描述

萨沙决定给女友买最贵的手提包，但价格高昂。为此他决定去赌场赚钱。赌场规则如下：

- 若下注 $y$ 枚硬币（正整数），获胜可得 $y \cdot k$ 枚（净赚 $y\cdot(k-1)$）
- 若失败则损失全部下注金额
- 下注金额不能超过当前持有量

赌场的促销规则：不能连续输超过 $x$ 次。

初始萨沙有 $a$ 枚硬币。请判断是否存在一种下注策略，使得无论赌场结果如何（只要不违反促销规则），萨沙都能保证硬币数量可以无限增长（即对于任意大的 $n$，总能通过若干次下注达到至少 $n$ 枚）。

### 输入输出样例（详见原题）

---

**算法分类**：贪心

---

### 题解综合分析

所有题解均基于**倍投法**的变种，核心思想是：在最坏连续输 $x$ 次的情况下，第 $x+1$ 次的下注金额必须能覆盖前 $x$ 次的累计损失。通过递推计算每轮最小下注金额，确保总成本不超过初始资金。

#### 关键思路
1. **递推公式**：设前 $i-1$ 轮总损失为 $sum$，则第 $i$ 轮至少下注 $\lfloor \frac{sum}{k-1} \rfloor + 1$ 以满足 $y_i \cdot (k-1) > sum$
2. **终止条件**：若前 $x+1$ 轮总成本超过 $a$ 则无解
3. **数学本质**：通过构造几何级数的下注序列，确保任意次失败后的胜利能回本

---

### 精选题解（评分≥4⭐）

#### 1. 作者：_Ink（⭐⭐⭐⭐⭐）
**亮点**：代码简洁高效，直接递推计算总成本，无需额外存储
```cpp
void solve() {
    int k, x, a; 
    cin >> k >> x >> a;
    ll sum = 0;
    for(int i = 1; i <= x + 1; i++) {
        sum += sum / (k - 1) + 1; // 核心递推式
        if(sum > a) { cout << "NO\n"; return; }
    }
    cout << "YES\n";
}
```

#### 2. 作者：CaoXian（⭐⭐⭐⭐）
**亮点**：详细推导不等式条件，代码包含前缀和优化
```cpp
for(int i = 1; i <= x; ++i) {
    sum += c[i];
    c[i + 1] = sum / (k - 1) + 1; // 显式存储每轮下注
    if(sum > a) break;
}
```

#### 3. 作者：No_Rest（⭐⭐⭐⭐）
**心得**：强调题目中"至少n个硬币"的误解点，提醒注意题意
```cpp
for(ll i = 1; i <= x + 1; ++i) {
    b[i] = floor(1.0 * sum / (k - 1)) + 1;
    sum += b[i];
    if(sum > a) { No; return; } // 实时检测溢出
}
```

---

### 关键技巧
1. **防溢出处理**：使用`long long`避免中间值溢出
2. **终止优化**：在递推过程中实时检查总成本，提前终止无效计算
3. **数学建模**：将赌博问题转化为序列构造问题，通过不等式约束保证回本

---

### 拓展练习
1. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031) - 贪心策略的应用
2. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002) - 递推与路径计数
3. [P7078 毒瘤题](https://www.luogu.com.cn/problem/P7078) - 最坏情况分析

---

### 调试心得
- **开long long**：多位作者提到未开`long long`导致WA
- **边界条件**：注意当 $k=2$ 时除法可能产生整数舍入误差
- **题意理解**：必须保证"任何符合规则的赌场操作"下的必胜性，而非存在性判断

---
处理用时：59.99秒