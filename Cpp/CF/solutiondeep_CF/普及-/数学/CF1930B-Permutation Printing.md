# 题目信息

# Permutation Printing

## 题目描述

You are given a positive integer $ n $ .

Find a permutation $ ^\dagger $ $ p $ of length $ n $ such that there do not exist two distinct indices $ i $ and $ j $ ( $ 1 \leq i, j < n $ ; $ i \neq j $ ) such that $ p_i $ divides $ p_j $ and $ p_{i+1} $ divides $ p_{j+1} $ .

Refer to the Notes section for some examples.

Under the constraints of this problem, it can be proven that at least one $ p $ exists.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, $ p=[4,1,2,3] $ is a valid permutation. However, the permutation $ p=[1,2,3,4] $ is not a valid permutation as we can choose $ i=1 $ and $ j=3 $ . Then $ p_1=1 $ divides $ p_3=3 $ and $ p_2=2 $ divides $ p_4=4 $ . Note that the permutation $ p=[3, 4, 2, 1] $ is also not a valid permutation as we can choose $ i=3 $ and $ j=2 $ . Then $ p_3=2 $ divides $ p_2=4 $ and $ p_4=1 $ divides $ p_3=2 $ .

In the second test case, $ p=[1,2,3] $ is a valid permutation. In fact, all $ 6 $ permutations of length $ 3 $ are valid.

## 样例 #1

### 输入

```
2
4
3```

### 输出

```
4 1 2 3
1 2 3```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个正整数 $n$。

找到一个长度为 $n$ 的排列 $p$，使得不存在两个不同的索引 $i$ 和 $j$（$1 \leq i, j < n$；$i \neq j$），满足 $p_i$ 整除 $p_j$ 且 $p_{i+1}$ 整除 $p_{j+1}$。

在本题的约束下，可以证明至少存在一个满足条件的排列 $p$。

#### 说明/提示

在第一个测试用例中，$p=[4,1,2,3]$ 是一个有效的排列。然而，排列 $p=[1,2,3,4]$ 不是一个有效的排列，因为我们可以选择 $i=1$ 和 $j=3$，此时 $p_1=1$ 整除 $p_3=3$，且 $p_2=2$ 整除 $p_4=4$。注意，排列 $p=[3, 4, 2, 1]$ 也不是一个有效的排列，因为我们可以选择 $i=3$ 和 $j=2$，此时 $p_3=2$ 整除 $p_2=4$，且 $p_4=1$ 整除 $p_3=2$。

在第二个测试用例中，$p=[1,2,3]$ 是一个有效的排列。事实上，所有长度为 $3$ 的排列都是有效的。

#### 样例 #1

##### 输入

```
2
4
3
```

##### 输出

```
4 1 2 3
1 2 3
```

### 题解分析与结论

#### 综合分析与结论

本题的核心在于构造一个排列，使得不存在两个不同的索引 $i$ 和 $j$，满足 $p_i$ 整除 $p_j$ 且 $p_{i+1}$ 整除 $p_{j+1}$。通过分析，可以发现一个有效的构造方法是让奇数位上的数递增，偶数位上的数递减。这样，当 $p_i < p_j$ 时，$p_{i+1} > p_{j+1}$，从而避免了 $p_i$ 整除 $p_j$ 且 $p_{i+1}$ 整除 $p_{j+1}$ 的情况。

#### 所选高分题解

1. **作者：Kawaii_qiuw (赞：5)**

   - **星级：5星**
   - **关键亮点：** 思路清晰，代码简洁，直接通过交替输出递增和递减的数来构造排列。
   - **核心代码：**
     ```cpp
     int l = 1, r = n;
     while(l <= r)
     {
         printf("%d ", l);
         l++;
         if(l > r)	break;
         printf("%d ", r);
         r--;
     }
     ```
   - **个人心得：** 通过让奇数位上的数递增，偶数位上的数递减，可以有效地避免整除关系。

2. **作者：__zyq_666_kpzc__ (赞：2)**

   - **星级：4星**
   - **关键亮点：** 通过构造数列满足 $a_i < a_j$ 且 $a_{i+1} > a_{j+1}$，确保不出现整除关系。
   - **核心代码：**
     ```cpp
     l=1,r=n,m=0;
     while(l<=r){
         l++;
         a[++m]=l;
         if(l<r){
             a[++m]=r;
             r--;
         }
     }
     ```
   - **个人心得：** 通过交替插入递增和递减的数，可以有效地避免整除关系。

3. **作者：joker_opof_qaq (赞：2)**

   - **星级：4星**
   - **关键亮点：** 通过让奇数位递增，偶数位递减，确保不出现整除关系。
   - **核心代码：**
     ```cpp
     int l=1,r=read();
     while(l<=r){
         cout<<l++<<" ";
         if(l<=r)cout<<r--<<" ";
     }
     ```
   - **个人心得：** 通过交替输出递增和递减的数，可以有效地避免整除关系。

### 最优关键思路或技巧

- **交替输出递增和递减的数：** 通过让奇数位上的数递增，偶数位上的数递减，可以有效地避免 $p_i$ 整除 $p_j$ 且 $p_{i+1}$ 整除 $p_{j+1}$ 的情况。
- **简单构造法：** 通过交替输出递增和递减的数，可以快速构造出满足条件的排列。

### 可拓展之处

- **类似题目：** 可以拓展到其他需要构造特定排列的题目，如构造一个排列使得相邻元素的差值为特定值等。
- **算法套路：** 交替输出递增和递减的数是一种常见的构造排列的方法，可以应用于其他需要构造特定排列的题目。

### 推荐题目

1. **洛谷 P1008 三连击** - 构造一个三位数的排列，使得三个数的比例为1:2:3。
2. **洛谷 P1012 拼数** - 构造一个排列，使得拼接后的数最大。
3. **洛谷 P1019 单词接龙** - 构造一个排列，使得相邻单词可以接龙。

### 个人心得总结

- **调试经历：** 通过交替输出递增和递减的数，可以有效地避免整除关系，调试时需要注意边界条件。
- **踩坑教训：** 在构造排列时，需要注意不重复输出同一个数，避免死循环。
- **顿悟感想：** 通过交替输出递增和递减的数，可以快速构造出满足条件的排列，这种方法简单且有效。

---
处理用时：46.60秒