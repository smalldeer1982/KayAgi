# 题目信息

# Subsequences (easy version)

## 题目描述

The only difference between the easy and the hard versions is constraints.

A subsequence is a string that can be derived from another string by deleting some or no symbols without changing the order of the remaining symbols. Characters to be deleted are not required to go successively, there can be any gaps between them. For example, for the string "abaca" the following strings are subsequences: "abaca", "aba", "aaa", "a" and "" (empty string). But the following strings are not subsequences: "aabaca", "cb" and "bcaa".

You are given a string $ s $ consisting of $ n $ lowercase Latin letters.

In one move you can take any subsequence $ t $ of the given string and add it to the set $ S $ . The set $ S $ can't contain duplicates. This move costs $ n - |t| $ , where $ |t| $ is the length of the added subsequence (i.e. the price equals to the number of the deleted characters).

Your task is to find out the minimum possible total cost to obtain a set $ S $ of size $ k $ or report that it is impossible to do so.

## 说明/提示

In the first example we can generate $ S $ = { "asdf", "asd", "adf", "asf", "sdf" }. The cost of the first element in $ S $ is $ 0 $ and the cost of the others is $ 1 $ . So the total cost of $ S $ is $ 4 $ .

## 样例 #1

### 输入

```
4 5
asdf
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 6
aaaaa
```

### 输出

```
15
```

## 样例 #3

### 输入

```
5 7
aaaaa
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
10 100
ajihiushda
```

### 输出

```
233
```

# AI分析结果

### 题目内容（中文重写）
# 子序列（简单版本）

## 题目描述
简单版本和困难版本的唯一区别在于数据范围。

子序列是指可以通过删除另一个字符串中的一些或不删除任何符号，同时不改变剩余符号的顺序而得到的字符串。要删除的字符不需要连续，它们之间可以有任意间隔。例如，对于字符串 "abaca"，以下字符串是它的子序列："abaca"、"aba"、"aaa"、"a" 和 ""（空字符串）。但以下字符串不是子序列："aabaca"、"cb" 和 "bcaa"。

给定一个由 $n$ 个小写拉丁字母组成的字符串 $s$。

在一次操作中，你可以选取给定字符串的任何一个子序列 $t$，并将其添加到集合 $S$ 中。集合 $S$ 中不能包含重复元素。这次操作的代价是 $n - |t|$，其中 $|t|$ 是添加的子序列的长度（即代价等于删除的字符数）。

你的任务是找出获得大小为 $k$ 的集合 $S$ 的最小可能总代价，或者报告无法做到这一点。

## 说明/提示
在第一个示例中，我们可以生成 $S$ = { "asdf", "asd", "adf", "asf", "sdf" }。$S$ 中第一个元素的代价是 $0$，其他元素的代价是 $1$。所以 $S$ 的总代价是 $4$。

## 样例 #1
### 输入
```
4 5
asdf
```
### 输出
```
4
```

## 样例 #2
### 输入
```
5 6
aaaaa
```
### 输出
```
15
```

## 样例 #3
### 输入
```
5 7
aaaaa
```
### 输出
```
-1
```

## 样例 #4
### 输入
```
10 100
ajihiushda
```
### 输出
```
233
```

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕如何求出不同长度的本质不同子序列的数量，然后通过贪心策略选取长度尽可能长的子序列来使得总代价最小。不同题解在动态规划的状态定义和转移方程上有所不同，但核心思路都是先统计子序列数量，再进行贪心选取。

### 所选的题解
- **wucstdio（5星）**
    - **关键亮点**：思路清晰，详细说明了动态规划的状态定义和转移方程，代码实现规范，注释较少但逻辑清晰，复杂度分析明确。
- **decoqwq（4星）**
    - **关键亮点**：递推思路简洁，通过记录字母上次出现的位置来避免重复计算，代码实现简单易懂。
- **wmrqwq（4星）**
    - **关键亮点**：动态规划思路明确，对可能出现的错误情况（$dp$ 值为负）进行了处理，代码中使用了较多自定义宏，结构清晰。

### 重点代码
#### wucstdio
```cpp
for(int i=1;i<=n;i++)
{
    f[i][1][t[i]-'a']=1;
    for(int j=1;j<=i;j++)
    {
        for(int c=0;c<26;c++)
        {
            if(c+'a'==t[i])f[i][j][c]+=s[i-1][j-1];
            else f[i][j][c]+=f[i-1][j][c];
            if(f[i][j][c]>k)f[i][j][c]=k;
            s[i][j]+=f[i][j][c];
        }
        if(s[i][j]>k)s[i][j]=k;
    }
}
s[n][0]=1;
for(int i=n;i>=0;i--)
{
    if(s[n][i]>k)
    {
        ans+=k*(n-i);
        k=0;
        break;
    }
    ans+=s[n][i]*(n-i);
    k-=s[n][i];
}
```
**核心实现思想**：使用三维数组 $f[i][j][c]$ 表示前 $i$ 个字符，长度为 $j$，最后一个字符为 $c$ 的子序列数量，通过状态转移方程计算不同长度的子序列数量，最后贪心选取。

#### decoqwq
```cpp
for(int i=1;i<=n;i++)
{
    for(int j=1;j<=i;j++)
    {
        if(las[a[i]]==0)
        {
            f[i][j]=f[i-1][j]+max(f[i-1][j-1],1ll);
        }
        else
        {
            f[i][j]=f[i-1][j]+f[i-1][j-1]-f[las[a[i]]-1][j-1];
        }
    }
    las[a[i]]=i;
}
for(int i=n;i>=0;i--)
{
    if(k<=f[n][i])
    {
        ans+=k*(n-i);
        k=0;
        break;
    }
    k-=f[n][i];
    ans+=f[n][i]*(n-i);
}
```
**核心实现思想**：使用二维数组 $f[i][j]$ 表示以 $i$ 位置结尾长度为 $j$ 的不同子串个数，通过记录字母上次出现的位置 $las[i]$ 来避免重复计算，最后贪心选取。

#### wmrqwq
```cpp
forl(i,1,n)
    pre[i]=lst[f(s[i])],lst[f(s[i])]=i;
forl(i,0,n)
    dp[i][0]=1;
forl(i,1,n)
    forl(j,1,i)
    {
        dp[i][j]=dp[i-1][j]+dp[i-1][j-1];
        if(pre[i])
            dp[i][j]-=dp[pre[i]-1][j-1];
    }
forr(i,n,0)
{
    Max(dp[n][i],0ll);
    if(m>=dp[n][i])
        ans+=(n-i)*dp[n][i],m-=dp[n][i];	
    else
        ans+=(n-i)*m,m=0;
}
```
**核心实现思想**：使用二维数组 $dp[i][j]$ 表示前 $i$ 个字符中长度为 $j$ 的不同的子序列数量，通过记录字符上次出现的位置 $pre[i]$ 来避免重复计算，对 $dp$ 值可能为负的情况进行处理，最后贪心选取。

### 最优关键思路或技巧
- **动态规划**：通过合理定义状态和转移方程，计算不同长度的本质不同子序列的数量。
- **贪心策略**：优先选择长度长的子序列，以使得总代价最小。
- **去重处理**：通过记录字符上次出现的位置，避免重复计算子序列。

### 可拓展之处
同类型题目可能会改变字符串的范围、子序列的选取规则或代价计算方式，但核心思路仍然是动态规划和贪心。类似算法套路包括在其他字符串问题中使用动态规划计算子序列数量，以及在优化问题中使用贪心策略。

### 推荐洛谷题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：考察动态规划中的 0 - 1 背包问题。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：经典的动态规划题目，与本题的动态规划思想有相似之处。
- [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：考察完全背包问题，也是动态规划的应用。

### 个人心得摘录与总结
- **wmrqwq**：提到 $dp_{n,i}$ 可能会小于 $0$，贪心前需要先将 $dp_{n,i}$ 和 $0$ 取最大值，否则会出现 Wrong Answer on test #35 的错误，提醒我们在动态规划中要注意边界情况和可能出现的负数结果。

---
处理用时：54.12秒