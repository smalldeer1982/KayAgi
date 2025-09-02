# 题目信息

# Ants

## 题目描述

It has been noted that if some ants are put in the junctions of the graphene integer lattice then they will act in the following fashion: every minute at each junction ( $ x $ , $ y $ ) containing at least four ants a group of four ants will be formed, and these four ants will scatter to the neighbouring junctions ( $ x+1 $ , $ y $ ), ( $ x-1 $ , $ y $ ), ( $ x $ , $ y+1 $ ), ( $ x $ , $ y-1 $ ) — one ant in each direction. No other ant movements will happen. Ants never interfere with each other.

Scientists have put a colony of $ n $ ants into the junction (0, 0) and now they wish to know how many ants will there be at some given junctions, when the movement of the ants stops.

## 说明/提示

In the first sample the colony consists of the one ant, so nothing happens at all.

In the second sample the colony consists of 6 ants. At the first minute 4 ants scatter from (0, 0) to the neighbouring junctions. After that the process stops.

## 样例 #1

### 输入

```
1 3
0 1
0 0
0 -1
```

### 输出

```
0
1
0
```

## 样例 #2

### 输入

```
6 5
0 -2
0 -1
0 0
0 1
0 2
```

### 输出

```
0
1
2
1
0
```

# AI分析结果

### 题目内容
# 蚂蚁

## 题目描述
据观察，如果将一些蚂蚁放置在石墨烯整数晶格的节点上，它们的行为如下：每分钟，在每个至少有四只蚂蚁的节点\((x, y)\)上，会形成一组四只蚂蚁的群体，这四只蚂蚁会分散到相邻的节点\((x + 1, y)\)、\((x - 1, y)\)、\((x, y + 1)\)、\((x, y - 1)\)，即每个方向一只蚂蚁。不会发生其他蚂蚁移动情况。蚂蚁之间从不相互干扰。

科学家将一群\(n\)只蚂蚁放入节点\((0, 0)\)，现在他们想知道，当蚂蚁的移动停止时，一些给定节点上会有多少只蚂蚁。

## 说明/提示
在第一个样例中，蚁群由一只蚂蚁组成，所以什么都不会发生。

在第二个样例中，蚁群由6只蚂蚁组成。在第一分钟，4只蚂蚁从\((0, 0)\)分散到相邻节点。之后这个过程停止。

## 样例 #1
### 输入
```
1 3
0 1
0 0
0 -1
```
### 输出
```
0
1
0
```

## 样例 #2
### 输入
```
6 5
0 -2
0 -1
0 0
0 1
0 2
```
### 输出
```
0
1
2
1
0
```

### 算法分类
模拟

### 题解综合分析与结论
这两道题解都围绕蚂蚁在晶格节点上的移动模拟展开。第一道题解使用深度优先搜索（DFS）并结合优化思路，第二道题解先尝试DFS后因栈溢出改为纯模拟。两者都考虑了坐标处理及边界情况，但在优化程度和代码实现上有差异。

### 所选的题解
 - **作者：封禁用户（星级：4星）**
    - **关键亮点**：提出将所有蚂蚁同时放入格子更新，采用DFS模拟蚂蚁爬行，通过观察数据发现对称性并利用对称性优化，减少计算量，还注意到特判坐标越界情况。
    - **个人心得**：吐槽其他题解复杂度计算错误，强调本题无常数级别的预处理算法。
    - **核心代码片段**：
```cpp
void dfs(int x, int y)
{
    if(a[x][y] < 4)
    {
        return;
    }
    int tmp = a[x][y];
    a[x][y] %= 4;
    if(x == 1)
    {
        a[x - 1][y] += tmp / 4 * 2;
        dfs(x - 1, y);
    }
    else if(x!= 0)
    {
        a[x - 1][y] += tmp / 4;
        dfs(x - 1, y);
    }
    if(y == 1)
    {
        a[x][y - 1] += tmp / 4 * 2;
        dfs(x, y - 1);
    }
    else if(y!= 0)
    {
        a[x][y - 1] += tmp / 4;
        dfs(x, y - 1);
    }
    a[x + 1][y] += tmp / 4;
    dfs(x + 1, y);
    a[x][y + 1] += tmp / 4;
    dfs(x, y + 1);
    return;
}
```
核心实现思想：当节点蚂蚁数大于等于4时，将多余蚂蚁按规则分散到相邻节点，并递归处理相邻节点。
 - **作者：Luo_gu_ykc（星级：3星）**
    - **关键亮点**：先想到用DFS模拟蚂蚁跳动，考虑到坐标可能为负通过加值处理坐标，后因DFS栈溢出改用双层循环枚举所有可能合法坐标，模拟蚂蚁跳动直至无蚂蚁可跳。
    - **核心代码片段**：
```cpp
while(vis){
    vis = 0; 
    for(int i = 0; i < N * 2; i++){
        for(int j = 0; j < N * 2; j++){
            if(cnt[i][j] >= 4){
                vis = 1; 
                int num = cnt[i][j] / 4;
                cnt[i - 1][j] += num;
                cnt[i + 1][j] += num;
                cnt[i][j - 1] += num;
                cnt[i][j + 1] += num;
                cnt[i][j] -= (num * 4);
            }
        }
    }
}
```
核心实现思想：通过双层循环遍历所有坐标，若某坐标蚂蚁数大于等于4，则按规则分散蚂蚁，并标记还有蚂蚁可跳。

### 最优关键思路或技巧
利用数据的对称性优化计算，如封禁用户题解中通过观察发现蚂蚁分布在平面直角坐标系中的对称性，只计算坐标轴和一个象限的情况，减少计算量。

### 可拓展之处
此类题目属于模拟类问题，类似套路为观察数据规律，利用对称性、周期性等减少计算量。同类型题可关注其他在网格上进行元素移动、状态变化的模拟场景。

### 洛谷相似题目推荐
 - [P1032 字串变换](https://www.luogu.com.cn/problem/P1032)：字符串模拟变换问题，与本题类似，需要按给定规则对字符串进行操作并模拟过程。
 - [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：在二维网格上根据一定规则对区域进行填涂模拟，和本题在网格上模拟状态变化类似。
 - [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：字符串模拟匹配问题，通过模拟字符串匹配过程统计单词数，与本题按规则模拟蚂蚁移动思路类似。 

---
处理用时：48.31秒