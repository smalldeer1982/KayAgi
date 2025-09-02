# Road to 1600

## 题目描述

Egor wants to achieve a rating of 1600 points on the well-known chess portal ChessForces and he needs your help!

Before you start solving the problem, Egor wants to remind you how the chess pieces move. Chess rook moves along straight lines up and down, left and right, as many squares as it wants. And when it wants, it can stop. The queen walks in all directions vertically and diagonally at any distance. You can see the examples below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1333E/73b9d5dec0fb48461c487105879fa605baff377a.png)To reach the goal, Egor should research the next topic:

There is an $ N \times N $ board. Each cell of the board has a number from $ 1 $ to $ N ^ 2 $ in it and numbers in all cells are distinct.

In the beginning, some chess figure stands in the cell with the number $ 1 $ . Note that this cell is already considered as visited. After that every move is determined by the following rules:

1. Among all not visited yet cells to which the figure can get in one move, it goes to the cell that has minimal number.
2. If all accessible cells were already visited and some cells are not yet visited, then the figure is teleported to the not visited cell that has minimal number. If this step happens, the piece pays a fee of $ 1 $ vun.
3. If all cells are already visited, the process is stopped.

Egor should find an $ N \times N $ board on which the rook pays strictly less vuns than the queen during the round with this numbering. Help him to find such $ N \times N $ numbered board, or tell that it doesn't exist.

## 说明/提示

In case we have $ 1 \times 1 $ board, both rook and queen do not have a chance to pay fees.

In second sample rook goes through cells $ 1 \to 3 \to 4 \to 6 \to 9 \to 5 \to 7 \to 13 \to 2 \to 8 \to 16 \to 11 \to 10 \to 12 \to 15 \to \textbf{(1 vun)} \to 14 $ .

Queen goes through $ 1 \to 3 \to 4 \to 2 \to 5 \to 6 \to 9 \to 7 \to 13 \to 8 \to 11 \to 10 \to 12 \to 15 \to \textbf{(1 vun)} \to 14 \to \textbf{(1 vun)} \to 16 $ .

As a result rook pays 1 vun and queen pays 2 vuns.

## 样例 #1

### 输入

```
1```

### 输出

```
-1```

## 样例 #2

### 输入

```
4```

### 输出

```
4 3 6 12 
7 5 9 15 
14 1 11 10 
13 8 16 2```

# 题解

## 作者：syksykCCC (赞：4)

首先发现 $n \le 2$ 是没法做的。

然后 $n = 3$ 可以暴力算一下，比如下面这种方案就是合法的：

![](https://i.loli.net/2020/04/10/42PmAuLKWehQbxg.png)

那么，如果 $n > 3$，能不能转化一下变成 $n = 3$ 的问题呢？

一种方法是使得外面的位置都不造成作用，只有最左上角的九格才发挥作用。

也就是我们只要确保两个棋子都能恰好将外面的绕完，然后进入最左上角的九宫格就行了，比如下面这样就是 $n = 5$ 的构造方法：

$$\begin{matrix} \color{red} 1 \color{blue} + 16 & \color{red} 7 \color{blue} + 16 & \color{red} 9 \color{blue} + 16 & 7 \to & 8 \downarrow \\ \color{red} 3 \color{blue} + 16 & \color{red} 2 \color{blue} + 16 & \color{red} 5 \color{blue} + 16 & 6\uparrow & 9 \downarrow \\ \color{red} 4 \color{blue} + 16 & \color{red} 8 \color{blue} + 16 & \color{red} 6 \color{blue} + 16 & 5\uparrow & 10 \downarrow \\ 1 \to  \ & 2 \to & 3 \to & 4\uparrow & 11 \downarrow \\ 16 \gets & 15 \gets & 14 \gets & 13 \gets & 12 \gets \end{matrix}$$

于是就是一个普及组的填数问题了。

代码仅供参考。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 505;
int n, a[N][N];
int main()
{
	scanf("%d", &n);
	if(n <= 2) return puts("-1") && 0;
	int cnt = 0, outmax = n * n - 9;
	a[1][1] = 1 + outmax; a[1][2] = 7 + outmax; a[1][3] = 9 + outmax;
	a[2][1] = 3 + outmax; a[2][2] = 2 + outmax; a[2][3] = 5 + outmax;
	a[3][1] = 4 + outmax; a[3][2] = 8 + outmax; a[3][3] = 6 + outmax;
	for(int i = 1; i <= n - 3; i++)
	{
		if(i & 1)
		{
			for(int j = 1; j <= i + 2; j++) a[i + 3][j] = ++cnt;
			a[i + 3][i + 3] = ++cnt;
			for(int j = i + 2; j >= 1; j--) a[j][i + 3] = ++cnt;
		}
		else
		{
			for(int j = 1; j <= i + 2; j++) a[j][i + 3] = ++cnt;
			a[i + 3][i + 3] = ++cnt;
			for(int j = i + 2; j >= 1; j--) a[i + 3][j] = ++cnt;
		}
	}
	for(int i = 1; i <= n; i++, puts(""))
		for(int j = 1; j <= n; j++) printf("%d ", a[i][j]); 
	return 0;
}
```

---

## 作者：AutumnKite (赞：3)

[宣传 blog](https://autumnkite.github.io/)（Github Pages 上不去可以用 [Gitee 上的镜像](https://autumnkite.gitee.io/)）

### 题解

直接考虑一个很大的棋盘看上去非常难做。我们考虑首先将车和后延一条固定的、相同的路径引导至一个较小的棋盘内。

考虑到 $n\le 2$ 时一定无解，我们只要将最后的棋盘控制在 $3\times 3$ 的规模即可。

如何构造一个满足题目条件的 $3\times 3$ 的棋盘？

一共只有 $3\times 3=9$ 个数，我们可以直接暴力枚举所有棋盘！

注意这个棋盘的最小值所在的格子必须与路径的终点在同一行或同一列，这样才可以保证车和后在这个棋盘中的起点相同。

### 暴力代码

```cpp
int a[5][5], p[15], vis[5][5];

bool rook(int x1, int y1, int x2, int y2) {
	return x1 == x2 || y1 == y2;
}

bool queen(int x1, int y1, int x2, int y2) {
	return x1 == x2 || y1 == y2 || x1 + y1 == x2 + y2 || x1 - y1 == x2 - y2;
}

template<typename T>
int work(T check) { // check 是一个判断两点是否可以互相到达的函数（上方 rook 和 queen 中的一种）
	int x = 0, y = 0;
	for (int i = 1; i <= 3; ++i) {
		for (int j = 1; j <= 3; ++j) {
			if (a[i][j] == 1) {
				x = i, y = j;
			}
			vis[i][j] = 0;
		}
	}
	vis[x][y] = 1;
	int res = 0;
	while (1) {
		int nx = 0, ny = 0, mn = 10, type = 2;
		for (int i = 1; i <= 3; ++i) {
			for (int j = 1; j <= 3; ++j) {
				if (!vis[i][j]) {
					int tp = !check(x, y, i, j);
					if (tp < type || (tp == type && a[i][j] < mn)) {
						nx = i, ny = j, mn = a[i][j], type = tp;
					}
				}
			}
		}
		if (type == 2) {
			break;
		}
		res += type, x = nx, y = ny, vis[x][y] = 1;
	}
	return res;
}

int main() {
	for (int i = 1; i <= 9; ++i) {
		p[i] = i;
	}
	while (1) {
		for (int i = 1; i <= 3; ++i) {
			for (int j = 1; j <= 3; ++j) {
				a[i][j] = p[(i - 1) * 3 + j];
			}
		}
		if (work(rook) < work(queen)) {
			for (int i = 1; i <= 9; ++i) {
				print(p[i], ' ');
				if (i % 3 == 0) {
					putchar('\n');
				}
			}
			return 0;
		}
		if (!std::next_permutation(p + 1, p + 1 + 9)) {
			break;
		}
	}
}
```

### 代码

```cpp
const int N = 505;

int n, a[N][N];

void solve() {
	read(n);
	if (n <= 2) {
		print(-1);
		return;
	}
	int B = n * n - 9;
	a[1][1] = B + 1, a[1][2] = B + 2, a[1][3] = B + 4;
	a[2][1] = B + 5, a[2][2] = B + 3, a[2][3] = B + 8;
	a[3][1] = B + 9, a[3][2] = B + 6, a[3][3] = B + 7;
	int now = 0;
	for (int i = 4; i <= n; ++i) {
		if (i & 1) {
			for (int j = 1; j <= i; ++j) {
				a[i][j] = ++now;
			}
			for (int j = i - 1; j; --j) {
				a[j][i] = ++now;
			}
		} else {
			for (int j = 1; j <= i; ++j) {
				a[j][i] = ++now;
			}
			for (int j = i - 1; j; --j) {
				a[i][j] = ++now;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			print(a[i][j], ' ');
		}
		putchar('\n');
	}
}
```

---

## 作者：Karry5307 (赞：3)

### 题意

给定一个 $n\times n$ 的棋盘，你需要给每个格子分配一个标号。接下来车和皇后都会在编号为 $1$ 的格子上遵循如下的过程，直到所有格子都已经经过一次：

- 对于所有能一步到达的并且曾经没有到达过的格子，这个棋子移动到编号最小的格子上。

- 如果一步到达的所有格子曾近都到达过，那么花费 $1$ 将这个棋子传送到编号最小且没有到达过的格子。

构造一组方案使得车走完整个棋盘的花费比皇后小。

$\texttt{Data Range:}1\leq n\leq 500$

### 题解

赛时差这个题惨失 AK，枯了/kk

但是确确实实是一道好题。

注意到车和皇后都可以横平竖直走到任意一个格子，唯一不同的是皇后可以走对角线，所以目标是通过在对角线处放置更小的编号从而诱导皇后进入无法到达的地方。

同时注意到大棋盘上直接构造很复杂，所以考虑先规约到小棋盘的情况。

很明显 $1\times 1$ 和 $2\times 2$ 无解，对所有 $3\times 3$ 的 $9!$ 种可能进行逐一检查可以确定出其中一组解来：

$$\begin{matrix}1&7&9\\3&2&5\\4&8&6\end{matrix}$$

这个时候考虑将这个 $3\times 3$ 的解拓展到更大棋盘的情况，也即在走完除了这个 $3\times 3$ 的格子之后两枚棋子以同样的花费到达 $1$。

又因为车和皇后都能横平竖直走，所以一种可行的构造方法为将这个丢到棋盘左上角，然后以 $(4,1)$ 为起点螺旋填数，比如这样：

$$\begin{matrix}1+16&7+16&9+16&7&8\\3+16&2+16&5+16&6&9\\4+16&8+16&6+16&5&10\\1&2&3&4&11\\16&15&14&13&12\end{matrix}$$

也就是说，车和皇后螺旋地从 $(4,1)$ 开始走，必然能够在 $n^2-9$ 步之后走到 $(n,1)$ 或者 $(1,n)$ 的位置上（到底是哪个取决于 $n$ 的奇偶性），然后这两个位置车和皇后都能一步到达 $(1,1)$，皇后就陷入设下的圈套了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e3+51;
ll n,x,y;
ll r[MAXN][MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	n=read(),x=4,y=1;
	if(n<=2)
	{
		return puts("-1"),0;
	}
	for(register int i=1;i<=n*n-9;i++)
	{
		r[x][y]=i,max(x,y)&1?y==1?x++:(x<y?x++:y--):x==1?y++:(x>y?y++:x--);
	}
	r[1][1]=n*n-8,r[1][2]=n*n-2,r[1][3]=n*n;
	r[2][1]=n*n-6,r[2][2]=n*n-7,r[2][3]=n*n-4;
	r[3][1]=n*n-5,r[3][2]=n*n-1,r[3][3]=n*n-3;
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=n;j++)
		{
			printf("%d ",r[i][j]);
		}
		puts("");
	}
}
```

---

## 作者：奇米 (赞：3)

## $\mathrm{CF1333E\ Road \ to \ 1600 }$

[$$\huge\color{blue}\boxed{\color{Violet}\mathfrak{There\ is \ my \ blog}}$$](https://www.luogu.com.cn/blog/wyy2020/)

#### **题目意思**

* [CF1333E](https://www.luogu.com.cn/problem/CF1333E)


#### $\mathrm{Sol}$

* 首先$n\leq 2$是无解的

* 对于有解的情况我们考虑皇后先按照车走的方法走（即这时候不会产生贡献）然后我们再强制皇后不优秀的方法走，那么我们有如下的构造方法：

* 我们构造一个$2\times 3$的矩形使得把皇后逼到$2\times3$那一格，然后这个时候强制让皇后花费$1$走到$1\times 1$那一格子就可以了。

* 于是车就用微小的优势获胜了。

* 一下构造就很简单了，具体看代码。

#### $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define pb push_back
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

int n,m,a[N][N],ans;

int main()
{
	n=read();
	if(n<3) return printf("-1\n"),0;
	for ( int i=n;i>3;i-- ) a[1][i]=++m;
	for ( int i=4;i<=n;i++ ) a[2][i]=++m;
	for ( int i=3;i<n;i++ ) 
	{
		if(i&1)
			for ( int j=n;j>=1;j-- ) a[i][j]=++m;
		else 
			for ( int j=1;j<=n;j++ ) a[i][j]=++m;
	}
	if(n&1) 
	{
		for ( int j=n;j>=1;j-- ) 
			if(j!=2) a[n][j]=++m;
	}
	else 
		for ( int j=1;j<=n;j++ ) 
			if(j!=2) a[n][j]=++m;
	a[n][2]=++m;
	a[1][2]=++m,a[2][1]=++m,a[2][2]=++m,a[1][3]=++m,a[2][3]=++m;
	a[1][1]=++m;
	for ( int i=1;i<=n;i++,puts("") ) 
		for ( int j=1;j<=n;j++ )	
			printf("%d ",a[i][j]);
	return 0;
}
```





---

## 作者：听取MLE声一片 (赞：2)

思维题，orz wqy。

思路首先是要确定的，是尽可能使后走进一个陷阱，所以失败次数比车多。

我们发现让后进入两个陷阱，车进入一个陷阱比较难构造，所以我们尝试构造车一次通关，后进入一次陷阱的情况。

在 $1 \times 1$ 以及 $2 \times 2$ 的图中，后可以从任意一个点走到另外任意一个点，所以是无解的。

在 $3 \times 3$ 的图中，我们可以用爆搜或者硬找出一种方案：

$$9 \quad 5 \quad 6$$

$$7 \quad 2 \quad 8$$

$$1 \quad 3 \quad 4$$



这种方案能把后卡死在 8，失败一次，而车能一遍成功

注意这里把 1 放在了左下角，之后有用。

我们发现，在图比 $3 \times 3$ 大的时候，可以硬套上面的方案，即把上面的表放在整张地图的左上，然后以右上为 $1$ 开始螺旋填数即可，如 $n=4$ 时：

$$9+7 \quad 5+7 \quad 6+7 \quad 1$$

$$7+7 \quad 2+7 \quad 8+7 \quad 2$$

$$1+7 \quad 3+7 \quad 4+7 \quad 3$$

$$7 \quad 6 \quad 5 \quad 4$$

$n=5$ 时：

![](https://cdn.luogu.com.cn/upload/image_hosting/8xz5ai2d.png)

$n \geq 3$ 就像上面螺旋构造即可，注意当输入为奇数时要翻转一下表使其能与螺旋填数接上（不过这里不翻转好像也能过）。

下面是代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=510;
int n,a[N][N],sum; 
int main()
{
	n=read();
	if(n<=2){
		cout<<-1;
		return 0;
	}
	if(n%2==0){
		a[1][1]=9,a[1][2]=5,a[1][3]=6;
		a[2][1]=7,a[2][2]=2,a[2][3]=8;
		a[3][1]=1,a[3][2]=3,a[3][3]=4;	
	}
	else{
		a[1][1]=4,a[1][2]=3,a[1][3]=1;
		a[2][1]=8,a[2][2]=2,a[2][3]=7;
		a[3][1]=6,a[3][2]=5,a[3][3]=9;
	}
	for(int i=n;i>3;i--){
		if((n-i)%2==0){
			for(int j=1;j<=i;j++){
				sum++;
				a[j][i]=sum;
			}
			for(int j=i-1;j>=1;j--){
				sum++;
				a[i][j]=sum;
			}
			continue;
		}
		for(int j=1;j<=i-1;j++){
			sum++;
			a[i][j]=sum;
		}
		for(int j=i;j>=1;j--){
			sum++;
			a[j][i]=sum;
		}
	}
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			a[i][j]+=sum;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			cout<<a[i][j]<<' ';
		cout<<endl;
	}
	return 0;
}

```



---

## 作者：万弘 (赞：2)

首先$n\le 2$时无解。  
手玩出$2\times 3$是这样的：
```
6 1 4
2 3 5
```
车的代价是0，后的代价是1.

考虑一般情况，让车和后一起把其他都走掉，最后剩下一个$2\times 3$的就好了。

把其他的走掉，只要强迫车走掉就好了，因为车能到达的位置后一定也能到达。

时间复杂度$\mathcal O(n^2)$
```cpp
/**********/
#define MAXN 511
ll a[MAXN][MAXN];
int main()
{
    ll n=read();
    if(n<=2){puts("-1");return 0;}
    ll cnt=0;
    for(ll i=n;i>3;--i)a[1][i]=++cnt;
    for(ll i=4;i<=n;++i)a[2][i]=++cnt;
    for(ll i=3;i<n;++i)
    {
        if(i&1)
            for(ll j=n;j;--j)a[i][j]=++cnt;
        else 
            for(ll j=1;j<=n;++j)a[i][j]=++cnt;
    }
    if(n&1)
    {
        for(ll j=n;j;--j)
            if(j!=2)a[n][j]=++cnt;
    }
    else
    {
        for(ll j=1;j<=n;++j)
            if(j!=2)a[n][j]=++cnt;
    }
        
    a[n][2]=++cnt;
    a[1][1]=cnt+6,a[1][2]=cnt+1,a[1][3]=cnt+4;
    a[2][1]=cnt+2,a[2][2]=cnt+3,a[2][3]=cnt+5;
    for(ll i=1;i<=n;++i)
        for(ll j=1;j<=n;++j)printf("%lld%c",a[i][j],j==n?'\n':' ');
    return 0;
}
```

---

## 作者：7KByte (赞：1)

由简入繁。

如果我们找到一个大小为$k$
的正方形满足条件，那么对于任何$>k$的正方形都可以构造出来。方法很简单，我们先在外围随便填一些数，最后把棋子引入大小为$k$的子矩形即可。

手盘样例发现$N\le2$时无解（总共也就那么多种情况

手盘$2\times 3$的矩形，可以比较容易找到一个解。

例如：

| $4$ | $6$ |
| :----------: | :----------: |
| $1$ | $3$ |
| $5$ | $2$ |

现在我们要将它扩大为$3\times 3$，延续上面的思想。

| $4+3$ | $6+3$ | $2$ |
| :----------: | :----------: | :----------: |
| $1+3$ | $3+3$ | $3$ |
| $5+3$ | $2+3$ | $1$ |


将它旋转$180^\texttt{。}$也是可以的。

| $1$ | $5$ | $8$ |
| :----------: | :----------: | :----------: |
| $3$ | $6$ | $4$ |
| $2$ | $9$ | $7$ |

用$3\times 3$的正方形可以构造出所有情况。

| $1+tot$ | $5+tot$ | $8+tot$ | $7$ | $8$ |  $\cdots$ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $3+tot$ | $6+tot$ | $4+tot$ | $6$ | $9$ | $\cdots$  |
| $2+tot$ | $9+tot$ | $7+tot$ | $5$ | $10$ | $\cdots$  |
| $1$ | $2$ | $3$ | $4$ | $11$ | $\cdots$  |
| $16$ | $15$ | $14$ | $13$ | $12$ |$\cdots$   |
| $\cdots$ | $\cdots$  |$\cdots$   |  $\cdots$ | $\cdots$  | $\cdots$  |


这样我们由简入繁解决了问题


```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 505
using namespace std;
const int bas[3][3]={1,5,8,3,6,4,2,9,7};
int ans[N][N];
int main(){
	int n;scanf("%d",&n);int idx=0;
	if(n<=2){puts("-1");return 0;}
	rep(k,4,n){
		if(k&1){
			rep(i,1,k)ans[k][i]=++idx;
			pre(i,k-1,1)ans[i][k]=++idx;
		}
		else{
			rep(i,1,k)ans[i][k]=++idx;
			pre(i,k-1,1)ans[k][i]=++idx;
		}
	}
	rep(i,1,3)rep(j,1,3)ans[i][j]=bas[i-1][j-1]+idx;
	rep(i,1,n){rep(j,1,n)printf("%d ",ans[i][j]);putchar('\n');}
	return 0;
}
```

---

