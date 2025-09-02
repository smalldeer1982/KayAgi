# Visible Black Areas

## 题目描述

Petya has a polygon consisting of $ n $ vertices. All sides of the Petya's polygon are parallel to the coordinate axes, and each two adjacent sides of the Petya's polygon are perpendicular. It is guaranteed that the polygon is simple, that is, it doesn't have self-intersections and self-touches. All internal area of the polygon (borders are not included) was painted in black color by Petya.

Also, Petya has a rectangular window, defined by its coordinates, through which he looks at the polygon. A rectangular window can not be moved. The sides of the rectangular window are parallel to the coordinate axes.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF962G/4e9eed6795a2bd70a392d64c22cb68435ea81a3d.png)Blue color represents the border of a polygon, red color is the Petya's window. The answer in this case is 2.Determine the number of black connected areas of Petya's polygon, which can be seen through the rectangular window.

## 说明/提示

The example corresponds to the picture above.

## 样例 #1

### 输入

```
5 7 16 3
16
0 0
18 0
18 6
16 6
16 1
10 1
10 4
7 4
7 2
2 2
2 6
12 6
12 12
10 12
10 8
0 8
```

### 输出

```
2```

# 题解

## 作者：Luzhuoyuan (赞：0)

Links:[[to Codeforces]](https://codeforces.com/problemset/problem/962/G) [[to Luogu]](https://www.luogu.com.cn/problem/CF962G)

### 题意简述

有一个矩形窗口和一个 $n$ 顶点的无自交叉、无自接触、每边为水平或竖直的多边形，多边形内部为黑色，其余部分为白色。给定窗口的左上角、右下角坐标以及多边形的每个顶点的坐标（逆时针方向），求忽略窗口外部分后黑色连通块的个数。

$1\le n,$ 所有坐标值 $\le 15000$。

### 思路

参考了[官方题解](https://codeforces.com/blog/entry/58869)的做法。下面认为位于窗口边界上的点位于窗口外。

我们沿着多边形每条边走，如果从窗口的外面走到里面，那么我们记录进入时多边形边与窗口的交点，称这种点为 i 点。如果从窗口的里面走到外面，那么我们称这个交点为 o 点，我们可以把这个出点和上一个入点连边，表示它们是配对的（容易证明它们在窗口内部的同一条折线上）。注意多边形的一条边可能同时产生上面两种点。下图是样例的配对方案。

![](https://cdn.luogu.com.cn/upload/image_hosting/l1jv9t96.png)

之后我们发现能把连通块封起来的除了多边形上的边还有窗口的边缘。显然窗口边缘上是 i 点和 o 点交替的，所以我们令每个 o 点向在它逆时针方向上最近的 i 点连边。最后连出几个连通块就有多少黑色连通块。

如下图，由于给出的多边形边是逆时针的，黑色部分在蓝线的左侧，应添加黄线以使之成为封闭的连通块。

![](https://cdn.luogu.com.cn/upload/image_hosting/p5ucarri.png)

但是还有一种特殊情况：多边形与窗口没有交点。

此时有三种情况：

- 多边形完全在窗口内部，此时其所有点都在窗口内部。答案为 $1$；
- 多边形完全包含窗口 / 与窗口不交：判断这两种情况我们可以从窗口内部引出一条射线，若该射线与多边形有奇数个交点则为前者，否则为后者。前者答案为 $1$，后者为 $0$。

用并查集维护 i/o 点的连通性。复杂度 $O(n\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=15005;
int lx,ly,rx,ry,n,x[N],y[N],f[N<<1],d[N<<1],len,tmp,pn,pos,ans;
struct node{int x,y;}p[N<<1];
inline int read(){
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x;
}
int getf(int x){return x==f[x]?x:(f[x]=getf(f[x]));}
inline void work(int l,int r){
	if(x[l]==x[r]){
		if(x[l]<=lx||x[l]>=rx)return;
		if(y[l]<y[r]){
			if(y[l]<=ly&&y[r]>ly)p[++pn]={x[l],ly};
			if(y[l]<ry&&y[r]>=ry)p[++pn]={x[l],ry},f[getf(pn-1)]=getf(pn);
		}else{
			if(y[l]>=ry&&y[r]<ry)p[++pn]={x[l],ry};
			if(y[l]>ly&&y[r]<=ly)p[++pn]={x[l],ly},f[getf(pn-1)]=getf(pn);
		}
	}else{
		if(y[l]<=ly||y[l]>=ry)return;
		if(x[l]<x[r]){
			if(x[l]<=lx&&x[r]>lx)p[++pn]={lx,y[l]};
			if(x[l]<rx&&x[r]>=rx)p[++pn]={rx,y[l]},f[getf(pn-1)]=getf(pn);
		}else{
			if(x[l]>=rx&&x[r]<rx)p[++pn]={rx,y[l]};
			if(x[l]>lx&&x[r]<=lx)p[++pn]={lx,y[l]},f[getf(pn-1)]=getf(pn);
		}
	}
}//分讨多边形边与窗口相交的情况并处理 i/o 点。
inline int val(int l){
	if(p[l].y==ly)return p[l].x-lx;
	if(p[l].x==rx)return rx-lx+p[l].y-ly;
	if(p[l].y==ry)return rx-lx+ry-ly+rx-p[l].x;
	return ((rx-lx)<<1)+ry-ly+ry-p[l].y;
}//排序用的，给点按逆时针方向赋权
signed main(){
	lx=read(),ry=read(),rx=read(),ly=read(),n=read();
	for(int i=1;i<=n;i++){
		x[i]=read(),y[i]=read();
		if(x[i]<=lx||x[i]>=rx||y[i]<=ly||y[i]>=ry)pos=i;
	}//选出一个在窗口外的点开始，便于操作
	if(!pos){puts("1");return 0;}
	//没有窗口外的点即为特殊情况 1
	for(int i=1;i<=(n<<1);i++)f[i]=d[i]=i;
	for(int i=pos+1;i<=n;i++)work(i-1,i);
	work(n,1);for(int i=2;i<=pos;i++)work(i-1,i);
	if(!pn){//可以理解为射线 x=lx+0.5(y<=ly)
		for(int i=2;i<=n;i++)if(y[i]==y[i-1]&&y[i]<=ly&&min(x[i],x[i-1])<=lx&&max(x[i],x[i-1])>=rx)ans^=1;
		if(y[1]==y[n]&&y[1]<=ly&&min(x[1],x[n])<=lx&&max(x[1],x[n])>=rx)ans^=1;
		printf("%d\n",ans);return 0;
	}//判断剩下两种特殊情况
	tmp=val(2);sort(d+1,d+1+pn,[](int x,int y){return val(x)<val(y);});
	//将 i/o 点按逆时针排序
	for(int i=((d[1]&1)?3:2);i<=pn;i+=2)f[getf(d[i-1])]=getf(d[i]);
	if(d[1]&1)f[getf(d[1])]=getf(d[pn]);
	for(int i=1;i<=pn;i++)if(i==getf(i))ans++;
	printf("%d\n",ans);
	return 0;
}
```
（逃

---

