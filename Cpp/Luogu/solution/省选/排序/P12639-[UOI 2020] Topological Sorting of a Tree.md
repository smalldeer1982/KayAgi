# [UOI 2020] Topological Sorting of a Tree

## 题目描述

给定一棵包含 $n$ 个顶点的树，顶点编号从 $1$ 到 $n$。树的根节点是编号为 $1$ 的顶点。对于每个 $v$（从 $2$ 到 $n$），定义 $p_v$ 为与 $v$ 相邻且在 $v$ 到根节点路径上的顶点编号。每条边 $(p_v, v)$ 上都标有符号 $\tt{<}$ 或 $\tt{>}$。

求将数字 $1$ 到 $n$ 填入树的所有顶点中的方案数，要求每个数字恰好使用一次，且满足所有边上标明的约束关系。具体来说：
- 对于标有 $\tt{<}$ 的边，需满足 $a[p_v] < a[v]$
- 对于标有 $\tt{>}$ 的边，需满足 $a[p_v] > a[v]$

由于答案可能很大，请输出对 $10^9 + 7$ 取模的结果。

## 说明/提示

- （$8$ 分）$n \leq 10$；
- （$6$ 分）$n \leq 18$；
- （$10$ 分）所有 $c_i = \tt{<}$；
- （$4$ 分）所有 $p_i = 1$；
- （$13$ 分）$p_i = i - 1$，且 $1 \leq n \leq 200$；
- （$19$ 分）所有 $p_i = i - 1$；
- （$24$ 分）$n \leq 200$；
- （$16$ 分）无额外限制。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
1 <
2 <
3 >```

### 输出

```
3```

## 样例 #2

### 输入

```
4
1 <
1 <
1 <```

### 输出

```
6```

## 样例 #3

### 输入

```
5
1 <
1 <
3 >
3 >```

### 输出

```
18```

# 题解

## 作者：Mirasycle (赞：4)

UOI 怎么考板子题？？经典树上拓扑序容斥。

将填入数字看成拓扑序，如果全部都是 $<$ 的话很好办，那就是外向树拓扑序个数，为 $\dfrac{n!}{\prod size_u}$。

现在我们多了内向边，于是需要把他们容斥掉。假设钦定了 $c$ 条符号为 $>$ 的边不满足性质（变成了 $<$ 号的边），那么就有 $(-1)^c$ 的系数。这样子最后会形成一个森林，一颗树的内部有拓扑序要求，树和树之间无要求。合并两颗大小分别为 $n$ 和 $m$ 的树的方案数为将排名 $[1,2\dots n]$ 和排名 $[1,2\dots m]$ 整合到排名 $[1,2\dots n+m]$ 的方案数，你只需要在这 $n+m$ 个位置中选 $n$ 个位置依次填入原排名为 $1,2\dots n$ 的数即可，那么就是 ${n+m\choose n}$。

考虑带着容斥系数进行 dp，每钦定一条边就 $\times (-1)$。

由于贡献系数是和子树大小相关的，所以我们要在 dp 的时候记录当前联通块的大小。所有设 $f_{u,i}$ 表示在 $u$ 点的时候其所在联通块大小为 $i$ 的时候的带着容斥系数的方案数之和。根据拓扑序公式，每次遇到一个大小为 $i$ 的子树都要乘上 $\dfrac{1}{i}$ 的贡献，**这个我们放在最后乘，下面的转移式子中不讨论这一项**。

在遇到 $<$ 的时候，就是 $\dfrac{n!}{\prod sz_i}$ 和 $\dfrac{m!}{\prod sz_i}$ 变成 $\dfrac{(n+m)!}{\prod sz_i}$，我们发现这个变化恰好是 $\dfrac{(n+m)!}{n!\times m!}={n+m\choose n}$。

$$f_{u,i+j}\gets f_{u,i}\times f_{v,j}\times {sz_u+sz_v\choose sz_u}$$

在遇到 $>$ 的时候，可以选择不钦定那么就是任意顺序，是森林的合并，有系数 ${sz_u+sz_v\choose sz_u}$，或者钦定为 $<$，和第一个转移系数相同就是多了一个 $-1$。

$$f_{u,i+j}\gets -f_{u,i}\times f_{v,j}\times {sz_u+sz_v\choose sz_u}$$

$$f_{u,i}\gets f_{u,i}\times f_{v,j}\times {sz_u+sz_v\choose sz_u}$$

注意每次做完转移之后要 $f_{u,i}\gets f_{u,i}\times \dfrac{1}{i}$。

时间复杂度 $O(n^2)$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=3e3+10;
const int mod=1e9+7;
void add(int &x,int y){ x=x+y>=mod?x+y-mod:x+y; }
void sub(int &x,int y){ x=x<y?x-y+mod:x-y; }
vector<pair<int,int> > G[maxn]; 
int n,f[maxn][maxn],g[maxn],sz[maxn];
int C[maxn][maxn],inv[maxn],fac[maxn];
void dfs(int u,int fa){
	f[u][1]=1; sz[u]=1;
	for(auto z:G[u]){
		int v=z.fi,w=z.se;
		dfs(v,u);
		if(w){
			for(int i=1;i<=sz[u];i++)
				for(int j=1;j<=sz[v];j++)
					add(g[i+j],1ll*f[u][i]*f[v][j]%mod*C[sz[u]+sz[v]][sz[u]]%mod);
		}else{
			for(int i=1;i<=sz[u];i++)
				for(int j=1;j<=sz[v];j++){
					sub(g[i+j],1ll*f[u][i]*f[v][j]%mod*C[sz[u]+sz[v]][sz[u]]%mod);
					add(g[i],1ll*f[u][i]*f[v][j]%mod*C[sz[u]+sz[v]][sz[u]]%mod);
				}
		}
		sz[u]+=sz[v];
		for(int i=1;i<=sz[u];i++) f[u][i]=g[i],g[i]=0;
	}
	for(int i=1;i<=sz[u];i++) f[u][i]=1ll*f[u][i]*inv[i]%mod;
}
void init(){
	inv[1]=fac[0]=1; C[0][0]=1;
	for(int i=1;i<=n;i++) fac[i]=1ll*i*fac[i-1]%mod;
	for(int i=2;i<=n;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n; init();
	for(int v=2;v<=n;v++){
		int u,t=0; char ch;
		cin>>u>>ch; t^=(ch=='<');
		G[u].pb(v,t);
	}
	dfs(1,0); int ans=0;
	for(int i=1;i<=n;i++) add(ans,f[1][i]);
	cout<<ans<<endl;	
	return 0;
}
```

---

## 作者：Shunpower (赞：0)

这其实就是 [P4099 [HEOI2013] SAO](https://www.luogu.com.cn/problem/P4099)。提供这个题简单的做法。

自然地，设 $f_{i,j}$ 表示 $i$ 子树内填满，根节点排名为 $j$ 的方案数。

考虑树形背包时合并，我们把一个儿子 $v$ 合并到 $u$ 为根的子树内。

不妨设当前 $u$ 排名为 $j$，$v$ 排名为 $k$，新的 $u$ 排名为 $i$。符号不妨设为 $<$（另一侧是对称的），考虑条件：

- $u$ 前面需要有 $i-j$ 个从 $v$ 子树内插进来的数。由于 $v$ 要在 $u$ 后面，所以要满足 $i-j<k$。

考虑系数：

- 刚刚那些数的插入方法数显然等价于把 $i-j$ 个球放入 $j$ 个可空的盒子里，方案数是 ${i-1\choose j-1}$。
- 然后考虑 $i$ 后面的部分。这部分还有 $siz_u-j+1$ 个空位，需要插入剩下的 $siz_v-(i-j)$ 个数，于是方案数是 ${siz_u+siz_v-i\choose siz_u-j}$。

于是我们可以写出 $<$ 这一部分的转移式了：

$$
\sum\limits_{j=1}^{siz_u}\sum\limits_{k=i-j+1}^{siz_v} f_{u,i}\gets f_{u,j}f_{v,k}{i-1\choose j-1}{siz_u+siz_v-i\choose siz_u-j}
$$

注意到整个系数和 $k$ 无关，所以把 $k$ 的部分独立出去做前缀和优化，记为数组 $s_y$，我们有：

$$
\sum\limits_{j=1}^{siz_u} f_{u,i}\gets f_{u,j}(s_{y,siz_y}-s_{y,i-j}){i-1\choose j-1}{siz_u+siz_v-i\choose siz_u-j}
$$

最后考虑 $i$ 的界。注意到 $i$ 至少要继承 $j$ 前面的数，所以 $i\ge j$，但是最多也只会插入 $siz_v$ 个数在前面，所以 $i\le j+siz_v$。

两层循环分别是 $siz_u,siz_v$，直接使用树形背包的复杂度证明，复杂度为 $\mathcal O(n^2)$。

代码写得略乱。

```cpp
int n;
int type[N];
vector <int> p[N];
int dp[N][N],sum[N][N];
int tmp[N];
int siz[N];
const int mod=1e9+7;
void add(int &x,int y){
    x+=y;
    if(x>=mod) x-=mod;
}
ll qpow(ll b,int p){
    if(!p) return 1;
    ll d=qpow(b,p>>1);
    if(p&1) return d*d%mod*b%mod;
    else return d*d%mod;
}
int fac[N],ifac[N];
int C(int n,int m){
    if(n<0||m<0||n<m) return 0;
    return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
mt19937 rnd(time(0));
void dfs(int x){
    dp[x][1]=1;
    siz[x]=1;
    shuffle(p[x].begin(),p[x].end(),rnd);
    for(auto y:p[x]){
        dfs(y);
        fr1(i,1,siz[x]+siz[y]) tmp[i]=0;
        fr1(j,0,siz[x]){
            fr1(i,j,j+siz[y]){
                int d=i-j;
                if(type[y]) add(tmp[i],1ll*dp[x][i-d]*sum[y][d]%mod*C(i-1,d)%mod*C(siz[x]+siz[y]-i,siz[x]-j)%mod);
                else add(tmp[i],1ll*dp[x][i-d]*(sum[y][siz[y]]+mod-sum[y][d])%mod*C(i-1,d)%mod*C(siz[x]+siz[y]-i,siz[y]-d)%mod);
            }
        }
        siz[x]+=siz[y];
        fr1(i,1,siz[x]){
            dp[x][i]=tmp[i];
        }
    }
    fr1(i,1,siz[x]){
        sum[x][i]=sum[x][i-1];
        add(sum[x][i],dp[x][i]);
    }
}
int main(){
#ifdef Ltp
    freopen("hack.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);
    cin>>n;
    fr1(i,2,n){
        int f;
        char c;
        cin>>f>>c;
        type[i]=(c=='>');
        p[f].pb(i);
    }
    fac[0]=1;
    fr1(i,1,n) fac[i]=1ll*fac[i-1]*i%mod;
    ifac[n]=qpow(fac[n],mod-2);
    fr2(i,n-1,0) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
    dfs(1);
    int ans=0;
    fr1(i,1,n) add(ans,dp[1][i]);
    cout<<ans<<'\n';
    ET;
}
//ALL FOR Zhang Junhao.
```

---

