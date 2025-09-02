# 题目信息

# [USACO09OPEN] Cow Digit Game S

## 题目描述

Bessie is playing a number game against Farmer John, and she wants you to help her achieve victory.

Game i starts with an integer N\_i (1 <= N\_i <= 1,000,000). Bessie goes first, and then the two players alternate turns. On each turn, a player can subtract either the largest digit or the smallest non-zero digit from the current number to obtain a new number. For example, from 3014 we may subtract either 1 or 4 to obtain either 3013 or 3010, respectively. The game continues until the number becomes 0, at which point the last player to have taken a turn is the winner.

Bessie and FJ play G (1 <= G <= 100) games. Determine, for each game, whether Bessie or FJ will win, assuming that both play perfectly (that is, on each turn, if the current player has a move that will guarantee his or her win, he or she will take it).

Consider a sample game where N\_i = 13. Bessie goes first and takes 3, leaving 10. FJ is forced to take 1, leaving 9. Bessie takes the remainder and wins the game.

贝茜和约翰在玩一个数字游戏．贝茜需要你帮助她．

游戏一共进行了G(1≤G≤100)场．第i场游戏开始于一个正整数Ni(l≤Ni≤1,000,000)．游

戏规则是这样的：双方轮流操作，将当前的数字减去一个数，这个数可以是当前数字的最大数码，也可以是最小的非0数码．比如当前的数是3014，操作者可以减去1变成3013，也可以减去4变成3010．若干次操作之后，这个数字会变成0．这时候不能再操作的一方为输家．    贝茜总是先开始操作．如果贝茜和约翰都足够聪明，执行最好的策略．请你计算最后的赢家．

比如，一场游戏开始于13.贝茜将13减去3变成10．约翰只能将10减去1变成9．贝茜再将9减去9变成0．最后贝茜赢．


## 说明/提示

For the first game, Bessie simply takes the number 9 and wins. For the second game, Bessie must take 1 (since she cannot take 0), and then FJ can win by taking 9.


## 样例 #1

### 输入

```
2 
9 
10 
```

### 输出

```
YES 
NO 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕博弈论解决“Cow Digit Game S”问题。核心思路是利用博弈论中必胜态和必败态的关系，通过递推或记忆化搜索确定每个状态的胜负情况。多数题解先初始化 1 - 9 为必胜态，0 为必败态，再从 10 开始递推，根据后继状态判断当前状态的胜负。部分题解使用了优化技巧，如离线处理、减少不必要的初始化等。

### 所选题解
- **作者：konjacq（5星）**
    - **关键亮点**：思路清晰，详细阐述了博弈论结论，给出了常规递推解法和更快的离线处理方法，代码简洁易懂。
    - **核心代码**：
```cpp
// 常规递推解法
for (int i=1;i<10;i++) f[i]=true;
for (int i=10;i<1000001;i++)
{
    if (f[i-fmax(i)]&&f[i-fmin(i)]);
    else f[i]=true;
}
```
核心实现思想：先将 1 - 9 标记为必胜态，然后从 10 开始遍历，若当前状态的两个后继状态都是必胜态，则当前状态为必败态，否则为必胜态。

- **作者：UperFicial（5星）**
    - **关键亮点**：不仅详细解释了博弈论的应用，还给出了优化思路，如减少不必要的初始化和使用位运算简化递推，时间复杂度和空间复杂度分析清晰。
    - **核心代码**：
```cpp
// 优化递推
dp[x]=(dp[x-minn]&dp[x-maxn])^1;
```
核心实现思想：利用位运算简化递推过程，根据后继状态的胜负情况确定当前状态的胜负。

- **作者：qzhwlyn（4星）**
    - **关键亮点**：先给出超时的 40 分代码，然后分析原因并给出 AC 代码，通过对比展示了优化过程，有助于理解。
    - **核心代码**：
```c
for(int i=10;i<=maxx;i++){
    m1=0;
    tot=i;
    while(tot){
        if(tot%10>m1) m1=tot%10;
        tot/=10;
    }
    m2=10;
    tot=i;
    while(tot){
        if(tot%10<m2&&tot%10) m2=tot%10;
        tot/=10;
    }
    if(f[i-m1]&&f[i-m2]);
    else f[i]=1;
}
```
核心实现思想：从 10 到最大询问值遍历，找出当前数的最大和最小非零数码，根据后继状态判断当前状态的胜负。

### 最优关键思路或技巧
- **博弈论应用**：利用“必胜态至少有一个后继是必败态，必败态的所有后继都是必胜态”这一结论，通过递推或记忆化搜索确定每个状态的胜负。
- **离线处理**：记录询问的最大值，只预处理该范围内的状态，减少不必要的计算。
- **位运算优化**：使用位运算简化递推过程，提高代码效率。

### 可拓展之处
同类型题通常涉及博弈论和状态转移，如巴什博弈、尼姆博弈等。解题关键在于找出状态转移规律，确定必胜态和必败态。类似算法套路包括记忆化搜索、动态规划等。

### 推荐题目
- [P1290 欧几里德的游戏](https://www.luogu.com.cn/problem/P1290)
- [P2197 nim 游戏](https://www.luogu.com.cn/problem/P2197)
- [P2964 [USACO09NOV]A Coin Game S](https://www.luogu.com.cn/problem/P2964)

### 个人心得摘录与总结
- **UperFicial**：审错题意导致 WA，之后加了优化抢到最优解。总结是做题要仔细审题，合理运用优化技巧。
- **环日加速器**：一开始骗分得了 40 分，之后根据老师讲解写出代码但超时，吸氧后 AC，最后通过预处理 A 了。总结是遇到超时问题可考虑预处理减少重复计算。 

---
处理用时：28.97秒