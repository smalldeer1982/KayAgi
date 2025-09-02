# 「MXOI Round 1」城市

## 题目描述

小 C 是 F 国的总统，尽管这个国家仅存在于网络游戏中，但他确实是这个国家的总统。

F 国由 $n$ 个城市构成，这 $n$ 个城市之间由 $n-1$ 条双向道路互相连接。保证从任意一个城市出发，都能通过这 $n-1$ 条双向道路，到达任意一个城市。

当然，通过这些双向道路是要收费的。通过第 $i$ 条双向道路，需要花费 $c_i$ 元。我们称 $c_i$ 为第 $i$ 条双向道路的费用。

我们定义 $cost(x,y)$ 表示从城市 $x$ 到城市 $y$ 的简单路径上，所有经过的双向道路的费用之和。特殊地，当 $x=y$ 时，$cost(x,y)=0$。

为了促进 F 国发展，小 C 新建了一个城市 $n+1$。现在他需要再新建一条双向道路，使得城市 $n+1$ 也可以通过这 $n$ 条双向道路到达任意一个城市。

他共有 $q$ 个新建道路的方案，每个方案会给定两个参数 $k_i,w_i$；对于每一个方案，你需要求出在新建一条连接城市 $k_i$ 和城市 $n+1$ 且费用为 $w_i$ 的双向道路后，所有 $cost(i,j)$ 之和，即 $\sum\limits_{i=1}^{n+1} \sum\limits_{j=1}^{n+1} cost(i,j)$。

由于答案可能很大，所以你只需要输出答案对 $998244353$ 取模的结果。

**方案之间相互独立**，也就是说所有方案不会影响现有的道路，这些方案不会真正被施行。

## 说明/提示

#### 【样例解释 #1】

在新建一条连接城市 $1$ 和城市 $5$ 且费用为 $2$ 的双向道路后，F 国的道路如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/j871257i.png)

例如，此时 $cost(4,5)=9$，$cost(1,3)=5$。

容易求得此时 $\sum\limits_{i=1}^{n+1} \sum\limits_{j=1}^{n+1} cost(i,j)=100$。

#### 【样例 #3】

见附加文件中的 `city/city3.in` 与 `city/city3.ans`。

该样例满足测试点 $4$ 的限制。

#### 【样例 #4】

见附加文件中的 `city/city4.in` 与 `city/city4.ans`。

该样例满足测试点 $11$ 的限制。

#### 【样例 #5】

见附加文件中的 `city/city5.in` 与 `city/city5.ans`。

该样例满足测试点 $14$ 的限制。

#### 【样例 #6】

见附加文件中的 `city/city6.in` 与 `city/city6.ans`。

该样例满足测试点 $20$ 的限制。

#### 【数据范围】

对于 $100\%$ 的数据，$2 \le n \le 2\times10^5$，$1 \le q \le 2\times10^5$，$1 \le u_i,v_i,k_i \le n$，$1 \le c_i,w_i \le 10^6$，保证从任意一个城市出发，都能通过原本存在的 $n-1$ 条双向道路，到达任意一个城市。

|测试点编号|$n \le$|$q \le$|特殊性质|
|:---:|:---:|:---:|:---:|
|$1\sim3$|$80$|$80$|无|
|$4\sim7$|$5000$|$5000$|无|
|$8\sim10$|$5000$|$2\times10^5$|无|
|$11\sim13$|$2\times10^5$|$2\times10^5$|A|
|$14\sim16$|$2\times10^5$|$2\times10^5$|B|
|$17\sim20$|$2\times10^5$|$2\times10^5$|无|

特殊性质 A：保证对于所有的 $1 \le i \lt n$，都有 $u_i=i,v_i=i+1$。

特殊性质 B：保证对于所有的 $1 \le i \le q$，都有 $k_i=1$。

## 样例 #1

### 输入

```
4 2
2 1 3
3 2 2
4 2 4
1 2
2 2```

### 输出

```
100
88```

## 样例 #2

### 输入

```
9 5
2 3 6
6 1 4
5 2 10
2 4 1
9 1 9
2 8 3
1 2 3
7 4 8
4 9
7 3
6 1
9 7
2 1
```

### 输出

```
1050
1054
970
1148
896```

# 题解

## 作者：Coffee_zzz (赞：21)

### Task 1~3

每次暴力求解答案即可。

### Task 4~7

对于每个询问，我们考虑每条边对答案的贡献。

我们设某条边 $i$ 的一侧有 $p_i$ 个点，由于总点数是 $n+1$，所以这条边的另一侧就有 $n+1-p_i$ 个点。

那么这条边被经过的次数就是 $p_i \times (n+1-p_i) \times 2$，这条边的贡献就是 $p_i \times (n+1-p_i) \times 2 \times c_i$。

接下来我们思考如何 $O(1)$ 求每条边的贡献。

我们首先假定 $1$ 为根，对于每个点 $u$，处理出以 $u$ 为根的子树的大小 $siz_u$。

那么我们假设对于某条边 $i$，它连接的两个节点为 $u$ 和 $v$，其中 $u$ 是 $v$ 的父亲。

若新加入的点 $n+1$ 在以 $v$ 为根的子树内，则 $p_i=siz_v+1$，贡献就是 $(siz_v+1) \times (n-siz_v) \times 2 \times c_i$；

若新加入的点 $n+1$ 在以 $v$ 为根的子树外，则 $p_i=siz_v$，贡献就是 $siz_v \times (n+1-siz_v) \times 2 \times c_i$；

最后我们处理出每一条边的贡献，求和即为答案。单次询问的时间复杂度为 $O(n)$，总复杂度为 $O(nq)$。

### Task 8~10

我们对目标式子进行一下变换：

$$\sum\limits_{i=1}^{n+1} \sum\limits_{j=1}^{n+1} cost(i,j)=(\sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} cost(i,j))+2 \times\sum\limits_{i=1}^{n} cost(i,n+1)$$

对于新建的边 $n$，根据刚才得到的结论，容易发现它的贡献一定为 $n\times 2\times w$，那么目标式子又可以进一步化简：

$$
\begin{aligned}
\sum\limits_{i=1}^{n+1} \sum\limits_{j=1}^{n+1} cost(i,j)
&=(\sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} cost(i,j))+2 \times\sum\limits_{i=1}^{n} cost(i,n+1)\\
&=(\sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} cost(i,j))+2 \times (\sum\limits_{i=1}^{n} cost(i,k))+n\times 2\times w
\end{aligned}
$$

那么我们可以 $O(n^2)$ 预处理出 $k=1\sim n$ 时 $2 \times (\sum\limits_{i=1}^{n} cost(i,k))$ 的值，每次询问用对应的 $2 \times (\sum\limits_{i=1}^{n} cost(i,k))$ 加上 $(\sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} cost(i,j))+n\times 2\times w$ 即可，时间复杂度 $O(n^2+q)$。

### Task 11~13

容易发现，对于每一个询问，新建的 $n+1$ 号节点都在以 $2\sim k$ 为根的子树中。

我们假设对于某条边 $i$，它连接的两个节点为 $u$ 和 $v$，其中 $u$ 是 $v$ 的父亲，那么 $1\sim k-1$ 这些边的贡献都是 $(siz_v+1) \times (n-siz_v) \times 2 \times c_i$，$k \sim n-1$ 这些边的贡献都是 $siz_v \times (n+1-siz_v) \times 2 \times c_i$。

这个东西显然是可以前缀和预处理的，那么我们每次询问都可以利用前缀和去求这两部分的答案，最后加上 $n \times 2 \times w$ 即可，时间复杂度 $O(n+q)$。

### Task 14~16

由于保证了 $k=1$，所以我们可以用 Task 8~10 的方法，预处理出 $k=1$ 对应的 $2 \times (\sum\limits_{i=1}^{n} cost(i,k))$，每次询问对其加上 $(\sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} cost(i,j))+n\times 2\times w$ 即可，时间复杂度 $O(n+q)$。

### Task 17~20

显然的，对于每一个询问，$1$ 号节点到 $k$ 号节点的简单路径上经过的所有点的子树中都包含新加入的 $n+1$ 号节点。

我们假设对于某条边 $i$，它连接的两个节点为 $u$ 和 $v$，其中 $u$ 是 $v$ 的父亲，那么对于每一个询问，$1$ 号节点到 $k$ 号节点的简单路径上经过的所有边的贡献都是 $(siz_v+1) \times (n-siz_v) \times 2 \times c_i$，剩余边的贡献都是 $siz_v \times (n+1-siz_v) \times 2 \times c_i$。

那我们可以对每个节点 $u$，求出 $1$ 号节点到 $u$ 号节点的简单路径上经过的所有边的 $(siz_v+1) \times (n-siz_v) \times 2 \times c_i$ 之和，储存在 $f_v$，同时也求出所有边的 $siz_v \times (n+1-siz_v) \times 2 \times c_i$ 之和，储存在 $g_v$，记录一下所有 $n-1$  条边的 $siz_v \times (n+1-siz_v) \times 2 \times c_i$ 之和 $sum$，每次询问的答案即 $f_k+sum-g_k+n \times 2 \times w$。

预处理的复杂度为 $O(n)$，单次询问的复杂度为 $O(1)$，总复杂度 $O(n+q)$，可以通过。

### Code

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5,mod=998244353;
int n,q,to[N<<1],nxt[N<<1],c[N<<1],head[N],cnt,fa[N],siz[N];
ll f[N],g[N],sf[N],sg[N],sumg;
void add(int u,int v,int w){
	to[++cnt]=v;
	nxt[cnt]=head[u];
	c[cnt]=w;
	head[u]=cnt;
}
void init(int u,int fat){
	siz[u]=1,fa[u]=fat;
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa[u]) continue;
		init(v,u);
		siz[u]=siz[u]+siz[v];
	}
}
void dfs(int u){
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa[u]) continue;
		f[v]=1ll*(siz[v]+1)*(n-siz[v])%mod*c[i]*2%mod;
		g[v]=1ll*siz[v]*(n-siz[v]+1)%mod*c[i]*2%mod;
		sf[v]=(f[v]+sf[u])%mod;
		sg[v]=(g[v]+sg[u])%mod;
		sumg=(sumg+g[v])%mod;
		dfs(v);
	}
}
int main(){
	ios::sync_with_stdio(0);
	int u,v,k,w;
	ll ans1,ans2,ans3;
	cin>>n>>q;
	for(int i=1;i<n;i++) cin>>u>>v>>w,add(u,v,w),add(v,u,w);
	init(1,0);
	dfs(1);
	for(int tmp=0;tmp<q;tmp++){
		cin>>k>>w;
		ans1=sf[k];
		ans2=sumg-sg[k];
		ans3=2ll*n*w;
		cout<<(ans1+ans2+ans3+mod)%mod<<endl;
	}
	return 0;
}
```

---

## 作者：iiiiiyang (赞：18)

[原神的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17659885.html)

[题目链接](https://www.luogu.com.cn/problem/P9584)

你说得对，但是不如换根。换根是由原先的树形 DP 简单变换而来，故事发生在这道叫做《城市》的题目中，在这里你妄图求解每个点到树中其它所有节点的距离，即 $f_i = \sum_{j = 1}^n dis_{i \to j}$。可以一次 dfs 求解出 $f_{root}$，然后我们发现走过一条边 $(u,v,w)$ 会使得 $siz_v$ 个节点减少 $w$ 的距离，$n - siz_v$ 个点增加 $w$ 的距离，于是你就得到了 $f_v = f_u + w \times (n - 2 \times siz_v)$，再做一次 dfs 即可。对于每个询问的答案显然为 $\sum_{i = 1}^n f_i + 2 \times (f_k + n \times w)$。这样我们代码比标程短 114514 倍，还更好想好写。同时效率上 std 跑一遍我的代码能够跑三遍，超越了绝大多数程序（包括你）的水平，这就是换根给我骄傲的资本。

```cpp
namespace LgxTpre
{
    static const int MAX=200010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    
    int n,q,dis[MAX],siz[MAX],f[MAX],ans;
    int x,y,z,k,w;
    vector<pii> G[MAX];
	
    inline void lmy_forever()
    {
    	read(n,q);
    	for(int i=1;i<n;++i) read(x,y,z),G[x].eb(mp(y,z)),G[y].eb(mp(x,z));
    	
    	auto dfs1=[&](auto dfs1,int now,int father)->void
    	{
    		siz[now]=1;
    		for(auto [to,val]:G[now]) if(to!=father) dis[to]=Cadd(dis[now],val),dfs1(dfs1,to,now),siz[now]+=siz[to],Madd(f[1],dis[to]);
		};
		dfs1(dfs1,1,0);
		
		auto dfs2=[&](auto dfs2,int now,int father)->void
		{
			Madd(ans,f[now]);
			for(auto [to,val]:G[now]) if(to!=father) f[to]=Cadd(f[now],Cmul(val,((siz[1]-2*siz[to])%Mod+Mod)%Mod)),dfs2(dfs2,to,now);
		};
		dfs2(dfs2,1,0);
		
		for(int i=1;i<=q;++i) read(k,w),write(Cadd(ans,Cmul(Cadd(f[k],Cmul(n,w)),2ll)),'\n');
    }
}
```

---

## 作者：Night_sea_64 (赞：7)

**Ns6 在赛时因为没有考虑取模再相减变负数的问题，痛失 40pts，离 AK 仅差一步之遥，警钟长鸣。**

题目名称简直可以改成“P9584【模板】换根 dp”。真的十分板子。

------------

#### 换根 dp 的过程如下：

先随便选一个根（我就用 $1$ 号点），先用一遍 dfs 预处理出每个点及其子树，点的个数 $sz$ 和到当前点的距离和 $d$。

再用一遍 dfs 将每个点的 $d$ 改成所有点到当前点的距离和。以样例 1 的图为例。注意此时 $5$ 号点还不存在。

![](https://cdn.luogu.com.cn/upload/image_hosting/j871257i.png)

$1$ 号点及其子树到它的距离和为 $3+(3+2)+(3+4)=15$。此时需要用它来转移到 $2$ 号点。以下是转移方法（$w_{x,y}$ 表示 $x\Leftrightarrow y$ 的边权）。

原先的数据，$2,3,4$ 都跑到 $1$。现在这三个点都只跑到 $2$，那么 $2$ 的子树其实占了便宜，因为它们少跑了 $1\Leftrightarrow2$ 那条边，总距离就减去 $3\times3=9$，即 $sz_2\times w_{1,2}$。但是除 $2$ 的子树之外的其它点都多走了 $1\Leftrightarrow2$ 的边，总距离加上了 $(4-3)\times3=3$，即 $(n-sz_2)\times w_{1,2}$。

以上两项合并，总距离加上 $(n-2\times sz_2)\times w_{1,2}$。

总的来说，换根 dp 的思想就是，先一遍 dfs 预处理出每个点及其子树的信息（其实就是先来一遍普通的树形 dp）。再来一遍 dfs，利用已经修改完成的父亲结点（根结点在第一个 dfs 的时候就处理完了，不用再改），把点及其子树的信息改成所有点到它的信息，这也是最难的部分。

------------

回到本题，换根 dp 先求出前 $n$ 个点的答案，记为 $sum$。$n+1$ 连到 $x$ 点上的时候，就加上所有点到 $x$ 的距离再多加一个 $w_{x,n+1}$ 再乘 $2$ 即可（因为是双向的，题目中的式子，双向要统计两遍）。即 $sum+d_x\times2+n\times w_{x,n+1}\times2$。

```cpp
#include<iostream>
#include<vector>
#define int long long
using namespace std;
int n,q,d[200010],sz[200010],sum;
struct edge{int x,w;};
vector<edge>v[200010];
const int mod=998244353;
void dfs1(int x,int last)
{
    sz[x]=1;
    for(auto e:v[x])
        if(e.x!=last)
        {
            dfs1(e.x,x);
            d[x]=(d[x]+d[e.x]+sz[e.x]*e.w)%mod,sz[x]+=sz[e.x];
        }
}
void dfs2(int x,int last)
{
    for(auto e:v[x])
        if(e.x!=last)
        {
            d[e.x]=(d[x]+mod*10000+e.w*(n-2*sz[e.x]))%mod;//为什么 +mod*10000？看这篇文章的第一句话！！！
            dfs2(e.x,x);
        }
}
signed main()
{
    cin>>n>>q;
    for(int i=1;i<n;i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        v[x].push_back({y,w});
        v[y].push_back({x,w});
    }
    dfs1(1,0);
    dfs2(1,0);
    for(int i=1;i<=n;i++)sum=(sum+d[i])%mod;
    while(q--)
    {
        int x,w;
        cin>>x>>w;
        cout<<(sum+d[x]*2+n*w*2)%mod<<endl;
    }
    return 0;
}
```

---

## 作者：Wf_yjqd (赞：7)

非常基础的树上 dp 板子。

------------

考虑预处理 $\sum\limits_{i=1}^n\sum\limits_{j=1}^n cost_{i,j}$，然后对于每次询问求 $\sum\limits_{i=1}^ncost_{n+1,i}\times2$，二者和为答案。

显然可以维护 $sz_i$ 表示以 $i$ 为根的子树大小。

然后我们将每个点贡献的代价分为子树中的和其他的，方便树上维护。

考虑维护 $f_i$ 表示 $i$ 到所有其子树中所有点的代价之和，则有 $f_i=\sum\limits_{j\in son_i}{f_j+sz_j\times val_{i,j}}$，其中 $val_{i,j}$ 表示 $i$ 和 $j$ 之间边长。

其实就是每个点都多增加 $i$ 到 $j$ 这条边的边权。

然后再求 $g_i$ 表示 $i$ 到除了他的子树外所有节点的代价之和，$g_i=g_{fa}+f_{fa}-f_i-sz_i\times val_{fa,i}+(n-sz_i)\times val_{fa,i}$，其中 $fa$ 为 $i$ 的父亲节点。

本质为 $fa$ 到 $i$ 的子树以外所有节点的代价和，然后每个点代价加上 $val_{fa,i}$。

注意根节点的 $g_1$ 为 $0$。

求出 $\sum\limits_{i=1}^n{f_i+g_i}$，每次询问再加上两倍的 $n\times w+f_k+g_k$，即父亲到所有点的代价和加上每条路增加一条长度为 $w$ 的边。

复杂度 $\operatorname{O}(n)$。

------------

真的很板好吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=2e5+84,maxm=4e5+84,mod=998244353;
namespace Sherry_fastinout{
    inline ll read(){
        ll x=0,f=1;
        char c=getchar();
        while(c<'0'||c>'9'){
            if(c=='-')
                f=-1;
            c=getchar();
        }
        while(c>='0'&&c<='9'){
            x=x*10+c-'0';
            c=getchar();
        }
        return x*f;
    }
    inline void write(ll x){
        if(x<0){
            x=-x;
            putchar('-');
        }
        if(x>9)
            write(x/10);
        putchar(x%10+'0');
        return ;
    }
}
using namespace Sherry_fastinout;
ll n,q,x,y,z,k,w,ans,f[maxn],g[maxn],sz[maxn];//哀太可爱辣
namespace Sherry_Graph{
    struct Edge{
        ll to,ne,val;
    }e[maxm];
    ll ecnt=1,head[maxn];
    inline void add(ll u,ll v,ll w){
        e[ecnt]={v,head[u],w};
        head[u]=ecnt++;
        return ;
    }
}
using namespace Sherry_Graph;
inline void dfsf(ll x,ll fa){
    sz[x]=1;
    for(ll i=head[x];i;i=e[i].ne){
        if(e[i].to==fa)
            continue;
        dfsf(e[i].to,x);
        sz[x]+=sz[e[i].to];
        f[x]=(f[x]+(f[e[i].to]+sz[e[i].to]*e[i].val%mod)%mod)%mod;
    }
    return ;
}
inline void dfsg(ll x,ll fa,ll enumm){
    if(enumm<0)
        g[x]=0;
    else
        g[x]=((((g[fa]+f[fa])%mod-f[x]+mod)%mod-sz[x]*e[enumm].val%mod+mod)%mod+(n-sz[x])*e[enumm].val%mod)%mod;
    for(ll i=head[x];i;i=e[i].ne)
        if(e[i].to!=fa)
            dfsg(e[i].to,x,i);
    return ;
}
int main(){
    n=read();
    q=read();
    for(ll i=1;i<n;i++){
        x=read();
        y=read();
        z=read();
        add(x,y,z);
        add(y,x,z);
    }
    dfsf(1,0);
    dfsg(1,0,-168);
    for(ll i=1;i<=n;i++)
        ans=((ans+f[i])%mod+g[i])%mod;
    while(q--){
        k=read();
        w=read();
        write((ans+((n*w%mod+f[k])%mod+g[k])%mod*2%mod)%mod);
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：shinzanmono (赞：6)

以下默认树的根为 $1$。

定义 $f_u$ 表示 $u$ 到子树内所有点的距离和，$g_u$ 表示 $u$ 到子树外所有点的距离和，$s_u$ 表示 $u$ 的子树大小。

很显然对于每个询问，答案为 $\sum_{u=1}^n(f_u+g_u)+2(s_1\cdot w+f_k+g_k)$。

状态转移方程：

$$
\begin{aligned}
&f_u=\sum_{v\in son_u}(f_v+w_{u\rightarrow v}s_v)\\
&g_u=g_{fa_u}+\sum_{v\in brother_u}(f_v+w_{fa_u\rightarrow v}s_v)+w_{fa_u\rightarrow u}(n-s_u)
\end{aligned}
$$

其中 $w_{u\rightarrow v}$ 表示 $u$ 到 $v$ 的边权。

但是求 $g_u$ 的过程是 $O(n^2)$ 的，我们需要优化。

对于 $u$ 的子节点 $v$，我们可以求出在 $v$ 前面和后面被扫到的同级结点的 $f_v+w_{fa_u\rightarrow v}s_v$ 的和 $pre_v$ 和 $suf_v$，于是，我们可以得到优化后的状态转移方程：

$$
g_u=g_{fa_u}+pre_u+suf_u+w_{fa_u\rightarrow u}(n-s_u)
$$

这样做的时间复杂度是 $O(n)$ 的，然后你就可以通过此题。

---

## 作者：Phartial (赞：4)

首先我们可以将要求的答案化作 $\displaystyle\left(\sum_{i=1}^n\sum_{j=1}^n\operatorname{cost}(i,j)\right)+2\sum_{i=1}^n\operatorname{cost}(i,n+1)$。

对于前半部分，我们可以单独考虑每条边对其的贡献。对于边 $e=(x,y,w)$，其将树划分成两个部分，一部分以 $x$ 为根，一部分以 $y$ 为根，显然这两个部分想要互达就必须要经过边 $e$，于是算出两部分的大小后相乘再乘二（因为一对点需要计算两次）就是边 $e$ 被经过的次数。

令 $1$ 为根，记以 $x$ 为根的子树大小为 $s_x$，父亲为 $f_x$，则边 $(x,f_x,w)$ 被经过的次数就是 $2s_x(n-s_x)$，贡献为 $2s_x(n-s_x)w$。

对于后半部分，再次考虑拆贡献，那么只需要计算每条边新增的贡献即可。新增的边 $(k_i,n+1,w_i)$ 的贡献为简单的 $2nw_i$，因为节点 $n+1$ 到其他点必须要经过此边，反之亦然。

对于其他边，不妨设 $g_x$ 为“在以 $x$ 为根的子树中，新增边 $(x,n+1,w)$ 后，子树中其他边的新增贡献”。考虑 $x$ 的每个儿子 $i$，在以 $i$ 为根的子树中，每条边的新增贡献不变，总贡献仍为 $g_i$；而对于边 $(x,i,v)$，由于 $n+1$ 位于 $x$ 一侧，所以新增的被经过的次数为 $i$ 一侧的大小乘二，即 $2s_i$，新增贡献为 $2s_iv$。

于是可以得到状态转移方程：

$$
g_x=\sum_{(x,i,v)\in\mathrm{edge}_x}g_i+2s_iv
$$

（$\mathrm{edge}_x$ 中不包括新增的边 $(x,n+1,w)$）

再记 $h_x$ 为“新增边 $(x,n+1,w)$ 后，整棵树中其他边的新增贡献”，显然有 $h_1=g_1$，因为以 $1$ 为根的子树就是原树。

对于 $h_x$，考虑其父节点的新增贡献 $h_{f_x}$，当前节点与父节点的新增贡献的唯一不同处在于边 $(x,f_x,v)$：在 $h_{f_x}$ 中，由于 $n+1$ 在 $f_x$ 一侧，它的新增贡献为 $2s_xv$；但在 $h_x$ 中，由于 $n+1$ 在 $x$ 一侧，所以它的新增贡献为 $2(n-s_x)v$。将此差值补上即可。

于是有状态转移方程：

$$
h_x=h_{f_x}+2(n-2s_x)v
$$

那么在新增边 $(k_i,n+1,w_i)$ 后，我们就可以简单的得到后半部分的值：$h_{k_i}+2nw_i$，加上前半部分的值即可得到最终答案。

```cpp
#include <iostream>
#include <vector>

using namespace std;
using LL = long long;
using Pil = pair<int, LL>;

const int kN = 2e5 + 1;
const LL kM = 998244353;

int n, q, s[kN];
vector<Pil> e[kN];
LL h[kN], g[kN], ans;

void D(int x, int f, LL w) {
  s[x] = 1;
  for (auto [i, v] : e[x]) {
    if (i != f) {
      D(i, x, v);
      s[x] += s[i], g[x] = (g[x] + g[i] + v * s[i] % kM) % kM;
    }
  }
  ans = (ans + w * s[x] % kM * (n - s[x]) % kM) % kM;
}
void S(int x, int f, LL w) {
  h[x] = (h[f] + w * (n - 2 * s[x]) % kM + kM) % kM;
  for (auto [i, v] : e[x]) {
    if (i != f) {
      S(i, x, v);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> q;
  for (int i = 1, x, y, w; i < n; ++i) {
    cin >> x >> y >> w;
    e[x].emplace_back(y, w), e[y].emplace_back(x, w);
  }
  D(1, 0, 0), h[0] = g[1], S(1, 0, 0);
  for (int x, v; q--;) {
    cin >> x >> v;
    cout << (ans + h[x] + 1LL * v * n % kM) * 2 % kM << '\n';
  }
  return 0;
}
```


---

## 作者：zct_sky (赞：2)

### Solution
-----
~~考场上这个蒟蒻跑了三遍 dfs。~~

$n$ 个点由 $n-1$ 条边联通，显然，这是一棵树。

先对不连 $n+1$ 这个节点的原树进行计算。

考虑对每一条边的贡献分别计算，若第 $i$ 条边是由父节点 $u$ 连到子节点 $v$，则由于乘法原理，该边被算了 $siz_v\times (n-siz_v)$ 次（$siz_v$ 表示 $v$ 及该节点子树的总大小），总贡献为 $2\times siz_v\times (n-siz_v)\times c_i$（$\times 2$ 是因为会被算 $cost(i,j)$ 和 $cost(j,i)$ 这两次）。

然后考虑加上第 $n+1$ 个节点后对总贡献会产生什么影响。

比如样例 $2$ 的第一个方案：

![](https://cdn.luogu.com.cn/upload/image_hosting/75udrjyt.png)

显然，对于图中加粗的节点，他们的 $siz$ 多了 $1$，而对于其他节点，他们的 $n-siz$ 多了 $1$。

容易发现，对于第 $n+1$ 个点连接的点至根节点 $1$ 的路径上皆为加粗的节点。

因此，我们可以通过三次 dfs 来解决：

第一次 dfs：预处理出 $siz$ 数组。

第二次 dfs：将每一条边的贡献按照 $2\times siz_v\times {\color{red}{(n-siz_v+1)}}\times c_i$ 计算，并预处理 $sum$ 数组（$sum_u=\sum\limits sum_{sub_u}+2\times siz_{sub_u}\times {(n-siz_{sub_u}+1)}\times c_i$，即 $sum_u$ 表示 $u$ 的子树的边贡献和）。

第三次 dfs：预处理出每个节点与 $n+1$ 连边的总贡献值（除了连的那条边外），记为 $init$ 数组。方法：遍历每个子节点，将原来的以 $2\times siz_v\times {\color{red}{(n-siz_v+1)}}\times c_i$ 计算贡献，改成将根节点至子节点的路径上以 $2\times {\color{red}{(siz_v+1)}}\times {(n-siz_v)}\times c_i$ 计算贡献，下传一个参数 $tmp$，$tmp_v=tmp_u+sum_u-sum_v-2\times siz_v\times {\color{red}{(n-siz_v+1)}}\times c_i + 2\times {\color{red}{(siz_v+1)}}\times {(n-siz_v)}\times c_i$（$u$ 为父节点，$v$ 为子节点），最后 $init_v=sum_v+tmp_v$。

最后对于新联的边，按照 $2\times siz_{n+1}\times {(n-siz_{n+1})}\times w_i$ 计算贡献即可（其实就是 $2\times n \times w_i$）。

还要注意开 `long long` 与取模的一些细节即可。
### Code
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return x*y;

}
const int N=2e5+7;
const int mod=998244353;
ll siz[N],sum[N],init[N];
int nxt[N<<1],head[N],tot,to[N<<1],val[N<<1];
int n,q;
void add(int u,int v,int w){
	nxt[++tot]=head[u];
	head[u]=tot;
	to[tot]=v;
	val[tot]=w;
}
void dfs1(int u,int fa){
	siz[u]=1;
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
	}
}
void dfs2(int u,int fa){
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa)continue;
		sum[u]+=2ll*val[i]*(n-siz[v]+1)%mod*(siz[v])%mod;
		sum[u]%=mod;
		dfs2(v,u);
		sum[u]+=sum[v];
		sum[u]%=mod;
	}
}
void dfs3(int u,int fa,ll s){
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa)continue;
		ll tmp=(s+sum[u])%mod;
		tmp=(tmp-2ll*val[i]*(n-siz[v]+1)%mod*(siz[v])%mod+mod)%mod;
		tmp=(tmp-sum[v]+mod)%mod;
		tmp%=mod;
		tmp+=2ll*val[i]*(n-siz[v])%mod*(siz[v]+1)%mod;
		tmp%=mod;
		dfs3(v,u,tmp);
	}
	init[u]=sum[u]+s;
	init[u]%=mod;
}
int main(){
	n=read();
	q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w);
		add(v,u,w);
	}
	dfs1(1,0);
	dfs2(1,0);
	dfs3(1,0,0);
	for(int i=1;i<=q;i++){
		int k=read(),c=read();
		ll answer=(init[k]+2ll*c*n%mod)%mod;
		printf("%lld\n",answer);
	}
	return 0;
}
```

---

## 作者：MornStar (赞：2)

# P9584 城市题解
## 题目大意
给你一棵 $n$ 个点的无根树，编号为 $1$ 到 $n$，令 $dis(i,j)$ 为树上点 $i$ 到点 $j$ 所经过的路径长度。

$q$ 次询问，每次询问加入一个编号为 $n+1$ 的点并与 $x$ 连接一条长度为 $w$ 的边。

求：
$$
\sum_{i=1}^{n+1}\sum_{j=1}^{n+1}dis(i,j)
$$
## 思路

回到式子，提出一部分来，原式则为：
$$
\sum_{i=1}^{n}\sum_{j=1}^{n}dis(i,j)+\sum_{i=1}^{n}dis(i,n+1)+\sum_{i=1}^{n}dis(n+1,i)
$$

其中 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}dis(i,j)$ 的值是不变化的，预处理一次就行。

剩下的部分就等于 $2\times \sum\limits_{i=1}^{n}dis(n+1,i)$

先看 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}dis(i,j)$。

考虑先把 $\sum\limits_{i=1}^{n}dis(i,1)$ 求出来，然后换根，注意到跟从 $a$ 换到 $b$ 时，到 $b$ 的子树的节点的距离都减少了 $a$ 到 $b$ 这条边的边权，反之，其余节点都加上了这个边权，
于是，换根的公式呼之欲出：
$$

\sum_{i=1}^{n}dis(i,b)=\sum_{i=1}^{n}dis(i,a)+(n-\operatorname{siz}_b\times 2)\times dis(a,b)

$$
加起来就是了。

其中， $a$ 和 $b$ 之间要有边连接。

再来看 $\sum\limits_{i=1}^{n}dis(n+1,i)$。

因为其只有一条连接着 $x$ 的边，所以可以把它拆开：$\sum\limits_{i=1}^{n}dis(n+1,x)+\sum\limits_{i=1}^{n}dis(i,x)$

前面一部分就等于 $n\times w$（$w$ 是边权），后面也在换根时处理过了，所以我们就可以在 $O(1)$ 时间内回答每次询问了。

## code
```cpp
//by MornStar
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
struct edge{
	int to,v;
};
long long n,q,siz[200005],dissum[200005],ans;
vector<edge>e[200005];
void dfs1(int now,int fa,long long dis){
	siz[now]=1;
	dissum[1]=(dissum[1]+dis)%mod;
	for(int i=0;i<e[now].size();i++){
		int to=e[now][i].to,v=e[now][i].v;
		if(to!=fa){
			dfs1(to,now,(dis+v)%mod);
			siz[now]+=siz[to];
		}
	}
}
void dfs2(int now,int fa){
	ans=(ans+dissum[now])%mod;
	for(int i=0;i<e[now].size();i++){
		int to=e[now][i].to,v=e[now][i].v;
		if(to!=fa){
			dissum[to]=((dissum[now]+(n-siz[to]*2)*v%mod)+mod)%mod;
			dfs2(to,now);
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>q;
	for(int i=1,u,v,w;i<n;i++){
		cin>>u>>v>>w;
		e[u].push_back({v,w});
		e[v].push_back({u,w});
	}
	dfs1(1,-1,0);
	dfs2(1,-1);
	for(int i=1,x,w;i<=q;i++){
		cin>>x>>w;
		cout<<(ans+(dissum[x]+w*n%mod)*2ll%mod)%mod<<"\n";
	}
}
```




---

## 作者：Argvchs (赞：2)

## 1. 题意

给出一棵 $n$ 个点的树，边有边权，每次询问添加一个点 $n + 1$ 和一条边 $(u, n + 1)$ 后任意两点之间的距离和。

## 2. 题解

考虑一条边对答案的贡献，即为通过这条边的路径数 $\times$ 边权。

为了方便计算，我们将边的贡献转为点的贡献：设 $a_u$ 表示 $u$ 到父亲的边权，$f_u$ 表示子树大小，$g_u = n - f_u$ 表示子树外大小，则点 $u$ 的贡献为 $a_u \cdot f_u \cdot g_u$。

然后考虑加了一条边 $(u, n + 1)$ 之后怎么算，不妨设 $u$ 是 $n + 1$ 的父亲。于是 $u$ 到根路径上每个点的**子树大小**都要 $+1$，其余点的**子树外大小**都要 $+1$，另外答案还要加上新边的贡献。

这样对于每个询问暴力加边计算是 $O(nm)$ 的，但其实可以直接预处理。发现新边的贡献比较好算，即 $n \cdot w$，于是考虑预处理每个点**除去新边的贡献**的答案。

我们先 DFS 预处理出每个点的 $a_u$、$f_u$、$g_u$，另外因为加了一个点所以预处理子树外大小时 $g_u = n + 1 - f_u$。

然后我们再 DFS 一遍求出每个点的答案，当遍历到一个点 $u$ 时 $f_u \gets f_u + 1$，$g_u \gets g_u - 1$，同时更新当前答案，回溯时再改回来即可。

最后处理询问的时候，将预处理的答案加上新边贡献即可，然后还要 $\times 2$ 因为每条路径要算两次。

时间复杂度 $O(n + m)$。

## 3. Code

```cpp
#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;
const int N = 2e5 + 5, P = 998244353;
int n, m, a[N], f[N], g[N], ans[N], cur;
vector<pair<int, int>> G[N];
void dfs1(int u, int fa) {
    f[u] = 1;
    for (auto [v, w] : G[u])
        if (v != fa) a[v] = w, dfs1(v, u), f[u] += f[v];
    g[u] = n + 1 - f[u];
    cur = (cur + (i64)a[u] * f[u] * g[u]) % P;
}
void dfs2(int u, int fa) {
    cur = (cur - (i64)a[u] * f[u] * g[u] + P) % P;
    ++f[u], --g[u];
    cur = (cur + (i64)a[u] * f[u] * g[u]) % P;
    ans[u] = cur;
    for (auto [v, w] : G[u])
        if (v != fa) dfs2(v, u);
    cur = (cur - (i64)a[u] * f[u] * g[u] + P) % P;
    --f[u], ++g[u];
    cur = (cur + (i64)a[u] * f[u] * g[u]) % P;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= n - 1; i++) {
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 1, u, w; i <= m; i++) {
        cin >> u >> w;
        cout << (ans[u] + (i64)n * w) * 2 % P << '\n';
    }
    return 0;
}
```

---

## 作者：igAC (赞：2)

# $\text{Description}$

[link](https://www.luogu.com.cn/problem/P9584)

# $\text{Solution}$

首先拆式子：

$$
\sum_{i=1}^{n+1}\sum_{j=1}^{n+1}cost(i,j)=\sum_{i=1}^{n}\sum_{j=1}^{n}cost(i,j)+2\sum_{i=1}^{n}cost(i,n+1)
$$

发现前两个 $\sum$ 是不变的，也就是对于每次询问只需求出后面的一个 $\sum$。

首先考虑前面的两个 $\sum$ 如何求。

设 $dis_x$ 表示 $x$ 节点到根的距离，$f_x$ 表示 $x$ 节点到其他节点的距离，$Size_x$ 表示 $x$ 的子树大小。

那么 $\sum_{i=1}^{n}\sum_{j=1}^{n}cost(i,j)=\sum_{i=1}^{n}f_i$。

我们令 $1$ 号节点为根节点，那么 $f_1=\sum_{i=1}^{n}dis_i$。

接下来思考如何进行转移:

考虑从根节点向下遍历时的发生的变化。

![](https://cdn.luogu.com.cn/upload/image_hosting/j871257i.png)

对于上例，从 $1$ 节点到 $2$ 节点，离 $2,3,4$ 节点都近了 $3$，离 $1,5$ 远了 $3$。

即：从 $fa_x$ 走到 $x$ 时，离 $x$ 子树中的节点都进了 $cost(fa_x,x)$，而离其他节点都远了 $cost(fa_x,x)$。

那么很容易推出转移：

$$
f_{x}=f_{fa_x}-Size_x \times cost(fa_x,x)+(n-Size_x) \times cost(fa_x,x)
$$

如此就把前面两个 $\sum$ 求出来了。

现在考虑每次询问，设 $n+1$ 节点连接 $x$ 号节点，我们发现 $n+1$ 号节点到 $y$ 号节点（$y \in [1,n]$）的距离都是 $cost(x,y)+cost(x,n+1)$。

以下令 $k=cost(x,n+1)$。

那么：

$$
2\sum_{i=1}^{n}cost(i,n+1)=2\sum_{i=1}^{n}(cost(i,x)+k)=2(\sum_{i=1}^{n}cost(i,x)+n \times k)
$$

由 $f_x$ 的定义知：$\sum_{i=1}^{n}cost(i,x)=f_x$。

所以：

$$
2\sum_{i=1}^{n}cost(i,n+1)=2(f_x+n \times k)
$$

整个算法的时间复杂度为 $O(n+q)$。

# $\text{Code}$

赛时代码（略改）：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
#define Mod 998244353
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,q,dis[N],ans;
int Size[N],f[N];
int head[N],tot;
struct Edge{
	int to,nxt;
	int val;
}e[N<<1];
void add_edge(int x,int y,int z){
	e[++tot].to=y;
	e[tot].val=z;
	e[tot].nxt=head[x];
	head[x]=tot;
}
void dfs1(int x,int f,int pre){
	dis[x]=(dis[f]+pre)%Mod;
	Size[x]=1;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to,z=e[i].val;
		if(y==f) continue;
		dfs1(y,x,z);
		Size[x]+=Size[y];
	}
}
void dfs2(int x,int fa,int pre){
	f[x]=(f[fa]-(Size[x]*pre)%Mod+Mod+((n-Size[x])*pre)%Mod)%Mod;
	ans=(ans+f[x])%Mod;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to,z=e[i].val;
		if(y==fa) continue;
		dfs2(y,x,z);
	}
}
signed main(){
	n=read(),q=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read(),z=read();
		add_edge(x,y,z);
		add_edge(y,x,z);
	}
	dfs1(1,0,0);
	for(int i=2;i<=n;++i) f[0]=(f[0]+dis[i])%Mod;
	dfs2(1,0,0);
	while(q--){
		int x=read(),d=read();
		printf("%lld\n",(ans+2*(f[x]+n*d%Mod)%Mod)%Mod);
	}
	return 0;
}
```

---

## 作者：Claire0918 (赞：1)

考虑对于每一个 $i$ 预处理 $\displaystyle \sum_{j = 1}^{n} \operatorname{cost}(i, j)$，可以用换根 DP 求解。

令 $f_i = \displaystyle \sum_{j = 1}^{n} \operatorname{cost}(i, j)$，$size_u$ 为以 $u$ 为根的子树大小。

先一次 DFS 求出 $f_1$，转移方程为 $\displaystyle f_u = \sum_{v \in son(u)} f_v + size_v \times w$。

```cpp
inline void dfs1(int u, int fa){
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].nex){
        const int v = edge[i].v;
        const long long w = edge[i].w;
        if (v != fa){
            dfs1(v, u);
            size[u] += size[v];
            f[u] = (f[u] + (f[v] + size[v] * w % mod) % mod) % mod;
        }
    }
}
```

然后再一次 DFS 求出剩余的 $f_i$。

假设现在已经知道了 $f_u$，要求得 $f_v, v \in son(u)$。

先令 $u$ 为树的根。

若树根从 $u$ 沿 $u$ 和 $v$ 之间的连边转移到 $v$，则会有 $size_v$ 个点离根的距离减少 $w$，$n - size_v$ 个点离根的距离增加 $w$。

因此转移方程为 $f_v = f_u + (n - size_v \times 2) * w$。

```cpp
inline void dfs2(int u, int fa){
    for (int i = head[u]; i; i = edge[i].nex){
        const int v = edge[i].v;
        const long long w = edge[i].w;
        if (v != fa){
            f[v] = (f[u] + w * (n - (size[v] << 1)) % mod + mod) % mod;
            dfs2(v, u);
        }
    }
}
```

预处理时间复杂度 $\mathcal{O}(n)$。

现在设 $\displaystyle sum = \sum_{i = 1}^{n} \sum_{j = 1}^{n} \operatorname{cost}(i, j) = \sum_{i = 1}^{n} f_i$。

每一次加一条连接 $n + 1$ 的边，所有点到 $n + 1$ 的距离之和即为 $f_k + n \times w$，由于还要反着算一遍，还要乘 $2$。

故得每一次查询的结果为 $sum + 2(f_k + n \times w)$。

每一次查询 $\mathcal{O}(1)$ 处理，总时间复杂度 $\mathcal{O}(n + q)$。

```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 2e5 + 10, maxm = 2e5 + 10, mod = 998244353;

struct{
    int v, nex;
    long long w;
} edge[maxm << 1];

int n, q;
int size[maxn];
long long f[maxn];
int head[maxn], top = 0;

inline void add(int u, int v, long long w){
    edge[++top].v = v;
    edge[top].w = w;
    edge[top].nex = head[u];
    head[u] = top;
}

inline void dfs1(int u, int fa){
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].nex){
        const int v = edge[i].v;
        const long long w = edge[i].w;
        if (v != fa){
            dfs1(v, u);
            size[u] += size[v];
            f[u] = (f[u] + (f[v] + size[v] * w % mod) % mod) % mod;
        }
    }
}

inline void dfs2(int u, int fa){
    for (int i = head[u]; i; i = edge[i].nex){
        const int v = edge[i].v;
        const long long w = edge[i].w;
        if (v != fa){
            f[v] = (f[u] + w * (n - (size[v] << 1)) % mod + mod) % mod;
            dfs2(v, u);
        }
    }
}

int main(){
    scanf("%d %d", &n, &q);
    for (int i = 1; i < n; i++){
        int u, v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    long long sum = 0;
    for (int i = 1; i <= n; i++){
        sum += f[i];
        sum %= mod;
    }
    while (q--){
        int k;
        long long w;
        scanf("%d %lld", &k, &w);
        printf("%lld\n", (sum + ((n * w % mod + f[k]) % mod << 1) % mod) % mod);
    }
}
```

---

## 作者：紊莫 (赞：1)

Luogu 比赛首次 AK 祭，故写此文以纪念。  

## Part 1 题意分析

给出一个带边权的树，求每次和某个节点连一个新的点后，$\sum_{i=1}^{n+1}\sum_{j=1}^{n+1} cost(i,j) $ 的值。  

## Part 2 思路

观察数据范围，肯定不能每次模拟，那么考虑先计算出原有的 $n$ 个点 $\sum_{i=1}^{n}\sum_{j=1}^{n} cost(i,j) $ 的值，然后对于每一次询问再去计算新的点和原先 $n$ 个点的贡献。  

那么怎么计算 $n$ 个点的贡献呢？  

数据范围很大，我们需要 $O(n)$ 的方法来计算。注意到我们是在一棵树上计算，所以自然想到换根 DP。  

首先，我们通过一次 dfs，求出如下的信息：  

- ``siz[now]``：表示当前节点所在子树的大小。  
- ``fa[now]``：表示当前节点和其父亲节点的距离。  
- ``f[now]``：表示当前节点到其**子树中**每个点的距离之和。  

前两者都可以在 dfs 的过程中顺便求出，对于 ``f[now]``，我们可以写出如下代码来计算：  

```cpp
f[now] = (f[now] + siz[to[i]] * w[i] % mod + f[to[i]]) % mod;
```

意思就是 ``f[now]`` 的值，相当于当前节点所有儿子的 ``f`` 值加上儿子子树的大小乘和儿子的距离，也就是说在儿子的基础上，每个点都要多走 ``w[i]`` 的路程。   

```cpp
void dfs(int now,int father){
	f[now] = 0; siz[now] = 1;
	for(int i=head[now];i;i=nxt[i]){
		if(to[i]==father) continue;
		dfs(to[i],now);
		siz[now] += siz[to[i]];
		fa[to[i]] = w[i];
		f[now] = (f[now] + siz[to[i]] * w[i] % mod + f[to[i]]) % mod;
	}
}
```

然后没完，我们只求了到子树的所有距离之和，可是到父亲的呢？所以我们需要换根，也就是把每个节点都看作是根。  

```cpp
void dp(int now,int father){
	if(now == 1) sum[now] = f[now];
	else sum[now]=sum[father]+fa[now]*(n-2*siz[now]);
	ans = (ans + sum[now])%mod;
	for(int i=head[now];i;i=nxt[i])
		if(to[i]!=father)
			dp(to[i],now);
}
```  

``sum[now]`` 就表示了当前节点到所有节点的距离总和。  

特别的，对于根节点，``sum[now] = f[now]``。  

注意这里的代码是化简过的，原先的思路是这样的：  

首先知道了父亲节点的 ``sum`` 值，那么首先要减去对于自己这块的贡献，然后对于父亲节点那，加上 ``fa[now]`` 带来的贡献，最后加上自己对于子树的 ``f[now]`` 即可。  

```cpp
sum[now] = sum[father] - f[now] - siz[now] * fa[now] + (n-siz[now]) * fa[now] + f[now];
```

整理一下即可。  

至此为止，我们已经求出了原先 $n$ 个点的贡献，那么对于新加入的点，计算方法就很简单了，直接参考我们计算 ``sum`` 的方法即可。  

## Part 3 代码  

[赛时 AC 代码（2.11 KB）](https://www.luogu.com.cn/paste/7rvyn9ys)

---

## 作者：Nwayy (赞：1)

[全局题解](https://www.cnblogs.com/Nwayy/p/17659635.html)

题意：给定一棵树，有边权，有 $q$ 次询问，每次询问把 $n+1$ 号点连向 $k$，边权为 $w$，求全局距离和对 $998244353$ 取模。询问间相互独立。$1 \le n,q \le 2 \times 10^5$。

赛时思路：先考虑拆式子。

设 $hp_{x}$ 表示 $x$ 到剩余所有点距离和。则容易得到：

$$\sum\limits_{i=1}^{n+1} \sum\limits_{j=1}^{n+1} cost(i,j)=\sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} cost(i,j)+2 \times \sum\limits_{i=1}^{n} cost(i,n+1)=\sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} cost(i,j)+2 \times hp_{k} \times n$$

先考虑 $hp$ 数组怎么求。首先我们可以求出 $i$ 子树内所有点到 $i$ 的 $hf$ 值，这是容易的，转移方程为 $hf_{x}=\sum\limits_{y \in son_{x}} {hf_{y}+s_{y} \times w(x,y)}$。其中 $s_{x}$ 表示 $x$ 子树内节点个数，$w(x,y)$ 表示 $x$ 与 $y$之间边权。

然后可以发现根节点此时的 $hf$ 值即为 $hp$ 值，而且容易发现每个节点的 $hp$ 值与其父亲有关，即 $hp_{x}=hf_{x}+(hp_{fa_{x}}-hp_{x}-s_{x} \times w(x,fa_{x}))+(n-s_{x}) \times w(x,fa_{x})$。其中 $fa_{x}$ 表示 $x$ 的父亲。

现在我们已经求出了 $hp$ 数组，式子进一步转换为 $\sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} cost(i,j)+2 \times hp_{k} \times n=\sum\limits_{i=1}^{n} hp_{i}+2 \times hp_{k} \times n$。然后预处理出 $\sum\limits_{i=1}^{n} hp_{i}$ 即可。

但是我写的时候是先用了另一种方法求 $\sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} cost(i,j)$ 的，就是考虑某条边被经过的次数，容易发现这条边分成两个集合，经过次数即为两个集合点个数乘积，由于 $cost(i,j)$ 和 $cost(j,i)$ 算两次，所以还要乘个 $2$。但是 $hp$ 数组是一定要求的。

复杂度依旧线性。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 500005
#define int long long
const int mod=998244353;
int n,m,i,j,ans,q,a,b,x[N],s[N],p,w,c,h[N],k,hp[N],f[N],dep[N];
struct AB{
	int a,b,c,n;
}d[N<<1];
void cun(int a,int b,int c){
	d[++k].a=a,d[k].b=b,d[k].c=c;
	d[k].n=h[a],h[a]=k;
}
void dfs(int a,int lst){
	f[a]=lst,x[a]=1,dep[a]=dep[lst]+1;
	for(int i=h[a];i;i=d[i].n){
		int y=d[i].b,c=d[i].c;
		if(y!=lst) dfs(y,a),x[a]=(x[a]+x[y])%mod,hp[a]=(hp[a]+hp[y])%mod,hp[a]=(hp[a]+x[y]*c%mod)%mod;
	}
	s[a]=n-x[a];
}
void work(int a,int lst){
	for(int i=h[a];i;i=d[i].n){
		int b=d[i].b,c=d[i].c;
		if(b!=lst) hp[b]=(hp[b]+((hp[a]-hp[b]-x[b]*c%mod)%mod+mod)%mod+s[b]*c%mod)%mod,work(b,a);
	}
}
signed main(){
	scanf("%lld%lld",&n,&q);
	for(i=1;i<n;i++){
		scanf("%lld%lld%lld",&a,&b,&c);
		cun(a,b,c),cun(b,a,c);
	}
	dfs(1,0),work(1,0);
	for(i=1;i<=k;i+=2){
		int a=d[i].a,b=d[i].b;
		if(dep[a]<dep[b]) ans=(ans+x[d[i].b]*(n-x[d[i].b])%mod*d[i].c%mod*2ll%mod)%mod;
		if(dep[b]<dep[a]) ans=(ans+x[d[i].a]*(n-x[d[i].a])%mod*d[i].c%mod*2ll%mod)%mod;
	}
	while(q--){
		scanf("%lld%lld",&p,&w);
		printf("%lld\n",(ans+(hp[p]+n*w%mod)*2ll%mod)%mod);
	}
	return 0;
}
```

---

## 作者：happy_zero (赞：1)

可以发现最终的答案可以分两部分来处理：$\sum_{i=1}^n\sum_{j=1}^ncost(i,j)$ 和 $2\times \sum_{i=1}^ncost(i,n+1)$，接下来就分两部分处理。

首先看第一部分。这一部分无论 $k_i,w_i$ 是多少都没有影响，所以可以预处理。记 $f_i$ 表示 $i$ 到树中所有节点的距离和，于是第一部分也就是 $\sum_{i=1}^nf_i$，而我们可以通过两遍 dfs 做到 $O(n)$ 求任意的 $f_i$，过程如下（设根为 $1$）：

- 第一遍先求出 $i$ 到其子树内的节点的距离和 $g_i$ 以及 $i$ 的子树大小，转移方程是 $siz_i=\sum_{k\in son_i}siz_k,g_i=\sum_{k\in son_i}g_k+s_k\times w$，其中 $w$ 表示的 $i$ 到 $j$ 的距离和。

- 第二遍就是求出 $f_i$。若 $i=1$，则 $f_i=g_i$，这会要让 $i$ 的父亲（$u$）的 $f_i$ 来更新 $i$：相较于 $f_u$，在 $i$ 子树外的点到 $i$ 的距离会增加 $w$，对应的贡献是 $(n-siz_i)\times w$；在 $i$ 子树内的点则距离都减少 $w$，对应贡献为 $-siz_i\times w$，整理起来就是 $f_i=f_u+(n-2\times siz_i)\times w$。

接下来看第二部分。假设 $n+1$ 是接在 $k$ 上，那么所有节点到 $n+1$ 的距离相较于 $k$ 都会增加 $w$，所以答案就是 $2\times (f_k+n\times w)$。

然后就做到了 $O(n)$ 预处理，$O(1)$ 查询，最后代码中记得及时取模，如果有像 $n-2\times siz_i$ 这样的式子要加上模数后再取模。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N = 2e5 + 5;
const int Mod = 998244353;
inline int read() {
    int w = 1, q = 0; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') w = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
    return w * q;
}
struct node {
    int to, w;
};
int n, s[N], f1[N], f2[N];
vector <node> p[N];
void dfs1(int k, int fa) {
	s[k] = 1;
    for (auto i : p[k]) {
        if (i.to == fa) continue;
        dfs1(i.to, k);
        s[k] += s[i.to];
        (f1[k] += (f1[i.to] + s[i.to] * i.w % Mod) % Mod) %= Mod;
    }
}
void dfs2(int k, int fa) {
	if (k == 1) f2[k] = f1[k];
    for (auto i : p[k]) {
        if (i.to == fa) continue;
        f2[i.to] = (f2[k] + (n - 2 * s[i.to] + Mod) % Mod * i.w % Mod) % Mod;
        dfs2(i.to, k);
    }
}
signed main() {
    int m; n = read(), m = read();
    for (int i = 1, u, v, w; i < n; i++)
        u = read(), v = read(), w = read(), p[u].pb({v, w}), p[v].pb({u, w});
    dfs1(1, 0), dfs2(1, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans += f2[i], ans %= Mod;
    while (m--) {
    	int x = read(), y = read();
    	cout << (ans + f2[x] * 2 % Mod + y * n * 2 % Mod) % Mod << "\n";
	}
    return 0;
}
```



---

## 作者：SXqwq (赞：1)

## Analysis

一眼顶针，鉴定为换根 dp。

如果大家做过[这道题](https://www.luogu.com.cn/problem/P2986)的话，我们可以直接在这道题的基础上进行修改。（赛场我就是这么干的 qwq）

首先，如果忽略每次询问新建一条边，那这道题是不是就和上面那个一模一样？

每次询问加边也非常简单，运用 dp 的思想，考虑每次询问新增一条边的贡献。我们知道每次新增一条的边是从 $k$ 到 $n+1$。显然首先增加了以 $k$ 为“根节点”的贡献（这里的“根节点”是以上面那个题为例）。由于我们保证 **图上的每一个点都可以到达任意一个点**。所以以每个点作为“根节点”的贡献都会加 $w$（每个点都可以到达 $n+1$）。

上述描述可能有些许抽象，我们来画图举例。
![](https://cdn.luogu.com.cn/upload/image_hosting/eqjx32p0.png)

在上图中，我们把 $5$ 号节点作为 $k$。我们已经预处理加边之前以每个节点为“根节点”的贡献。新增这条边，首先从 $8$ 可以到 $5$，然后就是 $5$ 的贡献。所以 $ans+f_5$。（$ans$ 为每次询问加边之前，每个节点作为“根节点”的贡献和，$f_5$ 表示以 $5$ 作为“根节点”的贡献。我们已经通过换根 dp 求出）。

然后，由于从 $8$ 走到 $5$ 然后可以到达任意一个节点，而图上一共有 $n$ 个节点（除了新加上的 $n+1$ 号节点），每次走都会走一遍 $w$，所以需要 $ans+w\times n$。

这样就结束吗？怎么样例都过不了！仔细想想，由于是无向图，我们能从 $8$ 走到图上任意一个节点，显然从图上任意一个节点都可以走到 $8$！上述更改都需要 $\times 2$。

至于换根 dp 部分就可以愉快地套用[这道题](https://www.luogu.com.cn/problem/P2986)啦！由于比较板这里不再赘述，不明白换根 dp 如何处理的可以去看这道题的题解呢！

注意，本题还有一个坑点就是取模，在下文的代码部分会给出。

## Code
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define int long long
#define INF 1e18
using namespace std;
const int mod =  998244353;
typedef pair<int,int> PAIR;
const int N = 1000010;
int c[N],f[N],f1[N];
int sum[N];
vector <PAIR> Edge[N];
long long n,q;
int Sum = 0;
void dfs1(int now,int fa,int dist)
{
    sum[now] = c[now]%mod;
    sum[now] %= mod;
    for(int i=0;i<Edge[now].size();i++)
    {
        int v = Edge[now][i].first%mod,w = Edge[now][i].second%mod;
        if(v == fa) continue;
        dfs1(v,now,dist+w%mod);
        sum[now] += sum[v]%mod;
        sum[now] %= mod;
        f1[now] += f1[v]+w%mod*sum[v]%mod;
        f1[now] %= mod;
    }
}
void dfs2(int now,int fa)
{
    for(int i=0;i<Edge[now].size();i++)
    {
        int v = Edge[now][i].first,w = Edge[now][i].second,u = now;
        if(v == fa) continue;
        f[v] = f[u]+f1[u]%mod-(f1[v]%mod+(sum[v]%mod)%mod*w%mod)+(sum[1]-sum[v])%mod*w;
        f[v] = (f[v]%mod+mod)%mod; //减法操作一定要这么处理，否则前面取模变小，后面数很大，做减法会出现负数。
        if(sum[1]-sum[v] < 0) 
        {
        	return;
		} 
        dfs2(v,now);
    }
}
signed main()
{   
//	freopen("input.txt","r",stdin); 
//	freopen("output.txt","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        c[i] = 1;
    }
    for(int i=1;i<n;i++)
    {
        long long u,v,w; 
        cin>>u>>v>>w;
        Edge[u].push_back(PAIR(v,w));
        Edge[v].push_back(PAIR(u,w));
        Sum += w%mod;
        Sum %= mod; 
    }
    dfs1(1,0,0);
    dfs2(1,0);
    int Sum1 = 0;
    for(int i=1;i<=n;i++)
    {
        Sum1 += (f[i]%mod+f1[i]%mod);
        Sum1 %= mod;
    }
    while(q--)
    {
        long long k,w;
        cin>>k>>w;
        __int128 t = (Sum1%mod + (f[k]+f1[k]%mod+w%mod*n)%mod*2%mod) % mod;
        long long ans2=(long long)t%mod;
        cout<<ans2<<endl;
    }
    return 0;
}   
```

---

## 作者：_Spectator_ (赞：1)

[可能更好的食用体验](/blog/523641/P9584) $|$ 
[题目传送门](/problem/P9584) $|$ 
[我的其他题解](/blog/523641/#type=题解-New)

------------

${\large\color{#00CD00}\text{思路}}$

换根 DP 板子题（不会的请 [P1395 会议](/problem/P1395)）。

首先可以发现城市的关系是一棵树。先假设 $1$ 为根结点，定义 $g_u$ 为以 $u$ 为根的**子树中的结点**到 $u$ 的费用之和。例如，在样例 $1$ 中，$g_1=5+7+3=15,\,g_2=2+4=6$。

再定义 $sz_u$ 为以 $u$ 为根的子树中的结点数量，$edge(u,v)$ 为 $(u,v)$ 两点之间的边的费用。那么，对于 $u$ 的一个子结点 $v$，就有 $sz_v$ 个结点经过 $edge(u,v)$ 这条边。不难推出 $g_u=\sum\limits_{v\in u} g_v+ sz_v\times edge(u,v)$。

这一过程可以跑一遍 dfs 实现：
```cpp
void dfs(int u,int fa)
{
	sz[u]=1;
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].v,w=edge[i].w;
		if(v==fa)continue;
		dfs(v,u);
		sz[u]+=sz[v];
		g[u]=Mod(g[u]+g[v]+sz[v]*w);
	}
}
```

然后进行换根 dp。定义 $f_u$ 为树上**所有的结点**到 $u$ 的费用之和。对于 $u$ 的一个子结点 $v$，直接给出式子：$f_v=g_v+f_u-(g_v+sz_u\times edge(u,v))+(n-sz_v)\times edge(u,v)$。接下来分段解释这个式子。
1. $g_v$：以 $v$ 为根的子树中的点到 $v$ 的费用之和。
2. $f_u-(g_v+sz_v\times edge(u,v))$：全局到 $u$ 的费用之和，减去以 $v$ 为根的子树中的点到 $v$ 的费用之和。即不在 $v$ 的子树中的点到 $u$ 的费用之和。
3. $(n-sz_v)\times edge(u,v)$：共有 $(n-sz_v)$ 个不在 $v$ 的子树中的点经过了 $edge(u,v)$ 这条边。

可以发现，$2$ 和 $3$ 加起来就是不在 $v$ 的子树中的点到 $v$ 的费用之和。再加上 $1$ 就是全局到 $v$ 的费用之和了。

这一过程需要再跑一遍 dfs 实现：
```cpp
void dfs2(int u,int fa)
{
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].v,w=edge[i].w;
		if(v==fa)continue;
		f[v]=Mod(g[v]+Mod(f[u]-(g[v]+sz[v]*w)+(n-sz[v])*w));
		dfs2(v,u);
	}
}
```
初始时记得 $f_1\gets g_1$。

最后算一遍 $\sum f$，询问时加上 $(f_k+w\times n)\times 2$（因为是双向的所以要乘 $2$）就是答案。

注意：这题模的过程会有点问题，大数据有可能模出负数。因为我懒所以就直接用 long long 算+多模几次（逃）。

------------

${\large\color{#00CD00}\text{代码}}$

```cpp
#include<bits/stdc++.h>
#define int long long
#define Mod(x) ((x)+mod)%mod
using namespace std;
const int N=2e5+5,mod=998244353;
int n,q,idx,ans;
int head[N],sz[N],g[N],f[N];
struct stu{
	int v,next,w;
}edge[2*N];
void add(int x,int y,int w)
{
	edge[++idx]={y,head[x],w};
	head[x]=idx;
}
void dfs(int u,int fa)
{
	sz[u]=1;
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].v,w=edge[i].w;
		if(v==fa)continue;
		dfs(v,u);
		sz[u]+=sz[v];
		g[u]=Mod(g[u]+g[v]+sz[v]*w);
	}
}
void dfs2(int u,int fa)
{
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].v,w=edge[i].w;
		if(v==fa)continue;
		f[v]=Mod(g[v]+Mod(f[u]-(g[v]+sz[v]*w)+(n-sz[v])*w));
		dfs2(v,u);
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>q;
	for(int i=1;i<n;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		add(x,y,z),add(y,x,z);
	}
	dfs(1,0);
	f[1]=g[1];
	dfs2(1,0);
	for(int i=1;i<=n;i++)ans=Mod(ans+f[i]);
	for(int i=1;i<=q;i++)
	{
		int k,w;
		cin>>k>>w;
		cout<<Mod(ans+(f[k]+w*n)*2)<<endl;
	}
	return 0;
}
```

---

## 作者：conti123 (赞：1)

### 分析
考虑用树形 DP。

我们先把前 $n$ 个点两两之间距离求出来。这一步可以转换为求路径，及每条边经过的次数 $\times$ 边权的和。

对于第 $n+1$ 个点，我们发现其和前 $n$ 个点的距离之和可以转换为两个东西：剩下 $n-1$ 个点到连接点的距离之和和新连接的边的经过次数。

定义 $f[i]$ 表示原来的树中剩下 $n-1$ 个节点到 $i$ 号节点的距离之和。

那么在第一次 dfs 中，$f[1]$ 是可以算出来的。

在第二次 dfs 中而前 $n$ 个点两两之间距离之和也可以求出来。

对于剩下的 $f[i]$，我们发现，对于一个子节点 $v$，若它的父亲节点是 $u$，那么可以得出 $f[v]=f[u]+w\times(n-2\times sz[v])$，其中 $w$ 表示连接点 $u$ 和点 $v$ 的边的边权，$sz[v]$ 表示以 $v$ 为根节点的子树有几个节点。

算出所有的 $f[i]$ 后，对于每次的询问，可以 $O(1)$ 得出答案。
### Code
```cpp

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
const int N=1e6+1;
int n,m,head[N],sz[N],x,y,z,idx,ans,d[N],up[N],f[N],g[N];
struct fy
{
	int v,w,next;
}edge[N<<1];
void add(int x,int y,int z)
{
	edge[++idx].v=y,edge[idx].w=z,edge[idx].next=head[x],head[x]=idx;
}
void dfs(int u,int fa)
{
	sz[u]=1;
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].v,w=edge[i].w;
		if(v==fa)
			continue;
		dfs(v,u);
		sz[u]+=sz[v];
		sz[u]%=mod;
		d[u]+=w*sz[v];
		d[u]+=d[v];
		d[u]%=mod;
	}
}
void dfs_(int u,int fa)
{
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].v,w=edge[i].w;
		if(v==fa)
			continue;
		dfs_(v,u);
		ans+=(sz[v]*(n-sz[v]))*w;
		ans%=mod;
	}
}
void dfs__(int u,int fa)
{
	for(int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].v,w=edge[i].w;
		if(v==fa)
			continue;
		f[v]=f[u]+w*(n-2*sz[v]);
		f[v]%=mod;
		f[v]=(f[v]+mod)%mod;//注意一定要加上mod
		dfs__(v,u);
	}
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<n;i++)
	{
		scanf("%lld%lld%lld",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	dfs(1,0);
	dfs_(1,0);
	f[1]=d[1];
	dfs__(1,0);
   //初始化f[i]
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&x,&y);
		printf("%lld\n",(ans+f[x]+n*y%mod)*2%mod);
      //要乘2因为我们算的只是有序数对。
	}
}
```

---

## 作者：玄学OIER荷蒻 (赞：1)

不知道要对 $998244353$ 取模（忘搞了），赛时回来补，心态炸了，代码爆 $0$ 取模就 AC 了。

首先分析问题。

先看这个式子，我们发现每次的公共部分是 $\sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} cost(i,j)$。

可以考虑把这个式子求出来，怎么求到时候再说。

然后每次不一样的部分是 $2\times \sum\limits_{i=1}^{n} cost(n+1,i)$。（自己到自己的距离为 $0$ 不用管）

下文中，我们令 $v_{x,y}$ 为连接 $x$ 到 $y$ 的边的距离。（如果是几条边连接不是一条就为 $0$）

我们只需要求出这个点到所有点的距离，然后我们发现，如果令 $1$ 为根，那么这个新点只能是叶子，它到所有节点的距离等于 $n\times v_{n+1,k}+\sum\limits_{i=1}^{n} cost(k,i)$

于是，这可以令我们想出，预处理出所有点对所有其他点的距离。

其实预处理这块，可以参考我做完后找出的这题：[连接](https://www.luogu.com.cn/problem/P2986)。

只能说一模一样。

然后我们考虑求出其子树大小 $z_i$ 和节点对所有子树的距离之和 $d_i$ 和其父亲 $f_i$，父亲怎么处理就不用我多说了。

可以一遍 dfs 搞定，因为 $z_i=\sum\limits_{f_j=i}{z_j}+1,d_i=\sum\limits_{f_j=i}{(d_j+z_j \times v_{i,j})}$。

接下来考虑求出一个点到非子树节点的距离之和 $k_i$，这里就是 $k_i=k_{f_i}+d_{f_i}+v_{i,f_i} \times (n-2\times d_i)$。

之后，这个要第二遍 dfs，代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q;
vector<pair<int,int> > v[200010]; 
long long fa[200010],zishu[200010],dzi[200010],dis3[200010];
long long mod=998244353;
void dfs1(int x){
	zishu[x]=1;
	for (int i=0;i<v[x].size();i++){
		if (v[x][i].first==fa[x]) continue;
		fa[v[x][i].first]=x;
		dfs1(v[x][i].first);
		zishu[x]+=zishu[v[x][i].first];
		dzi[x]=(v[x][i].second*zishu[v[x][i].first])%mod+(dzi[x]+dzi[v[x][i].first])%mod;
		dzi[x]%=mod;
	}
}
void dfs2(int x){
	for (int i=0;i<v[x].size();i++){
		if (v[x][i].first==fa[x]) continue;
		dis3[v[x][i].first]=dis3[x]+dzi[x]-(v[x][i].second*zishu[v[x][i].first])%mod-dzi[v[x][i].first]+(v[x][i].second*(n-zishu[v[x][i].first]))%mod;
		dis3[v[x][i].first]%=mod;
		if (dis3[v[x][i].first]<0) dis3[v[x][i].first]+=mod;
		dfs2(v[x][i].first);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>q;
	for (int i=1;i<=n-1;i++){
		int u,vv,c;
		cin>>u>>vv>>c;
		v[u].push_back(make_pair(vv,c));
		v[vv].push_back(make_pair(u,c));
	}
	dfs1(1);
	dfs2(1);
	long long ans=0;
	for (int i=1;i<=n;i++){
		ans+=dzi[i]+dis3[i];
	}
	while (q--){
		long long kk,ww;
		cin>>kk>>ww;
		cout<<((dzi[kk]+dis3[kk]+(ww*n)%mod+dzi[kk]+dis3[kk]+(ww*n)%mod+ans)%mod+mod)%mod<<'\n';
	}
	return 0;
}
```


最后，OI 赛制一定要测大样例！

---

## 作者：船酱魔王 (赞：1)

# P9584 城市 题解

## 题意回顾

给定边带权的一棵 $ n $ 点无向树，定义一棵树的总权值为每个点到所有点的距离之和。$ q $ 次询问，每次询问**临时**在一个点上向新点连一条边，每次组成一个 $ n+1 $ 点无向树。求每次询问后树的权值。（询问修改不作用于之后的询问）

$ 2 \le n \le 2 \times 10^5 $，$ 1 \le q \le 2 \times 10^5 $。

## 分析

我们先考虑初始时树的权值。

我们定义 $ f_u $ 表示 $ u $ 到子树内所有点的距离和，定义 $ w_{<u,v>} $ 为 $ u $ 到 $ v $ 的边的长度，显然有：

$$ f_u=\sum_{v \in \operatorname{Son}(u)}\{f_v+w_{<u,v>} \times sz_v\} $$

我们定义 $ dp_u $ 表示 $ u $ 到整棵树所有点的距离和，则显然有 $ dp_1=f_1 $。

考虑如何从父结点转移到子结点。我们可以发现不在子结点子树内的点到子结点会比父结点多走一条父子之间的边的距离，而子树内点会少走一条父子之间的边的距离，因此容易列出 $ u $ 向 $ v $ 转移的转移方程：

$$ dp_{v}=dp_{u}+(n-sz_{v} \times 2) \times w_{<u,v>} $$

当在一个点向新点连边时，权值增加了多少呢？因为发现新点到本身的距离为 $ 0 $，所以增加的部分只有原来点和新点之间的距离和，新点到每个点的距离和显然和每个点到新点的距离和一样。新点到每个点的距离显然是与他连边的点到每个点的距离加上 $ n $ 倍的边长。

因此，对于与新点连边的点 $ u $ 和边权 $ w $，答案即为：

$$ \sum_{i=1}^{n} dp_i+2 \times (nw+dp_{u}) $$

而 $ dp $ 数组的和可以直接预处理，因此本题解决，注意 ```long long``` 和及时取模。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 2e5 + 5;
const int mod = 998244353;
int n, q;
struct node {
	int to;
	int w;
};
node make(int v0, int w0) {
	node res;
	res.to = v0;
	res.w = w0;
	return res;
}
vector<node> g[N];
long long f[N];
int sz[N];
void pre_dfs(int u, int fath) {
	sz[u] = 1;
	for(int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].to;
		int w = g[u][i].w;
		if(v == fath) {
			continue;
		}
		pre_dfs(v, u);
		sz[u] += sz[v];
		f[u] += f[v] + (long long)sz[v] * w % mod;
		f[u] %= mod;
	}
}
long long dp[N];
void dfs(int u, int fath) {
	for(int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].to;
		int w = g[u][i].w;
		if(v == fath) {
			continue;
		}
		dp[v] = dp[u] + (long long)(n - sz[v] * 2) * w;
		dp[v] = (dp[v] % mod + mod) % mod;
		dfs(v, u);
	}
}
int main() {
	std::ios::sync_with_stdio(false);
	cin >> n >> q;
	int u, v, w;
	for(int i = 1; i < n; i++) {
		cin >> u >> v >> w;
		g[u].push_back(make(v, w));
		g[v].push_back(make(u, w));
	}
	pre_dfs(1, 0);
	dp[1] = f[1];
	dfs(1, 0);
	long long sum = 0;
	for(int i = 1; i <= n; i++) {
		sum += dp[i]; 
	}
	sum %= mod;
	for(int qi = 1; qi <= q; qi++) {
		cin >> u >> w;
		long long ans = sum + ((long long)dp[u] + (long long)n * w % mod) * 2 % mod;
		ans %= mod;
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：SamHJD (赞：0)

## [P9584 城市](https://www.luogu.com.cn/problem/P9584)

### 题意

给出一个 $n$ 个节点的树，定义 $dist_{i,j}$ 为树上 $i$ 到 $j$ 的距离。每次询问让你将点 $n+1$ 连向 $k$，边权为 $w$，求 $\sum\limits_{i=1}^{n+1}\sum\limits_{j=1}^{n+1}dist_{i,j}$。询问之间互不影响。

### 解法

**Part 1**

首先不考虑点 $n+1$，我们该如何求出 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}dist_{i,j}$ 呢？不妨考虑每条边对答案的贡献。

对于边 $u\to v$，$v$ 的子树包括它的所有点都要经过它连向其他节点计入答案，设 $x$ 的子树为 $siz_x$，则边 $u\to v$ 的贡献便为 $2\times siz_v\times (n-siz_v)\times w_{u\to v}$。那么总共的路径和为：

$$2\times\sum siz_v\times(n-siz_v)\times w_{u\to v}$$

**Part 2**

加入一个点 $n+1$ 连向 $k$ 后，我们观察每条边的贡献公式中哪里发生了变化。

对于根到 $k$ 的路径中，$siz_v$ 变大了一，因为多了点 $n+1$。对于其他的点，则是 $n-siz_v$ 变为 $n-siz_v+1$，因为 $siz_v$ 不变而除了这棵子树的其他店多了一个点 $n+1$。

总结变化，不为根到 $k$ 的路径的边的贡献为 $2\times siz_v\times (n-siz_v+1)\times w_{u\to v}$，在根到 $k$ 的路径的边的贡献为 $2\times (siz_v+1)\times (n-siz_v)\times w_{u\to v}$。新增的 $n+1\to k$ 的贡献为 $2\times n\times w_{n+1\to k}$。

**Part 3**

根到一个点 $k$ 的边的新贡献 $2\times (siz_v+1)\times (n-siz_v)\times w_{u\to v}$ 是可以预处理的，不为根到 $k$ 的路径的边的贡献 $2\times siz_v\times (n-siz_v+1)\times w_{u\to v}$ 却不太好预处理。

我们不妨将所有边都先按照这个公式计算，用 $tot$ 记录。然后减去根到 $k$ 的路径的边按照这个公式计算的贡献，加上根到 $k$ 的路径预处理出的真正贡献和 $2\times n\times w_{n+1\to k}$ 便是我们想要的答案。

取模不要忘，乘数 $x$ 的时候要写为 `xll`。

### 代码

```cpp
#include "bits/stdc++.h"
using namespace std;
#define int long long
const int N=2e5+10,MOD=998244353;
int n,q,ecnt,head[N],siz[N],f[N],tot,now[N],pre[N];
struct E{
	int u,v,next,w;
}e[N*2];
void add(int u,int v,int w){
	e[++ecnt]={u,v,head[u],w};
	head[u]=ecnt;
}
void dfs(int u,int fa){//计算子树大小
	f[u]=fa;
	siz[u]=1;
	for(int i=head[u];i;i=e[i].next){
		if(e[i].v==fa) continue;
		dfs(e[i].v,u);
		siz[u]+=siz[e[i].v];
	}
}
void dfs2(int u,int nowsum,int presum){
	now[u]=nowsum;pre[u]=presum;
	for(int i=head[u];i;i=e[i].next){
		if(e[i].v==f[u]) continue;
		int now_=1ll*(e[i].w*(siz[e[i].v]+1)%MOD*(n-siz[e[i].v])%MOD)*2%MOD;
        //now[k]记录1到k的路径上按照公式2计算的贡献和
		int pre_=1ll*(e[i].w*(siz[e[i].v])%MOD*(n-siz[e[i].v]+1)%MOD)*2%MOD;
        //pre[k]记录1到k的路径上按照公式1计算的贡献和
		tot+=2ll*(e[i].w*(siz[e[i].v])%MOD*(n-siz[e[i].v]+1)%MOD)%MOD;
        //tot记录按照所有边按照公式1计算的贡献和
		dfs2(e[i].v,nowsum+now_,presum+pre_);
	}
}
signed main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<n;++i){
		int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
		add(u,v,w);add(v,u,w);
	}
	dfs(1,0);
	dfs2(1,0,0);
	for(int i=1;i<=q;++i){
		int k,w;scanf("%lld%lld",&k,&w);
		printf("%lld\n",((tot-pre[k]+now[k]+w*n*2ll%MOD)+MOD)%MOD);
        //Part 3最后的计算过程
	}
	return 0;
}
```


---

## 作者：xxxxxxxb (赞：0)

考虑新建一个点之后答案的变化。

不难想到此时答案可以分成两个部分：

1. 加上这个点之前的所有点两两之间的费用和，这一部分是固定的，可以预处理。
  
2. 这个点的贡献。
  

对于第一部分，通过 $f$ 数组和 $g$ 数组，分别维护以这个点为根的子树中的节点到这个点的费用和，和除了以这个点为根的子树之外所有点到这个点的费用和。

有如下转移：

$ f_u = \sum_{v \in E_u} {f_v+ws_v} $

$g_v =g_u+ w(|E|-s_u) + f_u - f_v - ws_v + w(s_u - s_v)$

其中 $E_u$ 为 $u$ 引出的所有边，$v$ 是边权，$|E|$ 为点集大小，$s_u$ 为以 $u$ 为根的子树的大小。

第一个公式不难理解，就是以 $v$ 为根的子树的所有点先到点 $v$ 然后一起走 $w$ 的长度。

第二个公式中 $g_u+w(|E|-s_u)$ 表示除了以父亲节点为根的子树中的所有点一起走到父亲点，再一起走长度 $w$ 剩下部分表示以父亲为根的子树内除了以当前节点为根的子树的其他部分一起走到父亲节点，再走长度 $w$。

代码如下，注意取模 ：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = (int)2e5+7,MOD = 998244353;
int n,q;
struct E {
	int v,w,nxt;
}e[N*2];
int fs[N],ff[N],f[N],cnt,siz[N],sum;
void ins(int u,int v,int w) {
	e[++cnt] = {v,w,f[u]};
	f[u] = cnt;
}
void dfss(int now,int fat) {
	siz[now] = 1;
	for(int i = f[now];i;i=e[i].nxt) {
		int v = e[i].v,w = e[i].w;
		if(v == fat) continue;
		dfss(v,now);
		(siz[now] += siz[v]) %= MOD;
		fs[now] += (1ll*w*(siz[v]%MOD)%MOD + fs[v]) % MOD;
	}
}
void dfsf(int now,int fat) {
	for(int i = f[now];i;i = e[i].nxt) {
		int v = e[i].v,w = e[i].w;
		if(v == fat) continue;
		ff[v] = (1ll*ff[now]%MOD + 1ll*((n%MOD-siz[now]%MOD)%MOD)*w%MOD + 
				 1ll*fs[now]%MOD - 1ll*fs[v] - 1ll*w*siz[v]%MOD +
				 1ll*((siz[now] - siz[v])%MOD)*w + MOD)%MOD; //这里注意，模意义下的减法要先加MOD再模MOD
		dfsf(v,now);
	}
}
void sol() {
	int k,w;
	cin >> k >> w;
	cout << (1ll*sum + (2ll*(((fs[k] + ff[k]) % MOD + n*w%MOD)%MOD)%MOD)%MOD+MOD)%MOD << "\n";
}
signed main() {
	//freopen("city6.in","r",stdin);
	//freopen("city6.out","w",stdout);
	cin >> n >> q;
	for(int i = 1;i <= n-1;++i) {
		int u,v,w;
		cin >> u >> v >> w;
		ins(u,v,w);
		ins(v,u,w);
	}
	dfss(1,0);
	dfsf(1,0);
	for(int i = 1;i <= n;++i) {
		sum = (((sum+fs[i])%MOD)+ff[i])%MOD;
	}
	while(q--) {
		sol();
	}
	return 0;
}
```

---

## 作者：sbno333 (赞：0)

这道让我欲哭无泪，本来满分思路，结果减法没加模数，导致五十分，~~呜呜呜~~。

其实这道题我没感觉出动态规划，仔细想一下就能得到答案。

刚开始我想的的暴利，但看到那恐怖的数据量后，我沉默了。

因为这是 Div.3，所以我相信我能做出来，最后就得到了如下做法。

首先，我们可以只考虑 $a$ 到 $b$ 的情况，输出是乘二即可。

其次，我们考虑时可以先不考虑 $n+1$，输入时在临时处理，上下的在 $O(n)$ 的时间复杂度内即可。

由此，我们可以想到暴利，但由于 `TLE`，因此我们需要换个思路。

我们可以考虑每一条边，考虑这条边在所有可能中的经过的次数，在乘上边权，贡献给答案即可。

```cpp
void dfs(long long t){
	vis[t]=1;//标记，被标记过的就是根节点
	for(long long i=h[t];i;i=sd[i].ne){
		if(!vis[sd[i].v]){
			dfs(sd[i].v);//递归，为一下做准备
			s[t]+=s[sd[i].v];//计算子树节点数
			ans+=s[sd[i].v]*(n-s[sd[i].v])*sd[i].w;//不难发现一条边经过的次数为这条边离根节点远的的端点形成的子树的节点数乘其它节点的数量，即当且仅当其子树中的节点与非子树中的节点的简单路径会经过这条边
			ans%=mo;
		}
	}
	s[t]++;//加上这个节点，否则爆0（得到0）
}
```
接下来我们要处理询问，最好用 $O(1)$ 的时间复杂度。

不难发现点 $n+1$ 连点 $k$ 后增加的距离为所有点到点 $k$，加上 $n$ 倍的新边的权值 $w$，即该节点到任一点的距离，不难发现任一点到该点为任一点到点 $k$ 加 $n\times w$，因为一定会经过新边。

这个点我想了很久，最后的方案是这样的，新计算所有点到根节点的方案，然后对其它点进行转移。
```cpp
long long bfs(long long t){//主函数写bfs(1)，即假设点1为根并非真正的广搜，只是给个名字，该函数处理的是t的子树上的节点到该节点的距离之和
	vis[t]=0;
	long long an;
	an=0;
	for(long long i=h[t];i;i=sd[i].ne){
		if(vis[sd[i].v]){//根节点一定被标记过
			an+=bfs(sd[i].v);//增加子节点的子树到子节点的距离增加子节点子树上的节点数乘到子节点的距离，因为一定会经过
			an+=sd[i].w*s[sd[i].v];
			an%=mo;
		}
	}
	return an;
}
```

转移给其它点时可以在递归的过程中，函数只处理当前节点的子节点，顺手递归。

```cpp
void kfs(long long t){
	zz[t]%=mo;
	vis[t]=1;
	for(long long i=h[t];i;i=sd[i].ne){
		if(!vis[sd[i].v]){
			zz[sd[i].v]=zz[t]+mod*10-sd[i].w*s[sd[i].v]+(n-s[sd[i].v])*sd[i].w;//对于距离的变化，子节点为根的子树上的节点距离需求的点的距离在由该节点变为子节点后，均减少与子节点的距离，其它点则增加，减得事后要加模数，呜呜呜
			kfs(sd[i].v);//处理子节点
		}
	}
}
```

最后我们可以轻松的将它们组合起来。

```cpp
int main(){
	cin>>n>>q;
	for(long long i=1;i<n;i++){
		long long a1,a2,ww;
		cin>>a1>>a2>>ww;
		ad(a1,a2,ww),ad(a2,a1,ww);//临界表存储
	}
	dfs(1);//计算其它节点答案
	zz[1]=bfs(1);//任一点到点1的距离
	kfs(1);//处理其它点
	for(long long i=1;i<=q;i++){
		long long k1,w1;
		cin>>k1>>w1;
		long long zzz;
		zzz=n;
		zzz*=w1;//其它n个点都要经过这个边才能到达n+1
		zzz%=mo;
		zzz+=zz[k1];任一点到k的距离
		zzz+=ans;//其他情况
		zzz*=2;//由于a->b的距离等于b->a的距离，所以我们可以先各统计一次，然后乘二
		zzz%=mo;
		cout<<zzz<<endl;
	}
	return 0;
}
```

完整代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long mo=998244353;
long long h[1000009];
long long s[1000009];
long long zz[1000009];
struct st{
	long long v,ne,w;
}sd[1000009];
long long inn;
long long n,q;
void ad(long long a1,long long a2,long long ww){
	sd[++inn].v=a2;
	sd[inn].w=ww;
	sd[inn].ne=h[a1];
	h[a1]=inn;
}
long long ans;
bool vis[1000009];
void dfs(long long t){
	vis[t]=1;
	for(long long i=h[t];i;i=sd[i].ne){
		if(!vis[sd[i].v]){
			dfs(sd[i].v);
			s[t]+=s[sd[i].v];
			ans+=s[sd[i].v]*(n-s[sd[i].v])*sd[i].w;
			ans%=mo;
		}
	}
	s[t]++;
}
long long bfs(long long t){
	vis[t]=0;//经典的废物利用
	long long an;
	an=0;
	for(long long i=h[t];i;i=sd[i].ne){
		if(vis[sd[i].v]){
			an+=bfs(sd[i].v);
			an+=sd[i].w*s[sd[i].v];
			an%=mo;
		}
	}
	return an;
}
void kfs(long long t){
	zz[t]%=mo;
	vis[t]=1;//经典的废物利用
	for(long long i=h[t];i;i=sd[i].ne){
		if(!vis[sd[i].v]){
			zz[sd[i].v]=zz[t]+mod*10-sd[i].w*s[sd[i].v]+(n-s[sd[i].v])*sd[i].w;
			kfs(sd[i].v);
		}
	}
}
int main(){
	cin>>n>>q;
	for(long long i=1;i<n;i++){
		long long a1,a2,ww;
		cin>>a1>>a2>>ww;
		ad(a1,a2,ww),ad(a2,a1,ww);
	}
	dfs(1);
	zz[1]=bfs(1);
	kfs(1);
	for(long long i=1;i<=q;i++){
		long long k1,w1;
		cin>>k1>>w1;
		long long zzz;
		zzz=n;
		zzz*=w1;
		zzz%=mo;
		zzz+=zz[k1];
		zzz+=ans;
		zzz*=2;
		zzz%=mo;
		cout<<zzz<<endl;
	}
	return 0;
}
```

---

## 作者：liangjindong0504 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9584)

好不容易在赛时写出来了，特此纪念。（小号）

这题的大数据是真的有用。

换根 dp 模板题。

**【前言】**

前置知识：换根 dp。

建议先行完成[换根 dp 模板题](https://www.luogu.com.cn/problem/P3478)以后再来做本题。

话说普及组为什么会有换根 dp？

**【具体思路】**

看完题，立马能想到全源最短路。可是即使用 ~~spfa~~ 迪杰斯特拉算法、Johnson 算法都会超时。毕竟这个 $n \le 2 \times 10^5$ 连 $O(n^2)$ 都过不去。（也许能得 50 分）。

既然求最短路的算法不行，该考虑~~玄学优化~~从题目限制中找线索了。

注意到题目中的一句话：

**这 $n$ 个城市之间由 $n-1$ 条双向道路互相连接。保证从任意一个城市出发，都能通过这 $n-1$ 条双向道路，到达任意一个城市。**

$n-1$ 条边的连通图是什么啊？是**树**啊！

树上的“全源最短路”怎么求呢？立马想到换根 dp，时间复杂度仅为 $O(n)$。

由于这是一颗无根树，因此默认根为 $1$。

换根 dp 的思路在前面的模板题的题解里面，可以看看，这里就只讲一点。

以下没有图，大家自行脑部，推荐画出来。

设 $dp_i$ 为编号是 $i$ 的点到其它点的路径长度总和，$ds_i$ 为根节点到编号为 $i$ 的节点的路径长度。

首先，有一棵树，我们可以通过 $O(n)$ 的时间求出（即遍历一遍树）编号为 $1$。

此时，$dp_1$ 已经被求出来了，即为 $\sum\limits_{i=1}^{n} ds_i$。

至于换根 dp，又是什么呢？

比如说，节点 $u$ 有一个子节点 $v$，则将根转移到 $v$ 时（其实就是统计这个子节点到各个节点路径长度总和），以 $v$ 为根的子树到根节点的距离减少了 $cost(u,v)$，其它节点到根节点的距离就增加了 $cost(u,v)$。

再预处理出 $size_i$ 为以 $1$ 号节点为根时 $i$ 节点为根的子树有几个节点。

易得状态转移方程为：$dp_v=dp_u-size_v \times cost(u,v)+size_u \times cost(u,v)$。

以此类推，直到推完所有节点。

经过换根 dp 之后，我们可以将各个节点到其它节点路径长度总和求出。

这样，预处理就结束了。

而对于每一个问题，节点 $n+1$ 到其它节点的路径之和易得出是 $dp_{k_i}+w_in$。可以看成从节点 $n+1$ 走到节点 $k_i$ ，再走到各个点。

至于其它点到节点 $n+1$ 呢？其实也是上面那个式子，因为现在节点数量为 $n+1$，边为 $n$，图还是连通图，因此现在的图还是一棵树。

因此，对于每一次询问，都可以得出结果为 $\sum\limits_{i=1}^{n} dp_i+2 \times (dp_{k_i}+w_in)$。

若还是不太懂，看看具体是如何实现的。

**【具体实现】**

第一步：输入&建图。

这一步没什么好说的，用链式前向星或者 ```vector``` 都可以建图（个人喜欢用 ```vector```）。**注意建双向边。**

```cpp
n=read();
q=read();
for(int i=1;i<n;i++){
	int u,v,w;
	u=read();
	v=read();
	w=read();
	vec[u].push_back((node){v,w});
	vec[v].push_back((node){u,w});
}
```
本人用了快读快输。

第二步：换根 dp（二次扫描法）。

首先是处理 $size$ 数组以及处理 $ds$ 数组，具体见代码。
```cpp
void dfs(int u){
	si[u]=1;//大小当然初始化为 1（根节点） 
	for(int i=0;i<vec[u].size();i++){//枚举每一个子节点 
		//获取这条边的数据。
		int z=vec[u][i].zhong;
		int c=vec[u][i].chang;
		//如果访问过了打断 
		if(flag[z]){
			continue;
		}
		//标记一下 
		flag[z]=1;
		//更新数组 
		ds[z]=ds[u]+c;
		//搜索子节点 
		dfs(z);
		//处理 size 
		si[u]+=si[z];
	}
}
```
然后是第二次遍历，大体思路前面已经讲过了，给出的代码主要是细节实现。
```cpp
void dfn(int u){
	for(int i=0;i<vec[u].size();i++){//枚举每个子结点
		//获取子节点数据 
		int z=vec[u][i].zhong;
		int c=vec[u][i].chang;
		//访问过了就不访问了 
		if(flag[z]){
			continue;
		}
		//标记 
		flag[z]=1;
		//转移 
		dp[z]=dp[u]-si[z]*c+(n-si[z])*c;
		//搜索子节点 
		dfn(z);
	}
}
```
第三步：统计答案。

答案比较好统计，上面已经给出。只要注意**取模**就可以了。

**【最后总结】**

[完整代码](https://www.luogu.com.cn/paste/9roxml1g)。

[提交记录](https://www.luogu.com.cn/record/122958797)。

本题虽然涉及到提高组算法，但是其难度并不算太高。不过这种题目在 ```CSP-J``` 中出现的概率应该很小。可以说，这题算是 ```S``` 组 ```T1``` 的题，是为提高组选手准备的。（以上仅个人观点）

如果还有不懂的可以私信我。

---

## 作者：Zi_Gao (赞：0)

## 前言

感觉一些题解写的太麻烦了，这里提供一种更加简洁的做法。并且阅读本文请准备好草稿纸，树画出来一面大脑内存不够。

一些约定：

1. 本文拟定 $1$ 号节点为根。

2. $size_u$ 表示以 $u$ 节点为子树的大小。

3. $son_u$ 表示 $u$ 的儿子。

4. $par_u$ 表示 $u$ 的父亲。

5. $u\rightarrow v$ 表示 $u$ 到 $v$ 节点边。

6. $w_{u\rightarrow v}$ 表示 $u$ 到 $v$ 节点边权。

## 正文

### 0x00 分析题目

相当于本文要求在添加一条边之后树上任意两点距离和，并且询问独立。

这样的题首先考虑计算出整个树本身不考虑其他点的答案贡献，然后每次询问时计算这个修改所造成的贡献即可。

### 0x01 计算推导

令 $f_u$ 表示 $u$ 子树内到 $u$ 这个点的答案贡献；$g_u$ 表示 $u$ 子树外内到 $v$ 这个点的答案贡献。

显然整个树的贡献

$$baseans=\sum_{u=1}^{n}f_u+g_u$$

每次询问的答案可以拆成，树原本的贡献和原本的点到加入点的贡，对于第二部分可以考虑加入的这条边的贡献和其他点到 $k$ 的贡献，这样可以快速计算。

$$ans=baseans+2\times\left(f_k+g_k+n\times w\right)$$

接下来考虑如何计算 $f_u$ 和 $g_u$。

对于 $f_u$ 显然拆成其儿子的贡献 $f_v$ 和 $w_{u\rightarrow v}$ 的贡献。

$$f_u=\sum_{v\in son_u} f_v+w_{u\rightarrow v}\times size_v$$

对于 $g_u$ 可以考虑拆成 $g_{par_u}$ 和 $par_u$ 子树内除开 $u$ 子树的贡献再加上 $par_u\rightarrow u$ 边的贡献。发现第二部分就是 $f_{par_u}$ 减去计算 $u$ 时的贡献。那么：

$$g_u=g_{par_u}+f_{par_u}-w_{par_u\rightarrow u}\times size_u$$ 

### 0x02 代码实现

计算 $f$ 从下往上递推 DFS，计算 $g$ 从上往下递推 DFS 即可。

AC CODE

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){register char s[20];register int i=0;if(x<0){x=-x;putchar('-');}if(x==0){putchar('0');return;}while(x){s[i++]=x%10;x/=10;}while(i){putchar(s[--i]+'0');}return;}

struct EDGE{
    int to;
    long long w;
};

std::vector<EDGE> e[200010];

const long long mod=998244353;
long long f[200010],g[200010],siz[200010],n,baseans;

void addEdge(int u,int v,int w){
    e[u].push_back((EDGE){v,w});
    return;
}

void dfs(int u,int p){
    int v;
    siz[u]=1;
    for(auto edge:e[u])
        if((v=edge.to)!=p){
            dfs(v,u);
            f[u]=(f[u]+edge.w*siz[v]+f[v])%mod;
            siz[u]+=siz[v];
        }
    return;
}

void dfs2(int u,int p,long long w){
    if(u!=1)
        g[u]=(f[p]-(f[u]+w*siz[u])%mod+(n-siz[u])*w%mod+g[p]+mod)%mod;
    baseans=(baseans+g[u]+f[u])%mod;
    int v;
    for(auto edge:e[u])
        if((v=edge.to)!=p)
            dfs2(v,u,edge.w);
    return;
}

signed main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    register int i,u,v,w;
    n=read();
    int q=read();
    
    for(i=1;i<n;++i){
        u=read();
        v=read();
        w=read();
        addEdge(u,v,w);
        addEdge(v,u,w);
    }

    dfs(1,1);
    dfs2(1,1,0);

    for(i=0;i<q;++i){
        u=read();
        w=read();
        print((baseans+((g[u]+f[u]+n*w)<<1))%mod);puts("");
    }

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

---

## 作者：OldDriverTree (赞：0)

前置芝士：换根 DP
___

# Solution

设 $sz_u$ 表示 $u$ 子树的大小，$f_u$ 表示 $u$ 到 $u$ 子树里所有节点的距离和，$g_u$ 表示 $u$ 到所有节点节点的距离和。

$f$ 的状态转移方程就是：$f_u=\sum\limits_{v\in son_u} f_v+w\times sz_v$。

用 $g_{fa_u}$ 推 $g_u$ 时把根节点设为 $u$ 后 $u$ 到 $u$ 子树里的节点的距离和会减少 $sz_u\times w$，$u$ 到 $u$ 子树外的节点的距离和会增加 $(n-sz_u)\times w$，因此 $g$ 的转移方程就是 $g_u=g_{fa_u}+(n-2\times sz_u)\times w$。

对于每个询问，答案就为 $\sum_{i=1}^n g_i+2\times (g_k+n\times w)$，询问前先统计下 $\sum_{i=1}^n g_i$ 即可。

# Code

```c++
#include<bits/stdc++.h>
#define P pair<int,int>
#define v e.first
#define w e.second
using namespace std;
const int mod=998244353;
const int N=2e5+1;
int n,f[N],g[N];
int q,ans,sz[N];
vector<P> G[N];

int read() {
	int x=0; char ch=0; while (!isdigit(ch) ) ch=getchar();
	while (isdigit(ch) ) x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return x;
}
void dfs(int u,int fa) {
	sz[u]=1; for (auto e:G[u]) if (v^fa)
	dfs(v,u),sz[u]+=sz[v],f[u]=( (f[u]+f[v])%mod+(1ll*w*sz[v]%mod) )%mod;
}
void solve(int u,int fa) {
	for (auto e:G[u]) if (v^fa)
	g[v]=(g[u]+1ll*(n-2*sz[v])*w%mod+mod)%mod,solve(v,u);
}
int main()
{
	n=read(),q=read();
	for (int i=1,x,y,z;i<n;i++) {
		x=read(),y=read(),z=read();
		G[x].push_back({y,z}),G[y].push_back({x,z});
	}
	dfs(1,0),g[1]=f[1],solve(1,0);
	for (int i=1;i<=n;i++) ans=(ans+g[i])%mod;
	while (q--) {
		int x=read(),y=read();
		printf("%d\n",(ans+2*( (g[x]+1ll*n*y%mod)%mod) )%mod);
	}
	return 0;
}
```

---

## 作者：Convergent_Series (赞：0)

默认 $1$ 为树根。

令 $\displaystyle c_u=\sum_{i=1}^n cost(u,i)$，$siz_u$ 为以 $u$ 为根的子树大小，$in_u$ 为连接 $u$ 和 $u$ 的父亲的边，$w_u$ 为 $in_u$ 的边权。

化简所求式子： 

$\displaystyle \sum_{i=1}^{n+1}\sum_{j=1}^{n+1} cost(i,j)=\sum_{i=1}^{n}\sum_{j=1}^{n} cost(i,j)+2\times\sum_{i=1}^n cost(n+1,i)$

$\because$ 从结点 $n+1$ 到树上任意结点都必须经过新加的边到点 $k$，

$\therefore \displaystyle \sum_{i=1}^{n+1}\sum_{j=1}^{n+1} cost(i,j)=\sum_{i=1}^{n}c_i+2\times(c_k+nw)$

思路很明显了：$O(n)$ 预处理 $\forall i\in[1,n]\ c_i$，$O(1)$ 询问。

先计算 $c_1$：

对于每个结点 $u$，从 $1$ 到它的子树中任一点都要经过 $in_u$， 所以每条边对 $c_1$ 的贡献就是边权乘以端点中较深一个的子树大小。

考虑各节点之间 $c_i$ 的递推关系：

对于任意非根节点 $u$ 和他的父亲 $v$，

$\displaystyle c_u=\sum_{i\in u\text{的子树}} cost(i,u)+\sum_{i\notin u\text{的子树}} cost(i,u)=(n-siz_u)w_u+\sum_{i\in u\text{的子树}} cost(i,u)+\sum_{i\notin u\text{的子树}} cost(i,v)$

$\displaystyle c_v=\sum_{i\in u\text{的子树}} cost(i,v)+\sum_{i\notin u\text{的子树}} cost(i,v)=siz_uw_u+\sum_{i\in u\text{的子树}} cost(i,u)+\sum_{i\notin u\text{的子树}} cost(i,v)$

$\therefore c_u=c_v+(n-2siz_u)w_u$

根据 $c_1$ 递推得出 $\forall u\in[2,n]\ c_u$，统计 $\displaystyle\sum_{i=1}^n c_i$，每次询问时代入 $k,w$ 计算即可。

时间复杂度 $O(n+q)$。

### 代码：

```cpp
#include<bits/stdc++.h> 
#define int long long
using namespace std;
int read(){
	int a=0,f=1;char ch=getchar();
	while(!((ch>='0'&&ch<='9')||ch=='-')) ch=getchar();
	if(ch=='-') f=-1,ch=getchar();
	while(ch>='0'&&ch<='9') a=(a<<3)+(a<<1)+(ch^'0'),ch=getchar();
	a*=f;return a;
} 
void write(int a){
	if(a<0){putchar('-'),a=-a;}
	if(a>9) write(a/10); 
	putchar(a%10+'0');
}
const int N=2e5+10,mod=998244353;
struct edge{int to,ne,w;}e[N*2];
int ccnt=1,fi[N];
void add(int u,int v,int z){
	ccnt++;
	e[ccnt].to=v;e[ccnt].ne=fi[u];
	fi[u]=ccnt;e[ccnt].w=z;
}
int n,q,c[N],in[N],siz[N],dep[N],cost;
void dfs(int u,int v){//计算 siz,in
	siz[u]=1;dep[u]=dep[v]+1;
	for(int i=fi[u];i;i=e[i].ne){
		if(e[i].to!=v){
			dfs(e[i].to,u);
			siz[u]+=siz[e[i].to];in[e[i].to]=i;
		}
	}
}
void dfs2(int x,int in){//计算 c
	c[x]=(c[e[in^1].to]+e[in].w*((n-siz[x]-siz[x])%mod+mod)%mod)%mod;
	for(int i=fi[x];i;i=e[i].ne) if(i!=(in^1)) dfs2(e[i].to,i);
}
signed main(){
	n=read(),q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),z=read();
		add(u,v,z);add(v,u,z);
	}
	dfs(1,0);
	for(int i=2,j;i<=ccnt;i+=2){
		if(dep[e[i].to]<dep[e[i^1].to]) j=i^1;else j=i;
		c[1]=(c[1]+e[j].w*siz[e[j].to]%mod)%mod;
	}//计算c[1]
	for(int i=fi[1];i;i=e[i].ne){
		dfs2(e[i].to,i);
	}
	for(int i=1;i<=n;i++) cost=(cost+c[i])%mod;
	while(q--){
		int k=read(),w=read();
		write(((cost+c[k]*2+w*n*2)%mod+mod)%mod),putchar('\n');
	}
	return 0;
} 
```

---

## 作者：大眼仔Happy (赞：0)

~~我不敢相信这是一道绿题啊~~

来水一发绿题题解

观察一下数据范围，我们可以发现 $O(qn)$ 就可以导致爆炸，理想的时间复杂度应该是 $O(n+q)$。现在我们需要考虑如何做到这个时间复杂度。

显然要这样做的话，每次询问必然是要 $O(1)$ 来完成，那么我们就需要预处理出一些什么东西。

下面先不考虑修改的操作，就以原来的树试着求 $\sum_{i=1}^n\sum_{j=1}^ncost(i,j)$。显然暴力是 $O(n^2)$。考虑如何优化。

我们把视角从观察点的性质到观察边的性质。对于每一条边，可以去考虑一下这条边贡献了多少次。下定义 $f_x$ 表示 $x$ 子树的节点数量，$fa_x$ 表示 $x$ 节点的父亲。这里我们默认根为 $1$。显然对于一条边 $fa_u\rightarrow u$，当 $i$ 选择 $u$ 子树的点，$j$ 选择其他点，所构成的简单路径都会经过这条边。那么这条边的贡献次数就是 $num_u=2f_u(n-f_u)$，乘 $2$ 是因为 $i,j$ 可以互换位置，之后再乘上每条边的权值就是答案了。

```cpp
void dfs(int u,int fa)
{
	f[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa)continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
		f[u]+=f[v];
	}
}
```
```cpp
for(int i=1;i<n;i++)
{
	int u=e[i<<1].u,v=e[i<<1].v;ll w=e[i<<1].w;
	if(dep[u]>dep[v])swap(u,v);
	num[i]=(2*f[v]*(n-f[v]))%mod;
	ans=(ans+num[i]*w)%mod;
}
```

但是还有修改，下面我们就要考虑加上修改操作。显然对于每次修改，最后节点数都会变成 $n+1$，所以上面的 $n$ 就要改成 $n+1$。再考虑添加一条边对于 $f_x$ 即 $num_x$ 的影响。我们会发现，将 $k\rightarrow n+1$ 后，$n+1$ 所有的祖先 $u$ ，都会发生变化 $f_u\rightarrow f_u+1$，然后进一步导致边 $fa_u\rightarrow u$ 的贡献数量的变化 $num_u\xrightarrow{-4f_u+2n}num'_u$。所以我们就可以用 $dis_u$ 记录 $u$ 及其祖先的贡献答案的变化得到递推为 $dis_u=dis_{fa}+(-4f_u+2n)\times w_{fa\rightarrow u}$。需要注意的是因为根节点 $1$ 没有父亲，所以 $dis_1=0$。

一些细节，可以看[这个帖子](https://www.luogu.com.cn/discuss/673273)。

好了直接展示我们最终的代码吧：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=3e5+5;
const ll mod=998244353;
int n,q,rt;
ll ans;
struct edge{int u,v,nxt;ll w;}e[N<<1];
int cnt=1,head[N];ll num[N];
void add(int u,int v,ll w){e[++cnt]=(edge){u,v,head[u],w};head[u]=cnt;}
ll inline read()
{
	ll num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+ch-'0';ch=getchar();}
	return num*f;
}
void _print(ll num)
{
	if(num>9)_print(num/10);
	putchar(num%10+'0');
}
void print(ll x)
{
	if(x<0)putchar('-'),x=-x;
	_print(x);puts("");
}
int dep[N];ll f[N],dis[N];
void dfs(int u,int fa)
{
	f[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa)continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
		f[u]+=f[v];
	}
}
void calc(int u,int fa)
{
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa)continue;
		dis[v]=dis[u]+(-4*f[v]+2ll*n)%mod*e[i].w;
		dis[v]=(dis[v]%mod+mod)%mod;
		calc(v,u);
	}
}
int main(){
//	freopen("city4.in","r",stdin);
//	freopen("city4.out","w",stdout);
	n=read();q=read();
	for(int i=1;i<n;i++)
	{
		int u,v;ll w;
		u=read();v=read();w=read();
		add(u,v,w);add(v,u,w);
	}
	rt=1;
	dep[rt]=1;dfs(rt,0);
	dis[rt]=0;calc(rt,0);
	for(int i=1;i<n;i++)
	{
		int u=e[i<<1].u,v=e[i<<1].v;ll w=e[i<<1].w;
		if(dep[u]>dep[v])swap(u,v);
		num[i]=(2*f[v]*(n+1-f[v]))%mod;
		ans=(ans+num[i]*w)%mod;
	}
	for(int i=1;i<=q;i++)
	{
		int u=read(),v=n+1;ll w=read();
		ll Ans=ans+2ll*n*w+dis[u];
		print((Ans%mod+mod)%mod);
	}
	return 0;
}
```

完结撒花！

---

## 作者：rainygame (赞：0)

想不到再普及组比赛遇到了换根，而且居然没有 A 掉，大耻！

有一个非常显然的想法是：求出其余 $n-1$ 个点到 $i$ 点的距离和 $f_i$，每次询问的答案即为 $\sum\limits_{i=1}^nf_i+2(f_k+nw)$（注意此处 $\sum\limits_{i=1}^nf_i$ 可以再询问前就预处理出，所以处理单个询问的时间复杂度为 $O(1)$）。

那么现在的难点就在于如何快速的求出 $f_i$ 了，如果用传统的方法枚举每个点为根，然后 $O(n)$ 求答案的话，预处理的时间复杂度为 $O(n^2)$，无法通过。

但是我们可以考虑换根 DP。首先当然是求出 $f_1$ 的值，然后考虑状态转移：

当根从 $u$ 转移到 $v$ 时，$v$ 原来的子树不变，而除原以 $v$ 为根的子树的其它部分却变成了 $v$ 的子树，而且这些部分是以 $u$ 为根的，且与 $u$ 的唯一简单路径均经过 $e_{u \rightarrow v}$ 这条边（可以自行画图理解）。

因此我们考虑变化：原以 $v$ 为根的子树对 $f_u$ 的贡献 $siz_v \times w_{u\rightarrow v}$ 被消除，而其它部分对 $f_u$ 的贡献也添加了 $(n-siz_v)\times w_{u\rightarrow v}$。所以可得转移方程为：

$$
f_v=f_u+(n-2siz_v)\times w_{u\rightarrow v}
$$

注意 $siz$ 也需要更新，原 $siz_u$ 需要改为 $n-siz_v$，原 $siz_v$ 需要改为 $n$。

思路大体就是这个样子了。**但是要注意，一定要多取模！就算开了 `long long` 也要多取模，不然就会向我一样挂分！**

时间复杂度 $O(n+q)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 200001
const int MOD(998244353);

int n, q, u, v, w, ans;
int siz[MAXN], f[MAXN];

struct Edge{
	int v, w;
};
vector<Edge> e[MAXN];

int dfs(int x, int fa){
	siz[x] = 1;
	int res(0);
	for (auto i: e[x]){
		int v(i.v);
		if (v != fa){
			res = (res + dfs(v, x) + (siz[v] * i.w) % MOD) % MOD;
			siz[x] += siz[v];
		}
	}
	return res;
}

void dfs2(int x, int fa){
	for (auto i: e[x]){
		int v(i.v);
		if (v != fa){
			f[v] = f[x] + ((n-(siz[v]<<1)) * i.w) % MOD;
			if (f[v] < 0){
				f[v] += (llabs(f[v]) / MOD + 1) * MOD;
				f[v] %= MOD;
			}
			siz[x] = n-siz[v];
			siz[v] = n;
			dfs2(v, x);
		}
	}
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> q;
    for (int i(1); i<n; ++i){
    	cin >> u >> v >> w;
    	e[u].push_back({v, w});
    	e[v].push_back({u, w});
	}
	f[1] = dfs(1, 0);
	dfs2(1, 0);
	for (int i(1); i<=n; ++i) ans = (ans + f[i]) % MOD;
	
	while (q--){
		cin >> u >> w;
		cout << (ans + (w*n + f[u]) * 2) % MOD << '\n';
	}

    return 0;
}

```


---

