# 题目信息

# Dasha and Puzzle

## 题目描述

Dasha decided to have a rest after solving the problem. She had been ready to start her favourite activity — origami, but remembered the puzzle that she could not solve.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF761E/f94317c6a4e9720232d894633f6f0c7ec38b7c88.png)The tree is a non-oriented connected graph without cycles. In particular, there always are $ n-1 $ edges in a tree with $ n $ vertices.

The puzzle is to position the vertices at the points of the Cartesian plane with integral coordinates, so that the segments between the vertices connected by edges are parallel to the coordinate axes. Also, the intersection of segments is allowed only at their ends. Distinct vertices should be placed at different points.

Help Dasha to find any suitable way to position the tree vertices on the plane.

It is guaranteed that if it is possible to position the tree vertices on the plane without violating the condition which is given above, then you can do it by using points with integral coordinates which don't exceed $ 10^{18} $ in absolute value.

## 说明/提示

In the first sample one of the possible positions of tree is: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF761E/9f7bd78ab90b0ce22425fab0baf00155435088d1.png)

## 样例 #1

### 输入

```
7
1 2
1 3
2 4
2 5
3 6
3 7```

### 输出

```
YES
0 0
1 0
0 1
2 0
1 -1
-1 1
0 2```

## 样例 #2

### 输入

```
6
1 2
2 3
2 4
2 5
2 6
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4
1 2
2 3
3 4```

### 输出

```
YES
3 3
4 3
5 3
6 3```

# AI分析结果

### 题目内容
# 达莎与谜题

## 题目描述
达莎在解完题后决定休息一下。她正准备开始她最喜欢的活动——折纸，却想起了那个她解不出的谜题。

一棵树是一个无向连通且无环的图。特别地，一个有 $n$ 个顶点的树总是有 $n - 1$ 条边。

这个谜题是要将顶点放置在笛卡尔平面的整点上，使得相连顶点之间的线段与坐标轴平行。此外，线段的相交只允许在它们的端点处。不同的顶点应放置在不同的点上。

帮助达莎找到任何一种合适的方法将树的顶点放置在平面上。

保证如果有可能在不违反上述条件的情况下将树的顶点放置在平面上，那么你可以使用绝对值不超过 $10^{18}$ 的整点来完成。

## 说明/提示
在第一个样例中，树的一种可能放置方式是：
（此处为对应图片链接：https://cdn.luogu.com.cn/upload/vjudge_pic/CF761E/9f7bd78ab90b0ce22425fab0baf00155435088d1.png）

## 样例 #1
### 输入
```
7
1 2
1 3
2 4
2 5
3 6
3 7
```
### 输出
```
YES
0 0
1 0
0 1
2 0
1 -1
-1 1
0 2
```

## 样例 #2
### 输入
```
6
1 2
2 3
2 4
2 5
2 6
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
4
1 2
2 3
3 4
```
### 输出
```
YES
3 3
4 3
5 3
6 3
```

### 算法分类
构造

### 综合分析与结论
这几道题解思路基本一致，都先判断无解情况，即存在度数大于4的节点时无解，因为与某点关于坐标轴平行且边不相交的点最多只有4个。然后通过深度优先搜索（DFS）来构造树顶点在平面上的坐标。构造过程中，为保证边不相交，利用了 $2^k > 2^{k - 1} + 2^{k - 2} + \cdots + 2^0$ 这一性质，让边权随着树深度增加而减小，如设置边权为 $2^{n - deep}$ 或类似形式。同时记录节点来的方向，避免子节点向父节点方向连接。

### 所选的题解
- **作者：Chenyanxi0829 (5星)**
    - **关键亮点**：思路清晰简洁，代码实现精炼，直接以任意节点为根，通过DFS给每个儿子确定坐标，边权设置巧妙且代码实现简洁明了。
    - **核心代码片段**：
```cpp
void dfs(int x, int L, int A, int d) {
  int W = 0;
  for (int i : e[x]) {
    if (i!= A) {
      W += (W == L), X[i] = X[x] + dx[W] * (1 << (n - d)), Y[i] = Y[x] + dy[W] * (1 << (n - d)), dfs(i, (W ^ 1), x, d + 1), W++;
    }
  }
}
```
    - **核心实现思想**：以当前节点 `x` 为基础，遍历其儿子节点 `i`，根据儿子节点序号 `W` 和当前深度 `d` 确定儿子节点坐标 `(X[i], Y[i])`，并递归调用 `dfs` 处理儿子节点。
- **作者：npqenqpve (4星)**
    - **关键亮点**：思路阐述详细，对边权设置的原理解释清晰，通过结构体和 `map` 来记录节点坐标和判断坐标是否已被使用，逻辑较为清晰。
    - **核心代码片段**：
```cpp
void dfs(int u, int fa, int len, int from)
{
	for(int i=0;i<edge[u].size();i++)
	{
		int v=edge[u][i];
		if(v==fa) continue;
		int f;
		if(!m[make_pair(p[u].x,p[u].y+len)]&&from!=4) p[v]=(node){p[u].x,p[u].y+len},m[make_pair(p[u].x,p[u].y+len)]=1,f=1;
		else if(!m[make_pair(p[u].x,p[u].y-len)]&&from!=1) p[v]=(node){p[u].x,p[u].y-len},m[make_pair(p[u].x,p[u].y-len)]=1,f=4;
		else if(!m[make_pair(p[u].x+len,p[u].y)]&&from!=3) p[v]=(node){p[u].x+len,p[u].y},m[make_pair(p[u].x+len,p[u].y)]=1,f=2; 
		else if(!m[make_pair(p[u].x-len,p[u].y)]&&from!=2) p[v]=(node){p[u].x-len,p[u].y},m[make_pair(p[u].x-len,p[u].y)]=1,f=3;
		dfs(v,u,len/2,f);
	}
}
```
    - **核心实现思想**：对当前节点 `u` 的儿子节点 `v`，根据 `from` 方向和坐标是否已使用，确定 `v` 的坐标 `p[v]`，并更新 `map`，然后递归调用 `dfs` 处理儿子节点。
- **作者：water_tomato (4星)**
    - **关键亮点**：对边相交情况进行了图形化分析，使读者更易理解，代码注释详细，逻辑清晰。
    - **核心代码片段**：
```cpp
inline void dfs(int u, int f, int x, int y, int tag, int from){
	//tag 代表题解中的 k，from 代表父亲所在的方向 
	int tot=0;//tot 表示当前即将要走的方向 
	ansx[u]=x,ansy[u]=y;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(v==f) continue;
		if(tot==from) tot++;
		dfs(v,u,x+(1<<tag)*pos[tot][0],y+(1<<tag)*pos[tot][1],tag-1,(tot+2)%4);
		tot++;
	} 
}
```
    - **核心实现思想**：通过 `dfs` 函数，以当前节点 `u` 为基础，根据 `tag`（边权相关参数）和 `from`（父亲方向）确定儿子节点 `v` 的坐标 `(ansx[v], ansy[v])`，并递归调用 `dfs` 处理儿子节点。

### 最优关键思路或技巧
利用 $2^k > 2^{k - 1} + 2^{k - 2} + \cdots + 2^0$ 这一数学性质来设置边权，通过DFS递归构造树顶点在平面上的坐标，同时记录节点来的方向以避免子节点向父节点方向连接，从而实现满足条件的树顶点平面布局构造。

### 可拓展之处
同类型题或类似算法套路：此类题目属于图的构造类问题，类似的套路是在构造过程中利用一些数学性质来保证图的某些条件，如在树或图的布局、染色等问题中，通过合理设置参数和递归方式满足特定要求。

### 推荐洛谷题目
- [P1195 口袋的天空](https://www.luogu.com.cn/problem/P1195)：涉及最小生成树的构造，与本题类似在于都需要对图的结构进行一定的构建和处理。
- [P1364 医院设置](https://www.luogu.com.cn/problem/P1364)：需要通过对树的分析和处理来找到最优解，与本题在对树结构的操作上有相似之处。
- [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)：关于树的动态规划问题，在对树的节点和边的处理思想上与本题有一定关联，都是对树结构进行操作以满足特定条件。

### 个人心得
无。

---
处理用时：62.37秒