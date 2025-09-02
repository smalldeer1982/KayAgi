# 题目信息

# Socks

## 题目描述

Arseniy is already grown-up and independent. His mother decided to leave him alone for $ m $ days and left on a vacation. She have prepared a lot of food, left some money and washed all Arseniy's clothes.

Ten minutes before her leave she realized that it would be also useful to prepare instruction of which particular clothes to wear on each of the days she will be absent. Arseniy's family is a bit weird so all the clothes is enumerated. For example, each of Arseniy's $ n $ socks is assigned a unique integer from $ 1 $ to $ n $ . Thus, the only thing his mother had to do was to write down two integers $ l_{i} $ and $ r_{i} $ for each of the days — the indices of socks to wear on the day $ i $ (obviously, $ l_{i} $ stands for the left foot and $ r_{i} $ for the right). Each sock is painted in one of $ k $ colors.

When mother already left Arseniy noticed that according to instruction he would wear the socks of different colors on some days. Of course, that is a terrible mistake cause by a rush. Arseniy is a smart boy, and, by some magical coincidence, he posses $ k $ jars with the paint — one for each of $ k $ colors.

Arseniy wants to repaint some of the socks in such a way, that for each of $ m $ days he can follow the mother's instructions and wear the socks of the same color. As he is going to be very busy these days he will have no time to change the colors of any socks so he has to finalize the colors now.

The new computer game Bota-3 was just realised and Arseniy can't wait to play it. What is the minimum number of socks that need their color to be changed in order to make it possible to follow mother's instructions and wear the socks of the same color during each of $ m $ days.

## 说明/提示

In the first sample, Arseniy can repaint the first and the third socks to the second color.

In the second sample, there is no need to change any colors.

## 样例 #1

### 输入

```
3 2 3
1 2 3
1 2
2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 2 2
1 1 2
1 2
2 1
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 袜子

## 题目描述
阿尔谢尼已经长大独立了。他的母亲决定留他独自生活 $m$ 天，然后去度假。她准备了很多食物，留了一些钱，还把阿尔谢尼所有的衣服都洗了。
在她离开前十分钟，她意识到如果能准备一份在她离开的每一天具体该穿哪件衣服的说明也会很有用。阿尔谢尼的家人有点奇怪，所以所有衣服都被编了号。例如，阿尔谢尼的 $n$ 只袜子，每只都被赋予了一个从 $1$ 到 $n$ 的唯一整数。因此，他母亲唯一要做的就是为每一天写下两个整数 $l_{i}$ 和 $r_{i}$ —— 第 $i$ 天要穿的袜子的编号（显然，$l_{i}$ 代表左脚，$r_{i}$ 代表右脚）。每只袜子都被染成了 $k$ 种颜色中的一种。
母亲离开后，阿尔谢尼注意到按照说明，他在某些日子会穿不同颜色的袜子。当然，这是由于匆忙造成的严重错误。阿尔谢尼是个聪明的孩子，而且，神奇的是，他有 $k$ 罐颜料 —— 每种颜色一罐。
阿尔谢尼想重新给一些袜子染色，这样在 $m$ 天中的每一天，他都可以按照母亲的指示，穿上相同颜色的袜子。由于这些天他会非常忙，没有时间改变任何袜子的颜色，所以他现在就必须确定好颜色。
新的电脑游戏《博塔 - 3》刚刚发布，阿尔谢尼迫不及待地想玩。为了能够按照母亲的指示，在每一天都穿上相同颜色的袜子，最少需要改变多少只袜子的颜色呢？

## 说明/提示
在第一个样例中，阿尔谢尼可以把第一只和第三只袜子染成第二种颜色。
在第二个样例中，无需改变任何颜色。

## 样例 #1
### 输入
```
3 2 3
1 2 3
1 2
2 3
```
### 输出
```
2
```

## 样例 #2
### 输入
```
3 2 2
1 1 2
1 2
2 1
```
### 输出
```
0
```

### 算法分类
并查集

### 综合分析与结论
这些题解的核心思路都是利用并查集来处理袜子颜色相同的关系。因为题目中袜子颜色相同的关系具有传递性，符合并查集的应用场景。各题解先通过并查集将需要颜色相同的袜子编号合并到同一个集合，然后针对每个集合，找到集合中出现次数最多的颜色的袜子数量，用集合元素总数减去该数量，得到此集合最少需要修改的袜子数，最后将所有集合的最少修改数累加得到答案。不同题解在具体实现细节上略有差异，如输入方式、数据结构的使用以及代码的简洁性等方面。

### 所选的题解
- **作者：OldVagrant (5星)**
    - **关键亮点**：思路清晰，详细阐述了并查集的使用原理以及如何统计每个集合对答案的贡献。代码实现中使用了路径压缩和启发式合并优化并查集操作，还通过自定义输入函数提高输入效率。
    - **重点代码**：
```c
int find(int x){
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);//路径压缩，直接把该点的父亲节点改为集合代表
}
void merge(int x,int y){
    x=find(x),y=find(y);
    if(x==y) return;//如果两者已经在同一集合内则无需合并
    if(size[x]<size[y]) swap(x,y);//启发式合并，把小的合并到大的里面
    fa[y]=x,size[x]+=size[y];
}
```
核心实现思想：`find`函数用于查找元素所在集合的代表，通过路径压缩优化查找效率；`merge`函数用于合并两个集合，采用启发式合并策略，将小集合合并到大集合，减少树的高度，从而提高后续查找效率。
- **作者：quarmer (4星)**
    - **关键亮点**：简洁明了地阐述了思路，利用`unordered_map`来统计集合中每种颜色袜子的出现次数，代码结构较为清晰。
    - **重点代码**：
```cpp
int find(int x) {
    if(fa[x] == x) return fa[x] ;
    return fa[x] = find(fa[x]) ;
}
void join(int x, int y) {
    int fx = find(x), fy = find(y) ;
    if(fx!= fy) fa[fx] = fy ; 
}
```
核心实现思想：`find`函数查找元素所属集合的根节点，并进行路径压缩；`join`函数合并两个元素所在的集合。
- **作者：顾z (4星)**
    - **关键亮点**：对思路的描述详细，用`vector`维护每个联通块中的袜子颜色，并用`vis`数组统计每种颜色袜子的出现次数，实现较为直观。
    - **重点代码**：
```c++
int find(R int x){return f[x]==x?x:f[x]=find(f[x]);}
//...
for(R int i=1;i<=n;i++)
{
    R int fa=find(i);
    v[fa].push_back(col[i]);
}

for(R int i=1;i<=n;i++)
{
    R int tmp=v[i].size();
    R int mx=0;
    if(tmp>1)
    {
        for(R int j=0;j<tmp;j++)
        {
            vis[v[i][j]]++;
            mx=max(mx,vis[v[i][j]]);
        }
        for(R int j=0;j<tmp;j++)
            vis[v[i][j]]--;
        ans+=tmp-mx;
    }
}
```
核心实现思想：`find`函数查找并查集的根节点并压缩路径。先将每个袜子根据其所属集合放入对应的`vector`中，然后遍历每个`vector`，用`vis`数组统计颜色出现次数，计算每个集合最少需要修改的袜子数并累加到答案中。

### 最优关键思路或技巧
利用并查集维护袜子颜色相同的关系，这是解决本题的关键。通过并查集将具有传递关系的袜子合并到同一集合，使得问题转化为对每个集合内袜子颜色的处理。在处理每个集合时，找到出现次数最多的颜色，将其他袜子颜色修改为该颜色，能保证修改次数最少，这是一种贪心的思想。

### 可拓展之处
同类型题通常会考察具有传递关系的元素集合的处理，类似算法套路是先确定元素间的传递关系，然后使用并查集进行合并，最后对每个集合进行相应的统计或计算。例如，在一些图论问题中，判断哪些节点属于同一个连通分量，然后对每个连通分量进行特定的操作。

### 洛谷相似题目推荐
- [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)：通过并查集判断亲戚关系，与本题利用并查集处理元素间关系类似。
- [P1197 [JSOI2008] 星球大战](https://www.luogu.com.cn/problem/P1197)：结合并查集和图的操作，在动态变化中维护连通性，可拓展对并查集应用的理解。
- [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)：基础的并查集模板题，可巩固并查集的基本操作和应用。

### 个人心得摘录与总结
无。 

---
处理用时：75.00秒