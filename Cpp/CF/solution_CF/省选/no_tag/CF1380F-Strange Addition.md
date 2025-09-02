# Strange Addition

## 题目描述

对于非负整数 $a,b$，定义它们的 "奇异加法 $\oplus$" 如下：   
   
1. 将 $a,b$ 一上一下写在两行，并按照低位对齐。   
2. 将它们的每一位加起来，并将**每一位的结果从高位到低位连接在一起**，得到的就是 $a\oplus b$。   
   
（你可以认为，两个数都有无穷多的前导 0）   
   
例如，$3248\oplus 908=311416$，因为：   
   
![3248+908=311416](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1380F/a527f267dad59d6e6b988913627229dffe969f7d.png)   
   
你现在有一个**仅包含 $n$ 个 $0\sim 9$ 的数码**的字符串 $c$，并且还有 $m$ 次操作。一次操作为：  
   
- ```x d``` - 将 $c$ 的第 $x$ 个数码替换成数码 $d$ 。   
   
（注意，$c$ 在任何时刻都可能存在前导 0）   
   
每次操作过后，你需要输出，有多少个**有序对** $(a,b)$，满足 $a,b$ 都是非负整数，且 $a\oplus b=c$。     
   
答案对 $998244353$ 取模。

## 样例 #1

### 输入

```
2 3
14
2 4
2 1
1 0```

### 输出

```
15
12
2```

# 题解

## 作者：Froggy (赞：5)

## 动态 dp

先考虑如果没有修改操作怎么 dp。

设 $dp_i$ 表示 $1\sim i$ 位的答案。

如果第 $i$ 可以进位那么需要保证 $a_{i-1}=1$。

那么转移就显然了：

$$dp_i=(a_i+1)dp_{i-1}+[a_{i-1}=1](9-a_i)dp_{i-2}$$

每次修改都 $\mathcal{O}(n)$ dp 一遍显然会爆炸，考虑把转移写成矩阵形式：

$$
\begin{bmatrix}
dp_i \\
dp_{i-1}
\end{bmatrix}
=
\begin{bmatrix}
a_i+1 & [a_{i-1}=1](9-a_i)\\
1 & 0 
\end{bmatrix}

\times

\begin{bmatrix}
dp_{i-1} \\
dp_{i-2}
\end{bmatrix}
$$

边界：把 $dp_0$ 和 $dp_{-1}$ 设成 $1$。

用线段树维护即可。

注意：当修改 $a_x$ 的时候需要把 $x$ 和 $x+1$ 位置的矩阵都更新了。

时间复杂度：$\mathcal{O}(2^3m\log n)$。

---

***code:***

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int mod=998244353;
#define N 500050
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
int n,Q,a[N];
char s[N];
struct Matrix{    //矩阵板子
	int g[3][3];
	Matrix(){memset(g,0,sizeof(g));}
	inline Matrix operator *(const Matrix a){
		Matrix b;
		for(int i=1;i<=2;++i){
			for(int j=1;j<=2;++j){
				for(int k=1;k<=2;++k){
					b.g[i][j]=(b.g[i][j]+1LL*g[i][k]*a.g[k][j])%mod;
				}
			}
		}
		return b;
	}
}e,ed;
struct node{
	int l,r;
	Matrix p;
}tree[N<<2];
#define ls i<<1
#define rs i<<1|1
inline void update(int i){
	tree[i].p=tree[rs].p*tree[ls].p;
}
void build(int i,int l,int r){      //初始建树
	tree[i].l=l;
	tree[i].r=r;
	if(l==r){
		tree[i].p.g[2][1]=1;
		tree[i].p.g[1][1]=a[l]+1;
		tree[i].p.g[1][2]=(a[l-1]==1)*(9-a[l]);
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	update(i);
}
void Change(int i,int pos){           //更新矩阵
	if(tree[i].l==tree[i].r){
		tree[i].p.g[1][1]=a[pos]+1;
		tree[i].p.g[1][2]=(a[pos-1]==1)*(9-a[pos]);
		return;
	}
	int mid=(tree[i].l+tree[i].r)>>1;
	if(pos<=mid)Change(ls,pos);
	else Change(rs,pos);
	update(i);
}
int main(){
	n=read(),Q=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;++i){
		a[i]=s[i]-'0';
	}
	e.g[1][1]=e.g[2][2]=1;
	ed.g[1][1]=ed.g[2][1]=1; 
	build(1,1,n);
	while(Q--){
		int pos=read(),x=read();
		a[pos]=x;
		Change(1,pos);
		if(pos<n)Change(1,pos+1);
		printf("%d\n",(tree[1].p*ed).g[1][1]); //最后别忘了再乘上初矩阵
	}
	return 0;
}
```

[*Froggy's blog*](https://www.luogu.org/blog/1445353309froggy/)

#### 呱!!

---

## 作者：xukehg (赞：1)

板子题，基本把动态 dp 写到题面上了。

先忽略修改操作，定义 $dp_{i}$ 表示前 $i$ 位有多少种分解方式，设 $x = a_{i - 1} * 10 + a_{i}$，$cnt1_i$ 表示对于 $0 \leq i \leq 9$ 的分解方案数，$cnt2_i$ 表示对于 $10 \leq i \leq 18$ 的分解方案数，有以下两种情况。

- 如果 $10 > x$ 或者 $x > 18$，不存在特殊的分解，只能从上一位转移，即 $dp_{i} = dp_{i - 1} \times cnt_{a_{i}}$。
- 如果 $10 \leq x \leq 18$，除上述转移外，可以从前两位转移，类似 $12 = 3 + 9$。故有 $dp_{i} = dp_{i - 1} \times cnt1_{a_{i}} + dp_{i - 2} \times cnt2_{x}$。

综上，我们有了 $O(nq)$ 的方法。

考虑用矩阵描述转移，显然有

$$\begin{bmatrix}
dp_{i - 2} \space dp_{i - 1}
\end{bmatrix} \times \begin{bmatrix}
0 \space cnt2_{x}
\\1 \space cnt1_{a_{i}}
\end{bmatrix} = \begin{bmatrix}
dp_{i - 1} \space dp_{i}
\end{bmatrix}$$。用线段树维护即可。

[记录。](https://codeforces.com/contest/1380/submission/293810636)

---

## 作者：Rem_CandleFire (赞：1)

题意比较好理解，我们设 $f_i$ 为从高往低（这样方便操作）前 $i$ 位的方案数。假设要求的目标 $c$ 第 $i$ 位为 $a_i$，根据数学中整数加法的相关基础知识，易得：

$$f_i=(a_i+1)f_{i-1}+[a_{i-1}=1](9-a_i)f_{i-2}$$

加号前后两段分别表示进位与不进位的情况。观察到这一个线性 DP 的第 $i$ 项只与前两项相关，看到这种情况我们会联想到矩阵。所以将转移式改写成：
$$
\begin{bmatrix}
   f_i  \\
   f_{i-1} 
\end{bmatrix}

=
\begin{bmatrix}
   a_i+1 & [a_{i-1}=1](9-a_i) \\
   1 & 0
\end{bmatrix}
\times
\begin{bmatrix}
   f_{i+1} \\
   f_i
\end{bmatrix}
$$
那么我们想要求出最终的 $f_n$ 值，循环乘过去就好了。至此我们就了解了当没有修改操作时的做法。

如果我们需要修改使 $a_i=d$，观察上面的式子，只需要修改第 $i$ 个和第 $i+1$ 个矩阵就好了。所以整个问题最后需要维护一个线段树，支持单点修改和区间乘积。最后输出答案时要记得乘上初始的临界情况 $f_0=f_1=1$，即 $\begin{bmatrix}f_1\\ f_0 \end{bmatrix}=\begin{bmatrix} 1\\1 \end{bmatrix}$。

需要注意的是，**矩阵乘法不满足交换律，所以线段树上推时要注意左乘和右乘**。

[AC code](https://www.luogu.com.cn/paste/5dundbzl)

---

## 作者：FutaRimeWoawaSete (赞：0)

考虑两个个位数相加其值在 $[0,18]$ 之间。

设 $dp_{i,0/1}$ 表示前 $i$ 个数末尾一位为 $1$ / 不是 $1$ 的配对方案。     

那么显然可以得出如下方程：            

$dp_{i,0} = [(dp_{i - 1,0} + dp_{i - 1,1}) \times (s_i + 1) + (dp_{i - 2,0} + dp_{i - 2 , 1}) \times (9 - s_i) \times [s_{i - 1} = 1]] \times [s_i \neq 1]$

$dp_{i,1} = [(dp_{i - 1,0} + dp_{i - 1,1}) \times (s_i + 1) + (dp_{i - 2,0} + dp_{i - 2 , 1}) \times (9 - s_i) \times [s_{i - 1} = 1]] \times [s_i = 1]$

当然再观察一下发现其实可以只用一维表示的，但是太懒了就懒得化简了。

发现是一个常系数齐次递推，把对应的把系数打进矩阵里面后做单点修改的线段树维护矩乘就好了。    

注意一下每次改的时候若修改的是位置 $x$ 则 位置 $x + 1$ 的矩阵也要重置。          

时间复杂度 $O(4 ^ 3 n \log n)$，直接比别人多了个 $8$ 倍常数。
```cpp
/*
因为这个题得矩乘，所以答案只能从dp_{i - 1}转移2344
定义dp_{i,j}表示前i个数合并出来末尾为j的方案数
然而这个肯定会被卡掉的
发现只有前一位为1时存在进位，那么就射dp_{i,0/1}表示前i个数合并出来末尾是不是0/1就行了
然后大概得用一个4 * 4的矩阵转移：
首先看是1还是其他，然后把对应的系数扔就好了dp_{i,0/1} = dp_{i - 1,0} * (s[i] + 1) + dp_{i - 1,1} * (s[i] + 1) + [s_{i - 1} = 1] * (dp_{i - 2,1} * (9 - s_i) + dp_{i-2,0} * (9 - s_i))
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 5e5 + 5 , MOD = 998244353;
int n,q,vis[Len << 2];
struct node
{
	int a[5][5];
	node(){memset(a , 0 , sizeof a);}
	inline void clear(){for(int i = 1 ; i <= 4 ; i ++) for(int j = 1 ; j <= 4 ; j ++) a[i][j] = 0;}
	inline void build(){for(int i = 1 ; i <= 4 ; i ++) a[i][i] = 1;}
	node operator * (const node &y)
	{
		node z;z.clear();
		for(int i = 1 ; i <= 4 ; i ++)
			for(int k = 1 ; k <= 4 ; k ++)
			{
				if(!a[i][k]) continue; 
				for(int j = 1 ; j <= 4 ; j ++)
					z.a[i][j] = (z.a[i][j] + 1ll * a[i][k] * y.a[k][j] % MOD) % MOD;
			}
		return z; 
	}
}tree[Len << 2],Int,Ans,ADD;
char s[Len];
#define ls(p) p << 1
#define rs(p) p << 1 | 1
void push_up(int x){tree[x] = tree[ls(x)] * tree[rs(x)];vis[x] = vis[ls(x)] | vis[rs(x)];}
void build(int p,int l,int r)
{
	if(l == r) 
	{
		tree[p].clear();
		tree[p].a[1][3] = 1 , tree[p].a[2][4] = 1;
		int x = s[l] - '0';
		if(s[l] == '1') 
		{
			tree[p].a[1][2] = x + 1;
			tree[p].a[2][2] = x + 1;
			if(s[l - 1] == '1')
			{
				tree[p].a[4][2] = 9 - x;
				tree[p].a[3][2] = 9 - x;
			}
		}
		else
		{
			tree[p].a[1][1] = x + 1;
			tree[p].a[2][1] = x + 1;
			if(s[l - 1] == '1')
			{
				tree[p].a[4][1] = 9 - x;
				tree[p].a[3][1] = 9 - x;
			}
		}
		if(s[l] == '0') vis[p] = 0;
		else vis[p] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
	push_up(p);
}
void update(int p,int l,int r,int idx)
{
	if(l == r)
	{
		tree[p].clear();
		tree[p].a[1][3] = 1 , tree[p].a[2][4] = 1;
		int x = s[l] - '0';
		if(s[l] == '1') 
		{
			tree[p].a[1][2] = x + 1;
			tree[p].a[2][2] = x + 1;
			if(s[l - 1] == '1')
			{
				tree[p].a[4][2] = 9 - x;
				tree[p].a[3][2] = 9 - x;	
			}
		}
		else
		{
			tree[p].a[1][1] = x + 1;
			tree[p].a[2][1] = x + 1;
			if(s[l - 1] == '1')
			{
				tree[p].a[4][1] = 9 - x;
				tree[p].a[3][1] = 9 - x;
			}
		}
		if(s[l] == '0') vis[p] = 0;
		else vis[p] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	if(idx <= mid) update(ls(p) , l , mid , idx);
	else update(rs(p) , mid + 1 , r , idx);
	push_up(p);
}
int findidx(int p,int l,int r)
{
	if(l == r) 
	{
		if(!vis[p]) return -1;
		return l;
	}
	int mid = (l + r) >> 1;
	if(vis[ls(p)]) return findidx(ls(p) , l , mid);
	else return findidx(rs(p) , mid + 1 , r);
}
void query(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r){ADD = ADD * tree[p];return;}
	int mid = (l + r) >> 1;
	if(nl <= mid) query(ls(p) , l , mid , nl , nr);
	if(nr > mid) query(rs(p) , mid + 1 , r , nl , nr);
}
char ss[5];
int main()
{
	Int.clear();
	scanf("%d %d",&n,&q);
	scanf("%s",s + 1);
	s[0] = '?';
	build(1 , 1 , n);
	for(int j = 1 ; j <= q ; j ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		s[x] = y + '0';
		update(1 , 1 , n , x);
		if(x + 1 <= n) update(1 , 1 , n , x + 1);
		ADD.clear();ADD.build();
		int idx = findidx(1 , 1 , n);
		if(idx == -1) 
		{
			puts("1");
			continue;
		} 
		query(1 , 1 , n , idx , n);
		Int.clear();
		Int.a[1][1] = 1;
		Ans = Int * ADD;
		if(s[n] == '1') printf("%d\n",Ans.a[1][2]);
		else printf("%d\n",Ans.a[1][1]);
	}
	return 0;
}
```


---

## 作者：1saunoya (赞：0)

动态dp？
~~理解成数据结构维护矩阵就行了~~

考虑一个朴素的 $dp$ 转移方程。

设 $dp_i$ 为到当前 $i$ 位的方案数。

则 $dp_i$ 是可以从 $dp_{i-1}$ 和 $dp_{i-2}$ 转移得到的。

考虑进位问题，如果进位了，那么一定是 1。

~~以下问题自动省略~~

得到 $dp_i = (a_i + 1)dp_{i-1} + [a_{i-1}=1] (9 - a_i)\times dp_{i-2}$

$$ \left[\begin{matrix}dp_i \\ dp_{i-1}\end{matrix}\right] =\left[ \begin{matrix}a_i + 1 & [a_{i-1}=1]\times(9-a_i) \\ 1 & 0 \end{matrix} \right] \times \left[\begin{matrix}dp_{i-1} \\ dp_{i-2}\end{matrix}\right]$$

特殊的，令 $dp_0 = dp_{-1} = 1$

代码跑得慢，不放了。

---

