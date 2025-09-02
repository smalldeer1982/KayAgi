# Sereja and Straight Lines

## 题目描述

Sereja placed $ n $ points on a plane. Now Sereja wants to place on the plane two straight lines, intersecting at a right angle, so that one of the straight lines intersect the $ Ox $ axis at an angle of $ 45 $ degrees and the maximum distance from the points to the straight lines were minimum.

In this problem we consider the distance between points $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ equal $ |x_{1}-x_{2}|+|y_{1}-y_{2}| $ . The distance between the point and the straight lines is the minimum distance from the point to some point belonging to one of the lines.

Help Sereja, find the maximum distance from the points to the optimally located straight lines.

## 样例 #1

### 输入

```
4
0 0
2 0
0 2
2 2
```

### 输出

```
0.000000000000000
```

## 样例 #2

### 输入

```
4
1 0
0 1
2 1
1 2
```

### 输出

```
1.000000000000000
```

# 题解

## 作者：zyn0309 (赞：3)

[题目传送门](https://codeforces.com/problemset/problem/314/D)

我们充分发扬人类智慧，使用类似模拟退火的方法，初始将所有 $x$ 的平均值和 $y$ 的平均值作为起始点（两条直线的交点），把转移长度 $delta$ 设为 $2^{30}$，每次移动选择 $8$ 个方位和静止不动中答案最优的进行转移，每三次将 $delta$ 折半，直到 $delta$ 小于等于设定的下界。

但是这样还是过不了，再次发扬人类智慧，随机选取 $n$ 个点中任意两个点的中点作为起始点多跑几遍。最后根据数据大小动态调整一下参数就可以过了，如果参数调的好可以做到很高的通过率。

[提交记录](https://codeforces.com/problemset/submission/314/325085991)

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
double eps=1e-8;
const double inf=pow(2,30);
mt19937 rnd(time(0));
int n,posx,posy;
double dx[9]={0,0,0,1,-1,1,1,-1,-1},dy[9]={0,1,-1,0,0,1,-1,1,-1},ans[9],delta,res=2e9,up=-2e9,down=2e9,lef=2e9,rig=-2e9;
struct node{
	double x,y;
}d[N];
inline double getans(double x,double y){
	double k1=1,b1=y-x,k2=-1,b2=y+x,ans=0;
	for(int i=1;i<=n;++i)ans=max(ans,min(fabs(k1*d[i].x-d[i].y+b1),fabs(k2*d[i].x-d[i].y+b2)));
	res=min(res,ans);
	return ans;
}
inline void check(double len){
	for(int i=0;i<9;++i)ans[i]=getans(posx+len*dx[i],posy+len*dy[i]);
	double mi=ans[0];
	for(int i=1;i<9;++i)mi=min(mi,ans[i]);
	for(int i=0;i<9;++i)
	  if(mi==ans[i]){
	  	posx+=len*dx[i];
	  	posy+=len*dy[i];
	  	break;
	  }
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>d[i].x>>d[i].y,posx+=d[i].x/(double)(n),posy+=d[i].y/(double)(n);
	int T=3,limit=3;
	if(n==100000)T=2,eps=1e-3;
	if(n<=10)limit=1000;
	while(T--){
	  delta=inf;
	  int cnt=0;
	  while(delta>eps){
	    check(delta);
	    ++cnt;
	    if(cnt==limit)delta/=2,cnt=0;
	  }
	  if(T==1&&eps==1e-3){
	  	delta=1e4;
	  	eps=0.1;
	    int cnt=0;
	    while(delta>eps){
	      check(delta);
	      ++cnt;
	      if(cnt==limit)delta/=2,cnt=0;
	    }
	    eps=1e-3;
	  }
	  int x=rnd()%n+1,y=rnd()%n+1;
	  posx=(d[x].x+d[y].x)/2,posy=(d[x].y+d[y].y)/2;
	}
	cout<<fixed<<setprecision(6)<<res<<"\n";
	return 0;
}

```

---

## 作者：cmk666 (赞：2)

[题目传送门](/problem/CF314D)

首先这个夹角为 $45\degree$ 看着就很难受，所以先把所有点旋转 $45\degree$，然后就变成一根横线和一根竖线。

看到要求“最大值最小”状物，套路二分答案。

首先把旋转后的点按 $x$ 排序。

check 的时候直接枚举横线的位置，那么没有覆盖到的位置一定是一段前缀 + 后缀，我们要用一个竖线覆盖它们。容易发现我们只关心它们的最值，直接预处理所有前后缀的最值，check 时二分出相应的位置直接用即可。

时间复杂度 $O(n\log n\log ans)$，但是跑的比某些单 $\log$ 快。[submission](//codeforces.com/contest/314/submission/211887154)。

---

## 作者：zesqwq (赞：2)

先将坐标轴旋转 $45\degree$，这样变为找一个平行于 $x$ 的线，找一个平行于 $y$ 轴的线，每一个点到两线距离最小。

考虑二分答案，转化为给定 $n$ 个双区间 $[l_0,r_0], [l_1, r_1]$，求两个点 $x, y$，使得对于每个双区间，要么 $x \in [l_0,r_0]$，要么 $y \in [l_1, r_1]$。

我们发现两类区间都符合要么相同，要么不包含的性质，因此可以对第一类排序后双指针。

用双指针扫第一类区间，求出对于每个 $l$，选 $x$ 能覆盖到的最大的 $r$，然后再判定 $l$ 前的和 $r$ 后面的双区间的第二类区间是否有交即可。

一般实现 $O(n \log n \log V)$，精细实现 $O(n \log V)$。 

[submission](https://codeforc.es/contest/314/submission/211886265)

---

## 作者：q1uple (赞：0)

搞笑题，笔者更搞笑。

首先这个 $45$ 度非常的那啥，所以我们给他旋转一下，问题就变为了切一条横着和竖着的线，问最大值最小。

最大值最小，我们考虑二分。判断解是否合法，记此时答案为 $w$，对于一个区间 $\left[L,R\right]$，如果 $X_R-X_L \le w$，一定是合法的（这里是按 $X$ 排序过的），只需要考虑一段前缀和后缀是否合法，将最大值和最小值相减判断是否小于 $w$，满足就是合法的。

[submission](https://codeforces.com/contest/314/submission/325084479)

---

