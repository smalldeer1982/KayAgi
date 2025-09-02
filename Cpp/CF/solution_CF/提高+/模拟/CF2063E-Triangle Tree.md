# Triangle Tree

## 题目描述

某日，一棵巨树在乡间生长。小 John 决定与他的童年伙伴鹰一起将其作为新家。小 John 计划用镀锌方钢在树上建造结构，但他不知道有些结构在物理上无法实现。给定一棵以节点 $1$ 为根、包含 $n$ 个节点的有根树 $^{\text{∗}}$。节点对 $(u,v)$ 被称为好对，当且仅当 $u$ 不是 $v$ 的祖先 $^{\text{†}}$ 且 $v$ 不是 $u$ 的祖先。对于任意两个节点，$\text{dist}(u,v)$ 定义为从 $u$ 到 $v$ 的唯一简单路径的边数，$\text{lca}(u,v)$ 定义为它们的[最低公共祖先](https://en.wikipedia.org/wiki/Lowest_common_ancestor)。

定义函数 $f(u,v)$ 如下：
- 若 $(u,v)$ 是好对，则 $f(u,v)$ 为满足以下条件的整数 $x$ 的数量：存在一个由边长 $\text{dist}(u,\text{lca}(u,v))$、$\text{dist}(v,\text{lca}(u,v))$ 和 $x$ 构成的非退化三角形 $^{\text{‡}}$。
- 否则，$f(u,v) = 0$。

你需要计算以下值：
$$\sum_{i = 1}^{n-1} \sum_{j = i+1}^n f(i,j).$$

$^{\text{∗}}$ 树是无环连通图。有根树是指定一个特殊节点为根的树。

$^{\text{†}}$ 节点 $v$ 的祖先是从 $v$ 到根的简单路径上的所有节点（包含根但不含 $v$ 自身）。根节点没有祖先。

$^{\text{‡}}$ 当边长 $a$、$b$、$c$ 满足 $a+b \gt c$、$a+c \gt b$、$b+c \gt a$ 时，三角形为非退化的。

## 说明/提示

第一个测试用例中，唯一满足 $i<j$ 的好对是 $(2,3)$。此时 $\text{lca}(2,3)=1$，两个距离均为 $1$。对于边长 $1$ 和 $1$，唯一可能的 $x$ 值为 $1$，因此答案为 $1$。

第二个测试用例中没有好对，因此答案为 $0$。

第三个测试用例中，满足 $i<j$ 的好对有：
- $(2,5)$：$\text{lca}(2,5)=1$，距离为 $1$ 和 $1$，$x=1$。
- $(3,4)$：$\text{lca}(3,4)=2$，距离为 $1$ 和 $1$，$x=1$。
- $(3,5)$：$\text{lca}(3,5)=1$，距离为 $2$ 和 $1$，$x=2$。
- $(4,5)$：$\text{lca}(4,5)=1$，距离为 $2$ 和 $1$，$x=2$。
因此答案为 $1+1+1+1=4$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3
1 2
1 3
3
1 2
3 2
5
2 3
1 5
4 2
1 2
11
2 1
2 3
2 4
4 5
6 5
5 7
4 8
8 9
7 10
10 11```

### 输出

```
1
0
4
29```

# 题解

## 作者：cjh20090318 (赞：17)

年级里面有大佬用神奇启发式合并写的，还好我不会这么复杂的算法。

## 题意

给定一棵 $n$ 个点的树。

$\operatorname{dist}(u,v)$ 定义为从 $u$ 到 $v$ 的唯一简单路径上的边数，$\operatorname{lca}(u,v)$ 表示 $u$ 和 $v$ 的最近公共祖先，

设函数 $f(u,v)$ 表示：

- 当 $u$ 不为 $v$ 的祖先，且 $v$ 不为 $u$ 的祖先时，存在多少个整数 $x$ 使得边长为  $\operatorname{dist}(u,\operatorname{lca}(u,v))$ 、 $\operatorname{dist}(v,\operatorname{lca}(u,v))$、$x$ 能成为一个三角形。
- 否则函数值为 $0$。

最后需要求出：

$$
\sum_{i = 1}^{n-1} \sum_{j = i+1}^n f(i,j)
$$

## 分析

根据三角形边长的限制，可以得到：

$$
\vert \operatorname{dist}(u,\operatorname{lca}(u,v)) - \operatorname{dist}(v,\operatorname{lca}(u,v)) \vert < x < \operatorname{dist}(u,\operatorname{lca}(u,v)) + \operatorname{dist}(v,\operatorname{lca}(u,v))
$$

简单来说两边之和大于第三边，两边之差小于第三边。

把距离函数拆成深度，设 $d_u$ 为 $u$ 的深度，$lca = \operatorname{lca}(u,v)$，那么以上式子可以表示为：
$$
\vert d_u - d_v \vert < x < d_u + d_v - 2d_{lca}
$$
然后就可以表示出 $f(u,v)$：
$$
f(u,v) = (d_u + d_v - 2d_{lca}) - \vert d_u -d_v \vert - 1
$$
后面绝对值这一部分是 [[ABC186D] Sum of difference](https://www.luogu.com.cn/problem/AT_abc186_d)，可以把每个深度的个数加入到一个桶中，统计有多少个数比它小或大。

$d_u$ 和 $d_v$ 的求和也是简单的，对于每个点 $u$ 会有 $n-1$ 个询问和他有关，所以对答案的贡献即为 $(n-1)d_u$。

现在考虑这个 $-2d_{lca}$ 如何处理，需要求出有多少对点的最近公共祖先为 $lca$，显然在 $lca$ 两个不同子树内的任意点的最近公共祖先都是它。

设 $sz_u$ 表示 $u$ 的子树大小，$son_u$ 表示 $u$ 的儿子集合，存在点对数即为：

$$
\dfrac 1 2 \sum\limits_{u \in son_{lca}} \sum\limits_{v \in son_{lca} \land v \neq u} sz_u \times sz_v
$$

这个东西可以前缀和优化做到线性。

最后对于每一个询问还需要减 $1$，然后会发现对于$u$ 为 $v$ 的祖先或 $v$ 为 $u$ 的祖先的情况不应该多减，所以加上这一部分就好。

时间复杂度和空间复杂度均为 $O(n)$。

## 代码

```cpp
//the code is from chenjh
#include<bits/stdc++.h>
#define MAXN 300003
using namespace std;
typedef long long LL;
int n;
vector<int> G[MAXN];
LL ans1=0,ans2=0,ans3=0;
int dep[MAXN],sz[MAXN],a[MAXN];
void dfs(const int u,const int FA){
	++a[dep[u]=dep[FA]+1],sz[u]=1;
	ans1+=(n-1ll)*dep[u];
	int x=0;
	LL y=0;//前缀和统计 LCA 为当前点的点对个数。
	for(const int v:G[u])if(v!=FA){
		dfs(v,u),sz[u]+=sz[v];
		y+=(LL)sz[v]*x,x+=sz[v];
	}
	ans1-=2*(y+sz[u]-1)*dep[u],ans3+=sz[u]-1;//减去 2d_{lca}，排除祖先的情况。
}
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) G[i].clear(),a[i]=0;
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		G[u].push_back(v),G[v].push_back(u);
	}
	ans1=ans2=ans3=0;
	dfs(1,0);
	for(int i=1,x=0;i<=n;x+=a[i++]) ans2+=(LL)i*a[i]*(x-(n-a[i]-x));//处理绝对值部分。
	printf("%lld\n",ans1-ans2+ans3-n*(n-1ll)/2);
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：TTpandaS (赞：7)

赛时做完 C 后 5 min 切 E，全球 4 杀，然后因为用的是临时邮箱注册的小号，号被封了，我上早八。

对于一对 $(u,v)$，贡献为 $|dist(u,lca(u,v))+dist(v,lca(u,v))|-|dist(u,lca(u,v))-dist(v,lca(u,v))|+1$，经典绝对值与 $\min,\max$ 互换，等价于 $2 \times \min(dist(u,lca(u,v)),dist(v,lca(u,v)))-1$，考虑先将答案减去 $\dfrac{n\times(n-1)}{2}$，但是成祖先关系的点对不需要减，且成祖先关系的点对数量为 $\sum_{x \in V} dep_x$，加上即可。

剩下就是求 $\sum_{u,v \in V}2 \times \min(dist(u,lca(u,v)),dist(v,lca(u,v)))$，因为 $u,v$ 与 $lca(u,v)$ 成祖先关系，所以 $dist(u,lca(u,v))=dep_u-dep_{lca(u,v)}$，提取出来就是 $\sum_{u,v \in V}2 \times (\min(dep_u,dep_v)-dep_{lca(u,v)})$，所以计算每个点作为 lca 的次数即可，可以通过一个 dfs 解决。对于 $\sum_{u,v \in V}2 \times \min(dep_u,dep_v)$，直接按照 dep 排序，$dep_i$ 贡献次数就是 $n-i$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int T;
int n,ans;
vector<int> g[N];
int siz[N],dep[N];
void dfs(int x,int fa){
	dep[x]=dep[fa]+1,siz[x]=1;
	int sum=1,tot=0;
	for(int y:g[x]){
		if(y==fa) continue;
		dfs(y,x);
		siz[x]+=siz[y],tot+=siz[y]*sum,sum+=siz[y];
	}
	ans-=2*dep[x]*tot;
}
void solve(){
	cin>>n;
	for(int i=1,x,y;i<n;i++){
		cin>>x>>y;
		g[x].push_back(y),g[y].push_back(x);
	}
	ans=-n*(n-1)/2;
	dfs(1,0);
	sort(dep+1,dep+n+1);
	for(int i=1;i<=n;i++){
		ans+=2*dep[i]*(n-i)+(dep[i]-1);
		g[i].clear();
	}
	cout<<ans<<endl;
}
signed main(){
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：Masterwei (赞：7)

赛时最后半小时来打 CF，22：03 分调过样例结果数组忘清空，写篇题解警醒自己。

考虑一对点对 $(u,v)$，设它们的 lca 为 $x$，题目给的三角形的限制其实就是要找所有的 $x$，满足 $|dep_u-dep_v|<x<dep_u+dep_v-2\times dep_x$。

那么一对点对的贡献就是 $dep_u+dep_v-2\times dep_x-|dep_u-dep_v|-1$。

考虑在 lca 处算贡献，于是直接上 dsu on tree。

dsu 的时候套个树状数组，时间是 $O(n\log^2n)$。

两个都是小常数的 $\log$，所以跑的飞快。

没卡常，但最大点还没有 $700ms$。

注意存重儿子的数组要清空。


```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=3e5+5;
int n;
ll ans;
int head[Maxn],to[Maxn<<1],nxt[Maxn<<1],cnt1;
inline void add(int u,int v){
	to[++cnt1]=v;nxt[cnt1]=head[u];
	head[u]=cnt1;
}
struct Tree{
	int cnt;ll sum;
}t[Maxn];
inline void add(int x,int d,int p){
	for(;x<=n;x+=x&-x)t[x].cnt+=d,t[x].sum+=p;
}
inline Tree query(int l,int r){
	Tree res={0,0};
	for(int x=l-1;x;x-=x&-x)res.cnt-=t[x].cnt,res.sum-=t[x].sum;
	for(int x=r;x;x-=x&-x)res.cnt+=t[x].cnt,res.sum+=t[x].sum;
	return res;
}
int si[Maxn],son[Maxn],dfn[Maxn],cnt,b[Maxn],dep[Maxn];
void dfs1(int u,int v){
	dep[u]=dep[v]+1;
	si[u]=1;dfn[u]=++cnt;b[cnt]=u;
	for(int i=head[u];i;i=nxt[i]){
		int y=to[i];if(y==v)continue;
		dfs1(y,u);si[u]+=si[y];
		if(si[son[u]]<si[y])son[u]=y;
	}
}
ll now;
inline void add_(int val,int op){
	Tree tmp=query(1,n);
	now+=op*(tmp.cnt*val+tmp.sum-(query(1,val).cnt*val-query(1,val).sum)-(query(val+1,n).sum-query(val+1,n).cnt*val)-tmp.cnt);
}
void dfs(int u,int v,int op){
	for(int i=head[u];i;i=nxt[i]){
		int y=to[i];if(y==v||son[u]==y)continue;
		dfs(y,u,0);
	}
	if(son[u])dfs(son[u],u,1);
	now=0;
	for(int i=head[u];i;i=nxt[i]){
		int y=to[i];if(y==v||y==son[u])continue;
		for(int j=dfn[y];j<dfn[y]+si[y];j++){
			add_(dep[b[j]],1);
		}
		for(int j=dfn[y];j<dfn[y]+si[y];j++){
			add(dep[b[j]],1,dep[b[j]]);
		}
	}
	int all=0,nw=0;
	for(int i=head[u];i;i=nxt[i]){
		int y=to[i];if(y==v)continue;
		all+=nw*si[y]*2;nw+=si[y];
	}
	ans+=now-all*dep[u];
	add(dep[u],1,dep[u]);
	if(!op){
		for(int i=dfn[u];i<dfn[u]+si[u];i++)add(dep[b[i]],-1,-dep[b[i]]);
	}
}
inline void solve(){
	n=read();cnt1=0;for(int i=1;i<=n;i++)head[i]=0,t[i]={0,0},son[i]=0;
	cnt=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	dfs1(1,0);dfs(1,0,0);
	printf("%lld\n",ans);ans=0;
}
signed main(){
	int T=read();
	while(T--)solve();
	return 0;
}
```

---

## 作者：Nt_Tsumiki (赞：5)

唐诗 DS。

考虑答案到底是个啥，我们令 $d_1=\max\{\text{dis}_{u,\text{lca}},\text{dis}_{v,\text{lca}}\},d_2=\min\{\text{dis}_{u,\text{lca}},\text{dis}_{v,\text{lca}}\}$，那么答案就是 $\sum (d_1+d_2)-(d_1-d_2)-1=\sum 2d_2-1$。

考虑咋算，首先后面跟着的 $1$ 是好算的，在 LCA 处统计答案就行，前面的 $2d_2=2(\min\{\text{dep}_u,\text{dep}_v\}-\text{dep}_{\text{lca}})$，钦定 $\text{dep}_v<\text{dep}_u$ 也就是我们对与每一对合法的 $(u,v)$ 统计 $\text{dep}_v-\text{dep}_{\text{lca}}$，那我们考虑在 $v$ 处统计答案。

直接按 $\text{dep}_u$ 排序，那对于点 $v$ 总共的 $(u,v)$ 对数是 $pos_v-1$ 对，其中也包含不合法的，但是不合法的在计算时一定被消掉了，因为 $\text{LCA}(u,v)=v$，直接不管就行，那么 $\sum \text{dep}_v$ 就解决了，然后对于 $\sum \text{dep}_{\text{lca}}$ 直接考虑 P4211 的链加链求和就做完了。

[submission](https://codeforces.com/contest/2063/submission/302428074)

---

## 作者：hanhoudedidue (赞：5)

### 分析
首先注意到：给定两条边长分别为 $a,b(a<b)$ 的三角形，另外一条边长 $c$ 显然有 $b-a<c<b+a$，取值便为 $2a-1$。即最小值的两倍减一。

再来看题目所求，对于任意两个点，求以这两个点到它们的 LCA 的距离为两条边构成的三角形个数。发现和 LCA 有关，故考虑树上启发式合并。在 LCA 处计算贡献，在枚举该节点其中一棵子树的所有节点时，分两种情况考虑：

（一）：这个节点到当前 LCA 的距离作为最小值时，其贡献即为其它子树内（到当前 LCA 的）距离大于该节点的距离的个数乘上两倍该距离减一。

（二）：这个节点到当前 LCA 的距离作为较大值时，贡献为两倍其它子树内（到当前 LCA 的）距离小于该节点的距离总和减去其它子树内（到当前 LCA 的）距离小于该节点的个数。

使用树状树组维护即可。时间复杂度 $O(n\log^2 n)$。具体实现见代码。

### code：
```cpp
#include<bits/stdc++.h>
#define int long long
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
#define mid ((l+r)>>1)
#define lowbit(x) ((x)&(-x))
using namespace std;
const int N=6e5+5;
int n,m,T;
struct edge{
    int to,nxt;
}a[N];
int h[N],cnt,siz[N],son[N];
void add(int u,int v){
    a[++cnt].to=v;
    a[cnt].nxt=h[u];
    h[u]=cnt;
}
int ans;

int L[N],R[N],rk,rev[N],dep[N];
struct BIT{
    int t[N];
    void add(int x,int sum){
        if(!x) return;
        for(;x<=n;x+=lowbit(x)) t[x]+=sum;
    }
    int query(int x){
        int sum=0;
        for(;x;x-=lowbit(x)) sum+=t[x];
        return sum;
    }
}b1,b2;
void dfs1(int u,int fa){
    siz[u]=1;L[u]=++rk;rev[rk]=u;
    dep[u]=dep[fa]+1;
    for(int i=h[u];i;i=a[i].nxt){
        int v=a[i].to;if(v==fa) continue;
        dfs1(v,u);siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
    R[u]=rk;
    return;
}
void Add(int x){
    b1.add(x,x);
    b2.add(x,1);
}
void Del(int x){
    b1.add(x,-x);
    b2.add(x,-1);
}
int Query(int x,int rt){
    int res=0;
    res+=(b2.query(n)-b2.query(x))*(2*(x-rt)-1);//dis=x-rt
    res+=(2*b1.query(x)-2*b2.query(x)*rt-b2.query(x));//n*(2*(down-rt)-1)
    return res;
}
void dfs2(int u,int fa,bool keep){
    for(int i=h[u];i;i=a[i].nxt){
        int v=a[i].to;if(v==son[u]||v==fa) continue;
        dfs2(v,u,0); 
    }
    if(son[u]) dfs2(son[u],u,1);
    int kk=ans;
    for(int i=h[u];i;i=a[i].nxt){
        int v=a[i].to;if(v==fa||v==son[u]) continue;
        for(int j=L[v];j<=R[v];j++) ans+=Query(dep[rev[j]],dep[u]);
        for(int j=L[v];j<=R[v];j++) Add(dep[rev[j]]);
    }
    // cerr<<u<<':'<<ans-kk<<'\n';
    Add(dep[u]);
    if(!keep){
        for(int i=L[u];i<=R[u];i++) Del(dep[rev[i]]);
    }
}   
void init(){
    for(int i=1;i<=n;i++) b1.t[i]=b2.t[i]=0;
    for(int i=1;i<=n;i++) L[i]=R[i]=rev[i]=dep[i]=0;
    for(int i=1;i<=n;i++) a[i]=edge{0,0},h[i]=siz[i]=son[i]=0;
    rk=cnt=ans=0;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--){
        init();
        cin>>n;
        for(int i=1,u,v;i<n;i++){
            cin>>u>>v;
            add(u,v);add(v,u);
        }
        dfs1(1,0);
        dfs2(1,0,1);
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：linjunye (赞：2)

先考虑如何计算三角形个数。

按照题目意思，我们设已知的两条边（距离）长度为 $x$ 和 $y$，然后求有多少个 $a$，满足三条边能组成一个三角形。

那么我们就假设 $x<y$，这样比较好统计。

那么我们发现，判断是不是三角形，只需计算两条短边和是否大于第三边。

那么，就有两种情况：

- $a$ 是两条短边的其中一条，则 $y$ 是最长边。

- $a$ 是最长边。

计算第一种情况：$a+x>y$ 且 $a\le y$（$a=y$ 的情况不能忽略），解得 $y-x<a\le y$，因为 $x,y$ 均为整数（注意我们假设），所以有 $x$ 种。


计算第二种情况：$x+y>a$ 且 $a> y$，解得 $y<a<x+y$，因为 $x,y$ 均为整数，所以有 $x-1$ 种。

那么，总共有 $2x-1$ 种。

现在再放到一般问题中，发现总共有 $2\min\{x,y\}-1$ 种。

那么，我们可以更新 $f(u,v)$ 的定义了。这里为了简便，我们设 $\text{lca}(u,v)=l$：

- $u$ 是 $v$ 的祖先或 $v$ 是 $u$ 的祖先：$f(u,v)=0$。

- 否则，$f(u,v)=2\min\{dis(u,l),dis(v,l)\}-1$。

我们发现第一种在统计总贡献时忽略不计，所以总和变为（有限制）：

$$
\sum_{u,v}(2\min\{dis(u,l),dis(v,l)\}-1)
$$

注意到这是有限制时的总和，不太好计算，我们想变成无限制时的总和。我们将第一种情况带入第二种情况算一下：发现答案为 $-1$。

那么，我们在算无限制时的总和时，只要加上就可以了。

所以总和变为（无限制）：

$$
\sum_{u,v}(2\min\{dis(u,l),dis(v,l)\}-1)+cnt
$$

其中 $cnt$ 为第一种情况出现的总次数。

$cnt$ 的计算我们先不管，先考虑计算 $\sum_{u,v}(2\min\{dis(u,l),dis(v,l)\}-1)$。

发现这个 $-1$ 比较繁琐，所以移出去，它的总出现次数为 $\frac{n(n-1)}{2}$，所以总和变为：

$$
\sum_{u,v}2\min\{dis(u,l),dis(v,l)\}-\frac{n(n-1)}{2}=2\sum_{u,v}\min\{dis(u,l),dis(v,l)\}-\frac{n(n-1)}{2}
$$

继续考虑计算 $\sum_{u,v}\min\{dis(u,l),dis(v,l)\}$ 的值。

我们可以发掘一个性质：当 $x$ 是 $y$ 的祖先时，$dis(x,y)=dis(y,x)=dep_y-dep_x$。这里的 $dep$ 表示深度，且我们设根的深度为 $1$。

那么就可以变成 $\sum_{u,v}\min\{dep_u-dep_l,dep_v-dep_l\}=(\sum_{u,v}\min\{dep_u,dep_v\}-dep_l)$。

同样的，$dep_l$ 的总和计算先放一边，我们继续计算 $\sum_{u,v}\min\{dep_u,dep_v\}$ 的值。

到这里，已经成为了一个经典问题了。我们可以钦定一个深度 $i$ 为最小值。那么，$i$ 的贡献即为：比 $i$ 大的总数乘 $i$ 的个数，再加上 $i$ 之间两两配对的总和。

形式化的，$\sum_{u,v}\min\{dep_u,dep_v\}=\sum_{i=1}^{n}i(suf_{i+1}tot_i+\frac{tot_i(tot_i-1)}{2})$，这里的 $suf_i=\sum_{j=i}^{n}tot_j$，这里的 $tot_i$ 表示 $dep_x=i$ 的个数。

回溯，我们发现 $dep_l$ 的总和还没有计算。考虑计算它的贡献。

我们发现，只有当 $u,v$ 在 $l$ 的不同子树中，或是其中一个为 $l$ 时，它们的 LCA 才能是 $l$（注意这里算的是无限制）。

那么，总值变为：$\sum_{v}dep_lsiz_v(sum-siz_v)$。这里的 $v$ 为 $l$ 的邻边，且不为父亲。

为什么是 $sum$ 而不是 $dep_l$ 呢？因为两两子树之间只能配对一次，所以这里用 $sum$，具体操作时，先将 $sum=siz_l$，然后计算完一个 $v$ 时就减去 $siz_v$ 即可。

继续回溯，发现最上边还有一个 $cnt$。

如何计算两两之间，一个为祖先，一个为孩子的总个数呢？

有两种方法均可实现：

- 钦定 $u$ 为祖先，则 $cnt=\sum_{i-1}^{n}siz_u-1$。

- 钦定 $u$ 为孩子，则 $cnt=\sum_{i-1}^{n}dep_u-1$。

两种已尝试过，均可行。

这样，我们就做完这道题了，发现是很多的数学转化。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=300010;
vector<int>G[N];
int n;
int f[N];
int siz[N];
int dep[N],cnt[N];
int u,v;
void dfs(int u,int fa){//预处理dep,siz
	f[u]=fa;
	dep[u]=dep[fa]+1;
	siz[u]=1;
	for(auto v:G[u]){
		if(v==fa)continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
	return;
}
void solve(){
	int ans=0;
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)cnt[dep[i]]++;//就是原文的tot
	for(int i=1,sum=n;i<=n;i++){//计算 min(dep_u,dep_v) 总和
		if(!cnt[i])break;//防止错误计算
		sum-=cnt[i];//这里的sum其实就是原文的suf，只是这里用了更加方便的写法
		ans+=i*cnt[i]*sum;
		ans+=i*cnt[i]*(cnt[i]-1)/2;
	}
	ans*=2;//注意原式要*2
	for(int l=1;l<=n;l++){//计算dep_l总和。注意这里的总和也是包含在*2下的
		int sum=siz[l];
		for(auto v:G[l]){
			if(v==f[l])continue;
			ans-=2*dep[l]*(sum-siz[v])*siz[v];//所以要*2
			sum-=siz[v];
		}
	}
	ans-=n*(n-1)/2;//-1总和
	for(int i=1;i<=n;i++)ans+=dep[i]-1;//计算第一种情况的出现次数
	/*
	上面的另一种写法
	for(int i=1;i<=n;i++)ans+=siz[i]-1;
	*/
	cout<<ans<<"\n";
	//清空
	for(int i=1;i<=n;i++)G[i].clear();
	for(int i=1;i<=n;i++)cnt[i]=dep[i]=siz[i]=f[i]=0;
	return;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T=1;
	cin>>T;
	while(T--)solve();
	return 0;
}
```

这道题还是挺不错的。

---

## 作者：ran_qwq (赞：2)

傻人自有傻做法。

首先两条边为 $a,b$ 的三角形（$a\le b$），第三边 $c$ 的取值范围为 $(a-b,a+b)$，有 $2b-1$ 种取值，即只和最小边有关，和最大边无关。

设 $u,v$ 的 $\operatorname{lca}$ 为 $p$。枚举一点 $u$，则如果要使 $\operatorname{dist}(u,p)$ 产生贡献，应保证 $v$ 不在 $u$ 子树内，且  $\operatorname{dep}_v>\operatorname{dep}_u$ 或 $\operatorname{dep}_v=\operatorname{dep}_u$。但后者会算重，我们钦定按 $\operatorname{dep}$ 从大到小扫描线，则之前被扫到的 $v$ 可以计算在内。

限制比较多，子树的限制我们先不管它。我们现在要求的问题是 $\sum\operatorname{dist}(u,\operatorname{lca}(u,p)(u,v))$。

如果做过 P4211，这会非常容易。考虑拆贡献，修改时对 $1\sim u$ 的路径加 $1$，查询时求 $v$ 的个数乘上 $u$ 的深度，减去 $1\sim u$ 的路径和，树剖即可。

现在我们考虑子树的限制。我们惊奇地发现，一个 $u$ 子树内的点，如果这么统计，它对路径和的贡献为 $0$，只是减少了 $v$ 的个数！这是容易的，$v$ 的个数减去 $\operatorname{siz}_u$ 即可。

注意最终要求的是 $2b-1$。

```cpp
int n,m,id,idx,c,hd[N],d[N],sz[N],fa[N],sn[N],tp[N],dfn[N]; vi t[N]; ll as,s;
struct EDGE {int to,ne;} e[N*2];
il void add(int u,int v) {e[++id]={v,hd[u]},hd[u]=id;}
void dfs1(int u,int f) {
	d[u]=d[f]+1,t[d[u]].pb(u),sz[u]=1,fa[u]=f;
	for(int i=hd[u],v;i;i=e[i].ne) if((v=e[i].to)!=f)
		dfs1(v,u),sz[u]+=sz[v],sz[v]>sz[sn[u]]&&(sn[u]=v);
}
void dfs2(int u,int f) {
	tp[u]=f,dfn[u]=++idx; if(sn[u]) dfs2(sn[u],f);
	for(int i=hd[u],v;i;i=e[i].ne) if((v=e[i].to)!=fa[u]&&v!=sn[u]) dfs2(v,v);
}
struct SGT {
	#define ls (id<<1)
	#define rs (id<<1|1)
	#define mid (l+r>>1)
	#define all 1,1,n
	#define cur id,l,r
	#define Ls ls,l,mid
	#define Rs rs,mid+1,r
	int tg[N*4]; ll sm[N*4];
	il void pu(int id) {sm[id]=sm[ls]+sm[rs];}
	il void ad(int id,int l,int r,int k) {tg[id]+=k,sm[id]+=1ll*k*(r-l+1);}
	il void pd(int id,int l,int r) {ad(Ls,tg[id]),ad(Rs,tg[id]),tg[id]=0;}
	void upd(int id,int l,int r,int L,int R,int k) {
		if(L<=l&&r<=R) return ad(id,l,r,k);
		pd(cur),L<=mid?upd(Ls,L,R,k):void(),R>mid?upd(Rs,L,R,k):void(),pu(id);
	}
	ll qry(int id,int l,int r,int L,int R) {
		if(L<=l&&r<=R) return sm[id];
		pd(cur); return (L<=mid?qry(Ls,L,R):0)+(R>mid?qry(Rs,L,R):0);
	}
} sgt;
void upd(int u) {
	for(;tp[u]!=1;) sgt.upd(all,dfn[tp[u]],dfn[u],1),u=fa[tp[u]];
	sgt.upd(all,1,dfn[u],1);
}
ll qry(int u) {
	ll r=0; for(;tp[u]!=1;) r+=sgt.qry(all,dfn[tp[u]],dfn[u]),u=fa[tp[u]];
	return r+sgt.qry(all,1,dfn[u]);
}
void QwQ() {
	n=rd(),id=idx=as=c=s=0;
	for(int i=1;i<=n;i++) hd[i]=d[i]=sz[i]=fa[i]=sn[i]=tp[i]=dfn[i]=0,t[i].clear();
	for(int i=1;i<=n*4;i++) sgt.tg[i]=sgt.sm[i]=0;
	for(int i=1,u,v;i<n;i++) u=rd(),v=rd(),add(u,v),add(v,u);
	dfs1(1,0),dfs2(1,1);
	for(int i=n;i;i--) for(int u:t[i]) as+=1ll*c*i-qry(u),upd(u),c++,s+=c-sz[u];
	wrll(as*2-s,"\n");
}
```

---

## 作者：灵茶山艾府 (赞：2)

设三角形两条边的长度分别为 $a$ 和 $b$，且 $a\le b$。

那么第三条边最短是 $b-a+1$，最长是 $a+b-1$，所以第三条边的整数长度有

$$
(a+b-1) - (b-a+1) +1 = 2a-1
$$

种。

设所有 $a$ 之和为 $\textit{sum}$，所有符合要求的点对个数为 $\textit{pairs}$，那么答案为

$$
2\cdot \textit{sum} - \textit{pairs}
$$

$\textit{pairs}$ 好算，所有点对个数 $\dfrac{n(n-1)}{2}$ 减去不合法的点对个数，也就是每个点与其子树中的其余点的点对个数（子树大小减一）。

接下来计算 $\textit{sum}$。

对于点 $v$ 及其父节点这条边，考虑其贡献。

我们需要知道深度不低于 $v$ 的深度的点的个数。为避免重复计算，只考虑遍历过的点。

在遍历的同时，维护遍历过的节点个数 $\textit{cnt}$，以及每层的节点个数 $\textit{row}[d]$，其中 $d$ 是当前深度。

累加 $\textit{row}[d]$ 可以得到深度低于 $v$ 的节点个数 $\textit{above}$。

设 $v$ 的子树大小为 $\textit{sz}$，那么有 $\textit{cnt} - \textit{above} - \textit{sz}$ 个不在 $v$ 子树且深度不低于 $v$ 的节点。

两两一对，有

$$
\textit{sz} \cdot (\textit{cnt} - \textit{above} - \textit{sz})
$$

个合法点对会经过点 $v$ 及其父节点这条边，这便是点 $v$ 及其父节点这条边，对于 $\textit{sum}$ 的贡献。

AC 代码（Golang）：

```go
package main
import ("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	var T, n, v, w int
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &n)
		g := make([][]int, n+1)
		for range n - 1 {
			Fscan(in, &v, &w)
			g[v] = append(g[v], w)
			g[w] = append(g[w], v)
		}

		sum := 0
		pairs := n * (n - 1) / 2
		cnt := 0 // 遍历过的节点个数
		row := make([]int, n) // 每层的节点个数
		var dfs func(int, int, int, int) int
		dfs = func(v, fa, d, above int) int { // above 为深度低于 d 的节点个数
			cnt++
			row[d]++
			sz := 1 // 子树大小
			for _, w = range g[v] {
				if w != fa {
					sz += dfs(w, v, d+1, above+row[d])
				}
			}
			sum += sz * (cnt - above - sz)
			pairs -= sz - 1
			return sz
		}
		dfs(1, 0, 0, 0)
		Println(sum*2 - pairs)
	}
}
```

**时间复杂度**：$\mathcal{O}(n)$。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)

---

## 作者：JHPOTATO (赞：1)

先只考虑产生贡献的方案。

令 $dis_1=dist(u,lca(u,v)), dis_2=dist(v,lca(u,v))$，且 $dis_1\ge dis_2$，第三边长为 $x$，那么有 $dis_1-dis_2< x< dis_1+dis_2$，容易发现 $x$ 的取值方案有 $2\times dis_2-1$ 种。所以当 $f\left ( u,v \right )\ne  0$ 时，我们可以令 $f\left ( u,v \right )= 2\times  min\left ( dist(u,lca(u,v)),dist(v,lca(u,v)) \right ) -1$。 

首先把 $-1$ 的贡献抽出来，也就是所有的选择方案数，这个跑一遍树形 dp 就可以求出来。

接下来计算出 $\sum_{i=1}^{n}\sum_{j=1}^{n} min\left ( dist(i,lca(i,j)),dist(j,lca(i,j)) \right )$ 即可，$f(i,j),f(j,i)$ 正好算了两次。

这个形式已经可以用启发式合并做了，但我们还可以继续拆贡献。

借第二段中的变量继续分析，如果有 $dis_1>dis_2$ 那么我们完全可以先把 $u$ 向上跳到和 $v$ 相同深度的位置 $u'$ 再统计，可以发现这并不会影响答案，然后我们就可以同时把 $u'$ 和 $v$ 暴力向上跳，每跳一次贡献增加 1，跳到同一点 $\left ( lca(u,v) \right ) $ 时退出即可。

当然，直接暴力枚举点对并暴力跳肯定是不行的，这样还不如用前面推出的式子直接求，但这启示我们，我们可以每次只考虑同一深度的节点，每次处理完一层后把这层的点全部跳到上一层，然后进行相同的操作，这样每个节点只访问一次，时间复杂度是 $O(n)$ 的。

考虑同深度的点的整体贡献，显然一个点与任意一个不同的点之间都能产生贡献。所以我们只需求出当前层点数总和就可以快速计算。

最后的答案要记得除去 $-1$ 的贡献。


```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
void in(T &x){
	char c=getchar(), f=1;
	while ((c<'0' || c>'9') && c!='-') c=getchar();
	if (c=='-') f=-1, c=getchar();
	for (x=0; c>='0' && c<='9'; c=getchar())
		x=x*10+c-'0';
	x*=f;
}
const int N=3e5+5;
struct Node{
	int u,v,nxt;
}a[N*2];
int last[N],cnt,u,v,F[N],sz[N];
void add(int u,int v){
	a[++cnt]={u,v,last[u]};
	last[u]=cnt;
}
int T,n,mxd;
long long ans=0;
vector<int>dep[N];
void dfs(int u,int fa,int depth){
	F[u]=fa;sz[u]=1;
	mxd=max(mxd,depth);
	dep[depth].push_back(u);
	for(int i=last[u];i;i=a[i].nxt){
		int v=a[i].v;
		if(v==fa)continue;
		dfs(v,u,depth+1);
		sz[u]+=sz[v];	
	}
	ans-=n-sz[u]-depth+1;
}
int main(){
//	freopen("E.in","r",stdin);
//	freopen("E.out","w",stdout);
	in(T);
	while(T--){
		in(n);
		for(int i=1;i<=mxd;i++)dep[i].clear();
		for(int i=1;i<=n;i++)last[i]=0;
		cnt=mxd=ans=0;
		for(int i=1;i<n;i++){
			in(u);in(v);
			add(u,v);add(v,u);
		}
		dfs(1,0,1);
		ans/=2;
		for(int i=mxd;i>1;i--){
			int al=0;
			for(auto j:dep[i])al+=sz[j];
			for(auto j:dep[i]){
				if(al==sz[j])break;
				ans+=sz[j]*1ll*(al-sz[j]);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：_wsq_ (赞：1)

求所有点对的 $f$ 之和，一眼树上启发式合并。

三角形两边之和大于第三边，两边之差小于第三边。设 $a=\min(\operatorname{dist}(u,\operatorname{lca}( u,v)),\operatorname{dist}(v,\operatorname{lca}( u,v))),b=\max(\operatorname{dist}(u,\operatorname{lca}( u,v)),\operatorname{dist}(v,\operatorname{lca}( u,v)))$，则答案显然是 $(a+b)-(a-b)-1=a+b-a+b-1=2b-1$。因此我们可以用平衡树维护每个节点到当前节点的距离和平衡树内值在某一段的数之和。那么增加答案时就直接用新加进来的值把平衡树分裂为两部分，一部分用这部分的和更新，另一部分用新加进来的值和这部分的大小更新（这个式子比较复杂，细节见代码第 $71$ 行）。然后还要注意一定要每个子树都更新完答案再统一加入平衡树（否则 $\operatorname{lca}$ 就不是当前节点了），以及重儿子回溯时要将平衡树里所有的节点都加 $1$（可以单开一个变量表示总体的修改）。

代码：

```cpp
#include <iostream>
#include <cstdlib>
using namespace std;
#define maxn 300005
#define int long long
struct edge{
    int to,next;
}e[maxn<<1];
struct node{
    int l,r,siz,pri,val,sum;
}fhq[maxn];
int n,h[maxn],tot,totf,root,sz[maxn],hson[maxn],ans,cnt;
void addedge(int u,int v){
    e[++tot].to=v;
    e[tot].next=h[u];
    h[u]=tot;
    return;
}
void pushup(int x){
    fhq[x].siz=fhq[fhq[x].l].siz+fhq[fhq[x].r].siz+1;
    fhq[x].sum=fhq[fhq[x].l].sum+fhq[fhq[x].r].sum+fhq[x].val;
    return;
}
int newnode(int x){
    fhq[++totf].siz=1;
    fhq[totf].val=x;
    fhq[totf].sum=x;
    fhq[totf].pri=rand();
    return totf;
}
void split(int num,int rt,int &x,int &y){
    if(!rt){
        x=y=0;
        return;
    }
    if(fhq[rt].val<=num){
        x=rt;
        split(num,fhq[x].r,fhq[x].r,y);
    }
    else{
        y=rt;
        split(num,fhq[y].l,x,fhq[y].l);
    }
    pushup(rt);
    return;
}
int merge(int x,int y){
    if(!x||!y){
        return x+y;
    }
    if(fhq[x].pri<fhq[y].pri){
        fhq[x].r=merge(fhq[x].r,y);
        pushup(x);
        return x;
    }
    else{
        fhq[y].l=merge(x,fhq[y].l);
        pushup(y);
        return y;
    }
}
void add(int num){
    int x,y;
    split(num-cnt,root,x,y);
    root=merge(x,merge(newnode(num-cnt),y));
    return;
}
int query(int num){
    int x,y,ret;
    split(num-cnt,root,x,y);
    ret=((fhq[x].sum+cnt*fhq[x].siz)<<1)-fhq[x].siz+fhq[y].siz*((num<<1)-1);//这是代码第 71 行
    root=merge(x,y);
    return ret;
}
void clear(int x){
    if(!x){
        return;
    }
    clear(fhq[x].l);
    clear(fhq[x].r);
    fhq[x].l=0;
    fhq[x].r=0;
    fhq[x].siz=0;
    fhq[x].val=0;
    fhq[x].pri=0;
    fhq[x].sum=0;
    return;
}
void dfs(int x,int fa){
    sz[x]=1;
    hson[x]=0;
    for(int i=h[x];i;i=e[i].next){
        if(e[i].to==fa){
            continue;
        }
        dfs(e[i].to,x);
        sz[x]+=sz[e[i].to];
        if(sz[e[i].to]>sz[hson[x]]){
            hson[x]=e[i].to;
        }
    }
}
void queryl(int x,int fa,int dis){
    ans+=query(dis);
    for(int i=h[x];i;i=e[i].next){
        if(e[i].to==fa){
            continue;
        }
        queryl(e[i].to,x,dis+1);
    }
    return;
}
void addl(int x,int fa,int dis){
    add(dis);
    for(int i=h[x];i;i=e[i].next){
        if(e[i].to==fa){
            continue;
        }
        addl(e[i].to,x,dis+1);
    }
    return;
}
void dsu(int x,int fa,bool typ){
    for(int i=h[x];i;i=e[i].next){
        if(e[i].to==fa||e[i].to==hson[x]){
            continue;
        }
        dsu(e[i].to,x,false);
    }
    if(hson[x]){
        dsu(hson[x],x,true);
    }
    for(int i=h[x];i;i=e[i].next){
        if(e[i].to==fa||e[i].to==hson[x]){
            continue;
        }
        queryl(e[i].to,x,1);
        addl(e[i].to,x,1);
    }
    add(0);
    cnt++;
    if(!typ){
        clear(root);
        root=0;
        totf=0;
        cnt=0;
    }
    return;
}
signed main(){
    int t;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<n;i++){
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }
        dfs(1,0);
        dsu(1,0,false);
        cout<<ans<<'\n';
        for(int i=1;i<=n;i++){
            h[i]=0;
            sz[i]=0;
        }
        tot=0;
        ans=0;
    }
    return 0;
}
```

---

## 作者：hh弟中弟 (赞：1)

设 $dis_{u,lca}=a,dis_{v,lca}=b$，那么这个点对的贡献就是 $2\min(a,b)-1$。\
首先上一个启发式合并，树状数组维护单点加，区间查，然后分类讨论这个点是较小还是较大，去树状数组里查就好了。时间复杂度 $\mathcal{O}(n\log^2 n)$。\
发现这个还是比较唐，其实可以直接线段树合并，然后合并的时候 $\text{pushup}$ 一下贡献就好了。这样的复杂度是 $\mathcal{O}(n\log n)$。

---

## 作者：2huk (赞：1)

一个三角形，两条边是 $a, b$，那么另一条边 $c$ 应满足 $|a-b| < c < a+b$，即取值数为 $(a+b-1) - (|a-b|+1) + 1 = a + b - |a-b| - 1 = 2 \cdot \min(a, b) - 1$。

那么题目中的 $f(u, v)$ 即：

$$
\begin{aligned}
f(u,v) &= 2 \min(dis(u,lca), dis(v,lca))-1 \\
&= 2 (\min(dep_u, dep_v) - dep_{lca})-1
\end{aligned}
$$

考虑怎么统计所有 $f(u,v)$ 的和。分开来看：

- $\sum_{u<v} \min(dep_u, dep_v)$：经典问题。将 $dep$ 从大到小排序后答案为 $\sum_{i=1}^n dep_i (i-1)$。
- $\sum_{u<v} dep_{lca(u,v)}$：枚举 $lca$，那么 $u,v$ 必须从 $lca$ 的两个不同的子树内取。简单乘法原理即可。
- $\sum_{u<v} (-1)$：即 $-\dfrac 12 n(n-1)$。

---

## 作者：zxh923 (赞：1)

# Triangle Tree 题解

[题目传送门](https://www.luogu.com.cn/problem/CF2063E)

### 思路

鉴定为比较套路的拆贡献题。

首先给出一些定义：$s_u$ 表示 $u$ 子树的大小，$d_u$ 表示 $u$ 的深度，$cnt_i$ 表示深度不小于 $i$ 的点的个数，$tot_i$ 表示深度为 $i$ 的点的个数。

然后对于点对 $(u,v)$，设 $p$ 为 $u,v$ 的最近公共祖先，同时我们钦定 $d_u\le d_v$，以找出 $x$ 的取值范围。

显然根据三角形两边之和大于第三边的性质有：$x+d_u-d_p>d_v-d_p$ 以及 $d_u-d_p+d_v-d_p>x$。

移项，合并得：

$$d_v-d_u<x<d_v+d_u-2\times d_p$$

所以 $x$ 的取值有 $2\times d_u-2\times d_p-1$ 种。

于是我们就可以愉快地拆贡献了。

对于 $2\times d_u$，我们只需枚举每个 $u$，然后算出有多少个 $v$。不难发现 $v$ 的个数就是 $cnt_{d_u}-s_u$。

但是有一个问题，如果 $u,v$ 的深度相同，会被多算一次，所以对于每个深度 $i$，会多算 $\binom{tot_i}{2}$ 对。

然后对于 $-1$ 只需算出有多少对合法的 $(u,v)$ 即可，事实上一共有 $\displaystyle\sum_{u=1}^{n}(cnt_{d_u}-s_u)-\sum_{i=1}^{n}\binom{tot_i}{2}$ 对。

最后对于 $-2\times d_p$，我们只需枚举每个 $p$，然后算出有多少对 $(u,v)$。不难发现 $(u,v)$ 的对数就是 $\dfrac{\displaystyle\sum_{v\in son(u)}s_v\times (s_u-1-s_v)}{2}$。

最后把这些东西合到一起并且乘上各自的系数即可。

### 代码


```cpp
#include<bits/stdc++.h> 
#define int long long
#define N 300005
#define pii pair<int,int>
#define x first
#define y second
#define pct __builtin_popcount
#define mod 998244353
#define inf 1e18
#define pi acos(-1)
#define eps 1e-8
using namespace std;
int T=1,n,d[N],s[N],cnt[N],fa[N];
vector<int>e[N];
void add(int a,int b){
	e[a].push_back(b);
}
void dfs(int u,int f){
	s[u]=1;
	d[u]=d[f]+1;
	fa[u]=f;
	cnt[d[u]]++;
	for(auto j:e[u]){
		if(j==f)continue;
		dfs(j,u);
		s[u]+=s[j];
	}
}
void solve(int cs){
	cin>>n;
	for(int i=1;i<=n;i++){
		e[i].clear();
		cnt[i]=0;
	}
	for(int i=1;i<n;i++){
		int a,b;
		cin>>a>>b;
		add(a,b);add(b,a);
	}
	dfs(1,0);
	cnt[n+1]=0;
	for(int i=n;i;i--){
		cnt[i]+=cnt[i+1];
	}
	int res=0;
	int all=0;
	for(int i=1;i<=n;i++){
		res+=2*d[i]*(cnt[d[i]]-s[i]);
		all+=cnt[d[i]]-s[i];
	}
	for(int i=1;i<=n;i++){
		int sum=s[i]-1;
		for(auto j:e[i]){
			if(j==fa[i])continue;
			/*
			res-=2*d[i]*s[j]*(sum-s[j]);
			sum-=s[j];
			这样写也是对的 
			*/
			res-=2*d[i]*s[j]*(sum-s[j])/2;
		}
	}
	for(int i=1;i<=n;i++){
		int tot=cnt[i]-cnt[i+1];
		all-=tot*(tot-1)/2;
		res-=2*i*tot*(tot-1)/2;
	}
	cout<<res-all<<'\n';
}
void solution(){
    /*
    nothing here
    */
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
//	init();
	cin>>T;
    for(int cs=1;cs<=T;cs++){
        solve(cs);
    }
    return 0; 
}
```

---

## 作者：Iniaugoty (赞：1)

### [CF2063E Triangle Tree](/problem/CF2063E)

大炮轰蚊子。

前置知识：**线段树合并**或**长链剖分**，~~[[NOI2020] 命运](/problem/P6773) 或 [[十二省联考 2019] 希望](/problem/P5291)~~。

考虑三角形两条边 $a, b(a \le b)$，则第三边 $x$ 需要满足 $b - a < x < b + a$，于是有 $(b + a) - (b - a) - 1 = 2a - 1$ 个。

设 $u$ 子树内深度为 $i$ 的结点数量为 $f _ {u, i}$，$f _ u$ 的后缀和为 $h _ u$，则

$$f _ {u, i} = [dep _ u = i] + \sum _ {v \in \operatorname {son} (u)} f _ {v, i}$$

当 LCA 为 $u$ 时对答案的贡献为：

$$\sum _ {v, w \in \operatorname {son} (u), v \neq w} \sum _ {i = 1} ^ {n} (2i - 2dep _ u - 1) (f _ {v, i} h _ {w, i} + f _ {w, i} h _ {v, i + 1})$$

可以**线段树合并**（这里还需要维护一个区间深度和），在合并的过程中统计答案（类似 [[PKUWC2018] Minimax](/problem/P5298)），时空复杂度都为 $O(n \log n)$，[代码](https://codeforces.com/contest/2063/submission/302437220)。

有关深度的信息也可以**长链剖分**（这里用树状数组维护动态后缀和），在暴力添加短儿子贡献时统计答案，相比线段树合并在空间上少了个 $\log n$，~~细节多一车~~，先不写了。

---

## 作者：Unnamed114514 (赞：1)

枚举 LCA，这样就能钦定 LCA 的深度，考虑使用 DSU on Tree 求解。

在这种情况下，不同子树内的两点显然都是有贡献的，根据三角形两边之和大于第三边，两边之差小于第三边，有：

$$|(dep_u-dep_{LCA})-(dep_v-dep_{LCA})|=|dep_u-dep_v|<x<dep_u+dep_v-2dep_{LCA}$$

那么方案数为 $dep_u+dep_v-2dep_{LCA}-|dep_u-dep_v|-1$。

考虑拆绝对值：

- $dep_u\ge dep_v$：式子为 $2dep_v-2dep_{LCA}-1$，此时我们对于每个点，需要维护 $dep$ 比它小的数量和这些数的和。

- $dep_u<dep_v$：式子为 $2dep_u-2dep_{LCA}-1$，此时我们只需要维护 $dep$ 比它大的数的数量。

容易发现，使用树状数组维护即可通过。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=3e5+5;
int T,n,ans,c1[N],c2[N],dep[N],fa[N],siz[N],son[N];
vector<int> G[N];
void dfs(int u){
	siz[u]=1,son[u]=0;
	for(auto v:G[u]){
		if(v==fa[u]) continue;
		fa[v]=u,dep[v]=dep[u]+1;
		dfs(v);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
int lowbit(int x){ return x&-x; }
void add1(int x,int y){ for(;x<=n;x+=lowbit(x)) c1[x]+=y; }
int ask1(int x){ int s=0; for(;x;x-=lowbit(x)) s+=c1[x]; return s; }
void add2(int x,int y){ for(;x<=n;x+=lowbit(x)) c2[x]+=y; }
int ask2(int x){ int s=0; for(;x;x-=lowbit(x)) s+=c2[x]; return s; }
void clear(int u){
	add1(dep[u],-1),add2(dep[u],-dep[u]);
	for(auto v:G[u]){
		if(v==fa[u]) continue;
		clear(v);
	}
}
void update(int u){
	add1(dep[u],1),add2(dep[u],dep[u]);
	for(auto v:G[u]){
		if(v==fa[u]) continue;
		update(v);
	}
}
void solve(int u,int k){
	int a=ask1(dep[u]),b=ask2(dep[u]);
	ans+=(2*b-a*(2*k+1));
	a=ask1(n)-a;
	ans+=(2*a*dep[u]-a*(2*k+1));
	for(auto v:G[u]){
		if(v==fa[u]) continue;
		solve(v,k);
	}
}
void DSU(int u){
	for(auto v:G[u]){
		if(v==fa[u]||v==son[u]) continue;
		DSU(v);
		clear(v);
	}
	if(son[u]){
		DSU(son[u]);
		for(auto v:G[u]){
			if(v==fa[u]||v==son[u]) continue;
			solve(v,dep[u]);
			update(v);
		}
	}
	add1(dep[u],1),add2(dep[u],dep[u]);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1,u,v;i<n;++i){
			cin>>u>>v;
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		dep[1]=1,dfs(1);
		ans=0;
		DSU(1);
		cout<<ans<<endl;
		clear(1);
		for(int i=1;i<=n;++i) G[i].clear(),G[i].shrink_to_fit();
	}
	return 0;
}
```

---

## 作者：ZeroOf149 (赞：0)

# [CF2063E Triangle Tree](https://www.luogu.com.cn/problem/CF2063E)

可能是所有题解里面最无脑的一篇。

## 题目描述

给一棵有根树，根为 $1$。  
定义 $f(u, v)$ 为能够与 $\operatorname{dist}(u, \operatorname{lca}(u, v)), \operatorname{dist}(\operatorname{lca}(u, v), v)$ 组成三角形的整数的个数，求所有无祖先关系的无序数对 $\{u, v\}$ 对应的 $f(u, v)$ 的和。

## 解法说明

这里约定 $dep_{u}$ 是 $u$ 的深度（$dep_{1} = 1$），$siz_{u}$ 是 $u$ 为根的子树的大小。

如果整数 $x, a, b$ 能组成三角形，这说明 $|a-b| < x < a + b$，整数 $x$ 的取值有 $\max\{a + b - |a - b| - 1, 0\}$ 种。注意到这里 $a + b - |a - b| = 2\min\{a, b\} > 1$，因此 $f(u, v) = 2\min\{\operatorname{dist}(u, \operatorname{lca}(u, v)), \operatorname{dist}(\operatorname{lca}(u, v), v)\} - 1 = 2\min\{dep_{u}, dep_{v}\} - 2dep_{\operatorname{lca}(u, v)} - 1$。 

我们分开考虑此式子：  

$-1$ 会在每一个 $f(u, v)$ 里面出现一次，因此这一项对答案的贡献是所有无祖先关系的无序数对 $\{u, v\}$ 的个数的相反数，我们可以对每个 $u$ 计满足要求的 $v$ 的个数（$n - dep_{u} - siz_{u} + 1$），求和并除以二即可；  

每组无祖先关系的无序数对 $\{u, v\}$ 都对 $\min\{dep_{u}, dep_{v}\}$ 的系数产生 $2$ 的贡献，$dep_{\operatorname{lca}(u, v)}$ 的系数产生 $-2$ 的贡献。  

前者等价于对每个有序数对 $(u, v)$，当 $dep_{u} < dep_{v}$ 时对 $dep_{u}$ 的系数产生 $2$ 的贡献，当 $dep_{u} = dep_{v}$ 时对 $dep_{u}$ 的系数产生 $1$ 的贡献，否则无贡献；  
后者等价于以 $u$ 为 LCA 的无序点对个数 $l_{u}$，其相反数是对 $dep_{u}$ 的贡献，这可以通过容斥或前缀和优化实现。  

于是我们数出深度为数组下标的节点个数 $\{d_{n}\}$，与其后缀和 $\{d'_{n}\}$（$d'_{n+1} = 0$），节点 $u$ 对答案贡献为 $dep_{u}[2(d'_{dep{u}+1}-siz_{u}+1)+d_{dep_{u}}-1-l_{u}]$，最后求和即可。

## 代码实现
```cpp
#include <cstdio>
#include <vector>

using ll = long long;

constexpr int N = 3e5 + 5;

int T, n, dep[N], siz[N], cnt[N], pcnt[N];
ll lcnt[N], sum, kcnt;
std::vector<int> g[N];

void dfs(int u, int f) {
  dep[u] = dep[f] + 1;
  siz[u] = 1;
  lcnt[u] = 0;
  for (auto&& v : g[u])
    if (v != f) {
      dfs(v, u);
      siz[u] += siz[v];
      lcnt[u] -= siz[v] * (siz[v] - 1ll);
    }
  lcnt[u] += (siz[u] - 1ll) * (siz[u] - 2);
  kcnt += n - dep[u] - siz[u] + 1;
  ++cnt[dep[u]];
}

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      g[i].clear();
      cnt[i] = 0;
    }
    sum = kcnt = 0;
    for (int i = 1; i < n; ++i) {
      int u, v;
      scanf("%d %d", &u, &v);
      g[u].push_back(v);
      g[v].push_back(u);
    }
    dfs(1, 0);
    pcnt[n + 1] = 0;
    for (int i = n + 1; --i;) pcnt[i] = pcnt[i + 1] + cnt[i];
    for (int i = 1; i <= n; ++i)
      sum += dep[i] * (2ll * (pcnt[dep[i] + 1] - siz[i]) + cnt[dep[i]] + 1 - lcnt[i]);
    printf("%lld\n", sum - (kcnt >> 1));
  }
}
```

---

## 作者：RainWetPeopleStart (赞：0)

赛时写了 1h，没救了。

首先发现对于合法的对 $(x,y)$，有 $|dis_{x,lca}-dis_{y,lca}|<x<dis_{x,lca}+dis_{y,lca}$，枚举 LCA 的位置就可以使用 dsu on tree 和 BIT 做到 $O(n\log^2n)$，我赛时就写的这个。

赛后发现这个题可以 $O(n)$。

具体的，算原式的值较困难，改为算原式的 2 倍的值，因为 $f(u,u)=0$，故原式的 2 倍为 $\sum\limits_{i=1}^n\sum\limits_{j=1}^nf(i,j)$。

下记 $d_u$ 表示 $u$ 节点的深度。

在转化一下上文的式子，对于合法的对 $(x,y)$，有 $|d_x-d_y|<x<d_x+d_y-2d_{lca}$。

由此可得，$(x,y)$ 合法时，$f(x,y)=d_x+d_y-2d_{lca}-|d_x-d_y|-1$，否则 $f(x,y)=0=d_x+d_y-2d_{lca}-|d_x-d_y|$。

考虑拆贡献，对于 $d_x+d_y$ 部分，可以转化为 $2n\sum\limits_{i=1}^nd_i$。

对于 $d_{lca}$ 部分，考虑求出 $f_u$ 表示 lca 为 $u$ 的 $(x,y)$ 对数。

这个可以容斥算，$f_u=siz^2_u-\sum\limits_{i\in son_u}siz_i^2$。（$son_u$ 表示 $u$ 的子节点集合，$siz_u$ 表示以 $u$ 为根的子树大小）

则 $d_{lca}$ 的贡献为 $-2\sum\limits_{i=1}^nf_ud_u$。

对于 $|d_x-d_y|$ 部分，先把绝对值拆掉，然后枚举 $x$。

这时，我们需要求两个序列 $s1,s2$。其中 $s1_x=\sum\limits_{i=1}^n[d_i=x]$，$s2_x=\sum\limits_{i=1}^ni[d_i=x]$。

此时就可以算了，对于一个 $x$ 而言，$d_y\le d_x$ 的情况可以表示为 $\sum\limits_{i=1}^{d_x}(d_xs1_i-s2_i)$，$d_y>d_x$ 的情况可以表示为 $\sum\limits_{i=d_x+1}^n(s2_i-d_xs1_i)$，这两者都可以使用前缀和 $O(1)$ 算。

最后，对于 $-1/-0$ 部分，相当于求合法的 $(x,y)$ 的对数，发现不合法的 $(x,y)$ 对数是好求的，枚举 $x$，$y$ 是 $x$ 的祖先或 $x$ 子树内的点，因此，不合法的 $y$ 的数量是 $d_x+siz_x-1$，最后稍微容斥一下就行，复杂度 $O(n)$。

感谢 pretest 28。

代码：

赛后代码（$O(n)$）：


```cpp
#include<bits/stdc++.h>
#define vi vector<int>
#define vl vector<ll>
#define ll long long 
using namespace std;
const int N=3e5+10;
int n;
vi E[N];
int sz[N],h[N],dep[N];
void dfs(int u,int fa){
	sz[u]=1;dep[u]=dep[fa]+1;
	for(auto v:E[u]){
		if(v==fa) continue;
		dfs(v,u);sz[u]+=sz[v];
	}
}ll calc(int x){
	ll res=1ll*sz[x]*sz[x];
	for(auto ed:E[x]){
		if(sz[ed]>sz[x]) continue;
		res-=1ll*sz[ed]*sz[ed];
	}return res;
}
ll s1[N],s2[N];
void slv(){
	cin>>n;
	for(int i=1;i<=n;i++) E[i].clear(),s1[i]=0,s2[i]=0;
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		E[u].push_back(v);
		E[v].push_back(u);
	}dfs(1,0);
	for(int i=1;i<=n;i++) s1[dep[i]]++,s2[dep[i]]+=dep[i];
	for(int i=1;i<=n;i++) s1[i]+=s1[i-1],s2[i]+=s2[i-1];
	ll ans=2*n*s2[n];
	for(int i=1;i<=n;i++) ans-=2ll*calc(i)*dep[i];
	for(int i=1;i<=n;i++) ans-=s1[dep[i]]*dep[i]-s2[dep[i]]+(s2[n]-s2[dep[i]])-(s1[n]-s1[dep[i]])*dep[i];
	ans-=1ll*n*n;for(int i=1;i<=n;i++) ans+=sz[i]+dep[i]-1;
	cout<<ans/2<<endl;
}
int main(){
	int t;cin>>t;while(t--) slv();
	return 0;
}
```


赛时代码（$O(n\log^2n)$）：

```cpp
#include<bits/stdc++.h>
#define vi vector<int>
#define vl vector<ll>
#define ll long long 
using namespace std;
const int N=3e5+10;
int n;
struct bit{
	ll T[N];
	int lb(int x){return x&(-x);}
	void upd(int x,ll v){
		for(int i=x;i<=n;i+=lb(i)) T[i]+=v;
	}ll qry(int x){
		ll res=0;for(int i=x;i>0;i-=lb(i)) res+=T[i];return res;
	}
}b1,b2;
vi E[N];vi p,p2;
int sz[N],h[N],dep[N];
void dfs1(int u,int fa){
	sz[u]=1;dep[u]=dep[fa]+1;
	int mxs=0,mxid=0;
	for(auto v:E[u]){
		if(v==fa) continue;
		dfs1(v,u);
		sz[u]+=sz[v];
		if(sz[v]>mxs) mxs=sz[v],mxid=v;
	}h[u]=mxid;
}ll ans=0;
void clear(){
	while(!p.empty()){
		int x=p.back();p.pop_back();
		b1.upd(x,-1);b2.upd(x,-x);
	}
}
void dfss(int u,int fa,int d){
	int du=dep[u]-d;
	ll al=b1.qry(n),als=b2.qry(n);
	ll ad=b1.qry(dep[u]),ads=b2.qry(dep[u]);
	ll ao=al-ad,aos=als-ads;
	//cout<<al<<' '<<als<<' '<<u<<endl;
	ans+=al*(d-1-du)+als-(ad*(d+du)-ads)-(aos-ao*(d+du));
	//cout<<ad<<' '<<ads<<' '<<ans<<endl; 
	p2.push_back(dep[u]);
	for(auto v:E[u]){
		if(v==fa) continue;
		dfss(v,u,d+1);
	}
}void ins(){
	while(!p2.empty()){
		int x=p2.back();p2.pop_back();
		p.push_back(x);
		b1.upd(x,1);b2.upd(x,x);
	} 
}
void dfs2(int u,int fa){
	for(auto v:E[u]){
		if(v==fa||v==h[u]) continue;
		clear();dfs2(v,u);
	}clear();
	if(h[u]) dfs2(h[u],u);
	//cout<<ans<<' '<<u<<endl;
	for(auto v:E[u]){
		if(v==fa||v==h[u]) continue;
		dfss(v,u,1);ins();
		//cout<<ans<<' '<<u<<' '<<v<<endl;
	}p2.push_back(dep[u]);ins();
}
void slv(){
	ans=0;p.clear();p2.clear();
	cin>>n;
	for(int i=1;i<=n;i++) E[i].clear(),b1.T[i]=0,b2.T[i]=0;
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		E[u].push_back(v);
		E[v].push_back(u);
	}dfs1(1,0);dfs2(1,0);
	cout<<ans<<endl;
}
int main(){
	int t;cin>>t;while(t--) slv();
	return 0;
}
```

---

## 作者：UniGravity (赞：0)

感觉是很妙妙的一种线性做法。

首先考虑 $f(x,y)$ 等于什么，记 $a=\max(dist(x,lca(x,y)),dist(y,lca(x,y))),b=\min(dist(x,lca(x,y)),dist(y,lca(x,y)))$，那么另一边 $c$ 的取值范围是 $a-b<c<a+b$，共 $a+b-(a-b)-1=2b-1$ 种取法。

考虑对于某个数 $x$，只有当匹配的 $y$ 深度大于 $x$（等于时会被算两遍，所以另外处理）且 $y$ 不在 $x$ 子树内。此时的贡献就是 $2dist(x,lca(x,y))-1=2(dep_x-dep_{lca(x,y)})-1=2dep_x-2dep_{lca(x,y)}-1$。

对于这个式子拆贡献。首先发现减去 $1$ 的个数就是所有合法对的数目，等于 $\frac{n^2-\sum_i dep_i+siz_i-1}2$（所有有祖先关系的点）

然后是 $-2dep_{lca(x,y)}$ 变成求子树内有多少个跨越自己的合法对，直接在 dfs 时和前面的子树大小匹配即可。

最后的 $2dep_x$ 需要记录一下 $cnt1_x$ 表示**全部**深度大于等于 $x$ 的数量，然后再加上 $cnt2_x$ 表示**当前**深度等于 $x$ 的，这样保证了相同深度不会算重。

```cpp
const int N=300005;
int n,dep[N],cnt[N],cnt2[N],siz[N];ll tot[N];
vector<int>e[N];
il void dfs(int x,int fa){
    dep[x]=dep[fa]+1,cnt[dep[x]]++,siz[x]=0,tot[x]=0;
    for(int y:e[x])if(y!=fa){
        dfs(y,x),tot[x]+=1ll*siz[x]*siz[y],siz[x]+=siz[y];
    }
    siz[x]++;
}
il void work(){
    n=read();forto(i,0,n+1)e[i].clear(),cnt[i]=cnt2[i]=0;
    int u,v;
    forto(i,2,n){
        u=read(),v=read();
        e[u].eb(v),e[v].eb(u);
    }
    dfs(1,0);
    ll cnt1=1ll*n*n;forto(i,1,n)cnt1-=dep[i]+siz[i]-1;cnt1/=2;
    ll ans=-cnt1;
    forto(i,1,n)ans-=2ll*tot[i]*dep[i];
    forbk(i,n,1)cnt[i]+=cnt[i+1];
    forto(i,1,n)ans+=2ll*dep[i]*(cnt[dep[i]+1]-siz[i]+1+cnt2[dep[i]]),cnt2[dep[i]]++;
    printf("%lld\n",ans);
}
```

---

## 作者：Fishing_Boat (赞：0)

根据三角形三边关系：
$$
f(u,v)=dist(u,\operatorname{lca}(u,v))+dist(v,\operatorname{lca}(u,v))-1-|dist(u,\operatorname{lca}(u,v))-dist(v,\operatorname{lca}(u,v))|
$$
化简得：
$$
f(u,v)=2\min\{dist(u,\operatorname{lca}(u,v)),dist(v,\operatorname{lca}(u,v))\}-1
$$
发现只与点到最近公共祖先的距离有关，直接上长链剖分。

记 $f_{u,i}$ 表示以 $u$ 为跟的子树中，距离 $u$ 为 $i$ 的点的个数。

每次合并时暴力算出 $1$ 到 $d_v$ 的 $\sum\limits_{i} f_{u,i}$ 和 $\sum\limits_{i} (2f_{u,i}-1)$，其中 $d_v$ 表示以 $v$ 为根的子树的最大深度。

时间复杂度 $O(n)$。[submission](https://codeforces.com/contest/2063/submission/302554899)

---

