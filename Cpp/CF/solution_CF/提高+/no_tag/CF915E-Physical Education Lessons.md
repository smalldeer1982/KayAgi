# Physical Education Lessons

## 题目描述

#### 题意：
Alex高中毕业了，他现在是大学新生。虽然他学习编程，但他还是要上体育课，这对他来说完全是一个意外。快要期末了，但是不幸的Alex的体育学分还是零蛋！

Alex可不希望被开除，他想知道到期末还有多少天的工作日，这样他就能在这些日子里修体育学分。但是在这里计算工作日可不是件容易的事情：

从现在到学期结束还有 $n$ 天(从 $1$ 到 $n$ 编号)，他们一开始都是工作日。接下来学校的工作人员会**依次**发出 $q$ 个指令，每个指令可以用三个参数 $l,r,k$ 描述：

- 如果 $k=1$，那么从 $l$ 到 $r$ （包含端点）的所有日子都变成**非**工作日。

- 如果 $k=2$，那么从 $l$ 到 $r$ （包含端点）的所有日子都变成**工作日**。

帮助Alex统计每个指令下发后，剩余的工作日天数。

## 样例 #1

### 输入

```
4
6
1 2 1
3 4 1
2 3 2
1 3 2
2 4 1
1 4 2
```

### 输出

```
2
0
2
3
1
4
```

# 题解

## 作者：yzhang (赞：30)

## [更好的阅读](https://www.cnblogs.com/yzhang-rp-inf/p/9775249.html)

#### 原题传送门：[CF915E Physical Education Lessons](https://www.luogu.org/problemnew/show/CF915E)

## 前置芝士：珂朵莉树

### [窝博客里对珂朵莉树的介绍](https://www.cnblogs.com/yzhang-rp-inf/p/9443659.html )

#### 这道题很简单啊

#### 每个操作就是区间赋值0或1，顺带把总和修改一下，跑的飞快

```cpp
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define IT set<node>::iterator
using namespace std;
inline int read() //io优化
{
    register int x=0,f=1;register char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct node
{
    int l,r;
    mutable bool v;
    node(int L, int R=-1, bool V=0):l(L), r(R), v(V) {}
    bool operator<(const node& o) const
    {
        return l < o.l;
    }
};
set<node> s;
int sum=0;
IT split(int pos)
{
    IT it = s.lower_bound(node(pos));
    if (it != s.end() && it->l == pos) 
        return it;
    --it;
    int L = it->l, R = it->r;
    bool V = it->v;
    s.erase(it);
    s.insert(node(L, pos-1, V));
    return s.insert(node(pos, R, V)).first;
}
void assign_val(int l,int r,bool val)
{
    IT itr = split(r+1), itl = split(l), it = itl;
    for( ;itl != itr; ++itl)
        sum-=itl->v*(itl->r-itl->l+1); //过程中顺带计算
    s.erase(it,itr);
    s.insert(node(l,r,val));
    sum+=val*(r-l+1); //过程中顺带计算
}
int main()
{
	int n=read(),m=read();
	s.insert(node(1,n,1));
	sum=n;
	while(m--)
	{
		int l=read(),r=read(),op=read();
		if(op==1) //修改
			assign_val(l,r,0);
		else
			assign_val(l,r,1);
		printf("%d\n",sum); //输出总和
	}
	return 0;
}
```

---

## 作者：Uniecho1 (赞：16)

动态开点线段树

因为天数过多（Alex血条真的厚）显然线段树维护会GG

这个时候就需要动态开点

何为动态开点？？

看一下询问次数与天数的关系，会发现：
### 如果用堆的方式存线段树，会有非常多的点没有被访问而占了空间

所以动态开点，要在点里存储信息才开，否则不开

有Q次操作，每次操作最多涉及logN（也就是一条树链跑完，及操作叶子节点）所以**最多**会用到Q*logN个节点

所以理论上只需要开9*10^6+10个节点就好了......

然而......数据似乎有点锅？？？

......我开了1.6倍才过（手动滑稽）

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int l,r,val;
}T[300005*55];
int root,size,N,Q,lazy[300005*55];
void pushdown(int l,int r,int cur){
	if(lazy[cur]!=-1){
		int m=l+r>>1;
		if(!T[cur].l)T[cur].l=++size;
		if(!T[cur].r)T[cur].r=++size;
		lazy[T[cur].l]=lazy[T[cur].r]=lazy[cur];
		T[T[cur].l].val=lazy[cur]*(m-l+1);
		T[T[cur].r].val=lazy[cur]*(r-m);
		lazy[cur]=-1;
	}
}
void insert(int&cur,int x,int y,int l,int r,int k){
	if(!cur)cur=++size;
	if(x<=l&&r<=y){
		T[cur].val=k*(r-l+1);
		lazy[cur]=k;
		return;
	}
	pushdown(l,r,cur);int m=(l+r)>>1;
	if(x<=m)insert(T[cur].l,x,y,l,m,k);
	if(y>m)insert(T[cur].r,x,y,m+1,r,k);
	T[cur].val=T[T[cur].l].val+T[T[cur].r].val;
}
int main(){
	//freopen("in.txt","r",stdin);
	memset(lazy,-1,sizeof(lazy));
	scanf("%d%d",&N,&Q);
	for(int i=1,l,r,opt;i<=Q;i++){
		scanf("%d%d%d",&l,&r,&opt);
		if(opt==1)insert(root,l,r,1,N,opt);
		else insert(root,l,r,1,N,opt-2);
		printf("%d\n",N-T[root].val);
	}
	return 0;
}
```


---

## 作者：JRzyh (赞：15)

最近在学ODT，讲一下这题ODT解法。

[不会ODT?](http://baidu.apphb.com/?q=%E7%8F%82%E6%9C%B5%E8%8E%89%E6%A0%91)

这题就是一道ODT的板子，操作是推平，查询是求和

Q：这题不保证数据随机为什么还能用ODT?

A：hackODT的方法是没有推平操作，但这题修改操作全是推平操作。

于是暴力很好写，但CF的毒瘤们不会让你过的，故考虑优化。

每次查询区间是一定的，所以就维护一个变量 $sum$ 表示 $1 \rightarrow n$ 的和，再推平时统计，推平区间里有多少个元素值会变化，再根据变成什么修改 $sum$

code:

```
#include<bits/stdc++.h>
#define SIT set<node>::iterator
using namespace std;
int read()
{
    register int x=0,f=1;register char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct node
{
	int l,r;
	mutable long long v;
	node(int L, int R=-1, long long V=0):l(L), r(R), v(V) {}
	bool operator<(const node& o) const{return l < o.l;}
};
set<node>odt;
long long sum;
SIT spilt(int mid)
{
	SIT it=odt.lower_bound(node(mid));
	if(it!=odt.end()&&it->l==mid) return it;
	it--;
	node temp=*it;
	odt.erase(it);
	odt.insert(node(temp.l,mid-1,temp.v));
	return odt.insert(node(mid,temp.r,temp.v)).first;
}
void assign(int l,int r,long long val)
{
	SIT it2=spilt(r+1),it1=spilt(l);
	long long res=0;
	for(SIT it=it1;it!=it2;it++)
	{
		if(it->v!=val)res+=it->r-it->l+1;//一共有多少值会变
	}
	odt.erase(it1,it2);
	odt.insert(node(l,r,val));
	sum+=((val==0)?-res:res);//是加还是减
}
int n,q;
int main()
{
	n=read();q=read();
	odt.insert(node(1,n,1));
	sum=n;
	for(int i=1;i<=q;i++)
	{
		int l=read(),r=read();
		short opt=read();
		if(opt==1)
		{
			assign(l,r,0);
			printf("%d\n",sum);
		}
		else
		{
			assign(l,r,1);
			printf("%d\n",sum);
		}
	}
	return 0;
}
```

$$\text{That~is~all.~Thanks~fo~reading.}$$

↓点个赞吧


---

## 作者：TheShadow (赞：14)

# 闲扯

大佬们都太巨辣！！

题解里面都是用的 $ODT$ 和动态开点线段树，这些我都不会啊 $qwq$ ，所以我选择直接用线段树来做这道题。

# 题面

[CF915E Physical Education Lessons](https://www.luogu.org/problem/CF915E)

# Solution

看到题的第一反应使用线段树维护区间覆盖操作，然后看数据范围，发现是 $10^9$ ，当场懵逼。

想想怎么办。

突然发现 $q\leq 3\cdot10^5$ ，那么涉及到的端点最多只有 $6\cdot10^5$ 个，这个貌似是可以用线段树维护的。

我们用线段树维护两个相邻的端点之间形成的区间，同时维护区间和即可。

然后发现如果直接离散化给出的端点，在 $l=r$ 的情况下会出现 $l>r$ 的情况，所以我们将右端点加 $1$ ，然后每一个线段的长度直接用右端点减左端点即可。

然后对于没有涉及到的我们直接存下来，在输出答案时加上就好。

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
const int MAXN = 6e5+5;
int n,m,s[MAXN],sz,ans;
struct Node{
	int l,r,k;
}node[MAXN>>1];
#define lc (cur<<1)
#define rc (cur<<1|1)
struct Seg_Tree{
	int sum,val,tag;
}T[MAXN<<2];
il pushup(int cur){T[cur].sum=T[lc].sum+T[rc].sum;}
il pushdown(int cur,int l,int r){
	if(T[cur].tag==-1) return ;
	T[lc].tag=T[rc].tag=T[cur].tag;
	if(T[cur].tag==1) T[lc].sum=T[rc].sum=0;
	else T[lc].sum=T[lc].val,T[rc].sum=T[rc].val;
	T[cur].tag=-1;
}
il build_tree(int cur,int l,int r){
	T[cur].tag=-1;
	if(l==r) return T[cur].sum=T[cur].val=s[l+1]-s[l],void();
	build_tree(lc,l,mid),build_tree(rc,mid+1,r);
	pushup(cur),T[cur].val=T[lc].val+T[rc].val;
}
il updata(int cur,int l,int r,int L,int R,int k){
	if(l>=L&&r<=R){
		T[cur].tag=k;
		if(k==1) T[cur].sum=0;
		else T[cur].sum=T[cur].val;
		return ;
	}
	pushdown(cur,l,r);
	if(mid>=L) updata(lc,l,mid,L,R,k);
	if(R>mid) updata(rc,mid+1,r,L,R,k);
	pushup(cur);
}
it id(int x){return lower_bound(s+1,s+1+sz,x)-s;}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(m);
	for(ri i=1;i<=m;++i){
		read(node[i].l),read(node[i].r),read(node[i].k);
		++node[i].r;
		s[++sz]=node[i].l,s[++sz]=node[i].r;
	}
	sort(s+1,s+1+sz),sz=unique(s+1,s+1+sz)-s-1;
	ans=s[1]-1+n-s[sz]+1;
	build_tree(1,1,sz-1);
	for(ri i=1;i<=m;++i){
		ri x=id(node[i].l),y=id(node[i].r)-1;
		updata(1,1,sz-1,x,y,node[i].k);
		print(T[1].sum+ans),puts("");
	}
	return 0;
}
```

# 总结

一道挺裸的线段树的题，只是需要稍微转换一下。

---

## 作者：Ireliaღ (赞：9)

大佬们应该都写的线段树。我因为离散化总写炸，动态开点把握不好既不MLE也不RE的数组大小，只好写了一个Splay。

## 前置知识

~~熟练运(mo)用(gai)Splay~~

其实只要会基本的Splay，会推标记，稍加思考就可以魔改出来

## 本题解法

**~~我们知道，Splay是一种非常万能的数据结构。~~**

这道题的Splay解法是源自[NOIP2017D2T3列队](https://www.luogu.com.cn/problem/P3960)的思路。由于$10 ^ 9$的值域让我们无法把所有节点开出来，考虑到操作数只有$3 \times 10 ^ 5$，我们可以一个节点存储一整段的信息，当需要割裂节点时就割裂开，最后节点数是和操作数同数量级的。

每一个节点存储一下它的左右端点、这一段的值、子树的总和、赋值懒标记，再写一个割裂函数，剩的就是Splay的基本套路了。具体操作如下：

1. 使用割裂函数使$l$成为一个节点的左端点，使$r$成为一个节点的右端点。

2. 把$l - 1$ `Splay`到根，把$r + 1$ `Splay`到根的右儿子。这样得到的，以`ch[ch[rt][1]][0]`为根的子树就是我们需要操作的区间。

3. 把这个节点打上赋值标记就OK了

具体详见代码

```cpp
#pragma GCC optimize("Ofast")
#include <iostream>
#include <cstdio>

using namespace std;
const int MAXN = 4e6;

struct Node{
	Node *fa, *ch[2];
	int l, r, sum, val, asi, len;
	Node() {}
	
	Node(Node *fa, int l, int r, int val) : fa(fa), l(l), r(r), val(val) {
		ch[0] = ch[1] = NULL;
		asi = -1;
		len = r - l + 1;
		sum = val * len;
	}
}npool[MAXN];

Node *rt;
int n, m;
int ncnt;

Node *New(Node *fa, int l, int r, int val) {
	npool[ncnt] = Node(fa, l, r, val);
	return &npool[ncnt++];
}

void PushDown(Node *now) {
	if (now->asi != -1) {
		if (now->ch[0]) {
			now->ch[0]->val = now->asi;
			now->ch[0]->asi = now->asi;
			now->ch[0]->sum = now->asi * now->ch[0]->len;
		}
		if (now->ch[1]) {
			now->ch[1]->val = now->asi;
			now->ch[1]->asi = now->asi;
			now->ch[1]->sum = now->asi * now->ch[1]->len;
		}
		now->asi = -1;
	}
}

void PushAll(Node *now) {
	if (now->fa) PushAll(now->fa);
	PushDown(now);
}

void Update(Node *now) {
	int l = now->l, r = now->r, v = now->val;
	now->len = r - l + 1 + (now->ch[0] ? now->ch[0]->len : 0) + (now->ch[1] ? now->ch[1]->len : 0);
	now->sum = v * (r - l + 1) + (now->ch[0] ? now->ch[0]->sum : 0) + (now->ch[1] ? now->ch[1]->sum : 0);
}

void Rotate(Node *now) {
	Node *fa = now->fa, *anc = fa->fa;
	int d = (now == fa->ch[1]);
	if (anc) anc->ch[fa == anc->ch[1]] = now;
	now->fa = anc;
	fa->fa = now;
	fa->ch[d] = now->ch[!d];
	now->ch[!d] = fa;
	if (fa->ch[d]) fa->ch[d]->fa = fa;
	Update(fa); Update(now);
	if (!now->fa) rt = now;
}

void Splay(Node *now, Node *t) {
	if (!now || now == t) return;
	PushAll(now);
	while (now->fa != t) {
		Node *fa = now->fa, *anc = fa->fa;
		if (anc != t) {
			if ((fa == anc->ch[1]) ^ (now == fa->ch[1])) Rotate(now);
			else Rotate(fa);
		}
		Rotate(now);
	}
}

Node *Find(Node *now, int pos) {
	PushDown(now);
	if (pos < now->l) return Find(now->ch[0], pos);
	else if (pos <= now->r) return now;
	else return Find(now->ch[1], pos);
}

void Split(Node *now, int pos) {//[l, pos) [pos, r]
	PushDown(now);
	int l = now->l, r = now->r, v = now->val;
	Node *lc = now->ch[0];
	if (l == pos) return;
	now->l = pos;
	now->ch[0] = New(now, l, pos - 1, v);
	now->ch[0]->ch[0] = lc;
	if (lc) lc->fa = now->ch[0];
	Update(now->ch[0]); Update(now);
}

void Assign(int l, int r, int v) {
	Split(Find(rt, l), l);
	Split(Find(rt, r + 1), r + 1);
	Splay(Find(rt, l - 1), NULL);
	Splay(Find(rt, r + 1), rt);
	rt->ch[1]->ch[0]->val = v;
	rt->ch[1]->ch[0]->asi = v;
	rt->ch[1]->ch[0]->sum = v * rt->ch[1]->ch[0]->len;
	Update(rt->ch[1]);
	Update(rt);
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m;
	rt = New(NULL, 1, n, 1);
	rt->ch[0] = New(rt, 0, 0, 0);
	rt->ch[1] = New(rt, n + 1, n + 1, 0);
	Update(rt);
	for (int i = 1; i <= m; i++) {
		int op, l, r;
		cin >> l >> r >> op;
		if (op == 1) Assign(l, r, 0);
		else Assign(l, r, 1);
		cout << rt->sum << '\n';
	}
	return 0;
}
/*
4
6
1 2 1
3 4 1
2 3 2
1 3 2
2 4 1
1 4 2
*/
```

~~肯定有铁憨憨拷上面的代码交上去！~~

这样写的话，即使开了`Ofast`也是会TLE的。虽然复杂度是十分稳定的$O(n \log n)$，但是$Splay$的常数是一个顶俩还要多的。只要做过一些题，大家都知道，$Splay$和$LCT$的$\log n$经常被一些小常数的$\log ^ 2 n$吊起来锤。

所以我们需要一些毒瘤的卡常技巧吗？其实不用。

我们考虑一下数据结构常数的决定因素。

1. 工作原理

2. 节点个数

3. 是否有标记的下放

显然$1$是可以放弃治疗了，那么我们在$2$和$3$上下文章。我们通过旋转得到了一个子树代表一个区间，然后要把它赋值。显然可以把它整个扔掉，压成一个新的节点，这样可以大大优化$Splay$在本题的效率。

```cpp
#include <iostream>
#include <cstdio>

using namespace std;
const int MAXN = 4e6;

struct Node{
	Node *fa, *ch[2];
	int l, r, sum, val, len;
	Node() {}
	
	Node(Node *fa, int l, int r, int val) : fa(fa), l(l), r(r), val(val) {
		ch[0] = ch[1] = NULL;
		len = r - l + 1;
		sum = val * len;
	}
}npool[MAXN];

Node *rt;
int n, m;
int ncnt;

Node *New(Node *fa, int l, int r, int val) {
	npool[ncnt] = Node(fa, l, r, val);
	return &npool[ncnt++];
}

void Update(Node *now) {
	int l = now->l, r = now->r, v = now->val;
	now->len = r - l + 1 + (now->ch[0] ? now->ch[0]->len : 0) + (now->ch[1] ? now->ch[1]->len : 0);
	now->sum = v * (r - l + 1) + (now->ch[0] ? now->ch[0]->sum : 0) + (now->ch[1] ? now->ch[1]->sum : 0);
}

void Rotate(Node *now) {
	Node *fa = now->fa, *anc = fa->fa;
	int d = (now == fa->ch[1]);
	if (anc) anc->ch[fa == anc->ch[1]] = now;
	now->fa = anc;
	fa->fa = now;
	fa->ch[d] = now->ch[!d];
	now->ch[!d] = fa;
	if (fa->ch[d]) fa->ch[d]->fa = fa;
	Update(fa); Update(now);
	if (!now->fa) rt = now;
}

void Splay(Node *now, Node *t) {
	if (!now || now == t) return;
	while (now->fa != t) {
		Node *fa = now->fa, *anc = fa->fa;
		if (anc != t) {
			if ((fa == anc->ch[1]) ^ (now == fa->ch[1])) Rotate(now);
			else Rotate(fa);
		}
		Rotate(now);
	}
}

Node *Find(Node *now, int pos) {
	if (pos < now->l) return Find(now->ch[0], pos);
	else if (pos <= now->r) return now;
	else return Find(now->ch[1], pos);
}

void Split(Node *now, int pos) {//[l, pos) [pos, r]
	int l = now->l, r = now->r, v = now->val;
	Node *lc = now->ch[0];
	if (l == pos) return;
	now->l = pos;
	now->ch[0] = New(now, l, pos - 1, v);
	now->ch[0]->ch[0] = lc;
	if (lc) lc->fa = now->ch[0];
	Update(now->ch[0]); Update(now);
}

void Assign(int l, int r, int v) {
	Splay(Find(rt, l), NULL);
	Split(rt, l);
	Splay(Find(rt, r + 1), NULL);
	Split(rt, r + 1);
	Splay(Find(rt, l - 1), NULL);
	Splay(Find(rt, r + 1), rt);
	rt->ch[1]->ch[0] = New(rt->ch[1], l, r, v);//throw away the whole tree
	Update(rt->ch[1]);
	Update(rt);
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m;
	rt = New(NULL, 1, n, 1);
	rt->ch[0] = New(rt, 0, 0, 0);
	rt->ch[1] = New(rt, n + 1, n + 1, 0);
	Update(rt);
	for (int i = 1; i <= m; i++) {
		int op, l, r;
		cin >> l >> r >> op;
		if (op == 1) Assign(l, r, 0);
		else Assign(l, r, 1);
		cout << rt->sum << '\n';
	}
	return 0;
}
/*
4
6
1 2 1
3 4 1
2 3 2
1 3 2
2 4 1
1 4 2
*/
```

---

## 作者：LCuter (赞：6)

这道题真的毒瘤。。数组开小了RE，开大了就MLE,我大概开到$1.5\times 10^7$才卡过去。。当然如果选择神奇的离散化就没有上面的问题了，但是离散化我不想写啊。。只好选择动态开点线段树了

如果不考虑空间的问题，我们的问题实际上是维护一个$01$序列，每次操作会选择一段区间将其赋值为$0/1$，求每次操作完后区间$[1,n]$中$1$的个数。实际上我们发现，如果我们知道$[l,mid]$与$[mid+1,r]$中$1$的个数，那么$[l,r]$中$1$的个数就可以$O(1)$地得出。再看区间赋值操作，如果要更新一个区间，那么就是将该区间中$1$的个数变成$V\times(r-l+1)$，$V$表示赋的值，$l,r$表示该区间的左右端点，于是$\text{Lazy Tag}$是可以应用在上面的。综上，这道题我们可以使用线段树维护区间$1$的个数。在我奇奇怪怪的实现中，我是维护$0$的个数，然后用$n$减去区间中$0$的个数，大概是因为如果要维护$1$的个数的话，一开始比较难处理~~实际上是因为我太菜了~~，具体细节可以看下面的代码

```cpp
#include<bits/stdc++.h>
#define REG register
#define MAXN 300005
using namespace std;
inline int read(){
	REG int x(0);
	REG char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=(x*10)+(c^48),c=getchar();
	return x;
}

int n,q,rt;

struct Segment{
	#define Ls(now) (t[now].ls)
	#define Rs(now) (t[now].rs)
	#define mid ((l+r)>>1)
	int tot;
	struct Tree{
		int val,tag,ls,rs;
	}t[15000005];
	inline void Push_up(int now){t[now].val=t[Ls(now)].val+t[Rs(now)].val;}
	inline void Push_down(int now,int l,int r){
		if(!Ls(now)) Ls(now)=++tot;
		if(!Rs(now)) Rs(now)=++tot;
		t[Ls(now)].val=(t[now].tag-1)*(mid-l+1),t[Ls(now)].tag=t[now].tag;
		t[Rs(now)].val=(t[now].tag-1)*(r-mid),t[Rs(now)].tag=t[now].tag;
		t[now].tag=0;
	}
	void Upd(int& now,int l,int r,int x,int y,int state){
		if(!now) now=++tot;
		if(l>=x&&r<=y) t[now].val=(state-1)*(r-l+1),t[now].tag=state;
		else{
			if(t[now].tag) Push_down(now,l,r);
			if(mid>=x) Upd(Ls(now),l,mid,x,y,state);
			if(mid<y) Upd(Rs(now),mid+1,r,x,y,state);
			Push_up(now);
		}
	}
	int Ask(int now,int l,int r,int x,int y){
		if(!now) return 0;
		if(l>=x&&r<=y) return t[now].val;
		if(t[now].tag) Push_down(now,l,r);
		int ans=0;
		if(mid>=x) ans+=Ask(Ls(now),l,mid,x,y);
		if(mid<y) ans+=Ask(Rs(now),mid+1,r,x,y);
		return ans;
	}
}tree;

int main(){
	n=read(),q=read();
	while(q--){
		int l=read(),r=read(),opt=read();
		if(opt==1){
			tree.Upd(rt,1,n,l,r,2);
			printf("%d\n",n-tree.t[rt].val);
		}
		else{
			tree.Upd(rt,1,n,l,r,1);
			printf("%d\n",n-tree.t[rt].val);
		}
	}
}
```

---

## 作者：fmj_123 (赞：5)

### 动态开点线段树
题目暗示了区间修改，所以我们自然想到了用线段树来维护**非工作日**的天数。

然而我们再看一下数据范围，天数n的范围是$1 \le n \le 10^9$，像普通线段树一样预处理显然会爆空间。

天无绝人之路，我们看一下修改个数，$1\le q \le 3 \cdot 10^5  $， 比天数少很多，这也意味着，我们预先处理好的线段树**有些节点并没有用**

能否优化呢？答案是肯定的，这就是动态开点线段树，顾名思义，我们只要到用某个节点的时候，才分配一个点给它，这样使得我们使用的空间大大减少。其余的与普通线段树大致是相同的。

最后再说一下，本题的数组要开大一些，否则会疯狂$RE$

代码奉上~
```
#include<bits/stdc++.h>
using namespace std;
int tree[15001000],lson[15001000],rson[15001000],tag[15001000],d;
long long n,q,l,r,k;
void freelazy(int x,int l,int r)
{
	int mid=(l+r)/2;
    if (tree[x])
    {
	  tree[lson[x]]=(mid-l+1);
	  tree[rson[x]]=(r-(mid+1)+1);
    }
	else
	{
	  tree[lson[x]]=0;
	  tree[rson[x]]=0;
    }
	tag[lson[x]]=1;
    tag[rson[x]]=1;
    tag[x]=0;
    //正常的懒标记下放操作
}
void add(int x,int l,int r,int ql,int qr,int sd)
{
	
    if (ql<=l&&qr>=r)
    {
        tree[x]=(r-l+1)*sd;tag[x]=1;
        return ;
    }	
    if (!lson[x]) 
    {
        d++;
        lson[x]=d;
    }
    if (!rson[x]) 
    {
        d++;
        rson[x]=d;
    }//要用就开点
    //上面要记得记录左右儿子
	if (tag[x]) freelazy(x,l,r);
    int mid=(l+r)/2;
    if (ql>mid)
    {
        add(rson[x],mid+1,r,ql,qr,sd);
    }
    else
    if (qr<=mid)
    {
        add(lson[x],l,mid,ql,qr,sd);
    }
    else
    {
        add(lson[x],l,mid,ql,mid,sd);
        add(rson[x],mid+1,r,mid+1,qr,sd);
    }
    tree[x]=tree[lson[x]]+tree[rson[x]];
    //正常的线段树操作
}
int main()
{
    cin>>n>>q;d=1;
    for (int i=1;i<=q;i++)
    {
        scanf("%d%d%d",&l,&r,&k);//本题用cin、cout会有超时风险
        if (l>r) swap(l,r);
        if (k==1)
        {
            add(1,1,n,l,r,k);
        }
        else
        {
            add(1,1,n,l,r,0);
        }
        printf("%d\n",n-tree[1]);
    }
    return 0;
}
```

---

## 作者：SuperJvRuo (赞：4)

最近做了很多珂朵莉树的题，一看这题区间赋值操作，直接上珂朵莉树。区间赋值成0和赋值成1都是珂朵莉树最简单的操作。

```
#include<cstdio>
#include<cctype>
#include<set>

int Read()
{
    int x=0;char c=getchar();
    while(!isdigit(c))
    {
        c=getchar();
    }
    while(isdigit(c))
    {
        x=x*10+(c^48);
        c=getchar();
    }
    return x;
}

struct node
{
    int l,r;
    mutable int v;
    node(int L,int R=-1,int V=0):l(L),r(R),v(V) {}
    bool operator <(const node& o) const
    {
        return l<o.l;
    }
};

using std::set;
set<node> s;

int sum;

#define IT set<node>::iterator
IT split(int pos)
{
    IT it=s.lower_bound(node(pos));
    if (it!=s.end()&&it->l==pos)
        return it;
    --it;
    int L=it->l,R=it->r;
    int V=it->v;
    s.erase(it);
    s.insert(node(L,pos-1,V?pos-L:0));
    return s.insert(node(pos,R,V?R-pos+1:0)).first;
}

void assign(int l,int r,int val)
{
    IT itr=split(r+1),itl=split(l);
    for(IT it=itl;it!=itr;++it)
    {
        sum-=it->v;
    }
    s.erase(itl,itr);
    s.insert(node(l,r,val*(r-l+1)));
    sum+=val*(r-l+1);
}

int main()
{
    register int n=Read(),q=Read();
    s.insert(node(1,n,1));
    sum=n;
    int l,r;
    while(q--)
    {
        l=Read(),r=Read();
        assign(l,r,Read()-1);
        printf("%d\n",sum);
    }
    return 0;
}
```

---

## 作者：xukuan (赞：3)

珂朵莉树的小优化

首先裸的珂朵莉树会一直TLE on \#30，那么我们需要优化

我们发现这题只有assign和getsum两种操作，而且getsum的区间一定$[1,n]$。那么我们能否把getsum合并进assign里面呢？

显然是可以的，我们用sum记下当前的和，在每次assign的时候，直接修改sum的值，可以通过此题

代码：

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
using namespace std;

int n,m,sum;

namespace ODT{
	struct node{
		int l,r;
		mutable int val;
		node(int L,int R=-1,int Val=0):l(L),r(R),val(Val){}
		inline bool operator <(const node &x)const{
			return l<x.l;
		}
		#define set_node_it set<node>::iterator
	};
	set<node> s;
	inline set_node_it split(int x){
		set_node_it i=s.lower_bound(node(x));
		if(i!=s.end()&&i->l==x) return i;
		i--;
		int l=i->l,r=i->r,val=i->val;
		s.erase(i);
		s.insert(node(l,x-1,val));
		return s.insert(node(x,r,val)).first;
	}
	inline void assign(int l,int r,int val){
		set_node_it R=split(r+1),L=split(l);
		for(set_node_it i=L; i!=R; i++) sum-=i->val*(i->r-i->l+1);
		s.erase(L,R);
		s.insert(node(l,r,val));
		sum+=val*(r-l+1);
	}
}

int main(){
	scanf("%d %d",&n,&m); sum=n;
	ODT::s.insert(ODT::node(1,n,1));
	while(m--){
		int l,r,op; scanf("%d %d %d",&l,&r,&op);
		if(op==1) ODT::assign(l,r,0);
		if(op==2) ODT::assign(l,r,1);
		printf("%d\n",sum);
	}
	return 0;
}
```

---

## 作者：cyffff (赞：1)

# CF915E Physical Education Lessons
#### [_传送门_](https://www.luogu.com.cn/problem/CF915E)
一道简单的珂朵莉树模板题。
## 思路

珂朵莉树（$ODT$）是一种用 $std::set$ 维护的暴力数据结构，每个节点保存三个值：$l$、$r$、$v$，表示 $l$ 、$r$ 区间的值都为 $v$ ，有**区间推平**操作和**数据随机**时可以使用这种数据结构。

除区间推平，它还可以支持许多其它的操作，如区间加、区间 $k$ 大值、区间 $k$ 次求和等。

回到这道题，它只需要区间推平与区间求和，可以使用珂朵莉树。

如果想更好地理解珂朵莉树，建议去做一下[这道题](https://www.luogu.com.cn/problem/CF896C)，也可以看看其它 $dalao$ 的题解。

## 代码实现
如果直接使用区间求和求每次修改后的值是不行的，#$30$ 会 $\textcolor{#052242}{TLE}$，但是我们不求整段，直接求修改的一段增减了多少，输出即可，加个快读快输就跑得飞快。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pnt pair<int,int>
#define sit set<node>::iterator
struct node{
	int l,r;
	mutable int v;
	node(int L,int R=-1,int V=0):l(L),r(R),v(V){}
	friend bool operator<(const node& a,const node &b){
		return a.l<b.l;
	}
};
set<node>a;
int n,m,l,r,op,ans;
inline int read(){
	char ch=getchar();
	int x=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return x;
}
inline void write(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10^48);
}
inline sit split(int p){
	sit it=a.lower_bound(node(p));
	if(it!=a.end()&&it->l==p){
		return it;
	}
	it--;
	int l=it->l,r=it->r,v=it->v;
	a.erase(it);
	a.insert(node(l,p-1,v));
	return a.insert(node(p,r,v)).first;
}
inline void assign(int l,int r,int val){
	sit itr=split(r+1),itl=split(l);
	for(sit it=itl;it!=itr;it++){
		ans-=(it->r-it->l+1)*it->v;
	}
	ans+=(r-l+1)*val;
	a.erase(itl,itr);
	a.insert(node(l,r,val));
}
signed main(){
	n=read(),m=read();
	a.insert(node(1,n,1));
	ans=n;
	for(int i=1;i<=m;i++){
		l=read(),r=read();
		assign(l,r,read()-1);
		write(ans);
		puts("");
	}
	return 0;
}
/*
Time:5.78s
Memory:23.01MB
*/
```
再见qwq~

---

## 作者：Treaker (赞：1)

$$\color{cornflowerblue}{\mathcal{Treaker}}$$
# 珂朵莉树
其实最开始学珂朵莉树，我是拒绝的，~~因为他看起来时间复杂度并不正确~~，但是它实在是太好用了。

所以学了一发。

感觉简直就是区间覆盖的神器啊（随机数据下）

想学的话可以看一下[这个博客](https://www.cnblogs.com/yzhang-rp-inf/p/9443659.html)


完整代码如下：
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <set>
#define IT set<node>::iterator
using namespace std;
inline int read()
{
	int x = 0 , f = 1;	char ch = getchar();
	while(ch < '0' || ch > '9')	{if(ch == '-')	f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
	return x * f;
}
int n , Q , ans;
struct node
{
	int l , r;
	mutable int val;
	node(int l = 0,int r = -1,int val = 0) : l(l) , r(r) , val(val) {}
	friend bool operator < (const node &a,const node &b) {return a.l < b.l;}
};
set<node> s;
inline IT split(int pos)
{
	IT it = s.lower_bound(node(pos));
	if(it != s.end() && it -> l == pos) return it;
	it --;
	int l = it -> l , r = it -> r;int  val = it -> val;
	s.erase(it);
	s.insert(node(l,pos-1,val));
	return s.insert(node(pos,r,val)).first;
}
inline void assign(int l,int r,int val)
{
	IT itr = split(r+1) , itl = split(l) , it = itl;
	for(;it != itr;it ++) ans -= (it -> r - it -> l + 1) * it -> val;
	s.erase(itl,itr);
	s.insert(node(l,r,val));
	ans += (r - l + 1) * val;
}
int main()
{
	n = read(); Q = read();
	s.insert(node(1,n,1)); s.insert(node(n+1,n+1,0)); ans = n;
	for(int i = 1 , opt , l , r;i <= Q;i ++)
	{
		l = read(); r = read(); opt = read();
		if(opt & 1) assign(l,r,0);
		else assign(l,r,1);
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：万万没想到 (赞：1)

更好的阅读体验，原题传送门：[CF915E Physical Education Lessons](https://www.luogu.org/problemnew/show/CF915E)

因为原题中的操作一共只有3种，两种是区间赋值，剩下的是区间和。

序列的区别：工作日，非工作日，想到了什么？

没错！01序列，区间01赋值操作，又想到了什么？

没错！珂朵莉树（ODT），这种数据结构可以很好的满足我们区间赋值题的要求，由于珂朵莉树基于set，所以时间复杂度在数据随机情况下为O（mlogn），m为操作数，n为序列长度。珂朵莉树的原理及其应用百度上可以很容易搜索到。

在区间赋值的时间优化后，区间和便是暴力的统计了，但是需要在赋值前先统计，统计非工作日再用区间长度减去非工作日，不然会因为常数原因被卡。这个可以参考笔者下面的代码，代码如下：

```cpp
#include<bits/stdc++.h>
#define IT set<node>::iterator
#define LL long long
using namespace std;
inline int read(){
    char c=0;
    int x=0,f=1;
    for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+c-'0';
    x*=f;
    return x;
}
struct node{
    int l,r;
    mutable bool v;
    node(int L,int R=-1,bool V=0):l(L),r(R),v(V) {}
    bool operator<(const node& o) const
    {
        return l<o.l;
    }
};
set<node> s;
IT split(int pos){
    IT it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos) return it;
    --it;
    int L=it->l,R=it->r;
    bool V=it->v;
    s.erase(it);
    s.insert(node(L,pos-1,V));
    return s.insert(node(pos,R,V)).first;
}
int ans;
void assign_val(int l,int r,bool val){
    IT itr=split(r+1),itl=split(l),it=itl;
    while(itl!=itr){
    	ans=ans-itl->v*(itl->r-itl->l+1);
    	++itl;
    }
    s.erase(it,itr);
    s.insert(node(l,r,val));
    ans=ans+val*(r-l+1);   
}
int n,q,l,r,k;
int main(){
    n=read();
    q=read();
    ans=n;
    s.insert(node(1,n,1));
    s.insert(node(n+1,n+1,0));
    for(register int i=1;i<=q;++i){
    	l=read(),r=read(),k=read();
    	assign_val(l,r,k-1);
        printf("%d\n",ans);
    }
    return 0;
}
```


---

## 作者：关怀他人 (赞：0)

# 珂朵莉树板子题
### 不会珂朵莉树的看[yzhang大佬的博客](https://www.cnblogs.com/yzhang-rp-inf/p/9443659.html)
#### 对于每个操作直接区间推平就好了

注意一定要在直接在区间赋值时统计答案，不然会TLE30（~~调了很久~~）

#### AC的程序:
```cpp
/*
Problem : CF 915E
Algorithm : 珂朵莉树 
Status : AC
*/
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <iostream>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
using namespace std;
typedef long long ll;

const int INF = 0x3f3f3f3f;

void read(int &x)
{
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}

void print(int x)
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}

int n,q,sum;

struct Node{
	int l,r; //左右端点
	mutable int v;//这个区间的值
	Node(int x,int y = -1,int val = 0) : l(x),r(y),v(val) {}
	friend bool operator < (const Node &x,const Node &y){
		return x.l < y.l; //按左端点排序
	}
};

set<Node> s;

auto split(int pos){ //分裂操作，我偷懒用了auto
	auto it = s.lower_bound(Node(pos));
	if(it != s.end() && it->l == pos)
	    return it;
	it--;
	int l = it->l,r = it->r,v = it->v;
	s.erase(it);
	s.insert(Node(l,pos - 1,v));
	return s.insert(Node(pos,r,v)).first;
}

void assignVal(int l,int r,int val){ //区间赋值
	auto itr = split(r + 1),itl = split(l),it = itl; //注意这里一定要先split右端点，再split左端点，不然下标会出错
	for(;itl != itr;itl++)
	    sum -= itl->v * (itl->r - itl->l + 1); //直接统计答案
	s.erase(it,itr);
	s.insert(Node(l,r,val));
	sum += val * (r - l + 1); //直接统计答案
}

int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n);
	read(q);
	sum = n;
   	//0表示非工作日，1表示工作日
	s.insert(Node(1,n,1)); //开始全为工作日
	while(q--){
		int l,r,op;
		read(l);
		read(r);
		read(op);
		if(op == 1) 
		    assignVal(l,r,0); //将l-r变为非工作日
		else
		    assignVal(l,r,1); //将l-r变为工作日
		print(sum);
		puts("");
	}
	return 0;
}

```



---

