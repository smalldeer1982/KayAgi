# 题目信息

# Restoring the Permutation

## 题目描述

A permutation is a sequence of $ n $ integers from $ 1 $ to $ n $ , in which all numbers occur exactly once. For example, $ [1] $ , $ [3, 5, 2, 1, 4] $ , $ [1, 3, 2] $ are permutations, and $ [2, 3, 2] $ , $ [4, 3, 1] $ , $ [0] $ are not.

Polycarp was presented with a permutation $ p $ of numbers from $ 1 $ to $ n $ . However, when Polycarp came home, he noticed that in his pocket, the permutation $ p $ had turned into an array $ q $ according to the following rule:

- $ q_i = \max(p_1, p_2, \ldots, p_i) $ .

Now Polycarp wondered what lexicographically minimal and lexicographically maximal permutations could be presented to him.

An array $ a $ of length $ n $ is lexicographically smaller than an array $ b $ of length $ n $ if there is an index $ i $ ( $ 1 \le i \le n $ ) such that the first $ i-1 $ elements of arrays $ a $ and $ b $ are the same, and the $ i $ -th element of the array $ a $ is less than the $ i $ -th element of the array $ b $ . For example, the array $ a=[1, 3, 2, 3] $ is lexicographically smaller than the array $ b=[1, 3, 4, 2] $ .

For example, if $ n=7 $ and $ p=[3, 2, 4, 1, 7, 5, 6] $ , then $ q=[3, 3, 4, 4, 7, 7, 7] $ and the following permutations could have been as $ p $ initially:

- $ [3, 1, 4, 2, 7, 5, 6] $ (lexicographically minimal permutation);
- $ [3, 1, 4, 2, 7, 6, 5] $ ;
- $ [3, 2, 4, 1, 7, 5, 6] $ ;
- $ [3, 2, 4, 1, 7, 6, 5] $ (lexicographically maximum permutation).

For a given array $ q $ , find the lexicographically minimal and lexicographically maximal permutations that could have been originally presented to Polycarp.

## 样例 #1

### 输入

```
4
7
3 3 4 4 7 7 7
4
1 2 3 4
7
3 4 5 5 5 7 7
1
1```

### 输出

```
3 1 4 2 7 5 6 
3 2 4 1 7 6 5 
1 2 3 4 
1 2 3 4 
3 4 5 1 2 7 6 
3 4 5 2 1 7 6 
1 
1```

# AI分析结果

### 题目内容重写
#### 恢复排列

##### 题目描述
一个排列是一个包含 $1$ 到 $n$ 的整数序列，其中所有数字恰好出现一次。例如，$[1]$、$[3, 5, 2, 1, 4]$、$[1, 3, 2]$ 是排列，而 $[2, 3, 2]$、$[4, 3, 1]$、$[0]$ 不是。

Polycarp 被展示了一个从 $1$ 到 $n$ 的排列 $p$。然而，当他回到家时，他注意到口袋里的排列 $p$ 变成了一个数组 $q$，规则如下：
- $q_i = \max(p_1, p_2, \ldots, p_i)$。

现在 Polycarp 想知道，最初展示给他的排列可能是哪些字典序最小和字典序最大的排列。

一个长度为 $n$ 的数组 $a$ 字典序小于另一个长度为 $n$ 的数组 $b$，如果存在一个索引 $i$（$1 \le i \le n$），使得数组 $a$ 和 $b$ 的前 $i-1$ 个元素相同，且数组 $a$ 的第 $i$ 个元素小于数组 $b$ 的第 $i$ 个元素。例如，数组 $a=[1, 3, 2, 3]$ 字典序小于数组 $b=[1, 3, 4, 2]$。

例如，如果 $n=7$ 且 $p=[3, 2, 4, 1, 7, 5, 6]$，那么 $q=[3, 3, 4, 4, 7, 7, 7]$，且以下排列可能是最初展示给 Polycarp 的：
- $[3, 1, 4, 2, 7, 5, 6]$（字典序最小排列）；
- $[3, 1, 4, 2, 7, 6, 5]$；
- $[3, 2, 4, 1, 7, 5, 6]$；
- $[3, 2, 4, 1, 7, 6, 5]$（字典序最大排列）。

对于给定的数组 $q$，找出最初可能展示给 Polycarp 的字典序最小和字典序最大的排列。

##### 样例 #1
###### 输入
```
4
7
3 3 4 4 7 7 7
4
1 2 3 4
7
3 4 5 5 5 7 7
1
1
```

###### 输出
```
3 1 4 2 7 5 6 
3 2 4 1 7 6 5 
1 2 3 4 
1 2 3 4 
3 4 5 1 2 7 6 
3 4 5 2 1 7 6 
1 
1
```

### 算法分类
贪心

### 题解分析与结论
#### 综合分析与结论
本题的核心在于如何根据给定的前缀最大值数组 $q$，构造出字典序最小和字典序最大的排列。主要思路是通过贪心策略，分别选择当前可用的最小或最大数来填充排列。

#### 所选题解
1. **作者：Cutest_Junior (赞：1)**
   - **星级：4**
   - **关键亮点：**
     - 使用栈来维护字典序最大排列的候选数。
     - 使用指针和标记数组来维护字典序最小排列的候选数。
     - 代码结构清晰，易于理解。
   - **核心代码：**
     ```cpp
     void solve() {
         int n;
         scanf("%d", &n);
         for (int i = 1; i <= n; ++i) {
             scanf("%d", &a[i]);
         }
         memset(b, 0, sizeof b);
         int minn = 1;
         for (int i = 1; i <= n; ++i) {
             if (!b[a[i]]) {
                 printf("%d ", a[i]);
                 b[a[i]] = 1;
             }
             else {
                 while (b[minn]) {
                     ++minn;
                 }
                 printf("%d ", minn);
                 b[minn] = 1;
             }
         }
         printf("\n");
         stack s;
         a[0] = 0;
         for (int i = 1; i <= n; ++i) {
             if (a[i] != a[i - 1]) {
                 printf("%d ", a[i]);
                 b[a[i]] = 1;
                 for (int j = a[i - 1] + 1; j < a[i]; ++j) {
                     s.push(j);
                 }
             }
             else {
                 printf("%d ", s.top());
                 s.pop();
             }
         }
         printf("\n");
     }
     ```

2. **作者：wmrqwq (赞：0)**
   - **星级：4**
   - **关键亮点：**
     - 使用优先队列维护字典序最大排列的候选数。
     - 使用指针和标记数组来维护字典序最小排列的候选数。
     - 时间复杂度为 $O(n \log n)$，适合大数据量。
   - **核心代码：**
     ```cpp
     void solve() {
         while(!q.empty())
             q.pop();
         cin>>n;
         forl(i,1,n)
             cin>>a[i];
         ma=0,L=1;
         forl(i,1,n)
             vis[i]=0;
         forl(i,1,n) {
             if(ma!=a[i]) {
                 cout<<a[i]<<' ';
                 vis[a[i]]=1;
                 ma=a[i];
                 continue;
             }
             else {
                 while(vis[L])
                     L++;
                 cout<<L<<' ';
                 vis[L]=1;
             }
         }
         cout<<endl;
         ma=0,R=n;
         forl(i,1,n)
             vis[i]=0;
         forl(i,1,n) {
             if(ma!=a[i]) {
                 cout<<a[i]<<' ';
                 vis[a[i]]=1;
                 forl(j,ma+1,a[i])
                     if(!vis[j])
                         q.push(j);
                 ma=a[i];
                 continue;
             }
             else {
                 while(!q.empty()) {
                     ll num=q.top();
                     q.pop();
                     if(!vis[num]) {
                         cout<<num<<' ';
                         vis[num]=1;
                         break;
                     }		
                 }		
             }
         }
         cout<<endl;
     }
     ```

3. **作者：hswfwkj_ (赞：0)**
   - **星级：4**
   - **关键亮点：**
     - 使用链表来维护字典序最大排列的候选数。
     - 使用指针和标记数组来维护字典序最小排列的候选数。
     - 时间复杂度为 $O(n)$，效率较高。
   - **核心代码：**
     ```cpp
     void solve() {
         memset(d,0,sizeof(d));
         int p=1;
         cin>>n;
         for(int i=1;i<=n;i++)
             cin>>q[i];
         for(int i=1;i<=n;i++) {
             if(!d[q[i]]) {
                 d[q[i]]=1;
                 cout<<q[i]<<' ';
             }
             else {
                 while(d[p])p++;
                 d[p]=1;
                 cout<<p++<<' ';
             }
         }
         cout<<'\n';
         memset(d,0,sizeof(d));
         for(int i=1;i<=n;i++)
             nxt[i]=i-1,last[i]=i+1;
         for(int i=1;i<=n;i++) {
             if(!d[q[i]]) {
                 cout<<q[i]<<' ';
                 d[q[i]]=1;
                 nxt[last[q[i]]]=nxt[q[i]];
                 last[nxt[q[i]]]=last[q[i]];
             }
             else {
                 cout<<nxt[q[i]]<<' ';
                 nxt[last[nxt[q[i]]]]=nxt[nxt[q[i]]];
                 last[nxt[nxt[q[i]]]]=last[nxt[q[i]]];
                 nxt[q[i]]=nxt[nxt[q[i]]];
             }
         }
         cout<<'\n';
     }
     ```

### 最优关键思路或技巧
- **贪心策略：** 通过选择当前可用的最小或最大数来填充排列，确保字典序最小或最大。
- **数据结构选择：** 使用栈、优先队列或链表来维护候选数，提高效率。
- **时间复杂度优化：** 通过合理的数据结构选择，将时间复杂度优化到 $O(n)$ 或 $O(n \log n)$。

### 可拓展之处
- **类似题目：** 可以扩展到其他需要构造特定性质排列的问题，如构造特定顺序的排列、满足特定条件的排列等。
- **算法套路：** 贪心策略在构造类问题中广泛应用，可以结合其他数据结构如堆、栈、链表等进行优化。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

---
处理用时：74.06秒