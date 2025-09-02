# 题目信息

# [ABC278F] Shiritori

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc278/tasks/abc278_f

$ N $ 個の文字列 $ S\ _\ 1,S\ _\ 2,\ldots,S\ _\ N $ が与えられます。 $ S\ _\ i\ (1\leq\ i\leq\ N) $ は英小文字からなる長さ $ 10 $ 以下の空でない文字列で、互いに異なります。

先手太郎君と後手次郎君がしりとりをします。 このしりとりでは、先手太郎君と後手次郎君の手番が交互に訪れます。 はじめの手番は先手太郎君の手番です。 それぞれのプレイヤーは自分の手番において整数 $ i\ (1\leq\ i\leq\ N) $ を $ 1 $ つ選びます。 このとき、$ i $ は次の $ 2 $ つの条件を満たしていなければなりません。

- $ i $ は、しりとりが開始してからこれまでの $ 2 $ 人の手番で選ばれたどの整数とも異なる
- この手番がしりとりの最初の手番であるか、直前に選ばれた整数を $ j $ として、$ S\ _\ j $ の最後の文字と $ S\ _\ i $ の最初の文字が等しい
 
条件を満たす $ i $ を選べなくなったプレイヤーの負けで、負けなかったプレイヤーの勝ちです。

$ 2 $ 人が最適に行動したときに勝つのはどちらかを判定してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 16 $
- $ N $ は整数
- $ S\ _\ i\ (1\leq\ i\leq\ N) $ は英小文字からなる長さ $ 10 $ 以下の空でない文字列
- $ S\ _\ i\neq\ S\ _\ j\ (1\leq\ i\lt\ j\leq\ N) $
 
### Sample Explanation 1

例えば、ゲームは以下のように進行します。 この進行例では $ 2 $ 人の行動が必ずしも最適とは限らないことに注意してください。 - 先手太郎君が $ i=3 $ を選ぶ。$ S\ _\ i= $`if` である。 - 後手次郎君が $ i=2 $ を選ぶ。$ S\ _\ i= $`float` であり、`if` の最後の文字と `float` の最初の文字は等しい。 - 先手太郎君が $ i=5 $ を選ぶ。$ S\ _\ i= $`takahashi` であり、`float` の最後の文字と `takahashi` の最初の文字は等しい。 - 後手次郎君は $ i\neq2,3,5 $ であって $ S\ _\ i $ の最初の文字が `i` と等しいものを選べないため、負ける。 このとき、先手太郎君が勝ちます。

## 样例 #1

### 输入

```
6

enum

float

if

modint

takahashi

template```

### 输出

```
First```

## 样例 #2

### 输入

```
10

catch

chokudai

class

continue

copy

exec

havoc

intrinsic

static

yucatec```

### 输出

```
Second```

## 样例 #3

### 输入

```
16

mnofcmzsdx

lgeowlxuqm

ouimgdjxlo

jhwttcycwl

jbcuioqbsj

mdjfikdwix

jhvdpuxfil

peekycgxco

sbvxszools

xuuqebcrzp

jsciwvdqzl

obblxzjhco

ptobhnpfpo

muizaqtpgx

jtgjnbtzcl

sivwidaszs```

### 输出

```
First```

# AI分析结果

### 题目重写
【题目内容】
# [ABC278F] Shiritori

## 题目描述

给定 $N$ 个字符串 $S_1, S_2, \ldots, S_N$。每个字符串 $S_i$（$1 \leq i \leq N$）由小写字母组成，长度不超过 $10$，且互不相同。

先手太郎君和后手次郎君进行“しりとり”游戏。游戏规则如下：
- 先手太郎君和后手次郎君轮流选择字符串。
- 先手太郎君先手。
- 每次选择的字符串必须满足以下两个条件：
  1. 该字符串在之前的轮次中未被选择过。
  2. 如果是第一次选择，或者选择的字符串的首字母与上一次选择的字符串的最后一个字母相同。
- 无法选择满足条件的字符串的玩家输掉游戏，另一方获胜。

请判断在双方都采取最优策略的情况下，谁会获胜。

### 算法分类
动态规划、搜索、博弈论

### 题解分析与结论
本题的核心是通过动态规划或搜索来模拟博弈过程，判断在双方都采取最优策略的情况下谁会获胜。由于 $N \leq 16$，可以使用状态压缩来记录字符串的选择情况，并通过记忆化搜索或动态规划来优化计算。

### 精选题解
1. **作者：liangbowen (5星)**
   - **关键亮点**：使用状态压缩和记忆化搜索，思路清晰，代码简洁，优化到位。
   - **代码核心**：
     ```cpp
     bool dfs(int x, int lst) {
         if (vis[x][lst]) return ans[x][lst];
         for (int i = 1; i <= n; i++)
             if (!(x & (1 << (i - 1))))
                 if (lst == 0 || a[lst][a[lst].length() - 1] == a[i][0])
                     if (!dfs(x | (1 << (i - 1)), i))
                         {vis[x][lst] = true; return ans[x][lst] = true;}
         vis[x][lst] = true; return ans[x][lst] = false;
     }
     ```
   - **总结**：通过状态压缩和记忆化搜索，避免了重复计算，时间复杂度为 $O(2^N \times N)$。

2. **作者：StayAlone (4星)**
   - **关键亮点**：使用动态规划，状态转移方程清晰，代码结构良好。
   - **代码核心**：
     ```cpp
     int dfs(int b, int t) {
         if (~f[b][t]) return f[b][t];
         bool w = 0;
         rep1(i, 1, n) if (!((t >> i - 1) & 1) && (s[i][0] - 'a' + 1 == b || !b)) {
             w |= dfs(s[i][1] - 'a' + 1, t | (1 << i - 1)) ^ 1;
         } return f[b][t] = w; 
     }
     ```
   - **总结**：通过动态规划记录状态，避免了重复计算，时间复杂度为 $O(2^N \times N)$。

3. **作者：hejianxing (4星)**
   - **关键亮点**：使用倒序动态规划，思路独特，代码简洁。
   - **代码核心**：
     ```cpp
     for (int i = (1 << n) - 2; i >= 0; i--)
         for (int j = 0; j < n; j++)
             if ((i >> j) & 1) {
                 f[i][j] = 1;
                 for (int k = 0; k < n; k++)
                     if (k != j && !((i >> k) & 1) && a[k][l[k]] == a[j][0])
                         if (f[i ^ (1 << k)][k])
                             f[i][j] = 0;
             }
     ```
   - **总结**：通过倒序动态规划，避免了重复计算，时间复杂度为 $O(2^N \times N^2)$。

### 最优关键思路
使用状态压缩和记忆化搜索或动态规划来模拟博弈过程，避免重复计算，时间复杂度为 $O(2^N \times N)$。

### 拓展思路
类似的问题可以扩展到更大的 $N$ 或更复杂的规则，如允许重复选择字符串或增加其他限制条件。

### 推荐题目
1. [P1278 单词接龙](https://www.luogu.com.cn/problem/P1278)
2. [P1280 尼克的任务](https://www.luogu.com.cn/problem/P1280)
3. [P1281 书的复制](https://www.luogu.com.cn/problem/P1281)

### 个人心得摘录
- **liangbowen**：通过状态压缩和记忆化搜索，避免了重复计算，大大减少了时间复杂度。
- **StayAlone**：动态规划的状态转移方程清晰，代码结构良好，易于理解和维护。
- **hejianxing**：倒序动态规划的思路独特，代码简洁，适合处理类似的问题。

---
处理用时：32.77秒