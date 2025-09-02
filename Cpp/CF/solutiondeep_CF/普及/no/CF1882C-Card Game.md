# 题目信息

# Card Game

## 题目描述

There are $ n $ cards stacked in a deck. Initially, $ a_{i} $ is written on the $ i $ -th card from the top. The value written on a card does not change.

You will play a game. Initially your score is $ 0 $ . In each turn, you can do one of the following operations:

- Choose an odd $ ^{\dagger} $ positive integer $ i $ , which is not greater than the number of cards left in the deck. Remove the $ i $ -th card from the top of the deck and add the number written on the card to your score. The remaining cards will be reindexed starting from the top.
- Choose an even $ ^{\ddagger} $ positive integer $ i $ , which is not greater than the number of cards left in the deck. Remove the $ i $ -th card from the top of the deck. The remaining cards will be reindexed starting from the top.
- End the game. You can end the game whenever you want, you do not have to remove all cards from the initial deck.

What is the maximum score you can get when the game ends?

 $ ^{\dagger} $ An integer $ i $ is odd, if there exists an integer $ k $ such that $ i = 2k + 1 $ .

 $ ^{\ddagger} $ An integer $ i $ is even, if there exists an integer $ k $ such that $ i = 2k $ .

## 说明/提示

In the first test case, one can get the score of $ 5 $ as follows:

1. In the first turn, choose $ i=2 $ . Your score remains $ 0 $ and the numbers written on the cards from the top will become $ [-4, -3, 5] $ .
2. In the second turn, choose $ i=3 $ . Your score will become $ 5 $ and the numbers written on the cards from the top will become $ [-4, -3] $ .
3. In the third turn, end the game with the score of $ 5 $ .

In the second test case, one can get the score of $ 4 $ as follows:

1. In the first turn, choose $ i=3 $ . Your score will become $ 3 $ and the numbers written on the cards from the top will become $ [1, -2, -4] $ .
2. In the second turn, choose $ i=1 $ . Your score will become $ 4 $ and the numbers written on the cards from the top will become $ [-2, -4] $ .
3. In the third turn, end the game with the score of $ 4 $ .

In the third test case, one can get the score of $ 2 $ as follows:

1. In the first turn, choose $ i=1 $ . Your score will become $ -1 $ and the numbers written on the cards from the top will become $ [3, -5] $ .
2. In the second turn, choose $ i=1 $ . Your score will become $ 2 $ and the numbers written on the cards from the top will become $ [-5] $ .
3. In the third turn, end the game with the score of $ 2 $ .

## 样例 #1

### 输入

```
4
4
-4 1 -3 5
4
1 -2 3 -4
3
-1 3 -5
1
-1```

### 输出

```
5
4
2
0```

# AI分析结果

### 题目重写

#### 题目描述

有 $n$ 张牌叠在一起。初始时，第 $i$ 张牌上写有数字 $a_i$。牌上的数字不会改变。

你将进行一个游戏。初始时你的得分为 $0$。在每一轮中，你可以执行以下操作之一：

- 选择一个不大于当前牌堆中剩余牌数的奇数正整数 $i$。移除从上往下数的第 $i$ 张牌，并将牌上的数字加到你的得分中。剩余的牌将重新从上往下编号。
- 选择一个不大于当前牌堆中剩余牌数的偶数正整数 $i$。移除从上往下数的第 $i$ 张牌。剩余的牌将重新从上往下编号。
- 结束游戏。你可以在任何时候结束游戏，不必移除初始牌堆中的所有牌。

游戏结束时，你能获得的最大得分是多少？

### 算法分类

贪心

### 题解分析与结论

本题的核心思路是通过贪心策略最大化得分。大部分题解都采用了类似的方法：从第三张牌开始，尽可能多地取正数牌，然后对前两张牌进行特判。以下是各题解的要点总结：

1. **Leeb** 和 **BugGod** 的题解：**
   - 从第三张牌开始，所有正数牌都可以通过移除前面的负数牌来获取。
   - 对前两张牌进行特判，根据其正负情况决定是否取。
   - 代码简洁，思路清晰。

2. **佬头** 的题解：**
   - 从后往前遍历，优先取奇数位的正数牌。
   - 对前两张牌进行特判，逻辑清晰。
   - 代码实现较为简洁。

3. **phigy** 的题解：**
   - 使用动态规划的思路，设 $f_{i,1/0}$ 表示后 $i$ 张牌在第 $i$ 个位置时能拿奇/偶位时的最大得分。
   - 代码实现较为复杂，但思路新颖。

4. **Flyingsnow** 和 **_299817_** 的题解：**
   - 从第三张牌开始取所有正数牌，然后对前两张牌进行特判。
   - 代码简洁，思路清晰。

### 最优题解

#### 题解1：Leeb (★★★★★)

**关键亮点：**
- 从第三张牌开始，所有正数牌都可以通过移除前面的负数牌来获取。
- 对前两张牌进行特判，逻辑清晰。
- 代码简洁，易于理解。

**核心代码：**
```cpp
int t = in();
while (t--) {
    n = in(); int ans = 0; mem(a, 0);
    for (int i = 1; i <= n; ++i) {
        a[i] = in();
        if (i >= 3 && a[i] > 0) ans += a[i]; 
    }
    if (a[1] >= 0 && a[2] >= 0) ans += a[1] + a[2];
    elif (a[1] >= 0) ans += a[1];
    elif (a[1] + a[2] > 0) ans += a[1] + a[2];
    printf("%lld\n", ans);
}
```

#### 题解2：佬头 (★★★★☆)

**关键亮点：**
- 从后往前遍历，优先取奇数位的正数牌。
- 对前两张牌进行特判，逻辑清晰。
- 代码实现较为简洁。

**核心代码：**
```cpp
for(int _ = read(); _ >= 1; _ --){
    n = read(), a = read();
    if(n == 1){
        write(a > 0? a: 0), puts("");
        continue;
    }
    if(a > 0){
        ans = a;
        a = read(), ans += a > 0? a: 0;
    }
    else a += read(), ans = a > 0? a: 0;
    for(int i = 3; i <= n; ++ i) a = read(), ans += a > 0? a: 0;
    write(ans), puts("");
}
```

#### 题解3：Flyingsnow (★★★★☆)

**关键亮点：**
- 从第三张牌开始取所有正数牌，然后对前两张牌进行特判。
- 代码简洁，思路清晰。

**核心代码：**
```cpp
for (scanf("%lld", &T); T; --T) {
    int ans = 0;
    scanf("%lld", &n);
    memset(a, 0, sizeof a);
    
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        
        if (i >= 3 && a[i] > 0)
            ans += a[i];
    }
    
    if (a[1] >= 0 && a[2] >= 0)
        ans += a[1] + a[2];
    else if (a[1] >= 0) 
        ans += a[1];
    else if (a[2] >= 0 && a[1] + a[2] > 0)
        ans += a[1] + a[2];
    
    printf("%lld\n", ans);
}
```

### 最优思路总结

1. **贪心策略：** 从第三张牌开始，尽可能多地取正数牌，因为这些牌可以通过移除前面的负数牌来获取。
2. **特判前两张牌：** 根据前两张牌的正负情况，决定是否取它们。
3. **代码实现：** 代码简洁，逻辑清晰，易于理解和实现。

### 拓展思路

类似的问题可以通过贪心策略解决，尤其是当问题涉及到最大化或最小化某个值时。可以通过分析问题的性质，找到局部最优解，进而得到全局最优解。

### 推荐题目

1. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

这些题目都涉及到贪心策略的应用，适合进一步练习和巩固贪心算法的思想。

---
处理用时：38.97秒