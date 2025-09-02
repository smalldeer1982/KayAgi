# Mashmokh's Designed Problem

## 题目描述

给定一棵 $n$ 个节点的有根树，每个点连出的边都有序，共有 $m$ 个操作。（$n \le 10^5,m \le 10^5$）

操作有：

- 1.查询两个点 $u,v$ 的距离
- 2.以 $v$ 为根的子树从树中分开，并添加一条与其第 $h$ 个祖先的连边作为该祖先的最后一个儿子。
- 3.查询从一个点出发，按边的顺序进行 dfs,深度为 $k$ 的最后遍历的点

## 样例 #1

### 输入

```
4 9
1 2
1 3
1 4
0
1 1 4
2 4 2
1 3 4
3 1
3 2
2 3 2
1 1 2
3 1
3 2
```

### 输出

```
3
2
2
4
1
3
4
```

## 样例 #2

### 输入

```
2 2
1 2
0
1 2 1
3 1
```

### 输出

```
1
2
```

# 题解

## 作者：jun头吉吉 (赞：7)

## 题意
给定一棵 $n$ 个节点的有根树，每个点连出的边都有序，共有 $m$ 个操作。操作分三类：

1. 查询两个点 $u,v$ 的距离
2. 以 $v$ 为根的子树从树中分开，并添加一条与其第 $h$ 个祖先的连边作为该祖先的最后一个儿子。
3. 查询从一个点出发，按边的顺序进行dfs,深度为 $k$ 的最后遍历的点

$(n \le 10^5,m \le 10^5)$
## 题解
如果只有 $1$、$2$ 似乎可以 $\mathbb{LCT}$ 做，但边有顺序无疑让其无法实现。

树的遍历想到欧拉序 ~~（别问我怎么想到的）~~，通过欧拉序，边就都有序了，于是可以完成以上的操作。

记节点 $i$ 在欧拉序中第一遍为 $in[i]$ ，第二遍为 $out[i]$

![](https://cdn.luogu.com.cn/upload/image_hosting/w8ne133n.png)

欧拉序：$1\ 2\ 3\ 4\ 4\ 3\ 2\ 1$
### 操作一
如果我们记节点 $i$ 的深度为 $dep_i$，那么 $u\to v$ 的距离就是 $dep_u+dep_v-2\times dep_{lca(u,v)}$

假如我们已经能够维护 $u,v$ 的深度那么考虑 $\rm  lca$ 的深度与欧拉序有什么关系。

![](https://cdn.luogu.com.cn/upload/image_hosting/v4qwx2qt.png)

如果我们查$5\to3$的$\rm lca$

欧拉序：$\color{black}1\ 2\ 5\ \color{red}5\ 2\ 4\ 4\ 3\  6\ \color{black}3\ 1$

发现在 $(in[u],out[v])$ 之间的所有点全在他们的 $\rm lca$ 以下，取这一段深度的最小值加一即可。

不过注意此时 $u$ 比 $v$ 先访问，如果不满足就强行`swap(u,v)`

取最小值操作我们可以用 $\rm Splay$实现。（别问我为什么不用线段树，因为还有其他操作（
### 操作二
用欧拉序我们可以轻松摘下一棵树再挂上去：

![](https://cdn.luogu.com.cn/upload/image_hosting/i829zcti.png)

欧拉序：$\color{black}1\ 2\ \color{red}4\ 6\ 6\ 5\ 5\ 4\ \color{black}2\ 3\ 3\ 1$

把 $4$ 的子树摘下来挂到 $1$ 上

![](https://cdn.luogu.com.cn/upload/image_hosting/zog7x39y.png)

欧拉序： $\color{black}1\ 2\ 2\ 3\ 3\ \color{blue}4\ 6\ 6\ 5\ 5\ 4\ \color{black}1$

不难发现把 $v$ 挂到 $u$ 上就是把 $[in[v],out[v]]$ 这段区间插到 $out[u]$ 之前，并把其深度都减少 $h-1$

现在大量的序列操作， $\rm Splay$ **序列之王**的用处就体现出来了。

于是现在的问题变为怎么找到 $u$ ，其实就是 $[1,in[v])$中最后一个深度为 $dep[v]-h$ 的点，于是自然引入了操作3
### 操作三
对于一个深度为 $k$ 的节点，如果他排列在最后，那么他在欧拉序中的出现也一定在最后。

那么我们对每个节点维护最大值 $mx$ 与最小值 $mn$ ，并优先访问右儿子（如果$k\in [mn_l,mx_l]$），再是当前节点、左儿子。

那么现在用 $\mathcal{O}(\log n)$ 的时间，就可以找到最后一个深度为 $k$ 的了。那么在 **操作二**寻找指定深度的节点也可以迎刃而解了。

$\rm Splay$维护序列这里就不细讲了，做几个模板就都会了。
## 代码
```cpp
#include<bits/stdc++.h>
//#define faster
namespace fin{
	#ifdef faster
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
	#else
	inline int getc(){return getchar();}
	#endif
	template <typename T>inline void read(T& t){
		t=0;int f=0;char ch=getc();while (!isdigit(ch)){if(ch=='-')f = 1;ch=getc();}
	    while(isdigit(ch)){t=t*10+ch-48;ch = getc();}if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){read(t);read(args...);}
}
namespace fout{
	char buffer[1<<21];int p1=-1;const int p2 = (1<<21)-1;
	inline void flush(){fwrite(buffer,1,p1+1,stdout),p1=-1;}
	inline void putc(const char &x) {if(p1==p2)flush();buffer[++p1]=x;}
	template <typename T>void write(T x) {
		static char buf[15];static int len=-1;if(x>=0){do{buf[++len]=x%10+48,x/=10;}while (x);}else{putc('-');do {buf[++len]=-(x%10)+48,x/=10;}while(x);}
		while (len>=0)putc(buf[len]),--len;
	}
}
using namespace std;
const int N=2e5+10;
int n,m,in[N],out[N],id[N],dep[N],cnt;
vector<int>e[N];int root;
void dfs(int u,int dep){
	in[u]=++cnt,id[cnt]=u,::dep[cnt]=dep;
	for(auto v:e[u])dfs(v,dep+1);
	out[u]=++cnt,id[cnt]=u,::dep[cnt]=dep;
}
int f[N],ch[N][2],mn[N],mx[N],tag[N],sz[N];
#define min3(a,b,c) min((a),min(b,c))
#define max3(a,b,c) max((a),max(b,c))
void pushup(int x){
	int l=ch[x][0],r=ch[x][1];
	sz[x]=sz[l]+1+sz[r];
	mx[x]=max3(mx[l],dep[x],mx[r]);
	mn[x]=min3(mn[l],dep[x],mn[r]);
}
void add(int x,int val){
	mn[x]+=val,mx[x]+=val,tag[x]+=val,dep[x]+=val;
}
void pushdown(int x){
	int l=ch[x][0],r=ch[x][1];
	if(tag[x]){
		if(l)add(l,tag[x]);
		if(r)add(r,tag[x]);
	}tag[x]=0;
}
#define get(x) (ch[f[(x)]][1]==(x))
#define connect(x,y,p) {if(x)f[(x)]=(y);if(y)ch[(y)][(p)]=(x);}
void rotate(int x){
	int fa=f[x],ffa=f[fa],p1=get(x),p2=get(fa);
	connect(ch[x][p1^1],fa,p1);
	connect(fa,x,p1^1);
	connect(x,ffa,p2);
	pushup(fa);pushup(x);
}
void splay(int x,int goal=0){
	stack<int>q;q.push(x);
	for(int fa=x;f[fa]!=goal;fa=f[fa])q.push(f[fa]);
	while(q.size())pushdown(q.top()),q.pop();
	for(int fa;(fa=f[x])!=goal;rotate(x))
		if(f[fa]!=goal)rotate(get(x)==get(fa)?fa:x);
	if(!goal)root=x;
}
#define mid (l+r>>1)
int build(int l,int r){
	if(l<mid)ch[mid][0]=build(l,mid-1),f[ch[mid][0]]=mid;
	if(mid<r)ch[mid][1]=build(mid+1,r),f[ch[mid][1]]=mid;
	pushup(mid);return mid;
}
int findk(int x,int k){
	int l=ch[x][0],r=ch[x][1];pushdown(x);
	if(mn[r]<=k&&k<=mx[r])return findk(r,k);
	else if(dep[x]==k){splay(x);return id[x];}
	else return findk(l,k);
}
int split(int l,int r){
	splay(l);splay(r,l);return ch[r][0];
}
int getpre(int x){
	splay(x);x=ch[x][0];
	while(ch[x][1])x=ch[x][1];
	splay(x);return x;
}
int getsuf(int x){
	splay(x);x=ch[x][1];
	while(ch[x][0])x=ch[x][0];
	splay(x);return x;
}
int del(int l,int r){
	int L=getpre(l),R=getsuf(r);
	int x=split(L,R),y=f[x];
	ch[y][0]=f[x]=0;pushup(y);pushup(f[y]);
	return x;
}
signed main(){
	fin::read(n,m);
	for(int i=1,u,v;i<=n;i++){
		fin::read(u);
		for(int j=1;j<=u;j++)fin::read(v),e[i].push_back(v);
	}
	mn[0]=0x3f3f3f3f;
	dfs(1,0);build(1,cnt);
	while(m--){
		int op,u,v,k;
		fin::read(op);
		if(op==1){
			fin::read(u,v);
			splay(in[u]);int rku=sz[ch[in[u]][0]]+1,res=dep[in[u]];
			splay(in[v]);int rkv=sz[ch[in[v]][0]]+1;res+=dep[in[v]];
			if(rku>rkv)swap(u,v);u=split(in[u],out[v]);res-=(mn[u]-1)*2;
			fout::write(res);fout::putc('\n');
		}else if(op==2){
			fin::read(u,v);int val=v-1;
			splay(in[u]);v=findk(ch[in[u]][0],dep[in[u]]-v);
			u=del(in[u],out[u]);add(u,-val);
			int rt=getpre(out[v]);splay(rt);
			splay(out[v],rt);
			connect(u,out[v],0);
			pushup(out[v]),pushup(rt);
		}else{
			fin::read(k);
			splay(1);
			fout::write(findk(1,k));fout::putc('\n');
		}
	}
	fout::flush();
	return 0;
}
```

---

## 作者：_LPF_ (赞：4)

来一发 fhq_treap 的题解。

[CF414E Mashmokh's Designed Problem](https://www.luogu.com.cn/problem/CF414E)

> 给定一棵有根树（$1$ 为根），初始树边按优先级顺序给出，支持三种操作：
>
> - `1 u v`：查询 $u,v$ 之间的距离。
> - `2 u h`：将 $u,fa_u$ 之间的边断开，并连接 $u$ 与它的 $h$ 级祖先（即距离它 $h$ 的祖先），这条边的优先级最劣。
> - `3 k`，查询整棵树按照边的优先级顺序 dfs 后，最后遍历到的深度为 $k$ 的节点的编号。

第一眼 LCT，但是 $3$ 操作始终难以维护，考虑将问题转化为序列问题。

和树上莫队的思想类似，利用括号序来维护三种操作，设 $\text{in}_u,\text{out}_u$ 分别表示节点 $u$ 的入/出栈时间戳。

## 操作一

众所周知 $\text{dis}(u,v)=\text{dep}_u+\text{dep}_v-2\times \text{dep}_{\text{lca(u,v)}}$。

假设 $\text{in}_u<\text{in}_v$，显然 $(\text{in}_u,\text{out}_v)$ 之间的节点中，深度最小的恰比 $\text{lca}(u,v)$ 大 $1$。

对应到平衡树上，就是单点查询和求区间 $\min$。

## 操作三

先说操作三是因为操作二有部分基于它。

全局最后遍历的，显然就是括号序中，编号最大的 深度为 $k$ 的 数字对应的节点编号。

对应到平衡树上，即在每个节点上维护深度的 $\min/\max$，每次如果右子节点中有 $k$ 就往右走。

实际上利用了括号序列的连续性，就是两个深度为 $a,b$ 的节点之间，一定夹着深度为 $[a,b]$ 的节点。

## 操作二

首先要找到它的 $h$ 级祖先，那显然就是括号序 $[1,\text{in}_u)$ 中，深度为 $\text{dep}_u-h$ 的编号最大的节点。

求法类似操作三，设其为 $H$，然后将区间 $[\text{in}_u,\text{out}_u]$ 整体平移插入至 $\text{out}_H$ 之前即可，当然也要将这个区间的 $\text{dep}$ 整体 $-(h-1)$。

对应到平衡树上，就是区间分裂合并 + 区间减法。

## 综上

已经得到了一个不错的 $\mathcal O(n\log n)$ 的解法。

在实现上还有一点特别的，实现时常常要根据节点编号，寻找现在节点在序列中的位置。

方法是记录每个节点的 $\text{fa}$，然后每次暴力跳 $\text{fa}$ 来统计前序遍历时，在它前面的节点个数。

因为 treap 的堆性质，期望下树高为 $\mathcal O(\log n)$，所以复杂度是对的。

这是普通的 fhq_treap 所没有的，$\text{fa}$ 标记只需要在 push_up 时顺便维护即可。

```cpp
#include<bits/stdc++.h>
typedef long long LL;
#define rep(i, s, t) for(int i = (s); i <= (t); i ++)
#define per(i, s, t) for(int i = (s); i >= (t); i --)
#define Ede(i, u) for(int i = head[u]; i; i = e[i].nxt)
using namespace std;

const int N = 2e5 + 10;
int n, m, Rt, tot, in[N], out[N], id[N];
struct Tree {int l, r, fa, siz, val, div, Mx, Mn, Rnd;} t[N];
mt19937 myrand(20051024);

int read() {
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') f = (c == '-') ? - 1 : 1, c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
	return x * f;
}

int New(int val) {
	t[++ tot] = (Tree) {0, 0, 0, 1, val, 0, val, val, (int) myrand() % 20060814};
	return tot;
}

void Div(int o, int v) {t[o].val -= v, t[o].Mx -= v, t[o].Mn -= v, t[o].div += v;}

void Dow(int o) {
	if(t[o].div) {
		if(t[o].l) Div(t[o].l, t[o].div);
		if(t[o].r) Div(t[o].r, t[o].div);
		t[o].div = 0;
	}
}

void Upd(int o) {
	int l = t[o].l, r = t[o].r;
	t[o].siz = t[l].siz + t[r].siz + 1;
	t[o].Mx = t[o].Mn = t[o].val;
	if(l)
		t[o].Mx = max(t[o].Mx, t[l].Mx), 
		t[o].Mn = min(t[o].Mn, t[l].Mn), 
		t[l].fa = o;
	if(r)
		t[o].Mx = max(t[o].Mx, t[r].Mx), 
		t[o].Mn = min(t[o].Mn, t[r].Mn), 
		t[r].fa = o;
}

int Mer(int x, int y) {
	if(! x || ! y) return x | y;
	if(t[x].Rnd < t[y].Rnd)
		{Dow(x), t[x].r = Mer(t[x].r, y), Upd(x); return x;}
	else
		{Dow(y), t[y].l = Mer(x, t[y].l), Upd(y); return y;}
}

void Spl(int o, int s, int &x, int &y) {
	if(! o) {x = y = 0; return;}
	Dow(o);
	if(t[t[o].l].siz >= s)
		y = o, Spl(t[o].l, s, x, t[o].l);
	else
		x = o, Spl(t[o].r, s - t[t[o].l].siz - 1, t[o].r, y);
	Upd(o);
}

void Push(int o) {if(! o) return; Push(t[o].fa); Dow(o);}

int Pos(int o) {
	Push(o); int ans = t[t[o].l].siz + 1;
	while(o != Rt) {
		if(o == t[t[o].fa].r) ans += t[t[o].fa].siz - t[o].siz;
		o = t[o].fa;
	}
	return ans;
}

int x, y, z;

#define Get Spl(Rt, l - 1, x, y), Spl(y, r - l + 1, y, z)
#define Los Rt = Mer(Mer(x, y), z)

int Min(int l, int r) {Get; int ans = t[y].Mn; Los; return ans;}

int Las(int l, int r, int dep) {
	Get; int o = y;
	while(true) {
		Dow(o);
		int l = t[o].l, r = t[o].r;
		if(t[r].Mn <= dep && t[r].Mx >= dep) o = r;
		else if(t[o].val == dep) break;
		else o = t[o].l;
	}
	Los; return o;
}

void Moi(int l, int r, int v) {Get; Div(y, v); Los;}

void Mov(int l, int r, int to) {
	int a, b, c, d;
	if(to <= l)
		Spl(Rt, to - 1, a, b), Spl(b, l - to, b, c), Spl(c, r - l + 1, c, d);
	else
		Spl(Rt, l - 1, a, b), Spl(b, r - l + 1, b, c), Spl(c, to - r - 1, c, d);
	Rt = Mer(Mer(Mer(a, c), b), d);
}

vector<int> G[N];

void dfs(int u, int dep) {
	Rt = Mer(Rt, New(dep)), id[in[u] = tot] = u;
	for(int v : G[u]) dfs(v, dep + 1);
	Rt = Mer(Rt, New(dep)), id[out[u] = tot] = u;
}

int main() {
	n = read(), m = read();
	rep(u, 1, n) {
		int c = read();
		while(c --) G[u].push_back(read());
	}
	dfs(1, 1);
	while(m --) {
		int opt = read();
		if(opt == 1) {
			int u = read(), L = Pos(in[u]);
			int v = read(), R = Pos(in[v]);
			if(L > R) swap(u, v);
			printf("%d\n", t[in[u]].val + t[in[v]].val - 2 * (Min(Pos(in[u]) + 1, Pos(out[v]) - 1) - 1));
		}
		else if(opt == 2) {
			int u = read(), L = Pos(in[u]), R = Pos(out[u]);
			int k = read(), h = Las(1, L - 1, t[in[u]].val - k);
			Moi(L, R, k - 1), Mov(L, R, Pos(out[id[h]]));
		}
		else {
			int k = read() + 1;
			printf("%d\n", id[Las(1, 2 * n, k)]);
		}
	}
	return 0;
}
```

---

## 作者：jerry3128 (赞：2)

题解：splay & 括号序。
- 考虑到儿子先后这么敏感的东西，那么 LCT 肯定是比较难以维护的了。
- 在 ETT 载体选择的时候，我们应考虑多方面。欧拉序拥有最为完整的信息，并且能够支持换根，但是相对应的，它维护起来一定就会更加的繁冗。括号序虽然不能换根，但是在它能实现的情况下有较大的操作范围，且比较易于实现。
- 回到本题，发现维护上述信息只用括号序可以直接维护，故选择括号序。
- 为了对简化对操作二的实现，我们直接将所有的“最后一次遍历”改为“第一次遍历”，并将初始儿子顺序翻转。
- 那么考虑三种操作：
	- 操作一就是通过二者间求出 LCA 的深度直接加减计算即可。
   - 操作二就是将某个节点的子树区间提出，置于其父亲的最开始的 DFS 序，因为我们已经翻转 DFS 序。
   - 操作三就是查找一个节点的 “入” 节点后第一个深度大于等于 k 的节点。

- 考虑一些实现细节。
- 括号序中，“入”和“出”，查找 k 级祖先和第一个遍历到深度大于 k 的点就是前后缀直接查找深度的最值，平衡树上二分即可。换父亲还有区间的深度修改。至此本题所有操作得以解决。

```
//ayame保佑，夸哥保佑，狗妈保佑，MDR保佑，锉刀怪保佑，M99保佑，克爹保佑
#include<bits/stdc++.h>
using namespace std;
int p1=1000000,p2=0;
char buf[1000005],wb[1000005];
int gc() {
	if(p1>=1000000)fread(buf,1,1000000,stdin),p1=0;
	return buf[p1++];
}
#define gc getchar
#define Loli true
#define Kon xor true
long long getint() {
	long long ret=0,flag=1;
	char c=gc();
	while(c<'0'||c>'9') {
		if(c=='-')flag=-1;
		c=gc();
	}
	while(c<='9'&&c>='0') {
		ret=(ret<<3)+(ret<<1)+c-'0';
		c=gc();
	}
	return ret*flag;
}
void pc(char x) {
	if(p2>=1000000)fwrite(wb,1,1000000,stdout),p2=0;
	wb[p2++]=x;
}
void wrt(long long x) {
	if(x<0)pc('-'),x=-x;
	int c[24]= {0};
	if(!x)return pc('0'),void();
	while(x)c[++c[0]]=x%10,x/=10;
	while(c[0])pc(c[c[0]--]+'0');
}
int n,m;
vector<int> vec[100005];
namespace ETT{
	struct node{
		int ch[2],fa,pre,suf,sz;
		int dtag,midep,dep;
		int val,sum,mx,mi;
	}v[200005];
	void push_tag(int rt,int val){
		if(!rt)return;
		v[rt].midep+=val,v[rt].dep+=val,v[rt].dtag+=val;
	}
	void push_down(int rt){
		if(v[rt].dtag){
			push_tag(v[rt].ch[0],v[rt].dtag);
			push_tag(v[rt].ch[1],v[rt].dtag);
			v[rt].dtag=0;
		}
	}
	void push_up(int rt){
		v[rt].pre=v[rt].ch[0]?v[v[rt].ch[0]].pre:rt;
		v[rt].suf=v[rt].ch[1]?v[v[rt].ch[1]].suf:rt;
		v[rt].midep=min(v[rt].dep,min(v[v[rt].ch[0]].midep,v[v[rt].ch[1]].midep));
		v[rt].sum=v[rt].val+v[v[rt].ch[0]].sum+v[v[rt].ch[1]].sum;
		v[rt].mx=max(v[v[rt].ch[1]].mx,max(v[v[rt].ch[1]].sum+v[rt].val,v[v[rt].ch[1]].sum+v[rt].val+v[v[rt].ch[0]].mx));
		v[rt].mi=max(v[v[rt].ch[0]].mi,max(v[v[rt].ch[0]].sum+v[rt].val,v[v[rt].ch[0]].sum+v[rt].val+v[v[rt].ch[1]].mi));
		v[rt].sz=(!(rt&1))+v[v[rt].ch[0]].sz+v[v[rt].ch[1]].sz;
	}
	bool isroot(int x){
		return v[v[x].fa].ch[0]!=x&&v[v[x].fa].ch[1]!=x;
	}
	void rot(int x){
		int p=v[x].fa,g=v[p].fa;
		bool d=v[p].ch[1]==x;
		if(!isroot(p))v[g].ch[v[g].ch[1]==p]=x;
		v[p].ch[d]=v[x].ch[d^1];
		v[v[x].ch[d^1]].fa=p;
		v[x].ch[d^1]=p;
		v[x].fa=g,v[p].fa=x;
		push_up(p),push_up(x);
	}
	void pre_push_down(int rt){
		if(!isroot(rt))pre_push_down(v[rt].fa);
		push_down(rt);
	}
	void splay(int x,int f=0){
		pre_push_down(x);
		while(!isroot(x)&&v[x].fa!=f){
			int p=v[x].fa,g=v[p].fa;
			if(!isroot(p)&&g!=f)rot(v[g].ch[0]==p^v[p].ch[0]==x?x:p);
			rot(x);
		}
	}
	int search_pre(int x,int k){
		push_down(x);
		if(v[v[x].ch[1]].mx>=k)return search_pre(v[x].ch[1],k);k-=v[v[x].ch[1]].sum;
		if(k==v[x].val)return x;k-=v[x].val;
		return search_pre(v[x].ch[0],k);
	}
	int search_suf(int x,int k){
		push_down(x);
		if(v[v[x].ch[0]].mi>=k)return search_suf(v[x].ch[0],k);k-=v[v[x].ch[0]].sum;
		if(k==v[x].val)return x;k-=v[x].val;
		return search_suf(v[x].ch[1],k);
	}
	int cut(int x){
		splay(x<<1),splay(x<<1|1,x<<1);
		int l=v[v[x<<1].ch[0]].suf,r=v[v[x<<1|1].ch[1]].pre;
		splay(l),splay(r,l);
		v[v[r].ch[0]].fa=0,v[r].ch[0]=0;
		push_up(r),push_up(l);
		return x<<1;
	}
	void link(int x,int y){
		splay(x<<1),splay(v[v[x<<1].ch[1]].pre,x<<1),splay(y);
		v[v[x<<1].ch[1]].ch[0]=y,v[y].fa=v[x<<1].ch[1],push_up(v[x<<1].ch[1]),push_up(x<<1);
	}
	void modify(int x,int d){
		splay(x<<1),splay(x<<1|1,x<<1);
		int l=v[v[x<<1].ch[0]].suf,r=v[v[x<<1|1].ch[1]].pre;
		splay(l),splay(r,l),push_tag(v[r].ch[0],d),push_up(r),push_up(l);
	}
}
int fa[100005],dep[100005],sz[100005];
void dfs1(int x,int prt){
	fa[x]=prt,dep[x]=dep[prt]+1,sz[x]=1;
	for(int y:vec[x])
		dfs1(y,x),sz[x]+=sz[y];
}
void dfs2(int x,int prt){
	for(int y:vec[x])
		dfs2(y,x);
	if(prt){
		ETT::splay(prt<<1),ETT::splay(ETT::v[ETT::v[prt<<1].ch[1]].pre,prt<<1);
		ETT::splay(x<<1),ETT::v[ETT::v[prt<<1].ch[1]].ch[0]=x<<1;
		ETT::v[x<<1].fa=ETT::v[prt<<1].ch[1],ETT::push_up(ETT::v[prt<<1].ch[1]),ETT::push_up(prt<<1);
	}
}
int main() {
	ETT::v[0].midep=0x3f3f3f3f,ETT::v[0].mi=ETT::v[0].mx=-0x3f3f3f3f,ETT::v[0].dep=0x3f3f3f3f;
	n=getint(),m=getint();
	for(int i=1;i<=n;i++){
		int k=getint();vec[i].resize(k);
		for(int j=0;j<k;j++)vec[i][j]=getint();
	}
	dfs1(1,0);
	for(int rt=1;rt<=n;rt++){
		ETT::v[rt<<1].dep=ETT::v[rt<<1|1].dep=dep[rt],ETT::v[rt<<1].val=1,ETT::v[rt<<1|1].val=-1;
		ETT::v[rt<<1].ch[1]=rt<<1|1,ETT::v[rt<<1|1].fa=rt<<1;
		ETT::push_up(rt<<1|1),ETT::push_up(rt<<1);
	}
	dfs2(1,0);
	for(int i=1;i<=m;i++){
		int opt=getint();
		if(opt==1){
			int x=getint(),y=getint();
			if(x==y){wrt(0),pc('\n');continue;}
			int szx=(ETT::splay(x<<1),ETT::v[ETT::v[x<<1].ch[0]].sz),depx=ETT::v[x<<1].dep;
			int szy=(ETT::splay(y<<1),ETT::v[ETT::v[y<<1].ch[0]].sz),depy=ETT::v[y<<1].dep;
			if(szx>szy)swap(szx,szy),swap(x,y),swap(depx,depy);
			ETT::splay(x<<1),ETT::splay(y<<1,x<<1);
			int lcadep=min(ETT::v[ETT::v[y<<1].ch[0]].midep,ETT::v[y<<1].dep)-1;
			wrt(depx+depy-lcadep*2),pc('\n');
		}
		if(opt==2){
			int x=getint(),h=getint(),de=h;
			ETT::splay(x<<1),h=ETT::search_pre(ETT::v[x<<1].ch[0],h)>>1;
			ETT::splay(h<<1),ETT::modify(x,-de+1),ETT::link(h,ETT::cut(x));
		}
		if(opt==3){
			int x=1,k=getint();
			if(k==0)k=1;
			else ETT::splay(x<<1),k=ETT::search_suf(ETT::v[x<<1].ch[1],k)>>1;
			ETT::splay(k<<1),wrt(k),pc('\n');
		}
	}
	fwrite(wb,1,p2,stdout);
	return Loli Kon;
}
```

---

