# 「CGOI-2」No voice to cry suffering

## 题目背景

父亲，您的王国在崩塌；

父亲，您的人民在离去；

父亲，但您说我不该有为苦难哭泣的声音；

所以我将无能为力，所以我独自分崩离析。

## 题目描述

容器面前有 $n$ 个感染者，这 $n$ 个感染者排成一列，编号依次从 $1$ 到 $n$，第 $i$ 个感染者的感染深度为 $a_i$。

容器会从第 $x$ 个感染者处开始向第 $n$ 个感染者走，依次经过第 $x$ 到 $n$ 个感染者。容器会击杀所有经过的感染者。然而，如果击杀了两个**编号连续，感染深度严格递增**的感染者，那么它会略过下一个感染者（如果存在下一个）。

记 $f_x$ 表示若容器从第 $x$ 个位置开始，击杀的感染者数量（$f$ 之间两两独立）。例如有五个感染者，他们的感染深度依次为：

```plain
2 6 4 5 1
```

那么对应的 $f$ 序列为 $\{4,3,2,2,1\}$。

你不知道每个感染者的感染深度，只知道 $m$ 组 $f_i-f_{i+1}$ 的值，对于请输出满足条件的不同 $f$ 序列的数量对 $998244353$ 取模的结果。

序列 $f,g$ 不同，当且仅当存在 $1\le i \le n$ 满足 $f_i\not= g_i$。

## 说明/提示

### 样例一解释

初始：符合条件的 $f$ 序列有 $\{3,2,1\},\{2,2,1\}$。

约束一：初始的 $f$ 序列都不符合约束一，忽略该条件。

约束二：只有 $\{3,2,1\}$ 符合约束条件。

约束三：只有 $\{2,2,1\}$ 符合约束条件。结合约束二，不存在合法的 $f$ 序列，忽略该条件。

---

### 数据范围及约定

对于 $20\%$ 的数据，$n,m\le5$。

对于 $60\%$ 的数据，$n\le10^6$。

对于另外 $10\%$ 的数据，$m=0$。

对于 $100\%$ 的数据，$1 \leq n \leq 10^{11},0 \leq m \leq 5\times 10^4,0 \leq |y| \leq n,1 \leq x <n$。

## 样例 #1

### 输入

```
3 3
1 5
1 1
1 0```

### 输出

```
2
2
1
1```

## 样例 #2

### 输入

```
5 2
2 1
4 5```

### 输出

```
4
3
3```

# 题解

## 作者：lzqy_ (赞：5)

爆踩一下去年的自己。

首先还是考虑 $f$ 的转移，即：

$$ f_i=\left\{
\begin{aligned}
f_{i+1}+1\;(a_i\leq a_{i+1})
 \\
f_{i+3}+2\;(a_i>a_{i+1})
\end{aligned}
\right.
$$


也就是说，$f_i$ 的值是 $(f_{i+1}+1)$ 和 $(f_{i+3}+2)$ 中的任意一个（因为 $a$ 可以随便取），而取值个数和 $f_{i+1}+1=f_{i+3}+2$ 是否成立有关，也就是只和 $f_{i+1},f_{i+3}$ 的差有关。

所以考虑转移时维护 $f_{i+1}-f_{i+2},f_{i+2}-f_{i+3}$ 两个值，由 $f_{n+1}=0,f_{n}=1,f_{n-1}=2$ 出发，可以发现，这两个差值的组合一共只有三种，即 $\{1,1\},\{0,1\},\{1,0\}$，所以维护一个 $3\times 3$ 的转移矩阵即可。修改操作用线段树维护。

至于判断二元组是否合法，只需要修改后判断是否有解即可，若无解再撤销。**注意本身有解而取模后答案为 $0$ 的情况**。

代码没什么不同的，只是给出一种更正常的思维方式。

---

## 作者：lzqy_ (赞：3)

这里是出题人的题解。

------

考虑 $f$ 数组如何转移。按照题意分为两种情况，容易得到转移方程：

$$ f_i=\left\{
\begin{aligned}
f_{i+1}+1\;(a_i\leq a_{i+1})
 \\
f_{i+3}+2\;(a_i>a_{i+1})
\end{aligned}
\right.
$$

由于题目给出的是相邻值的差，所以再设 $g_i=f_i-f_{i+1}$。又因为每一个 $g$ 唯一对应一个 $f$，所以题目可以转换为： 

- 给出 $g$ 数组的若干个值，求有多少种可能的 $g$ 数组。


$g$ 比较抽象，考虑从 $f$ 入手，寻找性质。可以证明，$f$ 可构造的充要条件是：

- $f_{i+1}\leq f_i$ 且 $f_i-f_{i+1}\leq1\quad$①。

- $f_{i+2}<f_i\quad$②。

- 若 $f_i-f_{i+1}=0$，则 $f_{i+1}-f_{i+2}=f_{i+2}-f_{i+3}=1\quad$③。

证明：

------------

对于 $f_{n-2},f_{n-1},f_n$，有 $f_n=1$
，$f_{n-1}=2$，$f_{n-2}=2$ 或 $3$，满足①②性质。

若存在 $f_i,f_{i+1},f_{i+2}$ 满足①②性质，判断 $f_{i-1},f_i,f_{i+1}$ 是否满足①②性质：

- $f_i=f_{i+1}+1=f_{i+2}+2$
  - $a_{i-1}\leq a_i$：$f_{i-1}=f_i+1=f_{i+1}+2$，仍满足以上性质。
  - $a_{i-1}>a_i$：$f_{i-1}=f_i=f_{i+1}+1$，仍满足以上性质。

- $f_i=f_{i+1}+1=f_{i+2}+1$ 

  - $a_{i-1}\leq a_i$：$f_{i-1}=f_i+1=f_{i+1}+2$，仍满足以上性质。
  - $a_{i-1}>a_i$：$f_{i-1}=f_i+1=f_{i+1}+2$，仍满足以上性质。

- $f_i=f_{i+1}=f_{i+2}+1$

  - $a_{i-1}\leq a_i$：$f_{i-1}=f_i+1=f_{i+1}+1$，仍满足以上性质。
  - $a_{i-1}>a_i$：$f_{i-1}=f_i+1=f_{i+1}+1$，仍满足以上性质。

可以发现，若 $f_i,f_{i+1},f_{i+2}$ 满足①②，则 $f_{i-1},f_i,f_{i+1}$ 也满足①②。

又因为 $f_{n+1}=0,f_n=1,f_{n-1}=2$ 满足①②，因此整个 $f$ 数组都满足①②。

**因此①②是 $f$ 数组可构造的必要条件。**

-----

同时，根据上述分类讨论可得，当 $f_{i-1}-f_i=0$ 时，有 $f_i-f_{i+1}=f_{i+1}-f_{i+2}=1$，即满足③。

**因此①②③是 $f$ 数组可构造的必要条件。**

--------

设①②③成立，用以下方式构造序列 $a$：

$$ a_i=\left\{
\begin{aligned}
a_{i+1}-1\;(f_i-f_{i+1}=1)
 \\
a_{i+1}+1\;(f_i-f_{i+1}=0)
\end{aligned}
\right.
$$

不难证明，此时 $a$ 序列一定能推出原本的 $f$ 数组。

**因此①②③是 $f$ 数组可构造的充要条件，证毕。**

根据 $f$ 数组的性质，可得 $g$ 数组可构造的充要条件为：

- $g_n=g_{n-1}=1$。

- $g_i ∈ \{ 0,1 \}$。

- 若 $g_i=0$，则 $g_{i-1}=g_{i+1}=g_{i+2}=g_{i-2}=1$。

接下来正式考虑做法。

因为 $n$ 很大，$m$ 很小，所以考虑将 $g$ 数组分割成 $m$ 个没有约束条件的区间求解。

设 $F_{i,0/1/2}$ 表示长度为 $i$ 且满足 $g_i=0/1,g_{i+1}=0/1$ 的 $g$ 序列的个数（因为 $g_{i}=g_{i+1}=0$ 不成立，所以只有三种情况）。可得转移方程：

$$ \left\{
\begin{aligned}
&F_{i,0}=F_{i+1,0}+F_{i+1,1}&(0:g_i=1,g_{i+1}=1)
 \\
&F_{i,1}=F_{i+1,2}&(1:g_{i}=1,g_{i+1}=0)
\\
&F_{i,2}=F_{i+1,0}&(2:g_{i}=0,g_{i+1}=1)
\end{aligned}
\right.
$$

其中，初始条件为：



$$F_{n-1,0}=1,F_{n-1,1}=0,F_{n-1,2}=0$$



该转移方程可通过构造矩阵 $
\begin{bmatrix}
1 & 0 & 1\\
1 & 0 & 0\\
0 & 1 & 0\\
\end {bmatrix}
$ 来进行快速转移。

考虑约束条件：

- $g_i=1$：即规定 $F_{i,2}=0$，等价于乘上矩阵  $
  \begin{bmatrix}
  1 & 0 & 0\\
  0 & 1 & 0\\
  0 & 0 & 0\\
  \end {bmatrix}
  $。

- $g_i=0$：即规定 $F_{i,0}=F_{i,1}=0$，等价于乘上矩阵  $
  \begin{bmatrix}
  0 & 0 & 0\\
  0 & 0 & 0\\
  0 & 0 & 1\\
  \end {bmatrix}
  $。

用动态开点线段树维护矩阵乘即可。每次询问的答案即为树根的矩阵乘初始值。时间复杂度 $O(27m\log n)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=998244353;
const int maxn=100010;
const int NN=maxn*50;
inline ll read(){
	ll x=0,f=1;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar())
		if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x*f;
}
void update(int &x,int y){if((x+=y)>=mod)x-=mod;}
struct Matrix{
	int n,m;
	int a[3][3];
}N,G1,G2,F,data[NN];
map<ll,int>G;
int lson[NN],rson[NN];
ll n;
int m,cnt=1;
Matrix operator *(Matrix a,Matrix b){
	Matrix c;
	c.n=a.n,c.m=b.m;
	memset(c.a,0,sizeof(c.a));
	for(int i=0;i<c.n;i++)
		for(int j=0;j<c.m;j++)
			for(int k=0;k<b.n;k++)
				update(c.a[i][j],(a.a[i][k]*1ll*b.a[k][j])%mod);
	return c;
}
void init(Matrix &a){
	a.n=a.m=3;
	memset(a.a,0,sizeof(a.a));
	for(int i=0;i<3;i++)
		a.a[i][i]=1;
}
Matrix fastpow(Matrix n,ll m){
	Matrix a=n,S;
	init(S);
	while(m){
		if(m&1) S=S*a;
		a=a*a,m>>=1;
	}
	return S;
}	
void Mudify1(int &i,ll l,ll r,ll x){
	if(!i) i=++cnt,data[i]=fastpow(N,r-l+1);
	if(l>x||r<x) return ;
	if(l==x&&r==x){
		data[i]=data[i]*G1;
		return ;
	}
	ll mid=l+r>>1;
	Mudify1(lson[i],l,mid,x);
	Mudify1(rson[i],mid+1,r,x);
	data[i]=data[lson[i]]*data[rson[i]];
}
void Mudify2(int &i,ll l,ll r,ll x){
	if(!i) i=++cnt,data[i]=fastpow(N,r-l+1);
	if(l>x||r<x) return ;
	if(l==x&&r==x){
		data[i]=data[i]*G2;
		return ;
	}
	ll mid=l+r>>1;
	Mudify2(lson[i],l,mid,x);
	Mudify2(rson[i],mid+1,r,x);
	data[i]=data[lson[i]]*data[rson[i]];
}
int main(){
	n=read(),m=read();
	ll x;
	int rt=1,y;
	G[n]=G[n-1]=2;
	N.n=N.m=3,N.a[0][0]=N.a[0][2]=N.a[1][0]=N.a[2][1]=1;
	F.n=1,F.m=3,F.a[0][1]=F.a[0][2]=0,F.a[0][0]=1;
	G1.n=G1.m=3,G1.a[0][0]=G1.a[1][1]=1;
	G2.n=G2.m=3,G2.a[2][2]=1;
	data[1]=fastpow(N,n-2);
	Matrix Ans;
	Ans=F*data[1],printf("%lld\n",(Ans.a[0][0]+0ll+Ans.a[0][1]+Ans.a[0][2])%mod);
	for(int i=1;i<=m;i++){
		x=read(),y=read();
		if((y!=1&&y!=0)||G[x]);
		else if(!y&&(G[x-2]==1||G[x-1]==1||G[x+1]==1||G[x+2]==1));
		else{
			G[x]=y+1;
			if(y==1) Mudify1(rt,1,n-2,x);
			else Mudify2(rt,1,n-2,x);
		}
		Ans=F*data[1],printf("%lld\n",(Ans.a[0][0]+0ll+Ans.a[0][1]+Ans.a[0][2])%mod);
	}
	
	return 0;
} 
```

---

