# [EC Final 2022] Map

## 题目描述

有一个著名的数学定理，如果你把一张公园的地图完全放在公园里，那么地图上存在一个点与它所代表的点重合。

Mio 非常喜欢这个定理，所以她把她最喜欢的公园的地图完全放在了公园里。公园 $P$ 可以用一个矩形表示。公园的地图只是一个较小（或相等）版本的公园在纸上的打印。地图与原始矩形相似。地图上的每个点都通过相似变换对应于公园中的一个点。

我们可以正式定义地图：地图是一个矩形 $M$（大小较小或相等），加上一个正实数 $r$ 和一个双射函数 $f:M \rightarrow P$，满足以下条件：

- 对于 $M$ 中的每对不同的点 $a, b$，$|f(a)-f(b)|/|a-b|=r$。

这里 $|x-y|$ 表示点 $x$ 和点 $y$ 之间的欧几里德距离。

就像许多游戏一样，Mio 可以使用地图进行传送。准确地说，当 Mio 在地图上的某个点 $x$（包括边界）时，她可以传送到公园中相应的点 $f(x)$。她也可以选择不传送。反之亦然。当她在公园中的点 $y$（包括边界）时，她可以传送到代表她当前位置的地图上的点 $f^{-1}(y)$。她也可以选择不传送。

Mio 最多可以传送 $n$ 次（最少为 $0$ 次）。每次传送需要 $k$ 秒。Mio 还可以以每秒 $1$ 个单位的速度步行。

给定两个点 $s$ 和 $t$，找出 Mio 从 $s$ 到 $t$ 需要的最短时间。

每次传送可以是任意方向（从地图到公园，或从公园到地图）。地图可以倒置放置。由于地图位于公园内部，所以 Mio 可能同时在地图上和在公园中。在这种情况下，她可以选择传送的方向。

例如，在下图中，公园是 $ABCD$，地图是 $A'B'C'D'$。当 Mio 在地图上时，她同时在地图上和在公园中。当她在点 $D'$ 时，她可以从地图传送到公园（到达 $D$），并从公园传送到地图（到达 $D^{\prime\prime}$）。

![](https://cdn.luogu.com.cn/upload/image_hosting/hz6nq09e.png)

## 样例 #1

### 输入

```
2
0 0 0 2 4 2 4 0
0 0 0 1 2 1 2 0
2 1 4 2
1 1
0 0 0 3 6 3 6 0
0 1 1 0 3 2 2 3
0 0 4 2
0 3```

### 输出

```
1.0000000000
1.2272623352```

# 题解

## 作者：Diaоsi (赞：3)

[[EC Final 2022] Map](https://qoj.ac/contest/1197/problem/6302)

看着挺吓人的一道计算几何，其实写起来挺简单（？

首先最优的方案一定是先进行若干次连续的 $f$，然后走一小段，再进行若干次连续的 $f^{-1}$，这样一定是最优的。

为什么呢？假设在走了一段路之后再进行 $f$，那么这段路肯定放在 $f$ 之后走更优，因为地图中的路程一定更短。先 $f^{-1}$ 再走的情况同理。

所以只需要枚举 $f$ 和 $f^{-1}$ 的次数，由于 $n$ 很小，所以可以 $\mathcal{O}\big(n^2\big)$ 枚举。

接下来重点在于如何优雅地实现 $f$，不妨利用矩形的正交性，以矩形的左下角为原点建系：

![3](https://cdn.luogu.com.cn/upload/image_hosting/7j6y3mgn.png)

设当前坐标在 $DAB$ 坐标系下对应的向量为 $\mathbf{u}$，我们只需要把 $\mathbf{u}$ 沿着 $AD$ 和 $AB$ 进行分解，然后把坐标系变换到 $HEF$，再按照两个矩形的相似比进行伸缩变换就可以合成 $\mathbf{v}$。

具体变换可以用点乘实现，可以参考代码。

时间复杂度 $\mathcal{O}(n^2)$。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=110,M=10010,INF=0x3f3f3f3f;
const ld inf=2e18;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
struct node{
	ld x,y;
	node(ld xx=0,ld yy=0){x=xx,y=yy;}
	void in(){scanf("%Lf%Lf",&x,&y);}
}A[5],B[5],S,T;

node operator +(node a,node b){return node(a.x+b.x,a.y+b.y);}
node operator -(node a,node b){return node(a.x-b.x,a.y-b.y);}
ld operator *(node a,node b){return a.x*b.x+a.y*b.y;}
ld operator ^(node a,node b){return a.x*b.y-a.y*b.x;}

node operator *(ld x,node a){return node(x*a.x,x*a.y);}

ld sqr(ld x){return x*x;}
ld dis(node a,node b){return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));}

int _,n,k;
ld ans;

node f(node p){
	node ao=A[1],ai=A[4]-A[1],aj=A[2]-A[1];
	node bo=B[1],bi=B[4]-B[1],bj=B[2]-B[1];
	p=node(((p-ao)*ai)/(ai*ai),((p-ao)*aj)/(aj*aj));
	return bo+p.x*bi+p.y*bj;
}
void solve(){
	ans=inf;
	for(int i=1;i<=4;i++)A[i].in();
	for(int i=1;i<=4;i++)B[i].in();
	S.in();T.in();
	scanf("%d%d",&k,&n);
	node u=S;
	for(int i=0;i<=n;i++,u=f(u)){
		node v=T;
		for(int j=0;i+j<=n;j++,v=f(v))
			ans=std::min(ans,dis(u,v)+k*(i+j));
	}
	printf("%.10Lf\n",ans);
}
int main(){
	scanf("%d",&_);
	while(_--)solve();
	return 0;
}
```

---

