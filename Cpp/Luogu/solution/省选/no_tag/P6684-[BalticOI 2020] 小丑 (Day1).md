# [BalticOI 2020] 小丑 (Day1)

## 题目背景

由于官方测试数据量过大，为了避免过多资源占用，这里选取了部分官方数据作为本题测试数据。

## 题目描述

小丑回到了哥谭市，准备执行一个邪恶的计划。哥谭市有 $N$ 个路口（编号从 $1$ 到 $N$），$M$ 条道路（编号从 $1$ 到 $M$）。一条道路连接两个不同的路口，且两个路口间最多只有一条道路相连。

为了实现他的邪恶计划，小丑需要在城市中走完一个奇环。形式化地说，一个奇环为一个形如 $S,s_1,s_2,\ldots,s_k,S$ 的序列（要求 $k$ 为偶数），其中 $S$ 和 $s_1$，$s_k$ 和 $S$，以及 $\forall 1 \lt i \leq k$，$s_{i-1}$ 和 $s_i$ 之间都有道路直接相连。

然而，警察控制了城市中的部分街道。在第 $i$ 天，警察控制了编号在 $[l_i,r_i]$ 范围内的所有街道，小丑不能经过这些街道。然而小丑通过买通警察局的内鬼，了解到了警察在未来 $Q$ 天控制街道的计划，现在小丑想要知道，在哪些日子里，他的邪恶计划可以实现。

## 说明/提示

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/qr5q8ha4.png)

### 子任务

所有数据均满足：$1 \leq N,M,Q \leq 2 \times 10^5$。

- 子任务 1（6 分）：$1 \leq N,M,Q \leq 200$；
- 子任务 2（8 分）：$1 \leq N,M,Q \leq 2 \times 10^3$；
- 子任务 3（25 分）：$\forall i \in [1,Q]$，$l_i =1$；
- 子任务 4（10 分）：$\forall i \in [1,Q]$，$l_i \leq 200$；
- 子任务 5（22 分）：$Q \leq 2 \times 10^3$；
- 子任务 6（29 分）：无特殊限制。

## 样例 #1

### 输入

```
6 8 2
1 3
1 5
1 6
2 5
2 6
3 4
3 5
5 6
4 8
4 7
```

### 输出

```
NO
YES
```

# 题解

## 作者：Acoipp (赞：9)

## 题意：

> 给定 $n$ 条边，$m$ 个点的无向图，每次询问如果删掉编号为 $l \sim r$ 的边，剩下的图是否含有奇环。

## 分析

若设 $f_r$ 表示当右端点为 $r$，左端点最小为 $f_r$ 能够保证删掉 $f_r \sim r$ 的边后剩下的图含有奇环。

则若询问是 $l,r$，当且仅当 $l \ge f_r$ 含有奇环，否则没有奇环。

注意到若 $i<j$，则 $f_i \le f_j$。

证明：

> 如果 $i<j$，那么从 $i$ 扫到 $j$ 的过程中，右边的 边肯定是越来越少，那么肯定左边的边至少要达到 $f_i$ 才能满足以上条件。

然后这就是一个决策单调性转移。

如果用双指针的话，需要用 LCT 来动态维护二分图，但是我这里用的是分治处理决策单调性的转移，所以可以用带撤销的并查集。

并查集判定二分图的技巧可以左转 [[NOIP2010 提高组] 关押罪犯](https://www.luogu.com.cn/problem/P1525) 学习。

然后注意一个细节（不限于本题）：

当下述变量中 $t$ 可以为 $0$，那么请不要这么写：

```cpp
while(t--) solve();
```

应该改成：

```cpp
while(t>0) t--,solve();

//或for(int i=1;i<=t;i++) solve();
```

如果按第一种写法，$t$ 就会减成 $-1$，影响后面的循环处理。

**还有一点，如果没有一个 $l \le f_r$ 使得满足上述条件，那么 $f_r$ 的值应该比 $r$ 设置得要大，否则可能会 Wrong Answer 几个测试点。**

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 500005
using namespace std;
struct node{ll x,y,p,c;};
ll n,m,q,x[N],y[N],dp[N],i,fath[N],dep[N],now,cnt,s,t;
ll gf(ll x){return x==fath[x]?x:gf(fath[x]);}
stack<node> sta;
inline void merge_extra(ll f1,ll f2,ll c){
	node temp = (node){0,0,0,0};
	cnt += c;
	if(f1==f2){
		temp.p = -1;
		temp.c = c;
		sta.push(temp);
		return ;
	}
	if(dep[f1]<dep[f2]) temp.x=f1,temp.y=f2,temp.p=0,fath[f1]=f2,temp.c=c,sta.push(temp);
	else if(dep[f1]>dep[f2]) temp.x=f2,temp.y=f1,temp.p=0,fath[f2]=f1,temp.c=c,sta.push(temp);
	else temp.x=f1,temp.y=f2,temp.p=1,fath[f1]=f2,dep[f2]++,temp.c=c,sta.push(temp);
}
inline void merge(ll x,ll y){
	ll c = 0;
	if(gf(x)==gf(y)||gf(x+n)==gf(y+n)) c=1;
	ll f1 = gf(x),f2 = gf(y+n);
	merge_extra(f1,f2,c);
	f1 = gf(x+n),f2 = gf(y);
	merge_extra(f1,f2,c);
}
inline void pop(){
	node temp = sta.top();
	sta.pop();
	cnt -= temp.c;
	if(temp.p==-1) return ;
	fath[temp.x] = temp.x,dep[temp.y] -= temp.p;
}
void solve(ll l,ll r,ll s,ll t,ll now){
	if(l>r||s>t) return ;
	ll mid = (l+r)/2,ans = mid+1,t1 = 0,t2 = 0,t3 = now,ttt = min(t,mid);
	while(now>mid+1){
		now--;
		merge(x[now],y[now]);
		t1++;
	}
	for(ll i=s;i<=ttt;i++){
		if(cnt){
			ans = i;
			break;
		}
		merge(x[i],y[i]);
		t2++;
	}
	dp[mid] = ans;
	while(t2>0) t2--,pop(),pop();
	solve(l,mid-1,s,ans,now);
	while(t1>0) t1--,pop(),pop();
	for(ll i=s;i<ans;i++){
		merge(x[i],y[i]);
		t2++;
	}
	solve(mid+1,r,ans,t,t3);
	while(t2>0) t2--,pop(),pop();
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>q;
	for(i=1;i<=2*n;i++) fath[i]=i,dep[i]=1;
	for(i=1;i<=m;i++) cin>>x[i]>>y[i];
	solve(1,m,1,m,m+1);
	while(q--){
		cin>>s>>t;
		if(s>=dp[t]) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

## 复杂度

时间复杂度为严格 $O(n \log^2 n)$，而且常数很小（可撤销并查集还有一个 $\log$）；空间复杂度为 $O(n)$；代码复杂度也很低，2kb 左右就可以搞定。

---

## 作者：Arghariza (赞：8)

整体二分。

有个小技巧，就是可以把存边的数组往后复制一遍，然后删去区间 $[l,r]$ 就相当于保留区间 $[r+1,l+m-1]$ 的边。于是只需要解决这么个问题：

> 给定一张 $n$ 个点 $m$ 条边的无向图，$q$ 次询问，每次只保留区间 $[l,r]$ 的边，问是否是二分图。

乍一看有点像 [Cnoi2019 须臾幻境](https://www.luogu.com.cn/problem/P5385)？但是其实有不用 LCT 的做法。

考虑令 $f_l$ 表示最小的 $p$ 使得 $[l,p]$ 区间**不是**二分图。显然 $f$ 具有单调性，即 $\forall i\le i',f_i\le f_{i'}$。只需要求出所有的 $f_i$，就可以直接根据 $f_l$ 是否 $\le r$ 判断是否是二分图了。

由于 $f$ 的单调性，不难想到整体二分。令 $S(l,r,v_l,v_r)$ 表示处理 $f_{l},f_{l+1},\cdots, f_{r}$，并且 $v_l\le f_l\le f_r\le v_r$。令 $\text{mid}=\frac{l+r}{2}$，于是只需要求出 $f_{\text{mid}}$ 即可：用可撤销并查集从 $\text{mid}$ 开始加边，第一个使得图不是二分图的位置就是 $f_\text{mid}$。

为了保证复杂度，需要在分治之前将 $(r,v_l)$ 的边先加进并查集中。然后就没什么细节了。

复杂度 $O(m\log m\log n+q)$，整体二分复杂度写假的是小丑。

```cpp
// Problem: Joker
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1386C
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

namespace vbzIO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
    #if ONLINE_JUDGE
    #define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
    #else
    #define gh() getchar()
    #endif
    #define mt make_tuple
    #define mp make_pair
    #define fi first
    #define se second
    #define pc putchar
    #define pb emplace_back
    #define ins insert
    #define era erase
    typedef tuple<int, int, int> tu3;
    typedef pair<int, int> pi;
    inline int rd() {
        char ch = gh();
        int x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    inline void wr(int x) {
        if (x < 0) x = ~(x - 1), putchar('-');
        if (x > 9) wr(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace vbzIO;

const int N = 2e5 + 200;

int n, m, q, tp, st[N << 1], fa[N << 1], sz[N << 1], f[N];
pi p[N << 1];

int gf(int x) { return x == fa[x] ? x : gf(fa[x]); }
void mrg(int x, int y) {
	x = gf(x), y = gf(y);
	if (x == y) return;
	if (sz[x] < sz[y]) swap(x, y);
	fa[y] = x, sz[x] += sz[y], st[++tp] = y;
}

void del(int s) {
	while (tp > s) {
		int y = st[tp--];
		sz[fa[y]] -= sz[y], fa[y] = y;
	}
}

bool link(int x, int y) { 
	mrg(x, y + n), mrg(y, x + n);
	if (gf(x) == gf(y)) return 0;
	return 1;
}

void conq(int l, int r, int s, int t) {
	if (l > r || s > t) return;
	if (s == t) {
		for (int i = l; i <= r; i++) f[i] = s;
		return;
	}
	int mid = (l + r) >> 1, sz = tp;
	for (int i = mid; i <= r; i++) 
		if (!link(p[i].fi, p[i].se)) { f[mid] = i; break; }
	if (!f[mid]) 
		for (int i = max(s, r + 1); i <= t; i++) 
			if (!link(p[i].fi, p[i].se)) { f[mid] = i; break; }
	del(sz);
	for (int i = mid; i < min(s, r + 1); i++) link(p[i].fi, p[i].se); 
	conq(l, mid - 1, s, f[mid]), del(sz);
	for (int i = max(s, r + 1); i < f[mid]; i++) link(p[i].fi, p[i].se);
	conq(mid + 1, r, f[mid], t), del(sz);
}

int main() {
	n = rd(), m = rd(), q = rd();
	for (int i = 1; i <= n << 1; i++) fa[i] = i, sz[i] = 1;
	for (int i = 1, u, v; i <= m; i++) 
		u = rd(), v = rd(), p[i] = p[i + m] = mp(u, v);
	conq(1, m + 1, 1, m << 1 | 1);
	while (q--) {
		int l = rd(), r = rd();
		if (f[r + 1] <= m + l - 1) puts("YES");
		else puts("NO");
	}
    return 0;
}
```

---

## 作者：Judgelight (赞：5)

# 题意

[传送门](https://www.luogu.com.cn/problem/P6684)

# 题解

考虑关于一个二分图判定的显然单调性：如果此时的图有奇环，那么再加边仍然有奇环。

那么考虑设状态 $f_r$ 表示使得边集 $[1,f_r]\cup[r,m]$ 构成的图有奇环的最小的 $f_r$。显然有 $r_1<r_2\rightarrow f_{r_1}\le f_{r_2}$。

维护边集可以用 lct 或者并查集。

所以考虑按照这样的方式整体二分优化 dp。

其实这道题可以不用 lct 直接写可撤销并查集的。

首先保存一个进入函数时的时间戳 $t_1$（栈大小），再保存一下边集 $[mid,m]$ 的时间戳 $t_2$，这样当计算完当前的决策点后先回退到 $t_2$，然后去递归左边，递归后回退到 $t_1$，在最后再一次消除递归右边的影响，回退到 $t_1$。

这么做的正确性在于所有加入和删除都是连续且具有时间性的。

# 代码

```cpp
#include<bits/stdc++.h>
#define N 400009
using namespace std;
int n,m,q;
struct Edge{int x,y;}e[N];
struct DSU{
	int fa[N],Size[N],stk[N*2],top;
	void init(int n){top=0;for(int i=1;i<=n;i++)fa[i]=i,Size[i]=1;}
	int find(int x){return fa[x]==x?x:find(fa[x]);}
	void merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y){stk[++top]=-1;return ;}
		if(Size[x]>Size[y])swap(x,y);
		fa[x]=y,Size[y]+=Size[x],stk[++top]=x;
	}
	void review(){
		if(stk[top]==-1){top--;return ;}
		int x=stk[top--],y=find(x);
		fa[x]=x,Size[y]-=Size[x];
	}
}d;
int f[N];
void solve(int l,int r,int L,int R){
	if(l>r||L>R)return ;
	int mid=(l+r)>>1,tr=d.top,Mid;
	for(int i=r;i>=mid;i--)d.merge(e[i].x,e[i].y+n),d.merge(e[i].x+n,e[i].y);
	int tm=d.top;
	for(int i=L;i<=min(R,mid);i++){
		d.merge(e[i].x,e[i].y+n),d.merge(e[i].x+n,e[i].y);
		if(d.find(e[i].x)==d.find(e[i].y)){f[mid]=Mid=i;break;}
	}
	while(d.top>tm)d.review();
	solve(l,mid-1,L,Mid);
	while(d.top>tr)d.review();
	for(int i=L;i<Mid;i++)d.merge(e[i].x,e[i].y+n),d.merge(e[i].x+n,e[i].y);
	solve(mid+1,r,Mid,R);
	while(d.top>tr)d.review();
}
signed main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++)scanf("%d%d",&e[i].x,&e[i].y);
	d.init(n<<1);
	int s=-1;
	for(int i=m;i>=1;i--){
		d.merge(e[i].x,e[i].y+n),d.merge(e[i].x+n,e[i].y);
		if(d.find(e[i].x)==d.find(e[i].y)){
			s=i+1;
			for(int j=s;j<=m+1;j++)f[j]=m+1;
			break;
		}
	}
	if(s==-1){for(int i=1;i<=q;i++)printf("NO\n");return 0;}
	d.init(n<<1);
	solve(s,m+1,1,m);
	for(int i=1,l,r;i<=q;i++){
		scanf("%d%d",&l,&r);l--,r++;
		f[r]<=l?printf("YES\n"):printf("NO\n");
	}
	return 0;
}
```

---

## 作者：_AyachiNene (赞：5)

LCT 做法。
# 思路：
首先可以把序列复制一遍转化为选一个区间的边能否有奇环。发现答案显然有单调性，可以用双指针维护每一个 $l$ 的最小的一个 $r$，且用这个区间的边有一个奇环。接下来考虑怎么动态加删边并判断奇环。直接判断奇环可以用扩展域并查集或带权并查集，但是发现删边顺序不是按栈删的，所以不能用并查集。可以用 LCT 来实现动态加删边，发现后加入的边一定更优，直接用 LCT 维护最大生成树，再维护联通性就行了。这里有一些小细节，发现用扩展域并查集点数为 $2n$ 且边也要开虚点，常数太大，所以用带权并查集的方法维护，记一个子树大小直接算就能得出路径长度。
# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){char ch=getch();while(ch<'a'||ch>'z')ch=getch();while(ch>='a'&&ch<='z'){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
int n,m,q;
int u[1000005],v[1000005];
int p[1000005];
int vis[1000005];
namespace Nene
{
	int stk[1000005],top;
	struct spt
	{
		int ch[2],tag,f,siz;
		int val,mn;
		spt(){val=mn=1e9;}
	}t[1000005];
	inline int isroot(int p){return t[t[p].f].ch[0]!=p&&t[t[p].f].ch[1]!=p;}
	inline void update(int p)
	{
		t[p].mn=t[p].val;
		if(t[p].ch[0]) t[p].mn=min(t[p].mn,t[t[p].ch[0]].mn);
		if(t[p].ch[1]) t[p].mn=min(t[p].mn,t[t[p].ch[1]].mn);
		t[p].siz=t[t[p].ch[0]].siz+t[t[p].ch[1]].siz+1;
	}	
	inline void down(int p)
	{
		if(t[p].tag)
		{
			if(t[p].ch[0]) t[t[p].ch[0]].tag^=1;
			if(t[p].ch[1]) t[t[p].ch[1]].tag^=1;
			swap(t[p].ch[0],t[p].ch[1]);
			t[p].tag=0;
		}
	}
	inline void rotate(int p)
	{
		int f=t[p].f,ff=t[f].f;
		int k=t[f].ch[1]==p;
		if(!isroot(f)) t[ff].ch[t[ff].ch[1]==f]=p;t[p].f=ff;
		t[f].ch[k]=t[p].ch[k^1];t[t[p].ch[k^1]].f=f;
		t[p].ch[k^1]=f;t[f].f=p;
		update(f);update(p);
	}
	inline void splay(int p)
	{
		top=0;
		stk[++top]=p;
		for(int i=p;!isroot(i);i=t[i].f) stk[++top]=t[i].f;
		while(top) down(stk[top--]);
		while(!isroot(p))
		{
			int f=t[p].f,ff=t[f].f;
			if(!isroot(f)) (t[f].ch[1]==p)^(t[ff].ch[1]==f)?rotate(p):rotate(f);
			rotate(p);
		}
	}
	inline void access(int p){for(int last=0;p;last=p,p=t[p].f) splay(p),t[p].ch[1]=last,update(p);}
	inline int findroot(int p){access(p);splay(p);while(t[p].ch[0]) p=t[p].ch[0];return p;}
	inline void makeroot(int p){access(p);splay(p);t[p].tag^=1;}
	inline void split(int x,int y){makeroot(x);access(y);splay(y);}
	inline void link(int x,int y)
	{
		makeroot(x);
		t[x].f=y;
	}
	inline void cut(int x,int y)
	{
		split(x,y);
		if(t[y].ch[0]==x) t[y].ch[0]=t[x].f=0;	
	}
	inline int query(int x,int y)
	{
		split(x,y);
		return t[y].mn;
	}
	inline int dis(int x,int y)
	{
		split(x,y);
		return t[y].siz/2;
	}
	inline int check(int x,int y){return findroot(x)==findroot(y);}
	inline void merge(int e)
	{
		if(!check(u[e],v[e])) link(u[e],e+n),link(v[e],e+n);
		else
		{
			int p=query(u[e],v[e]);
			if(p<e)
			{
				cut(u[p],p+n);cut(p+n,v[p]);
				link(u[e],e+n);link(e+n,v[e]);
				vis[p]=1;
			}
		}
	}
}
using namespace Nene;
int main()
{
//	freopen("run2.in","r",stdin);
//	freopen("run.out","w",stdout);
	read(n,m,q);
	for(int i=1;i<=m;i++) t[i+n].mn=t[i+n].val=i;
	for(int i=1;i<=m;i++) read(u[i],v[i]),u[m+i]=u[i],v[m+i]=v[i];
	m<<=1;
	int cur=1;
	memset(p,0x3f,sizeof p);
	for(int i=1;i<=m/2+1;i++)
	{
		while(cur<=m)
		{
			if(check(u[cur],v[cur])&&(dis(u[cur],v[cur])&1)==0)
			{
				p[i]=cur;
				break;
			}
			merge(cur);
			++cur;
		}
		if(!vis[cur+n]) cut(u[i],i+n),cut(i+n,v[i]);
	}
	while(q--)
	{
		int tl,tr;
		read(tl,tr);
		int l=tr+1,r=m/2+tl-1;
		if(p[l]<=r) put("YES\n");
		else put("NO\n");
	}
	flush();
}
```

---

## 作者：ZhongYuLin (赞：4)

进行一步转化，将边序列倍长。考虑对于每个 $l$，求出最近的 $r$，使得 $\left[l,r\right]$ 内的边存在时，图中存在奇环。容易发现有单调性，于是可以用 LCT 配合双指针，但这太难了。考虑并查集。发现我们并不能删去左端点，于是可以使用整体二分，但这太难了。考虑到一个技巧： [【UR #23】地铁规划](https://uoj.ac/problem/693)。但这太难了。我们可以用线段树分治。

具体地，我们用线段树分治维护连边。初始我们不往线段树上放置连边。我们现在处理 $l=1$，暴力向右推动指针至最近的合法的 $r$。在指针移动途中，设现在移动到了 $r'$，根据单调性，$\left[l,r'\right]$ 间的点必然需要 $r'$ 这条边，于是将 $r'$ 加到这个区间上即可。


```cpp
#include<bits/stdc++.h>
#define ls mid<<1
#define rs mid<<1|1
using namespace std;
using pii=pair<int,int>;
const int N=2e5+3,INF=0x3f3f3f3f;
pii st[N*10],e[N*2];
int fa[N*2],d[N*2],R[N*2];
int n,m,q,top;
vector<int>t[N*4];
int find(int x){return fa[x]^x?find(fa[x]):x;}
void merge(int x,int y){
    if(x==y)return;
    if(d[x]>d[y])swap(x,y);
    int k=d[x]==d[y];
    st[++top]={x,k};
    fa[x]=y;d[y]+=k;
}
int add(int i){
    auto [u,v]=e[i];
    int k1=find(u),k2=find(u+n),k3=find(v),k4=find(v+n);
    merge(k1,k4);merge(k2,k3);
    return fa[k1]==fa[k2]||fa[k3]==fa[k4];
}
void upd(int x,int y,int k,int l=1,int r=2*m,int p=1){
    if(x<=l&&r<=y)return t[p].push_back(k);
    int mid=l+r>>1;
    if(x<=mid)upd(x,y,k,l,mid,ls);
    if(y>mid)upd(x,y,k,mid+1,r,rs);
}
void undo(int old){
    while(top>old){
        auto [x,del]=st[top--];
        d[fa[x]]-=del;fa[x]=x;
    }
}
void solve(int k,int l=1,int r=2*m,int p=1){
    int old=top;
    for(auto x:t[p]){
        if(k)break;
        k=add(x);
    }
    if(l==r){
        R[l]=R[l-1];
        while(!k&&R[l]<2*m){
            k=add(++R[l]);
            if(l<2*m)upd(l+1,min(R[l],2*m),R[l]);
        }
        if(!k)R[l]=INF;
    }else{
        int mid=l+r>>1;
        solve(k,l,mid,ls);
        solve(k,mid+1,r,rs);
    }
    undo(old);
}
int main(){
    int u,v,w,x,y,z;
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=m;++i)cin>>x>>y,e[i]=e[i+m]={x,y};
    iota(fa+1,fa+1+2*n,1);solve(0);
    for(;q--;)cin>>x>>y,puts(R[y+1]<=x+m-1?"YES":"NO");
    return 0;
}
```

当然也可以不转化题意，跑的非常快：


```cpp
#include<bits/stdc++.h>
#define ls mid<<1
#define rs mid<<1|1
using namespace std;
using pii=pair<int,int>;
const int N=2e5+3;
pii st[N*10],e[N];
int d[N*2],R[N],fa[N*2];
vector<int>t[N*4];
int n,m,q,top;
int find(int x){return fa[x]^x?find(fa[x]):x;}
void merge(int x,int y){
    if(x==y)return;
    if(d[x]>d[y])swap(x,y);
    int k=d[x]==d[y];
    st[++top]={x,k};
    fa[x]=y;d[y]+=k;
}
int add(int i){
    auto [u,v]=e[i];
    int k1=find(u),k2=find(u+n),k3=find(v),k4=find(v+n);
    merge(k1,k4);merge(k2,k3);
    return fa[k1]==fa[k2]||fa[k3]==fa[k4];
}
void upd(int x,int y,int k,int l=1,int r=m,int p=1){
    if(x<=l&&r<=y)return t[p].push_back(k);
    int mid=l+r>>1;
    if(x<=mid)upd(x,y,k,l,mid,ls);
    if(y>mid)upd(x,y,k,mid+1,r,rs);
}
void solve(int k,int l,int r,int p){
    int old=top;
    for(auto x:t[p]){
        if(k)break;
        k=add(x);
    }
    if(l==r){
        R[l]=R[l+1];
        while(!k&&R[l]>=l){
            if(l>1)upd(1,l-1,R[l]);
            k=add(R[l]--);
        }
    }else{
        int mid=l+r>>1;
        solve(k,mid+1,r,rs);
        solve(k,l,mid,ls);
    }
    while(top>old){
        auto [x,del]=st[top--];
        d[fa[x]]-=del;fa[x]=x;
    }
}
int main(){
    int u,v,w,x,y,z;
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=m;++i)cin>>x>>y,e[i]={x,y};
    for(int i=1;i<m;++i)upd(i+1,m,i);
    iota(fa,fa+1+2*n,0);R[m+1]=m;solve(0,1,m,1);
    for(int i=1;i<=q;++i)cin>>x>>y,puts(y<=R[x]?"YES":"NO");
    return 0;
}
```

---

## 作者：Niko！ (赞：4)

没有奇环<->二分图

也就是说，询问删去一个区间的边之后，原图是否是一个二分图。

保留的边不是一段区间，这个不太方便，考虑将边的序列排成一个环，这样就是求：环上的某一个区间的边是否形成一个二分图。

对每一个位置 $i$，预处理出：从它往后最多多少条连续的边，满足这些边是一个二分图，且没有边被加入两次（可能从环的另一端绕回来)。有了这个，我们就可以快速回答询问了。

考虑使用双指针来预处理这个东西，也就是支持加边删边判断是否是二分图，我们可以采用 LCT 维护关于加入时间的最大生成树，就可以快速加边删边了。

复杂度 $O(n \log n + q)$，有点卡常数，需要进行一定的常数优化。

```

#include <bits/stdc++.h>
#define maxn 400005

int t[maxn]={0},x[maxn],y[maxn],ch[maxn][2],fa[maxn]={0},rev[maxn]={0},vis[maxn],
max[maxn]={0},a[maxn],b[maxn],n,m,q,opt[maxn],lim[maxn]={0},size[maxn],R[maxn];
int stk[maxn],top;

int nxt(int x) { x++; if (x>m) x = 1; return x; }

int gmax(int a,int b) {return t[a]>t[b]?a:b;}

void update(int x) {max[x]=gmax(gmax(max[ch[x][0]],max[ch[x][1]]),x);size[x]=size[ch[x][0]]^size[ch[x][1]]^(x>n);}
void reverse(int x) {std::swap(ch[x][0],ch[x][1]); rev[x]^=1;}
void pushdown(int x) {if (rev[x]) {reverse(ch[x][0]);reverse(ch[x][1]);rev[x]=0;}}
int not_root(int x) {return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}

void rotate(int x) {
	int f=fa[x],g=fa[f],l=ch[f][1]==x;
	if (not_root(f)) ch[g][ch[g][1]==f]=x; 
	ch[f][l]=ch[x][l^1]; fa[ch[x][l^1]]=f;
	fa[f]=x;fa[x]=g; ch[x][l^1]=f;
	update(f);update(x); 
}

void spaly(int x) {
    int u=x; stk[++top]=u;
    while (not_root(u)) {stk[++top]=(u=fa[u]);}
    while (top) {pushdown(stk[top--]);}
    while(not_root(x)){
    	rotate(x);
  	 	if (not_root(fa[x])&&not_root(x)) rotate(rand()%2?fa[x]:x);
    }
}

void access(int x) {
	for (int y=0;x;x=fa[y=x]) {
		spaly(x); ch[x][1]=y; update(x);
	}
}

void make_root(int x) {
	access(x); spaly(x); reverse(x);
}

int find_root(int x) {
	access(x); spaly(x); while (ch[x][0]) pushdown(x),x=ch[x][0]; return x;
}

void split(int x,int y) {
//	printf("split:%d %d\n",x,y);
	make_root(y);access(x);spaly(y);}

void link(int x,int y) {
	make_root(x); fa[x]=y;// printf("lk:%d-%d\n",x,y);
} 

void cut(int x,int y) {
	make_root(x); access(y); spaly(x); ch[x][1]=fa[y]=0;
}

int dis(int a,int b) {
	make_root(b); if (find_root(a) != b) {return 1;}
	//printf("size[b] = %d\n",size[b]);
	return size[a];
}

void Cut(int b) {
//	printf("cut %d\n",b);
	vis[b]=0;
	cut(x[b],b+n),cut(b+n,y[b]);
}

void Link(int a,int w) {
	vis[a]=1;
	//printf("Link %d %d\n",a,w);
	t[a+n] = 2*m+1-w;
//	printf("link:%d<->%d\n",x[a],y[a]);
	make_root(x[a]);
	if (find_root(y[a])!=x[a]) {
		link(x[a],a+n),link(a+n,y[a]); }
	else {
		//printf("interact\n");
		//split(y[a],x[a]); //spaly(x[a]);
		if (t[max[y[a]]]>t[a+n]) {
			int b=max[y[a]]-n; 
		//	printf("%d\n",b);
		//	printf("cut:%d<->%d\n",x[b],y[b]);
			Cut(b);
			link(x[a],a+n),link(a+n,y[a]);
		}
	}
}

int read() {
	int x = 0; char c = getchar();
	while (c<'0'||c>'9')c=getchar();
	while('0'<=c&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x;
}

int main() {
	//freopen("c.in","r",stdin);
//	freopen("c2.out","w",stdout);
	scanf("%d%d%d",&n,&m,&q);
	for (int i=1;i<=m;++i) {
		x[i]=read();y[i]=read();
	//	conj[x[i]][y[i]]=conj[y[i]][x[i]]=i;
	} int p = 0,w=0,last=0;
	for (int i = 1; i <= m; ++ i) {
		while (1) {
			if (w>=m&&nxt(p) == i ) break;
			if (dis(x[nxt(p)],y[nxt(p)])%2==0){ last = max[y[nxt(p)]]-n; break;}
		//	printf("p->%d\n",nxt(p));
			p = nxt(p); w ++;
			Link(p,w);
		} R[i] = p;
	//	printf("R[%d] = %d\n",i,p);
		if (vis[i]) { Cut(i); if (last == i) last = 0; }
	} //for (int i = 1; i <= m; ++ i) printf("%d ",R[i]); 
	while (q--) {
		int l,r;
		l=read();r=read();
		int p = R[nxt(r)];
		if ((p < nxt(r) && p >= l-1) || (p == m && l == 1) || (r == m && p >= l-1)) puts("NO");
		else puts("YES");
	}
	return 0;
}

			
	
	
	
```


---

## 作者：L_zaa_L (赞：3)

对于禁用每段区间 $[l,r]$ 我们可以看成只能使用 $[1,l-1] \cup [r+1,m]$ 这里面的边，然后我们可以将边复制两遍，这样我们就可以将它看作只是用区间 $[r+1,l-1+m]$ 中的边。

我们考虑暴力该怎么做，就是可以对于每个左端点 $i$ 我们二分一下最后一个位置 $j$，使得 $[i,j]$ 之间的边组成二分图。判断二分图的方法就是可以用并查集维护的，就是将一个点拆成两个点 $x,x+n$，每次将合并 $u,v$ 的时候就只用合并 $(u,v+n),(v,u+n)$，如果 $u,v$ 在同一个集合中那么合并之后就是有奇环的。

然后我们记 $f_i$ 表示二分的最后一个位置。然后不难发现 $f_i$ 是满足单调性的。所以我们可以考虑整体二分，然后将并查集改成可撤销的并查集的。

然后你可能会发现代码跑的很慢，我们可以在整体二分 $[l,r,L,R]$ 的时候保留重复要算的区间 $[r,L]$ 就行了，这样能快很多。

时间复杂度是 $O(n\log^2 n)$，如果用 LCT 似乎可以得到一只 $\log$ 的代码。

## Code
```cpp
#include<bits/stdc++.h>
#define ls(x) ((x)*2)
#define rs(x) ((x)*2+1)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=4e5+5,base=999983,Mod=998244353;
char buf[(1<<21)+5],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void chmx(int &x,int y){(x<y)&&(x=y);}
inline void chmn(int &x,int y){(x>y)&&(x=y);}
inline void Add(int &x,int y){(x=x+y+Mod)%=Mod;}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
void print(int n){
    if(n<0){
        putchar('-');
        n*=-1;
    }
    if(n>9) print(n/10);
    putchar(n%10+'0');
}
int n,m,Q;
int s[N];
int fa[N],siz[N]; 
int u[N],v[N],ans[N];
inline int find(int x){while(fa[x]!=x)x=fa[x];return x;}
stack<tuple<int,int,int> >q;
	int tot;
	inline void merge(int x,int y){
	    y=find(y);
	    if(x==y) return;
	    if(siz[x]>siz[y]) swap(x,y);
	    fa[x]=y;siz[y]+=siz[x];
	    q.push(make_tuple(x,y,tot));
	}
	inline int Mer(int x,int y){
		++tot;
		int X=find(x),Y=find(y);
		if(X==Y) return 1;
		merge(X,y+n);merge(Y,x+n);
		return 0;
	}
	inline void POP(){
		while(q.size()&&get<2>(q.top())==tot){
			fa[get<0>(q.top())]=get<0>(q.top());
			siz[get<1>(q.top())]-=siz[get<0>(q.top())];
			q.pop();
		}
		tot--;
	}
void solve(int l,int r,int L,int R){
	if(l>r||L>R) return;
	if(L==R){For(i,l,r) ans[i]=L;return;}
	int mid=(l+r)>>1,p=R;
	For(i,mid,R){
		if(i>=r+1&&i<L) i=L;
		if(Mer(u[i],v[i])) {p=i;break;}
	} 
	ans[mid]=p;
	Rof(i,p,max(L,mid)){
		if(i>=r+1&&i<L) i=r;
		POP();
	}
	solve(l,mid-1,L,ans[mid]);For(i,mid,min(r,L-1)) POP();
	For(i,max(r+1,L),ans[mid]-1) Mer(u[i],v[i]);
    solve(mid+1,r,ans[mid],R);For(i,max(r+1,L),ans[mid]-1) POP();

}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	// ios::sync_with_stdio(false);
	// cin.tie(0); cout.tie(0);
	n=read(),m=read(),Q=read();
	For(i,1,n*2) fa[i]=i,siz[i]=1;
	For(i,1,m) u[i]=u[i+m]=read(),v[i]=v[i+m]=read();
	u[m*2+1]=v[m*2+1]=1;
	solve(1,m+1,1,m*2+1);
//	For(i,1,m) printf("%lld ",ans[i]);
//	puts("");
	while(Q--){
		int l=read(),r=read();
		if(ans[r+1]<=m+l-1){puts("YES");}
		else puts("NO");
	}
#ifdef LOCAL
    Debug("\nMy Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}

```

---

## 作者：_Ch1F4N_ (赞：3)

真的卡不动了，但是我感觉我的思路还是有一些价值的，就来写一篇题解吧。

考虑使用回滚莫队（不增）来维护，当区间删去一个点时相当于全局加入一条边，这个询问的本质是询问是否是二分图，所以考虑扩展值域并查集，这里使用路径压缩加按秩合并，记录下修改，在回滚时全部还原。

总复杂度是 $O(n \sqrt n \alpha(n))$ 目前还卡不过去，所以就只放一个在 LOJ 评测的链接。

[提交记录](https://loj.ac/s/1831460)

---

## 作者：gdf_yhm (赞：3)

[https://www.cnblogs.com/yhddd/p/18408090](https://www.cnblogs.com/yhddd/p/18408090)

[CF1386C](https://www.luogu.com.cn/problem/CF1386C)

[P6684](https://www.luogu.com.cn/problem/P6684)

cf 上时限 $1$ 秒，洛谷 $2$ 秒。

### 思路

维护是否有奇环可用拓展域并查集。暴力复杂度 $O(mq)$。发现插入容易删除困难，用不删除的莫队，可撤销并查集，复杂度 $O((n+q)\sqrt m\log n)$。大概要 $5$ 秒左右，只能过洛谷上的前 $5$ 个子任务。

等价对于每个 $r$ 求最小的 $l$ 使得 $[1,l]$ 和 $[r,m]$ 的边能组成奇环。将边复制一遍接在后面，即对于每个 $i$ 求最小的 $p$ 使得 $[i,p]$ 间的边组成奇环。这里 $p$ 有单调性。依次求每个 $i$，每次右移 $p$，加入的这条边 $p$ 会在求 $[i,p]$ 时都有贡献。插入容易删除困难，用线段树分治。初始没有边，分治到 $i$ 时会对之后一个区间加入若干条边，一共加边 $m$ 次。总复杂度 $O(m\log^2 m)$。

不开 long long 就能过 cf。

### code

```cpp
int n,m,q;
pii g[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
vector<int> tree[maxn<<2];
void updata(int nd,int l,int r,int ql,int qr,int id){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr){
		tree[nd].pb(id);
		return ;
	}
	if(ql<=mid)updata(ls,l,mid,ql,qr,id);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,id);
}
int f[maxn],siz[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return fd(f[x]);
}
int st[maxn<<5],tp,fl;
void merge(int x,int y){
	int u=fd(x),v=fd(y),uu=fd(x+n),vv=fd(y+n);
	if(u==v){
		fl=1;
		return ;
	}
	if(u!=vv){
		if(siz[u]<siz[vv])swap(u,vv);
		st[++tp]=vv;f[vv]=u,siz[u]+=siz[vv];
		if(siz[v]<siz[uu])swap(v,uu);
		st[++tp]=uu;f[uu]=v,siz[v]+=siz[uu];
	}
}
void del(){
	int u=st[tp];siz[f[u]]-=siz[u],f[u]=u;
	tp--;
}
int ans[maxn];
int p=1;
void dfs(int nd,int l,int r){
	int lst=tp,flag=fl;
	for(int i:tree[nd])merge(g[i].fi,g[i].se);
	if(l==r){
		while(p<=2*m&&!fl){
			merge(g[p].fi,g[p].se);
			updata(1,1,m+1,l+1,min(p,m+1),p);
			p++;
		}
		if(!fl)ans[l]=p;
		else ans[l]=p-1;
	}
	else dfs(ls,l,mid),dfs(rs,mid+1,r);
	while(tp>lst)del();
	fl=flag;
}
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=m;i++)g[i]={read(),read()},g[i+m]=g[i];
	for(int i=1;i<=2*n;i++)f[i]=i,siz[i]=1;
	dfs(1,1,m+1);
	while(q--){
		int l=read(),r=read();
		if(ans[r+1]<=m+l-1)puts("YES");
		else puts("NO");
	}
}
```

---

## 作者：鱼跃于渊 (赞：1)

一道神仙整体二分题。  

# 做法  

每次询问会禁用 $[l,r]$ 之间的边，也就是说只能用 $[1,l-1]\cup [r+1,n]$ 之间的边。  
感觉这个看起来不太好搞，我们可以把边复制一遍，这样我们就可以看作是只能用 $[r+1,l+m-1]$ 之间的边。  

考虑暴力怎么做。  
首先一张图不存在奇环的充要条件是该图为二分图，而判断图是否为二分图可以用扩展域并查集解决。  
也就是说我们对于每次询问，把 $[r+1,l+m-1]$ 之间的边加入并查集中，判断即可。  
这样子时间复杂度是 $O(m^2)$ 的，期望得分 $14$ 分。  

我们思考部分分，可以发现如果左端点 $l$ 是固定的，可以通过二分求出最靠右的 $r$，使得 $[l,r]$ 之间的边组成二分图。我们记这个位置为 $f_l$。  
对于部分分我们可以二分求解每个 $f_l$，期望得分 $49$ 分。  

接下来我们很容易从分别二分求解想到一起二分求解——整体二分。  
具体而言，整体二分 $(l,r,L,R)$，其中 $[l,r]$ 是值域，$[L,R]$ 是操作域。  
我们令 $mid\gets \lfloor \frac{L+R}{2}\rfloor$，求出 $f_{mid}$，然后分成 $(l,f_{mid},L,mid-1)$ 和 $(f_{mid},r,mid+1,R)$ 两个子问题。  
不过发现一个问题，如果我们每次都是暴力判断二分图，时间复杂度是 $O(n^2\log^2 n)$ 的，显然过不去。  
考虑使用可撤销并查集，然后在整体二分 $(l,r,L,R)$ 时保留重复的区间 $[R,l]$ 即可。  
时间复杂度 $O(n\log^2n)$，期望得分 $100$ 分。  

# 代码  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
const int N=4e5+5;
struct edge{
	int u,v,tm;
}e[N];
int n,m,q,ti;
int fg[N];
int fa[N],siz[N];
stack <edge> st;
int find(int x){
	return x==fa[x]?x:find(fa[x]);
}
void join(int x,int y){
	x=find(x);y=find(y);
	if(x==y) return;
	if(siz[x]>siz[y]) swap(x,y);
	fa[x]=y;siz[y]+=siz[x];
	st.push({x,y,ti});
}
bool merge(edge tp){
	ti++;
	int fx=find(tp.u),fy=find(tp.v);
	if(fx==fy) return 1;
	join(fx,tp.v+n);join(fy,tp.u+n);
	return 0;
}
void split(){
	for(edge tp;!st.empty()&&st.top().tm==ti;st.pop()){
		tp=st.top();
		fa[tp.u]=tp.u;
		siz[tp.v]-=siz[tp.u];
	}
	ti--;
}
void solve(int l,int r,int L,int R){
	if(l>r||L>R) return;
	if(l==r){
		per(i,L,R) fg[i]=l;
		return;
	}
	int p,mid=(L+R)>>1;
	for(p=mid;p<=r;p++){
		if(p==R+1) p=max(p,l);
		if(merge(e[p])) break;
	}
	fg[mid]=p;
	for(;p>=max(l,mid);p--){
		if(p==l-1) p=min(p,R);
		split();
	}
	solve(l,fg[mid],L,mid-1);
	per(i,mid,min(R,l-1)) split();
	per(i,max(R+1,l),fg[mid]-1) merge(e[i]);
	solve(fg[mid],r,mid+1,R);
	per(i,max(R+1,l),fg[mid]-1) split();
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e[i]=e[i+m]={u,v,i};
	}
	e[m*2+1]={1,1,m+1};
	iota(fa+1,fa+n*2+1,1);
	fill(siz+1,siz+n*2+1,1);
	solve(1,m*2+1,1,m+1);
	for(int i=1,l,r;i<=q;i++){
		cin>>l>>r;
		cout<<(fg[r+1]<=l+m-1?"YES\n":"NO\n");
	}
	return 0;
}
```

---

## 作者：Cx114514 (赞：0)

### 题目链接：[[BalticOI 2020 Day1] 小丑](https://www.luogu.com.cn/problem/P6684) / [Joker](https://www.luogu.com.cn/problem/CF1386C)
考虑将整个边的序列复制粘贴一遍，放在原序列的右侧。

这样，删除一个区间 $\left[l,r\right]$ 可以看作保留 $\left[r+1,n+l-1\right]$。

令 $R_i$ 表示以 $i$ 为左端点，右端点最左是多少才能使得这一个区间中的边组成一个奇环。

只要我们求出了所有的 $R$，对于每次查询，我们都可以 $O\left(1\right)$ 求解。

不难发现，$R$ 满足单调性，考虑整体二分。

令整体二分函数为 $solve\left(l,r,tl,tr\right)$，表示当前考虑左端点在 $\left[l,r\right]$ 中的情况，其 $R$ 的可能值在 $\left[tl,tr\right]$ 中。

在整体二分时，我们每次求出 $R_{mid}$，则函数可分解为 $solve\left(l,mid-1,tl,R_{mid}\right)$ 和 $solve\left(mid+1,r,R_{mid},tr\right)$。

问：如何求出 $R_{mid}$。

答：从 $mid$ 开始向后一直加边，用可撤销扩展域并查集维护，如果不会的话可以看 [[NOIP2010 提高组] 关押罪犯](https://www.luogu.com.cn/problem/P1525)。

但是，直接这么做的话复杂度冗余会很大。

当 $r\le tl$ 时，我们可以直接保留 $\left[r,tl\right]$，避免重复计算。

时间复杂度 $O\left(n\log^2 n\right)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int read()
{
	int f = 1;
	char c = getchar();
	while (!isdigit(c))
	{
	    if (c == '-') f = -1;
	    c = getchar();
    }
	int x = 0;
	while (isdigit(c))
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

int buf[25];

void write(long long x)
{
	int p = 0;
	if (x < 0)
	{
	    putchar('-');
	    x = -x;
	}
	if (x == 0) putchar('0');
	else
	{
		while (x)
		{
			buf[++p] = x % 10;
			x /= 10;
		}
		for (int i = p; i >= 1; i--)
			putchar('0' + buf[i]);
	}
}

int n, m, q, cnt, fa[400005], u[400005], v[400005], R[400005], sz[400005];

struct node
{
	int x, y, num;
};

stack < node > s;

int search(int x)
{
	if (fa[x] == x) return x;
	return search(fa[x]);
}

void _merge(int x, int y)
{
	x = search(x);
	y = search(y);
	if (x == y) return;
	if (sz[x] < sz[y]) swap(x, y);
	fa[y] = x;
	sz[x] += sz[y];
	s.push({x, y, cnt});
}

int merge(int x, int y)
{
	cnt++;
	int xx = search(x);
	int yy = search(y);
	if (xx == yy) return 1;
	_merge(xx, y + n);
	_merge(x + n, yy);
	return 0;
}

void undo()
{
	if (s.empty())
	{
		cnt--;
		return;
	}
	node t = s.top();
	while (t.num == cnt)
	{
		s.pop();
		fa[t.y] = t.y;
		sz[t.x] -= sz[t.y];	
		if (s.empty()) break;
		t = s.top();
	}
	cnt--;
}

void solve(int l, int r, int tl, int tr)
{
	if (l > r || tl > tr) return;
	if (tl == tr)
	{
		for (int i = l; i <= r; i++)
			R[i] = tl;
		return;
	}
	int mid = (l + r) / 2;
	int t;
	for (t = mid; t <= tr; t++)
	{
		if (t == r + 1) t = max(t, tl);
		if (merge(u[t], v[t])) break;
	}
	R[mid] = t;
	for (; t >= tl && t >= mid; t--)
	{
		if (t == tl) t = min(t, r);
		undo();
	}
	solve(l, mid - 1, tl, R[mid]);
	for (t = mid; t <= r && t < tl; t++)
		undo();
	for (t = max(r + 1, tl); t <= R[mid] - 1; t++)
		merge(u[t], v[t]);
	solve(mid + 1, r, R[mid], tr);
	for (t = max(r + 1, tl); t <= R[mid] - 1; t++)
		undo();
}

int main()
{
	n = read(), m = read(), q = read();
	for (int i = 1; i <= 2 * n; i++)
	{
		fa[i] = i;
		sz[i] = 1;
	}
	for (int i = 1; i <= m; i++)
	{
		u[i] = read(), v[i] = read();
		u[i + m] = u[i];
		v[i + m] = v[i];
	}
	u[2 * m + 1] = v[2 * m + 1] = 1;
	solve(1, m + 1, 1, 2 * m + 1);	
	while (q--)
	{
		int l, r;
		l = read(), r = read();
		if (R[r + 1] <= m + l - 1) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：STARSczy (赞：0)

这道题询问有没有奇环，其实就是询问是否**不是二分图**，而当一张图是二分图，它的子图一定也是二分图，所以其具有单调性。我们可以使用双指针求对于每个左端点可对应的最大右端点。

涉及删边，我们可以使用 lct 维护路径长度（求边的长度以求奇偶性）和路径上加入时间最小的边。即若边的两端不连通，则直接加边即可，否则判断这条边的两端距离的奇偶性，如果这是奇数，代表这是一个奇环，所以本次右端点扩展到此为止，否则将两端路径上加入时间最小的边删去，加入这条边（避免环的情况）。

这道题的做法楼上楼下都说得比较清楚了，所以我再说一下细节问题：
- 由于题目是求 $1$ 到 $l_i-1$ 和 $r_i+1$ 到 $n$，所以我们可以把边数组再复制一遍，求的区间就变成了 $r_i+1$ 到 $l_i-1+m$ 了。
- 发现 lct 不好维护边权问题，所以对于一条边，我们可以新开一个节点，使其连向边的两端，点权即为边权。
- 因为不是每个节点都要有边权，所以不是新开的点加入时间赋为无穷大。删边时注意删的时两条边。$0$ 号节点也要处理一下。
- 路径长度是包含新点的，处理时要记得。

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/rope>
#define rep(i,l,r) for(int i=(l),i##end=(r);i<=i##end;++i)
#define per(i,r,l) for(int i=(r),i##end=(l);i>=i##end;--i)
// #define int long long
#define double long double
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define rbtree(way) tree<way,null_type,less<way>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
const int maxn=1e6+10,maxm=1e6+10,mod=998244353,inf=1e9;
inline int ksm(int x,int k,int mod=mod){
	int ans=1;
	for(;k;k>>=1,x=x*x%mod) if(k&1) ans=ans*x%mod;
	return ans;
}

int n,m,q,u[maxn],v[maxn],rq[maxn];
int ett,tmp,sz[maxn],fa[maxn],c[maxn][2],st[maxn],tg[maxn],vl[maxn],s[maxn];
#define lc c[x][0]
#define rc c[x][1]
inline int nroot(int x){return c[fa[x]][0]==x||c[fa[x]][1]==x;}
inline void pushr(int x){swap(c[x][0],c[x][1]),tg[x]^=1;}
inline void pushup(int x){s[x]=min(min(s[lc],s[rc]),vl[x]),sz[x]=sz[lc]+sz[rc]+1;}
inline void pushdown(int x){tg[x]?lc?pushr(lc),0:0,rc?pushr(rc),0:0,tg[x]=0:0;}
inline void rotate(int x){
	int y=fa[x],z=fa[y],k=c[y][1]==x,w=c[x][!k];
	nroot(y)?c[z][c[z][1]==y]=x:0,c[x][!k]=y,c[y][k]=w,w?fa[w]=y:0,fa[y]=x,fa[x]=z,pushup(y);
}
inline void splay(int x){
	int y=x,z=0;
	for(st[++z]=y;nroot(y);st[++z]=y=fa[y]);
	for(;z;pushdown(st[z]),z--);
	for(;nroot(x);rotate(x)){
		y=fa[x],z=fa[y];
		if(nroot(y)) rotate((c[y][0]==x)^(c[z][0]==y)?x:y);
	}
	pushup(x);
}
inline void access(int x){for(int y=0;x;splay(x),rc=y,pushup(x),x=fa[y=x]);}
inline int findroot(int x){
	for(access(x),splay(x);lc;pushdown(x),x=lc);
	return splay(x),pushup(x),x;
}
inline void makeroot(int x){access(x),splay(x),pushup(x),pushr(x);}
inline void cut(int x,int y){
	makeroot(x);
	if(findroot(y)==x&&fa[y]==x&&!c[y][0]) fa[y]=c[x][1]=0,pushup(x);
}
inline void query(int x,int y){makeroot(x),access(y),splay(y),pushup(y);}
inline void link(int x,int y){makeroot(x),findroot(y)!=x?fa[x]=y:0;}

signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q,ett=n,s[0]=2*m+n+1;
	rep(i,1,m) cin>>u[i]>>v[i],u[m+i]=u[i],v[m+i]=v[i];
	rep(i,1,n+2*m) sz[i]=1,vl[i]=s[i]=2*m+n+1;
	rep(i,1,m<<=1){
		for(rq[i]=rq[i-1];rq[i]<m;++ett,vl[ett]=s[ett]=rq[i],link(u[rq[i]],ett),link(v[rq[i]],ett))
			if(findroot(u[rq[i]+1])!=findroot(v[rq[i]+1])) ++rq[i];
			else if(query(u[rq[i]+1],v[rq[i]+1]),sz[v[rq[i]+1]]&2) ++rq[i],
				tmp=s[v[rq[i]]],cut(u[tmp],n+tmp),cut(n+tmp,v[tmp]);
			else break;
		cut(u[i],n+i),cut(n+i,v[i]);
		// rep(i,1,n) cerr<<fa[i]<<" ";cerr<<"\n";
		// rep(j,1,n) cerr<<findroot(j)<<" ";cerr<<"\n";
	}
	// rep(i,1,m) cerr<<rq[i]<<" ";cerr<<"\n";
	rep(i,1,q){
		int l,r;
		cin>>r>>l,++l,r+=m/2-1,cout<<(r>rq[l]?"YES\n":"NO\n");
	}
	return 0;
}
```

---

## 作者：小超手123 (赞：0)

### 题意：

给定 $n$ 条边，$m$ 个点的无向图，每次询问如果删掉编号为 $[l,r]$ 的边，剩下的图是否含有奇环。

### 分析：

记 $f_{r}$ 表示最小的 $l$ 满足删去 $[l,r]$ 的边剩下的图有奇环。

对于询问一组 $l,r$，只需判断 $l \ge f_{r}$ 即可。

不难发现当 $r$ 增大时，$f_{r}$ 单调不降。因此可以使用决策单调性转移。注意如果删除 $[r,r]$ 的边仍然不存在奇环，记 $f_{r}$ 此时为 $r+1$，这样还能满足单调性。

记 $Sol(l,r,L,R)$ 表示当前正在计算 $f_{l},f_{l+1},\dots,f_{r}$ 且它们的值域都属于 $[L,R]$。

通常使用并查集来维护一个图是否有奇环，具体的，对于边 $(u,v)$：在并查集中 $merge(u,v+n)$ 和 $merge(u+n,v)$，然后判断 $u$ 和 $v$ 是否在一个连通块即可。

考虑计算 $f_{mid}$ 的值。假设当前已经把 $[1,L-1]$ 和 $[r+1,n]$ 的边加入了连通块。

然后加入 $[mid+1,r]$ 的边，若此时还没有奇环，再加入 $L$ 后面的边。这样确定出 $f_{mid}$（记为 $x$）的值后，使用可撤销并查集退回到计算 $f_{mid}$ 前（记录一个时间戳）。递归进入 $Sol(l,mid-1,L,x)$ 和 $Sol(mid+1,r,x,R)$。注意一些加边和回退操作。时间复杂度 $O(m \log m \log n + Q)$。

### 代码：

```cpp
#include<bits/stdc++.h>
#define N 400005
using namespace std;
int n, m, Q, top, flag, U[N], V[N], f[N], fa[2 * N], h[2 * N];
struct ljm { int fx, fy, opt; }G[N];
int find(int x) { return fa[x] == x ? x : find(fa[x]); }
void Merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if(fx == fy) return; if(h[fx] < h[fy]) swap(fx, fy);
    G[++top] = ((ljm){fx, fy, 0});
    if(h[fx] == h[fy]) h[fx]++, G[top].opt = 1;
    fa[fy] = fx;
}
void work(int i) {
    Merge(U[i], V[i] + n); Merge(U[i] + n, V[i]);
    if(find(U[i]) == find(V[i])) flag = 1;
}
void Pop() { fa[G[top].fy] = G[top].fy, h[G[top].fx] -= G[top].opt; top--; }
void Sol(int l, int r, int L, int R) {
    if(l > r) return;
    int mid = (l + r) / 2, lst = top, ok = flag; f[mid] = mid + 1;
    for(int i = mid + 1; i <= r; i++) work(i); 
    for(int i = L; i <= min(R, mid); i++) {
        if(flag) {
            f[mid] = i;
            break;
        }
        work(i);
    }
    flag = ok; while(top > lst) Pop();
    for(int i = mid; i <= r; i++) work(i); 
    Sol(l, mid - 1, L, f[mid]);
    flag = ok; while(top > lst) Pop();
    for(int i = L; i < f[mid]; i++) work(i);
    Sol(mid + 1, r, f[mid], R);
}
signed main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> Q;
    for(int i = 1; i <= m; i++) cin >> U[i] >> V[i];
    for(int i = 1; i <= 2 * n; i++) fa[i] = i, h[i] = 1;
    Sol(1, m, 1, m + 1);
    while(Q--) {
        int l, r; cin >> l >> r;
        cout << (l > r ? "NO" : (l >= f[r] ? "YES" : "NO")) << endl;
    }
    return 0;
}
```

---

