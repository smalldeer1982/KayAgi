# [USACO20JAN] Falling Portals P

## 题目描述

有 $N$（$2 \leq N \leq 2 \times 10^5$）个世界，每个世界有一个传送门。初始时，世界 $i$（对于 $1 \leq i \leq N$）位于 $x$ 坐标 $i$，$y$ 坐标 $A_i$（$1 \leq A_i \leq 10^9$）。每个世界里还有一头奶牛。在时刻 $0$，所有的 $y$ 坐标各不相同，然后这些世界开始坠落：世界 $i$ 沿着 $y$ 轴负方向以 $i$ 单位每秒的速度移动。

在任意时刻，如果两个世界在某一时刻 $y$ 坐标相同（可能是非整数时刻），传送门之间就会“同步”，使得其中一个世界的奶牛可以选择瞬间传送到另一个世界。

对于每一个 $i$，在世界 $i$ 的奶牛想要去往世界 $Q_i$（$Q_i \neq i$）。帮助每头奶牛求出如果她以最优方案移动需要多少时间。

每个询问的输出是一个分数 $a/b$，其中 $a$ 和 $b$ 为互质的正整数，或者 $-1$，如果不可能到达。

## 说明/提示

### 样例解释

考虑原先在世界 $2$ 的奶牛的答案。在时刻 $2$ 世界 $1$ 和世界 $2$ 同步，所以奶牛可以前往世界 $1$。在时刻 $\frac{7}{2}$ 世界 $1$ 和世界 $3$ 同步，所以奶牛可以前往世界 $3$。

### 子任务

- 测试点 $2 \sim 3$ 满足 $N \leq 100$。
- 测试点 $4 \sim 5$ 满足 $N \leq 2000$。
- 测试点 $6 \sim 14$ 没有额外限制。

## 样例 #1

### 输入

```
4
3 5 10 2
3 3 2 1```

### 输出

```
7/2
7/2
5/1
-1```

# 题解

## 作者：honglan0301 (赞：15)

## 题目分析

首先能想到一个正确但暴力的贪心，即如果 $A_{Q_i}<A_i$ 则要尽量快地往下走（碰到编号比当前大的世界就要传送），否则要尽量慢地向下走。例如下图中直线表示样例中每个世界纵坐标与时间的关系，从世界 $1$ 出发的牛会按照紫色波浪线每次往编号大的世界走。

![](https://cdn.luogu.com.cn/upload/image_hosting/cmbaclx6.png)

下面考虑如何快速维护这个过程，因为两种情况是对称的，故只考虑前者。

容易发现从世界 $i$ 出发所到达的地方是一个凸包，并且 $A_j<A_i$ 的世界显然没有用，要么没交点要么走得慢，所以是所有 $A_j\geq A_i$ 的世界所构成的凸包。这提示我们只需要按照 $A_i$ 从大到小的顺序插入直线维护凸包，插完点 $i$ 时的凸包就满足该处询问所需。因为截距是单调的，所以只需要单调栈维护即可，此处时间复杂度 $O(n)$。

再考虑询问，不是很懂题解里怎么都要根据凸包建树倍增，既然你都维护出凸包了为什么不直接在上面二分呢？于是只需使用二分，时间复杂度 $O(n\log n)$，可以通过本题，且常数和码量都很小。

## 代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
#define int long long

int n,a[100005],q[100005],bh[100005],stk[100005],top,ansz[100005],ansm[100005];
bool cmp(int x,int y) {return a[x]>a[y];}
bool check(int x,int y,int k) {return (a[x]-a[k])*(y-k)<(a[y]-a[k])*(x-k);}
void ins(int x,bool zt)
{
	while(top&&(zt^(x>stk[top]))||top>1&&check(stk[top-1],stk[top],x)) top--; stk[++top]=x;
	if(zt^(a[q[x]]<a[x]))
	{
		if(zt^(q[x]>stk[1])) return; int l=2,r=top;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if((zt^(q[x]<stk[mid]))&&check(stk[mid],stk[mid-1],q[x])) l=mid+1;
			else r=mid-1;
		}
		ansz[x]=a[stk[r]]-a[q[x]]; ansm[x]=stk[r]-q[x]; int gcdd=__gcd(ansz[x],ansm[x]);
		ansz[x]/=gcdd; ansm[x]/=gcdd;
	}
}

signed main()
{
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(0);
	cin>>n; for(int i=1;i<=n;i++) cin>>a[i],bh[i]=i;
	for(int i=1;i<=n;i++) cin>>q[i]; sort(bh+1,bh+n+1,cmp);
	for(int i=1;i<=n;i++) ins(bh[i],0); top=0; //a[q[i]]<a[i]
	for(int i=n;i>=1;i--) ins(bh[i],1);//a[q[i]]>a[i]
	for(int i=1;i<=n;i++) if(!ansz[i]) cout<<"-1\n"; else cout<<ansz[i]<<"/"<<ansm[i]<<"\n";
}
```


---

## 作者：xtx1092515503 (赞：8)

神题orz……

我们考虑一下，当两个世界“同步”之时，哪种情况我们会选择传送，哪种情况则不。

显然，当这头牛的目的地比它现在的位置要高时，它应该尽量往下落速度慢的世界走，这样方便等待高处的目的地落下来，也因此只要与它同步的世界比它慢就应该传送；当这头牛的目的地比它现在的位置要低时，它应该尽量往下落速度快的世界走，以此来追赶它的目的地，也因此只要与它同步的世界比它快就应该传送。

我们可以证明，只要固定了目的地的高度关系（即高于出发点高度还是低于出发点高度），则**无论时刻如何**，每一个世界上的牛，都有着唯一的传送目标。

有些绕口吧？

我们不妨假设我们的目的地在出发点下方，则我们应该尽量往下落速度大的世界走。我们把目的地在出发点上方的情况称作UP类，而目的地在出发点下方的情况称作DW类。则我们以下只考虑DW类。

我们考虑对于每个世界，画出它的高度$h$与时间$t$的关系。（注意下文中“**斜率**”一词指的是**倾斜程度**，即越陡峭的线斜率越大，换句话说，是正常的斜率**取绝对值**后的结果）

一张典型的图可能会长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/c9ezxqv9.png)

则在一处交点处，就意味着发生了一次“同步”，也就意味着斜率小的直线可以在DW时传送到斜率大的直线上，而斜率大的直线可以在UP时传送到斜率小的直线上。

考虑对于具体的两条直线$f$和$g$。它们长成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/g63wx9rz.png)

因为我们考虑的是DW情况，因此我们只考虑从$f$到$g$的情况。显然，只有当$g$是$f$出发后第一条遇见的大斜率直线时，$f$才会转移到$g$；否则，即之前存在一条大斜率直线，$f$就一定已经在那条直线上转移过去了。

这样看来，对于同一个$f$，这样的$g$应该是唯一的，因为$f$出发后遇到的第一条大斜率直线是唯一的。我们把这条直线$g$记作$dw_f$。这样子，如果我们已经找出了所有的$dw_f$，则对于询问，只需要不断地跳到$dw_f$，直到当前直线跑到了目的地的下面，即可。

但是，我们不能忽略的是，如果$f$不是从头开始的怎么办？换句话说，如果$f$不是出发点，它是从另一条直线，假设是$d$转移来的怎么办？这样子的话，（$dw_f$与$f$的交点）可能在（$f$与$d$的交点）前面，也就是说不能简单地跳到$dw_f$。

正常的情况是这样的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/xi2qbpu7.png)

$d$在$A$处转移到$f$，然后$f$又在$B$处转移到$g$。

然后特殊的情形，就是$f$之前还遇到过一个大斜率直线$h$，因此$h$成为了$dw_f$，但是$h$实际上不能从$A$出发转移到，因为$h$与$f$的交点在$A$左边。因此正确的转移点就是$g$，而非我们之前口胡的那个“不断跳$dw_f$的算法”中的$dw_f$。

即这样的情形：

![](https://cdn.luogu.com.cn/upload/image_hosting/ihg4ifgv.png)

可以看到，$dw_f$是$h$，但是在$A$处时$f$却跳不到$h$（因为$f$与$h$的交点$C$在$A$前面）。

但是，细心的读者可能已经发现了，在这样的情况下，$dw_d$变成了$h$而不是原图的$f$！这就导致了实际上$d$早在$D$点处就已经转到了$h$，而不会像原来我们想象的那样到$A$点再转。

事实上，每个转移的目标，一定是$dw_f$，因为如果出现了之前相交过的情况，此时的直线$h$一定与$d$的交点在$A$前面。也因此，直接暴力跳$dw_f$的算法是正确的。

这只是DW的情况。类似的，UP的情况也可以通过我们预处理一个$up_f$数组出来进行转移。此处不再赘述。

我们可以写出这样的$n^2$做法（$n^2$预处理，$n^2$跳$dw/up$）：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pii pair<int,int>
#define x first
#define y second
#define mp make_pair
int n,h[200100],up[200100],dw[200100],q[200100];
bool operator <=(const pii &u,const pii &v){
	return 1ll*u.x*v.y<=1ll*v.x*u.y;
}
bool operator >=(const pii &u,const pii &v){
	return 1ll*u.x*v.y>=1ll*v.x*u.y;
}
pii operator ~(pii u){
	if(u.x<=0)u.x*=-1,u.y*=-1;
	if(u.y<=0)return mp(0x3f3f3f3f,1);
	int tmp=__gcd(u.x,u.y);
	return mp(u.x/tmp,u.y/tmp);
}
pii cross(int x,int y){
	return ~mp(h[x]-h[y],x-y);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&h[i]);
	for(int i=1;i<=n;i++)scanf("%d",&q[i]);
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++){
		if(h[j]<h[i])continue;
		if(!dw[i])dw[i]=j;
		else if(cross(i,j)<=cross(i,dw[i]))dw[i]=j;
	}
	for(int i=1;i<=n;i++)for(int j=i-1;j;j--){
		if(h[j]>h[i])continue;
		if(!up[i])up[i]=j;
		else if(cross(i,j)<=cross(i,up[i]))up[i]=j;
	}
	for(int i=1;i<=n;i++)printf("%d ",up[i]);puts("");
	for(int i=1;i<=n;i++)printf("%d ",dw[i]);puts("");
	for(int i=1;i<=n;i++){
		int j=i;
		if(h[q[i]]>h[i])while(up[j]&&cross(j,q[i])>=cross(up[j],q[i]))j=up[j];
		else while(dw[j]&&cross(j,q[i])>=cross(dw[j],q[i]))j=dw[j];
		pii p=cross(j,q[i]);
		if(p==mp(0x3f3f3f3f,1))puts("-1");
		else printf("%d/%d\n",p.first,p.second);
	}
	return 0;
}
```
期望得分$35\%$。

我们考虑优化。

如果我们画出每个位置的$dw_f$的话，会发现实际上构成了一个（一堆）凸包：

即这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/macd30i8.png)

凸包可以通过单调队列预处理出来。复杂度$O(n)$。但是初始化时需要进行排序，因此是$O(n\log n)$的。

代码（实际上还是$O(n^2)$的，只不过跳$dw$时的深度可能比较小致使能通过$84\%$）：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pii pair<int,int>
#define x first
#define y second
#define mp make_pair
int n,h[200100],up[200100],dw[200100],q[200100],stk[200100],tp,ord[200100];
bool operator <=(const pii &u,const pii &v){
	return 1ll*u.x*v.y<=1ll*v.x*u.y;
}
bool operator >=(const pii &u,const pii &v){
	return 1ll*u.x*v.y>=1ll*v.x*u.y;
}
pii operator ~(pii u){
	if(u.x<=0)u.x*=-1,u.y*=-1;
	if(u.y<=0)return mp(0x3f3f3f3f,1);
	int tmp=__gcd(u.x,u.y);
	return mp(u.x/tmp,u.y/tmp);
}
pii cross(int x,int y){
	return ~mp(h[x]-h[y],x-y);
}
bool cmp(int x,int y){
	return h[x]<h[y];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&h[i]),ord[i]=i;
	for(int i=1;i<=n;i++)scanf("%d",&q[i]);
	sort(ord+1,ord+n+1,cmp);
	tp=0;
	for(int i=n;i;i--){
		int j=ord[i];
		while((tp&&cross(j,stk[tp])==mp(0x3f3f3f3f,1))||(tp>=2&&cross(j,stk[tp-1])<=cross(j,stk[tp])))tp--;
		dw[j]=stk[tp],stk[++tp]=j;
	}
	tp=0;
	for(int i=1;i<=n;i++){
		int j=ord[i];
		while((tp&&cross(j,stk[tp])==mp(0x3f3f3f3f,1))||(tp>=2&&cross(j,stk[tp-1])<=cross(j,stk[tp])))tp--;
		up[j]=stk[tp],stk[++tp]=j;
	}
//	for(int i=1;i<=n;i++)printf("%d ",up[i]);puts("");
//	for(int i=1;i<=n;i++)printf("%d ",dw[i]);puts("");
	for(int i=1;i<=n;i++){
		int j=i;
		if(h[q[i]]>h[i])while(up[j]&&cross(j,q[i])>=cross(up[j],q[i]))j=up[j];
		else while(dw[j]&&cross(j,q[i])>=cross(dw[j],q[i]))j=dw[j];
		pii p=cross(j,q[i]);
		if(p==mp(0x3f3f3f3f,1))puts("-1");
		else printf("%d/%d\n",p.first,p.second);
	}
	return 0;
}
```

发现所有的$dw/up$一定构成一棵树的结构。因此我们只需要建出这棵树，然后在上面树上倍增就可以在$\log n$时间内找到在目的地直线上方的最后一条直线。

总复杂度$O(n\log n)$。期望得分$100\%$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pii pair<int,int>
#define x first
#define y second
#define mp make_pair
int n,h[200100],up[200100][20],dw[200100][20],q[200100],stk[200100],tp,ord[200100];
bool operator <=(const pii &u,const pii &v){
	return 1ll*u.x*v.y<=1ll*v.x*u.y;
}
bool operator >=(const pii &u,const pii &v){
	return 1ll*u.x*v.y>=1ll*v.x*u.y;
}
pii operator ~(pii u){
	if(u.x<=0)u.x*=-1,u.y*=-1;
	if(u.y<=0)return mp(0x3f3f3f3f,1);
	int tmp=__gcd(u.x,u.y);
	return mp(u.x/tmp,u.y/tmp);
}
pii cross(int x,int y){
	return ~mp(h[x]-h[y],x-y);
}
bool cmp(int x,int y){
	return h[x]<h[y];
}
void print(pii p){
	if(p==mp(0x3f3f3f3f,1))puts("-1");
	else printf("%d/%d\n",p.first,p.second);
}
bool upche(int x,int y){
	if(!up[x][0])return false;
	pii u=cross(up[x][0],x);
	return 1ll*(h[x]-h[y])*u.y<=1ll*u.x*(x-y);
}
bool dwche(int x,int y){
	if(!dw[x][0])return false;
	pii u=cross(dw[x][0],x);
	return 1ll*(h[x]-h[y])*u.y>=1ll*u.x*(x-y);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&h[i]),ord[i]=i;
	for(int i=1;i<=n;i++)scanf("%d",&q[i]);
	sort(ord+1,ord+n+1,cmp);
	tp=0;
	for(int i=n;i;i--){
		int j=ord[i];
		while((tp&&cross(j,stk[tp])==mp(0x3f3f3f3f,1))||(tp>=2&&cross(j,stk[tp-1])<=cross(j,stk[tp])))tp--;
		dw[j][0]=stk[tp],stk[++tp]=j;
	}
	for(int j=1;j<19;j++)for(int i=1;i<=n;i++)dw[i][j]=dw[dw[i][j-1]][j-1];
	tp=0;
	for(int i=1;i<=n;i++){
		int j=ord[i];
		while((tp&&cross(j,stk[tp])==mp(0x3f3f3f3f,1))||(tp>=2&&cross(j,stk[tp-1])<=cross(j,stk[tp])))tp--;
		up[j][0]=stk[tp],stk[++tp]=j;
	}
	for(int j=1;j<19;j++)for(int i=1;i<=n;i++)up[i][j]=up[up[i][j-1]][j-1];
//	for(int i=1;i<=n;i++)printf("%d ",up[i][0]);puts("");
//	for(int i=1;i<=n;i++)printf("%d ",dw[i][0]);puts("");
	for(int i=1;i<=n;i++){
		int j=i;
		if(h[q[i]]>h[i]&&upche(i,q[i])){
			for(int k=18;k>=0;k--)if(up[j][k]&&upche(up[j][k],q[i]))j=up[j][k];
			j=up[j][0];
		}
		if(h[q[i]]<h[i]&&dwche(i,q[i])){
			for(int k=18;k>=0;k--)if(dw[j][k]&&dwche(dw[j][k],q[i]))j=dw[j][k];
			j=dw[j][0];
		}
		print(cross(j,q[i]));
	}
	return 0;
}
```


---

## 作者：Mine_King (赞：4)

提供一种点凸包的做法。

[在我的博客获得更好的阅读体验](https://caijimk.netlify.app/post/202307problemrecord)

---

考虑两个点 $i, j$ 相遇的时间。  
设其为 $k$，则 $a _ i - ik = a _ j - jk \iff a _ i - a _ j = k(i - j) \iff k = \dfrac{a _ i - a _ j}{i - j}$。  
也就是说相遇时间就是两点之间的斜率。（当然必须是正的）

稍微观察一下就会发现如果要从 $i$ 到 $Q _ i$ 至多经过一个中转点。

经过中转点的要求是：$i$ 到中转点的斜率小于中转点到 $Q _ i$ 的斜率。此时答案为中转点到 $Q _ i$ 的斜率。  
只有 $4$ 种情况（蓝色是起点，红色是终点，绿色是中转点）：

![](https://s2.loli.net/2023/07/16/KHWstgCG8uQ6XOj.png)

1 和 3，2 和 4 本质相同，我们只要处理其中两种，然后将图以原点中心对称再做一遍即可。

我们考虑处理 1 和 4。

对于 1：容易发现中转点是在以 $(0, 0)$ 为左下角，$(i, a _ i)$ 为右上角的矩形中的点。  
对于 4：容易发现中转点是在以 $(0, 0)$ 为左下角，$(i, a _ {q _ i})$ 为右上角的矩形中的点。

也就是我们要实现每次询问一个左下角矩形中的点到某个点（在矩形右上方）的斜率最小值。

考虑没有上边界限制怎么做：单调栈维护上凸壳的前半部分（斜率为正的部分） ，然后二分答案。

有上凸壳限制后，我们考虑维护多个上凸壳，然后每次再对应的上凸壳上二分答案。  
对于一个点，如果其可以同时属于多个上凸壳，我们让它属于最上面的那个，这样这些上凸壳就构成了一个森林。  
发现询问对应的上凸壳就是矩形内最上方的点所在的上凸壳。

考虑维护这些上凸壳。如果一个点可以同时属于多个上凸壳，我们选择最上方的上凸壳即可。  
此时我们惊奇地发现这和询问是等价的。

于是我们一边建树一边处理询问即可。

唯一剩下的问题就是树上二分，这个可以使用倍增解决。

```cpp
// Think twice, code once.
#include <set>
#include <cmath>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n, a[200005], q[200005];
vector<int> b[200005];
struct Frac {
	int p, q;

	Frac() = default;
	Frac(int _p, int _q): p(_p), q(_q) {int g = __gcd(p, q); p /= g, q /= g;}
	bool operator<(const Frac &x) const {return (long long)p * x.q < (long long)x.p * q;}
	bool operator==(const Frac &x) const {return p == x.p && q == x.q;}
} ans[200005];
struct Vect {
	int x, y;

	Vect() = default;
	Vect(int _x, int _y): x(_x), y(_y) {}
	bool operator==(const Vect &a) const {return x == a.x && y == a.y;}
};
int fa[200005][20];
set<pair<int, int>> s;

int binarySearch(int h, Vect now) {
	int st = prev(s.lower_bound({h, 0}))->second;
	for (int i = 17; i >= 0; i--) {
		int to = fa[st][i];
		if (fa[to][0] == 0) continue;
		if (Frac(now.y - a[fa[to][0]], now.x - fa[to][0]) < Frac(now.y - a[to], now.x - to)) st = to;
	}
	if (fa[st][0] && Frac(now.y - a[fa[st][0]], now.x - fa[st][0]) < Frac(now.y - a[st], now.x - st))
		st = fa[st][0];
	// if (now == Vect(2, 11)) printf("%d\n", st);
	return st;
}
void solve(int op) {
	for (int i = 1; i <= n; i++) {
		if (i < q[i] && a[i] < a[q[i]] && !s.empty() && s.begin()->first < a[i]) {
			// if (i == 2) puts("?");
			int p = binarySearch(a[i], Vect(q[i], a[q[i]]));
			ans[!op ? i : n - i + 1] = min(ans[!op ? i : n - i + 1], Frac(a[q[i]] - a[p], q[i] - p));
		}

		for (int j : b[i])
			if(!s.empty() && s.begin()->first < a[j]) {
				// if (j == 2) puts("?");
				int p = binarySearch(a[j], Vect(i, a[i]));
				ans[!op ? j : n - j + 1] = min(ans[!op ? j : n - j + 1], Frac(a[i] - a[p], i - p));
			}

		if (s.empty() || s.begin()->first > a[i]) {s.emplace(a[i], i); continue;}
		fa[i][0] = binarySearch(a[i], Vect(i, a[i]));
		for (int j = 1; j <= 17; j++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
		s.emplace(a[i], i);
	}
	return ;
}

int main() {
	// freopen("world.in", "r", stdin);
	// freopen("world.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &q[i]), ans[i] = Frac(1e9, 1);
		if (i < q[i] && a[i] < a[q[i]]) ans[i] = Frac(a[q[i]] - a[i], q[i] - i);
		if (q[i] < i && a[q[i]] < a[i]) ans[i] = Frac(a[i] - a[q[i]], i - q[i]);
	}

	for (int i = 1; i <= n; i++)
		if (q[i] < i && a[i] < a[q[i]])
			b[q[i]].push_back(i);
	solve(0);

	reverse(a + 1, a + n + 1);
	reverse(q + 1, q + n + 1);
	for (int i = 1; i <= n; i++) a[i] = -a[i], q[i] = n - q[i] + 1, vector<int>().swap(b[i]);
	memset(fa, 0, sizeof(fa));
	set<pair<int, int>>().swap(s);

	for (int i = 1; i <= n; i++)
		if (q[i] < i && a[i] < a[q[i]])
			b[q[i]].push_back(i);
	solve(1);

	for (int i = 1; i <= n; i++)
		if (ans[i].p == 1e9) puts("-1");
		else printf("%d/%d\n", ans[i].p, ans[i].q);
	return 0;
}
```

---

## 作者：KarmaticEnding (赞：3)

发现我们机房没有学习过凸包的同学看到题解带“凸包”两个字就直接跳过了，但是我看迄今为止没有不带凸包的做法，所以来发一篇题解，以详细讲讲这道题的凸包是个什么东西。

我们把这个问题放到一个平面直角坐标系图像上去看，其中 $y$ 表示高度，$x$ 表示时间，一个点 $(h,t)$ 就表示在 $t$ 时间某个世界在 $h$ 高度上。

那么，把所有世界看成一堆形如 $y=kx+b$ 的表达式，明显对于第 $i$ 个世界， 由于其下坠速度为 $i$，所以 $k_i=-i$；又因为其在 $x=0$ 时刻其 $y=a_i$，所以 $b_i=A_i$，那么第 $i$ 个世界的表达式为 $y_i=-ix+A_i$。由此，我们可以把样例的图画出来。

![image.png](https://s2.loli.net/2024/11/03/GHwy7MdTFlJInCz.png)

绿线表示第一个世界，蓝线表示第二个世界，红线表示第三个世界，紫线表示第四个世界。

考虑一个贪心，对于每一个世界里的奶牛，如果 $A_{Q_i}<A_i$，那么其就应该尽量从下降慢的世界往下降快的世界走，反之也是一样的。

比如对于一号世界的奶牛，其想要走到三号世界，那么在 $x=2$ 的时候就会面临一次选择：它是走蓝线呢，还是走绿线呢？由于 $A_{Q_1}=A_3>A_1$，所以它应该尽量慢地下降，那么它应该走下降速度慢的绿线而非蓝线。事实证明也是这样，走绿线它会在时刻 $\frac{7}{2}$ 与红线（第三个世界）相交，而走蓝线它要等到时刻 $5$ 才会与红线相交。

现在我们终于可以来讲讲凸包是个什么东西了。一堆函数的区间最小值或者区间最大值在平面直角坐标系上形成的图像，就叫做凸包。我们把上面图的紫线删掉之后，它的区间最小值形成的凸包就是这样的（青色线）：

![image.png](https://s2.loli.net/2024/11/03/pAFuhNPEJxySIDs.png)

（这只是我个人的理解，大佬们觉得有问题就请指正。）

为什么我们要把上图中的紫色线给删掉？其实我们可以观察到，它十分“孤僻”，不跟其他三条线在 $[0,+\infin)$ 上有交点，所以我们要干掉它。这也是第 $4$ 头奶牛无法走到其他世界的原因。

对于凸包，我们一条一条插入直线。我们上面说有两种凸包，所以这两种凸包要分开维护。比如说，对于“下降得快”的凸包，我们每插入一条直线 $i$，就会干掉一些直线  $j$。我们来想想我们干掉了哪些直线。

  - $A_j<A_i$ 的。如果 $j>i$，那么 $i$ 和 $j$ 在 $[0,+\infin)$ 上是没有交点的，没用；如果 $j<i$，那么 $j$ 下降得比 $i$ 慢，没用。

  - 与栈顶第二条直线交点 $x$ 坐标 比 栈顶第一条直线和第二条直线交点 $x$ 坐标 大的。具体原因见下两张图。

反之，对于“下降得慢”的凸包呢？我们要干掉所有 $A_j>A_i$ 的，原因与上同。同样的，我们也要干掉所有 与栈顶第二条直线交点 $x$ 坐标 比 栈顶第一条直线和第二条直线交点 $x$ 坐标 大的。

![image.png](https://s2.loli.net/2024/11/03/OG5AnypzcmfqrMl.png)

插入满足上面第二条限制的直线之后：

![image.png](https://s2.loli.net/2024/11/03/5RYkJLO8VEwH2CZ.png)

为了代码实现方便，不去判什么 $A_j$ 与 $A_i$ 的大小关系，在处理“下降得快”的凸包的时候，直接按照从 $A_i$ 从大到小的顺序插入线。如果第 $i$ 条线被插入的时候第 $Q_i$ 条线还没被插入，输出 $-1$。反之，输出最小时间。

自己写代码的时候写晕了，最后还是看了第一篇题解才勉强看会的。（也是看了好多遍才看懂了什么是凸包，因为以前没有学过）

[代码](https://www.luogu.com.cn/paste/tscv47lc)

---

## 作者：zzw4257 (赞：2)

> 给定一些线段集$y_i=h_i-ix_i$,再给定每个点的目标点$p_i$，求从$(0,y_i)$与目标线相交终点坐标最小$x$坐标(只能向右走，并且可以**多次**通过与另一条线的交点转移到另一条线上)

看一下样例

![geogebra-export](https://cdn.luogu.com.cn/upload/image_hosting/z076lurw.png)

然后后面的讨论我不喜欢$k<0$的直线，因此我们把线统一规定成$y_i=-h_i+ix_i$

然后有一个很显然的结论

- $h_{q_i}<h_i$,则$q_i<i$,所以要尽量上拐加速相遇
- $h_{q_i}>h_i$,则$q_i>i$,所以要尽量下拐加速相遇
- 其余情况均无解

~~其实懒得配图~~其实自己画一下真的会理解更透

考虑预处理这样上拐/下拐的第一个点

设$ufa_i$表示$i$直线(在$y$轴右侧)碰到的横坐标最小的交点对应$k$最大且大于$k_i(即i)$的直线编号

设$dfa_i$表示$i$直线(在$y$轴右侧)碰到的横坐标最小的交点对应$k$最小且小于$k_i(即i)$的直线编号

可以证明这个东西的轨迹是凸包，直接预处理即可

然后我们就尽量往对应的方向跳这个，每次注意是否下一个交点还在目标线上方/下方即可

然后发现这个过程明显可以倍增，即倍增跳到仍在目标线上方/下方，未跨越的最后一个点，再暴力跳一步

```cpp
//预处理
inline void ST(void){
	int i,j,l,r,x;
	for(q[l=r=1]=0,i=1;i<=n;++i){
		x=p[i];
		while((l<r&&Slope(q[r],x)<-eps)||((l+1<r)&&Slope(q[r],x)>Slope(q[r-1],q[r])))--r;
		*df[x]=q[r],q[++r]=x;
	}
	for(q[l=r=1]=0,i=n;i;--i){
		x=p[i];while((l<r&&Slope(q[r],x)<0)||((l+1<r)&&Slope(q[r],x)>Slope(q[r-1],q[r])))--r;
		*uf[x]=q[r],q[++r]=x;
	}
	for(j=1;j<=lg;++j)for(i=1;i<=n;++i){if(uf[i][j-1])uf[i][j]=uf[uf[i][j-1]][j-1];if(df[i][j-1])df[i][j]=df[df[i][j-1]][j-1];}
}
...
//倍增
if(h[Q[i]]<h[i]){
    if(Checku(i,Q[i])){//使劲向上偏上转的 
        for(j=lg;~j;--j)if(Checku(uf[x][j],Q[i]))x=uf[x][j];x=*uf[x];
        if(x<Q[i])puts("-1");else Print(x,Q[i]);
    }else if(i<Q[i])puts("-1");else Print(i,Q[i]);
}
else{
    if(Checkd(i,Q[i])){//使劲向下偏下转的
        for(j=lg;~j;--j)if(Checkd(df[x][j],Q[i]))x=df[x][j];x=*df[x];
        if(x>Q[i])puts("-1");else Print(x,Q[i]);
    }else if(i>Q[i])puts("-1");else Print(i,Q[i]);
}
```


---

## 作者：Anonymely (赞：0)

清新小贪心。

首先拍到平面上变成了很多条直线，有交点便可以换乘。

对于 $a_{q_i} < a_i$，$q_i$ 在 $a_i$ 下部，所以应该换成下标尽可能大的线，这样下降的才能更快。

猜测一手答案肯定在凸包上，证明感性理解。

而对于这种情况，只有满足 $a_j > a_i$ 的直线才会有用，且凸包内的斜率（即下标）应该单减。

于是按照 $a$ 排序后一个个插入即可得到凸包。

查询的话是求凸包与斜线交点，二分即可。

对于 $a_{q_i} > a_i$ 同理。

注意细节。

---

