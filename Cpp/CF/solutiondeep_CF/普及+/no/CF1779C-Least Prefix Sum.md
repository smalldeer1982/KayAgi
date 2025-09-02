# 题目信息

# Least Prefix Sum

## 题目描述

Baltic, a famous chess player who is also a mathematician, has an array $ a_1,a_2, \ldots, a_n $ , and he can perform the following operation several (possibly $ 0 $ ) times:

- Choose some index $ i $ ( $ 1 \leq i \leq n $ );
- multiply $ a_i $ with $ -1 $ , that is, set $ a_i := -a_i $ .

Baltic's favorite number is $ m $ , and he wants $ a_1 + a_2 + \cdots + a_m $ to be the smallest of all non-empty prefix sums. More formally, for each $ k = 1,2,\ldots, n $ it should hold that $ $$$a_1 + a_2 + \cdots + a_k \geq a_1 + a_2 + \cdots + a_m. $ $ </p><p>Please note that multiple smallest prefix sums may exist and that it is only required that  $ a\_1 + a\_2 + \\cdots + a\_m $  is one of them.</p><p>Help Baltic find the minimum number of operations required to make  $ a\_1 + a\_2 + \\cdots + a\_m$$$ the least of all prefix sums. It can be shown that a valid sequence of operations always exists.

## 说明/提示

In the first example, we perform the operation $ a_4 := -a_4 $ . The array becomes $ [-1,-2,-3,4] $ and the prefix sums, $ [a_1, \ a_1+a_2, \ a_1+a_2+a_3, \ a_1+a_2+a_3+a_4] $ , are equal to $ [-1,-3,-6,-2] $ . Thus $ a_1 + a_2 + a_3=-6 $ is the smallest of all prefix sums.

In the second example, we perform the operation $ a_3 := -a_3 $ . The array becomes $ [1,2,-3,4] $ with prefix sums equal to $ [1,3,0,4] $ .

In the third and fourth examples, $ a_1 + a_2 + \cdots + a_m $ is already the smallest of the prefix sums — no operation needs to be performed.

In the fifth example, a valid sequence of operations is:

- $ a_3 := -a_3 $ ,
- $ a_2 := -a_2 $ ,
- $ a_5 := -a_5 $ .

The array becomes $ [-2,-3,5,-5,20] $ and its prefix sums are $ [-2,-5,0,-5,15] $ . Note that $ a_1+a_2=-5 $ and $ a_1+a_2+a_3+a_4=-5 $ are both the smallest of the prefix sums (and this is a valid solution).

## 样例 #1

### 输入

```
6
4 3
-1 -2 -3 -4
4 3
1 2 3 4
1 1
1
5 5
-2 3 -5 1 -20
5 2
-2 3 -5 -5 -20
10 4
345875723 -48 384678321 -375635768 -35867853 -35863586 -358683842 -81725678 38576 -357865873```

### 输出

```
1
1
0
0
3
4```

# AI分析结果

### 题目内容重写
# 最小前缀和

## 题目描述

Baltic，一位著名的国际象棋选手兼数学家，有一个数组 $ a_1,a_2, \ldots, a_n $，他可以多次（可能为 $ 0 $ 次）执行以下操作：

- 选择某个索引 $ i $（$ 1 \leq i \leq n $）；
- 将 $ a_i $ 乘以 $ -1 $，即设置 $ a_i := -a_i $。

Baltic 最喜欢的数字是 $ m $，他希望 $ a_1 + a_2 + \cdots + a_m $ 是所有非空前缀和中最小的。更正式地说，对于每个 $ k = 1,2,\ldots, n $，应满足：
$$a_1 + a_2 + \cdots + a_k \geq a_1 + a_2 + \cdots + a_m.$$

请注意，可能存在多个最小的前缀和，并且仅要求 $ a_1 + a_2 + \cdots + a_m $ 是其中之一。

帮助 Baltic 找到使 $ a_1 + a_2 + \cdots + a_m $ 成为所有前缀和中最小的所需的最少操作次数。可以证明，总存在一个有效的操作序列。

## 说明/提示

在第一个示例中，我们执行操作 $ a_4 := -a_4 $。数组变为 $ [-1,-2,-3,4] $，前缀和 $ [a_1, \ a_1+a_2, \ a_1+a_2+a_3, \ a_1+a_2+a_3+a_4] $ 等于 $ [-1,-3,-6,-2] $。因此，$ a_1 + a_2 + a_3=-6 $ 是所有前缀和中最小的。

在第二个示例中，我们执行操作 $ a_3 := -a_3 $。数组变为 $ [1,2,-3,4] $，前缀和等于 $ [1,3,0,4] $。

在第三和第四个示例中，$ a_1 + a_2 + \cdots + a_m $ 已经是所有前缀和中最小的，因此无需执行任何操作。

在第五个示例中，一个有效的操作序列是：

- $ a_3 := -a_3 $，
- $ a_2 := -a_2 $，
- $ a_5 := -a_5 $。

数组变为 $ [-2,-3,5,-5,20] $，其前缀和为 $ [-2,-5,0,-5,15] $。注意，$ a_1+a_2=-5 $ 和 $ a_1+a_2+a_3+a_4=-5 $ 都是所有前缀和中最小的（这是一个有效的解决方案）。

## 样例 #1

### 输入

```
6
4 3
-1 -2 -3 -4
4 3
1 2 3 4
1 1
1
5 5
-2 3 -5 1 -20
5 2
-2 3 -5 -5 -20
10 4
345875723 -48 384678321 -375635768 -35867853 -35863586 -358683842 -81725678 38576 -357865873```

### 输出

```
1
1
0
0
3
4```

### 算法分类
贪心

### 题解分析与结论
本题的核心是通过贪心策略，利用优先队列（堆）来维护当前区间内的最大值或最小值，从而在每次操作中选择最优的元素进行取反操作，以达到使前缀和最小的目的。题解中普遍采用了从 $m$ 向两端扫描的方法，分别处理 $[1, m]$ 和 $[m+1, n]$ 区间，确保每个区间的前缀和满足条件。

### 精选题解
1. **作者：xzy090626 (5星)**
   - **关键亮点**：清晰地分析了问题的数学性质，提出了从 $m$ 向两端扫描的策略，并利用优先队列维护最大值和最小值，代码简洁且高效。
   - **核心代码**：
     ```cpp
     priority_queue<int,vector<int>,greater<int>>b;
     priority_queue<int>a;
     int cnt = 0;
     for(int i=m;i>1;--i){
         cnt += s[i];
         a.push(s[i]);
         if(cnt>0){
             cnt -= a.top()*2;
             a.pop();
             ans++;
         }
     }
     cnt = 0;
     for(int i=m+1;i<=n;++i){
         cnt += s[i];
         b.push(s[i]);
         if(cnt<0){
             cnt -= b.top()*2;
             b.pop();
             ans++;
         }
     }
     ```
   - **个人心得**：通过倒序扫描和贪心策略，确保了每次操作的最优性，避免了复杂的枚举和计算。

2. **作者：abensyl (4星)**
   - **关键亮点**：详细解释了前缀和的性质，并提出了从 $m$ 向两端扫描的方法，利用优先队列维护最大值和最小值，代码可读性强。
   - **核心代码**：
     ```cpp
     priority_queue<int> pque;
     priority_queue<int,vector<int>,greater<int>> pqui;
     for(int i=m;i>1;--i) {
         if(i!=m) sum[i]=sum[i+1]+a[i];
         else sum[i]=a[i];
         pque.push(a[i]);
         if(sum[i]>0) {
             sum[i]-=pque.top()*2;
             pque.pop();
             res++;
         }
     }
     for(int i=m+1;i<=n;++i) {
         if(i!=m+1) sum[i]=sum[i-1]+a[i];
         else sum[i]=a[i];
         pqui.push(a[i]);
         if(sum[i]<0) {
             sum[i]-=pqui.top()*2;
             pqui.pop();
             res++;
         }
     }
     ```
   - **个人心得**：通过优先队列维护最大值和最小值，确保了每次操作的最优性，避免了复杂的枚举和计算。

3. **作者：jiangtaizhe001 (4星)**
   - **关键亮点**：简洁地分析了问题，提出了从 $m$ 向两端扫描的策略，并利用优先队列维护最大值和最小值，代码简洁且高效。
   - **核心代码**：
     ```cpp
     priority_queue<int> bi,EB;
     priority_queue<int,vector<int>,greater<int> > sm,ES;
     for(i=m;i>=2;i--){
         sum+=a[i]; bi.push(a[i]);
         while(sum>0) sum-=bi.top()*2,bi.pop(),ans++;
     }
     for(i=m+1;i<=n;i++){
         sum+=a[i]; sm.push(a[i]);
         while(sum<0) sum-=sm.top()*2,sm.pop(),ans++;
     }
     ```
   - **个人心得**：通过优先队列维护最大值和最小值，确保了每次操作的最优性，避免了复杂的枚举和计算。

### 最优关键思路
1. **贪心策略**：从 $m$ 向两端扫描，分别处理 $[1, m]$ 和 $[m+1, n]$ 区间，确保每个区间的前缀和满足条件。
2. **优先队列**：利用优先队列维护当前区间内的最大值或最小值，每次选择最优的元素进行取反操作。

### 可拓展之处
类似的问题可以通过贪心策略和优先队列来解决，例如在处理区间和或前缀和问题时，优先队列可以帮助我们快速找到最优解。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P3378 堆](https://www.luogu.com.cn/problem/P3378)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：62.15秒