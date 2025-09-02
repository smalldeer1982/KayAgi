# [PA 2019 Final] 领地 / Terytoria

## 题目背景

译自 PA 2019 Final。$\texttt{3s,512M}$。

本题数据为自造。

std：zimpha，validator：Starrykiller，generator：KanameMadoka。

## 题目描述

一个长为 $X$ 宽为 $Y$ 的矩形被分为 $X\times Y$ 个方格。我们记第 $i$ 行第 $j$ 列的方格为 $(i,j)$。

有 $n$ 种动物。第 $i$ 种动物**不喜欢**待在以 $(x_i,y_i)$ 和 $(x_i',y_i')$ 为对角顶点确定的矩形内。我们保证这个矩形**严格包含于** $X\times Y$ 的矩形。

第 $i$ 种动物有 $c_i$ 只。那么，一共有 $S=c_1+c_2+\cdots+c_n$ 只动物。

现在要将每只动物放在一个方格里面。**一个方格里面可以放多只动物，但是一只动物不能待在它不喜欢的区域**。

记 $(i,j)$ 内有 $p_{i,j}$ 只动物，那么这种分配方式的得分为 $\displaystyle \sum_{1\le i\le X}\sum_{1\le j\le Y} {p_{i,j}\choose 2}$。这里，$\displaystyle {a\choose 2}=\frac{a(a-1)}{2}$。

找到合法的分配方式中得分最大的那个分配方式。只需要输出最大的得分。




## 说明/提示

- $1\le n\le 10^5$；
- $1\le X,Y\le 10^3$；
- $\textcolor{red}{1\le x_i\le x'_i\le X},\textcolor{red}{1\le y_i\le y'_i\le Y}$；
- 以下条件中，**至少有一个**成立：${x_i\neq 1},{y_i\neq 1},{x'_i\neq X},{y'_i\neq Y}$；
- $1\le c_i\le 10^3$。

样例解释：

对于第一个样例，只能把第一种动物全部放在 $(1,2)$，第二种动物全部放在 $(1,1)$，得分为 $\binom{4}{2}+\binom{3}{2}=9$。

对于第二个样例，最优方案为把三种动物都全部放在 $(4,1)$，得分为 $\binom{3}{2}=3$。容易证明没有比其更优的答案。



## 样例 #1

### 输入

```
2 1 2
1 1 1 1 3
1 2 1 2 4```

### 输出

```
9```

## 样例 #2

### 输入

```
3 7 3
1 1 3 3 1
5 1 7 3 1
3 2 5 3 1```

### 输出

```
3```

# 题解

## 作者：Reunite (赞：3)

简单题。

注意到一个 ban 掉的矩形至少会留下一条边界上的两个端点，所以所有的点都至少可以被集中在矩形的两个对角顶点上，先放完仅能放在一个顶点上的，对于能在两个顶点自由选择的点，显然全放在更多的那边更优。

但这样不一定最优，可能存在中间的一个点能够集中很多点。我们直接枚举一个中间点，把所有能放的点全部集中过来，剩下的点继续考虑选择放在对角顶点即可，直接模拟用差分维护一下即可做到 $O(n+XY)$。

正确性的话，稍微画一下能发现最优情况不会选择 $\ge 4$ 个点，且非顶点不会选择超过 $1$ 个，因为非顶点之间也肯定是尽量把一个弄的很大，剩下的那个一定可以平移到顶点上，或者与一个顶点重新分成一对对角顶点。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

int n,X,Y,all;
int A[16];
int a[16][1005][1005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

int main(){
	in(n),in(X),in(Y);
	while(n--){
		int x,y,xx,yy,c,s=0;
		in(x),in(y),in(xx),in(yy),in(c);
		all+=c;
		if(x==1&&y==1) s|=1;
		if(x==1&&yy==Y) s|=2;
		if(xx==X&&y==1) s|=4;
		if(xx==X&&yy==Y) s|=8;
		A[s]+=c;
		a[s][x][y]+=c;
		a[s][xx+1][y]-=c;
		a[s][x][yy+1]-=c;
		a[s][xx+1][yy+1]+=c;
	}
	for(int s=0;s<16;s++)
		for(int i=1;i<=X;i++)
			for(int j=1;j<=Y;j++)
				a[s][i][j]+=a[s][i-1][j]+a[s][i][j-1]-a[s][i-1][j-1];
	ll ans=0;
	for(int x:{0,1,2,3}){
		for(int y:{0,1,2,3}){
			if(x==y) continue;
			ll xx=0,yy=0,cc=0;
			for(int s=0;s<16;s++){
				if(!(s>>x&1)) xx+=A[s];
				if(!(s>>y&1)) yy+=A[s];
				if(!(s>>x&1)&&!(s>>y&1)) cc+=A[s];
			}
			if(xx<yy) xx-=cc;
			else yy-=cc;
			ans=max(ans,xx*(xx-1)/2+yy*(yy-1)/2);
		}
	}
	for(int i=1;i<=X;i++){
		for(int j=1;j<=Y;j++){
            if(i==1&&j==1) continue;
			if(i==1&&j==Y) continue;
			if(i==X&&j==1) continue;
			if(i==X&&j==Y) continue;
			ll s=all;
			for(int x=0;x<16;x++) s-=a[x][i][j];
			s=s*(s-1)/2;
			ans=max(ans,s);
			int b[4]={0},c[4][4]={0};
			for(int x=0;x<16;x++){
				for(int xx:{0,1,2,3}){
					if((x>>xx)&1) continue;
					b[xx]+=a[x][i][j];
					for(int yy:{0,1,2,3})
						if(!((x>>yy)&1)) c[xx][yy]+=a[x][i][j];
				}
			}
			for(int x:{0,1,2,3}){
				ans=max(ans,s+1ll*b[x]*(b[x]-1)/2);
				for(int y:{0,1,2,3}){
					if(y==x) continue;
					ll xx=b[x],yy=b[y];
					if(xx>yy) yy-=c[x][y];
					else xx-=c[x][y];
					ans=max(ans,s+xx*(xx-1)/2+yy*(yy-1)/2);
				}
			}
		}
	}
	printf("%lld\n",ans);

	return 0;
}
```

---

## 作者：Purslane (赞：2)

# Solution

注意到 $f(x) = \dbinom{x}{2}$ 是凸的，所以我们有结论：

必定存在一个点 $(x_0,y_0)$，使得所有能住在 $(x_0,y_0)$ 的动物都住在了 $(x_0,y_0)$。（反证法容易证明。）

如果你只观察到了这个，那你能得到一个 $O(V^6)$ 的 DP：每次还没有定居的动物一定形如——其不喜欢的地方包含了当前的一个矩形，所以直接暴力维护这个矩形的四个边界以及目前获得的代价。 ~~太好了，是多项式复杂度暴力，我们有救了。~~

假设我们已经放了一个点，剩下的所有动物不喜欢区域已经包含了这个点。所以可以证明——如果一个动物**不喜欢区域的并不是全集，那么一定不包含某一个角。**（反证法容易证明。）

所以下一次操作一定是将一个定居点放在某一个角。

而剩下的所有的动物一定都可以聚集到另一个角。

所以这道题和 DP 没有关系，因为决策太固定了，可以直接枚举。使用二维前缀和预处理一些东西，复杂度 $O(V^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10,MAXM=1e3+10;
int n,x,y,ans,xl[MAXN],xr[MAXN],yl[MAXN],yr[MAXN],c[MAXN],tot;
int pre1[MAXM][MAXM],pre2[MAXM][MAXM];
int f(int x) {return x*(x-1)/2;}
void solve(int cx,int cy,int ncx,int ncy) {
	memset(pre1,0,sizeof(pre1)),memset(pre2,0,sizeof(pre2));
	int ot=0;
	ffor(i,1,n) {
		pre1[xl[i]][yl[i]]+=c[i];
		pre1[xr[i]+1][yl[i]]-=c[i];
		pre1[xl[i]][yr[i]+1]-=c[i];
		pre1[xr[i]+1][yr[i]+1]+=c[i];	
		if(xl[i]<=cx&&cx<=xr[i]&&yl[i]<=cy&&cy<=yr[i]) {
			ot+=c[i];
			pre2[xl[i]][yl[i]]+=c[i];
			pre2[xr[i]+1][yl[i]]-=c[i];
			pre2[xl[i]][yr[i]+1]-=c[i];
			pre2[xr[i]+1][yr[i]+1]+=c[i];	
		}
	}
	ffor(i,1,x) ffor(j,1,y) pre1[i][j]=pre1[i-1][j]+pre1[i][j-1]+pre1[i][j]-pre1[i-1][j-1];
	ffor(i,1,x) ffor(j,1,y) pre2[i][j]=pre2[i-1][j]+pre2[i][j-1]+pre2[i][j]-pre2[i-1][j-1];
	ffor(i,1,x) ffor(j,1,y) ans=max(ans,f(tot-pre1[i][j])+f(pre2[i][j])+f(pre1[i][j]-pre2[i][j]));
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>x>>y;
	ffor(i,1,n) cin>>xl[i]>>yl[i]>>xr[i]>>yr[i]>>c[i],tot+=c[i];
	solve(1,1,x,y),solve(x,1,1,y),solve(x,y,1,1),solve(1,y,x,1);
	cout<<ans;
	return 0;
}
```

---

