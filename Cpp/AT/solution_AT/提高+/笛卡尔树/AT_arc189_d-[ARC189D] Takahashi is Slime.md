# [ARC189D] Takahashi is Slime

## 题目描述

有 $N$ 个史莱姆排成一列，从左到右依次编号为 $1, 2, \ldots, N$。第 $i$ 个史莱姆的大小为 $A_i$。  
对于每一个位置 $K = 1, 2, \ldots, N$，解决下面的问题：

> 初始时，第 $K$ 个史莱姆是高桥君。高桥君可以执行任意多次（可以是 $0$ 次）的操作。请计算高桥君在操作后能达到的最大大小。
>
> - 高桥君可以吸收一个相邻且大小小于他的史莱姆。吸收后，该史莱姆消失，高桥君的大小增加该史莱姆的大小。
>
> 在这个过程中，被吸收的史莱姆消失后空出的位置会立即由两侧的史莱姆填补，这使得两端的史莱姆重新相邻（请参考样例 1）。

## 说明/提示

- $2 \leq N \leq 5 \times 10^5$
- $1 \leq A_i \leq 10^9$
- 所有输入都是整数

### 样例解释

以 $K = 4$ 为例。我们用方括号 `[]` 标识高桥君，称其为**列状态**。初始状态下的列为 $(4, 13, 2, [3], 2, 6)$。以下是高桥君的操作步骤：
1. 高桥君吸收右邻的史莱姆，大小变为 $3 + 2 = 5$，列状态变为 $(4, 13, 2, [5], 6)$。
2. 高桥君吸收左邻的史莱姆，大小变为 $5 + 2 = 7$，列状态变为 $(4, 13, [7], 6)$。
3. 高桥君吸收右邻的史莱姆，大小变为 $7 + 6 = 13$，列状态变为 $(4, 13, [13])$。

最终，高桥君再也无法吸收任何比他小的邻居，所以他的最大可能大小是 $13$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
6
4 13 2 3 2 6```

### 输出

```
4 30 2 13 2 13```

## 样例 #2

### 输入

```
12
22 25 61 10 21 37 2 14 5 8 6 24```

### 输出

```
22 47 235 10 31 235 2 235 5 235 6 235```

# 题解

## 作者：what_can_I_do (赞：12)

[传送门](https://www.luogu.com.cn/problem/AT_arc189_d)

[几乎一样的题的题解](https://www.luogu.com.cn/article/bnyueicp)

本篇题解基于上面的这篇题解进行讲解。

这道题相比于 CF1998E1 的区别在于它不能取等。

首先先考虑如何求出这道题所要的答案。对于一个区间，如果这个区间的所有值的和大于分治到这一个区间的上一个区间，那么这个区间的最大值就可以把整个区间的所有值加给自己，然后它就可以成为上一个区间的最大值，那么就可以得到和上一个区间的最大值同样的答案，于是我们只需要再递归的时候记录一下目前的这个区间的最大值是否可以得到和上一个区间的最大值同样的答案就行了。

然后再讲一些和 CF1998E1 相比要多判断的地方。如果目前的其中一个最大值它的左边和右边也都是最大值，那么它就不能再操作，它的答案就是它自己。注意区间最靠左和最靠右的最大值要判断它是否也是整个区间的左端点或右端点。

# CODE：
```cpp
#include<bits/stdc++.h>
#define int long long
#define lc k<<1
#define rc k<<1|1
using namespace std;
int n;
struct aaa
{
	int val,v,id;
}a[500010];
vector<int> wz[500010];
int tr[2000010][2];
int ans[500010];
inline void build(int l,int r,int k)
{
	if(l==r)
	{
		tr[k][0]=a[l].v,tr[k][1]=a[l].val;
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,lc),build(mid+1,r,rc);
	tr[k][0]=max(tr[lc][0],tr[rc][0]),tr[k][1]=tr[lc][1]+tr[rc][1];
}
inline int query(int l,int r,int ql,int qr,int k)
{
	if(ql<=l&&r<=qr) return tr[k][0];
	int mid=(l+r)>>1,sum=0;
	if(ql<=mid) sum=query(l,mid,ql,qr,lc);
	if(mid<qr) sum=max(sum,query(mid+1,r,ql,qr,rc));
	return sum;
}
inline int querysum(int l,int r,int ql,int qr,int k)
{
	if(ql<=l&&r<=qr) return tr[k][1];
	int mid=(l+r)>>1;int sum=0;
	if(ql<=mid) sum+=querysum(l,mid,ql,qr,lc);
	if(mid<qr) sum+=querysum(mid+1,r,ql,qr,rc);
	return sum;
}
inline void solve(int l,int r,int mz)
{
	//cout<<l<<" "<<r<<" "<<mz<<endl;
	//cout<<querysum(1,n,l,r,1)<<endl;
	if(l>=r) return;
	int maxx=query(1,n,l,r,1);
	int rl=lower_bound(wz[maxx].begin(),wz[maxx].end(),l)-wz[maxx].begin(),rr=upper_bound(wz[maxx].begin(),wz[maxx].end(),r)-wz[maxx].begin()-1;
	//cout<<l<<" "<<r<<" "<<rl<<" "<<rr<<endl;
	int nw=l;
	for(register int i=rl;i<=rr;i++)
	{
		if(i==rl)
		{
			if(i<rr&&nw==wz[maxx][i])
				if(wz[maxx][i]+1==wz[maxx][i+1])
					ans[wz[maxx][i]]=-1;
		}
		else if(nw==wz[maxx][i])
		{
			if(i==rr)
			{
				if(wz[maxx][i]==r) ans[wz[maxx][i]]=-1;
			}
			else if(wz[maxx][i]+1==wz[maxx][i+1]) ans[wz[maxx][i]]=-1;
		}
		if(ans[wz[maxx][i]]==-1) ans[wz[maxx][i]]=0;
		else ans[wz[maxx][i]]=max(ans[mz],querysum(1,n,l,r,1));
		if(nw<=wz[maxx][i]-1)
		{
			if(querysum(1,n,nw,wz[maxx][i]-1,1)>a[wz[maxx][i]].val)
				solve(nw,wz[maxx][i]-1,wz[maxx][i]);
			else
				solve(nw,wz[maxx][i]-1,0);
		}
		nw=wz[maxx][i]+1;
	}
	if(nw<=r)
	{
		if(querysum(1,n,nw,r,1)>a[wz[maxx][rr]].val)
			solve(nw,r,wz[maxx][rr]);
		else
			solve(nw,r,0);
	}
}
signed main()
{
	scanf("%lld",&n);
	for(register int i=1;i<=n;i++) scanf("%lld",&a[i].val),a[i].id=i;
	if(n==1)
	{
		printf("%lld\n",a[1].val);
		return 0;
	}
	sort(a+1,a+n+1,[](aaa u,aaa v){return u.val<v.val;});
	int tot=0;
	a[0].val=0;
	for(register int i=1;i<=n;i++)
	{
		if(a[i].val!=a[i-1].val) tot++;
		a[i].v=tot;
	}
	sort(a+1,a+n+1,[](aaa u,aaa v){return u.id<v.id;});
	for(register int i=1;i<=n;i++) wz[a[i].v].push_back(i);
	build(1,n,1);
	solve(1,n,1);
	for(register int i=1;i<=n;i++)
		if(!ans[i]) printf("%lld ",a[i].val);
		else printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：Iniaugoty (赞：5)

### [ARC189D Takahashi is Slime](/problem/AT_arc189_d)

线性。好像题解已经有类似做法，但是我的更简洁（？）。

直接先建大根笛卡尔树（并且当一个区间出现多个最大值时，取最靠左的那个为根节点）。记 $i$ 的父亲、左孩子、右孩子分别为 $f _ i, l _ i, r _ i$，$i$ 子树内的 $a$ 之和为 $s _ i$。

从建树的过程考虑，发现一定有 $a _ {l _ i} < a _ i$，但是 $a _ {r _ i} \le a _ i$。对 $a _ {r _ i}$ 的取值分讨。

第一种情况，$a _ {r _ i} < a _ i$ 或者 $r _ i$ 不存在。$i$ 一定可以先把子树全吞掉。如果 $s _ i > a _ {f _ i}$ 的话，还可以再把 $f _ i$ 子树全吞掉，如果 $s _ {f _ i} > a _ {f _ {f _ i}}$，还能把 $f _ {f _ i}$ 子树全吞掉……以此类推直到某个 $i$ 的祖先 $u$，使得 $s _ u \le a _ {f _ u}$，那么 $i$ 的答案为 $s _ u$。这种答案可以用 dfs 线性处理出来。

第二种情况，$a _ {r _ i} = a _ i$。此时不能够直接吞 $r _ i$ 子树。再分讨：

- 如果 $l _ i$ 存在，或者 $l _ {r _ i}$ 存在，这意味着，$i$ 旁边还有一个严格小于 $a _ i$ 的数。先把他们吞掉，$i$ 就可以吞 $r _ i$ 子树了。于是本质上和第一种情况一样。

- 如果都不存在，容易发现此时 $a _ {i - 1} \ge a _ i$ 且 $a _ {i + 1} = a _ i$，显然什么都吞不了，答案为 $a _ i$。

[代码](https://atcoder.jp/contests/arc189/submissions/60626111)炒鸡好写。

---

## 作者：隔壁泞2的如心 (赞：4)

最暴力的做法当然就是让 Takahashi 一直尝试吃掉左边和右边的史莱姆直到没法再吃为止。

但当 Takahashi 已经很大，其他史莱姆比较小的时候这么算就很亏了，所以我们让 Takahashi 尝试吃某一边的史莱姆时，改为一口气吃掉 **一个最长的体积和不大于自己的区间** 内的所有史莱姆。这个区间可以用二分找到。

你会发现，如果 Takahashi 按照这种操作连续吃了 $3$ 次史莱姆，它的体积一定不小于一开始的两倍。所以这个做法是两个 $\log$ 的，在 5s 的时限下足以通过此题。~~所以我就是被这东西硬控了 90min？？~~

---

## 作者：Petit_Souris (赞：4)

应该是最简洁易懂的做法了。

Observation 1：每个点的最终状态是一段区间。设为 $[L_x,R_x]$。

Observation 2：对于两个点 $x,y$，如果 $y\in [L_x,R_x]$，则 $[L_y,R_y]\subseteq [L_x,R_x]$，取等条件为 $x\in [L_y,R_y]$。

那么我们可以考虑记忆化搜索。具体而言，初始时将所有 $[L_x,R_x]$ 设为 $[x,x]$。每次搜索一个点，尽可能往两侧扩展。比如可以扩展到 $L_x-1$，那么就继续搜索 $L_x-1$，并把 $[L_{L_x-1},R_{L_x-1}]$ 并入 $[L_x,R_x]$（由 Observation 2 容易证明正确性）。如果一个点已经搜过，不需要再次搜索，因此复杂度显然为 $\mathcal O(n)$。

总共只需要写一个前缀和，写一个 dfs，不用任何数据结构，且复杂度是高贵的线性。


```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=5e5+9;
ll n,C[N],L[N],R[N],sum[N],pre[N];
bool mem[N];
vector<ll>e[N];
void Merge(ll x,ll y){
    L[x]=min(L[x],L[y]),R[x]=max(R[x],R[y]),sum[x]=pre[R[x]]-pre[L[x]-1];
}
void solve(ll x){
    if(mem[x])return ;
    mem[x]=1,L[x]=R[x]=x,sum[x]=C[x];
    while(1){
        bool exd=0;
        if(L[x]>1&&C[L[x]-1]<sum[x])solve(L[x]-1),Merge(x,L[x]-1),exd=1;
        if(R[x]<n&&C[R[x]+1]<sum[x])solve(R[x]+1),Merge(x,R[x]+1),exd=1;
        if(!exd)break;
    }
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read();
    rep(i,1,n)C[i]=read(),pre[i]=pre[i-1]+C[i];
    rep(i,1,n)solve(i);
    rep(i,1,n)write(sum[i]),putchar(' ');
    putchar('\n');
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：是青白呀 (赞：4)

线性做法。

注意到当你处于一个位置 $x$ 时，其相邻的小于 $a_x$ 的连续段都是可以直接吃掉的，不必逐个考虑。于是我们对 $a$ 序列建立笛卡尔树，一个点两侧首个比它大的数中**较小**的那一个即为这个点在笛卡尔树上的父亲。我们求出 $sum_x$ 表示以 $x$ 为根的子树大小，若 $a$ 中所有数互不相同，则任意一个走到 $x$ 处的点，其当前权值均为 $sum_x$。仅需要判断 $sum_x$ 与 $a_{fa_x}$ 的大小关系即可知道走到 $x$ 的点能否继续往上走。

考虑从上往下做，DFS 的同时维护一个变量 $fv$ 表示走到这个点之后，父亲及以外的点还会产生多少贡献。以左儿子为例，若 $sum_{ls(x)}>a_x$，则令 $fv\gets sum_{rs(x)}+a_x$；否则走到 $ls(x)$ 后就停掉了，令 $fv=0$。递归到一个点 $v$ 时，即有 $ans_v=fv+sum_v$。

当 $a$ 中元素有相同时，可能出现 $a_v=a_{son_v}$，导致 $v$ 不能吃掉子树内的所有点。你发现此时只需要到达 $v$ 时权值大于 $a_v$，即可吃掉子树内的所有点，因此从任意非 $v$ 点出发走到 $v$ 的点，都是可以吃掉子树内所有点的。对于 $v$ 本身而言，若其两侧存在比它小的值，则同样可以吃掉子树内所有点；否则 $v$ 出发时不能进行任何合并，$ans_v=a_v$。特判掉最后一种情况即可。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define lowbit(i) (i&-i)
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=5e5+5,mo=998244353,inf=1e18+7;
void read(int &p){
    int x=0,w=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<3)+(x<<1)+ch-'0';
        ch=getchar();
    }
    p=x*w;
}
int n,a[N],ch[N][2],sum[N],ans[N];
void dfs1(int x){
    if(!x)return;
    sum[x]=a[x];
    rep(i,0,1)
        dfs1(ch[x][i]),sum[x]+=sum[ch[x][i]];
}
void dfs2(int x,int fv){
    if(!x)return;
    if((x==1||a[x-1]>=a[x])&&(x==n||a[x+1]>=a[x]))ans[x]=a[x];
    else ans[x]=sum[x]+fv;
    if(sum[ch[x][0]]>a[x])dfs2(ch[x][0],fv+sum[ch[x][1]]+a[x]);
    else dfs2(ch[x][0],0);
    if(sum[ch[x][1]]>a[x])dfs2(ch[x][1],fv+sum[ch[x][0]]+a[x]);
    else dfs2(ch[x][1],0);
}
signed main(){
    read(n);
    rep(i,1,n)
        read(a[i]);
    stack<int>stk;
    a[0]=inf,stk.push(0);
    rep(i,1,n){
        while(!stk.empty()&&a[stk.top()]<a[i])
            ch[i][0]=stk.top(),stk.pop();
        ch[stk.top()][1]=i,stk.push(i);
    }
    int rt;
    while(!stk.empty()&&stk.top())
        rt=stk.top(),stk.pop();
    dfs1(rt),dfs2(rt,0);
    rep(i,1,n)
        printf("%lld ",ans[i]);
    return 0;
}
```

---

## 作者：A2_Zenith (赞：3)

写个暴力，写个优化，过了。

于是我转身向山里走去。

---

首先我们注意到，对于初始状态是 $a_k$ 的情况下，这个史莱姆的重量在任何一个时刻都一定是一段包含 $k$ 的一段连续的区间。我们不妨设当前时刻的区间是 $[l,r]$。

然后呢？首先做一个前缀和，令 $S(l,r) = \sum\limits_{i=l}^r a_i$。这时候，我们先不考虑吃掉史莱姆后的体积变化，然后可以注意到，左右两侧比 $S(l,r)$ 小的可以直接吃掉。往左往右可以扩展多少，可以使用 ST 表做到单次 $\log$。

设扩展后的区间是 $[l',r']$。发现对于 $[l',r']$ 的情况是一个同样的问题。我们只需要知道这样扩展的还会做多少次。

我们发现，如果 $[l',r']$ 不能再扩展了，那么肯定就结束了。否则，吃掉左右两个史莱姆中的一个，此时的体积一定至少是 $S(l,r)$ 的两倍。

所以我们至多只会向外扩展 $\log \sum\limits_{i=1}^na_i = \log V$ 次。

我们对于每个 $k \in [1,n]$ 都做这个事情，复杂度是 $n \log n \log V$ 的。

在具体实现中，我使用了 map 来记录一个区间最多能扩展到的答案（就是写了一个类似路径压缩的东西），效率还不错，最大的点跑了 681 ms。


```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
#define fir first
#define sec second
#define mp make_pair
// #define endl '\n'
using namespace std;
const int maxn=5e5+7;
const int mod=998244353;
int n;
int a[maxn];
int S[maxn];
int LG[maxn];
int ST[maxn][22];
inline void GetLG(){
    LG[0]=-1;
    for(int i=1;i<maxn;i++)LG[i]=LG[i>>1]+1;
}
inline void GetST(){
    for(int i=1;i<=n;i++)ST[i][0]=a[i];
    for(int j=1;j<=LG[n];j++){
        for(int i=1;i<=n-(1<<j)+1;i++){
            ST[i][j]=max(ST[i][j-1],ST[i+(1<<j-1)][j-1]);
        }
    }
}
inline int Qmax(int l,int r){
    int t=LG[r-l+1];
    return max(ST[l][t],ST[r-(1<<t)+1][t]);
}
map<PII,PII> Nxt;
inline PII G(PII p){
    if(Nxt.count(p))return Nxt[p];
    PII nx=p;
    int L=p.fir,R=p.sec;
    int Sum=S[R]-S[L-1];
    int l=1,r=L-1;
    while(l<r){
        int mid=l+r>>1;
        if(Qmax(mid,L-1)<Sum)r=mid;
        else l=mid+1;
    }
    if(L>1)if(Qmax(l,L-1)<Sum)nx.fir=l;
    l=R+1,r=n;
    while(l<r){
        int mid=l+r+1>>1;
        if(Qmax(R+1,mid)<Sum)l=mid;
        else r=mid-1;
    }
    if(R<n)if(Qmax(R+1,l)<Sum)nx.sec=r;
    if(p.fir==nx.fir&&p.sec==nx.sec)return Nxt[p]=p;
    Nxt[p]=G(nx);
    return Nxt[p];
}
signed main(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],S[i]=S[i-1]+a[i];
    GetLG();
    GetST();
    Nxt[mp(1,n)]=mp(1,n);
    for(int i=1;i<=n;i++){
        PII ANS=G(mp(i,i));
        cout<<S[ANS.sec]-S[ANS.fir-1]<<" ";
    }
    cout<<endl;
    return 0;
}
```

---

## 作者：dengchengyu (赞：1)

## arc189_d

首先有一个 $O(n^2)$ 的贪心策略，对于每个点每次能往左就往左，能往右就往右。

考虑优化这个贪心策略，记当前扩展到 $[L,R]$，获得的和为 $sum$，那么我们每次往左扩展到最小的 $l$ 使得 $\max_{l\le j<L}\{a_j\}<sum$，往右也同理。

计算这个东西的时间复杂度，发现假若当前和为 $sum$，我们往左扩展了两次，那么第一次肯定有 $a_{l-1}\ge sum$，那么第二次结束后的 $sum'$ 一定有 $sum'\ge a_{l-1}+sum\ge 2\times sum$。

于是我们经过 $O(1)$ 次扩展一定会使得 $sum$ 至少乘 $2$。往右也同理。

由于 $a_i\le 10^9$，我们在经过 $O(\log a)$ 次后一定会停止或扩展到整个序列。

每次扩展时求最小的 $l$ 和最大的 $r$ 可以二分，可用 ST 表求区间最大值，常数较小。

时间复杂度 $O(n\log n\log a)$。

AC 代码：

```cpp
int a[N];
int n;
int mx[19][N];
int get(int l,int r){
	int len=r-l+1;
	return max(mx[__lg(len)][l],mx[__lg(len)][r-(1<<__lg(len))+1]);
}
ll sum[N];
signed main(){
	read(n);
	fo(i,1,n){
		read(a[i]);
		mx[0][i]=a[i];
		sum[i]=sum[i-1]+a[i];
	}
	fo(i,1,__lg(n))fo(j,1,n-(1<<i)+1){
		mx[i][j]=max(mx[i-1][j],mx[i-1][j+(1<<i-1)]);
	}
	fo(i,1,n){
		int L,R;
		L=R=i;
		ll s=a[i];
		while((L>1&&s>a[L-1])||(R<n&&s>a[R+1])){
			if(L>1&&s>a[L-1]){
				int l=1,r=L-1,as=0;
				while(l<=r){
					int mid=(l+r)>>1;
					if(get(mid,L-1)<s)as=mid,r=mid-1;
					else l=mid+1;
				}
				s=s+sum[L-1]-sum[as-1];
				L=as;
			}
			else if(R<n&&s>a[R+1]){
				int l=R+1,r=n,as=0;
				while(l<=r){
					int mid=(l+r)>>1;
					if(get(R+1,mid)<s)as=mid,l=mid+1;
					else r=mid-1;
				}
				s=s+sum[as]-sum[R];
				R=as;
			}
		}
		write(s,' ');
	}
	return 0;
}
```

---

## 作者：zzy0618 (赞：1)

显然的是，多吃一个是不劣的。

先给出有点问题的赛时想法。对于一个区间的严格最大值，它可以吃掉这个区间所有的数。最大值将这个区间分成两部分，如果一个子区间的严格最大值吃掉子区间的所有数大于这个最大值，那么这个最大值能干的子区间最大值也能干，于是递归解决问题。但是对于有多个相同最大值这个办法就死了，据说这个办法适用于 CF1998E1。

暴力模拟吃是 $O(n)$ 的，我们找到左右第一个大于等于他的，将这个区间全部吃掉，再检查这两个边上的值是否能够吃掉，一直这样做直到不能做为止。复杂度是对的，因为如果吃不掉，不会影响复杂度，如果能吃掉边上的，值就至少变为 $2$ 倍，很快就能通吃全局，所以至多有 $O(\log_2A)$ 次操作。

于是变成了求最近的 $\ge x$ 的位置的问题，可以线段树上二分，但是笔者 TLE 了。可以使用 ST 表加二分，最终复杂度 $n\log n \log A$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,INF=1e18;
int n,m,a[N];
int sum[N];
int s[N][20];
int ask(int l,int r){
    int k=log2(r-l+1);
    return max(s[l][k],s[r-(1<<k)+1][k]);
}int query1(int x,int y){
    int l=x,r=n+1;
    while(l<r){
        int M=l+r>>1;
        if(ask(l,M)>=y)r=M;
        else l=M+1;
    }return r;
}int query2(int x,int y){
    int l=0,r=x;
    while(l<r){
        int M=l+r+1>>1;
        if(ask(M,r)>=y)l=M;
        else r=M-1;
    }return l;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>a[i],sum[i]=sum[i-1]+a[i];
    a[0]=a[n+1]=INF;
    for(int i=0;i<=n+1;++i)
        s[i][0]=a[i];
    for(int j=1;j<20;++j)
        for(int i=0;i+(1<<j)-1<=n+1;++i)
            s[i][j]=max(s[i][j-1],s[i+(1<<j-1)][j-1]);
    for(int i=1;i<=n;++i){
        int l=i,r=i;
        while(1){
            int L=query2(l-1,sum[r]-sum[l-1]);
            int R=query1(r+1,sum[r]-sum[l-1]);
            l=L+1;r=R-1;
            int fl=0;
            if(sum[r]-sum[l-1]>a[L])fl=1,--l;
            if(sum[r]-sum[l-1]>a[R])fl=1,++r;
            if(!fl)break;
        }cout<<sum[r]-sum[l-1]<<' ';
    }
    return 0;
}
```

---

## 作者：未来姚班zyl (赞：1)

并查集维护连续段做法。

## 题目大意

有 $n$ 个史莱姆，大小 $a_i$，如果一个史莱姆比相邻的史莱姆大，就能吃掉那个史莱姆，大小加上它，对于每个史莱姆求最大的大小。

## 题目分析
考虑从小到大加入史莱姆，同时维护已加入史莱姆的连续段。为了方便，先考虑 $a_i$ 互不相等的情况。

当加入 $x$ 的时候，考虑与他相邻的连续段：

如果连续段的和小于等于 $a_x$，则这个连续段里的史莱姆的答案直接结算，然后合并连续段。

否则，直接合并连续段。

有相同的数特判一下就可以了，复杂度 $O(n\log n)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n-3
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=5e5+5,M=1e6+5,inf=(1LL<<31)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,a[N];
int v[N];
int lsh[N],b[N],m,ans[N];
int f[N],Sum[N],Mx[N],Mn[N];
vector<int>p[N],q[N];
inline int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
inline void merge(int x,int y){
	x=find(x),y=find(y);
	
}
inline void insert(int x){
	int w=a[x];
	v[x]=1;
	if(x>1&&v[x-1]){
		int y=find(x-1);
		if(Sum[y]<=Sum[x]){
			while(!p[y].empty())ans[p[y].back()]=Sum[y],p[y].pop_back();
			f[y]=x,Mn[x]=Mn[y],Sum[x]+=Sum[y];
		}else {
			Mx[y]=Mx[x],f[x]=y,Sum[y]+=Sum[x],p[y].pb(x);
		}
	}
	if(x<n&&v[x+1]){
		int y=find(x+1),w=b[a[x]];
		x=find(x);
		if(Sum[y]<=w){
			while(!p[y].empty())ans[p[y].back()]=Sum[y],p[y].pop_back();
			f[y]=x,Mn[x]=Mn[y],Sum[x]+=Sum[y];
		}else {
			int sl=(int)p[x].size(),sr=(int)p[y].size();
			if(sl<=sr){
				for(auto z:p[x])p[y].pb(z);
				Sum[y]+=Sum[x],Mx[y]=Mx[x],Mn[y]=min(Mn[y],Mn[x]),f[x]=y;
			}else {
				for(auto z:p[y])p[x].pb(z);
				Sum[x]+=Sum[y],Mn[x]=min(Mn[x],Mn[y]),f[y]=x;
			}
		}
	}
}
inline void Main(){
	n=read();
	repn(i)a[i]=read(),lsh[i]=ans[i]=a[i];
	sort(lsh+1,lsh+n+1);
	repn(i)if(lsh[i]^lsh[i+1])b[++m]=lsh[i];
	repn(i)a[i]=lower_bound(b+1,b+m+1,a[i])-b;
	repn(i)q[a[i]].pb(i),p[i].pb(i),f[i]=i,Sum[i]=b[a[i]],Mx[i]=Mn[i]=a[i];
	
	repm(i){
		for(auto y:q[i])insert(y);
		for(auto y:q[i]){
			int nw=find(y);
			if(Mx[nw]==Mn[nw]){
				p[nw].clear();
			}
		}
	}
	int x=find(1);
	for(auto y:p[x])ans[y]=Sum[x]; 
	a[0]=m+1,a[n+1]=m+1;
	repn(i)if(a[i]<=a[i-1]&&a[i]<=a[i+1])ans[i]=b[a[i]];
	repn(i)cout <<ans[i]<<' ';
}
signed main(){
	int T=1;
	while(T--)Main();
	return 0;
}
```

---

## 作者：strcmp (赞：0)

提供一个一点细节都没有的倍增 ST 表做法。

- 从 $x$ 开始跳，遇到 $\sum\limits_{i = l + 1}^{r - 1}a_i < \max(a_l,\,a_r)$ 的次数不会超过 $\Theta(\log v)$ 次。

证明：每次遇到并加入这个点，总和在经过两次跳跃后至少倍增一次，最多倍增 $\Theta(\log v)$ 次。

于是枚举起始点 $x$，记录当前的 $\sum\limits_{i = l + 1}^{r - 1} a_i$，每次只是倍增出最接近的大于这个和的左右端点，然后扩展到它们的开区间。

时间复杂度 $\Theta(n \log n \log v)$，5s 时限加上 AT 神机，可以轻松通过。

个人认为寻找分界点这种东西，使用倍增对比二分会少非常多细节。

当然这题考虑笛卡尔树会有更低复杂度的做法，但是这个双 log 做法在 AT 机子上能跑进 400ms，所以就直接写了（也有一点原因是那个 $\log v$ 远远跑不满）。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define mid (l + r >> 1)
using namespace std;
typedef long long int ll;
using ull = unsigned long long int;
using pii = pair<int, int>;
using pli = pair<ll, int>;
constexpr int maxn = 5e5 + 10, mod = 1e9 + 7;
int s[20][maxn], lg[maxn], n; ll a[maxn];
inline int rmq(int l, int r) {
	int g = lg[r - l + 1];
	return max(s[g][l], s[g][r - (1 << g) + 1]);
}
int main() {
	scanf("%d", &n); lg[0] = -1;
	rep(i, 1, n) scanf("%d", &s[0][i]), a[i] = a[i - 1] + s[0][i], lg[i] = lg[i >> 1] + 1;
	rep(i, 1, lg[n]) rep(j, 1, n - (1 << i - 1)) s[i][j] = max(s[i - 1][j], s[i - 1][j + (1 << i - 1)]);
	rep(i, 1, n) {
		int l = i, r = i;
		while (1) {
			int pl = l, pr = r; ll w = a[r] - a[l - 1];
			for (int j = lg[n]; j >= 0; j--) {
				int k = l - (1 << j);
				if (k >= 1 && rmq(k, pl - 1) < w) l = k;
			}
			for (int j = lg[n]; j >= 0; j--) {
				int k = r + (1 << j);
				if (k <= n && rmq(pr + 1, k) < w) r = k;
			}
			if (pl == l && pr == r) break;
		}
		printf("%lld ", a[r] - a[l - 1]);
	}
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

说一个最难写，理论复杂度最劣，最难调的做法。因为翻了 AT 榜单的三页也没有找到这样的做法所以来发一篇题解。

首先根据 CF1998E1 的做法，考虑对于每一个位置 $i$，每一次轮流暴力向左/右暴力扫描，若当前可以吃掉当前方向的下一个元素，那么贪心的吃掉显然不会更差，否则转向。

时间复杂度明显是 $O(n^2)$ 的，但是考虑转向的次数：除了前两次之外，若当前向方向 $o$ 走到 $x_1$ 位置后不能吃掉 $x_1$，则转向到 $-o$ 方向直到不能走。此时若转向回 $o$ 方向后仍然不能吃掉 $x_1$ 位置则直接结束了循环，否则若能吃掉 $x_1$，则显然这一通操作让答案**至少翻了一倍**。显然翻倍 $30$ 次之后不可能存在比当前数大的数，因此转向的次数是 $O(\log V)$ 级别的。

但是直接暴力判断显然不可接受。考虑当前的元素和为 $now$，当前吃掉的元素的左右端点分别为 $l,r$，若当前方向为右，则可以在一直不转向的前提下，吃掉 $i$ 位置（$r<i\le n$）的前提条件是：

$$
\forall j\in[r+1,i]\cap\mathbb{N_+},now+\sum\limits_{k=i+1}^{j-1}a_k>a_j
$$

直接做看上去太慢了，考虑优化。套路的对式子进行移项。变为：

$$
\forall j\in[r+1,i]\cap\mathbb{N_+},now>a_j-\sum\limits_{k=i+1}^{j-1}a_k
$$

另一侧同理。

于是考虑对于每一个 $i$，令 $j$ 结点的点权为：

+ $j=i$，$0$
+ $j>i$，$a_j-\sum\limits_{k=i+1}^{j-1} a_k$
+ $j<i$，$a_j-\sum\limits_{k=j+1}^{i-1} a_k$

但是每一次对这个东西建树时间复杂度显然过高（比暴力还高，是 $O(n^2\log^3n)$），因此考虑按照从小到大的顺序扫描 $i$，初始对 $i=1$ 的情况建线段树，然后若 $i$ 从 $x$ 变为 $x+1$（$x<n$），则对 $[1,x)$ 内所有的结点的点权增加 $-a_i$，$[x+2,n]$ 内所有的结点的点权增加 $a_{i+1}$，就可以让线段树内的权值从 $i=x$ 移动到 $i=x+1$ 的情况啦。

然后对于向左右两侧不停转向扩展的情况，考虑二分出最远的可以移动的结点，这个可以在线段树上维护区间 $\max$ 然后判断 $\max$ 是否 $\ge now$，得到这个极点，并直接在线段树上更新一个前缀或后缀的点权即可。在对于每一个 $i=x$ 的操作计算完毕后，将线段树的操作直接全部暴力撤销即可。时间复杂度为 $O(n\log^3n)$，视实现的优秀程度可以获得 `TLE` 一个或两个点。

考虑优化。容易发现在区间中找最左侧/最右侧的比 $now$ 大或相等的点，可以直接在线段树上二分，做到 $O(n\log^2n)$，这样就可以 `3s` 卡过了。注意线段树上二分的时候一定要下传懒标记，否则样例会输出 `4 30 13 30 2 30`。

核心代码：

```cpp
int n, a[N], s[N];
int qq(int l, int r) {
    return s[r] - s[l - 1];
}
struct qwq {
    int l, r, mx, tag;
    void init(int p) {
        l = r = p;
        if (p != 1) mx = a[p] - qq(2, p - 1);
        else mx = a[p];
    }
    void yhb(int v) {
        mx += v;
        tag += v;
    }
} z[N << 2];
qwq operator+(const qwq &l, const qwq &r) {
    return {l.l, r.r, max(l.mx, r.mx), 0ll};
}
void build(int l, int r, int rt) {
    if (l == r) return z[rt].init(l);
    int mid = l + r >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
    z[rt] = z[rt << 1] + z[rt << 1 | 1];
}
void pushyhb(int v) {
    if (z[v].tag) {
        z[v << 1].yhb(z[v].tag);
        z[v << 1 | 1].yhb(z[v].tag);
        z[v].tag = 0;
    }
}
void modify(int rt, int ll, int rr, int v) {
    if (ll > rr) return;
    int l = z[rt].l, r = z[rt].r;
    if (ll <= l && r <= rr) return z[rt].yhb(v);
    int mid = l + r >> 1;
    pushyhb(rt);
    if (ll <= mid) modify(rt << 1, ll, rr, v);
    if (mid < rr) modify(rt << 1 | 1, ll, rr, v);
    z[rt] = z[rt << 1] + z[rt << 1 | 1];
}
int query(int rt, int ll, int rr) {
    int l = z[rt].l, r = z[rt].r;
    if (ll <= l && r <= rr) return z[rt].mx;
    int mid = l + r >> 1, mx = -1e18;
    pushyhb(rt);
    if (ll <= mid) mx = query(rt << 1, ll, rr);
    if (mid < rr) mx = max(mx, query(rt << 1 | 1, ll, rr));
    return mx;
}
// 在区间中找到最后一个 >= now 的位置
int find1(int rt, int ll, int rr, int now) {
    int &l = z[rt].l, &r = z[rt].r;
    int mid = l + r >> 1;
    if (l == r) {
        if (z[rt].mx >= now) return l;
        return -1;
    }
    pushyhb(rt);
    if (l == ll && r == rr) {
        if (z[rt].mx < now) return -1;
        if (z[rt << 1 | 1].mx >= now) return find1(rt << 1 | 1, mid + 1, rr, now);
        return find1(rt << 1, ll, mid, now);
    }
    if (rr <= mid) return find1(rt << 1, ll, rr, now);
    if (ll > mid) return find1(rt << 1 | 1, ll, rr, now);
    int pos = find1(rt << 1 | 1, mid + 1, rr, now);
    if (~pos) return pos;
    return find1(rt << 1, ll, mid, now);
}
// 在区间中找到第一个 >= now 的位置
int find2(int rt, int ll, int rr, int now) {
    int &l = z[rt].l, &r = z[rt].r;
    int mid = l + r >> 1;
    if (l == r) {
        if (z[rt].mx >= now) return l;
        return -1;
    }
    pushyhb(rt);
    if (l == ll && r == rr) {
        if (z[rt].mx < now) return -1;
        if (z[rt << 1].mx >= now) return find2(rt << 1, ll, mid, now);
        return find2(rt << 1 | 1, mid + 1, rr, now);
    }
    if (rr <= mid) return find2(rt << 1, ll, rr, now);
    if (ll > mid) return find2(rt << 1 | 1, ll, rr, now);
    int pos = find2(rt << 1, ll, mid, now);
    if (~pos) return pos;
    return find2(rt << 1 | 1, mid + 1, rr, now);
}

struct ovo {int l, r, v;};
void run() {
    n = read();
    for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + (a[i] = read());
    build(1, n, 1);
    for (int i = 1; i <= n; ++i) {
        int lx = i, rx = i, now = a[i], lastop = 1, sile = 0;
        vector<ovo> vec;
        while (1) {
            if (lastop == 1) {
                if (lx == 1)
                    ++sile;
                else {
                    int l = 1, r = lx - 1, best = -1;
                    best = find1(1, 1, lx - 1, now) + 1;
                    if (best == 0) best = 1;
                    else if (best == lx) best = -1;
                    if (best == -1) ++sile;
                    else {
                        now += qq(best, lx - 1);
                        modify(1, 1, best, qq(best, lx - 1));
                        vec.push_back({1, best, qq(best, lx - 1)});
                        lx = best;
                    }
                }
            } else {
                if (rx == n)
                    ++sile;
                else {
                    int l = rx + 1, r = n, best = -1;
                    best = find2(1, rx + 1, n, now) - 1;
                    if (best == -2) best = n;
                    else if (best == rx) best = -1;
                    if (best == -1) ++sile;
                    else {
                        now += qq(rx + 1, best);
                        modify(1, rx + 1, n, qq(rx + 1, best));
                        vec.push_back({rx + 1, n, qq(rx + 1, best)});
                        rx = best;
                    }
                }
            }
            if (1 < sile) break;
            lastop = -lastop;
        }
        for (auto &[l, r, v] : vec)
            modify(1, l, r, -v);
        printf("%lld ", now);
        if (i != n) {
            modify(1, 1, i - 1, -a[i]);
            modify(1, i + 2, n, a[i + 1]);
        }
    }
    cout << '\n';
}
```

---

## 作者：Zhaohongrui (赞：0)

通过观察发现，对于史莱姆 $x$，如果它最多只能吃 $[l+1, r-1]$ 之间的史莱姆，当且仅当 $a_l \ge \sum_{i=l+1}^{r-1}{a_i}$ 且 $a_r \ge \sum_{i=l+1}^{r-1}{a_i}$。

于是我们可以暴力枚举满足上述条件的 $(l, r)$，并是用线段树维护区间取 $\min$，单点查询。

这样做虽然看似是 $O(n^2 \log \max{a_i})$ 的，无法通过本题。

但因为满足 $l+1<r$ 且 $a_l \ge \sum_{i=l+1}^{r-1}{a_i}$ 的 $(l, r)$ 只有 $O(n \log \max{a_i})$ 个。（想一想为什么？）

所以总复杂度为 $O(n \log n \log \max{a_i})$，可以通过本题。

一些细节：

1. 当 $a_l<\sum_{i=l+1}^{r-1}{a_i}$ 时，应立刻退出循环。
2. 线段树元素初始值应赋值为 $\sum_{i=1}^{n}{a_i}$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 5e5;
const LL inf = 0x3f3f3f3f3f3f3f3f;
int n;
LL a[N + 5];
LL sum;
class segment_tree {
#define mid (tree[x].l + tree[x].r >> 1)
#define lson (x << 1)
#define rson (x << 1 | 1)
	private:
	struct Tree {
		int l, r;
		LL lazy = inf, val = inf;
		Tree operator +(const Tree &x) const {
			return {l, x.r, inf, min(val, x.val)};
		}
	} tree[(N << 2) + 5];
	void update(int x, LL val) {
		tree[x].lazy = min(tree[x].lazy, val);
		tree[x].val = min(tree[x].val, val);
	}
	void pushup(int x) {
		tree[x] = tree[lson] + tree[rson];
	}
	void pushdown(int x) {
		LL &lazy = tree[x].lazy;
		update(lson, lazy), update(rson, lazy);
		lazy = inf;
	}
	public:
	void build(int l, int r, int x = 1) {
		if (l == r) {
			tree[x] = {l, r, inf, sum};
			return;
		}
		int m = l + r >> 1;
		build(l, m, lson), build(m + 1, r, rson);
		pushup(x);
	}
	void modify(int l, int r, LL val, int x = 1) {
		if (tree[x].l >= l && tree[x].r <= r) {
			update(x, val);
			return;
		}
		pushdown(x);
		if (l <= mid) modify(l, r, val, lson);
		if (r > mid) modify(l, r, val, rson);
		pushup(x);
	}
	Tree query(int i, int x = 1) {
		if (tree[x].l == tree[x].r) return tree[x];
		pushdown(x);
		return i <= mid ? query(i, lson) : query(i, rson);
	}
#undef mid
#undef lson
#undef rson
} tree;
int main() {
	scanf("%d", &n);
	a[0] = a[n + 1] = inf;
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]), sum += a[i];
	tree.build(1, n);
	for (int i = 0; i <= n - 1; i++) {
		LL sum = a[i + 1];
		for (int j = i + 2; j <= n + 1; j++) {
			if (sum > a[i]) break;
			if (sum <= min(a[i], a[j]))
				tree.modify(i + 1, j - 1, sum);
			sum += a[j];
		}
	}
	for (int i = 1; i <= n; i++)
		printf("%lld ", tree.query(i).val);
	putchar('\n');
	return 0;
}

```

---

