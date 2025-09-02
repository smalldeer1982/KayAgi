# President's Path

## 题目描述

#### 题面翻译
对于 $n$ 个点 $m$ 条边的简单无向图（无重边、自环），记 $f(s,t)$ 为 $R_{s,t}$ 类边的数量。$R_{s,t}$ 类边是指这样一类边：存在一条从 $s$ 到 $t$ 的最短路，满足这条边在最短路上。

对于每一对 $s,t$ ，你都要计算出 $f(s,t)$ 的值。

## 样例 #1

### 输入

```
5 6
1 2 1
2 3 1
3 4 1
4 1 1
2 4 2
4 5 4
```

### 输出

```
1 4 1 2 1 5 6 1 2 1 ```

# 题解

## 作者：兮水XiShui丶 (赞：11)

看到这道题之后,我们第一反应肯定是一遍$Floyd$.
然后考虑一下怎么判断某条边是不是被最短路覆盖.
朴素的想法是我们每次枚举边,然后以这条边两条边的端点$u,v$再枚举这两个端点的所有最短路.
即判断 
$$dis(s,u)+w+dis(v,t)==dis(s,t)$$ 
或者
$$dis(s,v)+w+dis(u,t)==dis(s,t)$$

但是这样统计答案的话,由于边的条数为$n^2$的,所以这种算法的总复杂度为$O(n^4)$的.显然过不了
所以我们考虑一下怎么优化.
我们考虑上一个算法的时间复杂度的瓶颈,显然在我们枚举了$s,t$之后,因为还需要枚举每一条边,所以枚举边显然会超时.
所以我们考虑一下枚举完$s,t$之后不再枚举每一条边,而是去枚举每一个中转点$p$.
然后如果我们发现  
$$dis(s,p)+dis(p,t)==dis(s,t)$$
那么显然在$dis(s,p)$上以$p$结尾的边都是可以被加入的.
所以我们现在的问题就只剩下了怎么求在$dis(s,p)$上的点了.
发现我们就算暴力枚举每条边然后验证也并不会超时.
所以直接这样做就可以了

---

## 作者：fade_away (赞：7)

感觉这边题解讲得有点奇怪，我来说说我的理解，虽然本质上是相同的。

首先预处理两两之间的最短路$f_{i,j}$，然后朴素做法是枚举一个点对，然后枚举一条边，看这条边是不是能够出现在最短路上，时间复杂度$O(n^2m)$，不够优秀。

于是我们先枚举起点$S$，考虑这时候的图，我们发现一个重要的事实：**此时我们可以给每条边定向，但不改变答案**。具体地，对于一条边$(u,v,c)$，若$f_{S,u}+c=f_{S,v}$，则它是$u\to v$的边，若$f_{S,v}+c=f_{S,u}$，则它是$v\to u$的边，显然一条边最多被定一个方向，没有被定向的边不会对$S$为起点的最短路产生任何影响。

然后边的贡献就能够规约到点上。具体地，对于一条边$u\to v$，若存在一条$S\to T$的最短路经过$v$，则$u\to v$显然可以被经过，于是可以对于每个点$v$记录以它为入点的边数$cnt_v$。

于是统计答案时，我们可以枚举终点$T$，然后枚举点$x$，若$x$能够在$S\to T$的最短路上，则会产生$cnt_x$的贡献。

时间复杂度$O(n^3+nm)$。

## Code
```cpp
int f[505][505], cnt[505];
struct Enode{ int u, v, c; } E[MAXN];
signed main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
#endif
	int n, m;
	read(n), read(m);
	for (int i = 1; i <= n ; ++ i)
		for (int j = 1; j <= n ; ++ j) f[i][j] = INF;
	for (int i = 1; i <= n ; ++ i) f[i][i] = 0;
	for (int i = 1, u, v, c; i <= m ; ++ i) {
		read(u), read(v), read(c), upmin(f[u][v], c), upmin(f[v][u], c);
		E[i] = (Enode){u, v, c};
	}
	for (int k = 1; k <= n ; ++ k)
		for (int i = 1; i <= n ; ++ i)
			for (int j = 1; j <= n ; ++ j)
				upmin(f[i][j], f[i][k] + f[k][j]);
	for (int i = 1; i <= n ; ++ i) {
		for (int j = 1; j <= n ; ++ j) cnt[j] = 0;
		for (int j = 1; j <= m ; ++ j) {
			if (f[i][E[j].v] == f[i][E[j].u] + E[j].c) ++ cnt[E[j].v];
			if (f[i][E[j].u] == f[i][E[j].v] + E[j].c) ++ cnt[E[j].u];
		}
		for (int j = i + 1; j <= n ; ++ j) {
			int ans = 0;
			for (int k = 1; k <= n ; ++ k)
				if (f[i][j] == f[i][k] + f[k][j]) ans += cnt[k];
			print(ans), putc(' ');
		}
	}
	return 0;
}
```

---

## 作者：墨舞灵纯 (赞：3)

现存的题解理论讲的很详细但是没有代码，

我来补充一下代码实现顺便讲一下思路。

这题一眼$Floyd$大家应该都清楚。然后我们统计有多少条边是更新了最短路的，用它去贡献答案。这个写法很简单，跑一边最短路，然后再枚举每条边检验一下就行。如果还没懂参见代码和注释以及上一篇题解。

时间复杂度$O(n^3)$

```
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm> 
#define it register int
#define il inline
using namespace std; 
const int N=505;
int f[N][N],e[N][N],n,m,cn[N],g[N][N]; 
int main()
{
	scanf("%d%d",&n,&m);
	memset(f,63,sizeof(f));
	memset(g,63,sizeof(g));
	int i,j,k,u,v,x;
	for(i=1;i<=n;++i) f[i][i]=0;
	while(m--)
	{
		scanf("%d%d%d",&u,&v,&x);
		f[u][v]=f[v][u]=g[u][v]=g[v][u]=min(f[u][v],x);
	}
	for(k=1;k<=n;++k)
		for(i=1;i<=n;++i)
			for(j=1;j<=n;++j)
					f[i][j]=f[j][i]=min(f[i][k]+f[k][j],f[i][j]);
	for(i=1;i<=n;++i)
	{
		for(j=1;j<=n;++j) cn[j]=0;
		for(j=1;j<=n;++j)
			for(k=1;k<=n;++k)
				if(f[i][k]+g[k][j]==f[i][j]) ++cn[j];//判断这条边是否在最短路上并累计贡献
		for(j=1;j<=n;++j)
			for(k=1;k<=n;++k)
				if(f[i][k]+f[k][j]==f[i][j]) e[i][j]+=cn[k];//如果(i,j)是由(i,k)和(k,j)拼接起来的，那么以k结尾的点都可以累计贡献 
	}
	for(i=1;i<=n;++i)
		for(j=i+1;j<=n;++j)
		{	
			if(f[i][j]>=1061109567) e[i][j]=0;
			printf("%d ",e[i][j]);
		}
	return 0;
}

```

---

## 作者：Prean (赞：2)

题意：对于所有的 $ (u,v) $，询问有多少条边在这两个点的最短路边集之并内。

考虑对于每一个 $ u $ 建立最短路 DAG 图，问题变成询问唯一的度数为 $ 0 $ 的节点到所有节点路径的并集有多少条边。

倒是很容易想到用 bitset 去做，不过复杂度是 $ O(\frac {n^4} {\omega}) $，应该跑不过去。我们注意到这题 $ O(n^3) $ 可过，所以考虑有没有 $ O(n^2) $ 的暴力。

由于枚举点对是 $ O(n^2) $ 的，考虑把边的计数转化到点上。

令 $ sum[u] $ 表示 $ u $ 的入度，那么 $ (u,v) $ 的路径上有多少条边就转化成了路径并集的权值和，此时就可以使用枚举点对做掉了。

题外话：能不能有更快的做法？

我们发现对于 $ u $ 需要枚举的点一定在其的“子树”之内，所以考虑维护一下子树集合。

然后我们发现 bitset 可以胜任这份工作，不过复杂度是 $ O(\frac {n^3} {\omega}+n^3) $

~~笔者只想快点儿做掉这道题，而且建图的话代码太长了，所以只写了 Floyd 的暴力。~~
```cpp
#include<cstdio>
typedef unsigned uint;
const uint M=505;	
uint n,m,sum[M],a[M][M],d[M][M],ans[M];
inline uint min(const uint&a,const uint&b){
	return a>b?b:a;
}
signed main(){
	register uint i,j,u,v,val;
	scanf("%u%u",&n,&m);
	for(i=1;i<=n;++i){
		for(j=1;j<=n;++j)a[i][j]=a[j][i]=d[i][j]=d[j][i]=0x7fffffff;
		d[i][i]=0;
	}
	for(i=1;i<=m;++i)scanf("%u%u%u",&u,&v,&val),a[u][v]=a[v][u]=d[u][v]=d[v][u]=min(a[u][v],val);
	for(i=1;i<=n;++i){
		for(u=1;u<=n;++u){
			for(v=1;v<=n;++v){
				d[u][v]=min(d[u][v],d[u][i]+d[i][v]);
			}
		}
	}
	for(i=1;i<=n;++i){
		for(u=1;u<=n;++u)sum[u]=ans[u]=0;
		for(u=1;u<=n;++u){
			for(v=1;v<=n;++v){
				if(d[i][u]+a[u][v]==d[i][v])++sum[v];
			}
		}
		for(u=1;u<=n;++u){
			for(v=1;v<=n;++v){
				if(d[i][u]+d[u][v]==d[i][v])ans[v]+=sum[u];
			}
		}
		for(u=i+1;u<=n;++u)printf("%u ",d[i][u]==0x7fffffff?0:ans[u]);
	}
}
```

---

## 作者：李至擎 (赞：0)

提供一种神必做法。

先用 floyd 求一下全源最短路。定义 $d_{s,t}$ 表示 $s,t$ 之间的最短路，那么题目求的就是有多少条边 $(u,v,w)$ 满足 $d_{s,u}+w+d_{v,t}=d_{s,t}$。直接枚举是 $O(n^4)$ 的，我们考虑优化一下枚举的顺序。

枚举 $s,v$，现在式子中的每一项都与且仅与 $s,t$ 中一个有关。移项一下，得到 $d_{s,u}+w=d_{s,t}-d_{v,t}$。先把所有的 $d_{s,u}+w$ 算出来，再枚举 $t$，求刚刚算出来的东西中等于 $d_{s,t}-d_{v,t}$ 的有多少个。

用 map 实现是 $O(n^3\log n)$ 的，会 T。理论上 unordered_map 是哈希表，随机数据均摊 $O(1)$，应该不会超时，但是它确实 T 了。（或许手写哈希表可以过，但我没试）

怎么办？我们利用哈希的思想，把这两项对一个大质数取模，这样就可以丢到桶里统计答案了。时间复杂度 $O(n^3)$。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e18,M=12255871; 
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int d[505][505],g[505][505],ans[505][505],B[12255875];
signed main(){
	int n=read(),m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			d[i][j]=(i==j)?0:inf;
		}
	}
	for(int i=1,u,v,w;i<=m;i++){
		u=read(),v=read(),w=read();
		g[u][v]=g[v][u]=w;
		d[u][v]=d[v][u]=w;
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
			}
		}
	}
	for(int s=1;s<=n;s++){
		for(int v=1;v<=n;v++){
			for(int u=1;u<=n;u++){
				if(g[u][v]!=0)B[(d[s][u]+g[u][v])%M]++;
			}
			for(int t=s+1;t<=n;t++){
				ans[s][t]+=B[((d[s][t]-d[v][t])%M+M)%M];
			}
			for(int u=1;u<=n;u++){
				if(g[u][v]!=0)B[(d[s][u]+g[u][v])%M]--;
			}
		}
	}
	for(int s=1;s<=n;s++){
		for(int t=s+1;t<=n;t++){
			printf("%lld ",ans[s][t]);
		}
	}
	return 0;
}
```

---

