# 题目信息

# Super-Permutation

## 题目描述

A permutation is a sequence $ n $ integers, where each integer from $ 1 $ to $ n $ appears exactly once. For example, $ [1] $ , $ [3,5,2,1,4] $ , $ [1,3,2] $ are permutations, while $ [2,3,2] $ , $ [4,3,1] $ , $ [0] $ are not.

Given a permutation $ a $ , we construct an array $ b $ , where $ b_i = (a_1 + a_2 +~\dots~+ a_i) \bmod n $ .

A permutation of numbers $ [a_1, a_2, \dots, a_n] $ is called a super-permutation if $ [b_1 + 1, b_2 + 1, \dots, b_n + 1] $ is also a permutation of length $ n $ .

Grisha became interested whether a super-permutation of length $ n $ exists. Help him solve this non-trivial problem. Output any super-permutation of length $ n $ , if it exists. Otherwise, output $ -1 $ .

## 样例 #1

### 输入

```
4
1
2
3
6```

### 输出

```
1
2 1
-1
6 5 2 3 4 1```

# AI分析结果

### 题目翻译
# Super-Permutation

## 题目描述

一个排列是一个包含 $n$ 个整数的序列，其中每个整数从 $1$ 到 $n$ 恰好出现一次。例如，$[1]$、$[3,5,2,1,4]$、$[1,3,2]$ 是排列，而 $[2,3,2]$、$[4,3,1]$、$[0]$ 不是。

给定一个排列 $a$，我们构造一个数组 $b$，其中 $b_i = (a_1 + a_2 +~\dots~+ a_i) \bmod n$。

如果排列 $[a_1, a_2, \dots, a_n]$ 满足 $[b_1 + 1, b_2 + 1, \dots, b_n + 1]$ 也是一个长度为 $n$ 的排列，则称其为超级排列。

Grisha 想知道是否存在长度为 $n$ 的超级排列。如果存在，输出任意一个超级排列；否则，输出 $-1$。

## 样例 #1

### 输入

```
4
1
2
3
6
```

### 输出

```
1
2 1
-1
6 5 2 3 4 1
```

### 算法分类
构造

### 题解分析与结论
这道题的核心在于构造一个满足特定条件的排列。通过分析，我们可以得出以下结论：
1. **$n$ 必须放在第一个位置**：如果 $n$ 不放在第一个位置，那么前缀和在模 $n$ 的意义下会出现重复，导致无法满足条件。
2. **奇数无解**：当 $n$ 为奇数时，前缀和的最后一个值会与第一个值在模 $n$ 的意义下相同，导致无法满足条件。
3. **偶数有解**：对于偶数 $n$，可以通过特定的构造方法生成满足条件的排列。

### 高星题解推荐
1. **作者：Little_Cart (赞：14)**  
   - **星级：5星**  
   - **关键亮点**：详细分析了 $n$ 必须放在第一个位置的原因，并给出了奇数和偶数的不同处理方式。通过分段构造，清晰地展示了如何生成满足条件的排列。
   - **代码实现**：
     ```cpp
     cout<<n<<" ";
     for(int i=n-1,j=2;j<=n-2;i-=2,j+=2){
         cout<<i<<" "<<j<<" ";
     }
     cout<<"1\n";
     ```

2. **作者：TimSwn090306 (赞：4)**  
   - **星级：4星**  
   - **关键亮点**：通过数对分组的方式，详细解释了如何构造满足条件的排列。特别是对于偶数 $n$ 的构造方法，给出了清晰的证明。
   - **代码实现**：
     ```cpp
     printf("%d ",n);
     for (int i=n-1;i>1;i-=2) printf("%d %d ",i,n+1-i);
     printf("1\n");
     ```

3. **作者：wawatime1 (赞：2)**  
   - **星级：4星**  
   - **关键亮点**：通过样例分析，找出了构造规律，并给出了简洁的代码实现。特别是对于奇数 $n$ 的无解情况，给出了明确的解释。
   - **代码实现**：
     ```cpp
     printf("%d ", n);
     for (int i = n - 1, j = 2; i > 1 && j < n; i -= 2, j += 2)
         printf("%d %d ", i, j);
     printf("1\n");
     ```

### 最优关键思路
1. **$n$ 必须放在第一个位置**：这是构造满足条件排列的前提。
2. **奇数无解**：通过分析前缀和的性质，可以得出奇数 $n$ 无解的结论。
3. **偶数构造方法**：通过将序列分成数对，确保每组数对的和在模 $n$ 的意义下满足条件。

### 可拓展之处
类似的问题可以通过分析排列的性质，特别是前缀和或模运算的性质，来构造满足特定条件的排列。这类问题通常需要结合数学分析和构造技巧来解决。

### 推荐题目
1. [CF1822D Super-Permutation](https://www.luogu.com.cn/problem/CF1822D)
2. [CF1328C Ternary XOR](https://www.luogu.com.cn/problem/CF1328C)
3. [CF1352C K-th Not Divisible by n](https://www.luogu.com.cn/problem/CF1352C)

### 个人心得总结
- **调试经历**：在构造排列时，确保每个步骤都符合模运算的性质，避免出现重复或遗漏的情况。
- **踩坑教训**：奇数 $n$ 的无解情况容易被忽略，需要特别注意。
- **顿悟感想**：通过分析样例和数学性质，可以找到构造排列的规律，避免盲目尝试。

---
处理用时：32.84秒