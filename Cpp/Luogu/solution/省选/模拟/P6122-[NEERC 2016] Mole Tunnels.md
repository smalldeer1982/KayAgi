# [NEERC 2016] Mole Tunnels

## 题目描述

鼹鼠们在底下开凿了 $n$ 个洞，由 $n-1$ 条隧道连接，对于任意的 $i>1$，第 $i$ 个洞都会和第 $\lfloor \frac{i}{2}\rfloor$ 个洞间有一条隧道，第 $i$ 个洞内还有 $c_i$ 个食物能供最多 $c_i$ 只鼹鼠吃。一共有 $m$ 只鼹鼠，第 $i$ 只鼹鼠住在第 $p_i$ 个洞内。

一天早晨，前 $k$ 只鼹鼠醒来了，而后 $m-k$ 只鼹鼠均在睡觉，前 $k$ 只鼹鼠就开始觅食，最终他们都会到达某一个洞，使得所有洞的 $c_i$ 均大于等于该洞内醒着的鼹鼠个数，而且要求鼹鼠行动路径总长度最小。现对于所有的 $1 \le k \le m$，输出最小的鼹鼠行动路径的总长度，保证一定存在某种合法方案。

## 说明/提示

$1 \le n,m \le 10^5$，$0 \le c_i \le m$，$1 \le p_i \le n$。

## 样例 #1

### 输入

```
5 4
0 0 4 1 1
2 4 5 2```

### 输出

```
1 1 2 4```

# 题解

## 作者：RuSun (赞：20)

觉得两篇题解没有将流量的维护讲清楚，直接就胡过去了。

省选前发题解 RP++ 。

[更好的阅读体验](https://rusunoi.github.io/post/P6122/)

先考虑费用流，树上双向边，容量无限，费用为 $1$ ，源点向所有有食物的点连边，所有鼹鼠向汇点连边。发现不能一次做完所有点，需要一个一个添加，费用流不方便做此题。

考虑模拟费用流，每新加入一个点，需要找到一条源点 $\to$ 加入的点 $\to$ 汇点的一条增广路，与源点汇点连接的边是唯一的，也就是需要在树上找到一条加入的点 $\to$ 有食物的点的最短路。现在考虑如何快速找到这样的最短路，注意到这是一棵二叉树，树高只有 $\log n$ ，考虑维护 $f _ i, g _ i$ 表示点 $i$ 到其子树中有食物的点的最短路为多少、是哪个点。这样从一个点一直跳父亲，只需要 $\log n$ 次就可以确定这个点。确定点后需要将这一条路径的流量减一，反向边流量加一。

双向边以及它们的反向边的流量以及费用可以简单地用一个数组即可维护，原来的一对父子 $p, s$ 需要建边 $(p, s, inf, 1)$ 以及反向边 $(s, p, 0, -1)$ ；$(s, p, inf, 1)$ 以及反向边 $(p, s, 0, -1)$ ，无论是 $p \to s$ 还是 $s \to p$ ，都优先考虑走对方的反向边，因为反向边的费用为 $-1$ ，是更优的。这样的话，我们维护一个 $wt _ i$ 表示从 $i$ 的父亲到 $i$ 的正向边流量，当其为正的时候，表示存在边 $(p, s, inf, 1), (s, p, wt _ i, -1)$ ，父亲到儿子只能选择正向边，儿子到父亲优先选择父亲到儿子的反向边；当其为负的时候，表示存在边 $(s, p, inf, 1), (p, s, wt _ i, -1)$ ，儿子到父亲只能选择反向边，父亲到儿子优先选择反向边；当为 $0$ 的时候，那么两者都没有流量，只能选择正向边。

新加入点 $p$ 时，先不断跳父亲，找到一个父亲 $pos$ 使得路径 $p \to pos \to g _ {pos}$ 是最短路，然后修改其中的流量，对于向上的边，相当于使 ``wt--`` ，向下的边反之。修改完路径后，需要将所有 $f _ i, g _ i$ 受到影响的点全部更新，即 $p \to pos, g _ {pos} \to pos, pos \to root$ 。

每个点完成后输出答案即可，复杂度 $O(n \log n)$ 。

```cpp
#include <cstdio>
using namespace std;
template <class Type>
void read(Type &x)
{
    char c;
    bool flag = false;
    while ((c = getchar()) < '0' || c > '9')
        c == '-' && (flag = true);
    x = c - '0';
    while ((c = getchar()) >= '0' && c <= '9')
        x = (x << 3) + (x << 1) + c - '0';
    flag && (x = ~x + 1);
}
template <class Type>
void write(Type x)
{
    x < 0 && (putchar('-'), x = ~x + 1);
    x > 9 && (write(x / 10), 0);
    putchar(x % 10 + '0');
}
const int N = 1e5 + 10, inf = 2e6;
int n, m, c[N], f[N << 1], g[N << 1], wt[N];
void chkmin (int &x, int &mn, int t, int k)
{
    k < mn && (mn = k, x = t);
}
int cst_up (int x)
{
    return wt[x] > 0 ? -1 : 1;
}
int cst_down (int x)
{
    return wt[x] < 0 ? -1 : 1;
}
void update (int x)
{
    f[x] = inf;
    c[x] && (f[x] = 0, g[x] = x);
    x << 1 <= n && (chkmin(g[x], f[x], g[x << 1], f[x << 1] + cst_down(x << 1)), 0);
    (x << 1 | 1) <= n && (chkmin(g[x], f[x], g[x << 1 | 1], f[x << 1 | 1] + cst_down(x << 1 | 1)), 0);
}
int main ()
{
    read(n), read(m);
    for (int i = 1; i <= n; i++)
        read(c[i]);
    for (int i = n; i; i--)
        update(i);
    int res = 0;
    for (int p; m; m--)
    {
        read(p);
        int mn = inf, pos;
        for (int u = p, t = 0; u; t += cst_up(u), u >>= 1)
            chkmin(pos, mn, u, f[u] + t);
        res += mn;
        for (int u = p; u ^ pos; u >>= 1)
            wt[u]--, update(u);
        c[g[pos]]--;
        for (int u = g[pos]; u ^ pos; u >>= 1)
            wt[u]++, update(u);
        for (; pos; pos >>= 1)
            update(pos);
        write(res), putchar(' ');
    }
    return 0;
}
```


---

## 作者：loverintime (赞：18)

容易建出费用流模型：

源点向松鼠住的洞连容量为 $1$， 费用为 $0$ 的边。

相邻两点连容量无限大， 费用为 $1$ 的边。

有食物的点向汇点连容量为 $c_i$， 费用为 $0$ 的边。

然后就是费用流板子了。 但显然， 这样会超时。

## 模拟费用流

我们可以模拟费用流的过程， 把时间优化到 $\Theta(n\log n)$。

具体来说， 我们每加入一个点时， 暴力查询到这个点距离最小且有食物的点。 这个可以 $dp$。 设 $f(i)$ 表示 $i$ 点到子树内的点的最小距离。 由于是一颗完全二叉树， 我们将加入的点暴力往上爬去找， 一次时间 $\Theta(\log n)$。

找到那个点之后， 暴力改变两点之间的路径的流量和边权（就像费用流一样）， 同时更新 $f$ 的值。 注意， $f$ 的值要更新到根， 有可能会更新少了 ~~（别问我是怎么知道的）~~。

然后复杂度就变成 $\Theta(n\log n)$ 了。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+5,inf=0x3f3f3f3f;
int n,m,p[N],c[N],f[N<<1],g[N<<1];
void upd(int &a,int &b,int x,int y){
	if(x<a) a=x,b=y;
}
int flow[N],ans;
void update(int x){
	f[x]=inf;
	if(c[x]) f[x]=0,g[x]=x;
	upd(f[x],g[x],f[x<<1]+(flow[x<<1]<0?-1:1),g[x<<1]);
	upd(f[x],g[x],f[x<<1|1]+(flow[x<<1|1]<0?-1:1),g[x<<1|1]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++) scanf("%d",&c[i]);
	for(int i=1; i<=m; i++) scanf("%d",&p[i]);
	memset(f,0x3f,sizeof f);
	for(int i=n; i; i--) update(i);
	for(int i=1; i<=m; i++){
		int x=inf,y=0,u=p[i],t=0,v=0;
		while(u){
			if(x>f[u]+t) x=f[u]+t,y=g[u],v=u;
			t+=(flow[u]>0?-1:1);u>>=1;
		}
		u=p[i];ans+=x;
		while(u!=v){
			flow[u]--;
			update(u>>1);
			u>>=1;
		}
		c[y]--;update(y);
		while(y!=v){
			flow[y]++;
			update(y>>1);
			y>>=1;
		}
		while(v) update(v),v>>=1;
		printf("%d ",ans);
	}
    return 0;
}

---

## 作者：z7z_Eta (赞：14)

题意 : $n$个点的完全二叉树, 点$i$上有$c_i$食物, $m$只不同位置的仓鼠依次醒来, 求最小总路径长度

------

~~不要脸的来水篇题解~~

据说是一道经典的**模拟费用流**

* 总路径长度可以看做 : 所有边可以经过无数次, 每经过一次花费1的费用
* 食物是每只仓鼠的终点 : 相当于$i$到汇连一条流量为$c_i$的边
* 每次都会进入一只仓鼠 : 相当于源向$p_i$加一条流量为1的边

因为这种建图**流量转移**非常的简单, 所以可以手动模拟使复杂度达到$O(nlogn)$

大致流程是 : 类似贪心, 每次找到最近距离的食物, 然后借助费用流的反悔机制, 在经过的路径上的反向边添加负费用的边, 最后更新距离

因为是完全二叉树, 所以每次的查找类似平衡树上查找, 复杂度保证为每次一个$log$, 更新答案的方式也类似平衡树的update

做法很奇妙, 也算是一道颇有启发性的一道题= =+

标签标蓝题是挺正常的

### 代码实现:

```
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<cmath>
#define ll long long
#define il inline
#define rep(i,s,t) for(register int i=(s);i<=(t);i++)
#define rev_rep(i,s,t) for(register int i=(s);i>=(t);i--)
#define each(i,u) for(int i=head[u];i;i=bow[i].nxt)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
#define pt(x) putchar(x)
using namespace std;
il int ci(){
	register char ch; int f=1;
	while(!isdigit(ch=getchar())) f=ch=='-'?-1:1;
	register int x=ch^'0';
	while(isdigit(ch=getchar())) x=(x*10)+(ch^'0');
	return f*x;
}
template<typename T>
il bool chk_min(T&x,T y){
	return y<x ? (x=y,1):0;
}

enum{N=800023}; // 点数多开几倍防止越界

#define lc(x) ((x)<<1)
#define rc(x) ((x)<<1|1)
int dis[N],c[N],pos[N];
int flow[N];
il int lenU(int x){ return flow[x]<0 ? -1:1; }
il int lenD(int x){ return flow[x]>0 ? -1:1; } 这里代码里的流量是根据正负判断是否是反向边的
如果CE了不要怪我

il void update(int x){
	dis[x] = 1e9;
	pos[x] = 0;
	if( c[x] ) dis[x]=0, pos[x]=x;
	if( chk_min(dis[x],dis[lc(x)]+lenD(lc(x))) ){
		pos[x] = pos[lc(x)];
	}
	if( chk_min(dis[x],dis[rc(x)]+lenD(rc(x))) ){
		pos[x] = pos[rc(x)];
	}
}

int main(){
	int n=ci(), m=ci();
	memset(dis,0x3f,sizeof(dis));
	rep(i,1,n) c[i]=ci();
	rev_rep(i,n,1) update(i);
	int ans = 0;
	while( m-- ){
		int s=ci();
		int t=0;
		int cost=1e9, now=0;
		#define up(x,s,t) for(register int x=s;x!=t;x>>=1)
		up(x,s,0){
			if( chk_min(cost,now+dis[x]) ) t=x;
			now += lenU(x);
		}
		int target = pos[t];
		ans += cost;
		up(x,s,t) flow[x]++;
		up(x,target,t) flow[x]--;
		c[target]--;
		up(x,target,t) update(x);
		up(x,s,0) update(x);
//	printf("c   "); rep(i,1,n) printf("%d ",c[i]); pt('\n');
//	printf("dis "); rep(i,1,n) printf("%d ",dis[i]); pt('\n');
//	printf("pos "); rep(i,1,n) printf("%d ",pos[i]); pt('\n');
//	printf("flw "); rep(i,1,n) printf("%d ",flow[i]); pt('\n');
		printf("%d ",ans);
	}
	pt('\n');
	return 0;
}
```

这么easy的题, 写过了却不是很有成就感

毕竟真正的模拟费用流还是很hard

---

## 作者：teylnol_evteyl (赞：9)

不难建出费用流模型：

- 对于树上的边 $(u,v)$，连容量为 $\infty$、费用为 $1$ 的双向边。
- 每个点 $u$ 向汇点连容量为 $c_i$、费用为 $0$ 的边。
- 对于新醒来的一只在 $u$ 点鼹鼠，连一条从原点到 $u$ 容量为 $1$、费用为 $0$ 的边。

每次新加入一只田鼠加边后跑费用流即可。

考虑模拟费用流。每次增广，相当于找到一条到有食物的节点的路径，并且改变一些边权。

记 $fa_u=\lfloor\frac u2\rfloor$，$ls_u = 2u$，$rs_u=2u+1$。设 $cnt_u$ 表示 $u$ 到 $fa_u$ 的边从上往下走的次数减从下往上走的次数，则：

$$
\operatorname{cost}(fa_u,u)=
\begin{cases}
1 & cnt_u\ge0\\
-1 & cnt_u<0
\end{cases}
$$
$$
\operatorname{cost}(u,fa_u)=
\begin{cases}
1 & cnt_u\le0\\
-1 & cnt_u<0
\end{cases}
$$

设 $f_u$ 表示 $u$ 到子树中最近的有食物的点的距离，则它的值可以通过左右儿子和自己是否有食物计算到，即 $f_u=\min\{f_{ls_u}+\operatorname{cost}(u,ls_u),f_{rs_u}+\operatorname{cost}(u,rs_u),[c_u=0]\infty\}$。同时维护取到最小值的节点。

对于新加入节点 $u$ 的鼹鼠，在 $u$ 的祖先中暴力枚举 $LCA$，同时维护 $u$ 到 $LCA$ 的距离 $du$。然后查询 $LCA$ 子树中，$LCA$ 到它最近的有食物的节点 $v$，则 $u$ 到 $LCA$ 再到 $v$ 是一条合法的路径，距离为 $d_u+f_{LCA}$。由于是完全二叉树，$LCA$ 的数量是 $O(\log n)$。

由于是完全二叉树，路径的长度是 $O(\log n)$，暴力修改路径上 $\operatorname{cost}(u,fa_u),\operatorname{cost}(fa_u,u)$ 的值，然后更新 $u,v$ 祖先的 $f$ 值。

时间复杂度 $O((n+m)\log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

namespace fast_read{
    char buf[1000005], *s = buf, *t = buf, ch, f;
    #define gc() s == t && (t = (s = buf) + fread(buf, 1, 1000000, stdin), s == t) ? EOF : *s ++ 
    template <typename T>
    inline void read(T &x)
    {
        x = f = 0, ch = gc();
        while(ch < '0' || ch > '9')
        {
            if(ch == '-') f = 1;
            ch = gc();
        }
        while('0' <= ch && ch <= '9') x = x * 10 + ch - 48, ch = gc();
        f && (x = -x);
    }
};
using fast_read::read;

const int N = 2e5 + 5;

int n, m, c[N], up[N], down[N], cnt[N];
int mindep[N], mint[N];

inline void pushup(int u)
{
	int ls = u << 1, rs = ls | 1;
	int dl = mindep[ls] + down[ls], dr = mindep[rs] + down[rs];
	if(c[u] && dl > 0 && dr > 0) mindep[u] = 0, mint[u] = u;
	else if(dl < dr) mindep[u] = dl, mint[u] = mint[ls];
	else mindep[u] = dr, mint[u] = mint[rs];
}

int main()
{
	read(n), read(m);
	for(int i = 1; i <= n; i ++ ) read(c[i]);
	memset(mindep, 0x3f, sizeof mindep);
	for(int u = n; u >= 1; u -- )
	{
		up[u] = down[u] = 1;
		pushup(u);
	}
	
	long long ans = 0;
	while(m -- )
	{
		int u, v = 0, w, d = 2e9, du = 0;
		read(u);
		for(int pw = u; pw; du += up[pw], pw >>= 1)
		{
			if(mindep[pw] + du < d)
			{
				d = mindep[pw] + du;
				v = mint[pw], w = pw;
			}
		}
		ans += d;
		printf("%lld ", ans);
		
		c[v] -- ;
		for(int i = u; i != w; i >>= 1)
		{
			cnt[i] ++ ;
			if(cnt[i] == 0) up[i] = 1;
			if(cnt[i] == 1) down[i] = -1;
			pushup(i);
		}
		for(int i = v; i != w; i >>= 1)
		{
			cnt[i] -- ;
			if(cnt[i] == -1) up[i] = -1;
			if(cnt[i] == 0) down[i] = 1;
			pushup(i);
		}
		for(int i = w; i; i >>= 1) pushup(i);
	}
	return 0;
}
```

---

## 作者：artofproblemsolving (赞：3)

分析：

考虑一个贪心，我们每次都把鼹鼠送到离它最近的还可以居住的洞里。但是，有一个显然问题是我们没法处理之前的鼹鼠对后续的影响。我们可以这样考虑：每当一名鼹鼠经过一条树边，我们就将其设置一条反方向的权为 -1 的边，表示如果有鼹鼠反向经过，则会抵消其影响。

那么我们先扫一遍整棵树，用 $f(i)$ 表示在 $i$ 的字数中距离 $i$ 最近的点到 $i$ 的距离，$g[i]$ 表示在 $i$ 的子树中距离 $i$ 最近的点的位置，这两个数组的维护我们都可以直接利用他们的子树信息得到： 

```
f[i]=min{f[v]|v∈i的儿子点集}
g[i]=f转移用到的那个v
```

查询最短路的时候，可以从 $p[i]$ 向上遍历 $p[i]$ 的所有祖先，同时维护经过的距离，不断用当前节点的 $f$ 值加上爬上来的距离更新最短路答案，最后，利用上面提到的转移式重构路径上的所有结点的 $f$ 和 $g$ 值，并且为沿途的路径打上标记。由于对于任意的 $i>1$，第 $i$ 个洞都会和第 $\lfloor \frac{i}{2} \rfloor$ 个洞间有一条隧道的题设条件保证了这棵树是一个完全二叉树，也就是树高最多为 $\log_2n$，且每个点至多有 2 个儿子，所以这个贪心加上暴力复杂度是 $O(n\log n)$。

代码：

```cpp
for(int i=n;i>=1;i--){
		if(c[i]) f[i]=0,g[i]=i;
		if(f[i>>1]>f[i]+1) f[i>>1]=f[i]+1,g[i>>1]=g[i]; 
	}
	for(int i=1;i<=m;i++){
		cin>>p[i];
		minn=1<<30,sum=0;
		for(int j=p[i];j;j>>=1){
			if(f[j]+sum<minn) minn=f[j]+sum,pos=g[j],lca=j;
			sum+=(v[j][0]>0)?(-1):1;
		}
		ans+=minn;
		cout<<ans;
		if(i!=m) cout<<' ';
		c[pos]--;
		for(int j=p[i];j!=lca;j>>=1) v[j][0]?v[j][0]--:v[j][1]++;
		for(int j=pos;j!=lca;j>>=1) v[j][1]?v[j][1]--:v[j][0]++;
		for(int j=p[i];j!=lca;j>>=1){
			f[j]=1<<30;
			if(c[j]&&0<f[j]) f[j]=0,g[j]=j;
			if((j<<1)<=n&&f[j<<1|1]+(v[j<<1][1]?-1:1)<f[j]){
				f[j]=f[j<<1]+(v[j<<1][1]?-1:1);
				g[j]=g[j<<1];
			} 
			if((j<<1|1)<=n&&f[j<<1|1]+(v[j<<1|1][1]?-1:1)<f[j]){
				f[j]=f[j<<1|1]+(v[j<<1|1][1]?-1:1);
				g[j]=g[j<<1|1];
			}
		}
		for(int j=pos;j;j>>=1){
			f[j]=1<<30;
			if(c[j]&&0<f[j]) f[j]=0,g[j]=j;
			if((j<<1)<=n&&f[j<<1]+(v[j<<1][1]?-1:1)<f[j]){
				f[j]=f[j<<1]+(v[j<<1][1]?-1:1);
				g[j]=g[j<<1];
			}
			if((j<<1|1)<=n&&f[j<<1|1]+(v[j<<1|1][1]?-1:1)<f[j]){
				f[j]=f[j<<1|1]+(v[j<<1|1][1]?-1:1);
				g[j]=g[j<<1|1];
			}
		}
	}
```


---

## 作者：UniGravity (赞：2)

## Solution P6122 [NEERC2016] Mole Tunnels
### 写在前面
有的题解没有具体说明模拟费用流更新流量的具体过程，而是直接上结论，这篇题解会较详细的解释这一过程。

同时推荐一题 [k-Maximum Subsequence Sum](https://www.luogu.com.cn/problem/CF280D)，这题的思维难度较低，对本题也有启发作用。

### 具体过程
题目要求最小的距离，首先可以想到的做法是[费用流](https://oi-wiki.org/graph/flow/min-cost/)的做法：
* 树上的每条边都连接双向边，容量为 $\infty$，费用为 $1$。
* 源点向所有鼹鼠连边，所有有食物的点向汇点连边。

如此跑费用流，但是会超时。


------------

我们采用模拟费用流的方式优化。每加入一个点（增广），都需要找到一条树上的路径 $p\to x\to y$，$x$ 是 $p$ 和 $y$ 的 lca，$y$ 是一个有食物的点。

对于每条边，我们维护这些信息：
* $xtof1_i$ 表示点 $i$ 到 $fa_i$ 的正边流量，费用为 $1$。
* $xtof2_i$ 表示点 $i$ 到 $fa_i$ 的反边流量，费用为 $-1$。
* $ftox1_i$ 表示点 $fa_i$ 到 $i$ 的正边流量，费用为 $1$。
* $ftox2_i$ 表示点 $fa_i$ 到 $i$ 的反边流量，费用为 $-1$。

当我们从 $i$ 走向 $fa_i$ 时：
* 若 $ftox2_i>0$，我们走这条反边，只需付出 $-1$ 的费用。
* 否则走 $xtof1_i$ 这条正边，付出 $1$ 的费用。

当我们从 $fa_i$ 走向 $i$ 时：
* 若 $xtof2_i>0$，我们走这条反边，只需付出 $-1$ 的费用。
* 否则走 $ftofx_i$ 这条正边，付出 $1$ 的费用。


------------

具体而言，我们在树上维护 $dmin_x$ 和 $pmin_x$，分别表示以 $x$ 为子树中的最小距离和这个点（即上文的 $x\to y$），这可以用树型 dp 解决。

那么分为以下几步：
1. 先不断做 $p\leftarrow fa_p$，找到祖先 $x$。
2. 减少 $c_x$。
3. 将 $p\to x$ 和 $x\to y$ 的路径流量更新。
4. 记得将 $x\to root$ 的路径也要更新。

可以发现这是一棵完全二叉树，不断跳父亲的时间复杂度为 $O(\log n)$，那么总的时间复杂度为 $O(n\log n)$，可以通过本题

### 完整代码
```cpp
#include <bits/stdc++.h>
#define fa(x) (x / 2)
#define lc(x) (x * 2)
#define rc(x) (x * 2 + 1)
using namespace std;

const int INF = 0x3f3f3f3f, N = 300005;

int n, m;
int c[N];

int xtof1[N]; // x->fa flow cost  1
int xtof2[N]; // x<-fa flow cost -1
int ftox1[N]; // fa->x flow cost  1
int ftox2[N]; // fa<-x flow cost -1

int dmin[N], pmin[N], flg[N];

inline void pushup(int x) {
	dmin[x] = c[x] > 0 ? 0 : INF;
	pmin[x] = c[x] > 0 ? x : -1;
	flg[x] = x;
	int d;
	if (lc(x) <= n) {
		if (xtof2[lc(x)] > 0) d = -1;
		else d = 1;
		if (dmin[lc(x)] + d <= dmin[x]) {
			dmin[x] = dmin[lc(x)] + d;
			pmin[x] = pmin[lc(x)];
			flg[x] = lc(x);
		}
	}
	if (rc(x) <= n) {
		if (xtof2[rc(x)] > 0) d = -1;
		else d = 1;
		if (dmin[rc(x)] + d <= dmin[x]) {
			dmin[x] = dmin[rc(x)] + d;
			pmin[x] = pmin[rc(x)];
			flg[x] = rc(x);
		}
	}
}

inline void build(int x) {
	if (lc(x) <= n) {
		build(lc(x));
	}
	if (rc(x) <= n) {
		build(rc(x));
	}
	
	pushup(x);
	
//	printf("%d: d-%d p-%d\n", x, dmin[x], pmin[x]);
}

int minv, minp;

inline void find(int x, int d) {
	if (d + dmin[x] < minv) {
		minv = d + dmin[x];
		minp = x;
	}
	if (fa(x)) {
		if (ftox2[x] > 0) d--;
		else d++;
		find(fa(x), d);
	}
}

inline void moveup(int x, int t) {
//	printf("up: %d\n", x);
	if (x == t) return;
	if (ftox2[x] > 0) {
		ftox2[x]--;
		ftox1[x]++;
	} else {
		xtof1[x]--;
		xtof2[x]++;
	}
	pushup(x);
	pushup(fa(x));
	moveup(fa(x), t);
}

inline void movedown(int x, int t) {
//	printf("down: %d %d\n", x, flg[x]);
	if (x == t) {
		c[t]--;
//		printf("c[%d] = %d\n", t, c[t]);
		pushup(x);
		return;
	}
	if (flg[x] == lc(x)) {
		if (xtof2[lc(x)] > 0) {
			xtof2[lc(x)]--;
			xtof1[lc(x)]++;
		} else {
			ftox1[lc(x)]--;
			ftox2[lc(x)]++;
		}
		movedown(lc(x), t);
		pushup(lc(x));
	} else {
		if (xtof2[rc(x)] > 0) {
			xtof2[rc(x)]--;
			xtof1[rc(x)]++;
		} else {
			ftox1[rc(x)]--;
			ftox2[rc(x)]++;
		}
		movedown(rc(x), t);
		pushup(rc(x));
	}
	pushup(x);
}

inline void movetop(int x) {
//	printf("top: %d\n", x);
	pushup(x);
	if (x <= 1) return;
	pushup(fa(x));
	movetop(fa(x));
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &c[i]);
		xtof1[i] = 1;
		xtof2[i] = 0;
		ftox1[i] = 1;
		ftox2[i] = 0;
	}
	build(1);
	int p, sum = 0;
	for (int i = 1; i <= m; i++) {
//		build(1);
		scanf("%d", &p);
		minv = INF, minp = -1;
		find(p, 0);
		sum += minv;
		int lca = minp;
		int t = pmin[lca];
//		printf("%d->%d->%d\n", p, lca, t);
		moveup(p, lca);
		movetop(lca);
		movedown(lca, t);
		movetop(lca);
		printf("%d ", sum);
	}
	return 0;
}
```

---

## 作者：UperFicial (赞：2)

[传送门](https://www.luogu.com.cn/problem/P6122)

同步发表于我的 [$\texttt{cnblog}$](https://www.cnblogs.com/UperFicial/p/16178283.html)。

### $\texttt{Description}$

有一棵 $n$ 个节点的完全二叉树，第 $i$ 个点最多贮存 $c_i$ 只鼹鼠，有 $m$ 只鼹鼠依次醒来，对于 $\forall k\in[1,m]$ 输出前 $k$ 只鼹鼠醒来后最少的运动长度总和。

$1\le n\le 10^5$。

### $\texttt{Solution}$

考虑暴力建图：

- 从 $s$ 向每只鼹鼠睡觉的地方连一条容量为 $1$，费用为 $0$ 的边。表示有 $1$ 只鼹鼠在某个洞里。

- 对于树上一个点，连向它能到达的点，容量为 $\infty$，费用为 $1$。表示一条边可以经过多只鼹鼠，但是需要一个单位的长度。

- 每个点向 $t$ 连一条容量为 $c_i$，费用为 $0$ 的边，表示一个终点的容量。

但这样建图是 $\Theta(nm)$ 的，边数也是 $nm$ 级别的，显然 [$\text{TLE}$](https://www.luogu.com.cn/record/74369874)。

那么唯一的办法，就是用摸你肺用流的思路来优化。

考虑加入了第 $i$ 个点，$s$ 与前 $i-1$ 个点之间的流量肯定是满流了，因为不会有无解的情况，所以每个点都到达相应的目的地。

回顾最小费用最大流的代码，现需要找到一条从 $s\to t$ 的增广路。

而只有点 $i$ 满足 $s$ 与 $i$ 的残余流量非 $0$，所以只需要找到 $i\to t$ 的增广路。也就是距离 $i$ 最短，并且还有食物的点。

考虑 $\texttt{DP}$。

我们设 $f_i$ 表示第 $i$ 个点到它为根的子树中的一个还有食物点的最近点的距离，$g_i$ 表示相应的点的编号。

子树外的点是无法进行 $\texttt{DP}$ 的，但是我们可以暴力向上跳父亲，因为这是一棵完全二叉树，树高是 $\log n$ 的。所以对于每一个父亲 $j$ 将 $f_i$ 对 $f_j$ 进行更新。复杂度是 $\Theta(\log n)$ 的。

第一步，我们先找到距离 $i$ 最近的点，设为 $v$，并求出 $v$ 对应的 $i$ 的祖先 $u$，累计路径距离。

之后对于 $i\to u$ 路径上的所有边容量减一，并暴力修改 $f$ 和 $g$ 的值。当然 $v\to u$ 路径上也应该进行相应的修改，只不过流量加一，因为我们这里走的是反向边。

最后暴力从 $u$ 跳根修改即可。

---

## 作者：dengjunhaodejia09 (赞：2)

这题还是要写拍呀。

考虑正常做不好做，考虑建出费用流模型。

将每一个点向四周连容量为正无穷，费用为一的边，而醒着的鼠鼠由原点连一条流量为一，费用为零的边，有物资的点向汇点连一条容量为物资数量，费用为零的边，就可以模拟鼠鼠的偷吃了。

费用流肯定是不可能的，但我们发现每次加点只用在上一个的残量网络上跑即可，试着模拟费用流。

那么我们就是要每次找最短路，每次将路径上的边容量减一，并增加容量为一的反向边。

发现第一个操作可以记录子树内的最近点，然后不断跳父亲即可，而其他的操作直接暴力跑路径即可，发现只有路径上的点以及他们的祖先子树内最短路会改变，暴力更改即可。

复杂度带一个树高，但此题是完全二叉树，所以直接这么写就可以了。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int a[200006],dep[200005],b[200005],Son[200005],Son_id[200005],ch[200005][2],fa[200005],num_ch[200005][2],num_fa[200005];
void chonggou(int id){
    Son[id]=2e9;
    Son_id[id]=-1;
    if(a[id]>0){
        Son[id]=0;
        Son_id[id]=id;
    }
    int bian0=(num_ch[id][0]>0?-1:1),bian1=(num_ch[id][1]>0?-1:1);
    if(ch[id][0]){
        if(Son_id[ch[id][0]]!=-1 && Son[ch[id][0]]+bian0<Son[id]){
            Son[id]=Son[ch[id][0]]+bian0;
            Son_id[id]=Son_id[ch[id][0]];
        }
    }
    if(ch[id][1]){
        if(Son_id[ch[id][1]]!=-1 && Son[ch[id][1]]+bian1<Son[id]){
            Son[id]=Son[ch[id][1]]+bian1;
            Son_id[id]=Son_id[ch[id][1]];
        }
    }
}
void build(int id){
    if(ch[id][0]){
        build(ch[id][0]);
    }
    if(ch[id][1]){
        build(ch[id][1]);
    }
    chonggou(id);
}
int insert(int id){
    int to=-1,Min=2e9;
    if(Son_id[id]){
        Min=Son[id];
        to=Son_id[id];
    }
    int yid=id,lu=0,yy=id;
    while(fa[id]){
        lu+=(num_fa[id]>0?-1:1);
        id=fa[id];
        if(a[id]>0){
            if(Min>lu){
                Min=lu;
                to=id;
            }
        }
        int opt=(ch[id][1]==yid);
        int bian=0;
        if(opt==0){
            bian=(num_ch[id][1]>0?-1:1);
        }else{
            bian=(num_ch[id][0]>0?-1:1);
        }
        if(lu+bian+Son[ch[id][opt^1]]<Min && ch[id][opt^1]!=0){
            Min=lu+bian+Son[ch[id][opt^1]];
            to=Son_id[ch[id][opt^1]];
        }
        yid=id;
    }
    id=yy;
    int yida=id,ytoa=to;
    while(dep[id]>dep[to]){
        num_fa[id]=num_fa[id]-1;
        num_ch[fa[id]][(ch[fa[id]][1]==id)]++;
        id=fa[id];
    }
    while(dep[id]<dep[to]){
        num_fa[to]++;
        num_ch[fa[to]][(ch[fa[to]][1]==to)]=num_ch[fa[to]][(ch[fa[to]][1]==to)]-1;
        to=fa[to];
    }
    while(fa[id]!=fa[to]){
        num_fa[id]=num_fa[id]-1;
        num_ch[fa[id]][(ch[fa[id]][1]==id)]++;
        id=fa[id];
        num_fa[to]++;
        num_ch[fa[to]][(ch[fa[to]][1]==to)]=num_ch[fa[to]][(ch[fa[to]][1]==to)]-1;
        to=fa[to];
    }
    if(id!=to){
        num_fa[id]=num_fa[id]-1;
        num_ch[fa[id]][(ch[fa[id]][1]==id)]++;
        id=fa[id];
        num_fa[to]++;
        num_ch[fa[to]][(ch[fa[to]][1]==to)]=num_ch[fa[to]][(ch[fa[to]][1]==to)]-1;
        to=fa[to];
    }
    id=yida;
    to=ytoa;
    a[to]--;
    while(dep[id]>dep[to]){
        chonggou(id);
        id=fa[id];
    }
    while(dep[id]<dep[to]){
        chonggou(to);
        to=fa[to];
    }
    while(fa[id]!=fa[to]){
        chonggou(id);
        id=fa[id];
        chonggou(to);
        to=fa[to];
    }
    chonggou(to);
    chonggou(id);
    to=fa[to];
    while(to){
        chonggou(to);
        to=fa[to];
    }
    return Min;
}
signed main(){
    // freopen("1.in","r",stdin);
    // freopen("1.out","w",stdout);
    cin>>n>>m;
    dep[1]=1;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(i>1){
            if(ch[i/2][0]==0){
                ch[i/2][0]=i;
                fa[i]=i/2;
            }else{
                ch[i/2][1]=i;
                fa[i]=i/2;
            }
            dep[i]=dep[fa[i]]+1;
        }
    }
    build(1);
    for(int i=1;i<=m;i++){
        cin>>b[i];
    }
    int ans=0,sum=0;
    for(int i=1;i<=m;i++){
        ans+=insert(b[i]);
        cout<<ans<<' ';
    }
    return 0;
}
```

---

## 作者：lfxxx (赞：1)

模拟费用流基础练习题。

考虑如下费用流连边：每只鼹鼠连边 $(S,p_i,1,0)$，每条树边连边 $(u,v,\infty,1),(v,u,\infty,1)$，每个点连边 $(u,T,c_u,0)$。

问题被我们转化为每次给第 $i$ 只鼹鼠流量后的最小费用最大流。

观察一下这个图中只有树边的反边是有意义的，因为连向源点或者汇点的边取反后如果要走就有负环了，并且树边的反边意义是撤销经过其的流量。

观察到每次增广必是从 $p_i$ 出发走到一个 $j$，因为最短路没有负环的情况下不会走重复点，所以这次增广的代价就是 $p_i$ 到 $j$ 的最小费用简单路径。

于是考虑 $dp_i$ 表示从点 $i$ 出发到其子树中的点的最小费用路径，并记下最优决策，每次加入点时枚举 $lca(p_i,j)$，并计算相对应的最小费用路径，取出最小的增广并暴力给增广路上的边的反边加流量即可。然后在从 $p_i,j$ 出发向上 pushup 更新 $dp_i$。

时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5+114;
const int inf = 1e18;
int dep[maxn],n,m;
pair<int,int> dp[maxn];//u 到子树内存在点的最小权 子树内最小点
int fa[maxn],son[maxn][2];//到父亲 到左右儿子的反边（费用为 -1）数量
int c[maxn];
void pushup(int u){ 
    if(u==0) return ;
    dp[u]=make_pair(inf,-1);
    if(c[u]>0) dp[u]=min(dp[u],make_pair(0*1ll,u));
    if((u<<1)<=n){
        if(son[u][0]>0) dp[u]=min(dp[u],make_pair(dp[u<<1].first-1,dp[u<<1].second));
        else dp[u]=min(dp[u],make_pair(dp[u<<1].first+1,dp[u<<1].second));     
    }
    if((u<<1|1)<=n){
        if(son[u][1]>0) dp[u]=min(dp[u],make_pair(dp[u<<1|1].first-1,dp[u<<1|1].second));
        else dp[u]=min(dp[u],make_pair(dp[u<<1|1].first+1,dp[u<<1|1].second));       
    }
    pushup(u>>1);
}
void solve(int u,int v){
    //u to v 增广
    while(u!=v){
        if(dep[u]>dep[v]) (fa[u]>0?fa[u]--:son[u>>1][u&1]++),u>>=1;
        else (son[v>>1][v&1]>0?son[v>>1][v&1]--:fa[v]++),v>>=1;
    }
    return ;
}
void dfs(int u){
    if(u>n) return ;
    dep[u]=dep[u>>1]+1;
    dfs(u<<1),dfs(u<<1|1);
    pushup(u);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>c[i];
    dfs(1);
    int ans=0;
    for(int i=1;i<=m;i++){
        int u;
        cin>>u;
        pair<int,int> ch=dp[u];
        int x=u;
        int s=0;
        while(x>1) s+=(fa[x]>0?1:-1),x>>=1,ch=min(ch,make_pair(dp[x].first-s,dp[x].second));
        ans+=ch.first;
        int v=ch.second;
        solve(u,v);
        c[v]--;
        pushup(u),pushup(v);
        cout<<ans<<' ';
    }
    return 0;
}
```

---

## 作者：xfrvq (赞：1)

反悔贪心，虚高黑题。但尝试不借助网络流说明，希望会好理解一些。

我们从 $1$ 到 $m$ 加鼹鼠，每轮找离当前鼹鼠 $p$ 最近的洞并填上。一条鼹鼠到洞的路径一定是先跳父亲后跳儿子。我们树形 dp 维护子树内有洞的最近点，从 $p$ 开始暴力跳父亲求出离它的最近洞。填洞后更新链的 dp 信息即可。

这样无正确性。考虑最重要的反悔操作。

注意到**当一条树边被下到上，上到下各经过一次，不如都不经过**。假设边 $(u,v)$ 被两条路径 $s_1\to u\to v\to t_1,s_2\to v\to u\to t_2$ 经过，那么 $s_1\to u\to t_2,s_2\to v\to t_1$ 满足要求同时可省下 $2$ 的答案。

于是我们先设边权为 $1$，走过一条边后，把它的反向边边权设为 $-1$，走它便可以抵消代价。

**注意到一条 $-1$ 边只能用一次，但一个位置可以有多条边**。我们设 $c_i$ 为**一条边被下到上经过的次数，减去上到下经过的次数**，（人话就是）$c_i\gt0$ 时有多余的下到上边，此时上到下的边权是 $-1$。$c_i\lt0$ 时有多余的上到下边，此时下到上的边权是 $-1$。

dp 需要用到边权信息。我们在更新链的 dp 信息前更新 $c_i$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

using pr = pair<int,int>;

const int N = 2e5 + 5;

int n,m,tot,a[N],p[N],c[N];
pr f[N];

void psu(int i){
	f[i] = a[i] ? pr(0,i) : pr(N,0);
	if(i * 2 <= n) f[i] = min(f[i],pr(f[i * 2].first + (c[i * 2] < 0 ? -1 : 1),f[i * 2].second));
	if(i * 2 + 1 <= n) f[i] = min(f[i],pr(f[i * 2 + 1].first + (c[i * 2 + 1] < 0 ? -1 : 1),f[i * 2 + 1].second));
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;++i) scanf("%d",a + i),f[i] = a[i] ? pr(0,i) : pr(N,0);
	for(int i = n;i >= 1;--i) psu(i);
	for(int i = 1,p;i <= m;++i){
		scanf("%d",&p);
		pr s(N,0);
		for(int j = p,t = 0;j >= 1;j /= 2)
			s = min(s,pr(f[j].first + t,j)),t += (c[j] > 0 ? -1 : 1);
		int q = f[s.second].second; --a[q];
		for(int j = q;j != s.second;j /= 2) ++c[j],psu(j);
		for(int j = p;j != s.second;j /= 2) --c[j],psu(j);
		for(int j = s.second;j >= 1;j /= 2) psu(j);
		printf("%d ",tot += s.first);
	}
	return 0;
}
```

---

