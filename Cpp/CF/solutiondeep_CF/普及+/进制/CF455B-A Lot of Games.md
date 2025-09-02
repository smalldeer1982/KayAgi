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

### 题目中文重写
# 很多游戏

## 题目描述

安德鲁、费多尔和亚历克斯都是富有创造力的人。现在他们为两名玩家发明了一款字符串游戏。

给定一组 $n$ 个非空字符串。在游戏过程中，两名玩家共同构建一个单词，初始时这个单词为空。玩家轮流行动。在自己的回合中，玩家必须在单词末尾添加一个字母，且得到的单词必须是该组中至少一个字符串的前缀。如果一名玩家无法行动，则判定为输家。

安德鲁和亚历克斯决定进行 $k$ 次这样的游戏。第 $i$ 局游戏的输家将成为第 $(i + 1)$ 局游戏的先手。他们约定，所有游戏的获胜者是赢得最后一局（第 $k$ 局）游戏的玩家。安德鲁和亚历克斯已经开始了游戏，费多尔想知道如果两名玩家都采取最优策略，谁会赢得这场游戏。请帮助他。

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
这些题解整体思路都是先构建 Trie 树，将问题转化为在 Trie 树上的博弈问题。在此基础上，分析每个节点的先手必胜和必败策略，再根据根节点的情况和游戏局数 $k$ 来判断最终胜负。

- **思路对比**：多数题解都明确指出要考虑先手的必胜和必败策略，通过递归或递推的方式在 Trie 树上进行状态计算。部分题解还详细讨论了不同情况下的胜负判断逻辑，如先手可胜可败、只能胜、只能败、不能胜也不能败等。
- **算法要点**：
    - 构建 Trie 树存储给定的字符串集合。
    - 通过深度优先搜索（DFS）计算每个节点的先手必胜和必败状态。
    - 根据根节点的状态和游戏局数 $k$ 确定最终胜负。
- **解决难点**：本题的关键难点在于考虑到玩家可以故意输掉游戏以获取后续游戏的主动权，因此需要同时计算先手的必胜和必败策略。不同题解在处理这个难点时，采用了不同的代码实现方式，但核心思路一致。

### 评分较高的题解
- **SuperJvRuo（5星）**
    - **关键亮点**：思路清晰，对各种情况的分析详细且易懂，代码注释丰富，可读性强。
    - **个人心得**：WA 了两遍之后才突然明白玩家可以故意输，强调了考虑这一因素的重要性。
- **xuyuansu（4星）**
    - **关键亮点**：思路阐述全面，代码简洁明了，对不同情况的判断逻辑清晰。
- **Azazеl（4星）**
    - **关键亮点**：对题意和题解的分析详细，将各种情况分类讨论，便于理解。

### 重点代码及核心实现思想
#### SuperJvRuo 的代码
```cpp
// 构建 Trie 树
void insert()
{
    cin>>str;
    int len=str.length();
    int now=0;
    for(int i=0;i<len;++i)
    {
        trie[now].haveSon=1;
        if(!trie[now].ch[str[i]-'a'])
        {
            trie[now].ch[str[i]-'a']=++size;
            now=size;
        }
        else
            now=trie[now].ch[str[i]-'a'];
    }
    ++trie[now].isStr;
}

// 求出各节点是否有必胜策略
int dfs1(int root)
{
    if(!trie[root].haveSon)
        return win[root]=0;
    else for(int i=0;i<26;++i)
    {
        if(trie[root].ch[i]&&!dfs1(trie[root].ch[i]))
            return win[root]=1;
    }
    return win[root]=0;
}

// 求出各节点是否有必败策略
int dfs2(int root)
{
    if(!trie[root].haveSon)
        return lose[root]=1;
    else for(int i=0;i<26;++i)
    {
        if(trie[root].ch[i]&&!dfs2(trie[root].ch[i]))
            return lose[root]=1;
    }
    return lose[root]=0;
}
```
**核心实现思想**：先构建 Trie 树存储输入的字符串，然后通过两个 DFS 函数分别计算每个节点的先手必胜和必败状态。对于必胜状态，若一个节点有一个后继节点是必败的，则该节点必胜；对于必败状态，若一个节点有一个后继节点没有必败策略，则该节点必败。

### 最优关键思路或技巧
- **Trie 树的应用**：将字符串集合存储在 Trie 树中，方便进行前缀匹配和状态计算。
- **同时考虑必胜和必败策略**：通过递归或递推的方式，在 Trie 树上计算每个节点的先手必胜和必败状态，以应对玩家故意输的情况。
- **分类讨论**：根据根节点的必胜和必败状态以及游戏局数 $k$ 的奇偶性，对不同情况进行分类讨论，确定最终胜负。

### 拓展思路
同类型题或类似算法套路包括其他基于树结构的博弈问题，如在二叉树、多叉树上进行轮流操作的游戏。解题的关键在于将问题转化为树结构，分析每个节点的状态转移，同时考虑玩家的策略选择。

### 推荐洛谷题目
1. [P2197 nim 游戏](https://www.luogu.com.cn/problem/P2197)：经典的博弈论题目，考察 Nim 游戏的必胜策略。
2. [P1247 取火柴游戏](https://www.luogu.com.cn/problem/P1247)：同样是博弈论问题，涉及到取火柴的策略分析。
3. [P3185 [HNOI2007]分裂游戏](https://www.luogu.com.cn/problem/P3185)：需要通过分析游戏规则，找出必胜策略，与本题的博弈思想类似。

---
处理用时：37.90秒