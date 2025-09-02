# 题目信息

# [ABC302C] Almost Equal

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc302/tasks/abc302_c

英小文字からなる長さ $ M $ の文字列 $ N $ 個 $ S_1,S_2,\dots,S_N $ が与えられます。ここで、$ S_i $ は互いに異なります。

これらを並び替えた文字列の列 $ T_1,T_2,\dots,T_N $ であって、以下の条件を満たすものが存在するか判定してください。

- $ 1\ \le\ i\ \le\ N-1 $ を満たす全ての整数 $ i $ に対して、$ T_i $ を $ 1 $ 文字だけ別の英小文字に変えて $ T_{i+1} $ にすることが出来る。

## 说明/提示

### 制約

- $ 2\ \le\ N\ \le\ 8 $
- $ 1\ \le\ M\ \le\ 5 $
- $ S_i $ は英小文字からなる長さ $ M $ の文字列である。$ (1\ \le\ i\ \le\ N) $
- $ S_i $ は互いに異なる。

### Sample Explanation 1

`abcd` , `abed` , `bbed` , `fbed` の順に並び替えると条件を満たします。

### Sample Explanation 2

どのように並び替えても条件を満たすことは出来ません。

## 样例 #1

### 输入

```
4 4
bbed
abcd
abed
fbed```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 5
abcde
abced```

### 输出

```
No```

## 样例 #3

### 输入

```
8 4
fast
face
cast
race
fact
rice
nice
case```

### 输出

```
Yes```

# AI分析结果

### 题目内容重写
给定 $N$ 个长度为 $M$ 的字符串，要求判断是否存在一种排列方式，使得相邻的两个字符串之间只有一个字符不同。

### 算法分类
搜索

### 题解分析与结论
本题的核心是通过搜索（如深度优先搜索或全排列枚举）来找到符合条件的字符串排列。由于 $N$ 和 $M$ 的范围都很小，直接暴力搜索是可行的。大多数题解都采用了全排列枚举的方式，通过 `next_permutation` 或递归 DFS 来生成所有可能的排列，并逐一检查是否满足条件。

### 评分较高的题解
1. **作者：FreedomKing (赞：2)**
   - **星级：4**
   - **关键亮点：** 使用了 `next_permutation` 来枚举全排列，代码简洁且易于理解。通过排序预处理，确保 `next_permutation` 的正确使用。
   - **核心代码：**
     ```cpp
     do {
         bool flag = true;
         for (int i = 1; i < n; i++) {
             int k = 0;
             for (int j = 0; j < m; j++)
                 if (s[i][j] != s[i+1][j]) k++;
             if (k > 1) flag = false;
         }
         if (flag) {
             cout << "Yes";
             return 0;
         }
     } while (next_permutation(s+1, s+n+1));
     ```
   - **个人心得：** 强调了 `next_permutation` 的使用前提是序列已经有序，否则可能导致遗漏。

2. **作者：happybob (赞：1)**
   - **星级：4**
   - **关键亮点：** 同样使用了 `next_permutation`，代码结构清晰，判断条件简洁明了。
   - **核心代码：**
     ```cpp
     do {
         bool f = 1;
         for (int i = 1; i < n; i++) {
             if (cntdif(s[i], s[i+1]) != 1) {
                 f = 0;
                 break;
             }
         }
         if (f) {
             printf("Yes\n");
             return 0;
         }
     } while (next_permutation(s+1, s+n+1));
     ```
   - **个人心得：** 无特别心得，但代码实现简洁，易于理解。

3. **作者：c1ampy (赞：1)**
   - **星级：4**
   - **关键亮点：** 提供了两种解法，暴力全排列和基于图论的解法。图论解法通过判断图的连通性来优化时间复杂度。
   - **核心代码：**
     ```cpp
     void dfs(const int cur) {
         ++dfn;
         visited[cur] = true;
         for (int i = head[cur]; i; i = edge[i].next) {
             int to = edge[i].to;
             if (!visited[to]) {
                 dfs(to);
             }
         }
     }
     ```
   - **个人心得：** 提供了更优的图论解法，虽然本题数据范围小，暴力解法已足够，但图论解法展示了更通用的思路。

### 最优关键思路
1. **全排列枚举：** 使用 `next_permutation` 或递归 DFS 生成所有可能的排列，逐一检查相邻字符串是否只有一个字符不同。
2. **图论优化：** 将字符串之间的关系抽象成图，判断图的连通性，适用于更大规模的数据。

### 拓展思路
类似问题可以通过图论中的哈密尔顿路径或欧拉路径来解决，特别是当数据规模较大时，图论方法可以显著提高效率。

### 推荐题目
1. [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
3. [P1037 产生数](https://www.luogu.com.cn/problem/P1037)

---
处理用时：23.92秒