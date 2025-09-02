# 题目信息

# Roads not only in Berland

## 题目描述

给定一个有 $n$ 个顶点，$n-1$ 条边的无向图。  
每一次操作都能去掉一条边，并且重新在某两个顶点之间连一条新边。  
试求需要多少次操作，才能使得从任一顶点都能到达其他的所有顶点，并构造方案。

$2 \le n \le 1000$。

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
0
```

## 样例 #2

### 输入

```
7
1 2
2 3
3 1
4 5
5 6
6 7
```

### 输出

```
1
3 1 3 7
```

# AI分析结果

### 题目内容
#### 题目描述
给定一个有 $n$ 个顶点，$n - 1$ 条边的无向图。  
每一次操作都能去掉一条边，并且重新在某两个顶点之间连一条新边。  
试求需要多少次操作，才能使得从任一顶点都能到达其他的所有顶点，并构造方案。

$2 \le n \le 1000$。

#### 样例 #1
**输入**
```
2
1 2
```
**输出**
```
0
```

#### 样例 #2
**输入**
```
7
1 2
2 3
3 1
4 5
5 6
6 7
```
**输出**
```
1
3 1 3 7
```

### 算法分类
并查集

### 综合分析与结论
这些题解主要围绕并查集和深度优先搜索（DFS）两种思路展开。
 - **并查集思路**：利用并查集判断图的连通性，确定需要删除和添加的边。在输入边时，若两端点已在同一连通块内，则该边为待删除边；统计不同祖先的数量，可确定需添加边的数量。添加边时，将不同连通块的祖先相连。不同题解在细节处理和代码实现上略有差异，如使用队列、数组、集合等不同数据结构存储待删除边或连通块信息。
 - **DFS思路**：通过DFS生成搜索树，搜索树外的边即为待删除边。从每个连通分量中任取一点，将这些点依次相连，使图连通。

### 所选的题解
 - **作者：灵茶山艾府 (赞：10)  星级：5星  关键亮点：使用DFS解决问题，代码简洁，时间复杂度为$O(n)$，思路清晰，无需并查集。**
```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n, v, w int
	Fscan(in, &n)
	g := make([][]int, n+1)
	for i := 1; i < n; i++ {
		Fscan(in, &v, &w)
		g[v] = append(g[v], w)
		g[w] = append(g[w], v)
	}

	type edge struct{ v, w int }
	deletes := []edge{}
	vis := make([]bool, n+1)
	var f func(v, fa int)
	f = func(v, fa int) {
		vis[v] = true
		for _, w := range g[v] {
			if!vis[w] {
				f(w, v)
			} else if w!= fa && v < w {
				deletes = append(deletes, edge{v, w})
			}
		}
	}
	vs := []int{}
	for i := 1; i <= n; i++ {
		if!vis[i] {
			vs = append(vs, i)
			f(i, 0)
		}
	}

	Fprintln(out, len(deletes))
	for i, p := range deletes {
		Fprintln(out, p.v, p.w, vs[i], vs[i+1])
	}
}
```
核心实现思想：先通过DFS遍历图，标记访问过的节点，在遍历过程中找到非树边（即会形成环的边）存入`deletes`切片。然后从每个未访问的节点出发进行DFS，将这些起始节点存入`vs`切片。最后按顺序输出删除的边以及连接不同连通分量的新边。

 - **作者：Maxwang (赞：6)  星级：5星  关键亮点：对并查集原理及本题思路阐述详细，代码注释丰富，便于理解。**
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<set>
using namespace std;
const int MAXN = 1e3 + 19;
struct edge{
	int u,v;
};
vector<int>G[MAXN];//存图 

queue<edge>del;//待删目录 

set<int>fa;//祖先集合 

struct uni{//并查集 
	int bin [ MAXN ];
	uni(){//初始自己是自己的祖先 
		for(int i = 0  ; i < MAXN ;i++)
		bin[i]=i;
	}
	int anc(int x)//找祖先 
	{
		if( bin[x] == x )return x;
		else return bin[x] = anc( bin[x] ); //路径压缩 
	} 
	void link( int x, int y )//认亲 
	{
		bin[ anc(x) ] = anc(y);
	}
}u;
int n;
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i < n ; i++)
	{
		int x,y;
		scanf( "%d%d",&x,&y);
		
		if(u.anc(x) == u.anc(y))//如果已经在同一连通块了 
		del.push( (edge) {x,y} );//加入待删目录 
		
		else//否则 
		u.link( x, y );//正常建图 
	}
	
	for(int i = 1 ; i <= n ; i++)
	{
		int x = u.anc(i);//找各个点的祖先 
		fa.insert(x);//加入集合（去重） 
	}
		
	cout << fa.size()-1 << endl;//集合的大小-1就是需要连的边数 
	
	if(fa.size()!=1)//如果未完全联通 
	{
		set<int>::iterator it=fa.begin();//取第一个祖先 
		int root = *it;
		
		fa.erase(root);//删掉所取的祖先 
		
		for(set<int>::iterator it=fa.begin();it!=fa.end();it++)//遍历其他祖先 
		{
			edge key = del.front();
			del.pop();//从待删目录里取边 
			
			printf("%d %d %d %d\n",key.u,key.v,root,*it);//输出 
		}
	}
	puts("");//好习惯 
	return 0;
} 
```
核心实现思想：定义并查集结构`uni`，在输入边时，利用并查集判断边的两端点是否在同一连通块，若是则将该边加入待删队列`del`，否则合并连通块。通过`set`集合`fa`统计不同祖先数量，确定需添加边数。最后从`del`队列取边，连接不同连通块的祖先。

 - **作者：ahawzlc (赞：4)  星级：4星  关键亮点：代码简洁明了，对并查集的使用和操作步骤清晰。**
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define F first
#define S second
using namespace std;
const int N=10005;
int f[N],gr[N],n,tot,cnt,now;
pair<int,int> d[N];
int find(int x) {//并查集找祖宗
	if(f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
bool merge(int x,int y) {//并查集合并
	x=find(x);
	y=find(y);
	if(x!=y) f[x]=y;
	else return 1;
	return 0;
}
void del(int i) {//处理+输出函数
	printf("%d %d %d %d\n",d[i].F,d[i].S,gr[now],gr[cnt]);//输出回收站当前边、当前合并的连通块祖宗
	merge(gr[now++],gr[cnt]);//合并连通块并将当前连通块定位到下一个
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<n;i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		if(merge(x,y)) d[++tot]=make_pair(x,y);//扔进回收站
	}
	for(int i=1;i<=n;i++) if(f[i]==i) gr[++cnt]=i;//统计连通块的祖宗
	now=1;
	printf("%d\n",tot);
	for(int i=1;i<=cnt-1;i++)
		del(i);//处理+输出
	return 0;
}
```
核心实现思想：定义并查集的查找`find`和合并`merge`函数。输入边时，若合并失败（即两端点已在同一连通块），将边存入`d`数组。统计连通块的祖先存入`gr`数组。通过`del`函数输出删除边和连接不同连通块的新边，并在函数内合并连通块。

### 最优关键思路或技巧
 - **DFS思路**：利用DFS遍历图的特性，简洁地找到非树边作为待删除边，避免了并查集路径压缩等复杂操作，时间复杂度低至$O(n)$。
 - **并查集思路**：利用并查集判断图的连通性，高效确定需要删除和添加的边，通过巧妙的数据结构（如队列、集合等）存储和处理边与连通块信息，使代码逻辑清晰。

### 同类型题或类似算法套路
此类题目通常围绕图的连通性展开，常见套路是利用并查集判断连通块，或利用DFS、BFS遍历图。对于有边权或求最小代价使图连通的问题，可能会结合最小生成树算法（如Kruskal、Prim算法）。

### 推荐题目
 - [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)：基础并查集模板题，帮助理解并查集基本操作。
 - [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)：通过实际场景应用并查集，加深对并查集概念的理解。
 - [P1197 [JSOI2008] 星球大战](https://www.luogu.com.cn/problem/P1197)：结合并查集与图论，在动态操作中维护图的连通性，提升对并查集应用的能力。

### 个人心得摘录与总结
 - **作者Maxwang**：强调了理解题目中“答案不唯一，输出任何答案”这一条件的重要性，避免因追求唯一答案而陷入复杂逻辑。总结了并查集“认亲和找祖先”的通俗理解方式，有助于初学者快速掌握并查集概念。 

---
处理用时：101.57秒