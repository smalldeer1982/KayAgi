# Relay Race

## 题目描述

Furik and Rubik take part in a relay race. The race will be set up on a large square with the side of $ n $ meters. The given square is split into $ n×n $ cells (represented as unit squares), each cell has some number.

At the beginning of the race Furik stands in a cell with coordinates $ (1,1) $ , and Rubik stands in a cell with coordinates $ (n,n) $ . Right after the start Furik runs towards Rubik, besides, if Furik stands at a cell with coordinates $ (i,j) $ , then he can move to cell $ (i+1,j) $ or $ (i,j+1) $ . After Furik reaches Rubik, Rubik starts running from cell with coordinates $ (n,n) $ to cell with coordinates $ (1,1) $ . If Rubik stands in cell $ (i,j) $ , then he can move to cell $ (i-1,j) $ or $ (i,j-1) $ . Neither Furik, nor Rubik are allowed to go beyond the boundaries of the field; if a player goes beyond the boundaries, he will be disqualified.

To win the race, Furik and Rubik must earn as many points as possible. The number of points is the sum of numbers from the cells Furik and Rubik visited. Each cell counts only once in the sum.

Print the maximum number of points Furik and Rubik can earn on the relay race.

## 说明/提示

Comments to the second sample: The profitable path for Furik is: $ (1,1) $ , $ (1,2) $ , $ (2,2) $ , and for Rubik: $ (2,2) $ , $ (2,1) $ , $ (1,1) $ .

Comments to the third sample: The optimal path for Furik is: $ (1,1) $ , $ (1,2) $ , $ (1,3) $ , $ (2,3) $ , $ (3,3) $ , and for Rubik: $ (3,3) $ , $ (3,2) $ , $ (2,2) $ , $ (2,1) $ , $ (1,1) $ . The figure to the sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF213C/a92c8e717fa04d02a17d26f350f073f77ae6ad03.png) Furik's path is marked with yellow, and Rubik's path is marked with pink.

## 样例 #1

### 输入

```
1
5
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2
11 14
16 12
```

### 输出

```
53
```

## 样例 #3

### 输入

```
3
25 16 25
12 18 19
11 13 8
```

### 输出

```
136
```

# 题解

## 作者：珅肐 (赞：19)

题意：

输入一个$n*n$的矩形，$a_{i,j}$ 是这个位置的价值。现在要从左上角走到右下角再返回，每个价值只被计算一次，求最大价值和

解法：

题目可以转化为两人同时从左上角走到右下角

很容易想到设$f[i][j][k][l]$表示第一个人在$i,j$第二个人在$k,l$能得到的最大值。

转移方程很容易得到，但是内存显然不够。

我们考虑减少一维，设$f[i][j][k]$表示两个人都走了$i$步，第一个人在第$j$行，第二个人在第$k$行的最大值。我们发现此时两人的纵坐标是可以算出来的！
第一个人的列为$i-j+1$，第二个是$i-k+1$。

这样就做完了

### 完整代码奉上：
```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
#include<cstring>
using namespace std;
inline int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
int f[607][307][307];
int a[307][307];
int main(){
	int n=read();
	for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)a[i][j]=read();
	memset(f,-0x3f,sizeof f);
	f[1][1][1]=a[1][1];
	for(int i=2;i<=n+n-1;++i)
		for(int j=1;j<=n;++j)if(i-j+1>=1 && i-j+1<=n)
			for(int k=1;k<=n;++k)if(i-k+1>=1 && i-k+1<=n){
				int t;
				if(j!=k)t=a[j][i-j+1]+a[k][i-k+1];
				else t=a[j][i-j+1];
				f[i][j][k]=max(f[i][j][k],f[i-1][j][k]+t);
				f[i][j][k]=max(f[i][j][k],f[i-1][j-1][k-1]+t);
				f[i][j][k]=max(f[i][j][k],f[i-1][j-1][k]+t);
				f[i][j][k]=max(f[i][j][k],f[i-1][j][k-1]+t);
			}
	printf("%d\n",f[n+n-1][n][n]);
	return 0;
}
```


---

## 作者：Composite_Function (赞：11)

# 前置内容

这一道题是一道很经典的题，~~本人卡了好久才过~~，故发篇题解纪念一下。

建议在做之前做一下：
[P1002过河卒](https://www.luogu.com.cn/problem/P1002#submit)
[P1004方格取数](https://www.luogu.com.cn/problem/P1004)（本题弱化）
[P1006传纸条](https://www.luogu.com.cn/problem/P1006)（本题弱化）

- 注：P1004与P1006相同

------------

# 思路

我们发现本题中，回来再走一遍与直接走两遍**等价**。于是我们可以用数组 $ans_{i, j, k, l}$ 来记录当前一个走到 $(i, j)$ ，一个走到 $(k, l)$ 的**最优答案**，也就是**最大值**。

分析之后，我们很快就可以发现：难道这题和 P1004 以及 P1006 一样！？当然不是！这题是它们两题的**强化版**。 $n$ 的**数据范围**要大的很多，导致 $O(n ^ 4)$ **空间复杂度**算法点名被卡。

既然 $ans$ 数组数据量太大，就要想办法**降维**。可以发现 $\max(i + j - 1)=\max(k + l - 1) = 2 * n + 1$，何必**再花一维来储存**呢？于是可以想出 $O(n ^ 3)$ **空间复杂度**算法——用数组 $ans_(i, j, k)$ 来记录走了 $i$ 步，一个走到第 $j$ 行，一个走到第 $k$ 行。

完结撒花！ (〃￣︶￣)人(￣︶￣〃) 

------------

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=305;
int n,a[N][N],f[2*N][N][N];//我就是在定义数组上挂了……
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>a[i][j];
    memset(f,-0x3f,sizeof(f));//数据范围中声明 a 可能为负
    f[1][1][1]=a[1][1];
    //------预备————走！------//
	for(int i=2;i<=2*n-1;i++)
		for(int j=1;j<=n;j++)
            if(i-j+1>=1&&i-j+1<=n)//防止越界
			    for(int k=1;k<=n;k++)
                    if(i-k+1>=1&&i-k+1<=n){//防止越界
                        int t;//两个同时取在一个地方只加一次
        				if(j!=k)t=a[j][i-j+1]+a[k][i-k+1];
        				else t=a[j][i-j+1];
        				f[i][j][k]=max(f[i][j][k],f[i-1][j][k]+t);
        				f[i][j][k]=max(f[i][j][k],f[i-1][j-1][k-1]+t);
        				f[i][j][k]=max(f[i][j][k],f[i-1][j-1][k]+t);
        				f[i][j][k]=max(f[i][j][k],f[i-1][j][k-1]+t);
                    }
    cout<<f[2*n-1][n][n]<<endl;
    return 0;//功德圆满
}//Fgx出品，勿抄
```

千山万水总是情，给个点赞行不行~~

---

## 作者：Garbage_fish (赞：5)

### 题意分析

从 $(1,1)$ 走到 $(n,n)$，再从 $(n,n)$ 走到 $(1,1)$，在每个点最多只计算一次的前提下，让走过的点的总和最大。

### WA 做法：

一开始我想的是先二维 dp 一次，使走过的价值最大，将走过的点的价值标记为 $0$，再走第二次，然后就 [**WA**](https://www.luogu.com.cn/record/121198622) 了，原因是这样不一定是最优解，如下图所示，这是二维 dp 的走法（红色表示第一条路径，蓝色表示第二条路径，紫色表示重叠部分，本图仅作举例，并非对应题目格式，空白部分表示 $0$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/7i2qidb4.png "")

而这是正确的走法：

![](https://cdn.luogu.com.cn/upload/image_hosting/j63s4ohi.png)

所以，需要同时处理两条路径的走法。

### MLE 做法（可优化）：

首先，为了方便，把第二条反着走的路径也转换为 $(1,1)$ 到 $(n,n)$ 的路径。

因为题目限制了只能往下走或往右走，因此无论何种路径，最多经过 $2\times n-1$ 步就可以到达终点，也就是说两条路径走的步数是一致的。

所以就可以考虑用 $f_{i,xa,ya,xb,yb}$ 表示用 $i$ 步使第一条路径走到 $(xa,ya)$，第二条路径走到 $(xb,yb)$ 的最大价值和，得到状态转移方程为：

$$
f_{i,xa,ya,xb,yb}=a_{xa,ya}+a_{xb,yb}+\max\left\{\begin{matrix}f_{i-1,xa,ya-1,xb,yb-1}
 \\f_{i-1,xa,ya-1,xb-1,yb}
 \\f_{i-1,xa-1,ya,xb,yb-1}
 \\f_{i-1,xa-1,ya,xb-1,yb}
\end{matrix}\right.
$$

显然的，开五维数组会 MLE，所以需要优化。

### AC 做法（由上面做法优化而来）：

因为上面提到步数是固定的，所以可以用步数 $i$ 减去坐标 $x$ 再加上 $1$ 得到坐标 $y$，这样就能优化成一个三维数组，$f_{i,xa,xb}$，状态转移方程也被优化成了：

$$
f_{i,xa,xb}=a_{xa,ya}+a_{xb,yb}+\max\left\{\begin{matrix}f_{i-1,xa,xb}
 \\f_{i-1,xa,xb-1}
 \\f_{i-1,xa-1,xb}
 \\f_{i-1,xa-1,xb-1}
\end{matrix}\right.
$$

于是这道题就被圆满的解决了。

**[AC](https://www.luogu.com.cn/record/121284061) Code:**

```cpp
#include <bits/stdc++.h>
using namespace std;
void fread(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}
const int N=301,oo=0x7fffffff;
int n,a[N][N],f[2*N][N][N];
signed main(){
	fread();
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
		}
	}
	for(int i=0;i<=2*n;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<=n;k++){
				f[i][j][k]=-oo;
			}
		}
	}
	f[1][1][1]=a[1][1];
	for(int i=2;i<=2*n-1;i++){
		for(int xa=1;xa<=i and xa<=n;xa++){
			for(int xb=1;xb<=i and xb<=n;xb++){
				int ya=i-xa+1;
				int yb=i-xb+1;
				int sum=a[xa][ya];
				if(xa!=xb)sum+=a[xb][yb];
				f[i][xa][xb]=max(f[i-1][xa][xb],max(f[i-1][xa][xb-1],max(f[i-1][xa-1][xb],f[i-1][xa-1][xb-1])))+sum;
			}
		}
	}
	cout<<f[2*n-1][n][n];
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：3)

这是一道好题。

[题目链接](https://www.luogu.com.cn/problem/CF213C)
## 思路
我原本的思路是把两条路径分开考虑，使用一个四维数组 $f_{i,j,k,l}$ 表示第一条从 ${1,1}$ 到 ${i,j}$ 的路径，第二条从 ${1,1}$ 到 ${k,l}$ 的路径可以取到的最大值。

但这么做的时间复杂度显然是 $O(n^4)$ 的，对于 $n=300$ 的数据，$300^4=8.1 \times 10^9$，虽然 $\verb!CF!$ 的神机也许可以跑过，但空间复杂度 $O(n^4)$ 显然炸了，所以我们考虑优化空间。

我们可以两条路径同时考虑，这样我们只要记录他们两个人共同走过的步数就好了，这样我们的状态就需要稍微变化一下，变成 $f_{i,j,k}$ 表示走 $i$ 步，第一条路径走到了第 $j$ 行，第二条路径走到了第 $k$ 行，我们惊奇地发现这时两条路径结尾的纵坐标是显然可以表示出来的，也就是对应了我们原来状态的 $f_{j,i-j+1,k,i-k+1}$。这样我们就成功地把空间复杂度降到了 $O(n^3)$，时间复杂度也顺便降到了 $O(n^3)$，显然可以通过本题。

## 代码
```cpp
#include<bits/stdc++.h>
#define rint register int
using namespace std;
int const N=3e2+10;
int a[N][N],f[N<<1][N][N];//这里千万不能开 long long，不然会 MLE
signed main(){
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for (rint i=1;i<=n;++i)
        for (rint j=1;j<=n;++j)
            cin>>a[i][j];
    memset(f,-0x3f,sizeof(f));
    f[1][1][1]=a[1][1];
    int maxn=(n<<1)-1;
    for (rint i=2;i<=maxn;++i)
        for (rint j=1;j<=n;++j){
            if (i-j+1<1 || i-j+1>n) continue;
            for (rint k=1;k<=n;++k){
                if (i-k+1<1 || i-k+1>n) continue;
                int sj=i-j+1,sk=i-k+1;//把两条路径的终点坐标算出来
                int p=a[j][sj];
                if (sj!=sk && j!=k) p+=a[k][sk];
                f[i][j][k]=max(f[i][j][k],
                           max(f[i-1][j][k]+p,
                           max(f[i-1][j-1][k-1]+p,
                           max(f[i-1][j-1][k]+p,
                               f[i-1][j][k-1]+p))));//转移
            }
        }
    cout<<f[maxn][n][n]<<'\n';
    return 0;
}
```


---

## 作者：MiPloRAs_3316 (赞：3)

[可能更好的食用体验](/blog/560595/solution-cf213c) $|$ 
[题目传送门](/problem/CF213C)


---
$\large{\textbf{\textsf{\color{RoyalBlue}{Meaning 题意}}}}$

输入一个 $n\times n$ 的矩形，每个 $a_{i,j}$ 是这个位置的价值。现在要从左上角走到右下角再返回，每个价值只被计算一次，求最大价值和（$1\le n \le 300,-1000\le a_{i,j}\le 1000$）。

---
$\large{\textbf{\textsf{\color{RoyalBlue}{Analysis 思路}}}}$

刚看题的时候，我们会想到跑 $2$ 次 dp，也就是第二次 dp 是基于第一次 dp 后的状态来进行的。

但这其实是错的，以下面这个样例为反例。
```txt
4
2 1 0 0
4 3 0 0
4 3 4 2
1 0 7 5
```

按照两次 dp 的思路，我们会这样跑：

![awa](https://cdn.luogu.com.cn/upload/image_hosting/oskt3r7p.png)

此时最大价值和是 $2+4+4+3+4+7+5+2+0+0+3+1+0=35$。

但如果这样跑：

![qwq](https://cdn.luogu.com.cn/upload/image_hosting/qhp9rhnr.png)

最大价值和就会变成：$2+4+4+1+0+7+5+2+4+3+3+1+0=36$。

显然第 $2$ 种解法的价值更大。

举出反例后，证明了两次 dp 的贪心思路的错误性，那么正解是什么呢？

回到图中，就会发现一红一蓝两条线似乎是同时行动的，而且长度都是 $2n-2$，那能不能看成小 $A$ 和小 $B$ 同时从 $(1,1)$ 走到 $(n,n)$？

状态表示：
$f(x,y,xx,yy)$ 表示 $A$ 位于 $(x,y)$，$B$ 位于 $(xx,yy)$ 时两条路径获得的最大价值和。

状态转移方程：

$$f(x,y,xx,yy)=\min
\begin{Bmatrix}
f(x-1,y,xx-1,yy)\\
f(x-1,y,xx,yy-1)\\
f(x,y-1,xx-1,yy)\\
f(x,y-1,xx,yy-1)
\end{Bmatrix}+a_{x,y}+a_{xx,yy}$$

PS：如果 $(x,y)$ 和 $(xx,yy)$ 重合，则要在上式的基础上减去一个 $a_{x,y}$。（每个价值只被计算一次。）

但是，$n\le 300$，四重循环时空复杂度都会炸，所以需要优化。

---
前文提到，**一红一蓝两条线是同时行动的**，也就是说**路径长度一致**，所以知道路径长度和其中一个维度的坐标，就可以求出另一个维度的坐标。

所以 $f(x,y,xx,yy)$ 这样繁琐的状态表示可以简化成 $f(k,x,xx)$（$k$ 表示路径长度）。

补充：路径长度为 $k$，行号为 $x$ 时，列号为 $k-x+2$。

再写一遍状态转移方程：

$$f(k,x,xx)=\min
\begin{Bmatrix}
f(k-1,x-1,xx-1)\\
f(k-1,x-1,xx)\\
f(k-1,x,xx-1)\\
f(k-1,x,xx)\\
\end{Bmatrix}+a_{x,y}+a_{xx,yy}$$

~~我试图把第一维滚动掉，失败了。（有大佬知道怎么滚可以教教我吗 qwq。）~~

---
$\large{\textbf{\textsf{\color{RoyalBlue}{Code 代码}}}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define _max(a,b,c,d) max(max((a),(b)),max((c),(d)))
int n,a[305][305],f[605][305][305];
signed main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			scanf("%d",&a[i][j]);
	memset(f,-0x3f,sizeof f);
	f[0][1][1]=a[1][1];
	for(int i=1; i<=2*n-2; i++)
	{
		for(int x=1; x<=n; x++)
		{
			int y=i-x+2;
			if(y<1) continue;
			for(int xx=1; xx<=n; xx++)
			{
				int yy=i-xx+2;
				if(yy<1) continue;
				f[i][x][xx]=INT_MIN;
				f[i][x][xx]=_max(f[i-1][x][xx-1],f[i-1][x-1][xx],f[i-1][x][xx],f[i-1][x-1][xx-1])+a[x][y];
				if(xx!=x || yy!=y) f[i][x][xx]+=a[xx][yy];
			}
		}
	}
	cout<<f[n+n-2][n][n];
	return 0;
}
```

---

## 作者：JWRuixi (赞：3)

其实就是升级版 [方格取数](https://www.luogu.com.cn/problem/P1004)。

- 分析

先考虑朴素做法，设 $f_{i, j, p, q}$，为两人在 $(i, j)$，$(p, q)$ 的最大值，时空复杂度 $O(n^4)$。

怎样缩小这个值呢？

观察到可以考虑让连个人一起走，同时取，即可省下一维。

即设 $f_{i,j,p}$ 为两人在 $(i, j)$，$(p, i + j - q)$ 的最大值。

$$f_{i, j, p} = \max(f_{i-1,j,p},f_{i-1,j,p-1},f_{i,j-1,p},f_{i,j-1,p-1})+a_{i,j}+a_{p,i+j-p}$$

注意如果 $i$ 和 $p$ 相等，即走到同一格，就要减去 $a_{i,j}$。

初始值赋成两倍 $a_{1, 1}$，来抵消第一次的效果。

- code

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace IO {
	char ibuf[(1 << 20) + 1], *iS, *iT;
#if ONLINE_JUDGE
#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
#else
#define gh() getchar()
#endif
#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9')   t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn = 350, inf = 1e9;
int n, a[maxn][maxn], f[maxn][maxn][maxn];

int main () {
	n = read();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			a[i][j] = read();
		}
	}
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) for (int k = 1; k <= n; k++) f[i][j][k] = -inf;//可能有负数
	f[1][1][1] = a[1][1] << 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int p = 1; p <= n; p++) {
				int q = i + j - p;
				if (q <= 0) break;
				if (i > 1 && p > 1) f[i][j][p] = max(f[i][j][p], f[i - 1][j][p - 1] + a[i][j] + a[p][q]);
				if (i > 1 && q > 1) f[i][j][p] = max(f[i][j][p], f[i - 1][j][p] + a[i][j] + a[p][q]);
				if (j > 1 && p > 1) f[i][j][p] = max(f[i][j][p], f[i][j - 1][p - 1] + a[i][j] + a[p][q]);
				if (j > 1 && q > 1) f[i][j][p] = max(f[i][j][p], f[i][j - 1][p] + a[i][j] + a[p][q]);//记得判越界
				
				if (i == p) f[i][j][p] -= a[i][j];//走到同一格
			}
		}
	}
	write(f[n][n][n]);
}
```

---

## 作者：cjrqwq (赞：1)

### 题意

有 $n\times n$ 的矩形，价值为 $a_{i,j}$。  
现在你要从 $a_{1,1}$ ，通过移动到 $a_{i,j+1},a_{i+1,j}$ 的方式，走到 $a_{n,n}$。  
再通过移动到 $a_{i,j-1},a_{i-1,j}$ 的方式，回去 $a_{1,1}$。定义价值为路径上 $a_{i,j}$ 的和，重复走过的路径只计算一次。

问最大的价值是多少？

---
### 思路
#### 错解

首先，猜个结论：先从 $1,1$ 跑 dp。然后按路径将 $a_i$ 设为 $0$。在从 $a_{n,n}$ 跑 dp。

但是这样做是错误的。
```
3
5 5 1
0 5 -2
5 -4 -2
```
dp 会跑出来 $11+1$ 的结果。但是正解却是 $4+10$。

dp：

$(1,1)\to(1,2)\to(2,2)\to(2,3)\to(3,3)\to(3,2)\to(3,1)\to(2,1)\to(1,1)$  
$5+5+5-2-2=11,0-4+5+0+0=1$

正解：

$(1,1)\to(2,1)\to(3,1)\to(3,2)\to(3,3)\to(3,2)\to(2,2)\to(2,1)\to(1.1)$  
$5+0+5-4-2=4,0+0+5+5+0=10$

---
#### 动态规划
此时我们就举出了反例。还是老实用朴素的 dp 吧。本题可以理解为**有两个人从** $(1,1)$ **走到** $(n,n)$。那就可以将状态设为 $dp_{x,y,xx,yy}$。分别是第一个人的坐标，第二个人的坐标。  
我们使两个人一起走，如果两人坐标相同，就只算一遍。这个时候的状态转移方程即让两个人各走一步：
$$dp_{x,y,xx,yy}=\max\{dp_{x-1,y,xx-1,yy},dp_{x-1,y,xx,yy-1},dp_{x,y-1,xx-1,yy},dp_{x,y-1,xx,yy-1}\}$$

但是时空复杂度：$\Theta (n^4)$。

#### 优化
考虑优化，dp 优化的本质就是削减**无用状态**与重复转移。我们注意到，只有 $x+y=xx+yy$ 的状态是有意义的，因为如果不同，说明不符合**两个人一起走**的定义。

假如两个人同时走，那么他们的**坐标和就会相同**。设坐标和为 $s$。那么枚举 $s,x,xx$。$y,yy$ 就可以算出来了。此时可设 $dp_{s,x,xx}$ 为坐标和为 $s$，第一个人在 $(x,s-x)$，第二个人在 $(xx,s-xx)$。

接下来思考状态转移方程，其实就是由朴素版推出来的：

$$dp_{s,x,xx}=\max\{dp_{s-1,x-1,xx},dp_{s-1,x,xx-1},dp_{s-1,x-1,xx-1},dp_{s-1,x,xx}\}$$

复杂度就变成 $\Theta(n^3)$ 。

---
#### 初始值
在开始的时候，我们要将所有状态设为**不可达**。但是 $dp_{2,1,1}$ 的状态是确定的。$dp_{2,1,1}\gets a_{1,1}$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e2+1;
int a[N][N],dp[N<<1][N][N],n;
int main() {
	memset(dp,-0x3f,sizeof dp);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			cin>>a[i][j];
		}
	}
	dp[2][1][1]=a[1][1];
	for(int i=3;i<=n<<1;i++) {
		for(int j=1;j<=n;j++) {if(i-j<1||i-j>n) continue;//枚举 x；y为 i-x+1,不能越界
			for(int k=1;k<=n;k++) {if(i-k<1||i-k>n) continue;//同上 
				int t=0;
				if(j==k) t=a[j][i-j];//相同只算一个 
				else t=a[j][i-j]+a[k][i-k];
				dp[i][j][k]=max(max(dp[i-1][j-1][k],dp[i-1][j][k-1]),max(dp[i-1][j][k],dp[i-1][j-1][k-1]))+t;
			}
		}
	}
	cout<<dp[n<<1][n][n];
	return 0;
}
```

---

## 作者：541forever (赞：0)

首先，发现问题等价于维护两个点从左上角走到右下角的路径并的价值和，考虑暴力 dp，设 $f_{i,j,k,l}$ 表示第一个点走到了 $(i,j)$，第二个点走到了 $(k,l)$，直接这样做的复杂度是 $O(n^4)$，不难发现，在没一步时的状态数实际上是 $O(n)$ 级别的且都在一条对角线上，那么，考虑直接枚举当前是第几步，两条路线分别走到的位置的纵坐标，横坐标可以直接算出来，直接转移即可。可能边界情况有些多，具体实现可以看代码。

[Code](https://codeforces.com/contest/213/submission/202732748)

---

## 作者：D2T1 (赞：0)

~~？~~

传纸条，但是 $O(n^4)$ 过不了。

考虑 $O(n^4)$ 做法的状态：$f_{i,j,k,l}$ 表示两个人分别走到 $(i,j),(k,l)$ 时的最优方案。

很显然两个人走的步数都相同，所以 $i+j=k+l$。所以四维实际上有一维可以去掉。

那既然去掉一维，那就再定义的好看一点：$f_{i,j,k}$ 表示两个人走到离 $(1,1)$ 点距离 $i$，横坐标分别为 $j,k$ 的最优方案。距离表示两个方格最短路上方格数 $+1$，这里 $+1$ 可以更方便的处理坐标的问题。

转移：

$$
f_{i,j,k}=\max(f_{i-1,j,k},f_{i-1,j,k-1},f_{i-1,j-1,k},f_{i-1,j-1,k-1})+
\begin{cases}
a_{j,i-j}&if&j=k\\
a_{j,i-j}+a_{k,i-k}&if&j\neq k
\end{cases}
$$

初始 $f_{2,1,1}=a_{1,1}$，其他地方都为 $-\inf$。答案取 $f_{2n,n,n}$。

```cpp
//CF213C
#include <bits/stdc++.h>
using namespace std;

const int N = 310;
int n, a[N][N], f[N*2][N][N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++ i){
		for(int j = 1; j <= n; ++ j){
			scanf("%d", &a[i][j]);
		}
	}
	memset(f, 0xcf, sizeof(f));
	f[2][1][1] = a[1][1];
	for(int i = 3; i <= n + n; ++ i){
		for(int j = 1; j <= n; ++ j){
			for(int k = 1; k <= n; ++ k){
				if(j == k){
					f[i][j][k] = max(max(f[i-1][j][k], f[i-1][j-1][k-1]), 
									 max(f[i-1][j-1][k], f[i-1][j][k-1])) + a[j][i-j];
				} else {
					f[i][j][k] = max(max(f[i-1][j][k], f[i-1][j-1][k-1]), 
									 max(f[i-1][j-1][k], f[i-1][j][k-1])) + a[j][i-j] + a[k][i-k];
				}
			}
		}
	}
	printf("%d\n", f[n+n][n][n]);
	return 0;
}
```

---

## 作者：Fhr123456 (赞：0)

[题目传送门](https://codeforces.com/problemset/problem/213/C)
## 题意
输入一个 $n\times n$ 的矩形，每个 $a_{i,j}$ 是这个位置的价值，现从左上角走到右下角再返回，每个位置的值只能计算一次，求最大价值和。
## 思路
跟方格取数差不多，从左上角走到右下角再返回和从左上角走到右下角两次是等价的。这题明显是一个 dp，最暴力的做法是四重循环枚举第一次走的 $i,j$ 和第二次走的 $i,j$。但是 $n \leq 300$，时间和空间都不允许，于是考虑优化。

设 $dp_{l,i,j}$ 表示横坐标和纵坐标之和为 $l$，也就是走了 $l-1$ 个格子，第一次的横坐标为 $i_1$，第二次的横坐标为 $i_2$，两次的纵坐标 $j_1,j_2$ 分别为 $l-i_1$ 和 $l-i_2$。然后就可以进行转移了，每次只能向右或向下走一格，所以转移方程就为
$$dp_{i1,i2}=\max(dp_{l-1,i_1-1,i_2},dp_{l-1,i_1,i_2-1},dp_{l-1,i_1-1,i_2-1},dp_{l-1,i_1,i_2})+a_{i_1,l-i_1}+a_{i_2,l-i_2}$$
最后注意两次走到同一个格子上时这个格子的价值只能计算一次，特判一下就好了。
## AC代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
inline int read(){
	int f=1,sum=0;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		sum=sum*10+ch-'0';
		ch=getchar();
	}
	return f*sum;
}
inline void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n,mp[304][304],dp[604][304][304];
int cal(int l,int i1,int j1,int i2,int j2){//转移
	int _1=dp[l-1][i1-1][i2-1];
	int _2=dp[l-1][i1-1][i2];
	int _3=dp[l-1][i1][i2-1];
	int _4=dp[l-1][i1][i2];
	if(i1==i2&&j1==j2) return max(_1,max(_2,max(_3,_4)))+mp[i1][j1];
	return max(_1,max(_2,max(_3,_4)))+mp[i1][j1]+mp[i2][j2];
}
int main(){
	n=read();
	memset(dp,-0x3f,sizeof(dp));//因为有负数所以要初始化为负无穷
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			mp[i][j]=read();
		}
	}
	dp[1][0][0]=dp[1][1][0]=dp[1][0][1]=dp[1][1][1]=0;//初始化
	for(int l=1;l<=2*n;l++){
		for(int i1=1;i1<=n;i1++){
			for(int i2=1;i2<=n;i2++){
				int j1=l-i1,j2=l-i2;
				if(j1<=0||j2<=0) break;
				dp[l][i1][i2]=max(dp[l][i1][i2],cal(l,i1,j1,i2,j2));
			}
		}
	}
	printf("%d",dp[2*n][n][n]);
	return 0;
}
```


---

## 作者：lgswdn_SA (赞：0)

题目中说 Furik 和 Rubik 走的是相反的道路。其实我们大不必这么复杂，因为如果 Rukik 是从 $1,1$ 走到 $n,n$ 那也一样。所以两个人相当于同时从 $1,1$ 走到 $n,n$。

一个很显然的发现：两人同时走到一个格子只会在两人步数相同时发生。所以我们可以采用 [传纸条](https://www.luogu.com.cn/problem/P1006) 这题同样的套路，写出状态 $f(k,i,j)$ 表示两人走了 $k$ 步，第一个人走到了第 $i$ 行，第二个人走到了第 $j$ 行的最大价值和。很明显，这时，第一个人在 $(i,j-i)$，第二个人在 $(j,k-j)$，于是我们看一下是否符合要求，然后计算一下价值即可。决策为枚举下一步两人往哪里走。

$f(k,i,j)\to f(k+1,i+1,j), f(k+1,i,j+1),f(k+1,i,j),f(k+1,i+1,j+1)$。

（为了方便，程序中定义为走到这两个点，不算上这两个点所获得的价值的最大值）

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=309;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,a[N][N],f[N<<1][N][N];

void upd(int &x,int y) {x=max(x,y);}

int main() {
	n=read();
	rep(i,1,n) rep(j,1,n) a[i][j]=read();
	memset(f,-0x3f,sizeof(f));
	f[1][1][1]=0;
	rep(k,1,2*n-1) {
		rep(i,max(1,1+k-n),min(k,n)) {
			rep(j,max(1,1+k-n),min(k,n)) {
				int val=(i==j?a[i][k-i+1]:a[i][k-i+1]+a[j][k-j+1])+f[k][i][j];
				upd(f[k+1][i][j],val),
				upd(f[k+1][i+1][j],val),
				upd(f[k+1][i][j+1],val),
				upd(f[k+1][i+1][j+1],val);
			}
		}
	}
	printf("%d\n",f[2*n-1][n][n]+a[n][n]);
	return 0;
} 
```

---

## 作者：Aryper (赞：0)

Relay Race

高级版的方格取数，多了负数的处理以及更大的数据。

可以看做从起点开始走两次到终点。

最暴力的方法是定义状态 $f_i,_j,_p,_q$ 表示第一次走到 $(i,j)$ 第二次走到 $(p,q)$ 的最大得分。

易得转移方程：

$$f_i,_j,_p,_q=\max\begin{cases}f_{i-1},_j,_{p-1},_q\\f_{i-1},_j,_p,_{q-1}\\f_i,_{j-1},_{p-1},_q\\f_i,_{j-1},_p,_{q-1}\end{cases}+a_i,_j+a_p,_q$$

如果 $(i,j)$ 和 $(p,q)$ 重合的话只计算一次。

当然我也没试这种方法，第一它的时间复杂度为 $O(n^4)$ ，第二它的内存直接爆了(本机运行都开不了8.1e9个long long) 。

所以我们优化一下状态，很容易发现如果两次走了相同的步数，那么到达坐标的横纵坐标之和相等。

那么定义状态 $f_i,_j,_k$ 表示第一次走到 $(i,j)$ ，第二次走到第 $k$ 行的最大得分。

显然第二次走的纵坐标就是 $i+j-k$ 。

那么转移方程：

$$f_i,_j,_k=\max\begin{cases}f_{i-1},_j,_k\\f_{i-1},_j,_{k-1}\\f_i,_{j-1},_k\\f_i,_{j-1},_{k-1}\end{cases}+a_i,_j+a_k,_{i+j-k}$$

同样，如果 $(i,j)$ 和 $(k,i+j-k)$ 重合则只计算一次。

时间复杂度 $O(n^3)$ 。

当然有一些更加优秀的做法，不过咕咕咕咕咕。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstring>
#include<vector>
#include<bitset>
#define ll long long
using namespace std;

ll n;

ll a[305][305],f[305][305][305];

inline ll read() {
	ll ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') {ret=(ret<<3)+(ret<<1)+ch-'0';ch=getchar();}
	return ret*f;
}

void write(ll x) {
	if(x<0) {x=-x;putchar('-');}
	if(x>9) write(x/10);
	putchar(x%10+48);
}

int main() {
	
	n=read();
	
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			a[i][j]=read();
		}
	}
	
	memset(f,-0x3f,sizeof(f));f[1][1][1]=a[1][1]+a[1][1];
	
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			for(int k=1;k<=n&&k<=i+j-1;k++) {
				if(i-1>=1&&k-1>=1) f[i][j][k]=max(f[i][j][k],f[i-1][j][k-1]+a[i][j]+a[k][i+j-k]);
				if(i-1>=1&&i+j-k-1>=1) f[i][j][k]=max(f[i][j][k],f[i-1][j][k]+a[i][j]+a[k][i+j-k]);
				if(j-1>=1&&k-1>=1) f[i][j][k]=max(f[i][j][k],f[i][j-1][k-1]+a[i][j]+a[k][i+j-k]);
				if(j-1>=1&&i+j-k-1>=1) f[i][j][k]=max(f[i][j][k],f[i][j-1][k]+a[i][j]+a[k][i+j-k]);
				if(i==k&&j==i+j-k) f[i][j][k]-=a[i][j];
			}
		}
	}
	
	write(f[n][n][n]);
	
	return 0;
}
```


---

