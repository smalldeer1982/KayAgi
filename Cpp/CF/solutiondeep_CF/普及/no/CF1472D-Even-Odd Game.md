# 题目信息

# Even-Odd Game

## 题目描述

During their New Year holidays, Alice and Bob play the following game using an array $ a $ of $ n $ integers:

- Players take turns, Alice moves first.
- Each turn a player chooses any element and removes it from the array.
- If Alice chooses even value, then she adds it to her score. If the chosen value is odd, Alice's score does not change.
- Similarly, if Bob chooses odd value, then he adds it to his score. If the chosen value is even, then Bob's score does not change.

If there are no numbers left in the array, then the game ends. The player with the highest score wins. If the scores of the players are equal, then a draw is declared.

For example, if $ n = 4 $ and $ a = [5, 2, 7, 3] $ , then the game could go as follows (there are other options):

- On the first move, Alice chooses $ 2 $ and get two points. Her score is now $ 2 $ . The array $ a $ is now $ [5, 7, 3] $ .
- On the second move, Bob chooses $ 5 $ and get five points. His score is now $ 5 $ . The array $ a $ is now $ [7, 3] $ .
- On the third move, Alice chooses $ 7 $ and get no points. Her score is now $ 2 $ . The array $ a $ is now $ [3] $ .
- On the last move, Bob chooses $ 3 $ and get three points. His score is now $ 8 $ . The array $ a $ is empty now.
- Since Bob has more points at the end of the game, he is the winner.

You want to find out who will win if both players play optimally. Note that there may be duplicate numbers in the array.

## 样例 #1

### 输入

```
4
4
5 2 7 3
3
3 2 1
4
2 2 2 2
2
7 8```

### 输出

```
Bob
Tie
Alice
Alice```

# AI分析结果

### 题目内容重写（中文）

**偶数-奇数游戏**

**题目描述**

在新年假期期间，Alice 和 Bob 使用一个包含 $n$ 个整数的数组 $a$ 玩以下游戏：

- 玩家轮流进行，Alice 先手。
- 每轮玩家选择任意一个元素并将其从数组中移除。
- 如果 Alice 选择的是偶数，则将该值加到她的得分中。如果选择的是奇数，Alice 的得分不变。
- 类似地，如果 Bob 选择的是奇数，则将该值加到他的得分中。如果选择的是偶数，Bob 的得分不变。

如果数组中没有剩余的数字，游戏结束。得分最高的玩家获胜。如果玩家得分相同，则宣布平局。

例如，如果 $n = 4$ 且 $a = [5, 2, 7, 3]$，则游戏可能如下进行（还有其他可能）：

- 第一轮，Alice 选择 $2$ 并获得 2 分。她的得分现在是 $2$。数组 $a$ 变为 $[5, 7, 3]$。
- 第二轮，Bob 选择 $5$ 并获得 5 分。他的得分现在是 $5$。数组 $a$ 变为 $[7, 3]$。
- 第三轮，Alice 选择 $7$ 并获得 0 分。她的得分现在是 $2$。数组 $a$ 变为 $[3]$。
- 最后一轮，Bob 选择 $3$ 并获得 3 分。他的得分现在是 $8$。数组 $a$ 现在为空。
- 由于 Bob 在游戏结束时得分更高，他获胜。

你需要找出如果双方都采取最优策略，谁会获胜。注意数组中可能包含重复的数字。

**样例 #1**

**输入**

```
4
4
5 2 7 3
3
3 2 1
4
2 2 2 2
2
7 8
```

**输出**

```
Bob
Tie
Alice
Alice
```

### 算法分类
贪心

### 综合分析与结论
本题的核心在于双方玩家在每轮选择时都采取最优策略，即选择当前数组中的最大值。Alice 和 Bob 分别通过选择偶数和奇数来增加自己的得分，但最优策略是无论选择的是奇数还是偶数，都选择当前最大的数。通过这种方式，双方可以最大化自己的得分或最小化对方的得分。

### 所选题解

#### 题解1：洛璟 (5星)
**关键亮点**：
- 通过排序确保每次选择最大的数。
- 使用作差法比较双方得分，简洁高效。
- 代码清晰，逻辑严谨。

**核心代码**：
```cpp
sort(a+1,a+n+1,cmp);
for(int i=1;i<=n;i++) {
    if(a[i]%2==0 && i%2==1) ans+=a[i];
    else if(a[i]%2==1 && i%2==0) ans-=a[i];
}
if(ans>0) printf("Alice\n");
else if(ans==0) printf("Tie\n");
else printf("Bob\n");
```

#### 题解2：LeavingZzz (4星)
**关键亮点**：
- 初始化得分后，通过排序和轮流选择最大数来计算最终得分。
- 通过同时加数的方式简化得分计算，避免复杂判断。

**核心代码**：
```cpp
sort(A+1,A+1+N);
int op=0;
for(int i=N;i>0;i--,op^=1) {
    if(op) Bo+=A[i];
    else Al+=A[i];
}
if(Al==Bo) puts("Tie");
else if(Al>Bo) puts("Alice");
else puts("Bob");
```

#### 题解3：Phartial (4星)
**关键亮点**：
- 先初始化双方的得分，然后通过排序和轮流选择最大数来更新得分。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
sort(a + 1, a + 1 + n);
for(int i = 0; i < n; i++) {
    s[i & 1] += a[n - i];
}
if(s[0] == s[1]) cout << "Tie" << endl;
else cout << (s[0] > s[1] ? "Alice" : "Bob") << endl;
```

### 最优关键思路或技巧
- **贪心策略**：每次选择当前数组中的最大值，无论其是奇数还是偶数。
- **作差法**：通过计算双方得分的差值来判断胜负，简化比较过程。
- **排序**：先对数组进行排序，确保每次选择都是当前最大的数。

### 可拓展之处
- 类似的问题可以扩展到多个玩家轮流选择最大值或最小值，或者根据其他规则进行选择。
- 可以结合动态规划或博弈论中的其他策略来解决更复杂的游戏问题。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：39.69秒