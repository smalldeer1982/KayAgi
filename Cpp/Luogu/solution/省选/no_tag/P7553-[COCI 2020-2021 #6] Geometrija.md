# [COCI 2020/2021 #6] Geometrija

## 题目描述

平面内有不共线的 $n$ 个点。如果两条线段 $\overline{AB}$  和 $\overline{CD}$ 有异于 $A, B, C, D$ 的公共点，则称他们「相交」。

记 $S$ 为 $n$ 个点两两相连得到的线段的集合。求不与 $S$ 中任意其他线段相交的线段数量。

## 说明/提示

#### 样例 1 解释

符合要求的线段如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/hduk6ziy.png)

#### 样例 2 解释

符合要求的线段如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/21ce6qj8.png)

------------

#### 数据规模与约定

**本题采用捆绑测试**。

| Subtask | 分值 | 数据规模与约定 |
| :----------: | :----------: | :----------: |
| $1$ | $20$ | $3 \le n \le 40$ |
| $2$ | $30$ | $3 \le n \le 200$ |
| $3$ | $60$ | 无附加约定 |

对于 $100\%$ 的数据，$3 \le n \le 10^3$，$-10^9 \le x_i, y_i \le 10^9$。

------------

#### 说明

**本题分值按 COCI 原题设置，满分 $110$**。

**题目译自 [COCI2020-2021](https://hsin.hr/coci/archive/2020_2021/) [CONTEST #6](https://hsin.hr/coci/archive/2020_2021/contest6_tasks.pdf) _T4 Geometrija_**。

## 样例 #1

### 输入

```
4
1 1
-1 1
-1 -1
1 -1```

### 输出

```
4```

## 样例 #2

### 输入

```
4
-1 -1
1 -1
0 1
0 0```

### 输出

```
6```

# 题解

## 作者：b1ngxu (赞：6)

通过观察可以发现：
**一条线段 $AB$ 被另一条线段 $CD$ 穿过等价于四边形 $ADBC$ 是凸的。**

![](https://cdn.luogu.com.cn/upload/image_hosting/nyonri28.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

考虑通过计数来代替判定，定义 $all[A][B]$ 表示以 $AB$ 为对角线的四边形个数，$aot[A][B]$ 表示以 $AB$ 为对角线且 $\angle A\geqslant\pi$ 的凹四边形个数。

当 $aot[A][B]+aot[B][A]=all[A][B]=all[B][A]$ 时表示 $AB$ 是满足条件的边，实际意义为以 $AB$ 为对角线的四边形全为凹四边形。

目前为止问题已经转化成如何求 $aot$ 和 $all$。

$all$ 的计算枚举一个点 $A$，对剩下的点进行极角排序，枚举到一个点 $B$ ，找到所有的 $C$ 使得 $\angle BAC\leqslant\pi$ 的个数为 $k$，那么 $all[A][B]$ 就是 $k*(n-1-k)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/3felozt2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

$aot$ 的计算同样枚举一个点 $A$，对剩下的点进行极角排序，枚举到一个点 $B$ ，找到所有的 $(C,D)$ 使得 $\angle BAC\leqslant\pi$ 且 $\angle CAD\leqslant\pi$ 且 $\angle BAD\leqslant\pi$ 的合法对数即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/uby515gd.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

具体细节可以看代码
```c
#include<bits/stdc++.h>
#define title "title"
#define ll long long
#define ull unsigned ll
#define fix(x) fixed<<setprecision(x)
#define pii pair<int,int>
#define vint vector<int>
#define pb push_back
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define red(i,a,b) for(int i=(a);i>=(b);i--)
#define Help freopen("a","r",stdin)
#define db double
#define ld long db
#define vii vector<pii>
#define fi first
#define se second
#define mp make_pair
using namespace std;
void Freopen()
{
	freopen(title".in","r",stdin);
	freopen(title".out","w",stdout);
}
int read()
{
	int g=0,f=1;
	char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){g=g*10+ch-'0';ch=getchar();}
	return g*f;
}
const int N=1005;
const db pi=acos(-1);
pair<db,int>st[N<<1];
pii p[N];
int n,su[N<<1],all[N][N],aot[N][N];
signed main()
{
	n=read();
	rep(i,1,n)
	{
		int x=read(),y=read();
		p[i]=pii(x,y);
	}
	rep(i,1,n)
	{
		int cnt=0;
		rep(j,1,n)if(i!=j)st[++cnt]=mp(atan2(p[j].se-p[i].se,p[j].fi-p[i].fi),j);
		sort(st+1,st+cnt+1);
		rep(j,1,cnt)st[j+cnt]=st[j],st[j+cnt].fi+=pi*2;
		int k=1;
		rep(j,1,cnt)
		{
			while(st[k+1].fi-st[j].fi<=pi)k++;
			su[j+cnt]=su[j]=k-j;
			all[i][st[j].se]=su[j]*(cnt-1-su[j]);
		}
		rep(j,1,cnt<<1)su[j]+=su[j-1];
		k=1;
		rep(j,1,cnt)
		{
			while(st[k+1].fi-st[j].fi<=pi)k++;
			aot[i][st[j].se]=su[k]-su[j]-(k-j)*(k-j-1)/2;
		}
	}
	
	int Ans=0;
	rep(i,1,n)rep(j,i+1,n)if(aot[i][j]+aot[j][i]==all[i][j])Ans++;
	cout<<Ans;
	return signed();
}

```


---

## 作者：feecle6418 (赞：3)

我不会做题，我只是英文题解的翻译工

------

首先解决如下问题：如何 $O(n\log n)$ 地判断一条线段 $PQ$ 是否合法？

这条线段一定把平面分割成了两个部分，要想与该线段相交，一定是两个部分各取一个点。假设两个部分的点集分别叫做 $\{A\},\{B\}$，我们枚举 $A$ 中的点 $X$，依次看是否存在一个 $B$ 中的点 $Y$，满足 $XY,PQ$ 相交。也就是，假如要判断下图中引出绿线的黑点 $X$ 是否存在 $Y$，就是要判断绿线是否夹到了 $B$ 中的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/0qf9dats.png)

事实上，这等价于，设 $C$ 为 $B$ 中 $Y$ 在 $XP$ 下方的点集（就是上面绿线下方的点集）。若所有 $C$ 中$\angle XPZ$ 最小的 $Z$ 与 $X$ 形成的线段 $XZ$ 都不与 $PQ$ 相交，那么就不存在 $Y\in B$，$XY$ 与 $PQ$ 相交（建议画图理解）。或者说，“在 $XP$ 下方的点集” 就是要在上面的绿线下方，这些点还要尽量满足下面的绿线，就是以 $Q$ 为顶点的极角尽量偏上。假如在上面的绿线下方以 $Q$ 为顶点的极角最偏上的 $Z$ 都不能满足条件，那就没有点能满足条件了。

算法具体流程：

- 将 $A$ 中的点、$B$ 中的点均按照 $P$ 为顶点的极角排序。
- 设 $f(X)$ 为 $\angle PQX$ 的大小，将 $B$ 中的点再次按照 $f(X)$ 排序，记 $X$ 在这个顺序中的排位为 $g(X)$。注意 $P,Q$ 为顶点的极角序不一定是一致的，所以需要排两次（例如上图中红圈中的点）。
- 对每个 $A$ 中的点 $X$，双指针求出 $B$ 中（按照 $P$ 为顶点的极角排序）$AP$ 下面的最上面的点，设为 $B_j$，则 $B_1\sim B_j$ 都在 $AP$ 下方，求出这些点中 $g$ 的最大值在哪个点取到，设为 $Y$，判断 $XY$ 是否都不与 $PQ$ 相交即可。

现在，问题是要判断 $O(n^2)$ 条线段，如何减少候选者数量？

考虑引入 **三角剖分**，就是用顶点在给定点上的三角形完全覆盖这些点构成的凸多边形（定义可以看 [这里](https://oi-wiki.org/geometry/triangulation/)）。

![](https://cdn.luogu.com.cn/upload/image_hosting/8oakjj9n.png)

我们找出任意一个三角剖分（方法：先求凸包，把凸包任意分为三角形，然后对每个三角形随便找个分界点递归求解），则答案线段一定在三角剖分上。而三角剖分是个平面图，至多有 $3n-6$ 条边，我们完全能够分别去检查！因此，我们在 $O(n^2\log n)$ 时间内解决了此问题。

代码在 LOJ 上能在 300ms 内通过，但洛谷上却被卡常，不清楚原因。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const double pi=acos(-1);
struct point{int x,y,id;}a[1005],b[1005],c[1005],d[1005];
ll Dot(point x,point y){return 1ll*x.x*y.x+1ll*x.y*y.y;}
ll Cross(point x,point y){return 1ll*x.x*y.y-1ll*x.y*y.x;}
ll Dis(point x,point y){return 1ll*(x.x-y.x)*(x.x-y.x)+1ll*(x.y-y.y)*(x.y-y.y);}
int sgn(ll x){return x>0?1:(x==0?0:-1);}
point operator +(point x,point y){return {x.x+y.x,x.y+y.y};}
point operator -(point x,point y){return {x.x-y.x,x.y-y.y};}
int st[1005],top,n,C,is[1005][1005],ans;
bool cmp(point x,point y){
	return Cross(x-a[C],y-a[C])>0;
}
void Solve(int x,int y,int z){
	is[x][y]=is[y][x]=is[x][z]=is[z][x]=is[y][z]=is[z][y]=1;
	for(int i=1;i<=n;i++){
		if(i!=x&&i!=y&&i!=z&&Cross(a[x]-a[i],a[y]-a[i])>0&&Cross(a[y]-a[i],a[z]-a[i])>0&&Cross(a[z]-a[i],a[x]-a[i])>0){
			Solve(i,x,y),Solve(i,y,z),Solve(i,z,x);
			return ;
		}
	}
}
bool Check(point x,point y,point a,point b){
	return sgn(Cross(x-a,y-a))!=sgn(Cross(x-b,y-b))&&sgn(Cross(a-x,b-x))!=sgn(Cross(a-y,b-y));
}
bool Check(int x,int y){
	int s1=0,s2=0;
	for(int i=1;i<=n;i++){
		if(i==x||i==y)continue;
		if(Cross(a[i]-a[x],a[y]-a[x])>0)b[++s1]=a[i];
		else c[++s2]=a[i];
	}
	C=x,sort(b+1,b+s1+1,cmp),sort(c+1,c+s2+1,cmp);
	for(int i=1;i<=s2;i++)d[i]=c[i],d[i].id=i;
	C=y,sort(d+1,d+s2+1,cmp);
	for(int i=1;i<=s2;i++)c[d[i].id].id=i;
	for(int i=1,mx=0,j=0,mxp=0;i<=s1;i++){
		while(j<s2&&Cross(b[i]-a[x],c[j+1]-a[x])>0){
			j++,mx=max(mx,c[j].id);
			if(mx==c[j].id)mxp=j;
		}
		if(mxp&&Check(a[x],a[y],b[i],c[mxp]))return 0;
	}
	return 1;
}
int main(){
	cin>>n;
	int mny=1e9,mnx=1e9,mnp=0;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y,a[i].id=i;
		if(a[i].y<mny)mny=a[i].y,mnx=a[i].x,mnp=i;
		else if(a[i].y==mny&&a[i].x<mnx)mnx=a[i].x,mnp=i;
	}
	C=1,swap(a[mnp],a[1]),sort(a+2,a+n+1,cmp);
	st[++top]=1,st[++top]=2;
	for(int i=3;i<=n;i++){
		while(top>1&&Cross(a[st[top]]-a[st[top-1]],a[i]-a[st[top-1]])<=0)top--;
		st[++top]=i;
	}
	st[++top]=st[1];
	for(int i=2;i<top;i++)Solve(st[1],st[i],st[i+1]);
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)if(is[i][j])ans+=Check(i,j);
	cout<<ans;
}
```



---

