# 题目信息

# [USACO19DEC] Livestock Lineup B

## 题目描述

每天，Farmer John 都要给他的 $8$ 头奶牛挤奶。她们的名字分别是 Bessie，Buttercup，Belinda，Beatrice，Bella，Blue，Betsy，和 Sue。

不幸的是，这些奶牛相当难以伺候，她们要求 Farmer John 以一种符合 $N$ 条限制的顺序给她们挤奶。每条限制的形式为“$X$ 必须紧邻着 $Y$ 挤奶”，要求奶牛 $X$ 在挤奶顺序中必须紧接在奶牛 $Y$ 之后，或者紧接在奶牛 $Y$ 之前。

请帮助 Farmer John 求出一种满足所有限制的奶牛挤奶顺序。保证这样的顺序是存在的。如果有多种顺序都满足要求，请输出字典序最小的一种。也就是说，第一头奶牛需要是所有可能排在任意合法奶牛顺序的第一位的奶牛中名字字典序最小的。在所有合法的以这头字典序最小的奶牛为首的奶牛顺序中，第二头奶牛需要是字典序最小的，以此类推。

## 说明/提示

$1 \leq N \leq 7$。

供题：Brian Dean

## 样例 #1

### 输入

```
3
Buttercup must be milked beside Bella
Blue must be milked beside Bella
Sue must be milked beside Beatrice```

### 输出

```
Beatrice
Sue
Belinda
Bessie
Betsy
Blue
Bella
Buttercup```

# AI分析结果

### 综合分析与结论

本题的核心在于找到满足所有限制条件的字典序最小的排列。由于奶牛数量较少（8头），且限制条件数量也不多（最多7条），因此大多数题解采用了全排列的暴力搜索方法，结合STL中的`next_permutation`函数来生成所有可能的排列，并逐一检查是否满足条件。这种方法虽然简单粗暴，但在本题的数据范围内是可行的。

部分题解还尝试了更高效的算法，如使用双向链表或邻接矩阵来存储奶牛之间的关系，并通过DFS或贪心策略来生成符合条件的排列。这些方法在理论上可以减少搜索空间，但在实际实现中，由于数据量较小，优化效果并不明显。

### 所选高星题解

#### 1. 作者：Yellow_Lemon_Tree (5星)
**关键亮点**：
- 使用`next_permutation`生成全排列，简洁高效。
- 通过`find`函数快速定位奶牛在排列中的位置，判断是否满足条件。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
do{
    if(sati()){
        for(int i=0;i<8;i++) cout<<cows[i]<<endl;
        break;
    }
} while(next_permutation(cows.begin(),cows.end()));
```
**实现思想**：通过`next_permutation`生成所有可能的排列，并使用`sati`函数检查是否满足所有限制条件，满足则输出并结束程序。

#### 2. 作者：Skyjoy (4星)
**关键亮点**：
- 使用`map`存储奶牛名字与索引的映射，方便快速查找。
- 通过`next_permutation`生成排列，并结合`map`判断是否满足条件。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
while(cnt<=43200){
    flag=0;
    cnt++;
    for(int i=0;i<n;i++){
        if(abs(m[sen[i][0]]-m[sen[i][5]])!=1){
            flag=1;
            break;
        }
    }
    if(!flag) break;
    next_permutation(s,s+8);
    for(int i=0;i<8;i++) m[s[i]]=i;
}
```
**实现思想**：通过`next_permutation`生成排列，并使用`map`快速判断是否满足所有限制条件，满足则输出并结束程序。

#### 3. 作者：Invisible_Blade (4星)
**关键亮点**：
- 使用双向链表和DFS来生成符合条件的排列，减少搜索空间。
- 通过`map`存储奶牛名字与索引的映射，方便快速查找。
- 代码结构清晰，逻辑严谨。

**核心代码**：
```cpp
while(tot<8){
    for(re i=1;i<=8;++i)
        if(!vis[i]&&du[i]!=2){now=i;break;}
    cout<<t[now]<<endl;
    ++tot,vis[now]=1;
    if(du[now]==1) dfs(now);
}
```
**实现思想**：通过遍历奶牛，选择字典序最小的奶牛作为起点，并使用DFS遍历其所在的链表，生成符合条件的排列。

### 最优关键思路与技巧

1. **全排列与`next_permutation`**：在数据量较小的情况下，使用全排列生成所有可能的排列，并通过`next_permutation`函数来生成字典序排列，是一种简单且有效的方法。
2. **快速查找与映射**：使用`map`或数组来存储奶牛名字与索引的映射，可以快速定位奶牛在排列中的位置，方便判断是否满足条件。
3. **DFS与链表**：对于更复杂的限制条件，可以使用DFS或链表来生成符合条件的排列，减少搜索空间。

### 可拓展之处

本题的解法可以拓展到其他类似的排列问题，尤其是那些需要满足特定限制条件的排列问题。例如，可以考虑使用更高效的搜索算法（如回溯、剪枝）来优化搜索过程，或者使用图论中的拓扑排序来处理更复杂的限制条件。

### 推荐题目

1. [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706) - 考察全排列的生成与输出。
2. [P1118 [USACO06FEB]Backward Digit Sums G/S](https://www.luogu.com.cn/problem/P1118) - 考察排列与数学结合的问题。
3. [P1037 [NOIP2002 普及组] 产生数](https://www.luogu.com.cn/problem/P1037) - 考察排列与图论结合的问题。

### 个人心得总结

在调试过程中，确保`next_permutation`生成的排列是字典序最小的，并且检查条件时要注意边界情况。使用`map`或数组来存储映射关系可以大大提高代码的可读性和效率。

---
处理用时：35.63秒