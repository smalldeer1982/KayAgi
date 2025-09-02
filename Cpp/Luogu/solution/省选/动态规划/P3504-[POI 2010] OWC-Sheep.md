# [POI 2010] OWC-Sheep

## 题目描述

**译自 POI 2010 Stage 2. Day 2「[Sheep](https://szkopul.edu.pl/problemset/problem/YjtAwdQrSiGcE_RLiEJpGiYE/site/?key=statement)」**

Byteasar 有一个凸多边形牧场，里面有一些羊。  
现在 Byteasar 想要把这个凸多边形划分成若干三角形（划分线不能在牧场中相交，只能在顶点相交），使得每一个三角形里面的羊都有偶数只。  
Byteasar 想知道有多少种方案，你只要输出方案数对 $m$ 取余后的结果即可。

## 样例 #1

### 输入

```
5 4 10
5 5
3 0
-1 -1
-3 4
1 10
1 0
-1 0
1 6
-2 5```

### 输出

```
3```

# 题解

## 作者：asuldb (赞：1)

[题目](https://www.luogu.com.cn/problem/P3504)

不难猜到或者发现的性质，如果连了**一条对角线划分出了奇数个点，那么这条对角线肯定不合法**；因为划分成三角形就不可能有对角线相交，于是划分成奇数的那一边怎么样也不可能划分成全是偶数

于是我们需要对每一条对角线求，有多少条个点在它上面，直接暴力枚举对角线用叉积来判是$O(n^2m)$的，显然过不去的样子；不难发现这个问题具有一定的单调性，对于一个点$i$，求凸包上其他点$j$和$i$所连对角线的划分情况，我们可以顺时针枚举点$j$，不难发现如果一个点在$(i,j-1)$这条边以上，那么也肯定在$(i,j)$以上，于是我们以点$i$为原点跑一边奇角排序，之后开个指针扫一扫就好了

之后求方案数就比较简单了，这是一个凸多边形的弦划分问题，可以大力区间$dp$

设$g_{l,r}$表示区间$[l,r]$的合法划分数

那么就有$g_{l,r}=\sum_{i=l+1}^{r-1}[f_{l,i}=1][f_{i,r}=1]g_{l,i}\times g_{i,r}$

$f_{l,i}=1$表示这条对角线合法

复杂度是$O(nm\log m+n^3)$，代码

```cpp
#include<bits/stdc++.h>
#define vt pt
#define re register
inline int read() {
	char c=getchar();int x=0,r=1;while(c<'0'||c>'9') {if(c=='-') r=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();return x*r;
}
const int maxn=603;
struct pt {int x,y;}a[maxn],b[200005];
int n,m,mod,nw;
int f[maxn][maxn],g[maxn][maxn],vis[maxn][maxn];
inline int qm(int x) {return x>=mod?x-mod:x;}
inline int crs(pt A,pt B) {return A.x*B.y-A.y*B.x;}
inline vt operator-(const pt A,const pt B) {return (vt){A.x-B.x,A.y-B.y};}
inline int cmp(const vt A,const vt B) {return crs(A-a[nw],B-a[nw])<0;}
int dfs(int l,int r) {
	if(vis[l][r]) return g[l][r];
	vis[l][r]=1;
	for(re int i=l+1;i<r;i++)
		if(!(f[l][i]|f[i][r])) g[l][r]=qm(g[l][r]+dfs(l,i)*dfs(i,r)%mod);
	return g[l][r];
}
int main() {
	n=read(),m=read(),mod=read();
	for(re int i=1;i<=n;i++) a[i].x=read(),a[i].y=read();
	for(re int i=1;i<=m;i++) b[i].x=read(),b[i].y=read();
	for(re int i=1;i<=n;i++) {
		nw=i;std::sort(b+1,b+m+1,cmp);int tot=0;
		for(re int j=i+1;j<=n;j++) {
			while(tot<m&&crs(a[j]-a[i],b[tot+1]-a[i])>=0) ++tot;
			f[i][j]=f[j][i]=(tot&1);
			if(tot&&crs(a[j]-a[i],b[tot]-a[i])==0) f[i][j]=f[j][i]=1;
		}
	}
	for(re int i=1;i<n;i++) g[i][i+1]=1,vis[i][i+1]=1;
	printf("%d\n",dfs(1,n));
	return 0;
}

```


---

## 作者：xtx1092515503 (赞：0)

**本题要么用```int```判叉积大小，要么乖乖开```long double```，```double```精度不够**。

卡了我大半个月啊。

首先，如果没有羊的限制，那么DP是很好想的，就是一个多边形三角剖分问题。设 $f[i,j]$ 表示区间 $[i,j]$ 的剖分数量，则有

$$f[i,j]=\begin{cases}1&(j-i\leq 1,\text{状态合法})\\\sum\limits_{k=i+1}^{j-1}f[i,k]f[k,j]&(j-i>l,\text{状态合法})\\0&(\text{状态不合法})\end{cases}$$

下面就考虑一下哪些是合法状态。这个就可以通过枚举 $i$，然后将其它所有顶点和羊以 $i$ 为原点进行极角排序，然后就可以看两个顶点间有多少只羊（即判断状态是否合法了）。

这里我有点后悔使用了```atan2```函数，因为坐标范围很大，如果这样排序就需要很大的精度，最终把```eps```是设成了```1e-20```才过。并且，我在排序的过程中使用了```fmod```函数，本意是把所有点映射到 $[0,\pi)$ 范围中，却没想到```fmod```函数的结果可能为负（这一点和```%```符号一模一样）然后就挂掉了。最后不得不手写了```fmod```。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define double long double
const double pi=acos(-1);
const double eps=1e-20;
int n,m,mod,f[610][610];
struct Vector{
	int x,y;
	Vector(int X=0,int Y=0){x=X,y=Y;}
	friend Vector operator +(const Vector &u,const Vector &v){return Vector(u.x+v.x,u.y+v.y);}
	friend Vector operator -(const Vector &u,const Vector &v){return Vector(u.x-v.x,u.y-v.y);}
	friend Vector operator *(const Vector &u,const int &v){return Vector(u.x*v,u.y*v);}
	friend Vector operator /(const Vector &u,const int &v){return Vector(u.x/v,u.y/v);}
	friend int operator &(const Vector &u,const Vector &v){return u.x*v.y-u.y*v.x;}//cross times
	friend int operator |(const Vector &u,const Vector &v){return u.x*v.x+u.y*v.y;}//point times
	double operator ~()const{return atan2(y,x);}
	void read(){scanf("%d%d",&x,&y);}
	void print(){printf("(%d,%d)",x,y);}
}p[610],q[20100];
double r[20100];
bool bad[610][610];
int dfs(int l,int r){
	if(r-l<=2)return 1;
	if(f[l][r]!=-1)return f[l][r];
	f[l][r]=0;
	for(int i=l+1;i<=r-1;i++)if(!bad[l][i]&&!bad[i][r])(f[l][r]+=1ll*dfs(l,i)*dfs(i,r)%mod)%=mod;
	return f[l][r];
}
double FMOD(double x){
	if(x<0)x+=2*pi;
	if(x>=2*pi)x-=2*pi;
	return x;
}
int main(){
	scanf("%d%d%d",&n,&m,&mod),memset(f,-1,sizeof(f));
	for(int i=1;i<=n;i++)p[n-i].read();
	for(int i=0;i<m;i++)q[i].read();
	for(int i=0;i+1<n;i++){
		double theta=~(p[i+1]-p[i])-eps;
		for(int j=0;j<m;j++)r[j]=FMOD(~(q[j]-p[i])-theta);
		sort(r,r+m);
//		for(int j=0;j<m;j++)printf("%.20Lf ",r[j]);puts("");
		for(int j=i+1,k=0;j<n;j++){
			double now=FMOD(~(p[j]-p[i])-theta);
			while(k<m&&now>r[k])k++;
//			printf("%d %d:%d\n",i,j,k);
//			printf("%.20Lf\n",now);
			if((k&1)||(k<m&&fabs(now-r[k])<eps)||(k&&fabs(now-r[k-1])<eps))bad[i][j]=true;
		}
	}
//	for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)printf("[%d,%d]:%d\n",i,j,bad[i][j]);
	printf("%d\n",dfs(0,n-1));
	return 0;
}
```

---

## 作者：卖淫翁 (赞：0)

```
首先我们需要预处理出多边形的每条对角线是否能把点分成两个偶数部分。这一步我们可以枚举一个起点，然后将k个点按照这个点的极角进行排序，然后扫一遍即可求出以这个点为对角线的一个端点的所有情况

上面一步时间复杂度是O(NKlogK+N^2)的

紧接着我们可以用类似凸多边形划分的区间DP来进行计算

设F[i][j]表示对角线(点i，点j)能不能把平面上的点分成两个偶数部分，g[i][j]表示点i到点j组成的凸多边形的合法划分方案数

则有g[i][j]+=g[i][o]*g[o][j]  (f[i][o]&&f[o][j],i<o<j)

这一步时间复杂度O(N^3)



总体时间复杂度O(N^3+NKlogK)
程序如下：
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define K 20010
#define N 610
using namespace std;
struct node{int x,y;};
int xj(node x,node y){return x.x*y.y-x.y*y.x;}
node operator -(const node &x,const node &y){return (node){x.x-y.x,x.y-y.y};}
node a[K],b[K],S;
bool f[N][N];
int g[N][N];
bool operator <(const node &x,const node &y){return (x.x-S.x)*(y.y-S.y)-(x.y-S.y)*(y.x-S.x)<0;}
int main()
{
	int n,k,m;
	scanf("%d%d%d",&n,&k,&m);
	int i,j,l,o,x,y;
	for(i=1;i<=n;i++)
	scanf("%d%d",&a[i].x,&a[i].y);
	for(i=1;i<=k;i++)
	scanf("%d%d",&b[i].x,&b[i].y);
	for(i=1;i<=n;i++)
	{
		S=a[i];
		sort(b+1,b+k+1);
		int tmp=0;
		for(j=i+1;j<=n;j++)
		{
			while(tmp<k&&xj(b[tmp+1]-S,a[j]-S)<0) tmp++;
			if(tmp%2==1||xj(b[tmp+1]-S,a[j]-S)==0) continue;
			f[i][j]=true;
		}
	}
	for(i=1;i<n;i++)
	g[i][i+1]=1;
	for(l=2;l<n;l++)
	for(i=1;i+l<=n;i++)
	if(f[i][i+l])
	{
		j=i+l;
		for(o=i+1;o<j;o++)
		if(f[i][o]&&f[o][j])
		(g[i][j]+=g[i][o]*g[o][j])%=m;
	}
	printf("%d",g[1][n]);
}
```

---

