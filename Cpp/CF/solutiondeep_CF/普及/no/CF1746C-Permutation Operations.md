# 题目信息

# Permutation Operations

## 题目描述

You are given a permutation $ a $ of size $ n $ and you should perform $ n $ operations on it. In the $ i $ -th operation, you can choose a non-empty suffix of $ a $ and increase all of its elements by $ i $ . How can we perform the operations to minimize the number of inversions in the final array?

Note that you can perform operations on the same suffix any number of times you want.

A permutation of size $ n $ is an array of size $ n $ such that each integer from $ 1 $ to $ n $ occurs exactly once in this array. A suffix is several consecutive elements of an array that include the last element of the array. An inversion in an array $ a $ is a pair of indices $ (i, j) $ such that $ i > j $ and $ a_{i} < a_{j} $ .

## 说明/提示

In the first test case one of the optimal solutions is to increase the whole array on each operation (that is, choose the suffix starting at index $ 1 $ ). The final array $ [11, 12, 13, 14] $ contains $ 0 $ inversions.

In the second test case, $ a $ will be equal to $ [2, 4, 3, 5, 6] $ , $ [2, 4, 3, 7, 8] $ , $ [2, 4, 6, 10, 11] $ , $ [2, 8, 10, 14, 15] $ and $ [7, 13, 15, 19, 20] $ after the first, second, third, fourth, and fifth operations, respectively. So the final array $ a $ has zero inversions.

## 样例 #1

### 输入

```
4
4
1 2 3 4
5
1 3 2 4 5
3
2 3 1
1
1```

### 输出

```
1 1 1 1
1 4 3 2 1
1 3 3
1```

# AI分析结果

### 题目内容重写
# 排列操作

## 题目描述

给定一个大小为 $n$ 的排列 $a$，你需要对它进行 $n$ 次操作。在第 $i$ 次操作中，你可以选择 $a$ 的一个非空后缀，并将其中的所有元素增加 $i$。如何执行这些操作，才能使最终数组中的逆序对数量最小？

注意：你可以对同一个后缀进行任意次数的操作。

一个大小为 $n$ 的排列是一个大小为 $n$ 的数组，其中每个从 $1$ 到 $n$ 的整数恰好出现一次。一个后缀是数组中包含最后一个元素的连续元素。数组 $a$ 中的逆序对是指一对索引 $(i, j)$，满足 $i > j$ 且 $a_{i} < a_{j}$。

## 说明/提示

在第一个测试用例中，一个最优解是在每次操作中增加整个数组（即选择从索引 $1$ 开始的后缀）。最终数组 $[11, 12, 13, 14]$ 包含 $0$ 个逆序对。

在第二个测试用例中，$a$ 在第一次、第二次、第三次、第四次和第五次操作后分别等于 $[2, 4, 3, 5, 6]$、$[2, 4, 3, 7, 8]$、$[2, 4, 6, 10, 11]$、$[2, 8, 10, 14, 15]$ 和 $[7, 13, 15, 19, 20]$。因此，最终数组 $a$ 有零个逆序对。

## 样例 #1

### 输入

```
4
4
1 2 3 4
5
1 3 2 4 5
3
2 3 1
1
1```

### 输出

```
1 1 1 1
1 4 3 2 1
1 3 3
1```

### 算法分类
构造

### 题解分析与结论
本题的核心目标是通过对排列的后缀进行增量操作，使得最终数组中的逆序对数量最小。题解中主要采用了构造的思路，通过合理的操作顺序和选择后缀，使得数组最终严格递增，从而消除所有逆序对。

### 所选题解
1. **作者：晴空一鹤 (赞：8)**  
   - **星级：4.5**  
   - **关键亮点**：通过每次操作选择特定位置的后缀，确保最终数组严格递增。思路清晰，代码简洁，时间复杂度为 $O(n)$。  
   - **个人心得**：构造题的关键在于找到合适的操作顺序，确保每一步都朝着目标前进。  
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++) {
         cin>>a[i];b[a[i]]=i+1;
     }
     for(int i=1;i<=n;i++)cout<<min(b[i],n)<<" ";
     ```

2. **作者：Light_Cone (赞：0)**  
   - **星级：4**  
   - **关键亮点**：通过差分思想，分析逆序对的贡献，选择最优的操作位置，确保逆序对数量最小。时间复杂度为 $O(n)$。  
   - **核心代码**：
     ```cpp
     fori(i,n) cin>>a[i],ans[n-a[i]+1]=i;
     fori(i,n) cout<<ans[i]<<" \n"[i==n];
     ```

3. **作者：lenlen (赞：13)**  
   - **星级：4**  
   - **关键亮点**：通过差分数组，找到需要调整的位置，确保最终数组严格递增。代码实现简单，时间复杂度为 $O(n)$。  
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++) {
         if(s[i]>0) continue;
         ans[a[i-1]]=i;
     }
     ```

### 最优关键思路或技巧
1. **构造法**：通过合理的操作顺序和选择后缀，确保最终数组严格递增。
2. **差分思想**：通过分析差分数组，找到需要调整的位置，确保逆序对数量最小。

### 可拓展之处
类似的问题可以通过构造法或差分思想来解决，尤其是在需要对数组进行多次操作以达到某种目标的情况下。

### 推荐题目
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

---
处理用时：34.59秒