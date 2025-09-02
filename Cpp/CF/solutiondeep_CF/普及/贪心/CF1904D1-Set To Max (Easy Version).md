# 题目信息

# Set To Max (Easy Version)

## 题目描述

This is the easy version of the problem. The only differences between the two versions of this problem are the constraints on $ n $ and the time limit. You can make hacks only if all versions of the problem are solved.

You are given two arrays $ a $ and $ b $ of length $ n $ .

You can perform the following operation some (possibly zero) times:

1. choose $ l $ and $ r $ such that $ 1 \leq l \leq r \leq n $ .
2. let $ x=\max(a_l,a_{l+1},\ldots,a_r) $ .
3. for all $ l \leq i \leq r $ , set $ a_i := x $ .

Determine if you can make array $ a $ equal to array $ b $ .

## 说明/提示

In the first test case, we can achieve array $ b $ by applying a single operation: $ (l,r)=(2,3) $ .

In the second test case, it can be shown we cannot achieve array $ b $ in any amount of operations.

In the third test case, we can achieve array $ b $ by applying two operations: $ (l,r)=(2,5) $ . followed by $ (l,r)=(1,3) $ .

In the fourth and fifth test cases, it can be shown we cannot achieve array $ b $ in any amount of operations.

## 样例 #1

### 输入

```
5
5
1 2 3 2 4
1 3 3 2 4
5
3 4 2 2 4
3 4 3 4 4
5
3 2 1 1 1
3 3 3 2 2
2
1 1
1 2
3
1 1 2
2 1 2```

### 输出

```
YES
NO
YES
NO
NO```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

这是该问题的简单版本。两个版本之间的唯一区别在于 $n$ 的约束和时间限制。只有在解决了所有版本的问题后，你才能进行 hack。

给定两个长度为 $n$ 的数组 $a$ 和 $b$。

你可以执行以下操作若干次（可能为零次）：

1. 选择 $l$ 和 $r$，使得 $1 \leq l \leq r \leq n$。
2. 令 $x=\max(a_l,a_{l+1},\ldots,a_r)$。
3. 对于所有 $l \leq i \leq r$，将 $a_i$ 赋值为 $x$。

确定是否可以通过这些操作使数组 $a$ 等于数组 $b$。

#### 说明/提示

在第一个测试用例中，我们可以通过一次操作实现数组 $b$：$(l,r)=(2,3)$。

在第二个测试用例中，可以证明我们无法通过任何操作实现数组 $b$。

在第三个测试用例中，我们可以通过两次操作实现数组 $b$：$(l,r)=(2,5)$，然后 $(l,r)=(1,3)$。

在第四个和第五个测试用例中，可以证明我们无法通过任何操作实现数组 $b$。

#### 样例 #1

##### 输入

```
5
5
1 2 3 2 4
1 3 3 2 4
5
3 4 2 2 4
3 4 3 4 4
5
3 2 1 1 1
3 3 3 2 2
2
1 1
1 2
3
1 1 2
2 1 2
```

##### 输出

```
YES
NO
YES
NO
NO
```

---

### 题解分析与结论

#### 综合分析

本题的核心问题是通过区间操作将数组 $a$ 转换为数组 $b$。操作的本质是将区间内的所有元素赋值为该区间的最大值。因此，我们需要判断是否可以通过一系列这样的操作使 $a$ 与 $b$ 相等。

**关键点：**
1. **无解条件**：如果存在某个位置 $i$，使得 $a_i > b_i$，则无解，因为操作只能使元素变大，不能变小。
2. **有解条件**：对于 $a_i < b_i$ 的情况，需要找到一个区间 $[l, r]$，使得该区间的最大值为 $b_i$，并且在该区间内没有元素大于 $b_i$，且区间内的所有 $b_j$ 都大于等于 $b_i$。

**难点：**
- 如何高效地找到满足条件的区间。
- 如何处理多个操作之间的相互影响。

#### 题解评分与亮点

1. **题解作者：CuteChat (赞：7)**
   - **评分：4星**
   - **亮点**：详细解释了无解条件，并通过左右拓展的方式寻找满足条件的区间。代码实现清晰，逻辑严谨。
   - **代码核心思想**：对于每个 $i$，分别向左和向右寻找等于 $b_i$ 的元素，并检查区间内的最大值和 $b_j$ 是否满足条件。
   - **代码片段**：
     ```cpp
     for (int i = 1; i <= n; ++i) {
         if (a[i] > b[i]) { 
             return puts("NO"), void(); 
         } else if (a[i] < b[i]) {
             bool ok = 0;
             for (int r = i + 1; r <= n; ++r) {
                 if (a[r] == b[i]) { 
                     ok = 1;
                     break;
                 }
                 if (a[r] > b[i] || b[i] > b[r]) break; 
             }
             if (ok) continue;
             ok = 0;
             for (int l = i; l >= 1; --l) {
                 if (a[l] == b[i]) { 
                     ok = 1;
                     break;
                 }
                 if (a[l] > b[i] || b[i] > b[l]) break; 
             }
             if (ok) continue;
             return puts("NO"), void(); 
         }
     }
     puts("YES");
     ```

2. **题解作者：Genius_Star (赞：0)**
   - **评分：4星**
   - **亮点**：使用 ST 表维护区间最大最小值，优化了查找效率。思路清晰，代码结构良好。
   - **代码核心思想**：通过 ST 表快速查询区间最大最小值，判断是否存在满足条件的区间。
   - **代码片段**：
     ```cpp
     inline int askmax(int l, int r){
         int k = log2(r - l + 1);
         return max(F[0][k][l], F[0][k][r - (1 << k) + 1]);
     }
     inline int askmin(int l, int r){
         int k = log2(r - l + 1);
         return min(F[1][k][l], F[1][k][r - (1 << k) + 1]);
     }
     ```

3. **题解作者：sordio (赞：0)**
   - **评分：4星**
   - **亮点**：通过从小到大处理 $b_i$，避免了操作之间的相互影响。思路清晰，代码简洁。
   - **代码核心思想**：对于每个 $i$，分别向左和向右寻找等于 $b_i$ 的元素，并检查区间内的最大值和 $b_j$ 是否满足条件。
   - **代码片段**：
     ```cpp
     bool left(int x){ 
         for(int i=x;i>=1;i--){
             if(a[i]>b[x]||b[x]>b[i]) return 0; 
             if(a[i]==b[x]) return 1; 
         }
         return 0; 
     }
     bool right(int x){ 
         for(int i=x;i<=n;i++){
             if(a[i]>b[x]||b[x]>b[i]) return 0;
             if(a[i]==b[x]) return 1;
         }
         return 0;
     }
     ```

#### 最优关键思路与技巧

1. **无解条件**：首先检查是否存在 $a_i > b_i$，若存在则直接输出 `NO`。
2. **区间查找**：对于 $a_i < b_i$ 的情况，分别向左和向右查找等于 $b_i$ 的元素，并检查区间内的最大值和 $b_j$ 是否满足条件。
3. **优化查找**：使用 ST 表等数据结构优化区间最大最小值的查询效率。

#### 拓展思路

- **类似问题**：可以通过区间操作将数组 $a$ 转换为数组 $b$ 的问题，通常需要考虑操作的性质（如只能变大或变小）以及操作之间的相互影响。
- **数据结构优化**：在处理区间查询问题时，可以考虑使用 ST 表、线段树等数据结构来优化查询效率。

#### 推荐题目

1. [P1904 区间最大值](https://www.luogu.com.cn/problem/P1904)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)

#### 个人心得

- **调试经历**：在处理区间操作时，容易忽略操作之间的相互影响，导致错误。建议在编写代码时，仔细考虑每个操作对后续操作的影响。
- **顿悟感想**：通过从小到大处理 $b_i$，可以避免操作之间的相互影响，这是一个非常巧妙的思路。

---
处理用时：56.36秒