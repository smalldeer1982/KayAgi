# 题目信息

# Numbers on Whiteboard

## 题目描述

Numbers $ 1, 2, 3, \dots n $ (each integer from $ 1 $ to $ n $ once) are written on a board. In one operation you can erase any two numbers $ a $ and $ b $ from the board and write one integer $ \frac{a + b}{2} $ rounded up instead.

You should perform the given operation $ n - 1 $ times and make the resulting number that will be left on the board as small as possible.

For example, if $ n = 4 $ , the following course of action is optimal:

1. choose $ a = 4 $ and $ b = 2 $ , so the new number is $ 3 $ , and the whiteboard contains $ [1, 3, 3] $ ;
2. choose $ a = 3 $ and $ b = 3 $ , so the new number is $ 3 $ , and the whiteboard contains $ [1, 3] $ ;
3. choose $ a = 1 $ and $ b = 3 $ , so the new number is $ 2 $ , and the whiteboard contains $ [2] $ .

It's easy to see that after $ n - 1 $ operations, there will be left only one number. Your goal is to minimize it.

## 样例 #1

### 输入

```
1
4```

### 输出

```
2
2 4
3 3
3 1```

# AI分析结果

### 题目内容重写
**题目描述**  
数字 $1, 2, 3, \dots, n$（每个整数从 $1$ 到 $n$ 各出现一次）被写在白板上。每次操作中，你可以擦去白板上的任意两个数字 $a$ 和 $b$，并写上一个整数 $\frac{a + b}{2}$ 向上取整的结果。你需要执行 $n - 1$ 次操作，使得最终留在白板上的数字尽可能小。

例如，当 $n = 4$ 时，最优的操作序列如下：  
1. 选择 $a = 4$ 和 $b = 2$，得到新数字 $3$，白板上剩下 $[1, 3, 3]$；  
2. 选择 $a = 3$ 和 $b = 3$，得到新数字 $3$，白板上剩下 $[1, 3]$；  
3. 选择 $a = 1$ 和 $b = 3$，得到新数字 $2$，白板上剩下 $[2]$。  

显然，经过 $n - 1$ 次操作后，白板上只会剩下一个数字。你的目标是最小化这个数字。

**样例输入**  
```
1
4
```

**样例输出**  
```
2
2 4
3 3
3 1
```

### 算法分类
贪心、构造

### 题解分析与结论
题目要求通过合并操作使得最终剩下的数字尽可能小。所有题解的核心思路都是通过贪心策略，每次选择最大的两个数进行合并，从而逐步减少序列中的最大值，最终得到最小的结果。经过分析，最终结果恒为 $2$，且可以通过特定的合并顺序实现。

### 精选题解
1. **作者：Konnyaku_LXZ**  
   - **星级：5**  
   - **关键亮点**：通过数学归纳法证明了最终结果恒为 $2$，并给出了简洁的合并顺序。代码实现清晰，逻辑严谨。  
   - **核心代码**：
     ```cpp
     void Print(){
         puts("2");
         for(int i=N;i>1;--i) printf("%d %d\n",i-1,i==N?i:i+1);
     }
     ```
   - **个人心得**：通过数学归纳法证明了结果的最优性，避免了复杂的模拟过程。

2. **作者：_zy_**  
   - **星级：4**  
   - **关键亮点**：通过举例和图示直观地展示了合并过程，帮助理解贪心策略的正确性。代码实现简洁，适合初学者理解。  
   - **核心代码**：
     ```cpp
     printf("2\n");
     if(n==2) {printf("1 2\n");continue;}
     printf("%d %d\n",n,n-2);
     printf("%d %d\n",n-1,n-1);
     while(n>=4) {
         printf("%d %d\n",n-1,n-3);
         n--;
     }
     ```
   - **个人心得**：通过举例和图示帮助理解贪心策略的正确性，适合初学者。

3. **作者：_Xiuer_**  
   - **星级：4**  
   - **关键亮点**：通过数学推导证明了最终结果为 $2$，并给出了详细的合并步骤。代码实现清晰，逻辑严谨。  
   - **核心代码**：
     ```cpp
     printf("2\n");
     if(n==2) {printf("1 2\n");continue;}
     printf("%d %d\n",n,n-2);
     printf("%d %d\n",n-1,n-1);
     for(int i=n-3;i>=1;i--)
         printf("%d %d\n",i+2,i);
     ```
   - **个人心得**：通过数学推导证明了结果的最优性，避免了复杂的模拟过程。

### 最优思路与技巧
1. **贪心策略**：每次选择最大的两个数进行合并，逐步减少序列中的最大值，最终得到最小的结果。
2. **数学归纳法**：通过数学归纳法证明最终结果恒为 $2$，避免了复杂的模拟过程。
3. **构造性证明**：通过构造特定的合并顺序，确保最终结果为 $2$。

### 拓展思路
类似的问题可以通过贪心策略和构造性证明来解决，例如在某些合并操作中，通过选择特定的数对来达到最优结果。这类问题通常需要结合数学归纳法和贪心策略来进行分析和解决。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)  
2. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)  
3. [P1966 [NOIP2013 提高组] 火柴排队](https://www.luogu.com.cn/problem/P1966)

---
处理用时：35.00秒