# [NOISG 2022 Qualification] Dragonfly

## 题目背景

在植物园和碧山公园周围的池塘中，经常可以看到蜻蜓。在一个更密集的森林区域中，Benson 记录了 $n$ 个池塘，以及蜻蜓可以捕食的昆虫数量和种类。

在池塘 $i$，共有 $b_i$ 只昆虫，这些昆虫属于种类 $s_i$。

此外，还有 $n-1$ 条小径，每条小径连接两池塘 $u_j$ 和 $v_j$（双向）。并且满足蜻蜓从每一个池塘出发都能到达其它所有池塘。

Benson 抓住了 $d$ 只蜻蜓，并计划依次释放到池塘 $1$。每只蜻蜓有一个目标池塘 $h_k \neq 1$，会沿着最短路径飞到目标池塘，并在经过的每个池塘中捕食昆虫（包括池塘 $1$）。

每次捕食会减少池塘中 $1$ 只昆虫（如果昆虫数量不为 $0$）。需要帮助 Benson 计算每只蜻蜓的飞行过程中捕食到的不同种类昆虫的数量。

## 题目描述

请确定每只蜻蜓的飞行过程中捕食到的不同种类昆虫的数量。

## 说明/提示

【样例解释】

对于样例 $1$，第一只蜻蜓飞向池塘 $2$，捕食 $1$ 只种类 $1$ 的昆虫和 $1$ 只种类 $2$ 的昆虫。第二只蜻蜓飞向池塘 $5$，捕食种类 $1$ 的昆虫，总共捕食 $1$ 个种类。  

对于样例 $2$，每只蜻蜓飞行后捕食到的不同种类分别是 $2, 1, 1, 1$。

【数据范围】

- $2 \leq n \leq 2 \times 10^5$
- $1 \leq d \leq 2 \times 10^6$
- $1 \leq s_i \leq n$，$0 \leq b_i \leq d$，$1 \leq u_j, v_j < n$

| 子任务编号 | 分值 | 额外限制条件                              |
| :--------: | :--: | :---------------------------------------: |
| $1$        | $10$ | $n, d \leq 1000$                          |
| $2$        | $10$ | $b_i = d$                                 |
| $3$        | $12$ | $b_i \leq 10$                             |
| $4$        | $12$ | $u_j = j$, $v_j = j + 1$                  |
| $5$        | $37$ | $s_i = i$                                 |
| $6$        | $16$ | $d \leq 2 \times 10^5$                    |
| $7$        |  $3$ | 无额外限制                                |

## 样例 #1

### 输入

```
5 6
4 1 0 3 1
1 3 2 2 1
2 5 4 3 4 2
5 2
2 1
1 4
1 3```

### 输出

```
2 1 2 1 1 0```

## 样例 #2

### 输入

```
7 4
0 2 4 4 0 1 3
6 1 6 2 2 2 1
7 5 2 4
4 1
4 5
6 2
1 6
1 3
6 7```

### 输出

```
2 1 1 1```

# 题解

## 作者：Masterwei (赞：9)

来一个离线做法。

由于我们要求的是一条从 $1$ 到某个点的路径上大于 $0$ 的点的不同种类数，在线比较麻烦，考虑离线。

设 $val_i$ 表示第 $i$ 个点会在前 $val_i$ 只蜻蜓的操作后都大于等于 $0$，那么如果我们有了 $val_i$，就相当于要算一条 $1$ 到 $h_i$ 的路径中有多少个种类，使得至少有一个是这个种类的点的 $val\ge i$。这个明显可以离线二维数点。

接下来考虑怎样才能求出 $val_i$，发现我们可以二分，于是直接整体二分就做完了。

时间复杂度为 $O(n\log n+n\log d+d\log d\log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
int plen,ptop,pstk[40];
char rdc[1<<20],out[1<<20],*rS,*rT;
#define gc() (rS==rT?rT=(rS=rdc)+fread(rdc,1,1<<20,stdin),(rS==rT?EOF:*rS++):*rS++)
#define pc(x) out[plen++]=(x)
#define flush() fwrite(out,1,plen,stdout),plen=0
template<class T=int>inline T read(){
    T x=0;char ch;bool f=1;
    while(!isdigit(ch=gc()))if(ch=='-')f^=1;
    do x=(x<<1)+(x<<3)+(ch^48);while(isdigit(ch=gc()));
    return f?x:-x;
}
inline int read(char*const s){
	char *t=s,ch;
    while(!isgraph(ch=gc()));
	do(*(t++))=ch;while(isgraph(ch=gc()));
	return (*t)='\000',t-s;
}
template<class T=int>inline void write(T x){
	if(plen>=1000000)flush();
	if(!x)return pc('0'),void();
	if(x<0)pc('-'),x=-x;
	for(;x;x/=10)pstk[++ptop]=x%10;
	while(ptop)pc(pstk[ptop--]+'0');
}
inline void write(const char*s){
	if(plen>=1000000)flush();
	for(int i=0;(*(s+i))!='\000';pc(*(s+(i++))));
}
inline void write(char*const s){
	if(plen>=1000000)flush();
	for(int i=0;(*(s+i))!='\000';pc(*(s+(i++))));
}
const int Maxn=2e5+5,N=2e6+5;
int n,m;
int b[Maxn],s[Maxn],val[Maxn];
int h[N];
int head[Maxn],to[Maxn<<1],nxt[Maxn<<1],cnt1;
inline void add_e(int u,int v){
	to[++cnt1]=v;nxt[cnt1]=head[u];
	head[u]=cnt1;
}
int dfn[Maxn],cnt2,si[Maxn];
void dfs(int u,int v){
	dfn[u]=++cnt2;si[u]=1;
	for(int i=head[u];i;i=nxt[i]){
		int y=to[i];if(y==v)continue;
		dfs(y,u);si[u]+=si[y];
	}
}
int t[Maxn];
inline void add(int x,int d){
	for(;x<=n;x+=x&-x)t[x]+=d;
}
inline int query(int l,int r){
	int res=0;
	for(int x=r;x;x-=x&-x)res+=t[x];
	for(int x=l-1;x>0;x-=x&-x)res-=t[x];
	return res;
}
int d[Maxn],d1[Maxn];
void solve(int l,int r,int L,int R){
//	printf("%d %d:\n",l,r);
//	for(int i=L;i<=R;i++)printf("%d ",d[i]);
//	puts("");
	if(l==r){
		for(int i=L;i<=R;i++)val[d[i]]=l;
		return;
	}int mid=l+r>>1;
	for(int i=l;i<=mid;i++)add(dfn[h[i]],1);
	int tot1=L-1,tot2=R+1;
	for(int j=L;j<=R;j++){
		int i=d[j];
		if(query(dfn[i],dfn[i]+si[i]-1)>=b[i])d1[++tot1]=i;//,printf("[%d,%d]:%d\n",l,r,i);
		else d1[--tot2]=i;
	}
	for(int j=L;j<=R;j++)d[j]=d1[j];
	solve(mid+1,r,tot2,R);
	for(int i=l;i<=mid;i++)add(dfn[h[i]],-1);
	solve(l,mid,L,tot1);
}
vector<int>Q[Maxn];
int ans[N];
multiset<int>a[Maxn];
int t1[N];
inline void add1(int x,int d){
	x=-x;
	for(;x;x-=x&-x)t1[x]+=d;
}
inline int query1(int x){
	int res=0;
	for(;x<=m;x+=x&-x)res+=t1[x];
	return res;
}
void Dfs(int u,int v){
	if(!a[s[u]].empty())add1(*a[s[u]].begin(),-1);
	a[s[u]].insert(-val[u]);
	add1(*a[s[u]].begin(),1);
	for(int i:Q[u])ans[i]=query1(i);
	for(int i=head[u];i;i=nxt[i]){
		int y=to[i];if(y==v)continue;
		Dfs(y,u);
	}add1(*a[s[u]].begin(),-1);
	a[s[u]].erase(a[s[u]].find(-val[u]));
	if(!a[s[u]].empty())add1(*a[s[u]].begin(),1);
}
int main(){
//	freopen("P11295_4.in","r",stdin);
//	freopen("P11295.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)b[i]=read(),val[i]=m,d[i]=i;
	for(int i=1;i<=n;i++)s[i]=read();
	for(int i=1;i<=m;i++)h[i]=read(),Q[h[i]].emplace_back(i);
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add_e(u,v);add_e(v,u);
	}
	dfs(1,0);
	solve(1,m,1,n);
	for(int i=1;i<=n;i++)if(!b[i])val[i]=0;
//	for(int i=1;i<=n;i++)printf("val[%d]=%d\n",i,val[i]);
	Dfs(1,0);
	for(int i=1;i<=m;i++)write(ans[i]),pc(' ');
	flush();
	return 0;
}
/*
10 10
3 3 3 5 6 9 3 1 7 3
10 10 5 3 7 6 1 10 6 6
2 6 2 7 3 6 6 5 3 4
1 4
6 7
7 9
8 7
3 6
8 10
3 1
6 2
5 2
*/
```

---

## 作者：_AyachiNene (赞：5)

树剖单 $\log$ 做法。
# 思路：
容易想到维护每一个池塘能产生贡献的时间段，再做一个扫描线就行了。考虑如何维护时间段，发现时间段显然是一个前缀，对于每一个蜻蜓，去做一个链减，在用数据结构维护链上剩下的 $b_i$ 最小值及其位置，每次把用完的位置的时间更新并把这个点删掉，用线段树加树剖，精细实现（每个重链单独开一个数据结构）做到 $m\log n$。然后直接去做一个扫描线，发现相同颜色的池塘深度浅的更容易产生贡献，直接开一个类似单调栈的东西，在 dfs 过程中，如果当前池塘删除时间比栈顶大，就把多出来的部分加入贡献，用一个树状数组做区间加单点查，回溯时撤销就行了。最后复杂度 $O(m\log n)$。
# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){x="";char ch=getch();while(ch<'a'||ch>'z')ch=getch();while(ch>='a'&&ch<='z'){x+=ch;ch=getch();}}
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
struct node
{
	int nxt,to;
}e[2000005<<1];
int head[2000005],cnt_edge;
inline void add_edge(int u,int v)
{
	e[++cnt_edge].to=v;
	e[cnt_edge].nxt=head[u];
	head[u]=cnt_edge;
}
int n,m;
struct Nene
{
	struct segt{int mn,p,tag;};
	basic_string<segt>t;
 	#define ls (root<<1)
	#define rs (root<<1|1)
	#define mid (l+r>>1)
	inline void init(int s){t.resize((s<<2)+5);}
	inline void update(int root)
	{
		t[root].mn=min(t[ls].mn,t[rs].mn)+t[root].tag;
		if(t[ls].mn<t[rs].mn) t[root].p=t[ls].p;
		else t[root].p=t[rs].p;
	}
	void change(int x,int v,int p,int root,int l,int r)
	{
		if(l==r) return t[root].p=p,t[root].mn=v,void();
		if(x<=mid) change(x,v,p,ls,l,mid);
		else change(x,v,p,rs,mid+1,r);
		update(root);
	}
	void add(int x,int y,int v,int root,int l,int r)
	{
		if(l>=x&&r<=y) return t[root].mn+=v,t[root].tag+=v,void();
		if(x<=mid) add(x,y,v,ls,l,mid);
		if(y>mid) add(x,y,v,rs,mid+1,r);
		update(root);
	}
}seg[200005];
int a[200005],b[200005],c[2000005];
basic_string<int>q[200005];
int f[200005],dep[200005],son[200005],siz[200005],dfn[200005],top[200005],sz[200005],cnt;
void dfs1(int u,int fa)
{
	f[u]=fa;dep[u]=dep[fa]+1;siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dfs1(v,u);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int t)
{
	top[u]=t;dfn[u]=++cnt;
	if(son[u]) dfs2(son[u],t);
	else sz[top[u]]=dfn[u]-dfn[top[u]]+1,seg[top[u]].init(sz[top[u]]);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f[u]||v==son[u]) continue;
		dfs2(v,v);
	}
	dfn[u]-=dfn[top[u]]-1;
}
int w[200005];
inline void update_path(int x,int t)
{
	while(x)
	{
		seg[top[x]].add(dfn[top[x]],dfn[x],-1,1,1,sz[top[x]]);
		while(seg[top[x]].t[1].mn<=0)
		{
			int p=seg[top[x]].t[1].p;
			if(seg[top[x]].t[1].mn==0) w[p]=t;
			seg[top[x]].change(dfn[p],1e9,p,1,1,sz[top[x]]);
		}
		x=f[top[x]];
	}
}
namespace Elaina
{
	int t[2000005];
	inline int lowbit(int x){return x&-x;}
	inline void Add(int x,int v){for(;x<=m;x+=lowbit(x))t[x]+=v;}
	inline void add(int x,int y,int v){Add(x,v);Add(y+1,-v);}
	inline int query(int x){int res=0;for(;x;x-=lowbit(x))res+=t[x];return res;}
}
basic_string<int>stk[200005];
int ans[2000005];
void dfs3(int u)
{
	int l=0;
	if(stk[b[u]].back()<w[u]) l=stk[b[u]].back()+1,Elaina::add(l,w[u],1),stk[b[u]].push_back(w[u]);
	for(int i=0;i<q[u].size();i++) ans[q[u][i]]=Elaina::query(q[u][i]);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f[u]) continue;
		dfs3(v);
	}
	if(l) Elaina::add(l,w[u],-1),stk[b[u]].pop_back();
}
int main()
{
//	freopen("P11295_5.in","r",stdin);
//	freopen(".out","w",stdout);
	read(n,m);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=1;i<=n;i++) read(b[i]),stk[i].push_back(0);
	for(int i=1;i<=m;i++) read(c[i]),q[c[i]].push_back(i);
	for(int i=1;i<n;i++)
	{
		int u,v;read(u,v);
		add_edge(u,v);add_edge(v,u);
	}
	dfs1(1,0);dfs2(1,1);
	for(int i=1;i<=n;i++) seg[top[i]].change(dfn[i],a[i],i,1,1,sz[top[i]]),w[i]=a[i]?m:0;
	for(int i=1;i<=m;i++) update_path(c[i],i);
	dfs3(1);
	for(int i=1;i<=m;i++) write(ans[i]),putch(' ');
	flush();
	return 0;
}
```

---

## 作者：dengchengyu (赞：3)

# [[NOISG2022 Qualification] Dragonfly](https://www.luogu.com.cn/problem/P11295) Solution in $O(d \log d)$

**提供一个使用线段树合并、栈、树状数组的严格单 $\log$ 离线做法。**

**题目大意**：给你一棵树，每个点有权值和颜色，每次问你一个从 $1$ 开始的路径，求权值不为 $0$ 的节点的颜色种类数，并且把所有权值不为 $0$ 的节点权值减一，询问之间不独立。

**解题思路**：考虑离线下来，因为一个节点权值为 $0$ 后就没有贡献了，那么考虑求出最后能产生贡献的时刻 $t_i$。

那么能吃节点 $i$ 的询问在 $i$ 的子树内。考虑以时间为下标建线段树，询问就在这个询问所在的时间插入一个点，那么我们可以自底向上线段树合并，合并到点 $i$ 时在线段树上二分即可求出 $t_i$。这一部分的线段树只需维护一个子树大小。这一部分是 $O(d\log d)$ 的。

求出 $t_i$ 后，对于第 $j$ 个询问，我们就是求满足下列条件的颜色个数：从 $1$ 到 $h_j$ 路径上存在这种颜色的点 $i$ 使得 $t_i\ge j$。

考虑从根开始遍历，进入一个节点就插入这个节点的贡献，离开子树就撤销贡献。

我们现在就想知道从 $1$ 到当前点的路径上，每种颜色 $t$ 的最大值是多少。然后每次最大值更新时用数据结构维护一下即可。

由于如果存在颜色相同的 $i,j$ 满足 $i$ 是 $j$ 的祖先，且 $t_i\ge t_j$，那么 $j$ 是没有用的。所以考虑对每种颜色开一个栈，当 $t$ 大于栈顶时才推进栈中，然后用一个以 $t$ 为下标的树状数组维护：有多少种颜色的 $t$ 大于等于某个数。

这一部分也是 $O(d\log d)$ 的。

然后就做完了，最终的复杂度就是 $O(d\log d)$ 的（这里我们设 $n,d$ 同阶）。

**实现细节**：

注意到线段树合并时，我们动态开点的静态数组可能会 MLE。但是线段树合并时很多合并后的节点就扔掉了。考虑用一个 `vector` 回收节点即可。

另外注意 $n,d$ 的规模是不一样的，数组不要开小了。

**[AC 代码](https://www.luogu.com.cn/record/197636113)**：

```cpp
const int N=2e5+5,M=2e6+5,L=2e7;
int tot,ls[L],rs[L],sz[L],rt[N];
vi emp;
#define mid ((l+r)>>1)
void merge(int &x,int y,int l,int r) {
	if(!x) {x=y; return;}
	if(!y) {return;}
	if(l==r) {sz[x]+=sz[y]; return;}
	merge(ls[x],ls[y],l,mid),merge(rs[x],rs[y],mid+1,r);
	sz[x]=sz[ls[x]]+sz[rs[x]];
	emp.pb(y);
}
void add(int &x,int l,int r,int y) {
	if(!x) {
		if(tot<L-1) x=++tot;
		else x=Back(emp),emp.pop_back(),sz[x]=ls[x]=rs[x]=0;
	}
	if(l==r) {sz[x]++; return;}
	if(y<=mid) add(ls[x],l,mid,y);
	else add(rs[x],mid+1,r,y);
	sz[x]=sz[ls[x]]+sz[rs[x]];
}
int query(int x,int l,int r,int y) {
	if(l==r) return l;
	if(sz[ls[x]]>=y) return query(ls[x],l,mid,y);
	return query(rs[x],mid+1,r,y-sz[ls[x]]);
}
struct BIT{
	#define lowbit(x) (x&(-x))
	int s[M];
	void update(int x,int y) {
		while(x<M) s[x]+=y,x+=lowbit(x);
	}
	int query(int x){
		int _s=0;
		while(x) _s+=s[x],x-=lowbit(x);
		return _s;
	}
}bit;
vi g[N],q[N];
int n,Q;
int b[N],s[N],h[M],t[N];
void dfs1(int x,int y) {
	for(int v:g[x]) {
		if(v==y) continue;
		dfs1(v,x);
		merge(rt[x],rt[v],1,Q);
	}
	for(int v:q[x]) add(rt[x],1,Q,v);
	if(b[x]) {
		if(sz[rt[x]]<b[x]) t[x]=Q;
		else t[x]=query(rt[x],1,Q,b[x]);
	}
}
stack<int> mx[N];
int ans[M];
void solve(int x,int y){
	int co=s[x],flag=0;
	if(t[x]) {
		if(mx[co].empty()||t[x]>mx[co].top()) {
			if(Size(mx[co])) bit.update(M-mx[co].top(),-1);
			mx[co].push(t[x]);
			bit.update(M-t[x],1);
			flag=1;
		}
	}
	for(int v:q[x]) {
		ans[v]=bit.query(M-v);
	}
	for(int v:g[x]) {
		if(v==y) continue;
		solve(v,x);
	}
	if(flag) {
		bit.update(M-t[x],-1);
		mx[co].pop();
		if(Size(mx[co])) bit.update(M-mx[co].top(),1);
	}
}
signed main(){
	read(n,Q);
	fo(i,1,n) read(b[i]);
	fo(i,1,n) read(s[i]);
	fo(i,1,Q) read(h[i]),q[h[i]].pb(i);
	fu(i,1,n) {
		int u,v; read(u,v);
		g[u].pb(v),g[v].pb(u);
	}
	dfs1(1,0);
	solve(1,0);
	fo(i,1,Q) write(ans[i],' ');
	return 0;
}
```

---

## 作者：nullqtr_pwp (赞：3)

四个月前模拟赛原题今天才找到，真服了。

提供一个单 $\log$ 做法，**不需要**高级数据结构。

## Solution

>二分时，如果要减小复杂度，每次二分可以保留确定部分的信息。


记原题的 $d$ 在下文中为 $m$。


考虑求出 $t_i$ 表示 $i$ 号点被取完的时刻。如果有了所有的 $t_i$，由于颜色相同的只能计入一次贡献，我们要求一个点在某个时刻被激活当且仅当祖先同色点都被取完，此时可以有贡献。那么可以 dfs 序来刻画一个子树。以横轴为时间，纵轴为 dfs 序，此时就可以在 dfs 来插入若干矩形表示矩形 $+1$，对于一个操作的答案就是二维平面上单点的和，可以用扫描线加树状数组维护。

考虑如何求 $t_i$，我们可以整体二分，设当前二分的时间为 $[l,r]$。如果单层使用树状数组维护，常数虽然很小，但是复杂度是双 $\log$，无法通过模拟赛原题。整体二分就需要在 $mid$ 时刻计算出每个点被经过的次数。判断哪些点被取完。如果被取完就染黑，否则染为白色。我们希望单层做到线性 check。所有商人都是从根往下走，考虑将整棵树分为两棵，$T_1$ 只包含黑点，$T_2$ 只包含白点：将所有白点找到祖先中首个白点；所有黑点找到祖先中首个黑点。对于 $[l,mid]$ 时刻每个操作的终点 $h$ 可以直接改为 $h$ 祖先中首个黑点；对于 $[mid+1,r]$ 每个操作终点改为 $h$ 祖先中首个白点。直接递归做即可。同时需要维护 $T_1,T_2$ 上每个点的父亲，统计经过次数可以使用树上差分的思想，对于二分对象保持原树的 dfs 序的偏序关系。这样减小复杂度的主要思想如开头所示。

时间复杂度 $\mathcal O((n+m)\log m)$。

## Code
```cpp
// 私は猫です

#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define inf 1000000000
#define infll 1000000000000000000ll
#define pii pair<int,int>
#define rep(i,a,b,c) for(int i=(a);i<=(b);i+=(c))
#define per(i,a,b,c) for(int i=(a);i>=(b);i-=(c))
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define dF(i,a,b) for(int i=(a);i>=(b);i--)
#define cmh(sjy) while(sjy--)
#define lowbit(x) (x&(-x))
#define HH printf("\n")
#define eb emplace_back
#define poly vector<int>
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
inline void chkmax(int &x,int y){ x=max(x,y); }
inline void chkmin(int &x,int y){ x=min(x,y); }
const int mod=998244353,maxn=800005;
vector<int>g[maxn];
int a[maxn],col[maxn],ans[2000005],h[2000005],n,m,rev[maxn],dfn[maxn],siz[maxn],tim;
int qwq[maxn],fa[maxn];
void init_dfs(int u,int f=0){
	rev[dfn[u]=++tim]=u,siz[u]=1,fa[u]=f;
	for(int v:g[u])if(v^f)init_dfs(v,u),siz[u]+=siz[v];
}
struct DS1{
	int t[2000005],N;
	void clear(){ F(i,1,N)t[i]=0; }
	void add(int x,int y){ if(!x)return; for(;x<=N;x+=lowbit(x))t[x]+=y; }
	void add(int l,int r,int x){ add(l,x),add(r+1,-x); }
	int query(int x){ int R=0; for(;x;x^=lowbit(x))R+=t[x]; return R; }
	int query(int l,int r){ return query(r)-query(l-1); }
}t1;
int V[maxn],Vl[maxn],Vr[maxn],cnt[maxn],up[2000005];
pii tmp[maxn];
void find(int l,int r,int x,int y){
	if(x>y)return;
	if(l==r){
		F(i,x,y)qwq[V[i]]=l;
		return;
	}
	int mid=(l+r)>>1;
	F(i,x,y)cnt[V[i]]=0;
	F(i,l,mid)++cnt[up[i]];
	dF(i,y,x)cnt[fa[V[i]]]+=cnt[V[i]];
	auto chk=[&](int u){ return cnt[u]<a[u]; };
	F(i,x,y){
		const int u=V[i];
		if(chk(fa[u]))tmp[u]=mkp(fa[u],tmp[fa[u]].se);
		else tmp[u]=mkp(tmp[fa[u]].fi,fa[u]);
	}
	F(i,l,mid)if(chk(up[i]))up[i]=tmp[up[i]].se;
	F(i,mid+1,r)if(!chk(up[i]))up[i]=tmp[up[i]].fi;
	int cnt1=0,cnt2=0;
	F(i,x,y){
		const int u=V[i];
		if(!chk(u))Vl[++cnt1]=u,fa[u]=tmp[u].se;
		else Vr[++cnt2]=u,fa[u]=tmp[u].fi,a[u]-=cnt[u];
	}
	F(i,1,cnt1)V[x+i-1]=Vl[i];
	F(i,1,cnt2)V[x+cnt1+i-1]=Vr[i];
	find(l,mid,x,x+cnt1-1);
	find(mid+1,r,x+cnt1,y);
}
vector<array<int,3>>qu[maxn];
void ins_mat(int l1,int r1,int l2,int r2){
	if(l1>r1||l2>r2)return;
	qu[l2].push_back({l1,r1,1});
	qu[r2+1].push_back({l1,r1,-1});
}
int lst[maxn];
void dfs(int u,int f=0){
	int t=lst[col[u]];
	ins_mat(t+1,qwq[u],dfn[u],dfn[u]+siz[u]-1);
	chkmax(lst[col[u]],qwq[u]);
	for(int v:g[u])if(v^f)dfs(v,u);
	lst[col[u]]=t;
}
void solve(){
	n=read(),m=read();
	F(i,1,n)a[i]=read();
	F(i,1,n)col[i]=read();
	F(i,1,m)up[i]=h[i]=read();
	F(i,1,n-1){
		int u=read(),v=read();
		g[u].push_back(v),g[v].push_back(u);
	}init_dfs(1);
	F(i,1,n)V[i]=rev[i];
	find(0,m+1,1,n),dfs(1);
	t1.N=m;
	F(i,1,n)g[i].clear();
	F(i,1,m)g[h[i]].push_back(i);
	F(i,1,n){
		for(auto [l,r,x]:qu[i])t1.add(l,r,x);
		for(int x:g[rev[i]])ans[x]=t1.query(x);
	}
	F(i,1,m)printf("%d ",ans[i]);
}
```

---

## 作者：xiezheyuan (赞：3)

感觉大家好像都写的是 $O((n+d)\log n)$ 的，给大家来一个 $O(n\log n+d\log^2 n)$ 的做法养养眼（bushi），成功抢下最劣解。

## 简要题意

有一个 $n$ 个点的树，第 $i$ 个点有 $b_i$ 个数，均为 $s_i$。

有 $d$ 次询问，每次询问给出一个点 $h_i$，一个人从 $h_i$ 走到 $1$，经过（包含起点和终点）的每一个点时，如果这个点有数，就将点上的任意一个数拿到手中，输出此时手中的数的种类数。询问完成后，将手中的所有数丢弃。

询问与询问之间**不相互独立**。

$1\leq n\leq 2\times 10^5,1\leq m\leq 2\times 10^6$。时间限制 $5000\mathrm{ms}$。

## 思路

首先考虑序列上的问题怎么做（也就是 Subtask 4）。问题就变成了给定一个序列，第 $i$ 个位置有 $b_i$ 个 $s_i$，每次询问就是一个人从 $h_i$ 出发走到 $1$，也就是走一段前缀。

我们不妨维护每一个点 $i$ 前（祖先）中离 $i$ 最近（深度最大）的点上写的数和 $i$ 相同的点，记作 $\mathrm{lst}(i)$，同时定义 $\mathrm{nxt}(\mathrm{lst}(i))=i$。那么我们可以维护一个树状数组，在每种颜色最早出现（深度最小）的位置增加 $1$，然后我们维护一个神秘数据结构，在这个数据结构上做前缀减 $1$，然后求出这段前缀中所有为 $0$ 的元素。

如果找到的点 $i$ 在树状数组中加过了 $1$（也就是成为了深度最浅的），就减去，然后尝试找到这个点 $i$ 的 $\mathrm{nxt}(i)$，然后重复此流程找到一个在数据结构中不为 $0$ 的 $i'$，将树状数组中的 $i'$ 增加 $1$。

以上思路都是很显然的，唯一的问题就是这个“神秘数据结构”是什么，需要支持前缀减 $1$ 同时查询新变成 $0$ 的元素。实际上这玩意用线段树就可以实现。具体来说，前缀减 $1$ 就正常打标记，查询时在线段树上做一个类似势能线段树的东西，如果当前节点的最小值 $\geq 1$，就直接跳出，因为子树内没有答案，否则直接递归，到达叶子结点就找到了答案，注意此时要将叶子节点的值设为 $\infty$ 表示以后这个点不会被用到了。由于每个叶子结点只会访问一次，故复杂度正确。

时间复杂度 $O((n+d)\log n)$。

现在考虑将这个做法上树，对树进行重链剖分，唯一的问题是 $\mathrm{nxt}(i)$ 不唯一，可以用一个 `vector` 记录一下，更新的时候写一个 BFS 即可。

时间复杂度 $O(n\log n+d\log^2 n)$ 无压力通过本题。利用全局平衡二叉树，可以优化到 $O((n+d)\log n)$，不过没必要。

## 代码

注意实现细节。

```cpp
#include <bits/stdc++.h>
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid ((l + r) >> 1)
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 2e5 + 5, M = 2e6 + 5;
int n, m, a[N], b[N], qry[M], lst[M];
vector<int> g[N], kcr[N];

int dep[N], siz[N], son[N], father[N], top[N], seg[N], rev[N];
bool failed[N];

void dfs1(int u, int fa){
    dep[u] = dep[fa] + 1, siz[u] = 1, father[u] = fa;
    int tmp = lst[b[u]];
    if(a[u]){
        kcr[lst[b[u]]].emplace_back(u);
        lst[b[u]] = u;
    }
    for(int v : g[u]){
        if(v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
    lst[b[u]] = tmp;
}

void dfs2(int u, int fa){
    if(son[u]){
        top[son[u]] = top[u], seg[son[u]] = ++seg[0], rev[seg[0]] = son[u];
        dfs2(son[u], u);
    }
    for(int v : g[u]){
        if(v == fa || v == son[u]) continue;
        top[v] = v, seg[v] = ++seg[0], rev[seg[0]] = v;
        dfs2(v, u);
    }
}

int mint[N << 2], tag[N << 2];

void build(int i, int l, int r){
    if(l == r) return (mint[i] = (a[rev[l]] ? a[rev[l]] : m)), void();
    build(ls, l, mid), build(rs, mid + 1, r);
    mint[i] = min(mint[ls], mint[rs]);
}

void mktag(int i, int v){ mint[i] += v, tag[i] += v; }
void pushdown(int i){
    if(tag[i]) mktag(ls, tag[i]), mktag(rs, tag[i]), tag[i] = 0;
}

vector<int> vct;

void update(int ql, int qr, int v, int i, int l, int r){
    if(ql <= l && r <= qr) return mktag(i, v);
    pushdown(i);
    if(ql <= mid) update(ql, qr, v, ls, l, mid);
    if(qr > mid) update(ql, qr, v, rs, mid + 1, r);
    mint[i] = min(mint[ls], mint[rs]);
}

void maintain(int ql, int qr, int i, int l, int r){
    if(mint[i] >= 1) return;
    if(l == r) return (mint[i] = m), vct.emplace_back(rev[l]), void();
    pushdown(i);
    if(ql <= mid) maintain(ql, qr, ls, l, mid);
    if(qr > mid) maintain(ql, qr, rs, mid + 1, r);
    mint[i] = min(mint[ls], mint[rs]);
}

void Update(int u){
    vct.clear();
    while(u){
        update(seg[top[u]], seg[u], -1, 1, 1, n);
        maintain(seg[top[u]], seg[u], 1, 1, n);
        u = father[top[u]];
    }
}

int t[N];

void update(int p, int v){
    while(p <= n) t[p] += v, p += lowbit(p);
}

int query(int p){
    int ret = 0;
    while(p) ret += t[p], p -= lowbit(p);
    return ret;
}

int Query(int u){
    int ret = 0;
    while(u){
        ret += query(seg[u]) - query(seg[top[u]] - 1);
        u = father[top[u]];
    }
    return ret;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> b[i];
    for(int i=1;i<=m;i++) cin >> qry[i];
    for(int i=1,u,v;i<n;i++){
        cin >> u >> v;
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    seg[1] = seg[0] = top[1] = rev[1] = 1;
    dfs1(1, 0), dfs2(1, 0), build(1, 1, n);
    for(int v : kcr[0]) update(seg[v], 1);
    for(int i=1;i<=m;i++){
        cout << Query(qry[i]) << ' ';
        Update(qry[i]);
        for(int j : vct){
            queue<int> q; q.emplace(j); failed[j] = 1;
            if((query(seg[j]) - query(seg[j] - 1)) != 1) continue;
            update(seg[j], -1);
            while(!q.empty()){
                int u = q.front(); q.pop();
                if(!failed[u]){
                    update(seg[u], 1);
                    continue;
                }
                if((query(seg[u]) - query(seg[u] - 1)) == 1) update(seg[u], -1);
                for(int v : kcr[u]) q.emplace(v);
            }
        }
    }
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：Chenyichen0420 (赞：1)

## 思路分析

对于每一个颜色，我们总是取深度最浅的作为代表元素，考虑能不能算出这个点能覆盖到哪些询问。

具体的来说，一个点能覆盖到的最靠右的询问就是他的子树下的第 $b_i$ 个询问。

这个看似可以用线段树合并去维护，实际上因为异常大的询问个数会导致 RE/MLE，比如[这个提交记录](https://www.luogu.com.cn/record/220330222)。

因此我们换一个思路：先用 dfs 序将问题转换为序列问题，然后用主席树去维护一下。其实这样确实是可行的。

具体的来说，我们进行两次 dfs。第一次标记每一个点的进出 dfs 序的位置，同时将询问添加到每一个点的线段树节点上。

第二次记录当前颜色的最靠下的出现位置，线段树二分求出能覆盖到的最靠右的询问，左端点设为父亲的右端点 $+1$。

处理完后，我们将每一次的修改位置标记到对应的询问上。

最后在处理询问的时候，我们先将这个点对应的修改的位置的子树的值修改掉，然后再查询。因为我们使用了 dfs 序，所以说一个子树在序列上也是连续的，可以用树状数组维护。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct IO {
#define mxsz (1 << 21)
	char buf[mxsz], * p1, * p2;
	char pbuf[mxsz], * pp;
	IO() : p1(buf), p2(buf), pp(pbuf) {}
	~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
	inline char gc() {
		if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, mxsz, stdin);
		return p1 == p2 ? ' ' : *p1++;
	}
#ifndef sipt
	inline int read() {
		int r = 0; char c = gc(); while (c < '0' || c>'9') c = gc();
		while (c >= '0' && c <= '9') r = r * 10 + (c ^ 48), c = gc();
		return r;
	}
#else
	inline int read() {
		int r = 0; char c = gc(); bool rev = 0;
		while (c < '0' || c>'9') rev |= (c == '-'), c = gc();
		while (c >= '0' && c <= '9') r = r * 10 + (c ^ 48), c = gc();
		return rev ? ~r + 1 : r;
	}
#endif
	inline void push(const char& c) {
		if (pp - pbuf == mxsz) fwrite(pbuf, 1, mxsz, stdout), pp = pbuf;
		*pp++ = c;
	}
	inline void write(int x) {
		static char sta[22]; int top = 0;
		do sta[top++] = x % 10, x /= 10; while (x);
		while (top) push(sta[--top] ^ 48);
	}
	inline void write(int x, char opc) {
#ifdef sopt
		if (x < 0) push('-'), x = ~x + 1;
#endif
		write(x), push(opc);
	}
} io;
vector<int>son[200005], q[200005], cz[2000005];
int n, m, c[200005], t[200005], lp[200005], rp[200005], ap, p[2000005];
struct seg_tree {
	struct node { int ls, rs, v; }re[2000005 * 32]; int sc;
	inline void ins(int cp, int l, int r, int& p) {
		re[++sc] = re[p]; p = sc; if (re[p].v++, l == r) return;
		int mid = l + r >> 1;
		if (cp <= mid) ins(cp, l, mid, re[p].ls);
		else ins(cp, mid + 1, r, re[p].rs);
	}
	inline int que(int k, int l, int r, int lp, int rp) {
		if (l == r) return l;
		int lk = re[re[rp].ls].v - re[re[lp].ls].v, mid = l + r >> 1;
		if (k <= lk) return que(k, l, mid, re[lp].ls, re[rp].ls);
		return que(k - lk, mid + 1, r, re[lp].rs, re[rp].rs);
	}
}sgt;
int id[200005], rt[200005], cp[200005], fr[200005], fl[200005];
inline void dft(int p, int f) {
	lp[p] = ++ap; id[ap] = p; rt[p] = rt[id[ap - 1]];
	for (int j : q[p]) sgt.ins(j, 0, m, rt[p]);
	for (int sp : son[p]) if (sp != f) dft(sp, p);
	rp[p] = ap;
}
inline void get(int p, int f) {
	fr[p] = sgt.que(c[p], 0, m, rt[id[lp[p] - 1]], rt[id[rp[p]]]);
	fl[p] = max(fr[cp[t[p]]] + 1, fl[cp[t[p]]]);
	if (fl[p] <= fr[p])
		cz[fl[p]].emplace_back(p),
		cz[fr[p] + 1].emplace_back(-p);
	int np = p; swap(np, cp[t[p]]);
	for (int sp : son[p]) if (sp != f) get(sp, p);
	swap(np, cp[t[p]]);
}
struct tree_array {
	int v[200005];
	inline static constexpr int lb(const int& p) { return p & ~p + 1; }
	inline void ins(int p, int t) {
		do v[p] += t; while ((p += lb(p)) <= n);
	}
	inline int que(int p) {
		int t = 0; do t += v[p]; while (p -= lb(p)); return t;
	}
}ta;
signed main() {
	ios::sync_with_stdio(0);
	n = io.read(); m = io.read();
	for (int i = 1; i <= n; ++i) c[i] = io.read();
	for (int i = 1; i <= n; ++i) t[i] = io.read();
	for (int i = 1; i <= m; ++i)
		q[p[i] = io.read()].emplace_back(i);
	for (int i = 1, l, r; i != n; ++i)
		l = io.read(), r = io.read(),
		son[l].emplace_back(r),
		son[r].emplace_back(l);
	dft(1, 0); get(1, 0);
	for (int i = 1; i <= m; ++i) {
		for (int j : cz[i])
			if (j > 0) ta.ins(lp[j], 1), ta.ins(rp[j] + 1, -1);
			else ta.ins(lp[-j], -1), ta.ins(rp[-j] + 1, 1);
		io.write(ta.que(lp[p[i]]), ' ');
	}
}
```

---

## 作者：Union_Find (赞：1)

这道题比较难刻画的一个点就是如何表示种类数。常见的方法是用这种颜色最前的一个点来表示，但是在这题里就不太合适。因为一个点会消失，所以我们尝试刻画的时间轴。

我们定义 $t_i$ 表示 $i$ 这个点在第 $t_i$ 次询问的时候变成 $0$，如果不会变成 $0$，$t_i = d + 1$。如果一开始就是 $0$，$t_i = 0$。如果在一个时间点，一个点的祖先里所有和它颜色相同的点都变成了 $0$，那么一直到它消失，它的子树内就有了 $1$ 的贡献。所以我们可以用 $L$ 表示这个点祖先全部消失的时间点，$R$ 表示自己消失的时间点，用 $dfn$ 刻画子树，我们就会发现这其实就是一个矩阵加，然后单点查询。可以转化成单点加，矩阵查。

二维树状数组开不下，我们要用离线二维数点。这一部分比较简单，就是板子，不会的具体看代码。

剩下的就是求 $t_i$ 了。树链剖分似乎可以，但是我们不喜欢大的数据结构，所以考虑二分。对于一个点，如果二分到 $mid$，就判断当前的子树内有多少个询问的点，和 $b_i$ 比较。但是这样子 check 就炸了。考虑可以整体二分。

我们整体二分，然后对于 $[l,mid]$ 的点加进树状数组里，时间复杂度就是 $O(d\log d\log n)$ 的，虽然 $d \le 2 \times 10^6$，但是整体二分和树状数组常熟很小，时限也很大，可以通过。

最后时间复杂度就是整体二分和离线二维数点，$O(d\log d\log n + d\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define N 200005
#define M 2000005
il int rd(){
	int s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
int n, m, a[N], c[N], h[M], u, v, q[N], q1[N], q2[N], tim[N];
int dfn[N], sz[N], ex, t[N];
int tr[N];
vector <int> e[N];
struct PT{
	int y, val;
};
vector <PT> dot[M];
il void add(int x, int k){for (int i = x; i <= n; i += (i & (-i))) tr[i] += k;}
il int ask(int x){int ans = 0;for (int i = x; i >= 1; i -= (i & (-i))) ans += tr[i];return ans;}

void dfs_init(int u, int fa){
	dfn[u] = ++ex, sz[u] = 1;
	for (int v : e[u]) if (v != fa) dfs_init(v, u), sz[u] += sz[v];
}
void solve(int l, int r, int ql, int qr){
	if (ql > qr) return ;
	if (l == r){
		for (int i = ql; i <= qr; i++) t[q[i]] = l;
		return ;
	}int mid = (l + r) >> 1, c1 = 0, c2 = 0, cnt = ql - 1, qmid;
	for (int i = l; i <= mid; i++) add(dfn[h[i]], 1);
	for (int i = ql; i <= qr; i++){
		int u = q[i], tmp = ask(dfn[u] + sz[u] - 1) - ask(dfn[u] - 1);
		if (tmp >= a[u]) q1[++c1] = q[i];
		else a[u] -= tmp, q2[++c2] = q[i];
	}for (int i = max(l, 1); i <= mid; i++) add(dfn[h[i]], -1);
	for (int i = 1; i <= c1; i++) q[++cnt] = q1[i];
	qmid = cnt;
	for (int i = 1; i <= c2; i++) q[++cnt] = q2[i];
	solve(l, mid, ql, qmid), solve(mid + 1, r, qmid + 1, qr);
}
void insert(int ax, int bx, int ay, int by){
	dot[ax].push_back(PT{ay, 1}), dot[ax].push_back(PT{by + 1, -1}), 
	dot[bx + 1].push_back(PT{ay, -1}), dot[bx + 1].push_back(PT{by + 1, 1});
}
void dfs_insert(int u, int fa){
	int lst = tim[c[u]];
	if (lst < t[u]) insert(lst + 1, t[u], dfn[u], dfn[u] + sz[u] - 1), tim[c[u]] = t[u];
	for (int v : e[u]) if (v != fa) dfs_insert(v, u);
	tim[c[u]] = lst;
}
int main(){
	n = rd(), m = rd();
	for (int i = 1; i <= n; i++) a[i] = rd();
	for (int i = 1; i <= n; i++) c[i] = rd();
	for (int i = 1; i <= m; i++) h[i] = rd();
	for (int i = 1; i < n; i++) u = rd(), v = rd(), e[u].push_back(v), e[v].push_back(u);
	for (int i = 1; i <= n; i++) q[i] = i;
	dfn[0] = 1e9;
	dfs_init(1, 0);
	solve(0, m + 1, 1, n);
	dfs_insert(1, 0);
	for (int i = 1; i <= m; i++){
		for (auto p : dot[i]) add(p.y, p.val);
		printf ("%d ", ask(dfn[h[i]]));
	} 
	return 0;
}

```

---

## 作者：tzl_Dedicatus545 (赞：1)

首先肯定是说你求出来每个点的最后存活时间，这个直接可持久化线段树 + 二分就可以做到 $n\log^2m$。

然后你求出来最后存活时间之后直接在树上 dfs 一遍，维护当前掉到根的那条链上每个颜色的最后消失时间，这里的复杂度是 $n\log m$ 的。

直接写这个你能获得最劣解。

吃饭老师对于“求出每个点的存活时间”这一部分有一个高妙做法：

我们直接对所有点进行整体二分：

> 每次处理时只传入有用的点（所有操作与查询的端点），之后再暴力滚前缀和。
>
> 由于只传入了有用的点，一层的复杂度是 $ O(r−l+R−L)$，所以总的复杂度就是 $O((n+d)\log n)$。

所以总复杂度可以做到 $O(n\log m)$

---

## 作者：Hoks (赞：1)

## 前言
好玩树剖题。

但是你能不能别再看错题了喵。

广告：[『从入门到入土』树链剖分学习笔记](https://www.luogu.com.cn/article/56o68hfu)。
## 思路分析
先寄一下我看错的部分：**每只蜻蜓都是从根出发的。**

这点就是解题的切入点。

在这个条件保证下，我们知道，如果两个可取的点 $u,v$ 颜色相同且 $u$ 为 $v$ 的祖先，那么 $u$ 严格不劣于 $v$。

考虑下如果不带修怎么做。

那就是我们先对每种颜色最早出现的地方单点 $+1$，然后数根链求和。

然后我们来修改。

修改时我们只关注新被减到 $0$ 的点，因为这些点从可取变成了不可取。

那么我们可以先用线段树维护最小值的方法求出新被减到 $0$ 的点。

具体的，当当前区间的最小值 $>1$ 时就直接打 `tag` 返回，不然就递归直到叶子修改，把 $0$ 的点搞出来同时修改值为 $+\infty$ 防止对以后产生影响。

接下来的问题是当一种颜色目前最优的点没了之后，怎么找到后继的点？

后继的点集，肯定是**一些最近的点**组成的集合。

还是前面的那个 $u$ 不劣于 $v$ 的性质，我们可以考虑预处理出每个点他后继的点集，一直遍历直到找到还可以取的点截止即可。

实现上可以先扔在 vector 里，修改时使用队列遍历。

结合上面那个要维护单点修改，树链查询，我们可以用 BIT+线段树+树剖解决。
## 代码
注意初始值即为 $0$ 的点。

使用了封装的板子，有点丑。
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=2e6+10,M=2,V=1e9,INF=1e18;
struct BIT//binary_indexed_tree
{
    int c[N],n;BIT(){memset(c,0,sizeof c);}
    void modify(int x,int v){for(;x<=n;x+=x&-x) c[x]+=v;}
    int query(int x){int res=0;for(;x;x-=x&-x) res+=c[x];return res;}
    void mdf(int l,int r,int v){modify(l,v),modify(r+1,-v);}
    int qry(int l,int r){return query(r)-query(l-1);}
}tt;vector<int>cur;
int n,d,a[N],s[N],q[N],mp[N],lst[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(long long x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='|'||c=='-'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
namespace tree_decomposition_SGT_Point
{
	int cnt;vector<int> e[N],nxt[N];
	int fa[N],son[N],si[N],dep[N];
	int top[N],id[N],dfn[N];
	struct SGT
	{
		#define ls (p<<1)
		#define rs (p<<1|1)
		#define mid ((l+r)>>1)
		#define pushup(p) (t[p]=min(t[ls],t[rs]))
		#define pushdown(p) (t[ls]+=lz[p],t[rs]+=lz[p],lz[ls]+=lz[p],lz[rs]+=lz[p],lz[p]=0)
		int L,R;
		vector<int> t,lz;//t for tree and lz for lazy tag
		void init(int l,int r)
		{
			t=lz=vector<int>((r-l+10)<<2);
			L=l,R=r;
		}
		void build(int p,int l,int r,int a[],int id[])
		{
			if(p==1) l=L,r=R;
			if(l==r) return t[p]=a[id[l]],void();
			build(ls,l,mid,a,id),build(rs,mid+1,r,a,id);
			pushup(p);
		}
		void modify(int p,int l,int r,int s,int e,int v)
		{
			if(p==1) l=L,r=R;
			if(l>=s&&r<=e&&t[p]>1) return lz[p]+=v,t[p]+=v,void();
			if(l==r)
			{
				if(t[p]>1) return;
				cur.emplace_back(id[l]);
				t[p]=INF;return;
			}pushdown(p);
			if(mid>=s) modify(ls,l,mid,s,e,v);
			if(mid<e) modify(rs,mid+1,r,s,e,v);
			pushup(p);
		}
		#undef ls
		#undef rs
		#undef mid
		#undef pushup
		#undef pushdown
	} sgt;
	inline void init(int l,int r,int a[])
	{
		sgt.init(l,r);
		sgt.build(1,0,0,a,id);
	}
	inline void add(int u,int v) { e[u].emplace_back(v),e[v].emplace_back(u); }
	inline void dfs1(int u,int ff)
	{
		fa[u]=ff,si[u]=1,dep[u]=dep[ff]+1;int t=lst[s[u]];
		if(a[u]) nxt[t].emplace_back(u),lst[s[u]]=u;
		for(auto v:e[u])
		{
			if(v==ff) continue;
			dfs1(v,u);si[u]+=si[v];
			if(si[son[u]]<si[v]) son[u]=v;
		}lst[s[u]]=t;
	}
	inline void dfs2(int u,int topf)
	{
		top[u]=topf,dfn[u]=++cnt,id[cnt]=u;
		if(son[u]) dfs2(son[u],topf);
		for(auto v:e[u])
		{
			if(v==fa[u]||v==son[u]) continue;
			dfs2(v,v);
		}
	}
	inline int LCA(int x,int y)
	{
		while(top[x]!=top[y])
		{
			if(dep[top[x]]<dep[top[y]]) swap(x,y);
			x=fa[top[x]];
		}
		return dep[x]<dep[y]?x:y;
	}
	inline void modify(int x,int y,int w)
	{
		while(top[x]!=top[y])
		{
			if(dep[top[x]]<dep[top[y]]) swap(x,y);
			sgt.modify(1,0,0,dfn[top[x]],dfn[x],w);
			x=fa[top[x]];
		}
		if(dep[x]>dep[y]) swap(x,y);
		sgt.modify(1,0,0,dfn[x],dfn[y],w);
	}
	inline int query(int x,int y)
	{
		int res=0;
		while(top[x]!=top[y])
		{
			if(dep[top[x]]<dep[top[y]]) swap(x,y);
			res+=tt.qry(dfn[top[x]],dfn[x]);
			x=fa[top[x]];
		}
		if(dep[x]>dep[y]) swap(x,y);
		return res+tt.qry(dfn[x],dfn[y]);
	}
}
using namespace tree_decomposition_SGT_Point;
inline void solve()
{
    tt.n=n=read();d=read();for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++) s[i]=read();for(int i=1;i<=d;i++) q[i]=read();
    for(int i=1,u;i<n;i++) u=read(),add(u,read());
	dfs1(1,0),dfs2(1,1);init(1,n,a);
	for(auto x:nxt[0]) tt.modify(dfn[x],1);
	for(int i=1;i<=d;i++)
	{
		print(query(1,q[i])),put(' '),modify(1,q[i],-1);
		for(auto s:cur)
		{
			queue<int> q;q.emplace(s);mp[s]=1;
			if(tt.qry(dfn[s],dfn[s])!=1) continue;
			tt.modify(dfn[s],-1);
			while(!q.empty())
			{
				int u=q.front();q.pop();
				if(!mp[u]){tt.modify(dfn[u],1);continue;}
				if(tt.qry(dfn[u],dfn[u])==1) tt.modify(dfn[u],-1);
				for(int v:nxt[u]) q.emplace(v);
			}
		}cur.clear();
	}
}
signed main()
{
    int T=1;
    // T=read();
    while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：1)

来个简单点的做法。

不难发现一个池塘存在（也就是其中有至少一个昆虫）的时间是一个前缀。

考虑怎么把这个前缀求出来，你发现对于一个点可以二分答案，check 形如一个点加子树查，用 dfn 序转化后是点加区间查，对于所有点处理前缀考虑整体二分，每次处理时只传入有用的点（所有操作与查询的端点），区间加差分之后再暴力滚前缀和，由于只传入了有用的点，一层的复杂度是 $O(r-l+R-L)$，所以总的复杂度就是 $O((n+d) \log n)$。

求出这个前缀之后考虑怎么求解静态的答案，你发现是对于一个点 $u$ 而言，如果 $u$ 的祖先中没有与其同色的点，$u$ 就会对子树内所有查询产生贡献，考虑怎么维护出所有产生贡献的 $u$。

直接正着做不好做，考虑倒过来做，现在需要支持加点与维护每一种颜色的极低点（祖先中没有同色的点）。

考虑将一种颜色的所有点的 dfn 序插入一个数据结构里面，加入一个点时先判断这个点有没有被删除，没被删除就算入贡献，并把其子树内所有点用在数据结构中找后继的方式全部找出来删掉，注意如果删掉了算入贡献的点需要把其的贡献也一并删掉，维护对于子树的贡献可以用 dfn 序与树状数组简单维护，而这个数据结构可以手写链表简单实现，于是做到了 $O((n+d) \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int maxn = 2e5+114;
const int maxd = 2e6+114;
int L[maxn],R[maxn],dfncnt,node[maxn];
vector<int> E[maxn];
int tr[maxn];//点加祖先链和 -> 子树加点和
int b[maxn],s[maxn],h[maxd];
int tim[maxn];//每个点被删除的时间（在第 tim[i] 次操作后被删除）
int lst[maxn],nxt[maxn];
int head[maxn],cov[maxn];
int vis[maxn];//一个点是否在产生贡献
int answer[maxd];//倒着做 
int n,d;
void dfs(int u,int fa){
	L[u]=++dfncnt;
	node[dfncnt]=u;
	for(int v:E[u]){
		if(v!=fa) dfs(v,u);
	}
	R[u]=dfncnt;
}
int pre[maxn];
int use[maxn];
void solve(int l,int r,vector<int> P,vector<int> Q){
	//P 点集合 Q 询问点集合
	int mid=(l+r)>>1;
	for(int i=l;i<=mid;i++) pre[L[h[i]]]++;
	for(int i=1;i<(int)P.size();i++) pre[P[i]]+=pre[P[i-1]];
	vector<int> Pl,Pr,Ql,Qr;
	for(int x:Q){
		int res=pre[R[x]]-pre[L[x]-1];
		if(b[x]<res) Ql.push_back(x);
		else b[x]-=res,Qr.push_back(x),tim[x]=max(tim[x],mid);
	}
	for(int i=l;i<=mid;i++) use[L[h[i]]]=1;
	for(int x:Ql) use[R[x]]=use[L[x]-1]=1;
	for(int x:P){
		if(use[x]==1){
			Pl.push_back(x);
			use[x]=0;
		}
	}
	for(int i=mid+1;i<=r;i++) use[L[h[i]]]=1;
	for(int x:Qr) use[R[x]]=use[L[x]-1]=1;
	for(int x:P){
		if(use[x]==1){
			Pr.push_back(x);
			use[x]=0;
		}
	}
	for(int x:P) pre[x]=0;
	if(l==r) return ;
	solve(l,mid,Pl,Ql);
	solve(mid+1,r,Pr,Qr);
}
void addseq(int l,int r,int c){
	int u=l;
	while(u<maxn) tr[u]+=c,u+=(u&(-u));
	u=r+1;
	while(u<maxn) tr[u]-=c,u+=(u&(-u));
}
int askseq(int u){
	int res=0;
	while(u>0) res+=tr[u],u-=(u&(-u));
	return res;
}
vector<int> Ins[maxd];
void delet(int u){
	int a=lst[u],b=nxt[u];
	if(a!=0) nxt[a]=b;
	if(b!=0) lst[b]=a;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>d;
	vector<int> P,Q;
	P.push_back(0);
	for(int i=1;i<=n;i++) cin>>b[i],Q.push_back(i),P.push_back(i);
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=d;i++) cin>>h[i];
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		E[u].push_back(v);
		E[v].push_back(u);
	}
	dfs(1,0);
	solve(1,d,P,Q);
	for(int i=1;i<=n;i++) Ins[tim[i]].push_back(i);
	for(int i=1;i<=n;i++){
		if(head[s[node[i]]]!=0){
			lst[i]=head[s[node[i]]];
			nxt[head[s[node[i]]]]=i;
		}
		head[s[node[i]]]=i;
	}
	for(int i=d;i>=1;i--){
		for(int x:Ins[i]){
			if(cov[L[x]]==0){
				//还没被覆盖
				while(nxt[L[x]]!=0&&nxt[L[x]]<=R[x]){
					int y=node[nxt[L[x]]];
					if(vis[y]==1){
						vis[y]=0;
						addseq(L[y],R[y],-1);
					}
					cov[L[y]]=1;
					delet(L[y]);
				}
				vis[x]=1;
				addseq(L[x],R[x],1);
			}
		}
		answer[i]=askseq(L[h[i]]);
	}
	for(int i=1;i<=d;i++) cout<<answer[i]<<' ';
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/P11295)

**题目大意**

> 给定 $n$ 个点的树，第 $i$ 个点上有 $a_i$ 个颜色为 $c_i$ 的球。有 $m$ 个人依次从 $1$ 走到某个点，每个人会在路径上每个 $a_i>0$ 的点取一个球，求每个人最终取走了多少种颜色的球。
>
> 数据范围：$n\le 2\times 10^5,m\le 2\times 10^6$。

**思路分析**

首先对于每种颜色，仅保留深度最小的一个点产生贡献。

那么一个点有贡献，当且仅当他的所有同色祖先都被清空了。

因此我们维护出每个点在什么时候被清空，那么每个点对答案有贡献的时刻是一个区间，且容易算出。

然后离线下来就变成子树加单点查询。

现在只需要求出每个点的清空时刻，相当于查询子树第 $a_u$ 小的操作，直接二分得到答案。

时间复杂度 $\mathcal O(n\log m+m\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5,MAXM=2e6+5;
vector <int> G[MAXN],opr[MAXM];
int n,m,a[MAXN],cl[MAXN],id[MAXM],hd[MAXN],pre[MAXM];
int dcnt,dfn[MAXN],rdn[MAXN],rk[MAXN],bc[MAXN],up[MAXN],ql[MAXN],qr[MAXN];
void dfs(int u,int fz) {
	dfn[u]=++dcnt,up[u]=bc[cl[u]],bc[cl[u]]=u,rk[dcnt]=u;
	for(int v:G[u]) if(v^fz) dfs(v,u);
	rdn[u]=dcnt,bc[cl[u]]=up[u];
}
int rt[MAXN];
struct ZkwSegt {;
	int ct[MAXM*22],ls[MAXM*22],rs[MAXM*22],a[MAXM*22],tot;
	void ins(int u,int l,int r,int q,int &p) {
		ct[p=++tot]=ct[q]+1;
		if(l==r) return ;
		int mid=(l+r)>>1;
		if(u<=mid) rs[p]=rs[q],ins(u,l,mid,ls[q],ls[p]);
		else ls[p]=ls[q],ins(u,mid+1,r,rs[q],rs[p]);
	}
	int qry(int k,int l,int r,int q,int p) {
		if(l==r) return l;
		int mid=(l+r)>>1,sz=ct[ls[p]]-ct[ls[q]];
		if(sz>=k) return qry(k,l,mid,ls[q],ls[p]);
		return qry(k-sz,mid+1,r,rs[q],rs[p]);
	}
}	TR;
struct FenwickTree {
	int tr[MAXN],s;
	void add(int x,int v) { for(;x<=n;x+=x&-x) tr[x]+=v; }
	int qry(int x)  { for(s=0;x;x&=x-1) s+=tr[x]; return s; }
}	FT;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i) cin>>cl[i];
	for(int i=1;i<=m;++i) cin>>id[i],pre[i]=hd[id[i]],hd[id[i]]=i;
	for(int i=1,u,v;i<n;++i) cin>>u>>v,G[u].push_back(v),G[v].push_back(u);
	dfs(1,0);
	for(int i=1;i<=n;++i) {
		rt[i]=rt[i-1];
		for(int x=hd[rk[i]];x;x=pre[x]) TR.ins(x,1,m,rt[i],rt[i]);
	}
	for(int i=1;i<=n;++i) {
		int u=rk[i];
		if(!a[u]) qr[u]=0;
		else if(TR.ct[rt[rdn[u]]]-TR.ct[rt[dfn[u]-1]]<a[u]) qr[u]=m;
		else qr[u]=TR.qry(a[u],1,m,rt[dfn[u]-1],rt[rdn[u]]);
		ql[u]=max(ql[up[u]],qr[up[u]]+1);
		if(ql[u]<=qr[u]) opr[ql[u]].push_back(u),opr[qr[u]+1].push_back(-u);
	}
	for(int i=1;i<=m;++i) {
		for(int x:opr[i]) {
			if(x>0) FT.add(dfn[x],1),FT.add(rdn[x]+1,-1);
			else FT.add(dfn[-x],-1),FT.add(rdn[-x]+1,1);
		}
		cout<<FT.qry(dfn[id[i]])<<" \n"[i==m];
	}
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

~~这几天每天都要写一遍主席树，感觉可以自封“主席树仙人”了。~~

首先，考虑每个节点的虫子会被哪些蜻蜓吃掉，显然可以用主席树求出**能吃到该节点虫子的蜻蜓的最大时间序**，设为 $m_u$。

对于每个节点，设 $t_u = \max_{v \text{ is } u\text{'s ancestor},s_v=s_u} m_v$，则这个节点可以给**落点在子树中**，**时间在 $(t_u,m_u]$ 中的蜻蜓提供新的食用种类**。

发现这个问题是二维偏序，直接扫描线即可。

复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10,MAXM=2e6+10;
int n,q,tot,sze[MAXN],ans[MAXM],b[MAXN],s[MAXN],h[MAXM],dfn[MAXN],lst[MAXN],anc[MAXN],occ[MAXN];
vector<int> G[MAXN];
vector<pair<int,pair<int,int>>> upd[MAXN];
vector<int> qr[MAXN];
void dfs(int u,int f) {
	dfn[u]=++tot,sze[u]=1;
	for(auto v:G[u]) if(v!=f) dfs(v,u),sze[u]+=sze[v];
	return ;
}
void get(int u,int f) {
	anc[u]=occ[s[u]],occ[s[u]]=u;
	if(lst[anc[u]]<lst[u]) upd[dfn[u]].push_back({1,{lst[anc[u]]+1,lst[u]}}),upd[dfn[u]+sze[u]].push_back({-1,{lst[anc[u]]+1,lst[u]}});
	else lst[u]=lst[anc[u]];
	for(auto v:G[u]) if(v!=f) get(v,u);
	occ[s[u]]=anc[u];
	return ;
}
namespace SSGT {
	#define mid (l+r>>1)
	const int MAXK=5e7+10;
	int tot,ls[MAXK],rs[MAXK],cnt[MAXK],rt[MAXN],lim;
	int copy(int u) {return ++tot,ls[tot]=ls[u],rs[tot]=rs[u],cnt[tot]=cnt[u],tot;}
	void update(int &u,int l,int r,int pos) {
		if(u<=lim) u=copy(u);
		cnt[u]++;
		if(l==r) return ;
		if(pos<=mid) update(ls[u],l,mid,pos);
		else update(rs[u],mid+1,r,pos);
		return ;
	}
	int bfind(int u1,int u2,int l,int r,int lim) {
		if(l==r) return l;
		if(cnt[ls[u2]]-cnt[ls[u1]]>=lim) return bfind(ls[u1],ls[u2],l,mid,lim);
		return bfind(rs[u1],rs[u2],mid+1,r,lim-cnt[ls[u2]]+cnt[ls[u1]]);
	}
	void init(void) {
		ffor(i,1,q) qr[dfn[h[i]]].push_back(i);
		ffor(i,1,n) {
			rt[i]=rt[i-1],lim=tot;
			for(auto id:qr[i]) update(rt[i],1,q,id);
		}
		ffor(i,1,n) if(b[i]) lst[i]=bfind(rt[dfn[i]-1],rt[dfn[i]+sze[i]-1],1,q,b[i]);
		return ;
	}
};
int tr[MAXM];
void update(int pos,int v) {
	while(pos<=q) tr[pos]+=v,pos+=pos&-pos;
	return ;	
}
int query(int pos) {
	int ans=0;
	while(pos) ans+=tr[pos],pos-=pos&-pos;
	return ans;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	ffor(i,1,n) cin>>b[i];
	ffor(i,1,n) cin>>s[i];
	ffor(i,1,q) cin>>h[i];
	ffor(i,1,n-1) {
		int u,v;
		cin>>u>>v,G[u].push_back(v),G[v].push_back(u);	
	}
	dfs(1,0);
	SSGT::init();
	get(1,0);
	ffor(i,1,n) {
		for(auto pr:upd[i]) {
			int v=pr.first,l=pr.second.first,r=pr.second.second;
			update(l,v),update(r+1,-v);
		}
		for(auto id:qr[i]) ans[id]=query(id);
	}
	ffor(i,1,q) cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：Svemit (赞：0)

# Sol
首先发现对于每个点，他能贡献到的一个前缀具有单调性，就是对每个 $u$ 查出最早什么时候存在超过 $b_u$ 个蜻蜓到该点子树内，记为 $lim_u$。

想查询某时刻有多少蜻蜓经过了该点，单点加，子树求和即可。

对这个东西套一个整体二分，就求出了所有点的 $lim_u$。

一次查询相当于数一条点到根上的颜色数。

按时间戳倒过来处理，发现要支持的操作有动态激活一个点和查询。

如果一条链上同时出现了两个相同颜色的点，考虑只计算更高的点的贡献。

在激活某个点时，考虑它能否继续产生贡献，也就是他到祖先的链中是否存在一个点满足颜色与他相同，如果没有就激活该点。

直接查询看上去不太好做。直接在预处理 dfs 时处理出根到当前点的链中每个颜色的点被激活的最早时间即可，如果到 $u$ 时，存在颜色与 $u$ 相同的点比 $u$ 更早激活，那么 $u$ 就不需要被激活了。

这个只需要对每个颜色开个 multiset 然后 dfs 扫一遍就好。

现在保证了在激活某个点时他顶上没有相同颜色的点，但是此时还没有解决先激活下方点再激活上方点的问题。

在激活 $u$ 后，可以为 $u$ 的子树中所有点提供 $s_u$ 的贡献，为了避免重复贡献，需要把 $u$ 子树中所有颜色与 $u$ 相同的点的贡献全都删去。

这东西是简单的，只需要对每个颜色开一个 set 存下所有当前该颜色的有贡献的点，删去贡献时一定是删除一段 dfn 序的点。

最后的子树加，单点查是简单的。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, M = 2e6 + 5;

int n, m;
int cnt[N], bel[N], a[M];
vector<int> e[N];
int c[N];
int lim[N];
int dfn[N], siz[N], tim, idfn[N];
multiset<int> ms[M];
set<int> s[M];
bool del[N];
vector<int> Add[M];
int ans[M];

void add(int x, int v) {
	if (!x) return;
	for (; x <= n; x += x & -x) c[x] += v;
}
int query(int x) {
	int res = 0;
	for (; x; x -= x & -x) res += c[x];
	return res;
}
int query(int l, int r) {
	return query(r) - query(l - 1);
}

void dfs1(int u, int fath) {
	dfn[u] = ++ tim, siz[u] = 1, idfn[tim] = u;
	for (auto v : e[u]) if (v != fath) {
		dfs1(v, u);
		siz[u] += siz[v];
	}
}

void solve(int l, int r, vector<int> &Q) {
	if (l == r) {
		for (auto i : Q) lim[i] = l;
		return;
	}
	int mid = (l + r) / 2;
	vector<int> L, R;
	for (int i = l; i <= mid; i ++) add(dfn[a[i]], 1);
	for (auto i : Q) {
		if (query(dfn[i], dfn[i] + siz[i] - 1) >= cnt[i]) L.push_back(i);
		else R.push_back(i);
	}
	solve(mid + 1, r, R);
	for (int i = l; i <= mid; i ++) add(dfn[a[i]], -1);
	solve(l, mid, L);
}

void dfs2(int u, int fath) {
	if (ms[bel[u]].size() && *ms[bel[u]].rbegin() >= lim[u]) del[u] = true;
	ms[bel[u]].insert(lim[u]);
	for (auto v : e[u]) if (v != fath) dfs2(v, u);
	ms[bel[u]].erase(ms[bel[u]].find(lim[u]));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i ++) cin >> cnt[i];
    for (int i = 1; i <= n; i ++) cin >> bel[i];
    for (int i = 1; i <= m; i ++) cin >> a[i];
    for (int i = 1; i < n; i ++) {
    	int u, v;
    	cin >> u >> v;
    	e[u].push_back(v), e[v].push_back(u);
    }
    dfs1(1, 0);
    vector<int> Q;
    for (int i = 1; i <= n; i ++) Q.push_back(i);
    solve(0, m, Q);
	dfs2(1, 0);
	for (int i = 1; i <= n; i ++) c[i] = 0;
	for (int i = 1; i <= n; i ++) if (!del[i]) Add[lim[i]].push_back(i);
	for (int i = m; i >= 1; i --) {
		for (auto u : Add[i]) {
			while (s[bel[u]].size()) {
				auto it = s[bel[u]].lower_bound(dfn[u]);
				if (it == s[bel[u]].end() || *it > dfn[u] + siz[u] - 1) break;
				int v = idfn[*it];
				s[bel[u]].erase(*it);
				add(dfn[v], -1), add(dfn[v] + siz[v], 1);
			}
			s[bel[u]].insert(dfn[u]);
			add(dfn[u], 1), add(dfn[u] + siz[u], -1);
		}
		ans[i] = query(dfn[a[i]]);
	}
	for (int i = 1; i <= m; i ++) cout << ans[i] << " \n"[i == m];

    return 0;
}
```

---

## 作者：Genius_Star (赞：0)

**如果你不想写树剖，可以来看本篇题解。**

首先感谢 [@Hoks](https://www.luogu.com.cn/user/551100) 对我本题思路的启发。

### 思路：

首先考虑求出 $tim_i$ 表示第 $i$ 个池塘里的昆虫全部被抓走的时间，容易发现具有单调性，可以二分；现在问题变为查询 $1 \sim mid$ 的这些操作抓走了 $i$ 号池塘多少只昆虫。

注意到，对于一条由根节点出发的路径 $1 \to u$ 进行路径加，可以树上差分，直接在 $s_u \gets s_u+ 1$；则 $i$ 号点被增加的量就是其子树内所有 $s$ 的和。

故考虑使用主席树，每次单点加；二分的时候查询区间和即可，该部分的时间复杂度为 $O(N \log N \log M)$~~应该可以使用全局平衡二叉树优化至单 log。~~

对于询问，是一条由根节点出发的路径数颜色问题；对于第 $i$ 个点，还需要在 $tim_i + 1$ 这个时间将这个点的颜色清掉。

即现在的问题是：

- 单点删除。

- 由根节点出发的路径数颜色。

~~带修莫队就别想了~~使用树剖加上树套树也是三个 log 的，也是过不去的。

考虑令 $pre_u$ 表示 $u$ 的祖先中离它最近的，颜色相同的点；则询问相当于求 $1 \to u$ 中有多少点的 $pre_u$ 为 $0$。

然后注意到若 $pre_u$ 已经等于 $0$ 了，则它后面一直也是 $0$；故可以对 $u$ 的子树所有点的权值加 $1$；这样询问 $1 \to u$ 中 $pre_u = 0$ 的点的数量就是点 $u$ 的权值。

现在问题是如何快速找到所有 $pre_u = 0$ 的点。

考虑维护一个 $S_u$ 表示满足 $pre_v = u$ 的 $v$ 组成的集合。

设当且要删除点 $u$，考虑进行一个懒标记的处理：

- 若 $pre_u \ne 0$，则不管，只打上一个懒标记。

- 否则 $pre_u = 0$；因为将该点删除了，所以先要将 $u$ 的贡献清除（即子树减去 $1$）；然后进行搜索遍历 $S_u$ 的所有点 $v$：

  - 若 $v$ 已经打了懒标记（即它已经被删除），则 $S_v$ 的所有点的 $pre$ 也会是 $0$；继续向 $S_v$ 搜索。
 
  - 否则 $v$ 还没被删除，令 $pre_v = 0$，将其的贡献算上（子树加）即可。
 
因为每个点最多只会有一次其 $pre$ 值为 $0$ 的时刻，故这样均摊是 $O(N)$ 的；对于子树加，单点查等操作，使用线段树维护。

时间复杂度为 $O(N \log N \log M + (N + Q) \log N)$。

**注意是建立了 $q \le 2 \times 10^6$ 个大小为 $n \le 2 \times 10^5$ 的线段树，空间和平常不太相同，请谨慎开空间。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it = l; it != r; ++it) (*it)=x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1,s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i,l,r) for(register int i = l; i <= r; ++i)
#define _For(i,l,r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10, M = 2e6 + 10; 
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, q, u, v, cnt;
int a[N], rt[M], tim[N], siz[N], dep[N], col[N], qr[M], dfn[N], pre[N], fa[N], id[N];
stack<int> S[N];
bool f[N];
vector<int> E[N], T[M];
inline void add(int u, int v){
	E[u].push_back(v);
	E[v].push_back(u);
}
inline void dfs(int u, int f){
	siz[u] = 1;
	pre[u] = (S[col[u]].empty() ? 0 : S[col[u]].top());
	dfn[u] = ++cnt;
	id[cnt] = u;
	S[col[u]].push(u);
	for(auto v : E[u]){
		if(v == f)
		  continue;
		fa[v] = u;
		dep[v] = dep[u] + 1;
		dfs(v, u);
		siz[u] += siz[v];
	}
	S[col[u]].pop();
}
namespace Seg{
	int cnt = 0;
	struct Node{
		int lson, rson;
		int sum;
	}X[N << 8];
	inline void newnode(int &k){
		X[++cnt] = X[k];
		k = cnt;
	} 
	inline void pushup(int k){
		X[k].sum = X[X[k].lson].sum + X[X[k].rson].sum;
	}
	inline void update(int &k, int l, int r, int i, int v){
		newnode(k);
		if(l == i && i == r){
			X[k].sum += v;
			return ;
		}
		int mid = (l + r) >> 1;
		if(i <= mid)
		  update(X[k].lson, l, mid, i, v);
		else
		  update(X[k].rson, mid + 1, r, i, v);
		pushup(k);
	}
	inline int query(int k, int l, int r, int ql, int qr){
		if(!k)
		  return 0;
		if(l == ql && qr == r)
		  return X[k].sum;
		int mid = (l + r) >> 1;
		if(qr <= mid)
		  return query(X[k].lson, l, mid, ql, qr);
		else if(ql > mid)
		  return query(X[k].rson, mid + 1, r, ql, qr);
		else
		  return query(X[k].lson, l, mid, ql, mid) + query(X[k].rson, mid + 1, r, mid + 1, qr);
	}
};
namespace Tree{
	int tag[N << 2];
	inline void update(int k, int l, int r, int ql, int qr, int v){
		if(ql <= l && r <= qr){
			tag[k] += v;
			return ;
		}
		int mid = (l + r) >> 1;
		if(ql <= mid)
		  update(k << 1, l, mid, ql, qr, v);
		if(qr > mid)
		  update(k << 1 | 1, mid + 1, r, ql, qr, v);
	}
	inline int query(int k, int l, int r, int i){
		int sum = tag[k];
		if(l == r)
		  return sum;
		int mid = (l + r) >> 1;
		if(i <= mid)
		  sum += query(k << 1, l, mid, i);
		else
		  sum += query(k << 1 | 1, mid + 1, r, i);
		return sum;
	}
};
inline void dfs(int u){
	while(!S[u].empty()){
		int v = S[u].top();
		S[u].pop();
		pre[v] = 0;
		if(!f[v])
		  Tree::update(1, 1, n, dfn[v], dfn[v] + siz[v] - 1, 1);
		else
		  dfs(v);
	}
}
inline void del(int u){
	f[u] = 1;
	if(!pre[u]){
		Tree::update(1, 1, n, dfn[u], dfn[u] + siz[u] - 1, -1);
		dfs(u);
	}
}
bool End;
int main(){
	n = read(), q = read();
	for(int i = 1; i <= n; ++i)
	  a[i] = read();
	for(int i = 1; i <= n; ++i)
	  col[i] = read();
	for(int i = 1; i <= q; ++i)
	  qr[i] = read();
	for(int i = 1; i < n; ++i){
		u = read(), v = read();
		add(u, v);
	}
	dfs(1, 1);
	for(int i = 1; i <= q; ++i){
		rt[i] = rt[i - 1];
		Seg::update(rt[i], 1, n, dfn[qr[i]], 1);
	}
	for(int i = 1; i <= n; ++i){
		tim[i] = q;
		int l = 0, r = q;
		while(l <= r){
			int mid = (l + r) >> 1;
			if(Seg::query(rt[mid], 1, n, dfn[i], dfn[i] + siz[i] - 1) >= a[i]){
				tim[i] = mid;
				r = mid - 1;
			}
			else
			  l = mid + 1;
		}
		T[tim[i] + 1].push_back(i);
	}
	for(int i = 1; i <= n; ++i){
		if(!pre[i])
		  Tree::update(1, 1, n, dfn[i], dfn[i] + siz[i] - 1, 1);
		else
		  S[pre[i]].push(i);
	}
	for(int i = 1; i <= q; ++i){
		for(auto u : T[i])
		  del(u);
		write(Tree::query(1, 1, n, dfn[qr[i]]));
		putchar(' ');
	}
//	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

