# Misha and LCP on Tree

## 题目描述

Misha has a tree with characters written on the vertices. He can choose two vertices $ s $ and $ t $ of this tree and write down characters of vertices lying on a path from $ s $ to $ t $ . We'll say that such string corresponds to pair $ (s,t) $ .

Misha has $ m $ queries of type: you are given $ 4 $ vertices $ a $ , $ b $ , $ c $ , $ d $ ; you need to find the largest common prefix of the strings that correspond to pairs $ (a,b) $ and $ (c,d) $ . Your task is to help him.

## 样例 #1

### 输入

```
6
bbbabb
2 1
3 2
4 3
5 2
6 5
6
2 5 3 1
1 5 2 3
5 6 5 6
6 3 4 1
6 2 3 4
2 2 4 5
```

### 输出

```
2
2
2
0
1
0
```

# 题解

## 作者：xht (赞：30)

> [CF504E Misha and LCP on Tree](https://codeforces.com/contest/504/problem/E)

## 题意

- 给定一棵 $n$ 个节点的树，每个节点有一个小写字母。
- 有 $m$ 组询问，每组询问为树上 $a \to b$ 和 $c \to d$ 组成的字符串的最长公共前缀。
- $n \le 3 \times 10^5$，$m \le 10^6$。

## 题解

首先，根据 hash 值具有可减性，可以通过预处理每个点到根以及根到每个点的 hash 值，$\mathcal O(1)$ 求出任意一条没有拐点的路径的 hash 值。

考虑树剖，我们可以将 $a \to b$ 和 $c \to d$ 的路径分别拆成 $\mathcal O(\log n)$ 个区间，然后每次消掉一个区间。

如果消不掉这个区间，则在这个区间上二分找到答案。

总时间复杂度 $\mathcal O(n + m \log n)$。

另外，在 CF 上最好写双 hash，且不能采用自然溢出，否则大概率被卡。

## 代码

```cpp
#define Hash pair <modint, modint>

const int N = 3e5 + 7, mod = 1e9 + 7;
const Hash B = mp((modint)131, (modint)13331);
int n, m, d[N], f[N], s[N], son[N], dfn[N], rnk[N], top[N], num;
Hash p[N], h1[N], h2[N];
char c[N];
vi e[N];

inline Hash operator + (Hash a, Hash b) {
	return mp(a.fi + b.fi, a.se + b.se);
}

inline Hash operator - (Hash a, Hash b) {
	return mp(a.fi - b.fi, a.se - b.se);
}

inline Hash operator * (Hash a, Hash b) {
	return mp(a.fi * b.fi, a.se * b.se);
}

inline Hash H(bool o, int x, int k) {
	if (o) return h2[x-k+1] - h2[x+1] * p[k];
	return h1[x+k-1] - h1[x-1] * p[k];
}

void dfs(int x) {
	s[x] = 1;
	for (auto y : e[x])
		if (y != f[x]) {
			f[y] = x, d[y] = d[x] + 1, dfs(y), s[x] += s[y];
			if (s[y] > s[son[x]]) son[x] = y;
		}
}

void dfs(int x, int p) {
	top[x] = p, dfn[x] = ++num, rnk[num] = x;
	if (son[x]) dfs(son[x], p);
	for (auto y : e[x]) if (y != f[x] && y != son[x]) dfs(y, y);
}

inline int lca(int x, int y) {
	while (top[x] != top[y]) {
		if (d[top[x]] > d[top[y]]) swap(x, y);
		y = f[top[y]];
	}
	if (d[x] > d[y]) swap(x, y);
	return x;
}

inline vector <pi> get(int x, int y) {
	int z = lca(x, y);
	vector <pi> o, w;
	while (d[top[x]] > d[z]) o.pb(mp(x, top[x])), x = f[top[x]];
	o.pb(mp(x, z));
	while (d[top[y]] > d[z]) w.pb(mp(top[y], y)), y = f[top[y]];
	if (y != z) w.pb(mp(son[z], y));
	while (w.size()) o.pb(w.back()), w.pop_back();
	return o;
}

int main() {
	rd(n), rds(c, n), p[0] = mp(1, 1), p[1] = B;
	for (int i = 1, x, y; i < n; i++)
		rd(x), rd(y), e[x].pb(y), e[y].pb(x), p[i+1] = p[i] * B;
	d[1] = 1, dfs(1), dfs(1, 1);
	for (int i = 1; i <= n; i++)
		h1[i] = h1[i-1] * B + mp(c[rnk[i]], c[rnk[i]]),
		h2[n+1-i] = h2[n+2-i] * B + mp(c[rnk[n+1-i]], c[rnk[n+1-i]]);
	rd(m);
	while (m--) {
		int a, b, c, d, ans = 0;
		ui s = 0, t = 0;
		rd(a), rd(b), rd(c), rd(d);
		vector <pi> f = get(a, b), g = get(c, d);
		while (s < f.size() && t < g.size()) {
			int df1 = dfn[f[s].fi], df2 = dfn[f[s].se];
			int dg1 = dfn[g[t].fi], dg2 = dfn[g[t].se];
			bool of = df1 > df2, og = dg1 > dg2;
			int lf = (of ? df1 - df2 : df2 - df1) + 1;
			int lg = (og ? dg1 - dg2 : dg2 - dg1) + 1;
			int len = min(lf, lg);
			Hash hf = H(of, df1, len);
			Hash hg = H(og, dg1, len);
			if (hf == hg) {
				if (len == lf) ++s;
				else f[s].fi = rnk[df1+(of?-1:1)*len];
				if (len == lg) ++t;
				else g[t].fi = rnk[dg1+(og?-1:1)*len];
				ans += len;
			} else {
				int l = 1, r = len;
				while (l < r) {
					int mid = (l + r) >> 1;
					hf = H(of, df1, mid);
					hg = H(og, dg1, mid);
					if (hf == hg) l = mid + 1;
					else r = mid;
				}
				ans += l - 1; break;
			}
		}
		print(ans);
	}
	return 0;
}
```

---

## 作者：mrsrz (赞：17)

[可能更好的体验](https://mrsrz.github.io/2019/12/17/CF504E/)

序列上的问题，我们可以用二分+哈希的方法，在 $O(n+m\log n)$ 的时间内解决问题。在知道两个位置的前缀或后缀哈希值的情况下，我们可以 $O(1)$ 计算中间这一段的哈希值。

现在问题搬到了树上，但对于树上的一条路径，我们仍然可以 $O(1)$ 得到它的哈希值。具体就是分别维护到根路径的正串哈希值和反串哈希值（$O(n)$ 预处理），然后可以通过到根的前缀/后缀 $O(1)$ 计算一条向根路径的哈希值。我们在 LCA 处断开，计算两段哈希值然后 $O(1)$ 合并就是该路径的哈希值。

在树上求哈希值的复杂度并没有变差，所以仍然可以 $O(\log n)$ 回答一次询问。

由于我们要二分 LCP 长度，所以我们要知道对每个长度，其结尾的点的位置，相当于一个求 $k$ 级祖先的问题。这里要求 $m\log n$ 次，所以用倍增的话复杂度就会多 $\log n$。

不难想到用长链剖分做到 $O(n\log n)$ 预处理，$O(1)$ 查询 $k$ 级祖先。

这样总时间复杂度是 $O((n+m)\log n)$。

需要注意常数还有不要被卡哈希，双哈希比较稳。这里由于 $m>n$，所以使用 ST 表的 $O(n\log n)$ 预处理 $O(1)$ 查询，常数会更小。~~不要用倍增求 LCA 那个慢死了~~。

## Code：

```cpp
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long LL;
#define lg2(x)(31-__builtin_clz(x))
const int md1=1004535809,md2=167772161,N=3e5+5;
int base1,base2;
int _1[N],_2[N],n,m;
int i1[N],i2[N];
char s[N];
int head[N],cnt;
int mxd[N],toph[N],tail[N],sonh[N],len[N],fa[N],F[19][N],dep[N],idx,dfn[N];
int*up[N],*down[N];
int st[20][N<<1];
inline int Inv(int a,const int&md){
	int ret=1,b=md-2;
	for(;b;b>>=1,a=(LL)a*a%md)if(b&1)ret=(LL)ret*a%md;
	return ret;
}
struct edge{
	int to,nxt;
}e[N<<1];
struct data{
	int s1,s2;
	int len;
	inline void push_front(char c){s1=(s1+(LL)c*_1[len])%md1,s2=(s2+(LL)c*_2[len++])%md2;}
	inline void push_back(char c){s1=((LL)s1*base1+c)%md1,s2=((LL)s2*base2+c)%md2,++len;}
	inline data operator+(const data&rhs)const{return(data){((LL)s1*_1[rhs.len]+rhs.s1)%md1,((LL)s2*_2[rhs.len]+rhs.s2)%md2,len+rhs.len};}
	inline bool operator==(const data&rhs)const{return s1==rhs.s1&&s2==rhs.s2&&len==rhs.len;}
}a[N],b[N];
void dfs(int now){
	st[0][dfn[now]=++idx]=now;
	sonh[now]=0,mxd[now]=dep[now];
	a[now]=a[fa[now]],b[now]=b[fa[now]];
	a[now].push_back(s[now]),b[now].push_front(s[now]);
	for(int i=head[now];i;i=e[i].nxt)
	if(!dep[e[i].to]){
		dep[e[i].to]=dep[now]+1;
		fa[e[i].to]=F[0][e[i].to]=now;
		dfs(e[i].to);
		st[0][++idx]=now;
		if(mxd[e[i].to]>mxd[now])mxd[now]=mxd[e[i].to],sonh[now]=e[i].to;
	}
}
void dfs2(int now){
	tail[toph[now]]=now,len[toph[now]]=dep[now]-dep[toph[now]]+1;
	if(sonh[now])toph[sonh[now]]=toph[now],dfs2(sonh[now]);
	for(int i=head[now];i;i=e[i].nxt)
	if(dep[e[i].to]>dep[now]&&e[i].to!=sonh[now])dfs2(toph[e[i].to]=e[i].to);
}
inline int kfa(int x,int k){
	if(dep[x]<=k)return 0;
	if(k==0)return x;
	const int lg=lg2(k);
	x=F[lg][x],k-=1<<lg;
	if(!k)return x;
	const int dlt=dep[x]-dep[toph[x]];
	if(dlt>=k)
	return down[toph[x]][dlt-k];
	return up[toph[x]][k-dlt];
}
inline int LCA(int x,int y){
	if(dfn[x]>dfn[y])swap(x,y);
	x=dfn[x],y=dfn[y];
	int lg=lg2(y-x+1);
	int a=st[lg][x],b=st[lg][y-(1<<lg)+1];
	return(dep[a]<dep[b])?a:b;
}
void init(){
	for(int i=1;i<19;++i)
	for(int j=1;j<=n;++j)
	F[i][j]=F[i-1][F[i-1][j]];
	for(int i=1;i<=n;++i)
	if(toph[i]==i){
		int h=len[i];
		up[i]=new int[h+2];
		down[i]=new int[h+2];
		*up[i]=*down[i]=i;
		for(int j=1,nw=fa[i];j<=h&&nw;++j,nw=fa[nw])
		up[i][j]=nw;
		for(int j=1,nw=sonh[i];j<=h&&nw;++j,nw=sonh[nw])
		down[i][j]=nw;
	}
	for(int i=1;i<20;++i)
	for(int j=1;j<=2*n;++j){
		int x=st[i-1][j],y=st[i-1][j+(1<<i-1)];
		st[i][j]=(dep[x]<dep[y])?x:y;
	}
}
inline data get(int u,int v){
	const data&x=b[u],&y=b[v];
	return(data){(LL)(x.s1-y.s1+md1)*i1[y.len]%md1,(LL)(x.s2-y.s2+md2)*i2[y.len]%md2,x.len-y.len};
}
inline data get_(int u,int v){
	const data&x=a[u],&y=a[v];
	return(data){(y.s1-(LL)x.s1*_1[y.len-x.len]%md1+md1)%md1,(y.s2-(LL)x.s2*_2[y.len-x.len]%md2+md2)%md2,y.len-x.len};
}
int main(){
	srand(time(0));
	base1=rand()%100+200,base2=rand()%300+400;
	scanf("%d%s",&n,s+1);
	_1[0]=_2[0]=i1[0]=i2[0]=1;
	for(int i=1;i<=n;++i)
	_1[i]=(LL)_1[i-1]*base1%md1,_2[i]=(LL)_2[i-1]*base2%md2;
	i1[1]=Inv(base1,md1),i2[1]=Inv(base2,md2);
	for(int i=2;i<=n;++i)
	i1[i]=(LL)i1[i-1]*i1[1]%md1,i2[i]=(LL)i2[i-1]*i2[1]%md2;
	for(int i=1;i<n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		e[++cnt]=(edge){v,head[u]},head[u]=cnt;
		e[++cnt]=(edge){u,head[v]},head[v]=cnt;
	}
	dfs(dep[1]=1),dfs2(toph[1]=1);
	init();
	for(scanf("%d",&m);m--;){
		int u1,v1,u2,v2;
		scanf("%d%d%d%d",&u1,&v1,&u2,&v2);
		int L1=LCA(u1,v1),L2=LCA(u2,v2);
		const int D1=dep[u1]+dep[v1]-2*dep[L1]+1,D2=dep[u2]+dep[v2]-2*dep[L2]+1;
		int l=1,r=min(D1,D2),ans=0;
		while(l<=r){
			const int mid=l+r>>1;
			const data _x=dep[u1]-mid+1>=dep[L1]?get(u1,kfa(u1,mid)):get(u1,L1)+get_(fa[L1],kfa(v1,D1-mid));
			const data _y=dep[u2]-mid+1>=dep[L2]?get(u2,kfa(u2,mid)):get(u2,L2)+get_(fa[L2],kfa(v2,D2-mid));
			if(_x==_y)l=(ans=mid)+1;else r=mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：xudaxia (赞：10)

~~1A真舒服。~~  
喜闻乐见的树链剖分+SA。  
一个初步的想法就是用树链剖分，把两个字符串求出然后hash+二分求lcp。。。不存在的。  
因为考虑到这个字符串是有序的，我们需要把每一条重链对应的字符串和这个重链反过来对应的字符串拼起来构成一个新的字符串。我们用树链剖分拼出两个字符串。用树剖拼出的这两个字符串，一定是重链拼成的字符串上一个一个区间，我们记录这些区间的左右端点。然后我们就是要一个一个处理区间。求两个区间对应字符串的lcp，我们直接上SA+ST表就行，求出lcp之后就在这些区间上分情况讨论，然后就结束了。  
具体看代码，~~太丑了也看不出来什么。~~
```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=601000;
int cnt,head[N];
int size[N],fa[N],dep[N],dfn[N],top[N],tot,son[N];
int s[N],id[N][2],cn,Top[N];
int sa[N],x[N],y[N],len,rk[N],height[N],m,mn[N][20],c[N];
int L[N][2],R[N][2],NUM[N],Num[N],n;
char S[N];
struct edge{
	int to,nxt;
}e[N];
void add(int u,int v){
	cnt++;
	e[cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
void dfs1(int u,int f){
	size[u]=1;
	fa[u]=f;
	dep[u]=dep[f]+1;
	int maxson=-1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f)continue;
		dfs1(v,u);
		if(size[v]>maxson){
			maxson=size[v];
			son[u]=v;
		}
		size[u]+=size[v];
	}
}
void dfs2(int u,int tp){
	dfn[u]=++tot;
	top[u]=tp;
	if(son[u])dfs2(son[u],tp);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa[u]||v==son[u])continue;
		Top[++cn]=v;
		dfs2(v,v);
	}
}
void build(int u){
	s[++len]=S[u];
	id[dfn[u]][0]=len;
	if(son[u]==0){
		id[dfn[u]][0]=len;
		s[++len]=S[u];
		id[dfn[u]][1]=len;
		return;
	}
	build(son[u]);
	s[++len]=S[u];
	id[dfn[u]][1]=len;
}
void get_sa(){
	for(int i=1;i<=len;i++)c[x[i]=s[i]]++;
	for(int i=1;i<=m;i++)c[i]+=c[i-1];
	for(int i=len;i>=1;i--)sa[c[x[i]]--]=i;
	for(int k=1;k<=len;k<<=1){
		int num=0;
		for(int i=len-k+1;i<=len;i++)y[++num]=i;
		for(int i=1;i<=len;i++)if(sa[i]>k)y[++num]=sa[i]-k;
		for(int i=1;i<=m;i++)c[i]=0;
		for(int i=1;i<=len;i++)c[x[i]]++;
		for(int i=1;i<=m;i++)c[i]+=c[i-1];
		for(int i=len;i>=1;i--)sa[c[x[y[i]]]--]=y[i],y[i]=0;
		for(int i=1;i<=len;i++)swap(x[i],y[i]);
		x[sa[1]]=1;num=1;
		for(int i=2;i<=len;i++)
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?num:++num;
		if(num==len)break;
		m=num;
	}
}
void get_height(){
	int k=0;
	for(int i=1;i<=len;i++)rk[sa[i]]=i;
	for(int i=1;i<=len;i++){
		if(rk[i]==1)continue;
		if(k)k--;
		int j=sa[rk[i]-1];
		while(i+k<=len&&j+k<=len&&s[i+k]==s[j+k])k++;
		height[rk[i]]=k;
	}
}
void pre_work(){
	for(int i=1;i<=len;i++)mn[i][0]=height[i];
	int Len=log2(len);
	for(int j=1;j<=Len;j++)
		for(int i=1;i+(1<<j)-1<=len;i++)
			mn[i][j]=min(mn[i][j-1],mn[i+(1<<j-1)][j-1]); 
}
int get_lcp(int l,int r){
	if(l>r)swap(l,r);
	l++;
	if(l>r)return 1e9;
	int Len=log2(r-l+1);
	return min(mn[l][Len],mn[r-(1<<Len)+1][Len]);
}
void work(int x,int y,int k){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			Num[k]++;
			L[Num[k]][k]=id[dfn[x]][1];
			R[Num[k]][k]=id[dfn[top[x]]][1];
			x=fa[top[x]];
		}
		else{
			NUM[k]--;
			L[NUM[k]][k]=id[dfn[top[y]]][0];
			R[NUM[k]][k]=id[dfn[y]][0];
			y=fa[top[y]];
		}
	}
	if(dep[x]>dep[y]){
		Num[k]++;
		L[Num[k]][k]=id[dfn[x]][1];
		R[Num[k]][k]=id[dfn[y]][1];
	}
	else{
		NUM[k]--;
		L[NUM[k]][k]=id[dfn[x]][0];
		R[NUM[k]][k]=id[dfn[y]][0];
	}
}
void calc(){
	int now0=1,now1=1;
	int tmp=0;
	while(now0<=n&&now1<=n){
		if(now0>Num[0]&&now0<NUM[0])now0=NUM[0];
		if(now1>Num[1]&&now1<NUM[1])now1=NUM[1];
		if(now0>n||now1>n)break;
		int LL=min(min(R[now0][0]-L[now0][0]+1,R[now1][1]-L[now1][1]+1),get_lcp(rk[L[now0][0]],rk[L[now1][1]]));
		L[now0][0]=L[now0][0]+LL;
		L[now1][1]=L[now1][1]+LL;
		tmp+=LL;
		if(L[now0][0]<=R[now0][0]&&L[now1][1]<=R[now1][1])break;
		if(L[now0][0]>R[now0][0])now0++;
		if(L[now1][1]>R[now1][1])now1++;
	}
	printf("%d\n",tmp);
}
int read(){
	int sum=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){sum=sum*10+ch-'0';ch=getchar();}
	return sum*f;
}
int main(){
	n=read();
	scanf("%s",S+1);
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	dfs1(1,0);cn=1;Top[1]=1;dfs2(1,1);
	for(int i=1;i<=cn;i++)build(Top[i]);
	m=122;
	get_sa();get_height();pre_work();
	m=read();
	int a,b,c,d;
	while(m--){
		a=read();b=read();
		c=read();d=read();
		Num[0]=Num[1]=0;
		NUM[0]=NUM[1]=n+1;
		work(a,b,0);work(c,d,1);
		calc();
	}
	return 0;
}
```

---

## 作者：Sol1 (赞：9)

这题的思维难度其实不算太高，评了个 \*3000 可能是因为比较难写以及卡常吧。

前置知识：字符串哈希、$O(n\log n)-O(1)$ LCA、长链剖分、树上差分。

回想一下，在求序列 LCP 的时候我们采用了二分的方法，这里也可以应用。

具体来说，我们二分 LCP 的长度 $k$，然后在两条路径上分别取出前 $k$ 个节点连成的字符串的哈希值 $h_{ab}$ 和 $h_{cd}$，然后比较两者是否相同即可。

然后我们就要在 $O(1)$ 时间内完成上述过程。

首先，提取一段路径连成的字符串的哈希值，这个可以树上差分完成。具体来讲，我们对一个节点 $v$ 维护两个哈希值 $u_v$ 和 $d_v$，分别表示路径 $v\rightarrow 1$ 连成字符串的哈希值和 $1\rightarrow v$ 连成字符串的哈希值。然后提取路径 $x\rightarrow y$ 的时候分为 $x\rightarrow \operatorname{lca}(x,y)$ 和 $\operatorname{lca}(x,y)\rightarrow y$。第一段的哈希值 $h_1=\dfrac{u_{x}-u_{f_{\operatorname{lca}(x,y)}}}{B^{dep_{\operatorname{lca}(x,y)}-1}}$，第二段的哈希值 $h_2=d_y-d_{\operatorname{lca}(x,y)}\cdot B^{\operatorname{dist}(y,\operatorname{lca}(x,y))}$，路径哈希值就是 $h_1\cdot B^{\operatorname{dist}(y,\operatorname{lca}(x,y))}+h_2$。通过提前预处理 $B^x$ 和 $B^{-x}$ 的值，达到复杂度 $O(1)$。

其中 $\operatorname{dist}(x,y)$ 表示 $x,y$ 两点之间的距离。

当然这是 $x,y$ 没有任何一个属于另一个的子树的情况。如果有这种情况，处理方法也是类似的，直接返回 $h_1$ 或 $h_2$ 即可。

然后我们来考虑怎么提取路径。

首先我们判断前 $k$ 个点会不会跨越 $\operatorname{lca}$。如果会，则路径为 $x\rightarrow f(y,\operatorname{dist}(x,y)-k)$；否则路径为 $x\rightarrow f(x,k-1)$。其中 $f(x,k)$ 表示 $x$ 的 $k$ 级祖先。

所以现在只要长链剖分求 $k$ 级祖先就可以做到 $O(1)$，在外面先求好 $\operatorname{lca}$ 是 $O(\log n)$ 的，但是并不会和二分的 $\log$ 乘到一起，所以总复杂度就是 $O((n+m)\log n)$ 的。

所以这题就做完了——吗？

你写好了交上去，就愉快地被卡 T 了 QAQ

我们分出来测一下，就会发现光是求 $10^6$ 次 lca 的耗时就会达到恐怖的 3.5s……

于是我们拿掉倍增 lca，换上 ST 表的 $O(n\log n)-O(1)$ lca，然后加上取模优化（这题里面取模优化效果极为明显，加上之后可以达到 6.5s），就可以过这题了。

注意实现的时候使用双哈希，避免被叉。

其实双哈希用 $10^9+7$ 和 $10^9+9$ 也是很危险的……可以使用一些小众一点的模数。

代码：

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

const int N = 300005;
const long long mod[2] = {1000000007, 1000000009};
struct Edge {
	int to, nxt;
	Edge() {
		nxt = -1;
	}
};
Edge e[N << 1];
int n, m, hd[N], pnt, fa[N][25], dep[N], maxdep[N], son[N], top[N], highbit[N], st[1000005][25], dfn[N], _time, _log[1000005];
long long uphash[N][2], dnhash[N][2], pow26[N][2], powInv26[N][2];
vector <int> up[N], dn[N];
char s[N];

inline long long Power(long long x, long long y, long long mod) {
	register long long ans = 1;
	while (y) {
		if (y & 1) ans = ans * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ans;
}

inline void AddEdge(int u, int v) {
	e[++pnt].to = v;
	e[pnt].nxt = hd[u];
	hd[u] = pnt;
}

inline void Read() {
	n = qread();
	highbit[0] = -1;
	for (register int i = 1;i <= n;i++) {
		s[i] = getchar();
		while (s[i] < 'a' || s[i] > 'z') s[i] = getchar();
		highbit[i] = highbit[i >> 1] + 1;
	}
	for (register int i = 1;i < n;i++) {
		register int u = qread(), v = qread();
		AddEdge(u, v);
		AddEdge(v, u);
	}
}

inline void Calc26() {
	pow26[0][0] = pow26[0][1] = 1;
	powInv26[0][0] = powInv26[0][1] = 1;
	powInv26[1][0] = Power(26ll, mod[0] - 2, mod[0]);
	powInv26[1][1] = Power(26ll, mod[1] - 2, mod[1]);
	pow26[1][0] = pow26[1][1] = 26;
	for (register int i = 2;i <= n;i++) {
		for (register int j = 0;j < 2;j++) {
			pow26[i][j] = pow26[i - 1][j] * 26ll % mod[j];
			powInv26[i][j] = powInv26[i - 1][j] * powInv26[1][j] % mod[j];
		}
	}
}

inline long long Add(long long x, long long y, long long mod) {
	return (x + y < mod ? x + y : x + y - mod);
}

inline long long Minus(long long x, long long y, long long mod) {
	return (x < y ? x - y + mod : x - y);
}

inline void Dfs1(int u) {
	_time++;
	st[_time][0] = u;
	dfn[u] = _time;
	for (register int j = 0;j < 2;j++) {
		uphash[u][j] = Add(uphash[fa[u][0]][j], pow26[dep[u] - 1][j] * (s[u] - 'a') % mod[j], mod[j]);
		dnhash[u][j] = Add(dnhash[fa[u][0]][j] * 26ll % mod[j], s[u] - 'a', mod[j]);
	}
	for (register int i = hd[u];~i;i = e[i].nxt) {
		if (e[i].to != fa[u][0]) {
			fa[e[i].to][0] = u;
			dep[e[i].to] = dep[u] + 1;
			Dfs1(e[i].to);
			_time++;
			st[_time][0] = u;
			if (maxdep[e[i].to] > maxdep[u]) {
				maxdep[u] = maxdep[e[i].to];
				son[u] = e[i].to;
			}
		}
	}
	maxdep[u]++;
}

inline void Dfs2(int u, int tp) {
	top[u] = tp;
	dn[tp].push_back(u);
	if (son[u]) Dfs2(son[u], tp);
	for (register int i = hd[u];~i;i = e[i].nxt) {
		if (e[i].to != fa[u][0] && e[i].to != son[u]) Dfs2(e[i].to, e[i].to);
	}
}

inline void Prefix() {
	for (register int j = 1;j <= 20;j++) {
		for (register int i = 1;i <= n;i++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
	}
	for (register int i = 1;i <= n;i++) {
		register int siz = dn[i].size(), u = i;
		for (register int j = 0;j < siz;j++) {
			up[i].push_back(u);
			u = fa[u][0];
		}
	}
	//printf("_time=%d\n", _time);
	for (register int j = 1;j <= 20;j++) {
		for (register int i = 1;i <= _time;i++) {
			if (i + (1 << j) - 1 > _time) break;
			if (dep[st[i][j - 1]] < dep[st[i + (1 << j - 1)][j - 1]]) st[i][j] = st[i][j - 1];
			else st[i][j] = st[i + (1 << j - 1)][j - 1];
			//printf("%d %d %d\n", i, j, st[i][j]);
		}
	}
	for (register int i = 2;i <= _time;i++) _log[i] = _log[i >> 1] + 1;
}

inline int Up(int u, int k) {
	if (!k) return u;
	u = fa[u][highbit[k]];
	k -= 1 << highbit[k];
	if (k >= dep[u] - dep[top[u]]) return up[top[u]][k - dep[u] + dep[top[u]]];
	else return dn[top[u]][dep[u] - dep[top[u]] - k];
}

inline int Lca(int u, int v) {
	if (dfn[u] > dfn[v]) swap(u, v);
	register int k = _log[dfn[v] - dfn[u] + 1];
	if (dep[st[dfn[u]][k]] < dep[st[dfn[v] - (1 << k) + 1][k]]) return st[dfn[u]][k];
	else return st[dfn[v] - (1 << k) + 1][k];
}

inline pair <pair <int, int>, int> Path(int u, int v, int l, int k) {
	if (dep[u] - dep[l] + 1 >= k) {
		register int tmp = Up(u, k - 1);
		return make_pair(make_pair(u, tmp), tmp);
	} else return make_pair(make_pair(u, Up(v, dep[u] + dep[v] - (dep[l] << 1) + 1 - k)), l);
}

//u -> v
inline long long Hashval(int u, int v, int l, int id) {
	if (v == l) return Minus(uphash[u][id], uphash[fa[l][0]][id], mod[id]) * powInv26[dep[fa[l][0]]][id] % mod[id];
	else if (u == l) return Minus(dnhash[v][id], dnhash[fa[l][0]][id] * pow26[dep[v] - dep[l] + 1][id] % mod[id], mod[id]);
	register long long lhash = Minus(uphash[u][id], uphash[fa[l][0]][id], mod[id]) * powInv26[dep[fa[l][0]]][id] % mod[id];
	register long long rhash = Minus(dnhash[v][id], dnhash[l][id] * pow26[dep[v] - dep[l]][id] % mod[id], mod[id]);
	return Add(lhash * pow26[dep[v] - dep[l]][id] % mod[id], rhash, mod[id]);
}

inline int Query(int a, int b, int c, int d) {
	register int lab = Lca(a, b), lcd = Lca(c, d);
	//printf("lab=%d lcd=%d\n", lab, lcd);
	register int l = 0, r = Min(dep[a] + dep[b] - (dep[lab] << 1) + 1, dep[c] + dep[d] - (dep[lcd] << 1) + 1) + 1;
	//printf("l=%d r=%d\n", l, r);
	while (l < r - 1) {
		register int mid = l + r >> 1;
		register bool flag = 1;
		register pair <pair <int, int>, int> p1 = Path(a, b, lab, mid), p2 = Path(c, d, lcd, mid);
		//printf("mid=%d %d->%d %d->%d\n", mid, p1.first.first, p1.first.second, p2.first.first, p2.first.second);
		for (register int j = 0;j < 2;j++) {
			if (Hashval(p1.first.first, p1.first.second, p1.second, j) != Hashval(p2.first.first, p2.first.second, p2.second, j)) {
				flag = 0;
				break;
			}
		}
		if (flag) l = mid;
		else r = mid;
	}
	return l;
}

inline void Solve() {
	//printf("%lld\n", uphash[2][0]);
	//printf("%d\n", Hashval(2, 2, 2, 0));
	m = qread();
	while (m--) {
		register int a = qread(), b = qread(), c = qread(), d = qread();
		printf("%d\n", Query(a, b, c, d));
	}
}

int main() {
	memset(hd, -1, sizeof(hd));
	Read();
	Calc26();
	dep[1] = 1;
	Dfs1(1);
	Dfs2(1, 1);
	Prefix();
	Solve();
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}
```

---

## 作者：EnofTaiPeople (赞：7)

题意要求树上两条路径所表示的字符串的 LCP，有一个很 basic 的做法就是维护链上的字符串哈希值，优点在于支持 link/cut，链字符加或赋值等操作，时间复杂度为 $q\log_2^2n$，其实很优秀，然而缺点在于容易被卡，常数大，当然可以选择多哈希，但有一种更好的 $O(q\log_2n)$ 的做法。

考虑将树重链剖分，将两条路径表示成路径区间并配对（使所有区间一一对应），这样能将它们分成 $O(\log_2n)$ 段在重剖序中的区间（注意有可能是反重剖序，所以预处理需要同时记重剖序的正串反串）。

于是问题变成了：给定一个字符串，求其两个后缀的 LCP。

我们发现 SAM 是维护后缀的，更适合求最长公共后缀，所以需要将字符串反过来求两个前缀的最长公共后缀。

考虑 parent 树中，一个节点的父亲是它的最长真后缀，所以两个节点的 lca 就是它们的最长真后缀，可以打 ST 表 $O(1)$ 求。

接下来就是平凡的了，如果上一段的 LCP 等于长度，就继续算下一段，否则就停止，时间 $O(n(|\sum|+\log_2n)+q\log_2n)$，空间 $O(n(|\sum|+\log_2n))$，实测 ST 表会被卡空间，所以要用线段树求最值，当然也可以离线下来 tarjan（似乎会变麻烦？），反正就是用时间还空间，然而因为 zkw 线段树常数太小了，所以并不会被卡常。

[CF 上的 AC 记录](https://codeforces.com/contest/504/submission/191650086)

---

## 作者：fade_away (赞：6)

# Solution
这里怎么没有跑得飞快的SAM + 树链剖分的题解啊，我来补一发。

大概就是你发现暴力匹配很慢，因为它是一个一个匹配的，复杂度为$O(len)$，因此我们考虑一串一串地匹配。

## Part one
先思考一个更简单的问题：给你一个串，求两个后缀的LCP。
这是一个经典问题，我们可以对反串建后缀自动机，这样原串上后缀LCP转化为反串上前缀的最长公共后缀，那么答案就是两个原串上前缀在SAM上的对应结点的LCA的maxlen。

这样单次询问可以做到$O(logn)$或者$O(1)$（RMQ求LCA）。
## Part two
再考虑树上的问题，我们发现树的结构并不优美，很难支持直接询问两个链的LCP，于是我们考虑树链剖分，预处理重链的信息，建出每个重链对应的串和反串的SAM（相当于维护了所有链顶到$x$的串和链底到$x$的串，以应对自上而下以及自下而上的两种链），这样两个链的LCP就能够通过求LCA快速得到。于是我们把树上问题转化为单个字符串的问题。

现在问题相当于有两个分别有$O(logn)$个段的字符串，求它们的LCP，这个可以简单地从前到后按段依次匹配完成，每次询问的时间复杂度为$O(logn)$。注意如果我们写的是$O(logn)$的LCA，这里我们匹配的时候只需要先特判是否是完全包含，不是完全包含再跑LCA，这样总复杂度还是$O(logn)$。

因此总时间复杂度为$O(mlog^2n)$/$O(mlogn)$。

实现时细节较多，代码比较复杂。

虽然写的是暴力$O(mlog^2n)$（因为在匹配的时候用了vector的erase），但目前还是CF Execution Time rank1（达成成就

## Code
```cpp
#include <bits/stdc++.h>
 
using namespace std;
//长长的快读和头

int id[MAXN << 1], n, m;
vector<int> e[MAXN];
struct SAM {
	int sz = 2, lst = 1, t[MAXN << 1][26], len[MAXN << 1], fa[MAXN << 1];
	int dfn[MAXN << 1], fns[MAXN << 1], SZ[MAXN << 1], head[MAXN << 1], top[MAXN << 1], mx[MAXN << 1], dep[MAXN << 1], DFN = 0, edgenum = 0;
	struct enode{ int to, nxt; } e[MAXN << 1];

	void add(int u, int v) {
		e[++ edgenum] = (enode){v, head[u]}, head[u] = edgenum;
	}
	void Init() {
		memset(t, 0, (sz + 10) * sizeof t[0]);
		sz = 2, lst = 1;
	}
	void insert(int c) {
		int p = lst, np = lst = sz ++;
		len[np] = len[p] + 1;
		for (; p && !t[p][c] ; p = fa[p]) t[p][c] = np;
		if (!p) { fa[np] = 1; return; }
		int q = t[p][c];
		if (len[q] == len[p] + 1) fa[np] = q;
		else {
			int nq = sz ++;
			len[nq] = len[p] + 1;
			fa[nq] = fa[q];
			fa[np] = fa[q] = nq;
			memcpy(t[nq], t[q], sizeof t[0]);
			for (; p && t[p][c] == q ; p = fa[p]) t[p][c] = nq;
		}
	}
	void dfs1(int x) {
		SZ[x] = 1, dep[x] = dep[fa[x]] + 1;
		for (int i = head[x]; i ; i = e[i].nxt) {
			int v = e[i].to;
			dfs1(v);
			SZ[x] += SZ[v];
			if (SZ[v] > SZ[mx[x]]) mx[x] = v;
		}
	}
	void dfs2(int x, int Top) {
		dfn[x] = ++ DFN, top[x] = Top;
		if (mx[x]) dfs2(mx[x], Top);
		for (int i = head[x]; i ; i = e[i].nxt) if (e[i].to != mx[x]) dfs2(e[i].to, e[i].to);
		fns[x] = DFN;
	}
	void work() {
		for (int i = 2; i < sz ; ++ i) add(fa[i], i);
		dfs1(1), dfs2(1, 1);
	}
	int getLCA(int x, int y) {
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]]) swap(x, y);
			x = fa[top[x]];
		}
		return dep[x] < dep[y] ? len[x] : len[y];
	}
	int getLCP(int x, int y) {
		if (dfn[x] <= dfn[y] && fns[y] <= fns[x]) return len[x];
		if (dfn[y] <= dfn[x] && fns[x] <= fns[y]) return len[y];
		return getLCA(x, y);
	}
} sam;

struct Trie_Tree{
	vector<int> V[MAXN << 1];
	queue<int> que;
	int ch[MAXN][26], Lst[MAXN << 1], nodenum = 1;
	void insert(char *st, int *a, int len) {
		int nw = 1;
		for (int i = 0; i < len ; ++ i) {
			if (!ch[nw][st[i] - 'a']) ch[nw][st[i] - 'a'] = ++ nodenum;
			nw = ch[nw][st[i] - 'a'];
			V[nw].PB(a[i]);
		}
	}
	void build_SAM(int x) {
		Lst[1] = 1, que.push(1);
		while (!que.empty()) {
			int q = que.front(); que.pop();
			for (auto t : V[q]) id[t] = Lst[q];
			for (int i = 0; i < 26 ; ++ i) {
				int v = ch[q][i];
				if (!v) continue;
				sam.lst = Lst[q];
				sam.insert(i);
				Lst[v] = sam.lst;
				que.push(v);
			}
		}
	}
} trie;



int LEN = 0, a[MAXN << 1];
char ST[MAXN], st[MAXN];
int sz[MAXN], dep[MAXN], fa[MAXN], mx[MAXN], dfn[MAXN], fns[MAXN], top[MAXN], DFN = 0;
void dfs1(int x, int father) {
	sz[x] = 1, dep[x] = dep[father] + 1, fa[x] = father;
	for (auto v : e[x]) {
		if (v == father) continue;
		dfs1(v, x);
		sz[x] += sz[v];
		if (sz[v] > sz[mx[x]]) mx[x] = v;
	}
}
void dfs2(int x, int Top) {
	dfn[x] = ++ DFN, top[x] = Top;
	if (mx[x]) dfs2(mx[x], Top);
	for (auto v : e[x]) {
		if (v == fa[x] || v == mx[x]) continue;
		dfs2(v, v);
	}
	fns[x] = DFN;
}

void build_trie(int x) {
	ST[LEN] = st[x], a[LEN] = dfn[x], ++ LEN;
	if (!mx[x]) {
		trie.insert(ST, a, LEN);
		reverse(ST, ST + LEN);
		reverse(a, a + LEN);
		for (int i = 0; i < LEN ; ++ i) a[i] += n;
		trie.insert(ST, a, LEN);
		LEN = 0;
	}
	else build_trie(mx[x]);

	for (auto v : e[x]) {
		if (v == fa[x] || v == mx[x]) continue;
		build_trie(v);
	}
}


vector<PR> stk, P, Q;
void getpath(vector<PR> &P, int A, int B) {
	P.clear(), stk.clear();
	while (top[A] != top[B]) {
		if (dep[top[A]] < dep[top[B]]) stk.PB(MP(dfn[top[B]], dfn[B])), B = fa[top[B]];
		else P.PB(MP(dfn[A], dfn[top[A]])), A = fa[top[A]];	
	}
	P.PB(MP(dfn[A], dfn[B]));
	
	reverse(stk.begin(), stk.end());
	P.insert(P.end(), stk.begin(), stk.end());
}

int solve() {
	int ans = 0;
	PR x = *P.begin(), y = *Q.begin();
	int fx = (x.fi < x.se), fy = (y.fi < y.se);
	while (P.size() && Q.size()) {
		int X, Y;
		if (fx) X = x.fi + n; else X = x.fi; 
		if (fy) Y = y.fi + n; else Y = y.fi;
		
		int len = min(sam.getLCP(id[X], id[Y]), min(abs(x.se - x.fi), abs(y.se - y.fi)) + 1);
		ans += len;
		
		if (fx) x.fi += len; else x.fi -= len;
		if (fy) y.fi += len; else y.fi -= len;
		
		int flag = 0;
		if ((fx && x.fi > x.se) || (!fx && x.fi < x.se)) flag = 1, P.erase(P.begin()), x = *P.begin(), fx = (x.fi < x.se);
		if ((fy && y.fi > y.se) || (!fy && y.fi < y.se)) flag = 1, Q.erase(Q.begin()), y = *Q.begin(), fy = (y.fi < y.se);
		if (!flag) break;
	}
	return ans;
}

signed main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	read(n), reads(st + 1);
	for (int i = 1, u, v; i < n ; ++ i) read(u), read(v), e[u].PB(v), e[v].PB(u);
	read(m);

	dfs1(1, 0);
	dfs2(1, 1);   
	build_trie(1);
	trie.build_SAM(1);
	sam.work();
	for (int i = 1, A, B, C, D; i <= m ; ++ i) {
		read(A), read(B), read(C), read(D);
		getpath(P, A, B);
		getpath(Q, C, D);
		print(solve());
		putc('\n');
	}
	return 0;
}
```


---

## 作者：little_sun (赞：2)

### 题目大意

给你一棵有$n$个节点的树，每个节点上有一个字符$c$。

有$m$次询问，每次询问$a\sim b$路径上的字符串和$c \sim d$路径上的字符串的最长公共前缀$\texttt{(LCP)}$

$n \leq 3 \times 10^5,\; m \leq 10^6$

### 分析

发现普通的$\texttt{LCP}$可以通过二分$+$哈希求出，我们考虑把这个做法拓展到树上。

维护$\texttt{h[u]}$表示根到$u$路径上的字符串哈希值，$\texttt{revh[u]}$表示$u$到根路径上的哈希值，则$u \sim v$路径上的哈希值可以表现为$\texttt{revh[u, lca]} \times \texttt{base}^{dv} + \texttt{h(lca,v])}$，其中$\texttt{dv}$表示$\texttt{v}$到$\texttt{lca}$的距离；而询问$u$和$v$到$\texttt{lca}$的哈希值可以视为一个序列问题解决。

回到原问题，我们二分$\texttt{LCP}$的长度$\texttt{k}$，并找到$\texttt{(a, b), (c, d)}$路径上第$\texttt{k}$个节点（记为$v_1, v_2$），判断$\texttt{(a,v1)}$与$\texttt{(c,v2)}$链上的哈希值是否相等，并调整二分区间，最后的$l$就是答案

时间复杂度$\mathcal{O}\texttt{((n + m) log n)}$，详细实现参见代码

### 代码

``` cpp
#include <bits/stdc++.h>

#define R register
#define ll long long
#define sum(a, b, mod) (((a) + (b)) % mod)

const int MaxN = 1e6 + 10;
const int mod = 998244853;

struct edge
{
    int next, to;
};

struct mod_t
{
    static int norm(int x) { return x + (x >> 31 & mod); }
    int x;
    mod_t() {}
    mod_t(int v) : x(v) {}
    mod_t(long long v) : x(v) {}
    mod_t(char v) : x(v) {}
    mod_t operator+(const mod_t &rhs) const { return norm(x + rhs.x - mod); }
    mod_t operator-(const mod_t &rhs) const { return norm(x - rhs.x); }
    mod_t operator*(const mod_t &rhs) const { return (ll)x * rhs.x % mod; }
};

edge e[MaxN << 1];
std::vector<int> up[MaxN], down[MaxN];

char s[MaxN];
int n, m, cnt;
mod_t h[MaxN], revh[MaxN], powm[MaxN], invp[MaxN], base, inv;
int son[MaxN], fa[MaxN][24], f[MaxN][24], Dep[MaxN], pos[MaxN];
int head[MaxN], dep[MaxN], maxd[MaxN], fir[MaxN], lg2[MaxN], top[MaxN];

void add_edge(int u, int v)
{
    ++cnt;
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

int querykth(int u, int k)
{
    if (!k) return u;
    u = fa[u][lg2[k]], k -= (1 << lg2[k]);
    k -= dep[u] - dep[top[u]], u = top[u];
    return ((k >= 0) ? up[u][k] : down[u][-k]);
}

int querylca(int u, int v)
{
    int l = fir[u], r = fir[v], k;
    if (l > r) std::swap(l, r);
    k = lg2[r - l + 1];
    return (Dep[f[l][k]] <= Dep[f[r - (1 << k) + 1][k]]) ? pos[f[l][k]] : pos[f[r - (1 << k) + 1][k]];
}

mod_t fast_pow(mod_t a, int b)
{
    mod_t ret = 1;
    while (b)
    {
        if (b & 1)
            ret = ret * a;
        a = a * a, b >>= 1;
    }
    return ret;
}

void init()
{
    srand(time(NULL));
    powm[0] = invp[0] = 1, base = (rand() % 2000) + 1001;
    inv = fast_pow(base, mod - 2);
    for (int i = 1; i <= n; i++)
    {
        powm[i] = (powm[i - 1] * 1ll * base);
        invp[i] = (invp[i - 1] * 1ll * inv);
    }
}

void prework()
{
    lg2[0] = -1;
    for (int i = 1; i <= cnt; i++)
        lg2[i] = lg2[i >> 1] + 1, f[i][0] = i;
    for (int j = 1; (1 << j) <= cnt; j++)
    {
        for (int i = 1; i <= cnt - (1 << j) + 1; i++)
            f[i][j] = (Dep[f[i][j - 1]] <= Dep[f[i + (1 << (j - 1))][j - 1]]) ? f[i][j - 1] : f[i + (1 << (j - 1))][j - 1];
    }
}

inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch <= '9' && ch >= '0')
        x = (x << 1) + (x << 3) + (ch - 48), ch = getchar();
    return x;
}

void dfs(int u, int fa)
{
    Dep[++cnt] = maxd[u] = dep[u] = dep[fa] + 1, ::fa[u][0] = fa;
    pos[cnt] = u, h[u] = h[fa] * 1ll * base + s[u];
    fir[u] = cnt, revh[u] = revh[fa] + powm[dep[fa]] * s[u];
    for (int i = 1; i <= 20; i++)
        ::fa[u][i] = ::fa[::fa[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].to;
        if (v == fa) continue;
        dfs(v, u), pos[++cnt] = u, Dep[cnt] = dep[u];
        if (maxd[v] > maxd[u])
            maxd[u] = maxd[v], son[u] = v;
    }
}

void dfs1(int u, int top)
{
    ::top[u] = top;
    if (u == top)
    {
        int x = u;
        for (int i = 0; i <= maxd[u] - dep[u]; i++)
            up[u].push_back(x), x = fa[x][0];
        x = u;
        for (int i = 0; i <= maxd[u] - dep[u]; i++)
            down[u].push_back(x), x = son[x];
    }
    if (son[u]) dfs1(son[u], top);
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].to;
        if (v != son[u] && v != fa[u][0]) dfs1(v, v);
    }
}

int qhash(int u, int v, int lca, int flca)
{
    int dv = dep[v] - dep[lca];
    mod_t h1 = (revh[u] - revh[flca] + mod) * invp[dep[flca]], h2, H;
    h2 = (h[v] - h[lca] * powm[dv]), H = h1 * powm[dv] + h2;
    return H.x;
}

int get(int u, int v, int k)
{
    int lca = querylca(u, v), d = dep[u] + dep[v] - 2 * dep[lca] + 1;
    return (k <= dep[u] - dep[lca]) ? 1 : 0;
}

int path(int u, int v, int k)
{
    int lca = querylca(u, v), d = dep[u] + dep[v] - 2 * dep[lca] + 1;
    if (k <= dep[u] - dep[lca])
        return querykth(u, k - 1);
    else
        return querykth(v, d - k);
}

int query(int a, int b, int c, int d)
{
    if (s[a] != s[c]) return 0;
    int lca1 = querylca(a, b), flca1 = fa[lca1][0], d1 = dep[a] + dep[b] - 2 * dep[lca1] + 1;
    int lca2 = querylca(c, d), flca2 = fa[lca2][0], d2 = dep[c] + dep[d] - 2 * dep[lca2] + 1;
    int l = 1, r = std::min(d1, d2);
    // printf("debug: a = %d, b = %d, c = %d, d = %d, lca(a, b) = %d, lca(c, d) = %d\n", a, b, c, d, lca1, lca2);
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        int x1 = get(a, b, mid), x2 = get(c, d, mid);
        int v1 = path(a, b, mid), v2 = path(c, d, mid);
        // printf("Debug: l = %d, r = %d, mid = %d, v1 = %d, v2 = %d\n", l, r, mid, v1, v2);
        if (qhash(a, v1, (x1 ? v1 : lca1), (x1 ? fa[v1][0] : flca1)) == qhash(c, v2, (x2 ? v2 : lca2), (x2 ? fa[v2][0] : flca2)))
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}

int main()
{
    scanf("%d\n%s", &n, s + 1), init();
    for (int i = 1; i < n; i++)
    {
        int u = read(), v = read();
        add_edge(u, v), add_edge(v, u);
    }
    m = read(), cnt = 0, dfs(1, 0), dfs1(1, 1), prework();
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read(), c = read(), d = read();
        printf("%d\n", query(a, b, c, d));
    }
    return 0;
}
```



---

## 作者：xfrvq (赞：1)

[$\tt Link$](/problem/CF504E)。

序列上的原问题有个 trick：二分 LCP 长度，再用哈希判断两条路径是否完全相等。

二分占去一个 $\log$，又有 $m\le10^6$，那我们只能在 $O(1)$ 的时间求哈希值了。

考虑路径哈希值怎么求。我是把路径想象为 $k$ 进制数（$k\gt26$，为了方便逆元 $k$ 为质数）。

然后对于每个点 $p$ 预处理 $p\to1$ 的路径的答案 $f$ 和 $1\to p$ 的路径的答案 $g$（$1$ 是根）。

求路径 $u\to v$ 的答案就先 $O(1)$ 求它们的 LCA $p$，分别使用 $f$ 和 $g$ 得到 $p\to v$ 和 $u\to p$ 的值，合并即可。

但是。怎么知道二分时跳了 $mid$ 步的两个左端点去到了哪里？这里需要长剖树上 $k$ 级祖先并分类讨论有没有跳过 $\tt lca$。

需要双哈希。

确实挺简单的，但是有了长剖，$O(1)$ LCA，巨大双哈希之后写起来和大模拟一样。

代码：<https://www.luogu.com.cn/paste/314zxi88>

---

## 作者：_ZSR_ (赞：0)

### [CF504E Misha and LCP on Tree](https://www.luogu.com.cn/problem/CF504E)

判断两个字符串的公共前缀肯定先想到哈希，然后又要最长，显然可以二分。因为字符串有序，即 $u$ 到 $v$ 的字符串和 $v$ 到 $u$ 的字符串是不同的，所以维护两个哈希数组。一个是根到节点 $u$ 的哈希值 $dist_u$，一个是节点 $u$ 到根的哈希值 $rdist_u$。每次二分长度的时候把当前二分的长度的哈希值用那两个数组凑出来，具体看代码，然后判断是否相等即可。

时间复杂度 $O(m \log^2 n)$。

code
```
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10,mod=998244353,bas=19260817,invb=494863259;
typedef long long ll;
int n,m,tot;
char str[N];
int h[N],to[N<<1],nxt[N<<1],idx;
int dep[N],size[N],top[N],f[N],son[N],dfn[N],rdfn[N];
ll hashbase[N],inv[N],dist[N],rdist[N];
inline void add(int a,int b)
{
	to[++idx]=b;
	nxt[idx]=h[a];
	h[a]=idx;
}
void dfs1(int u,int fa)
{
	f[u]=fa;
	size[u]=1;
	dep[u]=dep[fa]+1;
	dist[u]=(dist[fa]*bas%mod+str[u]-'a')%mod,rdist[u]=(1ll*(str[u]-'a')*hashbase[dep[fa]]%mod+rdist[fa])%mod;
	for (int i=h[u];i;i=nxt[i])
	{
		int v=to[i];
		if (v==fa) continue;
		dfs1(v,u);
		size[u]+=size[v];
		if (size[v]>size[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int t)
{
	top[u]=t;
	dfn[u]=++tot,rdfn[tot]=u;
	if (son[u]) dfs2(son[u],t);
	for (int i=h[u];i;i=nxt[i])
	{
		int v=to[i];
		if (v==f[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
inline int lca(int a,int b)
{
	while (top[a]!=top[b])
	{
		if (dep[top[a]]<dep[top[b]]) swap(a,b);
		a=f[top[a]];
	}
	if (dep[a]<dep[b]) return a;
	else return b;
}
inline int k_ancestor(int x,int k)
{
	while (dep[x]-dep[top[x]]<k)
	{
		k-=dep[x]-dep[top[x]]+1;
		x=f[top[x]];
	}
	return rdfn[dfn[x]-k];
}
inline ll gethash(int a,int b,int p,int len)
{
	if (dep[a]-dep[p]+1>=len)//没有越过最近公共祖先
	{
		int fa=k_ancestor(a,len);
		return ((rdist[a]-rdist[fa])*inv[dep[fa]]%mod+mod)%mod;
	}
	int x=dep[a]-dep[p],y=k_ancestor(b,dep[a]+dep[b]-dep[p]*2+1-len);
	ll dist1=((rdist[a]-rdist[p])*inv[dep[p]]%mod+mod)%mod,dist2=(dist[y]-dist[f[p]]*hashbase[len-x]%mod+mod)%mod;//dist1是左边不包括lca的哈希，dist2是右边包括lca的哈希
	return (dist1*hashbase[len-x]+dist2)%mod;
}
int main()
{
	scanf("%d",&n);
	scanf("%s",str+1);
	for (int i=1;i<n;++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b),add(b,a);
	}
	hashbase[0]=inv[0]=1;
	for (int i=1;i<=n;++i)
	{
		hashbase[i]=hashbase[i-1]*bas%mod;
		inv[i]=inv[i-1]*invb%mod;
	}
	dfs1(1,0);
	dfs2(1,1);
	scanf("%d",&m);
	for (int i=1,a,b,c,d;i<=m;++i)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		int x=lca(a,b),y=lca(c,d),lx=dep[a]+dep[b]-dep[x]*2+1,ly=dep[c]+dep[d]-dep[y]*2+1;
		int l=0,r=min(lx,ly),ans=0;
		while (l<=r)
		{
			int mid=l+r>>1;
			if (gethash(a,b,x,mid)==gethash(c,d,y,mid)) l=mid+1,ans=mid;
			else r=mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}		 	
```


---

