# 题目信息

# Equate Multisets

## 题目描述

Multiset —is a set of numbers in which there can be equal elements, and the order of the numbers does not matter. Two multisets are equal when each value occurs the same number of times. For example, the multisets $ \{2,2,4\} $ and $ \{2,4,2\} $ are equal, but the multisets $ \{1,2,2\} $ and $ \{1,1,2\} $ — are not.

You are given two multisets $ a $ and $ b $ , each consisting of $ n $ integers.

In a single operation, any element of the $ b $ multiset can be doubled or halved (rounded down). In other words, you have one of the following operations available for an element $ x $ of the $ b $ multiset:

- replace $ x $ with $ x \cdot 2 $ ,
- or replace $ x $ with $ \lfloor \frac{x}{2} \rfloor $ (round down).

Note that you cannot change the elements of the $ a $ multiset.

See if you can make the multiset $ b $ become equal to the multiset $ a $ in an arbitrary number of operations (maybe $ 0 $ ).

For example, if $ n = 4 $ , $ a = \{4, 24, 5, 2\} $ , $ b = \{4, 1, 6, 11\} $ , then the answer is yes. We can proceed as follows:

- Replace $ 1 $ with $ 1 \cdot 2 = 2 $ . We get $ b = \{4, 2, 6, 11\} $ .
- Replace $ 11 $ with $ \lfloor \frac{11}{2} \rfloor = 5 $ . We get $ b = \{4, 2, 6, 5\} $ .
- Replace $ 6 $ with $ 6 \cdot 2 = 12 $ . We get $ b = \{4, 2, 12, 5\} $ .
- Replace $ 12 $ with $ 12 \cdot 2 = 24 $ . We get $ b = \{4, 2, 24, 5\} $ .
- Got equal multisets $ a = \{4, 24, 5, 2\} $ and $ b = \{4, 2, 24, 5\} $ .

## 说明/提示

The first example is explained in the statement.

In the second example, it is impossible to get the value $ 31 $ from the numbers of the multiset $ b $ by available operations.

In the third example, we can proceed as follows:

- Replace $ 2 $ with $ 2 \cdot 2 = 4 $ . We get $ b = \{4, 14, 14, 26, 42\} $ .
- Replace $ 14 $ with $ \lfloor \frac{14}{2} \rfloor = 7 $ . We get $ b = \{4, 7, 14, 26, 42\} $ .
- Replace $ 26 $ with $ \lfloor \frac{26}{2} \rfloor = 13 $ . We get $ b = \{4, 7, 14, 13, 42\} $ .
- Replace $ 42 $ with $ \lfloor \frac{42}{2} \rfloor = 21 $ . We get $ b = \{4, 7, 14, 13, 21\} $ .
- Replace $ 21 $ with $ \lfloor \frac{21}{2} \rfloor = 10 $ . We get $ b = \{4, 7, 14, 13, 10\} $ .
- Got equal multisets $ a = \{4, 7, 10, 13, 14\} $ and $ b = \{4, 7, 14, 13, 10\} $ .

## 样例 #1

### 输入

```
5
4
2 4 5 24
1 4 6 11
3
1 4 17
4 5 31
5
4 7 10 13 14
2 14 14 26 42
5
2 2 4 4 4
28 46 62 71 98
6
1 2 10 16 64 80
20 43 60 74 85 99```

### 输出

```
YES
NO
YES
YES
YES```

# AI分析结果

### 题目内容重写
**题目描述**  
多重集（Multiset）是一种允许元素重复的集合，且元素的顺序不重要。两个多重集相等当且仅当每个元素出现的次数相同。例如，多重集 $\{2,2,4\}$ 和 $\{2,4,2\}$ 是相等的，但 $\{1,2,2\}$ 和 $\{1,1,2\}$ 不相等。

给定两个多重集 $a$ 和 $b$，每个集合包含 $n$ 个整数。你可以对 $b$ 中的元素进行以下操作：
- 将元素 $x$ 替换为 $x \cdot 2$；
- 或将元素 $x$ 替换为 $\lfloor \frac{x}{2} \rfloor$（向下取整）。

问是否可以通过任意次数的操作使 $b$ 与 $a$ 相等。

**样例解释**  
例如，当 $n = 4$，$a = \{4, 24, 5, 2\}$，$b = \{4, 1, 6, 11\}$ 时，可以通过以下操作使 $b$ 与 $a$ 相等：
1. 将 $1$ 替换为 $2$；
2. 将 $11$ 替换为 $5$；
3. 将 $6$ 替换为 $12$；
4. 将 $12$ 替换为 $24$。

最终 $b = \{4, 2, 24, 5\}$，与 $a$ 相等。

### 算法分类
贪心

### 题解分析与结论
本题的核心思路是通过贪心策略，将 $b$ 中的元素通过乘2或除2的操作，逐步匹配 $a$ 中的元素。大多数题解都采用了将 $a$ 和 $b$ 中的元素先处理为奇数，然后通过优先队列或排序来处理最大元素，逐步匹配的思路。

### 所选高分题解
#### 题解1：作者：baiABC (赞：14)
**星级：5星**  
**关键亮点**：通过将 $a$ 和 $b$ 中的元素处理为奇数，简化问题。使用优先队列处理最大元素，逐步匹配，思路清晰且代码简洁。
**核心代码**：
```cpp
while(!b.empty()) {
    if(*--b.end() > *--a.end()) {
        int x = *--b.end();
        b.erase(--b.end());
        b.insert(x/2);
    }
    else if(*--b.end() < *--a.end()) {
        ok = false;
        break;
    }
    else {
        b.erase(--b.end());
        a.erase(--a.end());
    }
}
```
**核心思想**：通过贪心策略，每次处理 $b$ 中最大的元素，逐步匹配 $a$ 中的元素。

#### 题解2：作者：tzyt (赞：5)
**星级：4星**  
**关键亮点**：通过位运算的性质，将问题转化为二进制前缀匹配问题，思路新颖且高效。
**核心代码**：
```cpp
while (b.size()) {
    int lb = b.top();
    b.pop();
    int la = a.back();
    if (la > lb) {
        goto FAIL;
    } else if (la < lb) {
        lb /= 2;
        b.push(lb);
    } else {  // la == lb
        a.pop_back();
    }
}
```
**核心思想**：利用二进制前缀匹配的性质，通过贪心策略逐步匹配 $a$ 和 $b$ 中的元素。

#### 题解3：作者：luo_shen (赞：1)
**星级：4星**  
**关键亮点**：通过优先队列处理最大元素，逐步匹配，代码简洁且易于理解。
**核心代码**：
```cpp
while(!q.empty()) {
    int x=q.top(),y=p.top();
    q.pop(),p.pop();
    if(y<x) {
        f=0;
        break;
    }
    else if(y>x) {
        q.push(x);
        p.push(y/2);
    }
}
```
**核心思想**：通过优先队列处理最大元素，逐步匹配 $a$ 和 $b$ 中的元素。

### 最优关键思路
最优的思路是通过将 $a$ 和 $b$ 中的元素处理为奇数，简化问题，然后通过贪心策略，每次处理 $b$ 中最大的元素，逐步匹配 $a$ 中的元素。这种方法既高效又易于实现。

### 拓展思路
类似的问题可以通过贪心策略结合位运算或优先队列来解决，尤其是在处理元素变换或匹配问题时，贪心策略往往能提供高效的解决方案。

### 推荐题目
1. [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：32.57秒