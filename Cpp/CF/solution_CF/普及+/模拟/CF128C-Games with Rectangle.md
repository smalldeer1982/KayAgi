# Games with Rectangle

## 题目描述

In this task Anna and Maria play the following game. Initially they have a checkered piece of paper with a painted $ n×m $ rectangle (only the border, no filling). Anna and Maria move in turns and Anna starts. During each move one should paint inside the last-painted rectangle a new lesser rectangle (along the grid lines). The new rectangle should have no common points with the previous one. Note that when we paint a rectangle, we always paint only the border, the rectangles aren't filled.

Nobody wins the game — Anna and Maria simply play until they have done $ k $ moves in total. Count the number of different ways to play this game.

## 说明/提示

Two ways to play the game are considered different if the final pictures are different. In other words, if one way contains a rectangle that is not contained in the other way.

In the first sample Anna, who performs her first and only move, has only one possible action plan — insert a $ 1×1 $ square inside the given $ 3×3 $ square.

In the second sample Anna has as much as 9 variants: 4 ways to paint a $ 1×1 $ square, 2 ways to insert a $ 1×2 $ rectangle vertically, 2 more ways to insert it horizontally and one more way is to insert a $ 2×2 $ square.

## 样例 #1

### 输入

```
3 3 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 4 1
```

### 输出

```
9
```

## 样例 #3

### 输入

```
6 7 2
```

### 输出

```
75
```

# 题解

## 作者：EnochWenzhou (赞：19)

CodeForces128C

题目：一个棋盘上有一个大小为n\*m的矩阵,矩阵边缘在棋盘线上.现在你要操作k次,每一次都在上一个画好的矩阵中再画一个矩阵,要求被严格包含,边缘也不能重叠且必须在棋盘线上.问你一共有几种画法.

思路：

首先容易发现，横坐标与纵坐标可以分开考虑，将横坐标可能的排列方案数与纵坐标可能的排列方案数相乘即为答案。不妨令n>m。

容易想到从DP入手，以f\[i\]\[j\]表示目前从里到外已经画了i个段，第i段的长度为j的方案数，容易想到转移方程：

$f[i][j]=(i==1)?1:\sum_{k=1}^{j-2}f[i-1][k]\times(j-k-1)$

j-k-1是长度为k的段在长度为j的段中排列的可能的排列方案数。

那么可见答案即是$f[k+1][n]\times f[k+1][m]$，这种做法也许理论复杂度是$O(n^2k)$的打法，比较暴力，但是貌似能水过去。以下考虑优化

因

$f[i][j]=1\times f[i-1][j-2]+2\times f[i-1][j-3]+3\times f[i-1][j-4]+...+(j-3)\times f[i-1][2]+(j-2)\times f[i-1][1]$

又有

$f[i][j-1]=1\times f[i-1][j-3]+2\times f[i-1][j-4]+3\times f[i-1][j-5]+...+(j-4)\times f[i-1][2]+(j-3)\times f[i-1][1]$

可知

$f[i][j]=f[i][j-1]+\sum_{k=1}^{j-2}f[i-1][k]$

容易发现∑的部分可以通过前缀和优化消去一层for循环使时间复杂度降至$O(nk)$，容易发现i这一维是多余的。

以下是DP做法代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;bool o1;
LL n,m,k,g[1010],f[1010],P=1e9+7;
bool o2;int main(){
	cin>>n>>m>>k;
	if(n<m)swap(n,m);
	for(LL j=1;j<=n;j++)f[j]=1;
	for(LL i=1;i<=k;i++)for(LL j=1;j<=n;j++)
		g[j]=(f[j]+g[j-1])%P,f[j]=((j<2?0:g[j-2])+f[j-1])%P;
	cout<<f[n]*f[m]%P;
	return 0;
}
```

DP的做法我想是很难继续优化了，但是这题其实可以更简单。容易发现答案就是$C_{n-1}^{2\times k}\times C_{m-1}^{2\times k}$。因为假如在n-1的段上随机选2\*k个点，最终只会映射到唯一的一种情况上去。于是这题最快可以达到O(n)，也就是求组合数的复杂度。

以下代码是用递推求组合数的AC代码,复杂度是0$O(n^2)$，如果用逆元求组合数复杂度就只有$O(n)$了，最小的复杂度应该也就只有$O(n)$了：

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL n,m,k,C[2020][2020],P=1e9+7;
int main(){
	C[0][0]=1;
	for(LL i=1;i<=1000;i++){
		C[i][0]=1;
		for(LL j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
	}
	cin>>n>>m>>k;
	cout<<C[n-1][2*k]*C[m-1][2*k]%P;
	return 0;
}
```

---

## 作者：fanypcd (赞：10)

首先英文题面中指出了每次绘制的矩形应画在上一次绘制的矩形内。（原来的翻译没有，所以当你感觉不可做的时候最好去看英文题面）。

那么组合的做法就比较显然了。

小学奥数记得学过求在一个 $n \times m$ 的矩形框内画出一个矩形，求有多少种画法。

![](https://cdn.luogu.com.cn/upload/image_hosting/bxx24idy.png)

确定矩形位置的是其对着的两个顶点（图中红蓝部分）。

如果我们能知道红点，蓝点的位置，那么对应的矩形是唯一确定的。

再看点的位置怎么确定，是由其横纵坐标的值确定的，如红点 $(2,2)$，蓝点 $(6,4)$。

那么我们在横轴共 7 个位置上任取两个，按顺序将它们作为红蓝两点的横坐标，在纵轴共 5 个位置上任取两个，按顺序将它们作为红蓝两点的纵坐标。

容易发现这样每种选位置的方案都对应唯一不重的一个矩形。

于是这个问题的答案就是 ${7 \choose 2} \times {5 \choose 2}$。

---

那么拓展到这道题，我们需要确定 $k$ 个矩形的 $2 \times k$ 个顶点的位置，那么总的方案数就是 ${n - 1 \choose 2 \times k} \times {m - 1 \choose 2 \times k}$，且容易发现对于每种情况，都存在画出的方法（每次取横纵坐标最小的位置和最大的位置对应的两个点画即可）。

预处理组合数做到 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
const int mod = 1e9 + 7;
#define N 1005
int inv[N], fac[N], ifac[N];
void init()
{
	inv[0] = inv[1] = fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for(int i = 2; i <= N - 5; i++)
	{
		inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
		fac[i] = 1ll * i * fac[i - 1] % mod;
		ifac[i] = 1ll * inv[i] * ifac[i - 1] % mod;
	}
	return;
}
inline int C(int n, int m)
{
	if(m > n)
	{
		return 0;
	}
	return 1ll * fac[n] * ifac[n - m] % mod * ifac[m] % mod;
}
signed main()
{
	init();
	int n, m, k;
	read(n), read(m), read(k);
	printf("%lld", 1ll * C(n - 1, 2 * k) * C(m - 1, 2 * k) % mod);
	return 0;
}
```

---

## 作者：Mo_Han136 (赞：8)

发现没有人写题解，本蒟蒻就来试一试。

### O(n^5)暴力写法

因为每次画矩形时只能在原有的内部画，因此矩形间转移的影响只和大小有关，与相对位置无关。

因此只需用$f[i][j][k]$表示走了i步，大小为$j \times k$的矩形的方案数。

用滚动数组优化空间。

直接暴力枚举下一个矩形进行转移。

P.S. 虽然相对位置对答案的转移没有影响，但对答案存在影响，转移时不要忽略。

dp转移部分：

```cpp
f[0][n][m]=1;
for(int i=1;i<=k;++i){
	int s=i&1;
	memset(f[s],0,sizeof(f[s]));
	for(int p=1;p<=n;++p)for(int q=1;q<=m;++q)
		for(int u=p+2;u<=n;++u)for(int v=q+2;v<=m;++v)
			Add(f[s][p][q],f[!s][u][v]*(u-p-1)%P*(v-q-1)%P);
}
```

最终答案就是第k步的所有矩形的方案数之和

$O(n^5)$完整代码:

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int M=1005,P=1e9+7;
int n,m,k;
LL f[2][M][M];
void Add(LL &x,LL y){
	x+=y;
	if(x>=P)x-=P;
	if(x<0)x+=P;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	f[0][n][m]=1;
	for(int i=1;i<=k;++i){
		int s=i&1;
		memset(f[s],0,sizeof(f[s]));
		for(int p=1;p<=n;++p)for(int q=1;q<=m;++q)
			for(int u=p+2;u<=n;++u)for(int v=q+2;v<=m;++v)
				Add(f[s][p][q],f[!s][u][v]*(u-p-1)%P*(v-q-1)%P);
	}
	LL ans=0;
	for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)
		Add(ans,f[k&1][i][j]);
	printf("%lld\n",ans);
	return 0;
}
```

### O(n^3) AC写法

其实我一开始也认为这样会超时，但实测时间大约1s，可见 ~~时代在进步~~ 常数很优秀

通过对暴力代码的分析+感性理解，发现横纵方向的方案数是互不干扰的。

采用倒推思想，只需求出在第k步能得到n行和m列的方案数即可，他们的乘积即为答案。

用$f[i][j]$表示第i步形成j行的方案数

其他思路与暴力写法相似

dp转移部分：
```cpp
for(int i=1;i<=n;++i)f[0][i]=1;
	for(int i=1;i<=k;++i)
		for(int p=1;p<=n;++p)
			if(f[i-1][p])for(int q=p+2;q<=n;++q)
```

$O(n^3)$完整代码：
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int M=1005,P=1e9+7;
int n,m,k;
LL f[M][M];
void Add(LL &x,LL y){
	x+=y;
	if(x>=P)x-=P;
	if(x<0)x+=P;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	if(n<m)swap(n,m);
	for(int i=1;i<=n;++i)f[0][i]=1;
	for(int i=1;i<=k;++i)
		for(int p=1;p<=n;++p)
			if(f[i-1][p])for(int q=p+2;q<=n;++q)
				Add(f[i][q],f[i-1][p]*(q-p-1)%P);
	printf("%lld\n",f[k][n]*f[k][m]%P);
	return 0;
}
```


$\mathcal{By}\quad\mathcal{Most}\ \mathcal{Handsome}$

$\mathcal{2020.08.09}$

---

## 作者：Graph_Theory (赞：3)

题目：在 $n\times m$ 的地图内画 $k$ 个矩形，严格包围。

思路：正确的矩形有上下左右 $4$ 条边，分别计算上下和左右在网格线上的位置。

那怎么算网格线可以画的位置。

显然是网格边框长度 $+1$ 得出网格线的数量
再减去 $2$(边框的网格线不可以画)得出 $m+1-2$ 和 $n+1-2$。

又因为矩形上下和左右各有两条边
所以在横轴和纵轴上分别要画 $k\times 2$ 条边

可见答案是 $C_{k \times 2}^{m+1-2}\times C_{k \times 2}^{n+1-2}$。

例子: $k=2$, $6\times5$

[![pPEW2i4.png](https://s1.ax1x.com/2023/08/07/pPEW2i4.png)](https://imgse.com/i/pPEW2i4)


---

## 作者：thostever (赞：2)

## 组合数做法

我们发现，对于每个矩形，只需要确定两条横着的边的位置和两条竖着的边的位置，我们便确定了这个矩形的位置。

一共需要确定 $2k$ 条横着的边和 $2k$ 条竖着的边。

可选的横着的边一共有 $n+1$ 个，减去最开始的矩形便是 $n-1$ 条。同理，有 $m-1$ 条可选的竖着的边。

那么我们一共的方案数便是 $C\begin{pmatrix}2k\\n-1\end{pmatrix}\times C\begin{pmatrix}2k\\m-1\end{pmatrix}$ 

直接 $O(n^2)$ 预处理组合数或者 $O(n)$ 求逆元即可。

我用的是乘法逆元///

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m,k;
int qpow(int x,int y)
{
	int p=1;
	while(y)
	{
		if(y&1) p*=x,p%=mod;
		x*=x; x%=mod;
		y>>=1;
	}
	return p;
}
int fac[1010];
int C(int x,int y)
{
	if(x<y) return 0;
	return fac[x]*qpow(fac[y]*fac[x-y]%mod,mod-2)%mod;
}
signed main()
{
	fac[0]=1;
	for(int i=1;i<=1000;i++) fac[i]=fac[i-1]*i,fac[i]%=mod;
	cin>>n>>m>>k;
	cout<<C(n-1,2*k)*C(m-1,2*k)%mod;
	return 0;
}
```


---

## 作者：shaozhehan (赞：1)

[原题链接](https://www.luogu.com.cn/problem/CF128C)

[CodeForces 链接](https://codeforces.com/problemset/problem/128/C)

题目大意：

在一个 $n\times m$ 的矩形里绘制矩形，每一次矩形都必须在上一次矩形的里边绘制，并不能和上一个矩形有任何公共点，一共进行 $k$ 次绘制。问你一共可以形成多少种不同的图形。答案对 $10^9+7$ 取模。

思路：

我们可以使用组合数解决。显然，给定一个横长平行于 $x$ 轴的长方形的矩形的左上角和右下角的坐标，就可以确定这个矩形的具体形状及位置。所以，我们可以在 $x$ 轴上选择 $2k$ 个点，从外到内的第 $i$ 个矩形必须选从左往右数第 $i$ 个点和从右往左数第 $i$ 个点作为左上角和右下角的竖坐标。所以，如果在 $x$ 轴上选择 $2k$ 个点并在 $y$ 轴上选择 $2k$ 个点就可以确定一个绘制矩形的方案。综上，总方案数为 $\begin{pmatrix}n\\2k\end{pmatrix}\times\begin{pmatrix}m\\2k\end{pmatrix}$。

我们可以根据公式 $\begin{pmatrix}k_1\\k_2\end{pmatrix}=\begin{pmatrix}k_1-1\\k_2-1\end{pmatrix}+\begin{pmatrix}k_1-1\\k_2\end{pmatrix}$ 使用记忆化搜索算出 $\begin{pmatrix}n\\2k\end{pmatrix}$ 和 $\begin{pmatrix}m\\2k\end{pmatrix}$，左右将其相乘并模 $10^9+7$，就可以了。

坑点：

1. 记得时时刻刻对 $10^9+7$ 取模，否则炸 ```int```！
1. 最后相乘时一定要乘 ```1ll```，以防半路炸 ```int```！
1. 算组合数的函数的边界要判定好！

上代码：
```cpp
#include <iostream>
using namespace std;

const int mod = 1e9 + 7;

int ans[1001][1001];// 记忆化数组

// 算组合数
int C(const int &n, const int &m){
    if (n < m){
        return 0;
    }
    if (m == 0 || m == n){
        return ans[n][m] = 1;
    }
    if (n == 1){
        return ans[n][m] = 1;
    }
    if (ans[n][m]){
        return ans[n][m];
    }
    return ans[n][m] = (C(n - 1, m) + C(n - 1, m - 1)) % mod;
}

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout 加速
    int n, m, k;
    cin >> n >> m >> k;
    cout << 1ll * C(n - 1, k << 1) * C(m - 1, k << 1) % mod;
    return 0;
}
```

---

## 作者：liuli688 (赞：0)

### 思路：
一个长方形由 $4$ 条边组成。如果确定了这 $4$ 条边，那么长方形的位置也就确定了。

对于一次选择，可以选 $n + 1$ 条横着的边。由于长方形必须被严格包含，边缘不能重叠，所以要从 $n + 1$ 条边中减去 $2$ 条，即可以选 $n - 1$ 条横着的边。同理，可以选 $m - 1$ 条竖着的边。

而我们一共要画 $k$ 次，又由于需要确定 $2$ 条横着的边和 $2$ 条竖着的边，所以要确定 $2k$ 条横着的边和 $2k$ 条竖着的边。

由于从 $a$ 件物品中选 $b$ 件（不计顺序）的方法数量为 $C ^ b _ a$，所以选择横着的边的方法数量为 $c ^ {2k} _ {n - 1}$，选择竖着的边的方法数量为 $c ^ {2k} _ {m - 1}$。乘法原理，总方案数为 $c ^ {2k} _ {n - 1} \times c ^ {2k} _ {m - 1}$。

前缀和 $+$ 乘法逆元即可。
### 代码：
```cpp
#define MAIN signed main()
#define SPEEDUP ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define USING using namespace std
#define END return 0
//框架
#define LL long long
#define ULL unsigned long long
#define DB double
#define LD long double
#define STR string
//数据类型
#define EL '\n'
#define INF INT_MAX
#define UINF INT_MIN
//常量
#define IN(n) cin >> n
#define OUT(n) cout << n
#define OUTL(n) cout << n << EL
#define PREC(n) setprecision(n)
#define FPREC(n) fixed << setprecision(n)
//<iostream>
#define FP(i,a,b) for(i = a;i < b;i++)
#define FM(i,a,b) for(i = a;i > b;i--)
#define FL(i,a,b) for(i = a;i <= b;i++)
#define FG(i,a,b) for(i = a;i >= b;i--)
#define BK break
#define CTN continue
#define REG register
//循环
#define FREO(n,m) freopen(n,"r",stdin),freopen(m,"w",stdout)
#define FREC(n) fclose(stdin),fclose(stdout)
//文件读写

#include <bits/stdc++.h>
USING;

LL qpow(LL a,LL b,LL p)//快速幂模板
{
	LL ans = 1,base = a;
	while(b)
   {
		if(b & 1)
			ans = (ans * base) % p;
		base = (base * base) % p;
		b >>= 1;
	}
	return ans;
}

const int MAX = 1e3,MOD = 1e9 + 7;
LL f[MAX+10],n,m,k,i;//记得 long long

void init()//前缀和初始化
{
	f[0] = 1;
	FL(i,1,MAX)
	{
		f[i] = f[i-1] * i;
		f[i] %= MOD;//随时取模
	}
}

LL c(LL m,LL n)//计算组合数
{
	if(m < n)
		return 0;
	return f[m] * qpow(f[n] * f[m-n] % MOD,MOD - 2,MOD) % MOD;
} 
MAIN
{
	SPEEDUP;
	init();
	IN(n >> m >> k);
	OUT(c(n-1,2*k) * c(m-1,2*k) % MOD);
	END;
}
```

---

## 作者：qwq___qaq (赞：0)

目前的题解里面没有和我一样的做法呢...

$n\times m$ 的矩阵，考虑成 $n\times m$ 个格子，那么边框不能放，那么下一次的边框 $a\times b$ 就需要保证 $a\in[2,n-1],b\in[2,m-1]$。

每一次分割显然只能取分割线集的首尾，于是，每一次分割线的选择都只会对应一种方案。

但是每次放新的边框会在左和右都割一下，所以会出现 $2k$ 条分割线，那么分割线的方案数就是 $C_{n-2}^{2k}C_{m-2}^{2k}$。

但是，你这样写连样例都过不了，于是考虑一下还有哪些方案漏掉了：

- 对于最后一次选择，可以只选一行的一部分，或一列的一部分，此时只有 $2k-1$ 条分割线。

那么就会有行是否有重合，列是否有重合 $4$ 种情况，加法原理，$C_{n-2}^{2k}C_{m-2}^{2k}+C_{n-2}^{2k-1}C_{m-2}^{2k}+C_{n-2}^{2k}C_{m-2}^{2k-1}+C_{n-2}^{2k-1}C_{m-2}^{2k-1}$。

---

