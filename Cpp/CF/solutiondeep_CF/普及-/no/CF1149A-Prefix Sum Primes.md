# 题目信息

# Prefix Sum Primes

## 题目描述

We're giving away nice huge bags containing number tiles! A bag we want to present to you contains $ n $ tiles. Each of them has a single number written on it — either $ 1 $ or $ 2 $ .

However, there is one condition you must fulfill in order to receive the prize. You will need to put all the tiles from the bag in a sequence, in any order you wish. We will then compute the sums of all prefixes in the sequence, and then count how many of these sums are prime numbers. If you want to keep the prize, you will need to maximize the number of primes you get.

Can you win the prize? Hurry up, the bags are waiting!

## 说明/提示

The first solution produces the prefix sums $ 1, \mathbf{\color{blue}{2}}, \mathbf{\color{blue}{3}}, \mathbf{\color{blue}{5}}, \mathbf{\color{blue}{7}} $ (four primes constructed), while the prefix sums in the second solution are $ 1, \mathbf{\color{blue}{2}}, \mathbf{\color{blue}{3}}, \mathbf{\color{blue}{5}}, 6, \mathbf{\color{blue}{7}}, 8, 10, \mathbf{\color{blue}{11}} $ (five primes). Primes are marked bold and blue. In each of these cases, the number of produced primes is maximum possible.

## 样例 #1

### 输入

```
5
1 2 1 2 1
```

### 输出

```
1 1 1 2 2
```

## 样例 #2

### 输入

```
9
1 1 2 1 1 1 2 1 1
```

### 输出

```
1 1 1 2 1 1 1 2 1
```

# AI分析结果



# 重写中文题目

## 题目描述

我们正在赠送装有数字瓷砖的漂亮大袋子！你要获得的袋子包含 $n$ 块瓷砖，每块瓷砖上写有数字 $1$ 或 $2$。

要获得奖品，必须将所有瓷砖排成一个序列（顺序任意）。我们将计算所有前缀和，并统计其中素数的数量。你需要最大化这个素数数量。

## 样例 #1

### 输入
```
5
1 2 1 2 1
```

### 输出
```
1 1 1 2 2
```

## 样例 #2

### 输入
```
9
1 1 2 1 1 1 2 1 1
```

### 输出
```
1 1 1 2 1 1 1 2 1
```

---

**算法分类**: 构造、贪心、数学（质数）

---

### 综合分析与结论

题目核心在于通过构造排列顺序，使得前缀和中尽可能多出现素数。所有题解均基于以下观察：
1. 素数（除2）都是奇数
2. 奇+偶=奇，奇+奇=偶
3. 最优策略是优先构造奇数前缀和，并尽可能延长奇数的连续生成

最优策略为：
1. 若存在至少1个1和1个2，先构造2→1（得到前缀和2,3两个素数）
2. 输出剩余所有2（保持前缀和为奇数，可能生成更多素数）
3. 最后输出剩余1（此时前缀和连续递增，可能包含更多素数）

---

### 高星题解推荐

#### 1. 作者：Rainbow_qwq（★★★★★）
**关键亮点**：
- 全面处理边界情况（总和<3、全为2等情况）
- 使用桶计数结构清晰
- 详细注释解释素数分布特性

**代码核心**：
```cpp
if(c[1]+c[2]*2<3) { // 总和不足3的特殊处理
    while(c[1])P(1);
    while(c[2])P(2);
    return 0;
}
if(c[2]) P(2), P(1); // 构造2→1
else P(1), P(1), P(1); // 全为1的特殊处理
while(c[2]) P(2); // 优先输出剩余2
while(c[1]) P(1); // 最后输出剩余1
```

#### 2. 作者：Biuld（★★★★☆）
**关键亮点**：
- 代码逻辑简洁直观
- 明确分阶段输出策略
- 变量命名清晰易读

**核心代码**：
```cpp
cout << 2 << ' ' << 1 << ' '; // 构造初始素数
for(int i=1;i<=b;i++) cout<<2<<' '; // 输出剩余2
for(int i=1;i<=a;i++) cout<<1<<' '; // 输出剩余1
```

---

### 最优技巧总结

1. **素数奇偶性利用**：构造奇前缀和序列以最大化素数出现概率
2. **阶段式构造**：先制造关键素数点（2,3），再填充2维持奇性，最后用1填充
3. **边界处理**：总和较小或单一元素时的特殊处理

---

### 类似题目推荐

1. [P1217 USACO1.5 回文质数](https://www.luogu.com.cn/problem/P1217) - 质数性质与构造
2. [P1304 哥德巴赫猜想](https://www.luogu.com.cn/problem/P1304) - 质数拆分与构造
3. [P2563 质数和分解](https://www.luogu.com.cn/problem/P2563) - 质数的动态规划应用

---

### 题解心得摘录

- **Rainbow_qwq**：调试时发现总和小于3的情况需要单独处理，否则会导致错误构造顺序
- **Loser_King**：虽然代码逻辑看似不通过样例，但利用SPJ特性仍能AC，提示测试数据可能存在设计特点

---
处理用时：50.08秒