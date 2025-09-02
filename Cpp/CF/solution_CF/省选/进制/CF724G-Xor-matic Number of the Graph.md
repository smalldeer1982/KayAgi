# Xor-matic Number of the Graph

## 题目描述

给你一个无向图，有n个顶点和m条边，每条边上都有一个非负权值。

我们称一个三元组  $(u,v,s)$ 是有趣的，当且仅当对于 $1 \le u < v \le n$ 且有一条从 $u$ 到 $v$ 的路径(可以经过相同的点和边多次)，其路径上的权值异或和为  $s$。对于一条路径，如果一条边经过了多次，则计算异或和时也应计算多次。不难证明，这样的三元组是有限的。

计算所有有趣的三元组中 $s$ 的和对于 $10^9+7$ 的模数

## 样例 #1

### 输入

```
4 4
1 2 1
1 3 2
2 3 3
3 4 1
```

### 输出

```
12
```

## 样例 #2

### 输入

```
4 4
1 2 1
2 3 2
3 4 4
4 1 8
```

### 输出

```
90
```

## 样例 #3

### 输入

```
8 6
1 2 2
2 3 1
2 4 4
4 5 5
4 6 3
7 8 5
```

### 输出

```
62
```

# 题解

## 作者：小粉兔 (赞：23)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/CF724G.html](https://www.cnblogs.com/PinkRabbit/p/CF724G.html)。

题目传送门：[CF724G](https://codeforces.com/problemset/problem/724/G)。

### 题意简述：

一张 $n$ 个点的无向图，边有边权。

定义三元组 $(u,v,w)(1\le u < v\le n)$ 合法当且仅当存在从点 $u$ 到点 $v$ 存在一条边权异或和为 $w$ 的路径，经过多次的边需要算多次。

求所有合法三元组的 $w$ 值之和对 $10^9+7$ 取模的值。

### 题解：

比较简单的线性基和图结合的题目，需要用到线性基的一些基本性质。

对异或线性基在图上的应用稍有了解的同学很快可以发现结论：

- 对于连通无向图 $G=(V,E)$ 以及 $G$ 的一棵生成树 $T$：  
- $G$ 中所有环（简单或非简单环）的异或和均可以被生成树中所有返祖边 $(x\to y)$ 对应的环 $(y\sim x\to y)$ 的异或和组成的线性基 $B$ 表示出来。  
- 点 $u$ 到点 $v$ 所有路径的异或和可以被 $T$ 中 $u$ 到 $v$ 的路径的异或和异或上线性基 $B$ 表示出来。  
- 更进一步地，$T$ 中 $u$ 到 $v$ 的路径的异或和等于 $u$ 到根的路径的异或和异或 $v$ 到根的路径的异或和。  
- 所以 $u$ 到 $v$ 所有路径的异或和等于 $d_u\oplus d_v\oplus B$，其中 $d_x$ 表示 $x$ 到根的路径的异或和。

对于一对 $(u,v)$，尝试统计 $d_u\oplus d_v\oplus B$ 中所有数的和。

直接做并不是很好做，考虑按位分开做：  
- 对于线性基 $B$ 和二进制位 $w$，有结论：  
- 设 $B$ 中元素个数为 $S$，则 $B$ 可以表示出 $2^S$ 个不同的数。  
- 如果 $B$ 中存在二进制第 $w$ 位为 $1$ 的数，则那 $2^S$ 个数中恰有 $2^{S-1}$ 个数的二进制第 $w$ 位为 $1$，另外 $2^{S-1}$ 个数的二进制第 $w$ 位为 $0$。  
- 如果 $B$ 中不存在二进制第 $w$ 位为 $1$ 的数，显然不可能表示出二进制第 $w$ 位为 $1$ 的数，全部 $2^S$ 个数的二进制第 $w$ 位均为 $0$。  
可以通过组合恒等式 $\sum_{i=0}^{n}\binom{n}{i}[i\bmod 2=1]=\begin{cases}0&,n=0\\2^{n-1}&,n>0\end{cases}$ 证明。

统计每一位有多少种能被表示出来的方式，统计进答案即可。

这样需要枚举 $(u,v)$，其实很简单就能优化。

直接枚举二进制位 $w$，考虑线性基 $B$ 中是否存在二进制第 $w$ 位为 $1$ 的数。

如果存在，这意味着无论 $d_u,d_v$ 的二进制第 $w$ 位是否为 $1$，都恰有 $2^{S-1}$ 条使得异或和的二进制第 $w$ 位为 $1$ 的路径。  
这意味着 $u,v$ 可以随便选，对答案的贡献为 $2^w2^{S-1}\binom{n}{2}$。

如果不存在，这意味着 $d_u,d_v$ 的二进制第 $w$ 位必须恰有一个为 $1$，并且此时存在 $2^S$ 条使得异或和的二进制第 $w$ 位为 $1$ 的路径。  
这意味着 $d_u,d_v$ 的第 $w$ 位必须恰有一个为 $1$，记第 $w$ 位为 $1$ 的 $d_x$ 的个数为 $x$，对答案的贡献为 $2^w2^Sx(n-x)$。

最后注意原图不一定联通，对于每个联通块分别计算即可。

时间复杂度 $\mathrm{O}(n\log^2t_i)$。

```cpp
#include <cstdio>
#include <cstring>

typedef long long LL;
const int Mod = 1000000007;
const int MN = 100005;
const int MM = 400005;

int N, M;
int h[MN], nxt[MM], to[MM], tot; LL w[MM];
inline void ins(int x, int y, LL z) { nxt[++tot] = h[x], to[tot] = y, w[tot] = z, h[x] = tot; }

LL B[60]; int C;
inline void Add(LL x) {
	for (int j = 59; ~j; --j) if (x >> j & 1)
		if (!B[j]) { B[j] = x, ++C; break; }
		else x ^= B[j];
}

bool vis[MN];
LL d[MN];
int s[MN], t;

void DFS(int u, LL v) {
	vis[u] = 1, d[u] = v, s[++t] = u;
	for (int i = h[u]; i; i = nxt[i]) {
		if (vis[to[i]]) Add(v ^ d[to[i]] ^ w[i]);
		else DFS(to[i], v ^ w[i]);
	}
}

LL Ans;

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; ++i) {
		int x, y; LL z;
		scanf("%d%d%lld", &x, &y, &z);
		ins(x, y, z); ins(y, x, z);
	}
	for (int i = 1; i <= N; ++i) if (!vis[i]) {
		memset(B, 0, sizeof B), C = t = 0;
		DFS(i, 0);
		for (int j = 0; j < 60; ++j) {
			LL c = (1ll << j) % Mod;
			bool ok = 0;
			for (int k = 0; k < 60; ++k) if (B[k] >> j & 1) ok = 1;
			if (ok) Ans = (Ans + (LL)t * (t - 1) / 2 % Mod * ((1ll << C - 1) % Mod) % Mod * c) % Mod;
			else {
				int x = 0;
				for (int i = 1; i <= t; ++i) if (d[s[i]] >> j & 1) ++x;
				Ans = (Ans + (LL)x * (t - x) % Mod * ((1ll << C) % Mod) % Mod * c) % Mod;
			}
		}
	}
	printf("%d\n", (LL)Ans % Mod);
	return 0;
}
```

---

## 作者：jun头吉吉 (赞：10)

# 一道很~~玄学~~的线性基+图论题
做这道题前建议先去做一下[[WC2011]最大XOR和路径](https://www.luogu.com.cn/problem/P4151)

~~这里假装所有人都会**最大XOR和路径**~~

根据最大XOR和路径的经验我们肯定是要找环，于是我们高高兴兴地打上了找环的板子。
```cpp
void dfs(x,res){
	dis[x]=res;
	flag[x]=true;
	For(x){	
		if(!flag[v(G)])dfs(v(G),res^w(G));
		else Base.insert(res^w(G)^dis[v(G)]);
	} 
}
```
###### 然后呢？

![一张图](https://cdn.luogu.com.cn/upload/image_hosting/cazkkkje.png)

经过观察我们发现，$i\to j$的简单路径的异或和就等于$dis_i\oplus dis_j$

于是我们高高兴兴地打了两个```for```循环，再枚举线性基中所有的情况，然后高高兴兴地地**TLE**了

因此我们必须有一种复杂度更优的算法

___

我们考虑能不能按位来考虑贡献。如果某一个环的第$i$位为$1$,那说明任意取两个点，异或这个环，就肯定可以让第$i$位为$1$,又因为线性基里面最高位为$i$的不能选，因此任意两个点之间的路径有$2^{|S|-1}$条，对答案的贡献为
$$\binom{2}{n}\times 2^i\times 2^{|S|-1}$$

那如果没有环第$i$位为$1$，那么只有$dis_{(2)}$第$i$位为$1$的点与$dis_{(2)}$第$i$位为$0$的点之间的简单路径才会使第$i$为变成一。此时线性基中的数可以随便取。设一共有$pos$个点，$cnt$个第$i$位为$1$($pos-cnt$个为$0$)。那么对答案的贡献就为：
$$2^i\times 2^{|S|}\times cnt\times (pos-cnt)$$

于是代码就很好写了（**注意卡常**）

```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;char c=getchar();bool f=false;
	for(;!isdigit(c);c=getchar())f!=c=='-';
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	if(f)x=-x;
}
template<typename T ,typename ...Arg>
inline void read(T &x,Arg &...args){
	read(x);read(args...);
}
template<typename T>
inline void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
typedef long long ll;
const int maxn_wei=63;
int pw[maxn_wei];
struct Linear_Basis{
	ll b[maxn_wei];int size;
	bool flag[maxn_wei];
	inline void init(){size=0;memset(b,0,sizeof b);memset(flag,0,sizeof flag);}
	inline void insert(ll x){
		//printf("Insert %lld\n",x);
		for(int i=maxn_wei-1;i>=0;i--)
			flag[i]|=((x&(1ll<<i))!=0);
		for(int i=maxn_wei-1;i>=0;i--){
			if(!(x&(1ll<<i)))continue;
			if(!b[i]){size++;b[i]=x;return;}
			x^=b[i];
		}
	}
	inline void print(){for(int i=maxn_wei-1;i>=0;i--)printf("%d %d\n",b[i],flag[i]);printf("\n");}
}B;
const int maxn=1e5+10;
const int maxm=2e5+10;
struct Graph{
	struct node{int v;ll w;int nxt;}e[maxm*4];
	int cnt,head[maxn*2];
	void add(int x,int y,ll w){e[++cnt]=(node){y,w,head[x]};head[x]=cnt;}
	#define For(G,x) for(int __=(G).head[x];__;__=(G).e[__].nxt)
	#define v(G) (G).e[__].v
	#define w(G) (G).e[__].w
	
}G;
int cnt[maxn_wei];
int n,m,u,v,pos;ll w;
bool vis[maxn];
ll dis[maxn];
const ll mod=1e9+7;
inline ll fpow(int b){
	ll a=2,ret=1;
	while(b){
		if(b&1)ret=ret*a%mod;
		a=a*a%mod,b>>=1;
	}
	return ret;
}
void dfs(int x,ll res,int fa){
	//printf("%d %lld\n",x,res);
	vis[x]=true;
	dis[x]=res;pos++;
	for(int i=0;i<maxn_wei;i++)
		if(res&(1ll<<i))cnt[i]++;
	For(G,x){
		if(v(G)==fa)continue;
		if(!vis[v(G)])dfs(v(G),res^w(G),x);
		else B.insert(res^w(G)^dis[v(G)]);
	}
}
ll ans=0;
inline ll C(ll x){
	return x*(x-1)*500000004%mod;
}
signed main(){
	//freopen("ttt.in","r",stdin); 
	pw[0]=1;
	for(int i=1;i<maxn_wei;i++)pw[i]=(pw[i-1]<<1)%mod;
	read(n,m);
	for(int i=1;i<=m;i++){read(u,v,w);G.add(u,v,w),G.add(v,u,w);}
	for(int i=1;i<=n;i++)
		if(!vis[i]){
			memset(cnt,0,sizeof cnt);
			B.init();
			pos=0;
			dfs(i,0,-1);
			//B.print();
			for(int j=0;j<maxn_wei;j++){
				if(B.flag[j])ans=(ans+1ll*C(pos)*pw[j]%mod*pw[B.size-1])%mod;
				else ans=(ans+1ll*cnt[j]*(pos-cnt[j])%mod*pw[j]%mod*pw[B.size])%mod; 
			}
		}
	write(ans);
}
```

---

## 作者：Alex_Wei (赞：7)

一道有趣的线性基题目的 $\mathcal{O}(n\log v)$ 做法。

类比最大 XOR 和路径可知，我们先求出该图的任意一棵 DFS 树，并分别记录从根到当前节点的异或和 $cur_i$。同时，求出所有简单环的异或和丢到线性基里面，然后按位考虑贡献。

不妨设线性基大小为 $sz$ 且当前位为 $i$，那么求出所有第 $i$ 位为 $0$ 和 $1$ 的 $cur_j$ 的个数，分别记为 $z(ero)$ 和 $o(ne)$。这样，我们可以算出当前位异或起来为 $0$ 和 $1$ 的数对个数，分别记为 $s(ame)$ 和 $d(iff)$。计算方法是简单的：$s=\dbinom z 2+\dbinom o 2$，$d=z\times o$。

若线性基内所有数的**或**的第 $i$ 位为 $1$，则表示线性基一共异或出 $2^{sz-1}$ 个第 $i$ 位为 $0$ 或者 $1$ 的数（即为 $0$ 和为 $1$ 的数的个数都是 $2^{sz-1}$）。很好证明，线性基内第 $i$ 位为 $0$ 的数可以任意选，而为 $1$ 的数（设个数为 $c$）只能选奇数个，后者我们知道是 $2^{c-1}$ 种方案（经典组合数等式）。因此，当前位对答案的贡献为 $(s+d)\times 2^i\times 2^{sz-1}$。

否则，线性基一共能异或出 $2^{sz}$ 个第 $i$ 位为 $0$ 的数，故贡献为 $d\times 2^i\times 2^{sz}$。

时间复杂度 $\mathcal{O}(n\log v)$。$v$ 是值域。

```cpp
const int N=1e5+5;
const int L=60;
const ll mod=1e9+7;
const ll iv2=mod+1>>1;

int size,cont;
ll sx,a[L];
void insert(ll x){
	for(int i=L-1;~i;i--)
		if(x>>i&1){
			if(a[i]){x^=a[i]; continue;}
			for(int j=i-1;~j;j--)if(x>>j&1)x^=a[j];
			for(int j=i+1;j<L;j++)if(a[j]>>i&1)a[j]^=x;
			return a[i]=x,size++,void();
		}
}

int n,m,cnt,hd[N],nxt[N<<2],to[N<<2];
ll val[N<<2],ans;
void add(int u,int v,ll w){
	nxt[++cnt]=hd[u],hd[u]=cnt;
	to[cnt]=v,val[cnt]=w;
}

bool vis[N]; ll cur[N];
int len,c[N];
void dfs(int id,ll w){
	vis[id]=1,cur[id]=w,c[++len]=id;
	for(int i=hd[id];i;i=nxt[i]){
		int it=to[i];
		if(vis[it])insert(w^val[i]^cur[it]);
		else dfs(it,w^val[i]);
	}
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(); ll t=read();
		add(u,v,t),add(v,u,t);
	} for(int i=1;i<=n;i++) if(!vis[i]){
		size=0,sx=0,cont=0,len=0,mem(a,0,L);
		dfs(i,0),cont=(1ll<<size)%mod;
		for(int i=0;i<L;i++)sx|=a[i];
		for(int i=0;i<L;i++){
			ll ze=0,on=0,pw=(1ll<<i)%mod,same,diff;
			for(int j=1;j<=len;j++)cur[c[j]]>>i&1?on++:ze++;
			same=(on*(on-1)/2+ze*(ze-1)/2)%mod,diff=(on*ze)%mod;
			if(sx>>i&1)ans=(ans+(same+diff)*pw%mod*cont%mod*iv2%mod)%mod;
			else ans=(ans+diff*pw%mod*cont%mod)%mod;
		}
	} cout<<ans<<endl;
	return 0;
}
```

---

## 作者：AFO_WR_Eternity (赞：4)

- 题目就不翻译了吧，应该写的很清楚了。。。

- 首先$,$ 不懂线性基的可以[戳这里](https://www.cnblogs.com/WR-Eternity/p/xian-xing-ji.html)。知道了线性基$,$ 但是从来没有写过线性基和图论相结合的$,$ 可以[戳这里](https://www.cnblogs.com/WR-Eternity/p/10273830.html)。
- 好$,$ 点完了这些前置技能之后，我们就可以来愉快的切题啦！

# 正片$:$

- 类比**$[WC$ $2011]$ 最大$xor$和路径**$,$ 我们肯定要找环$,$ 找完环后再用环去构造线性基$,$ 因为还是那句话嘛$:$ **任何一条复杂路径$,$ 都能有起始两点的一条简单路径再加上若干个环组成**。

- 那么接下来的问题就是$:$如何求出亦或值的和？

- $en$~~~，直接依据线性基，求出可以被这个线性基构造出的所有亦或值的和，然后相加，呃，是个好方法。

- 可惜$,$ 很不幸$,$ $xor$不满足分配律。然后我又冥思苦想了2天，终于找到了**“$n$个数中，任取几个数的亦或和的和”**这个问题的$O(n*63*63)$的做法，高兴了好一阵子，然后发现。。。哎$,$ 现在想想还是难受啊。

- 然后痛定思痛$,$ 改变视角——$woc$，原来这么简单$!$

- 不再考虑每一对数的$xor$和，我们改变目标 $,$去求：**对于每一对点的每一位，有多少种方案能使该位的$xor$和位1**。

- 对于我们原先就求出来的$d[1]$到$d[n]$ $($就是各个点到1号点的一条简单路径的$xor$和$)$ $,$ 我们要想求出$u$到$v$的一条简单路径$,$ 只需要用$d[u]$ $xor$ $d[v]$即可$,$ 因为重复走到路径会因为$xor$操作而抵消掉。

- 若线性基中有$cnt$个非零位，则一共会产生$2^{cnt}$个不同的$xor$值。

- 知道了这些以后$,$ 我们就可以开始讨论了$:$

- $1.$ $d[u]$ $xor$ $d[v]$第$k$位为1：这样的话，我们就需要不取第$k$个线性基$($因为只有第$k$位为1了才会对答案产生贡献嘛$!$ $)$ $,$ 这样的话，该项对于答案的贡献即为$:$ $2^{k}*2^{cnt-1}$。

 $2.$ $d[u]$ $xor$ $d[v]$第$k$位为0$:$ 显然，一定要取$k$个线性基$,$ 对答案的贡献即为$:$ $2^k*2^{cnt-1}$。
 
- 尽管这样$,$ 时间复杂度依然是$O(n^2*63)$的$,$ 吃不消$,$ 那么哪里还有优化的空间呢$?$

- 注意到$,$ $d[i]$第$k$位的值是固定的$,$ 那么我们就可以不单独讨论$"d[u]$ xor $d[v]"$对于答案的贡献$,$ 直接讨论$d[u]$对于答案的贡献。

- 先统计出第$k$位为$0$的数的个数$,$ 我们将其记为$x$ $,$ 再统计出第$k$位为$1$的数的个数$,$ 记为$y$ $,$ 总共有$point$个点。

- 分为$4$种情况讨论$:$

- **$1.$ $d[i]$的第$k$位为$1$ $,$ 线性基中有第$k$位为$1$的数**$:$ 此时我们有两种选择：$a.$ 选线性基中的$,$ 另一个点选择第$k$位为$0$的。 $b.$ 不选线性基中的$,$ 另一个点选择第$k$位为$1$的。总体对于答案的贡献为：$2^k*2^{cnt-1}*(point-1)$ $,$ 减$1$就是为了把自己给去掉。

 **$2.$ $d[i]$的第$k$位为$1$ $,$ 线性基中没有第$k$位为$1$的数**$:$ 这个时候另一个点只能取第$k$位为$0$的$,$ 所以总贡献为$:$ $2^k*2^{cnt}*x$。
 
 **$3.$ $d[i]$的第$k$位为$0$ $,$ 线性基中有第$k$位为$1$的数**$:$ 一样的$,$ 两种选择$:$ $a.$ 选线性基中的$,$ 另一个点选择第$k$位为$0$的。 $b.$ 不选线性基中的$,$ 另一个点选择第$k$位为$1$的。总贡献为$:$ $2^k*2^{cnt-1}*(point-1)$。
 
 **$3.$ $d[i]$的第$k$位为$0$ $,$ 线性基中没有第$k$位为$1$的数**$:$ 另一个点只能取第$k$位为$1$的$,$ 总贡献$:$ $2^k*2^{cnt}*y$。
 
- 最后别忘记给答案除个$2$就$OK$啦$!($要用逆元哦$)$

# 代码$:$
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=100005,M=400005,p=1e9+7,inv=500000004;
ll b[65],dist[M],d[N],a[N],two[65],s[N],z,ans,cnt,point;
int head[N],vet[M],nxt[M],c[65],n,m,x,y,tot;
bool vis[N],used[M];
void add(int x,int y,ll z){
    nxt[++tot]=head[x];
    vet[tot]=y;
    head[x]=tot;
    dist[tot]=z;
}
void insert(ll x){
    for (int i=62;i>=0;i--)
        if (x>>i)
            if (b[i]) x^=b[i];
            else {b[i]=x; break;}
}
void dfs(int u){
    a[++point]=d[u]; vis[u]=true;
    for (int i=head[u];i;i=nxt[i]){
        int v=vet[i];
        if (!vis[v]){
            d[v]=d[u]^dist[i];
            dfs(v);
        } else
            if (!used[i^1]){
                used[i^1]=true;
                insert(d[u]^d[v]^dist[i]);
            }
    }
}
ll calc(){
    ll ans=0;
    for (int j=0;j<=62;j++){
        ll x=0,y=0,flag=0;
        for (int i=1;i<=point;i++)
            if (a[i]>>j&1) x++; else y++;
        for (int i=0;i<=62;i++)
            if (b[i]>>j&1) flag=1;
        for (int i=1;i<=point;i++)
            if (a[i]>>j&1)
                if (flag)
                    (ans+=two[cnt-1]*(ll)(point-1)%p*two[j]%p)%=p;
                else
                    (ans+=two[cnt]*y%p*two[j]%p)%=p;
            else
                if (flag)
                    (ans+=two[cnt-1]*(ll)(point-1)%p*two[j]%p)%=p;
                else
                    (ans+=two[cnt]*x%p*two[j]%p)%=p;
    }
    return ans;
}
int main(){
    scanf("%d %d",&n,&m); tot=1;
    for (int i=1;i<=m;i++){
        scanf("%d %d %lld",&x,&y,&z);
        add(x,y,z); add(y,x,z);
    }
    two[0]=1;
    for (int i=1;i<=64;i++)
    	two[i]=two[i-1]*2%p;
    for (int i=1;i<=n;i++)
    	if (!vis[i]){
    		memset(b,0,sizeof(b));
            memset(c,0,sizeof(c));
    		point=0,cnt=0;
            dfs(i);
    		for (int j=0;j<=62;j++) cnt+=(b[j]>0);
    		(ans+=calc())%=p;
        }
        ans=ans*inv%p;
    	printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：zac2010 (赞：3)

不妨先看一道更为基础的题：[CF845G](https://www.luogu.com.cn/problem/CF845G)以及[它的题解](https://www.luogu.com.cn/blog/zac2010/solution-cf845g)。

回到这题。我们发现连通块的贡献独立，也就是说只要对每个连通块单独处理再求和就行了。

接下来我们关心单个连通块怎么做。由于题目让我们求的是所有 $s$ 之和而不是三元组个数，故而考虑拆贡献（对每一位分别考虑）。之后，就可以沿用 CF845G 那题利用线性基来维护路径的思路来计数了。

假设当前处理到第 $i$ 位、有 $n_0$ 个 $u$ 满足 $dis_u[i]=1$、有 $n_1$ 个 $u$ 满足 $dis_u[i]=0$（$dis_u[i]$ 表示 $dis_u$ 这个数二进制的第 $i$ 位是多少）。那么我们根据组合常识不难求出以下值：

* 边权异或和的第 $i$ 位为 $0$ 的路径数（记为 $p_0$）。

  根据 CF845G 那题中阐述的引理，对于一条路径 $u\to v$ 的边权异或和，它等价于 $dis_u\oplus dis_v$。

  于是它变成了找 $(dis_u\oplus dis_v)[i]=1$ 的点对数。

  即 $\frac{s(s-1)}{2}$，其中 $s$ 是当前连通块大小。

* 边权异或和的第 $i$ 位为 $1$ 的路径数（记为 $p_1$）。

  即 $n_0\times n_1$。

  当然也可以用容斥求得：$\frac{n(n-1)}{2}-(\dbinom {p_0} 2+\dbinom {p_1} 2)$。

接下来就可以直接统计答案了。分两种情况：

1. 假设当前线性基内存在一个数，满足它的第 $i$ 位为 $1$

   钦定线性基大小为 $sz$，那么对答案的贡献为 $p\times 2^{sz-1}\times 2^i$。

   其中 $2^{sz-1}$ 那一项采用了一个经典的组合套路：我们在线性基中任意地取出一个第 $i$ 位为 $1$ 的元素。对于其它元素任意选（有 $2^{sz-1}$ 种方案），而取出的元素将根据我们最终想得到的值来决定选不选。

2. 不存在这样一个元素

   显然只有那些 $(dis_u\oplus dis_v)[i]=1$ 的点对会在第 $i$ 位产生贡献。此外，线性基中的每个元素选和不选都是合法的。

   钦定线性基大小为 $sz$，那么贡献为 $p_1\times 2^{sz}\times 2^{i}$。
   
```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const ll mod = 1e9 + 7, inv2 = 500000004;
struct E{int v; ll w;}; vector<E> e[N];
int n, m, sz, vis[N]; vector<ll> s;
ll ans, dis[N], sum, a[65];
void insert(ll x){
	FR(i, 62, 0) if((x >> i) & 1){
		if(!a[i]){sum |= a[i] = x; sz++; return;}
		else x ^= a[i];
	}
}
ll query(ll ret = 0){
	FR(i, 62, 0){
		ll n[2] = {0}, p1, p;
		ll c = (1ll << i) % mod * ((1ll << sz) % mod) % mod;
		for(const ll &x: s) n[(x >> i) & 1]++;
		p1 = n[0] * n[1] % mod;
		p = s.size() * (s.size() - 1ll) / 2 % mod;
		if((sum >> i) & 1)
			(ret += p * c % mod * inv2) %= mod;
		else (ret += p1 * c) %= mod;
	}
	return ret;
}
void dfs(int u, int fa){
	vis[u] = 1, s.emplace_back(dis[u]);
	for(const auto &p: e[u]) if(p.v != fa){
		if(!vis[p.v]) dis[p.v] = dis[u] ^ p.w, dfs(p.v, u);
		else insert(dis[u] ^ dis[p.v] ^ p.w);
	}
}
int main(){
    scanf("%d%d", &n, &m);
    FL(i, 1, m){
        int u, v; ll w;
		scanf("%d%d%lld", &u, &v, &w);
        e[u].emplace_back((E){v, w});
		e[v].emplace_back((E){u, w});
    }
    FL(i, 1, n) if(!vis[i]){
    	vector<ll>().swap(s);
    	fill(a, a + 63, 0ll), sum = sz = 0;
    	dfs(i, 0), ans = query(ans);
	}
	printf("%lld\n", ans);
    return 0;
}
```


---

## 作者：daniEl_lElE (赞：1)

根据 [P4151](https://www.luogu.com.cn/problem/P4151) 的结论，我们很容易发现我们只需要在线性基中加入所有的环的权值。

考虑这题还要做些什么，本质上是求出两点路径权值在线性基上可以变成的所有权值。

对于线性基可以 $0/1$ 切换的位，贡献是一定的。于是只考虑线性基中 $0$ 的位。

此时我们要计算出有多少对 $(i,j)$ 这一位上的权值为 $1$，容易发现直接用到根的路径权值异或起来就可以得到两点直接的权值。这样就可以轻松计算了。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
vector<pair<int,int>> vc[1000005];
vector<pair<int,int>> tr[1000005];
int dep[1000005],vis[1000005],cnt[61][2],tag[61],siz=0,pts=0;
struct linearbasis{
	int f[61];
	void clear(){
		memset(f,0,sizeof(f));
	}
	void add(int x){
		for(int i=60;i>=0;i--){
			if((x>>i)&1){
				if(!f[i]) f[i]=x;
				x^=f[i];
			}
		}
	}
	void qtag(){
		for(int i=0;i<=60;i++){
			if(f[i]) siz++;
			for(int j=0;j<=60;j++){
				if((f[i]>>j)&1) tag[j]=1;
			}
		}
	}
}lb;
void dfs(int now){
	pts++;
	for(int i=0;i<=60;i++){
		cnt[i][(dep[now]>>i)&1]++;
	}
	vis[now]=1;
	for(auto v:vc[now]){
		if(vis[v.first]) lb.add(dep[now]^dep[v.first]^v.second);
		else dep[v.first]=dep[now]^v.second,tr[now].push_back(v),dfs(v.first);
	}
}
signed main(){
	int n,m,ans=0; cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w; cin>>u>>v>>w;
		vc[u].push_back(make_pair(v,w));
		vc[v].push_back(make_pair(u,w));
	}
	for(int pp=1;pp<=n;pp++){
		if(vis[pp]) continue;
		lb.clear();
		siz=pts=0;
		memset(cnt,0,sizeof(cnt));
		memset(tag,0,sizeof(tag));
		dfs(pp);
		lb.qtag();
		for(int i=0;i<=60;i++){
			if(tag[i]){
				(ans+=qp(2,siz-1)*((pts*(pts-1)/2)%mod)%mod*qp(2,i))%=mod;
			}
			else{
				(ans+=qp(2,siz)*cnt[i][0]%mod*cnt[i][1]%mod*qp(2,i))%=mod;
			}
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Fzrcy (赞：1)

因为题目没有保证原图连通，所以我们要对每个连通块计算贡献，这里以 与 $1$ 连通的连通块为例。

对于任意一个与 $1$ 连通的点 $x$ 预处理任意一条 $1\to x$ 的路径的异或和并存在 $dist_i$ 中，顺便将与 $1$ 连通的环的异或和加入线性基中。

那么点对 $(x,y)$ 的贡献为 $\sum_{s\in S}dist_i\operatorname{xor}dist_j\operatorname{xor} s$，其中 $s$ 是线性基的一个子集。直接暴力统计是 $O(n^2\log^2V)$ 的，考虑每个数位对答案的贡献。

设 $dist_x$ 的第 $i$ 位为 $1$ 的的 $x$ 的个数为 $c1$，第 $i$ 位为 $1$ 的个数为 $c2$，线性基中第 $i$ 位为 $1$ 的个数为 $t1$，第 $i$ 位为 $1$ 的个数为 $t2$。

若 $dist_x\operatorname{xor}dist_y$ 的第 $i$ 位为 $1$，则贡献次数为 $c1\times c2 \times 2^{t2}2^{t1-1}$。

若 $dist_x\operatorname{xor}dist_y$ 的第 $i$ 位为 $0$，则贡献次数为 $(\binom{c1}{2}+\binom{c2}{2}) \times 2^{t2}2^{t1-1}$。

对于 $t1=0$ 的情况，$dist_x\operatorname{xor}dist_y$ 的第 $i$ 位为 $0$ 的贡献次数为 $0$，$dist_x\operatorname{xor}dist_y$ 的第 $i$ 位为 $1$ 的贡献次数为 $c1\times c2 \times 2^{t2}$。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll mo=1e9+7;
const int N=1e6;

ll p[62];

void ins(ll x){
    if(!x) return;
    for(ll i=60; i>=0; i--)
    if(x>>i){
        if(!p[i]){p[i]=x; return;}
        else x^=p[i];
    }
}

int h[N], nt[N<<1], to[N<<1], cnt;
ll w[N<<1];

void link(int u, int v, ll W){
    nt[++cnt]=h[u], h[u]=cnt, to[cnt]=v, w[cnt]=W;
    nt[++cnt]=h[v], h[v]=cnt, to[cnt]=u, w[cnt]=W;
}

ll dist[N];
bool vis[N];
vector<ll> visit;

void dfs(int u, ll Now){
    visit.push_back(u);
    vis[u]=1, dist[u]=Now;
    for(int i=h[u]; i; i=nt[i])
        if(!vis[to[i]]) dfs(to[i], Now^w[i]);
        else ins(dist[to[i]]^Now^w[i]);
}

ll binom2(ll x){
    return 1ll*x*(x-1)/2ll%mo;
}

int n, m;

ll mul(ll x, ll y){return x*y%mo;}
ll add(ll x, ll y){return (x+y)%mo;}

ll calc(){
    ll ans=0;
    for(ll B=0; B<=60; B++){
        ll c1, c2, t1, t2, res;
        c1=c2=t1=t2=res=0;
        for(ll i:visit){
            if(((dist[i]>>B)&1))c1++;
            else c2++;
        }
        for(ll i=0; i<=60; i++)if(p[i]){
            if(((p[i]>>B)&1))t1++;
            else t2++;
        }
        if(t1==0){
            res=add(res, c1*c2%mo*((1ll<<t2)%mo)%mo);
        }
        else{
            res=add(res, add(binom2(c1), binom2(c2))*((1ll<<t1-1)%mo)%mo*((1ll<<t2)%mo)%mo);
            res=add(res, c1*c2%mo*((1ll<<t1-1)%mo)%mo*((1ll<<t2)%mo)%mo);
        }
        ans=add(ans, res*((1ll<<B)%mo)%mo);
    }
    return ans;
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i=1, x, y; i<=m; i++){
        static ll w;
        scanf("%d%d%lld", &x, &y, &w);
        link(x, y, w);
    }
    ll ans=0;
    for(int i=1; i<=n; i++)
    if(!vis[i]){
        memset(p, 0, sizeof p);
        visit.clear(), dfs(i, 0);
        ans=add(ans, calc());
    }
    printf("%lld\n", ans%mo);
    return 0;
}
```

---

## 作者：wcyQwQ (赞：1)

写复杂了/kk。

首先需要知道一个事情，就是两个点间所有路径的异或都可以表示为这两点的一条简单路径异或若干个环。

所以考虑将环的的异或和加到一个线性基里，记 $s_i$ 表示 $1 \rightarrow i$ 一条简单路径的异或和。根据上述结论，我们发现两个点 $i, j$ 之间的路径异或和可以表示为 $s_i \oplus s_j \oplus x$ 其中 $x$ 是线性基里的一个子集，这样我们枚举点可以做到 $O(n^2\log V)$。

枚举点是不优的，所以考虑计算每一个二进制位的贡献，记当前二进制为 $w$，$s$ 中第 $w$ 位为 $1$ 的有 $o$ 个，第 $w$ 位为 $0$ 的有 $z$ 个。线性基中第 $w$ 位为 $1$ 的有 $op$ 个，第 $w$ 位为 $0$ 的有 $zp$ 个。

假设 $s_i \oplus s_j$ 的第 $w$ 位为 $0$，那么这样的 $(i, j)$ 共有 $\binom{o}{2} + \binom{z}{2}$ 种，如果产生贡献，则 $op$ 中要选奇数个，这样有 $2^{op - 1}$ 种选法，所以这样一共就有 $2^{zp}2^{op - 1}(\binom{o}{2}+ \binom{z}{2})$ 种情况。

假设 $s_i \oplus s_j$ 的第 $w$ 为为 $1$，那么这样的 $(i, j)$ 共有 $oz$ 种，如果产生贡献，则 $op$ 中要选偶数个，也有 $2^{op - 1}$ 种选法，这样一共有 $2^{zp}2^{op - 1}oz$ 中情况。

注意当 $op = 0$ 时，第一种情况不存在，第二种情况的方法数为 $2^{zp}oz$。

这样直接对着式子写即可，时间复杂度 $O(n\log^2V)$。[Code](https://codeforces.com/contest/724/submission/207369365)

---

## 作者：eee_hoho (赞：1)

首先考虑如何计算答案，枚举每一条简单路径（可以写成$dis_u\oplus dis_v$，$dis$表示到$1$号点的异或和），然后和所有其他的环都能作为答案。

而这样子并不容易做，我们注意到线性基的一个性质。

假设该线性基的元素个数为$cnt$个，那么该线性基可以表示$2^{cnt}$个不同的数，而如果线性基的第$x$位为$1$，那么有$2^{cnt-1}$个数的第$x$为$1$。

这启发我们去对每一位分开考虑计算贡献。

如果线性基第$x$位为$1$，那么不管$u,v$怎么选都能使异或和第$x$位为$1$，那么贡献为$2^x2^{cnt-1}\begin{pmatrix}n\\2\end{pmatrix}$。

如果线性基第$x$位不为$1$，那么找到$dis_u$的第$x$位的个数$s$，那么需要选一个第$x$为$1$的端点和一个第$x$不为$1$的端点，而线性基上的$2^{cnt}$个数可以随便选，贡献为$2^x2^{cnt}s(n-s)$。

**Code**
``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N = 2e5;
const int P = 1e9 + 7;
using namespace std;
struct edges
{
    int to;
    long long cost;
}edge[N * 2 + 5];
int n,m,head[N + 5],nxt[N * 2 + 5],edge_cnt,vis[N + 5],cnt,ans,nn,sm[100];
long long dis[N + 5],p[100];
void add_edge(int u,int v,long long w)
{
    edge[++edge_cnt] = (edges){v,w};
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}
void ins(long long x)
{
    for (int i = 62;i >= 0;i--)
        if (x >> i & 1)
        {
            if (!p[i])
            {
                p[i] = x;
                cnt++;
                break;
            }
            x ^= p[i];
        }
}
void dfs(int u,long long cnt)
{
    vis[u] = 1;
    nn++;
    dis[u] = cnt;
    for (int i = 62;i >= 0;i--)
        if (dis[u] >> i & 1)
            sm[i]++;
    for (int i = head[u];i;i = nxt[i])
    {
        int v = edge[i].to;
        long long w = edge[i].cost;
        if (!vis[v])
            dfs(v,cnt ^ w);
        else
            ins(dis[u] ^ dis[v] ^ w);
    }
}
void calc(int st)
{
    memset(p,0,sizeof(p));
    memset(sm,0,sizeof(sm));
    cnt = 0;
    nn = 0;
    dfs(st,0);
    for (int i = 62;i >= 0;i--)
    {
        int fl = 0;
        for (int j = 62;j >= 0;j--)
            if (p[j] >> i & 1)
            {
                fl = 1;
                break;
            }
        if (fl)
            ans += 1ll * nn * (nn - 1) / 2 % P * ((1ll << i) % P) % P * ((1ll << cnt - 1) % P) % P,ans %= P;
        else
            ans += (1ll << cnt) % P * ((1ll << i) % P) % P * sm[i] % P * (nn - sm[i]) % P,ans %= P;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    int u,v;
    long long w;
    for (int i = 1;i <= m;i++)
    {
        scanf("%d%d%lld",&u,&v,&w);
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    for (int i = 1;i <= n;i++)
        if (!vis[i])
            calc(i);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：JPGOJCZX (赞：0)

节选自：[线性代数学习笔记（二）：线性基](https://www.luogu.com.cn/article/nhigvq6h)

[安利一下我的博客](https://www.luogu.com.cn/article/nhigvq6h)

我们先不考虑这道题是在图上操作，因此我们先来求不同异或和的和。

由于线性基中任意一组基异或起来都互不相同，这大大简化了这个问题，我们只需要统计即可，不需要考虑去重。

我们考虑按位算贡献。假设线性基中有 $tot$ 个基，其中有 $k (k > 0)$ 个基的第 $i$ 位为 $1$，那么就有 $tot - k$ 个第 $i$ 位为 $0$ 的基。这些第 $i$ 位为 $0$ 的基无论选不选都对答案不造成贡献，因此最终这一位的答案一定会乘以 $2^{tot - k}$。

现在我们考虑第 $i$ 位为 $1$ 的 $k$ 个基，只有当从中选出奇数个基时，才会在这一位上留下一个 $1$，因此答案是 $\displaystyle\sum_{0 \leq j \leq k \wedge j \bmod 2 = 1} \binom kj$。

我们考虑二项式定理 $(x + y)^k = \displaystyle\sum_{0 \leq j \leq k} \binom kj x^j y^{k - j}$，由于 $k > 0$，我们把 $x, y$ 带成 $-1$ 和 $1$，那么 $0 = \displaystyle\sum_{0 \leq j \leq k} \binom kj (-1)^j$，这个式子在 $j$ 为偶数时为正，$j$ 为奇数时为负，于是 $\displaystyle\sum_{0 \leq j \leq k \wedge j \bmod 2 = 1} \binom kj = \sum_{0 \leq j \leq k \wedge j \bmod 2 = 0} \binom kj$。

因为组合数一行之和 $\displaystyle 2^k$，那么 $\displaystyle\sum_{0 \leq j \leq k \wedge j \bmod 2 = 1} \binom kj = 2^{k - 1}$，于是这一位的答案就是 $2^{tot - 1}$。

很显然，如果 $k$ 为 $0$ 那么答案就是 $0$，因此如果存在一个最高位为 $i$ 的基，那么答案就会乘以 $2^{tot - 1}$，那么答案就是 $\displaystyle\prod_{i = 0}^{\log n} 2^{tot - 1} [w_i \neq 0]$。

回到这道题目，我们需要求不同的路径异或和的和。参考例题十一，我们把所有环插入线性基中，再找到一条主路径，那么最终答案就是线性基中的答案异或上主路径长度，但 $u$ 和 $v$ 都是不固定的，如果一对一对枚举，复杂度直接炸了，考虑如何优化。

还是考虑异或相等为 $0$ 的情况。如果我们随便找一个点作为起点，记录到 $u$ 的距离 $dis_u$ 和到 $v$ 的距离 $dis_v$，那么 $u$ 到 $v$ 的距离就是 $dis_u \operatorname{xor} dis_v$。

那么现在问题就变成了在集合 $\{dis_i\}$，中任意选两个数字 $dis_u, dis_v$，我们求出线性基中异或和的和，再异或上 $dis_u$ 和 $dis_v$，加入到答案中就行了。但这样复杂度依然爆炸。

我们继续考虑按位贡献，我们知道线性基如果有一个数第 $i$ 位上是 $1$，那么这一位上就有 $2^{tot - 1}$ 种方式凑出 $1$，$2^{tot - 1}$ 种方式凑出 $0$。因此无论 $\{dis_i\}$ 中选出两个数的异或和的第 $i$ 位为 $1$ 或者 $0$，对答案的贡献都是 $2^{tot - 1}$。假设 $\{dis_i\}$ 的大小为 $siz$，那么总贡献就是 $2^{tot - 1} \times \displaystyle\frac{siz(siz - 1)}{2}$。

如果线性基中没有数字第 $i$ 位上是 $1$，那么无论多少个数异或起来都是 $0$，因此答案需要乘以 $2^{tot}$。其次选出的 $dis_u$ 和 $dis_v$ 的第 $i$ 位上必须一个是 $0$，一个是 $1$。我们假设 $\{dis_i\}$ 中有 $cnt$ 个数字第 $i$ 位上为 $1$，那么对于答案的贡献就是 $2^{tot} \times cnt \times (siz - cnt)$。

最后，这道题的图可能不联通，每个连通块分开算即可。

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 9, M = 2e5 + 9, MOD = 1e9 + 7;
struct Edge{
	int v, w, nex;
} e[M << 1];
int head[N], ecnt;
void addEdge(int u, int v, int w){
	e[++ecnt] = Edge{v, w, head[u]};
	head[u] = ecnt;
}
int qpow(int a, int b){
	int res = 1;
	while(b > 0){
		if(b & 1)
			res = res * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}
int dis[N], n, m, ans, sum;
vector <int> vec;
bool vis[N];
struct Basis{
	int w[69], tot;
	void clear(){
		memset(w, 0, sizeof(w));
		tot = 0;
	}
	void insert(int x){
		for(int i = 62; ~i; i--){
			if(x >> i & 1ll){
				if(w[i])
					x ^= w[i];
				else {
					w[i] = x;
					tot++;
					break;
				}
			}
		}
	}
	int calc(){
		int sum = 0, res = 0, siz = vec.size();
		for(int i = 62; ~i; i--)
			sum |= w[i];
		for(int i = 62; ~i; i--){
			int cnt = 0;
			for(int j = 0; j < siz; j++)
				if(vec[j] >> i & 1ll)
					cnt++;
			if(sum >> i & 1ll)
				res = (res + qpow(2, i) % MOD * qpow(2, tot - 1) % MOD * (siz * (siz - 1) / 2 % MOD) % MOD) % MOD;
			else
				res = (res + qpow(2, i) % MOD * qpow(2, tot) % MOD * cnt % MOD * (siz - cnt) % MOD) % MOD;
		}
		return res;
	}
} b;
void dfs(int u){
	vis[u] = true;
	vec.push_back(dis[u]);
	for(int i = head[u]; i; i = e[i].nex){
		int v = e[i].v;
		if(vis[v])
			b.insert(dis[u] ^ dis[v] ^ e[i].w);
		else {
			dis[v] = dis[u] ^ e[i].w;
			dfs(v);
		}
	}
}
signed main(){
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= m; i++){
		int u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	for(int i = 1; i <= n; i++){
		if(!vis[i]){
			b.clear();
			vec.clear();
			dfs(i);
			ans = (ans + b.calc()) % MOD;
		}
	}
	printf("%lld", ans);
	return 0;    
}
```

---

## 作者：w9095 (赞：0)

[CF724G Xor-matic Number of the Graph](https://www.luogu.com.cn/problem/CF724G)

直接维护异或和之和，显然不可能。由于二进制位相互独立，我们考虑维护每一个二进制位的出现次数，再乘以位权加入结果。

对于路径的维护，我们参考[P4151 [WC2011] 最大XOR和路径](https://www.luogu.com.cn/problem/P4151)，分成主路径和若干个环。记路径 $1\to n$ 的边的异或和为 $dis[i]$，任意两点 $x,y$ 之间的路径的边的异或和可以由 $dis[x]\oplus dis[y]$ 得到。如果 $1\to x$ 和 $1\to y$ 在点 $z$ 前有重复部分，异或后重复部分消去，留下 $x\to z\to y$。否则，如果没有重复部分，则异或后变为 $x\to 1\to y$。结论成立。

如果有环的二进制第 $i$ 位为 $1$，那么我们肯定可以使第 $i$ 位为 $1$。如果目前答案第 $i$ 位为 $0$，直接异或，否则不异或。因此，任意一条 $x\to y$ 的简单路径都第 $i$ 位都可以为 $1$，有 $C_{n}^2$ 中选法。除了第 $i$ 位，其他位可以任意选择。方案数为 $2^{x-1}$，其中 $x$ 为线性基大小，即 $bas[i]\ne0$ 的数的数量。运用乘法原理，再乘上权值，这一位的贡献为：

$$C_{n}^2\times2^{x-1}\times2^i$$

如果没有环的二进制第 $i$ 位为 $1$，那么走环对于这一位没有影响。此时线性基可以随便选，方案数为 $2^x$，其中 $x$ 为线性基大小。我们只需要统计有多少条简单路径的异或和的第 $i$ 位为 $1$ 即可。

结合路径的计算式，$dis[x]\oplus dis[y]$，我们继续进行拆位。对每一个 $dis$，如果第 $i$ 位为 $1$，则将 $w_{i,1}$ 加 $1$；如果第 $i$ 位为 $0$，则将 $w_{i,0}$ 加 $1$。$w_{i,1}$ 表示第 $i$ 位为 $1$ 的 $dis$ 的个数，$w_{i,0}$ 表示第 $i$ 位为 $0$ 的 $dis$ 的个数。如果要让一条路径的权值 $dis[x]\oplus dis[y]$ 第 $i$ 位为 $1$，则必须在 $w_{i,1}$ 中和 $w_{i,0}$ 中各选一个。根据乘法原理，方案数为 $w_{i,0}\times w_{i,1}$。运用乘法原理，再乘上权值，这一位的贡献为：

$$w_{i,0}\times w_{i,1}\times2^{x}\times2^i$$

代码中这一部分实现方式略微不同，其中 $ct[i]$ 表示 $w_{i,1}$，$pos-ct[i]$ 表示 $w_{i,0}$。

注意图不一定联通，对于每个联通块分别计算即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct edge
{
	long long v,nxt,d;
}e[800000];
long long n,m,u,v,d,h[800000],bas[100],book[800000],dis[800000],ct[100],p[800000],cnt=1,ans=0,siz=0,pos=0;
const long long mod=1e9+7;
void add_edge(long long u,long long v,long long d)
{
	e[++cnt].nxt=h[u];
	e[cnt].v=v;
	e[cnt].d=d;
	h[u]=cnt;
}

void insert(long long x)
{
	for(int i=63;i>=0;i--)
	    if((x>>i)&1)
	       {
	       	if(bas[i]!=0)x^=bas[i];
	       	else
			   { 
			   siz++,bas[i]=x;
			   break;
		       }
		   }
}

void dfs(long long now,long long pre,long long dn)
{
	book[now]=1,dis[now]=dn,pos++;
    for(int i=63;i>=0;i--)
		if((dn>>i)&1)ct[i]++;
	for(int i=h[now];i;i=e[i].nxt)
	    if(i!=(pre^1))
	       {
	       	if(book[e[i].v])insert(dis[now]^dis[e[i].v]^e[i].d);
			else dfs(e[i].v,i,dn^e[i].d);    
		   }
}

int main()
{
	scanf("%lld%lld",&n,&m);
    p[0]=1;
    for(int i=1;i<=63;i++)p[i]=p[i-1]*2%mod;
	for(int i=1;i<=m;i++)
	    {
	    	scanf("%lld%lld%lld",&u,&v,&d);
	    	add_edge(u,v,d),add_edge(v,u,d);
		}
    for(int i=1;i<=n;i++)
        if(!book[i])
            {
            memset(bas,0,sizeof(bas)),memset(ct,0,sizeof(ct));
            pos=siz=0;
            dfs(i,0,0);
            long long flag=0;
            for(int j=63;j>=0;j--)flag|=bas[j];
            for(int j=63;j>=0;j--)
                if((flag>>j)&1)ans=(ans+pos*(pos-1)%mod*500000004%mod*p[siz-1]%mod*p[j]%mod)%mod;
                else ans=(ans+ct[j]*(pos-ct[j])%mod*p[siz]%mod*p[j]%mod)%mod;
            }
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Zhddd_ (赞：0)

首先，可以考虑在每个连通块内 DFS，遇到简单环就建线性基。

接下来，可以考虑这样统计答案：根据编号从大到小依次遍历所有点，对于一个点，按位统计比它编号大的点的贡献。

具体地说，设当前按编号 **从大到小** 遍历到了点 $i$，连通块内一共有 $tot$ 个点，按位统计到了第 $j$ 位，比 $i$ 编号大的点中，第 $j$ 位为 $1$ 的有 $n$ 个，为 $0$ 的有 $m$ 个。线性基中，第 $j$ 位为 $1$ 的有 $p$ 个，为 $0$ 的有 $q$ 个。DFS 时，起始点到点 $i$ 的异或路径长度为 $dis_i$。 

要统计答案，就相当于统计这一位出现 $1$ 的方案数，再乘上 $2^j$。

那么可分两类讨论：

1. 若 $p\ge 1$，且 $dis_i$ 的第 $j$ 位是 $1$，那么方案数就是这两个式子的和：

$$n\times\left(\dbinom{q}{0}+\dbinom{q}{1}+\dbinom{q}{2}+\cdots\right)\times\left(\dbinom{p}{1}+\dbinom{p}{3}+\dbinom{p}{5}+\cdots\right)$$

$$m\times\left(\dbinom{q}{0}+\dbinom{q}{1}+\dbinom{q}{2}+\cdots\right)\times\left(\dbinom{p}{0}+\dbinom{p}{2}+\dbinom{p}{4}+\cdots\right)$$

第一个式子表示：若与考虑 $i$ 与那 $n$ 个点，那么线性基中，应该在 $p$ 中选奇数个，$q$ 中选任意个，使得这一位为 $1$；第二个式子同理。

化简即为 $(n+m)\times2^q\times2^{p-1}=tot\times2^q\times2^{p-1}$，而 $dis_i$ 的第 $j$ 位是 $0$ 的情况同理，答案也是这个。

2. 若 $p=0$，那么上面的 $2^{p-1}$ 就不适用了，可以根据类似的定义再写一个：

若 $dis_i$ 的第 $j$ 位是 $1$，那么方案数为 $m\times 2^q$，否则为 $n\times2^q$。

综上所述，我们可以统计出 $n,m,p,q$ 的值，然后直接套公式就好了，由于有线性基，时间复杂度：$O(n\log n)$。

注意多取模。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ULL = unsigned long long;
const int N = 1e5 + 10, M = 4e5 + 10;
const ULL MOD = 1e9 + 7;
int n, m;
int h[N], e[M], ne[M], idx, disbit[65], pbit[65], cnt, tot, id[N];
ULL w[M], dis[N], p[65], res;
bool st[N];
void add(int a, int b, ULL c) {
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
void Insert(ULL x) {
	if (!x) return;
	for (int i = 60; ~i; i--) {
		if (!((x >> i) & 1)) continue;
		if (!p[i]) {
			p[i] = x;
			break;
		}
		x ^= p[i];
	}
}
void dfs(int u) {
	st[u] = true, id[++tot] = u;
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (st[v]) {
			Insert(dis[v] ^ w[i] ^ dis[u]);
			continue;
		}
		dis[v] = dis[u] ^ w[i];
		dfs(v);
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	memset(h, -1, sizeof h);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int a, b;
		ULL c;
		cin >> a >> b >> c;
		add(a, b, c), add(b, a, c);
	}
	for (int kkk = 1; kkk <= n; kkk++) {
		if (st[kkk]) continue;
		cnt = tot = 0;
		memset(p, 0, sizeof p);
		memset(pbit, 0, sizeof pbit);
		memset(disbit, 0, sizeof disbit);
		dfs(kkk);
		for (int i = 0; i <= 60; i++) {
			if (p[i]) {
				for (int j = 0; j <= 60; j++) {
					pbit[j] += ((p[i] >> j) & 1);
				}
				cnt++;
			}
		}
		sort(id + 1, id + tot + 1);
		for (int i = tot; i; i--) {
			ULL t = dis[id[i]];
			for (int j = 0; j <= 60; j++) {
				int p = pbit[j], q = cnt - pbit[j];
				if (p) res = (res + (ULL(1) << j) % MOD * (tot - i) % MOD * ((ULL(1) << q) % MOD) % MOD * ((ULL(1) << (p - 1)) % MOD)) % MOD;
				else if ((t >> j) & 1) {
					res = (res + (ULL(1) << j) % MOD * (tot - i - disbit[j]) % MOD * ((ULL(1) << q) % MOD)) % MOD;
				} else {
					res = (res + (ULL(1) << j) % MOD * (disbit[j]) % MOD * ((ULL(1) << q) % MOD)) % MOD;
				}
			}
			for (int j = 0; j <= 60; j++) {
				disbit[j] += ((t >> j) & 1);
			}
		}
	}
	cout << res << endl;
	return 0;
}
```

---

## 作者：tzc_wk (赞：0)

[Codeforces 题目传送门](https://codeforces.com/contest/724/problem/G) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF724G)

一道还算不套路的线性基罢……

首先由于图不连通，并且不同连通块之间的点显然不可能产生贡献，因此考虑对每个连通块单独计算贡献。按照 P4151 的套路可以对每个连通块先找出它的一棵生成树，记 $d_u$ 为 $u$ 到生成树树根上所有边权值的异或和。对于生成树上所有非树边 $(u,v,w)$，$u\to v$ 在树上的路径与这条边本身显然会形成一个环，且环的权值为 $d_u\oplus d_v\oplus w$，我们将这个环插入线性基。那么对于该联通块中的两点 $u,v$，所有 $u\to v$ 路径本质不同的异或和都可以写成 $d_u\oplus d_v\oplus x$ 的形式，其中 $x$ 可以表示为线性基中向量的线性组合。

显然暴力枚举 $u,v$ 是不可行的，考虑换个方式计算贡献，对于每一个二进制位 $2^p$，我们计算有多少个 $u,v,S$ 满足 $d_u\oplus d_v\oplus\operatorname{xor}\limits_{x\in S}x$ 的 $2^p$ 位为 $1$，那么会产生 $2^p\times\text{满足条件的三元组}(u,v,S)\text{的个数}$ 的贡献。那么这个贡献怎么计算呢？分两种情况，设线性基为 $b_1,b_2,\cdots,b_m$，那么：

- 如果 $\exist i$ 满足 $b_i$ 的 $2^p$ 位为 $1$，那么不论剩下 $m-1$ 个数选不选，我们总可以控制 $b_i$ 的选/不选来实现 $2^p$ 的第 $i$ 位为 $1$，因此可以表示为 $\operatorname{xor}\limits_{x\in S}x$ 的形式，并且 $2^p$ 位为 $1$ 的数的个数为 $2^{p-1}$。而根据线性基的性质，对于所有可以表示 $\operatorname{xor}\limits_{x\in S}x$ 的形式的 $y$，都恰好存在 $2^{t-m}$ 个集合 $S$ 满足 $\operatorname{xor}\limits_{x\in S}x=y$，其中 $t$ 为非树边个数。也就是说不论 $u,v$ 是什么，总有 $2^{t-1}$ 个集合 $S$ 满足 $d_u\oplus d_v\oplus\operatorname{xor}\limits_{x\in S}x$ 的 $2^p$ 位为 $1$，因此符合条件的 $u,v,S$ 的个数为 $2^{t-1}\times\dbinom{n}{2}$。
- 否则不论 $S$ 是什么，都有 $\operatorname{xor}\limits_{x\in S}x$ 的 $2^p$ 位为 $0$，故 $(u,v,S)$ 符合条件当且仅当 $d_u,d_v$ 的 $2^p$ 位的值不同，开个桶统计下有多少个 $u$ 满足 $d_u$ 的 $2^p$ 位为 $0$，贡献即为 $2^t\times d_p\times(siz-d_p)$，其中 $siz$ 为连通块大小。

剩下的就是乱搞搞的事了，时间复杂度 $n\log^2v$，其中 $v$ 为值域大小。

```cpp
const int MAXN=1e5;
const int MAXM=2e5;
const int MAXB=60;
const int MOD=1e9+7;
const int INV2=5e8+4;
int n,m,cnt=0,num[MAXB+5];ll a[MAXB+5];
int hd[MAXN+5],to[MAXM*2+5],nxt[MAXM*2+5],ec=0;ll val[MAXM*2+5];
void adde(int u,int v,ll w){to[++ec]=v;val[ec]=w;nxt[ec]=hd[u];hd[u]=ec;}
void init(){memset(a,0,sizeof(a));cnt=0;}
void ins(ll x){
	for(int i=MAXB;~i;i--) if(x>>i&1){
		if(!a[i]){++cnt;a[i]=x;return;}
		else x^=a[i];
	}
}
bitset<MAXN+5> vis;
ll dis[MAXN+5];vector<int> v;
void dfs(int x,ll cur){
	dis[x]=cur;vis[x]=1;v.pb(x);
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];ll z=val[e];
		if(!vis[y]) dfs(y,cur^z);
		else ins(dis[x]^dis[y]^z);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;ll w;scanf("%d%d%lld",&u,&v,&w);
		adde(u,v,w);adde(v,u,w);
	}
	int ans=0;
	for(int i=1;i<=n;i++) if(!vis[i]){
		init();memset(num,0,sizeof(num));v.clear();dfs(i,0);
		for(int j=0;j<=MAXB;j++) for(int u:v)
			if(dis[u]>>j&1) num[j]++;
		for(int j=0;j<=MAXB;j++){
			bool flg=0;
			for(int k=0;k<=MAXB;k++) if(a[k]>>j&1) flg=1;
			if(flg) ans=(ans+(1ll<<j)%MOD*((1ll<<cnt-1)%MOD)%MOD*v.size()%MOD*(v.size()-1)%MOD*INV2)%MOD;
			else ans=(ans+(1ll<<j)%MOD*((1ll<<cnt)%MOD)%MOD*num[j]%MOD*(v.size()-num[j]))%MOD;
		}
	} printf("%d\n",ans);
	return 0;
}
```



---

## 作者：bztMinamoto (赞：0)

更好的阅读体验->[这里](https://www.cnblogs.com/bztMinamoto/p/9720166.html)

线性基神仙题

首先异或和肯定得用线性基

然后路径肯定得找出所有环

那么先dfs一遍，找出到每个点的任意一条路径，然后把所有的环都给扔进线性基里面，

考虑接下来怎么做

经过深(kan)思(le)熟(ti)虑(jie)，我们发现每一个连通块里的所有点都要两两统计答案，那么我们要根据xor采取一个方法：二进制逐位统计

假设从大到小考虑第$k$位，此时所有点可以分为两类，第$k$位为0或第$k$位为1

先考虑两个点全0或全1的情况，这种情况下两个点异或起来第$k$位为0，对答案没有贡献，那么只有在线性基里存在第$k$位为1的数，异或上这两个点才能使其对答案有贡献

那么这个基必须选，然后剩下的基有$2^{cnt-1}$种选法（$cnt$为线性基里的元素个数），这一位对答案的贡献就是$2^{cnt-1}*2^{k}$

然后不同为0或1的情况同理，这个基必须不能选，剩下的基的选法如上

ps：我上面两个基必须选或不选只是打个比方，真正的意思是把这一个基拿出来，那么如果剩下的异或出来第$k$位是否为0，都能通过异或上这一个数使其第$k$位变为1（如果已经是1就不用异或了），所以剩下的数怎么组合都没有关系，方案数肯定是那么多

然后剩下的……看代码好了
```
//minamoto
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline ll read(){
    #define num ch-'0'
    char ch;bool flag=0;ll res;
    while((ch=getc())>'9'||ch<'0')
    (ch=='-')&&(flag=true);
    for(res=num;(ch=getc())<='9'&&ch>='0';res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
const int N=4e5+5,mod=1e9+7;
ll ans;
int n,m,top,cnt,cir,u,v;ll e;
int head[N],q[N],ver[N<<2],Next[N<<2],tot;ll edge[N<<2];
ll b[105],bin[105],circle[N],dis[N],dig[2];
inline void add(int u,int v,ll e){
	ver[++tot]=v,Next[tot]=head[u],head[u]=tot,edge[tot]=e;
}
void dfs(int u,int fa,ll d){
	dis[u]=d,q[++top]=u;
	for(int i=head[u];i;i=Next[i]){
		int v=ver[i];
		if(v!=fa){
			if(dis[v]==-1) dfs(v,u,dis[u]^edge[i]);
			else circle[++cir]=dis[u]^dis[v]^edge[i]; 
		}
	}
}
inline void insert(ll x){
	for(int i=63;i>=0;--i)
	if(x>>i&1){
		if(!b[i]) return (void)(b[i]=x,++cnt);
		x^=b[i];
	}
}
void init(){
	memset(b,0,sizeof(b)),cnt=0;
	for(int i=1;i<=cir;++i) insert(circle[i]);
}
void calc(){
	init();
	for(int j=0;j<=63;++j){
		bool flag=0;dig[0]=dig[1]=0;
		for(int i=1;i<=top;++i) dig[dis[q[i]]>>j&1]++;
		for(int i=0;i<=63;++i)
		if(b[i]>>j&1){flag=1;break;}
		ll res;
		if(flag){
			res=(dig[0]*(dig[0]-1)/2+dig[1]*(dig[1]-1)/2)%mod;
			if(cnt) (res*=bin[cnt-1])%=mod;
			(res*=bin[j])%=mod;
			(ans+=res)%=mod;
		}
		res=dig[0]*dig[1]%mod;
		if(flag){if(cnt) (res*=bin[cnt-1])%=mod;}
		else (res*=bin[cnt])%=mod;
		(res*=bin[j])%=mod;
		(ans+=res)%=mod;
	}
}
int main(){
//	freopen("testdata.in","r",stdin);
	memset(dis,-1,sizeof(dis));
	bin[0]=1;for(int i=1;i<=63;++i) bin[i]=(bin[i-1]<<1)%mod;
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		u=read(),v=read(),e=read();
		add(u,v,e),add(v,u,e);
	}
	for(int i=1;i<=n;++i)
	if(dis[i]==-1)
	top=cir=0,dfs(i,0,0),calc();
	printf("%lld\n",ans);
	return 0;
}
```

---

