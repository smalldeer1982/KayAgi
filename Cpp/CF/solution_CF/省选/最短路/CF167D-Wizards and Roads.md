# Wizards and Roads

## 题目描述

In some country live wizards. They love to build cities and roads.

The country used to have $ k $ cities, the $ j $ -th city ( $ 1<=j<=k $ ) was located at a point ( $ x_{j} $ , $ y_{j} $ ). It was decided to create another $ n-k $ cities. And the $ i $ -th one ( $ k&lt;i<=n $ ) was created at a point with coordinates ( $ x_{i} $ , $ y_{i} $ ):

- $ x_{i}=(a·x_{i-1}+b) mod (10^{9}+9) $
- $ y_{i}=(c·y_{i-1}+d) mod (10^{9}+9) $

Here $ a $ , $ b $ , $ c $ , $ d $ are primes. Also, $ a≠c,b≠d $ .

After the construction of all $ n $ cities, the wizards have noticed something surprising. It turned out that for every two different cities $ i $ and $ j $ , $ x_{i}≠x_{j} $ and $ y_{i}≠y_{j} $ holds.

The cities are built, it's time to build roads! It was decided to use the most difficult (and, of course, the most powerful) spell for the construction of roads. Using this spell creates a road between the towns of $ u $ , $ v $ ( $ y_{u} $ > $ y_{v} $ ) if and only if for any city $ w $ which lies strictly inside the corner at the point $ u $ , $ v $ (see below), there is a city $ s $ that does not lie in the corner, which is located along the $ x $ -coordinate strictly between $ w $ and $ u $ and simultaneously $ y_{s}&gt;y_{v} $ .

A corner on the points $ p_{2} $ ( $ x_{2} $ , $ y_{2} $ ), $ p_{1} $ ( $ x_{1} $ , $ y_{1} $ ) ( $ y_{1}&lt;y_{2} $ ) is the set of points ( $ x,y $ ), for which at least one of the two conditions is fulfilled:

- $ min(x_{1},x_{2})<=x<=max(x_{1},x_{2}) $ and $ y>=y_{1} $
- $ y_{1}<=y<=y_{2} $ and $ (x-x_{2})·(x_{1}-x_{2})>=0 $

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF167D/e6a75925f8bb3bfa6f6c97c47de7dcc2f9dc2c0a.png) The pictures showing two different corners In order to test the spell, the wizards will apply it to all the cities that lie on the $ x $ -coordinate in the interval $ [L,R] $ . After the construction of roads the national government wants to choose the maximum number of pairs of cities connected by the road, so that no city occurs in two or more pairs. Your task is for each $ m $ offered variants of values $ L $ , $ R $ to calculate the maximum number of such pairs after the construction of the roads. Please note that the cities that do not lie in the interval $ [L,R] $ on the $ x $ -coordinate, do not affect the construction of roads in any way.

## 说明/提示

In the first sample the roads connect the cities in a chain in the order of increasing of $ x $ .

In the second sample the remaining 5 cities will be located at points $ (5, 11); (20, 263098); (65, 292514823); (200, 76958738); (605, 622120197) $ .

## 样例 #1

### 输入

```
6 6
0 0
1 1
2 2
3 3
4 4
5 5
2 3 3 2
4
0 5
1 4
2 3
3 3
```

### 输出

```
3
2
1
0
```

## 样例 #2

### 输入

```
6 1
0 0
3 5 23917 11
4
0 1000000008
0 10
100 150
200 10000
```

### 输出

```
2
1
0
1
```

# 题解

## 作者：xtx1092515503 (赞：2)

[CF167D Wizards and Roads](https://www.luogu.com.cn/problem/CF167D)

首先我们看向奇奇怪怪的生成方式。只有 $10^5$ 却使用级数式的生成方式，我们轻松就能猜到，生成的数据应该 **具有随机数据的一切性质**。

为什么呢？因为它保证 $a,b,c,d$ 都是质数且两两不同，所以其必然以指数上升，进而取模是不可避免的；而又由于两两不同，所以上升的速率不同，进而不会具有相同的循环节，进而具有强的随机性。

进而我们将所有点按 $x$ 坐标排序，并令 $a_i$ 表示第 $i$ 个点的 $y$ 坐标。考虑若 $u<v$ 且 $a_u>a_v$ 的两点间有边。

考虑令 $t$ 为 $t>v$ 且 $a_t>a_v$ 的最小点，也即 $v$ 右侧首个纵坐标大于其的点。假如 $a_u>a_t$，则 $t$ 可以作为判定中的 $w$ 点，且其不存在一个合法的 $s$（因为 $[v,t]$ 中不存在任何纵坐标大于 $a_v$ 的点），进而 $u,v$ 不合法，不存在连边。

相反，若 $a_u<a_t$，则对于 $t$ 右侧所有的 $w$，我们都可以取 $t$ 作为 $s$。进而，$u,v$ 合法。

但是需要注意的是，$[u,v]$ 中也不能存在 $a_t>a_u$ 的点 $t$，不然你仍然找不到这样的 $s$。故可能合法的 $u$ 必然是 $v$ 左侧首个纵坐标大于之的点。

那么我们总结一下，令 $u$ 是左侧首个比它高的点，$t$ 是右侧首个比它高的点，则若 $a_u<a_t$，$u,v$ 间即有边。

同样的讨论亦适用于 $u>v$ 的情形。然后我们惊讶地发现，只需对每个 $v$ 找到其对应的 $u$ 和 $t$，则 $v$ 会往 $u,t$ 二者中较低的那个连边。

考虑这个关系。自己画一个单调栈玩玩的话，会发现其直接就是一棵笛卡尔树。

那么我们的思路到这时已经很清晰了，即求出区间 $[L,R]$ 中的点构成的笛卡尔树的最大匹配。

这听上去是个很复杂的问题。但是我们一开始就声明了我们的点具有随机的性质，进而 $a$ 可以被看作是随机序列。众所周知，随机序列的笛卡尔树的深度期望是 $\log n$ 的。那么直接把它用类似线段树的方法处理，复杂度直接就是 $\log$ 的。

具体而言，我们考虑 $O(n)$ 预处理出笛卡尔树中每棵子树的最大匹配。然后询问就和线段树一样处理：询问区间完整地在某个儿子中就进儿子处理，否则就合并两个儿子传回的结果；假如整棵子树都被包含在区间中，就直接使用预处理的结果即可。复杂度 $n\log n$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+9;
int n,q,K,_a,_b,_c,_d,a[100100],b[100100];
int ch[100100][2],rt,f[100100][2],g[100100][2],tp,stk[100100];
pair<int,int>p[100100];
void dfs(int x){
	for(int i=0,y;i<2;i++)if(y=ch[x][i]){
		dfs(y);
		f[x][1]=max(f[x][1]+max(f[y][0],f[y][1]),f[x][0]+f[y][0]+1);
		f[x][0]=f[x][0]+max(f[y][0],f[y][1]);
	}
}
#define lson ch[x][0]
#define rson ch[x][1]
void dfs(int x,int l,int r,int L,int R){
	g[x][0]=0xc0c0c0c0,g[x][1]=0;
	if(!x||l>R||r<L)return;
	if(R<x){dfs(lson,l,x-1,L,R),g[x][0]=g[lson][0],g[x][1]=g[lson][1];return;}
	if(L>x){dfs(rson,x+1,r,L,R),g[x][0]=g[rson][0],g[x][1]=g[rson][1];return;}
	if(L<=l&&r<=R){g[x][0]=f[x][0],g[x][1]=f[x][1];return;}
	g[x][0]=g[x][1]=0;
	int y;
	y=lson;dfs(y,l,x-1,L,R);
	g[x][1]=max(g[x][1]+max(g[y][0],g[y][1]),g[x][0]+g[y][0]+1);
	g[x][0]=g[x][0]+max(g[y][0],g[y][1]);
	y=rson;dfs(y,x+1,r,L,R);
	g[x][1]=max(g[x][1]+max(g[y][0],g[y][1]),g[x][0]+g[y][0]+1);
	g[x][0]=g[x][0]+max(g[y][0],g[y][1]);
}
int main(){
	scanf("%d%d",&n,&K);
	for(int i=1;i<=K;i++)scanf("%d%d",&p[i].first,&p[i].second);
	scanf("%d%d%d%d",&_a,&_b,&_c,&_d);
	for(int i=K+1;i<=n;i++)
		p[i]=make_pair((1ll*p[i-1].first*_a+_b)%mod,(1ll*p[i-1].second*_c+_d)%mod);
	sort(p+1,p+n+1,[](pair<int,int>x,pair<int,int>y){return x.second<y.second;});
	for(int i=1;i<=n;i++)p[i].second=i;
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++)a[i]=p[i].first,b[i]=p[i].second;
//	for(int i=1;i<=n;i++)printf("%d %d\n",a[i],b[i]);
	for(int i=1;i<=n;i++){
		while(tp&&b[stk[tp]]<b[i])ch[i][0]=stk[tp--];
		if(tp)ch[stk[tp]][1]=i;stk[++tp]=i;
	}
	rt=stk[1],dfs(rt);
	scanf("%d",&q);
	for(int i=1,l,r;i<=q;i++){
		scanf("%d%d",&l,&r);
		l=lower_bound(a+1,a+n+1,l)-a;
		r=upper_bound(a+1,a+n+1,r)-a-1;
		dfs(rt,1,n,l,r);
		printf("%d\n",max(g[rt][0],g[rt][1]));
	}
	return 0;
}
```





---

