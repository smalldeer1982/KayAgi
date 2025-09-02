# 题目信息

# Queries for the Array

## 题目描述

Monocarp had an array $ a $ consisting of integers. Initially, this array was empty.

Monocarp performed three types of queries to this array:

- choose an integer and append it to the end of the array. Each time Monocarp performed a query of this type, he wrote out a character +;
- remove the last element from the array. Each time Monocarp performed a query of this type, he wrote out a character -. Monocarp never performed this query on an empty array;
- check if the array is sorted in non-descending order, i.,e. $ a_1 \le a_2 \le \dots \le a_k $ , where $ k $ is the number of elements in the array currently. Every array with less than $ 2 $ elements is considered sorted. If the array was sorted by the time Monocarp was performing that query, he wrote out a character 1. Otherwise, he wrote out a character 0.

You are given a sequence $ s $ of $ q $ characters 0, 1, + and/or -. These are the characters that were written out by Monocarp, given in the exact order he wrote them out.

You have to check if this sequence is consistent, i. e. it was possible for Monocarp to perform the queries so that the sequence of characters he wrote out is exactly $ s $ .

## 说明/提示

In the first test case, Monocarp could perform the following sequence of queries:

- add the integer $ 13 $ ;
- add the integer $ 37 $ ;
- check that the current array $ [13, 37] $ is sorted in non-descending order (and it is sorted).

In the fifth test case, Monocarp could perform the following sequence of queries:

- add the integer $ 3 $ ;
- add the integer $ 2 $ ;
- check that the current array $ [3, 2] $ is sorted (it is not);
- remove the last element;
- add the integer $ 3 $ ;
- check that the current array $ [3, 3] $ is sorted (it is);
- remove the last element;
- add the integer $ -5 $ ;
- check that the current array $ [3, -5] $ is sorted (it is not).

In all other test cases of the example test, it is impossible for Monocarp to write the sequence $ s $ when performing the queries according to the statement.

## 样例 #1

### 输入

```
7
++1
+++1--0
+0
0
++0-+1-+0
++0+-1+-0
+1-+0```

### 输出

```
YES
NO
NO
NO
YES
NO
NO```

# AI分析结果

### 题目内容重写

Monocarp 有一个由整数组成的数组 $a$。最初，**这个数组是空的**。

Monocarp 对这个数组进行了三种查询：

- 选择一个整数，并将其 **到数组的末尾**。每当 Monocarp 执行一次这种类型的查询时，他都会写出一个字符 `+`；
- 从数组中删除 **数组的最后一个** 个元素。每次 Monocarp 执行这种类型的查询时，他都会写出一个字符（`-`）。Monocarp 从来没有在一个空数组上执行过这种查询；
- 检查数组是否以非降序排序，即 $a_1 \le a_2 \le \dots \le a_k$，其中 $k$ 是当前数组中元素的个数。**每个元素少于$2$的数组都被认为是排序过的**。如果在 Monocarp 执行该查询时数组已经排序，他就会写出字符 `1`。否则，他就写出一个字符 `0`。

给你一个由 $s$ 个 `0`、`1`、`+` 和 `-` 组成的字符序列。这些都是 Monocarp 写出的字符，并按照他写出的顺序给出。

你必须检查这个顺序是否一致，即 Monocarp 有可能进行查询，从而使他写出的字符顺序正好是 $s$。

### 算法分类
模拟

### 题解分析与结论

这道题的核心在于模拟 Monocarp 对数组的操作，并检查给定的操作序列是否合法。题解中，大多数解法都采用了类似的方法：通过维护当前数组的长度、已排序的最后一个位置、未排序的第一个位置等变量，来动态判断操作序列的合法性。

### 精选题解

#### 题解1：Creeper_l（5星）
**关键亮点：**
- 使用了三个变量 `cnt`、`finish_sort` 和 `unfinish_sort` 来维护数组的状态。
- 通过贪心策略，尽量保持数组的有序性，从而简化判断逻辑。
- 代码结构清晰，逻辑严密，易于理解。

**核心代码：**
```cpp
for(int i = 1;i <= len;i++)
{
    if(c[i] == '0')
    {
        if(cnt == finish_sort || cnt < 2){flag = false;break;} 
        if(!unfinish_sort) unfinish_sort = cnt;
    }
    if(c[i] == '1')
    {
        if(unfinish_sort != 0){flag = false;break;}
        finish_sort = cnt;
    }
    if(c[i] == '+') cnt++;
    if(c[i] == '-') 
    {
        cnt--;
        if(cnt < unfinish_sort) unfinish_sort = 0;
        if(cnt < finish_sort) finish_sort = cnt;
    }
}
```

#### 题解2：One_JuRuo（4星）
**关键亮点：**
- 使用了 `num`、`so` 和 `nso` 三个变量来维护数组的状态。
- 通过分类讨论，详细处理了每种操作的可能情况。
- 代码简洁，逻辑清晰，易于实现。

**核心代码：**
```cpp
for(int i=1;i<=n;++i)
{
    if(ch[i]=='+') ++num;
    if(ch[i]=='-') --num,nso=(num<nso)?0:nso,so=min(so,num);
    if(ch[i]=='1')
    {
        if(nso){flag=1;break;}
        so=num;
    }
    if(ch[i]=='0')
    {
        if(num<2||so==num){flag=1;break;}
        if(!nso) nso=num;
    }
}
```

#### 题解3：cosf（4星）
**关键亮点：**
- 使用了 `l`、`m` 和 `d` 三个变量来维护数组的状态。
- 通过初始化、操作处理和特判，确保了代码的鲁棒性。
- 代码结构清晰，逻辑严密，易于理解。

**核心代码：**
```cpp
for (char ch : q)
{
    if (ch == '0')
    {
        if (l == m || l <= 1)
        {
            e = 1;
            break;
        }
        else
        {
            d = min(d, l);
        }
    }
    if (ch == '1')
    {
        if (l >= d)
        {
            e = 1;
            break;
        }
        else
        {
            m = l;
        }
    }
    if (ch == '+')
    {
        l++;
    }
    if (ch == '-')
    {
        l--;
        if (l < m)
        {
            m = l;
        }
        if (l < d)
        {
            d = 1145141;
        }
    }
}
```

### 最优关键思路或技巧
- **状态维护**：通过维护当前数组的长度、已排序的最后一个位置、未排序的第一个位置等变量，动态判断操作序列的合法性。
- **贪心策略**：尽量保持数组的有序性，从而简化判断逻辑。
- **分类讨论**：详细处理每种操作的可能情况，确保代码的鲁棒性。

### 可拓展之处
- **同类型题**：类似的操作序列合法性判断问题，可以通过维护状态变量和贪心策略来解决。
- **类似算法套路**：动态维护状态变量，通过分类讨论和贪心策略，简化问题复杂度。

### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
3. [P3390 【模板】矩阵快速幂](https://www.luogu.com.cn/problem/P3390)

### 个人心得摘录
- **Creeper_l**：通过贪心策略，尽量保持数组的有序性，从而简化判断逻辑。
- **One_JuRuo**：通过分类讨论，详细处理了每种操作的可能情况，确保了代码的鲁棒性。
- **cosf**：通过初始化、操作处理和特判，确保了代码的鲁棒性。

---
处理用时：48.86秒