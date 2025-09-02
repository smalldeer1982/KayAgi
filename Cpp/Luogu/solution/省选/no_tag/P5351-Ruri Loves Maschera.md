# Ruri Loves Maschera

## 题目背景


琉璃最近沉迷于《Maschera》的二次创作。

## 题目描述

琉璃小说中的世界有 $n$ 座城市，其中有 $n-1$ 条道路，不包含重边、自环。这 $n-1$ 条道路中，第 $i$ 条道路的魔力值为 $w_i$。

琉璃作为夜魔女王，她决定要观光整个黑暗世界 。她每次会随机选一个城市为起点，经过不少于 $L$ 条且不多于 $R$ 条道路后在一个城市为终点结束。**她在观光的时候是不走回头路的。**若琉璃每次观光中经过道路的魔力值依次为 $v_1,v_2,...,v_k(L\leq k\leq R)$，那么她会获得 $\max(v_1,v_2,...,v_k)$ 的魔力值。

现在琉璃想知道，她尝试了所有合法的观光路线后，她所获得的魔力值总和为多少。

**注意，$x$ 到 $y$ 的路径和 $y$ 到 $x$ 的路径视为两条路径。**

## 说明/提示

数据范围：

对于 $10\%$ 的数据，$n\leq 5000$

另有 $10\%$ 的数据，$\min(x,y)=1$

另有 $15\%$ 的数据，$|x-y|=1$

另有 $25\%$ 的数据，$L=1,R=n-1$

对于 $100\%$ 的数据，$n\leq 10^5,1\leq L\leq R\leq n-1,1\leq w_i\leq 10^5$

## 样例 #1

### 输入

```
5 2 3
1 2 2
2 3 2
3 4 4
4 5 5```

### 输出

```
40```

# 题解

## 作者：mrsrz (赞：6)

点分治+树状数组即可。

树上的路径统计问题，很容易想到点分治。

每次分治的时候，我们对当前连通块，求出所有从根出发的路径的价值。

然后考虑如何合并这些链。

我们把所有的链按照其魔力值排序，然后从小到大枚举。对每条链，设其魔力值为$w$，它与其之前枚举到的链产生的贡献均为$w$。用树状数组来支持单点修改、区间查询，然后对每条链，在树状数组上查询之前有多少满足边数限制的链即可。然后再把这条链放进树状数组里。

注意减去同一棵子树内的贡献。

答案最后乘2即可。

时间复杂度$O(n\log^2 n)$。

## Code：
```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
const int N=1e5+7;
typedef long long LL;
LL ans;
int n,L,R;
struct edge{
	int to,nxt,w;
}e[N<<1];
int head[N],cnt,mx[N],sz[N],all,rt,vis[N];
void getrt(int now,int pre){
	mx[now]=0,sz[now]=1;
	for(int i=head[now];i;i=e[i].nxt)
	if(!vis[e[i].to]&&e[i].to!=pre)getrt(e[i].to,now),sz[now]+=sz[e[i].to],mx[now]=std::max(mx[now],sz[e[i].to]);
	mx[now]=std::max(mx[now],all-sz[now]);
	if(!rt||mx[now]<mx[rt])rt=now;
}
int B[N];
inline void add(int i,int x){for(;i<=R;i+=i&-i)B[i]+=x;}
inline int ask(int i){int x=0;for(;i;i^=i&-i)x+=B[i];return x;}
std::vector<std::pair<int,int>>al,tt;
void dfs(int now,int pre,int len,int val){
	tt.emplace_back(val,len);
	if(len<R)
	for(int i=head[now];i;i=e[i].nxt)
	if(e[i].to!=pre&&!vis[e[i].to])dfs(e[i].to,now,len+1,std::max(val,e[i].w));
}
void doit(int now){
	al.clear();
	for(int i=head[now];i;i=e[i].nxt)if(!vis[e[i].to]){
		tt.clear();
		dfs(e[i].to,now,1,e[i].w);
		std::sort(tt.begin(),tt.end());
		for(int t=0;t<tt.size();++t)
		ans-=(LL)tt[t].first*(ask(R-tt[t].second)-ask(std::max(0,L-tt[t].second-1))),add(tt[t].second,1);
		for(int t=0;t<tt.size();++t)add(tt[t].second,-1);
		for(auto t:tt)al.push_back(t);
	}
	std::sort(al.begin(),al.end());
	for(int t=0;t<al.size();++t)
	ans+=(LL)al[t].first*(ask(R-al[t].second)-ask(std::max(0,L-al[t].second-1))),add(al[t].second,1);
	for(int t=0;t<al.size();++t)add(al[t].second,-1);
	for(auto t:al)
	if(t.second>=L)ans+=t.first;
}
void solve(int now){
	vis[now]=1,doit(now);
	const int sm=all;
	for(int i=head[now];i;i=e[i].nxt)if(!vis[e[i].to]){
		rt=0;
		all=sz[e[i].to]<sz[now]?sz[e[i].to]:sm-sz[now];
		getrt(e[i].to,now),solve(rt);
	}
}
int main(){
	scanf("%d%d%d",&n,&L,&R);
	for(int i=1;i<n;++i){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e[++cnt]=(edge){v,head[u],w},head[u]=cnt;
		e[++cnt]=(edge){u,head[v],w},head[v]=cnt;
	}
	rt=0,all=n;
	getrt(1,0),solve(rt);
	printf("%lld\n",ans<<1);
	return 0;
}
```

---

## 作者：Owen_codeisking (赞：5)

$Ruri\ Loves\ Maschera$ 题解

这是 $Owen$ 自己出的。。。虽然超级像原题，但是是原创。。。

不少于 $L$ 条且不多于 $R$ 条的话可以想到点分治。我们在点分治记录两个值，一个是深度 $dep$，一个是该点到重心的最大值 $Max$。现在考虑怎么合并两个最大值。

我们先不管路径条数的限制。有 $n$ 个价值 $a_1\leq a_2\leq ...\leq a_n$，现在求 $\sum_{i=1}^{n}\max(a_i,v)$。

先找到一个数 $k$，使得 $a_k\leq v,a_{k+1}>v$。$[1,k]$ 的贡献为 $v\times k$，$[k+1,n]$ 的贡献为 $\sum_{i=k+1}^{n}a_i$

那么我们再加一维深度，对于每个点，只有  $L-dep_a\leq dep_b\leq R-dep_a$ 的值会对其产生贡献。所以我们将其转化为二维偏序问题，一维 $sort$ 一维用树状数组维护，时间复杂度 $O(n\log^2 n)$

---

## 作者：szhqwq (赞：3)

## $\tt{Solution}$

套路与 [P7283](https://www.luogu.com.cn/problem/P7283) 相同。

可以使用点分治套树状数组解决问题。

对于一条长度为 $l$ 的链，其价值 $w$ 为所经过的边的权值的**最大值**，题目要求满足条件 $L \le l \le R$ 的链的条数。首先将存下来的链根据 $w$ 从小到大排序，我们去考虑有多少条链能够与之合并，相当于去查找此前的链中满足 $L \le l + l'\le R$ 的个数，可以使用树状数组维护。

这样就是一个二维偏序问题，第一维 $w$ 排序处理，第二维在树状数组中查找满足条件的链的个数。

注意处理同一个子树里计算重复的情况，需要单独在统计一个子树内的链时减去。

题目中 $(x,y)$ 与 $(y,x)$ 为不同情况，所以最后答案乘 $2$ 即可。

```cpp
const int N = 1e6 + 10,inf = 1e9,mod = 998244353;
const ll inff = 1e18;
int n,L,R,rt,sum;
int h[N],e[N],ne[N],w[N],idx;
PII dd[N]; int cnt;
int mx[N],siz[N],dist[N]; 
bool vis[N]; int res;
PII aa[N]; int cc;
struct BIT {
    int tr[N];
    il int lowbit(int x) { return  x & -x; }

    il void add(int x,int k) {
        for (; x <= n; x += lowbit(x)) tr[x] += k;
    }

    il int ask(int x) {
        if (x < 0) x = 0;
        int res = 0;
        for (; x; x -= lowbit(x)) res += tr[x];
        return res;
    }
} bit;

il void add(int a,int b,int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx ++;
}

il void calcsiz(int u,int fa) {
    siz[u] = 1;
    mx[u] = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa || vis[j]) continue;
        calcsiz(j,u);
        chmax(mx[u],siz[j]);
        siz[u] += siz[j];
    }
    chmax(mx[u],sum - siz[u]);
    if (mx[u] < mx[rt]) rt = u;
}

il void calcdist(int u,int fa,int nowdis) {
    dd[++ cnt] = {dist[u],nowdis};
    if (nowdis >= R) return ;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa || vis[j]) continue;
        dist[j] = max(dist[u],w[i]);
        calcdist(j,u,nowdis + 1);
    }
}

il void calcans(int u) {
    cc = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (vis[j]) continue;
        cnt = 0; dist[j] = w[i]; calcdist(j,u,1);
        sort(dd + 1,dd + cnt + 1);
        rep(i,1,cnt) {
            res -= dd[i].fst * (bit.ask(R - dd[i].snd) - bit.ask(L - dd[i].snd - 1));
            bit.add(dd[i].snd,1);
        }
        rep(i,1,cnt) bit.add(dd[i].snd,-1),aa[++ cc] = dd[i];
        // cout << res << endl;
    }
    sort(aa + 1,aa + cc + 1);
    rep(i,1,cc) {
        res += aa[i].fst * (bit.ask(R - aa[i].snd) - bit.ask(L - aa[i].snd - 1));
        bit.add(aa[i].snd,1);
    }
    rep(i,1,cc) {
        if (aa[i].snd >= L) res += aa[i].fst;
        bit.add(aa[i].snd,-1);
    }
}

il void dfz(int u) {
    vis[u] = 1;
    calcans(u);
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (vis[j]) continue;
        mx[0] = inff;
        rt = 0; sum = siz[j];
        calcsiz(j,0);
        dfz(rt);
    }
}

il void solve() {
    //------------code------------
    memset(h,-1,sizeof h);
    read(n,L,R);
    rep(i,1,n - 1) {
        int a,b,c; read(a,b,c);
        add(a,b,c); add(b,a,c);
    }
    mx[0] = n; rt = 0; sum = n;
    calcsiz(1,0);
    dfz(rt);
    write(res << 1,'\n');
    return ;
}
```

---

## 作者：fzitb7912 (赞：3)

## 分析

考虑点分治。

将每条路径从重心断开分成两条子路径。若 $(x,y)$ 合法，则有：$L \le k1+k2 \le R$。将子路径边权最大值从小到大排序，就相当于求一个 $L-k2 \le k1 \le R-k2$ 的子路径数量，然后这条子路径的贡献就是 $cnt \times \max(v1,v2,\dots,v_{k2})$ 了。这个直接树状数组就行，复杂度是 $O(n \log^2 n)$ 的。

注：记得减去在同一棵子树中的两条子路径的情况和加上单独一条合法子路径的情况。

## 代码

```cpp
const int N=2e5+10;
int n,L,R;
int ne[N],e[N],h[N],w[N],idx;
int max_p[N],siz[N];
int root,Siz;
bool vis[N];
int ans;
vector<pii> v1,v2;
int tr[N];

il void add(int x,int y){
	while(x<N) tr[x]+=y,x+=x&(-x);
}
il int query(int x){
	int sum=0;
	while(x) sum+=tr[x],x-=x&(-x);
	return sum;
}
il bool cmp(pii a,pii b){
	return a.x<b.x;
}
il void add(int a,int b,int c){
	ne[++idx]=h[a],e[idx]=b,w[idx]=c,h[a]=idx;
	ne[++idx]=h[b],e[idx]=a,w[idx]=c,h[b]=idx;
}
il void dfs(int now,int fa,int dis,int Max){
	if(dis<=R)
		v2.push_back({Max,dis}),
		ans+=(dis>=L?Max:0);
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa||vis[j]) continue;
		if(dis+1<=R) dfs(j,now,dis+1,max(Max,w[i]));
	}
	return ;
}
il void calc(int now){
	v1.clear();
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(vis[j]) continue;
		v2.clear(),dfs(j,now,1,w[i]);
		sort(v2.begin(),v2.end(),cmp);
		for(auto x:v2){
			int sum;
			if(x.y>=L&&x.y<=R){
				sum=query(R-x.y);
				ans-=sum*x.x;
			}
			else if(x.y<=R){
				sum=query(R-x.y)-query(L-x.y-1);
				ans-=sum*x.x;
			}
			add(x.y,1);
		}
		for(auto x:v2){
			add(x.y,-1);
			v1.push_back(x);
		}
	}
	sort(v1.begin(),v1.end(),cmp);
	for(auto x:v1){
		if(x.y>=L&&x.y<=R){
			int sum=query(R-x.y);
			ans+=sum*x.x;
		}
		else if(x.y<=R){
			int sum=query(R-x.y)-query(L-x.y-1);
			ans+=sum*x.x;
		}
		add(x.y,1);
	}
	for(auto x:v2) add(x.y,-1);
	return ;
}
il void find(int now,int fa){
	siz[now]=1,max_p[now]=0;
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa||vis[j]) continue;
		find(j,now),siz[now]+=siz[j];
		max_p[now]=max(max_p[now],siz[j]);	
	}
	max_p[now]=max(max_p[now],Siz-siz[now]);
	if(max_p[root]>max_p[now]) root=now;
	return ;
}
il void work(int now){
	vis[now]=1,calc(now);
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(vis[j]) continue;
		Siz=siz[j],root=0,find(j,0);
		work(root);
	}
	return ;
}

il void solve(){
	n=rd,L=rd,R=rd;
	for(re int i=1,a,b,c;i<n;++i)
		a=rd,b=rd,c=rd,
		add(a,b,c);
	vis[0]=1,max_p[0]=n,root=0,Siz=n,find(1,0);
	work(root),printf("%lld\n",ans*2);
	return ;
}
```

---

## 作者：cccgift (赞：3)

# 第一篇$C++$题解（好伤心，告别$pascal$）

看到了“不少于$L$条且不多于$R$条道路”，又是求路径价值和，想到的也只有点分治了。

我认真看完了题目，发现这道题和[P4178 Tree](https://www.luogu.org/problemnew/show/P4178)非常像，P4178就是令$v[i]=1$的情况。

于是，我们把那道题的代码抄过来，改一下，就可以得到一个暴力代码，我用的是指针扫描数组法：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define int long long
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
template<typename T>
inline void read(T &x)
{
    static char ch;int f=1;
    for(x=0,ch=getchar();!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(;isdigit(ch);x=(x<<1)+(x<<3)+(ch^48),ch=getchar());x*=f;
}
struct node{
    int jia,point;
} c[100001];
int ver[200001],head[200001],edge[200001],nxt[200001],n,m,x,y,z,maxx,de[100001],minn,len[100001],len1,tot,gen,ans,L,R,tot1,k,s[100001];
bool vis[100001];
inline bool cmp(node x,node y) {return x.jia<y.jia;}
void dfs1(int x,int fa) { //求子树节点数量 
    len[x]=1;
    for(res i=head[x];i;i=nxt[i]) {
        if(vis[ver[i]]||ver[i]==fa) continue;
        dfs1(ver[i],x),len[x]+=len[ver[i]];
    }
}
void dfs2(int x,int fa,int tot) { //求树的重心 
    int max1=0;
    for(res i=head[x];i;i=nxt[i]) {
        if(vis[ver[i]]||ver[i]==fa) continue;
        max1=max(max1,len[ver[i]]),dfs2(ver[i],x,tot);
    }
    max1=max(max1,tot-len[x]);if(max1<minn) minn=max1,gen=x;
}
void dfs3(int x,int fa,int deep) { //这个dfs用来处理距离和魔法值
    de[x]=deep;
    for(res i=head[x];i;i=nxt[i]) if(ver[i]!=fa&&!vis[ver[i]]) dfs3(ver[i],x,max(deep,edge[i]));
}
void dfs4(int x,int fa,int tot) {
    if(tot>k) return;
    c[++len1].jia=tot,c[len1].point=x;
    for(res i=head[x];i;i=nxt[i]) if(ver[i]!=fa&&!vis[ver[i]]) dfs4(ver[i],x,tot+1);
}
inline void query(int x,int dat,int id) {
    memset(s,0,sizeof(s));
    len1=0,dfs4(x,0,dat),sort(c+1,c+1+len1,cmp);res l=1,r=len1;
//	for(res i=1;i<=len1;++i) printf("%lld %lld %lld ",c[i].jia,c[i].point,de[c[i].point]);puts("");
    while(l<r) if(c[l].jia+c[r].jia<=k) {
        for(res i=l+1;i<=r;++i) //注意这里扫描的边界，这就要看点分治是否学了进去
        if(k==R) tot+=id*max(de[c[i].point],de[c[l].point]);
        else tot1+=id*max(de[c[i].point],de[c[l].point]);
        ++l;
    }
    else --r;
}
void dianfenzhi(int x) { //点分治
    minn=1e9,dfs1(x,0),dfs2(x,0,len[x]),vis[x=gen]=true,dfs3(x,0,0),query(x,0,1);
    for(res i=head[x];i;i=nxt[i]) if(!vis[ver[i]]) query(ver[i],1,-1);
    for(res i=head[x];i;i=nxt[i]) if(!vis[ver[i]]) dianfenzhi(ver[i]);
}
inline void add(int x,int y,int z) {ver[++ans]=y,nxt[ans]=head[x],head[x]=ans,edge[ans]=z;}
signed main()
{
    read(n),read(L),read(R);
    for(res i=1;i<n;++i) read(x),read(y),read(z),add(x,y,z),add(y,x,z);
    k=R,dianfenzhi(1),k=L-1,memset(vis,false,sizeof(vis)),dianfenzhi(1); //注意初始化，一次dfs过后vis未清零会死的很惨
//    printf("%lld %lld\n",tot,tot1);
    printf("%lld",(tot-tot1)<<1);
    return 0;
}
```

然后我满怀信心地交了上去……

## 全部$TLE$!

很快我们会发现，P4178中扫描数组时，可以$O(1)$计算价值，然而本题中，$max(de[c[l].point],de[c[i].point])$不可能$O(1)$求出，于是，最后的时间复杂度为$O(n^2logn)$，连最小的数据都过不去。

接下来我们考虑优化。

对于目前点分治到的每一个根节点，计算出其余节点到它的距离和魔法值，然后把它们按照魔法值排序，然后从左到右依次考虑每一个节点。

我们发现，对于每一个节点，它的左边的节点与它构成的路径所能获得的魔力值就是它本身！同理，它的右边的节点所能获得的魔力值就是它的右边的节点的魔力值。

于是，我们用树状数组维护出现次数和魔法值，再加上指针扫描数组，就可以得出一个$O(nlog^2n)$的算法（虽然我这辈子第一次听说点分治中树状数组能和指针扫描一起使用的……）

注：这里的指针扫描数组并不是二分版，所以时间复杂度并不是$O(nlog^3n)$。

### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define int long long
#define lowbit(x) (x&(-x))
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
template<typename T>
inline void read(T &x)
{
    static char ch;int f=1;
    for(x=0,ch=getchar();!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(;isdigit(ch);x=(x<<1)+(x<<3)+(ch^48),ch=getchar());x*=f;
}
struct node{
    int jia,point;
} c[100001];
int ver[200001],head[200001],edge[200001],nxt[200001],n,m,x,y,z,maxx,de[100001],minn,len[100001],len1,tot,gen,ans,L,R,tot1,k,c1[100001],c2[100001],max2;
bool vis[100001];
inline bool cmp(node x,node y) {return x.jia<y.jia||(x.jia==y.jia&&de[x.point]<de[y.point]);}
void dfs1(int x,int fa) { //求子树节点数量 
    len[x]=1;
    for(res i=head[x];i;i=nxt[i]) {
        if(vis[ver[i]]||ver[i]==fa) continue;
        dfs1(ver[i],x),len[x]+=len[ver[i]];
    }
}
void dfs2(int x,int fa,int tot) { //求树的重心 
    int max1=0;
    for(res i=head[x];i;i=nxt[i]) {
        if(vis[ver[i]]||ver[i]==fa) continue;
        max1=max(max1,len[ver[i]]),dfs2(ver[i],x,tot);
    }
    max1=max(max1,tot-len[x]);if(max1<minn) minn=max1,gen=x;
}
void dfs3(int x,int fa,int deep) {
    de[x]=deep;
    for(res i=head[x];i;i=nxt[i]) if(ver[i]!=fa&&!vis[ver[i]]) dfs3(ver[i],x,max(deep,edge[i]));
}
void dfs4(int x,int fa,int tot) {
    if(tot>R) return;
    c[++len1].jia=tot,c[len1].point=x;
    for(res i=head[x];i;i=nxt[i]) if(ver[i]!=fa&&!vis[ver[i]]) dfs4(ver[i],x,tot+1);
}
inline void modify(int x,int y) {if(!x) ++x;for(res i=x;i<=max2;i+=lowbit(i)) c1[i]+=y,c2[i]+=x*y;} //注意树状数组得维护两个值，c1表示值出现的次数，c2表示魔法值*出现次数。
inline int ask(int x) {
    int tot1=0,tot2=0;
    for(res i=max2;i;i^=lowbit(i)) tot2+=c2[i];
    for(res i=x;i;i^=lowbit(i)) tot1+=c1[i],tot2-=c2[i];
    return tot1*x+tot2; //tot1*x表示该数左边，tot2表示该数右边
}
inline void query(int x,int dat,int id) {
    len1=0,dfs4(x,0,dat),sort(c+1,c+1+len1,cmp);res l=len1+1,r=len1,tot1=0;
//	for(res i=1;i<=len1;++i) printf("%lld %lld %lld ",c[i].jia,c[i].point,de[c[i].point]);puts(""); 
    for(res i=1;i<=len1;++i) { //这里用树状数组维护指针扫描
//    	printf("pre=%lld\n",tot);
    	while(l>1&&c[i].jia+c[l-1].jia>=L) modify(de[c[--l].point],1);
    	while(r>=1&&c[i].jia+c[r].jia>R) modify(de[c[r--].point],-1);
//    	printf("between=%lld\n",tot);
    	tot1+=ask(de[c[i].point]);
//    	printf("now=%lld\n",tot);
    }
    while(l<=r) modify(de[c[r--].point],-1); //清空树状数组，极其重要！我就因为这个调了很久很久
//	memset(c1,0,sizeof(long long)*(max2+1));
//	memset(c2,0,sizeof(long long)*(max2+1));
    tot+=tot1*id;
}
void dianfenzhi(int x) {
    minn=1e18,dfs1(x,0),dfs2(x,0,len[x]),vis[x=gen]=true,dfs3(x,0,0);
    for(res i=head[x];i;i=nxt[i]) if(!vis[ver[i]]) query(ver[i],1,-1);query(x,0,1);
    for(res i=head[x];i;i=nxt[i]) if(!vis[ver[i]]) dianfenzhi(ver[i]);
}
inline void add(int x,int y,int z) {ver[++ans]=y,nxt[ans]=head[x],head[x]=ans,edge[ans]=z;}
signed main()
{
    read(n),read(L),read(R);
    for(res i=1;i<n;++i) read(x),read(y),read(z),add(x,y,z),add(y,x,z),max2=max(max2,z);
    dianfenzhi(1);
//    printf("%lld %lld\n",tot,tot1);
    printf("%lld",tot);
    return 0;
}
```

---

## 作者：zzxLLL (赞：2)


点分治 + 树套树，$n \log^3 n$ 过 $10^5$。

---

树上路径问题，考虑点分治。

假设现在分治中心为 $u$，求经过 $u$ 的所有路径的贡献。

对于在 $u$ 的不同子树的两个点 $x, y$，设其与 $u$ 间的距离为 $dep_x, dep_y$，如果 $L \leq dep_x + dep_y \leq R$ 那么点对 $(x, y)$ 将造成 $\max(mx_x, mx_y)$，其中 $mx_x, mx_y$ 代表 $x, y$ 到 $u$ 的路径上的最大值。

考虑枚举点 $x$，统计所有的 $y$ 的贡献。对于这些 $y$ 又分成两类：$mx_y > mx_x$ 和 $mx_y \leq mx_x$。对于第一类，贡献是 $\sum mx_y$。对于第二类，设这样的 $y$ 共有 $t$ 个，那么答案就是 $t \cdot mx_x$。

于是就变成了一个二维数点问题，即 $L - dep_x \leq dep_y \leq R - dep_x$ 与 $mx_y, mx_x$ 的大小关系。

这个时候当然可以用容斥 + 树状数组，但是也可以无脑树套树。

直接开两颗树状数组套权值线段树，一棵维护权值和，另一颗维护数量（其实可以合并成一棵）。对于所有节点 $x$，先在树套树上查询所有点 $y$ 的贡献，然后将 $(mx_x, dep_x)$ 插入树套树中即可。

时间复杂度 $O(n \log^3 n)$，喜提 $20pts$ 的高分。

考虑怎么优化这个东西。

首先是数组大小，内层线段树的大小只需要开到 $10^6$ 即可，可以 $20pts \to 40pts$。

其次注意到每层分治完都要清空树套树，非常的耗时间。其实只需要将内层线段树的节点个数直接置 $0$，这样清空一次就是一只 $\log$ 的，可以 $40pts \to 85pts$。

再注意到深度 $> R$ 的点不会造成贡献，直接不统计这类点即可。

内层线段树也不必要开太大。对于每层的分治，开到下最深的深度即可。这样就可以得到 $100pts$。

还有一个比较玄学的，就是树状数组的写法。

```cpp
// 1
inline void add(int x, int y, int v) {
    for (; x <= V; x += l(x)) T.add(c[x], 0, n - 1, y, v);
}
inline long long qry(int l1, int r1, int l2, int r2) {
    long long ret = 0;
    for (int i = r1; i; i -= l(i)) ret += T.qry(c[i], 0, n - 1, l2, r2);
    for (int i = l1 - 1; i; i -= l(i)) ret -= T.qry(c[i], 0, n - 1, l2, r2);
    return ret;
}

// 2
inline void add(int x, int y, int v) {
    for (; x; x -= l(x)) T.add(c[x], 0, mxdep, y, v);
}
inline long long qry(int l1, int r1, int l2, int r2) {
    long long ret = 0;
    for (int i = l1; i <= V; i += l(i)) ret += T.qry(c[i], 0, mxdep, l2, r2);
    for (int i = r1 + 1; i <= V; i += l(i)) ret -= T.qry(c[i], 0, mxdep, l2, r2);
    return ret;
}
```

一种是前缀和式的，一种是后缀和式的。前者跑了 $12.48s$，后者跑了 $6.96s$，差距非常大。不知道什么原因。

写丑了的代码：

```cpp
const int M = 1e5 + 10, V = 100000;

int n, L, R;
std::vector<std::pair<int, int> >g[M];

bool vis[M];
int totsiz, minsiz, center, siz[M];
inline void getcenter(int u, int fa) {
	siz[u] = 1;
	int tmp = 0;
	for (auto E : g[u]) {
		int v = E.first;
		if (v == fa || vis[v]) continue;
		getcenter(v, u);
		siz[u] += siz[v];
		tmp = std::max(tmp, siz[v]);
	}
	tmp = std::max(tmp, totsiz - siz[u]);
	if (tmp < minsiz) minsiz = tmp, center = u;
}

int mxdep;
inline void getsize(int u, int fa, int dep) {
	siz[u] = 1, mxdep = std::max(mxdep, dep);
	for (auto E : g[u]) {
		int v = E.first;
		if (v == fa || vis[v]) continue;
		getsize(v, u, dep + 1), siz[u] += siz[v];
	}
}

struct Tree_In_Tree {
    
} t0, t1;

long long ans;
int dep[M], mxw[M];
std::vector<int>pt;
inline void dfs(int u, int mx, int fa) {
	dep[u] = dep[fa] + 1, mxw[u] = mx;
	if (dep[u] > R) return;
	pt.push_back(u);
	for (auto E : g[u]) {
		int v = E.first;
		if (v == fa || vis[v]) continue;
		dfs(v, std::max(mx, E.second), u);
	}
}

std::vector<std::pair<int, int> >rec;
inline void solve(int u) {
	mxdep = 0;
	getsize(u, 0, 0);
	if (siz[u] == 1) return;
	dep[u] = mxw[u] = 0, vis[u] = true;
	std::vector<std::pair<int, int> >().swap(rec);

	long long dlt = 0;
	for (auto E : g[u]) {
		int v = E.first;
		if (vis[v]) continue;
		std::vector<int>().swap(pt);
		dfs(v, E.second, u);

		for (int x : pt) {
			if (dep[x] > R) continue;
			long long con = 0;
			if (dep[x] >= L) con += mxw[x];
			con += t1.qry(1, mxw[x], std::max(L - dep[x], 0), R - dep[x]) * mxw[x];
			con += t0.qry(mxw[x] + 1, V, std::max(L - dep[x], 0), R - dep[x]);
			dlt += con;
		}
		for (int x : pt) {
			if (dep[x] > R) continue;
			t0.add(mxw[x], dep[x], mxw[x]);
			t1.add(mxw[x], dep[x], 1);
			rec.push_back({mxw[x], dep[x]});
		}
	}
	t0.T.tot = t1.T.tot = 0;
	for (auto p : rec)
		for (int i = p.first; i <= V; i += (i & -i)) t0.c[i] = t1.c[i] = 0;
	ans += dlt;

	for (auto E : g[u]) {
		int v = E.first;
		if (vis[v]) continue;
		totsiz = siz[v], minsiz = 233333333;
		getcenter(v, u), solve(center);
	}
}
```

---

## 作者：zhenglier (赞：2)

## 前置知识：~~淀粉质~~点分治

据出题人说：看到这种树上询问路径长度为L~R的信息的，肯定是点分治.

~~据出题人说:这道题是一道码农题，最开始还要套个K-D树。~~

先思考$O(n^2)$的算法（暴力），发现没什么好优化的。

再思考$O(n^2logn)$的点分治算法（可能会有人觉得复杂度变大了，但先别急），就是对于每个点出发的所有边都两两暴力拼接，判断是否满足答案，这复杂度是错误的（但出题人说$O(n^2logn)$能的10pts）。

再一看，我们可以发现，对于每一条长度为$l$的边，只有长度在$(L-l)$~$(R-l)$的所有边能成为答案。由我们设长度小于当前边的边才会对当前边产生贡献，因此可以将所有边排序一遍，然后用树状数组维护就行了。

但如果两条边再同一棵子树中，这个贡献是多余的，所以最后要对每个子树再跑一遍，在答案中减去，以保证正确性。

因为合并时我已经假设小于当前边的边才会有贡献，所以答案要乘2再输出。

数据好像比较水（没有什么**菊花图加链加完全二叉树**），我开始好像用了一个有点错误的算法水了过去？

```cpp#include<bits/stdc++.h>
#define res register int
#define ll long long
using namespace std;
const int N=100010;
int L,R,n,k;
inline int read(){
    int ret=0;char c;
    for(c=getchar();!isdigit(c);c=getchar());
    for(;isdigit(c);ret=ret*10+c-'0',c=getchar());
    return ret;
}
struct BIT{
    ll tr[N];
    void add(int x,ll z){
        if(x==0){tr[0]+=z;return;}
        for(;x<N;x+=x&-x)tr[x]+=z;
    }
    ll query(int x){
        if(x<0)return 0;
        if(x==0)return tr[0];
        ll ret=0;
        for(;x;x-=x&-x)ret+=tr[x];
        return ret;
    }
    void clear(int x){
        if(x==0){tr[0]=0;return;}
        for(;x<N;x+=x&-x)tr[x]=0;
    }
}tr;
int tot,bian[N<<1],nxt[N<<1],zhi[N<<1],head[N];
inline void add(int x,int y,int z){
    tot++,bian[tot]=y,zhi[tot]=z,nxt[tot]=head[x],head[x]=tot;
}
int S,v[N],sz[N],mx[N],root;
void getroot(int x,int f){
    sz[x]=1,mx[x]=0;
    for(res i=head[x];i;i=nxt[i]){
        res y=bian[i];
        if(f==y||v[y])continue;
        getroot(y,x);
        sz[x]+=sz[y];
        mx[x]=max(mx[x],sz[y]);
    }
    mx[x]=max(mx[x],S-sz[x]);
    if(mx[x]<mx[root]){
        root=x;
    }
}
void getsize(int x,int f){
    sz[x]=1;
    for(res i=head[x];i;i=nxt[i]){
        res y=bian[i];
        if(v[y]||y==f)continue;
        getsize(y,x);
        sz[x]+=sz[y];
    }
}
long long ans;
struct data{
    int l,now,trnum;
    data(int l=0,int now=0,int trnum=0):l(l),now(now),trnum(trnum){};
};
bool operator<(const data&x,const data&y){
    if(x.now!=y.now)return x.now<y.now;
    return x.l<y.l;
}
bool cmp(const data&x,const data&y){
    if(x.trnum!=y.trnum)return x.trnum<y.trnum;
    return x.now<y.now;
}
vector<data>q;
int trcnt;
void dfs1(int x,int f,int now,int l){
    q.push_back(data(l,now,trcnt));
    if(L<=l&&l<=R)ans+=now;
    for(int i=head[x];i;i=nxt[i]){
        int y=bian[i];
        if(y==f||v[y])continue;
        dfs1(y,x,max(now,zhi[i]),l+1);
    }
}
void solve(int x,int f,int pre){
    q.clear();
    getsize(x,f);
    v[x]=1;trcnt=0;
    for(int i=head[x];i;i=nxt[i]){
        int y=bian[i];
        if(v[y]||y==f)continue;
        trcnt++;
        dfs1(y,x,zhi[i],1);
    }
    sort(q.begin(),q.end());
    for(int len=q.size(),i=0;i<len;++i){
        ans+=1ll*(tr.query(R-q[i].l)-tr.query(L-q[i].l-1))*q[i].now;
        tr.add(q[i].l,1);
    }
    for(int len=q.size(),i=0;i<len;++i){
        tr.clear(q[i].l);
    }
    sort(q.begin(),q.end(),cmp);
    for(int now=0,i=head[x];i;i=nxt[i]){
        int y=bian[i];
        if(v[y]||y==f)continue;
        sort(&q[now],&q[now+sz[y]]);
        for(int j=now;j<now+sz[y];++j){
            ans-=1ll*(tr.query(R-q[j].l)-tr.query(L-q[j].l-1))*q[j].now;
            tr.add(q[j].l,1);
        }
        for(int j=now;j<now+sz[y];++j){
            tr.clear(q[j].l);
        }
        now+=sz[y];
    }
    for(res i=head[x];i;i=nxt[i]){
        res y=bian[i];
        if(y==f||v[y])continue;
        root=0;
        S=sz[x]>sz[y]?sz[y]:pre-sz[x];
        getroot(y,0);
        solve(root,0,S);
    }
}
int main(){
    cin>>n>>L>>R;
    for(res i=1;i<n;++i){
    	res x=read(),y=read(),z=read();
        add(x,y,z);
        add(y,x,z);
    }
    mx[0]=1e9;
    S=n;
    getroot(1,0);
    solve(root,0,n);
    cout<<ans*2<<endl;
}
```

---

## 作者：rfsfreffr (赞：1)

来自一位刚学点分治的萌新的题解，希望能对你有帮助。

我们定义 $val_{i,j}=\max \{v_1,v_2,v_3,...,v_k \}$ ，即 $i \to j$ 路径的魔力值， $d_{i,j}$ 为 $i \to j$ 上的边数。

题意即求: $\sum val_{i,j}[L\le d_{i,j} \le R]$

相当于，每一对点对都有一个权值，求满足某一条件的所有点对的权值和。

这样就很自然的可以开始考虑使用点分治。

设我们当前选取的根节点 (即原树重心) 是 $rt$。记 $mx_u=val_{u,rt},k_u=d_{u,rt}$, 这样对于每一个点 $u$ 到 $rt$ 的路径就可以表示成一个二元组 $(mx_u,k_u)$。

考虑如何合并。

假如我们现在有俩条路径 $(mx_u,k_u), (mx_v,k_v)$ ，他们合并后的路径就是 $(\max\ \{mx_u,mx_v \},k_u+k_v)$。

我们可以考虑算贡献，因为每一条路径对答案的贡献都是 $\max \{mx_u,mx_v \}$ ,可以找到有多少 $mx_v$ 比 $mx_u$ 小，设有 $t$ 个，这样 $mx_u$ 对答案的贡献就是 $k *mx_u$。

唉等等，现在我们好像只需要考虑一个**二维偏序**问题了。

先**不考虑**俩个点在 $rt$ 同一个的子节点的子树内情况，我们对于每一个  $(mx_u,k_u)$ 要找都有多少个 $(mx_v,k_v)$ 满足条件: 

$mx_v\le mx_u$  且 $L-k_u\le k_v \le R-k_u$

可以对 $mx$ 进行排序，然后树状数组维护 $k$ 即可。

但是如果我们采用合并子树的做法，相当于每一次都需要重新排序，复杂度会炸，考虑可加性问题可以整个算完后再减去子树内多算的贡献来解决。

这一部分实现也是很简单的，可以直接看代码即可。

# Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=1e5+5;

struct oi {
	int to;
	int w;
	int id;
};

struct oi2 {
	int mx;
	int k;
};

oi2 p[N];
int cnt;
vector<oi> b[N];
int n,L,R;
int sz,new_rt;
int minn;
int ans=0;
int mx[N];
int k[N];
int siz[N];
int vis[N];
int c[N*2];

void read() {
	cin>>n>>L>>R;
	for(int i=1; i<=n-1; i++) {
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		b[u].push_back({v,w,i});
		b[v].push_back({u,w,i});
	}
}

void dfs(int u,int fa) {
	siz[u]=1;
	int maxn=0;
	for(int i=0; i<b[u].size(); i++) {
		int v=b[u][i].to;
		int id=b[u][i].id;
		if(vis[id]||v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		if(siz[v]>maxn) maxn=siz[v];
	}
	maxn=max(sz-siz[u],maxn);
	if(maxn<minn) {
		minn=maxn;
		new_rt=u;
	}
}

int get_size(int u) {
	dfs(u,0);
	return siz[u];
}

int find_core(int u) {
	minn=2e9;
	dfs(u,0);
	return new_rt;
}

bool cmp(oi2 x,oi2 y) {
	return x.mx<y.mx;
}

int lowbit(int x) {
	return x&(-x);
}
void add(int x,int y) {
	for(; x<=n; x+=lowbit(x)) c[x]+=y;
}
int query(int x) {
	int res=0;
	if(x<0) return 0;
	for(; x; x-=lowbit(x)) res+=c[x];
	return res;
}

void dfs2(int u,int fa,int val,int len) {// 求出 mx 和 k 数组
	mx[u]=val;
	k[u]=len;
	p[++cnt]=(oi2) {
		mx[u],k[u]
	};
	for(int i=0; i<b[u].size(); i++) {
		int v=b[u][i].to;
		int w=b[u][i].w;
		int id=b[u][i].id;
		if(vis[id]||v==fa) continue;
		dfs2(v,u,max(val,w),len+1);
	}
}

int calc(int u,int k0) {
	cnt=0;
	dfs2(u,0,k0,(k0==0)?0:1);// 解决二维偏序问题
	sort(p+1,p+1+cnt,cmp);
	int res=0;
	for(int i=1; i<=cnt; i++) {
		res+=(query(R-p[i].k+1)-query(L-p[i].k))*p[i].mx;
		add(p[i].k+1,1);
	}
	for(int i=1; i<=cnt; i++) add(p[i].k+1,-1);
	return res;
}

void solve(int u) {
	sz=get_size(u);
	u=find_core(u);// 找重心
	for(int i=0; i<b[u].size(); i++) {
		int v=b[u][i].to;
		int w=b[u][i].w;
		int id=b[u][i].id;
		if(vis[id]) continue ;
		vis[id]=1;
		ans-=calc(v,w);//减去子树的贡献
		vis[id]=0;
	}
	ans+=calc(u,0);// 算贡献

	for(int i=0; i<b[u].size(); i++) {
		int v=b[u][i].to;
		int w=b[u][i].w;
		int id=b[u][i].id;
		if(vis[id]) continue;
		vis[id]=1;
		solve(v);// 点分治模板
		vis[id]=0;
	}
}

signed main() {
	read();
	solve(1);
	cout<<ans*2<<endl;// 答案最后要 *2
	return 0;
}

```




---

## 作者：wangif424 (赞：0)

## 简述题意

有一颗 $n$ 个点的树，定义 $val(u,v)$ 为从 $u$ 到 $v$ 的简单路径上边权的最大值。给定 $L,R$，求 $2\sum_{dis(u,v)\in[L,R]} val(u,v)$。

## 做法

看到 $dis(u,v)\in[L,R]$，考虑使用淀粉质。记中心为 $h$，过程中统计 $val(h,a)$ 和 $dis(h,a)$，简记为 $v_a，d_a$。

考虑贡献，假定 $dis(i,j)\in[L,R]$，若 $v_i \lt v_j$，则 $v_i$ 不产生贡献，反之有 $v_i$ 的贡献。于是以 $v$ 为关键字升序排序，这样 $v_i$ 会对 $v_j，\forall j \in [1,i-1]$ 都产生贡献。

刚刚忽略了 $dis(i,j)\in[L,R]$ 的限制，现在加上。我们对 $d_i$ 开值域树状数组统计其出现次数，然后有: $dis(i,j)=d_i+d_j\in[L,R] \iff d_j \in [L-d_i,R-d_i]$。树状数组区间求和即可求得 $d_i$ 产生贡献的次数。

最后考虑到我们刚刚将每个子树的信息统一处理，难免产生起点和终点在同一子树的情况。于是对每棵子树分别单独做一次如上过程，再将此贡献减去即可。

## AC 代码：

```cpp
#include <bits/stdc++.h>
#define R(x) x = read()
#define ENDL push('\n');
#define SPACE push(' ');
#define int long long
using namespace std;
char pbuf[1<<20], *pp=pbuf;
inline void push(const char &c) {
	if(pp - pbuf == 1<<20)fwrite(pbuf, 1, 1<<20, stdout),pp = pbuf;
	*pp++ = c;
}
class io {public:~io() {fwrite(pbuf, 1, pp - pbuf, stdout);}} _;
inline void write(int x) {
	if (x<0)x=-x,push('-');
	int sta[35],top=0;
	do {
		sta[top++]=x%10,x/=10;
	} while (x);
	while(top)push(sta[--top]^'0');
}
#ifndef LOCAL
	char buf[1<<23],*p1=buf,*p2=buf;
	#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
inline int read() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
    return x*f;
}
constexpr int N=3e5+100;
int n,L,R;
struct edge{
	int to,nxt,w;
}v[N<<1];
int fir[N],len;
void add(int x,int y,int w){v[++len]=edge{y,fir[x],w};fir[x]=len;}
int siz[N],miz[N],rt,sum,vis[N];
int val[N],cnt[N];
pair<int,int> hsd[N];int l;
void dfs1(int u,int fa){
	siz[u]=1;
	miz[u]=0;
	for(int i=fir[u];i;i=v[i].nxt){
		if(v[i].to==fa||vis[v[i].to])continue;
		dfs1(v[i].to,u);
		siz[u]+=siz[v[i].to];
		miz[u]=max(miz[u],siz[v[i].to]);
	}
	miz[u]=max(miz[u],sum-siz[u]);
	if(miz[u]<miz[rt])rt=u;
}
void dfs2(int u,int fa){
	hsd[++l]=make_pair(val[u],cnt[u]);
	for(int i=fir[u];i;i=v[i].nxt){
		if(v[i].to==fa||vis[v[i].to])continue;
		val[v[i].to]=max(val[u],v[i].w);
		cnt[v[i].to]=cnt[u]+1;
		dfs2(v[i].to,u);
	}
}
int ans;
int t[N];
int lowbit(int x){return x&-x;}
void add(int pos,int x){
	++pos;
	while(pos<=n+1){
		t[pos]+=x;
		pos+=lowbit(pos);
	}
}
int ask(int pos){
	++pos;
	int r=0;
	while(pos){
		r+=t[pos];
		pos-=lowbit(pos);
	}
	return r;
}
pair<int,int> jud[N];int tot;
void clac(int u){
	tot=0;
	for(int i=fir[u];i;i=v[i].nxt){
		if(vis[v[i].to])continue;
		val[v[i].to]=v[i].w;
		cnt[v[i].to]=1;
		l=0;
		dfs2(v[i].to,u);
		sort(hsd+1,hsd+1+l,less<pair<int,int>>());
		for(int j=1;j<=l;j++){
			if(R>=hsd[j].second)ans-=hsd[j].first*(ask(R-hsd[j].second)-ask(max(0ll,L-hsd[j].second-1)));
			add(hsd[j].second,1);
			jud[++tot]=hsd[j];
		}
		for(int j=1;j<=l;j++){
			add(hsd[j].second,-1);
		}
	}
	sort(jud+1,jud+1+tot,less<pair<int,int>>());
	for(int i=1;i<=tot;i++){
		if(R>=jud[i].second)ans+=jud[i].first*(ask(R-jud[i].second)-ask(max(-1ll,L-jud[i].second-1)));
		add(jud[i].second,1);
	}
	for(int i=1;i<=tot;i++){
		add(jud[i].second,-1);
	}
}
void getans(int u){
	vis[u]=1;
	clac(u);
	for(int i=fir[u];i;i=v[i].nxt){
		if(vis[v[i].to])continue;
		sum=siz[v[i].to];
		rt=0;
		dfs1(v[i].to,u);
		getans(rt);
	}
}
signed main(){
	R(n);R(L);R(R);
	for(int i=1;i<n;i++){
		int R(x),R(y),R(w);
		add(x,y,w);
		add(y,x,w);
	}
	sum=n;
	miz[0]=INT_MAX;
	dfs1(1,0);
	add(0,1);
	getans(rt);
	write(ans*2);
    return 0;
}
```

---

## 作者：wcyQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P5351)

[可能更好的阅读体验](https://chenyu-w.github.io./2023/02/22/P5351%20Ruri%20Loves%20Maschera/)

简单的淀粉质板子。


## 分析

考虑统计经过当前分治中心 $u$ 的答案，对于每个 $v \in \text{subtree}(u)$，我们维护 $d_v$ 和 $w_v$，表示 $u \rightarrow v$ 的边数和路径上的最大值，然后我们考虑对所有点按照 $w$ 进行排序。假设我们现在要计算一个点 $v$ 的贡献，由于按照 $w$ 排序过了，所以它的贡献就是 $w_v$ 乘上满足路径长度的路径条数，后面的问题显然是一个 BIT 就可以解决，所以我们就用 $O(n \log^2n)$ 解决了这道题。

## 代码

```c++
#include <bits/stdc++.h>
#define L(i, j, k) for(int i = (j); i <= (k); i++)
#define R(i, j, k) for(int i = (j); i >= (k); i--)
#define G(i, u) for (int i = h[(u)]; ~i; i = ne[i])
#define ll long long
#define ld long double
#define ull unsigned long long

using namespace std;
const int N = 1e5 + 10;
int h[N], e[N << 1], ne[N << 1], w[N << 1], idx;
int vis[N];
vector<pair<int, int> > now, all;
int n, L, R;
int tr[N];
ll res;

inline int read() {
    int x = 0, y = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * y;
}

inline void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

inline void add(int x, int v) {
    for (; x <= n; x += x & -x) tr[x] += v;
}

inline int ask(int x) {
    int res = 0;
    for (; x; x -= x & -x) res += tr[x];
    return res;
}

inline int getSize(int u, int p) {
    if (vis[u]) return 0;
    int res = 1;
    G(i, u) if (e[i] != p) res += getSize(e[i], u);
    return res;
}

inline int getRoot(int u, int p, int all, int &root) {
    if (vis[u]) return 0;
    int now = 0, sum = 1;
    G(i, u) {
        int v = e[i];
        if (v == p) continue;
        int k = getRoot(v, u, all, root);
        now = max(now, k), sum += k;
    }
    now = max(now, all - sum);
    if (now <= all / 2) root = u;
    return sum;
}

inline void getDist(int u, int p, int dist, int pe) {
    if (vis[u]) return;
    now.push_back({pe, dist});
    if (dist < R) G(i, u) if (e[i] != p) getDist(e[i], u, dist + 1, max(pe, w[i]));
}

inline ll calc(vector<pair<int, int> > &a) {
    ll res = 0;
    sort(a.begin(), a.end());
    for (pair<int, int> t : a) res += 1ll * t.first * (ask(R - t.second) - ask(max(0, L - t.second - 1))), add(t.second, 1);
    for (pair<int, int> t : a) add(t.second, -1);
    return res;
}

inline void calc(int u) {
    all.clear();
    G(i, u) {
        int v = e[i];
        if (vis[v]) continue;
        now.clear();
        getDist(v, u, 1, w[i]);
        res -= calc(now);
        for (pair<int, int> t : now) all.push_back(t); 
    }
    res += calc(all);
    for (pair<int, int> t : all) if (t.second >= L) res += t.first;
}

inline void dfs(int u) {
    if (vis[u]) return;
    getRoot(u, -1, getSize(u, -1), u);
    vis[u] = true;
    calc(u);
    G(i, u) dfs(e[i]);
}

int main() {
    memset(h, -1, sizeof h);
    n = read(), L = read(), R = read();
    L(_, 1, n - 1) {
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }
    dfs(1);
    printf("%lld\n", res << 1);
    return 0;
}
```



---

## 作者：hl666 (赞：0)

先ORZ$Owen$一发。感觉是个很套路的题，这里给一个蒟蒻的需要特判数据的伪$n\log^2 n$算法，真正的两只$\log$的还是去看标算吧（但这个好想好写跑不满啊）

首先这种树上路径统计的问题我们先套一个**点分治**上去就是了，然后求出分治中心连出去的每一条路径

我们还是套路地分成不同子树求解，如果我们对一条路径设一个**二元组**$(dep,val)$表示到分治中心的深度以及路径上的最大值，那么就考虑怎么把一棵子树内的路径和其它子树的合并了

考虑如果只有一个端点限制怎么做，很容易想到它们的和取值都满足单调性

那么我们直接把两边都按$dep$排序，然后直接$\text{two points}$扫出一个端点的范围即可

接下来考虑两个端点怎么做，我们发现此时可以选的点形成了一个区间，既然这个区间两个端点都满足单调性，所以这个区间移动也是单调的

那么就很简单了，我们扫出每个点的合法区间之后考虑怎么统计答案

首先所有比它小的数最后的贡献都是它的权值，然后所有大于它的数的贡献即是它们本身

我们直接拿两个**树状数组**来维护，一个记录比它小的数的个数，另一个记录比它大的数的权值和，直接跟着指针一起添删点即可

很容易发现，这样的复杂度大部分消耗在排序上，如果每次暴力排序的话复杂度最坏会被卡到$n^2\log^2 n$，但是很多时候一个点的度数没有那么多，所以跑起来非常快，大致比两个$\log$多一些常数吧

所以我们写完之后特判一下菊花图即可，这个更加简单，因为路径长度只有$1/2$，暴力排序后枚举一下即可

CODE

```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#define RI int
#define CI const int&
#define Tp template <typename T>
using namespace std;
typedef long long LL;
const int N=100005,INF=1e9;
struct edge
{
    int to,nxt,v;
}e[N<<1]; int n,head[N],rst[N],num,cnt,L,R,x,y,z; LL ans; bool flag;
class FileInputOutput
{
    private:
        static const int S=1<<21;
        #define tc() (A==B&&(B=(A=Fin)+fread(Fin,1,S,stdin),A==B)?EOF:*A++)
        char Fin[S],*A,*B;
    public:
        Tp inline void read(T& x)
        {
            x=0; char ch; while (!isdigit(ch=tc()));
            while (x=(x<<3)+(x<<1)+(ch&15),isdigit(ch=tc()));
        }
        #undef tc
}F;
inline int min(CI a,CI b)
{
    return a<b?a:b;
}
inline void addedge(CI x,CI y,CI z)
{
    e[++cnt]=(edge){y,head[x],z}; head[x]=cnt;
    e[++cnt]=(edge){x,head[y],z}; head[y]=cnt;
}
namespace Case1 //Point Division Solver
{
    class Tree_Array
    {
        private:
            int size[N]; LL sum[N]; bool vis[N];
        public:
            #define lowbit(x) x&-x
            inline void add(CI x,CI y,CI opt,RI i=0)
            {
                for (i=x;i<=num;i+=lowbit(i)) size[i]+=opt;
                for (i=x;i;i-=lowbit(i)) sum[i]+=opt*y;
            }
            inline int query_rk(RI x,int ret=0)
            {
                for (;x;x-=lowbit(x)) ret+=size[x]; return ret;
            }
            inline LL query_sum(RI x,LL ret=0)
            {
                for (;x<=num;x+=lowbit(x)) ret+=sum[x]; return ret;
            }
            #undef lowbit
    }BIT;
    #define to e[i].to
    class Point_Division_Solver
    {
        private:
            struct data
            {
                int dep,mxv;
                friend inline bool operator < (const data& A,const data& B)
                {
                    return A.dep<B.dep;
                }
            }s[N]; int size[N],tot,pl[N],pr[N]; bool vis[N];
            inline int max(CI a,CI b)
            {
                return a>b?a:b;
            }
            inline void maxer(int& x,CI y)
            {
                if (y>x) x=y;
            }
            inline void DFS(CI now,CI fa,CI d,CI mx)
            {
                s[++tot]=(data){d,mx}; if (L<=d&&d<=R) ans+=rst[mx];
                for (RI i=head[now];i;i=e[i].nxt)
                if (to!=fa&&!vis[to]) DFS(to,now,d+1,max(mx,e[i].v));
            }
        public:
            int mx[N],ots,rt;
            inline void getrt(CI now,CI fa=1)
            {
                size[now]=1; mx[now]=0;
                for (RI i=head[now];i;i=e[i].nxt) if (to!=fa&&!vis[to])
                getrt(to,now),size[now]+=size[to],maxer(mx[now],size[to]);
                if (maxer(mx[now],ots-size[now]),mx[now]<mx[rt]) rt=now;
            } 
            inline void solve(CI now)
            {
                RI i,j; vis[now]=1; tot=0; int lst=0;
                for (i=head[now];i;i=e[i].nxt) if (!vis[to])
                {
                    DFS(to,now,1,e[i].v); sort(s+lst+2,s+tot+1); if (lst)
                    {
                        int p1=lst; for (j=lst+1;j<=tot;++j)
                        {
                            while (p1&&s[p1].dep+s[j].dep>R) --p1; pr[j]=p1; 
                        }
                        int p2=1; for (j=tot;j>lst;--j)
                        {
                            while (p2<=lst&&s[p2].dep+s[j].dep<L) ++p2; pl[j]=p2;
                        }
                        p1=lst+1; p2=lst; for (j=lst+1;j<=tot;++j)
                        {
                            while (p1>pl[j]) --p1,BIT.add(s[p1].mxv,rst[s[p1].mxv],1);
                            while (p2>pr[j]) BIT.add(s[p2].mxv,rst[s[p2].mxv],-1),--p2;
                            ans+=1LL*BIT.query_rk(s[j].mxv)*rst[s[j].mxv]+BIT.query_sum(s[j].mxv+1);
                        }
                        for (j=p1;j<=p2;++j) BIT.add(s[j].mxv,rst[s[j].mxv],-1);
                    }
                    lst=tot; sort(s+1,s+lst+1);
                }
                for (i=head[now];i;i=e[i].nxt) if (!vis[to])
                mx[rt=0]=INF,ots=size[to],getrt(to,now),solve(rt);
            }
    }PD;
    #undef to
    inline void solve(void)
    {
        sort(rst+1,rst+n); num=unique(rst+1,rst+n)-rst-1;
        for (RI i=1;i<=cnt;++i) e[i].v=lower_bound(rst+1,rst+num+1,e[i].v)-rst;
        PD.mx[PD.rt=0]=INF; PD.ots=n; PD.getrt(1); PD.solve(PD.rt); 
    }
};
namespace Case2 //Flower Graph Solver
{
    inline void solve(void)
    {
        RI i; sort(rst+1,rst+n); if (L<=1&&1<=R)
        for (i=1;i<n;++i) ans+=rst[i]; if (L<=2&&2<=R)
        for (i=1;i<n;++i) ans+=1LL*rst[i]*(i-1);
    }
};
int main()
{
    //freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
    RI i; for (F.read(n),F.read(L),F.read(R),flag=i=1;i<n;++i)
    {
        F.read(x); F.read(y); F.read(z);
        addedge(x,y,z); rst[i]=z; if (min(x,y)!=1) flag=0;
    }
    if (flag) Case2::solve(); else Case1::solve();
    return printf("%lld",ans<<1LL),0;
}
```



---

