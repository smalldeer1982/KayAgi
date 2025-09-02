# 题目信息

# Meximum Array

## 题目描述

Mihai has just learned about the [MEX](https://en.wikipedia.org/wiki/Mex_(mathematics)) concept and since he liked it so much, he decided to use it right away.

Given an array $ a $ of $ n $ non-negative integers, Mihai wants to create a new array $ b $  that is formed in the following way:

While $ a $ is not empty:

- Choose an integer $ k $ ( $ 1 \leq k \leq |a| $ ).
- Append the MEX of the first $ k $ numbers of the array $ a $ to the end of array $ b $ and erase them from the array $ a $ , shifting the positions of the remaining numbers in $ a $ .

But, since Mihai loves big arrays as much as the MEX concept, he wants the new array $ b $ to be the lexicographically maximum. So, Mihai asks you to tell him what the maximum array $ b $ that can be created by constructing the array optimally is.

An array $ x $ is lexicographically greater than an array $ y $ if in the first position where $ x $ and $ y $ differ $ x_i > y_i $ or if $ |x| > |y| $ and $ y $ is a prefix of $ x $ (where $ |x| $ denotes the size of the array $ x $ ).

The MEX of a set of non-negative integers is the minimal non-negative integer such that it is not in the set. For example, MEX({ $ {1, 2, 3} $ }) $ = 0 $ and MEX({ $ {0, 1, 2, 4, 5} $ }) $ = 3 $ .

## 说明/提示

In the first test case, the lexicographically maximum array $ b $ is obtained by selecting $ k=5 $ , resulting in the $ MEX $ of the whole array $ a $ . It is lexicographically maximum because an array starting with a smaller number than $ 4 $ is lexicographically smaller, and choosing a $ k<5 $ would result in an array starting with a number smaller than $ 4 $ .

In the second test case, there are two ways to obtain the maximum array: first selecting $ k=6 $ , then $ k=2 $ , or first selecting $ k=7 $ and then $ k=1 $ .

## 样例 #1

### 输入

```
6
5
1 0 2 0 3
8
2 2 3 4 0 1 2 0
1
1
5
0 1 2 3 4
4
0 1 1 0
10
0 0 2 1 1 1 0 0 1 1```

### 输出

```
1
4 
2
5 1 
1
0 
1
5 
2
2 2 
4
3 2 2 0```

# AI分析结果

### 题目内容中文重写

# Meximum Array

## 题目描述

Mihai 刚刚学习了 [MEX](https://en.wikipedia.org/wiki/Mex_(mathematics)) 的概念，并且非常喜欢它，因此他决定立即使用它。

给定一个包含 $n$ 个非负整数的数组 $a$，Mihai 想要创建一个新的数组 $b$，其构造方式如下：

当 $a$ 不为空时：

- 选择一个整数 $k$（$1 \leq k \leq |a|$）。
- 将数组 $a$ 的前 $k$ 个数的 MEX 附加到数组 $b$ 的末尾，并将它们从数组 $a$ 中删除，同时将 $a$ 中剩余数字的位置进行移位。

由于 Mihai 喜欢大数组，他希望你告诉他通过最优构造得到的最大字典序数组 $b$ 是什么。

一个数组 $x$ 在字典序上大于数组 $y$，如果 $x$ 和 $y$ 在第一个不同的位置上 $x_i > y_i$，或者如果 $|x| > |y|$ 且 $y$ 是 $x$ 的前缀（其中 $|x|$ 表示数组 $x$ 的大小）。

一个非负整数集合的 MEX 是该集合中缺失的最小非负整数。例如，MEX({$1, 2, 3$}) $= 0$，MEX({$0, 1, 2, 4, 5$}) $= 3$。

## 说明/提示

在第一个测试用例中，通过选择 $k=5$，得到整个数组 $a$ 的 MEX，从而得到字典序最大的数组 $b$。这是因为以小于 $4$ 的数字开头的数组在字典序上更小，而选择 $k<5$ 会导致数组以小于 $4$ 的数字开头。

在第二个测试用例中，有两种方式可以得到最大数组：首先选择 $k=6$，然后选择 $k=2$，或者首先选择 $k=7$，然后选择 $k=1$。

## 样例 #1

### 输入

```
6
5
1 0 2 0 3
8
2 2 3 4 0 1 2 0
1
1
5
0 1 2 3 4
4
0 1 1 0
10
0 0 2 1 1 1 0 0 1 1```

### 输出

```
1
4 
2
5 1 
1
0 
1
5 
2
2 2 
4
3 2 2 0```

### 算法分类
贪心

### 题解分析与结论

本题的核心在于如何通过贪心策略构造出字典序最大的数组 $b$。各题解的主要思路都是通过贪心选择 MEX 最大的前缀，并尽可能减少删除的元素数量，以保证后续的 MEX 尽可能大。

### 所选高星题解

#### 题解作者：vectorwyx (赞：5)
- **星级**：5星
- **关键亮点**：
  - 使用 deque 维护每个值的位置序列，按值从小到大遍历直到遇到空的 deque，确定 MEX。
  - 通过贪心策略选择最靠左的与整体 MEX 相同的位置对应的前缀删除。
  - 时间复杂度 $O(n)$，效率高。
- **核心代码**：
```cpp
void solve(){
    cin>>n;fo(i,1,n) g[i].clear();
    fo(i,1,n) a[i]=read(),g[a[i]].pb(i);
    int pos=0;m=0;
    while(pos<n){
        int t=pos;
        fo(i,0,n){
            if(g[i].empty()){
                b[++m]=i;
                break;
            } 
            big(pos,g[i][0]);
        }
        big(pos,t+1);
        fo(i,0,n){
            if(g[i].empty()) break;
            while(!g[i].empty()&&g[i][0]<=pos) g[i].pop_front();
        }
    }
    cout<<m<<'\n';out(b,1,m);
}
```

#### 题解作者：cqbzhzf (赞：1)
- **星级**：4星
- **关键亮点**：
  - 使用 vector 上二分查找，快速确定前缀的 MEX。
  - 通过贪心策略选择最短的前缀，使得 MEX 最大。
  - 时间复杂度 $O(n \log n)$，代码简洁。
- **核心代码**：
```cpp
int lb(int x,int L)
{
    int l=0,r=v[x].size()-1;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(v[x][mid]<=L)
            l=mid+1;
        else 
            r=mid-1;
    }
    return (l>=v[x].size())?(n+1):v[x][l];
}
```

### 最优关键思路与技巧
- **贪心策略**：每次选择 MEX 最大的前缀，并尽可能减少删除的元素数量。
- **数据结构**：使用 deque 或 vector 维护每个值的位置序列，快速确定 MEX。
- **时间复杂度优化**：通过合理的数据结构和算法设计，将时间复杂度优化到 $O(n)$ 或 $O(n \log n)$。

### 可拓展之处
- 类似问题可以扩展到多维数组或更复杂的 MEX 计算场景。
- 可以结合其他贪心策略或动态规划，解决更复杂的字典序最大化问题。

### 推荐题目
1. [P4137 Rmq Problem / mex](https://www.luogu.com.cn/problem/P4137)
2. [P5495 Dirichlet 前缀和](https://www.luogu.com.cn/problem/P5495)
3. [P5496 序列自动机](https://www.luogu.com.cn/problem/P5496)

---
处理用时：39.93秒