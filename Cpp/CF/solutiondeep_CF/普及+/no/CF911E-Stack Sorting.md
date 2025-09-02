# 题目信息

# Stack Sorting

## 题目描述

Let's suppose you have an array $ a $ , a stack $ s $ (initially empty) and an array $ b $ (also initially empty).

You may perform the following operations until both $ a $ and $ s $ are empty:

- Take the first element of $ a $ , push it into $ s $ and remove it from $ a $ (if $ a $ is not empty);
- Take the top element from $ s $ , append it to the end of array $ b $ and remove it from $ s $ (if $ s $ is not empty).

You can perform these operations in arbitrary order.

If there exists a way to perform the operations such that array $ b $ is sorted in non-descending order in the end, then array $ a $ is called stack-sortable.

For example, $ [3,1,2] $ is stack-sortable, because $ b $ will be sorted if we perform the following operations:

1. Remove $ 3 $ from $ a $ and push it into $ s $ ;
2. Remove $ 1 $ from $ a $ and push it into $ s $ ;
3. Remove $ 1 $ from $ s $ and append it to the end of $ b $ ;
4. Remove $ 2 $ from $ a $ and push it into $ s $ ;
5. Remove $ 2 $ from $ s $ and append it to the end of $ b $ ;
6. Remove $ 3 $ from $ s $ and append it to the end of $ b $ .

After all these operations $ b=[1,2,3] $ , so $ [3,1,2] $ is stack-sortable. $ [2,3,1] $ is not stack-sortable.

You are given $ k $ first elements of some permutation $ p $ of size $ n $ (recall that a permutation of size $ n $ is an array of size $ n $ where each integer from $ 1 $ to $ n $ occurs exactly once). You have to restore the remaining $ n-k $ elements of this permutation so it is stack-sortable. If there are multiple answers, choose the answer such that $ p $ is lexicographically maximal (an array $ q $ is lexicographically greater than an array $ p $ iff there exists some integer $ k $ such that for every $ i<k $ $ q_{i}=p_{i} $ , and $ q_{k}>p_{k} $ ). You may not swap or change any of first $ k $ elements of the permutation.

Print the lexicographically maximal permutation $ p $ you can obtain.

If there exists no answer then output -1.

## 样例 #1

### 输入

```
5 3
3 2 1
```

### 输出

```
3 2 1 5 4 ```

## 样例 #2

### 输入

```
5 3
2 3 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5 1
3
```

### 输出

```
3 2 1 5 4 ```

## 样例 #4

### 输入

```
5 2
3 4
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# 栈排序

## 题目描述
假设你有一个数组 $a$ 、一个栈 $s$（初始为空）和一个数组 $b$（初始也为空）。
你可以执行以下操作，直到 $a$ 和 $s$ 都为空：
 - 取出 $a$ 的第一个元素，将其压入 $s$ 并从 $a$ 中移除（如果 $a$ 不为空）；
 - 从 $s$ 中取出栈顶元素，将其追加到数组 $b$ 的末尾并从 $s$ 中移除（如果 $s$ 不为空）。
你可以以任意顺序执行这些操作。
如果存在一种操作方式，使得最终数组 $b$ 按非降序排序，那么数组 $a$ 就称为可栈排序的。
例如，$[3,1,2]$ 是可栈排序的，因为如果我们执行以下操作，$b$ 将被排序：
1. 从 $a$ 中移除 $3$ 并将其压入 $s$；
2. 从 $a$ 中移除 $1$ 并将其压入 $s$；
3. 从 $s$ 中移除 $1$ 并将其追加到 $b$ 的末尾；
4. 从 $a$ 中移除 $2$ 并将其压入 $s$；
5. 从 $s$ 中移除 $2$ 并将其追加到 $b$ 的末尾；
6. 从 $s$ 中移除 $3$ 并将其追加到 $b$ 的末尾。
经过所有这些操作后，$b = [1,2,3]$，所以 $[3,1,2]$ 是可栈排序的。$[2,3,1]$ 是不可栈排序的。
给定某个大小为 $n$ 的排列 $p$ 的前 $k$ 个元素（回想一下，大小为 $n$ 的排列是一个大小为 $n$ 的数组，其中从 $1$ 到 $n$ 的每个整数恰好出现一次）。你必须恢复这个排列的其余 $n - k$ 个元素，使其可栈排序。如果有多个答案，选择字典序最大的答案（数组 $q$ 在字典序上大于数组 $p$，当且仅当存在某个整数 $k$，使得对于每个 $i < k$，$q_i = p_i$，并且 $q_k > p_k$）。你不得交换或更改排列的前 $k$ 个元素中的任何一个。
打印你可以获得的字典序最大的排列 $p$。
如果不存在答案，则输出 -1。

## 样例 #1
### 输入
```
5 3
3 2 1
```
### 输出
```
3 2 1 5 4 
```

## 样例 #2
### 输入
```
5 3
2 3 1
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
5 1
3
```
### 输出
```
3 2 1 5 4 
```

## 样例 #4
### 输入
```
5 2
3 4
```
### 输出
```
-1
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是围绕栈排序的性质，通过分析给定的前 $k$ 个元素，来构造出剩余的 $n - k$ 个元素，使得整个排列可栈排序且字典序最大。
1. **思路**：多数题解先对给定的前 $k$ 个元素进行入栈操作，并在过程中尽量弹出符合顺序的元素。然后根据栈内剩余元素的情况判断是否有解，若栈内元素非单调递增则无解；若有解，则按照一定规则补充剩余元素。
2. **算法要点**：利用栈的特性模拟操作过程，关键在于如何确定补充元素的顺序以保证字典序最大且可栈排序。例如，对于栈顶元素 $x$，要让 $x$ 出栈，需将开区间 $(y, x)$（$y$ 为 $b$ 末尾的数）中的数逆序加入排列。
3. **解决难点**：难点在于理解栈排序的条件以及如何在满足条件的基础上构造字典序最大的排列。需要考虑栈内元素的顺序对后续出栈的影响，以及如何合理安排剩余元素的加入顺序。

### 所选的题解
- **作者：Error_Eric (5星)**
    - **关键亮点**：定义 $f_{l,r}$ 表示可栈排序的数列并利用其性质，通过递归方式简洁明了地解决问题，思路清晰，代码实现巧妙。
    - **重点代码 - 核心实现思想**：通过 `f` 函数递归构造最大的 $f[1][n]$，若当前区间有给定值则按性质递归处理，若未给定则直接取字典序最大的数填充。
```cpp
void f(int b, int l, int r) {
    if (l > r) return;
    if (l == r)
        if (p[b] && p[b]!= l) {
            putchar('-'), putchar('1'), exit(0);
        } else return (void)(p[b] = l);
    if (p[b])
        if (l <= p[b] && p[b] <= r) f(b + 1, l, p[b] - 1), f(b + 1 + (p[b] - l), p[b] + 1, r);
        else {
            putchar('-'), putchar('1'), exit(0);
        }
    else for (rei i = 0; i <= (r - l); i++) p[b + i] = r - i;
}
```
- **作者：jucason_xu (4星)**
    - **关键亮点**：先对前 $k$ 项维护栈，判断栈的单调性确定是否有解，再根据栈顶元素和序列尾部元素的关系逆序压入剩余元素，逻辑清晰，复杂度为线性。
    - **重点代码 - 核心实现思想**：`chk` 函数维护栈并判断单调性，主函数根据判断结果处理剩余元素。
```cpp
bool chk() {
    int lst = 0;
    rp(i, k) {
        while (s.size() && s.back() == lst + 1) s.pop_back(), lst++;
        s.pb(a[i]);
    }
    while (s.size() && s.back() == lst + 1) s.pop_back(), lst++;
    return is_sorted(s.begin(), s.end(), cmp);
}
```
- **作者：尹昱钦 (4星)**
    - **关键亮点**：明确栈排序的两个关键结论，即栈内元素清空后剩余元素从大到小放入答案序列尾部，比栈顶元素小的元素在栈底则无解，基于此思路清晰地实现代码。
    - **重点代码 - 核心实现思想**：在处理栈内元素时，检查比栈顶元素小的元素是否已在栈中，若已在则无解，否则逆序加入答案序列。
```cpp
while (!s.empty()) {
    for (int i = s.top() - 1; i >= cnt; i--) {
        if (vis[i]) {
            cout << -1;
            return 0;
        }
        a[++k] = i;
        vis[i] = 1;
    }
    cnt = s.top() + 1;
    s.pop();
}
```

### 最优关键思路或技巧
利用栈的模拟操作和贪心策略。在处理给定的前 $k$ 个元素时，尽量让符合顺序的元素出栈，以简化后续判断。对于栈内剩余元素，根据栈排序的性质，通过逆序填充元素来保证字典序最大且满足栈排序条件。

### 同类型题或类似算法套路拓展
此类题目通常围绕栈的特性进行构造，类似套路包括分析栈操作过程中的元素顺序、状态变化等，通过模拟或递归方式解决问题。常见的拓展方向有改变栈的操作规则、增加限制条件等。

### 洛谷相似题目推荐
1. **P1908 逆序对**：通过归并排序或树状数组解决逆序对问题，与本题类似之处在于都涉及到对序列元素顺序的分析和处理。
2. **P1090 [NOIP2004 提高组] 合并果子**：利用贪心策略解决合并问题，与本题一样需要考虑如何通过合理的策略构造出最优解。
3. **P1823 [COI2007] Patrik 音乐会的等待**：通过对数据的排序和分析，结合贪心思想解决等待时间问题，与本题在分析数据顺序和构造最优解方面思路相似。 

---
处理用时：78.37秒