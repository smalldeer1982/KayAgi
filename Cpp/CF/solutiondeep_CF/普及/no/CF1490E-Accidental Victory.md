# 题目信息

# Accidental Victory

## 题目描述

A championship is held in Berland, in which $ n $ players participate. The player with the number $ i $ has $ a_i $ ( $ a_i \ge 1 $ ) tokens.

The championship consists of $ n-1 $ games, which are played according to the following rules:

- in each game, two random players with non-zero tokens are selected;
- the player with more tokens is considered the winner of the game (in case of a tie, the winner is chosen randomly);
- the winning player takes all of the loser's tokens;

The last player with non-zero tokens is the winner of the championship.

All random decisions that are made during the championship are made equally probable and independently.

For example, if $ n=4 $ , $ a = [1, 2, 4, 3] $ , then one of the options for the game (there could be other options) is:

- during the first game, the first and fourth players were selected. The fourth player has more tokens, so he takes the first player's tokens. Now $ a = [0, 2, 4, 4] $ ;
- during the second game, the fourth and third players were selected. They have the same number of tokens, but in a random way, the third player is the winner. Now $ a = [0, 2, 8, 0] $ ;
- during the third game, the second and third players were selected. The third player has more tokens, so he takes the second player's tokens. Now $ a = [0, 0, 10, 0] $ ;
- the third player is declared the winner of the championship.

Championship winners will receive personalized prizes. Therefore, the judges want to know in advance which players have a chance of winning, i.e have a non-zero probability of winning the championship. You have been asked to find all such players.

## 样例 #1

### 输入

```
2
4
1 2 4 3
5
1 1 1 1 1```

### 输出

```
3
2 3 4 
5
1 2 3 4 5```

# AI分析结果

### 题目内容重写

#### 题目描述

在Berland举行了一场锦标赛，共有$n$名选手参加。编号为$i$的选手拥有$a_i$（$a_i \ge 1$）个代币。

锦标赛由$n-1$场比赛组成，比赛规则如下：

- 每场比赛随机选择两名拥有非零代币的选手；
- 代币较多的选手获胜（如果代币相同，则随机选择一名获胜者）；
- 获胜者将获得失败者的所有代币；

最后拥有非零代币的选手将赢得锦标赛。

所有随机决策在锦标赛期间都是等概率且独立的。

例如，如果$n=4$，$a = [1, 2, 4, 3]$，那么比赛的一种可能情况（可能有其他情况）是：

- 第一场比赛，选择第一和第四名选手。第四名选手代币较多，因此他获得第一名选手的代币。现在$a = [0, 2, 4, 4]$；
- 第二场比赛，选择第四和第三名选手。他们代币相同，但随机选择第三名选手获胜。现在$a = [0, 2, 8, 0]$；
- 第三场比赛，选择第二和第三名选手。第三名选手代币较多，因此他获得第二名选手的代币。现在$a = [0, 0, 10, 0]$；
- 第三名选手赢得锦标赛。

锦标赛的获胜者将获得个性化奖品。因此，裁判希望提前知道哪些选手有可能获胜，即有非零概率赢得锦标赛。你需要找出所有这样的选手。

#### 样例 #1

##### 输入

```
2
4
1 2 4 3
5
1 1 1 1 1
```

##### 输出

```
3
2 3 4 
5
1 2 3 4 5
```

### 算法分类

贪心、排序、前缀和

### 题解综合分析与结论

本题的核心思路是通过贪心策略和前缀和来快速判断哪些选手有可能成为冠军。大多数题解都采用了以下步骤：

1. **排序**：将选手按照代币数从小到大排序。
2. **前缀和**：计算排序后选手代币的前缀和。
3. **贪心判断**：从后向前遍历，判断当前选手的前缀和是否大于等于下一个选手的代币数，如果是，则该选手有可能成为冠军。

这种方法的优点是时间复杂度为$O(n \log n)$，主要来自排序操作，前缀和和遍历操作都是线性的。

### 所选高分题解

#### 题解1：UperFicial (5星)

**关键亮点**：
- 通过贪心策略和前缀和快速判断哪些选手有可能成为冠军。
- 详细证明了如果第$i+1$支队伍能胜利，且$s_i \ge a_{i+1}$，那么第$i$支队伍也能胜利。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
sort(a + 1, a + n + 1, cmp);
for (int i = 1; i <= n; i++) {
    sum[i] = sum[i - 1] + a[i].val;
}
for (int i = n; i >= 1; i--) {
    if (sum[i - 1] >= a[i].val) {
        ans.push_back(a[i].id);
    } else {
        break;
    }
}
```

#### 题解2：Gokix (4星)

**关键亮点**：
- 从后向前遍历，利用前缀和判断选手是否有可能成为冠军。
- 代码结构清晰，注释详细。

**核心代码**：
```cpp
sort(a + 1, a + n + 1, cmp);
for (int i = 1; i <= n; i++) {
    f[i] = f[i - 1] + a[i].w;
}
for (int i = n; i >= 2; i--) {
    if (f[i - 1] < a[i].w) {
        break;
    }
}
```

#### 题解3：清烛 (4星)

**关键亮点**：
- 通过前缀和和贪心策略判断哪些选手有可能成为冠军。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
sort(a + 1, a + 1 + n, cmp1);
for (int i = 1; i <= n; i++) {
    sum[i] = sum[i - 1] + a[i].val;
}
DEC(i, n, 1) {
    ++cnt;
    if (a[i].val > sum[i - 1]) {
        ans = a[i].val;
        break;
    }
}
```

### 最优关键思路或技巧

1. **排序与前缀和**：通过排序和前缀和的结合，可以快速判断选手是否有可能成为冠军。
2. **贪心策略**：从后向前遍历，利用前缀和判断当前选手是否有可能成为冠军。

### 可拓展之处

这种贪心结合前缀和的思路可以应用于其他类似的问题，例如在某些资源分配问题中，通过排序和前缀和来快速判断某些资源是否可以被合理分配。

### 推荐题目

1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
3. [P1966 火柴排队](https://www.luogu.com.cn/problem/P1966)

### 个人心得摘录

- **UperFicial**：强调了贪心策略的正确性，并通过详细证明增强了题解的可信度。
- **Gokix**：从后向前遍历的思路非常清晰，代码结构简洁，易于理解。
- **清烛**：通过前缀和和贪心策略的结合，快速判断选手是否有可能成为冠军，代码简洁高效。

---
处理用时：38.78秒