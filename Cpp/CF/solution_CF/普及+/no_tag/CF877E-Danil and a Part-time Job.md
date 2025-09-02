# Danil and a Part-time Job

## 题目描述

Danil decided to earn some money, so he had found a part-time job. The interview have went well, so now he is a light switcher.

Danil works in a rooted tree (undirected connected acyclic graph) with $ n $ vertices, vertex $ 1 $ is the root of the tree. There is a room in each vertex, light can be switched on or off in each room. Danil's duties include switching light in all rooms of the subtree of the vertex. It means that if light is switched on in some room of the subtree, he should switch it off. Otherwise, he should switch it on.

Unfortunately (or fortunately), Danil is very lazy. He knows that his boss is not going to personally check the work. Instead, he will send Danil tasks using Workforces personal messages.

There are two types of tasks:

1. pow v describes a task to switch lights in the subtree of vertex $ v $ .
2. get v describes a task to count the number of rooms in the subtree of $ v $ , in which the light is turned on. Danil should send the answer to his boss using Workforces messages.

A subtree of vertex $ v $ is a set of vertices for which the shortest path from them to the root passes through $ v $ . In particular, the vertex $ v $ is in the subtree of $ v $ .

Danil is not going to perform his duties. He asks you to write a program, which answers the boss instead of him.

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF877E/76e99838c9d4f0aba9dd5ef366e55343e705a02b.png)The tree before the task pow 1.![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF877E/85a6f3926b45c5e1223a87bdba96341efa237d37.png)The tree after the task pow 1.

## 样例 #1

### 输入

```
4
1 1 1
1 0 0 1
9
get 1
get 2
get 3
get 4
pow 1
get 1
get 2
get 3
get 4
```

### 输出

```
2
0
0
1
2
1
1
0
```

# 题解

## 作者：SalomeJLQ (赞：8)

一次过题来写题解。

这题你只需要会：

- 建图
- 存dfs序
- 线段树板子

然后只要能想到，就可以过题了。

$$
\quad
$$

这种东西直接在树上不好快速维护，所以我们想，换做在序列上，我们如何维护？

在数列上用线段树明显很好维护。假设一段区间长度为 $size$，$1$ 的个数为 $val$，则显然反转之后 $1$ 的个数变为了 $size-val$。因此我们只需略改线段树区间修改的延迟标记下传函数即可：

```cpp
void spread(ll p){
	if(t[p].tag){
		t[p<<1].val=t[p<<1].size-t[p<<1].val;
		t[p<<1|1].val=t[p<<1|1].size-t[p<<1|1].val;
		t[p<<1].tag^=1,t[p<<1|1].tag^=1;
		t[p].tag=0;
	}
}
```

思考到这一步这题就做完了一半。另一半是什么？

$$
\quad
$$

我们现在要将树上问题转化到序列上来。我们有一个神奇的方法：搜索。

我们把节点 $u$ 的dfs序拆成前后两部分，第一部分为时间戳 $dfn$，后一部分为回溯时的编号 $out$。我们用 $cnt$ 记录编号，其中第一部分需要 $++$ $cnt$，第二部分不需要。我们再增加一个 $num$ 数组用于记录时间戳为 $cnt$ 的节点。

```cpp
void dfs(ll u,ll fa){
	dfn[u]=++cnt,num[cnt]=u;
	for(ll i=head[u];i;i=edge[i].nxt){
		ll v=edge[i].to;
		if(v==fa)continue;
		dfs(v,u);
	}
	out[u]=cnt;
}
```

这样搜索过后，所得的 $num$ 数组用于在建树时建立起树上节点和序列元素的对应位置，$dfn$ 数组和 $out$ 数组用于记录一个节点的子树在序列上的对应左右端点。

这样我们成功将树上问题放到了序列上来。我们完成了这题的另一半！

$$
\quad
$$

剩下的代码就很好码出来了，和线段树区间修改区间查和板子差不了多少。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read()
{
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int SIZE=200005;
struct Tree{ll l,r,val,size,tag;}t[SIZE*4];
struct Edge{ll to,nxt;}edge[SIZE];
char opt[15];
ll head[SIZE],tot,dfn[SIZE],out[SIZE],cnt,num[SIZE];
inline void add(ll x,ll y)
{
	edge[++tot].to=y,edge[tot].nxt=head[x],head[x]=tot;
}
ll n,m,a[SIZE];

//对树搜索 
void dfs(ll u,ll fa)
{
	dfn[u]=++cnt,num[cnt]=u;
	for(ll i=head[u];i;i=edge[i].nxt)
	{
		ll v=edge[i].to;
		if(v==fa)continue;
		dfs(v,u);
	}
	out[u]=cnt;
}

//下传延迟标记 
void spread(ll p)
{
	if(t[p].tag)
	{
		t[p<<1].val=t[p<<1].size-t[p<<1].val;
		t[p<<1|1].val=t[p<<1|1].size-t[p<<1|1].val;
		t[p<<1].tag^=1,t[p<<1|1].tag^=1;
		t[p].tag=0;
	}
}

//区间修，只要有递归就下传标记 
void change(ll p,ll l,ll r)
{
	if(l<=t[p].l&&r>=t[p].r)
	{
		t[p].val=t[p].size-t[p].val,t[p].tag^=1;
		return;
	}
	spread(p);
	int mid=t[p].l+t[p].r>>1;
	if(l<=mid)change(p<<1,l,r);
	if(r>mid)change(p<<1|1,l,r);
	t[p].val=t[p<<1].val+t[p<<1|1].val;
	t[p].size=t[p<<1].size+t[p<<1|1].size;
}

//区间查，只要有递归就下传标记 
ll ask(ll p,ll l,ll r)
{
	if(l<=t[p].l&&r>=t[p].r)
		return t[p].val;
	spread(p);
	ll mid=t[p].l+t[p].r>>1,ans=0;
	if(l<=mid)ans+=ask(p<<1,l,r);
	if(r>mid)ans+=ask(p<<1|1,l,r);
	return ans;
}

//建树，注意num的映射 
void build(ll p,ll l,ll r)
{
	t[p].l=l,t[p].r=r;
	if(l==r)
	{
		t[p].val=a[num[l]],t[p].size=1;
		return;
	}
	ll mid=l+r>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	t[p].val=t[p<<1].val+t[p<<1|1].val;
	t[p].size=t[p<<1].size+t[p<<1|1].size;
}

int main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		int x=read();
		add(x,i+1);
	}
	for(int i=1;i<=n;i++)a[i]=read();
	dfs(1,1),build(1,1,n),m=read();
	while(m--)
	{
		scanf("%s",&opt);ll x;scanf("%lld",&x);
		if(opt[0]=='g')
			printf("%lld\n",ask(1,dfn[x],out[x]));
		else change(1,dfn[x],out[x]);
	}
	return 0;
}
```

---

## 作者：jun头吉吉 (赞：6)

## 一道板子题
当你$\color{green}{AC}$了[Apple Tree](http://poj.org/problem?id=3321)，[【模板】线段树](https://www.luogu.com.cn/problem/P3372)，你会发现，这就是一个一眼题
### DFS序
按照我们$\texttt{dfs}$的顺序把树上的点标号，根据我们对dfs的了解，我们知道，dfs在搜完一颗树前，是不会往上跳的，因此我们知道

**$x$的子树上的dfs序是连续的，且$x$的dfs序最小**

那么我们就可以把子树操作改变为序列操作，设$dfn[x]$表示x的dfs序，$size[x]$表示x的子树的大小，那么对x的子树操作，就等价于对$dfn[x]\to dfn[x]+size[x]-1$的操作

于是，我们成功的把树上问题转移到了序列上


### 线段树
比较简单的线段树,稍微魔改一下板子就ok了
（具体看代码吧）

```cpp
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){
	    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
	}
	template <typename T>inline void read(T& t){
	    t=0;int f=0;char ch=getc();
	    while (!isdigit(ch)){
	        if(ch=='-')f = 1;
	        ch=getc();
	    }
	    while(isdigit(ch)){
   	    	t=t*10+ch-48;
   	    	ch = getc();
   		}
		if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){
	    read(t);read(args...);
	}
}
namespace out{
	char buffer[1<<21];
	int p1=-1;
	const int p2 = (1<<21)-1;
	inline void flush() {
		fwrite(buffer,1,p1+1,stdout),
		p1=-1;
	}
	inline void putc(const char &x) {
		if(p1==p2)flush();
		buffer[++p1]=x;
	}
	template <typename T>void write(T x) {
		static char buf[15];
		static int len=-1;
		if(x>=0){
			do{
    			buf[++len]=x%10+48,x/=10;
    		}while (x);
		}else{
    		putc('-');
			do {
    			buf[++len]=-(x%10)+48,x/=10;
			}while(x);
		}
		while (len>=0)
			putc(buf[len]),--len;
	}
}
using namespace std;
const int maxn=200000+10;
struct TREE{
	struct node{
		int l,r;
		int tag,val;
	}tree[maxn<<2];
	#define l(x) tree[(x)].l
	#define r(x) tree[(x)].r
	#define mid(x) (tree[(x)].l+tree[(x)].r>>1)
	#define tag(x) tree[(x)].tag
	#define val(x) tree[(x)].val
	#define lson x<<1
	#define rson x<<1|1
	int a[maxn];
	void pushdown(int x){
		if(tag(x)){
			tag(lson)^=1,val(lson)=r(lson)-l(lson)+1-val(lson);
			tag(rson)^=1,val(rson)=r(rson)-l(rson)+1-val(rson);
			tag(x)=0;
		}
	} 
	void pushup(int x){
		val(x)=val(lson)+val(rson);
	}
	void build(int x,int l,int r){
		l(x)=l,r(x)=r;tag(x)=0;
		if(l==r){val(x)=a[l];return;}
		build(lson,l(x),mid(x));
		build(rson,mid(x)+1,r(x));
		pushup(x);
	}
	void change(int x,int l,int r){//将[l,r]取反 
		if(r<l(x)||r(x)<l)return;
		if(l<=l(x)&&r(x)<=r){
			tag(x)^=1;
			val(x)=r(x)-l(x)+1-val(x);
			return;
		}
		pushdown(x);
		change(lson,l,r);
		change(rson,l,r);
		pushup(x);
	}
	int query(int x,int l,int r){
		if(r<l(x)||r(x)<l)return 0;
		if(l<=l(x)&&r(x)<=r)return val(x);
		pushdown(x);
		return query(lson,l,r)+query(rson,l,r); 
	}
}T; 
int n,m,a;
struct Graph{
	struct node{
		int v,nxt;
	}e[maxn<<1];
	int cnt,head[maxn];
	void add(int x,int y){e[++cnt]=(node){y,head[x]};head[x]=cnt;}
	int tot,dfn[maxn],size[maxn];
	void dfs(int x,int fa){
		dfn[x]=++tot,size[x]=1;
		for(int i=head[x];i;i=e[i].nxt)
			if(e[i].v!=fa)dfs(e[i].v,x),size[x]+=size[e[i].v];
	}
}G;
char get(){
	char c=in::getc();
	while(!isalpha(c))c=in::getc();
	return c;
}
signed main(){
	//freopen("in.cpp","r",stdin);
	in::read(n);
	for(int i=1;i<n;i++)
		in::read(a),G.add(a,i+1);
	G.dfs(1,0);
	for(int i=1;i<=n;i++)
		in::read(a),T.a[G.dfn[i]]=a;
	T.build(1,1,n);
	in::read(m);
	while(m--){
		char opt=get();
		int x;in::read(x);
		if(opt=='g'){
			out::write(T.query(1,G.dfn[x],G.dfn[x]+G.size[x]-1));
			out::putc('\n');	
		}
		else{
			T.change(1,G.dfn[x],G.dfn[x]+G.size[x]-1);
		}
		//for(int i=1;i<=n;i++)
		//	out::write(T.query(1,i,i)),out::putc(' ');
		//out::putc('\n');
	}
	out::flush();
	return 0;
}
```

---

## 作者：genshy (赞：6)

## 前言

一道很简单的题，当你刷过其他的树剖题，你就会发现这道题是如此的 So,Easy"

## 题意

两种操作，一个是求子树中 $1$ 的个数，另一种是区间取反，即 $0$变为$1$

$1$变为$0$。（~~学过树剖的一眼就切了雾~~）

## 前置芝士

#### dfn序 

 定义： 节点被遍历的顺序
 
 性质： 1. 子树中dfn序是连续的。
 
          2. 一条重链上dfn序是连续的（~~没学过树剖的请自行跳过~~）
## 分析

首先，我们可以遍历整棵树，求出每个点的dfn序，在以dfn序建树。

对于操作一，我们可以线段树维护区间和（由性质1可得子树的dfn序是连续的，

所以区间也是连续的）。

对于操作二，我们发现一个序列连续取两次反，就会变为原来的序列。所以我们

维护一个tag标记，1表示未取反，-1表示取反一次。下放时，孩子节点的tag直接

乘以-1就行了，区间和变为区间长度减去原来的区间和。

## 几个要注意的点

1. 标记要初始化为1，而不是0

1. 下放标记时，孩子节点的标记要乘以-1，而不是变为-1.（因为原来孩子可能

   要取反，现在在取反一次等同于没有取反）。

1. 下放时区间和变为区间长度减去原来的区间和

~~好像都是打标记出现的问题（雾）~~

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 2e5+10;
char opt[10];
int n,v,t,x,tot,num;
int dfn[N],w[N],a[N],size[N],head[N];
inline int read()
{
	int s = 0, w = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') w = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10+ch -'0'; ch = getchar();}
	return s * w;
}
struct node{int to,net;}e[N<<1];
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].net = head[x];
	head[x] = tot;
}
void dfs(int x,int fa)//dfs求dfs序
{
	size[x] = 1; dfn[x] = ++num; w[dfn[x]] = a[x];
	for(int i = head[x]; i; i = e[i].net)
	{
        int to = e[i].to;
        if(to == fa) continue;
        dfs(to,x);
        size[x] += size[to];
	}
}
struct Tree
{
	struct node{
		int lc,rc;
		int tag,sum;
	}tr[N<<2];
	#define l(o) tr[o].lc
	#define r(o) tr[o].rc
	#define tag(o) tr[o].tag
	#define sum(o) tr[o].sum
	void up(int o)
	{
		sum(o) = sum(o<<1) + sum(o<<1|1);
	}
	void cover(int o)
	{
		tag(o) *= -1;
		sum(o) = (r(o) - l(o) + 1) - sum(o);
	}
	void down(int o)//下放标记
	{
		if(tag(o) == -1)
		{
			cover(o<<1); cover(o<<1|1);
			tag(o) = 1;
		}
	}
	void build(int o,int L,int R)
	{
		l(o) = L, r(o) = R; tag(o) = 1;//tag初始化一定要为1
		if(L == R)
		{
			sum(o) = w[L]; return;
		}
		int mid = (L + R)>>1;
		build(o<<1,L,mid);
		build(o<<1|1,mid+1,R);
		up(o);
	}
	void chenge(int o,int L,int R)//区间取反
	{
        if(L <= l(o) && R >= r(o))
        {
        	cover(o); return;
        }
        down(o);
        int mid = (l(o) + r(o))>>1;
        if(L <= mid) chenge(o<<1,L,R);
        if(R > mid) chenge(o<<1|1,L,R);
        up(o);
	}
	int ask(int o,int L,int R)//区间和
	{
		int ans = 0;
		if(L <= l(o) && R >= r(o)) {return sum(o);}
		down(o);
		int mid = (l(o) + r(o))>>1;
		if(L <= mid) ans += ask(o<<1,L,R);
		if(R > mid) ans += ask(o<<1|1,L,R);
		return ans;
	}
}tree;
int main()
{
   n = read();
   for(int i = 2; i <= n; i++)//习惯了从1开始编号
   {
   	   v = read();
   	   add(v,i); add(i,v);
   }
   for(int i = 1; i <= n; i++) a[i] = read();
   dfs(1,1); tree.build(1,1,n);
   t = read();
   while(t--)
   {
   	   scanf("%s",opt+1);
   	   x = read();
   	   if(opt[1] == 'g')//询问子树1的个数
   	   {
   	   	   printf("%d\n",tree.ask(1,dfn[x],dfn[x] + size[x] - 1));
   	   }
   	   if(opt[1] == 'p')//区间取反
   	   {
   	   	   tree.chenge(1,dfn[x],dfn[x] + size[x] - 1);
   	   }
    }
    return 0;
}
```


---

## 作者：saxiy (赞：4)

### 简明的代码

思路和楼下大佬是一样的

 _~~大佬码风难以恭维~~_ 

#### dfs序 + 线段树

要注意这里lazy数组作为一个bool标记执行的是取反操作。

剩下的要点在代码注释里

------------

```cpp
#include <cstdio>
#define N 200005
using namespace std;

int n, q, a[N];
//邻接链表记录子节点
int head[N], point[N], next[N], top = 1;
//线段树的L,R标记(每个节点占域)
//P在这里记录dfs序先后顺序
int p[N], L[N], R[N], cnt, num;
int tr[4 * N];//线段树
bool lazy[4 * N];//bool-lazy数组

void insert(int u, int v) {//邻接链表插入
	point[top] = v;
	next[top] = head[u];
	head[u] = top++;
}

void dfs(int x) {//求dfs序
	L[x] = ++cnt;
	p[cnt] = x;
	for(int i = head[x];i;i = next[i])
		dfs(point[i]);
	R[x] = cnt;
}

void build(int l, int r, int x) {//建树
	if(l == r) {
		tr[x] = a[p[++num]];//P数组的作用体现出来了
		return;
	}
	int mid = l + r >> 1;
	build(l, mid, x << 1);
	build(mid + 1, r, x << 1 | 1);
	tr[x] = tr[x << 1] + tr[x << 1 | 1];//push_up
}

void push_down(int l, int r, int x) {//lazy-push_down
	int mid = l + r >> 1;
	tr[x << 1] = mid - l + 1 - tr[x << 1];//计算取反后节点数
	tr[x << 1 | 1] = r - mid - tr[x << 1 | 1];
	lazy[x << 1] = !lazy[x << 1];//!!取反操作
	lazy[x << 1 | 1] = !lazy[x << 1 | 1];
	lazy[x] = 0;
}

int get(int l, int r, int x, int ls, int lr) {//计算数量
	if(l == ls && r == lr) {
		return tr[x];
	}
	if(lazy[x]) push_down(l, r, x);
	int mid = l + r >> 1;
	if(lr <= mid) return get(l, mid, x << 1, ls, lr);
	else if(ls > mid) return get(mid + 1, r, x << 1 | 1, ls, lr);
	else {
		return get(l, mid, x << 1, ls, mid) + get(mid + 1, r, x << 1 | 1, mid + 1, lr);
	}
}

void pow(int l, int r, int x, int ls, int lr) {//集体取反
	if(l == ls && r == lr) {
		tr[x] = r - l + 1 - tr[x];
		lazy[x] = !lazy[x];
		return;
	}
	if(lazy[x]) push_down(l, r, x);
	int mid = l + r >> 1;
	if(lr <= mid) pow(l, mid, x << 1, ls, lr);
	else if(ls > mid) pow(mid + 1, r, x << 1 | 1, ls, lr);
	else {
		pow(l, mid, x << 1, ls, mid);
		pow(mid + 1, r, x << 1 | 1, mid + 1, lr);
	}
	tr[x] = tr[x << 1] + tr[x << 1 | 1];//!!push_up
}

int main() {
	scanf("%d", &n);
	int u;
	for(int i = 2;i <= n;i++) {
		scanf("%d", &u);
		insert(u, i);//建树
	}
	for(int i = 1;i <= n;i++)
		scanf("%d", a + i);
	dfs(1);
	build(1, cnt, 1);//建线段树
	scanf("%d", &q);
	char op[10];
	int x;
	while(q--) {
		scanf("%s%d", op, &x);
		if(*op == 'p') pow(1, cnt, 1, L[x], R[x]);
		else printf("%d\n", get(1, cnt, 1, L[x], R[x]));
	}
	return 0;
}
```

---

## 作者：Jairon314 (赞：3)

$ \text {Solution} $

$ \text{\small 前置芝士——轻重链剖分+线段树} $

____________

这题也算是一道很经典的题目了，就是几个树链剖分的基本处理方法，对树链剖分各种操作熟悉的人写这个题就十分轻松。我看懂这个题目以后，发现这个题比较好做，于是就来氵题解+氵紫题了。

本题的操作很明确：

> 1. 对一个节点的子树中所有节点的权值进行异或运算

> 2. 求一个节点的子树中所有节点的权值和

看到对子树进行修改与查询，明显就是树链剖分的基本操作。那么，将这颗树上的 $\text{dfs}$ 序提出来扔进线段树之后，线段树中的区间和查询+区间异或也是很经典的题目。比较值得一讲的地方就是 $\text{pushdown}$ 的操作了。

```cpp
void pushdown(int ID){
	if(tree[ID].lazy){
		tree[ID].lazy^=1;
		tree[ID<<1].lazy^=1;
		tree[ID<<1|1].lazy^=1;
		tree[ID<<1].val=tree[ID<<1].len-tree[ID<<1].val;
		tree[ID<<1|1].val=tree[ID<<1|1].len-tree[ID<<1|1].val;
	}
}
```

对线段树的一个区间进行异或操作以后，因为原本那棵树上所有节点的权值不是 ``1`` 就是 ``0`` ，所以修改之后该区间的区间和就变成了区间的长度减去原本的区间和。

$ \text {\color{red} e.g. \; \; 假设区间中的元素是[0,0,1,0,1]，那么它的区间和就是2，长度是5} $

$ \text {\color{red} 如果对这个区间进行取反操作，则操作后的区间元素是[1,1,0,1,0]} $

$ \text {\color{red} 它的区间和就变成了}{\color{red} 5 - 2=3} $

------------

接下来就是代码时间了，树链剖分和线段树的写法具体请看板子题

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

// #define int long long

/***************快读***************/

namespace IO {
char buf[1<<21], *p1 = buf, *p2 = buf, buf1[1<<21];
inline char gc () {return p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}

#ifndef ONLINE_JUDGE
#endif

#define gc getchar

template<class I>
inline void read(I &x) {
    x = 0; I f = 1; char c = gc();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = gc(); }
    while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = gc(); }
    x *= f;
}

template<class I>
inline void write(I x) {
    if(x == 0) {putchar('0'); return;}
    I tmp = x > 0 ? x : -x;
    if(x < 0) putchar('-');
    int cnt = 0;
    while(tmp > 0) {
        buf1[cnt++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while(cnt > 0) putchar(buf1[--cnt]);
}

#define in(x) read(x)
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')

} using namespace IO;

/***************快读***************/

#define maxn 1000010

struct Edge{
	int start;
	int end;
	int val;
	int nexty;
}edge[maxn];

int link[maxn],edge_cnt;

void add_edge(int u,int v,int w=0){
	edge[++edge_cnt]=(Edge){u,v,w,link[u]};
	link[u]=edge_cnt;
}

int tot[maxn],top[maxn],depth[maxn];
int fa[maxn],son[maxn],id[maxn];
int a[maxn],b[maxn];
int dfs_cnt;

int dfs1(int now,int f,int dep){
	fa[now]=f;
	depth[now]=dep;
	tot[now]=1;
	int maxson=-1;
	for(int i=link[now];i;i=edge[i].nexty){
		if(edge[i].end==f){continue;}
		tot[now]+=dfs1(edge[i].end,now,dep+1);
		if(maxson<tot[edge[i].end]){
			maxson=tot[edge[i].end];
			son[now]=edge[i].end;
		}
	}
	return tot[now];
}

void dfs2(int now,int topf){
	id[now]=++dfs_cnt;
	a[dfs_cnt]=b[now];
	top[now]=topf;
	if(!son[now]){return;}
	dfs2(son[now],topf);
	for(int i=link[now];i;i=edge[i].nexty){
		if(!id[edge[i].end]){
			dfs2(edge[i].end,edge[i].end);
		}
	}
}

class Segment_Fold{
	private:
		struct Seg_Tree{
			int l,r;
			int len;
			int val;
			int lazy;
		}tree[maxn];

	public:
		void pushup(int ID){
			tree[ID].val=tree[ID<<1].val+tree[ID<<1|1].val;
		}

		void build(int ID,int l,int r){
			tree[ID].l=l,tree[ID].r=r;
			tree[ID].len=(r-l+1);
			if(l==r){
				tree[ID].val=a[l];
				return;
			}
			int mid=(l+r)>>1;
			build(ID<<1,l,mid);
			build(ID<<1|1,mid+1,r);
			pushup(ID);
			return;
		}

		void pushdown(int ID){
			if(tree[ID].lazy){
				tree[ID].lazy^=1;
				tree[ID<<1].lazy^=1;
				tree[ID<<1|1].lazy^=1;
				tree[ID<<1].val=tree[ID<<1].len-tree[ID<<1].val;
				tree[ID<<1|1].val=tree[ID<<1|1].len-tree[ID<<1|1].val;
			}
		}

		void update(int ID,int l,int r){
			if(tree[ID].l>=l&&tree[ID].r<=r){
				tree[ID].lazy^=1;
				tree[ID].val=tree[ID].len-tree[ID].val;
				return;
			}
			pushdown(ID);
			int mid=(tree[ID].l+tree[ID].r)>>1;
			if(l<=mid){
				update(ID<<1,l,r);
			} if(r>mid){
				update(ID<<1|1,l,r);
			}
			pushup(ID);
			return;
		}

		void Tree_Update(int x,int y){
			while(top[x]!=top[y]){
				if(depth[top[x]]<depth[top[y]]){
					std::swap(x,y);
				}
				update(1,id[top[x]],id[x]);
				x=fa[top[x]];
			}
			if(depth[x]>depth[y]){
				std::swap(x,y);
			}
			update(1,id[x],id[y]);
			return;
		}

		int query(int ID,int l,int r){
			if(tree[ID].l>=l&&tree[ID].r<=r){
				return tree[ID].val;
			}
			pushdown(ID);
			int mid=(tree[ID].l+tree[ID].r)>>1;
			int ans=0;
			if(l<=mid){
				ans+=query(ID<<1,l,r);
			} if(r>mid){
				ans+=query(ID<<1|1,l,r);
			}
			return ans;
		}

		int Tree_Query(int x,int y){
			int ans=0;
			while(top[x]!=top[y]){
				if(depth[top[x]]<depth[top[y]]){
					std::swap(x,y);
				}
				ans+=query(1,id[top[x]],id[x]);
				x=fa[top[x]];
			}
			if(depth[x]>depth[y]){
				std::swap(x,y);
			}
			ans+=query(1,id[x],id[y]);
			return ans;
		}
}se;

int root=1;
int n,m;

int main(){
	read(n);
	for(int i=1,x;i<n;i++){
		read(x);
		add_edge(x,i+1);
	}
	for(int i=1;i<=n;i++){read(b[i]);}
	dfs1(root,0,1);
	dfs2(root,root);
	se.build(1,1,n);
	read(m);
	std::string opt;
	int k;
	while(m--){
		std::cin>>opt;
		read(k);
		if(opt[0]=='g'){
			outn(se.query(1,id[k],id[k]+tot[k]-1));
		} else{
			se.update(1,id[k],id[k]+tot[k]-1);
		}
	}
	return 0;
}
```

$\text{15}$分钟码完一遍过挑战无 $\text{bug}$


![](bilibili:BV1sM4y1M7wX)

---

## 作者：斜揽残箫 (赞：1)

## Description

给你一棵只有 0 和 1 的树，有两个操作 ：

+ 询问一棵子树中有几个 1。
+ 把一棵子树的数字取反。

$1 \leq n,q \leq 2 \times 10 ^ 5$。

其实就是一个树链剖分的板子题。

## Solution

前置知识 ： 树链剖分，线段树。

首先，先用树剖进行树上 dfs 的标记和子树的统计，这里有一个性质，就是一颗子树的 dfs 序肯定是连续的一串，所以，我们用 ```dfn[]``` 表示 dfs 序，用 ```tot[]``` 表示子树大小，那么点 $x$ 的子树内的点的 dfs 序的范围就是 ```dfn[x] + tot[x] - 1```。

所以，我们就把一个统计子树的问题转化到了一个序列上。

之后就直接搞一棵线段树就好了。

所以，因为只有 0 和 1，所以我们对于求有几个 1，维护一个区间和即可。

对于取反操作，取奇数次相当于取反，取偶数次相当于不变，并且取反后的区间和就是区间长度减去原来的区间和，之后打标记下放，都是常规操作了。

## Code 

```
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int Maxk = 2e5 + 10;
int dfn[Maxk],tot[Maxk],son[Maxk];
int top[Maxk],deep[Maxk],fa[Maxk];
int a[Maxk],b[Maxk];
vector <int> E[Maxk];
int n,m,cnt;
struct SegTree {
  int l_,r_,sum_,tag_,Len_;
}t[Maxk << 2];
inline int read()
{
	int s = 0, f = 0;char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}
void dfs1(int x,int f)
{
  deep[x] = deep[f] + 1;
  fa[x] = f;
  tot[x] = 1;
  for(int i = 0;i < E[x].size();i ++) {
    int y = E[x][i];
    if(y == f) continue;
    dfs1(y,x);
    tot[x] += tot[y];
    if(tot[y] > tot[son[x]]) son[x] = y;
  }  
} 
void dfs2(int x,int tf)
{
  dfn[x] = ++ cnt;  
  a[cnt] = b[x];
  top[x] = tf;
  if(!son[x]) return;
  dfs2(son[x],tf);
  for(int i = 0;i < E[x].size();i ++) {
    int y = E[x][i];
    if(y == fa[x] || y == son[x]) continue;
    dfs2(y,y); 
  } 
} 
void push_up(int i)
{
  t[i].sum_ = t[i << 1].sum_ + t[i << 1 | 1].sum_;
}
void build(int i,int l,int r)
{
  t[i].l_ = l;
  t[i].r_ = r;
  t[i].Len_ = r - l + 1;
  if(l == r) {
    t[i].sum_ = a[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(i << 1,l,mid);
  build(i << 1 | 1,mid + 1,r);
  push_up(i);
}
void push_down(int i)
{
  if(!t[i].tag_) return;
  t[i << 1].sum_ = t[i << 1].Len_ - t[i << 1].sum_;
  t[i << 1 | 1].sum_ = t[i << 1 | 1].Len_ - t[i << 1 | 1].sum_;
  t[i << 1].tag_ ^= 1;
  t[i << 1 | 1].tag_ ^= 1;
  t[i].tag_ ^= 1;
}
void Change(int i,int l,int r)
{
  if(t[i].l_ >= l && t[i].r_ <= r) {
    t[i].sum_ = t[i].Len_ - t[i].sum_;
    t[i].tag_ ^= 1;
    return;
  }
  push_down(i);
  int mid = (t[i].l_ + t[i].r_) >> 1;
  if(l <= mid) Change(i << 1,l,r);
  if(r > mid) Change(i << 1 | 1,l,r);
  push_up(i);
} 
int Ask(int i,int l,int r)
{
  if(t[i].l_ >= l && t[i].r_ <= r) return t[i].sum_;
  int Ans = 0,mid = (t[i].l_ + t[i].r_) >> 1;
  push_down(i);
  if(l <= mid) Ans += Ask(i << 1,l,r);
  if(r > mid) Ans += Ask(i << 1 | 1,l,r);
  return Ans; 
}
signed main()
{
  n = read();
  for(int i = 1;i <= n - 1;i ++) {
    int x = read();
    E[x].push_back(i + 1);
  }
  for(int i = 1;i <= n;i ++) b[i] = read();
  dfs1(1,0);
  dfs2(1,1);
  build(1,1,n);
  m = read();
  for(int i = 1;i <= m;i ++) {
    string s;cin >> s;int x = read();
    if(s[0] == 'g') printf("%d\n",Ask(1,dfn[x],dfn[x] + tot[x] - 1));
    else if(s[0] == 'p') Change(1,dfn[x],dfn[x] + tot[x] - 1);
  }
  return 0;
}
```


---

## 作者：KEBrantily (赞：1)

## Description

给定一棵权值只能为 $1$ 或 $0$ 的树，对其进行两种操作。

一种是将其中的某棵子树取反，另一种是询问某棵子树中 $1$ 的个数。

## Solution

比较板的线段树。

显然的，假设一棵大小为 $x$ 的子树中有 $y$ 个 1，那么这棵子树取反后就有 $x-y$ 个 $1$。

题目只需要我们维护一种信息，然后这种信息的变换只有这一种方法，所以我们知道了这个性质就可以直接搞了。

根据区间修改维护懒标记的原理，当一个点的子树取反后，它的左右儿子都要取反，因此懒标记下传时也不断取反就可以了。

然后就做完了。

## Code

```cpp
#include<bits/stdc++.h>
#define maxn 2001000
#define INF 0x3f3f3f3f 
//#define int long long

using namespace std;

int n,m,tot,cnt;
int a[maxn],head[maxn],lazy[maxn];
int sum[maxn],val[maxn],fa[maxn];
int dfn[maxn],top[maxn],son[maxn];
int dep[maxn],siz[maxn],pre[maxn];
struct edge{int fr,to,nxt;}e[maxn];

int read(){
	int s=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+ch-'0';ch=getchar();}
	return s*w;
}

void add(int fr,int to){
    e[++tot].fr=fr;e[tot].to=to;
    e[tot].nxt=head[fr];head[fr]=tot;
}

namespace Seg{
    #define ls x<<1
    #define rs x<<1|1
    void pushup(int x){
        sum[x]=sum[ls]+sum[rs];
    }
    
    void pushdown(int x,int ln,int rn){
        if(!lazy[x]) return;
        lazy[ls]^=1;
        lazy[rs]^=1;
        sum[ls]=ln-sum[ls];
        sum[rs]=rn-sum[rs];
        lazy[x]=0;
    }
    
    void build(int x,int l,int r){
        if(l==r){sum[x]=a[pre[l]];return;} 
        int mid=l+r>>1;
        build(ls,l,mid);build(rs,mid+1,r);
        pushup(x);
    }
    
    void update(int x,int l,int r,int L,int R){
        if(L<=l&&R>=r){sum[x]=r-l+1-sum[x],lazy[x]^=1;return;}
        int mid=l+r>>1;pushdown(x,mid-l+1,r-mid);
        if(L<=mid) update(ls,l,mid,L,R);
        if(R>=mid+1) update(rs,mid+1,r,L,R);
        pushup(x); 
    }
    
    int query(int x,int l,int r,int L,int R){
        if(L<=l&&R>=r)return sum[x];
        int mid=l+r>>1,ans=0;pushdown(x,mid-l+1,r-mid);
        if(L<=mid) ans+=query(ls,l,mid,L,R);
        if(R>=mid+1) ans+=query(rs,mid+1,r,L,R);
        return ans;
    }
}

namespace Cut{
    void dfs1(int x,int fat){
        dep[x]=dep[fat]+1;
        fa[x]=fat;siz[x]=1;
        for(int i=head[x];i;i=e[i].nxt){
            int to=e[i].to;
            if(to==fat) continue;
            dfs1(to,x);siz[x]+=siz[to];
            if(siz[to]>siz[son[x]])son[x]=to;
        }
    }
    
    void dfs2(int x,int tp){
        top[x]=tp;dfn[x]=++cnt;pre[cnt]=x;
        if(son[x]) dfs2(son[x],tp);
        for(int i=head[x];i;i=e[i].nxt){
            int to=e[i].to;
            if(to==fa[x]||to==son[x]) continue;
            dfs2(to,to);
        }
    }
}

int main(){
    n=read();
    for(int i=2,fa;i<=n;i++) fa=read(),add(fa,i);
    for(int i=1;i<=n;i++) a[i]=read();m=read();
    Cut::dfs1(1,0);Cut::dfs2(1,1);Seg::build(1,1,n);
    for(int i=1,pos;i<=m;i++){
        string opt;cin>>opt;pos=read();
        if(opt[0]=='g') printf("%d\n",Seg::query(1,1,n,dfn[pos],dfn[pos]+siz[pos]-1));
        else if(opt[0]=='p') Seg::update(1,1,n,dfn[pos],dfn[pos]+siz[pos]-1);
    }
    return 0;
}
```


---

## 作者：欧鹰 (赞：1)

（日常聊天）一天俩题解，爽呀。~~虽然不一定能过~~

------------


题意：树剖裸题。



------------

打一个树剖。

1. pow：拿区间长度减去当前1的个数；

2. get：求区间和。

3. 懒标记：如果改过两次，即相当于没改过。（如果你不会二进制的，只要拿懒标记%2，就可以）。

总结，树剖裸题。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

struct node{
	int u,v;
}a[2000500];

int laz[2000500],cnt;

int head[2000500],tree[2000500];

int n,m,p,wt[2000500],cntt,son[2000500];

int dep[2005000],top[2005000],w[2000500];

int siz[2005000],fath[2005000],r,id[2000500];

void add(int u,int v)
{
	a[++cntt].u=head[u];
	
	a[cntt].v=v;
	
	head[u]=cntt;
}

void pushdown(int u,int l,int r)
{
	if(laz[u]==0)return;
	
	int mid=(l+r)/2;
	
	laz[u*2]=(laz[u*2]+laz[u])%2;
	
	laz[u*2+1]=(laz[u*2+1]+laz[u])%2;
	
	tree[u*2]=-tree[u*2]+mid-l+1;
	
	tree[u*2+1]=-tree[u*2+1]+(r-mid);
	
	laz[u]=0;
	
	return;
}

void build(int u,int l,int r)
{
	if(l==r)
	{
		tree[u]=wt[l];
		
		return;
	}
    //cout<<u;
	int mid=(l+r)/2;
	
	build(u*2,l,mid);
	
	build(u*2+1,mid+1,r);
	
	tree[u]=tree[u*2]+tree[u*2+1]; 
	//cout<<tree[u];
}

void update(int u,int l,int r,int x,int y,int z)
{
	if(l>=x&&r<=y)
	{
		laz[u]=(laz[u]+1)%2;
		
		tree[u]=-tree[u]+(r-l+1);
		
		return;
	}
	
	int mid=(l+r)/2;
		//cout<<1;
	pushdown(u,l,r);
		
	if(x<=mid) update(u*2,l,mid,x,y,z);
	
	if(y>mid) update(u*2+1,mid+1,r,x,y,z);
	
	tree[u]=tree[u*2]+tree[u*2+1];
}

int query(int u,int l,int r,int x,int y)
{
	if(l>=x&&r<=y) return tree[u];
	
	pushdown(u,l,r);
	
	int mid=(l+r)/2,ans=0;
	
	if(x<=mid) ans=(ans+query(u*2,l,mid,x,y));
	
	if(y>mid) ans=(ans+query(u*2+1,mid+1,r,x,y));
	
	return ans;
}

int query1(int l,int r)
{
	int ans=0;
	
	while(top[l]!=top[r])
	{
		if(dep[top[l]]<dep[top[r]])swap(l,r);
		
		ans=(ans+query(1,1,n,id[top[l]],id[l]))%p;
		
		l=fath[top[l]];
	}
	
	if(dep[l]>dep[r])swap(l,r);
	
	ans=(ans+query(1,1,n,id[l],id[r]))%p;
	
	return ans%p; 
}

void add1(int l,int r,int t)
{
	t%=p;
	
	while(top[l]!=top[r])
	{
		if(dep[top[l]]<dep[top[r]])swap(l,r);
		
		update(1,1,n,id[top[l]],id[l],t);
		
		l=fath[top[l]];
	}
	
	if(dep[l]>dep[r])swap(l,r);
	
	update(1,1,n,id[l],id[r],t);
}

int query2(int u)
{
	return query(1,1,n,id[u],id[u]+siz[u]-1);
}

void add2(int u,int t)
{
	update(1,1,n,id[u],id[u]+siz[u]-1,t);
}

void dfs1(int u,int fa,int deep)
{
	dep[u]=deep;
	
	fath[u]=fa;
	
	siz[u]=1;
	
	int mson=-1;
	
	for(int i=head[u];i;i=a[i].u)
	{
		int v=a[i].v;
		
		if(v==fa)continue;
		
		dfs1(v,u,deep+1);
		
		siz[u]+=siz[v];
		
		if(siz[v]>mson)
		{
			son[u]=v;
			
			mson=siz[v];
		}
	}
}

void dfs2(int u,int topu)
{
	id[u]=++cnt;
	
	wt[cnt]=w[u];
	
	top[u]=topu;
	
	if(son[u]==0)return;
	
	dfs2(son[u],topu);
	
	for(int i=head[u];i;i=a[i].u)
	{
		int v=a[i].v;
		
		if(v==fath[u]||v==son[u])continue;
		
		dfs2(v,v);
	}
}

signed main()//主程序 
{
	cin>>n;
	
	for(int i=2;i<=n;i++)
	{
		int x,y;
		
		cin>>x;
		
		add(x,i);
		
		add(i,x);
	}
	
	for(int i=1;i<=n;i++) cin>>w[i];
	
	dfs1(1,0,1);
	
	dfs2(1,1);
	
	build(1,1,n);
	//cout<<tree[1];
	cin>>m;
	
	while(m--)
	{
		string opt;
		
		int x,y,z;
		
		cin>>opt;
		
		if(opt=="pow")
		{
			cin>>x;
			
			add2(x,1);
		}
		
		if(opt=="get")
		{
			cin>>x;
			
			cout<<query2(x)<<endl;
		}
		
	}
	
	return 0;
	
}
```



---

## 作者：__Hacheylight__ (赞：1)

题意：

给一棵 $n$ 个节点的树，每个节点有一个灯，灯可亮可灭。

给出 $m$ 个操作，分为两种：

* 将 $x$ 及其子树的灯变成相反状态（亮变灭，灭变亮）；
* 统计 $x$ 及其子树有多少个灯是亮的。

题目要我们支持子树异或，子树求和

这类子树问题可以很好的用 $dfs$ 序解决

子树对应着 $dfs$ 序的一个区间

区间就可以用线段树完成

记录 $sz$ 表示子树大小，$v$ 表示有多少个亮

取反就是 $v = sz - v$

弄个取反标记下传即可

```cpp
#include <map>
#include <set>
#include <ctime>
#include <queue>
#include <stack>
#include <cmath>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <numeric>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;
//#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define loop(s, v, it) for (s::iterator it = v.begin(); it != v.end(); it++)
#define cont(i, x) for (int i = head[x]; i; i = e[i].nxt)
#define clr(a) memset(a, 0, sizeof(a))
#define ass(a, sum) memset(a, sum, sizeof(a))
#define lowbit(x) (x & -x)
#define all(x) x.begin(), x.end()
#define ub upper_bound
#define lb lower_bound
#define pq priority_queue
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define iv inline void
#define enter cout << endl
#define siz(x) ((int)x.size())
#define file(x) freopen(#x".in", "r", stdin),freopen(#x".out", "w", stdout)
typedef long long ll ;
typedef unsigned long long ull ;
typedef pair <int, int> pii ;
typedef vector <int> vi ;
typedef vector <pii> vii ;
typedef queue <int> qi ;
typedef queue <pii> qii ;
typedef set <int> si ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
const int N = 200010 ;
const int INF = 0x3f3f3f3f ;
const int iinf = 1 << 30 ;
const ll linf = 2e18 ;
const int MOD = 1000000007 ;
const double eps = 1e-7 ;
void print(int x) { cout << x << endl ; exit(0) ; }
void PRINT(string x) { cout << x << endl ; exit(0) ; }
void douout(double x){ printf("%lf\n", x + 0.0000000001) ; }

char op[10] ;
int in[N], out[N], head[N], to[N], on[N] ;
int n, m, top = 1, tim ;

struct Edge {
	int to, nxt ;
} e[N << 1] ;

void add(int a, int b) {
	e[++top] = (Edge) {b, head[a]} ;
	head[a] = top ;
}

void dfs(int x, int fa) {
	in[x] = ++tim ; to[tim] = x ;
	cont(i, x) {
		int to = e[i].to ;
		if (to == fa) continue ;
		dfs(to, x) ;
	}
	out[x] = tim ;
}

struct Segtree {
	int l, r, v, sz, tag ; // 多少开着，子树大小为多少，取反标记
	#define ls(x) x << 1
	#define rs(x) x << 1 | 1
	#define l(x) tr[x].l
	#define r(x) tr[x].r
	#define v(x) tr[x].v
	#define sz(x) tr[x].sz
	#define tag(x) tr[x].tag
} tr[N << 2] ;

void pushup(int x) {
	v(x) = v(ls(x)) + v(rs(x)) ;
	sz(x) = sz(ls(x)) + sz(rs(x)) ;
}

void pushdown(int x) {
	if (tag(x)) {
		tag(ls(x)) ^= 1 ;
		tag(rs(x)) ^= 1 ;
		v(ls(x)) = sz(ls(x)) - v(ls(x)) ;
		v(rs(x)) = sz(rs(x)) - v(rs(x)) ;
		tag(x) = 0 ;
	}
}

void build(int x, int l, int r) {
	l(x) = l, r(x) = r ;
	if (l == r) {
		v(x) = on[to[l]] ;
		sz(x) = 1 ;
		return ;
	}
	int mid = (l + r) >> 1 ;
	build(ls(x), l, mid) ;
	build(rs(x), mid + 1, r) ;
	pushup(x) ;
}

void modify(int x, int l, int r) {
	if (l <= l(x) && r(x) <= r) {
		v(x) = sz(x) - v(x) ;
		tag(x) ^= 1 ;
		return ;
	}
	pushdown(x) ;
	int mid = (l(x) + r(x)) >> 1 ;
	if (l <= mid) modify(ls(x), l, r) ;
	if (mid < r) modify(rs(x), l, r) ;
	pushup(x) ;
}

int query(int x, int l, int r) {
	if (l <= l(x) && r(x) <= r) return v(x) ;
	pushdown(x) ;
	int mid = (l(x) + r(x)) >> 1, ans = 0 ;
	if (l <= mid) ans += query(ls(x), l, r) ;
	if (mid < r) ans += query(rs(x), l, r) ;
	return ans ;
}

signed main(){
	scanf("%d", &n) ;
	rep(i, 1, n - 1) {
		int x ; scanf("%d", &x) ;
		add(x, i + 1) ;
	}
	rep(i, 1, n) scanf("%d", &on[i]) ;
	dfs(1, 1) ;
	build(1, 1, n) ;
	scanf("%d", &m) ;
	while (m--) {
		scanf("%s", op + 1) ; int x ; scanf("%d", &x) ;
		if (op[1] == 'g') printf("%d\n", query(1, in[x], out[x])) ;
		else modify(1, in[x], out[x]) ;
	}
	return 0 ;
}

/*
写代码时请注意：
	1.ll？数组大小，边界？数据范围？
	2.精度？
	3.特判？
	4.至少做一些
思考提醒：
	1.最大值最小->二分？
	2.可以贪心么？不行dp可以么
	3.可以优化么
	4.维护区间用什么数据结构？
	5.统计方案是用dp？模了么？
	6.逆向思维？
*/


```


---

## 作者：Styx (赞：1)

**这道题有两个操作，子树异或，子树查询一的个数，可以用dfs序+线段树解决，异或标记可以通过tag[x]^=1来进行传递，每次更改相当于将区间内所有的1改为0，所有的0改为1，这样相当于把sum改为size-sum，可以O(1)实现**

**代码如下：**
```cpp
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define lson root<<1
#define rson root<<1|1
using namespace std;

struct node
{
	int l,r,lazy,sum;
} tr[800080];

vector<int> g[200020];
int id[200020],size[200020],c[200020],w[200020],tot;

void push_up(int root)
{
	tr[root].sum=tr[lson].sum+tr[rson].sum;
}

void push_down(int root)
{
	int mid=(tr[root].l+tr[root].r)>>1;
	tr[lson].sum=(mid-tr[root].l+1)-tr[lson].sum;
	tr[lson].lazy=1^tr[lson].lazy;
	tr[rson].sum=(tr[root].r-mid)-tr[rson].sum;
	tr[rson].lazy=1^tr[rson].lazy;
	tr[root].lazy=0;
}

void build(int root,int l,int r)
{
	if(l==r)
	{
		tr[root].l=l;
		tr[root].r=r;
		tr[root].sum=w[l];
		return ;
	}
	tr[root].l=l;
	tr[root].r=r;
	int mid=(l+r)>>1;
	build(lson,l,mid);
	build(rson,mid+1,r);
	push_up(root);
}

void update(int root,int l,int r,int val)
{
	if(tr[root].l==l&&tr[root].r==r)
	{
		tr[root].sum=(tr[root].r-tr[root].l+1)-tr[root].sum;
		tr[root].lazy=tr[root].lazy^1;
		return ;
	}
	if(tr[root].lazy)
	{
		push_down(root);
	}
	int mid=(tr[root].l+tr[root].r)>>1;
	if(l>mid)
	{
		update(rson,l,r,val);
	}
	else
	{
		if(mid>=r)
		{
			update(lson,l,r,val);
		}
		else
		{
			update(lson,l,mid,val);
			update(rson,mid+1,r,val);
		}
	}
	push_up(root);
}

int query(int root,int l,int r)
{
	if(tr[root].l==l&&tr[root].r==r)
	{
		return tr[root].sum;
	}
	if(tr[root].lazy)
	{
		push_down(root);
	}
	int mid=(tr[root].l+tr[root].r)>>1;
	if(mid<l)
	{
		return query(rson,l,r);
	}
	else
	{
		if(mid>=r)
		{
			return query(lson,l,r);
		}
		else
		{
			return query(lson,l,mid)+query(rson,mid+1,r);
		}
	}
}

void dfs(int now,int f)
{
	id[now]=++tot;
	w[tot]=c[now];
	size[now]=1;
	for(int i=0; i<g[now].size(); i++)
	{
		if(g[now][i]==f)
		{
			continue;
		}
		dfs(g[now][i],now);
		size[now]+=size[g[now][i]];
	}
}

void sub_update(int u,int val)
{
	update(1,id[u],id[u]+size[u]-1,val);
}

int sub_query(int u)
{
	return query(1,id[u],id[u]+size[u]-1);
}

int main()
{
	int n,m;
	scanf("%d",&n);
	for(int i=2; i<=n; i++)
	{
		int to;
		scanf("%d",&to);
		g[to].push_back(i);
		g[i].push_back(to);
	}
	for(int i=1; i<=n; i++)
	{
		scanf("%d",&c[i]);
	}
	dfs(1,0);
	build(1,1,n);
	scanf("%d",&m);
	char s[10];
	int val;
	for(int i=1; i<=m; i++)
	{
		scanf("\n%s %d",s,&val);
		if(s[0]=='g')
		{
			printf("%d\n",sub_query(val));
		}
		else
		{
			sub_update(val,1);
		}
	}
}
```

---

## 作者：louhao088 (赞：0)

树链剖分

## 思路

这是一道很简单的树剖题，若不会树剖，点[这里](https://www.luogu.com.cn/problem/P3384)

此题只要先用树剖将他变成线段树

改变子树，把子树反转即可，因为子树一定在一起，只要在线段树上操作即可

```cpp
void change(int rt,int l,int r)
{
	if(tr[rt].l>r||tr[rt].r<l)return;
	if(tr[rt].l>=l&&tr[rt].r<=r)
	{
		tr[rt].num=tr[rt].r-tr[rt].l+1-tr[rt].num;
		tr[rt].tag=tr[rt].tag^1;return;
	}
	push(rt);
	change(ls,l,r),change(rs,l,r);
	tr[rt].num=(tr[ls].num+tr[rs].num);
}
```

其余只要注意细节即可

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
#define ls rt<<1
#define rs rt<<1|1
const int maxn=500005;
struct edge
{
	int v,nex;
}e[maxn];
struct tree
{
	int l,r,num,tag;
}tr[maxn];
int head[maxn],a[maxn],n,m,mod,r,op,x,y,cnt=0,z;
int s[maxn],son[maxn],fa[maxn],h[maxn],top[maxn],id[maxn],idx=0,b[maxn];
void add(int u,int v){e[++cnt].v=v,e[cnt].nex=head[u],head[u]=cnt; }
void dfs1(int u)
{
	h[u]=h[fa[u]]+1;s[u]=1;
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(fa[u]==v)continue;
		fa[v]=u;dfs1(v);s[u]+=s[v];
		if(s[son[u]]<s[v])son[u]=v;
	}
} 
void dfs2(int u,int topp)
{
	id[u]=++idx;
	b[idx]=a[u];
	top[u]=topp;
	if(son[u])dfs2(son[u],topp);
	for(int i=head[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
void push(int rt)
{
	if(tr[rt].tag)
		tr[rs].tag=tr[rs].tag^1,tr[ls].tag=tr[ls].tag^1,
		tr[rs].num=tr[rs].r-tr[rs].l+1-tr[rs].num,
		tr[ls].num=tr[ls].r-tr[ls].l+1-tr[ls].num;
	tr[rt].tag=0;
}
void build(int rt,int l,int r)
{
	tr[rt].l=l,tr[rt].r=r;tr[rt].tag=0;
	if(l==r)
	{
		tr[rt].num=b[l];return;
	}
	int mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	tr[rt].num=tr[ls].num+tr[rs].num;
}
void change(int rt,int l,int r)
{
	if(tr[rt].l>r||tr[rt].r<l)return;
	if(tr[rt].l>=l&&tr[rt].r<=r)
	{
		tr[rt].num=tr[rt].r-tr[rt].l+1-tr[rt].num;
		tr[rt].tag=tr[rt].tag^1;return;
	}
	push(rt);
	change(ls,l,r),change(rs,l,r);
	tr[rt].num=(tr[ls].num+tr[rs].num);
}
int query(int rt,int l,int r)
{
	if(tr[rt].l>r||tr[rt].r<l)return 0;
	if(tr[rt].l>=l&&tr[rt].r<=r)return tr[rt].num;
	push(rt);
	return (query(ls,l,r)+query(rs,l,r));
}
char c=0;
int main()
{
	n=read();
	for(int i=1;i<n;i++)x=i+1,y=read(),add(x,y),add(y,x);
	for(int i=1;i<=n;i++)a[i]=read();
	dfs1(1),dfs2(1,1);
	build(1,1,n),m=read();
	for(int i=1;i<=m;i++)
	{
		while(c!='p'&&c!='g')c=getchar();
		if(c=='p')
			x=read(),change(1,id[x],id[x]+s[x]-1);
		if(c=='g')
			x=read(),printf("%d\n",query(1,id[x],id[x]+s[x]-1));c=0;
	}
	return 0;
}
```





---

