# 题目信息

# [USACO10DEC] Treasure Chest S

## 题目描述

Bessie and Bonnie have found a treasure chest full of marvelous gold coins! Being cows, though, they can't just walk into a store and buy stuff, so instead they decide to have some fun with the coins.

The N (1 <= N <= 5,000) coins, each with some value C\_i (1 <= C\_i <= 5,000) are placed in a straight line. Bessie and Bonnie take turns, and for each cow's turn, she takes exactly one coin off of either the left end or the right end of the line. The game ends when there are no coins left.

Bessie and Bonnie are each trying to get as much wealth as possible for themselves. Bessie goes first. Help her figure out the maximum value she can win, assuming that both cows play optimally.

Consider a game in which four coins are lined up with these values:

30  25  10  35

Consider this game sequence:

Bessie    Bonnie       New Coin

Player   Side   CoinValue   Total     Total         Line

Bessie   Right     35        35         0       30  25  10

Bonnie   Left      30        35        30         25  10

Bessie   Left      25        60        30           10

Bonnie   Right     10        60        40           --

This is the best game Bessie can play.

小 A 和小 B 在玩游戏。

初始时，有 $n$ 个硬币被摆成了一行，从左至右数第 $i$ 个硬币的价值为 $c_i$。

小 A 和小 B 每人一回合，在一个人的回合中，他可以选择**当前**硬币序列最左侧或者最右侧的硬币，并将他从序列中取出，将其价值累加到自己获得的累计价值中，然后进行另一个人的回合。当硬币全部被取走时，游戏结束。

请求出在双方都尽可能的使自己累计价值最大的情况下，若由小 A 进行第一回合，那么他能获得的累计价值最大是多少。

## 说明/提示

#### 输入输出样例 $1$ 解释

初始时，硬币序列为 $\{30,~25,~10,~35\}$。

第一回合，小 A 取走最右侧的硬币，序列变为 $\{30,~25,~10\}$，小 A 的累加价值为 $35$。

第二回合，小 B 取走最左侧的硬币，序列变为 $\{25,~10\}$，小 B 的累加价值为 $30$。

第三回合，小 A 取走最左侧的硬币，序列变为 $\{10\}$，小 A 的累加价值为 $35 + 25 = 60$。

第四回合，小 B 取走最左侧的硬币，序列变为空，小 B 的累加价值为 $30 + 10 = 40$，游戏结束。

小 A 获得的最大累计价值为 $60$。

#### 数据范围与约定

对于全部的测试点，$1 \leq n \leq 5 \times 10^3$，$1 \leq c_i \leq 5 \times 10^3$。

**提示：请注意，本题的空间限制为 $64$ Mib。**

## 样例 #1

### 输入

```
4 
30 
25 
10 
35 
```

### 输出

```
60 
```

# AI分析结果



### 综合分析与结论
本题是典型的区间DP问题，核心在于双方博弈策略下的最优解计算。所有题解均围绕动态规划展开，主要差异在于空间优化策略。最优解法通过滚动数组将空间复杂度优化至O(n)，是解决该题的核心技巧。贪心解法存在正确性风险，未成为主流解法。

---

### 精选题解推荐

#### 1. 逝星DS (★★★★★)
**关键亮点**：  
- 使用一维滚动数组优化空间，完美适配题目空间限制  
- 代码简洁清晰，逻辑易于理解  
- 通过前缀和优化区间和计算，提升效率  

**核心实现**：  
```cpp
int f[5002]; // 滚动数组存储DP状态
for (int l=2; l<=n; l++) {
    for (int i=1; i+l-1<=n; i++) {
        int j = i + l - 1;
        f[i] = sum[j] - sum[i-1] - min(f[i], f[i+1]);
    }
}
```

#### 2. ＂黎筱っ (★★★★☆)
**关键亮点**：  
- 详细分析了状态转移的方向性  
- 使用前缀和相减代替二维区间和数组  
- 提供状态压缩的数学推导过程  

**核心实现**：  
```cpp
for(int l=2; l<=n; l++) {
    for(int i=1; i+l-1<=n; i++) {
        f[i] = a[i+l-1] - a[i-1] - min(f[i+1], f[i]);
    }
}
```

#### 3. K0stlin (★★★★☆)
**关键亮点**：  
- 采用二进制位运算切换滚动数组状态  
- 双重循环方向设计巧妙，内存访问效率高  
- 代码注释清晰，便于理解优化逻辑  

**核心实现**：  
```cpp
for(int j=2; j<=n; j++) {
    for(int i=j; i>=1; i--) {
        f[j&1][i] = sum[j] - sum[i-1] - min(f[!(j&1)][i], f[j&1][i+1]);
    }
}
```

---

### 关键优化技巧总结
1. **滚动数组**：将二维DP数组压缩为一维，空间复杂度从O(n²)降为O(n)
2. **前缀和优化**：用`sum[j] - sum[i-1]`代替二维区间和数组`sum[i][j]`
3. **逆序更新**：在滚动数组更新时采用从右向左的遍历顺序，避免覆盖未使用的状态
4. **位运算切换状态**：通过`&1`操作实现滚动数组的自动切换，提升代码简洁性

---

### 同类题目推荐
1. [P2734 [USACO3.3] 游戏 A Game](https://www.luogu.com.cn/problem/P2734)  
   **相似点**：同款博弈取数模型，可直接套用滚动数组解法
   
2. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)  
   **相似点**：区间DP经典问题，需处理环形结构变种

3. [P1430 序列取数](https://www.luogu.com.cn/problem/P1430)  
   **相似点**：双人博弈取数加强版，需处理更复杂的状态转移

---

### 调试心得摘录
**ghj1222**：  
> "交上去qtmd90pts，MLE一个点，把评测鸡吊起来干一顿... 经验/教训：做题要早一点做否则改了内存就gg了"  
**总结**：空间优化需优先考虑标准技巧（如滚动数组），非常规方法（如动态内存）会增加调试复杂度

**Kinandra**：  
> "目前还不会证明，欢迎大家一起讨论证明(或证伪)"  
**总结**：博弈类问题需严谨证明贪心策略的正确性，避免直觉性解法

---
处理用时：54.42秒