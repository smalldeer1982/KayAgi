# 题目信息

# Little Alawn's Puzzle

## 题目描述

When he's not training for IOI, Little Alawn enjoys playing with puzzles of various types to stimulate his brain. Today, he's playing with a puzzle that consists of a $ 2 \times n $ grid where each row is a permutation of the numbers $ 1,2,3,\ldots,n $ .

The goal of Little Alawn's puzzle is to make sure no numbers on the same column or row are the same (we'll call this state of the puzzle as solved), and to achieve this he is able to swap the numbers in any column. However, after solving the puzzle many times, Little Alawn got bored and began wondering about the number of possible solved configurations of the puzzle he could achieve from an initial solved configuration only by swapping numbers in a column.

Unfortunately, Little Alawn got stuck while trying to solve this harder problem, so he was wondering if you could help him with it. Find the answer modulo $ 10^9+7 $ .

## 说明/提示

The two possible puzzle configurations for example $ 1 $ are:

- $ [1,4,2,3] $ in the first row and $ [3,2,1,4] $ in the second;
- $ [3,2,1,4] $ in the first row and $ [1,4,2,3] $ in the second.

## 样例 #1

### 输入

```
2
4
1 4 2 3
3 2 1 4
8
2 6 5 1 4 3 7 8
3 8 7 5 1 2 4 6```

### 输出

```
2
8```

# AI分析结果

### 题目重写
【题目内容】
# Little Alawn的拼图

## 题目描述

当Little Alawn不为IOI训练时，他喜欢玩各种类型的拼图来刺激大脑。今天，他正在玩一个由$2 \times n$网格组成的拼图，其中每一行都是数字$1,2,3,\ldots,n$的排列。

Little Alawn的拼图目标是确保同一列或同一行中没有相同的数字（我们称这种状态为“已解决”），并且他可以通过交换任何列中的数字来实现这一目标。然而，在多次解决拼图后，Little Alawn感到无聊，并开始思考从初始已解决配置出发，仅通过交换列中的数字，可以得到多少种可能的已解决配置。

不幸的是，Little Alawn在尝试解决这个更难的问题时卡住了，所以他想知道你是否能帮助他。请找出答案，并对$10^9+7$取模。

## 说明/提示

示例$1$的两种可能的拼图配置为：

- 第一行$[1,4,2,3]$，第二行$[3,2,1,4]$；
- 第一行$[3,2,1,4]$，第二行$[1,4,2,3]$。

## 样例 #1

### 输入

```
2
4
1 4 2 3
3 2 1 4
8
2 6 5 1 4 3 7 8
3 8 7 5 1 2 4 6
```

### 输出

```
2
8
```

### 算法分类
并查集

### 题解分析与结论
本题的核心在于通过并查集找到所有相互关联的列，这些列构成了一个个环，每个环有交换和不交换两种选择，因此最终答案为$2^x$，其中$x$为环的数量。并查集的使用是解决该问题的关键，能够高效地找到所有环的数量。

### 所选高星题解
1. **作者：wmrqwq (5星)**
   - **关键亮点**：通过并查集维护连通块，思路清晰，代码简洁。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++)
         a[find(u[i])]=find(v[i]);
     map<int,int>mp;
     for(int i=1;i<=n;i++)
         if(!mp[find(i)])
             mp[find(i)]=1,ans*=2,ans%=mod;
     ```
   - **个人心得**：通过并查集维护连通块，最终答案为$2^x$，其中$x$为连通块的数量。

2. **作者：Acc_Robin (4星)**
   - **关键亮点**：使用并查集求解循环置换数，代码简洁，思路清晰。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++)T[i]=i;
     for(int i=1,x;i<=n;i++)cin>>x,unit(a[i],x);
     for(int i=1;i<=n;i++)r+=T[i]==i;
     cout<<qpow(2,r)<<'\n';
     ```
   - **个人心得**：每个循环置换有交换和不交换两种情况，答案为$2^{cnt}$。

3. **作者：StayAlone (4星)**
   - **关键亮点**：通过DFS找环，思路清晰，代码简洁。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++) if(!vis[i]) vis[i]=true, dfs(i), cnt++;
     ll ans = 1;
     for(int i=1;i<=cnt;i++) ans = ans * 2 % mod;
     ```
   - **个人心得**：每个环有选与不选两种方案，答案为$2^x$。

### 最优关键思路
通过并查集或DFS找到所有环的数量，最终答案为$2^x$，其中$x$为环的数量。并查集的使用是解决该问题的关键，能够高效地找到所有环的数量。

### 拓展思路
类似的问题可以通过并查集或DFS找到所有环的数量，最终答案为$2^x$。这种思路可以应用于其他需要找到相互关联的元素并计算方案数的问题。

### 推荐题目
1. [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)
2. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
3. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)

---
处理用时：36.96秒