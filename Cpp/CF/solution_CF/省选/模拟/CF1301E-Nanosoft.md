# Nanosoft

## 题目描述

Warawreh created a great company called Nanosoft. The only thing that Warawreh still has to do is to place a large picture containing its logo on top of the company's building.

The logo of Nanosoft can be described as four squares of the same size merged together into one large square. The top left square is colored with red, the top right square is colored with green, the bottom left square is colored with yellow and the bottom right square is colored with blue.

An Example of some correct logos:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1301E/b18bda37e952600d50a433d5d6d034271a8ea951.png)

An Example of some incorrect logos:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1301E/aae70af4076310da7ad4524bd1dc8d30ba1f870a.png)

Warawreh went to Adhami's store in order to buy the needed picture. Although Adhami's store is very large he has only one picture that can be described as a grid of $ n $ rows and $ m $ columns. The color of every cell in the picture will be green (the symbol 'G'), red (the symbol 'R'), yellow (the symbol 'Y') or blue (the symbol 'B').

Adhami gave Warawreh $ q $ options, in every option he gave him a sub-rectangle from that picture and told him that he can cut that sub-rectangle for him. To choose the best option, Warawreh needs to know for every option the maximum area of sub-square inside the given sub-rectangle that can be a Nanosoft logo. If there are no such sub-squares, the answer is $ 0 $ .

Warawreh couldn't find the best option himself so he asked you for help, can you help him?

## 说明/提示

Picture for the first test:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1301E/5c5a8909793534c432ad07cd7594615ef6950dde.png)

The pictures from the left to the right corresponds to the options. The border of the sub-rectangle in the option is marked with black, the border of the sub-square with the maximal possible size, that can be cut is marked with gray.

## 样例 #1

### 输入

```
5 5 5
RRGGB
RRGGY
YYBBG
YYBBR
RBBRG
1 1 5 5
2 2 5 5
2 2 3 3
1 1 3 5
4 4 5 5```

### 输出

```
16
4
4
4
0```

## 样例 #2

### 输入

```
6 10 5
RRRGGGRRGG
RRRGGGRRGG
RRRGGGYYBB
YYYBBBYYBB
YYYBBBRGRG
YYYBBBYBYB
1 1 6 10
1 3 3 10
2 2 6 6
1 7 6 10
2 1 5 10```

### 输出

```
36
4
16
16
16```

## 样例 #3

### 输入

```
8 8 8
RRRRGGGG
RRRRGGGG
RRRRGGGG
RRRRGGGG
YYYYBBBB
YYYYBBBB
YYYYBBBB
YYYYBBBB
1 1 8 8
5 2 5 7
3 1 8 6
2 3 5 8
1 2 6 8
2 1 5 5
2 1 7 7
6 5 7 5```

### 输出

```
64
0
16
4
16
4
36
0```

# 题解

## 作者：EternalAlexander (赞：12)

记答案 $x$ 为边长的一半（也就是四块中某一个块的边长），所求即 $4x^2$。 

首先我们观察到，以一个点为左上角的合法图像最多只有一个。考虑以这个点为左上角的最小合法图像，显然任何真包含它的矩形都不是合法的图像。

第二个重要的观察是，假如询问范围内存在答案为 $x$ 的合法图像，一定存在答案为 $x-1$ 的合法图像，可以由之前的图像把最外面一圈扔掉得到，显然扔掉一圈的图像仍然在询问范围内。

至此我们可以开始做了。首先预处理出 $A_{i,j}$ 表示以 $i,j$ 为左上角的合法图像的答案，因为 $n\leq 500$ ，只要你支持查询一个矩形区间是否都是某种颜色，这个东西就可以 $\mathcal O(n^3)$ 暴力计算了。这种查询容易用二维前缀和实现。

如何处理询问呢，我们二分这个答案 $a$，即判断区间内是否存在答案至少为 $a$ 的图像。利用上述观察2的性质，我们知道这等价于区间内是否存在答案 **恰好** 为 $a$ 的图像，也就是查询子矩形 $(x1,y1),(x2-2a+1,y2-2a+1)$ 内是否存在 $(x,y)$ 使得 $A_{x,y}=a$ 。这个查询容易处理，我们对每种 $A_{x,y}$ 计算一个二维前缀和数组就可以 $\mathcal O(1)$ 查询了。

总复杂度 $\mathcal O(n^3+q\log n)$。

---

## 作者：奇米 (赞：6)

## 题解- $CF1301E \ Nanosoft$

[$$\huge\color{blue}\boxed{\color{Violet}\mathfrak{There\ is \ my \ blog}}$$](https://www.luogu.com.cn/blog/wyy2020/)


* **题目意思**

	就是让你在一个区域中找到最大符合条件的正方形。
    
* $Sol$

	考虑暴力用前缀和优化来统计答案。
    
    首先对于每一种颜色做一遍二位前缀和。然后$O(n \times m \times \min(n,m))$暴力**拓展**处理出所有边长为$k$的符合条件的正方形（具体做法看代码）。然后对一个符合条件的正方形的左上角打标记，再对整个矩形中符合条件的位置数做前缀和即可。然后就是$O(Q\times \min(n,m))$查询即可。代码里有比较清楚的解释。
    
* $Code$

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int N=505;
const int M=275;

char ch[N][N];
int n,m,Q,f[N][N],g[N][N][5],h[N][N][M],ans;

int main()
{
	n=read();
	m=read();
	Q=read();
	for ( int i=1;i<=n;i++ ) scanf("%s",ch[i]+1);
	for ( int i=1;i<=n;i++ ) 
		for ( int j=1;j<=m;j++ )
		{
			for ( int k=0;k<4;k++ )
				g[i][j][k]=g[i-1][j][k]+g[i][j-1][k]-g[i-1][j-1][k];
			if(ch[i][j]=='R') g[i][j][0]++;
			if(ch[i][j]=='G') g[i][j][1]++;
			if(ch[i][j]=='B') g[i][j][2]++;
			if(ch[i][j]=='Y') g[i][j][3]++;
		}
        //对每种颜色处理前缀和
	for ( int i=1;i<n;i++ ) 
		for ( int j=1;j<m;j++ )
			if(ch[i][j]=='R'&&ch[i+1][j]=='Y'&&ch[i][j+1]=='G'&&ch[i+1][j+1]=='B')
			{
				f[i][j]=1;
				for ( int k=2;k<=min(n,m)/2;k++ ) 
				{
					int x=i-k+1,y=j-k+1;
					int a=i,b=j;
					if(x<1||y<1) break;
                    //注意边界
					if(g[a][b][0]-g[a][y-1][0]-g[x-1][b][0]+g[x-1][y-1][0]!=k*k) break;
					x=i-k+1,y=j+1;
					a=i,b=j+k;
					if(x<1||y<1||a>n||b>m) break;
					if(g[a][b][1]-g[a][y-1][1]-g[x-1][b][1]+g[x-1][y-1][1]!=k*k) break;
					x=i+1,y=j+1;
					a=i+k,b=j+k;
					if(x<1||y<1||a>n||b>m) break;
					if(g[a][b][2]-g[a][y-1][2]-g[x-1][b][2]+g[x-1][y-1][2]!=k*k) break;
					x=i+1,y=j-k+1;
					a=i+k,b=j;
                    //x,y,a,b表示每一块颜色的左上左下，右上右下的位置
					if(x<1||y<1||a>n||b>m) break;
					if(g[a][b][3]-g[a][y-1][3]-g[x-1][b][3]+g[x-1][y-1][3]!=k*k) break;
					f[i-k+1][j-k+1]=k;
                    //对左上角打标记
				}
			}
	for ( int i=1;i<n;i++ ) 
		for ( int j=1;j<m;j++ ) 
			if(f[i][j]) h[i][j][f[i][j]]=1;
            //这个点对于边长k合法的
	for ( int i=1;i<=n;i++ ) 
		for ( int j=1;j<=m;j++ )
			for ( int k=1;k<=min(n,m)/2;k++ ) 
				h[i][j][k]+=h[i-1][j][k]+h[i][j-1][k]-h[i-1][j-1][k];//对合法点数量做前缀和
	while(Q--)
	{
		int x=read(),y=read();
		int xx=read(),yy=read();
		int mx=min(xx-x+1,yy-y+1)/2;
		for ( int k=mx;k>=1;k-- )//打着枚举，找到就结束
		{
			int sx=xx-2*k+1;
			int sy=yy-2*k+1;
			if(h[sx][sy][k]-h[sx][y-1][k]-h[x-1][sy][k]+h[x-1][y-1][k])
			{
				printf("%d\n",k*k*4);
				goto sleep;
			}
		}
		printf("0\n");
		sleep:;
	}
	return 0;
}
		
```


---

## 作者：Kelin (赞：5)

## 题意

给你一个$n\times m$的只包含四种颜色的网格。

$q$此询问，每次问一个矩阵中所包含的形如以下格式的$Logo$的最大面积

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1301E/b18bda37e952600d50a433d5d6d034271a8ea951.png)
$1\le n,m\le500,1\le q\le3\cdot10^5$


## [题解](https://blog.csdn.net/BeNoble_/article/details/104510129)

#### $1.$如何确定包含某个点的最大纯色正方形?

只考虑以点$(i,j)$为右下角的颜色为$p$的最大正方形的边长,设其为$L_{p,i,j}$.

则有:
$$
    L_{p,i,j}=\left\{
    \begin{aligned}
       & 0 & , color_{i,j}\neq p\\
       & \min\{L_{p,i-1,j},L_{p,i,j-1},L_{p,i-1,j-1}\}+1 & , color_{i,j}=p
    \end{aligned}\right.
$$

#### $2.$如何确定包含某个点的最大的$Logo$?

考虑红色方块的右下角$(i,j)$,则边长为$2k$的$Logo$合法的充要条件为:

$$L_{R,i,j}\ge k{\rm\ and\ }L_{G,i,j+k}\ge k{\rm\ and\ }L_{B,i+k,j+k}\ge k{\rm\ and\ }L_{Y,i+k,j}\ge k$$

当存在这样的$i,j,k$满足上述条件时,记$S_{k,i,j}=1$.

#### $3.$如何确定某个矩阵内的最大$Logo$?
先考虑如何判定边长为$2k$的$Logo$是否存在.

因为所记录的$(i,j)$为红色方块的右下角,故可以确定$(i,j)$的选点范围为子矩阵$:$

$$r_1-k+1\le i\le r_2-k,c_1-k+1\le j\le c_2-k$$

如果存在这样的$Logo$,也就是子矩阵中存在$S_{k,i,j}=1$,也就是子矩阵内$\sum S_{k,i,j}>0$.

可以发现$k$的有单调性的,故可以通过二分找到最大的$k$.

#### $4.$考虑另外一种思路

在第二步时记满足条件式的最大的$k$为$f_{i,j}$.

那么在第三步时的判定条件将变为$:$子矩阵中$\max f_{i,j}\ge k$.

---

总结下来题目体质就是求矩阵和或矩阵最大值.

具体方法为:

$a)$预处理前缀和,差分,时间复杂度$O(n^3+q\log n)$,空间复杂度$O(n^3)$.

```cpp
inline void Prepare(){
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            for(k=min(min(i,n-i),min(j,m-j));k>=1;--k){
                S[k][i][j]=S[k][i-1][j]+S[k][i][j-1]-S[k][i-1][j-1];
                if(L[0][i][j]>=k&&L[1][i][j+k]>=k&&L[2][i+k][j+k]>=k&&L[3][i+k][j]>=k){
                    for(int l=k;l>=1;--l)
                        S[l][i][j]=S[l][i-1][j]+S[l][i][j-1]-S[l][i-1][j-1]+1;
                    break;
                }
            }
}
inline bool Qry(int x1,int y1,int x2,int y2,int k){
    return S[k][x2][y2]-S[k][x1-1][y2]-S[k][x2][y1-1]+S[k][x1-1][y1-1];
}
```

$b)$二维$ST$表,时间复杂度$O(n^3+q\log n)$,空间复杂度$O(n^2\log^2n)$.

```cpp
inline void Prepare(){
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            for(k=min(min(i,n-i),min(j,m-j));k>=1;--k)
                if(L[0][i][j]>=k&&L[1][i][j+k]>=k&&L[2][i+k][j+k]>=k&&L[3][i+k][j]>=k){
                    f[0][0][i][j]=k;break;
                }
    for(int k=0;k<=Log[n];++k)
        fp(int l=0;l<=Log[m];++l)
            if(k||l)
                for(int i=1;i+(1<<k)-1<=n;++i)
                    for(int j=1;j+(1<<l)-1<=n;++j)
                        f[k][l][i][j]=l?max(f[k][l-1][i][j],f[k][l-1][i][j+(1<<(l-1))]):
                            max(f[k-1][l][i][j],f[k-1][l][i+(1<<(k-1))][j]);
}
inline bool Qry(int x1,int y1,int x2,int y2,int k){
    int Lx=Log[x2-x1+1],Ly=Log[y2-y1+1];
    return k<=max(max(f[Lx][Ly][x1][y1],f[Lx][Ly][x2-(1<<Lx)+1][y2-(1<<Ly)+1]),
            max(f[Lx][Ly][x2-(1<<Lx)+1][y1],f[Lx][Ly][x1][y2-(1<<Ly)+1]));
}
```

注意:参照点不止右下角一种选法,参照点选取的不同方案只影响子矩阵的范围和判定合法所选取的$L_{p,x,y}$.

---

## 作者：万弘 (赞：3)

~~第一眼：很像那个可持久化Trie的题，大概就是二维可持久化线段树的板子吧~~

醒醒，这不是ZJOI。

考虑如果矩形$(x1,y1,x2,y2)$中存在大小为$k\times k$的logo，若$k>2,$那么必然存在$(k-2)\times (k-2)$的logo，因此，问题的单调性是显然的，可以直接二分答案。

问题转化为，在矩形$(x1,y1,x2,y2)$中，是否存在大小为$k$的矩形。记为“简化询问”

一种比较直观的方法：（下面有比较巧妙的方法，可以跳过）  
记$f(i,j)$表示以$(i,j)$为右下角，最大的logo大小。显然大小为$2k\times 2k$的logo存在当且仅当矩形$(i-2k+1,j-2k+1,i,j)$的左上角全是红色（有$k\times k$个红色），右上角全是绿色（有$k\times k$个绿色）。。。。   
处理一下四种颜色的二维前缀和，即可$\mathcal O(1)$求得一个矩形中的某种颜色的数量，进而$\mathcal O(min(n,m))$的求出$f(i,j)$（$min(n,m)/2$是$k$的最大值）.  
然后，用二维ST表维护$f$,即可$\mathcal O(n\log n\times m\log m+nm\times min(n,m))$的时间内初始化，并在$\mathcal O(1)$的时间内回答“简化询问”。

更为巧妙的方法：  
记$exist(k,i,j)$表示以$(i,j)$为右下角，$(2k)\times (2k)$的logo是否存在。显然这当且仅当矩形$(i-2k+1,j-2k+1,i,j)$的左上角全是红色（有$k\times k$个红色），右上角全是绿色（有$k\times k$个绿色）。。。。  
处理一下四种颜色的二维前缀和，即可$\mathcal O(1)$求得一个矩形中的某种颜色的数量，进而$\mathcal O(nm\times min(n,m))$（$min(n,m)/2$是$k$的最大值）的时间内求出$exist(k,i,j).$

“简化询问”即为询问矩形$(x1,y1,x2,y2)$中是否存在某个$exist(k,i,j)>0$

对$exist(k,i,j)$求二维前缀和$f(k,i,j)$,即
$$f(k,i,j)=\sum_{x=1}^i\sum_{y=1}^j exist(k,x,y)=f(k,i-1,j)+f(k,i,j-1)-f(k,i-1,j-1)+exist(k,i,j)$$

即可$\mathcal O(1)$回答询问。  
贴一下后一种方法的代码：
```cpp
/**********/
#define MAXN 505
ll a[MAXN][MAXN],b[MAXN][MAXN],c[MAXN][MAXN],d[MAXN][MAXN],f[MAXN/2][MAXN][MAXN];//四种颜色的二维前缀和，以及f
ll s(ll sum[][MAXN],ll x1,ll y1,ll x2,ll y2)//在二维前缀和sum中查询(x1,y1,x2,y2)代表的子矩形和
{
	return sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];
}
int main()
{
	ll n=read(),m=read(),task=read();//task是询问数量
	for(ll i=1;i<=n;++i)//预处理颜色的前缀和
	{
		char cur;
		for(ll j=1;j<=m;++j)
		{
			std::cin>>cur;
			a[i][j]=a[i-1][j]+a[i][j-1]-a[i-1][j-1]+(cur=='R');
			b[i][j]=b[i-1][j]+b[i][j-1]-b[i-1][j-1]+(cur=='G');
			c[i][j]=c[i-1][j]+c[i][j-1]-c[i-1][j-1]+(cur=='Y');
			d[i][j]=d[i-1][j]+d[i][j-1]-d[i-1][j-1]+(cur=='B');
			//printf("%d ",a[i][j]);
		}
		//putchar('\n');
	}
	for(ll k=1;k<=250;++k)//预处理f
		for(ll i=k<<1;i<=n;++i)
			for(ll j=k<<1;j<=m;++j)
			{
				f[k][i][j]=f[k][i-1][j]+f[k][i][j-1]-f[k][i-1][j-1];
				ll sa=s(a,i-k-k+1,j-k-k+1,i-k,j-k),sb=s(b,i-k-k+1,j-k+1,i-k,j),sc=s(c,i-k+1,j-k-k+1,i,j-k),sd=s(d,i-k+1,j-k+1,i,j);
				if(sa==k*k && sb==k*k && sc==k*k && sd==k*k)++f[k][i][j];
			}
	while(task--)
	{
		ll x1=read(),y1=read(),x2=read(),y2=read();
		ll l=0,r=min((x2-x1+1)/2,(y2-y1+1)/2);
		while(l<r)//二分
		{
			ll mid=(l+r+1)>>1,tmp=s(f[mid],x1+mid+mid-1,y1+mid+mid-1,x2,y2);
			if(tmp>0)l=mid;//回答“简化询问”
			else r=mid-1;
		}
		printf("%d\n",l*l*4);
	}
	return 0;
}
```

---

## 作者：天梦 (赞：2)

### CF1301E Nanosoft

[链接](https://www.luogu.com.cn/problem/CF1301E)

这个题竟然没有人用二维 st 表过，这里写个题解。

以下，我们称一个 logo 最中间的那个点（不是方块）为关键点。大致思路如下：

1. 我们预处理出每一个点作为关键点时，最大方块边长除以 $2$ 为多少。这个可以二分。
2. 对于每一个询问，答案显然具有二分性，所以我们可以二分来做。

因为我们在第二次二分中需要 $O(1)$ 判断，所以我们需要提前预处理出二维 st 表。

第一次二分中的判断我们可以用二维前缀和优化到 $O(1)$。

代码：

```c++
#include<bits/stdc++.h>
#define dd double
#define ld long double
#define ll long long
#define uint unsigned int
#define ull unsigned long long
#define N 501
#define M number
using namespace std;

const int INF=0x3f3f3f3f;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

template<typename T> T Min(T a,T b){
    return a<b?a:b;
}

template<typename T> T Max(T a,T b){
    return a<b?b:a;
}

char s[N][N];
int sum[4][N][N],st[N][N][10][10],val[N][N],lg2[N],n,m,q;
//sum: 0 is red, 1 is green, 2 is blue, 3 is yellow
//st is the maxest

inline void build_st(){
    int maxx=Max(n,m);
    lg2[0]=-1;for(int i=1;i<=maxx;i++) lg2[i]=lg2[i/2]+1;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) st[i][j][0][0]=val[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=lg2[m];j++)
            for(int k=1;k+(1<<j)-1<=m;k++){
                st[i][k][0][j]=Max(st[i][k][0][j-1],st[i][k+(1<<(j-1))][0][j-1]);
            }
                
    for(int i=1;i<=lg2[n];i++)
        for(int j=0;j<=lg2[m];j++)
            for(int k=1;k+(1<<i)-1<=n;k++)
                for(int q=1;q+(1<<j)-1<=m;q++){
                    st[k][q][i][j]=Max(st[k][q][i-1][j],st[k+(1<<(i-1))][q][i-1][j]);
                }
                    
}

inline int query(int sx,int sy,int xx,int xy){
    int len1=lg2[xx-sx+1],len2=lg2[xy-sy+1];
    int maxx=-INF;
    maxx=Max(maxx,Max(st[sx][sy][len1][len2],st[xx-(1<<len1)+1][xy-(1<<len2)+1][len1][len2]));
    maxx=Max(maxx,Max(st[xx-(1<<len1)+1][sy][len1][len2],st[sx][xy-(1<<len2)+1][len1][len2]));
    return maxx;
}

inline bool check(int x,int y,int mid){
    int dx,dy,lx=x,ly=y;
    x=lx;y=ly;dx=x-mid,dy=y-mid;
    if(sum[0][x][y]+sum[0][dx][dy]-sum[0][x][dy]-sum[0][dx][y]!=mid*mid) return 0;
    x=lx+mid;y=ly;dx=x-mid;dy=y-mid;
    if(sum[3][x][y]+sum[3][dx][dy]-sum[3][x][dy]-sum[3][dx][y]!=mid*mid) return 0;
    x=lx;y=ly+mid;dx=x-mid;dy=y-mid;
    if(sum[1][x][y]+sum[1][dx][dy]-sum[1][x][dy]-sum[1][dx][y]!=mid*mid) return 0;
    x=lx+mid;y=ly+mid;dx=x-mid;dy=y-mid;
    if(sum[2][x][y]+sum[2][dx][dy]-sum[2][x][dy]-sum[2][dx][y]!=mid*mid) return 0;
    return 1;
}

inline int erfen(int x,int y){
    int l=0,r,res;
    r=Min(Min(x,y),Min(n-x,m-y));
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(x,y,mid)){res=mid;l=mid+1;}
        else r=mid-1;
    }
    return res;
}

inline bool AnsCheck(int sx,int sy,int xx,int xy,int mid){
    sx+=mid;sy+=mid;xx-=mid;xy-=mid;
    if(xx<sx||xy<sy) return 0;
    int maxx=query(sx,sy,xx,xy);
    if(maxx>=mid) return 1;
    return 0;
}

inline int BinaryAns(int sx,int sy,int xx,int xy){
    int l=0,r,res;
    r=Min(xx-sx,xy-sy);if(r&1) r--;
    while(l<=r){
        int mid=(l+r)>>1;
        if(AnsCheck(sx,sy,xx,xy,mid)){res=mid;l=mid+1;}
        else r=mid-1;
    }
    return res;
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);

    read(n);read(m);read(q);
    for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(s[i][j]=='R') sum[0][i][j]=1;
            else if(s[i][j]=='G') sum[1][i][j]=1;
            else if(s[i][j]=='B') sum[2][i][j]=1;
            else if(s[i][j]=='Y') sum[3][i][j]=1;
        }
    
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int k=0;k<=3;k++)
                sum[k][i][j]+=sum[k][i][j-1]+sum[k][i-1][j]-sum[k][i-1][j-1];
    
    for(int i=1;i<=n+1;i++)
        for(int j=1;j<=m+1;j++){
            val[i][j]=erfen(i-1,j-1);
        }
    n++;m++;

    // for(int i=1;i<=n;i++)
    //     for(int j=1;j<=m;j++)
    //         printf("i:%d j:%d val:%d\n",i,j,val[i][j]);

    build_st();
    while(q--){
        int sx,sy,xx,xy;read(sx);read(sy);read(xx);read(xy);xx++;xy++;
        int ans=BinaryAns(sx,sy,xx,xy);
        printf("%d\n",ans*ans*4);
    }
    return 0;
}
```



---

## 作者：cwfxlh (赞：1)

# [CF1301E](https://www.luogu.com.cn/problem/CF1301E)   

考虑两个 Nanosoft 图形之间的关系，要么同心，要么不交。于是这样的图形的数量级是 $n^2$ 级别的。枚举其中心即可做到 $O(n^2)$ 找到所有的 Nanosoft 图形。     

对于每一个询问，考虑枚举答案图形的边长，则对于边长为 $i$ 且在询问矩形 $(a,b,c,d)$ 内的图形，其左上角在一个矩形区域内。于是考虑按边长对所有的 Nanosoft 图形分类，将其位置记录在左上角，并做一个二维前缀和。查询的时候枚举边长，二维前缀和查询是否存在合法图形即可。复杂度 $O(n^3+nq)$，注意枚举长度的时候枚举偶数就可以了，否则可能被卡常。     

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int pre[253][503][503],n,m,q,R[503][503],G[503][503],Y[503][503],B[503][503],k1,k2,k3,k4,ans;
string s[503];
int getv(int lx,int ly,int rx,int ry,char c){
	lx=max(lx,1);
	ly=max(ly,1);
	rx=min(rx,n);
	ry=min(ry,m);
	if(c=='R')return R[rx][ry]-R[rx][ly-1]-R[lx-1][ry]+R[lx-1][ly-1];
	if(c=='G')return G[rx][ry]-G[rx][ly-1]-G[lx-1][ry]+G[lx-1][ly-1];
	if(c=='Y')return Y[rx][ry]-Y[rx][ly-1]-Y[lx-1][ry]+Y[lx-1][ly-1];
	if(c=='B')return B[rx][ry]-B[rx][ly-1]-B[lx-1][ry]+B[lx-1][ly-1];
	return 0;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		for(int j=1;j<=m;j++){
			R[i][j]=R[i-1][j]+R[i][j-1]-R[i-1][j-1];
			G[i][j]=G[i-1][j]+G[i][j-1]-G[i-1][j-1];
			Y[i][j]=Y[i-1][j]+Y[i][j-1]-Y[i-1][j-1];
			B[i][j]=B[i-1][j]+B[i][j-1]-B[i-1][j-1];
			if(s[i][j-1]=='R')R[i][j]++;
			if(s[i][j-1]=='G')G[i][j]++;
			if(s[i][j-1]=='Y')Y[i][j]++;
			if(s[i][j-1]=='B')B[i][j]++;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int len=1;;len++){
				if(getv(i-len+1,j-len+1,i,j,'R')!=len*len)break;
				if(getv(i-len+1,j+1,i,j+len,'G')!=len*len)break;
				if(getv(i+1,j-len+1,i+len,j,'Y')!=len*len)break;
				if(getv(i+1,j+1,i+len,j+len,'B')!=len*len)break;
				pre[len][i-len+1][j-len+1]++;
			}
		}
	}
	for(int i=1;i<=min(n,m)/2;i++){
		for(int j=1;j<=n;j++){
			for(int u=1;u<=m;u++)pre[i][j][u]+=pre[i][j-1][u]+pre[i][j][u-1]-pre[i][j-1][u-1];
		}
	}
	while(q--){
		cin>>k1>>k2>>k3>>k4;
		ans=0;
		for(int i=min(k3-k1+1,k4-k2+1)/2;i;i--){
			if(pre[i][k3-i*2+1][k4-i*2+1]-pre[i][k1-1][k4-i*2+1]-pre[i][k3-i*2+1][k2-1]+pre[i][k1-1][k2-1]!=0){
				ans=i*i*4;
				break;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Sai0511 (赞：1)

记 $E(l,i,j)$ 表示以 $(i,j)$ 为右下角，长度为 $2l$ 的 LOGO 是否存在，存在为 $1$，不存在为 $0$。这个函数显然可以通过对每种颜色做二位前缀和然后随便讨论一下四种颜色的坐标关系可以轻松的求出来。   
那么对与一个子矩阵来说，边长为 $2l$ 的 LOGO 是否存在也就是 $\sum E(l,i,j)$ 是否大于等于零。  
所以对 $E$ 再做一次二维前缀和就行了。  
同时又显然对于 $l'<l$，若长度为 $2l$ 的 LOGO 存在，则长度为 $2l'$ 的 LOGO 也一定存在，所以具备单调性。  
二分一下，没了。

---

## 作者：lsj2009 (赞：0)

难度：$2500$。

首先考虑一个性质：对于以 $(x,y)$ 为左上角的 logo 至多只有一个。

- 证明：假设以 $(x,y)$ 为左上角的 logo 有两个，那么就存在某个位置有两个颜色，显然不符。

那么我们可以考虑对于每个左上角 $(x,y)$ 暴力算出其 logo 边长的一半 $l$。

具体判断方法：首先在原矩阵分别提出 ``RGYB`` 的对应点，得到 $4$ 个 $01$ 矩阵，然后分别做二维前缀和，以 $(x,y)$ 为左上角、$l$ 为边长的矩阵是一个合法 logo 当且仅当：

1.  $(x,y)-(x+l-1,y+l-1)$ 全部是 ``R``。
2.  $(x,y+l)-(x+l-1,y+2l-1)$ 全部是 ``G``。
3.  $(x+l,y)-(x+2l-1,y+l-1)$ 全部是 ``Y``。
3.  $(x+l,y+l)-(x+2l-1,y+2l-1)$ 全部是 ``B``。

通过预处理好的二维前缀和可以轻松解决。复杂度 $\Theta(n^3)$。

然后再考虑一个性质：如果 $(x,y)-(x',y')$ 中存在半边长 $k$ 的 logo，那么一定存在半边长 $k-1$ 的 logo。

- 证明：考虑把半边长为 $k$ 的 logo 的外圈消掉。

既然有单调性，那么我们就可以考虑二分。现在问题在于如何快速计算 $(x,y)-(x',y')$ 中是否存在半边长 $k$ 的 logo。

我们考虑再建 $n$ 个 $01$ 矩阵，令第 $l$ 个矩阵的 $(x,y)$ 位置为 $0$。则 $(x,y)-(x',y')$ 中是否存在半边长 $l$ 的 logo 当且仅当在第 $k$ 个矩阵 $(x,y)-(x'-2l+1,y'-2l+1)$ 存在至少一个 $1$。

证明显然，因为如果 $(x'',y'')$ 在这个范围内且其为 $1$，则 $(x'',y'')-(x''+2l-1,y''+2l-1)$ 就是一个合法 logo 且其在 $(x,y)-(x',y')$ 范围内。

复杂度 $\Theta(n^3+q\log n)$。

---

## 作者：intel_core (赞：0)

看到题目里这个 $\text{logo}$ 的重点应该是这个正方形的中心。

取出这个中心之后四个角就是四个等大的正方形。

所以我们现在要想办法求出以 $(x,y)$ 为右下角的红色正方形边长的最大值（其它的颜色类似）。

先求出 $u_{i,j}$ 表示 $(i,j)$ 向上能延伸多少个红格，$l_{i,j}$ 表示 $(i,j)$ 往左能延伸多少个红格。

在 $O(n^2)$ 时间内有一车求法，就不说了。

记 $v_{i,j}$ 表示以 $(i,j)$ 为右下角的红色正方形边长的最大值。

从左往右，上到下扫一遍所有格子，求 ${v_{i,j}}$。

* 如果 $(i,j)$ 不为红色，显然 $v_{i,j}=0$。

* 否则 $v_{i,j}=\min \{v_{i-1,j-1}+1,l_{i,j},u_{i,j} \}$。

也同样可以在 $O(n^2)$ 内求出 $v$ 数组。

对四个颜色都做一遍类似的操作之后，就可以求出每个中心点最大的 $\text{logo}$ 边长了。

对于每个询问，二分答案。

现在 $\text{check}$ 一个答案 $x$，如果 $x$ 满足要求，那么可以确定 $\text{logo}$ 中心点的范围，查询在范围内的中心点有没有边长 $\ge x$ 的即可。

用前缀和数组 $f_{s,i,j}$ 表示矩形 $(1,1,i,j)$ 内有多少中心点的 $v \ge s$。

可以 $O(n^3)$ 处理出 $f$ 数组， $O(q \log n)$ 时间处理询问。

总复杂度 $O(n^3)$。

Tip ： 开 $f$ 数组的时候记得把 $s$ 那一维开成 $250$，否则会寄。

---

