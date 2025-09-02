# 题目信息

# Dances (Easy version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version $ m = 1 $ .

You are given two arrays of integers $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ . Before applying any operations, you can reorder the elements of each array as you wish. Then, in one operation, you will perform both of the following actions, if the arrays are not empty:

- Choose any element from array $ a $ and remove it (all remaining elements are shifted to a new array $ a $ ),
- Choose any element from array $ b $ and remove it (all remaining elements are shifted to a new array $ b $ ).

Let $ k $ be the final size of both arrays. You need to find the minimum number of operations required to satisfy $ a_i < b_i $ for all $ 1 \leq i \leq k $ .

This problem was too easy, so the problem author decided to make it more challenging. You are also given a positive integer $ m $ . Now, you need to find the sum of answers to the problem for $ m $ pairs of arrays $ (c[i], b) $ , where $ 1 \leq i \leq m $ . Array $ c[i] $ is obtained from $ a $ as follows:

- $ c[i]_1 = i $ ,
- $ c[i]_j = a_j $ , for $ 2 \leq j \leq n $ .

## 说明/提示

In the first test case for the pair of arrays $ ([1, 1], [3, 2]) $ , the answer is $ 0 $ . No operations or reordering of elements are needed.

## 样例 #1

### 输入

```
4
2 1
1
3 2
4 1
5 1 5
3 8 3 3
8 1
4 3 3 2 2 1 1
1 1 1 1 3 3 3 3
9 1
9 2 8 3 7 4 6 5
1 2 3 2 1 4 5 6 5```

### 输出

```
0
1
4
4```

# AI分析结果

### 题目内容重写

#### 题目描述

这是问题的简单版本，唯一的区别是在这个版本中 $m = 1$。

给定两个整数数组 $a_1, a_2, \ldots, a_n$ 和 $b_1, b_2, \ldots, b_n$。在应用任何操作之前，你可以重新排列每个数组的元素。然后，在一个操作中，如果数组不为空，你将执行以下两个动作：

- 从数组 $a$ 中选择任意一个元素并将其移除（所有剩余元素被移动到新的数组 $a$），
- 从数组 $b$ 中选择任意一个元素并将其移除（所有剩余元素被移动到新的数组 $b$）。

设 $k$ 为最终两个数组的大小。你需要找到满足 $a_i < b_i$ 对于所有 $1 \leq i \leq k$ 所需的最少操作数。

这个问题太简单了，所以问题作者决定使其更具挑战性。你还被给定一个正整数 $m$。现在，你需要找到对于 $m$ 对数组 $(c[i], b)$ 的问题答案的总和，其中 $1 \leq i \leq m$。数组 $c[i]$ 从 $a$ 获得如下：

- $c[i]_1 = i$，
- $c[i]_j = a_j$，对于 $2 \leq j \leq n$。

#### 说明/提示

在第一个测试用例中，对于数组对 $([1, 1], [3, 2])$，答案是 $0$。不需要任何操作或重新排列元素。

#### 样例 #1

##### 输入

```
4
2 1
1
3 2
4 1
5 1 5
3 8 3 3
8 1
4 3 3 2 2 1 1
1 1 1 1 3 3 3 3
9 1
9 2 8 3 7 4 6 5
1 2 3 2 1 4 5 6 5
```

##### 输出

```
0
1
4
4
```

### 算法分类
贪心、二分

### 题解分析与结论

#### 综合分析与结论

本题的核心在于通过贪心策略和二分搜索来找到最小的操作数，使得在删除部分元素后，剩下的数组满足 $a_i < b_i$。大多数题解都采用了以下思路：

1. **排序**：首先对数组 $a$ 和 $b$ 进行排序，以便更容易进行匹配。
2. **贪心匹配**：通过贪心策略，尽可能多地匹配 $a$ 和 $b$ 中的元素，使得 $a_i < b_i$。
3. **二分搜索**：利用二分搜索来确定最大的 $k$，使得在删除 $n-k$ 个元素后，剩下的元素满足条件。

#### 高星题解推荐

1. **作者：FFTotoro (赞：7)**
   - **星级：5星**
   - **关键亮点**：通过二分搜索和贪心策略，代码简洁且高效，时间复杂度为 $O(n \log n)$。
   - **核心代码**：
     ```cpp
     auto pd=[&](int x){
       vector<int> p,q;
       for(int i=0;i<x;i++)
         p.emplace_back(a[i]);
       for(int i=n-x;i<n;i++)
         q.emplace_back(b[i]);
       for(int i=0;i<x;i++)
         if(p[i]>=q[i])return false;
       return true;
     };
     while(l<r){
       int m=l+r+1>>1;
       if(pd(m))l=m;
       else r=m-1;
     }
     cout<<n-l<<endl;
     ```

2. **作者：One_JuRuo (赞：2)**
   - **星级：4星**
   - **关键亮点**：采用双指针进行贪心匹配，时间复杂度为 $O(n \log n)$，代码清晰易懂。
   - **核心代码**：
     ```cpp
     int j=n;
     for(int i=n;i>=1;--i){
       while(j>1&&a[j]>=b[i]) --j;
       if(j==1&&a[j]>=b[i]){ans=n-i;break;}
       else if(j==1&&a[j]<b[i]){ans=n-i+1;break;}
       --j;
     }
     printf("%d\n",n-ans);
     ```

3. **作者：pyz51 (赞：1)**
   - **星级：4星**
   - **关键亮点**：通过二分搜索和贪心策略，代码结构清晰，时间复杂度为 $O(n \log n)$。
   - **核心代码**：
     ```cpp
     bool check(int mid){
       for(int i=1;i<=n-mid;i++) if(a[i]>=b[i+mid]) return 0;
       return 1;
     }
     while(l<r){
       int mid=l+r>>1;
       if(check(mid)) r=mid;
       else l=mid+1;
     }
     cout<<l<<'\n';
     ```

### 最优关键思路或技巧

1. **排序与贪心匹配**：通过排序数组，可以更容易地进行贪心匹配，确保 $a_i < b_i$。
2. **二分搜索**：利用二分搜索来确定最大的 $k$，使得在删除 $n-k$ 个元素后，剩下的元素满足条件。

### 可拓展之处

1. **类似问题**：可以扩展到多个数组的匹配问题，或者在不同约束条件下的匹配问题。
2. **算法优化**：可以考虑更高效的匹配算法，或者在其他数据结构上的应用。

### 推荐题目

1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
3. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)

### 个人心得摘录

- **FFTotoro**：通过二分搜索和贪心策略，代码简洁且高效，时间复杂度为 $O(n \log n)$。
- **One_JuRuo**：采用双指针进行贪心匹配，代码清晰易懂，时间复杂度为 $O(n \log n)$。
- **pyz51**：通过二分搜索和贪心策略，代码结构清晰，时间复杂度为 $O(n \log n)$。

---
处理用时：39.40秒