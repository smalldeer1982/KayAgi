# 题目信息

# Dot

## 题目描述

Anton and Dasha like to play different games during breaks on checkered paper. By the 11th grade they managed to play all the games of this type and asked Vova the programmer to come up with a new game. Vova suggested to them to play a game under the code name "dot" with the following rules:

- On the checkered paper a coordinate system is drawn. A dot is initially put in the position $ (x,y) $ .
- A move is shifting a dot to one of the pre-selected vectors. Also each player can once per game symmetrically reflect a dot relatively to the line $ y=x $ .
- Anton and Dasha take turns. Anton goes first.
- The player after whose move the distance from the dot to the coordinates' origin exceeds $ d $ , loses.

Help them to determine the winner.

## 说明/提示

In the first test, Anton goes to the vector (1;2), and Dasha loses. In the second test Dasha with her first move shifts the dot so that its coordinates are (2;3), and Anton loses, as he has the only possible move — to reflect relatively to the line $ y=x $ . Dasha will respond to it with the same move and return the dot in position (2;3).

## 样例 #1

### 输入

```
0 0 2 3
1 1
1 2
```

### 输出

```
Anton```

## 样例 #2

### 输入

```
0 0 2 4
1 1
1 2
```

### 输出

```
Dasha```

# AI分析结果

### 题目内容
# 点

## 题目描述
安东和达莎喜欢在课间休息时，在方格纸上玩不同的游戏。到11年级时，他们已经玩遍了这类所有游戏，于是让程序员沃娃想出一个新游戏。沃娃向他们推荐了一款代号为 “点” 的游戏，规则如下：
- 在方格纸上绘制一个坐标系。最初，一个点位于位置$(x, y)$。
- 一步操作是将点移动到预先选定的向量之一。此外，每个玩家在一局游戏中可以将点相对于直线$y = x$对称反射一次。
- 安东和达莎轮流进行操作。安东先开始。
- 在某个玩家操作之后，如果点到坐标原点的距离超过$d$，则该玩家输掉游戏。

请帮助他们确定获胜者。

## 说明/提示
在第一个测试用例中，安东移动到向量$(1, 2)$，达莎输掉游戏。在第二个测试用例中，达莎第一步将点移动到坐标$(2, 3)$，安东输掉游戏，因为他唯一可能的操作是相对于直线$y = x$进行反射。达莎会对此做出相同的操作，将点返回到位置$(2, 3)$。

## 样例 #1
### 输入
```
0 0 2 3
1 1
1 2
```
### 输出
```
Anton
```

## 样例 #2
### 输入
```
0 0 2 4
1 1
1 2
```
### 输出
```
Dasha
```

### 算法分类
深度优先搜索 DFS

### 题解综合分析与结论
两道题解思路基本一致，都发现对称反射操作由于不会改变点到原点的距离，且对手可对称回来，所以在博弈中没有实际作用，可忽略该操作。然后基于简单的博弈论思想，利用深度优先搜索（DFS）来解决问题。对于当前点，若通过移动能到达先手必输的点，则当前点为先手必胜点，通过记忆化搜索避免重复计算，时间复杂度为 $\mathcal O(nd^2)$。

### 所选的题解
- **作者：DengDuck (3星)**
  - **关键亮点**：清晰阐述反射操作无用的原因，利用记忆化搜索实现博弈过程。
  - **核心代码**：
```cpp
bool dfs(LL x, LL y)
{
    if(d*d<x*x+y*y)
    {
        f[x+M][y+M]=1;
        return f[x+M][y+M];
    }
    if(f[x+M][y+M]!=-1)return f[x+M][y+M];
    for(int i=1;i<=n;i++)
    {
        if(!dfs(x+a[i],y+b[i]))
            f[x+M][y+M]=1;
    }
    if(f[x+M][y+M]==-1)f[x+M][y+M]=0;
    return f[x+M][y+M];
}
```
  - **核心实现思想**：若当前点到原点距离超过$d$，标记为当前玩家输（返回1）；若已计算过当前点结果则直接返回；遍历所有向量，若移动到的点是先手必输点，则当前点为先手必胜点；若遍历完所有向量都不满足，则当前点为先手必输点。
- **作者：ttq012 (3星)**
  - **关键亮点**：简洁明了地指出对称操作无用，代码实现简洁。
  - **核心代码**：
```cpp
bool dfs(int x, int y) {
    if (get_dist(x, y) > m)
        return f[x + 500][y + 500] = true;
    if (f[x + 500][y + 500])
        return f[x + 500][y + 500];
    for (int i = 1; i <= n; i ++)
        if (!dfs(x + xx[i], y + yy[i]))
            return f[x + 500][y + 500] = true;
    return f[x + 500][y + 500] = false;
}
```
  - **核心实现思想**：与上一题解类似，先判断当前点到原点距离是否超过$m$，若超过则当前玩家输；若已计算过当前点结果则直接返回；遍历向量，若能到达先手必输点则当前点为先手必胜点，否则为先手必输点。

### 最优关键思路或技巧
发现对称反射操作在博弈中不影响胜负结果，从而简化问题，仅考虑向量移动操作。利用记忆化搜索的方式实现博弈过程，避免重复计算，提高效率。

### 可拓展之处
此类题目属于博弈论结合搜索的类型，类似套路是分析特殊操作对博弈结果的影响，简化问题后利用搜索算法求解。例如，一些博弈问题中存在看似复杂但实际可忽略的操作，通过分析操作性质简化问题，再用搜索算法遍历所有可能状态。

### 洛谷相似题目推荐
- [P1290 欧几里得的游戏](https://www.luogu.com.cn/problem/P1290)：同样是博弈论问题，通过分析操作策略寻找获胜方法。
- [P2197 模板 - nim游戏](https://www.luogu.com.cn/problem/P2197)：经典的nim游戏，考察博弈论基础知识和搜索应用。
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：结合博弈论与贪心思想，分析游戏策略来确定获胜者。 

---
处理用时：45.58秒