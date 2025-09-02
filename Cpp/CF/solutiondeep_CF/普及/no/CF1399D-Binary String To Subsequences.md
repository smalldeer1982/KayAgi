# 题目信息

# Binary String To Subsequences

## 题目描述

You are given a binary string $ s $ consisting of $ n $ zeros and ones.

Your task is to divide the given string into the minimum number of subsequences in such a way that each character of the string belongs to exactly one subsequence and each subsequence looks like "010101 ..." or "101010 ..." (i.e. the subsequence should not contain two adjacent zeros or ones).

Recall that a subsequence is a sequence that can be derived from the given sequence by deleting zero or more elements without changing the order of the remaining elements. For example, subsequences of "1011101" are "0", "1", "11111", "0111", "101", "1001", but not "000", "101010" and "11100".

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
4
4
0011
6
111111
5
10101
8
01010000```

### 输出

```
2
1 2 2 1 
6
1 2 3 4 5 6 
1
1 1 1 1 1 
4
1 1 1 1 1 2 3 4```

# AI分析结果

### 题目内容重写（中文）

给定一个由 $n$ 个 0 和 1 组成的二进制字符串 $s$。

你的任务是将给定的字符串划分为最少数量的子序列，使得每个字符属于且仅属于一个子序列，并且每个子序列看起来像 "010101..." 或 "101010..."（即子序列中不应包含两个相邻的 0 或 1）。

回忆一下，子序列是指通过删除零个或多个元素而不改变剩余元素的顺序从给定序列派生的序列。例如，"1011101" 的子序列有 "0", "1", "11111", "0111", "101", "1001"，但不是 "000", "101010" 和 "11100"。

你需要回答 $t$ 个独立的测试用例。

### 样例 #1

#### 输入

```
4
4
0011
6
111111
5
10101
8
01010000
```

#### 输出

```
2
1 2 2 1 
6
1 2 3 4 5 6 
1
1 1 1 1 1 
4
1 1 1 1 1 2 3 4
```

### 算法分类
贪心

### 题解分析与结论

这道题的核心思想是通过贪心策略，尽可能地将当前字符接在已有的子序列后面，而不是新开一个子序列。为了高效地实现这一点，大多数题解都采用了维护两个栈或队列的方法，分别记录以 0 和 1 结尾的子序列的编号。这样可以在 $O(n)$ 的时间复杂度内解决问题。

### 所选高分题解

#### 题解1：b6e0_ (5星)
**关键亮点**：
- 使用 `vector` 数组来维护以 0 和 1 结尾的子序列，代码简洁且高效。
- 通过 `tar = (s[i] - '0') ^ 1` 快速找到需要匹配的子序列，避免了复杂的查找操作。
- 时间复杂度为 $O(n)$，适合大规模数据处理。

**核心代码**：
```cpp
vector<int>p[2];
p[s[0]-'0'].push_back(1);
be[0]=1;
for(i=1;i<n;i++)
{
    int tar=(s[i]-'0')^1;
    if(p[tar].empty())
    {
        be[i]=++ans;
        p[tar^1].push_back(ans);
    }
    else
    {
        int tmp=p[tar][p[tar].size()-1];
        be[i]=tmp;
        p[tar].pop_back();
        p[tar^1].push_back(tmp);
    }
}
```

#### 题解2：引领天下 (4星)
**关键亮点**：
- 使用优先队列来维护以 0 和 1 结尾的子序列，虽然多了一个 $log$ 的复杂度，但思路清晰。
- 通过 `priority_queue` 实现子序列的管理，代码结构清晰，易于理解。

**核心代码**：
```cpp
priority_queue<int,vector<int>,greater<int> > p,q;
if(s[i]=='0')
{
    if(p.empty())q.push(++k),cnt[i]=k;
    else cnt[i]=p.top(),p.pop(),q.push(cnt[i]);
}
else
{
    if(q.empty())p.push(++k),cnt[i]=k;
    else cnt[i]=q.top(),q.pop(),p.push(cnt[i]);
}
```

#### 题解3：tengkaize (4星)
**关键亮点**：
- 使用双栈来维护以 0 和 1 结尾的子序列，实现简单且高效。
- 通过 `stack` 实现子序列的管理，代码简洁，适合初学者理解。

**核心代码**：
```cpp
stack<int> st[2];
if (!st[s[i] ^ 1].empty()) {
    st[s[i]].push(st[s[i] ^ 1].top());
    st[s[i] ^ 1].pop();
}
else {
    st[s[i]].push(++k);
}
a[i] = st[s[i]].top();
```

### 最优关键思路或技巧
- **贪心策略**：尽可能地将当前字符接在已有的子序列后面，而不是新开一个子序列。
- **数据结构选择**：使用 `vector`、`stack` 或 `priority_queue` 来维护以 0 和 1 结尾的子序列，确保高效查找和更新。

### 可拓展之处
- **类似问题**：可以扩展到多字符序列的划分问题，如将字符串划分为多个不包含重复字符的子序列。
- **算法优化**：可以进一步优化数据结构的实现，如使用更高效的数据结构来维护子序列。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P3378 堆](https://www.luogu.com.cn/problem/P3378)

---
处理用时：36.73秒