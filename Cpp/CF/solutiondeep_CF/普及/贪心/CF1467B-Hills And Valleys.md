# 题目信息

# Hills And Valleys

## 题目描述

You are given a sequence of $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ . Let us call an index $ j $ ( $ 2 \le j \le {{n-1}} $ ) a hill if $ a_j > a_{{j+1}} $ and $ a_j > a_{{j-1}} $ ; and let us call it a valley if $ a_j < a_{{j+1}} $ and $ a_j < a_{{j-1}} $ .

Let us define the intimidation value of a sequence as the sum of the number of hills and the number of valleys in the sequence. You can change exactly one integer in the sequence to any number that you want, or let the sequence remain unchanged. What is the minimum intimidation value that you can achieve?

## 说明/提示

In the first test case, changing $ a_2 $ to $ 2 $ results in no hills and no valleys.

In the second test case, the best answer is just to leave the array as it is.

In the third test case, changing $ a_3 $ to $ 6 $ results in only one valley (at the index $ 5 $ ).

In the fourth test case, changing $ a_3 $ to $ 6 $ results in no hills and no valleys.

## 样例 #1

### 输入

```
4
3
1 5 3
5
2 2 2 2 2
6
1 6 2 5 2 10
5
1 6 2 5 1```

### 输出

```
0
0
1
0```

# AI分析结果

### 题目内容重写

#### 山峰与山谷

**题目描述**

给定一个由 $n$ 个整数组成的序列 $a_1, a_2, \ldots, a_n$。我们称一个索引 $j$（$2 \le j \le n-1$）为山峰，如果 $a_j > a_{j+1}$ 且 $a_j > a_{j-1}$；我们称它为山谷，如果 $a_j < a_{j+1}$ 且 $a_j < a_{j-1}$。

我们定义一个序列的“威慑值”为序列中山峰和山谷的总数。你可以将序列中的恰好一个整数修改为任意你想要的数，或者保持序列不变。你能达到的最小威慑值是多少？

**说明/提示**

在第一个测试用例中，将 $a_2$ 修改为 $2$ 后，序列中没有山峰和山谷。

在第二个测试用例中，最好的选择是保持数组不变。

在第三个测试用例中，将 $a_3$ 修改为 $6$ 后，只有一个山谷（在索引 $5$ 处）。

在第四个测试用例中，将 $a_3$ 修改为 $6$ 后，序列中没有山峰和山谷。

**样例 #1**

### 输入

```
4
3
1 5 3
5
2 2 2 2 2
6
1 6 2 5 2 10
5
1 6 2 5 1
```

### 输出

```
0
0
1
0
```

### 题解分析与结论

#### 综合分析

该题的核心思想是通过修改序列中的一个元素，使得序列中的山峰和山谷的数量最小化。各题解的思路基本一致，都是通过枚举每个元素，尝试将其修改为相邻元素的值，然后计算修改后的山峰和山谷数量，最终取最小值。

#### 最优关键思路

1. **枚举修改点**：遍历序列中的每个元素，尝试将其修改为左边或右边的值，计算修改后的山峰和山谷数量。
2. **局部影响**：修改一个元素只会影响其自身及其左右相邻元素的山峰和山谷状态，因此只需计算这三个位置的改变。
3. **贪心策略**：通过修改一个元素，使其与相邻元素相等，可以有效减少山峰和山谷的数量。

#### 评分较高的题解

1. **作者：CaiXY06 (赞：4)**
   - **星级**：4.5
   - **关键亮点**：通过定义 `hill` 和 `valley` 函数，清晰地区分了山峰和山谷的判断逻辑。使用 `work` 函数计算修改后的影响，代码结构清晰，逻辑严谨。
   - **代码核心**：
     ```cpp
     inline bool hill(int i){
         return i>1&&i<n&&a[i]>a[i-1]&&a[i]>a[i+1];
     }
     inline bool valley(int i){
         return i>1&&i<n&&a[i]<a[i-1]&&a[i]<a[i+1];
     }
     inline int work(int i,int j,int k){
         int res=0,cnt=0;
         res+=hill(i-1)||valley(i-1);
         res+=hill(i)||valley(i);
         res+=hill(i+1)||valley(i+1);
         a[i]=a[i+j];
         cnt+=hill(i-1)||valley(i-1);
         cnt+=hill(i)||valley(i);
         cnt+=hill(i+1)||valley(i+1);
         a[i]=k;
         return res-cnt;
     }
     ```

2. **作者：lndjy (赞：1)**
   - **星级**：4
   - **关键亮点**：通过 `gu` 和 `feng` 函数判断山谷和山峰，代码简洁明了。通过枚举每个元素修改为左右相邻元素的值，计算影响，逻辑清晰。
   - **代码核心**：
     ```cpp
     bool gu(int i){
         if(i==1||i==n) return 0;
         return (a[i-1]>a[i]&&a[i+1]>a[i]);
     }
     bool feng(int i){
         if(i==1||i==n) return 0;
         return (a[i-1]<a[i]&&a[i+1]<a[i]);
     }
     ```

3. **作者：断清秋 (赞：0)**
   - **星级**：4
   - **关键亮点**：通过 `flag` 数组标记山峰和山谷，代码结构清晰。通过枚举每个元素修改为左右相邻元素的值，计算影响，逻辑严谨。
   - **代码核心**：
     ```cpp
     for(ri i=2;i<=n-1;i++){
         if((a[i]>a[i+1]&&a[i]>a[i-1])||(a[i]<a[i+1]&&a[i]<a[i-1]))
             flag[i]=1,sum++;
     }
     ```

### 推荐题目

1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P1049 装箱问题](https://www.luogu.com.cn/problem/P1049)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

### 个人心得

- **调试经历**：在修改元素时，需要注意数组越界的问题，尤其是在处理第一个和最后一个元素时。
- **踩坑教训**：多组数据测试时，务必清空数组和变量，避免数据污染。
- **顿悟感想**：通过修改一个元素，使其与相邻元素相等，可以有效地减少山峰和山谷的数量，这是一种贪心策略的应用。

---
处理用时：43.38秒