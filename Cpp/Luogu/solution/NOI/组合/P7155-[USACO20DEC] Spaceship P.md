# [USACO20DEC] Spaceship P

## 题目描述

奶牛 Bessie 外星人绑架了，现在被关在了一艘外星人的飞船里！飞船有 $N$（$1≤N≤60$）间房间，编号为 $1…N$，其中某些房间之间由单向通过的门所连接（由于使用了奇怪的外星技术，一扇门甚至可能从一间房间通回这间房间本身！）。然而，没有两扇门具有完全相同的出发和到达房间。此外，Bessie 有一个遥控器，上有编号为 $1…K$ （$1≤K≤60$）的按钮。

如果 Bessie 能够完成一个怪异的任务，外星人就会释放她。首先，他们会选择两间房间 $s$ 和 $t$（$1≤s,t≤N$），以及两个整数 $b_s$ 和 $b_t$（$1≤b_s,b_t≤K$）。他们会将 Bessie 放在房间 $s$ 内，并令她立刻按下按钮 $b_s$。然后 Bessie 需要继续在飞船内穿梭，同时按下按钮。有一些 Bessie 的行动需要遵守的规则：

 - 在每间房间内，在按下恰好一个按钮后，她必须选择从某扇门离开去往另一间房间（可能会回到同一间房间）或停止行动。
 - 一旦 Bessie 按下某个按钮，她再次按下这个按钮即为非法，除非在此之间她按下过编号更大的按钮。换句话说，按下编号为 x 的按钮会使得这个按钮变为非法，同时所有编号 $<x$ 的按钮会被重置为合法。
 - 如果 Bessie 按下非法的按钮，任务即失败，外星人就会把她关起来。 

仅当 Bessie 停止行动时位于房间 $t$，她最后按下的按钮是 $b_t$，并且没有按下过非法按钮时，Bessie 才会被释放。

Bessie 担心她可能无法完成这一任务。对于 $Q$
（$1≤Q≤60$）个询问，每个询问包含一组 Bessie 认为可能的 $s,t,b_s$ 以及 $b_t$，Bessie 想要知道可以使她得到释放的通过房间与按键序列的数量。由于答案可能非常大，输出对 $10^9+7$ 取模的结果。 

## 说明/提示

门连接了房间 $1→2$、$2→3$、$3→4$、$4→5$ 以及 $6→6$。

对于第一个询问，Bessie 必须在按下第一个按钮后立刻停止行动。

对于第二个询问，答案显然为零，因为无法从房间 3 前往房间 1。

对于第三个询问，Bessie 的唯一选择是从房间 1 移动到房间 2 到房间 3，同时按下按钮 1、2 和 3。

对于第四个询问，Bessie 的移动方式是唯一的，她有三种可能的按键序列：

 - (1,2,3,2,1)
 - (1,2,1,3,1)
 - (1,3,1,2,1)

对于最后一个询问，Bessie 有五种可能的按键序列：

 - (2)
 - (2,3,2)
 - (2,3,1,2)
 - (2,1,3,2)
 - (2,1,3,1,2)

### 测试点性质：

 - 测试点 4-7 中，$K≤5$ 且 $(b_s,s)$ 在所有询问中均相同。
 - 测试点 8-11 中，对所有询问有 $b_s=K−1$ 以及 $b_t=K$。
 - 测试点 12-15 中，$N,K,Q≤20$。
 - 测试点 16-23 没有额外限制。

供题：Benjamin Qi 

## 样例 #1

### 输入

```
6 3 8
010000
001000
000100
000010
000000
000001
1 1 1 1
3 3 1 1
1 1 3 3
1 1 1 5
2 1 1 5
1 1 2 5
3 1 3 5
2 6 2 6
```

### 输出

```
1
0
1
3
2
2
0
5```

## 样例 #2

### 输入

```
6 4 6
001100
001110
101101
010111
110111
000111
3 2 4 3
3 1 4 4
3 4 4 1
3 3 4 3
3 6 4 3
3 1 4 2```

### 输出

```
26
49
29
27
18
22```

## 样例 #3

### 输入

```
6 10 5
110101
011001
001111
101111
111010
000001
2 5 2 5
6 1 5 2
3 4 8 3
9 3 3 5
5 1 3 4```

### 输出

```
713313311
716721076
782223918
335511486
539247783```

# 题解

## 作者：Rainybunny (赞：24)

&emsp;&emsp;[来这里看叭~](https://www.cnblogs.com/rainybunny/p/14493680.html)

# $\mathcal{Description}$

&emsp;&emsp;[Link](https://www.luogu.com.cn/problem/P7155).

&emsp;&emsp;Bessie 在一张含 $n$ 个结点的有向图上遍历，站在某个结点上时，她必须按下自己手中 $m$ 个按钮中处于激活状态的一个才能走向其他结点或终止遍历（不能原地等待）。初始时，所有按钮都处于激活状态，按下 $i$ 号按钮时，$i$ 号按钮变为非激活状态，所有编号 $<i$ 的按钮被激活。

&emsp;&emsp;给定 $q$ 组形如 $(b_s,s,b_t,t)$ 的询问，求 Bessie 从 $s$ 出发，第一步按 $b_s$ 按钮，到 $t$ 终止遍历，且最后一步按 $b_t$ 按钮的遍历方案数（遍历顺序或按键不同，方案则不同）。

&emsp;&emsp;$n,k,q\le60$。

# $\mathcal{Solution}$

&emsp;&emsp;大概是图上的高维大力 DP 题叭。

&emsp;&emsp;初步理解按键规则：若把 $m$ 个按键视为一个二进制数，那么在行动过程中这一数的数值是单增的——因为若按键最高非激活位被重新激活，则一定被更高位激活。

&emsp;&emsp;进一步，我们尝试以“非激活按键的最高位”为切入点设计 DP 状态。令 $f(h,i,j)$ 表示从 $i$ 出发（不钦定第一步）走到 $j$（不钦定最后一步），且非激活按键最高位不超过 $h$ 的方案数。转移：

- 当前方案根本没有取到过 $h$，$f(h,i,j)\longleftarrow f(h-1,i,j)$。

- 否则，枚举取到 $h$ 的唯一一点 $k$，显然有
    $$
    f(h,i,j)\longleftarrow\sum_{(u,k),(k,v)\in E}f(h-1,i,u)f(h-1,v,j)
    $$
    注意到 $h$ 和 $k$ 正在枚举，视为常数，乘法中的两个状态分别只和 $i$ 与 $j$ 有关，所以只需要定义辅助状态
    $$
    g(i)=\sum_{(u,k)\in E}f(h-1,i,u)
    $$
    $$
    h(j)=\sum_{(k,v)\in E}f(h-1,v,j)
    $$
    则有 $f(h,i,j)\longleftarrow g(i)h(j)$。

---

&emsp;&emsp;最后一个问题，求出这个 $f$ 有什么用呢？

&emsp;&emsp;$f$ 的定义与询问的差别仅有是否限制第一步和最后一步，所以可以直接把 $q$ 个限制当做虚拟点丢到状态里，让 $f$ 成为 $m\times(n+q)\times(n+q)$ 的状态，$f(h,i,j)$ 的含义变为：

- $i,j\le n$：含义不变；
- $i\le n$，$j>n$：从 $i$ 出发（不钦定第一步），走到第 $j-n$ 个询问的 $t$ 且最后一步为 $b_t$ 的方案数；
- $i>n$，$j\le n$：从第 $i-1$ 个询问的 $s$ 出发，且第一步为 $b_s$，走到 $j$（不钦定最后一步）的方案数；
- $i>n$，$j>n$：同理。

&emsp;&emsp;可见，第 $i$ 个询问的答案即为 $f(m,n+i,n+i)$。转移过程需要变化的地方仅是当枚举的 $(h,k)$ 恰好为某个询问的某个端点时才给 $g$ 或 $h$ 添加方案。

&emsp;&emsp;综上，复杂度 $\mathcal O(mn(n+q)^2)$，代码极度舒适。

## $\mathcal{Code}$

```cpp
/* Clearink */

#include <cstdio>

#define rep( i, l, r ) for ( int i = l, rpbound##i = r; i <= rpbound##i; ++i )
#define per( i, r, l ) for ( int i = r, rpbound##i = l; i >= rpbound##i; --i )

const int MAXN = 60, MOD = 1e9 + 7;
int n, m, q, f[MAXN + 5][MAXN * 2 + 5][MAXN * 2 + 5];
int lef[MAXN * 2 + 5], rig[MAXN * 2 + 5];
char adj[MAXN + 5][MAXN + 5];
struct Query { int bs, s, bt, t; } qry[MAXN + 5];

inline int mul( const long long a, const int b ) { return a * b % MOD; }
inline int add( int a, const int b ) { return ( a += b ) < MOD ? a : a - MOD; }
inline void addeq( int& a, const int b ) { ( a += b ) >= MOD && ( a -= MOD ); }

int main() {
	scanf( "%d %d %d", &n, &m, &q );
	rep ( i, 1, n ) {
		scanf( "%s", adj[i] + 1 );
		rep ( j, 1, n ) adj[i][j] ^= '0';
	}
	rep ( i, 1, q ) {
		scanf( "%d %d %d %d", &qry[i].bs, &qry[i].s, &qry[i].bt, &qry[i].t );
	}
	rep ( h, 1, m ) {
		int ( *fcur )[MAXN * 2 + 5]( f[h] );
		int ( *flas )[MAXN * 2 + 5]( f[h - 1] );
		rep ( i, 1, n + q ) rep ( j, 1, n + q ) fcur[i][j] = flas[i][j];
		rep ( k, 1, n ) {
			rep ( i, 1, n ) lef[i] = rig[i] = 0;
			lef[k] = rig[k] = 1;
			rep ( i, 1, q ) {
				lef[n + i] = qry[i].bs == h && qry[i].s == k;
				rig[n + i] = qry[i].bt == h && qry[i].t == k;
			}
			rep ( i, 1, n + q ) rep ( j, 1, n ) if ( adj[j][k] ) {
				addeq( lef[i], flas[i][j] );
			}
			rep ( i, 1, n ) rep ( j, 1, n + q ) if ( adj[k][i] ) {
				addeq( rig[j], flas[i][j] );
			}
			rep ( i, 1, n + q ) rep ( j, 1, n + q ) {
				addeq( fcur[i][j], mul( lef[i], rig[j] ) );
			}
		}
	}
	rep ( i, 1, q ) printf( "%d\n", f[m][n + i][n + i] );
	return 0;
}

```


---

## 作者：tzc_wk (赞：12)

[Portal](https://www.luogu.com.cn/problem/P7155)

Yet another 1e9+7

Yet another 计数 dp

Yet another 我做不出来的题

考虑合法的按键方式长啥样。假设我们依次按下了 $p_1,p_2,\dots,p_m$ 号按键。

若 $m=1$，则序列 $p_1,p_2,\dots,p_m$ 显然合法。

若 $m>1$，则 $p_1,p_2,\dots,p_m$ 必须有唯一最大值 $x$（否则的话第二次按 $x$ 的时候就不合法了）。假设 $x$ 将原序列分成两个子序列 $p_1,p_2,\dots,p_{k-1}$ 和 $p_{k+1},p_{k+2},\dots,p_{m}$，那么这两个序列的最大值必须都小于 $x$，否则原序列就不会有唯一最大值 $x$ 了。并且 $p_1,p_2,\dots,p_{k-1}$ 和 $p_{k+1},p_{k+2},\dots,p_{m}$ 也必须是合法序列。

形式化地说，$p_1,p_2,\dots,p_m$ 必须是一个大根堆的中序遍历。

这样就可以 $dp$ 了。设 $dp_{a,b,c,x1,x2}$ 表示起点为 $a$，终点为 $b$，按下的按键的编号都 $\leq c$ 的合法的行走路线个数。$x1$ 表示是否对第一次的按键有要求，$x2$ 表示是否对最后一次的按键有要求。

先考虑 $x1=x2=0$ 的情况，即对起点和终点按键都没有要求。

那么有以下两种转移方式：

- 按键序列中按下的编号最大的按键 $<c$，则 $dp_{a,b,c,0,0}=dp_{a,b,c-1,0,0}$
- 若按键序列中按下的编号最大的按键 $=c$，那么我们枚举在 $k$ 点按下编号为 $c$ 的键，那么 $a$ 到 $b$ 的路径被我们拆成了两部分 $a\to k$ 和 $k\to b$。我们进一步枚举 $k$ 之前到达的点 $u$ 和 $k$ 接下来到达的点 $v$，那么根据之前的推论，$a\to u$ 路径上我们只能按下编号 $\leq c-1$ 的键，$v\to b$ 的路径上我们也只能按下编号 $\leq c-1$ 的键。故我们有 $dp_{a,b,c,0,0}=\sum\limits_{k}\sum\limits_{(u,k)}\sum\limits_{(k,v)}dp_{a,u,c-1,0,0}\times dp_{v,b,c-1,0,0}$，记 $f_{a,k,c}=\sum\limits_{(u,k)}dp_{a,u,c-1,0,0}$， $g_{b,k,c}=\sum\limits_{(k,v)}dp_{v,b,c-1,0,0}$，那么上述式子可优化为 $dp_{a,b,c,0,0}=\sum\limits_{k}f_{a,k,c}\times g_{b,k,c}$（当然，如果 $k=a$ 那么 $k$ 可以是路径当中第一个点，此时就不存在 $k$ 之前的点了，故令所有 $f_{a,a,c}$ 加 $1$ 即可，$g_{b,b,c}$ 同理）。

紧接着是 $x1\neq 0$ 或 $x2\neq 0$ 的情况，这里以 $x1=1,x2=0$ 的情况为例，其它两种情况同理。

还是分两种情况（其实与之前那种情况大差不差）：

- 按键序列中按下的编号最大的按键 $<c$，则 $dp_{a,b,c,1,0}=dp_{a,b,c-1,1,0}$。

- 若按键序列中按下的编号最大的按键 $=c$， $dp_{a,b,c,1,0}=\sum\limits_{k}\sum\limits_{(u,k)}\sum\limits_{(k,v)}dp_{a,u,c-1,1,0}\times dp_{v,b,c-1,0,0}$，你还是记 $f_{a,k,c}=\sum\limits_{(u,k)}dp_{a,u,c-1,1,0}$， $g_{b,k,c}=\sum\limits_{(k,v)}dp_{v,b,c-1,0,0}$，将上述式子优化为 $dp_{a,b,c,1,0}=\sum\limits_{k}f_{a,k,c}\times g_{b,k,c}$（只不过 $k=a$ 的情况要改一下，只有当 $c=bs$ 的时候才能令 $f_{a,a,c}$ 加 $1$）

这样 $dp$ 一遍是 $n^4$ 的，加上 $q$ 次询问的条件，显然不能让我们满意。

不过发现对于每组询问，只有当 $a=s$ 的时候 $dp_{a,b,c,1,0}$ 才有意义，只有当 $b=t$ 的时候 $dp_{a,b,c,0,1}$ 才有意义。所以可以预处理出 $dp_{a,b,c,0,0}$ 的值，对于每组询问重新计算 $dp_{a,b,c,0,1},dp_{a,b,c,1,0},dp_{a,b,c,1,1}$ 的值。这样总复杂度就降到了 $n^4+qn^3$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
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
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=60;
const int MOD=1e9+7;
int n,k,qu;
char ed[MAXN+5][MAXN+5];
int dp[2][2][MAXN+5][MAXN+5][MAXN+5],f[2][MAXN+5][MAXN+5][MAXN+5],g[2][MAXN+5][MAXN+5][MAXN+5];
void prework(){
	for(int x=1;x<=k;x++){
		for(int i=1;i<=n;i++) for(int k=1;k<=n;k++) for(int l=1;l<=n;l++)
			if(ed[l][k]=='1') f[0][i][k][x]=(f[0][i][k][x]+dp[0][0][i][l][x-1])%MOD;
		for(int j=1;j<=n;j++) for(int k=1;k<=n;k++) for(int l=1;l<=n;l++)
			if(ed[k][l]=='1') g[0][j][k][x]=(g[0][j][k][x]+dp[0][0][l][j][x-1])%MOD;
		for(int i=1;i<=n;i++) f[0][i][i][x]=(f[0][i][i][x]+1)%MOD;
		for(int i=1;i<=n;i++) g[0][i][i][x]=(g[0][i][i][x]+1)%MOD;
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dp[0][0][i][j][x]=dp[0][0][i][j][x-1];
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) for(int k=1;k<=n;k++)
			dp[0][0][i][j][x]=(dp[0][0][i][j][x]+1ll*f[0][i][k][x]*g[0][j][k][x]%MOD)%MOD;
	}
}
int query(int s,int bs,int t,int bt){
	fill0(dp[1][0]);fill0(dp[0][1]);fill0(dp[1][1]);fill0(f[1]);fill0(g[1]);
	for(int x=1;x<=k;x++){
		for(int k=1;k<=n;k++) for(int l=1;l<=n;l++)
			if(ed[l][k]=='1') f[1][s][k][x]=(f[1][s][k][x]+dp[1][0][s][l][x-1])%MOD;
		for(int k=1;k<=n;k++) for(int l=1;l<=n;l++)
			if(ed[k][l]=='1') g[1][t][k][x]=(g[1][t][k][x]+dp[0][1][l][t][x-1])%MOD;
		if(x==bs) f[1][s][s][x]=(f[1][s][s][x]+1)%MOD;
		if(x==bt) g[1][t][t][x]=(g[1][t][t][x]+1)%MOD;
		for(int i=1;i<=n;i++){
			dp[1][0][s][i][x]=dp[1][0][s][i][x-1];
			dp[0][1][i][t][x]=dp[0][1][i][t][x-1];
			for(int k=1;k<=n;k++){
				dp[1][0][s][i][x]=(dp[1][0][s][i][x]+1ll*f[1][s][k][x]*g[0][i][k][x]%MOD)%MOD;
				dp[0][1][i][t][x]=(dp[0][1][i][t][x]+1ll*f[0][i][k][x]*g[1][t][k][x]%MOD)%MOD;
			}
		}
		dp[1][1][s][t][x]=dp[1][1][s][t][x-1];
		for(int k=1;k<=n;k++){
			dp[1][1][s][t][x]=(dp[1][1][s][t][x]+1ll*f[1][s][k][x]*g[1][t][k][x]%MOD)%MOD;
		}
	}
	return dp[1][1][s][t][k];
}
int main(){
	scanf("%d%d%d",&n,&k,&qu);
	for(int i=1;i<=n;i++) scanf("%s",ed[i]+1);
	prework();
	while(qu--){
		int s,bs,t,bt;scanf("%d%d%d%d",&bs,&s,&bt,&t);
		printf("%d\n",query(s,bs,t,bt));
	}
	return 0;
}
/*
6 3 8
010000
001000
000100
000010
000000
000001
1 1 1 1
3 3 1 1
1 1 3 3
1 1 1 5
2 1 1 5
1 1 2 5
3 1 3 5
2 6 2 6
*/
```



---

## 作者：Aleph1022 (赞：7)

讲个不要脑子的做法。

令邻接矩阵是 $\mathbf G$，所有元素 $\le k$ 的满足条件的序列的 GF 为 $F_k(z)$。  
那么如果不考虑 $b_s,s,b_t,t$，答案无非就是 $\mathbf G^{-1} F_k(\mathbf G)$。

不难发现计数 $F_k(z)$ 可以拆出最大值，即
$$
F_k(z) = z\sum\limits_{i=1}^k (1+F_{i-1}(z))^2
$$

那么考虑维护出所有 $F_k(\mathbf G)$，自然就是
$$
F_k(\mathbf G) = \mathbf G\sum\limits_{i=1}^k (1+F_{i-1}(\mathbf G))^2
$$

注意到平方只要计算 $k$ 次，那么计算所有 $F_k(\mathbf G)$ 的总复杂度就是 $O(k^2n^2+kn^3)$。

令 $\mathbf v_s$ 是行向量 $([i=s])_{i=1}^n$。  
令 $F_{b_s,0,k}(z),F_{0,b_t,k}(z),F_{b_s,b_t,k}(z)$ 分别是限定了序列首尾的 GF，那么有
$$
\begin{aligned}
F_{b_s,0,k}(z) &= z \sum\limits_{i=1}^k \left[F_{b_s,0,i-1}(z)(1+F_{i-1}(z))+[i=b_s](1+F_{i-1}(z))\right] \\
F_{0,b_t,k}(z) &= z \sum\limits_{i=1}^k \left[F_{0,b_t,i-1}(z)(1+F_{i-1}(z))+[i=b_t](1+F_{i-1}(z))\right] \\
F_{b_s,b_t,k}(z) &= z \sum\limits_{i=1}^k \left[F_{b_s,0,i-1}(z)F_{0,b_t,i-1}(z)+[i=b_s]F_{0,b_t,i-1}(z)+[i=b_t]F_{b_s,0,i-1}(z)+[i=b_s=b_t]\right]
\end{aligned}
$$

不妨直接维护出所有 $\mathbf v_s F_{b_s,0,k}(\mathbf G),F_{0,b_t,k}(\mathbf G) \mathbf v_t^T,\mathbf v_s \mathbf G^{-1} F_{b_s,b_t,k}(\mathbf G) \mathbf v_t^T$。  
根据递推式，维护前两者可以做到 $O(kn^2)$（向量乘矩阵），维护第三者可以做到 $O(kn)$（向量乘向量）。  
注意到 $\mathbf G$ 可能没有逆，但是只需要注意到递推时必然会多贡献一个 $\mathbf G$，去掉即可。

时间复杂度 $O(k^2n^2+kn^3+qkn^2)$。

代码：
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 60;
const int mod = 1e9 + 7;
int n,K,q;
struct Matrix
{
	int a[N + 5][N + 5];
	inline Matrix(int op = 0)
	{
		if(!op)
			for(int i = 1;i <= n;++i)
				for(int j = 1;j <= n;++j)
					a[i][j] = 0;
		else
			for(int i = 1;i <= n;++i)
				for(int j = 1;j <= n;++j)
					a[i][j] = i == j;
	}
	inline int *operator[](int x)
	{
		return a[x];
	}
	inline const int *operator[](int x) const
	{
		return a[x];
	}
	inline Matrix operator*(int x) const
	{
		Matrix ret;
		for(int i = 1;i <= n;++i)
			for(int j = 1;j <= n;++j)
				ret[i][j] = (long long)x * a[i][j] % mod;
		return ret;
	}
	inline Matrix operator+(const Matrix &o) const
	{
		Matrix ret;
		for(int i = 1;i <= n;++i)
			for(int j = 1;j <= n;++j)
				ret[i][j] = (a[i][j] + o[i][j]) % mod;
		return ret;
	}
	inline Matrix operator*(const Matrix &o) const
	{
		Matrix ret;
		for(int k = 1;k <= n;++k)
			for(int i = 1;i <= n;++i)
				for(int j = 1;j <= n;++j)
					ret[i][j] = (ret[i][j] + (long long)a[i][k] * o[k][j]) % mod;
		return ret;
	}
} G,f[N + 5],f_temp[N + 5];
struct Vector
{
	int a[N + 5];
	inline Vector(int x = 0)
	{
		for(int i = 1;i <= n;++i)
			a[i] = i == x;
	}
	inline int &operator[](int x)
	{
		return a[x];
	}
	inline const int &operator[](int x) const
	{
		return a[x];
	}
	inline Vector operator+(const Vector &o) const
	{
		Vector ret;
		for(int i = 1;i <= n;++i)
			ret[i] = (a[i] + o[i]) % mod;
		return ret;
	}
} f_10[N + 5],f_10_temp[N + 5];
inline Vector operator*(const Vector &a,const Matrix &b)
{
	Vector ret;
	for(int k = 1;k <= n;++k)
		for(int i = 1;i <= n;++i)
			ret[i] = (ret[i] + (long long)a[k] * b[k][i]) % mod;
	return ret;
}
struct VectorT
{
	int a[N + 5];
	inline VectorT(int x = 0)
	{
		for(int i = 1;i <= n;++i)
			a[i] = i == x;
	}
	inline int &operator[](int x)
	{
		return a[x];
	}
	inline const int &operator[](int x) const
	{
		return a[x];
	}
	inline VectorT operator+(const VectorT &o) const
	{
		VectorT ret;
		for(int i = 1;i <= n;++i)
			ret[i] = (a[i] + o[i]) % mod;
		return ret;
	}
} f_01[N + 5],f_01_temp[N + 5];
inline VectorT operator*(const Matrix &a,const VectorT &b)
{
	VectorT ret;
	for(int k = 1;k <= n;++k)
		for(int i = 1;i <= n;++i)
			ret[i] = (ret[i] + (long long)a[i][k] * b[k]) % mod;
	return ret;
}
int f_11[N + 5],f_11_temp[N + 5];
inline int operator*(const Vector &a,const VectorT &b)
{
	int ret = 0;
	for(int k = 1;k <= n;++k)
		ret = (ret + (long long)a[k] * b[k]) % mod;
	return ret;
}
int main()
{
	scanf("%d%d%d",&n,&K,&q);
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j)
			scanf("%1d",G[i] + j);
	f_temp[0] = G;
	for(int k = 1;k <= K;++k)
	{
		for(int i = 1;i <= k;++i)
			f[k] = f[k] + f_temp[i - 1];
		f_temp[k] = (f[k] + 1) * (f[k] + 1) * G;
	}
	for(int b_s,s,b_t,t;q;--q)
	{
		scanf("%d%d%d%d",&b_s,&s,&b_t,&t);
		Vector v_s(s),v_g_s = v_s * G;
		VectorT v_t(t),v_g_t = G * v_t;
		for(int k = 1;k <= K;++k)
		{
			f_10[k] = 0;
			for(int i = 1;i <= k;++i)
				f_10[k] = f_10[k] + f_10_temp[i - 1];
			if(b_s <= k)
				f_10[k] = f_10[k] + v_g_s * (f[b_s - 1] + 1);
			f_10_temp[k] = (f_10[k] * G) * (f[k] + 1);
		}
		for(int k = 1;k <= K;++k)
		{
			f_01[k] = 0;
			for(int i = 1;i <= k;++i)
				f_01[k] = f_01[k] + f_01_temp[i - 1];
			if(b_t <= k)
				f_01[k] = f_01[k] + (f[b_t - 1] + 1) * v_g_t;
			f_01_temp[k] = (f[k] + 1) * (G * f_01[k]);
		}
		for(int k = 1;k <= K;++k)
		{
			f_11[k] = 0;
			for(int i = 1;i <= k;++i)
				f_11[k] = (f_11[k] + f_11_temp[i - 1]) % mod;
			if(b_s <= k)
				f_11[k] = (f_11[k] + v_s * f_01[b_s - 1]) % mod;
			if(b_t <= k)
				f_11[k] = (f_11[k] + f_10[b_t - 1] * v_t) % mod;
			if(b_s == b_t && b_s <= k)
				f_11[k] = (f_11[k] + v_s * v_t) % mod;
			f_11_temp[k] = f_10[k] * f_01[k];
		}
		printf("%d\n",f_11[K]);
	}
}
```

---

## 作者：Gauss0320 (赞：2)

# Abstract

昨天有同机房的人说，[@GuildingStar](https://www.luogu.com.cn/user/75840) 的讲题听不懂，所以我就来写一些粗略的补充。

# Solution

首先，我们可以将答案写作从 $s$ 到 $t$ 走 $i$ 步的方案数与上长度为 $i+1$ 的合法按键序列的乘积之和。

并且注意到从 $s$ 到 $t$ 走 $i$ 步的方案数为 ${\mathbf A}^i(s;t)$，其中 $\mathbf{A}^i$ 为邻接矩阵 $\mathbf A$ 的 $i$ 次幂。

所以很容易想到设出一个生成函数 $F(x)$，使得$[x^i]F(x)$ 恰好为长度为 $i$ 的合法按键序列，根据多项式环的通用性质，答案就是 ${\mathbf A^{-1}}F(\mathbf A)$。

进一地，注意到每个合法的按键序列中有唯一的最大值，因为按下最大值之后不可能按到编号更大的按钮，所以我们可以将序列从最大值处断开，分为左右两段独立的区间来处理。

所以我们令 $F_k(x)$ 为所有元素 $\le k$ 的合法序列的生成函数。

写出转移方程
$$F_k(x)=x\sum_{i=1}^k(1+F_{i-1}(x))^2$$

解释：枚举序列中的最大值 $i$，拆成左右两段，两段中的元素均 $\le i-1$，然后作个卷积。乘 $x$ 是因为要去掉最大值，$+1$ 是因为我们的生成函数没有常数项，方便之后处理。

我们先预处理出所有的 $F_k(\mathbf A)$，时间复杂度为 $\mathcal O(kn^3)$。

接下来，考虑上序列首、尾的限制，设 $F_{b_s,0,k}(x),F_{0,b_t,k}(x),F_{b_s,b_t,k}(x)$为分别考虑首、尾、首和尾的限制的生成函数，仿照上式写出转移方程
$$
\begin{aligned}F_{b_s,0,k}(x)&=x\sum_{i=1}^k\left\{\left[[i=b_s]+F_{b_s,0,i-1}(x)\right]\left[1+F_{i-1}(x)\right]\right\}\\
F_{0,b_t,k}(x)&=x\sum_{i=1}^k\left\{\left[[i=b_t]+F_{0,b_t,i-1}(x)\right]\left[1+F_{i-1}(x)\right]\right\}\\
F_{b_s,b_t,k}(x)&=x\sum_{i=1}^k\left\{\left[[i=b_s]+F_{b_s,0,i-1}(x)\right]\left[[i=b_t]+F_{0,b_t,i-1}(x)\right]\right\}
\end{aligned}$$
设行向量 ${\mathbf \epsilon}_s=([i=s])_{i=1}^n$，实际上，在转移中，我们仅需维护出 $\epsilon_sF_{b_s,0,k}(\mathbf A),F_{0,b_t,k}(\mathbf A)\epsilon_t^{\text{T}},\epsilon_sF_{b_s,b_t,0}(\mathbf A)\epsilon_t^{\text{T}}$ 即可。

总的时间复杂度为 $\mathcal O(kn^3+qkn^2)$。

---

## 作者：xiaoyaowudi (赞：1)

## Sol

以下认为 $n,k$ 同阶。

设 $dp_{i,j},i\le j$ 表示从已经摁下 $i$ 按钮这个状态开始，到刚摁下 $j$ 这个按钮，中间没摁过 $>j$ 的所有方案的转移矩阵之和。

直接转移是 trivial 的，但是复杂度为 $\mathcal{O}\left(n^5\right)$，不够优秀。

注意到所有 dp 值的矩阵都是关于邻接矩阵 $M$ 的多项式。所以可以求出 $M$ 的特征多项式 $P\left(x\right)$，每次矩阵乘法就把两个对应的多项式 $\mathcal{O}\left(n^2\right)$ 相乘，然后对 $P$ 取模。预处理出 $M$ 的 $0\sim n$ 次方即可 $\mathcal{O}\left(n\right)$ 求出单个多项式对应的答案。

这时复杂度为 $\mathcal{O}\left(n^4+qn^3\right)$。因为询问的时候首先枚举最大位置，再对两个多项式做乘法并取模，再计算答案。还是不够优秀。考虑优化掉 $q$ 上面一个 $n$。

由于每次做乘法的两个多项式次数都是 $n-1$。于是考虑把所有的 dp 值都转为 $2n-1$ 维点值，然后预处理出每个点值对每个位置的贡献，即可 $\mathcal{O}\left(qn^2\right)$ 回答询问了。

## Code

```cpp
#include <iostream>
#include <algorithm>
constexpr int N(62),p(1e9+7);
void W(int &a,int b){a+=b;if(a>=p) a-=p;}
int W(int k){return k>=p?k-p:k;}
int fp(int a,int b){int ans(1),off(a);while(b){if(b&1) ans=1ll*ans*off%p;off=1ll*off*off%p;b>>=1;}return ans;}
void calc(int n,int mat[N][N],int ans[N])
{
	static int dat[N][N];dat[0][0]=1;
	for(int i(1);i<n;++i)
	{
		int pos(0);
		for(int j(i+1);j<=n;++j) if(mat[j][i]){pos=j;break;}
		if(!pos) continue;
		if(pos!=i+1)
		{
			for(int j(i);j<=n;++j) W(mat[i+1][j],mat[pos][j]);
			for(int j(1);j<=n;++j) W(mat[j][pos],p-mat[j][i+1]);
		}
		int iv(fp(mat[i+1][i],p-2));
		for(int j(i+2);j<=n;++j)
		{
			int num(1ll*iv*mat[j][i]%p);
			for(int k(i);k<=n;++k) mat[j][k]=(mat[j][k]+1ll*(p-num)*mat[i+1][k])%p;
			for(int k(1);k<=n;++k) mat[k][i+1]=(mat[k][i+1]+1ll*num*mat[k][j])%p;
		}
	}
	for(int i(1);i<=n;++i)
	{
		dat[i][0]=1ll*(p-dat[i-1][0])*mat[i][i]%p;dat[i][i]=dat[i-1][i-1];
		for(int j(1),t(mat[i][i]);j<i;++j) dat[i][j]=(dat[i-1][j-1]+1ll*(p-t)*dat[i-1][j])%p;
		for(int j(i-1),t(mat[i][i-1]);j;--j,t=1ll*t*mat[j+1][j]%p) for(int k(0);k<j;++k) dat[i][k]=(dat[i][k]+1ll*(p-dat[j-1][k])*t%p*mat[j][i])%p;
	}
	for(int i=0;i<=n;++i) ans[i]=dat[n][i];
}
int cp[N],pre[N][N],n;
void calc(int *a,int *b,int *c)
{
	static unsigned long long d[N<<1];
	for(int i(0);i<=2*(n-1);++i)
	{
		int l(std::max(0,i-n+1)),r(std::min(i,n-1));
		unsigned long long cur(0);
		for(int j(l);j<=r;j+=18)
		{
			int t(std::min(j+18-1,r));
			for(int k(j);k<=t;++k)
			{
				cur+=1ull*a[k]*b[i-k];
			}
			cur%=p;
		}
		d[i]=cur;
	}
	for(int i(1);i<n;++i)
	{
		int v(d[i+n-1]);
		for(int j(0);j<n;++j)
		{
			d[j]+=1ll*v*pre[i][j];
		}
		if(((n-1-i)%18)==0)
		{
			for(int j(0);j<n;++j)
			{
				d[j]%=p;
			}
		}
	}
	for(int i(0);i<n;++i) c[i]=d[i];
}
int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int K,q;std::cin>>n>>K>>q;
	static int trans[N][N],pre[N][N][N];
	for(int i(1);i<=n;++i)
	{
		static char s[N];std::cin>>(s);
		for(int j(0);j<n;++j) pre[1][i][j+1]=trans[i][j+1]=(s[j]-'0');
	}
	calc(n,trans,cp);
	::pre[0][n-1]=1;
	for(int i(1);i<n;++i)
	{
		std::copy(::pre[i-1],::pre[i-1]+n-1,::pre[i]+1);
		int t(p-::pre[i-1][n-1]);
		for(int j(0);j<n;++j) ::pre[i][j]=(::pre[i][j]+1ll*t*cp[j])%p;
	}
	for(int i(1);i<=n;++i) pre[0][i][i]=1;
	for(int _(2);_<n;++_)
	{
		static unsigned long long cur[N][N];
		for(int i(1);i<=n;++i) for(int j(1);j<=n;++j) cur[i][j]=0;
		for(int i(1);i<=n;++i)
		{
			for(int k(1);k<=n;++k)
			{
				for(int j(1);j<=n;++j)
				{
					cur[i][j]+=pre[_-1][i][k]*pre[1][k][j];
				}
			}
		}
		for(int i(1);i<=n;++i) for(int j(1);j<=n;++j) pre[_][i][j]=cur[i][j]%p;
	}
	static int ans[N<<1][N][N];
	int len(2*n-1);
	for(int i(1);i<=len;++i)
	{
		static int f[N<<1];std::fill(f,f+len,0);f[0]=1;int co(1);
		for(int j(1);j<=len;++j) if(j!=i)
		{
			co=1ll*co*fp((p+i-j)%p,p-2)%p;
			for(int t(len-1);t>=0;--t) f[t]=((t?f[t-1]:0)+1ll*(p-j)*f[t])%p;
		}
		for(int j(0);j<len;++j) f[j]=1ll*f[j]*co%p;
		for(int j(1);j<n;++j) for(int t(0);t<n;++t) f[t]=(f[t]+1ll*::pre[j][t]*f[j+n-1])%p;
		static unsigned long long g[N][N];
		for(int j(1);j<=n;++j) for(int t(1);t<=n;++t) g[j][t]=0;
		for(int j(0);j<n;++j)
		{
			for(int t(1);t<=n;++t) for(int k(1);k<=n;++k) g[t][k]+=1ull*pre[j][t][k]*f[j];
			if((n-1-j)%18==0)
			{
				for(int t(1);t<=n;++t) for(int k(1);k<=n;++k) g[t][k]%=p;
			}
		}
		for(int j(1);j<=n;++j) for(int t(1);t<=n;++t) ans[i-1][j][t]=g[j][t];
	}
	static int f[N][N][N<<1],g[N][N];
	for(int i(1);i<=K;++i)
	{
		static int v[N],tt[N],h[N];
		std::copy(h,h+n,v+1);std::copy(h,h+n,tt);v[0]=0;
		v[1]=(v[1]+1)%p;tt[0]=(tt[0]+1)%p;
		for(int j(0);j<n;++j) v[j]=(1ll*::pre[1][j]*v[n]+v[j])%p;
		calc(v,tt,g[i]);for(int j(0);j<n;++j) h[j]=(h[j]+g[i][j])%p;
	}
	static int vl[N];vl[0]=1;
	for(int i(1);i<=K;++i)
	{
		static int h[N][N];
		for(int j(1);j<i;++j)
		{
			std::copy(h[j],h[j]+n,f[i][j]);
		}
		f[i][i][0]=1;
		for(int j(1);j<=i;++j)
		{
			static int tmp[N];std::copy(vl,vl+n,tmp+1);tmp[0]=0;
			for(int t(0);t<n;++t) tmp[t]=(tmp[t]+1ll*::pre[1][t]*tmp[n])%p;
			calc(f[i][j],tmp,tmp);
			for(int t(0);t<n;++t) h[j][t]=(h[j][t]+tmp[t])%p;
		}
		for(int j(0);j<n;++j) vl[j]=(vl[j]+g[i][j])%p;
	}
	{
		static int co[N][N<<1];
		for(int i(0);i<n;++i)
		{
			for(int j(0);j<len;++j)
			{
				co[i][j]=fp(j+1,i);
			}
		}
		for(int i(1);i<=K;++i)
		{
			for(int j(1);j<=i;++j)
			{
				static unsigned long long tmp[N<<1];
				std::fill(tmp,tmp+len,0);
				for(int t(0);t<n;++t)
				{
					for(int w(0);w<len;++w)
					{
						tmp[w]+=1ull*co[t][w]*f[i][j][t];
					}
					if((n-1-t)%18==0)
					{
						for(int w(0);w<len;++w)
						{
							tmp[w]%=p;
						}
					}
				}
				for(int w(0);w<len;++w) f[i][j][w]=tmp[w];
			}
		}
	}
	while(q--)
	{
		int bs,s,bt,t;std::cin>>bs>>s>>bt>>t;
		static int res[N<<1];std::fill(res,res+len,0);
		for(int i(1);i<=K;++i) if(i>=bs && i>=bt)
		{
			for(int j(0);j<len;++j) res[j]=(res[j]+1ll*f[i][bs][j]*f[i][bt][j])%p;
		}
		int fin(0);
		for(int i(0);i<len;++i) fin=(fin+1ll*res[i]*ans[i][s][t])%p;
		std::cout<<fin<<std::endl;
	}
	return 0;
}
```

---

## 作者：Petit_Souris (赞：0)

感觉不到黑，欸，真难吗这题。

观察到在移动按按钮的过程中最高位是单调不降的，于是启发我们根据最高位设计 dp。

设 $dp_{u,v,i}$ 表示从 $u$ 走到 $v$，最高位为 $i$ 的方案数。转移时枚举中间点 $t$，其中 $t$ 是第一次按下 $i$ 的位置，分成 $u\to t$ 和 $t\to v$ 两段处理，最高位都 $<i$，可以用前缀和优化。

现在如果处理所有询问都暴力的话，复杂度为 $\mathcal O(n^5)$，大概无法通过。不过我们发现询问可以放一起搞，拆一个点出来处理开始和结束的两步就行了。复杂度 $\mathcal O(n^4)$，可以通过。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=129,Mod=1e9+7;
ll n,K,Q,dp[N][N][N],f[N],g[N];
ll bs[N],bt[N],S[N],T[N];
char s[N][N];
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),K=read(),Q=read();
    rep(i,1,n)scanf("%s",s[i]+1);
    rep(i,1,Q)bs[i]=read(),S[i]=read(),bt[i]=read(),T[i]=read();
    rep(i,1,K){
        memcpy(dp[i],dp[i-1],sizeof(dp[i]));
        rep(t,1,n){
            memset(f,0,sizeof(f)),memset(g,0,sizeof(g));
            f[t]=g[t]=1;
            rep(j,1,Q){
                if(bs[j]==i&&S[j]==t)f[j+n]=1;
                if(bt[j]==i&&T[j]==t)g[j+n]=1;
            }
            rep(u,1,n+Q){
                rep(v,1,n){
                    if(s[v][t]=='1')f[u]=(f[u]+dp[i-1][u][v])%Mod;
                }
            }
            rep(u,1,n+Q){
                rep(v,1,n){
                    if(s[t][v]=='1')g[u]=(g[u]+dp[i-1][v][u])%Mod;
                }
            }
            rep(u,1,n+Q){
                rep(v,1,n+Q)dp[i][u][v]=(dp[i][u][v]+f[u]*g[v])%Mod;
            }
        }
    }
    rep(i,1,Q)write(dp[K][i+n][i+n]),putchar('\n');
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# P7155 题解



**题目大意**

> 给一张 $n$ 个点的有向图，你有 $m$ 个按钮，每走一条边都要按一次按钮，按完按钮 $i$ 后 $i$ 不能按，且 $<i$ 的按钮可以按。
>
> $q$ 次询问 $u\to v$ 且在 $v$ 上要按 $b_u$，到 $v$ 后要按 $b_v$ 有多少种路径。
>
> 数据范围 $n,m,q\le 60$。

**思路分析**

注意到整条路径上最高位只会被按一次，因为一个按钮第二次可按意味着一定有一个更高的按钮被按。

设 $dp_{h,i,j}$ 表示按最高位为 $h$，$i\to j$ 的方案数，转移为：
$$
dp_{h,i,j}=\sum_{(u\to k)\in E}\sum_{(k\to v)\in E} dp_{h-1,i,u}\times dp_{h-1,v,j}
$$
注意到两个求和号无关，枚举 $k$ 后分别处理 $i/j$ 出发的方案数即可。

然后考虑怎么回答询问，考虑拆点：对于询问 $i$，设成节点 $i+q$，$k=u_i,h=bu_i$ 时才转移 $dp_{h-1,k,j}\to dp_{h,i+n,j}$，另一侧同理。

时间复杂度 $\mathcal O(nm(n+q)^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MOD=1e9+7;
int dp[2][128][128]; //dp[h][i][j]: max digit = h, path i -> j
int f[128],g[128]; //f[i] = sum(dp[h-1][i][u]*E[u->k]), g[i] = sum(dp[h-1][u][i]*E[k->u])
int bs[64],vs[64],bt[64],vt[64];
bool G[64][64];
inline void add(int &x,int y) { x=(x+y>=MOD)?x+y-MOD:x+y; }
signed main() {
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) scanf("%1d",&G[i][j]);
	for(int i=1;i<=q;++i) scanf("%d%d%d%d",&bs[i],&vs[i],&bt[i],&vt[i]);
	for(int h=1;h<=m;++h) {
		int cur=h&1;
		memcpy(dp[cur],dp[cur^1],sizeof(dp[cur]));
		for(int k=1;k<=n;++k) {
			memset(f,0,sizeof(f)),memset(g,0,sizeof(g)),f[k]=g[k]=1;
			for(int i=1;i<=q;++i) if(bs[i]==h&&vs[i]==k) f[i+n]=1;
			for(int i=1;i<=q;++i) if(bt[i]==h&&vt[i]==k) g[i+n]=1;
			for(int u=1;u<=n;++u) if(G[u][k]) {
				for(int i=1;i<=n+q;++i) add(f[i],dp[cur^1][i][u]);
			}
			for(int u=1;u<=n;++u) if(G[k][u]) {
				for(int i=1;i<=n+q;++i) add(g[i],dp[cur^1][u][i]);
			}
			for(int i=1;i<=n+q;++i) for(int j=1;j<=n+q;++j) add(dp[cur][i][j],1ll*f[i]*g[j]%MOD);
		}
	}
	for(int i=1;i<=q;++i) printf("%d\n",dp[m&1][i+n][i+n]);
	return 0;
}
```

---

## 作者：Anonymely (赞：0)

感觉思路很自然！

首先考虑操作序列，最大值只有一个，按照最大值分割之后递归到子问题，这启发我们记录最大值是多少即可，记 $f_{i,j,k}$ 表示从 $i$ 到 $j$ 最大值为 $k$，转移枚举最大值所在位置 $t$，并选择 $u,v$ 满足 $(u,t),(t,v)$ 即可，两维独立即可优化到 $n^4$，而每组询问也是特殊情况，塞到 $n$ 个点里面一起跑即可。


```cpp
#include <bits/stdc++.h>
using namespace std;

#define QwQ01AwA return 0
#define ll long long
#define look_time cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n'
template <typename T> void ckmax(T &x, const T y) {x = max(x, y);}
template <typename T> void ckmin(T &x, const T y) {x = min(x, y);}

const int N = 125;
const int mod = 1e9 + 7;
int n, m, q;
int f[N][N][N], g[N], h[N];
int e[N][N];
int s[N], t[N], bs[N], bt[N];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        s = " " + s;
        for (int j = 1; j <= n; j++) {
            e[i][j] = (s[j] == '1');
        }
    }
    for (int i = 1; i <= q; i++) cin >> bs[i] >> s[i] >> bt[i] >> t[i];
    for (int p = 1; p <= m; p++) {
        for (int i = 1; i <= n + q; i++) {
            for (int j = 1; j <= n + q; j++) {
                f[p][i][j] = f[p - 1][i][j];
            }
        }
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) g[i] = h[i] = 0;
            g[k] = h[k] = 1;
            for (int i = 1; i <= q; i++) g[i + n] = (k == s[i] && p == bs[i]);
            for (int i = 1; i <= q; i++) h[i + n] = (k == t[i] && p == bt[i]);
            for (int i = 1; i <= n + q; i++) {
                for (int j = 1; j <= n; j++) {
                    if (e[j][k]) (g[i] += f[p - 1][i][j]) %= mod;
                }
            }
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n + q; j++) {
                    if (e[k][i]) (h[j] += f[p - 1][i][j]) %= mod;
                }
            }
            for (int i = 1; i <= n + q; i++) {
                for (int j = 1; j <= n + q; j++) {
                    (f[p][i][j] += 1ll * g[i] * h[j] % mod) %= mod;
                }
            }
        }
    }
    for (int i = 1; i <= q; i++) cout << f[m][i + n][i + n] << '\n';
    QwQ01AwA;
}
```

---

