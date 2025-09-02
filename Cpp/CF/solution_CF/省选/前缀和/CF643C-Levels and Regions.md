# Levels and Regions

## 题目描述

Radewoosh is playing a computer game. There are $ n $ levels, numbered $ 1 $ through $ n $ . Levels are divided into $ k $ regions (groups). Each region contains some positive number of consecutive levels.

The game repeats the the following process:

1. If all regions are beaten then the game ends immediately. Otherwise, the system finds the first region with at least one non-beaten level. Let $ X $ denote this region.
2. The system creates an empty bag for tokens. Each token will represent one level and there may be many tokens representing the same level.
  - For each already beaten level $ i $ in the region $ X $ , the system adds $ t_{i} $ tokens to the bag (tokens representing the $ i $ -th level).
  - Let $ j $ denote the first non-beaten level in the region $ X $ . The system adds $ t_{j} $ tokens to the bag.
3. Finally, the system takes a uniformly random token from the bag and a player starts the level represented by the token. A player spends one hour and beats the level, even if he has already beaten it in the past.

Given $ n $ , $ k $ and values $ t_{1},t_{2},...,t_{n} $ , your task is to split levels into regions. Each level must belong to exactly one region, and each region must contain non-empty consecutive set of levels. What is the minimum possible expected number of hours required to finish the game?

## 说明/提示

In the first sample, we are supposed to split $ 4 $ levels into $ 2 $ regions. It's optimal to create the first region with only one level (it must be the first level). Then, the second region must contain other three levels.

In the second sample, it's optimal to split levels into two regions with $ 3 $ levels each.

## 样例 #1

### 输入

```
4 2
100 3 5 7
```

### 输出

```
5.7428571429
```

## 样例 #2

### 输入

```
6 2
1 2 4 8 16 32
```

### 输出

```
8.5000000000
```

# 题解

## 作者：_Arahc_ (赞：7)

看见题解里面全是斜率优化，没有**李超线段树**，所以写一篇纪念。

不想用李超线段树的也别略过啊 QAQ 还是有题目分析的。

[博客阅读体验更佳](https://walker68145.github.io/post/cf643c-ti-jie/)。

[题目传送门](https://www.luogu.com.cn/problem/CF643C)。

## 题目大意：

> 长度为 $n$ 的序列 $a$ 代表 $n$ 个关卡，划分成连续的 $m$ 段，记 $i$ 所属段左端点为 $l_i$。对于第 $i$ 个关卡用刚好一小时过关概率是 $\frac{a_i}{\sum_{j=l_i}^i a_j}$。如果没有过关要继续打这一关到过。求通关时间期望。$n\leqslant 2\times 10^5,m\leqslant 50$。

原题的变量名设的和这里不一样的，在本题解内都以本题解的描述为主。

## 题目分析

### Part1 期望

考虑一小时通过一关的概率是 $\dfrac{a_i}{\sum_{j=l_i}^i a_j}$。过一关需要的时间的期望。首先为了书写方便，我们用换元法，记 $x$ 表示分子，$y$ 表示分母。

如果你知道通过一关的时间期望怎么算，请直接跳转 Part2，如果只知道结论不知道推导，建议看一下 ~~因为里面也打了我博客的广告~~。

通过一关的时间的期望：

$$
\begin{aligned}
E
&= \frac{x}{y}\cdot 1+\frac{y-x}{y}\cdot\frac{x}{y}\cdot 2 +(\frac{y-x}{y})^2\cdot \frac{x}{y}\cdot 3 + \cdots \\
&= \frac{x}{y}[1+ 2\cdot\frac{y-x}{y} + 3\cdot(\frac{y-x}{y})^2 + 4\cdot(\frac{y-x}{y})^3 + \cdots] \\
\end{aligned}
$$

中括号里面的东西就是带系数的等比数列求和（$\sum_{k=2}^\infty k\cdot p^{k-1}$）的形式。我的[这篇博客](https://walker68145.github.io/post/gai-lu-yu-qi-wang/#%E5%BC%95%E7%90%86%E8%AF%81%E6%98%8E)给出了形如 $\sum_{k=0}^\infty p^k$ 和 $\sum_{k=0}^\infty k\cdot p^k$ 的求值，虽然不一样但是变通一下即可。可以得到：

$$
\begin{aligned}
\sum_{k=2}^\infty k\cdot p^{k-1}
&= \sum_{k=1}^\infty p^k+\sum_{l=1}^\infty\sum_{k=l}^\infty p^k \\
&= \frac{p}{1-p} + \sum_{l=1}^\infty \frac{p^l}{1-p} \\
&= \frac{p}{1-p} + \frac{p}{(1-p)^2} \\
&= \frac{p(2-p)}{(1-p)^2}
\end{aligned}
$$

$p=\frac{y-x}{y}=1-\frac{x}{y}$，代入：

$$
\begin{aligned}
E
&= \frac{x}{y}[1 + 2\cdot\frac{y-x}{y} + 3\cdot(\frac{y-x}{y})^2 + 4\cdot(\frac{y-x}{y})^3 + \cdots] \\
&= \frac{x}{y}[1 + \frac{(1-\frac{x}{y})(1+\frac{x}{y})}{(\frac{x}{y})^2}] \\
&= \frac{x}{y} + \frac{y}{x}[1-(\frac{x}{y})^2] \\
&= \frac{x}{y} + \frac{y}{x} - \frac{x}{y} \\
&= \frac{y}{x}
\end{aligned}
$$

到这里我们证得，通过一关的时间期望为 $\dfrac{\sum_{j=l_i}^i a_j}{a_i}$。

### Part2 前缀和与暴力DP

会暴力 $\operatorname{O}(n^2m)$ DP 的可以直接跳转到 Part3。

显然可以前缀和，设 $s_i=\sum_{j=1}^i a_i$，通过一关的期望就为：（注：原题用的分段指闭区间，但是为了方便前缀和后文全部用左开右闭的区间表示）$\dfrac{s_i-s_{l_i}}{a_i}$。通过一整段关的时间期望是：

$$
\begin{aligned}
\sum_{j=l_i}^{r_i} \frac{s_j-s_{l_i}}{a_j}
&= \sum_{j=l_i}^{r_i} (\frac{s_j}{a_j}-s_{l_i}\cdot\frac{1}{a_j}) \\
&= \sum_{j=l_i}^{r_i} \frac{s_j}{a_j} - s_{l_i}\sum_{j=l_i}^{r_i} \frac{1}{a_j}
\end{aligned}
$$

显然这两个都可以用前缀和，我们记录 $sa_i=\sum_{j=1}^i \frac{s_j}{a_j}$，$sb_i=\sum_{j=1}^i \frac{1}{a_j}$。

这样发现如果确定了一个分段的左右区间，整段的期望时间都可以 $\operatorname{O}(1)$ 地求出来。到这里不妨可以尝试概率 DP，设 $f_{i,j}$ 表示考虑前 $i$ 个关，且当前已经分出了 $j$ 段（显然按顺序数的第 $j$ 段右端点就是 $i$）的最优期望时间。转移时考虑当只分了 $j-1$ 段时，最后一段如何拆成两段即可。转移方程为：

$$f_{i,j}=\min_{k=1}^{i-1} \{ f_{k,j-1}+ sa_i - sa_k + sb_k\cdot s_k - sb_i\cdot s_k \}$$

把只和 $i$ 有关的提出来，为：

$$f_{i,j}=sa_i+\min_{k=1}^{i-1} \{ f_{k,j-1} - sa_k + sb_k\cdot s_k - sb_i\cdot s_k \}$$

暴力求解是 $\operatorname{O}(n^2m)$ 的。

### Part3 李超线段树

我们发现这东西很好用和斜率相关的东西维护。~~我知道你们都用斜率优化吊打我了但是我还是要写李超~~。而最小值函数里面的一陀东西，只有一项和 $i$ 有关，这更加确定了这题可以不用任何骚操作就能李超优化。

我们考虑把 $-s_k$ 当作斜率，$f_{k,j-1} - sa_k + sb_k\cdot s_k$ 当作截距。原转移的最小值函数里面就是一个 $kx+b$ 的形式了。查询这个东西的最小值，不就是查询一条 $x=sb_i$ 的直线，和这些直线交点的最小值吗？

直接李超线段树维护上述的直线即可。但是如果你不幸地 WA 在了第 11 个数据点，明显是因为精度误差爆掉了。（CF 数据上前 10 个点里面还有一个 $n\approx 10^3$ 的，没有挂的话转移基本没问题了）换句话说我们不得不面对**动态开点的李超线段树存在较大的精度误差**的问题。

其实动态开点的李超线段树不过就是做到了空间复杂度和直线数量（一般就是 $n$）同级。考虑到如果改成普通的线段树，就会出现 $nm\cdot 4$ 的尴尬空间复杂度，稳稳地 MLE（为了方便值域的 $10^6$ 我就也写成 $n$ 了）。

一个显而易见的方法可以解决这类问题，考虑到 DP 的状态转移中，对于任意的 $f_{i,j}$，它只由 $f_{k,j-1}$ 的状态转移过来，可以进行滚动数组优化。李超线段树也跟着滚动一下，空间复杂度优化至 $n\cdot 8$，精度是不容易卡的，这就十分稳定能过了。

接下来考虑第二个问题：不动态开点的李超线段树处理精度问题，一般会需要提前把要查询的浮点数离散化，然后查询，比如这样：

```cpp
f[i][now]=s1[i]+seg[now].ask(1,1,n,lower_bound(s2+1,s2+1+n,c[i])-s2);
// 这就是我交的 TLE on #52 的代码的转移
```

虽然找到离散化后对应的数是 $\log n$，李超线段树也是 $\log n$，但是考虑到他还是 STL，我写的李超线段树也人傻常数大，需要简单改一下：

```cpp
for(register int i=1;i<=n;++i)
	pos[i]=lower_bound(s2+1,s2+1+n,c[i])-s2;
...... // 中间省略部分语句
f[i][now]=s1[i]+seg[now].ask(1,1,n,pos[i]);
```

这样就卡过去了，最慢的点差不多 2500ms，理论的时间复杂度是 $nm\log n$ 级别，相对来说还可以。

### Part4 代码

 
 ```cpp
#include<cstdio>
#include<algorithm>
#define int long long // 要开 long long！
using namespace std;
const int max_n=1000005,inf=1000000000000000LL;
inline int read(){
	int x=0;bool w=0;char c=getchar();
	while(c<'0' || c>'9') w|=c=='-',c=getchar();
	while(c>='0' && c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return w?-x:x;
}
inline int min(int a,int b){return a<b?a:b;}

int n,m,a[max_n],s[max_n];

double s1[max_n],s2[max_n];

struct LiChao{ // 不动态开点李超
	int p[max_n*4];
	#define ls(x) (x<<1)
	#define rs(x) (x<<1|1)

	double b[max_n],k[max_n];

	inline double slp(int j,int i){return b[i]+s2[j]*k[i];}
    // 计算 x=s2[j] 时直线的 y 值。不是算斜率

	inline void add(int x,int l,int r,int t){
		if(l==r){
			if(slp(l,t)<slp(l,p[x]))
				p[x]=t;
			return;
		}
		int mid=(l+r)>>1;
		if(slp(mid,t)<slp(mid,p[x]))
			t^=p[x]^=t^=p[x];
	
		if(slp(l,t)<slp(l,p[x])) add(ls(x),l,mid,t);
		else if(slp(r,t)<slp(r,p[x])) add(rs(x),mid+1,r,t);
	}
	inline double ask(int x,int l,int r,int t){
		if(!x) return 0;
		double res=slp(t,p[x]);
		if(l==r) return res;
		int mid=(l+r)>>1;
		if(t<=mid) return min(res,ask(ls(x),l,mid,t));
		return min(res,ask(rs(x),mid+1,r,t));
	}
	inline void clear(){ // 清空线段树，状压用
		for(register int i=0;i<=n;++i)
			k[i]=b[i]=p[i]=0;
	}
	#undef ls
	#undef rs
}seg[2]; // 滚动数组压在李超上

double f[max_n][2]; // 滚动 j 
double c[max_n];
int pos[max_n];

signed main(){
	n=read(),m=read();
	for(register int i=1;i<=n;++i){
		a[i]=read();
		s[i]=s[i-1]+a[i]; // s 即题解的 s
		s1[i]=1.0*s[i]/a[i], // s1 即题解的 sa
		s2[i]=1.0/a[i]; // s2 即题解的 sb
	}
	for(register int i=1;i<=n;++i){
		s1[i]+=s1[i-1],
		s2[i]+=s2[i-1];
		c[i]=s2[i]; // c 数组用于离散化
	}
	sort(s2+1,s2+1+n);
	for(register int i=1;i<=n;++i)
		f[i][0]=inf; // 初始化，分成 0 段是不合法的
	for(register int i=1;i<=n;++i)
		pos[i]=lower_bound(s2+1,s2+1+n,c[i])-s2;
	for(register int j=1,now=1;j<=m;++j,now^=1){
		seg[now].clear(); // 滚动掉过去的状态
		for(register int i=1;i<=n;++i){
			f[i][now]=s1[i]+seg[now].ask(1,1,n,pos[i]);

			seg[now].k[i]=-1.0*s[i];
			seg[now].b[i]=s2[i]*s[i]-s1[i]+f[i][now^1];
			seg[now].add(1,1,n,i);
		}
	}
	printf("%.10lf",f[n][m&1]);
	return 0;
}
```

#### upd

DP 转移式写错了，已经改好；修正错别字，删除代码冗杂注释。

---

## 作者：whiteqwq (赞：4)

[CF643C Levels and Regions](https://www.luogu.com.cn/problem/CF643C)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1740106)

## 题意
- 给定$n$个关卡$a_1\cdots a_n$，将这些关卡分成$m$段。
- 若第$i$段为$[l_i,r_i]$，那么对于$j\in[l_i,r_i]$，$1$小时通过$j$关卡的概率为$\frac{a_j}{\sum_{k=l_i}^j a_k}$。
- 求通过所有关卡的最少期望答案是多少个小时。
- 数据范围：$1\leqslant n\leqslant 200000,1\leqslant m\leqslant \min\{50,n\}$。

## 分析
比较好的dp题，把期望和斜率优化结合起来了。

首先，既然$1$小时通过$j$关卡的概率为$\frac{a_j}{\sum_{k=l_i}^j a_k}$，那么$j$关卡期望$\frac{\sum_{k=l_i}^j a_k}{a_j}$个小时通过，设$suma$为$a$的前缀和，那么$j$关卡期望$\frac{suma_j-suma_{l_i-1}}{a_j}$个小时通过。

然后，对于每一段$[l_i,r_i]$，它的期望为
$$\sum_{j=l_i}^{r_i}\frac{suma_j-suma_{l_i-1}}{a_j}$$

这里为了方便，我们把这一段改为$(k,r_i]$，即$k=l_i-1$。这样它的期望就是
$$\sum_{j=k+1}^{r_i}\frac{suma_j-suma_k}{a_j}=\sum_{j=k+1}^{r_i}(\frac{suma_j}{a_j}-\frac{suma_k}{a_j})=\sum_{j=k+1}^{r_i}\frac{suma_j}{a_j}-suma_k\sum_{j=k+1}^{r_i}\frac{1}{a_j}$$

我们设$b_i=\frac{1}{a_i}$，$sumb$为$b$的前缀和；$c_i=\frac{suma_i}{a_i}$，$sumc$为$c$的前缀和。

这一段的期望可以直接改为
$$sumc_{r_i}-sumc_k-suma_k\cdot(sumb_{r_i}-sumb_k)$$

然后开始dp，我们设$f_{i,j}$为从关卡$1$处理到关卡$j$，分$i$段的最小期望。

那么很显然有转移：$f_{i,j}=\min_{k=1}^{j-1}\{f_{i-1,k}+sumc_j-sumc_k-suma_k\cdot(sumb_j-sumb_k)\}$。

看到这个式子存在项$-suma_k\cdot sumb_j$，果断选择斜率优化。

设当时处理到$i$段，且存在两个$j$的决策点$x,y$满足$y<x<j$，且$x$比$y$优，那么有：

$$f_{i-1,x}+sumc_j-sumc_x-suma_x\cdot(sumb_j-sumb_x)\leqslant f_{i-1,y}+sumc_j-sumc_y-suma_y\cdot(sumb_j-sumb_y)$$

然后拆括号，移项：

$$(f_{i-1,x}-sumc_x+suma_x\cdot sumb_x)-(f_{i-1,y}-sumc_y+suma_y\cdot sumb_y)\leqslant suma_x\cdot sumb_j-suma_y\cdot sumb_j$$

因为$x>y$，所以$suma_x-suma_y>0$，所以可以两边同除$suma_x-suma_y$，不变号：

$$\frac{(f_{i-1,x}-sumc_x+suma_x\cdot sumb_x)-(f_{i-1,y}-sumc_y+suma_y\cdot sumb_y)}{suma_x-suma_y}\leqslant sumb_j$$

把$suma_k$看成$x$坐标，把$f_{i-1,k}-sumc_k+suma_k\cdot sumb_k$看成$y$坐标，这就是一个斜率的形式，直接上斜率优化板子就好了。

注意，因为这里是小于号，综合分析后应该取下凸壳。

时间复杂度：$O(nm)$，可以通过本题。
## 代码
```
#include<stdio.h>
#include<queue>
#define int long long
#define inf 10000000000000000
using namespace std;
const int maxn=200005,maxm=55;
int i,j,k,m,n,l,r;
int a[maxn],suma[maxn],q[maxn];
double b[maxn],c[maxn],sumb[maxn],sumc[maxn],f[maxm][maxn];
inline int x(int p){
	return suma[p];
}
inline double y(int p,int c){
	return f[c-1][p]+1.0*suma[p]*sumb[p]-sumc[p];
}
inline double slope(int a,int b,int c){
	if(x(a)==x(b))
		return y(a,c)>y(b,c)? inf:-inf;
	return 1.0*(y(a,c)-y(b,c))/(x(a)-x(b));
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		suma[i]=suma[i-1]+a[i];
		b[i]=1.0/a[i],sumb[i]=sumb[i-1]+b[i];
		c[i]=1.0*suma[i]/a[i],sumc[i]=sumc[i-1]+c[i];
	}
	for(i=1;i<=n;i++)
		f[0][i]=inf;
	for(i=1;i<=m;i++){
		l=1,r=0;
		q[++r]=0;
		for(j=1;j<=n;j++){
			while(l<r&&slope(q[l+1],q[l],i)<=sumb[j])
				l++;
			f[i][j]=f[i-1][q[l]]+sumc[j]-sumc[q[l]]-suma[q[l]]*(sumb[j]-sumb[q[l]]);
			while(l<r&&slope(j,q[r-1],i)<=slope(q[r],q[r-1],i))
				r--;
			q[++r]=j;
		}
	}
	printf("%.10lf\n",f[m][n]);
	return 0;
}
```

---

## 作者：EityDawn (赞：3)

## 思路：

第一次完全自己做出期望题，写题解纪念之。

首先，每个位置的期望要推出来，需要一点数列知识。

设 $a=\sum_{x=l_i}^it_x,b=t_i$，则 $E_i(X)=b\sum_{i=1}^{\infty}{i(a-b)^{i-1}\over a^i}$。

我们设数列 $c_{n}={n(a-b)^{n-1}\over a^n}$，$S_n$ 为 $c_n$ 的前 $n$ 项和，$S_n={1\over a}+{2(a-b)\over a^2}+{3(a-b)^2\over a^3}+...+{n(a-b)^{n-1}\over a^n}$。

则 ${a-b\over a}S_{n}={(a-b)\over a^2}+{2(a-b)^2\over a^3}+...+{(n-1)(a-b)^{n-1}\over a^n}+{n(a-b)^n\over a^n}$，两式相减得 

$$
\begin{align}{b\over a}S_{n}&={1\over a}+{(a-b)\over a^2}+{(a-b)^2\over a^3}+...+{(a-b)^{n-1}\over a^n}-{n(a-b)^n\over a^{n+1}}\\&=\{{{1\over a}[1-({a-b\over a})^n]\over 1-{a-b \over a}}-{n(a-b)^n\over a^{n+1}}\}\end{align}
$$
再化一下简，得 $S_n={a[1-({a-b\over a})^n]\over b^2}-n({a-b\over a})^n$，而 ${a-b\over a}<1$，则当 $n\rightarrow \infty$，$({a-b\over a})^n=0$，所以 $S_n={a\over b^2}$。

那么期望 $E_i(X)={a\over b}$，即 $E_i(X)={\sum_{x=l_i}^it_x\over t_i}={\sum_{x=1}^it_x\over t_i}-{1\over t_i}\sum_{x=1}^{l_i}t_i$。

那么我们可以通过 $t_i$ 的前缀和，${\sum_{x=l_i}^it_x\over t_i}$ 的前缀和以及 ${1\over t_i}$ 的前缀和 $O(1)$ 求出区间 $[l,r]$ 的期望，分别记为 $suma_i,sumb_i,sumc_i$。

定义 $f_{i,j}$ 为前 $i$ 个位置分成了 $j$ 段，期望的最小值。

我们定义一个区间的期望和为 $w(l,r)=sumb_r-sumb_{l-1}-suma_{l-1}\times(sumc_{r}-sumc_{l-1})$。

则 $f_{i,j}=\min(f_{k,j-1}+w(k+1,i))$。

这里证明 $w(l,r+1)+w(l+1,r)≥w(l,r)+w(l+1,r+1)$。

移项得 $w(l,r+1)-w(l,r)\ge w(l+1,r+1)-w(l+1,r)$，代入得 $sumb_{r+1}-sumb_{r}-suma_{l-1}\times(sumc_{r+1}-sumc_{r})\ge sumb_{r+1}-sumb_{r}-suma_{l}\times(sumc_{r+1}-sumc_{r})$。

显然有 $suma_{l-1}\le suma_l$，故转移方程满足决策单调性，可以分治求解。

时间复杂度为 $O(nk\log n)$。

### code

```cpp
const int N=2e5+10;
double f[N][51];
int n,k;
ll a[N],suma[N];
double b[N],c[N],sumb[N],sumc[N];
int now=0;
void solve(int l,int r,int lt,int rt)
{
	int mid=(l+r)>>1,L=max(0,lt),R=min(rt,mid-1);
	double Res=1e18;int pos=0;
	for(int i=L;i<=R;i++)
	{
		double tmp=f[i][now-1]+sumb[mid]-sumb[i]-suma[i]*(sumc[mid]-sumc[i]);
		if(tmp<Res) Res=tmp,pos=i;
	}
	f[mid][now]=Res;
	if(l==r) return;
	solve(l,mid,lt,pos),solve(mid+1,r,pos,rt);
}
int main()
{
	read(n,k);
	for(int i=1;i<=n;i++) 
	{
		read(a[i]),suma[i]=suma[i-1]+a[i];
		c[i]=1.0/a[i],sumc[i]=sumc[i-1]+c[i];
		b[i]=1.0*suma[i]/a[i],sumb[i]=sumb[i-1]+b[i];
	}
	for(int i=0;i<=n;i++)
		for(int j=0;j<=k;j++) f[i][j]=1e18;
	f[0][0]=0;
	for(now=1;now<=k;now++) solve(0,n,0,n);
	write(f[n][k]);
    return 0;
}
```

---

## 作者：Skyjoy (赞：3)

挺简单的一道 dp 题目。

# 思路

显然我们可以考虑朴素的 dp 。我们令$f_{i,j}$ 表示当前考虑到 $j$ 级别且改级别以第 $i$ 个关卡为结尾的答案。我们可以得到一个最最朴素的 dp 柿子：

$$
f_{i,j}=\min_{1\le k\le i-1}f_{k,j-1}+\sum_{p=k+1}^{i}\frac{\sum_{x=k+1}^{p}t_x}{t_p}
$$

前缀和优化，令 $sum_x=\sum_{i=1}^{x}t_i$ ，则有：

$$
f_{i,j}=\min{f_{k,j-1}+\sum_{p=k+1}^{i}\frac{sum_{p}-sum_{k}}{t_p}}
$$
$$
=\min{f_{k,j-1}+\sum_{p=k+1}^{i}(\frac{sum_p}{t_p}}-\frac{sum_k}{t_p})
$$

继续前缀和优化，令 $S_x=\sum_{i=1}^{x}\frac{sum_i}{t_i}$ ， $T_x=\sum_{i=1}^{x}\frac{1}{t_i}$

则有：

$$
f_{i,j}=\min{f_{k,j-1}+S_i-S_k-sum_k\cdot(T_i-T_k)}
$$

现在复杂度是 $O(n^2m)$ ，无法通过此题。接下来我们该怎么优化呢？

我们把上式中所有和 $i$ 无关的东西移到一边，可以得到：

$$
f_{k,j-1}-S_k+sum_k\cdot T_k=T_i\cdot sum_k+f_{i,j}-S_i
$$

显然可以考虑斜率优化。我们对于直线斜截式 $y=kx+b$ ，我们令 $y=f_{k,j-1}-S_k+sum_k\cdot T_k$ ， $k=T_i$ ， $x=sum_k$ ， $b=f_{i,j}-S_i$ 。因为在每一次更新答案时，直线斜率是单调递增的，我们求的也是直线截距的最小值，所以我们可以套路地使用单调队列维护决策点所组成的下凸壳。这样复杂度就变成了 $O(nm)$ ，可以通过此题。

# 代码

```cpp
#include<bits/stdc++.h>
#define I using
#define love namespace
#define Elaina std
#define ll long long
I love Elaina;
const int N=200010;
const int M=60;
ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
ll n,m,t[N],sum[N],head,tail,cur,q[N];
double S[N],T[N],f[N][M];
double X(ll x){
	return sum[x];
}
double Y(ll x){
	return f[x][cur]-S[x]+sum[x]*T[x];
}
double slope(ll x,ll y){
	return (Y(x)-Y(y))/(X(x)-X(y));
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		t[i]=read(),sum[i]=sum[i-1]+t[i];
		S[i]=S[i-1]+(double)sum[i]/t[i],T[i]=T[i-1]+(double)1.0/t[i];
	}
	for(int i=1;i<=n;i++)f[i][1]=S[i];
	for(int i=2;i<=m;i++){
		cur=i-1,head=1,tail=0;
		for(int j=1;j<=n;j++){
			while(head<tail&&slope(q[head],q[head+1])<T[j])head++;
			f[j][i]=f[q[head]][i-1]+S[j]-S[q[head]]-sum[q[head]]*(T[j]-T[q[head]]);
			while(head<tail&&slope(q[tail-1],q[tail])>slope(q[tail],j))tail--;
			q[++tail]=j;
		}
	}
	printf("%lf",f[n][m]);
	return 0;
}
```
祝各位大神们 NOI 加油！

---

## 作者：kkkk0369 (赞：3)

题意：将$n$个数分成$k$组，对于任意一组取其中第$i$个数的概率为$t[k]/∑t[k]$，求分组后取完所有数的最小期望。

看到这道题第一反应就是动态规划……

$f[i][j]$表示把前$j$位分成$i$组所能最大优化的期望。

用$s[i]$记录$t[i]$前缀和，用$p[i]$记录$t[i]$倒数的前缀和。

于是得到DP方程：$f[i][j]=max(f[i-1][k]+s[k]*(p[j]-p[k]))$

关于DP方程作出如下解释：

1.第$i$组的状态只与第$i-1$组有关，需在第二维枚举$k$找最优解；

2.由于取第$i$组中第$k$个数的概率为$t[k]/s[k]$,期望为$s[k]/t[k]$,则分组后“被优化”的期望为$s[k]*(p[j]-p[k])$

我们发现这样写肯定要超时，由于方程中仅有$max$函数，我们想到使用斜率优化加速。

考虑$f[i][a]$和$f[i][b]$的值，设$f[i][a]>f[i][b]$，

则可得到$f[i-1][a]+s[a]*(p[j]-p[a])>f[i-1][b]+s[b]*(p[j]-p[b])$

设$f[i-1][a]-s[a]*p[a]=y(a)$，

拆项移项得到$y(a)-y(b)<(s[b]-s[a])*p[j]$，

优化式得到，剩下的就是实现了。

以下是AC代码（依然有疑问的来找本蒟蒻问吧）：

```cpp
#include<cstdio>
using namespace std;
int n,k,h,r;
long long t[200010],q[200010];
long long s[200010];
double p[200010];
double f[60][200010];
double ans,tot;//tot用于统计最劣期望值，即一组都不分
double v(long long x,long long y,int i)//斜率优化式
{
	return (f[i-1][x]-s[x]*p[x]-f[i-1][y]+s[y]*p[y])*1./(s[y]-s[x]);
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&t[i]);s[i]=s[i-1]+t[i];//前缀和
		p[i]=p[i-1]+1./t[i];tot+=s[i]*1./t[i];//倒数前缀和
	}
	for(int i=2;i<=k;i++)//这层放到外面
	{
		h=0;r=0;//队列清空
		for(int j=1;j<=n;j++)
		{
			while(h<r&&v(q[h],q[h+1],i)<p[j]) h++;
			while(h<r&&v(q[r-1],q[r],i)>v(q[r],j,i)) r--;
			f[i][j]=f[i-1][q[h]]+s[q[h]]*(p[j]-p[q[h]]);//DP方程
			q[++r]=j;//以上是斜率优化基本操作
		}
	}
	ans=tot-f[k][n];//f[k][n]即为最优解
	printf("%.10lf",ans);
	return 0;
}
```

---

## 作者：World_Creater (赞：2)

有人模拟赛消愁了，没想到 $\mathcal{O}(nm)$ 写了 $\mathcal{O}(nm\log n)$ 没卡进一秒（模拟赛的时限）。

首先某个点的期望次数等于概率的倒数，这样可以直接把每个点的贡献算出来。

记 $\operatorname{cost}(i,j)$ 为将 $[i,j]$ 划分为连续一段的贡献。

根据题意可以通过前缀和将柿子转化成：

$$\operatorname{cost}(i,j)=\sum_{t=i}^j \frac{pre_t-pre_{i-1}}{a_i}$$

$\operatorname{cost}(i,j)$ 可以 $\mathcal{O}(1)$ 转移到 $\operatorname{cost}(i\pm 1,j\pm 1)$。

并且这个柿子满足四边形不等式。

证明可以考虑下面的图里，红色蓝色贡献相等，而绿色部分小于橙色部分（橙色部分所对应的分子更大），因此相交小于包含。

![](https://cdn.luogu.com.cn/upload/image_hosting/ds8kj329.png)

因此 dp 柿子：$f(i,j)=\displaystyle{\operatorname{min}_{1\leq k<i}} f(k,j-1)+\operatorname{cost}(k+1,i)$ 可以使用决策单调性优化，用分治实现，复杂度 $\mathcal{O}(nm\log n)$。

代码可能有些地方小小卡了点常。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef double db;
db f[2][200005];
int n,k,a[200005];
db res,inv,t[200005];
long long sum;
int l=1,r;
inline void add1(const int &x)
{
	sum+=a[x];
	inv+=t[x];
	res+=sum*t[x];
}
inline void del1(const int &x)
{
	res-=sum*t[x];
	sum-=a[x];
	inv-=t[x];
}
inline void add2(const int &x)
{
	res+=inv*a[x]+1;
	sum+=a[x];
	inv+=t[x];
}
inline void del2(const int &x)
{
	res-=a[x]*inv;
	sum-=a[x];
	inv-=t[x];
}
inline db calc(const int &ql,const int &qr)
{
	// cerr<<ql<<" "<<qr<<"\n";
	while(l>ql) add2(--l);
	while(r<qr) add1(++r);
	while(l<ql) del2(l++);
	while(r>qr) del1(r--);
	return res;
}
inline void solve(const int &l,const int &r,const int &L,const int &R,const bool &t)
{
	if(l>r||L>R) return ;
	int mid=(l+r)>>1;
	pair<db,int> minn={1e15+5,0};
	for(int i=min(mid-1,R);i>=L;i--)
	{
		// cerr<<"???"<<t<<" "<<i<<" "<<mid<<" "<<f[i][t-1]+calc(i+1,mid)<<" "<<sum<<"\n";
		minn=min(minn,{f[!t][i]+calc(i+1,mid),i});
	}
	f[t][mid]=minn.first;
	// cerr<<mid<<" "<<t<<" "<<minn.second<<"\n";
	solve(l,mid-1,L,minn.second,t);
	solve(mid+1,r,minn.second,R,t);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		t[i]=1.0/a[i];
	}
	for(int i=1;i<=n;i++)
	{
		f[1][i]=calc(1,i);
	}
	for(int i=2;i<=k;i++)
	{
		solve(i,n,i-1,n,i&1);
	}
	cout<<fixed<<setprecision(12)<<f[k&1][n];
}
```

---

## 作者：hzlqwq (赞：1)

## CF643C Levels and Regions

不知道为什么，反正很喜欢这题，可能是因为这是第一道从头到尾自己做出来的概率论+斜率优化 dp 吧，遂作详细题解一篇供众大佬参考。

---

想要算总期望时间，首先我们需要求出单个关卡期望时间的表达式。设某关卡的通关概率为 $p$，则期望时间为：

$$
1\times p+2\times p(1-p)+3\times p(1-p)^2+4\times p(1-p)^3+\cdots
$$

即：

$$
p\left[1+2(1-p)+3(1-p)^2+4(1-p)^3+\cdots\right]
$$

即每种情况的**时间** $\times$ **前面都未通关但在此通关的概率**。

借助**错位相减法**的思路，若设上式中括号内的和为 $S$，则：

$$
(1-p)S=1-p+2(1-p)^2+3(1-p)^3+4(1-p)^4+\cdots
$$

用 $S$ 减去 $(1-p)S$，得：

$$
S-(1-p)S=pS=1+(1-p)+(1-p)^2+(1-p)^3+\cdots
$$

注意看，$pS$ 不就是我们一开始的原式吗！于是我们得到了原式的等比数列求和的形式！套用[等比数列求和公式](https://baike.baidu.com/item/%E7%AD%89%E6%AF%94%E6%95%B0%E5%88%97%E6%B1%82%E5%92%8C%E5%85%AC%E5%BC%8F/7527367?fr=ge_ala#2-3)（即再做一遍错位相减法）可得，期望时间为：

$$
\frac{1}{p}
$$

---

带回原式中，则关卡 $i$ 的期望时间为 $\displaystyle \frac{\sum_{x=l_j}^{i} t_x}{t_i}$。借助前缀和化简和式：令 $s_i$ 表示 $\displaystyle \sum_{x=1}^{i} t_x$，则原式 $=\displaystyle \frac{s_i-s_{l_j-1}}{t_i}$。

不难发现，原问题可以用 dp 求解：若令 $f_{i,j}$ 表示以第 $i$ 个关卡作为第 $j$ 个级别的末尾，前 $i$ 个游戏的最短 AK 时间，可以枚举上一个区间的末尾 $k$ 转移：

$$
f_{i,j}=\min_{k<i} f_{k,j-1}+\sum_{x=k+1}^{i} \frac{s_x-s_k}{t_x}
$$

借助前缀和化简和式：令 $\displaystyle x_i=\sum_{j=1}^{i} \frac{s_j}{t_j}$，$\displaystyle y_i=\sum_{j=1}^{i} \frac{1}{t_j}$，则：

$$
f_{i,j}=\min_{k<i} f_{k,j-1}+x_i-x_k-s_k(y_i-y_k)
$$

有点斜率优化的感觉，试试：若从 $a$ 转移而来（即 $k=a$）比从 $b$ 转移而来优，且 $a>b$（即 $a$ 在 $b$ 后面），则：

$$
f_{a}+x_i-x_a-s_a(y_i-y_a)<f_{b}+x_i-x_b-s_b(y_i-y_b)
$$

化简得：

$$
\frac{(f_a-x_a+y_a s_a)-(f_b-x_b+y_b s_b)}{s_a-s_b}<y_i
$$

$(f_a-x_a+y_a s_a)$，$s_a$ 与 $y_i$ 都是单调递增的，可以斜率优化 dp 做，具体参见[斜率优化 dp 模板题](https://www.luogu.com.cn/problem/P2365)，单调队列维护下凸壳即可。

转移被优化成了 $O(1)$ 的，总时间复杂度 $O(nk)$。

注意 dp 数组的一些初始化细节。

```cpp
#define front q.front()
#define back q.back()
#define sfront *(q.begin() + 1)
#define sback *(q.rbegin() + 1)
#define size q.size()
#define Y(p, t) (f[p][t] - x[p] + y[p] * s[p])

using namespace std;

const int N = 2e5 + 5, K = 55;

int n, k, t[N];
double s[N], x[N], y[N], f[N][K];
deque<int> q;

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> t[i], s[i] = s[i - 1] + t[i], x[i] = x[i - 1] + s[i] / t[i], y[i] = y[i - 1] + 1.0 / t[i],
                     f[i][0] = 1e18;
    for (int j = 1; j <= k; j++)
    {
        q.clear(), q.push_back(0), f[0][j] = 1e18;
        for (int i = 1; i <= n; i++)
        {
            while (size > 1 && Y(front, j - 1) - Y(sfront, j - 1) > y[i] * (s[front] - s[sfront]))
                q.pop_front();
            f[i][j] = f[front][j - 1] + x[i] - x[front] - s[front] * (y[i] - y[front]);
            while (size > 1 && (Y(back, j - 1) - Y(sback, j - 1)) / (s[back] - s[sback]) >
                                   (Y(i, j - 1) - Y(back, j - 1)) / (s[i] - s[back]))
                q.pop_back();
            q.push_back(i);
        }
    }
    cout << f[n][k] << "\n";
    return 0;
}
```


---

## 作者：az__eg (赞：1)

斜率优化板子，顺带复习一下。

首先我们先得知道期望怎么算。

$f_i$ 表示赢了 $i$ 场，还需要赢几场的期望数。

初始状态：

$$f_{n+1} = 0$$

然后考虑转移方程：

$p_i$ 表示第 $i$ 场赢的概率。

$$f_{i} = p_if_{i+1} + (1-p_i)f_{i} + 1$$

$$f_i = f_{i+1} + \frac{1}{p_i}$$

所以期望等于 $\sum\limits^n_{i=1}\frac{1}{p_i}$。

设 $sum_i=\sum\limits^i_{j=1}a_j$，$l_i$ 表示 $i$ 所在区间的左端点。

$$p_i = \frac{a_i}{\sum\limits^i_{j={l_i}}a_j}=\frac{a_i}{sum_i - sum_{l_i-1}}$$

所以期望等于 $\sum\limits_{i=1}^n \frac{sum_i - sum_{{l_i}-1}}{a_i}$。

我们希望它尽量小。

分解一下：

$$\sum\limits^n_{i=1}\frac{sum_i}{a_i} - \sum\limits^n_{i=1}\frac{sum_{{l_i}-1}}{a_i}$$

前面不变，所以要求 $\sum\limits^n_{i=1}\frac{sum_{{l_i}-1}}{a_i}$ 最大。

$dp_{i,j}$ 表示考虑到前 $i$ 个，分了 $j$ 段以后最大的上式。

设 $sum2_i = \sum\limits^i_j \frac{1}{a_j}$。

$dp_{i,j} = \max\limits^{i-1}_{l=0}(dp_{l,j-1}-sum_l\times sum2_l+ sum_l\times sum2_i)$

发现这个式子非常容易斜率优化。

斜率优化一下即可。

每个点为 $(sum_l,dp_{l,j-1}-sum_l\times sum2_l)$。

斜率为 $-sum2_i$。

然后就可以维护上凸包了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const double INF = 1e100;
int n,k;
int a[200001];
double sum[200001];
double sum2[200001];
double dp[200001];
double lst[200001];
int q[200001];
void read(int &x)
{
	x=0;char s=getchar();
	while(s<'0'||s>'9')s=getchar();
	while(s>='0'&&s<='9')x=x*10+s-'0',s=getchar();
}
double x(int i)
{
	return sum[i];
}
double y(int i)
{
	return lst[i]-sum[i]*sum2[i];
}
double slope(int i,int j)
{
	return (y(i)-y(j))/(x(i)-x(j));
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	read(n),read(k);
	int i,j,l;
	for(i=1;i<=n;i++)
	{
		read(a[i]);
		sum[i]=a[i]+sum[i-1];
		sum2[i]=1.0/a[i]+sum2[i-1]; 
	}
	for(i=1;i<=n;i++)
	{
		dp[i]=0;
	}
	for(i=2;i<=k;i++)
	{
		for(j=1;j<=n;j++)
		{
			lst[j]=dp[j];
		}
		int l=1,r=0;
		for(j=1;j<=n;j++)
		{
			while(l<r&&slope(q[r-1],q[r])<=slope(q[r-1],j))
			--r;
			q[++r]=j;
			while(l<r&&slope(q[l],q[l+1])>=-sum2[j])
			++l;
			dp[j]=lst[q[l]]+sum[q[l]]*(sum2[j]-sum2[q[l]]);
		}
	}
	double ans=0;
	for(i=1;i<=n;i++)
	{
		ans+=sum[i]/a[i];
	}
	cout<<fixed<<setprecision(10)<<ans-dp[n]; 
}
```




---

## 作者：Iniaugoty (赞：0)

>有 $n$ 个有序的"关卡"，将它们分为 $k$ 个连续段。设第 $i$ 个“关卡”所在连续段左端点为 $l$，则一次通过这关的概率为 $\frac {t _ i} {\sum _ {j = l} ^ {i} t _ j}$，如果一次没通过还要继续尝试直到通过。最小化按顺序通过所有“关卡”的期望时间。

设一次通过某个关卡的概率为 P，通过它的期望时间为 $E$。

如果第一次就通过，则只尝试一次；否则，浪费了这一次，后面还要重复尝试。所以

$$E = P + (1 - P)(1 + E)$$

整理得

$$E = \frac {1} {P}$$

于是我们知道通过第 $i$ 关的期望时间为 $\frac {\sum _ {j = l} ^ {i} t _ j} {t _ i}$。

不妨先把 $k$ 个连续段的要求去掉，然后考虑 DP。

设 $dp _ {i}$ 表示将前 $i$ 个关卡划分为若干个连续段的最小期望时间。枚举上一个连续段的右端点进行转移。则有

$$dp _ {i} = \min _ {j = 0} ^ {i - 1} \{ dp _ j + \sum _ {k = j + 1} ^ {i} \frac {\sum _ {l = j + 1} ^ {k} t _ l} {t _ k} \}$$

方程中有两个 $\sum$ 就很难看，我们一个一个化掉。

设 $s _ i = \sum _ {j = 1} ^ {i} t _ j$。则

$$dp _ {i} = \min _ {j = 0} ^ {i - 1} \{ dp _ j + \sum _ {k = j + 1} ^ {i} \frac {s _ k - s _ j} {t _ k} \}$$

即

$$dp _ {i} = \min _ {j = 0} ^ {i - 1} \{ dp _ j + \sum _ {k = j + 1} ^ {i} \frac {s _ k} {t _ k} - s _ j \sum _ {k = j + 1} ^ {i} \frac {1} {t _ k} \}$$

再设 $u _ i = \sum _ {j = 1} ^ {i} \frac {s _ j} {t _ j}$，$v _ i = \sum _ {j = 1} ^ {i} \frac {1} {t _ j}$。则

$$dp _ {i} = \min _ {j = 0} ^ {i - 1} \{ dp _ j + u _ i - u _ j - s _ j v _ i + s _ j v _ j \}$$

很斜率优化的形式啊。我们进行一些变形，可以得到

$$dp _ j - u _ j + s _ j v _ j = v _ i s _ j + dp _ i - u _ i$$

其中，$dp _ j - u _ j + s _ j v _ j$ 是 $y$，$v _ i$ 是斜率 $k$，$s _ j$ 是 $x$，$dp _ i - u _ i$ 是截距 $b$。

由于前缀和可以知道 $x$ 和 $k$ 都是上升的。同时，求最小值，最小化截距，考虑使用单调队列维护下凸壳。

再加上一维连续段数量 $k$ 之后也是容易的。

时间复杂度 $O(n k)$。

实现上注意 $eps$ 值设小一点。

[code](https://codeforces.com/contest/643/submission/270628166)。

***

另外，那个 DP 的形式也可能可以决策单调性分治，划分 $k$ 个连续段也可能可以 wqs 二分处理。~~但我不会证四边形不等式和函数凸性。~~

---

## 作者：tder (赞：0)

这里主要讲一下思维部分，实现部分请参考 [P3195 [HNOI2008] 玩具装箱](https://www.luogu.com.cn/problem/P3195)。

---

约定：

- $\text{sumt}_i=\sum_{j=1}^it_j$；
- $t'_i=\frac1{t'_i}$ 且 $\text{sumt}'_i=\sum_{j=1}^i{t'_j}$；
- $d_i=\frac{\text{sumt}_i}{t_i}=\text{sumt}_i\times t'_i$ 且 $\text{sumd}_i=\sum_{j=1}^id_j$。

对于第 $i$ 个关卡，有 $\dfrac{t_i}{\sum_{x=l_j}^{i}t_x}$ 的概率在 $1$ 小时内通过，即期望需要 $T_i=\dfrac{\sum_{x=l_j}^{i}t_x}{t_i}=\dfrac{\text{sumt}_i-\text{sumt}_{l_j-1}}{t_i}$ 个小时通过。

对于第 $i$ 个级别，共需 $\sum_{j=l_i}^{r_i}T_i$ 个小时通过。进行一些变换，有：

$$
\begin{aligned}
\sum_{j=l_i}^{r_i}T_i&=\sum_{j=l_i}^{r_i}\dfrac{\text{sumt}_j-\text{sumt}_{l_i-1}}{t_j} \\
&=\sum_{j=l_i}^{r_i}\left(\dfrac{\text{sumt}_j}{t_j}-\dfrac{\text{sumt}_{l_i-1}}{t_j}\right) \\
&=\left(\sum_{j=l_i}^{r_i}\dfrac{\text{sumt}_j}{t_j}\right)-\left(\sum_{j=l_i}^{r_i}\dfrac{\text{sumt}_{l_i-1}}{t_j}\right) \\
&=\left(\sum_{j=l_i}^{r_i}\dfrac{\text{sumt}_j}{t_j}\right)-\left(\text{sumt}_{l_i-1}\times\sum_{j=l_i}^{r_i}\dfrac{1}{t_j}\right) \\
&=\left(\sum_{j=l_i}^{r_i}d_j\right)-\left(\text{sumt}_{l_i-1}\times\sum_{j=l_i}^{r_i}t'_j\right) \\
&=\left(\text{sumd}_{r_i}-\text{sumd}_{l_i-1}\right)-\left(\text{sumt}_{l_i-1}\times\left(\text{sumt}'_{r_i}-\text{sumt}'_{l_i-1}\right)\right)
\end{aligned}
$$

用 $f_{i,j}$ 表示前 $j$ 关分为 $i$ 种难度的答案。那么，有：

$$
\begin{aligned}
f_{i,j}&=\min\left(f_{i-1,k}+\sum_{p=k+1}^{j}T_p\right) \\
&=\min\left(f_{i-1,k}+\left(\text{sumd}_j-\text{sumd}_k\right)-\left(\text{sumt}_k\times\left(\text{sumt}'_j-\text{sumt}'_k\right)\right)\right) \\
\end{aligned}
$$

其中 $1\le k<j$。

我们将其视为一个函数，套用斜率优化即可。

---

## 作者：Tyyyyyy (赞：0)

# CF643C

### 题目分析
容易想到定义 $dp_{i,j}$ 表示前 $i$ 个关卡分了 $j$ 级的最小期望时间。于是有转移方程：

$$dp_{i,j}=\min_{0\leq k<i}\{dp_{k,j-1}+cost(k+1,i)\}$$

其中，$cost(l,r)$ 表示把第 $l\sim r$ 个关卡分在一起的期望时间。考虑推出 $cost$ 的计算式。

因为通过一个关卡 $j$ 的期望时间是 $\displaystyle\frac{\sum_{i=l}^j t_i}{t_j}$（$1$ 小时通过的概率为 $P$，则期望时间为 $\frac{1}{P}$），所以可以得到

$$cost(l,r)=\sum_{j=l}^r\frac{\sum_{i=l}^j t_i}{t_j}$$

记 $t_i$ 的前缀和为 $sum_i$，$\frac{1}{t_i}$ 的前缀和为 $ts_i$，则

$$cost(l,r)=\sum_{j=l}^r\frac{sum_j-sum_{l-1}}{t_j}$$

这里面 $sum_{l-1}$ 是不变的，我们考虑把它提出来，并设 $\frac{sum_i}{t_i}$ 的前缀和为 $ss_i$。于是

$$cost(l,r)=ss_r-ss_{l-1}-sum_{l-1}(ts_r-ts_{l-1})$$

于是可以简化转移方程：

$$dp_{i,j}=\min_{0\leq k<i}\{dp_{k,j-1}+ss_i-ss_k-sum_k(ts_i-ts_k)\}$$

显然 $j$ 应当作为外层循环枚举，看作定值。考虑什么时候对于 $i$，从 $k$ 转移优于从 $k'$ 转移。

则有：

$$dp_{k,j-1}+ss_i-ss_k-sum_k(ts_i-ts_k)<dp_{k',j-1}+ss_i-ss_{k'}-sum_{k'}(ts_i-ts_{k'})$$

移项可以得到：

$$ts_i(sum_{k'}-sum_k)<dp_{k',j-1}-dp_{k,j-1}-ss_{k'}+ss_k+sum_{k'}ts_{k'}-sum_kts_k$$

即

$$ts_i<\frac{dp_{k',j-1}-dp_{k,j-1}-ss_{k'}+ss_k+sum_{k'}ts_{k'}-sum_kts_k}{sum_{k'}-sum_k}$$

所以，我们将每个决策点看作点 $P(sum_k,dp_{k,j-1}-ss_k+sum_kts_k)$，即可用斜率优化维护。

时间复杂度为 $O(nk)$。

Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;
int n,k,t[200010];
ll sum[200010];
ld dp[200010][60],ts[200010],ss[200010];
int q[200010],he,ta;
inline ll x(int p){return sum[p];}
inline ld y(int p,int i){return dp[p][i-1]+1.0*sum[p]*ts[p]-ss[p];}
inline ld slope(int p1,int p2,int i)
{
	if(x(p1)==x(p2))return y(p1,i)>y(p2,i)?1e18:-1e18;
	return (y(p1,i)-y(p2,i))/(x(p1)-x(p2));
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&t[i]),ts[i]=ts[i-1]+1.0/t[i],sum[i]=sum[i-1]+t[i],ss[i]=ss[i-1]+1.0*sum[i]/t[i];
	for(int i=1;i<=n;i++)dp[i][0]=1e18;
	for(int j=1;j<=k;j++)
	{
		q[he=ta=1]=0;
		for(int i=1;i<=n;i++)
		{
			while(he<ta&&slope(q[he+1],q[he],j)<=ts[i])he++;
			dp[i][j]=dp[q[he]][j-1]+ss[i]-ss[q[he]]-sum[q[he]]*(ts[i]-ts[q[he]]);
			while(he<ta&&slope(i,q[ta-1],j)<=slope(q[ta],q[ta-1],j))ta--;
			q[++ta]=i;
		}
	}
	printf("%.10Lf",dp[n][k]);
	return 0;
}
```


---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
有一种电子游戏，它由 $n$ 个关卡组成，每个关卡都被赋予了一个值 $t_i$。

现在，你要将这些关卡分成 $k$ 个级别，每个级别 $j$ 对应了一段**连续的**关卡 $[l_j,r_j]$，且必有 $l_j\leq r_j$。任何一个关卡在且仅在一个级别中。

然后，一名玩家将会从第 $1$ 个关卡，按顺序一直刷到第 $n$ 个关卡。当他打到第 $i$ 个关卡时，设这个关卡所在的级别是 $j$，则他有 $\dfrac{t_i}{\sum\limits_{x=l_j}^{i}t_x}$ 的概率在$1$小时内AC这个关卡，然后进入下一关；或者没有 AC 这个关卡（但仍然花了 $1$ 小时），还得再次挑战这个关卡。

你需要找到一种划分方法，使得该玩家期望 AK 该游戏的期望时间最小。输出这个最小的期望时间。
## $\text{Solution}$
一道乍看很吓人但是仔细想想并不难的小清新 dp 题。  
有一个期望相关的常用结论：**若一件事做成的概率是 $p$，那么做成这件事需要的期望次数是 $\dfrac{1}{p}$。**  
证明：设期望次数为 $x$，讨论第一次做成或者没做成，就有：
$$x=(p\times0+(1-p)\times x)+1$$
移项即可得。  

回到本题。  
显然不同段之间互相独立。  
设 $sum_i=\sum_{j=1}^i t_j$。  
那么本题 $(l,r)$ 区间划分成一段完成的期望次数就是：
$$\sum_{i=l}^r \frac{sum_i-sum_{l-1}}{t_i}$$
也就是：
$$\sum_{i=l}^r \frac{sum_i}{t_i}-sum_{l-1}\times\sum_{i=l}^r \frac{1}{t_i}$$
对 $\sum_{i=l}^r \dfrac{sum_i}{t_i}$ 和 $\sum_{i=l}^r \dfrac{1}{t_i}$ 分别求前缀和，我们就可以 $O(1)$ 转移了。  
然后~~直观感受~~可以发现，这个东西是满足**决策单调性**的。  
感性理解一下就是要使全局尽可能小，前面的 $\sum_{i=l}^r \dfrac{sum_i}{t_i}$ 全合起来后是定值，后面多一个元素的时候，$\sum_{i=l}^r \dfrac{1}{t_i}$ 变大，那么为了多减一些，$sum_{l-1}$ 的值应该相应的变大（或者至少不应该变小），所以转移点有单调性的。  
直接上分治即可，时间复杂度 $O(nk\log n)$。
（看题解的大佬这题也可以斜优做把 log 去掉）
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e5+100;
#define ll long long
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m;
double sum[N],t[N];
double s1[N],s2[N];
inline double calc(int l,int r){
  return (s1[r]-s1[l-1])-sum[l-1]*(s2[r]-s2[l-1]);
}
double dp[52][N];
void solve(int k,int l,int r,int tl,int tr){
  if(l>r) return;
  int mid=(l+r)>>1,pl(0);
  for(int i=tl;i<=min(mid-1,tr);i++){
    double w=dp[k-1][i]+calc(i+1,mid);
    if(w<dp[k][mid]){
      dp[k][mid]=w;pl=i;
    }
  }
  solve(k,l,mid-1,tl,pl);solve(k,mid+1,r,pl,tr);
  return;
}
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();
  for(int i=1;i<=n;i++){
    t[i]=read();
    sum[i]=sum[i-1]+t[i];
    s1[i]=s1[i-1]+sum[i]/t[i];
    s2[i]=s2[i-1]+1.0/t[i];
  }
  for(int i=0;i<=m;i++){
    for(int j=0;j<=n;j++) dp[i][j]=2e18;
  }
  dp[0][0]=0;
  for(int k=1;k<=m;k++) solve(k,1,n,0,n-1);
  printf("%lf\n",dp[m][n]);
  return 0;
}
/*

*/

```



---

## 作者：xtx1092515503 (赞：0)

我们考虑一下，假设$[l,r]$内的关卡被划在了一起，则通关第$r$关的期望时间是多少？

因为一次通过的概率是$\dfrac{t_r}{\sum\limits_{i=l}^{r}t_i}$，则我们期望需要$\dfrac{\sum\limits_{i=l}^{r}t_i}{t_r}$次才能通过。

我们再考虑，将区间$[l,r]$内的所有关卡划在一起，期望时间是多少？

则应为

$$\sum\limits_{i=l}^{r}\dfrac{\sum\limits_{j=l}^{i}t_j}{t_i}$$

我们设上面的式子为$w[l,r]$。

则我们可以考虑DP。

设$f_{i,j}$表示前$i$个位置分成$j$段的最小期望代价。

则我们有

$$f_{i,j}=\min\limits_{k=0}^{i-1}f_{k,j-1}+w[k+1,i]$$

为了方便表示，我们优先枚举$j$一维。换句话说，我们定义新的$g_i$表示旧的$f_{i,j}$，定义新的$f_i$表示旧的$f_{i,j-1}$。

则我们有

$$g_i=\min\limits_{j=0}^{i-1}f_j+w[j+1,i]$$

直接上$O(n^2)$DP，TLE12。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,t[200100],ll,rr,sum;
double inv,res,f[200100],g[200100];
double calc(int l,int r){
	while(ll>l){
		--ll;
		inv+=1.0/t[ll];
		sum+=t[ll];
		res+=inv*t[ll];
	}
	while(rr<r){
		++rr;
		inv+=1.0/t[rr];
		sum+=t[rr];
		res+=1.0*sum/t[rr];
	}
	while(ll<l){
		res-=inv*t[ll];
		sum-=t[ll];
		inv-=1.0/t[ll];
		ll++;
	}
	while(rr>r){
		res-=1.0*sum/t[rr];
		sum-=t[rr];
		inv-=1.0/t[rr];
		rr--; 
	}
	return res;
}
void func(){
	for(int i=1;i<=n;i++)g[i]=9e18;
	for(int i=1;i<=n;i++)for(int j=i-1;j;j--)g[i]=min(g[i],f[j]+calc(j+1,i));
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&t[i]),inv+=1.0/t[i],sum+=t[i],res+=1.0*sum/t[i],f[i]=res;
	ll=1,rr=n;
	while(--m)func(),memcpy(f,g,sizeof(g));
	printf("%lf\n",f[n]);
	return 0;
}
```
注意到这份代码中$w[l,r]$（即代码中的```calc```函数）的计算比较神奇，它采用了类似莫队的写法。因为$l$左移一格，$w[l,r]$增加$t_{l-1}*\sum\limits_{i=l-1}^{r}\dfrac{1}{t_i}$；$r$右移一格，$w[l,r]$增加$\dfrac{\sum\limits_{i=l}^{r+1}t_i}{t_{r+1}}$。因此只需要维护$inv=\sum\limits_{i=l}^{r}\dfrac{1}{t_i},sum=\sum\limits_{i=l}^{r}t_i$，就可以很轻松地实现莫队的查询。

我们考虑优化。

看一下[这道题](https://www.luogu.com.cn/problem/CF868F)。思想也是类似的，并且在该题中可以应用**四边形不等式**。我们不妨考虑一下，这道题能否使用四边形不等式呢？即

$$w[l-1,r+1]+w[l,r]\geq w[l,r+1]+w[l-1,r]$$

套用定义

$$\sum\limits_{i=l-1}^{r+1}\dfrac{\sum\limits_{j=l-1}^{i}t_j}{t_i}+\sum\limits_{i=l}^{r}\dfrac{\sum\limits_{j=l}^{i}t_j}{t_i}\geq \sum\limits_{i=l}^{r+1}\dfrac{\sum\limits_{j=l}^{i}t_j}{t_i}+\sum\limits_{i=l-1}^{r}\dfrac{\sum\limits_{j=l-1}^{i}t_j}{t_i}$$

整理一下

$$\sum\limits_{i=l-1}^{r+1}\dfrac{\sum\limits_{j=l-1}^{i}t_j}{t_i}-\sum\limits_{i=l-1}^{r}\dfrac{\sum\limits_{j=l-1}^{i}t_j}{t_i}\geq \sum\limits_{i=l}^{r+1}\dfrac{\sum\limits_{j=l}^{i}t_j}{t_i}-\sum\limits_{i=l}^{r}\dfrac{\sum\limits_{j=l}^{i}t_j}{t_i}$$

合并

$$\dfrac{\sum\limits_{j=l-1}^{r+1}t_j}{t_{r+1}}\geq \dfrac{\sum\limits_{j=l}^{r+1}t_j}{t_{r+1}}$$

最终得到

$$t_{l-1}\geq0$$

显然恒成立。

因此此DP符合四边形不等式，具有决策单调性。

对于这类问题，一般采取分治解法。即，设```func(l,r,L,R)```表示要确定$[l,r]$内的$g_i$，它们的决策点的备选集合是$[L,R]$。我们找出$[l,r]$的中点$mid$的最优决策点$mp$，然后继续递归地处理```func(l,mid-1,L,mp)```与```func(mid+1,r,mp,R)```。这时我们就能看出来之前莫队写法的优越之处了：它保证了每一层内莫队左右端点的总移动距离是$O(n)$的。因此总复杂度是$O(nk\log n)$的。第一发TLE，加上快读后AC。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,t[200100],ll,rr,sum;
double inv,res,f[200100],g[200100];
inline double calc(int l,int r){
	while(ll>l){
		--ll;
		inv+=1.0/t[ll];
		sum+=t[ll];
		res+=inv*t[ll];
	}
	while(rr<r){
		++rr;
		inv+=1.0/t[rr];
		sum+=t[rr];
		res+=1.0*sum/t[rr];
	}
	while(ll<l){
		res-=inv*t[ll];
		sum-=t[ll];
		inv-=1.0/t[ll];
		ll++;
	}
	while(rr>r){
		res-=1.0*sum/t[rr];
		sum-=t[rr];
		inv-=1.0/t[rr];
		rr--; 
	}
	return res;
}
inline void func(int l,int r,int L,int R){
	if(l>r||L>R)return;
	register int mid=(l+r)>>1;
	register int mp;
	register double mn=9e18;
	for(register int i=L;i<=R;i++)if(f[i]+calc(i+1,mid)<mn)mn=f[i]+calc(i+1,mid),mp=i;
	g[mid]=mn;
	func(l,mid-1,L,mp),func(mid+1,r,mp,R); 
}
inline void read(int &x){
	x=0;
	register char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
}
signed main(){
	read(n),read(m);
	for(register int i=1;i<=n;i++)read(t[i]),inv+=1.0/t[i],sum+=t[i],res+=1.0*sum/t[i],f[i]=res;
	ll=1,rr=n;
	while(--m)func(1,n,0,n-1),memcpy(f,g,sizeof(g));
	printf("%lf\n",f[n]);
	return 0;
}
```


---

