# [ZJOI2019] Minimax搜索

## 题目描述

九条可怜是一个喜欢玩游戏的女孩子。为了增强自己的游戏水平，她想要用理论的武器武装自己。这道题和著名的 Minimax 搜索有关。

可怜有一棵有根树，根节点编号为 $1$。定义根节点的深度为 $1$，其他节点的深度为它的父亲的深度加一。同时在叶子节点权值给定的情况下，可怜用如下方式定义了每一个非节点的权值：
- 对于深度为奇数的非叶子节点，它的权值是它所有子节点的权值最大值。
- 对于深度为偶数的非叶子节点，它的权值是它所有子节点的权值最小值。

最开始，可怜令编号为 $i$ 的叶子节点权值为 i，并计算得到了根节点的权值为 $W$。

现在，邪恶的 Cedyks 想要通过修改某些叶子节点的权值，来让根节点的权值发生改变。Cedyks 设计了一个量子攻击器，在攻击器发动后，Cedyks 会随机获得一个非空的叶子节点集合 $S$ 的控制权，并可以花费一定的能量来修改 $S$ 中的叶子节点的权值。

然而，修改叶子节点的权值也要消耗能量，对于 $S$ 中的叶子节点 $i$，它的初始权值为 $i$，假设 Cedyks 把它的权值修改成了 $w_i$（$w_i$ **可以是任意整数，包括负数**），则 Cedyks 在这次攻击中，需要花费的能量为 $\max_{i\in S} |i − w_i|$。

Cedyks 想要尽可能节约能量，于是他总是会**以最少的能量来完成攻击**，即在花费的能量最小的情况下，让根节点的权值发生改变。令 $w(S)$ 为 Cedyks 在获得了集合 $S$ 的控制权后，会花费的能量。特殊地，对于某些集合 $S$，可能无论如何改变 $S$ 中叶子节点的权值，根节点的权值都不会发生改变，这时，$w(S)$ 的值被定义为 $n$。为了方便，我们称 $w(S)$ 为 $S$ 的稳定度。

当有 $m$ 个叶子节点的时候，一共有 $2^m − 1$ 种不同的叶子节点的非空集合。在发动攻击前，Cedyks 想要先预估一下自己需要花费的能量。于是他给出了一个区间 $[L, R]$，他想要知道对于每一个 $k \in [L, R]$，有多少个集合 $S$ 满足 $w(S) = k$。

## 说明/提示

#### 样例 1 解释

最开始，在可怜的设定下（$i$ 号叶子节点的权值为 $i$），根节点的权值为 $4$。

树上一共有 $3$ 个叶子节点 $\{2,3,4\}$，一共有 $7$ 个非空的叶子节点权值，其中：

- $\{4\}, \{2,4\}, \{3,4\}, \{2,3,4\}$ 的稳定度为 $1$，只要稍微修改 $4$ 号叶子节点的权值，根节点的权值就会发生改变。
- $\{2\},\{3\}$ 的稳定度为 $5$，因为 $5$ 号的权值是 $2,3$ 的较小值，在只修改 $2$ 号或者 $3$ 号的情况下，$5$ 号点的权值始终小于等于 $3$，所以根节点的权值始终为 $4$。
- $\{2,3\}$ 的稳定度为 $3$，要让根节点的权值发生改变，必须让 $5$ 的权值大于 $4$，因此 $w_2 ,w_3$都必须要大于 $4$，所以稳定度为 $3$，一个可行的方案是把 $w_2 ,w_3$ 都设为 $5$。

#### 数据规模与约定

| 测试点 | $n$ | 其他约定 | 测试点 | $n$ | 其他约定 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $\le10$ | $L=R=n$ | $6$ | $\le2\times 10^5$ | $R-L\le50$ |
| $2$ | $\le50$ | $L=R=n$ | $7$ | $\le2\times 10^5$ | $R-L\le50$ |
| $3$ | $\le50$ | $L=R=n$ | $8$ | $\le2\times 10^5$ | 无 |
| $4$ | $\le5\times 10^3$ | $L=R=n$ | $9$ | $\le2\times 10^5$ | 无 |
| $5$ | $\le5\times 10^3$ | $L=R=n$ | $10$ | $\le2\times 10^5$ | 无 |

对于 $100\%$ 的数据，保证 $n\ge2$，$1\le L \le R \le n$。

## 样例 #1

### 输入

```
5 1 5
1 5
1 4
5 3
5 2```

### 输出

```
4 0 1 0 2```

# 题解

## 作者：Fuyuki (赞：17)

直接求 $w(S)=k$ 的方案数很困难，考虑放宽条件求 $w(S)\leq k$ 的方案数，即计算修改代价不大于 $k$ 的方案数。

设 $u$ 的权值为 $dp_u$，根的权值为 $dp_1=W$。如果有 $W\in S$，则只需要花费 $1$ 的代价将 $W$ 权值修改掉。这种情况是平凡的，所以接下来默认 $w\notin S$。

在整棵树上，满足 $dp_u=W$ 的所有节点 $u$ 构成了一条从叶子到根的链。如果这根链上有任何一个节点的权值发生改变，那么根的权值也会发生改变。

考虑每个叶子 $x$ 和 $W$ 的 $lca$，如果 $lca$ 的深度为奇数，那么只有当 $x>W$ 的时候，$W$ 的权值才可能因为 $x$ 发生改变。换言之，如果 $x\in S$，则此时将 $x$ 修改为 $x>W$ 一定比 $x<W$ 更优。

因此，如果当前代价为 $k$，则根据与 $W$ 的 $lca$ 的深度，可以贪心地直接确定每个节点的权值。

将链上的边断掉，可以对每个联通块求解有多少种方案会使得子树中存在的权值 $W$ 在当前位置被替换掉。设 $f_u$ 表示使得 $dp_u<W$ 的方案数，$cnt_u$  表示以 $u$ 为根的子联通块内的总方案数（即 $2$ 的叶子个数次方）。链上只要有一个节点能替换掉 $W$ 就是合法的，因此合法的方案数为总方案数减去所有不合法的方案数之积：
$$
ans=sum-\prod_{dp_u=W}([dep_u\operatorname{mod} 2\equiv 1]f_u+[dep_u\operatorname{mod} 2\equiv 0](cnt_u-f_u))
$$
计算 $f_u$ 的时候，注意到不存在权值为 $W$ 的叶子，因此使得 $dp_u>W$ 的方案数可以简单表示为 $cnt_u-f_u$ 。转移也可以写出来了：
$$
f_u=\begin{cases}\prod_{v\in son_u} f_v&dep_u\equiv 1\pmod{2}\\
cnt_u-\prod_{v\in son_u} (cnt_v-f_v)&dep_u\equiv 0\pmod{2}
\end{cases}
$$
设 $g_u=cnt-f_u$ 当 $dep_u\equiv 1\pmod{2}$，$g_u=f_u$ 当 $dep_u\equiv 0\pmod{2}$，那么就有：

$$ans=sum-\prod_{dp_u=W}(cnt_u-g_u)$$

$$g_u=cnt_u-\prod_{v\in son_u}g_v$$
至此，枚举最大代价的限制 $k$，可以 $O(n)$ 地计算答案的数量。

注意到将 $k$ 在 $1\sim n$ 中枚举的时候，每个叶子的 $f$ 最多发生 $1$ 次改变，这启发我们动态维护 $dp$ 的过程。

重链剖分之后，有：
$$
g_u=cnt_u+(-\prod_{v\in light_u}g_v)g_{weight_u}
$$
可以发现这是一个 $a_i=b+ca_{i+1}$ 的形式，并且满足结合律，所以可以直接照搬动态 $dp$ 的做法。

在每次跳轻边的时候，都需要一次求逆，因此哪怕你写了全局平衡二叉树，复杂度依旧会达到 $O(nlog^2n)$。

维护轻儿子的积时，因为可能出现乘 $0$，除 $0$ 的情况，所以需要一个额外的数组来统计 $0$ 的个数。

~~~~
```cpp
#include<bits/stdc++.h>
using namespace std;
#define lc ls[p]
#define rc rs[p]
#define I inline int
#define V inline void
#define ll long long int
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define REP(u) for(int i=h[u],v;v=e[i].t;i=e[i].n)if(v!=pre[u])
const int N=2e5+1,mod=998244353,INF=0x3f3f3f3f,sgn[2]={-1,1};
V cmin(int&x,int y){if(y-x>>31)x=y;}
V cmax(int&x,int y){if(x-y>>31)x=y;}
V check(int&x){x-=mod,x+=x>>31&mod;}
int sum[N],zero[N];
int n,m,L,R,W,tot,qwq,bas=1;
int h[N],dep[N],dp[N],ans[N],co[N];
int siz[N],wes[N],tmp[N],pre[N],cnt[N];
int ls[N],rs[N],fa[N],id[N],top[N],d[N];
struct node{
	int b,c;
	node(int x=0,int y=1){b=x,c=y;}
	node operator+(const node&u)const{
		return(node){int((1ll*c*u.b+b)%mod),int(1ll*c*u.c%mod)};
	}
}a[N],t[N];
struct edge{int t,n;}e[N<<1];
V add_edge(int x,int y){
	e[++tot]=(edge){y,h[x]},h[x]=tot,d[x]++;
	e[++tot]=(edge){x,h[y]},h[y]=tot,d[y]++;
}
I Pow(ll t,int x,ll s=1){for(;x;x>>=1,t=t*t%mod)if(x&1)s=s*t%mod;return s;}
V input(){
	scanf("%d%d%d",&n,&L,&R);int x,y;
	FOR(i,2,n)scanf("%d%d",&x,&y),add_edge(x,y);
}
I leaf(int u){return u>1&&d[u]==1;}
V dfs0(int u){
	dp[u]=(~dep[u]&1)*INF;
	REP(u)dep[v]=dep[u]+1,pre[v]=u,dfs0(v),(dep[u]&1?cmax:cmin)(dp[u],dp[v]);
	if(leaf(u))dp[u]=u;
}
V dfs1(int u){
	siz[u]=1,cnt[u]=1+leaf(u),check(bas<<=leaf(u));
	REP(u)if(dp[v]!=W){
		dep[v]=dep[u]+1,pre[v]=u,dfs1(v),siz[u]+=siz[v];
		if(cnt[u]=1ll*cnt[u]*cnt[v]%mod,siz[v]>siz[wes[u]])wes[u]=v;
	}
	REP(u)if(dp[v]==W)dfs1(v);
}
V upd(int p){t[p]=t[lc]+a[p]+t[rc];}
V add(int x,int w){
	if(w)sum[x]=1ll*sum[x]*w%mod,a[x].c=1ll*a[x].c*w%mod;
	else if(!zero[x]++)a[x].c=0;
}
V del(int x,int w){
	if(w=Pow(w,mod-2))sum[x]=1ll*sum[x]*w%mod,a[x].c=1ll*a[x].c*w%mod;
	else if(!--zero[x])a[x].c=sum[x];
}
V build(int&p,int L,int R){
	if(L>R)return;
	int sum=0,now=0,x;
	FOR(i,L,R)sum+=siz[tmp[i]];
	for(x=L,sum>>=1;(now+=siz[tmp[x]])<sum;x++);
	p=tmp[x],build(lc,L,x-1),build(rc,x+1,R),fa[lc]=fa[rc]=p;
}
V init(int p){if(p)init(lc),init(rc),upd(p);}
V dfs2(int u,int p){
	id[tmp[++tot]=u]=m,siz[u]-=siz[wes[u]],sum[u]=1,co[u]=p;
	if(wes[u])a[u]={cnt[u],sum[u]=mod-1},dfs2(wes[u],p),top[u]=top[wes[u]];
	else{
		if(leaf(u)&&(a[u]={(u<=W)+(u<W),0},dep[u]&1))a[u].b=cnt[u]-a[u].b;
		build(top[u],1,tot),tot=0;
	}
	REP(u)if(v!=wes[u]&&dp[v]!=W)dfs2(v,p),fa[top[v]]=u,init(top[v]),add(u,t[top[v]].b);
}
V build(int u){
	dfs2(m=u,sgn[dep[u]&1]),init(top[u]),add(0,(cnt[u]+mod-t[top[u]].b)%mod);
	REP(u)if(dp[v]==W)build(v);
}
V init(){dfs0(dep[1]=1),W=dp[1],dfs1(sum[0]=1),tot=0,build(m=1);}
V modify(int p){
	int x=id[p];
	del(0,cnt[x]+mod-t[top[x]].b);
	for(a[p]={1,0};p;p=fa[p]){
		if(p==top[p]&&fa[p])del(fa[p],t[p].b);
		upd(p);
		if(p==top[p]&&fa[p])add(fa[p],t[p].b);
	}
	add(0,cnt[x]+mod-t[top[x]].b);
}
V work(){
	FOR(i,1,n){
		check(ans[i]=bas+mod-a[0].c);
		if(W+i<=n&&leaf(W+i)&&co[W+i]<0)modify(W+i);
		if(W-i>=2&&leaf(W-i)&&co[W-i]>0)modify(W-i);
	}
	ans[0]=0,ans[n]=bas-1;
	ROF(i,n,1)check(ans[i]+=mod-ans[i-1]);
	FOR(i,L,R)cout<<ans[i]<<' ';
}
int main(){
	input();
	init();
	work();
	return 0;
}
```
~~~~

~~起码 10 个月没写动态 dp 了，写了好久~~

---

## 作者：cjy2003 (赞：17)

考虑求稳定度恰好是k的并不方便,于是转而求稳定度小于等于k的做差分即可   
首先考虑暴力   
考虑如何$O(n)$求稳定度小于等于k的方案数   
因为每个叶子结点的权值都不同,所以最终转移到根的一定是唯一的一条链,称为答案链   
而只要通过修改答案链上某个点子树中其他叶节点使链上这个点权值改变,就会使根节点权值改变   
我们要求有多少个集合在稳定度小于等于k时可以让链上的点权值改变,可以通过求有多少个集合不可以让链上点权值改变,用总数减掉即可   
由于链上的点有奇深度也有偶深度,所以分开考虑   
先考虑奇数深度的,偶数同理   
设$val$为当前根节点权值,$delt$为当前考虑的稳定度,$cnt[i]$为i子树中2^{叶子节点个数}   
设$dp[i]$表示考虑i的子树,有多少种集合满足使i的权值$<=val$(即不会改变链权值)   
当i为叶子时,$dp[i]=(i<=val)+(i+delt<=val)$   
当i深度为奇数时,i的所有儿子都要满足条件,所以$dp[i]=\prod_{j\in son[i]}dp[j]$  
当i深度为偶数时,只要一个儿子满足就可以,所以用总的减掉不合法的$dp[i]=cnt[i]-\prod_{j\in son[i]}(cnt[j]-dp[j])$   
最终的答案就是所有链上点子树dp值的乘积   

考虑对这个$dp$进行优化   
发现改变$delt$时,每个叶子节点的$dp$值只会改变一次,而改变后就会相应影响其上方的点的$dp$值,非常像动态dp   
为了方便动态dp的转移,我们定义$dp'$   
同样的先考虑奇数深度的链上的点   
由于最终答案是链上这个点儿子dp值的乘积,所以这个点儿子的$dp'$就等于$dp$   
而与这个点儿子节点深度奇偶性相同的点$dp'=dp$,不同的点$dp'=cnt-dp$   
于是转移就变得相同$dp'[i]=cnt[i]-\prod_{j\in son[i]}dp'[j]$,方便维护   
由于稳定度为0时许多叶子点的$dp$为0,而在改变其权值时需要除掉原来的dp值,不方便   
所以稳定度从大往小考虑   
动态$dp$的细节:   
点i和他重儿子zson[i]$dp'$值的关系可以看做$dp'[i]=k*dp'[zson[i]]+b$,其中$k=-\prod_{j\in son[x],j!=zson[x]}dp'[j],b=cnt[i]$   
这个东西本质上是矩阵乘法,但是{k1,b1} * {k2,b2}={k1 * k2,k1*b2+b1}可以减小常数   
另外要注意,判叶子节点不能只判出边个数为1,还要判不是根节点   
代码:   
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int mod=998244353;
int kpow(int a,int b)
{
    int s=1;
    while(b)
    {
        if(b&1)s=1ll*s*a%mod;
        b>>=1;
        a=1ll*a*a%mod;
    }
    return s;
}
int mdf[200020][3];
struct bian
{
    int to,nxt;
}bi[400040];
int n,head[200020],num,l,r,depth[200020],va[200020],cnt[200020],ans[200020];
int siz[200020],zson[200020],tp[200020],f[200020],id[200020],dy[200020],idnum,ed[200020],rt[200020];
int dp[200020],Ans=1;
bool type[200020],flag;
struct data
{
    int k,b;
    data(int kk=0,int bb=0){k=kk,b=bb;}
    friend data operator * (data a,data b){return data(1ll*a.k*b.k%mod,(1ll*a.k*b.b+a.b)%mod);}
}tr[800080],p[200020];
void add(int from,int to)
{
    bi[++num].nxt=head[from];
    head[from]=num;
    bi[num].to=to;
}
void predfs(int v,int fa)
{
    depth[v]=depth[fa]+1;f[v]=fa;siz[v]=1;
    if(!bi[head[v]].nxt&&v!=1)
    {
        va[v]=v,cnt[v]=2;
        return ;
    }
    int u;va[v]=depth[v]&1?1:n;cnt[v]=1;
    for(int i=head[v];i;i=bi[i].nxt)
    {
        u=bi[i].to;
        if(u==fa)continue;
        predfs(u,v);
        siz[v]+=siz[u];
        if(siz[u]>siz[zson[v]])zson[v]=u;
        cnt[v]=1ll*cnt[v]*cnt[u]%mod;
        if(depth[v]&1)va[v]=max(va[v],va[u]);
        else va[v]=min(va[v],va[u]);
    }
}
int getdp(int v,int fa,int topp,int RT)
{
    rt[v]=RT,id[v]=++idnum,dy[idnum]=v,tp[v]=topp;
    if(!bi[head[v]].nxt&&v!=1)
    {
        if(type[RT])
        {
            dp[v]=p[v].k=(depth[v]&1)?2-(v<=va[1]):(v<=va[1]);
            if(v<=va[1])mdf[va[1]-v][++mdf[va[1]-v][0]]=v;
        }
        else
        {
            dp[v]=p[v].k=(depth[v]&1)?(v>=va[1]):2-(v>=va[1]);
            if(v>=va[1])mdf[v-va[1]][++mdf[v-va[1]][0]]=v;
        }
        ed[topp]=idnum;
        return dp[v];
    }
    int u,ret=mod-1;
    dp[v]=getdp(zson[v],v,topp,RT);
    for(int i=head[v];i;i=bi[i].nxt)
    {
        u=bi[i].to;
        if(u==fa||u==zson[v])continue;
        ret=1ll*ret*getdp(u,v,u,RT)%mod;
    }
    p[v]=data(ret,cnt[v]),(dp[v]=cnt[v]+1ll*dp[v]*ret%mod)>=mod?dp[v]-=mod:0;
    return dp[v];
}
void dfs(int v,int fa)
{
    int ret=1,u;
    for(int i=head[v];i;i=bi[i].nxt)
    {
        u=bi[i].to;
        if(u==fa)continue;
        if(va[u]==va[v])dfs(u,v);
        else f[u]=0,type[u]=depth[v]&1,Ans=1ll*Ans*getdp(u,v,u,u)%mod;
    }
//	printf("%d %d\n",v,ret);
}
void build(int k,int l,int r)
{
    if(l==r)
    {
        tr[k]=p[dy[l]];
        return ;
    }
    build(k<<1,l,l+r>>1),build(k<<1|1,(l+r>>1)+1,r);
    tr[k]=tr[k<<1]*tr[k<<1|1];
}
void upd(int k,int l,int r,int pos)
{
    if(l==r)
    {
        tr[k]=p[dy[l]];
        return ;
    }
    if(pos<=l+r>>1)upd(k<<1,l,l+r>>1,pos);
    else upd(k<<1|1,(l+r>>1)+1,r,pos);
    tr[k]=tr[k<<1]*tr[k<<1|1];
}
data query(int k,int l,int r,int ll,int rr)
{
    if(l>=ll&&r<=rr)return tr[k];
    if(rr<=(l+r>>1))return query(k<<1,l,l+r>>1,ll,rr);
    if(ll>(l+r>>1))return query(k<<1|1,(l+r>>1)+1,r,ll,rr);
    return query(k<<1,l,l+r>>1,ll,rr)*query(k<<1|1,(l+r>>1)+1,r,ll,rr);
}
void modify(int x)
{
//	if(flag)printf("%d\n",x);
    int RT=rt[x];
    Ans=1ll*Ans*kpow(dp[RT],mod-2)%mod;
    p[x].k=(type[RT]^(depth[x]&1))?2:0;
    upd(1,1,idnum,id[x]);
    while(f[tp[x]])
    {
    //	if(flag)printf("%d\n",x);
        int fa=f[tp[x]];
        p[fa].k=1ll*p[fa].k*kpow(dp[tp[x]],mod-2)%mod;
        data s=query(1,1,idnum,id[tp[x]],ed[tp[x]]);
        (dp[tp[x]]=s.k+s.b)>=mod?dp[tp[x]]-=mod:0;
        p[fa].k=1ll*p[fa].k*dp[tp[x]]%mod;
        upd(1,1,idnum,id[fa]);
        x=fa;
    }
    data s=query(1,1,idnum,id[RT],ed[RT]);
    (dp[RT]=s.k+s.b)>=mod?dp[RT]-=mod:0;
    Ans=1ll*Ans*dp[RT]%mod;
}
int main()
{
    scanf("%d %d %d",&n,&l,&r);
    int x,y;
    for(int i=1;i<n;++i)
    {
        scanf("%d %d",&x,&y);
        add(x,y),add(y,x);
    }
    predfs(1,0);
    dfs(1,0);
//    printf("%d\n",mdf[1][1],mdf[1][2]);
    build(1,1,idnum);
 //   printf("%d ",mdf[1][0]);
    for(int i=n-1;i;--i)
    {
    	if(i==1)flag=1;
    	for(int u=1;u<=mdf[i][0];++u)modify(mdf[i][u]);
    	(ans[i]=cnt[1]+mod-Ans)>=mod?ans[i]-=mod:0;
    //	printf("%d\n",i);
    }
    ans[n]=cnt[1]-1;
    for(int i=l;i<=r;++i)
        printf("%d ",ans[i]-ans[i-1]<0?ans[i]-ans[i-1]+mod:ans[i]-ans[i-1]);
    return 0;
}
```


---

## 作者：lyyi2003 (赞：10)

## 发一篇不写动态dp的题解

动态dp太套路，我才不去写 ~~(其实是我不会~~

基本的思路还是对每个点考虑它会受到那些儿子的影响，然后dp出最小代价。

设f[i][j]表示，若要改变i的权值，i子树内所有叶子节点集合S中，满足w(S)=j的S的数量。考虑如何转移:

如果一个点为奇点(即深度为奇数)，若要使它的权值改变，那么有两种情况：


1.它的最大儿子改变了;

2.它的一个其它儿子的权值超过了最大的儿子;

设i的最大儿子为u，如果是第一种情况，直接从f[u][j]转移过来就可以了，但是对于第二种情况，设另一个儿子为v，注意到要使w[v]>w[u]，则w[v]必须加上w[u]-w[v]+1，意味着w[v]不仅需要改变，还至少要改变一个固定的值，难道我们要多设一维状态来表示要改变的值吗？

仔细思考一下就会发现，对于每一个i，w[i]需要改变的值都是唯一确定的，具体地，设点i需要改变的值为d(这里假设i为奇点，偶数类似），它的最大儿子为u，则分以下几种情况：

1. d<0，则i的**所有**孩子都要改变到w[u]-d以下(已经在w[u]-d以下则不改变)

2. d>0, 则需要存在一个儿子(包括u)改变到w[u]+d以上

3. 特殊地，若一个点只要求改变，我们令它的d值为0(就是上面讨论的那种)

初始时，点1的d值为0，一遍dfs即可求得所有点的d值，然后就可以按照d值来对每个点进行dp了。(可以参考我的代码）

那么如何合并两个儿子的答案呢？f[u][j]中只包含了u子树内所有叶子集合的数量，那么跨子树的呢？

设我们要合并的两个儿子为u,v，若存在u子树中的一个集合Su满足w(Su)=j，v子树中的一个集合Sv满足w(Sv)=k，则两个集合的并Suv满足w(Suv)=min(j,k)，也就是由f[u][j]*f[v][k]可以转移到f[i][min(j,k)] （这是上述情况２或３，情况１还需另外讨论）

我们并不需要枚举每一个j,k，前缀和优化一下就好了

这样我们就得到了一个O(n^2)的dp算法 ~~（对就是50分暴力~~

先贴一下50分暴力代码：

```cpp

// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=5007;
const int M=10007;
const ll mod=998244353;
ll f[N][N],tmp[N],s[N];
int hd[N],pre[M],to[M],num,dep[N],son[N],w[N],n;
void adde(int x,int y)
{
    num++;pre[num]=hd[x];hd[x]=num;to[num]=y;
}
void dfs(int v,int fa)//预处理w与最大(小)的儿子
{
    int i,u;
    dep[v]=dep[fa]+1;s[v]=1;
    for(i=hd[v];i;i=pre[i])
    {
        u=to[i];
        if(u==fa)continue;
        dfs(u,v);s[v]=s[v]*s[u]%mod;
        if(dep[v]&1){
            if(w[u]>w[son[v]])son[v]=u;
        }else if(!son[v]||w[u]<w[son[v]])son[v]=u;
    }
    if(!son[v])w[v]=v,s[v]=2;
    else w[v]=w[son[v]];
}
//以下是dp值合并
void orun(ll (&a)[N],ll (&b)[N])//情况2,3
{
    memset(tmp,0,sizeof(tmp));
    ll s1=a[n],s2=0;
    for(int i=n;i>=1;i--)
    {
        tmp[i]=(tmp[i]+s1*b[i]+s2*a[i])%mod;
        s1=(s1+a[i-1])%mod,s2=(s2+b[i])%mod;
    }
    for(int i=1;i<=n;i++)
        tmp[i]=(tmp[i]+a[i]+b[i])%mod;
    memcpy(a,tmp,sizeof(tmp));
}
void andun(ll (&a)[N],ll (&b)[N])//情况1
{
    memset(tmp,0,sizeof(tmp));
    ll s1=a[1],s2=0;
    for(int i=1;i<=n;i++)
    {
        tmp[i]=(tmp[i]+s1*b[i]+s2*a[i])%mod;
        s1=(s1+a[i+1])%mod,s2=(s2+b[i])%mod;
    }
    for(int i=1;i<=n;i++)
        tmp[n]=(tmp[n]+a[i]+b[i])%mod;
    memcpy(a,tmp,sizeof(tmp));
}
void dp(int v,int fa,int d)//这里d值直接传参
{
    int i,u;
    if(!son[v])f[v][max(1,abs(d))]=1;
    else if(!d||d>0&&(dep[v]&1)||d<0&&!(dep[v]&1))//复杂的讨论。。。
    {
        int tar;
        if(d)tar=w[son[v]]+d;
        else tar=dep[v]&1?w[son[v]]+1:w[son[v]]-1;
        for(i=hd[v];i;i=pre[i])
        {
            u=to[i];
            if(u==fa)continue;
            if(u==son[v])dp(u,v,d);
            else dp(u,v,tar-w[u]);
            orun(f[v],f[u]);
        }
    }
    else
    {
        int tar=w[son[v]]+d,first=1;
        ll mul=1;
        for(i=hd[v];i;i=pre[i])
        {
            u=to[i];
            if(u==fa)continue;//这里有一个细节比较重要，就是当w[u]的值不需要改变时不dp，直接记录答案
            if(d<0&&w[u]<=tar||d>0&&w[u]>=tar)
                mul=mul*s[u]%mod;
            else
            {
                dp(u,v,tar-w[u]);
                if(first)memcpy(f[v],f[u],sizeof(f[u])),first=0;
                else andun(f[v],f[u]);
            }
        }
        for(i=1;i<=n;i++)
            f[v][i]=f[v][i]*mul%mod;
        f[v][n]=(f[v][n]+mul-1)%mod;
    }
}
int main()
{
    int i,x,y,l,r;
    scanf("%d%d%d",&n,&l,&r);
    for(i=1;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        adde(x,y),adde(y,x);
    }
    dfs(1,0);
    dp(1,0,0);
    for(i=l;i<=r;i++)
        printf("%lld ",f[1][i]);
    return 0;
}

```

然后怎样优化这个算法呢？我在调试时发现f数组中有很多0值，为什么呢？我们发现，如果f[i]中一个位置非零，则它一定有一个孩子的这个位置上也非零，也就是说，一个点的非零状态数不超过它所有孩子的非零状态数之和，那么我们就可以离散的存下这些状态，然后启发式合并，这样可以做到O(nlogn)，但是如果像上面那样暴力合并的话，复杂度显然是不对的，所以我们还要维护一棵线段树，时间复杂度O(n log^2 n)。

怎么做呢？假设我们要把f[u]合并到f[v]上，那么显然可以枚举f[u]中的每一个值，然后暴力在f[v]的线段树中查前缀和，而对于f[v]中的每一个值，它需要乘以f[u]中的一段前缀和，而这个前缀和只有f[u]的状态数种取值，直接枚举f[u]的一个前缀，在f[v]的线段树中区间乘法即可。

具体的细节可以参考我的代码：(如果我有没讲清楚的地方，可以在评论区中提出或私信我）

```

// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=400007;
const int M=20000007;
const ll mod=998244353;
struct str
{
    int x;
    int y;
    int d;
}p[N];
ll s[N];
int hd[N],pre[N],to[N],num,dep[N],son[N],w[N],n,cnt;
int sum[M],lc[M],rc[M],mul[M],tot,rt[N],sn[N],sz[N];
void adde(int x,int y)
{
    num++;pre[num]=hd[x];hd[x]=num;to[num]=y;
}

void Mul(int k,int d)
{
    mul[k]=1ll*mul[k]*d%mod;
    sum[k]=1ll*sum[k]*d%mod;
}
void pushdown(int k)
{
    if(lc[k])Mul(lc[k],mul[k]);
    if(rc[k])Mul(rc[k],mul[k]);
    mul[k]=1;
}
void add(int &k,int l,int r,int x,int d)
{
    if(!k)k=++tot;
    if(l==r){sum[k]=(sum[k]+d)%mod;return;}
    int mid=l+r>>1;
    if(mul[k]!=1)pushdown(k);
    if(x<=mid)add(lc[k],l,mid,x,d);
    else add(rc[k],mid+1,r,x,d);
    sum[k]=(sum[lc[k]]+sum[rc[k]])%mod;
}
void modify(int k,int l,int r,int x,int y,int d)
{
    if(!k)return;
    if(l>=x&&r<=y)return Mul(k,d);
    int mid=l+r>>1;
    if(mul[k]!=1)pushdown(k);
    if(x<=mid)modify(lc[k],l,mid,x,y,d);
    if(y>mid)modify(rc[k],mid+1,r,x,y,d);
    sum[k]=(sum[lc[k]]+sum[rc[k]])%mod;
}
int query(int k,int l,int r,int x,int y)
{
    if(!k)return 0;
    if(l>=x&&r<=y)return sum[k];
    int mid=l+r>>1,ans=0;
    if(mul[k]!=1)pushdown(k);
    if(x<=mid)ans=(ans+query(lc[k],l,mid,x,y))%mod;
    if(y>mid)ans=(ans+query(rc[k],mid+1,r,x,y))%mod;
    return ans;
}
void visit(int k,int l,int r)
{
    if(!k)return ;
    if(l==r){p[++cnt]={sum[k],0,l};return ;}
    int mid=l+r>>1;
    if(mul[k]!=1)pushdown(k);
    visit(lc[k],l,mid);
    visit(rc[k],mid+1,r);
}

void dfs(int v,int fa)
{
    int i,u;
    dep[v]=dep[fa]+1;s[v]=1;
    sz[v]=0;
    for(i=hd[v];i;i=pre[i])
    {
        u=to[i];
        if(u==fa)continue;
        dfs(u,v);s[v]=s[v]*s[u]%mod;
        if(dep[v]&1){
            if(w[u]>w[son[v]])son[v]=u;
        }else if(!son[v]||w[u]<w[son[v]])son[v]=u;
        if(sz[u]>sz[sn[v]])sn[v]=u;
        sz[v]+=sz[u];
    }
    if(!son[v])w[v]=v,s[v]=2,sz[v]=1;
    else w[v]=w[son[v]];
}
void orun(int a,int b)
{
    cnt=0;
    visit(rt[b],1,n);
    for(int i=1;i<=cnt;i++)
        if(p[i].d<n)p[i].y=query(rt[a],1,n,p[i].d+1,n);
    int sm=0;
    p[0].d=0;
    for(int i=cnt;i>=1;i--)
    {
        sm=(sm+p[i].x)%mod;
        modify(rt[a],1,n,p[i-1].d+1,p[i].d,sm+1);
    }
    for(int i=1;i<=cnt;i++)
        add(rt[a],1,n,p[i].d,1ll*p[i].x*(p[i].y+1)%mod);
}
void andun(int a,int b)
{
    cnt=0;
    int tmp=(sum[rt[a]]+sum[rt[b]])%mod;
    visit(rt[b],1,n);
    for(int i=1;i<=cnt;i++)
        if(p[i].d>1)p[i].y=query(rt[a],1,n,1,p[i].d-1);
    int sm=0;
    p[cnt+1].d=n+1;
    if(p[1].d>1)modify(rt[a],1,n,1,p[1].d-1,0);
    for(int i=1;i<=cnt;i++)
    {
        sm=(sm+p[i].x)%mod;
        modify(rt[a],1,n,p[i].d,p[i+1].d-1,sm);
    }
    for(int i=1;i<=cnt;i++)
        add(rt[a],1,n,p[i].d,1ll*p[i].x*p[i].y%mod);
    add(rt[a],1,n,n,tmp);
}
void dp(int v,int fa,int d)
{
    int i,u;
    if(!son[v])add(rt[v],1,n,max(1,abs(d)),1);
    else if(!d||d>0&&(dep[v]&1)||d<0&&!(dep[v]&1))
    {
        int tar;
        if(d)tar=w[son[v]]+d;
        else tar=dep[v]&1?w[son[v]]+1:w[son[v]]-1;
        u=sn[v];
        if(u==son[v])dp(u,v,d);
        else dp(u,v,tar-w[u]);
        rt[v]=rt[u];
        for(i=hd[v];i;i=pre[i])
        {
            u=to[i];
            if(u==fa||u==sn[v])continue;
            if(u==son[v])dp(u,v,d);
            else dp(u,v,tar-w[u]);
            orun(v,u);
        }
    }
    else
    {
        int tar=w[son[v]]+d;
        ll ml=1;
        u=sn[v];
        if(d<0&&w[u]<=tar||d>0&&w[u]>=tar)
            ml=ml*s[u]%mod;
        else
        {
            dp(u,v,tar-w[u]);
            rt[v]=rt[u];
        }
        for(i=hd[v];i;i=pre[i])
        {
            u=to[i];
            if(u==fa||u==sn[v])continue;
            if(d<0&&w[u]<=tar||d>0&&w[u]>=tar)
                ml=ml*s[u]%mod;
            else
            {
                dp(u,v,tar-w[u]);
                if(!rt[v])rt[v]=rt[u];
                else andun(v,u);
            }
        }
        modify(rt[v],1,n,1,n,ml);
        add(rt[v],1,n,n,ml-1);
    }
}
int main()
{
    int i,x,y,l,r;
    scanf("%d%d%d",&n,&l,&r);
    for(i=1;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        adde(x,y),adde(y,x);
    }
    dfs(1,0);
    dp(1,0,0);
    for(i=l;i<=r;i++)
        printf("%d ",query(rt[1],1,n,i,i));
    return 0;
}

```
唉，写200多行还想了我好久，看你们随便写个一百行的动态dp还跑得比我快，真的心好累。。。

---

## 作者：linjingxiang (赞：6)

### Description

给定一颗以 $1$ 为根的有根树，首先按照 $\operatorname{minimax}$ 搜索的方式（即：根节点深度定为 $1$；叶子节点的权值为节点编号，非叶子节点的权值按照“深度为奇数在儿子中取 $\max$，深度为偶数在儿子中取 $\min$”的规则自下而上递归求得）找到根节点的权值 $w$。

定义一个叶子节点的非空子集 $S$ 的合法方案为所有“ **通过改变 $S$ 中的点的点权使得最终的 $\operatorname{minimax}$ 搜索结果不为 $w$ 的** ”方案。

而一个合法方案的代价为“**对每个点的修改量取 $\max$ 后的结果**”。

定义一个叶子节点的非空子集 $S$ 的代价即为它的**所有合法方案的代价最小值**。

对于给定的区间中的每一个数，求有多少个集合的代价为这个数。

答案对 $998244353$ 取模。

### Solution

#### Sub1 50分

首先想到模拟一遍没有修改的情况，找到 $w$ 的位置。这个按照 $\operatorname{minimax}$ 搜索的方式 dfs 一遍即可。

拿到 $w$ 后，我们来考虑什么样的集合 $S$ 能够改变最终的答案。可以发现有两种：

- 集合包含 $w$。由于树的节点编号唯一，此时使用 $1$ 的代价把 $w$ 修改掉必然可以使最终结果不为 $w$。
- 集合不包含 $w$。那么便需要保证 $w$ 在按照 $\operatorname{minimax}$ 搜索的方式向上跳的过程中在某一步被代替掉。我们把从 $w$ 到 $1$ 的路径叫做**特殊路径**。

第一种情况是很好解决的。我们主要关心第二种情况的统计方案。最终答案改变，当且仅当连接到特殊路径的全部子树中存在至少一个子树在那一层的选取变得比 $w$ 优。那么就出现了两种子树，一种要求最终的根节点权值变得比 $w$ 大，另一种要求最终的根节点权值变得比 $w$ 小。

我们尝试先求出一颗连接到特殊路径的子树的方案数，再尝试子树之间的方案数合并。

那么不妨先考虑要求根节点权值变得比 $w$ 大的情况，另一种情况是类似的。不难发现，我们关心的仅仅是“比 $w$ 大”，因此考虑 dp ，设 $dp[u][i]$ 表示在以 $u$ 为根节点的子树中，最优情况下恰好使用 $i$ 为代价能够使得 $u$ 的权值比 $w$ 大。

考虑转移：

- 边界条件，即点 $u$ 为叶子节点：

   1. 若 $u>w$，则已经达到标准，不管选不选 $u$ 都无需耗费任何代价。因此令 $dp[u][0]=2$。

  
   2. 若 $u\leq w$，则当前的 $u$ 不合法，如果选 $u$ 则需耗费 $w+1-u$ 的代价让它变得合法，如果不选 $u$ 则一定不合法，耗费 $n$ 的代价。因此令 $dp[u][w+1-u]=dp[u][n]=1$。

- 对于非叶子节点：

   1. 若这一层要求取 $\max$，则 $u$ 只要有一个儿子权值大于 $w$ 即可。我们将 $u$ 的儿子的 dp 数组两两合并。即：
 
  $$dp[u][i]=dp'[u][i]\times\sum^n_{j=i+1} dp[v][j]+dp[v][i]\times\sum^n_{j=i+1} dp'[u][j]+dp'[u][i]\times dp[v][i]$$

  表示：“一个代价比 $i$ 大一个代价为 $i$ 的方案”与“两个代价均为 $i$ 的方案”。

   2. 若这一层要求取 $\max$，则要求 $u$ 全部儿子权值大于 $w$。同理有：
 
  $$dp[u][i]=dp'[u][i]\times\sum^{i-1}_{j=0} dp[v][j]+dp[v][i]\times\sum^{i-1}_{j=0} dp'[u][j]+dp'[u][i]\times dp[v][i]$$

  表示：“一个代价比 $i$ 小一个代价为 $i$ 的方案”与“两个代价均为 $i$ 的方案”。

这样就可以拿到每一颗连在特殊路径上的子树的全部有效信息了。

接下来考虑合并。不难发现“所有连在特殊路径上的子树只需要有一个满足”这一要求正相当于非叶子节点的第一种转移，即取后缀和。

至此可以做到时间复杂度 $O(n^2)$ 即 $50pt$。

#### Sub1 50分

前置知识：线段树合并。[模板](https://www.luogu.com.cn/problem/P4556)

由于每个叶子节点会使所在子树最多增加 $2$ 个 dp 数组的不为 $0$ 的位置，对于任何一棵子树，有值的位置为 $O(子树大小)$，那么用线段树合并维护 dp 数组即可。

这道题算是比较难的线段树合并。线段树合并的关键在于：合并的过程中还要维护当前位置前缀/后缀的一些信息并且做到“边合并边修改”。

对于这题，需要实现两种合并，分别是前缀求和相乘和后缀求和相乘。

还需要注意的是，虽然最终方案不包括空集，但是过程中的每一棵子树都应该包含空集，才能转移。最后在 $dp[1][n]$ 减去 $1$ 即可。

详细操作过程可以看代码。

最终时间复杂度： $O(n log n)$。

```
#include<bits/stdc++.h>
#define mid (l+r>>1)
#define pb push_back
#define N 200005
#define mod 998244353
using namespace std;
int n,ql,qr,f[N],dep[N],w,sum[N<<6],tag[N<<6],ls[N<<6],rs[N<<6],tot,rt[N];
vector<int>t[N];
inline int mo(int x){return x<mod?x:x-mod;}
#define getc (cs==ct&&(ct=(cs=cb)+fread(cb,1,1<<15,stdin),cs==ct)?0:*cs++)
char cb[1<<15],*cs,*ct;
inline void read(int &num){
    char ch;while(!isdigit(ch=getc));
    for(num=ch-'0';isdigit(ch=getc);num=num*10+ch-'0');
}
inline void wq(const int& x) {
    int t=x;static char _wq_buffer[39];int bp=-1;
    if(!t)return putchar('0'),void();
    while(t)_wq_buffer[++bp]=t%10+'0',t/=10;
    for(int i=bp;i>=0;i--)putchar(_wq_buffer[i]);
}
inline int dfs(int u,int fa){
	f[u]=fa,dep[u]=dep[fa]+1;
	int res=t[u].size()==1?u:dep[u]&1?1:n;
	for(int v:t[u])if(v!=fa)res=dep[u]&1?max(res,dfs(v,u)):min(res,dfs(v,u));
	return res;
}
inline void F(int p,int k){sum[p]=1ll*sum[p]*k%mod,tag[p]=1ll*tag[p]*k%mod;}
inline void push_down(int p){
	if(tag[p]==1)return;
	if(ls[p])F(ls[p],tag[p]);
	if(rs[p])F(rs[p],tag[p]);
	tag[p]=1;
}
inline void push_up(int p){sum[p]=mo(sum[ls[p]]+sum[rs[p]]);}
inline void addsum(int &p,int l,int r,int x,int k){
	if(!p)p=++tot,tag[p]=1;
	if(l==r)return sum[p]=mo(sum[p]+k),void();
	push_down(p);
	if(x<=mid)addsum(ls[p],l,mid,x,k);
	if(x>mid)addsum(rs[p],mid+1,r,x,k);
	push_up(p);
}
inline void as(int u,int x,int k){addsum(rt[u],0,n,x,k);}
inline int mg1(int x,int y,int l,int r,int s1,int s2){//all<->left
	if(!x||!y)return (!x&&!y)?0:!x?(F(y,s1),y):(F(x,s2),x);
	if(l==r)return sum[x]=(1ll*sum[x]*s2+1ll*sum[y]*s1+1ll*sum[x]*sum[y])%mod,x;
	push_down(x),push_down(y);
	rs[x]=mg1(rs[x],rs[y],mid+1,r,mo(s1+sum[ls[x]]),mo(s2+sum[ls[y]]));
	ls[x]=mg1(ls[x],ls[y],l,mid,s1,s2);
	return push_up(x),x;
}
inline int mg2(int x,int y,int l,int r,int s1,int s2){//any<->right
	if(!x||!y)return (!x&&!y)?0:!x?(F(y,s1),y):(F(x,s2),x);
	if(l==r)return sum[x]=(1ll*sum[x]*s2+1ll*sum[y]*s1+1ll*sum[x]*sum[y])%mod,x;
	push_down(x),push_down(y);
	ls[x]=mg2(ls[x],ls[y],l,mid,mo(s1+sum[rs[x]]),mo(s2+sum[rs[y]]));
	rs[x]=mg2(rs[x],rs[y],mid+1,r,s1,s2);
	return push_up(x),x;
}
inline void out(int p,int l,int r){
	if(l==r)return wq(sum[p]-(l==n)),putchar(' '),void();
	push_down(p);
	if(ql<=mid)out(ls[p],l,mid);
	if(qr>mid)out(rs[p],mid+1,r);
}
inline void dfs2(int u,bool op){//op==1 means <w   op==0 means >w
	if(t[u].size()!=1)op^(dep[u]&1)?as(u,n,1):as(u,0,1);
	else op?(u<w?as(u,0,2):(as(u,n,1),as(u,u-w+1,1))):(u>w?as(u,0,2):(as(u,n,1),as(u,w+1-u,1)));
	for(int v:t[u])if(v!=f[u])dfs2(v,op),rt[u]=op^(dep[u]&1)?mg2(rt[u],rt[v],0,n,0,0):mg1(rt[u],rt[v],0,n,0,0);
}
int main(){
	read(n),read(ql),read(qr);
	for(int i=1,u,v;i<n;i++)read(u),read(v),t[u].pb(v),t[v].pb(u);
	w=dfs(1,0),as(0,1,1),as(0,n,1);
	for(int u=w;u!=1;u=f[u])for(int v:t[f[u]])if(v!=f[f[u]]&&v!=u)dfs2(v,dep[u]&1),rt[0]=mg2(rt[0],rt[v],0,n,0,0);
	out(rt[0],0,n);
}
```

---

## 作者：xyz32768 (赞：6)

- [题目传送门](https://loj.ac/problem/3044)

- 容易想到一种暴力 DP：先转化成对于每个 $k$ 求出 $\max_{i\in S}|i-w_i|\le k$ 的方案数，最后差分

- 然后问题转化成每个叶子的权值有个取值区间，注意这时我们可以把每个点的权值分成 $<W,=W,>W$（看作 $0,1,2$ ）三类处理，然后 DP $f[u][0/1/2]$

- 然后你会很快发现这么做不行，因为选取某些叶子集合时，根节点的权值可以小于 $W$ 也可以大于 $W$ ，直接用 $2^m-1$ 减掉 $f[u][0]+f[u][2]$ 无法得到正确结果

- 于是我们尝试考虑怎样才能在 $<W$ 和 $>W$ 这两个条件中去掉一个

- 考虑权值为 $W$ 的叶子到根的一条链

- 容易发现根节点的权值会被改变，当且仅当这条链上存在一个点会被改变

- 设这条链上有一个深度为奇数的点 $u$ （偶数同理），考虑把链上所有的边都删掉之后 $u$ 所在的连通块

- 易得在原树上 $u$ 的权值会被改，当且仅当删边之后**就 $u$ 所在的连通块**，能让 $u$ 的权值大于 $W$

- 特殊地，如果 $u$ 是叶子那么 $u$ 的权值会被改当且仅当 $u$ 在选定集合内且 $k>0$

- 这样我们就实现了在 $<W$ 和 $>W$ 这两个条件中去掉一个

- 我们有了一个 DP：$f[u]$ 表示 $u$ 的子树内的叶子节点有多少个子集能让 $u$ 的权值大于 $W$

- 如果 $u$ 的深度为奇数（$cnt_u$ 为 $u$ 的子树内叶子个数）：

- $$f[u]=2^{cnt_u}-\prod_{v\in son[u]}(2^{cnt_v}-f[v])$$

- 否则：

- $$f[u]=\prod_{v\in son[u]}f[v]$$

- 把所有连通块的 DP 结果用 $2^{cnt}$ 减掉后乘起来，即为根节点权值**不会被改变**的方案数

- 对每个 $k$ 进行 DP 的复杂度为 $O(n^2)$

- 考虑如何优化。我们注意到这个 DP 的转移和 $k$ 无关，只有初始值（叶子）和 $k$ 有关

- 而如果一个点 $u$ 所在的连通块根在原树中的深度为奇数，那么点 $u$ 的初值应该为：

- $$f[u]=[u>W]+[u+k>W]$$

- 注意到当 $k$ 不断加一的时候， $[u+k>W]$ 只会改变一次

- 于是从小到大枚举 $k$ 后动态 DP 即可

- 注意由于 $f[u]$ 可以为 $0$ ，所以往上更新 DP 值时不能把 $f[fa[u]]$ 直接除以 $f[u]$ ，而需要对每个点维护一个变量表示子节点的 DP 值中有多少个 $0$ ，另一个变量表示子节点不为 $0$ 的 DP 值之积

- $O(n\log^2n)$

## Code
```cpp
#include <bits/stdc++.h>
#define p2 p << 1
#define p3 p << 1 | 1

template <class T>
inline void read(T &res)
{
	res = 0; bool bo = 0; char c;
	while (((c = getchar()) < '0' || c > '9') && c != '-');
	if (c == '-') bo = 1; else res = c - 48;
	while ((c = getchar()) >= '0' && c <= '9')
		res = (res << 3) + (res << 1) + (c - 48);
	if (bo) res = ~res + 1;
}

template <class T>
inline T Min(const T &a, const T &b) {return a < b ? a : b;}

template <class T>
inline T Max(const T &a, const T &b) {return a > b ? a : b;}

const int N = 2e5 + 5, M = N << 1, L = M << 1, rqy = 998244353;

int n, l, r, dep[N], ecnt, nxt[M], adj[N], go[M], val[N], ans[N], f[N], cnt[N],
fa[N], sze[N], son[N], top[N], pos[N], idx[N], bot[N], QAQ, pw[N], re[N], c0[N],
rea = 1, cnt0;
bool lea[N], bel[N];

int qpow(int a, int b)
{
	int res = 1;
	while (b)
	{
		if (b & 1) res = 1ll * res * a % rqy;
		a = 1ll * a * a % rqy;
		b >>= 1;
	}
	return res;
}

struct modi
{
	int a, b;
	
	friend inline modi operator * (modi x, modi y)
	{
		return (modi) {(int) (1ll * x.a * y.a % rqy),
			(int) ((1ll * x.a * y.b + x.b) % rqy)};
	}
	
	friend inline int operator * (modi x, int y)
	{
		return (1ll * x.a * y + x.b) % rqy;
	}
} g[N], gp[L];

void add_edge(int u, int v)
{
	nxt[++ecnt] = adj[u]; adj[u] = ecnt; go[ecnt] = v;
	nxt[++ecnt] = adj[v]; adj[v] = ecnt; go[ecnt] = u;
}

void dfs(int u, int fu)
{
	dep[u] = dep[fu] + 1;
	val[u] = dep[u] & 1 ? 1 : n;
	bool is = 1;
	for (int e = adj[u], v; e; e = nxt[e])
		if ((v = go[e]) != fu)
		{
			dfs(v, u); is = 0;
			if (dep[u] & 1) val[u] = Max(val[u], val[v]);
			else val[u] = Min(val[u], val[v]);
		}
	if (is) lea[val[u] = u] = 1, ans[0] = (ans[0] + ans[0]) % rqy;
}

void dfs1(int u, int fu, bool op)
{
	fa[u] = fu; sze[u] = 1; bel[u] = op; cnt[u] = lea[u];
	for (int e = adj[u], v; e; e = nxt[e])
		if ((v = go[e]) != fu && val[v] != val[1])
		{
			dfs1(v, u, op);
			sze[u] += sze[v]; cnt[u] += cnt[v];
			if (sze[v] > sze[son[u]]) son[u] = v;
		}
	f[u] = (op ? val[u] > val[1] : val[u] < val[1]) ? pw[cnt[u]] : 0;
	g[u].a = re[u] = 1;
	if ((dep[u] & 1) ^ op)
	{
		for (int e = adj[u], v; e; e = nxt[e])
			if ((v = go[e]) != fu && val[v] != val[1] && v != son[u])
			{
				g[u].a = 1ll * g[u].a * f[v] % rqy;
				if (f[v]) re[u] = 1ll * re[u] * f[v] % rqy; else c0[u]++;
			}
	}
	else
	{
		for (int e = adj[u], v; e; e = nxt[e])
			if ((v = go[e]) != fu && val[v] != val[1] && v != son[u])
			{
				int tmp = (pw[cnt[v]] - f[v] + rqy) % rqy;
				g[u].a = 1ll * g[u].a * tmp % rqy;
				if (tmp) re[u] = 1ll * re[u] * tmp % rqy; else c0[u]++;
			}
		g[u].b = (pw[cnt[u]] - 1ll * g[u].a * pw[cnt[son[u]]] % rqy + rqy) % rqy;
	}
	bot[u] = son[u] ? bot[son[u]] : u;
}

void dfs2(int u, int fu)
{
	if (son[u])
	{
		top[son[u]] = top[u];
		idx[pos[son[u]] = ++QAQ] = son[u];
		dfs2(son[u], u);
	}
	for (int e = adj[u], v; e; e = nxt[e])
		if ((v = go[e]) != fu && v != son[u] && val[v] != val[1])
			top[v] = v, idx[pos[v] = ++QAQ] = v, dfs2(v, u);
}

void build(int l, int r, int p)
{
	if (l == r) return (void) (gp[p] = g[idx[l]]);
	int mid = l + r >> 1;
	build(l, mid, p2); build(mid + 1, r, p3);
	gp[p] = gp[p2] * gp[p3];
}

void change(int l, int r, int pos, modi v, int p)
{
	if (l == r) return (void) (gp[p] = v);
	int mid = l + r >> 1;
	if (pos <= mid) change(l, mid, pos, v, p2);
	else change(mid + 1, r, pos, v, p3);
	gp[p] = gp[p2] * gp[p3];
}

modi ask(int l, int r, int s, int e, int p)
{
	if (e < l || s > r) return (modi) {1, 0};
	if (s <= l && r <= e) return gp[p];
	int mid = l + r >> 1;
	return ask(l, mid, s, e, p2) * ask(mid + 1, r, s, e, p3);
}

void modify(int u, int x)
{
	bool fi = 1; int of;
	while (1)
	{
		int v = top[u], w = fa[v], rf = f[v], nf;
		if (fi) fi = 0, f[u] = x; nf = f[v];
		if (v != bot[u]) nf = f[v] =
			ask(1, n, pos[v], pos[bot[u]] - 1, 1) * f[bot[u]] % rqy;
		if (!w) {of = rf; u = v; break;}
		if ((dep[v] & 1) ^ bel[v]) rf = (pw[cnt[v]] - rf + rqy) % rqy,
			nf = (pw[cnt[v]] - nf + rqy) % rqy;
		if (!rf) c0[w]--; else re[w] = 1ll * re[w] * qpow(rf, rqy - 2) % rqy;
		if (!nf) c0[w]++; else re[w] = 1ll * re[w] * nf % rqy;
		g[w].a = c0[w] ? 0 : re[w];
		g[w].b = (dep[w] & 1) ^ bel[w] ? 0 : (pw[cnt[w]] -
			1ll * g[w].a * pw[cnt[son[w]]] % rqy + rqy) % rqy;
		change(1, n, pos[w], g[w], 1);
		u = w;
	}
	if (of == pw[cnt[u]]) cnt0--; else rea = 1ll * rea *
		qpow(pw[cnt[u]] - of + rqy, rqy - 2) % rqy;
	if (f[u] == pw[cnt[u]]) cnt0++;
		else rea = 1ll * rea * (pw[cnt[u]] - f[u] + rqy) % rqy;
}

int main()
{
	int x, y;
	read(n); read(l); read(r);
	for (int i = 1; i < n; i++)
		read(x), read(y), add_edge(x, y);
	ans[0] = pw[0] = ans[n] = 1; dfs(1, 0);
	for (int i = 1; i <= n; i++) pw[i] = (pw[i - 1] + pw[i - 1]) % rqy;
	rea = 499122177ll * ans[0] % rqy;
	for (int u = 1; u <= n; u++)
	{
		if (val[u] != val[1] || u == val[1]) continue;
		dfs1(u, 0, dep[u] & 1);
		if (!cnt[u] || lea[u]) continue;
		idx[pos[u] = ++QAQ] = top[u] = u;
		dfs2(u, 0);
	}
	build(1, n, 1);
	for (int i = 1; i < n; i++)
	{
		if (i > 1 && val[1] >= i && lea[val[1] - i + 1] && bel[val[1] - i + 1])
			modify(val[1] - i + 1, 1);
		if (i > 1 && val[1] <= n - i + 1 && lea[val[1] + i - 1]
			&& !bel[val[1] + i - 1]) modify(val[1] + i - 1, 1);
		ans[i] = cnt0 ? 0 : rea;
	}
	for (int i = l; i <= r; i++) printf("%d ", (ans[i - 1] - ans[i] + rqy) % rqy);
	return puts(""), 0;
}
```

---

## 作者：ljc1301 (赞：5)

说个只会平衡树就能做的方法。$\color{white}\text{是我这个蒟蒻自己想出来的}$

一个比较显然的结论是，只要对编号为$W$的节点改动1，根节点的权值就会发生变化。（显然没有权值为$W$的节点了，根节点不可能取到$W$。）所以只要$W\in S$，则$w(S)=1$，对答案的贡献是$2^{m-1}$，其中$m$为叶节点的个数。

下面讨论不选$W$的情况。（下面是可以参考的思维过程，觉得我没讲清楚，或觉得不屑于看的可以跳。）先考虑一个十分naive的dp。记$f[u][l][r][k]$表示要使$u$节点，满足操作后的根节点的权值$\in [l,r]$且$w(S)\leqslant k$。~~似乎复杂度要爆炸……不考虑可行性……~~我们要的是$l<W$或$r>W$时$f[1][l][r][k]$的值。

考虑怎么优化这个~~不可行的~~dp。我们发现，考虑转移，$u$的$l$会是子节点里所有的$l$满足条件时转移过来的，也就是说，当一个节点减更多的权值时，$l$变小，父亲的$l$也可能会小，以此类推。加更多的权值同理。所以，**我们每次尽量多的减少或增加就有可能改变根节点的权值，减或加多了权值不会变回去。**

但我们要求的是$l<W$或$r>W$时$f[1][l][r][k]$的值。如果把所有$<W$的数看成$-1$，$=W$的数看成$0$，$>W$的数看成$1$，若把这种映射看成$f(x)$，则$\min(f(a),f(b))=f(\min(a,b))$，对于$\max$也成立。所以，要把根节点改成$-1$或$1$，得把叶节点的一些都从$-1$改成$1$，或都从$1$改成$-1$，前者对应了把根节点的权值变小，后者对应了变大。而当然是改成$W\pm1$，这样$w$小。

再考虑另一个方法。记$f[u][k]$表示满足$S\subseteq \{x|x\text{在}u\text{的子树内}\land x\ne W\}$的所有S中，把$S$中若干$<W$的权值改大成$W+1$，能使得根节点的权值变大的个数。同理记$g[u][k]$表示满足$S\subseteq \{x|x\text{在}u\text{的子树内}\land x\ne W\}$的所有S中，把$S$中若干$>W$的权值改小成$W-1$，能使得根节点的权值变小的个数。

是不是感觉一下子好做了很多？~~但是时间复杂度还是不对……还是不可做啊……~~

我们把转移的式子列出来（为了方便只列$f$的，$g$的同理）：

1. 当$u$为叶节点时，若$u=W$，则$f[u]$全为0（规定不能选$W$，不可能把它变大）；若$u<W$，则$f[u][W+1-u]=1$（要用$W+1-u$的代价，而且必须有$S=\{u\}$；若$u>W$，则$f[u][0]=2$（不用代价，而且$S=\varnothing$或$S=\{u\}$）。
2. 若$u$的权值$>W$，则$S\subseteq \{x|x\text{在}u\text{的子树内}\land x\ne W\}$，所以$f[u][0]=2^{\{x|x\text{在}u\text{的子树内}\land x\ne W\}}$
3. 当$u$的权值是它所有子节点的权值最大值时，要满足有一个子节点的权值$>S$，$f[u][k]=\sum\limits_{a_{1\dots cnt[u]}\land \max\{a_i\}=k}\prod f[son[u][i]][a[i]]$，其中$cnt[u]$表示$u$的子节点个数，$son[u][i]$表示$u$的第$i$个子节点。
4. 当$u$的权值是它所有子节点的权值最小值时，要满足所有子节点的权值$>S$，$f[u][k]=\sum\limits_{a_{1\dots cnt[u]}\land \min\{a_i\}=k}\prod f[son[u][i]][a[i]]$，其中$cnt[u]$表示$u$的子节点个数，$son[u][i]$表示$u$的第$i$个子节点。

这样说似乎太抽象了……~~时间复杂度还不对……~~

怎么处理第3、4个转移式？发现似乎可以每次合并前两个$f$、$g$的值，再和第3个合并……（感性理解一下……）那么就可以写成下面这个式子（记当前要加入的子节点是$v$）：

3. 当$u$的权值是它所有子节点的权值最大值时，$f_{new}[u][k]=f[u][k]\sum\limits_{j\leqslant k}f[v][j]+f[v][k]\sum\limits_{j<k}f[u][j]$，前者是最大值取前面一些节点的情况，后者是取$v$的情况。
4. 当$u$的权值是它所有子节点的权值最小值时，$f_{new}[u][k]=f[u][k]\sum\limits_{j\geqslant k}f[v][j]+f[v][k]\sum\limits_{j>k}f[u][j]$

可以发现，$f[u][k]\ne 0$的数量不超过子树中不等于$0$的数量，其实是不超过子树中叶节点的数量。可以平衡树启发式合并！

具体来说，当两个序列$f[u]$、$f[v]$合并时，不妨令$f[u]$中不等于$0$的数量小于$f[v]$中的（否则换两个平衡树的根）。则从小到大枚举使$f[v][k]\ne 0$的$k$，把$f[u]$分成若干段，可以发现每一段中都乘同一个$f[v]$的前缀或后缀的和，再合并到$f_{new}[u]$；每一个$f[v]$也是乘上一个$f[u]$的前缀或后缀的和，再合并到$f_{new}[u]$。（讲的有点抽象，可以看代码。）

然后就能算出$f[1]$和$g[1]$了。

接下来考虑怎么统计答案。~~刚开始我这里想错了……~~

我们要先把$f[1]$中的所有数除以$2^{\text{编号}>W\text{的叶节点个数}}$，因为我把$>W$的数看作能选和不能选，选不选对对于$f$来说的权值没有影响。当然也可以强制不选，那第一个转移中$u>W$时$f[u][0]=1$，第二个转移中$f[u][0]=2^{\{x|x\text{在}u\text{的子树内}\land x<W\}}$，但我比较懒，就用了前一种方法。

先说一下，为什么把不能使根结点值改变的集合的稳定度当成$n$，其实是因为叶结点的编号一定在$[2,n]$内，改动$n-1$就能保证比任意数大。$w(S)=n$的答案可以通过把所有方法数$2^n-1$减去前面的所有答案。

而我们知道，根据开头的结论，只要$W\in S$，则$w(S)=1$，而且其他情况至少要改2的权值，所以对于$W\notin S$，$w(S)\geqslant2$。所以我们知道，$w(S)=1$的答案为$2^{n-1}$。

其次，对于$W\notin S$，我们可以把$S$看成$>W$和$<W$两部分，$w(S)$是两部分的$\min$。下面的统计就很类似了。记$cnt_1$为叶节点中编号$>W$的数量，$cnt_2$为叶节点中编号$<W$的数量。答案就是$ans_i=f[1][i]\left(2^{cnt_1}-\sum\limits_{j=i}^ng[1][j]\right)+g[1][i]\left(2^{cnt_2}-\sum\limits_{j=i+1}^nf[1][j]\right)$。

时间复杂度$O(n\log^2n)$，常数很小。

细节参考代码（感觉没啥细节，但我不知道为什么调了两三小时）（有些大于和大于等于可以交换的，可能会和上面的描述不太一样）：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=3000005;
const int maxnode=maxn;
const int kcz=998244353;
const int inv2=499122177;
struct node { int pri,sz,val,lc,rc; ll x,s,lazy; } p[maxnode];
int n,l,r,m,a[maxn],he[maxn],to[maxn<<1],ne[maxn<<1],tot,fa[maxn];
int w[maxn],cnt[maxn],rt[maxn],out[maxn],sz;
ll pow2[maxn],ans[maxn],ans1[maxn],ans2[maxn];
inline int read()
{
    int res=0,ch;
    bool f=0;
    for(ch=getchar();ch<'0' || ch>'9';ch=getchar()) f=(ch=='-');
    for(;'0'<=ch && ch<='9';ch=getchar()) res=res*10+(ch-'0');
    return f?-res:res;
}
int sta[30],top;
inline void write(long long x)
{
    if(!x) { putchar('0'); return; }
    if(x<0) putchar('-'),x=-x;
    top=-1;
    while(x) sta[++top]=x%10,x/=10;
    while(~top) putchar(sta[top--]^'0');
}
inline void add_edge(int u,int v) { to[tot]=v,ne[tot]=he[u],he[u]=tot++; }
inline int newnode(int x,ll s)
{
    ++tot;
    p[tot].val=x,p[tot].sz=1,p[tot].pri=rand();
    p[tot].x=p[tot].s=s,p[tot].lazy=1,p[tot].lc=p[tot].rc=0;
    return tot;
}
inline void pushup(int rt) { if(rt) p[rt].s=(p[p[rt].lc].s+p[p[rt].rc].s+p[rt].x)%kcz,p[rt].sz=p[p[rt].lc].sz+p[p[rt].rc].sz+1; }
inline void push(int rt,ll x) { if(rt) (p[rt].x*=x)%=kcz,(p[rt].s*=x)%=kcz,(p[rt].lazy*=x)%=kcz; }
inline void pushdown(int rt) { if(p[rt].lazy!=1) push(p[rt].lc,p[rt].lazy),push(p[rt].rc,p[rt].lazy),p[rt].lazy=1; }
void split(int rt,int &l,int &r,int x)
{
    if(!rt) { l=r=0; return; }
    pushdown(rt);
    if(p[rt].val<=x) l=rt,split(p[rt].rc,p[l].rc,r,x),pushup(l);
    else r=rt,split(p[rt].lc,l,p[r].lc,x),pushup(r);
}
void merge(int &rt,int l,int r)
{
    if(!l || !r) { rt=l|r; return; }
    if(p[l].pri>p[r].pri) pushdown(l),rt=l,merge(p[rt].rc,p[l].rc,r);
    else pushdown(r),rt=r,merge(p[rt].lc,l,p[r].lc);
    pushup(rt);
}
void dfs(int u,bool ismax)
{
    int i;
    w[u]=ismax?0x80000000:0x7fffffff,cnt[u]=0;
    for(i=he[u];~i;i=ne[i])
        if(to[i]!=fa[u])
        {
            fa[to[i]]=u;
            dfs(to[i],!ismax);
            cnt[u]+=cnt[to[i]];
            w[u]=ismax?max(w[u],w[to[i]]):min(w[u],w[to[i]]);
        }
    if(w[u]==(ismax?0x80000000:0x7fffffff)) w[u]=u,m++,cnt[u]++;
}
void print(int u)
{
    if(!u) return;
    pushdown(u);
    print(p[u].lc);
    out[sz++]=u;
    print(p[u].rc);
}
void solve(int u,bool ismax,bool isg)
{
    if(w[u]==u)
        if(w[u]==w[1]) rt[u]=0;
        else if((w[u]>w[1])^(!isg)) rt[u]=newnode(0,2);
        else rt[u]=newnode(abs(w[1]-w[u])+1,1);
    else if((w[u]>w[1])^(!isg) && w[u]!=w[1]) rt[u]=newnode(0,pow2[cnt[u]]);
    else
    {
        int i,sz1=0,sz2,j,t,a;
        ll sum1,sum2;
        bool flag=true;
        rt[u]=0;
        for(i=he[u];~i;i=ne[i])
            if(to[i]!=fa[u])
            {
                solve(to[i],!ismax,isg);
                sz2=cnt[to[i]];
                if(flag) { rt[u]=rt[to[i]]; sz1+=sz2; flag=false; continue; }
                if(p[rt[u]].sz<p[rt[to[i]]].sz)
                    swap(rt[u],rt[to[i]]),swap(sz1,sz2);
                sum1=0,sum2=0;
                sz=0,print(rt[to[i]]);
                for(j=0;j<sz;j++) p[out[j]].lc=p[out[j]].rc=0,p[out[j]].lazy=1,pushup(out[j]);
                t=0;
                for(j=0;j<sz;j++)
                {
                    split(rt[u],a,rt[u],p[out[j]].val);
                    (sum1+=p[a].s)%=kcz;
                    if(ismax^(!isg)) push(a,(pow2[sz2]+kcz-sum2)%kcz),(sum2+=p[out[j]].x)%=kcz,push(out[j],(pow2[sz1]+kcz-sum1)%kcz);
                    else push(a,sum2),(sum2+=p[out[j]].x)%=kcz,push(out[j],sum1);
                    if(p[a].s) merge(t,t,a);
                    if(p[out[j]].s)
                    { // 这里可以直接merge
                        if(t && !p[t].val && !p[out[j]].val) (p[t].x+=p[out[j]].x)%=kcz,pushup(t);
                        else merge(t,t,out[j]);
                    }
                }
                if(ismax^(!isg)) push(rt[u],(pow2[sz2]+kcz-sum2)%kcz);
                else push(rt[u],sum2);
                if(p[rt[u]].s) merge(rt[u],t,rt[u]); else rt[u]=t;
                sz1+=sz2;
            }
    }
}
int main()
{
    int i,u,v,cnt1,cnt2;
    ll t,s1,s2;
    n=read(),l=read(),r=read();
    for(tot=0,i=1;i<=n;i++) he[i]=-1;
    for(i=1;i<n;i++) u=read(),v=read(),add_edge(u,v),add_edge(v,u);
    m=0,fa[1]=0,dfs(1,1);
    for(i=w[1];i;i=fa[i]) cnt[i]--;
    for(i=1,pow2[0]=1;i<=m;i++) pow2[i]=pow2[i-1]*2%kcz;
    for(i=2;i<=n;i++) ans[i]=ans1[i]=ans2[i]=0;
    p[0].s=0,p[0].sz=0;
    tot=0,solve(1,1,1),sz=0,print(rt[1]);
    for(i=w[1]+1,cnt1=0,t=1;i<=n;i++) if(w[i]==i) cnt1++,(t*=inv2)%=kcz;
    for(i=0;i<sz;i++) ans1[p[out[i]].val]=p[out[i]].x*t%kcz;

    tot=0,solve(1,1,0),sz=0,print(rt[1]);
    for(i=1,cnt2=0,t=1;i<w[1];i++) if(w[i]==i) cnt2++,(t*=inv2)%=kcz;
    for(i=0;i<sz;i++) ans2[p[out[i]].val]=p[out[i]].x*t%kcz;
    
    ans[1]=pow2[m-1];
    s1=pow2[cnt2],s2=pow2[cnt1];
    for(i=2;i<n;i++)
    {
        s1=(s1+kcz-ans1[i])%kcz;
        ans[i]=(s1*ans2[i]+s2*ans1[i])%kcz;
        s2=(s2+kcz-ans2[i])%kcz;
    }
    for(i=1;i<n;i++) (ans[n]+=ans[i])%=kcz;
    ans[n]=(pow2[m]-1-ans[n]+kcz)%kcz;
    for(i=l;i<=r;i++) write(ans[i]),putchar(' ');
    putchar('\n');
    return 0;
}
```

---

## 作者：xcyyyyyy (赞：2)

一个 $O(n\log n)$ 的做法，单纯的线段树合并，思维代码都很简单。

考虑先计算出最后的值 $x$，若 $S$ 包含了 $x$，则 $w(S)=1$。我们考虑 $S$ 不包含 $x$ 的情况。

考虑将 $x$ 到 1 号节点的路径剖出来，这个路径将整个树分成了若干个小树。对应的，一个集合 $S$ 就被分到了若干颗树上。

若最后 $1$ 号节点的值不同，那么 $x$ 的值需要在某一点的时候被替换掉。若该层为 $\max$，则需要满足其对应的小数中有一个大于 $x$，反之小于 $x$，我们称这个要求为“小树的要求”。设 $S=\cup T_i$，若 $w(T_i)$ 表示满足对应小树的要求所需要的最少的能量，那么明显 $w(S)=\min w(T_i)$。

考虑一颗小树，我们计算一个序列 $a_i$，表示 $w(S)=i$ 的 $S$ 的数量。设该小树的根是 $rt$，父亲是 $u$，同时父亲是 $\min$ 类型。当然父亲是 $\max$ 同理。

此时，对于 $rt$ 来说，$S$ 又被分到了若干个子树中，设他们为 $T_i$。由于 $rt$ 的类型一定是 $\max$，所以要求所有子树最后的值都小于 $x$，所以 $w(S)=\max w(T_i)$。

对于 $rt$ 的儿子 $u$，由于 $u$ 的类型一定是 $\min$，所以只要求某一个儿子的值小于 $x$，所以 $w(S)=\min w(T_i)$。

通过找规律发现，最后我们的计算贡献一定是 $\max ,\min $ 交替的。

由于每一个儿子至多只有两种贡献，一颗树有值的 $a_i$ 的数量和该树的叶子数相等。

那么直接线段树合并就行了。

代码简洁易懂，应该一看就能明白：

```c++
#include<bits/stdc++.h>
using namespace std;
#define N 200005
#define p 998244353
#define ll long long
int n,L,R,x,dep[N],dad[N];
basic_string<int> G[N];
int ls[N<<5],rs[N<<5],tot;ll tr[N<<5],tag[N<<5];
int dfs(int u,int fa){
    dep[u]=dep[dad[u]=fa]+1;
    if(G[u].size()==1&&u!=1)return u;
    int ans;
    if(dep[u]&1){ans=0;for(int v:G[u])if(v!=fa)ans=max(ans,dfs(v,u));}
    else{ans=n;for(int v:G[u])if(v!=fa)ans=min(ans,dfs(v,u));}
    return ans;
}
inline void push(int u){
    if(tag[u]!=1)
        tag[ls[u]]=tag[ls[u]]*tag[u]%p,
        tag[rs[u]]=tag[rs[u]]*tag[u]%p,
        tr[ls[u]]=tr[ls[u]]*tag[u]%p,
        tr[rs[u]]=tr[rs[u]]*tag[u]%p,
        tag[u]=1;
}
inline void pull(int u){
    tr[u]=(tr[ls[u]]+tr[rs[u]])%p;
}
void upd(int &u,int l,int r,int x,int y){
    if(!u)u=++tot,tag[u]=1;
    if(l==r)return tr[u]=y,void();
    int m=(l+r)>>1;
    if(m>=x)upd(ls[u],l,m,x,y);
    else upd(rs[u],m+1,r,x,y);
    pull(u);
}
int merge1(int u,int v,int l,int r,ll mn1,ll mn2){//max 合并
    if(!u||!v){
        if(!u)return tr[v]=tr[v]*mn1%p,tag[v]=tag[v]*mn1%p,v;
        else return tr[u]=tr[u]*mn2%p,tag[u]=tag[u]*mn2%p,u;
    }
    if(l==r)return tr[u]=(tr[u]*mn2+tr[v]*mn1+tr[u]*tr[v])%p,u;
    push(u);push(v);
    int m=(l+r)>>1;
    rs[u]=merge1(rs[u],rs[v],m+1,r,(mn1+tr[ls[u]])%p,(mn2+tr[ls[v]])%p);
    ls[u]=merge1(ls[u],ls[v],l,m,mn1,mn2);
    return pull(u),u;
}
int merge2(int u,int v,int l,int r,ll mx1,ll mx2){//min 合并
    if(!u||!v){
        if(!u)return tr[v]=tr[v]*mx1%p,tag[v]=tag[v]*mx1%p,v;
        else return tr[u]=tr[u]*mx2%p,tag[u]=tag[u]*mx2%p,u;
    }
    if(l==r)return tr[u]=(tr[u]*mx2+tr[v]*(mx1+tr[u]))%p,u;
    push(u);push(v);
    int m=(l+r)>>1;
    ls[u]=merge2(ls[u],ls[v],l,m,(mx1+tr[rs[u]])%p,(mx2+tr[rs[v]])%p);
    rs[u]=merge2(rs[u],rs[v],m+1,r,mx1,mx2);
    return pull(u),u;
}
void output(int u,int l,int r,int L,int R){
    if(l==r)return printf("%lld ",(tr[u]-(l==n)+p)%p),void();
    int m=(l+r)>>1;push(u);
    if(m>=L)output(ls[u],l,m,L,R);
    if(m<R)output(rs[u],m+1,r,L,R);
}
int dfs(int u,int fa,int opt){
    int root=0;
    if(G[u].size()==1){
        if(!opt){//需要小于 x
            if(u<x)upd(root,0,n,0,2);
            else upd(root,0,n,n,1),upd(root,0,n,u-(x-1),1);
        }
        else{//需要大于 x
            if(u>x)upd(root,0,n,0,2);
            else upd(root,0,n,n,1),upd(root,0,n,(x+1)-u,1);
        }
    }else{
        if((dep[u]&1)^opt){//max 类型
            upd(root,0,n,0,1);
            for(int v:G[u])if(v!=fa)root=merge1(root,dfs(v,u,opt),0,n,0,0);
        }
        else{
            upd(root,0,n,n,1);//min 类型
            for(int v:G[u])if(v!=fa)root=merge2(root,dfs(v,u,opt),0,n,0,0);
        }    
    }
    return root;
}
int main(){
    scanf("%d%d%d",&n,&L,&R);
    for(int i=1,u,v;i<n;i++)scanf("%d%d",&u,&v),G[u]+=v,G[v]+=u;
    x=dfs(1,0);int rt=0,rt2;
    upd(rt,0,n,1,1);upd(rt,0,n,n,1);
    for(int i=x,rt2;dad[i];i=dad[i]){
        for(int v:G[dad[i]])if(v!=i&&v!=dad[dad[i]])
            rt2=dfs(v,dad[i],dep[dad[i]]&1),rt=merge2(rt,rt2,0,n,0,0);
    }
    output(rt,0,n,L,R);
}
```

---

## 作者：Owen_codeisking (赞：1)

$\%\%\% lyx$ 考场切 $T_3$

我来口胡一个假的 $O(n\log n)$ 解法。

一些废话：我考前奶 $noip$ 有动态 $dp$ 那么 $ZJOI$ 也有一道动态 $dp$，结果奶中了。

### 前置知识：动态 $dp$

最好是用全局平衡二叉树，用其他的也可以，时限不卡。

现在我们要挖掘根结点的值改变和函数 $w(S)$ 有什么特殊的性质。

### 1、$W$ 在变化成 $W\pm k$ 的形式时一定能变化成 $W\pm 1$

显然，我们可以在 $O(n)$ 时间内求出当前的 $W$

我们发现递推式：

$$\begin{cases}w_i=\text{min}_{fa_j=i}\ w_j&dep_i\ \text{mod}\ 2=0,i\notin leaf\\w_i=\text{max}_{fa_j=i}\ w_j&dep_i\ \text{mod}\ 2=1,i\notin leaf\\w_i=i&i\in leaf\end{cases}$$

可知 $w_i$ 一定取自叶子结点的编号。对于一个集合 $S$，我们验证是否存在 $w(S)=k$ 等价于把当前所有 $|T|=k$ 子集的元素改成 $W\pm1$ 跑一遍 $O(n)$ 的树形 $dp$

### 2、$w(S)\leq k$ 等价于 $w({x|x\in S,x<W})\leq k$ 或 $w({x|x\in S,x>W})\leq k$

其实就是把 $x>W$ 的叶子结点改成 $W-1$，$x<W$ 的叶子结点改成 $W+1$ 然后判合法。

### 3、转化询问形式

我们可以把答案差分一下，求 $w(S)\leq k$ 的方案数。方案数如果不好合并，那么转化成概率。$[L,R]$ 这个区间只是为了给部分分用的。

### 4、开始 $dp$

$x<W$ 和 $x>W$ 的 $dp$ 是类似的，所以我们只要讨论一种情况。

$f_i$ 表示在 $i$ 的权值 $<W$ 的概率。

$$f'_i=\prod_{fa_j=i}(1-f'_j)$$

$$f'_i=[i\ \text{mod}\ 2=0]f_i+[i\ \text{mod}\ 2=1](1-f_i)$$

这两条式子可以去掉深度奇偶性的分类，具体推导可以感性理解一下。

接下来就是从小到大枚举并修改每个叶子结点的概率，这部分可以用动态 $dp$ 实现。

但是有一个问题，每一次我们要重新除以 $1-f'_j$，就无法避免 $1-f'_j$ 为 $0$ 的情况。那么我们还要再写一个 $data$ 结构体，人工排除这种情况。

由于每次我们都要求 $1-f'_j$ 的逆元，所以理论上还有一个 $\log$ 的。我问了一下 $kczno1$，这个解法可以被完全可以被完全二叉树卡到 $O(n\log^2 n)$

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=200000+10;
const int mod=998244353;
int n,L,R,head[maxn],to[maxn<<1],nxt[maxn<<1],tot;
int m,W,w[maxn],top[maxn],dep[maxn],siz[maxn],son[maxn],fa[maxn];ll ans[maxn];

inline int read()
{
	register int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return (f==1)?x:-x;
}

void print(ll x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9) print(x/10);
	putchar(x%10+'0');
}

inline ll fpow(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1) ret=ret*a%mod;
	return ret;
}

inline void addedge(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}

void dfs(int x,int f)
{
	siz[x]=1;fa[x]=f;dep[x]=dep[f]+1;
	int maxson=-1;
	for(int i=head[x],y;i;i=nxt[i])
	{
		y=to[i];
		if(y==f) continue;
		dfs(y,x);siz[x]+=siz[y];
		if(siz[y]>maxson) son[x]=y,maxson=siz[y];
	}
	if(!son[x]) w[x]=x;
	else
	{
		w[x]=w[son[x]];
		for(int i=head[x],y;i;i=nxt[i])
		{
			y=to[i];
			if(y==f||y==son[x]) continue;
			if(dep[x]&1) w[x]=max(w[x],w[y]);
			else w[x]=min(w[x],w[y]);
		}
	}
}

struct data
{
	ll x;int now;
	inline void operator *= (const ll &b)
	{
		if(!b) now++;
		else x=x*b%mod;
	}
	inline void operator /= (const ll &b)
	{
		if(!b) now--;
		else x=x*fpow(b,mod-2)%mod;
	}
	inline operator ll()
	{
		return now?0:x;
	}
};

struct node
{
	ll x,y;
	inline operator ll()
	{
		return y;
	}
};
inline node operator + (const node &a,const node &b)
{
	return (node){a.x*b.x%mod,(a.y+a.x*b.y)%mod};
}

struct Global_bst
{
	int rt,ch[maxn][2],fa[maxn],sta[maxn],top;bool nrt[maxn],d;
	node sum[maxn];data dp[maxn];
	inline void pushup(int x)
	{
		sum[x]=(node){-dp[x],dp[x]};
		if(ch[x][0]) sum[x]=sum[ch[x][0]]+sum[x];
		if(ch[x][1]) sum[x]=sum[x]+sum[ch[x][1]];
	}
	int build(int l,int r)
	{
		if(l>r) return 0;
		int sum=0,now=0,x;
		for(int i=l;i<=r;i++) sum+=siz[sta[i]]-siz[son[sta[i]]];
		for(int i=l;i<=r;i++)
		{
			now+=siz[sta[i]]-siz[son[sta[i]]];
			if((now<<1)>=sum)
			{
				x=sta[i];
				if(!son[x])
				{
					if(d==0) dp[x].x=(x<W);
					else dp[x].x=1-(x>W);
					if(!(dep[x]&1)) dp[x].x=1-dp[x].x;
				}
				fa[ch[x][0]=build(l,i-1)]=x;
				fa[ch[x][1]=build(i+1,r)]=x;
				pushup(x);return x;
			}
		}
	}
	int dfs(int topf,int f)
	{
		for(int x=topf;x;f=x,x=son[x])
		{
			dp[x].x=1;
			for(int i=head[x],y,z;i;i=nxt[i])
			{
				y=to[i];
				if(y==f||y==son[x]) continue;
				z=dfs(y,x);fa[z]=x;dp[x]*=1-sum[z];
			}
		}
		top=0;
		for(int x=topf;x;x=son[x]) sta[++top]=x;
		return build(1,top);
	}
	inline void init()
	{
		rt=dfs(1,0);
		for(int x=1;x<=n;x++)
		{
			if(ch[fa[x]][0]==x||ch[fa[x]][1]==x) nrt[x]=1;
			else nrt[x]=0;
		}
	}
	inline void modify(int x,ll y)
	{
		if(!(dep[x]&1)) y=1-y;
		dp[x].x=y;dp[x].now=0;
		while(x)
		{
			if(!nrt[x])
			{
				dp[fa[x]]/=1-sum[x];
				pushup(x);
				dp[fa[x]]*=1-sum[x];
			}
			else pushup(x);
			x=fa[x];
		}
	}
	inline ll get()
	{
		return sum[rt];
	}
}T[2];

int main()
{
	n=read(),L=read(),R=read();
	int x,y;
	for(int i=1;i<n;i++)
	{
		x=read(),y=read();
		addedge(x,y),addedge(y,x);
	}
	dfs(1,0);W=w[1];
	for(int x=1;x<=n;x++)
		if(x!=son[fa[x]])
			for(int y=x;y;y=son[y]) top[y]=x;
	for(int x=1;x<=n;x++) m+=!son[x];
	ll now=fpow(2,m-1),inv2=(mod+1)>>1;
	T[0].d=0;T[1].d=1;T[0].init();T[1].init();
	for(int i=1;i<n;i++)
	{
		x=W+i-1;
		if(x>W&&x<=n&&!son[x]) T[0].modify(x,inv2);
		x=W-i+1;
		if(x>0&&x<W&&!son[x]) T[1].modify(x,inv2);
		ans[i]=now*(2-(1-T[0].get())*T[1].get()%mod)%mod;
	}
	ans[n]=now*2-1;
	for(int i=L;i<=R;i++) print(((ans[i]-ans[i-1])%mod+mod)%mod),putchar(' ');
	putchar('\n');
	return 0;
}
```

---

## 作者：dsidsi (赞：1)

# Solution

考虑差分，求出$w(S)\leq k$的集合数。

 - 显然，$w$的值域是连续的。所以$w$只会变成$w+1$或$w-1$。
 - 显然，$w(S)\leq 1$的集合数为$2^{m-1}$，所以接下来讨论的时候默认$w$节点不会修改。
 - 可以发现$w(s)\leq k$等价于把$S$中所有$< w$的叶子的权值改为$w+1$或把所有$> w$的权值改为$w+1$（如果能改的话）后，根节点的权值改变。

考虑方案数不好合并，用概率替代。

设$f_i$表示$i$节点的元素$< w$的概率，$g_i$表示$i$节点的元素$>w$的概率。

最终答案为$2^{m-1}(1-f_1)(1-g_1)$

转移如下

$$\begin{cases} f_u'=\prod_{v \in son_u}(1-f_v') \\f_u'=[dep_u \ mod \ 2 =0](1-f_u)[dep_u \ mod \ 2 =1]f_u\end{cases}$$

$$\begin{cases} g_u'=\prod_{v \in son_u}(1-g_v') \\g_u'=[dep_u \ mod \ 2 =1](1-g_u)[dep_u \ mod \ 2 =0]g_u\end{cases}$$

这样除了初值可以避免奇偶性的讨论，正确性感性理解就好了。

这样可以写[$70$分](https://loj.ac/submission/416702)（不是我的）。

可以发现随着$R$的增大，每次最多只会有两个叶子节点发生改变。所以维护$f_i'$之积，动态$DP$即可。

**tips**:由于会出现除$0$乘$0$的情况，所以用数对$(x,y)$表示原$DP$值$x\cdot 0^y$即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int gi()
{
    char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    int sum = 0;
    while('0' <= c && c <= '9') sum = sum * 10 + c - 48, c = getchar();
    return sum;
}

typedef long long ll;
const int maxn = 200005, mod = 998244353, inv = (mod + 1) >> 1;

int n, m, L, LL, R, val[maxn];

struct edge
{
    int to, next;
} e[maxn * 2];
int h[maxn], Tot;

inline void add(int u, int v)
{
    e[++Tot] = (edge) {v, h[u]}; h[u] = Tot;
    e[++Tot] = (edge) {u, h[v]}; h[v] = Tot;
}

inline int fpow(int x, int k)
{
    int res = 1;
    while (k) {
        if (k & 1) res = (ll)res * x % mod;
        x = (ll)x * x % mod; k >>= 1;
    }
    return res;
}

int leaf[maxn], dfn[maxn], low[maxn], ord[maxn], fa[maxn], top[maxn], son[maxn], f[maxn][2], dep[maxn], siz[maxn], Time;

struct node
{
    int x, y;
    
    node() {x = y = 0;}
    node(int _x, int _y) {x = _x; y = _y;}
    
    inline node operator* (const node &a) const {
        return node((ll)x * a.x % mod, y + a.y);
    }
    inline node operator/ (const node &a) const {
        return node((ll)x * fpow(a.x, mod - 2) % mod, y - a.y);
    }
    inline int val() {return y ? 0 : x;}
} g[maxn][2];

inline node init(int a)
{
    if (a >= mod) a -= mod;
    return a ? node(a, 0) : node(1, 1);
}

void dfs1(int u)
{
    dep[u] = dep[fa[u]] + 1; siz[u] = 1; leaf[u] = 1;
    if (dep[u] & 1) val[u] = -1;
    else val[u] = n + 1;
    
    for (int i = h[u], v; v = e[i].to, i; i = e[i].next)
        if (v != fa[u]) {
            fa[v] = u; leaf[u] = 0; dfs1(v);

            siz[u] += siz[v];
            if (siz[son[u]] < siz[v]) son[u] = v;
            if (dep[u] & 1) val[u] = max(val[u], val[v]);
            else val[u] = min(val[u], val[v]);
        }
    if (leaf[u]) val[u] = u, ++m;
}

void dfs2(int u)
{
    ord[dfn[u] = ++Time] = u;
    if (son[u]) top[son[u]] = top[u], dfs2(son[u]);
    else low[top[u]] = Time;
    for (int i = h[u], v; v = e[i].to, i; i = e[i].next)
        if (v != fa[u] && v != son[u]) top[v] = v, dfs2(v);
    if (!leaf[u]) {
        f[u][0] = f[u][1] = 1; g[u][0] = g[u][1] = init(1);
        for (int i = h[u], v; v = e[i].to, i; i = e[i].next)
            if (v != fa[u] && v != son[u]) {
                f[u][0] = (ll)f[u][0] * (mod + 1 - f[v][0]) % mod;
                f[u][1] = (ll)f[u][1] * (mod + 1 - f[v][1]) % mod;
                g[u][0] = g[u][0] * init(mod + 1 - f[v][0]);
                g[u][1] = g[u][1] * init(mod + 1 - f[v][1]);
            }
    } else {
        if (val[u] != val[1]) {
            if (val[u] < val[1]) f[u][0] = dep[u] & 1; 
            else if (val[u] - L < val[1]) f[u][0] = inv;
            else f[u][0] = (dep[u] & 1) ^ 1;
            if (val[u] > val[1]) f[u][1] = (dep[u] & 1) ^ 1;
            else if (val[u] + L > val[1]) f[u][1] = inv;
            else f[u][1] = dep[u] & 1;
        } else f[u][0] = (dep[u] & 1) ^ 1, f[u][1] = dep[u] & 1;
        g[u][0] = init(f[u][0]);
        g[u][1] = init(f[u][1]);
    }
    if (son[u]) {
        f[u][0] = (ll)f[u][0] * (mod + 1 - f[son[u]][0]) % mod;
        f[u][1] = (ll)f[u][1] * (mod + 1 - f[son[u]][1]) % mod;
    }
}

int tot, rt[maxn], sum[maxn << 2][2], pre[maxn << 2][2], lch[maxn << 2], rch[maxn << 2];

#define mid ((l + r) >> 1)

inline void merge(int &s, int len)
{
    sum[s][0] = (sum[lch[s]][0] + (ll)((len & 1) ? mod - pre[lch[s]][0] : pre[lch[s]][0]) * sum[rch[s]][0]) % mod;
    pre[s][0] = (ll)pre[lch[s]][0] * pre[rch[s]][0] % mod;
    sum[s][1] = (sum[lch[s]][1] + (ll)((len & 1) ? mod - pre[lch[s]][1] : pre[lch[s]][1]) * sum[rch[s]][1]) % mod;
    pre[s][1] = (ll)pre[lch[s]][1] * pre[rch[s]][1] % mod;
}

void build(int &s, int l, int r)
{
    s = ++tot;
    if (l == r) {
        sum[s][0] = pre[s][0] = g[ord[l]][0].val();
        sum[s][1] = pre[s][1] = g[ord[l]][1].val();
        return ;
    }
    build(lch[s], l, mid);
    build(rch[s], mid + 1, r);
    merge(s, mid - l + 1);
}

void modify(int &s, int l, int r, int p)
{
    if (l == r) {
        sum[s][0] = pre[s][0] = g[ord[l]][0].val();
        sum[s][1] = pre[s][1] = g[ord[l]][1].val();
        return ;
    }
    if (p <= mid) modify(lch[s], l, mid, p);
    else modify(rch[s], mid + 1, r, p);
    merge(s, mid - l + 1);
}

void modify(int u, int x)
{
    int v = top[u];
    if (fa[v]) g[fa[v]][x] = g[fa[v]][x] / init(mod + 1 - sum[rt[v]][x]);
    modify(rt[v], dfn[v], low[v], dfn[u]);
    if (fa[v]) g[fa[v]][x] = g[fa[v]][x] * init(mod + 1 - sum[rt[v]][x]), modify(fa[v], x);
}

int main()
{
    n = gi(); LL = L = gi(); R = gi();
    for (int i = 1; i < n; ++i) add(gi(), gi());

    dfs1(1);
    if (L == 1) printf("%d ", fpow(2, m - 1)), ++L, ++LL;
    else if (L > 2) --L;
    top[1] = 1; dfs2(1);

    for (int i = 1; i <= n; ++i)
        if (top[ord[i]] == ord[i])
            build(rt[ord[i]], dfn[ord[i]], low[ord[i]]);
    
    int pw = fpow(2, m - 1), lstans = 0, ans;
    lstans = (mod + 1 - (ll)(mod + 1 - sum[rt[1]][0]) * sum[rt[1]][1] % mod) * pw % mod;
    if (LL <= L && L <= R) printf("%d ", lstans);
    for (int i = L + 1; i <= R && i < n; ++i) {
        if (val[1] + i - 1 <= n && leaf[val[1] + i - 1]) {
            g[val[1] + i - 1][0] = init((mod + 1) >> 1);
            modify(val[1] + i - 1, 0);
        }
        if (val[1] - i + 1 >= 1 && leaf[val[1] - i + 1]) {
            g[val[1] - i + 1][1] = init((mod + 1) >> 1);
            modify(val[1] - i + 1, 1);
        }
        ans = (mod + 1 - (ll)(mod + 1 - sum[rt[1]][0]) * sum[rt[1]][1] % mod) * pw % mod;
        printf("%d ", (ans - lstans + mod) % mod);
        lstans = ans;
    }
    if (R == n) printf("%d ", (pw - lstans - 1 + mod) % mod);
    
    return 0;
}
```

---

## 作者：UKE_Automation (赞：0)

### [ZJOI2019] Minimax 搜索

[$\text{Link}$](https://www.luogu.com.cn/problem/P5281)

首先我们先跑一遍正常的搜索，把每个点的初始权值 $col_i$ 求出来。令 $W=col_1$，那么 $W$ 节点的根链上的所有节点的权值都应该是 $W$，而只要这里面有一个点的权值改变了，根节点就改变了。所以实际上我们可以把这条链上的边断开，对于每个连通块计算其对应方案数，然后组合起来即可。

现在考虑计数，首先直接算 $w(S)=k$ 的方案数比较困难，一个经典的想法是先求 $w(S)\le k$ 的方案数然后再做差分。然后考虑树形 dp，设 $dp(i)$ 表示 $i$ 子树内的所有叶子构成的集合的非空子集中，有多少集合 $S$ 可以使得在 $k$ 次操作以内让 $col_i<W$。由于把叶子改成 $W$ 没有意义，所以我们不用管 $col_i=W$ 的情况，那么 $col_i>W$ 的集合个数就是总方案数 $cnt_i$ 减去 $dp(i)$ 了。此时答案就可以写成：
$$
ans=sum-\sum_{col_x=W}\sum_{dep_x\bmod 2=0} (cnt_x-dp(x))+\sum_{dep_x\bmod 2=1} dp(x)
$$
然后考虑转移，这个也不是很困难，算方案的时候用一下容斥即可：
$$
dp(i)=\begin{cases}
\prod\limits_{j\in son(i)} dp(j),&dep_i\bmod 2=1\\
cnt_i-\prod\limits_{j\in son(i)} (cnt_j-dp(j)),& dep_i\bmod 2=0
\end{cases}
$$
最后我们来考虑一下初值。首先我们需要明白一件事：对于同一个连通块内的叶子，它们要改大还是改小取决于根节点在原树上的深度。如果根节点原本深度是奇数，那么所有点一定都是往大改的，否则的话就是往小改，这样的话才是最优的。那么根据这个，可以得出：

- 当根节点深度为奇数时，叶子节点 $x$ 的初值为 $dp(x)=[x<W]+[x+k<W]$。
- 当根节点深度为偶数时，叶子节点 $x$ 的初值为 $dp(x)=[x<W]+[x-k<W]$。

我们从小往大枚举 $k$，发现此时 $k$ 增加时每次只会有最多 $1$ 个位置的 dp 值发生改变。所以我们可以尝试使用动态 dp 维护上述过程。记：
$$
g(i)=\begin{cases}
cnt_i-dp(i),&dep_i\bmod 2=1\\
dp(i),& dep_i\bmod 2=0
\end{cases}
$$
那么上述转移可以写作：
$$
ans=sum-\sum _{col_x=W} (cnt_x-g(x))
$$
同时有：
$$
g(i)=cnt_i-\prod_{j\in son(i)} g(j)
$$
那么对原树做重链剖分，转移可以写成（其中 $\text{son}(i)$ 为 $i$ 的重儿子）：
$$
g(i)=cnt_i+(-\prod g(j))\times g(\text{son}(i))
$$
把上述转移写成矩阵形式为：
$$
\begin{bmatrix}
-\prod g(j)& cnt_i\\
0& 1
\end{bmatrix}\times 
\begin{bmatrix}
g(\text{son}(i))\\
1
\end{bmatrix}=
\begin{bmatrix}
g(i)\\
1
\end{bmatrix}
$$
用线段树维护一下左侧矩阵即可，总复杂度是 $O(n\log^2 n)$ 的。还需要注意的一点是我们处理轻儿子 dp 值积的时候会出现乘以 $0$ 或除以 $0$ 的情况，这个时候需要维护一下儿子中 $0$ 的数量来特判。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

const int Maxn = 2e5 + 5;
const int Inf = 2e9;
const int Mod = 998244353;
il int Add(int x, int y) {return x + y >= Mod ? x + y - Mod: x + y;} il void pls(int &x, int y) {x = Add(x, y);}
il int Del(int x, int y) {return x - y < 0 ? x - y + Mod : x - y;} il void sub(int &x, int y) {x = Del(x, y);}
il int qpow(int a, int b) {int res = 1; for(; b; a = 1ll * a * a % Mod, b >>= 1) if(b & 1) res = 1ll * res * a % Mod; return res;}
il int Inv(int a) {return qpow(a, Mod - 2);}
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool typ = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	typ ? putchar('\n') : putchar(' ');
}
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int n, m, l, r;
int head[Maxn], edgenum, deg[Maxn];
struct node {
	int nxt, to;
}edge[Maxn << 1];
void add(int u, int v) {
	deg[u]++, deg[v]++;
	edge[++edgenum] = {head[u], v}; head[u] = edgenum;
	edge[++edgenum] = {head[v], u}; head[v] = edgenum;
}

struct Mat {
	int a, b;
	Mat operator * (Mat y) {return {1ll * a * y.a % Mod, Add(1ll * a * y.b % Mod, b)};}
}a[Maxn];

int col[Maxn], dep[Maxn], W;
void dfs1(int x, int fth) {
	dep[x] = dep[fth] + 1;
	if(x != 1 && deg[x] == 1) {m++; col[x] = x; return ;}
	if(dep[x] % 2 == 0) col[x] = Inf;
	for(int i = head[x]; i; i = edge[i].nxt) {
		int to = edge[i].to;
		if(to == fth) continue;
		dfs1(to, x);
		if(dep[x] & 1) col[x] = max(col[x], col[to]);
		else col[x] = min(col[x], col[to]);
	}
}

int leaf(int x) {return col[x] != W && deg[x] == 1;}

int siz[Maxn], son[Maxn], fa[Maxn], top[Maxn], dfn[Maxn], rnk[Maxn], idx, cnt[Maxn], low[Maxn];
void dfs2(int x, int fth) {
	siz[x] = 1; fa[x] = fth; cnt[x] = 1;
	if(leaf(x)) {cnt[x] = 2; low[x] = x; return ;}
	for(int i = head[x]; i; i = edge[i].nxt) {
		int to = edge[i].to;
		if(to == fth || col[to] == W) continue;
		dfs2(to, x);
		siz[x] += siz[to]; cnt[x] = 1ll * cnt[x] * cnt[to] % Mod;
		if(siz[son[x]] < siz[to]) son[x] = to, low[x] = low[to];
	}
}

int g[Maxn], zer[Maxn], sum[Maxn], typ[Maxn];
void Mul(int x, int v) {
	a[x].a = 1ll * a[x].a * v % Mod;
	if(!v) zer[x]++;
	else sum[x] = 1ll * sum[x] * v % Mod;
}

void Div(int x, int v) {
	if(!v) {
		zer[x]--;
		if(!zer[x]) a[x].a = Mod - sum[x];
	}
	else a[x].a = 1ll * a[x].a * Inv(v) % Mod, sum[x] = 1ll * sum[x] * Inv(v) % Mod;
}

void dfs3(int x, int rt) {
	top[x] = rt; dfn[x] = ++idx; rnk[idx] = x; 
	if(!typ[x]) typ[x] = typ[fa[x]];
	if(son[x]) {
		dfs3(son[x], rt);
		g[x] = Mod - g[son[x]]; sum[x] = 1;
		a[x] = {Mod - 1, cnt[x]};
	}
	else {
		if(leaf(x)) {
			int f = 2 * (x < W);
			if(dep[x] & 1) g[x] = Del(cnt[x], f), a[x] = {g[x], 0};
			else g[x] = f, a[x] = {g[x], 0};
		}
		return ;
	}
	for(int i = head[x]; i; i = edge[i].nxt) {
		int to = edge[i].to;
		if(to == son[x] || to == fa[x] || col[to] == W) continue;
		dfs3(to, to);
		g[x] = 1ll * g[x] * g[to] % Mod;
		Mul(x, g[to]);
	}
	pls(g[x], cnt[x]);
}

namespace SMT {
	Mat t[Maxn << 2];
	#define ls(p) (p << 1)
	#define rs(p) (p << 1 | 1)
	void pushup(int p) {t[p] = t[ls(p)] * t[rs(p)];}
	void build(int p, int l, int r) {
		if(l == r) {
			t[p] = a[rnk[l]]; return ;
		}
		int mid = (l + r) >> 1;
		build(ls(p), l, mid), build(rs(p), mid + 1, r);
		pushup(p);
	}
	void mdf(int p, int l, int r, int x, Mat a) {
		if(l == r) {
			t[p] = a; return;
		}
		int mid = (l + r) >> 1;
		if(x <= mid) mdf(ls(p), l, mid, x, a);
		else mdf(rs(p), mid + 1, r, x, a);
		pushup(p);
	}
	Mat query(int p, int l, int r, int pl, int pr) {
		if(pl <= l && r <= pr) return t[p];
		int mid = (l + r) >> 1;
		Mat res = {1, 0};
		if(pl <= mid) res = res * query(ls(p), l, mid, pl, pr);
		if(pr > mid) res = res * query(rs(p), mid + 1, r, pl, pr);
		return res;
	}
}

int ans[Maxn], res[Maxn];

void mdf(int x) {
	int f = 1;
	if(dep[x] & 1) a[x] = {Del(cnt[x], f), 0};
	else a[x] = {f, 0};
	SMT::mdf(1, 1, n, dfn[x], a[x]);
	while(fa[top[x]]) {
		Mat ret = SMT::query(1, 1, n, dfn[top[x]], dfn[low[x]]);
		Div(fa[top[x]], g[top[x]]);
		g[top[x]] = Add(ret.a, ret.b);
		Mul(fa[top[x]], g[top[x]]);
		SMT::mdf(1, 1, n, dfn[fa[top[x]]], a[fa[top[x]]]);
		x = fa[top[x]];
	}
	Mat ret = SMT::query(1, 1, n, dfn[top[x]], dfn[low[x]]);
	Div(0, Del(cnt[top[x]], g[top[x]]));
	g[top[x]] = Add(ret.a, ret.b);
	Mul(0, Del(cnt[top[x]], g[top[x]]));
}

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	read(n), read(l), read(r);
	for(int i = 1, u, v; i < n; i++) {
		read(u), read(v);
		add(u, v);
	}
	dfs1(1, 0);
	W = col[1]; sum[0] = 1; a[0] = {1, 0};
	for(int i = 1; i <= n; i++) {
		if(col[i] == W) {
			typ[i] = dep[i] & 1;
			dfs2(i, 0), dfs3(i, i);
			Mul(0, Del(cnt[i], g[i]));
		}
	}
	ans[0] = a[0].a; ans[n] = 1;
	SMT::build(1, 1, n);
	for(int i = 1; i < n; i++) {
		if(W - i + 1 >= 1 && leaf(W - i + 1) && typ[W - i + 1] == 1) mdf(W - i + 1);
		if(W + i - 1 <= n && leaf(W + i - 1) && typ[W + i - 1] == 0) mdf(W + i - 1);
		ans[i] = a[0].a;
	}
	for(int i = 1; i <= n; i++) res[i] = Del(ans[i - 1], ans[i]);
	pls(res[1], qpow(2, m - 1));
	for(int i = l; i <= r; i++) write(res[i], 0);
	Usd();
	return 0;
}
```

---

## 作者：OIer_Automation (赞：0)

考虑花费恰好为 $k$ 的集合数较为难求，不如先转化成花费 $\le k$ 后再进行差分。考虑先求出最开始时所有节点的权值，假设此时根节点的权值为 $W$，那么编号为 $W$ 的叶子节点的根链肯定也全为 $W$，如果想要让根节点的权值改变，只需要让这条根链上的任何一个点的权值改变即可，于是我们考虑分开对每一个点求解其改变的集合数。

现在我们断掉了 $W$ 的根链上的所有边得到了若干个连通块，假设其中的一个的根节点为 $u$，在这个连通块中总共有 $c$ 个叶子节点，那么在这里选择集合的总方案数是 $\text{cnt}_u=2^c$。设 $f(u)$ 表示只考虑节点 $u$ 的子树，$u$ 的权值最终 $<W$ 的集合数。考虑按照每个点**在原树上的**深度分类讨论：

1. $\text{dep}_u\bmod 2=1$，此时 $u$ 取所有儿子节点的最大值，那么只需要所有的儿子节点的权值均 $<W$ 即可，即 $f(u)=\prod_{v\in\text{son}_u} f(v)$。
2. $\text{dep}_u\bmod 2=0$，此时 $u$ 取所有儿子节点的最小值，那么只需要有一个儿子节点的权值 $<W$ 即可，用容斥简单得到 $f(u)=\text{cnt}_u-\prod_{v\in\text{son}_u}(\text{cnt}_v-f_v)$。

转移方程比较凌乱，但我们可以令 $g(u)$ 在 $\text{dep}_u\bmod 2=1$ 时表示 $\text{cnt}_u-f(u)$，在 $\text{dep}_u\bmod 2=0$ 时表示 $f(u)$，那么转移方程就可以统一写作 $g(u)=\text{cnt}_u-\prod_{v\in\text{son}_u}g(v)$。初始值在所有叶子节点处，当根节点的深度为奇数时值为 $[u<W]+[u+k<W]$，否则为 $[u<W]+[u-k<W]$。这是因为根据根节点的深度，我们为了使其改变，在调整的时候肯定需要尽可能对应向大或向小调。此时枚举 $k$ 可以做到 $O(n^2)$ 求解。

考虑每一次的转移实际上是完全相同的，只有初始值不同，而每一个点的初始值在 $k$ 变化的最多改变一次，于是可以考虑动态 dp。对每个连通块树链剖分，那么转移是 $g(u)=\text{cnt}_u-(\prod_{v\in\text{light}_u}g(v))g(\text{heavy}_u)$，可以看作 $y=kx+b$ 的形式，并且这个形式有结合律，因此可以直接用线段树维护这个内容，复杂度是 $O(n\log^2 n)$ 的。

实际实现的时候考虑到 $g(u)$ 的取值可能为 $0$，因此消除贡献的时候不能直接除，而是要统计所有非 $0$ 的数的积和 $0$ 的个数，然后特判是否有 $0$ 之后才能得出正确的结果。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline

const int N=2e5+5,P=998244353,G=499122177,inf=1e9;

il int Add(int x,int y){return x+y>=P?x+y-P:x+y;}il void Dadd(int &x,int y){x=x+y>=P?x+y-P:x+y;}
il int Dec(int x,int y){return x-y<0?x-y+P:x-y;}
il int Mul(int x,int y){return 1ll*x*y%P;}il void Dmul(int &x,int y){x=1ll*x*y%P;}
il void Dmin(int &x,int y){x=x<=y?x:y;}il void Dmax(int &x,int y){x=x>=y?x:y;}
il int Qpow(int a,int b=P-2){int res=1;for(;b;b>>=1,Dmul(a,a))if(b&1)Dmul(res,a);return res;}

int n,L,R,tot,W,num,ansv;
int head[N],nxt[N<<1],to[N<<1],deg[N],pw[N],dep[N],faz[N],val[N],siz[N],cnt[N],son[N],id[N],dfn[N],top[N],bot[N],g[N],rea[N],zer[N],ans[N];
bitset<N>lea,opt;
struct Tag{
	int k,b;
	friend Tag operator +(Tag x,Tag y){return {Mul(x.k,y.k),Add(Mul(x.k,y.b),x.b)};}
}t[N];
namespace T{
	Tag tag[N<<2];
	il void PushUp(int id){tag[id]=tag[id<<1]+tag[id<<1|1];}
	il void Build(int id=1,int l=1,int r=n){
		if(l==r)return tag[id]=t[dfn[l]],void();
		int mid=(l+r)>>1,ls=id<<1,rs=id<<1|1;
		Build(ls,l,mid),Build(rs,mid+1,r),PushUp(id);
	}
	il void Modify(int p,Tag v,int id=1,int l=1,int r=n){
		if(l==r)return tag[id]=v,void();
		int mid=(l+r)>>1,ls=id<<1,rs=id<<1|1;
		p<=mid?Modify(p,v,ls,l,mid):Modify(p,v,rs,mid+1,r),PushUp(id);
	}
	il Tag Query(int p,int q,int id=1,int l=1,int r=n){
		if(p<=l&&r<=q)return tag[id];
		int mid=(l+r)>>1,ls=id<<1,rs=id<<1|1;
		if(q<=mid)return Query(p,q,ls,l,mid);
		if(p>mid)return Query(p,q,rs,mid+1,r);
		return Query(p,q,ls,l,mid)+Query(p,q,rs,mid+1,r);
	}
}

il void AddEdge(int u,int v){
	++tot,nxt[tot]=head[u],to[tot]=v,head[u]=tot,deg[u]++;
	++tot,nxt[tot]=head[v],to[tot]=u,head[v]=tot,deg[v]++;
}
il void Dfs1(int u){
	if(lea[u])return val[u]=u,void();
	val[u]=dep[u]&1?-inf:inf;
	for(int i=head[u],v;v=to[i];i=nxt[i])if(v!=faz[u])dep[v]=dep[u]+1,faz[v]=u,Dfs1(v),(dep[u]&1?Dmax:Dmin)(val[u],val[v]);
}
il void Dfs2(int u,int op){
	siz[u]=1,opt[u]=op;
	if(lea[u])return cnt[u]=1,Dadd(ans[0],ans[0]);
	for(int i=head[u],v;v=to[i];i=nxt[i])if(v!=faz[u]&&val[v]!=W){
		Dfs2(v,op),siz[u]+=siz[v],cnt[u]+=cnt[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
	for(int i=head[u],v;v=to[i];i=nxt[i])if(v!=faz[u]&&val[v]==W)Dfs2(v,op^1);
}
il void Dfs3(int u,int tp){
	dfn[++num]=u,id[u]=num,cnt[u]=pw[cnt[u]],top[u]=tp;
	if(!son[u]&&lea[u]){int c=(u<W)+(u<=W);return bot[u]=u,g[u]=dep[u]&1?2-c:c,void();}
	if(son[u]){
		rea[u]=1,Dfs3(son[u],tp),bot[u]=bot[son[u]];
		for(int i=head[u],v;v=to[i];i=nxt[i])if(v!=faz[u]&&v!=son[u]&&val[v]!=W)Dfs3(v,v),g[v]?Dmul(rea[u],g[v]),0:zer[u]++;
		g[u]=zer[u]?0:rea[u],t[u]={P-g[u],cnt[u]},g[u]=Dec(cnt[u],Mul(g[u],g[son[u]]));
	}
	for(int i=head[u],v;v=to[i];i=nxt[i])if(v!=faz[u]&&val[v]==W)Dfs3(v,v);
}
il void Modify(int u){
	int lsti,lstn;
	while(true){
		int v=top[u],w=faz[v],k=bot[u],inv=g[v],now;
		if(lea[u])g[u]=1;
		now=v==k?g[v]:g[v]=(T::Query(id[v],id[k]-1)+(Tag){0,g[k]}).b;
		if(!w){lsti=Dec(cnt[v],inv),lstn=Dec(cnt[v],now);break;}
		inv?Dmul(rea[w],Qpow(inv)),0:zer[w]--,now?Dmul(rea[w],now),0:zer[w]++,t[w].k=zer[w]?0:P-rea[w],T::Modify(id[w],t[w]),u=w;
	}
	if(lsti)Dmul(ansv,Qpow(lsti));if(lstn)Dmul(ansv,lstn);
}

int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>L>>R,dep[1]=ans[0]=ans[n]=pw[0]=1;
	for(int i=1,u,v;i<n;i++)cin>>u>>v,AddEdge(u,v);
	for(int i=1;i<=n;i++)pw[i]=Add(pw[i-1],pw[i-1]),lea[i]=deg[i]==1&&i!=1;
	Dfs1(1),W=val[1],Dfs2(1,1),ansv=Mul(ans[0],G),Dfs3(1,1),T::Build();
	for(int i=1;i<=n;i++)if(val[i]==W)faz[i]=0;
	for(int i=1;i<n;i++){
		ans[i]=ansv;
		if(W>i&&lea[W-i]&&opt[W-i])Modify(W-i);
		if(W+i<=n&&lea[W+i]&&!opt[W+i])Modify(W+i);
	}
	for(int i=L;i<=R;i++)cout<<Dec(ans[i-1],ans[i])<<" ";
}
```

---

## 作者：花淇淋 (赞：0)

## Solution
考虑对 $k\in [l-1,r]$ 分别求出有多少个集合 $S$ 满足 $w(S)\le k$，记作 $ans_k$。

先求出 $1$ 的初始权值 $W$。

记 $val(x)$ 表示 $x$ 的权值。枚举 $k$，现在对于每个叶子 $u$，如果 $u\in S$，那么 $val(u)\in [u-W,u+W]$，否则 $val(u)=W$。

我们发现，把叶子节点的权值改成 $W$ 肯定是不优的。所以改动一些叶子后，如果 $val(1)$ 还是 $W$，那么肯定路径 $1→W$ 上每个点的权值都是 $W$，且其它的点的权值都不是 $W$。

因此，如果想要 $val(1)$ 改变，那么路径 $1→W$ 上肯定存在一个点 $x$，$val(x)\ne W$。记 $x$ 在路径 $1→W$ 上的子节点为 $y$。如果 $x$ 深度是奇数，  那么肯定存在一个 $x$ 的子节点 $z(z\ne y)$，$val(z)>W$。$x$ 深度是偶数时同理。

我们把 $1→W$ 上的边全部断掉，再求一遍每个点的权值。如果原路径 $1→W$ 上存在某个深度为奇数的点的权值 $>W$，或者某个深度为偶数的点的权值 $<W$，那么 $val(1)$ 肯定改变，否则肯定不变。

记 $f(u)$ 表示 $u$ 子树中，使 $val(u)>w$ 的合法叶子节点集合有几个。$g(u)$ 表示 $u$ 子树中，使 $val(u)<w$ 的合法叶子节点集合有几个。

如果 $u$ 是叶子节点：$f(u)=[u>W]+[u+k>W],g(u)=[u<W]+[u-k<W]$。其中 $[u>W],[u<W]$ 表示 $u$ 不在叶子节点集合内，$[u+k>W],[u-k<W]$ 表示在集合内。

如果 $u$ 是深度为奇数的非叶子节点，如果 $val(u)>W$，那么 $u$ 的子节点最大权值必须 $>W$，也就是说不能全部 $\le W$。因此 $f(u)=2^{cnt_u}\prod_{v\in son_u}(2^{cnt_v}-f(v))$。其中 $cnt_u$ 表示 $u$ 的子树内有几个叶子节点。

如果 $u$ 是深度为偶数的非叶子节点，如果 $val(u)>W$，那么 $u$ 的子节点全部 $<W$。因此 $f(u)=\prod_{v\in son_u}f(v)$。

$g$ 的转移和 $f$ 类似。

接下来求 $ans_k$。考虑补集转化，即用 $2^{cnt_1}$ 减去不会让 $val(1)$ 改变的集合数。不会让 $val(1)$ 改变，就是要让原路径 $1→W$ 上的每个点的权值都不变。那么把深度为奇数的 $2^{cnt_x}-f_x$ 和深度为偶数的 $2^{cnt_x}-g_x$ 全部相乘就是答案了。

至此，我们得到了一个 $O(n(R-L))$ 的做法。

考虑优化，我们发现转移与 $k$ 无关，只有叶子节点的 $f,g$ 和 $k$ 有关。进一步地，我们发现随着 $k$ 变大，每个叶子节点的 $f,g$ 最多改变一次。因此可以看作是 $O(n)$ 次修改的动态 $dp$，时间复杂度 $O(n\log^2 n)$。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define p2 p << 1
#define p3 p << 1 | 1

template <class t>
inline void read(t & res)
{
    char ch;
    while (ch = getchar(), !isdigit(ch));
    res = ch ^ 48;
    while (ch = getchar(), isdigit(ch))
    res = res * 10 + (ch ^ 48);
}

template <class t>
inline void print(t x)
{
    if (x > 9) print(x / 10);
    putchar(x % 10 + 48);
}

const int e = 2e5 + 5, mod = 998244353;

struct point
{
    int x, y;
}b[e], que[e];
struct matrix
{
    int a, b;
    
    matrix(){}
    matrix(int _a, int _b) :
        a(_a), b(_b) {}
}tr[e << 2];
vector<int>g[e], c[e], d[e];
int f[e], dep[e], L, R, w, n, fa[e], a[e], m, nxt[e], go[e], adj[e], val[e], K, cnt[e], f2[e];
int q[e], h[e], num, all, sum[e << 2], son[e], sze[e], dfnA[e], dfnB[e], timA, timB, idA[e], idB[e];
int st[e], ed[e], bot[e], top[e], ans[e], rt[e], now_rt;
bool is[e], op, bo[e];

inline void add(int &x, int y)
{
    (x += y) >= mod && (x -= mod);
}

inline void del(int &x, int y)
{
    (x -= y) < 0 && (x += mod);
}

inline int plu(int x, int y)
{
    add(x, y);
    return x;
}

inline int sub(int x, int y)
{
    del(x, y);
    return x;
}

inline int mul(int x, int y)
{
    return (ll)x * y % mod;
}

inline int ksm(int x, int y)
{
    int res = 1;
    while (y)
    {
        if (y & 1) res = mul(res, x);
        y >>= 1;
        x = mul(x, x);
    }
    return res;
}

inline matrix operator + (matrix u, matrix v)
{
    return matrix(mul(u.a, v.a), plu(mul(u.b, v.a), v.b));
}

inline void link1(int x, int y)
{
    g[x].push_back(y);
    g[y].push_back(x);
}

inline void link2(int x, int y)
{
    nxt[++num] = adj[x]; adj[x] = num; go[num] = y;
}

inline void dfs1(int u, int pa)
{
    dep[u] = dep[pa] + 1;
    fa[u] = pa;
    if (dep[u] & 1) val[u] = 0;
    else val[u] = n + 1;
    int len = g[u].size(), i;
    bool pd = 0;
    for (i = 0; i < len; i++)
    {
        int v = g[u][i];
        if (v == pa) continue;
        pd = 1;
        dfs1(v, u);
        if (dep[u] & 1) val[u] = max(val[u], val[v]);
        else val[u] = min(val[u], val[v]);
    }
    if (!pd) val[u] = u, all++;   
}

inline void dfs2(int u)
{
    if (val[u] == u)
    {
        if (op) 
        {
            f[u] = (u > w) + (u + K > w);
            if (L <= w + 1 - u && w + 1 - u <= R) c[w + 1 - u].push_back(u);
        }
        else 
        {
            f[u] = (u < w) + (u - K < w);
            if (L <= u + 1 - w && u + 1 - w <= R) d[u + 1 - w].push_back(u);
        }
        return;
    }
    f[u] = f2[u] = 1;
    bool fl = ((dep[u] & 1) && op) || ((~dep[u] & 1) && !op);
    bo[u] = fl;
    for (int i = adj[u]; i; i = nxt[i])
    {
        int v = go[i];
        dfs2(v);
        if (fl) f[u] = mul(f[u], sub(q[v], f[v]));
        else f[u] = mul(f[u], f[v]);
        if (v != son[u])
        {
            if (fl) f2[u] = mul(f2[u], sub(q[v], f[v]));
            else f2[u] = mul(f2[u], f[v]);
        }
    }
    if (fl) f[u] = sub(q[u], f[u]);
}

inline void dfs3(int u)
{
    if (val[u] == u) cnt[u] = 1;
    sze[u] = 1;
    rt[u] = now_rt;
    for (int i = adj[u]; i; i = nxt[i])
    {
        int v = go[i];
        dfs3(v);
        cnt[u] += cnt[v];
        sze[u] += sze[v];
        if (sze[v] > sze[son[u]]) son[u] = v;
    }
}

inline void dfs4(int u, int fi)
{
    top[u] = fi;
    dfnA[u] = ++timA;
    idA[timA] = u;
    if (son[u]) 
    {
        dfs4(son[u], fi);
        st[u] = timB + 1;
        for (int i = adj[u]; i; i = nxt[i])
        {
            int v = go[i];
            if (v == son[u]) continue;
            dfnB[v] = ++timB;
            idB[timB] = v;
        }
        ed[u] = timB;
    }
    for (int i = adj[u]; i; i = nxt[i])
    {
        int v = go[i];
        if (v == son[u]) continue;
        dfs4(v, v);
    }
    if (son[u]) bot[u] = bot[son[u]];
    else bot[u] = u;
}

inline void build(int l, int r, int p)
{
    if (l == r)
    {
        int u = idA[l], v = idB[l];
        if (son[u])
        {
            if (bo[u])
            {
                int v = son[u];
                tr[p] = matrix(f2[u], sub(q[u], mul(f2[u], q[v])));
            }
            else tr[p] = matrix(f2[u], 0);
        }
        if (v)
        {
            int pa = fa[v];
            if (bo[pa]) sum[p] = sub(q[v], f[v]);
            else sum[p] = f[v];
        }
        return;
    }
    int mid = l + r >> 1;
    build(l, mid, p2);
    build(mid + 1, r, p3);
    tr[p] = tr[p3] + tr[p2];
    sum[p] = mul(sum[p2], sum[p3]);
}

inline void upt_tr(int l, int r, int s, matrix u, int p)
{
    if (l == r)
    {
        tr[p] = u;
        return;
    }
    int mid = l + r >> 1;
    if (s <= mid) upt_tr(l, mid, s, u, p2);
    else upt_tr(mid + 1, r, s, u, p3);
    tr[p] = tr[p3] + tr[p2];
}

inline void upt_sum(int l, int r, int s, int v, int p)
{
    if (l == r)
    {
        sum[p] = v;
        return;
    }
    int mid = l + r >> 1;
    if (s <= mid) upt_sum(l, mid, s, v, p2);
    else upt_sum(mid + 1, r, s, v, p3);
    sum[p] = mul(sum[p2], sum[p3]);
}

inline matrix ask_tr(int l, int r, int s, int t, int p)
{
    if (l == s && r == t) return tr[p];
    int mid = l + r >> 1;
    if (t <= mid) return ask_tr(l, mid, s, t, p2);
    else if (s > mid) return ask_tr(mid + 1, r, s, t, p3);
    else return ask_tr(mid + 1, r, mid + 1, t, p3) + ask_tr(l, mid, s, mid, p2);
}

inline int ask_sum(int l, int r, int s, int t, int p)
{
    if (l == s && r == t) return sum[p];
    int mid = l + r >> 1;
    if (t <= mid) return ask_sum(l, mid, s, t, p2);
    else if (s > mid) return ask_sum(mid + 1, r, s, t, p3);
    else return mul(ask_sum(l, mid, s, mid, p2), ask_sum(mid + 1, r, mid + 1, t, p3));
}

inline void pair_mul(point &u, int x)
{
    if (!x) u.y++;
    else u.x = mul(u.x, x);
}

inline void pair_div(point &u, int x)
{
    if (!x) u.y--;
    else u.x = mul(u.x, ksm(x, mod - 2));
}

inline void cover(int &x, point u)
{
    int res = u.x;
    if (u.y) res = 0;
    x = sub(all, res);
}

inline int calc(int x, matrix c)
{
    return plu(mul(x, c.a), c.b);
}

inline int ask(int x)
{
    if (x == bot[x]) return f[x];
    int l = dfnA[x], r = dfnA[bot[x]] - 1;
    return calc(f[bot[x]], ask_tr(1, n, l, r, 1));
}

inline void change(int x)
{
    pair_div(que[K], sub(q[rt[x]], f[rt[x]]));
    x = top[x];
    while (x)
    {
        f[x] = ask(x);
        if (!fa[x]) break;
        int y = fa[x];
        if (bo[y]) upt_sum(1, n, dfnB[x], sub(q[x], f[x]), 1);
        else upt_sum(1, n, dfnB[x], f[x], 1);
        f2[y] = ask_sum(1, n, st[y], ed[y], 1);
        
        matrix tmp;
        if (bo[y])
        {
            int v = son[y];
            tmp = matrix(f2[y], sub(q[y], mul(f2[y], q[v])));
        }
        else tmp = matrix(f2[y], 0);
        upt_tr(1, n, dfnA[y], tmp, 1);
        
        x = top[y];
    }
    pair_mul(que[K], sub(q[x], f[x]));
}

int main()
{
    freopen("minimax.in", "r", stdin);
    freopen("minimax.out", "w", stdout);
    read(n); read(L); read(R);
    int i, x, y, j;
    for (i = 1; i < n; i++) read(x), read(y), link1(x, y), b[i].x = x, b[i].y = y;
    dfs1(1, 0);
    x = w = val[1];
    h[0] = 1;
    for (i = 1; i <= n; i++) h[i] = plu(h[i - 1], h[i - 1]);
    while (x != 1)
    {
        a[++m] = x;
        x = fa[x];
    }
    a[++m] = 1;
    reverse(a + 1, a + m + 1);
    for (i = 1; i <= m; i++) is[a[i]] = 1;
    for (i = 1; i < n; i++)
    {
        x = b[i].x; y = b[i].y;
        if (!is[x] || !is[y])
        {
            if (fa[x] == y) link2(y, x);
            else link2(x, y);
        }
    }
    for (i = 1; i <= m; i++) now_rt = a[i], dfs3(a[i]);
    all = h[all];
    for (i = 1; i <= n; i++) q[i] = h[cnt[i]];
    for (i = 1; i <= m; i++) dfs4(a[i], a[i]), fa[a[i]] = 0;
    
    bool flag = 0;
    if (L == 1) K = L, flag = 1, L++;
    else K = L - 1;
    que[K].x = 1;
    for (j = 1; j <= m; j++) 
    {
        int u = a[j];
        op = j & 1; dfs2(u);
        pair_mul(que[K], sub(q[u], f[u]));
    }
    cover(ans[K], que[K]);
    build(1, n, 1);
    for (i = L; i <= R; i++)
    {
        que[i] = que[i - 1];
        K = i;
        int lenc = c[i].size(), lend = d[i].size();
        for (j = 0; j < lenc; j++)
        {
            int u = c[i][j];
            f[u] = (u > w) + (u + K > w);
            change(u);
        }
        for (j = 0; j < lend; j++)
        {
            int u = d[i][j];
            f[u] = (u < w) + (u - K < w);
            change(u);
        }
        if (i == n)
        {
            ans[i] = sub(all, 1);
            continue;
        }
        cover(ans[i], que[i]);
    }
    if (flag) L--;
    for (i = L; i <= R; i++) 
    print(sub(ans[i], ans[i - 1])), putchar(i == R ? '\n' : ' ');
    return 0;
}
```

---

## 作者：foreverlasting (赞：0)

[推销博客](https://foreverlasting1202.github.io/)

动态$DP$。

考场上完全没去想这道题。出来后听说这题送了$70$分，然后我还是只会$10$分。是我太菜了对吗。

首先要考虑到根节点的答案一定是一个叶子所传递上来的，所以考虑枚举是哪个叶子传递的。

可以发现的是，若是叶子$x$所传递的，那么从根节点为$x$的链上的所有点的权值都和$x$相同。而这个状态下若要更改根的权值，要么更改这条链上任意一个点的权值，要么把其他点的权值变为和$x$一样。显然更改链上的是最优的。

于是我们只要计算这条链作为答案链时，此时的稳定度一定小于等于当前答案叶子与根节点的差的绝对值，因此只要求出这条链上权值不变的方案数，再用总方案数减去这个方案数就是这条答案链的方案数。

一条链权值不变的方案数显然可以$DP$。然后由于我们每次只用更改一个叶子。于是我们考虑动态$DP$的过程，每一次把要更改的叶子结点暴力修改值，然后像动态$DP$那样子沿着重链往上跳，用线段树维护一下$DP$值，时间复杂度是$O(log^2n\ast (R-L))$。

code:
```cpp
//2019.4.4 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-5
#define RG register
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void swap(res &x,res &y){
    x^=y^=x^=y;
}
const int N=2e5+10;
const int kcz=998244353;
namespace MAIN{
    int pw[N];
    inline void add(res &x,const res &y){
        x+=y,x>=kcz?x-=kcz:(x<0?x+=kcz:1);
    }
    inline int Add(const res &x,const res &y){
        return x+y>=kcz?x+y-kcz:(x+y<0?x+y+kcz:x+y);
    }
    inline int mul(const res &x,const res &y){
        return int(1LL*x*y%kcz);
    }
    int n,L,R;
    struct E{
        int next,to;
        E() {}
        E(res next,res to):next(next),to(to) {}
    }edge[N<<1];
    int head[N],cnt;
    inline void addedge(const res &u,const res &v){
        edge[++cnt]=E(head[u],v),head[u]=cnt;
        edge[++cnt]=E(head[v],u),head[v]=cnt;
    }
    struct Matrix{
        int a,b;
        Matrix() {}
        Matrix(res a,res b):a(a),b(b) {}
    }A[N],tr[N<<2];
    inline Matrix operator * (const Matrix &x,const Matrix &y){
        return Matrix(mul(x.a,y.a),Add(mul(x.a,y.b),x.b));
    }
    int sz[N],val[N],dep[N],son[N],fa[N],top[N],dfn[N],low[N],idx,C[N],pos[N];
    void dfs(res x,res fax,res depx){
        dep[x]=depx,fa[x]=fax,sz[x]=1,val[x]=(dep[x]&1?1:n),C[x]=1;
        RG bool leaf=0;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==fax)continue;
            leaf=1,dfs(tox,x,depx+1),sz[x]+=sz[tox],C[x]=mul(C[x],C[tox]);
            val[x]=(dep[x]&1?max(val[x],val[tox]):min(val[x],val[tox]));
            if(sz[son[x]]<sz[tox])son[x]=tox;
        }
        if(!leaf)val[x]=x,C[x]=2;
        else A[x].b=C[x];
    }
    void dfs(res x,res topx){
        top[x]=topx,dfn[x]=++idx,pos[idx]=x;
        if(son[x])dfs(son[x],topx);
        else low[topx]=idx;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==son[x]||tox==fa[x])continue;
            dfs(tox,tox);
        }
    }
    inline int qpow(res x,res y){
        res ret=1;
        while(y){
            if(y&1)ret=mul(ret,x);
            x=mul(x,x),y>>=1;
        }
        return ret;
    }
    int dp[N],rt[N];
    int Ans=1;
    int Q[N][3];
    bool flag[N];
    void DP(res x,const res &RT){
        rt[x]=RT;
        RG bool leaf=0;
        res ret=kcz-1;
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==fa[x])continue;
            leaf=1,DP(tox,RT);
            if(son[x]!=tox)ret=mul(ret,dp[tox]);
        }
        if(!leaf){
            if(flag[RT]){
                dp[x]=A[x].a=(dep[x]&1)?2-(x<=val[1]):(x<=val[1]);
                if(x<=val[1])Q[val[1]-x][++Q[val[1]-x][0]]=x;
            }
            else {
                dp[x]=A[x].a=(dep[x]&1)?(x>=val[1]):2-(x>=val[1]);
                if(x>=val[1])Q[x-val[1]][++Q[x-val[1]][0]]=x;
            }
            return;
        }
        A[x].a=ret,dp[x]=Add(mul(ret,dp[son[x]]),C[x]);
    }
    void dfs(res x){
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            if(tox==fa[x])continue;
            if(val[x]==val[tox])dfs(tox);
            else dfs(tox,tox),flag[tox]=bool(dep[x]&1),DP(tox,tox),Ans=mul(Ans,dp[tox]);
        }
    }
    void build(res rt,res l,res r){
        if(l==r){tr[rt]=A[pos[l]];return;}
        res mid=(l+r)>>1;
        build(rt<<1,l,mid),build(rt<<1|1,mid+1,r);
        tr[rt]=tr[rt<<1]*tr[rt<<1|1];
    }
    void modify(res rt,res l,res r,res p,res va){
        if(l==r){tr[rt].a=va;return;}
        res mid=(l+r)>>1;
        if(p<=mid)modify(rt<<1,l,mid,p,va);
        else modify(rt<<1|1,mid+1,r,p,va);
        tr[rt]=tr[rt<<1]*tr[rt<<1|1];
    }
    Matrix query(res rt,res l,res r,const res &L,const res &R){
        if(L<=l&&r<=R)return tr[rt];
        res mid=(l+r)>>1;
        if(L<=mid&&R>mid)return query(rt<<1,l,mid,L,R)*query(rt<<1|1,mid+1,r,L,R);
        if(L<=mid)return query(rt<<1,l,mid,L,R);
        if(R>mid)return query(rt<<1|1,mid+1,r,L,R);
    }
    inline void modify(res x){
        res RT=rt[x];
        Ans=mul(Ans,qpow(dp[RT],kcz-2)),modify(1,1,idx,dfn[x],(flag[RT]^(dep[x]&1))?2:0);
        while(top[x]!=RT){
            RG Matrix p=query(1,1,idx,dfn[top[x]],low[top[x]]);
            res od=dp[top[x]],nw=Add(p.a,p.b);
            dp[top[x]]=nw,x=fa[top[x]],A[x].a=mul(mul(A[x].a,qpow(od,kcz-2)),nw);
            modify(1,1,idx,dfn[x],A[x].a);
        }
        RG Matrix p=query(1,1,idx,dfn[RT],low[RT]);
        dp[RT]=Add(p.a,p.b),Ans=mul(Ans,dp[RT]);
    }
    int ans[N];
    inline void MAIN(){
        n=read(),L=read(),R=read(),pw[0]=1;
        for(res i=1;i<=n;i++)head[i]=-1,pw[i]=mul(pw[i-1],2);
        for(res i=1;i<n;i++){
            res u=read(),v=read();
            addedge(u,v);
        }
        dfs(1,0,1),dfs(1),build(1,1,idx),ans[n]=C[1]-1;
        for(res i=n-1;i;i--){
            for(res j=1;j<=Q[i][0];j++)modify(Q[i][j]);
            ans[i]=Add(C[1],-Ans);
        }
        for(res k=L;k<=R;k++)printf("%d ",Add(ans[k],-ans[k-1]));
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

