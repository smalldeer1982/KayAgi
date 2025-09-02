# 题目信息

# Garland

## 题目描述

Once at New Year Dima had a dream in which he was presented a fairy garland. A garland is a set of lamps, some pairs of which are connected by wires. Dima remembered that each two lamps in the garland were connected directly or indirectly via some wires. Furthermore, the number of wires was exactly one less than the number of lamps.

There was something unusual about the garland. Each lamp had its own brightness which depended on the temperature of the lamp. Temperatures could be positive, negative or zero. Dima has two friends, so he decided to share the garland with them. He wants to cut two different wires so that the garland breaks up into three parts. Each part of the garland should shine equally, i. e. the sums of lamps' temperatures should be equal in each of the parts. Of course, each of the parts should be non-empty, i. e. each part should contain at least one lamp.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/c2b0d1858f505d34921dc11648298e7a84c2f7b5.png)Help Dima to find a suitable way to cut the garland, or determine that this is impossible.

While examining the garland, Dima lifted it up holding by one of the lamps. Thus, each of the lamps, except the one he is holding by, is now hanging on some wire. So, you should print two lamp ids as the answer which denote that Dima should cut the wires these lamps are hanging on. Of course, the lamp Dima is holding the garland by can't be included in the answer.

## 说明/提示

The garland and cuts scheme for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/578d2b3356505b1b3987876ed70f57ef1ae0c5b0.png)

## 样例 #1

### 输入

```
6
2 4
0 5
4 2
2 1
1 1
4 2
```

### 输出

```
1 4
```

## 样例 #2

### 输入

```
6
2 4
0 6
4 2
2 1
1 1
4 2
```

### 输出

```
-1
```

# AI分析结果

### 题目翻译
# 花环

## 题目描述
有一次在新年的时候，迪玛做了一个梦，梦中他得到了一个神奇的花环。花环是一组灯，其中一些灯对通过电线相连。迪玛记得花环中的任意两盏灯都可以直接或间接地通过一些电线相连。此外，电线的数量恰好比灯的数量少一个。

这个花环有一些不寻常的地方。每盏灯都有自己的亮度，亮度取决于灯的温度。温度可以是正的、负的或零。迪玛有两个朋友，所以他决定和他们分享这个花环。他想剪断两条不同的电线，使花环分成三部分。花环的每一部分应该亮度相同，即每一部分灯的温度总和应该相等。当然，每一部分都应该是非空的，即每一部分至少应该包含一盏灯。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/c2b0d1858f505d34921dc11648298e7a84c2f7b5.png)

帮助迪玛找到一种合适的剪断花环的方法，或者确定这是不可能的。

在检查花环时，迪玛拿起其中一盏灯将花环提了起来。因此，除了他提着的那盏灯之外，每盏灯现在都挂在某根电线上。所以，你应该输出两个灯的编号作为答案，表示迪玛应该剪断这两盏灯所挂的电线。当然，迪玛提着花环的那盏灯不能包含在答案中。

## 说明/提示
第一个样例的花环和剪断方案：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/578d2b3356505b1b3987876ed70f57ef1ae0c5b0.png)

## 样例 #1
### 输入
```
6
2 4
0 5
4 2
2 1
1 1
4 2
```
### 输出
```
1 4
```

## 样例 #2
### 输入
```
6
2 4
0 6
4 2
2 1
1 1
4 2
```
### 输出
```
-1
```

### 综合分析与结论
这些题解的核心思路基本一致，都是先判断整棵树点权和是否为 3 的倍数，若不是则无解；若是，则通过树形 DP 从叶子节点向上计算每个子树的权值和，当子树权值和等于整棵树权值和的 1/3 时，将该子树“剪掉”（权值置为 0）并记录节点，最后判断记录的节点数是否大于等于 3，若满足则输出前两个节点，否则输出 -1。

### 所选题解
- **作者：maniac！ (赞：17) - 5星**
    - **关键亮点**：思路清晰，代码注释详细，对解题过程的文字描述生动且易于理解，能让读者很好地跟上思路。
    - **个人心得**：作者一开始将题目分析成树形动规，但实现代码后发现实际动规的味道不浓，更多是巧妙的想法，提醒大家不要盲目套类型题的解法。
    - **核心代码**：
```cpp
void dfs(int x,int y){
    tem[x]=t[x];
    for(int i=head[x];i;i=next[i]){
        int v=ver[i];
        if(v!=y){
            dfs(v,x);
            tem[x]+=tem[v];
        }
    }
    if(tem[x]==sum) ans[++cnt]=x,tem[x]=0;
}
```
核心实现思想：通过深度优先搜索遍历树，计算以每个节点为根的子树的权值和，若权值和等于整棵树权值和的 1/3，则记录该节点并将其权值和置为 0。

- **作者：无咕_ (赞：6) - 4星**
    - **关键亮点**：不仅给出了详细的思路和代码，还列出了类似题型，方便读者拓展练习。
    - **核心代码**：
```cpp
void dfs(int now,int fa){
    treesum[now]=a[now];
    for(int i=head[now];i;i=edge[i].nxt){
        int to=edge[i].to;
        if(to==fa)continue;
        dfs(to,now);
        treesum[now]+=treesum[to];
    }
    if(treesum[now]==sum/3)ans[++num_ans]=now,treesum[now]=0;
}
```
核心实现思想：与上一题解类似，通过深度优先搜索计算子树权值和，满足条件时记录节点并置权值和为 0。

- **作者：kenlig (赞：5) - 4星**
    - **关键亮点**：代码中有详细注释，对解题步骤的解释清晰，便于读者理解代码逻辑。
    - **核心代码**：
```cpp
int dfs(int x,int fath){
    ksum[x]=a[x];
    for(int i=head[x];i;i=edge[i].nxt){
        int y=edge[i].to;
        if(y!=fath){
            dfs(y,x);
            ksum[x]+=ksum[y];
        }
    }
    if(ksum[x]==sum){
        cnt++;
        ans[cnt]=x;
        ksum[x]=0;
    }
}
```
核心实现思想：同样是深度优先搜索计算子树权值和，满足条件时记录节点并更新权值和。

### 最优关键思路或技巧
- **树形 DP 思想**：利用树形结构的特点，从叶子节点向上递推计算子树的权值和，避免重复计算。
- **剪枝优化**：在开始时判断点权和是否为 3 的倍数，若不是则直接判定无解，减少不必要的计算。
- **子树处理**：当找到权值和为整棵树权值和 1/3 的子树时，将其权值和置为 0，避免对后续判断产生干扰。

### 拓展思路
同类型题或类似算法套路通常涉及树的遍历和子树信息的统计，如树的重心、树的直径等问题，都可以使用树形 DP 的方法解决。

### 推荐题目
1. [P2014 [CTSC1997]选课](https://www.luogu.com.cn/problem/P2014)
2. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
3. [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)

### 个人心得总结
作者 maniac！一开始将题目错误分析为树形动规，实现代码后才发现实际动规味道不浓，提醒大家做题时不要盲目套类型题的解法，要深入理解题目本质。作者 ctq1999 尝试了 $O(n^2)$ 的暴力解法和在遍历中直接输出的方法，但分别在 #28 TLE 和 #8 WA，最后参考题解才得到正确解法，说明做题时要多尝试不同方法，同时也要及时学习优秀的解题思路。 

---
处理用时：43.60秒