# [COTS 2025] 发好奖 / Hijerarhija

## 题目描述


$N$ 个人的上下级关系构成一棵树。第 $1$ 个人为总监，第 $i$（$i\ge 2$）个人的直接上级为 $s_i$。

现在要给员工分配奖金。每个人的奖金可以是正整数，或者 $0$（没有奖金）。如果第 $i$ 个人获得了至少 $c_i$ 的奖金，下一年他的**积极性**会提高 $p_i$，否则积极性不会提高。

并非所有人都必须获得奖金，但是每个获得奖金的人的直接上级必须获得至少 $1$ 的奖金。

在发出的奖金总额不超过 $K$ 的前提下，求出积极性提高的总和最大值。

## 说明/提示


### 样例解释

样例 $2$ 解释：

一个合法的奖金分配方案：员工依次获得的奖金为 $1,1,0,2,3$。

分配方案 $1,1,1,2,3$ 不合法，因为奖金超支了。  

分配方案 $0,1,1,2,3$ 同样不合法，因为第 $2$ 个人获得了奖金，但其直接上级未获得。


### 数据范围

- $2\le N\le 5\, 000$；
- $1\le K\le 5\, 000$；
- $1\le p_i\le 10^5$；
- $1\le c_i\le 5\, 000$；
- $1\le s_i\lt i$；
- 输入的所有值均为整数。

### 子任务

子任务 $0$ 为样例。

其中，「$-$」表示「不保证」。

| 子任务编号 | $N\le$ | $K\le$ | 特殊性质 | 得分 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $20$ | $-$ | $-$  |  $7$ |
| $2$ | $-$ | $-$ | $\text{A}$ |  $9$ |
| $3$ | $-$ | $-$ | $\text{B}$ |  $14$ |
| $4$ | $500$ | $500$ | $-$  |  $19$ |
| $5$ | $100$ | $-$ | $-$ |  $21$ |
| $6$ | $-$ | $-$ | $-$ |  $30$ |

- 特殊性质 $\text{A}$：$c_i=1$，且 $j$ 是 $i$ 的上级 $\implies$ $p_j\ge p_i$。
- 特殊性质 $\text{B}$：$\forall 2\le i\le N$，$s_i=i-1$。

2025-06-03: 增加了一组 hack 数据

## 样例 #1

### 输入

```
2 100
1
10 10
101 100```

### 输出

```
0```

## 样例 #2

### 输入

```
5 7
1 1 2 2
2 1 2 3 3
4 2 4 2 3```

### 输出

```
6```

## 样例 #3

### 输入

```
4 9
1 2 2
3 4 4 2
2 5 5 4```

### 输出

```
7```

# 题解

## 作者：min_inf (赞：10)

神奇 trick。

在 DFS 序上 DP，设 $f_{i,j}$ 为 DFS 序在 $[1,i)$ 中的点代价为 $j$ 的答案。选 $i$ 这个点就转移到 $i+1$，不选就转移到 $end_i+1$（即这个子树外）。

```cpp
rep(i,1,n){
    int u=rdfn[i];
    rep(j,0,m){
        chkmax(dp[ed[u]+1][j],dp[i][j]);
        if(j<m)chkmax(dp[i+1][j+1],dp[i][j]);
        if(j+c[u]<=m)chkmax(dp[i+1][j+c[u]],dp[i][j]+p[u]);
    }
}
```

---

## 作者：gcx12012 (赞：8)

### 前言
不太正常的树形 dp。
### Solution
这里假定 $n,k$ 同阶。

首先 $O(n^3)$ 的树形背包是好想的，这里就不多说了。

然后发现树形背包的做法不太好优化至 $O(n^2)$，于是考虑改变转移方式。

这个题求的是有关包含点 $1$ 联通块的最大价值，于是考虑由某个节点转移到它的若干儿子。

这里推荐一个 dfs 写法：设当前考虑到节点 $u$，要转移到的儿子节点为 $v$，我们考虑先 $O(n)$ 转移到节点 $v$，然后直接递归至 $v$，到处理完子树 $v$ 后将 $f_u$ 的对应位置和子树内的每一个 $f_i$ 取 $\max$。

这样还是 $O(n^3)$ 的，此时我们可以在回溯的过程中将$f_u$ 直接和 $f_v$ 取 $\max$，这样是对的，因为经过这样的操作之后子树 $v$ 的 $f$ 已经预处理好了。

这么做是 $O(n^2)$ 的，完全可以通过，并且代码很短。
```
vector<int >e[N];
ll f[N][N],a[N],b[N];
int n,m;

ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void dfs(int u){
	for(int v:e[u]){
		For(i,0,m){
			if(i+1<=m) f[v][i+1]=max(f[v][i+1],f[u][i]);
			if(i+b[v]<=m) f[v][i+b[v]]=max(f[v][i+b[v]],f[u][i]+a[v]);
		}
		dfs(v);
		For(i,0,m) f[u][i]=max(f[u][i],f[v][i]);
	}
}

int main()
{
    //freopen("gcx.in","r",stdin);
    //freopen("gcx.out","w",stdout);
    n=read(),m=read();
    For(i,1,n){
    	For(j,0,m){
    		f[i][j]=-1e15;
    	}
    }
    For(i,2,n){
    	int u=read();
    	e[u].pb(i);
    }
    For(i,1,n) a[i]=read();
    For(i,1,n) b[i]=read();
    f[1][1]=0,f[1][b[1]]=a[1];
    dfs(1);
    ll ans=-1e15;
    For(i,0,m) ans=max(ans,f[1][i]);
    cout<<ans;
   	return 0;
}
```

---

## 作者：2019yyy (赞：4)

考虑到这是一个树形背包，无论怎么做都逃不掉背包卷积的复杂度，只能规避掉卷积这个事情。

接下来就是一个很难想到的 trick 了，我们可以在 dfs 序上 dp ，因为 dfs 序由大到小的转移完全满足给子节点发钱则必须发父亲这一性质。

对于一个点 $x$，如果至少在它的位置放了 $1$，那么就可以在它的子树内转移。（即向 $dfn_x+1$ 转移）

否则，则必须向它的子树外转移。（即向 $dfn_x+siz_x$ 转移）

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> g[110000];
int siz[110000],c[110000],v[110000],dfn[110000],cnt,f[5100][5100];
void dfs(int x){
    siz[x]=1,dfn[++cnt]=x;
    for(auto to:g[x]) dfs(to),siz[x]+=siz[to];
}
int main(){
    int n,m;cin>>n>>m;memset(f,-0x3f,sizeof(f));
    for(int i=2,x;i<=n;i++) cin>>x,g[x].push_back(i);
    int ans=0;dfs(1);f[1][0]=0;
    for(int i=1;i<=n;i++) cin>>v[i];
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1;i<=n;i++){
        int now=dfn[i];
		for(int j=0;j<=m;j++){
			f[i+siz[now]][j]=max(f[i+siz[now]][j],f[i][j]);
			if(j+1<=m) f[i+1][j+1]=max(f[i+1][j+1],f[i][j]);
			if(j+c[now]<=m) f[i+1][j+c[now]]=max(f[i+1][j+c[now]],f[i][j]+v[now]);
		}
    }
    for(int i=0;i<=m;i++) ans=max(ans,f[n+1][i]);
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：Hoks (赞：2)

## 前言
比较 tricky 的 dp 题。

同 trick 题：[P6326 Shopping](https://www.luogu.com.cn/problem/P6326)（要不是写过这个猫猫还真想不到）。
## 思路分析
直接来尝试暴力的设计 $f_{i,j}$ 表示 $i$ 这个子树用了 $j$ 的钱能得到的最大积极性。

然后你发现在合并的时候要把父亲的背包和每个子节点都合并过去，而且合并背包这个东西是 $O(m^2)$ 的。

这样总的复杂度就会是 $O(nm^2)$，无法通过本题。

优化点也自然就是在避免合并背包。

我们考虑把树拍成 dfn 序列，因为一个子节点如果要发钱父亲节点一定要发钱，所以我们考虑在 dfn 序上从小到大的转移。

此时我们需要考虑一个点从其兄弟节点并过来的贡献，复杂度还是 $O(nm^2)$。

考虑到对于一个点 $u$，如果选了他就可以继续在他的子树里转移，如果不选他那么只能去兄弟子树转移，所以我们不妨直接把他的贡献扔到对应的位置上去。

通过这个方法我们把每次的枚举变成了一次后置的转移（相当于合并了大量转移），复杂度变为 $O(nm)$。

具体的，对于点 $u$，设其 dfn 序为 $dfn_u$，其子树大小为 $si_u$，那么选择他则往 $dfn_u+1$ 转移，否则往 $dfn_u+si_u+1$ 转移。
## 代码
写完这题建议去看看 shopping 那题，很深刻。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
using namespace std;
const int N=5e3+10,M=2,V=1e6,INF=1e18;
int n,m,cnt,a[N],b[N],f[N][N<<1],dfn[N],ed[N],id[N];vector<int>e[N];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c=='?'||c=='<'||c=='='||c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline void dfs(int u)
{
	dfn[u]=++cnt;id[cnt]=u;
	for(auto v:e[u]) dfs(v);
	ed[u]=cnt;
}
inline void solve()
{
	n=read(),m=read();memset(f,-0x3f,sizeof f);
	for(int i=2;i<=n;i++) e[read()].emplace_back(i);
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read();dfs(1);
	f[1][0]=0;
	for(int i=1;i<=n;i++)
	{
		int u=id[i];
		for(int j=0;j<=m;j++)
		{
			f[ed[u]+1][j]=max(f[ed[u]+1][j],f[i][j]);
			f[i+1][j+1]=max(f[i+1][j+1],f[i][j]);
			f[i+1][j+b[u]]=max(f[i+1][j+b[u]],f[i][j]+a[u]);
		}
	}print(*max_element(f[n+1],f[n+1]+m+1));
}
signed main()
{
	int T=1;
	// T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：Undead2008 (赞：2)

[COTS 2025 题解合集](https://www.luogu.com.cn/article/dupadkce)

直接暴力树形 dp 会出现两个背包卷积，就炸缸了。

使用技巧规避背包卷积。对 dfs 序上每个点开一个背包，按照 dfs 序从小到大依次转移，设当前点为 $x$。

- $x$ 不给发钱，将 $\text{dfn}_x-1$ 处的背包直接和 $\text{dfn}_x+\text{sz}_x$ 处的背包对位取 $\max$，表示子树中也不会有人发钱。
- 否则给 $x$ 发钱，将 $\text{dfn}_x-1$ 处的背包加上 $1$ 的花费或者 $w_i$ 的花费和 $p_i$ 的收益转移到 $\text{dfn}_x$ 处。

```cpp
for(int i=1;i<=n;i++){
  int l=i,r=i+Sz[Id[i]]-1;
  for(int K=0;K<=k;K++)f[r][K]=max(f[r][K],f[l-1][K]);
  for(int K=1;K<=k;K++)f[i][K]=max(f[i][K],f[i-1][K-1]);
  for(int K=w[Id[i]];K<=k;K++)f[i][K]=max(f[i][K],f[i-1][K-w[Id[i]]]+c[Id[i]]);
  for(int K=0;K<=k;K++)A=max(A,f[i][K]);
}
```

---

## 作者：Kingna (赞：1)

> 每个获得奖金的人的直接上级必须获得至少 $1$ 的奖金。

这句话可以转化为每个获得奖金的人可以使得他们的下级可以有资格获得奖金。

我们按照 dfn 序从小到大进行 dp：
* 若当前 $u$ 不获得奖金，那么 $u$ 的子树也不会获得奖金。那么直接跳转到 $dfn_u+sz_u$ 位置进行 dp。
* 若当前 $u$ 获得奖金，那么跳转到 $dfn_u+1$ 进行 dp。同时获得奖金有两种情况：获得 $1$ 奖金或者获得 $c_i$ 奖金。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 3e5 + 5, M = 5005;

int n, m, p[N], c[N], din[N], sz[N], idx, f[M][M], vv[N];
vector<int> G[N]; 

void dfs(int u, int fa) {
  din[u] = ++idx; vv[idx] = u; sz[u] = 1;
  for (auto v : G[u]) {
    dfs(v, u);
    sz[u] += sz[v];
  } 
}

signed main() {
  cin >> n >> m;
  memset(f, -0x3f, sizeof f); 
  _for(i, 2, n) {
    int x; cin >> x;
    G[x].push_back(i);
  }
  _for(i, 1, n) cin >> p[i];
  _for(i, 1, n) cin >> c[i];
  dfs(1, 0);
  f[1][0] = 0;
  _for(i, 1, n) {
    _for(j, 0, m) {
      f[i + sz[vv[i]]][j] = max(f[i + sz[vv[i]]][j], f[i][j]);
      if (j + 1 <= m) f[i + 1][j + 1] = max(f[i + 1][j + 1], f[i][j]);
      if (j + c[vv[i]] <= m) f[i + 1][j + c[vv[i]]] = max(f[i + 1][j + c[vv[i]]], f[i][j] + p[vv[i]]); 
    }
  }
  int res = 0;
  _for(i, 0, m) res = max(res, f[n + 1][i]);
  cout << res << endl; 
}
```

---

