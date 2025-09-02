# [USACO19DEC] Greedy Pie Eaters P

## 题目背景

Farmer John has $M$ cows, conveniently labeled $1 \ldots M$, who enjoy the occasional change of pace
from eating grass.  As a treat for the cows, Farmer John has baked $N$ pies ($1 \leq N \leq 300$), labeled
$1 \ldots N$.  Cow $i$ enjoys pies with labels in the range $[l_i, r_i]$ (from $l_i$ to $r_i$ inclusive),
and no two cows enjoy the exact same range of pies.  Cow $i$ also has a weight, $w_i$, which 
is an integer in the range $1 \ldots 10^6$.

Farmer John may choose a sequence of cows $c_1,c_2,\ldots, c_K,$ after which the
selected cows will take turns eating in that order. Unfortunately, the cows 
don't know how to share! When it is cow $c_i$'s turn to eat, she will consume
all of the  pies that she enjoys --- that is, all remaining pies in the interval
$[l_{c_i},r_{c_i}]$.  Farmer John would like to avoid the awkward situation
occurring when it is a cows turn to eat but all of the pies she enjoys have already been
consumed. Therefore, he wants you to compute the largest possible total weight
($w_{c_1}+w_{c_2}+\ldots+w_{c_K}$) of a sequence $c_1,c_2,\ldots, c_K$ for which each cow in the
sequence eats at least one pie.

## 题目描述

Farmer John 有 $M$ 头奶牛，为了方便，编号为 $1,\dots,M$。这些奶牛平时都吃青草，但是喜欢偶尔换换口味。Farmer John 一天烤了 $N$ 个派请奶牛吃，这 $N$ 个派编号为 $1,\dots,N$。第 $i$ 头奶牛喜欢吃编号在 $\left[ l_i,r_i \right]$ 中的派（包括两端），并且没有两头奶牛喜欢吃相同范围的派。第 $i$ 头奶牛有一个体重 $w_i$，这是一个在 $\left[ 1,10^6 \right]$ 中的正整数。

Farmer John 可以选择一个奶牛序列 $c_1,c_2,\dots,c_K$，并让这些奶牛按这个顺序轮流吃派。不幸的是，这些奶牛不知道分享！当奶牛  吃派时，她会把她喜欢吃的派都吃掉——也就是说，她会吃掉编号在 $[l_{c_i},r_{c_i}]$ 中所有剩余的派。Farmer John 想要避免当轮到一头奶牛吃派时，她所有喜欢的派在之前都被吃掉了这样尴尬的情况。因此，他想让你计算，要使奶牛按 $c_1,c_2,\dots,c_K$ 的顺序吃派，轮到这头奶牛时她喜欢的派至少剩余一个的情况下，这些奶牛的最大可能体重（$w_{c_1}+w_{c_2}+\ldots+w_{c_K}$）是多少。

## 说明/提示

#### 样例解释
在这个样例中，如果奶牛 $1$ 先吃，那么奶牛 $2$ 就吃不到派了。然而，先让奶牛 $2$ 吃，然后奶牛 $1$ 只吃编号为 $2$ 的派，仍可以满足条件。

对于全部数据，$1 \le N \le 300,1 \le M \le \dfrac{N(N-1)}{2},1 \le l_i,r_i \le N,1 \le w_i \le 10^6$。
#### 数据范围
对于测试点 $2-5$，满足 $N \le 50,M \le 20$；

对于测试点 $6-9$，满足 $N \le 50$。

USACO 2019 December 铂金组T1

## 样例 #1

### 输入

```
2 2
100 1 2
100 1 1
```

### 输出

```
200
```

# 题解

## 作者：wylt (赞：68)

USACO 2019 December 铂金组T1 Greedy Pie Eaters

原题面（英文）：[http://www.usaco.org/index.php?page=viewproblem2&cpid=972](http://www.usaco.org/index.php?page=viewproblem2&cpid=972)

官方题解（英文）：[http://www.usaco.org/current/data/sol_pieaters_platinum_dec19.html](http://www.usaco.org/current/data/sol_pieaters_platinum_dec19.html)



------------
### 题意简述
有 M 头牛，N 个派，每头牛都有体重和吃派的范围，分别用 $w$, $l$, $r$ 表示，

每头牛按顺序轮流吃派，且牛 i 会吃掉此时 $\left[l_{i}\ ,r_{i}\right]$ 的所有派。

我们需要求出每头牛按顺序吃完后，满足所有牛都至少吃到一个的 $\max\sum\limits_{i=c1}^{ck}w_i$ 。

其中 $N\le300,\ w_{i}\le10^6$ 。

### 题目分析

容易看出本题是一道区间求极值的问题，而区间 dp 就刚好可以解决此类问题，再看数据范围 $N\le300$, 所以我们可以朝区间 dp 这方面思考一下。

那么我们可以得到一个基本思路， $f(i,j)=\max(\ f(i,j),\ f(i,k-1)+f(k+1,j)+p(k,i,j)\ )$ 。

其中 $i,j,k$ 为下标，表示第 $i$ 个派 ；

$f(i,j)$ 表示此时 $\left[i\ ,j\right]$ 已被吃完的最大 $\sum\limits_{}^{}w$ ；

$p(k,i,j)$ 表示当 k 还未被吃时能吃掉 k 且 $i\le l\le k\le r\le j$ 的最大的一个 $w$ ；

所以转移方程可以理解为通过合并 $f(i,k-1)+f(k+1,j)$ 更新 $f(i,j)$ 的值，

而**第一个问题**就来了：为什么是 $f(i,k-1)+f(k+1,j)$ 而不是 $f(i,k)+f(k+1,j)$ 呢？

因为题目要求每头牛都**至少吃到一个**，所以在合并时就必须满足 k 还未被吃，

而 $f(i,k)+f(k+1,j)$ 就可能存在两部分都已经被吃完的尴尬情况。

**第二个问题**，为什么 $p(k,i,j)$ 中 $i\le l\le k\le r\le j$ 呢？

因为现在我们要求合并时拥有最大 $w$ 的一个能吃掉第 k 个派的牛，

所以 k 必须在这头牛的 $l,r$ 之间，且不能把 $\left[i\ ,j\right]$ 以外的派吃掉，而影响了后面的更新

**第三个问题**，也是最难的一个问题，就是如何求出 $p(k,i,j)$。

我们知道， $p(k,i,j)$ 肯定是可以先预处理出来的，其实思路也基本就是区间 dp 的思路，

即 $p(k,i-1,j)=\max(\ p(k,i-1,j),\ p(k,i,j)\ )$ ；

$p(k,i,j+1)=\max(\ p(k,i,j+1),\ p(k,i,j)\ )$。

也就是通过已经得出的一个个向外更新，最终扩展到整个序列。

**温馨提示（血的教训）**：

我们可以发现下面代码的两个更新循环有许多不一样，但改变任何一个的顺序都会 wa 掉。

对于区间 dp 千万要注意循环的顺序，一般循环有三层，分为枚举 $i,j$ 和他们的合并点 $k$ ，

有两种顺序为 $i->j->k$ 和 $k->i->j$ ，

也就是 $k$ 的出现顺序不同，我们可以根据模拟的方法推出哪种顺序不对，

只要发现会用到未更新过的点更新自己就是错误的，一般很快就可以判断出来。

其次还要注意是从 $1$ 枚举到 $N$ 还是要反过来从 $N$ 枚举到 $1$ ，方法和上面一样，就不多说了。



------------
### 代码

代码和官方题解的思路基本一样，但可读性可能会好一点。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int f[305][305];
int p[305][305][305];

int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int w,l,r;
		cin>>w>>l>>r;
		for(int j=l;j<=r;j++){
			p[j][l][r]=w;//由于没有两头奶牛喜欢吃相同范围的派，可以不用比较大小，直接赋值即可 
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=k;i>=1;i--){
			for(int j=k;j<=n;j++){
				//if为了防止下标超过[1,n] 
				if(i!=1){ 
					p[k][i-1][j]=max(p[k][i][j],p[k][i-1][j]);
				}
				if(j!=n){
					p[k][i][j+1]=max(p[k][i][j],p[k][i][j+1]);
				}
			}
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=i;j<=n;j++){
			for(int k=i;k<j;k++){//k!=j是因为底下的f(k+1,j) 
				f[i][j]=max(f[i][j],f[i][k]+f[k+1][j]);//先把f(i,j)用前几次的新数据更新 
			}
			for(int k=i;k<=j;k++){
				f[i][j]=max(f[i][j],(k!=i?f[i][k-1]:0)+(k!=j?f[k+1][j]:0)+p[k][i][j]);
				//同样要防止出现f(i,j)中，i>j的情况 
			}
		}
	}
	cout<<f[1][n];
	return 0;
}
```


---

## 作者：Cry_For_theMoon (赞：46)

&emsp;&emsp;[传送门](https://www.luogu.com.cn/problem/P5851)

&emsp;&emsp;这道水题WA了3次才发现 $n,m$ 写反了，大家千万吸取我这个垃圾的教训。

&emsp;&emsp;设 $f(i,j)$ 是在 $i..j$ 块派**范围（即不能超出，但也不要求全部吃完）** 内的答案。那么最后答案就是 $f(1,n)$（~~蒟蒻WA了三次就是输出了 f(1,m)~~)

&emsp;&emsp;我们知道，$DP$ 一般都是考虑 **最后一步和上一步的关系**，那么对于区间 $[i,j]$，我们**吃掉的最后一个派** 可以是 $[i,j]$ 之间的任何一个派，**如果最后吃掉的是派 $k$，那么它对其它的派就不影响了**。什么意思，因为选择一头牛要保证这个区间至少还剩下一个派，如果最后吃掉的是第 $k$ 个，那么这头选择的牛的要求范围内其它的派已经无所谓了，不造成影响。那么应该拆成 $f(i,k-1)$ 和 $f(k+1,j)$ 两个区间。又因为 $f$ 数组里的定义是不超过 $[i,j]$，那么这两个子问题的任意解都不会吃掉第 $k$ 个派。

&emsp;&emsp;那么怎么确定吃掉第 $k$ 个派的这头牛？显然这头牛的要求范围不应超过 $i,j$，因此设 $g(i,j,k)$ 是 $[i,j]$ 内要求范围有第 $k$ 个派的牛中最大的体重。那么可以拆成 $g(i+1,j,k)$ 和 $g(i,j-1,k)$，本题就可以做了。

&emsp;&emsp;如果你使用这两个方程转移，**你会发现根本不需要判断是不是会出界！**，因为不合法状况一定不会RE且为0，符合不合法状况的理想的值。

&emsp;&emsp;然后你会发现 $f$ 也是不需要初始状态的，只有 $g$ 需要。但是 $g$ 的初始状态如果视作 $i=j$ 时不好做，你需要枚举所有奶牛（或者再开一个类似前向星的东西存，太麻烦了）。可能有人已经发现上面的 $g$ 的方程没有考虑 **刚好有一个奶牛把整个$[i,j]$全部吃掉**的情况，这种情况就是留待初始化的。

&emsp;&emsp;代码里提供了一种区间DP的不易出错的写法：既然区间DP的转移通常是小区间转移大区间，可以最外层枚举长度，第二层枚举起点，此时终点易得，第三层枚举断点。这个套路就不需要记 $i,j$ 到底哪个正序枚哪个倒序了。（~~真是为OI赛制量身定做的写法QwQ)~~

```cpp
//USACO2019,Platinum
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=310,MAXM=90010;
int f[MAXN][MAXN],g[MAXN][MAXN][MAXN];
int w[MAXM],l[MAXM],r[MAXM];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&w[i],&l[i],&r[i]);
		for(int j=l[i];j<=r[i];j++){
			g[l[i]][r[i]][j] = w[i];
		}
	}
	for(int len=1;len<=n;len++){
		for(int i=1;i+len-1<=n;i++){
			int j = i+len-1;
			for(int k=i;k<=j;k++){
				g[i][j][k] = max(g[i][j][k],max(g[i+1][j][k],g[i][j-1][k]));
			}
		}
	}
	for(int len = 1;len<=n;len++){
		for(int i=1;i+len-1<=n;i++){
			int j = i+len-1;
			for(int k=i;k<j;k++){
				f[i][j] = max(f[i][j],f[i][k]+f[k+1][j]);
			}
			for(int k=i;k<=j;k++){
				f[i][j] = max(f[i][j],g[i][j][k] + f[i][k-1] + f[k+1][j]);
			}
		}
	}
	printf("%d\n",f[1][n]);
	return 0;
} 
```


---

## 作者：Purple_wzy (赞：11)

#### A Greedy Pie Eaters

题目：http://www.usaco.org/index.php?page=viewproblem2&cpid=972

题目大意：有n个派，m头牛，每头牛有一个区间[l,r]和一个权值w。
没有两头牛有相同的[l,r]。
你需要选择一些牛，按一定顺序吃派。每头牛会吃完他的那个区间的所有派。
问在满足每头牛都至少有一个派吃的情况下，能获得的最大权值是多少。

n<=300,m<=45000

题解：n很小，可以想到区间DP。

设f[i][j]表示吃掉的派是[i,j]的子集的最大权值。

显然，f[i][j]=max{f[i][k-1]+f[k][j]}，k$\in$[i,j]

但这样的转移不能加入新的牛。

可以考虑待合并的两个状态f[i][k-1]和f[k+1][j],此时k这个派还没有牛动。

我们设mx[k][i][j]表示满足i<=l[k]<=k<=r[k]<=j的所有牛的最大权值。

那么加入新牛的转移方程就出炉了：

f[i][j]=max{f[i][k-1]+mx[k][i][j]+f[k+1][j]},k$\in$(i,j)

复杂度O($n^3$)

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define re register int
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
typedef long long ll;
#define I inline void
#define IN inline int
template<class D>I read(D &res){
	res=0;register D g=1;register char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')g=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	res*=g;
}
int n,m,mx[330][330][330],f[330][330],W,X,Y;
int main(){
	freopen("pieaters.in","r",stdin);
	freopen("pieaters.out","w",stdout);
	read(n);read(m);
	memset(mx,0,sizeof(mx));
	F(i,1,m){
		read(W);read(X);read(Y);
		F(j,X,Y)mx[j][X][Y]=max(W,mx[j][X][Y]);
	}
	F(i,1,n){
		FOR(j,i,1){
			F(k,i,n){
				if(j>1)mx[i][j-1][k]=max(mx[i][j-1][k],mx[i][j][k]);
				if(k<n)mx[i][j][k+1]=max(mx[i][j][k+1],mx[i][j][k]);
			}
		}
	}
	FOR(i,n,1){
		F(j,i,n){
			F(k,i,j-1)f[i][j]=max(f[i][j],f[i][k]+f[k+1][j]);
			F(k,i,j)f[i][j]=max(f[i][j],mx[k][i][j]+(k>i?f[i][k-1]:0)+(k<j?f[k+1][j]:0));
		}
	}
	printf("%d",f[1][n]);
	return 0;
}
```
推荐一下我的博客：https://www.cnblogs.com/Purple-wzy/

这里有USACO12月月赛的全部12篇题解~

---

## 作者：Godzilla (赞：3)

### 题目大意：

有 $M$ 头牛， $N$ 个派，每头牛会吃掉 $[l_i,r_i]$ 中的派，且有一个体重 $w_i$ 。要求选出一个顺序，使得当轮到一头牛时，  至少会吃 $1$ 个派，求 $\max\sum\limits_{}^{}w_i$ 。

$N \le 300 , w_i \le 10^6$ 。

---

### 思路：

区间dp。

设 $f(i,j)$ 表示第 $i$ 至 $j$ 个派被吃完，最大的 $\sum\limits_{}^{}w_i$ ，从 $f(i,k)$ 和  $f(k+1,j)$ 转移。

如果其中的牛吃了 $[i,j]$ 之外的派，那么有可能答案过大，因为有些派被算了两次。

所以规定奶牛吃派的范围 $l_x \ge i$ 且 $r_x \le j$ 。

基于贪心策略，可以假设新加入的那头牛只得到1个派，那么可以枚举剩下的派 $k$ ，得：

$f(i,j)=\max\{f(i,k)+f(k+2,j)+w_x\}，(l_x \ge i，r_x \le j)$ 。

由于枚举 $i,j,k$ 就有 $O(n^3)$ 了，那么 $w_x$ 必须预处理才行。

设 $g(i,j,k)$ 表示 $[i,j]$ 内，包含 $k$ 的奶牛的最大的 $w_i$ 。 

$g(i,j,k)=\max\{g(i+1,j,k),g(i,j-1,k)\}$ 。

对于每单独一头奶牛进行初始化即可。

$f(i,j)=\max\{f(i,k+f(k+2,j)+g(i,j,k)\}$ 。

### 代码：

```c++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

#define LL long long

using namespace std;

const int kM=1e5+5;
const int kN=305;

struct Node{
	int w,l,r;
}a[kM];

int n,m;
int g[kN][kN][kN];
LL f[kN][kN];

void Init(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		scanf("%d%d%d",&a[i].w,&a[i].l,&a[i].r);
	}
}

int main(){
	Init();
	for(int i=1;i<=m;++i){
		int l=a[i].l,r=a[i].r;
		for(int j=l;j<=r;++j){
			g[l][r][j]=max(g[l][r][j],a[i].w);//对每头奶牛进行初始化
		}
	}
	for(int i=1;i<n;++i){
		for(int j=1;j+i<=n;++j){
			int k=i+j;
			for(int l=j;l<=k;++l){
				g[j][k][l]=max(g[j][k][l],max(g[j+1][k][l],g[j][k-1][l]));//预处理g数组
			}
		}
	}
	for(int i=0;i<n;++i){
		for(int j=1;j+i<=n;++j){
			int k=i+j;
			for(int l=j;l<=k;++l){
				f[j][k]=max(f[j][k],f[j][l-1]+f[l+1][k]+(LL)g[j][k][l]);
			}
		}
	}
	printf("%lld",f[1][n]);
	return 0;
}
```



---

## 作者：我去 (赞：3)

思路大佬们都讲得很清楚了，但是那个代码循环是真的恶心

总之要满足“**更新一个点时不能使用到没有更新的点**”

因为都是**长度短的更新长度长的**,于是按照长度枚举，就不会这么恶心

```c++
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cctype>
using namespace std;

const int MAXN = 305;
const int MAXM = 45000;

template <typename T>
inline void read(T&x){
	x=0; char temp=getchar(); bool f=false;
	while(!isdigit(temp)){if(temp=='-') f=true; temp=getchar();}
	while(isdigit(temp)){x=(x<<1)+(x<<3)+temp-'0'; temp=getchar();}
	if(f) x=-x;
}
template <typename T>
void print(T x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) print(x/10);
	putchar(x%10+'0');
}

//basic
int n,m;

//DP
int g[MAXN][MAXN][MAXN],f[MAXN][MAXN];

inline void Init(){
	for(register int len=1;len<=n;len++)
		for(register int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			for(register int k=l;k<=r;k++){
				if(l>1) g[k][l-1][r]=max(g[k][l-1][r],g[k][l][r]);
				if(r<n) g[k][l][r+1]=max(g[k][l][r+1],g[k][l][r]);
			}
		}
}

inline void DP(){
	for(register int len=1;len<=n;len++)
		for(register int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			for(register int k=l;k<r;k++) f[l][r]=max(f[l][r],f[l][k]+f[k+1][r]);
			for(register int k=l;k<=r;k++) f[l][r]=max(f[l][r],f[l][k-1]+f[k+1][r]+g[k][l][r]);
		}
}

int main(){
	read(n),read(m);
	for(register int i=1;i<=m;i++){
		int l,r,w; read(w),read(l),read(r);
		for(register int j=l;j<=r;j++) g[j][l][r]=max(g[j][l][r],w);
	}
	Init();
	DP();
	print(f[1][n]);
	return 0;
}
```

---

## 作者：issue_is_fw (赞：2)

设想一下,在区间$[1,n]中,仅剩下一块蛋糕k$

$k$肯定是给那头重量最大的牛吃最划算

因为它重量最大,吃的范围也不对区间造成影响...因为只剩下$k$了

所以按照区间DP的规则,怎么来转移就稍微有点头绪了

定义$dp[i][j]$为$[i,j]$的蛋糕贡献的奶牛最大重量

当枚举到某个子区间$[l,r]$时

可以枚举分割点从两个区间拼接而来

$$dp[i][j]=dp[i][k]+dp[k+1][j]$$

也可以枚举分割点,表示这块蛋糕被吃带来的最大贡献奶牛

但是奶牛吃的区间要在$[l,r]$中,因为不能有后效性,只能对当前区间造成影响

所以预处理一个$p[k][i][j]$表示能吃$k$且吃的区间不超过$[i,j]$的最大奶牛

转移就是否明了(这个数组p也是区间DP的转移,很好理解)

$$dp[i][j]=dp[i][k-1]+dp[k+1][j]+p[k][i][j]$$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,p[309][309][309],f[309][309];
int main()
{
	cin >> n >> m;
	for(int i=1;i<=m;i++)
	{
		int w,l,r; cin >> w >> l >> r;
		for(int j=l;j<=r;j++)	p[j][l][r]=w;
	}
	for(int k=1;k<=n;k++)
	for(int l=1;l<=n;l++)
	for(int i=1;i+l-1<=n;i++)
	{
		int j=i+l-1,q=p[k][i+1][j],w=p[k][i][j-1];
		if( i+1>j )	q=0;	if( j-1<i )	w=0;
		p[k][i][j]=max( p[k][i][j],max(q,w) );
	}
	for(int l=1;l<=n;l++)
	for(int i=1;i+l-1<=n;i++)
	{
		int j=i+l-1;
		for(int k=i;k<j;k++)
			f[i][j]=max( f[i][j],f[i][k]+f[k+1][j] );
		for(int k=i;k<=j;k++)
		{
			int q=f[i][k-1],w=f[k+1][j];
			if( k==i )	q=0;	if( k==j )	w=0;
			f[i][j]=max( f[i][j],q+w+p[k][i][j] );
		}
	}
	cout << f[1][n];
}
```

---

## 作者：xixiup (赞：2)

## 思路分享

由于奶牛是一个区间一个区间地吃派地，故我们可以考虑区间$DP$。

我们可以设 $dp_{i,j}$ 表示吃掉派 $i \cdots j$ 的情况下奶牛的体重的和最大是多少。

为了更好地维护答案，我们还需要一个 $f_{k,i,j}$，表示在区间 $\left[ i,j \right]$ 范围内，满足 $l_x \leqslant k \leqslant r_x$ 的所有 $x$ 中 $w_x$ 的最大值。

然后我们就可以欢乐地推出式子了。

首是 $f$：
$$
\boxed{f_{k,i,j}=\max(f_{k,i+1,j},f_{k,i,j-1})}
$$
然后是 $DP$：
$$
\boxed{dp_{i,j}=\max(dp_{i,k-1}+f_{i,k,j}+dp_{k+1,j},dp_{i,k}+dp_{k+1,j}))\quad(k \in \left[i \cdots j\right])}
$$
最后就可以输出 $dp_{1,n}$就可以了。

## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=310;
int n,m,dp[maxn][maxn],f[maxn][maxn][maxn];
int main(){
	freopen("pie.in","r",stdin);
	freopen("pie.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int w,l,r;
		scanf("%d%d%d",&w,&l,&r);
		for(int j=l;j<=r;j++){//f赋初始值
			f[j][l][r]=w;	
		}
	}
	for(int l=2;l<=n;l++){//处理f
		for(int i=1;i+l-1<=n;i++){
			int j=i+l-1;
			for(int k=i;k<=j;k++){
				if(i>1){
					f[k][i-1][j]=max(f[k][i-1][j],f[k][i][j]);
				}
				if(j<n){
					f[k][i][j+1]=max(f[k][i][j+1],f[k][i][j]);
				}
			}
		}
	}
	for(int l=1;l<=n;l++){//处理dp
		for(int i=1;i+l-1<=n;i++){
			int j=i+l-1;
			for(int k=i;k<j;k++){
				dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]);
			}
			for(int k=i;k<=j;k++){
				dp[i][j]=max(dp[i][j],dp[i][k-1]*(i!=k)+f[k][i][j]+dp[k+1][j]*(j!=k));
			}
		}
	}
	cout<<dp[1][n];
	return 0;
}
```


---

## 作者：yangwenbin (赞：2)

[P5851 [USACO19DEC]Greedy Pie Eaters P](https://www.luogu.com.cn/problem/P5851)

这道题，是一道很好的区间 $DP$ 的例题，反正挺难想到解题思路的。

首先分析题意，这道题的题意很明确，没有什么令人不理解的地方，但是思路形成与实现有点困难

首先，看到题目，能猜测大概率是一道 $DP$ ，看看数据范围，“$1 \le n \le 300$ ”这就很有可能是区间 $DP$

所以 定义 $dp$ 数组 如下 ：

$dp[left][right] \implies$ 表示从 $left$ 到 $right$ 的范围内的 $\max \sum\limits_{i = c1}^{ck} W_i$


思考一下 ~~（亿下）（手动滑稽）~~

这道题的状态转移方程就出来了：

$
\because $  避免当轮到一头奶牛吃派时，她所有喜欢的派在之前都被吃掉了这样尴尬的情况

$ \therefore $ 在做 $DP$ 是要空开一位，让能吃这位的最大体重的牛吃

$ \therefore $ 定义 $p[k][left][right]$ 表示 能吃 $k$ ，且 $ i \le l \le  k \le r \le j $ 的 $\max W_i$

$\therefore$
$$
dp[i][j] = dp[i][k-1]+dp[k+1][j] + p[k][i][j]
$$

可是问题又来了 $p$ 数组怎么处理出来呢？

这是个好问题 

首先明确一个事实，就是这个一定是可以预处理出来的 ！~~（不然算个der）~~

考虑一下，思路也是区间 $DP$ ，


$$
p[k][i-1][j] =\max (p[k][i][j],p[k][i-1][j]);
$$
$$
p[k][i][j+1] =\max (p[k][i][j],p[k][i][j+1]);
$$

从已知想外层更新

- 注意空间，数组开太大会 $MLE$

# cdoe

```
#include <bits/stdc++.h>
using namespace std;

const int SIZE = 305;
const int NUM = 44850;

inline int read()
{
	int x = 0,f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return f * x;
}

int n,m;
int dp[SIZE][SIZE];
int p[SIZE][SIZE][SIZE];

signed main()
{
	n = read();m = read();
	for (int i = 1; i <= m; ++i)
	{
		int w = read(),l = read(),r = read();
		for (int j = l; j <= r; ++j)
		{
			p[j][l][r] = w;
		}
	}
	
	for (int k = 1; k <= n; ++k)
	{
		for (int i = k; i >= 1; --i)
		{
			for (int j = k; j <= n; ++j)
			{
				if (i != 1)
				{
					p[k][i-1][j] = max(p[k][i][j],p[k][i-1][j]);
				}
				if (j != n)
				{
					p[k][i][j+1] = max(p[k][i][j],p[k][i][j+1]);
				}
			}
		}
	}
	
	for (int i = n; i >= 1; --i)
	{
		for (int j = i; j <= n; ++j)
		{
			for (int k = i; k < j; ++k)
			{
				dp[i][j] = max(dp[i][j],dp[i][k] + dp[k+1][j]);
			}
			for (int k = i; k <= j; ++k)
			{
				dp[i][j] = max(dp[i][j],(k != i ? dp[i][k-1] : 0) + (k != j ? dp[k+1][j] : 0) + p[k][i][j]);
			}
		}
	}
	printf("%d\n",dp[1][n]);
	return 0;
}  
```


---

## 作者：xcxc82 (赞：1)

## [原题面](https://www.luogu.com.cn/problem/P5851)

## 大致题意

有$M$头奶牛,$N$个派,每头奶牛都有一个吃派的范围和体重,分别用$l$,$r$,$w$表示

求出每头奶牛按顺序吃完后,满足每个奶牛都吃到至少一个派的情况下的最大体重值之和

## 分析

设$f[i][j]$为区间$[i,j]$可获得的最大权值

$w[i][j][k]$为能吃掉$k$的最大的一个$w(i\le l\le k\le r\le j)$

先来考虑如何去搞出$w[i][j][k]$

可以去用已知的$w[i][j][k]$去一个个向外更新,扩展到整个序列

得到转移:

$w[i-1][j][k] = max(w[i][j][k] , w[i-1][j][k])$

$w[i][j+1][k] = max(w[i][j][k] , w[i][j+1][k])$

要注意的是这里的枚举顺序

因为是不断向外扩展更新的,在枚举$i$时要倒序枚举,枚举$j$时要正序枚举

转移方程的话首先可以联想到

$f[i][j] = max(f[i][k]+f[k+1][j])(i\le k <j)$

但由于这样转移不能让新进入的奶牛吃到派

因此要改为

- $f[i][j] = max(f[i][k-1]+w[i][j][k]+f[k+1][j])$(第$k$个派还未被吃)



## $code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 310;
int n,m;
int dp[MAXN][MAXN] , w[MAXN][MAXN][MAXN];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int l,r,val;
		scanf("%d%d%d",&val,&l,&r);
		for(int j = l;j<=r;j++){
			
			w[l][r][j] = max(w[l][r][j] , val);
		} 
	}
	for(int k=1;k<=n;k++){
		for(int i=k;i>=1;i--){
			for(int j=k;j<=n;j++){
				if(i!=1) w[i-1][j][k] = max(w[i][j][k] , w[i-1][j][k]);
				if(j!=n) w[i][j+1][k] = max(w[i][j][k] , w[i][j+1][k]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		dp[i][i] = w[i][i][i];
	}
	for(int len=1;len<n;len++){
		for(int i=1;i+len<=n;i++){
			int j = i+len;
			for(int k=i;k<=j;k++){
				dp[i][j] = max(dp[i][j] , dp[i][k-1]+dp[k+1][j]+w[i][j][k]);
			}
		}
	}
	cout<<dp[1][n];
}
```


---

## 作者：Viktley (赞：0)

随便安利一下我的博客：[link](https://blog.csdn.net/bigwinner888/article/details/113525325)

**题目大意：**

给出 $N$ 个 $pie$ ，$M$ 头牛， 

每头奶牛都有一个吃派的范围和体重,

分别用 $l$ , $r$ , $w$ 表示。

问每头牛吃完后,

在每头牛都吃到至少一个派的情况下最大体重值和

------------

**思路：**

依题意，每头奶牛都是按区间的方式吃草。

所以我们考虑使用区间dp.

设 $f[i][j]$ 表示第 $i$ 个 $pie$ 到 第 $j$ 个 $pie$ 之间

全部吃完， 所能贡献的最大体重和。

**怎样考虑转移？**

普通的转移方程:
$$f\lbrack i\rbrack\lbrack j\rbrack\;=\;\underset{i\leq k<j}{min}(f\lbrack i\rbrack\lbrack k\rbrack,\;f\lbrack k\;+\;1\rbrack\lbrack j\rbrack)$$

它实现了两两区间的合并，

但是并没有使得新的奶牛进来吃草。

所以我们考虑在 $i\sim j$ 中枚举一个点 $k$。

使 $k$ 为新牛吃草的点。

即得出方程：

$$\underset{\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;i\leq k<j}{f\lbrack i\rbrack\lbrack j\rbrack\;\;=max}(f\lbrack i\rbrack\lbrack j\rbrack,\;\;f\lbrack i\rbrack\lbrack k\;-\;1\rbrack\;+\;dis\lbrack k\rbrack\lbrack i\rbrack\lbrack j\rbrack\;+\;f\lbrack k\;+\;1\rbrack\lbrack j\rbrack)$$

设 $dis[k][i][j]$ 表示当 $k$ 新来的牛吃掉 $k$

且 $i\le l\le k\le r\le j$ 的最大体重；

**dis值然后求？**

建议大家先去康康此题：[涂色](https://www.luogu.com.cn/problem/P4170)

我们根据涂色的思路，每次多图一个点。

那在该题中，dis的值可以考虑每次由

区间 $i\sim j$ 转移到 $i-1\sim j$ 和 $i\sim j + 1$

即：
$$dis[k][i - 1][end] = max(dis[k][i - 1][end], dis[k][i][end]);$$

$$dis[k][i][end + 1] = max(dis[k][i][end + 1], dis[k][i][end]);$$

**Final node:**

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
#define fre(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
#define ll long long

using namespace std;

const int MAX = 2147483647;
const int N = 310;
int n, m, w, l, r, dis[N][N][N],f[N][N];

int main(){
	scanf("%d%d", &n, &m);
	for(register int i=1;i<=m;i++){
		scanf("%d%d%d", &w, &l, &r);
		for(int  j = l; j <= r; j++) dis[j][l][r] = max(dis[j][l][r], w);
	}
	for(int len = 1; len <= n; len++)
 	 for(int i = 1; i + len - 1 <= n; i++)
	 {
		int end = i + len - 1;
		for(int k = i; k <= end; k++)
		{
			if(i > 1) dis[k][i - 1][end] = max(dis[k][i - 1][end], dis[k][i][end]);
			if(end < n) dis[k][i][end + 1] = max(dis[k][i][end + 1], dis[k][i][end]);
		}
	 }
	for(int len = 1; len <= n; len++)
 	 for(int i = 1; i + len - 1 <= n; i++)
	 { 
		int end = i + len - 1;
		for(int k = i; k <= end; k++)
			f[i][end] = max(f[i][end], f[i][k - 1] + dis[k][i][end] + f[k + 1][end]);
	 }
	printf("%d\n", f[1][n]);
	return 0;
}
```


---

## 作者：qmq菜死了 (赞：0)

题目意思就是：有 M 头奶牛，有 N 个派，每头奶牛会吃掉 L 到 R 中所有剩余的派，并获得一个权值 W，要求在所有奶牛至少吃掉一个派的情况下，最多可以获得的权值。

这道题是有关求区间最大权值的问题，并且 N<=300，范围很小，所以自然而然可以联想到区间 dp 的做法。

f[i][j] 表示区间 [i,j] 被吃掉可以获得的最大权值，k[l][i][j] 表示 l没被吃，还可以吃的最大权值

由此也可以推出转移方程：f[i][j]=max(f[i][j],f[i][l-1]+f[l+1][j]+k[l][i][j])

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=320;//数组开大一些
int n,m,f[N][N],k[N][N][N];
//f[i][j]表示区间 [i,j] 被吃掉可以获得的最大权值，k[l][i][j] 表示 l没被吃，还可以吃的最大权值
//由此也可以推出转移方程：f[i][j]=max(f[i][j],f[i][l-1]+f[l+1][j]+k[l][i][j])
inline int read()
{
	int num=0;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		num=(num<<1)+(num<<3)+c-'0';
		c=getchar();
	}
	return num;
}//快读，当数据量大时会比 cin 和 scanf 快上不少
int main()
{
	n=read();
	m=read();
	for(int i=1;i<=m;i++)
	{
		int a=read(),b=read(),c=read();
		for(int j=b;j<=c;j++)
		{
			k[j][b][c]=a;//赋予初值
		}
	}
	for(int i=1;i<=n;i++)//预处理 k[l][i][j]
	{
		for(int j=i;j>=1;j--)
		{
			for(int l=i;l<=n;l++)
			{
				k[i][j-1][l]=max(k[i][j-1][l],k[i][j][l]);//答案要最大值，都取最大值
				k[i][j][l+1]=max(k[i][j][l+1],k[i][j][l]);
			}
		}
	}
	for(int i=n;i>=1;i--)
	{
		for(int j=i;j<=n;j++)
		{
			for(int l=i;l<=j;l++)
			{
				f[i][j]=max(f[i][j],f[i][l-1]+f[l+1][j]+k[l][i][j]);//转移方程
			}
		}
	}
	cout<<f[1][n];// f[i][n] 即为最大值
	return 0;
}
```


---

## 作者：yezl (赞：0)

这一题看上去还是比较复杂的呀，我来帮忙整理一下题意。

### 题目概述：

有 $ m $ 头奶牛，第 $ i $ 头重量为 $ w_i $ 的奶牛会吃掉一个闭区间 $ [l_i,r_i] $ 中的所有派，要你给一个让每一头奶牛都吃到派的顺序且要使此时奶牛们的重量和最大。

### 思路分析：

刚想要暴搜的我~~看了一下这道题的标签~~，好，很明显这道题要用动态规划，于是我们先来定义一下状态，这状态怎么定义好呢？~~在dalao同学的帮助下~~我想了一会，于是进行了如下定义：  
状态：  $ \mathrm{\normalsize{f[i][j]}} $ 表示 $ \mathrm{\normalsize{[i,j]}} $ 被吃完的最大体重值, $ \mathrm{\normalsize{p[k][i][j]}} $ 表示 $ k $ 还没被吃且能吃 $ \mathrm{\normalsize{(i<=l<=k<=r<=j)}} $ 的最大的一个 $ w $ 。  
状态转移方程：$ \texttt{f[i][j]=max(f[i][j],f[i][k-1]+f[k+1][j]+p[k][i][j])} $

### 不多说，直接上代码：

```c
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;
const int N=305;
int n,m,f[N][N],p[N][N][N];
//状态：f[i][j]表示[i,j]被吃完的最大体重值,p[k][i][j]表示k还没被吃且能吃(i<=l<=k<=r<=j)的最大的一个w 
//状态转移方程：f[i][j]=max(f[i][j],f[i][k-1]+f[k+1][j]+p[k][i][j])
inline int read()//快读，数据量大时比 scanf 还快些 
{
	int num=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		num=(num<<1)+(num<<3)+c-'0';
		c=getchar();
	}
	return num;
}
int main()
{
	n=read(),m=read();//读入 n,m 
	for(int i=1;i<=m;i++)
	{
		int w=read(),l=read(),r=read();
		for(int j=l;j<=r;j++)
			p[j][l][r]=w;
	}
	for(int k=1;k<=n;k++)//预处理p[k][i][j] 
		for(int i=k;i>=1;i--)
			for(int j=k;j<=n;j++)
				p[k][i-1][j]=max(p[k][i-1][j],p[k][i][j]),p[k][i][j+1]=max(p[k][i][j+1],p[k][i][j]);
	for(int i=n;i>=1;i--)
		for(int j=i;j<=n;j++)
			for(int k=i;k<=j;k++)
				f[i][j]=max(f[i][j],f[i][k-1]+f[k+1][j]+p[k][i][j]);
	printf("%d",f[1][n]);
	return 0;
}
```

希望能帮到大家。（刚学LaTeX，还不怎么会，格式问题的话希望指出）

---

