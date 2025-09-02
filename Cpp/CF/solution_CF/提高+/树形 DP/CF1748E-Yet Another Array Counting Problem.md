# Yet Another Array Counting Problem

## 题目描述

对于长度为 $n$ 的序列 $x$，定义其在子段 $[l;r]$ 的“最左端最大值位置”为最小的满足 $l\leq i\leq r$ 且 $x_i=\max_{j=l}^rx_j$ 的整数 $i$。  
给定整数 $n,m$ 和长度为 $n$ 的序列 $a$，你需要求出满足下列要求的序列 $b$ 的数量：

- 序列 $b$ 长度为 $n$，且对任意整数 $i(1\leq i\leq n)$ 都有 $1\leq b_i\leq m$ 成立。
- 对任意整数 $l,r(1\leq l\leq r\leq n)$，总有 $a,b$ 在子段 $[l;r]$ 的“最左端最大值位置”相同。

答案对 $10^9+7$ 取模。  
每个测试点包含多组数据。

## 样例 #1

### 输入

```
4
3 3
1 3 2
4 2
2 2 2 2
6 9
6 9 6 9 6 9
9 100
10 40 20 20 100 60 80 60 60```

### 输出

```
8
5
11880
351025663```

# 题解

## 作者：TernaryTree (赞：14)

简单笛卡尔树上 dp。

前置知识：笛卡尔树。

根据大根堆性质建出笛卡尔树，那么 $[l,r]$ 的“最左端最大值位置”就是 $l$ 和 $r$ 在笛卡尔树上的 $\textrm{lca}$。

若两个序列的所有“最左端最大值”都相等，那么意味着这两个序列所建出的笛卡尔树形态相同。转换为权值 $\le m$ 的笛卡尔树计数问题。

不妨设 $f_{u,j}$ 表示笛卡尔树上点 $u$ 权值为 $j$，其子树的答案。则有

$$f_{u,j}=\sum_{k=1}^{j-1}f_{lc_u,k}\times \sum_{k=1}^{j}f_{rc_u,k}$$

时间复杂度 $\Theta(\sum n\times m)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;

int n, m, t;
int p[maxn];
int s[maxn], cnt;
int lc[maxn], rc[maxn];
vector<vector<int>> f;

void dfs(int u) {
    for (int i = 1; i <= m; i++) f[u][i] = 1;
    if (lc[u]) dfs(lc[u]);
    if (rc[u]) dfs(rc[u]);
    if (lc[u]) for (int i = 1; i <= m; i++) f[u][i] = f[u][i] * f[lc[u]][i - 1] % mod;
    if (rc[u]) for (int i = 1; i <= m; i++) f[u][i] = f[u][i] * f[rc[u]][i] % mod;
    for (int i = 2; i <= m; i++) f[u][i] = (f[u][i] + f[u][i - 1]) % mod;
}

signed main() {
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> p[i];
        for (int i = 1; i <= n; i++) {
            int top = cnt;
            while (top && p[s[top]] < p[i]) --top;
            if (top) rc[s[top]] = i;
            if (top < cnt) lc[i] = s[top + 1];
            s[cnt = ++top] = i;
        }
        f.resize(n + 1);
        for (int i = 1; i <= n; i++) f[i].resize(m + 1);
        dfs(s[1]);
        cout << f[s[1]][m] << endl;
        for (int i = 1; i <= cnt; i++) s[i] = 0;
        for (int i = 1; i <= n; i++) lc[i] = rc[i] = 0;
        cnt = 0;
    }
    
    return 0;
}

```

---

## 作者：江户川·萝卜 (赞：10)

以下简称 `leftmost-maximum` 为 $\text{lmax}$。

考虑把 $a_i$ 在哪些区间里成为 $\text{lmax}$ 分别拎出来。

对于 $a_i$ 从大到小，从左至右地看， 发现最大，最左的数一定是所有包含它的区间的 $\text{lmax}$。换句话说，若一个区间的 $\text{lmax}$ 是 $a_k$，那么在此区间内包含 $a_k$ 的子区间的 $\text{lmax}$ 都是它。于是把整个序列分成两个独立子区间（可能为空），可以分治下去然后再合并信息。

因此考虑 $\text{dp}$。

设在某个区间 $[L,R]$ 内的 $\text{lmax}$ 为 $k$，那么记 $\text{dp}_{k,j}$ 表示当 $b_k\le j$ 时 $b_L\dots b_R$ 的方案数。

又记 $[L,k-1]$ 的 $\text{lmax}$ 为 $k_L$，$[k+1,R]$ 的 $\text{lmax}$ 为 $k_R$，

那么根据 $\text{lmax}$ 的性质，$b_{k_L}<j$，$b_{k_R}\le j$，因此：

$$\text{dp}_{k,j}=\text{dp}_{k.j-1}+\text{dp}_{k_L,j-1}\times\text{dp}_{k_R,j}$$

注意特判子区间为空的情况。

至于如何计算一个区间内的 $\text{lmax}$，用 $\text{ST}$ 表或线段树等数据结构维护即可。

复杂度 $O(n\log n +nm)$，
```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define MOD 1000000007
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define N 500005
#define ls p<<1
#define rs p<<1|1
typedef long long ll;
using namespace std;
int a[N];
vector<ll> dp[200005];
int n,m;
int ind[8000005];
inline void pushup(int p){
    if(a[ind[ls]]<a[ind[rs]]) ind[p]=ind[rs];
    else ind[p]=ind[ls];
}
void build(int p,int l,int r){
    if(l==r){
        ind[p]=l;
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
}
int query(int p,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr) return ind[p];
    int mid=l+r>>1,res=0;
    if(ql>mid) return query(rs,mid+1,r,ql,qr);
    else if(qr<=mid) return query(ls,l,mid,ql,qr);
    res=query(ls,l,mid,ql,qr);
    int k=query(rs,mid+1,r,ql,qr);
    if(a[res]<a[k]) return k;
    else return res;
}
int dfs(int l,int r){ 
    if(l>r) return -1;
    if(l==r){
        for(int i=1;i<=m;i++) dp[l][i]=i;
        return l;
    }
    int id=query(1,1,n,l,r);
    int L=dfs(l,id-1);
    int R=dfs(id+1,r);
    if(L==-1){
        for(int i=1;i<=m;i++) dp[id][i]=dp[R][i]+dp[id][i-1],dp[id][i]%=MOD;
    }
    else if(R==-1){
        for(int i=1;i<=m;i++) dp[id][i]=dp[L][i-1]+dp[id][i-1],dp[id][i]%=MOD;
    }
    else{
        for(int i=1;i<=m;i++) dp[id][i]=dp[L][i-1]*dp[R][i]%MOD+dp[id][i-1],dp[id][i]%=MOD;
    }
    return id;
}
void solve(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],dp[i].clear(),dp[i].resize(m+1);
    build(1,1,n);
    int x=dfs(1,n);
    cout<<dp[x][m]<<'\n';
}
int main(){
//    std::ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int Case;cin>>Case;while(Case--)
    solve();
}
```

---

## 作者：Hovery (赞：5)

先考虑 $1\sim n$ 中最大值最左的位置 $pos$，只要包含它的区间，那所有题目要求的值是一样的。

这样就可以对于一段区间最大值最左的位置进行分治。

考虑答案怎么处理。

首先发现 $\sum n\times m\le10^6$，说明可以存每个位置填了哪些数。

设 $dp_{i,j}$ 表示在第 $i$ 个位置填了 $j$ 并且合法的方案数。

观察这个位置 $pos$，有 $\forall l\le i < pos\ a_i<a_{pos},\forall pos < i \le r\ a_i\le a_{pos}$。

所以转移就有 $dp_{i,j}=\sum\limits_{a=1}^{j-1}\sum\limits_{b=1}^j dp_{ls,a} \times dp_{rs, b}$，发现式子里的可以前缀和优化做到 $\Theta(1)$。

对于每次找区间的这个位置，用 ST 表维护即可。

总复杂度是 $\Theta(\sum n\times m+n\log n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define pii pair<int, int>
#define fi first
#define se second
#define pb push_back
using namespace std;

const int mod = 1e9 + 7;

int a[200010];
int st[18][200001], pos[18][200001];
int Log[200010], len[18];

void init()
{
    for (int i = 2;i <= 200000;i++)
    Log[i] = Log[i >> 1] + 1;
    len[0] = 1;
    for (int i = 1;i <= 17;i++)
    {
        len[i] = len[i - 1] * 2;
    }
}

int qry(int l, int r)
{
    int low = Log[r - l + 1];
    r = r - len[low] + 1;
    if (st[low][l] >= st[low][r])
    return pos[low][l];
    return pos[low][r];
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector< vector<int> > dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1;i <= n;i++)
    {
        cin >> a[i];
    }
    for (int i = 1;i <= Log[n];i++)
    {
        for (int j = 1;j <= n;j++)
        {
            st[i][j] = pos[i][j] = 0;
        }
    }
    for (int i = 1;i <= n;i++)
    {
        st[0][i] = a[i];
        pos[0][i] = i;
    }
    for (int j = 1;j <= 17;j++)
    {
        for (int i = 1;i <= n - len[j] + 1;i++)
        {
            if (st[j - 1][i] >= st[j - 1][i + len[j - 1]])
            {
                st[j][i] = st[j - 1][i];
                pos[j][i] = pos[j - 1][i];
            }
            else
            if (st[j - 1][i] < st[j - 1][i + len[j - 1]])
            {
                st[j][i] = st[j - 1][i + len[j - 1]];
                pos[j][i] = pos[j - 1][i + len[j - 1]];
            }
        }
    }

    auto dfs = [&](auto &self, int l, int r) -> int
    {
        if (l > r)
        {
            return 0;
        }
        if (l == r)
        {
            for (int i = 1;i <= m;i++)
            {
                dp[l][i] = i;
            }
            return l;
        }
        int _ = qry(l, r);
        int ls = self(self, l, _ - 1), rs = self(self, _ + 1, r);

        for (int i = 1;i <= m;i++)
        {
            if (ls && rs)
            dp[_][i] = dp[ls][i - 1] * dp[rs][i] % mod + dp[_][i];
            if (ls && rs == 0)
            dp[_][i] = dp[ls][i - 1] + dp[_][i];
            if (ls == 0 && rs)
            dp[_][i] = dp[rs][i] + dp[_][i];
            dp[_][i] %= mod;
        }

        for (int i = 1;i <= m;i++)
        {
            dp[_][i] = (dp[_][i] + dp[_][i - 1]) % mod;
        }

        return _;
    };

    cout << dp[dfs(dfs, 1, n)][m] << '\n';

    dp.shrink_to_fit();

    return;
}

signed main()
{
    IOS;
    int t = 1;
    cin >> t;
    init();
    while (t--)
    {
        solve();
    }
}
```

---

## 作者：jiangtaizhe001 (赞：2)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16886525.html)

[题目传送门](https://codeforces.com/contest/1748/problem/E)

### 题目大意
给定一个长度为 $n$ 的序列 $a$ 和 $m$，定义 $[l,r]$ 的 _最左边的最大值_ 为 最小的 $l\le i\le r$ 满足 $x_i=\max\{a_l,a_{l+1},\dots,a_r\}$  
求满足以下条件的长度为 $n$ 的序列 $b$ 的数量

- 对于所有的 $1\le i\le n$，有 $1\le b_i\le m$
- 对于所有的 $1\le l\le r\le n$，满足序列 $a$ 的区间 $[l,r]$ 的 _最左边的最大值_ 等于序列 $b$ 的区间 $[l,r]$ 的 _最左边的最大值_

答案对 $10^9+7$ 取模  
$2\le n,m\le 10^5$，$1\le a_i\le m$，$n\cdot m\le 10^6$，$\sum n\cdot m\le 10^6$  
### 题目解析
> 讲个笑话，这个东西叫笛卡尔树，在HHHOJ模拟赛考了不下五次   
——@[275307894a](https://www.luogu.com.cn/user/181766)

原来小丑竟是我自己。（HHHOJ 为某中学内部 OJ）

我们发现，对于序列 $a$ 的任意一个区间 $[L,R]$，如果 $[L,R]$ 的 _最左边的最大值_ 为 $t$，那么不难发现：

- 对于 $L\le l\le t\le r\le R$，$[l,r]$ 的 _最左边的最大值_ 为 $t$
- 对于 $L\le l\le r< t$，$[l,r]$ 的 _最左边的最大值_ $p$ 满足 $a_p<a_t$
- 对于 $L\le l\le r< t$，$[l,r]$ 的 _最左边的最大值_ $q$ 满足 $a_q\le a_t$  

根据以上性质，我们发现这样对于大小的限制就递归到了两个子区间内。  
我们可以用一些数据结构（我写了个线段树）来快速查找任意子区间的 _最左边的最大值_ ，这样我们就可以把所有关于大小的约束建立起来。  
不难发现最后所有的大小约束关系会变成一棵二叉树，然后在上面跑 DP 就可以了。设 $f_{i,j}$ 为节点 $i$ 为 $j$ 的时候这棵子树的方案数，然后直接 DP 转移即可。$f_{i,j}$ 计算完之后，需要计算 $j$ 一维前缀和方便接下来的转移。  
时间复杂度 $O(nm+n\log n)$
```cpp
#include<cstdio>
#define db double
#define gc getchar
#define pc putchar
#define U unsigned
#define ll long long
#define ld long double
#define ull unsigned long long
#define Tp template<typename _T>
#define Me(a,b) memset(a,b,sizeof(a))
Tp _T mabs(_T a){ return a>0?a:-a; }
Tp _T mmax(_T a,_T b){ return a>b?a:b; }
Tp _T mmin(_T a,_T b){ return a<b?a:b; }
Tp void mswap(_T &a,_T &b){ _T tmp=a; a=b; b=tmp; return; }
Tp void print(_T x){ if(x<0) pc('-'),x=-x; if(x>9) print(x/10); pc((x%10)+48); return; }
#define EPS (1e-7)
#define INF (0x7fffffff)
#define LL_INF (0x7fffffffffffffff)
#define maxn 200039
#define maxm 1000039
#define MOD 1000000007
#define Type int
#ifndef ONLINE_JUDGE
//#define debug
#endif
using namespace std;
Type read(){
	char c=gc(); Type s=0; int flag=0;
	while((c<'0'||c>'9')&&c!='-') c=gc(); if(c=='-') c=gc(),flag=1;
	while('0'<=c&&c<='9'){ s=(s<<1)+(s<<3)+(c^48); c=gc(); }
	if(flag) return -s; return s;
}
class SGT{//Segment Tree
	private:
		struct JTZ{ int maxx,pos; }sum[maxn<<2];
		JTZ merge(JTZ x,JTZ y){
			if(x.maxx!=y.maxx) return x.maxx>y.maxx?x:y;
			else return x.pos<y.pos?x:y;
		}
		int *arr,siz,L,R;
		void up(int rt){ sum[rt]=merge(sum[rt<<1],sum[rt<<1|1]); return; }
		void build(int l,int r,int rt){
			if(l==r){ sum[rt].maxx=arr[l]; sum[rt].pos=l; return; } int mid=(l+r)>>1;
			build(l,mid,rt<<1); build(mid+1,r,rt<<1|1); up(rt); return;
		}
		JTZ querymax(int l,int r,int rt){
			if(L<=l&&r<=R) return sum[rt]; int mid=(l+r)>>1; JTZ tmp;
			if(mid>=L){
				tmp=querymax(l,mid,rt<<1);
				if(mid<R) tmp=merge(tmp,querymax(mid+1,r,rt<<1|1));
			} else if(mid<R) tmp=querymax(mid+1,r,rt<<1|1); return tmp;
		}
	public:
		void init(int _siz,int *_arr){ siz=_siz; arr=_arr; build(1,siz,1); return; }
		int query(int l,int r){ L=l,R=r; return querymax(1,siz,1).pos; }
}tr;
struct Node{ int ls,rs; }bt[maxn]; int siz;//Binary Tree
int build(int l,int r){
	if(l>r) return 0; int mid=tr.query(l,r),tmp=++siz;
	bt[tmp].ls=build(l,mid-1); bt[tmp].rs=build(mid+1,r); return tmp;
}
int n,m,a[maxn]; ll f[maxm];
#define get(i,j) (((i)-1)*m+(j))
void dfs(int x){
	int i;
	if(!bt[x].ls&&!bt[x].rs) for(i=1;i<=m;i++) f[get(x,i)]=i%MOD;
	else if(!bt[x].ls&&bt[x].rs){
		dfs(bt[x].rs);
		for(i=1;i<=m;i++) f[get(x,i)]=f[get(bt[x].rs,i)];
		for(i=2;i<=m;i++) f[get(x,i)]+=f[get(x,i-1)],f[get(x,i)]%=MOD;
	} else if(bt[x].ls&&!bt[x].rs){
		dfs(bt[x].ls); f[get(x,1)]=0;
		for(i=2;i<=m;i++) f[get(x,i)]=f[get(bt[x].ls,i-1)];
		for(i=2;i<=m;i++) f[get(x,i)]+=f[get(x,i-1)],f[get(x,i)]%=MOD;
	} else{
		dfs(bt[x].ls); dfs(bt[x].rs); f[get(x,1)]=0;
		for(i=2;i<=m;i++) f[get(x,i)]=f[get(bt[x].ls,i-1)]*f[get(bt[x].rs,i)]%MOD;
		for(i=2;i<=m;i++) f[get(x,i)]+=f[get(x,i-1)],f[get(x,i)]%=MOD;
	} return;
}
void work(){
	n=read(); m=read(); int i; for(i=1;i<=n;i++) a[i]=read();
	tr.init(n,a); siz=0; build(1,n); for(i=1;i<=n*m;i++) f[i]=0;
	dfs(1); print(f[m]),pc('\n'); return;
}
int main(){
#ifdef LOCAL
	freopen("1.in","r",stdin);
#endif
	int T=read(); while(T--) work(); return 0;
}
```

---

## 作者：Kingna (赞：1)

## [CF1748E Yet Another Array Counting Problem](https://www.luogu.com.cn/problem/CF1748E)

### 题目大意

对于长度为 $n$ 的序列 $x$，定义其在子段 $[l,r]$ 的“最左端最大值位置”为最小的满足 $l\leq i\leq r$ 且 $x_i=\max_{j=l}^rx_j$ 的整数 $i$。给定整数 $n,m$ 和长度为 $n$ 的序列 $a$，你需要求出满足下列要求的序列 $b$ 的数量：

- 序列 $b$ 长度为 $n$，且对任意整数 $i(1\leq i\leq n)$ 都有 $1\leq b_i\leq m$ 成立。
- 对任意整数 $l,r(1\leq l\leq r\leq n)$，总有 $a,b$ 在子段 $[l,r]$ 的“最左端最大值位置”相同。

### 题目思路

显然建立笛卡尔树找到区间最左端最大值位置。定义 $f_{i,j}$ 表示以 $i$ 为根节点且 $i$ 为最左端最大值 $j$ 所在位置的方案数。笛卡尔树本质上是找到最值位置，再将区间分成两半。那么我们设 $i$ 左边的区间是 $ls$，右边的区间是 $rs$，则有转移方程式：

$$f_{i,j}=\sum \limits _{k=1}^{j-1} f_{ls,k}\times \sum \limits _{k=1}^{j} f_{rs,k}$$

含义为左边区间最大值最多为 $j-1$，右边区间最大值最多为 $j$，因为 $i$ 这个位置满足最左端最大值的限制。其实转移区间怎么划分，就看给定的序列 $a$ 的最左端最大值的位置了。

代码：https://pastebin.com/Yz3pNBqL

---

## 作者：Chenyichen0420 (赞：1)

## 思路分析

首先，观察题目性质，最左端最大值位置可以视为双关键字排序的结果，其中第一关键字是值的大小，降序，第二关键字是下标的大小，升序。

这个性质，其实我们不难想到笛卡尔树。这时候我们可以维护这样一个笛卡尔树，其二叉搜索树性质维护下标，小者左，大者右；其堆性质维护权值，大根堆。

这样做完了之后呢？好像没了思路。没关系，我们再看其他性质。

我们还要求 $b$ 与 $a$ 在每一段的最左端最大值位置相同，这样子，由笛卡尔树在本题限制下的唯一构造性，不难知道两个树同构。

显然，我们只需要维护其堆性质合理即可。需要注意，在本题限制下，左子树的值严格小于父亲的值，右子树的值大于等于父亲的值。

因此，再结合一下题目中 $\Sigma n\times m\le1e6$，可以大胆猜测就是树上动规了。令 $dp_{i,j}$ 表示以 $i$ 为根，点 $i$ 值**不大于** $j$ 的同构树的个数。初

始状态下 $dp_{i,j}=1(i\in[1,n],j\in[1,m])$。

若 $p$ 有左子节点 $l_p$，则 $dp_{p,j}=dp_{p,j}\times dp_{l_p,j-1}$。

若 $p$ 有右子节点 $r_p$，则 $dp_{p,j}=dp_{p,j}\times dp_{r_p,j}$。

最后将 $dp_{p,j}$ 重新计算为 $\Sigma_{k=1}^jdp_{p,k}$，即计算根值不大于 $j$ 的同构树数量的前缀和。

代码如下，[记录](https://codeforces.com/problemset/submission/1748/291278852)：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int mod = 1e9 + 7;
int n, m, t, p[200005], s[200005], pt, l[200005], r[200005];
struct dynamic {
	int v[2000005];
	inline int& at(int l, int r) {
		return v[(l - 1) * (m + 1) + r + 1];
	}
}f;
inline void dfs(int p) {
	for (int i = 1; i <= m; i++) f.at(p, i) = 1;
	if (l[p] && (dfs(l[p]), 1))
		for (int i = 1; i <= m; i++)
			f.at(p, i) = f.at(p, i) * f.at(l[p], i - 1) % mod;
	if (r[p] && (dfs(r[p]), 1))
		for (int i = 1; i <= m; i++)
			f.at(p, i) = f.at(p, i) * f.at(r[p], i) % mod;
	for (int i = 2; i <= m; i++)
		f.at(p, i) = (f.at(p, i) + f.at(p, i - 1)) % mod;
}
signed main() {
	ios::sync_with_stdio(0);
	for (cin >> t; t; t--) {
		fill(s + 1, s + pt + 1, 0);
		fill(l + 1, l + n + 1, 0);
		fill(r + 1, r + n + 1, 0);
		cin >> n >> m >> p[1]; pt = s[1] = 1;
		for (int i = 2; i <= n; i++) {
			cin >> p[i];
			while (pt && p[s[pt]] < p[i]) pt--;
			if (pt) l[i] = r[s[pt]], r[s[pt]] = i;
			else l[i] = s[1]; s[++pt] = i;
		}
		fill(f.v + 1, f.v + (n + 1) * (m + 1), 0);
		dfs(s[1]); cout << f.at(s[1], m) << endl;
	}
}
```

---

## 作者：jamesharden666 (赞：1)

## 题目大意

有 $t$ 组数据，每次给定一个数组 $a$ 和 $m$，问你能构造出多少个不同的数组 $b$，使得 $\forall l,r \in[1,n]$ 最左边的最大值位置相同。

## 题目思路

设最左边的最大值的位置为 $k$，容易发现，所有 $[l,r]$ 的子区间只要包含 $k$，它最左边的最大值就是 $k$，所以考虑分治。

设 $f_{pos,j}$ 表示以 $pos$ 为最左边的最大值，$a_{pos}\leq j$ 的方案数。

分治时，我们可以用线段树维护当前区间最左边的最大值，在 $[l,pos-1]$ 中要小于 $j$，在 $[pos+1,r]$ 中要小于等于 $j$，$a_{pos} \in [1,j]$，所以状态转移方程式为 $f_{pos,j}=f_{pos,j-1}+f_{posl,j-1}*f_{posr,j}$。

其中 $posl$ 是 $[l,pos-1]$ 中最左边的最大值，$posr$ 是 $[l,pos-1]$ 中最左边的最大值。

答案即为 $f_{pos,m}$。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int q,n,m,a[200000+10];
long long ans=0;
vector<long long> f[200000+10]; 
const long long mod=1e9+7;
struct node
{
    int l,r,v,maxn;
}t[800000+10];
long long read()
{
    long long s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
        s=s*10+(ch-'0'),ch=getchar();
    return s*w;
}
void build(int root,int l,int r)
{
    t[root].l=l;
    t[root].r=r;
    if(l==r)
    {
        t[root].v=a[l];
        t[root].maxn=l;
        return ;
    }
    int mid=(l+r)>>1;
    build(root<<1,l,mid);
    build(root<<1|1,mid+1,r);
    if(t[root<<1].v>=t[root<<1|1].v)
    {
        t[root].v=t[root<<1].v;
        t[root].maxn=t[root<<1].maxn;
    }
    else
    {
        t[root].v=t[root<<1|1].v;
        t[root].maxn=t[root<<1|1].maxn;
    }
}
int ask(int root,int l,int r)
{
    if(t[root].l>=l&&t[root].r<=r)
        return t[root].maxn;
    if(t[root].l>r||t[root].r<l)
        return 0;
    long long val=0,pos=0;
    if(t[root<<1].r>=l)
    {
        int k=ask(root<<1,l,r);
        if(a[k]>val)
        {
            val=a[k];
            pos=k;
        }
    }
    if(t[root<<1|1].l<=r)
    {
        int k=ask(root<<1|1,l,r);
        if(a[k]>val)
        {
            val=a[k];
            pos=k;
        }
    }
    return pos;
}
int divide(int l,int r)
{
    if(l>r)
        return -1;
    if(l==r)
    {
        for(int i=1;i<=m;++i)
            f[l][i]=i;
        return l;
    }
    int pos=ask(1,l,r);
    int posl=divide(l,pos-1);
    int posr=divide(pos+1,r);
    if(posl==-1)
        for(int i=1;i<=m;++i)
            f[pos][i]=(f[pos][i-1]+f[posr][i]%mod)%mod;
    else if(posr==-1)
        for(int i=1;i<=m;++i)
            f[pos][i]=(f[pos][i-1]+f[posl][i-1]%mod)%mod;
    else    
        for(int i=1;i<=m;++i)
            f[pos][i]=(f[pos][i-1]+f[posl][i-1]*f[posr][i]%mod)%mod;
    return pos;
}
int main()
{
    q=read();
    while(q--)
    {
        n=read(),m=read();
        for(int i=1;i<=n;++i)
        {
            a[i]=read();
            f[i].clear();
            f[i].resize(m+10);
        }
        build(1,1,n);
        int pos=divide(1,n);
        printf("%lld\n",f[pos][m]);
    }   
    return 0;
}   
```





---

## 作者：Seven_07 (赞：0)

看了题解，想不到这是几年前的老题，本蒟蒻刚学笛卡尔树就做出来了。~（话说这道题还没关闭题解提交吗）~

言归正传，观察到题面中“区间最左段最大值”，判断出这题需要用笛卡尔树；而数据 $\sum n\times m\le10^6$ 提醒我们这题时间复杂度 $O(nm)$。

不多说了，直接说正解：先建笛卡尔树，然后树上 dp。

令 $dp_{i,j}$ 表示考虑了 $i$ 以及其所有子树，每个点取值小于等于 $j$ 时，满足条件的方案数。

接下来考虑转移：

- 对于叶子节点，显然有 $dp_{i,j}=j$。

- 否则，其次考虑该节点取值：若当前节点选 $j$，其左子树的所有点的取值都必须小于 $j$（不然有可能与题目要求矛盾），同理，右子树的所有点的取值必须不超过 $j$，注意是不超过（因为只考虑最左端）。

- 用 $l_i$表示节点 $i$ 的左儿子，$r_i$表示节点 $i$ 的右儿子，状态转移方程：$dp_{i,j} = dp_{l_i,j-1}\times dp_{r_i,j} + dp_{i,j-1}$。

答案为 $dp_{root,m}$。

代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define endl "\n"
using namespace std;
struct dkr{
	int l=0,r=0;
}tree[200005];
int a[200005];
int s[200005],top,n,m;
const ll mod = 1e9+7;
void dfs(int x,vector<vector<ll > >&dp){
	if(x==0)	return;
	dfs(tree[x].l,dp),dfs(tree[x].r,dp);
	if(tree[x].l==tree[x].r&&tree[x].l==0){//好像不用分类讨论？
		for(int i = 1;i <= m;i++){
			dp[x][i]=i%mod;
		}
	}
	else{
		for(int i = 1;i <= m;i++){
			dp[x][i]=(dp[tree[x].l][i-1]*dp[tree[x].r][i]%mod+dp[x][i-1])%mod;
		}
	}
	return;
}
int main(){
	int t; cin >> t;
	while(t--){
		cin >> n >> m;
		vector<vector<ll > >dp(n+5,vector<ll>(m+5,0));
		for(int i = 0;i <= m;i++)	dp[0][i]=1;//没有左/右儿子视为1 
		for(int i = 1;i <= n;i++){
			cin >> a[i];
		}
		top = 0;
		memset(tree,0,sizeof tree);
		for(int i = 1;i <= n;i++){//建树
			int k = 0;
			while(top&&a[s[top]]<a[i]){
				k = s[top];
				top--;
			}
			if(k)	tree[i].l = k;
			tree[s[top]].r = i;
			s[++top]=i;
		}
		dfs(s[1],dp);
		cout << dp[s[1]][m] <<endl;
	} 
	
	return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

## Solution CF1748E

### Idea

考虑如何使得 $a$ 和 $b$ 的最左端最大值位置相同：只需要 $a$ 和 $b$ 的笛卡尔树相同（相同值越靠左越优先）就可以了。

所以我们可以先建出序列 $a$ 的笛卡尔树。

紧接着我们在笛卡尔树上跑 dp。

设 $dp_{u,i}$ 表示当前笛卡尔树上节点 $u$ 的权值是 $i$ 的 $b$ 序列方案数。

那么有：

$$dp_{u,i}=\sum_{j=1}^{i-1}dp_{ls_u,j}\times \sum_{j=1}^idp_{rs_u,j}$$

为何左边只能到 $i-1$ 呢？因为如果左边出现了 $i$，那么最左端最大值位置就是那个靠左的位置而不是 $u$ 了。

注意根节点不是 $1$，而是最后留在单调栈里面的点：因为没有任何一个位置可以比它大从而把它从单调栈里踢出去，所以它才是笛卡尔树的根节点。

注意多测清空。

### Code

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=200005,mod=1e9+7;
int a[N],top,n,now;
int st[N],ls[N],rs[N],m;
vector<ll>dp[N];
inline int read() {
    int x=0,flag=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')flag=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+ch-'0';
    return x*flag;
}
void dfs(int now){
	for(int i=1;i<=m;i++)dp[now][i]=1;
	if(ls[now]){
		dfs(ls[now]);
	}
	if(rs[now])dfs(rs[now]);
	if(ls[now]){
		for(int i=1;i<=m;i++){
			dp[now][i]=dp[now][i]*dp[ls[now]][i-1]%mod;
		}
	} 
	if(rs[now]){
		for(int i=1;i<=m;i++){
			dp[now][i]=dp[now][i]*dp[rs[now]][i]%mod;
		}
	} 
	for(int i=1;i<=m;i++){
		dp[now][i]=(dp[now][i]+dp[now][i-1])%mod;
	}
}
void solve(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	now=0,top=0;
	for(int i=1;i<=n;i++){
		now=top;
		while(now&&a[st[now]]<a[i]){
			now--;
		}
		if(now)rs[st[now]]=i;
		if(now<top)ls[i]=st[now+1];
		st[++now]=i;
		top=now;
	}
	for(int i=0;i<=n+1;i++)dp[i].resize(m+2);
	dfs(st[1]);
	printf("%lld\n",dp[st[1]][m]%mod);
	for(int i=1;i<=n;i++){
		st[i]=0;
		ls[i]=0;
		rs[i]=0;
	}
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--)solve();
}

```

---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1748E)

有些人还是啥都不会。

看到题目应该能想到这是笛卡尔树的性质，因为每一对 $(l,r)$ 都满足最左端最大值位置相同，所以说明在笛卡尔树上，每一对点的 `lca` 相同，说明 $a$ 和 $b$ 序列的笛卡尔树相同。

我们以下标为键，$a_i$ 为值建立大根笛卡尔树，现在题目就转换成在这个树上填值满足笛卡尔树的形态不变。

因为计数，考虑动态规划，设 $dp_{u,j}$ 表示当前点为 $u$，填写了 $j$ 的方案数，分三类讨论即可。

- 如果没有儿子，$dp_{u,j}=1$。
- 如果只有一个儿子，如果是左儿子，那左儿子只能填 $[1,j-1]$，因为根据键的性质，左儿子键值小于 $u$，如果填了大于 $j-1$ 的数的话，就不满足左端最大值在 $u$ 的限制条件了，而是在左儿子。如果是只有右儿子的话，那右儿子填 $[1,j]$ 均可。
- 如果有两个儿子，根据上文，左儿子可以填 $[1,j-1]$，右儿子可以填 $[1,j]$，加法原理即可。

具体转移方程见代码。

这个转移显然是可以 $O(m)$ 搞出来的，所以总时间就是 $O(\sum n \times m)$。

注意要用 `vector` 来开数组。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
const int mod=1e9+7;
#define int long long 
struct node{
	int l,r;
}dis[N];
struct edge{
	int v,id;
};
struct node1{
	int k,w;
};
int t,n,m,a[N];
vector<long long> dp[N];
vector<edge> g[N];
stack<node1> sta;
void Clear(){
	for(int i=1;i<=n;i++)	g[i].clear(),dp[i].clear(),dis[i].l=dis[i].r=0;
}
void DP(int u){
	dp[u].push_back(0);
	if(g[u].size()==0)	for(int i=1;i<=m;i++)	dp[u].push_back(1);
	else if(g[u].size()==1){
		DP(g[u][0].v);
		int sum=0;
		if(g[u][0].id==1)	for(int i=1;i<=m;i++)	dp[u].push_back(sum),sum+=dp[g[u][0].v][i],sum%=mod;
		else	for(int i=1;i<=m;i++)	sum+=dp[g[u][0].v][i],dp[u].push_back(sum),sum%=mod;
	}
	else{
		DP(g[u][0].v),DP(g[u][1].v);
		int sum1=0,sum2=0;
		for(int i=1;i<=m;i++)	sum2+=dp[g[u][1].v][i],sum2%=mod,dp[u].push_back((sum1%mod*sum2%mod)%mod),sum1+=dp[g[u][0].v][i],sum1%=mod;
	}
}
void Slove(){
	for(int i=1;i<=n;i++){
		int lst=0;
		while(!sta.empty()&&a[i]>sta.top().w)	lst=sta.top().k,sta.pop();
		if(sta.empty())	dis[i].l=lst;
		else{
			int now=sta.top().k;	
			dis[i].l=dis[now].r;dis[now].r=i;
		}
		sta.push({i,a[i]});
	}
	for(int i=1;i<=n;i++){
		if(dis[i].l!=0)	g[i].push_back({dis[i].l,1});
		if(dis[i].r!=0)	g[i].push_back({dis[i].r,0});
//		cout<<i<<" "<<dis[i].l<<" "<<dis[i].r<<endl;
	}
	int lst1=0;
	while(!sta.empty())	lst1=sta.top().k,sta.pop();
	DP(lst1);
//	cout<<lst1<<" ";
	long long ans=0;
	for(int i=1;i<=m;i++)	ans+=dp[lst1][i],ans%=mod;
	cout<<ans<<endl;
	Clear();
//	cout<<dp[2][2]<<endl;
}
signed main(){
	cin>>t;
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)	scanf("%d",&a[i]);
		Slove();
	}
}
/* chong xin an pai zhi 
 dp[u][j] = dp[v1][1-->j-1]*dp[v2][1-->j]
*/
/*
4
4 2
2 2 2 2
*/
```

---

## 作者：RockyYue (赞：0)

本文中记 $g_a(l,r)$ 为 $a_{l\dots r}$ 的“最左段最大值位置”，$g_b(l,r)$ 为 $b$ 中对应的位置，则 $b$ 需要且仅需要满足对于所有 $1\le l<r\le n$，$g_b(l,r)=g_a(l,r)$。

对于一个区间 $[l,r]$ 和给定的 $k\in [l,r]$，$g_b(l,r)=k$ 的充要条件为 $b_{l\dots k-1}<b_k$ 且 $b_{k+1\dots r}\le b_k$。处理 $g_b(l,r)=g_a(l,r)$ 时，令 $k=g_a(l,r)$，以下为了方便描述暂且不考虑 $k=l,r$ 的情况。

需要统计合法 $b$ 的个数，考虑枚举 $b_k$，则这里对 $b_{l\dots k-1}$ 和 $b_{k+1\dots r}$ 中最大值的要求也是动态变化的。而这个两段中最大值的位置刚好是 $g_a(l,k-1)$ 和 $g_b(k+1,r)$，这恰好是两个子段中枚举的 $b_{k'}$ 的值，故考虑记录状态。设 $f_{l,r,x}$ 为对于 $g_a(l,r)=g_b(l,r)=p$，有 $b_p\le x$ 时 $b_{[l,r]}$ 中其余位的取值方案数，则有：$f_{l,r,x}=f_{l,r,x-1}+f_{l-1,p,x-1}\cdot f_{p+1,r,x}$。

于是考虑分治，先处理出 $f_{l,p}$ 和 $f_{p+1,r}$，用这两个数组计算得 $f_{l,r}$。对于 $g_a$ 的计算，可以使用 ST 表预处理，于是总复杂度 $O(n\log n)$。

需要注意的是我们上文的分析都是基于 $k\neq l,r$ 的，需要特判这两种情况。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,M=2e5+5,H=25,P=1e9+7;
vector<vector<int> > f;
int n,m,a[N];
int maxv[N][H],maxp[N][H];
void initST(){
	for(int i=1;i<=n;++i){
		for(int j=0;j<H;++j)maxv[i][j]=-1e12;
	}
	for(int i=1;i<=n;++i)maxv[i][0]=a[i],maxp[i][0]=i;
	for(int j=1;j<H;++j){
		for(int i=1;i+(1<<j)-1<=n;++i){
			maxv[i][j]=max(maxv[i][j-1],maxv[i+(1<<j-1)][j-1]);
			maxp[i][j]=(maxv[i][j]==maxv[i][j-1])?maxp[i][j-1]:maxp[i+(1<<j-1)][j-1];
		}
	}
}
inline int maxl(int l,int r){
	int t=log2(r-l+1);
	return maxv[l][t]>=maxv[r-(1<<t)+1][t]?maxp[l][t]:maxp[r-(1<<t)+1][t];
}
void dp(int l,int r,int p){
	if(l==r){
		for(int i=1;i<=m;++i)f[p][i]=i;
		return ;
	}
	int lp,rp;
	if(p!=l)dp(l,p-1,lp=maxl(l,p-1));
	if(p!=r)dp(p+1,r,rp=maxl(p+1,r));
	if(p==l){
		for(int i=1;i<=m;++i)f[p][i]=(f[p][i-1]+f[rp][i])%P;
		return ;
	}
	if(p==r){
		for(int i=1;i<=m;++i)f[p][i]=(f[p][i-1]+f[lp][i-1])%P;
		return ;
	}
	for(int i=1;i<=m;++i)f[p][i]=(f[p][i-1]+f[lp][i-1]*f[rp][i]%P)%P;
}
signed main() {
	ios :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while (T--) {
		f.clear();
		cin>>n>>m;
		for(int i=0;i<=n+5;++i){
			vector<int> v(m+5);
			f.push_back(v);
		}
		for(int i=1;i<=n;++i)cin>>a[i];
		initST();
		int p;
		dp(1,n,p=maxl(1,n));
		cout<<f[p][m]<<'\n';
	}
	return 0;
}
```



---

## 作者：OIer_ACMer (赞：0)

~~这道题竟然卡了我 $30$ 分钟！！！~~


------------
注意：本题是蒟蒻第一次做笛卡尔树之类的题目，部分思路参考[大佬博客](https://blog.csdn.net/AC__dream/article/details/128512116)。

------------
## 大致思路：
这道题是笛卡尔树的**模板题**，首先我们要知道笛卡尔树的预备知识：
1. 笛卡尔树是**二叉排序树和堆的结合**。


2. 对于一个笛卡尔树，对笛卡尔树**进行中序遍历即可得到原序列**。


3. 笛卡尔树中每个节点的**左子树上的节点的坐标都是小于该节点的**，**右子树上的节点的坐标都是大于该节点的**。而且每个节点的值是**大于或小于其子树上的节点的值**的，这个**取决于是和大根堆结合还是和小根堆结合**。

那么，在这道题中，我们要知道~~出题人没那么好心~~我们需要构造出 $a$ 数组和 $b$ 数组的笛卡尔树**且两者形态相同**才可以符合**让根节点的值大于其左子节点的值，大于等于其右子节点的值**的条件，然后利用树形 DP 向每个节点进行填值求方案数即可。

建树的过程，可以发现：

1. 每个右子树根节点的父亲节点**就是他左边第一个大于他的数的位置**。

2. 每个节点的左子树根节点**就是他左边小于该值的数中的最大值的最小下标**。

3. 这个显然可以用栈来维护，那么建树复杂度就是 $O(n)$，细节可以见代码。

最后就是根据笛卡尔树的结果求方案数了：

首先，我们设 $f[x][y]$ 代表 $x$ 节点取值为 $1$ 到 $y$ 时的方案数和，$l _ i$ 为第 $i$ 个左子树，$r _ i$ 为第 $i$ 个右子树。那么更新过程就有四种情况：

1. 若 $x$ 既有左子树又有右子树，则同时更新，$f[x][y]=f[x][y-1]+f[l[x]][y-1] \times f[r[x]][y]$。

2. 若 $x$ 只有左子树，则 $f[x][y]=f[x][y-1]+f[l[x]][y-1]$。

3. 同理，若 $x$ 只有右子树，则 $f[x][y]=f[x][y-1]+f[r[x]][y-1]$。

4. 若没有儿子节点，则返回 $y$ 节点。

最后，我们要用 $ans$ 数组找出最优解，输出答案。


------------
## 警钟敲烂：
记住！！！全局变量**慎用**！！！就这地方卡了我 $30$ 分钟！！！

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int N = 2e6 + 10, mod = 1e9 + 7;
int l[N], r[N], fa[N];
int stacks[N], top;
int f[N], v[N];
int n, m;
void build(int n)
{
    top = 0;
    for (int i = 1; i <= n; i++)
    {
        r[i] = l[i] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        v[i] = read();
        while (top && v[stacks[top]] < v[i])
        {
            l[i] = stacks[top], top--;
        }
        fa[i] = stacks[top];
        fa[l[i]] = i;
        if (fa[i])
        {
            r[fa[i]] = i;
        }
        stacks[++top] = i;
    }
}
int find(int x, int y)
{
    return (x - 1) * m + y;
}
int dp(int x, int R)
{
    if (R < 1)
    {
        return 0;
    }
    if ((!l[x]) && (!r[x]))
    {
        return R;
    }
    if (f[find(x, R)] != -1)
    {
        return f[find(x, R)];
    }
    long long ans = 0;
    if (l[x] && r[x])
    {
        ans = (dp(x, R - 1) + dp(l[x], R - 1) * dp(r[x], R)) % mod;
    }
    else if (l[x])
    {
        ans = (dp(x, R - 1) + dp(l[x], R - 1)) % mod;
    }
    else if (r[x])
    {
        ans = (dp(x, R - 1) + dp(r[x], R)) % mod;
    }
    return f[find(x, R)] = ans;
}
signed main()
{
    int T;
    cin >> T;
    while (T--)
    {
        n = read();
        m = read();
        for (int i = 1; i <= n * m; i++)
        {
            f[i] = -1;
        }
        build(n);
        int root, maxn = 0;
        for (int i = 1; i <= n; i++)
        {
            if (v[i] > maxn)
            {
                maxn = v[i], root = i;
            }
        }
        cout << dp(root, m) << endl;
    }
    return 0;
}
/*
4
3 3
1 3 2
4 2
2 2 2 2
6 9
6 9 6 9 6 9
9 100
10 40 20 20 100 60 80 60 60
*/
```

[AC 记录](https://www.luogu.com.cn/record/121098079)

---

## 作者：Imiya (赞：0)

我们先求出全局最大最左，就知道了所有左端点小于等于它且右端点大于等于它的子区间的最大最左，然后序列就可以被分成两部分，分别再进行这个操作，一直递归下去就可以求出所有子区间的最大最左。

现在 $b$ 的所有子区间的最大最左与 $a$ 的一样，就一定有 $b$ 每一次拆分序列的位置与 $a$ 一致。

容易发现这个拆分过程相当于在遍历 $a$ 的[笛卡尔树](https://oi-wiki.org/ds/cartesian-tree/)，并且是一棵大根笛卡尔树（若权值相等将位置靠左的视为更大）。这棵笛卡尔树的形状与 $a$ 的拆分方案唯一对应，所以它的形状一定与 $b$ 的笛卡尔树的形状相同。

那么问题变成求出 $a$ 的笛卡尔树，然后问有多少种在树上填数的方案使得重新填数的树依然是一棵符合我们要求的笛卡尔树。

看眼数据范围 $n\cdot m\le 10^6$，直接 $O(nm)$ 的树形 dp 即可。$f(i,j)$ 表示限制 $i$ 号节点上只能填小于等于 $j$ 的数时，整棵子树的填数方案。

显然有 $f(i,j)=f(i,j-1)+f(ls,j-1)\cdot f(rs,j)$，若 $i$ 为空则返回 $1$，若 $j<1$ 则返回 $0$。

##### 代码
```cpp
#include<iostream>
#include<map>
using namespace std;
#define int long long
const int N=200100,P=1000000007;
int n,m,a[N];
int stk[N],top;
int ls[N],rs[N];
map<pair<int,int>,int>f;
void init(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)ls[i]=rs[i]=stk[i]=0;
    top=0;
    f.clear();
    for(int i=1;i<=n;i++){
        while(top&&a[stk[top]]<a[i])ls[i]=stk[top--];
        if(top)rs[stk[top]]=i;
        stk[++top]=i;
    }
}
int dp(int nd,int k){
    if(f.count(make_pair(nd,k)))return f[make_pair(nd,k)];
    if(!nd)return 1;
    if(k<1)return 0;
    return f[make_pair(nd,k)]=(dp(nd,k-1)+dp(ls[nd],k-1)*dp(rs[nd],k)%P)%P;
}
signed main(){
    // freopen("read.in","r",stdin);
    int t;cin>>t;
    while(t--){
        init();
        cout<<dp(stk[1],m)<<endl;
    }
    return 0;
}
```

---

## 作者：cszhpdx (赞：0)

### 性质：

考虑这一句话。

对任意整数 $l,r(1\leq l\leq r\leq n)$，总有 $a,b$ 在子段 $[l;r]$ 的“最左端最大值位置”相同。

容易想到当 $a_i=b_i$ 的时候一定成立，或者说当 $a_i$ 互不相同时 $b$ 离散化后和 $a$ 一样时一定成立（比如 $(1,2,3,4)$ 和 $(2,3,4,5)$）。

但是如果 $a$ 中有重复出现的值呢？题目要求“最左端最大值位置”相同。其实我们可以把每个值看作一个 $(a_i,i)$ 的二元组，$a_i$ 为第一关键字，$i$ 为第二关键字。我们发现 $b$ 满足条件当且仅当 $a,b$ 按照这个二元组的比较大小方式离散化后相同。

有些抽象，比如：$(1,3,2,2)$，其实当这两个 $2$ 同时存在于一个区间的时候，右边那个二永远也不会取到，我们就当作前面的 $2$ 比后面的 $2$ 大就好了。

这样的话我们就可以对 $a$ 离散化，变成一个 $n$ 级排列，比如 $(1,3,2,2)$ 变成 $(1,4,3,2)$。

### 构造
一个显然的思路是：
找出区间 $[L,R]$ 最大值 $a_p$，显然 $[L,p)$ 每个元素必须小于 $b_p$，$(p,R]$ 每个元素必须小于等于 $b_p$，我们令 $b_p$ 向 其他的位置连边，这样得到一个有向无环图，然后各种动态规划。

显然这会炸~~所以我们用数据结构优化建图。~~

其实很多边是不必要的，我们直接把 $b_p$ 分别向 $[L,p),(p,R]$ 最大值连边就够了，然后发现这玩意其实就是一颗笛卡尔树。

所以最后的解法就是，建笛卡尔树然后树上 $dp$ 就完了。

令 $f_{i,j}$ 表示节点 $i$ 值为 $j$ 时以 $i$ 为根的子树有多少种方案。

（我为什么写了个 ST 表来构造笛卡尔树？）

```cpp
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define cmin(a, b) (a)=min((a), (b))
#define cmax(a, b) (a)=max((a), (b))
#define mem(a, x) memset(a, x, sizeof(a))
#define rps(i, b, e) for(int i=(b);i<=(e);i++)
#define prs(i, e, b) for(int i=(e);i>=(b);i--)
#define rpg(i, g, x) for(int i=g.head[x];i;i=g.e[i].nxt)
#define opf(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)
using namespace std;
template<class T>
inline void read(T &x) {
	x=0;
	bool f=false;
	char c=getchar();
	while(!isdigit(c))f|=(c=='-'), c=getchar();
	while(isdigit(c))x=x*10+(c-'0'), c=getchar();
	if(f)x=-x;
}
typedef long long LL;
const int NR=2e5+10, CF=20;
const LL MOD=1e9+7;
LL T, n, m, a[NR], fmx[NR][CF+5], lg[NR];
vector<LL>f[NR], ss[NR];
LL lt[NR], rt[NR];
inline LL gtmx(LL l, LL r) {
    LL tp=lg[r-l+1];
    LL x=fmx[l][tp], y=fmx[r-(1<<tp)+1][tp];
    if(a[x]>=a[y])return x;
    return y;
}
LL build(LL l, LL r) {
    if(l>r)return 0;
    LL p=gtmx(l, r);
    lt[p]=build(l, p-1);
    rt[p]=build(p+1, r);
    return p;
}
void dp(LL x) {
    if(lt[x]==0 && rt[x]==0) {
        rps(i, 1, m)f[x][i]=1, ss[x][i]=i;
        return;
    }
    if(lt[x]>0)dp(lt[x]);
    if(rt[x]>0)dp(rt[x]);
    if(lt[x]>0 && rt[x]>0)rps(i, 1, m)f[x][i]=ss[lt[x]][i-1]*ss[rt[x]][i]%MOD;
    else if(lt[x]>0)rps(i, 1, m)f[x][i]=ss[lt[x]][i-1];
    else rps(i, 1, m)f[x][i]=ss[rt[x]][i];
    rps(i, 1, m)ss[x][i]=(ss[x][i-1]+f[x][i])%MOD;
}
void work() {
    read(n), read(m);
    rps(i, 1, n)read(a[i]), fmx[i][0]=i;
    rps(j, 1, CF)rps(i, 1, n-(1<<j)+1) {
        fmx[i][j]=fmx[i][j-1];
        if(a[fmx[i+(1<<j-1)][j-1]]>a[fmx[i][j]])
            fmx[i][j]=fmx[i+(1<<j-1)][j-1];
    }
    rps(i, 1, n)lt[i]=rt[i]=0;
    LL rt=build(1, n);
    // rps(i, 1, n)printf("%lld %lld ;;\n", lt[i], ::rt[i]);
    rps(i, 1, n)f[i].assign(m+1, 0), ss[i].assign(m+1, 0);
    dp(rt);
    printf("%lld\n", ss[rt][m]);
}
int main() {
    lg[1]=0;
    rps(i, 2, NR-1)lg[i]=lg[i/2]+1;
    read(T);
    while(T--)work();
	return 0;
}
```

---

## 作者：Ender_hz (赞：0)

# 前言

住校生周六回家难得打一场 CF，没交代码，看到 LG Aca 群里说 E 题水就去看了看，自己手推了一会儿，发现分治就能解决…（蒟蒻刚学 OI，随手糊的）

题意不在此赘述。

# 思路

直觉告诉我们，对于序列 $a$，符合题目要求的方案数应该只与元素间的相对位置和大小关系有关。

对于序列 $a_{l..r}$，构造一棵对应的二叉树，满足：

+ 每个节点对应序列中的一个元素（若序列为空，则树为空）；
+ 根节点为题目所述的「最左端最大值」的位置（记为 $rt$）；
+ 左子树为 $a_{l..rt-1}$ 对应的树，右子树为 $a_{rt+1..r}$ 对应的树（记左右子树对应的根节点为 $ls, rs$）。

构造数组 $f$，$f_{i,j}$ 维护 $b_i=j$ 时，以 $i$ 为根节点的子树对应的序列的方案数，注意到 $b_{ls}\ngeq b_{rt}, b_{rs}\ngtr b_{rt}$，则易得转移方程为 $f_{i,j} = \left(\sum\limits_{k=1}^{j-1}f_{ls,k}\right)\left(\sum\limits_{k=1}^{j}f_{rs, k}\right)$。

显然可以用前缀和优化（$g_{i,j}=\sum\limits_{k=1}^{j}f_{i,k}$），则状态转移方程变为 $f_{i,j} = g_{ls,j-1}\times g_{rs,j}$。

答案即为 $g_{rt, m}$。

细节：注意多组数据之间的清零问题，本人保证了每个数据都被更新，故没有使用 `memset`。

# 代码

```cpp
#include<iostream>
#define sfor(i, h, t) for(int i = (h); i <= (t); ++i)
#define il inline
#define f(i, j) f[i * M + i + j]
#define g(i, j) g[i * M + i + j]
using namespace std;
typedef long long ll;
const int MAXN = 200008;
const int MAXNM = 2000008;
const ll P = 1000000007;
int T, N, M;
int num[MAXN];
ll f[MAXNM], g[MAXNM];
struct SEGT {
    int val[MAXN << 2];
    il int pushup(int x, int y) {
        return num[x] >= num[y] ? x : y;
    }
    il void build(int l, int r, int p) {
        if(l == r) {
            val[p] = l;
            return;
        }
        int mid = (l & r) + ((l ^ r) >> 1), ls = p << 1, rs = p << 1 | 1;
        build(l, mid, ls);
        build(mid + 1, r, rs);
        val[p] = pushup(val[ls], val[rs]);
    }
    il int query(int L, int R, int l, int r, int p) {
        if(L <= l && r <= R)
            return val[p];
        int res = 0, mid = (l & r) + ((l ^ r) >> 1), ls = p << 1, rs = p << 1 | 1;
        if(L <= mid)
            res = pushup(res, query(L, R, l, mid, ls));
        if(mid < R)
            res = pushup(res, query(L, R, mid + 1, r, rs));
        return res;
    }
}segT;
il int solve(int l, int r) {
    if(l > r)
        return 0;
    if(l == r) {
        sfor(i, 0, M) {
            f(l, i) = 1;
            g(l, i) = i;
        }
        return l;
    }
    int rt = segT.query(l, r, 1, N, 1);
    int ls = solve(l, rt - 1), rs = solve(rt + 1, r);
    g(rt, 0) = 0;
    sfor(i, 1, M) {
        f(rt, i) = g(ls, i - 1) * g(rs, i) % P;
        g(rt, i) = (g(rt, i - 1) + f(rt, i)) % P;
    }
    return rt;
}
signed main(void) {
    ios::sync_with_stdio(false);
    cin >> T;
    while(T--) {
        cin >> N >> M;
        sfor(i, 1, N)
            cin >> num[i];
        segT.build(1, N, 1);
        sfor(i, 0, M)
            g[i] = 1;
        int rt = solve(1, N);
        cout << g(rt, M) << '\n';
    }
}
```

---

## 作者：Polaris_Australis_ (赞：0)

很容易看出是 dp 题，首先考虑构造一棵笛卡尔树：左儿子为 $a$ 序列左侧第一个权值比它小的位置，右儿子为右侧第一个权值小于等于它的位置。之后在笛卡尔树上 dp。设 $dp_{i,j}$ 表示 $i$ 号节点子树所表示的连续段全部处理完，$b_i$ 的权值为 $j$ 的方案数，转移很显然：

$$
dp_{i,j}=(\sum\limits_{k=1}^{j-1}dp_{ls_{i},j})(\sum\limits_{k=1}^{j}dp_{rs_{i},{j}})
$$

这道题就解决了。

代码：

```cpp
// Problem: E. Yet Another Array Counting Problem
// Contest: Codeforces - Codeforces Round #833 (Div. 2)
// URL: https://codeforces.com/contest/1748/problem/E
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#define Wilson_Inversion_AUTHOR            \
|****************************************| \
|                                        | \
|     $$\   $$\   $$\         $$$$\      | \
|     $$ |  $$ |  $$ |        \$$  |     | \
|     $$ |  $$ |  $$ |         $$ /      | \
|     $$ |  $$ |  $$ |         $$ |      | \
|     \$$\ $$$$\ $$  |         $$ |      | \
|      $$ |$$$$ |$$ /          $$ |      | \
|      \$$$$ \$$$$  |          $$ |      | \
|       \$$  /\$$  /          $$$$\      | \
|        \__/  \__/           \____|     | \
|                                        | \
|****************************************|
#include <bits/stdc++.h>
#define gdb
#ifdef gdb
#define dbg cerr << "Wilson_Inversion\n"
#define debug(x) cerr << "[" << #x << "=" << x << "]\n"
#define DEBUG(x, __n) {                                                         \
	cerr << "[" << #x << ":\n";                                                 \
	for (int __i = 0; __i < __n; ++ __i) cerr << __i << ":" << x[__i] << ",\n"; \
	cerr << __n << ":" << x[__n] << "]\n"                                       \
}
#else
#define dbg 0
#define debug(x) 0
#define DEBUG(x, __n) 0
#endif
#define pb push_back
#define mk make_pair
#define ff first
#define ss second
#define int long long
#define db double
#define miny(x, y) x = min(x, y)
#define maxy(x, y) x = max(x, y)
#define lowbit(x) ((x) & (-(x)))
#define fu(i, l, r) for (int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (int i = (r); i >= (l); --i)
#define mem(x, y) memset(x, y, sizeof (x))
#define file(x)                   \
	freopen(x ".in", "r", stdin); \
	freopen(x ".out", "w", stdout);
#define mod 1000000007
#ifdef int
#define inf 0x3f3f3f3f3f3f3f3f
#else
#define inf 0x3f3f3f3f
#endif
#define inv(x) qp(x, mod - 2)
using namespace std;
namespace Std {
	void read(int &x) {
		x = 0;
		int y = 1;
		char c = getchar();
		while (c < '0' || c > '9') {
			if (c == '-') y = -1;
			c = getchar();
		}
		while (c >= '0' && c<= '9') {
			x = (x << 1) + (x << 3) + (c & 15);
			c = getchar();
		}
		x *= y;
	}
	void write(int x) {
		char s[50];
		int tot = 0;
		while (x) {
			s[++tot] = (x % 10);
			x /= 10;
		}
		while (tot) putchar(s[tot--]);
	}
	int qp(int x, int y) {
		int cmp = 1;
		while (y) {
			if (y & 1) (cmp *= x) %= mod;
			(x *= x) %= mod;
			y >>= 1;
		}
		return cmp;
	}
	int T, n, m, f[1000010], a[1000010];
	vector <int> vec[1000010];
	int find(int x) {
		return ((f[x] == x) ? x : (f[x] = find(f[x])));
	}
	void main() {
		read(T);
		while (T --) {
			read(n);
			read(m);
			for (int i = 0; i <= m; ++ i) vec[i].clear();
			for (int i = 1; i <= n; ++ i) {
				read(a[i]);
				f[i] = i;
			}
			for (int i = n; i; -- i) vec[a[i]].pb(i);
			int dp[n + 3][m + 3], sum[n + 3][m + 3];
			for (int i = 1; i <= n; ++ i) {
				for (int j = 0; j <= m; ++ j) dp[i][j] = sum[i][j] = 0;
			}
			for (int i = 1; i <= m; ++ i) {
				for (auto j : vec[i]) {
					if (a[j + 1] <= a[j] && a[j - 1] < a[j] && j != n && j != 1) {
						for (int k = 1; k <= m; ++ k) {
							dp[j][k] = (sum[find(j - 1)][k - 1]) * sum[find(j + 1)][k] % mod;
							sum[j][k] = (sum[j][k - 1] + dp[j][k]) % mod;
						}
						f[find(j - 1)] = f[find(j + 1)] = j;
					} else if (a[j - 1] < a[j] && j != 1) {
						for (int k = 1; k <= m; ++ k) {
							dp[j][k] = sum[find(j - 1)][k - 1];
							sum[j][k] = (sum[j][k - 1] + dp[j][k]) % mod;
						}
						f[find(j - 1)] = j;
					} else if(a[j + 1] <= a[j] && j != n) {
						for (int k = 1; k <= m; ++ k) {
							dp[j][k] = sum[find(j + 1)][k];
							sum[j][k] = (sum[j][k - 1] + dp[j][k]) % mod;
						}
						f[find(j + 1)] = j;
					} else {
						for (int k = 1; k <= m; ++ k) {
							dp[j][k] = 1;
							sum[j][k] = (sum[j][k - 1] + dp[j][k]) % mod;
						}
					}
				}
			}
			int ans = 0;
			for (int i = 1; i <= m; ++ i) (ans += dp[find(1)][i]) %= mod;
			printf("%lld\n", ans);
		}
	}
}  // namespace Std
#undef int
int main() {
	Std :: main();
	return 0;
}
```


---

## 作者：MortisM (赞：0)

# Preface

一道好题，序列转树上问题属实优美，但是做多了就套路了？

# Statement

给定一个长度为 $n$ 的数组 $[a_1,a_2,...,a_n]$ 满足 $a_i \leq m$，要求有多少个长度为 $n$ 的数组 $[b_1,b_2,...,b_n]$ 满足：
+ $1\leq b_i\leq m$
+ 对于任意区间 $[l,r]$，都有 $[a_l,a_{l+1},...,a_r]$ 的最左边的最大值的位置等于 $[b_l,b_{l+1},...,b_r]$ 的最左边的最大值的位置

输出答案模 $10^9+7$。

数据范围：$n,m\leq 2\cdot 10^5,n\cdot m\leq 10^6$。

# Solution

首先先从 $[1,n]$ 入手，先可以求出这个区间最左边的最大值的位置，设为 $m$，设 $[l,m-1]$ 的最左边的最大值的位置为 $x$，$[m+1,r]$ 的最左边的最大值位置为 $y$，容易发现 $b_u>b_x,b_u\geq b_y$。

这启发我们去转二叉树树形 dp，我们可以以 $u$ 为根节点 $x,y$ 为左右儿子递归下去建树。这个过程本来是 $O(n^2)$ 的，但是可以用 ST 表 + 二分达到 $O(n\log n)$ 的时间复杂度。

设 $f(u,i)$ 表示 dp 到点 $u$，$b_u=i$ 的方案数。设 $u$ 的左右儿子分别为 $x,y$，则：
+ 若 $x,y$ 都不存在，则 $f(u,i)=1$
+ 若只有 $x$ 存在且 $i=1$，则 $f(u,i)=0$
+ 否则若只有 $x$ 存在，则 $f(u,i)=\sum_{j=1}^{i-1}f(x,j)$
+ 若只有 $y$ 存在，则 $f(u,i)=\sum_{j=1}^if(y,j)$
+ 若 $x,y$ 都存在，则 $f(u,i)=\sum_{j=1}^{i-1}f(x,j)\cdot\sum_{j=1}^if(y,j)$

用前缀和优化即可，时间复杂度 $O(n\log n+nm)$。

# Summary

奇技淫巧，我无话可说……

# Code

```cpp
//AC!
//After_contest
#include<bits/stdc++.h>
//#define int long long
#define repe(i,l,r) for(int (i)=l;(i)<=r;(i)++)
#define rep(i,n) for(int (i)=1;(i)<=n;(i)++)
#define FOR(i,r,l) for(int (i)=r;(i)>=l;(i)--)
#define INF 0x3f3f3f
#define pii pair<int,int>
#define ll long long
#define mpr make_pair
#define pb push_back
#define F first
#define S second
#define sz(v) (int)((v).size())
#define ALL(v) (v).begin(),(v).end()
#define rALL(v) (v).rbegin(),(v).rend()
#define srt(v) sort(ALL(v))
#define rsrt(v) sort(rALL(v))
#define rev(v) reverse(ALL(v))
#define lb(v,x) (int)(lower_bound(ALL(v),x)-v.begin())
#define ub(v,x) (int)(upper_bound(ALL(v),x)-v.begin())
#define uni(v) v.resize(unique(ALL(v))-v.begin())
using namespace std;
int read(){int sum=0,f=1;char c;c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){sum=(sum<<1)+(sum<<3)+(c-'0');c=getchar();}return sum*f;}
void out(int x){if(x<0){x=-x;putchar('-');}if(x>=10)out(x/10);putchar(x%10+'0');}
void die(string s){puts(s.c_str());exit(0);}
int fast(int a,int b,int P){int res=1;if(P<=0){while(b){if(b&1)res=res*a;a=a*a;b>>=1;}}else{while(b){if(b&1)res=res*a%P;a=a*a%P;b>>=1;}}return res;}
const int N=2e5+10,P=1e9+7;
int n,m,a[N],st[N][20];
vector<int> vec[N];
vector<vector<int>> dp,sum;
int getmx(int l,int r){
	int k=log2(r-l+1);
	return max(st[l][k],st[r-(1<<k)+1][k]);
}
int calc(int l,int r){
	if(l>r)return -1;
	int val=getmx(l,r);
	return *lower_bound(vec[val].begin(),vec[val].end(),l);
}
void dfs(int u,int l,int r){
	int lson=calc(l,u-1),rson=calc(u+1,r);
	if(lson!=-1)dfs(lson,l,u-1);
	if(rson!=-1)dfs(rson,u+1,r);
	for(int x=1;x<=m;x++){
		if(lson==-1&&rson==-1)dp[u][x]=1;
		else if(rson==-1&&x==1)dp[u][x]=0;
		else if(rson==-1)dp[u][x]=sum[lson][x-1];
		else if(lson==-1)dp[u][x]=sum[rson][x];
		else dp[u][x]=1LL*sum[lson][x-1]*sum[rson][x]%P;
		sum[u][x]=(sum[u][x-1]+dp[u][x])%P;
	}
}
void solve(){
	n=read(),m=read();
	for(int i=1;i<=m;i++)vec[i].clear();
	for(int i=1;i<=n;i++){
		a[i]=read();
		vec[a[i]].pb(i);
		st[i][0]=a[i];
	}
	for(int j=1;j<20;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
	vector<int> tmp(m+1,0);
	dp.clear();
	sum.clear();
	for(int i=0;i<=n;i++){
		dp.pb(tmp);
		sum.pb(tmp);
	}
	int rt=calc(1,n);
	dfs(rt,1,n);
	out(sum[rt][m]),putchar('\n');
}
int main(){
	int t=read();
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

不错的一个 dp 套路。

## 思路

最简单的思想是考虑 $dp_{i,j,k}$ 表示 $i\sim j$ 区间内最大值为 $k$ 的方案数。转移时合并两个区间需要保证这两个的最大值关系和在原数列中一模一样。

这样是 $O(n^2m)$ 的显然不可过。

考虑按原数列从小向大填。

我们发现每次增加一个数只会多出一组 $dp_{x,k}$，于是状态数降低到了 $O(nm)$ 级别。

转移的话，每次考虑合并这个数两边目前比他小的数，可以用并查集维护一下。具体也和先文一样需要保证最大值在原数列关系一样。

补充说明：合并时（即状态转移时），目前看到位置的左边要求严格比这个位置的值小。右边则小于等于即可。原因是每次求 $\max$ 位置时算的是最左边。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int f[1000005];
int find(int i){
	return (f[i]==i?f[i]:f[i]=find(f[i]));
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		int a[n+1];
		vector<int> vc[m+1];
		for(int i=1;i<=n;i++){
			cin>>a[i];
			vc[a[i]].push_back(i);
		}
		for(int i=1;i<=n;i++) f[i]=i;
		int dp[n+1][m+1],pre[n+1][m+1];
		for(int i=1;i<=n;i++) for(int j=0;j<=m;j++) dp[i][j]=0,pre[i][j]=0;
		for(int i=1;i<=m;i++){
			reverse(vc[i].begin(),vc[i].end());
			for(auto v:vc[i]){
				if(a[v+1]<=a[v]&&a[v-1]<a[v]&&v+1<=n&&v-1>0){
					for(int j=1;j<=m;j++){
						dp[v][j]=(pre[find(v-1)][j-1]*pre[find(v+1)][j])%mod;
						pre[v][j]=(pre[v][j-1]+dp[v][j])%mod;
					}
					f[find(v-1)]=v;
					f[find(v+1)]=v;
				}
				else if(a[v+1]<=a[v]&&v+1<=n){
					for(int j=1;j<=m;j++){
						dp[v][j]=(pre[find(v+1)][j])%mod;
						pre[v][j]=(pre[v][j-1]+dp[v][j])%mod;
					}
					f[find(v+1)]=v;
				}
				else if(a[v-1]<a[v]&&v-1>0){
					for(int j=1;j<=m;j++){
						dp[v][j]=(pre[find(v-1)][j-1])%mod;
						pre[v][j]=(pre[v][j-1]+dp[v][j])%mod;
					}
					f[find(v-1)]=v;
				}
				else{
					for(int j=1;j<=m;j++){
						dp[v][j]=1;
						pre[v][j]=(pre[v][j-1]+dp[v][j])%mod;
					}
				}
			}
		}
		int ans=0;
		for(int i=1;i<=m;i++){
			ans=(ans+dp[find(1)][i])%mod;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

