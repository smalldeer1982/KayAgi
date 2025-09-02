# Two Arrays

## 题目描述

给定两个整数数组 $a_1,a_2,\dots,a_n$ 和 $b_1,b_2,\dots,b_m$。

Alice 和 Bob 要玩一个游戏。Alice 先手，然后两人轮流操作。

他们在一个 $n \times m$ 的网格上进行游戏（网格有 $n$ 行 $m$ 列）。初始时，棋盘上的车位于第一行第一列。

每次轮到某位玩家时，可以进行以下两种操作之一：

1. 将车移动到当前行或当前列的另一个格子。玩家不能将车移动到已经被访问过 $1000$ 次的格子（即，整个游戏过程中，车在某个格子最多只能停留 $1000$ 次）。注意，起始格子在游戏开始时已被访问过一次。
2. 立即结束游戏，得分为 $a_r+b_c$，其中 $(r, c)$ 是当前车所在的格子（即车在第 $r$ 行第 $c$ 列）。

Bob 希望最大化得分，而 Alice 希望最小化得分。如果两人都采取最优策略，游戏的最终得分是多少？

## 说明/提示

在第一个测试样例中，Alice 将车移动到 $(2, 1)$，Bob 再将车移回 $(1, 1)$。这个过程会重复 $999$ 次，直到最后 Alice 移动后，Bob 无法再将车移回 $(1, 1)$，因为该格子已被访问 $1000$ 次。最终得分为 $a_2+b_1=4$。

在第二个测试样例中，最终得分为 $a_3+b_5$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 1
3 2
2```

### 输出

```
4```

## 样例 #2

### 输入

```
4 5
235499701 451218171 355604420 132973458
365049318 264083156 491406845 62875547 175951751```

### 输出

```
531556171```

# 题解

## 作者：Rainbow_qwq (赞：13)

首先显然地二分答案，$\le x$ 的为 Alice 的胜点，$>x$ 的为 Bob 的胜点，连边会发现是个二分图，于是就是二分图博弈。

二分图博弈是每个点只能经过一次，题目有个 1000 次，但我们猜它就等于一次的情况。

为了分析方便把 $a,b$ 都排成升序，这样 01 矩阵会变成一条折线，左上方都是 0 右下方都是 1 这样子。

现在要判断 $(x,y)$ 是哪方胜，根据二分图博弈结论就是判断去掉这个点最大匹配是否减少。

最大匹配感觉不太好做..转成最大独立集？这样就变成了每行、每列只能选 0 或只能选 1。

手玩一下，瞎调整来感受怎样选点最优。显然是上面的若干行列选 0，下面的若干行列选 1。于是方案就是选一个点 $(x,y)$，选上所有 $(\le x,\le y)$ 的白点和 $(>x,>y)$ 的黑点。

这个 $y$ 根据 $x$ 单调，于是双指针即可。

去掉一个点大概也是这样选点。其实应该把抠掉的那一行/列移到边界上，但是不移的话也能过，大概是因为判断的结果没有区别吧。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
#define int long long
using namespace std;
inline int read()
{
	char c=getchar();int x=0;bool f=0;
	for(;!isdigit(c);c=getchar())f^=!(c^45);
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
	if(f)x=-x;return x;
}

#define fi first
#define se second
#define pb push_back
#define mkp make_pair
typedef pair<int,int>pii;
typedef vector<int>vi;

#define maxn 200005
#define inf 0x3f3f3f3f

int n,m,a[maxn],b[maxn],pa,pb;

int ca[maxn],sa[maxn],posa[maxn],posb[maxn],cb[maxn],sb[maxn],mid;
int F(int x,int y,int o){
	int res=0,p;
	if(ca[x]>=y)res+=x*y;
	else p=posa[y],res+=p*y+sa[x]-sa[p];
	if(cb[y+1]>=n-x)res+=(n-x)*(m-y);
	else p=posb[n-x],res+=(n-x)*(m-p+1)+sb[y+1]-sb[p];
	res-=o*(pa<=x&&pb<=y&&a[pa]+b[pb]<=mid);
	res-=o*(pa>x&&pb>y&&a[pa]+b[pb]>mid);
	return res;
}
bool chk()
{
	int j=m;
	For(i,1,n){
		while(j&&a[i]+b[j]>mid)posa[j]=i-1,--j;
		ca[i]=j,sa[i]=sa[i-1]+ca[i];
	}
	while(j)posa[j]=n,--j;
	
	j=1;
	cb[m+1]=n+1;
	posb[n+1]=m+1;
	Rep(i,m,1){
		while(j<=n&&b[i]+a[j]<=mid)posb[n-j+1]=i+1,++j;
		cb[i]=n-j+1,sb[i]=sb[i+1]+cb[i];
	}
	while(j<=n)posb[n-j+1]=1,++j;
	
	j=1;
	int res1=sb[1],res2=sb[1]-(a[pa]+b[pb]>mid);
	For(i,1,n){
		while(j<m&&F(i,j,0)<=F(i,j+1,0))++j;
		res1=max(res1,F(i,j,0));
	}
	j=1;
	For(i,1,n){
		while(j<m&&F(i,j,1)<=F(i,j+1,1))++j;
		res2=max(res2,F(i,j,1));
	}
	return res1==res2;
}

signed main()
{
	n=read(),m=read();
	For(i,1,n)a[i]=read();
	For(i,1,m)b[i]=read();
	int a1=a[1],b1=b[1];
	sort(a+1,a+n+1),sort(b+1,b+m+1);
	pa=lower_bound(a+1,a+n+1,a1)-a,pb=lower_bound(b+1,b+m+1,b1)-b;
	int l=0,r=a[pa]+b[pb],res=r;
	while(l<=r){
		mid=l+r>>1;
		if(chk())res=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<res;
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：4)

**[E. Two Arrays](https://www.luogu.com.cn/problem/CF1710E)（9.5）**

你在开发一种很新奇的游戏。难道你是想要，yuanshen？

首先，我们知道博弈双方足够聪明，可以直接知道比赛结果 $rus$，如果当前对手给自己的局面优于 $rus$ 那就直接停止，更优矛盾。我们二分结果，这个图的方格分成两个部分，一个部分（小于等于 $rus$ 的）是只能 Alice 踩的，一部分（大于 $rus$ 的）是只能 Bob 踩的，我们发现这玩意是二分图。

我们给同行间，同列间的所有的异色点对连边，我们得到一张二分图。我们发现它们竟然在玩二分图博弈，这让我们想到经典的结论：Alice 赢的充要条件是二分图的最大匹配必须包含起点 $S$。

但是我们发现点数是 $\mathcal O(nm)$ 的，承受不了，我们考虑优化。

首先我们对 $a,b$ 都排序，那么不难发现图的两部分会通过一条经过 $(1,m),(n,1)$ 的直线划分开。

![](https://cdn.luogu.com.cn/upload/image_hosting/ml847jn0.png)

我们要求它的最大匹配。这是一个很新的问题，我们考虑由于 点数 $-$ 最大匹配 $\times 2=$ 最大独立集。我们尝试去求最大独立集。这要求每行每列都只有一边出现，我们给每个行列涂颜色。那么一个方格可以取当且仅当方格的颜色和行列所染颜色都一样。

通过手膜和感性理解发现肯定是对行列的一个前缀染白色，后缀染黑色。

![](https://cdn.luogu.com.cn/upload/image_hosting/s9q2csoe.png)

我们可以通过枚举这个点，我们发现对每行而言，这个可染的数值必然是个凸函数，并且最大的点是单调升的。我们均摊一下就好了。

最终的复杂度是 $\mathcal O(n\log V)$。

代码比较长，但是很好读懂。

[submission](https://codeforces.com/contest/1710/submission/220859093)





---

## 作者：2022zy (赞：0)

发现直接做肯定不好做，观察最大值&最小值。

所以想到二分 $mid$ ，使得 Alice 在 $\le mid$ 时结束， Bob 在 $\gt mid$ 时结束，则双方一定会走到不能再走时结束。

相当于将原图分为两类点，连为二分图，两人在上面不停左右横跳，不能走的人输，即二分图博弈。

*注意以下部分证明时要记住 Alice 和 Bob 都绝顶聪明。*

> **二分图博弈**
> 
> 结论：
> 
>先手获胜的充要条件是，所有二分图最大匹配方案中都包含起点。
> 
> 证明：（详细证明请参考网络）
> 
>显然当后手能走时先手可以走到其匹配的那个点。
> 
>考虑若先手不获胜会怎样，此时所有最大匹配都包含起点吗？
> 
> 判定方法：
> 
>求原图最大匹配，再求去掉起点后的最大匹配。若两者相等则说明至少有一种最大匹配不包含起点，即先手必败。否则先手必胜。

于是转换为判定性问题，即询问 Alice 能否获胜。若能获胜，则说明当前限制对 Alice 是松的，对 Bob 是紧的，即希望继续询问 $[l,mid]$ 的区间。反之亦然。

每个点能走 $1000$ 次和只能走 $1$ 次得到的判定结果是一样的，手玩证明它走出来的样子会是一些循环。

但我们显然不能在原图上做 $nm$ 个点的二分图最大匹配。

发现走的是每一行和每一列，所以与 $a$ 和 $b$ 的顺序无关。于是我们自然地联想到将 $a$ 和 $b$ 从小到大排序，这样可以利用单调性解决很多问题。

*为描述方便，以下成 $\le mid$ 的点为白点， $\gt mid$ 的为黑点，一个匹配是一白一黑。*

但是此时最大匹配仍不好求，我们联想到一个结论：最大独立集 $=$ 总点数 $-$ 最大匹配，证明仍然考虑反证。

于是我们要求现在这个图的最大独立集（以下称选到的点），发现每行 / 每列选到的点要么全白要么全黑，否则会产生匹配，不是独立集。

一条行和一条列会将原图分割为四个小矩形，选到的点一定形如左上角的白点 $+$ 右下角的黑点，可调整法证明。

于是枚举行分界线，对于一行 $i$ ，其有对应最优的一列分界线 $j$ 。

发现每一行对应的 $j$ 是单调的。考虑反证，若后一行的 $j$ 比前一行的 $j$ 往前，那么算出增加的贡献后会发现前一行的 $j$ 并非最优的一列。

而对于当前行，向后拓展 $j$ 直到不能再拓展时是最优的。拓展考虑会增加哪些贡献，算出每一列有几个白点后就能 $\mathcal{O}(1)$ 求。

于是双指针，时间复杂度 $\mathcal{O}(n)$ 。

将上面的全部打完就结束了，总时间 $\mathcal{O}(n\log V)$ 。

```cpp
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=2e5+5;

int n,m,a[N],b[N];
int sx,sy;

int he,j,s1[N],s2[N];
#define ll long long
ll sm,now;
ll find(int x,int y,int mid){
	he=n;now=0;
	for(int i=1;i<=m;i++){
		while(he>0&&a[he]+b[i]>mid)he--;
		s1[i]=he;s2[i]=n-he;
		now+=(n-he);
	}
	if(x>0)now--;
	he=m;
	sm=now;j=0;
	for(int i=1;i<=n;i++){
		while(he>0&&a[i]+b[he]>mid)he--;
		now=now+min(he,j)-(min(m-he,m-j)-(int)(i==x&&y>j));
		while(j<m&&min(s1[j+1],i)>=(min(s2[j+1],n-i)-(int)(j+1==y&&x>i))){
			now=now+min(s1[j+1],i)-(min(s2[j+1],n-i)-(int)(j+1==y&&x>i));
			j++;
		}
		sm=max(sm,now);
	}
	return 1ll*n*m-(x>0)-sm;
}

bool check(int mid){
	return (find(0,0,mid)!=find(sx,sy,mid));
}

int main(){
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&b[i]);
	}
	
	sx=a[1];sy=b[1];
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	for(int i=1;i<=n;i++){
		if(a[i]==sx){
			sx=i;break;
		}
	}
	for(int i=1;i<=m;i++){
		if(b[i]==sy){
			sy=i;break;
		}
	}
	
	int l=0,r=a[sx]+b[sy]-1,mid=0,Ans=a[sx]+b[sy];
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid))Ans=mid,r=mid-1;
		else l=mid+1;
	}
	
	printf("%d\n",Ans);
	
	return 0;
}
```

---

