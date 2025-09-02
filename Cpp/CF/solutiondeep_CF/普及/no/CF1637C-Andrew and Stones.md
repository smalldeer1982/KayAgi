# 题目信息

# Andrew and Stones

## 题目描述

Andrew has $ n $ piles with stones. The $ i $ -th pile contains $ a_i $ stones. He wants to make his table clean so he decided to put every stone either to the $ 1 $ -st or the $ n $ -th pile.

Andrew can perform the following operation any number of times: choose $ 3 $ indices $ 1 \le i < j < k \le n $ , such that the $ j $ -th pile contains at least $ 2 $ stones, then he takes $ 2 $ stones from the pile $ j $ and puts one stone into pile $ i $ and one stone into pile $ k $ .

Tell Andrew what is the minimum number of operations needed to move all the stones to piles $ 1 $ and $ n $ , or determine if it's impossible.

## 说明/提示

In the first test case, it is optimal to do the following:

1. Select $ (i, j, k) = (1, 2, 5) $ . The array becomes equal to $ [2, 0, 2, 3, 7] $ .
2. Select $ (i, j, k) = (1, 3, 4) $ . The array becomes equal to $ [3, 0, 0, 4, 7] $ .
3. Twice select $ (i, j, k) = (1, 4, 5) $ . The array becomes equal to $ [5, 0, 0, 0, 9] $ . This array satisfy the statement, because every stone is moved to piles $ 1 $ and $ 5 $ .

 There are $ 4 $ operations in total.In the second test case, it's impossible to put all stones into piles with numbers $ 1 $ and $ 3 $ :

1. At the beginning there's only one possible operation with $ (i, j, k) = (1, 2, 3) $ . The array becomes equal to $ [2, 1, 2] $ .
2. Now there is no possible operation and the array doesn't satisfy the statement, so the answer is $ -1 $ .

In the third test case, it's optimal to do the following:

1. Select $ (i, j, k) = (1, 2, 3) $ . The array becomes equal to $ [2, 0, 2] $ . This array satisfies the statement, because every stone is moved to piles $ 1 $ and $ 3 $ .

 The is $ 1 $ operation in total.In the fourth test case, it's impossible to do any operation, and the array doesn't satisfy the statement, so the answer is $ -1 $ .

## 样例 #1

### 输入

```
4
5
1 2 2 3 6
3
1 3 1
3
1 2 1
4
3 1 1 2```

### 输出

```
4
-1
1
-1```

# AI分析结果

### 题目内容重写
Andrew 有 $n$ 堆石头，第 $i$ 堆有 $a_i$ 个石头。他希望将所有石头都移动到第 $1$ 堆或第 $n$ 堆中。他可以执行以下操作任意次数：选择三个下标 $1 \le i < j < k \le n$，且第 $j$ 堆至少有 $2$ 个石头，然后从第 $j$ 堆中取出 $2$ 个石头，分别放入第 $i$ 堆和第 $k$ 堆。问最少需要多少次操作才能将所有石头移动到第 $1$ 堆或第 $n$ 堆，或者判断是否不可能。

### 算法分类
贪心

### 题解分析与结论
本题的核心是通过贪心策略，尽可能高效地将中间堆的石头移动到两端。题解主要集中在如何判断无解情况以及如何计算最小操作次数。大多数题解都提到了以下关键点：
1. **无解情况**：当 $n=3$ 且中间堆的石头数为奇数时，或者当所有中间堆的石头数都为 $1$ 时，无解。
2. **操作次数计算**：对于偶数堆，直接计算 $\frac{a_i}{2}$ 次操作；对于奇数堆，需要额外的一次操作将其变为偶数，因此操作次数为 $\frac{a_i+1}{2}$。

### 高星题解推荐
1. **作者：baiABC (5星)**
   - **关键亮点**：清晰的无解判断和操作次数计算，代码简洁且高效。
   - **代码核心**：通过遍历中间堆，统计奇数和偶数的数量，计算最小操作次数。
   ```cpp
   for(int i = 1; i <= n; ++i) {
       if(i == 1 || i == n) continue;
       if(a[i] > 1) ok = true;
       if(a[i] & 1) ++c; // 是奇数
       s += a[i];
   }
   printf("%lld\n", (s+c)/2);
   ```

2. **作者：让风忽悠你 (4星)**
   - **关键亮点**：详细的无解情况分析，操作次数的计算方法清晰。
   - **代码核心**：通过判断中间堆是否有大于 $1$ 的石头，计算操作次数。
   ```cpp
   for(int i = 2; i < n; i++) {
       if(a[i] > 1) pd = 1;
       ans += ((a[i] + 1) / 2);
   }
   printf("%lld\n", ans);
   ```

3. **作者：sprads (4星)**
   - **关键亮点**：对奇偶数的处理思路清晰，代码简洁。
   - **代码核心**：通过遍历中间堆，计算操作次数并判断无解情况。
   ```cpp
   for(int i = 2; i < n; i++) {
       if(a[i] > 1) return 1;
   }
   return 0;
   ```

### 最优关键思路
1. **无解判断**：当 $n=3$ 且中间堆为奇数时，或所有中间堆都为 $1$ 时，无解。
2. **操作次数计算**：对于偶数堆，操作次数为 $\frac{a_i}{2}$；对于奇数堆，操作次数为 $\frac{a_i+1}{2}$。

### 可拓展之处
类似的问题可以扩展到其他类型的移动操作，例如将石头从中间堆移动到任意堆，或者允许不同的移动规则。这类问题通常可以通过贪心策略或动态规划来解决。

### 推荐题目
1. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1966 [NOIP2013 提高组] 火柴排队](https://www.luogu.com.cn/problem/P1966)

---
处理用时：26.30秒