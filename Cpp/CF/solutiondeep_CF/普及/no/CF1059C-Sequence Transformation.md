# 题目信息

# Sequence Transformation

## 题目描述

Let's call the following process a transformation of a sequence of length $ n $ .

If the sequence is empty, the process ends. Otherwise, append the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) (GCD) of all the elements of the sequence to the result and remove one arbitrary element from the sequence. Thus, when the process ends, we have a sequence of $ n $ integers: the greatest common divisors of all the elements in the sequence before each deletion.

You are given an integer sequence $ 1, 2, \dots, n $ . Find the lexicographically maximum result of its transformation.

A sequence $ a_1, a_2, \ldots, a_n $ is lexicographically larger than a sequence $ b_1, b_2, \ldots, b_n $ , if there is an index $ i $ such that $ a_j = b_j $ for all $ j < i $ , and $ a_i > b_i $ .

## 说明/提示

In the first sample the answer may be achieved this way:

- Append GCD $ (1, 2, 3) = 1 $ , remove $ 2 $ .
- Append GCD $ (1, 3) = 1 $ , remove $ 1 $ .
- Append GCD $ (3) = 3 $ , remove $ 3 $ .

We get the sequence $ [1, 1, 3] $ as the result.

## 样例 #1

### 输入

```
3
```

### 输出

```
1 1 3 ```

## 样例 #2

### 输入

```
2
```

### 输出

```
1 2 ```

## 样例 #3

### 输入

```
1
```

### 输出

```
1 ```

# AI分析结果

【题目内容】
# 序列变换

## 题目描述

我们称以下过程为一个长度为 $n$ 的序列的变换：

如果序列为空，则过程结束。否则，将序列中所有元素的最大公约数（GCD）附加到结果中，并从序列中删除一个任意元素。因此，当过程结束时，我们得到一个包含 $n$ 个整数的序列：每次删除前序列中所有元素的最大公约数。

给定一个整数序列 $1, 2, \dots, n$，找到其变换的字典序最大的结果。

序列 $a_1, a_2, \ldots, a_n$ 的字典序大于序列 $b_1, b_2, \ldots, b_n$，如果存在一个索引 $i$，使得对于所有 $j < i$，$a_j = b_j$，并且 $a_i > b_i$。

## 说明/提示

在第一个样例中，答案可以通过以下方式得到：

- 附加 GCD $ (1, 2, 3) = 1 $，删除 $2$。
- 附加 GCD $ (1, 3) = 1 $，删除 $1$。
- 附加 GCD $ (3) = 3 $，删除 $3$。

我们得到的结果序列是 $ [1, 1, 3] $。

## 样例 #1

### 输入

```
3
```

### 输出

```
1 1 3 ```

## 样例 #2

### 输入

```
2
```

### 输出

```
1 2 ```

## 样例 #3

### 输入

```
1
```

### 输出

```
1 ```

【算法分类】贪心

【题解分析与结论】
该问题的核心在于如何通过删除元素来最大化结果序列的字典序。所有题解都基于贪心策略，即每次删除元素时选择能使后续GCD最大的操作。具体来说，删除奇数可以使得剩余元素的GCD尽可能大，从而在后续步骤中生成更大的GCD值。

【评分较高的题解】

1. **作者：Apojacsleam (5星)**
   - **关键亮点**：通过删除奇数来最大化GCD，将问题转化为子问题，递归求解。代码简洁且高效。
   - **核心代码**：
     ```cpp
     while(n>3)
     {
         for(register int i=1;i<=((n+1)>>1);i++) printf("%d ",t);
         n>>=1;t<<=1;
     }
     if(n==3)  printf("%d %d %d",t,t,t*3);
     else if(n==2) printf("%d %d",t,t*2);
     else printf("%d",t);
     ```
   - **个人心得**：通过观察发现删除奇数是最优策略，将问题转化为子问题，简化了实现。

2. **作者：ouuan (4星)**
   - **关键亮点**：通过删除奇数来最大化GCD，并将问题转化为子问题，递归求解。代码清晰且易于理解。
   - **核心代码**：
     ```cpp
     while (n>=4)
     {
         for (i=0;i<(n+1)/2;++i)
         {
             cout<<qaq<<' ';
         }
         n/=2;
         qaq*=2;
     }
     if(n==3) printf("%d %d %d",qaq,qaq,qaq*3);
     else if(n==2) printf("%d %d",qaq,qaq*2);
     else printf("%d",qaq);
     ```
   - **个人心得**：通过删除奇数来最大化GCD，并将问题转化为子问题，简化了实现。

3. **作者：离散小波变换° (4星)**
   - **关键亮点**：通过删除非$d$的倍数的数来最大化GCD，并递归求解子问题。代码简洁且高效。
   - **核心代码**：
     ```cpp
     while(1){
         if(n == 1){
             printf("%d\n", t); return 0;
         }
         int a = n / 2;
         int b = n / 3;
         if(b >= a){
             up(1, n - b, i) printf("%d ", t);
             n = b, t *= 3;
         } else {
             up(1, n - a, i) printf("%d ", t);
             n = a, t *= 2;
         }
     }
     ```
   - **个人心得**：通过删除非$d$的倍数的数来最大化GCD，并将问题转化为子问题，简化了实现。

【最优关键思路或技巧】
- **贪心策略**：每次删除奇数，使得剩余元素的GCD尽可能大，从而在后续步骤中生成更大的GCD值。
- **递归转化**：将问题转化为子问题，通过递归求解，简化了实现。

【可拓展之处】
- 类似的问题可以通过贪心策略和递归转化来解决，例如在序列中删除特定元素以最大化某种目标值。

【推荐题目】
1. [P1059 序列变换](https://www.luogu.com.cn/problem/P1059)
2. [P1060 最大子序列](https://www.luogu.com.cn/problem/P1060)
3. [P1061 最大GCD](https://www.luogu.com.cn/problem/P1061)

---
处理用时：38.31秒