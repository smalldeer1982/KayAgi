# [ABC265G] 012 Inversion

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc265/tasks/abc265_g

各要素が $ 0,1,2 $ のいずれかである長さ $ N $ の数列 $ A=(A_1,\ldots,A_N) $ が与えられます。  
 $ Q $ 個のクエリを順に処理してください。各クエリは以下の $ 2 $ 種類のいずれかです。

- `1 L R`：数列 $ (A_L,\ldots,A_R) $ の転倒数を出力する
- `2 L R S T U`： $ L\leq\ i\ \leq\ R $ を満たす各 $ i $ について、$ A_i $ が $ 0 $ なら $ S $ に、$ 1 $ なら $ T $ に、$ 2 $ なら $ U $ に置き換える
 
転倒数とは？ 数列 $ B\ =\ (B_1,\ \ldots,\ B_M) $ の転倒数とは、整数の組 $ (i,\ j) $ $ (1\ \leq\ i\ であって\ B_i\ >\ B_j $ を満たすものの個数です。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ A_i\ \leq\ 2 $
- $ 1\leq\ Q\leq\ 10^5 $
- 各クエリにおいて、$ 1\leq\ L\ \leq\ R\ \leq\ N $
- $ 2 $ 種類目のクエリにおいて、$ 0\leq\ S,T,U\ \leq\ 2 $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

最初 $ A=(2,0,2,1,0) $ です。 - $ 1 $ 番目のクエリにおいて、$ (A_2,A_3,A_4,A_5)=(0,2,1,0) $ の転倒数 $ 3 $ を出力します。 - $ 2 $ 番目のクエリを処理すると、$ A=(2,2,0,1,0) $ となります。 - $ 3 $ 番目のクエリにおいて、$ (A_2,A_3,A_4,A_5)=(2,0,1,0) $ の転倒数 $ 4 $ を出力します。

## 样例 #1

### 输入

```
5 3
2 0 2 1 0
1 2 5
2 2 4 2 1 0
1 2 5```

### 输出

```
3
4```

## 样例 #2

### 输入

```
3 3
0 1 2
1 1 1
2 1 3 0 0 0
1 1 3```

### 输出

```
0
0```

# 题解

## 作者：DaiRuiChen007 (赞：7)

# ABC265G 题解



## 思路分析

思路比较简单，区间修改区间查询的数据结构第一时间想到线段树。

考虑对于线段树上的每一个节点，维护 $cnt_x$ 表示每个 $x$ 在对应区间里出现的个数，维护 $inv_{x,y}$ 表示区间中出现 $a_i=x,a_j=y$ 且 $i<j$ 的数对数量。

每次修改维护一个关于 $\{0,1,2\}$ 的置换（这里的置换定义不太严谨，不一定是 $0,1,2$ 的一个排列，只是表示 $0,1,2$ 最后欧分别会变成什么元素）的 Lazy Tag，打标记的时候只需要暴力置换 ${0,1,2}$ 的值。

每次回答答案的时候输出所有 $x>y$ 的 $inv_{x,y}$ 的和即可。

时间复杂度 $\Theta(nw^2\log n)$，$w$ 为 $\{a_i\}$ 的值域。

## 代码呈现

下面具体分析一下如何让代码更加清晰：

首先，我们对 Lazy Tag 设立一个结构体 `Record`，用数组 `p[3]` 维护置换 $\{0,1,2\}\gets \{p_0,p_1,p_2\}$：

```cpp
struct Record {
	int p[3]
};
```

接下来，我们要实现一个 `Record` 的构造函数，其中默认的构造函数应该是 $\{p_i\}=\{0,1,2\}$，并且支持构造一个题目中给出的 $\{p_i\}=\{s,t,u\}$ 的标记：

```cpp
struct Record {
	/* Funciton Before */
	Record() { p[0]=0,p[1]=1,p[2]=2; }
	Record(int s,int t,int u) { p[0]=s,p[1]=t,p[2]=u; }
};
```

为了调用方便，我们可以重载 `[]` 运算符，用 `tag[i]` 代替 `tag.p[i]`，从而减少码量：

```cpp
struct Record {
	/* Funciton Before */
	inline int& operator [](const int &i) { return p[i]; }
};
```

由于我们要支持在一轮置换的基础上再进行一轮置换，因此我们可以重载 `+` 运算符，用 `tag1+tag2` 表示先进行 `tag1` 代表的置换，然后再进行 `tag2` 代表的置换：

```cpp
struct Record {
	/* Funciton Before */
	inline friend Record operator +(Record org,Record add) {
		return Record(add[org[0]],add[org[1]],add[org[2]]);
	}
};
```



接下来，我们实现维护每个线段树信息的 `Node` 结构体。

首先，一个 `Node` 结构体要维护 `inv[3][3]` 和 `cnt[3]` 的信息，代表的含义如题所示，同时维护一个 `Record` 结构体表示当前区间对应的 Lazy Tag：

```cpp
struct Node {
	int inv[3][3],cnt[3];
	Record tag; 
};
```

接下来实现构造函数，除了默认的空区间外，我们要在线段树建立的过程中求叶子结点的值，即区间 $[x,x]$，此时 $inv_{x,y}$ 全为 $0$，而  $cnt_{a_x}$ 为 $1$ 其余为 $0$：

```cpp
struct Node {
	/* Funciton Before */
	Node() { memset(inv,0,sizeof(inv)),memset(cnt,0,sizeof(cnt)); }
	Node(int k) { memset(inv,0,sizeof(inv)),memset(cnt,0,sizeof(cnt));++cnt[k];	}
};
```

由于线段树在维护过程中要不断进行 Push Up，因此我们可以重载 `+` 运算符来维护合并左右区间后得到的结果。

此时 $cnt_x$ 直接是左右区间的 $cnt_x$ 之和。

$inv_{x,y}$ 统计的满足 $a_i=x,a_j=y$ 的数对 $(a_i,a_j)$ 数量有三种：

- $a_i,a_j$ 都在左区间，贡献为左区间 $inv_{x,y}$ 的值。
- $a_i$ 在左区间，$a_j$ 在右区间，贡献为左区间 $cnt_x$ 的值乘上右区间 $cnt_y$ 的值。
- $a_i,a_j$ 都在右区间，贡献为右区间 $inv_{x,y}$ 的值。

按照上述过程维护合并操作即可：

```cpp
struct Node {
	/* Funciton Before */
	inline friend Node operator +(Node L,Node R) {
		Node A;
		for(int i:{0,1,2}) A.cnt[i]=L.cnt[i]+R.cnt[i];
		for(int i:{0,1,2}) {
			for(int j:{0,1,2}) {
				if(i==j) continue;
				A.inv[i][j]=L.inv[i][j]+L.cnt[i]*R.cnt[j]+R.inv[i][j];
			}
		}
		return A;
	}
};
```

接下来，在修改操作和线段树 Push Down 的时候，需要不断在一个原有的 `Node` 节点上进行一次置换，暴力执行一个由 `Record` 维护的置换即可：

```cpp
struct Node {
	/* Funciton Before */
	inline void add(Record op) {
		Node ret;
		tag=tag+op;
		for(int i:{0,1,2}) for(int j:{0,1,2}) ret.inv[op[i]][op[j]]+=inv[i][j];
		for(int i:{0,1,2}) for(int j:{0,1,2}) inv[i][j]=(i==j)?0:ret.inv[i][j];
		for(int i:{0,1,2}) ret.cnt[op[i]]+=cnt[i];
		for(int i:{0,1,2}) cnt[i]=ret.cnt[i];
	}
};
```

最后还要统计一个区间对应的 `Node` 节点的答案，实现一个成员函数维护即可：

```cpp
struct Node {
	/* Funciton Before */
	inline int calc() {
		int ret=0;
		for(int i:{0,1,2}) for(int j:{0,1,2}) if(i>j) ret+=inv[i][j];
		return ret;
	}
};
```

最后就是线段树模板和主函数了，这部分的实现比较简单，各位自行完成即可，完整代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+1;
struct Record {
	int p[3];
	Record() { p[0]=0,p[1]=1,p[2]=2; }
	Record(int s,int t,int u) { p[0]=s,p[1]=t,p[2]=u; }
	inline int& operator [](const int &i) { return p[i]; }
	inline friend Record operator +(Record org,Record add) {
		return Record(add[org[0]],add[org[1]],add[org[2]]);
	}
};
struct Node {
	int inv[3][3],cnt[3];
	Record tag; 
	Node() { memset(inv,0,sizeof(inv)),memset(cnt,0,sizeof(cnt)); }
	Node(int k) { memset(inv,0,sizeof(inv)),memset(cnt,0,sizeof(cnt));++cnt[k];	}
	inline friend Node operator +(Node L,Node R) {
		Node A;
		for(int i:{0,1,2}) A.cnt[i]=L.cnt[i]+R.cnt[i];
		for(int i:{0,1,2}) {
			for(int j:{0,1,2}) {
				if(i==j) continue;
				A.inv[i][j]=L.inv[i][j]+L.cnt[i]*R.cnt[j]+R.inv[i][j];
			}
		}
		return A;
	}
	inline void add(Record op) {
		Node ret;
		tag=tag+op;
		for(int i:{0,1,2}) for(int j:{0,1,2}) ret.inv[op[i]][op[j]]+=inv[i][j];
		for(int i:{0,1,2}) for(int j:{0,1,2}) inv[i][j]=(i==j)?0:ret.inv[i][j];
		for(int i:{0,1,2}) ret.cnt[op[i]]+=cnt[i];
		for(int i:{0,1,2}) cnt[i]=ret.cnt[i];
	}
	inline int calc() {
		int ret=0;
		for(int i:{0,1,2}) for(int j:{0,1,2}) if(i>j) ret+=inv[i][j];
		return ret;
	}
};
int n,q,a[MAXN];
class SegmentTree {
	private:
		Node tree[MAXN<<2];
		inline int left(int x) { return x<<1; }
		inline int right(int x) { return x<<1|1; }
		inline void pushup(int pos) { tree[pos]=tree[left(pos)]+tree[right(pos)]; }
		inline void pushdown(int pos) {
			tree[left(pos)].add(tree[pos].tag);
			tree[right(pos)].add(tree[pos].tag);
			tree[pos].tag=Record();
		}
	public:
		inline void Build(int l=1,int r=n,int pos=1) {
			if(l==r) {
				tree[pos]=Node(a[l]);
				return ;
			}
			int mid=(l+r)>>1;
			Build(l,mid,left(pos));
			Build(mid+1,r,right(pos));
			pushup(pos);
			return ;
		}
		inline void Modify(int ul,int ur,Record k,int l=1,int r=n,int pos=1) {
			if(ul<=l&&r<=ur) {
				tree[pos].add(k);
				return ;
			}
			pushdown(pos);
			int mid=(l+r)>>1;
			if(ul<=mid) Modify(ul,ur,k,l,mid,left(pos));
			if(mid<ur) Modify(ul,ur,k,mid+1,r,right(pos));
			pushup(pos);
		}
		inline Node Query(int ul,int ur,int l=1,int r=n,int pos=1) {
			if(ul<=l&&r<=ur) return tree[pos];
			pushdown(pos);
			int mid=(l+r)>>1;
			if(ur<=mid) return Query(ul,ur,l,mid,left(pos));
			if(mid<ul) return Query(ul,ur,mid+1,r,right(pos));
			return Query(ul,ur,l,mid,left(pos))+Query(ul,ur,mid+1,r,right(pos));
		}
}	S;
signed main() {
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	S.Build();
	while(q--) {
		int op;
		scanf("%lld",&op);
		if(op==1) {
			int l,r;
			scanf("%lld%lld",&l,&r);
			printf("%lld\n",S.Query(l,r).calc());
		}
		if(op==2) {
			int l,r,s,t,u;
			scanf("%lld%lld%lld%lld%lld",&l,&r,&s,&t,&u);
			S.Modify(l,r,Record(s,t,u));
		}
	}
	return 0;
}
```



---

## 作者：Epoch_L (赞：5)

## Solution
区间修改和区间查询，考虑线段树。

由于所有数 $\in\{0,1,2\}$，对于一个区间，维护以下信息：

+ $ans(i,j)$ 表示形如 $(i,j)$ 这样的逆序对。

+ $sum(i)$ 表示数字 $i$ 出现的个数。

+ $s,t,u$ 的 $tag$ 标记。

上传标记很简单，$sum$ 就直接加，$ans(i,j)$ 就是左区间 $ans$ 和右区间 $ans$ 和左区间 $sum(i)$ 乘右区间 $sum(j)$。

```cpp
void pushup(int p){
  for(int i=0;i<3;i++)sum[p][i]=sum[ls[p]][i]+sum[rs[p]][i];
  for(int i=0;i<3;i++)for(int j=0;j<3;j++)
    ans[p][i][j]=ans[ls[p]][i][j]+ans[rs[p]][i][j]+1ll*sum[ls[p]][i]*sum[rs[p]][j];
}
```

主要是怎么处理标记，注意到原序列 $0\to s,1\to t,2\to u$，仅仅涉及到一个交换的问题，只需要开一个临时变量，然后将其赋回来即可。

```cpp
tmp[0]=s;tmp[1]=t;tmp[2]=u;
for(int i=0;i<3;i++){
  a[tmp[i]]+=sum[p][i];//注意是+，因为没有保证 s,t,u 互不相等
  for(int j=0;j<3;j++)res[tmp[i]][tmp[j]]+=ans[p][i][j];
}
for(int i=0;i<3;i++)sum[p][i]=a[i];
for(int i=0;i<3;i++)for(int j=0;j<3;j++)ans[p][i][j]=res[i][j];
```

下传标记要注意，并非直接覆盖，例如原来有 $tags=1$，现在多一个 $tagt=2$，等价于 $tags=2$。也就是说我们得看上一次变成了什么，结合代码理解。

```cpp
tags[p]=tmp[tags[p]];
tagt[p]=tmp[tagt[p]];
tagu[p]=tmp[tagu[p]];//tmp 的定义同上一段代码
```

查询就是将多个区间合并，区间内的直接加 $ans$，跨区间的需要记一下前面的区间出现了多少个 $1,2$，然后将能产生贡献的数乘起来加入答案即可。

## Code
细节多，有点难写，2.78KB 成功压到了 99 行。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using ull=unsigned long long;
inline void read(int &x){
  char ch=getchar();
  int r=0,w=1;
  while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
  while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
  x=r*w;
}
const int N=1e5+7;
int n,q,x,lst1,lst2;
ll ss;
struct seg_tree{
  int root,tot,sum[N*4][3],tags[N*4],tagt[N*4],tagu[N*4],ls[N*4],rs[N*4];
  ll ans[N*4][3][3];
  void pushup(int p){
    for(int i=0;i<3;i++)sum[p][i]=sum[ls[p]][i]+sum[rs[p]][i];
    for(int i=0;i<3;i++)for(int j=0;j<3;j++)
      ans[p][i][j]=ans[ls[p]][i][j]+ans[rs[p]][i][j]+1ll*sum[ls[p]][i]*sum[rs[p]][j];
  }
  void update(int p,int s,int t,int u){
    int a[3],tmp[3];
    ll res[3][3];
    for(int i=0;i<3;i++)a[i]=0;
    for(int i=0;i<3;i++)for(int j=0;j<3;j++)res[i][j]=0;
    tmp[0]=s;tmp[1]=t;tmp[2]=u;
    for(int i=0;i<3;i++){
      a[tmp[i]]+=sum[p][i];
      for(int j=0;j<3;j++)res[tmp[i]][tmp[j]]+=ans[p][i][j];
    }
    for(int i=0;i<3;i++)sum[p][i]=a[i];
    for(int i=0;i<3;i++)for(int j=0;j<3;j++)ans[p][i][j]=res[i][j];
    if(tags[p]==-1)tags[p]=s,tagt[p]=t,tagu[p]=u;
    else{
      tags[p]=tmp[tags[p]];
      tagt[p]=tmp[tagt[p]];
      tagu[p]=tmp[tagu[p]];
    }
  }
  void pushdown(int p){
    update(ls[p],tags[p],tagt[p],tagu[p]);
    update(rs[p],tags[p],tagt[p],tagu[p]);
    tags[p]=tagt[p]=tagu[p]=-1;
  }
  void pre(int &p,int l=1,int r=n){
    if(!p)p=++tot;
    if(l==r){read(x),sum[p][x]++;return;}
    int mid=l+r>>1;
    pre(ls[p],l,mid);pre(rs[p],mid+1,r);
    pushup(p);tags[p]=tagt[p]=tagu[p]=-1;
  }
  void modify(int &p,int ql,int qr,int s,int t,int u,int l=1,int r=n){
    if(!p)p=++tot;
    if(ql<=l&&r<=qr){
      update(p,s,t,u);
      return;
    }
    if(tags[p]!=-1)pushdown(p);
    int mid=l+r>>1;
    if(ql<=mid)modify(ls[p],ql,qr,s,t,u,l,mid);
    if(qr>mid)modify(rs[p],ql,qr,s,t,u,mid+1,r);
    pushup(p);
  }
  ll query(int &p,int ql,int qr,int l=1,int r=n){
    if(!p)p=++tot;
    if(ql<=l&&r<=qr){
      ss+=lst2*(sum[p][0]+sum[p][1]);
      ss+=lst1*sum[p][0];
      lst1+=sum[p][1];lst2+=sum[p][2];
      return ans[p][2][0]+ans[p][2][1]+ans[p][1][0];
    }
    if(tags[p]!=-1)pushdown(p);
    int mid=l+r>>1;
    ll tmp=0;
    if(ql<=mid)tmp+=query(ls[p],ql,qr,l,mid);
    if(qr>mid)tmp+=query(rs[p],ql,qr,mid+1,r);
    return tmp;
  }
}tr;
int main(){
  read(n);read(q);tr.pre(tr.root);
  while(q--){
    int op,l,r,s,t,u;read(op);read(l);read(r);
    if(op==1){
      ss=lst1=lst2=0;
      printf("%lld\n",tr.query(tr.root,l,r)+ss);
    }
    else read(s),read(t),read(u),tr.modify(tr.root,l,r,s,t,u);
  }
  return 0;
}
```

---

## 作者：LinkWish (赞：1)

因为值只有 $0,1,2$，所以可以直接使用线段树维护一个区间内的信息 $cnt_i$ 和  $c_{i,j}(i\ne j)$ 分别代表区间内 $i$ 的个数和区间内满足 $a_x=i,a_y=j,x<y$ 的二元组 $(x,y)$ 的数量。

区间合并时，设左区间为 $lc$，右区间为 $rc$，结果为 $x$。

显然，

$x_{num_i}=lc_{num_i}+rc_{num_i}$

$x_{c_{i,j}}=lc_{c_{i,j}}+rc_{c_{i,j}}+lc_{num_i}\times rc_{num_j}$

对于题目中的 $0,1,2$ 之间的相互转换，我们可以对于每个节点维护一个 $f_i$ 表示 $i$ 变成了 $f_i$。所以每次更改的时候我们需要重新计算一下。设原先节点信息为 $x$，计算后的信息为 $y$，则

$y_{num_i}=\sum\limits_{j=0}^2 [f_j=i]\times x_{num_j}$

$y_{c_{i,j}}=\sum\limits_{k=0}^2\sum\limits_{l=0}^2[k\ne l]\times[f_k\ne f_l]\times[f_k=i]\times[f_l=j]\times x_{c_{i,j}}$

$y_{f_i}=f_{y_{f_i}}$

标记的下传直接用上述的三个式子即可，在下传后记得 $x_{f_i}:=i(0\leq i \leq 2)$。

程序只给出主体部分，主要是前面一部分的模板有一些影响观感，而且给出主体已经能够辅助理解。

```cpp
//Linkwish's code
const int N=100005;
struct node{
	int pos[3];
	int num[3];
	int c[3][3];
	inline node(){
		for(int i=0;i<3;i++)pos[i]=i;
		memset(num,0,sizeof num);
		memset(c,0,sizeof c);
	}
}t[N<<2];
int n,m;
int a[N];
inline int ls(int x){return x<<1;}
inline int rs(int x){return x<<1|1;}
inline node merge(node x,node y){
	node res;
	for(int i=0;i<3;i++)res.num[i]=x.num[i]+y.num[i];
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(i==j)continue;
			res.c[i][j]=x.c[i][j]+y.c[i][j]+x.num[i]*y.num[j];
		}
	}
	return res;
}
inline void trans(node &x,int *f){
	node tmp;
	for(int i=0;i<3;i++){
		tmp.num[f[i]]+=x.num[i];
		tmp.pos[i]=f[x.pos[i]];
	}
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(i==j||f[i]==f[j])continue;
			tmp.c[f[i]][f[j]]+=x.c[i][j];
		}
	}
	x=tmp;
}
inline void push_down(int x){
	trans(t[ls(x)],t[x].pos);
	trans(t[rs(x)],t[x].pos);
	for(int i=0;i<3;i++)t[x].pos[i]=i;
}
void build(int x,int l,int r){
	if(l==r){
		t[x].num[a[l]]=1;
		return ;
	}
	int mid=(l+r)>>1;
	build(ls(x),l,mid);
	build(rs(x),mid+1,r);
	t[x]=merge(t[ls(x)],t[rs(x)]);
}
void modify(int x,int l,int r,int L,int R,int *f){
	if(l>=L&&r<=R){
		trans(t[x],f);
		return ;
	}
	push_down(x);
	int mid=(l+r)>>1;
	if(L<=mid)modify(ls(x),l,mid,L,R,f);
	if(R>mid)modify(rs(x),mid+1,r,L,R,f);
	t[x]=merge(t[ls(x)],t[rs(x)]);
}
node ask(int x,int l,int r,int L,int R){
	if(l>=L&&r<=R)return t[x];
	push_down(x);
	int mid=(l+r)>>1;
	node res;
	if(L<=mid)res=ask(ls(x),l,mid,L,R);
	if(R>mid)res=merge(res,ask(rs(x),mid+1,r,L,R));
	return res;
}
signed main(){
	read(n),read(m);
	for(int i=1;i<=n;i++)read(a[i]);
	build(1,1,n);
	int op,x,y;
	int g[3],ans;
	node res;
	while(m--){
		read(op),read(x),read(y);
		if(op==1){
			res=ask(1,1,n,x,y),ans=0;
			for(int i=1;i<3;i++)
				for(int j=i-1;~j;j--)
					ans+=res.c[i][j];
			writeln(ans);
		}
		else{
			for(int i=0;i<3;i++)read(g[i]);
			modify(1,1,n,x,y,g);
		}
	}
	return 0;
}
```


---

## 作者：yqr123YQR (赞：0)

板板题。
### 题意
维护值域为 $\{0,1,2\}$ 的序列，支持操作：
- 修改：将给定区间 $[l,r]$ 内的 $0,1,2$ 分别替换为给定的 $s,t,u$；
- 查询：求给定区间 $[l,r]$ 的逆序对数。

### 思路
值域很小，所以完全可以维护出 $\forall i,j\in\{0,1,2\}$ 的 $(i,j)$ 数对出现的数量 $p_{i,j}$（前一个数出现的位置比后一个数出现的位置更靠前），以及 $0/1/2$ 各自出现的次数 $cnt_{0/1/2}$。

——这不直接线段树？

- 维护

考虑数对 $(i,j)$ 的数量，只能由 $3$ 种累积而成：
1. 左区间原有的：就是左儿子维护的 $(i,j)$ 数量；
2. 右区间原有的：就是右儿子维护的 $(i,j)$ 数量；
3. 一左一右的：因为数对中的 $i$ 在左区间，$j$ 在右区间，互不影响。由乘法原理，可以直接算左儿子记录的 $cnt_i$ 乘右儿子记录的 $cnt_j$，即为该情况的方案。

$cnt$ 的修改较简单，不加叙述。
- 修改

可以直接在节点上维护 $tag_{0/1/2}$，分别表示 $0/1/2$ 会被替换成什么值。`pushdown` 时将每种数对 $(i,j)$ 的数量累积进新的 $p_{tag_i,tag_j}$ 就行，$cnt$ 同理。

~~只要不像蠢猪笨牛一样，`pushdown` 时把左右儿子节点的标记给覆盖了就行。~~
### 代码
```cpp
#include<stdio.h>
#include<ctype.h>
#include<memory.h> 
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 100000;
namespace IO {
	const int bufsize = 230005;
	static char obuf[bufsize], *p3 = obuf, *p4 = obuf + bufsize;
	char gtchar()
	{
		static char buf[bufsize], *p1 = buf, *p2 = buf;
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufsize, stdin), p1 == p2)? EOF: *p1++;
	}
	void flush() {fwrite(obuf, 1, p3 - obuf, stdout), p3 = obuf;}
	void ptchar(char ch)
	{
		if(p3 == p4) flush();
		*p3++ = ch;
	}
	void write(ll x)
	{
		if(x < 0) ptchar('-'), x = -x;
		if(x > 9) write(x / 10);
		ptchar(x - x / 10 * 10 ^ 48);
	}
	ll read()
	{
		ll ret = 0;
		char ch = gtchar();
		bool f = false;
		while(!isdigit(ch)) f = ch == '-', ch = gtchar();
		while(isdigit(ch)) ret = (ret << 3) + (ret << 1) + (ch ^ 48), ch = gtchar();
		return f? -ret: ret;
	}
}
using IO::read;
using IO::write;
int n, m, a[maxn + 5];
struct segment_tree {
	struct node {
		ll p[3][3];
		int cnt[3], tag[3];
		void init() {
			for(int i = 0; i <= 2; i++)
			{
				cnt[i] = 0, tag[i] = i;
				for(int j = 0; j <= 2; j++) p[i][j] = 0;
			}
		}
		friend node operator + (node a, node b) {
			node ret;
			for(int i = 0; i <= 2; i++)
			{
				ret.cnt[i] = a.cnt[i] + b.cnt[i], ret.tag[i] = i;
				for(int j = 0; j <= 2; j++) ret.p[i][j] = a.p[i][j] + b.p[i][j] + (ll) a.cnt[i] * b.cnt[j];//每种数对，要么由左右区间自己提供，要么就是横跨左右区间。
			}
			return ret;
		}
	}tr[maxn * 4 + 5];
	#define l(k) k << 1
	#define r(k) k << 1 | 1
	void build(int k, int sl, int sr) {
		tr[k].init();
//		for(int i = 0; i <= 2; i++) tr[k].tag[i] = i;
		if(sl == sr) return tr[k].cnt[a[sl]] = 1, void();
		int mid = sl + sr >> 1;
		build(l(k), sl, mid), build(r(k), mid + 1, sr);
		pushup(k);
	}
	void change(int k, int s, int t, int u) {
		int ncnt[3], to[3] = {s, t, u};
		ll np[3][3];
		memset(ncnt, 0, sizeof ncnt);
		memset(np, 0, sizeof np);
		for(int i = 0; i <= 2; i++)
		{
			ncnt[to[i]] += tr[k].cnt[i];
			for(int j = 0; j <= 2; j++) np[to[i]][to[j]] += tr[k].p[i][j];
		}
		memcpy(tr[k].cnt, ncnt, sizeof ncnt);
		memcpy(tr[k].p, np, sizeof np);
		for(int i = 0; i <= 2; i++) tr[k].tag[i] = to[tr[k].tag[i]];
	}
	void pushdown(int k) {
		int s = tr[k].tag[0], t = tr[k].tag[1], u = tr[k].tag[2];
		change(l(k), s, t, u), change(r(k), s, t, u);
		for(int i = 0; i <= 2; i++) tr[k].tag[i] = i; 
	}
	void pushup(int k) {tr[k] = tr[l(k)] + tr[r(k)];}
	void modify(int k, int sl, int sr, int ql, int qr, int s, int t, int u) {
		if(ql <= sl && sr <= qr) return change(k, s, t, u);
		int mid = sl + sr >> 1;
		pushdown(k);
		if(ql <= mid) modify(l(k), sl, mid, ql, qr, s, t, u);
		if(qr > mid) modify(r(k), mid + 1, sr, ql, qr, s, t, u);
		pushup(k);
	}
	node query(int k, int sl, int sr, int ql, int qr) {
		if(ql <= sl && sr <= qr) return tr[k];
		int mid = sl + sr >> 1;
		node ret;
		ret.init();
		pushdown(k);
		if(ql <= mid) ret = query(l(k), sl, mid, ql, qr);
		if(qr > mid) ret = ret + query(r(k), mid + 1, sr, ql, qr);
		return ret;
	}

	void print(int k, int sl, int sr) {
		if(sl == sr)
		{
			for(int i = 0; i <= 2; i++) if(tr[k].cnt[i]) printf("%d(%d)", i, tr[k].cnt[i]);
			printf(" ");
			return;
		}
		int mid = sl + sr >> 1;
		pushdown(k);
		print(l(k), sl, mid), print(r(k), mid + 1, sr);
	}
	#undef l
	#undef r
}tree;
ll solve(segment_tree::node t)
{
	ll ret = t.p[1][0] + t.p[2][1] + t.p[2][0];
//	for(int i = 1; i <= 2; i++) for(int j = 0; j < i; j++) ret += t.p[i][j];
	return ret;
}
int main()
{
// 	freopen("array.in", "r", stdin);
// 	freopen("array.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	tree.build(1, 1, n);
	for(int i = 1, op, l, r, s, t, u; i <= m; i++)
	{
		op = read(), l = read(), r = read();
		if(op == 1) write(solve(tree.query(1, 1, n, l, r))), IO::ptchar('\n');
		else s = read(), t = read(), u = read(), tree.modify(1, 1, n, l, r, s, t, u);
//		tree.print(1, 1, n), puts("====");
	}
	IO::flush();
	return 0;
}
/*
5 5
2 1 0 2 1
1 2 4
1 1 5
2 1 4 1 1 1
1 2 4
1 1 5
*/
```

---

