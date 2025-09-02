# 题目信息

# Two Teams

## 题目描述

There are $ n $ students standing in a row. Two coaches are forming two teams — the first coach chooses the first team and the second coach chooses the second team.

The $ i $ -th student has integer programming skill $ a_i $ . All programming skills are distinct and between $ 1 $ and $ n $ , inclusive.

Firstly, the first coach will choose the student with maximum programming skill among all students not taken into any team, and $ k $ closest students to the left of him and $ k $ closest students to the right of him (if there are less than $ k $ students to the left or to the right, all of them will be chosen). All students that are chosen leave the row and join the first team. Secondly, the second coach will make the same move (but all students chosen by him join the second team). Then again the first coach will make such move, and so on. This repeats until the row becomes empty (i. e. the process ends when each student becomes to some team).

Your problem is to determine which students will be taken into the first team and which students will be taken into the second team.

## 说明/提示

In the first example the first coach chooses the student on a position $ 3 $ , and the row becomes empty (all students join the first team).

In the second example the first coach chooses the student on position $ 4 $ , and the row becomes $ [2, 1] $ (students with programming skills $ [3, 4, 5] $ join the first team). Then the second coach chooses the student on position $ 1 $ , and the row becomes empty (and students with programming skills $ [1, 2] $ join the second team).

In the third example the first coach chooses the student on position $ 1 $ , and the row becomes $ [1, 3, 5, 4, 6] $ (students with programming skills $ [2, 7] $ join the first team). Then the second coach chooses the student on position $ 5 $ , and the row becomes $ [1, 3, 5] $ (students with programming skills $ [4, 6] $ join the second team). Then the first coach chooses the student on position $ 3 $ , and the row becomes $ [1] $ (students with programming skills $ [3, 5] $ join the first team). And then the second coach chooses the remaining student (and the student with programming skill $ 1 $ joins the second team).

In the fourth example the first coach chooses the student on position $ 3 $ , and the row becomes $ [2, 1] $ (students with programming skills $ [3, 4, 5] $ join the first team). Then the second coach chooses the student on position $ 1 $ , and the row becomes empty (and students with programming skills $ [1, 2] $ join the second team).

## 样例 #1

### 输入

```
5 2
2 4 5 3 1
```

### 输出

```
11111
```

## 样例 #2

### 输入

```
5 1
2 1 3 5 4
```

### 输出

```
22111
```

## 样例 #3

### 输入

```
7 1
7 2 1 3 5 4 6
```

### 输出

```
1121122
```

## 样例 #4

### 输入

```
5 1
2 4 5 3 1
```

### 输出

```
21112
```

# AI分析结果

### 题目内容重写（中文）

有 $n$ 个学生站成一排。两个教练正在组建两支队伍——第一个教练选择第一支队伍，第二个教练选择第二支队伍。

第 $i$ 个学生有一个整数编程能力值 $a_i$。所有编程能力值都是唯一的，并且介于 $1$ 和 $n$ 之间。

首先，第一个教练将从所有未被选中的学生中选择编程能力值最大的学生，并选择他左边最近的 $k$ 个学生和右边最近的 $k$ 个学生（如果左边或右边的学生少于 $k$ 个，则选择所有可用的学生）。所有被选中的学生离开队伍并加入第一支队伍。然后，第二个教练进行同样的操作（但他选中的学生加入第二支队伍）。接着，第一个教练再次进行选择，依此类推。这个过程重复进行，直到队伍为空（即每个学生都加入了某个队伍）。

你的问题是确定哪些学生将加入第一支队伍，哪些学生将加入第二支队伍。

### 算法分类
模拟

### 题解分析与结论

该题的核心逻辑是模拟两个教练轮流选择学生的过程，每次选择当前能力值最大的学生及其左右各 $k$ 个学生。难点在于如何高效地找到当前未被选中的最大能力值学生，并快速删除已选中的学生。

#### 题解对比
1. **SSerxhs** 的题解使用了双向链表来维护学生的左右关系，并通过从大到小遍历能力值来找到当前最大值。复杂度为 $O(n)$，思路清晰且代码简洁。
2. **da32s1da** 的题解使用了优先队列来维护最大值，并通过双向链表来删除已选中的学生。复杂度为 $O(n \log n)$，思路较为复杂但代码可读性较好。
3. **一扶苏一** 的题解使用了排序和双向链表，通过标记数组来判断学生是否被选中。复杂度为 $O(n \log n)$，思路清晰但代码稍显冗长。

#### 最优关键思路
- **双向链表**：用于高效地维护学生的左右关系，并快速删除已选中的学生。
- **从大到小遍历能力值**：通过排序或优先队列来快速找到当前未被选中的最大能力值学生。

#### 可拓展之处
- 类似的问题可以通过双向链表和优先队列的结合来解决，尤其是在需要频繁删除和查找最大值的场景中。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)
3. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)

### 个人心得
- **SSerxhs** 提到：“由于原数列是个排列，所以复杂度可以由势能分析得到是均摊$O(n)$。” 这表明在特定条件下，复杂度可以进一步优化。
- **da32s1da** 提到：“注意每次取出最大值时，若两个堆堆顶相同，删掉。” 这提醒我们在使用优先队列时要注意堆顶元素的处理。

### 精选题解

#### 1. SSerxhs (5星)
- **关键亮点**：使用双向链表和从大到小遍历能力值，复杂度为 $O(n)$，代码简洁且高效。
- **核心代码**：
```cpp
while (n)
{
    t ^= 3;
    while (ans[dy[n]]) --n;
    if (!n) break; ans[dy[n]] = t;
    j = pre[dy[n]]; k = nxt[dy[n]];
    for (i = 1; (j) && (i <= m); i++) ans[j] = t, j = pre[j];
    for (i = 1; (k) && (i <= m); i++) ans[k] = t, k = nxt[k];
    pre[k] = j; nxt[j] = k;
}
```

#### 2. da32s1da (4星)
- **关键亮点**：使用优先队列和双向链表，复杂度为 $O(n \log n)$，思路清晰但代码稍复杂。
- **核心代码**：
```cpp
while (!q.empty())
{
    while (p.size() && q.top() == p.top()) q.pop(), p.pop();
    if (q.empty()) break;
    for (i = 1, j = net[q.top().second]; i <= K && j; i++, j = net[j]) vis[j] = opt + 1, p.push(pr(a[j], j));
    for (i = 1, k = pre[q.top().second]; i <= K && k; i++, k = pre[k]) vis[k] = opt + 1, p.push(pr(a[k], k));
    vis[q.top().second] = opt + 1; q.pop();
    pre[j] = k; net[k] = j; opt ^= 1;
}
```

#### 3. 一扶苏一 (4星)
- **关键亮点**：使用排序和双向链表，复杂度为 $O(n \log n)$，思路清晰但代码稍显冗长。
- **核心代码**：
```cpp
for (int i = 1; i <= n; ++i) if (!dlt[pos[i]])
{
    if (cot != 1) cot = 1;
    else cot = 2;
    int s = lf[pos[i]];
    int cnt = 0;
    while ((cnt < k) && (s)) dlt[s] = true, ans[s] = cot, ++cnt, s = lf[s];
    s = rf[pos[i]];
    cnt = 0;
    while ((cnt < k) && (s)) dlt[s] = true, ans[s] = cot, ++cnt, s = rf[s];
    s = pos[i];
    if (lf[s]) rf[lf[s]] = rf[s];
    if (rf[s]) lf[rf[s]] = lf[s];
    ans[pos[i]] = cot; dlt[pos[i]] = true;
}
```

---
处理用时：41.56秒