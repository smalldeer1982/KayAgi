# [COCI 2009/2010 #4] PALACINKE

## 题目描述

 **译自 [COCI 2010.02](http://hsin.hr/coci/archive/2009_2010/) T6「[PALACINKE](http://hsin.hr/coci/archive/2009_2010/contest4_tasks.pdf)」**

安娜有几个同学过来吃可丽饼，然而安娜忘了这事。当安娜发现时，留给她烤可丽饼的时间只剩下 $T$ 分钟了。她马上跑出去采购四样原材料：面粉 `B`，鸡蛋 `J`，牛奶 `M` 和果酱 `P`。

安娜周边有 $N$ 个路口，编号为 $1\ldots N$，还有 $M$ 条单向道路连接它们。已知每条路上的商店会卖哪些材料，保证每条路上的商店至少会卖（上述四种材料中）的一种。


![](https://cdn.luogu.com.cn/upload/image_hosting/dy9d4iw5.png)

安娜穿过一条道路时，如果她进入了这条路上的商店买东西，则她通过这条路耗时  $2$ 分钟，否则耗时  $1$ 分钟。即使她买完了所有原材料仍可以进店买东西。

安娜需要从 $1$ 开始，最终回到 $1$。

安娜需要在 $T$ 分钟内采购到四种原材料。请问她有多少种「采购方式」，答案对 $5557$ 取模。采购方式包含了她经过的结点的次序，以及她在每条路上买不买材料，但不计她在哪个商店买了什么。例如，当 $T=7$ 时，在上图中有 $5$ 种采购方式：

![](https://cdn.luogu.com.cn/upload/image_hosting/ug3bvehg.png)

## 说明/提示

$1\le N\le 25,$ $1\le M\le 500,$ $1\le T\le 10^9$.  
保证没有两条单向道路相同（但可能有两条连接的结点相同，而方向相反的道路）。

## 样例 #1

### 输入

```
3 3
1 2 BMJ
2 3 MJP
3 1 JPB
5```

### 输出

```
3```

## 样例 #2

### 输入

```
3 4
1 2 B
2 1 P
1 3 J
3 1 M
8```

### 输出

```
2```

## 样例 #3

### 输入

```
5 7
1 2 B
2 4 M
1 3 J
3 4 MB
4 1 JP
4 5 J
5 1 P
7```

### 输出

```
5```

# 题解

## 作者：allenchoi (赞：12)

## 前言：  
在写这道题的时候踩了一个大坑，题目要求要在第 $T$ 分钟或以前回到 $1$ 号店，而不是恰好在第 $T$ 分钟。  
虽然 [yukimianyan](https://www.luogu.com.cn/user/509229) 大佬的题解思路写的已经非常清楚了，但我觉得代码有一点看不懂，于是决定用相同的思路再写一篇。  
## 科技：  
矩阵乘法、快速幂  
## 思路：  
首先不考虑买食材的限制，设 $dp_{x,y}$ 为第 $y$ 秒在 $x$ 号节点的方案数。  
则有：  
$\begin{cases}
dp_{x,0}=[x=1]\\
dp_{x,1}=[(1,x,w)\in E]\\
dp_{x,y}=\sum_{(u,x,w)\in E}dp_{u,y-1}+dp_{u,y-2}(y>1)
\end{cases}$  
而看到 $N\le25,T\le10^9$ 的范围，就很容易想到矩阵快速幂。  
首先一个 $1\times(2n+1)$ 的矩阵 $T_i$ 表示：  
$[dp_{1,i-1},dp_{2,i-1}...dp_{n,i-1},dp_{1,i},dp_{2,i}...dp_{n,i},ans]$ 的矩阵。  
再设计用于转移的 $(2n+1)\times(2n+1)$ 的矩阵 $base$ （ $T_i=T_{i-1}\times base$ ）。  
其中，对于前 $i(i\le n)$ 列，矩阵中 第 $i+n$ 行为 $1$ ，其余均为 $0$ ，用于更新 $dp_{x,i-1}$ 的值（改为原 $dp_{x,i}$ ）。  
对于所有的边 $(u,v,w)\in E$ ，应将矩阵中的第 $u+n$ 行，第 $v+n$ 列标为 $1$ (用 $dp_{u,i-1}$ 更新 $dp_{v,i}$ )。  
第 $2n+1$ 列的第 $n+1$ 行和第 $2n+1$ 行标为 $1$ ，其余为 $0$ （ $ans$ 加上 $dp_{1,i-1}$ ）。  
但是我们发现，转移时并没有利用到 $dp_{u,i-2}$ ，肯定有问题（没有考虑到要买全食材）。  
用容斥原理解决这个问题：  
设 $F_S$ 表示只能买集合 $S$ 内物品（不能买 $S$ 以外的物品）且最终回到一方案总数，则答案为：  
$F_{\begin{Bmatrix}B,J,M,P\end{Bmatrix}}$  
$-F_{{\begin{Bmatrix}B,J,M\end{Bmatrix}}}-F_{{\begin{Bmatrix}B,J,P\end{Bmatrix}}}-F_{{\begin{Bmatrix}B,M,P\end{Bmatrix}}}-F_{{\begin{Bmatrix}J,M,P\end{Bmatrix}}}$  
$+F_{{\begin{Bmatrix}B,J\end{Bmatrix}}}+F_{{\begin{Bmatrix}B,M\end{Bmatrix}}}+F_{{\begin{Bmatrix}B,P\end{Bmatrix}}}+F_{{\begin{Bmatrix}J,M\end{Bmatrix}}}+F_{{\begin{Bmatrix}J,P\end{Bmatrix}}}+F_{{\begin{Bmatrix}M,P\end{Bmatrix}}}$    
$-F_{{\begin{Bmatrix}B\end{Bmatrix}}}-F_{{\begin{Bmatrix}J\end{Bmatrix}}}-F_{{\begin{Bmatrix}M\end{Bmatrix}}}-F_{{\begin{Bmatrix}P\end{Bmatrix}}}$   
$+F_\varnothing$  
枚举集合 $S$ 。  
则此时的 $base$ 矩阵中，对于所有的边 $(u,v,w)\in E\land w\subseteq S$ ，第 $u$ 行第 $v+n$ 列标为 $1$ 。  
最后由矩阵乘法的结合律可知：  
$F_S=T_1\times {base_S}^T$  
时间复杂度 $O(2^k\times \log T \times N^3)$
## 代码：  
~~~cpp
//建议定义新矩阵时将其数组无脑memset 防止出错
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 30,M = 510,mod = 5557;
int n,m,T,l,a,b,c,ans,bx[410];
string s;
struct edge{int u,v,w;} g[M];
struct matrix{int n,m,s[N << 1][N << 1];} bgn,base,tmp;
matrix operator *(matrix x,matrix y)
{
	matrix ret;
	ret.n = x.n,ret.m = y.m;
	memset(ret.s,0,sizeof(ret.s));
	for(int i = 1;i <= x.n;i++)
		for(int j = 1;j <= y.m;j++)
			for(int k = 1;k <= x.m;k++)
				ret.s[i][j] = (ret.s[i][j] + x.s[i][k] * y.s[k][j] % mod) % mod;
	return ret;
}
int popcount(int x)
{
	int ret = 0;
	for(int i = 1;i <= 8;i <<= 1) if(x & i) ret++;
	return ret;
}
int v()
{
	int ret = 0;
	l = s.length();
	for(int i = 0;i < l;i++) ret |= bx[s[i]];
	return ret;
}
void init(int s)
{
	memset(base.s,0,sizeof(base.s));
	base.s[n + 1][2 * n + 1] = base.s[2 * n + 1][2 * n + 1] = 1;
	for(int i = 1;i <= n;i++) base.s[i + n][i] = 1;
	for(int i = 1;i <= m;i++)
	{
		base.s[g[i].u + n][g[i].v + n] = 1;
		if((g[i].w & s) == g[i].w) base.s[g[i].u][g[i].v + n] = 1;
	}
}
matrix ksm(matrix x,int y)
{
	matrix ret;
	ret.n = ret.m = 2 * n;
	memset(ret.s,0,sizeof(ret.s));
	for(int i = 1;i <= 2 * n;i++) ret.s[i][i] = 1;
	while(y)
	{
		if(y & 1) ret = ret * x;
		x = x * x;
		y >>= 1;
	}
	return ret;
}
//BJMP
int main()
{
//	freopen("data.in","r",stdin);
	bx['B'] = 1,bx['J'] = 2,bx['M'] = 4,bx['P'] = 8;
	cin >> n >> m;
	for(int i = 1;i <= m;i++)
	{
		cin >> a >> b >> s;
		c = v();
		g[i] = (edge){a,b,c};
	}
	cin >> T;
   //bgn就是T1
	memset(bgn.s,0,sizeof(bgn.s));
	bgn.n = 1,bgn.m = base.n = base.m = 2 * n + 1;
	bgn.s[1][1] = 1;
	for(int i = 1;i <= m;i++) if(g[i].u == 1) bgn.s[1][g[i].v + n] = 1;
	for(int i = 15;i >= 0;i--)
	{
		init(i);
		tmp = bgn * ksm(base,T);
		a = tmp.s[1][n * 2 + 1];
		if(popcount(i) & 1) ans = (ans - a + mod) % mod;
		else ans = (ans + a) % mod;
	}
	cout << ans << endl;
	return 0;
}
~~~

---

## 作者：ran_qwq (赞：11)

## Part 1 朴素 dp

设 $dp_{u,i,s}$ 为走到第 $u$ 个点，一共走了 $i$ 步，目前买到的原材料状态为 $s$ 的方案数。设有一条 $u$ 到 $v$ 的边，且这条边上能买到状态 $t$，状态转移方程如下：

$$dp_{v,i+1,s\cup t}\leftarrow dp_{v,i+1,s\cup t}+dp_{u,i,s}$$

答案是 $\sum\limits_{i=1}^Tdp_{1,i,15}$。

时间复杂度 $O((N+M)T)$，带 $16$ 倍常数。

## Part 2 矩阵加速图上 dp

前置知识：[矩阵乘法 & 矩阵快速幂](https://oi-wiki.org/math/linear-algebra/matrix/#%E7%9F%A9%E9%98%B5%E4%B9%98%E6%B3%95)。

先考虑一个问题：

> 一张 $N$ 个点的有向图，求从 $1$ 开始走恰好 $T$ 条边，回到 $1$ 的方案数。其中 $N\le25,T\le10^9$。

这个问题相当于跑 $T$ 遍 floyd。而 floyd 的转移方程和矩阵乘法极其相似，都是枚举中间点 $k$，由 $i$ 通过 $k$ 转移到 $j$ 的形式。

设 $f_i$ 为走了 $i$ 条边的矩阵，则 $f_i=f_{i-1}\cdot f_1$（走了 $i-1$ 步，再走一步）。即 $f_T=f_1^T$。

答案是 $f_{T,1,1}$。这个类似整数 $a$ 的 $b$ 次方的形式，可以用快速幂优化。

## Part 3 如何建边

本题与 Part 2 的问题相比，复杂了不少地方，包括：

1. 不是恰好走 $T$ 条边，而是小于等于 $T$ 条边。

这个好办。矩阵加速图上问题如果可以停留，需要建一个自环。在这里只有在点 $1$ 能停留，就在点 $1$ 建一个自环，这是 [可乐](https://www.luogu.com.cn/problem/P3758) 的 trick。

然而需要保证走了这个自环不能再走出去买东西，需要新建一个 $0$ 号点，让 $1$ 连向 $0$，并且 $0$ 建自环，同时 $T$ 要加一（需要另外从 $1$ 走到 $0$）。

2. 经过一条边可以额外用 $1$ 个单位时间买东西，也可以不买东西。

参见 [迷路](https://www.luogu.com.cn/problem/P4159) 的 trick，如果有权值 $W$ 大于 $1$ 的边，则将一个点分为 $W$ 份，设原图第 $i$ 个点分成的第 $j$ 份为 $V_{i,j}$。则 $V_{i,j}$ 向 $V_{i,j+1}$ 连边（$j<W$）；设原图上 $x$ 到 $y$ 有一条边权为 $z$ 的边，则 $V_{x,z}$ 向 $V_{y,1}$ 连边。

本题中 $W=2$，将点分为两份，按照上述连边过程连。

3. 朴素 dp 中还有一维当前状态维。

一个较蠢的方法是：将一个点继续分为 $16$ 份，代表当前买到的不同原材料状态。但这样点数就达到惊人的 $801$，一次矩阵乘法评测机直接原地炸裂（有模运算，常数巨大）。

考虑容斥，即计算只考虑某个集合的原材料的答案。设 $g_s$ 为只考虑集合 $s$ 的原材料的答案，计算时只连只包含 $s$ 集合的边（该边的原材料是 $s$ 的子集）。

最终答案是 $\sum\limits_{s=0}^{15}g_s\cdot(-1)^{|s|}$。

---

## 作者：takanashi_mifuru (赞：7)

题目答案要求四个原材料全部拿到手，一看发现不会做，于是再考虑正难则反，考虑求出总方案数和不合法方案数减一下得到合法方案数。

总方案数很好求，就是求出安娜在图上瞎几把乱走的方案数。

我们先设状态 $dp_{t,u}$ 表示第 $t$ 个时刻人在点 $u$ 的方案数，边界条件是 $dp_{0,1}=1$，很容易根据题目推出大致转移方程 $dp_{t,v}=dp_{t-1,u}+dp_{t-2,u}$，其中要求 $u$ 有边指向 $v$，最后回到点 $1$ 的总方案数就是所有 $dp_{t,1}$ 的和。

再考虑不合法方案数，我们发现不合法方案数是有条件的，即我指定的不能买的元素是不能买的，那好办，我们在转移的时候判一下边上的元素是否满足我钦点的条件，如果不满足那就只将他直接走过来的方案 $dp_{t-=1,u}$ 记录，这样就能计算。

这样的话时间复杂度是 $O((n+m)T)$ 的，发现 $T$ 很大，考虑矩阵优化递推。

设置一个大小为 $1\times (2n+1)$ 的起始矩阵 $st=\begin{bmatrix}dp_{t-1,1},dp_{t-1,2}\dots dp_{t-1,n},dp_{t,1},dp_{t,2},\dots dp_{t-1,n},ans\end{bmatrix}$，其中 $ans$ 就是所有 $dp_{t,1}$ 的和。

考虑设计矩阵 $S$，大小为 $(2n+1)\times(2n+1)$，先考虑怎么更新 $ans$，最右下角 $((2n+1),(2n+1))$的位置放上 $1$ 表示继承上一次的 $ans$，再在 $((n+1),(2n+1))$ 放上 $1$ 表示拿走 $dp_{t,1}$，然后最底下一行最右边一列除了这两个位置全部排上 $0$。

然后就是左上大小为 $2n\times 2n$ 的矩阵，考虑剖成 $4$ 块 $n\times n$ 的矩阵，左边 $n$ 列的两个小块需要把 $dp_{t,u}$ 全部搬到前面去，所以左上角第一小块全 $0$，而左下角则是单位矩阵。

再考虑右边两个小块，这是要更新 $dp_{t+1,u}$，对于 $dp_{t,u}$，只要有连边肯定能往 $dp_{t+1,v}$ 更新，这样的关系我们发现就是邻接矩阵，所以右下角原封不动塞上邻接矩阵，而 $dp_{t-1,u}$，我们发现如果 $u$ 有边指向 $v$ 并且这条边上的材料不包含我开头就踹出去的材料那么这条边就是可以选的，我们把可以选的边选出来之后丢进邻接矩阵再丢进右上角的矩阵里就可以了。

这样就能够以高贵的 $O(n^3\log T)$ 的时间复杂度薄纱此题。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,T;
int ljb[30][30];//BJMP四位
const int P=5557; 
const int siz=51;
int change(char c){
	switch(c){
		case 'B':{
			return 1<<0;
			break;
		}
		case 'J':{
			return 1<<1;
			break;
		}
		case 'M':{
			return 1<<2;
			break;
		}
		case 'P':{
			return 1<<3;
			break;
		}
	}
}
struct Matrix{
	int a[siz][siz];
	void init(){
		for(int i=0;i<siz;i++){
			for(int j=0;j<siz;j++){
				a[i][j]=0;
			}
		}
		return;
	}
	Matrix operator * (const Matrix &b)const{
		Matrix tmp;
		for(int i=0;i<siz;i++){
			for(int j=0;j<siz;j++){
				tmp.a[j][i]=0;
				for(int k=0;k<siz;k++){
					tmp.a[j][i]+=a[k][i]*b.a[j][k]%P;
					tmp.a[j][i]%=P;
				}
			}
		}
		return tmp;
	}
};
Matrix tmp;
Matrix x;
Matrix power(int y){
	if(y==1)return x;
	tmp=power(y>>1);
	if(y&1)return tmp*tmp*x;
	else return tmp*tmp;
}
Matrix st;
int solve(int opt){
	st.init();
	st.a[0][n+n]=1;
	st.a[0][0]=1;
	for(int i=2;i<=n;i++){
		if(ljb[1][i]){
			st.a[0][i+n-1]=1;
		}
	}
	x.init();
	for(int i=n;i<n+n;i++){
		x.a[i][i-n]=1;
	}
	for(int i=n;i<n+n;i++){
		for(int j=n;j<n+n;j++){
			if(ljb[i-n+1][j-n+1])x.a[i][j]=1; 
		}
	}
	for(int i=0;i<n;i++){
		for(int j=n;j<n+n;j++){
			if(ljb[i+1][j-n+1]&&!(ljb[i+1][j-n+1]&opt))x.a[i][j]=1;
		}
	}
	x.a[n+n][n+n]=1;
	x.a[n][n+n]=1;
	if(T>1){
		st=power(T-1)*st;
	}
	return (st.a[0][n+n]+st.a[0][n])%P;
}
int Pn(int x){
	int num=0;
	while(x){
		if(x&1)num++;
		x>>=1;
	}
	if(num&1)return -1;
	return 1;
}
int main(){
	scanf("%d%d",&n,&m);	
	for(int i=1;i<=m;i++){
		int u,v;
		string S;
		scanf("%d%d",&u,&v);
		cin>>S;
		for(int i=0;i<S.size();i++){
			ljb[u][v]+=change(S[i]);
		}
	}
	scanf("%d",&T);
	int ans=0;
	for(int i=0;i<16;i++){
		ans+=solve(i)*Pn(i);
	}
	ans%=P;ans+=P;ans%=P;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：ottora (赞：7)

考虑以下的经典模型：

> 给定一张 $n$ 个点、$m$ 条边的有向连通图，边权都为 $1$，求 $a,b$ 两点之间距离为 $t$ 的路径条数（不可在某一点逗留，$n\le25,m\le500,t\le10^9$）。

$t$ 很大，自然想到倍增；而 $n$ 又很小，不妨记矩阵 $\boldsymbol F\left(x\right)$ 表示答案，其中 $\boldsymbol F_{ij}\left(x\right)$ 代表 $t=x$ 时第 $i$ 个结点到第 $j$ 个结点的路径条数。为了实现倍增，思考 $\boldsymbol F\left(x\right)$ 的递推式：枚举中间节点 $k$ 得： $\boldsymbol F_{ij}\left(x_1+x_2\right)=\sum_{k=1}^n\boldsymbol F_{ik}\left(x_1\right)\boldsymbol F_{kj}\left(x_2\right)$。而这恰好就是矩阵乘法 $\boldsymbol F\left(x_1+x_2\right)=\boldsymbol F\left(x_1\right)\boldsymbol F\left(x_2\right)$ 的定义，所以答案即为 $\boldsymbol F_{ab}\left(t\right)=\left[\boldsymbol F^t\left(1\right)\right]_{ab}$，而 $\boldsymbol F\left(1\right)$ 在构图时即可求。于是可以用矩阵快速幂，时间复杂度即为 $O\left(n^3\log t\right)$。

---

本题还需考虑以下细节：

- 图中存在边权为 $2$ 的边。

  我们可以每条边都新增一个虚拟结点过渡，但是 $m$ 太大了，最好是将每个结点都配上一个对应的虚拟结点。例如边 $i\overset2\to j$ 可以拆成 $i\overset1\to\left(i+n\right)\overset1\to j$。

- 可以回到结点 $1$ 后一直逗留。

  因为结点 $1\sim2n$ 已经用过了，可以令结点 $\left(2n+1\right)$ 统计答案。那么只需要新增两条边 $1\overset1\to\left(2n+1\right)$（新的答案汇入）和 $\left(2n+1\right)\overset1\to\left(2n+1\right)$（旧的答案累加），就得到 $\boldsymbol F_{1\left(2n+1\right)}\left(t+1\right)=\sum_{k=0}^t\boldsymbol F_{11}\left(k\right)$。

- 需要进店买东西。

  如果将每个结点分裂为 $2^4=16$ 个结点分别表示每一种状态的话，复杂度将会变为 $O\left(2^{3k}n^3\log t\right)$（其中 $k=4$ 表示物品数），这显然太大了。若考虑容斥，假设至少购买某单个物品的路径集合分别为 $A_1,A_2,A_3,A_4$， 不购买任意物品的路径集合为 $A_0$，由容斥原理：
  $$
  \left|\bigcap_{i=1}^4A_i\right|=\left|\bigcup_{i=1}^4\overline{A_i}\right|=\sum_{k=1}^4\left(-1\right)^k\sum_{1\le i_1<i_2<\cdots<i_k\le n}\left|\overline{A_{i_1}}\cap \overline{A_{i_2}}\cap\cdots\cap \overline{A_{i_k}}\right|
  $$
  此时左边 $\left|\bigcap_{i=1}^4A_i\right|$ 即为答案。容易看出 $\left|\overline{A_{i_1}}\cap \overline{A_{i_2}}\cap\cdots\cap \overline{A_{i_k}}\right|$ 表示 $i_1,i_2,\cdots,i_k$ 这些物品都不买的方案数，也就是建图时将包含这些物品的边删去即可，时间复杂度降为 $O\left(2^k n^3\log t\right)$。

  代码中是计算：
  $$
  \left|\bigcap_{i=1}^4A_i\right|=\sum_{k=1}^4\left(-1\right)^{n-k}\sum_{1\le i_1<i_2<\cdots<i_k\le n}\left|A_0\cup A_{i_1}\cup A_{i_2}\cup\cdots\cup A_{i_k}\right|
  $$
  实际上两个式子是等价的，可以用二项式反演的组合意义证明。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxm=505;
const int maxn=55;
const int P=5557;
int N,M,T,Ans,L[maxm],R[maxm],X[maxm];
struct graph{
	int n,ans[maxn][maxn];
	graph(){clear();}
	void setNodeNumber(int n_){n=n_;}
	void addEdge(int l,int r){ans[l][r]=(ans[l][r]+1)%P;}
	void init(int n_){setNodeNumber(n_);for(int i=1;i<=n;i++)ans[i][i]=1;}
	void clear(){n=0;memset(ans,0x00,sizeof ans);}
	void operator*=(const graph B){
		graph C;C.n=n;
		for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			C.ans[i][j]=(C.ans[i][j]+ans[i][k]*B.ans[k][j]%P)%P;
		*this=C;
	}
	void operator^=(const int B){
		graph w=*this,ret;ret.init(n);
		for(int k=B;k;k>>=1){if(k&1) ret*=w;w*=w;}
		*this=ret;
	}
	int getAns(int s,int t){return ans[s][t];}
}Map;
int read(){
	int f=1,ret=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f; ch=getchar();}
	while( isdigit(ch)) ret=(ret<<3)+(ret<<1)+(ch&15),ch=getchar();
	return f*ret;
}
int countTrueBinary(int x){
	int ret=0;
	for(int k=0;k<0x20;k++) if(x&1<<k) ret++;
	return ret;
} 
int main(){
	N=read(),M=read();
	for(int i=1;i<=M;i++){
		L[i]=read(),R[i]=read();string s;cin>>s;
		for(int j=0;j<s.size();j++) switch(s[j]){
			case'B':X[i]|=0x08;break;
			case'J':X[i]|=0x04;break;
			case'M':X[i]|=0x02;break;
			case'P':X[i]|=0x01;break;
		}
	}
	T=read();
	for(int k=0;k<0x10;k++){
		Map.clear();
		Map.setNodeNumber(N<<1|1);
		Map.addEdge(     1,N<<1|1);
		Map.addEdge(N<<1|1,N<<1|1);
		for(int i=1;i<=N;i++) Map.addEdge(i,i+N);
		for(int i=1;i<=M;i++) Map.addEdge(L[i],R[i]);
		for(int i=1;i<=M;i++) if((X[i]&k)==X[i]) Map.addEdge(L[i]+N,R[i]);
		Map^=T+1;
		if(countTrueBinary(k)&1) Ans=((Ans-Map.getAns(1,N<<1|1))%P+P)%P;
		else                     Ans= (Ans+Map.getAns(1,N<<1|1))%P     ;
	}
	printf("%d\n",Ans);
	return 0;
}
```



---

## 作者：yukimianyan (赞：7)

做法：矩阵优化 DP + 容斥原理。

## 矩阵优化 DP
先不要考虑商品，写个不管约束条件的 DP。令 $f_{t,u}$ 表示在 $t$ 时刻安娜在结点 $u$ 上的方案数。初始时有 $f_{0,1}=1,f_{0,u\neq 1}=0$。考虑转移，如果存在一条单向边 $(u,v)$，则我们能用 1 分钟（不买东西）或者 2 分钟（买东西）经过它，则

$$f_{t,v}=\sum\limits_{(u,v)\in E}{(f_{t-1,u}+f_{t-2,u})}$$

这就是朴素的 DP。发现奇妙的 $N\leq 25,T\leq 10^9$，套路地想到矩阵乘法。这里的 DP 需要用到 $t-1$ 和 $t-2$ 两个时刻，因此矩阵至少要存下前两个时刻的 DP 值。题目要求至少 $t$ 分钟内回到 $1$ 的答案，因此我们还需要一个 $ans$ 记录。我们可以构造这样的矩阵：

$$
I_t=\begin{bmatrix}
f_{t-1,1},f_{t-1,2},\cdots,f_{t-1,n},f_{t,1},f_{t,2},\cdots,f_{t,n},ans
\end{bmatrix}
$$

表示 $t$ 时刻的 DP 值，我们希望找到一个方阵 $X$ 使 $I_tX=I_{t+1}$。

首先把 $I_{t,1,n+1\sim2n}$ 的值转移到 $I_{t+1,1,1\sim n}$，这部分值不变都是 $f_t$，在 $X$ 的"左下角"填一排对角线 $1$。

然后我们要推 $f_{t+1}$ 的 DP 值，它依赖于 $f_t,f_{t-1}$（务必区分 $f_t,f_{t-1}$ 转移的含义，$f_t$ 是直接经过商店不买东西，$f_{t-1}$ 是进入商店买东西），如果存在一条边 $(u,v)\in E$，就将 $X_{u,v+n},X_{u+n,v+n}$ 的值加一，使它转移。给一个具体的例子，感性理解一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/sqwe3jy6.png)

（关于如何想出这一个矩阵，个人理解是把矩阵乘法结果中第 $i$ 行第 $j$ 列看作是，$a$ 矩阵的第 $i$ 行顺时针旋转 $90^\circ$，与 $b$ 矩阵的第 $j$ 列，重合在一起，算乘法的和。这样的方式可能能帮助你理解。）

还有一个 $ans$，我们在最右下角 $X_{2n+1,2n+1}$ 放一个 $1$（可以理解为继承上一次），再在 $X_{n+1,2n+1}$ 放一个 $1$（可以理解为加上 $f_{t,1}$ 的方案数）。于是我们有了 $I_tX=I_{t+1}$，快速幂优化 $I_1X^t=I_{t+1}$ 的转移即可。

## 容斥原理
回归题目，它要我们求出四种商品全买的方案数。直接求不好做，考虑合法方案数 + 不合法方案数 = 总方案数，总方案数显然是安娜在图上随便走的方案数，所以第一步把题意转化成不合法方案数。

令 $B,J,M,P$ 分别为强制不买 B,J,M,P 的方案数，不合法的方案数就是 $|B\cup J\cup M\cup P|$，发现这是个容斥原理，那么有 

$$\begin{aligned}
|B\cup J\cup M\cup P|&=|B|+|J|+|M|+|P|\\
&-|B\cap J|-|B\cap M|-|B\cap P|-|J\cap M|-|J\cap P|-|M\cap P|\\
&+|B\cap J\cap M|+|B\cap M\cap P|+|B\cap J\cap P|+|B\cap J\cap M|\\
&+|B\cap J\cap M\cap P|.
\end{aligned}$$

由于这是 $\cap$（交），把它理解成 $\land$（并），我们对于这当中的每个集合，强制不买那些商品（但是可以经过有那些商品的店而不进去买），按照上文的矩阵优化递推出合法方案数，最后就能得到我们想要的不合法的方案数。
## 实现
- 判断二进制数 $t,s$ 在子集意义下是否有 $t\subseteq s$，可以用 `(~s&t)==0` 实现。
- 构造 $I_1$ 矩阵时暴力计算 $f_{1,u}$ 的方案数。
- 观察到这题模数很小，那么矩阵可以开 `int`，算完一个值统一取模，以减少常数（需要跑 $16$ 次矩阵快速幂）。
- 务必搞清楚容斥系数！

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
int popcount(int x){return (x&1)+(x>>1&1)+(x>>2&1)+(x>>3&1);}
const int P=5557; 
template<int N,int M,class T=int> struct graph{
    int head[N+10],nxt[M*2+10],cnt;
    struct edge{
        int u,v;T w;
        edge(int u=0,int v=0,T w=0):u(u),v(v),w(w){}
    } e[M*2+10];
    graph(){memset(head,cnt=0,sizeof head);}
    edge operator[](int i){return e[i];}
    void add(int u,int v,T w=0){e[++cnt]=edge(u,v,w),nxt[cnt]=head[u],head[u]=cnt;}
    void link(int u,int v,T w=0){add(u,v,w),add(v,u,w);}
};
template<int N,int M,class T=LL> struct matrix{
	T a[N+3][M+3];
	matrix(bool f=0){
		memset(a,0,sizeof a);
		if(f) for(int i=1;i<=N;i++) a[i][i]=1;
	}
	T* operator[](int i){return a[i];}
	void print(int n,int m){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				printf("%d%c",a[i][j]," \n"[j==m]);
			}
		}	
	}
};
template<int N,int M,int R,class T=LL> matrix<N,R,T> operator*(matrix<N,M,T> a,matrix<M,R,T> b){
	matrix<N,R,T> c=0;
	for(int i=1;i<=N;i++){
		for(int j=1;j<=R;j++){
			for(int k=1;k<=M;k++){
				c[i][j]+=a[i][k]*b[k][j];
			}
			c[i][j]%=P;
		}
	}
	return c;
}
template<int N,class T=LL> matrix<N,N,T> operator^(matrix<N,N,T> a,LL b){
	matrix<N,N,T> ans=1;
	for(;b;b>>=1,a=a*a) if(b&1) ans=ans*a;
	return ans;
}
int n,m,t,tb[128];
char buf[110];
graph<30,510,int> g;
matrix<60,60,int> o;
matrix<1,60,int> e;
int has(char *s){int res=0;for(int i=1,len=strlen(s+1);i<=len;i++) res+=tb[s[i]];return res;}
void binprt(int x){for(int i=3;i>=0;i--) putchar((x>>i&1)+'0');}
int solve(int sta){
	o=0,e=0;
	e[1][1]=1,o[n*2+1][n*2+1]=o[n+1][n*2+1]=1;//e={0,1}
	for(int i=1;i<=n;i++) o[i+n][i]=1;
	for(int i=1;i<=g.cnt;i++){
		//(u,v)=>f[n][u]=f[n-1][v]+f[n-2][v]
		int u=g[i].u,v=g[i].v;
		o[u+n][v+n]++;
		if(u==1) e[1][v+n]++;
		if((~sta&g[i].w)==0) o[u][v+n]++;
	}
	return (e*(o^t))[1][n*2+1];
}
int main(){
//	#ifdef LOCAL
//	 	freopen("input.in","r",stdin);
//	#endif
	tb['B']=1,tb['J']=2,tb['M']=4,tb['P']=8;
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++) scanf("%d%d%s",&u,&v,buf+1),g.add(u,v,has(buf));
	scanf("%d",&t);
	int all=solve(15),res=0;
	for(int i=1;i<=15;i++) res+=solve(15-i)*(popcount(i)&1?1:-1);//,printf("ban=%d,ans%c=%d\n",i,"-+"[popcount(i)&1],solve(15-i));
//	printf("all=%d,res=%d\n",all,res);
	printf("%d\n",((all-res)%P+P)%P);
	return 0;
}
/*
t in s => ~s&t==0
*/
```
复杂度：$O(2^kn^3\log T)$，其中 $k=4$ 为商品种类数。

---

## 作者：CmsMartin (赞：7)

## 题目描述

[题目传送门](https://www.luogu.com.cn/problem/P5188)

## 思路

发现 $T \le 10^9$ 很大，要么倍增要么数学要么矩阵优化。

第二者显然不可取，在这里我们考虑矩阵优化。

题目的限制必须买四样东西是比较麻烦的，然而不能买其中的几样东西是简单的。考虑容斥。

设 $F_{S}$ 表示只能买 $S$ 内的物品（不一定要全买）然后就可以容斥求。

设 $f_{i,j}$ 表示第 $j$ 秒在第 $i$ 个节点的方案数。

则可以构造初始矩阵:

$$\mathbf{A} = [f_{1,0},f_{2,0},\dots,f_{n,0},f_{1,1},f_{2,1},\dots,f_{n,1}]$$


然后可以平凡的转移。

对于每一种情况，将包含 $S$ 的边设为 $E_S$

$$
f_{i,j} = \sum_{(u,v,w) \in E_{S}} f_{i,j - 1} + f_{i,j - 2}
$$

构造矩阵。

然后就做完了。

---

## 作者：XuYueming (赞：6)

## 前言

题目链接：[洛谷](https://www.luogu.com.cn/problem/P5188)。

[更好的体验](https://www.cnblogs.com/XuYueming/p/18387610)。

## 题意简述

$n$ 个点，$m$ 条边。每条边上有商店，经过一条边花费 $1$ 单位时间，如果在边上的商店购物，额外花费 $1$ 单位时间。需要购买 $4$ 种物品，每个商店售出 $1 \sim 4$ 种物品不等。请问，在 $T$ 个单位时间内，从 $1$ 出发购物，得到这 $4$ 种物品，并回到 $1$ 的方案数，对 $5557$ 取模。你在购完并回到 $1$ 后可以立即停止，不能在其他点逗留。

$n \leq 25$，$m \leq 500$，$T \leq 10^9$。

## 题目分析

四种物品很少，想到使用状压 DP。记 $f_{i, u, \mathcal{S}}$ 表示经过了 $i$ 个单位时间，现在在 $u$，目前购买了的物品集合为 $\mathcal{S}$，的方案数。初始状态 $f_{0, 1, \varnothing} = 1$，答案即为 $\sum \limits _ {i = 0} ^ T f_{i, 1, \{1, 2, 3, 4\}}$。

转移其实不难，对于 $(u, v, S')$ 这条边，枚举是否进行购买即可。

1. 不购买
    $$
    f_{i + 1, v, S} \gets f_{i, u, S}
    $$
1. 购买
    $$
    f_{i + 2, v, S \cup S'} \gets f_{i, u, S}
    $$

其中 $a \gets b$ 表示将 $b$ 累加到 $a$ 上。

直接做是 $\Theta(2^{|S|}T(n + m))$，$T$ 很大，肯定超时。转移这么简单，考虑使用矩阵快速幂优化。

由于 $f_{i}$ 需要用到 $f_{i - 1}$ 和 $f_{i - 2}$，并且需要额外记录 $ans$，所以我们转移是从 $\displaystyle \begin{bmatrix} f_{i - 2} & f_{i - 1} & ans \end{bmatrix}$ 转移到 $\displaystyle \begin{bmatrix} f_{i - 1} & f_{i} & ans' \end{bmatrix}$。

考虑构造转移矩阵，注意到，把状态 $\lambda$ 的值乘上 $k$ 累加到 $\varphi$，相当于在转移矩阵的第 $\lambda$ 行，第 $\varphi$ 列累加一个 $k$。（采用转移矩阵放置在左边的形式。）当然，我们这里所有 $k = 1$。这一部分预处理是简单的。考虑什么时候累加答案。发现，如果 $v = 1$，并且目标状态 $S$ 或者 $S \cup S'$ 是全集，不光要累加到 $f$ 上，也要累加到 $ans$ 上。$f_{i - 1}$ 放到答案矩阵左侧这一步，可以在转移矩阵中套一个单位矩阵。

$$
\begin{gathered}
{\large
\left [
\begin{array}{ccc:ccc:c}
f_{i-2, 1, \varnothing} & \cdots & f_{i-2, n, \{1, 2, 3, 4\}} & f_{i-1, 1, \varnothing} & \cdots & f_{i-1, n, \{1, 2, 3, 4\}} & ans \\
\end{array}
\right ]}

\\

{\Huge \times}

\\
{\large
\left [
\begin{array}{ccc:ccc:c}
0 & \cdots & 0 & & & & \\
\vdots & \ddots & \vdots & & & & \\
0 & \cdots & 0 & & & & \\
\hdashline
1 & \cdots & 0 & & & & \\
\vdots & \ddots & \vdots & & & & \\
0 & \cdots & 1 & & & & \\
\hdashline
0 & \cdots & 0 & 0 & \cdots & 0 & 1 \\
\end{array}
\right ]}

\\

{\Huge \Downarrow}

\\

{\large
\left [
\begin{array}{ccc:ccc:c}
f_{i-1, 1, \varnothing} & \cdots & f_{i-1, n, \{1, 2, 3, 4\}} & f_{i, 1, \varnothing} & \cdots & f_{i, n, \{1, 2, 3, 4\}} & ans' \\
\end{array}
\right ]}

\end{gathered}
$$

构造转移矩阵的代码：

```cpp
// a => false: f[i-2], true: f[i-1]
inline int cal(bool a, int u, int st) {
    return (u - 1) * (1 << 4) + st + (a ? n * (1 << 4) : 0);
}

B = 2 * n * (1 << 4);  // ans 的位置
for (int u = 1; u <= n; ++u)
for (int st = 0; st < 1 << 4; ++st) {
    toadd(trans(cal(true, u, st), cal(false, u, st)), 1);  // 单位矩阵
    for (int o = xym.head[u]; o; o = xym[o].nxt) {
        int v = xym[o].to;
        toadd(trans(cal(true, u, st), cal(true, v, st)), 1);
        if (v == 1 && st == 0b1111)
            toadd(trans(cal(true, u, st), B), 1);
        toadd(trans(cal(false, u, st), cal(true, v, st | xym[o].len)), 1);
        if (v == 1 && (st | xym[o].len) == 0b1111)
            toadd(trans(cal(false, u, st), B), 1);
    }
}
toadd(trans(B, B), 1);  // 右下角 ans 累加
```

时间复杂度降到了：$\Theta\Big((n 2^{|S|})^3 \log T\Big) = \Theta(n^316^{|S|}\log T)$。还是会超时，但是能拿到 $70$pts。

考场上，我想到这里就不会做了。事实上，我们发现 $16^{|S|}$ 显然是算法瓶颈所在，在矩阵乘法立方的加持下，不能记录 $2^{|S|}$。那怎么做呢？

我们可以在一开始**钦定**某些商品不能购买，得到在「钦定意义」下的「至多」购买 $x$ 个商品的方案 $f(x)$。我们求的是「恰好」购买 $x = 4$ 个商品的方案 $g(x)$。使用二项式反演即可，参见[我的学习笔记](https://www.cnblogs.com/XuYueming/p/18397758)，适用 [$\mathtt{Thm}\ 2.1$](https://www.cnblogs.com/XuYueming/p/18397758#mjx-eqn%3Athm21)，这里给出公式：

$$
f(x) = \sum \limits _ {i = 0} ^ x \dbinom{n - i}{n - x} g(i) \Longleftrightarrow g(x) = \sum _ {i = 0} ^ x (-1)^{x - i} \binom{n - i}{n - x} f(i)
$$

至于「钦定」后怎么求出 $f(x)$，同样使用矩阵快速幂，初始化转移矩阵的时候，如果需要购买，则要保证购买的物品没有当前钦定不能买的。这次矩阵大小是 $2n + 1$，总的时间复杂度为 $\Theta(2^{|S|}n^3\log T)$。

## 代码

[$70$ 分代码](https://www.luogu.com.cn/paste/t7ii194d)。

```cpp
#include <cstdio>
#include <cstring>
#include <unordered_map>
#include <limits>
#include <iostream>
using namespace std;

const int N = 30, M = 520;

namespace Mod_Int_Class {
    // see 70 pts code
}

using namespace Mod_Int_Class;

int n, m, t, B;

struct Graph {
    struct node {
        int to, len, nxt;
    } edge[M];
    int tot = 1, head[N];
    void add(int u, int v, int w) {
        edge[++tot] = {v, w, head[u]};
        head[u] = tot;
    }
    inline node & operator [] (const int x) {
        return edge[x];
    }
} xym;

inline int cal(bool a, int u) {
    return (u - 1) + (a ? n : 0);
}

struct Matrix {
    mint val[51][51];
    mint * operator [] (const int x) {
        return val[x];
    }
    mint const * operator [] (const int x) const {
        return val[x];
    }
    mint & operator () (const int a, const int b) {
        // a 转移到 b
        return val[a][b];
    }
    Matrix() {
        memset(val, 0x00, sizeof (val));
    }
    inline Matrix friend operator * (const Matrix &a, const Matrix &b) {
        static Matrix res;
        memset(res.val, 0x00, sizeof (res.val));
        for (register int i = 0; i <= B; ++i)
        for (register int k = 0; k <= B; ++k)
        for (register int j = 0; j <= B; ++j)
            res[i][j] += a[i][k] * b[k][j];
        return res;
    }
} trans, base;

inline int calc(char c) {
    switch (c) {
        case 'B': return 0;
        case 'J': return 1;
        case 'M': return 2;
        case 'P': return 3;
        default:  return -1;
    }
}

inline mint solve(int S) {
    memset(trans.val, 0x00, sizeof (trans.val));
    memset(base.val, 0x00, sizeof (base.val));
    
    for (int u = 1; u <= n; ++u){
        ++trans(cal(true, u), cal(false, u));
        for (int o = xym.head[u]; o; o = xym[o].nxt) {
            int v = xym[o].to;
            ++trans(cal(true, u), cal(true, v));
            if (v == 1)
                ++trans(cal(true, u), B);
            if (!(xym[o].len & S)) {  // 如果没有当前钦定不能买的
                ++trans(cal(false, u), cal(true, v));
                if (v == 1)
                    ++trans(cal(false, u), B);
            }
        }
    }
    ++trans(B, B);
    base[0][cal(true, 1)] = 1;
    for (int x = t; x; trans = trans * trans, x >>= 1) {
        if (x & 1) base = base * trans;
    }
    return base[0][B];
}

mint f[4], ans;

signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; ++i) {
        static char str[8];
        scanf("%d%d%s", &u, &v, str);
        int w = 0;
        for (int j = 0; str[j]; ++j) w |= 1 << calc(str[j]);
        xym.add(u, v, w);
    }
    B = 2 * n;
    scanf("%d", &t);
    for (int st = 0; st < 1 << 4; ++st)
        f[__builtin_popcount(st)] += solve(st);
    for (int i = 0; i <= 4; ++i) {
        // C(4 - i, 4 - 4) = 1
        if ((4 - i) & 1)
            ans -= f[i];
        else
            ans += f[i];
    }
    printf("%hu", ans.raw());
    return 0;
}

```

---

## 作者：Jerrywang09 (赞：6)

一道非常好的容斥原理、矩阵题。建议难度：紫。

观察到只有 $4$ 种原料，需要全部买齐，因此可以进行容斥，所有方案先减去至少少 $1$ 种原料的方案，再加回至少少 $2$ 种原料的方案，以此类推。此过程可以使用二进制枚举哪些原料必须不选，这个状态记为 $ban$。（话说这是个老套路了。）去掉与 $ban$ 有交集的边。

> 如果两个二进制表示的集合 $s,t$ 有交集，则有 `s&t>0`（C++ 代码）。

对于这个去掉一些边的新图，计算有多少种方案，$k$ 步内能从起点 $1$ 绕回起点。如果是恰好 $k$ 步，这个问题相当简单：邻接矩阵 $k$ 次幂后 $(1,1)$ 的值。

本题求的是 $k$ 步内，需要一点转化。构造一个辅助结点编号为 $0$ 并构成自环，结点 $1$ 连向结点 $0$。这样转化过后，答案就是邻接矩阵 $k$ 次幂后 $(1,1)+(1,0)$，再 $-1$。$(1,1)$ 就是恰好 $k$ 步的答案，$(1,0)$ 是 $<k$ 步的答案，因为如果提前结束，就可以从 $1$ 走向 $0$，$0$ 构成自环也就继承了之前所有提前结束的方案。最后 $-1$ 是因为不能一上来就直接走向 $0$，相当于待在起点没有动。

```cpp
#include <bits/stdc++.h>
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define F first
#define S second
#define pii pair<ll, int>
#define ll long long
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=30, mod=5557;
using namespace std;

vector<pii> g[N];
map<char, int> mp;
int n, nn, m, t;
struct matrix
{
    int a[N+N][N+N]={0};
    matrix operator *(matrix b)
    {
        matrix c;
        rep(i, 0, nn) rep(j, 0, nn) rep(k, 0, nn)
            c.a[i][j]=(c.a[i][j]+a[i][k]*b.a[k][j]%mod)%mod;
        return c;
    }
};
matrix qp(matrix a, int b)
{
    matrix res;
    rep(i, 0, nn) res.a[i][i]=1;
    while(b)
    {
        if(b&1) res=res*a;
        a=a*a; b>>=1;
    }
    return res;
}
int calc(int ban)
{
    int a[N+N][N+N]={0};
    rep(u, 1, n)
    {
        for(pii t:g[u])
        {
            int v=t.F, w=t.S;
            a[u][v]=1;
            if(w&ban) continue; // 有交集
            a[u][u+n]=a[u+n][v]=1;
        }
    }
    a[1][0]=a[0][0]=1;
    matrix mat; memcpy(mat.a, a, sizeof a);
    mat=qp(mat, t);
    int res=(mat.a[1][1]+mat.a[1][0]-1+mod)%mod;
    return res;
}

int main()
{
    mp['J']=1; mp['B']=2; mp['M']=4; mp['P']=8;
    scanf("%d%d", &n, &m); nn=n+n;
    rep(i, 1, m)
    {
        int u, v; scanf("%d%d", &u, &v);
        string s; cin>>s;
        int st=0;
        for(char c:s) st+=mp[c];
        g[u].push_back({v, st});
    }
    scanf("%d", &t);
    int res=0;
    rep(msk, 0, 15)
    {
        int w=__builtin_popcount(msk);
        if(w&1) res=(res-calc(msk)+mod)%mod;
        else res=(res+calc(msk))%mod;
    }
    printf("%d", res);

    return 0;
}
```

---

## 作者：kyEEcccccc (赞：6)

## 题意简述：
有一张有向图 $(V, E)$，有四种物品，每条边上可能有四种物品的一个非空子集。通过一条边需要 $1$ 单位时间，收集该边上的物品需要额外的 $1$ 单位时间（即总共 $2$ 单位时间）。问在给定时间 $T$ 以内，从节点 $1$ 出发，收集所有物品至少一个，并回到节点 $1$ 的方案总数是多少。

数据范围是 $T \le 10^9, |V| \le 25, |E| \le 500$。

## 初步分析
数据范围中点数很小，而在图上行走的时间很大，很有可能涉及矩阵或多项式知识求解。

考虑经典问题：从某张图某个点出发，恰好/至多走 $K$ 步，有多少种方法最终停在特定的某个点。这个问题的解法是邻接矩阵进行快速幂（对于“至多”需要额外加一维）。

这道题目与此十分相似，但是有两点不同：首先，加入了收集物品的限制；其次，边权不一定为 $1$。所以考虑改造原先的矩阵做法来解决。

## 朴素做法
首先考虑如何处理边权为2的问题。一个显然的想法是将矩阵的长宽扩大一倍。有两种方法理解这种做法：一种是记录了 $1$ 单位或 $2$ 单位时间前的原图，进行类DP的状态转移。另一种是想象将原图每个节点复制一份，要想获得字母，就必须从原图点花 $1$ 步走到复制点，再从复制点走到另一个点。而原图点连出的边没有物品，这样就可以直接按照经典方法做。作者采取后一种理解，因为代码比较直观。

接下来考虑处理物品的限制。考虑将收集到的物品集合压缩为一个四位二进制数加入状态中。转移时，既转移点，也转移获得的物品。或者也可以理解为分层图。无论如何，这种做法的状态总数是 $\Theta((n\cdot 2^p)^3\log T)$，考虑常数以后，计算次数大概是 $(2 \times 25 \times 2^4)^3\times 30 = 1.536 \times 10^{10}$，无法获得满分。

## 优化策略
这里有一个套路。当我们注意到一道题有如下特征：1. 是要同时满足若干个条件的计数问题； 2. 若干个条件如果去掉（或者钦定不满足）以后，计数的做法不难；3. 时间复杂度是状态个数的高次（或其他增长快于线性的）函数。那么我们应当考虑容斥。容斥优化的本质是把限制所带来的贡献从高次函数中取出来，让它的贡献变成线性级别。

对于这道题，我们的做法是：钦定不取得某些物品，考虑有多少种方法在 $T$ 时间以内回到原点，那么这一部分就是上述经典问题。然后将答案容斥起来即可。

该算法时间复杂度 $\Theta(n^3 \cdot 2^p \cdot \log T)$。计算出来是 $(2\times 25)^3 \times 2^4\times30 = 6 \times 10^7$ 刚好过题。注意优化对时间复杂度的表达式有什么改变，就能理解上述的“套路”的意义。

## 实现
实现是容易的。

```cpp
// Author: kyEEcccccc

#include <bits/stdc++.h>

using namespace std;

using LL = long long;
using ULL = unsigned long long;

#define F(i, l, r) for (int i = (l); i <= (r); ++i)
#define FF(i, r, l) for (int i = (r); i >= (l); --i)
#define MAX(a, b) ((a) = max(a, b))
#define MIN(a, b) ((a) = min(a, b))

const int N = 55, P = 5557;

struct Mat
{
	int a[N][N];
};
struct Vec
{
	int a[N];
};
void mul_mat(Mat &x, Mat y, int n)
{
	Mat t = x;
	F(i, 1, n) F(j, 1, n)
	{
		x.a[i][j] = 0;
	}
	F(i, 1, n) F(j, 1, n) F(k, 1, n)
	{
		(x.a[i][j] += t.a[i][k] * y.a[k][j]) %= P;
	}
}
void mul_vec(Mat x, Vec &v, int n)
{
	Vec t = v;
	F(i, 1, n)
	{
		v.a[i] = 0;
	}
	F(i, 1, n) F(k, 1, n)
	{
		(v.a[i] += x.a[i][k] * t.a[k]) %= P;
	}
}
void pow_mat(Mat &x, int k, int n)
{
	Mat t = x;
	F(i, 1, n) F(j, 1, n)
	{
		x.a[i][j] = (i == j ? 1 : 0);
	}
	while (k)
	{
		if (k & 1)
		{
			mul_mat(x, t, n);
		}
		mul_mat(t, t, n);
		k >>= 1;
	}
}

int n, m, ti;
struct Edge
{
	int u, v, c;
};
vector<Edge> ori_e;

int solve(int t)
{
	Mat g;
	F(i, 1, 2*n+1) F(j, 1, 2*n+1)
	{
		g.a[i][j] = 0;
	}
	for (auto ee : ori_e)
	{
		if ((ee.c | t) == t)
		{
			// cout << t << ": " << ee.u << ' ' << ee.v << '\n';
			g.a[ee.u][ee.v] += 1;
		}
	}
	g.a[2*n+1][2*n+1] = 1;
	g.a[2*n+1][1] = 1;
	pow_mat(g, ti, 2*n+1);
	Vec v;
	v.a[1] = 1;
	F(i, 2, 2*n+1)
	{
		v.a[i] = 0;
	}
	mul_vec(g, v, 2*n+1);
	return (v.a[1] + v.a[2*n+1]) % P;
}

int trans(string s)
{
	int w = 0;
	if (s.find('B') != s.npos)
	{
		w |= 1;
	}
	if (s.find('M') != s.npos)
	{
		w |= 2;
	}
	if (s.find('J') != s.npos)
	{
		w |= 4;
	}
	if (s.find('P') != s.npos)
	{
		w |= 8;
	}
	return w;
}

int main(void)
{
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(nullptr);

	cin >> n >> m;
	F(i, 1, n)
	{
		ori_e.push_back({i*2-1, i*2, 0});
	}
	F(i, 1, m)
	{
		int u, v;
		string s;
		cin >> u >> v >> s;
		int w = trans(s);
		ori_e.push_back({u*2-1, v*2-1, 0});
		ori_e.push_back({u*2, v*2-1, w});
	}
	cin >> ti;

	int ans = 0;
	F(t, 0, 15)
	{
		if (__builtin_parity(15 ^ t))
		{
			ans -= solve(t);
		}
		else
		{
			ans += solve(t);
		}
	}
	cout << (ans % P + P) % P << endl;

	return 0;
}
```

用了循环宏，希望不要因此被喷。

---

## 作者：smallpeter (赞：4)

# sol
做这个题的时候输在完全没想过容斥/ll。

一个感觉比较直观的想法是设状态 $f_{T,i,S}$ 表示在 $T$ 时刻走到点 $i$ 且四种物品的获得情况为 $S$ 的方案数。然后发现 $f_{T,i,S}$ 只会从 $f_{T-1,x_1,y_1}$ 和 $f_{T-2,x_2,y_2}$ 转移过来，而 $T$ 又很大，可以考虑用矩阵来优化，式子不难就不列了。还有一个问题是要计算的是在 $T$ 秒内的方案数，而我们只能算出恰好为 $T$ 的方案数。可以考虑对图改造一下：新加一个虚拟点 $n+1$，从 1 指向这个点，这个点再指向自己，权值都设置为 16，时间要多给 1 秒。

当然这个东西是过不了的，主要问题在于矩阵大小太大了，于是我们考虑通过容斥将第三维状态省去。我们枚举一个集合 $T$ ，表示只能选择 $T$ 内的数的方案数，可得答案为 $\sum\limits_{T}calc_T\times{-1}^{4-\left|T\right|}$。再套用刚刚分析的做法就可以得到正解了。时间复杂度为 $O(Mn^3\log T)$，但是要带八倍常数。

# 代码
```
#include<bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define fi first
#define se second
#define pb push_back
#define pii pair<LL,LL>
#define mem(a,x) memset((a),(x),sizeof(a))

//#define long long int
#define LLL __int128

template<typename type>
inline void read(type &x)
{
	x=0;bool flag(0);char ch=getchar();
	while(!isdigit(ch)) flag=ch=='-',ch=getchar();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	flag?x=-x:0;
}

template<typename type>
inline void write(type x,bool mode=1)//0为空格，1为换行
{
	x<0?x=-x,putchar('-'):0;static short Stack[50],top(0);
	do Stack[++top]=x%10,x/=10; while(x);
	while(top) putchar(Stack[top--]|48);
	mode?putchar('\n'):putchar(' ');
}

LL qsm(LL a,LL b,LL mod){
	LL ans=1,sum=a;
	while(b){
		if(b&1) ans=ans*sum%mod;
		sum=sum*sum%mod;
		b>>=1;
	}
	return ans;
}

const LL N=60,M=16,mod=5557;

struct Matrix{
	LL n,m;
	LL a[N][N];
	friend Matrix operator *(const Matrix x,const Matrix y){
		Matrix nw;
		nw.n=x.n,nw.m=y.m;
		for(LL i=0;i<nw.n;i++){
			for(LL j=0;j<nw.m;j++){
				nw.a[i][j]=0;
				for(LL k=0;k<x.m;k++){
					nw.a[i][j]=(nw.a[i][j]+x.a[i][k]*y.a[k][j])%mod;
				}
			}
		}
		return nw;
	}
}init,step;

LL n,m,ti;

vector<pair<LL,LL> > g[N],g2[N];

char s[N];

map<char,LL> mp;

Matrix initx(){
	Matrix x;
	x.n=x.m=2*n;
	for(LL i=0;i<x.n;i++) for(LL j=0;j<x.m;j++) x.a[i][j]=(i==j);
	return x;
}

Matrix qsm(Matrix a,LL b){
	Matrix ans=initx();
	while(b){
		if(b&1) ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}

void solve(){
	read(n),read(m);
	for(LL i=1;i<=m;i++){
		LL u,v;
		read(u),read(v);
		scanf("%s",s+1);
		LL len=strlen(s+1);
		LL cnt=0;
		for(LL j=1;j<=len;j++) cnt+=(1<<mp[s[j]]);
		g[u].push_back({v,cnt});
		g2[v].push_back({u,cnt});
	}
	n++;
	g[1].push_back({n,M});
	g2[n].push_back({1,M});
	g[n].push_back({n,M});
	g2[n].push_back({n,M});
	read(ti);
	LL ans=0;
	for(LL S=0;S<M;S++){
		LL cnt=0;
		for(LL j=0;j<4;j++) cnt+=((S>>j)&1);
		init.n=1,init.m=2*n;
		for(LL j=0;j<2*n;j++) init.a[0][j]=0;
		init.a[0][0]=1;
		for(auto [v,w]:g[1]){
			init.a[0][v+n-1]++;
		}
		step.n=step.m=2*n;
		for(LL i=0;i<n;i++){
			for(LL j=0;j<2*n;j++) step.a[j][i]=(j==i+n);
		}
		for(LL i=n;i<2*n;i++){
			for(LL j=0;j<2*n;j++) step.a[j][i]=0;
			for(auto [v,w]:g2[i-n+1]){
				step.a[v+n-1][i]++;
				if((w&S)==w) step.a[v-1][i]++;
			}
		}
//		step.a[n][n]++;
		init=init*qsm(step,ti+1);
		ans=(ans+init.a[0][n-1]*(cnt&1?mod-1:1))%mod;
//		write(init.a[0][n-1]);
	}
	write(ans);
}

int main(){
//	freopen("cyb.in","r",stdin);
//	freopen("cyb.out","w",stdout);
	mp['B']=0;
	mp['J']=1;
	mp['M']=2;
	mp['P']=3;
	LL T=1;
//	read(T);
	while(T--){
		solve();
	}
}
```cpp

---

## 作者：封禁用户 (赞：3)

首先容易发现对于两个矩阵相乘时唯一会炸的地方就在于中间的交交界点是可以破开走两步的，举个例子：以 $f_x$ 表示走 $x$ 步时的矩阵，假如要走 $a+b$ 步，由走 $a$ 步的情况与走 $b$ 步的情况相乘合并而来也就是 $f_{a+b}=f_a \times f_b$，那么直接相乘就无法统计在 $a$ 与 $a+1$ 这两步去逛超市的情况，影响是非常大的。那么最直观的考虑就是再加上 $f_{a-1} \times f_2 \times f_{b-1}$，但是这样就会统计两次在 $(a-1,a),(a,a+1),(a+1,a+2)$ 都不逛超市的的情况，那么容易发现这种情况的次数就是 $f_{a-1} \times f_1^2 \times f_{b-1}$的答案，那么再减去这个值即可。之后就只用想去处理 $f_{a+b-1}$ 的值，首先想到 $f_{a+b-1}=f_a \times f_{b-1}$，但是还是一样没法处理 $a$ 与 $a+1$ 这两步去逛超市的情况，那么容易想到再加上 $f_{a-1} \times f_b$，也就是不考虑在 $a-1$ 与 $a$ 这两步去逛超市的情况，与 $f_{a+b}$ 类似的想法就是在减去同时不在 $(a-1,a),(a,a+1)$ 不去逛超市的情况，非常巧的发现就是 $f_{a-1} \times f_1 \times f_{b-1}$，那么减去即可。这样的做法就是以容斥的思想去处理合并时的边界情况，我觉的挺巧妙的，但是常数非常非常非常非常大，因为要乘好几次。

之后加个容斥就没了，容斥就不多说了。

上代码：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define rint register int
using namespace std;bool o1;
int n,m,a1,b1,t,p,P=5557,ANS,A[1000],B[1000],C[1000],o;
char c1[6];
struct node{
	int a[30][30];
	node(){memset(a,0,sizeof(a));}
	node operator * (const node &_) const{//矩阵乘法
		node rst;
		for(rint i=1;i<=n;i++)
			for(rint j=1;j<=n;j++)
				for(rint k=1;k<=n;k++)
					(rst.a[j][k]+=a[j][i]*_.a[i][k])%=P;
		return rst;
	}
	node operator + (const node &_) const{
	//两个矩阵相加,其实就是将每一个点的两个值相加，减法同理
		node rst;
		for(rint i=1;i<=n;i++)
			for(rint j=1;j<=n;j++)
				rst.a[i][j]=(a[i][j]+_.a[i][j])%P;
		return rst;
	}
	node operator - (const node &_) const{//矩阵减法
		node rst;
		for(rint i=1;i<=n;i++)
			for(rint j=1;j<=n;j++)
				rst.a[i][j]=(a[i][j]-_.a[i][j]+P)%P;
		return rst;
	}
}nw[35],Nw[35],ans,Ans,tmp,Tmp;
bool o2;int main(){
	scanf("%d%d",&n,&m);
	for(rint i=1;i<=m;i++){
		scanf("%d%d%s",&a1,&b1,c1);
		t=0;
		for(rint j=0;j<strlen(c1);j++){
			if(c1[j]=='B')t|=1;
			if(c1[j]=='J')t|=2;
			if(c1[j]=='M')t|=4;
			if(c1[j]=='P')t|=8;
		}
		A[i]=a1,B[i]=b1,C[i]=t;
	}
	cin>>p;
	if(p==1){cout<<0;return 0;}
	n++;
	for(int T=0;T<16;T++){//容斥
		memset(nw[0].a,0,sizeof(nw[0].a));
		memset(nw[1].a,0,sizeof(nw[1].a));
		for(int i=1;i<=m;i++){
			nw[0].a[A[i]][B[i]]++;//加边
			if((C[i]|T)==T)nw[1].a[A[i]][B[i]]++;
		}
		nw[0].a[1][n]=1,nw[0].a[n][n]=1;
		for(rint i=1;i<=n;i++)
			for(rint j=1;j<=n;j++)
				for(rint k=1;k<=n;k++)
					(nw[1].a[j][k]+=nw[0].a[j][i]*nw[0].a[i][k])%=P;
		Nw[1]=nw[0];
		//对于步数1,2的情况要预处理一遍
		for(rint i=2;i<=30;i++){
			Nw[i]=
			Nw[i-1]*nw[i-1]+
			nw[i-1]*Nw[i-1]-
			Nw[i-1]*nw[0]*Nw[i-1];
			//Nw[i]表示走(1<<i)-1步的情况
			nw[i]=
			nw[i-1]*nw[i-1]+
			Nw[i-1]*nw[1]*Nw[i-1]
			-Nw[i-1]*nw[0]*nw[0]*Nw[i-1];
			//nw[i]表示走(1<<i)步的情况
		}
		o=p-1,ans=nw[1],Ans=nw[0];
		//开头是走两步的情况，假如目前走了x步ans代表x步的情况，Ans表示走x-1步
		if(o&1){
			Ans=nw[1];//走两步
			ans=Nw[2];//走三步
			o--;
		}
		//因为合并时不能合并长度为1的步数，会比较麻烦，于是这边有一个预处理
		for(rint i=1;i<=30;i++)if(o&(1<<i)){
			Tmp=Ans;
			Ans=
			Tmp*nw[i]+
			ans*Nw[i]-
			Tmp*nw[0]*Nw[i];
			ans=
			ans*nw[i]+
			Tmp*nw[1]*Nw[i]-
			Tmp*nw[0]*nw[0]*Nw[i];
			//这边的合并的过程与前面是一样的
		}
		if(T==0||T==3||T==5||T==6||T==9||T==10||T==12||T==15)ANS=(ANS+ans.a[1][n])%P;
		else ANS=(ANS-ans.a[1][n]+P)%P;
		//容斥计算结果
	}
	cout<<ANS;
	return 0;
}
```

---

## 作者：free_fall (赞：3)

首先，我们观察到一共只有 $4$ 种原材料，容易想到状压，记录当前已经采购的材料有哪几种于是我们非常自然地得到了这样一个状态：$f_{st,i,j}$ 表示当前采购的原材料为 $st$，位于 $i$ 路口，花了 $j$ 时间的方案数，那么答案就是 $\sum_{i=0}^{T}f_{15,1,i} $。

看一看时间复杂度，wow，居然到达了惊人的 $w=2$，$O(w^4nT)$，而且空间也绝对完蛋。

考虑进一步优化，我们把 $st$ 从状态里面去掉，用容斥来进行计算（看起来好像没什么用，但是对后续优化有帮助），我们用 $f_{i,j}$ 表示位于 $i$ 路口，花了 $j$ 时间的方案数，在做容斥时分别计算不取某个或某些原材料的方案数，那么答案就是：$\sum_{st=0}^{15} (-1)^{cnt_{st}}\sum_{i=0}^{T}f_{1,i} $。

于是我们发现，好像没什么用，空间时间照样超时，怎么办呢？首先这个状态肯定是不能要了，我们观察数据范围发现这个 $n$ 很小，而且状态只从 $j-1$ 和 $j-2$ 转移过来，是不是和斐波那契数列的求解很像？于是我们可以用矩阵乘法来解决这个问题（如果前面没有容斥，这里就不能用矩阵乘法优化了）。

构造矩阵，我们可以用 $1$ 到 $n$ 表示当前的答案，$n+1$ 到 $n+n$ 表示上一步的答案，再用 $0$ 表示所有答案的和。然后对于可以经过商店的边 $u \to v$，$bas_{u+n,v}=1$，对于所有边，$bas_{u,v}=1$（详细构造方式看代码）。

这样空间就开的下了，$w=2$，时间复杂度为 $O(w^4n^3 \log T)$。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=55,M=505,mod=5557;
int n,m,t,u[M],v[M],w[M],ans;
struct mat{
	int a[N][N];
	mat(){
		memset(a,0,sizeof a);
		return;
	}
	mat operator*(const mat &b)const{
		mat res;
		for(int i=0;i<=n*2;i++){
			for(int j=0;j<=n*2;j++){
				for(int k=0;k<=n*2;k++){
					res.a[i][j]=(res.a[i][j]+a[i][k]*b.a[k][j]%mod)%mod;
				}
			}
		}
		return res;
	}
};
int fp(mat a,int b){
	mat res;
	res.a[0][1]=1;
	while(b){
		if(b&1)res=res*a;
		a=a*a;
		b>>=1;
	}
	return (res.a[0][1]+res.a[0][0])%mod;
}
void dfs(int p,int st,int cnt){
	if(p>=4){
		mat bas,res;
		for(int i=1;i<=m;i++){
			if((st&w[i])==0)bas.a[u[i]+n][v[i]]=1;
			bas.a[u[i]][v[i]]=1;
		}
		for(int i=1;i<=n;i++){
			bas.a[i][i+n]=1;
		}
		bas.a[0][0]=bas.a[1][0]=1;
		res.a[0][1]=1;
		int now=fp(bas,t);
		if(cnt%2==0)ans=(ans+now)%mod;
		else ans=(ans-now+mod)%mod;
		return;
	}
	dfs(p+1,st,cnt);
	dfs(p+1,st|(1<<p),cnt+1);
	return;
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		char s[6];
		int len;
		scanf("%lld%lld%s",&u[i],&v[i],s);
		len=strlen(s);
		for(int j=0;j<len;j++){
			if(s[j]=='B')w[i]|=1<<0;
			if(s[j]=='J')w[i]|=1<<1;
			if(s[j]=='M')w[i]|=1<<2;
			if(s[j]=='P')w[i]|=1<<3;
		}
	}
	scanf("%lld",&t);
	dfs(0,0,0);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：_AyachiNene (赞：2)

# 思路：
容易想到一个状压 dp，设 $f_{t,i,s}$ 表示时间为 $t$ 在 $i$ 点，食材的状态为 $s$ 的方案数，转移是容易的，枚举出边即可。看到这个数据提示我们用矩阵优化这个 dp，但发现一个问题，如果把状压的部分也计入矩阵，这个矩阵的大小就炸了。容易想到用容斥优化。每次枚举一个状态，用这个状态的 $1$ 的个数作为容斥系数，买东西的边必须是这个状态的子集，直接走不影响，发现刚好就容掉了。还有一个坑点就是时间不用刚好到 $t$，在矩阵里再记一个总和就行了。时间复杂度 $2^m n^3\log t$，$m$ 为物品的种数。
# Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){x="";char ch=getch();while(!(ch>='a'&&ch<='z')&&!(ch>='A'&&ch<='Z'))ch=getch();while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);putch(' ');write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
const int mod=5557;
struct matrix
{
	int a[51][51];
	matrix(){memset(a,0,sizeof a);}
	inline matrix operator*(const matrix &x)
	{
		matrix res;
		for(int i=0;i<51;i++)
			for(int j=0;j<51;j++)
				for(int k=0;k<51;k++) res.a[i][j]=(res.a[i][j]+a[i][k]*x.a[k][j])%mod;
		return res;
	}
}f,base;
int n,m,t;
int e[30][30];
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n,m);
	for(int i=1;i<=m;i++)
	{
		int u,v;string s;
		read(v,u);read_s(s);
		for(int j=0;j<s.size();j++)
			if(s[j]=='B') e[u][v]|=1;
			else if(s[j]=='J') e[u][v]|=2;
			else if(s[j]=='M') e[u][v]|=4;
			else e[u][v]|=8;
	}
	read(t);
	int ans=0;
	for(int s=0;s<16;s++)
	{
		memset(base.a,0,sizeof base.a);memset(f.a,0,sizeof f.a);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				if((s&e[i][j])==e[i][j]&&e[i][j]) base.a[j-1][n+i-1]=1;
				if(e[i][j]) base.a[n+j-1][n+i-1]=1;
			}
		f.a[0][n]=1;
		for(int i=1;i<=n;i++) base.a[n+i-1][i-1]=1;
		base.a[50][50]=base.a[n][50]=1;
		for(int p=t;p;p>>=1,base=base*base) if(p&1) f=f*base;
		ans=(ans+(__builtin_popcount(s)&1?-1:1)*(f.a[0][n]+f.a[0][50])+mod)%mod;
	}
	write(ans);
	flush();
	return 0;
}
```

---

## 作者：sdyzpf (赞：2)

发现题解区全是容斥，提供一个不需要容斥的做法。建议理解完容斥做法题解的建图后再观看本题解。

首先，将一个点拆成两点仍是必要的。此时我们若考虑仅通过一次快速幂解决问题，就需在每个点上增设 $2^k$ 种状态。我们令原材料的种类数为 $k$。此时大部分题解认为，跑矩阵快速幂的复杂度为 $O(2^{3k+3}n^3\log T)$ 的。这种做法是将 $2^k$ 种状态都建成点，显然是不优秀的。我们不妨将矩阵里的每个元素从数更改为一个大小 $16$ 的数组，思考状态转移，我们发现原本矩阵中两数乘法的操作变成了两个数组的或运算卷积，而加法操作则为两个数组中元素一一对应相加。由于或运算卷积对于加法有分配率，所以我们重定义的矩阵乘法也是有结合律的。此时我们的复杂度降为 $O(2^{2k+3}n^3\log T)$，但仍不够优秀，但或运算卷积是可以使用 FWT 的，预处理出矩阵中所有元素进行 FWT 后的结果，单次卷积的复杂度变为 $O(2^k)$，总时间复杂度为 $O(2^{k+3}n^3\log T+2^kkn^2)$，与容斥做法效率相当。

代码实现如下：
``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=5557;
int n,m,T,g[51][51][16],dp[51][16],tmpdp[51][16],tmpg[51][51][16];
inline void FWT(int *a){
	for(int p=0;p<16;p++)
		for(int msk=0;msk<16;msk++)
			if(msk>>p&1){
				a[msk]+=a[msk^(1<<p)];
				if(a[msk]>=mod) a[msk]-=mod;
			}
}
inline void IFWT(int *a){
	for(int p=0;p<16;p++)
		for(int msk=0;msk<16;msk++)
			if(msk>>p&1){
				a[msk]-=a[msk^(1<<p)];
				if(a[msk]<0) a[msk]+=mod;
			}
}
inline void qpow(int ind){
	while(ind){
		if(ind&1){
			memset(tmpdp,0,sizeof(tmpdp));
			for(int i=0;i<=50;i++)
				for(int j=0;j<=50;j++)
					for(int p=0;p<16;p++)
						tmpdp[j][p]=(tmpdp[j][p]+dp[i][p]*g[i][j][p])%mod;
			memcpy(dp,tmpdp,sizeof(dp));
		}
		ind>>=1;
		memset(tmpg,0,sizeof(tmpg));
		for(int i=0;i<=50;i++)
			for(int j=0;j<=50;j++)
				for(int k=0;k<=50;k++)
					for(int p=0;p<16;p++)
						tmpg[i][j][p]=(tmpg[i][j][p]+g[i][k][p]*g[k][j][p])%mod;
		memcpy(g,tmpg,sizeof(g));
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;dp[1][0]=1;FWT(dp[1]);
	for(int i=1;i<=n;i++) g[i+n][i][0]=1;
	g[0][0][0]=g[1][0][0]=1;
	for(int i=1;i<=m;i++){
		int u,v,msk=0;
		string s;
		cin>>u>>v>>s;
		if(s.find('B')!=string::npos) msk|=1;
		if(s.find('P')!=string::npos) msk|=2;
		if(s.find('J')!=string::npos) msk|=4;
		if(s.find('M')!=string::npos) msk|=8;
		g[u][v][0]=1;g[u][v+n][msk]=1;
	}
	cin>>T;
	for(int i=0;i<=2*n;i++)
		for(int j=0;j<=2*n;j++) FWT(g[i][j]);
	qpow(T);IFWT(dp[0]);IFWT(dp[1]);
	cout<<(dp[0][15]+dp[1][15])%mod;
	return 0;
}
```

---

## 作者：ax_by_c (赞：0)

令 $n=N,k=\lvert U\rvert$，本题中 $k=4$。

考虑 DP，设 $f_{i,x,S}$ 表示第 $i$ 秒走到了第 $x$ 个点，已经取到的集合为 $S$ 的方案数，答案即为 $\sum_{i=0}^{T} f_{i,1,U}$。

显然可以将 $f_{i-1,x,S},f_{i,x,S},\sum_{j=0}^{i}f_{j,1,U}$ 之间的转移写成矩阵乘法的形式，时间复杂度 $O(n^38^k\log T)$，无法通过。

考虑容斥，设最终取到的集合与 $S'$ 无交的方案数为 $F(S')$，则答案为 $\sum_{S'}(-1)^{\lvert S'\rvert}F(S')$。

此时 DP 就不需要记录已经取到的集合了，可以设 $f_{i,x}$ 表示第 $i$ 秒走到了第 $x$ 个点且已经取到的集合与 $S'$ 无交的方案数，同样使用矩阵乘法，时间复杂度 $O(n^3\log T)$。

总时间复杂度 $O(2^kn^3\log T)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
const int mod=5557;
const int N=30;
const int S=(1<<4)+5;
int rd_(){
	int res=0;
	char c=getchar();
	while(!(c=='B'||c=='J'||c=='M'||c=='P'))c=getchar();
	while(c=='B'||c=='J'||c=='M'||c=='P'){
		if(c=='B')res|=1;
		if(c=='J')res|=2;
		if(c=='M')res|=4;
		if(c=='P')res|=8;
		c=getchar();
	}
	return res;
}
struct E{
	int v,w;
};
int n,m,T,msk,pct[S];
vector<E>g[N];
struct matr{
	int n,m,a[N*2][N*2];
	void clr(){
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]=0;
	}
};
matr operator * (const matr &a,const matr &b){
	matr c;
	c.n=a.n,c.m=b.m;
	c.clr();
	for(int i=1;i<=a.n;i++)for(int k=1;k<=b.m;k++)for(int j=1;j<=a.m;j++)
	c.a[i][k]=(c.a[i][k]+a.a[i][j]*b.a[j][k]%mod)%mod;
	return c;
}
matr operator ^ (matr a,int b){
	matr r=a;
	b--;
	while(b){
		if(b&1)r=r*a;
		a=a*a;
		b>>=1;
	}
	return r;
}
matr ff,ss;
int F(int st){
	ff.n=ff.m=n*2+1;
	ff.clr();
	ff.a[n*2+1][n*2+1]++;
	for(int u=1;u<=n;u++){
		ff.a[n+u][u]++;
		for(auto e:g[u]){
			ff.a[n+u][n+e.v]++;if(n+e.v==n+1)ff.a[n+u][n*2+1]++;
			if(!(e.w&st)){
				ff.a[u][n+e.v]++;
				if(n+e.v==n+1)ff.a[u][n*2+1]++;
			}
		}
	}
	ss.n=1,ss.m=n*2+1;
	ss.clr();
	ss.a[1][n+1]++;
	ss.a[1][n*2+1]++;
	ff=ff^T;
	ss=ss*ff;
	return ss.a[1][n*2+1];
}
void main(){
	msk=(1<<4)-1;
	scanf("%d %d",&n,&m);
	for(int i=1,u,v,w;i<=m;i++){
		scanf("%d %d",&u,&v);
		w=rd_();
		g[u].push_back({v,w});
	}
	scanf("%d",&T);
	for(int i=0;i<=msk;i++)pct[i]=pct[i>>1]+(i&1);
	int ans=0;
	for(int i=0;i<=msk;i++){
		if(pct[i]%2==0)ans=(ans+F(i))%mod;
		else ans=(ans-F(i)+mod)%mod;
	}
	printf("%d\n",ans);
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

