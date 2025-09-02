# Stone Age Problem

## 题目描述

数组 $a$ 有 $n$ 个元素，需要进行 $q$ 次操作。

操作1：将第 $i$ 号元素改为 $x$

操作2：将数组中所有元素改为 $x$

每次操作完成后，输出当前数组中所有元素的总和。

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
1 1 5
2 10
1 5 11
1 4 1
2 1```

### 输出

```
19
50
51
42
5```

# 题解

## 作者：_lfxxx_ (赞：6)

### 题意
给出一个 $n$ 个数的序列 $a$，$q$ 次修改，格式如下。

- `1 i x` 将 $a_i$ 变为 $x$ 即 $a_i\gets x$。
- `2 x` 将序列所有数变为 $x$。

每次询问后输出所有数的和即 $\displaystyle\sum_{i=1}^na_i$。

数据范围：$1\le n,q\le2\times10^5,1\le a_i,x\le10^9$。
### 思路
显然可以线段树，$O(n+q\log n)$ 解决。

这里提供一个 $O(n+q)$ 且码量小的方法。

记 $t_i$ 为 $a_i$ 最后修改的时间（第几次操作），$T$ 为 $2$ 操作最后的时间。

$1$ 操作可以通过比较时间计算和的变化，$2$ 操作和就为 $n\times x$。

最后，一定要开 `long long`。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace solution{
#define ll long long
constexpr int N=2e5+5;
int a[N],t[N],tag,T=-1;
void main(){
#ifdef IAKIOI
	freopen("in.txt","r",stdin);
#endif
	int n,q,op,x,y;
	ll sum=0;
	cin>>n>>q;
	for(int i=1;i<=n;++i)
		cin>>a[i],sum+=a[i];
	for(int i=1;i<=q;++i){
		cin>>op>>x;
		if(op==1){
			cin>>y;
			sum+=y-(t[x]>T?a[x]:tag);
			t[x]=i,a[x]=y;
		}
		else
			tag=x,T=i,sum=(ll)n*x;
		cout<<sum<<'\n';
	}
}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return solution::main(),0;
}

```


---

## 作者：Engulf (赞：3)

维护一个序列 $a$，要求支持两种操作：

1. 给定 $i,x$，将 $a_i$ 修改为 $x$；
2. 给定 $x$，将整个数组修改为 $x$。

求出每次操作后整个数组的值。

本题涉及区间操作，可以使用线段树来维护。

关于线段树的原理，此处不会详解，因为已有[模板题](https://www.luogu.com.cn/problem/P1253)（含有区间覆盖的线段树）的存在。

```cpp
// author: TMJYH09
// create time: 2022/05/15 00:13:22
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,q;
int a[200005];
struct seg{
    int l,r;
    int sum,cov;
}tr[200005<<2];
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
inline void pushup(int p){tr[p].sum=tr[ls(p)].sum+tr[rs(p)].sum;}
void build(int p,int l,int r){
    tr[p].l=l;tr[p].r=r;
    if(l==r){tr[p].sum=a[l];return;}
    int mid=l+r>>1;
    build(ls(p),l,mid);
    build(rs(p),mid+1,r);
    pushup(p);
}
void pushdown(int p){
    if(tr[p].cov){
        tr[ls(p)].cov=tr[rs(p)].cov=tr[p].cov;
        tr[ls(p)].sum=(tr[ls(p)].r-tr[ls(p)].l+1)*tr[p].cov;
        tr[rs(p)].sum=(tr[rs(p)].r-tr[rs(p)].l+1)*tr[p].cov;
        tr[p].cov=0;
    }
}
void modify(int p,int x,int k){
    if(tr[p].l==tr[p].r){
        tr[p].cov=tr[p].sum=k;return;
    }
    pushdown(p);
    int mid=tr[p].l+tr[p].r>>1;
    if(x<=mid)modify(ls(p),x,k);
    else modify(rs(p),x,k);
    pushup(p);
}
void cover(int p,int l,int r,int k){
    if(l<=tr[p].l&&tr[p].r<=r){
        tr[p].cov=k;
        tr[p].sum=(tr[p].r-tr[p].l+1)*k;
        return;
    }
    pushdown(p);
    int mid=tr[p].l+tr[p].r>>1;
    if(l<=mid)cover(ls(p),l,r,k);
    if(mid<r)cover(rs(p),l,r,k);
    pushup(p);
}

signed main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(1,1,n);
    while(q--){
        int t;
        cin>>t;
        if(t==1){
            int i,x;cin>>i>>x;modify(1,i,x);
        }else{
            int x;cin>>x;cover(1,1,n,x);
        }
        cout<<tr[1].sum<<endl;
    }
    return 0;
}
```

---

## 作者：sickbot (赞：1)

## 题意
给你一个长度为 $n(n \le 2 \times 10^5)$ 的序列和 $q(q \le 2 \times 10^5)$ 个询问，询问格式为：

```
1 i x
```
或
```
2 x
```
其中第一种表示把下标为 $i$ 的元素改为 $k$ ，第二种表示把所有元素改成 $x$ 。
每次修改后都要输出该数组的所有元素之和。
## 思路
首先，我们可以记录所有元素的和，此处设为 
$\textbf{sum}$ 。

另外，用 $\textbf{set}$ 记录所有满足
* 在一次整体修改（询问二）后单独修改（询问一）的元素

的下标。特别地，一开始所有元素都在其中。

则对于查询二，我们只需要把 $\textbf{sum}$ 改为 $x \times n$ 即可，同时清空 $\textbf{set}$ ；

对于查询一，我们可以看此下标是否在 $\textbf{set}$ 中，若不在，则该元素修改前即是上一次查询二中的 $x$ 值，同时把其下标加入 $\textbf{set}$ ，并修改它在数组中的值；

否则，这个元素修改前的值就是在数组中记录的值。

如果不好理解，可以配合代码食用。

~~本题其实是裸的[线段树](https://oi-wiki.org/ds/seg/)~~
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long useTC,mod;
// /*segment tree*/   template<typename T>struct segment_tree{unsigned int N;vector<T> tree,lazy_tag;T build(unsigned int l,unsigned int r,unsigned int p,const vector<T> &original){if(l==r){return tree[p]=original[l];}unsigned int m=l+((r-l)>>1);return tree[p]=build(l,m,p<<1,original)+build(m+1,r,(p<<1)|1,original);}void update(unsigned int l,unsigned int r,T c,unsigned int s=0,unsigned int t=0,unsigned int p=1){if(p==1){s=1,t=N;}if(l<=s&&t<=r){tree[p]+=(t-s+1)*c,lazy_tag[p]+=c;return;}unsigned int m=s+((t-s)>>1);if(lazy_tag[p]){tree[p<<1]+=lazy_tag[p]*(m-s+1),tree[(p<<1)|1]+=lazy_tag[p]*(t-m),lazy_tag[p<<1]+=lazy_tag[p],lazy_tag[(p<<1)|1]+=lazy_tag[p];}lazy_tag[p]=0;if(l<=m){update(l,r,c,s,m,p<<1);}if(r>m){update(l,r,c,m+1,t,(p<<1)|1);}tree[p]=tree[p<<1]+tree[(p<<1)|1];}T getsum(unsigned int l,unsigned int r,unsigned int s=0,unsigned int t=0,unsigned int p=1){if(p==1){s=1,t=N;}if(l<=s&&t<=r) {return tree[p];}unsigned int m=s+((t-s)>>1);if(lazy_tag[p]){tree[p<<1]+=lazy_tag[p]*(m-s+1),tree[(p<<1)|1]+=lazy_tag[p]*(t-m),lazy_tag[p<<1]+=lazy_tag[p],lazy_tag[(p<<1)|1]+=lazy_tag[p];}lazy_tag[p]=0;T sum=0;if(l<=m) {sum=getsum(l,r,s,m,p<<1);}if(r>m) {sum+=getsum(l,r,m+1,t,(p<<1)|1);}return sum;}segment_tree(vector<T> original={0}){N=original.size();if(original.size()==1&&original[0]==0){N=100005;}original.insert(original.begin(),0),tree.resize(4*N),lazy_tag.resize(4*N),build(1,N,1,original),tree[0]=N;}};
/*union find set*/ struct union_find{int N;vector<int> fa;union_find(int n=100005):N(n){fa.resize(n+1);for(int i=1;i<=n;++i)fa[i]=i;}int root(int x){return ((fa[x]==x)?(x):(fa[x]=root(fa[x])));}void unite(int a,int b){fa[root(a)]=root(b);}bool same(int a,int b){return root(a)==root(b);}};
/*yes or no*/      inline string YN(bool x,string Y="Yes",string N="No"){return (x)?(Y):(N);}
/*quick pow*/      template<typename T>T pow(T a,T b,T m=mod){T res=1;a%=m;while(b>0){res=(b&1)?(res*a%m):(res);a=a*a%m;b>>=1;}return res;}
using uint=unsigned int; using i64=long long; using u64=unsigned long long;
using pii=pair<int,int>; using puu=pair<unsigned,unsigned>; using p64=pair<long long,long long>; using pu64=pair<unsigned long long,unsigned long long>;
template<class t,class u> ostream& operator<<(ostream& os,const pair<t,u>& p){return os<<"("<<p.first<<","<<p.second<<")";}
#define f0(i,n)     for(long long i=0;i<n;++i)
#define f1(i,n)     for(long long i=1;i<=n;++i)
#define ff(i,b,e,s) for(long long i=b;i<=e;i+=s)
#define all(n)      n.begin(),n.end()
#define fir         first
#define sec         second
#define pb          push_back
#define mp          make_pair
#define over(n,v)   {n; return v;}
/*
    NOTE:
    Never define variable or functions called 'f0' or 'f1' or 'ff'
    There may be strange bugs in function pow(a,b,m) and ceil()
    Use i64 if necessary
    Check useTC
    Priority_queue is max-heap (default)
*/
//Global Variables & Functions
set<i64> notsame; //若i在其中则表示在一次询问二后单独修改了a[i]
i64 a[300000];
i64 n,q;
signed temp__main()
{
    cin>>n>>q;
    i64 all=0LL,sum=0LL;
    f0(i,n) 
    {
        cin>>a[i];
        notsame.insert(i);
        sum+=a[i];
    }
    while(q--)
    {
        i64 op;cin>>op;
        if(op==2) 
        {
            cin>>all;
            sum=all*n;
            notsame.clear();
            cout<<sum<<endl;
        }
        else
        {
            i64 pos,val;
            cin>>pos>>val;
            pos--;
            i64 ori;
            if(notsame.count(pos)) ori=a[pos]; //在set中
            else ori=all,notsame.insert(pos); //不在set中
            a[pos]=val;
            sum=sum-ori+val;
            cout<<sum<<endl;
        }
    }
    return 0;
}
void temp__init()
{
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cout.setf(ios::fixed),cout.precision(20);
    useTC=0,mod=1000000007;
    unsigned long long temp__t=1;
    if(useTC)cin>>temp__t;
    while(temp__t--) temp__main();
}
signed main()
{
    temp__init();
    return 0;
}

```



---

## 作者：Shunpower (赞：1)

## 题目大意

给定一个 $n$ 项数列 $a$，有以下操作：

- 单点修改 $a_i$ 为 $x$
- 将 $a$ 中的所有值全部改为 $x$

每次操作后输出数列和。

数据范围：$1\leqslant n,q\leqslant2\cdot 10^5$

## 思路

一个最为纯粹的想法是搞一个线段树，有单点修改和全局推平，还要维护和，显然很不想写。

但是我们发现只用输出所有数的和，我们不妨试试脱离线段树。

### 单点修改

很容易，原数为 $a_i$，改成 $g$，直接给和加上一个 $g-a_i$ 就行了。

### 全局推平

假设改成 $g$ 直接把和改成 $g\times n$ 就行。

但是这会和单点修改冲突的地方在于，全局推平之后我们不会去修改 $a_i$，所以我们得在单点修改的时候将 $a_i$ 改为上次推平的数。

但是这又会出问题，我们无法知道这个要被修改的数有没有被推平过。假设一次推平之后我们要修改两次它，每次它都会被改成推平的那个数，第二次修改后维护的和就不对了。也不能通过是否等于推平数这样简单的判断来处理，所以我们必须在修改之后打上标记，然后在下次推平的时候清掉所有标记。

但是这样时间会被卡成 $O(nq)$，`memset` 清标记太慢了。容易发现我们其实把很多没有标记的点清成了没有标记的点，毫无意义，所以使用一个栈保存哪些标记需要清空。

时间复杂度回到 $O(n+q)$，原因是如果每次都要给 $x$ 个数清标记，那么最多也就只有 $\frac{n}{x}$ 次，总共是是 $O(n)$ 的。

## 代码

```
//Author:Zealous_YH
//Hai Bian & Xiao Bao
#include <bits/stdc++.h>
#define ET return 0
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ll long long
#define ull unsigned long long
#define inf INT_MAX
#define uinf INT_MIN
#define pt puts("")
#define fr1(i,a,b) for(int i=a;i<=b;i++)
#define fr2(i,a,b) for(int i=a;i>=b;i--)
#define fv(i,p) for(int i=0;i<p.size();i++)
using namespace std;
const int N=2e5+10;
int maxn=uinf,minn=inf;
int tnt,tot;
ll n,q;
ll sum;
ll a[N];
bool ok[N];
ll las;//要开long long
stack <int> s;
int main(){
	las=inf;
	cin>>n>>q;
	fr1(i,1,n){
		cin>>a[i];
		sum+=a[i];
	}
	while(q--){
		ll opt,x,y;
		cin>>opt;
		if(opt==1){
			cin>>x>>y;
			if(las!=inf&&!ok[x]){//还没有推平过或者已经推平一次了就不用再来一次了
				ok[x]=1;//打标记
				a[x]=las;
				s.push(x);//丢到栈里
			}
			sum+=y-a[x];//单点修改改和
			a[x]=y;//记得要改原数组
		}
		else{
			cin>>x;
			las=x;//记录上一次推平推平成了什么数
			sum=x*n;
			while(!s.empty()){
				ok[s.top()]=0;//用栈来快速清标记
				s.pop();
			}
		}
		cout<<sum<<endl;
	}
	ET;
}
//Teens-in-Times
//HJL 2004.06.15
//Everything For Ji.
//Everything For Lin.
//Everything For You.
```

[赛时 AC](https://codeforces.com/contest/1679/submission/157157660)

---

## 作者：小木虫 (赞：1)

### Preface  
线段树板子题。  
### Problem  
给你一个序列，有两种操作：  
1.将其中一个数更改。  
2.全体更改。  
每次操作完输出全部之和。  
### Solution  
发现简直是线段树模板题的弱化版，连询问函数都免了，直接输出根节点的值就可以了，懒惰标记也直接打在根节点上，更改的时候下传。  
code：  
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int T;
const int N=2e5+10;
ll n;ll a[N];
ll q,t,x,y;
ll tree[N<<4];ll lazy[N<<4];
void init(){
	
}
void pushdown(int rt,int left,int right){
	int mid=(left+right)/2;
	if(left==right)return;
	if(lazy[rt]){
		lazy[rt*2]=lazy[rt];
		lazy[rt*2+1]=lazy[rt];
		tree[rt*2]=(mid-left+1)*lazy[rt];
		tree[rt*2+1]=(right-mid)*lazy[rt];
		lazy[rt]=0;
	}
}
void pushup(int rt){
	tree[rt]=tree[rt*2]+tree[rt*2+1];
}
void update(int rt,int left,int right,int x,ll y){
	pushdown(rt,left,right);
	if(left==right){
		tree[rt]=y;lazy[rt]=0;return;
	}
	int mid=(left+right)/2;
	if(x<=mid)update(rt*2,left,mid,x,y);
	else update(rt*2+1,mid+1,right,x,y);
	pushup(rt);
}
void solve(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		update(1,1,n,i,a[i]);
	}
	for(int i=1;i<=q;i++){
		cin>>t;
		if(t==1){
			cin>>x>>y;
			update(1,1,n,x,y);
			pushdown(1,1,n);
			cout<<tree[1]<<endl;
		}else{
			cin>>x;
			lazy[1]=x;
			tree[1]=n*x;
			cout<<n*x<<endl;
		}
	}
}
int main(){
	T=1;
	while(T--)init(),solve();
	return 0;
}
```


---

## 作者：Anguei (赞：0)

## 题意

给你一个长度为 $n$ 的数列 $a$，进行 $q$ 次操作。操作有三种：
- 把 $a_i$ 赋值为 $x$；
- 把 $a$ 中所有数字赋值为 $x$；
- 查询 $a$ 的所有元素和。

$n, q \leq 2\times 10^5$。

## 分析

看到第二种操作（区间推平），想到珂朵莉树。

虽然此题数据不保证随机，但是只有单点修改和区间赋值两种修改操作，且所有的查询操作范围都一致，所以还是可以跑过去的。

顺带一提，由于珂朵莉树的每个区间都是相邻的，后一个区间的左端点等于前一个区间的右端点，所以珂朵莉树也可以用 `std::map` 来实现——

用二元组 $[l, val]$ 表示珂朵莉树的每个区间，使用 `std::map<int, int>` 存储。`key` 是区间的左端点，`value` 是区间的值。这比 `set` 的写法简洁不少。

[珂朵莉树做法代码](https://www.luogu.com.cn/paste/tf180kku)

## 更优的做法

虽然珂朵莉树的做法可以过，但有点碰运气的成分。其实此题还有无需数据结构的做法。

只需记录每个位置上次修改的时间戳（`lastSingle[i]`）、以及上一次全局修改是什么时候、修改成了什么即可（`lastAll`，`lastAllVal`）。

同时维护整个数列的和：若是全局修改，新的数列和是 $n\times x$；如果是单点修改，判断修改的位置之前是什么（利用时间戳），然后加加减减即可。

时间复杂度 $O(n+q)$，额外空间复杂度 $O(n)$。

```cpp
void solution() {
  int n, q;
  read(n, q);
  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) read(a[i]);
  ll s = std::accumulate(a.begin() + 1, a.end(), 0ll);
  int lastAll = -1, lastAllVal = -1;
  std::vector<int> lastSingle(n + 1);
  for (int _ = 1; _ <= q; ++_) {
    int opt;
    read(opt);
    if (opt == 1) {
      int idx, x;
      read(idx, x);
      s -= lastSingle[idx] < lastAll ? lastAllVal : a[idx];
      s += x;
      lastSingle[idx] = _;
      a[idx] = x;
    } else {
      int x;
      read(x);
      lastAll = _;
      lastAllVal = x;
      s = 1ll * x * n;
    }
    print(s);
  }
}
```

---

## 作者：Hooch (赞：0)

### 题目大意

给定一个长度为 $n$ 的正整数序列 $a$，现在有 $q$ 个操作，每个操作如下：

+ 操作 $1$，单点修改，将 $a_i$ 修改为 $x$。
+ 操作 $2$，全局修改，将所有 $i\in[1,n]$ 的 $a_i$ 修改为 $x$。

每次修改完成后，要求输出所有 $a_i$ 的和。

### 基本思路

这道题听同机房巨佬 [Zealous_YH](https://www.luogu.com.cn/user/399150) 和 [L_h_](https://www.luogu.com.cn/user/413129) 说，还能用一些比本题解的方法更简便的解法，有问题可以问一下他们，这里就不讲了。

我的解法就很暴力，直接把 $1$ 操作看成单点修改，$2$ 操作看成区间修改，求和直接看成区间和，这些都可以用**线段树**来做，然后就行了。

这个应该是打过线段树的都会的吧。

码风凑合着看吧：

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (register int i(l); i <= r; ++i)
#define rep2(i, l, r) for (register int i(l); i >= r; --i)
#define int long long
using namespace std;
const int Buffer_Size = 1 << 10;
namespace {
    char buffer[Buffer_Size], *ihead = buffer + Buffer_Size, *itail = ihead;
    inline char Next_Char() {
        if (ihead == itail) fread(buffer, 1, Buffer_Size, stdin), ihead = buffer;
        return *ihead++;
    }
    template <typename T>
    inline void read(T &x) {
        x = 0; char ch = Next_Char(); T f = 1;
        while (!isdigit(ch)) f -= (ch == '-') << 1, ch = Next_Char();
        while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = Next_Char();
        x *= f;
    }
    template <typename T, typename ...L> inline void read(T &x, L &...y) {read(x), read(y...);}
    inline void readstr(string &s) {
        s = ""; char ch = Next_Char();
        while (ch == ' ' || ch == '\n') ch = Next_Char();
        while (ch ^ ' ' && ch ^ '\n') s += ch, ch = Next_Char();
    }
    inline int read() {int x; read(x); return x;}
}
const int N = 2e5 + 5;
int n, q; 
inline int lson(int x) {return x << 1;}
inline int rson(int x) {return x << 1 | 1;}
struct node {
    int l, r; //左右端点
    int tag, sum;
} t[N << 2];
inline void pushup(int x) { 
    t[x].sum = t[lson(x)].sum + t[rson(x)].sum; 
}
inline void pushdown(int x) {
    if (t[x].tag == -1) return ;
    t[lson(x)].tag = t[rson(x)].tag = t[x].tag;
    int mid = t[x].r + t[x].l >> 1;
    t[lson(x)].sum = (mid - t[x].l + 1) * t[x].tag;
    t[rson(x)].sum = (t[x].r - mid) * t[x].tag;
    t[x].tag = -1;
}
inline void buildtree(int x, int l, int r) {
    t[x].tag = -1; t[x].l = l; t[x].r = r;
    if (t[x].l == t[x].r) {
        t[x].sum = read();
        return ;
    } int mid = t[x].l + t[x].r >> 1;
    buildtree(lson(x), l, mid);
    buildtree(rson(x), mid + 1, r);
    pushup(x);
}
inline void update(int x, int L, int R, int val) {
    if (L <= t[x].l && t[x].r <= R) {
        t[x].tag = val;
        t[x].sum = val * (t[x].r - t[x].l + 1);
        return ;
    } int mid = t[x].l + t[x].r >> 1; pushdown(x);
    if (L <= mid) update(lson(x), L, R, val);
    if (R > mid) update(rson(x), L, R, val); 
    pushup(x);
}
signed main(void) {
    read(n, q); buildtree(1, 1, n);
    while (q--) {
        int op, pos, x; read(op);
        if (op == 1) {
            read(pos, x);
            update(1, pos, pos, x);
        } else {
            read(x);
            update(1, 1, n, x);
        }
        printf("%lld\n", t[1].sum);
    }
}
```



---

