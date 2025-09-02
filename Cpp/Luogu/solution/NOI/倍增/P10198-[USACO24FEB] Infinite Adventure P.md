# [USACO24FEB] Infinite Adventure P

## 题目背景

**注意：本题的内存限制为 512MB，通常限制的 2 倍。**

## 题目描述

Bessie 正在计划一次在 $N$（$1\le N\le 10^5$）个城市的大陆上的无尽冒险。每个城市 $i$ 都有一个传送门以及循环周期 $T_i$。所有 $T_i$ 均为 $2$ 的幂，且 $T_1+\cdots+T_N\le 10^5$。如果你在日期 $t$ 进入城市 $i$ 的传送门，那么你会立即从城市 $c_{i,t\bmod T_i}$ 的传送门出来。

Bessie 的旅行有 $Q$（$1\le Q\le 5\cdot 10^4$）个计划，每个计划由一个元组 $(v,t,\Delta)$ 组成。在每个计划中，她将于日期 $t$ 从城市 $v$ 出发。然后，她将执行以下操作 $\Delta$ 次：她将进入当前城市的传送门，然后等待一天。对于她的每一个计划，她想要知道她最终会在哪个城市。

## 说明/提示

### 样例解释 1

Bessie 的前三次冒险会如下进行：

- 在第一次冒险中，她于时刻 $4$ 从城市 $2$ 出发，于时刻 $5$ 到达城市 $3$，于时刻 $6$ 到达城市 $4$，于时刻 $7$ 到达城市 $2$。
- 在第二次冒险中，她于时刻 $3$ 从城市 $3$ 出发，于时刻 $4$ 到达城市 $4$，于时刻 $5$ 到达城市 $2$，于时刻 $6$ 到达城市 $4$，于时刻 $7$ 到达城市 $2$，于时刻 $8$ 到达城市 $4$，于时刻 $9$ 到达城市 $2$。
- 在第三次冒险中，她于时刻 $3$ 从城市 $5$ 出发，于时刻 $4$ 到达城市 $5$，于时刻 $5$ 到达城市 $5$。

### 测试点性质

- 测试点 $3$：$\Delta_j\le 2\cdot 10^2$。
- 测试点 $4-5$：$N,\sum T_j\le 2\cdot 10^3$。
- 测试点 $6-8$：$N,\sum T_j\le 10^4$。
- 测试点 $9-18$：没有额外限制。

## 样例 #1

### 输入

```
5 4
1 2 1 2 8
2
3 4
4
2 3
5 5 5 5 5 1 5 5
2 4 3
3 3 6
5 3 2
5 3 7```

### 输出

```
2
2
5
4```

## 样例 #2

### 输入

```
5 5
1 2 1 2 8
2
3 4
4
2 3
5 5 5 5 5 1 5 5
2 4 3
3 2 6
5 3 2
5 3 7
5 3 1000000000000000000```

### 输出

```
2
3
5
4
2```

# 题解

## 作者：C1942huangjiaxu (赞：7)

很深刻的题。

图上行走问题自然想到倍增，先简单尝试一下。

记 $f_{i,j,k}$ 表示日期 $\bmod T_i=k$，从 $i$ 走 $2^j$ 步到的节点。

但发现走 $2^j$ 步的过程中，可能走到 $T_u\gt T_i$ 的点，这样只记录日期 $\bmod T_i$ 的信息就不够了。

所以如果遇到了点 $u$，我们将 $f_{i,j,k}$ 强制停止在点 $u$，需要记录 $g_{i,j,k}$ 表示实际行走的长度。

**我们称 $T_i$ 相同的点为同一层的点**，考虑这样对于每次询问的复杂度，每一步有 2 种可能，如果强制停止了，那么层数加 $1$，否则剩余距离减半。

记 $m=\max T_i,N=\sum T_i$，每次减半前最多爬 $\log m$ 层，一次询问的复杂度为 $O(\log m\log V)$。

但是我们预处理时同样要这样走，所以总时间复杂度为 $O(N\log^2 V\log m)$，无法通过。

发现实际上我们记录这个 $2^j$ 步并没有什么意义，因为我们可能根本走不到 $2^j$ 步就强制停止了，而这个步数的要求却使得我们有较高的复杂度。

因为只有走到了，$T_u\gt T_i$ 的点 $u$ 才会强制停止，我们干脆把 $f_{i,j,k}$ 定义为，**从 $i$ 走 $2^j$ 个同一层的点后到达的点**，这里同样会强制停止，但是我们的预处理的复杂度变成 $O(N(\log m+\log V))$。

再来考虑询问，我们先用 $O(\log m)$ 的复杂度爬到最高层，再用 $O(\log V)$ 的复杂度找到这一层的最后一个节点，然后层数上限减 1，总复杂度 $O(\log m(\log m+log V))$。

这样，我们以 $O(N(\log m+\log V)+Q\log m(\log m+log V))$ 的复杂度解决了本题。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf=2e18;
const int N=1e5+5;
int n,q,t[N],mx;
int *c[N],*f[61][N];
ll *g[61][N];
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i){
		scanf("%d",&t[i]);
		c[i]=new int[t[i]];
		mx=max(mx,t[i]);
		for(int j=0;j<=60;++j)f[j][i]=new int[t[i]],g[j][i]=new ll[t[i]];
	}
	for(int i=1;i<=n;++i)
		for(int j=0;j<t[i];++j)scanf("%d",&c[i][j]);
	for(int j=1;j<=mx;j<<=1){
		for(int i=1;i<=n;++i)if(t[i]==j)for(int k=0;k<j;++k){
			int x=c[i][k];ll dt=1;
			while(t[x]<j&&dt<inf){
				int y=f[60][x][k+dt&t[x]-1];
				dt+=g[60][x][k+dt&t[x]-1];
				x=y;
			}
			f[0][i][k]=x,g[0][i][k]=min(inf,dt);
		}
		for(int l=1;l<=60;++l)for(int i=1;i<=n;++i)if(t[i]==j)for(int k=0;k<j;++k){
			int x=f[l-1][i][k];ll dt=g[l-1][i][k];
			if(t[x]!=j){
				f[l][i][k]=x;
				g[l][i][k]=dt;
				continue;
			}
			f[l][i][k]=f[l-1][x][k+dt&j-1];
			g[l][i][k]=min(inf,g[l-1][x][k+dt&j-1]+dt);
		}
	}
	while(q--){
		int x;ll T,dt,w;
		scanf("%d%lld%lld",&x,&T,&dt);
		while(dt){
			for(int j=60;~j&&dt;--j)if((w=g[j][x][T&t[x]-1])<=dt){
				dt-=w;
				int ls=t[x];
				x=f[j][x][T&t[x]-1];
				T+=w;
				if(t[x]!=ls)j=61;
			}
			if(dt){
				x=c[x][T&t[x]-1];
				++T,--dt;
			}
		}
		printf("%d\n",x);
	}
	return 0;
}
```

---

## 作者：cyffff (赞：5)

[$\text{Link}$](https://www.luogu.com.cn/problem/P10198)

## 题意
给定 $n$ 个数组 $c_{i,0\dots t_i-1}$，其中 $t_i$ 为 $2$ 的幂。有 $q$ 次询问，每次询问给出三个参数 $x,T,\Delta$，接下来会执行 $\Delta$ 次 $x\gets c_{x,T\bmod t_x},T\gets T+1$，求出最终的 $x$。

$n,\sum t\le 10^5$，$q\le 5\times 10^4$。
## 题解

令 $n=\sum t$，$v=\max\Delta$。

**从一点开始走若干步到达的点提示使用倍增**。

我们的状态数不能太多，于是一个想法是设 $f_{i,j,k}$ 表示现在在点 $i$，当前时间 $\bmod\ t_i$ 等于 $j$，走 $2^k$ 步到达的点。

此时一个问题是如果跳到一个 $t_u>t_i$ 的点 $u$，维护的信息不足以得知当前时间 $\bmod\ t_u$ 的值。**注意到 $t_i$ 只有 $\log n$ 种，即我们在一条路径上最多遇到 $\log n$ 次这种情况**。于是我们将此种情况下的 $f_{i,j,k}$ 定义为在这 $2^k$ 步中遇到的第一个 $t_u>t_i$ 的点 $u$，还需再维护 $g_{i,j,k}$ 表示在这个 $u$ 之前已经走了几步了。

预处理与单次询问均可模拟：从高至低枚举每一位，不断跳直到该位为 $0$，每一位至多只会跳 $\log n$ 次。时间复杂度为 $O(n\log n\log^2v+q\log n\log v)$，无法通过。

考虑复杂度瓶颈为预处理部分，我们在特殊情况中经过了形如 $i\to u\to v$ 且 $t_u<t_v<t_i$ 这样的路径，这造成了很大的复杂度开销，**我们希望每一次跳到的点 $u$ 对应的 $t_u$ 均为路径上的前缀最大值**，这样一条任意长的路径也只需要跳 $\log n+\log v$ 次即可跳完。

考虑令 $f_{i,j,k}$ 为在时间为 $j\pmod{t_i}$ 时从点 $i$ 开始不断走直到经过了 $2^k$ 个使得 $t_u=t_i$ 的点 $u$ 或到达一个使得 $t_u>t_i$ 的点 $u$，此时到达的点。相应地有 $g_{i,j,k}$ 表示这条路径的长度。

预处理时先从小到大枚举 $v$，对所有 $t_i=2^v$ 的 $i$ 求出所有 $f_{i,j,k}$。重点为求出 $f_{i,j,0}$，从 $c_{i,j}$ 开始不断向其后第一个 $t$ 比自身大的跳即可。

询问时先不断向大跳直到达到路径上 $t$ 的最大值，此后跳过所有 $t$ 值为最大值的点即可减小最大值，显然我们只能减少 $\log n$ 次。

总时间复杂度 $O(n\log v+q\log n\log v)$，可以通过。

---

## 作者：山田リョウ (赞：3)

对不起我没携带大脑。

但是这样的好处是成为了[最短解](https://qoj.ac/problem/8538/statistics)。

看到数据范围 $10^{18}$ 自然想到倍增，于是你就会了 $O(n\log^3n+q\log^2n)$：

具体来说，记 $f_{u,t,\Delta}$ 表示从在模 $T_u$ 为 $t$ 的时刻开始从 $u$ 跳 $2^\Delta$ 步后达到的位置，特别的，要求除去终点外经过的 $2^\Delta$ 个结点 $v$ 均满足 $T_v\leq T_u$，否则无法唯一确定跳的过程。进一步的，记录在模 $T_u$ 为 $t$ 的时刻从 $u$ 开始跳跳到的第一个满足 $T_v>T_u$ 的 $v$ 以及经过的时间。

这样你回答询问时只需要先跳到一个跳剩余步数不会超过限制的点，从这个点再利用倍增数组将剩余步数至少除以 $2$ 即可。考虑到 $T$ 每次增大至少翻倍，回答一次询问的复杂度即为 $O(\log^2n)$。

但遗憾的是预处理时没法简单的直接继承，也需要朴素地进行倍增，这样预处理复杂度就变为了 $O(n\log^3n)$。

---

于是我就发现我的预处理做法实际有点蠢，具体来说，倍增的复杂度不依赖于步数是等比数列，你只需要保证比不会太小即可，限制比在 $[\frac{3}{2},2]$ 之间即可使预处理复杂度变为 $O(n\log^2n)$ 就能通过本题。

[submission.](https://qoj.ac/submission/996381)

---

## 作者：Nelofus (赞：2)

每个点跳到的位置是只与当前 $t$ 相关且唯一的，求跳 $k$ 步之后的状态，考虑倍增。

一个问题是，如果我们在每个点只维护当前的 $t\bmod T_u$ 的结果，会丢掉信息，从一个 $T_i$ 小的节点进入 $T_i$ 大的节点的时候，高位的信息是有用的。

只有 $\operatorname{lcm}_{i=1}^{N}T_i=\max_{i=1}^{N} T_i$ 个本质不同的状态，记 $S=\max_{i=1}^{N} T_i$，对每个 $i$ 扩展 $c_{i,j}$ 的定义，每个 $0\le j<S$ 令 $c_{i,j}=c_{i,j\bmod T_i}$，这样一来倍增的过程中就不会丢掉当前 $t$ 的信息了。从而，我们有一个 $\mathcal O(nT\log \Delta+q\log \Delta)$ 的做法。

显然，这不能满足我们的需要。还有两个性质没用上：

1.   $$
     \sum_{i=1}^{N}T_i\le 10^5
     $$

2.   $T_i$ 是 $2$ 的幂。

这提示我们只有 $\log T$ 个不同的 $T_i$，也提示我们可以对每个 $i$ 建 $T_i$ 个点。

在什么情况下，会有这种“信息丢失”的转移发生？

![【图】](https://s2.loli.net/2024/05/19/gWBMvKtP7Iqpzkx.jpg)

从一个小的转移到大的过程中，你没有办法确定转移后，下一步的转移是哪一条线指的，这就没有办法合并到倍增的过程中。

过程没法合并怎么办？考虑直接不合并。每当我们到达某一个 $T_{c_{i,j}}>T_i$ 的位置的时候就停下来，手动跳一步。

令 $\Delta$ 表示剩余跳跃次数。

手动跳跃的过程只会发生 $\mathcal O(\log T)$ 次就会到达最高的一个 $T_i$，在最高位这次倍增跳跃一定可以至少减半，可以每次减半都需要花费 $\log T$ 的代价（中途跳跃减少的步数只会降低 $\Delta$ 不影响分析），所以这样做（如果实现得正确，即每次应当从 $\lfloor\log_2\Delta\rfloor$ 开始）的复杂度是 $\mathcal O(\log \Delta\log T)$ 的。

那么要做的事就是预处理出一个函数 $\operatorname{J}(k,u,t)$ 表示在 $u$ 处，自 $t$ 时刻开始，往后 $2^k$ 步后到达的位置，或是 $2^k$ 步中碰到的第一个 $T_v$ 大于 $T_u$ 的位置 $v$，再维护一个 $\operatorname{G}(k,u,t)$ 表示上述过程中实际走了多少步。

一个朴素的想法是，我们从小到大枚举 $T_u$，所有 $T_v>T_u$ 的 $v$ 处 $\operatorname{J}(k,v,t)=v,\operatorname{G}(k,v,t)=0$，看起来这样就能合并了……吧？

可惜事与愿违，如果直接这样做，倍增的过程会停在一个先下降后的上升的段。

![【第二个图】](https://s2.loli.net/2024/05/19/3TjoPfaCcnKSB8D.jpg)

这是因为低处的 $T_v$ 在对一个不高于 $T_u$ 但比它高的 $T_w$ 的时候，维护转移在 $>T_v$ 处被阻断而不是在 $>T_u$ 处被阻断。

>   $\mathcal O(\log^2\Delta)$ 预处理做法（喜提 MLE 过不了）
>
>    我们希望在低处的 $v$ 也维护的是 $>T_u$ 的第一个点的信息。
>
>   那么就把整个倍增数组直接分成 $\log T$ 层，对于第 $p$ 个数组，只将所有 $T_v>2^p$ 的位置 $v$ 设置为 $\operatorname{J}(k,v,t)=v,\operatorname{G}(k,v,t)=0$（也就是只有在下一个位置 $T_v>2^p$ 的时候才阻断转移），这样每次在 $u$ 处查询的时候，查询第 $\log_2 T_u$ 个数组的倍增信息，这个时候就是跳跃到 $2^k$ 步后第一个 $>T_u$ 的位置了。

>   $\mathcal O(\log \Delta)$ 预处理做法
>
>   考虑干脆别管那些比他小的 $v$ 了。钦定每次跳跃都一定跳跃到下一个和它同层的节点。这个过程也是可以倍增的，复杂度 $\mathcal O(n\log \Delta)$。

总复杂度 $\mathcal O(\sum T_i\log (\log T+\log\Delta) +q\log \Delta(\log \Delta+\log T))$。

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/P10198)

**题目大意**

> 给定 $n$ 个点的图，时刻 $t$ 在 $u$ 节点，那么 $t+1$ 时刻会在 $b_{a,t\bmod a_u}$ 节点，其中 $a_u$ 是 $2$ 的幂。
>
> $q$ 次询问 $t$ 时刻从 $u$ 出发走 $d$ 步会到达哪个节点。
>
> 数据范围：$n,\sum a_u\le 10^5,d\le 10^{18}$。

**思路分析**

首先肯定需要倍增，$f_{u,t,i}$ 表示 $t$ 时刻从 $u$ 出发走 $2^i$ 步的结果，但问题是如果路程中遇到 $a_v>a_u$ 的点，$t$ 的信息就不够了。

但我们发现此时直接切换到 $v$ 的位置开始倍增，那么这个过程只会进行 $\mathcal O(\log A)$ 次，因为 $a_v\ge 2a_u$。

因此 $f_{u,t,i}$ 表示从 $u$ 出发走 $2^i$ 步或到达 $a_v>a_u$ 点的结果，$d_{u,t,i}$ 表示实际运动的步数。

那么查询复杂度 $\mathcal O(\log A\log T)$，但预处理时需要 $\mathcal O(n\log T)$ 次询问，难以接受。

注意到我们的瓶颈时 $f_{u,t,i-1}$ 可能跳到一个 $a_v<a_u$ 的点，那么就会失去 $t$ 的信息。

那么我们不妨改变定义，直接令 $f_{u,t,i}$ 表示经过 $2^i$ 个 $a_v=a_u$ 的点，或遇到 $a_v>a_u$ 的点时停止。

那么询问时我们会用 $\mathcal O(\log A)$ 轮倍增到达 $a$ 最大的点，随后每轮倍增，剩余路径上 $a$ 的最大值减小，因此倍增总轮数 $\mathcal O(\log A)$。

时间复杂度 $\mathcal O(n\log T+q\log A\log T)$。

**代码呈现 **

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e5+5;
const ll inf=2e18;
int n,q,a[MAXN];
vector <int> b[MAXN],f[MAXN][64];
vector <ll> d[MAXN][64];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i) {
		b[i].resize(a[i]);
		for(int &p:b[i]) cin>>p;
		for(int k=0;k<=60;++k) d[i][k].resize(a[i]),f[i][k].resize(a[i]);
	}
	for(int s=1;s<MAXN;s<<=1) {
		for(int u=1;u<=n;++u) if(a[u]==s) {
			for(int i=0;i<s;++i) {
				int v=b[u][i]; ll t=1;
				while(a[v]<s&&t<inf) {
					int w=f[v][60][(i+t)%a[v]];
					t+=d[v][60][(i+t)%a[v]],v=w;
				}
				f[u][0][i]=v,d[u][0][i]=min(t,inf);
			}
		}
		for(int k=1;k<=60;++k) for(int u=1;u<=n;++u) if(a[u]==s) {
			for(int i=0;i<s;++i) {
				int v=f[u][k-1][i]; ll t=d[u][k-1][i];
				if(a[v]==s) {
					f[u][k][i]=f[v][k-1][(i+t)%s];
					d[u][k][i]=min(d[v][k-1][(i+t)%s]+t,inf);
				} else f[u][k][i]=v,d[u][k][i]=t;
			}
		}
	}
	for(int u;q--;) {
		ll dis,cur;
		cin>>u>>cur>>dis;
		while(dis) {
			for(int k=60;~k;--k) if(dis>=d[u][k][cur%a[u]]) {
				int v=f[u][k][cur%a[u]];
				ll t=d[u][k][cur%a[u]];
				if(a[v]!=a[u]) k=61;
				dis-=t,cur+=t,u=v;
			}
			if(dis) u=b[u][cur%a[u]],--dis,++cur;
		}
		cout<<u<<"\n";
	}
	return 0;
}
```

---

## 作者：Graphcity (赞：0)

看到这种需要跳 $10^{18}$ 次的题目，首先想到的就是倍增。考虑如何刻画信息。如果我们单纯设 $f_{i,j,k}$ 表示到达第 $i$ 座城市，日期 $\bmod T_i=j$，跳 $2^k$ 步走到的位置，当然是错误的。原因就是如果我们跳到了一座 $T>T_i$ 的城市，那么信息就不够用了。

设 $(i,j)$ 表示第 $i$ 座城市的第 $j$ 个传送门。我们先记录二元组 $up_{i,j}$ 表示从 $(i,j)$ 出发，跳到第一个 $T>T_i$ 的城市的编号，以及需要用多久。转移的话，考虑直接从 $(i,j)$ 开始暴力跳 $up$，直到跳到一个 $T\ge T_i$ 的城市为止。容易发现至多跳 $\log V$ 次。假如我们跳到的是 $T>T_i$ 的点，那就万事大吉了。

否则，我们从 $(i,j)$ 连一条有向边到这个最后跳到的点。我们发现对于同一个 $T$ 的点，每个点的出度都 $\le 1$，形成了一张由树和内向基环树森林组成的图。对于森林的部分，它最终一定能从根结点的 $up$ 跳出去，遍历一遍就好了。对于环上的点，它永远都跳不出去了。此时我们就可以利用上面的倍增算法，设 $fa_{i,j},dis_{i,j}$ 分别表示从第 $i$ 个点跳 $2^j$ 轮走到的点 / 经过的距离和。

对于询问，我们考虑用递归的方式求解，设 `Solve(x,t,k)` 表示从城市 $x$，时刻 $t$ 开始，经过 $k$ 个时刻后的答案。如果当前点的 $up$ 要用的时间 $\le k$，就跳到 $up$ 对应的城市；否则如果能跳到 $T=T_x$ 的城市，就执行倍增算法；如果都不能，就先跳一步试试看。可以证明这样跳单次是 $O(\log n\log V)$ 的。

总时间复杂度 $O(n\log V+q\log n\log V)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5;
const ll inf=2e18+5;

int n,m,s,fa[Maxn+5],anc[Maxn+5][65];
ll val[Maxn+5],dis[Maxn+5][65];
int h[Maxn+5],fr[Maxn+5];
pair<int,ll> dw[Maxn+5],to[Maxn+5],up[Maxn+5];
vector<int> c[Maxn+5],id[Maxn+5],w[Maxn+5];
vector<int> v[Maxn+5];

inline void dfs(int x,int p,ll k) {up[x]=make_pair(p,k); for(auto y:v[x]) dfs(y,p,k+val[y]);}
inline void Work(int d)
{
    for(auto i:w[d]) For(j,0,h[i]-1)
    {
        int p=id[i][j],x=c[i][j]; ll res=1;
        if(h[c[i][j]]>h[i]) {up[p]=make_pair(c[i][j],1ll); continue;}
        if(h[c[i][j]]==h[i]) {to[p]=make_pair(c[i][j],1ll); continue;}
        while(h[x]<h[i])
        {
            auto [y,len]=up[id[x][(res+j)&(h[x]-1)]];
            if(!y) break; res+=len,x=y;
        }
        if(h[x]==h[i]) to[p]=make_pair(x,res);
        if(h[x]>h[i]) up[p]=make_pair(x,res);
    }
    for(auto i:w[d]) For(j,0,h[i]-1) if(to[id[i][j]].first)
    {
        auto [y,len]=to[id[i][j]];
        int p=id[i][j],k=id[y][(len+j)&(h[i]-1)];
        fa[p]=k,val[p]=len,v[k].push_back(p);
    }
    for(auto i:w[d]) For(j,0,h[i]-1) {int p=id[i][j]; if(up[p].first) dfs(p,up[p].first,up[p].second);}
    for(auto i:w[d]) For(j,0,h[i]-1) {int p=id[i][j]; anc[p][0]=fa[p],dis[p][0]=val[p];}
    For(k,1,60) for(auto i:w[d]) For(j,0,h[i]-1)
    {
        int p=id[i][j]; anc[p][k]=anc[anc[p][k-1]][k-1];
        dis[p][k]=min(inf,dis[p][k-1]+dis[anc[p][k-1]][k-1]);
    }
}
inline int Get(int x,ll t,ll k)
{
    if(!k) return x; int p=id[x][t&(h[x]-1)];
    if(up[p].first && up[p].second<=k) return Get(up[p].first,t+up[p].second,k-up[p].second);
    if(to[p].first && to[p].second<=k)
    {
        Rof(i,60,0) if(anc[p][i] && k>=dis[p][i])
            t+=dis[p][i],k-=dis[p][i],p=anc[p][i];
        return Get(fr[p],t,k);
    } return Get(c[x][t&(h[x]-1)],t+1,k-1);
}

int main()
{
    cin>>n>>m; For(i,1,n) cin>>h[i];
    For(i,1,n) c[i].resize(h[i]),id[i].resize(h[i]);
    For(i,1,n) For(j,0,h[i]-1) cin>>c[i][j],id[i][j]=++s,fr[s]=i;
    For(i,1,n) w[__lg(h[i])].push_back(i);
    For(i,0,20) if(!w[i].empty()) Work(i);
    while(m--) {int x; ll t,k; cin>>x>>t>>k; printf("%d\n",Get(x,t,k));}
    return 0;
}
```

---

