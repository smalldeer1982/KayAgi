# [ABC201E] Xor Distances

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc201/tasks/abc201_e

$ N $ 頂点の重み付き木があります。$ i $ 本目の辺は頂点 $ u_i $ と頂点 $ v_i $ を双方向に結んでいて、その重みは $ w_i $ です。

頂点の組 $ (x,y) $ について、$ \text{dist}(x,y) $ を以下のように定めます。

- $ x $ から $ y $ への最短パスに含まれる辺全ての重みの **XOR**

$ 1\ \leq\ i\ \lt\ j\ \leq\ N $ を満たす全ての組 $ (i,j) $ について $ \text{dist}(i,j) $ を求め、その総和を $ (10^9+7) $ で割った余りを出力してください。

 $ \text{\ XOR\ } $ とは 整数 $ a,\ b $ のビットごとの排他的論理和 $ a\ \text{\ XOR\ }\ b $ は、以下のように定義されます。

- $ a\ \text{\ XOR\ }\ b $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ a,\ b $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 3\ \text{\ XOR\ }\ 5\ =\ 6 $ となります (二進表記すると: $ 011\ \text{\ XOR\ }\ 101\ =\ 110 $)。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ u_i\ \lt\ v_i\ \leq\ N $
- $ 0\ \leq\ w_i\ \lt\ 2^{60} $
- 与えられるグラフは木
- 入力は全て整数

### Sample Explanation 1

$ \text{dist}(1,2)=1, $ $ \text{dist}(1,3)=3, $ $ \text{dist}(2,3)=2 $ であり、これらの総和は $ 6 $ です。

### Sample Explanation 3

$ (10^9+7) $ で割った余りを出力してください。

## 样例 #1

### 输入

```
3
1 2 1
1 3 3```

### 输出

```
6```

## 样例 #2

### 输入

```
5
3 5 2
2 3 2
1 5 1
4 5 13```

### 输出

```
62```

## 样例 #3

### 输入

```
10
5 7 459221860242673109
6 8 248001948488076933
3 5 371922579800289138
2 5 773108338386747788
6 10 181747352791505823
1 3 803225386673329326
7 8 139939802736535485
9 10 657980865814127926
2 4 146378247587539124```

### 输出

```
241240228```

# 题解

## 作者：allqpsi (赞：6)

比赛时只想出一半，现在来打题解了。

## 思路：

先说一个性质：在一个树上，两个节点之间的路径的异或值等于他们两到根节点的异或值互相异或。原因很简单，$a\oplus a$ 等于零。所以根节点到它们两的公共部分抵消没了，只剩两个节点之间的路径的异或值。

然后我们预处理出根节点到每点的异或值，就把问题转换为：给你一个数组，其中每两个数相互异或和所得的值。

怎么做呢，我考场上就是这里寄的。我们可以分别对于每个 $2^i$ 分别计算它的贡献。什么时候 $2^i$ 有贡献呢？我们设有 $x$ 个数模 $2^i$ 为一，则其贡献为 $\left( x\times \left( n-x\right) \right) \times 2^{i}$。为什么呢？因为当我们两个数相互异或，只有这两个数在此位不同是才可取到此值。则 $x$ 为此位为一的数 $n-x$ 为此位为零的数。贡献便为它们两相乘再乘 $2^i$。

时间复杂度：$O\left( n\right)$ 预处理根到每个节点距离，$O\left( n\log V\right)$ 预处理 $x$，$O\left( \log V\right)$ 算贡献，总体 $O\left( n\log V\right)$。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,a,b,c,di[200005],ans=0,f[65];
struct node{
	int x,y;
};
vector<node>vi[200005];
void dfs(int x,int fa){
	for(int i=0;i<vi[x].size();i++){
		int v=vi[x][i].x,w=vi[x][i].y;
		if(v==fa){
			continue;
		}
		di[v]=di[x]^w;
		dfs(v,x);
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>a>>b>>c;
		vi[a].push_back(node{b,c});
		vi[b].push_back(node{a,c});
	}
	di[1]=0;
	dfs(1,0);
	for(int i=1;i<=n;i++){
		for(int j=0;j<=60;j++){
			if((di[i]&(1ll<<j))){
				f[j]++;
				f[j]%=mod;
			}
		}
	}
	for(int i=0;i<=60;i++){
		ans+=(((1ll<<i)%mod)*((f[i]*(n-f[i]))%mod))%mod;
		ans%=mod;
	}
	cout<<ans;
}
```

---

## 作者：_Ponder_ (赞：5)

[Xor Distances](https://www.luogu.com.cn/problem/AT_abc201_e)

### 题目大意

给定一颗带边权无根树，定义 $\text{dis}(i,j)$ 表示 $i,j$ 两点在树上的最短路径的边权的异或和。求：
$$\sum_{i=1}^n\sum_{j=i+1}^n\text{dis}(i,j)$$

### 思路分析

首先，容易证明：

$$\text{dis}(i,j)=\text{dis}(i,x)\oplus\text{dis}(x,j)$$

这个式子告诉我们，无论以哪个点作为树的根，树上两点之间的最短路径的边权的异或和等于两点到根的最短路径的边权的异或和的异或。（感性理解就是公共部分被异或了两次消掉了）

那么不妨设 $1$ 为根，先 dfs 一遍求出根到每个点的异或和，再考虑统计答案。

由于异或的每一位是独立的，因此不妨对每一位考虑对答案的贡献。

注意到，只有 $0\oplus1=1$ 会对答案产生贡献，因此可以得出答案的计算式：

$$\text{ans}=\sum 2^ip_i(n-p_i)$$

其中，$p_i$ 表示在所有的异或和中，第 $i$ 位是 $1$ 的数量，$n-p_i$ 就是第 $i$ 位是 $0$ 的数量，根据乘法原理，总贡献就是 $2^ip_i(n-p_i)$。

时间复杂度为 $O(n\log V)$，其中 $V$ 为异或和的值域。

---

证明过程：

记 $\text{lca}(i,j)$ 为 $m$。

$$\begin{aligned}\text{dis}(i,j)&=\text{dis}(i,m)\oplus\text{dis}(m,j)\\&=\text{dis}(i,m)\oplus\text{dis}(m,j)\oplus\text{dis}(m,x)\oplus\text{dis}(m,x)\\&=(\text{dis}(i,m)\oplus\text{dis}(m,x))\oplus(\text{dis}(m,j)\oplus\text{dis}(m,x))\\&=\text{dis}(i,x)\oplus\text{dis}(x,j)\end{aligned}$$

### 代码

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=400200,mod=1000000007;

int to[N],nxt[N],head[N];
int w[N],dis[N],ans;
int n,in1,in2,idx=1,in3;

void add(int u,int v,int c){
    idx++;to[idx]=v;nxt[idx]=head[u];head[u]=idx;w[idx]=c;
}

void dfs(int s,int fa){
    for(int i=head[s];i;i=nxt[i]){
        int v=to[i];
        if(v==fa) continue;
        dis[v]=dis[s]^w[i];//递推异或和
        dfs(v,s);
    }
}

signed main(){
    scanf("%lld",&n);
    for(int i=1;i<n;i++){
        scanf("%lld%lld%lld",&in1,&in2,&in3);
        add(in1,in2,in3);add(in2,in1,in3);
    }
    dfs(1,0);
    for(int i=0;i<60;i++){//最多 60 位
        int cnt=0;
        for(int j=1;j<=n;j++)
            if(dis[j]>>i&1) cnt++;
        int temp=(1ll<<i)%mod;
        int temp2=cnt*(n-cnt)%mod;
        ans=(ans+temp*temp2%mod)%mod;
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：Ginger_he (赞：4)

## 题目描述

给定一棵带权无根树，定义 $dis(i,j)$ 为 $i$ 到 $j$ 最短路径上边权的异或和。

求 $\sum\limits_{1\le i<j\le n}dis(i,j)$，对 $10^9+7$ 取模。

## 题解

钦定 $1$ 为根，则有

$$dis(i,j)=dis(1,i)\oplus dis(1,j)$$

因此，我们可以先 dfs 一遍求出每个点到 $1$ 的距离，记为 $dis_i$，然后考虑二进制下每一位的贡献。

令 $cnt_j$ 表示所有 $dis_i$ 中二进制下第 $j$ 位为 $1$ 的数量，因为只有 $0\oplus1=1$，所以这一位的贡献为

$$cnt_j\times(n-cnt_j)\times2^j$$

将每一位的贡献累加即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 200005
const ll p=1e9+7;
struct node
{
	int v;
	ll w;
};
int n,u,v;
ll w,dis[N],cnt,ans;
vector<node> g[N];
void dfs(int x,int fa)
{
	for(auto i:g[x])
	{
		if(i.v==fa)
			continue;
		dis[i.v]=dis[x]^i.w;
		dfs(i.v,x); 
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%lld",&u,&v,&w);
		g[u].push_back(node{v,w});
		g[v].push_back(node{u,w});
	}
	dfs(1,0);
	for(ll i=0;i<63;i++)
	{
		cnt=0;
		for(int j=1;j<=n;j++)
		{
			if((dis[j]>>i)&1)
				cnt++;
		}
		ans=(ans+(1ll<<i)%p*cnt%p*(n-cnt)%p)%p;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：PineappleSummer (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc201_e)

看题目，发现 `Xor`，一眼异或。

定义 $dis(i,j)$ 为 $i$ 到 $j$ 最短路径上边权的异或和。

钦定 $1$ 为根，则有 $dis(1,i)\oplus dis(1,j)=dis(i,j)$。

画个图理解下：

![](https://cdn.luogu.com.cn/upload/image_hosting/hwfxsgju.png)

设 $k$ 为 $(i,j)$ 的**最近公共祖先**，则根据树上两点间路径唯一，可得 $dis(i,j)=dis(i,k)\oplus dis(j,k)$，而 $dis(1,i)=dis(1,k)\oplus dis(i,k)$，$dis(1,j)=dis(1,k)\oplus dis(j,k)$。由于 $dis(1,k)\oplus dis(1,k)=0$，所以
$$\begin{aligned}
dis(i,j)&=dis(i,k)\oplus dis(j,k)
\\&=dis(1,k)\oplus dis(i,k)\oplus dis(1,k)\oplus dis(j,k)
\\&=dis(1,i)\oplus dis(1,j)
\end{aligned}$$

DFS 遍历整个树，对于 $i\in \left[1,n\right]$，求出来 $dis(1,i)$。答案就转化成了 $\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^ndis(1,i)\oplus dis(1,j)$。

然后就是异或题的常见操作了：拆位算贡献。

对于 $dis(1,i)$ 的第 $k$ 位，它需要和 $n-1$ 个第 $k$ 位进行异或，根据异或的性质 $0\oplus 1=1$，只有一对 $(0,1)$ 才会产生贡献。记第 $k$ 上 $0$ 的个数为 $cnt_0$，$1$ 的个数为 $cnt_1$，则第 $k$ 位对答案的贡献为 $cnt_0\times cnt_1\times 2^k$。

时间复杂度为 $O(n\log V)$，其中 $V$ 为异或和的值域。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=1e9+7;
const int N=2e5+10;
int n,cnt[2];
struct Edge{
	int y;
	ll v;
};
ll d[N],ans;
vector<Edge>G[N];
void dfs(int k,int fa)
{
	for(auto i:G[k])
	{
		if(i.y!=fa)
			d[i.y]=d[k]^i.v,dfs(i.y,k);
	}
}
int main()
{
//    freopen("input.in","r",stdin);
//    freopen("output.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int u,v;
		ll w;
		cin>>u>>v>>w;
		G[u].push_back(Edge{v,w});
		G[v].push_back(Edge{u,w});
	}
	dfs(1,0);
	for(int i=0;i<63;i++)
	{
		cnt[0]=cnt[1]=0;
		for(int j=1;j<=n;j++)
			cnt[(d[j]>>i)&1]++;
		ans=(ans+(1ll<<i)%mod*cnt[1]%mod*cnt[0]%mod)%mod;
	}
	cout<<ans;
    return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc201/submissions/45027416)

---

## 作者：Crazyouth (赞：1)

## 分析

**本文钦定 $1$ 为根。**

不难发现，$\operatorname{dis}(u,v)=\operatorname{dis}(1,u)\oplus\operatorname{dis}(1,v)$，所以原式等于 $\displaystyle\sum_{1\le i<j\le n}(\operatorname{dis}(1,i)\oplus\operatorname{dis}(1,j))$，因此只要计算出每个大于 $1$ 的 $i$ 的 $\operatorname{dis}(1,i)$，就可以把问题转为“给定一个数列，求这些数两两异或的和”，又可以把这个数列的每个数的每个位拿出来转成“给定一个数列，只包含 $0$ 或 $1$，求这些数两两异或的和”，不难发现答案就是 $0$ 的个数，因此乘上当前的位值即可。要注意的是，由于双向存图，最后答案要乘 $2^{-1} \bmod (10^9+7)$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
vector<pair<int,int>> G[200010];
int a[200010];
void dfs(int u,int fa)
{
	for(auto p:G[u])
	{
		int v=p.first,w=p.second;
		if(v==fa) continue;
		a[v]=a[u]^w;
		dfs(v,u);
	}
}
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		G[u].push_back({v,w});
		G[v].push_back({u,w});
	}
	dfs(1,0);
	int ans=0;
	for(int i=60;~i;i--)
	{
		int now=0;
		for(int j=1;j<=n;j++) now+=((a[j]>>i)&1);
		int ret=0;
		for(int j=1;j<=n;j++)
		{
			if((a[j]>>i)&1) ret+=n-now;
			else ret+=now;
		}
		ret>>=1ll;
		ret%=mod; 
		ans=(ans+(1ll<<i)%mod*ret)%mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Sorato_ (赞：0)

# ABC201E Xor Distances

## 题目大意

给定一个带权树，求树上每两点的简单路径上的边权的异或和的和。

形式化的，定义 $dis(i,j)$ 为 $i$ 到 $j$ 的简单路径上的边权的异或和，求 $\large\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\text{dis}(i,j)$。

## Solve

令 $\large f(u)=\sum\limits_{i=1}^n\text{dis}(u,i)$。

指定 $1$ 为根，考虑先 dfs 遍历树求出 $f(1)$，然后换根 $\text{DP}$。

若已知 $f(u)$，对于 $v\in son_u$，我们分两部分考虑，即在子树 $v$ 中的 $A$ 集合和不在子树 $v$ 中的 $B$ 集合。

- 对于 $B$ 中的点，根从 $u$ 转移到 $v$，他们到根的路径的异或和会多异或上 $w(u,v)$。
- 对于 $A$ 中的店，他们到根的路径的异或和会少异或上 $w(u,v)$，由于异或的自反性，通过再异或上一个 $w(u,v)$ 也可以实现。

综上，$f(v)$ 即为 $f(u)$ 的每一项异或上 $w(u,v)$ 的和，即 $\large f(v)=\sum\limits_{i=1}^n dis(u,i)\oplus w(u,v)$。

考虑如何计算。

不难想到：用 $cnt$ 记录下 $f(u)$ 的每一项 $x$ 二进制下 $1$ 和 $0$ 的个数，按位枚举 $w(u,v)$，若其第 $i$ 位为 $1$，则 $x\oplus w(u,v)$ 后第 $i$ 位会与原来相反，所以此时交换 $cnt_{i,1}$ 和 $cnt_{i,0}$。

经过交换后，我们有 $\large f(v)=\sum\limits_{i=0}^{m-1}2^i\times cnt_{i,1}$。本题 $w\leq2^{60}$，故 $m=60$。

答案即为 $\large\frac {\sum\limits_{u=1}^nf(u)} 2$。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
#define mod 1000000007
int n,cnt[60][2],ans,mi[60]={1};
#define PII pair<int,int>
vector<PII>e[200010];
void dfs1(int u,int d,int fa)
{
	for(int i=59;i>=0;i--)	cnt[i][d>>i&1]++;
	for(auto i:e[u])
		if(i.first!=fa)	dfs1(i.first,d^i.second,u);
}
void dfs2(int u,int fa)
{
	for(int i=59;i>=0;i--)	ans=(ans+mi[i]*cnt[i][1]%mod)%mod;
	for(auto i:e[u])
	if(i.first!=fa)
	{
		for(int j=59;j>=0;j--)
			if(i.second>>j&1)
				swap(cnt[j][1],cnt[j][0]);
		dfs2(i.first,u);
		for(int j=59;j>=0;j--)
			if(i.second>>j&1)
				swap(cnt[j][1],cnt[j][0]);
	}
}
signed main()
{
	n=read();
	for(int i=1;i<60;i=-~i)	mi[i]=(mi[i-1]<<1)%mod;
	for(int i=1,u,v,w;i<n;i=-~i)
		u=read(),v=read(),w=read(),
		e[u].push_back({v,w}),e[v].push_back({u,w});
	dfs1(1,0,0);dfs2(1,0);
	return printf("%lld",ans*500000004/*显然这是2在mod 1e9+7下的逆元*/%mod),0;
}
```

---

## 作者：ast123 (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc201_e)

定义 $s[i]$ 为节点 $i$ 到根节点 $1$ 的路径上边权异或和，则 $u$ 与 $v$ 之间的路径的异或和为 $(s[u] \oplus s[lca(u,v)]) \oplus (s[v] \oplus s[lca(u,v)] = s[u] \oplus s[v]$，于是就转化为求 $\displaystyle \sum_{i=1}^{n} \sum_{j=i+1}^{n} s[i] \oplus s[j]$。

对于位运算，考虑拆位，可以求出每一二进制位 $1$ 的个数，假设为 $sum[i]$（$i$ 从 $1$ 开始，第 $i$ 位位权为 $2^{i-1}$），每一位贡献为位权 $\times$ 该位 $0$ 的数量 $\times$ 该位 $1$ 的数量，即 $2^{i-1} \times sum[i] \times (n-sum[i])$，累加起来就是答案。

[代码](https://www.luogu.com.cn/record/157614409)

---

## 作者：0zhouyq (赞：0)

### ABC201E 题解
[传送门](https://www.luogu.com.cn/problem/AT_abc201_e)

### 思路

首先想到对于任意三个点 $i$，$j$，$k$，有 $dis(i,j)=dis(k,i) \oplus dis(k,j)$。我们令这棵树的根是 $1$。那么，所求的东西相当于 $\sum_{i=1}^{n-1}\sum_{j=i+1}^n dis(1,i) \oplus dis(1,j)$。

考虑二进制拆位计算异或。我们二进制从低位往高位数。设 $sum_{i,j}$ 为从第 $i$ 个数到第 $n$ 个数中二进制第 $j$ 位为 $1$ 的数的个数。考虑第 $i$ 个数的贡献。如果它的第 $j$ 位是 $1$，那么只有其他数的这一位是 $0$ 才会产生贡献。容易得到第 $i+1$ 个数到第 $n$ 个数中一共有 $n-i-sum_{i+1,j}$ 个数这一位是 $0$。那么贡献就是 $2^{j-1} \times (n-i-sum_{i+1,j})$。同样的，若第 $i$ 个数第 $j$ 位是 $0$，则贡献为 $2^{j-1} \times sum_{i+1,j}$。累计即可。

实现的时候注意取模。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=1000000007;
ll sum[200010][70],dis[200010],mi[70],ans,MI[70];
vector<pair<ll,ll> > vc[200010];
void dfs(ll h,ll now,ll fa){
	dis[h]=now;
	for(ll i=0;i<vc[h].size();i++){
		ll t=vc[h][i].first;
		if(t!=fa) dfs(t,now^vc[h][i].second,h);
	}
}
int main(){
	mi[1]=1;
	for(ll i=2;i<=60;i++) mi[i]=mi[i-1]*2;
	ll n;
	scanf("%lld",&n);
	for(ll i=1;i<n;i++){
		ll x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		vc[x].push_back(make_pair(y,z));
		vc[y].push_back(make_pair(x,z));
	}
	dfs(1,0,-1);
	for(ll i=n;i;i--){
		for(ll j=1;j<=60;j++){
			sum[i][j]=sum[i+1][j];
			if((dis[i]&mi[j])!=0) sum[i][j]++;
		}
	}
	for(ll i=1;i<=60;i++) MI[i]=mi[i]%mod;
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=60;j++){
			if((dis[i]&mi[j])!=0) ans=(ans+MI[j]*((n-i)-sum[i+1][j])%mod)%mod;
			else ans=(ans+MI[j]*sum[i+1][j]%mod)%mod;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：cosf (赞：0)

我们假定一个根 $r$。

显然，由于异或的抵消规律，$dis(i, j) = dis(i, r) \oplus dis(j, r)$。于是，我们可以把所有点 $i$ 对应的 $dis(i, r)$ 算出来，题目就变成了这样：

> 给定一个长度为 $n$ 的数列 $d_1, d_2, \dots, d_n$，求它们两两异或得到的结果相加等于多少。

我们可以一位一位地算。对于一位，每一个数只能是 $0$ 或者 $1$。

假设这一位中 $1$ 的个数为 $s$，则 $0$ 的个数为 $n - s$。对于一个数，如果它是 $0$，则和它异或的有值的个数（即 $1$）的个数是 $s$。否则有 $n - 1 - (s - 1) = n - s$ 个。

综合起来就是 $(n - s)\times s + s \times (n - s) = 2s(n - s)$。因为题目给定要 $u_i < v_i$，所以还要除一个 $2$，即 $s(n - s)$。~~当然，这一步也可以暴力算，毕竟又优化不了复杂度。反正我就写的暴力~~

每一位算出的答案加起来即可。记得勤于取模，否则会挂得很惨。

## 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 300005ll
#define MOD 1000000007ll

using ll = long long;
using pll = pair<ll, ll>;

ll val[MAXN];

vector<pll> e[MAXN];

ll n;

void dfs(ll p, ll f)
{
    for (pll c : e[p])
    {
        if (c.first == f)
        {
            continue;
        }
        val[c.first] = val[p] ^ c.second;
        dfs(c.first, p);
    }
}

ll calc(ll k)
{
    ll s = 0;
    for (ll i = 1; i <= n; i++)
    {
        s += (val[i] >> k) & 1ll;
    }
    ll res = 0;
    for (ll i = 1; i <= n; i++)
    {
        if ((val[i] >> k) & 1ll)
        {
            res += n - s;
        }
        else
        {
            res += s;
        }
    }
    return (res >> 1ll) % MOD;
}

int main()
{
    cin >> n;
    for (ll i = 1; i < n; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }
    dfs(1, 0);
    ll res = 0;
    for (ll k = 61; ~k; k--)
    {
        res = (res + (1ll << k) % MOD * calc(k) % MOD) % MOD;
    }
    if (res >= MOD || res < 0)
    {
        return -1;
    }
    cout << res << endl;
    return 0;
}
```

---

## 作者：FreedomKing (赞：0)

[Atcoder Beginning Contest Virtual Participation 计划](https://www.luogu.com.cn/blog/FreedomKing/ABCVP)。

一道挺有意的异或和题。

### 思路

注：下文中的 $\oplus$ 为按位异或符号。

首先看到树上异或和肯定要第一时间想到 $d(root,x)\oplus d(root,y)=d(x,y)$ 的性质，这里 $d(x,y)$ 表示 $x,y$ 之间的唯一树上路径的边权的异或和。虽然题目描述的是无根树，但可以证明这里的 $root$ 可以由我们自由选定同时使式子依然成立。然后我们就先考虑选定一个根例如 $1$ 作为 $root$，然后预处理出 $d(1,i),(2\le i\le n)$，发现如果 $O(n^2)$ 的时间复杂度枚举两个点加和明显会超时。

考虑一个经典 trick 二进制贡献计算：我们对于第 $i((1\le i\le \log_2 V)(V={\max\{a_x\}(1\le x\le n)})$ 位二进制位，将 $d(1,x)(1\le x\le n)$ 分为两类，分别是二进制下第 $i$ 位为 $0,1$ 的两种，数量分别记为 $cnt_0,cnt_1$，然后我们考虑当且仅当 $0\oplus 1$ 时值才为 $1$，即产生贡献，所以只有将 $0$ 和 $1$ 两两组合时才需要计算贡献，贡献为 $0,1$ 数量相乘，即为 $cnt_0\times cnt_1$，然后再乘上其二进制下的权值 $2^i$ 即可。最终得出答案的式子如下：

$$\sum_{i=0}^{i\le \log_2 V} 2^i\times cnt_0\times cnt_1$$

最终时间复杂复 $O(n\log V)$。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,xN=1e7+5,mN=1e4+5,mod=1e9+7;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
namespace FreedomKing_qwq{
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){x/=gcd(x,y);return (x*y);}
	inline int max(int x,int y){return (x>y?x:y);}
	inline int min(int x,int y){return (x<y?x:y);}
	inline int abs(int x){return (x>0?x:-x);}
}
struct node{int v,w;};
vector<node>e[N];
int d[N],n,m,t,k;
inline void dfs(int x,int fa){
	for(int i=0;i<e[x].size();i++){
		int v=e[x][i].v,w=e[x][i].w;
		if(v!=fa){
			d[v]=d[x]^w;
			dfs(v,x);
		}
	}
	return;
}
signed main(){
	n=qr;
	for(int i=2;i<=n;i++){
		int u=qr,v=qr,w=qr;
		e[u].push_back({v,w});
		e[v].push_back({u,w});
	}
	dfs(1,0);
	int ans=0;
	for(int i=0;i<64;i++){
		int cnt0=0,cnt1=0;
		for(int j=1;j<=n;j++){
			if((d[j]>>i)&1) cnt0++;
			else cnt1++;
		}
		ans=(ans+((((1ll<<i)%mod)*cnt0%mod)*cnt1%mod))%mod;
	}
	qw(ans);
	return  0;
}
```

---

## 作者：lrqlrq250 (赞：0)

## 解题思路
我们要求的是无根树上任意两点之间的异或距离，不难发现钦定哪个节点为根对答案没有影响。因此不妨设 $1$ 为根。

首先对树进行一次遍历，求出所有的 $dis(1, i)$（$dis$ 的定义和题面相同）。

设 $k$ 为 $(i, j)$ 的 LCA，注意到 $dis(1, k) \oplus dis(1, k) = 0$，因此一定有：

$$dis(i, j) = dis(1, i) \oplus dis(1, j)$$

知道了所有的 $dis$ 后，我们考虑如何计算 $\sum\limits_{1\leq i<j\leq n} dis(1, i) \oplus dis(1, j)$。

对于两个数二进制下的每一位，只有 $0 \oplus 1 = 1$，此时在这一位上会对答案产生贡献。

因此我们统计 $p_i$ 为所有二进制下第 $i$ 位是 $1$ 的 $dis$ 数量，则 $n - p_i$ 就对应第 $i$ 位是 $0$ 的 $dis$ 数量，一个 $0$ 和一个 $1$ 可以在这一位上产生一次贡献，因此总答案为：
$$\sum_{i \ge 0} p_i \cdot(n - p_i) \cdot 2^i$$

遍历的时间复杂度为 $O(n + m)$，统计答案的时间复杂度为 $O(n \log w)$，在本题中 $\log w \leq 60$，可以通过。

## AC Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define mod 1000000007
using namespace std;
const int N = 200005;
struct Edge{int to, next; ll w;}e[N << 1];
int n, head[N], tot, p[65];
ll dis[N];
bool vis[N];

inline void addedge(int u, int v, ll w){
	e[++tot].to = v;
	e[tot].w = w;
	e[tot].next = head[u];
	head[u] = tot;
}

signed main(){
	scanf("%d", &n);
	int u, v;
	ll w;
	for (int i=1; i<n; i++){
		scanf("%d%d%lld", &u, &v, &w);
		addedge(u, v, w); addedge(v, u, w);
	}
	queue<int> q; q.push(1);
	dis[1] = 0; vis[1] = 1;
	while (!q.empty()){
		u = q.front(); q.pop();
		for (int i=head[u]; i; i=e[i].next) if (!vis[e[i].to]){
			v = e[i].to;
			dis[v] = dis[u] ^ e[i].w;
			vis[v] = 1;
			q.push(v);
		}
	}
	int len = 0, nowlen;
	for (int i=2; i<=n; i++){
		nowlen = 0;
		while (dis[i]){
			if (dis[i] & 1) p[nowlen]++;
			nowlen++;
			dis[i] >>= 1;
		}
		len = max(len, nowlen);
	}
	ll ans = 0;
	for (int i=0; i<len; i++) ans = (ans + (((1ll << i) % mod) * (1ll * p[i] * (n - p[i]) % mod) % mod)) % mod;
	printf("%lld\n", ans);
	return 0;
}

```



---

