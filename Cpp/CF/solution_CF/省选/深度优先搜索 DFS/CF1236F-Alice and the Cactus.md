# Alice and the Cactus

## 题目描述

Alice recently found some cactuses growing near her house! After several months, more and more cactuses appeared and soon they blocked the road. So Alice wants to clear them.

[A cactus](https://en.wikipedia.org/wiki/Cactus_graph) is a connected undirected graph. No edge of this graph lies on more than one simple cycle. Let's call a sequence of different nodes of the graph $ x_1, x_2, \ldots, x_k $ a simple cycle, if $ k \geq 3 $ and all pairs of nodes $ x_1 $ and $ x_2 $ , $ x_2 $ and $ x_3 $ , $ \ldots $ , $ x_{k-1} $ and $ x_k $ , $ x_k $ and $ x_1 $ are connected with edges. Edges $ (x_1, x_2) $ , $ (x_2, x_3) $ , $ \ldots $ , $ (x_{k-1}, x_k) $ , $ (x_k, x_1) $ lies on this simple cycle.

There are so many cactuses, so it seems hard to destroy them. But Alice has magic. When she uses the magic, every node of the cactus will be removed independently with the probability $ \frac{1}{2} $ . When a node is removed, the edges connected to it are also removed.

Now Alice wants to test her magic. She has picked a cactus with $ n $ nodes and $ m $ edges. Let $ X[S] $ (where $ S $ is a subset of the removed nodes) be the number of connected components in the remaining graph after removing nodes of set $ S $ . Before she uses magic, she wants to know [the variance](https://en.wikipedia.org/wiki/Variance) of random variable $ X $ , if all nodes of the graph have probability $ \frac{1}{2} $ to be removed and all $ n $ of these events are independent. By the definition the variance is equal to $ E[(X - E[X])^2] $ , where $ E[X] $ is the [expected value](https://en.wikipedia.org/wiki/Expected_value) of $ X $ . Help her and calculate this value by modulo $ 10^9+7 $ .

Formally, let $ M = 10^9 + 7 $ (a prime number). It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, find such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first sample, the answer is $ \frac{7}{64} $ . If all nodes are removed the value of $ X $ is equal to $ 0 $ , otherwise, it is equal to $ 1 $ . So, the expected value of $ X $ is equal to $ 0\times\frac{1}{8}+1\times\frac{7}{8}=\frac{7}{8} $ . So, the variance of $ X $ is equal to $ (0 - \frac{7}{8})^2\times\frac{1}{8}+(1-\frac{7}{8})^2\times\frac{7}{8} = (\frac{7}{8})^2\times\frac{1}{8}+(\frac{1}{8})^2\times\frac{7}{8} = \frac{7}{64} $ .

In the second sample, the answer is $ \frac{1}{4} $ .

## 样例 #1

### 输入

```
3 3
1 2
2 3
1 3
```

### 输出

```
984375007```

## 样例 #2

### 输入

```
5 6
1 2
2 3
1 3
3 4
4 5
3 5
```

### 输出

```
250000002```

# 题解

## 作者：9AC8E2 (赞：10)

先%一发zyk

![](https://cdn.luogu.com.cn/upload/image_hosting/p6sdawv6.png)

先考虑把方差拆开
$$D(X)=\sum_{i}(x_i-E(X))^2\times p_i$$
$$D(X)=\sum_{i}x_i^2\times p_i-2\times \sum_{i}x_i\times E(X)\times p_i+\sum_{i}E(X)^2\times p_i$$
$$D(X)=E(X^2)-2\times E(X)^2+E(X)^2\times \sum_{i}p_i$$
$$\sum_ip_i=1$$
$$D(X)=E(X^2)-E(X)^2$$

设$X$为联通块个数，$a$为点数，$b$为边数，$c$为环数
则有
$$X=a-b+c$$
即联通块个数等于点数-边数+环数

根据期望的线性性

$$E(X^2)=E((a-b+c)^2)$$
$$=E(a^2+b^2+c^2+2ac-2ab-2bc)$$
$$=E(a^2)+E(b^2)+E(c^2)+2E(ac)-2E(ab)-2E(bc)$$

然后考虑每个期望怎么求
### $E(a^2)$
#### 解法一
直接写出式子$E(a^2)=\frac{\sum_{i=0}^{n}i^2\times C_{n}^{i}}{2^n}$

这个式子已经可以$O(n)$算了

不过再优化一下，根据$mC_{m}^{n}=nC_{m-1}^{n-1}$,上式显然等于$\frac{n\times (n+1)}{4}$
#### 解法二
$E(a^2)$等于枚举两个点，可以重复，求他们同时存在的概率的和

对于每个点$i$,考虑另外一个点$j$

- 若$i=j$,概率为$\frac{1}{2}$
- 若$i\not=j$,概率为$\frac{1}{4}$

最后的期望为$\frac{n\times(n+1)}{4}$

### $E(b^2)$
$E(b^2)$等于枚举两条边，可以重复，求他们同时存在的概率的和

对于每条边$i$,考虑另一条边$i$

- 若$i=j$，概率为$\frac{1}{4}$
- 若$i$和$j$相连，概率为$\frac{1}{8}$
- 若$i$和$j$没有什么关系，概率为$\frac{1}{16}$

考虑记录每个点的度数，因为没有重边，显然不会重复计数

### $E(c^2)$
$E(c^2)$等于枚举两个环，可以重复，求他们同时存在的概率的和

考虑先算出每个环$i$的大小$size_i$,共$cnt$个环

那么第$i$个环存在的概率$P_i=\frac{1}{2^{size_i}}$

对于每个环$i$,考虑另一个环$i$

- 若$i=j$，概率为$P_i$
- 若$i$与$j$有一个点相同，概率为$P_i\times P_j\times 2$
- 若$i$与$j$没有什么关系，概率为$P_i\times P_j$

### $E(ab)$
$E(b^2)$等于枚举一个点和一条边，求他们同时存在的概率的和

对于每个点$i$,考虑每一条边$i$

- 若$i$是$j$的一个顶点，概率为$\frac{1}{4}$
- 若$i$和$j$没有什么关系，概率为$\frac{1}{8}$

### $E(ac)$
$E(b^2)$等于枚举一个点和一个环，求他们同时存在的概率的和

对于每个点$i$,考虑每一个环$i$

- 若$i$在$j$上，概率为$P_j$
- 若$i$和$j$没有什么关系，概率为$P_j\times \frac{1}{2}$
### $E(bc)$
$E(b^2)$等于枚举一条边和一个环，求他们同时存在的概率的和

对于每个环$i$,考虑每一条边$i$

- 若$j$在$i$上，概率为$P_i$
- 若$j$有一个点在$i$上，概率为$P_i\times \frac{1}{2}$
- 若$i$和$j$没有什么关系，概率为$P_i\times \frac{1}{4}$

### $E(X)$
$$E(a)=\frac{n}{2}$$
$$E(b)=\frac{m}{4}$$
$$E(c)=\sum_{i=1}^{cnt}P_i$$
$$E(X)=E(a)-E(b)+E(c)$$

[代码在这里](https://www.luogu.com.cn/paste/1pt1bpz1)

---

## 作者：雪颜 (赞：6)

神仙题竟然没题解？作为出题人的好$(xiǎo)$朋$(fěn)$友$(sī)$写个题解。

先考虑如何计算连通块个数：点数-边数+环数。

再考虑把期望拆开：

$E([x-E(x)]^2)=E(x^2-2xE(x)+E(x)^2)=E(x^2)-E(x)^2$

考虑拆开$x^2$：设点数为$a$，边数为$b$，环数为$c$，那么$x=a-b+c  => x^2=a^2+b^2+c^2-2ab-2bc+2ac$ 。

然后讨论点在环上，边在环上，边的一个点在环上，环相交这些情况。

理论上考虑所有相交和不相交的情况应该是线性的，官方题解给出求逆元要$O(nlogn)$，实际上可以线性预处理，所以时间复杂度是线性的。

$PS:$ 特别鸣谢 @双管荧光灯 @iostream 两位神仙的指导

代码：
```cpp
#include<stdio.h>
#include<vector>
#define it register int
#define il inline
#define P 1000000007
using namespace std;
const int N=1000005; 
int d[N],fa[N],i2[N],h[N],nxt[N],adj[N],n,m,rd[N],u,v,t,tot,siz[N],sum[N],sum2[N],sd[N];
bool vs[N];
vector<int> vec[N];
il void add(){nxt[++t]=h[u],h[u]=t,adj[t]=v,nxt[++t]=h[v],h[v]=t,adj[t]=u;}
void dfs(it x){
	vs[x]=1;
	for(it i=h[x],j,k;i;i=nxt[i])
		if((j=adj[i])^fa[x]){
			if(vs[j]){
				if(d[x]>d[j]){
					++tot;
					for(k=x;k^j;k=fa[k]) vec[tot].push_back(k);
					vec[tot].push_back(j),siz[tot]=vec[tot].size();
				}
				continue;
			}
			fa[j]=x,d[j]=d[x]+1,dfs(j);
		}
} 
il int mo(it x){while(x<0) x+=P;while(x>=P) x-=P;return x;}
il int pf(it x){return 1ll*x*x%P;}
il int E(){
	it ans=0;
	for(it i=1;i<=tot;++i) ans=mo(ans+i2[siz[i]]);
	return mo(ans+1ll*n*i2[1]%P-1ll*m*i2[2]%P);
}
il int vv(){return (pf(n)+n+0ll)*i2[2]%P;}  
il int cc(){
	it ans=0,i;
	for(i=1;i<=tot;++i) ans=mo(ans+i2[siz[i]]);
	ans=mo(ans+1ll*ans*ans%P);
	for(i=1;i<=tot;++i) ans=mo(ans-i2[siz[i]<<1]);
	for(i=1;i<=n;++i) ans=mo(ans+pf(sum[i])-sum2[i]);
	return ans;
} 
il int ee(){
	it ans=mo(pf(m)+m);
	for(it i=1;i<=n;++i) ans=mo(ans+pf(rd[i]));
	return 1ll*ans*i2[4]%P;
}
il int vc(){
	it ans=0;
	for(it i=1;i<=tot;++i) ans=mo(ans+1ll*(siz[i]+n)*i2[siz[i]+1]%P);
	return ans;
}  
il int ve(){return (2ll+n)*m%P*i2[3]%P;} 
il int ce(){
	it ans=0;
	for(it i=1;i<=tot;++i)
		ans=mo(ans+1ll*i2[siz[i]]*(siz[i]+1ll*sd[i]*i2[1]%P+1ll*(m-siz[i]-sd[i])*i2[2]%P)%P);
	return ans;
}
int main(){
	scanf("%d%d",&n,&m);it i,j,x=(n>m?n:m);
	i2[0]=1,i2[1]=P+1>>1;
	for(i=2,x=x<20?20:x;i<=x;++i) i2[i]=1ll*i2[i-1]*i2[1]%P;
	for(i=1;i<=m;++i) scanf("%d%d",&u,&v),++rd[u],++rd[v],add();
	dfs(1);
	for(i=1;i<=tot;++i){
		for(j=0;j<siz[i];++j)
			x=vec[i][j],sd[i]+=rd[x],sum[x]=mo(sum[x]+i2[siz[i]]),sum2[x]=mo(sum2[x]+pf(i2[siz[i]]));
		sd[i]-=(siz[i]<<1);
	} 
	printf("%lld",((vv()+cc()+ee()+(vc()-ve()-ce())*2ll%P-pf(E()))%P+P)%P);
	return 0;
}


---

## 作者：DaiRuiChen007 (赞：0)

# CF1236F 题解

[Problem Link](https://www.luogu.com.cn/problem/CF1236F)

**题目大意**

> 给一个 $n$ 个点 $m$ 条边的点仙人掌，随机删掉若干个点，求连通块个数 $X$ 的方差。
>
> 数据范围：$n,m\le 5\times 10^5$。

**思路分析**

根据方差定义，我们要求的就是 $E[X^2]-E^2[X]$，设新图点、边、环的数量分别为 $V,E,C$，则 $X=V-E+C$。

那么得到 $E[X^2]-E^2[X]=E[V^2]+E[E^2]+E[C^2]+2(E[VC]-E[EC]-E[VE])-(E[V]-E[E]+E[C])^2$。

- $E[V^2]$：转成选一对点 $(i,j)$ 被保留的概率，讨论 $i=j$ 或 $i\ne j$ 即可。
- $E[E^2]$：讨论选的一对边是相同、有一个公共点、还是无交。
- $E[C^2]$：讨论选的一对环是相同、有一个公共节点、还是无交。
- $E[VC]$：讨论选的点是否在选的环上。
- $E[EC]$：讨论选的边是在选的环上，还是有一个点相交，还是无交。
- $E[VE]$：讨论选的点是否是所选边的端点。

分类讨论后对于每种情况细节处理即可。

时间复杂度 $\mathcal O(n+m)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=5e5+5,MOD=1e9+7;
struct Edge { int u,v; };
int dsu[MAXN];
inline int find(int x) { while(x^dsu[x]) x=dsu[x]=dsu[dsu[x]]; return x; }
vector <int> G[MAXN];
int Fa[MAXN],dep[MAXN];
inline void dfs(int u,int fa) {
	dep[u]=dep[fa]+1,Fa[u]=fa;
	for(int v:G[u]) if(v^fa) dfs(v,u);
}
int n,m,k,siz[MAXN],deg[MAXN],inv[MAXN];
vector <int> cyc[MAXN],nod[MAXN];
inline int V2() { //E[ |V|^2 ]
	return n*(n+1)%MOD*inv[2]%MOD;
}
inline int E2() { //E[ |E|^2 ]
	int ans=m*m%MOD*inv[4]%MOD;
	ans=(ans+m*(inv[2]+MOD-inv[4])%MOD)%MOD;
	for(int i=1;i<=n;++i) {
		ans=(ans+deg[i]*(deg[i]-1)%MOD*inv[4])%MOD;
	}
	return ans;
}
inline int C2() { //E[ |C|^2 ]
	int ans=0,sum=0;
	for(int i=1;i<=k;++i) sum=(sum+inv[siz[i]])%MOD;
	ans=sum*sum%MOD;
	for(int i=1;i<=k;++i) {
		ans=(ans+inv[siz[i]]+MOD-inv[siz[i]]*inv[siz[i]]%MOD)%MOD;
	}
	for(int i=1;i<=n;++i) {
		int tmp=0;
		for(int j:cyc[i]) tmp=(tmp+inv[siz[j]])%MOD;
		ans=(ans+tmp*tmp%MOD)%MOD;
		for(int j:cyc[i]) ans=(ans+MOD-inv[siz[j]]*inv[siz[j]]%MOD)%MOD;
	}
	return ans;
}
inline int VC() { //E[ |V|*|C| ]
	int ans=0;
	for(int i=1;i<=k;++i) {
		ans=(ans+siz[i]*inv[siz[i]]%MOD)%MOD;
		ans=(ans+(n-siz[i])*inv[siz[i]+1]%MOD)%MOD;
	}
	return ans;
}
inline int VE() { //E[ |V|*|E| ]
	int ans=0;
	for(int i=1;i<=n;++i) {
		ans=(ans+deg[i]*inv[2]%MOD)%MOD;
		ans=(ans+(m-deg[i])*inv[3]%MOD)%MOD;
	}
	return ans;
}
inline int EC() { //E[ |E|*|C| ]
	int ans=0;
	for(int i=1;i<=k;++i) {
		ans=(ans+siz[i]*inv[siz[i]]%MOD)%MOD;
		int tot=m-siz[i];
		for(int j:nod[i]) {
			tot-=deg[j]-2; 
			ans=(ans+(deg[j]-2)*inv[siz[i]+1]%MOD)%MOD;
		}
		ans=(ans+tot*inv[siz[i]+2]%MOD)%MOD;
	}
	return ans;
}
inline int V() {
	return n*inv[1]%MOD;
}
inline int E() {
	return m*inv[2]%MOD;
}
inline int C() {
	int ans=0;
	for(int i=1;i<=k;++i) ans=(ans+inv[siz[i]])%MOD;
	return ans;
}
signed main() {
	scanf("%lld%lld",&n,&m);
	inv[0]=1;
	for(int i=1;i<MAXN;++i) inv[i]=(MOD+1)/2*inv[i-1]%MOD;
	vector <Edge> Edges;
	iota(dsu+1,dsu+n+1,1);
	for(int i=1,u,v;i<=m;++i) {
		scanf("%lld%lld",&u,&v);
		++deg[u],++deg[v];
		int x=find(u),y=find(v);
		if(x==y) Edges.push_back({u,v});
		else {
			G[u].push_back(v);
			G[v].push_back(u);
			dsu[x]=y;
		}
	}
	dfs(1,0);
	for(auto e:Edges) {
		++k;
		int u=e.u,v=e.v;
		while(u^v) {
			if(dep[u]<dep[v]) swap(u,v);
			cyc[u].push_back(k);
			nod[k].push_back(u);
			++siz[k],u=Fa[u];
		}
		++siz[k];
		cyc[u].push_back(k);
		nod[k].push_back(u);
	}
	int ex=(V2()+C2()+E2())%MOD;
	int ep=(VC()+MOD-VE()+MOD-EC())%MOD;
	int e=(V()+C()+MOD-E())%MOD;
	printf("%lld\n",(ex+ep*2+MOD-e*e%MOD)%MOD);
	return 0;
}
```

---

