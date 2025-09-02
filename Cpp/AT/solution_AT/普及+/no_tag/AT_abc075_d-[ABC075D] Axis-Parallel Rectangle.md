# [ABC075D] Axis-Parallel Rectangle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc075/tasks/abc075_d

2次元座標上に $ N $ 個の点があります。   
 $ i(1≦i≦N) $ 番目の点の座標は $ (x_i,y_i) $ です。   
 長方形の内部に $ N $ 点のうち $ K $ 個以上の点を含みつつ、それぞれの辺がX軸かY軸に平行な長方形を考えます。  
 このとき、長方形の辺上の点は長方形の内部に含みます。   
 それらの長方形の中で、最小の面積となるような長方形の面積を求めてください。

## 说明/提示

### 制約

- $ 2≦K≦N≦50 $
- $ -10^9≦x_i,y_i≦10^9\ (1≦i≦N) $
- $ x_i≠x_j\ (1≦i\ <\ j≦N) $
- $ y_i≠y_j\ (1≦i\ <\ j≦N) $
- 入力値はすべて整数である。(21:50 追記)

### Sample Explanation 1

条件を満たす最小面積となる長方形の $ 1 $ つは $ (1,1),(8,1),(1,4),(8,4) $ の $ 4 $ つの頂点で構成されます。 その面積は $ (8-1)\ ×\ (4-1)\ =\ 21 $ であるため、$ 21 $ と出力します。

### Sample Explanation 3

オーバーフローに注意してください。

## 样例 #1

### 输入

```
4 4
1 4
3 3
6 2
8 1```

### 输出

```
21```

## 样例 #2

### 输入

```
4 2
0 0
1 1
2 2
3 3```

### 输出

```
1```

## 样例 #3

### 输入

```
4 3
-1000000000 -1000000000
1000000000 1000000000
-999999999 999999999
999999999 -999999999```

### 输出

```
3999999996000000001```

# 题解

## 作者：0xyz (赞：3)

### 一、做法

以下令上边为平行于 $x$ 轴的纵坐标较大的那一条边，下边为平行于 $x$ 轴的纵坐标较小的那一条边，左边为平行于 $y$ 轴的横坐标较小的那一条边，右边为平行于 $y$ 轴的横坐标较大的那一条边。

首先有一个很显然的性质：矩形的 $4$ 条边上都必须有点，因为如果一条边上没有点，这一条边可以适当向内收缩使得矩形边上及内部点数不变并且面积缩小。所以矩形的面积要最小，它的每一条边都至多只有 $n$ 种选法。

然后就是这一题的做法。有一个很显然的暴力（官方题解给的就是这个）：枚举矩形的 $4$ 条边分别由哪个点决定，然后判断被它包含的点的数量是否大于等于 $K$。时间复杂度 $O(n^5)$，可以通过此题。[官方题解](https://img.atcoder.jp/abc075/editorial.pdf)写了，代码就不给了。

再优化，可以在离散化所有点后使用二维前缀和，在 $O(1)$ 的时间内统计一个指定矩形内部有多少点，然后 $O(n^4)$ 通过这道题。其他题解写了，代码就不给了。

再优化，我们可以只枚举 $3$ 条边，比如说上、左、右 $3$ 条边。此时我们发现，下边的纵坐标变大，矩形内部包含的点的个数就不会增大；下边的纵坐标变小，矩形内部包含的点的个数就不会减少。所以我们可以 $O(\log n)$ 二分下边的纵坐标，再 $O(1)$ 判断矩形里面的点的个数是否大于等于 $K$ 即可。时间复杂度 $O(n^3\log n)$，代码就不给了。

再优化，我们还可以发现一个性质。对于固定的下边和左边，我们要保证面积最小，即恰好大于等于 $K$ 个点使得 $4$ 条边再缩就会导致矩形包含的点的个数小于 $K$，那么我们逐渐增大右边时，就需要减小上边的纵坐标，来使得矩形恰好包含至少 $K$ 个点。所以一开始我们假设，在离散化后，有 $cx$ 个不同的横坐标，有 $cy$ 个不同纵坐标，我们设定的矩形左边的横坐标编号为 $i$，下边的纵坐标编号为 $j$，右边的横坐标编号为 $k$，上边的纵坐标编号为 $h$，那么我们就让 $k$ 从 $i$ 开始枚举到 $cx$，让 $h$ 从 $cy$ 开始对应缩小使得 $h$ 再缩一点矩形包含的点的个数就会小于 $K$。那么这种情况时才可以保证矩形的面积可能最小。注意，由于 $k=i$ 时很可能即使 $h=cy$，矩形包含的点数也不足 $K$，所以要先让 $k$ 自增到存在 $h\le cy$ 的矩形包含至少 $K$ 个点。时间复杂度：枚举 $i,j$ 要 $O(n^2)$，处理 $h,k$ 需要 $O(n)$，所以总的时间复杂度是 $O(n^3)$。所以其实这一题可以出到 $n\le 500$。

### 二、代码

```cpp
#include<bits/stdc++.h>
#define S(lx,rx,ly,ry) s[rx][ry]+s[lx-1][ly-1]-s[rx][ly-1]-s[lx-1][ry]
using namespace std;
typedef long long ll;
ll n,K,x[60],y[60],ans=4e18,cx,cy,X[60],Y[60],p[60][60],s[60][60],c=0;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>K;
	for(ll i=1;i<=n;i++)cin>>X[i]>>Y[i],x[++c]=X[i],y[c]=Y[i];
	sort(x+1,x+c+1);cx=unique(x+1,x+c+1)-x-1;
	sort(y+1,y+c+1);cy=unique(y+1,y+c+1)-y-1;
	for(ll i=1;i<=n;i++){
		X[i]=lower_bound(x+1,x+cx+1,X[i])-x;
		Y[i]=lower_bound(y+1,y+cy+1,Y[i])-y;
		p[X[i]][Y[i]]=1;
	}
	for(ll i=1;i<=cx;i++)
		for(ll j=1;j<=cy;j++)s[i][j]=p[i][j]+s[i-1][j]+s[i][j-1]-s[i-1][j-1];
	for(ll i=1;i<=cx;i++)
		for(ll j=1;j<=cy;j++)
			if(S(i,cx,j,cy)>=K)
				for(ll k=i,h=cy;k<=cx;k++)
					if(S(i,k,j,cy)>=K){
					while(S(i,k,j,h-1)>=K)h--;
					ans=min(ans,(x[k]-x[i])*(y[h]-y[j]));
				}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：普罗 (赞：0)

首先离散化，把地图缩小到50*50，然后用前缀处理计算出每个区域位置到（0,0）点所构成矩形中的点的个数 然后通过前缀结果快速枚举每两个位置之间的点数总和，最后取满足条件的最小面积（注意计算面积需要使用离散前的长宽数据）

```cpp
#include<stdio.h>
#include<stdlib.h>
struct node
{
	long long x,y;
	int a,b;
}point[55];
int incx(const void *a, const void *b)
{
    struct node m = *(struct node *)a;
    struct node n = *(struct node *)b;
    if(m.x<n.x) return -1;
    else return 1;
}
int incy(const void *a, const void *b)
{
    struct node m = *(struct node *)a;
    struct node n = *(struct node *)b;
    if(m.y<n.y) return -1;
    else return 1;
}
int main()
{
	int n,k,mp[55][55],xmax,ymax,temp;
	bool np[55][55];
	long long x[55],y[55],S,min=-1,xx[55],yy[55],Smax=-1;
	for(int i=0;i<55;i++)
	{
		for(int j=0;j<55;j++)
		{
			mp[i][j]=0;
			np[i][j]=false;
		}
	}
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)scanf("%lld%lld",&point[i].x,&point[i].y);
	qsort(point,n,sizeof(struct node),incx);
	temp=0;
	for(int i=0;i<n;i++)
	{
		point[i].a=temp;
		xx[temp]=point[i].x;
		temp++;
	}
	qsort(point,n,sizeof(struct node),incy);
	temp=0;
	for(int i=0;i<n;i++)
	{
		point[i].b=temp;
		np[point[i].a][point[i].b]=true;
		yy[temp]=point[i].y;
		temp++;
	}
	if(np[0][0]==false)mp[0][0]=0;
	else mp[0][0]=1;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i==0)mp[i][j]=mp[i][j-1]+np[i][j];
			else if(j==0)mp[i][j]=mp[i-1][j]+np[i][j];
			else mp[i][j]=mp[i-1][j]+mp[i][j-1]-mp[i-1][j-1]+np[i][j];
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			for(int p=i+1;p<n;p++)
			{
				for(int q=j+1;q<n;q++)
				{
					int sum;
					if(i==0)sum=mp[p][q]-mp[p][j-1];
					else if(j==0)sum=mp[p][q]-mp[i-1][q];
					else sum=mp[p][q]-mp[i-1][q]-mp[p][j-1]+mp[i-1][j-1];
					if(sum>=k)
					{
						if((xx[p]-xx[i])*(yy[q]-yy[j])<=Smax||Smax<0)Smax=(xx[p]-xx[i])*(yy[q]-yy[j]);
					}
				}
			}
		}
	}
	printf("%lld\n",Smax);
}
```


---

## 作者：fly20040720 (赞：0)

题意：平面上有一些点，要框一个矩形，使它的边界和内部至少有k个点

这题可以说是d题里面码量比较大的了，但是很整齐，就是每一个都是常用技巧。

思维难度很低，就是先离散化，然后枚举，二维前缀和优化（甚至都不用）

```cpp
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;

struct node
{
    int x,y;
} a[55];

map<int,int> mpx,mpy;
map<int,int> invx,invy;

int sum[55][55];
int b[55][55];

bool cmp1(node aa,node bb)
{
    return aa.x < bb.x;
}

bool cmp2(node aa,node bb)
{
    return aa.y < bb.y;
}

int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&a[i].x,&a[i].y);
    long long ans;
    sort(a+1,a+n+1,cmp1);
    for(int i=1;i<=n;i++)
    {
        invx[i]=a[i].x;
        mpx[a[i].x]=i;
    }
    long long dx=a[n].x - a[1].x;
    sort(a+1,a+n+1,cmp2);
    for(int i=1;i<=n;i++)
    {
        invy[i]=a[i].y;
        mpy[a[i].y]=i;
    }
    long long dy=a[n].y - a[1].y;
    ans=dx * dy;
    for(int i=1;i<=n;i++)
    {
        int x=a[i].x,y=a[i].y;
        b[mpx[x]][mpy[y]]=1;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            sum[i][j]=sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + b[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int s=i;s<=n;s++)
                for(int q=j;q<=n;q++)
                {
                    if(sum[s][q] - sum[s][j-1] - sum[i-1][q] + sum[i-1][j-1] >= k)
                    {
                        long long dx=invx[s] - invx[i];
                        long long dy=invy[q] - invy[j];
                        long long tmp=abs(dx) * abs(dy);
                        ans=min(ans,tmp);
                    }
                }
    printf("%lld\n",ans);
    return 0;
}

---

