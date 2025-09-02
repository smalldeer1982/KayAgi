# Paint it really, really dark gray

## 题目描述

给你一棵节点编号为$1...n$的树，每个节点都有两种颜色：粉色或黑色。现在你要从1号节点（即树根）出发，每经过一个节点，该节点的颜色就会改变。（粉色变为黑色，黑色变为粉色）。

现在请你找出一条从1号节点（即树根）出发的路径，使得沿这条路径走完后，所有的节点颜色都变为黑色。**注意：你可以经过一个节点或一条边多次，并且路径不要求一定要在1号节点（即树根）结束。**

-----------------------------

## 样例 #1

### 输入

```
5
1
1
-1
1
-1
2 5
4 3
2 4
4 1
```

### 输出

```
1 4 2 5 2 4 3 4 1 4 1
```

# 题解

## 作者：MY（一名蒟蒻） (赞：11)

[原题传送门](https://www.luogu.com.cn/problem/CF717E)

本题的难点主要是在定义递归结束后某个节点的状态。定义 $\text{dfs(x)}$ 表示在递归完以 $\text{x}$ 为根的子树把这个子树染黑后，停下来的点？显然非常不可做。

考虑定义 $\text{dfs(x)}$ 表示从 $\text{x}$ 开始走，**最后回到** $\text{x}$ ，将以 $\text{x}$ 为根的子树中除了 $\text{x}$ 以外的节点都变成黑色（$\text{x}$ 的颜色可以任意）。

这样确定了递归后我们在什么位置，题目经过这样的转化变得可做起来。

这个 $\text{x}$ 的颜色之后会由父亲处理。

---
那么如何`dfs`，或者说`dfs`的流程是怎样的呢？

$\text{dfs(x)}$ ：先往每个子树走，走回来后，如果 $\text{x}$ 一个儿子 $\text{y}$ 是白色，就从 $\text{x}$ 走到 $\text{y}$ 再走回 $\text{x}$ 把 $\text{y}$ 变黑。

这样做一遍后，除了根节点以外都是黑色，然后如果根是白色，找一个儿子（一定是黑色），过去-回来-过去然后结束路径即可。

容易证明这样构造的路径长度是可以接受的，大概是常数乘上 $\text{n}$ 。

时间复杂度 $\text{O(n)}$ ， $\text{dfs}$ 时输出路径即可。

感觉思路已经说得非常清晰了，实现基本就是翻译一下。读者可以锻炼一下自己的码力。建议大家不看以下代码自己写出来。
## Code
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace std;

const int N=2e5+10;

int n,fir[N],tot,col[N],fa[N];
struct node {int to,nex;} e[N << 1];

void add(int u,int v)
{
	e[++tot].to=v;
	e[tot].nex=fir[u];
	fir[u]=tot;
	return ;
}

void init(int x,int dad)
{
	fa[x]=dad;
	for(int i=fir[x];i;i=e[i].nex)
		if(e[i].to^dad) init(e[i].to,x);
	return ; 
}

void dfs(int x)
{
	printf("%d ",x);
	for(int i=fir[x];i;i=e[i].nex)
		if(e[i].to^fa[x])
		{
			col[e[i].to]^=1;//往子树走
			dfs(e[i].to);
			printf("%d ",x);
			col[x]^=1;//回来
			if(!col[e[i].to])//处理儿子颜色
			{
				printf("%d %d ",e[i].to,x);
				col[e[i].to]=1;
				col[x]^=1;
			}
		}
	return ;
}

int main()
{
//	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {scanf("%d",&col[i]); if(col[i] < 0) col[i]=0;}
	for(int i=1,u,v;i<n;i++) {scanf("%d%d",&u,&v); add(u,v); add(v,u);}
	init(1,0); dfs(1);
	if(!col[1]) printf("%d 1 %d ",e[fir[1]].to,e[fir[1]].to);//最后的白点
//	fclose(stdin); fclose(stdout);
	return 0;
}
```
难度建议蓝。

感谢阅读！您的评论和点赞是对作者最大的支持！

---

## 作者：water_tomato (赞：5)

[博客版本](https://code.watertomato.com/cf717e-paint-it-really-really-dark-gray-%e9%a2%98%e8%a7%a3/)

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF717E)

有一棵树有粉点有黑点，从根开始走，每走到一个点都会改变颜色。求一种方案使所有点变成黑色。

## 解析

我们考虑使用递归的方式寻找答案。假设一棵树的深度只有 $2$，那么我们只需要从根开始，找到粉点，走过去再回来，重复几次，就可以使下一层的所有点变为黑色。

以这种方式一层一层染色，最后对于根节点，如果为黑色不用处理，否则，走下去，走回来，再走下去然后停止就可以了（题目不要求一定在树根结束）。

详见代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
struct edge{
	int to,nxt;
}e[N<<1];
int head[N],cnt,col[N],tot,step[N<<5],n;//step要开大点！ 
inline void add(int u,int v){
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
inline void change(int u){
	col[u]=-col[u];
}
inline void dfs(int u,int fa){
	bool yezi=true;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
		yezi=false;
	}
	if(!yezi){//走到 u
		step[++tot]=u;
		change(u);
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,u);
		if(col[v]==-1){//处理儿子中的粉点
			step[++tot]=v;
			step[++tot]=u;
			change(v);change(u);
		}
	}
	if(!yezi&&fa!=0){//走回到父亲
		step[++tot]=fa;
		change(fa);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&col[i]);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	change(1);
	dfs(1,0);
	if(col[1]==-1){
		int i=head[1];
		int v=e[i].to;
		step[++tot]=v;
		step[++tot]=1;
		step[++tot]=v;
	}
	for(int i=1;i<=tot;i++)
		printf("%d ",step[i]);
	return 0;
}
```



---

