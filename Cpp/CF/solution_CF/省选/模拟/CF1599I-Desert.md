# Desert

## 题目描述

众所周知，一个无向图是仙人掌图当且仅当每条无向边至多属于一个环 。特别的，只有一个点的图也是仙人掌图 。

如果无向图的每一个连通块都是一个仙人掌图，那么我们称这个图是 “沙漠” 。( 类比树和森林之间的关系 )

给定一个 $N$ 个点 $M$ 条边的无向图，边的编号分别为 $E_1,E_2…E_M$ 。

求数字对 $(L,R)$ 的个数 ，$(1\leq L\leq R\leq M)$，使得只由 $E_L,E_{L+1}…E_R$ 组成的无向图是 “沙漠” 。

## 样例 #1

### 输入

```
5 6
1 2
2 3
3 4
4 5
5 1
2 4```

### 输出

```
20```

## 样例 #2

### 输入

```
2 3
1 2
1 2
1 2```

### 输出

```
5```

# 题解

## 作者：BlankAo (赞：2)

**CF1599I Desert / [原题链接](https://www.luogu.com.cn/problem/CF1599I)**

## 题意

> **仙人掌**是一张无向连通图，在一个仙人掌上，任意一条边至多只会出现在一个环上。
>
> **荒漠**是一张无向图，一个荒漠的每个极大连通分量都是一个仙人掌。

给定一个 $n$ 个点 $m$ 条边的无向图，求有多少对 $l,r\in [1,m]$，使得只保留编号在 $[l,r]$ 中的边后，图变成荒漠。

数据范围：$n\le 2.5\times 10^5,m\le 5\times 10^5$

## 解法

转化一下题目，运用尺取法（Two-pointer），维护两个指针 $l,r$，代表现在 $[l,r]$ 是合法的区间。那么 $r$ 右移时，我们加边； $l$ 右移时，我们删边。

然后就可以用 Link Cut Cactus 去维护加边、删边了。但是我不会 LCC，于是用 LCT 去维护。

LCT 不支持维护边的信息，将边拆点即可，设为 $E$ 点。

LCT 上维护两个值 $val=0/1,tot$，依次代表 $E$ 点是否在某个环中，这个点的子树是否有在环中的 $E$ 点。

### 加边

设加第 $r$ 条边 $(x,y)$。如果 $x,y$ 不连通，直接加入即可。如果联通，查询 $x,y$ 间是否有在环中的 $E$ 点（即查询 $x\sim y$ 的 Splay 根节点的 $tot$）。

- *如果没有，那么加边后这些 $E$ 点都变成环中边了。将它们的 $val$ 设成 1，用 lazytag 维护。同时维护一个值 $id$，代表 $val=1$ 是来自于哪条边。即将 $x\sim y$ 的 $id:=r$，同样用 lazytag 维护，具体原因下文会讲。
- 如果有，那么加边会导致会有 $E$ 点对应的边同时处于两个环中（一个是现在加的边，一个是以前让它的 $val=1$ 的边），就不是荒漠了。不断地 $l:=l+1$，删边，直到查询到这种情况不出现为止。

### 删边

设删第 $l$ 条边 $(x,y)$。如果 $x,y$ 联通，那么就直接剪断。

但是这样做会有错误。如果以前 $x,y$ 在一个环中，但是环边没有加入 LCT（上述带 * 的情况）那么会造成信息的丢失。我们把根的 $id$ 对应的边再加入进 LCT 即可，同时要清零 $id$。

如果不连通，那么这个边加边时就是带 * 的情况。我们把 $x\sim y$ 的 Splay， $val:=0,id:=0$ 即可。用 lazytag 维护。

时间复杂度 $O(nlogn)$。（$n$ 为拆点后的总点数）

## 代码

```c++
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define lsn(o) tre[o].son[0]
#define rsn(o) tre[o].son[1]
using namespace std;
const int n7=1012345,m7=n7;
struct dino{int x,y;}e[m7];
struct mist{int fa,son[2];int laz,id,lazid;bool val,tot,fp;}tre[n7];
int n,m;long long ans;

int rd(){
	int shu=0;bool fu=0;char ch=getchar();
	while( !isdigit(ch) ){if(ch=='-')fu=1;ch=getchar();}
	while( isdigit(ch) )shu=(shu<<1)+(shu<<3)+ch-'0',ch=getchar();
	return fu?-shu:shu;
}

void updat(int o){
	tre[o].tot=(tre[lsn(o)].tot|tre[rsn(o)].tot);
	if(o>n)tre[o].tot|=tre[o].val;
}

void pudown(int o){
	if(tre[o].laz==1){
		tre[lsn(o)].val=tre[rsn(o)].val=1;
		tre[lsn(o)].tot=tre[rsn(o)].tot=1;
		tre[lsn(o)].laz=tre[rsn(o)].laz=1;
	}
	if(tre[o].laz==-1){
		tre[lsn(o)].val=tre[rsn(o)].val=0;
		tre[lsn(o)].tot=tre[rsn(o)].tot=0;
		tre[lsn(o)].laz=tre[rsn(o)].laz=-1;
	}
	tre[o].laz=0;
	
	if(tre[o].lazid>0){
		tre[lsn(o)].id=tre[rsn(o)].id=tre[o].lazid;
		tre[lsn(o)].lazid=tre[rsn(o)].lazid=tre[o].lazid;
	}
	if(tre[o].lazid==-1){
		tre[lsn(o)].id=tre[rsn(o)].id=0;
		tre[lsn(o)].lazid=tre[rsn(o)].lazid=-1;
	}
	tre[o].lazid=0;

	if(tre[o].fp){
		tre[lsn(o)].fp^=1,tre[rsn(o)].fp^=1;
		swap( lsn(o),rsn(o) );
		tre[o].fp=0;
	}
	
	tre[0]=(mist){0,{0,0},0,0,0,0,0,0};
}

bool Dwhi(int o){return rsn(tre[o].fa)==o;}

bool izrot(int o){return lsn(tre[o].fa)==o||rsn(tre[o].fa)==o;}

void rota(int o){
	int y=tre[o].fa,z=tre[y].fa,whi=Dwhi(o);
	int fawhi=(izrot(y)?Dwhi(y):-1),v=tre[o].son[!whi];
	tre[v].fa=y,tre[y].son[whi]=v;
	tre[y].fa=o,tre[o].son[!whi]=y;
	tre[o].fa=z;if(~fawhi)tre[z].son[fawhi]=o;
	updat(y),updat(o);
}

void puall(int o){
	if( izrot(o) )puall(tre[o].fa);
	pudown(o);
}

void splay(int o){
	puall(o);
	while( izrot(o) ){
		int y=tre[o].fa;
		if( izrot(y) ){
			Dwhi(o)==Dwhi(y)?rota(y):rota(o);
		}
		rota(o);
	}
}

void aces(int o){
	int las=0;
	while(o){
		splay(o),rsn(o)=las,updat(o);
		las=o,o=tre[o].fa;
	}
}

void Mroot(int o){
	aces(o),splay(o),tre[o].fp^=1;
}

int Froot(int o){
	aces(o),splay(o);
	while( lsn(o) )pudown(o),o=lsn(o);
	splay(o);
	return o;
}

void split(int o1,int o2){
	Mroot(o1),aces(o2),splay(o2);
}

void link(int o1,int o2){
	if( Froot(o1)==Froot(o2) )return;
	Mroot(o1),tre[o1].fa=o2;
}

bool cancut(int o1,int o2){
	if( Froot(o1)^Froot(o2) )return 0;
	split(o1,o2);
	if( tre[o1].fa^o2 || lsn(o1) || rsn(o1) )return 0;
	return 1;	
}

void cut(int o1,int o2){
	if( cancut(o1,o2) )tre[o1].fa=lsn(o2)=0,updat(o2);
}

int Gdot(int now){
	pudown(now);
	int o=lsn(now);
	while(o){
		if(o>n)return o;
		else pudown(o),o=rsn(o);
	}	
	o=rsn(now);
	while(o){
		if(o>n)return o;
		else pudown(o),o=lsn(o);
	}
	return 0;
}

bool check(int o1,int o2){
	if( Froot(o1)^Froot(o2) )return 1;
	split(o1,o2);int o=Gdot(o2);splay(o);
	if(!tre[o].tot)return 1;
	return 0;
}

int main(){
	n=rd(),m=rd();
	rep(i,1,m)e[i]=(dino){rd(),rd()};
	for(int l=1,r=0;r<=m;++r){
		ans=ans+r-l+1;
	//	printf("!%d %d\n",l,r);
		if(r==m)break; 
		while( !check(e[r+1].x,e[r+1].y) ){
			if( !cancut(e[l].x,l+n)  ){
				split(e[l].x,e[l].y);
				int o=Gdot(e[l].y);
				if(o){
					splay(o);
					tre[o].val=tre[o].tot=0,tre[o].laz=-1;
					tre[o].id=0,tre[o].lazid=-1;
				}
			}
			else{
				int z=tre[l+n].id;
				cut(e[l].x,l+n),cut(l+n,e[l].y);
				if(z){					
					link(e[z].x,z+n),link(z+n,e[z].y);
					split(e[l].x,e[l].y);
					int o=Gdot(e[l].y);
					if(o){
						splay(o);
						tre[o].val=tre[o].tot=0,tre[o].laz=-1;
					}
				}
			}
			l++;
		}
		if( Froot(e[r+1].x)==Froot(e[r+1].y) ){
			split(e[r+1].x,e[r+1].y);
			int o=Gdot(e[r+1].y);
			if(o){
				splay(o);			
				tre[o].val=tre[o].tot=1,tre[o].laz=1;
				tre[o].id=tre[o].lazid=r+1;
			}
		}
		else{
			link(e[r+1].x,r+1+n),link(r+1+n,e[r+1].y);		
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：momentous (赞：0)

题面就不重复了。

我们发现，当一个图是沙漠的时候，那么它的子图一定是一个沙漠。

这使得我们可以使用双指针解决这个问题。

我们考虑对每一个 $l$ ，求出一个最大的 $r$ ，使得当只保留 $[l,r]$ 中的边时，图是一个沙漠。

我们需要一个数据结构去维护这个沙漠。

这个数据结构需要支持： 1. 插入/删除一条边 2. 判断一条边插入后图是否为沙漠。

显然可以想到用 LCT 去维护。

用 LCT 去维护沙漠中每一个仙人掌的生成树构成的森林。

#### （尝试并）插入边

当我们插入一条边 $(x,y)$ 的时候，如果 $x$ 和 $y$ 已经联通了，那么会产生一个环。

由于是沙漠，这就要求环上不能有边已经存在环中。

由于 LCT 只能维护节点的信息，我们把边看作点。为了和原先的点加以区分，我们把这样的节点类型记作 1 。

这样我们就可以通过查询 $x$ 到 $y$ 的链上是否有被打上标记的 1 类型的节点来判断是否可以连结 $(x,y)$ 这条边了。

如果 $(x,y)$ 能连结，那么我们把 $x$ 到 $y$ 的链上打一个值为 $(x,y)$ 边的编号的标记。

如果 $x$ 和 $y$ 没有联通，那么直接 link 就可以了，不需要打标记。

#### 删除边

如果这条边 $(x,y)$ 在沙漠中，但是不在 LCT 上，那么说明它是非树边，把 $x$ 到 $y$ 的链上的标记清空。

如果 $(x,y)$ 在 LCT 上，并且这条边不存在任何一个环内（即标记是空的），直接断开，不会有任何影响。

否则 $(x,y)$ 存在在一个环上。

我们将 $(x,y)$ 的标记所对应的非树边记作 $(u,v)$ 。

由于我们要删除边 $(x,y)$ ，那么 $(u,v)$ 就会成为树边。

所以先将链 $(u,v)$ 的标记清空，再断开 $(x,y)$ ，连结 $(u,v)$ 。

## 关于代码实现

这里给出一种相对好写的一种实现。

我们用 `val[]` 记录当前节点的值。

若为 -1 那么是原先的节点，否则若 >=0 则是由边变成的，同时具有非树边的编号的意义。

`tg[]` 的意义就是标记。

`mx[]` 表示的是当前节点在它的 splay 的子树中 `val[]` 的最大值。

这样当你把 $x$ 到 $y$ 的链分离成一棵 splay 的时候，你就可以直接通过 splay 根的 `mx[]` 值去判断是否有标记和标记对应的边是哪条。

当你下传标记的时候，如果 `val[]` 的值为 -1 ，我们就不需要改变 `val[]` 的值，否则直接把 `val[]` 改成标记的值。

然后...就没有然后了。

[**code**](https://codeforces.com/problemset/submission/1599/139636652)

---

