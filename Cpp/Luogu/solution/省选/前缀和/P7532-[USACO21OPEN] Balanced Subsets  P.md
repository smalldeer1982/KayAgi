# [USACO21OPEN] Balanced Subsets  P

## 题目描述

Farmer John 的草地可以被看作是由正方形方格组成的巨大的二维方阵（想象一个巨大的棋盘），对于每一个 $1≤i≤N$、$1≤j≤N$，方格可以用有序对 $(i,j)$ 表示。某些方格中含有草。

方格的一个非空子集被称为是「平衡的」，如果以下条件成立：

- 1. 所有子集中的方格均含有草。
- 2. 子集是四连通的。换句话说，从子集中的任一方格到另一方格均存在一条路径使得路径中的相邻方格均水平或竖直方向上相邻。
- 3. 如果方格 $(x_1,y)$ 和 $(x_2,y)$（$x_1≤x_2$）存在于子集中，那么所有满足 $x_1≤x≤x_2$ 的方格 $(x,y)$ 也存在于子集中。
- 4. 如果方格 $(x,y_1)$ 和 $(x,y_2)$（$y_1≤y_2$）存在于子集中，那么所有满足 $y_1≤y≤y_2$ 的方格 $(x,y)$ 也存在于子集中。

计算平衡的子集数量模 $10^9+7$ 的结果。

## 说明/提示

#### 样例一解释

对于这个测试用例，所有的四连通子集均是平衡的。

```
G.  .G  ..  ..  GG  .G  ..  G.  GG  .G  G.  GG  GG
.., .., G., .G, .., .G, GG, G., G., GG, GG, .G, GG
```

#### 样例二解释

以下是一个符合第二个条件（四连通）但不符合第三个条件的子集的例子： 

```
GG..
.G..
GG..
....
```

#### 数据范围与约定

$1\le N \le 150$ 。

## 样例 #1

### 输入

```
2
GG
GG```

### 输出

```
13```

## 样例 #2

### 输入

```
4
GGGG
GGGG
GG.G
GGGG```

### 输出

```
642```

# 题解

## 作者：Creeper_l (赞：3)

原题链接：[P7532](https://www.luogu.com.cn/problem/P7532)

## 前言

这道题是今天 NOIP 模拟赛的 T1，~~赛时只有 5 分~~。

## 题意
 
简化一下题意，即在一个 $n\times n$ 的方阵中，求出有多少个满足条件的连通块，使得：

- 同一行或列的两点中间没有空

- 连通块内全是草

可以发现，其实连通块就是一个**凸多边形**。

## 思路

很显然，这道题是一道计数 DP。

因为时凸多边形，所以它的边只有两种情况——扩张和缩小。于是我们可以设计出状态：

$dp_{i,l,r,p,q}$ 表示选完第 $i$ 行，第 $i$ 行选 $l$ 至 $r$ 的区间里的格子，左右端点分别处于扩张或缩小的状态。

很容易想到一个 $O(n^{5})$ 的暴力DP，先枚举 $i,l,r$，再枚举 $x,y$ 来转移。但这样转移肯定会超时，于是考虑优化。

我们会发现，其实每次方程转移时用的数据都是 $f$ 数组里的一个子区间，于是可以用**前缀和**进行优化，做到 $O(1)$ 去转移，这样整个代码的时间复杂度就时 $O(n^{3})$ 的了，可以通过本题。

## 写法

现在我们知道要用前缀和了，到底要怎么求呢？可以看到下面的 get 函数

```cpp
int get(int i,int l,int r,int x,int y,int p,int q) {
	return (f[i][r][y][p][q] - f[i][l - 1][y][p][q] - f[i][r][x - 1][p][q] + f[i][l - 1][x - 1][p][q]) % mod;
}
```

首先，求前缀和的过程就是二维前缀和板子，不多赘述。

主要讲传入函数的参数的意义：

- $i$ 表示正在求的那一行的上一行，用已知推未知。

- $l$ 和 $r$ 表示第 $i$ 行左端点可能在的区间。

- $x$ 和 $y$ 表示第 $i$ 行右端点可能在的区间。

- $p$ 和 $q$ 表示第 $i$ 行左右端点分别处于扩张或缩小的状态。

怎么用这个前缀和呢，看下面代码：

```cpp
dp[i][l][r][0][0] = (get(i - 1,l,r,l,r,0,0) + 1) % mod; 
dp[i][l][r][0][1] = (get(i - 1,l,r,r + 1,n,0,0) + get(i - 1,l,r,r,n,0,1)) % mod;
dp[i][l][r][1][0] = (get(i - 1,1,l - 1,l,r,0,0) + get(i - 1,1,l,l,r,1,0)) % mod;
dp[i][l][r][1][1] = (get(i - 1,1,l - 1,r + 1,n,0,0) + get(i - 1,1,l - 1,r,n,0,1)) % mod;
dp[i][l][r][1][1] = (get(i - 1,1,l,r + 1,n,1,0) + get(i - 1,1,l,r,n,1,1) + dp[i][l][r][1][1]) % mod;
```
这里加一减一的细节很多，需要注意。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls id << 1
#define rs id << 1 | 1
#define inf 0x3f3f3f3f
typedef pair <int,int> pii;
const int MAXN = 160;
const int mod = 1e9 + 7;
int n,dp[MAXN][MAXN][MAXN][2][2],f[MAXN][MAXN][MAXN][2][2],sum[MAXN],ans;
char c[MAXN]; 
int get(int i,int l,int r,int x,int y,int p,int q) {
	return (f[i][r][y][p][q] - f[i][l - 1][y][p][q] - f[i][r][x - 1][p][q] + f[i][l - 1][x - 1][p][q]) % mod;
}
signed main()
{
	cin >> n;
	for(int i = 1;i <= n;i++) {
		cin >> (c + 1);
		for(int j = 1;j <= n;j++) sum[j] = sum[j - 1] + (c[j] == 'G');
		for(int l = n;l >= 1;l--)
			for(int r = l;r <= n;r++) {
				if(sum[r] - sum[l - 1] != r - l + 1) continue;
				dp[i][l][r][0][0] = (get(i - 1,l,r,l,r,0,0) + 1) % mod; 
				dp[i][l][r][0][1] = (get(i - 1,l,r,r + 1,n,0,0) + get(i - 1,l,r,r,n,0,1)) % mod;
				dp[i][l][r][1][0] = (get(i - 1,1,l - 1,l,r,0,0) + get(i - 1,1,l,l,r,1,0)) % mod;
				dp[i][l][r][1][1] = (get(i - 1,1,l - 1,r + 1,n,0,0) + get(i - 1,1,l - 1,r,n,0,1)) % mod;
				dp[i][l][r][1][1] = (get(i - 1,1,l,r + 1,n,1,0) + get(i - 1,1,l,r,n,1,1) + dp[i][l][r][1][1]) % mod;
				for(int p = 0;p < 2;p++) for(int q = 0;q < 2;q++) ans = (ans + dp[i][l][r][p][q]) % mod;
			}
		for(int j = 1;j <= n;j++) 
			for(int k = 1;k <= n;k++)
				for(int p = 0;p <= 1;p++)
					for(int q = 0;q <= 1;q++)
						f[i][j][k][p][q] = (((f[i][j - 1][k][p][q] + f[i][j][k - 1][p][q]) % mod - f[i][j - 1][k - 1][p][q]) + dp[i][j][k][p][q]) % mod;
	}
	cout << (ans + mod) % mod;
    return 0;
}


```







---

## 作者：7KByte (赞：3)

感觉在哪见过原题。。。

感性一下这个限制条件，发现就是要求这个联通块是个凸多边形的形状。

由于是个网格图，我们可以发现从上往下，左端点先减后增，右端点先增后减，当然也可以单增或单减。

这样我们可以定义状态 $\large f_{i,l,r,0/1,0/1}$ 表示第 $i$ 结尾，第 $i$ 行填了 $[l,r]$ 的格子，左边处于增/减状态，右边处于增/减状态的方案数。

枚举前面一行填的格子，我们不难得到一个 $\rm O(N^5)$  的解法。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 155
using namespace std;
int n,u[N],f[N][N][N][2][2];char s[N];
int main(){
	scanf("%d",&n);int ans=0;
	rep(i,1,n){
		scanf("%s",s+1);
		rep(j,1,n)u[j]=u[j-1]+(s[j]=='G');
		pre(l,n,1)rep(r,l,n)if(u[r]-u[l-1]==r-l+1){
			f[i][l][r][0][0]=1;
			pre(x,n,1)rep(y,x,n){
				if(x>=l&&y<=r)f[i][l][r][0][0]+=f[i-1][x][y][0][0];
				if(x>=l&&x<=r&&y>r)f[i][l][r][0][1]+=f[i-1][x][y][0][0];
				if(x>=l&&x<=r&&y>=r)f[i][l][r][0][1]+=f[i-1][x][y][0][1];
				if(y>=l&&y<=r&&x<l)f[i][l][r][1][0]+=f[i-1][x][y][0][0];
				if(y>=l&&y<=r&&x<=l)f[i][l][r][1][0]+=f[i-1][x][y][1][0];
				if(x<=l&&y>=r)f[i][l][r][1][1]+=f[i-1][x][y][1][1];
				if(x<l&&y>=r)f[i][l][r][1][1]+=f[i-1][x][y][0][1];
				if(x<=l&&y>r)f[i][l][r][1][1]+=f[i-1][x][y][1][0];
				if(x<l&&y>r)f[i][l][r][1][1]+=f[i-1][x][y][0][0];
			}
			rep(x,0,1)rep(y,0,1)ans+=f[i][l][r][x][y];
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

观察一下，如果我们把 $f$ 数组写成一个矩阵，则每次转移加上的一定是 $f[i-1]$ 的一个子矩阵之和！

大力二维前缀和即可，时间复杂度$\rm O(N^3)$。

作为 USACO P组最后一题貌似简单了一点？

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 155
#define P 1000000007
using namespace std;
int n,u[N],f[N][N][N][2][2],g[N][N][N][2][2];char s[N];
int w(int i,int x,int y,int p,int q,int l,int r){
	return (((g[i][y][q][l][r]-g[i][x-1][q][l][r])%P-g[i][y][p-1][l][r])%P+g[i][x-1][p-1][l][r])%P;
}
int main(){
	scanf("%d",&n);int ans=0;
	rep(i,1,n){
		scanf("%s",s+1);
		rep(j,1,n)u[j]=u[j-1]+(s[j]=='G');
		pre(l,n,1)rep(r,l,n)if(u[r]-u[l-1]==r-l+1){
			f[i][l][r][0][0]=1+w(i-1,l,r,l,r,0,0);
			f[i][l][r][0][1]=(w(i-1,l,r,r+1,n,0,0)+w(i-1,l,r,r,n,0,1))%P;
			f[i][l][r][1][0]=(w(i-1,1,l-1,l,r,0,0)+w(i-1,1,l,l,r,1,0))%P;
			f[i][l][r][1][1]=((w(i-1,1,l,r,n,1,1)+w(i-1,1,l-1,r+1,n,0,0))%P+
							  (w(i-1,1,l-1,r,n,0,1)+w(i-1,1,l,r+1,n,1,0))%P)%P;
			rep(x,0,1)rep(y,0,1)(ans+=f[i][l][r][x][y])%=P;
		}
		rep(p,0,1)rep(q,0,1)rep(x,1,n)rep(y,1,n)
			g[i][x][y][p][q]=(((g[i][x-1][y][p][q]+g[i][x][y-1][p][q])%P-g[i][x-1][y-1][p][q])%P+f[i][x][y][p][q])%P;
	}
	printf("%d\n",(ans+P)%P);
	return 0;
}
```

---

## 作者：_zhangcx (赞：2)

# [[USACO21OPEN] Balanced Subsets P](https://www.luogu.com.cn/problem/P7532)

如果有蒟蒻想出状态但不会转移的请看这篇题解，~~就比如我~~

首先解析一下题目中“平衡”条件，就是实心凸多边形的充要条件，因为如果是凹的，一定会有一行/一列不连续。

求平衡连通块个数，显然是计数 DP。

那么从上到下扫一遍这个四边形，那么左、右端点一定是先扩张后收缩的，于是得到状态设计:

$f_{l,r,p,q}$（其中 $p,q \in \{0,1\}$）：扫到第 $i$ 行，第 $i$ 行左右端点分别为 $l$、$r$，且到此时左端点是扩张/收缩趋势（$p$），右端点是扩张/收缩趋势（$q$）的方案数。

方便起见，我们把 $p$、$q$ 这两维称为“变化趋势”。

## SubTask

$n \le 50$ 的情况直接转移状态即可。

可以看看我的代码和图理解一下。

![图1](https://cdn.luogu.com.cn/upload/image_hosting/a8p0xo8x.png)

时间复杂度 $O(n^5)$

```cpp
#define int long long int
namespace SubTask {
/* O(n^5): 照状态直接转移即可，能拿到50pts高分
 */
void solve() {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            ss[j] = ss[j - 1] + (s[i][j] == 'G');
        for (int l = 1; l <= n; l++) {
            for (int r = l; r <= n; r++) { // 枚举这一个区间 [l, r]
                if (ss[r] - ss[l - 1] != r - l + 1)
                    continue;  // 没有填满色
                f[i][l][r][0][0] = 1; // 这个代表现在第 i 行的 [l, r] 是整个图形的顶部
                for (int x = 1; x <= n; x++)
                    for (int y = x; y <= n; y++) {  // 枚举上一个区间 [x, y]
                        // 注意到变化趋势：0可以转到1，但是1不可以转到0，如果是l/r不变那么认为l/r的变化趋势也不变

                        // l, r都扩张，变化趋势不变
                        if (l <= x && y <= r)
                            add(f[i][l][r][0][0], f[i - 1][x][y][0][0]);
                        // l一定保证扩张，分讨r是收缩/不变的两种情况
                        if (l <= x && x <= r && r < y)
                            add(f[i][l][r][0][1], f[i - 1][x][y][0][0]);
                        if (l <= x && x <= r && r <= y)
                            add(f[i][l][r][0][1], f[i - 1][x][y][0][1]);

                        // r一定保证扩张，分讨l是收缩/不变的两种情况
                        if (x < l && l <= y && y <= r)
                            add(f[i][l][r][1][0], f[i - 1][x][y][0][0]);
                        if (x <= l && l <= y && y <= r)
                            add(f[i][l][r][1][0], f[i - 1][x][y][1][0]);

                        // 分讨l是收缩/不变及r是收缩/不变的四种情况
                        if (x <= l && y >= r)
                            add(f[i][l][r][1][1], f[i - 1][x][y][1][1]);
                        if (x < l && y >= r)
                            add(f[i][l][r][1][1], f[i - 1][x][y][0][1]);
                        if (x <= l && y > r)
                            add(f[i][l][r][1][1], f[i - 1][x][y][1][0]);
                        if (x < l && y > r)
                            add(f[i][l][r][1][1], f[i - 1][x][y][0][0]);
                    }
                for (int c = 0; c < 4; c++)
                    add(ans, f[i][l][r][c >> 1][c & 1]);
            }
        }
    }
    printf("%lld\n", ans);
}
};
```

## FullSolution

$n \le 150$ 的情况要考虑优化。

可以看出我们转移状态的时候用了 $x$ 和 $y$ 帮助转移，但这样也大大增加了我们的时间复杂度。

考虑去掉 $x$ 和 $y$ 这两层循环，把情况列出来试一试：

![图2](https://cdn.luogu.com.cn/upload/image_hosting/n969f4ki.png)

可以发现对于每种情况的 $x$ 和 $y$ ，它们分别都在一个连续区间内

于是把每一种情况用前缀和优化一下即可

时间复杂度 $O(n^3)$

```cpp
#include <bits/stdc++.h>

#define int long long int

using namespace std;

const int N = 1.5e2 + 10, mod = 1e9 + 7;
int n;
char s[N][N];
int f[N][N][N][2][2]; // 见状态设计
int ss[N];

void add(int &x, int ad) { x = (x + (ad % mod + mod)) % mod; }

namespace SubTask {
/** O(n^5): 照状态直接转移即可，能拿到50pts高分
 */
void solve() {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            ss[j] = ss[j - 1] + (s[i][j] == 'G');
        for (int l = 1; l <= n; l++) {
            for (int r = l; r <= n; r++) { // 枚举这一个区间 [l, r]
                if (ss[r] - ss[l - 1] != r - l + 1)
                    continue;  // 没有填满色
                f[i][l][r][0][0] = 1; // 只有一层[l,r]的情况也要算在内
                for (int x = 1; x <= n; x++)
                    for (int y = x; y <= n; y++) {  // 枚举上一个区间[x, y]
                        // 注意到变化趋势：0可以转到1，但是1不可以转到0，如果是l/r不变那么认为l/r的变化趋势也不变

                        // l, r都扩张，变化趋势不变
                        if (l <= x && y <= r)
                            add(f[i][l][r][0][0], f[i - 1][x][y][0][0]);
                        // l一定保证扩张，分讨r是收缩/不变的两种情况
                        if (l <= x && x <= r && r < y)
                            add(f[i][l][r][0][1], f[i - 1][x][y][0][0]);
                        if (l <= x && x <= r && r <= y)
                            add(f[i][l][r][0][1], f[i - 1][x][y][0][1]);

                        // r一定保证扩张，分讨l是收缩/不变的两种情况
                        if (x < l && l <= y && y <= r)
                            add(f[i][l][r][1][0], f[i - 1][x][y][0][0]);
                        if (x <= l && l <= y && y <= r)
                            add(f[i][l][r][1][0], f[i - 1][x][y][1][0]);

                        // 分讨l是收缩/不变及r是收缩/不变的四种情况
                        if (x <= l && y >= r)
                            add(f[i][l][r][1][1], f[i - 1][x][y][1][1]);
                        if (x < l && y >= r)
                            add(f[i][l][r][1][1], f[i - 1][x][y][0][1]);
                        if (x <= l && y > r)
                            add(f[i][l][r][1][1], f[i - 1][x][y][1][0]);
                        if (x < l && y > r)
                            add(f[i][l][r][1][1], f[i - 1][x][y][0][0]);
                    }
                for (int c = 0; c < 4; c++)
                    add(ans, f[i][l][r][c >> 1][c & 1]);
            }
        }
    }
    printf("%lld\n", ans);
}
};

namespace FullSolution {
/** O(n^3): 对于O(n^5)的算法，考虑优化
 *  发现每次f[i][...]转移加上的就是一个f[i-1][...]的子矩阵和
 *  所以去掉枚举x和y的两层，改为加上上一维对应f的子矩阵和
 */
int sf[N][N][2][2]; // f的前缀和 (滚掉[i]项)
void init_sf(int i) { // 处理f[i][...]的前缀和数组sf
    memset(sf, 0, sizeof(sf));
    for (int c = 0; c < 4; c++)
        for (int l = 1; l <= n; l++)
            for (int r = 1; r <= n; r++) {
                int p = c >> 1, q = c & 1;
                add(sf[l][r][p][q], sf[l - 1][r][p][q] + sf[l][r - 1][p][q] - sf[l - 1][r - 1][p][q] + f[i][l][r][p][q]);
            }
}
int getsum(int l1, int r1, int l2, int r2, int p, int q) { // 求子矩阵和
    int res = 0;
    l1--, l2--;
    add(res, sf[r1][r2][p][q] - sf[l1][r2][p][q] - sf[r1][l2][p][q] + sf[l1][l2][p][q]);
    return res;
}
void solve() {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            ss[j] = ss[j - 1] + (s[i][j] == 'G');
        for (int l = 1; l <= n; l++) {
            for (int r = l; r <= n; r++) { // 枚举这一个区间[l, r]
                if (ss[r] - ss[l - 1] != r - l + 1)
                    continue;  // 没有填满色
                add(f[i][l][r][0][0], 1 + getsum(l, r, l, r, 0, 0));
                add(f[i][l][r][0][1], getsum(l, r, r + 1, n, 0, 0)
                                    + getsum(l, r, r, n, 0, 1));
                add(f[i][l][r][1][0], getsum(1, l - 1, l, r, 0, 0)
                                    + getsum(1, l, l, r, 1, 0));
                add(f[i][l][r][1][1], getsum(1, l, r, n, 1, 1)
                                    + getsum(1, l - 1, r + 1, n, 0, 0)
                                    + getsum(1, l - 1, r, n, 0, 1)
                                    + getsum(1, l, r + 1, n, 1, 0));
                // 每一个getsum()都对应之前的一个分讨
                for (int c = 0; c < 4; c++)
                    add(ans, f[i][l][r][c >> 1][c & 1]);
            }
        }
        init_sf(i); // 更新一下f的前缀和
    }
    printf("%lld\n", ans);
}
};

main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", s[i] + 1);
    // SubTask::solve(); // 这里是O(n^5)的做法
    FullSolution::solve(); // 这是正解
    return 0;
}

```

---

## 作者：Anonymely (赞：0)

雪豹书上的原来是这个题吗。

发现合法连通块一定长的是凸多边形，数据范围很小，考虑直接维护，$f_{i,l,r,0/1,0/1}$ 表示第 $i$ 行选在 $[l,r]$，且左端处于伸/缩，右端处于伸/缩。

转移能二维前缀和优化。


```cpp
#include <bits/stdc++.h>
using namespace std;

#define QwQ01AwA return 0
#define ll long long
#define look_time cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n'
template <typename T> void ckmax(T &x, const T y) {x = max(x, y);}
template <typename T> void ckmin(T &x, const T y) {x = min(x, y);}

const int N = 155;
const int mod = 1e9 + 7;
int n, cnt[N]; string s;
ll f[N][N][N][2][2];
ll qsum(int i, int x1, int x2, int y1, int y2, int p, int q) {
	return ((f[i][x2][y2][p][q] - f[i][x1 - 1][y2][p][q] - f[i][x2][y1 - 1][p][q] + f[i][x1 - 1][y1 - 1][p][q]) % mod + mod) % mod;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		cin >> s; s = " " + s;
		for (int j = 1; j <= n; j++) cnt[j] = cnt[j - 1] + (s[j] == 'G');
		for (int l = 1; l <= n; l++) {
			for (int r = l; r <= n; r++) {
				if (cnt[r] - cnt[l - 1] != r - l + 1) continue;
				f[i][l][r][1][1] = (qsum(i - 1, l, r, l, r, 1, 1) + 1) % mod;
				f[i][l][r][1][0] = (qsum(i - 1, l, r, r + 1, n, 1, 1) + qsum(i - 1, l, r, r, n, 1, 0)) % mod;
				f[i][l][r][0][1] = (qsum(i - 1, 1, l - 1, l, r, 1, 1) + qsum(i - 1, 1, l, l, r, 0, 1)) % mod;
				f[i][l][r][0][0] = (qsum(i - 1, 1, l - 1, r + 1, n, 1, 1) + qsum(i - 1, 1, l - 1, r, n, 1, 0) + qsum(i - 1, 1, l, r + 1, n, 0, 1) + qsum(i - 1, 1, l, r, n, 0, 0)) % mod;
				for (int p = 0; p < 2; p++) {
					for (int q = 0; q < 2; q++) {
						ans = (ans + f[i][l][r][p][q]) % mod;
					}
				}
				// cerr << l << ' ' << r << ' ' << f[i][l][r][1][1] << ' ' << f[i][l][r][1][0] << ' ' << f[i][l][r][0][1] << ' ' << f[i][l][r][0][0] << '\n'; 
			}
		}
		// cerr << ans << '\n';
		for (int p = 0; p < 2; p++) {
			for (int q = 0; q < 2; q++) {
				for (int l = 1; l <= n; l++) {
					for (int r = 1; r <= n; r++) {
						f[i][l][r][p][q] = (f[i][l][r][p][q] + f[i][l][r - 1][p][q]) % mod;
					}
				}
				for (int l = 1; l <= n; l++) {
					for (int r = 1; r <= n; r++) {
						f[i][l][r][p][q] = (f[i][l - 1][r][p][q] + f[i][l][r][p][q]) % mod;
					}
				}
			}
		}
	}
	cout << ans << '\n';
	QwQ01AwA;
}
```

---

## 作者：ZXZ_ (赞：0)

# P7532 [USACO21OPEN] Balanced Subsets P

## 题意

求在给定的字符矩阵中符合题意的凸多边形个数。



## 做法

考虑 DP。

设状态：$f_{i,l,r,0/1,0/1}$ 表示枚举到第 $i$ 行，选择区间 $l$ 到 $r$ 的方案数。而两个 $0$，$1$ 位表示左右当前区间的左右端点是由上一行的左右端点扩展或缩小来的（相等也属于缩小）。
我们易得一个 $n^5$ 的转移。

### 优化

考虑要怎么优化。我们举个例子，我们在转移状态：$f_{i,l,r,0,0}$ 时，必然要从状态 $f_{i-1,x,y,0,0}$ 转移而来，$x$，$y$ 是枚举的上一行的左右端点。
那么我们将 $x$，$y$ 的值列举成矩阵的形式，可以发现我们所加的是属于矩阵中的一个子区间的值。
那么可以用二维前缀和进行优化。通过得知上一行的左右端点的区间和上一行左右端点的扩展或缩减情况进行转移。

复杂度：

$O(n^3)$

不过要注意统计答案涉及到减操作时，因为取了模，要先加上 mod 再模 mod 防止出现负数。

```cpp
#include<bits/stdc++.h>
#define N 151
#define mod 1000000007
#define int long long
using namespace std;
int n,f[N][N][N][2][2],g[N][N][N][2][2],sum[N],ans;
char s[N][N];
int getx(int i,int l,int r,int x,int y,int p,int q){return 	(g[i][r][y][p][q]-g[i][r][x-1][p][q]-g[i][l-1][y][p][q]+g[i][l-1][x-1][p][q])%mod;}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			sum[j]=sum[j-1]+(s[i][j]=='G');
		for(int l=n;l>=1;l--)
			for(int r=l;r<=n;r++)
				if(sum[r]-sum[l-1]==r-l+1){
					f[i][l][r][0][0]=(getx(i-1,l,r,l,r,0,0)+1)%mod,f[i][l][r][0][1]=(getx(i-1,l,r,r+1,n,0,0)+getx(i-1,l,r,r,n,0,1))%mod;
					f[i][l][r][1][0]=(getx(i-1,1,l-1,l,r,0,0)+getx(i-1,1,l,l,r,1,0))%mod;
					f[i][l][r][1][1]=(getx(i-1,1,l-1,r+1,n,0,0)+getx(i-1,1,l-1,r,n,0,1))%mod,f[i][l][r][1][1]=(f[i][l][r][1][1]+getx(i-1,1,l,r,n,1,1)+getx(i-1,1,l,r+1,n,1,0))%mod;
					ans=(ans+f[i][l][r][0][0]+f[i][l][r][0][1])%mod,ans=(ans+f[i][l][r][1][0]+f[i][l][r][1][1])%mod;
				}
		for(int l=1;l<=n;l++)for(int r=1;r<=n;r++)for(int p=0;p<2;p++)for(int q=0;q<2;q++)g[i][l][r][p][q]=(g[i][l][r-1][p][q]+g[i][l-1][r][p][q]-g[i][l-1][r-1][p][q]+f[i][l][r][p][q])%mod;
	}
	printf("%lld",(ans+mod)%mod);
}
```

---

## 作者：xiaofu15191 (赞：0)

今天模拟赛的 T1。原本 DP 状态设对了，但是连 $O(n^5)$ 的暴力都写炸，只好去打了暴力。

阅读题目，可以想到，每一行选的都是一个连续的区间。从上往下，区间的边界可以先往外延伸再缩回，但是不可以先缩回再延伸。

先设 DP 状态 $f_{i,l,r,p,q}$ 表示当前在第 $i$ 行选择了区间 $[l,r]$，$p=1$ 表示从上往下，区间左边界没有缩回过，可以继续延伸，$p=0$ 表示不可继续延伸，右边界同理。

转移时，对于确定的区间 $[x,y]$，我们要将其转移到当前所在的 $[l,r]$，转移的方法是唯一的，想到可以分 $p,q$ 的情况统计 DP 数组的前缀和省去 $[x,y]$ 的枚举。前缀和不用考虑区间左右边界的顺序，按照正常的二维前缀和处理即可。

现在考虑如何转移。设我们获取数组前缀和的函数为 $\operatorname{pre}(i,l_1,r_1,l_2,r_2,p,q)$，表示获取第 $i$ 行中，左边界位于 $[l_1,r_1]$，右边界位于 $[l_2,r_2]$，边界可延展状态为 $(p,q)$ 的数组前缀和。

- 对于 $f_{i,l,r,1,1}$，因为两边界都可延伸，显然我们应当从 $[l,r]$ 区间中的子区间转移而来，所以 $f_{i,l,r,1,1}=\operatorname{pre}(i-1,l,r,l,r,1,1)+1$。

- 对于 $f_{i,l,r,1,0}$，分两种情况。从可延伸的右边界转移为不可延伸，那么它一定有「缩进来」这个操作，所以从 $\operatorname{pre}(i-1,l,r,r+1,n,1,1)$ 转移过来；从不可延伸的右边界转移，那么前一个状态的右边界一定大于等于 $r$，从 $\operatorname{pre}(i-1,l,r,r,n,1,0)$ 转移。

- 对于 $f_{i,l,r,0,1}$ 大体同上，$f_{i,l,r,0,0}$ 的情况也是上面几种的综合。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const long long mod=1000000007;
long long n,ans,f[160][160][160][2][2],sum[160][160][160][2][2],check[160][160];//1 means spread
char graph[160][160];
long long get_pre(long long i,long long l1,long long r1,long long l2,long long r2,long long p1,long long p2)
{
	return (sum[i][r1][r2][p1][p2]-sum[i][l1-1][r2][p1][p2]-sum[i][r1][l2-1][p1][p2]+sum[i][l1-1][l2-1][p1][p2])%mod;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			cin>>graph[i][j];
			check[i][j]=check[i][j-1]+(graph[i][j]=='G');
		}
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		for(long long l=1;l<=n;l++)
			for(long long r=l;r<=n;r++)
			{
				if(r-l+1!=check[i][r]-check[i][l-1]) continue;
				f[i][l][r][1][1]=get_pre(i-1,l,r,l,r,1,1)+1;
				f[i][l][r][1][0]=get_pre(i-1,l,r,r+1,n,1,1)+get_pre(i-1,l,r,r,n,1,0);
				f[i][l][r][0][1]=get_pre(i-1,1,l-1,l,r,1,1)+get_pre(i-1,1,l,l,r,0,1);
				f[i][l][r][0][0]=get_pre(i-1,1,l-1,r+1,n,1,1)+get_pre(i-1,1,l,r+1,n,0,1)+get_pre(i-1,1,l,r,n,0,0)+get_pre(i-1,1,l-1,r,n,1,0);
				f[i][l][r][1][1]%=mod;
				f[i][l][r][1][0]%=mod;
				f[i][l][r][0][1]%=mod;
				f[i][l][r][0][0]%=mod;
				for(long long p1=0;p1<=1;p1++)
					for(long long p2=0;p2<=1;p2++)
						ans=(ans+f[i][l][r][p1][p2])%mod;
			}
		for(long long l=1;l<=n;l++)
			for(long long r=1;r<=n;r++)
				for(long long p1=0;p1<=1;p1++)
					for(long long p2=0;p2<=1;p2++)
						sum[i][l][r][p1][p2]=((sum[i][l-1][r][p1][p2]+sum[i][l][r-1][p1][p2]-sum[i][l-1][r-1][p1][p2])%mod+f[i][l][r][p1][p2])%mod;
	}
	cout<<(ans+mod)%mod<<endl;
}
```

---

