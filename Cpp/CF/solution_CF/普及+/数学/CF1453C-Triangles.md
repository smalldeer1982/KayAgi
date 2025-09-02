# Triangles

## 题目描述

Gildong has a square board consisting of $ n $ rows and $ n $ columns of square cells, each consisting of a single digit (from $ 0 $ to $ 9 $ ). The cell at the $ j $ -th column of the $ i $ -th row can be represented as $ (i, j) $ , and the length of the side of each cell is $ 1 $ . Gildong likes big things, so for each digit $ d $ , he wants to find a triangle such that:

- Each vertex of the triangle is in the center of a cell.
- The digit of every vertex of the triangle is $ d $ .
- At least one side of the triangle is parallel to one of the sides of the board. You may assume that a side of length $ 0 $ is parallel to both sides of the board.
- The area of the triangle is maximized.

Of course, he can't just be happy with finding these triangles as is. Therefore, for each digit $ d $ , he's going to change the digit of exactly one cell of the board to $ d $ , then find such a triangle. He changes it back to its original digit after he is done with each digit. Find the maximum area of the triangle he can make for each digit.

Note that he can put multiple vertices of the triangle on the same cell, and the triangle can be a [degenerate triangle](https://cutt.ly/NhbjZ2l); i.e. the area of the triangle can be $ 0 $ . Also, note that he is allowed to change the digit of a cell from $ d $ to $ d $ .

## 说明/提示

In the first case, for $ d=0 $ , no matter which cell he chooses to use, the triangle with vertices at $ (1, 1) $ , $ (1, 3) $ , and $ (3, 1) $ is the biggest triangle with area of $ \cfrac{2 \cdot 2}{2} = 2 $ . Since we should print it multiplied by $ 2 $ , the answer for $ d=0 $ is $ 4 $ .

For $ d=1 $ , Gildong can change the digit of the cell at $ (1, 3) $ into $ 1 $ , making a triangle with vertices on all three $ 1 $ 's that has an area of $ 2 $ .

For $ d=2 $ , Gildong can change the digit of one of the following six cells into $ 2 $ to make a triangle with an area of $ \cfrac{1}{2} $ : $ (1, 1) $ , $ (1, 2) $ , $ (1, 3) $ , $ (3, 1) $ , $ (3, 2) $ , and $ (3, 3) $ .

For the remaining digits (from $ 3 $ to $ 9 $ ), the cell Gildong chooses to change will be the only cell that contains that digit. Therefore the triangle will always be a degenerate triangle with an area of $ 0 $ .

In the third case, for $ d=4 $ , note that the triangle will be bigger than the answer if Gildong changes the digit of the cell at $ (1, 4) $ and use it along with the cells at $ (2, 1) $ and $ (4, 3) $ , but this is invalid because it violates the condition that at least one side of the triangle must be parallel to one of the sides of the board.

## 样例 #1

### 输入

```
5
3
000
122
001
2
57
75
4
0123
4012
3401
2340
1
9
8
42987101
98289412
38949562
87599023
92834718
83917348
19823743
38947912```

### 输出

```
4 4 1 0 0 0 0 0 0 0
0 0 0 0 0 1 0 1 0 0
9 6 9 9 6 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
18 49 49 49 49 15 0 30 42 42```

# 题解

## 作者：WitheredZeal (赞：3)

我先对另一篇题解的话表示反驳，我的方法才是最麻烦的（悲）。  
# 题意  
你有$n \times m$ 个点，每个点有一种颜色（$0 \sim 9$）。  
对于每一种颜色，你需要求出，如果你最多修改一个点的颜色，可以组成的三角形的最大面积是多少，要求这个三角形至少有一条边是水平或者竖直的。  
输出面积$\times2$（为了避免输出小数）。

# 题解  

“要求这个三角形至少有一条边是水平或者竖直的。”  
那么我们就对至少有一条边是水平的和至少有一条边是竖直的都算一遍最大值即可。  
为了避免常数过大，我们把$10$个颜色一起做，而不是对每个颜色做一遍。

### 1.至少有一条边是水平的  
三角形有 $2$ 种情况。  
- 本来有一条边是水平的，那么把离这条边最远的点染成这个颜色可以使面积最大。   

- 我们找到一个点，然后把这一排中离它最远的点染成相同的颜色，然后再找到离这条边最远的**已经是相同颜色**的点。  

	具体代码：  
```cpp
	for (int i=0;i<=9;i++) U[i]=n+1,D[i]=0;
	//U[i]表示i号颜色最上面的点的行数，D[i]表示i号颜色最下面的点的行数
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
		{
			U[a[i][j]]=min(U[a[i][j]],i);
			D[a[i][j]]=max(D[a[i][j]],i);
		}
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<=9;j++) L[j]=n+1,R[j]=0;
		//L[j]表示当前行（第i行）j号颜色最左边的点的列数
		//R[j]表示当前行（第i行）j号颜色最右边的点的列数
		for (int j=1;j<=n;j++) 
		{
			L[a[i][j]]=min(L[a[i][j]],j);
			R[a[i][j]]=max(R[a[i][j]],j);
		}
		for (int j=0;j<=9;j++)
		{
			//这是第一种情况
			//R[j]-L[j] 水平边的最长长度
			//max(i-1,n-i)是离这条边最远的点 离这条边的距离
			ans[j]=max(ans[j],(R[j]-L[j])*max(i-1,n-i));

			//这是第二种情况，H是最大高度，W是最宽宽度
			int H=max(i-U[j],D[j]-i);
			int W=max(R[j]-1,n-L[j]);
			//注意有可能2个负数相乘变成了正数，所以要清零
			if (H<0) H=0;
			if (W<0) W=0;
			ans[j]=max(ans[j],W*H);
		}
	}
```  


### 2.至少有一条边是竖直的  
情况类似，$2$ 种情况。  
- 本来有一条边是竖直的，那么把离这条边最远的点染成这个颜色可以使面积最大。   

- 我们找到一个点，然后把这一列中离它最远的点染成相同的颜色，然后再找到离这条边最远的**已经是相同颜色**的点。  

	代码也类似
```cpp
	for (int i=0;i<=9;i++) L[i]=n+1,R[i]=0;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
		{
			L[a[i][j]]=min(L[a[i][j]],j);
			R[a[i][j]]=max(R[a[i][j]],j);
		}
	}
	for (int j=1;j<=n;j++)
	{
		for (int i=0;i<=9;i++) U[i]=n+1,D[i]=0;
		for (int i=1;i<=n;i++)
		{
			U[a[i][j]]=min(U[a[i][j]],i);
			D[a[i][j]]=max(D[a[i][j]],i);
		}
		for (int i=0;i<=9;i++)
		{
			ans[i]=max(ans[i],(D[i]-U[i])*max(j-1,n-j));
			int W=max(j-L[i],R[i]-j);
			int H=max(D[i]-1,n-U[i]);
			if (H<0) H=0;
			if (W<0) W=0;
			ans[i]=max(ans[i],H*W);
		}
	}
```  

完整代码如下：  
```cpp
#include<bits/stdc++.h>
#define int long long
#define rd(x) x=read()
using namespace std;
const int N=2005+5;
const int M=5005;
const int mod=998244353;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int ksm(int x,int y){int ret=1;while (y){if (y&1) ret=(ret*x)%mod;x=(x*x)%mod;y>>=1;}return ret;}
 
int n,m,k;
int a[N][N];
string str;
int ans[N];
int L[N],R[N];
int U[N],D[N];
signed main()
{
	int T;
	cin>>T;
	while (T--)
	{
		rd(n);
		for (int i=0;i<=9;i++) ans[i]=0;
		for (int i=1;i<=n;i++)
		{
			cin>>str;
			for (int j=1;j<=n;j++) a[i][j]=str[j-1]-'0';
		}
		for (int i=0;i<=9;i++) U[i]=n+1,D[i]=0;
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
			{
				U[a[i][j]]=min(U[a[i][j]],i);
				D[a[i][j]]=max(D[a[i][j]],i);
			}
		}
		for (int i=1;i<=n;i++)
		{
			for (int j=0;j<=9;j++) L[j]=n+1,R[j]=0;
			for (int j=1;j<=n;j++) 
			{
				L[a[i][j]]=min(L[a[i][j]],j);
				R[a[i][j]]=max(R[a[i][j]],j);
			}
			for (int j=0;j<=9;j++)
			{
				ans[j]=max(ans[j],(R[j]-L[j])*max(i-1,n-i));
				int H=max(i-U[j],D[j]-i);
				int W=max(R[j]-1,n-L[j]);
				if (H<0) H=0;
				if (W<0) W=0;
				ans[j]=max(ans[j],W*H);
			}
		}
		for (int i=0;i<=9;i++) L[i]=n+1,R[i]=0;
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
			{
				L[a[i][j]]=min(L[a[i][j]],j);
				R[a[i][j]]=max(R[a[i][j]],j);
			}
		}
		for (int j=1;j<=n;j++)
		{
			for (int i=0;i<=9;i++) U[i]=n+1,D[i]=0;
			for (int i=1;i<=n;i++)
			{
				U[a[i][j]]=min(U[a[i][j]],i);
				D[a[i][j]]=max(D[a[i][j]],i);
			}
			for (int i=0;i<=9;i++)
			{
				ans[i]=max(ans[i],(D[i]-U[i])*max(j-1,n-j));
				int W=max(j-L[i],R[i]-j);
				int H=max(D[i]-1,n-U[i]);
				if (H<0) H=0;
				if (W<0) W=0;
				ans[i]=max(ans[i],H*W);
			}
		}
		for (int i=0;i<=9;i++) printf("%lld ",ans[i]);
		cout<<endl;
	}
}
```

---

## 作者：IntrepidStrayer (赞：2)

## 题意

给定 $n\times m$ 个方格，每个方格有颜色（$0-9$）。对于每一个 $k\;(0\le k\le 9)$，最多可以修改一个方格的颜色，在这些方格中选取三个，求一个面积最大的三角形使得

1. 三角形的顶点在格子的中心
2. 三个格子的颜色都是 $k$ 
3. 至少一条边与边界平行（即水平或竖直）。

## 题解

由于可以修改一个点的颜色，那么只需要找两个点。

我们称与边界平行的边为底边。

1. 两点都是底边的端点

这两个点必定在同一行或同一列。以同一行为例，设两点在第 $i$ 行，颜色是 $k$。为使底边最大，这两个点要取第 $i$ 行最左边的和最右边的 $k$ 色点。为使高最大，可以取另一个点在第 $1$ 行或第 $n$ 行。

2. 有一点不是底边的端点

我们枚举底边的一个端点，假设在第 $i$ 行第 $j$ 列，颜色是 $k$。

以底边水平为例。为使高最大，应取另一个点在 **所有方格中最上方或最下方的颜色为 $k$ 的方格**。为使底边最长，应取底边的另一个端点在第 $1$ 列或第 $n$ 列。

注意第一点要求：两个同一行的点分别在第 $i$ 列和第 $j$ 列，线段长度为 $\mid i-j\mid$ 而不需要加 $1$。因此不需要判断是否组成三角形（是否有位置相同的两点），因为此时面积为 $0$。

## 代码

```cpp
/*
top[0/1][i][k] 表示第 i 行最左 / 右的颜色为 k 的格子在第几列
top[2/3][i][k] 表示第 i 列最上 / 下的颜色为 k 的格子在第几行。
ccc[0/1/2/3][k] 表示所有方格中最左 / 右 / 上 / 下的颜色为 k 的方格的列 / 行。
*/

#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;
inline int max(int x, int y) {return x > y ? x : y;}
inline void chmax(int& x, int y) {if(x < y) x = y;}
inline void chmin(int& x, int y) {if(x > y) x = y;}
inline int min(int x, int y) {return x < y ? x : y;}
inline void swap(int &x, int &y) {x ^= y ^= x ^= y;}
#define rei register int
#define rep(i, l, r) for(rei i = l, i##end = r; i <= i##end; ++i)
#define per(i, r, l) for(rei i = r, i##end = l; i >= i##end; --i)
char inputbuf[1 << 23], *p1 = inputbuf, *p2 = inputbuf;
#define getchar() (p1 == p2 && (p2 = (p1 = inputbuf) + fread(inputbuf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
inline int read() {
	int res = 0; char ch = getchar(); bool f = true;
	for(; ch < '0' || ch > '9'; ch = getchar())
		if(ch == '-') f = false;
	for(; ch >= '0' && ch <= '9'; ch = getchar())
		res = res * 10 + (ch ^ 48);
	return f ? res : -res;
}
inline char getch() {
	char ch = getchar(); for(; ch == ' ' || ch == '\n'; ch = getchar());
	return ch;
}
const int N = 2015;
char a[N][N];
int top[4][N][10], ccc[4][10], n, mx[10];

void input() {
	n = read();
	rep(i, 1, n) rep(j, 1, n) a[i][j] = getch() - 48;
}

void init() {// 预处理
	memset(top, 0, sizeof(top));
	rep(i, 1, n)
		for(rei j = 1, lst = 10; j <= n && lst; ++ j)
			if(!top[0][i][a[i][j]]) top[0][i][a[i][j]] = j, -- lst;
	rep(i, 1, n)
		for(rei j = n, lst = 10; j >= 1 && lst; -- j)
			if(!top[1][i][a[i][j]]) top[1][i][a[i][j]] = j, -- lst;
	rep(j, 1, n)
		for(rei i = 1, lst = 10; i <= n && lst; ++ i)
			if(!top[2][j][a[i][j]]) top[2][j][a[i][j]] = i, -- lst;
	rep(j, 1, n)
		for(rei i = n, lst = 10; i >= 1 && lst; -- i)
			if(!top[3][j][a[i][j]]) top[3][j][a[i][j]] = i, -- lst;
	rep(i, 0, 9) {
		ccc[0][i] = ccc[2][i] = 1e9;
		ccc[1][i] = ccc[3][i] = 0;
	}
	rep(i, 1, n) rep(d, 0, 9) {
		if(top[0][i][d]) chmin(ccc[0][d], top[0][i][d]);
		if(top[2][i][d]) chmin(ccc[2][d], top[2][i][d]);
		chmax(ccc[1][d], top[1][i][d]);
		chmax(ccc[3][d], top[3][i][d]);
	}
}

void solve() {
	int r;
	memset(mx, 0, sizeof(mx));
	rep(d, 0, 9) {//1.
		rep(i, 1, n)
			if(top[0][i][d] && top[1][i][d])
				chmax(mx[d], (top[1][i][d] - top[0][i][d]) * max(i - 1, n - i));
		rep(i, 1, n)
			if(top[2][i][d] && top[3][i][d])
				chmax(mx[d], (top[3][i][d] - top[2][i][d]) * max(i - 1, n - i));
	}
	rep(i, 1, n) rep(j, 1, n) {//2.
		r = a[i][j];
		chmax(mx[r], (j - ccc[0][r]) * max(i - 1, n - i));
		chmax(mx[r], (ccc[1][r] - j) * max(i - 1, n - i));
		chmax(mx[r], (i - ccc[2][r]) * max(j - 1, n - j));
		chmax(mx[r], (ccc[3][r] - i) * max(j - 1, n - j));
	}
	rep(i, 0, 9) printf("%d ", mx[i]); putchar(10);
}

signed main() {
	for(int T = read(); T; -- T) {
		input();
		init();
		solve();
	}
	return 0;
}
```

---

## 作者：Little09 (赞：0)

估计我的方法是最麻烦的…但是这题没有题解，那我来一发。

因为可以将任意一个方格改为所需的数字，所以只要有两个点就可以找三角形。可以分两种情况：

1. 两个点的连线与方格纸平行

	另一个点在边界上时面积最大。
    
    比如先做水平方向，先枚举一个行，找到两个个点在此水平方向上最靠左、右的点就可以了。最靠左、右的点可以预处理。然后再对列处理一次。
    
2. 两个点的连线不与方格纸平行

	另一个点有要求：一定与这两个点其中一个的横坐标或纵坐标相等。同样也在边界上最大。
    
    处理方式和上面差不多，就是不用一行一行地来，应当在整个图找最左最右的点。然后再处理一次上下。
    
实现有点复杂……不过就都是复制再改一改就好了。

不理解的画图理解一下，思路还是很简单的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2001][2001]; 
int p[2][2001][10],q[2][2001][10],ans[10];
int P[11],Q[11];
inline int read()
{
	char C=getchar();
	int F=1,ANS=0;
	while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
	while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
	return F*ANS;
} 
int main()
{
	int T=read();
	while (T--)
	{
		int n=read();
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
			{
				char x;
				cin >> x;
				a[i][j]=x-'0';
			}
		}
		memset(ans,0,sizeof(ans));
		for (int i=1;i<=n;i++)
		{
			for (int j=0;j<10;j++) p[0][i][j]=-1,q[0][i][j]=-1;
			for (int j=1;j<=n;j++)
			{
				if (p[0][i][a[i][j]]==-1) p[0][i][a[i][j]]=j;
			}
			for (int j=n;j>=1;j--)
			{
				if (q[0][i][a[i][j]]==-1) q[0][i][a[i][j]]=j;
			}
			for (int j=0;j<=9;j++)
			{
				if (p[0][i][j]!=-1&&q[0][i][j]!=p[0][i][j]) ans[j]=max(ans[j],(q[0][i][j]-p[0][i][j])*max(i-1,n-i));
			}
		}
		for (int i=1;i<=n;i++)
		{
			for (int j=0;j<10;j++) p[1][i][j]=-1,q[1][i][j]=-1;
			for (int j=1;j<=n;j++)
			{
				if (p[1][i][a[j][i]]==-1) p[1][i][a[j][i]]=j;
			}
			for (int j=n;j>=1;j--)
			{
				if (q[1][i][a[j][i]]==-1) q[1][i][a[j][i]]=j;
			}
			for (int j=0;j<=9;j++)
			{
				if (p[1][i][j]!=-1&&q[1][i][j]!=p[1][i][j]) ans[j]=max(ans[j],(q[1][i][j]-p[1][i][j])*max(i-1,n-i));
			}
		}
		for (int i=0;i<=9;i++) P[i]=-1,Q[i]=-1;
		for (int i=n;i>=1;i--)
		{
			for (int j=1;j<=n;j++)
			{
				if (P[a[j][i]]==-1) P[a[j][i]]=i;
			}
		}
		for (int i=n;i>=1;i--)
		{
			for (int j=1;j<=n;j++)
			{
				if (Q[a[i][j]]==-1) Q[a[i][j]]=i;
			}
		}
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
			{
				if (P[a[i][j]]!=-1&&P[a[i][j]]!=j) ans[a[i][j]]=max(ans[a[i][j]],(P[a[i][j]]-j)*max(i-1,n-i));
			}
		}
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
			{
				if (Q[a[i][j]]!=-1&&Q[a[i][j]]!=i) ans[a[i][j]]=max(ans[a[i][j]],(Q[a[i][j]]-i)*max(j-1,n-j));
			}
		}
		for (int i=0;i<=9;i++) P[i]=-1,Q[i]=-1;
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
			{
				if (P[a[j][i]]==-1) P[a[j][i]]=i;
			}
		}
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
			{
				if (Q[a[i][j]]==-1) Q[a[i][j]]=i;
			}
		}
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
			{
				if (P[a[i][j]]!=-1&&P[a[i][j]]!=j) ans[a[i][j]]=max(ans[a[i][j]],(j-P[a[i][j]])*max(i-1,n-i));
			}
		}
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++)
			{
				if (Q[a[i][j]]!=-1&&Q[a[i][j]]!=i) ans[a[i][j]]=max(ans[a[i][j]],(i-Q[a[i][j]])*max(j-1,n-j));
			}
		}
		for (int i=0;i<=9;i++) cout << ans[i] << " ";
		cout << endl;
	}
	return 0;
}
```

代码写的有点长。

---

