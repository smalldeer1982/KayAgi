# Mathematics Curriculum

## 题目描述

Let $ c_1, c_2, \ldots, c_n $ be a permutation of integers $ 1, 2, \ldots, n $ . Consider all subsegments of this permutation containing an integer $ x $ . Given an integer $ m $ , we call the integer $ x $ good if there are exactly $ m $ different values of maximum on these subsegments.

Cirno is studying mathematics, and the teacher asks her to count the number of permutations of length $ n $ with exactly $ k $ good numbers.

Unfortunately, Cirno isn't good at mathematics, and she can't answer this question. Therefore, she asks you for help.

Since the answer may be very big, you only need to tell her the number of permutations modulo $ p $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

A sequence $ a $ is a subsegment of a sequence $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 说明/提示

In the first test case, there are four permutations: $ [1, 3, 2, 4] $ , $ [2, 3, 1, 4] $ , $ [4, 1, 3, 2] $ and $ [4, 2, 3, 1] $ .

Take permutation $ [1, 3, 2, 4] $ as an example:

For number $ 1 $ , all subsegments containing it are: $ [1] $ , $ [1, 3] $ , $ [1, 3, 2] $ and $ [1, 3, 2, 4] $ , and there're three different maxima $ 1 $ , $ 3 $ and $ 4 $ .

Similarly, for number $ 3 $ , there're two different maxima $ 3 $ and $ 4 $ . For number $ 2 $ , there're three different maxima $ 2 $ , $ 3 $ and $ 4 $ . And for number $ 4 $ , there're only one, that is $ 4 $ itself.

## 样例 #1

### 输入

```
4 3 2 10007```

### 输出

```
4```

## 样例 #2

### 输入

```
6 4 1 769626776```

### 输出

```
472```

## 样例 #3

### 输入

```
66 11 9 786747482```

### 输出

```
206331312```

## 样例 #4

### 输入

```
99 30 18 650457567```

### 输出

```
77365367```

# 题解

## 作者：wurzang (赞：17)

### 题意

- 我们定义一个排列中的数字 $x$ 是好的，当且仅当包含它的子串的最大值的个数为 $m$

- 现在 Cirno 想问你，有多少长度为 $n$ 的排列满足好的数字有恰好 $k$ 个。

### 题解


出题人逆大天，$\mathcal{O}(n^5)$ 过 100，真是牛逼嗷

首先我们考虑给你一个排列，怎么确定里面的数字是好的。

假设这个数的位置是 $x$，那么子串最大值的个数就是 $[1\ldots x]$ 中的后缀最大值个数加上 $[x\ldots n]$ 的前缀最大值个数。正确性很显然。

根据笛卡尔树的经典结论，这个东西就是笛卡尔树上 $x$ 的层数。具体证明大概就是，只有 $[1\ldots x]$ 中的后缀最大值能成为 $x$ 的祖先，如果一个点 $y$ 它后面有数字大于它的话，那么这个数字会在构造笛卡尔树的过程中，把 $y$ 放到左儿子，$x$ 放到右儿子，这样点 $y$ 就不可能成为 $x$ 的祖先。反之，后缀最大值都能成为 $x$ 的祖先。而 $[x\ldots n]$ 的证明则同理。

于是问题转化成，有多少形态不同的笛卡尔树满足其层数为 $m$ 的节点数等于 $k$。

这个显然可以 dp，设 $f_{i,j,k}$ 为大小为 $i$ 的子树中，有多少点层数为 $m$，且这个子树的根离根节点的距离为 $j$


转移有 
$$
f_{i,j,k}=\sum_a\sum_b {i-1 \choose a} \times f_{a,j+1,b} \times f_{i-1-a,j+1,k-b-[j==m]}
$$

但是这样是过不去的，因为出题人会卡你常数，你需要加个剪枝，比如说我们发现一个大小为 $i$ 的子树中同一层的节点个数最多为 $\dfrac{i+1}{2}$，我们可以根据这个剪枝，于是就能常数除以 4。

我写题解的原因就是为了这个卡常（

具体看[代码](https://codeforces.com/contest/1580/submission/130537073)



---

## 作者：Miko35 (赞：12)

题意：

求满足以下条件的排列个数：

- 长度为 $n$。
- 恰有 $k$ 个数满足：所有包含这个数的区间中，不同的最大值的个数恰有 $m$ 个。

---

$\textrm{Solution}$：

除去这个 100 的范围，是一道好的练手题。

将“所有包含这个数的区间中，不同的最大值的个数恰有 $m$ 个”的数称作 $m$ - 好数，那么用 $f_{i,j,k}$ 表示：长度为 $i$ 的序列，$k$ - 好数有 $j$ 个的方案数。

考虑如何转移 $f_{i,j,k}$：枚举最大值的位置 $p$，左右两边只需要保留偏序关系，可以看作是长度为 $p-1$ 和 $i-p$ 的两个排列，划分方案数就是 $\dbinom{n-1}{p-1}$。

跨越最大值的区间显然只会对不同最大值个数有 $1$ 的贡献，需要找的其实是左右两边的 $(k-1)$ - 好数。所以可以再枚举一维 $c$ 表示左半边的 $(k-1)$ - 好数个数，右半边即为 $j-c-[k=1]$（中间的最大值是 $1$ - 好数，要判掉）。

所以有转移：

$$f_{i,j,k}=\sum_p \binom{n-1}{p-1}\sum_c f_{p-1,c,k-1}\cdot f_{i-p,j-c-[k=1],k-1}$$

时间复杂度 $O(n^5)$，需要注意的是：

- $p=1$ 或 $p=i$ 需要特判。
- 如 $j=0$ 且 $k>i$ 的边界情况需要注意，按定义计算。
- 乘法很慢，可以先判断是否为 $0$ 再转移。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define rgi register int
#define FOR(i,a,b) for(rgi i=a,i##i=b;i<=i##i;++i)
#define ROF(i,a,b) for(rgi i=a,i##i=b;i>=i##i;--i)
using namespace std;
const int N=110;
int n,m,K,P,f[N][N][N],fac[N],C[N][N];
inline int get(int i,int j,int k){
	if(!j&&(k>i||k<1))return fac[i];
	return f[i][j][k];
}
signed main(){
	scanf("%d%d%d%d",&n,&m,&K,&P),f[1][1][1]=C[0][0]=fac[0]=1;
	FOR(i,1,n){
		C[i][0]=1,fac[i]=1ll*fac[i-1]*i%P;
		FOR(j,1,i)C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
	}
	FOR(i,2,n)FOR(j,0,min(i,K))FOR(k,1,min(i-j+1,m)){
		rgi G=j-(k==1),X,Y;
		f[i][j][k]=(get(i-1,G,k-1)*2)%P;
		FOR(p,2,i-1)FOR(c,0,min(p,G))if((X=get(p-1,c,k-1))&&(Y=get(i-p,G-c,k-1))){
			f[i][j][k]=(f[i][j][k]+1ll*X*Y%P*C[i-1][p-1])%P;
		}
	}
	printf("%d",f[n][K][m]);
	return 0;
}
```




---

## 作者：vectorwyx (赞：10)

对于 $1\sim i$  的排列，考虑其最大值 $i$ 在哪个位置。如果 $i$ 在位置 $w$，那么左边就变成了 $n=w-1,m=m-1$ 的版本，右边就变成了 $n=i-w,m=m-1$ 的版本

这样并不能转移，再加一维 $k$ 表示好数有 $k$ 个的方案数，然后枚举左边贡献多少个好数，这样是 $O(n^5)$ 的。具体地，令 $f(i,j,k)$ 表示 $n=i,m=j,k=k$ 时的答案，那么 $f(i,j,k)=\sum f(w-1,j-1,t)\cdot f(i-w,j-1,k-(j==1)-t)\cdot \binom{i-1}{w-1}$

初始化和卡常一堆细节，感谢切队指导。有一个挺重要的点是对于 $j>i$，$f(i,j,0)$ 应当初始化为 $i!$。还有一个很有力的常数优化是如果 $f(w-1,j-1,t),f(i-w,j-1,k-(j==1)-t)$ 中有一个值为 $0$ 那就不要转移。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#define pb push_back
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define db double
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) printf("%lld ",*(a+i));puts("");}

const int N=105;
int qlr,n,m,kk,C[N][N],f[N][N][N],fac[N];

signed main(){
	cin>>n>>m>>kk>>qlr;
	//f[1][1][1]=1;
	fo(i,0,n) f[0][i][0]=1;
	fac[0]=fac[1]=1;fo(i,2,n) fac[i]=(ll)fac[i-1]*i%qlr;
	C[0][0]=1;
	fo(i,1,n){
		C[i][0]=1;
		fo(j,1,i) C[i][j]=(C[i-1][j-1]+C[i-1][j])%qlr; 
		//out(C[i],0,i);
	}
	fo(i,0,n) f[0][i][0]=1;
	//fo(i,0,m) f[1][i][0]=1;
	//f[1][1][1]=1;f[1][1][0]=0;
	fo(i,1,n){
		f[i][1][1]=fac[i];
		fo(j,i+1,n) f[i][j][0]=fac[i];
		fo(j,2,min(i,m))
			fo(k,0,min(i-j+1,kk)){
				f[i][j][k]=(f[i][j][k]+(f[i-1][j-1][k-(j==1)]<<1))%qlr;
				fo(w,2,i-1)//枚举 i 所在位置，再枚举左半边要贡献多少个好数 
					fo(t,0,k-(j==1)) if(f[w-1][j-1][t]&&f[i-w][j-1][k-(j==1)-t])
						f[i][j][k]=(f[i][j][k]+(ll)f[w-1][j-1][t]*f[i-w][j-1][k-(j==1)-t]%qlr*C[i-1][w-1])%qlr;
				//printf("%lld,%lld,%lld:%lld\n",i,j,k,f[i][j][k]);
			}		
	}

	cout<<f[n][m][kk];
	return 0;
}
/*
-------------------------------------------------
*/


```


---

## 作者：GIFBMP (赞：5)

写一发题解纪念一下这一道自己想出来的 DP 好题。

首先我们发现，对于一个排列，对其建立笛卡尔树之后，包含一个下标的区间中不同最大值的种数就等于这个点在笛卡尔树上的深度。显然每个排列与一个带标号笛卡尔树唯一对应（以下的“笛卡尔树”均指带标号的笛卡尔树），那么原问题就转化为求有 $n$ 个节点，有 $k$ 个深度为 $m$ 的节点的笛卡尔树有多少种。

于是我们可以设 $f_{i,j,k}$ 表示从小到大考虑了 $i$ 个点，当前笛卡尔树上有 $j$ 个深度为 $k$ 的节点，笛卡尔树共有多少种不同的形态。我们发现，由于 $i$ 是当前权值最大的节点，故 $i$ 一定为笛卡尔树的根。于是枚举左右子树各有多少节点即可。那么对于 $k>1$ 的情况，我们可以得出：

$$f_{i,j,k}=\sum_{l=0}^{i-1}\sum_{p=0}^{j}C_{i-1}^l\times f_{l,p,k-1}\times f_{i-1-l,j-p,k-1}$$

那么对于 $k=1$ 的情况，我们设 $g_i$ 表示节点数为 $i$ 的不同笛卡尔树数量，那么可以得出：

$$g_i=
\begin{cases}
1& 0\le i\le 1\\
\sum_{j=0}^{i-1}C_{i-1}^j\times g_j\times g_{i-1-j}&i>1\\
\end{cases}
$$

于是有：

$$f_{i,j,1}=
\begin{cases}
g_i&j=1\\
0&\text{otherwise}
\end{cases}
$$

那么就可以得到一个 $\Theta(n^5)$ 的做法。但是显然是跑不过去这题的，我们考虑剪枝：

1.当 $k>i$ 时，若 $j=0$，$f_{i,j,k}=g_i$，否则 $f_{i,j,k}=0$；

2.乘法取模运算较慢，当转移的三项中任何一项为 $0$ 就可以直接跳过。

于是就可以通过本题。时间复杂度为 $\Theta(n^5)$，但是带一个很小的常数。

Code:

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std ;
int n , m , K , mod ;
typedef long long ll ;
ll c[110][110] , f[110][110][110] , g[110] ;
int main () {
	scanf ("%d%d%d%d" , &n , &m , &K , &mod) ;
	if (m > n || (m == n && K > 1)) return !printf ("0") ;
	for (int i = 0 ; i <= n ; i++) c[i][0] = 1 ;
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 ; j <= i ; j++)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod ;
	f[1][1][1] = f[1][0][0] = 1 ;
	for (int i = 0 ; i <= m ; i++) f[0][0][i] = 1 ;
	for (int i = 2 ; i <= m ; i++) f[1][0][i] = 1 ;
	g[0] = g[1] = 1 ;
	for (int i = 2 ; i <= n ; i++)
		for (int j = 0 ; j < i ; j++)
			g[i] = (g[i] + c[i - 1][j] * g[j] % mod * g[i - 1 - j] % mod) % mod ;
	for (int i = 2 ; i <= n ; i++) {
		f[i][1][1] = g[i] ;
		for (int k = 2 ; k <= m ; k++) {
			if (k > i) {f[i][0][k] = g[i] ; continue ;}
			for (int j = 0 ; j <= K ; j++) {
				for (int l = 0 ; l <= j ; l++)
					for (int p = 0 ; p < i ; p++) {
						if (!c[i - 1][p] || !f[p][l][k - 1] || !f[i - 1 - p][j - l][k - 1]) continue ;
						f[i][j][k] = (f[i][j][k] + c[i - 1][p] * f[p][l][k - 1] % mod * f[i - 1 - p][j - l][k - 1] % mod) % mod ;
					}
			}
		}
	}
	printf ("%lld\n" , f[n][K][m]) ;
	return 0 ;
}
```

---

## 作者：TernaryTree (赞：2)

流汗黄豆了，出题人是不是觉得自己 $\Theta(n^5)$ 能过 $n\le 100$ 很炫酷/tx。评 *2600 纯纯是因为赛时大家不敢写吧。

考虑建出笛卡尔树，并发现“所有包含这个数的区间中，不同的最大值的个数”恰为这个数在笛卡尔树上的深度（根节点深度为 $1$）。那么就是让你求满足笛卡尔树深度为 $m$ 的点有 $k$ 个的排列的个数。

dp，$f_{i,j,k}$ 表示 $i$ 个数的排列，笛卡尔树上深度为 $j$ 的有 $k$ 个的方案数。转移枚举根节点的位置 $p$ 与分给左子树 $q$ 个深度为 $j$ 的结点，贡献是 $f_{p-1,j-1,q}f_{i-p,j-1,k-q}\binom{i-1}{p-1}$，最后组合数的意义是选 $p-1$ 个数放到左边去当成 $1\sim p-1$。

这里是 $\Theta(n^5)$ 的，但是似乎出题人并不打算让我们这么轻松过。正常实现很慢，但是很多答案都是 $0$。考虑设 $g_{i,j}$ 表示长为 $i$ 的排列，深度为 $j$ 的最多有多少个，这可以简单做到 $\Theta(n^3)$。若 $z>g_{n,m}$ 则无解输出 $0$。看起来这样就跑的很快了，加上一些经典常数优化即可通过。

```cpp
#include <bits/stdc++.h>
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, r, l) for (int i = (r); i >= (l); --i)
#define gc getchar
#define pc putchar

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;
using ll = long long;

const int maxn = 2e2 + 10;
const bool multidata = 0;

template<typename T = int>
T read() {
	T x = 0, f = 1; char c = gc();
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = gc(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = gc();
	return x * f;
}

template<typename T = int>
void write(T x) {
	if (x < 0) pc('-'), x = -x;
	if (x < 10) return void (pc(x + '0'));
	write<T>(x / 10), pc(x % 10 + '0');
}

int n, m, z, mod;
int f[maxn][maxn][maxn];

int fac[maxn];

void init() {
	fac[0] = 1; rep(i, 1, maxn - 1) fac[i] = (ll) fac[i - 1] * i % mod;
}

int fk[maxn][maxn];

int C(int n, int m) {
	if (n < 0 || n < m || m < 0) return 0;
	return fk[n][m];
}

int g[maxn][maxn]; 

void fake_main() {
	n = read(), m = read(), z = read(), mod = read();
	g[1][1] = 1;
	rep(i, 2, n) {
		g[i][1] = 1;
		rep(j, 2, i) rep(p, 1, i) g[i][j] = max(g[i][j], g[p - 1][j - 1] + g[i - p][j - 1]);
	}
//	write(g[n][m]), pc('\n');
	if (z > g[n][m]) return void (puts("0"));
	rep(i, 0, n) {
		fk[i][0] = fk[i][i] = 1;
		rep(j, 1, i - 1) fk[i][j] = (fk[i - 1][j - 1] + fk[i - 1][j]) % mod;
	}
	init();
	f[1][1][1] = 1;
	rep(i, 0, n) f[0][i][0] = 1;
	rep(i, 0, n) f[1][i][0] = 1; f[1][1][0] = 0;
	rep(i, 2, n) {
		f[i][1][1] = fac[i];
		rep(j, 2, min(i, m)) {
			rep(k, 0, min(i - j + 1, z)) {
//				cout << i << " " << j << " " << k << ": " << " ";
//				cout << endl;
				rep(p, 1, i) {
					rep(q, 0, k) {
//						cout << " " << p - 1 << " " << j - 1 << " " << q << " and " << i - p << " " << j - 1 << " " << k - q << " " << f[p - 1][j - 1][q] * f[i - p][j - 1][k - q] << endl;
						(f[i][j][k] += (ll) f[p - 1][j - 1][q] * f[i - p][j - 1][k - q] % mod * C(i - 1, p - 1) % mod) %= mod;
					}
				}
//				cout << f[i][j][k] << endl;
			}
		}
		rep(j, min(i, m) + 1, m) f[i][j][0] = fac[i];
	}
	write(f[n][m][z]); 
}

signed main() {
//	freopen("CF1580B.out", "w", stdout);
	int T = multidata ? read() : 1;
	while (T--) fake_main();
	return 0;
}
/*
j <= i, k <= i - j + 1
*/

```

---

## 作者：一只绝帆 (赞：2)

想了一晚上 $O(n^4)$ 结果标程是 $O(n^5)$ 的。

这个故事告诉我们没事不要摆，$O(n^5)$ 过 $100$。

首先你想一想这个限制，发现相当于求有多少长为 $n$ 的排列对应的笛卡尔树满足恰有 $k$ 个深度为 $m$ 的节点。

考虑 dp，在这种树形态的 dp 中虽然没有确定形态的树，但你依然可以沿用子树 dp 的套路，从子树转移过来。

（以下原题中的 $k$ 用 $K$ 表示。）

设 $f_{i,j,k}$ 为子树大小为 $i$，树根在原树的深度为 $j$，子树中有 $k$ 个深度为 $m$ 的节点的方案数。

转移枚举左子树有 $l$ 个节点以及有 $p$ 个深度为 $m$ 的节点。

$$f_{i,j,k}\gets\sum_{l< i}\binom{i-1}{l}\sum_{p+[j==m]\le k}f_{l,j+1,p}f_{i-l-1,j+1,k-p-[j==m]}$$

初始条件是 $f_{0,j,0}=1$。

复杂度 $O(n^5)$，但是严重跑不满，很多维都是有范围的。

关于为什么乘上 $\binom{i-1}{l}$，这是因为一棵笛卡尔树只需要保证上面大于下面即可，所以 $i$ 个数里除了最大值必须作根，剩的可以随便选作左子树。

转移显然是先倒序枚举 $j$，再任意顺序枚举 $i,k,l,p$。

但是你发现 $i$ 的范围不好界定，跑的贼慢，然后你发现最外层正序枚举 $i$ 也可以，还有一个剪枝的结论是大小为 $x$ 的二叉树同一层最多有 $\left\lceil\frac{x}{2}\right\rceil$ 个点。

还有对于 $j>m$，没必要跑那么多。

Code：

```cpp
#include<bits/stdc++.h>
#define Z(x,y) (x=(x+(y))%p)
#define F(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define UF(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define deb(...) fprintf(stderr,__VA_ARGS__)
using namespace std;typedef long long ll;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char *p1,*p2,buf[1<<21];
int read() {
    int s=0,w=0;char ch=gc();
    while(ch<'0'||ch>'9') w|=(ch=='-'),ch=gc();
    while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=gc();
    return w?-s:s;
} const int N=105;
int f[N][N][N],C[N][N],ans;int n,m,K,md;
void init(int n) {
    F(i,0,n) C[i][0]=1;
    F(i,1,n) F(j,1,i) C[i][j]=(0ll+C[i-1][j-1]+C[i-1][j])%md;
}
int main() {
    n=read();m=read();K=read();md=read();init(n);UF(j,n+1,1) f[0][j][0]=1;
    F(i,1,n) UF(j,n-i+1,1) F(l,0,i-1) {
        if(j<=m) F(k,0,i+1>>1) F(p,0,min(k-(j==m),l+1>>1)) {
            f[i][j][k]=(0ll+f[i][j][k]+1ll*C[i-1][l]*f[l][j+1][p]%md*f[i-1-l][j+1][k-(j==m)-p]%md)%md;
        } else f[i][j][0]=(0ll+f[i][j][0]+1ll*C[i-1][l]*f[l][j+1][0]%md*f[i-1-l][j+1][0]%md)%md;
    } cout<<f[n][1][K];
    return 0;
}

```


---

## 作者：daniEl_lElE (赞：2)

考虑第二个条件，等价于建出笛卡尔树深度为 $m$ 的位置有 $k$ 个。

考虑 $dp_{i,j,k}$ 表示子树大小为 $i$，有 $j$ 个深度为 $m$ 的位置，深度为 $k$ 的方案数，枚举左右子树大小和深度为 $m$ 的位置数。这样是 $O(n^5)$ 的，常数很小。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
int dp[105][105][105],C[105][105];
signed main(){
	int n,m,k,p;
	cin>>n>>m>>k>>p;
	const int mod=p;
	for(int i=0;i<=100;i++) C[i][0]=1;
	for(int i=1;i<=100;i++) for(int j=1;j<=n;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	for(int i=1;i<=n+1;i++) dp[0][0][i]=1;
	for(int i=1;i<=n;i++){//length
		for(int j1=0;j1<i;j1++){//length of part 1
			int j2=i-j1-1;//length of part 2
			for(int g=1;g<=n-i+1;g++){
				if(g<=m)
					for(int l1=0;l1<=min(j1,k);l1++){
						for(int l2=0;l2<=min(j2,k-l1);l2++){
							(dp[i][l1+l2+(g==m)][g]+=dp[j1][l1][g+1]*dp[j2][l2][g+1]%mod*C[i-1][j1])%=mod;
						}
					}
				else (dp[i][0][g]+=dp[j1][0][g+1]*dp[j2][0][g+1]%mod*C[i-1][j1])%=mod;
			}
		}
	}
	cout<<dp[n][k][1];
	return 0;
}

```

---

## 作者：Umbrella_Leaf (赞：1)

### 题意简述

> 求有多少长度为 $n$ 的排列满足笛卡尔树上深度为 $m$ 的点有 $k$ 个。

### 思路分析

直接 DP，状态就是 $dp_{n,m,k}$ 表示有多少长度为 $n$ 的排列满足笛卡尔树上深度为 $m$ 的点有 $k$ 个。

转移时枚举笛卡尔树其中一个儿子的大小和里面深度为 $m$ 的个数，有：

$$dp_{n,m,k}=\sum_i\sum_jdp_{i,m-1,j}dp_{n-i-1,m-1,k-j}\dbinom{n-1}{i}$$

直接转移就能过！$O(n^5)$ 冲 $n=100$！

题解区里都说要卡常，但是状态根本不满，记搜不香吗……

### 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
int mod;
int fac[105],C[105][105];
int dp[105][105][105];
int solve(int n,int m,int k){
	if(n<k)return 0;
	if(!n)return 1;	
	if(m==1)return (k==1)*fac[n];
	if(dp[n][m][k]>=0)return dp[n][m][k];
	int res=0;
	for(int i=0;i<n;i++)
		for(int j=max(k+i+1-n,0);j<=min(k,i);j++)
			res=(res+1ll*solve(i,m-1,j)*solve(n-i-1,m-1,k-j)%mod*C[n-1][i]%mod)%mod;
	dp[n][m][k]=res;
	return res;
}
int main(){
	int n,m,k;
	scanf("%d%d%d%d",&n,&m,&k,&mod);
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	memset(dp,-1,sizeof(dp));
	printf("%lld\n",solve(n,m,k));
	return 0;
}
```

---

## 作者：ReTF (赞：1)

好题。如果 $n\le 50$，让人一眼看出来 $O(n^5)$ 可以通过就更好了。

从大到小插入元素构成排列，在插入某一个元素之前，之前插入的所有元素将序列分成若干段空白，观察到如果当前一段插入一个数后，该数的答案为 $a$，在当前段加入一个数后该段分裂为两小段，答案均为 $a+1$。

假设排列为 $p$，以 $i$ 为编号，$p_i$ 为权值构建笛卡尔树，发现在序列中插入某个 $p_i$ 时，$p_i$ 所插入的一段的答案恰好为 $d_i$，其中 $d_i$ 表示节点 $i$ 在笛卡尔树上的深度。

此时题意转化成了有多少棵不同的大小为 $n$ 的二叉树，满足深度为 $m$ 的节点恰好有 $k$ 个，父节点的编号大于儿子的编号。

dp，设 $f_{i,j,k}$ 表示满足大小为 $i$，父节点的编号大于儿子的编号，含有 $j$ 个**在最终树上**深度为 $m$ 的点，这些节点在**当前树内**的深度为 $k$。

转移如下：

$$f_{i+1,j,k}=\sum_{l}\sum_{L}f_{l,L,k-1}\times f_{i-l,j-L,k-1}\times \dbinom{i}{l}$$

时间复杂度 $O(n^5)$，卡常后可以通过。

---

## 作者：Purslane (赞：0)

# Solution

考虑给定一个序列，建出这个序列的笛卡尔树。事实上也就问你有多少个排列的笛卡尔树的深度为 $m$ 的点为 $k$ 个。

考虑设 $dp_{n,m,k}$ 为所求问题的答案。

很容易写出转移方程式（枚举最大值点在哪）：

$$
dp_{n,m,k} = \sum_{l=0}^{n-1} \sum_{x=0}^k \binom{n-1}{l} dp_{l,m-1,x}dp_{n-1-l,m-1,k-x}
$$

不过有很多边界问题要处理。为了防止出现这么多麻烦事，我们钦定 $m=1$ 的时候，如果 $k=1$ 返回 $n!$，否则返回 $0$。特别的，如果 $n=0$，返回 $[k=0]$。这样我们使用记忆化搜索转移，搜到 $m=1$ 就可以回溯了，防止发生一些我不能理解的情况。

不过你这样容易给卡常。考虑一些优化。

有一个很明显的性质：一个 $n$ 节点的二叉树，同一层不能有严格多于 $\dfrac{n+1}{2}$ 个节点。所以可以减掉所有 $2k > n+1$ 的情况。这样你甚至可以少枚举一些 $x$。

大概是 $483 \rm ms$，卡不动了。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100+10;
int n,m,k,p,frac[MAXN],C[MAXN][MAXN],dp[MAXN][MAXN][MAXN],vis[MAXN][MAXN][MAXN];
int solve(int n,int m,int k) {
	if(!n) return !k;
	if(vis[n][m][k]) return dp[n][m][k];
	if(k*2>=n+2) return vis[n][m][k]=1,dp[n][m][k]=0;
	if(m==0) return vis[n][m][k]=1,dp[n][m][k]=(k==0);
	if(m==1) {
		vis[n][m][k]=1;
		if(k==1) return dp[n][m][k]=frac[n];
		return dp[n][m][k]=0;
	}
	vis[n][m][k]=1;
	ffor(l,0,n-1) {
		int r=n-1-l;
		int xl=max(0ll,k-(r+2)/2),yl=min(l/2+1,k);
		ffor(x,xl,yl) {
			int y=k-x;
			dp[n][m][k]=(dp[n][m][k]+solve(l,m-1,x)*solve(r,m-1,y)%p*C[l+r][l])%p;
		}
	}
	return dp[n][m][k];
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k>>p;
	C[0][0]=1; frac[0]=1; ffor(i,1,n) frac[i]=frac[i-1]*i%p;
	ffor(i,1,n) {C[i][0]=1;ffor(j,1,n) C[i][j]=(C[i-1][j]+C[i-1][j-1])%p;}
	cout<<solve(n,m,k);
	return 0;
}
```

---

