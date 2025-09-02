# 二人の星座

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2014/tasks/joisc2014_k



# 题解

## 作者：wuzhaoxin (赞：14)

## [AT1227] 二人の星座

[传送门](https://joisc2014.contest.atcoder.jp/tasks/joisc2014_k)

### 题意

给定`n`个点，每个点的颜色为三种中的一种，求出有多少对不相交的三角形（三角形的三个顶点必须满足颜色不同）

保证没有三点共线

$6 \leqslant n \leqslant 2000$

### 题解

只有当存在一条直线能够将两个三角形分在两个平面内时这两个三角形不相交。

考虑三角形的内公切线，两个三角形的内公切线一定可以将两个三角形分割开，并且任意一对三角形都存在两条内公切线。

根据这个我们可以得到一个 $n^3$ 的做法：枚举两个点，分别作为两个三角形的两个顶点，计算出这两个点所在的直线，即两个三角形的内公切线。数出在这条直线上方和下方每种颜色的点的数量，然后直接计算答案即可（如何计算答案可以参考代码不过相信大家都会）。由于一对三角形有两条公切线，所以最终答案根据写法除以`2`或者`4`。

考虑优化数在直线上、下方的点的数量的过程，我们可以确定一个点，然后旋转直线，每次碰到一个点就将这个点从原来的平面中删除、计算答案并加入另一个平面。

我们将所有点按照与被确定的点的直线的斜率排序，直线斜率从负无穷大的开始旋转，遇到点的顺序即为排序后点的顺序。

此时每对三角形在两条公切线的每个端点都被计算了一次，一红计算了`4`次，最终答案要除以`4`

时间复杂度 $O(n^2logn)$

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int gi() {
	register int x; register char c, op = 0;
	while(c = getchar(), c < '0' || c > '9') if(c == '-') op = !op;
	x = c ^ 48;
	while(c = getchar(), c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48);
	return op ? -x : x;
}
int n;
struct node {
	int x, y, c;
	long long a, b;
	bool operator < (const node& t)const {
		if(a * t.b - b * t.a == 0) return x < t.x;
		return (a * t.b - b * t.a > 0) ^ (t.a < 0) ^ (a < 0);
	}
} t[3001], g[3001];
long long ans = 0;
int t1[3], t2[3];
int bl[3001];
void work(int p) {
	t1[0] = t1[1] = t1[2] = t2[0] = t2[1] = t2[2] = 0;
	memcpy(g, t, sizeof(t));
	swap(g[p], g[n]);
	for(int i = 1; i < n; i ++)
		g[i].a = g[i].x - g[n].x, g[i].b = g[i].y - g[n].y;
	sort(g + 1, g + n);
	for(int i = 1; i < n; i ++)
		if(g[i].a >= 0) bl[i] = 0, t1[g[i].c] ++;
		else bl[i] = 1, t2[g[i].c] ++;
	for(int i = 1; i < n; i ++) {
		if(bl[i]) t2[g[i].c] --;
		else t1[g[i].c] --;
		long long tmp = 1;
		for(int j = 0; j <= 2; j ++) if(j != g[n].c) tmp *= t1[j];
		for(int j = 0; j <= 2; j ++) if(j != g[i].c) tmp *= t2[j];
		ans += tmp;
		tmp = 1;
		for(int j = 0; j <= 2; j ++) if(j != g[n].c) tmp *= t2[j];
		for(int j = 0; j <= 2; j ++) if(j != g[i].c) tmp *= t1[j];
		ans += tmp;
		bl[i] ^= 1;
		if(bl[i]) t2[g[i].c] ++;
		else t1[g[i].c] ++;
	}
}
int main() {
	n = gi();
	for(int i = 1; i <= n; i ++)
		t[i].x = gi(), t[i].y = gi(), t[i].c = gi();
	for(int i = 1; i <= n; i ++) work(i);
	printf("%lld\n", ans / 4);
	return 0;
}
```

---

## 作者：Nt_Tsumiki (赞：1)

考虑不交的两个三角形一定能做出两条内公切线，我们不妨从这上面入手。

考虑枚举内公切线的位置，那么我们要统计的实际就是有顶点位于内公切线上，另外两个点在公切线的同侧，但是两个三角形间另外两个点在异侧的三角形对数。

直接暴力做是 $O(n^3)$ 的，考虑优化，这里使用旋转扫描线。

具体的考虑枚举内公切线的一个端点，然后把剩下的点按极角排序，维护一个双指针状物，始终统计一个半平面内的颜色数，总复杂度是 $O(n^2\log n)$。

实现上算极角的时候可以在排序前先算好了，因为 atan2 很慢，算 $O(n^2\log n)$ 次容易被卡常。

[submission](https://atcoder.jp/contests/joisc2014/submissions/62580690)

---

## 作者：PCCP (赞：0)

## 题意

平面内有 $ n\ (n\le3000) $ 个点，有三种颜色，每个点的颜色是三种中的一种。求不相交的三色三角形对数。

## 思路

因为两个三角形不相交，那平民就一定能被某条直线分割成两个区域，两个三角形各在一个区域。类似于圆形，我们可以类比引申出一个概念：三角形的内公切线，不过两个三角形的内公切线是分别过两个三角形的一个顶点的。三角形的内公切线最多有两条，因为题目保证**任意三点不共线**，所以在本题中不相交的两个三角形**有且仅有两条**内公切线。

那我们就可以枚举内公切线，再容斥。我们可以先固定一端，枚举另一个三角形的端点，然后计算两个端点和两个区间内其他点能组成的三角形个数（需要注意的是，两个端点可以和两个区域自由组合）。暴力统计的话时间复杂度是 $ O(n^3) $。

那如何才能快速计数呢？我们的点必须通过什么方式快速排序，才能在 $ \log_2{n} $ 的时间内统计出答案。发现我们枚举第二个端点时，其实相当于从固定点引了一条射线围着固定点旋转，然后再反向延长。于是可以把直角坐标系转化为**极坐标系**，通过极角对其余点排序。由于极角是相对于原点的角度，这样还能通过极角二分出最后一个极角小于反向延长线的点。统计数量则可以先做一遍前缀和预处理。时间复杂度 $ O(n^2\log_2{n}) $。

如何按极角排序，用极角的什么计算值排序呢？可以使用数学库里的 `atan2(y,x)` 函数计算极角反正切值排序，需要注意的是 `atan2(y,x)` 函数计算的极角范围是 $ [ -\pi,\pi ] $，转化成直角坐标系内就是从 x 轴的负半轴逆时针旋转一周回到 x 轴负半轴，函数值顺此递增。另外，`atan2(y,x)` 函数由于增长速度极慢在 LOJ 和 AT 上会被卡精度，在其他大部分 OJ 内均可通过，不建议食用。

这是我在 LOJ 和同学 OJ 上的记录对比：

![](https://cdn.luogu.com.cn/upload/image_hosting/3x7mkuix.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/a2ht6hvp.png)

那有没有其他计算方法？有，可以将三维向量的叉积扩展到二维计算。更简单的，可以直接计算直线斜率经行分类排序。这两种排序方式请读者自行实现。~~（其实是我不想再敲一遍了）~~

考虑到一对三角形会被两条内公切线各统计一遍，一条公切线上的两个端点又会各统计一次，所以最后被答案除以四即可。

## 代码

注意！本代码不可再 AT 与 LOJ 上通过！

免责声明：本题解不为任何个人的代码无法通过负责，请勿因为在 AT 上无法通过而举报本题解！

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<list>
#include<set>
using namespace std;
const int N=3e3+10;
int n,l,r,mid,op1,op2,ot1,ot2,acr;
long long ans,cnt[N][3],syd;
struct point{
    int col;
	double tht,x,y;
}zvd[N],ori;
bool cmp1(point a,point b){
	if(a.tht==b.tht)
		return a.x<b.x;
	return a.tht<b.tht;
}
bool cmp2(point a,point b){
	if(a.x==b.x)
		return a.y<b.y;
	return a.x<b.x;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf%d",&zvd[i].x,&zvd[i].y,&zvd[i].col);
	sort(zvd+1,zvd+n+1,cmp2);
	for(int i=1;i<=n;i++){
		ori=zvd[i];
		for(int j=1;j<=n;j++){
			zvd[j].x-=ori.x,zvd[j].y-=ori.y;
			zvd[j].tht=atan2(zvd[j].y,zvd[j].x);
		}
		sort(zvd+1,zvd+n+1,cmp1);
		zvd[0].tht=-1e9;
		for(int j=0;j<3;j++)
			cnt[0][j]=0;
		for(int j=1;j<=n;j++){
			for(int k=0;k<3;k++)
				cnt[j][k]=cnt[j-1][k];
			if(zvd[j].x||zvd[j].y)
				++cnt[j][zvd[j].col];
		}
		if(ori.col==0)
			op1=1,op2=2;
		else if(ori.col==1)
			op1=0,op2=2;
		else
			op1=0,op2=1;
		for(int j=1;j<=n;j++){
			if(!zvd[j].x&&!zvd[j].y)
				continue;
			syd=atan2(0-zvd[j].y,0-zvd[j].x);
			l=0,r=n,acr=0;
			while(l<=r){
				mid=(l+r)>>1;
				if(zvd[mid].tht<=syd){
					acr=mid;
					l=mid+1;
				}
				else
					r=mid-1;
			}
			if(zvd[j].col==0)
				ot1=1,ot2=2;
			else if(zvd[j].col==1)
				ot1=0,ot2=2;
			else
				ot1=0,ot2=1;
			if(zvd[j].y>0||(zvd[j].y==0&&zvd[j].x<0)){
				ans+=(cnt[j-1][ot1]-cnt[acr][ot1])*(cnt[j-1][ot2]-cnt[acr][ot2])*(cnt[acr][op1]+cnt[n][op1]-cnt[j][op1])*(cnt[acr][op2]+cnt[n][op2]-cnt[j][op2]);
				ans+=(cnt[j-1][op1]-cnt[acr][op1])*(cnt[j-1][op2]-cnt[acr][op2])*(cnt[acr][ot1]+cnt[n][ot1]-cnt[j][ot1])*(cnt[acr][ot2]+cnt[n][ot2]-cnt[j][ot2]);
			}
			else{
				ans+=(cnt[acr][ot1]-cnt[j][ot1])*(cnt[acr][ot2]-cnt[j][ot2])*(cnt[j-1][op1]+cnt[n][op1]-cnt[acr][op1])*(cnt[j-1][op2]+cnt[n][op2]-cnt[acr][op2]);
				ans+=(cnt[acr][op1]-cnt[j][op1])*(cnt[acr][op2]-cnt[j][op2])*(cnt[j-1][ot1]+cnt[n][ot1]-cnt[acr][ot1])*(cnt[j-1][ot2]+cnt[n][ot2]-cnt[acr][ot2]);
			}
		}
		for(int j=1;j<=n;j++)
			zvd[j].x+=ori.x,zvd[j].y+=ori.y;
		sort(zvd+1,zvd+n+1,cmp2);
	}
	ans=ans/4;
	printf("%lld\n",ans);
}
```

---

