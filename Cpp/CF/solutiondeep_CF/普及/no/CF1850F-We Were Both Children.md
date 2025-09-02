# 题目信息

# We Were Both Children

## 题目描述

Mihai and Slavic were looking at a group of $ n $ frogs, numbered from $ 1 $ to $ n $ , all initially located at point $ 0 $ . Frog $ i $ has a hop length of $ a_i $ .

Each second, frog $ i $ hops $ a_i $ units forward. Before any frogs start hopping, Slavic and Mihai can place exactly one trap in a coordinate in order to catch all frogs that will ever pass through the corresponding coordinate.

However, the children can't go far away from their home so they can only place a trap in the first $ n $ points (that is, in a point with a coordinate between $ 1 $ and $ n $ ) and the children can't place a trap in point $ 0 $ since they are scared of frogs.

Can you help Slavic and Mihai find out what is the maximum number of frogs they can catch using a trap?

## 说明/提示

In the first test case, the frogs will hop as follows:

- Frog 1: $ 0 \to 1 \to 2 \to 3 \to \mathbf{\color{red}{4}} \to \cdots $
- Frog 2: $ 0 \to 2 \to \mathbf{\color{red}{4}} \to 6 \to 8 \to \cdots $
- Frog 3: $ 0 \to 3 \to 6 \to 9 \to 12 \to \cdots $
- Frog 4: $ 0 \to \mathbf{\color{red}{4}} \to 8 \to 12 \to 16 \to \cdots $
- Frog 5: $ 0 \to 5 \to 10 \to 15 \to 20 \to \cdots $

 Therefore, if Slavic and Mihai put a trap at coordinate $ 4 $ , they can catch three frogs: frogs 1, 2, and 4. It can be proven that they can't catch any more frogs.In the second test case, Slavic and Mihai can put a trap at coordinate $ 2 $ and catch all three frogs instantly.

## 样例 #1

### 输入

```
7
5
1 2 3 4 5
3
2 2 2
6
3 1 3 4 9 10
9
1 3 2 4 2 3 7 8 5
1
10
8
7 11 6 8 12 4 4 8
10
9 11 9 12 1 7 2 5 8 10```

### 输出

```
3
3
3
5
0
4
4```

# AI分析结果

### 题目内容重写

**题目描述**

Mihai和Slavic正在观察一组编号为$1$到$n$的$n$只青蛙，它们最初都位于坐标$0$处。青蛙$i$的跳跃长度为$a_i$。

每秒钟，青蛙$i$会向前跳跃$a_i$个单位。在青蛙开始跳跃之前，Slavic和Mihai可以在一个坐标上放置一个陷阱，以捕捉所有经过该坐标的青蛙。

然而，孩子们不能离家太远，所以他们只能在前$n$个点（即坐标在$1$到$n$之间的点）放置陷阱，而且他们不能在$0$点放置陷阱，因为他们害怕青蛙。

你能帮助Slavic和Mihai找出使用陷阱最多能捕捉多少只青蛙吗？

**说明/提示**

在第一个测试用例中，青蛙的跳跃过程如下：

- 青蛙1：$0 \to 1 \to 2 \to 3 \to \mathbf{\color{red}{4}} \to \cdots $
- 青蛙2：$0 \to 2 \to \mathbf{\color{red}{4}} \to 6 \to 8 \to \cdots $
- 青蛙3：$0 \to 3 \to 6 \to 9 \to 12 \to \cdots $
- 青蛙4：$0 \to \mathbf{\color{red}{4}} \to 8 \to 12 \to 16 \to \cdots $
- 青蛙5：$0 \to 5 \to 10 \to 15 \to 20 \to \cdots $

因此，如果Slavic和Mihai在坐标$4$放置陷阱，他们可以捕捉到三只青蛙：青蛙1、2和4。可以证明他们无法捕捉到更多的青蛙。

在第二个测试用例中，Slavic和Mihai可以在坐标$2$放置陷阱，并立即捕捉到所有三只青蛙。

### 算法分类

**数学**

### 题解分析与结论

题目要求找到一个坐标$x$（$1 \leq x \leq n$），使得在$a$数组中$x$的因数个数最多。核心思路是通过统计每个数的因数在$a$数组中的出现次数，最终找到最大值。

### 评分较高的题解

1. **作者：Crazyouth (赞：9)**
   - **星级：5**
   - **关键亮点：**
     - 通过统计$a$数组中每个数的出现次数，避免了重复计算。
     - 使用双重循环计算每个数的因数个数，时间复杂度为$O(n \log n)$，效率较高。
     - 代码简洁清晰，易于理解。
   - **核心代码：**
     ```cpp
     for(int i=1;i<=n;i++)
     for(int j=0;j<=n;j+=i)
     {
         cnt[j]+=num[i];//计算因数个数
     }
     int ans=-1;
     for(int i=1;i<=n;i++) ans=max(ans,cnt[i]);//取出最大
     ```

2. **作者：Zaku (赞：1)**
   - **星级：4**
   - **关键亮点：**
     - 使用桶统计每个数的出现次数，避免了重复计算。
     - 通过倒序遍历桶，优化了计算过程，时间复杂度为$O(n \log n)$。
     - 代码简洁，逻辑清晰。
   - **核心代码：**
     ```cpp
     for (int i = n; i >= 1; i -- )
         for(int j = 2 * i; j <= n; j += i) 
             t[j] += t[i];
     cout << *max_element(t + 1, t + 1 + n) << endl;
     ```

3. **作者：Phartial (赞：0)**
   - **星级：4**
   - **关键亮点：**
     - 使用桶统计每个数的出现次数，避免了重复计算。
     - 通过枚举每个数的倍数，优化了计算过程，时间复杂度为$O(n \log n)$。
     - 代码简洁，逻辑清晰。
   - **核心代码：**
     ```cpp
     for (int i = 1; i <= n; ++i) {
         for (int j = i; j <= n; j += i) {
             f[j] += b[i];
         }
     }
     cout << *max_element(f + 1, f + n + 1) << '\n';
     ```

### 最优关键思路与技巧

- **统计出现次数**：通过统计$a$数组中每个数的出现次数，避免了重复计算。
- **枚举倍数**：通过枚举每个数的倍数，优化了计算过程，时间复杂度为$O(n \log n)$。
- **桶优化**：使用桶统计每个数的出现次数，进一步优化了计算过程。

### 可拓展之处

- **类似题目**：可以扩展到其他需要统计因数或倍数的题目，如统计某个范围内所有数的因数个数等。
- **优化技巧**：在类似题目中，可以通过统计出现次数和枚举倍数来优化计算过程。

### 推荐题目

1. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
2. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
3. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)

---
处理用时：29.84秒