# 题目信息

# [AGC063A] Mex Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc063/tasks/agc063_a

`A`, `B` からなる長さ $ N+1 $ の文字列 $ S\ =\ S_0\cdots\ S_N $ が与えられます． 各 $ k=1,\ \ldots,\ N $ に対して次の問題を解いてください：

> Alice と Bob が集合 $ X $ を使ってゲームをします．$ X $ ははじめ空集合で，$ t=1,\ldots,\ k $ の順に次の行動を行います．
> 
> - $ t $ が奇数ならば，Alice が非負整数 $ x $ を選び，$ X $ を $ X\cup\ \{x\} $ に置き換える．
> - $ t $ が偶数ならば，Bob が非負整数 $ x $ を選び，$ X $ を $ X\cup\ \{x\} $ に置き換える．
>  
> $ k $ 回すべての行動が終わった時点での $ \mathrm{mex}(X) $ を $ x $ とするとき，文字 $ S_x $ が `A` ならば Alice が，$ S_x $ が `B` ならば Bob が勝者となります．集合 $ X $ の要素数は $ k $ 以下であるため，$ x\ =\ \mathrm{mex}(X)\ \leq\ k $ が成り立つ（したがって文字 $ S_x $ が存在する）ことに注意してください．
> 
> 両者が最適に行動した場合の勝者の名前を出力してください．

   $ \mathrm{mex}(X) $ とは？ 非負整数からなる有限集合 $ X $ に対し，$ x\notin\ X $ を満たす最小の非負整数 $ x $ を $ \mathrm{mex}(X) $ と定義します．

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ S $ は `A`, `B` からなる長さ $ N+1 $ の文字列である．
 
### Sample Explanation 1

$ k=1 $ とした場合のゲームの進行例の一例を次に示します． - Alice が $ x=10 $ を選ぶ． - $ \mathrm{mex}(X)=\mathrm{mex}(\lbrace\ 10\rbrace)\ =\ 0 $ であり，$ S_0 $ は `A` なので，Alice が勝利する． $ k=2 $ とした場合のゲームの進行例の一例を次に示します． - Alice が $ x=2 $ を選ぶ． - Bob が $ x=0 $ を選ぶ． - $ \mathrm{mex}(X)=\mathrm{mex}(\lbrace\ 0,2\rbrace)\ =\ 1 $ であり，$ S_1 $ は `B` なので，Bob が勝利する．

## 样例 #1

### 输入

```
2

ABB```

### 输出

```
Alice

Bob```

## 样例 #2

### 输入

```
4

AAAAA```

### 输出

```
Alice

Alice

Alice

Alice```

## 样例 #3

### 输入

```
7

BBAABABA```

### 输出

```
Bob

Bob

Alice

Bob

Alice

Bob

Alice```

# AI分析结果

### 题目翻译

给定一个由字符 `A` 和 `B` 组成的长度为 $N+1$ 的字符串 $S = S_0\cdots S_N$。对于每个 $k=1,\ldots,N$，解决以下问题：

Alice 和 Bob 使用集合 $X$ 进行游戏。$X$ 初始为空集，$t=1,\ldots,k$ 时依次执行以下操作：

- 如果 $t$ 是奇数，Alice 选择一个非负整数 $x$，并将 $X$ 替换为 $X \cup \{x\}$。
- 如果 $t$ 是偶数，Bob 选择一个非负整数 $x$，并将 $X$ 替换为 $X \cup \{x\}$。

在所有 $k$ 次操作结束后，设 $x = \mathrm{mex}(X)$，如果字符 $S_x$ 是 `A`，则 Alice 获胜；如果 $S_x$ 是 `B`，则 Bob 获胜。注意，集合 $X$ 的元素个数不超过 $k$，因此 $x = \mathrm{mex}(X) \leq k$，且字符 $S_x$ 存在。

$\mathrm{mex}(X)$ 的定义是：对于非负整数构成的有限集合 $X$，$\mathrm{mex}(X)$ 是满足 $x \notin X$ 的最小非负整数 $x$。

### 题解分析与结论

#### 综合分析
所有题解的核心思路都是通过统计字符串中 `A` 和 `B` 的数量来决定每轮的胜者。由于 $\mathrm{mex}(X)$ 的定义，集合中的数不会成为 $\mathrm{mex}(X)$，因此 Alice 和 Bob 会分别选择对方字符的下标来减少对方的获胜机会。最终，通过比较 `A` 和 `B` 的数量来决定胜者。

#### 最优关键思路
1. **贪心策略**：Alice 和 Bob 分别选择对方字符的最小下标，以减少对方的获胜机会。
2. **统计比较**：通过统计字符串中 `A` 和 `B` 的数量，直接比较两者的数量来决定胜者。
3. **简化问题**：将问题转化为简单的字符统计问题，避免了复杂的集合操作。

#### 推荐题解
1. **作者：chinazhanghaoxun (赞：6)**
   - **星级**：★★★★★
   - **关键亮点**：思路清晰，代码简洁，直接通过统计 `A` 和 `B` 的数量来决定胜者，避免了复杂的模拟过程。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n;i++){ 
         (s[i]=='A') ? cnta++ : cntb++;
         if(cnta>=cntb) puts("Alice"); 
         else  puts("Bob");
     }
     ```

2. **作者：yuheng_wang080904 (赞：2)**
   - **星级**：★★★★
   - **关键亮点**：详细分析了 Alice 和 Bob 的操作次数，并给出了具体的判断条件，逻辑清晰。
   - **代码核心**：
     ```cpp
     for(int i=0;i<=n;i++){
         cnta+=(s[i]=='A');
         cntb+=(s[i]=='B');
         if(i==0)continue;
         if(cnta>=cntb)cout<<"Alice"<<endl;
         else cout<<"Bob"<<endl;
     }
     ```

3. **作者：goIdie (赞：1)**
   - **星级**：★★★★
   - **关键亮点**：简化了问题，直接比较 `A` 和 `B` 的数量，代码简洁明了。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n;i++){
         if(s[i]=='A') cnta++; 
         else cntb++; 
         if(cnta>=cntb) cout<<"Alice"<<endl; 
         else cout<<"Bob"<<endl;
     }
     ```

### 扩展思路与推荐题目
1. **扩展思路**：本题的核心是通过贪心策略和统计比较来简化问题，类似的思路可以应用于其他博弈论问题或需要优化选择策略的题目。
2. **推荐题目**：
   - [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：考察动态规划和路径选择。
   - [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的背包问题，考察贪心和动态规划。
   - [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)：考察贪心策略和优化选择。

---
处理用时：41.47秒