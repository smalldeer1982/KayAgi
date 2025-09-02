# 题目信息

# Solitaire

## 题目描述

A boy named Vasya wants to play an old Russian solitaire called "Accordion". In this solitaire, the player must observe the following rules:

- A deck of $ n $ cards is carefully shuffled, then all $ n $ cards are put on the table in a line from left to right;
- Before each move the table has several piles of cards lying in a line (initially there are $ n $ piles, each pile has one card). Let's number the piles from left to right, from 1 to $ x $ . During one move, a player can take the whole pile with the maximum number $ x $ (that is the rightmost of remaining) and put it on the top of pile $ x-1 $ (if it exists) or on the top of pile $ x-3 $ (if it exists). The player can put one pile on top of another one only if the piles' top cards have the same suits or values. Please note that if pile $ x $ goes on top of pile $ y $ , then the top card of pile $ x $ becomes the top card of the resulting pile. Also note that each move decreases the total number of piles by 1;
- The solitaire is considered completed if all cards are in the same pile.

Vasya has already shuffled the cards and put them on the table, help him understand whether completing this solitaire is possible or not.

## 说明/提示

In the first sample you can act like that:

- put the 4-th pile on the 1-st one;
- put the 3-rd pile on the 2-nd one;
- put the 2-nd pile on the 1-st one.

In the second sample there is no way to complete the solitaire.

## 样例 #1

### 输入

```
4
2S 2S 2C 2C
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2
3S 2C
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
#### Solitaire
1. **题目描述**：一个名叫瓦夏（Vasya）的男孩想玩一种古老的俄罗斯纸牌游戏“Accordion”。在这个纸牌游戏中，玩家必须遵守以下规则：
    - 一副有\(n\)张牌的牌组被仔细洗牌，然后将所有\(n\)张牌从左到右排成一行放在桌子上。
    - 在每次移动之前，桌子上有几堆牌排成一行（最初有\(n\)堆，每堆有一张牌）。我们从左到右将这些牌堆编号为\(1\)到\(x\)。在一次移动中，玩家可以拿起编号最大为\(x\)的整堆牌（即剩余牌堆中最右边的那一堆），并将其放在牌堆\(x - 1\)的顶部（如果\(x - 1\)存在），或者放在牌堆\(x - 3\)的顶部（如果\(x - 3\)存在）。只有当两堆牌的顶牌具有相同的花色或数值时，玩家才能将一堆牌放在另一堆牌的顶部。请注意，如果牌堆\(x\)放在牌堆\(y\)的顶部，那么牌堆\(x\)的顶牌将成为新牌堆的顶牌。另外，每次移动都会使牌堆总数减少\(1\)。
    - 当所有牌都在同一堆中时，纸牌游戏被认为完成。
    - 瓦夏已经洗好牌并将它们放在桌子上，请帮助他判断是否有可能完成这个纸牌游戏。
2. **说明/提示**：
    - 在第一个示例中，你可以这样操作：
        - 将第\(4\)堆牌放在第\(1\)堆上；
        - 将第\(3\)堆牌放在第\(2\)堆上；
        - 将第\(2\)堆牌放在第\(1\)堆上。
    - 在第二个示例中，没有办法完成纸牌游戏。
3. **样例 #1**：
    - **输入**：
```
4
2S 2S 2C 2C
```
    - **输出**：
```
YES
```
4. **样例 #2**：
    - **输入**：
```
2
3S 2C
```
    - **输出**：
```
NO
```

### 算法分类
深度优先搜索 DFS

### 题解综合分析与结论
三道题解均采用深度优先搜索（DFS）结合记忆化的方法来解决问题。核心思路都是通过记录特定状态（当前牌堆长度及后几张牌的状态）来判断是否能完成游戏，若已搜索过该状态则直接返回结果，避免重复计算。主要区别在于状态表示和代码实现细节上。

### 所选的题解
- **作者：EnochWenzhou（5星）**
    - **关键亮点**：思路清晰，代码简洁明了。状态表示直接使用牌的编号，记忆化数组定义简洁，对状态的判断和转移逻辑清晰，直接在DFS函数中完成所有操作。
    - **重点代码**：
```cpp
bool dfs(int l,int a,int b,int c){
    if(l==1)return 1;
    if(f[l][a][b][c])return 0;
    if(s[c][0]==s[b][0]||s[c][1]==s[b][1])if(dfs(l-1,l-3,a,c))return 1;
    if(l>3&&s[c][0]==s[l-3][0]||s[c][1]==s[l-3][1])if(dfs(l-1,c,a,b))return 1;
    f[l][a][b][c]=1;
    return 0;
}
```
核心实现思想：在DFS函数中，首先判断当前状态是否为结束状态（牌堆长度为1），若是则返回成功。若该状态已被标记为失败则直接返回失败。然后根据规则判断是否能进行两种移动操作，若能则递归调用DFS函数，若其中一种递归调用成功则返回成功，否则标记该状态为失败并返回失败。
- **作者：lmy_2011（4星）**
    - **关键亮点**：代码注释详细，对状态的记录和转移逻辑在注释中解释清晰，方便理解。状态表示同样使用牌的编号，与EnochWenzhou的思路类似。
    - **重点代码**：
```cpp
int dfs(int l,int s1,int s2,int s3){
    if(l==1) 
        return 1;
    if(book[l][s1][s2][s3]==1) 
        return 0;
    if(s[s2][0]==s[s3][0] || s[s2][1]==s[s3][1])
        if(dfs(l-1,l-3,s1,s3)) 
            return 1;
    if(l>=4 && s[s3][0]==s[l-3][0] || s[s3][1]==s[l-3][1])
        if(dfs(l-1,s3,s1,s2)) 
            return 1;
    book[l][s1][s2][s3]=1;
    return 0;
}
```
核心实现思想：与EnochWenzhou的代码类似，先判断是否为结束状态，再判断是否已搜索过该失败状态，然后按规则尝试两种移动操作，递归调用DFS函数，若成功则返回成功，否则标记失败并返回失败。
- **作者：dbodb（3星）**
    - **关键亮点**：将牌的花色和点数转换为一个整数来表示牌的状态，在状态表示上有自己的独特方式，但整体代码相对复杂，可读性稍逊。
    - **重点代码**：
```cpp
int dfs(int ns,int x,int y,int z){
    if(dp[ns][x][y][z]!=-1)return dp[ns][x][y][z];
    if(ns<=3){
        if(pan(x,z)&&pan(y,z)){
            dp[ns][x][y][z]=1;
        }
        else dp[ns][x][y][z]=0;
        return dp[ns][x][y][z];
    }
    int leap=0;
    if(pan(y,z)&&dfs(ns-1,a[ns-3],x,z))
        leap=1;
    if(pan(a[ns-3],z)&&dfs(ns-1,z,x,y))
        leap=1;
    dp[ns][x][y][z]=leap;
    return leap;
}
```
核心实现思想：同样先判断该状态是否已搜索过，对于长度小于等于3的情况特殊处理，然后按规则尝试两种移动操作，递归调用DFS函数，根据递归结果标记当前状态并返回结果。

### 最优关键思路或技巧
采用记忆化搜索，通过记录已经搜索过的状态（当前牌堆长度及后几张牌的状态），避免重复计算，大大提高了搜索效率。在状态表示上，可以直接使用牌的编号，也可以将花色和点数转换为一个整数来表示牌的状态。

### 可拓展之处
同类型题通常是涉及状态转移和判断的搜索问题，例如一些棋盘类游戏的可解性判断。类似算法套路为：明确状态表示，确定状态转移规则，利用记忆化搜索避免重复计算。

### 洛谷相似题目
1. P1605 迷宫（涉及DFS搜索与状态记录）
2. P1141 01迷宫（DFS结合记忆化，判断可达性）
3. P2392 kkksc03考前临时抱佛脚（DFS搜索不同组合方式，可通过记忆化优化） 

---
处理用时：78.75秒