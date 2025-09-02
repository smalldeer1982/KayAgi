# Spiral Maximum

## 题目描述

Let's consider a $ k×k $ square, divided into unit squares. Please note that $ k>=3 $ and is odd. We'll paint squares starting from the upper left square in the following order: first we move to the right, then down, then to the left, then up, then to the right again and so on. We finish moving in some direction in one of two cases: either we've reached the square's border or the square following after the next square is already painted. We finish painting at the moment when we cannot move in any direction and paint a square. The figure that consists of the painted squares is a spiral.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF173C/9bdc9b1befc556927df1bc6bdf8e832b185f9b78.png) The figure shows examples of spirals for $ k=3,5,7,9 $ . You have an $ n×m $ table, each of its cells contains a number. Let's consider all possible spirals, formed by the table cells. It means that we consider all spirals of any size that don't go beyond the borders of the table. Let's find the sum of the numbers of the cells that form the spiral. You have to find the maximum of those values among all spirals.

## 说明/提示

In the first sample the spiral with maximum sum will cover all 1's of the table.

In the second sample the spiral may cover only six 1's.

## 样例 #1

### 输入

```
6 5
0 0 0 0 0
1 1 1 1 1
0 0 0 0 1
1 1 1 0 1
1 0 0 0 1
1 1 1 1 1
```

### 输出

```
17```

## 样例 #2

### 输入

```
3 3
1 1 1
1 0 0
1 1 1
```

### 输出

```
6```

## 样例 #3

### 输入

```
6 6
-3 2 0 1 5 -1
4 -1 2 -3 0 1
-5 1 2 4 1 -2
0 -2 1 3 -1 2
3 1 4 -3 -2 0
-1 2 -1 3 1 2
```

### 输出

```
13```

# 题解

## 作者：E1_de5truct0r (赞：6)

简单的 dp。

首先看到题目，发现暴力是 $O(n^4)$ 妥妥的 T 飞。因此考虑 dp 优化复杂度。不难想到状态：$dp_{l,i,j}$ 表示边长为 $l$，顶点位于 $(i,j)$ 的正方形内，“螺旋形”所能取到的最大值。

那么怎么转移呢？这成为了本题的难点。

如果你像 @wz20201136 一样强大，你可以选择暴力莽规律，但是我太懒了。所以就撑着下巴看了 20 分钟题，然后发现了惊人的结论：

先放图。

![](https://cdn.luogu.com.cn/upload/image_hosting/xleqfydt.png)

第一幅和第三幅对比，第二幅和第四幅对比。你发现了什么？

没错，$(l,i,j)$ 相当于一圈外框，去掉 $(i+1,j)$ 这个点再加上 $(i+2,j+1)$ 这个点，其余的就是 $dp_{l-4,i+2,j+2}$。

所以转移方程就推出来了，并不轻松。

$$dp_{l,i,j} = sqr_{i,j} - a_{i+1,j} + a_{i+2,j+1} + dp_{l-4,i+2,j+2}$$

其中 $sqr{l,i,j}$ 计算的是这个正方形的周长，需要分别用到每行每列的前缀和。总时间复杂度 $O(n^3)$。但是空间太大开不下怎么办？我们发现 $l-4$ 与 $l-1 \operatorname{mod} 3$ 同余，所以可以把第一位压成 3，每次 $dp_{l\%3,i,j}$ 从 $dp_{(l-1)\%3,i,j}$ 转移即可。那么这道题就做完了，应该是目前最简洁的做法。

```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[3][505][505],a[505][505],hp[505][505],lp[505][505];

int sqr(int l,int x,int y)
{
	int X=x+l-1,Y=y+l-1;
	int upr=hp[x][Y]-hp[x][y-1], // 正方形上面一条边 
		lfl=lp[X][y]-lp[x-1][y], // 正方形左边一条边 
		dor=hp[X][Y]-hp[X][y-1], // 正方形下面一条边 
		ril=lp[X][Y]-lp[x-1][Y]; // 正方形右边一条边
	return upr+lfl+dor+ril-a[x][y]-a[X][y]-a[x][Y]-a[X][Y];
	// 在计算的时候四个角上的顶点会算两次，因此分别减去。
}
int main()
{
	int n,m,ans=-1e9;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			hp[i][j]=hp[i][j-1]+a[i][j]; // 每行的前缀和 
			lp[i][j]=lp[i-1][j]+a[i][j]; // 每列的前缀和 
			dp[1][i][j]=a[i][j]; // 当 l=5 时要用到，虽然题目中不成立但是必须要写 
		}
	//以上为预处理和输入
	 
	for(int l=3;l<=min(n,m);l+=2) // 边长长度 
		for(int i=1;i+l-1<=n;i++)
			for(int j=1;j+l-1<=m;j++) // 左上角顶点位置 
			{
				dp[l%3][i][j]=sqr(l,i,j)-a[i+1][j]+dp[(l-1)%3][i+2][j+2];
				if(l!=3) dp[l%3][i][j]+=a[i+2][j+1];
				ans=max(ans,dp[l%3][i][j]); // 找最优答案 
			}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Allanljx (赞：5)

## 思路
首先，每个螺旋矩阵都是边长为奇数正方形，因此我们以中心那一格为基准，然后就可以发现上一个正方形刚好可以塞到当前这个正方形中。因此我们先枚举中心点，然后枚举边长，最后用前缀和转移。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans=-INT_MAX;
int a[505][505];
int h[505][505];
int qz[505][505];
void init()//前缀和
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			h[i][j]=h[i][j-1]+a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			qz[i][j]=a[i][j]+qz[i-1][j]+h[i][j-1];
		}
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}
	init();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)//枚举中心点
		{
			int sum=a[i][j];//边长为1
			for(int k=3;k<=min(n,m);k+=2)//枚举边长
			{
				if(i+k/2>n||i-k/2<1||j+k/2>m||j-k/2<1)//越界
					break;
				sum=qz[i+k/2][j+k/2]-qz[i+k/2][j-k/2-1]-qz[i-k/2-1][j+k/2]+qz[i-k/2-1][j-k/2-1]-sum-a[i-k/2+1][j-k/2];//转移
				ans=max(ans,sum);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：_lxy_ (赞：4)

### 题意 

求一个 $n \times m$ 的矩形中螺旋形最大的数字和。 

### 分析

![](https://cdn.luogu.com.cn/upload/image_hosting/ui2ckug2.png)

看图不难发现，以同一个方块为中心的两个边长差为 $2$ 的螺旋形的数字和其实是有规律的，大一些的螺旋形的数字和就等于整个正方形的数字和减去小一些的螺旋形数字和再减去小螺旋形左上角左侧的数。因此我们先用二维前缀和预处理每一个正方形的面积，然后循环每一个中心，递推出以 $(i,j)$ 为中心，从 $(i,j)$ 向边缘有 $k$ 个方格的螺旋形的数字和。

```cpp 
dp[i][j][k]=sum(i,j,k)-dp[i][j][k-1]-a[i-k+1][j-k],ans=qmax(ans,dp[i][j][k]); 
```

### 代码

```cpp
#include <bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int MAXN=503;
const int inf=2139062143;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
	register T1 x=0;register bool f=false;char ch=getchar();
	while(ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch>='0') x=(x*10)+(ch^48),ch=getchar();
	x=(f?-x:x);a=x;qread(b...);
}
template<class T1,class T2>inline T1 qmax(const T1 &x,const T2 &y){return x>y?x:y;}
template<class T1,class T2>inline T1 qmin(const T1 &x,const T2 &y){return x<y?x:y;}
int n,m,a[MAXN][MAXN],dp[MAXN][MAXN][257],f[MAXN][MAXN],ans=-inf;
inline int get_sum(int a1,int b1,int a2,int b2){return f[a2][b2]-f[a1-1][b2]-f[a2][b1-1]+f[a1-1][b1-1];}
inline int sum(int a1,int b1,int k){return get_sum(a1-k,b1-k,a1+k,b1+k);} // 计算正方形数字和
int main()
{
	qread(n,m);int i,j,k;for(i=1;i<=n;i++) for(j=1;j<=m;j++) qread(a[i][j]);
	for(i=1;i<=n;i++) for(j=1;j<=m;j++) f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1]+a[i][j]; // 二维前缀和
	for(i=1;i<=n;i++) for(j=1;j<=m;j++) dp[i][j][0]=a[i][j]; // 初始化，每个边长为1的螺旋形的数字和都是所在格子的数
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			int t=qmin(i-1,qmin(j-1,qmin(n-i,m-j))); // 最大边长
			for(k=1;k<=t;k++) dp[i][j][k]=sum(i,j,k)-dp[i][j][k-1]-a[i-k+1][j-k],ans=qmax(ans,dp[i][j][k]);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：npqenqpve (赞：4)

### 思路：
发现可能的答案的种类是 $n^3$ 级别的，可以直接搞出来，但是显然不能模拟走螺旋。

观察样例可以发现，对于一个起点是 $(i,j)$，大小为 $k$ 的螺旋，其实相当于在某个范围内去掉一个起点为 $(i+1,j+1)$ 的大小为 $k-2$ 的螺旋，在去掉 $(i+1,j)$ 这个点的值。

然后就可以直接求出从某个点开始大小为 $k$ 的螺旋了
但是这记录了三个互相独立的信息，需要 $n^3$ 的空间，显然开不下。

但是其实每一次得到新的 $(i,j)$ 和 $k$ 之前，都保留了一部分 $k-2$ 时的答案，我们要用的也只有 $(i+1,j+1)$，直接覆盖即可。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[505][505],dp[505][505],d[505][505];
int n,m,ans=-INT_MAX;
signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
            dp[i][j][1]=a[i][j];
            d[i][j]=d[i-1][j]+d[i][j-1]-d[i-1][j-1]+a[i][j];
        }
    }
    for(int k=3;k<=min(n,m);k+=2)
    {
        for(int i=1;k+i-1<=n;i++)
        {
            for(int j=1;k+j-1<=m;j++)
            {
                dp[i][j]=d[k+i-1][k+j-1]-d[k+i-1][j-1]-d[i-1][k+j-1]+d[i-1][j-1]-dp[i+1][j+1]-a[i+1][j];
                ans=max(dp[i][j],ans);
            }
        }
    }
    cout<<ans;
}
```

---

