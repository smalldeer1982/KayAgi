# Network Safety

## 题目描述

题意：

给你一个有$n$点个和$m$条边的图，第$i$个点的权值为$c_i$。

定义图为安全的条件对于所有的边都保证$c_l≠c_r$

请你求出对于任意的$x$，集合$s$中所有点的点权$xor\quad x$后图仍然安全，这样的$x$和$s$的组合的数量。

答案对于$1e9+7$取模

保证一开始给出的图是安全的。

## 样例 #1

### 输入

```
4 4 2
0 1 0 1
1 2
2 3
3 4
4 1
```

### 输出

```
50
```

## 样例 #2

### 输入

```
4 5 3
7 1 7 2
1 2
2 3
3 4
4 1
2 4
```

### 输出

```
96
```

# 题解

## 作者：zhaotiensn (赞：8)

显然对于所有边是否安全都没有关系的$x$，所能提供的贡献一定是$2^n$。显然这种情况对于每一个点都可以取或不取。

如果$x=c_l\quad xor \quad c_r$,那么$l$和$r$要么都选，要么都不选。那么我们可以把$l$和$r$看做一个点来处理，把它们变成一个联通块。这样的话贡献应该是$2^{size}$，$size$表示联通块的数量。

因为一共有$m$条边，所以最多有$m$个$x$对于边的状态有影响，可以考虑枚举$m$条边，计算出$x$，对于每一个$x$改变点的状态。

然后因为每一条边只会被改变一次，所以最多可以改变$m$次，时间复杂度为$O(m)$。

代码：
```
#include <algorithm>
#include <iostream>
#include <cstdio>

#define ll long long
#define Max 500005

using namespace std;

inline char gc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define gc getchar
inline ll read(){
    ll x=0;char ch=gc();bool positive=1;
    for(;!isdigit(ch);ch=gc())if(ch=='-')positive=0;
    for(;isdigit(ch);ch=gc())x=x*10+ch-'0';
    return positive?x:-x;
}

inline void write(ll x){
    if(x<0)x=-x,putchar('-');
    if(x>9)write(x/10);putchar(x%10+'0');
}

inline void writeln(ll x){
    write(x);puts("");
}//无用的快读快输

struct Node{
    ll l,r,num;
    inline bool operator<(const Node&x)const{
        return num<x.num;
    }
}e[Max];//存边

const ll mod=1e9+7;

ll n,m,k,s,cnt,ans,sum,size,a[Max],fa[Max];

inline ll find(ll x){//直接并查集维护联通块状态
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

inline ll pow(ll x,ll y){
    ll ans=1;
    while(y){
        if(y&1)ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}

int main(){
    n=read();m=read();k=read();
    for(ll i=1;i<=n;i++)a[i]=read();
    for(ll i=1;i<=m;i++){
        e[i].l=read();e[i].r=read();
        e[i].num=a[e[i].l]^a[e[i].r];
    }
    sort(e+1,e+m+1);
    for(ll i=1;i<=n;i++)fa[i]=i;
    s=1;
    for(ll i=2;i<=m;i++){//枚举x
        if(e[i].num!=e[i-1].num){
            cnt++;
            sum=n;//初始化
            for(ll j=s;j<i;j++){
                if(find(e[j].l)!=find(e[j].r)){
                    sum--;//改变联通块数量
                    fa[find(e[j].l)]=find(e[j].r);
                }
            }
            ans=(ans+pow(2ll,sum))%mod;//统计答案
            for(ll j=s;j<i;j++){//直接还原
                fa[e[j].l]=e[j].l;
                fa[e[j].r]=e[j].r;
            }
            s=i;
        }
    }
    sum=n;
    cnt++;
    for(ll i=s;i<=m;i++){
        if(find(e[i].l)!=find(e[i].r)){
            sum--;
            fa[find(e[i].l)]=find(e[i].r);
        }
    }
    ans=((ans+pow(2ll,sum))%mod+(pow(2ll,k)-cnt+mod)%mod*pow(2ll,n)%mod)%mod;//统计答案
    writeln(ans);
    return 0;
}

```

---

## 作者：redegg (赞：4)

设大写字母为点的编号，小写字母为对应大写字母点的值。

如果我框选了$A,B$两点，那么$A,B$两点无论感染了什么病毒，都不会破坏图的安全性（因为一开始图就是安全的，而两个不同数异或同一个数后也一定不同）。

那么现在破坏图的安全性只有一种可能，我选了$A$，没选$B$，而$a \oplus x=b$。

并且，由于异或的性质，我们可以直接算出$x$，$x=a\oplus b$。

对于一条边，我们知道了要让图不安全就是只选两端点中的一个并且病毒是两端点的异或值。

那么在病毒为$x=a\oplus b$时，我一定得选$AB$两点，所以我们可以把AB看做一个点。

我们合并点后$k$个点，这$k$点之间的异或值都不等于$x$了，我们可以有$2^k$个选法。

如何合并点并且求出合并后点的数量呢？用并查集，每次合并就是点数$-1$。

一切就很简单了，我们只需要得到一条边两端的异或值，然后就知道它会受到哪个病毒的影响了。

由于$n$很大，所以我们用$map$来存储。

具体看代码：

```
#include <bits/stdc++.h>
using namespace std;

long long mod=1e9+7;

int n,m,k;
long long b[500005];

long long ans;

map<long long,int> a;
map<long long,int> g[500005];

long long fast(long long x,int v)
{
    long long an=1;
    while(v)
    {
        if(v%2)
            an=(an*x)%mod;
        x=(x*x)%mod;
        v/=2;
    }
    return an;
}

int findfa(int x,long long key)
{
    if(g[x][key]==x)
        return x;
    return g[x][key]=findfa(g[x][key],key);
}

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    ans=(fast(2,k)*fast(2,n))%mod;
    for(int i=1;i<=n;i++)
        scanf("%lld",&b[i]);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        long long key=b[x]^b[y];
        if(g[x][key]==0)
            g[x][key]=x;
        if(g[y][key]==0)
            g[y][key]=y;
        if(findfa(x,key)==findfa(y,key))continue;
        else
            g[findfa(x,key)][key]=g[findfa(y,key)][key];
        ans=((ans-fast(2,n-a[key]))%mod+mod)%mod;
        a[key]++;
        ans=(ans+fast(2,n-a[key]))%mod;
    }
    printf("%lld",ans%mod);
    return 0;
}

```

---

## 作者：zhangzhixing99 (赞：3)

[更好的阅读体验（隐藏评论区）？](https://www.luogu.me/paste/fcnii3rf)
## 题目摘要
给一张带点权的图（网络结构），和一个整数 $k(k\isin[0,60])$。  
如果这张图是"安全"的，当且仅当每条边连接的两个点点权互不相同。
对于 $\forall x(x\isin[0,2^k-1])$，选出一个由点构成的集合 $s$，使得将 $s$ 中的所有点的点权全部 $\oplus x$ 后，图仍然"安全"。找出这样的 $x\& s$ 对的数量。  
上文中，$\oplus$ 代表[二进制异或运算](https://blog.csdn.net/2302_78926002/article/details/143086369)，而 $\&$ 并不代表二进制与运算，而是单纯的凑对关系。
## 前置知识
- 二进制异或运算的一些性质（这个后面会说到，这里就不贴链接了）
- [并查集](https://blog.dotcpp.com/a/76623)
- [快速幂](https://cloud.tencent.com/developer/article/2382608)
## 正题开始
既然提到了"异或"和边，我们可以先看看它们之间拥有什么样的关系。  
设边连结了点 $u$ 和 $v$，点权为 $c_u$ 和 $c_v$：  
如果 $a=c_u\oplus c_v$，则
- $a\oplus c_u=c_v$
- $a\oplus c_v=c_u$

当题中 $x$ 取 $a$ 时，如果 $u$ 选 $v$ 不选，或者 $v$ 选 $u$ 不选，都会导致修改后的 $u,v$ 点权相同。  
而剩下的情况，并不会导致最终两点点权相同（可自行证明）。  
于是我们在 $x$ 取 $c_u\oplus c_v$ 时合并两点即可。  
"合并操作"的实现方法可以使用并查集来维护。
## 实现方法
考虑如何统计答案。  
我们设 $S$ 为执行到这一步时，连通块的大小。  
在没有出现上述情况的条件下，每个点每个 $x$ 都可以选或不选，答案为 $2^{n+k}$。  
每次合并节点后，将答案减去 $2^{n-S}$ 后，合并联通块。  
然后将答案加上 $2^{n-S}$。  
算幂用快速幂即可。
## 时间复杂度
- 输入点权：$\Theta(n)$。
- 遍历边：$\Theta(m)$。
- 快速幂：$\Theta(\text{log}_2n)$。
- 并查集：$\Theta(\alpha(n))$，其中 $\alpha()$ 为[反阿克曼函数](https://baike.baidu.com/item/%E9%98%BF%E5%85%8B%E6%9B%BC%E5%87%BD%E6%95%B0?fromModule=lemma_search-box)。
- 总时间复杂度：$\Theta (n+m(\text{log}_2 n+\alpha(n)))$。
## 空间复杂度
- 点权：$\Theta(n)$。
- 并查集：虽然每个点都有很多种合并需要的权值，但是边数不超过 $m$ 条，所有可能的合并权值也只有 $m$ 种，总空间复杂度为 $\Theta(m)$ 。为了达到上述效果，我们可以使用查询及赋值只需要 $\Theta(1)$ 时间复杂度的[无序映射](https://blog.csdn.net/scm06111/article/details/142319330)。
- 总空间复杂度：$\Theta(n+m)$。
## 代码
码风不良，dalao 们不喜勿喷。
```cpp
#include <bits/stdc++.h>
using namespace std;

#define EOL '\n'

const int mod = 1e9 + 7;

int n, m, k;
long long w[500010];
unordered_map<long long, int> cnt, top[500010];
long long ans;

int Find(int u, long long key)
{
	if (u == top[u][key])
	{
		return u;
	}
	return top[u][key] = Find(top[u][key], key);
}

long long qpow(long long bas, long long t)
{
	long long ret = 1, mul = bas;
	while (t)
	{
		if (t & 1)
		{
			ret *= mul;
			ret %= mod;
		}
		mul *= mul;
		mul %= mod;
		t >>= 1;
	}
	return ret;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i)
	{
		cin >> w[i];
	}
	ans = qpow(2, n + k);
	for (int i = 1; i <= m; ++i)
	{
		int u, v;
		cin >> u >> v;
		long long x = w[u] ^ w[v];
		if (!top[u].count(x))
		{
			top[u][x] = u;
		}
		if (!top[v].count(x))
		{
			top[v][x] = v;
		}
		if (Find(u, x) == Find(v, x))
		{
			continue;
		}
		top[Find(v, x)][x] = Find(u, x);
		ans = ((ans - qpow(2, n - cnt[x])) % mod + mod) % mod;
		++cnt[x];
		ans = (ans + qpow(2, n - cnt[x])) % mod;
	}
	cout << ans << EOL;
	return 0;
}
```

---

## 作者：niuzh (赞：2)

#### 思路

对于边 $(u,v)$ 能让其变得不安全只可能是 $c_u \oplus x = c_v $ 或 $c_v \oplus x=c_u$。（因为此图最开始是安全的，所以不可能是 $c_u \oplus x=c_v \oplus x$）显然，$x$ 只能为 $c_u \oplus c_v$，将 $x$ 设为此边边权。

考虑对于 $0$ 到 $2^k-1$ 中的某值 $a$，$(S,a)$ 中 $S$ 的取值个数：

- 如果 $a$ 不等于任何一条边的边权，$S$ 有 $2^n$ 种取值。（对任意点异或都没事）
- 否则，由于边权等于 $a$ 的边要么不异或要么都异或，统计只保留边权等于 $a$ 的边后联通块个数为 $m$，$S$ 有 $2^m$ 种取值。

由于只有 $m$ 条边，最多只有 $m$ 种危险的 $x$，枚举即可。

#### 代码

```cpp
/*
 * @FilePath: test.cpp
 * @Author: niu-zh
 */
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10,mod=1e9+7;
int c[N];
map<int,int> cnt,fa[N];
set<int> s;
int qpow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1)
		{
			res=res*x%mod;
		}
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
int find(int x,int tmp)
{
	if (fa[x][tmp]==x)
	{
		return x;
	}
	return fa[x][tmp]=find(fa[x][tmp],tmp);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,m,k;
	cin>>n>>m>>k;
	for (int i=1; i<=n; i++)
	{
		cin>>c[i];
	}
	for (int i=1,x,y; i<=m; i++)
	{
		cin>>x>>y;
		int tmp=c[x]^c[y];
		s.insert(tmp);
		if (fa[x][tmp]==0)
		{
			fa[x][tmp]=x;
		}
		if (fa[y][tmp]==0)
		{
			fa[y][tmp]=y;
		}
		if (find(x,tmp)==find(y,tmp))
		{
			continue;
		}
		fa[find(x,tmp)][tmp]=fa[find(y,tmp)][tmp];
		cnt[tmp]++;
	}
	int ans=0;
	for(auto i:s)
	{
		ans+=(qpow(2,n-cnt[i]))%mod;
		ans%=mod;
	}
	cout<<(ans+(((qpow(2,k)-(int)s.size())*qpow(2,n))%mod))%mod;
	return 0;
}
```

---

## 作者：MoyunAllgorithm (赞：1)

非常良心的一道简单水题。

### 题目大意

有一张 $N$ 点 $M(\le 5 \times 10^5)$ 边的**安全的**图。第 $i$ 个点有权值 $c_i$。一张图被定义为“安全的”，当且仅当：

- 对于所有边 $(u,v)$，$c_u \neq c_v$。

请问有多少个二元组 $(x,S)(0 \le x \le 2^K-1,K \le 60)$ 满足将点集 $S$ 内的点的权值异或上 $x$ 后，图依旧安全？


### SOLUTION

对于边 $(u,v)$：如果存在 $(x,S)$ 让它变得危险，那么唯一的可能性是：

- $c_u \oplus x= c_v$ 或 $c_v \oplus x =c_u $；

- $u,v$ 中恰有一个在 $S$ 中。

**证明** 若 $u,v$ 都不在 $S$ 中，那就不会异或了，显然不是；若都在 $S$ 中，则有 $c_u \oplus x = c_v \oplus x$，即 $c_u=c_v$，不满足题意。

那可以得到：对于 $(u,v)$，唯一的 $x$ 满足 $x = c_u \oplus c_v$。当然，有很多可能的 $S$。

对于所有的 $x$：

- 若 $x$ 不构成危险，那么随便异或，即 $S$ 有 $2^N$ 种取值；

- 若 $x$ 构成危险：则对于所有危险的边 $(u,v)$，$u,v$ 必须要么都异或要么都不异或。这时它可被视作一个点。即，要用并查集维护现在还有哪些可以随意染色的点(包括危险边缩成的点）。$S$ 有 $2^n$（$n$ 为当前点数）种取值。

只有 $M$ 种危险的 $x$ 取值。枚举这些取值即可。

时间复杂度为 $O(M \log M+ M \alpha(M) )$。

实现细节：一个危险 $x$ 统计完后，并查集要清空。这是 $O(NM)$ 的。因此用 **栈** 存储在这一个 $x$ 中被合并的点，在这个 $x$ 点后只把这些 $x$ 的并查集清空。这样，是 $O(M)$ 的。

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <utility>
#include <queue>
#include <unordered_map>
#include <cstdlib>
#define LL long long
#define PII pair<int,int>
using namespace std;
const int MAXN=5e5+5;
const int MOD=1e9+7;
LL po[MAXN],c[MAXN];
LL ans;
int fa[MAXN],siz[MAXN];
int N,M,K;
struct Dangers
{
    int u,v;
    LL c;
    bool operator<(const Dangers &j) const
    {
        return c<j.c;
    }
}danger[MAXN];
int Find(int x)
{
    return fa[x]==x?x:fa[x]=Find(fa[x]);
}
void Merge(int u,int v,int &n)
{
    if(u==v) return;
    if(siz[u]<siz[v]) swap(u,v);
    fa[v]=u;
    siz[u]+=siz[v];
    n--;//在此处，两个合并说明少了一个点
    return;
}
int st[MAXN],tp=0;
int main()
{
    scanf("%d %d %d",&N,&M,&K);
    for(int i=1;i<=N;i++) scanf("%lld",&c[i]);
    po[0]=1;
    for(int i=1;i<=max(N,K);i++) po[i]=(po[i-1]<<1)%MOD;
    //预处理2的次幂
    for(int i=1;i<=N;i++)
    {
        fa[i]=i;
        siz[i]=1;
    }
    for(int i=1;i<=M;i++)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        danger[i]={u,v,c[u]^c[v]};
    }
    sort(danger+1,danger+M+1);//对危险排序
    ans=((po[K])*po[N])%MOD;
    int n=N;
    for(int i=1;i<=M;i++)
    {
        st[++tp]=danger[i].u;
        st[++tp]=danger[i].v;
        Merge(Find(danger[i].u),Find(danger[i].v),n);
        if(danger[i].c!=danger[i+1].c||i==M)
        {
            ans=((ans-po[N]+po[n])%MOD+MOD)%MOD;
            n=N;
            for(;tp;tp--) fa[st[tp]]=st[tp];
            tp=0;
        }
    }
    ans=(ans%MOD+MOD)%MOD;
    printf("%lld\n",ans);
    return 0;
}
```




---

## 作者：半笙、凡尘 (赞：1)

# CF1039C Network Safety

[~~为了尊重原版，这里把英文题面也留下。~~](http://codeforces.com/problemset/problem/1039/C)

感谢 [$zjwwjhy$](https://www.luogu.com.cn/user/81662) 的讲解。

---

- 题面

  The Metropolis computer network consists of nn servers, each has an encryption key in the range from $0$ to $2^k-1$ assigned to it. Let $c_i$ be the encryption key assigned to the $i$ -th server. Additionally, mm pairs of servers are directly connected via a data communication channel. Because of the encryption algorithms specifics, a data communication channel can only be considered safe if the two servers it connects have distinct encryption keys. The initial assignment of encryption keys is guaranteed to keep all data communication channels safe.

  You have been informed that a new virus is actively spreading across the internet, and it is capable to change the encryption key of any server it infects. More specifically, the virus body contains some unknown number $x$ in the same aforementioned range, and when server $i$ is infected, its encryption key changes from $ci$ to $ci$ $\oplus$ $x$, where $\oplus$ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).
  
  Sadly, you know neither the number $x$ nor which servers of Metropolis are going to be infected by the dangerous virus, so you have decided to count the number of such situations in which all data communication channels remain safe. Formally speaking, you need to find the number of pairs $(A,i)$, where $A$ is some (possibly empty) subset of the set of servers and $x$ is some number in the range from $0$ to $2^k-1$, such that when all servers from the chosen subset $A$ and none of the others are infected by a virus containing the number $x$ , all data communication channels remain safe. Since this number can be quite big, you are asked to find its remainder modulo $10^9+7$.


- 题意

  给出一个由 $n$ 个点 $m$ 条边组成的图，每个点有一个权值 $c_i$。保证给出的图是“安全”的。$(n \leq 500000,m \leq min(\frac{n*(n-1)}{2},500000),c_i \leq 2^k-1,k \leq 60)$
  
  对于“一个‘安全’的图”的定义是：对于这个图里所有的边的两端点都满足 $c_l \not = c_r$。
  
  现在对于任意一个 $x$ $(x \leq 2^k-1)$，图中任意数量的点组成的点集 $s$，求 $s$ 中所有的点 $xor$ $x$ 后，图仍然为“安全”的图，这样的 $x$ 和 $s$ 组合的方案数，答案对 $10^9+7$ 取模。
  
---

- 题解

  考虑下面这个样例 $n=4,m=4,k=2$ 的情况，很明显，当 $x=0,2,3$ 时都有 $2^4$ 种方案。
  只有当 $x=1$ 时，$0 \oplus 1=1$，会使图出现不安全的情况，那么使图为安全的方案只有全部 $xor$ $x$ 和全部不 $xor$ $x$ 两种方案。
  ![](https://i.loli.net/2020/11/23/Do9lEN8CH2UzMxs.png)
  
  那么就可以归纳出：如果对于一个 $x$，它对图是否安全不会产生影响（无论怎么操作，一定不会产生使图“不安全”的 $x$），它对答案的贡献一定是 $2^n$。所以我们只要考虑会对图是否“安全”产生影响的 $x$ 即可。
  
   对于一条边，当 $c_l \oplus x=c_r$ 时，要使图为安全的，只有这条边上两个点全部 $xor$ $x$ 和全部不 $xor$ $x$ 这两种情况，也就是都取，或者都不取两种情况。那么就可以抽象地把两个点看成一个点，用并查集去维护合并点的过程，每次合并点数都 $-1$。（如图中情况，每次把每条边上的两个点看成一个点，最终得到的只有一个点，那么就只有这个点 $xor$ $x$ 和不 $xor$ $x$ 两种方案。）
  
---

- 接下来就是一点也不激动人心的代码了：

```cpp
#include<bits/stdc++.h>
/* Forever_chen */
#define RT register
#define M 1000000007 
#define int long long
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
template<class t>inline void write(t x){
	if(x<0)putchar('-'),write(-x);
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}
template<class t>inline void writeln(t x){
	write(x);putchar('\n');
	return;
}
template<class t>inline void write_blank(t x){
	write(x);putchar(' ');
	return;
}
int n,m,k,a[500010],f[500010],cnt[500010],tot,ans,p[500010];
vector<int> qx[500010],qy[500010];
map<int,int>vis;
namespace bsfc{
	int quick_power(int x,int y){
		int ans=1,cnt=x;
		while(y){
			if(y&1){
				ans=ans*cnt%M;
			}
			cnt=cnt*cnt%M;
			y>>=1;
		}
		return ans;
	}
	int find(int k){
		if(f[k]==k){
			return k;
		}
		return f[k]=find(f[k]);
	}
} 
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n);
	read(m);
	read(k);
	for(int i=1;i<=n;i++){
		f[i]=i;
	}
	for(int i=1;i<=n;i++){
		read(a[i]);
	}
	for(int i=1;i<=m;i++){
		cnt[i]=n;
	}
	for(int i=1,l,r;i<=m;i++){
		read(l);
		read(r);
		if(vis[a[l]^a[r]]==0){
			tot++;
			vis[a[l]^a[r]]=tot;
		}
		p[vis[a[l]^a[r]]]++;
		qx[vis[a[l]^a[r]]].push_back(l);
		qy[vis[a[l]^a[r]]].push_back(r);
	}
	for(int i=1;i<=tot;i++){
		for(int j=0;j<p[i];j++){
			int fx=bsfc::find(qx[i][j]),fy=bsfc::find(qy[i][j]);
			if(fx!=fy){
				f[fx]=fy;
				cnt[i]--;
			}
		}
		for(int j=0;j<p[i];j++){
			f[qx[i][j]]=qx[i][j];
			f[qy[i][j]]=qy[i][j];
		}
		ans=(ans+bsfc::quick_power(2,cnt[i]))%M;
	}
	ans=(ans+((1ll<<k)-tot)%M*bsfc::quick_power(2,n)%M)%M;
	writeln(ans);
	//system("pause");
	return 0;
}
```


---

