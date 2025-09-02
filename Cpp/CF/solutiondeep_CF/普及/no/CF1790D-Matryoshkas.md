# 题目信息

# Matryoshkas

## 题目描述

Matryoshka is a wooden toy in the form of a painted doll, inside which you can put a similar doll of a smaller size.

A set of nesting dolls contains one or more nesting dolls, their sizes are consecutive positive integers. Thus, a set of nesting dolls is described by two numbers: $ s $ — the size of a smallest nesting doll in a set and $ m $ — the number of dolls in a set. In other words, the set contains sizes of $ s, s + 1, \dots, s + m - 1 $ for some integer $ s $ and $ m $ ( $ s,m > 0 $ ).

You had one or more sets of nesting dolls. Recently, you found that someone mixed all your sets in one and recorded a sequence of doll sizes — integers $ a_1, a_2, \dots, a_n $ .

You do not remember how many sets you had, so you want to find the minimum number of sets that you could initially have.

For example, if a given sequence is $ a=[2, 2, 3, 4, 3, 1] $ . Initially, there could be $ 2 $ sets:

- the first set consisting of $ 4 $ nesting dolls with sizes $ [1, 2, 3, 4] $ ;
- a second set consisting of $ 2 $ nesting dolls with sizes $ [2, 3] $ .

According to a given sequence of sizes of nesting dolls $ a_1, a_2, \dots, a_n $ , determine the minimum number of nesting dolls that can make this sequence.

Each set is completely used, so all its nesting dolls are used. Each element of a given sequence must correspond to exactly one doll from some set.

## 说明/提示

The first test case is described in the problem statement.

In the second test case, all matryoshkas could be part of the same set with minimum size $ s=7 $ .

In the third test case, each matryoshka represents a separate set.

## 样例 #1

### 输入

```
10
6
2 2 3 4 3 1
5
11 8 7 10 9
6
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
8
1 1 4 4 2 3 2 3
6
1 2 3 2 3 4
7
10 11 11 12 12 13 13
7
8 8 9 9 10 10 11
8
4 14 5 15 6 16 7 17
8
5 15 6 14 8 12 9 11
5
4 2 2 3 4```

### 输出

```
2
1
6
2
2
2
2
2
4
3```

# AI分析结果

### 题目重写
**Matryoshkas**

**题目描述**

Matryoshka（套娃）是一种木制玩具，外形为彩绘的娃娃，内部可以放入一个更小的相似娃娃。

一组套娃包含一个或多个套娃，它们的大小是连续的正整数。因此，一组套娃由两个数字描述：$s$ — 组中最小的套娃大小，$m$ — 组中套娃的数量。换句话说，这组套娃包含大小为 $s, s + 1, \dots, s + m - 1$ 的套娃，其中 $s$ 和 $m$ 为正整数（$s,m > 0$）。

你原本有一组或多组套娃。最近，你发现有人将所有套娃混合在一起，并记录了一个套娃大小的序列 — 整数 $a_1, a_2, \dots, a_n$。

你不记得原本有多少组套娃，因此你想找出最初可能拥有的最小套娃组数。

例如，如果给定的序列是 $a=[2, 2, 3, 4, 3, 1]$。最初可能有 $2$ 组套娃：

- 第一组包含 $4$ 个套娃，大小为 $[1, 2, 3, 4]$；
- 第二组包含 $2$ 个套娃，大小为 $[2, 3]$。

根据给定的套娃大小序列 $a_1, a_2, \dots, a_n$，确定可以组成该序列的最小套娃组数。

每组套娃必须完全使用，因此组中的所有套娃都必须被使用。序列中的每个元素必须恰好对应某个组中的一个套娃。

**说明/提示**

第一个测试用例在题目描述中已经给出。

在第二个测试用例中，所有套娃可能属于同一组，最小大小为 $s=7$。

在第三个测试用例中，每个套娃代表一个单独的组。

### 算法分类
贪心

### 题解分析与结论
本题的核心是通过贪心策略将给定的套娃大小序列划分为尽可能少的连续整数组。所有题解都采用了类似的思路：使用 `map` 统计每个数字的出现次数，然后从大到小遍历序列，尝试将连续的整数组成一组，并减少相应的计数。

### 所选高分题解

#### 1. 作者：Lovely_Elaina (赞：7)
**星级：5**
**关键亮点：**
- 使用 `map` 统计数字出现次数，结合贪心策略从大到小遍历序列。
- 代码简洁清晰，逻辑明确。
- 通过 `while` 循环扩展连续区间，确保每组套娃的完整性。

**代码核心实现：**
```cpp
for(register int i = n; i >= 1; i--){
    if(!m[a[i]]) continue;
    int p = a[i];
    m[p]--;
    while(1){
        if(m[p-1] > 0)
            p--,m[p]--;
        else break;
    }
    ans++;
}
```

#### 2. 作者：arrow_king (赞：2)
**星级：4**
**关键亮点：**
- 同样使用 `map` 和贪心策略，代码结构与前一个题解相似。
- 强调了每个数只会被删除一次，时间复杂度为 $O(n\log n)$。

**代码核心实现：**
```cpp
for(int i=n;i>=1;i--){
    if(mp[a[i]]==0) continue;
    int now=a[i];
    mp[now]--;
    while(1){
        if(mp[now-1]>0){
            now--;
            mp[now]--;
        }
        else break;
    }
    ans++;
}
```

#### 3. 作者：loser_seele (赞：2)
**星级：4**
**关键亮点：**
- 提出了“极长区间”的概念，并解释了为什么贪心策略是正确的。
- 代码实现与前两个题解类似，但增加了对贪心策略正确性的证明。

**代码核心实现：**
```cpp
for(int i=1;i<=n;i++)
if(cnt[a[i]]){
    int now=a[i];
    while(cnt[now])
        cnt[now]--,now++;
    ans++;
}
```

### 最优关键思路
- **贪心策略**：从大到小遍历序列，尽可能将连续的整数组成一组，减少组数。
- **数据结构**：使用 `map` 统计每个数字的出现次数，方便快速查找和更新。

### 可拓展之处
- 类似的问题可以扩展到其他需要将序列划分为连续子序列的场景，如连续日期的分组、连续任务的分组等。

### 推荐题目
1. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得
- **调试经历**：在实现贪心策略时，确保从大到小遍历序列是关键，否则可能导致无法正确扩展连续区间。
- **顿悟感想**：贪心策略的正确性在于每次尽可能多地使用连续整数，从而减少组数。

---
处理用时：34.81秒