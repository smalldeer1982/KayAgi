# Duff in the Army

## 题目描述

Duff 是一个军队中的一名士兵。Malek 是她的上司。

他们在一个名为 Andarz Gu 的国家里，这个国家有 $n$ 个城市，分别编号 $1\sim n$。有 $n-1$ 条双向通行的道路联通整个国家。

一共有 $m$ 个人居住在这个国家中的一些城市里，每一个人有他的身份号（第 $i$ 个人的身份号是 $i$）。注意，有可能有多个人居住在同一个城市，也有可能有些城市无人居住。

Malek 喜欢对别人下命令，所以他让 Duff 回答他的 $q$ 个提问，每一个提问包含三个数 $v,u$ 和 $a$，表示：设一共有 $x$ 个人居住在从城市 $u$ 到城市 $v$（包含断点）的路径上，他们的身份号从小到大排序后分别是 $p_1,p_2,...,p_x$，设 $k=min(x,a)$，那么 Duff 应该按顺序告诉 Malek $k,p_1,p_2,...,p_k$。换句话说，Malek 想要知道在路径上身份编号前 $a$ 小的人（或者更少，如果这条路上总共居住的人少于 $a$ 个）。

Duff 现在非常忙碌，所以她让你来帮助她回答 Malek 的提问。

## 样例 #1

### 输入

```
5 4 5
1 3
1 2
1 4
4 5
2 1 4 3
4 5 6
1 5 2
5 5 10
2 3 3
5 3 1
```

### 输出

```
1 3
2 2 3
0
3 1 2 4
1 2
```

# 题解

## 作者：zeroy0410 (赞：10)

#### 题目
有n个城市，由n-1条边连接。两个城市之间的道路是唯一的。 
有m个人，住在这n个城市中，现在给出m个人，生活的城市编号。 
你需要回答，从一个城市u到另一个城市v的路径中，编号前a小的人的编号是哪些？

#### 思路1（树上倍增）
树上倍增，可以开一个$num[i][j]$,表示i这个点向前跳$2^j-1$格后到达的点，这样，对于两个点而言，就可以向上跳跃，直到交汇为止，答案则是归并后的ans数组。

此题的切入点主要在$a<=10$这个条件，这样使我们每个vector只要保存最多10个元素就好了。

倍增这种数据结构，是树上问题求解的常用途径，遇到树的问题要优先考虑。

#### 代码
```c++
#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,m,q,fa[M][20],dep[M],top[M],sz[M],son[M];
vector<int>G[M];
vector<int>cty[M];
vector<int>num[M][20];//倍增保存城市往上爬 
vector<int>ans;
vector<int> up(vector<int>&b,vector<int>&c){
	int i=0,j=0;
	vector<int>a;
	a.clear();
	while(i<b.size()&&j<c.size()&&a.size()<10){
		if(b[i]<c[j])a.push_back(b[i++]);
		else a.push_back(c[j++]);
	}
	while(i<b.size()&&a.size()<10)a.push_back(b[i++]);
	while(j<c.size()&&a.size()<10)a.push_back(c[j++]);
	return a;
}
void dfs(int x,int f,int d){
	dep[x]=d;
	fa[x][0]=f;fa[x][1]=fa[f][0];
	num[x][0]=cty[x];num[x][1]=up(cty[x],cty[f]);
	for(int i=0;i<G[x].size();i++){
		int u=G[x][i];
		if(u==f)continue;
		dfs(u,x,d+1);
	}
} 
int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);	
	}
	for(int i=1,a;i<=m;i++){
		scanf("%d",&a);
		cty[a].push_back(i);//已经自动有序 
	} 
	dfs(1,0,1);
	for(int j=2;j<=19;j++)
		for(int i=1;i<=n;i++){
			fa[i][j]=fa[fa[i][j-1]][j-1]; 
			num[i][j]=up(num[i][j-1],num[fa[i][j-1]][j-1]);
		}
	for(int i=1,u,v,a;i<=q;i++){
		scanf("%d%d%d",&u,&v,&a);
		ans.clear();
		if(dep[u]>dep[v])swap(u,v);
		int step=dep[v]-dep[u];
		for(int i=19;i>=0;i--)
			if(step&1<<i)ans=up(ans,num[v][i]),v=fa[v][i];
		if(u==v){
			ans=up(ans,num[v][0]);
			goto e;
		}
		for(int i=19;i>=0;i--){
			if(fa[u][i]!=fa[v][i]){
				ans=up(num[u][i],ans);
				ans=up(num[v][i],ans);
				u=fa[u][i];
				v=fa[v][i];
			}
		}
		ans=up(ans,num[u][0]);
		if(u!=v)ans=up(ans,num[v][1]);
		e:;
		int len=ans.size();
		len=min(len,a);
		printf("%d",len);
		for(int i=0;i<len;i++)
			printf(" %d",ans[i]);
		puts("");
	}
	return 0;
} 
```

#### 思路2（树链剖分）
从树剖的角度看，这就是一道裸题。

我们按轻重链破树成链，利用归并树，记录l,r区间内的前10个元素，最后查找一下就好了，对于树链剖分不是很熟悉的同学，可以看一下洛谷日报的[一篇文章](https://www.luogu.org/blog/communist/shu-lian-pou-fen-yang-xie)

还要注意的是这题迷之卡vector，czj大佬考场上就是因为这个没能AK，（tql），所以封装了一下。

```c++
#include<bits/stdc++.h>
#define M 100005
#define faa tree[p]
#define lsn tree[p<<1]
#define rsn tree[p<<1|1]
using namespace std;
struct arr{
	int Q[10],len;
	int size(){
		return len;
	}
	void push_back(int x){
		Q[len++]=x;
	}
	void clear(){
		for(int i=0;i<10;i++)
			Q[i]=0;
		len=0;
	}
};
int n,m,q;
//树链剖分 
vector<int>G[M];
vector<int>cty[M];
int son[M],sz[M],dep[M],ID[M],fa[M],ln[M],tt=0,top[M];
arr ans;
void dfs(int x,int f,int d){
	dep[x]=d;fa[x]=f;sz[x]=1;son[x]=0;
	for(int i=0;i<G[x].size();i++){
		int u=G[x][i];
		if(u==f)continue;
		dfs(u,x,d+1); 
		if(sz[u]>sz[son[x]])son[x]=u;
		sz[x]+=sz[u];
	}
}
void dfs_top(int x,int tp){
	top[x]=tp;ID[x]=++tt;ln[tt]=x;
	if(son[x])dfs_top(son[x],tp);
	for(int i=0;i<G[x].size();i++){
		int u=G[x][i];
		if(u==son[x]||u==fa[x])continue;
		dfs_top(u,u);
	}
}
struct node{
	int l,r;
	arr num;
}tree[M<<2];
arr up(arr &B,arr &C){
	arr A;
	A.clear();
	int i=0,j=0;
	while(i<B.size()&&j<C.size()&&A.size()<10){
		if(B.Q[i]<C.Q[j])A.push_back(B.Q[i++]);
		else A.push_back(C.Q[j++]);
	}
	while(i<B.size()&&A.size()<10)A.push_back(B.Q[i++]);
	while(j<C.size()&&A.size()<10)A.push_back(C.Q[j++]);
	return A;
}
void build(int l,int r,int p){
	tree[p].l=l;tree[p].r=r;tree[p].num.clear();
	if(l==r){
		for(int i=0;i<cty[ln[l]].size();i++){
			tree[p].num.push_back(cty[ln[l]][i]);
			if(tree[p].num.size()==10)break;
		}
	}
	else {
		int mid=l+r>>1;
		build(l,mid,p<<1);
		build(mid+1,r,p<<1|1);
		tree[p].num=up(tree[p<<1].num,tree[p<<1|1].num);
	}
}
void query(int l,int r,int p){
	if(tree[p].l==l&&tree[p].r==r){
		ans=up(ans,tree[p].num);
	}
	else {
		int mid=tree[p].l+tree[p].r>>1;
		if(r<=mid)query(l,r,p<<1);
		else if(l>mid)query(l,r,p<<1|1);
		else{
			query(l,mid,p<<1);
			query(mid+1,r,p<<1|1);
		}
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for(int i=1,a;i<=m;i++){
		scanf("%d",&a);
		cty[a].push_back(i);
	}
	dfs(1,0,1);
	dfs_top(1,1);
	build(1,n,1);
	for(int i=1,u,v,c;i<=q;i++){
		scanf("%d%d%d",&u,&v,&c);
		ans.clear();
		while(top[u]!=top[v]){
			if(dep[top[u]]>dep[top[v]]){
				query(ID[top[u]],ID[u],1);
				u=fa[top[u]];
			}
			else {
				query(ID[top[v]],ID[v],1);
				v=fa[top[v]];
			}
		} 
		if(dep[u]>dep[v])query(ID[v],ID[u],1);
		else query(ID[u],ID[v],1);
		int len=ans.size();
		len=min(len,c);
		printf("%d",len);
		for(int i=0;i<len;i++)
			printf(" %d",ans.Q[i]);
		puts("");
	}
	return 0;
}
```




---

## 作者：Max_QAQ (赞：4)

**思路：**

看到查询的是树上的两点之间路径的上前 $k$ 小的值。

所以可以考虑用树链剖分。~~（感觉这个题还能再强化一点，加个求子树的。）~~

既然要用树链剖分的话，就得来个线段树，那我们就要想想如何对线段树进行维护。

看到题目的范围 $1 \leqslant a \leqslant 10$ ，也就是说顶多查前 $10$ 小的值。

那我们在维护线段树时，每次只需要维护前 $10$ 小就行了。

没有修改所以不用考虑 pushdown 只需要在建线段树时 pushup 就行了。

那么 pushup 时我们把左右儿子分别的前 $10$ 小的值都记录下来，然后再对这些数进行排序。

再来考虑查询，查询时也是一样，把查询区间前 $10$ 小的值记录下来，再进行排序。

那么这样我们的返回值就需要是一个序列了，因此可以使用结构体进行返回。

**注意：**

每个城市可能会住很多人，可能会超过 $10$ 个所以要用 vector 进行存储，又因为范围的限制，所以在建树时可以将其排序后用结构体转存，这样可以减小常数。

贴个代码。

```cpp

#include<bits/stdc++.h>
#define lson rt<<1
#define rson rt<<1|1
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
inline void write(int x){
	static int sta[35];int top=0;
	if(x<0) putchar('-'),x=-x;
	do{sta[++top]=x%10,x/=10;}while(x);
	while(top) putchar(sta[top--]+'0');
	return putchar(' '),void();
}
inline void chkmax(int &x,int y){return x=(x>y)?x:y,void();}
inline void chkmin(int &x,int y){return x=(x<y)?x:y,void();}
int n,m,q,cnt;
int id[100010];
int head[100010],ver[200010],to[200010],tot;
int fa[100010],son[100010],siz[100010],dep[100010],top[100010];
struct JY{//定义结构体
	int a[21],siz;
	inline void init(){siz=0;}//初始化，在查询的时候需要对返回数组进行初始化否则会           RE
	inline void push_back(int x){a[++siz]=x;}//插入值
	inline bool empty(){return (siz==0);}//判断是否为空
	inline void so(){sort(a+1,a+1+siz);}//排序
	inline void print(){for(int i=1;i<=siz;i++) printf("%d ",a[i]);printf("\n");}//调试用的
};
JY qu;
vector<int> a[100010],b[100010];//存储城市信息
struct SegmentTree{//线段树
	JY a;
	inline void qs(){a.so();}
}st[100010*4];
inline void add(int x,int y){
	ver[++tot]=y;
	to[tot]=head[x];
	head[x]=tot;
}
void dfs1(int x,int fath,int depth){//树剖两件套
	int maxson=-1;
	fa[x]=fath;dep[x]=depth;siz[x]=1;
	for(int i=head[x];i;i=to[i]){
		int y=ver[i];
		if(y==fath) continue;
		dfs1(y,x,depth+1);
		siz[x]+=siz[y];
		if(siz[y]>maxson) son[x]=y,maxson=siz[y];
	}
}
void dfs2(int x,int topf){//树剖两件套
	id[x]=++cnt;
	b[cnt]=a[x];
	top[x]=topf;
	if(!son[x]) return;
	dfs2(son[x],topf);
	for(int i=head[x];i;i=to[i]){
		int y=ver[i];
		if(y==fa[x]||y==son[x]) continue;
		dfs2(y,y);
	}
}
inline void pushup(int rt){
	for(int i=1;i<=st[lson].a.siz;i++) st[rt].a.push_back(st[lson].a.a[i]);
	for(int i=1;i<=st[rson].a.siz;i++) st[rt].a.push_back(st[rson].a.a[i]);
	st[rt].qs();st[rt].a.siz=min(st[rt].a.siz,10);//为了减小常数，所以取一下 min
}
void build(int rt,int l,int r){//建树
	if(l==r){
		int cnt=1;
		sort(b[l].begin(),b[l].end());//顶多查 10 个值，所以后面的可以直接舍弃
		for(vector<int>::iterator iter=b[l].begin();iter!=b[l].end()&&cnt<=10;cnt++,iter++) st[rt].a.push_back(*iter);
		return ;
	}
	int mid=(l+r)>>1;
	build(lson,l,mid);
	build(rson,mid+1,r);
	pushup(rt);
}
JY query(int rt,int l,int r,int L,int R,int k){//普通的查询
	if(L<=l&&r<=R){
		return st[rt].a;
	}
	int mid=(l+r)>>1;
	JY res,temp;res.init();
	if(L<=mid){
		temp=query(lson,l,mid,L,R,k);
		for(int i=1;i<=temp.siz;i++) res.push_back(temp.a[i]);
	}
	if(R>mid){
		temp=query(rson,mid+1,r,L,R,k);
		for(int i=1;i<=temp.siz;i++) res.push_back(temp.a[i]);
	}
	res.so();res.siz=min(res.siz,k);//同 pushup
	return res;
}
JY qRange(int x,int y,int k){//树上查值
	JY ans,temp;ans.init();
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		temp=query(1,1,n,id[top[x]],id[x],k);
		x=fa[top[x]];
		for(int i=1;i<=temp.siz;i++) ans.push_back(temp.a[i]);
		ans.so();ans.siz=min(ans.siz,k);
	}
	if(dep[x]>dep[y]) swap(x,y);
	temp=query(1,1,n,id[x],id[y],k);
	for(int i=1;i<=temp.siz;i++) ans.push_back(temp.a[i]);
	ans.so();ans.siz=min(ans.siz,k);
	return ans;
}
signed main(){
	n=read(),m=read(),q=read();
	for(int i=1,x,y;i<n;i++){
		x=read(),y=read();
		add(x,y);add(y,x);
	}
	for(int i=1;i<=m;i++) a[read()].push_back(i);
	dfs1(1,0,1);dfs2(1,1);
	build(1,1,n);
	for(int i=1,x,y,k;i<=q;i++){
		x=read(),y=read(),k=read();
		qu=qRange(x,y,k);
		write(qu.siz);
		for(int i=1;i<=qu.siz;i++) write(qu.a[i]);
		putchar('\n');
	}
	return 0;//拜拜~~~
}

```

---

## 作者：qwaszx (赞：4)

普及一下静态树链问题的正确树剖做法?

很多初学树剖的人不管问题是静态还是动态都会往上套一个数据结构，这就使得复杂度变成两个$\log$.然而事实上可以预处理出每个点到其链顶这条链上的信息，这样前面的跳链就变成一个$\log$，只需要在最后一段不完整的链上用一个数据结构维护，这部分也是一个$\log$.

当然应该还是没有写得好一点的主席树跑得快.$rk1$的主席树跑得飞快，原理不明emmm可能是封装的问题吧

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=5e5;
struct Node
{
    int w[12],s;
    Node operator +(const Node &a)const
    {
        Node t;t.s=min(s+a.s,10);
        for(int k=1,i=1,j=1;k<=t.s;k++)
            t.w[k]=(j>a.s||(i<=s&&w[i]<a.w[j]))?w[i++]:a.w[j++];
        return t;
    }
};
int dfs_cnt,id[N],tmp[12],n,m,q,mm,to[N],dep[N],ts[N],tw[N][12],a[N][12],s[N],fst[N],nxt[N],son[N],size[N],f[N],tp[N];
struct Segmenttree
{
    Node a[N];
    void build(int rot,int lt,int rt)
    {
        if(lt==rt)
        {
            a[rot].s=ts[lt];
            for(int i=1;i<=ts[lt];i++)a[rot].w[i]=tw[lt][i];
            return;
        }
        int mid=(lt+rt)>>1;
        build(rot<<1,lt,mid),build(rot<<1|1,mid+1,rt);
        a[rot]=a[rot<<1]+a[rot<<1|1];
    }
    Node query(int rot,int lt,int rt,int lq,int rq)
    {
        if(lt>=lq&&rt<=rq)return a[rot];
        int mid=(lt+rt)>>1;
        if(rq<=mid)return query(rot<<1,lt,mid,lq,rq);
        else if(lq>mid)return query(rot<<1|1,mid+1,rt,lq,rq);
        else return query(rot<<1,lt,mid,lq,mid)+query(rot<<1|1,mid+1,rt,mid+1,rq);
    }
}seg;
void ade(int u,int v){to[++mm]=v,nxt[mm]=fst[u],fst[u]=mm;}
void dfs1(int u,int fa)
{
    size[u]=1,f[u]=fa,dep[u]=dep[fa]+1;int mx=0;
    for(int i=fst[u];i;i=nxt[i])
    {
        int v=to[i];if(v==fa)continue;
        dfs1(v,u),size[u]+=size[v];if(size[v]>mx)mx=size[v],son[u]=v;
    }
}
void merge(int a[],int b[],int su,int &sv,int lim)
{
    int cnt=sv+su;if(cnt>lim)cnt=lim;
    for(int k=1,i=1,j=1;k<=cnt;k++)
        tmp[k]=((a[i]<b[j]&&i<=su)||j>sv)?a[i++]:b[j++];
    sv=cnt;for(int i=1;i<=cnt;i++)b[i]=tmp[i];
}
void dfs2(int u,int top)
{
    tp[u]=top;id[u]=++dfs_cnt;
    ts[dfs_cnt]=s[u];for(int i=1;i<=s[u];i++)tw[dfs_cnt][i]=a[u][i];
    if(u!=top)merge(a[f[u]],a[u],s[f[u]],s[u],10);//并上它父亲的信息
    if(son[u])dfs2(son[u],top);
    for(int i=fst[u];i;i=nxt[i])
    {
        int v=to[i];if(v==f[u]||v==son[u])continue;
        dfs2(v,v);
    }
}
void query(int u,int v,int k)
{
    int ans[12],anss=0;
    while(tp[u]!=tp[v])
    {
        if(dep[tp[u]]<dep[tp[v]])swap(u,v);
        merge(a[u],ans,s[u],anss,k);
        u=f[tp[u]];
    }
    if(dep[u]<dep[v])swap(u,v);
    Node t=seg.query(1,1,n,id[v],id[u]);
    merge(t.w,ans,t.s,anss,k);
    printf("%d ",anss);
    for(int i=1;i<=anss;i++)printf("%d ",ans[i]);puts("");
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1,u,v;i<n;i++)scanf("%d%d",&u,&v),ade(u,v),ade(v,u);
    for(int i=1,x;i<=m;i++)
    {
        scanf("%d",&x);
        if(s[x]<=10)a[x][++s[x]]=i;
    }
    dfs1(1,0),dfs2(1,1);seg.build(1,1,n);
    for(int i=1;i<=q;i++)
    {
        int u,v,k;
        scanf("%d%d%d",&u,&v,&k);
        query(u,v,k);
    }
}


---

## 作者：Resurgammm (赞：3)

> 求树上两点间路径的前 $k$ 小值。

考虑树链剖分，那么重点在线段树维护什么。

看这个 $k\leq 10$，所以可以开一个 vector  暴力记录前 $10$ 小即可。

写 pushup 时将左儿子和右儿子 vector 里的值都记录下来，排序一下取前 $10$ 小即可。

查询同理，记得每跳链时都要排序 $+$ 取前 $10$ 小，否则会因为数组越界而 RE。

$\text{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout)
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		if(x<0) putchar('-'),x=-x;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(y,x,sizeof(x))
	
	const int maxn=1e5+5;
	
	int n,m,q;
	vector<int> a[maxn],b[maxn];
	struct node{
		int a[25],size;
		node(){fill(a,0); size=0;}
		inline void push_back(int x){a[++size]=x;}
		inline void Sort(){sort(a+1,a+1+size);}
	};	
	namespace Graph{
		int head[maxn],id;
		struct e{int v,next;}edge[maxn<<1];
		inline void add(int u,int v){
			edge[++id].v=v;
			edge[id].next=head[u];
			head[u]=id;
		}
	}using namespace Graph;
	namespace SegmentTree{
		#define lson p<<1
		#define rson p<<1|1
		node t[maxn<<2];
		inline void pushup(int p){
			for(int i=1;i<=t[lson].size;i++) t[p].push_back(t[lson].a[i]);
			for(int i=1;i<=t[rson].size;i++) t[p].push_back(t[rson].a[i]);
			t[p].Sort(); t[p].size=min(t[p].size,10);
		}
		void build(int p,int l,int r){
			if(l==r){
				sort(b[l].begin(),b[l].end());
				for(int i=0,j=1;i<b[l].size() && j<=10;i++,j++) t[p].push_back(b[l][i]);
				return;
			}
			int mid=(l+r)>>1;
			build(lson,l,mid); build(rson,mid+1,r);
			pushup(p);
		}
		node query(int p,int l,int r,int tl,int tr){
			if(tl<=l && r<=tr) return t[p];
			int mid=(l+r)>>1;
			node res;
			if(tl<=mid){
				node tmp=query(lson,l,mid,tl,tr);
				for(int i=1;i<=tmp.size;i++) res.push_back(tmp.a[i]);
			}
			if(tr>mid){
				node tmp=query(rson,mid+1,r,tl,tr);
				for(int i=1;i<=tmp.size;i++) res.push_back(tmp.a[i]);
			}
			res.Sort(); res.size=min(res.size,10);
			return res;
		}
	}using namespace SegmentTree;
	namespace TreeChain{
		int dep[maxn],size[maxn],f[maxn],son[maxn],top[maxn],dfn[maxn],tim;
		void dfs1(int u,int fa){
			f[u]=fa; size[u]=1;
			dep[u]=dep[fa]+1;
			for(int i=head[u];i;i=edge[i].next){
				int v=edge[i].v;
				if(v==fa) continue;
				dfs1(v,u);
				size[u]+=size[v];
				if(size[v]>size[son[u]]) son[u]=v;
			}
		}
		void dfs2(int u,int topf){
			top[u]=topf;
			dfn[u]=++tim; b[tim]=a[u];
			if(!son[u]) return;
			dfs2(son[u],topf);
			for(int i=head[u];i;i=edge[i].next){
				int v=edge[i].v;
				if(v==f[u] || v==son[u]) continue;
				dfs2(v,v);
			}
		}
		node qrange(int x,int y){
			node res;
			while(top[x]!=top[y]){
				if(dep[top[x]]<dep[top[y]]) swap(x,y);
				node tmp=query(1,1,n,dfn[top[x]],dfn[x]);
				for(int i=1;i<=tmp.size;i++) res.push_back(tmp.a[i]);
				res.Sort(); res.size=min(res.size,10);
				x=f[top[x]];
			}
			if(dep[x]>dep[y]) swap(x,y);
			node tmp=query(1,1,n,dfn[x],dfn[y]);
			for(int i=1;i<=tmp.size;i++) res.push_back(tmp.a[i]);
			res.Sort(); res.size=min(res.size,10);
			return res;
		}
	}using namespace TreeChain;
	
	inline int main(){
		n=read(); m=read(); q=read();
		for(int i=1;i<n;i++){
			int x=read(),y=read();
			add(x,y); add(y,x);
		}
		for(int i=1;i<=m;i++) a[read()].push_back(i);
		dfs1(1,0); dfs2(1,1); build(1,1,n);
		while(q--){
			int u=read(),v=read(),x=read();
			node res=qrange(u,v);
			printf("%d ",min(res.size,x));
			for(int i=1;i<=min(res.size,x);i++) printf("%d ",res.a[i]);
			puts("");
		}
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：dsjkafdsaf (赞：2)

## 题目描述

有`n`个城市，由`n-1`条边连接。两个城市之间的道路是唯一的。

有`m`个人，住在这`n`个城市中，现在给出`m`个人，生活的城市编号。

你需要回答，从一个城市`u`到另一个城市`v`的路径中，编号前`a`小的人的编号是哪些？ 

## Input

第一行3个整数`n,m,q` 

接下里`n-1`行，表示连接两个城市的一条边。

接下来一行`m`个数，表示编号为`i`的人生活在`c[i]`城市 

接下来`q`行，每行`3`个整数`v,u,a`表示一个询问。

## Output

对于每个询问，如果路径上有`t`个人，则先输出`k=min(a,t)`。再输出前`k`小的编号。 具体格式见样例

## Sample Input
```
5 4 5
1 3
1 2
1 4
4 5
2 1 4 3
4 5 6
1 5 2
5 5 10
2 3 3
5 3 1
```
## Sample Output
```
1 3
2 2 3
0
3 1 2 4
1 2
```
其实就是暴力。。。。

让我们来想一下，每个城市只要存编号前`10`的编号，寻找答案的话，进行排序，查询`u`到`lca(u,v),lca(u,v)`到`v`的路径，暴力求解，最坏时间复杂度`O(10*q*n^2)`

粗略的想，大体思路是没什么更好的写法了（我太弱了。。。），只能优化暴力了；

怎样优化呢?只要将时间复杂度降一个`log(n)`就行了，从而想到利用倍增来储存路径，`lca`的同时进行路径的归并，利用归并的思想和倍增的思想来优化时间复杂度；

`f[i][j]`为`lca`的倍增数组,`F[i][j]`为路径的倍增数组。
## 代码如下
```cpp
#include<bits./stdc++.h>
using namespace std;
const int M=1e5+5;
int n,m,q,a,b,u,v,sz,L[M][15],f[M][25],F[M][25][15],dep[M],ans[15];
vector<int>T[M];
void dfs(int x,int fa) {
	dep[x]=dep[f[x][0]=fa]+1;
	F[x][0][0]=(sz=L[fa][0]);
	for(int i=1; i<=sz; i++)F[x][0][i]=L[fa][i];
	for(int i=0; i<(int)T[x].size(); i++) {
		int y=T[x][i];
		if(y==fa)continue;
		dfs(y,x);
	}
}
void merge(int a[15],int b[15],int (&c)[15]) {
	int t[15],a1=1,b1=1,t1=0;
	while(a1<=a[0]&&b1<=b[0]&&t1<10) {
		if(a[a1]<b[b1])t[++t1]=a[a1++];
		else t[++t1]=b[b1++];
	}
	while(a1<=a[0]&&t1<10)t[++t1]=a[a1++];
	while(b1<=b[0]&&t1<10)t[++t1]=b[b1++];
	for(int i=1; i<=(c[0]=t1); i++)c[i]=t[i];
}
void LCA(int x,int y) {
	int X=x,Y=y;
	ans[0]=0;
	if(dep[x]<dep[y])swap(x,y);
	int step=dep[x]-dep[y];
	for(int i=20; i>=0; i--)if(step&(1<<i))merge(ans,F[x][i],ans),x=f[x][i];
	if(x==y) {
		if(dep[X]>dep[Y])merge(ans,L[X],ans);
		else merge(ans,L[Y],ans);
		return;
	}
	for(int i=20; i>=0; i--)
		if(f[x][i]!=f[y][i]) {
			merge(ans,F[x][i],ans);
			merge(ans,F[y][i],ans);
			x=f[x][i],y=f[y][i];
		}
	merge(ans,F[x][0],ans);
	merge(ans,L[X],ans);
	merge(ans,L[Y],ans);
}
int main() {
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1; i<n; i++)scanf("%d%d",&a,&b),T[a].push_back(b),T[b].push_back(a);
	for(int i=1; i<=m; i++) {
		scanf("%d",&a);
		if(L[a][0]<10)L[a][++L[a][0]]=i;
	}
	dfs(1,0);
	for(int i=1; i<=20; i++)
		for(int j=1; j<=n; j++) {
			f[j][i]=f[f[j][i-1]][i-1];
			merge(F[j][i-1],F[f[j][i-1]][i-1],F[j][i]);
		}
	for(int i=1; i<=q; i++) {
		scanf("%d%d%d",&v,&u,&a);
		LCA(v,u);
		printf("%d",min(a,ans[0]));
		for(int j=1; j<=min(a,ans[0]); j++)printf(" %d",ans[j]);
		puts("");
	}
}
```

---

## 作者：MeowScore (赞：1)

本题解使用树剖+线段树。

下面说的“数字”指的是题目里人的身份号。

线段树每个节点自然是维护区间内前 $10$ 小的数字，如果总共不到 $10$ 个数字那就全部维护进来。方便合并，还要维护一下区间中有多少个数字。合并区间信息的话就是把两个待合并的区间里前十小的数字分别全部取出放在一起，从小到大排序，拿走前 $10$ 个（不到 $10$ 个数字那就全拿走）就是合并后的答案。

区间前十小一定来自于左、右区间各自的前十小，所以是维护十个。

由于树上每个点可能有好多人，所以需要用 vector 存一下，还要记录一下时间戳对应的树上点编号，建立线段树的时候到了叶子节点，从 vector 里把这个时间戳对应的树上的点里面的人的身份号都拿出来排序，取前 $10$ 小（同理，不到 $10$ 个数字那就全拿走）。

查询的时候，常规树剖写法。线段树的话定义 void 类型会比较好写（吧），开一个全局数组，每次查询一段完整区间就把这段区间和这个数组进行合并，合并规则和上文类似。

然后就做掉了 qwq。

如果有什么不清楚的地方或是题解的哪里有误，欢迎私信交流问题！

代码：

```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int ss=0,ww=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			ww=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ss=ss*10+ch-'0';
		ch=getchar();
	}
	return ss*ww;
}
const int N=100010;
int cnt,head[N],nex[N*2],to[N*2];
void add(int x,int y){
	cnt++;
	to[cnt]=y;
	nex[cnt]=head[x];
	head[x]=cnt;
}
vector<int> p[N];
int fa[N],dfn[N],dep[N],tp[N],sz[N],son[N],tot;
int t[N];//t[i]表示时间戳i对应的树上的点的编号 
void dfs1(int x,int f){
	fa[x]=f;
	dep[x]=dep[f]+1;
	sz[x]=1;
	int maxn=-1;
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==f)
			continue;
		dfs1(y,x);
		sz[x]+=sz[y];
		if(sz[y]>maxn){
			maxn=sz[y];
			son[x]=y;
		}
	}
}
void dfs2(int x,int top){
	tp[x]=top;
	tot++;
	dfn[x]=tot;
	t[tot]=x;
	if(son[x])
		dfs2(son[x],top);
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==fa[x]||y==son[x])
			continue;
		dfs2(y,y);
	}
}
struct ST{
	int sum;//区间内的数字个数 
	int a[11];//区间内前10小的数字（当然是有序存放的） 
}st[N*4];
int d[N];//合并两段区间时，用来盛放两段全部数字的数组 
int cmp(int x,int y){
	return x<y;
}
int min(int x,int y){
	if(x>=y)
		return y;
	return x;
}
void update(int root,int l,int r){
	st[root].sum=st[root*2].sum+st[root*2+1].sum;
	int nw=0;
	for(int i=1;i<=min(st[root*2].sum,10);i++){//取出左边前10小的数字，不到十个那就全拿（下面的注释就不说的这么严谨了，可能直接说“10个”） 
		nw++;
		d[nw]=st[root*2].a[i];
	}
	for(int i=1;i<=min(st[root*2+1].sum,10);i++){//右边的 
		nw++;
		d[nw]=st[root*2+1].a[i];
	}
	sort(d+1,d+nw+1,cmp);
	for(int i=1;i<=min(st[root].sum,10);i++)//拿走10个 
		st[root].a[i]=d[i];
}
void build(int root,int l,int r){
	if(l==r){
		int s=p[t[l]].size();
		st[root].sum=s;
		for(int i=0;i<s;i++)
			d[i+1]=p[t[l]][i];
		sort(d+1,d+s+1,cmp);
		for(int i=1;i<=min(10,s);i++)
			st[root].a[i]=d[i];
		return;
	}
	int mid=(l+r)/2;
	build(root*2,l,mid);
	build(root*2+1,mid+1,r);
	update(root,l,r);
}
int ans[11];//记录当前合并的答案的全局数组 
int ans_size; 
void ask(int root,int l,int r,int x,int y){
	if(l>=x&&r<=y){
		int nw=0;
		for(int i=1;i<=min(10,st[root].sum);i++){//拿走当前区间前10小的数字 
			nw++;
			d[nw]=st[root].a[i];
		}
		for(int i=1;i<=ans_size;i++){//把当前已经合并的答案拿出来 
			nw++;
			d[nw]=ans[i];
		}
		sort(d+1,d+nw+1,cmp);
		ans_size=0;
		for(int i=1;i<=min(10,nw);i++){//排好序，再取走前10小 
			ans_size++;
			ans[ans_size]=d[i];
		}
		return;
	}
	int mid=(l+r)/2;
	if(mid>=x)
		ask(root*2,l,mid,x,y);
	if(mid+1<=y)
		ask(root*2+1,mid+1,r,x,y);
}
int main(){
	int n,m,q;
	n=read();
	m=read();
	q=read();
	for(int i=1;i<n;i++){
		int x,y;
		x=read();
		y=read();
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=m;i++){
		int x;
		x=read();
		p[x].push_back(i);
	}
	dfs1(1,1);
	dfs2(1,1);
	build(1,1,n);
	for(int i=1;i<=q;i++){
		int x,y,z;
		x=read();
		y=read();
		z=read();
		ans_size=0;
		while(tp[x]!=tp[y]){
			if(dep[tp[x]]<dep[tp[y]])
				swap(x,y);
			ask(1,1,n,dfn[tp[x]],dfn[x]);
			int nw=0;
			x=fa[tp[x]];
		}
		if(dep[x]>dep[y])
			swap(x,y);
		ask(1,1,n,dfn[x],dfn[y]);
		printf("%d ",min(z,ans_size));
		for(int j=1;j<=min(ans_size,z);j++)
			printf("%d ",ans[j]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Night_Bringer (赞：1)

# 前言
[博客园食用更佳](https://www.cnblogs.com/C202202chenkelin/p/14676438.html)
# 题意
$n$ 个城市，构成一棵树。给定 $m$ 个人生活在的城市，输入时的 $A_i$ 表示编号为 $i$ 的人居住的城市。 有 $q$ 次询问，给定两个城市，求两个城市的路径中，编号前 $a$ 小的人的编号并输出。
# 思路
树上倍增。

可以将 $u$ 到 $v$ 的路径分为三个部分：
1. 从 $u$ 到 $lca$ 但不包含 $lca$的路径。
2. 从 $v$ 到 $lca$ 但不包含 $lca$的路径。
3. $lca$ 这个点

所以先预处理出 $dis[i][j][k]$ ： $i$ 向上跳 $2^j-1$ 部第 $k$ 小的值。由于查询的 $a\leq10$ ，所以预处理出前 $10$ 小的即可。

预处理代码：
```cpp
for(int i = 1; i <= n; i++)
	for(int j = 1; j <= 10; j++) dis[i][0][j] = w[i][j];
for(int j = 1; j <= 30; j++)
	for(int i = 1; i <= n; i++) {
		fa[i][j] = fa[fa[i][j - 1]][j - 1];
		for(int k = 1; k <= 10; k++) dis[i][j][k] = dis[fa[i][j - 1]][j - 1][k];
		for(int k = 1; k <= 10; k++) dis[i][j][k + 10] = dis[i][j - 1][k];
		sort(dis[i][j] + 1, dis[i][j] + 1 + 20);
	}
```
查询分三部分，其实也跟普通的树上求简单路径的距离差不多。

先求出 $lca$ ，再用 $u$ 和 $v$ 倍增分别向上爬即可。记得最后在算上 $lca$ 。

时间复杂度 $O(30n\log n)$ ，$30$ 是因为 $10\times \log 10\approx30$。
# Code
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
namespace Quick_Function {
	template <typename Temp> void Read(Temp &x) {
		x = 0; char ch = getchar(); bool op = 0;
		while(ch < '0' || ch > '9') { if(ch == '-') op = 1; ch = getchar(); }
		while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
		if(op) x = -x;
	}
	template <typename T, typename... Args> void Read(T &t, Args &... args) { Read(t); Read(args...); }
	template <typename Temp> Temp Max(Temp x, Temp y) { return x > y ? x : y; }
	template <typename Temp> Temp Min(Temp x, Temp y) { return x < y ? x : y; }
	template <typename Temp> Temp Abs(Temp x) { return x < 0 ? (-x) : x; }
	template <typename Temp> void Swap(Temp &x, Temp &y) { x ^= y ^= x ^= y; }
}
using namespace Quick_Function;
#define INF 0x3f3f3f3f
const int MAXN = 1e5 + 5;
struct Edge { int Next, To; };
Edge edge[MAXN << 1];
int head[MAXN], edgetot = 1;
void Addedge(int u, int v) {
	edge[++edgetot].Next = head[u], edge[edgetot].To = v, head[u] = edgetot;
	edge[++edgetot].Next = head[v], edge[edgetot].To = u, head[v] = edgetot;
}
int w[MAXN][21];
int n, m, q, a;
int dep[MAXN], fa[MAXN][31], dis[MAXN][31][21];
int res1[21], res2[21];
int Get_Lca(int x, int y) {
	if(dep[x] < dep[y]) Swap(x, y);
	for(int i = 30; i >= 0; i--)
		if(dep[x] - (1 << i) >= dep[y]) x = fa[x][i];
	if(x == y) return x;
	for(int i = 30; i >= 0; i--)
		if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}
void dfs(int u, int step) {
	dep[u] = step;
	for(int i = head[u]; i; i = edge[i].Next) {
		int v = edge[i].To;
		if(v != fa[u][0]) {
			fa[v][0] = u;
			dfs(v, step + 1);
		}
	}
}
void Upclimb1(int x, int y) {
	memset(res1, 0x3f, sizeof(res1));
	for(int i = 30; i >= 0; i--)
		if(dep[x] - (1 << i) >= dep[y]) {
			for(int k = 1; k <= 10; k++) res1[k + 10] = dis[x][i][k];
			sort(res1 + 1, res1 + 1 + 20);
			x = fa[x][i];
		}
}
void Upclimb2(int x, int y) {
	memset(res2, 0x3f, sizeof(res2));
	for(int i = 30; i >= 0; i--)
		if(dep[x] - (1 << i) >= dep[y]) {
			for(int k = 1; k <= 10; k++) res2[k + 10] = dis[x][i][k];
			sort(res2 + 1, res2 + 1 + 20);
			x = fa[x][i];
		}
}
void Query(int x, int y) {
	int ans = 0;
	int lca = Get_Lca(x, y);
	if(lca == x) {
		Upclimb1(y, x);
		for(int i = 1; i <= 10; i++) res1[i + 10] = w[x][i];
		sort(res1 + 1, res1 + 1 + 20);
		for(int i = 1; i <= a; i++)
			if(res1[i] != INF) ans++;
		printf("%d ", ans);
		for(int i = 1; i <= a; i++)
			if(res1[i] != INF) printf("%d ", res1[i]);
		return;
	}
	if(lca == y) {
		Swap(x, y);
		Upclimb1(y, x);
		for(int i = 1; i <= 10; i++) res1[i + 10] = w[x][i];
		sort(res1 + 1, res1 + 1 + 20);
		for(int i = 1; i <= a; i++)
			if(res1[i] != INF) ans++;
		printf("%d ", ans);
		for(int i = 1; i <= a; i++)
			if(res1[i] != INF) printf("%d ", res1[i]);
		return;
	}
	Upclimb1(x, lca);
	Upclimb2(y, lca);
	for(int i = 1; i <= 10; i++) res1[i + 10] = res2[i];
	sort(res1 + 1, res1 + 1 + 20);
	for(int i = 1; i <= 10; i++) res1[i + 10] = w[lca][i];
	sort(res1 + 1, res1 + 1 + 20);
	for(int i = 1; i <= a; i++)
		if(res1[i] != INF) ans++;
	printf("%d ", ans);
	for(int i = 1; i <= a; i++)
		if(res1[i] != INF) printf("%d ", res1[i]);
}
int main() {
	memset(w, 0x3f, sizeof(w));
	memset(dis, 0x3f, sizeof(dis));
	Read(n, m, q);
	for(int i = 1, u, v; i < n; i++)
		Read(u, v), Addedge(u, v);
	for(int i = 1, a; i <= m; i++) {
		Read(a);
		w[a][11] = i;
		sort(w[a] + 1, w[a] + 1 + 11);
	}
	dfs(1, 0);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= 10; j++) dis[i][0][j] = w[i][j];
	for(int j = 1; j <= 30; j++)
		for(int i = 1; i <= n; i++) {
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
			for(int k = 1; k <= 10; k++) dis[i][j][k] = dis[fa[i][j - 1]][j - 1][k];
			for(int k = 1; k <= 10; k++) dis[i][j][k + 10] = dis[i][j - 1][k];
			sort(dis[i][j] + 1, dis[i][j] + 1 + 20);
		}
	int u, v;
	while(q--) {
		Read(u, v, a);
		Query(u, v);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Styx (赞：1)

很明显的一道主席树啊  
为什么都要用树链剖分呢qwq

建出每个点的线段树，记录权值为他到根(随便钦点的)的所有点的人的身份号，然后用差分的思路还原出整条路径的线段树，直接查询第$k$小就可以了

大常数代码大概也就400ms左右

代码如下:
```cpp
#include<bits/stdc++.h>
#define lson tr[now].l
#define rson tr[now].r
using namespace std;

struct tree
{
    int l,r,sum;
}tr[5000050];

int n,m,q,cnt,rt[100010],fa[100010][18],deep[100010];
vector<int> g[100010],op[100010];
int N=100001;

int push_up(int now)
{
	tr[now].sum=tr[lson].sum+tr[rson].sum;
}

int insert(int &now,int f,int l,int r,int pos)
{
	now=++cnt;
	if(l==r)
	{
		tr[now].sum=tr[f].sum+1;
		return 0;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
	{
		insert(lson,tr[f].l,l,mid,pos);
		rson=tr[f].r;
	}
	else
	{
		lson=tr[f].l;
		insert(rson,tr[f].r,mid+1,r,pos);
	}
	push_up(now);
}

int query(int a1,int a2,int a3,int a4,int l,int r,int k)
{
	if(l==r) return l;
	int sz=tr[tr[a1].l].sum+tr[tr[a2].l].sum-tr[tr[a3].l].sum-tr[tr[a4].l].sum;
	int mid=(l+r)>>1;
	if(sz>=k)
	{
		return query(tr[a1].l,tr[a2].l,tr[a3].l,tr[a4].l,l,mid,k);
	}
	else
	{
		return query(tr[a1].r,tr[a2].r,tr[a3].r,tr[a4].r,mid+1,r,k-sz);
	}
}

int dfs(int now,int f,int dep)
{
	fa[now][0]=f;
	deep[now]=dep;
	for(int i=1;i<=17;i++)
	{
		fa[now][i]=fa[fa[now][i-1]][i-1];
	}
	for(int i=0;i<g[now].size();i++)
	{
		if(g[now][i]==f) continue;
		dfs(g[now][i],now,dep+1);
	}
}

int lca(int x,int y)
{
	if(deep[y]>deep[x]) swap(x,y);
	for(int i=17;i>=0;i--)
	{
		if(deep[fa[x][i]]>=deep[y]) x=fa[x][i];
	}
	if(x==y) return x;
	for(int i=17;i>=0;i--)
	{
		if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	}
	return fa[x][0];
}

int dfs2(int now,int f)
{
	if(op[now].size()==0) rt[now]=++cnt,tr[rt[now]].l=tr[rt[f]].l,tr[rt[now]].r=tr[rt[f]].r,push_up(rt[now]);
	else insert(rt[now],rt[f],1,N,op[now][0]);
	for(int i=1;i<op[now].size();i++)
	{
		insert(rt[now],rt[now],1,N,op[now][i]);
	}
	for(int i=0;i<g[now].size();i++)
	{
		if(g[now][i]==f) continue;
		dfs2(g[now][i],now);
	}
}

int print(int now)
{
	printf("%d ",tr[now].sum);
	if(lson) print(lson);
	if(rson) print(rson);
}

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    int from,to,val;
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&from,&to);
        g[from].push_back(to);
        g[to].push_back(from);
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&to);
        op[to].push_back(i);
    }
    dfs(1,0,1);
    dfs2(1,0);
    while(q--)
    {
    	scanf("%d%d%d",&from,&to,&val);
    	int anc=lca(from,to);
    	int fan=fa[anc][0];
    	int sz=tr[rt[from]].sum+tr[rt[to]].sum-tr[rt[anc]].sum-tr[rt[fan]].sum;
    	val=min(sz,val);
    	printf("%d ",val);
    	for(int i=1;i<=val;i++)
    	{
    		printf("%d ",query(rt[from],rt[to],rt[anc],rt[fan],1,N,i));
		}
    	puts("");
	}
}
```

---

## 作者：未来姚班zyl (赞：0)

## 题目大意

在一棵树上住着若干个居民，编号 $1\sim m$，若干次询问，求路径上编号前 $a$ 大的居民。

## 题目分析

注意到 $a\le 10$，可以直接套树上主席树。由于树上一个节点可能有多个值，我们要多开两个变量记录主席树的左右节点是否已经新建。复杂度 $O(an\log n)$，轻松通过此题。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L xd[x].l
#define R xd[x].r
#define mid (l+r>>1LL)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =1e5+5,M=2e6+5,inf=(1LL<<31)-1;
const ll llf=1e18,mod=1e9+7;
const ui base=13331;
using namespace std;
int n=read(),m=read(),q=read(),h[N],to[N<<1],nxt[N<<1],cnt,top[N],f[N],dep[N],siz[N],son[N],dfn[N],Time,Id[N],root[N];
inline void add(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;
} 
vector<int>p[N];
struct seg{
	int l,r,w;
	bool fl,fr;
}xd[N*60];
int tot;
inline int build(int &x,int l,int r){
	x++;
	if(l==r)return x;
	int now=x;
	xd[now].l=build(x,l,mid),xd[now].r=build(x,mid+1,r);
	return now;
}
inline void getup(int x){
	xd[x].w=xd[L].w+xd[R].w;
}
inline void modify(int x,int l,int r,int p){
	if(l==r)return xd[x].w++,void();
	if(p<=mid){
		if(xd[x].fl)xd[++tot]=xd[L],L=tot,xd[x].fl=0,xd[L].fl=xd[L].fr=1;
		modify(lc,p);
	}
	else {
		if(xd[x].fr)xd[++tot]=xd[R],R=tot,xd[x].fr=0,xd[R].fl=xd[R].fr=1;
		modify(rc,p);
	}
	getup(x);
}
inline void dfs(int x,int fa){
	f[x]=fa,dep[x]=dep[fa]+1,siz[x]=1;
	e(x)if(y^fa){
		root[y]=++tot;
		xd[tot]=xd[root[x]];
		xd[tot].fl=xd[tot].fr=1;
		for(auto z:p[y])modify(root[y],1,m,z);
		dfs(y,x),siz[x]+=siz[y],son[x]=siz[y]>siz[son[x]]?y:son[x]; 
	}
}
inline void Dfs(int x,int low){
	top[x]=low,dfn[x]=++Time,Id[Time]=x;
	if(son[x])Dfs(son[x],low);
	e(x)if(y^f[x]&&y^son[x])Dfs(y,y);
}
inline int query(int a,int b,int c,int d,int l,int r,int k){
	if(l==r)return l;
	int lk=xd[xd[a].l].w+xd[xd[b].l].w-xd[xd[c].l].w-xd[xd[d].l].w;
	if(lk>=k)return query(xd[a].l,xd[b].l,xd[c].l,xd[d].l,l,mid,k);
	return query(xd[a].r,xd[b].r,xd[c].r,xd[d].r,mid+1,r,k-lk);
}
inline int lca(int x,int y){
	while(top[x]^top[y])dep[top[x]]>dep[top[y]]?x=f[top[x]]:y=f[top[y]];
	return dep[x]<dep[y]?x:y;
}
int main(){
	for(int i=1,x,y;i^n;i++)x=read(),y=read(),add(x,y),add(y,x);
	rep(i,1,m)p[read()].pb(i);
	root[0]=build(tot,1,m);
    root[1]=++tot,xd[tot]=xd[root[0]];
    xd[tot].fl=xd[tot].fr=1;
    for(auto x:p[1])modify(root[1],1,m,x);
	dfs(1,0),Dfs(1,1); 
	for(int i=1,x,y,k,Lca;i<=q;i++){
		x=read(),y=read(),k=read(),Lca=lca(x,y);
		k=min(k,xd[root[x]].w+xd[root[y]].w-xd[root[Lca]].w-xd[root[f[Lca]]].w);
		pf(k),putchar(' ');
		rep(j,1,k)pf(query(root[x],root[y],root[Lca],root[f[Lca]],1,m,j)),putchar(' ');
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Erotate (赞：0)

考虑树上倍增，看到 $a$ 最大只有 $10$，所以我们可以对每个节点开一个 `vector` 来存储编号前 $10$ 小的人。

我们可以在求两个点的 `Lca` 的同时合并答案，预处理的时候顺便把每个点的答案也预处理了。那么，我们只需要暴力把两个节点的前 $10$ 大的答案存到另一个 `vector` 里即可。反正最多 $10$ 次，时间不会炸，代码如下。

```cpp
vector<int>id[N],man[N][20]//这里 id 存的是每个城市里人的编号，man 则是每个节点祖先城市里人的编号。
vector<int> clb(vector<int> a,vector<int> b){
	int i=0,j=0;
	vector<int>c;
	c.clear();
	while(i<a.size() && j<b.size() && c.size()<10){
		if(a[i]<b[j]) c.push_back(a[i++]);
		else c.push_back(b[j++]);
	}
	while(i<a.size() && c.size()<10) c.push_back(a[i++]);
	while(j<b.size() && c.size()<10) c.push_back(b[j++]);
	return c;
}
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	f[u][0]=fa,f[u][1]=f[fa][0];
	man[u][0]=id[u],man[u][1]=clb(id[u],id[fa]);
	for(int i=2;i<=17;++i){
		f[u][i]=f[f[u][i-1]][i-1];
		man[u][i]=clb(man[u][i-1],man[f[u][i-1]][i-1]);
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa) continue;
		dfs(v,u);
	}
}
vector<int> lca(int x,int y){
	vector<int> res;
	if(dep[x]>dep[y]) swap(x,y);
	for(int i=17;i>=0;--i)
		if(dep[f[y][i]]>=dep[x]){
			res=clb(res,man[y][i]);
			y=f[y][i];
		}
	if(x==y) return clb(res,man[x][0]);
	for(int i=17;i>=0;--i)
		if(f[x][i]!=f[y][i]){
			res=clb(res,clb(man[x][i],man[y][i]));
			x=f[x][i],y=f[y][i];
		}
	res=clb(res,man[x][0]);
	if(x!=y) res=clb(res,man[y][1]);
	return res;
}
```


---

## 作者：封禁用户 (赞：0)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF587C)

[CF](https://codeforces.com/problemset/problem/587/C)

### 分析

看到区间第 $a$ 小，想到可持久化线段树。

对于每一个节点，建立包含出根到自己的所有权值的线段树，可以发现每一个节点的信息都是继承其父亲的，因此可以可持久化。

链 $[u,v]$ 的权值信息可以用 $[rt_u - rt_v - rt_{\text{lca}(u,v)} - rt_{father_{\text{lca}(u,v)}}]$ 表示，在该线段树上二分即可。

时间复杂度是 $O(na\log{n})$。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define pii pair<int,int>
#define N 100010
int head[N],nxt[N<<1],to[N<<1],cnt = 0;
inline void add(int u,int v)
{
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
}
vector<int> g[N];
int rt[N],f[N][20],dep[N],sum[N],n,m,q;
struct Tree
{
	#define mid (l+r)/2
	int L[N<<5],R[N<<5],sz[N<<5],times;
	Tree() {times = 0;}
	int update(int u,int v,int l,int r,int x)
	{
		u = ++times;
		L[u] = L[v],R[u] = R[v],sz[u] = sz[v] + 1;
		if(l == r) return u;
		if(x <= mid) L[u] = update(L[u],L[v],l,mid,x);
		else R[u] = update(R[u],R[v],mid+1,r,x);
		return u;
	}
	int query(int u,int v,int t,int w,int l,int r,int x)
	{
		if(l == r) return l;
		int tp = sz[L[u]] + sz[L[v]] - sz[L[t]] - sz[L[w]];
		if(tp >= x) return query(L[u],L[v],L[t],L[w],l,mid,x);
		return query(R[u],R[v],R[t],R[w],mid+1,r,x - tp);
	}
}tree;
void dfs(int u,int fa)
{
	sum[u] = sum[fa] + (int)g[u].size();
	dep[u] = dep[fa] + 1;
	f[u][0] = fa;
	rt[u] = rt[fa];
	for(auto i:g[u]) rt[u] = tree.update(rt[u],rt[u],1,m,i);
	for(register int i = head[u];i;i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs(v,u);
	}
}
inline int lca(int u,int v)
{
	if(dep[u] < dep[v]) swap(u,v);
	D(i,18,0)
		if(dep[f[u][i]] >= dep[v])
			u = f[u][i];
	if(u == v) return u;
	D(i,18,0)
		if(f[u][i] != f[v][i])
			u = f[u][i],v = f[v][i];
	return f[u][0];
}
int main()
{
	read(n),read(m),read(q);
	F(i,1,n-1)
	{
		int u,v;
		read(u),read(v);
		add(u,v);
		add(v,u);
	}
	F(i,1,m)
	{
		int x;
		read(x);
		g[x].push_back(i);
	}
	dfs(1,0);
	F(i,1,18)
		F(j,1,n)
			f[j][i] = f[f[j][i-1]][i-1];
	while(q--)
	{
		int u,v,x,t,w;
		read(u),read(v),read(x);
		t = lca(u,v);
		w = f[t][0];
		x = min(x,sum[u] + sum[v] - sum[t] - sum[w]);
		write(x),putchar(' ');
		F(i,1,x) write(tree.query(rt[u],rt[v],rt[t],rt[w],1,m,i)),putchar(' '); 
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：wrzSama (赞：0)

## 题意

有 $m$ $(1 \le m \le 10^5)$ 个人生活在一棵 $n$ 个节点的树上，他们的编号为 $1 \sim m$。给定 $q$ $(1 \le q \le 10^5)$ 次询问，每次按顺序输出 $2$ 个点间的简单路径上编号前 $k$ $(1 \le k \le 10)$ 小的人的编号（如果这条路径上不满 $k$ 人则按顺序输出所有人的编号）。

## 思路

我们可以对这颗树进行重链剖分，并在线段树上的每个节点用 set 维护该区间内所有节点的编号。因为每个人最多会出现在线段树上 $\log n$ 个节点表示的区间中，所以所有的 set 中最多有 $n \log n$ 个节点。查询路径上编号前 $k$ 小的人时，我们通过树剖找到线段树上所有包含该路径的节点，并依次尝试用 set 中前 $k$ 小的元素更新答案。该算法时间复杂度为 $O(q \log^3 n)$，但实际远远跑不满。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int read_result=0,is_below_0=0;
	char now_ch=0;
	while(!isdigit(now_ch))
	{
		is_below_0|=now_ch=='-';
		now_ch=getchar();
	}
	while(isdigit(now_ch))
	{
		read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);
		now_ch=getchar();
	}
	return is_below_0?-read_result:read_result;
}
inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n,m,q,fa[100005],d[100005],sz[100005],hs[100005],dfn[100005],tot,top[100005],ans[15];
vector<int>tr[100005];
set<int>s[400005];
priority_queue<int>q1;
inline void dfs(int u)
{
	d[u]=d[fa[u]]+1;
	sz[u]=1;
	for(int i=0;i<tr[u].size();++i)
	{
		int v=tr[u][i];
		if(v==fa[u]) continue;
		fa[v]=u;
		dfs(v);
		sz[u]+=sz[v];
		if(sz[v]>sz[hs[u]]) hs[u]=v;
	}
}
inline void dfs1(int u,int x)
{
	top[u]=x;
	dfn[u]=++tot;
	if(hs[u]) dfs1(hs[u],x);
	for(int i=0;i<tr[u].size();++i)
	{
		int v=tr[u][i];
		if(v==fa[u]||v==hs[u]) continue;
		dfs1(v,v);
	}
}
inline int lca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(d[top[x]]>d[top[y]]) x=fa[top[x]];
		else y=fa[top[y]];
	}
	if(d[x]<d[y]) return x;
	return y;
}
inline void update(int o,int l,int r,int x,int k)
{
	s[o].insert(k);
	if(l==r) return;
	int mid=(l+r)>>1;
	if(x<=mid) update(o<<1,l,mid,x,k);
	else update(o<<1|1,mid+1,r,x,k);
}
inline void query(int o,int l,int r,int x,int y,int k)
{
	if(x<=l&&r<=y)
	{
		set<int>::iterator it=s[o].begin();
		while(q1.size()<k)
		{
			if(it==s[o].end()) break;
			q1.push(*it);
			++it;
		}
		if(it==s[o].end()) return;
		while(q1.size()==k&&q1.top()>*it)
		{
			if(it==s[o].end()) break;
			q1.pop();
			q1.push(*it);
			++it;
		}
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) query(o<<1,l,mid,x,y,k);
	if(y>mid) query(o<<1|1,mid+1,r,x,y,k);
}
int main()
{
	n=read();
	m=read();
	q=read();
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read();
		tr[u].push_back(v);
		tr[v].push_back(u);
	}
	dfs(1);
	dfs1(1,1);
	for(int i=1;i<=m;++i) update(1,1,tot,dfn[read()],i);
	while(q--)
	{
		int u=read(),v=read(),a=read(),x=lca(u,v);
		while(top[u]!=top[x])
		{
			query(1,1,tot,dfn[top[u]],dfn[u],a);
			u=fa[top[u]];
		}
		query(1,1,tot,dfn[x],dfn[u],a);
		while(top[v]!=top[x])
		{
			query(1,1,tot,dfn[top[v]],dfn[v],a);
			v=fa[top[v]];
		}
		if(v!=x) query(1,1,tot,dfn[x]+1,dfn[v],a);
		int tmp=0;
		while(q1.size())
		{
			ans[++tmp]=q1.top();
			q1.pop();
		}
		write(tmp);
		for(int i=tmp;i;--i)
		{
			putchar(' ');
			write(ans[i]);
		}
		puts("");
	}
	return 0;
}
```


---

## 作者：Arghariza (赞：0)

首先先把权值挂到点上，发现 $a\le 10$，故可以直接求出这前 $a$ 小数。

### Sol 1

然后就变成了树上查询第 $k$ 小，经典套路，开一棵可持久化权值线段树，原树上每个点维护一个版本，表示其到根上路径上所有点的权值，查询时找到 $lca_{u,v}$ 后差分然后主席树上二分即可，复杂度 $O(an\log n)$。


### Sol 2

你发现这个 $a$ 十分地小，于是可以用线段树维护重链上前 $10$ 小的数 $a_i(i\le 10)$。首先需要使用重链剖分。

然后合并线段树节点的时候，搞两个指针按照归并的思想比较大小，然后加入合并后节点 $a$ 数组的末尾即可，需要注意的是 $len_a\le 10$。

复杂度 $O(an\log^2 a)$。

因为线段树好写，所以写了线段树。

还有一点需要注意，原树上一个点权值可能大于 $10$ 个，取最小 $10$ 个即可。

```cpp
#include <bits/stdc++.h>
namespace mystd {
	inline int read() {
	    char c = getchar();
	    int x = 0, f = 1;
	    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
	    return x * f;
	}
	inline void write(int x) {
	    if (x < 0) x = ~(x - 1), putchar('-');
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

const int maxn = 1e5 + 100;
const int inf = 0x3f3f3f3f;
struct edge { int to, nxt; } e[maxn << 1];
struct seg {
	int cnt, a[15];
	seg () { memset(a, inf, sizeof(a)), cnt = 0; }
	seg operator + (const seg &rhs) const {
		seg res;
		int i = 0, j = 0;
		while (res.cnt <= 10) {
			if (i >= cnt && j >= rhs.cnt) break;
			if (i == cnt || a[i] > rhs.a[j]) res.a[res.cnt] = rhs.a[j], j++, res.cnt++;
			if (i >= cnt && j >= rhs.cnt) break;
			if (j == rhs.cnt || rhs.a[j] >= a[i]) res.a[res.cnt] = a[i], i++, res.cnt++;
		}
		return res;
	}
} tr[maxn << 2];
int n, m, q, tot, cnt, head[maxn];
int sz[maxn], son[maxn], fa[maxn], top[maxn], id[maxn], dep[maxn], pos[maxn];
vector<int> p[maxn];

void add_edge(int u, int v) {
	e[++tot] = (edge) { v, head[u] };
	head[u] = tot;
}

#define ls x << 1
#define rs x << 1 | 1
#define mid ((l + r) >> 1)
void pushup(int x) { tr[x] = tr[ls] + tr[rs]; }
void build(int l, int r, int x) {
	if (l == r) {
		for (int i : p[pos[l]]) {
			tr[x].a[tr[x].cnt++] = i;
			if (tr[x].cnt == 10) break;
		}
		return;
	}
	build(l, mid, ls), build(mid + 1, r, rs), pushup(x);
}

seg query(int l, int r, int s, int t, int x) {
	if (s <= l && r <= t) return tr[x];
	if (s > mid) return query(mid + 1, r, s, t, rs);
	else if (t <= mid) return query(l, mid, s, t, ls);
	else return query(l, mid, s, mid, ls) + query(mid + 1, r, mid + 1, t, rs);
}

void dfs1(int u, int fat) {
	fa[u] = fat, sz[u] = 1, dep[u] = dep[fat] + 1;
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == fat) continue;
		dfs1(v, u), sz[u] += sz[v];
		if (sz[v] > sz[son[u]]) son[u] = v;
	}
}

void dfs2(int u, int pre) {
	top[u] = pre, pos[id[u] = ++cnt] = u;
	if (son[u]) dfs2(son[u], pre);
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	} 
}

seg qrypath(int u, int v) {
	seg res;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		res = res + query(1, n, id[top[u]], id[u], 1);
		u = fa[top[u]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	return res + query(1, n, id[u], id[v], 1);
}

int main() {
	n = read(), m = read(), q = read();
	for (int i = 1, u, v; i <= n - 1; i++) {
		u = read(), v = read();
		add_edge(u, v), add_edge(v, u);
	}
	for (int i = 1; i <= m; i++) p[read()].push_back(i); 
	dfs1(1, 0);
	dfs2(1, 1);
	build(1, n, 1);
	while (q--) {
		int u = read(), v = read(), a = read();
		seg res = qrypath(u, v);
		write(min(res.cnt, a)), putchar(' ');
		for (int i = 0; i < res.cnt && i < a; i++) write(res.a[i]), putchar(' ');
		puts("");
	}
	return 0;
}

```

---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15786350.html)

# 题目大意

给定一棵树，树上每个点有一个权值，又有 $q$ 个询问。

对于每一个询问 `u v rk`，让你求出点 $u$ 与点 $v$ 之间的路径上的点的前 $rk$ 小。

# 题目分析

考虑树上倍增，比较无脑。

我们令 $dis[i][j][k]$ 表示从点 $i$ 向上跳 $2^{j}-1$ 步后第 $k$ 小的值，再用 $w[i][j]$ 存储城市 $i$ 里居住的人，按编号从小到大排序。

初始化时因为从点 $i$ 向上跳 $0(=2^0-1)$ 步后第 $j$ 小就是 $w[i][j]$，所以可以初始化出 $dis$ 数组。

随后用类似于倍增 $\mathbf{LCA}$ 父亲/祖先节点迭代的方法迭代即可，具体如下：

```cpp
for(register int i=1;i<=n;i++)
{
	for(register int j=1;j<=10;j++)
	{
		dis[i][0][j]=w[i][j];
	}
}
	
for(register int j=1;j<=20;j++)
{
	for(register int i=1;i<=n;i++)
   	{
		for(register int k=1;k<=10;k++)
		{
			dis[i][j][k]=dis[fa[i][j-1]][j-1][k];
				
			dis[i][j][k+10]=dis[i][j-1][k];
		}
			
		sort(dis[i][j]+1,dis[i][j]+20+1);
	}
}
```

-----

再来考虑怎么回答询问，不妨设当前询问为 `x y rk`。

令 $lca$ 表示 $x,y$ 的树上最近公共祖先。

将 $res1[~],res2[~]$ 初始化为很大的数。

若 $x=lca$，我们倍增更新 $y\to lca$ 的路径即可，将处理的前 $10$ 小放在 $res1[~]$ 中。

再将 $w[x][i](1\le i\le 10)$ 的值放入 $res1[~]$ 中也来更新，最后数组前 $rk$ 个数中那些不为这个很大的数的数就是答案。

$lca=y$ 和其他情况类似，详见代码。

**注意时时排序！**

# 代码

```cpp
//2022/1/4

//2022/1/5

//2022/1/10

const int INF=0x3f3f3f3f;

const int ma=1e5+5;

struct Gragh
{
	int v;
	
	int nxt;
};

Gragh gra[ma<<1];

int head[ma],dep[ma],res1[21],res2[21];

int fa[ma][21],w[ma][21];

int dis[ma][21][21];
//dis[i][j][k]:i 向上跳 2^{j}-1 步后第 k 小的值 

int n,m,q;

int idx;

inline void add(int u,int v)
{
	gra[++idx].v=v;
	
	gra[idx].nxt=head[u];
	
	head[u]=idx;
}

inline void dfs(int now,int fath,int depth)
{
	fa[now][0]=fath;
	
	dep[now]=depth;
	
	for(register int i=1;i<=20;i++)
	{
		fa[now][i]=fa[fa[now][i-1]][i-1];
	}
	
	for(register int i=head[now];i;i=gra[i].nxt)
	{
		int v=gra[i].v;
		
		if(v!=fath)
		{
			dfs(v,now,depth+1);
		}
	}
}

inline int LCA(int x,int y)
{
	if(dep[x]<dep[y])
	{
		swap(x,y);
	}
	
	for(register int i=20;i>=0;i--)
	{
		if(dep[x]>=dep[y]+(1<<i))
		{
			x=fa[x][i];
		}
	}
	
	if(x==y)
	{
		return x;
	}
	
	for(register int i=20;i>=0;i--)
	{
		if(fa[x][i]!=fa[y][i])
		{
			x=fa[x][i];
			
			y=fa[y][i];
		}
	}
	
	return fa[x][0];
} 

inline void updata1(int x,int y)
{
	mst(res1,0x3f);
	
	for(register int i=20;i>=0;i--)
	{
		if(dep[x]>=dep[y]+(1<<i))
		{
			for(register int j=1;j<=10;j++)
			{
				res1[j+10]=dis[x][i][j];
			}
			
			sort(res1+1,res1+20+1);
			
			x=fa[x][i];
		}
	}
}

inline void updata2(int x,int y)
{
	mst(res2,0x3f);
	
	for(register int i=20;i>=0;i--)
	{
		if(dep[x]>=dep[y]+(1<<i))
		{
			for(register int j=1;j<=10;j++)
			{
				res2[j+10]=dis[x][i][j];
			}
			
			sort(res2+1,res2+20+1);
			
			x=fa[x][i];
		}
	}
}

inline void query(int x,int y,int rk)
{
	int ans=0;
	
	int lca=LCA(x,y);
	
	if(lca==x)
	{
		updata1(y,x);
		
		for(register int i=1;i<=10;i++)
		{
			res1[i+10]=w[x][i];
		}
		
		sort(res1+1,res1+20+1);
		
		for(register int i=1;i<=rk;i++)
		{
			if(res1[i]!=INF)
			{
				ans++;
			}
		}
		
		printf("%d ",ans);
		
		for(register int i=1;i<=rk;i++)
		{
			if(res1[i]!=INF)
			{
				printf("%d ",res1[i]);
			}
		}
		
		enter();
	}
	
	else if(lca==y)
	{
		swap(x,y);
		
		updata1(y,x);
		
		for(register int i=1;i<=10;i++)
		{
			res1[i+10]=w[x][i];
		}
		
		sort(res1+1,res1+20+1);
		
		for(register int i=1;i<=rk;i++)
		{
			if(res1[i]!=INF)
			{
				ans++;
			}
		}
		
		printf("%d ",ans);
		
		for(register int i=1;i<=rk;i++)
		{
			if(res1[i]!=INF)
			{
				printf("%d ",res1[i]);
			}
		}
		
		enter();
	}
	
	else
	{
		updata1(x,lca);
		
		updata2(y,lca);
		
		for(register int i=1;i<=10;i++)
		{
			res1[i+10]=res2[i];
		}
		
		sort(res1+1,res1+20+1);
		
		for(register int i=1;i<=10;i++)
		{
			res1[i+10]=w[lca][i];
		}
		
		sort(res1+1,res1+20+1);
		
		for(register int i=1;i<=rk;i++)
		{
			if(res1[i]!=INF)
			{
				ans++;
			}
		}
		
		printf("%d ",ans);
		
		for(register int i=1;i<=rk;i++)
		{
			if(res1[i]!=INF)
			{
				printf("%d ",res1[i]);
			}
		}
		
		enter();
	}
}

int main(void)
{
	mst(w,0x3f);mst(dis,0x3f);
	
	n=read(),m=read(),q=read();
	
	for(register int i=1;i<n;i++)
	{
		int u=read(),v=read();
		
		add(u,v),add(v,u);
	}
	
	for(register int i=1;i<=m;i++)
	{
		int x=read();
		
		w[x][11]=i;
		
		sort(w[x]+1,w[x]+11+1);
	}
	
	dfs(1,0,1);
	
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=10;j++)
		{
			dis[i][0][j]=w[i][j];
		}
	}
	
	for(register int j=1;j<=20;j++)
	{
		for(register int i=1;i<=n;i++)
		{
			for(register int k=1;k<=10;k++)
			{
				dis[i][j][k]=dis[fa[i][j-1]][j-1][k];
				
				dis[i][j][k+10]=dis[i][j-1][k];
			}
			
			sort(dis[i][j]+1,dis[i][j]+20+1);
		}
	}
	
	while(q--)
	{
		int u=read(),v=read(),rk=read();
		
		query(u,v,rk);
	}
	
	return 0;
}
```

---

## 作者：漠寒 (赞：0)

## 分析

读了下题，立马就想到了主席树，对每个点存一个值域线段树，存储其到根的路径上有哪些点，$x$ 到 $y$ 的路径就是他们线段树合起来再减去两倍 $lca$ 的线段树，再把 $lca$ 本身所含点加上即可。

然后发现每个点就比他爹线段树多含了它本身所含的点（就是那些住它那儿的）。所以主席树就可以轻松处理这个问题了。

需要注意的是，一个城市可能含多个住民，所以在修改线段树的儿子时需要注意是继承上次修改的结果，还是继承它父亲的对应位置。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void read(int &res){
	char c;
	int f=1;
	res=0;
	c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
	res*=f;
}
int n,m,q;
vector<int>v[100005];
int head[100005],tot;
struct edge{
	int to,nex;
}e[200005];
inline void add(int qq,int mm){
	e[++tot].to=mm;
	e[tot].nex=head[qq];
	head[qq]=tot;
}
int root[100005],cnt;
struct node{
	int sum,ls,rs;
}a[2000000];
void build(int &rt,int l,int r){
	if(!rt)rt=++cnt;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(a[rt].ls,l,mid);
	build(a[rt].rs,mid+1,r);
}
void modify(int rt,int rtt,int l,int r,int x){
	if(l==r){
		a[rtt].sum++;
		return;
	}
	int mid=(l+r)>>1;
	if(mid>=x){
		if(a[rtt].ls){//每次修改的时候都要新建一次，要不你会把你爹的东西也改了（改了一个小时） 
			int k=++cnt;
			a[k]=a[a[rtt].ls];
			a[rtt].ls=k;
		}
		else {
			int k=++cnt;
			a[k]=a[a[rt].ls];
			a[rtt].ls=k;
		}
		if(!a[rtt].rs)a[rtt].rs=a[rt].rs;
		modify(a[rt].ls,a[rtt].ls,l,mid,x);
	}
	else {
		if(a[rtt].rs){
			int k=++cnt;
			a[k]=a[a[rtt].rs];
			a[rtt].rs=k;
		}
		else {
			int k=++cnt;
			a[k]=a[a[rt].rs];
			a[rtt].rs=k;
		}
		if(!a[rtt].ls){
			a[rtt].ls=a[rt].ls;
		}
		modify(a[rt].rs,a[rtt].rs,mid+1,r,x);
	}
	a[rtt].sum=a[a[rtt].ls].sum+a[a[rtt].rs].sum;
}
int fa[100005][17],dep[100005];
void dfs(int u,int f){
	fa[u][0]=f;
	dep[u]=dep[f]+1;
	root[u]=++cnt;
	a[root[u]]=a[root[f]];//可能没有居民住这儿，所以先处理一下 
	for(int i=0;i<v[u].size();i++){
		modify(root[f],root[u],1,m,v[u][i]);
	}
	for(int i=head[u];i;i=e[i].nex){
		int vv=e[i].to;
		if(vv==f)continue;
		dfs(vv,u);
	}
}
void init(){//lca倍增写法 
	for(int i=1;i<=16;i++){
		for(int j=1;j<=n;j++){
			fa[j][i]=fa[fa[j][i-1]][i-1];
		}
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=16;i>=0;i--){
		if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
	}
	if(x==y)return x;
	for(int i=16;i>=0;i--){
		if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	}
	return fa[x][0];
}
int query(int rt,int rtt,int rrt,int tr,int l,int r,int k){
	if(l==r)return l;
	int mid=(l+r)>>1,sa=a[a[rt].ls].sum+a[a[rtt].ls].sum-a[a[rrt].ls].sum-a[a[tr].ls].sum;//这应该是主席树最基础的东西吧 
	if(sa>=k)return query(a[rt].ls,a[rtt].ls,a[rrt].ls,a[tr].ls,l,mid,k);
	else return query(a[rt].rs,a[rtt].rs,a[rrt].rs,a[tr].rs,mid+1,r,k-sa);
}
signed main()
{
	read(n);read(m);read(q);
	for(int i=1;i<n;i++){
		int x,y;
		read(x);read(y);
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=m;i++){
		int x;
		read(x);
		v[x].push_back(i);
	}
	build(root[0],1,n);//预处理，好像不写这个也可以 
	dfs(1,0);
	init();
	for(int i=1;i<=q;i++){
		int x,y,aa;
		read(x);read(y);read(aa);
		int gg=lca(x,y);
		int kk=fa[gg][0];
		int ss=a[root[x]].sum+a[root[y]].sum-a[root[kk]].sum-a[root[gg]].sum;
		if(aa>ss)aa=ss;
		printf("%d ",aa);
		for(int j=1;j<=aa;j++){
			printf("%d ",query(root[x],root[y],root[kk],root[gg],1,m,j));
		}
		puts("");
	}
	return 0;
}




```


---

## 作者：AFewSuns (赞：0)

为什么题解都是树剖，倍增啥的，给出一种主席树的做法。

### 题目大意

给你一棵树，每个树上的节点有一些带编号的人，求 $u$ 到 $v$ 的路径上编号前 $k$ 小的人。（$1\leq n,m,q \leq 10^5,1 \leq k \leq 10$）

### 题目分析

题目相当于求路径前 $k$ 大。对于每一个节点 $u$，用线段树维护它到根的路径上有多少个人，并以编号为下标。

在 dfs 的时候直接把 $u$ 接在 $fa$ 的线段树上，像主席树一样维护就行了。

查询 $u$ 到 $v$ 的路径，就相当于是查询 $u$ 的线段树加上 $v$ 的线段树，减去 $lca$ 的线段树，再减去 $fa_{lca}$ 的线段树（容斥一下）。

可是主席树只能查第 $k$ 小，怎么查前 $k$ 小的数呢？

考虑 $1 \leq k \leq 10$，直接暴力遍历输出就行了。

具体来说，现在线段树搜到了一个区间 $[l,r]$，如果这里的数的个数小于等于 $k$，那就直接搜索左右儿子，搜到底之后就输出。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define LC lc[x]
#define RC rc[x]
using namespace std;
vector<ll> v[100010];
ll n,m,q,head[100010],cnt=0;
ll rt[100010],tree[2000020],lc[2000020],rc[2000020],tot=0;
ll f[100010][22],dep[100010];
struct node{
	ll nxt,to;
}e[200020];
void add(ll u,ll v){
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
void build(ll &x,ll l,ll r){
	x=++tot;
	if(l==r) return;
	ll mid=(l+r)>>1;
	build(LC,l,mid);
	build(RC,mid+1,r);
}
void copy(ll x,ll y){
	tree[x]=tree[y];
	LC=lc[y];
	RC=rc[y];
}
void mdf(ll &x,ll y,ll l,ll r,ll pos){
	x=++tot;
	copy(x,y);
	tree[x]++;
	if(l==r) return;
	ll mid=(l+r)>>1;
	if(pos<=mid) mdf(LC,lc[y],l,mid,pos);
	else mdf(RC,rc[y],mid+1,r,pos);
}
void dfs(ll fa,ll u){
	dep[u]=dep[fa]+1;
	f[u][0]=fa;
	for(ll i=1;i<=18;i++) f[u][i]=f[f[u][i-1]][i-1];
	rt[u]=rt[fa];
	for(ll i=0;i<v[u].size();i++) mdf(rt[u],rt[u],1,m,v[u][i]);//建主席树 
	for(ll i=head[u];i;i=e[i].nxt){
		ll v=e[i].to;
		if(v==fa) continue;
		dfs(u,v);
	}
}
ll get_lca(ll x,ll y){//倍增求lca 
	if(dep[x]<dep[y]) swap(x,y);
	for(ll i=18;i>=0;i--) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	for(ll i=18;i>=0;i--){
		if(f[x][i]!=f[y][i]){
			x=f[x][i];
			y=f[y][i];
		}
	}
	return f[x][0];
}
void query(ll a1,ll a2,ll a3,ll a4,ll l,ll r,ll k){
	if((tree[a1]+tree[a2]-tree[a3]-tree[a4])==0) return;//如果没人就直接返回 
	ll mid=(l+r)>>1;
	if((tree[a1]+tree[a2]-tree[a3]-tree[a4])<=k){//如果已经小于等于k个 
		if(l==r){
			printf("%lld ",l);//暴力输出
			return;
		}
		query(lc[a1],lc[a2],lc[a3],lc[a4],l,mid,k);
		query(rc[a1],rc[a2],rc[a3],rc[a4],mid+1,r,k); 
		return;
	}
	ll tmp=tree[lc[a1]]+tree[lc[a2]]-tree[lc[a3]]-tree[lc[a4]];
	query(lc[a1],lc[a2],lc[a3],lc[a4],l,mid,k);//由于是求前k小，而不是第k小，左边是一定要搜的 
	if(tmp<k) query(rc[a1],rc[a2],rc[a3],rc[a4],mid+1,r,k-tmp);//如果左边个数不够再搜右边 
}
int main(){
	scanf("%lld %lld %lld",&n,&m,&q);
	for(ll i=1;i<n;i++){
		ll u,v;
		scanf("%lld %lld",&u,&v);
		add(u,v);
		add(v,u);
	}
	for(ll i=1;i<=m;i++){
		ll x;
		scanf("%lld",&x);
		v[x].push_back(i);//vector存每个点有哪些人 
	}
	build(rt[0],1,m);
	dfs(0,1);
	while(q--){
		ll u,v,a;
		scanf("%lld %lld %lld",&u,&v,&a);
		ll lca=get_lca(u,v);
		ll sum=tree[rt[u]]+tree[rt[v]]-tree[rt[lca]]-tree[rt[f[lca][0]]];//u->v的路径上有多少人 
		a=min(a,sum);//之间取min
		printf("%lld ",a); 
		query(rt[u],rt[v],rt[lca],rt[f[lca][0]],1,m,a);//获取答案 
		printf("\n");
	}
} 
```

---

## 作者：AuCloud (赞：0)

# 树剖+线段树

由于每次询问最多10个，故可以~~暴力~~维护区间前10个编号

线段树pushup和树剖查询的时候把两个节点里的值扔进一个set里然后拿出前10个来就好了（。

以下是核心代码（合并）
```
struct hehe{
    int rk[11];
};
hehe merge(hehe x, hehe y)
{
    hehe ret;
    set<int>se;
    for(int i = 1; i <= 10 && x.rk[i]; i++)
    {
        se.insert(x.rk[i]);
    }
    for(int i = 1; i <= 10 && y.rk[i]; i++)
    {
        se.insert(y.rk[i]);
    }
    int tot = 1;
    for(set<int>::iterator i = se.begin(); i != se.end() && tot <= 10; i++, tot++)
    {
        ret.rk[tot] = *i;
    }
    return ret;
}

```
线段树pushup直接$tr[p] = merge(tr[lson], tr[rson])$

树剖查询每次让ans和查询出的结果merge一下，最后输出ans前十即可



---

## 作者：傅思维666 (赞：0)


## 题解：

还是数据范围能给出更多的提示。

看到这个$a\le 10$，还要输出前k小的都是谁，那么就直接考虑暴力维护前10即可。

然后是路径统计。考虑树上倍增和树链剖分。但是对比一下，倍增对树链的维护更容易理解和好码一些。所以采用了vector维护前十集合+倍增。

唯一需要注意的点就是vector的合并问题。可以考虑类似归并排序的做法，把两个vector合并进一个vector里。

剩下的就是裸的树上倍增了。

代码：

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=1e5+10;
int n,m,q;
int tot,to[maxn<<1],nxt[maxn<<1],head[maxn];
int fa[maxn][20],deep[maxn];
vector<int> c[maxn];
vector<int> set[maxn][20];
vector<int> ans;
void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
vector<int> merge(vector<int> a,vector<int> b)
{
	int i=0,j=0;
	vector<int> ret;
	ret.clear();
	while(i<a.size()&&j<b.size()&&ret.size()<10)
	{
		if(a[i]<b[j])
			ret.push_back(a[i++]);
		else
			ret.push_back(b[j++]);
	}
	while(i<a.size()&&ret.size()<10)
		ret.push_back(a[i++]);
	while(j<b.size()&&ret.size()<10)
		ret.push_back(b[j++]);
	return ret;
}
void dfs(int x,int f)
{
	deep[x]=deep[f]+1;
	fa[x][0]=f;
	set[x][0]=c[x];
	for(int i=1;i<=19;i++)
	{
		fa[x][i]=fa[fa[x][i-1]][i-1];
		set[x][i]=merge(set[x][i-1],set[fa[x][i-1]][i-1]);
	}
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==f)
			continue;
		dfs(y,x);
	}
}
vector<int> solve(int x,int y)
{
	vector<int> ret;
	ret.clear();
	if(deep[x]<deep[y])
		swap(x,y);
	for(int i=19;i>=0;i--)
		if(deep[fa[x][i]]>=deep[y])
		{
			ret=merge(ret,set[x][i]);
			x=fa[x][i];
		}
	if(x==y)
	{
		ret=merge(ret,set[x][0]);
		return ret;
	}
	for(int i=19;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
		{
			ret=merge(ret,set[x][i]);
			ret=merge(ret,set[y][i]);
			x=fa[x][i];
			y=fa[y][i];
		}
	ret=merge(ret,set[x][0]);
	if(x!=y)
		ret=merge(ret,set[y][1]);
	return ret;
}
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=m;i++)
	{
		int x;
		scanf("%d",&x);
		c[x].push_back(i);
	}
	dfs(1,0);
	while(q--)
	{
		int x,y,a;
		scanf("%d%d%d",&x,&y,&a);
		ans.clear();
		ans=solve(x,y);
		int sz=ans.size();
		int k=min(sz,a);
		printf("%d ",k);
		for(int i=0;i<k;i++)
			printf("%d ",ans[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：TheShadow (赞：0)

# 闲扯

这题用倍增做着感觉好麻烦啊，一个是走 $2^k$ 条边，一个是走 $2^k$ 个点，细节上要注意一下。

# 题面

[CF587C Duff in the Army](https://www.luogu.org/problem/CF587C)

# Solution

这道题有一个很关键的性质： $a\leq10$ 。

这是一个很小的值，所以我们可以直接维护。

由于是树上的路径，我们可以考虑用倍增维护。

我们设 $f_{i,j}$ 表示点 $i$ 向上走 $2^k$ 条边后到达的点， $node_{i,j}$ 表示从 $i$ 开始的 $2^j$ 个点的答案。

然后就可以像普通的树上倍增那样做了，在实现细节上需要注意。

# Code

```c++
#include<bits/stdc++.h>
#define del(a,i) memset(a,i,sizeof(a))
#define ll long long
#define inl inline
#define il inl void
#define it inl int
#define ill inl ll
#define re register
#define ri re int
#define rl re ll
#define mid ((l+r)>>1)
#define lowbit(x) (x&(-x))
#define INF 0x3f3f3f3f
using namespace std;
template<class T>il read(T &x){
	int f=1;char k=getchar();x=0;
	for(;k>'9'||k<'0';k=getchar()) if(k=='-') f=-1;
	for(;k>='0'&&k<='9';k=getchar()) x=(x<<3)+(x<<1)+k-'0';
	x*=f;
}
template<class T>il _print(T x){
	if(x/10) _print(x/10);
	putchar(x%10+'0');
}
template<class T>il print(T x){
	if(x<0) putchar('-'),x=-x;
	_print(x);
}
ll mul(ll a,ll b,ll mod){long double c=1.;return (a*b-(ll)(c*a*b/mod)*mod)%mod;}
it qpow(int x,int m,int mod){
	int res=1,bas=x%mod;
	while(m){
		if(m&1) res=(1ll*res*bas)%mod;
		bas=(1ll*bas*bas)%mod,m>>=1;
	}
	return res%mod;
}
const int MAXN = 1e5+5;
int n,m,q,u,v,k,head[MAXN],num_edge,lg2[MAXN];
struct Arr{
	int val[15],len;
	Arr(){del(val,0),len=0;}
	il updata(int a){if(len<10) val[++len]=a;}
}node[MAXN][20];
inl Arr pushup(Arr a,Arr b){
	Arr res;ri i=1,j=1;
	while(i<=a.len&&j<=b.len&&res.len<10){
		if(a.val[i]<b.val[j]) res.val[++res.len]=a.val[i++];
		else res.val[++res.len]=b.val[j++];
	}
    // 为了防止有一个为空（会直接跳出上方循环）
	while(i<=a.len&&res.len<10) res.val[++res.len]=a.val[i++];
	while(j<=b.len&&res.len<10) res.val[++res.len]=b.val[j++];
	return res;
}
struct Edge{
	int next,to;
	Edge(){}
	Edge(int next,int to):next(next),to(to){}
}edge[MAXN<<1];
il add_edge(int u,int v){
	edge[++num_edge]=Edge(head[u],v),head[u]=num_edge;
	edge[++num_edge]=Edge(head[v],u),head[v]=num_edge;
}
int d[MAXN],f[MAXN][20];
il DFS(int u,int fa){
	f[u][0]=fa;
	for(ri i=1;(1<<i)<=d[u];++i) f[u][i]=f[f[u][i-1]][i-1],node[u][i]=pushup(node[u][i-1],node[f[u][i-1]][i-1]);
	for(ri i=head[u];i;i=edge[i].next){
		if(edge[i].to==fa) continue;
		d[edge[i].to]=d[u]+1,DFS(edge[i].to,u);
	}
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(m),read(q);
	for(ri i=2;i<=n;++i) lg2[i]=lg2[i>>1]+1;
	for(ri i=1;i<n;++i) read(u),read(v),add_edge(u,v);
	for(ri i=1;i<=m;++i) read(u),node[u][0].updata(i);
	DFS(1,0);
	for(ri i=1;i<=q;++i){
		read(u),read(v),read(k);
		Arr ans;
		if(d[u]<d[v]) swap(u,v);
		while(d[u]!=d[v]) ans=pushup(ans,node[u][lg2[d[u]-d[v]]]),u=f[u][lg2[d[u]-d[v]]];
		if(u==v){
			ans=pushup(ans,node[v][0]);
			printf("%d ",min(k,ans.len));
			for(ri j=1;j<=min(k,ans.len);++j) printf("%d ",ans.val[j]);puts("");
			continue;
		}
		for(ri s=lg2[d[u]];s>=0;--s)
			if(f[u][s]!=f[v][s]){
				ans=pushup(ans,node[u][s]);
				ans=pushup(ans,node[v][s]);
				u=f[u][s],v=f[v][s];
			}
		ans=pushup(ans,node[u][0]),ans=pushup(ans,node[v][0]),ans=pushup(ans,node[f[u][0]][0]);// 这 3 个点没有统计进来
		printf("%d ",min(k,ans.len));
		for(ri j=1;j<=min(k,ans.len);++j) printf("%d ",ans.val[j]);puts("");
	}
	return 0;
}
```



---

## 作者：ez_lcw (赞：0)

看到题目中$a<=10$，自然就想到用暴力维护这个东东。

设倍增数组$fa[u][i]$和$minn[u][i]$，其中$minn$存的是一个结构体，结构体中包含两个东东：一个数组和这个数组中的元素个数。

$fa[u][i]$表示啥我就不说了，$minn[u][i]$表示从$u$到$fa[u][i]$（即$u$的$i$倍祖先）中前$10$小的值。

合并就暴力合并，每次看哪个小就加哪个，查找就按$lca$的方式查找。

~~说实话挺暴力的~~

最后的代码+注释如下：

```cpp
#include<bits/stdc++.h>
 
#define N 100010
#define A 15
#define K 20
#define INF 0x7fffffff
 
using namespace std;
 
struct data
{
    int tot,num[A];
    void init()
    {
        for(int i=1;i<=11;i++)
            num[i]=INF;
    }
    void add(int x)
    {
        if(tot==10)
            return;
        num[++tot]=x;//为啥add时不用排序？因为主程序中插入时就是有序的
    }
}t[N],minn[N][K],none;
 
int n,m,q;
int cnt,head[N],nxt[N<<1],to[N<<1];
int fa[N][K],d[N];
 
void adde(int u,int v)
{
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
 
data merge(data a,data b,int t=10)//暴力merge
{
    data c=none;
    int x=1,y=1;
    while(x<=a.tot&&y<=b.tot&&c.tot<t)
    {
        if(a.num[x]<b.num[y])c.num[++c.tot]=a.num[x++];
        else c.num[++c.tot]=b.num[y++];
    }
    while(x<=a.tot&&c.tot<t)
        c.num[++c.tot]=a.num[x++];
    while(y<=b.tot&&c.tot<t)
        c.num[++c.tot]=b.num[y++];
    return c;
}
 
void dfs(int u)
{
    for(int i=1;i<=17;i++)//合并倍增数组
    {
        fa[u][i]=fa[fa[u][i-1]][i-1];
        minn[u][i]=merge(minn[u][i-1],minn[fa[u][i-1]][i-1]);
    }
    for(int i=head[u];i;i=nxt[i])
    {
        if(to[i]!=fa[u][0])
        {
            d[to[i]]=d[u]+1;
            fa[to[i]][0]=u;
            minn[to[i]][0]=t[u];
            dfs(to[i]);
        }
    }
}
 
data lca(int a,int b,int x)
{
    data ans=none;
    if(d[a]<d[b])swap(a,b);
    ans=merge(ans,t[a],x);
    for(int i=17;i>=0;i--)
        if(d[a]-(1<<i)>=d[b])
            ans=merge(ans,minn[a][i],x),a=fa[a][i];
    if(a==b)
        return ans;
    ans=merge(ans,t[b],x);
    for(int i=17;i>=0;i--)
    {
        if(fa[a][i]!=fa[b][i])
        {
            ans=merge(ans,merge(minn[a][i],minn[b][i],x),x);
            a=fa[a][i],b=fa[b][i];
        }
    }
    ans=merge(ans,minn[a][0],x);
    return ans;
}
 
int main()
{
    none.init();
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)
        t[i].init();
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        adde(u,v),adde(v,u);
    }
    for(int i=1;i<=m;i++)
    {
        int c;
        scanf("%d",&c);
        t[c].add(i);
    }
    dfs(1);
    while(q--)
    {
        int u,v,a;
        scanf("%d%d%d",&u,&v,&a);
        data t=lca(u,v,a);
        if(t.tot)
        {
            printf("%d ",t.tot);
            for(int i=1;i<=t.tot;i++)
                printf("%d ",t.num[i]);
            puts("");
        }
        else
            puts("0");
    }
    return 0;
}
```


---

