# 题目信息

# Bogosort

## 题目描述

You are given an array $ a_1, a_2, \dots , a_n $ . Array is good if for each pair of indexes $ i < j $ the condition $ j - a_j \ne i - a_i $ holds. Can you shuffle this array so that it becomes good? To shuffle an array means to reorder its elements arbitrarily (leaving the initial order is also an option).

For example, if $ a = [1, 1, 3, 5] $ , then shuffled arrays $ [1, 3, 5, 1] $ , $ [3, 5, 1, 1] $ and $ [5, 3, 1, 1] $ are good, but shuffled arrays $ [3, 1, 5, 1] $ , $ [1, 1, 3, 5] $ and $ [1, 1, 5, 3] $ aren't.

It's guaranteed that it's always possible to shuffle an array to meet this condition.

## 样例 #1

### 输入

```
3
1
7
4
1 1 3 5
6
3 2 1 5 6 4```

### 输出

```
7
1 5 1 3
2 4 6 1 3 5```

# AI分析结果

【题目内容翻译】
# Bogosort

## 题目描述

给定一个数组 $a_1, a_2, \dots , a_n$。如果对于每一对下标 $i < j$，条件 $j - a_j \ne i - a_i$ 成立，则称该数组是“好的”。你能将这个数组重新排列，使其变为“好的”吗？重新排列数组意味着可以任意重新排序其元素（保留初始顺序也是一种选择）。

例如，如果 $a = [1, 1, 3, 5]$，那么重新排列后的数组 $[1, 3, 5, 1]$、$[3, 5, 1, 1]$ 和 $[5, 3, 1, 1]$ 是“好的”，但重新排列后的数组 $[3, 1, 5, 1]$、$[1, 1, 3, 5]$ 和 $[1, 1, 5, 3]$ 不是。

题目保证总是可以通过重新排列数组来满足这个条件。

## 样例 #1

### 输入

```
3
1
7
4
1 1 3 5
6
3 2 1 5 6 4```

### 输出

```
7
1 5 1 3
2 4 6 1 3 5```

【算法分类】
排序、构造

【题解分析与结论】
所有题解的核心思路都是通过将数组从大到小排序来满足题目条件。具体来说，当数组从大到小排序时，$i$ 递增而 $a_i$ 递减，因此 $i - a_i$ 严格递增，从而保证了对于任意 $i < j$，$j - a_j \ne i - a_i$。这种构造方法简单且高效，时间复杂度为 $O(n \log n)$。

【评分较高的题解】
1. **作者：C　C　A (赞：8)**  
   - **星级：5星**  
   - **关键亮点：** 思路清晰，代码简洁，直接通过排序和逆序输出实现目标。  
   - **核心代码：**
     ```cpp
     sort(a + 1 , a + n + 1);
     for(int i = n; i >= 1; i--)
         printf("%d " , a[i]);
     ```

2. **作者：do_while_false (赞：3)**  
   - **星级：4星**  
   - **关键亮点：** 使用了快读和快写优化，代码效率较高，思路与第一题解一致。  
   - **核心代码：**
     ```cpp
     stable_sort(a + 1, a + n + 1);
     reverse(a + 1, a + n + 1);
     for(int i = 1; i <= n; i++) write(a[i]);
     ```

3. **作者：vectorwyx (赞：2)**  
   - **星级：4星**  
   - **关键亮点：** 使用了宏定义简化代码，思路清晰，代码可读性强。  
   - **核心代码：**
     ```cpp
     sort(a + 1, a + 1 + n, cmp);
     fo(i, 1, n) printf("%d ", a[i]);
     ```

【最优关键思路】
通过将数组从大到小排序，确保 $i - a_i$ 严格递增，从而满足题目条件。这种方法简单且高效，适用于类似需要构造特定顺序的题目。

【可拓展之处】
类似的问题可以通过分析题目条件，找到合适的排序或构造策略来解决。例如，某些题目可能需要将数组从小到大排序，或者根据特定规则进行排序。

【推荐题目】
1. [P1104 生日](https://www.luogu.com.cn/problem/P1104) - 考察排序和构造
2. [P1093 奖学金](https://www.luogu.com.cn/problem/P1093) - 考察排序和多重条件判断
3. [P1051 谁拿了最多奖学金](https://www.luogu.com.cn/problem/P1051) - 考察排序和统计

---
处理用时：29.45秒