# 题目信息

# Merge Not Sort

## 题目描述

You are currently researching the Merge Sort algorithm. Merge Sort is a sorting algorithm that is based on the principle of Divide and Conquer. It works by dividing an array into two subarrays of equal length, sorting each subarrays, then merging the sorted subarrays back together to form the final sorted array.

You are particularly interested in the merging routine. Common merge implementation will combine two subarrays by iteratively comparing their first elements, and move the smaller one to a new merged array. More precisely, the merge algorithm can be presented by the following pseudocode.

```
<pre class="verbatim"><br></br>    Merge(A[1..N], B[1..N]):<br></br>        C = []<br></br>        i = 1<br></br>        j = 1<br></br>        while i <= N AND j <= N:<br></br>            if A[i] < B[j]:<br></br>                append A[i] to C<br></br>                i = i + 1<br></br>            else:<br></br>                append B[j] to C<br></br>                j = j + 1 <br></br>        while i <= N:<br></br>            append A[i] to C<br></br>            i = i + 1 <br></br>        while j <= N:<br></br>            append B[j] to C<br></br>            j = j + 1 <br></br>        return C<br></br>
```

During your research, you are keen to understand the behaviour of the merge algorithm when arrays $ A $ and $ B $ are not necessarily sorted. For example, if $ A = [3, 1, 6] $ and $ B = [4, 5, 2] $ , then $ \text{Merge}(A, B) = [3, 1, 4, 5, 2, 6] $ .

To further increase the understanding of the merge algorithm, you decided to work on the following problem. You are given an array $ C $ of length $ 2 \cdot N $ such that it is a permutation of $ 1 $ to $ 2 \cdot N $ . Construct any two arrays $ A $ and $ B $ of the same length $ N $ , such that $ \text{Merge}(A, B) = C $ , or determine if it is impossible to do so.

## 说明/提示

Explanation for the sample input/output #1

The solution $ A = [3, 1, 4] $ and $ B = [5, 2, 6] $ is also correct.

Explanation for the sample input/output #2

The solution $ A = [1, 2, 3, 4] $ and $ B = [5, 6, 7, 8] $ is also correct.

## 样例 #1

### 输入

```
3
3 1 4 5 2 6```

### 输出

```
3 1 6
4 5 2```

## 样例 #2

### 输入

```
4
1 2 3 4 5 6 7 8```

### 输出

```
2 3 5 7
1 4 6 8```

## 样例 #3

### 输入

```
2
4 3 2 1```

### 输出

```
-1```

# AI分析结果

### 题目内容翻译

# 合并但不排序

## 题目描述

你正在研究归并排序算法。归并排序是一种基于分治原则的排序算法。它通过将数组分成两个长度相等的子数组，分别对每个子数组进行排序，然后将排序后的子数组合并回最终的有序数组。

你对合并过程特别感兴趣。常见的合并实现会通过迭代比较两个子数组的第一个元素，并将较小的一个移动到新的合并数组中。更准确地说，合并算法可以用以下伪代码表示。

```
<pre class="verbatim"><br></br>    Merge(A[1..N], B[1..N]):<br></br>        C = []<br></br>        i = 1<br></br>        j = 1<br></br>        while i <= N AND j <= N:<br></br>            if A[i] < B[j]:<br></br>                append A[i] to C<br></br>                i = i + 1<br></br>            else:<br></br>                append B[j] to C<br></br>                j = j + 1 <br></br>        while i <= N:<br></br>            append A[i] to C<br></br>            i = i + 1 <br></br>        while j <= N:<br></br>            append B[j] to C<br></br>            j = j + 1 <br></br>        return C<br></br>
```

在你的研究中，你特别想了解当数组 $ A $ 和 $ B $ 不一定有序时，合并算法的行为。例如，如果 $ A = [3, 1, 6] $ 和 $ B = [4, 5, 2] $ ，那么 $ \text{Merge}(A, B) = [3, 1, 4, 5, 2, 6] $ 。

为了进一步理解合并算法，你决定解决以下问题。给定一个长度为 $ 2 \cdot N $ 的数组 $ C $ ，它是 $ 1 $ 到 $ 2 \cdot N $ 的一个排列。构造任意两个长度均为 $ N $ 的数组 $ A $ 和 $ B $ ，使得 $ \text{Merge}(A, B) = C $ ，或者确定是否不可能做到。

## 说明/提示

样例输入/输出 #1 的解释

解 $ A = [3, 1, 4] $ 和 $ B = [5, 2, 6] $ 也是正确的。

样例输入/输出 #2 的解释

解 $ A = [1, 2, 3, 4] $ 和 $ B = [5, 6, 7, 8] $ 也是正确的。

## 样例 #1

### 输入

```
3
3 1 4 5 2 6```

### 输出

```
3 1 6
4 5 2```

## 样例 #2

### 输入

```
4
1 2 3 4 5 6 7 8```

### 输出

```
2 3 5 7
1 4 6 8```

## 样例 #3

### 输入

```
2
4 3 2 1```

### 输出

```
-1```

### 算法分类
构造、动态规划

### 题解分析与结论

1. **FFTotoro的题解**：通过将数组划分为多个“块”，每个块的第一个元素小于下一个块的第一个元素。然后使用背包DP来判断是否可以将这些块分配到两个数组中，使得每个数组的长度为N。思路清晰，代码实现较为复杂，但逻辑严谨。
2. **Xiphi的题解**：从大到小考虑，将数组划分为多个“固定段”，然后使用背包DP来判断是否可以将这些段分配到两个数组中。思路较为直观，但实现中使用了记忆化搜索，代码可读性一般。
3. **xyz105的题解**：参考了官方题解，通过将数组划分为多个连续段，要求每个段的第一个数小于下一个段的第一个数。然后使用背包DP来判断是否可以将这些段分配到两个数组中。思路清晰，代码简洁，实现较为高效。

### 评分较高的题解

1. **FFTotoro的题解**（4星）
   - 关键亮点：通过划分“块”并使用背包DP来解决问题，思路清晰，逻辑严谨。
   - 代码实现：使用`std::set`来构造方案，代码较为复杂但逻辑清晰。

   ```cpp
   vector<set<int> > f(n+1);
   for(int j=0;j<w.size();j++)
     for(int i=n-1;~i;i--)
       if(!i||!f[i].empty()){
         if(i+w[j].size()<=n&&f[i+w[j].size()].empty()){
           for(int k:f[i])f[i+w[j].size()].emplace(k);
           f[i+w[j].size()].emplace(j);
         }
       }
   ```

2. **xyz105的题解**（4星）
   - 关键亮点：通过划分连续段并使用背包DP来解决问题，思路清晰，代码简洁。
   - 代码实现：使用`pre`数组记录方案，代码实现高效。

   ```cpp
   ok[0] = 1;
   for (int i = 1; i <= b_cnt; i++)
     for (int j = 2 * n; j >= b[i]; j--)
       if (!ok[j] && ok[j - b[i]]) ok[j] = 1, pre[j] = i;
   ```

### 最优关键思路或技巧

- **划分块/段**：将数组划分为多个块或段，每个块的第一个元素小于下一个块的第一个元素，这是解决问题的关键。
- **背包DP**：使用背包DP来判断是否可以将这些块或段分配到两个数组中，使得每个数组的长度为N。

### 可拓展之处

- 类似的问题可以扩展到其他合并算法或分治算法的逆向问题，如快速排序的分区过程。
- 可以考虑将问题扩展到多维数组或更复杂的合并规则。

### 推荐题目

1. [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)
2. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：51.83秒