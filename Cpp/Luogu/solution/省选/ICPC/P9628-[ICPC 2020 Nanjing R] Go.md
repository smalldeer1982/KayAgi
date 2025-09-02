# [ICPC 2020 Nanjing R] Go

## 题目描述

**围棋**是一种对抗性游戏，目的是用自己的石头比对手的石头包围更大的棋盘总面积。游戏的核心理念是**自由**，即一个开放点，或者更确切地说，是棋盘上垂直线和水平线的交叉点，上面没有石头，与群体接壤。

一个白色或黑色的石头，如果它至少有一个直接正交相邻的自由（上、下、左或右），或者必须与一块有生命的相同颜色的石头在同一个连接组中，那么它是有生命的，被称为**活着**。我们说，如果两块颜色相同的石头正交相邻，它们就直接相连。如果存在一系列石头 $s_1,s_2,…,s_k$ ，对于所有 $1\leq i<k$ ， $s_{i-1}$ 和 $s_i$ 颜色相同且正交相邻，则相同颜色的两块石头 $s_1$ 和 $s_k$ 属于同一连通组。

例如，在下图的左侧，两块白色的石头都没有活着，因为它们被周围的黑色石头捕获了；而在右边的部分，最右边的白色石头也没有生命，即使最左边的黑色石头也没有。

![Go](https://cdn.luogu.com.cn/upload/image_hosting/zjm3icu0.png)

给定一个有 $n$ 条垂直线和 $n$ 条水平线的棋盘，其中可能有一些石头躺在上面，请计算黑色石头捕获的白色石头的数量（也就是说，计算没有生命的白色石头数量）。上述例子的结果分别为 $2$ 和 $1$ 。

然而，我们亲爱的朋友 Kotori 认为这个问题让我们聪明的参赛者解决太简单了，所以她想让你独立翻转每块石头的颜色（也就是说，把黑色的石头变成白色的石头，反之亦然$^1$），并在每次翻转后找到相应的答案。

独立翻转的意思是，在翻转石头的颜色之前，其他石头应该变回原来的颜色。还要注意，这个问题中的数据不是来自真实世界，这意味着棋盘的大小不一定是 $19×19$ ，黑白石头的数量可以是任意整数。

$^1$反之亦然：在这里，它可以用 ```把白色的石头变成黑色的石头``` 来代替。这是现代英语中非常常见的短语，尤其是在学术写作中，所以请记住。

## 说明/提示

对于第二个测试样例，按照 $(1,2),(2,1),(2,2),(2,3),(3,1),(3,2)$ 的顺序翻转石头后，死亡的白色石头数量分别为 $1,0,1,2,0,0$ 。

对于第三个测试样例，棋盘上的所有石头，无论是黑色还是白色，都不是活着的。

## 样例 #1

### 输入

```
3
2
.o
..
3
.x.
xoo
ox.
2
oo
oo```

### 输出

```
0
870527216
485539347```

# 题解

## 作者：C1942huangjiaxu (赞：0)

将白棋看成点，相邻的白棋之间连一条边。

如果一个棋子的周围有空位，则认为这个棋子是**活棋子**。

如果一个连通块中有活棋子，那么这个连通块就是活的。

答案即为死的连通块大小和，需要维护每个连通块的**大小**和**活棋子数**。

求出初始局面的答案，考虑改变一枚棋子的颜色，可能改变的只有与它相邻的连通块。

我们先把这些连通块的答案减去，改变颜色后，再把新的答案加上。

**如果黑棋变为白棋**，直接把相邻连通块信息合并即可，**一个连通块可能有多条边与该棋子相连**，注意去重。

**如果白棋变为黑棋**，用 tarjan 求出割点，并建立 DFS 树，分 $2$ 种情况讨论。

+ 如果不是割点，那么没有产生新的连通块，只需要判断该棋子是否是**原先连通块唯一的活棋子**即可。

+ 如果是割点，会分裂出多个连通块，枚举 DFS 树中儿子分裂出去的连通块，用整个连通块的信息减去儿子分裂出去的连通块的信息，即可得到父亲所在连通块的信息。

时间复杂度 $O(n^2)$，主要难点在代码实现上。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005,M=1e6+5,B=1e6+7,P=1e9+7;
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
int T,n,id[N][N],cnt,px[M],py[M],ans,va[M],Ans;
int dfn[M],low[M],co[M],tot,cl[M],Cl[M],sz[M],Sz[M];
bool ch[M],cut[M];
vector<int>e[M],g[M];
char s[N][N];
bool onb(int x,int y){
	return x>0&&x<=n&&y>0&&y<=n;
}
bool lf(int x,int y){
	for(int k=0;k<4;++k){
		int i=x+dx[k],j=y+dy[k];
		if(onb(i,j)&&s[i][j]=='.')return true;
	}
	return false;
}
void tarjan(int x){
	dfn[x]=low[x]=++dfn[0],co[x]=tot,cl[x]=ch[x],sz[x]=1;
	for(auto v:e[x]){
		if(!dfn[v]){
			g[x].push_back(v);
			tarjan(v);
			low[x]=min(low[x],low[v]);
			if(low[v]>=dfn[x])cut[x]=true;
			cl[x]+=cl[v],sz[x]+=sz[v];
		}else low[x]=min(low[x],dfn[v]);
	}
}
void calc(int x){
	if(!Cl[co[x]])va[x]-=Sz[co[x]];
	if(cut[x]){
		int Rs=Sz[co[x]]-1,Rc=Cl[co[x]]-ch[x];
		for(auto v:g[x])if(low[v]>=dfn[x]){
			if(!cl[v])va[x]+=sz[v];
			Rs-=sz[v],Rc-=cl[v];
		}
		if(!Rc)va[x]+=Rs;
	}else{
		if(Cl[co[x]]-ch[x]==0)va[x]+=Sz[co[x]]-1;
	}
	for(auto v:g[x])calc(v);
}
int rev(int i,int j){
	if(s[i][j]=='o')return va[id[i][j]];
	int res=0,Rs=1,Rc=lf(i,j);
	set<int>S;
	for(int k=0;k<4;++k){
		int x=i+dx[k],y=j+dy[k];
		if(onb(x,y)&&s[x][y]=='o')S.insert(co[id[x][y]]);
	}
	for(auto v:S){
		if(!Cl[v])res-=Sz[v];
		Rs+=Sz[v],Rc+=Cl[v];
	}
	if(!Rc)res+=Rs;
	return res;
}
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=cnt;++i)e[i].clear(),g[i].clear(),co[i]=va[i]=dfn[i]=0;
	cnt=dfn[0]=tot=ans=Ans=0;
	for(int i=1;i<=n;++i)scanf("%s",s[i]+1);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)if(s[i][j]=='o'){
			id[i][j]=++cnt;
			ch[cnt]=lf(i,j);
			px[cnt]=i,py[cnt]=j;
		}
	for(int i=1;i<=cnt;++i)
		for(int j=0;j<4;++j){
			int x=px[i]+dx[j],y=py[i]+dy[j];
			if(onb(x,y)&&s[x][y]=='o')e[i].push_back(id[x][y]);
		}
	for(int i=1;i<=cnt;++i)if(!co[i]){
		++tot;
		tarjan(i);
		Cl[tot]=cl[i],Sz[tot]=sz[i];
		if(g[i].size()>1)cut[i]=true;
		else cut[i]=false;
		if(!cl[i])ans+=Sz[tot];
		calc(i);
	}
	for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)if(s[i][j]!='.'){
		int t=ans+rev(i,j);
		Ans=(1ll*Ans*B+t)%P;
	}
	printf("%d\n",Ans);
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：zheng_zx (赞：0)

## P9628 [ICPC2020 Nanjing R] Go

[题目传送门](https://www.luogu.com.cn/problem/P9628)

### 分析

---

预处理所有白棋的连通性，以及每个白棋能接触到多少个空格子 $alive[i]$。某个白棋被断气的充要条件是：它的整个连通块所有棋子的 $alive$ 都为 $0$。

首先考虑某个白棋变成了黑棋。如果原来的白棋连通块都断气了，那本次继续保持断气。否则，我们就要考察周围的白棋，可能部分连通块会断气。

这个 ```task``` 的本质是点双。如果中间这个变成黑棋的白棋是割点，那么割点下所有 $\operatorname{low}$ 没有越过它的连通块均可能影响答案。依次考察他们的 $alive$ 的和，如果是 $0$ 的话就产生断气后的贡献。

黑棋变白棋比较简单。直接观察白棋附近有没有空格，或者周围四个方向的白棋连通块的 $alive$ 有没有不是 $0$ 的。如果存在的话，整体就不会断气（所以我们得把之前断的给加上），否则继续保持断气。

---

