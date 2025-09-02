# 题目信息

# New Year and Fireworks

## 题目描述

One tradition of welcoming the New Year is launching fireworks into the sky. Usually a launched firework flies vertically upward for some period of time, then explodes, splitting into several parts flying in different directions. Sometimes those parts also explode after some period of time, splitting into even more parts, and so on.

Limak, who lives in an infinite grid, has a single firework. The behaviour of the firework is described with a recursion depth $ n $ and a duration for each level of recursion $ t_{1},t_{2},...,t_{n} $ . Once Limak launches the firework in some cell, the firework starts moving upward. After covering $ t_{1} $ cells (including the starting cell), it explodes and splits into two parts, each moving in the direction changed by $ 45 $ degrees (see the pictures below for clarification). So, one part moves in the top-left direction, while the other one moves in the top-right direction. Each part explodes again after covering $ t_{2} $ cells, splitting into two parts moving in directions again changed by $ 45 $ degrees. The process continues till the $ n $ -th level of recursion, when all $ 2^{n-1} $ existing parts explode and disappear without creating new parts. After a few levels of recursion, it's possible that some parts will be at the same place and at the same time — it is allowed and such parts do not crash.

Before launching the firework, Limak must make sure that nobody stands in cells which will be visited at least once by the firework. Can you count the number of those cells?

## 说明/提示

For the first sample, the drawings below show the situation after each level of recursion. Limak launched the firework from the bottom-most red cell. It covered $ t_{1}=4 $ cells (marked red), exploded and divided into two parts (their further movement is marked green). All explosions are marked with an 'X' character. On the last drawing, there are $ 4 $ red, $ 4 $ green, $ 8 $ orange and $ 23 $ pink cells. So, the total number of visited cells is $ 4+4+8+23=39 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750D/958e71e20888e0f3c92e01fa2be2e012117f122b.png)For the second sample, the drawings below show the situation after levels $ 4 $ , $ 5 $ and $ 6 $ . The middle drawing shows directions of all parts that will move in the next level.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750D/c21fe29a69f3371f920085202e17e34b6a0270b1.png)

## 样例 #1

### 输入

```
4
4 2 2 3
```

### 输出

```
39
```

## 样例 #2

### 输入

```
6
1 1 1 1 1 3
```

### 输出

```
85
```

## 样例 #3

### 输入

```
1
3
```

### 输出

```
3
```

# AI分析结果

### 题目内容
#### 新年烟花
#### 题目描述
迎接新年的一个传统是向天空发射烟花。通常，发射的烟花会垂直向上飞行一段时间，然后爆炸，分裂成几个部分向不同方向飞行。有时，这些部分在一段时间后也会爆炸，分裂成更多部分，依此类推。

利马克（Limak）生活在一个无限的网格中，他有一枚烟花。烟花的行为由递归深度 $n$ 和每个递归层级的持续时间 $t_{1},t_{2},\cdots,t_{n}$ 描述。一旦利马克在某个单元格发射烟花，烟花就会开始向上移动。在覆盖 $t_{1}$ 个单元格（包括起始单元格）后，它会爆炸并分裂成两部分，每部分移动方向改变 $45$ 度（见下图以作说明）。所以，一部分朝左上角方向移动，而另一部分朝右上角方向移动。每部分在覆盖 $t_{2}$ 个单元格后再次爆炸，再次分裂成两部分，移动方向又改变 $45$ 度。这个过程一直持续到第 $n$ 级递归，此时所有 $2^{n - 1}$ 个现有部分爆炸并消失，不再产生新的部分。经过几个递归层级后，有可能一些部分会同时处于同一位置 —— 这是允许的，并且这些部分不会碰撞。

在发射烟花之前，利马克必须确保没有人站在烟花至少会经过一次的单元格中。你能计算出这些单元格的数量吗？
#### 说明/提示
对于第一个样例，下面的图展示了每个递归层级后的情况。利马克从最底部的红色单元格发射烟花。它覆盖了 $t_{1}=4$ 个单元格（标记为红色），爆炸并分成两部分（它们后续的移动标记为绿色）。所有爆炸都用“X”字符标记。在最后一张图中，有 $4$ 个红色、$4$ 个绿色、$8$ 个橙色和 $23$ 个粉色单元格。所以，被访问的单元格总数是 $4 + 4 + 8 + 23 = 39$。
![样例1图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750D/958e71e20888e0f3c92e01fa2be2e012117f122b.png)
对于第二个样例，下面的图展示了第 $4$、$5$ 和 $6$ 层级后的情况。中间的图展示了下一层级所有部分将移动的方向。
![样例2图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750D/c21fe29a69f3371f920085202e17e34b6a0270b1.png)
#### 样例 #1
**输入**
```
4
4 2 2 3
```
**输出**
```
39
```
#### 样例 #2
**输入**
```
6
1 1 1 1 1 3
```
**输出**
```
85
```
#### 样例 #3
**输入**
```
1
3
```
**输出**
```
3
```

### 算法分类
搜索（深度优先搜索 DFS 和广度优先搜索 BFS）

### 题解综合分析与结论
这几道题解主要围绕通过搜索算法模拟烟花的扩散过程来求解。由于 $n \leq 30$，$t_i \leq 5$，可知烟花经过的矩阵范围有限，为搜索算法提供了可行性。各题解的思路、要点和难点对比如下：
 - **思路**：均是模拟烟花发射、爆炸、分裂及各部分移动的过程，通过记录烟花经过的单元格来统计总数。
 - **算法要点**：利用数组记录方向，使用数据结构（结构体）存储节点信息，通过循环控制移动距离，通过队列（BFS）或递归（DFS）实现搜索。
 - **解决难点**：为避免重复计算导致超时，需要进行记忆化剪枝。

### 所选的题解
 - **作者：FreedomKing (赞：1) - 4星**
    - **关键亮点**：思路清晰，直接点明用广搜模拟烟花发散过程，代码注释详细，对广搜模板及关键步骤解释到位。
    - **重点代码 - 核心实现思想**：使用结构体 `node` 存储每个点的坐标 `x`、`y`，深度 `depth` 及方向 `dir`。`bfs` 函数中，利用队列存储待处理节点，每次取出队头节点，根据当前深度和方向移动并标记经过的单元格，然后向两个新方向扩展。
```cpp
struct node{int x,y,depth,dir;};//结构体，用来存储移动到每个点时的信息
void bfs(){
	queue<node>q;//队列，用来存下次移动的信息
	q.push({mid,mid,1,2});//存下起点
	while(!q.empty()){//只要还有要走的，就不停歇地循环下去
		int x=q.front().x,y=q.front().y,dep=q.front().depth,dir=q.front().dir;//把队头的信息取出
		q.pop();//用完就可以直接推出队列了
		if(vis[x][y][dep][dir]||dep>n) continue;//剪枝
		vis[x][y][dep][dir]=true;//标记剪枝
		for(int i=1;i<=a[dep];i++){
			x+=dx[dir];//移动
			y+=dy[dir];
			f[x][y]=1;//标记已被经过
		}
		q.push({x,y,dep+1,(dir+1)%8});//向下两个方向广搜
		q.push({x,y,dep+1,(dir+7)%8});
	}
	return;
}
```
 - **作者：crh1272336175 (赞：1) - 4星**
    - **关键亮点**：同样采用 BFS 方法，代码简洁明了，在常规 BFS 框架基础上，明确指出记忆化剪枝的必要性，并通过四维数组 `mp` 实现，有效避免 TLE。
    - **重点代码 - 核心实现思想**：结构体 `node` 与上述类似，`bfs` 函数中，每次取出队列中的节点，先判断是否已访问过（通过 `mp` 数组）及深度是否超过限制，若未访问则标记并按当前方向移动标记单元格，最后向两个新方向扩展。
```cpp
struct node
{
	int x,y,depth,dir;
};
queue<node> q;
void bfs()
{
	q.push({152,152,1,2});//起先向上移动,dir=2
	while(!q.empty())
	{
		node now=q.front(); q.pop();
		if(mp[now.x][now.y][now.depth][now.dir] || now.depth>n) continue;
		mp[now.x][now.y][now.depth][now.dir]=1;
		for(int i=1; i<=a[now.depth]; i++)
		{
			now.x+=dx[now.dir];
			now.y+=dy[now.dir];
			v[now.x][now.y]=1;
		}
		q.push({now.x,now.y,now.depth+1,(now.dir+1)%8});
		q.push({now.x,now.y,now.depth+1,(now.dir+7)%8});
	} 
}
```
 - **作者：JACK_POT (赞：0) - 4星**
    - **关键亮点**：采用深度优先搜索 DFS 遍历烟花分支，详细列举了每个方向分支的变化情况，通过设置偏移值处理坐标可能为负的问题，并利用四维数组 `f` 进行记忆化剪枝。
    - **重点代码 - 核心实现思想**：`dfs` 函数中，根据当前层级、坐标及方向，先进行记忆化剪枝，然后按当前方向移动并标记单元格，接着根据当前方向确定两个分支方向并递归调用 `dfs` 函数。
```cpp
void dfs(int step,int x,int y,int p,int q){//当前是第step层，开始坐标为[x,y]
//x轴方向为p，y轴方向为q(用-1，1，0表示，x轴和y轴方向是数组存储顺序)
	if(f[step][x][y][p+1][q+1]) return;
	f[step][x][y][p+1][q+1]=1;//记忆化剪枝
	if(step>n) return;//层数到n+1退出
	int len=a[step];//每次走的长度
	for(int i=1;i<=len;i++){
		x+=p; y+=q;//坐标更新
		Map[x][y]=1;//每一步都标记
	}
	int xx,yy;//表示下一步的方向
	if(p==-1&&q==0) xx=-1,yy=-1;
	else if(p==-1&&q==-1) xx=0,yy=-1;
	else if(p==0&&q==-1) xx=1,yy=-1;
	else if(p==1&&q==-1) xx=1,yy=0;
	else if(p==1&&q==0) xx=1,yy=1;
	else if(p==1&&q==1) xx=0,yy=1;
	else if(p==0&&q==1) xx=-1,yy=1;
	else if(p==-1&&q==1) xx=-1,yy=0;
	dfs(step+1,x,y,xx,yy);//分支1
	
	if(p==-1&&q==0) xx=-1,yy=1;
	else if(p==-1&&q==1) xx=0,yy=1;
	else if(p==0&&q==1) xx=1,yy=1;
	else if(p==1&&q==1) xx=1,yy=0;
	else if(p==1&&q==0) xx=1,yy=-1;
	else if(p==1&&q==-1) xx=0,yy=-1;
	else if(p==0&&q==-1) xx=-1,yy=-1;
	else if(p==-1&&q==-1) xx=-1,yy=0;
	dfs(step+1,x,y,xx,yy);//分支2
}
```

### 最优关键思路或技巧
 - **记忆化剪枝**：由于烟花的部分可能出现重复路径，使用记忆化剪枝能显著减少重复计算，避免超时。如通过四维数组记录已访问过的状态（包括坐标、深度、方向等信息），当再次遇到相同状态时直接跳过。
 - **方向数组**：利用数组记录不同方向的偏移量，方便实现烟花各部分的移动，使代码简洁且易于理解。

### 同类型题或类似算法套路拓展
此类题目属于搜索模拟类型，通常给定一些规则，要求模拟某个过程并统计相关结果。类似套路包括：
 - 明确搜索方向和状态表示，使用数组或结构体记录状态信息。
 - 对于可能出现重复状态的情况，及时进行记忆化剪枝。
 - 根据题目特点选择合适的搜索算法（DFS 或 BFS），若空间允许且需要快速找到最短路径等，BFS 较为合适；若注重递归逻辑和空间节省，DFS 可能更好。

### 洛谷相似题目推荐
 - **P1126 机器人搬重物**：通过搜索算法模拟机器人在网格中的移动，需要考虑障碍物等条件，与本题类似，需记录访问状态避免重复。
 - **P1605 迷宫**：同样是在迷宫环境下的搜索问题，可类比本题通过标记已访问单元格来统计路径或满足条件的单元格数量。
 - **P1596 湖计数**：利用搜索算法统计连通区域数量，与本题在搜索遍历和状态记录方面有相似之处。 

---
处理用时：113.42秒