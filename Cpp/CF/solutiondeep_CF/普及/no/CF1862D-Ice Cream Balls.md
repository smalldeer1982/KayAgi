# 题目信息

# Ice Cream Balls

## 题目描述

Tema decided to improve his ice cream making skills. He has already learned how to make ice cream in a cone using exactly two balls.

Before his ice cream obsession, Tema was interested in mathematics. Therefore, he is curious about the minimum number of balls he needs to have in order to make exactly $ n $ different types of ice cream.

There are plenty possible ice cream flavours: $ 1, 2, 3, \dots $ . Tema can make two-balls ice cream with any flavours (probably the same).

Two ice creams are considered different if their sets of ball flavours are different. For example, $ \{1, 2\} = \{2, 1\} $ , but $ \{1, 1\} \neq \{1, 2\} $ .

For example, having the following ice cream balls: $ \{1, 1, 2\} $ , Tema can make only two types of ice cream: $ \{1, 1\} $ and $ \{1, 2\} $ .

Note, that Tema do not need to make all the ice cream cones at the same time. This means that he making ice cream cones independently. Also in order to make a following cone $ \{x, x\} $ for some $ x $ , Tema needs at least $ 2 $ balls of type $ x $ .

Help Tema answer this question. It can be shown that answer always exist.

## 说明/提示

In the first sample, it is enough to have following balls types: $ \{1, 1\} $ . Note, that set $ \{1\} $ if not enough since we need at least $ 2 $ balls of a type $ 1 $ in order to make such cone $ \{1, 1\} $ .

In the second sample, it is not possible to make it with $ 2 $ balls, but it can be done with these balls: $ \{1, 2, 3\} $ .

In the third sample, $ \{1, 2, 3, 4\} $ is optimal answer, so we can get following ice cream cones: $ \{1, 2\} $ , $ \{1, 3\} $ , $ \{1, 4\} $ , $ \{2, 3\} $ , $ \{2, 4\} $ , $ \{3, 4\} $ .

## 样例 #1

### 输入

```
5
1
3
6
179
1000000000000000000```

### 输出

```
2
3
4
27
2648956421```

# AI分析结果

### 题目内容重写
# 冰激凌球

## 题目描述

Tema 决定提高他制作冰激凌的技能。他已经学会了如何用两个球制作一个冰激凌甜筒。

在他对冰激凌着迷之前，Tema 对数学很感兴趣。因此，他很好奇，为了制作恰好 $n$ 种不同的冰激凌，他至少需要多少个冰激凌球。

冰激凌的口味有很多种：$1, 2, 3, \dots$。Tema 可以用任何口味的两个球制作冰激凌（可能相同）。

如果两个冰激凌的球的口味集合不同，则认为它们是不同的。例如，$\{1, 2\} = \{2, 1\}$，但 $\{1, 1\} \neq \{1, 2\}$。

例如，如果有以下冰激凌球：$\{1, 1, 2\}$，Tema 只能制作两种冰激凌：$\{1, 1\}$ 和 $\{1, 2\}$。

注意，Tema 不需要同时制作所有的冰激凌甜筒。这意味着他可以独立地制作冰激凌甜筒。此外，为了制作一个 $\{x, x\}$ 的甜筒，Tema 至少需要 $2$ 个 $x$ 类型的球。

帮助 Tema 回答这个问题。可以证明答案总是存在的。

## 说明/提示

在第一个样例中，只需要有以下类型的球：$\{1, 1\}$。注意，集合 $\{1\}$ 是不够的，因为我们需要至少 $2$ 个 $1$ 类型的球才能制作 $\{1, 1\}$ 的甜筒。

在第二个样例中，用 $2$ 个球无法完成，但可以用以下球完成：$\{1, 2, 3\}$。

在第三个样例中，$\{1, 2, 3, 4\}$ 是最优答案，因此我们可以得到以下冰激凌甜筒：$\{1, 2\}$，$\{1, 3\}$，$\{1, 4\}$，$\{2, 3\}$，$\{2, 4\}$，$\{3, 4\}$。

## 样例 #1

### 输入

```
5
1
3
6
179
1000000000000000000```

### 输出

```
2
3
4
27
2648956421```

### 算法分类
数学

### 题解分析与结论
本题的核心是通过数学推导和二分查找来确定最少需要的冰激凌球数量。大多数题解都采用了以下思路：
1. 首先通过二分查找找到最大的 $k$，使得 $\frac{k(k-1)}{2} \leq n$，即用 $k$ 个不同的球可以构成 $\frac{k(k-1)}{2}$ 种不同的冰激凌。
2. 然后通过添加重复的球来补全剩余的 $n - \frac{k(k-1)}{2}$ 种冰激凌，每添加一个重复的球可以增加一种新的冰激凌。

### 精选题解
1. **作者：sunkuangzheng (赞：9)**
   - **星级：5**
   - **关键亮点：** 通过一元二次方程求解 $k$，简洁高效。
   - **核心代码：**
     ```cpp
     k=(1+sqrt(8*n+1))/2,x = k*(k-1)/2;
     cout <<k + n - x<<"\n";
     ```

2. **作者：Shadow_T (赞：5)**
   - **星级：4**
   - **关键亮点：** 使用二分查找确定 $k$，并处理大数问题。
   - **核心代码：**
     ```cpp
     mid=(l+r+1)/2;
     if(mid*(mid-1)/2>n) r=mid-1;
     else l=mid;
     ```

3. **作者：ax_by_c (赞：4)**
   - **星级：4**
   - **关键亮点：** 详细解释了二分查找的思路，并给出了清晰的实现。
   - **核心代码：**
     ```cpp
     int mid=l+((r-l)>>1);
     if((mid*(mid-1)/2)<=n) l=mid+1;
     else r=mid-1;
     ```

### 最优关键思路
通过二分查找确定最大的 $k$，使得 $\frac{k(k-1)}{2} \leq n$，然后通过添加重复的球来补全剩余的 $n - \frac{k(k-1)}{2}$ 种冰激凌。

### 拓展思路
类似的问题可以出现在组合数学中，尤其是在需要计算组合数或排列数的情况下。可以通过二分查找或数学公式来优化计算。

### 推荐题目
1. [P1495 组合数问题](https://www.luogu.com.cn/problem/P1495)
2. [P1102 排列组合](https://www.luogu.com.cn/problem/P1102)
3. [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)

### 个人心得
在处理大数问题时，使用 `__int128` 可以有效避免溢出问题。同时，二分查找的边界条件需要仔细处理，确保不会遗漏可能的解。

---
处理用时：30.48秒