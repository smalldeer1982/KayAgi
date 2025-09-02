# 题目信息

# Divisors of Two Integers

## 题目描述

Recently you have received two positive integer numbers $ x $ and $ y $ . You forgot them, but you remembered a shuffled list containing all divisors of $ x $ (including $ 1 $ and $ x $ ) and all divisors of $ y $ (including $ 1 $ and $ y $ ). If $ d $ is a divisor of both numbers $ x $ and $ y $ at the same time, there are two occurrences of $ d $ in the list.

For example, if $ x=4 $ and $ y=6 $ then the given list can be any permutation of the list $ [1, 2, 4, 1, 2, 3, 6] $ . Some of the possible lists are: $ [1, 1, 2, 4, 6, 3, 2] $ , $ [4, 6, 1, 1, 2, 3, 2] $ or $ [1, 6, 3, 2, 4, 1, 2] $ .

Your problem is to restore suitable positive integer numbers $ x $ and $ y $ that would yield the same list of divisors (possibly in different order).

It is guaranteed that the answer exists, i.e. the given list of divisors corresponds to some positive integers $ x $ and $ y $ .

## 样例 #1

### 输入

```
10
10 2 8 1 2 4 1 20 4 5
```

### 输出

```
20 8
```

# AI分析结果

【题目内容】
# 两个整数的约数

## 题目描述

最近你收到了两个正整数 $x$ 和 $y$。你忘记了它们，但你记得一个包含 $x$ 的所有约数（包括 $1$ 和 $x$）和 $y$ 的所有约数（包括 $1$ 和 $y$）的乱序列表。如果 $d$ 同时是 $x$ 和 $y$ 的约数，那么 $d$ 在列表中会出现两次。

例如，如果 $x=4$ 和 $y=6$，那么给定的列表可以是 $[1, 2, 4, 1, 2, 3, 6]$ 的任意排列。一些可能的列表是：$[1, 1, 2, 4, 6, 3, 2]$、$[4, 6, 1, 1, 2, 3, 2]$ 或 $[1, 6, 3, 2, 4, 1, 2]$。

你的问题是恢复合适的正整数 $x$ 和 $y$，使得它们能生成相同的约数列表（可能顺序不同）。

保证答案存在，即给定的约数列表对应某些正整数 $x$ 和 $y$。

## 样例 #1

### 输入

```
10
10 2 8 1 2 4 1 20 4 5
```

### 输出

```
20 8
```

【算法分类】  
数学

【题解分析与结论】  
本题的核心思路是通过分析约数的性质，找出两个整数 $x$ 和 $y$。所有题解都基于以下关键点：
1. **最大数性质**：列表中最大的数一定是 $x$ 或 $y$ 中的一个，因为一个数的最大约数是它本身。
2. **约数剔除**：在确定了一个数（如 $x$）后，剔除列表中所有 $x$ 的约数，剩下的数中最大的就是另一个数 $y$。
3. **重复约数处理**：如果 $x$ 和 $y$ 有共同的约数，这些约数在列表中会出现两次，因此需要确保只剔除一次。

【评分较高的题解】

1. **作者：STA_Morlin (5星)**  
   - **关键亮点**：通过 $\Theta(n)$ 的时间复杂度实现，避免了排序的开销，代码简洁高效。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= n; ++ i) {
         v[a[i]] -= !(x%a[i]);
         if (v[a[i]]) y = max(y, a[i]);
     }
     ```
   - **个人心得**：通过使用计数数组 `v` 来记录每个数的出现次数，确保只剔除一次 $x$ 的约数，从而高效地找到 $y$。

2. **作者：installb (4星)**  
   - **关键亮点**：使用 `char` 数组代替 `bool` 数组，节省空间，代码清晰。
   - **核心代码**：
     ```cpp
     for(register int i = 1;i <= n;i ++){
         if(maxn % a[i] == 0 && (!vis[a[i]])){
             vis[a[i]] = 1;
             a[i] = 0;
         }
     }
     ```
   - **个人心得**：通过将已处理的数置为 $0$，避免了重复处理，简化了后续的最大值查找。

3. **作者：AzureMist (4星)**  
   - **关键亮点**：通过排序和标记数组，确保只剔除一次 $x$ 的约数，思路清晰。
   - **核心代码**：
     ```cpp
     for(int i=0;i<=n-1;i++){
         if(d[n-1]%d[i]==0&&em[d[i]]==0){
             em[d[i]]=1;
             d[i]=-1;
         }
     }
     ```
   - **个人心得**：通过将已处理的数置为 $-1$，避免了重复处理，简化了后续的最大值查找。

【最优关键思路】  
- **最大数性质**：利用列表中最大数一定是 $x$ 或 $y$ 的性质，快速确定一个数。
- **约数剔除**：通过标记或计数数组，确保只剔除一次 $x$ 的约数，避免重复处理。
- **时间复杂度优化**：避免排序，直接通过一次遍历找到最大值和剔除约数，达到 $\Theta(n)$ 的时间复杂度。

【可拓展之处】  
- **类似问题**：可以扩展到多个整数的约数问题，或者处理更复杂的约数关系。
- **算法套路**：在处理约数相关问题时，通常可以利用最大数性质和约数剔除的思路，结合计数或标记数组来优化时间复杂度。

【推荐题目】  
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
2. [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)
3. [P1069 细胞分裂](https://www.luogu.com.cn/problem/P1069)

---
处理用时：37.52秒