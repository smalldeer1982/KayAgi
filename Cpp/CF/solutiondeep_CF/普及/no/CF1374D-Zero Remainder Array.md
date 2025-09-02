# 题目信息

# Zero Remainder Array

## 题目描述

You are given an array $ a $ consisting of $ n $ positive integers.

Initially, you have an integer $ x = 0 $ . During one move, you can do one of the following two operations:

1. Choose exactly one $ i $ from $ 1 $ to $ n $ and increase $ a_i $ by $ x $ ( $ a_i := a_i + x $ ), then increase $ x $ by $ 1 $ ( $ x := x + 1 $ ).
2. Just increase $ x $ by $ 1 $ ( $ x := x + 1 $ ).

The first operation can be applied no more than once to each $ i $ from $ 1 $ to $ n $ .

Your task is to find the minimum number of moves required to obtain such an array that each its element is divisible by $ k $ (the value $ k $ is given).

You have to answer $ t $ independent test cases.

## 说明/提示

Consider the first test case of the example:

1. $ x=0 $ , $ a = [1, 2, 1, 3] $ . Just increase $ x $ ;
2. $ x=1 $ , $ a = [1, 2, 1, 3] $ . Add $ x $ to the second element and increase $ x $ ;
3. $ x=2 $ , $ a = [1, 3, 1, 3] $ . Add $ x $ to the third element and increase $ x $ ;
4. $ x=3 $ , $ a = [1, 3, 3, 3] $ . Add $ x $ to the fourth element and increase $ x $ ;
5. $ x=4 $ , $ a = [1, 3, 3, 6] $ . Just increase $ x $ ;
6. $ x=5 $ , $ a = [1, 3, 3, 6] $ . Add $ x $ to the first element and increase $ x $ ;
7. $ x=6 $ , $ a = [6, 3, 3, 6] $ . We obtained the required array.

 Note that you can't add $ x $ to the same element more than once.

## 样例 #1

### 输入

```
5
4 3
1 2 1 3
10 6
8 7 1 8 3 7 5 10 8 9
5 10
20 100 50 20 100500
10 25
24 24 24 24 24 24 24 24 24 24
8 8
1 2 3 4 5 6 7 8```

### 输出

```
6
18
0
227
8```

# AI分析结果

### 题目内容
# Zero Remainder Array

## 题目描述

给定一个由 $n$ 个正整数组成的数组 $a$。

初始时，你有一个整数 $x = 0$。在每次操作中，你可以执行以下两种操作之一：

1. 选择 $1$ 到 $n$ 中的一个 $i$，将 $a_i$ 增加 $x$（即 $a_i := a_i + x$），然后将 $x$ 增加 $1$（即 $x := x + 1$）。
2. 仅将 $x$ 增加 $1$（即 $x := x + 1$）。

第一种操作对每个 $i$ 最多只能执行一次。

你的任务是找到使数组中的每个元素都能被 $k$ 整除所需的最小操作次数。

你需要回答 $t$ 个独立的测试用例。

## 说明/提示

考虑第一个测试用例的示例：

1. $x=0$，$a = [1, 2, 1, 3]$。仅增加 $x$；
2. $x=1$，$a = [1, 2, 1, 3]$。将 $x$ 加到第二个元素并增加 $x$；
3. $x=2$，$a = [1, 3, 1, 3]$。将 $x$ 加到第三个元素并增加 $x$；
4. $x=3$，$a = [1, 3, 3, 3]$。将 $x$ 加到第四个元素并增加 $x$；
5. $x=4$，$a = [1, 3, 3, 6]$。仅增加 $x$；
6. $x=5$，$a = [1, 3, 3, 6]$。将 $x$ 加到第一个元素并增加 $x$；
7. $x=6$，$a = [6, 3, 3, 6]$。我们得到了所需的数组。

注意，你不能对同一个元素多次增加 $x$。

## 样例 #1

### 输入

```
5
4 3
1 2 1 3
10 6
8 7 1 8 3 7 5 10 8 9
5 10
20 100 50 20 100500
10 25
24 24 24 24 24 24 24 24 24 24
8 8
1 2 3 4 5 6 7 8```

### 输出

```
6
18
0
227
8```

### 算法分类
贪心

### 题解分析与结论
该题的核心在于如何通过最少的操作次数使得数组中的每个元素都能被 $k$ 整除。由于每次操作只能对一个元素进行一次增加操作，因此需要合理安排增加的顺序，使得 $x$ 的增加能够覆盖所有需要增加的元素。

### 所选题解
1. **作者：Blunt_Feeling (赞：6)**  
   - **星级：5**  
   - **关键亮点**：使用集合 `set` 去重，并通过 `upper_bound` 和 `lower_bound` 计算每个余数出现的次数，最后通过等差数列的末项公式计算最大操作次数。  
   - **个人心得**：通过去重和排序，简化了问题的处理，思路清晰，代码可读性强。  
   - **核心代码**：
     ```cpp
     for(set<int>::iterator it=st.begin();it!=st.end();it++) {
         if(*it==0) continue;
         int num=(upper_bound(a+1,a+n+1,*it)-lower_bound(a+1,a+n+1,*it));
         ans=max(ans,k-*it+(num-1)*k+1);
     }
     ```

2. **作者：45dino (赞：2)**  
   - **星级：4**  
   - **关键亮点**：通过 `map` 记录每个余数出现的次数，并根据次数计算最大操作次数，代码简洁明了。  
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++) {
         if(a[i]%k==0) continue;
         num[k-a[i]%k]++;
         if(num[k-a[i]%k]==maxx)
             ans=max(ans,k-a[i]%k);
         if(num[k-a[i]%k]>maxx) {
             maxx=num[k-a[i]%k];
             ans=k-a[i]%k;
         }
     }
     ```

3. **作者：PanH (赞：0)**  
   - **星级：4**  
   - **关键亮点**：通过 `map` 记录每个余数出现的次数，并根据次数计算最大操作次数，代码简洁明了。  
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++) {
         x%=k;
         if(x==0) continue;
         p[x]++;
         ans=max(ans,p[x]*k-x);
     }
     ```

### 最优关键思路或技巧
1. **余数处理**：将数组中的每个元素对 $k$ 取模，得到余数，然后根据余数计算需要增加的值。
2. **去重与排序**：通过集合 `set` 或 `map` 去重，并排序，简化问题处理。
3. **等差数列计算**：通过等差数列的末项公式计算最大操作次数，确保覆盖所有需要增加的元素。

### 可拓展之处
该题的思路可以拓展到其他需要合理安排操作顺序的问题，如任务调度、资源分配等。类似的问题可以通过贪心算法和数学计算来优化操作顺序。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：38.33秒