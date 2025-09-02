# Equidistant Vertices

## 题目描述

A tree is an undirected connected graph without cycles.

You are given a tree of $ n $ vertices. Find the number of ways to choose exactly $ k $ vertices in this tree (i. e. a $ k $ -element subset of vertices) so that all pairwise distances between the selected vertices are equal (in other words, there exists an integer $ c $ such that for all $ u, v $ ( $ u \ne v $ , $ u, v $ are in selected vertices) $ d_{u,v}=c $ , where $ d_{u,v} $ is the distance from $ u $ to $ v $ ).

Since the answer may be very large, you need to output it modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
3

4 2
1 2
2 3
2 4

3 3
1 2
2 3

5 3
1 2
2 3
2 4
4 5```

### 输出

```
6
0
1```

# 题解

## 作者：Acfboy (赞：14)

本想着 Div.3 玩玩就好，所以直接开了最后一题，想着 $40$ 分钟内可以解决。然后就……悲剧了。

> 给定一棵 $n$ 个节点的树，求选出 $k$ 个点，它们两两距离相同的方案数。

首先容易发现一个性质，如果 $k > 2$，那么这些点一定有一个“中心点”本身不被选中但所有选中的点到它距离都一样。

那么考虑枚举这一个中心点，以其为根把树变成有根树，考虑每一个距离求方案数。但这样还不行，因为如果有俩点的 LCA 不是根，那么它们之间的距离就和到其它点之间的距离不一样了。  
所以还必须要 LCA 是根。那么就是要每个子树中最多只能选一个点。

现在想想方案怎么计数。  
一开始想的是可能存在神奇的组合数方法，但想了一会儿未果，而且数据范围那么小，似乎并不是想让我们去推式子组合数的。所以考虑 dp。  
$f_{i, j}$ 表示根的前 $i$ 个子树中一共有 $j$ 个子树中取了点的方案数。那么转移就两种，当前子树取点或不取点，易得 $f_{i, j} = f_{i-1,j} + f_{i-1, j-1} \times a_i$，其中 $a_i$ 是第 $i$ 棵子树的该层点数。

那么做法就很清晰了。

1. 枚举一个根。
2. dfs 记录每个子树下面每一个深度的点数。
3. 枚举每一个深度。
4. 进行 dp。

不要忘了**好好地**清空数组！我因为清空时写了：

```cpp
for (int j = 1; j <= n; j++)
                for (int l = 0; l <= n; l++) num[i][j] = 0;
```

调了一个小时 qwq。

完整代码。

```cpp
#include <iostream>
#include <vector>
#define int long long
const int N = 205, P = 1000000007;
int T, n, k, x, y, num[N][N], f[N][N];
std::vector<int> g[N];
std::vector<int> a;
void dfs(int u, int fa) {
    num[u][0] = 1;
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) continue;
        dfs(v, u);
        for (int j = 1; j <= n; j++)
            num[u][j] += num[v][j-1];
    }
}
signed main() {
    std::cin >> T;
    while (T--) {
        std::cin >> n >> k;
        int ans = 0;
        for (int i = 1; i < n; i++)
            std::cin >> x >> y, g[x].push_back(y), g[y].push_back(x);
        if (k == 2) {
            std::cout << n * (n-1) / 2 << '\n';
            for (int i = 1; i <= n; i++) g[i].clear();
            continue;
        }
        for (int i = 1; i <= n; i++) {
            dfs(i, 0);
            for (int j = 1; j <= n; j++) {
                for (int l = 0; l < (int)g[i].size(); l++) 
                    a.push_back(num[g[i][l]][j-1]);
                f[0][0] = 1;
                for (int x = 1; x <= (int)a.size(); x++) {
                    f[x][0] = 1;
                    for (int y = 1; y <= x; y++)
                        f[x][y] = (f[x-1][y] + f[x-1][y-1]*a[x-1]%P) % P;
                }
                ans = (ans + f[a.size()][k]) % P;
                for (int x = 1; x <= (int)a.size(); x++)
                    for (int y = 1; y <= x; y++) f[x][y] = 0;
                a.clear();
            }
            for (int j = 1; j <= n; j++)
                for (int l = 0; l <= n; l++) num[j][l] = 0;
        }
        std::cout << ans << '\n';
        for (int i = 1; i <= n; i++) g[i].clear();
        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= n; j++) num[i][j] = 0;
    }
    return 0;
}
```


---

## 作者：beauty_son_whm (赞：2)

$k$ 个点两两距离相等，只能有两种情况。

$cas1: k=2$ 因为树是联通的，所以答案是 $\frac{n\cdot(n-1)}{2}$。

$cas2:k>2$ 必然存在一个中心点是这 $k$ 个点的 $Lca$。
 使得这个中心点到这些点的距离相等。
 
那么我们考虑做树形 $dp$。

$down_{x,j}$ 表示以 $x$ 为根，距离 $x$ 为 $j$ 的点有多少个。

$down_{x,j}=
\begin{cases}
\sum_{y \in son_{i}}down_{y,j-1},&j>=1\\
1 ,&j=0
\end{cases}
$

$up_{x,j}$ 表示除了以 $i$ 为根的子树，距离 $x$ 为 $j$ 的点有多少个。

$up_{x,j}=
\begin{cases}
up_{fa,j-1}+down_{fa,j-1}-down_{x,j-2},&j>=1\\
0 ,&j=0
\end{cases}
$

意思是要么就是走出父亲的子树，要么就是走到父亲的子树，然后减去自己的贡献。

然后你做一个 $dp$ 计数，

$dp_{x,j,k}$ 表示以 $x$ 为根，我当前从不同的子树里选出来了 $j$ 个距离 $x$ 为 $p$ 的点的方案数。


$dp_{x,i,p}=dp_{x,j-1,p}\cdot down_{son,p-1}$

最后的答案就是：       $\sum_{i=1}^n\sum_{j=1}^n(dp_{i,k,j}+dp_{i,k-1,j}\cdot up_{i,j})$。

$code:$
```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define pc putchar
using namespace std;
const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
void write(int x){
	if(x==0){pc('0');return ;}
	if(x<0) x=-x,pc('-');
	char nnu[25];int top=0;
	while(x){nnu[++top]=x%10+'0';x/=10;}
	for(int i=top;i;i--) pc(nnu[i]);
	return ;
}
basic_string<int>e[105];
int T,n,k;
ll down[105][105];
ll up[104][105];
int dep[105];
ll tp[105][105];
ll ans=0;
void dfs(int x,int fa){
	down[x][0]=1;
	dep[x]=dep[fa]+1;
	for(auto y:e[x]){
		if(y==fa) continue;
		dfs(y,x);
		for(int i=0;i<=n;i++){
			down[x][i+1]=(down[x][i+1]+down[y][i])%mod;
		}
	}
	return ;
} 
void dfs_(int x,int fa){
    if(x!=1)
    for(int i=1;i<=n;i++){
        up[x][i]=(up[x][i]+up[fa][i-1])%mod;
        if(i==1&&x!=1) up[x][i]=(up[x][i]+1)%mod;
        if(i>=2){
            up[x][i]=(down[fa][i-1]-down[x][i-2]+up[x][i]+mod)%mod;
        }
    }
    memset(tp,0,sizeof(tp));
	for(int i=0;i<=n;i++) tp[0][i]=1;
	for(int j=1;j<=n;j++){
		for(auto y:e[x]){
     		if(y==fa) continue;
			for(int i=k;i>=1;i--){
				tp[i][j]=(tp[i][j]+tp[i-1][j]*down[y][j-1]%mod)%mod;
			}
        }
	}
	for(int i=1;i<=n;i++){
		ans=(ans+tp[k][i])%mod;
        ans=(ans+tp[k-1][i]*up[x][i]%mod)%mod;
	}
    for(auto y:e[x]){
        if(y==fa) continue;
        dfs_(y,x);
    }
    return ;
}
signed main(){
	T=read();
	while(T--){
		n=read(),k=read();
        for(int i=1;i<=n;i++) e[i].clear();
		for(int i=1,u,v;i<n;i++){
			u=read(),v=read();
			e[u]+=v;
			e[v]+=u; 
		}
        if(k==2){
            cout<<(n*(n-1ll)/2%mod)<<endl;
            continue;
        }
		ans=0;
		memset(down,0,sizeof(down));
        memset(up,0,sizeof(up));
		dfs(1,1);
        dfs_(1,0);
		cout<<ans<<endl;
	}
	return 0;
}

```



---

## 作者：ncwzdlsd (赞：1)

DP。

首先特判 $n=2$ 的情况，输出 $C_n^2$。

对于满足条件的 $k$ 个点，等价于存在一个中间点 $x$ 使得这 $k$ 个点中的每一个都满足 $d(a_i,x)=d(a_j,x)$。

考虑如何统计方案数，由于 $n$ 的范围很小，我们直接让每一个点都成为根，计算其他点的深度求方案数。对于选择的点，需要让任意两个点的 LCA 均为根结点。想要满足这个限制，则每个同层数结点各自的子树内只能选一个点。

$c_i$ 记录以当前点为根的子树中，深度为 $i$ 的点的个数，$f(i,j)$ 表示深度为 $i$ 的结点选了 $j$ 棵子树的方案数，显然，$f(i,j)=\sum f(i,j-1)\times c_{v_i,w}$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod=1e9+7;
int head[105],f[105][105],c[105],dep[105],cnt;
struct edge{int to,nxt;}e[205];

void add(int x,int y){e[++cnt]={y,head[x]},head[x]=cnt;}

void dfs(int x,int fa)
{
    dep[x]=dep[fa]+1,c[dep[x]]++;
    for(int i=head[x];i;i=e[i].nxt)
    {
        if(e[i].to==fa) continue;
        dfs(e[i].to,x);
    }
}

void solve()
{
    int n,k;cin>>n>>k;
    cnt=0;
    for(int i=1;i<=n;i++) head[i]=0,dep[i]=0;
    for(int i=1;i<=n*2;i++) e[i]={0,0};
    for(int i=1,u,v;i<n;i++) cin>>u>>v,add(u,v),add(v,u);
    if(k==2) return cout<<n*(n-1)/2<<endl,void();
    int ans=0;
    for(int rt=1;rt<=n;rt++)
    {
        dep[rt]=0;
        for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) f[i][j]=0;
        for(int i=0;i<=n;i++) f[i][0]=1;
        for(int kk=head[rt];kk;kk=e[kk].nxt)
        {
            for(int i=0;i<=n;i++) c[i]=0;
            dfs(e[kk].to,rt);
            // for(int i=1;i<=n;i++) c[dep[i]]++;
            for(int i=1;i<=n;i++)
            {
                if(!c[i]) break;
                for(int j=k;j;j--) f[i][j]+=f[i][j-1]*c[i]%mod,f[i][j]%=mod;
                // if(rt==2) for(int j=k;j;j--) cout<<f[i][j]<<endl;
            }
        }  
        for(int i=1;i<=n;i++) ans+=f[i][k],ans%=mod;
        // cout<<ans<<"qwq\n";
        // for(int i=1;i<=n;i++) cout<<c[2]<<endl;
        // puts("");
    }
    cout<<ans<<'\n';
}

signed main()
{
    int t;cin>>t;
    while(t--) solve();
    return 0;
}
```

---

## 作者：little_sheep917 (赞：1)

> 给定一棵有 $n$ 个点的树，要求选出 $k$ 个点，使得这 $k$ 个点两两距离相同。答案模 $10^9+7$ 。
>
> $1\leq t\leq 10$
>
> $2\leq k\leq n\leq 100$

设选出的 $k$ 个点为黑点，其他的为白点 .

考虑这 $k$ 个距离两两相同的点的排布，在树的一条链上，必定至多有两个点为黑点 .

所以，枚举根节点 $r$  ，设剩下的 $k$ 个点到这个点距离相同 . 所有的情况都可以归结到这个样子 .

观察可得，这 $k$ 个节点必定存在与不同的子树中 . 否则，在同一个子树的节点之间的距离会比到其他节点的距离要小 .

接着枚举 $k$ 个点到 $r$ 的距离 $d$ ，通过 $dfs$ 求出每个子树距离 $r$ 距离为 $d$ 的节点个数 .

因为每个节点最多选 $1$ 个，所以可以用一个背包求出 .

用 $f(i,j)$ 表示到了第 $i$ 个子树，选了 $j$ 个黑点的方案数 .

用 $cnt(i)$ 表示第 $i$ 个子树中距离 $r$ 距离为 $d$ 的节点个数 .

$f(i,j)=f(i-1,j-1)\times cnt(i)+f(i-1,j)$

枚举根 $\mathrm O(n)$，枚举距离 $\mathrm O(n)$ ，$dfs$ $\mathrm O(n)$ 之后背包 $\mathrm O(n^2)$ .

时间复杂度 : $\mathrm O(n^4)$

空间复杂度 : $\mathrm O(n^2)$

其实只跑了 31ms ，因为仔细想想，没有什么数据能使这个跑满，一般都远远跑不满 .

code

```c++
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int t;
int n,k;
vector<int>g[110]; 
int dep[110],dp[110][110];
inline void upd(int &x,int y){
	x=(x+y)%mod;
}
void dfs(int x,int fa,int d,int &cnt){
	if(dep[x]==d)cnt++;
	for(int i=0;i<(int)g[x].size();i++){
		int to=g[x][i];
		if(to==fa)continue;
		dep[to]=dep[x]+1;
		dfs(to,x,d,cnt);
	}
}
void solve(){
	cin>>n>>k;
	for(int i=0;i<n;i++)g[i].clear();
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		u--;v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	if(k==2){
		cout<<1ll*n*(n-1)/2%mod<<endl;
		return;
	}
	int ans=0;
	for(int r=0;r<n;r++)for(int d=1;d<=n;d++){
		if((int)g[r].size()<k)continue;
		dp[0][0]=1;
		for(int i=0;i<(int)g[r].size();i++){
			int cnt=0;
			dep[g[r][i]]=1;
			dfs(g[r][i],r,d,cnt);
			for(int j=0;j<=i+1;j++)dp[i+1][j]=0;
			for(int j=0;j<=i;j++){
				if(cnt>0)upd(dp[i+1][j+1],1ll*dp[i][j]*cnt%mod);
				upd(dp[i+1][j],dp[i][j]);
			}
		}
		cout<<endl;
		upd(ans,dp[(int)g[r].size()][k]);
	}
	cout<<ans<<endl;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
/*inline? ll or int? size? min max?*/
```



---

## 作者：jun头吉吉 (赞：1)

## 题意
$n$ 个节点的树，选 $k$ 个点使得任意两个点距离相同的方案数。
## 题解

$k=2$ 时任意选两个点就符合条件，即 $\binom n2$。

否则必然有一个点为根使得：

1. $k$ 个点在不同子树内
2. $k$ 个点深度相同

枚举深度 $d$，每一棵子树深度为 $d$ 的数量分别为 $a_1,a_2,\dots$，那么方案数就是

$$
[x^k]\prod_i 1+a_ix
$$

然后就做完了。


看上去是个多项式算法就能过，就不分析复杂度了。
## 代码
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define chkmx(a,b) ((a)=max((a),(b)))
#define chkmn(a,b) ((a)=min((a),(b)))
using namespace std;
template<typename T>
inline void read(T &x){x=0;char c=getchar();bool f=false;for(;!isdigit(c);c=getchar())f|=c=='-';for(;isdigit(c);c=getchar())x=x*10+c-'0';if(f)x=-x;}
template<typename T ,typename ...Arg>inline void read(T &x,Arg &...args){read(x);read(args...);}
template<typename T>inline void write(T x){if(x<0)putchar('-'),x=-x;if(x>=10)write(x/10);putchar(x%10+'0');}
//#define int long long
typedef long long ll;
#define fi first
#define se second
#define lc (x<<1)
#define rc (x<<1|1)
#define mid (l+r>>1)
template<const int mod>
struct modint{
    int x;
    modint<mod>(int o=0){x=o;}
    modint<mod> &operator = (int o){return x=o,*this;}
    modint<mod> &operator +=(modint<mod> o){return x=x+o.x>=mod?x+o.x-mod:x+o.x,*this;}
    modint<mod> &operator -=(modint<mod> o){return x=x-o.x<0?x-o.x+mod:x-o.x,*this;}
    modint<mod> &operator *=(modint<mod> o){return x=1ll*x*o.x%mod,*this;}
    modint<mod> &operator ^=(int b){
        modint<mod> a=*this,c=1;
        for(;b;b>>=1,a*=a)if(b&1)c*=a;
        return x=c.x,*this;
    }
    modint<mod> &operator /=(modint<mod> o){return *this *=o^=mod-2;}
    modint<mod> &operator +=(int o){return x=x+o>=mod?x+o-mod:x+o,*this;}
    modint<mod> &operator -=(int o){return x=x-o<0?x-o+mod:x-o,*this;}
    modint<mod> &operator *=(int o){return x=1ll*x*o%mod,*this;}
    modint<mod> &operator /=(int o){return *this *= ((modint<mod>(o))^=mod-2);}
    template<class I>friend modint<mod> operator +(modint<mod> a,I b){return a+=b;}
    template<class I>friend modint<mod> operator -(modint<mod> a,I b){return a-=b;}
    template<class I>friend modint<mod> operator *(modint<mod> a,I b){return a*=b;}
    template<class I>friend modint<mod> operator /(modint<mod> a,I b){return a/=b;}
    friend modint<mod> operator ^(modint<mod> a,int b){return a^=b;}
    friend bool operator ==(modint<mod> a,int b){return a.x==b;}
    friend bool operator !=(modint<mod> a,int b){return a.x!=b;}
    bool operator ! () {return !x;}
    modint<mod> operator - () {return x?mod-x:0;}
    modint<mod> &operator++(int){return *this+=1;}
};
using mint=modint<1OOOOOOOO7>;
const int N=110;
struct poly{
	mint a[N];
	void init(){
		memset(a,0,sizeof a);
		a[0]=1;
	}
	void mul(mint b){
		//mul 1+bx
		for(int i=N-1;i;i--)
			a[i]+=a[i-1]*b;
	}
}f[N];
int t,n,k;vector<int>e[N];
int cnt[N];
void dfs(int u,int fa,int dep){
	cnt[dep]++;
	for(auto v:e[u])if(v!=fa)
		dfs(v,u,dep+1);
}
signed main(){
	read(t);while(t--){
		read(n,k);
		for(int i=1;i<=n;i++)e[i].clear();
		for(int i=1,u,v;i<n;i++)
			read(u,v),e[u].pb(v),e[v].pb(u);
		if(k==2){write(n*(n-1)/2),putchar('\n');continue;}
		mint ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)f[j].init();
			for(auto v:e[i]){
				memset(cnt,0,sizeof cnt);
				dfs(v,i,1);
				for(int j=1;j<=n;j++)
					f[j].mul(cnt[j]);
			}
			for(int j=1;j<=n;j++)
				ans+=f[j].a[k];
		}
		write(ans.x);putchar('\n');
	}
}
```

---

## 作者：happybob (赞：0)

题意：给 $n$ 个点的树和 $k$，边无权。问有多少种方案，选出 $k$ 个点且 $k$ 个点中两两距离相等。对 $10^9+7$ 取模。$2 \leq k \leq n \leq 100$，多测。

特判 $k=2$ 时，输出 $\dbinom{n}{2}$。

考虑 $k > 2$，容易发现对于每个选出的点集 $S$，一定存在且仅存在一个点 $u$，使得整棵树以 $u$ 为根时，点集中的点在 $u$ 的不同儿子的子树中，且深度都相同。换句话说就是这个点集有一个中点。

考虑枚举这个点，这个的复杂度为 $O(n)$。然后处理出每个儿子的子树中每个深度的点数。枚举相同的深度 $d$。考虑 DP，设 $f_{i,j}$ 表示处理了前 $i$ 个儿子，选了 $j$ 个点的方案数。则 $f_{i,j} = f_{i-1,j} + f_{i-1,j-1} \times cnt_{i,d}$，$cnt_{i,d}$ 表示以 $i$ 这个儿子为根的子树中深度为 $d$ 的点数。

乍一看是 $O(n^4)$ 的，其实仔细分析是 $O(n^2k)$ 的，不过证明略过，因为这个 $O(n^4)$ 看起来就跑不满。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <map>
using namespace std;

const int N = 105;
constexpr long long MOD = static_cast<long long>(1e9 + 7);

int t, n, k;
vector<int> G[N];
long long dp[N][N];
int cnt[N][N];
int maxd = 0;
int nowp = 0;

void dfs(int u, int fa, int d)
{
	maxd = max(maxd, d);
	cnt[nowp][d]++;
	for (auto& j : G[u])
	{
		if (j == fa) continue;
		dfs(j, u, d + 1);
	}
}

int idx, son[N];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n >> k;
		for (int i = 1; i <= n; i++) G[i].clear(), G[i].shrink_to_fit();
		for (int i = 1; i < n; i++)
		{
			int u, v;
			cin >> u >> v;
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		if (k == 2)
		{
			cout << n * (n - 1) / 2 << "\n";
			continue;
		}
		long long ans = 0LL;
		for (int i = 1; i <= n; i++)
		{
			maxd = 0;
			for (int j = 1; j <= n; j++)
			{
				for (int k = 1; k <= n; k++) cnt[j][k] = 0;
			}
			idx = 0;
			for (auto& j : G[i])
			{
				nowp = j;
				dfs(j, i, 2);
				son[++idx] = j;
			}
			for (int d = 2; d <= maxd; d++)
			{
				int lst = 0;
				for (int j = 0; j <= idx; j++)
				{
					for (int p = 0; p <= k; p++) dp[j][p] = 0;
				}
				dp[0][0] = 1;
				for (int p = 1; p <= idx; p++)
				{
					if (!cnt[son[p]][d])
					{
						continue;
					}
					for (int c = 0; c <= k; c++)
					{
						dp[p][c] = (dp[lst][c] + (!c ? 0LL : dp[lst][c - 1] * cnt[son[p]][d] % MOD)) % MOD;
					}
					lst = p;
				}
				ans = (ans + dp[lst][k]) % MOD;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
```


---

## 作者：TernaryTree (赞：0)

考虑 $k\ge 3$，那么此时任意三个节点都不在一条链上，并且这几个点两两路径并应该会集中于一个中心点，每个点与中心点距离相等。

于是我们枚举这个中心点，我们选中的点应该在这个中心点的不同子树内的同一深度。再枚举一个深度，预处理出的每个子树的各个深度的节点数，然后考虑 dp。

设 $f_{i,j}$ 表示前 $i$ 棵子树内有 $j$ 个点的方案数，有

$$f_{i,j}=f_{i-1,j}+cnt_{i,c}\cdot f_{i-1,j-1}$$

其中 $cnt_{i,c}$ 表示当前子树在当前深度下有多少个结点。

然后注意到如果子树数量 $\lt k$ 的结点显然都不会是中心点。那么子树数量，也就是度数 $\ge k$ 的结点不超过 $\Theta(\dfrac nk)$ 个，这是因为所有结点的度数总和为 $2n-2$。然后枚举深度是 $\Theta(n)$，dp 是 $\Theta(nk)$，所以总复杂度为 $\Theta(n^3)$。

特判 $n=2$ 的情况。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 2e2 + 10;
const int mod = 1e9 + 7;

int T, n, k, ans;
vector<int> g[maxn];
int deg[maxn];
int cnt[maxn][maxn];
int f[maxn][maxn];

void dfs(int u, int fa, int rt, int dep) {
	++cnt[rt][dep];
	for (int v : g[u]) if (v != fa) dfs(v, u, rt, dep + 1);
}

signed main() {
	cin >> T;
	while (T--) {
		cin >> n >> k;
		for (int i = 1, u, v; i < n; i++) {
			cin >> u >> v;
			g[u].push_back(v), g[v].push_back(u);
			++deg[u], ++deg[v];
		}
		if (k == 2) {
			cout << ((n - 1) * n / 2) % mod << endl;
			for (int i = 1; i <= n; i++) g[i].clear(), deg[i] = 0;
			continue;
		}
		ans = 0;
		for (int u = 1; u <= n; u++) {
			if (deg[u] < k) continue;
			for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cnt[i][j] = 0;
			for (int i = 0; i < g[u].size(); i++) dfs(g[u][i], u, i + 1, 1);
			for (int c = 1; c <= n; c++) {
				for (int i = 0; i <= g[u].size(); i++) for (int j = 0; j <= k; j++) f[i][j] = 0;
				f[0][0] = 1;
				for (int i = 1; i <= g[u].size(); i++) for (int j = 0; j <= k; j++) f[i][j] = (f[i - 1][j] + cnt[i][c] * f[i - 1][j - 1] % mod) % mod;
				(ans += f[g[u].size()][k]) %= mod;
			}
		}
		cout << ans << endl;
		for (int i = 1; i <= n; i++) g[i].clear(), deg[i] = 0;
	}
	return 0;
}
```

---

## 作者：FiraCode (赞：0)

### CF Round #734(Div.3) F,Equidistant Vertices
#### 题意：
[洛谷题目链接](https://www.luogu.com.cn/problem/CF1551F)

[CF题目链接](https://codeforc.es/contest/1551/problem/F)

给定一棵有 $n$ 个点的树，要求选出 $k$ 个点，使得这 $k$ 个点两两距离相同。

输入数据有 $t$ 组（ $1 \leq t \leq 10$ ），每组数据第一行有两个数 $n$ 和 $k$ （ $2 \leq k \leq n \leq 100$ ），意义如上，下面 n−1 n-1n−1 行每行有两个数 u,vu,vu,v 代表有一条边连接 u,vu,vu,v 两个点，对于每组数据，输出方案数，答案对 $10^9+7$ 取模。
#### 题解思路：
我们先特判一下，当 $k \le 2$ 的时候，那么他们的距离是相同的。

当 $k=3$ 时，只有他是有分叉的，才有可能使得这三个点两两距离相同。那么他们的距离就是他们分叉的距离两两相同。

所以当 $k \ge 3$ 时，他们的结果是一样的。

还有一个隐含条件，就是这些点不在同一子树里。

那么组合数就不可做了。

而我们发现 $n$ 很小，所以我们可以枚举分叉点，我们就求他离分叉点有多远的点的个数。

我们设距离为 $d$，那么我们就统计离分叉点距离为 $d$ 的点的个数。

记为 $c_1,c_2,c_3,...,c_k$，其中 $k$ 是子树的个数。

那么我们设 $dp_{i,j}$ 表示前 $i$ 个分支，并选了 $j$ 个点。

那么状态转移方程为：
$$dp_{i,j} = (dp_{i-1,j} + dp_{i-1,j-1} \times c_i)$$
那么时间复杂度为 $\mathcal{O(n^2 k)}$。

并且我们还可以把 $i$ 这一维给优化掉。

因为这道题的范围很小，所以我们可以用floyd求最短路。
### AC CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
const int N = 110;
int n, k, g[N][N];
int cnt[N], dp[N];
void solve() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			g[i][j] = (i == j) ? 0 : mod;
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		g[u][v] = g[v][u] = 1;
	}
	if (k == 2) {
		printf("%d\n", n * (n - 1) / 2);
		return;
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int d = 1; d <= n; d++) {
			for (int j = 1; j <= n; j++)
				cnt[j] = 0;
			for (int u = 1; u <= n; u++)
				if (g[i][u] == d) {
					for (int v = 1; v <= n; v++)
						if (g[i][v] == 1 && g[i][u] == g[i][v] + g[v][u]) {
							cnt[v]++;
						}
				}
			for (int j = 1; j <= k; j++)
				dp[j] = 0;
			dp[0] = 1;
			for (int j = 1; j <= n; j++)
				if (cnt[j] > 0) {
					for (int l = k; l >= 1; l--)
						dp[l] = (dp[l] + 1ll * dp[l - 1] * cnt[j]) % mod;
				}
			ans = (ans + dp[k]) % mod;
		}
	}
	printf("%d\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：peterwuyihong (赞：0)

green problem so hard！

题意：给定一棵有 $n$ 个点的树，要求选出 $k$ 个点，使得这 $k$ 个点两两距离相同。答案对 $10^9+7$ 取模输出。

显然可以直接讨论 $k>2$ 的情况，斯时，如果那 $k$ 个点两两距离相同，那么必然存在一个点，到 $k$ 个点的距离相同，称其为关键点，那么关键点和 $k$ 个点构成一株菊花，且 $k$ 个点在以关键点为根的不同子树中。

那么就非常明了了啊！直接枚举关键点，作为根，然后再枚举深度，表示关键点到每个点的距离，然后你设每个子树里这个深度出现次数为 $a_i$，然后求 $[x^k]\prod1+a_ix$ 即可。

```cpp
poly mtt(poly a,poly b){
  poly ans(a.size()+b.size()-1);
  rep(i,0,a.size()-1)rep(j,0,b.size()-1)
  add(ans[i+j],Mul(a[i],b[j]));
  return ans;
}
void solve(){
  int n,k;
  cin>>n>>k;
  vector<vector<int> >g(n);
  rep(i,0,n-2){
    int x,y;
    cin>>x>>y,x--,y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  if(k==2)return cout<<n*(n-1)/2<<endl,void();
  auto get=[&](int rt){
    vector<int>a;
    int app;
    function<void(int,int,int,int)>dfs=[&](int x,int fa,int d,int dep){
      if(dep==d)app++;
      for(int y:g[x])if(y!=fa)
        dfs(y,x,d,dep+1);
    };
    int ans=0;
    rep(d,0,n-2){
      a.clear();
      for(int x:g[rt])
        app=0,dfs(x,rt,d,0),a.push_back(app);
      if(a.size()<k)return 0;
      poly D={1};
      for(int i:a)D=mtt(D,{1,i});
      add(ans,D[k]);
    }
    return ans;
  };
  int ans=0;
  rep(i,0,n-1)add(ans,get(i));
  cout<<ans<<endl;
}
```

---

## 作者：Wf_yjqd (赞：0)

考虑选中的点一定不存在三个在同一条链上。

转化问题为找出子图为菊花图且叶子节点到根节点距离相同，其中叶子节点即为选中的点。

枚举这个子图的根，显然可以树上 dp 求出深度相同的点的个数。

dp 维护选取 $k$ 个分支的方案数，我还用滚动数组减了一维。

求和即可，复杂度 $\operatorname{O}(n^4)$。

------------

转移可以看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=284,mod=1e9+7;
namespace Sherry_Graph{
    struct Edge{
        ll to,ne;
    }e[maxn];
    ll ecnt=1,head[maxn];
    inline void add(ll u,ll v){
        e[ecnt]={v,head[u]};
        head[u]=ecnt++;
        return ;
    }
}
using namespace Sherry_Graph;
ll T,n,k,x,y,ans,du[maxn],dep[maxn],cnt[maxn][maxn],f[maxn];//度，深度，以i为根的子树中深度为j的个数，选了i个的方案数
inline void dfs(ll x,ll fa){
    dep[x]=dep[fa]+1;
    cnt[x][dep[x]]=1;
    for(ll i=head[x];i;i=e[i].ne)
        if(e[i].to!=fa){
            dfs(e[i].to,x);
            for(ll j=1;j<=n;j++)
                cnt[x][j]+=cnt[e[i].to][j];
        }
    return ;
}
int main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld",&n,&k);
        for(ll i=0;i<=n+23;i++)
            head[i]=du[i]=0;
        ecnt=1;
        ans=0;
        for(ll i=1;i<n;i++){
            scanf("%lld%lld",&x,&y);
            add(x,y);
            add(y,x);
            du[x]++;
            du[y]++;
        }
        if(k==2){
            printf("%lld\n",n*(n-1)/2);
            continue;
        }
        for(ll i=1;i<=n;i++){
            if(du[i]<k)
                continue;
            for(ll j=1;j<=n;j++)
                for(ll l=1;l<=n;l++)
                    cnt[j][l]=0;
            dfs(i,0);
            for(ll j=1;j<=n;j++){
                if(cnt[i][j]<k)
                    continue;
                for(ll l=1;l<=k;l++)
                    f[l]=0;
                f[0]=1;
                for(ll l=head[i];l;l=e[l].ne)
                    for(ll m=k;m>=1;m--)//滚动数组
                        f[m]=(f[m]+f[m-1]*cnt[e[l].to][j]%mod)%mod;
                ans=(ans+f[k])%mod;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

