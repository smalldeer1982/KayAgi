# [AGC061E] Increment or XOR

## 题目描述

有一个非负整数 $X$，初始值为 $S$。你可以以任意顺序、任意次数执行以下操作：

- 给 $X$ 加 $1$。该操作的代价为 $A$。
- 选择一个 $1$ 到 $N$ 之间的 $i$，将 $X$ 替换为 $X \oplus Y_i$。该操作的代价为 $C_i$。这里，$\oplus$ 表示按位异或运算。

请你求出将 $X$ 变为给定非负整数 $T$ 所需的最小总代价，或者报告无法达成目标。

按位异或运算的定义如下：  
对于非负整数 $A, B$，$A \oplus B$ 的二进制表示中，第 $2^k$ 位（$k \geq 0$）的数，如果 $A$ 和 $B$ 的该位只有一个为 $1$，则结果为 $1$，否则为 $0$。

例如，$3 \oplus 5 = 6$（二进制为：$011 \oplus 101 = 110$）。  
一般地，$k$ 个非负整数 $p_1, p_2, p_3, \dots, p_k$ 的按位异或为 $(\dots((p_1 \oplus p_2) \oplus p_3) \oplus \dots \oplus p_k)$，并且可以证明，这个结果与顺序无关。

## 说明/提示

### 限制条件

- $1 \leq N \leq 8$
- $0 \leq S, T < 2^{40}$
- $0 \leq A \leq 10^5$
- $0 \leq Y_i < 2^{40}$（$1 \leq i \leq N$）
- $0 \leq C_i \leq 10^{16}$（$1 \leq i \leq N$）
- 输入中的所有值均为整数。

### 样例解释 1

可以通过以下方式将 $X$ 变为 $T$：  
- 选择 $i=1$，将 $X$ 替换为 $X \oplus 8$，此时 $X=7$，代价为 $2$。  
- 给 $X$ 加 $1$，此时 $X=8$，代价为 $1$。  
- 选择 $i=1$，将 $X$ 替换为 $X \oplus 8$，此时 $X=0$，代价为 $2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 15 0 1
8 2```

### 输出

```
5```

## 样例 #2

### 输入

```
3 21 10 100
30 1
12 1
13 1```

### 输出

```
3```

## 样例 #3

### 输入

```
1 2 0 1
1 1```

### 输出

```
-1```

## 样例 #4

### 输入

```
8 352217 670575 84912
239445 2866
537211 16
21812 6904
50574 8842
380870 5047
475646 8924
188204 2273
429397 4854```

### 输出

```
563645```

# 题解

## 作者：Rainbow_qwq (赞：12)

最近回顾了一下 [Picks loves segment tree IX](https://uoj.ac/problem/659)，然后终于会做这题了，其实两题在思维上有很大的相似之处。

核心思想是划分阶段的问题。

分析一下 $+1$ 的操作，应该怎么考虑：

看作 bitxor 一段 $1$：这样需要记录末尾 $1$ 的连续个数（最低的一个 $0$ 在哪里），不太好做。

转换一下思路，$+1$ 会把最后一段 $1$ 用 $0$ 清空，接下来的过程从一段 $0$ 开始。状态里记录末尾 $0$ 的个数。（这跟上面链接那题差不多）

状态记录末尾 $0$ 的个数有什么好处？因为这是适应 $+1$ 操作的子结构，某次 $+1$ 后会把 $[0,i]$ 清空，形成了一个**子问题**（从 $0$ 到某个状态），初始状态就只要考虑 $S/0$ 两种。

并且，在 $+1$ 操作冲破第 $i$ 位前，第 $i$ 位都不受影响，这意味着在状态中额外记录 每个 $Y_i$ 被 XOR 了奇数还是偶数次，第 $i$ 位就确定了。

这体现了 $+1$ 操作的单调性：在冲到第 $i$ 位前第 $i$ 位都不受影响，冲到第 $i$ 位后起点统一变成 $[0,i]$ 全是 $0$ 的状态。

根据单调性，可以设计从低位 dp 转移到高位的状态。下面分析一下变化的阶段。

对于最下面的若干位，整个过程是从 $S\to 0\to T$ 的。

初始状态有两种，$0\sim i-1$ 位从 $S$ 开始和从 $0$ 开始。

结束状态有两种，$0\sim i-1$ 位和 $T$ 相同且不向 $i$ 进位；$0\sim i-1$ 位清成全 $0$ 并往上进一位。

设 $f(i,0/1,0/1,msk)$ 表示只考虑最低的 $0\sim i-1$ 位（即 $+1$ 时**不能影响更上面的位**），起点的两个情况（$0/1$ 表示 $S/0$ 开始），终点的两个情况（$0/1$ 表示 $T$ 结束并不进位 / $0$ 结束并进位），在这个变化过程中 $msk$ 集合的 $Y_i$ 被 XOR 了奇数次。

从 $f(i)$ 转移到 $f(i+1)$：

转移 1：如果（进位/不进位了之后）第 $i$ 位是匹配的，可直接转移到 $f(i+1,j_0,j_1,msk)$。

转移 2：考虑进行了新的进位操作的转移。

- 先调用 $f(i,j_0,1,msk)$ 操作，条件是从 $j_0$ 开始，这个操作完后第 $i$ 位是 $1$（即进位只进到第 $i$ 位，不能影响上面的位）。
- 然后调用若干次 $f(i,1,1,msk)$ 进位操作，条件是这个操作完后第 $i$ 位是 $1$（即进位只进到第 $i$ 位，不能影响上面的位）。
- 最后调用一次 $f(i,1,j_1,msk)$ 操作，条件是进到第 $i$ 位时符合 $j_1$ 的要求。

转移写出来就是 $f(i,j_0,1,msk_0)+f(i,1,1,msk_1)+f(i,1,1,msk_2)+...+f(i,1,j_1,msk_l) \to f(i+1,j_0,j_1,\oplus\ msk)$。

容易发现这是一个最短路的形式，可以用 dijkstra 的方式，每次从 dp 数组中取出最小的未用过的一个，转移到其他所有的，一次 dp 复杂度就是 $2^{2n}$。

初始状态不需要任何一位匹配，就是 $f(0,j,0,msk)=\sum_{x\in msk}C_x,f(0,j,1,msk)=\sum_{x\in msk}C_x+A$。

最终答案就是 $\min(f_{40,0,0,msk})$，于是总复杂度 $O(2^{2n}\log V)$。

[Submission](https://atcoder.jp/contests/agc061/submissions/40969427)

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
#define int long long
using namespace std;

#define maxn 800005
#define inf 0x3f3f3f3f3f3f3f3f

int n,S,T,A,mxs;
int x[66],c[66],sx[666],sc[666];

int f[42][2][2][260],g[260];
bool vis[260];

signed main()
{
	n=read(),S=read(),T=read(),A=read(),mxs=1<<n;
	For(i,0,n-1)x[i]=read(),c[i]=read();
	For(s,0,mxs-1)
		For(i,0,n-1)
			if(s>>i&1)sx[s]^=x[i],sc[s]+=c[i];
	memset(f,63,sizeof f);
	For(s,0,mxs-1)
		For(i,0,1) For(j,0,1) f[0][i][j][s]=sc[s]+A*j;
	For(i,0,39){
		// from a to b
		For(j0,0,1)For(j1,0,1){
			int a=j0?0:(S>>i&1);
			int b=j1?1:(T>>i&1);
			For(s,0,mxs-1)
				if((sx[s]>>i&1)==(a^b))
					f[i+1][j0][j1][s]=f[i][j0][j1][s];
		}
		For(j0,0,1){
			int a=j0?0:(S>>i&1);
			memset(g,63,sizeof g);
			memset(vis,0,sizeof vis);
			For(s,0,mxs-1)
				if((sx[s]>>i&1)==a) g[s]=f[i][j0][1][s];
			while(1){
				int mn=inf,u=-1;
				For(s,0,mxs-1)
					if(!vis[s] && g[s]<mn)mn=g[s],u=s;
				if(u==-1)break;
				vis[u]=1;
				For(s,0,mxs-1)
					if((sx[s]>>i&1)==1)
						g[s^u]=min(g[s^u],g[u]+f[i][1][1][s]); 
				For(j1,0,1){
					int b=j1?1:(T>>i&1);
					For(s,0,mxs-1)
						if((sx[s]>>i&1)==(b^1))
							f[i+1][j0][j1][u^s]=min(g[u]+f[i][1][j1][s],f[i+1][j0][j1][u^s]);
				}
			}
		}
	}
	int res=inf;
	For(i,0,mxs-1)res=min(res,f[40][0][0][i]);
	if(res==inf)puts("-1");
	else cout<<res;
	return 0;
}
```

---

## 作者：苹果蓝17 (赞：5)

考虑逐位处理。假设只考虑第 $0,1,\cdots,k$ 位，关注整个过程中第 $k-1$ 位是否向第 $k$ 位进位：

- 第 $k-1$ 位没有向第 $k$ 位进位，那么只需要知道每种操作被使用次数的奇偶性就可以得知第 $k$ 位的值。

- 第 $k-1$ 位没有向第 $k$ 位进位，那么一定存在一个时刻（即进位后的一瞬间）使得后 $k$ 位均为 $0$。

设 $dp_{k,id1,id2,mask}$ 表示只考虑第 $0,1,\cdots,k-1$ 位，某个状态下代价最小值，其中 $id_1$ 表示初始状态（为 $0$ 表示 $S$，为 $1$ 表示 $0$），$id_2$ 表示终止状态（为 $0$ 表示 $T$ 且要求整个过程中不向第 $k$ 位进位，为 $1$ 表示 $0$ 且仅在最后一次操作中进位），$mask$ 表示每种操作被使用次数的奇偶性。

由 $k$ 转移到 $k+1$，转移同样有两种：

- 若不进位，则若第 $k$ 位匹配就有 $dp_{k,id_1,id_2,mask} \rightarrow dp_{k+1,id_1,id_2,mask}$。

- 若进位，则整个过程一定形如 $S \rightarrow 100 \cdots 0 \rightarrow \cdots \rightarrow 100 \cdots 0 \rightarrow T$。有转移 $dp_{k,id1,1,mask_1}+dp_{k,1,1,mask_2}+\cdots+dp_{k,1,1,mask_{t-1}}+dp_{k,1,id_2,mask_t} \rightarrow dp_{k+1,id_1,id_2,\oplus mask_i}$。注意每一步均要维护第 $k$ 位匹配。

第二种转移可以使用类似 Dijkstra 算法的方式，当然不需要优先队列优化，每一次暴力找出最小值转移即可。

初始状态 $dp_{0,id_1,0,mask}=\sum_{i \in mask} C_i$，$dp_{0,id_1,1,mask}=A+\sum_{i \in mask} C_i$，这可以理解为 $0.5$ 进位至 $1$（实际上就是直接加 $1$，为了方便转移理解为进位），这也是 $A$ 唯一出现的地方。

总时间复杂度 $O(4^n \log W)$。

[**Code**](https://atcoder.jp/contests/agc061/submissions/39099539)

---

## 作者：DaiRuiChen007 (赞：4)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc061_e)

**题目大意**

> 给定 $x$，以及 $n$ 个操作 $(q_i,w_i)$，你可以进行如下操作：
>
> - $x\gets x+1$ 代价为 $c$。
> - $x\gets x\oplus q_i$ 代价为 $w_i$。
>
> 求让 $x$ 从 $s$ 变成 $t$ 的最小代价。
>
> 数据范围：$n\le 8,s,t,q_i\le 2^{40}$。

**思路分析**



考虑观察结构：先看最高位 $k$，注意到每次进位后低 $k-1$ 位都会全部变成 $0$，按照 $k-1$ 每次进位分割，从 $s_k$ 开始，每次进位之前第 $k$ 位都是 $0$，然后变成 $1$，最终成为 $t_k$（且不能进位）。

那么观察第 $k-1$ 位需要哪些结构：我们需要考虑从 $s_k$ 开始的情况，由于每次进位后相当于从 $s=0$ 重新出发，因此还要考虑从 $0$ 开始的情况，而最终要么到达 $t_k$ 要么进位变成 $2^k$（低 $k-1$ 位全部变成 $0$）。

不断递归，我们可以大概得出一个子结构：$f_{k,x,y,S}$ 表示当前考虑了 $k$ 位，$S$ 是使用次数位奇数的异或操作数，$x\in\{0,1\}$ 表示起点是 $s_k/0$，$y\in\{0,1\}$ 表示终点是 $t_k/2^{k+1}$。

先考虑边界条件：$f_{-1,x,y,S}=w_S+y\times C$（$w_S$ 表示 $S$ 内部操作之和）。

每次转移 $f_{k-1}\to f_k$ 考虑两种情况：有进位或没进位。

如果没进位，那么要求 $x$ 对应的起点异或上 $S$ 内的元素得到第 $k$ 位恰为 $y$ 对应的终点（$y=1$ 时要求第 $k$ 位恰好为 $1$，这样加上进位后还能向 $k+1$ 进位）。

如果有进位那么相当于 $f_{k+1,x,y,\oplus_{i=1}^m S_i}\gets f_{x,1,S_1}+ f_{1,1,S_2}+\cdots+f_{1,1,S_{m-1}}+f_{1,y,S_m}$，即中间每次都在进位，但是不能对高位有影响，因此中间部分每个 $S_i$ 第 $k$ 位必须是 $1$，这样就能通过异或消掉 $f_{k,1,1,S_{i-1}}$ 进位的贡献，然后再接受 $f_{k,1,1,S_i}$ 的进位且保持不对更高位进位。

注意到转移形式类似最短路，Dijkstra 处理即可。

时间复杂度 $\mathcal O(2^{2n}\log V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll inf=1e18;
ll n,S,T,C,a[8],c[8],q[1<<8],w[1<<8],f[2][2][1<<8],g[2][2][1<<8],d[1<<8];
//x:start=s/0, y: end=t/2^k+1
bool vis[1<<8];
int dg(ll s,int k) { return (s>>k)&1; }
signed main() {
	scanf("%lld%lld%lld%lld",&n,&S,&T,&C);
	for(int i=0;i<n;++i) scanf("%lld%lld",&a[i],&c[i]);
	for(int s=0;s<(1<<n);++s) for(int i=0;i<n;++i) if(s&(1<<i)) {
		q[s]^=a[i],w[s]+=c[i];
	}
	for(int s=0;s<(1<<n);++s) for(int x:{0,1}) for(int y:{0,1}) f[x][y][s]=w[s]+y*C;
	for(int k=0;k<40;++k) {
		memset(g,0x3f,sizeof(g));
		array<int,2> u={dg(S,k),0},v={dg(T,k),1};
		for(int s=0;s<(1<<n);++s) for(int x:{0,1}) for(int y:{0,1}) {
			if((u[x]^dg(q[s],k))==v[y]) g[x][y][s]=f[x][y][s];
		}
		for(int x:{0,1}) {
			memset(d,0x3f,sizeof(d));
			memset(vis,false,sizeof(vis));
			for(int s=0;s<(1<<n);++s) if(dg(q[s],k)==u[x]) d[s]=f[x][1][s];
			while(true) {
				int p=-1;
				for(int s=0;s<(1<<n);++s) if(!vis[s]&&(p==-1||d[p]>d[s])) p=s;
				if(p==-1||d[p]>=inf) break;
				vis[p]=true;
				for(int s=0;s<(1<<n);++s) if(!vis[p^s]&&dg(q[s],k)) d[p^s]=min(d[p^s],d[p]+f[1][1][s]);
				for(int s=0;s<(1<<n);++s) for(int y:{0,1}) if((dg(q[s],k)^1)==v[y]) {
					g[x][y][p^s]=min(g[x][y][p^s],d[p]+f[1][y][s]);
				}
			}
		}
		memcpy(f,g,sizeof(f));
	}
	ll ans=*min_element(f[0][0],f[0][0]+(1<<n));
	printf("%lld",ans>=inf?-1ll:ans);
	return 0;
}
```

---

## 作者：jun头吉吉 (赞：3)

## 题意
给定 $N,A,S,T,C_{1,\dots,N},Y_{1,\dots,N}$，初始手上有一个 $S$，每次可以：

- 给 $S$ 加上 $1$，代价为 $A$；
- 给 $S$ 异或上 $Y_i$，代价为 $C_i$。

最小化把 $S$ 变成 $T$ 的代价或者报告无解。

$1\le N\le 8,0\le S,T,Y_i<2^{40},0\le A\le 10^5,0\le C_i\le 10^{16}$

## 题解

我们考虑一个子问题，叫做 $(k,s,t,m)$，大意是这样的：

低 $k$ 位 $X$ 和 $Y$ 相同。如果 $s=0$ 则 $X=S$ 否则 $X=0$。如果 $t=0$ 则 $Y=T$ 且 $k-1$ 位没有向 $k$ 进位，否则 $Y=0$ 且向 $k$ 进位（这个进位一定是最后一步加一，否则之前就有进位就已经得到全部为 $0$ 了）。然后 $m$ 中的数异或了奇数次否则是偶数次。

记 $cost(k,s,t,m)$ 表示这个子问题的最小代价。初始值是这样的：

- $cost(0,s,0,m)=\sum _{i\in m}C_i$
- $cost(0,s,1,m)=\sum_{i\in m}C_i+A$。（加一可以看做是 $-1$ 向 $0$ 进位）

最后要求的是 $\min cost(B,0,0,?)$。其中 $B=40$。

考虑怎么从 $cost(k,?,?,?)$ 转移到 $cost(k+1,?,?,?)$。

首先如果 $k-1\to k$ 没有进位，并且这一位 $X$ 经过 $m$ 中的数异或后得到的就是 $Y$，转移就是 $cost(k+1,s,0,m)\leftarrow cost(k,s,0,m)$。

然后如果 $k-1\to k$ 进位了，并且这一位 $X$ 经过 $m$ 中的数异或后得到 $1$，那么加上上一个进位就又进位了，所以就是 $cost(k+1,s,1,m)\leftarrow cost(k,s,1,m)$。

否则过程就类似于  经过 $k-1$ 的子问题，当前位为 $0$ $\to $ 进位使得当前位为 $1$ $\to $ 经过 $k-1$ 的子问题，当前位为 $0$ $\to$ 进位使得当前位为 $1$ $\to \dots$。写成形式化的形式就是 $cost(k+1,s,t,\bigoplus_{i=0}^{l}m_i)\leftarrow cost(k,s,1,m_0)+cost(k,1,1,m_1)+\dots+cost(k,1,1,m_{l-1})+cost(k,1,t,m_l)$。限制条件是每一次进位的时候当前位都是 $0$（最后一次除外）。这个转移是一个最短路的形式，用朴素的 Dijkstra 复杂度为 $2^{2N}$。

所以整个题目的复杂度为 $\mathcal O(B2^{2N})$。

## 代码
```cpp
#define h(x,k) ((x)>>(k)&1)
const int N=8;const ll inf=0x3f3f3f3f3f3f3f3f;
int n,A;ll S,T,y[N],c[N],v[1<<N],f[2][2][1<<N],g[2][2][1<<N],dis[1<<N],ans=inf;bool vis[1<<N];
signed main(){
	read(n,S,T,A);for(int i=0;i<n;i++)read(y[i],c[i]);
	for(int m=0;m<(1<<n);m++)for(int i=0;i<n;i++)if(m>>i&1)v[m]^=y[i];
	for(int s=0;s<2;s++)for(int m=0;m<(1<<n);m++){
		for(int i=0;i<n;i++)if(m>>i&1)f[s][0][m]+=c[i];
		f[s][1][m]=f[s][0][m]+A;
	}
	for(int k=0;k<40;k++){
		memcpy(g,f,sizeof f);memset(f,0x3f,sizeof f);
		for(int s=0;s<2;s++){
			memset(dis,0x3f,sizeof dis);memset(vis,0,sizeof vis);
			for(int m=0;m<(1<<n);m++)
				if(!h((s?0:S)^v[m],k))dis[m]=g[s][1][m];
				else chkmn(f[s][1][m],g[s][1][m]);
			while(1){
				pair<ll,int>mn(inf,-1);
				for(int m=0;m<(1<<n);m++)if(!vis[m])chkmn(mn,mp(dis[m],m));
				int m=mn.se;if(m==-1)break;else vis[m]=1;
				for(int mm=0;mm<(1<<n);mm++)if(h(v[mm],k))chkmn(dis[m^mm],dis[m]+g[1][1][mm]);
			}
			for(int m=0;m<(1<<n);m++)for(int mm=0;mm<(1<<n);mm++){
				if(h(T^v[mm],k))chkmn(f[s][0][m^mm],dis[m]+g[1][0][mm]);
				if(!h(v[mm],k))chkmn(f[s][1][m^mm],dis[m]+g[1][1][mm]);
			}
			for(int m=0;m<(1<<n);m++)
				if(h((s?0:S)^v[m],k)==h(T,k))chkmn(f[s][0][m],g[s][0][m]);
		}
	}
	ll ans=*min_element(f[0][0],f[0][0]+(1<<n));
	write(ans==inf?-1:ans);
}
```

---

## 作者：Cx114514 (赞：2)

### 题目链接：[[AGC061E] Increment or XOR](https://www.luogu.com.cn/problem/AT_agc061_e)
乍看题目无从下手，但不难注意到一个特殊的地方：$n\le 8$。且在不进行 $+1$ 操作的时候，只要知道每种 $xor$ 操作的奇偶性，即可还原出该数，遂考虑状压 DP。

接下来考虑 $+1$ 操作。对于每次 $+1$ 操作，均可以看作把最低位连续的若干个 $1$ 变为 $0$ 并向高位进位。

考虑对于最低的 $i$ 位。

初始状态有两种：与 $S$ 相同或全是 $0$。

结束状态也有两种：与 $T$ 相同或进行一次进位后全是 $0$。

设 $f_{i,0/1,0/1,S}$ 表示**最低的 $i$ 位，从 $S$ / 全是 $0$ 开始，在 $T$ / 进位并全是 $0$ 结束，进行的操作奇偶性是 $S$** 的最小代价。

考虑转移。

对于最低的 $i$ 位，整个操作一定形如：

$S\to 0 \to 0 \to \cdots \to T$

（$0$ 代表最低的 $i$ 位全为 $0$）

这个时候可能有人会问：从 $S\to T$ 不是直接 $S\to 0 \to T$ 就可以了吗？

因为对于每一个 $0$ 都代表了在当前位上的一次进位，在任意一位上，都有可能进位多次。

形式化转移如下：

$f_{i,j,k,\oplus_{i=1}^{l} S_{i}}=f_{i-1,j,1,S_{1}}+\sum\limits_{i=2}^{l-1}f_{i-1,1,1,S_{i}}+f_{i-1,1,k,S_{l}}$

这是一个最短路的形式，可以用 dijkstra 辅助转移。

初始状态：$f_{0,0/1,0,S}=\sum\limits_{i\in S}c_{i}$，$f_{0,0/1,1,S}=\sum\limits_{i\in S}c_{i}+A$。

时间复杂度为 $O\left(2^{2n}\log V\right)$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, s, t, a, ans = 1145141919810000000, y[15], c[15], xr[1005], dis[1005], f[45][5][5][1005];

bool vis[1005];

signed main()
{
	cin >> n >> s >> t >> a;
	for (int i = 1; i <= n; i++)
		cin >> y[i] >> c[i];
	for (int i = 0; i < (1 << n); i++)
	{
		
		int sum = 0;
		for (int j = 1; j <= n; j++)
			if (i & (1 << (j - 1))) sum += c[j];
		for (int j = 1; j <= n; j++)
			if (i & (1 << (j - 1))) xr[i] ^= y[j];
		f[0][0][0][i] = f[0][1][0][i] = sum;
		f[0][0][1][i] = f[0][1][1][i] = sum + a;
	}
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j <= 1; j++)
			for (int k = 0; k <= 1; k++)
			{
				int X = j ? 0 : (s >> i & 1);
				int Y = k ? 1 : (t >> i & 1);
				for (int l = 0; l < (1 << n); l++)
					if ((xr[l] >> i & 1) == (X ^ Y)) f[i + 1][j][k][l] = f[i][j][k][l];
					else f[i + 1][j][k][l] = 1145141919810000000;
			}
		for (int j = 0; j <= 1; j++)
		{
			int X = j ? 0 : (s >> i & 1);
			for (int k = 0; k < (1 << n); k++)
				dis[k] = 1145141919810000000;
			for (int k = 0; k < (1 << n); k++)
				vis[k] = 0;
			for (int k = 0; k < (1 << n); k++)
				if ((xr[k] >> i & 1) == X) dis[k] = f[i][j][1][k];
			while (1)
			{
				int minn = 1145141919810000000, minx = -1;
				for (int k = 0; k < (1 << n); k++)
					if (!vis[k] && dis[k] < minn)
					{
						minn = dis[k];
						minx = k;
					}
				if (minx == -1) break;
				vis[minx] = 1;
				for (int k = 0; k < (1 << n); k++)
					if ((xr[k] >> i & 1) == 1) dis[k ^ minx] = min(dis[k ^ minx], dis[minx] + f[i][1][1][k]);
				for (int k = 0; k <= 1; k++)
				{
					int Y = (k ? 1 : (t >> i & 1));
					for (int l = 0; l < (1 << n); l++)
						if ((xr[l] >> i & 1) == (Y ^ 1)) f[i + 1][j][k][l ^ minx] = min(f[i + 1][j][k][l ^ minx], dis[minx] + f[i][1][k][l]);
				}
			}
		}
	}
	for (int i = 0; i < (1 << n); i++)
		ans = min(ans, f[40][0][0][i]);
	if (ans == 1145141919810000000) cout << -1 << endl;
	else cout << ans << endl;
	return 0;
}
```

---

## 作者：Larunatrecy (赞：2)

### [AGC061E Increment or XOR](https://www.luogu.com.cn/problem/AT_agc061_e)

每个时刻被 $+1$ 操作影响的一定是一些低位，而高位只和每种操作数量的奇偶性有关。

并且我们可以发现，在 $+1$ 操作向更高位影响时，低位一定全是 $1$，然后全变成 $0$。

那么我们可以设计一个 `dp`，$f_{i,u,s,t}$ 表示当前被 $+1$ 操作影响到的最高位是 $i$，每种操作奇偶性的状态是 $u$，$s$ 和 $t$ 分别代表低位的起始状态和终止状态。

由上面可以知道，$s$ 要么和 $S$ 相同，要么全是 $0$，$t$ 要么全是 $1$，要么和 $T$ 相同，都可以只用 $0/1$ 表示。

考虑怎么从 $f_i$ 转移到 $f_{i+1}$：

- 从始至终没有向第 $i+1$ 进位，那么就只和 $u$ 有关。
- 否则的话，一定是从某个其实状态 $s$ 先进行若干操作变成全 $1$，然后 $+1$，然后再进行若干次操作变成全 $1$，即 $f_{i,u_1,s,1}+f_{i,u_2,1,1}……+f_{i,u_k,1,t}$，当然需要保证从始至终不向 $i+2$ 进位，这个转移是一个最短路的形式，我们用 `dij`，每次取最小值更新别的状态即可。

复杂度 $O(4^n\log{V})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = (1<<8)+7;
const int M = 44;
template <typename T>inline void read(T &x)
{
    x=0;char c=getchar();bool f=0;
    for(;c<'0'||c>'9';c=getchar())f|=(c=='-');
    for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c-'0');
    x=(f?-x:x);
}
int n;
typedef long long LL;
LL Y[M],C[M],A,S,T;
LL dp[M][N][2][2],cost[N],val[N];
int get(LL x,int i){return (x>>(i-1))&1;}
int valS[2][M],valT[2][M];
bool used[N];
LL dis[N];
const LL inf = 1e18;
int main()
{
    read(n);read(S);read(T);read(A);
    for(int i=0;i<n;i++)
    {
        read(Y[i]);
        read(C[i]);
    }
    for(int s=0;s<(1<<n);s++)
    for(int i=0;i<n;i++)
    if((s>>i)&1)
    {
        val[s]^=Y[i];
        cost[s]+=C[i];
    }
    int lim=42;
    for(int i=0;i<=lim;i++)
    for(int u=0;u<(1<<n);u++)
    for(int s=0;s<=1;s++)
    for(int t=0;t<=1;t++)
    dp[i][u][s][t]=inf;
    for(int u=0;u<(1<<n);u++)
    for(int s=0;s<=1;s++)
    for(int t=0;t<=1;t++)
    dp[0][u][s][t]=cost[u];
    for(int i=1;i<=lim;i++)
    {
        valS[0][i]=get(S,i);valS[1][i]=0;
        valT[0][i]=get(T,i);valT[1][i]=1;
    }
    for(int i=1;i<=lim;i++)
    {
        for(int u=0;u<(1<<n);u++)
        for(int s=0;s<=1;s++)
        for(int t=0;t<=1;t++)
        {
            if((valS[s][i]^get(val[u],i))==valT[t][i])
            dp[i][u][s][t]=dp[i-1][u][s][t];
        }
        for(int l=0;l<=1;l++)
        {
            for(int u=0;u<(1<<n);u++)
            {
                used[u]=0;
                dis[u]=inf;
                if((valS[l][i]^get(val[u],i))==0)
                dis[u]=min(dis[u],dp[i-1][u][l][1]+A);
            }
            while(1)
            {
                int x=-1;
                for(int u=0;u<(1<<n);u++)
                if(!used[u]&&(x==-1||dis[u]<dis[x]))x=u;
                if(x==-1)break;
                used[x]=1;
                for(int u=0;u<(1<<n);u++)
                if(get(val[u],i)==1)
                dis[x^u]=min(dis[x^u],dis[x]+dp[i-1][u][1][1]+A);
            }
            for(int u=0;u<(1<<n);u++)
            for(int v=0;v<(1<<n);v++)
            for(int r=0;r<=1;r++)
            if((get(val[v],i)^1)==valT[r][i])
            dp[i][u^v][l][r]=min(dp[i][u^v][l][r],dis[u]+dp[i-1][v][1][r]);
        }
    }
    LL ans=inf;
    for(int u=0;u<(1<<n);u++)
    ans=min(ans,dp[lim][u][0][0]);
    if(ans==inf)ans=-1;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：lalaouye (赞：2)

题目中涉及到了加法和异或，一个是进位加法，一个是不进位加法，显得很不可做。

但是我们注意到加法只加 $1$，如果产生进位了，那会将末尾的所有 $1$ 推平成 $0$，而如果没有进位，则后面的位不会受到加法影响。

这启发我们挖掘这道题的过程。我们发现这个过程形似可以从低位推到高位，并且过程中会有很多整个后缀全部为 $0$ 的状态。那么我们可以将过程分成若干个阶段阶段，并且发现，在 $[0,i-1]$ 位还未产生进位时，处理 $[i,40]$ 位的异或操作是简单的，只需要记录每个异或操作次数的奇偶性即可，因为他们不会收到加法影响，那么我们考虑 dp，设 $f_{i,0/1,0/1,s}$ 表示考虑 $[0,i-1]$ 位，初始状态是 $S$ 或全 $0$，末尾状态是 $T$ 或进位，异或操作的奇偶性为 $S$，从初始状态到末尾状态的最小代价。

我们发现这个状态设计是足够的，现在考虑转移。

首先，第 $i$ 位若可以直接匹配状态，直接转移就行，挨个讨论即可。

现在开始考虑需要多次进位的转移。首先，由于会出现进位，若我们要转移 $f_{i+1,x,y,S}$，首先我们显然要从 $f_{i,x,1,S_0}$ 开始，然后，我们接下来将会进行一系列的异或和加法操作，在此过程中我们需控制进位只能在第 $i$ 位进位，不能影响到最后的位置。最后，我们再以一个 $f_{i,1,y,S_{m+1}}$ 的操作完成转移，$m$ 表示中间的综合操作的次数，那么转移方程就呼之欲出了：

$$f_{i+1,x,y,\bigoplus_{j=0}^{m+1} S_j}=f_{i,x,1,S_0}+f_{i,1,y,S_{m+1}}+\sum_{j=1}^m f_{i,1,1,S_j}$$

我们发现这个转移的形式其实是一个最短路形式，那么我们可以用 dijkstra 的方式去转移，最后答案为 $\min(f_{40,0,0,S})$，时间复杂度 $\mathcal{O}(2^{2n}\log V)$。

---

