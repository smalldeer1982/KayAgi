# Omkar and Duck

## 题目描述

This is an interactive problem.

Omkar has just come across a duck! The duck is walking on a grid with $ n $ rows and $ n $ columns ( $ 2 \leq n \leq 25 $ ) so that the grid contains a total of $ n^2 $ cells. Let's denote by $ (x, y) $ the cell in the $ x $ -th row from the top and the $ y $ -th column from the left. Right now, the duck is at the cell $ (1, 1) $ (the cell in the top left corner) and would like to reach the cell $ (n, n) $ (the cell in the bottom right corner) by moving either down $ 1 $ cell or to the right $ 1 $ cell each second.

Since Omkar thinks ducks are fun, he wants to play a game with you based on the movement of the duck. First, for each cell $ (x, y) $ in the grid, you will tell Omkar a nonnegative integer $ a_{x,y} $ not exceeding $ 10^{16} $ , and Omkar will then put $ a_{x,y} $ uninteresting problems in the cell $ (x, y) $ . After that, the duck will start their journey from $ (1, 1) $ to $ (n, n) $ . For each cell $ (x, y) $ that the duck crosses during their journey (including the cells $ (1, 1) $ and $ (n, n) $ ), the duck will eat the $ a_{x,y} $ uninteresting problems in that cell. Once the duck has completed their journey, Omkar will measure their mass to determine the total number $ k $ of uninteresting problems that the duck ate on their journey, and then tell you $ k $ .

Your challenge, given $ k $ , is to exactly reproduce the duck's path, i. e. to tell Omkar precisely which cells the duck crossed on their journey. To be sure of your mastery of this game, Omkar will have the duck complete $ q $ different journeys ( $ 1 \leq q \leq 10^3 $ ). Note that all journeys are independent: at the beginning of each journey, the cell $ (x, y) $ will still contain $ a_{x,y} $ uninteresting tasks.

## 说明/提示

The duck's three journeys are illustrated below.

 $ 1 + 2 + 3 + 2 + 10 + 3 + 2 = 23 $

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1392E/1f37e64a30ebc0ce9a89e8167cd742026bd8716b.png) $ 1 + 4 + 9 + 0 + 7 + 3 + 2 = 26 $

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1392E/667ac6d07d64f19cfddefd0d7011d38081a57cc2.png) $ 1 + 2 + 3 + 6 + 10 + 3 + 2 = 27 $

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1392E/15493ac75878713db55c0e2b89a479ece7aa36b0.png)

## 样例 #1

### 输入

```
4




3
23







26







27```

### 输出

```
1 2 3 6
4 6 2 10
9 0 7 3
2 8 8 2


1 1
1 2
1 3
2 3
2 4
3 4
4 4

1 1
2 1
3 1
3 2
3 3
3 4
4 4

1 1
1 2
1 3
1 4
2 4
3 4
4 4```

# 题解

## 作者：xiaolilsq (赞：6)

[题目链接](https://codeforces.com/problemset/problem/1392/E)

## 题目大意

构造一个 $n\times n$ 的矩阵，每个元素取值范围为 $[0,10^{16}]$ ，使得所有从 $(1,1)$ 仅往下或往右走走到 $(n,n)$ 的路径的权值两两不同（一条路径的权值定义为这条路径经过的所有元素之和）。

$1\le n\le 25$ 。

## 题目分析

### 思路一

神 @[Imakf](https://www.luogu.com.cn/user/47863) 提供了一种构造方法，把向右走认为是字符“a”，向左走认为是字符“b”，把所有 $(1,1)$ 到 $(n,n)$ 的路径写成字符串然后按照字典序排序后依次钦定权值为 $0,1,\dots,{2(n-1)\choose n-1}-1$ ，然后按照这个钦定的权值去给每个格子赋值就行了。

这样做为什么是对的？如果将所有路径插入 Trie 树，那么某个点 $(x,y)$ 到 $(n,n)$ 的所有路径在 Trie 树上面是连续的，按照上面的构造方法所有路径的权值也就是连续的一段，由此不难发现这样构造就是正确的（或者说钦定的权值并不会出现冲突）。

具体如何实现？认为左上角是 $(1,1)$ 右下角是 $(n,n)$ ，给每个格子 $(x,y)$ 记录一个 $[L,R]$ 表示 $(x,y)$ 到 $(n,n)$ 的所有路径的权值取值范围，先钦定第 $n$ 列的所有元素取值 $0$ ，然后按列数从大到小，行数从大到小确定每个格子元素的取值，先认为当前格子取值为 $0$ ，看从当前格子向下走和向右走的权值是否有重复，如果有的话就加大当前格子下面格子的取值。这样构造在极限数据 $n=25$ 时每个元素取值是符合范围的。

### 思路二

考虑二进制拆分，使用如下构造方式：

```
 0  0  0  0
 1  2  4  8
 0  0  0  0
 4  8 16 32
```

（奇数行所有元素为 $0$ ，偶数行位置 $(x,y)$ 的值为 $2^{x+y-3}$ ）

这种方法相当于把某个数二进制表示下若干连续的 $1$ 绑定在一起，连续的 $1$ 在同一行一起经过，不连续的 $1$ 在不同行经过，不难发现这样构造也不会出现重复。

## 参考代码

思路一的代码：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ch() getchar()
#define pc(x) putchar(x)
using namespace std;
template<typename T>void read(T&x){
	static char c;static int f;
	for(c=ch(),f=1;c<'0'||c>'9';c=ch())if(c=='-')f=-f;
	for(x=0;c>='0'&&c<='9';c=ch())x=x*10+(c&15);x*=f;
}
template<typename T>void write(T x){
	static char q[65];int cnt=0;
	if(x<0)pc('-'),x=-x;
	q[++cnt]=x%10,x/=10;
	while(x)
		q[++cnt]=x%10,x/=10;
	while(cnt)pc(q[cnt--]+'0');
}
long long L[35][35],R[35][35],val[35][35];
int main(){
	int n;read(n);
	for(int i=1;i<=n;++i){
		val[i][n]=0;
		L[i][n]=R[i][n]=0;
	}
	for(int j=n-1;j>=1;--j){
		val[n][j]=0;
		L[n][j]=R[n][j]=L[n][j+1];
		for(int i=n-1;i>=1;--i){
			val[i][j]=0;
			if(L[i+1][j]<=R[i][j+1]){
				long long delta=R[i][j+1]-L[i+1][j]+1;
				L[i+1][j]+=delta,R[i+1][j]+=delta;
				val[i+1][j]+=delta;
			}
			L[i][j]=L[i][j+1];R[i][j]=R[i+1][j];
		}
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;pc(" \n"[j==n]),++j)
			write(val[i][j]);
	fflush(stdout);
	int q;read(q);
	while(q--){
		long long x;read(x);
		int nx=1,ny=1;
		while(nx<=n&&ny<=n){
			write(nx),pc(' '),write(ny),pc('\n');
			if(nx<n&&L[nx+1][ny]<=x&&x<=R[nx+1][ny]){
				x-=val[nx+1][ny];++nx;
			}
			else{
				x-=val[nx][ny+1];++ny;
			}
		}
		fflush(stdout);
	}
	return 0;
}
/*
_|_|_|_|        _|_|      _|      _|   _|_|_|_|_|   _|_|_|_|_|   _|
_|      _|    _|    _|    _|_|    _|       _|       _|           _|
_|      _|   _|      _|   _| _|   _|       _|       _|           _|
_|      _|   _|_|_|_|_|   _|  _|  _|       _|       _|_|_|_|_|   _|
_|      _|   _|      _|   _|   _| _|       _|       _|           _|
_|      _|   _|      _|   _|    _|_|       _|       _|           _|
_|_|_|_|     _|      _|   _|      _|   _|_|_|_|_|   _|_|_|_|_|   _|_|_|_|_|

_|_|_|_|_|   _|      _|   _|_|_|_|     _|      _|
    _|        _|    _|    _|      _|    _|    _|
    _|         _|  _|     _|      _|     _|  _|
    _|          _|_|      _|      _|      _|_|
    _|         _|  _|     _|      _|       _|
    _|        _|    _|    _|      _|       _|
    _|       _|      _|   _|_|_|_|         _|

_|             _|_|_|     _|      _|   _|_|_|_|_|
_|           _|      _|   _|      _|   _|
_|           _|      _|    _|    _|    _|
_|           _|      _|    _|    _|    _|_|_|_|_|
_|           _|      _|     _|  _|     _|
_|           _|      _|      _|_|      _|
_|_|_|_|_|     _|_|_|         _|       _|_|_|_|_|

_|_|_|_|_|   _|      _|   _|_|_|_|_|
    _|        _|    _|        _|
    _|         _|  _|         _|
    _|          _|_|          _|
    _|           _|           _|
    _|           _|           _|
    _|           _|           _|

Created by xiaolilsq.
*/


```

---

## 作者：KellyFrog (赞：3)

题面比较恶心，大概的意思：你要构造一个 $n\times n$ 的矩阵，满足任意一个路径和所对应的路径唯一（即没有两条路径和相同）。

我们采用如下的构造方式：

对于 $a_{i,j}$，如果 $i$ 为偶数，则 $a_{i,j}=0$，否则 $a_{i,j}=2^{i+j}$，那么对于 $n=4$，我们构造出来的 $a$ 就是这样的：

```
2 4 8 16
0 0 0 0
8 16 32 64
0 0 0 0
```

接下来我们证明为什么这样的构造方式能够保证路径和唯一。

观察上面的构造方式，发现对于一个 $a_{x,y}$，$a_{x+1,y}\neq a_{x,y+1}$，那么假设在 $a_{x,y}$ 之后两条路径开始不同，那么一定是一个取到了 $2^{x+y}$ 一个取到了 $0$。

又因为我们不能往回走，所以不可能第二次有机会取到 $2^{x+y}$，两条路径和就是不同的。

之后简单模拟就可以回答询问。

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 30;

typedef long long ll;

ll a[MAXN][MAXN];

int main() {
	int n, q;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			printf("%lld ", (i & 1ll) << (i + j));
		}
		puts("");
	}
	fflush(stdout);
	scanf("%d", &q);
	while(q--) {
		ll x = 0;
		scanf("%lld", &x);
		int px = 0, py = 0;
		printf("%d %d\n", px + 1, py + 1);
		for(int i = 1; i <= n * 2 - 2; i++) {
			if(((x >> i) & 1) == (px & 1)) {
				py++;
			} else {
				px++;
			}
			printf("%d %d\n", px + 1, py + 1);
		}
		fflush(stdout);
	}
}
```

---

## 作者：DPair (赞：2)

## 简要题意
给你一个 $n$，要求构造一个 $n\times n$ 的矩阵，使得从左上到右下所有长度为 $2n-1$ 的路径上的点权和互不相同。

并且要求对于若干组询问输出对应的路径。

## 解法
首先由于我们要构造出的每一条路径权值和不同，因此显然要构造出一个整数的集合，里面每一个数与一条路径一一对应。

只有这样给你这个数你才可以唯一确定这条路径。

那么我们考虑什么可以和一条路径一一对应，一个常见的转化是一个长度为 $2n-2$ 的序列，里面每一个元素取 “向下走” 或者 “向右走”。显然所有包含恰好 $n-1$ 个向下和恰好 $n-1$ 个向右的这种序列与一条路径一一对应。

注意到这个序列每一位只有两种取值，因此考虑压位，发现 $2^{50-2}=2^{48}<10^{16}$ 因此开得下。

那么现在的问题是：考虑如何构造一个矩阵使得 **所有路径的和的二进制表示可以唯一确定一个序列。** 

考虑归纳，假设我们对于一个长度为 $x$ 的 **二进制下的** 前缀已经可以确定当前位置，那么我们只需要对于 $x+1$ 这一位确定我们应该是往右还是往下。

我们可以考虑对于矩阵上的每一个位置维护出它向右是对应的二进制位取 $1$ 还是向下取 $1$，因此只需要每一位向右向下一个取 $1$ 一个取 $0$ 即可。由于我们 $x=0$ 时显然知道当前位置在 $(1, 1)$，因此后面都可以递推的构造出一条路径。

因此可以构造一个矩阵，其中偶数行都是 $0$，奇数行则考虑一个位置 $(i,j)$ 可以取 $2^{i+j-2}$，这样每一条对角线取值全部相同，而且不难发现一定对应一个新的二进制位。

最后找路径顺推即可。

```cpp
#include <cstdio>

typedef long long LL;
int n;

inline LL value(int x, int y) { return (x & 1) * (1ll << (x + y - 1)); }

int main() {
    scanf("%d", &n);
    for (int i = 0;i < n;++ i) {
        for (int j = 0;j < n;++ j) printf("%lld ", value(i, j));
        printf("\n");
    }
    fflush(stdout);

    int q; scanf("%d", &q);
    while(q --) {
        LL x; scanf("%lld", &x);
        int i = 0, j = 0;
        while(i < n - 1 && j < n - 1){
            printf("%d %d\n", i + 1, j + 1);
            const LL t = 1ll << (i + j);
            if(value(i + 1, j) == (t & x)) ++ i;
            else ++ j;
        }
        while(i < n - 1) {
            printf("%d %d\n", i + 1, j + 1);
            ++ i;
        }
        while(j < n - 1) {
            printf("%d %d\n", i + 1, j + 1);
            ++ j;
        }
        printf("%d %d\n", i + 1, j + 1);
        fflush(stdout);
    }
}

```

---

## 作者：5ab_juruo (赞：1)

给一种不一样的构造。

一个朴素的想法是：让每一条可能的路径产生的权值和都互不相同，且满足一定的单调关系。以 $n=4$ 为例，先令最右上的路径权值为 $0$，即：

```plain
0 0 0 0
      0
      0
      0
```


接下来考虑递推：在倒数第二格向下的路径要恰好比最右侧的路径大 $1$，所以对应位置填上 $1$。以此类推，可以推出第二行：

```plain
0 0 0 0
1 1 1 0
  y x 0
      0
```

推下一行的 $x$ 时要满足：$x$ 上方所有的路径的最大值比经过 $x$ 的路径的最小值恰好小 $1$，本例中 $x=3$。类似地，最小的经过 $y$ 的路径的权值要比当前已经填了的路径中最大值大 $1$。

下图解释了一般情况下的填数策略（蓝色是之前最大的路径，绿色是新的最小路径，灰色是蓝色比绿色多出来的，黄色是绿色比蓝色多出来的）：

![](https://cdn.luogu.com.cn/upload/image_hosting/7k0owja5.png)

递推的方式也说明了正确性：将起点和终点调换，令向左为 $1$，向上为 $0$，将每一条路径按照经过的边的字典序排序，则这条路径的权值就是其在排序后序列的排名 $-1$。

处理询问是平凡的：倒着走，如果能向左走就向左，否则向上，然后逆序输出即可。

由于数据范围非常小，怎么做都能过，$n=25$ 时最大的 $a_{i,j}$ 还不到 $10^{13}$。

```cpp
/* name: 1392E
 * author: 5ab
 * created at: 2022-12-11
 */
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

typedef long long ll;
const int max_n = 25;

ll a[max_n][max_n], sm[max_n];
int seq[max_n * 2];

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			a[i][j] = sm[j + 1] - a[i - 1][j] + 1;
			for (int k = 0; k < i - 1; k++)
				a[i][j] -= a[k][j] - a[k][0];
		}
		partial_sum(a[i], a[i] + n, sm);
	}
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cout << a[i][j] << " \n"[j == n - 1];
	cout << flush;
	
	int q;
	ll x;
	
	cin >> q;
	while (q--)
	{
		cin >> x;
		
		ll tmp;
		for (int i = n - 1, j = n - 1, sk = 0; i > 0 || j > 0; sk++)
		{
			if (i == 0)
				seq[sk] = 1, x -= a[i][--j];
			else if (j == 0)
				seq[sk] = 0, x -= a[--i][j];
			else
			{
				tmp = 0;
				for (int k = 0; k <= i; k++)
					tmp += a[k][j - 1];
				if (tmp <= x)
					seq[sk] = 1, x -= a[i][--j];
				else
					seq[sk] = 0, x -= a[--i][j];
			}
		}
		reverse(seq, seq + 2 * n - 2);
		
		int ps[2] = {1, 1};
		cout << ps[0] << " " << ps[1] << "\n";
		for (int i = 2; i < 2 * n; i++)
		{
			ps[seq[i - 2]]++;
			cout << ps[0] << " " << ps[1] << "\n";
		}
		cout << flush;
	}
	
	return 0;
}
```

---

## 作者：leoair (赞：1)

### 题意：
本题是一道交互题。给定一个 $n$，构造一个 $n$ 行 $n$ 列的矩阵 $a$。有 $q$ 组询问，每组询问给定一个 $x$，使从 $a_{1,1}$ 开始往 $a_{n,n}$ 走，有一条路径的权值和为 $x$。

### 分析：
首先将 $x$ 二进制拆分，设若 $x$ 的第 $i$ 位为 $1$，则代表路径上的第 $i$ 个数是 $2^i$，否则第 $i$ 个数是 $0$。
由此，我们可以按照这个性质构造这个矩阵：（以 $n=4$ 为例）
$\begin{vmatrix}{\color{Red}1}&|&{\color{Blue}0}&|&{\color{Green}4}&|&{\color{Brown}0}\\{\color{Blue}2}&|&{\color{Green}0}&|&{\color{Brown}8}&|&{\color{SkyBlue}{16}}\\{\color{Green}4}&|&{\color{Brown}0}&|&{\color{SkyBlue}0}&|&{\color{Purple}0}\\{\color{Brown}8}&|&{\color{SkyBlue}{16}}&|&{\color{Purple}{32}}&|&{\color{Gray}{64}}\end{vmatrix}$
根据我们构造的这个矩阵，我们可以发现，若 $x$ 的第 $i$ 位是 $1$，则往下走，否则往右走，由此我们可以得出要求的路径。

### Code：
```cpp
/*
user:leoair
time:2022.3.24
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, a[35][35];

inline int read(){
    int s = 0, w = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; w *= ch == '-' ? -1 : 1, ch = getchar());
    for (; ch >= '0' && ch <= '9'; s = s * 10 + ch - '0', ch = getchar());
    return s * w;
}

signed main(){
    n = read();
    for (int i = n; i; --i)
        for (int j = n; j; --j)
            if (j == 1 || i == n) a[i][j] = 1ll << (i + j - 2);
            else if (j == 2 || i == n - 1) a[i][j] = 0;
            else a[i][j] = a[i + 2][j - 2];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) printf("%lld%c", a[i][j], j == n ? '\n' : ' ');
    fflush(stdout);
    for (int q = read(), m, x, y; q--; ){
        m = read(), x = 1, y = 1;
        puts("1 1\n");
        for (int i = 1; i <= n * 2 - 2; ++i){
            if ((m >> i & 1) == (a[x + 1][y] >> i & 1)) ++x;
            else ++y;
            printf("%lld %lld\n", x, y);
        }
        fflush(stdout);
    }
    return 0;
}
```

---

## 作者：Day_Tao (赞：0)

神秘构造。

惊人的注意力可以发现 $2^{2n}\le10^{16}$，所以不妨从这里入手。

题目的意思就是要求每一条路径的和不同，而且还有若干组询问给出路径和求路径，所以随机构造肯定是不行的，不然对于询问的处理就很麻烦了。

考虑格路问题的本质。就是向下或者向右走嘛。而根据上面的 $2^{2n}\le10^{16}$，$2n$ 就是走的步数，所以我们不妨对于每一步往哪走都用二进制位记录下来。于是我们不难得出如下构造：

$$\begin{bmatrix}
0&0&0&0&0&\cdots\\
2^0&2^1&2^2&2^3&\cdots\\
0&0&0&\cdots\\
2^2&2^3&\vdots&\ddots\\
0&\vdots\\
\vdots
\end{bmatrix}$$

即：对于一个点 $(i,j)$，往下或往右走会对路径和二进制下第 $2^{i+j-2}$ 位进行贡献。这样我们要的矩阵就构造好了。

这样构造在询问时直接将给出的 $x$ 二进制拆位对于每一位决策当前往哪走即可。

时间复杂度 $O(q\log V+n^2)$。代码很简洁。

```cpp
int n,q,a[N][N];
inline void an(int x,int y){cout<<x<<' '<<y<<endl;}
signed main(){
	n=rd();
	for(int x=3;x<=(n<<1);x++)
		for(int i=1,j=x-i;i<x;i++,j--)if(i<=n&&j<=n)a[i][j]=i&1?1ll<<x-3:0;
	for(int i=1;i<=n;i++,cout<<endl)
		for(int j=1;j<=n;j++)cout<<a[i][j]<<' ';
	q=rd();while(q--){
		int x=rd(),X=1,Y=1;an(X,Y);
		for(int i=0;i<(n-1<<1);i++){
			if(x>>i&1){if(a[X+1][Y])X++;else Y++;}
			else {if(a[X+1][Y])Y++;else if(X<n)X++;else Y++;}an(X,Y);
		}
	}
}
```

---

## 作者：Nuisdete (赞：0)

其实就是让构造一个路径权值和两两不同的矩阵。

在矩阵中依次填数，考虑倒着走，钦定这一步往左走的路径一定比往上走的路径权值和要大，那么直接统计两种走法的最大权值和最小权值之差，再加一填入左面的格子即可。

填入的最大数是路径总条数级别的，远小于 $10^{16}$。

输出同样直接倒着走即可。

```cpp
# include <cstdio>
# include <vector>
# include <cstring>
# include <utility>
# include <algorithm>
# include <functional>

# define int long long

int a[100][100], b[100][100];

void solve() {

  memset(a, 0, sizeof a);
  memset(b, 0, sizeof b);

  int n;
  scanf("%lld", &n);
  for (int i = 2; i <= n; ++i) {
    b[i][1] = b[i - 1][1];
    for (int j = 1; j < n; ++j) {
      int sum1 = 0, sum2 = 0;
      for (int k = 1; k < i; ++k) sum1 += a[k][j];
      for (int k = 1; k < i; ++k) sum2 += a[k][1];
      for (int k = 2; k <= j + 1; ++k) sum2 += a[i - 1][k];
      a[i][j] = sum2 - sum1 + 1, b[i][j] += a[i][j] + b[i][j - 1];
    }
    b[i][n] = b[i][n - 1];
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j)
      printf("%lld%c", a[i][j], " \n"[j == n]); fflush(stdout);
  }

  int q;
  scanf("%lld", &q);
  for (int i = 1; i <= q; ++i) {
    int V; scanf("%lld", &V);
    std::vector<std::pair<int, int> > vec;

    std::function<void(int, int, int)> dfs = [&](int x, int y, int val) {
      vec.emplace_back(x, y);
      if (x == 1 && y == 1) return;
      if (x == 1 || b[x - 1][y] + a[x][y] < val) 
        dfs(x, y - 1, val - a[x][y]); 
      else dfs(x - 1, y, val - a[x][y]);
    };
    dfs(n, n, V);

    for (auto it = vec.rbegin(); it != vec.rend(); it ++)
      printf("%lld %lld\n", it->first, it->second), fflush(stdout);
  }  
}

signed main() {

  int T = 1;
  while (T--) solve();

  return 0;
}
```

---

## 作者：Daniel_yao (赞：0)

## Problem
交互题。你需要构造一个矩阵，使得从 $(1,1)$ 到 $(n,n)$ 的所有路径互不相同。构造这个矩阵，并且每次给定 $(1,1)$ 到 $(n,n)$ 其中的一条路径的权值和，找出这条路径。

权值 $w(0\le w\le 10^{16})$。
## Solve
首先是构造矩阵。受到“由 $2$ 的任意次方之和可以构成所有自然数”的启发。想要让路径之和互不相同，只需要在第 $i$ 行 $j$ 列的格子上填上 $2^{i+j}$ 就行了。而且找路径也很好找。

不过权值的数据范围是有限制的，一看 $1\le n\le 25$。所以权值最大会达到 $2^{50}=1125899906842624$ 。然后发现超了 $10^{16}$，~~真的是天亡我也~~。

不过你想想看，其实并不需要所有的权值都得这样构造。我们可以空一些行出来。像这样：
```
1 2 4 8 
2 4 8 16
4 8 16 32
8 16 32 64
```
可以空一些行，让其耗费的权值更小，空行补 $0$ 即可。
```
1 2 4 8
0 0 0 0
2 4 8 16
0 0 0 0
```
这样，权值最大值域就会变成 $2^{\frac{50}{2}}= 33554432$，$10^8$ 都不到，可谓是非常优秀。再来看怎样上找路径，假设要找的路径权值和为 $x$，将 $x$ 二进制分解之后，如果 $x$ 的第 $i$ 位上为 $1$，并且现在为奇数行，则向左走，否则向下走，如果是偶数行，则相反（第 $i$ 位上为 $1$，向下，否则向右）。原理也很简单，二进制第 $i$ 位为 $1$，说明该数的构成中一定有 $2^i$。肯定希望走到一个权值不为 $0$ 的一行，反之，希望走到一个权值为 $0$ 的一行。然后就具体情况具体讨论即可。

时间复杂度 $O(n^2+Tn)$，记得交互。
## Code 
```cpp
#include <bits/stdc++.h>
#define int long long
#define H 19260817
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)
#define MOD 1000003
#define mod 1000000007

using namespace std;

inline int read() {
  rint x=0,f=1;char ch=getchar();
  while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
  while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
  return x*f;
}

void print(int x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

int n, T;

signed main() {
  n = read();
  For(i,0,n-1) {
    For(j,0,n-1) {
      cout << ((i & 1) << (i + j)) << ' ';
    }
    cout << '\n';
  }
  fflush(stdout);
  T = read();
  while(T--) {
    int x = read();
    int px = 0, py = 0;
    cout << px + 1 << ' ' << py + 1 << '\n';
    For(i,1,n*2-2) {
      if(((x >> i) & 1) == (px & 1)) py++;
      else px++;
      cout << px + 1 << ' ' << py + 1 << '\n';
    }
    fflush(stdout);
  }
  return 0;
}
```

---

## 作者：傅天宇 (赞：0)

[luogu's link](https://www.luogu.com.cn/problem/CF1392E)

[CF's link](https://codeforces.com/problemset/problem/1392/E)

#### 题意：

交互题，给出一个正整数 $n$（$1\le n\le25$），你需要构造一个 $n\times n$ 的矩阵 $a$，我们称 $a$ 中第 $i$ 行第 $j$ 列的数字为 $a_{i,j}$（$1\le a_{i,j}\le 10^{16}$）。我们定义一条路径为从 $a_{1,1}$ 开始，每次向下或向右走一格（不能走出去），最终到达 $a_{n,n}$ 的元素的集合。我们定义“路径和”为一条路径上所有元素的和。现在有 $q$ 组询问，每组询问包括一个整数 $x$，你需要找到一条路径，满足其路径和等于 $x$，保证解存在。

#### Solution：

根据题意，可以构造出矩阵 $a$ 。

当 $n=4$ 时，构造如下：

|    0 |    0 |    0 |    0 |
| ---: | ---: | ---: | ---: |
|    2 |    4 |    8 |   16 |
|    0 |    0 |    0 |    0 |
|    8 |   16 |   32 |   64 |

以此类推。

构造出这个矩阵，后面路径根据二进制分解就很好推了。

#### Code：

```cpp
/*
 * @Author: FuTianyu 
 * @Date: 2020-12-02 14:23:09 
 * @Last Modified by: FuTianyu
 * @Last Modified time: 2020-12-03 07:32:25
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
/*
快读快输
*/
int n,t;
signed main(){
    n=read();
    FOR(i,0,n-1){
        FOR(j,0,n-1){
            if(j>0) cout<<" ";
            if(i%2==0) cout<<0;
            else cout<<(1ll<<(i+j-1));
        }
        cout<<endl;
    }
    t=read();
    while(t--){
        int x=read();
        int i=0,j=0;
        cout<<i+1<<" "<<j+1<<endl;
        while(i<n-1||j<n-1){
            bool f=0;
            if(x&(1ll<<i+j)) f=1;
            if(i%2!=f) i++;
            else j++;
            cout<<i+1<<" "<<j+1<<endl;
        }
    }
    return 0;
}
```



---

