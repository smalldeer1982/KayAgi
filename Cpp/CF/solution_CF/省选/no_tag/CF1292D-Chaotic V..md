# Chaotic V.

## 题目描述

设$x$是大于$1$的正整数，定义$f(x)$为$x$的最小质因子的值。

现在考虑构造一棵树$T$。其中节点均用从$1$开始的正整数编号，对于任意大于$1$的正整数$x$，节点$x$在树上的父亲是$\frac{x}{f(x)}$。

在这棵树上有$n$个关键节点，很特别地，这$n$个节点的编号均可以表示成一个非负整数的阶乘。更具体地，第$i$个节点$P_i$的编号为$k_i!=\prod_{j=1}^{k_i}j$。

定义$\text{DIS}(i,j)$表示树上$i,j$两点间最短路所包含的边数。现在你找出树上的一个节点$P$，最小化$\sum_{i=1}^n\text{DIS}(P,P_i)$的值。你只需要输出这个最小值即可。

## 样例 #1

### 输入

```
3
2 1 4```

### 输出

```
5```

## 样例 #2

### 输入

```
4
3 1 4 4```

### 输出

```
6```

## 样例 #3

### 输入

```
4
3 1 4 1```

### 输出

```
6```

## 样例 #4

### 输入

```
5
3 1 4 1 5```

### 输出

```
11```

# 题解

## 作者：Querainy (赞：6)

来一发虚树题解。

昨天上午开了一场VP，然后机房神仙秒了这个D。我一看这不是虚树题吗?但是我不会写虚树，所以学了一下午，今天来写个题解。

这是一道很好的虚树练手题，至少它让我对虚树有了更深刻的认识。

在进入正题——建虚树之前，我相信大家都能看出来，不同的点数其实不超过5000，所以我们可以打表预处理每个阶乘的唯一分解形式。

然后，如果我们建出了虚树，就把原问题转化成了一个点边均带权的重心问题。接下来还要考虑这个带权重心可能在虚树的点上，虚树的边上，甚至虚树的外面——而后两种是不好处理的。

显然，在虚树的外面肯定不优，接下来我们用调整法证明在虚树的边上不会比在这条边的某个端点上更优。如果这条边两边所有点的权重之和相同，那么我们随便取一个端点，得到的带权路径长度和是一样的；如果两边权重和不同，我们取权重较小一边的端点，一定比这个边上的点更优。实际上，如果一棵虚树的一条边代表原树的一条链，而这条链上全是0权点，那么在这条链之外一定还存在带权重心。

考虑如果要建虚树，我们需要搞定以下几个操作 : 

### 1.给点排序

发现其实不用给点排序。如果我们按除去的那个质因子从小到大的顺序遍历儿子的话，我们发现走上来是砍去最小质因子的过程，而走下去则是乘上最大质因子的过程。所以，既然阶乘的各质因子次数都是单调递增的，dfs序也是单调递增的。

### 2.求LCA

考虑一个点走到它的各级祖先时砍质因子的过程。发现如果$u$是$v$的祖先，那么$u$前面有若干0，然后接下来一个质因子的次数比$v$小，剩下的质因子次数都和$v$相同。

所以我们要求$l=\operatorname{LCA}(u,v)$，就先求出$u,v$的最长公共后缀，然后接下来一位取$u,v$这一位上的$\min$，剩下的位取$0$。举个例子，比如我们要求$\operatorname{LCA}(15,20)$(可以看看样例的图，括号里表示唯一分解形式) : 

$$
\begin{aligned}
15&=(0,1,1,0,...)\\
20&=(2,0,1,0,...)\\
\operatorname{LCA}(15,20)=5&=(0,0,1,0,...)\\
\end{aligned}
$$

### 3.判断相等

废话。

### 4.判断祖先关系

其实在第二部分已经讨论过了。我们要判断$u$是不是$v$的后代，只要看$v$第一个非$0$位是不是小于$u$对应位的值，然后后面的位是不是相等。

解决了这几个问题，我们就可以成功地建立虚树。接下来的任务是求出带权重心，我们可以使用换根dp来搞定。

复杂度，预处理是$O(k\log\log k)$，建立虚树是$O(\frac{k^2}{\log k})$，dp是$O(k)$，所以总复杂度$O(\frac{k^2}{\log k})$，速度还可以。

我码力不太行，写了160行才写完。注意一下$k$可能为0，需要特判$0!=1$。

```cpp
#include<stdio.h>
#include<string.h>

int n;
int b[5002],prime[700],pcnt;
int temp[5002],val[20002];
int cnt;
long long ans=0x7fffffffffffffff;

struct Num
{
	int e[700];
	Num(){ memset(e,0,sizeof(e)); }
	inline bool operator == (Num x)
	{
		for(int i=1;i<=pcnt;i++)
			if(e[i]!=x.e[i]) return 0;
		return 1;
	}
	inline bool operator < (Num x)
	{
		for(int i=1;i<=pcnt;i++)
			if(e[i]!=x.e[i])
				if(e[i]<x.e[i]) return 1;
				else return 0;
		return 0;
	}
}a[20000];

inline void init()
{
	for(int i=2;i<=5000;i++)
		if(!b[i])
		{
			prime[++pcnt]=i;
			for(int j=2*i;j<=5000;j+=i)
				b[j]=1;
		}
	
	for(int i=1;i<=5000;i++) temp[i]=i;
	for(int i=1;i<=pcnt;i++)
		for(int j=1;j<=5000;j++)
			while(temp[j]%prime[i]==0)
				temp[j]/=prime[i],a[j].e[i]++;
	for(int i=1;i<=5000;i++)
		for(int j=1;j<=pcnt;j++)
			a[i].e[j]+=a[i-1].e[j];
	cnt=5000;
}

struct Edge
{
	int v,w,next;
}e[100002];

int h[50002];
int ecnt;

inline void add_edge(int u,int v,int w)
{
	e[++ecnt]={v,w,h[u]};
	h[u]=ecnt;
	e[++ecnt]={u,w,h[v]};
	h[v]=ecnt;
}

#define min(x,y) ((x)<(y)?(x):(y))

inline Num lca(Num a,Num b)
{
	Num c;
	int i=pcnt;
	for(;a.e[i]==b.e[i];i--) c.e[i]=a.e[i];
	c.e[i]=min(a.e[i],b.e[i]);
	i--;
	for(;i>0;i--) c.e[i]=0;
	return c;
}

inline int dist(Num u,Num v)//jump from u to v
{
	int res=0;
	for(int i=1;i<=pcnt;i++)
		res+=u.e[i]-v.e[i];
	return res;
}

inline bool is_son(Num u,Num v)//check if u is v's son
{
	int i=1;
	for(;i<=pcnt&&!v.e[i];i++);
	if(i>pcnt) return 1;
	if(v.e[i]>u.e[i]) return 0;
	i++;
	for(;i<=pcnt;i++)
		if(v.e[i]!=u.e[i]) return 0;
	return 1;
}

int s[20002],top;

inline void insert(int u)
{
	a[++cnt]=lca(a[s[top]],a[u]);
	if(!(a[cnt]==a[s[top]]))
	{
		while(is_son(a[s[top-1]],a[cnt])&&!(a[s[top-1]]==a[cnt]))
			add_edge(s[top],s[top-1],dist(a[s[top]],a[s[top-1]])),top--;
		if(!(a[cnt]==a[s[top-1]]))
			add_edge(s[top],cnt,dist(a[s[top]],a[cnt])),s[top]=cnt;
		else
			add_edge(s[top],s[top-1],dist(a[s[top]],a[s[top-1]])),top--;
	}
	s[++top]=u;
}

inline void build()
{
	s[++top]=1;
	for(int i=2;i<=5000;i++)
		if(val[i])
			insert(i);
	for(int i=1;i<top;i++)
		add_edge(s[i],s[i+1],dist(a[s[i+1]],a[s[i]]));
}

bool vis[20002];
int sum[20002];
long long dp[20002],f[20002];

void dfs1(int u,int fa)
{
	vis[u]=1;
	sum[u]=val[u];
	f[u]=0;
	for(int i=h[u];i;i=e[i].next)
		if(e[i].v!=fa)
			dfs1(e[i].v,u),sum[u]+=sum[e[i].v],f[u]+=(long long)e[i].w*sum[e[i].v]+f[e[i].v];
}

void dfs2(int u,int fa)
{
	for(int i=h[u];i;i=e[i].next)
		if(e[i].v!=fa)
			dp[e[i].v]=(dp[u]-(f[e[i].v]+(long long)e[i].w*sum[e[i].v])+(long long)e[i].w*(sum[1]-sum[e[i].v])+f[e[i].v]),
			dfs2(e[i].v,u);
}

int main()
{
	scanf("%d",&n);
	for(int i=1,k;i<=n;i++)
		scanf("%d",&k),k==0?val[1]++:val[k]++;
	init();
	build();
	dfs1(1,0);
	dp[1]=f[1];
	dfs2(1,0);
	for(int i=1;i<=cnt;i++)
		if(vis[i]) ans=min(ans,dp[i]);
	printf("%I64d",ans);
	return 0;
}
```

---

## 作者：xht (赞：5)

本题其实很暴力。

主要思路就是，先将点数减小到 $n = 5 \times 10^3$。

假设答案为 $1$，然后每次往最大的子树走，如果答案能够更优则更新答案，否则输出答案即可。

考虑细节上的问题，第一点是，由于点数太大，图是无法显式建出来的。

如何隐式建图呢？

首先可以将 $1! \sim n!$ 的所有质因数以及幂次数都求出来，具体来说就是求出 $1 \sim n$ 的然后做一个前缀和即可。

然后对于每个 $i$ 建立一个指针 $p_i$ 指向 $i!$ 的最大质因数，特别地如果 $c_i$（即 $i$ 出现的次数）为零则最大质因数默认为 $1$。

那么每次往一棵子树走的时候，动态维护这个指针即可。

接下来考虑时间复杂度。

由于一个点的可重质因子个数是 $\mathcal O(\log n)$ 级别的，因此最多走 $\mathcal O(n \log n)$ 条边。

每走一条边需要均摊 $\mathcal O(n)$ 的时间维护。

总时间复杂度 $\mathcal O(n^2 \log n)$。

```cpp
const int N = 5e3 + 1;
int n, c[N], f[N][N], p[N], s[N];
ll ans, now;

int main() {
	rd(n);
	for (int i = 1, x; i <= n; i++) rd(x), ++c[x];
	for (int i = 2; i < N; i++) {
		memcpy(f[i], f[i-1], sizeof(f[i]));
		for (int j = 2, k = i; j <= k; j++)
			while (k % j == 0) ++f[i][j], k /= j;
	}
	for (int i = 1; i < N; i++)
		if (!c[i]) p[i] = 1;
		else for (int j = 1; j <= i; j++)
			if (f[i][j]) p[i] = j, now += 1ll * f[i][j] * c[i];
	ans = now;
	while (*max_element(p + 1, p + N) > 1) {
		memset(s, 0, sizeof(s));
		for (int i = 0; i < N; i++) s[p[i]] += c[i];
		int o = max_element(s + 1, s + N) - s, w = s[o];
		if (w * 2 <= n || o == 1) break;
		ans = min(ans, now -= w * 2 - n);
		for (int i = 0; i < N; i++) {
			if (p[i] != o) p[i] = 1;
			if (p[i] == 1) continue;
			--f[i][p[i]];
			while (p[i] > 1 && !f[i][p[i]]) --p[i];
		}
	}
	print(ans);
	return 0;
}
```

---

## 作者：Soulist (赞：4)

水水水水水水水题解。

考虑如何描述答案会变小，套用幻想乡战略游戏的结论即可。

具体如下：

考虑跨过一条边从 $x$ 走到 $v$，对于答案的变化，应当形如 $+(n-sz_v)-sz_v$

换句话说会变小等价于 $2sz_v>n$，这样的点 $v$ 在 $x$ 的出边中唯一。

注意到以 $x$ 为根后子树大小随父亲到儿子单调不升，显然如果至此点没有合法的点时既有到达最优。

接下来考虑如何求出每个点内部的子树大小。

我们会发现实际上 $\dfrac{x}{f(x)}$ 这个形式是容易找到规律的，它指明 $x$ 往上走到的祖先是 $x$ 的最大质因数。

所以我们实际上只需要对 $x!$ 类型的所有点进行质因数分解，然后依次把质因数消掉即可。

然后又因为我们每次走的质因数显然单调，所以暴力从大到小枚举质因数即可。

复杂度可以被感性理解为：$O(n^2\log \log n)$ 证明不会。

然后细节比较多。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int M = 5000 + 5 ;
const int N = 1000 + 5 ;
int n, m, a[M], k[M][N], R[M], use[M], p[N], sum[M], Ans, top, isp[M] ; 
void init( int x ) {
	rep( i, 2, x )
		if( !isp[i] ) { p[++ top] = i ;
			for( re int j = 2 * i; j <= x; j += i ) isp[j] = 1 ;
		}
	rep( i, 1, top ) {
		int u = p[i] ; for( re int j = u; j <= x; j += u ) k[j][i] = k[j / u][i] + 1 ;
	} sum[0] = sum[1] = 0 ;
	rep( i, 2, x ) {
		sum[i] = sum[i - 1] ;
		rep( j, 1, top ) sum[i] += k[i][j] ;
		rep( j, 1, top ) k[i][j] += k[i - 1][j] ;
		for( re int j = top; j >= 1; -- j )
		if( k[i][j] ) { R[i] = j ; break ; }
		Ans = Ans + sum[i] * a[i] ;
	}
}
signed main()
{
	n = gi() ; int x, cnt = 0, sz ;
	rep( i, 1, n ) x = gi(), ++ a[x], m = max( m, x ) ;
	init( m ) ; int flag = 1 ;
	for( re int i = top; i >= 1; -- i ) {
		flag = 1 ; while( flag ) {
			sz = 0 ; 
			rep( j, 2, m ) if( R[j] == i && ( use[j] == cnt ) ) sz += a[j] ; 
			if( 2 * sz > n ) {
				Ans = Ans + n - 2 * sz ; 
				rep( j, 2, m ) if( R[j] == i && ( use[j] == cnt ) ) { 
					-- k[j][R[j]], ++ use[j] ; if( !k[j][R[j]] )
					while( ( !k[j][R[j]] ) && ( R[j] != 0 ) ) -- R[j] ;
				} ++ cnt, flag = 1 ;
			} else flag = 0 ;
		} 
	} printf("%lld\n", Ans ) ;
	return 0 ;
}
```

---

## 作者：RiverHamster (赞：3)

[官方题解](https://codeforces.com/blog/entry/73051)

[在我的blog阅读](https://www.cnblogs.com/RiverHamster/sol-cf1292d)

记$K = \max{k_i}$

貌似比原题解的复杂度正确一点，$O(K\log^2 K )$的

## 题意

给一棵树，$i$与$\dfrac{i}{minFactor(i)}$连边

给$n$个关键点，每个点的位置是$k_i!$

求一个点到所有关键点距离最短（重复算多次），$n \leq 10^6, k_i \leq 5\times10^3$

## 思路

- 到所有点的最短距离其实等价于求树的重心（点、边均带权）
- 构出虚树就可以解决

首先发现，LCA的深度就是公共最大质因子个数，每个点的分叉的位置就是第一次质因子改变的地方。如$5^2$变成$5^3$就会分叉。

依次插入$1!$到 $5000!$，设插入$i!$

显然，插入一个质数一定会连接$1$，否则对$i$做质因子分解，第一次改变的质因子一定是$i$的最大质因子

所以可以求出这个质因子，$(i-1)!$中大于等于它的质因子不会分叉，然后在这个位置分叉（可能在一条虚边上，需要拆开边，开一个新点）。

用树状数组维护$(i-1)!$的各个质因子出现个数，就可以快速求出公共部分的长度，记为$com$，然后将$(i-1)!$的质因子个数和记为$facSum$，$facSum - com$就是要跳的步数，暴力向上跳，然后需要开新点就开新点，不需要就直接挂下面就好了，连一条长为$facSum' - com$（$facSum'$为$i!$的质因子个数）即可，这里有点类似SAM插入。

最后从根节点开始贪心地进入$size \geq \lfloor \dfrac{n}{2} \rfloor$的子树即可。

## 复杂度
- $k$次查询树状数组，$O(K \log K)$
- 每次分解质因子插入树状数组，$O(K \log ^2 K)$（最多有$O(K \log K)$个质因子）
- 每次暴力向上跳，因为每次深度$+1$（指虚树），所以$O(K)$
- 上界不是很紧

## Code
[CF提交记录](https://codeforces.com/contest/1292/submission/69286634)

也可以在我blog看

好像写长了点...


---

## 作者：lfxxx (赞：1)

可以做到 $O(\max k \log{\max k} + n)$，不知道为什么开这么小。

首先建边方式就是每次除掉一个最小的质因子，假若你把所有点拎出来建虚树，那么在虚树上不断走大于 $\frac{n}{2}$ 的子树即可，但是不需要真的建立虚树，因为我们有如下结论：令关键点 $i!$ 编号为 $i$，则任意子树内所有关键点编号为一段连续区间。

证明考虑从 $i! \to (i+1)!$ 时，是一个旋转的过程，转出了子树就不会回来了。

于是我们考虑假装在虚树上走，并维护当前节点子树内的关键点编号为 $[l,r]$，走到这个节点的质数为 $now$，我们考虑下一个分岔口的形态有两种可能：

1. 假若 $r!$ 与 $l!$ 中 $now$ 作为因子出现数量一致，那么在 $now$ 处不会产生分叉，令 $now$ 为比其小的第一个质数继续判断下去。

2. 假若 $l!$ 与 $r!$ 中 $now$ 的数量不同，那么令 $L = (\frac{l}{now}+1) \times now$，则区间 $[l,L-1],[L,r]$ 会形成一个分岔口，区间 $[l,L-1]$ 代表其乘的是第一个小于 $now$ 的质数而 $[L,r]$ 乘的是 $now$，找到大于 $\frac{n}{2}$ 的子树向子树内递归即可。

上面的操作总共会做虚树上路径长度加上质数数量次，每次需要 $\log \max k$ 的时间判断，子树大小前缀和预处理下即可，总复杂度就是 $O(\max k \log{\max k} + n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxv = 2e6+114;
int stk[maxv],tp;
int Pr[maxv];
void init(){
    for(int i=2;i<maxv;i++){
        if(Pr[i]==0){
            stk[++tp]=i;
        }
        for(int j=1;j<=tp;j++){
            if(i*stk[j]>=maxv) break;
            Pr[i*stk[j]]=stk[j];
            if(i%stk[j]==0) break;
        }
    }
}
int pre[maxv];
int cnt[maxv];
int ask(int u,int p){
    int res=0;
    int q=p;
    while(u>=q){
        res+=u/q;
        q*=p;
    }
    return res;
}
int ans;
int now;
int l,r;
int n;
signed main(){
    //freopen("battle.in","r",stdin);
    //freopen("battle.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    init();
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        if(x==0) x=1;
        pre[x]++;        
    }
    for(int i=1;i<maxv;i++) pre[i]+=pre[i-1];
    for(int i=1;i<maxv;i++){
        cnt[i]=cnt[i-1];
        int x=i;
        while(Pr[x]!=0){
            cnt[i]++;
            x/=Pr[x];
        }
        if(x!=1) cnt[i]++;
        ans+=cnt[i]*(pre[i]-pre[i-1]);
    }
    for(int i=1;i<=tp;i++){
        int sub=(i==tp?(pre[maxv-1]-pre[stk[i]-1]):(pre[stk[i+1]-1]-pre[stk[i]-1]));
        if((pre[maxv-1]-sub)-sub<0){
            l=stk[i],r=(i==tp?maxv-1:stk[i+1]-1);
            ans=ans+(pre[maxv-1]-sub)-sub;
            now=i;
        }
    }
    while(now!=0){
        if(r<((l/stk[now])+1)*stk[now]){
            if(now==1) break;
            int sub=pre[r]-pre[l-1];
            if((pre[maxv-1]-sub)-sub<0){
                ans=ans+((pre[maxv-1]-sub)-sub)*ask(l,stk[now-1]);
                now--;
            }else{
                break;
            }
        }else{
            int L=((l/stk[now])+1)*stk[now];         
            //[l,L-1] [L,r]
            int sub1=pre[L-1]-pre[l-1];
            int sub2=pre[r]-pre[L-1];
            if((pre[maxv-1]-sub1)-sub1<0){
                if(now==1) break;
                ans=(ans+((pre[maxv-1]-sub1)-sub1)*ask(l,stk[now-1]));
                now--;
                r=L-1;
            }else if((pre[maxv-1]-sub2)-sub2<0){
                int e=ask(L+1,stk[now])-ask(l,stk[now]);
                ans=(ans+((pre[maxv-1]-sub2)-sub2)*e);
                l=L;
            }else break;
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：zhouhuanyi (赞：1)

链接:https://www.luogu.com.cn/problem/CF1292D

~~话说这个题怎么比上面那道题还要简单，顺序是不是弄反了。~~

讲一讲我的做法:

题解:如果我们把这些数看成一棵树，每个节点x的父亲是$\frac{x}{f(x)}$(其中$f(x)$是$x$的最小质因子)。样例的图给了我们一个很好的示范:
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1292D/e214af30f3eb751abab75da52b3089227c0773fd.png)

我们可以发现，原问题其实就是让我们求一个节点到所有结点的路径和最小，其实这就是一个树上问题。

我们考虑解决这个树上问题，由于数太大，我们可以做一个类似扩域的操作，定义树上的每一个数都为($a_{1},a_{2},a_{3},...a_{5000}$)的形式(其中$a_{i}$表示在该数的质因子中，$i$出现的次数)。

现在我们需要定义如下三个运算：

$1.x\times y$

$2.lca(x,y)$

$3.dis(x,y)$

对于第一种运算，将每一位的$a_{i}$相加即可。我们可以用第一种运算预处理$x!$所表示的数。

对于第二种运算，可以求出两个数的最长公共后缀，最长公共后缀的位就取它们两个相同的值，不一样的那一位取最小值，前面的位就取$0$。

对于第三种运算，也可以求出两个数的最长公共后缀，最长公共后缀的位没有贡献，不一样的那一位的贡献则为它们的差，前面的位的贡献则为它们的和。

考虑树上的节点过多，而有用的只有输入的节点以及它们的$lca$，所以我们可以重新建一棵树。由于一个$lca$可能是另外两个$lca$的$lca$，而深度最大的$lca$不能是其他$lca$的$lca$。所以我们可以将$lca$按深度排序，利用类似$kruskal$重构树的方法建树。但这样的$lca$有$n^2$个，建树的复杂度过高。

考虑优化。重新考虑第二种运算，可以发现每个数的$lca$的深度即为两个数的最长公共后缀的大小。将每个数看作一个字符串，因为质因子个数是递增的，所以较小数的字典序也最小。利用后缀数组的值是我们知道，字典序相邻的最长公共后缀会尽量大，所以我们使用到的$lca$只有相邻两数的$lca$。

建出树后，原问题彻彻底底的变为了树上问题，换根$dp$即可。

```
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
struct node
{
	int map[5001];
};
struct reads
{
	int v,data,nxt;
};
reads edge[10001];
node a[10001],sum[10001];
int b[1000001],n,x,leng;
long long S,head[10001],len,dp[10001],dp2[10001],sz[10001],res=1e18,t,num[10001],length;
bool used[10001];
node c,ans;
struct tree_made
{
	int depth,num,x,y;
	bool operator < (const tree_made &t)const
	{
		return depth>t.depth;
	}
};
tree_made LCA[5001];
void add_edge(int x,int y,int z)
{
	edge[++len].v=y;
	edge[len].data=z;
	edge[len].nxt=head[x];
	head[x]=len;
	return;
}
node add(node a,node b)
{
	for (int i=1;i<=5000;++i)
		c.map[i]=a.map[i]+b.map[i];
	return c;
}
int dist(node a,node b)
{
	int sum=0,i;
	for (i=5000;i>=1;--i)
		if (a.map[i]!=b.map[i])
		{
			sum=abs(a.map[i]-b.map[i]);
			break;
		}
	i--;
    for (;i>=1;--i)
    	sum+=a.map[i]+b.map[i];
    return sum;
}
node lca(node a,node b)
{
	for (int i=1;i<=5000;++i)
		c.map[i]=0;
	for (int i=5000;i>=1;--i)
	{
		c.map[i]=a.map[i];
		if (a.map[i]!=b.map[i])
		{
			c.map[i]=min(a.map[i],b.map[i]);
			return c;
		}
	}
	return a;
}
void dfs(int x)
{
	used[x]=1;
	dp[x]=0;
	sz[x]=num[x];
	for (int i=head[x];i>0;i=edge[i].nxt)
		if (!used[edge[i].v])
		{
			dfs(edge[i].v);
			dp[x]+=dp[edge[i].v]+sz[edge[i].v]*edge[i].data;
			sz[x]+=sz[edge[i].v];
		}
	return;
}
void dfs2(int x)
{
	used[x]=0;
	for (int i=head[x];i>0;i=edge[i].nxt)
		if (used[edge[i].v])
		{
			dp2[edge[i].v]=dp2[x]+edge[i].data*(n-sz[edge[i].v])-sz[edge[i].v]*edge[i].data;
			dfs2(edge[i].v);
		}
	return;
}
int rt[10001];
int find(int x)
{
	if (rt[x]==x)
		return x;
	return rt[x]=find(rt[x]);
}
void unionn(int x,int y)
{
	rt[find(x)]=find(y);
	return;
}
signed main()
{
	cin>>n;
	for (int i=2;i<=5000;++i)
	{
		t=i;
		for (int j=2;j*j<=i;++j)
			if (t%j==0)
			{
				while (t%j==0)
				{
					t/=j;
					a[i].map[j]++;
				}
			}
		if (t>1)
			a[i].map[t]++;
	} 
	for (int i=1;i<=5000;++i)
		sum[i]=add(sum[i-1],a[i]);
	for (int i=1;i<=n;++i)
		cin>>b[i];
	for (int i=1;i<=n;++i)
	{
		if (b[i]==0)
			b[i]++;
		num[b[i]]++;
	}
	for (int i=1;i<=10000;++i)
		rt[i]=i;
	length=0;
	S=5000;
	for (int i=2;i<=5000;++i)
	{
		if (dist(lca(sum[i],sum[i-1]),sum[i-1])!=0)
		{
			++S; 
			LCA[++length].num=S;
			sum[S]=lca(sum[i],sum[i-1]);
		}
		else
			LCA[++length].num=i-1;
		LCA[length].x=i;
		LCA[length].y=i-1;
		LCA[length].depth=dist(sum[1],lca(sum[i],sum[i-1]));
	}
	sort(LCA+1,LCA+length+1);
	for (int i=1;i<=length;++i)
	{
		add_edge(LCA[i].num,find(LCA[i].x),dist(sum[LCA[i].num],sum[find(LCA[i].x)]));
		add_edge(LCA[i].num,find(LCA[i].y),dist(sum[LCA[i].num],sum[find(LCA[i].y)]));
		if (find(LCA[i].x!=LCA[i].num))
			unionn(LCA[i].x,LCA[i].num);
		if (find(LCA[i].y!=LCA[i].num))
			unionn(LCA[i].y,LCA[i].num);
	}
	dfs(LCA[length].num); 
	dp2[LCA[length].num]=dp[LCA[length].num];
	dfs2(LCA[length].num);
	for (int i=1;i<=S;++i)
		res=min(res,dp2[i]);
	cout<<res<<endl;
	return 0;
}

---

## 作者：Mirasycle (赞：0)

首先根据经典结论，题目中的 $P$ 点即为重心。

本题为找重心的一大经典方法，也就是在更优的情况下每次都往最大的子树走一步，直到抵达重心。

思考一下判定重心的结论，假设树的大小为 $n$，就是以某个点为根的时候，所有子树的大小都 $\le \dfrac{n}{2}$。注意这里的大小 $n$ 是题目中所给关键点的个数，而非算上了那些虚点，因为虚点唯一的作用就是增加了长度，而树重心的位置和边权无关，只与点权有关，具体证明可以看 [P3345 的第一篇题解](https://www.luogu.com.cn/article/8lwanwsi)，注意那篇题解里有个笔误，就是他说和点权无关，实际是和点权有关的。

我们初始从 $1$ 节点出发，然后开始统计每个子树的大小，由题意可得每个数所在子树都是**以它的最大质因子为根的子树**。

于是我们统计每个质因子作为最大质因子出现的次数，设出现次数最大的质因子为 $p$，如果 $2\times sz_p >n$（此时不符合上述所说的结论），我们就往 $p$ 所在子树内走一步，动态更新答案（答案要增加 $n-sz_p$，同时减小 $sz_p$）。

每次移动之后修改关键点所在子树的根的信息，比如从 $1\to p$ 之后，$p$ 子树之外的关键点所在子树的根就变成了 $1$。同时 $p$ 子树内的关键点的子树根也变了，如果 $p$ 的幂次为 $1$ 就变成了次大质因数，否则就还是 $p$。注意前后两个 $p$ 数字大小相同，但是点不同。

所以每次移动 $rt\to rt'$ 之后，$rt'$ 外部的关键点所在子树的根就变成了 $rt$。我们要让 $sz_{rt}\gets n-sz_{rt'}$。对于原本 $rt$ 子树内的关键点，它们所在子树内的根变成了可重质因子集合中的次大，同时把最大的踢出去。

由于每个数的可重质因子个数不超过 $O(n\log V)$，所以时间复杂度为 $O(n^2\log V)$。

---

## 作者：Purslane (赞：0)

# Solution

考虑 $\text{dis}(u,v) = \text{dep}_u + \text{dep}_v - 2 \text{dep}_{\text{lca}(u,v)}$，因此在固定 $\text{dep}_P$ 时，最大化 $\sum \text{dep}_{\text{lca}(P,p_i)}$。

考虑两个点的 $\rm lca$ 数论意义是什么。显然是，将所有质因数排列后的 $\rm lcp$。

这启发我们倒着建立阶乘的所有质因数的字典树。然后可以在上面直接遍历关键点（注意关键点一定是阶乘对应的点的祖先的集合）。

直接遍历这棵树显然不太对（主要是 Trie 树在字符集大的时候有点耗空间，其实发现每个点的 $\deg$ 均摊一下不是太大，但是这样难写），发现每个时刻当前访问的点子树内的节点编号是一个区间。所以直接模拟这个过程即可。

我写的是 $O(V^2 \log^2 V)$ 的，把 `calc` 函数换成预处理就是 $O(V^2 \log V)$ 的了。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e3+10;
int n,m=5000,dep[MAXN],flg[MAXN],cnt[MAXN],pre[MAXN];
ll tot,mx[MAXN*15];
vector<int> pr;
int calc(int v,int p) {
	int ans=0;
	while(v>=p) ans+=v/p,v/=p;
	return ans;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,2,m) ffor(j,2,m/i) flg[i*j]=1;
	ffor(i,2,m) ffor(j,1,i) if(flg[j]==0&&i%j==0) {dep[i]=dep[i/j]+1;}
	ffor(i,1,m) dep[i]+=dep[i-1];
	ffor(i,2,m) if(!flg[i]) pr.push_back(i);
	reverse(pr.begin(),pr.end());
	ffor(i,1,n) {int p;cin>>p,cnt[p]++,tot+=dep[p];}
	ffor(i,1,m) pre[i]=pre[i-1]+cnt[i];
	ffor(i,1,m) if(cnt[i]) {
		int l=1,r=m,tmp=0;
		ll sum=0;
		for(auto v:pr) {
			int cnt=0,mul=i;
			while(mul>=v) cnt+=mul/v,mul/=v;
			if(cnt) ffor(j,1,cnt) {
				while(calc(l,v)<j) l++;
				tmp++,sum+=pre[r]-pre[l-1],mx[tmp]=max(mx[tmp],sum);
			}
			r=min(r,(i/v+1)*v-1);
		}
	}
	ll ans=LONG_LONG_MAX;
	ffor(i,0,m*15) ans=min(ans,1ll*i*n+tot-2*mx[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：OptimisticForever (赞：0)

考虑建出虚树之后就好做了，我们只需要找重心。

如何建虚树？提供一个不需要单调栈的做法。

我们求出相邻两个数 $(i,i+1)$ 的 $lca$ 的深度，对深度建笛卡尔树，然后建成一棵新的树 $T'$。

对这个 $T'$ 求重心即可。

这个做法的正确性依赖于相同的 $lca$ 是一段连续的区间，由于 $i!$ 本身的 dfs 序就已经排好了，所以这是正确的。

现在题目变成求 $(i,i+1)$ 的深度，我们发现 $i+1$ 的最大质因子后面的位置都是不变的，所以深度就等于大于这个质因子的次数和加上 $i!$ 这个质因子的次数，容易使用树状数组维护。时间复杂度 $O(k\log^2 k+n)$。 

顺带提一下如何找重心，众所周知重心与边权无关，所以我们对点权找出重心，然后就可以直接计算了。

---

## 作者：lizihan250 (赞：0)

# Codeforces Round 614 Div 2 F & Div 1 D. Chaotic V.

## 题意简述

设 $x$ 为大于 $1$ 的整数，定义 $f(x)$ 为 $x$ 的最大质因子。

构造一棵以 $1$ 号节点为根的树，对于任意整数 $x>0$，有 $x$ 号的节点的父亲节点为 $\frac{x}{f(x)}$。

给定 $n (1 \le n \le 10^6)$ 个“关键点”，每个“关键点”的编号都可以表示为 $k!$ 的形式。其中， $k$ 为小于等于 $5000$ 的自然数， $!$ 表示阶乘。

试指定一节点，使其到所有“关键点”的距离之和最小。注意可能有多个编号相同的“关键点”，此时这些点视为不同的点。

## 解题思路

观察树的性质，容易发现：若从 $1$ 号节点走到一个编号为 $\prod \limits_{i=1}^n p_i^{a_i}$ 的点，会先经过 $a_n$ 条边，每条边连接的儿子节点的编号恰是父亲节点编号的 $p_n$ 倍；再经过 $a_{n-1}$ 条边，每条边连接的儿子节点的编号恰是父亲节点编号的 $p_{n-1}$ 倍……依此类推。

既然从 $1$ 号节点往其它节点走有着特别特殊的含义。我们考虑如下算法：先假定答案节点为 $1$ 号节点，接着尝试向一个子树拓展。若这个子树内有 $x$ 个关键点，则将答案节点移动到这个子树的根节点可以使答案节点与 $x$ 个节点的距离减少 $1$，与剩下 $n-x$ 个节点的距离增加 $1$。因此，若 $x > n-x$，则答案节点变为该子树的根节点。若某一刻，答案节点变为向任何一个子节点都会使答案增大，则算法结束，给出答案。直接暴力模拟这个过程的时间复杂度极高，我们考虑优化这个过程。

首先，$n$ 的规模达到了惊人的 $10^6$，然而事实上，所有点编号只有 $5000$ 种不同的取值。我们可以将编号相同的点合并。

接着，我们考虑“转移”。若当前答案节点为 $x$，当前子树内的所有“关键点”的编号除以 $x$ 后的最大质因子均为 $p$，则若能转移的话，必然转移到编号为 $x \times p$ 的点。否则，选择一个数 $p$，使得当前子树内以 $p$ 为最大质因子的的数最多，然后尝试转移到编号为 $x \times p$ 的节点。

一步一步往下跳显然很慢，我们考虑合并转移操作。若当前子树内的所有“关键点”的编号除以 $x$ 后的最大质因子均为 $p$，且存在最大的正整数 $a$，使得它们都能被 $p^a$ 整除，则我们可以一次性向上跳 $k$ 步。

每转移一次至少会使 $1$ 个值的关键节点离开子树，每次删除一个节点时间复杂度 $O(k)$，故时间复杂度 $O(k^2)$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxk=5000,Maxp=669;
bitset<Maxk+10> isn_prime(1);
int cnt,primes[Maxp+10];
int n,nw,cn,oppo=0,flag=0,p,mx,nums[Maxk+10],mp[Maxk+10][Maxp+10],sum[Maxk+10];
long long dis;
vector<int> remain,er;
vector<int>::iterator it;
int main()
{
    //freopen("Ivy.in","r",stdin);
    //freopen("Ivy.out","w",stdout);
    for(int i=2;i<=Maxk;i++)
    {
        if(isn_prime[i]) continue;
        cnt++;
        primes[cnt]=i;
        for(int j=i*i;j<=Maxk;j+=i) isn_prime[j]=true;
    }
    sum[0]=0;
    for(int i=1;i<=Maxp;i++)
        mp[0][i]=0;
    for(int i=1;i<=Maxk;i++)
    {
        sum[i]=sum[i-1];
        for(int j=1;j<=Maxp;j++)
            mp[i][j]=mp[i-1][j];
        nw=i;
        for(int j=1;j<=cnt;j++)
            while(nw%primes[j]==0)
            {
                sum[i]++;
                mp[i][j]++;
                nw/=primes[j];
            }
    }
    mx=cnt;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&cn);
        if(cn==0) cn=1;
        nums[cn]++;
        dis+=sum[cn];
    }
    for(int i=1;i<=Maxk;i++)
        if(nums[i]>0) remain.emplace_back(i);
    /*printf("%lld %d\n",dis,mx);
    for(int i=0;i<remain.size();i++)
    {
        printf("%d %d\n",remain[i],nums[remain[i]]);
    }
    printf("\n");*/
    while((oppo<<1)<n&&mx>0)
    {
        p=100000;
        for(int i=0;i<remain.size();i++)
            p=min(p,mp[remain[i]][mx]);
        for(int i=0;i<remain.size();i++)
            mp[remain[i]][mx]-=p;
        dis-=1ll*p*(n-(oppo<<1));
        flag=0;
        for(int i=0;i<remain.size();i++)
            if(mp[remain[i]][mx]>0) flag+=nums[remain[i]];
        if((flag<<1)>n)
        {
            for(int i=0;i<remain.size();i++)
                if(mp[remain[i]][mx]==0) oppo+=nums[remain[i]],remain.erase(remain.begin()+i),i--;
        }
        else
        {
            for(int i=0;i<remain.size();i++)
                if(mp[remain[i]][mx]>0) oppo+=nums[remain[i]],remain.erase(remain.begin()+i),i--;
            mx--;
        }
        /*printf("%lld %d %d\n",dis,mx,oppo);
        for(int i=0;i<remain.size();i++)
        {
            printf("%d %d\n",remain[i],nums[remain[i]]);
        }
        printf("\n");*/
    }
    printf("%lld\n",dis);
    return 0;
}

```

---

## 作者：_edge_ (赞：0)

考虑暴力，我们直接求出每一个点的父亲，把整棵树的都建出来，那求树的重心就很简单了。

怎么暴力呢，我们观察每次乘上一个数 $i$，把这个数先分解质因数。

$i=\prod \limits _{i=1}^{cnt} p_i^{k_i}$ 并且保证 $p_{i-1} < p_{i}$。

我们考虑他找父亲的过程，一定是先把最小的那个质因子除掉，然后往上，我们试图寻找出他第一个在原来树上的节点。

这个非常好找，容易发现只要 $i$ 的最大质因子被除掉即可。

然后，我们利用一个桶，记录当前 $tot \sim i$ 这些数对应的节点，这样就可以在 $O(\dfrac{k^2}{\log k})$ 的时间内定位出来了。

打个表发现节点总数大概只有 3e7 级别。

然后我们需要注意一下空间，直接开是开不下的，考虑把一条链的情况缩到一个 bool 数组里面，表示 $x$ 和 $x+1$ 是否有连边即可。


```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define pb push_back 
using namespace std;
mt19937 rnd(chrono::system_clock().now().time_since_epoch().count());
int gen(int l,int r) {return rnd()%(r-l+1)+l;}
const int INF=32684653+5;
const int INFN=5e3+5;
struct _node_edge{
    int to_,next_;
}edge[INFN<<2];
int tot,head[INF],sz[INF];
bool vis[INF];
void add_edge(int x,int y) {
    edge[++tot]={y,head[x]};
    head[x]=tot;
}
int rt,Max;
int n,num[INFN],totn,A[INFN],L[INFN];
long long res;
int id[INFN],Prime[INFN],pre[INFN],prime[INFN],p[INFN];
void DFS(int x,int fa) {
    // if (x<=10) cerr<<x<<" "<<fa<<" qwqeqwe?\n";
    int Max2=0;
    for (int i=head[x];i;i=edge[i].next_) {
        int v=edge[i].to_;
        if (v==fa) continue;
        DFS(v,x);
        Max2=max(Max2,sz[v]);
        sz[x]+=sz[v];
    }
    if (vis[x+1]) {
        int v=x+1;
        if (v!=fa) {
            DFS(v,x);
            Max2=max(Max2,sz[v]);
            sz[x]+=sz[v];
        }
    }
    Max2=max(Max2,n-sz[x]);
    if (Max>Max2) Max=Max2,rt=x;
}
void DFS2(int x,int fa) {
    for (int i=head[x];i;i=edge[i].next_) {
        int v=edge[i].to_;
        if (v==fa) continue;
        DFS2(v,x);
        sz[x]+=sz[v];
        res+=sz[v];
    }
    if (vis[x]) {
        int v=x-1;
        if (v!=fa) {
            DFS2(v,x);
            sz[x]+=sz[v];
            res+=sz[v];
        }
    }
    if (vis[x+1]) {
        int v=x+1;
        if (v!=fa) {
            DFS2(v,x);
            sz[x]+=sz[v];
            res+=sz[v];
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    memset(prime,1,sizeof prime);
    prime[0]=prime[1]=0;int N=5e3;
    for (int i=2;i<=N;i++) {
        if (prime[i]) Prime[++Prime[0]]=i,pre[i]=Prime[0];
        for (int j=1;j<=Prime[0] && Prime[j]*i<=N;j++) {
            prime[Prime[j]*i]=0;
            if (!(i%Prime[j])) break;
        }
    }
    cin>>n;
    for (int i=1;i<=n;i++) {
        int x=0;cin>>x;
        num[x]++;
    }
    num[1]+=num[0];num[0]=0;
    ++totn;sz[1]+=num[1];pre[1]=1;
    for (int i=2;i<=5e3;i++) {
        int xx=i,cnt1=0,kk=0;
        for (int j=1;j<=Prime[0];j++) {
            if (xx%Prime[j]) continue;
            kk=0;
            while (xx%Prime[j]==0) 
                xx/=Prime[j],A[j]++,cnt1=max(cnt1,j),kk++;
        }
        int ba=kk;
        for (int j=1;j<cnt1;j++) ba+=A[j]; // totn+1 ? 
        if (!L[cnt1]) L[cnt1]=1;
        add_edge(totn+1,L[cnt1]);add_edge(L[cnt1],totn+1);
        // for (int j=totn+2;j<=totn+ba;j++) add_edge(j,j-1);
        for (int j=totn+2;j<=totn+ba;j++) vis[j]=1;
        sz[totn+ba]+=num[i];pre[i]=totn+ba;
        int AA=ba;
        // L[cnt1]=totn+1
        int id3=totn+kk;ba=kk;
        for (int j=cnt1;j;j--) {
            L[j]=id3;
            id3+=A[j-1];
        }
        totn+=AA;
    }
    // cerr<<totn<<" qweq?\n";

    Max=1e9;DFS(1,0);
    for (int i=1;i<=totn;i++) sz[i]=0;
    for (int i=1;i<=5e3;i++) sz[pre[i]]+=num[i];
    DFS2(rt,0);
    cout<<res<<"\n";
    return 0;
}
```

---

## 作者：Leasier (赞：0)

考虑来分析 $\operatorname{LCA}_T (x, y)$ 怎么算：

- 将 $x, y$ 的质因数的幂次按对应的质数升序排序（这里包括 $p^0$ 状物）。
- 设 LCS 中最后一个对应的质数为 $p_i$，则 LCA 为 LCS 中元素之积乘上 $p_{i - 1}^{\min(v_{p_{i - 1}}(x), v_{p_{i - 1}}(y))}$。 

由此我们可以得出 $dis_T (x, y)$ 怎么算：

- 类似地找出上面的 $i$。
- 距离即为两者 $< p_i$ 的部分的幂次和加上 $|v_{p_{i - 1}}(x) - v_{p_{i - 1}}(y)|$。

考虑抓出所有阶乘的质因数分解式。注意到若我们固定一个后缀，质因数分解式包含这个后缀的 $x!$ 对应 $x$ 的范围是一个**区间**。证明是显然的。

考虑从后往前依次向最终的 $P$ 中填入质因数的幂次。设我们现在正在填入 $p_i$，此前的区间为 $[l, r]$，则有两种情况：

- 填入不与区间内任何阶乘相同的幂次：在填完 $i$ 之后，剩下的项我们一定会全部填入 $p_j^0$。枚举 $p_i$ 的幂次即可。
- 填入后新区间 $[l', r'] \subseteq [l, r]$：此时我们填的数固定。

注意到我们可以通过两个前缀和处理出填入每个质数后第 $\leq i$ 位的贡献，于是我们预处理出区间后 dp 即可。

时间复杂度为 $O(n + N^2 \ln \ln N)$，其中 $N$ 为值域 $5 \times 10^3$。

代码：
```cpp
#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

const int N = 5e3;

typedef struct {
	int nxt;
	int end;
} Edge;

typedef struct {
	int cnt = 0;
	int head[N + 7];
	Edge edge[N + 7];
	
	inline void add_edge(int start, int end){
		cnt++;
		edge[cnt].nxt = head[start];
		head[start] = cnt;
		edge[cnt].end = end;
	}
} Graph;

const int M = 669 + 7, K = 4995 + 7;
int prime[N + 7], power[N + 7][M], len[M], lpos[M][N + 7], rpos[M][N + 7], bucket[N + 7], pre[N + 7];
ll sum1[M][N + 7], sum2[K][N + 7], dp[M][N + 7];
bool p[N + 7];
Graph g[M];

inline int init(){
	int cnt = 0;
	p[0] = p[1] = true;
	for (register int i = 2; i <= N; i++){
		if (!p[i]) prime[++cnt] = i;
		for (register int j = 1; j <= cnt && i * prime[j] <= N; j++){
			p[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	for (register int i = 1; i <= N; i++){
		int t = i;
		for (register int j = 1; j <= cnt; j++){
			power[i][j] = power[i - 1][j];
			while (t % prime[j] == 0){
				t /= prime[j];
				power[i][j]++;
			}
		}
	}
	len[cnt + 1] = 1;
	lpos[cnt + 1][1] = 0;
	rpos[cnt + 1][1] = N;
	for (register int i = cnt; i >= 1; i--){
		for (register int j = 1; j <= len[i + 1]; j++){
			for (register int k = lpos[i + 1][j]; k <= rpos[i + 1][j]; ){
				int pos = k;
				while (pos < rpos[i + 1][j] && power[pos + 1][i] == power[k][i]) pos++;
				len[i]++;
				lpos[i][len[i]] = k;
				rpos[i][len[i]] = pos;
				g[i].add_edge(j, len[i]);
				k = pos + 1;
			}
		}
	}
	return cnt;
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline int max(int a, int b){
	return a > b ? a : b;
}

inline ll min(ll a, ll b){
	return a < b ? a : b;
}

int main(){
	int n = read(), cnt = init();
	ll ans = 0x7fffffffffffffffll;
	for (register int i = 1; i <= n; i++){
		int k = read();
		bucket[max(k, 1)]++;
	}
	for (register int i = 1; i <= N; i++){
		pre[i] = pre[i - 1] + bucket[i];
	}
	for (register int i = 1; i <= cnt; i++){
		for (register int j = 1; j <= N; j++){
			sum1[i][j] = sum1[i - 1][j] + sum1[i][j - 1] - sum1[i - 1][j - 1] + (ll)bucket[j] * power[j][i];
		}
	}
	dp[cnt + 1][1] = 0;
	for (register int i = cnt; i >= 1; i--){
		for (register int j = 1; j <= len[i]; j++){
			dp[i][j] = 0x7fffffffffffffffll;
		}
		for (register int j = 0; j <= power[N][i]; j++){
			for (register int k = 1; k <= N; k++){
				sum2[j][k] = sum2[j][k - 1] + (ll)bucket[k] * abs(power[k][i] - j);
			}
		}
		for (register int j = 1; j <= len[i + 1]; j++){
			int out = (lpos[i + 1][j] > 0 ? pre[lpos[i + 1][j] - 1] : 0) + (n - pre[rpos[i + 1][j]]);
			for (register int k = 0; k <= power[N][i]; k++){
				ans = min(ans, dp[i + 1][j] + (ll)power[k][i] * out + (sum2[power[k][i]][rpos[i + 1][j]] - (lpos[i + 1][j] > 0 ? sum2[power[k][i]][lpos[i + 1][j] - 1] : 0)) + (sum1[i - 1][rpos[i + 1][j]] - (lpos[i + 1][j] > 0 ? sum1[i - 1][lpos[i + 1][j] - 1] : 0)));
			}
			for (register int k = g[i].head[j]; k != 0; k = g[i].edge[k].nxt){
				int x = g[i].edge[k].end;
				dp[i][x] = min(dp[i][x], dp[i + 1][j] + (ll)power[lpos[i][x]][i] * out + ((sum2[power[lpos[i][x]][i]][rpos[i + 1][j]] - (lpos[i + 1][j] > 0 ? sum2[power[lpos[i][x]][i]][lpos[i + 1][j] - 1] : 0)) - (sum2[power[lpos[i][x]][i]][rpos[i][x]] - (lpos[i][x] > 0 ? sum2[power[lpos[i][x]][i]][lpos[i][x] - 1] : 0))) + ((sum1[i - 1][rpos[i + 1][j]] - (lpos[i + 1][j] > 0 ? sum1[i - 1][lpos[i + 1][j] - 1] : 0)) - (sum1[i - 1][rpos[i][x]] - (lpos[i][x] > 0 ? sum1[i - 1][lpos[i][x] - 1] : 0))));
			}
		}
	}
	for (register int i = 1; i <= len[1]; i++){
		ans = min(ans, dp[1][i]);
	}
	printf("%lld", ans);
	return 0;
}
```

---

