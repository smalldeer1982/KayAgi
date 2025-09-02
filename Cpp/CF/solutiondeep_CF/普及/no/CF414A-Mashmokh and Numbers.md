# 题目信息

# Mashmokh and Numbers

## 题目描述

It's holiday. Mashmokh and his boss, Bimokh, are playing a game invented by Mashmokh.

In this game Mashmokh writes sequence of $ n $ distinct integers on the board. Then Bimokh makes several (possibly zero) moves. On the first move he removes the first and the second integer from from the board, on the second move he removes the first and the second integer of the remaining sequence from the board, and so on. Bimokh stops when the board contains less than two numbers. When Bimokh removes numbers $ x $ and $ y $ from the board, he gets $ gcd(x,y) $ points. At the beginning of the game Bimokh has zero points.

Mashmokh wants to win in the game. For this reason he wants his boss to get exactly $ k $ points in total. But the guy doesn't know how choose the initial sequence in the right way.

Please, help him. Find $ n $ distinct integers $ a_{1},a_{2},...,a_{n} $ such that his boss will score exactly $ k $ points. Also Mashmokh can't memorize too huge numbers. Therefore each of these integers must be at most $ 10^{9} $ .

## 说明/提示

 $ gcd(x,y) $ is greatest common divisor of $ x $ and $ y $ .

## 样例 #1

### 输入

```
5 2
```

### 输出

```
1 2 3 4 5
```

## 样例 #2

### 输入

```
5 3```

### 输出

```
2 4 3 7 1```

## 样例 #3

### 输入

```
7 2
```

### 输出

```
-1
```

# AI分析结果



# Mashmokh 和数字

## 题目描述

Mashmokh 和他的老板 Bimokh 在玩一个游戏。Mashmokh 需要在黑板上写出一个包含 $n$ 个不同整数的序列。Bimokh 会进行若干次操作：第一次操作移除序列前两个数并计算它们的 $gcd$，第二次操作移除剩余序列的前两个数，依此类推。当剩余数字不足两个时停止。要求构造一个序列使得所有操作的 $gcd$ 之和等于 $k$，且所有数字不超过 $10^9$。

## 算法分类
构造

---

## 题解分析与结论

### 核心思路
构造首项数对的 $gcd$ 为 $k - (n/2 -1)$，后续数对使用连续自然数保证 $gcd=1$。当 $n$ 为奇数时补充独立大数。

### 最优题解

#### RE_Prince 的题解（4星）
**关键亮点**：
1. 首项数对设计为 $(a, 2a)$ 保证 $gcd=a$
2. 后续数对采用连续奇偶数避免重复
3. 使用大数填充奇数情况避免冲突

**核心代码**：
```cpp
int first = 1 + m - n/2;
cout << first << " " << first*2 << " ";
for(int i=2; i<=n/2; i++) {
    while(st与已用数冲突) st++;
    cout << st << " " << st+1 << " "; // 互质数对
    st += 2;
}
if(n%2) cout << 114514; // 补充独立数
```

#### 流绪 的题解（4星）
**关键亮点**：
1. 首项直接计算为 $k - n/2 +1$
2. 后续数对采用 $a*2 + i$ 的形式保证互质
3. 奇数情况补1的特殊处理

**个人心得**：
> "样例一直接输出连续数的思路启发了我，当k刚好等于操作次数时，所有gcd都为1即可"

---

## 关键技巧总结
1. **首项构造法**：通过首项数对承载主要分数贡献，后续数对维持最小分数
2. **连续数互质**：利用相邻自然数互质的性质快速构造低分数段
3. **冲突避免**：通过递增起始值或使用大数避免数值重复
4. **奇偶处理**：单独处理奇数情况的最后一个元素

---

## 相似题目推荐
1. [CF359B - Permutation](https://codeforces.com/problemset/problem/359/B)（构造特定差值的排列）
2. [P7914 [CSP-S 2021] 括号序列](https://www.luogu.com.cn/problem/P7914)（特殊构造类问题） 
3. [CF1325C - Ehab and Path-etic MEXs](https://codeforces.com/problemset/problem/1325/C)（树边权构造）

---
处理用时：58.42秒