# [ICPC 2021 Macao R] Permutation on Tree

## 题目描述

给定一个有 $n$ 个顶点的树，其中顶点 $r$ 是根，如果一个排列 $p_1, p_2, \cdots, p_n$ 满足以下约束条件，我们称其为好排列：

- 设 $a_x$ 是排列中 $x$ 的索引（即 $p_{a_x} = x$）。对于所有 $1 \le u, v \le n$，如果顶点 $u$ 是树中顶点 $v$ 的祖先，则 $a_u < a_v$。

定义排列的分数为 $\sum\limits_{i=1}^{n-1} |p_i - p_{i+1}|$，其中 $|x|$ 表示 $x$ 的绝对值。计算所有不同好排列的分数之和。

## 样例 #1

### 输入

```
4 2
1 2
2 3
1 4```

### 输出

```
15```

## 样例 #2

### 输入

```
3 1
1 2
2 3```

### 输出

```
2```

# 题解

## 作者：cyffff (赞：4)

[$\text{Link}$](https://www.luogu.com.cn/problem/P9663)

## 题意

给定一颗叶向树，求所有合法拓扑序 $p$ 的 $\sum_{i=2}^n|p_i-p_{i-1}|$ 之和，对 $10^9+7$ 取模。

$n\le200$。

## 思路

考虑求一颗树的拓扑序数量，定义 $g_x$ 为 $x$ 子树内拓扑序的数量，$sz_x$ 为 $x$ 子树大小。考虑 $x$ 不同子树之间无限制，而 $x$ 必须摆在第一位，显然有

$$g_x=\binom{sz_x-1}{sz_{t_1},sz_{t_2},\dots,sz_{t_k}}\prod_{i=1}^kg_{t_i}$$

其中 $t_{1\sim k}$ 为 $x$ 的儿子，多重组合数 $\binom{n}{s_1,s_2,\dots.s_k}$ 意义为把 $n$ 个数划分成 $k$ 个大小给定集合的方案数。

根据此式，我们可以算出 $\text{reduce}(x,p_1,\dots)$ 表示求 $x$ 子树去掉 $p_1,\dots$ 子树后合法拓扑序数量，其中 $p_{1\sim k}$ 均为 $x$ 的儿子，此函数时间复杂度为 $O(k)$，预处理 $g_x$ 逆元即可。

考虑枚举 $a,b$，计算它们在所有合法拓扑序中相邻的次数。
- $a,b$ 有祖先后代关系。那么此时 $a$ 一定是 $b$ 的父亲，考虑 $a$ 子树内所有拓扑序，那么 $b$ 一定在第二位，方案数为 $\text{reduce}(a,b)\cdot\binom{sz_a-2}{sz_b-1}\cdot g_b$。
- $a,b$ 无祖先后代关系。设 $c=\text{LCA}(a,b)$，$a',b'$ 分别为 $c$ 的 $a,b$ 方向的儿子。由于 $a,b$ 相邻，不妨先把 $a,b$ 子树拓扑序合并，方案数为 $\binom{sz_a+sz_b-2}{sz_a-1}\cdot g_ag_b$。考虑令 $f(u,v)$ 表示 $u,v$ 子树拓扑序拼起来有几个是 $a,b$ 相邻的，则 $f(fa_u,v)\gets f(u,v)\cdot\text{reduce}(fa_u,u)\cdot\binom{sz_{fa_u}+sz_v-2}{sz_u+sz_v-1}$，$f(u,v)\to f(u,fa_v)$ 同理。最后 $c$ 子树内 $a,b$ 相邻方案数就是 $f(a',b')\cdot\text{reduce}(c,a',b')\cdot\binom{c-2}{sz_{a'}+sz_{b'}-1}$。

子树内方案数容易推至全树方案数，总时间复杂度 $O(n^4)$。

考虑 $a,b$ 在 $f$ 转移式中无体现，考虑令原来 $a,b$ 时的 $f(u,v)$ 记作 $f'(a,b,u,v)$，新定义 $f(u,v)$ 为 $\sum_{a\in S_u}\sum_{b\in S_v}|a-b|f'(a,b,u,v)$，转移式不变，在 $fa_u=fa_v$ 时统计贡献，注意不能转移至 $u,v$ 有祖先后代关系的状态。子树方案数也可加起来一起推至全树，总时间复杂度 $O(n^2)$。

---

## 作者：Mashiroqwq (赞：2)

考虑枚举一个 $x \in [1,n)$，将 $\leq x$ 的看作 $0$，$>x$ 的看作 $1$，那么一个排列的贡献实际上就是 $\sum _{x=1}^{n-1}\sum [[p_i\leq x]+ [p_{i+1}>x]=1]$。

那么问题转变为一个给定一棵树，每一个点有权值 $0$ 或 $1$，求所有排布方案的贡献之和。

设 $f_x$ 表示 $x$ 子树内的排布方案树之和是多少。

设 $g_{x,k,0/1}$ 表示 $x$ 子树内所有排布方案中第 $k$ 个数是 $0$ 还是 $1$ 的排布方案有多少。

设 $h_{x,k}$ 表示 $x$ 子树内所有排布方案中第 $k$ 个数和第 $k+1$ 个数不同的方案数有多少。

在枚举一个 $x$ 的情况时，贡献就是 $\sum_{i=1}^{n-1} h_{r,i}$。

转移方程建议自己手推。容易发现复杂度为 $O(n^3)$。

```cpp
//code by Emissary
#include<bits/stdc++.h>

#define ll long long

using namespace std;

const int MAXN = 202;
const int mod = 1e9+7;

int n, r, siz[MAXN];
int val[MAXN], fac[MAXN<<1], ifac[MAXN<<1];
int head[MAXN], ne[MAXN<<1], to[MAXN<<1], cnt;
int f[MAXN], g[MAXN][MAXN][2], h[MAXN][MAXN], o[MAXN][MAXN][2], q[MAXN][MAXN];

inline void add(int x, int y){++cnt;to[cnt]=y;ne[cnt]=head[x];head[x]=cnt;}

inline int C(int x, int y){return x<y?0:1ll*fac[x]*ifac[y]%mod*ifac[x-y]%mod;}

inline ll Quickpow(ll x, ll y){
	ll z=1;
	while(y){
		if(y&1) z=z*x%mod;
		x=x*x%mod; y>>=1;
	}
	return z;
}

inline void dfs(int x, int fa){
	siz[x]=1; int lim;
	g[x][1][val[x]]=1; f[x]=1; 
	for(int i=head[x];i;i=ne[i]){
		if(to[i]==fa) continue;
		dfs(to[i],x);
		for(int j=0;j<=siz[x];++j) q[x][j]=h[x][j], h[x][j]=0;
		for(int j=2;j<=siz[x];++j)
			for(int k=1;k<=siz[to[i]];++k)
				(h[x][j+k-1]+=2ll*(1ll*g[to[i]][k][1]*g[x][j][0]%mod+1ll*g[to[i]][k][0]*g[x][j][1]%mod)%mod*C(j+k-3,j-2)%mod*C(siz[x]-j+siz[to[i]]-k,siz[x]-j)%mod)%=mod;
		(h[x][1]+=1ll*(1ll*g[to[i]][1][1]*g[x][1][0]%mod+1ll*g[to[i]][1][0]*g[x][1][1]%mod)*C(siz[x]-1+siz[to[i]]-1,siz[x]-1)%mod)%=mod;
		for(int j=2;j<siz[x];++j)
			for(int k=0;k<=siz[to[i]];++k)
				(h[x][j+k]+=1ll*q[x][j]*f[to[i]]%mod*C(j+k-2,k)%mod*C(siz[x]-j-1+siz[to[i]]-k,siz[to[i]]-k)%mod)%=mod;
		for(int k=1;k<siz[to[i]];++k)
			for(int j=1;j<=siz[x];++j)
				(h[x][j+k]+=1ll*h[to[i]][k]*f[x]%mod*C(j+k-2,j-1)%mod*C(siz[to[i]]-k-1+siz[x]-j,siz[x]-j)%mod)%=mod;	
		for(int j=0;j<=siz[x];++j) o[x][j][0]=g[x][j][0], o[x][j][1]=g[x][j][1], g[x][j][0]=g[x][j][1]=0;
		for(int j=2;j<=siz[x];++j){
			for(int k=0;k<=siz[to[i]];++k){
				(g[x][j+k][0]+=1ll*o[x][j][0]*f[to[i]]%mod*C(j+k-2,k)%mod*C(siz[x]-j+siz[to[i]]-k,siz[x]-j)%mod)%=mod;
				(g[x][j+k][1]+=1ll*o[x][j][1]*f[to[i]]%mod*C(j+k-2,k)%mod*C(siz[x]-j+siz[to[i]]-k,siz[x]-j)%mod)%=mod;
			}
		}
		for(int k=1;k<=siz[to[i]];++k){
			for(int j=1;j<=siz[x];++j){
				(g[x][j+k][0]+=1ll*g[to[i]][k][0]*f[x]%mod*C(j+k-2,j-1)%mod*C(siz[to[i]]-k+siz[x]-j,siz[x]-j)%mod)%=mod;
				(g[x][j+k][1]+=1ll*g[to[i]][k][1]*f[x]%mod*C(j+k-2,j-1)%mod*C(siz[to[i]]-k+siz[x]-j,siz[x]-j)%mod)%=mod;
			}
		}
		f[x]=1ll*f[x]*f[to[i]]%mod*C(siz[x]+siz[to[i]]-1,siz[to[i]])%mod; g[x][1][val[x]]=f[x]; 
		if(siz[x]>1) (h[x][1]+=1ll*q[x][1]*C(siz[x]+siz[to[i]]-2,siz[x]-2)%mod*f[to[i]]%mod)%=mod;
		siz[x]+=siz[to[i]];
	}
	return ;
}

inline void prework(int lim){
	fac[0]=ifac[0]=1;
	for(int i=1;i<=lim;++i) fac[i]=1ll*fac[i-1]*i%mod, ifac[i]=Quickpow(fac[i],mod-2);
	return ;
}

inline void clear(){
	memset(f,0,sizeof f);
	memset(g,0,sizeof g);
	memset(h,0,sizeof h);
	return ;
}

int main(){
	cin >> n >> r;
	prework(n<<1);
	for(int i=2;i<=n;++i){
		int x, y;
		cin >> x >> y;
		add(x,y), add(y,x);
	}
	int ans=0;
	for(int x=1;x<n;++x){
		for(int i=1;i<=n;++i) val[i]=(i>x);
		clear(); dfs(r,0);
		for(int i=1;i<n;++i) (ans+=h[r][i])%=mod;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

好题。

首先 $p$ 一定是一个拓扑序。然后我们考虑对每对相邻的 $p_i=a,p_{i+1}=b$ 的结构去计数其在多少个排列中出现了。

我们考虑相邻的 $a,b$ 是怎么产生的，对于点 $u$ 的两个儿子 $A,B$，其拓扑序中包含 $a,b$，我们将两个拓扑序列合并，并保证 $a,b$ 相邻，然后再后面的合并中把 $a,b$ 捆在一起作为一个元素。

不妨枚举 $a,b$ 在 $A,B$ 子树拓扑序中的位置 $i,j$， 那么合并后使得 $a,b$ 相邻（$a$ 在 $b$ 前面）的方案数就是 ${i+j-2 \choose i-1} \times {{sz_a+sz_b-i-j} \choose {sz_a-i}}$。这个部分暴力枚举是 $O(n^4)$ 的。

我们还需要知道 $a$ 在子树 $A$ 的拓扑序中位于第 $i$ 个的方案数，不妨记为 $dp_{A,i,a}$，考虑转移这个 dp，你发现枚举完 $a$ 后转移行如一个树上背包于是可以做到 $O(n^3)$。

考虑优化前面的暴力枚举，你发现枚举 $a$ 后使得 $a$ 产生贡献的 $b$ 是一个前缀，枚举 $b$ 后类似，于是对 $dp_{A,i,a}$ 处理一个第三维的前缀和数组即可做到 $O(n^3)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+7;
const int maxn = 214;
int sz[maxn],f[maxn],g[maxn];
int dp[maxn][maxn][maxn],pre[maxn][maxn][maxn];
int C[maxn][maxn];
int n,r;
vector<int> E[maxn];
void dfs1(int u,int fa){
    sz[u]=0;
    f[u]=1;
    for(int v:E[u]){
        if(v!=fa){
            dfs1(v,u);
            sz[u]+=sz[v];
            f[u]=f[u]*f[v]%mod*C[sz[u]][sz[v]]%mod;
        }
    }
    sz[u]++;
}
void dfs2(int u,int fa){
    for(int v:E[u]){
        if(v!=fa){
            g[v]=g[u];
            int siz=0;
            for(int w:E[u]){
                if(w!=fa&&w!=v){
                    siz+=sz[w];
                    g[v]=g[v]*f[w]%mod*C[siz][sz[w]]%mod;
                }
            }
            siz+=sz[v]-1;
            g[v]=g[v]*C[siz][sz[v]-1]%mod;
            dfs2(v,u);
        }
    }
}
int ans;
void dfs3(int u,int fa){
    dp[u][1][u]=f[u];
    for(int v:E[u]){
        if(v!=fa){
            dfs3(v,u);
            int fv=1;
            int siz=0;
            for(int w:E[u]){
                if(w!=v&&w!=fa) siz+=sz[w],fv=fv*f[w]%mod*C[siz][sz[w]]%mod;
            }
            for(int i=1;i<=sz[v];i++){
                for(int x=1;x<=n;x++){
                    for(int j=0;j<sz[u]-sz[v];j++){
                        //dp[v][i][x]->dp[u][i+j+1][x]
                        dp[u][1+i+j][x]=(dp[u][1+i+j][x]+dp[v][i][x]*fv%mod*C[i+j-1][i-1]%mod*C[sz[u]-1-j-i][sz[v]-i]%mod)%mod;
                    }
                }
            }
        }
    }
    for(int i=1;i<=sz[u];i++){
        for(int x=1;x<=n;x++){
            pre[u][i][x]=(pre[u][i][x-1]+dp[u][i][x])%mod;
        }
    }
    for(int x=1;x<=n;x++){
        ans=(ans+abs(x-u)*dp[u][2][x]%mod*g[u]%mod)%mod;
    }
    for(int v:E[u]){
        if(v!=fa){
            for(int w:E[u]){
                if(w!=fa&&w!=v){
                    //sub_v sub_w
                    //默认 v 子树中取的放前面
                    int sum=0;
                    for(int i=1;i<=sz[v];i++){
                        for(int j=1;j<=sz[w];j++){
                            int insv=C[i+j-2][i-1]*C[sz[v]+sz[w]-i-j][sz[v]-i]%mod;
                            //v 子树大
                            for(int x=1;x<=n;x++){
                                sum=(sum+insv*dp[v][i][x]%mod*pre[w][j][x]%mod*x%mod)%mod;
                                sum=(sum+insv*dp[w][j][x]%mod*((pre[v][i][n]+mod-pre[v][i][x])%mod)%mod*(mod-x)%mod)%mod;
                            }
                            //w 子树大  
                            for(int x=1;x<=n;x++){
                                sum=(sum+insv*dp[w][j][x]%mod*pre[v][i][x]%mod*x%mod)%mod;
                                sum=(sum+insv*dp[v][i][x]%mod*((pre[w][j][n]+mod-pre[w][j][x])%mod)%mod*(mod-x)%mod)%mod;
                            }
                        }
                    }
                    int siz=sz[v]+sz[w]-1;
                    for(int sub:E[u]){
                        if(sub!=fa&&sub!=v&&sub!=w){
                            siz+=sz[sub];
                            sum=sum*f[sub]%mod*C[siz][sz[sub]]%mod;
                        }
                    }
                    ans=(ans+sum*g[u]%mod)%mod;
                }
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>r;
    for(int i=0;i<=n;i++){
        C[i][0]=1;
        for(int j=1;j<i;j++){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
        }
        C[i][i]=1;
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs1(r,0);
    g[r]=1;
    dfs2(r,0);
    dfs3(r,0);
    cout<<ans<<"\n";
    return 0;
}
```

---

