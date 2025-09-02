# Biathlon Track

## 题目描述

日前，国际奥委会宣布2030年冬季奥运会将在托木斯克举办。托木斯克市政府计划提前建设所有奥运设施，首要任务是建造一条冬季两项滑雪道。

为此，市政府划拨了一块矩形土地，并将其划分为 $ n \times m $ 个相同的方格。每个方格用行号（从1至 $ n $）和列号（从1至 $ m $）来表示。此外，这些方格各有一个高度。比赛中，运动员需要在方格间移动。如果从高处移动到低处，就是下坡；反之，则是上坡；若在两个高度相同的方格间移动，则是平地移动。

滑雪道应围成一个矩形，运动员将沿着这个矩形区域的边界顺时针移动。已知在平地、上坡和下坡上分别需要 $ t_{p} $、$ t_{u} $ 和 $ t_{d} $ 秒。市政府希望选择一条路径，使得运动员经过这条路径的时间尽量贴近 $ t $ 秒。换句话说，经过路径所需的时间 $ t_{s} $ 与 $ t $ 之间差距应尽可能小。

以输入的第一个示例为例，$ n=6 $，$ m=7 $，市政府期望滑雪道的通过时间为 $ t=48 $ 秒，同时，$ t_{p}=3 $，$ t_{u}=6 $ 和 $ t_{d}=2 $。如果选择图中箭头指示的矩形路径，运动员便可沿这个边界顺时针移动恰好用时 $ 48 $ 秒。该路径的左上角起点为第 $ 4 $ 行第 $ 3 $ 列，右下角终点为第 $ 6 $ 行第 $ 7 $ 列。

另外，政府还要求路径围成的矩形每条边必须至少由三个方格构成，并且整体需完全位于分配的土地内部。

你需要根据这块土地的高度信息以及相应的时间参数，编写程序找到最合适的矩形路径。如果存在多个满足要求的矩形，你可以输出其中任意一个。

## 样例 #1

### 输入

```
6 7 48
3 6 2
5 4 8 3 3 7 9
4 1 6 8 7 1 1
1 6 4 6 4 8 6
7 2 6 1 6 9 4
1 9 8 6 3 9 2
4 5 6 8 4 3 7```

### 输出

```
4 3 6 7
```

# 题解

## 作者：_lxy_ (赞：1)

### 题意

略

### 分析

~~真·暴力踩标算~~

记录从上至下、从下至上、从左至右、从右至左花费时间的前缀和，暴力枚举每一个左上角的点和右下角的点的坐标，计算出此时的总时间和 $t$ 的差，如果比目前的最小值小就更新答案。时间复杂度大概为 $O(\frac{n^2m^2}{4})$ ，显然会 TLE ，但是时限 4.5s ，随便卡卡就过了。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=307;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
	register T1 x=0;register bool f=false;char ch=getchar();
	while(ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch>='0') x=(x*10)+(ch^48),ch=getchar();
	x=(f?-x:x);a=x;qread(b...);
}
template<class T>inline T qmax(const T &a,const T &b){return a>b?a:b;}
template<class T>inline T qmin(const T &a,const T &b){return a<b?a:b;}
int n,m,t,tp,tu,td,a[MAXN][MAXN],pre[4][MAXN][MAXN];
int f(int a1,int b1,int a2,int b2)
{
	if(!a2||a2==n+1||!b2||b2==m+1) return 0;
	if(a[a1][b1]==a[a2][b2]) return tp;
	if(a[a1][b1]<a[a2][b2]) return td;
	return tu;
}
void init()
{
	int i,j;
	for(i=1;i<=n;i++) for(j=1;j<=m;j++) pre[0][i][j]=pre[0][i][j-1]+f(i,j,i,j-1); // 从左往右
	for(i=1;i<=n;i++) for(j=m;j>=1;j--) pre[1][i][j]=pre[1][i][j+1]+f(i,j,i,j+1); // 从右往左
	for(j=1;j<=m;j++) for(i=1;i<=n;i++) pre[2][i][j]=pre[2][i-1][j]+f(i,j,i-1,j); // 从上往下
	for(j=1;j<=m;j++) for(i=n;i>=1;i--) pre[3][i][j]=pre[3][i+1][j]+f(i,j,i+1,j); // 从下往上
}
int mn=1e9+7,a1,b1,a2,b2;
signed main()
{
	qread(n,m,t,tp,tu,td);int i,j,k,l;
	for(i=1;i<=n;i++) for(j=1;j<=m;j++) qread(a[i][j]);init();
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			for(k=i+2;k<=n;k++)
			{
				for(l=j+2;l<=m;l++)
				{
					int tmp=pre[0][i][l]-pre[0][i][j]+ // 上面的一行
					        pre[1][k][j]-pre[1][k][l]+ // 下面的一行
							pre[2][k][l]-pre[2][i][l]+ // 右面的一列
							pre[3][i][j]-pre[3][k][j]; // 左面的一列
					tmp=abs(t-tmp);
					if(mn>=tmp)
					{
						mn=tmp;
						a1=i,b1=j,a2=k,b2=l;
					}
				}
			}
		}
	}
	printf("%lld %lld %lld %lld\n",a1,b1,a2,b2);
	return 0;
}
```

---

