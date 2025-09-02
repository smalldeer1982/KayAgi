# Rooks and Rectangles

## 题目描述

波雷卡普有一个n×m大小的棋盘，上面有k个车。他又放了q个矩形在上面。每一个矩形要受到保护。矩形受到保护的意思是对于该矩形内部所有的格子能够被这个矩形内的某个车攻击到或者被占据，和矩形外面的车无关，即矩形外面的车不能攻击到矩形里面。车的位置是固定的。

样例解释：对于最后一个矩形，用红色框框表示的，因为(1,2)不能被某个车攻击到，所以是NO。

## 样例 #1

### 输入

```
4 3 3 3
1 1
3 2
2 3
2 3 2 3
2 1 3 3
1 2 2 3
```

### 输出

```
YES
YES
NO
```

# 题解

## 作者：xxseven (赞：0)

不难证明一个矩形被保护的条件为**每一行**至少有一个车或**每一列**至少有一个车。

由于这两个条件是独立的，我们可以分开来做。

那么问题就被转化为如何判断每一行是否至少有一个车。

离线，按列扫描线，对每一行维护当行最后一次出现车的列号。

当扫描到一个询问矩形的上边缘时，找出当前矩形宽度内**最后一次出现车的时间最早的那一列**，如果出现时间晚于矩形的下边缘，那么说明每一行都至少有一个车。

发现我们要做的事情是单点赋值和区间查询最小，线段树即可。记 $n,m,k,q$ 同阶，则时间复杂度为 $O(n \log n)$。

[AC Record](https://codeforces.com/problemset/submission/524/285243213)

希望这篇题解能够帮到你！

---

## 作者：qianxinyu (赞：0)

# [Rooks and Rectangles](https://www.luogu.com.cn/problem/CF524E)
## 题目大意
有 $k$ 个车，要求回答某个矩形内的所有车的攻击范围能不能遍布整个矩形
## 思路
首先，可以想到，如果每一行都有车，那么这个矩形肯定是符合要求的，每一列都有也同理。

而如果有一行没有车且有一列也没有车的话，肯定存在一个格子没有车可以攻击到。

所以我们只要判断这个矩形是不是每行都有车或是不是每列都有车。

因为这题是二维的，个人感觉分块很难维护，而树套树的话空间也不够，在线的话好像无路可走（如果有dalao想到在线解法可以来教我），所以考虑离线。

我们可以枚举 $x$ 坐标，在上面维护一颗线段树，存下第 $i$ 的行，上一个车的 $x$ 坐标为多少。可以想到，如果在枚举到 $x_2$ 时 $[y_1,y_2]$ 的每一个行里的值都大于 $x_1$ 的话，这个矩形里的每一行就都有车。

而对于每列都有车的情况几乎一模一样。

## 处理
### 1.维护区间最小
显然是一个最简单的最小值线段树。
### 2.枚举 $x$ 坐标
把矩形按 $x_2$ 排序，然后用 `vector` 存车。（想排序的也可以，但是个人认为 `vector` 存车更方便）
## 代码

```cpp
#include"cstdio"
#include"vector"
#include"algorithm"
inline int min(int x,int y){return x<y?x:y;}
inline int max(int x,int y){return x>y?x:y;}
inline int abs(int x){return x>0?x:-x;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
const int N=100010;
#define mid ((l+r)>>1)
struct tree{//一题里如果要用多颗线段树，可以考虑用结构体
	int t[N*2],L[N*2],R[N*2],rt,cnt;
	void update(int &k,int l,int r,int x,int z){
		if(!k)k=++cnt;
		if(l==r){t[k]=z;return;}
		if(x<=mid)update(L[k],l,mid,x,z);
		else update(R[k],mid+1,r,x,z);
		t[k]=min(t[L[k]],t[R[k]]);
	}
	void upd(int x,int z){update(rt,1,N,x,z);}
	int query(int k,int l,int r,int x,int y){
		if(l>y||x>r)return (1<<29);
		if(!k)return 0;
		if(x<=l&&r<=y)return t[k];
		return min(query(L[k],l,mid,x,y),query(R[k],mid+1,r,x,y));
	}
	int que(int x,int y){return query(rt,1,N,x,y);}
}_x,_y;//懒得清空
int n,m,k,q,now;
std::vector<int>vx[N],vy[N];//懒得清空
int x[N*2],y[N*2],ans[N*2];
struct P{int x,y,X,Y,i;}p[N*2];
bool cmp_x(P x,P y){return x.X<y.X;}
bool cmp_y(P x,P y){return x.Y<y.Y;}
int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&q);
	for(int i=1;i<=k;i++)scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=q;i++)scanf("%d%d%d%d",&p[i].x,&p[i].y,&p[i].X,&p[i].Y),p[i].i=i;
	for(int i=1;i<=k;i++)vx[x[i]].push_back(y[i]);
	std::sort(p+1,p+q+1,cmp_x);
	now=1;
	for(int i=1;i<=n;i++){
		for(int y:vx[i])_x.upd(y,i);
		while(p[now].X==i&&now<=q){
			if(_x.que(p[now].y,p[now].Y)>=p[now].x)ans[p[now].i]=1;
			now++;
		}
	}
	for(int i=1;i<=k;i++)vy[y[i]].push_back(x[i]);
	std::sort(p+1,p+q+1,cmp_y);
	now=1;
	for(int i=1;i<=m;i++){
		for(int x:vy[i])_y.upd(x,i);
		while(p[now].Y==i&&now<=q){
			if(_y.que(p[now].x,p[now].X)>=p[now].y)ans[p[now].i]=1;
			now++;
		}
	}
	for(int i=1;i<=q;i++)printf(ans[i]?"YES\n":"NO\n");
	return 0;
}

```
## 有问题可以来问我。

---

## 作者：reyik (赞：0)

线段树

如果某一个矩阵每一行都有车或者每一列都有车 那么这个矩阵就会被覆盖

考虑分别处理这两个问题

以第一个问题为例

我们把每一个矩阵按照$y2$排序把所有点按$y$排序

我们先扫每一列 线段树维护当前每一行中行最大的车在哪一行 然后我们不断把当前行的车插入线段树

查询的时候查询$y2$为当前列的矩阵 如果$x1$行到$x2$行中每一列行最大的车的最小值是$>=y1$的 那么这个矩阵就满足第一个条件

第二个条件以此类推

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
const int N=200005;
struct node {
  int u1,v1,u2,v2,id;
}a[N<<2];
int minn[N<<2];
int k,q,m,n;
bool Ans[N];
vector<int> h[N],l[N];
bool cmp(node a,node b) {
  return a.u2<b.u2;
}
bool cmp1(node a,node b) {
  return a.v2<b.v2;
}
void update(int x) {
  minn[x]=min(minn[x<<1],minn[x<<1|1]);
}
void modify(int x,int l,int r,int y,int z) {
  if(l==r) {
    minn[x]=z;
    return ;
  }
  int mid=(l+r)>>1;
  if(y<=mid) modify(x<<1,l,mid,y,z);
  else modify(x<<1|1,mid+1,r,y,z);
  update(x);
  return ;
}
int query(int x,int l,int r,int L,int R) {
  if(L<=l && r<=R) return minn[x];
  int mid=(l+r)>>1;
  int ret=100000000;
  if(L<=mid) ret=min(ret,query(x<<1,l,mid,L,R));
  if(R>mid) ret=min(ret,query(x<<1|1,mid+1,r,L,R));
  return ret;
}
int main() {
  scanf("%d%d%d%d",&n,&m,&k,&q);
  for (int i=1;i<=k;++i) {
    int x,y;
    scanf("%d%d",&x,&y);
    h[x].push_back(y);
    l[y].push_back(x);
  }
  for (int i=1;i<=q;++i) {
    a[i].id=i;
    scanf("%d%d%d%d",&a[i].u1,&a[i].v1,&a[i].u2,&a[i].v2);
  }
  sort(a+1,a+1+q,cmp);
  int now=1;
  for (int i=1;i<=n;++i) {
    for (int j=0;j<h[i].size();++j) {
      int k=h[i][j];
      modify(1,1,max(n,m),k,i);
    }
    while(now<=q && a[now].u2==i) {
      int ret=query(1,1,max(n,m),a[now].v1,a[now].v2);
      if(ret>=a[now].u1) Ans[a[now].id]=1;
      ++now;
    }
  }
  memset(minn,0,sizeof(minn));
  sort(a+1,a+1+q,cmp1);
  now=1;
  for (int i=1;i<=m;++i) {
    for (int j=0;j<l[i].size();++j) {
      int k=l[i][j];
      modify(1,1,max(n,m),k,i);
    }
    while(now<=q && a[now].v2==i) {
      int ret=query(1,1,max(n,m),a[now].u1,a[now].u2);
      if(ret>=a[now].v1) Ans[a[now].id]=1;
      ++now;
    }
  }
  for (int i=1;i<=q;++i) {
    if(Ans[i]) puts("YES");
    else puts("NO");
  }
  return 0;
}


```

---

## 作者：intel_core (赞：0)

如果一个矩形都被内部的车覆盖了，要么矩形内所有列上都有车，要么所有行上都有车。

> 反证：假设这两个都不成立，设 $x$ 行无车，$y$ 行无车，那么 $(x,y)$ 没有被覆盖。

所以只需要把行和列分开考虑，如果满足任意一个条件就是 `YES`，否则就是 `NO`。

这种平面上矩形的问题一般用扫描线来做。

问题来了，怎么判断矩形内所有行上都有车？

我们可以对 $y$ 轴开一棵线段树，扫描线扫过 $x=k$ 这条线的时候，把上面所有的车 $(k,y)$ 对应的 $y$ 里的值更新为 $k$。

这样在查询的时候只需要区间最小值 $\le x_1$ 就可以。

复杂度 $O(n \log n)$，注意两遍之间要清空。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=2e5+10;
int n,m,k,q,ans[NR];
vector<int>col[NR],row[NR];
#define pb push_back
struct mat{
	int x1,y1,x2,y2,id;
}t[NR];
bool cmp1(mat r1,mat r2){return r1.x2<r2.x2;}
bool cmp2(mat r1,mat r2){return r1.y2<r2.y2;}

int minn[NR<<2];
#define lson (id<<1)
#define rson (id<<1|1)
#define mid ((l+r)>>1)
void update(int id){
	minn[id]=min(minn[lson],minn[rson]);
}
void init(){
	memset(minn,0,sizeof(minn));
} 
void change(int id,int l,int r,int pos,int k){
	if(l==r){
		minn[id]=max(minn[id],k);
		return;
	}
	if(pos<=mid)change(lson,l,mid,pos,k);
	else change(rson,mid+1,r,pos,k);
	update(id);
}
int query(int id,int l,int r,int L,int R){
	if(r<L||R<l)return 1e9;
	if(L<=l&&r<=R)return minn[id];
	return min(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
}

int main(){
	cin>>n>>m>>k>>q;
	for(int i=1,x,y;i<=k;i++)
		scanf("%d%d",&x,&y),col[x].pb(y),row[y].pb(x);
	for(int i=1;i<=q;i++)
		scanf("%d%d%d%d",&t[i].x1,&t[i].y1,&t[i].x2,&t[i].y2),t[i].id=i;
	sort(t+1,t+1+q,cmp1);
	for(int i=1;i<=q;i++){
		for(int j=t[i-1].x2+1;j<=t[i].x2;j++)
			for(int x:col[j])change(1,1,m,x,j);
		ans[t[i].id]|=(query(1,1,m,t[i].y1,t[i].y2)>=t[i].x1);
	}
	sort(t+1,t+1+q,cmp2);init();
	for(int i=1;i<=q;i++){
		for(int j=t[i-1].y2+1;j<=t[i].y2;j++)
			for(int x:row[j])change(1,1,n,x,j);
		ans[t[i].id]|=(query(1,1,n,t[i].x1,t[i].x2)>=t[i].y1);
	}
	for(int i=1;i<=q;i++)puts(ans[i]?"YES":"NO");
	return 0;
}
```

---

