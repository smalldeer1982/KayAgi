# [USACO04OPEN] Cave Cows 2

## 题目描述

洞窟里有一道长长的通道．它由 $ N $ ( $ 1 \leq N \leq 25000 $ )段道尾相连构成，编号分别为 $ 1 \ldots N $ 。

每个通道有一个阈值，其范围在 $ [1,10^9] $ 。依次通过 $ i \ldots j $ 的通道，那奶牛的体重指数就不能超过 $ i \ldots j $ 通道中阈值的最小值。贝茜有 
$ Q $ ( $ 1 \leq Q \leq 25000 $ )个问题，想请教你由 $ i $ 到 $ j $ 的通道的阈值的最小值。

## 样例 #1

### 输入

```
10 4
75
30
100
38
50
51
52
20
81
5
1 10
3 5
6 9
8 10```

### 输出

```
5
38
20
5```

# 题解

## 作者：LJC00118 (赞：8)

看到 Venus 的题解写道：首先排除Treap Splay这种根本不可能用于这题的东西

所以我们来用 $ Splay $ 来做这题

$ Splay $ 可以简单的提取出一个区间，如果要提取出 $ [l, r] $ 这个区间，我们先 $ splay (root, r + 1) $，此时 $ root $ 的左孩子是区间 $ [1, r] $，然后我们 $ splay (root -> leftson, l - 1) $，此时 $ root $ 的左孩子的右孩子是区间 $ [l, r] $，我们在节点上维护区间最小值即可

当然如果直接 $ splay (root, r + 1) $ 可能会出锅，如果 $ l = 1 \ \&\&\ r = n$，$ splay (root, r + 1 ) $ 可能会导致 $ RE $，所以我们在最左边和最右边放一个节点，改成 $ splay (root, r + 2) $ 后 $ splay (root -> leftson, l) $ 即可

```cpp
#include <bits/stdc++.h>
#define CIOS ios::sync_with_stdio(false);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> ";
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename T>
inline void read(T &f) {
	f = 0; T fu = 1; char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') fu = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
	f *= fu;
}

template <typename T>
void print(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + 48);
	else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
	print(x); putchar(t);
}

struct Node {
	Node *ch[2];
	int size, val, minn;
	
	Node (int a, int b, int c, Node *d, Node *e) : size(a), val(b), minn(c) { ch[0] = d; ch[1] = e; }
}*root, *null;

void update(Node *u) {
	u -> size = 1; u -> minn = u -> val;
	u -> size += u -> ch[0] -> size, u -> minn = min(u -> minn, u -> ch[0] -> minn);
	u -> size += u -> ch[1] -> size, u -> minn = min(u -> minn, u -> ch[1] -> minn);
}

void rotate(Node *&u, int d) {
	Node *tmp = u -> ch[d];
	u -> ch[d] = tmp -> ch[d ^ 1];
	tmp -> ch[d ^ 1] = u;
	update(u); update(tmp);
	u = tmp;
}

void splay(Node *&u, int k) {
	int ltree = u -> ch[0] -> size;
	if(ltree + 1 == k) return;
	int d = k > ltree, k2 = d ? k - ltree - 1 : k;
	int ltree2 = u -> ch[d] -> ch[0] -> size;
	if(ltree2 + 1 != k2) {
		int d2 = k2 > ltree2;
		splay(u -> ch[d] -> ch[d2], d2 ? k2 - ltree2 - 1 : k2);
		if(d == d2) rotate(u, d); else rotate(u -> ch[d], d2);
	}
	rotate(u, d);
}

int a[25005], n, m;
Node *build(int l, int r) {
	if(l > r) return null;
	if(l == r) return new Node(1, a[l], a[r], null, null);
	int mid = (l + r) >> 1; Node *t = new Node(1, a[mid], a[mid], build(l, mid - 1), build(mid + 1, r));
	return update(t), t;
}

int main() {
	null = new Node(0, 1e9, 1e9, 0, 0);
	read(n); read(m);
	for(register int i = 1; i <= n; i++) read(a[i]);
	root = build(0, n + 1); 
	while(m--) {
		int l, r; read(l); read(r);
		splay(root, r + 2);
		splay(root -> ch[0], l);
		print(root -> ch[0] -> ch[1] -> minn, '\n');
	} 
	return 0;
}
```

---

## 作者：VenusM1nT (赞：5)

今天初学树套树，突然想起来这道题似乎可以用树套树来做，然后自己写的线段树套 $\text{FHQ}$ 就光荣地 $\text{T}$ 了 $1$ 个点，开 $O2$ 可以 $\text{AC}$，或者套别的平衡树应该可以 $\text{AC}$，代码仅供娱乐。

```cpp
#include<bits/stdc++.h>
#define MAXN 25005
#define MAXM 5000005
#define inf 2147483647
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
using namespace std;
struct FHQTreap
{
	int son[2],val,siz,key;
}t[MAXM];
int n,Q,a[MAXN],siz;
template <typename T> void Read(T &x)
{
	x=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar());
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch-48);
}
struct FHQ_Treap
{
	int root;
	int NewNode(int val)
	{
		t[++siz].siz=1;
		t[siz].key=rand();
		t[siz].val=val;
		return siz;
	}
	void Update(int rt)
	{
		t[rt].siz=t[t[rt].son[0]].siz+t[t[rt].son[1]].siz+1;
	}
	int Merge(int x,int y)
	{
		if(!x || !y) return x+y;
		if(t[x].key<t[y].key)
		{
			t[x].son[1]=Merge(t[x].son[1],y);
			Update(x);
			return x;
		}
		else
		{
			t[y].son[0]=Merge(x,t[y].son[0]);
			Update(y);
			return y;
		}
	}
	void Split(int rt,int pos,int &x,int &y)
	{
		if(!rt) x=y=0;
		else
		{
			if(t[rt].val<=pos)
			{
				x=rt;
				Split(t[rt].son[1],pos,t[rt].son[1],y);
			}
			else
			{
				y=rt;
				Split(t[rt].son[0],pos,x,t[rt].son[0]);
			}
			Update(rt);
		}
	}
	void Build(int x,int y)
	{
		for(int i=x;i<=y;i++) Insert(a[i]);
	}
	void Insert(int val)
	{
		int x,y;
		Split(root,val,x,y);
		root=Merge(Merge(x,NewNode(val)),y);
	}
	int FindRak(int val)
	{
		int x,y,res;
		Split(root,val-1,x,y);
		res=t[x].siz+1;
		root=Merge(x,y);
		return res;
	}
}fhq[MAXN<<2];
void BuildSegmentTree(int rt,int l,int r)
{
	fhq[rt].Build(l,r);
	if(l==r) return;
	int mid=l+r>>1;
	BuildSegmentTree(rt<<1,l,mid);
	BuildSegmentTree(rt<<1|1,mid+1,r);
}
int QueryRak(int rt,int l,int r,int tl,int tr,int val)
{
	if(tl<=l && r<=tr) return fhq[rt].FindRak(val)-1;
	int mid=l+r>>1,res=0;
	if(tl<=mid) res+=QueryRak(rt<<1,l,mid,tl,tr,val);
	if(tr>mid) res+=QueryRak(rt<<1|1,mid+1,r,tl,tr,val);
	return res;
}
int QueryVal(int x,int y,int rk)
{
	int l=0,r=inf/20,res=-1;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(QueryRak(1,1,n,x,y,mid)+1<=rk)
		{
			res=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	return res;
}
int main()
{
	Read(n);
	Read(Q);
	for(int i=1;i<=n;i++) Read(a[i]);
	BuildSegmentTree(1,1,n);
	while(Q--)
	{
		int x,y;
		Read(x);
		Read(y);
		printf("%d\n",QueryVal(x,y,1));
	}
	return 0;
}
```

---
首先，和区间操作有关，容易让人想到的是**线段树**，但这题仅有查询，而没有修改，那么我们就很容易想到 $\text{ST}$ **表**，当然，既然和这两个东西扯上关系了，**树状数组**也是可以做的，所以我就无聊的写了三份……

至于怎么做这都是模板级别的问题了……

上代码

 - 线段树 （$80ms\quad 1.3MB\quad 0.82KB$）

```cpp
#include<bits/stdc++.h>
#define inf 1010580540
using namespace std;
int n,Q,a[25005],val[25005<<2];
void BuildSegmentTree(int rt,int l,int r)
{
	if(l==r)
	{
		val[rt]=a[l];
		return;
	}
	int mid=l+r>>1;
	BuildSegmentTree(rt<<1,l,mid);
	BuildSegmentTree(rt<<1|1,mid+1,r);
	val[rt]=min(val[rt<<1],val[rt<<1|1]);
}
int Query(int rt,int l,int r,int tl,int tr)
{
	if(l>=tl && tr>=r) return val[rt];
	int mid=l+r>>1,res=inf;
	if(tl<=mid) res=min(res,Query(rt<<1,l,mid,tl,tr));
	if(tr>mid) res=min(res,Query(rt<<1|1,mid+1,r,tl,tr));
	return res;
}
int main()
{
	memset(a,60,sizeof(a));
	memset(val,60,sizeof(val));
	scanf("%d %d",&n,&Q);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	BuildSegmentTree(1,1,n);
	while(Q--)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		printf("%d\n",Query(1,1,n,x,y));
	}
	return 0;
}
```

 - $ST$表 （$64ms\quad 2.73MB\quad 0.49KB$）
 
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int f[25][25005];
int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&f[0][i]);
    for(int i=1;i<=21;i++)
    {
        for(int j=1;j+(1<<i)-1<=n;j++)
        {
            f[i][j]=min(f[i-1][j],f[i-1][j+(1<<(i-1))]);
        }
    }
    for(int i=1,x,y;i<=m;i++)
    {
        scanf("%d %d",&x,&y);
        int t=log2(y-x+1);
        printf("%d\n",min(f[t][x],f[t][y-(1<<t)+1]));
    }
    return 0;
}
```

 - 树状数组 （$90ms\quad 0.91MB\quad 0.62KB$）
 
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,Q,a[25005],c[25005];
int lowbit(int x)
{
	return x&-x;
}
void Modify(int x,int num)
{
	while(x<=n)
	{
		c[x]=min(c[x],num);
		x+=lowbit(x);
	}
}
int Query(int l,int r)
{
	int res=a[r];
	while(l<=r)
	{
		res=min(res,a[r]);
		r--;
		while(r-l>=lowbit(r))
		{
			res=min(res,c[r]);
			r-=lowbit(r);
		}
	}
	return res;
}
int main()
{
	memset(c,60,sizeof(c));
	scanf("%d %d",&n,&Q);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		Modify(i,a[i]);
	}
	while(Q--)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		printf("%d\n",Query(x,y));
	}
	return 0;
}
```

---

## 作者：C20212724杨京朝 (赞：3)

看到大佬们用什么树套树，Splay，分块，ST表，主席树，我只好躲在一旁观望，毕竟只会线段树而且还有人码了，但是——
### 我还会暴力
------------
这是多么振奋人心的一声呐喊啊，咳咳，言归正传，我们先分析一下暴力的时间复杂度，最坏的话O(n ^ 2),最好的话大概是O(n),显然没什么用，不过不如类比一下P1816忠诚，就改了一下题面和输出格式而已，而忠诚纯暴力有90，这题的数据范围只有20000，难度也可想而知。

------------
既然都决定要水暴力了，那就不要犹豫了，代码：1.86s，勉强能过
```cpp
#include <cstdio>
#include <algorithm>
using namespace std; 
int a[100005];
int main() {
	int n,k,ans = 1e9,x,y;//ans即答案，求最小值时把初值定义为极大值，很常用的技巧
	scanf("%d %d",&n,&k);
	for(int i = 1;i <= n;i ++) scanf("%d",&a[i]);//输入都会吧？
	for(int i = 1;i <= k;i ++) {
		scanf("%d %d",&x,&y);
		for(int i = x;i <= y;i ++) ans = min(a[i],ans);//对区间遍历一遍	
        	//这里貌似必须把区间遍历完，原因：区间无序（这里貌似是个暗示？）
		printf("%d\n",ans);//输出
		ans = 1e9;//重新赋值！！！
	}
	return 0;
}
```
------------
都说了有暗示了：不妨将区间变为有序序列，说白了就是sort噻，这是一个逆向思维，之前是在区间中找最小值，现在是在最小值中找在这个区间的数。
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#define RET register int
#define LL long long 
#define MAXN 50005
using namespace std;
int n,m;
struct node {
	int s;
	int num;
}a[MAXN];
bool cmp(node x,node y) {
	return x.s < y.s;
}
int main() {
	scanf("%d %d",&n,&m);
	for(RET i = 1;i <= n;i ++) scanf("%d",&a[i].s),a[i].num = i;//输入并存下当前这个数的位置：排序会打乱顺序
	sort(a + 1,a + n + 1,cmp);
	for(RET i = 1;i <= m;i ++) {
		int x,y;
		scanf("%d %d",&x,&y);
		for(RET j = 1;j <= n;j ++) 
			if(a[j].num >= x && a[j].num <= y) {
				cout << a[j].s << endl;//找到了就是最优解，直接退出循环
				break;
			}//见上文
	}
	return 0;
}
```
这份代码还挺快的：130ms，不知道这个玄学为什么能快这么多，评论区求解，或许因为数据？

------------
最后再贴份线段树，楼下的童鞋已经讲得很清楚了，80ms：
```cpp
#include <cstdio> 
#include <algorithm>
using namespace std;
const int MAXN = 100005;
int a[MAXN],tree[MAXN * 4],cnt;
void build(int now,int l,int r) {
	if(l == r) {
		cnt ++;
		tree[now] = a[cnt];
	}
	else {
		int mid = (l + r) / 2;
		build(now * 2,l,mid);
		build(now * 2 + 1,mid + 1,r);
		tree[now] = min(tree[now * 2],tree[now * 2 + 1]); 
	}
}
int look_up(int now,int l,int r,int x,int y) {
	int ans = 1e9;
	if(x <= l && y >= r) {
		ans = tree[now];
	}
	else {
		int mid = (l + r) / 2;
		if(x <= mid) ans = min(ans,look_up(now * 2,l,mid,x,y));
		if(y > mid) ans = min(ans,look_up(now * 2 + 1,mid + 1,r,x,y));
	}
	return ans;
} 
int main() {
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i = 1;i <= n;i ++) scanf("%d",&a[i]);
	build(1,1,n);
	for(int i = 1;i <= m;i ++) {
		int x,y;
		scanf("%d %d",&x,&y);
		printf("%d\n",look_up(1,1,n,x,y));
	}
	return 0;
}
```



---

## 作者：ahawzlc (赞：3)

~~线段树解区间求值最好了！~~

----
## 简介：

线段树是一种用于区间求值的数据结构，基于二叉树，下面我简单介绍一下在本题中用于求最值的线段树：

线段树主要是承担$\Theta(n\log n)$区间（单点）修改和区间（单点）查询。

线段树示意图：

![4.8tj1.png](https://i.loli.net/2020/04/08/a2j8OGsecRiBbwt.png)

## 操作：

### $update$
更新操作，是建树（$build$）和修改（$change$（本题中用不到））后更新线段树数值的操作。

### $build$
建树操作，具体见代码

### $ask$
询问操作，参考示意图。假如我们要求区间$[2,5]$的最值，我们可以把区间拆成$[2],[3,4],[5]$然后递归求。设要求$[x,y]$的最值，那么只要是满足$[x\le l,r\le y]$的节点，都可以纳入答案。我们不用递归到单点，如果有整段的，可以直接拿来用，这就是线段树的精髓罢。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=1000000007;
int va[25005];
struct linetree {
	int l,r,sum;//结构体，本节点维护l——r的最值，sum为本节点的数值
} tree[125005];
void update(int now,int lson,int rson) {//与模板最不同的地方就是这里了
	tree[now].sum=min(tree[lson].sum,tree[rson].sum);//当前节点是左右孩子的最小值
}
void build(int now,int l,int r) {//建树，now为当前节点编号
	tree[now].l=l;
	tree[now].r=r;
	if(l==r) {
		tree[now].sum=va[l];
		return;
	}
	int mid=(l+r)>>1;
	int lson=now<<1;//将左孩子定到2*now位置
	int rson=now<<1|1;//右孩子定到2*now+1位置
	build(lson,l,mid);//继续向下建树
	build(rson,mid+1,r);//同上
	update(now,lson,rson);//递归回来更新当前节点
}
int sum=MAXN;
void ask(int now,int x,int y) {//区间求最值
	if(x<=tree[now].l&&y>=tree[now].r) {//只要满足这个条件，就可以将它作为某段区间纳入答案
		sum=min(sum,tree[now].sum);
		return;
	}//见注释的解释
	int l=tree[now].l,r=tree[now].r;
	int mid=(l+r)>>1;
	int lson=now<<1;
	int rson=now<<1|1;//意义与建树是一样
	if(x<=mid) ask(lson,x,y);//运用二分原理
	if(y>mid) ask(rson,x,y);
}
signed main() {
	int n,m;
	cin>>n>>m;
	for(int i=1; i<=n; i++)
		cin>>va[i];
	build(1,1,n);//可以参考示例图
	for(int i=1; i<=m; i++) {
		int x,y;
		cin>>x>>y;
		sum=MAXN;
		ask(1,x,y);
		cout<<sum<<endl;
	}
	return 0;
}
```

---

## 作者：shuiyuhan (赞：3)

这题好像没有pascal题解哦，那我来水一发

题目描述：求序列中一段区间的最小值

显然用线段树做啊！
```pascal
代码：
uses math;//math库是个好东西
var
  i,j,n,k,m,ans,p,mid,x,y,id,t:longint;
  a,tree:array[0..4000009] of longint;
  f:boolean;
procedure build(p,l,r:longint);//建树
var
  mid:longint;
begin
  if (l=r) then begin tree[p]:=a[l]; exit; end;
  mid:=(l+r) div 2;
  build(p*2,l,mid);
  build(p*2+1,mid+1,r);
  tree[p]:=min(tree[p+p],tree[p+p+1]);
end;
function query(p,l,r,x,y:longint):longint;//查询
var
  mid:longint;
begin
  mid:=(l+r) div 2;
  if (l=x)and(r=y) then exit(tree[p])
  else if y<=mid then exit(query(p*2,l,mid,x,y))
  else if x>mid then exit(query(p*2+1,mid+1,r,x,y))
  else exit(min(query(p*2,l,mid,x,mid),query(p*2+1,mid+1,r,mid+1,y)));
end;
begin
  readln(n,m);
  for i:=1 to n do readln(a[i]);
  build(1,1,n);
  for i:=1 to m do
  begin
    readln(x,y);
    writeln(query(1,1,n,x,y));
  end;
end.
```

---

## 作者：He_Ren (赞：2)

[P5097 [USACO2004OPEN]Cave Cows 2 洞穴里的牛之二](https://www.luogu.org/problemnew/show/P5097)



## 题意简述

$n$个数，$q$次询问，每次询问$[i,j]$的最小值



## 分析

静态区间最小值，一看就是st表的模板题。

所以我们选择用主席树（大雾）实现区间第$k$大

## 代码

加了一些基本的注释~~凑字数~~

毕竟各位看官都不是学主席树来的对吧

安利一篇@bestFy 大佬的[$\large blog$](https://blog.csdn.net/bestFy/article/details/78650360)（大家可以在P3834 【模板】可持久化线段树 1（主席树）的[题解](https://www.luogu.org/problemnew/solution/P3834)里找到）

本蒟蒻初学主席树，有坑的话不要揍我$\text{QAQ}$

```cpp
#include<cstdio>
#include<algorithm>
const int MAXN = 25000 + 5;
const int N = MAXN * 24;
using namespace std;

int root[MAXN];
int pcnt=0,ans[N],ls[N],rs[N];

void build(int &u,int l,int r)//建树
{
	u=++pcnt;
	if(l==r) return;
	int mid = (l+r)>>1;
	build(ls[u],l,mid);
	build(rs[u],mid+1,r);
}

void update(int &u,int v,int l,int r,int p)//修改
{
	u=++pcnt;
	ans[u] = ans[v] + 1;
	if(l==r) return;
	
	ls[u]=ls[v]; rs[u]=rs[v];
	int mid = (l+r)>>1;
	if(p<=mid) update(ls[u],ls[v],l,mid,p);
	else update(rs[u],rs[v],mid+1,r,p);
}

int query(int u,int v,int l,int r)//查询第k小（因为k=1所以把k省掉了qwq）
{
	if(l==r) return l;
	int mid = (l+r)>>1;
	if(ans[ls[v]]-ans[ls[u]]) return query(ls[u],ls[v],l,mid);//因为k=1,左边有数就去左边
	else return query(rs[u],rs[v],mid+1,r);
}

int a[MAXN],b[MAXN];

int main(void)
{
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]), b[i]=a[i];
	//离散化
	sort(b+1,b+n+1);
	int m=unique(b+1,b+n+1)-(b+1);
	build(root[0],1,m);
	
	for(int i=1; i<=n; ++i)
		update(root[i],root[i-1],1,m, lower_bound(b+1,b+m+1, a[i])-b );
	
	while(q--)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%d\n",b[ query(root[l-1],root[r], 1,m) ]);
	}
	return 0;
}
```

求赞qwq

---

## 作者：AveMarina (赞：0)

## 线段树的一个小技巧
**关于线段树：它被评论区的神犇们说的很明白了~~所以我就不多说了~~**

那么正题是我在标题提到的小技巧，这个技巧可以用来**节省大量空间和部分码量**。我们思考下普通线段树的建树过程，它的所有父节点的值都是由**叶子节点决定的**，而我们为了在建树的过程中对叶子节点赋值，一般会选择**先将原序列保存下来，再等到递归到叶子节点时赋值上去。** 可以发现，这个过程完全不是必须的，**与其把原序列存起来等到走到叶子节点再赋值，还不如直接在走到叶子节点时将值输入进去。**

## 板子
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 25000 * 4 + 10;
struct Node {
	int l, r, mn;
} root[N];
void pushup(int now) {
	root[now].mn = min(root[now << 1].mn, root[now << 1 | 1].mn);
}
void build(int now, int l, int r) {
	root[now].l = l, root[now].r = r;
	if (l == r) {
		// 本篇题解的核心内容：直接输入叶子节点的值以达到节省空间和减少码量的目的 
		scanf("%d", &root[now].mn);
		return;
	}	
	int mid = (l + r) >> 1;
	build(now << 1, l, mid);
	build(now << 1 | 1, mid + 1, r);
	pushup(now);
}
int query(int now, int L, int R) {
	if (L <= root[now].l && root[now].r <= R) return root[now].mn;
	if (L > root[now].r || R < root[now].l) return 1e9;
	int mid = (root[now].l + root[now].r) >> 1;
	return min(query(now << 1, L, R), query(now << 1 | 1, L, R));
}
int main() {
	int n, m, l, r;
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	while (m--) scanf("%d%d", &l, &r), printf("%d\n", query(1, l, r));
	return 0;
} 
```
~~写的好啰嗦的样子，明明一句话能说明白的...~~

---

## 作者：PragmaGCC (赞：0)

图论做多了看啥都是图嘛……

第一眼看过去：
> 想请教你由 $i$ 到 $j$ 的通道的阈值的最小值

~~啥玩意？最短路？~~

咳咳，言归正传。

读题发现，这道题就是让我们求区间最小值。

再看一看，没有要求进行修改？

那好啊！女少口阿！

上来就是ST表啊！
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, st[100005][20];//2^19足够了
int read()//快读
{
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * w;
}
int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
    {
        int num = read();
        st[i][0] = num;//输入
    }
    for (int j = 1; j <= 19; j++)
    {
        for (int i = 1; i <= n - (1 << j) + 1; i++)
        {
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);//预处理
        }
    }
    for (int i = 1; i <= m; i++)
    {
        int l = read(), r = read();
        int e = log2(r - l + 1);//还记得当年我把log2写成log的惨案
        printf("%d\n", min(st[l][e], st[r - (1 << e) + 1][e]));//查询
    }
    return 0;
}
```

---

## 作者：_Ayanami_ (赞：0)

dalao们都打了树状数组线段树什么的

然而其实直接把点sort一遍然后找到第一个在区间里的就能A

数据比较水
用时只有53ms
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
struct node//结构体
{
	int v,s;
}
a[25001];
int n,m,l,r;
bool cmp(node x,node y)
{
	return x.v<y.v;//从小到大排序
}
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;++i)
	{
		scanf("%d",&a[i].v);//通道阀值
		a[i].s=i;//记录通道编号
	}
	sort(a+1,a+n+1,cmp);
	while(m--)
	{
		scanf("%d%d",&l,&r);
		for(register int i=1;i<=n;++i)
		{
			if(l<=a[i].s&&a[i].s<=r)//判断是否在区间内
			{
				printf("%d\n",a[i].v);
				break;
			}
		}
	}
}
```

---

## 作者：DrunkXT (赞：0)

线段树什么的，写起来费神。

于是我就用了树状数组（好东西啊）。

具体讲树状数组的文章网上太多了，我在这里不多赘述。

不要以为树状数组只能求和！！

但我对树状数组掌握也不算很好。

在这里介绍求最大最小值方法，

话不多说，从代码入手：

```cpp
void add(int ii,int x)
{
	for(int i=ii;i<=n;i+=lowbit(i))
		minn[i]=min(x,minn[i]);
	return;
}
```
插入，和一般的树状数组差不多吧。

```
int minx(int l,int r)
{
	int mi=1<<30;
	while(l<=r)
	{
		for(;r-lowbit(r)>=l;r-=lowbit(r))
			mi=min(minn[r],mi);
		mi=min(mi,a[r]);
		r--;
	}
	return mi;
}
```
关键在这里，由于不是每个区间都维护到了，所以需要这句r--多次处理。（其他都是标配吧）

具体细节自己模拟感受可能更深，也更能理解。

我就直接放完整代码了：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;
int n;
int q;
int a[MAXN];
int minn[MAXN];
int lowbit(int x)
{
	return x&(-x);
}
void add(int ii,int x)
{
	for(int i=ii;i<=n;i+=lowbit(i))
		minn[i]=min(x,minn[i]);
	return;
}
int minx(int l,int r)
{
	int mi=1<<30;
	while(l<=r)
	{
		for(;r-lowbit(r)>=l;r-=lowbit(r))
			mi=min(minn[r],mi);
		mi=min(mi,a[r]);
		r--;
	}
	return mi;
}
int main()
{
	scanf("%d",&n);
	scanf("%d",&q);
	for(int i=0;i<MAXN;i++)
		minn[i]=1<<30;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		add(i,a[i]);
	}
	for(int i=1;i<=q;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%d\n",minx(l,r));
	}
	return 0;
}
```

代码格式不好看，请原谅

---

## 作者：两年打铁 (赞：0)

这种静态区间的查询问题，还是最小值，$O(1)$ 查询，它就是
# ST表
ST表的思想是类似于倍增的，即$f[i][j]$ 表示从j这个点向右$2^i$ 的区间的最小值

那么我们建表就可以像倍增一样直接求个min

建表nlogn 查询O(1)

有模板题，详见[P3865 【模板】ST表](https://www.luogu.org/problemnew/show/P3865)

```
#include<bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
const int big=0x7fffffff;
using namespace std;
inline void read(int &x)
{
    x=0;char ch=getchar();int pd=1;
    while(ch<'0'||ch>'9'){if(ch=='-')pd=-pd;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    x*=pd;
}
inline void write(const int &x)
{
    char ggg[10001];int s=0;int tmp=x;
    if(tmp==0){putchar('0');return;}
    if(tmp<0){tmp=-tmp;putchar('-');}
    while(tmp>0){ggg[s++]=tmp%10+'0';tmp/=10;}
    while(s>0){putchar(ggg[--s]);}
}

int n,q,f[22][25010];
inline int query(int l,int r)
{
	int k=log2(r-l+1);//注意+1防止RE
	return min(f[k][l],f[k][r-(1<<k)+1]);
}

int main()
{
	read(n);
	read(q);
	for(register int i=1;i<=n;++i)
	{
		read(f[0][i]);
	}
    
    //这里是建表的过程
	for(register int j=1;j<=20;++j)
	{
		for(register int i=1;i+(1<<(j-1))<=n;++i)
		{
			f[j][i]=min(f[j-1][i],f[j-1][i+(1<<(j-1))]);
		}
	}
	while(q--)
	{
		int l,r;
		read(l);
		read(r);
		write(query(l,r));
		puts("");
	}
	return 0;
}

```


---

## 作者：寒冰大大 (赞：0)

初略地看了一下，貌似没有C++er用线段树来做的

不过这道题用线段树做也好容易理解的

于是来一发。


```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<queue>
#include<vector>
#include<stack>
#include<algorithm>
#include<string>

using namespace std;

int n,m;

struct tree{
    int l,r,min;
}t[100860];

int a[25965];

void build_tree(int i,int l,int r)
{
    if(l==r)
    {
        t[i].min=a[l]; //l=r的时候，这个过程必然是从线段树左边到右边（因为先l后r因此直接满足顺序来了就ok了）
        return ;
    }
    int mid=(l+r)/2;
    build_tree(i*2,l,mid);  /
    build_tree(i*2+1,mid+1,r);
    t[i].min=min(t[i*2].min,t[i*2+1].min);
    return ;
}

int ask_min_tree(int i,int l,int r,int a,int b)
{
    if(a<=l&&r<=b) return t[i].min;  //这是我认为的比较好理解的一种方式，当l和r在ab之间就返回，看见过一些毒瘤写法，感觉这样比较好
    int mid=(l+r)/2;
    int ans=0x3f3f3f3f;
    if(a<=mid) ans=min(ask_min_tree(i*2,l,mid,a,b),ans);
    if(b>mid) ans=min(ask_min_tree(i*2+1,mid+1,r,a,b),ans);
    return ans;  //如果没有ans出来，那么返回一个极大值，不影响答案
}

int main()
{
    int i,j;
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    build_tree(1,1,n); //直接建树
    for(i=1;i<=m;i++)
    {
        int t1,t2;
        scanf("%d %d",&t1,&t2);
        printf("%d\n",ask_min_tree(1,1,n,t1,t2));
    }
    return 0;
}
```


---

