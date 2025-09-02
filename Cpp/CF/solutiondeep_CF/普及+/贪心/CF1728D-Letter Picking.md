# 题目信息

# Letter Picking

## 题目描述

Alice and Bob are playing a game. Initially, they are given a non-empty string $ s $ , consisting of lowercase Latin letters. The length of the string is even. Each player also has a string of their own, initially empty.

Alice starts, then they alternate moves. In one move, a player takes either the first or the last letter of the string $ s $ , removes it from $ s $ and prepends (adds to the beginning) it to their own string.

The game ends when the string $ s $ becomes empty. The winner is the player with a lexicographically smaller string. If the players' strings are equal, then it's a draw.

A string $ a $ is lexicographically smaller than a string $ b $ if there exists such position $ i $ that $ a_j = b_j $ for all $ j < i $ and $ a_i < b_i $ .

What is the result of the game if both players play optimally (e. g. both players try to win; if they can't, then try to draw)?

## 说明/提示

One of the possible games Alice and Bob can play in the first testcase:

1. Alice picks the first letter in $ s $ : $ s= $ "orces", $ a= $ "f", $ b= $ "";
2. Bob picks the last letter in $ s $ : $ s= $ "orce", $ a= $ "f", $ b= $ "s";
3. Alice picks the last letter in $ s $ : $ s= $ "orc", $ a= $ "ef", $ b= $ "s";
4. Bob picks the first letter in $ s $ : $ s= $ "rc", $ a= $ "ef", $ b= $ "os";
5. Alice picks the last letter in $ s $ : $ s= $ "r", $ a= $ "cef", $ b= $ "os";
6. Bob picks the remaining letter in $ s $ : $ s= $ "", $ a= $ "cef", $ b= $ "ros".

Alice wins because "cef" &lt; "ros". Neither of the players follows any strategy in this particular example game, so it doesn't show that Alice wins if both play optimally.

## 样例 #1

### 输入

```
2
forces
abba```

### 输出

```
Alice
Draw```

# AI分析结果



# 题目内容中文翻译

# 字母选取游戏

## 题目描述

Alice 和 Bob 正在玩一个游戏。初始时给定一个非空字符串 $s$，由小写拉丁字母组成，字符串长度为偶数。每个玩家都有一个初始为空的字符串。

Alice 先手，两人交替行动。每轮玩家选择 $s$ 的首字符或尾字符，将其从 $s$ 中移除并拼接到自己字符串的开头。

当 $s$ 为空时游戏结束，字符串字典序更小的玩家获胜。若字符串相等则为平局。

若双方都采取最优策略（优先争取胜利，无法胜利则争取平局），求最终游戏结果。

---

# 题解综合分析

### 核心算法：区间 DP 博弈分析
所有题解均围绕博弈论中的最优决策展开，主要采用区间 DP 进行状态转移。关键点在于：
1. **状态设计**：定义 $dp[l][r]$ 表示子串 $s[l..r]$ 的游戏结果
2. **转移逻辑**：枚举 Alice 的两种选择（首/尾），考虑 Bob 的反制策略
3. **字典序比较**：结合当前选择的字符比较与子问题结果

### 关键优化洞察
部分题解发现 **Bob 无法获胜**，只需判断 Alice 必胜或平局，将问题简化为判断特殊结构（回文、成对重复等）。

---

# 精选题解

## 1. 作者：_•́へ•́╬_（⭐⭐⭐⭐⭐）
**核心思路**：正统区间 DP 解法
```cpp
int dfs(int l, int r) {
    if (l > r) return 0;
    if (ans[l][r] != -1) return ans[l][r];
    
    // 计算三种子情况
    int x = dfs(l+2, r), y = dfs(l+1, r-1), z = dfs(l, r-2);
    
    // Alice 选左端时的两种反制情况
    bool cond1 = (x==1 || (!x && s[l]<s[l+1])) && 
                (y==1 || (!y && s[l]<s[r]));
    
    // Alice 选右端时的两种反制情况
    bool cond2 = (z==1 || (!z && s[r]<s[r-1])) && 
                (y==1 || (!y && s[r]<s[l]));
    
    if (cond1 || cond2) return ans[l][r] = 1; // Alice 必胜
    // ... 平局判断类似
}
```
**亮点**：状态转移全面，严格遵循博弈逻辑

## 2. 作者：MoyunAlgorithm（⭐⭐⭐⭐）
**核心思路**：发现 Bob 无法胜出，将问题转化为结构判断
```cpp
while (l < r && s[l] == s[r]) l++, r--; // 消去外围相同字符
if (l >= r) puts("Draw"); // 形成回文结构
else {
    // 检查内部是否成对重复
    bool flag = true;
    for (int i = l; i <= r; i += 2)
        if (s[i] != s[i+1]) flag = false;
    puts(flag ? "Draw" : "Alice");
}
```
**亮点**：时间复杂度优化至 O(n)，代码简洁

## 3. 作者：DaiRuiChen007（⭐⭐⭐⭐）
**核心思路**：标准博弈论 min-max 实现
```cpp
dp[l][r] = max( // Alice 选择最优策略
    min( // Bob 选择最不利情况
        comb(s[l], s[r], dp[l+1][r-1]), 
        comb(s[l], s[l+1], dp[l+2][r])
    ),
    min(
        comb(s[r], s[l], dp[l+1][r-1]),
        comb(s[r], s[r-1], dp[l][r-2])
    )
);
```
**亮点**：采用经典博弈建模方法，代码结构清晰

---

# 关键技巧总结
1. **区间 DP 状态设计**：将字符串博弈转化为子区间结果组合
2. **字典序比较层级**：优先比较子问题结果，其次当前字符
3. **对称性利用**：当字符串呈现回文或重复结构时可直接判平
4. **博弈策略建模**：Alice 最大化优势，Bob 最小化损失

---

# 同类题目推荐
1. [P2734 [USACO3.3] 游戏 A Game](https://www.luogu.com.cn/problem/P2734) - 区间 DP 博弈
2. [P2962 [USACO09NOV] Lights G](https://www.luogu.com.cn/problem/P2962) - 博弈状态压缩
3. [P5641 [CSGRound2] 开拓者的卓识](https://www.luogu.com.cn/problem/P5641) - 前缀和优化博弈

---
处理用时：66.95秒