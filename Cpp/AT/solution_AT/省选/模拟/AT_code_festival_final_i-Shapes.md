# Shapes

## 题目描述

在二维平面上有 $n$ 个图形，每个图形是由所有与某个点 $(x_i, y_i)$ 的曼哈顿距离正好为 $r_i$ 的点组成的。任意两个图形之间没有重叠区域。

接下来有 $m$ 个查询，要求计算从某个坐标点 $(x1, y1)$ 到另一个坐标点 $(x2, y2)$ 的最短路径上必须经过的点数。需要注意的是，查询中提供的坐标保证不在任何一个图形内。

移动过程中，可以经过任何实数坐标点。

## 样例 #1

### 输入

```
5
0 0 1
0 0 5
0 0 9
0 0 13
20 20 1
4
0 0 13 13
0 0 0 7
0 2 0 3
0 0 20 20```

### 输出

```
4
2
0
5```

## 样例 #2

### 输入

```
6
0 0 10
0 5 4
5 0 4
0 -5 4
-5 0 4
8 8 2
4
0 5 0 -5
6 0 10 10
-5 0 0 0
5 0 8 8```

### 输出

```
2
2
1
3```

# 题解

## 作者：happy_dengziyue (赞：1)

### 1 简要题意

在一个平面直角坐标系上，给定 $N$ 个正方形，保证这些正方形互不相切或相交（即不同正方形的边没有交点），并且保证它们的**对角线**平行于坐标轴。

然后进行 $Q$ 次询问，形如：你需要作一条从 $(x_1,y_1)$ 到 $(x_2,y_2)$ 的曲线，求这条曲线**最少**与多少正方形相交。保证 $(x_1,y_1)$ 和 $(x_2,y_2)$ 都**不在**正方形的边上。

$1\le N,Q\le10^5$

### 2 思路

对角线平行于坐标轴的正方形是不好做的。可以首先先将坐标系旋转 $45^\circ$，使得所有正方形的边平行于坐标轴，这可以通过将所有的点 $(x,y)$ 变为 $(x+y,x-y)$ 容易地实现。

考虑暴力计算一次询问。显然如果一个正方形覆盖了 $(x_1,y_1)$ 和 $(x_2,y_2)$ 中的**恰好一个**，曲线就一定要和它相交；反之就一定不需要相交，因为正方形之间一定有空隙可供穿过。

发现这个问题很难维护，但是我们可以考虑容斥。先统计有多少正方形覆盖了 $(x_1,y_1)$，再统计有多少正方形覆盖了 $(x_2,y_2)$。发现如果一个正方形**同时**覆盖了这两个点，就会被统计两次，但实际上它不应该被统计，于是再减去多出来的部分即可。

考虑如何求解上述问题。引入一个包含整个坐标系的无限大的正方形，发现正方形的包含与被包含关系可以表示为一棵树。包含某个点的正方形数量，就是最小的能包含它的正方形在树上的深度；而计算同时包含两个点的正方形数量，只需要再求一次 LCA 的深度即可。

建树和找到包含某个点的最小正方形都是可以用扫描线套线段树实现的。

### 3 代码与记录

```cpp
// LUOGU_RID: 188637376
#include<bits/stdc++.h>
using namespace std;
#define max_n 400020
#define inf 0x3f3f3f3f
int n;
int q;
struct A{int x1,x2,y1,y2;}a[max_n+2];
A que[max_n+2];
int xx[max_n+2],xi=0;
int yy[max_n+2],yi=0;
struct T{
	int l,r;
	set<int>se;
}tr[max_n<<2];
vector<pair<pair<int,int>,int>>opa[max_n+2];
vector<pair<pair<int,int>,int>>opd[max_n+2];
vector<pair<int,pair<int,int>>>opq[max_n+2];
int fa[22][max_n+2];
int de[max_n+2];
int ansp[max_n+2][4];
inline int findx(int w){return lower_bound(xx+1,xx+xi+1,w)-xx;}
inline int findy(int w){return lower_bound(yy+1,yy+yi+1,w)-yy;}
inline void build(int o,int l,int r){
	tr[o].l=l; tr[o].r=r; tr[o].se.clear(); tr[o].se.insert(0);
	if(l>=r)return;
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
}
inline void upd(int o,int ql,int qr,int w){
	int l=tr[o].l,r=tr[o].r;
	if(ql<=l&&r<=qr){
		if(w>=0)tr[o].se.insert(w);
		else tr[o].se.erase(-w);
		return;
	}
	int mid=(l+r)>>1;
	if(ql<=mid)upd(o<<1,ql,qr,w);
	if(qr>mid)upd(o<<1|1,ql,qr,w);
}
inline int query(int o,int x){
	int l=tr[o].l,r=tr[o].r,res=0;
	if(!tr[o].se.empty())res=*--tr[o].se.end();
	if(l>=r)return res;
	int mid=(l+r)>>1;
	if(x<=mid)res=max(res,query(o<<1,x));
	else res=max(res,query(o<<1|1,x));
	return res;
}
inline int asklca(int u,int v){
	if(de[u]<de[v])swap(u,v);
	for(int i=20;i>=0;--i){if(de[fa[i][u]]>=de[v])u=fa[i][u];}
	if(u==v)return u;
	for(int i=20;i>=0;--i){if(fa[i][u]!=fa[i][v]){u=fa[i][u]; v=fa[i][v];}}
	return fa[0][u];
}
int main(){
	#ifdef dzy
	freopen("i_1.in","r",stdin);
	freopen("i_1.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1,x,y,r;i<=n;++i){scanf("%d%d%d",&x,&y,&r); a[i]=(A){x+y-r,x+y+r,x-y-r,x-y+r};}
	a[++n]=(A){-inf,inf,-inf,inf};
	scanf("%d",&q);
	for(int i=1,x1,y1,x2,y2;i<=q;++i){scanf("%d%d%d%d",&x1,&y1,&x2,&y2); que[i]={x1+y1,x2+y2,x1-y1,x2-y2};}
	for(int i=1;i<=n;++i){xx[++xi]=a[i].x1; xx[++xi]=a[i].x2; yy[++yi]=a[i].y1; yy[++yi]=a[i].y2;}
	for(int i=1;i<=q;++i){xx[++xi]=que[i].x1; xx[++xi]=que[i].x2; yy[++yi]=que[i].y1; yy[++yi]=que[i].y2;}
	sort(xx+1,xx+xi+1); xi=unique(xx+1,xx+xi+1)-xx-1;
	sort(yy+1,yy+yi+1); yi=unique(yy+1,yy+yi+1)-yy-1;
	for(int i=1;i<=n;++i){a[i].x1=findx(a[i].x1); a[i].x2=findx(a[i].x2); a[i].y1=findy(a[i].y1); a[i].y2=findy(a[i].y2);}
	for(int i=1;i<=q;++i){que[i].x1=findx(que[i].x1); que[i].x2=findx(que[i].x2); que[i].y1=findy(que[i].y1); que[i].y2=findy(que[i].y2);}
	sort(a+1,a+n+1,[](A a,A b){return 1ll*(a.x2-a.x1)*(a.y2-a.y1)>1ll*(b.x2-b.x1)*(b.y2-b.y1);});
	for(int i=1;i<=n;++i){opa[a[i].x1].push_back({{a[i].y1,a[i].y2},i}); opd[a[i].x2].push_back({{a[i].y1,a[i].y2},i});}
	for(int i=1;i<=q;++i){
		opq[que[i].x1].push_back({que[i].y1,{i,1}}); opq[que[i].x2].push_back({que[i].y2,{i,2}});
	}
	build(1,1,yi);
	for(int i=1;i<=xi;++i){
		for(auto u:opa[i]){fa[0][u.second]=query(1,u.first.first); upd(1,u.first.first,u.first.second,u.second);}
		for(auto u:opq[i])ansp[u.second.first][u.second.second]=query(1,u.first);
		for(auto u:opd[i])upd(1,u.first.first,u.first.second,-u.second);
	}
	for(int i=1;i<=n;++i)de[i]=de[fa[0][i]]+1;
	for(int i=1;i<=20;++i){for(int u=1;u<=n;++u)fa[i][u]=fa[i-1][fa[i-1][u]];}
	for(int i=1;i<=q;++i)printf("%d\n",de[ansp[i][1]]+de[ansp[i][2]]-de[asklca(ansp[i][1],ansp[i][2])]*2);
	return 0;
}
```

[记录传送门](https://atcoder.jp/contests/code-festival-2014-final/submissions/59750236)

By **dengziyue**

---

