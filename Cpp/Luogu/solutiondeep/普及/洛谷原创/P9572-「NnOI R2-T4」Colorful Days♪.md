# 题目信息

# 「NnOI R2-T4」Colorful Days♪

## 题目描述

给出如下定义：

1. 定义 $ AB $ 为 $ A $ 数组后拼接 $ B $ 数组。
2. 定义 $ A^{0}=\{\} $（即空数组），且对 $i=1,2,3,\cdots$，$ A^{i}=A^{i-1}A$。
2. 定义 $ \operatorname{LCS}(A,B) $ 为 $ A $ 数组和 $ B $ 数组的**最长公共子序列**长度。

现给定长度为 $ n $ 的数组 $ S $ 和长度为 $ m $ 的数组 $ T $，数组中的数均为正整数。

你现在需要找到最小的非负整数 $k$，使得 $ \operatorname{LCS}(S^k,T) $ 最大。

出题人很仁慈，如果你无法最小化 $k$，你也可以拿到一部分分数。

## 说明/提示

**【样例 1 解释】**

当 $k = 2$ 时，$S^k = \text{\{23 34 \textcolor{red}{53 23 34} 53\}}$，其中标红的是 $S^k$ 和 $T$ 的最长公共子序列。

**【数据范围】**

**提示：本题开启捆绑测试。**

对于 $ 100\% $ 的数据，保证 $ 1 \le n,m,S_i,T_i \le 10^6 $，$ c_1,c_2 \in \{0,1\} $。

$$
\def\r{\cr\hline}
\def\None{\text{None}}
\def\arraystretch{1.5}
\begin{array}{c|c|c}
\textbf{Subtask} & \textbf{Sp. Constraints} & \textbf{Score}\r
\textsf1& c_1=c_2=0 & 2 \r
\textsf2& n \le 10^3，m \le 10^2 & 8 \r
\textsf3& n \le 10^4，m \le 10^3 & 15 \r
\textsf4& c_2=0 & 15 \r
\textsf5& n,m \le 10^5，S_i,T_i \le 26 & 20 \r
\textsf6& 无特殊限制 & 40 \r
\end{array}
$$

在赛后新添加的 hack 测试点会加入 subtask7。

### 题目来源

| 项目 | 人员 |
|:-:|:-:|
|idea| 船酱魔王 |
|data| 船酱魔王 |
|check| Sudohry |
|solution| 船酱魔王 |

## 样例 #1

### 输入

```
3 4 1 1
23 34 53
53 25 23 34```

### 输出

```
3 2```

## 样例 #2

### 输入

```
9 10 1 1
15 12 26 21 26 21 23 12 23
26 11 21 15 16 15 12 23 17 12```

### 输出

```
7 3```

# AI分析结果

### 综合分析与结论
这些题解思路大致相同，都将题目拆分为两问解答：
 - **第一问**：由于\(S\)可无限复制，\(\text{LCS}(S^k,T)\)最大时是\(T\)中在\(S\)里出现过的元素个数，通过遍历\(T\)判断元素是否在\(S\)中出现统计答案。
 - **第二问**：为求最小的\(k\)，用贪心策略，按\(T\)顺序匹配\(S\)，维护上一个匹配位置，每次找当前元素在\(S\)中大于上一位置的最小位置，找不到则新开一个\(S\)。为优化查找，利用\(10^6\)值域，用`vector`或`set`记录每个数在\(S\)中的位置，通过二分查找（如`upper_bound`或`lower_bound`）实现\(O(\log n)\)查找，整体时间复杂度\(O(m\log n)\) 。

### 所选的题解
- **作者：船酱魔王（5星）**
    - **关键亮点**：作为官方题解，思路阐述清晰，从得分策略引入，逐步分析两问解法，代码注释详细。
    - **重点代码及核心思想**：
```cpp
int findx(int p, int val) {
    int l, r, mid;
    l = -1;
    r = g[p].size();
    while(l + 1 < r) {
        mid = (l + r) >> 1;
        if(g[p][mid] > val) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return r;
}
// 核心思想：二分查找函数，在g[p]数组中找第一个大于val的位置
```
```cpp
for(int i = 1; i <= n; i++) {
    scanf("%d", &s[i]);
    vis[s[i]] = 1;
}
for(int i = 1; i <= m; i++) {
    scanf("%d", &t[i]);
}
for(int i = 1; i <= m; i++) {
    if(!vis[t[i]]) {
        t[i] = -1;
    }
} 
// 标记并去除T中在S里未出现的元素
```
```cpp
for(int i = 1; i <= m; i++) {
    if(t[i]!= -1) {
        m++;
        t[m] = t[i];
    }
}
// 重构T数组，仅保留在S中出现的元素
```
```cpp
for(int i = 1; i <= n; i++) {
    g[s[i]].push_back(i);
}
// 记录每个数在S中的位置
```
```cpp
int sc = 1;
int pos = g[t[1]][0];
for(int i = 2; i <= m; i++) {
    pos = findx(t[i], pos);
    if(pos == g[t[i]].size()) {
        pos = g[t[i]][0];
        sc++;
    } else {
        pos = g[t[i]][pos];
    }
}
// 贪心匹配，统计最小k值
```
 - **作者：Jorisy（4星）**
    - **关键亮点**：思路清晰简洁，代码实现精炼，对两问的转换和贪心策略的描述准确。
    - **重点代码及核心思想**：
```cpp
for(int i=1;i<=n;i++)
{
    scanf("%d",&a[i]);
    v[a[i]].push_back(i);
}
// 记录每个数在S中的位置
```
```cpp
for(int i=1;i<=m;i++)
{
    scanf("%d",&b[i]);
    if(v[b[i]].size()) b[++p]=b[i];
}
m=p;
// 重构T数组，仅保留在S中出现的元素
```
```cpp
printf("%d ",p*c1);
int lst=0;
for(int i=1;i<=m;i++)
{
    auto t=lower_bound(v[b[i]].begin(),v[b[i]].end(),lst+1);
    if(t==v[b[i]].end())
    {
        ans++;
        lst=*v[b[i]].begin();
    }
    else lst=*t;
}
cout<<++ans*c2;
// 贪心匹配，统计最小k值
```
 - **作者：COsm0s（4星）**
    - **关键亮点**：解法阐述简洁明了，对每一步操作和复杂度分析清晰，代码实现简洁高效。
    - **重点代码及核心思想**：
```cpp
for (int i = 1; i <= n; i ++) cin >> s[i], cnt[s[i]].push_back(i), s[i + n] = s[i];
for (int i = 1; i <= n; i ++) cnt[s[i]].push_back(i + n);
// 记录每个数在S中的位置，并复制一遍S方便处理边界情况
```
```cpp
int lst = n, flag = 1;
for (int i = 1; i <= m; i ++) {
    if (!cnt[t[i]].size()) continue;
    sum ++;
    int k = upper_bound(cnt[t[i]].begin(), cnt[t[i]].end(), lst) - cnt[t[i]].begin();
    lst = cnt[t[i]][k];
    if (cnt[t[i]][k] > n)  LCS ++, lst -= n;
}
// 贪心匹配，统计最长公共子序列长度和最小k值
```

### 最优的关键思路或技巧
 - **思维方式**：将原问题拆分为求最长公共子序列长度和最小\(k\)值两问，通过分析性质，发现第一问是统计\(T\)中在\(S\)出现的元素个数；第二问利用贪心策略，尽可能在已有\(S\)中匹配\(T\)元素。
 - **数据结构与算法优化**：利用\(10^6\)值域，用`vector`或`set`存储每个数在\(S\)中的位置，通过二分查找实现快速定位，将查找时间复杂度从\(O(n)\)优化到\(O(\log n)\)，整体时间复杂度达到\(O(m\log n)\)。

### 可拓展之处
此类题目属于序列匹配与优化问题，常见拓展方向是改变序列操作或约束条件，如序列拼接规则变化、增加元素限制等。类似算法套路是先分析问题性质确定贪心策略，再利用合适数据结构优化查找或操作。

### 相似知识点的洛谷题目
 - [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略和优先队列优化解决合并问题，与本题贪心思想类似。
 - [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：涉及策略分析与贪心选择，锻炼思维能力，与本题分析问题确定策略过程相似。
 - [P2827 [NOIP2016 提高组] 蚯蚓](https://www.luogu.com.cn/problem/P2827)：通过数据结构优化实现贪心策略，与本题利用数据结构优化贪心过程类似。

### 个人心得摘录与总结
 - **作者：聊机**：提到rank1解题速度快，自己做题时间长，通过逐步分析部分分得到正解思路，先解决特殊情况拿部分分，再逐步优化到正解。
 - **作者：玄学OIER荷蒻**：分享解题时间和对值域提示的看法，还提及离散化思路（虽超纲），拓宽了解题思路。 

---
处理用时：44.02秒