# 题目信息

# Game with Reversing

## 题目描述

Alice and Bob are playing a game. They have two strings $ S $ and $ T $ of the same length $ n $ consisting of lowercase latin letters. Players take turns alternately, with Alice going first.

On her turn, Alice chooses an integer $ i $ from $ 1 $ to $ n $ , one of the strings $ S $ or $ T $ , and any lowercase latin letter $ c $ , and replaces the $ i $ -th symbol in the chosen string with the character $ c $ .

On his turn, Bob chooses one of the strings $ S $ or $ T $ , and reverses it. More formally, Bob makes the replacement $ S := \operatorname{rev}(S) $ or $ T := \operatorname{rev}(T) $ , where $ \operatorname{rev}(P) = P_n P_{n-1} \ldots P_1 $ .

The game lasts until the strings $ S $ and $ T $ are equal. As soon as the strings become equal, the game ends instantly.

Define the duration of the game as the total number of moves made by both players during the game. For example, if Alice made $ 2 $ moves in total, and Bob made $ 1 $ move, then the duration of this game is $ 3 $ .

Alice's goal is to minimize the duration of the game, and Bob's goal is to maximize the duration of the game.

What will be the duration of the game, if both players play optimally? It can be shown that the game will end in a finite number of turns.

## 说明/提示

In the first test case, in her turn, Alice can replace the third symbol of the string $ S $ with x. After that, both strings will become equal to "abxde" and the game will end after one move. Since Alice's goal is to finish the game in as few moves as possible, this move will be one of her optimal first moves, and the final answer will be $ 1 $ .

In the second test case, in her turn, Alice can replace the fifth symbol of the string $ T $ with h. After this move, $ S = $ "hello", $ T = $ "olleh". Then Bob makes his turn. In his turn, he must reverse one of the strings. If Bob chooses the string $ S $ , then after his turn both strings will be equal to "olleh", and if he chooses the string $ T $ , then after his turn both strings will be equal to "hello". Thus, after the presented first move of Alice, the game will definitely end in $ 2 $ moves. It can be shown that there is no strategy for Alice to finish the game in less than $ 2 $ moves, with both players playing optimally. The final answer is $ 2 $ .

In the third test case, in her first move, Alice can replace the second symbol of the string $ S $ with c. After this move, $ S = $ "ac", $ T = $ "cd". Then Bob makes his turn. If Bob reverses the string $ S $ , then after his turn $ S = $ "ca", $ T = $ "cd". Then it is easy to see that in this case Alice can definitely finish the game on the $ 3 $ -rd move, by replacing the second symbol of the string $ T $ with a, after which both strings will become equal to "ca". If Bob reverses the string $ T $ , then after his turn $ S = $ "ac", $ T = $ "dc". In this case, Alice can also definitely finish the game on the $ 3 $ rd move, by replacing the first symbol of the string $ S $ with d, after which both strings will become equal to "dc". Thus, Alice can definitely finish the game in $ 3 $ moves regardless of Bob's moves. It can be shown that the game cannot end in less than $ 3 $ moves, with both players playing optimally.

In the fifth test case, the strings $ S $ and $ T $ are equal, so the game will end without starting, in $ 0 $ moves.

## 样例 #1

### 输入

```
7
5
abcde
abxde
5
hello
olleo
2
ab
cd
7
aaaaaaa
abbbbba
1
q
q
6
yoyoyo
oyoyoy
8
abcdefgh
hguedfbh```

### 输出

```
1
2
3
9
0
2
6```

# AI分析结果

### 中文重写题目

Alice 和 Bob 正在玩一个游戏。他们有两个长度相同的字符串 $S$ 和 $T$，长度均为 $n$，由小写拉丁字母组成。玩家轮流进行操作，Alice 先手。

在 Alice 的回合，她可以选择一个整数 $i$（从 $1$ 到 $n$），选择其中一个字符串 $S$ 或 $T$，以及任意一个小写拉丁字母 $c$，并将所选字符串的第 $i$ 个字符替换为 $c$。

在 Bob 的回合，他可以选择其中一个字符串 $S$ 或 $T$，并将其反转。更正式地说，Bob 执行 $S := \operatorname{rev}(S)$ 或 $T := \operatorname{rev}(T)$，其中 $\operatorname{rev}(P) = P_n P_{n-1} \ldots P_1$。

游戏将持续到字符串 $S$ 和 $T$ 相等为止。一旦字符串相等，游戏立即结束。

定义游戏的持续时间为双方玩家在游戏过程中总共进行的移动次数。例如，如果 Alice 总共进行了 $2$ 次移动，Bob 进行了 $1$ 次移动，那么游戏的持续时间为 $3$。

Alice 的目标是最小化游戏的持续时间，而 Bob 的目标是最大化游戏的持续时间。

如果双方都采取最优策略，游戏的持续时间是多少？可以证明游戏将在有限步数内结束。

### 算法分类
模拟

### 题解分析与结论

1. **核心思路**：所有题解的核心思路都是通过比较字符串 $S$ 和 $T$ 的正序和反序，统计不同字符的数量，然后根据奇偶性计算游戏的最短持续时间。

2. **难点对比**：
   - **无钩七不改名**：通过直接统计正序和反序的不同字符数量，然后根据奇偶性计算最小步数，思路清晰但代码略显复杂。
   - **Lagerent**：同样统计正序和反序的不同字符数量，但代码结构更简洁，逻辑更清晰。
   - **c1ampy**：通过假设 Bob 总是翻转同一个字符串，简化了问题，代码实现较为简洁。

3. **最优思路**：Lagerent 的题解思路清晰，代码简洁，逻辑严谨，是最优的解决方案。

### 评分较高的题解

#### 题解1：Lagerent (5星)
- **关键亮点**：代码结构简洁，逻辑清晰，通过统计正序和反序的不同字符数量，结合奇偶性计算最小步数。
- **核心代码**：
```cpp
int tot1 = 0, tot2 = 0;
rep(i, 1, n) {
    if(str1[i] != str2[i]) ++ tot1;
    if(str1[i] != str2[n - i + 1]) ++ tot2;
}
if(tot1 == 0) {
    puts("0"); return;
}
else if(tot2 == 0) {
    puts("2"); return;
}
int ans = 1e8;
if(tot1 % 2 == 0) ans = min(ans, tot1 * 2);
else ans = min(ans, tot1 * 2 - 1);
if(tot2 % 2 == 0) ans = min(ans, tot2 * 2 - 1);
else ans = min(ans, tot2 * 2);
printf("%d\n", ans);
```

#### 题解2：c1ampy (4星)
- **关键亮点**：通过假设 Bob 总是翻转同一个字符串，简化了问题，代码实现较为简洁。
- **核心代码**：
```cpp
int ans_T = 0;
for (int i = 0; i < n; ++i) {
    ans_T += S[i] != T[i];
}
int ans_T_reversed = 0;
for (int i = 0; i < n; ++i) {
    ans_T_reversed += S[i] != T_reversed[i];
}
ans_T = ans_T & 1 ? (ans_T << 1) - 1 : ans_T << 1;
ans_T_reversed = ans_T_reversed & 1 ? ans_T_reversed << 1 : (ans_T_reversed << 1) - 1;
cout << min(ans_T, ans_T_reversed) << '\n';
```

### 最优关键思路或技巧
- **统计不同字符数量**：通过统计字符串 $S$ 和 $T$ 正序和反序的不同字符数量，结合奇偶性计算最小步数。
- **简化问题**：假设 Bob 总是翻转同一个字符串，简化了问题的复杂度。

### 可拓展之处
- **类似问题**：可以扩展到多个字符串的翻转和修改问题，或者扩展到不同的操作规则。
- **类似算法套路**：在涉及字符串操作和博弈论的问题中，统计不同字符数量并结合奇偶性计算步数是一个常见的套路。

### 推荐题目
1. [P1032 字串变换](https://www.luogu.com.cn/problem/P1032)
2. [P1078 文化之旅](https://www.luogu.com.cn/problem/P1078)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得
- **调试经历**：在统计不同字符数量时，需要注意字符串的索引从0开始还是从1开始，避免越界错误。
- **顿悟感想**：通过假设 Bob 总是翻转同一个字符串，可以大大简化问题的复杂度，减少不必要的计算。

---
处理用时：34.34秒