# [PumpkinOI Round 1] 造树据

## 题目背景

> 拍上了，舒服。

## 题目描述

小 P 正在造数据对拍，可是他拍了 $114514$ 组都没有拍出来。他去请教大佬，但被大佬 D 了，他被告知他随机生成树的期望高度是 $O(\log n)$ 的，强度不够。

小 P 很难过，以至于无法思考。所以他想请问你，对于他给出的任意一棵**无根树**，以他的随机生成方式，生成出与其形态相同的树即与其**同构**的树的概率。

小 P 随机生成一棵**无根树**的方式为：

- 对于 $2\le i\le n$ 的结点，等概率向 $[1,i-1]$ 中连一条边 

## 说明/提示

**本题采用子任务捆绑/依赖**

对于 $10\%$ 的数据，保证 $2\le n\le 10$。

对于 $30\%$ 的数据，保证 $2\le n\le 20$。

对于 $50\%$ 的数据，保证 $2\le n\le 10^3$。

对于另外 $10\%$ 的数据，保证给出的是一条链。

对于另外 $10\%$ 的数据，保证给出的树按照题面中小 P 随机生成树的方式生成。

对于 $100\%$ 的数据，$2\le n\le 5\times 10^5$。


## 样例 #1

### 输入

```
3
1 3
2 3```

### 输出

```
1```

## 样例 #2

### 输入

```
5
5 3
2 3
1 4
4 3```

### 输出

```
83187030```

## 样例 #3

### 输入

```
5
1 3
4 1
2 4
3 5```

### 输出

```
332748118```

# 题解

## 作者：pyiming (赞：3)

由于 $fa_u<u$，显然原问题可以转化为给树上对应结点标号。（即树上拓扑序）

考虑树形 dp。对于子树 $u$，编号最小的肯定是根结点。剩下的 $siz_u-1$ 个编号要依次分给每个子树，则方案数为 $\frac{(siz_u-1)!}{\Pi_{v\in son_u}siz_v!}$。但是我们注意到，对于两个同构的子树，显然，他们之间的编号分配是等价的。所以要用树哈希来判同构，则可以将所有子树中同构的分成一组。假设有 $k$ 组，第 $i$ 组大小为 $cnt_i$，则 $f(u)=\frac{(siz_u-1)!\times \Pi_{v\in son_u}f(v)}{\Pi_{v\in son_u}siz_v!\times \Pi_{i=1}^k cnt_i!}$。

考虑统计答案，由于题意中给出的是无根树，所以要换根统计 $f(u)$ 的和。注意到，同构的两棵树答案显然只用每统计一次，同时对树哈希换根即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=5e5;
const int mod=998'244'353;
struct modint{
    int v;
    modint():v(0){}
    modint(int x):v(x){}
    modint operator+(modint o){
        int t=v+o.v;
        if(t>=mod){
            t-=mod;
        }
        return {t};
    }
    modint operator-(modint o){
        int t=v-o.v;
        if(t<0){
            t+=mod;
        }
        return {t};
    }
    modint operator*(modint o){
        return {1ll*v*o.v%mod};
    }
};
struct IO{
    int n;
    int u[N+2],v[N+2];
    void init(){
        cin>>n;
        for(int i=1;i<n;i++){
            cin>>u[i]>>v[i];
        }
    }
    modint ans;
    void output(){
        cout<<ans.v<<"\n";
    }
};
modint qpow(modint a,ll b){
    modint ans=1;
    while(b){
        if(b&1){
            ans=ans*a;
        }
        a=a*a;
        b>>=1;
    }
    return ans;
}
struct Comb{
    modint fac[N+2],inv[N+2];
    Comb(){
        fac[0]=1;
        for(int i=1;i<=N;i++){
            fac[i]=fac[i-1]*modint(i);
        }
        inv[N]=qpow(fac[N],mod-2);
        for(int i=N-1;i>=0;i--){
            inv[i]=inv[i+1]*modint(i+1);
        }
    }
};
struct solution{
    IO io;
    solution(IO io):io(io){}
    vector<int> e[N+2];
    void prework(){
        for(int i=1;i<io.n;i++){
            e[io.u[i]].push_back(io.v[i]);
            e[io.v[i]].push_back(io.u[i]);
        }
    }
    ull h(ull x){
		return x*x*123+x*567+8910;
	}
	ull g(ull x){
		return h(x&((1ull<<32)-1))+h(x>>32);
	}
    int siz[N+2];
    modint f[N+2];
    ull Hash[N+2];
    map<ull,int> mp[N+2];
    Comb c;
    void dfs1(int u,int fa){
        siz[u]=1;
        f[u]=1;
        Hash[u]=1;
        for(int v:e[u]) if(v!=fa){
            dfs1(v,u);
            siz[u]+=siz[v];
            f[u]=f[u]*f[v]*c.inv[siz[v]];
            Hash[u]+=g(Hash[v]);
            f[u]=f[u]*qpow(++mp[u][Hash[v]],mod-2);
        }
        f[u]=f[u]*c.fac[siz[u]-1];
    }
    map<ull,int> flag;
    void dfs2(int u,int fa){
        if(!flag[Hash[u]]){
            io.ans=io.ans+f[u];
            flag[Hash[u]]=1;
        }
        for(int v:e[u]) if(v!=fa){
            f[u]=f[u]*(mp[u][Hash[v]]--);
            f[u]=f[u]*qpow(f[v],mod-2)*c.fac[siz[v]]*c.inv[io.n-1]*c.fac[io.n-siz[v]-1];
            Hash[u]-=g(Hash[v]);
            Hash[v]+=g(Hash[u]);
            f[v]=f[v]*f[u]*c.inv[io.n-siz[v]]*c.inv[siz[v]-1]*c.fac[io.n-1];
            f[v]=f[v]*qpow((++mp[v][Hash[u]]),mod-2);
            dfs2(v,u);
            f[v]=f[v]*(mp[v][Hash[u]]--);
            f[v]=f[v]*qpow(f[u],mod-2)*c.fac[io.n-siz[v]]*c.fac[siz[v]-1]*c.inv[io.n-1];
            Hash[v]-=g(Hash[u]);
            Hash[u]+=g(Hash[v]);
            f[u]=f[u]*f[v]*c.inv[siz[v]]*c.fac[io.n-1]*c.inv[io.n-siz[v]-1];
            f[u]=f[u]*qpow((++mp[u][Hash[v]]),mod-2);
        }
    }
    void solve(){
        prework();
        dfs1(1,0);
        io.ans=0;
        dfs2(1,0);
        io.ans=io.ans*c.inv[io.n-1];
    }
};
int main(){
    // freopen("data.in","r",stdin);
    cin.tie(0)->sync_with_stdio(0);
    IO io;
    io.init();
    solution s(io);
    s.solve();
    s.io.output();
    return 0;
}
```

---

## 作者：qczrz6v4nhp6u (赞：1)

并不是很困难的题，不懂为啥赛时只过了 6 个人。

### Solution

首先将概率转化为计数方案数。注意到生成方式实际上生成的是有根树，考虑枚举每一个点为根，并将形成的所有有根树去重后对应的答案加起来。

指定根后一种合法的标号方式给出了有根树的一个拓扑序，并且不同的根之间不会算重。根据结论：有根树的拓扑序数量为 $n!\prod_{i=1}^n\frac{1}{siz_i}$，对这个换根 dp，写一下发现过不了第一个样例，这是怎么回事呢。

手玩一下发现对于一个节点的两个同构的儿子子树，他们其实是互不区分的。所以还要对于每一个点的每一个儿子的子树，划分等价类后除以每个等价类大小的阶乘。

换根 dp 部分是平凡的，不再赘述。

可能需要带 $\log$。

### Code

```cpp
bool Mst;
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=5e5+5,mod=998244353;
const ull mask=chrono::steady_clock::now().time_since_epoch().count();
inline ull shift(ull x){
	x^=mask;
	x^=x<<7;
	x^=x>>13;
	x^=x<<17;
	x^=x>>23;
	x^=mask;
	return x;
}
inline ll qpow(ll a,ll b){
	ll res=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)res=res*a%mod;
	return res;
}
int n;vector<int> Gr[N];
ll fac[N],ifac[N],inv[N];
void init(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	ifac[n]=qpow(fac[n],mod-2);
	for(int i=n;i>=1;i--)ifac[i-1]=ifac[i]*i%mod;
	for(int i=1;i<=n;i++)inv[i]=ifac[i]*fac[i-1]%mod;
}
int siz[N];ull h[N];ll f[N];unordered_map<ull,int> g[N];
void dfs1(int x,int fa){
	siz[x]=h[x]=f[x]=1;
	for(auto &y:Gr[x])
		if(y!=fa){
			dfs1(y,x);
			siz[x]+=siz[y];
			h[x]+=shift(h[y]);
			f[x]=f[x]*f[y]%mod*inv[++g[x][h[y]]]%mod;
		}
	f[x]=f[x]*inv[siz[x]]%mod;
}
void dfs2(int x,int fa){
	for(auto &y:Gr[x])
		if(y!=fa){
			int tsiz=siz[x];
			ull th=h[x];
			ll tf=f[x];
			
			f[x]=f[x]*siz[x]%mod;
			siz[x]-=siz[y];
			f[x]=f[x]*inv[siz[x]]%mod;
			h[x]-=shift(h[y]);
			f[x]=f[x]*qpow(f[y],mod-2)%mod*g[x][h[y]]%mod;
			
			f[y]=f[y]*siz[y]%mod;
			siz[y]+=siz[x];
			f[y]=f[y]*inv[siz[y]]%mod;
			h[y]+=shift(h[x]);
			f[y]=f[y]*f[x]%mod*inv[++g[y][h[x]]]%mod;
			
			dfs2(y,x);
			
			siz[x]=tsiz;
			h[x]=th;
			f[x]=tf;
		}
}
pair<ull,ll> ans[N];int len;
bool Med;
int main(){
	cerr<<abs(&Mst-&Med)/1048576.0<<endl;
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;init(n);
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		Gr[u].emplace_back(v);
		Gr[v].emplace_back(u);
	}
	dfs1(1,0),dfs2(1,0);
	for(int i=1;i<=n;i++)ans[i]=make_pair(h[i],f[i]);
	sort(ans+1,ans+n+1);
	len=unique(ans+1,ans+n+1)-ans-1;
	ll sum=0;
	for(int i=1;i<=len;i++)sum+=ans[i].se;
	cout<<sum%mod*n%mod<<'\n';
	return 0;
}
```

---

