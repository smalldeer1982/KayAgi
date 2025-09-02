# 题目信息

# Array Repetition

## 题目描述

Jayden has an array $ a $ which is initially empty. There are $ n $ operations of two types he must perform in the given order.

1. Jayden appends an integer $ x $ ( $ 1 \leq x \leq n $ ) to the end of array $ a $ .
2. Jayden appends $ x $ copies of array $ a $ to the end of array $ a $ . In other words, array $ a $ becomes $ [a,\underbrace{a,\ldots,a}_{x}] $ . It is guaranteed that he has done at least one operation of the first type before this.

Jayden has $ q $ queries. For each query, you must tell him the $ k $ -th element of array $ a $ . The elements of the array are numbered from $ 1 $ .

## 说明/提示

In the first test case:

- After the first operation $ a = [1] $ ;
- After the second operation $ a = [1, 2] $ ;
- After the third operation $ a = [1, 2, 1, 2] $ ;
- After the fourth operation $ a = [1, 2, 1, 2, 3] $ ;
- After the fifth operation $ a = [1, 2, 1, 2, 3, 1, 2, 1, 2, 3, 1, 2, 1, 2, 3, 1, 2, 1, 2, 3] $ .

In the fourth test case, after all operations $ a = [1, 2] $ .

## 样例 #1

### 输入

```
4
5 10
1 1
1 2
2 1
1 3
2 3
1 2 3 4 5 6 14 15 16 20
10 10
1 3
1 8
2 15
1 6
1 9
1 1
2 6
1 1
2 12
2 10
32752 25178 3198 3199 2460 2461 31450 33260 9016 4996
12 5
1 6
1 11
2 392130334
1 4
2 744811750
1 10
1 5
2 209373780
2 178928984
1 3
2 658326464
2 1000000000
914576963034536490 640707385283752918 636773368365261971 584126563607944922 1000000000000000000
2 2
1 1
1 2
1 2```

### 输出

```
1 2 1 2 3 1 2 3 1 3
9 8 1 3 1 3 6 3 8 8
11 11 11 10 11
1 2```

# AI分析结果

### 题目翻译
Jayden 有一个初始为空的数组 $a$，他需要按顺序执行 $n$ 次操作，操作分为两种类型：

1. Jayden 将一个整数 $x$（$1 \leq x \leq n$）添加到数组 $a$ 的末尾。
2. Jayden 将数组 $a$ 复制 $x$ 份并添加到数组 $a$ 的末尾。换句话说，数组 $a$ 变为 $[a,\underbrace{a,\ldots,a}_{x}]$。保证在执行此操作之前至少执行过一次第一种操作。

Jayden 有 $q$ 个查询。对于每个查询，你需要告诉他数组 $a$ 的第 $k$ 个元素。数组的元素从 $1$ 开始编号。

### 算法分类
模拟、递归、二分

### 题解分析与结论
该题的核心在于如何处理大规模数组的复制操作，避免直接存储和遍历。所有题解都采用了类似的思路：通过记录每次操作后的数组长度，利用递归或二分查找来确定第 $k$ 个元素的位置。由于复制操作会使得数组长度呈指数级增长，因此题解中大多通过取模操作来缩小查询范围，从而避免直接处理超长数组。

### 精选题解
1. **题解作者：Luzhuoyuan**  
   **星级：5**  
   **关键亮点：**  
   - 通过记录每个复制操作后的数组长度，利用递归和取模操作快速定位第 $k$ 个元素。
   - 代码简洁，逻辑清晰，使用了 `vector` 来存储每个复制操作后的数组片段。
   - 时间复杂度为 $O(q\log V)$，其中 $V$ 为 $k$ 的值域，效率较高。

   **核心代码：**
   ```cpp
   while(m--){
       int x=read();
       for(int i=k;i>=0;i--){
           x=(x-1)%l[i]+1;
           if(x>g[i]){printf("%d ",ve[i][x-g[i]-1]);break;}
       }
   }
   ```

2. **题解作者：ax_by_c**  
   **星级：4**  
   **关键亮点：**  
   - 通过二分查找确定第 $k$ 个元素的位置，利用递归和取模操作缩小查询范围。
   - 代码结构清晰，使用了 `upper_bound` 进行二分查找，时间复杂度为 $O(q\log n)$。
   - 通过记录每个操作后的数组长度，避免了直接处理超长数组。

   **核心代码：**
   ```cpp
   int Q(int ed,ll pos){
       if(op[ed]==2){
           return Q(ed-1,(pos-1)%sz[ed-1]+1);
       }
       else{
           if(sz[ed]==pos) return kr[ed];
           if(sz[pr[ed]]<pos) return kr[ed-sz[ed]+pos];
           return Q(pr[ed],pos);
       }
   }
   ```

3. **题解作者：kimidonatsu**  
   **星级：4**  
   **关键亮点：**  
   - 通过记录每次操作后的数组长度，利用递归和取模操作快速定位第 $k$ 个元素。
   - 代码逻辑清晰，使用了 `vector` 来存储每个复制操作后的数组片段。
   - 时间复杂度为 $O(q\log V)$，效率较高。

   **核心代码：**
   ```cpp
   for(int i = pos.size() - 1; ~i; i--){
       int idx = pos[i];
       if(f[idx] > k && f[idx - 1] < k){
           if(k % f[idx - 1] == 0) k = f[idx - 1];
           else k %= f[idx - 1];
       }
   }
   ```

### 最优关键思路
通过记录每次操作后的数组长度，利用递归或二分查找结合取模操作，快速定位第 $k$ 个元素的位置，避免直接处理超长数组。

### 拓展思路
类似的问题可以通过记录关键操作后的状态，利用递归或二分查找来缩小查询范围，避免直接处理大规模数据。这种方法在处理大规模复制、拼接等操作时非常有效。

### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

---
处理用时：40.48秒