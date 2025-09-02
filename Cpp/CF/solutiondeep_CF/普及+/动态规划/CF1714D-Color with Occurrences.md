# 题目信息

# Color with Occurrences

## 题目描述

You are given some text $ t $ and a set of $ n $ strings $ s_1, s_2, \dots, s_n $ .

In one step, you can choose any occurrence of any string $ s_i $ in the text $ t $ and color the corresponding characters of the text in red. For example, if $ t=\texttt{bababa} $ and $ s_1=\texttt{ba} $ , $ s_2=\texttt{aba} $ , you can get $ t=\color{red}{\texttt{ba}}\texttt{baba} $ , $ t=\texttt{b}\color{red}{\texttt{aba}}\texttt{ba} $ or $ t=\texttt{bab}\color{red}{\texttt{aba}} $ in one step.

You want to color all the letters of the text $ t $ in red. When you color a letter in red again, it stays red.

In the example above, three steps are enough:

- Let's color $ t[2 \dots 4]=s_2=\texttt{aba} $ in red, we get $ t=\texttt{b}\color{red}{\texttt{aba}}\texttt{ba} $ ;
- Let's color $ t[1 \dots 2]=s_1=\texttt{ba} $ in red, we get $ t=\color{red}{\texttt{baba}}\texttt{ba} $ ;
- Let's color $ t[4 \dots 6]=s_2=\texttt{aba} $ in red, we get $ t=\color{red}{\texttt{bababa}} $ .

Each string $ s_i $ can be applied any number of times (or not at all). Occurrences for coloring can intersect arbitrarily.

Determine the minimum number of steps needed to color all letters $ t $ in red and how to do it. If it is impossible to color all letters of the text $ t $ in red, output -1.

## 说明/提示

The first test case is explained in the problem statement.

In the second test case, it is impossible to color all the letters of the text in red.

## 样例 #1

### 输入

```
6
bababa
2
ba
aba
caba
2
bac
acab
abacabaca
3
aba
bac
aca
baca
3
a
c
b
codeforces
4
def
code
efo
forces
aaaabbbbcccceeee
4
eeee
cccc
aaaa
bbbb```

### 输出

```
3
2 2
1 1
2 4
-1
4
1 1
2 6
3 3
3 7
4
3 1
1 2
2 3
1 4
2
4 5
2 1
4
3 1
4 5
2 9
1 13```

# AI分析结果

### 题目内容重写
给定一个字符串 $t$ 和 $n$ 个字符串 $s_1, s_2, \dots, s_n$。每次操作可以选择 $t$ 中任意一个与 $s_i$ 相等的子串，并将其染成红色。同一个字符可以被多次染色，但染色后始终为红色。求将 $t$ 中所有字符染成红色的最小操作次数，并输出具体方案。如果无法将所有字符染成红色，则输出 -1。

### 样例
输入：
```
6
bababa
2
ba
aba
caba
2
bac
acab
abacabaca
3
aba
bac
aca
baca
3
a
c
b
codeforces
4
def
code
efo
forces
aaaabbbbcccceeee
4
eeee
cccc
aaaa
bbbb
```

输出：
```
3
2 2
1 1
2 4
-1
4
1 1
2 6
3 3
3 7
4
3 1
1 2
2 3
1 4
2
4 5
2 1
4
3 1
4 5
2 9
1 13
```

### 题解分析与结论
本题的核心问题是如何用最少的操作次数将字符串 $t$ 中的所有字符染成红色。由于 $t$ 和 $s_i$ 的长度都较小，可以采用动态规划或贪心算法来解决。

#### 动态规划思路
动态规划的思路是设 $dp[i]$ 表示将 $t$ 的前 $i$ 个字符染成红色的最小操作次数。转移时，枚举所有可能的 $s_j$，如果 $s_j$ 能够匹配 $t$ 的某个子串，则更新 $dp[i]$。同时，记录转移路径以便输出方案。

#### 贪心思路
贪心的思路是将问题转化为区间覆盖问题。首先找出所有 $s_j$ 在 $t$ 中的匹配位置，然后选择最长的覆盖区间，逐步覆盖整个字符串 $t$。

### 评分较高的题解
1. **作者：Tx_Lcy (5星)**
   - **关键亮点**：使用了动态规划的思路，代码简洁且易于理解。通过 $pre[i]$ 数组记录转移路径，便于输出方案。
   - **代码核心**：
     ```cpp
     for (int i=1;i<=n;++i)
         for (int j=1;j<=k;++j)
             if (i>=t[j].length()){
                 if (s.substr(i-t[j].length()+1,t[j].length())==t[j])
                     for (int l=(int)(i-t[j].length());l<i;++l)
                         if (f[l]+1<f[i]){
                             f[i]=f[l]+1;
                             pre[i]=l;
                             a[i]={i-t[j].length()+1,j};
                         }
             }
     ```

2. **作者：__KrNalty__ (4星)**
   - **关键亮点**：将问题转化为区间覆盖问题，使用贪心算法解决。思路清晰，代码实现较为直观。
   - **代码核心**：
     ```cpp
     while (left <= len) {
         int pos = 0;
         for (int i = 1; i <= cnt; i++) {
             if (l[i] <= left) {
                 if (r[i] > right) {
                     right = r[i];
                     pos = i;
                 }
             }
         }
         anss.push_back(pos);
         left = right + 1;
         ans++;
     }
     ```

3. **作者：Dr_Gilbert (4星)**
   - **关键亮点**：动态规划的实现较为详细，预处理了匹配信息，优化了转移过程。代码结构清晰，适合初学者理解。
   - **代码核心**：
     ```cpp
     for (int i = 1; i <= n; i++) {
         for (int j = 1; j <= m; j++) {
             if (!flag[i][j]) continue;
             for (int k = i - len[j]; k < i; k++) {
                 if (dp[k] + 1 < dp[i]) {
                     from[i] = k;
                     type[i] = j;
                     dp[i] = dp[k] + 1;
                 }
             }
         }
     }
     ```

### 最优关键思路
动态规划是解决该问题的最优思路，通过状态转移和路径记录，能够高效地求解最小操作次数并输出方案。贪心算法虽然思路简单，但在某些情况下可能无法保证最优解。

### 拓展思路
类似的问题可以扩展到更复杂的字符串匹配或区间覆盖问题，如多次覆盖、重叠覆盖等。可以考虑使用更高效的字符串匹配算法（如KMP）来优化匹配过程。

### 推荐题目
1. [P1514 引水入城](https://www.luogu.com.cn/problem/P1514) - 区间覆盖问题
2. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375) - 字符串匹配
3. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040) - 动态规划与区间覆盖

---
处理用时：44.80秒