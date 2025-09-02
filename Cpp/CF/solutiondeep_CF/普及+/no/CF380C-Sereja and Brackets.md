# 题目信息

# Sereja and Brackets

## 题目描述

Sereja has a bracket sequence $ s_{1},s_{2},...,s_{n} $ , or, in other words, a string $ s $ of length $ n $ , consisting of characters "(" and ")".

Sereja needs to answer $ m $ queries, each of them is described by two integers $ l_{i},r_{i} $ $ (1<=l_{i}<=r_{i}<=n) $ . The answer to the $ i $ -th query is the length of the maximum correct bracket subsequence of sequence $ s_{li},s_{li}+1,...,s_{ri} $ . Help Sereja answer all queries.

You can find the definitions for a subsequence and a correct bracket sequence in the notes.

## 说明/提示

A subsequence of length $ |x| $ of string $ s=s_{1}s_{2}...\ s_{|s|} $ (where $ |s| $ is the length of string $ s $ ) is string $ x=s_{k1}s_{k2}...\ s_{k|x|} $ $ (1<=k_{1}<k_{2}<...<k_{|x|}<=|s|) $ .

A correct bracket sequence is a bracket sequence that can be transformed into a correct aryphmetic expression by inserting characters "1" and "+" between the characters of the string. For example, bracket sequences "()()", "(())" are correct (the resulting expressions "(1)+(1)", "((1+1)+1)"), and ")(" and "(" are not.

For the third query required sequence will be «()».

For the fourth query required sequence will be «()(())(())».

## 样例 #1

### 输入

```
())(())(())(
7
1 1
2 3
1 2
1 12
8 12
5 11
2 10
```

### 输出

```
0
0
2
10
4
6
6
```

# AI分析结果

### 题目内容
#### Sereja和括号
1. **题目描述**：Sereja有一个括号序列\(s_{1},s_{2},\cdots,s_{n}\)，即一个长度为\(n\)的字符串\(s\)，由字符“(”和“)”组成。Sereja需要回答\(m\)个查询，每个查询由两个整数\(l_{i},r_{i}\)描述\((1\leq l_{i}\leq r_{i}\leq n)\)。第\(i\)个查询的答案是序列\(s_{l_{i}},s_{l_{i}+1},\cdots,s_{r_{i}}\)中最大的正确括号子序列的长度。请帮助Sereja回答所有查询。你可以在注释中找到子序列和正确括号序列的定义。
2. **说明/提示**：
    - 字符串\(s = s_{1}s_{2}\cdots s_{|s|}\)（其中\(|s|\)是字符串\(s\)的长度）的长度为\(|x|\)的子序列是字符串\(x = s_{k_{1}}s_{k_{2}}\cdots s_{k_{|x|}}\) \((1\leq k_{1}<k_{2}<\cdots<k_{|x|}\leq |s|)\)。
    - 正确括号序列是一种括号序列，通过在字符串的字符之间插入字符“1”和“+”，可以将其转换为正确的算术表达式。例如，括号序列“()()”、“(())”是正确的（得到的表达式为“(1)+(1)”、“((1 + 1)+1)”），而“)("和“(”则不正确。
    - 对于第三个查询，所需序列将是“()”。
    - 对于第四个查询，所需序列将是“()(())(())”。
3. **样例 #1**：
    - **输入**：
```
())(())(())(
7
1 1
2 3
1 2
1 12
8 12
5 11
2 10
```
    - **输出**：
```
0
0
2
10
4
6
6
```

### 算法分类
线段树

### 综合分析与结论
这些题解主要围绕如何高效求解给定区间内最长合法括号子序列长度展开。大部分题解采用线段树数据结构，少数使用ST表。
1. **思路方面**：
    - 多数题解通过维护区间内未匹配的左、右括号数量，利用线段树的区间合并特性来求解。如Meatherm、LJC00118等题解，将原括号序列按位置构建线段树节点，叶节点记录该位置括号类型对应的未匹配括号数，非叶节点通过左右子节点未匹配括号数计算自身未匹配括号数，同时考虑左右子区间可匹配括号对数。
    - 部分题解如SunsetGlow95、sinsop90、pldzy将括号序列转化为数值序列（左括号为1，右括号为 - 1）并求前缀和，借助RMQ或ST表维护区间最小值，通过分析前缀和与区间长度、未匹配括号数关系求解。
2. **算法要点**：
    - 线段树解法关键在于合理定义节点维护信息（未匹配括号数等）及准确实现区间合并操作。如Meatherm题解中，节点维护未匹配左括号数\(Lsum_k\)和右括号数\(Rsum_k\)，区间合并时减去左右子区间可匹配括号对数\(\min\{Lsum_{lc},Rsum_{rc}\}\)。
    - ST表解法核心是利用其快速查询区间最值能力，结合转化后的前缀和序列，通过公式计算合法括号子序列长度。
3. **解决难点**：
    - 难点在于如何找到一种有效的数据结构或方法来处理多个区间查询，并准确计算未匹配括号数及合法括号子序列长度。线段树通过区间合并解决此问题，而转化为前缀和结合RMQ/ST表则从另一个角度巧妙利用数值关系求解。

### 所选的题解
1. **作者：Meatherm (赞：22)  星级：5星**
    - **关键亮点**：思路清晰，直接采用线段树维护区间内不能匹配的左括号数量\(Lsum_k\)和右括号数量\(Rsum_k\)，详细说明了叶节点和非叶节点的计算方式，时间复杂度分析准确。
    - **重点代码核心实现思想**：构建线段树时，叶节点根据原序列字符确定\(Lsum_k\)和\(Rsum_k\)，非叶节点通过左右子节点计算并更新。查询时，根据查询区间递归获取子区间信息并合并。
    - **核心代码片段**：
```cpp
// 构建线段树
void build(int k, int l, int r) {
    if (l == r) {
        if (s[l] == '(')
            tree[k].Lsum = 1;
        if (s[r] == ')')
            tree[k].Rsum = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc(k), l, mid);
    build(rc(k), mid + 1, r);
    pushup(k);
    return;
}
// 查询
Tree ask(int k, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return tree[k];
    }
    int mid = (l + r) >> 1;
    if (L <= mid &&!(mid < R))
        return ask(lc(k), l, mid, L, R);
    if (!(L <= mid) && mid < R)
        return ask(rc(k), mid + 1, r, L, R);
    Tree Lc = ask(lc(k), l, mid, L, R), Rc = ask(rc(k), mid + 1, r, L, R), Ans;
    int New = std::min(Lc.Lsum, Rc.Rsum);
    Ans.Lsum = Lc.Lsum + Rc.Lsum - New;
    Ans.Rsum = Lc.Rsum + Rc.Rsum - New;
    return Ans;
}
```
2. **作者：SunsetGlow95 (赞：11)  星级：4星**
    - **关键亮点**：将合法括号序列转化为数值序列及前缀和问题，利用RMQ维护区间最小值，给出了清晰的思路分析和公式推导，且提到了ST表和线段树不同时间复杂度。
    - **重点代码核心实现思想**：先将括号序列转化为前缀和数组，利用ST表预处理区间最值，查询时根据公式计算合法括号子序列长度。
    - **核心代码片段**：
```cpp
// ST表预处理
for (int i(1); i <= N; ++i) {
    if (str[i] == '(') st[i][0] = st[i - 1][0] + 1;
    else st[i][0] = st[i - 1][0] - 1;
}
for (int i(1); (1 << i) <= N; ++i) {
    for (int j(1); j + (1 << (i - 1)) <= N; ++j) {
        st[j][i] = min(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
    }
}
// 查询
for (int l(0), r(0); M--; ) {
    cin >> l >> r;
    int nmin(-min(query(l, r) - st[l - 1][0], 0));
    cout << (r - l + 1) - nmin - (st[r][0] - st[l - 1][0] + nmin) << endl;
}
```
3. **作者：LJC00118 (赞：5)  星级：4星**
    - **关键亮点**：同样采用线段树，思路独特地考虑将能匹配的括号删掉后剩余括号形如“))))))((((((((”，通过线段树维护区间内左边“)”个数、右边“(”个数及能匹配括号对数，区间合并时计算新增匹配对数。
    - **重点代码核心实现思想**：构建线段树时，叶节点根据字符确定左边“)”和右边“(”个数，非叶节点通过合并左右子节点信息更新。查询时，递归获取子区间信息并合并。
    - **核心代码片段**：
```cpp
// 构建线段树
void build(int u, int l, int r) {
    p[u].l = l; p[u].r = r;
    if (l == r) {
        p[u].val = ele(0, c[l] == ')', c[l] == '(');
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r);
    p[u].val = merge(p[u << 1].val, p[u << 1 | 1].val);
}
// 查询
ele query(int u, int l, int r) {
    if (l <= p[u].l && p[u].r <= r) return p[u].val;
    int mid = (p[u].l + p[u].r) >> 1; ele ans;
    if (mid >= l) ans = merge(ans, query(u << 1, l, r));
    if (mid + 1 <= r) ans = merge(ans, query(u << 1 | 1, l, r));
    return ans;
}
```

### 最优关键思路或技巧
1. **数据结构选择**：线段树能高效处理区间查询和更新问题，对于本题多个区间查询需求，通过合理定义节点信息（如未匹配括号数）和区间合并操作，可有效解决问题。
2. **问题转化**：将括号序列转化为数值序列并求前缀和，利用前缀和性质及区间最值维护，从另一角度巧妙解决问题，如结合RMQ或ST表。

### 同类型题或类似算法套路
1. 此类题目通常围绕括号序列的性质展开，可拓展到更复杂的括号匹配问题，如嵌套括号结构、多种括号类型匹配等。
2. 类似算法套路包括利用数据结构（线段树、ST表等）维护区间信息，或通过转化问题为其他熟悉模型（如数值序列前缀和）来求解。

### 洛谷相似题目
1. **P3372 【模板】线段树 1**：基础线段树模板题，用于巩固线段树的基本操作和区间查询更新理解。
2. **P3865 【模板】ST 表**：ST表模板题，帮助掌握ST表数据结构及其在区间最值查询中的应用。
3. **P2880 [USACO07MAR]Face The Right Way G**：可通过类似线段树维护区间信息思路解决，同时涉及贪心思想。

### 个人心得摘录与总结
1. **作者：Meatherm**：感慨自己出的题在Codeforces被找到原题，体现了题目积累和练习的重要性。
2. **作者：SunsetGlow95**：提到写错ST表取\(r\)时不考虑最后一个元素，在特定式子调整下也能通过，反映出对题目公式推导和代码细节的深入理解有助于发现一些特殊情况。 

---
处理用时：104.37秒