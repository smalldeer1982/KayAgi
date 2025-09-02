# 题目信息

# [USACO09OCT] Papaya Jungle G

## 题目描述

Bessie has wandered off the farm into the adjoining farmer's land. He raises delicious papaya fruit, which is a delicacy for cows. The papaya jungle is partitioned into a grid of squares with R rows and C columns (1 <= R <= 40, 1 <= C <= 40), as is popular in Wisconsin. Bessie can travel from a given square to any existing adjacent square whose route is parallel to the X or Y axis.  So in the

following diagram, if Bessie is at the square labeled 'B', she can travel to any of the squares labeled 'T':

.T.
TBT
.T.
Bessie always starts out by munching the papayas in square

(row=1,col=1).  After she's done with one square, Bessie always uses her trusty binoculars to count the low-hanging fruit in each of the adjacent squares. She then always moves to the square with the most visible uneaten fruit (a square that happily is always unique).

Sooner or later, following this rule, Bessie always ends up in square (R,C) and eats the fruit there.

Given the dimensions of the papaya jungle and the amount of fruit F\_ij in each square (1 <= F\_ij <= 100), determine the total number of fruit Bessie consumes for a given papaya jungle.

POINTS: 80

Bessie不小心游荡出Farmer John的田地，而走进了相邻的农民的地里。她举起一个木瓜，木瓜对奶牛来说可是不可多得得美味。这个木瓜林像一般的威斯康星州的田地一样被分割成一个R行C列的网格(1 <= R <= 40, 1 <= C <= 40)。Bessie可以从一个格沿着一条跟X轴或Y轴平行的直线走到邻接的另一个格。Bessie发现一开始她自己在木瓜林的(1,1)，也就是第一行第一列慢悠悠地咀嚼着木瓜。

Bessie总是用她最信赖地双筒望远镜去数每一个邻接的格里挂着的木瓜的数目。然后她就游荡到那个有最多没有被吃掉的木瓜的邻接的格子（保证这样的格子只有一个）。

按照这种移动方法，最终Bessie总是会在(R,C)停止然后吃掉那里的木瓜。

给定这个木瓜林的大小及每个格的木瓜数F\_ij(1 <= F\_ij <= 100), 要求Bessie一共吃了多少个木瓜。


## 说明/提示

Three rows; four columns. Bessie starts in upper left corner at the '3'.


Bessie eats the papayas in the order given by the letters next to the numbers below:

(1,1) ---> (1,C) 

(1,1) 3a  3   4g  5h  (1,C) 

|   4b  5c  3f  2i    |

(R,1) 1   7d  4e  2j  (R,C) 

(R,1) ---> (R,C) 

She declines to eat 4 of the papayas but consumes 39 (visiting all but two squares of the grid). 



## 样例 #1

### 输入

```
3 4 
3 3 4 5 
4 5 3 2 
1 7 4 2 
```

### 输出

```
39 
```

# AI分析结果

### 算法分类
**模拟**

### 综合分析与结论
题目要求模拟Bessie在网格中的移动过程，每次选择相邻格子中木瓜最多的一个，直到到达终点。所有题解的核心思路都是通过模拟Bessie的移动过程，逐步累加她吃掉木瓜的数量。虽然部分题解使用了DFS或BFS，但本质上仍然是模拟过程，因此最合适的分类是**模拟**。

### 所选高星题解
#### 题解1：作者：zjj20051228 (赞：9)
**星级：5星**
**关键亮点：**
- 使用DFS实现模拟过程，代码简洁清晰。
- 通过方向数组`dx`和`dy`简化了相邻格子的遍历。
- 直接在DFS中累加木瓜数量，逻辑清晰。

**核心代码：**
```cpp
void dfs(int x,int y)
{
	sum=sum+a[x][y];
	a[x][y]=0;
	if(x==r&&y==c)
		return;
	int mx,my,ans=0;
	for(int i=0;i<4;i++)
	{
		int tx=x+dx[i];
		int ty=y+dy[i];
		if(tx>=1&&tx<=r&&ty>=1&&ty<=c&&a[tx][ty]>ans)
		{
			ans=a[tx][ty];
			mx=tx,my=ty;
		}	
	}
	dfs(mx,my);	
}
```
**实现思想：**
- 从起点开始，每次选择相邻格子中木瓜最多的一个，递归调用DFS继续移动，直到到达终点。

#### 题解2：作者：a___ (赞：2)
**星级：4星**
**关键亮点：**
- 使用简单的`while`循环模拟移动过程，代码直观易懂。
- 通过条件判断选择下一个移动的格子，逻辑清晰。

**核心代码：**
```cpp
while (1)
{
    sum+=g[i][j]; g[i][j]=0;
    if (i==r&&j==c) break;
    else if (g[i+1][j]>g[i][j+1]&&g[i+1][j]>g[i][j-1]&&g[i+1][j]>g[i-1][j]&&i+1<=r) i++;
    else if (g[i-1][j]>g[i][j+1]&&g[i-1][j]>g[i][j-1]&&g[i-1][j]>g[i+1][j]&&i-1>=1) i--;
    else if (g[i][j+1]>g[i+1][j]&&g[i][j+1]>g[i][j-1]&&g[i][j+1]>g[i-1][j]&&j+1<=c) j++;
    else if (g[i][j-1]>g[i][j+1]&&g[i][j-1]>g[i+1][j]&&g[i][j-1]>g[i-1][j]&&j-1>=1) j--;
}
```
**实现思想：**
- 通过`while`循环不断选择下一个移动的格子，直到到达终点。

#### 题解3：作者：deamoon_2 (赞：0)
**星级：4星**
**关键亮点：**
- 使用简单的循环和条件判断模拟移动过程，代码简洁。
- 通过方向数组`x`和`y`简化了相邻格子的遍历。

**核心代码：**
```cpp
while(i!=n||j!=m)
{
	int t,s=0;
	for(int l=1;l<=4;l++)
	{
		if(a[i+x[l]][j+y[l]]>s)
		{
			s=a[i+x[l]][j+y[l]];
			t=l;
		}
	}
	a[i][j]=0; 
	i+=x[t];
	j+=y[t];
	sum+=s;
}
```
**实现思想：**
- 通过`while`循环不断选择下一个移动的格子，直到到达终点。

### 最优关键思路或技巧
- **方向数组**：使用`dx`和`dy`数组简化相邻格子的遍历，避免重复代码。
- **模拟过程**：通过循环或递归模拟Bessie的移动过程，逐步累加木瓜数量。
- **边界检查**：在移动时始终检查是否越界，确保程序正确运行。

### 可拓展之处
- **类似题目**：可以考虑在更复杂的网格中进行类似的模拟，例如加入障碍物或动态变化的木瓜数量。
- **算法优化**：如果网格较大，可以考虑使用优先队列或其他数据结构优化选择下一个格子的过程。

### 推荐题目
1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1131 [ZJOI2007]时态同步](https://www.luogu.com.cn/problem/P1131)

---
处理用时：43.53秒