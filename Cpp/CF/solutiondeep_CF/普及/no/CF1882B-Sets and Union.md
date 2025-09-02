# 题目信息

# Sets and Union

## 题目描述

You have $ n $ sets of integers $ S_{1}, S_{2}, \ldots, S_{n} $ . We call a set $ S $ attainable, if it is possible to choose some (possibly, none) of the sets $ S_{1}, S_{2}, \ldots, S_{n} $ so that $ S $ is equal to their union $ ^{\dagger} $ . If you choose none of $ S_{1}, S_{2}, \ldots, S_{n} $ , their union is an empty set.

Find the maximum number of elements in an attainable $ S $ such that $ S \neq S_{1} \cup S_{2} \cup \ldots \cup S_{n} $ .

 $ ^{\dagger} $ The union of sets $ A_1, A_2, \ldots, A_k $ is defined as the set of elements present in at least one of these sets. It is denoted by $ A_1 \cup A_2 \cup \ldots \cup A_k $ . For example, $ \{2, 4, 6\} \cup \{2, 3\} \cup \{3, 6, 7\} = \{2, 3, 4, 6, 7\} $ .

## 说明/提示

In the first test case, $ S = S_{1} \cup S_{3} = \{1, 2, 3, 4\} $ is the largest attainable set not equal to $ S_1 \cup S_2 \cup S_3 = \{1, 2, 3, 4, 5\} $ .

In the second test case, we can pick $ S = S_{2} \cup S_{3} \cup S_{4} = \{2, 3, 4, 5, 6\} $ .

In the third test case, we can pick $ S = S_{2} \cup S_{5} = S_{2} \cup S_{3} \cup S_{5} = \{3, 5, 6, 8, 9, 10\} $ .

In the fourth test case, the only attainable set is $ S = \varnothing $ .

## 样例 #1

### 输入

```
4
3
3 1 2 3
2 4 5
2 3 4
4
4 1 2 3 4
3 2 5 6
3 3 5 6
3 4 5 6
5
1 1
3 3 6 10
1 9
2 1 3
3 5 8 9
1
2 4 28```

### 输出

```
4
5
6
0```

# AI分析结果

【题目翻译】
# 集合与并集

## 题目描述

你有 $n$ 个整数集合 $S_{1}, S_{2}, \ldots, S_{n}$。我们称一个集合 $S$ 为可达的，如果可以选择一些（可能为空）集合 $S_{1}, S_{2}, \ldots, S_{n}$，使得 $S$ 等于它们的并集 $^{\dagger}$。如果你不选择任何集合 $S_{1}, S_{2}, \ldots, S_{n}$，它们的并集为空集。

找到一个可达的集合 $S$，使得 $S \neq S_{1} \cup S_{2} \cup \ldots \cup S_{n}$，并且 $S$ 的元素个数最大。

 $^{\dagger}$ 集合 $A_1, A_2, \ldots, A_k$ 的并集定义为至少出现在其中一个集合中的元素集合。例如，$ \{2, 4, 6\} \cup \{2, 3\} \cup \{3, 6, 7\} = \{2, 3, 4, 6, 7\} $。

## 说明/提示

在第一个测试用例中，$ S = S_{1} \cup S_{3} = \{1, 2, 3, 4\} $ 是最大的可达集合，且不等于 $ S_1 \cup S_2 \cup S_3 = \{1, 2, 3, 4, 5\} $。

在第二个测试用例中，我们可以选择 $ S = S_{2} \cup S_{3} \cup S_{4} = \{2, 3, 4, 5, 6\} $。

在第三个测试用例中，我们可以选择 $ S = S_{2} \cup S_{5} = S_{2} \cup S_{3} \cup S_{5} = \{3, 5, 6, 8, 9, 10\} $。

在第四个测试用例中，唯一可达的集合是 $ S = \varnothing $。

【算法分类】
枚举

【题解分析与结论】
该题的核心思路是通过枚举某个元素，强制不选择包含该元素的集合，然后计算剩余集合的并集大小，取最大值。由于数据范围较小（$n \leq 50$，元素 $\leq 50$），可以直接暴力枚举。

【评分较高的题解】

1. **作者：Nuclear_Fish_cyq (5星)**
   - **关键亮点**：思路清晰，代码简洁，使用了布尔数组来记录集合中元素的存在情况，避免了复杂的数据结构。
   - **代码核心思想**：枚举每个元素，计算不包含该元素的集合的并集大小，取最大值。
   ```cpp
   for(int i = 0; i <= 50; i++){
       if(!app[i]) continue;
       cnt = 0;
       for(int j = 0; j <= 50; j++) flag[j] = false;
       for(int j = 0; j < n; j++){
           if(!a[j][i]){
               for(int k = 0; k <= 50; k++){
                   if(!flag[k] && a[j][k]){
                       cnt++;
                       flag[k] = true;
                   }
               }
           }
       }
       ans = max(ans, cnt);
   }
   ```

2. **作者：lfxxx (4星)**
   - **关键亮点**：使用了 `bitset` 来压缩集合的表示，优化了空间复杂度，代码简洁高效。
   - **代码核心思想**：枚举每个元素，使用 `bitset` 计算不包含该元素的集合的并集大小，取最大值。
   ```cpp
   for(int i = 1; i <= 55; i++){
       if(U[i] == 0) continue;
       bitset<maxn> now;
       for(int j = 1; j <= n; j++){
           if(S[j][i] == 0) now |= S[j];
       }
       ans = max(ans, (int)now.count());
   }
   ```

3. **作者：Leeb (4星)**
   - **关键亮点**：代码清晰，使用了布尔数组记录集合中元素的存在情况，避免了复杂的数据结构，思路简单直接。
   - **代码核心思想**：枚举每个元素，计算不包含该元素的集合的并集大小，取最大值。
   ```cpp
   for(int x = 0; x <= 50; x++){
       if(vis[x]){
           res = 0, mem(f, 0);
           for(int i = 1; i <= n; i++){
               if(is[i][x]) continue;
               else{
                   for(int j = 0; j <= 50; j++){
                       if(!f[j] && is[i][j]) ++res, f[j] = 1;
                   }
               }
           }
           ans = max(res, ans);
       }
   }
   ```

【最优关键思路】
通过枚举某个元素，强制不选择包含该元素的集合，然后计算剩余集合的并集大小，取最大值。这种方法在数据范围较小的情况下非常高效，且代码实现简单。

【可拓展之处】
类似的问题可以通过枚举某个条件来优化搜索空间，例如在组合数学或图论中，枚举某个节点或边来简化问题。

【推荐题目】
1. P1880 [NOI1995] 石子合并
2. P1886 滑动窗口
3. P1887 乘积最大

【个人心得】
- **调试经历**：在处理多组数据时，务必在每组数据开始前清空所有数组，避免数据污染。
- **顿悟感想**：通过枚举某个元素来简化问题，是一种常见的优化思路，尤其是在数据范围较小的情况下。

---
处理用时：31.77秒