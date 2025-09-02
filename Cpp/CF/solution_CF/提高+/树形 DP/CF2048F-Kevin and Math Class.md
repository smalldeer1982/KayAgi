# Kevin and Math Class

## 题目描述

Kevin 是来自 Eversleeping Town 的一名学生，他正在参加一门数学课，老师正在给他出一些除法练习题。

在黑板上，有两行正整数，每行包含 $n$ 个数字。第一行是 $a_1, a_2, \ldots, a_n$，第二行是 $b_1, b_2, \ldots, b_n$。

对于每个除法练习题，Kevin 可以选择任何一个区间 $[l, r]$，并在 $b_l, b_{l+1}, \ldots, b_r$ 中找到最小的值 $x$。然后他将修改 $l \leq i \leq r$ 范围内的每个 $a_i$，使得每个 $a_i$ 被 $x$ 除后的结果向上取整。

更正式地，他选择两个整数 $1 \leq l \leq r \leq n$，设 $x = \min_{l \leq i \leq r} b_i$，然后将所有 $l \leq i \leq r$ 范围内的 $a_i$ 修改为 $ \lceil \frac{a_i}{x} \rceil$。

Kevin 只有当所有 $a_i$ 都变为 1 时，才能离开教室回家。他非常渴望回家，想知道实现这一目标所需的最小除法练习次数。

## 说明/提示

对于第一个测试用例:  
$[{\color{red}{5,4}}, 2] \xrightarrow[\min(b_1, b_2) = 3] {\text{操作区间}[1, 2]} [{\color{red}{2, 2, 2}}] \xrightarrow[\min(b_1, b_2, b_3) = 2]{\text{操作区间}[1, 3]} [1, 1, 1]$

对于第二个测试用例:  
$[{\color{red}{3, 6, 1}}, 3, 2] \xrightarrow[\min(b_1, b_2, b_3) = 3]{\text{操作区间}[1, 3]} [1, {\color{red}{2, 1, 3}}, 2] \xrightarrow[\min(b_2, b_3, b_4) = 2]{\text{操作区间}[2, 4]} [1, 1, 1, {\color{red}{2, 2}}] \xrightarrow[\min(b_4, b_5) = 2]{\text{操作区间}[4, 5]} [1, 1, 1, 1, 1]$

translation from [Yorg](https://www.luogu.com.cn/user/617130)

## 样例 #1

### 输入

```
3
3
5 4 2
6 3 2
5
3 6 1 3 2
3 5 3 2 2
6
8 3 3 7 5 8
3 2 3 4 2 3```

### 输出

```
2
3
3```

# 题解

## 作者：_jimmywang_ (赞：9)

验题人题解。

首先观察到 $b_i\ge 2$，因此就算每次都取整个 $[1,n]$ 操作，也最多只会操作 $O(\log a_i)$ 次。因此我们得到了一个答案的上界，取的宽松一点，可以算作 $63$。

然后我们发现操作顺序对操作的结果没有影响，因此考虑对于所有 $i$，把 $b_i$ 作为这个区间的最小值时，对它操作的次数。

另一个观察是，但凡我们钦定了某一个 $b_i$ 作为一个区间的最小值来操作，那么选取一个极大的， $\min_{j=l}^rb_j=b_i$ 的区间 $[l,r]$ 一定不劣，因为这样能以相同的分母和次数除到尽可能多的数。

对于每个位置，我们可以预处理这个区间。但是如果你对这类问题熟悉，就会发现这些区间一定要么相离要么包含，且包含关系形成了一棵**小根笛卡尔树**。因此我们考虑建出笛卡尔树，并在这上面进行处理。

设 $dp_{u,i}$ 表示只在以 $u$ 为根的子树内操作 $i$ 次，后这个区间内的 $a$ 的最大值**最小**能是多少。

因为操作顺序不影响，为了方便，我们钦定先对儿子的子树进行操作，再操作自己。

如果这个点只有一个儿子，那么先把 $a_u$ 纳入考虑范围，即 $dp_{u,i}\leftarrow \max(dp_{son,i},a_u)$。然后考虑对 $u$ 自己进行操作，即 $dp_{u,i} \leftarrow \min(dp_{u,i},\lceil \dfrac{dp_{u,i-1}}{b_u}\rceil)$。

如果有两个儿子，那么需要先合并 $l_u$ 和 $r_u$ 的信息，这是一个简单的背包合并。然后和上面一样纳入 $a_u$ 的信息然后对自己操作。

最后，我们找到最小的 $ans$ 使得 $dp_{root,ans}=1$ 即可。

复杂度 $O(n\log^2a_i)$，因为有一个背包合并。但是由于笛卡尔树上有两个儿子的节点数最多是差不多 $\frac{n}{2}$ 个，所以较小常数的实现还是可以轻松通过的。

代码较丑，仅供参考。

（注：因为 $\lceil\dfrac{a}{b}\rceil=1+\lfloor\dfrac{a-1}{b}\rfloor$，$\lceil\dfrac{\lceil\dfrac{a}{b}\rceil}{c}\rceil=1+\lfloor\dfrac{\lfloor\dfrac{a-1}{b}\rfloor}{c}\rfloor$，代码中一律使用下取整的方式处理。具体的，把所有的 $a_i$ 先减去 1，然后把判定条件改为全部除成 0。）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(ll i=a;i<=b;i++)
#define wt int tt=d;while(tt--)
#define py puts("Yes")
#define pn puts("No")
#define pritnf printf
#define edfl endl
#define fe(i,e) for(int i=0;i<e.size();i++)
#define vi vector<ll>
inline ll rd() {
	ll x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
namespace binom{
	const ll Lim=300010,mod=998244353;
	ll jc[Lim],inv[Lim],inc[Lim];
	void pre(){
		jc[0]=jc[1]=inc[0]=inc[1]=inv[0]=inv[1]=1;
		f(i,2,Lim-1)jc[i]=jc[i-1]*i%mod,inv[i]=(mod-mod/i)*inv[mod%i]%mod,
		inc[i]=inc[i-1]*inv[i]%mod;
	}ll C(ll n,ll m){if(n<0||m<0||n<m)return 0;return jc[n]*inc[m]%mod*inc[n-m]%mod;}
}
// using namespace binom;
ll dx[4]={0,1,0,-1};
ll dy[4]={1,0,-1,0};
#define d rd()
#define pb push_back
const ll N=300010;
struct edge{ll v,w,nx;}e[N<<1];
ll hd[N],cnt;
void add(ll u,ll v,ll w){e[++cnt]=(edge){v,w,hd[u]};hd[u]=cnt;}
ll qp(ll a,ll b,ll p){
	ll ans=1;while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;b>>=1;
	}return ans;
}ll n,m;
ll a[500010],b[500010];
ll l[500010],r[500010];
ll st[500010],tp;
ll dp[500010][70];
ll rt;
void dfs(ll u){
    if(l[u]+r[u]==0){
        dp[u][0]=a[u];
        f(i,1,63)dp[u][i]=dp[u][i-1]/b[u];
        return;
    }if(l[u]*r[u]==0){ll s=(l[u]==0?r[u]:l[u]);dfs(s);
        f(i,0,63)dp[u][i]=max(a[u],dp[s][i]);
        f(i,1,63)dp[u][i]=min(dp[u][i],dp[u][i-1]/b[u]);
        return;
    }
    dfs(l[u]),dfs(r[u]);
    f(i,0,63)f(j,0,i)dp[u][i]=min(dp[u][i],max(a[u],max(dp[l[u]][j],dp[r[u]][i-j])));
    f(i,1,63)dp[u][i]=min(dp[u][i],dp[u][i-1]/b[u]);
}
int main(){
	wt{
        n=d;
        f(i,1,n)a[i]=d-1;
        f(i,1,n)b[i]=d,l[i]=r[i]=0;
        tp=0;st[++tp]=1;
        f(i,2,n){
            while(tp&&b[i]<b[st[tp]])l[i]=st[tp--];
            if(tp)r[st[tp]]=i;st[++tp]=i;
        }rt=st[1];
        f(i,1,n)f(j,0,63)dp[i][j]=4000000000000000000;
        dfs(rt);
        f(i,0,63)if(dp[rt][i]==0){cout<<i<<endl;break;}
    }
	return 0;
}
```

---

## 作者：xAlec (赞：6)

[Problem](https://www.luogu.com.cn/problem/CF2048F)

## statement

给定长度为 $n$ 的数组 $a,b$，每次操作可以任意选择一个区间 $[l,r]$，记 $x = \displaystyle\min_{l \leq i \leq r}b_i$，然后 $\forall a_i(i \in [l,r]),a_i \leftarrow \lfloor{\frac{a_i}{x}}\rfloor$，求最终使得 $a_i$ 均变为 $1$ 的最小操作次数。

## solution

补题听学长讲的。

首先观察数据范围，发现 $b_i$ 下界为 $2$，意味着每次操作选取整段，最多 $\log a_i$ 此操作，约为 $60$，十分可做。

在我们钦定 $b_i$ 为一个包含它的区间的最小值时，选取一段极长区间并不会对答案产生劣的影响，也就是说，选取区间存在包含性，因此考虑建笛卡尔树。

记 $dp_{i,j}$ 表示 $i$ 号点值为 $j$ 的最小操作次数，由于值域 $V \leq 10^{18}$，考虑将第二维与定义交换，即 $dp_{i,j}$ 表示 $i$ 节点在最小操作次数为 $j$ 时的值，转移如下：

$$
\begin{aligned}
tmp &\leftarrow \max\{a_u,\max\{dp_{u,j},dp_{v,k}\}\}
\\
dp_{u,j + k} &\leftarrow \min\{dp_{i,j + k},tmp\}
\\
dp_{u,j} &\leftarrow \min\{dp_{i,j},\lceil{\frac{dp_{u,j - 1}}{b_u}}\rceil\}
\end{aligned}
$$

其中 $u,v$ 分别表示子树根的左右儿子。

答案为 $dp_{root,i} = 1$ 时的 $i$。

## code

[Submission](https://codeforces.com/contest/2048/submission/297427733)

---

## 作者：_lmh_ (赞：4)

$\lceil\frac{\lceil\frac{x}{a}\rceil}{b}\rceil=\lceil\frac{x}{ab}\rceil=\lceil\frac{\lceil\frac{x}{b}\rceil}{a}\rceil$，所以操作顺序不会影响结果。（设 $x=kab-r(0\le r<ab)$，读者自证不难）

注意到 $b_i\ge 2$，所以每次选 $[1,n]$ 一定能在 $\log_2V<64$ 次之内完成。（这里 $V=10^{18}$ 为值域）

看见区间最小值的操作直接对序列建笛卡尔树。说人话就是，对于一个区间 $[l,r]$ 每次选出其中最小的 $b_u$，对 $[l,u-1]$ 和 $[u+1,r]$ 递归处理之后算跨越 $u$ 的操作。不需要显式地把这棵树建出来。

先考虑跨越 $u$ 的操作。由于每次操作 $a$ 单调不降，所以每次都对 $[l,r]$ 操作显然最优。这就启发我们只记录 $a$ 的最大值。

朴素的 dp 状态是 $f_{u,x}$ 代表 $[l,r]$ 区间内（$u$ 和有效的 $[l,r]$ 一一对应）$a$ 最大值为 $x$ 最少需要多少步。现在交换状态定义域和值域，重新定义 $f_{u,i}$ 代表区间内进行 $i$ 次操作 $a$ 最大值的最小值。

先考虑不跨越 $u$ 的操作，可以枚举左右两个区间的操作次数。

再考虑跨越 $u$ 的操作。我们可以把这次操作用到左右的区间里（也就是 $f_{u,i}$ 不变），也可以从 $f_{u,i-1}$ 用一次操作转移过来。

最后找到第一个等于 $1$ 的 $f$ 即可。时间复杂度 $O(n\log^2V)$，如果使用了单 $\log$ 的方法建笛卡尔树则为 $O(n\log n+n\log^2V)$。

记得卡常。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lson (u<<1)
#define rson (u<<1|1)
const ll N=200007;
ll T,n,a[N],b[N],ans[N][64],root,pos[N<<2];
void build(ll u,ll l,ll r){
	if (l==r){
		pos[u]=l;return;
	}
	int mid=l+r>>1;
	build(lson,l,mid);build(rson,mid+1,r);
	if (b[pos[lson]]<=b[pos[rson]]) pos[u]=pos[lson];
	else pos[u]=pos[rson];
}
int query(int u,int l,int r,int L,int R){
	if (L<=l&&r<=R) return pos[u];
	int mid=l+r>>1;
	if (R<=mid) return query(lson,l,mid,L,R);
	if (L>mid) return query(rson,mid+1,r,L,R);
	int p1=query(lson,l,mid,L,R),p2=query(rson,mid+1,r,L,R);
	if (b[p1]<=b[p2]) return p1;return p2;
}
ll dfs(int l,int r){
	if (l>r) return 0;
	if (l==r){
		ans[l][0]=a[l];
		for (int i=1;i<64;++i) ans[l][i]=(ans[l][i-1]-1)/b[l]+1;
		return l;
	}
	ll u=query(1,1,n,l,r);
	ll pl=dfs(l,u-1),pr=dfs(u+1,r);
	for (int i=0;i<64;++i) ans[u][i]=max(ans[pl][0],ans[pr][i]);
	for (int i=1;i<64;++i) for (int j=0;i+j<64;++j) ans[u][i+j]=min(ans[u][i+j],max(ans[pl][i],ans[pr][j]));
	ans[u][0]=max(ans[u][0],a[u]);
	for (int i=1;i<64;++i) ans[u][i]=min(max(ans[u][i],a[u]),(ans[u][i-1]-1)/b[u]+1);
	return u;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for (int i=1;i<=n;++i) cin>>a[i];
		for (int i=1;i<=n;++i) cin>>b[i];
		build(1,1,n);
		root=dfs(1,n);
		for (int i=0;i<64;++i) if (ans[root][i]==1){
			cout<<i<<'\n';break;
		}
	}
	return 0;
}
```

---

## 作者：Cindy_Li (赞：2)

#### 题意

给定两个长为 $n$ 的序列 $a,b$。

选择两个整数 $1 \leq l \leq r \leq n$，设 $x = \min_{l \leq i \leq r} b_i$，将所有 $l \leq i \leq r$ 的 $a_i$ 修改为 $\left \lceil \frac{a_i}{x} \right\rceil$。

求所有 $a_i$ 都变为 1 所需的最小操作次数，$n\leq 10^5$，$b_i\ge 2$。

#### 题解

注意到总操作次数上界是 $\log$，区间最小值直接上笛卡尔树，每次操作极大支配区间肯定不劣。

$f(u,i)$ 表示 $u$ 子树内操作 $i$ 次后 $\max a_i$ 的最小值，暴力背包合并即可。

复杂度 $O(n\log^2 n)$。

```c++
#include<bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define REPG(i,g,x) for(int i=g.head[x];~i;i=g.edge[i].nxt)
#define LL long long
 
template<class T>
inline void read(T &x){
    T s=0,f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=getchar()) s=s*10+c-'0';
    x=s*f;
}

const int N=2e5+5,CF=20;
LL a[N],b[N];
int n;
int ls[N],rs[N];
int st[N],tl;
inline void build(){
    tl=0;
    rep(i,1,n){
        ls[i]=rs[i]=0;
        while(tl && b[st[tl]]>b[i]) ls[i]=st[tl],tl--;
        rs[st[tl]]=i;st[++tl]=i;
    }
}

namespace ST{
    LL st[CF][N];
    inline void init(){
        rep(i,1,n) st[0][i]=a[i];
        rep(j,1,18) rep(i,1,n-(1<<j)+1)
            st[j][i]=max(st[j-1][i],st[j-1][i+(1<<(j-1))]);
    }
    inline LL query(int l,int r){
        if(l==r) return st[0][l];
        int lg=log2(r-l);
        return max(st[lg][l],st[lg][r-(1<<lg)+1]);
    }
}

LL f[N][3*CF+5];
inline void dfs(int u,int l,int r){
    if(!u) return;
    dfs(ls[u],l,u-1),dfs(rs[u],u+1,r);
    f[u][0]=ST::query(l,r);rep(i,1,60) f[u][i]=f[u][0];
    int mxl=0,mxr=0;
    rep(i,0,60){
        f[u][i]=min(f[u][i],max(a[u],max(f[ls[u]][mxl],f[rs[u]][mxr])));
        if(f[ls[u]][mxl]>f[rs[u]][mxr]) mxl++;
        else mxr++;
    }
    rep(i,1,60) f[u][i]=min(f[u][i],(f[u][i-1]+b[u]-1)/b[u]);
}
inline void work(){
    read(n);
    rep(i,1,n) read(a[i]);
    rep(i,1,n) read(b[i]);
    build();
    ST::init();
    dfs(st[1],1,n);
    rep(i,0,60) if(f[st[1]][i]==1) return printf("%d\n",i),void();
}

int main(){
    int T;read(T);
    while(T--) work();
    return 0;
}
```

---

## 作者：gdf_yhm (赞：1)

[CF2048F](https://www.luogu.com.cn/problem/CF2048F)

[my blog](https://yhddd123.github.io/post/cf2048f-ti-jie/)

### 思路

如果想操作 $b_p$，选可以选的最长区间不劣，那可以选的区间即为小根笛卡尔树上 $p$ 对应的区间。只有 $O(n)$ 个包含关系成树的可行操作区间，从下往上操作。可以设 $dp_{u,v}$ 表示操作完 $u$ 的子树，$u$ 对应的区间中 $a_u$ 的最大值最小为 $v$，最少做几次。注意到至多只会操作 $\log V$ 次，交换 dp 的状态和答案，$dp_{u,i}$ 表示 $u$ 子树内做 $i$ 次 $a_u$ 的最大值最小为多少。暴力合并复杂度 $O(n\log V)$。

分步转移，$dp_{u,i}=\min_{j+k=i}(\max (dp_{ls,j},dp_{rs,k}))$。$dp_{u,i}$ 单调，min-max 卷积可以 $O(siz)$ 归并的合并。$dp_{u,i}=\max(dp_{u,i},a_u)$，$dp_{u,i}=\min(dp_{u,i},\lceil \frac{dp_{u,i-1}}{b_u}\rceil)$。复杂度 $O(n\log V)$。

### code

```cpp
int n,a[maxn],b[maxn];
int st[18][maxn];
bool cmp(int u,int v){return b[u]<b[v];}
int que(int l,int r){
	int k=__lg(r-l+1);
	return min(st[k][l],st[k][r-(1<<k)+1],cmp);
}
vector<int> dp[maxn];
vector<int> merge(vector<int> u,vector<int> v){
	if(!u.size())return v;
	if(!v.size())return u;
	vector<int> res;res.pb(max(u[0],v[0]));
	int p=1,q=1;
	while(p<u.size()&&q<v.size()){
		if(max(u[p],v[q-1])<max(u[p-1],v[q]))res.pb(max(u[p],v[q-1])),p++;
		else res.pb(max(u[p-1],v[q])),q++;
	}
	while(p<u.size())res.pb(max(u[p],v.back())),p++;
	while(q<v.size())res.pb(max(u.back(),v[q])),q++;
	res.resize(60);
	return res;
}
int idx;
int sovle(int l,int r){
	if(l>r)return 0;
	int nd=++idx;dp[nd].resize(60);
	if(l==r){
		for(int i=0,v=a[l];i<60;i++)dp[nd][i]=v,v=(v+b[l]-1)/b[l];
		return nd;
	}
	int mid=que(l,r),ls=sovle(l,mid-1),rs=sovle(mid+1,r);
	dp[nd]=merge(dp[ls],dp[rs]);
	for(int i=0;i<60;i++)dp[nd][i]=max(dp[nd][i],a[mid]);
	for(int i=1;i<60;i++)dp[nd][i]=min(dp[nd][i],(dp[nd][i-1]+b[mid]-1)/b[mid]);
	return nd;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)st[0][i]=i;
	for(int j=1;j<18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)],cmp);
	}
	idx=0;sovle(1,n);
	int pos=60;for(int i=59;~i;i--)if(dp[1][i]==1)pos=i;
	printf("%lld\n",pos);
}
```

---

## 作者：happybob (赞：1)

题意：

给定 $n$ 和两个长度为 $n$ 的正整数序列 $a_1,a_2,\cdots,a_n$ 与 $b_1,b_2,\cdots,b_n$。你要进行若干次操作，每次操作选择正整数 $1 \leq l \leq r \leq n$，令 $k=\min \limits_{i=l}^r b_i$，然后依次对于所有 $l \leq i \leq r$，将 $a_i$ 更改为 $\lceil \dfrac{a_i}{k} \rceil$。求使得序列 $a$ 中每个数都变为 $1$ 的最小操作次数。你只需要求出最小操作次数，不需要给出构造。

$1 \leq n \leq 2 \times 10^5$，$1 \leq a_i \leq 10^{18}$，$2 \leq b_i \leq 10^{18}$。时限 $2$ 秒，空间限制 $1$ GB。

解法：

首先，答案不超过 $60$。每次选择区间 $[1,n]$ 即可。根据计算 $10^{18}$ 不断除以 $2$ 并上取整，$60$ 次就会变为 $1$。

另一方面，显然每次选择的区间必为 $b$ 的小根笛卡尔树上某个点代表的子树区间。

考虑在 $b$ 的小根笛卡尔树上树形 DP，记 $f_{i,j}$ 表示 $i$ 子树内操作 $j$ 次，子树内最大值最小是多少。转移时直接模拟可以做到 $O(n \log^2 V)$，适当卡常可以通过。

[Submission Link.](https://codeforces.com/contest/2048/submission/297328622)

进一步，对于固定的 $i$，随着 $j$ 增大，$f_{i,j}$ 单调不增。注意到转移的本质是计算 $c_i = \min \limits_{0 \leq x \leq i} \left( \max(a_x,b_{i-x})\right)$，即 $\min - \max$ 卷积，由于 $a,b$ 单调不升，类似归并排序即可做到 $O(\log V)$ 转移。

---

## 作者：R_shuffle (赞：0)

不妨先考虑每次操作的实质，由于区间的大小是无关紧要的，所以一定会尽可能大的区间操作。所以考虑每次选哪个位置的 $b_i$，然后再考虑尽可能的大的区间。

所以实际上就是笛卡尔树，考虑每次选出区间最小值作为子树的根，然后左右两边递归下去处理。不难发现操作次数是 $O(\log (\max a_i))$ 的，所以考虑记录 $f_{i,j}$ 表示笛卡尔树上节点 $i$ 及其子树上操作了 $j$ 次，所能得到的区间最大值的最小可能。每次考虑左右子树合并，再枚举子树的根操作了多少次，由于一个节点最坏情况下是需要 $O(\log^2(\max a_i))$ 去转移的，所以复杂度最坏就是 $O(n\log^2(\max a_i))$ 的。

---

## 作者：ran_qwq (赞：0)

upd on 2025/2/24：修改了一处笔误。

Observation 1：令 $a_i\leftarrow a_i-1$，最后目标是变成 $0$，上取整变成下取整。因为 $\lceil\dfrac{a_i}x\rceil=\lfloor\dfrac{a_i-1}x\rfloor+1$。

Observation 2：$\lfloor\frac{\lfloor \frac Ax\rfloor}y\rfloor=\lfloor\frac{\lfloor \frac Ay\rfloor}x\rfloor$，即操作顺序不影响结果。

Observation 3：由于 $b_i\ge2$，即如果每次都是对整个区间操作，只需 $\log V$ 次可变成 $0$。

Observation 4：对于一个 $b_i$，保证 $b_i$ 不变的情况下，取极长的区间不劣。即设左边第一个 $b_j<b_i$ 的位置为 $l_i$，右边第一个 $b_j<b_i$ 的位置为 $r_i$，则取 $(l_i,r_i)$ 不劣，还是因为 $b_i\ge 2$，操作的越多，变成 $0$ 的机会就越大。

建出笛卡尔树，在笛卡尔树上 dp。设 $f_{u,i}$ 表示 $u$ 的子树，当前操作 $i$ 次，子树内最大的 $a$ 值。

操作有两种：一是儿子的操作合并上来，二是对当前区间操作。合并相当于树上背包，$f_{u,i}\leftarrow\min\limits_j\max(\{f_{l_u,j},f_{r_u,i-j},a_u\})$。对当前区间操作就是 $f_{u,i}$ 继承 $f_{u,i-1}$，$f_{u,i}\leftarrow \lfloor\dfrac{f_{u,i-1}}{b_u}\rfloor$。

由于只需 $\log V$ 次操作，时间复杂度 $O(n\log^2V)$。

```cpp
int n,tp,l[N],r[N],st[N]; ll a[N],b[N],g[61],f[N][61];
void dfs(int u) {
	if(!l[u]&&!r[u]) {
		f[u][0]=a[u];
		for(int i=1;i<=60;i++) cminll(f[u][i],f[u][i-1]/b[u]);
	} else if(l[u]&&!r[u]) {
		dfs(l[u]);
		for(int i=0;i<=60;i++) f[u][i]=min(i?f[u][i-1]/b[u]:INFll,max(f[l[u]][i],a[u]));
	} else if(!l[u]&&r[u]) {
		dfs(r[u]);
		for(int i=0;i<=60;i++) f[u][i]=min(i?f[u][i-1]/b[u]:INFll,max(f[r[u]][i],a[u]));
	} else {
		dfs(l[u]),dfs(r[u]);
		for(int i=0;i<=60;i++) {
			if(i) f[u][i]=f[u][i-1]/b[u];
			for(int j=0;j<=i;j++) cminll(f[u][i],max({f[l[u]][j],f[r[u]][i-j],a[u]}));
		}
	}
}
void QwQ() {
	n=rd(),tp=0;
	for(int i=1;i<=n;i++) mst(f[i],0x3f),l[i]=r[i]=0;
	for(int i=1;i<=n;i++) a[i]=rdll()-1;
	for(int i=1;i<=n;i++) b[i]=rdll();
	for(int i=1,j;i<=n;i++) {
		for(;tp&&b[st[tp]]>b[i];) l[i]=st[tp--];
		if(tp) r[st[tp]]=i; st[++tp]=i;
	}
	dfs(st[1]);
	for(int i=0;i<=60;i++) if(!f[st[1]][i]) return wr(i,"\n");
}
```

---

## 作者：subcrip (赞：0)

$O(n\log^2 U)$ 的解法题解区已经讲的差不多了，但是由于我既不会笛卡尔树也不会 minmax 卷积，所以这里提供一个复杂度更低 $O(n\log n\log U)$ 但比较简单的优化。

首先可以注意到以下结论：

1. 一共有至多 $n$ 个极大的操作区间，这里的极大指的是如果再想向两边扩展，则一定会使得区间的 $b$ 最小值减小；
2. 答案不超过 $64$。

因此，可以先分治子区间，求出数组 $dp_{ij}$ 表示第 $i$ 个子区间操作 
$j$ 次后区间 $a$ 最大值的最小值。然后再把子区间合并上来。

问题在于如何合并。如果采用类似树形背包的合并方法，由于这里并不是树形背包，所以复杂度是暴力的 $O(n\log^2U)$，差不多 $8\times 10^8$ 级别。由于我人傻常数大，所以估计不卡半天常肯定过不去。

但是可以用一个大根堆维护一下每个子区间的 $a$ 最大值，每次操作堆顶表示的子区间即可让最大值减小。这样操作 $64$ 次可以得到 $g_{ij}$，表示 $i$ 的**子区间**总共操作 $j$ 次后，子区间 $a$ 最大值的最小值。再通过 DP 转移

$$
dp_{ij}\leftarrow\min\left(\left\lceil\dfrac{dp_{i,j-1}}x\right\rceil,g_{ij}\right)
$$

即可求出 $dp_i$ 的值。总时间复杂度 $O(n\log n\log U)$，其中 $U$ 是值域大小。[代码](https://codeforces.com/contest/2048/submission/304542104)

---

