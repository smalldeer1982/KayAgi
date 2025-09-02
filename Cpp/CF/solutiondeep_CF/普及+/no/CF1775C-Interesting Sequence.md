# 题目信息

# Interesting Sequence

## 题目描述

Petya and his friend, robot Petya++, like to solve exciting math problems.

One day Petya++ came up with the numbers $ n $ and $ x $ and wrote the following equality on the board: $ $$$n\ \&\ (n+1)\ \&\ \dots\ \&\ m = x, $ $  where  $ \\&amp; $  denotes the <a href="https://en.wikipedia.org/wiki/Bitwise_operation#AND">bitwise AND operation</a>. Then he suggested his friend Petya find such a minimal  $ m $  ( $ m \\ge n$$$) that the equality on the board holds.

Unfortunately, Petya couldn't solve this problem in his head and decided to ask for computer help. He quickly wrote a program and found the answer.

Can you solve this difficult problem?

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775C/3708862555546ebb5c352c2d2207eacbd490398b.png)

## 说明/提示

In the first example, $ 10\ \&\ 11 = 10 $ , but $ 10\ \&\ 11\ \&\ 12 = 8 $ , so the answer is $ 12 $ .

In the second example, $ 10 = 10 $ , so the answer is $ 10 $ .

In the third example, we can see that the required $ m $ does not exist, so we have to print $ -1 $ .

## 样例 #1

### 输入

```
5
10 8
10 10
10 42
20 16
1000000000000000000 0```

### 输出

```
12
10
-1
24
1152921504606846976```

# AI分析结果

### 题目内容重写（中文）

**有趣的序列**

**题目描述**

Petya 和他的朋友，机器人 Petya++，喜欢解决有趣的数学问题。

有一天，Petya++ 提出了两个数字 $n$ 和 $x$，并在黑板上写下了以下等式：

$$ n\ \&\ (n+1)\ \&\ \dots\ \&\ m = x, $$

其中 $\&$ 表示按位与操作。然后他建议他的朋友 Petya 找到最小的 $m$（$m \geq n$），使得黑板上的等式成立。

不幸的是，Petya 无法在脑海中解决这个问题，决定求助于计算机。他很快写了一个程序并找到了答案。

你能解决这个难题吗？

**说明/提示**

在第一个例子中，$10\ \&\ 11 = 10$，但 $10\ \&\ 11\ \&\ 12 = 8$，所以答案是 $12$。

在第二个例子中，$10 = 10$，所以答案是 $10$。

在第三个例子中，我们可以看到所需的 $m$ 不存在，所以必须输出 $-1$。

**样例 #1**

**输入**

```
5
10 8
10 10
10 42
20 16
1000000000000000000 0
```

**输出**

```
12
10
-1
24
1152921504606846976
```

### 算法分类
位运算

### 题解分析与结论

这道题的核心在于通过按位与操作找到最小的 $m$，使得从 $n$ 到 $m$ 的所有数的按位与结果等于 $x$。多位题解都采用了类似的思路，即通过分析二进制位的变化来逐步逼近答案。

#### 关键思路与技巧
1. **二进制位分析**：大多数题解都从二进制位的角度出发，分析 $n$ 和 $x$ 的每一位，判断是否存在无解情况，并逐步调整 $n$ 的值。
2. **lowbit 操作**：多位题解使用了 `lowbit` 操作（即 `x & -x`）来快速找到 $n$ 的最低有效位，并通过不断加上 `lowbit` 来逐步调整 $n$ 的值。
3. **无解条件**：如果 $n$ 的某一位为 $0$ 而 $x$ 的对应位为 $1$，则无解。此外，如果 $n$ 的某些位无法通过按位与操作变为 $x$ 的对应位，也无解。

#### 推荐题解

1. **BFSDFS123 的题解（4星）**
   - **关键亮点**：通过 `lowbit` 操作逐步调整 $n$ 的值，并在过程中判断无解情况。思路清晰，代码简洁。
   - **核心代码**：
     ```cpp
     while(na!=nb)
     {
         a+=lowbit(a);
         na=na&a;
         if(na<nb)
         {
             puts("-1");
             return ;
         }
     }
     printf("%lld\n",a);
     ```
   - **个人心得**：通过 `lowbit` 操作逐步逼近答案，避免了复杂的二进制位操作。

2. **xiaomuyun 的题解（4星）**
   - **关键亮点**：详细分析了二进制位的变化，并提出了三种无解情况，逻辑严谨。
   - **核心代码**：
     ```cpp
     if(sn[i]!=sx[i]&&sx[i]=='1'){//第一种无解情况
         flag=true;
         break;
     }
     if(sn[i]==sx[i]&&sx[i]=='1') f=true;//统计前面是否有定下来的1
     if(sn[i]!=sx[i]&&sx[i]=='0'){
         lst=i;
         if(f){//第三种无解情况
             flag=true;
             break;
         }
     }
     ```
   - **个人心得**：通过二进制位的逐位分析，确保了无解条件的全面覆盖。

3. **not_clever_syl 的题解（4星）**
   - **关键亮点**：通过 `lowbit` 操作逐步调整 $n$ 的值，并在过程中判断无解情况，代码简洁高效。
   - **核心代码**：
     ```cpp
     while((n&y)&&!(x&y)&&(m&y))m+=lowbit(m);//一直加上lowbit(m)直到m的那一位为0
     n&=m;
     f=f||bool((~n)&x);//m让比它低位的1变成了0，此时无解，输出-1
     if(f)break;
     ```
   - **个人心得**：通过 `lowbit` 操作逐步逼近答案，避免了复杂的二进制位操作。

### 扩展思路
这道题的核心在于二进制位的分析与按位与操作的应用。类似的问题可以通过分析二进制位的变化来解决，例如通过按位或、按位异或等操作来调整数字的值。

### 推荐题目
1. [P1100 高低位交换](https://www.luogu.com.cn/problem/P1100)
2. [P1226 快速幂](https://www.luogu.com.cn/problem/P1226)
3. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)

---
处理用时：44.04秒