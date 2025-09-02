# 题目信息

# A Lot of Games

## 题目描述

Andrew, Fedor and Alex are inventive guys. Now they invent the game with strings for two players.

Given a group of $ n $ non-empty strings. During the game two players build the word together, initially the word is empty. The players move in turns. On his step player must add a single letter in the end of the word, the resulting word must be prefix of at least one string from the group. A player loses if he cannot move.

Andrew and Alex decided to play this game $ k $ times. The player who is the loser of the $ i $ -th game makes the first move in the $ (i+1) $ -th game. Guys decided that the winner of all games is the player who wins the last ( $ k $ -th) game. Andrew and Alex already started the game. Fedor wants to know who wins the game if both players will play optimally. Help him.

## 样例 #1

### 输入

```
2 3
a
b
```

### 输出

```
First
```

## 样例 #2

### 输入

```
3 1
a
b
c
```

### 输出

```
First
```

## 样例 #3

### 输入

```
1 2
ab
```

### 输出

```
Second
```

# AI分析结果

### 题目翻译
# 许多游戏

## 题目描述
安德鲁、费多尔和亚历克斯都是富有创造力的人。现在他们为两名玩家发明了一款字符串游戏。

给定一组 $n$ 个非空字符串。游戏过程中，两名玩家共同构建一个单词，初始时单词为空。玩家轮流行动。在自己的回合中，玩家必须在单词末尾添加一个字母，得到的单词必须是该组中至少一个字符串的前缀。如果一名玩家无法行动，则判定为输家。

安德鲁和亚历克斯决定进行 $k$ 次这样的游戏。第 $i$ 局游戏的输家将成为第 $(i + 1)$ 局游戏的先手。他们约定，所有游戏的胜者是赢得最后一局（第 $k$ 局）游戏的玩家。安德鲁和亚历克斯已经开始了游戏，费多尔想知道如果两名玩家都采取最优策略，谁将赢得游戏。请帮助他。

## 样例 #1
### 输入
```
2 3
a
b
```
### 输出
```
First
```

## 样例 #2
### 输入
```
3 1
a
b
c
```
### 输出
```
First
```

## 样例 #3
### 输入
```
1 2
ab
```
### 输出
```
Second
```

### 综合分析与结论
这些题解的核心思路都是基于Trie树解决博弈问题。首先构建Trie树，将每个节点视为博弈状态，然后通过深度优先搜索（DFS）来计算每个节点的必胜和必败策略。

- **思路对比**：大部分题解都提到了要考虑先手的必胜和必败策略，根据根节点的这两种策略以及游戏局数 $k$ 的奇偶性来判断最终胜负。不过部分题解用二进制数表示状态转移，思路较为独特。
- **算法要点**：
    - 构建Trie树存储输入的字符串。
    - 利用DFS计算每个节点的必胜和必败策略。
    - 根据根节点的策略和 $k$ 的奇偶性判断最终胜负。
- **解决难点**：本题的难点在于考虑到玩家可以故意输来掌控主动权，所以需要同时计算必胜和必败策略。不同题解在处理这个难点时，有的使用两个DFS函数分别计算，有的使用二进制数进行状态转移。

### 所选题解
- **作者：SuperJvRuo（5星）**
    - **关键亮点**：思路清晰，详细阐述了不同情况下的胜负判断逻辑，代码注释丰富，可读性强。
    - **个人心得**：WA了两遍之后才突然明白玩家可以故意输。
```cpp
//trie树
struct Node
{
    int ch[26];
    int isStr;
    bool haveSon;
}trie[100005];
int size;

//求出各节点是否有必胜策略
int dfs1(int root)
{
    //叶子节点必败，递归终止
    if(!trie[root].haveSon)
        return win[root]=0;
    else for(int i=0;i<26;++i)
    {
        //有一个后继节点是必败的，那么这个节点就是必胜的
        if(trie[root].ch[i]&&!dfs1(trie[root].ch[i]))
            return win[root]=1;
    }
    return win[root]=0;
}

//求出各节点是否有必败策略
int dfs2(int root)
{
    //叶子节点仅有必败策略，递归终止
    if(!trie[root].haveSon)
        return lose[root]=1;
    else for(int i=0;i<26;++i)
    {
        //有一个后继节点没有必败策略，那么当前节点就是必败的
        if(trie[root].ch[i]&&!dfs2(trie[root].ch[i]))
            return lose[root]=1;
    }
    return lose[root]=0;
}
```
核心实现思想：通过两个DFS函数分别计算每个节点的必胜和必败策略。对于必胜策略，如果一个节点有一个后继节点是必败的，那么该节点必胜；对于必败策略，如果一个节点有一个后继节点没有必败策略，那么该节点必败。

- **作者：xuyuansu（4星）**
    - **关键亮点**：思路清晰，代码简洁，对各种情况的判断逻辑明确。
```cpp
void dfs(int x)
{
    f[x][0]=0;f[x][1]=0;
    int s=0;
    for(int i=0;i<26;i++)
    {
        if(!son[x][i]) continue;
        dfs(son[x][i]);s++;
        if(f[son[x][i]][1]==0) f[x][1]=1;
        if(f[son[x][i]][0]==0) f[x][0]=1;
    }
    if(!s) f[x][0]=1;
}
```
核心实现思想：通过DFS计算每个节点的必胜和必败策略，存储在二维数组 `f` 中。如果一个节点的某个儿子没有必胜策略，则该节点有必胜策略；如果一个节点的某个儿子没有必败策略，则该节点有必败策略。

- **作者：Azazеl（4星）**
    - **关键亮点**：详细分析了各种情况，代码结构清晰。
```cpp
void Dfs1(int u)
{
    f[u]=-1; 
    for(int i=0;i<26;i++)
    {
        if(!ch[u][i]) continue;
        if(ch[u][i]) Dfs1(ch[u][i]);
        if(f[ch[u][i]]==-1) f[u]=1;
    }
    if(u==1&&f[u]==1) CanWin=true;
}
void Dfs2(int u)
{
    f[u]=-1;
    if(!Child[u]) f[u]=1;
    for(int i=0;i<26;i++)
    {
        if(!ch[u][i]) continue;
        if(ch[u][i]) Dfs2(ch[u][i]);
        if(f[ch[u][i]]==-1) f[u]=1;
    }
    if(u==1&&f[u]==1) CanLose=true;
}
```
核心实现思想：通过两个DFS函数分别计算根节点的必胜和必败策略。在 `Dfs1` 中，如果一个节点的某个儿子是必败的，则该节点必胜；在 `Dfs2` 中，如果一个节点的某个儿子没有必败策略，则该节点必败。

### 最优关键思路或技巧
- 使用Trie树存储字符串，将字符串前缀问题转化为树节点的状态问题。
- 通过DFS递归计算每个节点的必胜和必败策略，利用博弈论的基本原理进行状态转移。

### 拓展思路
同类型题可以是在其他图结构上进行博弈，如棋盘、有向图等。类似算法套路包括状态压缩、记忆化搜索等，用于处理复杂的状态和减少重复计算。

### 洛谷题目推荐
1. [P2197 【模板】nim游戏](https://www.luogu.com.cn/problem/P2197)
2. [P1247 取火柴游戏](https://www.luogu.com.cn/problem/P1247)
3. [P3185 [HNOI2007]分裂游戏](https://www.luogu.com.cn/problem/P3185)

### 个人心得总结
SuperJvRuo在WA了两遍后才意识到玩家可以故意输，这提醒我们在解决博弈问题时要全面考虑各种可能的策略，不能局限于常规思维。

---
处理用时：47.32秒