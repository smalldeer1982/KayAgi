# New Year and Old Subsequence

## 题目描述

定义一个数字串满足性质$nice$当且仅当：该串包含子序列$2017$，且不包含子序列$2016$。

定义一个数字串的函数$ugliness$为：该串至少删去几个字符，可以使得剩余串满足性质$nice$；如果该串没有满足性质$nice$的子序列，则该串的$ugliness$是$-1$。

给定一个长度为$n$的字符串$t$，和$q$次询问，每次询问用$(l,r)$表示。对于每次询问，回答$ugliness(t[l,r])$。

## 说明/提示

$$ 4 \leq n \leq 200000,1 \leq q \leq 200000,1 \leq l \leq r \leq n $$

## 样例 #1

### 输入

```
8 3
20166766
1 8
1 7
2 8
```

### 输出

```
4
3
-1
```

## 样例 #2

### 输入

```
15 5
012016662091670
3 4
1 14
4 15
1 13
10 15
```

### 输出

```
-1
2
1
-1
-1
```

## 样例 #3

### 输入

```
4 2
1234
2 4
1 2
```

### 输出

```
-1
-1
```

# 题解

## 作者：Alex_Wei (赞：21)

> [CF750E New Year and Old Subsequence 题面传送门](https://www.luogu.com.cn/problem/CF750E)

> 题意简述：多次询问一个字符串的一个子串至少删去多少个字符后才能使得其不包含子序列 $2016$ 而包含 $2017$。

[DP 学习笔记例题 II —— cnblogs](https://www.cnblogs.com/alex-wei/p/14482723.html)。

---

直接大力 DP 就好了：设 $f_{i,0/1/2/3/4}$ 分别表示包含 $\varnothing/2/20/201/2017$ 在 $[1,i]$ 中最少需要删去多少个字符，那么有

$$\begin{cases}f_{i,0}=f_{i-1,0}+[s_i=2]\\f_{i,1}=\min(f_{i-1,1}+[s_i=0],f_{i-1,0}[s_i=2])\\f_{i,2}=\min(f_{i-1,2}+[s_i=1],f_{i-1,1}[s_i=0])\\f_{i,3}=\min(f_{i-1,3}+[s_i=7\lor s_i=6],f_{i-1,2}[s_i=1])\\f_{i,4}=\min(f_{i-1,4}+[s_i=6],f_{i-1,3}[s_i=7])\end{cases}$$

需要注意的是如果 $[]$ 中的条件不成立是不能转移的（而不是视为 $0$），应视为 $\infty$。因为转移只与前一项有关，故将上式改写成矩阵乘法形式即可。每次询问直接用 $\begin{bmatrix}0&\infty&\infty&\infty&\infty\end{bmatrix}$ 去乘 $[l,r]$ 的区间矩阵积（用线段树维护即可），得到的 $f_{r,4}$ 即为所求（如果 $f_{r,4}=\infty$ 则无解）。**注意这里的矩阵乘法应定义为 $C_{i,j}=\min(A_{i,k}+B_{k,j})$。**

事实上，**$\prod_{i=l}^r G_i$ 的第一行就是 $f_r$**（$G_i$ 是 $f_{i-1}\to f_i$ 的转移矩阵），所以直接求出矩阵区间矩阵积即可，不过用上面的方法可以 $f\times G$ **枚举第一行**，矩阵乘法就是平方的；而 $G\times G$ 是必须三方，**常数会更大。**

~~然而 cin 换成 scanf，endl 换成 "\n" 后跑得快了两倍。~~

```cpp
/*
	Powered by C++11.
	Author : Alex_Wei.
*/

#include <bits/stdc++.h>
using namespace std;

#define mem(x,v) memset(x,v,sizeof(x))

const int S=5;
const int N=2e5+5;
const int inf=0x3f3f3f3f;

struct matrix{
	int a[S][S];
	void print(){
		puts("------------ print matrix --------------");
		for(int i=0;i<S;i++,cout<<endl)
			for(int j=0;j<S;j++)
				cout<<setw(4)<<(a[i][j]<N?a[i][j]:-1);
	}
	matrix friend operator * (matrix x,matrix y){
		matrix z; mem(z.a,0x3f);
		for(int i=0;i<S;i++)
			for(int j=0;j<S;j++)
				for(int k=0;k<S;k++)
					z.a[i][j]=min(z.a[i][j],x.a[i][k]+y.a[k][j]);
		return z;
	}
	matrix friend operator / (matrix x,matrix y){
		matrix z; mem(z.a,0x3f);
		for(int i=0;i<S;i++)
			for(int j=0;j<S;j++)
				z.a[0][i]=min(z.a[0][i],x.a[0][j]+y.a[j][i]);
		return z;
	}
}val[N<<2],G[N],ans,pri;

void build(int l,int r,int x){
	if(l==r)return val[x]=G[l],void();
	int m=l+r>>1;
	build(l,m,x<<1),build(m+1,r,x<<1|1);
	val[x]=val[x<<1]*val[x<<1|1]; 
} void query(int l,int r,int ql,int qr,int x){
	if(ql<=l&&r<=qr)return ans=ans/val[x],void();
	int m=l+r>>1;
	if(ql<=m)query(l,m,ql,qr,x<<1);
	if(m<qr)query(m+1,r,ql,qr,x<<1|1);
}

int n,q;
char s;
int main(){
	cin>>n>>q;
	mem(pri.a,0x3f),pri.a[0][0]=0;
	for(int i=1;i<=n;i++){
		cin>>s,mem(G[i].a,0x3f);
		for(int j=0;j<S;j++)G[i].a[j][j]=0;
		if(s=='2')G[i].a[0][0]=1,G[i].a[0][1]=0;
		if(s=='0')G[i].a[1][1]=1,G[i].a[1][2]=0;
		if(s=='1')G[i].a[2][2]=1,G[i].a[2][3]=0;
		if(s=='7')G[i].a[3][3]=1,G[i].a[3][4]=0;
		if(s=='6')G[i].a[3][3]=1,G[i].a[4][4]=1;
	} build(1,n,1);
	for(int i=1;i<=q;i++){
		int l,r; cin>>l>>r;
		ans=pri,query(1,n,l,r,1);
		cout<<(ans.a[0][4]<=n?ans.a[0][4]:-1)<<endl;
	}
	return 0;
}
```

---

## 作者：D2T1 (赞：11)

# CF750E 题解（ddp）

------------

先想一个简单的问题：题目只询问一次，询问的 $(l,r)$ 为 $(1,n)$。

使用 dp 来解决。

状态：$f_{i,j}$ 表示前 $i$ 个数字与 $2017$ 的前 $j$ 位匹配（**且不与第 $j+1$ 位匹配**，不与 $2016$ 匹配）所需要删除的元素个数的最小值。此处的“匹配”指后者为前者的子序列。

为什么要这么复杂呢？简单一点不行吗？就设一维会怎么样？

假设状态定义只有 $f_i$，现在递推到第 $k$ 位，发现是 $6$。现在怎么办？你不知道这个 $6$ 之前有没有 $201$，要不要删，产生了后效性（前面是否有 $201$ 不在状态中），dp 解决不了。

这时升维就是最好的解决方法。若 $f_{j,3}$ 有答案则前面必定有 $201$。

转移：首先考虑 $f_{i,0}$。

什么情况下前 $i$ 个数字不与 $2$ 匹配呢？就是没有 $2$ 的情况。所以很简单：

$$f_{i,0} = \begin{cases} f_{i-1,0}+1~(s_i=2) \\ f_{i-1,0}~(s_i≠2) \end{cases}$$

接着 $f_{i,1}$。

$$f_{i-1}=\begin{cases} f_{i-1,0}~(s_i=2) \\ \inf~(s_i≠2) \end{cases}$$

这条很容易理解，如果出现了 $2$ 就直接从 $f_{i-1,0}$ 转移过来，什么都不用加。如果 $2$ 根本就没有出现过。那就设为无穷大，表示没有答案（为什么取无穷大呢，因为答案求最小值，取无穷大可以避免特判）。

$$f_{i,1} = \begin{cases} f_{i-1,1}+1~(s_i=0) \\ f_{i-1,1}~(s_i≠0) \end{cases}$$


这又是什么呢？如果 $s_i=0$ 且前面出现了 $2$，还满足定义吗？看看之前的定义。

> $f_{i,j}$ 表示前 $i$ 个数字与 $2017$ 的前 $j$ 位匹配（**且不与第 $j+1$ 位匹配**，不与 $2016$ 匹配）

所以要删掉一个才满足定义。

于是两条合起来，取最小值：

$$f_{i,1} = \min(\begin{cases} f_{i-1,1}+1~(s_i=0) \\ f_{i-1,1}~(s_i≠0) \end{cases},\begin{cases} f_{i-1,0}~(s_i=2) \\ \inf~(s_i≠2) \end{cases})$$

接下来以此类推，注意 $f_{i,3/4}$ 的转移的时候排除掉 $s_i=6$ 的情况。

总的方程如下：

$
\begin{cases}
f_{i,0} = \begin{cases} f_{i-1,0}+1~(s_i=2) \\ f_{i-1,0}~(s_i≠2) \end{cases}
\\
f_{i,1} = \min(\begin{cases} f_{i-1,1}+1~(s_i=0) \\ f_{i-1,1}~(s_i≠0) \end{cases},\begin{cases} f_{i-1,0}~(s_i=2) \\ \inf~(s_i≠2) \end{cases})
\\
f_{i,2} = \min(\begin{cases} f_{i-1,2}+1~(s_i=1) \\ f_{i-1,2}~(s_i≠1) \end{cases},\begin{cases} f_{i-1,1}~(s_i=0) \\ \inf~(s_i≠0) \end{cases})
\\
f_{i,3} = \min(\begin{cases} f_{i-1,3}+1~(s_i=7 ~or~s_i=6) \\ f_{i-1,3}~(s_i≠7~and~s_i≠6) \end{cases},\begin{cases} f_{i-1,2}~(s_i=1) \\ \inf~(s_i≠1) \end{cases})
\\
f_{i,4} = \min(\begin{cases} f_{i-1,4}+1~(s_i=6) \\ f_{i-1,4}~(s_i≠6) \end{cases},\begin{cases} f_{i-1,3}~(s_i=7) \\ \inf~(s_i≠7) \end{cases})
\end{cases}
$

边界为 $f_{0}=\{0,\inf,\inf,\inf,\inf\}$（没有答案的状态取无穷大）。

------------

接下来，解决原题目。

学过矩阵优化 dp 的应该都能想到，把上面那一大串转移化成矩阵的形式，然后查询一段区间的时候把代表区间内数的矩阵乘起来就行。

化成矩阵如下（根据每一位的数字不同，矩阵也有些许差异，使用三目运算符表示，大家应该都能看懂）：

$$
\begin{bmatrix}
f_{i-1,0} & f_{i-1,1} & f_{i-1,2} & f_{i-1,3} & f_{i-1,4}
\end{bmatrix}
$$

$$\times$$

$$
\begin{bmatrix}
(s_i=2)?1:0 & (s_i=2)?0:\inf & \inf & \inf & \inf
\\
\inf &(s_i=0)?1:0 & (s_i=0)?0:\inf & \inf & \inf
\\
\inf & \inf &(s_i=1)?1:0 & (s_i=1)?0:\inf & \inf
\\
\inf & \inf & \inf &(s_i=7~or~s_i=6)?1:0 & (s_i=7)?0:\inf
\\
\inf & \inf & \inf & \inf & (s_i=6)?1:0
\end{bmatrix}
$$

$$=$$

$$
\begin{bmatrix}
f_{i,0} & f_{i,1} & f_{i,2} & f_{i,3} & f_{i,4}
\end{bmatrix}
$$

然后查询 $[l,r]$ 的答案就直接把 $s_{l:r}$ 的矩阵乘起来就行。这里可以用线段树维护。

注意有个问题，要不要乘上初始矩阵，即边界 $\begin{bmatrix}0&\inf&\inf&\inf&\inf\end{bmatrix}$ 呢？其实乘不乘都没多大关系，具体的我也不太明白（）可能在评论区会补充。

------------

```cpp
//CF750E
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10, inf = 0x3f3f3f3f;
int n, m; char s[N];
struct Matrix{
	int a[5][5];
	Matrix(){ memset(a, 0x3f, sizeof(a)); }
	Matrix operator * (const Matrix &p) const {
		Matrix ans;
		for(int i = 0; i < 5; ++ i)
			for(int j = 0; j < 5; ++ j)
				for(int k = 0; k < 5; ++ k)
					ans.a[i][j] = min(ans.a[i][j], a[i][k]+p.a[k][j]);
		return ans;
	}
};
struct SegmentTree{
	struct node{ int l, r; Matrix val; } T[N<<2];
	void build(int p, int l, int r){
		T[p].l = l, T[p].r = r;
		if(l == r){
			for(int i = 0; i < 5; ++ i) T[p].val.a[i][i] = 0;
			if(s[l] == '2') T[p].val.a[0][0] = 1, T[p].val.a[0][1] = 0;
			if(s[l] == '0') T[p].val.a[1][1] = 1, T[p].val.a[1][2] = 0;
			if(s[l] == '1') T[p].val.a[2][2] = 1, T[p].val.a[2][3] = 0;
			if(s[l] == '7') T[p].val.a[3][3] = 1, T[p].val.a[3][4] = 0;
			if(s[l] == '6') T[p].val.a[3][3] = 1, T[p].val.a[4][4] = 1;
		} else {
			int mid = l + r >> 1;
			build(p<<1, l, mid); build(p<<1|1, mid+1, r);
			T[p].val = T[p<<1].val * T[p<<1|1].val; 
		}
	}
	Matrix query(int p, int l, int r){
		if(l <= T[p].l && T[p].r <= r) return T[p].val;
		int mid = T[p].l + T[p].r >> 1;
//		Matrix res;
//		if(l <= mid) res = res * query(p<<1, l, r);
//		if(mid < r) res = res * query(p<<1|1, l, r);
//		return res;
//		写成上面这种有什么问题呢？问题在于res应该初始化为什么，为了避免这个问题，可以使用下面这种
		if(r <= mid) return query(p<<1, l, r);
		if(mid < l) return query(p<<1|1, l, r);
		return query(p<<1, l, r) * query(p<<1|1, l, r);
	}
} Solver;

int main(){
	scanf("%d%d%s", &n, &m, s+1);
	Solver.build(1, 1, n);
	while(m--){
		int l, r; scanf("%d%d", &l, &r);
		int res = Solver.query(1, l, r).a[0][4];
		printf("%d\n", (res >= inf ? -1 : res));
	}
	return 0;
}
```

---

## 作者：木xx木大 (赞：7)

[CF750E New Year and Old Subsequence](https://www.luogu.com.cn/problem/CF750E)

日常吐槽：这题翻译有问题啊，明明是子序列而不是子串

线段树维护矩乘良心题，不在树上，无修改。（被同机房巨佬吐槽说无修改是静态dp）
* 首先进行状压：设 $dp_{i,j}$ 表示到第 $i$ 个字符为止，子序列状态为 $j$ ,需要删除的最小字符个数。表示用0,1,2,3,4分别表示已有子序列状态为$\emptyset,2,20,201,2017$

* 发现 $dp_i$ 的转移仅与 $i-1$ 有关，考虑用矩阵乘法优化

* 设转移矩阵
  $$
  D=\left[ \begin{matrix} a_{0,0} \dots&a_{0,4} \\ a_{1,0} \dots&a_{1,4}  \\ a_{2,0} \dots&a_{2,4} \\ a_{3,0} \dots&a_{3,4}\\a_{4,0} \dots&a_{4,4} \end{matrix} \right]
  $$

其中 $a_{i,j}$ 表示从 $i$ 状态转移到 $j$ 状态需要删去的字符个数。对于一个不是关键字符的字符（关键字符为$0,1,2,6,7$），显然$a_{i,j}=0$。对于一个非6的关键字符，若要维持之前的状态，必须要删去这个字符；若要继续向下一个状态转移，不必删除这个字符。以2为例，初始转移矩阵为
$$
D=\left[ \begin{matrix} 1 & 0 & inf & inf & inf\\ inf & 0 & inf & inf & inf \\ inf & inf & 0 & inf & inf \\ inf & inf & inf & 0 & inf\\ inf & inf  & inf & inf & 0 \end{matrix} \right]
$$

当前字符为6时，如果已有状态为 $201$ 或 $2017$ ，必须删去这个字符。转移矩阵为
$$
D=\left[ \begin{matrix} 0 & inf & inf & inf & inf\\ inf & 0 & inf & inf & inf \\ inf & inf & 0 & inf & inf \\ inf & inf & inf & 1 & inf\\ inf & inf  & inf & inf & 1 \end{matrix} \right]
$$
为了回答一个区间的询问，用线段树维护矩阵即可（好像倍增也可以）


```cpp
#include<bits/stdc++.h>
#define mid (l+r)/2
using namespace std;
namespace FGF
{
	int n,m;
	const int N=2e5+5;
	struct matrx{
		int a[5][5];
	}t[N<<2];
	char s[N];
	const int INF=0x3f3f3f3f;
	matrx operator + (matrx x,matrx y)
	{
		matrx s;memset(s.a,0x3f,sizeof(s.a));
		for(int i=0;i<5;i++)
			for(int j=0;j<5;j++)	
				for(int k=0;k<5;k++)
					s.a[i][j]=min(s.a[i][j],x.a[i][k]+y.a[k][j]);
		return s;
	}
	void build(int ro,int l,int r)
	{
		if(l==r)
		{
			memset(t[ro].a,0x3f,sizeof(t[ro].a));
			for(int i=0;i<5;i++)
				t[ro].a[i][i]=0;
			if(s[l]=='2')t[ro].a[0][0]=1,t[ro].a[0][1]=0;
			if(s[l]=='0')t[ro].a[1][1]=1,t[ro].a[1][2]=0;
			if(s[l]=='1')t[ro].a[2][2]=1,t[ro].a[2][3]=0;
			if(s[l]=='7')t[ro].a[3][3]=1,t[ro].a[3][4]=0;
			if(s[l]=='6')t[ro].a[3][3]=1,t[ro].a[4][4]=1;
			return;
		}
		build(ro<<1,l,mid),build(ro<<1|1,mid+1,r);
		t[ro]=t[ro<<1]+t[ro<<1|1];
	}
	matrx ask(int ro,int l,int r,int L,int R)
	{
		if(l>=L&&r<=R)return t[ro];
		if(R<=mid)return ask(ro<<1,l,mid,L,R);
		if(L>mid)return ask(ro<<1|1,mid+1,r,L,R);
		return ask(ro<<1,l,mid,L,R)+ask(ro<<1|1,mid+1,r,L,R);
	}
	void work()
	{
		scanf("%d%d",&n,&m);
		scanf("%s",s+1);
		build(1,1,n);
		while(m--)
		{
			int L,R;
			scanf("%d%d",&L,&R);
			int ans=ask(1,1,n,L,R).a[0][4];
			if(ans>=INF)puts("-1");
			else printf("%d\n",ans);
		}
	}
}
int main()
{
	FGF::work();
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：3)

不知道为什么，题解都写的很令人谔谔，这里大致讲一下我的理解吧。        

~~也不是说讲的很模糊，只是感觉理解起来都有点歧义。~~

首先考虑一下这个 dp 应该长成个什么形式：            

令 $dp_{i,1/2/3/4/5}$ 表示如果在前 $i$ 个字母里面你要包含且只包含 $\phi/2/20/201/2017$ 需要删去的最小数字个数。            

这里的包且仅包含就比如说，包含了 $dp_{i,2}$ 这种状态就只能包含 $2$，而不能有 $20/201/2017$。                 

考虑可以以如下的方式 dp：              

记 $(x = y)$ 表示如果 $x = y$ 则该值为 $1$ 否则为 Inf，$[x = y]$ 表示如果 $x = y$ 则该值为 $1$ 否则该值为 $0$。

$dp_{i,1} = dp_{i - 1,1} + [s_i = 2]$

$dp_{i,2} = \min(dp_{i - 1 , 2} + [s_i = 0],dp_{i - 1,1} \times (s_i = 2))$

$dp_{i,3} = \min(dp_{i - 1 , 3} + [s_i = 1],dp_{i - 1,2} \times (s_i = 0))$

$dp_{i,4} = \min(dp_{i - 1 , 4} + [s_i = 7 \land s_i = 6] , dp_{i - 1,3} \times (s_i = 1))$

$dp_{i,5} = \min(dp_{i - 1,5} + [s_i = 6] , dp_{i - 1,4} \times (s_i = 7))$              

应该比较好理解，就不展开讲为什么了。                 

然后发现我们都是从 $dp_{i - 1}$ 转移到 $dp_i$ 的，加上有区间查询，不难想到线段树维护矩阵后区间查矩阵积。                

在叶子节点填入矩阵时注意：初始化时对角线值全初始化为 $0$ 其余值全初始化为 Inf ，然后在 $s_i = 2,0,1,6,7$ 时把系数直接打进去就好了。

时间复杂度 $O(5 ^ 3 n \log n)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5 , Inf = 1e9;
int n,q,l,r;
char s[Len];
struct Node
{
	int a[6][6];
	inline void Init(){for(int i = 1 ; i <= 5 ; i ++) for(int j = 1 ; j <= 5 ; j ++) a[i][j] = Inf;} 
	inline void build(){for(int i = 1 ; i <= 5 ; i ++) a[i][i] = 0;}
	Node operator * (const Node &y)
	{
		Node z;
		z.Init();
		for(int i = 1 ; i <= 5 ; i ++)
			for(int j = 1 ; j <= 5 ; j ++)
				for(int k = 1 ; k <= 5 ; k ++) z.a[i][j] = min(z.a[i][j] , a[i][k] + y.a[k][j]);
		return z;
	}
}tree[Len << 2],Int,ADD,RES;
bool flaw;
#define ls(p) p << 1
#define rs(p) p << 1 | 1
void push_up(int x){tree[x] = tree[ls(x)] * tree[rs(x)];}
void build(int p,int l,int r)
{
	if(l == r)
	{
		tree[p].Init();
		tree[p].build();
		if(s[l] == '2') tree[p].a[1][1] = 1 , tree[p].a[1][2] = 0;
		if(s[l] == '0') tree[p].a[2][2] = 1 , tree[p].a[2][3] = 0;
		if(s[l] == '1') tree[p].a[3][3] = 1 , tree[p].a[3][4] = 0;
		if(s[l] == '7') tree[p].a[4][4] = 1 , tree[p].a[4][5] = 0;
		if(s[l] == '6') tree[p].a[4][4] = 1 , tree[p].a[5][5] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
	push_up(p);
}
void query(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r) 
	{
		if(!flaw)
		{
			flaw = 1;
			ADD = tree[p];
		}
		else ADD = ADD * tree[p];
		return;
	}
	int mid = (l + r) >> 1;
	if(nl <= mid) query(ls(p) , l , mid , nl , nr);
	if(nr > mid) query(rs(p) , mid + 1 , r , nl , nr);
	push_up(p);
}
int main()
{
	Int.Init();
	Int.a[1][1] = 0;
	scanf("%d %d",&n,&q);
	scanf("%s",s + 1);
	build(1 , 1 , n);
	while(q --)
	{
		scanf("%d %d",&l,&r);
		flaw = 0;
		query(1 , 1 , n , l , r);
		RES = Int * ADD;
		if(RES.a[1][5] == Inf) RES.a[1][5] = -1;
		printf("%d\n",RES.a[1][5]);
	}
	return 0;
}
```

---

## 作者：tzc_wk (赞：3)

[Codeforces 题目传送门](https://codeforces.com/contest/750/problem/E) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF750E)

~~u1s1 我做这道 *2600 的动力是 wjz 出了道这个套路的题，而我连起码的思路都没有，wtcl/kk~~

首先考虑怎样对某个固定的串计算答案，这显然可以 $dp$ 解决，设 $dp_{i,j}$ 表示考虑前 $i$ 个字符，删去之后与 $2017$ 的 LCS 为 $j$，最少需删除多少个字符，那么显然有转移方程：

- $dp_{i,0}=\begin{cases}dp_{i-1,0}&(s[i]\neq'2')\\dp_{i-1,0}+1&(s[i]='2')\end{cases}$
- $dp_{i,1}=\begin{cases}dp_{i-1,0}&(s[i]\neq'0'\land s[i]\neq'2')\\\min(dp_{i-1,1},dp_{i-1,0})&(s[i]='2')\\dp_{i-1,0}+1&(s[i]='0')\end{cases}$
- $dp_{i,2}=\begin{cases}dp_{i-1,1}&(s[i]\neq'1'\land s[i]\neq'0')\\\min(dp_{i-1,2},dp_{i-1,0})&(s[i]='0')\\dp_{i-1,1}+1&(s[i]='1')\end{cases}$
- $dp_{i,3}=\begin{cases}dp_{i-1,3}&(s[i]\neq'7'\land s[i]\neq'1'\land s[i]\neq'6')\\\min(dp_{i-1,3},dp_{i-1,2})&(s[i]='1')\\dp_{i-1,2}+1&(s[i]='6'\lor s[i]='7')\end{cases}$
- $dp_{i,4}=\begin{cases}dp_{i-1,4}&(s[i]\neq'7'\land s[i]\neq'6')\\\min(dp_{i-1,4},dp_{i-1,3})&(s[i]='7')\\dp_{i-1,4}+1&(s[i]='6')\end{cases}$

初始值为 $dp_{0,0}=0,dp_{0,i}=-\infty(i>0)$。

注意到像这样的**常系数其次线性递推式**可以写成矩阵的形式，也就是说对于每个字符 $s_i$ 都可以找到一个 $4\times 4$ 矩阵 $A_i$ 使得 $\begin{bmatrix}dp_{i,0}\\dp_{i,1}\\dp_{i,2}\\dp_{i,3}\\dp_{i,4}\end{bmatrix}=A_i\times\begin{bmatrix}dp_{i-1,0}\\dp_{i-1,1}\\dp_{i-1,2}\\dp_{i-1,3}\\dp_{i-1,4}\end{bmatrix}$，也就是说对于一组询问 $[l,r]$，如果我们记 $B_i=\begin{bmatrix}dp_{i,0}\\dp_{i,1}\\dp_{i,2}\\dp_{i,3}\\dp_{i,4}\end{bmatrix}$，那么有 $B_r=A_r\times B_{r-1}=A_r\times A_{r-1}\times B_{r-2}=A_r\times A_{r-1}\times\dots A_l\times B_{l-1}$，而显然有 $B_{l-1}=\begin{bmatrix}0\\-\infty\\-\infty\\-\infty\\-\infty\end{bmatrix}$，故最终的答案为 $(\prod\limits_{i=l}^rA_i)\times \begin{bmatrix}0\\-\infty\\-\infty\\-\infty\\-\infty\end{bmatrix}$。不难发现这个东西是以区间乘法的形式出现的，而矩阵又不支持除法，故可以想到我们喜闻乐见的线段树。简单维护一下即可。

时间复杂度 $q\omega^3\log n$，其中 $\omega$ 为矩阵大小，在此题中为 $5$。

这个套路（线段树维护矩阵乘法）就是动态 dp（ddp） 的大致思想，比较毒瘤的动态 dp 一般还需套个树剖什么的。不过由于我太懒了就暂且不继续学 ddp 了（

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=2e5;
const int INF=0x3f3f3f3f;
int n,qu;char str[MAXN+5];
struct matrix{
	int a[5][5];
	matrix(){memset(a,63,sizeof(a));}
	matrix operator *(const matrix &rhs){
		matrix ret;
		for(int i=0;i<5;i++) for(int j=0;j<5;j++) for(int k=0;k<5;k++)
			chkmin(ret.a[i][j],a[i][k]+rhs.a[k][j]);
		return ret;
	}
};
struct node{int l,r;matrix v;} s[MAXN*4+5];
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;if(l==r){
		for(int i=0;i<5;i++) s[k].v.a[i][i]=0;
		if(str[l]=='2') s[k].v.a[0][0]=1,s[k].v.a[0][1]=0;
		if(str[l]=='0') s[k].v.a[1][1]=1,s[k].v.a[1][2]=0;
		if(str[l]=='1') s[k].v.a[2][2]=1,s[k].v.a[2][3]=0;
		if(str[l]=='7') s[k].v.a[3][3]=1,s[k].v.a[3][4]=0;
		if(str[l]=='6') s[k].v.a[3][3]=1,s[k].v.a[4][4]=1;
		return;
	} int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	s[k].v=s[k<<1].v*s[k<<1|1].v;
}
matrix query(int k,int l,int r){
	if(l<=s[k].l&&s[k].r<=r) return s[k].v;
	int mid=s[k].l+s[k].r>>1;
	if(r<=mid) return query(k<<1,l,r);
	else if(l>mid) return query(k<<1|1,l,r);
	else return query(k<<1,l,mid)*query(k<<1|1,mid+1,r);
}
int main(){
	scanf("%d%d%s",&n,&qu,str+1);build(1,1,n);
	while(qu--){
		int l,r;scanf("%d%d",&l,&r);int ret=query(1,l,r).a[0][4];
		if(ret>=INF) puts("-1");else printf("%d\n",ret);
	}
	return 0;
}
```

---

## 作者：zesqwq (赞：3)

# CF750E New Year and Old Subsequence

## solution

我们用 $f_{i,k}$ 表示考虑到第 $i$ 位，要有 $2017$ 的前 $k$ 位的子序列并且不包含 $2016$ 最少要用几个数。

然后就可以把 $\text{dp}$ 方程写出来

$$f_{i,0}=f_{i-1,0} + [s_i=2]$$
$$f_{i,1}=\min\{f_{i-1,1} + [s_i=0],\text{if}[s_i = 2]f_{i-1,0}\}$$
$$f_{i,2}=\min\{f_{i-1,2} + [s_i=1],\text{if}[s_i = 0]f_{i-1,1}\}$$
$$f_{i,3}=\min\{f_{i-1,3} + ([s_i=7] \text{or} [s_i=6]),\text{if}[s_i = 1]f_{i-1,2}\}$$
$$f_{i,4}=\min\{f_{i-1,4} + [s_i=6],\text{if}[s_i = 7]f_{i-1,3}\}$$

注意到后面的转移中条件如果不成立则不能转移。

接着我们发现题目把这个东西转换成了区间问题，于是乎我们就采用动态 $\text{dp}$ 的套路去写这个 $\text{dp}$ 式。

$$\begin{bmatrix} f_{i - 1,0} & f_{i - 1,1} & f_{i - 1,2} & f_{i - 1,3} & f_{i - 1,4} \end{bmatrix} * \begin{bmatrix} a & b & c & d & e \\ f & g & h & i & j \\ k & l & m & n & o \\ p & q & r & s & t \\ u & v & w & x & y\end{bmatrix} = \begin{bmatrix} f_{i,0} & f_{i,1} & f_{i,2} & f_{i,3} & f_{i,4} \end{bmatrix}$$

为了方便写，我用 $x\to0$ 表示如果 $x=1$，则值为 $0$，否则为无穷大。

接着就硬解这个矩阵，解出来会长这个样子。

$$\begin{bmatrix} [s_i=2] & s_i=2\to 0 & inf & inf & inf \\ inf & [s_i=0] & s_i=0\to 0 & inf & inf \\ inf & inf & [s_i = 1] & s_1 = 1\to 0 & inf \\ inf & inf & inf & [s_i=7] \text{or} [s_i=6] & s_i=7\to 0 \\ inf & inf & inf & inf & [s_i=6]\end{bmatrix}$$

然后就把这个东西扔到线段树里就 $\text{OK}$ 了。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
constexpr int inf = 0x3f3f3f3f;
struct Matrix {
    int mat[5][5];
    inline Matrix operator*(const Matrix &b) const {
        Matrix c;
        memset(c.mat, 0x3f, sizeof(c.mat));
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                for (int k = 0; k < 5; k++) c.mat[i][j] = min(mat[i][k] + b.mat[k][j], c.mat[i][j]);
        return c;
    }
} w[N << 2];
int n, q;
char s[N];
inline void pushup(int u) { w[u] = w[u << 1] * w[u << 1 | 1]; }
void build(int u, int L, int R) {
    if (L == R) {
        char c = s[L];
        w[u] = (Matrix){{{c == '2', c == '2' ? 0 : inf, inf, inf, inf},
                         {inf, c == '0', c == '0' ? 0 : inf, inf, inf},
                         {inf, inf, c == '1', c == '1' ? 0 : inf, inf},
                         {inf, inf, inf, c == '7' || c == '6', c == '7' ? 0 : inf},
                         {inf, inf, inf, inf, c == '6'}}};
        return;
    }
    int M = L + R >> 1;
    build(u << 1, L, M), build(u << 1 | 1, M + 1, R);
    pushup(u);
}
Matrix query(int u, int L, int R, int l, int r) {
    if (L >= l && R <= r) return w[u];
    int M = L + R >> 1;
    if (M >= r) return query(u << 1, L, M, l, r);
    if (M < l) return query(u << 1 | 1, M + 1, R, l, r);
    return query(u << 1, L, M, l, r) * query(u << 1 | 1, M + 1, R, l, r);
}
int main() {
    cin >> n >> q;
    scanf("%s", s + 1), build(1, 1, n);
    int l, r;
    while (q--) {
        scanf("%d %d", &l, &r);
        Matrix ans = query(1, 1, n, l, r);
        printf("%d\n", ans.mat[0][4] <= n ? ans.mat[0][4] : -1);
    }
    return 0;
}
```



---

## 作者：Hoks (赞：0)

## 前言
比较简单的题。

摘自[杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
考虑下如果只有一次询问 $[1,n]$ 怎么做。

肯定是考虑设计一个 dp。

定义 $f_{i,0/1/2/3/4}$ 为目前已经出现过了 $\phi/2/20/201/2017$ 最少要删掉多少个字符。

那么转移方程式就可以比较简单的写出来了：

$$f_{i,0}=f_{i-1,0}+(s_i=2)$$

因为我们要保证还是 $0$，所以要删掉 $2$。

$$f_{i,1}=\min(f_{i-1,0}(s_i=2),f_{i-1,1}+(s_i=0))$$

$$f_{i,2}=\min(f_{i-1,1}(s_i=0),f_{i-1,2}+(s_i=1))$$

$$f_{i,3}=\min(f_{i-1,2}(s_i=1),f_{i-1,3}+(s_i=7))$$

$$f_{i,4}=\min(f_{i-1,3}(s_i=7),f_{i-1,4}+(s_i=6))$$

考虑如何优化这个东西。

构造成矩阵扔到线段树上去维护。

直接把转移方程式抄下来就行了，但是记得不能转移的要赋 INF 防止错误转移。
## 代码

```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=2e5+10,M=5,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
struct Matrix
{
    int a[M][M];Matrix(){memset(a,0x3f,sizeof a);}
    Matrix operator * (const Matrix &b)const
    {
        Matrix t;
        for(int i=0;i<M;i++) for(int j=0;j<M;j++)
            for(int k=0;k<M;k++) t.a[i][j]=min(t.a[i][j],a[i][k]+b.a[k][j]);
        return t;
    }
}a[N],t[N<<2],ans,base;int n,m;char s[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='&'||c=='|'||c=='('||c==')'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void build(int p,int l,int r)
{
    if(l==r) return t[p]=a[l],void();
    build(ls,l,mid);build(rs,mid+1,r);t[p]=t[ls]*t[rs];
}
inline void query(int p,int l,int r,int s,int e)
{
    if(l>=s&&r<=e) return ans=ans*t[p],void();
    if(mid>=s) query(ls,l,mid,s,e);
    if(mid<e) query(rs,mid+1,r,s,e);
}
inline void solve()
{
    read();m=read();base.a[0][0]=0;rd(s,n);for(int i=1;i<=n;i++)
    {
        for(int j=0;j<M;j++) a[i].a[j][j]=0;
        if(s[i]=='0') a[i].a[1][1]=1,a[i].a[1][2]=0;
        if(s[i]=='1') a[i].a[2][2]=1,a[i].a[2][3]=0;
        if(s[i]=='2') a[i].a[0][0]=1,a[i].a[0][1]=0;
        if(s[i]=='6') a[i].a[3][3]=1,a[i].a[4][4]=1;
        if(s[i]=='7') a[i].a[3][3]=1,a[i].a[3][4]=0;
    }build(1,1,n);for(int i=1,l,r;i<=m;i++)
    {
        l=read(),r=read();ans=base;query(1,1,n,l,r);
        print(ans.a[0][4]<n?ans.a[0][4]:-1),put('\n');
    }
}
signed main()
{
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：Jerrywang09 (赞：0)

动态 DP。先考虑如何写出朴素的 DP：设 $f(i,j)$ 表示到第 $i$ 个字符，最少需要删掉多少个字符，可以得到 $2017$ 的前 $j$ 个字符。

分情况讨论转移，详见如下的暴力代码。转移分为两种：继承原状态并删数，或者添加一个数。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=200010, inf=0x3f3f3f3f;
using namespace std;

int n, T, a[N], f[N][5];

int main()
{
	scanf("%d%d", &n, &T);
	rep(i, 1, n) scanf("%1d", a+i);
	while(T--)
	{
		int l, r; scanf("%d%d", &l, &r);
		f[l-1][0]=0, f[l-1][1]=f[l-1][2]=f[l-1][3]=f[l-1][4]=inf;
		rep(i, l, r)
		{
			f[i][0]=f[i-1][0]+(a[i]==2);
			f[i][1]=f[i-1][1]+(a[i]==0);
			if(a[i]==2) f[i][1]=min(f[i][1], f[i-1][0]);
			f[i][2]=f[i-1][2]+(a[i]==1);
			if(a[i]==0) f[i][2]=min(f[i][2], f[i-1][1]);
			f[i][3]=f[i-1][3]+(a[i]==6 || a[i]==7);
			if(a[i]==1) f[i][3]=min(f[i][3], f[i-1][2]);
			f[i][4]=f[i-1][4]+(a[i]==6);
			if(a[i]==7) f[i][4]=min(f[i][4], f[i-1][3]);
		}
		printf("%d\n", f[r][4]>n?-1:f[r][4]);
	}
	
	return 0;
}
```

将下标 $i$ 位置上的转移写成矩阵，在线段树上维护，即可得到正解。

```cpp
// Title:  New Year and Old Subsequence
// Source: CF750E
// Author: Jerrywang
#include <bits/stdc++.h>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=200010, inf=0x3f3f3f3f;
using namespace std;

int n, T, a[N], f[N][5];

struct mat
{
	int a[5][5];
	void O() {memset(a, 0x3f, sizeof a);}
	void E() {O(); rep(i, 0, 4) a[i][i]=0;}
};
mat operator *(mat a, mat b)
{
	mat res; res.O();
	rep(k, 0, 4) rep(i, 0, 4) rep(j, 0, 4)
		res.a[i][j]=min(res.a[i][j], a.a[i][k]+b.a[k][j]);
	return res;
}

struct node
{
	int l, r; mat a;
} t[N<<2];
#define lc p<<1
#define rc p<<1|1
void build(int p, int l, int r)
{
	t[p]={l, r};
	if(l==r)
	{
		mat &A=t[p].a;
		A.E();
		if(a[l]==2) A.a[0][0]=1, A.a[0][1]=0;
		if(a[l]==0) A.a[1][1]=1, A.a[1][2]=0;
		if(a[l]==1) A.a[2][2]=1, A.a[2][3]=0;
		if(a[l]==6 || a[l]==7) A.a[3][3]=1;
		if(a[l]==7) A.a[3][4]=0;
		if(a[l]==6) A.a[4][4]=1;
		return;
	}
	int mid=l+r>>1;
	build(lc, l, mid), build(rc, mid+1, r);
	t[p].a=t[lc].a*t[rc].a;
}
mat query(int p, int l, int r)
{
	if(l<=t[p].l && t[p].r<=r) return t[p].a;
	int mid=t[p].l+t[p].r>>1;
	if(r<=mid) return query(lc, l, r);
	if(l>mid)  return query(rc, l, r);
	return query(lc, l, r)*query(rc, l, r);
}

int main()
{
	scanf("%d%d", &n, &T);
	rep(i, 1, n) scanf("%1d", a+i);
	build(1, 1, n);
	while(T--)
	{
		int l, r; scanf("%d%d", &l, &r);
		mat t; t.O();
		t.a[0][0]=0, t.a[0][1]=t.a[0][2]=t.a[0][3]=t.a[0][4]=inf;
		t=t*query(1, l, r);
		printf("%d\n", t.a[0][4]>n?-1:t.a[0][4]);
	}
	
	return 0;
}
```

---

## 作者：__ycx2010__ (赞：0)

## Solution

设 $f_{i,0/1/2/3/4}$ 表示前 $i$ 个字符不包含 $2016$ 且包含 $\emptyset,2,20,201,2017$ 所需要改变的最小字符数量。

将状态转移方程转为矩阵乘法形式，然后用线段树维护区间矩阵乘法即可，时间复杂度 $O(n\log n)$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 200010, inf = 0x3f3f3f3f;
char s[N];

struct matrix {
	int a[5][5];
	void init(int x) {
		int tmp[5][5] = 
			{{(x == 2), inf, inf, inf, inf},
			{(x == 2) ? 0 : inf, (x == 0), inf, inf, inf},
			{inf, (x == 0) ? 0 : inf, (x == 1), inf, inf},
			{inf, inf, (x == 1) ? 0 : inf, (x == 6 || x == 7), inf},
			{inf, inf, inf, (x == 7) ? 0 : inf, (x == 6)}};
		for (int i = 0; i < 5; i ++ )
			for (int j = 0; j < 5; j ++ )
				a[i][j] = tmp[j][i];
	}
	const matrix operator *(const matrix &B) const {
		matrix C;
		for (int i = 0; i < 5; i ++ )
			for (int j = 0; j < 5; j ++ ) {
				C.a[i][j] = inf;
				for (int k = 0; k < 5; k ++ )
					C.a[i][j] = min(C.a[i][j], a[i][k] + B.a[k][j]);
			}
		return C;
	}
} tr[N << 2];

void pushup(int u) {
	tr[u] = tr[u << 1] * tr[u << 1 | 1];
}

void build(int u, int l, int r) {
	if (l == r) {
		int x = s[l] - '0';
		tr[u].init(x);
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
	pushup(u);
}

matrix query(int u, int l, int r, int s, int t) {
	if (s <= l && r <= t) return tr[u];
	int mid = l + r >> 1;
	if (s > mid) return query(u << 1 | 1, mid + 1, r, s, t);
	if (t <= mid) return query(u << 1, l, mid, s, t);
	return query(u << 1, l, mid, s, t) * query(u << 1 | 1, mid + 1, r, s, t);
}

int main() {
	int n, q;
	scanf("%d%d%s", &n, &q, s + 1);
	build(1, 1, n);
	while (q -- ) {
		int l, r;
		scanf("%d%d", &l, &r);
		matrix tmp = query(1, 1, n, l, r);
		if (tmp.a[0][4] == inf) puts("-1");
		else printf("%d\n", tmp.a[0][4]);
	}
	return 0;
}
```

---

## 作者：SoyTony (赞：0)

先考虑朴素 DP，设 $f_i$ 表示 $[1,i]$ 前缀的最小代价。

设计状态就要考虑当前与 $2016$ 的匹配程度以及是否已经匹配了 $2017$，具体可以设计成 $5$ 个状态，$0/1/2/3$ 分别对应最多匹配到 $2016$ 第 $0/1/2/3$ 位，$4$ 代表匹配到 $201$ 且已经匹配了 $2017$。

转移和当前这一位是什么有关，绝大多数状态都是直接从 $f_{i-1}$ 顺承过来。

比较特殊的例如 $a_i=2$ 时：

$$f_{i,0}=f_{i-1,0}+1,f_{i,1}=\min(f_{i-1,0},f_{i-1,1})$$

即保持原来匹配状态必须要花费代价删去，更新匹配状态取二者较小值，$a_i=0,1$ 同理。

另外在 $a_i=6$ 位置则是：

$$f_{i,3}=f_{i-1,3}+1,f_{i,4}=f_{i-1,4}+1$$

也就是必须花费代价删去。

这样得到一个单次 $O(n)$ 的做法，考虑优化。

注意到转移都是线性的，且类似 $(\min,+)$，这个满足广义矩阵乘法，可以线段树维护转移矩阵优化。

把转移方程原样挪到矩阵上就行了，如果不转移就把转移矩阵设成 $\infty$。

（转移矩阵太多了，为了方便见代码主函数）

```cpp
int n,q;
char s[maxn];
int f[maxn][5];

struct Matrix{
    int a[5][5];
    Matrix(){
        for(int i=0;i<5;++i){
            for(int j=0;j<5;++j){
                a[i][j]=inf;
            }
        }
    }
    Matrix operator*(const Matrix &rhs)const{
        Matrix res;
        for(int i=0;i<5;++i){
            for(int j=0;j<5;++j){
                for(int k=0;k<5;++k){
                    res.a[i][k]=min(res.a[i][k],a[i][j]+rhs.a[j][k]);
                }
            }
        }
        return res;
    }
    inline void output(){
        for(int i=0;i<5;++i){
            for(int j=0;j<5;++j){
                printf("%10d ",a[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}I[10];

struct SegmentTree{
#define mid ((l+r)>>1)
#define lson rt<<1,l,mid
#define rson rt<<1|1,mid+1,r
    Matrix Mat[maxn<<2];
    inline void push_up(int rt){
        Mat[rt]=Mat[rt<<1]*Mat[rt<<1|1];
    }
    void build(int rt,int l,int r){
        if(l==r){
            Mat[rt]=I[s[l]-'0'];
            return;
        }
        build(lson),build(rson);
        push_up(rt);
    }
    Matrix query(int rt,int l,int r,int pl,int pr){
        if(pl<=l&&r<=pr) return Mat[rt];
        if(pr<=mid) return query(lson,pl,pr);
        else if(pl>mid) return query(rson,pl,pr);
        else return query(lson,pl,pr)*query(rson,pl,pr);
    }
#undef mid
#undef lson
#undef rson
}S;

int ans;

int main(){
    I[0].a[0][0]=0,I[0].a[1][1]=1,I[0].a[1][2]=0,I[0].a[2][2]=0,I[0].a[3][3]=0,I[0].a[4][4]=0;
    I[1].a[0][0]=0,I[1].a[1][1]=0,I[1].a[2][2]=1,I[1].a[2][3]=0,I[1].a[3][3]=0,I[1].a[4][4]=0;
    I[2].a[0][0]=1,I[2].a[0][1]=0,I[2].a[1][1]=0,I[2].a[2][2]=0,I[2].a[3][3]=0,I[2].a[4][4]=0;
    I[3].a[0][0]=0,I[3].a[1][1]=0,I[3].a[2][2]=0,I[3].a[3][3]=0,I[3].a[4][4]=0;
    I[4].a[0][0]=0,I[4].a[1][1]=0,I[4].a[2][2]=0,I[4].a[3][3]=0,I[4].a[4][4]=0;
    I[5].a[0][0]=0,I[5].a[1][1]=0,I[5].a[2][2]=0,I[5].a[3][3]=0,I[5].a[4][4]=0;
    I[6].a[0][0]=0,I[6].a[1][1]=0,I[6].a[2][2]=0,I[6].a[3][3]=1,I[6].a[4][4]=1;
    I[7].a[0][0]=0,I[7].a[1][1]=0,I[7].a[2][2]=0,I[7].a[3][3]=0,I[7].a[3][4]=0,I[7].a[4][4]=0;
    I[8].a[0][0]=0,I[8].a[1][1]=0,I[8].a[2][2]=0,I[8].a[3][3]=0,I[8].a[4][4]=0;
    I[9].a[0][0]=0,I[9].a[1][1]=0,I[9].a[2][2]=0,I[9].a[3][3]=0,I[9].a[4][4]=0;
    n=read(),q=read();
    scanf("%s",s+1);
    S.build(1,1,n);
    while(q--){
        int l=read(),r=read();
        Matrix now=S.query(1,1,n,l,r);
        ans=now.a[0][4];
        if(ans==inf) ans=-1;
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：CmsMartin (赞：0)

[更好的阅读体验](http://cmsblog.top/archives/2023-01-13-15-59-36)

## 题目描述

[题目传送门](http://codeforces.com/problemset/problem/750/E)

## 思路

先忽视区间查询，比较好想到的是动态规划，设 $f_{i,0/1/2/3/4}$ 分别表示 $[1,i]$ 分别满足含有 $\varnothing/2/20/201/2017$ 子序列且没有 $2016$ 的方案数。

接下来大力转移：

首先定义 $g(0) = +\infty, g(1) = 0$。

+ $f_{i,0}$ 的转移
> $f_{i,0}$ 需要删的时候，就是出现了 $2$，那么很容易得到转移为：

$$f_{i,0} = f_{i-1,0}+ [s=2]$$

+ $f_{i,1}$ 的转移
> $f_{i,1}$ 需要删的时候，就是前面出现了 $2$，并且这里出现了 $0$，或者这里第一次出现 $2$，那么很容易得到转移为：

$$
f_{i,1} = \min\{f_{i - 1, 1} + [s_i = 0], f_{i - 1, 0} + g([s_i = 2])\}
$$

+ $f_{i,2}$ 的转移
> $f_{i,2}$ 需要删的时候，就是前面出现了 $20$，并且这里出现了 $1$，或者前面出现了 $2$，并且这里出现了 $0$，那么很容易得到转移为：

$$
f_{i,2} = \min\{f_{i - 1, 2} + [s_i = 1], f_{i - 1, 1} + g([s_i = 0])\}
$$

+ $f_{i,3}$ 的转移
> $f_{i,3}$ 需要删的时候，就是前面出现了 $201$，并且这里出现了 $6$ 或者 $7$，或者前面出现了 $20$，并且这里出现了 $1$，那么很容易得到转移为：

$$
f_{i,3} = \min\{f_{i - 1, 3} + [s_i = 6 \lor s_i = 7], f_{i - 1, 2} + g([s_i = 1])\}
$$

+ $f_{i,4}$ 的转移
> $f_{i,4}$ 需要删的时候，就是前面出现了 $2017$，并且这里出现了 $6$，或者前面出现了 $201$，并且这里出现了 $7$，那么很容易得到转移为：

$$
f_{i,4} = \min\{f_{i - 1, 4} + [s_i = 6], f_{i - 1, 3} + g([s_i = 7])\}
$$

然后转移就做完了。

观察到数据范围很大，考虑矩阵快速幂优化，很容易想到首先要新定义矩阵乘法：

$$\mathbf{C}_{i,j} = \min_{1 \le k \le n}\{ \mathbf{A}_{i,k} + \mathbf{B}_{k,j}\}$$

然后，我们可以把动态规划写成矩阵：

$$
\begin{bmatrix}
f_{i,0} & f_{i,1} & f_{i,2} & f_{i,3} & f_{i,4}
\end{bmatrix}

=

\begin{bmatrix}
f_{i - 1,0} & f_{i - 1,1} & f_{i - 1,2} & f_{i - 1,3} & f_{i - 1,4}
\end{bmatrix}

\times

\begin{bmatrix}
[s_i=2]& g([s_i=2]) & +\infty & +\infty & +\infty \\
+\infty & [s_i=0] & g([s_i=0]) & +\infty & +\infty \\
+\infty & +\infty & [s_i=1] & g([s_i = 1]) & +\infty \\
+\infty & +\infty & +\infty & [s_i = 6 \lor s_i = 7] & g([s_i=7]) \\
+\infty & +\infty & +\infty & +\infty & [s_i=6]
\end{bmatrix}
$$

然后，我们由于要查询区间的答案，那么用线段树维护区间矩阵乘法，然后设区间 $[l,r]$ 转移矩阵的积为 $\mathbf{C}$，那么答案为：

$$\begin{bmatrix} 0 & +\infty & +\infty & +\infty & +\infty \end{bmatrix} \times \mathbf{C}$$

然后就做完了，时间复杂度 $\Theta(q\log n)$，常数极大。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN_Matrix = 5, MAXN = 2e5 + 10;

struct Matrix {
    int M[MAXN_Matrix][MAXN_Matrix];
    Matrix() {
        memset(M, 0x3f, sizeof M);
    }
    Matrix friend operator*(Matrix x, Matrix y) {
        Matrix res;
        for (int i = 0; i < MAXN_Matrix; i++) {
            for (int j = 0; j < MAXN_Matrix; j++) {
                for (int k = 0; k < MAXN_Matrix; k++) {
                    res.M[i][j] = min(res.M[i][j], x.M[i][k] + y.M[k][j]);
                }
            }
        }
        return res;
    }

    Matrix friend operator^(Matrix x, Matrix y) {
        Matrix res;
        for (int i = 0; i < MAXN_Matrix; i++) {
            for (int j = 0; j < MAXN_Matrix; j++) {
                res.M[0][i] = min(res.M[0][i], x.M[0][j] + y.M[j][i]);
            }
        }
        return res;
    }
} SMT[MAXN << 2], Ans, Prime, G[MAXN];

void Build(int p, int l, int r) {
    if (l == r) {
        SMT[p] = G[l];
        return;
    }
    int mid = l + r >> 1;
    Build(p << 1, l, mid);
    Build(p << 1 | 1, mid + 1, r);
    SMT[p] = SMT[p << 1] * SMT[p << 1 | 1];
}

void Query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        Ans = Ans ^ SMT[p];
        return;
    }
    int mid = l + r >> 1;
    if (ql <= mid) Query(p << 1, l, mid, ql, qr);
    if (mid < qr) Query(p << 1 | 1, mid + 1, r, ql, qr);
}

int N, P;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> P;
    Prime.M[0][0] = 0;
    for (int i = 1; i <= N; i++) {
        static char S;
        cin >> S;
        for (int j = 0; j < MAXN_Matrix; j++) G[i].M[j][j] = 0;
        if (S == '2') {
            G[i].M[0][0] = 1;
            G[i].M[0][1] = 0;
        }
        if (S == '0') {
            G[i].M[1][1] = 1;
            G[i].M[1][2] = 0;
        }
        if (S == '1') {
            G[i].M[2][2] = 1;
            G[i].M[2][3] = 0;
        }
        if (S == '7') {
            G[i].M[3][3] = 1;
            G[i].M[3][4] = 0;
        }
        if (S == '6') {
            G[i].M[3][3] = 1;
            G[i].M[4][4] = 1;
        }
    }
    Build(1, 1, N);
    for (int i = 1; i <= P; i++) {
        static int l, r;
        cin >> l >> r;
        Ans = Prime;
        Query(1, 1, N, l, r);
        cout << (Ans.M[0][4] <= N ? Ans.M[0][4] : -1) << endl;
    }
    return 0;
}
```

---

## 作者：chroneZ (赞：0)

设 $f_{i. 0 / 1 / 2 / 3 / 4}$ 表示考虑到第 $i$ 个位置，当前字符串**包含且仅包含**字符串 $\varnothing, \text{2}, \text{20}, \text{201}, \text{2017}$ 时的最小删除数。容易得到如下的转移：

$$
\begin{array}{l}
f_{i, 0} = f_{i - 1, 0} + [s_i = 2] \\
f_{i, 1} = \min \left \{ \begin{array}{l} f_{i - 1, 0}, s_i = 2 \\f_{i - 1, 1} + [s_i = 0] \end{array}\right.\\
f_{i, 2} = \min \left \{ \begin{array}{l} f_{i - 1, 1}, s_i = 0 \\f_{i - 1, 2} + [s_i = 1] \end{array}\right.\\
f_{i, 3} = \min \left \{ \begin{array}{l} f_{i - 1, 2}, s_i = 1 \\f_{i - 1, 3} + [s_i = 6 \vee s_i = 7] \end{array}\right.\\
f_{i, 4} = \min \left \{ \begin{array}{l} f_{i - 1, 3}, s_i = 7 \\f_{i - 1, 4} + [s_i = 6] \end{array}\right.
\end{array}
$$

由于需要支持区间询问，因此定义广义矩阵乘法 $(A * B)_{ij} = \min \limits_{k = 1} ^ n \{A_{ik} + B_{kj} \}$，则状态转移可被等价于如下形式：
$$
\begin{bmatrix}
	f_{i, 0} & f_{i, 1} & f_{i, 2} & f_{i, 3} & f_{i, 4}
\end{bmatrix}
=
\begin{bmatrix}
	f_{i - 1, 0} & f_{i - 1, 1} & f_{i - 1, 2} & f_{i - 1, 3} & f_{i - 1, 4}
\end{bmatrix}
*
\begin{bmatrix}
	[s_i = 2] 	& [s_i \neq 2]\cdot \infty 	& \infty		 			& \infty		 			& \infty\\
	\infty 		& [s_i = 0] 				& [s_i \neq 0] \cdot \infty & \infty 					& \infty\\
	\infty	 	& \infty 					& [s_i = 1] 				& [s_i \neq 1] \cdot \infty & \infty\\
	\infty 		& \infty				 	& \infty 					& [s_i = 6 \vee s_i = 7] 	& [s_i \neq 7] \cdot \infty\\
	\infty 		& \infty 					& \infty 					& \infty 					& [s_i = 6]
\end{bmatrix}
$$
记上式中的 $5 \times 5$ 矩阵为 $U_i$，则对于一组询问区间 $(l, r)$，其目标矩阵为 $\begin{bmatrix} 0 & \infty & \infty & \infty & \infty \end{bmatrix} * \prod \limits_{i = l} ^ r U_i$。其实该式的结果与 $\prod \limits_{i = l} ^ r U_i$ 的第一行是等价的。

由于矩阵乘法满足广义结合律，因此可以使用线段树维护区间矩阵积即可。

```cpp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int INF = 1e9, MN = 2e5 + 10;
struct matrix{
	int A[5][5]; int N, M;
	matrix operator * (const matrix &x) const {
		matrix r;
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 5; j++){
				r.A[i][j] = INF;
				for(int k = 0; k < 5; k++)
					r.A[i][j] = min(r.A[i][j], A[i][k] + x.A[k][j]);
			}
		}
		return r;
	}
};
matrix t[MN << 2], a[MN];
void build(int k, int l, int r){
	if(l == r){
		t[k] = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	t[k] = t[k << 1] * t[k << 1 | 1];
}
matrix query(int k, int l, int r, int x, int y){
	if(x <= l && r <= y) return t[k];
	int mid = l + r >> 1;
	if(y <= mid) return query(k << 1, l, mid, x, y);
	if(x > mid) return query(k << 1 | 1, mid + 1, r, x, y);
	return query(k << 1, l, mid, x, y) * query(k << 1 | 1, mid + 1, r, x, y);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	int n, q; cin >> n >> q;
	string s; cin >> s;
	matrix cur;
	memset(cur.A, 0x3f, sizeof(cur.A));
	for(int i = 0; i < n; i++){
		cur.A[0][0] = (s[i] == '2');
		cur.A[0][1] = (s[i] != '2' ? INF : 0);
		cur.A[1][1] = (s[i] == '0');
		cur.A[1][2] = (s[i] != '0' ? INF : 0);
		cur.A[2][2] = (s[i] == '1');
		cur.A[2][3] = (s[i] != '1' ? INF : 0);
		cur.A[3][3] = (s[i] == '6' || s[i] == '7');
		cur.A[3][4] = (s[i] != '7' ? INF : 0);
		cur.A[4][4] = (s[i] == '6');
		a[i + 1] = cur;
	}
	build(1, 1, n);
	int l, r;
	while(q--){
		cin >> l >> r;
		int res = query(1, 1, n, l, r).A[0][4];
		cout << (res >= INF ? -1 : res) << "\n";
	}
}
```



---

